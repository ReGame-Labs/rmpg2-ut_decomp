/* More commands of the monsters' animation scripts, and what happens when a monster is hit: by a projectile
 * (the table D_8007F680 of handlers by projectile kind, run from func_8004C064) or by another monster
 * (func_8004DDFC). Named after its first function until the rest is understood.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "game.h"
#include "game_8004C064.h"

/* The current object as a scalar: the same word as D_800AA248.cur_obj, which some functions read on its own
 * (func_8004C738). */

s32 func_8001EB10(s32 range, s32 arg1);                     /* a random number */
void func_8001E4B0(GameObject *obj);                        /* free an object */
void func_8001F724(s32 sound);
void func_8001F7CC(s32 sound, s32 variant);
void func_80020BA0(s32, u16 flags, GameObject *obj);
s32 func_8002CD24(u16, Monster *m, s32);
void func_8002CE74(u16, Monster *m, s32);
void func_8002CFAC(Monster *m, Building *b);
void func_8002D5B8(Monster *m, s32);
u16 func_8003CBE0(Ai *p, Monster *m);
u16 func_8003CC84(Ai *p, Monster *m);
u16 func_80053970(Monster *m, Monster *other);
void func_80053C50(s32, Monster *m);
void func_80053D68(s32, Monster *m);
void func_8005404C(Monster *m);
void func_800540D0(Monster *m);
void func_8005417C(Monster *m);
void func_80054374(s32, Monster *m);
void *func_80054728(u16);
void func_8005E0E8(Monster *m);
s32 func_8005F208();                                        /* called with 0, 1 or 2 arguments */
void func_800634D4(Monster *m, s32);
void func_800635F4(s32, s32);


void func_8004C0E0(Ai *p, Monster *m);
void func_8004C1A0(Ai *p, Monster *m);
void func_8004C1E4(Ai *p, Monster *m);
void func_8004C1F8(Ai *p, Monster *m);
void func_8004C20C(Ai *p, Monster *m);
void func_8004C220(Ai *p, Monster *m);
void func_8004C2B0(Ai *p, Monster *m);
u16 func_8004C308(s32 pc, s32);
s32 func_8004D150(u16 *side, Monster *m, s32 bld);
s32 func_8004D264(s16 *side, Monster *m, s32 bld);
u16 func_8004D530(Monster *m, Ai **out);
u16 func_8004D5D4(Ai *p);
u16 func_8004D6F8(Monster *m, Ai **out);
void func_8004D980(GameObject *obj, Monster *m, Monster *other);
void func_8004DAB0(GameObject *obj, Monster *m, Monster *other);
void func_8004DAD4(Monster *m, Monster *other);
void func_8004DB28(GameObject *obj, Monster *m, Monster *other);
void func_8004DBB0(Monster *m, Monster *other);
void func_8004DC08(Monster *m, Monster *other);
void func_8004DC7C(Monster *m, Monster *other);
void func_8004DCFC(GameObject *obj, Monster *m, Monster *other);
void func_8004DD78(GameObject *obj, Monster *m, Monster *other);
void func_8004FC00(s32 n, Monster *m);

void func_8004C064(Ai *p, Monster *m) {
    u16 kind;
    ProjectileHitFn *handler;

    if (p->unk_0E != 0) {
        kind = p->action;
        if (kind < 0xF) {
            if (m->unk_1AE != 0 && kind == 1) {
                p->action = 0;
            }
            handler = &D_8007F680[p->action];
            (*handler)(p, m);
        }
    }
}

void func_8004C0E0(Ai *p, Monster *m) {
    s32 push;
    s32 lift;
    s16 action;

    m->unk_022++;
    if (func_8003CC84(p, m) == 1) {
        action = 0x55;
    } else {
        if (func_8003CBE0(p, m) == 1) {
            push = 0x220000;
            lift = 0x1A0000;
        } else {
            push = 0xA0000;
            lift = 0x1C000;
        }
        m->unk_010.w += lift;
        if (m->unk_010.w > 0x440000) {
            m->unk_010.w = 0x440000;
        }
        func_80053D68(push, m);
        action = 8;
        m->unk_126 = 0;
    }
    m->action = action;
}

void func_8004C1A0(Ai *p, Monster *m) {
    func_80053C50(0x40000, m);
    m->unk_126 = p->action;
    m->action = 8;
}

void func_8004C1E4(Ai *p, Monster *m) {
    m->unk_126 = p->action;
    m->action = 8;
}

void func_8004C1F8(Ai *p, Monster *m) {
    m->unk_126 = 6;
    m->action = 0x25;
}

void func_8004C20C(Ai *p, Monster *m) {
    m->unk_126 = 3;
    m->action = 0x2A;
}

void func_8004C220(Ai *p, Monster *m) {
    func_8001F724(0x4F);
    m->unk_126 = 5;
    m->action = 0x1A;
}

void func_8004C258(void) {
    Monster *m = D_800AA248.cur_obj->owner.monster;
    GameObject *o;

    func_80053C50(*D_800AA248.cur_obj->arg.h << 16, m);
    o = m->unk_16C;
    if (o != NULL) {
        func_8001E4B0(o);
        m->unk_16C = NULL;
    }
}

void func_8004C2B0(Ai *p, Monster *m) {
}

s32 func_8004C2B8(s32 pc, s32 arg1) {
    GameObject *obj = D_800AA248.cur_obj;

    if (obj->unk_48 != pc) {
        return func_8004C308(pc, arg1);
    }
    D_800AA248.unk_7A = 1;
    return 1;
}

u16 func_8004C308(s32 pc, s32 arg1) {
    D_800AA248.cur_obj->unk_48 = pc;
    D_800AA248.cur_obj->script_pc = pc;
    D_800AA248.cur_obj->unk_4C = 0;
    D_800AA248.cur_obj->unk_4D = 0;
    D_800AA248.cur_obj->unk_64 = 0;
    func_800635F4(arg1, pc);
    D_800AA248.cur_obj->flags |= 0x800;
    D_800AA248.unk_7A = 0;
    return 0;
}

void func_8004C38C(void) {
}

void func_8004C394(void) {
    D_800AA248.cur_obj->unk_74 = 0xFFFF;
}

void func_8004C3A8(void) {
    GameObject *saved = D_800AA248.cur_obj;
    Monster *m = saved->owner.monster;

    func_80020BA0(*saved->arg.w, saved->flags, saved);
    if (m->id == 7) {
        D_800AA248.cur_obj->unk_74 = D_801F9ABC;
    } else {
        D_800AA248.cur_obj->unk_74 = 0;
    }
    D_800AA248.cur_obj = saved;
}

void func_8004C430(void) {
    GameObject *obj = D_800AA248.cur_obj;
    s32 pc = *obj->arg.w;

    obj->script_pc = pc;
    obj->unk_48 = pc;
}

void func_8004C458(void) {
    D_800AA248.cur_obj->script_pc = *D_800AA248.cur_obj->arg.w;
}

void func_8004C478(void) {
    GameObject *obj = D_800AA248.cur_obj;
    s32 *arg = obj->arg.w;

    obj->unk_48 = *arg;
    D_800AA248.cur_obj->script_pc = *arg;
}

void func_8004C4AC(void) {
    GameObject *obj = D_800AA268.p;
    s32 *arg = obj->arg.w;
    s32 first = *arg++;
    s32 second = *arg;

    if (obj->owner.monster->action == 0x4E) {
        obj->unk_48 = second;
        obj->script_pc = second;
        return;
    }
    obj->unk_48 = first;
    obj->script_pc = first;
}

void func_8004C4EC(void) {
    GameObject *obj = D_800AA248.cur_obj;
    s32 *arg = obj->arg.w;
    s32 pc;

    if (obj->owner.monster->action != 0x4E) {
        pc = *arg;
        obj->unk_48 = pc;
        obj->script_pc = pc;
    }
}

void func_8004C528(void) {
    GameObject *saved = D_800AA248.cur_obj;
    Monster *m = saved->owner.monster;
    GameObject *o;
    u16 side;

    if ((s16) m->action == (s16) m->unk_170) {
        side = m->unk_1B0;
        if (side == 0 || side == 3) {
            m->action = 0;
        } else {
            m->action = 6;
        }
        o = m->unk_16C;
        m->unk_0E0 = 0;
        m->unk_0E2 = 0;
        m->unk_126 = 0;
        m->unk_12A = 0;
        m->unk_1CA = 0;
        m->unk_1C8 = 0;
        m->unk_180 = NULL;
        if (o != NULL) {
            func_8001E4B0(o);
            m->unk_16C = NULL;
        }
    }
    D_800AA248.cur_obj = saved;
}

void func_8004C5CC(void) {
    Monster *m = D_800AA248.cur_obj->owner.monster;
    GameObject *obj;
    s32 pc;

    if (D_800AA2DC != 0 && func_8005F208() == 4 && m != NULL && m->unk_008.w <= 0x40000) {
        m->unk_008.s.hi = 0;
        if (m->unk_1B0 != 0) {
            m->action = 0x1D;
        } else {
            switch (m->action) {
            case 0x1C:
            case 0x39:
                m->action = 0x5B;
                break;
            case 0xA:
            case 0x1D:
            case 0x24:
            case 0x2F:
                m->action = 0x59;
                break;
            case 0xB:
            case 0x22:
            case 0x23:
                m->action = 0x5A;
                break;
            case 0x28:
                m->action = 0x5C;
                break;
            case 0x3A:
                m->action = 0x5E;
                break;
            case 0x1E:
            case 0x29:
                m->action = 0x5D;
                break;
            default:
                m->action = 0x59;
                return;
            }
        }
        obj = D_800AA248.cur_obj;
        pc = *obj->arg.w;
        if (pc != 0) {
            obj->script_pc = pc;
            obj->unk_48 = pc;
        }
        m->unk_0DC = 0;
        m->unk_184 = 1;
    }
}

void func_8004C710(void) {
}

void func_8004C718(void) {
    Monster *m = D_800AA248.cur_obj->owner.monster;

    m->unk_170 = m->action;
}

void func_8004C738(void) {
    GameObject *obj = D_800AA268.p;
    Monster *m = obj->owner.monster;
    u16 *arg = obj->arg.h;
    u16 action;

    m->unk_05C = m->action;
    action = *arg;
    m->unk_0D8 = 0;
    m->action = action;
}

void func_8004C768(void) {
    GameObject *obj = D_800AA248.cur_obj;
    Monster *m = obj->owner.monster;

    if (m->unk_0CC == 1 && obj->pos_y.s.hi >= 0xDC) {
        obj->pos_y.s.hi = 0xE1;
        m->action = 0x4D;
        D_800AA248.cur_obj->vel_x.w = 0;
        D_800AA248.cur_obj->vel_y.w = 0;
        D_800AA248.cur_obj->unk_84 = 0;
        D_800AA248.cur_obj->unk_88 = 0;
        m->unk_100 = 0;
        m->unk_104 = 0;
        D_800AA248.cur_obj->script_pc = *D_800AA248.cur_obj->arg.w;
    }
}

void func_8004C80C(void) {
    D_800AA248.cur_obj->vel_y.w = 0xFFFF4000;
    D_800AA248.cur_obj->owner.monster->unk_150 = 0x1E;
}

#ifdef NON_MATCHING
/* 81%: the speed-limit switch is a jump table in the original (7 entries); here GCC emits compares */
void func_8004C83C(void) {
    GameObject *obj = D_800AA248.cur_obj;
    Monster *m = obj->owner.monster;
    u16 action;
    s32 speed;
    s32 vel;
    s32 pc;

    if (m->unk_150 != 0) {
        m->unk_150--;
    }
    action = m->action;
    if (action != 0x20 && action != 0xF) {
        m->action = 2;
    }
    speed = m->unk_100;
    if (m->unk_166 == 0) {
        switch (m->unk_0CC) {
        case 6:
        case 7:
        case 8:
            speed -= 0x2000;
clamp:
            if (m->unk_150 == 0) {
                if (m->unk_168 != 7) {
                    if (speed < 0) {
                        speed = 0;
                    }
                } else if (speed > 0) {
                    speed = 0;
                }
            }
            if (m->unk_152 == 0) {
                if (m->unk_150 == 0) {
                    if (speed > 0x14000) {
                        speed = 0x14000;
                    } else if (speed < -0x14000) {
                        speed = -0x14000;
                    }
                } else if (speed > 0x12000) {
                    speed = 0x12000;
                } else if (speed < -0x12000) {
                    speed = -0x12000;
                }
            } else if (speed > 0x8000) {
                speed = 0x8000;
            } else if (speed < -0x8000) {
                speed = -0x8000;
            }
            m->unk_100 = speed;
            break;
        case 2:
        case 3:
        case 4:
            speed += 0x2000;
            goto clamp;
        }
    }
    if (m->unk_0D0 & 4) {
        if (m->unk_0CC != 1 && m->unk_0CC != 8 && m->unk_0CC != 2) {
            vel = obj->vel_y.w;
            if ((u32) (vel + 0x28000) <= 0x58000 && m->unk_1AA < 2) {
                m->unk_1AA = 2;
                if (vel >= 0) {
                    obj->vel_y.w = 0;
                }
                pc = *obj->arg.w;
                obj->unk_48 = pc;
                obj->script_pc = pc;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004C064", func_8004C83C);
#endif

void func_8004CA70(void) {
    Monster *m = D_800AA248.cur_obj->owner.monster;
    GameObject *obj;
    s32 pc;
    s32 vel;

    if (m->action != 0x20) {
        m->action = 2;
    }
    if (m->unk_0C8 & 4) {
        vel = D_800AA248.cur_obj->vel_y.w;
        if (m->unk_1AA < 2) {
            m->unk_1AA = 2;
            if (vel >= 0) {
                D_800AA248.cur_obj->vel_y.w = 0;
            }
            return;
        }
    }
    obj = D_800AA268.p;
    pc = *obj->arg.w;
    obj->unk_48 = pc;
    obj->script_pc = pc;
}

void func_8004CB08(void) {
    Monster *m = D_800AA248.cur_obj->owner.monster;
    u16 action;
    s32 speed;

    if (D_800AA248.cur_obj->pos_y.s.hi >= 0x50) {
        action = m->action;
        m->action = 0xF;
        if (m->unk_168 != 7) {
            speed = 0x4000;
            if (action == 0x3D) {
                speed = 0x6000;
            }
        } else {
            speed = -0x4000;
            if (action == 0x3D) {
                speed = -0x6000;
            }
        }
        m->unk_104 = 0x4000;
        m->unk_100 = speed;
        D_800AA248.cur_obj->vel_y.w = 0xFFFC0000;
        D_800AA248.cur_obj->vel_x.w = 0;
        return;
    }
    m->action = 0x17;
    speed = -0x8000;
    if (m->unk_168 != 7) {
        speed = 0x8000;
    }
    m->unk_100 = speed;
    m->unk_104 = 0x4000;
    D_800AA248.cur_obj->vel_y.w = 0xFFFC0000;
    D_800AA248.cur_obj->vel_x.w = 0;
}

void func_8004CBD4(void) {
    D_800AA248.cur_obj->vel_y.w = 0xFFFC0000;
}

void func_8004CBE8(void) {
    D_800AA248.cur_obj->vel_y.w = 0x40000;
}

void func_8004CBFC(void) {
    D_800AA248.cur_obj->vel_y.w = 0;
}

void func_8004CC0C(void) {
    Monster *m = D_800AA248.cur_obj->owner.monster;
    s32 *arg;

    m->action = 1;
    m->unk_168 = 7;
    arg = D_800AA248.cur_obj->arg.w;
    D_800AA248.cur_obj->unk_48 = *arg++;
    D_800AA248.cur_obj->script_pc = *arg;
}

void func_8004CC5C(void) {
    Monster *m = D_800AA248.cur_obj->owner.monster;
    s32 *arg;

    m->action = 1;
    m->unk_168 = 3;
    arg = D_800AA248.cur_obj->arg.w;
    D_800AA248.cur_obj->unk_48 = *arg++;
    D_800AA248.cur_obj->script_pc = *arg;
}

void func_8004CCAC(void) {
    Monster *m = D_800AA248.cur_obj->owner.monster;
    u16 side;

    switch (m->unk_05C) {
    case 0x4E:
        m->action = 2;
        return;
    case 0x4D:
        m->action = 0;
        return;
    case 8:
    case 0x14:
    case 0x15:
    case 0x18:
        side = m->unk_1B0;
        if (side != 0 && side != 3) {
            m->action = 6;
            return;
        }
        m->action = 0;
        return;
    default:
        m->action = m->unk_05C;
        return;
    }
}

void func_8004CD58(void) {
    Monster *m = D_800AA248.cur_obj->owner.monster;
    u16 side = m->unk_1B0;

    if (side == 0 || side == 3) {
        m->action = 0;
        return;
    }
    m->action = 6;
}

void func_8004CD94(void) {
    D_800AA248.cur_obj->owner.monster->action = 6;
}

void func_8004CDB0(void) {
    Monster *m = D_800AA248.cur_obj->owner.monster;
    s32 vel;

    vel = 0xFFFF0000;
    if (m->unk_1C4.s.hi < 0xC9) {
        vel = 0x10000;
    }
    D_800AA248.cur_obj->vel_x.w = vel;
    m->unk_1CC = 1;
}

void func_8004CDEC(void) {
    Monster *m = D_800AA248.cur_obj->owner.monster;
    s16 x;

    m->unk_13E = 0x1A4;
    m->action = 0;
    D_800AA248.cur_obj->pos_y.s.hi = 0xE1;
    D_800AA248.cur_obj->pos_x.s.hi &= D_801D8866;
    if (D_801D37BC == 0 && D_801FA98C != 0) {
        x = D_800AA248.cur_obj->pos_x.s.hi;
        if (x >= D_801FA98C && D_801FA990 >= x) {
            m->action = 0x35;
        }
    }
}

void func_8004CE8C(void) {
    if (D_800AA248.cur_obj->owner.monster->unk_0CC != 0) {
        D_800AA248.cur_obj->script_pc = *D_800AA248.cur_obj->arg.w;
    }
}

void func_8004CECC(void) {
    u16 cc = D_800AA248.cur_obj->owner.monster->unk_0CC;

    if (cc != 0 && cc != 5) {
        D_800AA248.cur_obj->script_pc = *D_800AA248.cur_obj->arg.w;
    }
}

void func_8004CF14(void) {
    if ((u32) (D_800AA248.cur_obj->owner.monster->unk_0CC - 4) < 3) {
        D_800AA248.cur_obj->script_pc = *D_800AA248.cur_obj->arg.w;
    }
}

void func_8004CF5C(void) {
    u16 cc = D_800AA248.cur_obj->owner.monster->unk_0CC;
    GameObject *obj;

    if (cc != 0) {
        if (cc == 1 || cc == 8 || cc == 2) {
            obj = D_800AA248.cur_obj;
            obj->script_pc = *obj->arg.w;
        }
    }
}

void func_8004CFC0(void) {
    func_8001E4B0(D_800AA248.cur_obj);
}

void func_8004CFE8(void) {
    GameObject *saved = D_800AA248.cur_obj;
    Monster *m;
    u16 side;
    u16 ea;
    Building *b;
    s32 r;
    s32 hit;
    u16 sp10;

    if (D_800AA2DC == 0 || !(D_8007BD78.flags & 0x40)) {
        m = saved->owner.monster;
        side = m->unk_1B0;
        if (side != 0 && side != 3) {
            ea = m->unk_0EA;
            if ((u32) (ea - 3) >= 2 && ea != side) {
                b = func_80054728(m->unk_1B2);
                if (b != NULL) {
                    m->unk_0FA = m->pos.s.lo;
                    m->unk_0FC = m->pos.s.hi;
                    if (b->unk_058 != 0) {
                        func_8002CFAC(m, b);
                    } else {
                        r = func_8004D150(&sp10, m, (s32) b);
                        if (m->unk_1BC == 0) {
                            hit = func_8002CD24(sp10, m, r);
                            if (hit != 0) {
                                func_8004C064((Ai *) hit, m);
                                m->unk_18A = 1;
                                D_800AA248.cur_obj = saved;
                                return;
                            }
                        } else {
                            func_8002CE74(sp10, m, r);
                        }
                        b->unk_032 = m->id;
                    }
                    m->unk_18A = 1;
                    func_8005404C(m);
                }
            }
        }
        D_800AA248.cur_obj = saved;
    }
}

s32 func_8004D150(u16 *side, Monster *m, s32 bld) {
    s32 part;
    s16 s;

    part = bld + 0x98;
    part += m->unk_1B4 * 0x54;
    s = 2;
    if (m->unk_1B0 == 1) {
        s = 1;
    }
    *side = s;
    return part;
}

void func_8004D194(void) {
    GameObject *saved = D_800AA248.cur_obj;
    Monster *m;
    Building *b;
    s16 sp10;

    if (D_800AA2DC == 0 || !(D_8007BD78.flags & 0x40)) {
        m = saved->owner.monster;
        b = func_80054728(m->unk_1B2);
        if (b != NULL) {
            if (m->unk_1B0 != 3) {
                m->unk_0FA = m->pos.s.lo;
                m->unk_0FC = m->pos.s.hi;
                if (b->unk_058 != 0) {
                    func_8002CFAC(m, b);
                } else {
                    func_8002D5B8(m, func_8004D264(&sp10, m, (s32) b));
                }
            }
        }
        D_800AA248.cur_obj = saved;
    }
}

#ifdef NON_MATCHING
/* 95%: the registers of floor - 1 and its masked copy */
s32 func_8004D264(s16 *side, Monster *m, s32 bld) {
    u16 floor;
    s32 part;
    s32 n;
    u16 idx;
    s16 s;

    floor = m->unk_1B4;
    part = bld + 0x98;
    if (floor != 0) {
        n = floor - 1;
        if ((u16) n != 0) {
            idx = n;
            if (m->unk_1BC != 0) {
                idx = n + 1;
            }
            part += idx * 0x54;
        }
    }
    s = 2;
    if (m->unk_1B0 == 1) {
        s = 1;
    }
    *side = s;
    return part;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004C064", func_8004D264);
#endif

void func_8004D2D4(void) {
    D_800AA248.cur_obj->owner.monster->action = 6;
}

void func_8004D2F0(void) {
    Monster *m = D_800AA248.cur_obj->owner.monster;
    s32 speed;
    s32 d;

    if (m->unk_168 != 3) {
        speed = m->unk_100;
        d = 0xFFFA0000;
        if (speed > 0) {
            d = 0xFFFE0000;
        }
        D_800AA248.cur_obj->vel_x.w += d;
        if (speed >= -0x8000) {
            m->unk_100 = -0x8000;
        }
    } else {
        speed = m->unk_100;
        d = 0x60000;
        if (speed < 0) {
            d = 0x20000;
        }
        D_800AA248.cur_obj->vel_x.w += d;
        if (speed <= 0x8000) {
            m->unk_100 = 0x8000;
        }
    }
}

void func_8004D38C(Monster *m) {
    Ai *p;
    s32 vel;
    GameObject *o;

    if (func_8004D6F8(m, &p) == 1 && p->action != 0x4E) {
        p->action = 0xF2;
        vel = 0xFFFB8000;
        if (D_800AA248.cur_obj->flags & 0x10) {
            vel = 0x48000;
        }
        o = p->obj;
        o->vel_y.w = 0xFFFA8000;
        o->vel_x.w = vel;
        o->unk_88 = 0x4000;
        if (D_800AA2DC != 0 && func_8005F208(D_800AA2DC, vel) == 3) {
            D_8007BD78.unk_08[D_801FA8A0[m->id - 1] - 1] += 1;
            D_8007BD78.flags |= 0x20;
        }
    }
}

void func_8004D488(Monster *m) {
    Ai *p;

    if (func_8004D530(m, &p) == 1) {
        p->action = 0x4E;
        p->unk_0C = 0;
        if (D_800AA2DC != 0 && func_8005F208(D_800AA2DC) == 3) {
            D_8007BD78.unk_08[D_801FA8A0[m->id - 1] - 1] += 3;
            D_8007BD78.flags |= 0x20;
        }
    }
}

u16 func_8004D530(Monster *m, Ai **out) {
    Ai *p;
    u16 n;
    u16 kind;

    n = D_801D870C;
    p = D_801D85C8;
    if (n != 0) {
        do {
            kind = p->action;
            if (kind == 0x1E || (u32) (kind - 0x46) < 8) {
                if (func_8004D5D4(p)) {
                    *out = p;
                    return 1;
                }
            }
            p++;
        } while (--n != 0);
    }
    *out = NULL;
    return 0;
}

u16 func_8004D5D4(Ai *p) {
    s16 x = D_800AA248.cur_obj->pos_x.s.hi;
    s16 px = p->obj->pos_x.s.hi;

    if (x + 0x14 < px || px < x - 0x14) {
        return 0;
    }
    return 1;
}

void func_8004D614(void) {
    Monster *m = D_800AA248.cur_obj->owner.monster;
    Ai *p;
    s32 push;
    u16 kind;
    u16 prev;

    if (func_8004D6F8(m, &p) == 1) {
        func_8005E0E8(m);
        push = 0x1E;
        if (m->unk_1AC != 0) {
            push = 0x5A;
        }
        func_80054374(push, m);
        m->unk_126 = 0;
        kind = 0xF0;
        if (p->action >= 0x1E) {
            kind = 0xF5;
        }
        func_80053D68(0x30000, m);
        p->action = kind;
        prev = m->unk_05C;
        if (prev != 2 && prev != 0x4E) {
            m->action = 8;
        }
        m->unk_18A = 1;
        D_800AA2C0 = 1;
        return;
    }
    D_800AA248.unk_78 = 0;
}

#ifdef NON_MATCHING
/* 68%: the hit-box test against the projectile's frame; the loop keeps two pointers (record and record + 0x36) as givs */
u16 func_8004D6F8(Monster *m, Ai **out) {
    u16 n;
    Ai *p;
    GameObject *o;
    SpriteFrame *f;
    s16 x;
    s32 left;
    s32 right;
    s32 top;

    n = D_801D870C;
    p = D_801D85C8;
    if (n != 0) {
        do {
            if ((u32) (p->action - 9) < 0x5C && p->unk_34.u.hi == 0) {
                o = p->obj;
                x = o->pos_x.s.hi;
                f = o->frame;
                if (x < D_801F9AC8.s.hi && x < D_801F9AC8.s.hi - 0x50) {
                    x += (D_801D8864.w + 1) >> 16;
                }
                if (o->flags & 0x10) {
                    right = x + f->origin.u.lo;
                    left = right - f->size.u.lo;
                } else {
                    left = x - f->origin.u.lo;
                    right = f->size.u.lo + left;
                }
                top = o->pos_y.s.hi - f->origin.u.hi;
                if (left < m->unk_11C && (s16) m->unk_118 < (s16) right && (s16) top < (s16) m->unk_11E &&
                    (s16) m->unk_11A < (s16) (top + f->size.u.hi)) {
                    m->unk_18A = 1;
                    *out = p;
                    return 1;
                }
            }
            p++;
        } while (--n != 0);
    }
    *out = NULL;
    return 0;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004C064", func_8004D6F8);
#endif

void func_8004D860(void) {
    Monster *m = D_800AA248.cur_obj->owner.monster;

    if (m->unk_18E == 0) {
        if (m->unk_126 == 0x19) {
            m->action = 0x4B;
            func_80053D68(0x440000, m);
            return;
        }
        if (m->action == 0x45) {
            return;
        }
    }
    switch (m->unk_126) {
    case 0:
        m->action = 0x18;
        break;
    case 1:
        m->action = 0x14;
        break;
    case 0xC:
        m->action = 0x49;
        return;
    case 0xB:
        m->action = 0x65;
        return;
    default:
        m->action = 0x15;
        break;
    }
    func_8001EB10(3, 0);
}

void func_8004D948(void) {
    func_8001F7CC(0xE6, 0x54);
}

void func_8004D96C(void) {
    D_800AA248.cur_obj->unk_80 = 0x1003;
}

void func_8004D980(GameObject *obj, Monster *m, Monster *other) {
    s32 vel;

    m->unk_18A = 1;
    other->unk_1CC = 4;
    obj->pos_x.s.hi = 0x500;
    obj->pos_y.s.hi = 0x500;
    func_800634D4(other, 6);
    func_80053D68(0xE0000, m);
    vel = m->unk_010.w + 0x90000;
    m->unk_010.w = vel;
    if (vel > 0x440000) {
        m->unk_010.w = 0x440000;
    }
    other->unk_0E4 = m->id;
    m->unk_126 = 0;
    m->action = 0x4A;
    D_800AA248.unk_78 = 1;
}

void func_8004DA30(GameObject *obj, Monster *m, Monster *other) {
    func_8001F724(0x55);
    other->unk_1CC = 4;
    obj->pos_x.s.hi = 0x500;
    obj->pos_y.s.hi = 0x500;
    func_800634D4(other, 6);
    func_80053D68(0xE0000, m);
    other->unk_0E4 = m->id;

    D_800AA248.unk_78 = 1;
}

void func_8004DAB0(GameObject *obj, Monster *m, Monster *other) {
    func_8004DBB0(m, other);
}

void func_8004DAD4(Monster *m, Monster *other) {
    other->action = 0xF;
    func_800634D4(other, 5);
    func_8004FC00(1, m);
    func_8005417C(m);
    D_800AA2C0 = 1;
}

void func_8004DB28(GameObject *obj, Monster *m, Monster *other) {
    s16 action;

    other->unk_0E4 = m->id;
    action = 0x2E;
    if (D_800AA248.cur_obj->pos_y.s.hi < other->obj->pos_y.s.hi) {
        action = 0x2D;
    }
    other->action = action;
    func_800634D4(other, 5);
    func_8004FC00(1, m);
    func_800540D0(m);
    D_800AA248.unk_78 = 1;
}

void func_8004DBB0(Monster *m, Monster *other) {
    other->action = 0x23;
    other->unk_1B0 = 0;
    func_800634D4(other, 5);
    func_8004FC00(1, m);
    func_8005417C(m);
    D_800AA2C0 = 1;
}

#ifdef NON_MATCHING
/* 78%: the order of the stores and of the call's constant argument */
void func_8004DC08(Monster *m, Monster *other) {
    other->unk_132 = 0;
    other->unk_0E4 = 0;
    other->unk_0E6 = 0;
    other->unk_0EE = 0x12C;
    other->action = 0x22;
    other->unk_1B0 = 0;
    other->unk_0E4 = m->id;
    func_800634D4(other, 5);
    func_8004FC00(1, m);
    func_8005417C(m);
    D_800AA2C0 = 1;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004C064", func_8004DC08);
#endif

#ifdef NON_MATCHING
/* 79%: the order of the stores around the random call */
void func_8004DC7C(Monster *m, Monster *other) {
    s16 action;

    action = 0x1C;
    if (func_8001EB10(0xF, 0) & 1) {
        action = 0x39;
    }
    other->action = action;
    other->unk_0E4 = m->id;
    func_800634D4(other, 5);
    func_8004FC00(1, m);
    D_800AA2C0 = 1;
    func_800540D0(m);
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004C064", func_8004DC7C);
#endif

void func_8004DCFC(GameObject *obj, Monster *m, Monster *other) {
    s32 vel;

    other->action = 0x1D;
    other->unk_100 = 0;
    other->unk_1B0 = 0;
    vel = 0xFFFE0000;
    if (obj->flags & 0x10) {
        vel = 0x20000;
    }
    obj->vel_x.w = vel;
    func_800634D4(other, 5);
    func_8004FC00(1, m);
    func_8005417C(m);
    D_800AA2C0 = 1;
}

void func_8004DD78(GameObject *obj, Monster *m, Monster *other) {
    s32 vel;

    other->unk_0E4 = m->id;
    other->action = 0xA;
    other->unk_1B0 = 0;
    other->unk_100 = 0;
    vel = 0xFFFC0000;
    if (obj->flags & 0x10) {
        vel = 0x40000;
    }
    obj->vel_x.w = vel;
    func_800634D4(other, 5);
    func_8004FC00(1, m);
    D_800AA2C0 = 1;
    func_8005417C(m);
}

#ifdef NON_MATCHING
/* 98%: the other monster's object is reread after the action test in the original (one register less) */
void func_8004DDFC(void) {
    Monster *m = D_800AA248.cur_obj->owner.monster;
    u16 id = m->id;
    Monster *other;
    GameObject *o;
    u16 i;
    s16 hit;
    u16 side;
    u16 kind;

    i = 7;
    do {
        if (id != i) {
            other = &D_801E0B78[i];
            if (other->unk_058 & 1) {
                o = other->obj;
                if (!(o->unk_6C & 0x80) && other->unk_0DC != 0) {
                    hit = func_80053970(m, other);
                    if (hit != 0) {
                        if (other->action == 0x37) {
                            if (D_8007A68A != 0) {
                                func_8004D980(o, m, other);
                                return;
                            }
                            continue;
                        }
                        m->unk_18A = 1;
                        if (other->action == 0x4D) {
                            if (m->unk_18E != 0 || other->unk_18E != 0 || m->unk_1B0 != 0 || other->unk_1B0 != 0 ||
                                other->obj->pos_y.s.hi < 0xE1 ||
                                (other->obj->flags & 0x10) != (D_800AA248.cur_obj->flags & 0x10)) {
                                other->action = 0x4F;
                                D_800AA248.unk_78 = 1;
                                return;
                            }
                            func_8004DAB0(other->obj, m, other);
                            return;
                        }
                        func_800634D4(other, 5);
                        if (D_8007A68A != 0) {
                            func_80053C50(0x20000, other);
                        }
                        other->unk_0EE = 0x78;
                        other->unk_180 = m;
                        if (other->action == 0x2C) {
                            func_8004DAD4(m, other);
                            return;
                        }
                        side = other->unk_1B0;
                        if ((u32) (side - 1) < 2) {
                            func_8004DB28(o, m, other);
                            return;
                        }
                        o = other->obj;
                        if (side == 3 || o->pos_y.s.hi >= 0xE1) {
                            if ((D_800AA248.cur_obj->flags & 0x10) == (o->flags & 0x10)) {
                                if (side != 0) {
                                    func_8004DBB0(m, other);
                                    return;
                                }
                                if (other->unk_0CC != 5 || m->unk_18E != 0 || other->unk_18E != 0 || m->unk_1B0 != 0) {
                                    if (other->unk_132 == 0) {
                                        other->unk_132 = 0xB4;
                                        other->unk_0E4 = 0;
                                        other->unk_0E6 = 0;
                                    }
                                    if (m->unk_142 == 0) {
                                        kind = other->unk_0E4;
                                        if (kind == 0) {
                                            hit = 0x3A;
                                            func_800540D0(m);
                                        } else if (other->unk_0E6 == 0) {
                                            other->unk_0E6 = kind;
                                            hit = 0xB;
                                            func_8005417C(m);
                                        }
                                        other->action = hit;
                                        other->unk_0E4 = m->id;
                                        func_800634D4(other, 5);
                                        func_8004FC00(1, m);
                                        D_800AA248.unk_78 = 1;
                                        return;
                                    }
                                    func_8004DC08(m, other);
                                    return;
                                }
                                func_8004DAB0(other->obj, m, other);
                                return;
                            }
                            if (other->unk_132 == 0) {
                                other->unk_132 = 0xB4;
                                other->unk_0E4 = 0;
                                other->unk_0E6 = 0;
                            }
                            if (m->unk_142 == 0) {
                                kind = other->unk_0E4;
                                if (kind == 0) {
                                    func_8004DC7C(m, other);
                                    return;
                                }
                                if (other->unk_0E6 == 0) {
                                    other->unk_0E6 = kind;
                                    func_8004DC7C(m, other);
                                    return;
                                }
                            }
                            other->unk_132 = 0;
                            other->unk_0E4 = 0;
                            other->unk_0E6 = 0;
                            if (other->unk_1B0 == 3) {
                                func_8004DCFC(o, m, other);
                                return;
                            }
                            func_8004DD78(o, m, other);
                            return;
                        }
                        func_8004DAD4(m, other);
                    }
                }
            }
        }
    } while (--i != 0);
    D_800AA2C0 = 0;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004C064", func_8004DDFC);
#endif

void func_8004E264(void) {
    if (D_800AA248.cur_obj->pos_y.s.hi < 0xE1) {
        D_800AA248.cur_obj->script_pc = *D_800AA248.cur_obj->arg.w;
    }
}

void func_8004E2A0(void) {
    GameObject *obj = D_800AA268.p;
    s32 *arg = obj->arg.w;

    obj->vel_y.w = *arg++;
    obj->owner.monster->unk_104 = *arg;
}

void func_8004E2D0(void) {
    Monster *m = D_800AA248.cur_obj->owner.monster;

    m->unk_100 = 0;
    m->unk_104 = 0;
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
}

void func_8004E308(void) {
    Monster *m;
    s32 speed;

    D_800AA248.cur_obj->vel_x.w = 0;
    m = D_800AA248.cur_obj->owner.monster;
    if (m->unk_1D8 == 0) {
        speed = 0xFFFF7000;
        if (m->unk_168 == 7) {
            speed = 0x9000;
        }
        m->unk_100 = speed;
        D_800AA248.cur_obj->vel_y.w = 0xFFFD0000;
        m->unk_104 = 0x6000;
        return;
    }
    speed = 0xFFFF0000;
    if (m->unk_168 == 7) {
        speed = 0x10000;
    }
    m->unk_100 = speed;
    D_800AA248.cur_obj->vel_y.w = 0xFFFA0000;
    m->unk_104 = 0x6000;
    m->unk_1D8 = 0;
}

void func_8004E3A4(void) {
    Monster *m;
    s32 speed;

    D_800AA248.cur_obj->vel_x.w = 0;
    m = D_800AA248.cur_obj->owner.monster;
    speed = 0xC000;
    if (m->unk_168 == 7) {
        speed = 0xFFFF4000;
    }
    m->unk_100 = speed;
    D_800AA248.cur_obj->vel_y.w = 0xFFFB0000;
    m->unk_104 = 0x4000;
    m->action = 2;
}

void func_8004E404(void) {
    Monster *m;
    s32 speed;

    D_800AA248.cur_obj->vel_x.w = 0;
    m = D_800AA248.cur_obj->owner.monster;
    if (m->unk_1D8 == 0) {
        speed = 0x8000;
        if (m->unk_168 == 7) {
            speed = -0x8000;
        }
        m->unk_100 = speed;
        D_800AA248.cur_obj->vel_y.w = 0xFFFD0000;
        m->unk_104 = 0x6000;
        return;
    }
    speed = 0x10000;
    if (m->unk_168 == 7) {
        speed = 0xFFFF0000;
    }
    m->unk_100 = speed;
    D_800AA248.cur_obj->vel_y.w = 0xFFFA0000;
    m->unk_104 = 0x6000;
    m->unk_1D8 = 0;
}

void func_8004E49C(void) {
    Monster *m;
    s32 speed;

    D_800AA248.cur_obj->vel_x.w = 0;
    m = D_800AA248.cur_obj->owner.monster;
    speed = 0xA000;
    if (m->unk_168 == 7) {
        speed = 0xFFFF6000;
    }
    m->unk_100 = speed;
}

void func_8004E4E0(void) {
    Monster *m;
    s32 speed;

    D_800AA248.cur_obj->vel_x.w = 0;
    m = D_800AA248.cur_obj->owner.monster;
    speed = 0xFFFF6000;
    if (m->unk_168 == 7) {
        speed = 0xA000;
    }
    m->unk_100 = speed;
}

void func_8004E520(void) {
    Monster *m;
    s32 speed;

    D_800AA248.cur_obj->vel_x.w = 0;
    m = D_800AA248.cur_obj->owner.monster;
    speed = 0x4000;
    if (m->unk_168 == 7) {
        speed = -0x4000;
    }
    m->unk_100 = speed;
    D_800AA248.cur_obj->vel_y.w = 0xFFFD0000;
    m->unk_104 = 0x6000;
}
