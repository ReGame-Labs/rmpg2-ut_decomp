#!/usr/bin/env bash
# Runs CI's checks locally, in the runner's environment (Docker, ubuntu-24.04: the Dockerfile), before a push.
# The working tree's tracked files (and new files not yet added, so a pre-commit run sees them) are streamed into a
# fresh container; its tools/ is the Docker volume rmpg2-ci-tools, where the tools scripts/setup.sh builds live
# (built once, ~3 min, kept between runs; a pin change rebuilds what changed; the tracked files of tools/ are
# refreshed into it on every run); the game files come from extracted/disc (or the private checkout's
# gamedata/disc), mounted read-only. Nothing is written to this checkout.
#
# Usage: scripts/ci_local.sh [--check] [--no-build] [--shell] [--clean-tools]
#   --check        the build from scratch (as CI's push to main does)
#   --no-build     the disc-free checks only (what a fork's pull request gets)
#   --shell        a shell in the prepared container instead of the checks
#   --clean-tools  delete the tools volume first
#   RMPG2_JOBS=N   fewer parallel jobs
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
IMAGE=rmpg2-ci
VOLUME=rmpg2-ci-tools
args=() shell=0
while [[ $# -gt 0 ]]; do
    case "$1" in
        --check|--no-build) args+=("$1"); shift ;;
        --shell) shell=1; shift ;;
        --clean-tools) docker volume rm -f "$VOLUME" >/dev/null; shift ;;
        -h|--help) sed -n '2,14p' "$0"; exit 0 ;;
        *) echo "unknown argument: $1" >&2; exit 2 ;;
    esac
done
command -v docker >/dev/null || { echo "docker is not installed" >&2; exit 1; }

docker build -q -t "$IMAGE" "$ROOT" >/dev/null

# The game files: this checkout's extracted/disc (a directory or a symlink into the private checkout).
disc=()
if d="$(cd "$ROOT" && readlink -f extracted/disc 2>/dev/null)" && [[ -f "$d/SLUS_007.42" ]]; then
    disc=(-v "$d:/work/extracted/disc:ro")
else
    echo "ci_local: no extracted/disc: the disc-free checks only" >&2
    args+=(--no-build)
fi

# Inside the container: unpack the tree from stdin (tools/ lands in the volume), then the checks.
read -r -d '' inner <<'EOF' || true
set -euo pipefail
mkdir -p /work && cd /work && tar -x
git init -q . && git add -A -- src include config >/dev/null 2>&1 || true   # tools/hacks.py reads `git ls-files`
scripts/setup.sh binutils venv cmake mkpsxiso gcc objdiff ext
export PATH="/work/tools/venv/bin:$PATH"
if [[ "${1:-}" == --shell ]]; then exec bash; fi
scripts/test.sh "$@"
EOF
inner_args=()
[[ $shell -eq 1 ]] && inner_args=(--shell) || inner_args=("${args[@]}")
tty=()
[[ -t 0 && $shell -eq 1 ]] && tty=(-t)
# The tree: tracked files plus new untracked ones (not the ignored tools/, extracted/, build/, ...).
(cd "$ROOT" && git ls-files -z --cached --others --exclude-standard | tar -c --null -T -) |
    docker run --rm -i "${tty[@]}" -v "$VOLUME:/work/tools" "${disc[@]}" \
        -e RMPG2_JOBS="${RMPG2_JOBS:-$(nproc)}" -e RMPG2_UBUNTU_MIRROR="${RMPG2_UBUNTU_MIRROR:-}" \
        "$IMAGE" bash -c "$inner" -- "${inner_args[@]}"
