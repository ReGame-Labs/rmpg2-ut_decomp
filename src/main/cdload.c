/* The CD file reader (by index into the file table, with a checksum) and the overlay loader; docs/DISC_LAYOUT.md.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80060F3C);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80061014);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80061068);

void func_800610E8(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_800610F0);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80061110);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_8006113C);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80061158);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80061170);

INCLUDE_ASM("asm/main/nonmatchings/cdload", cdload_read_file);

INCLUDE_ASM("asm/main/nonmatchings/cdload", cdload_wait_sync);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_800613FC);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80061444);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_800614B0);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_800614BC);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_800614E0);

INCLUDE_ASM("asm/main/nonmatchings/cdload", cdload_wait_read_sync);

INCLUDE_ASM("asm/main/nonmatchings/cdload", cdload_checksum);

INCLUDE_ASM("asm/main/nonmatchings/cdload", cdload_city_file_index);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80061668);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80061774);

INCLUDE_ASM("asm/main/nonmatchings/cdload", cdload_load_overlay);

INCLUDE_ASM("asm/main/nonmatchings/cdload", cdload_load_city_table);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_800619A4);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80061ACC);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80061B4C);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80061D10);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80061F90);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_800621F8);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80062868);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80062C10);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80062C30);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80062D88);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80062DA8);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80062DCC);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80062DEC);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80062E24);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80062E44);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80062E64);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80062E88);

void func_80062EA8(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80062EB0);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80062F14);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_8006301C);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80063064);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80063084);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_800630E8);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_800631B4);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80063214);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80063270);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_800632CC);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_800632E8);
