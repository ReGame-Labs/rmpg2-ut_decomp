/* A file of the game's code, named after its first function until its contents are understood.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "game_8002A330.h"

s32 *func_8002A330(void) {
    return func_80025C08(D_8007C934);
}

void func_8002A354(s32 arg0) {
    if (arg0 == 1) {
        func_8001F39C(D_8007C944);
    } else {
        func_8001F39C(D_8007C95C);
    }
    D_801D85A4 = func_8002A330();
    func_8001EDB0();
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002A3A4);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002A4E8);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002A72C);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002AC34);

void func_8002AD84(void) {
    s32 *var_s0;
    s32 *var_s1;
    s32 var_s2;

    var_s2 = 0;
    var_s1 = D_801FB19C;
    var_s0 = D_801FB2DC;
    do {
        *var_s0 = 0;
        *var_s1 = func_8001EA78() & 0x7F;
        var_s1++;
        var_s2 += 1;
        var_s0++;
    } while (var_s2 < 0x50);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002ADE8);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002AF28);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002B0E0);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002B3AC);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002B640);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002B6E8);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002B878);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002B988);

UnkStruct7 *func_8002BA30(s32 arg0) {
    UnkStruct7 *temp_a1;

    temp_a1 = &D_801E0B78[arg0 & 0xFFFF];
    if (D_8007A7D4 & 1) {
        temp_a1->unk_08 = 0x440000;
    }
    return temp_a1;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002BA70);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002BAEC);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002BE30);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002BE78);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002BF24);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002BF70);

void func_8002BFE4(s32 arg0, UnkStruct1 *arg1) {
    s32 temp_s0;

    temp_s0 = func_8002BF70(arg1) & 0xFFFF;
    if (temp_s0 == 1) {
        if ((func_8004F7A4(arg1) & 0xFFFF) == temp_s0) {
            if ((u16) arg1->unk_16 < (u16) arg1->unk_00) {
                func_8002E278(arg0, arg1);
                return;
            }
            arg1->unk_14 = 0xE;
            goto block_8;
        }
        arg1->unk_14 = 0x11;
        if (D_801E1E40 == temp_s0) {
            D_801FA890 = 0xB4;
        } else {
            D_801E1E40 = (u16) D_801E1E40 - 1;
        }
block_8:
        arg1->unk_30 = 0;
        arg1->unk_16 = 0U;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002C0AC);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002C0F8);

void func_8002C19C(UnkStruct1 *arg0) {
    if ((u16) arg0->unk_2A < 0x18U) {
        func_8002EB00();
        return;
    }
    arg0->unk_14 = 0;
    arg0->unk_2A = 1U;
    arg0->unk_2C = 0;
    arg0->unk_2E = 0;
}

void func_8002C1E8(UnkStruct1 *arg0) {
    if (((u16) arg0->unk_30) != 0) {
        func_8002ED90();
        return;
    }
    arg0->unk_14 = 0;
    arg0->unk_0C = 0;
}

void func_8002C228(UnkStruct1 *arg0) {
    func_8002FEA4();
    arg0->unk_30 = 0;
    arg0->unk_16 = 0;
    arg0->unk_14 = 0xB;
}

void func_8002C25C(UnkStruct1 *arg0) {
    if (arg0->unk_16 != arg0->unk_00) {
        func_8002E854();
        func_80030B5C(arg0);
        return;
    }
    arg0->unk_14 = 0x10;
    arg0->unk_30 = 0;
    arg0->unk_16 = 0U;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002C2B4);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002C32C);

void func_8002C3C4(UnkStruct1 *arg0) {
    u16 temp_v0;

    temp_v0 = arg0->unk_82;
    if (temp_v0 != 0) {
        arg0->unk_82 = (u16) (temp_v0 - 1);
        return;
    }
    if (arg0->unk_00 == arg0->unk_16) {
        func_8002F084(arg0);
        return;
    }
    func_8002E854(arg0);
    func_80030B5C(arg0);
}

void func_8002C430(UnkStruct1 *arg0) {
    if (arg0->unk_90 != 0) {
        arg0->unk_14 = 4;
        return;
    }
    if (arg0->unk_36 > arg0->unk_38) {
        arg0->unk_14 = 0;
        arg0->unk_36 = 0;
        arg0->unk_38 = 0;
        func_80025BBC(arg0);
        if (arg0->unk_34 == 1) {
            arg0->unk_34 = 2;
            return;
        }
        arg0->unk_34 = 1;
        return;
    }
    func_8002E9F8(arg0);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002C4B8);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002C6A0);

void func_8002C738(UnkStruct1 *arg0) {
    arg0->unk_14 = 0x10;
    func_8002C6A0();
}

void func_8002C75C(UnkStruct1 *arg0) {
    UnkStruct4 *temp_s1;

    temp_s1 = arg0->unk_98;
    D_800AA268.obj = temp_s1;
    if (((u16) arg0->unk_14) == 6) {
        arg0->unk_14 = 8U;
    } else {
        arg0->unk_14 = 0U;
    }
    if (arg0->unk_58 != 3) {
        func_8001F724(5);
        func_8001E698(temp_s1, arg0->unk_5C);
    }
}

void func_8002C7D0(UnkStruct1 *arg0) {
    if (arg0->unk_84 == 0) {
        arg0->unk_14 = 6;
        func_8002C75C(arg0);
        return;
    }
    arg0->unk_14 = 8;
    func_8002C738(arg0);
}

void func_8002C814(UnkStruct1 *arg0) {
    void *temp_a0;

    func_8001F724(5);
    temp_a0 = arg0->unk_84;
    arg0->unk_14 = 0;
    if (temp_a0 != NULL) {
        func_8001E698(temp_a0, D_80011E18);
    }
}

void func_8002C858(UnkStruct1 *arg0) {
    u16 temp_v0;
    u16 temp_v1;

    temp_v0 = arg0->unk_82;
    if (temp_v0 != 0) {
        arg0->unk_82 = (u16) (temp_v0 - 1);
        return;
    }
    temp_v1 = arg0->unk_00;
    if (temp_v1 == arg0->unk_16) {
        func_8002F084();
        return;
    }
    arg0->unk_16 = temp_v1;
    func_8002C6A0();
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002C8B4);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002CA8C);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002CBF4);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002CD24);

void func_8002CE40(UnkStruct2 *arg0, s32 arg1) {
    if ((arg0->unk_00 != 0) && ((u16) arg0->unk_04 >= 2U)) {
        arg0->unk_0E = 1;
        arg0->unk_14 = arg1;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002CE74);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002CFAC);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002D0C0);

void func_8002D144(s32 arg0, UnkStruct1 *arg1) {
    s32 temp_s2;

    temp_s2 = D_800AA268.obj;
    if ((D_800AA2DC == 0) || !(D_8007BD78 & 0x40)) {
        if (arg1->unk_78 == 0) {
            func_8002F5B0(arg0, arg1);
            func_8003089C(5, arg0);
        } else {
            func_8002D228(arg0, arg1);
        }
        arg1->unk_14 = 1;
        arg1->unk_78 = (u16) (arg1->unk_78 + 1);
        D_800AA268.obj = temp_s2;
    }
}

void func_8002D1F4(s32 arg0, UnkStruct1 *arg1) {
    if (arg1->unk_06 == 0) {
        func_8002D370(arg0, arg1, arg1->unk_08);
    }
}

void func_8002D228(s32 arg0, UnkStruct1 *arg1) {
    UnkStruct2 *temp_s0;

    temp_s0 = arg1->unk_70;
    temp_s0--;
    if (temp_s0->unk_04 >= 2U) {
        if (temp_s0->unk_06 == 0) {
            func_8002E440(arg0, temp_s0);
            return;
        }
        if (!(func_8002D2CC(temp_s0->unk_04, arg1) & 0xFFFF)) {
            func_8002FB6C(arg0, temp_s0, arg1);
            return;
        }
        func_8002D448(arg0, arg1);
    }
}

s32 func_8002D2CC(s32 arg0, UnkStruct1 *arg1) {
    if ((arg1->unk_88 != 0) || (arg1->unk_20 == D_80011BA4) || ((arg1->unk_24 != 0) && ((s16) ((u16) arg1->unk_24 - 1) == (arg0 & 0xFFFF))) || ((arg1->unk_28 != 0) && ((s16) ((u16) arg1->unk_28 - 1) == (arg0 & 0xFFFF))) || ((arg1->unk_26 != 0) && ((s16) ((u16) arg1->unk_26 - 1) == (arg0 & 0xFFFF)))) {
        return 1;
    }
    return arg1->unk_76 != 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002D370);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002D448);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002D5B8);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002D844);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002D9F8);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002DAAC);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002DB3C);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002DBF4);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002DE08);

void func_8002DF64(s32 arg0, UnkStruct1 *arg1) {
    if (arg1->unk_00 < 6U) {
        func_8002DFA8();
        return;
    }
    func_8002E148();
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002DFA8);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002E0C8);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002E148);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002E278);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002E348);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002E440);

void func_8002E5F4(s32 arg0) {
    func_8002E658(arg0 & 0xFFFF);
}

void func_8002E614(s32 arg0) {
    s32 *temp_v0;

    temp_v0 = func_8002E658(arg0 & 0xFFFF);
    if ((temp_v0 != NULL) && (*temp_v0 != 0)) {
        func_8003C894(temp_v0);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002E658);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002E854);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002E9A4);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002E9F8);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002EB00);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002EBD8);

void func_8002ECA0(UnkStruct1 *arg0) {
    u16 var_s1;
    UnkStruct2 *var_s0;

    func_8002E278(D_800AA260, arg0);
    func_8003CD08(arg0);
    func_8003D60C(arg0);
    var_s0 = &arg0->unk_EC;
    var_s1 = arg0->unk_00 - 1;
    do {
        func_80025898(var_s0);
        func_80025B7C(var_s0);
        var_s0++;
    } while (--var_s1 != 0);
    arg0->unk_14 = 0x10;
}

void func_8002ED28(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002ED30);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002ED90);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002EE14);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002F01C);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002F084);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002F100);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002F474);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002F558);

void func_8002F5B0(s32 arg0, UnkStruct1 *arg1) {
    s32 temp_a0;
    s32 temp_s1;
    s32 temp_s2;
    UnkStruct2 *temp_s0;

    temp_s0 = arg1->unk_70;
    temp_s2 = D_800AA268.obj;
    temp_s1 = arg1->unk_64;
    if (temp_s0->unk_06 == 0) {
        func_80030698(0, arg0, temp_s0);
        temp_a0 = temp_s0->unk_00;
        if (temp_a0 != 0) {
            func_8001E698(temp_a0, temp_s1);
            temp_s0->unk_06 = 1U;
        }
    }
    D_800AA268.obj = temp_s2;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002F630);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002F65C);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002F688);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002F898);

void func_8002F9BC(void) {
    UnkStruct2 *temp_s0;

    temp_s0 = D_800AA268.obj->unk_90;
    func_8001E4B0(D_800AA268.obj);
    func_80025B7C(temp_s0);
}

void func_8002F9F4(UnkStruct2 *arg0) {
    arg0->unk_20 = 1;
    arg0->unk_38 = 1;
    if ((arg0->unk_08)->unk_02 != 2) {
        arg0->unk_50 = 1;
    }
}

void func_8002FA20(s32 arg0, UnkStruct1 *arg1) {
    if ((arg1->unk_06 == 0) && (arg1->unk_12 >= 5U) && (arg1->unk_2A >= 5U) &&
        ((arg1->unk_08->unk_02 == 2) || (arg1->unk_42 >= 5U))) {
        func_8002FDC0();
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002FAA4);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002FB38);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002FB6C);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002FD24);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002FDC0);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002FEA4);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002FF74);

void func_800300A0(UnkStruct1 *arg0, UnkStruct1 *arg1) {
    if ((arg0 != NULL) && (arg1->unk_80 != 0)) {
        if (arg0->unk_1A >= 0xF0) {
            func_800300F4();
            return;
        }
        arg0->unk_1A = (s16) ((u16) arg0->unk_1A + 3);
    }
}

void func_800300F4(void) {
    func_80030114();
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80030114);

s32 func_80030268(s16 arg0, s32 arg1, UnkStruct8 *arg2) {
    s32 var_v1;

    if (arg2->unk_DC != 0) {
        var_v1 = arg2->unk_F4 - arg0;
        if (var_v1 < 0) {
            var_v1 = -var_v1;
        }
        return (var_v1 << 0x10) <= (arg1 << 0x10);
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_800302AC);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80030338);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_800303DC);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8003044C);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8003047C);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_800305C8);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80030698);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80030754);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80030834);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8003089C);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_800308EC);

void func_800309AC(s16 arg0, UnkStruct5 *arg1) {
    UnkStruct3 *temp_a0;
    UnkStruct1 *temp_v1;
    UnkStruct1 *temp_v1_2;

    temp_v1 = arg1->unk_00;
    if (temp_v1 != NULL) {
        temp_v1->unk_16 = (u16) (temp_v1->unk_16 + arg0);
        func_800308EC(arg0, arg1->unk_0C);
        func_800308EC(arg0, arg1->unk_24);
        func_800308EC(arg0, arg1->unk_3C);
        temp_a0 = arg1->unk_08->unk_18;
        if ((temp_a0 != NULL) && (temp_a0->unk_0A == arg1->unk_04)) {
            temp_v1_2 = temp_a0->unk_00;
            if (temp_v1_2 != NULL) {
                temp_v1_2->unk_16 = (u16) (temp_v1_2->unk_16 + arg0);
            }
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80030A70);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80030B00);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80030B5C);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80030BAC);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80030C7C);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80030CD4);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80030D14);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80030D74);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80030E04);

void func_80030FA4(void) {
    void *temp_a0;
    s32 temp_s2;
    UnkStruct2 *temp_s0;
    UnkStruct1 *temp_s1;

    temp_s0 = D_800AA268.obj->unk_90;
    temp_s2 = D_800AA268.obj->unk_94;
    temp_s1 = temp_s0->unk_08;
    if ((temp_s2 != 0) && (temp_s1 != NULL)) {
        if (((u16) temp_s1->unk_14) < 9U) {
            temp_s1->unk_10 = (u16) (temp_s1->unk_10 + 8);
            func_800257C4(temp_s0);
            func_800256B0(temp_s0);
            func_8002F630(temp_s1, temp_s2, temp_s0);
        }
    } else {
        func_8003CD5C(temp_s0);
        func_800256CC(temp_s0);
        func_800257C4(temp_s0);
        temp_a0 = temp_s0->unk_00;
        if (temp_a0 != NULL) {
            func_8001E4B0(temp_a0);
        }
        func_80025B7C(temp_s0);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80031074);

void func_8003111C(s32 arg0, UnkStruct1 *arg1) {
    if (((u8 *) arg1 >= D_801E0D98) && ((u8 *) arg1 <= D_801E0D98 + 0xCC0)) {
        arg1->unk_26 = (u16) (((u16) arg1->unk_26) + arg0);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80031154);

void func_80031224(void) {
    UnkStruct1 *temp_v0;

    func_8001F724(5);
    temp_v0 = func_8003D1F8((D_800AA268.obj->unk_90)->unk_10);
    if (((u16) temp_v0->unk_14) < 3U) {
        temp_v0->unk_14 = 0xCU;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80031280);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80031364);

s32 func_80031420(s32 arg0, s32 arg1) {
    return arg1 + ((arg0 & 0xFFFF) * 0x54) + 0x44;
}

void func_80031444(void) {
    func_80031B10();
    func_80031A3C();
    func_800245F8();
    func_8003149C();
    func_800315D8();
    func_80031690();
    func_8002A3A4();
    func_8002AD84();
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8003149C);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_800315D8);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80031690);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80031714);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8003197C);

void func_80031A3C(void) {
    D_801D8864 = *func_80025C08(D_800838A0);
}

void func_80031A68(void) {
    if ((D_801D37BC == 0) && (D_801D37C0 == 0) && (D_801D857C != 0)) {
        func_80020BA0(D_801D857C, 0x8002, D_800AA268.obj);
        D_801D857C = 0;
        func_8001E7A0();
    }
}

void func_80031AC8(void) {
    if ((D_801D37BC == 0) && (D_801D37C0 == 0)) {
        D_800AA268.obj->unk_44 = *D_800AA268.obj->unk_5C;
    }
}

void func_80031B10(void) {
    D_801FA98C = 0;
    D_801FAC90 = 0;
    D_801FAC8C = 0;
    D_801FA990 = 0;
    D_801D37BC = 0;
    D_801D37C0 = 0;
    D_801D87B0 = 0;
    D_801D376C = 0;
    D_801D37B8 = 0;
    D_801D87B4 = 0;
    D_801FAC84 = 0;
    D_801F9AB0 = 0;
}

void func_80031B74(s32 arg0) {
    func_80031CB4(D_8007D1E8, arg0);
}

void func_80031B9C(s32 arg0) {
    func_80031CB4(D_8007D0B8, arg0);
}

void func_80031BC4(s32 arg0) {
    func_80031CB4(D_8007D104, arg0);
}

void func_80031BEC(s32 arg0) {
    func_80031CB4(D_8007D150, arg0);
}

void func_80031C14(s32 arg0) {
    func_80031CB4(D_8007D19C, arg0);
}

void func_80031C3C(s32 arg0) {
    func_80031CB4(D_8007D364, arg0);
}

void func_80031C64(s32 arg0) {
    func_80031CB4(D_8007D3B0, arg0);
}

void func_80031C8C(s32 arg0) {
    func_80031CB4(D_8007D3FC, arg0);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80031CB4);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80031EC0);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80031F20);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80031F5C);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80031F98);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80031FD4);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80032008);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80032064);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8003212C);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_800322AC);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_800322E8);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80032350);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80032530);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80032630);

void func_80032668(s32 arg0) {
    func_80031CB4(D_8007D280, arg0);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80032690);

void func_80032710(s32 arg0) {
    func_80031CB4(D_8007D234, arg0);
}

void func_80032738(s32 arg0) {
    func_80031CB4(D_8007D2CC, arg0);
}

void func_80032760(s32 arg0) {
    func_80031CB4(D_8007D318, arg0);
}

void func_80032788(void) {
    func_8003EB5C(D_80091B98, D_800AA268.obj);
}

void func_800327B4(void) {
    func_8003EB5C(D_80091BC8, D_800AA268.obj);
}

void func_800327E0(void) {
    func_8003EB5C(D_80091BF8, D_800AA268.obj);
}

void func_8003280C(void) {
    func_8003EB5C(D_80091C04, D_800AA268.obj);
}

void func_80032838(void) {
    func_8003EB5C(D_80091C30, D_800AA268.obj);
}

void func_80032864(void) {
    func_8003EB5C(D_80091C48, D_800AA268.obj);
}

void func_80032890(void) {
    func_8003EB5C(D_80091C88, D_800AA268.obj);
}

void func_800328BC(void) {
    func_8003EB5C(D_80091CC0, D_800AA268.obj);
}

void func_800328E8(void) {
    func_8003EB5C(D_80091CF8, D_800AA268.obj);
}

void func_80032914(void) {
    func_8003EB5C(D_80091D38, D_800AA268.obj);
}

void func_80032940(void) {
    func_8003EB5C(D_80091D68, D_800AA268.obj);
}

void func_8003296C(void) {
    func_8003EB5C(D_80091DC4, D_800AA268.obj);
}

void func_80032998(void) {
    func_8003EB5C(D_80091D90, D_800AA268.obj);
}

void func_800329C4(void) {
    func_8003EB5C(D_80091DD0, D_800AA268.obj);
}

void func_800329F0(void) {
    func_8003EB5C(D_80091E04, D_800AA268.obj);
}

void func_80032A1C(void) {
    func_8003EB5C(D_80091E34, D_800AA268.obj);
}

void func_80032A48(void) {
    func_8003EB5C(D_80091E40, D_800AA268.obj);
}

void func_80032A74(void) {
    func_8003EB5C(D_80091E80, D_800AA268.obj);
}

void func_80032AA0(void) {
    func_8003EB5C(D_80091EF0, D_800AA268.obj);
}

void func_80032ACC(void) {
    func_8003EB5C(D_80091F30, D_800AA268.obj);
}

void func_80032AF8(void) {
    func_8003EB5C(D_80091F68, D_800AA268.obj);
}

void func_80032B24(void) {
    func_8003EB5C(D_80091FA0, D_800AA268.obj);
}

void func_80032B50(void) {
    func_8003EB5C(D_80091FE0, D_800AA268.obj);
}

void func_80032B7C(void) {
    func_8003EB5C(D_80092010, D_800AA268.obj);
}

void func_80032BA8(void) {
    func_8003EB5C(D_8009206C, D_800AA268.obj);
}

void func_80032BD4(void) {
    func_8003EB5C(D_80092038, D_800AA268.obj);
}

void func_80032C00(void) {
    func_8003EB5C(D_80092078, D_800AA268.obj);
}

void func_80032C2C(void) {
    func_8003EB5C(D_800920A8, D_800AA268.obj);
}

void func_80032C58(void) {
    func_8003EB5C(D_800920D8, D_800AA268.obj);
}

void func_80032C84(void) {
    func_8003EB5C(D_800920E4, D_800AA268.obj);
}

void func_80032CB0(void) {
    func_8003EB5C(D_80092124, D_800AA268.obj);
}

void func_80032CDC(void) {
    func_8003EB5C(D_8009213C, D_800AA268.obj);
}

void func_80032D08(void) {
    func_8003EB5C(D_80092164, D_800AA268.obj);
}

void func_80032D34(void) {
    func_8003EB5C(D_8009219C, D_800AA268.obj);
}

void func_80032D60(void) {
    func_8003EB5C(D_800921D4, D_800AA268.obj);
}

void func_80032D8C(void) {
    func_8003EB5C(D_80092214, D_800AA268.obj);
}

void func_80032DB8(void) {
    func_8003EB5C(D_80092244, D_800AA268.obj);
}

void func_80032DE4(void) {
    func_8003EB5C(D_800922A0, D_800AA268.obj);
}

void func_80032E10(void) {
    func_8003EB5C(D_8009226C, D_800AA268.obj);
}

void func_80032E3C(void) {
    func_8003EB5C(D_800922AC, D_800AA268.obj);
}

void func_80032E68(void) {
    func_8003EB5C(D_800922D4, D_800AA268.obj);
}

void func_80032E94(void) {
    func_8003EB5C(D_80092304, D_800AA268.obj);
}

void func_80032EC0(void) {
    func_8003EB5C(D_80092310, D_800AA268.obj);
}

void func_80032EEC(void) {
    func_8003EB5C(D_80092338, D_800AA268.obj);
}

void func_80032F18(void) {
    func_8003EB5C(D_80092350, D_800AA268.obj);
}

void func_80032F44(void) {
    func_8003EB5C(D_80092384, D_800AA268.obj);
}

void func_80032F70(void) {
    func_8003EB5C(D_800923BC, D_800AA268.obj);
}

void func_80032F9C(void) {
    func_8003EB5C(D_800923F4, D_800AA268.obj);
}

void func_80032FC8(void) {
    func_8003EB5C(D_80092404, D_800AA268.obj);
}

void func_80032FF4(void) {
    func_8003EB5C(D_8009245C, D_800AA268.obj);
}

void func_80033020(void) {
    func_8003EB5C(D_8009248C, D_800AA268.obj);
}

void func_8003304C(void) {
    func_8003EB5C(D_800924E8, D_800AA268.obj);
}

void func_80033078(void) {
    func_8003EB5C(D_800924B4, D_800AA268.obj);
}

void func_800330A4(void) {
    func_8003EB5C(D_800924F4, D_800AA268.obj);
}

void func_800330D0(void) {
    func_8003EB5C(D_80092534, D_800AA268.obj);
}

void func_800330FC(void) {
    func_8003EB5C(D_80092574, D_800AA268.obj);
}

void func_80033128(void) {
    func_8003EB5C(D_80092580, D_800AA268.obj);
}

void func_80033154(void) {
    func_8003EB5C(D_800925C0, D_800AA268.obj);
}

void func_80033180(void) {
    func_8003EB5C(D_800925D8, D_800AA268.obj);
}

void func_800331AC(void) {
    func_8003EB5C(D_80092604, D_800AA268.obj);
}

void func_800331D8(void) {
    func_8003EB5C(D_8009262C, D_800AA268.obj);
}

void func_80033204(void) {
    func_8003EB5C(D_80092654, D_800AA268.obj);
}

void func_80033230(void) {
    func_8003EB5C(D_8009268C, D_800AA268.obj);
}

void func_8003325C(void) {
    func_8003EB5C(D_800926B4, D_800AA268.obj);
}

void func_80033288(void) {
    func_8003EB5C(D_80092710, D_800AA268.obj);
}

void func_800332B4(void) {
    func_8003EB5C(D_800926DC, D_800AA268.obj);
}

void func_800332E0(void) {
    func_8003EB5C(D_8009271C, D_800AA268.obj);
}

void func_8003330C(void) {
    func_8003EB5C(D_80092754, D_800AA268.obj);
}

void func_80033338(void) {
    func_8003EB5C(D_8009278C, D_800AA268.obj);
}

void func_80033364(void) {
    func_8003EB5C(D_80092798, D_800AA268.obj);
}

void func_80033390(void) {
    func_8003EB5C(D_800927D4, D_800AA268.obj);
}

void func_800333BC(void) {
    func_8003EB5C(D_800927EC, D_800AA268.obj);
}

void func_800333E8(void) {
    func_8003EB5C(D_80092818, D_800AA268.obj);
}

void func_80033414(void) {
    func_8003EB5C(D_80092840, D_800AA268.obj);
}

void func_80033440(void) {
    func_8003EB5C(D_80092868, D_800AA268.obj);
}

void func_8003346C(void) {
    func_8003EB5C(D_800928A0, D_800AA268.obj);
}

void func_80033498(void) {
    func_8003EB5C(D_800928C8, D_800AA268.obj);
}

void func_800334C4(void) {
    func_8003EB5C(D_80092924, D_800AA268.obj);
}

void func_800334F0(void) {
    func_8003EB5C(D_800928F0, D_800AA268.obj);
}

void func_8003351C(void) {
    func_8003EB5C(D_80092930, D_800AA268.obj);
}

void func_80033548(void) {
    func_8003EB5C(D_8009296C, D_800AA268.obj);
}

void func_80033574(void) {
    func_8003EB5C(D_800929A4, D_800AA268.obj);
}

void func_800335A0(void) {
    func_8003EB5C(D_800929B0, D_800AA268.obj);
}

void func_800335CC(void) {
    func_8003EB5C(D_800929D8, D_800AA268.obj);
}

void func_800335F8(void) {
    func_8003EB5C(D_80092A64, D_800AA268.obj);
}

void func_80033624(void) {
    func_8003EB5C(D_80092A8C, D_800AA268.obj);
}

void func_80033650(void) {
    func_8003EB5C(D_80092AB4, D_800AA268.obj);
}

void func_8003367C(void) {
    func_8003EB5C(D_80092ADC, D_800AA268.obj);
}

void func_800336A8(void) {
    func_8003EB5C(D_80092B1C, D_800AA268.obj);
}

void func_800336D4(void) {
    func_8003EB5C(D_80092B54, D_800AA268.obj);
}

void func_80033700(void) {
    func_8003EB5C(D_80092B7C, D_800AA268.obj);
}

void func_8003372C(void) {
    func_8003EB5C(D_80092BD8, D_800AA268.obj);
}

void func_80033758(void) {
    func_8003EB5C(D_80092BA4, D_800AA268.obj);
}

void func_80033784(void) {
    func_8003EB5C(D_800934A0, D_800AA268.obj);
}

void func_800337B0(void) {
    func_8003EB5C(D_800934DC, D_800AA268.obj);
}

void func_800337DC(void) {
    func_8003EB5C(D_80093538, D_800AA268.obj);
}

void func_80033808(void) {
    func_8003EB5C(D_80093548, D_800AA268.obj);
}

void func_80033834(void) {
    func_8003EB5C(D_8009363C, D_800AA268.obj);
}

void func_80033860(void) {
    func_8003EB5C(D_80093698, D_800AA268.obj);
}

void func_8003388C(void) {
    func_8003EB5C(D_80093768, D_800AA268.obj);
}

void func_800338B8(void) {
    func_8003EB5C(D_800937A8, D_800AA268.obj);
}

void func_800338E4(void) {
    func_8003EB5C(D_8009382C, D_800AA268.obj);
}

void func_80033910(void) {
    func_8003EB5C(D_800937F4, D_800AA268.obj);
}

void func_8003393C(void) {
    func_8003EB5C(D_80093864, D_800AA268.obj);
}

void func_80033968(void) {
    func_8003EB5C(D_8009388C, D_800AA268.obj);
}

void func_80033994(void) {
    func_8003EB5C(D_800937E8, D_800AA268.obj);
}

void func_800339C0(void) {
    func_8003EB5C(D_800938AC, D_800AA268.obj);
}

void func_800339EC(void) {
    func_8003EB5C(D_80092BE4, D_800AA268.obj);
}

void func_80033A18(void) {
    func_8003EB5C(D_80092C20, D_800AA268.obj);
}

void func_80033A44(void) {
    func_8003EB5C(D_80092C7C, D_800AA268.obj);
}

void func_80033A70(void) {
    func_8003EB5C(D_80092C8C, D_800AA268.obj);
}

void func_80033A9C(void) {
    func_8003EB5C(D_80092D88, D_800AA268.obj);
}

void func_80033AC8(void) {
    func_8003EB5C(D_80092DE4, D_800AA268.obj);
}

void func_80033AF4(void) {
    func_8003EB5C(D_80092EB4, D_800AA268.obj);
}

void func_80033B20(void) {
    func_8003EB5C(D_80092EDC, D_800AA268.obj);
}

void func_80033B4C(void) {
    func_8003EB5C(D_80092F48, D_800AA268.obj);
}

void func_80033B78(void) {
    func_8003EB5C(D_80092F10, D_800AA268.obj);
}

void func_80033BA4(void) {
    func_8003EB5C(D_80092F80, D_800AA268.obj);
}

void func_80033BD0(void) {
    func_8003EB5C(D_80092FA8, D_800AA268.obj);
}

void func_80033BFC(void) {
    func_8003EB5C(D_80092F04, D_800AA268.obj);
}

void func_80033C28(void) {
    func_8003EB5C(D_80092FC8, D_800AA268.obj);
}

void func_80033C54(void) {
    func_8003EB5C(D_80093008, D_800AA268.obj);
}

void func_80033C80(void) {
    func_8003EB5C(D_80093064, D_800AA268.obj);
}

void func_80033CAC(void) {
    func_8003EB5C(D_800930BC, D_800AA268.obj);
}

void func_80033CD8(void) {
    func_8003EB5C(D_800930C8, D_800AA268.obj);
}

void func_80033D04(void) {
    func_8003EB5C(D_8009314C, D_800AA268.obj);
}

void func_80033D30(void) {
    func_8003EB5C(D_8009321C, D_800AA268.obj);
}

void func_80033D5C(void) {
    func_8003EB5C(D_800932F4, D_800AA268.obj);
}

void func_80033D88(void) {
    func_8003EB5C(D_80093324, D_800AA268.obj);
}

void func_80033DB4(void) {
    func_8003EB5C(D_80093360, D_800AA268.obj);
}

void func_80033DE0(void) {
    func_8003EB5C(D_80093370, D_800AA268.obj);
}

void func_80033E0C(void) {
    func_8003EB5C(D_80093398, D_800AA268.obj);
}

void func_80033E38(void) {
    func_8003EB5C(D_800933B0, D_800AA268.obj);
}

void func_80033E64(void) {
    func_8003EB5C(D_80093354, D_800AA268.obj);
}

void func_80033E90(void) {
    func_8003EB5C(D_800938EC, D_800AA268.obj);
}

void func_80033EBC(void) {
    func_8003EB5C(D_8009393C, D_800AA268.obj);
}

void func_80033EE8(void) {
    func_8003EB5C(D_80093988, D_800AA268.obj);
}

void func_80033F14(void) {
    func_8003EB5C(D_80093994, D_800AA268.obj);
}

void func_80033F40(void) {
    func_8003EB5C(D_800939CC, D_800AA268.obj);
}

void func_80033F6C(void) {
    func_8003EB5C(D_80093A1C, D_800AA268.obj);
}

void func_80033F98(void) {
    func_8003EB5C(D_80093AD4, D_800AA268.obj);
}

void func_80033FC4(void) {
    func_8003EB5C(D_80093AFC, D_800AA268.obj);
}

void func_80033FF0(void) {
    func_8003EB5C(D_80093B24, D_800AA268.obj);
}

void func_8003401C(void) {
    func_8003EB5C(D_80093B3C, D_800AA268.obj);
}

void func_80034048(void) {
    func_8003EB5C(D_80093B74, D_800AA268.obj);
}

void func_80034074(void) {
    func_8003EB5C(D_80093B9C, D_800AA268.obj);
}

void func_800340A0(void) {
    func_8003EB5C(D_8009397C, D_800AA268.obj);
}

void func_800340CC(void) {
    func_8003EB5C(D_80093BBC, D_800AA268.obj);
}

void func_800340F8(void) {
    func_8003EB5C(D_80093C00, D_800AA268.obj);
}

void func_80034124(void) {
    func_8003EB5C(D_80093C28, D_800AA268.obj);
}

void func_80034150(void) {
    func_8003EB5C(D_80093C50, D_800AA268.obj);
}

void func_8003417C(void) {
    func_8003EB5C(D_80093C68, D_800AA268.obj);
}

void func_800341A8(void) {
    func_8003EB5C(D_80093C80, D_800AA268.obj);
}

void func_800341D4(void) {
    func_8003EB5C(D_80093CA4, D_800AA268.obj);
}

void func_80034200(void) {
    func_8003EB5C(D_80093CD0, D_800AA268.obj);
}

void func_8003422C(void) {
    func_8003EB5C(D_80093D10, D_800AA268.obj);
}

void func_80034258(void) {
    func_8003EB5C(D_80093D50, D_800AA268.obj);
}

void func_80034284(void) {
    func_8003EB5C(D_80093D60, D_800AA268.obj);
}

void func_800342B0(void) {
    func_8003EB5C(D_80093DD8, D_800AA268.obj);
}

void func_800342DC(void) {
    func_8003EB5C(D_80093E30, D_800AA268.obj);
}

void func_80034308(void) {
    func_8003EB5C(D_80093EF8, D_800AA268.obj);
}

void func_80034334(void) {
    func_8003EB5C(D_80093C5C, D_800AA268.obj);
}

void func_80034360(void) {
    func_8003EB5C(D_80093F10, D_800AA268.obj);
}

void func_8003438C(void) {
    (D_800AA268.obj->unk_90)->unk_36 = 1;
}

void func_800343A8(void) {
    (D_800AA268.obj->unk_90)->unk_36 = 0;
}

void func_800343C0(void) {
    func_8003EB5C(D_80093F44, D_800AA268.obj);
}

void func_800343EC(void) {
    func_8003EB5C(D_80093F44, D_800AA268.obj);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80034418);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_800344B8);
