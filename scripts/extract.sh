#!/usr/bin/env bash
# Extract the disc into extracted/disc/ and write the mkpsxiso layout to extracted/rmpg2.xml (paths relative to the
# XML, so the tree is relocatable).
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
DISC="$ROOT/iso/rmpg2.bin"
OUT="$ROOT/extracted"

[[ -e "$DISC" ]] || { echo "missing $DISC; run scripts/setup.sh disc" >&2; exit 1; }

rm -rf "$OUT/disc" "$OUT/rmpg2.xml"
mkdir -p "$OUT"
"$ROOT/tools/mkpsxiso/bin/dumpsxiso" -q -x "$OUT/disc" -s "$OUT/rmpg2.xml" "$DISC"

# Make source paths relative to the XML's directory.
sed -i "s|\"$OUT/|\"|g" "$OUT/rmpg2.xml"

echo "extracted $(find "$OUT/disc" -type f | wc -l) files to extracted/disc, layout in extracted/rmpg2.xml"
