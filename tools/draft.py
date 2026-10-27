#!/usr/bin/env python3
"""Typed m2c drafts: m2c with the function's own unit as its context.

The context is the unit's .c preprocessed as the build preprocesses it (tools/cc_psx.sh -E with the unit's flags
from configure.py), reduced to declarations: each function definition becomes its prototype (a K&R one `T f();`),
the INCLUDE_ASM `__asm__` statements go. m2c then knows every type, struct field, global and prototype the unit
knows, so its draft names fields and types instead of guessing offsets.

  tools/venv/bin/python tools/draft.py func_8004874C            # print the draft
  tools/venv/bin/python tools/draft.py func_80099B54 -t overattr -- --no-andor   # m2c options after --
  tools/venv/bin/python tools/draft.py --sweep throw    # draft and score every INCLUDE_ASM function

--sweep compiles each draft in place of its INCLUDE_ASM in a copy of the unit (tools/variant.py's scoring: the
unit_diff comparison, m2c's macros header included) and prints a table; the unit is not edited. The drafts are
written to build/draft/<target>/<unit>/<func>.c, ready for `tools/variant.py put <func> <file>` once cleaned up
(committed C never uses m2c's M2C_ macros or its header).
"""
import argparse
import os
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import variant  # noqa: E402
from variant import skip_balanced, skip_literal  # noqa: E402

M2C = ROOT / "tools/ext/m2c"

# A K&R definition's head up to a parameter declaration: `T name(a, b) T a;` (not cut at that `;`).
KR_HEAD = re.compile(r"\s*[A-Za-z_][^;{}=]*?\b\w+\s*\(\s*\w+(?:\s*,\s*\w+)*\s*\)\s*[^;{}=()]*[A-Za-z_][^;{}=]*;"
                     r"(?:\s*[^;{}=]+;)*\s*$", re.S)
KR_DEF = re.compile(r"\s*(.*?\b\w+)\s*\(\s*\w+(?:\s*,\s*\w+)*\s*\)", re.S)


def prototype(head: str) -> str:
    """The declaration of a definition's head: `T f(T a)` as is, a K&R `T f(a, b) T a; T b;` as `T f();`."""
    head = head.strip()
    if head.endswith(")"):
        m = re.search(r"\(([^()]*)\)$", head)
        params = m.group(1).strip() if m else ""
        if params and params != "void" and re.fullmatch(r"\w+(?:\s*,\s*\w+)*", params) and "..." not in params:
            return head[:m.start()].rstrip() + "();"  # K&R without declarations: every parameter int
        return head + ";"
    m = KR_DEF.match(head)
    return (m.group(1) + "();") if m else ""


def outside_brackets(text: str) -> str:
    """`text` without what is inside (), [] and {}."""
    out, depth = [], 0
    for c in text:
        depth += c in "([{"
        if not depth:
            out.append(c)
        depth -= c in ")]}"
    return "".join(out)


def declarations(pp: str) -> str:
    """A preprocessed unit reduced to its declarations: definitions become prototypes, __asm__ statements go."""
    text = "\n".join(ln for ln in pp.split("\n") if not ln.lstrip().startswith("#"))
    out, start, i, n = [], 0, 0, len(text)
    while i < n:
        c = text[i]
        if c in "\"'":
            i = skip_literal(text, i)
        elif c in "([":
            i = skip_balanced(text, i)
        elif c == ";":
            chunk = text[start:i + 1]
            if not KR_HEAD.match(chunk):
                if not re.match(r"\s*(?:__asm__|asm)\b", chunk):
                    out.append(chunk.strip())
                start = i + 1
            i += 1
        elif c == "{":
            head = text[start:i]
            end = skip_balanced(text, i)
            if "(" in head and "=" not in outside_brackets(head) and not re.search(r"\b(?:struct|union|enum)\b[^()]*$",
                                                                                 head):
                out.append(prototype(head))
                start = end
            i = end
        else:
            i += 1
    return "\n".join(x for x in out if x) + "\n"


def context(unit: variant.Unit) -> Path:
    """The unit's declarations, written next to its other work files."""
    pp, log, rc = unit.compile(unit.text(), "ctx", preprocess=True)
    if rc:
        sys.exit(f"{unit.path}: the preprocessor failed:\n{log}")
    text = declarations(pp.read_text())
    unit.clean("ctx")
    path = unit.work / "ctx.h"
    path.parent.mkdir(parents=True, exist_ok=True)
    if not path.exists() or path.read_text() != text:
        path.write_text(text)
    return path


def asm_path(unit: variant.Unit, func: str) -> Path:
    region = variant.find(unit.text(), func)
    folder = (region.folder if region else None) or unit.folder
    path = ROOT / folder / f"{func}.s"
    if not path.exists():
        sys.exit(f"{path.relative_to(ROOT)} missing: m2c drafts a function still in INCLUDE_ASM"
                 " (configure.py writes its asm)")
    return path


def m2c(asm: Path, ctx: Path, extra=()):
    """m2c's draft: (status, text)."""
    r = subprocess.run([sys.executable, str(M2C / "m2c.py"), "--target", "mipsel-gcc-c", "--valid-syntax",
                        "--context", str(ctx), *extra, str(asm)], capture_output=True, text=True, cwd=ROOT)
    out = "\n".join(ln for ln in r.stdout.splitlines() if not ln.startswith("/* Warning: struct"))
    return r.returncode, out + "\n" if r.returncode == 0 else (r.stdout + r.stderr)


def m2c_error(out: str) -> str:
    """m2c's reason for a failure: the first line of its message."""
    lines = [ln.strip() for ln in out.splitlines() if ln.strip() and ln.strip() not in ("/*", "*/")]
    lines = [ln for ln in lines if not ln.startswith("Decompilation failure")]
    return lines[0] if lines else "m2c failed"


def sweep(unit: variant.Unit, jobs: int, extra=()):
    text = unit.text()
    funcs = [m.group(1) for m in re.finditer(r'^INCLUDE_ASM\(\s*"[^"]+"\s*,\s*(\w+)\s*\);', text, re.M)
             if variant.find(text, m.group(1)).kind == "asm"]
    if not funcs:
        sys.exit(f"{unit.path.relative_to(ROOT)}: no INCLUDE_ASM function outside WIP blocks")
    ctx = context(unit)
    out_dir = ROOT / "build/draft" / unit.target / unit.name
    out_dir.mkdir(parents=True, exist_ok=True)
    print(f"{unit.name}: {len(funcs)} INCLUDE_ASM functions, gcc {unit.cc} -G{unit.g}, -j {jobs}", flush=True)

    def one(func):
        asm = ROOT / variant.find(text, func).folder / f"{func}.s"
        size = sum(1 for ln in asm.read_text().splitlines() if re.match(r"\s*/\*\s*[0-9A-F]+ ", ln))
        rc, draft = m2c(asm, ctx, extra)
        if rc:
            return func, size, None, m2c_error(draft)
        (out_dir / f"{func}.c").write_text(draft)
        region = variant.find(text, func)
        scored = '#include "m2c_macros.h"\n' + draft
        s = unit.score(variant.put_text(text, region, scored), func, f"sw_{func}", includes=[str(M2C)])
        body = variant.find(draft, func)
        return func, size, s, "M2C macros" if body and "M2C_" in body.c else ""

    with ThreadPoolExecutor(max(1, jobs)) as ex:
        rows = list(ex.map(one, funcs))
    matched = 0
    for func, size, s, note in rows:
        if s is None:
            print(f"  {func:24} {size:5}  m2c failed: {note}")
            continue
        matched += s.match
        print(f"  {func:24} {size:5}  {s}" + (f"  ({note})" if note and s.error is None else ""))
    print(f"{matched}/{len(funcs)} drafts match as drafted; drafts in {out_dir.relative_to(ROOT)}/")


def main():
    argv = sys.argv[1:]
    extra = []
    if "--" in argv:
        k = argv.index("--")
        argv, extra = argv[:k], argv[k + 1:]
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("func", nargs="?")
    ap.add_argument("-t", "--target")
    ap.add_argument("-u", "--unit")
    ap.add_argument("--sweep", metavar="UNIT", help="draft and score every INCLUDE_ASM function of UNIT")
    ap.add_argument("-j", "--jobs", type=int, default=int(os.environ.get("RMPG2_JOBS") or 4))
    ap.add_argument("--context", action="store_true", help="print the context instead of the draft")
    a = ap.parse_args(argv)
    if a.sweep:
        target = a.target or "main"
        if not (ROOT / f"src/{target}/{a.sweep}.c").exists():
            sys.exit(f"src/{target}/{a.sweep}.c missing")
        return sweep(variant.Unit(target, a.sweep), a.jobs, extra)
    if not a.func:
        ap.error("a function, or --sweep UNIT")
    target, name = variant.locate(a.func, a.target, a.unit)
    unit = variant.Unit(target, name)
    ctx = context(unit)
    if a.context:
        print(ctx.read_text(), end="")
        return
    rc, out = m2c(asm_path(unit, a.func), ctx, extra)
    print(out, end="")
    sys.exit(rc)


if __name__ == "__main__":
    main()
