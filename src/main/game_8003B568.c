/* A file of the game's code, named after its first function until its contents are understood.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "game_8003B568.h"

void func_8003B568(void) {
    UnkStructB1 *var_s0;
    u16 temp_v0_2;
    u16 var_s1;
    u32 temp_v0;

    var_s1 = D_801E29B0;
    var_s0 = D_801FA9BC;
    temp_v0 = var_s1 & 0xFFFF;
    if (temp_v0 != 0) {
        if (temp_v0 >= 9U) {
            var_s1 = 8;
        }
        do {
            func_8003B5D0(var_s0);
            temp_v0_2 = var_s1 - 1;
            var_s1 = temp_v0_2;
            var_s0++;
        } while (temp_v0_2 & 0xFFFF);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003B5D0);

INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003B68C);

INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003B6E0);

INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003B9A0);

INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003B9C8);

INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003BAB0);

INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003BD48);

INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003BE34);

INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003BF34);

void func_8003C080(void) {
    (D_800AA248.unk_20->unk_90)->unk_06 = 0;
    func_8004CFC0();
}

void func_8003C0AC(void) {
    (D_800AA248.unk_20->unk_90)->unk_0C = 1;
}

void func_8003C0C8(void) {
    (D_800AA248.unk_20->unk_90)->unk_1C = 0;
}

void func_8003C0E0(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003C0E8);

INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003C130);

INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003C1C0);

INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003C2D4);

INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003C344);

INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003C3B0);

void func_8003C674(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003C67C);

INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003C858);

void func_8003C894(void **arg0) {
    void *temp_a0;

    temp_a0 = *arg0;
    if (temp_a0 != NULL) {
        func_8001E4B0(temp_a0);
    }
    func_8003CCC0(arg0);
}

void func_8003C8D4(UnkStructB1 *arg0) {
    void *temp_a0;

    temp_a0 = arg0->unk_00;
    if (temp_a0 != NULL) {
        if (arg0->unk_1A != 0) {
            func_8003C934(arg0);
            return;
        }
        func_8001E4B0(temp_a0);
        goto block_4;
    }
block_4:
    func_8003CCC0(arg0);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003C934);

void func_8003C9E8(UnkStructB1 *arg0) {
    if (arg0->unk_1A == 0xA) {
        func_8003CA28(arg0);
        return;
    }
    func_8003CA70();
}

void func_8003CA28(UnkStructB1 *arg0) {
    UnkStruct1 *temp_v1;

    temp_v1 = arg0->unk_14;
    if ((temp_v1 != NULL) && ((u32) (arg0->unk_06 - 0x45) < 2U)) {
        func_8003CADC(temp_v1);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003CA70);

void func_8003CADC(UnkStruct1 *arg0) {
    s16 var_v1;

    func_8001F724(3);
    var_v1 = 0x294;
    if (arg0->unk_186 != 0) {
        var_v1 = 0x528;
        arg0->unk_186 = 0U;
    }
    arg0->unk_140 = var_v1;
    arg0->unk_56 = 1;
    func_8005DD48(arg0);
}

void func_8003CB30(UnkStruct1 *arg0) {
    func_8001F724(3);
    arg0->unk_144 = 0x294;
    arg0->unk_56 = 3;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003CB68);

INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003CBE0);

INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003CC84);

void func_8003CCA8(void) {
    D_801E1C80 += 0x258;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003CCC0);
