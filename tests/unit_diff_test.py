#!/usr/bin/env python3
"""tools/unit_diff.py's comparison on a unit made up for the test (no game files; needs scripts/setup.sh's
toolchain). An "original" in splat's style (an alias, a jump table on .L labels, a constant where the C has a
relocation) against the C that links to its bytes, then C objects that differ in one way each: the comparison must
pass the first and fail every other, naming the function at fault.

  tools/venv/bin/python tests/unit_diff_test.py
"""
import re
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import unit_diff  # noqa: E402

AS = ROOT / "tools/binutils/bin/mipsel-linux-gnu-as"
W = ROOT / "build/tests/unit_diff"  # not /tmp: tools/cc_psx.sh keeps its .m.s only outside /tmp

ORIGINAL = """\
.set noreorder
.set noat
.text
.globl func_80010000
.type func_80010000, @function
func_80010000:
    lui $v0, %hi(D_80020000_alt)
    addiu $v0, $v0, %lo(D_80020000_alt)
    sll $a0, $a0, 2
    addu $a0, $a0, $v0
    lw $v0, 0x0($a0)
    jr $ra
    addiu $v0, $v0, 0x1
.size func_80010000, . - func_80010000

.globl func_8001001C
.type func_8001001C, @function
func_8001001C:
    addiu $sp, $sp, -0x18
    sltiu $v0, $a0, 0x5
    beqz $v0, .L8001007C
    sw $ra, 0x10($sp)
    lui $v0, %hi(jtbl_80011000)
    addiu $v0, $v0, %lo(jtbl_80011000)
    sll $v1, $a0, 2
    addu $v1, $v1, $v0
    lw $v0, 0x0($v1)
    nop
    jr $v0
    nop
.L8001004C:
    jal func_80010000
    addiu $a0, $zero, 0x1
    j .L80010080
    nop
.L8001005C:
    j .L80010080
    addiu $v0, $zero, 0x7
.L80010064:
    j .L80010080
    addiu $v0, $zero, 0x9
.L8001006C:
    j .L80010080
    addiu $v0, $zero, 0xB
.L80010074:
    j .L80010080
    addiu $v0, $zero, 0xD
.L8001007C:
    addu $v0, $zero, $zero
.L80010080:
    lw $ra, 0x10($sp)
    nop
    jr $ra
    addiu $sp, $sp, 0x18
.size func_8001001C, . - func_8001001C

.globl func_80010090
.type func_80010090, @function
func_80010090:
    lui $v0, 0x8002
    jr $ra
    addiu $v0, $v0, 0x4
.size func_80010090, . - func_80010090

.section .rodata
.globl jtbl_80011000
jtbl_80011000:
    .word .L8001004C, .L8001005C, .L80010064, .L8001006C, .L80010074
"""

F0 = """int func_80010000(int x) {
    return D_80020000[x] + 1;
}
"""
F1 = """int func_8001001C(int x) {
    switch (x) {
    case 0:
        return func_80010000(1);
    case 1:
        return 7;
    case 2:
        return 9;
    case 3:
        return 11;
    case 4:
        return 13;
    }
    return 0;
}
"""
F2 = """int *func_80010090(void) {
    return &D_80020000[1];
}
"""
C = "extern int D_80020000[];\n\n" + F0 + "\n" + F1 + "\n" + F2
# The original as an overlay's object ends: each section padded to 8 for the next object's `. = ALIGN(8);`, the
# zero words in its asm (a word after the last function, one after the jump table).
PADDED = ORIGINAL.replace(".size func_80010090, . - func_80010090\n",
                          ".size func_80010090, . - func_80010090\n    .word 0\n") + "    .word 0\n"
ALIGN8 = {".text": 8, ".rodata": 8}
RESOLVER = dict(exact={"D_80020000": 0x80020000}, aliases={"D_80020000_alt": ("D_80020000", 0)})


def sh(cmd):
    r = subprocess.run([str(c) for c in cmd], capture_output=True, text=True, cwd=ROOT)
    if r.returncode:
        sys.exit(f"{' '.join(map(str, cmd))}:\n{r.stdout}{r.stderr}")


def compile_c(name, text):
    (W / f"{name}.c").write_text(text)
    sh(["tools/cc_psx.sh", "-V", "2.8.1", W / f"{name}.c", "-o", W / f"{name}.o"])
    return W / f"{name}.o"


def edit_asm(name, base, old, new):
    """A C object whose compiler output (maspsx's) is edited: a difference C could produce, made exact."""
    text = (W / f"{base}.o.m.s").read_text()
    assert old in text, (name, old)
    (W / f"{name}.s").write_text(text.replace(old, new, 1))
    sh([AS, "-EL", "-march=r3000", "-mtune=r3000", "-no-pad-sections", "-G0", "-o", W / f"{name}.o", W / f"{name}.s"])
    return W / f"{name}.o"


def assemble(name, text):
    (W / f"{name}.s").write_text(text)
    sh([AS, "-EL", "-march=r3000", "-mtune=r3000", "-no-pad-sections", "-G0", "-o", W / f"{name}.o", W / f"{name}.s"])
    return W / f"{name}.o"


def main():
    shutil.rmtree(W, ignore_errors=True)
    W.mkdir(parents=True)
    original = assemble("original", ORIGINAL)
    padded = assemble("padded", PADDED)
    padded_word = assemble("padded_word", PADDED.replace("    .word 0\n", "    .word 1\n", 1))

    good = compile_c("good", C)
    cases = [
        # name, C object, the functions that must fail (None: the unit must link), why[, original, alignment]
        ("matching", good, None, "the alias, the jump table and the constant resolve to the original's words"),
        ("aligned", good, None, "an original that ends with the zero fill up to the next object's ALIGN(8)",
         padded, ALIGN8),
        ("unaligned", good, set(), "the same original where the next object follows at 4", padded, None),
        ("fillword", good, set(), "an original with a non-zero word where the fill would be", padded_word, ALIGN8),
        ("extra", compile_c("extra", C.replace(F1, "int func_extra(int x) {\n    return x + 2;\n}\n\n" + F1)),
         {"func_extra"}, "a function the original does not have, the others moved by it"),
        ("size", compile_c("size", C.replace("return D_80020000[x] + 1;", "return D_80020000[x] * 3 + 1;")),
         {"func_80010000"}, "a function one instruction longer, its first instructions the original's"),
        ("register", edit_asm("register", "good", "addu\t$4,$4,$2", "addu\t$4,$2,$4"),
         {"func_80010000"}, "the same instruction with its operands swapped"),
        ("reloc", edit_asm("reloc", "good", "addiu\t$2,$2,%lo(D_80020000) # low", "addiu\t$2,$2,%lo(D_80020000+8)"),
         {"func_80010000"}, "a relocation to another address"),
        ("branch", edit_asm("branch", "good", "beq\t$2,$0,$L3", "beq\t$2,$0,$L11"),
         {"func_8001001C"}, "a branch to another label"),
        ("jtbl", compile_c("jtbl", C.replace("case 2:", "case @:").replace("case 3:", "case 2:")
                                    .replace("case @:", "case 3:")),
         {"func_8001001C"}, "the same code, its jump table's entries swapped"),
        ("order", compile_c("order", "extern int D_80020000[];\n\n" + F2 + "\n" + F0 + "\n" + F1),
         set(), "every function the original's, in another order"),
    ]
    resolver = unit_diff.Resolver(**RESOLVER)
    failed = 0
    for name, obj, must_fail, why, *against in cases:
        orig, align = against or (original, None)
        res = unit_diff.compare(orig, obj, resolver, align=align)
        bad = {n for n, reasons in res.functions.items() if reasons}
        ok = res.links if must_fail is None else (not res.links and bad == must_fail)
        detail = "; ".join(f"{n}: {', '.join(r)}" for n, r in res.functions.items() if r) or "-"
        print(f"{'ok  ' if ok else 'FAIL'} {name:9} {why}\n       unit: {'links' if res.links else '; '.join(res.unit)}"
              f"\n       functions: {detail}")
        failed += not ok
    if failed:
        sys.exit(f"unit_diff_test: {failed} case(s) wrong")
    print(f"unit_diff_test: {len(cases)} cases ok")


if __name__ == "__main__":
    main()
