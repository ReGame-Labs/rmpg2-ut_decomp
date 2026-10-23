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

/* 83 %: an object's hit box against a monster's; the original computes -w + x with negu in place (here x - w), loads the object's y and flags before the box, and loads the monster's four edges in another order */
#ifdef NON_MATCHING
s32 func_8003B9C8(UnkStruct4 *obj, UnkStruct7 *m) {
    UnkStruct16 *box;
    s16 x;
    u16 y;
    s32 flip;
    u16 w;
    s16 a;
    s16 left;
    s16 right;
    s16 top;
    s16 bottom;
    s16 m_right;
    s16 m_left;
    s16 m_top;
    s16 m_bottom;

    x = (s16) obj->unk_16;
    box = obj->unk_34;
    if (x < D_801F9ACA) {
        x += (D_801D8864 + 1) >> 16;
    }
    y = obj->unk_18.h.hi;
    flip = obj->unk_22 & 0x10;
    a = box->unk_10 + x;
    if (flip) {
        a = (u16) -box->unk_10 + x;
    }
    left = a;
    w = box->unk_14;
    top = box->unk_12 + y;
    if (flip) {
        w = -w;
    }
    right = w + x;
    bottom = box->unk_16 + y;
    if (flip) {
        left = right;
        right = a;
    }
    m_bottom = m->unk_11E;
    m_right = m->unk_11C;
    m_left = m->unk_118;
    m_top = m->unk_11A;
    if (left < m_right && m_left < right && top < m_bottom && m_top < bottom) {
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003B9C8);
#endif





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

void func_8003C2D4(u16 k, UnkStructB2 *rec) {
    s32 *t;

    if (rec->unk_10->unk_06 >= 5) {
        rec->unk_04 = 2;
        if ((u16) (k - 1) < 0x4A) {
            t = (s32 *) ((k << 2) + (u32) D_800830BC);
            func_8003CEA0(*t, rec->unk_00);
        }
    }
}












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

/* 78.7 %: an object's 'idle' test; the original keeps the result in v0 with the two zero stores in the branches' delay slots and the last test as a branch, where every form tried becomes a set-on-compare (xori/sltu) or uses another register */
#ifdef NON_MATCHING
u16 func_8003C858(UnkStructB3 *p, s32 arg1, s32 arg2) {
    u16 r = 0;

    if (p->unk_08 == 0) {
        r = 0;
        if (p->unk_0C == 0) {
            r = 1;
            if (p->unk_04 == 3) {
                r = 0;
            }
        }
    }
    return r;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003C858);
#endif










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

void func_8003C934(UnkStructB1 *rec) {
    UnkStruct4 *saved;
    UnkStructB4 *step;
    u16 k;

    saved = D_800AA248.unk_20;
    rec->unk_04 = 8;
    D_800AA248.unk_20 = rec->unk_00;
    func_8003C9E8(rec);
    step = D_8007DDD4;
    k = rec->unk_1A;
    if (k >= 14) {
        k = 2;
    }
    if (k != 0) {
        step += k;
        if (rec->unk_14 != NULL) {
            func_80054374(step->unk_04, rec->unk_14);
        }
        func_8001E698(D_800AA248.unk_20, step->unk_00);
    }
    D_800AA268.obj = saved;
}


void func_8003C9E8(UnkStructB1 *arg0) {
    if (arg0->unk_1A == 0xA) {
        func_8003CA28(arg0);
        return;
    }
    func_8003CA70(arg0);
}

void func_8003CA28(UnkStructB1 *arg0) {
    UnkStruct1 *temp_v1;

    temp_v1 = arg0->unk_14;
    if ((temp_v1 != NULL) && ((u32) (arg0->unk_06 - 0x45) < 2U)) {
        func_8003CADC(temp_v1);
    }
}

void func_8003CA70(UnkStructB1 *rec) {
    UnkStruct1 *a;
    s32 kind;

    a = rec->unk_14;
    if (a != NULL) {
        kind = rec->unk_06;
        if (kind >= 0x31) {
            if (kind < 0x34) {
                func_8003CB68(0x1E0, a);
            } else if (kind < 0x4A) {
                if (kind >= 0x48) {
                    func_8003CB30(a);
                }
            }
        }
    }
}




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

void func_8003CB68(s16 n, UnkStruct1 *a) {
    s16 v;

    v = n;
    func_8001F724(3);
    if (a->unk_186 != 0) {
        v = n << 1;
        a->unk_186 = 0;
        if ((u16) v > 0x5A0) {
            v = 0x5A0;
        }
    }
    a->unk_142 = v;
    a->unk_56 = 2;
    func_8005DD48(a);
}





















INCLUDE_ASM("asm/main/nonmatchings/game_8003B568", func_8003CBE0);

u16 func_8003CC84(UnkStructB3 *p, s32 hit) {
    if (hit == 0) {
        return 0;
    }
    return (u16) (p->unk_06 - 0x40) < 3;
}



void func_8003CCA8(void) {
    D_801E1C80 += 0x258;
}

void func_8003CCC0(void *arg0) {
    UnkStructB2 *rec = arg0;

    if (rec >= D_801D3824 && rec < D_801D3824 + 28) {
        rec->unk_10->unk_0C = 0;
        memset(rec, 0, sizeof(UnkStructB2));
    }
}

