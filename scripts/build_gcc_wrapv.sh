#!/usr/bin/env bash
# Rebuilds the GCC 2.8.1 PSX compiler that scripts/setup.sh installs (docs/TOOLCHAIN.md "Compiler"): decompals/old-gcc's
# own recipe at the pinned commit, with one change, -fwrapv in the host CFLAGS.
#
# Why: old-gcc's release binaries are built by a modern host GCC, which takes signed overflow as undefined. GCC 2.8.1's
# cse.c (fold_rtx, case PLUS) tests `INTVAL (const_arg1) < 0 && - INTVAL (const_arg1) >= 0` to keep INT_MIN out, and
# the host folds the second half away; the result turns `x + 0x80000000` into a subu where the original compiler
# emits an addu. With -fwrapv the test works as written. Without it the recipe reproduces old-gcc's 0.17 release
# binaries bit for bit.
#
# usage: scripts/build_gcc_wrapv.sh [out_dir]   (default: build/gcc-wrapv; needs Docker)
# Writes gcc-2.8.1-psx-wrapv.tar.gz (cpp, cc1, gcc, cc1plus, g++: the layout of old-gcc's tarball) and
# gcc-2.8.1-psx-wrapv-src.tar.gz (the corresponding source: GCC 2.8.1 and the recipe as built), and their SHA-256.
# The pins in scripts/setup.sh are those of the published tarball.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
OUT="$(realpath -m "${1:-$ROOT/build/gcc-wrapv}")"

OLDGCC_URL=https://github.com/decompals/old-gcc.git
OLDGCC_COMMIT=b74211c9d959e9724802f3177c8229cd67202c87   # tag 0.17
GCC_URL=https://ftp.gnu.org/gnu/gcc/gcc-2.8.1.tar.gz
GCC_SHA256=3b30fbfdf93e628373d90d174243f3267b0eec9ebe792bb64fd15b8828c2ea4c

log() { printf '\033[1;34m[gcc-wrapv]\033[0m %s\n' "$*"; }
die() { printf '\033[1;31m[gcc-wrapv]\033[0m %s\n' "$*" >&2; exit 1; }

command -v docker >/dev/null || die "needs Docker"
work="$(mktemp -d)"
trap 'rm -rf "$work"' EXIT

log "old-gcc @ ${OLDGCC_COMMIT:0:7}"
git -C "$work" init -q old-gcc
git -C "$work/old-gcc" fetch -q --depth 1 "$OLDGCC_URL" "$OLDGCC_COMMIT"
git -C "$work/old-gcc" checkout -q FETCH_HEAD

recipe="$work/old-gcc/gcc-2.8.1-psx.Dockerfile"
sed -i 's/CFLAGS="-std=gnu89 -m32 -static"/CFLAGS="-std=gnu89 -m32 -static -fwrapv"/' "$recipe"
grep -q -- '-static -fwrapv"' "$recipe" || die "the recipe's CFLAGS line has changed: $recipe"

log "building (docker, a few minutes)"
(cd "$work/old-gcc" && docker build -q -f gcc-2.8.1-psx.Dockerfile --target export --output "$work/bin" .) >/dev/null
for f in cpp cc1 gcc cc1plus g++; do [[ -x "$work/bin/$f" ]] || die "missing $f"; done

# Reproducible archives: sorted names, fixed owner and times, no gzip timestamp.
pack() {  # pack <archive> <dir> <names...>
    local archive=$1 dir=$2; shift 2
    tar -C "$dir" --sort=name --owner=0 --group=0 --numeric-owner --mtime=@0 -cf - "$@" | gzip -n -9 > "$archive"
}
mkdir -p "$OUT"
pack "$OUT/gcc-2.8.1-psx-wrapv.tar.gz" "$work/bin" cc1 cc1plus cpp g++ gcc

log "corresponding source"
mkdir -p "$work/src/gcc-2.8.1-psx-wrapv"
curl -fsSL "$GCC_URL" -o "$work/src/gcc-2.8.1-psx-wrapv/gcc-2.8.1.tar.gz"
echo "$GCC_SHA256  $work/src/gcc-2.8.1-psx-wrapv/gcc-2.8.1.tar.gz" | sha256sum -c --quiet - || die "gcc-2.8.1.tar.gz: checksum mismatch"
cp -r "$work/old-gcc/patches" "$work/old-gcc/tests" "$recipe" "$work/src/gcc-2.8.1-psx-wrapv/"
cp "$0" "$work/src/gcc-2.8.1-psx-wrapv/build_gcc_wrapv.sh"
pack "$OUT/gcc-2.8.1-psx-wrapv-src.tar.gz" "$work/src" gcc-2.8.1-psx-wrapv

(cd "$OUT" && sha256sum gcc-2.8.1-psx-wrapv.tar.gz gcc-2.8.1-psx-wrapv-src.tar.gz | tee SHA256SUMS)
log "done: $OUT"
