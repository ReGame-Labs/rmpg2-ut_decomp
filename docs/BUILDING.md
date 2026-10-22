# Building

The goal is C source that rebuilds a **byte-identical** game executable with the original-era toolchain (an old GCC
through maspsx and GNU as; [`TOOLCHAIN.md`](TOOLCHAIN.md) has the evidence). Contributors: read
[`CONTRIBUTING.md`](CONTRIBUTING.md) too.

## Requirements

Linux x86_64 with git, Python 3.10+, make, gcc/g++, cmake, ninja, curl, xz, unzip. Everything else is built or
unpacked into `tools/` by the setup script, with no root access needed. You need your own disc image of *Rampage 2:
Universal Tour (USA)*, SLUS-00742, as a raw `.bin` (2352-byte sectors).

## Setup

```sh
cp tools/local.env.example tools/local.env   # set RMPG2_DISC_BIN to your disc image's .bin
scripts/setup.sh                             # mipsel binutils, mkpsxiso, Python venv, old GCCs, objdiff, decomp tools; links the disc into iso/
scripts/extract.sh                           # disc -> extracted/disc + extracted/rmpg2.xml
```

`scripts/setup.sh disc` checks the image's SHA-1 against the dump this project was started from (a single-track
dump; the retail disc has one data track and two audio tracks). Another dump of the same release works as long as its
`SLUS_007.42` and `OVERLAYS/*.BIN` are the same files: run `scripts/setup.sh --disc /path/to/your.bin` to link it
without the check, then `scripts/extract.sh`; the build checks the files themselves (`config/*.sha1`).

**Git worktrees.** A worktree has only tracked files. Run `scripts/worktree_init.sh` in a new worktree: it links the
main checkout's built tools and `tools/local.env`, and links the disc and extracts it (about a second, no rebuild).
`scripts/setup.sh` always installs tools into the main checkout and links them into worktrees.

## Build

```sh
scripts/build.sh            # split with splat, build with ninja, check every SHA-1 against config/*.sha1
scripts/build.sh --check    # the same from scratch (deletes asm/ and build/ first)
scripts/check_toolchain.sh  # smoke test of the compilers and diff tools (no disc needed)
scripts/rebuild_iso.sh      # rebuild the disc image from extracted/ and compare it to yours
```

Outputs: `build/SLUS_007.42`, `build/OVERATTR.BIN` and `build/OVERMOVE.BIN`, each checked byte-identical against the
original (`config/*.sha1`). Functions not yet decompiled are built from split assembly.

## Checks

```sh
scripts/test.sh             # the scripts parse, the Python compiles, the workaround census, the toolchain smoke test, the build
scripts/ci_local.sh         # the same inside CI's Docker image (ubuntu-24.04), before a push; --check builds from scratch
```

[`../tests/README.md`](../tests/README.md) describes them. CI runs them on every pull request and push to `main`
(`.github/workflows/ci.yml`); a pull request from a fork gets the disc-free checks only.
