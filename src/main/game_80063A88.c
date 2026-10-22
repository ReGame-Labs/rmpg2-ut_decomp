/* A piece of the game's own code between Psy-Q library objects: the sound driver on libspu (docs/TOOLCHAIN.md).
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
void func_80063C7C(s16);
void func_80063CC0(s16);

extern s32 D_800853C4;
extern s32 D_800853D0;
extern s32 D_800853D4;
extern s32 D_800853E0;
extern s32 D_800853E8;

extern s32 D_800853CC;
extern s32 D_800853E4;

INCLUDE_ASM("asm/main/nonmatchings/game_80063A88", func_80063A88);

INCLUDE_ASM("asm/main/nonmatchings/game_80063A88", func_80063BB0);

INCLUDE_ASM("asm/main/nonmatchings/game_80063A88", func_80063C7C);

INCLUDE_ASM("asm/main/nonmatchings/game_80063A88", func_80063CC0);

INCLUDE_ASM("asm/main/nonmatchings/game_80063A88", func_80063D04);

void func_80063DF8(s32 v) {
    D_800853E0 = v;
    D_800853E8 = v << 16;
    D_800853C4 = 0;
    D_800853E4 = 0;
    func_80063CC0(v);
    D_800853C4 = 1;
}

INCLUDE_ASM("asm/main/nonmatchings/game_80063A88", func_80063E48);

s32 func_80063F30(void) {
    return D_800853E4 >= 2;
}

void func_80063F48(s32 v) {
    D_800853CC = v;
    D_800853D4 = v << 16;
    D_800853C4 = 0;
    D_800853D0 = 0;
    func_80063C7C(v);
    D_800853C4 = 1;
}

s32 func_80063F98(void) {
    return D_800853CC;
}
