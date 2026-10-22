#!/usr/bin/env bash
# Prepare a fresh git worktree (or a fresh clone beside a private checkout). A checkout only has tracked files, so
# the gitignored ones (built tools, tools/local.env, the disc link, extracted/, private/) are missing. This script:
#   1. symlinks the main checkout's built tools and local.env into this worktree (setup.sh link)
#   2. links the private checkout (setup.sh private: private/, AGENTS.private.md)
#   3. links the disc (setup.sh disc) and extracts it (extract.sh); without a disc image, the private checkout's
#      gamedata/disc (the executable and the overlays) is enough to build
# If the main checkout already has extracted/, a worktree links its iso/ and extracted/ instead.
# Idempotent, ~1 s. To install a NEW tool from a worktree, run scripts/setup.sh <step>: it installs into the main
# checkout's tools/ and links it here.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
MAIN="$(dirname "$(git -C "$ROOT" rev-parse --path-format=absolute --git-common-dir)")"

# A worktree of a checkout that already has the disc extracted shares it (read-only inputs).
if [[ "$MAIN" != "$ROOT" && -f "$MAIN/extracted/disc/SLUS_007.42" && ! -e "$ROOT/extracted" ]]; then
    "$ROOT/scripts/setup.sh" link private
    [[ -e "$MAIN/iso" ]] && ln -s "$MAIN/iso" "$ROOT/iso"
    ln -s "$MAIN/extracted" "$ROOT/extracted"
    echo "iso/, extracted/ -> $MAIN (shared with the main checkout)"
    echo "worktree ready: $ROOT"
    exit 0
fi
"$ROOT/scripts/setup.sh" link private disc
if [[ -f "$ROOT/extracted/disc/SLUS_007.42" ]]; then
    # Already extracted (re-extracting would pull files from under worktrees that link to it).
    echo "extracted/ already present; rm -rf extracted and rerun to re-extract"
elif [[ -e "$ROOT/iso/rmpg2.bin" ]]; then
    "$ROOT/scripts/extract.sh"
elif PD="$("$ROOT/scripts/private_dir.sh" 2>/dev/null)" && [[ -f "$PD/gamedata/disc/SLUS_007.42" ]]; then
    # The private checkout without the disc image: its executable and overlays are enough to build.
    mkdir -p "$ROOT/extracted"
    ln -sfn "$PD/gamedata/disc" "$ROOT/extracted/disc"
    echo "extracted/disc -> $PD/gamedata/disc (no disc image; the executable and the overlays only)"
else
    echo "no disc: set RMPG2_DISC_BIN (or RMPG2_PRIVATE) in tools/local.env (see tools/local.env.example)" >&2
    exit 1
fi
echo "worktree ready: $ROOT"
