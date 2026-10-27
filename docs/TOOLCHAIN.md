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

## Psy-Q libraries

The library code follows the game's: `0x80063FA8`–`0x8007A684` (91,868 bytes), with one library object before it,
the `InitHeap` stub at `0x80063A78` that crt0 calls, placed between two of the game's objects. The objects were
identified with `tools/psyq_match.py` over lab313ru/psx_psyq_signatures (the `.text` of every object of Psy-Q 2.6
to 4.7, relocated bytes masked): first whole objects (`psyq_match.py extracted/disc/SLUS_007.42`), then, for the
units that lists, function by function (`--functions`). `config/main.yaml` holds the result as one
`psyq/<library>/<object>` unit per object, `config/symbol_addrs.txt` the 242 function names.

**The linker dropped the library functions nothing references.** Most objects in the image are shorter than the
library's: libetc's `INTR.OBJ` holds 7 of its 10 entry points (no `StopCallback`, `RestartCallback`,
`GetIntrMask`), libapi's `COUNTER.OBJ` 3 of 5, libgpu's `SYS.OBJ` 12 of 33, libmcrd's `LIBMCRD.OBJ` 14 of 19. The
functions that remain keep the library's order and bytes, so an object is recognised function by function: each
version's signature is cut at its function labels (a slice runs to the next function label, static code included),
the slices are searched in the unit in label order, and a slice that fits nowhere is a dropped function. The unit
of dropping is an entry point with the static code that follows it: every function kept is called from the
executable or from an overlay (the overlays call `CdRead2`, the `St*` streaming functions, `MemCard*`, `strchr`,
`strcmp`), or is followed by static code that is (`SetDrawEnv`, `DrawOTag2`, `MemCardReadData`,
`MemCardWriteData`, `MemCardUnformat`, `PadInfoAct`, `_spu_FsetPCR`, `CD_set_test_parmnum`).

**Four pieces of the game's own code sit between the library objects** (`wess_spu`, `wess`, `wess_seq`,
`wess_trigger` in `config/main.yaml`: 27,292 bytes, 147 functions): the game's sound driver, WESS (the
Williams/Midway sound system), which calls `SpuSetKey`, `SpuSetVoiceAttr` and the rest of libspu and holds the
`SPSX` string. No signature of any version matches them. The linker pulled them from the game's own library in the
same passes as the Psy-Q objects, which is why they are interleaved; they belong to the game's code.

**Version: Psy-Q 4.3.** Every object is consistent with 4.3; six are consistent with 4.3 only (libcd's
`CDREAD.OBJ`, libpad's `PADPORTM`, `PADMAIN`, `PADSEQM` and `PADIF`, libmcrd's `LIBMCRD.OBJ`) and three more with
4.2–4.3 (libgpu's `SYS.OBJ`, libpad's `PADENTRY.OBJ` and `PADCMD.OBJ`). The whole-object match
reports five libcd hits consistent with 4.6/4.7 only (`SYS.OBJ`, `BIOS_2.OBJ`, `S_003`/`S_004`/`S_005`); those are
4.6's one-function objects matching functions that 4.3 keeps inside its `SYS.OBJ` and `BIOS.OBJ`, whose static code
is byte-identical to 4.3's and not to 4.4's or 4.5's. The `$Id` dates above (libgpu `sys.c` of January 1998) fit a
1998 release. One libds object is linked, `DSCB.OBJ` (`DsReadyCallback` and `DsDataCallback`), because libcd's
`StUnSetRing` calls them in its libds mode; nothing else of libds is present.

| Library | Objects | Bytes | Versions consistent with every object |
|---|---|---|---|
| LIBCD | 15 | 13,472 | 4.3 |
| LIBPAD | 7 | 11,792 | 4.3 |
| LIBSPU | 25 | 11,124 | 4.3–4.6 |
| LIBGPU | 6 | 10,176 | 4.2–4.3 |
| LIBMCRD | 3 | 6,676 | 4.3 |
| LIBC2 | 16 | 5,252 | 4.1–4.7 |
| LIBETC | 5 | 3,124 | 4.3–4.7 |
| LIBSN | 2 | 1,584 | 3.3–4.6 |
| LIBGTE | 6 | 1,136 | 4.1–4.7 |
| LIBCARD | 10 | 804 | 4.1–4.4 |
| LIBAPI | 28 | 708 | 4.1–4.7 |
| LIBDS | 1 | 56 | 4.0–4.5 |
| crt0 `2MBYTE.OBJ` | 1 | 196 | all |

124 objects, 65,904 bytes of library code (plus crt0). No libsnd, libpress (it is in `OVERMOVE.BIN`), libgs or
libmath object is linked; the game's sound runs on libspu and its own driver.

**Byte-identical twins**, settled from the callers and callees rather than the bytes:
- `PadStartCom` at `0x8006988C` (libpad `PADENTRY.OBJ`), not `PadChkVsync` or `PadStopCom`: it calls
  `_padStartCom`.
- `SpuWrite` at `0x8006B9F4` (`S_W.OBJ`), not `SpuRead` (`S_R.OBJ`): it calls `_spu_Fw`.
- `CdFlush`, `CdSync` and `CdReady` at `0x800673E0`, `0x80067400`, `0x80067420`: each calls its `CD_*` routine;
  `CdSyncCallback` and `CdReadyCallback` follow them in the object's order (`CdSetDebug` precedes `CdSync` in the
  library, so it is one of the dropped functions).
- `DsReadyCallback` at `0x80072B18`, not `DsSyncCallback` or `DsStartCallback`: `StUnSetRing` calls it where its
  libcd branch calls `CdReadyCallback`.
- `_bu_init` at `0x800793C4`: `C112.OBJ` exists in both libcard and libapi with the same bytes; it follows
  libcard's `INIT.OBJ` and is filed under libcard.
- The eight `funcEvSp*` handlers of libmcrd's `BIOS.OBJ` and the `_get_card_event`/`_chk_card_event` pairs are
  named in the library's order.
- Whole-object hits that were coincidences: the 16-byte `GsGetWorkBase` at `0x80063F98` and `0x8007A484` (a getter
  of a game variable, and libapi's `ReadInitPadFlag`), and `COMB_3.OBJ` at `0x80067108` (inside libgpu's `SYS.OBJ`).

**Not named:** the static functions of the objects (they stay `func_…`; some carry a name because an older version
of the library exported it, such as libgpu's `_addque` and `set_alarm`), and the five functions of libpad's
`PADIF.OBJ`, for which the signature database has no labels.

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

### The sound driver: GCC 2.7.2

The four pieces of the game's own code that sit between the Psy-Q objects (`wess_spu`, `wess`, `wess_seq`,
`wess_trigger`: the sound driver, `docs/DISC_LAYOUT.md` "The files") were built with **GCC 2.7.2**,
not 2.8.1: their stores to globals go through the assembler's macro form (`sh $v1, sym`, which assembles to a
`lui $at` pair), a form 2.8.x never emits because it splits every address itself, and over the experiment's drafts
2.7.2 matches 72 of their functions where 2.8.1 matches 32 (`wess`: 47 against 16, mean 89.5 % against
73.4 %). `configure.py`'s `CC_OVERRIDES` names them; `tools/cc_psx.sh` pairs 2.7.2 with ASPSX 2.56. The
controllers' vibration in `vibrate`, just before them, is 2.8.1: all 12 of its functions match with it.

### Division: the assembler's checks

cc1 writes a division by a variable as the three-operand `div`/`divu` macro, and ASPSX expanded it with the
divide-by-zero check (`bnez divisor` / `break 7`) and, for `div`, the overflow check (`-1` and `0x80000000`, `break 6`):
every such division in the executable has them, in both compilers' code. `tools/cc_psx.sh` runs maspsx with
`--expand-div` for that.

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

## The overlays

`OVERLAYS/OVERMOVE.BIN` carries the only library code outside the executable: Psy-Q libpress, as three objects
(`config/overmove.yaml`, named by `tools/psyq_match.py --raw --base 0x80097EA4 --functions --yaml
config/overmove.yaml`): `VLC.OBJ` (`DecDCTvlc` alone, `DecDCTvlcSize` dropped), `LIBPRESS.OBJ` (`DecDCTReset`,
`DecDCTin`, `DecDCTout`, `DecDCToutCallback` with its static helpers; `DecDCTGetEnv`, `DecDCTPutEnv`,
`DecDCTBufSize`, `DecDCTinSync`, `DecDCToutSync` and `DecDCTinCallback` dropped) and the VLC decoding tables, 70 KB
of data in `.text` with no function. The libpress code is consistent with Psy-Q 4.2–4.7 (`DecDCTvlc` with 4.3–4.7),
in line with the executable's 4.3. `OVERATTR.BIN` holds no library code; both overlays call the executable's library
functions by absolute address.

Both overlays were compiled like the executable. `tools/compiler_id.py --target overattr --rodata-start 0x80097EA4
--rodata-end 0x80098730` scores 72 functions: 8 exact with GCC 2.8.0 and 2.8.1, 7 with 2.95.2, 4 with 2.91.66, none
with 2.7.2, and `func_8009C7E4` matches 2.8.x only; `--target overmove --rodata-end 0x80097EF8` scores 8: 2 exact
with 2.8.x (`func_800A9CC0` with 2.8.x only), 1 with 2.9x. No `$gp`-relative access in either: `-G0`.
