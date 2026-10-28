/* The monsters: the action dispatcher (monster_dispatch_action, the handler table D_8007F8FC by Monster.action) and the
 * actions, the hits and the knockback, the score and the extra lives, and climbing the buildings.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "game.h"
#include "monster.h"

void monster_dispatch_action(Monster *e, GameObject *obj, u16 index) {
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
    D_800AA248.action = state;
    D_800AA248.unk_0C = x;
    D_800AA248.cur_obj = obj;
    D_8007F8FC[state](e);
}

void func_80050190(Monster *e) {
    if (!(e->buttons & 4)) {
        e->action = 0;
    }
}

// u16 A2 B1
void monster_update_walk(Monster *e) {
    s32 *speeds;
    s32 speed;
    u16 dir;
    u16 act;
    s16 x;

    if (e->unk_18E == 0 || e->dir == 0) {
        D_800AA268.p->vel_y.w = 0;
        e->unk_104 = 0;
        if (e->id == 7 && D_801F9ABC != 0) {
            if (D_801F9ABC == 3) {
                speeds = D_8007FAE4;
            } else {
                speeds = D_8007FA9C;
            }
        } else {
            speeds = D_8007FB08[e->id - 1];
        }
        dir = e->dir;
        D_800AA248.dir = dir;
        speed = speeds[dir];
        if (D_8007C976 == 2) {
            if (speed > 0x6000) {
                speed -= 0x1000;
            } else if (speed < -0x6000) {
                speed += 0x1000;
            }
        }
        if (e->unk_168 == 7) {
            if (e->dir < 2 || e->dir == 5) {
                e->unk_100 = 0;
                act = 0;
                D_800AA268.p->vel_x.w = 0;
            } else if (e->dir < 5) {
                e->unk_100 = 0;
                act = 0xC;
                D_800AA268.p->vel_x.w = 0;
            } else {
                act = 1;
                e->unk_100 = speed;
            }
        } else {
            if (e->dir < 2 || e->dir == 5) {
                e->unk_100 = 0;
                act = 0;
                D_800AA268.p->vel_x.w = 0;
            } else if (e->dir >= 6) {
                e->unk_100 = 0;
                act = 0xC;
                D_800AA268.p->vel_x.w = 0;
            } else {
                act = 1;
                e->unk_100 = speed;
            }
        }
        e->action = D_800AA248.action = act;
        D_800AA248.unk_08 = e->climb_side;
        if (D_800AA248.unk_08 != 0) {
            func_8005520C(e);
        } else if ((u16) (e->dir - 4) < 3 && e->health.w > 0xFFFF) {
            monster_grab_building(e);
        }
        act = D_800AA25C;
        e->action = act;
        if (act == 0 && D_801E1E44 >= 2) {
            func_80050E88(e);
        }
        if (e->unk_18E == 0 && e->climb_side == 0 && D_801D37BC == 0 && D_800AA268.p->pos_y.s.hi >= 0xE1 &&
            D_801FA98C != 0) {
            x = D_800AA268.p->pos_x.s.hi;
            if (x >= D_801FA98C && x <= D_801FA990) {
                if (x - D_801FA98C < 0x21) {
                    if (e->unk_168 != 7) {
                        e->action = 0x3D;
                    }
                } else if (D_801FA990 - x < 0x21) {
                    if (e->unk_168 != 3) {
                        e->action = 0x3D;
                    }
                } else {
                    e->action = 0x35;
                }
            }
        }
    } else {
        func_80050B40(e);
    }
}

void func_800504B4(Monster *e) {
    D_800AA248.dir = e->dir;
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
    D_800AA248.cur_obj->vel_y.w = e->screen_y <= 0x6FFFFF ? 0x20000 : 0xC0000;
    if (e->unk_168 == 7) {
        func_80054E1C(e);
    } else {
        func_80055014(e);
    }
}

void func_8005059C(Monster *e) {
    s32 kind;

    D_800AA248.dir = e->dir;
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

    obj = monster_get_building(e->climb_building);
    if (obj != NULL) {
        if (e->climb_side == 2) {
            x = obj->right;
            if (D_800AA268.p->flags & 0x10) {
                x += 0x18;
            } else {
                x -= 0x18;
            }
            D_800AA268.p->pos_x.s.hi = x;
        } else if (e->climb_side == 1) {
            x = obj->left;
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

#ifdef NON_MATCHING
/* 83.56%: the original keeps the x offset and its copy (negated when the holder faces left) in two registers, reads
 * the holder's x before the index and copies e into a1 (frame takes a0); here they share one. dx = d before the
 * facing test (the original's delay-slot move) and the x read before the frame: 81.5 % */
void monster_follow_holder(Monster *e) {
    GameObject *holder;
    SpriteFrame *frame;
    FramePoint *pt;
    s32 i;
    s32 x;
    s32 d;
    s32 dx;
    s32 dy;

    holder = e->holder;
    if (holder != NULL) {
        D_800AA248.cur_obj->priority = holder->priority + 1;
        D_800AA248.cur_obj->vel_y.w = holder->vel_y.w;
        D_800AA248.cur_obj->vel_x.w = 0;
        frame = holder->frame;
        x = holder->pos_x.u.hi;
        pt = (FramePoint *) &frame->unk_10;
        i = e->id - 1;
        pt += i;
        dy = pt->y - frame->origin.u.hi;
        d = pt->x - frame->origin.u.lo;
        if (holder->flags & 0x10) {
            dx = -d;
            D_800AA248.cur_obj->flags |= 0x10;
        } else {
            dx = d;
            D_800AA248.cur_obj->flags &= ~0x10;
        }
        D_800AA248.cur_obj->pos_x.w = D_801D8864.w & ((x + dx) << 16);
        D_800AA248.cur_obj->pos_y.s.hi = dy + holder->pos_y.u.hi;
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/monster", monster_follow_holder);
#endif

void monster_update_climb(Monster *e) {
    s32 *speeds;
    s32 vy;
    u16 dir;

    if (e->climb_building == 0) {
        e->action = 0xF;
        func_8005180C(e);
        return;
    }
    D_800AA268.p->vel_x.w = 0;
    e->unk_100 = 0;
    if (e->id == 7 && D_801F9ABC != 0) {
        if (D_801F9ABC == 3) {
            speeds = D_8007FB6C;
        } else {
            speeds = D_8007FB24;
        }
    } else {
        speeds = D_8007FB90[e->id - 1];
    }
    dir = e->dir;
    D_800AA248.dir = dir;
    D_800AA248.cur_obj->vel_y.w = speeds[dir];
    if (D_8007C976 == 1) {
        if (D_800AA248.cur_obj->vel_y.w > 0x6000) {
            D_800AA248.cur_obj->vel_y.w -= 0x1000;
        } else if (D_800AA248.cur_obj->vel_y.w < -0x6000) {
            D_800AA248.cur_obj->vel_y.w += 0x1000;
        }
    }
    if (D_800AA248.cur_obj->vel_y.w != 0) {
        D_800AA248.action = 5;
        e->action = 5;
    } else {
        D_800AA248.action = 6;
        e->action = 6;
        e->unk_104 = 0;
        D_800AA248.cur_obj->vel_y.w = 0;
    }
    if (e->unk_168 == 7) {
        func_80054A50(e);
        return;
    }
    func_80054BA4(e);
}

void func_800509EC(Monster *e) {
    func_80050E58(e);
    func_800531C0(e);
    if ((s16) e->pos.u.hi != 0 && e->unk_0DE != 0) {
        if (e->unk_18A == 0) {
            func_80036A20(e);
            if (e->unk_18A == 0) {
                pickup_collect(e);
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

void func_80050BBC(e)
Monster *e;
{
    GameObject *obj;
    s32 dir;
    s32 *p;
    s32 v;

    obj = D_800AA268.p = e->obj;
    dir = e->dir;
    if (!(obj->unk_6C & 0x80)) {
        if (dir != 0) {
            if (e->unk_168 == 7) {
                if (dir < 5 && dir != 1) {
                    e->action = 0xC;
                }
            } else if (dir >= 6) {
                e->action = 0xC;
            }
        }
        if (D_801FA734 == 0 && D_801F9ACC.w < 0) {
            goto still;
        }
        dir = e->dir;
    } else {
    still:
        dir = 1;
        if (obj->vel_y.w < 0) {
            obj->vel_y.w = 0;
        }
    }
    p = &D_8007FBAC[dir].unk_1A0;
    e->unk_1A0 = *p++;
    e->unk_1A4 = *p++;
    e->unk_100 = *p++;
    e->unk_104 = *p++;
    e->unk_198 = *p++;
    e->unk_19C = *p;
    v = e->unk_198;
    if (v == -1) {
        v = obj->vel_x.w;
        if (abs(abs(v) - 0xA000) > 0xA000) {
            if (v > 0) {
                v = -0xA000;
            } else if (v < 0) {
                v = 0xA000;
            }
        } else {
            obj->vel_x.w = 0;
        }
        e->unk_198 = v;
    }
    v = e->unk_19C;
    if (v == -1) {
        v = obj->vel_y.w;
        if (abs(abs(v) - 0xA000) > 0xA000) {
            if (v > 0) {
                v = -0xA000;
            } else if (v < 0) {
                v = 0xA000;
            }
        } else {
            obj->vel_y.w = 0;
        }
        e->unk_19C = v;
    }
}

void func_80050DAC(Monster *e) {
    func_80050E58(e);
    func_800531C0(e);
}

void func_80050DD8(Monster *e) {
    u16 n;

    D_800AA248.dir = e->dir;
    if (e->dir == 0) {
        func_800531C0(e);
        return;
    }
    n = e->climb_side;
    D_800AA248.unk_08 = n;
    if (n == 0 || e->climb_side == 3) {
        e->action = 0;
        monster_update_walk(e);
    } else {
        e->action = 6;
        monster_update_climb(e);
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

#ifdef NON_MATCHING
/* 98.60%: 98.6 %: global-alloc order: m (22 refs over 63 insns, 1.40) outranks obj (14 over 32, 1.31) and e (17
 * over 176, 0.39) outranks i (7 over 59, 0.24); obj and i each need one more reference (15 and 8) to come first as
 * in the original. Merging the per-path action stores lowers m and e enough, but the smaller loop then hoists
 * &D_801E0B78 and drops the 0x1C/0xB constants from s4/s5 */
void func_80050E88(Monster *e) {
    Monster *m;
    GameObject *obj;
    u16 i;
    s16 y;
    s16 d;
    s32 ad;
    s16 dist;
    u16 act;

    if (D_800AA2DC != 0 && (D_8007BD78.flags & 0x100)) {
        return;
    }
    y = D_800AA268.p->pos_y.s.hi;
    if (y >= 0xE2) {
        return;
    }
    i = 7;
    do {
        if (i == e->id) {
            continue;
        }
        m = &D_801E0B78[i];
        if (!(m->unk_058 & 1)) {
            continue;
        }
        if (m->action != 0) {
            continue;
        }
        obj = m->obj;
        if (y != obj->pos_y.s.hi) {
            continue;
        }
        if ((D_800AA268.p->flags & 0x10) != (obj->flags & 0x10)) {
            d = func_8003FCD8(obj->pos_x.s.hi, D_800AA268.p->pos_x.s.hi);
            ad = (s16) abs(d);
            if (ad < 0x21) {
                if (obj->flags & 0x10) {
                    if (d > 0) {
                        act = 0x1C;
                        e->action = act;
                        m->action = act;
                        return;
                    }
                } else if (d < 0) {
                    act = 0x1C;
                    e->action = act;
                    m->action = act;
                    return;
                }
                if (ad < 0x19) {
                    act = 0xB;
                    e->action = act;
                    m->action = act;
                    return;
                }
            }
        } else {
            dist = func_8003FCD8(obj->pos_x.s.hi, D_800AA268.p->pos_x.s.hi);
            ad = (s16) abs(dist);
            if (ad < 0x19) {
                if (obj->flags & 0x10) {
                    if (dist > 0) {
                        m->action = 0x1C;
                        e->action = 0xB;
                        return;
                    }
                    e->action = 0x1C;
                    m->action = 0xB;
                    return;
                }
                if (dist < 0) {
                    m->action = 0x1C;
                    e->action = 0xB;
                    return;
                }
                e->action = 0x1C;
                m->action = 0xB;
                return;
            }
        }
    } while (--i != 0);
}
#else
INCLUDE_ASM("asm/main/nonmatchings/monster", func_80050E88);
#endif

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

    if (e->unk_164 == 0) {
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

void func_800514CC(Monster *e) {
    Monster *m;
    u16 i;

    if (e->pos.s.lo == 0 || (e->climb_side != 0 && e->climb_side != 3)) {
        func_800510E8(e);
        return;
    }
    i = 7;
    do {
        m = &D_801E0B78[i];
        if (m != e && (m->unk_058 & 1) && m->unk_0DC != 0 && m->action != 0x37) {
            D_800AA248.unk_08 = monster_test_hit_box(e, m);
            if (D_800AA248.unk_08 != 0) {
                m->attacker = e;
                if (m->action == 0x4D) {
                    func_80051410(e, m);
                    return;
                }
                func_800634D4(m, 5);
                if (D_8007A68A != 0) {
                    func_80053C50(0x30000, m);
                }
                if (m->unk_18E != 0) {
                    func_800511B4(e, m);
                    return;
                }
                if (e->unk_164 != 0) {
                    func_80051248(e, m);
                    return;
                }
                if (m->climb_side != 0 || m->obj->pos_y.s.hi != 0xE1) {
                    func_80051150(e, m);
                    return;
                }
                if ((D_800AA248.cur_obj->flags & 0x10) == (m->obj->flags & 0x10)) {
                    func_800511F8(e, m);
                    return;
                }
                if (D_800AA248.unk_08 != 1 || e->action != 4 || e->unk_104 != 0) {
                    func_800512CC(e, m);
                    return;
                }
                m->action = 0x28;
                func_8004FC00(2, e);
                func_800540D0(e);
                func_800510E8(e);
                return;
            }
        }
    } while (--i != 0);
    if (e->unk_18A != 0 || (func_80036A20(e), e->unk_18A != 0) || (pickup_collect(e), e->unk_18A != 0) ||
        (func_8004D38C(e), e->unk_18A != 0) || (func_8003F114(e), e->unk_18A != 0) ||
        (func_80047028(e), e->unk_18A != 0)) {
        func_800634D4(e, 3);
    }
    func_800510E8(e);
}

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
            if (D_800AA248.action == 0x4E || (monster_find_roof(), D_800AA248.action == 2)) {
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
    g->dir = e->dir;
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
            D_800AA248.unk_08 = (u16) monster_test_hit_box(e, m);
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
            pickup_collect(e);
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
        pickup_collect(e);
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

void monster_start_jump(Monster *e) {
    s32 vy;

    D_800AA248.action = 0x2C;
    e->action = 0x2C;
    switch (e->dir) {
    case 4:
    case 5:
    case 6:
        vy = -0x90000;
        break;
    case 1:
    case 2:
    case 8:
        vy = -0x50000;
        break;
    default:
        vy = -0x70000;
        break;
    }
    D_800AA268.p->vel_y.w = vy;
    e->unk_104 = 0;
}

void func_80052520(Monster *e) {
    GameState *g;
    s32 vx;
    u16 dir;

    vx = 0;
    g = &D_800AA248;
    g->dir = 0;
    if (D_801D3DC2 >= 3) {
        func_80052880(e, g);
        return;
    }
    g->dir = e->dir;
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
        monster_find_wall(e);
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
        monster_find_roof();
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

void func_80052880(Monster *e, GameState *g) {
    Monster *other;
    s32 vx;

    switch (e->id) {
    default:
        other = &D_801E0B78[func_80025DF8(1)];
        if (other->climb_side != 3) {
            other = &D_801E0B78[func_80025DF8(2)];
            if (other->climb_side != 3) {
                vx = func_80052A68(e);
                break;
            }
        }
        vx = func_80052A0C(e, other);
        break;
    case 1:
        other = &D_801E0B78[func_80025DF8(3)];
        if (other->climb_side != 3) {
            other = &D_801E0B78[func_80025DF8(2)];
            if (other->climb_side != 3) {
                vx = func_80052A68(e);
                break;
            }
        }
        vx = func_80052A0C(e, other);
        break;
    case 2:
        other = &D_801E0B78[func_80025DF8(1)];
        if (other->climb_side != 3) {
            other = &D_801E0B78[func_80025DF8(3)];
            if (other->climb_side != 3) {
                vx = func_80052A68(e);
                break;
            }
        }
        vx = func_80052A0C(e, other);
        break;
    }
    e->unk_100 = vx;
    e->unk_104 = 0x4000;
    e->climb_side = 0;
    e->climb_building = 0;
    monster_find_wall(e);
    if (e->action == 0x2C) {
        if (D_800AA268.p->vel_y.w > 0) {
            func_80052ADC(e);
            return;
        }
        func_80051A08(e);
        return;
    }
    func_800531C0(e);
}

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

    monster_find_roof();
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
    D_800AA248.dir = e->dir;
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
                other = bonus_find_most_lives();
                if (other != NULL) {
                    other->lives--;
                    e->lives = 0;
                    e->lives_shown = 0xFF;
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

#ifdef NON_MATCHING
/* 98.78%: the definition pointer: local-alloc gives it v0 in its suggested-register pass (the copy from the call's
 * value suggests v0, free over its life); the original's sits in a1 after the temporaries took v0/v1/a0, which is
 * what a block-local pseudo without that suggestion (allocated by priority after the short temporaries) or a global
 * pseudo gets (case 3's building pointer, global, takes a0 the same way). Read-back through D_800AA284/new_def,
 * chained stores, a second set, a dead assignment in another block, an argument to func_8001DCB4: no change */
void func_80052E9C(Monster *e) {
    s32 *speeds;
    s32 speed;
    u16 dir;
    Building *city;
    Building *u;
    ObjectDef *def;
    u16 x;
    s16 i;

    switch (e->id) {
    case 3:
        speeds = D_8007FB08[e->id - 1];
        dir = e->dir;
        D_800AA248.dir = dir;
        speed = speeds[dir];
        if (e->unk_168 == 7) {
            if (e->dir < 2 || e->dir == 5) {
                e->unk_100 = 0;
                D_800AA248.cur_obj->vel_x.w = 0;
            } else if (e->dir < 5) {
                D_800AA248.cur_obj->flags &= ~0x10;
                e->unk_168 = 7;
                e->unk_100 = 0;
                D_800AA248.cur_obj->vel_x.w = 0;
            } else {
                e->unk_100 = speed;
            }
        } else {
            if (e->dir < 2 || e->dir == 5) {
                e->unk_100 = 0;
                D_800AA248.cur_obj->vel_x.w = 0;
            } else if (e->dir >= 6) {
                D_800AA248.cur_obj->flags |= 0x10;
                e->unk_168 = 3;
                e->unk_100 = 0;
                D_800AA248.cur_obj->vel_x.w = 0;
            } else {
                e->unk_100 = speed;
            }
        }
        if (e->climb_side == 3) {
            u = monster_get_building(e->climb_building);
            x = D_800AA268.p->pos_x.s.hi;
            if (u->state >= 4 || (s16) x < (s16) u->left || u->right < (s16) x) {
                e->climb_side = 0;
            }
        } else if (D_800AA248.cur_obj->pos_y.s.hi != 0xE1) {
            D_800AA248.cur_obj->pos_y.w += 0x18000;
            if (D_800AA248.cur_obj->pos_y.w > 0xE10000) {
                D_800AA248.cur_obj->pos_y.w = 0xE10000;
            }
        }
        break;
    case 5:
        monster_find_roof(e);
        func_8005A0F0();
        break;
    case 4:
        if (e->obj->vel_y.s.hi > 0) {
            city = D_801D3DC8;
            D_800AA248.unk_0C = e->front_x;
            D_800AA248.unk_10 = e->obj->pos_y.s.hi;
            for (i = 0; i < (s16) D_801E29A4; i++) {
                func_80054608(city->priority, e, city);
                city++;
            }
            if (e->action == 0) {
                func_80059D2C();
                func_8001F724(5);
                def = func_8001D110();
                D_800AA284.p = def;
                def->flags = 0x1006;
                def->anim = &D_80016A30;
                def->id = D_80016A30.id;
                def->pos_y.w = e->obj->pos_y.w - 0x50000;
                def->pos_x.w = e->obj->pos_x.w;
                func_8001DCB4();
            }
        }
        break;
    case 1:
    case 2:
    case 6:
    case 7:
        break;
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/monster", func_80052E9C);
#endif

void func_800531C0(Monster *e) {
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    D_800AA248.cur_obj->unk_84 = 0;
    D_800AA248.cur_obj->unk_84 = 0;
    e->unk_100 = 0;
    e->unk_104 = 0;
}

#ifdef NON_MATCHING
/* 96.30%: everything but the camera clamp matches (the if/else adds give both ternary shapes, b declared before a
 * gives the bump's registers). the camera clamp, as in func_800535E4: the original reuses the wrap test's camera
 * load for the first bound (cse-skip-blocks over the wrap) and keeps the %hi of D_801F9AC8 in a0 for every later
 * access, yet reloads the camera word for the second bound and in both clamp arms and loads each bound's constant
 * afresh there: cse knew the HIGH but no longer the MEM, the sums or the constants. No cc1 flag reproduces it
 * (-fno-cse-follow-jumps, -fno-cse-skip-blocks, -fno-thread-jumps, -fno-rerun-cse-after-loop, -fno-expensive-
 * optimizations, -fno-strength-reduce, scheduling, -fno-force-mem: never the reload). Volatile reads of D_801F9AC8
 * after a local camera copy for the wrap test and first bound, with the inverted if (bound test first, the low arm
 * in the else) and v = K; v += camera in the arms, give the original's layout and reloads (97.7 %, left: the high
 * arm's constant reused, the first bound's sum register), but the camera is not volatile: func_80039C98 (npc.c,
 * matched) reuses one load across its joins. Ternary, MIN/MAX, inverted, two-if and stepwise forms tried with plain
 * reads: no reload */
void func_80053204(Monster *e) {
    GameObject *shadow;
    Monster *m;
    GameObject *b;
    GameObject *a;
    s32 v;
    s32 d;

    if (e->unk_218 != NULL) {
        func_80053804((s32) e->unk_218, e);
        return;
    }
    m = e->bump_target;
    if (m != NULL) {
        a = D_800AA268.p;
        b = m->obj;
        if ((a->pos_x.w == b->pos_x.w && a->pos_y.w > b->pos_y.w) || a->pos_x.w >= b->pos_x.w) {
            if (a->pos_y.w > b->pos_y.w) {
                e->bounce_vy = 0x40000;
                e->bounce_dy = -0x8000;
            } else {
                e->bounce_vy = -0x40000;
                e->bounce_dy = 0x8000;
            }
            e->bounce_vx = -0x80000;
            e->bounce_dx = 0x8000;
            e->action = 0x58;
            e->bump_target = 0;
            return;
        }
    }
    shadow = e->shadow;
    e->bump_target = 0;
    switch (e->dir) {
    case 3:
        D_800AA248.cur_obj->vel_x.w = 0x87000;
        D_800AA248.cur_obj->vel_y.w = 0;
        e->action = 0x50;
        break;
    case 2:
        D_800AA248.cur_obj->vel_x.w = 0x77000;
        D_800AA248.cur_obj->vel_y.w = 0x1A000;
        e->action = 0x52;
        break;
    case 4:
        D_800AA248.cur_obj->vel_x.w = 0x77000;
        D_800AA248.cur_obj->vel_y.w = -0x1A000;
        e->action = 0x51;
        break;
    case 7:
        D_800AA248.cur_obj->vel_x.w = 0x7000;
        D_800AA248.cur_obj->vel_y.w = 0;
        e->action = 0x50;
        break;
    case 8:
        D_800AA248.cur_obj->vel_x.w = 0x17000;
        D_800AA248.cur_obj->vel_y.w = 0x1A000;
        e->action = 0x52;
        break;
    case 6:
        D_800AA248.cur_obj->vel_x.w = 0x17000;
        D_800AA248.cur_obj->vel_y.w = -0x1A000;
        e->action = 0x51;
        break;
    case 5:
        D_800AA248.cur_obj->vel_x.w = 0x47000;
        D_800AA248.cur_obj->vel_y.w = -0x34000;
        e->action = 0x51;
        break;
    case 1:
        D_800AA248.cur_obj->vel_x.w = 0x47000;
        D_800AA248.cur_obj->vel_y.w = 0x34000;
        e->action = 0x52;
        break;
    default:
        D_800AA248.cur_obj->vel_x.w = 0x47000;
        D_800AA248.cur_obj->vel_y.w = 0;
        e->action = 0x50;
        break;
    }
    v = D_800AA268.p->pos_x.w;
    if (D_801D3780 != 0) {
        v += 0x40000;
    } else {
        v += D_800AA268.p->vel_x.w;
    }
    if (v <= D_801F9AC8.w) {
        v += D_801D8864.w;
    }
    if (D_801D3780 == 0) {
        if (v < D_801F9AC8.w + 0x500000) {
            v = D_801F9AC8.w + 0x500000;
        } else if (D_801F9AC8.w + 0x1400000 < v) {
            v = D_801F9AC8.w + 0x1400000;
        }
    }
    v &= D_801D8864.w;
    D_800AA248.cur_obj->pos_x.w = v;
    shadow->pos_x.w = v;
    v = D_800AA248.cur_obj->pos_y.w;
    if (D_801D3780 != 0) {
        v += 0x18000;
    } else {
        v += D_800AA248.cur_obj->vel_y.w;
    }
    if (D_801D3780 == 0) {
        if (v < -0x370000) {
            v = -0x370000;
        } else if (v > 0x820000) {
            v = 0x820000;
        }
    }
    D_800AA248.cur_obj->pos_y.w = v;
    shadow->pos_y.w = v;
    shadow->priority = D_800AA248.cur_obj->priority - 1;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/monster", func_80053204);
#endif

#ifdef NON_MATCHING
/* 92.33%: abs() gives the original's in-place negates with the stores before the branches; the if/else adds give
 * both ternary shapes (jump.c turns the one-insn 0x40000 arm into the delay-slot set, the lui/ori 0x18000 arm stays
 * a branch). Left: the step pseudo takes v0 where the original has v1, and the camera clamp, as in func_800535E4:
 * the original reuses the wrap test's camera load for the first bound (cse-skip-blocks over the wrap) and keeps the
 * %hi of D_801F9AC8 in a0 for every later access, yet reloads the camera word for the second bound and in both
 * clamp arms and loads each bound's constant afresh there: cse knew the HIGH but no longer the MEM, the sums or the
 * constants. No cc1 flag reproduces it (-fno-cse-follow-jumps, -fno-cse-skip-blocks, -fno-thread-jumps, -fno-rerun-
 * cse-after-loop, -fno-expensive-optimizations, -fno-strength-reduce, scheduling, -fno-force-mem: never the
 * reload). Volatile reads of D_801F9AC8 after a local camera copy for the wrap test and first bound, with the
 * inverted if (bound test first, the low arm in the else) and v = K; v += camera in the arms, give the original's
 * layout and reloads (97.7 %, left: the high arm's constant reused, the first bound's sum register), but the camera
 * is not volatile: func_80039C98 (npc.c, matched) reuses one load across its joins. Ternary, MIN/MAX, inverted,
 * two-if and stepwise forms tried with plain reads: no reload */
void func_800535E4(Monster *e) {
    GameObject *shadow;
    s32 v;
    s32 step;

    v = e->bounce_vx;
    step = e->bounce_dx;
    shadow = e->shadow;
    e->bump_target = 0;
    e->unk_218 = 0;
    v += step;
    e->bounce_vx = v;
    v = abs(v);
    step = abs(step);
    if (step >= v) {
        e->bounce_dx = 0;
    }
    v = e->bounce_vx;
    D_800AA248.cur_obj->vel_x.w = v;
    v = e->bounce_vy;
    step = e->bounce_dy;
    v += step;
    e->bounce_vy = v;
    v = abs(v);
    step = abs(step);
    if (step >= v) {
        e->bounce_dy = 0;
    }
    v = e->bounce_vy;
    D_800AA248.cur_obj->vel_y.w = v;
    if ((e->bounce_dy | e->bounce_dx) == 0) {
        e->action = 0x50;
    }
    v = D_800AA248.cur_obj->pos_x.w;
    if (D_801D3780 != 0) {
        v += 0x40000;
    } else {
        v += D_800AA248.cur_obj->vel_x.w;
    }
    if (v <= D_801F9AC8.w) {
        v += D_801D8864.w;
    }
    if (D_801D3780 == 0) {
        if (v < D_801F9AC8.w + 0x500000) {
            v = D_801F9AC8.w + 0x500000;
        } else if (D_801F9AC8.w + 0x1400000 < v) {
            v = D_801F9AC8.w + 0x1400000;
        }
    }
    v &= D_801D8864.w;
    D_800AA248.cur_obj->pos_x.w = v;
    shadow->pos_x.w = v;
    v = D_800AA248.cur_obj->pos_y.w;
    if (D_801D3780 != 0) {
        v += 0x18000;
    } else {
        v += D_800AA248.cur_obj->vel_y.w;
    }
    if (D_801D3780 == 0) {
        if (v < -0x370000) {
            v = -0x370000;
        } else if (v > 0x820000) {
            v = 0x820000;
        }
    }
    D_800AA248.cur_obj->pos_y.w = v;
    shadow->pos_y.w = v;
    shadow->priority = D_800AA248.cur_obj->priority - 1;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/monster", func_800535E4);
#endif

void func_80053804(s32 unused, Monster *e) {
    /* LOOP_BLOCK class A2: the plain statements give the original's order only with -fno-schedule-insns
     * -fno-schedule-insns2 (sched2 sinks the two zero stores below the constants); a macro's block, likely. */
    LOOP_BLOCK(e->bounce_vy = 0; e->bounce_dy = 0;);
    e->bounce_vx = 0xFFF60000;
    e->bounce_dx = 0x4000;
    e->action = 0x58;
    e->bump_target = 0;
}

void func_8005382C(u16 kind) {
    D_800AA268.p->unk_8C = D_8007BE0C[kind];
}

s32 monster_test_boxes(s16 x, s16 y, Monster *m) {
    s16 px;
    s16 bx;
    s16 by;

    px = x;
    if (m->unk_0DC == 0 || m->action == 0x37) {
        return 0;
    }
    if (x < D_801F9ACA) {
        px = x + ((D_801D8864.w + 1) >> 16);
    }
    bx = m->box_x0;
    by = m->box_y0;
    if (px >= bx && y >= by) {
        bx = m->box_x1;
        by = m->box_y1;
        if (bx >= px && by >= y) {
            return 1;
        }
    }
    bx = m->box2_x0;
    by = m->box2_y0;
    if (px >= bx && y >= by) {
        bx = m->box2_x1;
        by = m->box2_y1;
        if (bx >= px && by >= y) {
            return 2;
        }
    }
    return 0;
}

u16 monster_test_hit_box(Monster *e, Monster *m) {
    s16 left;
    u16 top;
    u16 right;
    u16 bottom;
    s32 w;
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;

    if (m->unk_0DC == 0) {
        return 0;
    }
    if (D_800AA2DC & 0x7000) {
        if (e->climb_side != 0) {
            if (m->climb_side == 0) {
                return 0;
            }
        } else if (m->climb_side != 0) {
            return 0;
        }
    }
    right = e->hit_right;
    left = e->hit_left;
    top = e->hit_top;
    bottom = e->hit_bottom;
    if (left < D_801F9ACA) {
        w = (D_801D8864.w + 1) >> 16;
        left += w;
        right += w;
    }
    x0 = m->box_x0;
    y0 = m->box_y0;
    x1 = m->box_x1;
    y1 = m->box_y1;
    if (left < x1 && (s16) right > x0 && (s16) top < y1 && (s16) bottom > y0) {
        return 1;
    }
    x0 = m->box2_x0;
    y0 = m->box2_y0;
    x1 = m->box2_x1;
    y1 = m->box2_y1;
    if (left < x1 && (s16) right > x0 && (s16) top < y1 && (s16) bottom > y0) {
        return 2;
    }
    return 0;
}

u16 func_80053AC4(s16 a, s16 b, s16 c, s16 d, Monster *e) {
    if (e->unk_0DC == 0 || e->action == 0x37) {
        return 0;
    }
    return monster_test_point(a, b, c, d, e);
}

s32 monster_test_point(s16 x, s16 y, s16 dx, s16 dy, Monster *e) {
    u16 ax;
    u16 ay;

    if (x < D_801F9ACA) {
        x += (D_801D8864.w + 1) >> 16;
    }
    ax = e->box_x0;
    ay = e->box_y0;
    ax -= dx;
    ay -= dy;
    if (x < (s16) ax || y < (s16) ay) {
        return 0;
    }
    ax = e->box_x1;
    ay = e->box_y1;
    ax += dx;
    ay += dy;
    if ((s16) ax < x || (s16) ay < y) {
        return 0;
    }
    return 1;
}

u16 monster_test_box_x(s16 x, Monster *e) {
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

    if (e->icon_timers[0] == 0 && D_801E2A54 < 9 && D_801FA890 == 0) {
        if ((u32) (e->action - 0x34) >= 2) {
            if (D_800AA2DC == 0) {
                if (e->play_frames < 0x78) {
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

void func_80053DE4(Monster *e) {
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

void func_80053EA8(void) {
    GameObject *obj;
    Monster *m;
    ObjectDef *def;
    u16 x;
    s32 y;
    s16 flip;

    obj = D_800AA268.p;
    y = obj->pos_y.u.hi;
    x = obj->pos_x.u.hi;
    m = obj->owner.monster;
    func_8001F724(0x61);
    if ((u32) (m->climb_side - 1) < 2) {
        s32 sx = (s16) x;

        y = y - 0x13;
        flip = obj->flags & 0x10;
        if (!flip) {
            x = sx - 6;
        } else {
            x = sx + 6;
        }
        flip = (flip == 0) * 0x10;
    } else {
        s32 sx;

        y = y - 0x20;
        flip = obj->flags & 0x10;
        sx = (s16) x;
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
        old = e->score;
        e->score += points;
        score = e->score;
        for (;;) {
            if (score < next) {
                return;
            }
            n++;
            if (old < next) {
                e->lives++;
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
            building_clear_monster(e);
            D_8007A7D4 &= 0xFFFE;
            cdload_sort_players();
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
/* 95.39%: cse, the camera clamp's class: in the facing-left block the original reloads box_x0 but reuses the sign-
 * extended px (a0): cse knew the register expression but not the MEM. Here cse carries box_x0 into that block by
 * skip-blocks as well as follow-jumps (-fno-cse-follow-jumps alone changes nothing); with both off box_x0 is
 * reloaded but px is extended again. A u16 copy of box_x0 for the first bound keeps the size (the reload slot
 * becomes its re-extension, 93.1 %); s16/s32 copies, in-place x0 -= 0x30, casts on either bound, ternary, ||, goto,
 * result-variable and early-return forms tried */
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
INCLUDE_ASM("asm/main/nonmatchings/monster", func_8005453C);
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
    if (x >= (s16) u->left + 8 && u->right - 8 >= x) {
        top = u->top;
        if (top - 4 >= y && top - 4 - y < 0xB && u->priority >= kind) {
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
                e->obj->pos_y.s.hi = u->top + 8;
            }
        }
    }
}

Building *monster_get_building(u16 n) {
    Building *city;
    u16 i;
    u16 count;

    /* The original tests the count as an s16; other units read it u16. */
    if (n == 0 || *(s16 *) &D_801E29A4 == 0) {
        return NULL;
    }
    city = D_801D3DC8;
    count = D_801E29A4;
    i = 1;
    if (i != n) {
        while (1) {
            city++;
            if (--count == 0) {
                break;
            }
            if (++i == n) {
                break;
            }
        }
    }
    return city;
}

void func_8005478C(Monster *e) {
    Building *obj;

    obj = monster_get_building(e->climb_building);
    if (obj != NULL && obj->unk_078 == 0 && obj->unk_058 == 0) {
        func_80031280(e, obj);
    }
}

void monster_grab_building(Monster *e) {
    Building *city;
    u16 x;
    u16 cx;
    s16 d;
    s32 ad;
    s32 w;
    s16 n;

    if (e->unk_18E != 0) {
        return;
    }
    city = D_801D3DC8;
    x = e->front_x;
    D_800AA248.unk_40 = n = D_801E29A4;
    if (n == 0) {
        return;
    }
    D_800AA248.unk_04 = 0;
    do {
        D_800AA248.unk_04++;
        if (city->state < 9) {
            cx = city->left;
            d = x - cx;
            ad = abs(d);
            w = D_801D8864.w >> 16;
            if (ad > w / 2) {
                if ((s16) cx < (s16) x) {
                    cx++;
                    cx += w;
                }
                d = x - cx;
            }
            if ((u16) (d + 0x32) < 0xFA) {
                if (d < 0x32 && monster_test_left_side(x, city) == 1) {
                    if (func_80057AD8(e, city, 1) != 0) {
                        continue;
                    }
                    if (func_800575F0(0, e, city, D_800AA248.unk_04) == 0) {
                        func_800564C0(e, city);
                        func_80055FBC(e, city);
                        return;
                    }
                } else {
                    if (func_80057AD8(e, city, 2) != 0) {
                        continue;
                    }
                    if (monster_test_right_side(x, city) == 1 && func_80057300(0, e, city, D_800AA248.unk_04) == 0) {
                        func_80056510(e, city);
                        func_800560A8(e, city);
                        return;
                    }
                }
            }
        }
        city++;
    } while (--D_800AA248.unk_40 != 0);
}

void func_80054A18(Monster *e) {
    func_800578E0(e, monster_get_building(e->climb_building));
}

void func_80054A50(Monster *e) {
    Building *u;
    GameState *g;
    GameState *h;
    s32 limit;
    u16 kind;

    u = monster_get_building(e->climb_building);
    if (!func_80057AD8(e, u, 2)) {
        monster_find_floor(e, u);
        func_800578E0(e, u);
        g = &D_800AA248;
        if (g->action == 5) {
            g->unk_0C = e->front_x;
            g->unk_10 = g->cur_obj->pos_y.s.hi;
            if ((u32) (g->dir - 4) < 3U) {
                if (func_800573C8(e, u) == 1) {
                    e->unk_104 = 0;
                    g->cur_obj->vel_y.w = 0;
                } else {
                    func_8005640C(e, u);
                }
            } else {
                kind = u->priority;
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

    u = monster_get_building(e->climb_building);
    if (!func_80057AD8(e, u, 1)) {
        monster_find_floor(e, u);
        func_800578E0(e, u);
        g = &D_800AA248;
        if (g->action == 5) {
            g->unk_0C = e->front_x;
            g->unk_10 = g->cur_obj->pos_y.s.hi;
            if ((u32) (g->dir - 4) < 3U) {
                if (func_800576B8(e, u) == 1) {
                    e->unk_104 = 0;
                    g->cur_obj->vel_y.w = 0;
                } else {
                    func_8005640C(e, u);
                }
            } else {
                kind = u->priority;
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
    kind = u->priority;
    if (u == D_801D3DC8 || (func_80054D74(kind, e, city - 1), D_800AA250 != 3)) {
        func_80054D74(kind, e, u + 1);
    }
}

void func_80054D74(u16 kind, Monster *e, Building *u) {
    u16 next;

    if (u->state < 0xB && u->priority >= kind && D_800AA248.unk_0C >= (s16) u->left + 8 &&
        (s16) u->right - 8 >= D_800AA248.unk_0C && D_800AA248.unk_10 >= (s16) u->top - 4) {
        next = u->unk_01E;
        e->climb_side = 3;
        e->climb_building = next;
        D_800AA248.unk_08 = 3;
        e->action = 0;
        D_800AA248.action = 0;
        D_800AA248.cur_obj->pos_y.s.hi = u->top + 8;
    }
}

void func_80054E1C(Monster *e) {
    Building *city;
    s16 y;

    city = monster_get_building(e->climb_building);
    monster_find_floor(e, city);
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

    city = monster_get_building(e->climb_building);
    if (func_80057AD8(e, city, 2) == 0) {
        monster_find_floor(e, city);
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

    city = monster_get_building(e->climb_building);
    if (func_80057AD8(e, city, 1) == 0) {
        monster_find_floor(e, city);
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

    u = monster_get_building(e->climb_building);
    if (!func_80057AD8(e, u, 1)) {
        monster_find_floor(e, u);
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

void func_8005520C(Monster *e) {
    Building *u;
    GameState *g;
    GameState *h;
    s16 d;

    u = monster_get_building(e->climb_building);
    monster_find_floor(e, u);
    func_800578E0(e, u);
    g = &D_800AA248;
    if (g->action != 0xF && g->action != 2 && g->action != 0x4E) {
        g->unk_10 = (s16) u->top + 8;
        g->cur_obj->pos_y.s.hi = g->unk_10;
        if ((u32) (g->dir - 4) < 3U && !func_80057AD8(e, u, 3)) {
            func_80055970(e, u);
            e->action = g->action;
            if (g->action == 0xD) {
                return;
            }
        }
        h = &D_800AA248;
        d = h->unk_0C;
        h->unk_40 = 0;
        d -= u->left;
        if (d <= 0) {
            func_80055454(e, u);
            return;
        }
        if (d < 0x10) {
            func_8005558C(e, u);
            return;
        }
        d = h->unk_0C;
        d = u->right - d;
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

void func_800553B0(Monster *e) {
    Building *obj;

    if (!(D_800AA2DC & 0x38)) {
        obj = monster_get_building(e->climb_building);
        if (!func_80057AD8(e, obj, 1)) {
            monster_find_floor(e, obj);
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
        if (D_800AA248.dir == 1 || D_800AA248.dir == 8) {
            func_80055600(e, city);
        } else {
            func_800554F8(e, city);
        }
    }
}

void func_800554F8(Monster *e, Building *u) {
    if (!(D_800AA2DC & 0x38) && !func_80057AD8(e, u, 1)) {
        if (D_800AA248.dir == 2 || D_800AA248.dir == 4 || D_800AA248.dir == 3) {
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

    obj = monster_get_building(e->climb_building);
    if (!func_80057AD8(e, obj, 2)) {
        monster_find_floor(e, obj);
        func_800578E0(e, obj);
        if (D_800AA25C != 0xF && D_800AA25C != 2 && D_800AA25C != 0x4E) {
            func_80055740(e, obj);
        }
    }
}

void func_80055740(Monster *e, Building *u) {
    D_800AA248.unk_40 = 1;
    if (!func_80057AD8(e, u, 2)) {
        if ((u32) (D_800AA248.dir - 1) < 2U) {
            func_800558AC(e, u);
            return;
        }
        func_800557C8(e, u);
    }
}

void func_800557C8(Monster *e, Building *u) {
    if (!func_80057AD8(e, u, 2)) {
        if (D_800AA248.dir == 8 || D_800AA248.dir == 6 || D_800AA248.dir == 7) {
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
        kind = city->priority;
        start = city;
        if (city == D_801D3DC8) {
            city = &D_801D3DC8[(s16) D_801E29A4 - 1];
        } else {
            city--;
        }
        if (kind < city->priority || city->state >= 0xB) {
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

    kind = city->priority;
    if (city == &D_801D3DC8[(s16) D_801E29A4 - 1]) {
        city = D_801D3DC8;
    } else {
        city++;
    }
    if (kind >= city->priority && city->state < 0xB) {
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

void func_80055CA8(Monster *e) {
    Building *city;
    u16 v;
    u16 action;

    D_800AA248.cur_obj->pos_x.s.hi &= D_801D8866;
    D_800AA248.action = e->action;
    if (D_800AA248.action == 0 || e->action == 0xB || e->action == 0x1C) {
        e->unk_168 = (D_800AA268.p->flags & 0x10) ? 7 : 3;
    }
    if (e->action != 2 && e->action != 0x4E) {
        e->unk_166 = 0;
    }
    v = e->unk_0DE;
    if ((s16) e->unk_0DE != 0) {
        v = 0;
        if (e->action != 3 && e->action != 0x11) {
            e->unk_0DE = 0;
        }
    }
    e->unk_1DE = v;
    D_800AA248.unk_08 = e->climb_side;
    if (D_800AA248.unk_08 == 0 || e->unk_18E != 0) {
        if (e->unk_0DC != 0 || (D_800AA2DC != 0 && (D_8007BD78.flags & 0x100))) {
            e->climb_floor = 0;
            e->climb_building = 0;
            if (D_800AA248.cur_obj->vel_y.w == 0 && e->unk_104 == 0) {
                action = e->action;
                D_800AA248.action = action;
                if (action != 2 && action != 0x11 && action != 0x4E) {
                    if (e->action == 0x37) {
                        if (e->unk_1CC != 4 && e->unk_1CC != 1) {
                            D_800AA248.cur_obj->pos_y.w = 0xDD0000;
                        }
                    } else if (e->unk_18E != 0) {
                        e->climb_side = 0;
                    } else {
                        D_800AA248.cur_obj->pos_y.w = 0xE10000;
                        e->unk_1DE = 1;
                    }
                }
            }
        }
    } else {
        D_800AA248.unk_10 = D_800AA248.cur_obj->pos_y.s.hi;
        D_800AA248.cur_obj = e->obj;
        city = monster_get_building(e->climb_building);
        monster_find_floor(e, city);
        if (D_800AA248.unk_08 == 1) {
            if (D_800AA248.action != 0x10 && D_800AA248.action != 0xD) {
                func_800564C0(e, city);
            }
        } else if (D_800AA248.unk_08 == 2) {
            if (D_800AA248.action != 0x10 && D_800AA248.action != 0xD) {
                func_80056510(e, city);
            }
        } else if (D_800AA248.unk_08 == 3) {
            if (D_800AA248.action != 0x10) {
                func_80056560(e);
            }
        }
    }
    if (D_800AA248.action != 0xC) {
        e->unk_168 = (D_800AA248.cur_obj->flags & 0x10) ? 7 : 3;
    }
    if (e->unk_16C != NULL) {
        func_800544D8(e, e->unk_16C, e->obj);
    }
}

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
        e->prev_action = 0;
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
    e->prev_action = 0;
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
        e->prev_action = 0;
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
    e->prev_action = 0;
}

void func_8005618C(Monster *e, Building *city) {
    D_800AA248.cur_obj->pos_y.w = 0xE10000;
    D_800AA248.action = 0;
    e->action = 0;
    e->climb_building = 0;
    e->climb_side = 0;
    func_8004E8A8();
}

u16 monster_test_left_side(s16 x, Building *city) {
    s16 left;
    s16 cx;
    s16 px;

    left = city->left;
    cx = left;
    px = x;
    if (left < D_801F9ACA) {
        cx += 1 + (D_801D8864.w >> 16);
    }
    if (x < D_801F9ACA) {
        px = x + (1 + (D_801D8864.w >> 16));
    }
    if ((u16) (cx - px + 0x12) >= 0x2D || (u16) city->left_side != 0) {
        return 0;
    }
    D_800AA258 = 0xE0;
    return 1;
}

u16 monster_test_right_side(s16 x, Building *city) {
    s16 left;
    s16 cx;
    s16 px;

    left = city->right;
    cx = left;
    px = x;
    if (left < D_801F9ACA) {
        cx += 1 + (D_801D8864.w >> 16);
    }
    if (x < D_801F9ACA) {
        px = x + (1 + (D_801D8864.w >> 16));
    }
    if ((u16) (cx - px + 0x12) >= 0x2D || (u16) city->right_side != 0) {
        return 0;
    }
    D_800AA258 = 0xE0;
    return 1;
}

u16 func_800562E4(s16 x, Building *city) {
    s16 left;
    s16 cx;
    s16 px;
    s16 d;

    left = city->left;
    cx = left;
    px = x;
    if (left < D_801F9ACA) {
        cx += 1 + (D_801D8864.w >> 16);
    }
    if (x < D_801F9ACA) {
        px = x + (1 + (D_801D8864.w >> 16));
    }
    d = cx - px;
    if (D_800AA258 < (s16) city->top + 0xA || d < -0x10 || d >= 0x19) {
        return 0;
    }
    return 1;
}

u16 func_80056378(s16 x, Building *city) {
    s16 left;
    s16 cx;
    s16 px;
    s16 d;

    left = city->right;
    cx = left;
    px = x;
    if (left < D_801F9ACA) {
        cx += 1 + (D_801D8864.w >> 16);
    }
    if (x < D_801F9ACA) {
        px = x + (1 + (D_801D8864.w >> 16));
    }
    d = cx - px;
    if (D_800AA258 < (s16) city->top + 0xA || d < -0x10 || d >= 0x19) {
        return 0;
    }
    return 1;
}

void func_8005640C(Monster *e, Building *city) {
    u16 n;
    s16 h;
    GameState *g;

    g = &D_800AA248;
    n = e->climb_side;
    g->unk_08 = n;
    if ((s16) city->top + 0x34 >= g->unk_10) {
        h = e->screen_x.s.hi;
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
    D_800AA268.p->pos_x.s.hi = monster_get_building(e->climb_building)->left + 0x28;
}

void func_800564C0(Monster *e, Building *city) {
    D_800AA268.p->pos_x.s.hi = city->left - 0x11;
}

void func_800564D8(Monster *e) {
    D_800AA268.p->pos_x.s.hi = monster_get_building(e->climb_building)->right - 0x28;
}

void func_80056510(Monster *e, Building *u) {
    D_800AA268.p->pos_x.s.hi = u->right + 0x11;
}

void func_80056528(Monster *e) {
    D_800AA268.p->pos_y.s.hi = monster_get_building(e->climb_building)->top + 0x30;
}

void func_80056560(Monster *e) {
    D_800AA268.p->pos_y.s.hi = monster_get_building(e->climb_building)->top + 8;
}

u16 monster_find_roof(e)
Monster *e;
{
    Building *city;
    u16 hit;
    s16 n;

    D_800AA248.unk_08 = e->climb_side;
    D_800AA248.unk_0C = e->front_x;
    city = D_801D3DC8;
    D_800AA248.unk_10 = D_800AA248.cur_obj->pos_y.s.hi;
    n = D_801E29A4;
    D_800AA248.unk_40 = n;
    if (n == 0) {
        return 0;
    }
    D_800AA248.unk_04 = 0;
    do {
        D_800AA248.unk_04++;
        if (city->state < 9 && (u16) (e->front_x - city->left + 0x32) < 0xFA) {
            hit = func_80056708(e, city);
            if (hit == 1) {
                func_800567E8(e, city);
                if (city->unk_058 == 0) {
                    if (D_800AA248.dir == 1) {
                        func_8002D144(e, city);
                    }
                } else {
                    func_8002CFAC(e, city);
                    if (city->unk_058 - 2 >= 2U) {
                        monster_start_jump(e);
                    }
                }
                return 1;
            }
        }
        city++;
    } while (--D_800AA248.unk_40 != 0);
    return 0;
}

s32 func_80056708(Monster *e, Building *u) {
    GameState *g;
    s32 y;
    s16 py;
    s16 top;
    u16 action;

    g = &D_800AA248;
    y = g->cur_obj->pos_y.w;
    g->unk_10 = y;
    action = e->action;
    g->action = action;
    if (action == 0x2C) {
        g->unk_10 = y + 8;
    }
    g->unk_10 -= D_801F9ACC.w;
    if ((u32) (g->unk_10 - 0x500000) > 0xB80000) {
        return 0;
    }
    py = g->cur_obj->pos_y.s.hi;
    g->unk_10 = py;
    if (g->unk_0C < (s16) u->left + 0x10 || (s16) u->right - 0x10 < g->unk_0C || g->unk_08 != 0) {
        return 0;
    }
    top = u->top;
    if (py < top || top + 0x10 < py) {
        return 0;
    }
    return 1;
}

void func_800567E8(Monster *e, Building *city) {
    D_800AA248.cur_obj->pos_y.s.hi = city->top;
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
            d = (s16) city->left - e->front_x;
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

    if (u->left_side < 0) {
        return 0;
    }
    if (D_800AA268.p->pos_y.s.hi < (s16) u->top + 0x30) {
        return 0;
    }
    n = func_80056A44(e, u);
    if ((u16) u->left_side < n && func_800575F0(n, e, u, e->climb_building) != 1) {
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

    kind = city->priority;
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
            d = (s16) city->right - e->front_x;
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

    if (u->right_side < 0) {
        return 0;
    }
    if (D_800AA268.p->pos_y.s.hi < (s16) u->top + 0x30) {
        return 0;
    }
    n = func_80056A44(e, u);
    if ((u16) u->right_side < n && func_80057300(n, e, u, e->climb_building) != 1) {
        func_800560A8(e, u);
        func_80056510(e, u);
        return 1;
    }
    return 0;
}

u16 monster_find_wall(Monster *e) {
    Building *city;
    s32 d;
    s32 d2;
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
        d = (s16) city->right - e->front_x;
        if ((d < 0 ? -d : d) < 0x15 && (u16) func_80056C18(e, city) == 1) {
            return 1;
        }
        d2 = (s16) city->left - e->front_x;
        if ((d2 < 0 ? -d2 : d2) < 0x15 && (u16) func_80056990(e, city) == 1) {
            return 1;
        }
        city++;
    } while (--D_800AA248.unk_40 != 0);
    return 0;
}

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

void monster_find_floor(Monster *e, Building *city) {
    s16 *limit;
    u16 side;
    u16 floor;
    u16 ledge;
    u16 kind;
    u16 y;
    s16 top;

    ledge = 0;
    side = e->climb_side;
    D_800AA248.unk_08 = side;
    y = D_800AA248.cur_obj->pos_y.s.hi;
    floor = 0;
    if (side != 0) {
        D_800AA248.unk_04 = city->unk_000;
        if (D_800AA248.action == 9 || side == 3) {
            D_800AA248.unk_04--;
            floor = D_800AA248.unk_04;
        } else {
            kind = city->priority;
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
            for (;;) {
                floor++;
                if ((u32) floor >= D_800AA248.unk_04) {
                    D_800AA248.unk_04--;
                    floor = D_800AA248.unk_04;
                    break;
                }
                top = *limit++;
                if ((s16) y >= top) {
                    if ((s16) y < (s16) (top + 6)) {
                        ledge++;
                    }
                    break;
                }
            }
        }
    }
    e->climb_floor = floor;
    e->unk_1BC = ledge;
}

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

    p = monster_get_building(e->climb_building)->unk_018;
    if (p != NULL && p->unk_1C == 2) {
        return func_800571D0(e, p);
    }
    return 0;
}

u16 func_80057170(Monster *e) {
    BuildingBlock *p;

    p = monster_get_building(e->climb_building)->unk_018;
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

void func_800578E0(Monster *e, Building *city) {
    u16 n;
    u16 kind;

    if (city == NULL) {
        func_80056E78(e);
        return;
    }
    if (city->unk_058 == 1 && city->state != 0) {
        func_80056EB8(e, city);
        return;
    }
    kind = city->state;
    if (kind >= 0xB) {
        func_80056E78(e);
        return;
    }
    if (kind != 4) {
        if ((u16) func_80057A08(e) == 1) {
            func_80056E78(e);
            return;
        }
        if (D_801D3D64.unk_5E >= 0x1E || (e->screen_y <= 0x700000 && D_801D3D64.unk_58 != 0)) {
            func_80056E2C(e, city);
        }
        return;
    }
    n = city->unk_082;
    if (n >= 0x83) {
        return;
    }
    if ((u16) e->climb_floor < 3) {
        e->action = 0x2B;
        return;
    }
    if (n == 0) {
        func_80056E78(e);
    }
}

u16 func_80057A08(Monster *e) {
    Building *city;
    GameObject *top;

    if (e->climb_side == 0 || e->climb_building == 0) {
        return 0;
    }
    city = monster_get_building(e->climb_building);
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
