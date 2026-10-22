<!-- Thanks for contributing! Please read docs/CONTRIBUTING.md first. Keep the pull request to one topic. -->

## What changed

<!-- What this does and why. Link the issue it fixes: "Fixes #123". -->

## How it was tested

<!-- Commands you ran and their result. Fork pull requests get CI without the game files, so the byte-identical
build has to be run by you. -->

- [ ] `scripts/test.sh --check` passes (the checks and the byte-identical build from scratch)

## Checklist

- [ ] No game data: no disc image, extracted files, `asm/`, assets, BIOS or SDK files
- [ ] Anything borrowed from another project is recorded in `docs/THIRD_PARTY.md`
- [ ] New names follow the conventions (`docs/MATCHING.md`) and are in `config/*symbol*.txt`
- [ ] `docs/PROGRESS.md` updated if functions were matched (`tools/progress.py --readme`)
