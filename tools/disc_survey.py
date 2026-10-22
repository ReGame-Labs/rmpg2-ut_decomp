#!/usr/bin/env python3
"""Survey the extracted disc: the executable's header and regions, the files by extension and directory, and the
overlays' candidate load addresses.

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
LOADS_STORES = (0x09, 0x20, 0x21, 0x23, 0x24, 0x25, 0x28, 0x29, 0x2B)  # addiu, lb..sw

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
    gp = sum(1 for w in ws if (w >> 21) & 31 == 28 and w >> 26 in LOADS_STORES)
    # Over the whole image, data included: words of .rodata/.data decode as instructions too (docs/TOOLCHAIN.md
    # "Compiler" has the count over the code alone: none).
    print(f"  {gp} words decoding as $gp-relative loads/stores/addiu (data included)")
    last = max(i for i, w in enumerate(ws) if w)
    print(f"  last non-zero word 0x{base + last * 4:08x}; image end 0x{base + len(ws) * 4:08x}")


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
    """Each overlay's candidate load address: the lui/lo references its code makes, clustered."""
    print("== overlays: addresses their code references (the load address makes most of them land inside)")
    for p in sorted(OVERLAYS.glob("*.BIN")):
        d = p.read_bytes()
        refs = [a for a in hilo_addresses(words(d[:len(d) & ~3])) if 0x80010000 <= a < 0x80200000]
        hist = collections.Counter(a >> 16 for a in refs)
        top = ", ".join(f"0x{h:04x}xxxx: {n}" for h, n in hist.most_common(4))
        print(f"  {p.name:14} {len(d):7} B  {len(refs):5} refs  {top}")


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
    file_types()
    check_overlays()
    if args.checksums:
        write_checksums()


if __name__ == "__main__":
    main()
