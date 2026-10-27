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

/* 98.55 %: the sky gradient's colour bytes; the original materializes the colour table's address before the frame pointer's (the two lui/la swapped), every statement order tried keeps the pointer first */
#ifdef NON_MATCHING
void func_8002A4E8(void) {
    UnkStructFrame *frame;
    s32 colour;

    D_801FB41C = 0x808080;
    colour = D_8007CD40[D_801FA960 - 100];
    D_801FA9A4 = colour;
    if (colour == 0) {
        D_801F9A38 = 0;
        return;
    }
    D_801F9A38 = 1;
    D_801FAC80->unk_74 = D_8007CAFC[0xC];
    D_801FAC80->unk_75 = D_8007CAFC[0x10];
    D_801FAC80->unk_76 = D_8007CAFC[0x14];
    D_801FAC80->unk_7C = D_801FAC80->unk_74;
    D_801FAC80->unk_7D = D_801FAC80->unk_75;
    D_801FAC80->unk_7E = D_801FAC80->unk_76;
    D_801FAC80->unk_84 = D_8007CAFC[0];
    D_801FAC80->unk_85 = D_8007CAFC[4];
    D_801FAC80->unk_86 = D_8007CAFC[8];
    D_801FAC80->unk_8C = D_801FAC80->unk_84;
    D_801FAC80->unk_8D = D_801FAC80->unk_85;
    D_801FAC80->unk_8E = D_801FAC80->unk_86;
    D_801FAC80->unk_98 = D_8007CAFC[0x18];
    D_801FAC80->unk_99 = D_8007CAFC[0x1C];
    D_801FAC80->unk_9A = D_8007CAFC[0x20];
    D_801FAC80->unk_A0 = D_801FAC80->unk_98;
    D_801FAC80->unk_A1 = D_801FAC80->unk_99;
    D_801FAC80->unk_A2 = D_801FAC80->unk_9A;
    D_801FAC80->unk_A8 = D_801FAC80->unk_74;
    D_801FAC80->unk_A9 = D_801FAC80->unk_75;
    D_801FAC80->unk_AA = D_801FAC80->unk_76;
    D_801FAC80->unk_B0 = D_801FAC80->unk_7C;
    D_801FAC80->unk_B1 = D_801FAC80->unk_7D;
    D_801FAC80->unk_B2 = D_801FAC80->unk_7E;
    D_801FA9A4 = (D_801FAC80->unk_98 << 16) | (D_801FAC80->unk_99 << 8) | D_801FAC80->unk_9A;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002A4E8);
#endif


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

void func_8002B988(void) {
    s16 temp_v0;
    s32 temp_s0;
    s32 var_s1;
    Monster *temp_a0;

    func_8002B878();
    var_s1 = 0;
    do {
        if (D_801FA8A0[var_s1] != 0) {
            temp_s0 = (var_s1 + 1) & 0xFFFF;
            func_8002BA70(temp_s0);
            temp_a0 = func_8002BA30(temp_s0);
            if (D_8007A7D4 & 1) {
                temp_v0 = D_8007A688 - 1;
                temp_a0->unk_002 = temp_v0;
                temp_a0->unk_004 = temp_v0;
            }
        }
        var_s1 += 1;
    } while (var_s1 < 7);
}

Monster *func_8002BA30(s32 arg0) {
    Monster *temp_a1;

    temp_a1 = &D_801E0B78[arg0 & 0xFFFF];
    if (D_8007A7D4 & 1) {
        temp_a1->unk_008.w = 0x440000;
    }
    return temp_a1;
}

void func_8002BA70(s32 n) {
    Monster *m;
    GameObject *saved;

    m = &D_801E0B78[(u16) n];
    saved = D_800AA248.unk_20;
    func_8002BE30(m);
    m->id = n;
    m->unk_128 = n;
    func_8002BAEC(m);
    D_800AA248.unk_20 = saved;
}


INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002BAEC);

#ifdef NON_MATCHING
/* 99.8 %: the original's frame is 32 bytes (a spilled or address-taken local?), this one's 24. */
void func_8002BE30(Monster *arg0) {
    if (D_8007A7D4 & 1) {
        memset(arg0, 0, 0x220);
    } else {
        memset(arg0->unk_058, 0, 0x1C0);
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002BE30);
#endif

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002BE78);

void func_8002BF24(s32 arg0, UnkStruct1 *arg1) {
    if (arg1->unk_16 < arg1->unk_00) {
        func_8002DF64(arg0, arg1);
        return;
    }
    arg1->unk_14 = 0xE;
    arg1->unk_30 = 0;
    arg1->unk_16 = 0;
}

s32 func_8002BF70(UnkStruct1 *a) {
    UnkStruct1 *p;
    u16 n;
    u16 i;

    i = a->unk_1E;
    p = D_801D3DC8;
    n = i;
    if (n != 0) {
        do {
            if (p->unk_1E < n && p->unk_14 < 0x11 && p->unk_58 == 0) {
                return 0;
            }
            p++;
        } while (--i != 0);
    }
    return 1;
}






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

void func_8002C0AC(s32 arg0, UnkStruct1 *arg1) {
    if (arg1->unk_16 < arg1->unk_00) {
        func_8002E0C8(arg0, arg1);
        return;
    }
    arg1->unk_14 = 0x10;
    arg1->unk_30 = 0;
    arg1->unk_16 = 0;
}

void func_8002C0F8(s32 n, UnkStruct1 *a) {
    void (**handler)(UnkStruct1 *);
    s32 saved;

    if (a->unk_16 < a->unk_00) {
        handler = D_8007CFD0;
        if (a->unk_76 != 1) {
            a->unk_14 = 9;
            return;
        }
        handler += a->unk_76;
        saved = D_800AA248.unk_18;
        D_800AA248.unk_18 = n;
        (*handler)(a);
        D_800AA248.unk_18 = saved;
        return;
    }
    a->unk_14 = 0xE;
    a->unk_30 = 0;
    a->unk_16 = 0;
}




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
    if (arg0->unk_30 != 0) {
        func_8002ED90(arg0);
        return;
    }
    arg0->unk_14 = 0;
    arg0->unk_0C = 0;
}

void func_8002C228(UnkStruct1 *arg0) {
    func_8002FEA4((UnkStructFEA4 *) arg0);  /* the record's other view: to be unified */
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

s32 func_8002C2B4(UnkStruct1 *a) {
    s32 done;

    done = 0;
    func_8002E9A4(a);
    func_8002EBD8(a);
    a->unk_14 = 0x11;
    switch (D_801E1E40) {
    case 1:
        D_801FA890 = 0xB4;
    case 0:
        done = 1;
        break;
    default:
        D_801E1E40--;
        break;
    }
    return done;
}





extern u8 D_8001236C_b[];
void func_8002C32C(UnkStruct1 *a) {
    if (a->unk_00 > a->unk_16) {
        func_8002D9F8(a);
        return;
    }
    if (a->unk_84 != NULL) {
        func_8001E698(a->unk_84, a->unk_02 == 2 ? D_8001236C : D_8001236C_alt);
        a->unk_84 = NULL;
    }
    a->unk_14 = 0x10;
    a->unk_30 = 0;
    a->unk_16 = 0;
}




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

/* An old-style definition: its callers pass the actor they already hold in a0 without naming it. */
void func_8002C6A0(a)
UnkStruct1 *a;
{
    GameObject *obj;
    GameObject *spr;

    obj = a->unk_84;
    D_800AA268.obj = obj;
    if (obj != NULL) {
        func_8001E698(obj, D_80011E48);
        func_8002CBF4((Monster *) a);
        a->unk_84 = NULL;
    }
    func_8002EBD8(a);
    spr = a->unk_98[0].unk_00;
    spr->unk_80 = 0x20A;
    if (D_801E1E40 != 0) {
        if (D_801E1E40 == 1) {
            D_801FA890 = 0xB4;
        } else {
            D_801E1E40--;
        }
        func_8001E698(spr, a->unk_60);
    }
}



void func_8002C738(UnkStruct1 *arg0) {
    arg0->unk_14 = 0x10;
    func_8002C6A0();
}

void func_8002C75C(UnkStruct1 *arg0) {
    GameObject *temp_s1;

    temp_s1 = arg0->unk_98[0].unk_00;
    D_800AA248.unk_20 = temp_s1;
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

void func_8002CA8C(void) {
    GameObject *saved = D_800AA248.unk_20;
    UnkStruct1 *owner = saved->owner.item->unk_08;
    UnkStructD110 *r;
    GameObject *spr;
    s32 *anim;

    D_800AA248.unk_3C = func_8001D110();
    anim = D_80011E10;
    r = D_800AA248.unk_3C;
    r->unk_28 = anim;
    r->unk_00 = D_80011E10[0];
    r->unk_12 = saved->pos_x.u.hi;
    r->unk_16 = saved->pos_y.u.hi;
    r->unk_20 = saved->unk_80 - 1;
    spr = func_8001DCB4();
    owner->unk_84 = spr;
    spr->owner.item = (UnkStruct2 *) owner;  /* the owner: to be unified */
    spr->unk_70 = 0x749;
    if (func_8001A3AC() < 0x23) {
        D_800AA248.unk_20 = saved;
        return;
    }
    if (D_8007A690 == 1) {
        anim = D_80011E90;
    } else {
        r->unk_12 = spr->pos_x.u.hi + 0x14;
        anim = D_80011E68;
        r->unk_16 = spr->pos_y.u.hi - 0x32;
    }
    r->unk_28 = anim;
    r->unk_00 = *anim;
    r->unk_20 += 5;
    spr = func_8001DCB4();
    spr->unk_70 = 0x749;
    spr->owner.item = (UnkStruct2 *) owner;
    if (D_8007A690 != 1) {
        spr->flags |= 0x400;
    }
    D_800AA268.obj = saved;
}

void func_8002CBF4(Monster *m) {
    GameObject *saved = D_800AA248.unk_20;
    GameObject *body;
    UnkStructD110 *r;
    GameObject *spr;
    s32 *anim;

    if (func_8001A3AC() >= 0x46) {
        body = m->unk_098;
        r = func_8001D110();
        D_800AA248.unk_3C = r;
        if (m->unk_058 == 3) {
            anim = D_80011ED8;
        } else if (D_8007A690 == 1) {
            anim = D_80011ED0;
        } else {
            anim = D_80011E68;
        }
        r->unk_28 = anim;
        r->unk_00 = *anim;
        r->unk_12 = body->pos_x.u.hi;
        r->unk_16 = body->pos_y.u.hi;
        r->unk_20 = body->unk_80 + 5;
        spr = func_8001DCB4();
        if (m->unk_058 != 3 && D_8007A690 != 1) {
            spr->flags |= 0x400;
            spr->pos_x.u.hi += 0x14;
            spr->pos_y.u.hi -= 0x32;
        }
        D_800AA268.obj = saved;
    }
}

#ifdef NON_MATCHING
/* 98.2 %: the original reloads r->unk_06 for the argument of func_8003089C where this reuses the compare's
 * load, and keeps rec in s1 and r in s2 (swapped here). */
UnkStruct2 *func_8002CD24(u16 idx, UnkStruct1 *a, UnkStruct2 *rec) {
    GameObject *q = NULL;
    UnkStruct5 *r;
    u16 k;
    u16 arg;

    if (rec->unk_08->unk_70 == rec) {
        func_8002CE74(idx, a, rec - 1);
    } else if (a->unk_142 != 0) {
        func_80030E04(a, rec);
    } else {
        r = (UnkStruct5 *) func_8002ED30(idx, rec);  /* the record's other view: to be unified */
        k = r->unk_06;
        func_8002DBF4(idx, 5, a, rec);
        arg = 0xFFFF;
        if (r->unk_06 != k) {
            arg = r->unk_06;
        }
        func_8003089C(arg, a);
        q = r->unk_0C.unk_00;
        if (q != NULL) {
            if (q->unk_1C.u.lo != 3 || q->prev < 0xC) {
                func_8002CE40((UnkStruct2 *) q, a);
            } else {
                q = NULL;
            }
        }
    }
    return (UnkStruct2 *) q;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002CD24);
#endif

void func_8002CE40(UnkStruct2 *arg0, s32 arg1) {
    if ((arg0->unk_00 != 0) && ((u16) arg0->unk_04 >= 2U)) {
        arg0->unk_0E = 1;
        arg0->unk_14 = arg1;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002CE74);

void func_8002CFAC(Monster *m, UnkStruct1 *b) {
    u16 v;

    if (b->unk_58 == 2 && D_801E1E40 != 1) {
        func_8001F724(0x2B);
        return;
    }
    if (b->unk_58 == 3 && D_801E1E40 != 1) {
        func_8001F724(0x2B);
        return;
    }
    if (b->unk_14 != 0x10) {
        v = 5;
        if (b->unk_10 != 0) {
            v = 7;
            if (b->unk_10 >= b->unk_12) {
                v = 8;
                goto done;
            }
        }
        b->unk_10++;
        if ((u16) (b->unk_58 - 2) >= 2) {
            func_8001F724(0x4D);
        }
        func_8003111C(1, m);
        func_80031154(5, m);
        b->unk_32 = m->id;
        m->unk_18A = 1;
done:
        b->unk_14 = v;
    }
}

void func_8002D0C0(s32 arg0, UnkStruct1 *arg1) {
    GameObject *temp_s2;

    temp_s2 = D_800AA248.unk_20;
    if (arg1->unk_78 == 0) {
        func_8002F5B0(arg0, arg1);
        func_8003089C(5, arg0);
    } else {
        func_8002D448(arg0, arg1);
    }
    arg1->unk_78 = (u16) (arg1->unk_78 + 1);
    D_800AA248.unk_20 = temp_s2;
}

void func_8002D144(s32 arg0, UnkStruct1 *arg1) {
    s32 temp_s2;

    temp_s2 = D_800AA248.unk_20;
    if ((D_800AA2DC == 0) || !(D_8007BD78 & 0x40)) {
        if (arg1->unk_78 == 0) {
            func_8002F5B0(arg0, arg1);
            func_8003089C(5, arg0);
        } else {
            func_8002D228(arg0, arg1);
        }
        arg1->unk_14 = 1;
        arg1->unk_78 = (u16) (arg1->unk_78 + 1);
        D_800AA248.unk_20 = temp_s2;
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

void func_8002D370(s32 a, UnkStruct1 *b, UnkStruct1 *c) {
    u16 i = 0;
    u16 n = func_8002F558(c);

    while (1) {
        i++;
        if (func_8002ED30(n, b)->unk_06 < 5) {
            break;
        }
        if (i >= c->unk_02) {
            func_8002FA20(a, b);
            return;
        }
        n++;
        if (c->unk_02 < n) {
            n = 1;
        }
    }
    func_8002DBF4(n, 6, a, b);
    func_8003089C(5, a);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002D448);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002D5B8);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002D844);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002D9F8);

void *func_8002DAAC(u16 which, u16 n, UnkStruct5 *rec) {
    s32 **p;
    s32 *t;
    s32 r;
    u16 k;

    r = 0;
    if (n < 7) {
        k = rec->unk_08->unk_1C;
        if (k != 0) {
            p = D_80011D98;
            if (k < 3) {
                p += k - 1;
                t = *p;
                t += func_8001EB10(0x20, 0) & 1;
                r = t[n * 2];
            }
        }
    }
    return (void *) r;
}



#ifdef NON_MATCHING
/* 92 %: the original lays the `v == 0` and `v == n` outcomes out of line after an inlined `return result` for the 2;
 * the same statements in every nesting tried keep them in line. */
s32 func_8002DB3C(u16 which, u16 n, UnkStruct5 *rec) {
    UnkStruct12 *g;
    s32 result;
    u16 v;

    switch (which) {
    case 1:
        g = &rec->unk_0C;
        break;
    case 2:
        g = &rec->unk_24;
        break;
    case 3:
        g = &rec->unk_3C;
        break;
    default:
        return 1;
    }
    if (rec->unk_06 == 0) {
        if (n == 0) {
            result = 3;
            if (g->unk_10 != NULL) {
                result = 1;
            }
        } else {
            v = g->unk_06;
            if (v != 0) {
                if (v != n && v < 5) {
                    result = 2;
                } else {
                    result = 1;
                }
            } else {
                result = 3;
            }
        }
    } else {
        result = 1;
    }
    return result;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002DB3C);
#endif

/* 82 %: the sprite request for a record's slot; the original keeps n (a1) in s3 and needs one saved register less (no s8), and its u16 n compares unsigned; the u16, s16 and int parameter forms each add a copy or a sign extension */
#ifdef NON_MATCHING
void func_8002DBF4(u16 which, s32 n, UnkStruct1 *a, UnkStruct2 *rec) {
    GameObject *saved;
    GameObject *obj;
    UnkStructD110 *req;
    SpriteFrame *ofs;
    UnkStruct12 *slot;
    u16 r;
    u16 m;
    u16 dx;
    u16 dy;
    s32 anim;

    saved = D_800AA248.unk_20;
    if (rec->unk_08->unk_70 != rec) {
        m = n;
        r = func_8002DB3C(which, m, (UnkStruct5 *) rec);
        if (r != 1) {
            if (r == 3) {
                if (m >= 5) {
                    func_8002E5F4(which, (UnkStruct5 *) rec);
                }
                anim = (s32) func_8002DAAC(which, m, (UnkStruct5 *) rec);
                if (anim != 0) {
                    D_800AA248.unk_3C = func_8001D110();
                    req = D_800AA248.unk_3C;
                    req->unk_00 = anim;
                    req->unk_0C = 0x715;
                    ofs = rec->unk_00->frame;
                    if (which == 1) {
                        dx = ofs->unk_10;
                        dy = ofs->unk_12;
                        slot = &((UnkStruct5 *) rec)->unk_0C;
                    } else if (which == 2) {
                        req->unk_04 |= 0x10;
                        dx = ofs->unk_20;
                        dy = ofs->unk_22;
                        slot = &((UnkStruct5 *) rec)->unk_24;
                    } else {
                        dx = ofs->unk_18;
                        dy = ofs->unk_1A;
                        slot = &((UnkStruct5 *) rec)->unk_3C;
                    }
                    req->unk_12 = rec->unk_00->pos_x.u.hi + dx;
                    req->unk_16 = rec->unk_00->pos_y.u.hi + dy;
                    req->unk_20 = rec->unk_00->unk_80 + 7;
                    obj = func_8001DCB4();
                    D_800AA268.obj = obj;
                    if (obj != NULL) {
                        if ((u16) n < 2) {
                            slot->unk_10 = obj;
                            slot->unk_16 = n;
                        } else {
                            slot->unk_00 = obj;
                            slot->unk_06 = n;
                        }
                    }
                    func_80030698(m, a, rec);
                    func_8002FA20((s32) a, (UnkStruct1 *) rec);
                }
            } else if (r == 2) {
                func_8002DE08(which, m, (s32) a, (UnkStruct5 *) rec);
                func_80030698(m, a, rec);
                func_8002FA20((s32) a, (UnkStruct1 *) rec);
            }
        }
    }
    D_800AA268.obj = saved;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002DBF4);
#endif






void func_8002DE08(u16 which, s16 n, s32 arg2, UnkStruct5 *rec) {
    GameObject *saved = D_800AA268.obj;
    void *t;
    UnkStruct12 *g;
    GameObject *obj;

    t = func_8002DAAC(which, n, rec);
    if (t != NULL) {
        switch (which) {
        case 1:
            g = &rec->unk_0C;
            break;
        case 2:
            g = &rec->unk_24;
            break;
        default:
            g = &rec->unk_3C;
            break;
        }
        if ((u16) n < 2) {
            obj = g->unk_10;
        } else {
            obj = g->unk_00;
        }
        D_800AA268.obj = obj;
        if (obj != NULL) {
            if ((u16) n >= 5) {
                if ((u16) n != 6 || g->unk_06 != 5) {
                    func_8002E5F4(which, rec);
                }
            }
            func_80020BA0(t, obj->flags, obj);
            func_80030754(g, n, arg2, rec);
            if ((u16) n < 2) {
                g->unk_16 = n;
            } else {
                g->unk_06 = n;
            }
        }
    }
    D_800AA268.obj = saved;
}

void func_8002DF64(s32 arg0, UnkStruct1 *arg1) {
    if (arg1->unk_00 < 6U) {
        func_8002DFA8(arg0, arg1);
        return;
    }
    func_8002E148(arg0, arg1);
}

void func_8002DFA8(s32 arg0, UnkStruct1 *arg1) {
    GameObject *temp_s2;
    u16 temp_v1;
    u16 temp_v1_2;
    u16 var_s0;
    UnkStruct2 *temp_a1;
    UnkStruct2 *temp_a1_2;

    temp_v1 = (u16) arg1->unk_30;
    temp_s2 = D_800AA248.unk_20;
    if (temp_v1 != 0) {
        arg1->unk_30 = temp_v1 - 1;
    } else {
        temp_a1 = arg1->unk_98;
        if (arg1->unk_16 == 0) {
            func_8002FAA4(arg0, temp_a1);
        } else {
            temp_a1_2 = &temp_a1[arg1->unk_16];
            temp_v1_2 = temp_a1_2->unk_04;
            if (temp_v1_2 == arg1->unk_00) {
                func_8002F5B0(arg0, arg1);
                func_8003D60C(arg1);
            } else {
                if (temp_a1_2->unk_06 != 0) {
                    var_s0 = 0;
                    if (temp_v1_2 == arg1->unk_8A) {
                        func_80030D14(arg1->unk_18.w, temp_a1_2);
                    }
                } else {
                    var_s0 = 0x20;
                    func_8002E348(arg0, temp_a1_2);
                    if (arg1->unk_16 & 1) {
                        var_s0 = 0x18;
                    }
                }
                arg1->unk_30 = var_s0;
            }
        }
        arg1->unk_16 = arg1->unk_16 + 1;
    }
    D_800AA248.unk_20 = temp_s2;
}

void func_8002E0C8(s32 n, UnkStruct1 *a) {
    UnkStruct2 *end;
    UnkStruct2 *p;

    end = a->unk_70;
    func_8002F5B0(n, a);
    func_8003D60C(a);
    p = a->unk_98;
    func_8002FAA4(n, p);
    do {
        p++;
        func_80030E04(0, p);
    } while (end != p);
    a->unk_16 = a->unk_00;
}







void func_8002E148(s32 arg0, UnkStruct1 *a) {
    GameObject *saved = D_800AA268.obj;
    u16 count;
    u16 left;
    UnkStruct2 *rec;
    u16 v;

    if (a->unk_30 != 0) {
        a->unk_30--;
    } else {
        count = a->unk_00;
        left = count - a->unk_16;
        rec = a->unk_98;
        if (left == 1) {
            func_8002FAA4(arg0, rec);
        } else {
            rec = &rec[left - 1];
            if (rec->unk_04 == count) {
                func_8002F5B0(arg0, a);
                func_8003D60C(a);
            } else {
                if (rec->unk_06 != 0) {
                    v = 0;
                    if (rec->unk_04 == a->unk_8A) {
                        func_80030D14(a->unk_18.w, rec);
                    }
                } else {
                    v = 0x18;
                    func_8002E348(arg0, rec);
                    if (a->unk_16 & 1) {
                        v = 0x20;
                    }
                }
                a->unk_30 = v;
            }
        }
        a->unk_16++;
    }
    D_800AA268.obj = saved;
}

void func_8002E278(s32 arg0, UnkStruct1 *a) {
    GameObject *saved = D_800AA268.obj;
    UnkStruct2 *rec = a->unk_98;

    if (a->unk_16 == 0) {
        func_8002FAA4(arg0, rec);
        goto next;
    }
    while (1) {
        if (rec->unk_04 == a->unk_00) {
            func_8002F5B0(arg0, a);
            func_8003D60C(a);
            a->unk_16 = a->unk_00;
            break;
        }
        func_8002E348(arg0, rec);
        a->unk_30 = (a->unk_16 & 1) ? 0x20 : 0x18;
next:
        rec++;
        a->unk_16++;
    }
    D_800AA268.obj = saved;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002E348);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002E440);

void func_8002E5F4(u16 which, UnkStruct5 *rec) {
    func_8002E658(which, rec);
}

void func_8002E614(u16 which, UnkStruct5 *rec) {
    s32 *temp_v0;

    temp_v0 = func_8002E658(which, rec);
    if ((temp_v0 != NULL) && (*temp_v0 != 0)) {
        func_8003C894(temp_v0);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002E658);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002E854);

void func_8002E9A4(UnkStruct1 *arg0) {
    GameObject *temp_a0;
    GameObject *temp_s1;

    temp_a0 = arg0->unk_98[0].unk_00;
    temp_s1 = D_800AA248.unk_20;
    D_800AA248.unk_20 = temp_a0;
    temp_a0->unk_80 = 0x20A;
    func_8001E698(temp_a0, arg0->unk_60);
    D_800AA248.unk_20 = temp_s1;
}

void func_8002E9F8(UnkStruct1 *a) {
    u16 i = 2;
    UnkStruct2 *rec = &a->unk_98[1];
    u16 *p = a->unk_3A;
    u16 k = a->unk_36;
    GameObject *saved = D_800AA268.obj;
    u16 v;
    s32 n;
    UnkStructPair *tbl;
    for (;; i++) {
        v = *p;
        n = i - 1;
        if (k < a->unk_00 - n || v >= 0xC) {
            rec++;
            p++;
        } else {
            *p = v + 1;
            p++;
            if (a->unk_34 == 1) {
                tbl = D_8007CE08;
            } else {
                tbl = D_8007CE34;
            }
            tbl += v - 1;
            func_800309AC(tbl->unk_00, (UnkStruct5 *) rec);
            rec++;
        }
        if (a->unk_00 == i) {
            break;
        }
    }
    a->unk_36 = k + 1;
    D_800AA268.obj = saved;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002EB00);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002EBD8);

void func_8002ECA0(UnkStruct1 *arg0) {
    u16 var_s1;
    UnkStruct2 *var_s0;

    func_8002E278(D_800AA260, arg0);
    func_8003CD08(arg0);
    func_8003D60C(arg0);
    var_s0 = &arg0->unk_98[1];
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

UnkStruct2 *func_8002ED30(u16 which, void *arg1) {
    UnkStruct5 *rec = arg1;
    UnkStruct12 *slot;

    slot = NULL;
    switch (which) {
    case 1:
        slot = &rec->unk_0C;
        break;
    case 2:
        slot = &rec->unk_24;
        break;
    case 3:
        slot = &rec->unk_3C;
        break;
    }
    return (UnkStruct2 *) slot;
}



void func_8002ED90(UnkStruct1 *arg0) {
    u16 var_s1;
    s16 var_s2;
    u16 temp_v0;
    u32 temp_v1;
    UnkStruct2 *var_s0;

    var_s2 = arg0->unk_0C;
    var_s1 = arg0->unk_00 - 1;
    temp_v0 = (u16) arg0->unk_30 - 1;
    temp_v1 = temp_v0 & 3;
    arg0->unk_30 = temp_v0;
    var_s0 = &arg0->unk_98[1];
    if (temp_v1 < 2U) {
        if (temp_v1 == 0) {
            var_s2 = -var_s2;
        }
        do {
            func_8002EE14(var_s2, (UnkStruct5 *) var_s0);  /* the record's other view: to be unified */
            var_s0++;
        } while (--var_s1 != 0);
    }
}

void func_8002EE14(s16 dy, UnkStruct5 *s) {
    UnkStruct1 *b = s->unk_00;
    UnkStruct12 *g;
    GameObject *r;
    GameObject **pp;
    UnkStruct14 *q;

    if (b != NULL) {
        b->unk_18.u.hi += dy;
        r = s->unk_0C.unk_00;
        g = &s->unk_0C;
        if (r != NULL) {
            r->pos_y.u.hi += dy;
        }
        r = g->unk_10;
        if (r != NULL) {
            r->pos_y.u.hi += dy;
        }
        pp = g->unk_08;
        if (pp != NULL) {
            r = *pp;
            if (r != NULL) {
                r->pos_y.u.hi += dy;
            }
        }
        q = g->unk_0C;
        if (q != NULL) {
            r = q->unk_00;
            if (r != NULL) {
                r->pos_y.u.hi += dy;
            }
        }
        r = s->unk_24.unk_00;
        g = &s->unk_24;
        if (r != NULL) {
            r->pos_y.u.hi += dy;
        }
        r = g->unk_10;
        if (r != NULL) {
            r->pos_y.u.hi += dy;
        }
        pp = g->unk_08;
        if (pp != NULL) {
            r = *pp;
            if (r != NULL) {
                r->pos_y.u.hi += dy;
            }
        }
        q = g->unk_0C;
        if (q != NULL) {
            r = q->unk_00;
            if (r != NULL) {
                r->pos_y.u.hi += dy;
            }
        }
        r = s->unk_3C.unk_00;
        g = &s->unk_3C;
        if (r != NULL) {
            r->pos_y.u.hi += dy;
        }
        r = g->unk_10;
        if (r != NULL) {
            r->pos_y.u.hi += dy;
        }
        pp = g->unk_08;
        if (pp != NULL) {
            r = *pp;
            if (r != NULL) {
                r->pos_y.u.hi += dy;
            }
        }
        q = g->unk_0C;
        if (q != NULL) {
            r = q->unk_00;
            if (r != NULL) {
                r->pos_y.u.hi += dy;
            }
        }
    }
}

UnkStruct1 *func_8002F01C(void) {
    UnkStruct1 *found;
    UnkStruct1 *p;
    u16 n;

    found = NULL;
    n = D_801E29A4;
    p = D_801D3DC8;
    if (n != 0) {
        do {
            if (p->unk_20 == D_80011BA4 && p->unk_94 == 0) {
                p->unk_94 = 1;
                found = p;
                break;
            }
            p++;
        } while (--n != 0);
    }
    return found;
}


INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002F084);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002F100);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002F474);

/* 97.3 %: a random 1-3 per building kind; the original masks the final value with andi 0xffff (a u16 it does not know is small), every typing of the temporary drops or moves the mask */
#ifdef NON_MATCHING
u16 func_8002F558(UnkStruct1 *a) {
    s32 r;

    r = func_8001EB10(0x8000, 0);
    if (a->unk_02 == 2) {
        return (r & 1) + 1;
    }
    r &= 3;
    if (r == 0) {
        return 3;
    }
    return r;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002F558);
#endif
















void func_8002F5B0(s32 arg0, UnkStruct1 *arg1) {
    s32 temp_a0;
    s32 temp_s1;
    s32 temp_s2;
    UnkStruct2 *temp_s0;

    temp_s0 = arg1->unk_70;
    temp_s2 = D_800AA248.unk_20;
    temp_s1 = arg1->unk_64;
    if (temp_s0->unk_06 == 0) {
        func_80030698(0, arg0, temp_s0);
        temp_a0 = temp_s0->unk_00;
        if (temp_a0 != 0) {
            func_8001E698(temp_a0, temp_s1);
            temp_s0->unk_06 = 1U;
        }
    }
    D_800AA248.unk_20 = temp_s2;
}

void func_8002F630(UnkStruct1 *arg0, s32 arg1, UnkStruct2 *arg2) {
    func_8002F688(arg0, 0, arg1, arg2);
}

void func_8002F65C(UnkStruct1 *arg0, s32 arg1, UnkStruct2 *arg2) {
    func_8002F688(arg0, 1, arg1, arg2);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002F688);

void func_8002F898(UnkStruct6 *arg0, UnkStruct2 *rec) {
    GameObject *saved = D_800AA248.unk_20;
    GameObject *obj;
    UnkStruct3 *r;
    u8 *anim;

    if (rec->unk_04 != 1) {
        if (rec->unk_08->unk_70 == rec) {
            func_8001E4B0(rec->unk_00);
        } else {
            func_8002F9F4(rec);
            if (arg0->unk_02 == 2) {
                anim = D_8001236C;
            } else {
                if (arg0->unk_02 != 3) {
                    D_800AA248.unk_20 = saved;
                    return;
                }
                anim = D_80012394;
            }
            func_80025848(rec);
            obj = rec->unk_00;
            D_800AA268.obj = obj;
            if (obj != NULL) {
                func_8001E698(obj, anim);
                func_80024964(0x49, obj);
                r = arg0->unk_18;
                if (r != NULL && r->unk_0A == rec->unk_04) {
                    func_80030D14(r);
                }
            }
        }
    }
    D_800AA268.obj = saved;
}

void func_8002F9BC(void) {
    UnkStruct2 *temp_s0;

    temp_s0 = D_800AA248.unk_20->owner.item;
    func_8001E4B0(D_800AA248.unk_20);
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

void func_8002FAA4(s32 arg0, UnkStruct2 *arg1) {
    GameObject *temp_a1;
    GameObject *temp_s1;

    temp_s1 = D_800AA248.unk_20;
    if (arg1->unk_06 == 0) {
        temp_a1 = arg1->unk_00;
        D_800AA248.unk_20 = temp_a1;
        if (temp_a1 != NULL) {
            func_8002FB38(arg1->unk_08->unk_5C, temp_a1);
            arg1->unk_06 = 1;
            func_80030698(0, arg0, arg1);
            func_8001F724(0x45);
        }
    }
    D_800AA248.unk_20 = temp_s1;
}

void func_8002FB38(void *arg0, GameObject *arg1) {
    if (arg1->frame != arg0) {
        func_80020BA0(arg0, 0x8002, arg1);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002FB6C);

void func_8002FD24(UnkStruct1 *arg0, UnkStruct1 *arg1) {
    u16 i;
    u16 temp_a3;
    Monster *temp_a2;

    i = 7;
    do {
        temp_a2 = &D_801E0B78[i];
        if (temp_a2->unk_058 & 1) {
            temp_a3 = temp_a2->unk_1B0;
            if (temp_a3 != 0) {
                if ((temp_a2->unk_1B2 == arg1->unk_1E) && (temp_a3 != 3)) {
                    if (temp_a2->unk_1B4 >= arg0->unk_04) {
                        temp_a2->action = 0xF;
                    }
                }
            }
        }
    } while (--i != 0);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002FDC0);

void func_8002FEA4(UnkStructFEA4 *a) {
    GameObject *saved = D_800AA248.unk_20;
    UnkStructD110 *r;
    GameObject *spr;
    s16 x;

    if (func_8001A3AC() >= 0x23) {
        r = func_8001D110();
        r->unk_28 = D_80012068;
        r->unk_00 = D_80012068[0];
        x = (u16) a->unk_04 + (a->unk_0E - a->unk_04 - 0x7A) / 2;
        r->unk_12 = x;
        r->unk_16 = a->unk_06 - 0x1D;
        r->unk_20 = a->unk_08 + 0x90;
        D_800AA248.unk_3C = r;
        spr = func_8001DCB4();
        if (spr != NULL) {
            spr->owner.item = (UnkStruct2 *) a;  /* the owner: to be unified */
        }
        D_800AA248.unk_20 = saved;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8002FF74);

void func_800300A0(UnkStruct15 *arg0, UnkStruct1 *arg1) {
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

void func_800302AC(u16 kind, Monster *m) {
    s16 action;
    s32 push;

    switch (kind) {
    case 1:
        action = 0x46;
        push = 0x60000;
        break;
    case 2:
        action = 0x49;
        push = 0x30000;
        break;
    case 3:
        action = 0x47;
        push = 0x50000;
        break;
    default:
        return;
    }
    m->action = action;
    m->unk_05C = 0;
    func_80053C50(push, m);
    m->unk_13C = 0x4B;
}


INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80030338);

void func_800303DC(UnkStruct1 *a, GameObject *obj) {
    UnkStructPair *p;
    u16 n;
    s16 d;

    if (obj->unk_80 != 2) {
        p = D_801D8804;
        n = 13;
        do {
            if (p->unk_00 == 0) {
                d = a->unk_16 - a->unk_1C;
                p->unk_00 = d + 0x19;
                p->unk_02 = d + (u16) a->unk_30 - 0x19;
                return;
            }
            p++;
        } while (--n != 0);
    }
}

void func_8003044C(void) {
    UnkStructPair *p;
    u16 n;

    p = D_801D8804;
    n = 14;
    do {
        p->unk_00 = 0;
        p->unk_02 = 0;
        p++;
    } while (--n != 0);
}


INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8003047C);

void func_800305C8(s32 *anim, s16 y, GameObject *body, UnkStructFEA4 *rec) {
    GameObject *saved = D_800AA268.obj;
    UnkStructD110 *r;
    s32 x;

    r = func_8001D110();
    r->unk_16 = y;
    r->unk_28 = anim;
    r->unk_00 = *anim;
    x = rec->unk_04 + ((rec->unk_02 == 2) ? 0x4F : 0x77);
    r->unk_12 = D_801D8866 & func_8001EB10(x, rec->unk_04);
    r->unk_20 = body->unk_80 + 1;
    D_800AA248.unk_3C = r;
    func_8001DCB4();
    D_800AA248.unk_20 = saved;
}

#ifdef NON_MATCHING
/* 93 %: the original saves arg1 into s2 and copies arg0 into v1 at the very start (the call passes the raw
 * argument, the compares its s16 value); every form tried orders the prologue differently. */
void func_80030698(s32 arg0, UnkStruct1 *arg1, UnkStruct2 *arg2) {
    s16 temp_s0;
    u16 temp_v0;
    u32 temp_a1;
    UnkStruct1 *temp_s1;

    temp_s1 = arg2->unk_08;
    temp_s0 = arg0;
    if ((temp_s1 != NULL) && ((u16) temp_s1->unk_14 < 9U) && (temp_s0 < 7)) {
        func_80031154(arg0 & 0xFFFF);
        if (temp_s0 >= 0) {
            temp_v0 = temp_s1->unk_10 + D_8007CFE8[temp_s0];
            temp_a1 = temp_v0 & 0xFFFF;
            temp_s1->unk_10 = temp_v0;
            func_80030834(temp_s1, temp_a1);
            if (temp_a1 < temp_s1->unk_12) {
                func_8003111C(1, arg1);
            }
        }
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80030698);
#endif

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80030754);

#ifdef NON_MATCHING
/* 91 %: the original keeps the difference in v1 and masks it twice, with var_v0/var_v1 in v0/v1; every
 * form tried masks once and puts var_v0 in a1. */
void func_80030834(UnkStruct1 *arg0, s32 arg1) {
    s16 var_v0;
    s16 var_v1;
    s32 temp_v0;

    if ((u16) arg0->unk_14 == 0) {
        temp_v0 = arg0->unk_12 - arg1;
        if ((u16) temp_v0 != 0) {
            var_v0 = 0x1A;
            if ((u16) temp_v0 < 4U) {
                var_v1 = 3;
                goto block_6;
            }
            var_v0 = 0xE;
            if ((u16) temp_v0 < 6U) {
                var_v1 = 1;
block_6:
                arg0->unk_30 = var_v0;
                arg0->unk_0C = var_v1;
                arg0->unk_14 = 3;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80030834);
#endif

void func_8003089C(u16 i, UnkStruct1 *a) {
    u16 *p;

    if (i < 7 && a->unk_00 != 0) {
        p = D_8007CFF8;
        p += i + 1;
        func_8001F724(*p);
    }
}

void func_800308EC(s16 arg0, UnkStruct12 *arg1) {
    GameObject **temp_v0;
    GameObject *obj;
    UnkStruct14 *temp_d;

    obj = arg1->unk_00;
    if (obj != NULL) {
        obj->pos_x.u.hi = (u16) (obj->pos_x.u.hi + arg0);
    }
    obj = arg1->unk_10;
    if (obj != NULL) {
        obj->pos_x.u.hi = (u16) (obj->pos_x.u.hi + arg0);
    }
    temp_v0 = arg1->unk_08;
    if (temp_v0 != NULL) {
        obj = *temp_v0;
        if (obj != NULL) {
            obj->pos_x.u.hi = (u16) (obj->pos_x.u.hi + arg0);
        }
    }
    temp_d = arg1->unk_0C;
    if ((temp_d != NULL) && (temp_d->unk_04 < 0xBU)) {
        obj = temp_d->unk_00;
        if (obj != NULL) {
            obj->pos_x.u.hi = (u16) (obj->pos_x.u.hi + arg0);
        }
    }
}

void func_800309AC(s16 arg0, UnkStruct5 *arg1) {
    UnkStruct3 *temp_a0;
    UnkStruct1 *temp_v1;
    UnkStruct1 *temp_v1_2;

    temp_v1 = arg1->unk_00;
    if (temp_v1 != NULL) {
        temp_v1->unk_16 = (u16) (temp_v1->unk_16 + arg0);
        func_800308EC(arg0, &arg1->unk_0C);
        func_800308EC(arg0, &arg1->unk_24);
        func_800308EC(arg0, &arg1->unk_3C);
        temp_a0 = arg1->unk_08->unk_18;
        if ((temp_a0 != NULL) && (temp_a0->unk_0A == arg1->unk_04)) {
            temp_v1_2 = temp_a0->unk_00;
            if (temp_v1_2 != NULL) {
                temp_v1_2->unk_16 = (u16) (temp_v1_2->unk_16 + arg0);
            }
        }
    }
}

void func_80030A70(s32 arg0, UnkStruct12 *arg1) {
    GameObject **temp_v0;
    GameObject *obj;
    UnkStruct14 *temp_d;

    obj = arg1->unk_00;
    if (obj != NULL) {
        obj->vel_y.w = arg0;
    }
    obj = arg1->unk_10;
    if (obj != NULL) {
        obj->vel_y.w = arg0;
    }
    temp_v0 = arg1->unk_08;
    if (temp_v0 != NULL) {
        obj = *temp_v0;
        if (obj != NULL) {
            obj->vel_y.w = arg0;
        }
    }
    temp_d = arg1->unk_0C;
    if ((temp_d != NULL) && (temp_d->unk_04 < 0xBU)) {
        obj = temp_d->unk_00;
        if (obj != NULL) {
            obj->vel_y.w = arg0;
        }
    }
}

void func_80030B00(s32 vy, UnkStruct2 *rec) {
    GameObject *obj;

    obj = rec->unk_00;
    if (obj != NULL) {
        obj->vel_y.w = vy;
        func_80030A70(vy, &((UnkStruct5 *) rec)->unk_0C);
        func_80030A70(vy, &((UnkStruct5 *) rec)->unk_24);
        func_80030A70(vy, &((UnkStruct5 *) rec)->unk_3C);
    }
}


#ifdef NON_MATCHING
/* 95 %: the original computes the first record's address in two steps (unk_98, then + 0x54), as a loop
 * induction variable would; the indexed form moves the base into s2 instead. */
void func_80030B5C(UnkStruct1 *arg0) {
    u16 var_s1;
    UnkStruct2 *var_s0;

    var_s1 = arg0->unk_00 - 1;
    var_s0 = &arg0->unk_98[1];
    do {
        func_80030C7C(var_s0);
        var_s0++;
    } while (--var_s1 != 0);
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80030B5C);
#endif

void func_80030BAC(UnkStruct12 *arg0) {
    GameObject **temp_v0;
    GameObject *obj;
    UnkStruct14 *temp_d;

    obj = arg0->unk_00;
    if (obj != NULL) {
        obj->pos_y.w = obj->pos_y.w + obj->vel_y.w;
    }
    obj = arg0->unk_10;
    if (obj != NULL) {
        obj->pos_y.w = obj->pos_y.w + obj->vel_y.w;
    }
    temp_v0 = arg0->unk_08;
    if (temp_v0 != NULL) {
        obj = *temp_v0;
        if (obj != NULL) {
            obj->pos_y.w = obj->pos_y.w + obj->vel_y.w;
        }
    }
    temp_d = arg0->unk_0C;
    if ((temp_d != NULL) && (temp_d->unk_04 < 0xBU)) {
        obj = temp_d->unk_00;
        if (obj != NULL) {
            obj->pos_y.w = obj->pos_y.w + obj->vel_y.w;
        }
    }
}

void func_80030C7C(UnkStruct2 *rec) {
    GameObject *obj;

    obj = rec->unk_00;
    if (obj != NULL) {
        obj->pos_y.w += obj->vel_y.w;
        func_80030BAC(&((UnkStruct5 *) rec)->unk_0C);
        func_80030BAC(&((UnkStruct5 *) rec)->unk_24);
        func_80030BAC(&((UnkStruct5 *) rec)->unk_3C);
    }
}


s32 func_80030CD4(UnkStruct17 *part) {
    s32 r;
    if (part->unk_08 == 0) {
        func_80030D14();
        r = 0;
    } else {
        part->unk_10 = 1;
        r = 1;
    }
    return r;
}





void func_80030D14(UnkStruct19 *p) {
    GameObject *saved;
    GameObject *obj;

    saved = D_800AA248.unk_20;
    if (p != NULL) {
        obj = p->unk_00;
        D_800AA248.unk_20 = obj;
        func_8001E698(obj, p->unk_04);
        func_8001F724(0x42);
    }
    D_800AA248.unk_20 = saved;
}



#ifdef NON_MATCHING
/* 83.8 %: the loop's pointer register is &p->unk_98 in the original (negative offsets for unk_70 and unk_14),
 * &p->unk_14 here: which field's address the compiler keeps as the induction variable. */
void func_80030D74(void) {
    u16 n = D_801E29A4;
    s16 count = 0;
    UnkStruct1 *p;
    GameObject *o;

    if (n != 0) {
        p = D_801D3DC8;
        do {
            o = p->unk_70->unk_00;
            if (!(p->unk_98[0].unk_00->unk_6C & 0x80) || o == NULL || !(o->unk_6C & 0x80)) {
                if (p->unk_14 < 0x10) {
                    count++;
                }
            }
            p++;
        } while (--n != 0);
        D_801FA734 = count;
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80030D74);
#endif

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80030E04);

void func_80030FA4(void) {
    void *temp_a0;
    s32 temp_s2;
    UnkStruct2 *temp_s0;
    UnkStruct1 *temp_s1;

    temp_s0 = D_800AA248.unk_20->owner.item;
    temp_s2 = D_800AA248.unk_20->unk_94.p;
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

void func_8003111C(s32 arg0, Monster *arg1) {
    if (((u8 *) arg1 >= D_801E0D98) && ((u8 *) arg1 <= D_801E0D98 + 0xCC0)) {
        arg1->unk_026 = (u16) (((u16) arg1->unk_026) + arg0);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80031154);

void func_80031224(void) {
    UnkStruct1 *temp_v0;

    func_8001F724(5);
    temp_v0 = func_8003D1F8((D_800AA248.unk_20->owner.item)->unk_10);
    if (((u16) temp_v0->unk_14) < 3U) {
        temp_v0->unk_14 = 0xCU;
    }
}

void func_80031280(s32 arg0, UnkStruct1 *a) {
    void *target = a->unk_20;
    void **t;
    UnkStruct2 *r;

    if (a->unk_58 == 0) {
        t = D_8007D008;
    } else {
        t = D_8007D060;
    }
    while (*t != NULL) {
        if (*t == target) {
            break;
        }
        t++;
    }
    if (*t != NULL) {
        if (a->unk_58 != 0) {
            func_8002CFAC(arg0, a);
        } else {
            r = a->unk_70;
            if (r != NULL && r->unk_00 != NULL && r->unk_08 != NULL) {
                func_8002F5B0(arg0, a);
                func_8001F724(5);
                a->unk_78++;
                func_80031364(a);
            }
        }
    }
}

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

/* 83 %: the level's two lists; the original loads r->unk_04 after the two stores to D_801D37BC/D_801D37C0 (so they may alias it: likely fields of one struct, not scalars) and sets up D_801E1E34 before the call's argument */
#ifdef NON_MATCHING
void func_80031690(void) {
    s32 *lists;
    UnkStruct18 *r;

    lists = D_801E1E34;
    r = (UnkStruct18 *) func_80025C08(&D_80084028[0]);
    D_801D37BC = r->unk_00;
    D_801D37C0 = r->unk_02;
    D_801D857C = r->unk_04;
    if (D_801D857C != 0) {
        func_8003197C(r->unk_0C, D_801D857C, &lists[0]);
        func_8003197C(r->unk_18, r->unk_08, &lists[1]);
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80031690);
#endif





INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80031714);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8003197C);

void func_80031A3C(void) {
    D_801D8864 = *func_80025C08(D_800838A0);
}

void func_80031A68(void) {
    if ((D_801D37BC == 0) && (D_801D37C0 == 0) && (D_801D857C != 0)) {
        func_80020BA0(D_801D857C, 0x8002, D_800AA248.unk_20);
        D_801D857C = 0;
        func_8001E7A0();
    }
}

void func_80031AC8(void) {
    if ((D_801D37BC == 0) && (D_801D37C0 == 0)) {
        D_800AA248.unk_20->script_pc = *D_800AA248.unk_20->arg.w;
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

void func_80031EC0(s32 arg0, UnkStruct9 *arg1) {
    if (arg1->unk_0A != 0) {
        if (arg1->unk_0C == 1) {
            arg1->unk_0A = 4;
            arg1->unk_0C = 0;
            arg1->unk_08 = 0x15;
            func_80032630(arg0, arg1);
        }
    } else {
        arg1->unk_0C = 0;
        arg1->unk_0A = 1;
        func_80032630(arg0, arg1);
    }
}

void func_80031F20(s32 arg0, UnkStruct9 *arg1) {
    if (arg1->unk_0C == 1) {
        arg1->unk_0A = 5;
        arg1->unk_0C = 0;
        arg1->unk_08 = 0x16;
        func_80032630(arg0, arg1);
    }
}

void func_80031F5C(s32 arg0, UnkStruct9 *arg1) {
    if (arg1->unk_0C == 1) {
        arg1->unk_0A = 6;
        arg1->unk_0C = 0;
        arg1->unk_08 = 0x17;
        func_80032630(arg0, arg1);
    }
}

void func_80031F98(s32 arg0, UnkStruct9 *arg1) {
    if (arg1->unk_0C == 1) {
        arg1->unk_0A = 9;
        arg1->unk_0C = 0;
        arg1->unk_08 = 0x32;
        func_80032630(arg0, arg1);
    }
}

void func_80031FD4(s32 arg0, UnkStruct9 *arg1) {
    if (arg1->unk_0C == 1) {
        func_8003DB74(arg1);
    }
}

#ifdef NON_MATCHING
/* 94.5 %: the original puts `move a0, v1` (the call's first argument) in the jal's delay slot, after the two stores;
 * every form tried schedules it before them. */
void func_80032008(s16 arg0, s32 arg1, UnkStruct9 *arg2) {
    s16 var_v0;

    if (arg0 != -1) {
        arg2->unk_0A = 9;
        var_v0 = 0x32;
    } else {
        arg2->unk_0A = 0x10;
        var_v0 = 0x33;
    }
    arg2->unk_0C = 0;
    arg2->unk_08 = var_v0;
    func_80032630(arg1, arg2);
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80032008);
#endif

void func_80032064(s32 arg0, UnkStruct9 *arg1) {
    s16 var_v0;
    s32 var_v1;

    arg1->unk_36 = 0;
    if (arg1->unk_0C == 1) {
        arg1->unk_0C = 0;
        if (D_800AA248.unk_20->pos_y.w <= 0x5F0000) {
            var_v1 = 0x30000;
            arg1->unk_0A = 0xB;
            var_v0 = 0x3C;
        } else {
            var_v1 = 0x2C000;
            arg1->unk_0A = 0xA;
            var_v0 = 0x3B;
        }
        arg1->unk_08 = var_v0;
        arg1->unk_24 = 1;
        D_800AA248.unk_20->vel_y.w = var_v1;
        func_8003E788(arg1);
        D_800AA248.unk_20->unk_80 = 0x353;
        func_80032630(arg0, arg1);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_8003212C);

void func_800322AC(s32 arg0, UnkStruct9 *arg1) {
    if (arg1->unk_0C == 1) {
        arg1->unk_0A = 0xE;
        arg1->unk_0C = 0;
        arg1->unk_08 = 0x1E;
        func_80032630(arg0, arg1);
    }
}

void func_800322E8(s32 arg0, UnkStruct9 *arg1) {
    if (arg1->unk_0C == 1) {
        arg1->unk_0A = 0xF;
        arg1->unk_08 = 0x46;
        arg1->unk_0C = 0;
        if (D_800AA248.unk_20->flags & 0x10) {
            D_800AA248.unk_20->vel_x.w = 0x28000;
        } else {
            D_800AA248.unk_20->vel_x.w = 0xFFFD8000;
        }
        func_80032630(arg0, arg1);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80032350);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80032530);

void func_80032630(s32 handlers, UnkStruct9 *r) {
    void (**h)(UnkStruct9 *);

    h = (void (**)(UnkStruct9 *)) handlers;
    h += r->unk_0A;
    (*h)(r);
}


void func_80032668(s32 arg0) {
    func_80031CB4(D_8007D280, arg0);
}

void func_80032690(s32 n, UnkStruct9 *r) {
    s32 v;

    if (r->unk_0C == 1) {
        r->unk_0A = 0xF;
        r->unk_08 = 0x46;
        r->unk_0C = 0;
        v = -0x8000;
        if (D_800AA248.unk_20->flags & 0x10) {
            v = 0x8000;
        }
        D_800AA248.unk_20->vel_x.w = v;
        D_800AA248.unk_20->pos_y.u.hi += 5;
        func_80032630(n, r);
    }
}


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
    func_8003EB5C(D_80091B98, D_800AA248.unk_20);
}

void func_800327B4(void) {
    func_8003EB5C(D_80091BC8, D_800AA248.unk_20);
}

void func_800327E0(void) {
    func_8003EB5C(D_80091BF8, D_800AA248.unk_20);
}

void func_8003280C(void) {
    func_8003EB5C(D_80091C04, D_800AA248.unk_20);
}

void func_80032838(void) {
    func_8003EB5C(D_80091C30, D_800AA248.unk_20);
}

void func_80032864(void) {
    func_8003EB5C(D_80091C48, D_800AA248.unk_20);
}

void func_80032890(void) {
    func_8003EB5C(D_80091C88, D_800AA248.unk_20);
}

void func_800328BC(void) {
    func_8003EB5C(D_80091CC0, D_800AA248.unk_20);
}

void func_800328E8(void) {
    func_8003EB5C(D_80091CF8, D_800AA248.unk_20);
}

void func_80032914(void) {
    func_8003EB5C(D_80091D38, D_800AA248.unk_20);
}

void func_80032940(void) {
    func_8003EB5C(D_80091D68, D_800AA248.unk_20);
}

void func_8003296C(void) {
    func_8003EB5C(D_80091DC4, D_800AA248.unk_20);
}

void func_80032998(void) {
    func_8003EB5C(D_80091D90, D_800AA248.unk_20);
}

void func_800329C4(void) {
    func_8003EB5C(D_80091DD0, D_800AA248.unk_20);
}

void func_800329F0(void) {
    func_8003EB5C(D_80091E04, D_800AA248.unk_20);
}

void func_80032A1C(void) {
    func_8003EB5C(D_80091E34, D_800AA248.unk_20);
}

void func_80032A48(void) {
    func_8003EB5C(D_80091E40, D_800AA248.unk_20);
}

void func_80032A74(void) {
    func_8003EB5C(D_80091E80, D_800AA248.unk_20);
}

void func_80032AA0(void) {
    func_8003EB5C(D_80091EF0, D_800AA248.unk_20);
}

void func_80032ACC(void) {
    func_8003EB5C(D_80091F30, D_800AA248.unk_20);
}

void func_80032AF8(void) {
    func_8003EB5C(D_80091F68, D_800AA248.unk_20);
}

void func_80032B24(void) {
    func_8003EB5C(D_80091FA0, D_800AA248.unk_20);
}

void func_80032B50(void) {
    func_8003EB5C(D_80091FE0, D_800AA248.unk_20);
}

void func_80032B7C(void) {
    func_8003EB5C(D_80092010, D_800AA248.unk_20);
}

void func_80032BA8(void) {
    func_8003EB5C(D_8009206C, D_800AA248.unk_20);
}

void func_80032BD4(void) {
    func_8003EB5C(D_80092038, D_800AA248.unk_20);
}

void func_80032C00(void) {
    func_8003EB5C(D_80092078, D_800AA248.unk_20);
}

void func_80032C2C(void) {
    func_8003EB5C(D_800920A8, D_800AA248.unk_20);
}

void func_80032C58(void) {
    func_8003EB5C(D_800920D8, D_800AA248.unk_20);
}

void func_80032C84(void) {
    func_8003EB5C(D_800920E4, D_800AA248.unk_20);
}

void func_80032CB0(void) {
    func_8003EB5C(D_80092124, D_800AA248.unk_20);
}

void func_80032CDC(void) {
    func_8003EB5C(D_8009213C, D_800AA248.unk_20);
}

void func_80032D08(void) {
    func_8003EB5C(D_80092164, D_800AA248.unk_20);
}

void func_80032D34(void) {
    func_8003EB5C(D_8009219C, D_800AA248.unk_20);
}

void func_80032D60(void) {
    func_8003EB5C(D_800921D4, D_800AA248.unk_20);
}

void func_80032D8C(void) {
    func_8003EB5C(D_80092214, D_800AA248.unk_20);
}

void func_80032DB8(void) {
    func_8003EB5C(D_80092244, D_800AA248.unk_20);
}

void func_80032DE4(void) {
    func_8003EB5C(D_800922A0, D_800AA248.unk_20);
}

void func_80032E10(void) {
    func_8003EB5C(D_8009226C, D_800AA248.unk_20);
}

void func_80032E3C(void) {
    func_8003EB5C(D_800922AC, D_800AA248.unk_20);
}

void func_80032E68(void) {
    func_8003EB5C(D_800922D4, D_800AA248.unk_20);
}

void func_80032E94(void) {
    func_8003EB5C(D_80092304, D_800AA248.unk_20);
}

void func_80032EC0(void) {
    func_8003EB5C(D_80092310, D_800AA248.unk_20);
}

void func_80032EEC(void) {
    func_8003EB5C(D_80092338, D_800AA248.unk_20);
}

void func_80032F18(void) {
    func_8003EB5C(D_80092350, D_800AA248.unk_20);
}

void func_80032F44(void) {
    func_8003EB5C(D_80092384, D_800AA248.unk_20);
}

void func_80032F70(void) {
    func_8003EB5C(D_800923BC, D_800AA248.unk_20);
}

void func_80032F9C(void) {
    func_8003EB5C(D_800923F4, D_800AA248.unk_20);
}

void func_80032FC8(void) {
    func_8003EB5C(D_80092404, D_800AA248.unk_20);
}

void func_80032FF4(void) {
    func_8003EB5C(D_8009245C, D_800AA248.unk_20);
}

void func_80033020(void) {
    func_8003EB5C(D_8009248C, D_800AA248.unk_20);
}

void func_8003304C(void) {
    func_8003EB5C(D_800924E8, D_800AA248.unk_20);
}

void func_80033078(void) {
    func_8003EB5C(D_800924B4, D_800AA248.unk_20);
}

void func_800330A4(void) {
    func_8003EB5C(D_800924F4, D_800AA248.unk_20);
}

void func_800330D0(void) {
    func_8003EB5C(D_80092534, D_800AA248.unk_20);
}

void func_800330FC(void) {
    func_8003EB5C(D_80092574, D_800AA248.unk_20);
}

void func_80033128(void) {
    func_8003EB5C(D_80092580, D_800AA248.unk_20);
}

void func_80033154(void) {
    func_8003EB5C(D_800925C0, D_800AA248.unk_20);
}

void func_80033180(void) {
    func_8003EB5C(D_800925D8, D_800AA248.unk_20);
}

void func_800331AC(void) {
    func_8003EB5C(D_80092604, D_800AA248.unk_20);
}

void func_800331D8(void) {
    func_8003EB5C(D_8009262C, D_800AA248.unk_20);
}

void func_80033204(void) {
    func_8003EB5C(D_80092654, D_800AA248.unk_20);
}

void func_80033230(void) {
    func_8003EB5C(D_8009268C, D_800AA248.unk_20);
}

void func_8003325C(void) {
    func_8003EB5C(D_800926B4, D_800AA248.unk_20);
}

void func_80033288(void) {
    func_8003EB5C(D_80092710, D_800AA248.unk_20);
}

void func_800332B4(void) {
    func_8003EB5C(D_800926DC, D_800AA248.unk_20);
}

void func_800332E0(void) {
    func_8003EB5C(D_8009271C, D_800AA248.unk_20);
}

void func_8003330C(void) {
    func_8003EB5C(D_80092754, D_800AA248.unk_20);
}

void func_80033338(void) {
    func_8003EB5C(D_8009278C, D_800AA248.unk_20);
}

void func_80033364(void) {
    func_8003EB5C(D_80092798, D_800AA248.unk_20);
}

void func_80033390(void) {
    func_8003EB5C(D_800927D4, D_800AA248.unk_20);
}

void func_800333BC(void) {
    func_8003EB5C(D_800927EC, D_800AA248.unk_20);
}

void func_800333E8(void) {
    func_8003EB5C(D_80092818, D_800AA248.unk_20);
}

void func_80033414(void) {
    func_8003EB5C(D_80092840, D_800AA248.unk_20);
}

void func_80033440(void) {
    func_8003EB5C(D_80092868, D_800AA248.unk_20);
}

void func_8003346C(void) {
    func_8003EB5C(D_800928A0, D_800AA248.unk_20);
}

void func_80033498(void) {
    func_8003EB5C(D_800928C8, D_800AA248.unk_20);
}

void func_800334C4(void) {
    func_8003EB5C(D_80092924, D_800AA248.unk_20);
}

void func_800334F0(void) {
    func_8003EB5C(D_800928F0, D_800AA248.unk_20);
}

void func_8003351C(void) {
    func_8003EB5C(D_80092930, D_800AA248.unk_20);
}

void func_80033548(void) {
    func_8003EB5C(D_8009296C, D_800AA248.unk_20);
}

void func_80033574(void) {
    func_8003EB5C(D_800929A4, D_800AA248.unk_20);
}

void func_800335A0(void) {
    func_8003EB5C(D_800929B0, D_800AA248.unk_20);
}

void func_800335CC(void) {
    func_8003EB5C(D_800929D8, D_800AA248.unk_20);
}

void func_800335F8(void) {
    func_8003EB5C(D_80092A64, D_800AA248.unk_20);
}

void func_80033624(void) {
    func_8003EB5C(D_80092A8C, D_800AA248.unk_20);
}

void func_80033650(void) {
    func_8003EB5C(D_80092AB4, D_800AA248.unk_20);
}

void func_8003367C(void) {
    func_8003EB5C(D_80092ADC, D_800AA248.unk_20);
}

void func_800336A8(void) {
    func_8003EB5C(D_80092B1C, D_800AA248.unk_20);
}

void func_800336D4(void) {
    func_8003EB5C(D_80092B54, D_800AA248.unk_20);
}

void func_80033700(void) {
    func_8003EB5C(D_80092B7C, D_800AA248.unk_20);
}

void func_8003372C(void) {
    func_8003EB5C(D_80092BD8, D_800AA248.unk_20);
}

void func_80033758(void) {
    func_8003EB5C(D_80092BA4, D_800AA248.unk_20);
}

void func_80033784(void) {
    func_8003EB5C(D_800934A0, D_800AA248.unk_20);
}

void func_800337B0(void) {
    func_8003EB5C(D_800934DC, D_800AA248.unk_20);
}

void func_800337DC(void) {
    func_8003EB5C(D_80093538, D_800AA248.unk_20);
}

void func_80033808(void) {
    func_8003EB5C(D_80093548, D_800AA248.unk_20);
}

void func_80033834(void) {
    func_8003EB5C(D_8009363C, D_800AA248.unk_20);
}

void func_80033860(void) {
    func_8003EB5C(D_80093698, D_800AA248.unk_20);
}

void func_8003388C(void) {
    func_8003EB5C(D_80093768, D_800AA248.unk_20);
}

void func_800338B8(void) {
    func_8003EB5C(D_800937A8, D_800AA248.unk_20);
}

void func_800338E4(void) {
    func_8003EB5C(D_8009382C, D_800AA248.unk_20);
}

void func_80033910(void) {
    func_8003EB5C(D_800937F4, D_800AA248.unk_20);
}

void func_8003393C(void) {
    func_8003EB5C(D_80093864, D_800AA248.unk_20);
}

void func_80033968(void) {
    func_8003EB5C(D_8009388C, D_800AA248.unk_20);
}

void func_80033994(void) {
    func_8003EB5C(D_800937E8, D_800AA248.unk_20);
}

void func_800339C0(void) {
    func_8003EB5C(D_800938AC, D_800AA248.unk_20);
}

void func_800339EC(void) {
    func_8003EB5C(D_80092BE4, D_800AA248.unk_20);
}

void func_80033A18(void) {
    func_8003EB5C(D_80092C20, D_800AA248.unk_20);
}

void func_80033A44(void) {
    func_8003EB5C(D_80092C7C, D_800AA248.unk_20);
}

void func_80033A70(void) {
    func_8003EB5C(D_80092C8C, D_800AA248.unk_20);
}

void func_80033A9C(void) {
    func_8003EB5C(D_80092D88, D_800AA248.unk_20);
}

void func_80033AC8(void) {
    func_8003EB5C(D_80092DE4, D_800AA248.unk_20);
}

void func_80033AF4(void) {
    func_8003EB5C(D_80092EB4, D_800AA248.unk_20);
}

void func_80033B20(void) {
    func_8003EB5C(D_80092EDC, D_800AA248.unk_20);
}

void func_80033B4C(void) {
    func_8003EB5C(D_80092F48, D_800AA248.unk_20);
}

void func_80033B78(void) {
    func_8003EB5C(D_80092F10, D_800AA248.unk_20);
}

void func_80033BA4(void) {
    func_8003EB5C(D_80092F80, D_800AA248.unk_20);
}

void func_80033BD0(void) {
    func_8003EB5C(D_80092FA8, D_800AA248.unk_20);
}

void func_80033BFC(void) {
    func_8003EB5C(D_80092F04, D_800AA248.unk_20);
}

void func_80033C28(void) {
    func_8003EB5C(D_80092FC8, D_800AA248.unk_20);
}

void func_80033C54(void) {
    func_8003EB5C(D_80093008, D_800AA248.unk_20);
}

void func_80033C80(void) {
    func_8003EB5C(D_80093064, D_800AA248.unk_20);
}

void func_80033CAC(void) {
    func_8003EB5C(D_800930BC, D_800AA248.unk_20);
}

void func_80033CD8(void) {
    func_8003EB5C(D_800930C8, D_800AA248.unk_20);
}

void func_80033D04(void) {
    func_8003EB5C(D_8009314C, D_800AA248.unk_20);
}

void func_80033D30(void) {
    func_8003EB5C(D_8009321C, D_800AA248.unk_20);
}

void func_80033D5C(void) {
    func_8003EB5C(D_800932F4, D_800AA248.unk_20);
}

void func_80033D88(void) {
    func_8003EB5C(D_80093324, D_800AA248.unk_20);
}

void func_80033DB4(void) {
    func_8003EB5C(D_80093360, D_800AA248.unk_20);
}

void func_80033DE0(void) {
    func_8003EB5C(D_80093370, D_800AA248.unk_20);
}

void func_80033E0C(void) {
    func_8003EB5C(D_80093398, D_800AA248.unk_20);
}

void func_80033E38(void) {
    func_8003EB5C(D_800933B0, D_800AA248.unk_20);
}

void func_80033E64(void) {
    func_8003EB5C(D_80093354, D_800AA248.unk_20);
}

void func_80033E90(void) {
    func_8003EB5C(D_800938EC, D_800AA248.unk_20);
}

void func_80033EBC(void) {
    func_8003EB5C(D_8009393C, D_800AA248.unk_20);
}

void func_80033EE8(void) {
    func_8003EB5C(D_80093988, D_800AA248.unk_20);
}

void func_80033F14(void) {
    func_8003EB5C(D_80093994, D_800AA248.unk_20);
}

void func_80033F40(void) {
    func_8003EB5C(D_800939CC, D_800AA248.unk_20);
}

void func_80033F6C(void) {
    func_8003EB5C(D_80093A1C, D_800AA248.unk_20);
}

void func_80033F98(void) {
    func_8003EB5C(D_80093AD4, D_800AA248.unk_20);
}

void func_80033FC4(void) {
    func_8003EB5C(D_80093AFC, D_800AA248.unk_20);
}

void func_80033FF0(void) {
    func_8003EB5C(D_80093B24, D_800AA248.unk_20);
}

void func_8003401C(void) {
    func_8003EB5C(D_80093B3C, D_800AA248.unk_20);
}

void func_80034048(void) {
    func_8003EB5C(D_80093B74, D_800AA248.unk_20);
}

void func_80034074(void) {
    func_8003EB5C(D_80093B9C, D_800AA248.unk_20);
}

void func_800340A0(void) {
    func_8003EB5C(D_8009397C, D_800AA248.unk_20);
}

void func_800340CC(void) {
    func_8003EB5C(D_80093BBC, D_800AA248.unk_20);
}

void func_800340F8(void) {
    func_8003EB5C(D_80093C00, D_800AA248.unk_20);
}

void func_80034124(void) {
    func_8003EB5C(D_80093C28, D_800AA248.unk_20);
}

void func_80034150(void) {
    func_8003EB5C(D_80093C50, D_800AA248.unk_20);
}

void func_8003417C(void) {
    func_8003EB5C(D_80093C68, D_800AA248.unk_20);
}

void func_800341A8(void) {
    func_8003EB5C(D_80093C80, D_800AA248.unk_20);
}

void func_800341D4(void) {
    func_8003EB5C(D_80093CA4, D_800AA248.unk_20);
}

void func_80034200(void) {
    func_8003EB5C(D_80093CD0, D_800AA248.unk_20);
}

void func_8003422C(void) {
    func_8003EB5C(D_80093D10, D_800AA248.unk_20);
}

void func_80034258(void) {
    func_8003EB5C(D_80093D50, D_800AA248.unk_20);
}

void func_80034284(void) {
    func_8003EB5C(D_80093D60, D_800AA248.unk_20);
}

void func_800342B0(void) {
    func_8003EB5C(D_80093DD8, D_800AA248.unk_20);
}

void func_800342DC(void) {
    func_8003EB5C(D_80093E30, D_800AA248.unk_20);
}

void func_80034308(void) {
    func_8003EB5C(D_80093EF8, D_800AA248.unk_20);
}

void func_80034334(void) {
    func_8003EB5C(D_80093C5C, D_800AA248.unk_20);
}

void func_80034360(void) {
    func_8003EB5C(D_80093F10, D_800AA248.unk_20);
}

void func_8003438C(void) {
    (D_800AA248.unk_20->owner.item)->unk_36 = 1;
}

void func_800343A8(void) {
    (D_800AA248.unk_20->owner.item)->unk_36 = 0;
}

void func_800343C0(void) {
    func_8003EB5C(D_80093F44, D_800AA248.unk_20);
}

void func_800343EC(void) {
    func_8003EB5C(D_80093F44, D_800AA248.unk_20);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_80034418);

INCLUDE_ASM("asm/main/nonmatchings/game_8002A330", func_800344B8);
