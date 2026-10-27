#!/usr/bin/env python3
"""tools/variant.py and tools/draft.py on a unit made up for the test (no game files; needs scripts/setup.sh's
toolchain). The "original" is a C file compiled with GCC 2.8.1 and again with 2.7.2; the unit under test has one
function of each form (C, INCLUDE_ASM of the original's words, a WIP block with its score comment, a K&R
definition). With each compiler: the unit as written links; `put` keeps C that matches and leaves the file alone
otherwise; `--wip` writes the block (score, note, INCLUDE_ASM) and the unit still links; `try` ranks the matching
variant first; `perm` finds the original's statement order and alternative. Then draft.py's context (definitions to
prototypes, K&R and __asm__ handled) and a typed m2c draft that names a struct field.

  tools/venv/bin/python tests/variant_test.py
"""
import re
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import draft  # noqa: E402
import unit_diff  # noqa: E402
import variant  # noqa: E402

W = ROOT / "build/tests/variant"  # not /tmp: tools/cc_psx.sh keeps its .m.s only outside /tmp
ASM = W.relative_to(ROOT) / "asm"

HEAD = """extern int D_a, D_b, D_c;
extern int D_tab[];
int krsum();
"""
ADD_ONE = """int add_one(int x) {
    return D_tab[x] + 1;
}
"""
TWICE = """int twice(int x) {
    return x * 2 + 1;
}
"""
PICK = """int pick(int a, int b) {
    if (a > b) {
        return a - b;
    }
    return b - a;
}
"""
SETBOTH = """void setboth(int x) {
    D_b = x + 1;
    D_tab[1] = 5;
    D_a = x;
    D_c = 3;
}
"""
KRSUM = """int krsum(a, b)
int a;
int b;
{
    return a - b;
}
"""
ORIGINAL = HEAD + "\n" + "\n".join([ADD_ONE, TWICE, PICK, SETBOTH, KRSUM])
INCLUDE_ASM = ('#define INCLUDE_ASM(FOLDER, NAME) __asm__(".section .text\\n.set noat\\n.set noreorder\\n'
               '.include \\"" FOLDER "/" #NAME ".s\\"\\n.set reorder\\n.set at\\n")\n')
PICK_WIP = PICK.replace("return b - a;", "return a - b;")
UNIT = (INCLUDE_ASM + HEAD + "\n" + ADD_ONE + "\n"
        + f'INCLUDE_ASM("{ASM}", twice);\n\n'
        + "/* 50.00%: the old note */\n#ifdef NON_MATCHING\n" + PICK_WIP
        + f'#else\nINCLUDE_ASM("{ASM}", pick);\n#endif\n\n'
        + SETBOTH + "\n" + KRSUM)

failed = 0


def check(ok: bool, what: str, detail: str = ""):
    global failed
    print(f"{'ok  ' if ok else 'FAIL'} {what}" + (f"\n       {detail}" if detail and not ok else ""))
    failed += not ok


def sh(cmd):
    r = subprocess.run([str(c) for c in cmd], capture_output=True, text=True, cwd=ROOT)
    if r.returncode:
        sys.exit(f"{' '.join(map(str, cmd))}:\n{r.stdout}{r.stderr}")


def asm_of(obj: Path, func: str, out: Path):
    """The original's words of `func` as a splat-style .s (the functions taken this way use no relocation)."""
    elf = unit_diff.Elf(obj)
    off, size = elf.functions()[func]
    text = elf.index[".text"]
    assert not [r for r in elf.relocs.get(text, []) if off <= r[0] < off + size], func
    words = elf.section_words(".text")[off // 4:(off + size) // 4]
    out.write_text(f".global {func}.NON_MATCHING\n{func}.NON_MATCHING:\n.global {func}\n.type {func}, @function\n"
                   f"{func}:\n" + "".join(f"    .word 0x{w:08X}\n" for w in words) + f".size {func}, . - {func}\n")


def run(cc: str):
    d = W / cc
    d.mkdir(parents=True)
    (d / "original.c").write_text(ORIGINAL)
    sh(["tools/cc_psx.sh", "-V", cc, d / "original.c", "-o", d / "original.o"])
    for f in ("twice", "pick"):
        asm_of(d / "original.o", f, ROOT / ASM / f"{f}.s")
    path = d / "unit.c"
    path.write_text(UNIT)
    checker = unit_diff.Checker("test", "unit", expected=d / "original.o", resolver=unit_diff.Resolver({}),
                                bases={}, c_sections=None, align={})
    unit = variant.Unit("test", "unit", path=path, cc=cc, g=0, flags=["-I."], checker=checker, work=d / "work")
    print(f"--- gcc {cc}")

    text = unit.text()
    kinds = {f: variant.find(text, f) for f in ("add_one", "twice", "pick", "setboth", "krsum")}
    check({f: r.kind for f, r in kinds.items()} == {"add_one": "c", "twice": "asm", "pick": "wip",
                                                     "setboth": "c", "krsum": "c"},
          "find: each form (C, INCLUDE_ASM, WIP block, K&R past its prototype)", str(kinds))
    check(kinds["pick"].c == PICK_WIP and kinds["pick"].note == "the old note", "find: the WIP's C and its note",
          repr(kinds["pick"]))
    check(kinds["krsum"].c == KRSUM, "find: the K&R definition's span", repr(kinds["krsum"].c))
    s = unit.score(text, "add_one", "base")
    check(s.match, "the unit as written links", str(s))

    def put(func, c, wip=False, note=None):
        region = variant.find(unit.text(), func)
        s = unit.score(variant.put_text(unit.text(), region, c), func, "put")
        return s, variant.keep(unit, func, region, c, s, wip, note)

    before = unit.text()
    s, what = put("twice", TWICE.replace("* 2", "* 3"))
    check(not s.match and s.reasons and unit.text() == before, "put: C that differs is scored and not kept",
          f"{s}; {what}")
    s, what = put("twice", TWICE)
    check(s.match and what == "kept as C" and variant.find(unit.text(), "twice").kind == "c",
          "put: an INCLUDE_ASM function's matching C is kept", f"{s}; {what}")
    s, what = put("pick", PICK_WIP.replace("a - b;\n}", "b + a;\n}"), wip=True)
    region = variant.find(unit.text(), "pick")
    block = unit.text()[region.start:region.end]
    pct = re.escape(s.percent())
    check(region.kind == "wip" and re.match(rf"#ifdef NON_MATCHING\n/\* {pct}: the old note \*/\n", block)
          and f'INCLUDE_ASM("{ASM}", pick);' in block and "50.00%" not in unit.text(),
          "put --wip: the block rewritten, the new score with the old note", block)
    nm = unit.compile(unit.text(), "nm", defines=("NON_MATCHING",))[2]
    unit.clean("nm")
    check(nm == 0 and unit.score(unit.text(), "add_one", "after").match,
          "put --wip: the unit links and the WIP compiles with -DNON_MATCHING")
    s, what = put("pick", PICK)
    check(s.match and "NON_MATCHING" not in unit.text() and "the old note" not in unit.text(),
          "put: a WIP's matching C replaces the block and its comment", f"{s}; {what}")

    region = variant.find(unit.text(), "krsum")
    variants = variant.split_variants(
        KRSUM.replace("a - b", "b - a") + "//--- ANSI\n" + "int krsum(int a, int b) {\n    return a + b;\n}\n"
        + "//---\n" + "int krsum(a, b) {\n    return a - ;\n}\n" + "//---\n" + KRSUM)
    rows = variant.score_many(unit, "krsum", region, list(enumerate(variants, 1)), 2)
    ranked = [n for n, _ in sorted(rows, key=lambda r: r[1].key(), reverse=True)]
    scores = dict(rows)
    check(len(variants) == 4 and ranked[0] == 4 and scores[4].match and ranked[-1] == 3 and scores[3].error,
          "try: the K&R variant that matches ranks first, the one that does not compile last",
          variant.table([(n, s, "") for n, s in rows], 9))

    tpl = variant.Template(SETBOTH.replace("    D_b = x + 1;\n    D_tab[1] = 5;\n    D_a = x;\n    D_c = 3;\n",
                                           "    //@P D_a = x;\n    D_tab[1] = 5; //@P\n    //@P D_b = x + 1;\n"
                                           "    //@G1 D_c = 4;\n    //@G1\n    //@G1 D_c = 3;\n"))
    first = tpl.candidate(0)[0]
    check(tpl.count() == 18 and "//@" not in first and "D_c = 4;" in first and "D_c = 3;" not in first,
          "perm: 3! orders x 3 alternatives (one empty), candidate 0 as written", f"{tpl.count()}: {first}")
    region = variant.find(unit.text(), "setboth")
    cands = [(i, tpl.candidate(i)[0]) for i in tpl.indices(100)]
    rows = variant.score_many(unit, "setboth", region, cands, 2)
    matches = [dict(cands)[i] for i, s in rows if s.match]
    check(SETBOTH in matches and all("D_c = 3;" in m and m.index("D_b") < m.index("D_a") for m in matches),
          "perm: the original's order and alternative match, no other alternative, no order with D_a first",
          str(matches))
    check(tpl.indices(5, seed=1)[0] == 0 and len(set(tpl.indices(5, seed=1))) == 5, "perm: the cap samples")


PP = """# 1 "x.c"
typedef struct Foo { int a; short b; struct Foo *next; } Foo;
extern Foo D_foo;
static int tbl[3] = { 1, 2, 3 };
int (*fns[2])(int) = { 0, 0 };
__asm__(".include \\"x.s\\"");
int ansi(Foo *f, int n) { if (n) { return f->a; } return "}{"[0]; }
# 12 "x.c"
static int kr(a, b)
    int a;
    Foo *b;
{
    return a + b->a;
}
int bare(x) { return x; }
enum E { E_A, E_B };
struct S { int (*cb)(int); };
short get_b(Foo *f);
void vfn(void) { }
"""
CONTEXT = """typedef struct Foo { int a; short b; struct Foo *next; } Foo;
extern Foo D_foo;
static int tbl[3] = { 1, 2, 3 };
int (*fns[2])(int) = { 0, 0 };
int ansi(Foo *f, int n);
static int kr();
int bare();
enum E { E_A, E_B };
struct S { int (*cb)(int); };
short get_b(Foo *f);
void vfn(void);
"""
GET_B = """.set noat
.set noreorder
glabel get_b
    lh $v0, 0x4($a0)
    jr $ra
    nop
"""


def drafts():
    print("--- draft.py")
    ctx = draft.declarations(PP)
    check(ctx == CONTEXT, "context: definitions become prototypes (K&R `T f();`), data and types stay, no __asm__",
          ctx)
    (W / "ctx.h").write_text(ctx)
    (W / "get_b.s").write_text(GET_B)
    rc, out = draft.m2c(W / "get_b.s", W / "ctx.h")
    check(rc == 0 and "->b" in out and "short get_b(Foo *" in out.replace("s16", "short"),
          "m2c with the context: the draft has the prototype's types and the field's name", out)


def main():
    shutil.rmtree(W, ignore_errors=True)
    (ROOT / ASM).mkdir(parents=True)
    for cc in ("2.8.1", "2.7.2"):
        run(cc)
    drafts()
    if failed:
        sys.exit(f"variant_test: {failed} check(s) wrong")
    print("variant_test: ok")


if __name__ == "__main__":
    main()
