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
| `$gp = 0x80097EA4`; 10 `$gp`-relative loads and stores in the whole image | crt0 / code | Almost everything built with `-G0`; a handful of small variables sit in `.sdata`/`.sbss` |
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

## Compiler: not settled yet

The working assumption is **GCC 2.8.1 `-O2 -G0`** through maspsx (ASPSX 2.80), the compiler of the same maintainer's
other PS1 project of this era and of most 1998–1999 Psy-Q games; `configure.py`'s `DEFAULT_CC` and `DEFAULT_G` say
so. It is unconfirmed until `tools/compiler_id.py` runs: m2c drafts of a few hundred game functions, compiled with
GCC 2.7.2, 2.8.0, 2.8.1, 2.91.66 and 2.95.2 at `-G0` and `-G8`, scored by objdiff against the original. Compilers are
scored on natural C only, never on what the permuter can force. `scripts/check_toolchain.sh` runs every one of them
through `tools/cc_psx.sh` as a smoke test.

## Unknowns

- The compiler and its version (above).
- The end of `.data` and the small-data sections around `$gp`; the `.bss` range (the header has no bss fields; crt0
  zeroes `0x800AA240`–`0x801FE208`, which looks like the heap rather than `.bss`).
- The overlays' load addresses and whether their code was compiled like the executable's.
