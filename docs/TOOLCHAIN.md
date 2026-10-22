# Toolchain: what built the original game

What the executable itself says about the SDK and the compiler, and what is still to be settled. The numbers below
come from `tools/disc_survey.py` and `tools/psyq_match.py` over `SLUS_007.42` (SHA-1 `3cb8f02a…`, dated 1999-03-01
on the disc).

## Evidence in the executable

| Evidence | Where | Meaning |
|---|---|---|
| `$Id: sys.c,v 1.140 1998/01/12 07:52:27 noda Exp yos $` | `.rodata` | libgpu `SYS.OBJ` |
| `$Id: bios.c,v 1.86 1997/03/28 07:42:42 makoto Exp yos $` | `.rodata` | libcd `BIOS.OBJ` |
| `$Id: intr.c,v 1.75 1997/02/07 09:00:36 makoto Exp $` | `.rodata` | libetc `INTR.OBJ` |
| `Library Programs (c) 1993-1997 Sony Computer Entertainment Inc., All Rights Reserved.` | `.rodata` | Psy-Q runtime banner |
| `2MBYTE.OBJ` crt0 at `0x80017758` (entry `0x80017760`): clears a block, reads the RAM size word, sets `$gp`, calls `InitHeap`-like code and then `main` | `.text` | SN Systems psylink startup |
| `.rodata` at `0x80010000`, before all `.text` | layout | psylink ordering: each object's `.rodata` in link order, then every `.text` |
| `$gp = 0x80097EA4`, the end of `.data`, set by crt0; no `$gp`-relative load, store or `addiu` anywhere in the code | crt0 / code | Everything built with `-G0` ("Compiler" below): no `.sdata`, no `.sbss` |
| libpress strings (`MDEC_rest:bad option`) | `OVERLAYS/OVERMOVE.BIN` | libpress is linked into the movie overlay, not the executable |
| `BASLUS-00742` / `RAMPAGE` | `OVERLAYS/OVERATTR.BIN` | The memory-card file header: the attract/save code is in that overlay |

The `$Id` dates bound the SDK from below (libgpu from January 1998). Psy-Q 4.3 and 4.4 are the releases of the game's
time (March 1999).

## Psy-Q libraries (signature match)

`tools/psyq_match.py extracted/disc/SLUS_007.42` (lab313ru/psx_psyq_signatures, Psy-Q 2.6–4.7):

- **Library span:** `0x80063F98`–`0x8007A684` (92 KB), after the game's code; crt0 (`2MBYTE.OBJ`, 196 bytes) at
  `0x80017758`, right before `main` at `0x8001781C`.
- **100 objects placed** (29 KB of the 92 KB span); 16 gaps inside the span total about 62 KB of library code the
  signature database does not know (the matcher reports each gap).
- **Version:** 98.5 % of the matched bytes are consistent with **Psy-Q 4.3**; 5 objects (`LIBCD SYS.OBJ`, `BIOS_2.OBJ`,
  `S_003/S_004/S_005`, 400 bytes in all) match only the 4.6/4.7 signatures, which points at a libcd newer than the
  rest (a patch release, or a 4.4 whose signatures the database lacks). To be settled by naming the gaps (issue
  "Psy-Q library identification").

| Library | Objects | Bytes |
|---|---|---|
| LIBSPU | 19 | 7,936 |
| LIBPAD | 4 | 6,208 |
| LIBC2 | 13 | 4,832 |
| LIBCD | 14 | 4,544 |
| LIBSN | 1 | 1,552 |
| LIBETC | 3 | 1,488 |
| LIBGTE | 6 | 1,136 |
| LIBCARD | 8 | 624 |
| LIBAPI | 21 | 352 |
| LIBMCRD | 1 | 272 |
| LIBGPU | 4 | 208 |
| crt0 `2MBYTE.OBJ` | 1 | 196 |
| LIBGS | 4 | 96 |
| LIBCOMB | 1 | 16 |

LIBGPU's 208 bytes cannot be all of it (its `sys.c` banner is in the image): most of LIBGPU, LIBGTE and LIBSND (if
any) are in the gaps. 7 placed objects are ambiguous between libraries (tiny byte-identical twins) and stay unnamed
until link facts settle them.

## Compiler: GCC 2.8.1 `-O2 -G0`

The game's code was built with **GCC 2.8.1 (or 2.8.0, which generates the same code) at `-O2`, with `-G0`**, through
ASPSX; the build uses old-gcc's `gcc-2.8.1-psx` with maspsx emulating ASPSX 2.80 (`tools/cc_psx.sh`). 2.8.1 is the
compiler of Psy-Q 4.3, the SDK the libraries point at; 2.8.0 is Psy-Q 4.1's.

The evidence is `tools/compiler_id.py`: m2c drafts of game functions taken from `asm/main/game.s` with no hand edits
(`--valid-syntax` plus `m2c_macros.h`), compiled with every GCC in `tools/gcc` (2.7.2, 2.8.0, 2.8.1, 2.91.66, 2.95.2)
at `-O2`, at `-G0` and `-G8`, and scored by objdiff against the original function. Natural C only: nothing the
permuter can force counts. A draft compiles identically on every compiler or not at all (its failures are m2c's,
the same for every column), so the exact matches per compiler are the measure; the mean score is secondary (a
draft's wrong types move it for every compiler).

| Run | Functions scored | 2.7.2 | 2.8.0 | 2.8.1 | 2.91.66 | 2.95.2 | Drafts that don't compile |
|---|---|---|---|---|---|---|---|
| defaults (150 selected, 4–139 instructions) | 146 | 3 (66.7 %) | 57 (88.2 %) | 57 (88.2 %) | 34 (85.7 %) | 36 (86.0 %) | 4 |
| `--max 400` | 389 | 12 (67.3 %) | 149 (88.6 %) | 149 (88.6 %) | 94 (84.5 %) | 104 (86.3 %) | 11 |
| `--max 400 --max-insns 300` (4–273 instructions) | 376 | 10 (65.6 %) | 155 (87.7 %) | 155 (87.7 %) | 94 (84.6 %) | 102 (85.6 %) | 24 |
| `--max 400 --no-exclude` (jump tables and `.rodata` users kept) | 382 | 9 (66.6 %) | 150 (87.6 %) | 150 (87.6 %) | 89 (84.5 %) | 97 (85.4 %) | 11 (and 7 m2c failures) |
| **the four runs together** | **948** | **26** | **384** | **384** | **227** | **250** | |

Each cell is the number of exact matches at `-G0` and, in parentheses, the mean score over the run. At `-G8` every
compiler matches fewer functions (2.8.x: 124 of the 948, every one of them also exact at `-G0`), and no function
matches at `-G8` only.

What separates the compilers, over the 948 functions:

| Matched exactly by | Functions |
|---|---|
| 2.8.0, 2.8.1, 2.91.66 and 2.95.2 | 230 |
| 2.8.0 and 2.8.1 only | 105 |
| 2.8.0, 2.8.1 and 2.95.2 | 25 |
| 2.7.2, 2.8.0 and 2.8.1 | 18 |
| all five | 5 |
| 2.7.2 only | 2 (`func_80063DF8`, `func_80063F48`: the last functions before the library span, library code by their compiler) |
| 2.91.66 or 2.95.2 but not 2.8.x | 0 |

2.8.0 and 2.8.1 score the same on every one of the 948 functions, at both `-G`. 134 of the 384 functions 2.8.x
matches are matched by neither 2.91.66 nor 2.95.2; the larger ones, where the difference is not a single
instruction:

| Function | Instructions | 2.7.2 | 2.8.x | 2.91.66 | 2.95.2 |
|---|---|---|---|---|---|
| `func_8001BECC` | 88 | 62.0 % | 100 % | 86.1 % | 94.6 % |
| `func_800309AC` | 49 | 96.7 % | 100 % | 71.9 % | 72.5 % |
| `func_8002D144` | 44 | 86.4 % | 100 % | 87.4 % | 89.1 % |
| `func_8004C528` | 41 | 85.6 % | 100 % | 92.0 % | 90.4 % |
| `func_80061774` | 38 | 90.1 % | 100 % | 87.3 % | 87.8 % |
| `func_800233E0` | 37 | 96.8 % | 100 % | 76.9 % | 93.4 % |
| `func_8004F370` | 37 | 98.4 % | 100 % | 90.7 % | 90.7 % |
| `func_80017A40` | 34 | 61.7 % | 100 % | 77.6 % | 74.7 % |
| `func_8002F5B0` | 32 | 81.5 % | 100 % | 89.2 % | 84.9 % |

The functions with jump tables or `.rodata` constants (102 of the 1,868; excluded by default because m2c drafts them
with the cases out of order or without the constants) change nothing: of the 7 the `--no-exclude` run scored, one
(`func_8002C814`) is exact on 2.8.x and 2.9x alike, the rest are below 100 % on every compiler.

### `-G0` everywhere

`$gp` is set to `0x80097EA4` by crt0 and then never used: the executable's code makes no `$gp`-relative load, store
or `addiu` at all. The "10 `$gp`-relative accesses" `tools/disc_survey.py` counts are words in `.rodata` and `.data`
that decode as such instructions, plus crt0's own `addiu $gp, $gp, 0x7EA4`. So every file of the executable was
compiled with `-G0` (`configure.py` `DEFAULT_G`), there is no `.sdata`/`.sbss` to speak of, and the `-G8` column of the
experiment only confirms it. The overlays are checked separately when they become targets.

### Reproducing

```sh
scripts/build.sh                                              # the split tree
tools/venv/bin/python tools/compiler_id.py                    # the defaults: 150 functions
tools/venv/bin/python tools/compiler_id.py --max 400
tools/venv/bin/python tools/compiler_id.py --max 400 --max-insns 300
tools/venv/bin/python tools/compiler_id.py --max 400 --no-exclude
```

Each run prints the table and writes `build/compiler_id/results.csv` (one row per function, compiler and `-G`) and
each function's draft and objects under `build/compiler_id/<function>/`. The exact matches are the first functions to
decompile once the code is split into files: their drafts are already matching C.

## Unknowns

- Whether the overlays' code was compiled like the executable's (their layout and load address:
  `DISC_LAYOUT.md` "Overlays").
