# Third-party code and data

Every file or snippet copied or closely adapted from another project gets an entry here **when it's borrowed**
(MIT/BSD require keeping the copyright notice).

| What (our path) | Source project @ commit | Their path | License | Notes |
|---|---|---|---|---|
| The build and tooling scaffold: `scripts/setup.sh`, `scripts/build.sh`, `scripts/extract.sh`, `scripts/rebuild_iso.sh`, `scripts/check_toolchain.sh`, `scripts/worktree_init.sh`, `tools/cc_psx.sh`, `tools/permuter_prelude.inc`, `configure.py`, `diff_settings.py`, `permuter_settings.toml`, `tools/psyq_match.py`, `tools/compiler_id.py`, `tools/disc_survey.py`, `tools/progress.py`, `tools/unit_diff.py`, `tools/split_case_sizes.py`, `tools/hacks.py`, `config/main.yaml`'s options, `include/common.h`, `.github/`, the structure of `docs/MATCHING.md` and the C patterns in it | gascarcella/dw2003recomp @ `main` (2026-10-21) | the same paths | MIT (Copyright (c) 2026 Gabriel Scarcella) | The same maintainer's PS1 decompilation of Digimon World 2003. Adapted: the game's names, addresses and targets replaced; the overlay tiers, the port and the reference-test layers removed. The C patterns in MATCHING.md were found on GCC 2.8.1 code and hold here if the compiler identification confirms 2.8.x. |
| *(no code)* The idea of a CI census of the matching workarounds (`tools/hacks.py`) | ReGame-Labs/dw3_decomp | `tools/hacks.py` | MIT (Copyright (c) 2026 juandav) | Idea only, through dw2003recomp's tool. |
| *(no code)* The structure of the sound driver (`src/main/game_8006BB14.c`, `game_80076C8C.c`, `game_80063A88.c`): WESS, the Williams/Midway sound system | Erick194/PSXDOOM-RE | its WESS sources | GPL-3.0 | Consulted to recognise the driver (the module and sequence formats, the command table's order); nothing is copied: the C and the names are written from this game's code. |
| Psy-Q library signatures (not vendored: `scripts/setup.sh ext` clones them into `tools/ext/psyq-sigs`; `tools/psyq_match.py` reads them) | lab313ru/psx_psyq_signatures @ `e9e46e7` | `*/*.json` | MIT | Used to identify and name library code; nothing is copied into the repository. |

Tools used but not vendored (installed by `scripts/setup.sh`: binutils, mkpsxiso, old-gcc, objdiff, maspsx, m2c,
asm-differ, decomp-permuter, splat) don't need entries.
