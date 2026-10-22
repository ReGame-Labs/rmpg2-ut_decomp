#!/usr/bin/env bash
# Prints the private checkout's directory (the original binaries the build and CI read, the maintainers' internal
# documents): $RMPG2_PRIVATE, RMPG2_PRIVATE in tools/local.env, or the sibling ../rmpg2-ut_privatedata of the main
# checkout. Exit 1 (nothing printed) when there is none. Nothing from it is ever copied into this repository.
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
MAIN="$(dirname "$(git -C "$ROOT" rev-parse --path-format=absolute --git-common-dir)")"
dir="${RMPG2_PRIVATE:-}"
if [[ -z "$dir" && -f "$MAIN/tools/local.env" ]]; then
    # shellcheck disable=SC1091
    source "$MAIN/tools/local.env"
    dir="${RMPG2_PRIVATE:-}"
fi
[[ -n "$dir" ]] || dir="$MAIN/../rmpg2-ut_privatedata"
[[ -d "$dir" ]] || exit 1
cd "$dir" && pwd
