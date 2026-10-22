# asm-differ settings: tools/venv/bin/python tools/ext/asm-differ/diff.py -mw <function>
# Diffs the built executable against the original (needs a linked build/, i.e. `scripts/build.sh` once).
def apply(config, args):
    config["arch"] = "mipsel"
    config["baseimg"] = "extracted/disc/SLUS_007.42"
    config["myimg"] = "build/SLUS_007.42"
    config["mapfile"] = "build/main/SLUS_007.42.map"
    config["source_directories"] = ["src", "include", "asm"]
    config["objdump_executable"] = "tools/binutils/bin/mipsel-linux-gnu-objdump"
    config["make_command"] = ["ninja"]
