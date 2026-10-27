/* The attackers: the military units (soldiers, vehicles, helicopters...) that hunt the monsters. A pool of four
 * Attacker slots, each driving one GameObject through a state machine: one handler per state and attacker type,
 * in function tables elsewhere. Named after its first function until the rest is understood.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "game_80043E28.h"
#include "psyq/libc2.h"

void func_8003EB5C(void *anim, GameObject *obj);           /* start an animation on obj */
void func_8001E698(GameObject *obj, void *anim);           /* start an animation on obj (the other calling order) */
u16 func_8003E79C(void);
s32 func_8001EB10(s32 range, s32 arg1);                     /* a random number */
void func_80034B68(s32 vel);
void func_8001E4B0(GameObject *obj);                        /* free an object */
ObjectDef *func_8001D110(void);                             /* a fresh definition to fill in */
GameObject *func_8001DCB4(void);                            /* create the object of D_800AA248.new_def */
void func_80053D68(s32, Monster *m);
void func_8005E0E8(Monster *m);
void func_80047554(void *anim, Attacker *a);
void func_800475F4();                   /* game_8004750C */
u16 func_8004B6C4(GameObject *obj, s32, s32);
void func_8001E39C(GameObject *obj);
void func_8001E2F8(GameObject *obj);


/* Animations (.data) */
extern u8 D_800953BC[], D_800951A8[], D_800950EC[], D_80094EC0[], D_80094ECC[], D_80094ED8[],
    D_80094E1C[], D_80094E28[], D_80094E34[], D_80094E40[], D_80094EB0[], D_80094C9C[], D_80094CB0[], D_80094C10[],
    D_80094C2C[], D_80094C38[], D_80094BA8[], D_80094B54[], D_8009540C[], D_80095274[], D_80093418[], D_800951B4[],
    D_80093460[], D_80095204[], D_800933D4[], D_80095268[], D_8009346C[], D_80095388[], D_800933E0[], D_80095300[],
    D_80095354[], D_80095348[], D_800950F8[], D_80095128[], D_80095064[], D_80095094[],
    D_80094FC0[], D_80095058[], D_80094F7C[], D_80094FB4[], D_80094EF0[], D_80094EFC[], D_80094F20[], D_80094DDC[],
    D_80094DE8[], D_80094CBC[], D_80094C4C[], D_80094C58[], D_80094C8C[], D_80094BC4[], D_80094BD0[], D_80094B9C[],
    D_80094B68[];

/* This file's handlers, in the order the state machines reach them. */
void func_80044204(Attacker *a);
s32 func_80044240(u16 kind, s16 x, s16 y, u16 flags, s32 vel_x, u16 state);
void func_80044418();                   /* (Attacker *a); some callers pass nothing */
void func_800455CC(Attacker *a);
void func_80044790(Attacker *a);
void func_80045A74(void);
u16 func_80045AB0(void);
void func_8004578C(Attacker *a);
void func_80045848(Attacker *a);
void func_80045884(Attacker *a);
void func_80045EF0(Attacker *a);
void func_80045F70(Attacker *a);
void func_80045FCC(Attacker *a);
void func_80046254(Attacker *a);
void func_80046490(Attacker *a);
void func_8004654C(Attacker *a);
void func_80046588(Attacker *a);
void func_800468F0(Attacker *a);
void func_80046BD4(Attacker *a);
void func_80046D5C(Attacker *a);
void func_80046EC0(Attacker *a);
void func_8004415C(Attacker *a);
void func_80044494(Attacker *a);
void func_80044E08(Attacker *a);
void func_8004510C(Attacker *a);
void func_800455F0(Attacker *a);
void func_80045B58(Attacker *a);
void func_80045E54(Attacker *a);
void func_800460F8(Attacker *a);
void func_80046340(Attacker *a);
void func_80046794(Attacker *a);
void func_80046A78(Attacker *a);
void func_80046D84(Attacker *a);
void func_80044E98(Attacker *a);
void func_80044F08(Attacker *a);
void func_80044FD4(Attacker *a);
void func_80045040(void);
void func_8004507C(void);
void func_800451CC(Attacker *a);
void func_8004523C(Attacker *a);
void func_80045308(Attacker *a);
void func_80045348(void);
void func_80045384(void);
void func_8004538C(Attacker *a);
void func_80045424(Attacker *a);
void func_800456D0(Attacker *a);
void func_800457C8(Attacker *a);
void func_8004595C(Attacker *a);
void func_8004570C(Attacker *a);
void func_800458DC(Attacker *a);
void func_80045A2C(Attacker *a);
void func_80045CC0(Attacker *a);
void func_80045D14(Attacker *a);
void func_80045C68(void);
void func_80045C94(void);
void func_80045C14(Attacker *a);
void func_80046198(Attacker *a);
void func_800461D4(Attacker *a);
void func_800462A8(Attacker *a);
void func_80046420(Attacker *a);
void func_800464CC(Attacker *a);
void func_80046660(Attacker *a);
void func_80046470(Attacker *a);
void func_800465E0(Attacker *a);
void func_8004674C(Attacker *a);
void func_80046834(Attacker *a);
void func_80046870(Attacker *a);
void func_8004694C(Attacker *a);
void func_80046B18(Attacker *a);
void func_80046B54(Attacker *a);
void func_80046C30(Attacker *a);
void func_80046E24(Attacker *a);
void func_80046E84(Attacker *a);
void func_80046F60(void);
void func_80044638(Attacker *a);
void func_800446E4(Attacker *a);
void func_80044A08(Attacker *a);
void func_8004489C(Attacker *a);
void func_800447F0(Attacker *a);
void func_80044B28(Attacker *a);
void func_80044BE0(Attacker *a);
void func_80044CC8(Attacker *a);
void func_80044584(Attacker *a);

void func_80043E28(void) {
    func_8003EB5C(D_8008E6AC, D_800AA248.cur_obj);
}

void func_80043E54(void) {
    func_8003EB5C(D_8008E6AC, D_800AA248.cur_obj);
}

void func_80043E80(void) {
    func_8003EB5C(D_8008E6AC, D_800AA248.cur_obj);
}

void func_80043EAC(void) {
    func_8003EB5C(D_8008E6AC, D_800AA248.cur_obj);
}

void func_80043ED8(void) {
    func_8003EB5C(D_8008E6AC, D_800AA248.cur_obj);
}

void func_80043F04(void) {
    func_8003EB5C(D_8008E6AC, D_800AA248.cur_obj);
}

void func_80043F30(void) {
    Attacker *a;
    u16 n;

    n = 4;
    a = D_801FA8A8;
    do {
        func_800455CC(a);
        a++;
    } while (--n != 0);
    D_801E1C84 = n;
}

void func_80043F84(void) {
    u16 left;
    Attacker *a;
    u16 i;

    i = 0;
    if (D_801E1C84 != 0) {
        a = D_801FA8A8;
        left = D_801E1C84;
        if (left >= 5) {
            left = 4;
        }
        do {
            if (a->type != 0) {
                func_8004402C(a);
            } else {
                left++;
            }
            a++;
            if (++i >= 5) {
                break;
            }
        } while (--left != 0);
    }
}

void func_8004402C(Attacker *a) {
    D_800AA248.cur_obj = a->obj;
    if (a->type != 0) {
        func_8004415C(a);
        if (a->state != 0x1E) {
            switch (a->type) {
            case 1:
                func_80044E08(a);
                return;
            case 8:
            case 9:
                func_80044494(a);
                return;
            case 7:
                func_8004510C(a);
                return;
            case 2:
                func_800455F0(a);
                return;
            case 3:
                func_80045E54(a);
                return;
            case 11:
                func_80046340(a);
                return;
            case 4:
                func_80046794(a);
                return;
            case 5:
                func_80046A78(a);
                return;
            case 12:
                func_80046D84(a);
                return;
            case 6:
                func_80045B58(a);
                return;
            case 10:
                func_800460F8(a);
                break;
            }
        }
    }
}

void func_8004415C(Attacker *a) {
    if (a->state != 0x1E) {
        func_8003E79C();
        if (D_800AA248.unk_4C != 0) {
            a->state = 0x1E;
            func_8001E698(D_800AA248.cur_obj, D_8009540C);
            if ((u16) D_800AA248.cur_obj->unk_80 < 0x390) {
                D_800AA248.cur_obj->unk_80 = 0x390;
                func_8001E39C(D_800AA248.cur_obj);
                func_8001E2F8(D_800AA248.cur_obj);
            }
        }
    }
}

void func_80044204(Attacker *a) {
    a->unk_18 = 0;
    a->unk_20 = 0;
    a->state = 0xD;
    func_8003EB5C(D_800953BC, D_800AA248.cur_obj);
}

#ifdef NON_MATCHING
/* 85%: the original keeps the address of D_800AA248 and the value of D_801E1C84 live across the search loop (no reload at the found slot), with the counter in a0; the loop form that does that is not found yet */
s32 func_80044240(u16 kind, s16 x, s16 y, u16 flags, s32 vel_x, u16 state) {
    GameObject *saved;
    Attacker *a;
    u16 n;
    ObjectDef *def;

    saved = D_800AA248.cur_obj;
    if (kind != 0 && D_801E1C84 < 4) {
        a = D_801FA8A8;
        n = 4;
        do {
            if (a->type == 0) {
                goto found;
            }
            a++;
        } while (--n != 0);
        D_800AA248.cur_obj = saved;
    }
    return 1;

found:
    D_801E1C84++;
    func_800455CC(a);
    a->type = kind;
    def = func_8001D110();
    D_800AA248.new_def = def;
    def->flags = flags;
    def->unk_0C = 0x717;
    def->id = D_8007F1F4[kind];
    D_800AA248.cur_obj = func_8001DCB4();
    a->unk_16 = 1;
    D_800AA248.cur_obj->pos_x.s.hi = x;
    D_800AA248.cur_obj->pos_y.s.hi = y;
    D_800AA248.cur_obj->vel_x.w = 0;
    a->state = state;
    a->obj = D_800AA248.cur_obj;
    D_800AA248.cur_obj->owner.attacker = a;
    D_800AA248.cur_obj = saved;
    return 0;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_80043E28", func_80044240);
#endif

void func_800443AC(s32 vel) {
    if (func_8001EB10(0x190, 0) & 1) {
        D_800AA248.cur_obj->flags |= 0x10;
    } else {
        D_800AA248.cur_obj->flags &= ~0x10;
    }
    func_80034B68(vel);
}

/* Defined the old way: some handlers call it with no argument (the slot is in a0 from their own argument). */
void func_80044418(a)
Attacker *a;
{
    GameObject *obj = a->obj;

    if (obj != NULL) {
        func_8001E4B0(obj);
        a->obj = NULL;
    }
    a->type = 0;
    D_801E1C84--;
}

void func_80044468(void) {
    func_80044418(D_800AA248.cur_obj->owner.attacker);
}

void func_80044494(Attacker *a) {
    switch (a->state) {
    case 14:
        func_800475F4();
        return;
    case 0:
        func_80044638(a);
        return;
    case 21:
        func_800446E4(a);
        return;
    case 26:
        func_80044A08(a);
        return;
    case 27:
        func_8004489C(a);
        return;
    case 28:
        func_800447F0(a);
        return;
    case 23:
        func_80044B28(a);
        return;
    case 25:
        func_80044BE0(a);
        return;
    case 13:
    case 31:
        func_80044CC8(a);
        return;
    case 29:
        func_80044584(a);
        return;
    default:
        func_80044418(a);
        return;
    }
}

void func_80044584(Attacker *a) {
    s32 vel;

    if (a->unk_18 != 0) {
        func_80044790(a);
        return;
    }
    vel = D_800AA248.cur_obj->vel_y.w + a->unk_10;
    D_800AA248.cur_obj->vel_y.w = vel;
    D_800AA248.cur_obj->pos_y.w += vel;
    if (D_800AA248.cur_obj->pos_y.s.hi >= 0xD9) {
        a->state = 0x1F;
        a->unk_18 = 0;
        a->unk_0A = 0;
        D_800AA248.cur_obj->vel_y.w = 0;
        a->unk_10 = 0;
        func_8003EB5C(D_80095274, D_800AA248.cur_obj);
    }
}

void func_80044638(Attacker *a) {
    GameObject *obj;
    s32 vel;

    a->state = 0x15;
    a->unk_0A = 0;
    obj = D_800AA248.cur_obj;
    if (func_8001EB10(0x3E8, 0) & 1) {
        vel = -0x7000;
    } else {
        vel = 0x7000;
    }
    obj->vel_x.w = vel;
    D_800AA248.cur_obj->vel_y.w = 0xFFFE0000;
    a->unk_10 = 0x4000;
    if (a->type == 9) {
        func_8001E698(D_800AA248.cur_obj, D_80093418);
    } else {
        func_8001E698(D_800AA248.cur_obj, D_800951B4);
    }
}

void func_800446E4(Attacker *a) {
    s32 vel;

    vel = D_800AA248.cur_obj->vel_y.w + a->unk_10;
    if (vel > 0x30000) {
        vel = 0x30000;
    }
    D_800AA248.cur_obj->vel_y.w = vel;
    D_800AA248.cur_obj->pos_y.w += vel;
    if (a->unk_0A != 0) {
        a->state = 0x1A;
        a->unk_0A = 0;
        if (a->type == 9) {
            func_8003EB5C(D_80093460, D_800AA248.cur_obj);
        } else {
            func_8003EB5C(D_80095204, D_800AA248.cur_obj);
        }
    }
}

void func_80044790(Attacker *a) {
    a->state = 0x1D;
    a->unk_18 = 0;
    a->unk_0A = 0;
    if (a->type == 9) {
        func_8003EB5C(D_800933D4, D_800AA248.cur_obj);
    } else {
        func_8003EB5C(D_80095268, D_800AA248.cur_obj);
    }
}

void func_800447F0(Attacker *a) {
    s32 accel;
    s32 vel;

    if (a->hit_by->obj->flags & 0x10) {
        accel = 0x10000;
        vel = 0xFFF90000;
    } else {
        accel = 0xFFFF0000;
        vel = 0x70000;
    }
    D_800AA248.cur_obj->unk_84 = accel;
    D_800AA248.cur_obj->vel_x.w = vel;
    a->state = 0x1B;
    a->unk_18 = 0;
    a->unk_0A = 0;
    if (a->type == 9) {
        func_8003EB5C(D_8009346C, D_800AA248.cur_obj);
    } else {
        func_8003EB5C(D_80095388, D_800AA248.cur_obj);
    }
}

#ifdef NON_MATCHING
/* 96%: the slot is kept in a3 from the entry (a copy of a0) and the ground level in a1; this keeps the slot in a0 */
void func_8004489C(Attacker *a) {
    s32 vel;
    s32 vy;
    s16 ground;

    if (a->unk_18 != 0) {
        func_80044790(a);
        return;
    }
    D_800AA248.cur_obj->pos_x.w += D_800AA248.cur_obj->vel_x.w;
    vel = D_800AA248.cur_obj->vel_x.w + D_800AA248.cur_obj->unk_84;
    D_800AA248.cur_obj->vel_x.w = vel;
    if (vel < 0) {
        vel = -vel;
    }
    if (vel < 0x7001) {
        D_800AA248.cur_obj->unk_84 = 0;
        D_800AA248.cur_obj->vel_x.w = 0;
    }
    vy = D_800AA248.cur_obj->vel_y.w + a->unk_10;
    if (vy > 0xC000) {
        vy = 0xC000;
    }
    D_800AA248.cur_obj->vel_y.w = vy;
    D_800AA248.cur_obj->pos_y.w += vy;
    ground = 0xD9;
    if (a->type == 9) {
        ground = 0xE0;
    }
    if (D_800AA248.cur_obj->pos_y.s.hi >= ground) {
        a->state = 0x17;
        a->unk_0A = 0;
        a->unk_10 = 0;
        D_800AA248.cur_obj->vel_y.w = 0;
        D_800AA248.cur_obj->pos_y.s.hi = ground;
        if (a->type == 9) {
            func_8003EB5C(D_800933E0, D_800AA248.cur_obj);
        } else {
            func_8003EB5C(D_80095300, D_800AA248.cur_obj);
        }
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_80043E28", func_8004489C);
#endif

#ifdef NON_MATCHING
/* 96%: as func_8004489C, the slot register */
void func_80044A08(Attacker *a) {
    s32 vel;
    s16 ground;

    if (a->unk_18 != 0) {
        func_800447F0(a);
        return;
    }
    D_800AA248.cur_obj->pos_x.w += D_800AA248.cur_obj->vel_x.w;
    vel = D_800AA248.cur_obj->vel_y.w + a->unk_10;
    if (vel > 0xC000) {
        vel = 0xC000;
    }
    D_800AA248.cur_obj->vel_y.w = vel;
    D_800AA248.cur_obj->pos_y.w += vel;
    ground = 0xD9;
    if (a->type == 9) {
        ground = 0xE0;
    }
    if (D_800AA248.cur_obj->pos_y.s.hi >= ground) {
        a->state = 0x17;
        a->unk_0A = 0;
        a->unk_10 = 0;
        D_800AA248.cur_obj->vel_y.w = 0;
        D_800AA248.cur_obj->pos_y.s.hi = ground;
        if (a->type == 9) {
            func_8003EB5C(D_800933E0, D_800AA248.cur_obj);
        } else {
            func_8003EB5C(D_80095300, D_800AA248.cur_obj);
        }
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_80043E28", func_80044A08);
#endif

void func_80044B28(Attacker *a) {
    if (func_8003E79C() == 1) {
        func_80044418(a);
        return;
    }
    if (a->unk_0A != 0) {
        func_800443AC(0xFFFE0000);
        D_800AA248.cur_obj->unk_80 = D_800AA248.cur_obj->pos_y.s.hi + 0xF23;
        a->state = 0x19;
        a->unk_0A = 0;
        if (a->type == 9) {
            func_8003EB5C(D_800938AC, D_800AA248.cur_obj);
        } else {
            func_8003EB5C(D_80095354, D_800AA248.cur_obj);
        }
    }
}

void func_80044BE0(Attacker *a) {
    if (func_8003E79C() == 1) {
        func_80045A74();
    }
    if (a->unk_20 != 0) {
        func_80044204(a);
        return;
    }
    if (a->unk_22 != 0) {
        if (a->type == 9) {
            func_80047554(D_800937E8, a);
        } else {
            func_80047554(D_80095348, a);
        }
        return;
    }
    D_800AA248.cur_obj->pos_x.w = (D_800AA248.cur_obj->pos_x.w + D_800AA248.cur_obj->vel_x.w) & D_801D8864.w;
    if (D_800AA248.cur_obj->unk_6C & 0x80) {
        func_80044418(a);
    }
}

void func_80044CC8(Attacker *a) {
    Monster *m;

    if (a->unk_18 != 0) {
        m = a->hit_by;
        func_80053D68(8, m);
        func_8005E0E8(m);
        m->action = 8;
        D_800AA248.cur_obj->pos_y.w = 0x02000000;
        a->unk_18 = 0;
    }
}

void func_80044D34(void) {
    s16 y;

    if (func_8003E79C() == 0) {
        y = D_800AA248.cur_obj->pos_y.s.hi;
        if (y < 0x99) {
            func_80044240(8, D_800AA248.cur_obj->pos_x.s.hi, y, 0x1004, D_800AA248.cur_obj->vel_x.w, 0);
        }
    }
}

void func_80044D94(void) {
    s16 y;

    if (func_8003E79C() == 0) {
        y = D_800AA248.cur_obj->pos_y.s.hi;
        if (y < 0x99) {
            func_80044240(9, D_800AA248.cur_obj->pos_x.s.hi, y, 0x1004, D_800AA248.cur_obj->vel_x.w, 0);
        }
    }
}

void func_80044DF4(void) {
    D_800AA248.cur_obj->vel_y.w = 0xFFFC0000;
}

void func_80044E08(Attacker *a) {
    switch (a->state) {
    case 0:
        func_80044E98(a);
        return;
    case 1:
        func_80044F08(a);
        return;
    case 2:
        func_80044FD4(a);
        return;
    case 3:
        func_80045040();
        return;
    case 4:
        func_8004507C();
        return;
    }
}

void func_80044E98(Attacker *a) {
    if (D_800AA248.cur_obj->pos_y.s.hi >= 0xE1) {
        a->state = 4;
        return;
    }
    a->state = 1;
    D_800AA248.cur_obj->vel_y.w = 0xFFFE0000;
    a->unk_10 = 0x8000;
    func_8001E698(D_800AA248.cur_obj, D_800950F8);
}

#ifdef NON_MATCHING
/* 99%: register names only: the object in a0 and the mask address in v1, here the other way round */
void func_80044F08(Attacker *a) {
    s32 vel;

    vel = D_800AA248.cur_obj->vel_x.w;
    D_800AA248.cur_obj->pos_x.w = (D_800AA248.cur_obj->pos_x.w + vel) & D_801D8864.w;
    vel = D_800AA248.cur_obj->vel_y.w + 0x8000;
    if (vel > 0x40000) {
        vel = 0x40000;
    }
    D_800AA248.cur_obj->vel_y.w = vel;
    D_800AA248.cur_obj->pos_y.w += vel;
    if (D_800AA248.cur_obj->pos_y.s.hi >= 0xE1) {
        D_800AA248.cur_obj->pos_y.s.hi = 0xE1;
        a->state = 2;
        D_800AA248.cur_obj->vel_y.w = 0;
        a->unk_10 = 0;
        func_8003EB5C(D_80095128, D_800AA248.cur_obj);
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_80043E28", func_80044F08);
#endif

void func_80044FD4(Attacker *a) {
    if (func_8003E79C() == 1) {
        func_80044418(a);
        return;
    }
    if (a->unk_0A != 0) {
        a->state = 3;
        func_8001E698(D_800AA248.cur_obj, D_800951A8);
    }
}

void func_80045040(void) {
    if (D_800AA248.cur_obj->unk_6C & 0x80) {
        func_80044418();
    }
}

void func_8004507C(void) {
}

void func_80045084(void) {
    s16 y;

    if (func_8003E79C() == 0) {
        y = D_800AA248.cur_obj->pos_y.s.hi;
        if (y >= 0xE1) {
            y -= 0x10;
        }
        func_80044240(1, D_800AA248.cur_obj->pos_x.s.hi, y, 0x1004, D_800AA248.cur_obj->vel_x.w, 0);
    }
}

void func_800450F8(void) {
    D_800AA248.cur_obj->unk_80 = 0x1001;
}

void func_8004510C(Attacker *a) {
    switch (a->state) {
    case 0:
        func_800451CC(a);
        return;
    case 1:
        func_8004523C(a);
        return;
    case 2:
        func_80045308(a);
        return;
    case 3:
        func_80045348();
        return;
    case 5:
        func_80045384();
        return;
    case 6:
        func_8004538C(a);
        return;
    case 7:
        func_80045424(a);
        return;
    default:
        func_80044418(a);
        return;
    }
}

void func_800451CC(Attacker *a) {
    if (D_800AA248.cur_obj->pos_y.s.hi >= 0xE1) {
        a->state = 5;
        return;
    }
    a->state = 1;
    D_800AA248.cur_obj->vel_y.w = 0xFFFE0000;
    a->unk_10 = 0x8000;
    func_8001E698(D_800AA248.cur_obj, D_80095064);
}

#ifdef NON_MATCHING
/* 99%: as func_80044F08 */
void func_8004523C(Attacker *a) {
    s32 vel;

    vel = D_800AA248.cur_obj->vel_x.w;
    D_800AA248.cur_obj->pos_x.w = (D_800AA248.cur_obj->pos_x.w + vel) & D_801D8864.w;
    vel = D_800AA248.cur_obj->vel_y.w + 0x8000;
    if (vel > 0x40000) {
        vel = 0x40000;
    }
    D_800AA248.cur_obj->vel_y.w = vel;
    D_800AA248.cur_obj->pos_y.w += vel;
    if (D_800AA248.cur_obj->pos_y.s.hi >= 0xE1) {
        D_800AA248.cur_obj->pos_y.s.hi = 0xE1;
        a->state = 2;
        D_800AA248.cur_obj->vel_y.w = 0;
        a->unk_10 = 0;
        func_8003EB5C(D_80095094, D_800AA248.cur_obj);
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_80043E28", func_8004523C);
#endif

void func_80045308(Attacker *a) {
    if (a->unk_0A != 0) {
        a->state = 3;
        func_8001E698(D_800AA248.cur_obj, D_800950EC);
    }
}

void func_80045348(void) {
    if (D_800AA248.cur_obj->unk_6C & 0x80) {
        func_80044418();
    }
}

void func_80045384(void) {
}

void func_8004538C(Attacker *a) {
    if (D_800AA248.cur_obj->unk_6C & 0x80) {
        func_80044418();
        return;
    }
    if (a->unk_16 != 0) {
        a->unk_16 = 0;
        func_8001E698(D_800AA248.cur_obj, D_80094FC0);
        return;
    }
    if (a->unk_0A != 0) {
        a->unk_0A = 0;
        func_8003EB5C(D_80095058, D_800AA248.cur_obj);
    }
}

void func_80045424(Attacker *a) {
    if (D_800AA248.cur_obj->unk_6C & 0x80) {
        func_80044418();
        return;
    }
    if (a->unk_16 != 0) {
        a->unk_16 = 0;
        func_8001E698(D_800AA248.cur_obj, D_80094F7C);
        return;
    }
    if (a->unk_0A != 0) {
        a->unk_0A = 0;
        func_8003EB5C(D_80094FB4, D_800AA248.cur_obj);
    }
}

void func_800454BC(void) {
    s16 y;

    if (func_8003E79C() == 0) {
        y = D_800AA248.cur_obj->pos_y.s.hi;
        if (y >= 0xE1) {
            y -= 0x10;
        }
        func_80044240(7, D_800AA248.cur_obj->pos_x.s.hi, y, 0x1004, D_800AA248.cur_obj->vel_x.w, 0);
    }
}

void func_80045530(void) {
    D_800AA248.cur_obj->unk_80 = D_800AA248.cur_obj->pos_y.s.hi + 0xF23;
}

void func_80045550(void) {
    Attacker *a = D_800AA248.cur_obj->owner.attacker;

    a->state = D_8007F224[func_8001EB10(0x1F, 0) & 1];
    a->unk_0A = 0;
    a->unk_16 = 1;
}

void func_800455B0(void) {
    D_800AA248.cur_obj->owner.attacker->unk_0A = 1;
}

void func_800455CC(Attacker *a) {
    memset(a, 0, sizeof(Attacker));
}

void func_800455F0(Attacker *a) {
    switch (a->state) {
    case 14:
        func_800475F4();
        return;
    case 13:
        func_80046D5C(a);
        return;
    case 0:
        func_800456D0(a);
        return;
    case 2:
        func_800457C8(a);
        return;
    case 3:
        func_8004595C(a);
        return;
    case 1:
        func_8004570C(a);
        return;
    case 5:
        func_80045884(a);
        return;
    case 9:
        func_800458DC(a);
        return;
    case 10:
        func_80045A2C(a);
        return;
    default:
        func_80044418(a);
        return;
    }
}

void func_800456D0(Attacker *a) {
    a->timer = 0x15;
    a->state = 1;
    func_8001E698(D_800AA248.cur_obj, D_80094EC0);
}

void func_8004570C(Attacker *a) {
    if (a->unk_20 != 0) {
        func_80044204(a);
        return;
    }
    if (a->unk_22 != 0) {
        func_80047554(D_80094EF0, a);
        return;
    }
    if (--a->timer < 0) {
        func_8004578C(a);
    }
}

void func_8004578C(Attacker *a) {
    a->timer = 0x141;
    a->state = 2;
    func_8003EB5C(D_80094ECC, D_800AA248.cur_obj);
}

void func_800457C8(Attacker *a) {
    if (a->unk_20 != 0) {
        func_80044204(a);
        return;
    }
    if (a->unk_22 != 0) {
        func_80047554(D_80094EF0, a);
        return;
    }
    if (--a->timer < 0) {
        func_80045848(a);
    }
}

void func_80045848(Attacker *a) {
    a->timer = 3;
    a->state = 9;
    func_8003EB5C(D_80094ED8, D_800AA248.cur_obj);
}

void func_80045884(Attacker *a) {
    D_800AA248.cur_obj->vel_y.w = 0;
    func_800443AC(0xFFFF0000);
    a->state = 3;
    func_8003EB5C(D_80094EFC, D_800AA248.cur_obj);
}

void func_800458DC(Attacker *a) {
    if (a->unk_20 != 0) {
        func_80044204(a);
        return;
    }
    if (a->unk_22 != 0) {
        func_80047554(D_80094EF0, a);
        return;
    }
    if (--a->timer < 0) {
        func_80045884(a);
    }
}

void func_8004595C(Attacker *a) {
    if (a->unk_20 != 0) {
        func_80044204(a);
        return;
    }
    if (a->unk_22 != 0) {
        func_80047554(D_80094EF0, a);
        return;
    }
    D_800AA248.cur_obj->pos_x.w = (D_800AA248.cur_obj->pos_x.w + D_800AA248.cur_obj->vel_x.w) & D_801D8864.w;
    if (func_80045AB0() == 1) {
        func_80044418(a);
        return;
    }
    if (func_8003E79C() == 1) {
        func_80045A74();
    }
}

void func_80045A2C(Attacker *a) {
    a->timer = 0;
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    func_8003EB5C(D_80094F20, D_800AA248.cur_obj);
}

void func_80045A74(void) {
    D_800AA248.cur_obj->vel_x.w = -D_800AA248.cur_obj->vel_x.w;
    D_800AA248.cur_obj->flags ^= 0x10;
}

u16 func_80045AB0(void) {
    if (D_800AA248.cur_obj->unk_6C & 0x80) {
        return func_8004B6C4(D_800AA248.cur_obj, 0x12C, D_800AA248.cur_obj->vel_x.w > 0 ? 2 : 1);
    }
    return 0;
}

void func_80045B04(void) {
    D_800AA248.cur_obj->owner.attacker->state = 5;
}

void func_80045B20(void) {
    D_800AA248.cur_obj->owner.attacker->state = 6;
}

void func_80045B3C(void) {
    D_800AA248.cur_obj->owner.attacker->state = 7;
}

void func_80045B58(Attacker *a) {
    if (!(D_800AA248.cur_obj->unk_6C & 0x80)) {
        switch (a->state) {
        case 8:
            func_80045CC0(a);
            return;
        case 11:
            func_80045D14(a);
            return;
        case 6:
            func_80045C68();
            return;
        case 7:
            func_80045C94();
            return;
        case 0:
        case 4:
            func_80045C14(a);
            return;
        }
    }
    func_80044418(a);
}

void func_80045C14(Attacker *a) {
    if (a->unk_16 != 0) {
        a->unk_16 = 0;
        func_8001E698(D_800AA248.cur_obj, D_80094E1C);
        return;
    }
    func_8003EB5C(D_80094E1C, D_800AA248.cur_obj);
}

void func_80045C68(void) {
    func_8003EB5C(D_80094E28, D_800AA248.cur_obj);
}

void func_80045C94(void) {
    func_8003EB5C(D_80094E34, D_800AA248.cur_obj);
}

void func_80045CC0(Attacker *a) {
    if (a->unk_16 != 0) {
        a->unk_16 = 0;
        func_8001E698(D_800AA248.cur_obj, D_80094E40);
        return;
    }
    func_8003EB5C(D_80094E40, D_800AA248.cur_obj);
}

void func_80045D14(Attacker *a) {
    if (a->unk_16 != 0) {
        a->unk_16 = 0;
        func_8001E698(D_800AA248.cur_obj, D_80094EB0);
        return;
    }
    func_8003EB5C(D_80094EB0, D_800AA248.cur_obj);
}

void func_80045D68(void) {
    func_80044240(6, D_800AA248.cur_obj->pos_x.s.hi, D_800AA248.cur_obj->pos_y.s.hi - 4, 0x1002, D_800AA248.cur_obj->vel_x.w, 0);
}

void func_80045DB4(void) {
    func_80044240(6, D_800AA248.cur_obj->pos_x.s.hi, D_800AA248.cur_obj->pos_y.s.hi - 4, 0x1003, D_800AA248.cur_obj->vel_x.w, 8);
}

void func_80045E04(void) {
    func_80044240(6, D_800AA248.cur_obj->pos_x.s.hi, D_800AA248.cur_obj->pos_y.s.hi - 4, 0x1003, D_800AA248.cur_obj->vel_x.w, 0xB);
}

void func_80045E54(Attacker *a) {
    switch (a->state) {
    case 14:
        func_800475F4();
        return;
    case 13:
        func_80046D5C(a);
        return;
    case 2:
        func_80045EF0(a);
        return;
    case 3:
        func_80045FCC(a);
        return;
    default:
        func_80044418(a);
        return;
    }
}

void func_80045EF0(Attacker *a) {
    if (a->unk_20 != 0) {
        func_80044204(a);
        return;
    }
    if (a->unk_22 != 0) {
        func_80047554(D_80094DDC, a);
        return;
    }
    if (--a->timer < 0) {
        func_80045F70(a);
    }
}

void func_80045F70(Attacker *a) {
    a->timer = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    func_800443AC(0xFFFF0000);
    a->state = 3;
    func_8003EB5C(D_80094DE8, D_800AA248.cur_obj);
}

void func_80045FCC(Attacker *a) {
    if (a->unk_20 != 0) {
        func_80044204(a);
        return;
    }
    if (a->unk_22 != 0) {
        func_80047554(D_80094DDC, a);
        return;
    }
    D_800AA248.cur_obj->pos_x.w += D_800AA248.cur_obj->vel_x.w;
    D_800AA248.cur_obj->pos_x.w &= D_801D8864.w;
    if (func_80045AB0() == 1) {
        func_80044418(a);
        return;
    }
    if (func_8003E79C() == 1) {
        func_80045A74();
    }
}

void func_800460B8(void) {
    func_80044240(3, D_800AA248.cur_obj->pos_x.s.hi, D_800AA248.cur_obj->pos_y.s.hi, 0x1004, D_800AA248.cur_obj->vel_x.w, 0);
}

void func_800460F8(Attacker *a) {
    switch (a->state) {
    case 14:
        func_800475F4();
        return;
    case 13:
        func_80046D5C(a);
        return;
    case 0:
        func_80046198(a);
        return;
    case 2:
        func_800461D4(a);
        return;
    case 3:
        func_800462A8(a);
        return;
    case 4:
        func_80044418(a);
        return;
    }
}

void func_80046198(Attacker *a) {
    a->timer = 0x3C;
    a->state = 2;
    func_8001E698(D_800AA248.cur_obj, D_80094C9C);
}

void func_800461D4(Attacker *a) {
    if (a->unk_20 != 0) {
        func_80044204(a);
        return;
    }
    if (a->unk_22 != 0) {
        func_80047554(D_80094CB0, a);
        return;
    }
    if (--a->timer < 0) {
        func_80046254(a);
    }
}

void func_80046254(Attacker *a) {
    a->timer = 0;
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    a->state = 3;
    func_8003EB5C(D_80094CBC, D_800AA248.cur_obj);
}

void func_800462A8(Attacker *a) {
    if (a->unk_20 != 0) {
        func_80044204(a);
        return;
    }
    if (a->unk_22 != 0) {
        func_80047554(D_80094CB0, a);
    }
}

void func_80046300(void) {
    func_80044240(0xA, D_800AA248.cur_obj->pos_x.s.hi, D_800AA248.cur_obj->pos_y.s.hi, 0x1004, D_800AA248.cur_obj->vel_x.w, 0);
}

void func_80046340(Attacker *a) {
    switch (a->state) {
    case 14:
        func_800475F4();
        return;
    case 13:
        func_80046D5C(a);
        return;
    case 0:
        func_80046420(a);
        return;
    case 2:
        func_800464CC(a);
        return;
    case 3:
        func_80046660(a);
        return;
    case 1:
        func_80046470(a);
        return;
    case 5:
        func_80046588(a);
        return;
    case 9:
        func_800465E0(a);
        return;
    case 10:
        func_8004674C(a);
        return;
    default:
        func_80044418(a);
        return;
    }
}

void func_80046420(Attacker *a) {
    if (a->unk_0A != 0) {
        func_80046490(a);
        return;
    }
    a->state = 1;
    func_8001E698(D_800AA248.cur_obj, D_80094C10);
}

void func_80046470(Attacker *a) {
    func_80046490(a);
}

void func_80046490(Attacker *a) {
    a->timer = 0x141;
    a->state = 2;
    func_8003EB5C(D_80094C2C, D_800AA248.cur_obj);
}

void func_800464CC(Attacker *a) {
    if (a->unk_20 != 0) {
        func_80044204(a);
        return;
    }
    if (a->unk_22 != 0) {
        func_80047554(D_80094C4C, a);
        return;
    }
    if (--a->timer < 0) {
        func_8004654C(a);
    }
}

void func_8004654C(Attacker *a) {
    a->timer = 3;
    a->state = 9;
    func_8003EB5C(D_80094C38, D_800AA248.cur_obj);
}

void func_80046588(Attacker *a) {
    D_800AA248.cur_obj->vel_y.w = 0;
    func_800443AC(0xFFFE0000);
    a->state = 3;
    func_8003EB5C(D_80094C58, D_800AA248.cur_obj);
}

void func_800465E0(Attacker *a) {
    if (a->unk_20 != 0) {
        func_80044204(a);
        return;
    }
    if (a->unk_22 != 0) {
        func_80047554(D_80094C4C, a);
        return;
    }
    if (--a->timer < 0) {
        func_80046588(a);
    }
}

void func_80046660(Attacker *a) {
    if (a->unk_20 != 0) {
        func_80044204(a);
        return;
    }
    if (a->unk_22 != 0) {
        func_80047554(D_80094C4C, a);
        return;
    }
    D_800AA248.cur_obj->pos_x.w += D_800AA248.cur_obj->vel_x.w;
    D_800AA248.cur_obj->pos_x.w &= D_801D8864.w;
    if (func_80045AB0() == 1) {
        func_80044418(a);
        return;
    }
    if (func_8003E79C() == 1) {
        func_80045A74();
    }
}

void func_8004674C(Attacker *a) {
    a->timer = 0;
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    func_8003EB5C(D_80094C8C, D_800AA248.cur_obj);
}

void func_80046794(Attacker *a) {
    switch (a->state) {
    case 14:
        func_800475F4();
        return;
    case 13:
        func_80046D5C(a);
        return;
    case 0:
        func_80046834(a);
        return;
    case 2:
        func_80046870(a);
        return;
    case 3:
        func_8004694C(a);
        return;
    default:
        func_80044418(a);
        return;
    }
}

void func_80046834(Attacker *a) {
    a->timer = 0x50;
    a->state = 2;
    func_8001E698(D_800AA248.cur_obj, D_80094BA8);
}

void func_80046870(Attacker *a) {
    if (a->unk_20 != 0) {
        func_80044204(a);
        return;
    }
    if (a->unk_22 != 0) {
        func_80047554(D_80094BC4, a);
        return;
    }
    if (--a->timer < 0) {
        func_800468F0(a);
    }
}

void func_800468F0(Attacker *a) {
    a->timer = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    func_800443AC(0xFFFF0000);
    a->state = 3;
    func_8003EB5C(D_80094BD0, D_800AA248.cur_obj);
}

void func_8004694C(Attacker *a) {
    if (a->unk_20 != 0) {
        func_80044204(a);
        return;
    }
    if (a->unk_22 != 0) {
        func_80047554(D_80094BC4, a);
        return;
    }
    D_800AA248.cur_obj->pos_x.w += D_800AA248.cur_obj->vel_x.w;
    D_800AA248.cur_obj->pos_x.w &= D_801D8864.w;
    if (func_80045AB0() == 1) {
        func_80044418(a);
        return;
    }
    if (func_8003E79C() == 1) {
        func_80045A74();
    }
}

void func_80046A38(void) {
    func_80044240(4, D_800AA248.cur_obj->pos_x.s.hi, D_800AA248.cur_obj->pos_y.s.hi, 0x1004, D_800AA248.cur_obj->vel_x.w, 0);
}

void func_80046A78(Attacker *a) {
    switch (a->state) {
    case 14:
        func_800475F4();
        return;
    case 13:
        func_80046D5C(a);
        return;
    case 0:
        func_80046B18(a);
        return;
    case 2:
        func_80046B54(a);
        return;
    case 3:
        func_80046C30(a);
        return;
    default:
        func_80044418(a);
        return;
    }
}

void func_80046B18(Attacker *a) {
    a->timer = 0x50;
    a->state = 2;
    func_8001E698(D_800AA248.cur_obj, D_80094B54);
}

void func_80046B54(Attacker *a) {
    if (a->unk_20 != 0) {
        func_80044204(a);
        return;
    }
    if (a->unk_22 != 0) {
        func_80047554(D_80094B9C, a);
        return;
    }
    if (--a->timer < 0) {
        func_80046BD4(a);
    }
}

void func_80046BD4(Attacker *a) {
    a->timer = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    func_800443AC(0xFFFF0000);
    a->state = 3;
    func_8003EB5C(D_80094B68, D_800AA248.cur_obj);
}

void func_80046C30(Attacker *a) {
    if (a->unk_20 != 0) {
        func_80044204(a);
        return;
    }
    if (a->unk_22 != 0) {
        func_80047554(D_80094B9C, a);
        return;
    }
    D_800AA248.cur_obj->pos_x.w += D_800AA248.cur_obj->vel_x.w;
    D_800AA248.cur_obj->pos_x.w &= D_801D8864.w;
    if (func_80045AB0() == 1) {
        func_80044418(a);
        return;
    }
    if (func_8003E79C() == 1) {
        func_80045A74();
    }
}

void func_80046D1C(void) {
    func_80044240(5, D_800AA248.cur_obj->pos_x.s.hi, D_800AA248.cur_obj->pos_y.s.hi, 0x1004, D_800AA248.cur_obj->vel_x.w, 0);
}

void func_80046D5C(Attacker *a) {
    GameObject *obj = a->obj;

    D_800AA248.cur_obj = obj;
    if (a->unk_18 != 0) {
        obj->pos_y.w = 0x02000000;
    }
}

void func_80046D84(Attacker *a) {
    switch (a->state) {
    case 14:
        func_800475F4();
        return;
    case 13:
        func_80046D5C(a);
        return;
    case 0:
        func_80046E24(a);
        return;
    case 2:
        func_80046E84(a);
        return;
    case 3:
        func_80046F60();
        return;
    default:
        func_80044418(a);
        return;
    }
}

void func_80046E24(Attacker *a) {
    D_800AA248.cur_obj->vel_y.w = 0;
    func_800443AC(0xFFFE0000);
    a->timer = 0x12;
    a->state = 2;
    func_8001E698(D_800AA248.cur_obj, D_80094B54);
}

void func_80046E84(Attacker *a) {
    if (--a->timer < 0) {
        func_80046EC0(a);
    }
}

void func_80046EC0(Attacker *a) {
    if (a->unk_20 != 0) {
        func_80044204(a);
        return;
    }
    if (a->unk_22 != 0) {
        func_80047554(D_80094B54, a);
        return;
    }
    a->timer = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    func_800443AC(0xFFFE0000);
    a->state = 3;
    func_8003EB5C(D_80094B54, D_800AA248.cur_obj);
}

void func_80046F60(void) {
}

#ifdef NON_MATCHING
/* 84%: the search is the while condition (right shape); the original keeps a second pointer to unk_20 as a giv and hoists the constant 1 before the loop */
void func_80046F68(Monster *m) {
    Attacker *a;
    u16 n;
    s32 dx;
    GameObject *o;
    GameObject *saved;
    s16 x;

    a = D_801FA8A8;
    n = 4;
    saved = D_800AA248.cur_obj;
    if (D_801E1C84 != 0) {
        x = m->obj->pos_x.s.hi;
        while ((o = a->obj) == NULL || a->type == 0 || (o->unk_6C & 0x80) ||
               (dx = o->pos_x.s.hi - x, dx < 0 ? -dx : dx) > ((s16) o->size.u.lo >> 1) - 1) {
            a++;
            if (--n == 0) {
                goto end;
            }
        }
        a->unk_20 = 1;
    }
end:
    D_800AA248.cur_obj = saved;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_80043E28", func_80046F68);
#endif

INCLUDE_ASM("asm/main/nonmatchings/game_80043E28", func_80047028);

INCLUDE_ASM("asm/main/nonmatchings/game_80043E28", func_8004718C);
