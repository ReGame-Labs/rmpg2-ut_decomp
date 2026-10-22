/* A file of the game's code, named after its first function until its contents are understood.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"

s32 func_8001A3AC(void);
void func_8001E450(s32);
void func_8001ED54(s32 *);
void func_8005EE54(void);

extern s32 D_80089624[];
extern s32 D_80089644[];
extern s32 D_800AA2DC;
extern s16 D_801FB468;
extern s16 D_801FB46C;

s32 func_8005D198(void) {
    return func_8001A3AC() >= 0x46;
}

void func_8005D1BC(s32 arg0, s32 n) {
    func_8001E450((u16)(n + 0x790));
    func_8001E450((u16)(n + 0x798));
    func_8001E450((u16)(n + 0x7A8));
    func_8001E450((u16)(n + 0x7A0));
}

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005D20C);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005D364);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005D644);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005D7D8);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005D918);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005D9BC);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005DBC4);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005DD48);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005DF2C);

void func_8005E0E0(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005E0E8);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005E124);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005E19C);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005E214);

void func_8005E2D8(void) {
    s16 t;

    if (D_801FB46C != 0) {
        t = D_801FB46C + 1;
        D_801FB46C = t;
        switch (t) {
        case 0x3C:
            func_8001E450(0x401);
            func_8001ED54(D_80089624);
            break;
        case 0x78:
            func_8001E450(0x401);
            func_8001ED54(D_80089644);
            break;
        case 0xB4:
            func_8001E450(0x401);
            func_8001E450(0x402);
            D_801FB46C = 0;
            break;
        }
    }
}

void func_8005E398(void) {
    D_801FB468 = 0;
    if (D_800AA2DC != 0) {
        func_8005EE54();
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005E3CC);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005E4E4);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005E5C8);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005E60C);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005EE54);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005F12C);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005F208);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005F33C);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005F5B8);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005F9FC);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005FA8C);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005FB14);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005FEF4);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8006036C);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_800603FC);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_80060524);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_80060A7C);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_80060BA8);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_80060D44);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_80060DCC);
