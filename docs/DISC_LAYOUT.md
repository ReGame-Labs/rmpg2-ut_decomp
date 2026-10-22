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

The regions (`config/main.yaml`; the code regions are the first split, to be refined with evidence):

| Address | Size | What |
|---|---|---|
| `0x80010000`–`0x80017758` | 30,552 | `.rodata` of every object, in link order (psylink puts them before all `.text`); the first 0x580 bytes are the file table's checksums (below) |
| `0x80017758`–`0x8001781C` | 196 | crt0 (Psy-Q `2MBYTE.OBJ`): clears `.bss`, reads `_ramsize` (2 MB, from its own table at `0x80017810`) and `_stacksize` (`0x600`, at `0x8007A70C`), sets `$sp = 0x80200000` and `$gp`, calls `InitHeap` (the BIOS call stub at `0x80063A78`) and `main` |
| `0x8001781C`–`0x80063FA8` | 313,228 | The game's code, `main` first, split into files ("The files" below); the `InitHeap` stub (16 bytes at `0x80063A78`, the first library object) sits between two of its objects |
| `0x80063FA8`–`0x8007A684` | 91,868 | The Psy-Q library objects (123 objects, 65,888 bytes; `docs/TOOLCHAIN.md`), with three pieces of the game's sound driver between them (25,980 bytes) |
| `0x8007A684`–`0x80097EA4` | 120,352 | `.data`; the last non-zero word is at `0x80097E9C`. No `.sdata` or `.sbss`: the code makes no `$gp`-relative access, and `$gp` is simply the end of `.data` |
| `0x80097EA4`–`0x80098000` | 348 | Zeros: the file is padded to a whole sector (`t_size` is a multiple of 0x800). The overlay region starts here |

## The files

The game's code is split into the files below (`config/main.yaml`, one `c` subsegment each with its `.rodata` and
`.data`; the evidence of every boundary is in the YAML's comments, following [`MATCHING.md`](MATCHING.md)
"Splitting a target into files"). The link order is the order of the `.text`: psylink placed each object's
`.rodata` and `.data` in that order, with data-only objects between the code files (the file table's checksums
first of all, the screens' tables between `game_800500EC` and `game_80057C94`, the overlay region's address after
`cdload`, and the tables pulled from a library after the Psy-Q objects). Twelve boundaries are proven by jump-table
parity, their position inside the window then taken from the `.data` pieces each side uses (weak where the window
has none); the others by a file's `.data` and its callers. Files are named after their first function until their
contents are understood; `cdload` is the CD file reader.

| File | `.text` | `.rodata` | `.data` | Contents |
|---|---|---|---|---|
| `game_8001781C` | `0x8001781C`–`0x8002A330` | `0x800105A8`–`0x80010784` | `0x8007A684`–`0x8007C934` | `main` and the start of the game: 352 functions |
| `game_8002A330` | `0x8002A330`–`0x80034590` | `0x80010784`–`0x800108D8` | `0x8007C934`–`0x8007D448` | 340 functions |
| `game_80034590` | `0x80034590`–`0x8003B568` | `0x800108D8`–`0x80010CB4` | `0x8007D448`–`0x8007DB60` | 141 functions |
| `game_8003B568` | `0x8003B568`–`0x8003CD08` | `0x80010CB4`–`0x80010D70` | `0x8007DB60`–`0x8007DE44` | 36 functions |
| `game_8003CD08` | `0x8003CD08`–`0x8004160C` | `0x80010D70`–`0x80010E64` | `0x8007DE44`–`0x8007E6C8` | 120 functions |
| `game_8004160C` | `0x8004160C`–`0x80043118` | `0x80010E64`–`0x80010F78` | `0x8007E6C8`–`0x8007ED64` | 82 functions; a run of 11-instruction stubs before `func_80042670` |
| `game_80043118` | `0x80043118`–`0x80043E28` | `0x80010F78`–`0x8001107C` |  | 49 functions, starting with a run of 11-instruction stubs; no `.data` of its own |
| `game_80043E28` | `0x80043E28`–`0x8004750C` | `0x8001107C`–`0x80011340` | `0x8007F1F4`–`0x8007F228` | 116 functions, starting with a run of 11-instruction stubs |
| `game_8004750C` | `0x8004750C`–`0x8004C064` | `0x80011340`–`0x800113FC` | `0x8007F228`–`0x8007F680` | 73 functions |
| `game_8004C064` | `0x8004C064`–`0x8004E574` | `0x800113FC`–`0x800114E0` | `0x8007F680`–`0x8007F710` | 79 functions |
| `game_8004E574` | `0x8004E574`–`0x800500EC` | `0x800114E0`–`0x80011534` | `0x8007F710`–`0x8007F8FC` | 58 functions |
| `game_800500EC` | `0x800500EC`–`0x80057C94` | `0x80011534`–`0x80011594` | `0x8007F8FC`–`0x8007FC84` | the last file whose `.data` precedes the screens' tables |
| `game_80057C94` | `0x80057C94`–`0x8005D198` | `0x80011594`–`0x800115D8` | `0x8008434C`–`0x80085264` | the first file whose `.data` follows the screens' tables; 150 small tables, one per function |
| `game_8005D198` | `0x8005D198`–`0x80060F3C` | `0x800115D8`–`0x8001169C` |  | 38 functions; uses the config tables `D_8008427C`–`D_8008433C` |
| `cdload` | `0x80060F3C`–`0x800633EC` | `0x80016A90`–`0x80016AC8` | `0x80085264`–`0x80085328` | the CD file reader and the overlay loader (`cdload_read_file`, `cdload_load_overlay`); `func_800619A4`–`func_80062868` and the stream reader `func_80062C10`–`func_800632E8` may be files of their own |
| `game_800633EC` | `0x800633EC`–`0x80063A78` |  | `0x80085328`–`0x800853C0` | the sound setup, before the `InitHeap` stub |
| `game_80063A88` | `0x80063A88`–`0x80063FA8` |  | `0x800853C0`–`0x800853F4` | the SPU setup, between the first two library objects |
| `game_8006BB14` | `0x8006BB14`–`0x80070914` |  |  | the sound driver (the `SPSX` string), between library objects |
| `game_80076C8C` | `0x80076C8C`–`0x800783C0` |  |  | more of the sound driver |
| `game_80078A40` | `0x80078A40`–`0x80078A88` |  |  | one sound-driver function |

The `.rodata` between the files' pieces holds data-only objects: `0x80010000`–`0x800105A8` the file table's
checksums, `0x8001169C`–`0x80016A90` const tables and strings used from `.data` and from code all over,
`0x80016AC8`–`0x80017758` the overlay region's address (twice, `D_80016AC8` and `D_80016ACC`), `D_80016AD0` and
the libraries' `.rodata`. The `.data` outside the files: `0x8007ED64`–`0x8007F1F4` and `0x8007FC84`–`0x8008434C`
the screens' tables (500-byte records with 16-byte descriptors) and the config tables `D_8008427C`–`D_8008433C`,
`0x800853F4`–`0x800888DC` the Psy-Q libraries' `.data` in link order, `0x800888DC`–`0x80097EA4` the tables linked
after the libraries, the file table among them. `.bss` stays one unit: uninitialised globals are COMMON symbols,
placed by the linker in an order of its own.

## Memory map

| Address | Size | What |
|---|---|---|
| `0x80010000`–`0x80098000` | 557,056 | The executable's image, above |
| `0x80097EA4`–`0x800AA240` | 74,652 | The overlay region: `OVERATTR.BIN`, `OVERMOVE.BIN` or a city's `.BIN` table, one at a time (below). Sized for the larger overlay: `OVERMOVE.BIN` ends exactly where `.bss` starts |
| `0x800AA240`–`0x801FE208` | 1,392,584 | `.bss`, cleared by crt0; the code references `0x800AA240`–`0x801FE1C8` and nothing between the overlay region and it. Not in the file (`config/main.yaml`'s `bss` segment) |
| `0x801FE20C`–`0x801FFA04` | 6,136 | The Psy-Q heap: `InitHeap(_end + 4, _ramsize - _stacksize - _end)` |
| `0x801FFA00`–`0x80200000` | 1,536 | `_stacksize` below the initial `$sp = 0x80200000` (`SYSTEM.CNF` says `STACK = 801ffffc`; the stack grows down through the heap's space when it needs more) |

`tools/disc_survey.py` ("memory map") checks the ranges against crt0 and the addresses the code builds with
`lui`/`addiu` pairs.

## Overlays

`OVERLAYS/OVERATTR.BIN` (72,220 bytes: the attract mode, the credits and the memory-card screens; it holds the save
header `BASLUS-00742`) and `OVERLAYS/OVERMOVE.BIN` (74,652 bytes: the movie player, with libpress) are headerless
images that both load at **`0x80097EA4`**, right after `.data`, into the region `0x80097EA4`–`0x800AA240`. The
executable loads one at a time: it reads the file into a buffer (the pointer at `D_801E1C78`) through the file table
below and copies it to the region (`cdload_load_overlay`: `0` for `OVERATTR.BIN`, `1` for `OVERMOVE.BIN`, from the
index table `D_80085274` = `{0x52, 0x53}`; `D_80085278` remembers which one is loaded). A second loader
(`cdload_load_city_table`) puts a city's `.BIN` table (`RACKS*/`, `BONUS/`: 1–3 KB of data, not code) in the same
region. The load address is a constant in `.rodata` (`0x80016AC8` and `0x80016ACC`, one per loader).

Evidence for the address: with it, `OVERMOVE.BIN` ends exactly at the start of `.bss` (`0x800AA240`); the
executable's `.data` holds 1,670 pointers into `0x80097EA8`–`0x80098AD0`, which are `OVERATTR.BIN`'s strings
(`0x80098310` is `SAVING GAME`); and the addresses each overlay's code builds land inside itself, in the executable
or in `.bss` (`tools/disc_survey.py` "overlays").

The executable and the overlays were linked together, as psylink overlay groups: the executable calls overlay
functions by absolute address (`jal` to 13 addresses in the region, `func_800A9890` in `OVERMOVE.BIN` eight times,
with a movie number) and reads and writes overlay variables (`D_800A9220`, `D_800A9840`, `D_800A98B8`, ...) and
tables (`D_800A5DD8`, ...); the overlays call the executable's functions (`OVERATTR.BIN` the memory-card and screen
code, `OVERMOVE.BIN` the CD streaming and `func_80063DF8`) and use its `.bss`. There is no entry table: each
overlay's symbols have fixed addresses.

Each overlay is a link unit of its own (`config/overattr.yaml`, `config/overmove.yaml`; a `Target` in
`configure.py`; `config/OVERATTR.BIN.sha1`, `config/OVERMOVE.BIN.sha1`). It links against the executable's symbols
(`build/main/SLUS_007.42.syms.ld`, made from the executable's ELF without the overlay region) so its calls into the
executable resolve to the executable's own definitions; splat gets the executable's names from
`build/exe_symbols.txt`, written by `configure.py` from `config/symbol_addrs.txt`. The overlay's own names are in
`config/<overlay>.symbols.txt`. Both were compiled like the executable, GCC 2.8.1 `-O2 -G0`
([`TOOLCHAIN.md`](TOOLCHAIN.md) "The overlays").

| Overlay | `.rodata` | `.text` | `.data` and `.bss` |
|---|---|---|---|
| `OVERATTR.BIN` | `0x80097EA4`–`0x80098730`: the save header, the credits' and the memory-card screens' strings, nine jump tables | `0x80098730`–`0x800A3360`: 108 functions, one file (`overattr`) until the evidence says otherwise (its jump tables share one parity, the string users run in text order) | `0x800A3360`–`0x800A92A4` `.data`, then zeros to the file's end `0x800A98C0`: its `.bss`, inside the file. The file table says 72,244 bytes, 24 more than the file: the loader copies that much, so the image in memory extends 24 bytes past the file's last word |
| `OVERMOVE.BIN` | `0x80097EA4`–`0x80097EF8`: libpress's strings (`MDEC_rest`, `MDEC_in_sync`, ...) | `0x80097EF8`–`0x800AA0EC`: libpress first (`psyq/libpress/vlc`: `DecDCTvlc`; `psyq/libpress/libpress`: `DecDCTReset`, `DecDCTin`, `DecDCTout`, `DecDCToutCallback` and its static helpers; `psyq/libpress/vlctbl`: the VLC decoding tables, 70 KB of data in `.text`, `0x8009870C`–`0x800A9890`), then the game's movie player (`overmove`, 9 functions from `0x800A9890`) | `0x800AA0EC`–`0x800AA240`: the movie table and the player's state |

No other library code is in the overlays: `OVERATTR.BIN` calls the executable's `MemCard*`, `strchr`, `strcmp` and
`sprintf`; `OVERMOVE.BIN` the executable's `CdRead2`, the `St*` streaming functions, `DMACallback`, `ResetCallback`
and `printf`.

## The file table

The executable never opens a file by name. It holds a table of the data track's files in disc order: a `CdlLOC`
(BCD minute, second, sector, track) per file at `D_80089820`, the sizes at `D_80089DA0` and a checksum per file
(the exclusive-or of its words, the tail zero-padded to a word) at `0x80010000`, the first 0x580 bytes of
`.rodata`. Entry `n` is the `n`-th file on the disc after `SYSTEM.CNF` and the executable (0 = `MISC/FILE00.IXA`,
82 and 83 = the overlays, 84 = `RACKS00/SALTLAKE.BIN`, 347 = `BONUS/BONUSGRU.CMB`); 348 of the 352 entries are
used, and the `CDPAD*.DAT` padding files are not in it. `tools/disc_survey.py` ("file table") checks the sizes
against the extracted files.

The reader (`func_8006118C(index, buffer)`) sets double speed (`CdlSetmode`), seeks to the entry (`CdlSetloc`),
reads `(size + 0x7FF) / 0x800` sectors (`CdRead`, waiting on `CdReadSync`), checksums the buffer against the table
and retries up to five times, re-initialising the drive on failure; it returns the size. Streams (`FILE00.IXA`,
the `.XAS` movies) are in the table with the placeholder checksum `0x2032B3CC`: they are played, not read.
