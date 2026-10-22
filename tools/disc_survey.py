#!/usr/bin/env python3
"""Survey the extracted disc: the executable's header, regions and memory map (crt0, .bss, the heap), its file
table against the disc, the files by extension and directory, and the overlays' load address.

Reproduces the findings in docs/DISC_LAYOUT.md. Run after scripts/extract.sh:
    tools/venv/bin/python tools/disc_survey.py [--checksums]

--checksums rewrites config/SLUS_007.42.sha1 and config/overlays.sha1.
Adapted from gascarcella/dw2003recomp's tools/disc_survey.py (MIT; docs/THIRD_PARTY.md).
"""
import argparse
import collections
import hashlib
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
DISC = ROOT / "extracted" / "disc"
EXE = DISC / "SLUS_007.42"
OVERLAYS = DISC / "OVERLAYS"
DISC_XML = ROOT / "extracted" / "rmpg2.xml"   # dumpsxiso's rebuild description: the files in disc order
LOADS_STORES = (0x09, 0x20, 0x21, 0x23, 0x24, 0x25, 0x28, 0x29, 0x2B)  # addiu, lb..sw

# The executable's layout (config/main.yaml); the survey checks the facts below against the image.
TEXT_START, TEXT_END = 0x80017758, 0x8007A684     # crt0, the game's code, the libraries
DATA_START, DATA_END = 0x8007A684, 0x80097EA4     # .data; the file is padded to a sector after it
OVERLAY_BASE, OVERLAY_END = 0x80097EA4, 0x800AA240  # both overlays load here; OVERMOVE.BIN fills it exactly
BSS_START, BSS_END = 0x800AA240, 0x801FE208       # .bss, cleared by crt0
FILE_TABLE = (0x80089820, 0x80089DA0, 0x80010000, 352)  # CdlLOC per file, sizes, checksums (.rodata), entries

# Opcodes and funct codes of the R3000 user-mode instruction set, to tell code from data by density.
OPS = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 18, 32, 33, 34, 35, 36, 37, 38, 40, 41, 42, 43, 46, 49,
       50, 57, 58}
FUNCTS = {0, 2, 3, 4, 6, 7, 8, 9, 12, 13, 16, 17, 18, 19, 24, 25, 26, 27, 32, 33, 34, 35, 36, 37, 38, 39, 42, 43}


def words(data):
    return struct.unpack_from(f"<{len(data) // 4}I", data)


def is_insn(w):
    op = w >> 26
    return w == 0 or op in OPS or (op == 0 and (w & 0x3F) in FUNCTS)


def hilo_addresses(ws):
    """Absolute addresses built by lui + (addiu | load | store) pairs."""
    out = []
    for i, x in enumerate(ws):
        if x >> 26 != 0x0F:
            continue
        rt, hi = (x >> 16) & 31, (x & 0xFFFF) << 16
        for y in ws[i + 1: i + 8]:
            if (y >> 21) & 31 == rt and y >> 26 in LOADS_STORES:
                lo = y & 0xFFFF
                out.append((hi + lo - (0x10000 if lo & 0x8000 else 0)) & 0xFFFFFFFF)
                break
    return out


def exe_header():
    d = EXE.read_bytes()
    assert d[:8] == b"PS-X EXE", "not a PS-X EXE"
    f = struct.unpack_from("<10I", d, 0x10)
    names = ["pc0", "gp0", "t_addr", "t_size", "d_addr", "d_size", "b_addr", "b_size", "s_addr", "s_size"]
    print(f"== {EXE.name}: {len(d)} bytes, SHA-1 {hashlib.sha1(d).hexdigest()}")
    for n, v in zip(names, f):
        print(f"  {n:7} 0x{v:08x}")
    marker = d[0x4C:0x80].split(b"\0")[0].decode()
    print(f"  marker  {marker}")
    return d, f[2]


def exe_regions(d, base):
    """Code and data regions by instruction density (1 KB windows), the entry's $gp, the last used word."""
    ws = words(d[0x800:])
    print("== regions (by instruction density per 1 KB; the exact boundaries are in config/main.yaml)")
    prev = None
    for s in range(0, len(ws), 256):
        win = ws[s:s + 256]
        dens = sum(1 for w in win if is_insn(w)) / len(win)
        zero = sum(1 for w in win if w == 0) / len(win)
        cls = "code" if dens > 0.97 and zero < 0.5 else ("zero" if zero > 0.95 else "data")
        if cls != prev:
            print(f"  0x{base + s * 4:08x} {cls}")
            prev = cls
    jr = [i for i, w in enumerate(ws) if w == 0x03E00008]
    print(f"  first `jr $ra` 0x{base + jr[0] * 4:08x}, last 0x{base + jr[-1] * 4:08x}, {len(jr)} in all")
    for i, w in enumerate(ws):
        if w >> 16 == 0x3C1C and ws[i + 1] >> 16 == 0x279C:  # lui $gp / addiu $gp, $gp
            lo = ws[i + 1] & 0xFFFF
            lo -= 0x10000 if lo & 0x8000 else 0
            print(f"  $gp = 0x{((w & 0xFFFF) << 16) + lo:08x} (set at 0x{base + i * 4:08x})")
    code = ws[(TEXT_START - base) // 4:(TEXT_END - base) // 4]
    gp = sum(1 for w in code if (w >> 21) & 31 == 28 and w >> 26 in LOADS_STORES and (w >> 16) & 31 != 28)
    print(f"  {gp} $gp-relative loads/stores in the code (crt0's own `addiu $gp` excluded): no small data")
    last = max(i for i, w in enumerate(ws) if w)
    print(f"  last non-zero word 0x{base + last * 4:08x}; image end 0x{base + len(ws) * 4:08x}")


def memory_map(d, base):
    """What crt0 does with RAM, and the .bss bounds from the addresses the code builds with lui/addiu pairs."""
    ws = words(d[0x800:])
    code = ws[(TEXT_START - base) // 4:(TEXT_END - base) // 4]
    print("== memory map")
    # crt0 (Psy-Q 2MBYTE.OBJ): clears [v0, v1) in words, reads _ramsize, sets $sp, calls InitHeap(_end + 4,
    # _ramsize - _stacksize - _end) and then main. The two lui/addiu pairs at its start are the clear range.
    entry = struct.unpack_from("<I", d, 0x10)[0]
    crt0 = hilo_addresses(ws[(entry - base) // 4:(entry - base) // 4 + 4])
    print(f"  crt0 clears 0x{crt0[0]:08x}-0x{crt0[1]:08x} ({crt0[1] - crt0[0]} B): .bss")
    stacksize_at = 0x8007A70C  # crt0: lw v1, %lo(_stacksize)(v1) after `lui v1, 0x8008`
    ramsize, stacksize = ws[(0x80017810 - base) // 4], ws[(stacksize_at - base) // 4]
    heap = crt0[1] + 4
    print(f"  _ramsize 0x{ramsize:x} (crt0's table at 0x80017810), _stacksize 0x{stacksize:x} (0x{stacksize_at:08x}); "
          f"$sp = 0x{0x80000000 | ramsize:08x}; InitHeap(0x{heap:08x}, 0x{ramsize - stacksize - (crt0[1] & 0x1FFFFFFF):x})")
    refs = [a for a in hilo_addresses(code) if DATA_END <= a < 0x80200000]
    ovl = sorted({a for a in refs if a < OVERLAY_END})
    bss = [a for a in refs if OVERLAY_END <= a < crt0[1]]
    print(f"  code references above .data: {len(refs)}; in the overlay region {len(ovl)} distinct "
          f"(0x{ovl[0]:08x} the loader's destination, then overlay symbols from 0x{ovl[1]:08x}), "
          f"in .bss {len(bss)} (0x{min(bss):08x}-0x{max(bss):08x}), above it "
          f"{sorted({hex(a) for a in refs if a >= crt0[1]})}")
    dws = ws[(DATA_START - base) // 4:(DATA_END - base) // 4]
    ptrs = [w for w in dws if OVERLAY_BASE <= w < OVERLAY_END]
    print(f"  .data words pointing into the overlay region: {len(ptrs)} (0x{min(ptrs):08x}-0x{max(ptrs):08x}: "
          f"OVERATTR.BIN's strings)")


def xml_files():
    """The disc's files in disc order from extracted/rmpg2.xml, with their type; [] without the XML."""
    if not DISC_XML.exists():
        return []
    import re
    names, stack = [], []
    for m in re.finditer(r"<(dir|/dir|file)\b([^>]*)>", DISC_XML.read_text()):
        tag, attrs = m.group(1), m.group(2)
        if tag == "dir":
            stack.append(re.search(r'name="([^"]+)"', attrs).group(1))
        elif tag == "/dir":
            stack.pop()
        else:
            names.append(("/".join(stack + [re.search(r'name="([^"]+)"', attrs).group(1)]),
                          re.search(r'type="([^"]+)"', attrs).group(1)))
    return names


def file_table(d, base):
    """The executable's file table: a CdlLOC (BCD minute, second, sector, track) and a size per file, in disc order,
    plus a checksum table at the start of .rodata. Checked against the disc's file order (the XML) and sizes."""
    locs, sizes, sums, n = FILE_TABLE
    print(f"== file table: {n} entries; CdlLOC at 0x{locs:08x}, sizes at 0x{sizes:08x}, checksums at 0x{sums:08x}")
    ws = words(d[0x800:])
    files = xml_files()
    # The table skips SYSTEM.CNF and the executable; the CDPAD*.DAT padding files come after its last entry.
    # Streams ("mixed": XA) are in it with a placeholder checksum: they are played, not read and checked.
    disc = [f for f in files[2:] if not f[0].startswith("CDPAD")]
    bcd = lambda b: (b >> 4) * 10 + (b & 15)
    ok = used = 0
    for i in range(n):
        m, s, f, _ = d[0x800 + locs - base + i * 4: 0x800 + locs - base + i * 4 + 4]
        lba = (bcd(m) * 60 + bcd(s)) * 75 + bcd(f) - 150
        size, cks = ws[(sizes - base) // 4 + i], ws[(sums - base) // 4 + i]
        if size == 0:
            continue
        used += 1
        if i < len(disc):
            name, kind = disc[i]
            p = DISC / name
            on_disc = p.stat().st_size if p.exists() else -1
            ok += size == on_disc
            if "OVER" in name or size != on_disc:
                print(f"  {i:3} lba {lba:6} size {size:8} checksum {cks:08x}  {name} ({on_disc} B on disc"
                      f"{'' if size == on_disc else ', differs'})")
    print(f"  {used} entries used, {n - used} spare; {ok} sizes match the disc's files in XML order"
          + ("" if files else " (no extracted/rmpg2.xml: not checked)"))


def file_types():
    print("== files by extension")
    stats = collections.defaultdict(lambda: [0, 0])
    for p in DISC.rglob("*"):
        if p.is_file():
            ext = p.suffix.upper().lstrip(".") or "(none)"
            stats[ext][0] += 1
            stats[ext][1] += p.stat().st_size
    for ext, (n, size) in sorted(stats.items(), key=lambda kv: -kv[1][1]):
        print(f"  {ext:8} {n:5} files {size / 2**20:9.2f} MiB")
    print("== files by directory")
    for d in sorted(p for p in DISC.iterdir() if p.is_dir()):
        files = [p for p in d.rglob("*") if p.is_file()]
        print(f"  {d.name:10} {len(files):4} files {sum(p.stat().st_size for p in files) / 2**20:9.2f} MiB")


def check_overlays():
    """Each overlay at the load address: where the lui/lo references its code makes land (inside itself, in the
    executable, in .bss), and its end against the start of .bss."""
    print(f"== overlays at 0x{OVERLAY_BASE:08x} (the executable reads one into a buffer and copies it there)")
    for p in sorted(OVERLAYS.glob("*.BIN")):
        d = p.read_bytes()
        end = OVERLAY_BASE + len(d)
        refs = [a for a in hilo_addresses(words(d[:len(d) & ~3])) if 0x80010000 <= a < 0x80200000]
        where = collections.Counter("itself" if OVERLAY_BASE <= a < end else "exe" if a < OVERLAY_BASE else
                                    ".bss" if BSS_START <= a < BSS_END else "other" for a in refs)
        print(f"  {p.name:14} {len(d):7} B  0x{OVERLAY_BASE:08x}-0x{end:08x}  {len(refs):5} refs: "
              + ", ".join(f"{k} {v}" for k, v in where.most_common())
              + ("  (ends where .bss starts)" if end == BSS_START else ""))


def write_checksums():
    cfg = ROOT / "config"
    (cfg / "SLUS_007.42.sha1").write_text(f"{hashlib.sha1(EXE.read_bytes()).hexdigest()}  SLUS_007.42\n")
    lines = [f"{hashlib.sha1(p.read_bytes()).hexdigest()}  OVERLAYS/{p.name}" for p in sorted(OVERLAYS.glob("*.BIN"))]
    (cfg / "overlays.sha1").write_text("\n".join(lines) + "\n")
    print(f"== wrote config/SLUS_007.42.sha1 and config/overlays.sha1 ({len(lines)} overlays)")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--checksums", action="store_true", help="rewrite config/*.sha1")
    args = ap.parse_args()
    if not EXE.exists():
        sys.exit("extracted/disc missing; run scripts/extract.sh first")
    d, base = exe_header()
    exe_regions(d, base)
    memory_map(d, base)
    file_table(d, base)
    file_types()
    check_overlays()
    if args.checksums:
        write_checksums()


if __name__ == "__main__":
    main()
