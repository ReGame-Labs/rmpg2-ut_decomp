/* The monsters' attacks and the objects they throw: script commands that spawn and drive them, the hit tests
 * against monsters, and the attack table.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "game.h"
#include "psyq/libc2.h"
#include "attacker.h"           /* Attacker: the attack command func_80047554 drives one */

/* A thrown object's bookkeeping (func_8004B660). */
typedef struct {
    /* 0x00 */ GameObject *obj;
    /* 0x04 */ GameObject *thrower;    /* the current object when the throw was made (func_8004A9B0) */
    /* 0x08 */ u16 unk_08;             /* the kind: func_8004AD18 dispatches on it */
    /* 0x0A */ u16 unk_0A;             /* the state: 1 in flight, 0x10 done */
    /* 0x0C */ u8 unk_0C[0x02];
    /* 0x0E */ u16 armed;
} Throw;

/* A throw's speed, per attack kind (the table D_8007F2A4, 31 entries). */
typedef struct {
    /* 0x00 */ s32 vx;
    /* 0x04 */ s32 vy;
} ThrowSpeed;

extern ThrowSpeed D_8007F2A4[];
int abs(int);
void func_8004AE2C(void);
u16 monster_test_boxes(s16 x, s16 y, Monster *m);
extern s32 D_80091B60[];
extern s32 D_8008C810[];
extern s32 D_8008C828[];
void func_8004A93C(Monster *m);
u16 func_80053BE8(s16 x, Monster *m);
extern s32 D_80091788[];
extern s32 D_800917D0[];
extern s32 D_8009192C[];
extern s32 D_800918C4[];
extern s32 D_80091AD0[];
extern s32 D_80091820[];
void func_80049D90(Throw *t);
void func_8004A90C(Monster *m);
u16 func_80053AC4(s16 x, s16 y, s32 a, s32 b, Monster *m);
/* The handlers of the thrown objects, one per throw kind (func_8004AD18 dispatches on Throw.unk_08). */
void func_800490D4(Throw *t);
void func_80049304(Throw *t);
void func_800494B4(Throw *t);
void func_80049650(Throw *t);
void func_80049850(Throw *t);
void func_800499F4(Throw *t);
void func_80049B9C(Throw *t);
void func_80049E10(Throw *t);
void func_8004A044(Throw *t);
void func_8004A1F8(Throw *t);
void func_8004A698(Throw *t);
void func_8003A744(Throw *t);
void func_8003956C(Throw *t);
extern s32 D_8008C804;
extern u16 D_801D8850;

void func_8001E4B0(GameObject *obj);                        /* free an object */
void func_8001F724(u16);
void func_8001F7CC(u16 sound, u16 variant);
u16 *func_80025C08(void *);
s32 func_80025DF8(s32 player);
void func_80029118(s16, u16);
void func_80053C50(s32, Monster *m);
void func_8006353C(s32);
u16 func_8004A9B0();
s32 func_8001EB10(s32 range, s32 x);
s16 func_8003FCD8(s32, s32);              /* a horizontal distance */
extern s32 D_800916D8[];
void func_8004B204(void);
void func_8003EB5C(void *anim, GameObject *obj);
void func_8004B540(void);
void func_8004B754(void);
void func_8004B990(void);
void func_8004B3D0(void);
void func_8004AEA4(void *slot);
void func_8004AD18(Throw *slot);
ObjectDef *func_8001D110(void);
u16 func_80047F64(u16 kind, u16 b, Throw *t);
u16 func_80047DEC(u16 a, u16 b, s16 dx, s16 dy, Throw *t);
u16 func_80047EA0(u16 a, u16 b, Throw *t);
u16 func_8004B6C4(GameObject *obj, s16 range, s32 mode);
void func_8004EFAC(void);
void func_8004AF80(void);
void func_8004AF1C();

extern u8 D_8007F634[];
extern s16 D_801D8724;
extern Throw D_801E1CC4[];             /* 21 slots */
/* A thrown object (three records at D_801F9A54): the thrower's object and the thrown one, where it starts, where it
 * is put back on a second pass (state 7) or a third, its speed and what it plays when it lands. Its first 0x10 bytes
 * are laid out like a Throw (func_8004B540 hands one to func_8004B660). */
typedef struct {
    /* 0x00 */ GameObject *obj;
    /* 0x04 */ s16 x0;                 /* the start, relative to the camera */
    /* 0x06 */ u16 x_alt;              /* the x of the second pass */
    /* 0x08 */ u16 y0;
    /* 0x0A */ u16 y_alt;              /* the y of the second pass */
    /* 0x0C */ u16 y_back;             /* the y of the other passes */
    /* 0x0E */ u16 armed;
    /* 0x10 */ GameObject *thrown;
    /* 0x14 */ s32 speed;
    /* 0x18 */ void *land_anim;        /* the animation started when the thrown object lands */
} ThrowRec;

/* A throw record's initial values (three entries at D_8007F644), copied field by field by func_8004B204. */
typedef struct {
    /* 0x00 */ u16 x_alt;
    /* 0x02 */ u16 y_alt;
    /* 0x04 */ u16 y_back;
    /* 0x06 */ u8 pad_06[0x02];
    /* 0x08 */ s32 speed;
    /* 0x0C */ void *land_anim;
    /* 0x10 */ s16 x0;
    /* 0x12 */ u16 y0;
} ThrowInit;

extern ThrowInit D_8007F644[];
extern s32 D_80096240[];               /* two animations, chosen by D_801FA960 (below 75 or not) */
extern s32 D_80096258[];
void func_8001E698(GameObject *obj, void *anim);
u16 func_8004B660(Throw *t, GameObject *target, s16 range, u16 mode);

extern ThrowRec D_801F9A54[];          /* 3 records */
extern u16 D_801D8710;
extern u16 D_8007F28C[];
extern u16 D_8007F298[];
extern s32 D_80096150[];                 /* an animation: its first word is the sprite id */
void func_80062E24(s32);
GameObject *func_8001DCB4(void);
extern u16 D_801E2A4C;
extern u16 D_801E2A54;
extern u16 D_801E1C8C;
extern u16 D_801E0D60;
extern s16 D_801E28D0;
extern s16 D_801E28F0;
extern s32 D_801FA7D8;

extern void (*D_8007F228[])(void);

void func_8004750C(void) {
    s32 i = func_8001EB10(0xE, 2);

    D_8007F228[i & 0xF]();
}

void func_80047554(void *anim, Attacker *at) {
    GameObject *saved = D_800AA248.cur_obj;
    GameObject *obj;
    Monster *hb;
    s32 vx;

    func_8003EB5C(anim, saved);
    obj = at->obj;
    hb = at->hit_by;
    D_800AA248.cur_obj = obj;
    vx = 0x48000;
    if (hb->obj->flags & 0x10) {
        vx = -0x48000;
    }
    obj->vel_x.w = vx;
    D_800AA248.cur_obj->vel_y.w = -0x58000;
    D_800AA248.cur_obj->unk_88 = 0x4000;
    at->state = 0xE;
    D_800AA248.cur_obj = saved;
}

void func_800475F4(Attacker *at) {
    GameObject *saved;
    GameObject *obj;
    s32 vel;
    s32 x;

    obj = at->obj;
    saved = D_800AA248.cur_obj;
    D_800AA248.cur_obj = obj;
    vel = obj->vel_x.w;
    x = obj->pos_x.w;
    x += vel;
    x &= D_801D8864.w;
    obj->pos_x.w = x;
    vel = D_800AA248.cur_obj->vel_y.w + 0x6500;
    D_800AA248.cur_obj->vel_y.w = vel;
    D_800AA248.cur_obj->pos_y.w += vel;
    if (D_800AA248.cur_obj->pos_y.w > 0xE0FFFF) {
        D_800AA248.cur_obj->pos_y.w = 0xE10000;
        func_80044204(at);
    }
    D_800AA248.cur_obj = saved;
}

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
        d = (u16) obj->pos_x.s.hi - (u16) D_801F9AC8.s.hi;
        dx = d;
        if (d < -0x1F3) {
            dx = (u16) D_801D8864.s.hi + d;
        }
        if (obj->flags & 0x10) {
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

    saved->script.pc += 4;
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
    D_800AA248.cur_obj->script.pc = *D_800AA248.cur_obj->arg.w;
}

u16 func_80047DEC(u16 a, u16 b, s16 dx, s16 dy, Throw *t) {
    ObjectDef *def;
    s16 x = dx;

    def = func_8001D110();
    D_800AA248.new_def = def;
    if (!(D_800AA248.cur_obj->flags & 0x10)) {
        x = -dx;
    }
    def->pos_x.s.hi = x + (u16) D_800AA248.cur_obj->pos_x.s.hi;
    def->pos_y.s.hi = dy + (u16) D_800AA248.cur_obj->pos_y.s.hi;
    return func_80047F64(a, b, t);
}

u16 func_80047EA0(u16 a, u16 b, Throw *t) {
    ObjectDef *def = func_8001D110();
    GameObject *cur;
    SpriteFrame *fr;
    s16 dx;
    s16 dy;
    s16 x;

    D_800AA248.new_def = def;
    cur = D_800AA248.cur_obj;
    fr = cur->frame;
    dx = fr->unk_10 - fr->origin.u.lo;
    x = dx;
    dy = fr->unk_12 - fr->origin.u.hi;
    if (cur->flags & 0x10) {
        x = -dx;
    }
    def->pos_x.s.hi = x + (u16) cur->pos_x.s.hi;
    def->pos_y.s.hi = dy + (u16) D_800AA248.cur_obj->pos_y.s.hi;
    return func_80047F64(a, b, t);
}

u16 func_80047F64(u16 kind, u16 b, Throw *t) {
    GameObject *saved = D_800AA248.cur_obj;
    ObjectDef *def = D_800AA248.new_def;
    GameObject *obj;

    def->flags = 0x1005;
    def->unk_0C = 0x720;
    def->id = 0x4F0000D6;
    def->anim = &D_8008C804;
    obj = func_8001DCB4();
    D_800AA248.cur_obj = obj;
    if (obj == NULL) {
        D_800AA248.cur_obj = saved;
        return 1;
    }
    t->obj = obj;
    t->unk_08 = b;
    t->unk_0A = 1;
    D_800AA248.cur_obj->unk_94.p = t;
    if (kind >= 0x1F) {
        kind = 0x1E;
    }
    D_800AA248.cur_obj->vel_y.w = D_8007F2A4[kind].vy;
    D_800AA248.cur_obj->vel_x.w = (saved->flags & 0x10) ? D_8007F2A4[kind].vx : -D_8007F2A4[kind].vx;
    D_800AA248.cur_obj = saved;
    return 0;
}

extern s32 D_80091B54[];
u16 func_80048070(u16 kind, u16 b, Throw *t) {
    GameObject *saved = D_800AA248.cur_obj;
    ObjectDef *def;
    GameObject *cur;
    SpriteFrame *fr;
    s16 dx;
    s16 dy;
    s16 x;

    def = func_8001D110();
    D_800AA248.new_def = def;
    cur = D_800AA248.cur_obj;
    fr = cur->frame;
    dx = fr->unk_20 - fr->origin.u.lo;
    x = dx;
    dy = fr->unk_22 - fr->origin.u.hi;
    if (cur->flags & 0x10) {
        x = -dx;
        def->unk_04 |= 0x10;
    }
    def->pos_x.s.hi = D_800AA248.cur_obj->pos_x.s.hi + x;
    def->pos_y.s.hi = D_800AA248.cur_obj->pos_y.s.hi + dy;
    def->flags = 0x1005;
    def->anim = D_80091B54;
    def->id = 0x4F0000AA;
    def->unk_0C = 0x735;
    D_800AA248.cur_obj = func_8001DCB4();
    if (D_800AA248.cur_obj == NULL) {
        D_800AA248.cur_obj = saved;
        return 1;
    }
    t->obj = D_800AA248.cur_obj;
    t->unk_08 = b;
    t->unk_0A = 1;
    D_800AA248.cur_obj->unk_94.p = t;
    D_800AA248.cur_obj->vel_y.w = D_8007F2A4[kind].vy;
    if (saved->flags & 0x10) {
        D_800AA248.cur_obj->vel_x.w = -D_8007F2A4[kind].vx;
    } else {
        D_800AA248.cur_obj->vel_x.w = D_8007F2A4[kind].vx;
    }
    D_800AA268.p = saved;
    return 0;
}

u16 func_800481FC(u16 kind, u16 b, Throw *t) {
    GameObject *saved = D_800AA248.cur_obj;
    ObjectDef *def;
    GameObject *cur;
    SpriteFrame *fr;
    s16 dx;
    s16 dy;
    s16 x;
    s32 vx;

    D_800AA248.new_def = func_8001D110();
    def = D_800AA248.new_def;
    cur = D_800AA248.cur_obj;
    fr = cur->frame;
    dy = fr->unk_22 - fr->origin.u.hi;
    dx = fr->unk_20 - fr->origin.u.lo;
    x = dx;
    if (cur->flags & 0x10) {
        x = -dx;
        def->unk_04 |= 0x10;
    } else {
        def->unk_04 &= ~0x10;
    }
    def->pos_x.s.hi = D_800AA248.cur_obj->pos_x.s.hi + x;
    def->pos_y.s.hi = D_800AA248.cur_obj->pos_y.s.hi + dy;
    def->flags = 0x1005;
    def->anim = &D_8008C804;
    def->id = 0x4F0000D6;
    def->unk_0C = 0x720;
    D_800AA248.cur_obj = func_8001DCB4();
    if (D_800AA248.cur_obj == NULL) {
        D_800AA248.cur_obj = saved;
        return 1;
    }
    t->obj = D_800AA248.cur_obj;
    t->unk_08 = b;
    t->unk_0A = 1;
    D_800AA248.cur_obj->unk_94.p = t;
    D_800AA248.cur_obj->vel_y.w = D_8007F2A4[kind].vy;
    vx = D_8007F2A4[kind].vx;
    if (D_800AA248.cur_obj->flags & 0x10) {
        vx = -vx;
    }
    D_800AA248.cur_obj->vel_x.w = vx;
    D_800AA248.cur_obj = saved;
    return 0;
}

u16 func_80048384(u16 b, Throw *t) {
    GameObject *saved = D_800AA248.cur_obj;
    ObjectDef *def;
    GameObject *cur;
    SpriteFrame *fr;
    s16 dy;
    s16 dx;
    s16 x;
    u16 left = 0;
    s32 vx;

    D_800AA248.new_def = func_8001D110();
    def = D_800AA248.new_def;
    cur = D_800AA248.cur_obj;
    fr = cur->frame;
    dy = fr->unk_12 - fr->origin.u.hi - 5;
    dx = fr->unk_10 - fr->origin.u.lo - 5;
    x = dx;
    if (cur->flags & 0x10) {
        x = -dx;
    } else {
        left = 1;
    }
    def->pos_x.s.hi = (u16) D_800AA248.cur_obj->pos_x.s.hi + x;
    def->pos_y.s.hi = (u16) D_800AA248.cur_obj->pos_y.s.hi + dy;
    def->flags = 0x1005;
    def->unk_0C = 0x721;
    def->id = 0x4F0000D8;
    def->anim = D_800916D8;
    D_800AA248.cur_obj = func_8001DCB4();
    if (D_800AA248.cur_obj == NULL) {
        D_800AA248.cur_obj = saved;
        return 1;
    }
    t->obj = D_800AA248.cur_obj;
    t->unk_08 = b;
    t->unk_0A = 1;
    D_800AA248.cur_obj->unk_94.p = t;
    D_800AA248.cur_obj->vel_y.w = -(((func_8001EB10(0x7F, 1) & 3) + 0xE) << 15);
    if (saved->unk_68.monster != NULL) {
        vx = abs(func_8003FCD8(saved->pos_x.s.hi, saved->unk_68.monster->obj->pos_x.s.hi));
        vx = ((vx >> 5) << 15) + 0x4000;
    } else {
        vx = ((func_8001EB10(0x7F, 1) & 7) + 2) << 15;
    }
    if (left) {
        vx = -vx;
    }
    D_800AA248.cur_obj->vel_x.w = vx;
    D_800AA248.cur_obj = saved;
    return 0;
}

extern s32 D_80091878[];

u16 func_80048558(u16 b, Throw *t) {
    GameObject *saved = D_800AA248.cur_obj;
    ObjectDef *def;
    GameObject *cur;
    GameObject *obj;
    SpriteFrame *fr;
    s16 dy;
    s16 dx;
    s16 x;
    u16 left = 0;
    s32 vx;

    D_800AA248.new_def = func_8001D110();
    def = D_800AA248.new_def;
    cur = D_800AA248.cur_obj;
    fr = cur->frame;
    dy = fr->unk_12 - fr->origin.u.hi - 5;
    dx = fr->unk_10 - fr->origin.u.lo - 5;
    x = dx;
    if (cur->flags & 0x10) {
        x = -dx;
    } else {
        left = 1;
    }
    def->pos_x.s.hi = (u16) D_800AA248.cur_obj->pos_x.s.hi + x;
    def->pos_y.s.hi = (u16) D_800AA248.cur_obj->pos_y.s.hi + dy;
    def->flags = 0x1005;
    def->unk_0C = 0x730;
    def->id = 0x4F0000EA;
    def->anim = D_80091878;
    obj = func_8001DCB4();
    D_800AA248.cur_obj = obj;
    if (obj == NULL) {
        D_800AA248.cur_obj = saved;
        return 1;
    }
    obj->flags |= saved->flags & 0x10;
    t->obj = D_800AA248.cur_obj;
    t->unk_08 = b;
    t->unk_0A = 1;
    D_800AA248.cur_obj->unk_94.p = t;
    D_800AA248.cur_obj->vel_y.w = -(((func_8001EB10(0x7F, 1) & 3) + 0xC) << 15);
    if (saved->unk_68.monster != NULL) {
        vx = abs(func_8003FCD8(saved->unk_68.monster->obj->pos_x.s.hi, saved->pos_x.s.hi));
        vx = ((vx >> 5) << 15) + 0x8000;
    } else {
        vx = ((func_8001EB10(0x7F, 1) & 7) + 5) << 15;
    }
    if (left) {
        vx = -vx;
    }
    D_800AA248.cur_obj->vel_x.w = vx;
    D_800AA248.cur_obj = saved;
    return 0;
}

#ifdef NON_MATCHING
/* 93 %: the original copies the state block's address into a second saved register after the facing test (move s0,s2) and uses both; here one register holds it throughout, so the frame has one saved register less */
extern s32 D_8009186C[];

u16 func_8004874C(u16 b, Throw *t) {
    GameObject *saved = D_800AA248.cur_obj;
    ObjectDef *def;
    GameObject *cur;
    GameObject *obj;
    SpriteFrame *fr;
    s16 dx;
    s16 dy;
    s16 x;
    s32 vx;

    def = func_8001D110();
    D_800AA248.new_def = def;
    cur = D_800AA248.cur_obj;
    fr = cur->frame;
    dx = fr->unk_10 - fr->origin.u.lo - 5;
    x = dx;
    dy = fr->unk_12 - fr->origin.u.hi - 5;
    if (cur->flags & 0x10) {
        x = -dx;
    }
    def->pos_x.s.hi = cur->pos_x.s.hi + x;
    def->pos_y.s.hi = D_800AA248.cur_obj->pos_y.s.hi + dy;
    def->flags = 0x1005;
    def->unk_0C = 0x744;
    def->id = 0x4F0000F2;
    def->anim = D_8009186C;
    obj = func_8001DCB4();
    D_800AA248.cur_obj = obj;
    if (obj == NULL) {
        D_800AA248.cur_obj = saved;
        return 1;
    }
    obj->flags |= saved->flags & 0x10;
    t->obj = D_800AA248.cur_obj;
    t->unk_08 = b;
    t->unk_0A = 1;
    D_800AA248.cur_obj->unk_94.p = t;
    if (saved->flags & 0x10) {
        vx = 0x70000;
    } else {
        vx = -0x70000;
    }
    D_800AA248.cur_obj->vel_x.w = vx;
    D_800AA248.cur_obj->vel_y.w = -0x40000;
    D_800AA248.cur_obj = saved;
    return 0;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/throw", func_8004874C);
#endif

extern s32 D_80091B24[];
extern u16 D_801E28A8;

u16 func_800488B8(u16 b, Throw *t) {
    GameObject *saved = D_800AA248.cur_obj;
    ObjectDef *def;

    def = func_8001D110();
    D_800AA248.new_def = def;
    def->pos_x.s.hi = D_800AA248.cur_obj->pos_x.s.hi + 4;
    def->pos_y.s.hi = D_800AA248.cur_obj->pos_y.s.hi - 0x30;
    def->flags = 0x1005;
    def->unk_0C = 0x736;
    def->anim = D_80091B24;
    D_800AA248.cur_obj = func_8001DCB4();
    if (D_800AA248.cur_obj == NULL) {
        D_800AA248.cur_obj = saved;
        return 1;
    }
    t->obj = D_800AA248.cur_obj;
    t->unk_08 = b;
    t->unk_0A = 1;
    D_800AA248.cur_obj->vel_y.w = 0xFFFD8000;
    D_801E28A8 = (D_801E28A8 + 1) & 3;
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->unk_88 = -0x2000;
    D_800AA248.cur_obj->unk_08.w = D_801E28A8;
    D_800AA248.cur_obj = saved;
    return 0;
}

extern s32 D_8009198C[];

u16 func_800489C0(u16 b, Throw *t) {
    GameObject *saved = D_800AA248.cur_obj;
    ObjectDef *def;
    GameObject *cur;
    SpriteFrame *fr;
    s16 dy;
    s16 dx;
    s16 x;
    u16 left = 0;
    s32 vx;

    D_800AA248.new_def = func_8001D110();
    def = D_800AA248.new_def;
    cur = D_800AA248.cur_obj;
    fr = cur->frame;
    dy = fr->unk_12 - fr->origin.u.hi - 5;
    dx = fr->unk_10 - fr->origin.u.lo - 5;
    x = dx;
    if (cur->flags & 0x10) {
        x = -dx;
    } else {
        left = 1;
    }
    def->pos_x.s.hi = (u16) D_800AA248.cur_obj->pos_x.s.hi + x;
    def->pos_y.s.hi = (u16) D_800AA248.cur_obj->pos_y.s.hi + dy;
    def->flags = 0x1005;
    def->unk_0C = 0x731;
    def->id = 0x4F0000EE;
    def->anim = D_8009198C;
    D_800AA248.cur_obj = func_8001DCB4();
    if (D_800AA248.cur_obj == NULL) {
        D_800AA248.cur_obj = saved;
        return 1;
    }
    t->obj = D_800AA248.cur_obj;
    t->unk_08 = b;
    t->unk_0A = 1;
    D_800AA248.cur_obj->unk_94.p = t;
    D_800AA248.cur_obj->vel_y.w = -(((func_8001EB10(0x7F, 1) & 3) + 0xE) << 15);
    if (saved->unk_68.monster != NULL) {
        vx = abs(func_8003FCD8(saved->unk_68.monster->obj->pos_x.s.hi, saved->pos_x.s.hi));
        vx = ((vx >> 5) << 15) + 0x8000;
    } else {
        vx = ((func_8001EB10(0x7F, 1) & 3) + 5) << 15;
    }
    if (left) {
        vx = -vx;
    }
    D_800AA248.cur_obj->vel_x.w = vx;
    D_800AA248.cur_obj = saved;
    return 0;
}

u16 func_80048B98(u16 b, Throw *t) {
    GameObject *saved = D_800AA248.cur_obj;
    ObjectDef *def;
    GameObject *cur;
    GameObject *target;
    SpriteFrame *fr;
    s16 dx;
    s16 dy;
    s16 x;
    s32 tx;
    s32 cx;
    s32 vy;
    s32 d;
    s32 vx;

    def = func_8001D110();
    D_800AA248.new_def = def;
    cur = D_800AA248.cur_obj;
    fr = cur->frame;
    dx = fr->unk_10 - fr->origin.u.lo - 5;
    x = dx;
    dy = fr->unk_12 - fr->origin.u.hi - 5;
    if (cur->flags & 0x10) {
        x = -dx;
    }
    def->pos_x.s.hi = cur->pos_x.s.hi + x;
    def->pos_y.s.hi = D_800AA248.cur_obj->pos_y.s.hi + dy;
    def->flags = 0x1005;
    def->unk_0C = 0x721;
    def->id = 0x4F0000D8;
    def->anim = D_800916D8;
    D_800AA248.cur_obj = func_8001DCB4();
    if (D_800AA248.cur_obj == NULL) {
        D_800AA248.cur_obj = saved;
        return 1;
    }
    t->obj = D_800AA248.cur_obj;
    t->unk_08 = b;
    t->unk_0A = 1;
    D_800AA248.cur_obj->unk_94.p = t;
    if (saved->unk_68.monster != NULL) {
        target = saved->unk_68.monster->obj;
        if (target != NULL) {
            vy = -0x90000;
            if (D_800AA248.cur_obj->pos_y.s.hi < target->pos_y.s.hi) {
                vy = -0x70000;
            }
            D_800AA248.cur_obj->vel_y.w = vy;
            tx = target->pos_x.s.hi;
            cx = D_800AA248.cur_obj->pos_x.s.hi;
            vx = abs(func_8003FCD8(saved->pos_x.s.hi, tx));
            vx = ((vx >> 5) << 15) + 0x4000;
            if (tx < cx) {
                vx = -vx;
            }
            D_800AA248.cur_obj->vel_x.w = vx;
        }
    }
    D_800AA268.p = saved;
    return 0;
}

extern s32 D_8009177C[];

u16 func_80048D4C(u16 b, Throw *t) {
    GameObject *saved = D_800AA248.cur_obj;
    ObjectDef *def;
    SpriteFrame *fr;
    s16 dx;
    s16 dy;

    def = func_8001D110();
    D_800AA248.new_def = def;
    if (D_800AA248.cur_obj->flags & 0x10) {
        def->unk_04 |= 0x10;
    }
    def->id = 0x4F0000DA;
    fr = D_800AA248.cur_obj->frame;
    dx = fr->unk_10 - fr->origin.u.lo;
    dy = fr->unk_12 - fr->origin.u.hi;
    def->pos_x.s.hi = D_800AA248.cur_obj->pos_x.s.hi + dx;
    def->pos_y.s.hi = D_800AA248.cur_obj->pos_y.s.hi + dy;
    def->unk_0C = 0x722;
    def->flags = 0x1005;
    def->anim = D_8009177C;
    D_800AA248.cur_obj = func_8001DCB4();
    if (D_800AA248.cur_obj == NULL) {
        D_800AA248.cur_obj = saved;
        return 1;
    }
    t->obj = D_800AA248.cur_obj;
    t->unk_08 = b;
    t->unk_0A = 1;
    D_800AA248.cur_obj->unk_94.p = t;
    D_800AA248.cur_obj = saved;
    return 0;
}

extern s32 D_80091A70[];

u16 func_80048E6C(u16 b, Throw *t) {
    GameObject *saved = D_800AA248.cur_obj;
    ObjectDef *def;
    SpriteFrame *fr;
    s16 dx;
    s16 dy;

    def = func_8001D110();
    D_800AA248.new_def = def;
    def->id = 0x4F0000E6;
    fr = D_800AA248.cur_obj->frame;
    dx = fr->unk_10 - fr->origin.u.lo;
    dy = fr->unk_12 - fr->origin.u.hi;
    def->pos_x.s.hi = D_800AA248.cur_obj->pos_x.s.hi + dx;
    def->pos_y.s.hi = D_800AA248.cur_obj->pos_y.s.hi + dy;
    def->unk_0C = 0x723;
    def->flags = 0x1005;
    def->anim = D_80091A70;
    D_800AA248.cur_obj = func_8001DCB4();
    if (D_800AA248.cur_obj == NULL) {
        D_800AA248.cur_obj = saved;
        return 1;
    }
    t->obj = D_800AA248.cur_obj;
    t->unk_08 = b;
    t->unk_0A = 1;
    D_800AA248.cur_obj->unk_94.p = t;
    D_800AA248.cur_obj = saved;
    return 0;
}

extern s32 D_80091ABC[];
extern s32 D_80091A7C[];

u16 func_80048F60(Monster *m, u16 b, Throw *t) {
    GameObject *saved = D_800AA248.cur_obj;
    ObjectDef *def;
    GameObject *cur;
    SpriteFrame *fr;
    s16 dx;
    s16 dy;
    s16 x;

    D_800AA248.new_def = func_8001D110();
    cur = D_800AA248.cur_obj;
    def = D_800AA248.new_def;
    fr = cur->frame;
    dx = fr->unk_20 - fr->origin.u.lo;
    x = dx;
    dy = fr->unk_22 - fr->origin.u.hi;
    if (cur->flags & 0x10) {
        x = -dx;
        def->unk_04 |= 0x10;
    }
    def->pos_x.s.hi = D_800AA248.cur_obj->pos_x.s.hi + x;
    def->pos_y.s.hi = D_800AA248.cur_obj->pos_y.s.hi + dy;
    def->flags = 0x1005;
    def->unk_0C = 0x724;
    if (m->kind == 0x15) {
        def->anim = D_80091ABC;
    } else {
        def->anim = D_80091A7C;
    }
    def->id = *(s32 *)def->anim;
    D_800AA248.cur_obj = func_8001DCB4();
    if (D_800AA248.cur_obj == NULL) {
        D_800AA248.cur_obj = saved;
        return 1;
    }
    t->obj = D_800AA248.cur_obj;
    t->unk_08 = b;
    t->unk_0A = 1;
    D_800AA248.cur_obj->unk_94.p = t;
    D_800AA248.cur_obj->vel_x.w = saved->vel_x.w >> 1;
    D_800AA248.cur_obj->vel_y.w = 0;
    m->unk_02A = 0;
    D_800AA248.cur_obj = saved;
    return 0;
}

extern s32 D_80091730[];
extern s32 D_800916E4[];

void func_800490D4(Throw *t) {
    GameObject *saved = D_800AA248.cur_obj;
    Monster *m;
    s32 vy;
    s16 hit;
    u16 i;

    if (t->unk_0A == 1) {
        saved->pos_x.w = (saved->pos_x.w + saved->vel_x.w) & D_801D8864.w;
        vy = D_800AA248.cur_obj->vel_y.w + 0x4000;
        if (vy <= -0x90000) {
            vy = -0x90000;
        }
        D_800AA248.cur_obj->vel_y.w = vy;
        D_800AA248.cur_obj->pos_y.w += vy;
        if (D_800AA248.cur_obj->vel_y.w >= 0 && D_800AA248.cur_obj->pos_y.s.hi >= 0xD9) {
            t->unk_0A = 0x10;
            D_800AA248.cur_obj->script.pc = (s32) D_80091730;
        } else {
            i = 7;
            do {
                m = &D_801E0B78[i];
                if ((m->unk_058 & 1) && m->unk_140 == 0) {
                    hit = monster_test_boxes(D_800AA248.cur_obj->pos_x.s.hi, D_800AA248.cur_obj->pos_y.s.hi, m);
                    if (hit != 0) {
                        func_80053C50(0x34000, m);
                        t->unk_0A = 0x10;
                        D_800AA248.cur_obj->script.pc = (s32) D_800916E4;
                        break;
                    }
                }
            } while (--i != 0);
        }
    }
    D_800AA268.p = saved;
}

void func_8004928C(void) {
    if (D_800AA248.cur_obj->vel_y.w <= -0x10000) {
        D_800AA248.cur_obj->script.pc = *D_800AA248.cur_obj->arg.w;
    }
}

void func_800492C8(void) {
    if (D_800AA248.cur_obj->vel_y.w <= 0x10000) {
        D_800AA248.cur_obj->script.pc = *D_800AA248.cur_obj->arg.w;
    }
}

void func_80049304(Throw *t) {
    Monster *m;
    s32 vy;
    s16 hit;
    u16 i;

    if (t->unk_0A != 1) {
        return;
    }
    D_800AA248.cur_obj->pos_x.w = (D_800AA248.cur_obj->pos_x.w + D_800AA248.cur_obj->vel_x.w) & D_801D8864.w;
    vy = D_800AA248.cur_obj->vel_y.w + 0x4000;
    if (vy <= -0x90000) {
        vy = -0x90000;
    }
    D_800AA248.cur_obj->vel_y.w = vy;
    D_800AA248.cur_obj->pos_y.w += vy;
    if (D_800AA248.cur_obj->vel_y.w >= 0 && D_800AA248.cur_obj->pos_y.s.hi >= 0xD9) {
        t->unk_0A = 0x10;
        D_800AA248.cur_obj->script.pc = (s32) D_8009192C;
        return;
    }
    i = 7;
    do {
        m = &D_801E0B78[i];
        if ((m->unk_058 & 1) && m->unk_140 == 0) {
            hit = monster_test_boxes(D_800AA248.cur_obj->pos_x.s.hi, D_800AA248.cur_obj->pos_y.s.hi, m);
            if (hit != 0) {
                func_80053C50(0x58000, m);
                func_8004A93C(m);
                t->unk_0A = 0x10;
                D_800AA248.cur_obj->script.pc = (s32) D_800918C4;
                return;
            }
        }
    } while (--i != 0);
}

void func_800494B4(Throw *t) {
    Monster *m;
    s16 hit;
    u16 i;

    if (t->unk_0A != 1) {
        return;
    }
    D_800AA248.cur_obj->pos_x.w = (D_800AA248.cur_obj->pos_x.w + D_800AA248.cur_obj->vel_x.w) & D_801D8864.w;
    D_800AA248.cur_obj->vel_y.w += 0x2000;
    D_800AA248.cur_obj->pos_y.w += D_800AA248.cur_obj->vel_y.w;
    if (D_800AA248.cur_obj->vel_y.w >= 0 && D_800AA248.cur_obj->pos_y.s.hi >= 0xD9) {
        t->unk_0A = 0x10;
        func_8001E698(D_800AA248.cur_obj, D_80091AD0);
        return;
    }
    i = 7;
    do {
        m = &D_801E0B78[i];
        if ((m->unk_058 & 1) && m->unk_140 == 0) {
            hit = monster_test_boxes(D_800AA248.cur_obj->pos_x.s.hi, D_800AA248.cur_obj->pos_y.s.hi, m);
            if (hit != 0) {
                func_80053C50(0x58000, m);
                func_8004A93C(m);
                t->unk_0A = 0x10;
                func_8001E698(D_800AA248.cur_obj, D_80091AD0);
                return;
            }
        }
    } while (--i != 0);
}

#ifdef NON_MATCHING
/* 99.25%: registers only: the original gives x a0, the counter a1 and the object a2 (here a2, a0, a1) */
/* A pair per throw kind (D_8007F39C): the vertical speed it gets back when it lands, and the height it lands at. */
typedef struct {
    /* 0x00 */ s32 unk_0;
    /* 0x04 */ s32 unk_4;
} ThrowLanding;

extern ThrowLanding D_8007F39C[];

void func_80049650(Throw *t) {
    u16 x;
    Monster *m;
    GameObject *o;
    s32 v;
    GameObject *cur;
    u16 i;

    if (t->unk_0A == 0x10) {
        return;
    }
    v = D_800AA248.cur_obj->vel_x.w + D_800AA248.cur_obj->pos_x.w;
    v &= D_801D8864.w;
    D_800AA248.cur_obj->pos_x.w = v;
    v = D_800AA248.cur_obj->unk_88 + D_800AA248.cur_obj->vel_y.w;
    D_800AA248.cur_obj->vel_y.w = v;
    D_800AA248.cur_obj->pos_y.w += v;
    cur = D_800AA248.cur_obj;
    if (cur->unk_88 <= 0) {
        if (cur->pos_y.w > D_8007F39C[cur->unk_08.w].unk_4) {
            return;
        }
        x = 0;
        i = 7;
        cur->unk_88 = D_8007F39C[cur->unk_08.w].unk_0;
        do {
            m = &D_801E0B78[i];
            if (m->unk_058 & 1) {
                o = m->obj;
                if (x == 0 || (D_800AA248.cur_obj->unk_08.w & 1)) {
                    x = o->pos_x.s.hi;
                }
            }
        } while (--i != 0);
        if (x != 0) {
            D_800AA268.p->pos_x.s.hi = x;
        }
        D_800AA268.p->flags |= 0x20;
    } else if (D_801F9ACC.w + cur->pos_y.w > 0xD8FFFF) {
        cur->pos_y.w = 0xCF0000;
        D_800AA248.cur_obj->flags &= ~0x20;
        func_8001E698(D_800AA248.cur_obj, D_80095678);
        t->unk_0A = 0x10;
        D_800AA248.cur_obj->vel_x.w = 0;
        D_800AA248.cur_obj->vel_y.w = 0;
        D_800AA248.cur_obj->unk_88 = 0;
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/throw", func_80049650);
#endif

extern s32 D_80091A20[];
extern s32 D_800919D4[];

void func_80049850(Throw *t) {
    Monster *m;
    s32 vy;
    s16 hit;
    u16 i;

    if (t->unk_0A != 1) {
        return;
    }
    D_800AA248.cur_obj->pos_x.w = (D_800AA248.cur_obj->vel_x.w + D_800AA248.cur_obj->pos_x.w) & D_801D8864.w;
    vy = D_800AA248.cur_obj->vel_y.w + 0x4000;
    if (vy >= -8) {
        vy = -9;
    }
    D_800AA248.cur_obj->vel_y.w = vy;
    D_800AA248.cur_obj->pos_y.w += vy;
    if (D_800AA248.cur_obj->vel_y.w >= 0 && D_800AA248.cur_obj->pos_y.s.hi >= 0xD9) {
        t->unk_0A = 0x10;
        D_800AA248.cur_obj->script.pc = (s32) D_80091A20;
        return;
    }
    i = 7;
    do {
        m = &D_801E0B78[i];
        if ((m->unk_058 & 1) && m->unk_140 == 0) {
            hit = monster_test_boxes(D_800AA248.cur_obj->pos_x.s.hi, D_800AA248.cur_obj->pos_y.s.hi, m);
            if (hit != 0) {
                func_80053C50(0x48000, m);
                t->unk_0A = 0x10;
                D_800AA248.cur_obj->script.pc = (s32) D_800919D4;
                return;
            }
        }
    } while (--i != 0);
}

void func_800499F4(Throw *t) {
    Monster *m;
    u16 i;

    if (t->unk_0A != 1) {
        return;
    }
    if (D_800AA248.cur_obj->unk_08.w == 0) {
        func_80049D90(t);
        if (D_800AA248.cur_obj->pos_y.s.hi >= 0xD9) {
            D_800AA248.cur_obj->vel_y.w = 0;
            D_800AA248.cur_obj->unk_08.w = 0xE6;
            D_800AA248.cur_obj->priority = 0x1005;
        }
        return;
    }
    if (D_800AA248.cur_obj->unk_08.w == 1) {
        t->unk_0A = 0x10;
        D_800AA248.cur_obj->script.pc = (s32) D_80091820;
        func_8001F724(5);
        return;
    }
    if (--D_800AA248.cur_obj->unk_08.w < 0xD8) {
        i = 7;
        do {
            m = &D_801E0B78[i];
            if ((m->unk_058 & 1) && m->obj->pos_y.s.hi >= 0xE1 &&
                func_80053AC4(D_800AA248.cur_obj->pos_x.s.hi, D_800AA248.cur_obj->pos_y.s.hi, 5, 0x37, m) != 0) {
                func_80053C50(0x58000, m);
                func_8004A90C(m);
                t->unk_0A = 0x10;
                D_800AA248.cur_obj->script.pc = (s32) D_80091820;
                func_8001F724(5);
                return;
            }
        } while (--i != 0);
    }
}

#ifdef NON_MATCHING
/* 99.7 %: register names only: the original keeps the object in a0 and the camera's x in a1, here the other way round */
void func_80049B9C(Throw *t) {
    Monster *m;
    GameObject *o;
    s32 d;
    u16 i;

    if (t->unk_0A != 1) {
        return;
    }
    func_80049D90(t);
    if (D_800AA248.cur_obj->pos_y.s.hi >= 0xD9) {
        D_800AA248.cur_obj->unk_08.w++;
        if (D_800AA248.cur_obj->unk_08.w == 4) {
            t->unk_0A = 0x10;
            D_800AA248.cur_obj->script.pc = (s32) D_80091AD0;
            func_8001F724(5);
            return;
        }
        D_800AA248.cur_obj->vel_y.w = (D_800AA248.cur_obj->vel_y.w >> 2) - D_800AA248.cur_obj->vel_y.w;
        o = D_800AA248.cur_obj;
        if (o->vel_x.w == 0) {
            if (o->pos_x.w > D_801F9AC8.w) {
                d = o->pos_x.w - D_801F9AC8.w;
            } else {
                d = D_801D8864.w + 1;
                d -= D_801F9AC8.w;
            }
            o->vel_x.w = (d <= 0xC80000) ? 0x20000 : -0x20000;
        }
    }
    i = 7;
    do {
        m = &D_801E0B78[i];
        if ((m->unk_058 & 1) && m->unk_140 == 0 &&
            func_80053AC4(D_800AA248.cur_obj->pos_x.s.hi, D_800AA248.cur_obj->pos_y.s.hi, 3, 3, m) != 0) {
            func_80053C50(0x58000, m);
            func_8004A93C(m);
            t->unk_0A = 0x10;
            D_800AA248.cur_obj->script.pc = (s32) D_80091AD0;
            func_8001F724(5);
            return;
        }
    } while (--i != 0);
}
#else
INCLUDE_ASM("asm/main/nonmatchings/throw", func_80049B9C);
#endif

void func_80049D90(Throw *t) {
    s32 vel;

    vel = D_800AA248.cur_obj->pos_x.w + D_800AA248.cur_obj->vel_x.w;
    vel &= D_801D8864.w;
    D_800AA248.cur_obj->pos_x.w = vel;
    vel = D_800AA248.cur_obj->vel_y.w + 0x4000;
    if (vel > 0x9FFFF) {
        vel = 0xA0000;
    }
    D_800AA248.cur_obj->vel_y.w = vel;
    vel += D_800AA248.cur_obj->pos_y.w;
    if (vel > 0xD90000) {
        vel = 0xD90000;
    }
    D_800AA248.cur_obj->pos_y.w = vel;
}

void func_80049E10(Throw *t) {
    GameObject *saved = D_800AA268.p;
    Monster *m;
    s32 vx;
    u16 i;

    if (t->unk_0A == 1) {
        if (saved->unk_6C & 0x80) {
            func_8004AE2C();
        } else {
            vx = saved->vel_x.w;
            if (vx <= 0) {
                if (D_801D3D8A < 0) {
                    vx += D_801D3D8A;
                }
            } else if (D_801D3D8A > 0) {
                vx += D_801D3D8A;
            }
            vx += D_800AA248.cur_obj->pos_x.w;
            D_800AA248.cur_obj->pos_x.w = vx & D_801D8864.w;
            D_800AA248.cur_obj->pos_y.w -= D_800AA248.cur_obj->vel_y.w;
            if (D_800AA248.cur_obj->vel_y.w <= 0 && D_800AA248.cur_obj->pos_y.s.hi >= 0xD9) {
                t->unk_0A = 0x10;
                D_800AA248.cur_obj->script.pc = (s32) D_8008C810;
            } else {
                i = 7;
                do {
                    m = &D_801E0B78[i];
                    if ((m->unk_058 & 1) && !(m->obj->unk_6C & 0x80) && m->unk_140 == 0 &&
                        monster_test_boxes(D_800AA248.cur_obj->pos_x.s.hi, D_800AA248.cur_obj->pos_y.s.hi, m) != 0) {
                        if (t->unk_08 == 0x12) {
                            func_80053C50(0x1C000, m);
                        } else {
                            func_80053C50(0x18000, m);
                        }
                        t->unk_0A = 0x10;
                        D_800AA248.cur_obj->script.pc = (s32) D_8008C828;
                        break;
                    }
                } while (--i != 0);
            }
        }
    }
    D_800AA268.p = saved;
}

void func_8004A044(Throw *t) {
    GameObject *obj;
    Monster *m;
    s32 vx;
    u16 i;

    if (t->unk_0A != 1) {
        return;
    }
    obj = D_800AA268.p;
    if (obj->unk_6C & 0x80) {
        func_8004AE2C();
        return;
    }
    vx = obj->vel_x.w;
    if (vx <= 0) {
        if (D_801D3D8A < 0) {
            vx += D_801D3D8A;
        }
    } else if (D_801D3D8A > 0) {
        vx += D_801D3D8A;
    }
    vx += D_800AA248.cur_obj->pos_x.w;
    D_800AA248.cur_obj->pos_x.w = vx & D_801D8864.w;
    D_800AA248.cur_obj->pos_y.w -= D_800AA248.cur_obj->vel_y.w;
    i = 7;
    do {
        m = &D_801E0B78[i];
        if ((m->unk_058 & 1) && !(m->obj->unk_6C & 0x80) && m->unk_140 == 0 &&
            monster_test_boxes(D_800AA248.cur_obj->pos_x.s.hi, D_800AA248.cur_obj->pos_y.s.hi, m) != 0) {
            func_80053C50(0x28000, m);
            t->unk_0A = 0x10;
            func_8001E698(D_800AA248.cur_obj, D_80091B60);
            return;
        }
    } while (--i != 0);
}

void func_8004A1F8(Throw *t) {
    GameObject *saved = D_800AA268.p;
    Monster *m;
    s32 vx;
    u16 i;

    if (t->unk_0A == 1) {
        if (saved->unk_6C & 0x80) {
            func_8004AE2C();
        } else {
            vx = saved->vel_x.w;
            if (vx <= 0) {
                if (D_801D3D8A < 0) {
                    vx += D_801D3D8A;
                }
            } else if (D_801D3D8A > 0) {
                vx += D_801D3D8A;
            }
            vx += D_800AA248.cur_obj->pos_x.w;
            D_800AA248.cur_obj->pos_x.w = vx & D_801D8864.w;
            D_800AA248.cur_obj->pos_y.w += D_800AA248.cur_obj->vel_y.w;
            if (D_800AA248.cur_obj->pos_y.s.hi >= 0xD9) {
                t->unk_0A = 0x10;
                D_800AA248.cur_obj->script.pc = (s32) D_8008C810;
            } else if (--D_800AA248.cur_obj->unk_8C == 0) {
                func_8004AE2C();
            } else {
                i = 7;
                do {
                    m = &D_801E0B78[i];
                    if ((m->unk_058 & 1) && !(m->obj->unk_6C & 0x80) && m->unk_140 == 0) {
                        if (monster_test_boxes(D_800AA248.cur_obj->pos_x.s.hi, D_800AA248.cur_obj->pos_y.s.hi, m) != 0) {
                            func_80053C50(0xA000, m);
                            t->unk_0A = 0x10;
                            func_8001E698(D_800AA248.cur_obj, D_8008C828);
                            break;
                        }
                        vx = D_800AA248.cur_obj->pos_x.w + (D_800AA248.cur_obj->vel_x.w >> 1);
                        vx &= D_801D8864.w;
                        if (monster_test_boxes(vx >> 16, D_800AA248.cur_obj->pos_y.s.hi, m) != 0) {
                            D_800AA248.cur_obj->pos_x.w = vx;
                            func_80053C50(0xA000, m);
                            t->unk_0A = 0x10;
                            func_8001E698(D_800AA248.cur_obj, D_8008C828);
                            break;
                        }
                    }
                } while (--i != 0);
            }
        }
    }
    D_800AA268.p = saved;
}

s32 func_8004A468(Ai *ai) {
    Monster *target = ai->target;
    GameObject *obj;
    s16 r;
    s16 d;

    if (target == NULL || (obj = target->obj) == NULL) {
        return 3;
    }
    d = (u16) D_800AA248.cur_obj->pos_y.s.hi - (u16) obj->pos_y.s.hi - 0x23;
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

extern s32 D_80091B48[];
extern ThrowSpeed D_8007F3BC[];

u16 func_8004A51C(u16 kind, u16 b, Throw *t) {
    GameObject *saved = D_800AA248.cur_obj;
    ObjectDef *def;
    GameObject *cur;
    SpriteFrame *fr;
    s16 dx;
    s16 dy;
    s16 x;

    def = func_8001D110();
    D_800AA248.new_def = def;
    cur = D_800AA248.cur_obj;
    fr = cur->frame;
    dx = fr->unk_20 - fr->origin.u.lo;
    x = dx;
    dy = fr->unk_22 - fr->origin.u.hi;
    if (cur->flags & 0x10) {
        x = -dx;
        def->unk_04 |= 0x10;
    }
    def->pos_x.s.hi = D_800AA248.cur_obj->pos_x.s.hi + x;
    def->pos_y.s.hi = D_800AA248.cur_obj->pos_y.s.hi + dy;
    def->flags = 0x1005;
    def->anim = D_80091B48;
    def->id = 0x4F0000D6;
    def->unk_0C = 0x725;
    D_800AA248.cur_obj = func_8001DCB4();
    if (D_800AA248.cur_obj == NULL) {
        D_800AA248.cur_obj = saved;
        return 1;
    }
    t->obj = D_800AA248.cur_obj;
    t->unk_08 = b;
    t->unk_0A = 1;
    D_800AA248.cur_obj->unk_94.p = t;
    D_800AA248.cur_obj->vel_y.w = D_8007F3BC[kind].vy;
    D_800AA248.cur_obj->vel_x.w = (saved->flags & 0x10) ? -D_8007F3BC[kind].vx : D_8007F3BC[kind].vx;
    D_800AA248.cur_obj->unk_8C = 0x18;
    D_800AA248.cur_obj = saved;
    return 0;
}

#ifdef NON_MATCHING
/* 70 %: the logic is right; the layout is not: the original keeps the landing and the hit blocks inline before their jumps to the sound, here they are placed after the loop */
void func_8004A698(Throw *t) {
    GameObject *saved = D_800AA248.cur_obj;
    Monster *m;
    s32 vy;
    s16 hit;
    u16 i;

    if (t->unk_0A == 1) {
        if (!(saved->unk_6C & 0x80)) {
            saved->pos_x.w = (saved->pos_x.w + saved->vel_x.w) & D_801D8864.w;
            vy = D_800AA248.cur_obj->vel_y.w - 0x18000;
            if (vy < -0x30000) {
                vy = -0x30000;
            }
            D_800AA248.cur_obj->vel_y.w = vy;
            D_800AA248.cur_obj->pos_y.w -= vy;
            if (D_800AA248.cur_obj->pos_y.s.hi >= 0xD9) {
                t->unk_0A = 0x10;
                D_800AA248.cur_obj->script.pc = (s32) D_80091788;
                D_800AA248.cur_obj->flags |= 0x800;
            } else {
                i = 7;
                do {
                    m = &D_801E0B78[i];
                    if ((m->unk_058 & 1) && m->unk_140 == 0) {
                        hit = monster_test_boxes(D_800AA248.cur_obj->pos_x.s.hi, D_800AA248.cur_obj->pos_y.s.hi, m);
                        if (hit != 0) {
                            func_80053C50(0x58000, m);
                            t->unk_0A = 0x10;
                            func_8004A93C(m);
                            D_800AA248.cur_obj->script.pc = (s32) D_800917D0;
                            D_800AA248.cur_obj->flags |= 0x800;
                            goto sound;
                        }
                        if (D_800AA248.cur_obj->vel_x.w != 0 && func_80053BE8(D_800AA248.cur_obj->pos_x.s.hi, m) != 0) {
                            D_800AA248.cur_obj->vel_x.w >>= 1;
                        }
                    }
                } while (--i != 0);
                goto end;
            }
        } else {
            func_8004AE2C();
        }
sound:
        if (!(D_800AA248.cur_obj->unk_6C & 0x80)) {
            func_8001F7CC(0x28, 5);
        }
    }
end:
    D_800AA268.p = saved;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/throw", func_8004A698);
#endif

void func_8004A90C(Monster *m) {
    m->action = 0x20;
    m->obj->vel_y.w = 0xFFF70000;
    m->unk_104 = 0x4000;
    m->unk_100 = 0;
    m->climb_side = 0;
    m->climb_building = 0;
    m->climb_floor = 0;
}

void func_8004A93C(Monster *m) {
    u16 side = m->climb_side;

    if (side != 0) {
        if (side != 3) {
            func_8004EFAC();
            m->action = 0x12;
        } else {
            m->action = 0x3A;
        }
    } else {
        if (m->obj->pos_y.s.hi < 0xE1) {
            func_8004EFAC();
            m->action = 0xF;
        } else {
            m->action = 0x3A;
        }
    }
}

u16 func_80039358(Monster *m, u16 a, u16 kind, Throw *t);
u16 func_8003A5A0(u16 a, u16 kind, Throw *t, s32 alt);

u16 func_8004A9B0(m, a, kind, b, c)
    Monster *m;
    u16 a;
    u16 kind;
    u16 b;
    u16 c;
{
    GameObject *saved = D_800AA268.p;
    Throw *t;
    u16 n;
    u16 i;
    u16 r;

    n = D_801D8724;
    if (D_801D8724 >= 0x15) {
        return 1;
    }
    t = D_801E1CC4;
    i = 1;
    D_801D8724 = n + 1;
    if (t->obj != NULL) {
        do {
            if (++i >= 0x15) {
                return 1;
            }
            t++;
        } while (t->obj != NULL);
    }
    func_8004AEA4(t);
    t->thrower = D_800AA268.p;
    r = 1;
    switch (kind) {
    case 1:
        r = func_80047EA0(a, kind, t);
        break;
    case 2:
        r = func_80048B98(kind, t);
        break;
    case 8:
        r = func_80048384(kind, t);
        break;
    case 11:
        r = func_80048558(kind, t);
        break;
    case 12:
        r = func_800489C0(kind, t);
        break;
    case 3:
        r = func_80048D4C(kind, t);
        break;
    case 4:
        r = func_80048E6C(kind, t);
        break;
    case 5:
        r = func_80048F60(m, kind, t);
        break;
    case 6:
        r = func_8004A51C(a, kind, t);
        break;
    case 7:
        r = func_80039358(m, a, kind, t);
        break;
    case 9:
        r = func_80047DEC(a, kind, b, c, t);
        break;
    case 21:
        r = func_8003A5A0(a, kind, t, 0);
        break;
    case 22:
        r = func_8003A5A0(a, kind, t, 1);
        break;
    case 18:
        r = func_800481FC(a, kind, t);
        break;
    case 17:
        r = func_80048070(a, kind, t);
        break;
    case 23:
        r = func_8004874C(kind, t);
        break;
    case 19:
        r = func_800488B8(kind, t);
        break;
    }
    if (r == 1) {
        D_801D8724--;
    }
    D_800AA268.p = saved;
    return r;
}

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

void func_8004AD18(Throw *t) {
    switch (t->unk_08) {
    case 1:
    case 9:
    case 18:
        func_80049E10(t);
        break;
    case 11:
        func_80049304(t);
        break;
    case 12:
        func_80049850(t);
        break;
    case 19:
        func_80049650(t);
        break;
    case 2:
    case 8:
        func_800490D4(t);
        break;
    case 3:
        func_800499F4(t);
        break;
    case 4:
        func_80049B9C(t);
        break;
    case 5:
        func_8004A698(t);
        break;
    case 6:
        func_8004A1F8(t);
        break;
    case 21:
    case 22:
        func_8003A744(t);
        break;
    case 17:
        func_8004A044(t);
        break;
    case 23:
        func_800494B4(t);
        break;
    case 7:
        func_8003956C(t);
        break;
    }
}

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
    D_800AA248.cur_obj->vel_x.w >>= 1;
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

void func_8004AFD4(void) {
    u16 s = D_801E2A54;

    if (s >= 9) {
        if (s == 9) {
            func_8004B990();
        } else if (s == 10) {
            func_8004B754();
        }
    } else {
        func_8004B540();
    }
}

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

void func_8004B204(void) {
    GameObject *saved = D_800AA248.cur_obj;
    ObjectDef *def;
    s32 *anim;
    ThrowRec *rec;
    ThrowInit *ini;
    s32 x;
    u16 n;

    D_800AA248.new_def = func_8001D110();
    def = D_800AA248.new_def;
    if (D_801FA960 >= 0x4B) {
        def->anim = anim = D_80096258;
    } else {
        def->anim = anim = D_80096240;
    }
    n = 3;
    rec = D_801F9A54;
    ini = D_8007F644;
    def->id = anim[0];
    do {
        rec->x_alt = ini->x_alt;
        rec->y_alt = ini->y_alt;
        rec->y_back = ini->y_back;
        rec->speed = ini->speed;
        rec->land_anim = ini->land_anim;
        rec->x0 = ini->x0;
        rec->y0 = ini->y0;
        x = D_801F9AC8.w + (rec->x0 << 16);
        def->pos_x.w = x;
        if (x <= 0) {
            def->pos_x.w = x + D_801D8864.w;
        }
        def->pos_y.s.hi = rec->y0;
        def->flags = 0x4000;
        D_800AA248.cur_obj = func_8001DCB4();
        if (D_800AA248.cur_obj == NULL) {
            D_801E2A54 = 0xB;
            D_801D8710 = 0;
            D_800AA248.cur_obj = saved;
            return;
        }
        rec->obj = D_800AA248.cur_obj;
        rec++;
        ini++;
        D_800AA248.cur_obj->vel_x.w = 0xC0000;
    } while (--n != 0);
    D_801D8710 = 3;
    D_800AA248.cur_obj = saved;
}

#ifdef NON_MATCHING
/* 92 %: the wrap is width & (camera + x), as the original; loop.c hoists only the width's high half out of the loop here, the original also the camera's (s7 and s8) */
void func_8004B3D0(void) {
    u16 s = 7;
    ThrowRec *rec;
    GameObject *obj;
    u16 n;
    u16 x;
    u16 y;

    if (D_801E2A54 != 4) {
        s = 8;
    }
    rec = D_801F9A54;
    n = D_801D8710;
    D_801E2A54 = s;
    do {
        rec->armed = 0;
        obj = rec->obj;
        if (D_801E2A54 == 7) {
            if (D_801FA960 >= 0x4B) {
                func_8001E698(obj, D_80096258);
            } else {
                func_8001E698(obj, D_80096240);
            }
            x = rec->x_alt;
            y = rec->y_alt;
        } else {
            if (D_801FA960 >= 0x4B) {
                func_8001E698(obj, D_80096258);
            } else {
                func_8001E698(obj, D_80096240);
            }
            x = rec->x0;
            y = rec->y_back;
        }
        rec++;
        obj->pos_y.s.hi = y;
        obj->pos_x.w = D_801D8864.w & (D_801F9AC8.w + (x << 16));
        obj->flags ^= 0x10;
        obj->vel_x.w = -obj->vel_x.w;
    } while (--n != 0);
}
#else
INCLUDE_ASM("asm/main/nonmatchings/throw", func_8004B3D0);
#endif

void func_8004B540(void) {
    ThrowRec *rec = D_801F9A54;
    u16 n = D_801D8710;
    GameObject *obj;
    u16 s;

    do {
        obj = rec->obj;
        rec++;
        obj->pos_x.w = (obj->vel_x.w + obj->pos_x.w) & D_801D8864.w;
    } while (--n != 0);
    func_8004B990();
    /* the counter doubles as the mode: the original re-extends it before the call (andi a3) */
    n = 2;
    if (D_801E1C8C == 2) {
        n = 1;
    }
    rec = D_801F9A54;
    if (func_8004B660((Throw *) rec, D_801F9A54[0].obj, 100, n) == 0) {
        if (D_801E1C8C == 3) {
            func_8004B80C();
        }
    } else {
        n = D_801D8710;
        do {
            obj = rec->obj;
            rec++;
            obj->pos_y.s.hi += 0x250;
        } while (--n != 0);
        s = 1;
        if (D_801E2A54 == 8) {
            s = 9;
        }
        D_801E2A54 = s;
        if (s == 9) {
            func_8004B754();
        }
    }
}

u16 func_8004B660(Throw *t, GameObject *target, s16 range, u16 mode) {
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

u16 func_8004B6C4(GameObject *obj, s16 range, s32 mode) {
    s32 x = D_801F9AC8.w;
    s32 dx = range << 16;

    mode &= 0xFFFF;
    if (mode != 1) {
        dx += 0x1800000;
        x += dx;
        x &= D_801D8864.w;
        if (obj->pos_x.w >= x) {
            D_800AA2C0 = 1;
        } else {
            D_800AA2C0 = 0;
        }
    } else {
        x -= dx;
        if (x <= 0) {
            x += D_801D8864.w;
        }
        if (x >= obj->pos_x.w) {
            D_800AA2C0 = mode;
        } else {
            D_800AA2C0 = 0;
        }
    }
    return D_800AA2C0;
}

void func_8004B754(void) {
    u16 n = D_801D8710;
    ThrowRec *rec = D_801F9A54;
    u16 q;
    u32 total;

    do {
        if (rec->obj != NULL) {
            func_8001E4B0(rec->obj);
        }
        rec++;
    } while (--n != 0);
    total = *func_80025C08(D_8007F634);
    q = total / D_801D8850;
    if (q < 0x537) {
        q = 0x538;
    } else {
        D_801D8850++;
    }
    func_8004AF1C(q);
}

void func_8004B80C(void) {
    GameObject *saved = D_800AA248.cur_obj;
    ThrowRec *rec = D_801F9A54;
    ObjectDef *def;
    GameObject *obj;
    s32 x;
    u16 n;

    if (rec->thrown == NULL) {
        obj = rec->obj;
        x = obj->pos_x.w;
        if (x < D_801F9AC8.w) {
            x += D_801D8864.w;
        }
        if (x >= D_801F9AC8.w + 0x820000 && x <= (D_801D8864.w >> 1) + D_801F9AC8.w) {
            n = D_801D8710;
            if (D_8007A696 & 8) {
                func_80062E24(0x6D);
                D_8007A696 &= ~8;
            }
            D_800AA248.new_def = func_8001D110();
            def = D_800AA248.new_def;
            do {
                obj = rec->obj;
                def->pos_x.w = obj->pos_x.w;
                def->pos_y.w = obj->pos_y.w;
                def->anim = D_80096150;
                def->id = D_80096150[0];
                def->flags = 0x1004;
                D_800AA248.cur_obj = func_8001DCB4();
                rec->thrown = D_800AA248.cur_obj;
                D_800AA248.cur_obj->vel_x.w = rec->speed;
                D_800AA248.cur_obj->unk_88 = 0x9000;
                rec++;
            } while (--n != 0);
        }
    }
    D_800AA248.cur_obj = saved;
}

void func_8004B990(void) {
    u16 n = D_801D8710;
    ThrowRec *rec = D_801F9A54;
    GameObject *saved = D_800AA248.cur_obj;
    GameObject *obj;
    s32 v;

    obj = rec->thrown;
    if (obj != NULL) {
        do {
            v = obj->pos_x.w + obj->vel_x.w;
            v &= D_801D8864.w;
            obj->pos_x.w = v;
            v = obj->vel_y.w + obj->unk_88;
            if (v > 0xD0000) {
                v = 0xD0000;
            }
            obj->vel_y.w = v;
            obj->pos_y.w += v;
            if (obj->pos_y.w > 0xDC0000) {
                obj->pos_y.w = 0xDC0000;
                obj->unk_88 = 0;
                obj->vel_y.w = 0;
                obj->vel_x.w = 0;
                func_8001F724(5);
                func_8001E698(obj, rec->land_anim);
                if (D_801E0D60 == 0) {
                    D_801E0D60 = 1;
                    func_8004BAC0();
                }
            }
            rec++;
        } while (--n != 0 && (obj = rec->thrown) != NULL);
    }
    D_800AA248.cur_obj = saved;
}

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

INCLUDE_ASM("asm/main/nonmatchings/throw", func_8004BBC8);

void func_8004BFE0(void) {
    ObjectDef *def = func_8001D110();
    GameObject *saved;

    D_800AA248.new_def = def;
    def->pos_x.s.hi = D_800AA248.cur_obj->pos_x.s.hi;
    def->pos_y.s.hi = D_800AA248.cur_obj->pos_y.s.hi - 0xA;
    def->flags = 0x4100;
    def->anim = &D_8008A7A4;
    def->id = D_8008A7A4.id;
    saved = D_800AA248.cur_obj;
    func_8001DCB4();
    D_800AA248.cur_obj = saved;
}
