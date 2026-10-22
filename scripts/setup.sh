#!/usr/bin/env bash
# Project-local toolchain setup. Idempotent: re-running skips finished steps.
# Nothing here needs sudo or installs outside the repo.
#
# Usage: scripts/setup.sh [--disc /path/to/disc.bin] [step...]
#        scripts/setup.sh --pins      print the pinned versions, tags, hashes and URLs (CI's tool-cache key)
#   steps: binutils venv cmake mkpsxiso gcc objdiff ext link private disc  (default: all)
#   optional (not in the default steps): psyq
#   binutils: GNU binutils for mipsel-linux-gnu (as, ld, objdump, nm) built from the pinned tarball into tools/binutils
#   venv:     tools/venv with tools/requirements.txt (splat, spimdisasm, the diff tools' Python packages)
#   cmake:    CMake and Ninja pip-installed into tools/venv, only when the system has none
#   mkpsxiso: mkpsxiso/dumpsxiso (the disc's extraction and rebuild) into tools/mkpsxiso
#   gcc:      the old-gcc PSX builds (GCC 2.7.2 ... 2.95.2, static i386 binaries) into tools/gcc/<version>
#   objdiff:  objdiff-cli (the per-function diff and the progress report) into tools/bin
#   ext:      pinned git clones of maspsx, m2c, asm-differ, decomp-permuter, psx_psyq_signatures into tools/ext
#   link:     in a git worktree, symlink the main checkout's built tools into this one (no-op in the main checkout)
#   private:  link the private checkout (scripts/private_dir.sh: the original binaries the build reads) as private/
#   disc:     verify the user's disc image (SHA-1 of the dump this project was started from) and link it as iso/rmpg2.bin
#   psyq:     Sony's Psy-Q 4.3/4.4 compilers and assembler (the binaries decomp.me uses) plus wibo, for cross-checking
#             the open toolchain against the real one; never committed (tools/psyq is gitignored)
#
# Worktrees: built tools always go into the MAIN checkout's tools/ (shared by every worktree), and the "link" step
# symlinks them into this worktree. Tracked inputs (requirements.txt, ...) are read from this checkout.
#
# Adapted from gascarcella/dw2003recomp's scripts/setup.sh (MIT; docs/THIRD_PARTY.md).
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
MAIN="$(dirname "$(git -C "$ROOT" rev-parse --path-format=absolute --git-common-dir)")"
TOOLS="$ROOT/tools"          # tracked files of this checkout
INSTALL="$MAIN/tools"        # built/installed tools, shared across worktrees
SRC="$INSTALL/src"
JOBS="${RMPG2_JOBS:-$(nproc)}"   # RMPG2_JOBS: fewer on a shared machine (as scripts/build.sh)
PINS_BEFORE="$(compgen -A variable)"   # `--pins`: every variable defined from here to the steps is a pin (below)

BINUTILS_VER=2.47
BINUTILS_SHA256=154ab23b60070e8f27013c22977f1129425d67d1e8acd6e13010e617811e4cff
MKPSXISO_TAG=v2.30

# decompals/old-gcc release: GNU GCC built with Psy-Q's PSX patches (static i386 binaries).
# Psy-Q 4.0/4.3/4.4/4.5/4.6 shipped 2.7.2/2.8.0/2.8.1/2.91.66/2.95.2. SHA-256 of each tarball.
OLDGCC_TAG=0.17
OLDGCC=(
    "2.7.2   500a459b3485e885a8d302cac23c2a4632f3900e03a09153f6190699fd723571"
    "2.8.0   1a3c956fe8aea5ebdb251749d95de2c84f023530584d7bd663744b5ec24050b7"
    "2.8.1   f6f6e883942d4d3289d048236c672e71ed410e546aaae8ff655952f1567e1be0"
    "2.91.66 f773a0a9659fa4ff74313ac4363d939312e8125675cd09ad9f8c1202f587f1fd"
    "2.95.2  932ed3669710a82b12570c29c46ff42989b6505b2af10db84d4551d55dfc0b1c"
)

OBJDIFF_VER=3.8.2
OBJDIFF_CLI_SHA256=e5445089a6f707e30cb5e02992451b604619cedfd2660ee2373a86bfefd9e718  # linux-x86_64

# Python tools used straight from git, pinned to a commit (no tags/PyPI releases worth using).
EXT=(
    "maspsx          https://github.com/mkst/maspsx.git                   7686f845a181700534c83c0419183e38aeb3e49c"
    "m2c             https://github.com/matt-kempster/m2c.git             708d2d2cb2698f091a92492b328f73b24209f72d"
    "asm-differ      https://github.com/simonlindholm/asm-differ.git      0dd09af8f8008f1f880327cf0aca3b26d2562ea2"
    "decomp-permuter https://github.com/simonlindholm/decomp-permuter.git 059609d4aec73eb0650726772954e1ad575825f8"
    "psyq-sigs       https://github.com/lab313ru/psx_psyq_signatures.git e9e46e7e133ef275a79bfce650924f98edb086bc"
)

# SHA-1 of the disc image this project was started from: a single-track dump of Rampage 2: Universal Tour (USA),
# SLUS-00742 (164,495 sectors of 2352 bytes). Not a verified Redump image (the retail disc has one data track and
# two audio tracks); the build only needs the files it holds (config/SLUS_007.42.sha1 is what matters).
DISC_SHA1=7146646ad0d23a499850e284f2853a9a5519eb58

# Sony's Psy-Q 4.3/4.4 compilers and assembler (the binaries decomp.me uses, from mkst/esa's releases), run through
# wibo; an optional cross-check of the open toolchain against the real one. Never committed.
PSYQ=(
    "psyq4.3.tar.gz https://github.com/mkst/esa/releases/download/psyq-binaries/psyq4.3.tar.gz 577038d66507d3aa5423de0ba3f540e121a4f60f637f4794aa4350135d4f9a46"
    "psyq4.4.tar.gz https://github.com/mkst/esa/releases/download/psyq-binaries/psyq4.4.tar.gz 72e73934bab0d51933eb95af514afb14f3d432f01530eac3ddb16dfbb57ab66c"
    "psyq-obj-parser.tar.gz https://github.com/decompme/compilers/releases/download/compilers/psyq-obj-parser.tar.gz 353495f13f6756773cd905ba3a0743843232f95719e306fc6ee56cbf7d731a3e"
    "wibo https://github.com/decompals/wibo/releases/download/0.6.16/wibo 8a8490a6172aa4f0f6ddcadb144ca96f51da6e90e6648ce9adaf4f6babb6e00b"
)

# RMPG2_UBUNTU_MIRROR: the Ubuntu archive binutils' fallback tarball comes from (CI sets the runners' own mirror).
UBUNTU_MIRROR="${RMPG2_UBUNTU_MIRROR:-http://archive.ubuntu.com/ubuntu}"

log() { printf '\033[1;34m[setup]\033[0m %s\n' "$*"; }
die() { printf '\033[1;31m[setup]\033[0m %s\n' "$*" >&2; exit 1; }
# fetch URL FILE: a download that survives a transient failure (CI runners get resets and stalls from mirrors): a
# transfer under 1 KB/s for a minute is given up, 5 retries on any error, no connect longer than 30 s.
fetch() {
    curl -sSfL --retry 5 --retry-all-errors --retry-delay 5 --connect-timeout 30 --max-time 600 \
        --speed-limit 1024 --speed-time 60 -o "$2" "$1"
}

step_binutils() {
    local prefix="$INSTALL/binutils"
    if [[ -x "$prefix/bin/mipsel-linux-gnu-as" ]]; then
        log "binutils: already installed ($("$prefix/bin/mipsel-linux-gnu-as" --version | head -1))"
        return
    fi
    mkdir -p "$SRC"
    local tarball="$SRC/binutils-$BINUTILS_VER.tar.xz"
    if [[ ! -f "$tarball" ]]; then
        log "binutils: downloading $BINUTILS_VER"
        # Ubuntu's .orig tarball is the upstream file (same SHA-256); the fallback for networks that block ftp.gnu.org.
        fetch "https://ftp.gnu.org/gnu/binutils/binutils-$BINUTILS_VER.tar.xz" "$tarball.part" ||
            fetch "$UBUNTU_MIRROR/pool/main/b/binutils/binutils_$BINUTILS_VER.orig.tar.xz" "$tarball.part"
        mv "$tarball.part" "$tarball"
    fi
    echo "$BINUTILS_SHA256  $tarball" | sha256sum -c --quiet - || die "binutils: checksum mismatch"
    rm -rf "$SRC/binutils-$BINUTILS_VER" "$SRC/binutils-build"
    tar -C "$SRC" -xf "$tarball"
    mkdir -p "$SRC/binutils-build"
    log "binutils: configuring (target mipsel-linux-gnu)"
    (cd "$SRC/binutils-build" && "../binutils-$BINUTILS_VER/configure" \
        --prefix="$prefix" --target=mipsel-linux-gnu \
        --disable-nls --disable-werror --disable-gdb --disable-gdbserver \
        --disable-sim --disable-gprofng --disable-libdecnumber --disable-readline \
        MAKEINFO=true >/dev/null)
    log "binutils: building with $JOBS jobs"
    make -C "$SRC/binutils-build" -j"$JOBS" MAKEINFO=true >/dev/null
    make -C "$SRC/binutils-build" install MAKEINFO=true >/dev/null
    rm -rf "$SRC/binutils-build" "$SRC/binutils-$BINUTILS_VER"
    log "binutils: installed to $prefix"
}

step_mkpsxiso() {
    local prefix="$INSTALL/mkpsxiso"
    if [[ -x "$prefix/bin/dumpsxiso" && -x "$prefix/bin/mkpsxiso" ]]; then
        log "mkpsxiso: already installed"
        return
    fi
    command -v cmake >/dev/null && command -v ninja >/dev/null || step_cmake
    mkdir -p "$SRC"
    local dir="$SRC/mkpsxiso"
    if [[ ! -d "$dir/.git" ]]; then
        log "mkpsxiso: cloning $MKPSXISO_TAG"
        git -c advice.detachedHead=false clone -q --branch "$MKPSXISO_TAG" --depth 1 --recurse-submodules --shallow-submodules \
            https://github.com/Lameguy64/mkpsxiso.git "$dir"
    fi
    log "mkpsxiso: building"
    cmake -S "$dir" -B "$dir/build" -G Ninja -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX="$prefix" >/dev/null
    cmake --build "$dir/build" -j"$JOBS" >/dev/null
    cmake --install "$dir/build" >/dev/null
    log "mkpsxiso: installed to $prefix"
}

# CMake and Ninja from PyPI (official wheels), pinned, into the venv: only when the system has none (no sudo).
CMAKE_PIP=cmake==3.31.10
NINJA_PIP=ninja==1.13.0
step_cmake() {
    local venv="$INSTALL/venv"
    if command -v cmake >/dev/null && command -v ninja >/dev/null; then
        log "cmake: cmake and ninja on PATH ($(command -v cmake), $(command -v ninja))"
        return
    fi
    [[ -x "$venv/bin/pip" ]] || step_venv
    if [[ ! -x "$venv/bin/cmake" || ! -x "$venv/bin/ninja" ]]; then
        log "cmake: installing $CMAKE_PIP $NINJA_PIP into tools/venv (missing from PATH)"
        "$venv/bin/pip" install -q "$CMAKE_PIP" "$NINJA_PIP"
    fi
    export PATH="$PATH:$venv/bin"   # after the system's: the venv's python stays out of the way
    log "cmake: using $(command -v cmake), $(command -v ninja) (tools/venv)"
}

step_venv() {
    local venv="$INSTALL/venv"
    # A venv's console scripts (pip, splat, ...) hard-code the interpreter's path: a venv restored under another
    # path (a renamed checkout, CI's cache from another workspace) cannot run them. Recreate it.
    if [[ -f "$venv/bin/pip" && "$(dirname "$(sed -n '1s/^#!//p' "$venv/bin/pip")")" != "$venv/bin" ]]; then
        log "venv: made for another path ($(sed -n '1s/^#!//p' "$venv/bin/pip")); recreating"
        rm -rf "$venv"
    fi
    if [[ ! -x "$venv/bin/python" ]]; then
        log "venv: creating with $(python3 --version)"
        python3 -m venv "$venv"
    fi
    log "venv: installing tools/requirements.txt"
    "$venv/bin/pip" install -q --upgrade pip
    "$venv/bin/pip" install -q -r "$TOOLS/requirements.txt"
}

# old-gcc PSX builds into tools/gcc/<version>/ (cpp, cc1, gcc, ...).
step_gcc() {
    local entry ver sha dir tarball
    mkdir -p "$SRC" "$INSTALL/gcc"
    for entry in "${OLDGCC[@]}"; do
        read -r ver sha <<<"$entry"
        dir="$INSTALL/gcc/$ver"
        if [[ -x "$dir/cc1" && -f "$dir/.sha256" && "$(cat "$dir/.sha256")" == "$sha" ]]; then
            log "gcc: $ver already installed"
            continue
        fi
        tarball="$SRC/gcc-$ver-psx.tar.gz"
        if [[ ! -f "$tarball" ]] || ! echo "$sha  $tarball" | sha256sum -c --quiet - 2>/dev/null; then
            log "gcc: downloading $ver (old-gcc $OLDGCC_TAG)"
            fetch "https://github.com/decompals/old-gcc/releases/download/$OLDGCC_TAG/gcc-$ver-psx.tar.gz" \
                "$tarball.part"
            mv "$tarball.part" "$tarball"
        fi
        echo "$sha  $tarball" | sha256sum -c --quiet - || die "gcc: checksum mismatch for $ver"
        rm -rf "$dir"
        mkdir -p "$dir"
        tar -C "$dir" -xzf "$tarball"
        echo "$sha" > "$dir/.sha256"
        log "gcc: installed $ver to $dir"
    done
}

step_psyq() {
    local dir="$INSTALL/psyq" entry name url sha
    mkdir -p "$dir"
    for entry in "${PSYQ[@]}"; do
        read -r name url sha <<<"$entry"
        if [[ ! -f "$dir/$name" ]] || ! echo "$sha  $dir/$name" | sha256sum -c --quiet - 2>/dev/null; then
            log "psyq: downloading $name"
            fetch "$url" "$dir/$name.part"
            echo "$sha  $dir/$name.part" | sha256sum -c --quiet - || die "psyq: checksum mismatch for $name"
            mv "$dir/$name.part" "$dir/$name"
        fi
        [[ "$name" == *.tar.gz ]] && tar -C "$dir" -xzf "$dir/$name"
    done
    chmod +x "$dir/wibo" "$dir/psyq-obj-parser"
    log "psyq: installed to $dir (wibo $dir/psyq4.4/CC1PSX.EXE ...)"
}

# objdiff-cli (prebuilt, checksum-pinned) into tools/bin/.
step_objdiff() {
    local bin="$INSTALL/bin/objdiff-cli"
    if [[ -x "$bin" ]] && echo "$OBJDIFF_CLI_SHA256  $bin" | sha256sum -c --quiet - 2>/dev/null; then
        log "objdiff: already installed ($("$bin" --version))"
        return
    fi
    mkdir -p "$INSTALL/bin"
    log "objdiff: downloading objdiff-cli $OBJDIFF_VER"
    fetch "https://github.com/encounter/objdiff/releases/download/v$OBJDIFF_VER/objdiff-cli-linux-x86_64" "$bin.part"
    echo "$OBJDIFF_CLI_SHA256  $bin.part" | sha256sum -c --quiet - || die "objdiff: checksum mismatch"
    chmod +x "$bin.part"
    mv "$bin.part" "$bin"
    log "objdiff: installed $("$bin" --version)"
}

# Pinned git clones into tools/ext/<name>/. The commit hash is the checksum.
step_ext() {
    local entry name url commit dir
    mkdir -p "$INSTALL/ext"
    for entry in "${EXT[@]}"; do
        read -r name url commit <<<"$entry"
        dir="$INSTALL/ext/$name"
        if [[ -d "$dir/.git" && "$(git -C "$dir" rev-parse HEAD)" == "$commit" ]]; then
            log "ext: $name already at ${commit:0:12}"
            continue
        fi
        if [[ ! -d "$dir/.git" ]]; then
            log "ext: cloning $name"
            git clone -q "$url" "$dir"
        fi
        git -C "$dir" fetch -q origin "$commit" 2>/dev/null || git -C "$dir" fetch -q origin
        git -c advice.detachedHead=false -C "$dir" checkout -q "$commit"
        [[ "$(git -C "$dir" rev-parse HEAD)" == "$commit" ]] || die "ext: $name is not at $commit"
        log "ext: $name at ${commit:0:12}"
    done
}

# Symlink the user's own disc image into iso/ (never copied into git).
step_disc() {
    local bin="${DISC_PATH:-}"
    if [[ -z "$bin" && -f "$INSTALL/local.env" ]]; then
        # shellcheck disable=SC1091
        source "$INSTALL/local.env"
        bin="${RMPG2_DISC_BIN:-}"
    fi
    if [[ -z "$bin" ]]; then
        log "disc: no disc given (use --disc or set RMPG2_DISC_BIN in tools/local.env); skipping"
        return
    fi
    [[ -f "$bin" ]] || die "disc: not found: $bin"
    log "disc: verifying SHA-1 (this reads ~370 MB)"
    local sha
    sha="$(sha1sum "$bin" | cut -d' ' -f1)"
    if [[ "$sha" != "$DISC_SHA1" ]]; then
        die "disc: SHA-1 $sha does not match the expected image $DISC_SHA1"
    fi
    mkdir -p "$ROOT/iso"
    ln -sfn "$bin" "$ROOT/iso/rmpg2.bin"
    cat > "$ROOT/iso/rmpg2.cue" <<'EOF'
FILE "rmpg2.bin" BINARY
  TRACK 01 MODE2/2352
    INDEX 01 00:00:00
EOF
    log "disc: linked iso/rmpg2.bin -> $bin"
}

# The private checkout (scripts/private_dir.sh): linked as private/ (gitignored). Nothing from it is ever copied
# into this repository. Its link.sh, when it has one, may link more of its files into this checkout (each one kept
# out of git through .git/info/exclude, never through the tracked .gitignore).
step_private() {
    local pd
    pd="$("$ROOT/scripts/private_dir.sh" 2>/dev/null)" || { log "private: no private checkout (optional; RMPG2_PRIVATE in tools/local.env); skipping"; return; }
    [[ -e "$ROOT/private" && ! -L "$ROOT/private" ]] && die "private: $ROOT/private exists and is not a symlink"
    ln -sfn "$pd" "$ROOT/private"
    log "private: private/ -> $pd"
    [[ -x "$pd/link.sh" ]] && "$pd/link.sh" "$ROOT"
    return 0
}

# In a worktree: symlink every gitignored entry of the main checkout's tools/ that is missing here (built tools,
# local.env). No-op in the main checkout.
step_link() {
    [[ "$MAIN" != "$ROOT" ]] || return 0
    local src name dst
    for src in "$INSTALL"/* "$INSTALL"/.[!.]*; do
        [[ -e "$src" ]] || continue
        name="$(basename "$src")"
        dst="$TOOLS/$name"
        [[ -e "$dst" || -L "$dst" ]] && continue
        # this checkout's .gitignore: a branch that adds a tool knows its directory before main does
        if git -C "$ROOT" check-ignore -q "tools/$name"; then
            ln -s "$src" "$dst"
            log "link: tools/$name -> $src"
        fi
    done
}

# The pins: every variable this script defined after PINS_BEFORE (versions, tags, SHA-256s, URLs), as `declare -p`
# lines. CI hashes them with tools/requirements.txt into its tool cache's key (.github/actions/setup), so a change to
# this script's logic alone keeps the cache valid; only what the tools are built from changes the key.
pins() {
    local v
    for v in $(comm -13 <(sort <<< "$PINS_BEFORE") <(compgen -A variable | sort)); do
        [[ "$v" =~ ^[A-Z][A-Z0-9_]*$ ]] || continue
        case "$v" in PINS_BEFORE|UBUNTU_MIRROR|DISC_PATH|FUNCNAME) continue ;; esac
        declare -p "$v"
    done
}

DISC_PATH=""
steps=()
while [[ $# -gt 0 ]]; do
    case "$1" in
        --disc) DISC_PATH="$2"; shift 2 ;;
        --pins) pins; exit 0 ;;
        -h|--help) sed -n '2,24p' "$0"; exit 0 ;;
        *) steps+=("$1"); shift ;;
    esac
done
[[ ${#steps[@]} -gt 0 ]] || steps=(binutils venv cmake mkpsxiso gcc objdiff ext link private disc)

for s in "${steps[@]}"; do
    declare -F "step_$s" >/dev/null || die "unknown step: $s"
    "step_$s"
done
# Anything just installed into the main checkout becomes visible in this worktree.
step_link
log "done"
