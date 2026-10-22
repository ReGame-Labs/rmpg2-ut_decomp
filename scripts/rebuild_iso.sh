#!/usr/bin/env bash
# Rebuild the disc image from extracted/ with mkpsxiso and compare it to the original.
# Usage: scripts/rebuild_iso.sh [xml]   (default: extracted/rmpg2.xml)
# Output: build/rmpg2.bin + .cue. Exits non-zero if the image differs.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
XML="${1:-$ROOT/extracted/rmpg2.xml}"
mkdir -p "$ROOT/build"

# Run from the XML directory so its relative source paths resolve.
(cd "$(dirname "$XML")" && "$ROOT/tools/mkpsxiso/bin/mkpsxiso" -y -q \
    -o "$ROOT/build/rmpg2.bin" -c "$ROOT/build/rmpg2.cue" "$(basename "$XML")")

if cmp -s "$ROOT/build/rmpg2.bin" "$ROOT/iso/rmpg2.bin"; then
    echo "OK: build/rmpg2.bin is bit-identical to iso/rmpg2.bin"
else
    echo "DIFF: build/rmpg2.bin differs from iso/rmpg2.bin ($(cmp -l "$ROOT/build/rmpg2.bin" "$ROOT/iso/rmpg2.bin" 2>/dev/null | wc -l) bytes)" >&2
    exit 1
fi
