# The checks

`scripts/test.sh` is the one entry point; CI (`.github/workflows/ci.yml`) and `scripts/ci_local.sh` (the same in
CI's Docker image) run the same steps. Tests never change the game's code: a check lives in `tests/`, `tools/` or
`scripts/`, never in `src/`.

| Check | What | Needs |
|---|---|---|
| Scripts and Python | `bash -n` over every script, `py_compile` over every tool | nothing |
| Workaround census | `tools/hacks.py`: every `FAKE:` has its reason, every `LOOP_BLOCK` its evidence class, no inline asm or `#if 0` in game code ([`docs/MATCHING.md`](../docs/MATCHING.md)) | nothing |
| Toolchain smoke test | `scripts/check_toolchain.sh`: a function through every old GCC, maspsx and as; m2c, objdiff, asm-differ, the permuter run | `scripts/setup.sh` |
| The byte-identical build | `scripts/build.sh` (`--check`: from scratch): every output equals its `config/*.sha1` | the game files (`extracted/disc`) |

Planned, as issues: an emulator boot check of the rebuilt executable (PCSX-Redux, headless), and record/replay tests
once overlays and game logic are in C.
