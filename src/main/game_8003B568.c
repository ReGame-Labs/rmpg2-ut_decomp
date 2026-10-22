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

void func_8003B68C(void) {
    u16 n = 8;
    UnkStructB1 *p = D_801FA9BC;

    do {
        func_8003B9A0(p);
        p++;
    } while (--n != 0);
    D_801E29B0 = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003B6E0);

void func_8003B9A0(UnkStructB1 *p) {
    memset(p, 0, sizeof(UnkStructB1));
    D_801E29B0 = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003B9C8);

INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003BAB0);

#ifdef NON_MATCHING
/* 85 %: the original loads the limit once into v0 and copies it to v1 (a separate variable from the tested
 * value); every form tried loads it once into the variable or twice. */
void func_8003BD48(UnkStructB1 *b) {
    s32 limit;
    u16 x;
    u16 d;
    UnkStruct4 *obj;

    if (b->unk_08 == 2) {
        if (D_801FAC84 != 0) {
            limit = D_801FAC84;
            obj = D_800AA268.obj;
            x = obj->unk_16;
            if (obj->unk_22 & 0x10) {
                d = (u16) D_801F9AB0 - x + 0x31;
            } else {
                d = (u16) (limit - x);
            }
            if (d < 0x32) {
                func_8003BF34(obj, b, x);
            }
        } else if (D_801D37BC == 0) {
            if (D_801FA98C != 0) {
                limit = D_801FA98C;
                obj = D_800AA268.obj;
                x = obj->unk_16;
                if (obj->unk_22 & 0x10) {
                    d = (u16) D_801FA990 - x + 0x31;
                } else {
                    d = (u16) (limit - x);
                }
                if (d < 0x32) {
                    func_8003BF34(obj, b, x);
                }
            }
        }
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003BD48);
#endif

INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003BE34);

#ifdef NON_MATCHING
/* 98.8 %: the first test's second range check masks `st - 0xD` to 16 bits (andi) in the original; the same
 * expression in a local, in the field, or as a switch with case ranges drops the mask. */
void func_8003BF34(UnkStruct4 *obj, UnkStructB1 *b, u16 x) {
    u8 *anim = NULL;
    u16 flags;
    UnkStruct4 *o;

    if ((u32) (b->unk_06 - 0x16) < 2U || ((b->unk_06 - 0xD) & 0xFFFF) < 5U) {
        b->unk_0A = 1;
        return;
    }
    flags = obj->unk_22;
    obj->unk_22 = (flags & 0x10) ? (flags & 0xFFEF) : (flags | 0x10);
    b->unk_34 = -b->unk_34;
    obj->unk_0C = -obj->unk_0C;
    switch (b->unk_06) {
    case 6:
        anim = D_8008A4A0;
        b->unk_06 = 7;
        break;
    case 7:
        anim = D_8008A494;
        b->unk_06 = 6;
        break;
    case 8:
        anim = D_8008A4C4;
        b->unk_06 = 9;
        break;
    case 9:
        anim = D_8008A4B8;
        b->unk_06 = 8;
        break;
    }
    if (anim != NULL) {
        func_8001E698(b->unk_00, anim);
    }
    o = b->unk_40;
    if (o != NULL) {
        o->unk_22 = obj->unk_22;
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003BF34);
#endif

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

void func_8003C130(void) {
    UnkStructB2 *p = D_801D3824;
    u16 n = D_801D8738;
    UnkStruct4 *saved = D_800AA268.obj;

    if (n != 0) {
        do {
            if (p->unk_04 != 0) {
                func_8003C1C0(p->unk_1C, p);
            }
            p++;
        } while (--n != 0);
    }
    D_800AA268.obj = saved;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003C1C0);

INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003C2D4);

void func_8003C344(void) {
    UnkStructB2 *p = D_801D3824;
    u16 n = 0x1C;

    do {
        memset(p, 0, sizeof(UnkStructB2));
        p++;
    } while (--n != 0);
    D_801F9980 = 0;
    D_801F9984 = 0;
    D_801F9988 = 0;
}

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
