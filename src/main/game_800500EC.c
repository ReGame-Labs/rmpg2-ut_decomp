/* A file of the game's code, named after its first function until its contents are understood.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "game.h"
#include "game_800500EC.h"

#ifdef NON_MATCHING
/* 83.5%: the original copies e to a3 and builds &D_800AA248 in a0 (the clamped action in v1); here e stays in a0 and the action takes a3 */
void func_800500EC(Monster *e, GameObject *obj) {
    s16 x;
    s16 half;
    s16 state;

    half = (s16) obj->unk_1C.u.lo >> 1;
    x = obj->pos_x.s.hi;
    if (obj->flags & 0x10) {
        x -= half;
    } else {
        x += half;
    }
    e->front_x = x;
    state = e->action;
    if (state >= 0x68) {
        state = 0x67;
    }
    D_800AA248.unk_0C = x;
    D_800AA248.action = state;
    D_800AA248.cur_obj = obj;
    D_8007F8FC[state](e);
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800500EC);
#endif

void func_80050190(Monster *e) {
    if (!(e->buttons & 4)) {
        e->action = 0;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800501B0);

void func_800504B4(Monster *e) {
    D_800AA248.unk_24 = e->dir;
    D_800AA248.cur_obj->vel_y.w = 0;
    D_800AA248.cur_obj->vel_x.w = 0;
    e->unk_100 = 0;
    e->unk_104 = 0;
    if (e->unk_168 == 7) {
        func_800553B0(e, e);
        return;
    }
    func_800556AC(e, e);
}

void func_80050520(Monster *e) {
    D_800AA248.cur_obj->vel_x.w = 0;
    e->unk_104 = 0;
    D_800AA248.cur_obj->vel_y.w = e->unk_1C0 <= 0x6FFFFF ? 0x20000 : 0xC0000;
    if (e->unk_168 == 7) {
        func_80054E1C(e);
    } else {
        func_80055014(e);
    }
}

void func_8005059C(Monster *e) {
    s32 kind;

    D_800AA248.unk_24 = e->dir;
    D_800AA248.cur_obj->vel_y.w = 0;
    D_800AA248.cur_obj->vel_x.w = 0;
    e->unk_104 = 0;
    e->unk_100 = 0;
    if (e->unk_168 == 7) {
        kind = e->dir;
        if (kind < 5) {
            if (kind >= 2) {
                e->action = 0xC;
            }
        }
    } else {
        kind = e->dir;
        if (kind < 9) {
            if (kind >= 6) {
                e->action = 0xC;
            }
        }
    }
}

void func_8005061C(void) {
}

void func_80050624(Monster *e) {
    D_800AA268.p->vel_x.w = 0;
    e->unk_104 = 0;
    if (e->unk_168 == 7) {
        func_80054F18(e);
    } else {
        func_80055110(e);
    }
}

void func_80050670(Monster *e) {
    D_800AA268.p->vel_x.w = 0;
    e->unk_104 = 0;
    if (e->unk_168 == 7) {
        func_80054E1C(e);
    } else {
        func_80055014(e);
    }
}

void func_800506BC(Monster *e) {
    Building *obj;
    s16 x;

    obj = func_80054728(e->climb_building);
    if (obj != NULL) {
        if (e->climb_side == 2) {
            x = obj->unk_00E;
            if (D_800AA268.p->flags & 0x10) {
                x += 0x18;
            } else {
                x -= 0x18;
            }
            D_800AA268.p->pos_x.s.hi = x;
        } else if (e->climb_side == 1) {
            x = obj->unk_004;
            if (D_800AA268.p->flags & 0x10) {
                x += 0x18;
            } else {
                x -= 0x18;
            }
            D_800AA268.p->pos_x.s.hi = x;
        }
        func_800531C0(e);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80050774);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_8005086C);

void func_800509EC(Monster *e) {
    func_80050E58(e);
    func_800531C0(e);
    if ((s16) e->pos.u.hi != 0 && e->unk_0DE != 0) {
        if (e->unk_18A == 0) {
            func_80036A20(e);
            if (e->unk_18A == 0) {
                func_8003BAB0(e);
                if (e->unk_18A == 0) {
                    func_8004F65C();
                    if (e->unk_18A == 0) {
                        func_8004D614();
                        if (e->unk_18A == 0) {
                            func_8003F50C(e);
                            if (e->unk_18A == 0) {
                                func_8004718C(e);
                                if (e->unk_18A == 0) {
                                    func_8004ECDC();
                                    if (e->unk_18A == 0) {
                                        func_8004ED8C();
                                        if (e->unk_18A == 0) {
                                            func_8004DDFC();
                                            if (e->unk_18A == 0) {
                                                func_8004EFE8();
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if (e->unk_18A != 0) {
            func_800634D4(e, 1);
        }
    } else if (e->unk_18A != 0) {
        func_800634D4(e, 1);
    }
}

void func_80050B40(Monster *e) {
    e->action = 0x4C;
    func_80050BBC();
    if (D_800AA268.p->vel_x.w == 0 && D_800AA268.p->vel_y.w == 0 && e->unk_100 == 0 && e->unk_104 == 0) {
        e->action = 0;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80050BBC);

void func_80050DAC(Monster *e) {
    func_80050E58(e);
    func_800531C0(e);
}

void func_80050DD8(Monster *e) {
    u16 n;

    D_800AA248.unk_24 = e->dir;
    if (e->dir == 0) {
        func_800531C0(e);
        return;
    }
    n = e->climb_side;
    D_800AA248.unk_08 = n;
    if (n == 0 || e->climb_side == 3) {
        e->action = 0;
        func_800501B0(e);
    } else {
        e->action = 6;
        func_8005086C(e);
    }
}

void func_80050E58(Monster *e) {
    u16 n;

    n = e->climb_side;
    D_800AA250 = n;
    if (n != 0) {
        func_80054A18();
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80050E88);

void func_800510BC(Monster *a, Monster *b) {
    GameObject *body;
    u16 flags;

    body = b->obj;
    flags = body->flags;
    if ((flags & 0x10) == (a->obj->flags & 0x10)) {
        body->flags = flags ^ 0x10;
    }
}

void func_800510E8(Monster *e) {
    func_80050E58(e);
    if (e->unk_104 == 0 || (D_800AA268.p->vel_y.w >= 0 && D_800AA268.p->pos_y.s.hi >= 0xE1)) {
        func_800531C0(e);
    }
}

void func_80051150(Monster *e, Monster *e2) {
    GameObject *body;
    s32 v;

    body = e2->obj;
    e2->action = 0xF;
    v = -0x20000;
    if (body->flags & 0x10) {
        v = 0x20000;
    }
    body->vel_x.w = v;
    func_8004FC00(1, e);
    func_8005417C(e);
    func_800510E8(e);
}

void func_800511B4(Monster *e, Monster *e2) {
    e2->action = 0x39;
    func_8004FC00(1, e);
    func_8005417C(e);
    func_800510E8(e);
}

void func_800511F8(Monster *e, Monster *e2) {
    e2->action = 0x22;
    func_800634D4(e2, 5);
    func_8004FC00(1, e);
    func_8005417C(e);
    func_800510E8(e);
}

void func_80051248(Monster *e, Monster *e2) {
    GameObject *b;
    s32 vx;

    func_800510BC(e, e2);
    e2->action = 0xA;
    func_8004FC00(1, e);
    func_8005417C(e);
    e2->obj->vel_y.w = 0xFFFA0000;
    b = e2->obj;
    vx = 0xFFFE0000;
    if (b->flags & 0x10) {
        vx = 0x20000;
    }
    b->vel_x.w = vx;
    func_800510E8(e);
}

void func_800512CC(Monster *e, Monster *e2) {
    GameObject *body;
    s32 v;

    body = e2->obj;
    e2->action = 0xA;
    v = -0x40000;
    if (body->flags & 0x10) {
        v = 0x40000;
    }
    body->vel_x.w = v;
    func_8004FC00(1, e);
    func_8005417C(e);
    func_800510E8(e);
}

void func_80051330(Monster *e, Monster *other) {
    u16 id;

    if ((u16) e->unk_164 == 0) {
        id = e->id;
        e->unk_18A = 1;
        other->action = 0x41;
        other->unk_0E4 = id;
        e->action = 0x42;
        e->unk_18C = 0;
        other->unk_18C = 0;
        other->unk_12A = e->id;
        e->unk_12A = other->id;
        func_8004F7F4(other->obj, e, other, e->obj);
        func_800510E8(e);
    } else {
        if (D_8007A68A != 0) {
            func_80053C50(0x30000, other);
        }
        func_800511F8(e, other);
    }
}

void func_800513EC(Monster *e, Monster *e2) {
    e2->action = 0x4F;
    func_800510E8(e);
}

void func_80051410(Monster *e, Monster *e2) {
    GameObject *b;

    b = e2->obj;
    if ((b->flags & 0x10) == (D_800AA248.cur_obj->flags & 0x10)) {
        func_80051330(e, e2);
        return;
    }
    if (D_800AA248.unk_08 != 1 || e->action != 4 || e->unk_104 != 0 || b->pos_y.s.hi < 0xE1) {
        func_800513EC(e, e2);
        return;
    }
    func_8004F470(e, e2);
    func_800510E8(e);
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800514CC);

void func_800517C0(Monster *e) {
    e->unk_104 = 0x4000;
    e->climb_side = 0;
    e->climb_building = 0;
    if (D_800AA268.p->vel_y.w > 0) {
        func_8005189C(e);
    }
}

void func_8005180C(Monster *e) {
    if (e->unk_16C != NULL) {
        func_8001E4B0(e->unk_16C);
        e->unk_16C = NULL;
    }
    e->climb_side = 0;
    e->climb_building = 0;
    if (e->unk_18E != 0) {
        e->unk_104 = 0xC000;
    } else {
        e->unk_104 = 0x4000;
    }
    if (D_800AA268.p->vel_y.w > 0) {
        func_8005189C(e);
    } else {
        func_80051A08(e);
    }
}

void func_8005189C(Monster *e) {
    if (D_800AA268.p->pos_y.s.hi < 0xE1) {
        func_8005199C(e);
        return;
    }
    D_800AA268.p->pos_y.s.hi = 0xE1;
    if (D_801D8740 < 2 || D_801F9ACC.w == 0 || D_801F9ACC.w > 0xFFF00000U) {
        if ((u16) func_80031714(e) == 1) {
            e->action = 0x35;
            D_800AA268.p->pos_y.s.hi = 0xED;
        } else {
            if (e->action != 0x17) {
                func_80029118(5, 8);
                e->action = 0xE;
            } else {
                func_80029118(5, 0xC);
                e->action = 0x66;
            }
            func_8004EFAC();
        }
        func_800531C0(e);
        return;
    }
    func_80052798(e);
}

void func_8005199C(Monster *e) {
    func_800376D8(e);
    if (e->action == 0x53) {
        func_800531C0(e);
    } else if ((u16)(D_800AA268.p->pos_y.s.hi - 0xC8) < 0x11) {
        func_8005421C(e);
    }
}

void func_80051A08(Monster *e) {
    if (D_800AA268.p->vel_y.w <= 0 && D_800AA268.p->pos_y.w <= (s32) D_801F9ACC.w) {
        D_800AA268.p->vel_y.w = 0;
    }
}

void func_80051A48(Monster *e) {
    if (!(e->buttons & 4)) {
        e->action = 2;
    }
    func_80051C9C(e);
}

void func_80051A80(Monster *e) {
    if (D_800AA248.cur_obj->vel_y.w >= 0) {
        if ((u16) func_80031714(e) == 1) {
            e->action = 0x35;
            D_800AA248.cur_obj->pos_y.s.hi = 0xED;
            func_800531C0(e);
        } else {
            D_800AA248.action = e->action;
            if (e->action != 0x4E) {
                e->action = 0x19;
                D_800AA248.action = 0x19;
                func_800531C0(e);
            } else {
                e->action = 0x4D;
                D_800AA248.action = 0x4D;
                func_800531C0(e);
            }
        }
    }
}

void func_80051B38(Monster *e) {
    s32 vy;

    vy = D_800AA248.cur_obj->vel_y.w;
    if (vy > 0) {
        if (e->health.w != 0) {
            if (D_800AA248.action == 0x4E || (func_80056598(), D_800AA248.action == 2)) {
                if (D_800AA248.cur_obj->pos_y.s.hi < 0xE1) {
                    func_8005199C(e);
                    return;
                }
                D_800AA248.cur_obj->pos_y.s.hi = 0xE1;
                func_800376D8(e);
                if (e->action != 0x53) {
                    func_8003EF64(e);
                    func_80046F68(e);
                    func_8004D488(e);
                    if (D_801D8740 < 2 || D_801F9ACC.w == 0 || D_801F9ACC.w > 0xFFE00000) {
                        func_80051A80(e);
                        return;
                    }
                    func_80052798(e);
                    return;
                }
                goto state_done;
            }
            if (D_800AA248.action != 0x2C) {
            state_done:
                func_800531C0(e);
            }
        }
    } else if (vy != 0 && e->unk_104 == 0) {
        e->unk_104 = 0xA000;
    }
}

void func_80051C9C(Monster *e) {
    GameObject *p;
    GameState *g;

    p = e->unk_16C;
    if (p != NULL) {
        func_8001E4B0(p);
        e->unk_16C = NULL;
    }
    g = &D_800AA248;
    e->climb_side = 0;
    e->climb_building = 0;
    g->unk_24 = e->dir;
    if ((u32) (e->dir - 4) >= 3U) {
        func_80051B38(e);
    } else if (e->unk_168 == 7) {
        func_80056AC8(e);
        g->action = e->action;
        if (e->action == 2 || e->action == 0x4E) {
            func_80051B38(e);
        } else {
            func_800531C0(e);
        }
    } else {
        func_80056840(e);
        if (e->action == 2 || e->action == 0x4E) {
            func_80051B38(e);
        } else {
            func_800531C0(e);
        }
    }
}

void func_80051D8C(Monster *e, Monster *m) {
    GameObject *obj;

    obj = m->obj;
    if ((obj->flags & 0x10) == (D_800AA248.cur_obj->flags & 0x10)) {
        if (D_8007A68A != 0) {
            func_80053C50(0x30000, m);
        }
        func_8004FC00(1, e);
        func_800634D4(m, 5);
    } else if (D_800AA248.unk_08 == 1 || e->action == 4 || e->unk_104 != 0 || obj->pos_y.s.hi < 0xE1) {
        m->action = 0xA;
        func_8005417C(e);
    } else {
        func_8004F470(e, m);
    }
}

void func_80051E80(Monster *e) {
    Monster *m;
    u16 i;

    if (e->pos.s.lo != 0) {
        i = 7;
        do {
            m = &D_801E0B78[i];
            if (m == e || !(m->unk_058 & 1)) {
                continue;
            }
            if (m->unk_0DC == 0 || m->action == 0x37) {
                continue;
            }
            D_800AA248.unk_08 = (u16) func_80053970(e, m);
            if (D_800AA248.unk_08 == 0) {
                continue;
            }
            if (m->action == 0x4D) {
                func_80051D8C(e, m);
                break;
            }
            if (D_8007A68A != 0) {
                func_80053C50(0x30000, m);
            }
            func_800634D4(m, 5);
            func_8004FC00(1, e);
            if (m->climb_side != 0 || m->obj->pos_y.s.hi != 0xE1) {
                m->action = 0xF;
                m->obj->vel_x.w = (m->obj->flags & 0x10) ? 0x20000 : -0x20000;
            } else if ((D_800AA248.cur_obj->flags & 0x10) == (m->obj->flags & 0x10)) {
                m->action = 0x22;
            } else {
                m->action = 0xA;
                m->obj->vel_x.w = (m->obj->flags & 0x10) ? 0x40000 : -0x40000;
            }
            func_8005417C(e);
            break;
        } while (--i != 0);
    }
    if (e->unk_18A == 0) {
        func_80036A20(e);
        if (e->unk_18A == 0) {
            func_8003BAB0(e);
            if (e->unk_18A == 0) {
                func_8004D38C(e);
                if (e->unk_18A == 0) {
                    func_8003F114(e);
                    func_80047028(e);
                }
            }
        }
    }
    if (D_800AA268.p->pos_y.s.hi >= 0xD1 && D_800AA268.p->vel_y.w >= 0) {
        e->action = 2;
        func_80058F78(e);
    }
}

void func_80052100(Monster *e) {
    func_80050E58(e);
    func_800531C0(e);
}

void func_8005212C(Monster *e) {
    if ((s16) e->pos.u.hi == 0 || e->unk_0DE == 0 || e->unk_18A != 0) {
        func_8005222C(e);
        if (e->unk_18A != 0) {
            func_800634D4(e, 1);
        }
        return;
    }
    func_80036A20(e);
    if (e->unk_18A == 0) {
        func_8003BAB0(e);
        if (e->unk_18A == 0) {
            func_8004DDFC();
            if (e->unk_18A != 0) {
                func_800634D4(e, 1);
                return;
            }
            func_8004D614();
            if (e->unk_18A != 0) {
                func_800634D4(e, 1);
                return;
            }
            func_8003F50C(e);
            if (e->unk_18A != 0) {
                func_800634D4(e, 1);
                return;
            }
            func_8004718C(e);
            if (e->unk_18A != 0) {
                func_800634D4(e, 1);
                return;
            }
        }
    }
    func_8005222C(e);
    if (e->unk_18A != 0) {
        func_800634D4(e, 1);
    }
}

void func_8005222C(Monster *e) {
    e->climb_side = 0;
    e->climb_building = 0;
    if (D_800AA268.p->pos_y.s.hi >= 0xE1) {
        D_800AA268.p->pos_y.s.hi = 0xE1;
        if (D_801D8740 < 2 || D_801F9ACC.w == 0 || D_801F9ACC.w > 0xFFF00000) {
            if ((u16) func_80031714(e) == 1) {
                e->action = 0x35;
                D_800AA268.p->pos_y.s.hi = 0xED;
            } else {
                e->action = 0x19;
            }
            func_800531C0(e);
        } else {
            func_80052798(e);
        }
    }
}

void func_800522F8(Monster *e) {
    GameObject *b;

    e->climb_side = 0;
    e->climb_building = 0;
    b = D_800AA268.p;
    if (b->vel_y.w > 0 && b->pos_y.s.hi >= 0xE1) {
        b->pos_y.s.hi = 0xE1;
        if (D_801D8740 < 2 || D_801F9ACC.w == 0 || D_801F9ACC.w > 0xFFF00000) {
            if ((u16) func_80031714(e) == 1) {
                e->action = 0x35;
                D_800AA268.p->pos_y.s.hi = 0xED;
                func_800531C0(e);
            }
        }
    }
}

void func_800523B8(Monster *e) {
    e->climb_side = 0;
    e->climb_building = 0;
    if (D_800AA268.p->pos_y.s.hi >= 0xE1) {
        if (D_801D8740 < 2 || D_801F9ACC.w == 0 || D_801F9ACC.w > 0xFFF00000) {
            if ((u16)func_80031714(e) == 1) {
                func_800524AC(e);
                e->action = 0x35;
                D_800AA268.p->pos_y.s.hi = 0xED;
            }
            func_800531C0(e);
        } else {
            func_800524AC(e);
            func_80052798(e);
        }
    } else if (e->unk_104 == 0) {
        e->unk_104 = 0x4000;
    }
}

void func_800524A4(void) {
}

void func_800524AC(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800524B4);

void func_80052520(Monster *e) {
    GameState *g;
    s32 vx;
    u16 dir;

    vx = 0;
    g = &D_800AA248;
    g->unk_24 = 0;
    if (D_801D3DC2 >= 3) {
        func_80052880(e, g);
        return;
    }
    g->unk_24 = e->dir;
    dir = e->dir;
    if (dir >= 2) {
        if (dir < 5) {
            vx = 0x8000;
        } else if (dir != 5) {
            vx = -0x8000;
        }
    }
    e->unk_100 = vx;
    e->unk_104 = 0x4000;
    e->climb_side = 0;
    e->climb_building = 0;
    if ((u16) (e->dir - 4) < 3) {
        func_80056CCC(e, g);
        if (e->action != 0x2C) {
            func_800531C0(e);
            return;
        }
    }
    if (D_800AA268.p->vel_y.w > 0) {
        func_800526A4(e);
    } else {
        func_80051A08(e);
    }
}

void func_8005262C(Monster *e) {
    s16 state;

    if ((u16) func_80031714(e) == 1) {
        e->action = 0x35;
        D_800AA268.p->pos_y.s.hi = 0xED;
        func_800531C0(e);
        return;
    }
    state = 0x19;
    if (D_801D3DC2 >= 7) {
        state = 0xE;
    }
    e->action = state;
}

void func_800526A4(Monster *e) {
    if (e->health.w != 0) {
        func_80056598();
        if (e->action != 0x2C) {
            func_800531C0(e);
            return;
        }
    }
    if (D_800AA268.p->pos_y.s.hi < 0xE1) {
        func_8005199C(e);
        return;
    }
    D_800AA268.p->pos_y.s.hi = 0xE1;
    func_800376D8(e);
    func_8003EF64(e);
    func_80046F68(e);
    func_8004D488(e);
    if (D_801D8740 < 2 || D_801F9ACC.w == 0 || D_801F9ACC.w > 0xFFE00000) {
        func_8005262C(e);
    } else {
        func_80052798(e);
    }
}

void func_80052798(Monster *e) {
    s32 vy;

    if (func_8005E4E4() & 2) {
        e->unk_100 = 0;
        e->obj->vel_x.w = 0;
        e->action = 0;
        return;
    }
    if (D_801F9914 >= 0x89 || e->health.w <= 0xFFFF) {
        func_80029118(5, 8);
        e->action = 0;
        return;
    }
    e->action = 0x2C;
    func_80029118(5, 8);
    vy = D_800AA268.p->vel_y.w;
    if (vy <= 0x60000) {
        vy = -0x60000;
    } else if (vy > 0xBFFFF) {
        vy = -0xC0000;
    } else {
        vy += 0x10000;
        vy = -vy;
    }
    D_800AA268.p->vel_y.w = vy;
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80052880);

/* 0x8000 when a's player has a lower D_801D3D98 entry than b's, else -0x8000. */
s32 func_80052A0C(Monster *a, Monster *b) {
    s32 dir;
    u8 *slot;
    u8 i;
    s32 *score;
    s32 *p;
    s32 x;

    slot = D_801FA8A0;
    i = slot[a->id - 1];
    score = D_801D3D98;
    dir = -0x8000;
    p = &score[i];
    x = *p;
    p = &score[slot[b->id - 1]]; /* FAKE: one pointer for both scores: the original computes both element addresses into the same register (a1) */
    if (x < *p) {
        dir = 0x8000;
    }
    return dir;
}

s32 func_80052A68(Monster *e) {
    s32 *score;
    s32 dir;

    score = &D_801D3D98[D_801FA8A0[e->id - 1]];
    if (e->unk_100 < 0) {
        dir = 0x8000;
        if (*score > 0x640000) {
            dir = -0x8000;
        }
        return dir;
    }
    dir = (*score < 0x12C0000) ? 0x8000 : -0x8000;
    return dir;
}

void func_80052ADC(Monster *e) {
    u16 state;

    func_80056598();
    state = e->action;
    if (state != 0x2C) {
        func_800531C0(e);
        return;
    }
    if (D_800AA248.cur_obj->pos_y.s.hi < 0xE1) {
        func_8005199C(e);
        return;
    }
    D_800AA248.cur_obj->pos_y.s.hi = 0xE1;
    func_800376D8(e);
    func_8003EF64(e);
    func_80046F68(e);
    func_8004D488(e);
    if (D_801D8740 < 2 || D_801F9ACC.w == 0 || D_801F9ACC.w > 0xFFE80000U) {
        func_8005262C(e);
        return;
    }
    e->action = state;
    func_80029118(5, 8);
    D_800AA248.cur_obj->vel_y.w = 0xFFF10000;
}

void func_80052BE0(Monster *e) {
    s32 vx;
    u16 kind;

    func_80053C50(0x700, e);
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.unk_24 = e->dir;
    kind = e->dir;
    vx = 0;
    if (kind >= 2 && kind != 5) {
        vx = 0xFFFE0000;
        if (kind < 5) {
            vx = 0x20000;
        }
    }
    e->unk_100 = vx;
    if ((u16) func_80031714(e) == 0) {
        e->action = 0x36;
        func_80052E44(e);
    }
}

void func_80052C7C(Monster *e) {
    func_80053C50(0x700, e);
    func_800531C0(e);
}

void func_80052CB0(Monster *e) {
    Monster *other;
    GameObject *b;
    s32 state;

    state = e->unk_1CC;
    e->unk_1C8 = 1;
    if (state != 0) {
        if (state == 1) {
            if (e->buttons & 0x10) {
                other = func_8005D918();
                if (other != NULL) {
                    other->unk_004--;
                    e->unk_004 = 0;
                    e->unk_002 = 0xFF;
                    func_8001F724(0x71);
                    e->health.w = 0x440000;
                    e->unk_1CC = 0;
                    e->action = 0x3B;
                    e->unk_0DC = 0;
                    return;
                }
            }
            if (!(D_800AA268.p->unk_6C & 0x80) && e->unk_0E4 == 0) {
                return;
            }
        }
        e->unk_1CC = 4;
        e->unk_05E = 1;
        b = D_800AA268.p;
        b->pos_y.s.hi = 0x500;
        b->pos_x.s.hi = 0x500;
    }
    func_800531C0(e);
}

void func_80052DA8(Monster *e) {
    func_800531C0(e);
}

void func_80052DC8(Monster *e) {
    func_800531C0(e);
}

void func_80052DE8(Monster *e) {
    e->unk_046 = 1;
    func_800531C0(e);
}

void func_80052E0C(Monster *e) {
    func_800531C0(e);
    if (e->action == 1) {
        e->action = 0;
    }
}

void func_80052E44(Monster *e) {
    func_800531C0(e);
    func_80052E70(e);
}

void func_80052E70(Monster *e) {
    func_8005382C(e->dir);
}

void func_80052E94(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80052E9C);

void func_800531C0(Monster *e) {
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    D_800AA248.cur_obj->unk_84 = 0;
    D_800AA248.cur_obj->unk_84 = 0;
    e->unk_100 = 0;
    e->unk_104 = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80053204);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800535E4);

void func_80053804(s32 unused, Monster *e) {
    /* LOOP_BLOCK class A2: the plain statements give the original's order only with -fno-schedule-insns
     * -fno-schedule-insns2 (sched2 sinks the two zero stores below the constants); a macro's block, likely. */
    LOOP_BLOCK(e->unk_208 = 0; e->unk_210 = 0;);
    e->unk_20C = 0xFFF60000;
    e->unk_214 = 0x4000;
    e->action = 0x58;
    e->unk_200 = 0;
}

void func_8005382C(u16 kind) {
    D_800AA268.p->unk_8C = D_8007BE0C[kind];
}

#ifdef NON_MATCHING
/* 82.4 %: the original keeps the wrapped x in t0 and loads the boxes' y bounds (0x10A, 0x10E, 0x112, 0x116) with lhu, comparing them shifted; here they are loaded signed */
s32 func_80053854(s16 x, s16 y, Monster *m) {
    s16 px;

    px = x;
    if (m->unk_0DC == 0 || m->action == 0x37) {
        return 0;
    }
    if (x < D_801F9ACA) {
        px = x + ((D_801D8864.w + 1) >> 16);
    }
    if (px >= m->box_x0 && y >= m->box_y0 && m->box_x1 >= px && m->box_y1 >= y) {
        return 1;
    }
    if (px >= m->box2_x0 && y >= (s16) m->box2_y0 && m->box2_x1 >= px && (s16) m->box2_y1 >= y) {
        return 2;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80053854);
#endif

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80053970);

u16 func_80053AC4(s16 a, s16 b, s16 c, s16 d, Monster *e) {
    if (e->unk_0DC == 0 || e->action == 0x37) {
        return 0;
    }
    return func_80053B30(a, b, c, d, e);
}

#ifdef NON_MATCHING
/* 99.6 %: (ay - dy) and (ay + dy) land in v1/v0 here; the original computes each into a0, ay's own register */
s32 func_80053B30(s16 x, s16 y, s16 dx, s16 dy, Monster *e) {
    s16 px;
    u16 ax;
    u16 ay;

    px = x;
    if (x < D_801F9ACA) {
        px = x + ((D_801D8864.w + 1) >> 16);
    }
    ax = e->box_x0;
    ay = e->box_y0;
    if (px < (s16) (ax - dx) || y < (s16) (ay - dy)) {
        return 0;
    }
    ax = e->box_x1;
    ay = e->box_y1;
    if ((s16) (ax + dx) < px || (s16) (ay + dy) < y) {
        return 0;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80053B30);
#endif

u16 func_80053BE8(s16 x, Monster *e) {
    s16 v;

    v = x;
    if (x < D_801F9ACA) {
        v = x + ((D_801D8864.w + 1) >> 16);
    }
    if (v < e->box_x0) {
        return 0;
    }
    return v <= e->box_x1;
}

void func_80053C50(s32 amount, Monster *e) {
    s32 level;

    if (e->unk_140 == 0 && D_801E2A54 < 9 && D_801FA890 == 0) {
        if ((u32) (e->action - 0x34) >= 2) {
            if (D_800AA2DC == 0) {
                if (e->unk_040 < 0x78) {
                    level = amount / 20000;
                    if (level >= 0x10) {
                        level = 0xF;
                    }
                    func_800634B0(e, level);
                    amount = 1;
                }
            } else {
                amount *= 4;
            }
        }
        func_80053D68(-amount, e);
    } else {
        amount >>= 1;
        level = amount / 20000;
        if (level >= 0x10) {
            level = 0xF;
        }
        func_800634B0(e, level);
    }
}

void func_80053D68(s32 amount, Monster *e) {
    s32 level;

    if (!(D_8007BD78.flags & 0x400)) {
        e->unk_0F0 += amount;
        if (amount > 0) {
            amount = -amount;
        }
        level = -amount / 20000;
        if (level >= 0x10) {
            level = 0xF;
        }
        func_800634B0(e, level);
    }
}

void func_80053DE4(void) {
}

void func_80053DEC(void) {
    GameObject *b;
    ObjectDef *node;
    u16 x;
    s32 id;

    b = D_800AA268.p;
    func_8001F724(0x29);
    b = b->owner.monster->obj;
    if (b->flags & 0x10) {
        x = D_801FAC90;
    } else {
        x = D_801FAC8C;
    }
    node = func_8001D110();
    id = 0x010035C2;
    node->unk_0C = 0x738;
    node->flags = 0x4000;
    node->pos_y.s.hi = 0xED;
    node->pos_x.s.hi = x;
    node->id = id;
    node->anim = &D_800954CC;
    D_800AA248.new_def = node;
    func_8001DCB4();
    D_800AA248.cur_obj = b;
}

#ifdef NON_MATCHING
/* 92.3 %: y and the flip flag swap s3/s4, and the original computes the flag into v1 and copies it (move in the delay slot) */
void func_80053EA8(void) {
    GameObject *obj;
    Monster *m;
    ObjectDef *def;
    u16 x;
    s32 y;
    s32 sx;
    s16 flip;

    obj = D_800AA268.p;
    y = obj->pos_y.u.hi;
    x = obj->pos_x.u.hi;
    m = obj->owner.monster;
    func_8001F724(0x61);
    if ((u32) (m->climb_side - 1) < 2) {
        y = y - 0x13;
        sx = (s16) x;
        flip = obj->flags & 0x10;
        if (flip) {
            x = sx + 6;
        } else {
            x = sx - 6;
        }
        flip = (flip == 0) * 0x10;
    } else {
        y = y - 0x20;
        sx = (s16) x;
        flip = obj->flags & 0x10;
        if (flip) {
            x = sx - 0x31;
        } else {
            x = sx + 0x31;
        }
    }
    def = func_8001D110();
    D_800AA248.new_def = def;
    def->unk_0C = 0x739;
    def->flags = 0x1100;
    def->pos_y.s.hi = y;
    def->pos_x.s.hi = x;
    def->id = 0x4F0000B2;
    def->anim = &D_8008C7A4;
    obj = func_8001DCB4();
    obj->flags |= flip;
    obj->unk_9C = m->id;
    D_800AA248.cur_obj = obj;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80053EA8);
#endif

void func_80053FDC(void) {
    GameObject *b;
    s32 v;

    b = D_800AA268.p;
    v = b->vel_y.w + 0x3000;
    if (v > 0x60000) {
        v = 0x60000;
    }
    b->pos_y.w += v;
    b->vel_y.w = v;
    if (b->pos_y.s.hi >= 0xC0) {
        b->priority = 0x319;
    } else {
        b->script.pc = *b->arg.w;
    }
}

void func_8005404C(Monster *e) {
    GameObject *b;
    ObjectDef *node;
    u16 y;

    b = D_800AA248.cur_obj;
    node = func_8001D110();
    D_800AA248.new_def = node;
    node->unk_0C = 0x743;
    node->flags = 0x4000;
    node->pos_x.s.hi = e->pos.u.lo;
    y = e->pos.u.hi;
    node->id = 0x4F000052;
    node->anim = &D_800123BC;
    node->pos_y.s.hi = y;
    func_8001DCB4();
    D_800AA248.cur_obj = b;
}

void func_800540D0(Monster *e) {
    GameObject *b;
    ObjectDef *node;
    u16 y;

    b = D_800AA248.cur_obj;
    func_8001F724((func_8001EA78() & 3) + 0x17);
    func_8001F724((func_8001EA78() & 1) + 0x15);
    node = func_8001D110();
    D_800AA248.new_def = node;
    node->unk_0C = 0x741;
    node->flags = 0x4000;
    node->pos_x.s.hi = e->pos.u.lo;
    y = e->pos.u.hi;
    node->id = 0x4F000066;
    node->anim = &D_800954A4;
    node->pos_y.s.hi = y;
    func_8001DCB4();
    D_800AA248.cur_obj = b;
}

void func_8005417C(Monster *e) {
    GameObject *b;
    ObjectDef *node;
    u16 y;

    b = D_800AA248.cur_obj;
    func_8001F724((func_8001EA78() & 1) + 0x1B);
    func_8001F724(0x14);
    node = func_8001D110();
    D_800AA248.new_def = node;
    node->unk_0C = 0x742;
    node->flags = 0x4000;
    node->pos_x.s.hi = e->pos.u.lo;
    y = e->pos.u.hi;
    node->id = 0x4F000060;
    node->anim = &D_8009547C;
    node->pos_y.s.hi = y;
    func_8001DCB4();
    D_800AA248.cur_obj = b;
}

void func_8005421C(Monster *e) {
    Monster *m;
    GameObject *obj;
    s32 dx;
    u16 i;

    if (D_801E28C8 != 0) {
        if (D_800AA248.cur_obj->vel_y.w > 0x580000) {
            i = 7;
            do {
                if (e->id == i) {
                    continue;
                }
                m = &D_801E0B78[i];
                if (!(m->unk_058 & 1) || m->unk_0DC == 0 || m->action == 0x37 || m->climb_side != 0) {
                    continue;
                }
                obj = m->obj;
                dx = obj->pos_x.s.hi - D_800AA248.cur_obj->pos_x.s.hi;
                if ((dx < 0 ? -dx : dx) < 0x13 && obj->pos_y.s.hi == 0xE1) {
                    m->attacker = e;
                    if (D_8007A68A != 0) {
                        func_80053C50(0x30000, m);
                    }
                    func_800634D4(m, 5);
                    m->action = 0xE;
                    D_800AA248.cur_obj->vel_y.w = -0x50000;
                    return;
                }
            } while (--i != 0);
        }
    }
}

void func_80054374(s32 points, Monster *e) {
    s32 old;
    s32 score;
    s32 next;
    s32 step;
    s32 n;

    n = 0;
    if (e->health.w != 0) {
        step = 50000;
        next = step;
        old = e->unk_038;
        e->unk_038 += points;
        score = e->unk_038;
        for (;;) {
            if (score < next) {
                return;
            }
            n++;
            if (old < next) {
                e->unk_004++;
                func_8001F724(0x71);
                return;
            }
            next += step;
            if (n == 2) {
                step += 25000;
                n = 0;
            }
        }
    }
}

void func_800543FC(void) {
    Monster *e;
    u16 i;

    i = 3;
    do {
        e = &D_801E0B78[func_80025DF8(i)];
        e->obj = NULL;
        if (e->id != 0 && e->action == 0x37) {
            e->unk_058 &= 0xFFFE;
            D_801FA8A0[e->id - 1] = 0;
            e->id = 0;
            D_8007A7D4 |= 1;
            func_8002BE30(e);
            D_8007A7D4 &= 0xFFFE;
            func_80060F3C();
        }
    } while (--i != 0);
    D_801F9924 = 0;
}

void func_800544D8(Monster *e, GameObject *dst, GameObject *src) {
    if (e->action == 0x47) {
        dst->pos_x.s.hi = src->pos_x.s.hi;
        dst->pos_y.s.hi = src->pos_y.s.hi;
    } else if (e->pos.w != 0) {
        dst->pos_x.s.hi = e->pos.u.lo;
        dst->pos_y.s.hi = e->pos.u.hi;
    }
    dst->priority = src->priority + 0x1000;
}

#ifdef NON_MATCHING
/* 95.4 %: the original reloads m->box_x0 for the facing-left test (its first load dies in the bound's subtraction) and keeps m->box_x1 in v1 */
s32 func_8005453C(s16 x, s32 unused, Monster *m) {
    GameObject *obj;
    s16 px;

    obj = m->obj;
    px = x;
    if (m->unk_0DC == 0 || m->action == 0x37) {
        return 0;
    }
    if (x < D_801F9ACA) {
        px = x + ((D_801D8864.w + 1) >> 16);
    }
    if (px >= m->box_x0 - 0x30 && m->box_x1 + 0x30 >= px) {
        if (!(obj->flags & 0x10)) {
            if (px >= m->box_x1) {
                return 1;
            }
        } else if (m->box_x0 >= px) {
            return 1;
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_8005453C);
#endif

void func_80054608(u16 kind, Monster *e, Building *u) {
    s16 y;
    s16 x;
    s16 top;
    u16 next;

    y = e->obj->pos_y.s.hi;
    if (y >= 0xE1) {
        e->action = 0;
        return;
    }
    x = e->front_x;
    if (x >= (s16) u->unk_004 + 8 && u->unk_00E - 8 >= x) {
        top = u->unk_074;
        if (top - 4 >= y && top - 4 - y < 0xB && u->unk_008 >= kind) {
            if (u->state >= 9) {
                e->unk_152 = (u32) (e->action - 5) < 2;
                e->action = 2;
                e->obj->vel_y.w = 0;
                e->unk_104 = 0;
                func_800580F8(e);
                e->action = 0x4E;
                e->climb_side = 0;
            } else {
                next = u->unk_01E;
                e->climb_side = 3;
                e->action = 0;
                e->climb_building = next;
                e->obj->pos_y.s.hi = u->unk_074 + 8;
            }
        }
    }
}

#ifdef NON_MATCHING
/* 80.6 %: the original tests the count signed (lh) and loads it again unsigned (lhu) into its own register, and i steps as ++i != n (addiu/move/andi) */
Building *func_80054728(u16 n) {
    Building *city;
    u16 i;
    u16 count;

    if (n == 0 || (s16) D_801E29A4 == 0) {
        return NULL;
    }
    count = D_801E29A4;
    city = D_801D3DC8;
    for (i = 1; i != n; i++) {
        city++;
        if (--count == 0) {
            break;
        }
    }
    return city;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80054728);
#endif

void func_8005478C(Monster *e) {
    Building *obj;

    obj = func_80054728(e->climb_building);
    if (obj != NULL && obj->unk_078 == 0 && obj->unk_058 == 0) {
        func_80031280(e, obj);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800547EC);

void func_80054A18(Monster *e) {
    func_800578E0(e, func_80054728(e->climb_building));
}

void func_80054A50(Monster *e) {
    Building *u;
    GameState *g;
    GameState *h;
    s32 limit;
    u16 kind;

    u = func_80054728(e->climb_building);
    if (!func_80057AD8(e, u, 2)) {
        func_80056F38(e, u);
        func_800578E0(e, u);
        g = &D_800AA248;
        if (g->action == 5) {
            g->unk_0C = e->front_x;
            g->unk_10 = g->cur_obj->pos_y.s.hi;
            if ((u32) (g->unk_24 - 4) < 3U) {
                if (func_800573C8(e, u) == 1) {
                    e->unk_104 = 0;
                    g->cur_obj->vel_y.w = 0;
                } else {
                    func_8005640C(e, u);
                }
            } else {
                kind = u->unk_008;
                limit = 0xE3;
                if (kind != 0x300) {
                    limit = 0xDB;
                    if (kind != 0x200) {
                        limit = 0xD3;
                    }
                }
                h = &D_800AA248;
                if (h->unk_10 >= limit) {
                    func_8005618C(e, u);
                } else if (func_800574EC(e, u) == 1) {
                    e->unk_104 = 0;
                    h->cur_obj->vel_y.w = 0;
                } else {
                    func_80054CF8(e, u);
                }
            }
        }
    }
}

void func_80054BA4(Monster *e) {
    Building *u;
    GameState *g;
    GameState *h;
    s32 limit;
    u16 kind;

    u = func_80054728(e->climb_building);
    if (!func_80057AD8(e, u, 1)) {
        func_80056F38(e, u);
        func_800578E0(e, u);
        g = &D_800AA248;
        if (g->action == 5) {
            g->unk_0C = e->front_x;
            g->unk_10 = g->cur_obj->pos_y.s.hi;
            if ((u32) (g->unk_24 - 4) < 3U) {
                if (func_800576B8(e, u) == 1) {
                    e->unk_104 = 0;
                    g->cur_obj->vel_y.w = 0;
                } else {
                    func_8005640C(e, u);
                }
            } else {
                kind = u->unk_008;
                limit = 0xE3;
                if (kind != 0x300) {
                    limit = 0xDB;
                    if (kind != 0x200) {
                        limit = 0xD3;
                    }
                }
                h = &D_800AA248;
                if (h->unk_10 >= limit) {
                    func_8005618C(e, u);
                } else if (func_800577DC(e, u) == 1) {
                    e->unk_104 = 0;
                    h->cur_obj->vel_y.w = 0;
                } else {
                    func_80054CF8(e, u);
                }
            }
        }
    }
}

void func_80054CF8(Monster *e, Building *city) {
    Building *u;
    u16 kind;

    u = city;
    kind = u->unk_008;
    if (u == D_801D3DC8 || (func_80054D74(kind, e, city - 1), D_800AA250 != 3)) {
        func_80054D74(kind, e, u + 1);
    }
}

void func_80054D74(u16 kind, Monster *e, Building *u) {
    u16 next;

    if (u->state < 0xB && u->unk_008 >= kind && D_800AA248.unk_0C >= (s16) u->unk_004 + 8 &&
        (s16) u->unk_00E - 8 >= D_800AA248.unk_0C && D_800AA248.unk_10 >= (s16) u->unk_074 - 4) {
        next = u->unk_01E;
        e->climb_side = 3;
        e->climb_building = next;
        D_800AA248.unk_08 = 3;
        e->action = 0;
        D_800AA248.action = 0;
        D_800AA248.cur_obj->pos_y.s.hi = u->unk_074 + 8;
    }
}

void func_80054E1C(Monster *e) {
    Building *city;
    s16 y;

    city = func_80054728(e->climb_building);
    func_80056F38(e, city);
    func_800578E0(e, city);
    if (D_800AA248.action != 0xF && D_800AA248.action != 2 && D_800AA248.action != 0x4E) {
        if (func_80057AD8(e, city, 2) == 0) {
            D_800AA248.unk_0C = e->front_x;
            y = D_800AA248.cur_obj->pos_y.s.hi;
            D_800AA248.unk_10 = y;
            if (y >= 0xE2) {
                func_8005618C(e, city);
            } else if (func_800573C8(e, city) == 1) {
                e->unk_104 = 0;
                D_800AA248.cur_obj->vel_y.w = 0;
            } else {
                func_80054CF8(e, city);
            }
        }
    }
}

void func_80054F18(Monster *e) {
    Building *city;
    s16 y;

    city = func_80054728(e->climb_building);
    if (func_80057AD8(e, city, 2) == 0) {
        func_80056F38(e, city);
        func_800578E0(e, city);
        if (D_800AA248.action != 0xF && D_800AA248.action != 2 && D_800AA248.action != 0x4E) {
            D_800AA248.unk_0C = e->front_x;
            y = D_800AA248.cur_obj->pos_y.s.hi;
            D_800AA248.unk_10 = y;
            if (y >= 0xE2) {
                func_8005618C(e, city);
            } else if (func_800573C8(e, city) == 1) {
                e->unk_104 = 0;
                D_800AA248.cur_obj->vel_y.w = 0;
            } else {
                func_8005640C(e, city);
            }
        }
    }
}

void func_80055014(Monster *e) {
    Building *city;
    s16 y;

    city = func_80054728(e->climb_building);
    if (func_80057AD8(e, city, 1) == 0) {
        func_80056F38(e, city);
        func_800578E0(e, city);
        if (D_800AA248.action != 0xF && D_800AA248.action != 2 && D_800AA248.action != 0x4E) {
            D_800AA248.unk_0C = e->front_x;
            y = D_800AA248.cur_obj->pos_y.s.hi;
            D_800AA248.unk_10 = y;
            if (y >= 0xE2) {
                func_8005618C(e, city);
            } else if (func_800576B8(e, city) == 1) {
                e->unk_104 = 0;
                D_800AA248.cur_obj->vel_y.w = 0;
            } else {
                func_80054CF8(e, city);
            }
        }
    }
}

void func_80055110(Monster *e) {
    Building *u;
    s16 y;

    u = func_80054728(e->climb_building);
    if (!func_80057AD8(e, u, 1)) {
        func_80056F38(e, u);
        func_800578E0(e, u);
        if (D_800AA248.action != 0xF && D_800AA248.action != 2 && D_800AA248.action != 0x4E) {
            D_800AA248.unk_0C = e->front_x;
            y = D_800AA248.cur_obj->pos_y.s.hi;
            D_800AA248.unk_10 = y;
            if (y >= 0xE2) {
                func_8005618C(e, u);
                return;
            }
            if (func_800576B8(e, u) == 1) {
                e->unk_104 = 0;
                D_800AA248.cur_obj->vel_y.w = 0;
                return;
            }
            func_8005640C(e, u);
        }
    }
}

#ifdef NON_MATCHING
/* 97.9%: the original reloads D_800AA248.unk_0C (through the pointer, kept in a0) for the second difference; GCC here reuses the first load */
void func_8005520C(Monster *e) {
    Building *u;
    GameState *g;
    GameState *h;
    s16 d;

    u = func_80054728(e->climb_building);
    func_80056F38(e, u);
    func_800578E0(e, u);
    g = &D_800AA248;
    if (g->action != 0xF && g->action != 2 && g->action != 0x4E) {
        g->unk_10 = (s16) u->unk_074 + 8;
        g->cur_obj->pos_y.s.hi = g->unk_10;
        if ((u32) (g->unk_24 - 4) < 3U && !func_80057AD8(e, u, 3)) {
            func_80055970(e, u);
            e->action = g->action;
            if (g->action == 0xD) {
                return;
            }
        }
        h = &D_800AA248;
        h->unk_40 = 0;
        d = h->unk_0C - u->unk_004;
        if (d <= 0) {
            func_80055454(e, u);
            return;
        }
        if (d < 0x10) {
            func_8005558C(e, u);
            return;
        }
        d = u->unk_00E - h->unk_0C;
        if (d <= 0) {
            func_80055740(e, u);
            return;
        }
        if (d < 0x10) {
            func_8005584C(e, u);
            return;
        }
        func_80055948(e, u);
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_8005520C);
#endif

void func_800553B0(Monster *e) {
    Building *obj;

    if (!(D_800AA2DC & 0x38)) {
        obj = func_80054728(e->climb_building);
        if (!func_80057AD8(e, obj, 1)) {
            func_80056F38(e, obj);
            func_800578E0(e, obj);
            if (D_800AA25C != 0xF && D_800AA25C != 2 && D_800AA25C != 0x4E) {
                func_80055454(e, obj);
            }
        }
    }
}

void func_80055454(Monster *e, Building *city) {
    D_800AA248.unk_40 = 1;
    if (!(D_800AA2DC & 0x38) && !func_80057AD8(e, city, 1)) {
        if (D_800AA248.unk_24 == 1 || D_800AA248.unk_24 == 8) {
            func_80055600(e, city);
        } else {
            func_800554F8(e, city);
        }
    }
}

void func_800554F8(Monster *e, Building *u) {
    if (!(D_800AA2DC & 0x38) && !func_80057AD8(e, u, 1)) {
        if (D_800AA248.unk_24 == 2 || D_800AA248.unk_24 == 4 || D_800AA248.unk_24 == 3) {
            func_80055948(e, u);
            return;
        }
        e->action = 9;
        D_800AA248.action = 9;
    }
}

void func_8005558C(Monster *e, Building *u) {
    if (!(D_800AA2DC & 0x38) && !func_80057AD8(e, u, 1) && (D_800AA26C == 1 || D_800AA26C == 8)) {
        func_80055600(e, u);
    }
}

void func_80055600(Monster *e, Building *u) {
    if (!(D_800AA2DC & 0x38) && !func_80057AD8(e, u, 1)) {
        if (func_800577DC(e, u) == 1) {
            if (D_800AA288 != 0) {
                func_800554F8(e, u);
            }
        } else {
            func_800564C0(e, u);
            func_80056050(e, u);
            func_80056528(e);
        }
    }
}

void func_800556AC(Monster *e) {
    Building *obj;

    obj = func_80054728(e->climb_building);
    if (!func_80057AD8(e, obj, 2)) {
        func_80056F38(e, obj);
        func_800578E0(e, obj);
        if (D_800AA25C != 0xF && D_800AA25C != 2 && D_800AA25C != 0x4E) {
            func_80055740(e, obj);
        }
    }
}

void func_80055740(Monster *e, Building *u) {
    D_800AA248.unk_40 = 1;
    if (!func_80057AD8(e, u, 2)) {
        if ((u32) (D_800AA248.unk_24 - 1) < 2U) {
            func_800558AC(e, u);
            return;
        }
        func_800557C8(e, u);
    }
}

void func_800557C8(Monster *e, Building *u) {
    if (!func_80057AD8(e, u, 2)) {
        if (D_800AA248.unk_24 == 8 || D_800AA248.unk_24 == 6 || D_800AA248.unk_24 == 7) {
            func_80055948(e, u);
            return;
        }
        e->action = 9;
        D_800AA248.action = 9;
    }
}

void func_8005584C(Monster *e, Building *u) {
    if (!func_80057AD8(e, u, 2) && (u32) (D_800AA26C - 1) < 2U) {
        func_800558AC(e, u);
    }
}

void func_800558AC(Monster *e, Building *u) {
    if (!func_80057AD8(e, u, 2)) {
        if (func_800574EC(e, u) == 1) {
            if (D_800AA288 != 0) {
                func_800557C8(e, u);
            }
        } else {
            func_80056510(e, u);
            func_80056134(e, u);
            func_80056528(e);
        }
    }
}

void func_80055948(Monster *e, Building *u) {
    if (D_800AA248.action == 9) {
        e->action = 0;
        D_800AA248.action = 0;
    }
}

void func_80055970(Monster *e, Building *city) {
    Building *start;
    GameState *g;
    u16 kind;

    if (!(D_800AA2DC & 0x38)) {
        kind = city->unk_008;
        start = city;
        if (city == D_801D3DC8) {
            city = &D_801D3DC8[(s16) D_801E29A4 - 1];
        } else {
            city--;
        }
        if (kind < city->unk_008 || city->state >= 0xB) {
            func_80055B68(e, start);
            return;
        }
        g = &D_800AA248;
        if (!func_80056378(g->unk_0C, city)) {
            func_80055AB8(e, city, start);
            return;
        }
        if (func_800573EC(e, city, e->climb_building) == 1) {
            e->unk_104 = 0;
            g->cur_obj->vel_y.w = 0;
            return;
        }
        func_800560A8(e, city);
        e->action = 0xD;
        g->action = 0xD;
    }
}

void func_80055AB8(Monster *e, Building *city, Building *start) {
    if (func_800562E4(D_800AA248.unk_0C, city) == 0) {
        func_80055B68(e, start);
        return;
    }
    if (func_800576DC(e, city, e->climb_building) == 1) {
        e->unk_104 = 0;
        D_800AA248.cur_obj->vel_y.w = 0;
        return;
    }
    func_80055FBC(e, city);
    e->action = 0xD;
    D_800AA248.action = 0xD;
}

void func_80055B68(Monster *e, Building *city) {
    GameState *g;
    u16 kind;

    kind = city->unk_008;
    if (city == &D_801D3DC8[(s16) D_801E29A4 - 1]) {
        city = D_801D3DC8;
    } else {
        city++;
    }
    if (kind >= city->unk_008 && city->state < 0xB) {
        g = &D_800AA248;
        if (!func_80056378(g->unk_0C, city)) {
            if (!func_800562E4(g->unk_0C, city)) {
                return;
            }
            if (func_800576DC(e, city, e->climb_building) == 1) {
                e->unk_104 = 0;
                g->cur_obj->vel_y.w = 0;
                return;
            }
            func_80055FBC(e, city);
        } else {
            if (func_800573EC(e, city, e->climb_building) == 1) {
                e->unk_104 = 0;
                g->cur_obj->vel_y.w = 0;
                return;
            }
            func_800560A8(e, city);
        }
        e->action = 0xD;
        g->action = 0xD;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80055CA8);

void func_80055FBC(Monster *e, Building *city) {
    u16 target;
    u16 state;

    target = city->unk_01E;
    e->climb_side = 1;
    e->climb_building = target;
    D_800AA248.unk_08 = 1;
    state = e->action;
    if (state == 0x11 || state == 2 || state == 0x4E || state == 0x2C) {
        e->action = 6;
        D_800AA248.action = 6;
        e->unk_168 = 3;
        D_800AA248.cur_obj->vel_x.w = 0;
        D_800AA248.cur_obj->vel_y.w = 0;
        e->unk_05C = 0;
    } else {
        D_800AA248.action = 0xD;
        e->action = 0xD;
    }
}

void func_80056050(Monster *e, Building *city) {
    u16 target;

    target = city->unk_01E;
    e->climb_side = 1;
    e->climb_building = target;
    D_800AA248.unk_08 = 1;
    e->action = 6;
    D_800AA248.action = 6;
    e->unk_168 = 3;
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    e->unk_05C = 0;
}

void func_800560A8(Monster *e, Building *city) {
    u16 target;
    u16 state;

    target = city->unk_01E;
    e->climb_side = 2;
    e->climb_building = target;
    D_800AA248.unk_08 = 2;
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    state = e->action;
    if (state == 0x11 || state == 2 || state == 0x4E || state == 0x2C) {
        e->action = 6;
        D_800AA25C = 6;
        e->unk_168 = 7;
        e->unk_05C = 0;
    } else {
        D_800AA248.action = 0xD;
        e->action = 0xD;
    }
}

void func_80056134(Monster *e, Building *city) {
    u16 target;

    target = city->unk_01E;
    e->climb_side = 2;
    e->climb_building = target;
    D_800AA248.unk_08 = 2;
    e->action = 6;
    D_800AA248.action = 6;
    e->unk_168 = 7;
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    e->unk_05C = 0;
}

void func_8005618C(Monster *e, Building *city) {
    D_800AA248.cur_obj->pos_y.w = 0xE10000;
    D_800AA248.action = 0;
    e->action = 0;
    e->climb_building = 0;
    e->climb_side = 0;
    func_8004E8A8();
}

#ifdef NON_MATCHING
/* 88 %: the screen-wrap sum: the original adds (x + 1) + width with the width loaded signed, here it is reassociated and loaded unsigned */
u16 func_800561CC(s16 x, Building *city) {
    s16 left;
    s32 cx;
    s16 px;

    left = (s16) city->unk_004;
    cx = left;
    px = x;
    if (left < D_801F9ACA) {
        cx = cx + 1 + D_801D8866;
    }
    if (x < D_801F9ACA) {
        px = x + 1 + D_801D8866;
    }
    if ((u16) (cx - px + 0x12) >= 0x2D || (u16) city->unk_024 != 0) {
        return 0;
    }
    D_800AA258 = 0xE0;
    return 1;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800561CC);
#endif

#ifdef NON_MATCHING
/* 88 %: as func_800561CC (its twin for the other end) */
u16 func_80056258(s16 x, Building *city) {
    s16 left;
    s32 cx;
    s16 px;

    left = (s16) city->unk_00E;
    cx = left;
    px = x;
    if (left < D_801F9ACA) {
        cx = cx + 1 + D_801D8866;
    }
    if (x < D_801F9ACA) {
        px = x + 1 + D_801D8866;
    }
    if ((u16) (cx - px + 0x12) >= 0x2D || (u16) city->unk_028 != 0) {
        return 0;
    }
    D_800AA258 = 0xE0;
    return 1;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80056258);
#endif

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800562E4);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80056378);

void func_8005640C(Monster *e, Building *city) {
    u16 n;
    s16 h;
    GameState *g;

    g = &D_800AA248;
    n = e->climb_side;
    g->unk_08 = n;
    if ((s16) city->unk_074 + 0x34 >= g->unk_10) {
        h = e->unk_1C4.s.hi;
        if (h < 0x30) {
            if (n == 1) {
                goto stand;
            }
        clear:
            e->unk_104 = 0;
            g->cur_obj->vel_y.w = 0;
            return;
        }
        if (h >= 0x159 && n != 2) {
            goto clear;
        }
    stand:
        g->action = 0x10;
            e->action = 0x10;
    }
}

void func_80056488(Monster *e) {
    D_800AA268.p->pos_x.s.hi = func_80054728(e->climb_building)->unk_004 + 0x28;
}

void func_800564C0(Monster *e, Building *city) {
    D_800AA268.p->pos_x.s.hi = city->unk_004 - 0x11;
}

void func_800564D8(Monster *e) {
    D_800AA268.p->pos_x.s.hi = func_80054728(e->climb_building)->unk_00E - 0x28;
}

void func_80056510(Monster *e, Building *u) {
    D_800AA268.p->pos_x.s.hi = u->unk_00E + 0x11;
}

void func_80056528(Monster *e) {
    D_800AA268.p->pos_y.s.hi = func_80054728(e->climb_building)->unk_074 + 0x30;
}

void func_80056560(Monster *e) {
    D_800AA268.p->pos_y.s.hi = func_80054728(e->climb_building)->unk_074 + 8;
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80056598);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80056708);

void func_800567E8(Monster *e, Building *city) {
    D_800AA248.cur_obj->pos_y.s.hi = city->unk_074;
    e->climb_building = city->unk_01E;
    D_800AA248.unk_08 = 3;
    e->climb_side = 3;
    D_800AA248.action = 0x19;
    e->action = 0x19;
    func_8005478C(e);
}

u16 func_80056840(Monster *e) {
    Building *city;
    s32 d;
    s16 n;

    D_800AA248.unk_0C = e->front_x;
    D_800AA248.unk_10 = D_800AA248.cur_obj->pos_y.w;
    D_800AA248.unk_10 -= D_801F9ACC.w;
    if ((u32) (D_800AA248.unk_10 - 0x580000) > 0xB00000) {
        return 0;
    }
    D_800AA248.unk_10 = D_800AA248.cur_obj->pos_y.s.hi;
    n = D_801E29A4;
    D_800AA248.unk_40 = n;
    if (n == 0) {
        return 0;
    }
    D_800AA248.unk_04 = 0;
    city = D_801D3DC8;
    do {
        D_800AA248.unk_04++;
        if (city->state < 9) {
            d = (s16) city->unk_004 - e->front_x;
            if ((d < 0 ? -d : d) < 0x15 && (e->skip_building == 0 || city->unk_01E != e->skip_building) &&
                (u16) func_80056990(e, city) == 1) {
                return 1;
            }
        }
        city++;
    } while (--D_800AA248.unk_40 != 0);
    return 0;
}

s32 func_80056990(Monster *e, Building *u) {
    u16 n;

    if (u->unk_024 < 0) {
        return 0;
    }
    if (D_800AA268.p->pos_y.s.hi < (s16) u->unk_074 + 0x30) {
        return 0;
    }
    n = func_80056A44(e, u);
    if ((u16) u->unk_024 < n && func_800575F0(n, e, u, e->climb_building) != 1) {
        func_80055FBC(e, u);
        func_800564C0(e, u);
        return 1;
    }
    return 0;
}

u16 func_80056A44(Monster *e, Building *city) {
    s16 *limit;
    u16 kind;
    u16 i;

    kind = city->unk_008;
    i = 0;
    switch (kind) {
    case 0x300:
        limit = D_8007FD04;
        break;
    case 0x200:
        limit = D_8007FD24;
        break;
    default:
        limit = D_8007FD44;
        break;
    }
    while (++i < 15) {
        if (D_800AA258 >= *limit) {
            break;
        }
        limit++;
    }
    return i;
}

u16 func_80056AC8(Monster *e) {
    Building *city;
    s32 d;
    s16 n;

    D_800AA248.unk_0C = e->front_x;
    D_800AA248.unk_10 = D_800AA248.cur_obj->pos_y.w;
    D_800AA248.unk_10 -= D_801F9ACC.w;
    if ((u32) (D_800AA248.unk_10 - 0x580000) > 0xB00000) {
        return 0;
    }
    D_800AA248.unk_10 = D_800AA248.cur_obj->pos_y.s.hi;
    n = D_801E29A4;
    D_800AA248.unk_40 = n;
    if (n == 0) {
        return 0;
    }
    D_800AA248.unk_04 = 0;
    city = D_801D3DC8;
    do {
        D_800AA248.unk_04++;
        if (city->state < 9) {
            d = (s16) city->unk_00E - e->front_x;
            if ((d < 0 ? -d : d) < 0x15 && (e->skip_building == 0 || city->unk_01E != e->skip_building) &&
                (u16) func_80056C18(e, city) == 1) {
                return 1;
            }
        }
        city++;
    } while (--D_800AA248.unk_40 != 0);
    return 0;
}

s32 func_80056C18(Monster *e, Building *u) {
    u16 n;

    if (u->unk_028 < 0) {
        return 0;
    }
    if (D_800AA268.p->pos_y.s.hi < (s16) u->unk_074 + 0x30) {
        return 0;
    }
    n = func_80056A44(e, u);
    if ((u16) u->unk_028 < n && func_80057300(n, e, u, e->climb_building) != 1) {
        func_800560A8(e, u);
        func_80056510(e, u);
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80056CCC);

void func_80056E2C(Monster *e, Building *city) {
    u16 n;

    n = e->climb_side;
    D_800AA248.unk_08 = n;
    if ((u32) (n - 1) < 2) {
        D_800AA248.action = 0x12;
        e->action = 0x12;
    } else {
        func_80056E78(e);
    }
}

void func_80056E78(Monster *e) {
    D_800AA25C = 2;
    e->action = 2;
    func_800580F8(e);
    e->climb_side = 0;
    e->climb_building = 0;
    e->climb_floor = 0;
}

void func_80056EB8(Monster *e, Building *city) {
    u16 n;

    if (city->state == 4) {
        if (city->unk_082 != 0) {
            return;
        }
        goto fall;
    }
    n = e->climb_side;
    D_800AA248.unk_08 = n;
    if (n == 3) {
        D_800AA248.action = 0x2C;
        e->action = 0x2C;
        return;
    }
    if (city->state >= 0xB) {
    fall:
        func_80056E78(e);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80056F38);

u16 func_8005703C(Monster *e, Building *u) {
    BuildingBlock *p;

    p = u->unk_018;
    if (p != NULL && p->unk_1C == 2) {
        return func_800570D4(e, p);
    }
    return 0;
}

u16 func_80057088(Monster *e, Building *u) {
    BuildingBlock *p;

    p = u->unk_018;
    if (p != NULL && p->unk_1C == 1) {
        return func_800570D4(e, p);
    }
    return 0;
}

s32 func_800570D4(Monster *e, BuildingBlock *p) {
    s32 x;

    x = p->unk_1E + 8;
    if (x < e->box_y0 || x >= e->box_y1) {
        return 0;
    }
    return 1;
}

u16 func_80057110(Monster *e) {
    BuildingBlock *p;

    p = func_80054728(e->climb_building)->unk_018;
    if (p != NULL && p->unk_1C == 2) {
        return func_800571D0(e, p);
    }
    return 0;
}

u16 func_80057170(Monster *e) {
    BuildingBlock *p;

    p = func_80054728(e->climb_building)->unk_018;
    if (p != NULL && p->unk_1C == 1) {
        return func_800571D0(e, p);
    }
    return 0;
}

s32 func_800571D0(Monster *e, BuildingBlock *p) {
    s32 x;

    x = p->unk_0E - 8;
    if (e->box_y1 < x || e->box_y0 >= x) {
        return 0;
    }
    return 1;
}

u16 func_8005720C(Monster *e, Building *u) {
    BuildingBlock *p;

    p = u->unk_018;
    if (p != NULL && p->unk_1C == 2) {
        return func_800572A4(e, p);
    }
    return 0;
}

u16 func_80057258(Monster *e, Building *u) {
    BuildingBlock *p;

    p = u->unk_018;
    if (p != NULL && p->unk_1C == 1) {
        return func_800572A4(e, p);
    }
    return 0;
}

s32 func_800572A4(Monster *e, BuildingBlock *p) {
    s32 x;

    x = p->unk_1E + 8;
    if (x < e->box_y0 || x >= e->box_y1) {
        x = p->unk_0E - 8;
        if (e->box_y1 < x || e->box_y0 >= x) {
            return 0;
        }
    }
    return 1;
}

u16 func_80057300(u16 x, Monster *e, Building *city, u16 n) {
    Monster *m;
    s32 d;
    u16 i;

    i = 7;
    do {
        if (i != e->id) {
            m = &D_801E0B78[i];
            if ((m->unk_058 & 1) && m->climb_side == 2 && m->climb_building == n) {
                d = m->climb_floor - x;
                if ((d < 0 ? -d : d) < 2) {
                    return 1;
                }
            }
        }
    } while (--i != 0);
    return func_8005720C(e, city);
}

u16 func_800573C8(Monster *e, Building *city) {
    return func_800573EC(e, city, e->climb_building);
}

u16 func_800573EC(Monster *e, Building *city, u16 n) {
    Monster *m;
    s32 d;
    s32 dy;
    s16 y;
    s16 my;
    u16 i;

    i = 7;
    do {
        if (i != e->id) {
            m = &D_801E0B78[i];
            if ((m->unk_058 & 1) && m->climb_side == 2 && m->climb_building == n) {
                d = m->climb_floor - e->climb_floor;
                if ((d < 0 ? -d : d) < 2) {
                    y = D_800AA248.cur_obj->pos_y.s.hi;
                    my = m->obj->pos_y.s.hi;
                    if (y >= my) {
                        dy = y - my;
                        if (dy < 0) {
                            dy = -dy;
                        }
                        if (dy < 0x14) {
                            return 1;
                        }
                    }
                }
            }
        }
    } while (--i != 0);
    return func_8005703C(e, city);
}

u16 func_800574EC(Monster *e, Building *city) {
    Monster *m;
    s32 d;
    s32 dy;
    s16 y;
    s16 my;
    u16 i;

    i = 7;
    do {
        if (i != e->id) {
            m = &D_801E0B78[i];
            if ((m->unk_058 & 1) && m->climb_side == 2 && m->climb_building == e->climb_building) {
                d = m->climb_floor - e->climb_floor;
                if ((d < 0 ? -d : d) < 2) {
                    y = D_800AA248.cur_obj->pos_y.s.hi;
                    my = m->obj->pos_y.s.hi;
                    if (y <= my) {
                        dy = y - my;
                        if (dy < 0) {
                            dy = -dy;
                        }
                        if (dy < 0x14) {
                            return 1;
                        }
                    }
                }
            }
        }
    } while (--i != 0);
    return func_80057110(e);
}

u16 func_800575F0(u16 x, Monster *e, Building *city, u16 n) {
    Monster *m;
    s32 d;
    u16 i;

    i = 7;
    do {
        if (i != e->id) {
            m = &D_801E0B78[i];
            if ((m->unk_058 & 1) && m->climb_side == 1 && m->climb_building == n) {
                d = m->climb_floor - x;
                if ((d < 0 ? -d : d) < 2) {
                    return 1;
                }
            }
        }
    } while (--i != 0);
    return func_80057258(e, city);
}

u16 func_800576B8(Monster *e, Building *u) {
    return func_800576DC(e, u, e->climb_building);
}

u16 func_800576DC(Monster *e, Building *city, u16 n) {
    Monster *m;
    s32 d;
    s32 dy;
    s16 y;
    s16 my;
    u16 i;

    i = 7;
    do {
        if (i != e->id) {
            m = &D_801E0B78[i];
            if ((m->unk_058 & 1) && m->climb_side == 1 && m->climb_building == n) {
                d = m->climb_floor - e->climb_floor;
                if ((d < 0 ? -d : d) < 2) {
                    y = D_800AA248.cur_obj->pos_y.s.hi;
                    my = m->obj->pos_y.s.hi;
                    if (y >= my) {
                        dy = y - my;
                        if (dy < 0) {
                            dy = -dy;
                        }
                        if (dy < 0x14) {
                            return 1;
                        }
                    }
                }
            }
        }
    } while (--i != 0);
    return func_80057088(e, city);
}

u16 func_800577DC(Monster *e, Building *city) {
    Monster *m;
    s32 d;
    s32 dy;
    s16 y;
    s16 my;
    u16 i;

    i = 7;
    do {
        if (i != e->id) {
            m = &D_801E0B78[i];
            if ((m->unk_058 & 1) && m->climb_side == 1 && m->climb_building == e->climb_building) {
                d = m->climb_floor - e->climb_floor;
                if ((d < 0 ? -d : d) < 2) {
                    y = D_800AA248.cur_obj->pos_y.s.hi;
                    my = m->obj->pos_y.s.hi;
                    if (y <= my) {
                        dy = y - my;
                        if (dy < 0) {
                            dy = -dy;
                        }
                        if (dy < 0x14) {
                            return 1;
                        }
                    }
                }
            }
        }
    } while (--i != 0);
    return func_80057170(e);
}

#ifdef NON_MATCHING
/* 98.8 %: the two parameters get s1/s0 instead of s0/s1 (the shared tail and the separate NULL call are right) */
void func_800578E0(Monster *e, Building *city) {
    u16 n;
    u16 kind;

    if (city == NULL) {
        func_80056E78(e);
        return;
    }
    {
        if (city->unk_058 == 1 && city->state != 0) {
            func_80056EB8(e, city);
            return;
        }
        kind = city->state;
        if (kind < 0xB) {
            if (kind != 4) {
                if ((u16) func_80057A08(e) != 1) {
                    if (D_801D3D64.unk_5E >= 0x1E || (e->unk_1C0 <= 0x700000 && D_801D3D64.unk_58 != 0)) {
                        func_80056E2C(e, city);
                    }
                    return;
                }
            } else {
                n = city->unk_082;
                if (n >= 0x83) {
                    return;
                }
                if ((u16) e->climb_floor < 3) {
                    e->action = 0x2B;
                    return;
                }
                if (n != 0) {
                    return;
                }
            }
        }
    }
    func_80056E78(e);
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800578E0);
#endif

u16 func_80057A08(Monster *e) {
    Building *city;
    GameObject *top;

    if (e->climb_side == 0 || e->climb_building == 0) {
        return 0;
    }
    city = func_80054728(e->climb_building);
    if (city != NULL) {
        if (city->state != 4) {
            return 0;
        }
        if (e->climb_side != 3) {
            if ((u16) e->climb_floor == 0) {
                return 0;
            }
            top = *func_80031420(e->climb_floor, city);
            if (e->obj->pos_y.s.hi >= top->pos_y.s.hi) {
                return 0;
            }
        }
        city->unk_032 = e->id;
        return 1;
    }
    return 0;
}

u16 func_80057AD8(Monster *e, Building *city, u16 which) {
    if (!(D_800AA2DC & 4)) {
        return 0;
    }
    if (city == &D_801D3DC8[0] && (which & 1)) {
        return 1;
    }
    if (city == &D_801D48D0 && (which & 2)) {
        return 1;
    }
    return 0;
}

void func_80057B40(void) {
    func_8001E878();
    func_8001E698(D_800AA248.cur_obj, (void *) D_800AA248.unk_00);
}

void func_80057B78(void) {
    D_800AA268.p->owner.monster->unk_028 = 1;
}

void func_80057B94(Monster *e, s32 *table) {
    table += (u16) (e->id - 1);
    func_8004C2B8(*table, e);
}

/* Starts the animation script of entry n of the monster's table (8-byte entries: the script, a value for unk_0EA). */
void func_80057BD4(u16 n, Monster *e, s32 *table) {
    table += (u16) (e->id - 1);
    table = (s32 *) *table; /* FAKE: the table pointer reused for the id and the entry: the original keeps all three in a2 */
    table = (s32 *) func_8001B660((s32) table + n * 8);
    e->unk_0EA = ((u16 *) table)[2];
    func_8004C2B8(*table, e);
}

/* Starts the animation script of table[monster id - 1], entry n. */
void func_80057C38(u16 n, Monster *e, s32 *table) {
    table += (u16) (e->id - 1);
    func_8004C2B8(*(s32 *) func_8001B660(*table + n * 4), e);
}

void func_80057C8C(void) {
}
