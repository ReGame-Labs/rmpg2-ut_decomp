#!/usr/bin/env bash
# The project's checks, one entry point (tests/README.md): the scripts parse and the Python compiles, the workaround
# census (tools/hacks.py), the toolchain smoke test, unit_diff's comparison and the variant scorer's and drafter's
# test, and with the disc the byte-identical build. Exits non-zero on the first failure. CI runs the same steps (.github/workflows/ci.yml; scripts/ci_local.sh
# runs them in Docker).
# Usage: scripts/test.sh [--check] [--no-build]
#   --check     the build from scratch (scripts/build.sh --check) instead of the incremental one
#   --no-build  the disc-free checks only
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"
BUILD=1
CHECK=()
while [[ $# -gt 0 ]]; do
    case "$1" in
        --check) CHECK=(--check); shift ;;
        --no-build) BUILD=0; shift ;;
        -h|--help) sed -n '2,8p' "$0"; exit 0 ;;
        *) echo "unknown argument: $1" >&2; exit 2 ;;
    esac
done
PY="$ROOT/tools/venv/bin/python"
[[ -x "$PY" ]] || PY=python3

echo "=== scripts parse, Python compiles"
bash -n scripts/*.sh tools/*.sh
"$PY" -m py_compile configure.py diff_settings.py tools/*.py tests/*.py

echo "=== census: the matching workarounds (tools/hacks.py)"
"$PY" tools/hacks.py --check

if [[ -x tools/binutils/bin/mipsel-linux-gnu-as && -x tools/gcc/2.8.1/cc1 ]]; then
    echo "=== toolchain smoke test (scripts/check_toolchain.sh)"
    scripts/check_toolchain.sh
    echo "=== unit_diff's comparison (tests/unit_diff_test.py)"
    "$PY" tests/unit_diff_test.py
    echo "=== the variant scorer and the drafter (tests/variant_test.py)"
    "$PY" tests/variant_test.py
else
    echo "=== toolchain smoke test, unit_diff's comparison, the variant scorer: skipped (scripts/setup.sh first)"
fi

if [[ $BUILD -eq 1 ]]; then
    if [[ -f extracted/disc/SLUS_007.42 ]]; then
        echo "=== the byte-identical build (scripts/build.sh ${CHECK[*]:-})"
        scripts/build.sh "${CHECK[@]}"
    else
        echo "=== the byte-identical build: skipped (no extracted/disc: scripts/worktree_init.sh)"
    fi
fi
echo "test.sh: ok"
