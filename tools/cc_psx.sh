#!/usr/bin/env bash
# Compile one C file like the original toolchain: cpp -> cc1 -> maspsx -> GNU as.
# Used by build.ninja (configure.py), decomp-permuter and experiments, so all compile the same way.
#
# Usage: tools/cc_psx.sh [-V VERSION] [-G N] [-MD DEPFILE] [--data-in-c] [-E] [-I DIR|-D DEF ...] input.c -o output.o
#   -V   old-gcc version in tools/gcc/ (default: configure.py's DEFAULT_CC, 2.8.1: docs/TOOLCHAIN.md "Compiler");
#        maspsx emulates the ASPSX of the same Psy-Q
#   -G   small-data size for cc1 and maspsx (default 0)
#   -MD  write a make-style dependency file (headers and .include'd asm)
#   --data-in-c  the file defines its own .bss/.sbss (configure.py DATA_IN_C): no --use-comm-section
#   -E   preprocess only: cpp's output, with the build's flags, into the -o file (tools/draft.py's context)
# Intermediates are kept next to the output: <out>.i, <out>.s (cc1), <out>.m.s (maspsx), except for outputs under /tmp
# (decomp-permuter compiles every candidate to /tmp/permuterXXXX.o: kept files once filled the disk).
#
# Adapted from gascarcella/dw2003recomp's tools/cc_psx.sh (MIT; docs/THIRD_PARTY.md).
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
T="$ROOT/tools"

ver=2.8.1 g=0 dep="" in="" out="" pp_only=0 cpp_flags=() inc_flags=() comm=(--use-comm-section)
while [[ $# -gt 0 ]]; do
    case "$1" in
        -V) ver="$2"; shift 2 ;;
        -G) g="$2"; shift 2 ;;
        -G*) g="${1#-G}"; shift ;;
        -MD) dep="$2"; shift 2 ;;
        --data-in-c) comm=(); shift ;;
        -E) pp_only=1; shift ;;
        -o) out="$2"; shift 2 ;;
        -I) cpp_flags+=("-I$2"); inc_flags+=("-I$2"); shift 2 ;;
        -D) cpp_flags+=("-D$2"); shift 2 ;;
        -I*) cpp_flags+=("$1"); inc_flags+=("$1"); shift ;;
        -D*) cpp_flags+=("$1"); shift ;;
        -*) echo "cc_psx.sh: unknown option $1" >&2; exit 2 ;;
        *) in="$1"; shift ;;
    esac
done
[[ -n "$in" && -n "$out" ]] || { echo "usage: cc_psx.sh [-V ver] [-G n] [-MD dep] [-I..] in.c -o out.o" >&2; exit 2; }

# GCC version -> ASPSX version of the same Psy-Q release (decomp.me's table). 2.8.1 pairs with 2.80 rather than 2.79
# so that maspsx can take the address of a $gp variable (`addiu rX, $gp, %gp_rel(x)`, gp_allow_la); it changes
# nothing else, and the executable makes no $gp-relative access anyway (docs/TOOLCHAIN.md "Compiler").
case "$ver" in
    2.7.2) aspsx=2.56 ;; 2.8.0) aspsx=2.77 ;; 2.8.1) aspsx=2.80 ;;
    2.91.66) aspsx=2.81 ;; 2.95.2) aspsx=2.86 ;;
    *) echo "cc_psx.sh: unknown GCC version $ver" >&2; exit 2 ;;
esac
gcc="$T/gcc/$ver"
[[ -x "$gcc/cc1" ]] || { echo "cc_psx.sh: $gcc/cc1 missing (scripts/setup.sh gcc)" >&2; exit 1; }
cpp=("$gcc/cpp" -nostdinc -lang-c -D_LANGUAGE_C -D__GNUC__=2 "${cpp_flags[@]}" "$in")
if [[ $pp_only -eq 1 ]]; then
    exec "${cpp[@]}" "$out"
fi
case "$out" in
    /tmp/*) trap 'rm -f "$out.i" "$out.s" "$out.m.s"' EXIT ;;
esac

"${cpp[@]}" "$out.i"
"$gcc/cc1" -quiet -O2 -mips1 -mcpu=3000 -mgas -msoft-float -G"$g" "$out.i" -o "$out.s"
# --use-comm-section: C definitions without an initializer stay COMMON instead of getting storage in this object, so
# they resolve to the definitions in the data asm (a unit whose data is still asm) while maspsx still counts them as
# defined in this file for $gp. --data-in-c drops it: the object then holds its .bss/.sbss itself, in definition
# order. maspsx then makes a global's .sbss symbol local, so the globals (cc1's `.comm`, not `.lcomm`) get their
# .globl back. --expand-div: ASPSX expanded cc1's three-operand div/divu macros with the divide-by-zero check
# (bnez/break 7, plus the -1/0x80000000 overflow check, break 6, for div): every division by a variable in the
# executable has them.
"$T/venv/bin/python" "$T/ext/maspsx/maspsx.py" --aspsx-version="$aspsx" -G"$g" --expand-div "${comm[@]}" \
    < "$out.s" > "$out.m.s"
if [[ ${#comm[@]} -eq 0 ]]; then
    sed -n 's/^[[:space:]]*\.comm[[:space:]]\{1,\}\([A-Za-z_.$][A-Za-z0-9_.$]*\),.*/\t.globl\t\1/p' "$out.s" >> "$out.m.s"
fi
as_dep=()
[[ -n "$dep" ]] && as_dep=(--MD "$dep.as")
"$T/binutils/bin/mipsel-linux-gnu-as" -EL -march=r3000 -mtune=r3000 -no-pad-sections -G0 \
    "${inc_flags[@]}" "${as_dep[@]}" -o "$out" "$out.m.s"

if [[ -n "$dep" ]]; then
    # Headers from cpp's line markers + .include'd asm from as; one rule for ninja.
    {
        printf '%s:' "$out"
        sed -n 's/^# [0-9]* "\([^"<]*\)".*/\1/p' "$out.i" | sort -u | awk -v src="$in" '$0 != src {printf " %s", $0}'
        sed '1s/^[^:]*://' "$dep.as" | tr -d '\\\n' | tr ' ' '\n' | awk -v ms="$out.m.s" 'NF && $0 != ms {printf " %s", $0}'
        echo
    } > "$dep"
    rm -f "$dep.as"
fi
