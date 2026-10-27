/* Commands of the monsters' animation scripts: each function runs one command on the object being updated
 * (D_800AA248.cur_obj, whose owner is the Monster), with its operands at cur_obj->arg; the ones that set
 * cur_obj->script_pc are branches. Named after its first function until the rest is understood.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "gameobject.h"
#include "game_8004E574.h"

s32 func_8001EB10(s32 range, s32 arg1);                     /* a random number */
s32 func_8001EA78(void);                                    /* a random number */
void func_8001F7CC(s32 sound, s32 variant);                 /* play a sound */
ObjectDef *func_8001D110(void);                             /* a fresh definition to fill in */
GameObject *func_8001DCB4(void);                            /* create the object of D_800AA248.new_def */
void func_8001E4B0(GameObject *obj);                        /* free an object */
void func_80020BA0(s32, u16 flags, GameObject *obj);
void func_8002CE74(u16, Monster *m, void *);
void func_8002CFAC(Monster *m, Building *b);
void func_8002D0C0(Monster *m, Building *b);
u16 func_80030CD4(void *);
void func_80030E04(Monster *m, void *, void *);
void func_80031280(Monster *m, Building *b, u16);
void func_8004CFE8(void);
s32 func_8004D150(u16 *, Monster *m, void *);
void func_800524B4(Monster *m);
void func_80053C50(s32, Monster *m);
void func_8005404C(Monster *m);
u16 func_8005453C(s16 x, s16 y, Monster *m);
void *func_80054728(u16);
void func_80056488(Monster *m);
void func_800564D8(Monster *m);
void func_80056560(Monster *m);

extern u16 D_801D36FC;
extern u16 D_801D37BC;
extern u16 D_801FA98C;
extern u16 D_801FA990;
extern u16 D_801E29A4;
extern u16 D_801F9ABC;
extern GameObject *D_800AA284;
extern u16 D_801D8866;
extern s16 D_801F9ACA;
extern GameObject *D_801D874C;
extern s16 D_801E289C;
extern s32 D_80011B08[];
extern s32 *D_80085114[];
extern s16 D_801F9A44[];
extern u8 D_801FA8A6;
extern u8 D_80095628[], D_80095678[], D_8009556C[];

void func_8004F7F4(GameObject *obj, Monster *m1, Monster *m2, GameObject *cur);

void func_8004E574(void) {
    Monster *m = D_800AA248.cur_obj->owner.monster;
    SpeedPair *s;

    if (D_800AA248.cur_obj->unk_20.f.flags & 0x10) {
        s = D_8007F758;
    } else {
        s = D_8007F710;
    }
    s += m->unk_0CC;
    m->unk_100 = s->speed;
    D_800AA248.cur_obj->vel_y.w = s->vel_y;
    m->unk_104 = 0x4000;
    if (m->unk_18E != 0) {
        D_800AA248.cur_obj->vel_y.w = 0xFFFA0000;
        m->unk_104 = 0x2000;
    }
    D_800AA248.cur_obj->vel_x.w = 0;
}

void func_8004E608(void) {
    Monster *m = D_800AA248.cur_obj->owner.monster;
    s32 speed;

    speed = 0x10000;
    if (D_800AA248.cur_obj->unk_20.f.flags & 0x10) {
        speed = 0xFFFF0000;
    }
    m->unk_100 = speed;
    D_800AA248.cur_obj->vel_y.w = 0xFFFA8000;
    m->unk_104 = 0x4000;
    D_800AA248.cur_obj->vel_x.w = 0;
}

void func_8004E658(void) {
    Monster *m = D_800AA248.cur_obj->owner.monster;
    SpeedPair *s;

    if (m->unk_168 == 7) {
        s = D_8007F7E8;
    } else {
        s = D_8007F7A0;
    }
    s += m->unk_0CC;
    m->unk_100 = s->speed;
    D_800AA248.cur_obj->vel_y.w = s->vel_y;
    m->unk_104 = 0x4000;
    if (m->unk_18E != 0) {
        D_800AA248.cur_obj->vel_y.w = 0xFFFA0000;
        m->unk_104 = 0x2000;
    }
    D_800AA248.cur_obj->vel_x.w = 0;
}

#ifdef NON_MATCHING
/* 97%: register names only (the level state's address in a1, the monster in a0) */
void func_8004E6F0(void) {
    Monster *m = D_800AA248.cur_obj->owner.monster;
    SpeedPair *s = &D_8007F878[m->unk_0CC];

    m->unk_100 = s->speed;
    D_800AA248.cur_obj->vel_y.w = s->vel_y;
    m->unk_104 = 0x4000;
    if (m->unk_18E != 0) {
        D_800AA248.cur_obj->vel_y.w = 0xFFFA0000;
        m->unk_104 = 0x2000;
    }
    D_800AA248.cur_obj->vel_x.w = 0;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004E574", func_8004E6F0);
#endif

#ifdef NON_MATCHING
/* 97%: as func_8004E6F0 */
void func_8004E764(void) {
    Monster *m = D_800AA248.cur_obj->owner.monster;
    SpeedPair *s = &D_8007F830[m->unk_0CC];

    m->unk_100 = s->speed;
    D_800AA248.cur_obj->vel_y.w = s->vel_y;
    m->unk_104 = 0x4000;
    if (m->unk_18E != 0) {
        D_800AA248.cur_obj->vel_y.w = 0xFFFA0000;
        m->unk_104 = 0x2000;
    }
    D_800AA248.cur_obj->vel_x.w = 0;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004E574", func_8004E764);
#endif

void func_8004E7D8(void) {
    D_800AA248.cur_obj->pos_y.s.hi = *D_800AA248.cur_obj->arg.h;
}

void func_8004E7F8(void) {
    u16 *arg = D_800AA248.cur_obj->arg.h;

    D_800AA248.cur_obj->pos_x.s.hi += arg[0];
    D_800AA248.cur_obj->pos_y.s.hi += arg[1];
}

void func_8004E83C(void) {
    Monster *m;

    if (D_801D36FC != 0x240) {
        m = D_800AA248.cur_obj->owner.monster;
        if (m->unk_008.w <= 0x190000 && m->unk_004 == 0 && m->unk_0F6 == 0) {
            m->unk_0F6 = 1;
            m->action = 0x1E;
        }
    }
}

void func_8004E8A8(void) {
}

void func_8004E8B0(void) {
}

void func_8004E8B8(void) {
    Monster *m = D_800AA248.cur_obj->owner.monster;
    u16 y;
    void *bld;
    u16 kind;

    if (m->unk_1B0 == 2) {
        D_800AA248.cur_obj->unk_20.f.flags |= 0x10;
    } else if (m->unk_1B0 == 1) {
        D_800AA248.cur_obj->unk_20.f.flags &= ~0x10;
    }
    y = D_800AA248.cur_obj->pos_y.s.hi;
    bld = func_80054728(m->unk_1B2);
    if (bld != NULL) {
        kind = *(u16 *) ((u8 *) bld + 8);
        if (kind != 0x300) {
            y -= 8;
            if (kind != 0x200) {
                y -= 8;
            }
        }
    }
    D_800AA248.cur_obj->pos_y.s.hi = y;
    m->action = 6;
}

void func_8004E97C(void) {
    D_800AA248.cur_obj->unk_20.f.flags ^= 0x10;
}

void func_8004E99C(void) {
    D_800AA248.cur_obj->unk_20.f.flags ^= 0x10;
    if (D_800AA248.cur_obj->unk_20.f.flags & 0x10) {
        D_800AA248.cur_obj->pos_x.s.hi += 0xE;
    } else {
        D_800AA248.cur_obj->pos_x.s.hi -= 0xE;
    }
}

void func_8004EA00(void) {
    D_800AA248.cur_obj->unk_20.f.flags ^= 0x10;
    D_800AA248.cur_obj->pos_y.s.hi += *D_800AA248.cur_obj->arg.h;
}

void func_8004EA44(void) {
    D_800AA248.cur_obj->unk_20.f.flags ^= 0x20;
    D_800AA248.cur_obj->pos_y.s.hi += *D_800AA248.cur_obj->arg.h;
}

void func_8004EA88(void) {
    D_800AA248.cur_obj->unk_20.f.flags &= ~0x20;
}

void func_8004EAA8(void) {
    D_800AA248.cur_obj->owner.monster->unk_1C8 = 0;
}

void func_8004EAC0(void) {
    if (D_800AA248.cur_obj->unk_6C & 0x80) {
        D_800AA248.cur_obj->script_pc = *D_800AA248.cur_obj->arg.w;
    }
}

void func_8004EAFC(void) {
    if (D_800AA248.cur_obj->owner.monster->unk_138 != 0) {
        D_800AA248.cur_obj->script_pc = *D_800AA248.cur_obj->arg.w;
    }
}

void func_8004EB3C(void) {
    D_800AA248.cur_obj->owner.monster->unk_138 = *D_800AA248.cur_obj->arg.h;
}

void func_8004EB5C(void) {
    s32 vel;

    vel = 0xA0000;
    if (D_800AA248.cur_obj->unk_20.f.flags & 0x10) {
        vel = 0xFFF60000;
    }
    D_800AA248.cur_obj->vel_x.w = vel;
}

void func_8004EB88(void) {
    Monster *m = D_800AA248.cur_obj->owner.monster;

    if (m->unk_1B0 == 1) {
        func_80056488(m);
    } else {
        func_800564D8(m);
    }
    m->unk_1B0 = 3;
    m->action = 0;
}

#ifdef NON_MATCHING
/* 97%: the building index stays in a2 across the loop in the original; here it is copied to a3 and the masked counter takes a2 */
void func_8004EBE8(void) {
    Monster *m = D_800AA248.cur_obj->owner.monster;
    u16 bld;
    u16 n;
    Building *b;
    u16 i;

    if (m->unk_1B0 == 1) {
        func_80056488(m);
    } else {
        func_800564D8(m);
    }
    func_80056560(m);
    bld = m->unk_1B2;
    if (bld != 0) {
        n = D_801E29A4;
        b = D_801D3DC8;
        if (n != 0) {
            i = 0;
            do {
                i++;
                if (i == bld && b->unk_078 == 0) {
                    func_80031280(m, b, bld);
                    return;
                }
                b++;
            } while (--n != 0);
        }
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004E574", func_8004EBE8);
#endif

void func_8004ECA8(void) {
    D_800AA248.cur_obj->owner.monster->unk_05E = 1;
    D_800AA248.cur_obj->pos_x.s.hi = 0x500;
    D_800AA248.cur_obj->pos_y.s.hi = 0x500;
}

void func_8004ECDC(void) {
    if ((D_800AA2DC == 0 || !(D_8007BD78.flags & 0x40)) && D_800AA248.cur_obj->owner.monster->unk_18A == 0) {
        func_8004CFE8();
    }
}

void func_8004ED44(void) {
    if (D_800AA248.cur_obj->owner.monster->obj->vel_y.w <= 0) {
        D_800AA248.cur_obj->script_pc = *D_800AA248.cur_obj->arg.w;
    }
}

#ifdef NON_MATCHING
/* 96%: the building array's address is materialized before the count test in the original (lui before, addiu in the delay slot) */
void func_8004ED8C(void) {
    GameObject *saved = D_800AA248.cur_obj;
    Monster *m;
    Building *b;

    if (D_800AA2DC == 0 || !(D_8007BD78.flags & 0x40)) {
        m = saved->owner.monster;
        D_800AA248.cur_obj = m->obj;
        if (m->unk_1B0 == 3 && m->unk_0EA == 4) {
            b = D_801D3DC8;
            if (D_801E29A4 != 0) {
                b += m->unk_1B2 - 1;
                m->unk_0FC = m->y;
                m->unk_0FA = m->x;
                if (b->unk_058 == 0) {
                    func_8002D0C0(m, b);
                } else {
                    func_8002CFAC(m, b);
                    m->unk_18A = 1;
                    if ((u32) (b->unk_058 - 2) >= 2) {
                        func_800524B4(m);
                    }
                }
                func_8005404C(m);
                b->unk_032 = m->id;
                m->unk_18A = 1;
                D_800AA248.unk_78 = 1;
            } else {
                D_800AA248.unk_78 = 0;
            }
        } else {
            D_800AA248.unk_78 = 0;
        }
        D_800AA248.cur_obj = saved;
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004E574", func_8004ED8C);
#endif

void func_8004EEF4(void) {
    func_8001F7CC(0xE6, *D_800AA248.cur_obj->arg.h);
}

void func_8004EF28(void) {
    func_8001F7CC(0xE6, (func_8001EA78() & 3) + 0x22);
}

void func_8004EF58(void) {
    s32 v;

    func_8001F7CC(0xFA, (func_8001EA78() & 3) + 0x22);
    v = func_8001EA78() & 3;
    if (v == 3) {
        v = 0;
    }
    func_8001F7CC(0x64, v + 0x47);
}

void func_8004EFAC(void) {
    s32 v;

    v = func_8001EA78() & 3;
    if (v == 3) {
        v = 0;
    }
    func_8001F7CC(0xF0, v | 0x14);
}

#ifdef NON_MATCHING
/* 96%: the registers of the monster and of the other monster's object are swapped (s1/s2) */
void func_8004EFE8(void) {
    Monster *m = D_800AA248.cur_obj->owner.monster;
    Monster *other;
    GameObject *o;
    u16 i;

    if (D_800AA248.cur_obj->pos_y.s.hi == 0xE1 && m->unk_1B0 == 0 && m->unk_18E == 0) {
        i = 7;
        do {
            if (i != m->id) {
                other = &D_801E0B78[i];
                if (other->id != 0 && (other->unk_058 & 1) && other->unk_1B0 == 0 && other->unk_18E == 0) {
                    o = other->obj;
                    if (o != NULL && !(o->unk_6C & 0x80)) {
                        if (other->unk_0DC != 0 && other->action == 3 && o->pos_y.s.hi == 0xE1 &&
                            (D_800AA248.cur_obj->unk_20.f.flags & 0x10) != (o->unk_20.f.flags & 0x10)) {
                            if (func_8005453C(m->x, m->y, other)) {
                                m->unk_18A = 1;
                                other->action = 0x41;
                                other->unk_0E4 = m->id;
                                m->action = 0x42;
                                other->unk_18C = 0;
                                m->unk_18C = 0;
                                other->unk_12A = m->id;
                                m->unk_12A = other->id;
                                func_8004F7F4(o, m, other, D_800AA248.cur_obj);
                                return;
                            }
                        }
                    }
                }
            }
        } while (--i != 0);
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004E574", func_8004EFE8);
#endif

#ifdef NON_MATCHING
/* 86%: the definition pointer is kept in a1 and D_800AA248.new_def stored right after the call; the stores to the definition come in another order */
void func_8004F1CC(void) {
    GameObject *saved = D_800AA248.cur_obj;
    GameObject *obj = saved;
    ObjectDef *def;
    GameObject *o;
    s32 *anim;
    u16 v;

    func_8001E4B0(D_801D874C);
    def = func_8001D110();
    D_800AA248.new_def = def;
    if (D_801E289C == 6) {
        anim = D_80011B08;
    } else {
        anim = D_80085114[D_801E289C];
    }
    D_801F9A44[D_801E289C] = 0;
    def->anim = anim;
    def->unk_1C = 0;
    def->id = *anim;
    def->pos_x.s.hi = obj->pos_x.s.hi + 0x46;
    def->flags = 0x101;
    def->pos_y.s.hi = obj->pos_y.s.hi - 0xA;
    o = func_8001DCB4();
    o->unk_70 = 0x540;
    if (D_801E289C == 6 && D_801FA8A6 != 0) {
        v = 3;
    } else {
        v = D_8007F8C0[D_801E289C];
    }
    o->unk_74 = v;
    D_800AA248.cur_obj = saved;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004E574", func_8004F1CC);
#endif

void func_8004F300(void) {
    if (*(u16 *) ((u8 *) D_800AA248.cur_obj->owner.p - 0x88) < 2) {
        D_800AA248.cur_obj->script_pc = D_800AA248.cur_obj->unk_48;
    }
}

void func_8004F33C(void) {
    GameObject *obj = D_800AA248.cur_obj;

    obj->unk_4D = func_8001EB10(0x12C, 0x1E);
}

void func_8004F370(void) {
    Monster *m = D_800AA248.cur_obj->owner.monster;
    u16 a;
    GameObject *o;

    if ((m->unk_05C != 0x63 && m->obj->pos_y.s.hi < 0xC3) || m->unk_1B0 != 0) {
        a = m->unk_05C;
        m->action = a;
        if (a == 2) {
            o = m->obj;
            if (o->vel_y.s.hi == 0) {
                o->vel_y.s.hi = 7;
            }
        }
    } else {
        m->action = 0;
    }
}

void func_8004F404(void) {
    Monster *m;
    s32 vel;

    if (D_800AA248.cur_obj->vel_x.w == 0) {
        m = D_800AA248.cur_obj->owner.monster;
        m->unk_1C8 = 1;
        vel = 0xF0000;
        if (D_800AA248.cur_obj->unk_20.f.flags & 0x10) {
            vel = 0xFFF10000;
        }
        D_800AA248.cur_obj->vel_x.w = vel;
        D_800AA248.cur_obj->vel_y.w = 0xFFF90000;
        m->unk_104 = 0x8000;
    }
}

void func_8004F470(s32 arg0, Monster *m) {
    m->action = 0xA;
}

#ifdef NON_MATCHING
/* 95%: the definition's id is stored after its y; the C stores it before */
void func_8004F47C(void) {
    GameObject *saved = D_800AA248.cur_obj;
    Monster *m = saved->owner.monster;
    s32 frame = saved->anim_frame;
    GameObject *obj;
    ObjectDef *def;
    s32 *arg;

    if (frame == 0x02003E9E || frame == 0x02003E9A || frame == 0x03003DFE || frame == 0x03003DFA ||
        frame == 0x04003DF6 || frame == 0x04003DF2 || frame == 0x0E003E8E || frame == 0x0E003E8A ||
        frame == 0x09003E94 || frame == 0x09003E92 || frame == 0x0C003E68 || frame == 0x0C003E66 ||
        frame == 0x0D003D94 || frame == 0x0D003D92) {
        D_800AA248.cur_obj->unk_74 = D_8007F8D0[m->id - 1];
    } else if (m->id == 7) {
        saved->unk_74 = D_801F9ABC;
    } else {
        saved->unk_74 = D_8007F8C0[m->id - 1];
    }
    obj = m->unk_16C;
    arg = D_800AA248.cur_obj->arg.w;
    D_800AA248.cur_obj = obj;
    if (obj == NULL) {
        def = func_8001D110();
        D_800AA248.new_def = def;
        def->pos_x.s.hi = m->x;
        def->pos_y.s.hi = m->y;
        def->id = 0x4F00000C;
        def->flags = saved->unk_80 + 1;
        D_800AA248.cur_obj = func_8001DCB4();
        m->unk_16C = D_800AA248.cur_obj;
    }
    D_800AA248.cur_obj->unk_80 = saved->unk_80 + 1;
    func_80020BA0(*arg, D_800AA248.cur_obj->unk_20.f.flags, D_800AA248.cur_obj);
    D_800AA248.cur_obj = saved;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004E574", func_8004F47C);
#endif

void func_8004F65C(void) {
    Monster *m = D_800AA248.cur_obj->owner.monster;
    void *bld;
    u8 *part;
    s16 y;

    if ((u32) (m->unk_0EA - 1) >= 2 && m->unk_1B0 != 0 && m->unk_1B0 != 3 && m->unk_1B2 != 0) {
        bld = func_80054728(m->unk_1B2);
        if (bld != NULL) {
            part = *(u8 **) ((u8 *) bld + 0x18);
            if (part != NULL && *(s16 *) (part + 0x1C) == m->unk_1B0) {
                y = m->y;
                if (*(s16 *) (part + 0x1E) + 0xE >= y && y >= *(s16 *) (part + 0xE) - 0xE) {
                    m->unk_18A = 1;
                    if (func_80030CD4(part) == 1) {
                        func_80053C50(0x50000, m);
                        m->action = 0x2A;
                    }
                }
            }
        }
    }
}

void func_8004F754(void) {
    GameObject *obj = D_800AA248.cur_obj;
    s32 *arg = obj->arg.w;
    s32 target = *arg++;
    u16 side = obj->owner.monster->unk_0EA;

    if (side == 3 || side == 4) {
        if (side == 4) {
            target = *arg;
        }
        obj->script_pc = target;
    }
}

s32 func_8004F7A4(u8 *list) {
    u16 n = *(u16 *) list;
    GameObject **p = (GameObject **) (list + 0x98);
    GameObject *o;

    do {
        o = *p;
        if (o != NULL && !(o->unk_6C & 0x80)) {
            return 1;
        }
        p = (GameObject **) ((u8 *) p + 0x54);
    } while (--n != 0);
    return 0;
}

#ifdef NON_MATCHING
/* 75%: the x coordinates are read after func_8001D110 and the midpoint arithmetic differs */
void func_8004F7F4(GameObject *obj, Monster *m1, Monster *m2, GameObject *cur) {
    ObjectDef *def;
    GameObject *o;
    s16 x1;
    u16 x2;
    s32 x;

    def = func_8001D110();
    x1 = cur->pos_x.s.hi;
    x2 = obj->pos_x.s.hi;
    if (D_801F9ACA >= x1) {
        x1 += D_801D8866;
    }
    if (D_801F9ACA >= (s16) x2) {
        x2 += D_801D8866;
    }
    x = (s16) (x1 + x2) >> 1;
    if (x >= (s16) D_801D8866) {
        x -= D_801D8866;
    }
    def->pos_x.s.hi = x;
    cur->pos_x.s.hi = x;
    obj->pos_x.s.hi = x;
    def->flags = 0x5500;
    def->anim = D_8009556C;
    def->id = 0x0100005E;
    def->pos_y.s.hi = cur->pos_y.s.hi;
    D_800AA284 = (GameObject *) def;
    o = func_8001DCB4();
    o->unk_70 = 0x743;
    m2->unk_0DC = 0;
    m1->unk_0DC = 0;
    o->unk_94.monster = m1;
    o->owner.monster = m2;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004E574", func_8004F7F4);
#endif

#ifdef NON_MATCHING
/* 85%: the chain that picks unk_056 (1, 2, 5 or 0) and the order of the two monster loads */
void func_8004F910(void) {
    GameObject *obj = D_800AA248.cur_obj;
    Monster *other = obj->unk_94.monster;
    Monster *m = obj->owner.monster;
    u16 v;
    s16 result;

    if (m->unk_18C >= other->unk_18C || !(func_8001EB10(0xF, 0) & 1)) {
        other->action = 0x43;
        m->action = 0x1E;
    } else {
        v = m->unk_03C;
        if (v != 0) {
            other->unk_03C = v;
            other->unk_03E += m->unk_03E;
            m->unk_03E = 0;
        }
        v = m->unk_140;
        if (v != 0) {
            other->unk_140 += v;
            m->unk_140 = 0;
        }
        v = m->unk_142;
        if (v != 0) {
            other->unk_142 += v;
            m->unk_142 = 0;
        }
        result = 2;
        if (other->unk_142 < other->unk_140) {
            result = 1;
        } else if (other->unk_142 != 0) {
            result = 2;
        } else if (other->unk_03C != 0) {
            result = 5;
        } else {
            result = 0;
        }
        other->unk_056 = result;
        other->action = 0x43;
        m->action = 0x1E;
        func_80053C50(0x30000, m);
    }
    other->unk_1C8 = 0;
    other->obj->pos_y.s.hi = 0xE1;
    m->obj->pos_y.s.hi = 0xE1;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004E574", func_8004F910);
#endif

void func_8004FA78(void) {
}

void func_8004FA80(void) {
    GameObject **p = D_800AA248.cur_obj->owner.monster->unk_1D0;

    if (p != NULL && (*p)->pos_y.s.hi < 0x150) {
        D_800AA248.cur_obj->script_pc = *D_800AA248.cur_obj->arg.w;
    }
}

void func_8004FADC(void) {
    D_800AA248.cur_obj->owner.monster->unk_0DC = 1;
}

void func_8004FAF8(void) {
    D_800AA248.cur_obj->owner.monster->unk_0DC = 0;
}

void func_8004FB10(void) {
    Monster *m = D_800AA248.cur_obj->owner.monster;
    s32 v = m->unk_1C4.w;

    if (v <= 0x27FFFF) {
        if (m->unk_168 == 7) {
            m->action = 0xC;
        }
    } else if (v > 0x014FFFFF) {
        if (m->unk_168 == 3) {
            m->action = 0xC;
        }
    }
}

void func_8004FB70(void) {
    D_800AA248.cur_obj->owner.monster->unk_13E = 0x1A4;
}

void func_8004FB8C(void) {
    GameObject *obj = D_800AA248.cur_obj;
    s16 x;

    if (D_801D37BC == 0 && D_801FA98C != 0) {
        x = obj->pos_x.s.hi;
        if (x >= D_801FA98C && D_801FA990 >= x) {
            obj->script_pc = *obj->arg.w;
        }
    }
}

void func_8004FBF8(void) {
}

void func_8004FC00(s32 n, Monster *m) {
    if (D_801D36FC != 0x240) {
        m->unk_028 += n;
    }
}

#ifdef NON_MATCHING
/* 84%: the sign extension of x for the third case is hoisted before the branches in the original */
void func_8004FC2C(void) {
    GameObject *saved = D_800AA248.cur_obj;
    Monster *m = saved->owner.monster;
    u16 x = saved->pos_x.s.hi;
    u16 side = m->unk_1B0;
    u16 y = saved->pos_y.s.hi;
    s32 flip;
    ObjectDef *def;
    GameObject *obj;

    if (side != 1) {
        if (side == 2) {
            x -= 0x24;
            y -= 0x2B;
            flip = 0x10;
        } else {
            flip = saved->unk_20.f.flags & 0x10;
            if (flip == 0) {
                x = (s16) x + 0x21;
            } else {
                x = (s16) x - 0x21;
            }
            y -= 0x2A;
        }
    } else {
        x += 0x24;
        y -= 0x2B;
        flip = 0;
    }
    def = func_8001D110();
    D_800AA248.new_def = def;
    def->flags = 0x1100;
    def->pos_x.s.hi = x;
    def->pos_y.s.hi = y;
    def->id = 0x4F0000C2;
    def->anim = D_80095628;
    obj = func_8001DCB4();
    D_800AA248.cur_obj = obj;
    obj->unk_20.f.flags |= flip;
    D_800AA248.cur_obj->unk_9C = m->id;
    D_800AA248.cur_obj = saved;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004E574", func_8004FC2C);
#endif

#ifdef NON_MATCHING
/* 96%: register names only (x, y and the saved object in s2, s1, s3) */
void func_8004FD44(void) {
    GameObject *saved = D_800AA248.cur_obj;
    Monster *m = saved->owner.monster;
    s32 x = (u16) saved->pos_x.s.hi;
    s32 y = (u16) saved->pos_y.s.hi;
    s32 flip;
    ObjectDef *def;
    GameObject *obj;

    flip = 0;
    if (m->unk_1B0 == 2) {
        x += 4;
        y -= 0x28;
        flip = 0x10;
    } else {
        x -= 4;
        y -= 0x28;
    }
    def = func_8001D110();
    D_800AA248.new_def = def;
    def->flags = 0x1100;
    def->pos_x.s.hi = x;
    def->pos_y.s.hi = y;
    def->id = 0x4F0000C2;
    def->anim = D_80095628;
    obj = func_8001DCB4();
    D_800AA248.cur_obj = obj;
    obj->unk_20.f.flags |= flip;
    D_800AA248.cur_obj->unk_9C = m->id;
    D_800AA248.cur_obj = saved;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004E574", func_8004FD44);
#endif

#ifdef NON_MATCHING
/* 84%: the registers of y and the flip, and the sign of the top-of-sprite arithmetic */
void func_8004FE28(void) {
    GameObject *saved = D_800AA248.cur_obj;
    Monster *m = saved->owner.monster;
    s32 top = (u16) saved->pos_y.s.hi - saved->height;
    u16 side = m->unk_1B0;
    s32 dx;
    s32 y;
    s32 flip;
    s16 x;
    ObjectDef *def;
    GameObject *obj;

    if (side != 1) {
        y = top + 0x21;
        if (side == 2) {
            dx = 8;
            y = top + 0x14;
            flip = 0;
        } else {
            dx = -0x1E;
            flip = saved->unk_20.f.flags & 0x10;
            if (flip == 0) {
                dx = 0x1E;
            }
        }
    } else {
        dx = -8;
        y = top + 0x14;
        flip = 0x10;
    }
    x = dx + (u16) D_800AA248.cur_obj->pos_x.s.hi;
    def = func_8001D110();
    D_800AA248.new_def = def;
    def->flags = 0x1100;
    def->pos_y.s.hi = y;
    def->pos_x.s.hi = x;
    def->anim = D_80095678;
    obj = func_8001DCB4();
    D_800AA248.cur_obj = obj;
    obj->unk_20.f.flags |= flip;
    D_800AA248.cur_obj->unk_9C = m->id;
    D_800AA248.cur_obj = saved;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004E574", func_8004FE28);
#endif

void func_8004FF3C(void) {
    GameObject *saved = D_800AA248.cur_obj;
    Monster *m = saved->owner.monster;
    u16 side = m->unk_1B0;
    u16 ea;
    void *bld;
    s32 r;
    u16 sp10;

    if (side != 0 && side != 3) {
        ea = m->unk_0EA;
        if (ea != 4) {
            if (ea != 3) {
                if (ea != side) {
                    bld = func_80054728(m->unk_1B2);
                    if (bld != NULL) {
                        m->unk_0FA = m->x;
                        m->unk_0FC = m->y;
                        if (*(u16 *) ((u8 *) bld + 0x58) != 0) {
                            func_8002CFAC(m, bld);
                            m->unk_18A = 1;
                        } else {
                            r = func_8004D150(&sp10, m, bld);
                            if (r != 0) {
                                if (m->unk_1BC == 0) {
                                    func_80030E04(m, (void *) r, (void *) r);
                                } else {
                                    func_8002CE74(sp10, m, (void *) r);
                                }
                            }
                        }
                    }
                    D_800AA248.cur_obj = saved;
                }
            }
        }
    }
}

void func_80050044(void) {
    Monster *m = D_800AA248.cur_obj->owner.monster;

    switch (m->unk_0CC) {
    case 7:
        m->unk_100 -= 0x2000;
        break;
    case 6:
    case 8:
        m->unk_100 -= 0x2000;
        break;
    case 2:
    case 3:
    case 4:
        m->unk_100 += 0x2000;
        break;
    default:
        return;
    }
    if (m->unk_100 > 0x10000) {
        m->unk_100 = 0x10000;
    }
    if (m->unk_100 < -0x10000) {
        m->unk_100 = -0x10000;
    }
}

INCLUDE_RODATA("asm/main/nonmatchings/game_8004E574", D_800114FC);
