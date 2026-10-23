/* The monsters' attacks and the objects they throw: script commands that spawn and drive them, the hit tests
 * against monsters, and the attack table. Named after its first function until the rest is understood.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "gameobject.h"
#include "psyq/libc2.h"
#include "game_80043E28.h"           /* Attacker: the attack command func_80047554 drives one */

/* A thrown object's bookkeeping (func_8004B660). */
typedef struct {
    /* 0x00 */ GameObject *obj;
    /* 0x04 */ u8 unk_04[0x04];
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ u16 unk_0A;
    /* 0x0C */ u8 unk_0C[0x02];
    /* 0x0E */ u16 armed;
} Throw;

/* A throw's speed, per attack kind (the table D_8007F2A4, 31 entries). */
typedef struct {
    /* 0x00 */ s32 vx;
    /* 0x04 */ s32 vy;
} ThrowSpeed;

extern ThrowSpeed D_8007F2A4[];
extern s32 D_8008C804;
extern u16 D_801D8850;

void func_8001E4B0(GameObject *obj);                        /* free an object */
void func_8001F724(s32 sound);
void func_8001F7CC(u16 sound, u16 variant);
u16 *func_80025C08(void *);
s32 func_80025DF8(s32 player);
void func_80029118(s32, s32);
void func_80053C50(s32, Monster *m);
void func_8006353C(s32);
u16 func_8004A9B0(Monster *m, s32 a, s32 kind, s16 b, s16 c);
s32 func_8001EB10(s32 range, s32 x);
void func_8004B204(void);
void func_8003EB5C(void *anim, GameObject *obj);
extern s32 D_8008A7A4;
void func_8004B540(void);
void func_8004B754(void);
void func_8004B990(void);
void func_8004B3D0(void);
void func_8004AEA4(void *slot);
void func_8004AD18(Throw *slot);
ObjectDef *func_8001D110(void);
u16 func_80047F64(u16 kind, u16 b, Throw *t);
u16 func_80047DEC(u16 a, u16 b, s16 dx, s16 dy, s32 e);
u16 func_80047EA0(u16 a, u16 b, s32 c);
u16 func_8004B6C4(GameObject *obj, s16 range, s32 mode);
void func_8004EFAC(void);
void func_8004AF80(void);
void func_8004AF1C();

extern u8 D_8007F634[];
extern s16 D_801D8724;
extern Throw D_801E1CC4[];             /* 21 slots */
/* A throw in flight (three records at D_801F9A54): the throwing object, the thrown one and its speed. */
typedef struct {
    /* 0x00 */ GameObject *obj;
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ u16 unk_0A;
    /* 0x0C */ u16 unk_0C;
    /* 0x0E */ u16 unk_0E;
    /* 0x10 */ GameObject *thrown;
    /* 0x14 */ s32 speed;
    /* 0x18 */ void *land_anim;        /* the animation started when the thrown object lands */
} ThrowRec;

extern ThrowRec D_801F9A54[];          /* 3 records */
extern s32 D_801F9AC8;                 /* the camera's x, 16.16 */
extern u16 D_801F9ACA;                 /* its integer half */
extern s32 D_801D8864;                 /* the level's width, 16.16 */
extern u16 D_801D8866;                 /* its integer half */
extern u16 D_801D8740;
extern u16 D_801D8710;
extern u16 D_8007A696;
extern u16 D_8007F28C[];
extern u16 D_8007F298[];
extern s32 D_80096150;
void func_80062E24(s32);
GameObject *func_8001DCB4(void);
extern u16 D_801E2A4C;
extern u16 D_801E2A54;
extern u16 D_801E1C8C;
extern u16 D_801E1C80;
extern u16 D_801E0D60;
extern s16 D_801E28D0;
extern s16 D_801E28F0;
extern s32 D_801FA7D8;
extern s16 D_801E0D4C;


INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004750C);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80047554);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_800475F4);

void func_800476A8(void) {
    u8 *slot;
    u16 n;

    n = 0x15;
    slot = D_801E1CC4;
    do {
        func_8004AEA4(slot);
        slot += 0x10;
    } while (--n != 0);
    D_801D8724 = n;
}

void func_800476FC(void) {
    GameObject *saved = D_800AA248.cur_obj;
    u16 *p = saved->arg.h;
    u16 variant = *p++;
    u16 sound = *p++;
    u16 a = *p;

    if (!(saved->unk_6C & 0x80)) {
        if (variant != 0) {
            func_8001F7CC(sound, variant);
        }
        if (a != 0) {
            func_8004A9B0(0, a, 1, 0, 0);
        }
    }
    D_800AA248.cur_obj = saved;
}

void func_80047780(void) {
    GameObject *saved = D_800AA248.cur_obj;
    u16 *arg = saved->arg.h;
    u16 variant = *arg++;
    u16 sound = *arg;

    if (!(saved->unk_6C & 0x80)) {
        if (variant != 0) {
            func_8001F7CC(sound, variant);
        }
        func_8004A9B0(0, 0, 23, 0, 0);
    }
    D_800AA248.cur_obj = saved;
}

void func_800477F0(void) {
    GameObject *saved = D_800AA248.cur_obj;
    GameObject *obj;
    Monster *m;
    u16 *p;
    s32 id;
    u16 variant;
    u16 sound;
    s16 d;
    s16 dx;
    s16 yoff;
    s16 xoff;

    if (!(saved->unk_6C & 0x80)) {
        m = saved->owner.monster;
        if (m->unk_022 >= 5) {
            m->unk_022 = 0;
        }
        obj = D_800AA248.cur_obj;
        d = (u16) obj->pos_x.p.i - D_801F9ACA;
        dx = d;
        if (d < -0x1F3) {
            dx = D_801D8866 + d;
        }
        if (obj->unk_20.f.flags & 0x10) {
            yoff = 0;
            if (dx >= 0xC9) {
                yoff = -8;
                xoff = -0x10;
                id = D_8007F28C[m->unk_022];
            } else {
                xoff = -0x12;
                id = D_8007F298[m->unk_022];
            }
        } else {
            yoff = -8;
            if (dx < 0xC8) {
                xoff = -0x10;
                id = D_8007F28C[m->unk_022];
            } else {
                yoff = 0;
                xoff = -0x12;
                id = D_8007F298[m->unk_022];
            }
        }
        p = D_800AA248.cur_obj->arg.h;
        variant = *p++;
        sound = *p++;
        if (p != NULL) {
            func_8001F7CC(sound, variant);
        }
        if (id != 0) {
            func_8004A9B0(0, id, 9, yoff, xoff);
            m->unk_022++;
        }
    }
    D_800AA248.cur_obj = saved;
}

void func_8004799C(void) {
    GameObject *saved = D_800AA248.cur_obj;
    u16 *p = saved->arg.h;
    u16 variant = *p++;
    u16 sound = *p++;
    u16 a = *p;

    if (!(saved->unk_6C & 0x80)) {
        if (variant != 0) {
            func_8001F7CC(sound, variant);
        }
        func_8004A9B0(0, a, 17, 0, 0);
    }
    D_800AA248.cur_obj = saved;
}

void func_80047A1C(void) {
    GameObject *saved = D_800AA248.cur_obj;
    u16 *arg = saved->arg.h;
    u16 variant = *arg++;
    u16 sound = *arg;

    if (!(saved->unk_6C & 0x80)) {
        if (variant != 0) {
            func_8001F7CC(sound, variant);
        }
        func_8004A9B0(0, 0, 2, 0, 0);
    }
    D_800AA248.cur_obj = saved;
}

void func_80047A8C(void) {
    GameObject *saved = D_800AA248.cur_obj;
    u16 *arg = saved->arg.h;
    u16 variant = *arg++;
    u16 sound = *arg;

    if (!(saved->unk_6C & 0x80)) {
        if (variant != 0) {
            func_8001F7CC(sound, variant);
        }
        func_8004A9B0(0, 0, 8, 0, 0);
    }
    D_800AA248.cur_obj = saved;
}

void func_80047AFC(void) {
    GameObject *saved = D_800AA248.cur_obj;
    u16 *arg = saved->arg.h;
    u16 variant = *arg++;
    u16 sound = *arg;

    if (!(saved->unk_6C & 0x80)) {
        if (variant != 0) {
            func_8001F7CC(sound, variant);
        }
        func_8004A9B0(0, 0, 11, 0, 0);
    }
    D_800AA248.cur_obj = saved;
}

void func_80047B6C(void) {
    GameObject *saved = D_800AA248.cur_obj;
    Monster *m;
    u16 kind;

    saved->script_pc += 4;
    m = saved->owner.monster;
    kind = m->unk_02A;
    if (kind != 0) {
        GameObject *obj = D_800AA248.cur_obj;
        u16 *p = obj->arg.h;
        s16 variant = *p++;
        u16 sound = *p++;
        u16 a = *p++;
        s16 b = *p++;
        s16 c = *p;

        if (!(obj->unk_6C & 0x80)) {
            if (kind != 1) {
                if (func_8004A9B0(m, a, 5, b, c) == 0) {
                    m->unk_02A = 0;
                    m->unk_01C = func_8001EB10(4, 2);
                }
            } else {
                if (variant != 0) {
                    func_8001F7CC(sound, variant);
                }
                func_8004A9B0(m, a, 6, b, c);
            }
        }
    }
    D_800AA248.cur_obj = saved;
}

void func_80047C9C(void) {
    GameObject *saved = D_800AA248.cur_obj;
    u16 *arg = saved->arg.h;
    u16 variant = *arg++;
    u16 sound = *arg;

    if (!(saved->unk_6C & 0x80)) {
        if (variant != 0) {
            func_8001F7CC(sound, variant);
        }
        func_8004A9B0(0, 0, 3, 0, 0);
    }
    D_800AA248.cur_obj = saved;
}

void func_80047D0C(void) {
    GameObject *saved = D_800AA248.cur_obj;
    u16 *arg = saved->arg.h;
    u16 variant = *arg++;
    u16 sound = *arg;

    if (!(saved->unk_6C & 0x80)) {
        if (variant != 0) {
            func_8001F7CC(sound, variant);
        }
        func_8004A9B0(0, 0, 4, 0, 0);
    }
    D_800AA248.cur_obj = saved;
}

void func_80047D7C(void) {
    GameObject *obj = D_800AA248.cur_obj;
    u16 *p = obj->arg.h;
    u16 variant = *p++;
    u16 sound = *p;

    if (!(obj->unk_6C & 0x80) && variant != 0xFFFF) {
        func_8001F7CC(sound, variant);
    }
}

void func_80047DCC(void) {
    D_800AA248.cur_obj->script_pc = *D_800AA248.cur_obj->arg.w;
}

u16 func_80047DEC(u16 a, u16 b, s16 dx, s16 dy, s32 e) {
    ObjectDef *def;
    s16 x = dx;

    def = func_8001D110();
    D_800AA248.new_def = def;
    if (!(D_800AA248.cur_obj->unk_20.f.flags & 0x10)) {
        x = -dx;
    }
    def->pos_x.p.i = x + (u16) D_800AA248.cur_obj->pos_x.p.i;
    def->pos_y.p.i = dy + (u16) D_800AA248.cur_obj->pos_y.p.i;
    return func_80047F64(a, b, e);
}

u16 func_80047EA0(u16 a, u16 b, s32 c) {
    ObjectDef *def = func_8001D110();
    GameObject *cur;
    SpriteFrame *fr;
    s16 dx;
    s16 dy;
    s16 x;

    D_800AA248.new_def = def;
    cur = D_800AA248.cur_obj;
    fr = cur->frame;
    dx = fr->unk_10 - fr->unk_08;
    x = dx;
    dy = fr->unk_12 - fr->unk_0A;
    if (cur->unk_20.f.flags & 0x10) {
        x = -dx;
    }
    def->pos_x.p.i = x + (u16) cur->pos_x.p.i;
    def->pos_y.p.i = dy + (u16) D_800AA248.cur_obj->pos_y.p.i;
    return func_80047F64(a, b, c);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80047F64);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80048070);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_800481FC);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80048384);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80048558);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004874C);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_800488B8);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_800489C0);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80048B98);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80048D4C);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80048E6C);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80048F60);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_800490D4);

void func_8004928C(void) {
    if (D_800AA248.cur_obj->vel_y.v <= -0x10000) {
        D_800AA248.cur_obj->script_pc = *D_800AA248.cur_obj->arg.w;
    }
}

void func_800492C8(void) {
    if (D_800AA248.cur_obj->vel_y.v <= 0x10000) {
        D_800AA248.cur_obj->script_pc = *D_800AA248.cur_obj->arg.w;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80049304);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_800494B4);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80049650);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80049850);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_800499F4);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80049B9C);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80049D90);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80049E10);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004A044);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004A1F8);

s32 func_8004A468(Monster *m) {
    Monster *target = m->target;
    GameObject *obj;
    s16 r;
    s16 d;

    if (target == NULL || (obj = target->obj) == NULL) {
        return 3;
    }
    d = (u16) D_800AA248.cur_obj->pos_y.p.i - (u16) obj->pos_y.p.i - 0x23;
    if (d <= 0) {
        d = -d;
        r = 4;
        if (d >= 0x18) {
            r = 5;
            if (d >= 0x30) {
                r = 7;
                if (d < 0x48) {
                    r = 6;
                }
            }
        }
    } else if (d < 0x18) {
        r = 3;
    } else if (d < 0x30) {
        r = 2;
    } else {
        r = d < 0x48;
    }
    return r;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004A51C);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004A698);

void func_8004A90C(Monster *m) {
    m->action = 0x20;
    m->obj->vel_y.v = 0xFFF70000;
    m->unk_104 = 0x4000;
    m->unk_100 = 0;
    m->unk_1B0 = 0;
    m->unk_1B2 = 0;
    m->unk_1B4 = 0;
}

#ifdef NON_MATCHING
/* 99%: register names only: the action in v0 and the side in v1 in the original */
void func_8004A93C(Monster *m) {
    s16 action;
    u16 side = m->unk_1B0;

    if (side != 0) {
        action = 0x3A;
        if (side != 3) {
            func_8004EFAC();
            action = 0x12;
        }
    } else {
        action = 0x3A;
        if (m->obj->pos_y.p.i < 0xE1) {
            func_8004EFAC();
            action = 0xF;
        }
    }
    m->action = action;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004A93C);
#endif

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004A9B0);

void func_8004AC84(void) {
    GameObject *saved = D_800AA248.cur_obj;
    Throw *slot;
    u16 i;
    GameObject *obj;

    if (D_801D8724 != 0) {
        slot = D_801E1CC4;
        i = 1;
        do {
            obj = slot->obj;
            D_800AA248.cur_obj = obj;
            if (obj != NULL) {
                func_8004AD18(slot);
            }
            slot++;
        } while ((i += 1) < 22);
    }
    D_800AA248.cur_obj = saved;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004AD18);

void func_8004AE2C(void) {
    void *other = D_800AA248.cur_obj->unk_94.p;

    func_8001E4B0(D_800AA248.cur_obj);
    if (other != NULL) {
        func_8004AEA4(other);
    }
    if (D_801D8724 != 0) {
        D_801D8724 = (u16) D_801D8724 - 1;
    }
}

void func_8004AE84(void) {
    D_800AA248.cur_obj->vel_x.v >>= 1;
}

void func_8004AEA4(void *slot) {
    memset(slot, 0, 0x10);
}

void func_8004AEC8(void) {
    D_800AA248.cur_obj->owner.monster->unk_02A = 0;
}

void func_8004AEE0(void) {
    D_801D8850 = 3;
    func_8004AF1C(*func_80025C08(D_8007F634));
}

/* Defined the old way: func_8004AEE0 above passes it a u16 it reads from a table. */
void func_8004AF1C(arg0)
s16 arg0;
{
    D_801E1C80 = arg0;
    D_801E2A54 = 1;
    D_801E2A4C = 1;
    D_801E1C8C = 0;
    D_801E0D60 = 0;
    D_801E28D0 = 0;
    D_801E28F0 = 0;
    D_801FA7D8 = 0x64;
    func_8004AF80();
}

void func_8004AF80(void) {
    ThrowRec *rec;
    u16 n;

    rec = D_801F9A54;
    n = 3;
    do {
        memset(rec, 0, sizeof(ThrowRec));
        rec++;
    } while (--n != 0);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004AFD4);

void func_8004B038(void) {
    u16 t = D_801E1C80;

    if (t == 0) {
        if (D_801E2A54 == 0xB) {
            return;
        }
reset:
        func_8004AFD4();
        return;
    }
    if (D_801D8740 != 0) {
        t--;
        D_801E1C80 = t;
        switch (t) {
        case 0x537:
            if (!(D_8007A696 & 8)) {
                func_8001F7CC(0x8C, 0x6D);
                D_8007A696 |= 8;
            }
            break;
        case 0x4B0:
            D_801E2A54 = 3;
            D_801E1C8C = 1;
            break;
        case 0x258:
            D_801E2A54 = 4;
            D_801E1C8C = 2;
            break;
        case 0:
            D_801E2A54 = 5;
            D_801E1C8C = 3;
            break;
        }
        if (D_801E2A54 >= 2) {
            if (D_801E2A54 < 6) {
                func_8004B17C();
            } else {
                goto reset;
            }
        }
    }
}

void func_8004B17C(void) {
    if (D_801E1C8C == 1) {
        func_8004B1C8();
        return;
    }
    if (D_801E1C8C < 4) {
        func_8004B3D0();
    }
}

void func_8004B1C8(void) {
    if (D_801E2A4C == 1) {
        func_8004B204();
        D_801E2A54 = 6;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004B204);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004B3D0);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004B540);

u16 func_8004B660(Throw *t, GameObject *target, s16 range, s32 mode) {
    u16 armed = t->armed;

    if (target->unk_6C & 0x80) {
        if (armed != 0) {
            return func_8004B6C4(t->obj, range, mode & 0xFFFF);
        }
    } else if (armed == 0) {
        t->armed = 1;
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004B6C4);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004B754);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004B80C);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004B990);

void func_8004BAC0(void) {
    s32 i;
    s32 id;
    Monster *m;
    u16 action;

    i = 0;
    do {
        id = func_80025DF8(i + 1);
        if (D_801FA8A0[id - 1] != 0) {
            m = &D_801E0B78[id];
            action = m->action;
            if (action != 0x37 && action != 0x26 && D_801E0D4C == 0) {
                func_80053C50(0x1E0000, m);
                func_8001F724(0x64);
                action = m->action;
                if ((u16) (action - 0x34) >= 2 && action != 0x2A && action != 0x63 && action != 0x47) {
                    m->action = 0xA;
                }
            }
        }
        i++;
    } while (i < 3);
    func_80029118(0xC, 0x10);
    func_8006353C(7);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004BBC8);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004BFE0);
