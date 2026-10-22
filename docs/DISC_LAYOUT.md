# Disc layout and memory map

What is on the disc and where the executable puts things. Reproduce with `tools/venv/bin/python
tools/disc_survey.py` after `scripts/extract.sh`.

## The disc

*Rampage 2: Universal Tour* (USA), SLUS-00742, Midway Home Entertainment, 1999. Volume `SLUS-00742`, publisher
`MIDWAY HOME ENTERTAINMENT INC.`, creation date 1999-03-01. The retail disc has one data track and two audio tracks;
this project was started from a single-track dump (164,495 sectors), which `scripts/rebuild_iso.sh` rebuilds
bit-identical from `extracted/`. The data track holds 355 files (351 MB), no deeper than one directory:

| Directory | Files | Size | Contents |
|---|---|---|---|
| `/` | `SYSTEM.CNF`, `SLUS_007.42`, `CDPAD1-4.DAT` | 559 KB + 4 × 8.6 MB | The boot file (`BOOT = cdrom:\SLUS_007.42;1`, `TCB = 4`, `EVENT = 10`, `STACK = 801ffffc`), the executable, four padding files dated 1996 |
| `OVERLAYS/` | `OVERATTR.BIN` (72,220 B), `OVERMOVE.BIN` (74,652 B) | 143 KB | The two code overlays: the attract mode and memory-card screens (holds the save header `BASLUS-00742`), and the movie player (libpress) |
| `MISC/` | 24 | 95 MB | `FILE00.IXA` (92.5 MB, interleaved XA audio: the music), the monsters' `.SPB` sprite banks (`NEWRAT`, `NEWGRGE`, ... two per monster) and `.BIN` tables (`GEORGE.BIN`, `LIZZY.BIN`, ...), `GENERAL.SPT`, `SCORES.CMB` |
| `MISC2/` | 26 | 4.3 MB | Front end: `TITLE.CMB`, `MENU.CMB`, `INTRO.CMB`, `LEGAL.CMB`, the world maps (`*MAP.SPT`), `SELECT.SPB`, `JAIL.SPB`, the victory banks (`*VICTRY.SPB`), `BIGFONT.BIN`, `TEXT.BIN`, `WARNING.SPT` |
| `MOVIE/`, `SOUND/` | 18 + 14 | 120 MB + 34 MB | `.XAS` streams: the opening and news movies, the monsters' cutscenes, the publisher logos; `SOUND/MAIN.LCD` (450 KB), `RAMPAGE.WMD`, `RAMPAGE.WSD` (the sound bank) |
| `RACKS00/`–`RACKS14/` | 10 or 20 each | 2.5–5.6 MB each | The cities ("racks"): one `.CMB` (the level, ~520–590 KB) and one `.BIN` (1–3 KB, dated 1999-03-01 like the executable) per city, five or ten cities per directory, grouped by continent |
| `BONUS/` | 14 | 2.2 MB | The bonus stages, the same `.CMB` + `.BIN` pairs |

File formats (`.CMB`, `.SPB`, `.SPT`, `.BIN`, `.IXA`, `.XAS`, `.LCD`, `.WMD`, `.WSD`) are not documented yet; the code
that reads them will name them. By extension: 143 `.BIN`, 137 `.CMB`, 29 `.XAS`, 24 `.SPB`, 11 `.SPT`, 4 `.DAT`, one
each of `.IXA`, `.LCD`, `.WMD`, `.WSD`, `.CNF`.

## The executable

`SLUS_007.42`: a PS-X EXE of 559,104 bytes, SHA-1 `3cb8f02ac807c1cf74a94e5df19a03633a14d962`.

| Header field | Value |
|---|---|
| `pc0` (entry) | `0x80017760` (inside crt0 at `0x80017758`) |
| `gp0` | 0 (crt0 sets `$gp = 0x80097EA4`) |
| `t_addr`, `t_size` | `0x80010000`, `0x88000` (the image: `0x80010000`–`0x80098000`) |
| `d_*`, `b_*` | 0 (the header declares no data or bss) |
| `s_addr` | `0x801FFFF0` |
| marker | `Sony Computer Entertainment Inc. for North America area` |

The regions (`config/main.yaml`; the boundaries are the first split, to be refined with evidence):

| Address | Size | What |
|---|---|---|
| `0x80010000`–`0x80017758` | 30,552 | `.rodata` of every object, in link order (psylink puts them before all `.text`) |
| `0x80017758`–`0x8001781C` | 196 | crt0 (Psy-Q `2MBYTE.OBJ`): clears `0x800AA240`–`0x801FE208`, reads the RAM size word at `0x80017810` (`0x00200000`), sets `$sp = 0x80200000` and `$gp`, calls the heap setup at `0x80063A78` and `main` |
| `0x8001781C`–`0x80063F98` | 313,212 | The game's code, `main` first (1,868 functions as splat finds them) |
| `0x80063F98`–`0x8007A684` | 92,396 | The Psy-Q libraries (`docs/TOOLCHAIN.md`) |
| `0x8007A684`–`0x80098000` | 120,700 | `.data`, then the small data around `$gp` (`0x80097EA4`); the last non-zero word is at `0x80097E9C` |
| `0x80098000`– | | `.bss`: not in the file; its end is where the overlays or the heap begin (open) |

## Overlays

`OVERLAYS/OVERATTR.BIN` and `OVERLAYS/OVERMOVE.BIN` are headerless code images the executable loads over a fixed
address (open). `tools/disc_survey.py` lists the addresses each one's code references, from which the load address
follows: OVERATTR's references are mostly `0x800Axxxx` (and the top of RAM, `0x801Dxxxx`–`0x801Fxxxx`), OVERMOVE's
`0x8009xxxx` and `0x800Axxxx`. Each becomes a link unit of its own (`config/<name>.yaml`, a `Target` in `configure.py`,
`config/overlays.sha1`) once that is known, and links against the executable's symbols.
