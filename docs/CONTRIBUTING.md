# Contributing

Thanks for wanting to help. This page covers what you need before you open a pull request. The project's background
is in the [README](../README.md).

## Ground rules

- **Never commit game data.** Nothing from the disc: no BIN/ISO, extracted files, split assembly (`asm/`), assets,
  textures, audio, BIOS, and no Psy-Q/SDK files. The repository is code only; everyone supplies their own disc. Check
  `git status` before you commit.
- **The matching build must stay byte-identical.** `SLUS_007.42` (and every overlay once it is a target) must still
  rebuild to the original SHA-1. A change that breaks it can't be merged.
- **USA release only** (SLUS-00742). Anything you borrow from another project must be recorded in
  [`THIRD_PARTY.md`](THIRD_PARTY.md) in the same pull request.
- **Don't decompile Psy-Q library functions.** They are identified by signature, named with Sony's names and stay as
  split assembly. No SDK header is used: the interface the game calls is declared in `include/psyq/`.
- By contributing you agree that your work is released under the project's [MIT licence](../LICENSE).

## What you can work on

- **Open issues**, in particular those labelled
  [`good first issue`](https://github.com/ReGame-Labs/rmpg2-ut_decomp/labels/good%20first%20issue) or
  [`help wanted`](https://github.com/ReGame-Labs/rmpg2-ut_decomp/labels/help%20wanted).
- **Matching functions** ([`PROGRESS.md`](PROGRESS.md); `INCLUDE_ASM` in `src/`).
- **Names and types:** most functions and data are still `func_…`/`D_…`.
- **File formats** (`.CMB`, `.SPB`, `.SPT`, `.IXA`, ...): documenting one helps name the code that reads it.

For anything bigger than a small fix, open an issue (or comment on an existing one) first, so we can agree on the
approach before you spend time on it.

## Getting set up

Follow [`BUILDING.md`](BUILDING.md): `tools/local.env` pointing at your disc, `scripts/setup.sh`,
`scripts/extract.sh`, then `scripts/build.sh`. Everything installs into `tools/`; no root access is needed. If you
work in a git worktree, run `scripts/worktree_init.sh` in it first.

## Making a change

### Decompilation (matching C)

The workflow, the tools (splat, objdiff, asm-differ, decomp-permuter, m2c) and the C patterns that make this compiler
match are in [`MATCHING.md`](MATCHING.md). In short:

- A function is **matching** when it compiles from C and the full build is byte-identical. Until then it stays
  `INCLUDE_ASM`; work-in-progress C goes under `#ifdef NON_MATCHING` and must still compile with `-DNON_MATCHING`.
- **Naming:** game symbols are `<module>_<verb>_<noun>` in snake_case, with the module prefix being the source file's
  name (`src/main/cdload.c` → `cdload_read_file`); types are PascalCase, constants `MODULE_UPPER_SNAKE`, unknown
  fields `unk_1C`. Unnamed symbols keep splat's defaults (`func_8001xxxx`, `D_8001xxxx`). Name only what you
  understand.
- New names go in `config/symbol_addrs.txt` (the executable) or `config/<overlay>.symbols.txt` (overlays).
- A forced match (`FAKE:`) or a `LOOP_BLOCK` is a last resort and carries its reason in a comment; `tools/hacks.py`
  checks that in CI.

### Documentation

`docs/` holds reference documentation only: how things are and why. Plans and problems go in issues.

## Checks before a pull request

CI on a pull request from a fork has **no game files**, so it can only build the toolchain and run the disc-free
checks. Please run the rest yourself and say so in the pull request:

```sh
scripts/test.sh --check     # the checks and the byte-identical build from scratch
scripts/ci_local.sh --check # the same in CI's Docker image, if you have Docker
```

## Opening a pull request

- Branch from `main`, keep the pull request focused on one thing, and write commit messages that say what changed and
  why.
- Fill in the [pull request template](../.github/PULL_REQUEST_TEMPLATE.md): what changed, how you tested it, and the
  checklist.
- Update progress with `tools/venv/bin/python tools/progress.py --readme` if you matched functions.
- A maintainer reviews and merges. CI must be green.

## Reporting issues

Use the [issue templates](https://github.com/ReGame-Labs/rmpg2-ut_decomp/issues/new/choose). Never attach game files or a
disc image.
