/* OVERLAYS/OVERMOVE.BIN: the movie player (libpress's MDEC decoding is in psyq/libpress/), loaded at 0x80097EA4 by
 * cdload_load_overlay(1); the executable calls func_800A9890 with a movie number. docs/DISC_LAYOUT.md "Overlays". */
#include "common.h"

INCLUDE_ASM("asm/overmove/nonmatchings/overmove", func_800A9890);

INCLUDE_ASM("asm/overmove/nonmatchings/overmove", func_800A99E4);

INCLUDE_ASM("asm/overmove/nonmatchings/overmove", func_800A9C58);

INCLUDE_ASM("asm/overmove/nonmatchings/overmove", func_800A9CC0);

INCLUDE_ASM("asm/overmove/nonmatchings/overmove", func_800A9D30);

INCLUDE_ASM("asm/overmove/nonmatchings/overmove", func_800A9E5C);

INCLUDE_ASM("asm/overmove/nonmatchings/overmove", func_800A9EE0);

INCLUDE_ASM("asm/overmove/nonmatchings/overmove", func_800AA008);

INCLUDE_ASM("asm/overmove/nonmatchings/overmove", func_800AA09C);
