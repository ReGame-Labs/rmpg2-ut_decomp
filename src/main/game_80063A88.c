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

extern s16 D_800853D6;
extern s32 D_800853D8;
extern s32 D_800853DC;
extern s16 D_800853EA;
extern s32 D_800853EC;
extern s32 D_800853F0;

void func_80063D04(void) {
    if (D_800853C4 != 0) {
        if (D_800853E4 > 0) {
            D_800853E4--;
            D_800853E8 += D_800853F0;
            if (D_800853E4 == 0) {
                D_800853E8 = D_800853EC;
            }
            D_800853E0 = D_800853EA;
            func_80063CC0(D_800853EA);
        }
        if (D_800853D0 > 0) {
            D_800853D0--;
            D_800853D4 += D_800853DC;
            if (D_800853D0 == 0) {
                D_800853D4 = D_800853D8;
            }
            D_800853CC = D_800853D6;
            func_80063C7C(D_800853D6);
        }
    }
}

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
