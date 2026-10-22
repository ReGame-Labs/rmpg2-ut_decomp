#!/usr/bin/env python3
"""Generate build.ninja and objdiff.json.

  tools/venv/bin/python configure.py             # split with splat, then write the files
  tools/venv/bin/python configure.py --no-split  # reuse the existing asm/ and linker scripts
  ninja                                          # build everything and check the SHA-1s

Each TARGET is one link unit (the executable now, the overlays later): a splat YAML, the linker script splat
writes, and the SHA-1 the output must have. The objects and their order come from splat's linker script; sources
map to objects by path:
    asm/<t>/X.s      -> build/<t>/asm/<t>/X.s.o
    assets/<t>/X.bin -> build/<t>/assets/<t>/X.bin.o
    src/<t>/X.c      -> build/<t>/src/<t>/X.c.o   (cpp -> cc1 -> maspsx -> as)

Adapted from gascarcella/dw2003recomp's configure.py (MIT; docs/THIRD_PARTY.md).
"""
import argparse
import json
import re
import subprocess
import sys
from dataclasses import dataclass
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parent
TOOLS = "tools"
PYTHON = f"{TOOLS}/venv/bin/python"
BINUTILS = f"{TOOLS}/binutils/bin/mipsel-linux-gnu-"
SPLAT = f"{TOOLS}/venv/bin/splat"


@dataclass
class Target:
    name: str          # short name, also the asm/src/build subdirectory
    yaml: str          # splat config
    output: str        # final binary
    sha1: str          # file with "<sha1>  <basename>"
    ld_extra: tuple = ()  # extra linker scripts (e.g. the EXE's symbols, for overlays)


# The executable's global symbols as a linker script, for the overlays to link against (their calls into the
# executable resolve to its own definitions). Made from the executable's ELF by ninja.
EXE_SYMS = "build/main/SLUS_007.42.syms.ld"
# Both overlays load at OVERLAY_BASE, between the executable's .data and its .bss (docs/DISC_LAYOUT.md "Overlays");
# the executable's symbols in that region are the overlays' own and are left out of EXE_SYMS.
OVERLAY_BASE, OVERLAY_END = 0x80097EA4, 0x800AA240

TARGETS = [
    # config/aliases.ld: extra names for addresses that have several (docs/MATCHING.md "How targets are configured").
    Target("main", "config/main.yaml", "build/SLUS_007.42", "config/SLUS_007.42.sha1", ("config/aliases.ld",)),
    # The overlays (docs/DISC_LAYOUT.md "Overlays"): headerless images loaded at OVERLAY_BASE, linked against the
    # executable's symbols (EXE_SYMS: the calls into the executable resolve to its own definitions).
    Target("overattr", "config/overattr.yaml", "build/OVERATTR.BIN", "config/OVERATTR.BIN.sha1", (EXE_SYMS,)),
    Target("overmove", "config/overmove.yaml", "build/OVERMOVE.BIN", "config/OVERMOVE.BIN.sha1", (EXE_SYMS,)),
]

# Compiler per C file; anything not listed uses DEFAULT_CC (tools/cc_psx.sh picks the matching ASPSX version for
# maspsx). GCC 2.8.1 -O2: the compiler-ID experiment's verdict (docs/TOOLCHAIN.md "Compiler"); 2.8.0 generates the
# same code, 2.8.1 is the one Psy-Q 4.3 shipped.
DEFAULT_CC = "2.8.1"
CC_OVERRIDES: dict[str, str] = {}      # "src/main/foo.c": "2.7.2"
# -G per target: the executable's code makes no $gp-relative access at all (docs/TOOLCHAIN.md), so every file is
# -G0. Exceptions by C path in G_OVERRIDES (none expected for the executable; the overlays are settled separately).
DEFAULT_G = {"main": 0}  # targets not listed: 0
G_OVERRIDES: dict[str, int] = {}


def g_for(src: str) -> int:
    """-G for a C file src/<target>/...: G_OVERRIDES, else its target's default."""
    return G_OVERRIDES.get(src, DEFAULT_G.get(Path(src).parts[1], 0))


# C files that define all their own data (every .data/.sdata/.sbss/.bss subsegment of theirs in the YAML is the C
# object's): compiled without maspsx's --use-comm-section, so their variables without an initializer get storage in
# the object. The other C files' tentative definitions stay COMMON and resolve to the data asm.
DATA_IN_C: set[str] = set()


def cc_flags(src: str) -> list[str]:
    """Extra tools/cc_psx.sh flags for a C file."""
    return ["--data-in-c"] if src in DATA_IN_C else []


AS_FLAGS = "-EL -march=r3000 -mtune=r3000 -no-pad-sections -G0 -Iinclude -Iinclude/asm_generated -I."
# C files go through tools/cc_psx.sh (cpp -> cc1 -O2 -> maspsx -> as), shared with the permuter.
CC_INCLUDES = "-Iinclude -Iinclude/asm_generated -I."

# Progress categories for objdiff: "game" (the game's code) and "sdk" (Psy-Q library code: crt0 and the library
# units under psyq/, excluded from progress). Unit names are <target>/<path under asm/<t>/ or src/<t>/>.
SDK_UNIT_PREFIXES = {"main": ("crt0", "psyq"), "overattr": ("psyq",), "overmove": ("psyq",)}


# The executable's names for the overlays' splat configs: config/symbol_addrs.txt with `absolute:True` added,
# because splat ignores user symbols outside the segments it is splitting otherwise.
EXE_NAMES_FOR_OVERLAYS = "build/exe_symbols.txt"


def write_exe_names():
    out = []
    for line in (ROOT / "config/symbol_addrs.txt").read_text().splitlines():
        m = re.match(r"^(\w+ = 0x[0-9A-Fa-f]+;)\s*(?://\s*(.*))?$", line.strip())
        if m:
            out.append(f"{m.group(1)} // {(m.group(2) or '').strip()} absolute:True".replace("//  ", "// "))
    path = ROOT / EXE_NAMES_FOR_OVERLAYS
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text("// Generated by configure.py from config/symbol_addrs.txt; do not edit.\n" + "\n".join(out) + "\n")


def split(t: Target):
    print(f"splat: {t.yaml}")
    subprocess.run([SPLAT, "split", t.yaml], cwd=ROOT, check=True, stdout=subprocess.DEVNULL)
    align_small_data(ROOT / splat_paths(t)["ld_script_path"])


def align_small_data(ld_script: Path):
    """psylink starts every game object's .sdata, .sbss and .bss 8-aligned (.data and .text only 4-aligned). splat's
    linker script (SUBALIGN(4)) gets `. = ALIGN(8);` in front of those sections of the executable's game units, C or
    asm (an asm subsegment already ends with the padding, so it is a no-op there). Psy-Q objects are left alone."""
    text = ld_script.read_text()
    pat = re.compile(r"^(\s*)(build/main/(?:src/main/\w+\.c|asm/main/data/\w+\.\w+\.s)\.o\(\.(?:sdata|sbss|bss)\);)$",
                     re.M)
    new = pat.sub(lambda m: f"{m.group(1)}. = ALIGN(8);\n{m.group(1)}{m.group(2)}", text)
    if new != text:
        ld_script.write_text(new)


def splat_paths(t: Target):
    opts = yaml.safe_load((ROOT / t.yaml).read_text())["options"]
    return {k: opts[k] for k in ("ld_script_path", "elf_path", "undefined_funcs_auto_path",
                                 "undefined_syms_auto_path", "asm_path", "src_path")}


def objects_from_ld(ld_script: Path):
    seen, objs = set(), []
    for m in re.finditer(r"^\s*(build/\S+?\.o)\(", ld_script.read_text(), re.M):
        if m.group(1) not in seen:
            seen.add(m.group(1))
            objs.append(m.group(1))
    return objs


def source_of(obj: str, t: Target):
    return obj[len(f"build/{t.name}/"):-len(".o")]   # asm/main/X.s, src/main/X.c, ...


class Ninja:
    def __init__(self):
        self.lines = []

    def w(self, s=""):
        self.lines.append(s)

    def rule(self, name, command, description, **kw):
        self.w(f"rule {name}")
        self.w(f"  command = {command}")
        self.w(f"  description = {description}")
        for k, v in kw.items():
            self.w(f"  {k} = {v}")
        self.w()

    def build(self, outs, rule, ins=(), implicit=(), variables=None):
        outs = " ".join(outs) if isinstance(outs, (list, tuple)) else outs
        ins = " ".join(ins) if isinstance(ins, (list, tuple)) else ins
        imp = (" | " + " ".join(implicit)) if implicit else ""
        self.w(f"build {outs}: {rule} {ins}{imp}".rstrip())
        for k, v in (variables or {}).items():
            self.w(f"  {k} = {v}")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--no-split", action="store_true", help="don't run splat")
    args = ap.parse_args()

    write_exe_names()
    if not args.no_split:
        for t in TARGETS:
            split(t)

    n = Ninja()
    n.w("# Generated by configure.py; do not edit.")
    n.w("ninja_required_version = 1.10")
    n.w()
    n.rule("as", f"{BINUTILS}as {AS_FLAGS} --MD $out.d -o $out $in",
           "as $in", depfile="$out.d", deps="gcc")
    n.rule("bin", f"{BINUTILS}objcopy -I binary -O elf32-tradlittlemips -B mips $in $out", "bin $in")
    n.rule("cc", f"tools/cc_psx.sh -V $cc -G $g $flags -MD $out.d {CC_INCLUDES} $in -o $out",
           "cc $in (gcc $cc)", depfile="$out.d", deps="gcc")
    n.rule("ld", f"{BINUTILS}ld -EL -nostdlib $ldscripts -Map $map -o $out", "ld $out")
    # truncate: the file's size is the config's last segment end; a section padded to 4 bytes would otherwise leave
    # extra bytes.
    n.rule("objcopy", f"{BINUTILS}objcopy -O binary $in $out && truncate -s $size $out", "objcopy $out")
    n.rule("sha1", f"echo \"$$(cut -d' ' -f1 $sha1)  $in\" | sha1sum --quiet -c - && touch $out",
           "sha1 $in")
    n.rule("syms", f"{BINUTILS}nm --defined-only -g $in | "
           f"awk '$$1 < \"{OVERLAY_BASE:08x}\" || $$1 >= \"{OVERLAY_END:08x}\" "
           f"{{ printf \"%s = 0x%s;\\n\", $$3, $$1 }}' > $out",
           "syms $out")
    n.rule("configure", f"{PYTHON} configure.py", "configure", generator="1")
    n.build(EXE_SYMS, "syms", "build/main/SLUS_007.42.elf")
    n.w()

    units = []
    finals = []
    expected_objs = []  # objdiff target objects for C units (built by default; objdiff doesn't build them)
    for t in TARGETS:
        p = splat_paths(t)
        ld_script = ROOT / p["ld_script_path"]
        if not ld_script.exists():
            sys.exit(f"{ld_script} missing: run without --no-split")
        objs = objects_from_ld(ld_script)
        n.w(f"# ---- {t.name} ({t.yaml}) ----")
        for obj in objs:
            src = source_of(obj, t)
            if src.endswith(".s"):
                n.build(obj, "as", src)
            elif src.endswith(".bin"):
                n.build(obj, "bin", src)
            elif src.endswith(".c"):
                cc = CC_OVERRIDES.get(src, DEFAULT_CC)
                n.build(obj, "cc", src, variables={"cc": cc, "g": g_for(src), "flags": " ".join(cc_flags(src))})
            else:
                sys.exit(f"don't know how to build {obj} (source {src})")

            # objdiff: every code unit. asm units only have a target (the original bytes); C units diff their object
            # against the assembled original asm of the same unit.
            stem = str(Path(*Path(src).with_suffix("").parts[2:]))  # asm/<t>/X.s -> X
            if src.endswith((".s", ".c")) and "/data/" not in src and stem != "header":
                sdk = stem.startswith(SDK_UNIT_PREFIXES.get(t.name, ()))
                cat = "sdk" if sdk else ("game" if t.name == "main" else "overlay")
                unit = {"name": f"{t.name}/{stem}", "metadata": {"progress_categories": [cat]}}
                if src.endswith(".c"):
                    expected = f"build/expected/{t.name}/{stem}.s.o"
                    full_asm = f"{p['asm_path']}/{stem}.s"
                    n.build(expected, "as", full_asm)
                    expected_objs.append(expected)
                    unit.update(target_path=expected, base_path=obj)
                    unit["metadata"]["source_path"] = src
                else:
                    unit.update(target_path=obj)
                units.append(unit)

        ldscripts = [p["ld_script_path"], p["undefined_syms_auto_path"],
                     p["undefined_funcs_auto_path"], *t.ld_extra]
        elf, mapf = p["elf_path"], p["elf_path"][:-len(".elf")] + ".map"
        n.build(elf, "ld", objs, implicit=ldscripts,
                variables={"ldscripts": " ".join(f"-T {s}" for s in ldscripts), "map": mapf})
        size = yaml.safe_load((ROOT / t.yaml).read_text())["segments"][-1][0]
        n.build(t.output, "objcopy", elf, variables={"size": str(size)})
        n.build(t.output + ".ok", "sha1", t.output, implicit=[t.sha1], variables={"sha1": t.sha1})
        finals.append(t.output + ".ok")
        n.w()

    deps = ["configure.py", "config/symbol_addrs.txt"] + [t.yaml for t in TARGETS]
    deps += [str(p.relative_to(ROOT)) for p in sorted((ROOT / "config").glob("*.symbols.txt"))]
    n.build("build.ninja", "configure", implicit=deps)
    n.w()
    n.w(f"default {' '.join(finals + expected_objs)}")
    (ROOT / "build.ninja").write_text("\n".join(n.lines) + "\n")

    objdiff = {
        "$schema": "https://raw.githubusercontent.com/encounter/objdiff/main/config.schema.json",
        "min_version": "3.0.0",
        "custom_make": "ninja",
        "build_target": False,
        "build_base": True,
        "watch_patterns": ["*.c", "*.h", "*.s", "*.inc"],
        "progress_categories": [{"id": "game", "name": "Game code (SLUS_007.42)"},
                                {"id": "overlay", "name": "Game code (overlays)"},
                                {"id": "sdk", "name": "Psy-Q SDK (not decompiled)"}],
        "units": units,
    }
    (ROOT / "objdiff.json").write_text(json.dumps(objdiff, indent=2) + "\n")
    print(f"wrote build.ninja ({len(TARGETS)} target(s)) and objdiff.json ({len(units)} units)")


if __name__ == "__main__":
    main()
