# Rampage 2: Universal Tour decompilation

A matching decompilation of **Rampage 2: Universal Tour** (PlayStation, USA, SLUS-00742). The goal is C source that
recompiles into a byte-identical copy of the game's executable and overlays, built with the original-era toolchain.

> [!IMPORTANT]
> **This repository contains no game data.** You need your own copy of the game: the build reads the executable and
> the overlays from your disc image. This project is not affiliated with or endorsed by Midway, Avalanche Software or
> Sony.

## State

Every file already rebuilds byte-identical from split assembly; the work is turning that assembly into matching C.
[`docs/PROGRESS.md`](docs/PROGRESS.md) has the numbers.

## Documentation

| Document | Contents |
|---|---|
| [`docs/BUILDING.md`](docs/BUILDING.md) | Building: requirements, setup, the byte-identical build, the checks |
| [`docs/CONTRIBUTING.md`](docs/CONTRIBUTING.md) | How to contribute |
| [`docs/MATCHING.md`](docs/MATCHING.md) | How to match a function: workflow, tools, conventions, C patterns |
| [`docs/PROGRESS.md`](docs/PROGRESS.md) | How much of the game's code is matched |
| [`docs/TOOLCHAIN.md`](docs/TOOLCHAIN.md) | What built the original game |
| [`docs/DISC_LAYOUT.md`](docs/DISC_LAYOUT.md) | Disc files, memory map, overlays |
| [`docs/THIRD_PARTY.md`](docs/THIRD_PARTY.md) | Everything borrowed from other projects |
| [`tests/README.md`](tests/README.md) | The checks |

Problems and planned work are in the [issues](https://github.com/ReGame-Labs/rmpg2-ut_decomp/issues).

## Contributing

Contributions are welcome: matching a function, naming symbols, documenting a format. Read
[`docs/CONTRIBUTING.md`](docs/CONTRIBUTING.md) before opening a pull request.

## A note on how it is made

Part of the matching work and the tooling is done with the help of AI coding tools. Every change goes through the
same gate regardless of who or what wrote it: the byte-identical build, the checks in CI, and a maintainer's review.

## License

Our own work (source, tools, documentation) is under the [MIT licence](LICENSE). The decompiled source was written
by reading the game's machine code; every borrowing from other projects is recorded in
[`docs/THIRD_PARTY.md`](docs/THIRD_PARTY.md). The game itself remains the property of its publisher.
