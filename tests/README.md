# The checks

`scripts/test.sh` is the one entry point; CI (`.github/workflows/ci.yml`) and `scripts/ci_local.sh` (the same in
CI's Docker image) run the same steps. Tests never change the game's code: a check lives in `tests/`, `tools/` or
`scripts/`, never in `src/`.

| Check | What | Needs |
|---|---|---|
| Scripts and Python | `bash -n` over every script, `py_compile` over every tool and test | nothing |
| Workaround census | `tools/hacks.py`: every `FAKE:` has its reason, every `LOOP_BLOCK` its evidence class, no inline asm or `#if 0` in game code ([`docs/MATCHING.md`](../docs/MATCHING.md)) | nothing |
| Toolchain smoke test | `scripts/check_toolchain.sh`: a function through every old GCC, maspsx and as; m2c, objdiff, asm-differ, the permuter run | `scripts/setup.sh` |
| unit_diff's comparison | `tests/unit_diff_test.py`: `tools/unit_diff.py`'s check on a unit made up for the test: the C that links to an original in splat's style (an alias, a jump table on labels, a constant where the C has a relocation) passes, also against an original that ends with the zero fill up to the next object's `ALIGN(8)`; that fill not expected, or a non-zero word in its place, a longer function, swapped operands, another relocation target, another branch target, swapped jump-table entries, an extra function and another function order each fail | `scripts/setup.sh` |
| The variant scorer and the drafter | `tests/variant_test.py`: `tools/variant.py` on a unit made up for the test, its original compiled with GCC 2.8.1 and with 2.7.2, one function of each form (C, `INCLUDE_ASM`, a WIP block, a K&R definition): the unit as written links; `put` keeps matching C, leaves the file alone otherwise, and with `--wip` rewrites the block with the new score and the old note (the unit still links, the block compiles with `-DNON_MATCHING`); `try` ranks the matching variant first and a variant that does not compile last; `perm` finds the original's statement order and alternative; putting a function twice does not repeat the declarations above it; `-s` aligns a candidate with one store more on the original's instructions, its branch included; `--dump` gives each pseudo its priority in global-alloc's order, the pseudos crossing a call `s` registers and the variables their registers; with 2.8.1, `--cc1`: a function whose original was compiled with `-fno-schedule-insns2` matches only under that flag, and nothing is kept under it (`-k` and `--wip` refused). `tools/draft.py`'s context (definitions to prototypes, K&R, `__asm__`) and a typed m2c draft that names a struct field | `scripts/setup.sh` |
| The byte-identical build | `scripts/build.sh` (`--check`: from scratch): every output equals its `config/*.sha1` | the game files (`extracted/disc`) |

Planned, as issues: an emulator boot check of the rebuilt executable (PCSX-Redux, headless), and record/replay tests
once overlays and game logic are in C.
