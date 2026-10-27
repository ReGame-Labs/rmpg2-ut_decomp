/* The pickups: the eight 0x58-byte Pickup records of D_801FA9BC, made from a spawn list, run by kind and handed to
 * the monster that touches them; also the 0x30-byte records of D_801D3824.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "building.h"     /* the declarations building shares with it */
#include "pickup.h"

extern s16 D_801F9980;
extern s16 D_801F9984;
extern s16 D_801F9988;
extern s32 D_801FA72C;

void func_8004CFC0(void);
void bonus_add_icon(Monster *);

void func_80029D1C(void);
/* The handlers of the D_801FA9BC records by kind (pickup_update): building.c and npc.c. */
void building_update_pickup(Pickup *r);
void func_80034B94(Pickup *r);
void func_800350C0(Pickup *r);
void func_8003537C(Pickup *r);
void func_8003566C(Pickup *r);
void func_80035C4C(Pickup *r);

void pickup_update_all(void);
void pickup_update(Pickup *);
void pickup_clear_all(void);
void pickup_clear(Pickup *);
void func_8003C130(void);
void func_8003C344(void);
void func_8003C080(void);
void func_8003C0AC(void);
void func_8003C0C8(void);
void func_8003C0E0(void);
void func_8003BD48(Pickup *);
void func_8003BF34(GameObject *, Pickup *, u16);   /* the third argument is not used */
extern u8 D_8008A494[];
extern u8 D_8008A4A0[];
extern u8 D_8008A4B8[];
extern u8 D_8008A4C4[];
void func_8003C1C0(u16, UnkStructB2 *);
void func_8003C674();                  /* empty; func_8003C3B0 passes it two arguments */
BuildingPart *func_8003C67C(Building *u, UnkStructB2 *rec);
void func_8003CE24(BuildingPart *p, ObjectDef *def, UnkStructB2 *rec, s32 arg3);
void func_8003C8D4(Pickup *arg0);
void func_8003C934(Pickup *);
void func_8003C9E8(Pickup *arg0);
typedef struct UnkStructB4 {  /* provisional: 8-byte records of D_8007DDD4 (an animation and a value per step) */
    void *unk_00;
    u16 unk_04;
} UnkStructB4;
extern UnkStructB4 D_8007DDD4[];
extern void (*D_8007DDB4[8])(void);
s32 pickup_test_touch(GameObject *, Monster *);
void func_8003CA28(Pickup *arg0);
void func_8003CA70(Pickup *);
void func_8003CADC(Monster *arg0);
void func_8003CB30(Monster *arg0);
void func_8003CCA8(void);
void func_8003CB68(s16, Monster *);
void func_8003CEA0(Anim *, GameObject *);
extern s32 D_800830BC[];
u16 func_8003C858(BuildingPart *, s32, s32);
u16 func_8003CC84(BuildingPart *, s32);
void func_8003C2D4(u16, UnkStructB2 *);
/* The handlers of the D_801D3824 records by kind (func_8003C1C0), in actor.c. */
void func_8003D03C(UnkStructB2 *rec);
void func_8003D0D4(UnkStructB2 *rec);
void func_8003D11C(UnkStructB2 *rec);
void func_8003D228(UnkStructB2 *rec);
void func_8003D30C(UnkStructB2 *rec);
void func_8003D3CC(UnkStructB2 *rec);
void func_8003D5C8(void);


extern s32 D_8007DDA4[];
extern s32 D_8007DB60[];                /* the second sprite of kinds 0xD..0x11 */
extern s32 D_800830AC[];
extern s16 D_801D8748;
void func_800380C0(GameObject *mover);
void func_800346FC(Pickup *r);
void func_80034C54(GameObject *obj);
void func_800634D4(Monster *, u32);
extern GameObject *D_801FB44C[3];

void pickup_update_all(void) {
    Pickup *var_s0;
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
            pickup_update(var_s0);
            temp_v0_2 = var_s1 - 1;
            var_s1 = temp_v0_2;
            var_s0++;
        } while (temp_v0_2 & 0xFFFF);
    }
}

void pickup_update(Pickup *r) {
    D_800AA268.p = r->obj;
    func_80029D1C();
    switch (r->kind) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
        building_update_pickup(r);
        break;
    case 24:
        func_8003566C(r);
        break;
    case 26:
    case 28:
        func_80035C4C(r);
        break;
    case 22:
    case 23:
        func_80034B94(r);
        break;
    case 27:
        func_800350C0(r);
        break;
    case 20:
    case 21:
        func_8003537C(r);
        break;
    }
}

void pickup_clear_all(void) {
    u16 n = 8;
    Pickup *p = D_801FA9BC;

    do {
        pickup_clear(p);
        p++;
    } while (--n != 0);
    D_801E29B0 = 0;
}

void pickup_spawn_all(void) {
    Anim *anim;
    SpawnItem *item;
    Pickup *r;
    GameObject *obj;
    GameObject *part;
    ObjectDef *def;
    u16 n;

    pickup_clear_all();
    item = (SpawnItem *)func_80025C08(D_8007DDA4);
    n = item->unk_04;
    item++;
    if (n == 0) {
        return;
    }
    if (n > 8) {
        n = 8;
    }
    D_801E29B0 = n;
    r = D_801FA9BC;
    do {
        D_800AA248.new_def = func_8001D110();
        def = D_800AA248.new_def;
        anim = item->anim;
        def->anim = anim;
        def->id = anim->id;
        r->unk_0A = 0;
        r->unk_08 = 1;
        r->kind = item->unk_04;
        obj = func_8001DCB4();
        r->obj = obj;
        obj->owner.p = r;
        obj->pos_x.u.hi = item->unk_06;
        obj->pos_y.u.hi = item->unk_08;
        obj->flags |= item->unk_0A;
        obj->priority = item->unk_0C;
        if (r->kind != 0x17) {
            obj->priority = obj->pos_y.u.hi + 0xF23;
        }
        obj->kind = 0x71A;
        if (item->unk_0E == -1) {
            r->unk_1C = func_8001EB10(0xC8, 0x64);
        } else {
            r->unk_1C = item->unk_0E;
        }
        if (r->kind != 0x16 && r->kind != 0x17) {
            func_800380C0(obj);
        }
        if (r->kind >= 0xD && r->kind < 0x12) {
            obj->priority += 2;
            D_800AA248.new_def = func_8001D110();
            def = D_800AA248.new_def;
            def->id = D_8007DB60[r->kind - 0xD];
            if (r->kind == 0xD && (obj->flags & 0x10)) {
                def->id = 0x080027EA;
            }
            if (r->kind == 0xF && (obj->flags & 0x10)) {
                def->id = 0x080027F4;
            }
            r->unk_40 = func_8001DCB4();
            r->unk_40->flags = obj->flags;
            r->unk_40->priority = obj->priority + 1;
            r->unk_40->kind = 0x71A;
            r->unk_40->pos_x.u.hi = obj->pos_x.u.hi;
            r->unk_40->pos_y.u.hi = obj->pos_y.u.hi;
        }
        item++;
        r++;
    } while (--n != 0);
}

void pickup_clear(Pickup *p) {
    memset(p, 0, sizeof(Pickup));
    D_801E29B0 = 0;
}

#ifdef NON_MATCHING
/* 91.74%: the shape is right (the negu-then-add copies, the swap); registers differ, and the original loads the y
 * before the flags */
s32 pickup_test_touch(GameObject *obj, Monster *m) {
    SpriteFrame *box;
    s16 x;
    u16 y;
    s32 flip;
    u16 dx;
    u16 dy;
    u16 w;
    u16 h;
    s16 left;
    s16 right;
    s16 top;
    s16 bottom;
    s16 l;
    s16 r;
    s16 m_right;
    s16 m_left;
    s16 m_top;
    s16 m_bottom;

    x = obj->pos_x.s.hi;
    box = obj->frame;
    if (x < D_801F9ACA) {
        x += (D_801D8864.w + 1) >> 16;
    }
    flip = obj->flags & 0x10;
    dx = box->unk_10;
    dy = box->unk_12;
    y = obj->pos_y.u.hi;
    if (flip) {
        dx = -dx;
    }
    left = dx + x;
    l = left;
    w = box->unk_14;
    h = box->unk_16;
    top = dy + y;
    if (flip) {
        w = -w;
    }
    right = w + x;
    r = right;
    bottom = h + y;
    if (flip) {
        l = right;
        r = left;
    }
    m_bottom = m->hit_bottom;
    m_right = m->hit_right;
    m_left = m->hit_left;
    m_top = m->hit_top;
    if (l < m_right && m_left < r && top < m_bottom && m_top < bottom) {
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/pickup", pickup_test_touch);
#endif





void pickup_collect(Monster *e) {
    u16 n;
    Pickup *r;
    GameObject *obj;
    s32 i;

    n = D_801E29B0;
    r = D_801FA9BC;
    if (n == 0) {
        return;
    }
    do {
        if (!(r->obj->unk_6C & 0x80) && r->unk_08 == 2 && r->kind != 0 && r->kind < 0x1D) {
            if (r->kind >= 0xD && r->kind < 0x12 && r->unk_40 != NULL && pickup_test_touch(r->unk_40, e) != 0) {
                e->unk_024++;
                func_80054374(0x28, e);
                r->unk_54 = e;
                r->unk_44 = D_800AA248.cur_obj->flags;
                r->unk_4E = e->pos.u.lo;
                r->unk_50 = e->pos.u.hi;
                if (e->icon_timers[1] != 0) {
                    r->unk_1A += 10;
                }
                e->unk_18A = 1;
                func_800346FC(r);
                func_800634D4(e, 4);
            }
            if (r->kind == 0x16 || r->kind == 0x17) {
                for (i = 0; i < 3; i++) {
                    obj = D_801FB44C[i];
                    if (obj != NULL && pickup_test_touch(obj, e) != 0) {
                        func_8001F724(0x60);
                        func_80034C54(obj);
                        D_801FB44C[i] = NULL;
                    }
                }
            }
            if (pickup_test_touch(r->obj, e) != 0) {
                e->unk_024++;
                func_80054374(0x28, e);
                r->unk_08 = 3;
                r->unk_54 = e;
                r->unk_44 = D_800AA248.cur_obj->flags;
                r->unk_4E = e->pos.u.lo;
                r->unk_50 = e->pos.u.hi;
                if (e->icon_timers[1] != 0) {
                    r->unk_1A += 10;
                }
                e->unk_18A = 1;
                func_800634D4(e, 4);
                return;
            }
        }
        r++;
    } while (--n != 0);
}

#ifdef NON_MATCHING
/* 85 %: the original loads the limit once into v0 and copies it to v1 (a separate variable from the tested
 * value); every form tried loads it once into the variable or twice. */
void func_8003BD48(Pickup *b) {
    s32 limit;
    u16 x;
    u16 d;
    GameObject *obj;

    if (b->unk_08 == 2) {
        if (D_801FAC84 != 0) {
            limit = D_801FAC84;
            obj = D_800AA268.p;
            x = obj->pos_x.u.hi;
            if (obj->flags & 0x10) {
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
                obj = D_800AA268.p;
                x = obj->pos_x.u.hi;
                if (obj->flags & 0x10) {
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
INCLUDE_ASM("asm/main/nonmatchings/pickup", func_8003BD48);
#endif

s32 func_8003BE34(Pickup *rec) {
    D_800AA248.cur_obj->vel_y.w += rec->unk_30;
    D_800AA248.cur_obj->pos_y.w += D_800AA248.cur_obj->vel_y.w;
    D_800AA248.cur_obj->vel_x.w += rec->unk_34;
    D_800AA248.cur_obj->pos_x.w += D_800AA248.cur_obj->vel_x.w;
    D_800AA248.cur_obj->pos_x.w &= D_801D8864.w;
    if (rec->unk_3E != 0) {
        if (D_800AA248.cur_obj->unk_6C & 0x80) {
            D_800AA248.result = 1;
            return 1;
        }
        D_800AA248.result = 0;
        return 0;
    }
    if (!(D_800AA248.cur_obj->unk_6C & 0x80)) {
        rec->unk_3E = 1;
    }
    D_800AA248.result = 0;
    return 0;
}


void func_8003BF34(GameObject *obj, Pickup *b, u16 x) {
    u8 *anim = NULL;
    u16 flags;
    GameObject *o;

    if (b->kind == 0x16 || b->kind == 0x17) {
        b->unk_0A = 1;
        return;
    }
    if (b->kind >= 0xD && b->kind < 0x12) {
        b->unk_0A = 1;
        return;
    }
    flags = obj->flags;
    obj->flags = (flags & 0x10) ? (flags & 0xFFEF) : (flags | 0x10);
    b->unk_34 = -b->unk_34;
    obj->vel_x.w = -obj->vel_x.w;
    switch (b->kind) {
    case 6:
        anim = D_8008A4A0;
        b->kind = 7;
        break;
    case 7:
        anim = D_8008A494;
        b->kind = 6;
        break;
    case 8:
        anim = D_8008A4C4;
        b->kind = 9;
        break;
    case 9:
        anim = D_8008A4B8;
        b->kind = 8;
        break;
    }
    if (anim != NULL) {
        func_8001E698(b->obj, anim);
    }
    o = b->unk_40;
    if (o != NULL) {
        o->flags = obj->flags;
    }
}

void func_8003C080(void) {
    (D_800AA248.cur_obj->owner.item)->unk_06 = 0;
    func_8004CFC0();
}

void func_8003C0AC(void) {
    D_800AA248.cur_obj->owner.ai->unk_0C = 1;
}

void func_8003C0C8(void) {
    D_800AA248.cur_obj->owner.ai->unk_1C.s = 0;
}

void func_8003C0E0(void) {
}

void func_8003C0E8(void) {
    s32 i;

    i = func_8001EB10(0x1F, 0);
    D_8007DDB4[i & 7]();
}












void func_8003C130(void) {
    UnkStructB2 *p = D_801D3824;
    u16 n = D_801D8738;
    GameObject *saved = D_800AA268.p;

    if (n != 0) {
        do {
            if (p->unk_04 != 0) {
                func_8003C1C0(p->unk_1C, p);
            }
            p++;
        } while (--n != 0);
    }
    D_800AA268.p = saved;
}

void func_8003C1C0(u16 kind, UnkStructB2 *rec) {
    D_800AA268.p = rec->obj;
    func_80029D1C();
    if (rec->unk_04 == 1) {
        func_8003C2D4(rec->kind, rec);
    } else if (rec->unk_18 > 0) {
        if (--rec->unk_18 == 0) {
            func_8003D5C8();
        }
    } else {
        switch (kind) {
        case 0:
            func_8003D0D4(rec);
            break;
        case 1:
            func_8003D228(rec);
            break;
        case 2:
            func_8003D3CC(rec);
            break;
        case 3:
            func_8003D11C(rec);
            break;
        case 9:
            func_8003D03C(rec);
            break;
        case 11:
            func_8003D30C(rec);
            break;
        }
    }
}

void func_8003C2D4(u16 k, UnkStructB2 *rec) {
    s32 *t;

    if (rec->unk_10->unk_06 >= 5) {
        rec->unk_04 = 2;
        if ((u16) (k - 1) < 0x4A) {
            t = (s32 *) ((k << 2) + (u32) D_800830BC);
            func_8003CEA0(*t, rec->obj);
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

#ifdef NON_MATCHING
/* 98.84%: the statements are right; the original reloads the spilled list pointer and the constant 1 of the
 * D_801D8748 test into a3 (here t0), so reload_cse drops the call's li a3,1 */
void func_8003C3B0(void) {
    SpawnItem *list;
    SpawnItem *item;
    UnkStructB2 *rec;
    Building *u;
    ObjectDef *def;
    BuildingPart *p;
    u16 *q;
    GameObject *obj;

    if (D_800AA2DC != 0) {
        return;
    }
    func_8003C344();
    list = (SpawnItem *)func_80025C08(D_800830AC);
    D_800AA248.unk_00 = func_8001EB10(10, 0);
    if (D_800AA248.unk_00 != 0) {
        D_800AA248.unk_00--;
    }
    rec = D_801D3824;
    D_800AA248.unk_08 = 0x1C;
    item = &list[D_800AA248.unk_00];
    def = func_8001D110();
    u = D_801D3DC8;
    def->pos_x.s.hi = -400;
    def->pos_y.s.hi = -400;
    do {
        D_800AA248.unk_28 = (u16)u->unk_00A;
        if (D_800AA248.unk_28 != 0) {
            do {
                p = func_8003C67C(u, rec);
                if (p != NULL) {
                    if ((u16)p->unk_14 != 0) {
                        def->flags = 0;
                    } else {
                        q = func_8003D1F8((s32)p);
                        func_8003C674(q, def);
                        def->flags = q[4] - 1;
                    }
                    if (D_801D8748 != 1 || item->unk_0A == 0) {
                        func_8003CE24(p, def, rec, 1);
                        def->anim = item->anim;
                        def->id = item->anim->id;
                        def->unk_0C = 0x780;
                        D_800AA248.new_def = def;
                        obj = func_8001DCB4();
                        if (obj == NULL) {
                            goto done;
                        }
                        rec->obj = obj;
                        if (p->unk_04 != 2) {
                            obj->flags &= ~0x10;
                        }
                        obj->owner.p = rec;
                        rec->unk_1C = item->unk_0C;
                        rec->kind = item->unk_04;
                        rec->unk_0A = item->unk_06;
                        rec->unk_0C = item->unk_08;
                        rec->unk_08 = item->unk_0A;
                        rec->unk_1A = item->unk_0E;
                        p->unk_0C = rec;
                        rec->unk_10 = p;
                        rec->unk_18 = -1;
                        rec->unk_04 = 1;
                    }
                }
                rec++;
                item++;
                if (item->unk_04 == 0) {
                    item = list;
                }
                if (--D_800AA248.unk_08 == 0) {
                    goto done;
                }
            } while (--D_800AA248.unk_28 != 0);
        }
        u++;
    } while (u->unk_000 != 0);
done:
    D_801D8738 = 0x1C - (u16)D_800AA250;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/pickup", func_8003C3B0);
#endif

void func_8003C674(void) {
}

#ifdef NON_MATCHING
/* 81.9 %: the control flow is the original's (a first try, then a do-while stepping through the parts); the original compares top with a register holding 2 that it reuses as the random draw's argument, keeps the draw in a0, and is 3 instructions longer */
BuildingPart *func_8003C67C(Building *u, UnkStructB2 *rec) {
    BuildingItem *item;
    BuildingItem *next;
    BuildingPart *part;
    u32 top;
    u32 idx;
    u16 i;

    D_801F9988 = u->unk_01E;
    top = u->unk_000 - 1;
    i = 0;
    if (top > 2) {
        idx = func_8001EB10(top, 2) + (D_801FA72C & 3);
        if (idx > top) {
            idx -= top;
            if (idx == 0) {
                idx = 2;
            }
        }
    } else {
        idx = 2;
    }
    D_801F9984 = idx;
    item = u->items;
    if (idx == 1) {
        item = &u->items[1];
    } else {
        item += idx - 1;
    }
    D_801F9980 ^= 1;
    part = &item->unk_0C;
    if (D_801F9980 != 0) {
        part = &item->unk_24;
    }
    if (func_8003C858(part, (s32)item, (s32)rec) != 1) {
        do {
            i++;
            if (i >= 4) {
                D_801F9980 = part->unk_04 - 1;
                return NULL;
            }
            if (part->unk_04 < 2) {
                part++;
            } else {
                next = (BuildingItem *)(part + 2);
                if (top < next->unk_04) {
                    item = &u->items[1];
                    part = &u->items[1].unk_0C;
                    D_801F9980 = 1;
                    D_801F9984 = 2;
                } else {
                    part = &next->unk_0C;
                }
            }
        } while (func_8003C858(part, (s32)item, (s32)rec) != 1);
    }
    D_801F9980 = part->unk_04 - 1;
    return part;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/pickup", func_8003C67C);
#endif

u16 func_8003C858(BuildingPart *p, s32 arg1, s32 arg2) {
    if (p->unk_08 == 0 && p->unk_0C == 0 && p->unk_04 != 3) {
        return 1;
    }
    return 0;
}










void func_8003C894(void **arg0) {
    void *temp_a0;

    temp_a0 = *arg0;
    if (temp_a0 != NULL) {
        func_8001E4B0(temp_a0);
    }
    func_8003CCC0(arg0);
}

void func_8003C8D4(Pickup *arg0) {
    void *temp_a0;

    temp_a0 = arg0->obj;
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

void func_8003C934(Pickup *rec) {
    GameObject *saved;
    UnkStructB4 *step;
    u16 k;

    saved = D_800AA248.cur_obj;
    rec->unk_04 = 8;
    D_800AA248.cur_obj = rec->obj;
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
        func_8001E698(D_800AA248.cur_obj, step->unk_00);
    }
    D_800AA268.p = saved;
}


void func_8003C9E8(Pickup *arg0) {
    if (arg0->unk_1A == 0xA) {
        func_8003CA28(arg0);
        return;
    }
    func_8003CA70(arg0);
}

void func_8003CA28(Pickup *arg0) {
    Monster *temp_v1;

    temp_v1 = arg0->unk_14;
    if ((temp_v1 != NULL) && ((u32) (arg0->kind - 0x45) < 2U)) {
        func_8003CADC(temp_v1);
    }
}

void func_8003CA70(Pickup *rec) {
    Monster *a;
    s32 kind;

    a = rec->unk_14;
    if (a != NULL) {
        kind = rec->kind;
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




void func_8003CADC(Monster *arg0) {
    s16 var_v1;

    func_8001F724(3);
    var_v1 = 0x294;
    if (arg0->unk_186 != 0) {
        var_v1 = 0x528;
        arg0->unk_186 = 0U;
    }
    arg0->icon_timers[0] = var_v1;
    arg0->icon_kind = 1;
    bonus_add_icon(arg0);
}

void func_8003CB30(Monster *arg0) {
    func_8001F724(3);
    arg0->icon_timers[2] = 0x294;
    arg0->icon_kind = 3;
}

void func_8003CB68(s16 n, Monster *a) {
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
    a->icon_timers[1] = v;
    a->icon_kind = 2;
    bonus_add_icon(a);
}





















s32 func_8003CBE0(Pickup *rec, Monster *a) {
    s32 kind;

    if (a == NULL) {
        goto fail;
    }
    switch (a->id) {
    case 1:
        kind = 4;
        break;
    case 2:
        kind = 5;
        break;
    case 3:
        kind = 6;
        break;
    case 4:
        kind = 1;
        break;
    case 5:
        kind = 2;
        break;
    case 6:
        kind = 3;
        break;
    case 7:
        kind = 7;
        break;
    default:
        goto fail;
    }
    if (kind != rec->kind) {
fail:
        return 0;
    }
    rec->unk_1A = 0xB;
    a->unk_146 = 0x5A;
    a->icon_kind = 7;
    return 1;
}







u16 func_8003CC84(BuildingPart *p, s32 hit) {
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

