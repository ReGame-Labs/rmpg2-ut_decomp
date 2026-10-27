#!/usr/bin/env python3
"""Compile one C unit on its own and check it per function against the original, without ninja.

Compiles src/<target>/<unit>.c the way build.ninja does (compiler and -G from configure.py's
CC_OVERRIDES/G_OVERRIDES, via tools/cc_psx.sh) into build/unit_diff/, then compares it with
build/expected/<target>/<unit>.s.o (made by ninja; `scripts/build.sh` once). Safe to run while other
sessions edit other units: it touches no ninja state.

The check is the link's: every word of the object as the link would write it. Relocations are applied with the
addresses they resolve to: the original's symbols (config/symbol_addrs.txt, config/<target>.symbols.txt, the
target's extra linker scripts such as config/aliases.ld, which gives one address several names; splat's names like
D_8004xxxx and its undefined_*_auto lists; the last link's symbols last), the original object's own sections at
their addresses. A function passes when its size is the original's and every instruction is the same word once
linked (opcode, registers, immediates, relocated fields and branch targets), and, for a function with a jump table
in .rodata, when the table's entries are. Each function of the C object is placed at the original function's
address, so a function is judged on its own even when an earlier one changed size. objdiff's match percent is
shown next to each function as the score to iterate on; it does not decide the result ("OK (by address)": objdiff
scores the function below 100%, typically a relocation naming another symbol for the same address, while the
linked words are the original's).

The summary says the unit links to the original bytes only when every function (C and asm) is at its original
offset with its original size and passes, the .text between functions is the original's, and every data section
the C provides (.rodata, .data, .sdata: the YAML's `.rodata`-style subsegments) is word for word the original's
once relocated. Each section ends where the link starts the next object's (the zero fill up to a `. = ALIGN(8);`
of the target's linker script is part of it: the original's asm has it, the C object not). The exit status is 0
then, 1 otherwise. Data sections the unit still takes from asm are not
compared (listed with --all).

  tools/venv/bin/python tools/unit_diff.py main                 # every function's result
  tools/venv/bin/python tools/unit_diff.py main func_8001781C   # + side-by-side instruction diff
  options: -G N / -V VER to override the file's -G or compiler; --all to list INCLUDE_ASM ones too;
           -D NON_MATCHING (repeatable) to score the WIP C instead of its INCLUDE_ASM
Adapted from gascarcella/dw2003recomp's tools/unit_diff.py (MIT; docs/THIRD_PARTY.md).
"""
import argparse
import bisect
import json
import math
import re
import struct
import subprocess
import sys
from collections import Counter
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT))
import configure  # noqa: E402  (CC_OVERRIDES, g_for, DEFAULT_CC, CC_INCLUDES, TARGETS, EXE_SYMS)

OBJDUMP = ROOT / "tools/binutils/bin/mipsel-linux-gnu-objdump"


def run(cmd):
    return subprocess.run(cmd, capture_output=True, text=True, cwd=ROOT)


NAME_ADDR = re.compile(r"^(?:D|func|jtbl)_(?:[A-Z0-9]+_)?([0-9A-F]{8})$")  # splat's default names

# ---- the objects ------------------------------------------------------------------------------------------------

R_MIPS_32, R_MIPS_26, R_MIPS_HI16, R_MIPS_LO16, R_MIPS_GPREL16, R_MIPS_PC16 = 2, 4, 5, 6, 7, 10
RELOC_NAMES = {R_MIPS_32: "32", R_MIPS_26: "26", R_MIPS_HI16: "HI16", R_MIPS_LO16: "LO16",
               R_MIPS_GPREL16: "GPREL16", R_MIPS_PC16: "PC16"}
SHN_UNDEF, SHN_ABS, SHN_COMMON = 0, 0xFFF1, 0xFFF2
STT_FUNC, STT_SECTION = 2, 3


def _s16(x: int) -> int:
    return x - 0x10000 if x & 0x8000 else x


class Elf:
    """A relocatable little-endian MIPS ELF32 object: sections, symbols, relocations (REL)."""

    def __init__(self, path: Path):
        self.path = Path(path)
        b = self.path.read_bytes()
        if b[:4] != b"\x7fELF" or b[4] != 1 or b[5] != 1:
            sys.exit(f"{path}: not a little-endian ELF32 object")
        shoff, = struct.unpack_from("<I", b, 0x20)
        shentsize, shnum, shstrndx = struct.unpack_from("<HHH", b, 0x2E)
        hdrs = [struct.unpack_from("<10I", b, shoff + i * shentsize) for i in range(shnum)]
        names = hdrs[shstrndx]

        def cstr(table, off):
            start = table[4] + off
            return b[start:b.index(b"\0", start)].decode("latin-1")

        self.names = [cstr(names, h[0]) for h in hdrs]
        self.size = [h[5] for h in hdrs]
        self.data = [b[h[4]:h[4] + h[5]] if h[1] != 8 else b"" for h in hdrs]  # SHT_NOBITS has no bytes
        self.index = {}
        for i, n in enumerate(self.names):
            self.index.setdefault(n, i)
        self.syms = []  # (name, value, size, type, bind, shndx)
        for h in hdrs:
            if h[1] == 2:  # SHT_SYMTAB
                strtab = hdrs[h[6]]
                for off in range(h[4], h[4] + h[5], 16):
                    nm, value, size, info, _, shndx = struct.unpack_from("<IIIBBH", b, off)
                    name = cstr(strtab, nm)
                    if info & 0xF == STT_SECTION and shndx < len(self.names):
                        name = self.names[shndx]
                    self.syms.append((name, value, size, info & 0xF, info >> 4, shndx))
        self.relocs = {}  # section index -> [(offset, type, symbol index)] in the table's order
        for h in hdrs:
            if h[1] == 9:  # SHT_REL
                self.relocs[h[7]] = [(o, i & 0xFF, i >> 8) for o, i in struct.iter_unpack("<II", b[h[4]:h[4] + h[5]])]

    def section_words(self, name: str):
        i = self.index.get(name)
        if i is None:
            return []
        d = self.data[i]
        return [int.from_bytes(d[o:o + 4].ljust(4, b"\0"), "little") for o in range(0, len(d), 4)]

    def section_size(self, name: str) -> int:
        i = self.index.get(name)
        return 0 if i is None else self.size[i]

    def functions(self) -> dict:
        """Function name -> (offset, size) in .text, in offset order (alternative entries without a size left out)."""
        text = self.index.get(".text")
        funcs = sorted((v, s, n) for n, v, s, t, _, shndx in self.syms if t == STT_FUNC and shndx == text and s)
        return {n: (v, s) for v, s, n in funcs}

    def asm_functions(self) -> set:
        """Functions still in INCLUDE_ASM: the `nonmatching` macro gives each a `<name>.NON_MATCHING` symbol."""
        return {s[0][:-len(".NON_MATCHING")] for s in self.syms if s[0].endswith(".NON_MATCHING")}

    def defined(self) -> dict:
        """Global symbol name -> (section name, value), for the definitions the other object may reference."""
        return {n: (self.names[shndx], v) for n, v, _, t, bind, shndx in self.syms
                if bind != 0 and shndx not in (SHN_UNDEF, SHN_ABS, SHN_COMMON) and shndx < len(self.names)
                and not n.endswith(".NON_MATCHING")}


# ---- where symbols are ------------------------------------------------------------------------------------------

ASSIGN = re.compile(r"^\s*([A-Za-z_.$][\w.$]*)\s*=\s*([^;]+);", re.M)
ALIAS_EXPR = re.compile(r"^([A-Za-z_.$][\w.$]*)\s*(?:([+-])\s*(0x[0-9A-Fa-f]+|\d+))?$")


def read_assignments(path: Path):
    """`name = value;` lines of a symbol file or linker script: ({name: {addresses}}, {name: (other, addend)})."""
    addrs, aliases = {}, {}
    if not path.exists():
        return addrs, aliases
    text = re.sub(r"/\*.*?\*/", "", path.read_text(errors="replace"), flags=re.S)
    for name, expr in ASSIGN.findall(text):
        expr = expr.strip()
        if re.fullmatch(r"0x[0-9A-Fa-f]+|\d+", expr):
            addrs.setdefault(name, set()).add(int(expr, 0))
        elif m := ALIAS_EXPR.match(expr):
            k = int(m.group(3), 0) if m.group(3) else 0
            aliases[name] = (m.group(1), -k if m.group(2) == "-" else k)
    return addrs, aliases


def _unique(seen: dict) -> dict:
    """Names given to more than one address (static helpers copied per file) are left out."""
    return {n: a.pop() for n, a in seen.items() if len(a) == 1}


class Resolver:
    """Symbol name -> address, in order: the original object's own definitions, the project's symbol files and
    linker scripts (exact), splat's default names (D_80012345), splat's undefined_*_auto lists and the last link's
    symbols (derived), each alias through the name it stands for."""

    def __init__(self, exact: dict, derived: dict = None, aliases: dict = None):
        self.exact, self.derived, self.aliases = exact, derived or {}, aliases or {}
        self.local = {}  # filled by compare(): the original object's definitions

    @classmethod
    def for_target(cls, target: str) -> "Resolver":
        t = next((t for t in configure.TARGETS if t.name == target), None)
        if t is None:
            sys.exit(f"unknown target {target}")
        exact, derived, aliases = {}, {}, {}
        files = ["config/symbol_addrs.txt", f"config/{target}.symbols.txt",
                 *(f for f in t.ld_extra if f != configure.EXE_SYMS)]
        for f in files:
            a, al = read_assignments(ROOT / f)
            for n, v in a.items():
                exact.setdefault(n, set()).update(v)
            aliases.update(al)
        for f in (f"build/{target}/undefined_syms_auto.txt", f"build/{target}/undefined_funcs_auto.txt",
                  configure.EXE_SYMS):
            a, al = read_assignments(ROOT / f)
            for n, v in a.items():
                derived.setdefault(n, set()).update(v)
            for n, v in al.items():
                aliases.setdefault(n, v)
        return cls(_unique(exact), _unique(derived), aliases)

    def named(self, name: str, depth: int = 0):
        """The address the project's files give `name` (no object definitions), or None."""
        if name in self.exact:
            return self.exact[name]
        if name in self.aliases and depth < 8:
            other, k = self.aliases[name]
            a = self.address(other, depth + 1)
            return None if a is None else a + k
        m = NAME_ADDR.match(name)
        if m:
            return int(m.group(1), 16)
        return self.derived.get(name)

    def address(self, name: str, depth: int = 0):
        if name in self.local:
            return self.local[name]
        return self.named(name, depth)


def map_bases(target: str, unit: str) -> dict:
    """Where the last link put this unit's sections (build/<target>/*.map): the fallback for a section of the
    original object that has no symbol with a known address."""
    bases = {}
    for path in sorted((ROOT / f"build/{target}").glob("*.map")):
        for ln in path.read_text(errors="replace").splitlines():
            m = re.match(r"^ (\.\w+)\s+0x([0-9a-f]+)\s+0x[0-9a-f]+ \S*/" + re.escape(unit) + r"\.[cs]\.o$", ln)
            if m and int(m.group(2), 16):
                bases.setdefault(m.group(1), int(m.group(2), 16))
    return bases


def section_bases(elf: Elf, resolver: Resolver, fallback: dict = None) -> dict:
    """The original object's sections' addresses, from its symbols whose address the project's files give (the most
    common answer wins), else `fallback`."""
    votes = {}
    for name, value, _, typ, _, shndx in elf.syms:
        if typ == STT_SECTION or shndx in (SHN_UNDEF, SHN_ABS, SHN_COMMON) or shndx >= len(elf.names):
            continue
        if name.startswith(".") or name.endswith(".NON_MATCHING"):
            continue
        a = resolver.named(name)
        if a is not None:
            votes.setdefault(elf.names[shndx], Counter())[a - value] += 1
    bases = dict(fallback or {})
    bases.update({sec: c.most_common(1)[0][0] for sec, c in votes.items()})
    return bases


class Placement:
    """Where a section offset of an object lands: the original object's sections at their bases; the C object's
    .text function by function at the same-named original function (so that a function is compared on its own when
    an earlier one changed size), its other sections where the original's are. A location without a known base
    stays (section, offset), which compares equal only to the same location in the other object."""

    def __init__(self, bases: dict, funcs: dict = None, original_funcs: dict = None):
        self.bases = bases
        self.spans = []  # (start, end, offset in the original), C object only
        if funcs and original_funcs:
            self.spans = sorted((v, v + s, original_funcs[n][0]) for n, (v, s) in funcs.items() if n in original_funcs)
        self.starts = [s[0] for s in self.spans]

    def locate(self, sec: str, off: int):
        if sec == ".text" and self.spans:
            i = bisect.bisect_right(self.starts, off) - 1
            if i >= 0 and off < self.spans[i][1]:
                off = self.spans[i][2] + off - self.spans[i][0]
        if sec in self.bases:
            return (self.bases[sec] + off) & 0xFFFFFFFF
        return ("@" + sec, off)


def linked_words(elf: Elf, sec: str, place: Placement, resolver: Resolver):
    """`sec`'s words as the link writes them: each relocated field filled in with the address its target resolves
    to (an int), or, where an address can't be known, (the word without the field, relocation type, target)."""
    words = elf.section_words(sec)
    i = elf.index.get(sec)
    if i is None:
        return words
    rels = elf.relocs.get(i, [])

    def target(symi, addend):
        name, value, _, _, _, shndx = elf.syms[symi]
        if shndx in (SHN_UNDEF, SHN_COMMON):
            a = resolver.address(name)
            return ("?" + name, addend) if a is None else (a + addend) & 0xFFFFFFFF
        if shndx == SHN_ABS:
            return (value + addend) & 0xFFFFFFFF
        return place.locate(elf.names[shndx], value + addend)

    for k, (off, typ, symi) in enumerate(rels):
        w = words[off // 4]
        if typ == R_MIPS_HI16:  # the addend pairs with the next LO16 of the same symbol, as ld pairs them
            lo = next((words[o // 4] & 0xFFFF for o, t, s in rels[k + 1:] if t == R_MIPS_LO16 and s == symi), 0)
            a = ((w & 0xFFFF) << 16) + _s16(lo)
        elif typ == R_MIPS_26:
            a = (w & 0x3FFFFFF) << 2
        elif typ == R_MIPS_PC16:
            a = _s16(w & 0xFFFF) << 2
        elif typ == R_MIPS_32:
            a = w
        else:  # LO16, GPREL16
            a = _s16(w & 0xFFFF)
        t = target(symi, a)
        here = place.locate(sec, off)
        if typ == R_MIPS_32:
            mask, field = 0xFFFFFFFF, t
        elif typ == R_MIPS_26:
            mask, field = 0x3FFFFFF, None if isinstance(t, tuple) else (t >> 2) & 0x3FFFFFF
        elif typ == R_MIPS_HI16:
            mask, field = 0xFFFF, None if isinstance(t, tuple) else ((t + 0x8000) >> 16) & 0xFFFF
        elif typ == R_MIPS_LO16:
            mask, field = 0xFFFF, None if isinstance(t, tuple) else t & 0xFFFF
        elif typ == R_MIPS_PC16 and not isinstance(t, tuple) and not isinstance(here, tuple):
            mask, field = 0xFFFF, ((t - here) >> 2) & 0xFFFF
        else:  # GPREL16 ($gp is not modelled), a PC16 that can't be placed
            mask, field = 0xFFFF, None
        if typ == R_MIPS_32:
            words[off // 4] = t
        elif field is None:
            words[off // 4] = (w & ~mask & 0xFFFFFFFF, RELOC_NAMES.get(typ, str(typ)), t)
        else:
            words[off // 4] = (w & ~mask & 0xFFFFFFFF) | field
    return words


# ---- the comparison ---------------------------------------------------------------------------------------------

class Result:
    def __init__(self):
        self.functions = {}   # name -> [reasons]; [] = passes
        self.asm = set()      # functions still in INCLUDE_ASM in the C object
        self.order = []       # the original's functions in offset order, then the C object's extra ones
        self.sections = {}    # data section -> ("OK" | "OK by address" | "DIFFERS", detail)
        self.unit = []        # reasons the unit does not link to the original bytes
        self.words = {}       # function -> (original words, C words), for the side-by-side diff

    @property
    def links(self) -> bool:
        return not self.unit


def compare(expected: Path, out: Path, resolver: Resolver, fallback_bases: dict = None,
            c_sections=None, align: dict = None) -> Result:
    """Compare the C object `out` with the original's object `expected`. `c_sections`: the data sections the C
    object provides (None: those either object has bytes in). `align`: section -> the alignment the link gives
    what follows it (`following_alignment`; 4 when not given): the zero fill up to there is part of the section."""
    e, c = Elf(expected), Elf(out)
    res = Result()
    bases = section_bases(e, resolver, fallback_bases)

    def size(elf, sec):
        """`sec`'s size as the link lays it out: up to where the next object's section starts."""
        n, a = elf.section_size(sec), max(4, (align or {}).get(sec, 4))
        start = bases.get(sec, 0)
        return 0 if not n else -(-(start + n) // a) * a - start

    def fill(words, elf, sec):
        return words + [0] * (size(elf, sec) // 4 - len(words))
    e_place = Placement(bases)
    resolver.local = {}
    for n, (sec, v) in e.defined().items():
        a = e_place.locate(sec, v)
        if not isinstance(a, tuple):
            resolver.local[n] = a
    e_funcs, c_funcs = e.functions(), c.functions()
    c_place = Placement(bases, c_funcs, e_funcs)
    e_text = fill(linked_words(e, ".text", e_place, resolver), e, ".text")
    c_text = fill(linked_words(c, ".text", c_place, resolver), c, ".text")
    res.asm = c.asm_functions()

    res.order = list(e_funcs) + [n for n in c_funcs if n not in e_funcs]
    for name in res.order:
        if name not in c_funcs:
            res.functions[name] = ["missing from the C object"]
            continue
        if name not in e_funcs:
            res.functions[name] = ["not in the original"]
            continue
        (eo, es), (co, cs) = e_funcs[name], c_funcs[name]
        ew, cw = e_text[eo // 4:(eo + es) // 4], c_text[co // 4:(co + cs) // 4]
        res.words[name] = (ew, cw)
        reasons = []
        if es != cs:
            reasons.append(f"size 0x{cs:X}, original 0x{es:X}")
        ndiff = sum(1 for x, y in zip(ew, cw) if x != y)
        if ndiff:
            first = next(i for i, (x, y) in enumerate(zip(ew, cw)) if x != y)
            reasons.append(f"{ndiff} instruction{'s' * (ndiff > 1)} differ{'s' * (ndiff == 1)},"
                           f" the first at +0x{first * 4:X}")
        res.functions[name] = reasons

    # The layout: every function at its original offset with its original size, the bytes between them the same.
    if size(e, ".text") != size(c, ".text"):
        res.unit.append(f".text 0x{c.section_size('.text'):X} bytes, original 0x{e.section_size('.text'):X}")
    moved = [n for n in res.order if e_funcs.get(n) != c_funcs.get(n)]
    if moved:
        res.unit.append(f"{len(moved)} function{'s' * (len(moved) > 1)} not at the original's offset or size"
                        f" (first {moved[0]})")
    elif len(e_text) == len(c_text):
        inside = set()
        for o, s in e_funcs.values():
            inside.update(range(o // 4, (o + s) // 4))
        if any(x != y for i, (x, y) in enumerate(zip(e_text, c_text)) if i not in inside):
            res.unit.append(".text between functions differs")

    # Data sections: word for word once relocated; a .rodata word that points into a function is its jump table.
    raw = Resolver({})
    e_spans = sorted((o, o + s, n) for n, (o, s) in e_funcs.items())
    text_base = bases.get(".text")

    def function_at(w):
        if isinstance(w, int) and text_base is not None:
            off = w - text_base
        elif isinstance(w, tuple) and w[0] == "@.text":
            off = w[1]
        else:
            return None
        i = bisect.bisect_right([s[0] for s in e_spans], off) - 1
        return e_spans[i][2] if i >= 0 and off < e_spans[i][1] else None

    for sec in (".rodata", ".data", ".sdata"):
        if c_sections is not None and sec not in c_sections:
            if e.section_size(sec):
                res.sections[sec] = ("asm", f"{e.section_size(sec)} bytes")
            continue
        if not e.section_size(sec) and not c.section_size(sec):
            continue
        a = fill(linked_words(e, sec, e_place, resolver), e, sec)
        b = fill(linked_words(c, sec, c_place, resolver), c, sec)
        if a == b:
            ra = fill(linked_words(e, sec, Placement({}), raw), e, sec)
            rb = fill(linked_words(c, sec, Placement({}, c_funcs, e_funcs), raw), c, sec)
            res.sections[sec] = ("OK" if ra == rb else "OK by address", f"{e.section_size(sec)} bytes")
            continue
        first = next(i for i in range(max(len(a), len(b))) if i >= len(a) or i >= len(b) or a[i] != b[i])
        res.sections[sec] = ("DIFFERS", f"{e.section_size(sec)} vs {c.section_size(sec)} bytes,"
                                        f" first difference at 0x{first * 4:X}")
        res.unit.append(f"{sec} differs")
        if sec == ".rodata":
            for i in range(min(len(a), len(b))):
                if a[i] != b[i]:
                    for f in {function_at(a[i]), function_at(b[i])} - {None}:
                        why = f"its jump table differs (.rodata +0x{i * 4:X})"
                        if f in res.functions and not any(r.startswith("its jump table") for r in res.functions[f]):
                            res.functions[f].append(why)

    bad = [n for n in res.order if res.functions.get(n)]
    if bad:
        res.unit.insert(0, f"{len(bad)} function{'s' * (len(bad) > 1)} differ{'s' * (len(bad) == 1)}")
    return res


def c_data_sections(target: str, unit: str):
    """The data sections the C file provides: its `.rodata`/`.data`/`.sdata` subsegments in the target's YAML
    (`rodata`/`data` ones stay asm). None when the YAML has none for the unit (compare what is there)."""
    t = next(t for t in configure.TARGETS if t.name == target)
    secs, found = set(), False

    def walk(segs):
        nonlocal found
        for s in segs or []:
            if isinstance(s, dict):
                typ, name = s.get("type"), s.get("name")
                walk(s.get("subsegments"))
            elif isinstance(s, list) and len(s) >= 3:
                typ, name = s[1], s[2]
            else:
                continue
            if name == unit and typ in ("rodata", "data", "sdata", ".rodata", ".data", ".sdata"):
                found = True
                if typ.startswith("."):
                    secs.add(typ)

    walk(yaml.safe_load((ROOT / t.yaml).read_text()).get("segments"))
    return secs if found else None


def following_alignment(target: str, unit: str) -> dict:
    """Section -> the alignment the target's linker script gives what follows the C unit's section: N for a
    `. = ALIGN(N);` before the next input section (configure.py's align_overlay_sections and align_small_data), else
    the script's SUBALIGN(4). The original's asm ends with that fill (a zero word after an overlay object's last
    function, a string's padding), the C object without it."""
    t = next(t for t in configure.TARGETS if t.name == target)
    path = ROOT / configure.splat_paths(t)["ld_script_path"]
    if not path.exists():
        return {}
    lines = [ln.strip() for ln in path.read_text().splitlines()]
    out = {}
    for i, ln in enumerate(lines):
        m = re.fullmatch(rf"\S*/src/{re.escape(target)}/{re.escape(unit)}\.c\.o\((\.\w+)\);", ln)
        if not m:
            continue
        a = 4
        for nxt in lines[i + 1:]:
            if k := re.fullmatch(r"\. = ALIGN\((\d+)\);", nxt):
                a = max(a, int(k.group(1)))
            elif not re.fullmatch(r"[A-Za-z_]\w* = [^;]*;", nxt):  # past symbol assignments only
                break
        out[m.group(1)] = a
    return out


def disasm(obj: Path, func: str):
    """objdump's text of `func`'s instructions, each relocation's type and symbol appended."""
    r = run([str(OBJDUMP), "-drz", "-m", "mips:3000", f"--disassemble={func}", str(obj)])
    out = []
    for ln in r.stdout.splitlines():
        m = re.match(r"^\t+[0-9a-f]+: R_MIPS_(\w+)\t(\S+)$", ln)
        if m and out:
            out[-1] += f"  ; {m.group(1)} {m.group(2)}"
            continue
        m = re.match(r"^\s*([0-9a-f]+):\t([0-9a-f]{8}) \t(.*)$", ln)
        if m:
            out.append(" ".join(p.strip() for p in m.group(3).split("\t")))
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("unit")
    ap.add_argument("func", nargs="?")
    ap.add_argument("-t", "--target", default="main")
    ap.add_argument("-G", type=int)
    ap.add_argument("-V")
    ap.add_argument("--all", action="store_true", help="also list functions still in INCLUDE_ASM")
    ap.add_argument("-D", action="append", default=[], metavar="DEF", help="extra preprocessor define")
    args = ap.parse_args()

    src = f"src/{args.target}/{args.unit}.c"
    expected = ROOT / f"build/expected/{args.target}/{args.unit}.s.o"
    if not expected.exists():
        sys.exit(f"{expected} missing: run scripts/build.sh once")
    out = ROOT / f"build/unit_diff/{args.target}/{args.unit}.c.o"
    out.parent.mkdir(parents=True, exist_ok=True)
    cc = args.V or configure.CC_OVERRIDES.get(src, configure.DEFAULT_CC)
    g = args.G if args.G is not None else configure.g_for(src)
    r = run(["tools/cc_psx.sh", "-V", cc, "-G", str(g), *configure.cc_flags(src), *(f"-D{d}" for d in args.D),
             *configure.CC_INCLUDES.split(),
             src, "-o", str(out)])
    if r.returncode != 0:
        sys.exit(r.stdout + r.stderr)

    r = run([str(ROOT / "tools/bin/objdiff-cli"), "diff", "-1", str(expected), "-2", str(out), "-o", "-"])
    if r.returncode != 0:
        sys.exit(r.stderr)
    pct = {s["name"]: s.get("match_percent") for s in json.loads(r.stdout)["left"]["symbols"]
           if s.get("kind") == "SYMBOL_FUNCTION"}

    res = compare(expected, out, Resolver.for_target(args.target), map_bases(args.target, args.unit),
                  c_data_sections(args.target, args.unit), following_alignment(args.target, args.unit))
    ok = by_addr = done = 0
    still_asm = sum(1 for n in res.order if n in res.asm)
    for name in res.order:
        reasons, p = res.functions[name], pct.get(name)
        if name in res.asm:
            if reasons:  # the original's own code: a difference here is the comparison's, or the layout's
                print(f"  {name:24} asm, differs: {'; '.join(reasons)}")
            elif args.all:
                print(f"  {name:24} asm")
            continue
        done += 1
        if not reasons:
            ok += 1
            if p == 100.0:
                mark = "OK"
            else:
                mark, by_addr = "OK (by address)", by_addr + 1
        else:
            # objdiff's score, rounded down: never "100.00%" for a function that differs
            score = "" if p is None or p >= 100.0 else f"{math.floor(p * 100) / 100:.2f}%: "
            mark = score + "; ".join(reasons)
        print(f"  {name:24} {mark}")
    for sec, (status, detail) in res.sections.items():
        if status != "asm" or args.all:
            print(f"  {sec:24} {status} ({detail})" if status != "DIFFERS" else f"  {sec:24} DIFFERS: {detail}")
    verdict = ("the unit links to the original bytes" if res.links
               else "the unit does not link to the original bytes: " + "; ".join(res.unit))
    print(f"{args.unit} (gcc {cc}, -G{g}): {ok}/{done} C functions match"
          + (f" ({by_addr} by address)" if by_addr else "") + f", {still_asm} still asm; {verdict}")

    if args.func:
        if args.func not in res.words:
            sys.exit(f"{args.func}: {'; '.join(res.functions.get(args.func, ['not a function of the unit']))}")
        a, b = disasm(expected, args.func), disasm(out, args.func)
        wa, wb = res.words[args.func]
        w = max([len(x) for x in a] + [10])
        print(f"\n{'original':{w}}   C   (| differs once linked; ~ same once linked, other symbol or form)")
        for i in range(max(len(a), len(b))):
            x = a[i] if i < len(a) else ""
            y = b[i] if i < len(b) else ""
            same = i < len(wa) and i < len(wb) and wa[i] == wb[i]
            print(f"{x:{w}} {'  ' if same and x == y else ' ~' if same else ' |'} {y}")
    sys.exit(0 if res.links else 1)


if __name__ == "__main__":
    main()
