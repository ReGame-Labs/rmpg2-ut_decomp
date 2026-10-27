/* The buildings: the 0x584-byte records of D_801D3DC8, their items, parts and blocks, what monsters do to them and
 * what falls from them. The file starts with the sky (the clouds, the thunder, the rain and the snow) and ends with
 * the handlers of the Ai kinds 1 to 12 (D_8007DE44) and their animation states.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "building.h"
#include "npc.h"

void func_800634D4(Monster *, u32);

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

void func_8002A3A4(void) {
    ObjectDef *def;
    GameObject *obj;
    s32 chance;
    s32 rain;
    s32 players;

    D_8007C976 = 0;
    chance = D_8007CB4C[D_801FA960];
    D_801FB190.unk_00 = 0;
    players = D_8007A690;
    rain = chance >> 16;
    if (players == 1) {
        if (func_8001EAC4(100) < rain) {
            D_8007C976 = players;
        } else if (func_8001EAC4(100) < (s16) chance) {
            D_8007C976 = 2;
        }
    }
    def = func_8001D110();
    def->unk_1C = 1;
    def->id = 0x4F00097E;
    def->flags = 0x50;
    D_800AA248.new_def = def;
    obj = func_8001DCB4();
    obj->pos_x.s.hi = -100;
    obj->pos_y.s.hi = -100;
    D_801FB194 = obj;
    obj->unk_6C |= 0x10;
    func_8001B054(obj);
    def->id = 0x4F000982;
    D_800AA248.new_def = def;
    obj = func_8001DCB4();
    obj->pos_x.s.hi = -100;
    obj->pos_y.s.hi = -100;
    D_801FB420 = obj;
    obj->unk_6C |= 0x10;
    func_8001B054(obj);
}

void building_set_sky_colours(void) {
    s32 colour;
    s32 *c;

    D_801FB41C = 0x808080;
    colour = D_8007CD40[D_801FA960 - 100];
    D_801FA9A4 = colour;
    if (colour == 0) {
        D_801F9A38 = 0;
        return;
    }
    D_801F9A38 = 1;
    c = D_8007CAFC;
    D_801FAC80->unk_74 = c[3];
    D_801FAC80->unk_75 = c[4];
    D_801FAC80->unk_76 = c[5];
    D_801FAC80->unk_7C = D_801FAC80->unk_74;
    D_801FAC80->unk_7D = D_801FAC80->unk_75;
    D_801FAC80->unk_7E = D_801FAC80->unk_76;
    D_801FAC80->unk_84 = c[0];
    D_801FAC80->unk_85 = c[1];
    D_801FAC80->unk_86 = c[2];
    D_801FAC80->unk_8C = D_801FAC80->unk_84;
    D_801FAC80->unk_8D = D_801FAC80->unk_85;
    D_801FAC80->unk_8E = D_801FAC80->unk_86;
    D_801FAC80->unk_98 = c[6];
    D_801FAC80->unk_99 = c[7];
    D_801FAC80->unk_9A = c[8];
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


INCLUDE_ASM("asm/main/nonmatchings/building", func_8002A72C);

void func_8002AC34(GameObject *obj) {
    s16 d;

    if (D_8007C976 == 0) {
        if (D_801FB198 > 0x12430) {
            main_set_frame(0x4F00097E, obj->flags, obj);
            obj->pos_x.s.hi = (D_801FB198 - 0x12430) / 58 + 0xF0;
            obj->pos_y.s.hi = 0x82 - (D_801FB198 - 0x12430) / 78;
        } else if (D_801FB198 > 0x2A30 && D_801FB198 < 0xA8C0) {
            main_set_frame(0x4F000980, obj->flags, obj);
            d = (0xA8C0 - D_801FB198) / 54 + 0x81;
            obj->pos_x.s.hi = 0x122;
            obj->flags |= 0x400;
            obj->pos_y.s.hi = 0x82 - D_801FB198 / d;
            D_801FB420->pos_x.s.hi = obj->pos_x.s.hi;
            D_801FB420->pos_y.s.hi = obj->pos_y.s.hi;
        }
    }
}

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

void func_8002ADE8(void) {
    D_801FAC80->unk_74 = 0xA0;
    D_801FAC80->unk_75 = 0xA0;
    D_801FAC80->unk_76 = 0x80;
    D_801FAC80->unk_7C = 0xA0;
    D_801FAC80->unk_7D = 0xA0;
    D_801FAC80->unk_7E = 0x80;
    D_801FAC80->unk_98 = 0xA0;
    D_801FAC80->unk_99 = 0xA0;
    D_801FAC80->unk_9A = 0x80;
    D_801FAC80->unk_A0 = 0xA0;
    D_801FAC80->unk_A1 = 0xA0;
    D_801FAC80->unk_A2 = 0x80;
    D_801FAC80->unk_A8 = 0xA0;
    D_801FAC80->unk_A9 = 0xA0;
    D_801FAC80->unk_AA = 0x80;
    D_801FAC80->unk_B0 = 0xA0;
    D_801FAC80->unk_B1 = 0xA0;
    D_801FAC80->unk_B2 = 0x80;
    D_801FA9A4 = (D_801FAC80->unk_98 << 16) | (D_801FAC80->unk_99 << 8) | D_801FAC80->unk_9A;
    D_801FB41C = ((((D_801FB41C >> 16) & 0xFF) + 0x20) << 16) | ((((D_801FB41C >> 8) & 0xFF) + 0x20) << 8) | ((D_801FB41C & 0xFF) + 0x20);
}

void building_update_sky(void) {
    s32 i;
    s32 r;

    if (D_8007C976 == 1) {
        for (i = 0; i < 80; i++) {
            building_update_cloud(i);
        }
        if (D_8007C979 != 0) {
            func_8002ADE8();
            D_8007C979--;
            return;
        }
        if (D_8007C97A != 0) {
            D_8007C97A--;
            return;
        }
        if (D_8007C978 != 0) {
            D_8007C978--;
        }
        switch (D_8007C978) {
        case 1:
        case 2:
        case 3:
        case 4:
            D_8007C979 = 1;
            D_8007C97A = 1;
            break;
        case 5:
            D_8007C979 = 4;
            D_8007C97A = 1;
            break;
        default:
            r = func_8001EA78() & 0x1FF;
            if (r == 9) {
                D_8007C978 = 6;
                D_8007C979 = (func_8001EA78() & 3) + 9;
                D_8007C97A = 2;
                r = func_8001EA78() & 1;
                func_8001F724(r + 0x27);
            }
            break;
        }
    }
    if (D_8007C976 == 2) {
        if (D_801FA960 >= 100 && D_801D8728 == 0) {
            for (i = 0; i < 40; i++) {
                building_update_snowflake(i);
            }
        } else {
            for (i = 0; i < 80; i++) {
                building_update_raindrop(i);
            }
        }
    }
}

void building_update_cloud(s32 i) {
    GameObject *obj;
    ObjectDef *def;
    s32 *ids;
    s32 mask;
    u16 r;

    mask = ((s16 *) func_80025C08(D_800838A0))[1];
    if (D_801FB19C[i] != 0) {
        D_801FB19C[i]--;
        return;
    }
    if (D_801FB2DC[i] == NULL) {
        def = func_8001D110();
        if ((func_8001EA78() & 0xFF) < 0x80) {
            def->id = 0x4F000966;
            ids = D_8007CB2C;
        } else {
            def->id = 0x4F000968;
            ids = D_8007CB3C;
        }
        def->unk_1C = 2;
        def->flags = 0x1005;
        D_800AA284.p = def;
        obj = func_8001DCB4();
        obj->unk_40.ids = ids;
        obj->script.pc = 0;
        obj->pos_x.s.hi = (((D_801F9ACA - 400) & mask) + func_8001EA78() % 800) & mask;
        obj->pos_y.s.hi = -100;
        if (D_801FA960 > 100 && D_801D8728 == 0) {
            obj->unk_74 = 0x52;
        }
        obj->vel_x.w = 6;
        D_801FB2DC[i] = obj;
    } else {
        obj = D_801FB2DC[i];
        if (obj->pos_y.s.hi >= 0xD8) {
            obj->pos_y.s.hi = 0xDD;
            if ((u32) obj->script.pc < 4) {
                main_set_frame(obj->unk_40.ids[obj->script.pc], obj->flags, obj);
                obj->script.pc++;
            } else {
                if ((func_8001EA78() & 0xFF) < 0x80) {
                    main_set_frame(0x4F000966, obj->flags, obj);
                } else {
                    main_set_frame(0x4F000968, obj->flags, obj);
                }
                obj->script.pc = 0;
                obj->pos_x.s.hi = (((D_801F9ACA - 400) & mask) + func_8001EA78() % 800) & mask;
                r = func_8001EA78();
                obj->pos_y.s.hi = (D_801F9ACC.w >> 16) - ((r & 0x1F) + 50);
                return;
            }
        } else {
            obj->pos_x.u.hi = (obj->pos_x.u.hi + obj->vel_x.u.lo) & mask;
            obj->pos_y.u.hi += obj->vel_x.u.lo;
        }
    }
    obj->flags |= 0x400;
}

void building_update_raindrop(s32 i) {
    GameObject *obj;
    ObjectDef *def;
    s32 mask;
    u16 r;

    mask = ((s16 *) func_80025C08(D_800838A0))[1];
    if (D_801FB19C[i] != 0) {
        D_801FB19C[i]--;
        return;
    }
    if (D_801FB2DC[i] == NULL) {
        def = func_8001D110();
        if ((func_8001EA78() & 0xFF) < 0x80) {
            def->id = 0x4F00097A;
        } else {
            def->id = 0x4F00401A;
        }
        def->unk_1C = 2;
        def->flags = 0x1005;
        D_800AA284.p = def;
        obj = func_8001DCB4();
        obj->script.pc = 0;
        obj->pos_x.s.hi = (((D_801F9ACA - 100) & mask) + func_8001EA78() % 600) & mask;
        obj->pos_y.s.hi = -100;
        obj->vel_x.w = func_8001EA78() & 0xFFFF;
        if ((func_8001EA78() & 0xFF) < 0x80) {
            obj->vel_x.w = -obj->vel_x.w;
        }
        obj->vel_y.w = 4;
        D_801FB2DC[i] = obj;
        return;
    }
    obj = D_801FB2DC[i];
    if (obj->pos_y.s.hi >= 0xD8) {
        obj->pos_y.s.hi = 0xDD;
        if ((u32) obj->script.pc < 6) {
            main_set_frame(0x4F00097C, obj->flags, obj);
            obj->script.pc++;
            return;
        }
        if ((func_8001EA78() & 0xFF) < 0x80) {
            main_set_frame(0x4F00097A, obj->flags, obj);
        } else {
            main_set_frame(0x4F00401A, obj->flags, obj);
        }
        obj->script.pc = 0;
        obj->pos_x.s.hi = (((D_801F9ACA - 100) & mask) + func_8001EA78() % 600) & mask;
        r = func_8001EA78();
        obj->pos_y.s.hi = (D_801F9ACC.w >> 16) - ((r & 0x1F) + 50);
    } else {
        obj->pos_x.w += obj->vel_x.w;
        obj->pos_y.u.hi += obj->vel_y.u.lo;
    }
}

void func_8002B640(void) {
    D_800AA248.cur_obj->pos_x.s.hi = (((D_801F9ACA - 400) & (D_801D8864.w >> 16)) + func_8001EA78() % 800) & D_801D8864.w;
    D_800AA248.cur_obj->pos_y.s.hi = -100;
    func_8003EB5C(&D_80097E30, D_800AA248.cur_obj);
}

void building_update_snowflake(s32 i) {
    GameObject **slot;
    GameObject *obj;
    ObjectDef *def;
    s32 mask;
    s32 dy;

    mask = ((s16 *) func_80025C08(D_800838A0))[1];
    if (D_801FB19C[i] != 0) {
        D_801FB19C[i]--;
        return;
    }
    slot = &D_801FB2DC[i];
    if (*slot == NULL) {
        def = func_8001D110();
        def->anim = &D_80097E30;
        def->id = D_80097E30.id;
        def->unk_1C = 2;
        def->flags = 0x1005;
        D_800AA284.p = def;
        obj = func_8001DCB4();
        obj->pos_x.s.hi = (((D_801F9ACA - 400) & mask) + func_8001EA78() % 800) & mask;
        dy = (func_8001EA78() & 0x1F) + 50;
        obj->pos_y.s.hi = (D_801F9ACC.w >> 16) - dy;
        obj->vel_x.w = 8;
        *slot = obj;
        return;
    }
    obj = *slot;
    if (obj->pos_y.s.hi >= 0xD8) {
        obj->pos_y.s.hi = 0xDD;
        func_8003EB5C(D_80097E64, obj);
    } else {
        obj->pos_x.u.hi = (obj->pos_x.u.hi + obj->vel_x.u.lo) & mask;
        obj->pos_y.u.hi += obj->vel_x.u.lo;
    }
}

void func_8002B878(void) {
    s32 i;
    s32 n;
    s32 mode;

    mode = 1;
    n = 0;
    for (i = 0; i < 7; i++) {
        if (D_801FA8A0[i] != 0) {
            n++;
        }
    }
    if (n >= 3) {
        mode = 0;
    }
    D_801D8740 = 0;
    for (i = 0; i < 7; i++) {
        if (D_801FA8A0[i] != 0 && func_8001AA4C(D_8007CDA4[i][0], D_8007CDA4[i][mode + 3]) != 0) {
            func_8001AB30(D_8007CDA4[i][1], D_8007CDA4[i][2]);
            D_801D8740++;
        }
    }
}

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
            building_reset_monster(temp_s0);
            temp_a0 = func_8002BA30(temp_s0);
            if (D_8007A7D4 & 1) {
                temp_v0 = D_8007A688 - 1;
                temp_a0->lives_shown = temp_v0;
                temp_a0->lives = temp_v0;
            }
        }
        var_s1 += 1;
    } while (var_s1 < 7);
}

Monster *func_8002BA30(s32 arg0) {
    Monster *temp_a1;

    temp_a1 = &D_801E0B78[arg0 & 0xFFFF];
    if (D_8007A7D4 & 1) {
        temp_a1->health.w = 0x440000;
    }
    return temp_a1;
}

void building_reset_monster(s32 n) {
    Monster *m;
    GameObject *saved;

    m = &D_801E0B78[(u16) n];
    saved = D_800AA248.cur_obj;
    building_clear_monster(m);
    m->id = n;
    m->unk_128 = n;
    building_spawn_monster(m);
    D_800AA248.cur_obj = saved;
}


void building_spawn_monster(Monster *m) {
    ObjectDef *def;
    GameObject *obj;
    s32 i;
    s32 other;   /* read unset when no other monster has a player: the original's bug, kept */
    s32 unused[2];  /* never used: the original frame has 8 bytes for it */

    m->unk_0EC = 0;
    m->buttons = 0;
    m->unk_058 = 1;
    D_800AA248.new_def = func_8001D110();
    def = D_800AA248.new_def;
    def->pos_y.s.hi = 0xE1;
    def->id = D_8007CDEC[m->id - 1];
    def->anim = &D_80096560;
    def->flags = 0x1004;
    obj = func_8001DCB4();
    D_800AA248.cur_obj = obj;
    obj->kind = 0x74A;
    m->unk_01E = m->id;
    m->unk_178 = m->id;
    switch (D_801D8740) {
    case 1:
        D_800AA248.cur_obj->pos_x.s.hi = 200;
        break;
    case 2:
        for (i = 0; i < 7; i++) {
            if (m->id != i + 1 && D_801FA8A0[i] != 0) {
                other = D_801FA8A0[i];
            }
        }
        if (D_801FA8A0[m->id - 1] < other) {
            D_800AA268.p->pos_x.s.hi = 0x89;
        } else {
            D_800AA268.p->pos_x.s.hi = 0x106;
        }
        break;
    default:
        D_800AA268.p->pos_x.s.hi = (D_801FA8A0[m->id - 1] - 2) * 125 + 200;
        break;
    }
    D_800AA248.cur_obj->unk_72 = D_8007CDA4[m->id - 1][0];
    if (m->id == 7) {
        D_800AA248.cur_obj->unk_74 = D_801F9ABC;
    } else {
        D_800AA248.cur_obj->unk_74 = 0;
    }
    D_800AA248.cur_obj->unk_8C = (m->id < 2) ? 2 : 4;
    func_8001E2B8(D_800AA248.cur_obj);
    m->obj = D_800AA248.cur_obj;
    D_800AA248.cur_obj->owner.monster = m;
    m->unk_01C = 0;
    m->unk_046 = 0;
    m->unk_1E0 = 0;
    m->unk_1E2 = 0;
    m->unk_174 = -1;
    if (m->unk_01A & 0xF) {
        func_8002A1AC(m, m->unk_01A & 0xF);
    }
    if (D_800AA2DC == 0) {
        bonus_create_bars(m);
        bonus_create_lives(m);
        bonus_create_score(m);
        func_8005E124(m, 0x7A0);
        return;
    }
    switch (bonus_get_round_kind()) {
    case 2:
        bonus_create_counter(1, D_801FA8A0[m->id - 1]);
        bonus_create_lives(m);
        break;
    case 3:
        bonus_create_counter(2, D_801FA8A0[m->id - 1]);
        bonus_create_lives(m);
        break;
    case 4:
        bonus_create_bars(m);
        bonus_create_lives(m);
        break;
    }
}

void building_clear_monster(Monster *arg0) {
    s32 unused[2];  /* never used: the original frame has 8 bytes for it */

    if (D_8007A7D4 & 1) {
        memset(arg0, 0, 0x220);
    } else {
        memset(&arg0->unk_058, 0, 0x1C0);
    }
}

void func_8002BE78(Building *b) {
    GameObject *obj;

    if (b->unk_010 >= b->unk_012) {
        if (b->unk_076 != 0) {
            b->state = 0xF;
        } else if (b->def == (BuildingDef *) D_80011BA4) {
            b->state = 9;
        } else if (b->def == (BuildingDef *) D_80011BA4_alt) {
            b->state = 9;
        } else {
            obj = b->falling;
            if (obj != NULL) {
                D_800AA268.p = obj;
                obj->vel_y.w = 0x28000;
                obj->unk_88 = 0xB00;
                func_8003CCC0(obj->owner.p);
                b->unk_016 = 0;
                b->state = 0xD;
            } else {
                b->state = 9;
            }
        }
    }
}

void func_8002BF24(Monster *arg0, Building *arg1) {
    if (arg1->unk_016 < arg1->unk_000) {
        func_8002DF64(arg0, arg1);
        return;
    }
    arg1->state = 0xE;
    arg1->unk_030 = 0;
    arg1->unk_016 = 0;
}

s32 func_8002BF70(Building *a) {
    Building *p;
    u16 n;
    u16 i;

    i = a->unk_01E;
    p = D_801D3DC8;
    n = i;
    if (n != 0) {
        do {
            if (p->unk_01E < n && p->state < 0x11 && p->unk_058 == 0) {
                return 0;
            }
            p++;
        } while (--i != 0);
    }
    return 1;
}






void func_8002BFE4(Monster *arg0, Building *arg1) {
    s32 temp_s0;

    temp_s0 = func_8002BF70(arg1) & 0xFFFF;
    if (temp_s0 == 1) {
        if ((func_8004F7A4(arg1) & 0xFFFF) == temp_s0) {
            if ((u16) arg1->unk_016 < (u16) arg1->unk_000) {
                func_8002E278(arg0, arg1);
                return;
            }
            arg1->state = 0xE;
            goto block_8;
        }
        arg1->state = 0x11;
        if (D_801E1E40 == temp_s0) {
            D_801FA890 = 0xB4;
        } else {
            D_801E1E40 = (u16) D_801E1E40 - 1;
        }
block_8:
        arg1->unk_030 = 0;
        arg1->unk_016 = 0U;
    }
}

void func_8002C0AC(Monster *arg0, Building *arg1) {
    if (arg1->unk_016 < arg1->unk_000) {
        func_8002E0C8(arg0, arg1);
        return;
    }
    arg1->state = 0x10;
    arg1->unk_030 = 0;
    arg1->unk_016 = 0;
}

void func_8002C0F8(s32 n, Building *a) {
    void (**handler)(Building *);
    s32 saved;

    if (a->unk_016 < a->unk_000) {
        handler = D_8007CFD0;
        if (a->unk_076 != 1) {
            a->state = 9;
            return;
        }
        handler += a->unk_076;
        saved = D_800AA248.unk_18;
        D_800AA248.unk_18 = n;
        (*handler)(a);
        D_800AA248.unk_18 = saved;
        return;
    }
    a->state = 0xE;
    a->unk_030 = 0;
    a->unk_016 = 0;
}




void func_8002C19C(Building *arg0) {
    if ((u16) arg0->unk_02A < 0x18U) {
        func_8002EB00();
        return;
    }
    arg0->state = 0;
    arg0->unk_02A = 1U;
    arg0->unk_02C = 0;
    arg0->unk_02E = 0;
}

void func_8002C1E8(Building *arg0) {
    if (arg0->unk_030 != 0) {
        func_8002ED90(arg0);
        return;
    }
    arg0->state = 0;
    arg0->unk_00C = 0;
}

void func_8002C228(Building *arg0) {
    func_8002FEA4(arg0);
    arg0->unk_030 = 0;
    arg0->unk_016 = 0;
    arg0->state = 0xB;
}

void func_8002C25C(Building *arg0) {
    if (arg0->unk_016 != arg0->unk_000) {
        func_8002E854();
        func_80030B5C(arg0);
        return;
    }
    arg0->state = 0x10;
    arg0->unk_030 = 0;
    arg0->unk_016 = 0U;
}

s32 func_8002C2B4(Building *a) {
    s32 done;

    done = 0;
    func_8002E9A4(a);
    func_8002EBD8(a);
    a->state = 0x11;
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
void func_8002C32C(Building *a) {
    if (a->unk_000 > a->unk_016) {
        func_8002D9F8(a);
        return;
    }
    if (a->falling != NULL) {
        func_8001E698(a->falling, a->kind == 2 ? D_8001236C : D_8001236C_alt);
        a->falling = NULL;
    }
    a->state = 0x10;
    a->unk_030 = 0;
    a->unk_016 = 0;
}




void func_8002C3C4(Building *arg0) {
    u16 temp_v0;

    temp_v0 = arg0->unk_082;
    if (temp_v0 != 0) {
        arg0->unk_082 = (u16) (temp_v0 - 1);
        return;
    }
    if (arg0->unk_000 == arg0->unk_016) {
        func_8002F084(arg0);
        return;
    }
    func_8002E854(arg0);
    func_80030B5C(arg0);
}

void func_8002C430(Building *arg0) {
    if (arg0->unk_090 != NULL) {
        arg0->state = 4;
        return;
    }
    if (arg0->unk_036 > arg0->unk_038) {
        arg0->state = 0;
        arg0->unk_036 = 0;
        arg0->unk_038 = 0;
        func_80025BBC(arg0);
        if (arg0->unk_034 == 1) {
            arg0->unk_034 = 2;
            return;
        }
        arg0->unk_034 = 1;
        return;
    }
    func_8002E9F8(arg0);
}

void building_update_all(void) {
    GameObject *saved;
    Building *b;
    Building *p;
    u16 n;

    saved = D_800AA248.cur_obj;
    if (D_801D36FC == 0x150) {
        building_count_standing();
        b = p = D_801D3DC8;
        n = D_801E29A4;
        if (n == 0) {
            D_800AA248.cur_obj = saved;
            return;
        }
        do {
        if (b->unk_058 == 0) {
            switch (b->state) {
            case 17:
                if (b->unk_07C != NULL) {
                    func_800300A0((UnkStruct15 *) b->unk_07C, b);
                }
                break;
            case 0:
                func_8002BE78(b);
                break;
            case 9:
                func_8002BF24(NULL, b);
                break;
            case 10:
                func_8002BFE4(NULL, b);
                break;
            case 12:
                func_8002C0AC(NULL, b);
                break;
            case 15:
                func_8002C0F8(0, b);
                break;
            case 2:
                func_8002C19C(b);
                break;
            case 3:
                func_8002C1E8(b);
                break;
            case 14:
                func_8002C228(b);
                break;
            case 11:
                func_8002C25C(b);
                break;
            case 16:
                if ((u16) func_8002C2B4(b) == 1) {
                    n = 1;
                }
                break;
            case 13:
                func_8002C32C(b);
                break;
            case 4:
                func_8002C3C4(b);
                break;
            case 1:
                func_8002C430(b);
                break;
            }
        } else {
            func_8002C8B4(b);
        }
            p++;
            b = p;
        } while (--n != 0);
        D_800AA268.p = saved;
    }
}

/* An old-style definition: its callers pass the actor they already hold in a0 without naming it. */
void func_8002C6A0(a)
Building *a;
{
    GameObject *obj;
    GameObject *spr;

    obj = a->falling;
    D_800AA268.p = obj;
    if (obj != NULL) {
        func_8001E698(obj, D_80011E48);
        func_8002CBF4((Monster *) a);
        a->falling = NULL;
    }
    func_8002EBD8(a);
    spr = a->items[0].obj;
    spr->priority = 0x20A;
    if (D_801E1E40 != 0) {
        if (D_801E1E40 == 1) {
            D_801FA890 = 0xB4;
        } else {
            D_801E1E40--;
        }
        func_8001E698(spr, a->unk_060);
    }
}



void func_8002C738(Building *arg0) {
    arg0->state = 0x10;
    func_8002C6A0();
}

void func_8002C75C(Building *arg0) {
    GameObject *temp_s1;

    temp_s1 = arg0->items[0].obj;
    D_800AA248.cur_obj = temp_s1;
    if (((u16) arg0->state) == 6) {
        arg0->state = 8U;
    } else {
        arg0->state = 0U;
    }
    if (arg0->unk_058 != 3) {
        func_8001F724(5);
        func_8001E698(temp_s1, arg0->unk_05C);
    }
}

void func_8002C7D0(Building *arg0) {
    if (arg0->falling == 0) {
        arg0->state = 6;
        func_8002C75C(arg0);
        return;
    }
    arg0->state = 8;
    func_8002C738(arg0);
}

void func_8002C814(Building *arg0) {
    void *temp_a0;

    func_8001F724(5);
    temp_a0 = arg0->falling;
    arg0->state = 0;
    if (temp_a0 != NULL) {
        func_8001E698(temp_a0, D_80011E18);
    }
}

void func_8002C858(Building *arg0) {
    u16 temp_v0;
    u16 temp_v1;

    temp_v0 = arg0->unk_082;
    if (temp_v0 != 0) {
        arg0->unk_082 = (u16) (temp_v0 - 1);
        return;
    }
    temp_v1 = arg0->unk_000;
    if (temp_v1 == arg0->unk_016) {
        func_8002F084();
        return;
    }
    arg0->unk_016 = temp_v1;
    func_8002C6A0();
}

void func_8002C8B4(Building *b) {
    GameObject *saved;
    Monster *m;

    saved = D_800AA248.cur_obj;
    if (b->unk_090 != NULL) {
        b->state = 4;
    }
    if (b->state != 0x10) {
        if (b->unk_032 >= 1 && b->unk_032 <= 7 && b->unk_058 == 1 && (m = &D_801E0B78[b->unk_032])->icon_timers[1] != 0) {
            func_8002C7D0(b);
            D_800AA248.cur_obj = saved;
            return;
        }
        if (b->unk_010 >= b->unk_012) {
            if (b->state < 2) {
                func_8002C7D0(b);
                D_800AA268.p = saved;
                return;
            }
        } else if (b->state == 0) {
            b->unk_032 = 0;
            D_800AA268.p = saved;
            return;
        }
        switch (b->state) {
        case 5:
            if (b->unk_058 != 3) {
                func_8002C75C(b);
            } else {
                func_8002F100(b);
            }
            D_800AA268.p = saved;
            return;
        case 7:
            if (b->unk_058 != 3) {
                func_8002C814(b);
            } else {
                func_8002F100(b);
            }
            break;
        case 8:
            func_8002C738(b);
            break;
        case 4:
            func_8002C858(b);
            break;
        default:
            b->unk_032 = 0;
            D_800AA268.p = saved;
            return;
        }
    }
    b->unk_032 = 0;
    D_800AA268.p = saved;
}

void func_8002CA8C(void) {
    GameObject *saved = D_800AA248.cur_obj;
    Building *owner = saved->owner.item->building;
    ObjectDef *r;
    GameObject *spr;
    s32 *anim;

    D_800AA248.new_def = func_8001D110();
    anim = D_80011E10;
    r = D_800AA248.new_def;
    r->anim = anim;
    r->id = D_80011E10[0];
    r->pos_x.u.hi = saved->pos_x.u.hi;
    r->pos_y.u.hi = saved->pos_y.u.hi;
    r->flags = saved->priority - 1;
    spr = func_8001DCB4();
    owner->falling = spr;
    spr->owner.building = owner;
    spr->kind = 0x749;
    if (func_8001A3AC() < 0x23) {
        D_800AA248.cur_obj = saved;
        return;
    }
    if (D_8007A690 == 1) {
        anim = D_80011E90;
    } else {
        r->pos_x.u.hi = spr->pos_x.u.hi + 0x14;
        anim = D_80011E68;
        r->pos_y.u.hi = spr->pos_y.u.hi - 0x32;
    }
    r->anim = anim;
    r->id = *anim;
    r->flags += 5;
    spr = func_8001DCB4();
    spr->kind = 0x749;
    spr->owner.item = (BuildingItem *) owner;
    if (D_8007A690 != 1) {
        spr->flags |= 0x400;
    }
    D_800AA268.p = saved;
}

void func_8002CBF4(Monster *m) {
    GameObject *saved = D_800AA248.cur_obj;
    GameObject *body;
    ObjectDef *r;
    GameObject *spr;
    s32 *anim;

    if (func_8001A3AC() >= 0x46) {
        body = m->icons[0];
        r = func_8001D110();
        D_800AA248.new_def = r;
        if (m->unk_058 == 3) {
            anim = D_80011ED8;
        } else if (D_8007A690 == 1) {
            anim = D_80011ED0;
        } else {
            anim = D_80011E68;
        }
        r->anim = anim;
        r->id = *anim;
        r->pos_x.u.hi = body->pos_x.u.hi;
        r->pos_y.u.hi = body->pos_y.u.hi;
        r->flags = body->priority + 5;
        spr = func_8001DCB4();
        if (m->unk_058 != 3 && D_8007A690 != 1) {
            spr->flags |= 0x400;
            spr->pos_x.u.hi += 0x14;
            spr->pos_y.u.hi -= 0x32;
        }
        D_800AA268.p = saved;
    }
}

BuildingItem *func_8002CD24(u16 idx, Monster *a, BuildingItem *rec) {
    Ai *q = NULL;
    BuildingPart *r;
    u16 k;

    if (rec->building->unk_070 == rec) {
        rec--;
        func_8002CE74(idx, a, rec);
    } else if (a->icon_timers[1] != 0) {
        func_80030E04(a, rec);
    } else {
        r = func_8002ED30(idx, rec);
        k = r->unk_06;
        func_8002DBF4(idx, 5, a, rec);
        if (r->unk_06 == k) {
            func_8003089C(0xFFFF, a);
        } else {
            func_8003089C(r->unk_06, a);
        }
        q = (Ai *) r->unk_0C;
        if (q != NULL) {
            if ((u16) q->unk_1C.s != 3 || q->unk_04 < 0xC) {
                func_8002CE40(q, a);
            } else {
                q = NULL;
            }
        }
    }
    return (BuildingItem *) q;
}

void func_8002CE40(Ai *arg0, Monster *arg1) {
    if ((arg0->obj != 0) && ((u16) arg0->unk_04 >= 2U)) {
        arg0->unk_0E = 1;
        arg0->target = arg1;
    }
}

void func_8002CE74(u16 idx, Monster *a, BuildingItem *rec) {
    BuildingPart *part;
    u16 top;

    if (a->icon_timers[1] != 0) {
        func_80030E04(a, rec);
        return;
    }
    top = 0xFFFF;
    if (rec->building->unk_070 != rec && rec->unk_06 == 0) {
        part = func_8002ED30(idx, rec);
        top = 0;
        if (part->unk_10 == NULL) {
            func_8002DBF4(idx, 0, a, rec);
        } else {
            top = 1;
            if (part->unk_16 == 0) {
                func_8002DE08(idx, 1, a, rec);
            } else {
                top = 5;
                if (part->unk_06 == 0) {
                    func_8002DBF4(idx, 5, a, rec);
                } else if (part->unk_06 < 5) {
                    func_8002DE08(idx, 5, a, rec);
                } else {
                    top = 0xFFFF;
                }
            }
        }
    }
    func_8003089C(top, a);
    func_8002FA20(a, rec);
}

void func_8002CFAC(Monster *m, Building *b) {
    u16 v;

    if (b->unk_058 == 2 && D_801E1E40 != 1) {
        func_8001F724(0x2B);
        return;
    }
    if (b->unk_058 == 3 && D_801E1E40 != 1) {
        func_8001F724(0x2B);
        return;
    }
    if (b->state != 0x10) {
        v = 5;
        if (b->unk_010 != 0) {
            v = 7;
            if (b->unk_010 >= b->unk_012) {
                v = 8;
                goto done;
            }
        }
        b->unk_010++;
        if ((u16) (b->unk_058 - 2) >= 2) {
            func_8001F724(0x4D);
        }
        func_8003111C(1, m);
        func_80031154(5, m);
        b->unk_032 = m->id;
        m->unk_18A = 1;
done:
        b->state = v;
    }
}

void func_8002D0C0(Monster *arg0, Building *arg1) {
    GameObject *temp_s2;

    temp_s2 = D_800AA248.cur_obj;
    if (arg1->unk_078 == 0) {
        func_8002F5B0(arg0, arg1);
        func_8003089C(5, arg0);
    } else {
        func_8002D448(arg0, arg1);
    }
    arg1->unk_078 = (u16) (arg1->unk_078 + 1);
    D_800AA248.cur_obj = temp_s2;
}

void func_8002D144(Monster *arg0, Building *arg1) {
    s32 temp_s2;

    temp_s2 = D_800AA248.cur_obj;
    if ((D_800AA2DC == 0) || !(D_8007BD78.flags & 0x40)) {
        if (arg1->unk_078 == 0) {
            func_8002F5B0(arg0, arg1);
            func_8003089C(5, arg0);
        } else {
            func_8002D228(arg0, arg1);
        }
        arg1->state = 1;
        arg1->unk_078 = (u16) (arg1->unk_078 + 1);
        D_800AA248.cur_obj = temp_s2;
    }
}

void func_8002D1F4(Monster *arg0, BuildingItem *arg1) {
    if (arg1->unk_06 == 0) {
        func_8002D370(arg0, arg1, arg1->building);
    }
}

void func_8002D228(Monster *arg0, Building *arg1) {
    BuildingItem *temp_s0;

    temp_s0 = arg1->unk_070;
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

s32 func_8002D2CC(s32 arg0, Building *arg1) {
    if ((arg1->unk_088 != 0) || (arg1->def == D_80011BA4) || ((arg1->left_side != 0) && ((s16) ((u16) arg1->left_side - 1) == (arg0 & 0xFFFF))) || ((arg1->right_side != 0) && ((s16) ((u16) arg1->right_side - 1) == (arg0 & 0xFFFF))) || ((arg1->unk_026 != 0) && ((s16) ((u16) arg1->unk_026 - 1) == (arg0 & 0xFFFF)))) {
        return 1;
    }
    return arg1->unk_076 != 0;
}

void func_8002D370(Monster *a, BuildingItem *b, Building *c) {
    u16 i = 0;
    u16 n = building_pick_part(c);

    while (1) {
        i++;
        if (func_8002ED30(n, b)->unk_06 < 5) {
            break;
        }
        if (i >= c->kind) {
            func_8002FA20(a, b);
            return;
        }
        n++;
        if (c->kind < n) {
            n = 1;
        }
    }
    func_8002DBF4(n, 6, a, b);
    func_8003089C(5, a);
}

void func_8002D448(Monster *m, Building *b) {
    BuildingItem *rec;
    BuildingPart *p;
    u16 mode = 0;
    u16 tries;
    u16 idx;

    rec = b->unk_070;
    rec--;
    while (rec->unk_06 != 0) {
        rec--;
        if (rec->unk_04 < 2) {
            b->unk_010 = b->unk_012;
            return;
        }
    }
    if (m->icon_timers[1] != 0) {
        func_8002E440(m, rec);
        return;
    }
    tries = 0;
    idx = building_pick_part(b);
    for (;;) {
        p = func_8002ED30(idx, rec);
        if (p->unk_06 == 0) {
            mode = 1;
            if (p->unk_10 != NULL) {
                mode = 5;
            }
            break;
        }
        if (p->unk_06 < 5) {
            mode = 5;
            break;
        }
        tries++;
        if (tries >= b->kind) {
            func_8002FDC0(m, rec);
            func_8003089C(mode, m);
            return;
        }
        idx++;
        if (idx > b->kind) {
            idx = 1;
        }
    }
    func_8002DBF4(idx, mode, m, rec);
    func_8003089C(mode, m);
}

#ifdef NON_MATCHING
/* 92.52%: 92.5%: the control flow and the shared restore at the end are the original's; the original keeps rec in
 * t0 (here a2, so F65C's move a2 is gone, 2 instructions short) and allocates m/saved/next/p0/p1 differently */
void func_8002D844(BuildingPart *p0, BuildingPart *p1, Monster *a, BuildingPart *p2, BuildingItem *rec);

void func_8002D5B8(Monster *m, BuildingItem *rec) {
    GameObject *saved;
    Building *b;
    BuildingItem *next;
    BuildingItem *prev;
    BuildingPart *p0;
    BuildingPart *p1;
    BuildingPart *p2;
    s32 side;
    u16 n;
    u16 r;
    u16 l;
    u16 both;

    saved = D_800AA268.p;
    if (m->icon_timers[1] != 0) {
        func_80030E04(m, rec);
        goto end;
    }
    b = rec->building;
    if (b->unk_070 == rec || b->state != 0) {
        goto end;
    }
    if (rec->unk_04 < 2) {
        goto single;
    }
    b->unk_02C = rec->unk_04;
    side = 1;
    if (m->obj->flags & 0x10) {
        side = 2;
    }
    b->unk_02E = side;
    b->state = 2;
    if (b->unk_02E == 1) {
        p0 = &rec->unk_0C;
        p1 = &rec->unk_24;
    } else {
        p0 = &rec->unk_24;
        p1 = &rec->unk_0C;
    }
    p2 = NULL;
    if (b->kind != 2) {
        p2 = &rec->unk_3C;
    }
    n = rec->unk_06;
    if (n == 0) {
    place:
        func_8002D844(p0, p1, m, p2, rec);
        goto end;
    }
    if (n == 2) {
        goto end;
    }
    if (b->unk_012 < 0x23) {
        goto collapse;
    }
    next = rec + 1;
    prev = rec - 1;
    r = next->unk_06;
    l = prev->unk_06;
    both = r | l;
    if (both == 0) {
        if (!(func_8001EB10(0x8000, 0) & 1)) {
            goto go_next;
        }
        goto go_prev;
    }
    if (both == 3 && n == 1) {
        goto collapse;
    }
    if (r & l) {
        goto collapse;
    }
    if (l == 0) {
        goto go_prev;
    }
go_next:
    rec = next;
    if (b->unk_070 == next) {
        func_8002F5B0(m, b);
        goto end;
    }
    p0 = (BuildingPart *)((BuildingItem *)p0 + 1);
    p1 = (BuildingPart *)((BuildingItem *)p1 + 1);
    if (p2 != NULL) {
        p2 = (BuildingPart *)((BuildingItem *)p2 + 1);
    }
    goto place;
go_prev:
    rec = prev;
    if (prev->unk_04 == 1) {
    single:
        if (rec->unk_06 == 0) {
            func_8002FAA4(m, rec);
            D_800AA268.p = saved;
            return;
        }
        rec++;
        if (rec->unk_06 == 0) {
            func_8002D1F4(m, rec);
        }
        goto end;
    }
    p0 = (BuildingPart *)((BuildingItem *)p0 - 1);
    p1 = (BuildingPart *)((BuildingItem *)p1 - 1);
    if (p2 != NULL) {
        p2 = (BuildingPart *)((BuildingItem *)p2 - 1);
    }
    goto place;
collapse:
    func_8002F65C(b, (s32)m, rec);
end:
    D_800AA268.p = saved;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/building", func_8002D5B8);
#endif

void func_8002D844(BuildingPart *p0, BuildingPart *p1, Monster *a, BuildingPart *p2, BuildingItem *rec) {
    GameObject *saved;
    u16 top;
    u16 arg;

    saved = D_800AA268.p;
    top = 0;
    if (p0->unk_06 == 0) {
        func_8002DBF4(p0->unk_04, 2, a, rec);
        top = p0->unk_06;
    } else {
        if (p0->unk_06 != 6) {
            func_8002DE08(p0->unk_04, 6, a, rec);
            top = p0->unk_06;
        }
        if (p2 != NULL && p2->unk_06 == 0) {
            func_8002DBF4(p2->unk_04, 4, a, rec);
            if (top < p2->unk_06) {
                top = p2->unk_06;
            }
        } else {
            if (p2 != NULL && p2->unk_06 != 5) {
                func_8002DE08(p2->unk_04, 5, a, rec);
                if (top < p2->unk_06) {
                    top = p2->unk_06;
                }
            }
            if (p1->unk_06 == 0) {
                func_8002DBF4(p1->unk_04, 3, a, rec);
                if (top < p1->unk_06) {
                    top = p1->unk_06;
                }
            } else if (p1->unk_06 < 5) {
                func_8002DE08(p1->unk_04, 5, a, rec);
                if (top < p1->unk_06) {
                    top = p1->unk_06;
                }
            }
        }
        func_8002FA20(a, rec);
    }
    arg = top;
    if (top == 0) {
        arg = 0xFFFF;
    }
    func_8003089C(arg, a);
    D_800AA268.p = saved;
}

void func_8002D9F8(Building *a) {
    GameObject *obj;
    GameObject *saved;
    BuildingItem *rec;

    obj = a->falling;
    saved = D_800AA248.cur_obj;
    D_800AA248.cur_obj = obj;
    func_8003D158(obj);
    rec = a->unk_070;
    rec -= a->unk_016;
    if (obj->pos_y.s.hi + obj->unk_1C.s.hi >= rec->obj->pos_y.s.hi + 0x18) {
        func_8002F898(a, rec);
        a->unk_016++;
    }
    D_800AA248.cur_obj = saved;
}

void *func_8002DAAC(u16 which, u16 n, BuildingItem *rec) {
    s32 **p;
    s32 *t;
    s32 r;
    u16 k;

    r = 0;
    if (n < 7) {
        k = rec->building->unk_01C;
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



s32 func_8002DB3C(u16 which, u16 n, BuildingItem *rec) {
    BuildingPart *g;
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
                if (v == n || v >= 5) {
                    result = 1;
                } else {
                    result = 2;
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

void func_8002DBF4(u16 which, u16 n, Monster *a, BuildingItem *rec) {
    GameObject *saved;
    GameObject *obj;
    ObjectDef *req;
    SpriteFrame *ofs;
    BuildingPart *slot;
    u16 r;
    u16 dx;
    u16 dy;
    s32 anim;

    saved = D_800AA248.cur_obj;
    if (rec->building->unk_070 != rec) {
        r = func_8002DB3C(which, n, rec);
        if (r != 1) {
            if (r == 3) {
                if (n >= 5) {
                    func_8002E5F4(which, rec);
                }
                anim = (s32) func_8002DAAC(which, n, rec);
                if (anim != 0) {
                    D_800AA248.new_def = func_8001D110();
                    req = D_800AA248.new_def;
                    req->id = anim;
                    req->unk_0C = 0x715;
                    ofs = rec->obj->frame;
                    switch (which) {
                    case 1:
                        dx = ofs->unk_10;
                        dy = ofs->unk_12;
                        slot = &rec->unk_0C;
                        break;
                    case 2:
                        req->unk_04 |= 0x10;
                        dx = ofs->unk_20;
                        dy = ofs->unk_22;
                        slot = &rec->unk_24;
                        break;
                    default:
                        dx = ofs->unk_18;
                        dy = ofs->unk_1A;
                        slot = &rec->unk_3C;
                        break;
                    }
                    req->pos_x.u.hi = rec->obj->pos_x.u.hi + dx;
                    req->pos_y.u.hi = rec->obj->pos_y.u.hi + dy;
                    req->flags = rec->obj->priority + 7;
                    obj = func_8001DCB4();
                    D_800AA268.p = obj;
                    if (obj != NULL) {
                        if (n < 2) {
                            slot->unk_10 = obj;
                            slot->unk_16 = n;
                        } else {
                            slot->unk_00 = obj;
                            slot->unk_06 = n;
                        }
                    }
                } else {
                    goto end;
                }
            } else if (r == 2) {
                func_8002DE08(which, n, a, rec);
            } else {
                goto end;
            }
            func_80030698(n, a, rec);
            func_8002FA20(a, rec);
        }
    }
end:
    D_800AA268.p = saved;
}






void func_8002DE08(which, n, arg2, rec)
u16 which;
s16 n;
Monster *arg2;
BuildingItem *rec;
{
    GameObject *saved = D_800AA268.p;
    void *t;
    BuildingPart *g;
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
        D_800AA268.p = obj;
        if (obj != NULL) {
            if ((u16) n >= 5) {
                if ((u16) n != 6 || g->unk_06 != 5) {
                    func_8002E5F4(which, rec);
                }
            }
            main_set_frame(t, obj->flags, obj);
            func_80030754(g, n, arg2, rec);
            if ((u16) n < 2) {
                g->unk_16 = n;
            } else {
                g->unk_06 = n;
            }
        }
    }
    D_800AA268.p = saved;
}

void func_8002DF64(Monster *arg0, Building *arg1) {
    if (arg1->unk_000 < 6U) {
        func_8002DFA8(arg0, arg1);
        return;
    }
    func_8002E148(arg0, arg1);
}

void func_8002DFA8(Monster *arg0, Building *arg1) {
    GameObject *temp_s2;
    u16 temp_v1;
    u16 temp_v1_2;
    u16 var_s0;
    BuildingItem *temp_a1;
    BuildingItem *temp_a1_2;

    temp_v1 = (u16) arg1->unk_030;
    temp_s2 = D_800AA248.cur_obj;
    if (temp_v1 != 0) {
        arg1->unk_030 = temp_v1 - 1;
    } else {
        temp_a1 = arg1->items;
        if (arg1->unk_016 == 0) {
            func_8002FAA4(arg0, temp_a1);
        } else {
            temp_a1_2 = &temp_a1[arg1->unk_016];
            temp_v1_2 = temp_a1_2->unk_04;
            if (temp_v1_2 == arg1->unk_000) {
                func_8002F5B0(arg0, arg1);
                func_8003D60C(arg1);
            } else {
                if (temp_a1_2->unk_06 != 0) {
                    var_s0 = 0;
                    if (temp_v1_2 == arg1->unk_08A) {
                        func_80030D14(arg1->unk_018, temp_a1_2);
                    }
                } else {
                    var_s0 = 0x20;
                    func_8002E348(arg0, temp_a1_2);
                    if (arg1->unk_016 & 1) {
                        var_s0 = 0x18;
                    }
                }
                arg1->unk_030 = var_s0;
            }
        }
        arg1->unk_016 = arg1->unk_016 + 1;
    }
    D_800AA248.cur_obj = temp_s2;
}

void func_8002E0C8(Monster *m, Building *a) {
    BuildingItem *end;
    BuildingItem *p;

    end = a->unk_070;
    func_8002F5B0(m, a);
    func_8003D60C(a);
    p = a->items;
    func_8002FAA4(m, p);
    do {
        p++;
        func_80030E04(0, p);
    } while (end != p);
    a->unk_016 = a->unk_000;
}







void func_8002E148(Monster *arg0, Building *a) {
    GameObject *saved = D_800AA268.p;
    u16 count;
    u16 left;
    BuildingItem *rec;
    u16 v;

    if (a->unk_030 != 0) {
        a->unk_030--;
    } else {
        count = a->unk_000;
        left = count - a->unk_016;
        rec = a->items;
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
                    if (rec->unk_04 == a->unk_08A) {
                        func_80030D14(a->unk_018, rec);
                    }
                } else {
                    v = 0x18;
                    func_8002E348(arg0, rec);
                    if (a->unk_016 & 1) {
                        v = 0x20;
                    }
                }
                a->unk_030 = v;
            }
        }
        a->unk_016++;
    }
    D_800AA268.p = saved;
}

void func_8002E278(Monster *arg0, Building *a) {
    GameObject *saved = D_800AA268.p;
    BuildingItem *rec = a->items;

    if (a->unk_016 == 0) {
        func_8002FAA4(arg0, rec);
        goto next;
    }
    while (1) {
        if (rec->unk_04 == a->unk_000) {
            func_8002F5B0(arg0, a);
            func_8003D60C(a);
            a->unk_016 = a->unk_000;
            break;
        }
        func_8002E348(arg0, rec);
        a->unk_030 = (a->unk_016 & 1) ? 0x20 : 0x18;
next:
        rec++;
        a->unk_016++;
    }
    D_800AA268.p = saved;
}

void func_8002E348(Monster *arg0, BuildingItem *rec) {
    Building *b;
    u16 n;

    if (rec->unk_06 == 0) {
        n = 0;
        if (rec->unk_0C.unk_06 < 5) {
            func_8002E614(1, rec);
            n++;
        }
        if (rec->unk_24.unk_06 < 5) {
            func_8002E614(2, rec);
            n++;
        }
        if (rec->building->kind != 2 && rec->unk_3C.unk_06 < 5) {
            func_8002E614(3, rec);
            n++;
        }
        if (n != 0) {
            func_8002FDC0(arg0, rec);
            func_8001F724(0x45);
        }
    }
    b = rec->building;
    if (b->unk_08A == rec->unk_04) {
        func_80030D14(b->unk_018);
    }
}

/* 94.2 %: per part, the original fills the delay slot of the zero test from the else block (li v1,5 there, its store's 5 in v1), this one from the then block */
#ifdef NON_MATCHING
void func_8002E440(Monster *arg0, BuildingItem *rec) {
    BuildingPart *part;
    u16 n;

    if (rec->unk_06 == 0) {
        n = 0;
        part = &rec->unk_0C;
        if (part->unk_06 < 5) {
            func_8002E5F4(1, rec);
            if (part->unk_06 != 0) {
                func_80030754(part, 5, arg0, rec);
                part->unk_06 = 5;
            } else {
                part->unk_06 = 5;
                func_80030698(5, arg0, rec);
            }
            n++;
        }
        part = &rec->unk_24;
        if (part->unk_06 < 5) {
            func_8002E5F4(2, rec);
            if (part->unk_06 != 0) {
                func_80030754(part, 5, arg0, rec);
                part->unk_06 = 5;
            } else {
                part->unk_06 = 5;
                func_80030698(5, arg0, rec);
            }
            n++;
        }
        part = &rec->unk_3C;
        if (rec->building->kind != 2 && part->unk_06 < 5) {
            func_8002E5F4(3, rec);
            if (part->unk_06 != 0) {
                func_80030754(part, 5, arg0, rec);
                part->unk_06 = 5;
            } else {
                part->unk_06 = 5;
                func_80030698(5, arg0, rec);
            }
            n++;
        }
        if (n != 0) {
            func_8002FDC0(arg0, rec);
            func_8003089C(6, arg0);
        }
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/building", func_8002E440);
#endif

void func_8002E5F4(u16 which, BuildingItem *rec) {
    func_8002E658(which, rec);
}

void func_8002E614(u16 which, BuildingItem *rec) {
    s32 *temp_v0;

    temp_v0 = func_8002E658(which, rec);
    if ((temp_v0 != NULL) && (*temp_v0 != 0)) {
        func_8003C894(temp_v0);
    }
}

s32 *func_8002E658(u16 which, BuildingItem *rec) {
    GameObject *saved;
    ObjectDef *def;
    GameObject *obj;
    SpriteFrame *frame;
    Ai *ai;
    u16 x;
    u16 y;
    Building *bld;

    saved = D_800AA248.cur_obj;
    D_800AA248.new_def = func_8001D110();
    def = D_800AA248.new_def;
    bld = rec->building;
    def->unk_24 = bld->unk_06C;
    def->anim = &D_80011D48;
    def->id = D_80011D48.id;
    obj = rec->obj;
    frame = obj->frame;
    switch (which) {
    case 1:
        ai = rec->unk_0C.unk_0C;
        x = frame->unk_10 + obj->pos_x.u.hi;
        y = frame->unk_12 + obj->pos_y.u.hi;
        break;
    case 2:
        ai = rec->unk_24.unk_0C;
        x = frame->unk_20 + obj->pos_x.u.hi;
        y = frame->unk_22 + obj->pos_y.u.hi;
        def->unk_04 |= 0x10;
        break;
    case 3:
        ai = rec->unk_3C.unk_0C;
        x = frame->unk_18 + obj->pos_x.u.hi;
        y = frame->unk_1A + obj->pos_y.u.hi;
        break;
    default:
        D_800AA268.p = saved;
        return NULL;
    }
    def->pos_x.s.hi = x;
    def->pos_y.s.hi = y;
    def->flags = rec->obj->priority + 0x80;
    D_800AA248.cur_obj = func_8001DCB4();
    if (func_8001A3AC() < 0x23) {
        D_800AA248.cur_obj = saved;
        return (s32 *) ai;
    }
    bld = rec->building;
    if (bld->state != 9) {
        D_800AA248.unk_00 = func_8001EB10(0x8000, 0) & 0x3F;
        if ((u32) D_800AA248.unk_00 >= 0x20) {
            def->anim = &D_80011F10;
            def->id = D_80011F10.id;
            def->flags -= 2;
            def->unk_24 = 0;
            def->pos_x.s.hi += 8;
            def->pos_y.s.hi += 8;
            func_8001DCB4();
        }
    }
    D_800AA268.p = saved;
    return (s32 *) ai;
}

void func_8002E854(Building *b) {
    GameObject *saved;
    GameObject *obj;
    BuildingItem *rec;
    s32 v;           /* the fall v, then the bottom y */
    u16 n;

    obj = b->unk_070->obj;
    saved = D_800AA248.cur_obj;
    D_800AA248.cur_obj = obj;
    rec = b->items;
    if (obj->vel_y.w == 0) {
        v = 0x20000;
        func_80030D14(b->unk_018);
        b->unk_016 = 1;
        n = b->unk_000 - 1;
        if (b->state == 4) {
            v = 0x40000;
        }
        rec = &b->items[1];
        do {
            func_80030B00(v, rec);
            rec++;
        } while (--n != 0);
    } else {
        rec += b->unk_016;
        obj = rec->obj;
        D_800AA248.cur_obj = obj;
        v = obj->pos_y.s.hi - obj->unk_1C.s.hi + obj->size.s.hi;
        if (obj->pos_y.s.hi >= 0x12D || v >= (s16) b->bottom - 8) {
            func_800257F0(rec);
            func_80025B7C(rec);
            b->unk_016++;
        }
    }
    D_800AA268.p = saved;
}

void func_8002E9A4(Building *arg0) {
    GameObject *temp_a0;
    GameObject *temp_s1;

    temp_a0 = arg0->items[0].obj;
    temp_s1 = D_800AA248.cur_obj;
    D_800AA248.cur_obj = temp_a0;
    temp_a0->priority = 0x20A;
    func_8001E698(temp_a0, arg0->unk_060);
    D_800AA248.cur_obj = temp_s1;
}

void func_8002E9F8(Building *a) {
    u16 i = 2;
    BuildingItem *rec = &a->items[1];
    u16 *p = a->unk_03A;
    u16 k = a->unk_036;
    GameObject *saved = D_800AA268.p;
    u16 v;
    s32 n;
    UnkStructPair *tbl;
    for (;; i++) {
        v = *p;
        n = i - 1;
        if (k < a->unk_000 - n || v >= 0xC) {
            rec++;
            p++;
        } else {
            *p = v + 1;
            p++;
            if (a->unk_034 == 1) {
                tbl = D_8007CE08;
            } else {
                tbl = D_8007CE34;
            }
            tbl += v - 1;
            func_800309AC(tbl->unk_00, rec);
            rec++;
        }
        if (a->unk_000 == i) {
            break;
        }
    }
    a->unk_036 = k + 1;
    D_800AA268.p = saved;
}

void func_8002EB00(Building *b) {
    BuildingItem *rec;
    UnkStructPair *mid;
    UnkStructPair *side;
    u16 i;

    rec = b->items;
    rec += b->unk_02C - 1;
    i = b->unk_02A;
    if (rec->building->unk_02E == 1) {
        mid = D_8007CE60;
        side = D_8007CF18;
    } else {
        mid = D_8007CEBC;
        side = D_8007CF74;
    }
    mid += i - 1;
    side += i - 1;
    func_800309AC(side->unk_00, rec - 1);
    func_800309AC(side->unk_00, rec + 1);
    func_800309AC(mid->unk_00, rec);
    b->unk_02A++;
}

void func_8002EBD8(Building *b) {
    Building *o;
    u16 n;
    u16 kind;

    n = D_801E29A4;
    o = D_801D3DC8;
    if (n != 0) {
        if (b->priority == 0x300) {
            kind = 0x200;
        } else if (b->priority == 0x200) {
            kind = 0x100;
        } else {
            return;
        }
        do {
            if (o->state < 0x10 && o->priority == kind && o->right > (s16) b->left &&
                (b->right >= o->right || b->right >= (s16) o->left)) {
                o->left_side = 0;
                o->right_side = 0;
                o->unk_026 = 0;
            }
            o++;
        } while (--n != 0);
    }
}

void func_8002ECA0(Building *arg0) {
    u16 var_s1;
    BuildingItem *var_s0;

    func_8002E278((Monster *) D_800AA260, arg0);
    func_8003CD08(arg0);
    func_8003D60C(arg0);
    var_s0 = &arg0->items[1];
    var_s1 = arg0->unk_000 - 1;
    do {
        func_80025898(var_s0);
        func_80025B7C(var_s0);
        var_s0++;
    } while (--var_s1 != 0);
    arg0->state = 0x10;
}

void func_8002ED28(void) {
}

BuildingPart *func_8002ED30(u16 which, BuildingItem *rec) {
    BuildingPart *slot;

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
    return slot;
}



void func_8002ED90(Building *arg0) {
    u16 var_s1;
    s16 var_s2;
    u16 temp_v0;
    u32 temp_v1;
    BuildingItem *var_s0;

    var_s2 = arg0->unk_00C;
    var_s1 = arg0->unk_000 - 1;
    temp_v0 = (u16) arg0->unk_030 - 1;
    temp_v1 = temp_v0 & 3;
    arg0->unk_030 = temp_v0;
    var_s0 = &arg0->items[1];
    if (temp_v1 < 2U) {
        if (temp_v1 == 0) {
            var_s2 = -var_s2;
        }
        do {
            func_8002EE14(var_s2, var_s0);
            var_s0++;
        } while (--var_s1 != 0);
    }
}

void func_8002EE14(s16 dy, BuildingItem *s) {
    GameObject *b = s->obj;
    BuildingPart *g;
    GameObject *r;
    Ai *pp;
    Ai *q;

    if (b != NULL) {
        b->pos_y.u.hi += dy;
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
            r = pp->obj;
            if (r != NULL) {
                r->pos_y.u.hi += dy;
            }
        }
        q = g->unk_0C;
        if (q != NULL) {
            r = q->obj;
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
            r = pp->obj;
            if (r != NULL) {
                r->pos_y.u.hi += dy;
            }
        }
        q = g->unk_0C;
        if (q != NULL) {
            r = q->obj;
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
            r = pp->obj;
            if (r != NULL) {
                r->pos_y.u.hi += dy;
            }
        }
        q = g->unk_0C;
        if (q != NULL) {
            r = q->obj;
            if (r != NULL) {
                r->pos_y.u.hi += dy;
            }
        }
    }
}

Building *func_8002F01C(void) {
    Building *found;
    Building *p;
    u16 n;

    found = NULL;
    n = D_801E29A4;
    p = D_801D3DC8;
    if (n != 0) {
        do {
            if (p->def == D_80011BA4 && p->unk_094 == 0) {
                p->unk_094 = 1;
                found = p;
                break;
            }
            p++;
        } while (--n != 0);
    }
    return found;
}


void func_8002F084(Building *a) {
    GameObject *saved;

    saved = D_800AA268.p;
    a->state = 0x10;
    a->unk_030 = 0;
    a->unk_082 = 0;
    a->unk_016 = 0;
    func_8001E698(a->unk_090, a->kind == 2 ? D_8001236C : D_8001236C_alt);
    a->unk_090 = NULL;
    D_800AA268.p = saved;
}

void func_8002F100(Building *b) {
    GameObject *saved;
    GameObject *obj;
    GameObject *box;
    ObjectDef *def;
    u16 t;

    saved = D_800AA248.cur_obj;
    func_8001F724(5);
    if (b->falling != NULL) {
        if (b->unk_010 >= 0x4B) {
            D_801FB448->unk_40.w = (0x7D - b->unk_010) * 3;
        } else {
            D_801FB448->unk_40.w = (0x4B - b->unk_010) * 2;
        }
        b->state = 0;
        if (b->unk_010 >= 0x19 && b->unk_010 < 0x32) {
            if (b->items[0].obj->anim != (s32) &D_80016890) {
                func_8002CBF4((Monster *) b);
                func_80029118(8, 8);
            }
            func_8001E698(b->items[0].obj, &D_80016890);
        } else {
            t = b->unk_010;
            if (t >= 0x32 && t < 0x4B) {
                if (b->items[0].obj->anim != (s32) &D_800168B8) {
                    D_801FB448->colour = 0xFFFF00;
                    func_8002CBF4((Monster *) b);
                    func_80029118(8, 8);
                    building_set_players_action(10);
                    func_8001E698(b->items[0].obj, &D_800168B8);
                    D_800AA284.p = func_8001D110();
                    def = D_800AA284.p;
                    def->anim = &D_80016964;
                    def->id = D_80016964.id;
                    def->pos_x.s.hi = b->items[0].obj->pos_x.u.hi + 0x1B;
                    def->pos_y.s.hi = b->items[0].obj->pos_y.u.hi - 0x44;
                    def->flags = 0x1DB;
                    obj = func_8001DCB4();
                    obj->kind = 0x749;
                    b->falling = obj;
                } else {
                    func_8001E698(b->falling, &D_80016964);
                }
            } else if (t >= 0x4B) {
                if (b->items[0].obj->anim != (s32) &D_800168D8) {
                    D_801FB448->unk_40.w = 0x96;
                    func_8002CBF4((Monster *) b);
                    func_80029118(8, 8);
                    building_set_players_action(10);
                    b->top += 0x14;
                    func_8001E698(b->items[0].obj, &D_800168D8);
                } else {
                    if (t > 0x64 && D_801FB448->colour != 0xFF0000) {
                        D_801FB448->colour = 0xFF0000;
                    }
                    func_8001E698(b->falling, &D_80016964);
                    if (b->unk_010 >= b->unk_012) {
                        D_801FB448->unk_40.w = 0;
                        func_8001E4B0(D_801FB448);
                        D_801FB448 = NULL;
                        building_set_players_action(0x62);
                    }
                }
            }
        }
    } else {
        def = func_8001D110();
        box = main_create_box(0, 0, 0x96, 5, 0xFF00);
        box->pos_x.s.hi = 0x73;
        box->pos_y.s.hi = 0xD7;
        box->priority = 0x7000;
        b->falling = b->items[0].obj;
        def->anim = &D_80016A78;
        def->id = D_80016A78.id;
        def->pos_x.s.hi = 0x64;
        def->pos_y.s.hi = 0xDC;
        def->flags = 0x7000;
        def->unk_0C = 0x794;
        D_801FB448 = box;
        def->unk_06 |= 0x20;
        func_8001DCB4();
        D_800AA248.cur_obj = saved;
        return;
    }
    D_800AA268.p = saved;
}

void building_set_players_action(u16 action) {
    s16 i;
    Monster *m;

    for (i = 0; i < D_801D8740; i++) {
        m = &D_801E0B78[func_80025DF8(D_801FB49C[i])];
        if (m->action != 0x37 && m->action != 0x3B && (action != 0x62 || m->action == 0)) {
            m->action = action;
        }
    }
}

u16 building_pick_part(Building *a) {
    s32 r;

    r = func_8001EB10(0x8000, 0);
    if (a->kind == 2) {
        return (r & 1) + 1;
    }
    r &= 3;
    return r ? r : 3;
}
















void func_8002F5B0(Monster *arg0, Building *arg1) {
    s32 temp_a0;
    s32 temp_s1;
    s32 temp_s2;
    BuildingItem *temp_s0;

    temp_s0 = arg1->unk_070;
    temp_s2 = D_800AA248.cur_obj;
    temp_s1 = arg1->unk_064;
    if (temp_s0->unk_06 == 0) {
        func_80030698(0, arg0, temp_s0);
        temp_a0 = temp_s0->obj;
        if (temp_a0 != 0) {
            func_8001E698(temp_a0, temp_s1);
            temp_s0->unk_06 = 1U;
        }
    }
    D_800AA248.cur_obj = temp_s2;
}

void func_8002F630(Building *arg0, s32 arg1, BuildingItem *arg2) {
    func_8002F688(arg0, 0, arg1, arg2);
}

void func_8002F65C(Building *arg0, s32 arg1, BuildingItem *arg2) {
    func_8002F688(arg0, 1, arg1, arg2);
}

void func_8002F688(b, flag, m, rec)
Building *b;
u16 flag;
Monster *m;
BuildingItem *rec;
{
    GameObject *saved;
    GameObject *obj;
    ObjectDef *def;
    BuildingBlock *blk;
    s32 *anim;

    saved = D_800AA248.cur_obj;
    if (rec->unk_06 == 2) {
        func_8001F724(0xF);
    } else {
        func_8002F9F4(rec);
        func_800256CC(rec);
        if (b->kind == 2) {
            D_800AA248.unk_0C = (s32) D_80011BA4;
        } else if (b->kind != 3) {
            D_800AA248.cur_obj = saved;
            return;
        } else {
            D_800AA248.unk_0C = (s32) D_80011BDC;
        }
        D_800AA248.cur_obj = rec->obj;
        if (flag) {
            def = func_8001D110();
            def->pos_x.s.hi = D_800AA248.cur_obj->pos_x.u.hi;
            def->pos_y.s.hi = D_800AA248.cur_obj->pos_y.u.hi;
            anim = (s32 *) D_800AA248.unk_0C;
            def->anim = anim;
            def->id = *anim;
            def->flags = D_800AA248.cur_obj->priority + 0x80;
            def->unk_24 = b->unk_06C;
            if (b->unk_02E != 1) {
                def->unk_04 |= 0x10;
                def->pos_x.s.hi = b->right;
            }
            obj = D_800AA248.cur_obj;
            D_800AA248.new_def = def;
            func_8001DCB4();
            D_800AA248.cur_obj = obj;
        }
        func_8002FB38(b->def->unk_1C, D_800AA268.p);
        func_8001F724(5);
        func_8003CDAC(rec);
        rec->unk_06 = 2;
        func_8003111C(2, m);
        func_80054374(0x1E, m);
        if (flag) {
            blk = b->unk_018;
            if (blk != NULL && blk->unk_0A == rec->unk_04) {
                func_80030D14(blk);
            }
        }
    }
    D_800AA268.p = saved;
}

void func_8002F898(Building *arg0, BuildingItem *rec) {
    GameObject *saved = D_800AA248.cur_obj;
    GameObject *obj;
    BuildingBlock *r;
    u8 *anim;

    if (rec->unk_04 != 1) {
        if (rec->building->unk_070 == rec) {
            func_8001E4B0(rec->obj);
        } else {
            func_8002F9F4(rec);
            if (arg0->kind == 2) {
                anim = D_8001236C;
            } else {
                if (arg0->kind != 3) {
                    D_800AA248.cur_obj = saved;
                    return;
                }
                anim = D_80012394;
            }
            func_80025848(rec);
            obj = rec->obj;
            D_800AA268.p = obj;
            if (obj != NULL) {
                func_8001E698(obj, anim);
                func_80024964(0x49, obj);
                r = arg0->unk_018;
                if (r != NULL && r->unk_0A == rec->unk_04) {
                    func_80030D14(r);
                }
            }
        }
    }
    D_800AA268.p = saved;
}

void func_8002F9BC(void) {
    BuildingItem *temp_s0;

    temp_s0 = D_800AA248.cur_obj->owner.item;
    func_8001E4B0(D_800AA248.cur_obj);
    func_80025B7C(temp_s0);
}

void func_8002F9F4(BuildingItem *arg0) {
    arg0->unk_0C.unk_14 = 1;
    arg0->unk_24.unk_14 = 1;
    if ((arg0->building)->kind != 2) {
        arg0->unk_3C.unk_14 = 1;
    }
}

void func_8002FA20(Monster *arg0, BuildingItem *arg1) {
    if ((arg1->unk_06 == 0) && (arg1->unk_0C.unk_06 >= 5U) && (arg1->unk_24.unk_06 >= 5U) &&
        ((arg1->building->kind == 2) || (arg1->unk_3C.unk_06 >= 5U))) {
        func_8002FDC0(arg0, arg1);
    }
}

void func_8002FAA4(Monster *arg0, BuildingItem *arg1) {
    GameObject *temp_a1;
    GameObject *temp_s1;

    temp_s1 = D_800AA248.cur_obj;
    if (arg1->unk_06 == 0) {
        temp_a1 = arg1->obj;
        D_800AA248.cur_obj = temp_a1;
        if (temp_a1 != NULL) {
            func_8002FB38(arg1->building->unk_05C, temp_a1);
            arg1->unk_06 = 1;
            func_80030698(0, arg0, arg1);
            func_8001F724(0x45);
        }
    }
    D_800AA248.cur_obj = temp_s1;
}

void func_8002FB38(void *arg0, GameObject *arg1) {
    if (arg1->frame != arg0) {
        main_set_frame(arg0, 0x8002, arg1);
    }
}

void func_8002FB6C(Monster *arg0, BuildingItem *rec, Building *b) {
    GameObject *saved;
    GameObject *obj;
    ObjectDef *def;
    BuildingBlock *blk;
    BuildingItem *top;
    Anim *anim;
    s32 dx;
    u16 kind;

    saved = D_800AA248.cur_obj;
    if (rec->unk_04 >= 2) {
        func_8002F9F4(rec);
        kind = b->kind;
        if (kind == 2) {
            dx = 0x28;
            anim = &D_80011F58;
        } else {
            dx = 0x3C;
            if (kind != 3) {
                D_800AA248.cur_obj = saved;
                return;
            }
            anim = &D_80011F90;
        }
        def = func_8001D110();
        obj = rec->obj;
        D_800AA248.cur_obj = obj;
        def->anim = anim;
        def->id = anim->id;
        def->pos_y.s.hi = obj->pos_y.s.hi;
        def->pos_x.s.hi = obj->pos_x.u.hi + dx;
        def->flags = obj->priority + 0x80;
        D_800AA248.new_def = def;
        func_8001DCB4();
        func_8001F724(5);
        blk = b->unk_018;
        if (blk != NULL && blk->unk_0A == rec->unk_04) {
            func_80030D14(blk);
        }
        func_8002FB38((void *) b->unk_08C, obj);
        func_8003111C(2, arg0);
        func_8003CD5C(rec);
        b->unk_000--;
        func_8002FD24(rec, b);
        top = b->unk_070;
        func_8001E4B0(top->obj);
        func_80025B7C(top);
        b->unk_070 = rec;
        b->top = obj->pos_y.u.hi + 0xC;
        rec->unk_06 = 3;
    }
    D_800AA268.p = saved;
}

void func_8002FD24(BuildingItem *arg0, Building *arg1) {
    u16 i;
    u16 temp_a3;
    Monster *temp_a2;

    i = 7;
    do {
        temp_a2 = &D_801E0B78[i];
        if (temp_a2->unk_058 & 1) {
            temp_a3 = temp_a2->climb_side;
            if (temp_a3 != 0) {
                if ((temp_a2->climb_building == arg1->unk_01E) && (temp_a3 != 3)) {
                    if (temp_a2->climb_floor >= arg0->unk_04) {
                        temp_a2->action = 0xF;
                    }
                }
            }
        }
    } while (--i != 0);
}

void func_8002FDC0(Monster *m, BuildingItem *rec) {
    Building *b;
    SpriteFrame **frames;
    GameObject *saved;
    GameObject *obj;

    b = rec->building;
    saved = D_800AA248.cur_obj;
    frames = b->frames;
    if (rec->unk_04 >= 2 && rec->unk_04 < b->unk_000) {
        obj = rec->obj;
        frames += rec->unk_04 - 2;
        D_800AA248.cur_obj = obj;
        if (obj->frame != *frames) {
            func_800257C4(rec);
            func_800256B0(rec);
            func_8001F724(5);
            func_8002FB38(*frames, obj);
            rec->unk_06 = 1;
            func_8003111C(1, m);
        }
    }
    D_800AA268.p = saved;
}

void func_8002FEA4(Building *a) {
    GameObject *saved = D_800AA248.cur_obj;
    ObjectDef *r;
    GameObject *spr;
    s16 x;

    if (func_8001A3AC() >= 0x23) {
        r = func_8001D110();
        r->anim = D_80012068;
        r->id = D_80012068[0];
        x = a->left + (a->right - (s16) a->left - 0x7A) / 2;
        r->pos_x.u.hi = x;
        r->pos_y.u.hi = a->bottom - 0x1D;
        r->flags = a->priority + 0x90;
        D_800AA248.new_def = r;
        spr = func_8001DCB4();
        if (spr != NULL) {
            spr->owner.building = a;
        }
        D_800AA248.cur_obj = saved;
    }
}

void building_create_roof(void) {
    GameObject *saved;
    Building *b;
    ObjectDef *def;
    Anim **anim;
    u16 dx;

    saved = D_800AA248.cur_obj;
    b = saved->owner.p;
    if (b->priority == 0x300 && b->roof != 0) {
        def = func_8001D110();
        D_800AA248.new_def = def;
        if (b->kind == 2) {
            dx = 0x28;
        } else if (b->kind != 3) {
            D_800AA248.cur_obj = saved;
            return;
        } else {
            dx = 0x3C;
        }
        def->pos_x.s.hi = dx + b->left;
        def->pos_y.s.hi = b->bottom;
        anim = D_8007CFD8;
        if (b->roof >= 1 && b->roof <= 3) {
            anim += b->roof;
            def->anim = *anim;
            def->id = (*anim)->id;
            def->flags = 0x38F;
            D_800AA248.cur_obj = func_8001DCB4();
            b->unk_07C = D_800AA248.cur_obj;
            func_800303DC(D_800AA248.cur_obj, b);
        }
    }
    D_800AA268.p = saved;
}

void func_800300A0(UnkStruct15 *arg0, Building *arg1) {
    if ((arg0 != NULL) && (arg1->roof != 0)) {
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

void func_80030114(GameObject *obj, Building *b) {
    Monster *m;
    u16 i;
    s32 x;

    if (b->roof != 0) {
        i = 7;
        do {
            m = &D_801E0B78[i];
            if ((m->unk_058 & 1) && m->climb_side == 0 && m->action < 2 && m->unk_13C == 0 &&
                m->obj->pos_y.s.hi == 0xE1) {
                x = obj->pos_x.s.hi;
                D_800AA248.unk_00 = x;
                if (b->roof == 3) {
                    D_800AA248.unk_00 = x + 5;
                    D_800AA248.unk_08 = 10;
                } else {
                    D_800AA248.unk_08 = 30;
                }
                if ((u16) func_80030268(D_800AA248.unk_00, (s16) D_800AA248.unk_08, m) != 0) {
                    func_800302AC(b->roof, m);
                }
            }
        } while (--i != 0);
    }
}

s32 func_80030268(s16 arg0, s32 arg1, Monster *arg2) {
    s32 var_v1;

    if (arg2->unk_0DC != 0) {
        var_v1 = arg2->front_x - arg0;
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


u16 func_80030338(GameObject *obj) {
    UnkStructPair *p;
    s16 x;

    p = D_801D8804;
    D_800AA248.unk_4C = 0;
    x = ((s16) obj->size.u.lo >> 1) + (obj->pos_x.u.hi - obj->unk_1C.u.lo);
    while (p->unk_00 != 0) {
        if (x >= p->unk_00 && x <= p->unk_02) {
            D_800AA248.unk_4C = 1;
            return 1;
        }
        p++;
    }
    return D_800AA294;
}

void func_800303DC(GameObject *obj, Building *b) {
    UnkStructPair *p;
    u16 n;
    s16 d;

    if (b->roof != 2) {
        p = D_801D8804;
        n = 13;
        do {
            if (p->unk_00 == 0) {
                d = obj->pos_x.u.hi - obj->unk_1C.u.lo;
                p->unk_00 = d + 0x19;
                p->unk_02 = d + obj->size.u.lo - 0x19;
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


void func_8003047C(void) {
    Building *owner;
    s32 *anim;
    s32 r;

    owner = D_800AA248.cur_obj->owner.building;
    anim = NULL;
    if (func_8001A3AC() < 0x23) {
        func_8001E4B0(D_800AA248.cur_obj);
        return;
    }
    if (owner->state == 0x10 || owner->state == 0x11) {
        func_8001E698(D_800AA248.cur_obj, D_80012110);
        return;
    }
    r = func_8001EB10(0x7001, 0) + owner->unk_000;
    r &= 0x4F;
    if (r < 0x20) {
        switch (r & 7) {
        case 0:
        case 1:
            anim = D_8001214C;
            break;
        case 2:
            anim = D_800121AC;
            break;
        case 3:
            anim = D_8001214C_alt;
            break;
        case 4:
            anim = D_80012204;
            break;
        case 5:
            anim = D_80012264;
            break;
        case 6:
            anim = D_800122B4;
            break;
        case 7:
            anim = D_8001231C;
            break;
        }
        func_800305C8(anim, D_800AA268.p->pos_y.s.hi, D_800AA268.p, owner);
    }
}

void func_800305C8(s32 *anim, s16 y, GameObject *body, Building *rec) {
    GameObject *saved = D_800AA268.p;
    ObjectDef *r;
    s32 x;

    r = func_8001D110();
    r->pos_y.u.hi = y;
    r->anim = anim;
    r->id = *anim;
    x = (s16) rec->left + ((rec->kind == 2) ? 0x4F : 0x77);
    r->pos_x.u.hi = D_801D8866 & func_8001EB10(x, (s16) rec->left);
    r->flags = body->priority + 1;
    D_800AA248.new_def = r;
    func_8001DCB4();
    D_800AA248.cur_obj = saved;
}

void func_80030698(s16 n, Monster *a, BuildingItem *rec) {
    Building *b;
    u16 v;

    b = rec->building;
    if (b != NULL && b->state < 9 && n < 7) {
        func_80031154((u16) n, a);
        if (n >= 0) {
            u16 *step = &D_8007CFE8[n];
            b->unk_010 = v = b->unk_010 + *step;
            func_80030834(b, v);
            if (v < b->unk_012) {
                func_8003111C(1, a);
            }
        }
    }
}

void func_80030754(BuildingPart *part, s16 n, Monster *arg2, BuildingItem *rec) {
    Building *b;
    u16 *step;

    b = rec->building;
    if (b->state < 9 && n < 7) {
        func_80031154((u16) n, arg2);
        if (n >= 0) {
            step = &D_8007CFE8[n];
            if ((s16) part->unk_06 >= 0) {
                b->unk_010 += *step - D_8007CFE8[part->unk_06];
                func_80030834(b, b->unk_010);
                if (b->unk_010 < b->unk_012) {
                    func_8003111C(1, arg2);
                }
            }
        }
    }
}

void func_80030834(Building *b, s32 v) {
    u16 d;
    s16 a;
    s16 c;

    if (b->state == 0 && (d = b->unk_012 - v) != 0) {
        if (d < 4) {
            c = 3;
            a = 0x1A;
        } else if (d < 6) {
            a = 0xE;
            c = 1;
        } else {
            return;
        }
        b->unk_030 = a;
        b->unk_00C = c;
        b->state = 3;
    }
}

void func_8003089C(u16 i, Monster *a) {
    u16 *p;

    if (i < 7 && a->id != 0) {
        p = D_8007CFF8;
        p += i + 1;
        func_8001F724(*p);
    }
}

void func_800308EC(s16 arg0, BuildingPart *arg1) {
    Ai *temp_v0;
    GameObject *obj;
    Ai *temp_d;

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
        obj = temp_v0->obj;
        if (obj != NULL) {
            obj->pos_x.u.hi = (u16) (obj->pos_x.u.hi + arg0);
        }
    }
    temp_d = arg1->unk_0C;
    if ((temp_d != NULL) && (temp_d->unk_04 < 0xBU)) {
        obj = temp_d->obj;
        if (obj != NULL) {
            obj->pos_x.u.hi = (u16) (obj->pos_x.u.hi + arg0);
        }
    }
}

void func_800309AC(s16 arg0, BuildingItem *arg1) {
    BuildingBlock *temp_a0;
    GameObject *temp_v1;
    GameObject *temp_v1_2;

    temp_v1 = arg1->obj;
    if (temp_v1 != NULL) {
        temp_v1->pos_x.u.hi = (u16) (temp_v1->pos_x.u.hi + arg0);
        func_800308EC(arg0, &arg1->unk_0C);
        func_800308EC(arg0, &arg1->unk_24);
        func_800308EC(arg0, &arg1->unk_3C);
        temp_a0 = arg1->building->unk_018;
        if ((temp_a0 != NULL) && (temp_a0->unk_0A == arg1->unk_04)) {
            temp_v1_2 = temp_a0->unk_00;
            if (temp_v1_2 != NULL) {
                temp_v1_2->pos_x.u.hi = (u16) (temp_v1_2->pos_x.u.hi + arg0);
            }
        }
    }
}

void func_80030A70(s32 arg0, BuildingPart *arg1) {
    Ai *temp_v0;
    GameObject *obj;
    Ai *temp_d;

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
        obj = temp_v0->obj;
        if (obj != NULL) {
            obj->vel_y.w = arg0;
        }
    }
    temp_d = arg1->unk_0C;
    if ((temp_d != NULL) && (temp_d->unk_04 < 0xBU)) {
        obj = temp_d->obj;
        if (obj != NULL) {
            obj->vel_y.w = arg0;
        }
    }
}

void func_80030B00(s32 vy, BuildingItem *rec) {
    GameObject *obj;

    obj = rec->obj;
    if (obj != NULL) {
        obj->vel_y.w = vy;
        func_80030A70(vy, &rec->unk_0C);
        func_80030A70(vy, &rec->unk_24);
        func_80030A70(vy, &rec->unk_3C);
    }
}


void func_80030B5C(Building *a) {
    u16 n;
    BuildingItem *rec;

    n = a->unk_000 - 1;
    rec = a->items;
    do {
        rec++;
        func_80030C7C(rec);
    } while (--n != 0);
}

void func_80030BAC(BuildingPart *arg0) {
    Ai *temp_v0;
    GameObject *obj;
    Ai *temp_d;

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
        obj = temp_v0->obj;
        if (obj != NULL) {
            obj->pos_y.w = obj->pos_y.w + obj->vel_y.w;
        }
    }
    temp_d = arg0->unk_0C;
    if ((temp_d != NULL) && (temp_d->unk_04 < 0xBU)) {
        obj = temp_d->obj;
        if (obj != NULL) {
            obj->pos_y.w = obj->pos_y.w + obj->vel_y.w;
        }
    }
}

void func_80030C7C(BuildingItem *rec) {
    GameObject *obj;

    obj = rec->obj;
    if (obj != NULL) {
        obj->pos_y.w += obj->vel_y.w;
        func_80030BAC(&rec->unk_0C);
        func_80030BAC(&rec->unk_24);
        func_80030BAC(&rec->unk_3C);
    }
}


s32 func_80030CD4(BuildingBlock *part) {
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

    saved = D_800AA248.cur_obj;
    if (p != NULL) {
        obj = p->unk_00;
        D_800AA248.cur_obj = obj;
        func_8001E698(obj, p->unk_04);
        func_8001F724(0x42);
    }
    D_800AA248.cur_obj = saved;
}



/* 98.6 %: the loop's pointer register is &p->items[0] in the original (negative offsets for unk_070 and state), &p->state here; count and n swap a1/a2 */
#ifdef NON_MATCHING
void building_count_standing(void) {
    u16 n = D_801E29A4;
    s16 count = 0;
    Building *p;
    GameObject *o;
    GameObject *q;

    if (n != 0) {
        p = D_801D3DC8;
        do {
            q = p->items[0].obj;
            o = p->unk_070->obj;
            if (!(q->unk_6C & 0x80) || o == NULL || !(o->unk_6C & 0x80)) {
                if (p->state < 0x10) {
                    count++;
                }
            }
            p++;
        } while (--n != 0);
        D_801FA734 = count;
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/building", building_count_standing);
#endif

void func_80030E04(Monster *m, BuildingItem *rec) {
    GameObject *saved;
    Building *b;
    Anim *anim;
    s32 dx;
    ObjectDef *def;
    GameObject *obj;
    BuildingBlock *blk;

    saved = D_800AA248.cur_obj;
    if (rec->unk_06 < 2 || m == NULL) {
        if (rec->unk_04 != 0) {
            if (rec->unk_04 == 1) {
                func_8002FAA4(m, rec);
            } else {
                b = rec->building;
                if (m != NULL && rec >= b->unk_070) {
                    D_800AA248.cur_obj = saved;
                    return;
                }
                if (b->unk_076 != 0) {
                    b->unk_010 = b->unk_012;
                } else {
                    if (b->kind == 2) {
                        anim = &D_80011FC8;
                        dx = 0x28;
                    } else {
                        anim = &D_80012018;
                        dx = 0x3C;
                    }
                    D_800AA248.new_def = func_8001D110();
                    def = D_800AA248.new_def;
                    def->anim = anim;
                    def->id = anim->id;
                    obj = rec->obj;
                    D_800AA248.cur_obj = obj;
                    def->pos_x.s.hi = obj->pos_x.u.hi + dx;
                    def->pos_y.s.hi = obj->pos_y.u.hi;
                    def->flags = b->priority + 0x11;
                    obj = func_8001DCB4();
                    obj->owner.p = rec;
                    obj->unk_94.monster = m;
                    blk = b->unk_018;
                    if (blk != NULL && blk->unk_0A == rec->unk_04) {
                        func_80030D14(blk);
                    }
                }
            }
        }
        D_800AA268.p = saved;
    }
}

void func_80030FA4(void) {
    void *temp_a0;
    s32 temp_s2;
    BuildingItem *temp_s0;
    Building *temp_s1;

    temp_s0 = D_800AA248.cur_obj->owner.item;
    temp_s2 = (s32) D_800AA248.cur_obj->unk_94.p;
    temp_s1 = temp_s0->building;
    if ((temp_s2 != 0) && (temp_s1 != NULL)) {
        if (((u16) temp_s1->state) < 9U) {
            temp_s1->unk_010 = (u16) (temp_s1->unk_010 + 8);
            func_800257C4(temp_s0);
            func_800256B0(temp_s0);
            func_8002F630(temp_s1, temp_s2, temp_s0);
        }
    } else {
        func_8003CD5C(temp_s0);
        func_800256CC(temp_s0);
        func_800257C4(temp_s0);
        temp_a0 = temp_s0->obj;
        if (temp_a0 != NULL) {
            func_8001E4B0(temp_a0);
        }
        func_80025B7C(temp_s0);
    }
}

void func_80031074(void) {
    GameObject *saved;
    BuildingItem *rec;   /* tested before it is set: a bug of the original, whose test reads the caller's s0 */

    saved = D_800AA268.p;
    if (rec != NULL && rec->obj != NULL && rec->building != NULL) {
        rec = saved->owner.item;
        func_800305C8(func_8001EB10(rec->unk_04 + 0x5ABC, rec->unk_04) & 1 ? D_800121AC : D_8001214C,
                      rec->obj->pos_y.s.hi + 12, saved, rec->building);
        D_800AA268.p = saved;
    }
}

void func_8003111C(s32 arg0, Monster *arg1) {
    if (((u8 *) arg1 >= D_801E0D98) && ((u8 *) arg1 <= D_801E0D98 + 0xCC0)) {
        arg1->unk_026 = (u16) (((u16) arg1->unk_026) + arg0);
    }
}

void func_80031154(kind, m)
    u16 kind;
    Monster *m;
{
    s32 points;

    if ((u8 *) m >= D_801E0D98 && (u8 *) m <= D_801E0D98 + 0xCC0) {
        if (kind < 4) {
            points = 10;
            func_800634D4(m, 0);
        } else {
            switch (kind) {
            case 5:
                points = 20;
                func_800634D4(m, 1);
                break;
            case 10:
                points = 20;
                func_800634D4(m, 2);
                break;
            case 6:
                points = 10;
                func_800634D4(m, 3);
                break;
            default:
                return;
            }
        }
        func_80054374(points, m);
    }
}

void func_80031224(void) {
    Building *temp_v0;

    func_8001F724(5);
    temp_v0 = func_8003D1F8((s32) D_800AA248.cur_obj->owner.ai->unk_10.p);
    if (((u16) temp_v0->state) < 3U) {
        temp_v0->state = 0xCU;
    }
}

void func_80031280(Monster *arg0, Building *a) {
    void *target = a->def;
    void **t;
    BuildingItem *r;

    if (a->unk_058 == 0) {
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
        if (a->unk_058 != 0) {
            func_8002CFAC(arg0, a);
        } else {
            r = a->unk_070;
            if (r != NULL && r->obj != NULL && r->building != NULL) {
                func_8002F5B0(arg0, a);
                func_8001F724(5);
                a->unk_078++;
                func_80031364(a);
            }
        }
    }
}

void func_80031364(Building *b) {
    GameObject *saved;
    ObjectDef *def;
    GameObject *obj;
    s32 x;

    saved = D_800AA248.cur_obj;
    D_800AA248.new_def = func_8001D110();
    def = D_800AA248.new_def;
    def->anim = &D_80011F58;
    def->id = D_80011F58.id;
    x = (s16) b->left;
    def->pos_x.s.hi = b->kind == 2 ? x + 0x28 : x + 0x3C;
    obj = b->unk_070->obj;
    def->pos_y.s.hi = obj->pos_y.u.hi + (obj->size.s.hi >> 1);
    def->flags = b->priority + 0x80;
    func_8001DCB4();
    D_800AA268.p = saved;
}

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

void func_8003149C(void) {
    s32 *p;
    u16 n;
    ObjectDef *def;
    GameObject *obj;
    s32 x;
    s32 y;

    p = func_80025C08(D_80084268);
    n = *(u16 *) p;
    p++;
    do {
        def = func_8001D110();
        D_800AA248.new_def = def;
        def->id = *p & ~0x800000;
        if (*p != 0) {
            x = *++p;
            y = *++p;
            if (y >= 0xE2) {
                def->unk_1C = 2;
                def->flags = y + 0xF23;
            } else {
                def->unk_1C = 1;
                def->flags = y + 0x51F;
            }
            obj = func_8001DCB4();
            obj->kind = 0x74B;
            obj->pos_x.s.hi = obj->unk_08.s.lo = x;
            obj->pos_y.s.hi = obj->unk_08.s.hi = y - obj->size.s.hi;
            func_8001B054(obj);
            if (*p & 0x800000) {
                obj->flags |= 0x10;
            }
        }
        p++;
    } while (--n != 0);
}

void func_800315D8(void) {
    u16 *p;

    p = (u16 *) func_80025C08(D_80083CE8);
    D_801FA98C = *p++;
    D_801FAC90 = *p++;
    D_801FAC8C = *p++;
    D_801FA990 = *p++;
    D_801D87B0 = *p++;
    D_801D376C = *p++;
    D_801D37B8 = *p++;
    D_801D87B4 = *p++;
    D_801FAC84 = *p++;
    D_801F9AB0 = *p++;
}

#ifdef NON_MATCHING
/* 92.42%: 92.4%: only the prologue's order differs: the original computes lists (s1) before the call's argument
 * (a0) */
void func_80031690(void) {
    GameObject **lists;
    UnkStruct18 *r;

    lists = D_801E1E34;
    r = (UnkStruct18 *) func_80025C08(&D_80084028[0]);
    D_801D37BC = r->unk_00;
    D_801D37C0 = r->unk_02;
    D_801D857C = r->unk_04;
    if (D_801D857C != 0) {
        func_8003197C(r->unk_0C, r->unk_04, &lists[0]);
        func_8003197C(r->unk_18, r->unk_08, &lists[1]);
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/building", func_80031690);
#endif





s32 func_80031714(Monster *m) {
    s16 i;
    s16 x;
    u16 px;
    s32 hit;

    if (bonus_get_round_kind() == 1) {
        x = m->obj->pos_x.s.hi;
        for (i = 0; i < 4; i++) {
            if (x >= D_8007D0A8[i][0] && x <= D_8007D0A8[i][1]) {
                return 0;
            }
        }
        return 1;
    }
    hit = 0;
    if (D_801FA98C != 0 && m->climb_side == 0) {
        px = D_800AA268.p->pos_x.u.hi;
        switch (m->action) {
        case 0x34:
            if ((s16) px >= (u16) D_801FAC90 && (s16) px <= (u16) D_801FAC8C) {
                hit = 1;
            }
            break;
        case 1:
            if (D_801D37BC == 0 && D_801D37C0 == 0) {
                if ((s16) px <= D_801FA990 && (s16) px >= (u16) D_801FAC90) {
                    hit = 1;
                }
            }
            break;
        case 0:
            if (D_801D37BC == 0 && D_801D37C0 == 0) {
                if ((s16) px >= (u16) D_801FAC90 && (s16) px <= (u16) D_801FAC8C) {
                    hit = 1;
                }
            }
            break;
        default:
            if (D_801D37BC != 0 || D_801D37C0 != 0) {
                if ((s16) px >= D_801D37BC && (s16) px <= D_801D37C0) {
                    if (D_801E1E34[0] != NULL) {
                        func_8001F724(0x29);
                        func_8001E4B0(D_801E1E34[0]);
                        func_8001E4B0(D_801E1E34[1]);
                    }
                    hit = 1;
                    D_801D37BC = 0;
                    D_801D37C0 = 0;
                }
            } else if ((s16) px >= (u16) D_801FAC90 && (s16) px <= (u16) D_801FAC8C) {
                hit = 1;
            }
            break;
        }
    }
    return hit;
}

void func_8003197C(u16 *p, s32 id, GameObject **out) {
    GameObject *saved;
    ObjectDef *def;
    GameObject *obj;

    saved = D_800AA248.cur_obj;
    def = func_8001D110();
    D_800AA248.new_def = def;
    def->id = id;
    def->unk_1C = 0;
    def->flags = 0x600;
    obj = func_8001DCB4();
    *out = obj;
    obj->flags |= *p++;
    obj->pos_x.u.hi = *p++;
    obj->pos_y.u.hi = obj->unk_1C.u.hi + (*p - obj->size.u.hi);
    obj->priority = p[1];
    obj->kind = 0x540;
    D_800AA248.cur_obj = saved;
}

void func_80031A3C(void) {
    D_801D8864.w = *func_80025C08(D_800838A0);
}

void func_80031A68(void) {
    if ((D_801D37BC == 0) && (D_801D37C0 == 0) && (D_801D857C != 0)) {
        main_set_frame(D_801D857C, 0x8002, D_800AA248.cur_obj);
        D_801D857C = 0;
        func_8001E7A0();
    }
}

void func_80031AC8(void) {
    if ((D_801D37BC == 0) && (D_801D37C0 == 0)) {
        D_800AA248.cur_obj->script.pc = *D_800AA248.cur_obj->arg.w;
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

void func_80031B74(Ai *arg0) {
    func_80031CB4(D_8007D1E8, arg0);
}

void func_80031B9C(Ai *arg0) {
    func_80031CB4(D_8007D0B8, arg0);
}

void func_80031BC4(Ai *arg0) {
    func_80031CB4(D_8007D104, arg0);
}

void func_80031BEC(Ai *arg0) {
    func_80031CB4(D_8007D150, arg0);
}

void func_80031C14(Ai *arg0) {
    func_80031CB4(D_8007D19C, arg0);
}

void func_80031C3C(Ai *arg0) {
    func_80031CB4(D_8007D364, arg0);
}

void func_80031C64(Ai *arg0) {
    func_80031CB4(D_8007D3B0, arg0);
}

void func_80031C8C(Ai *arg0) {
    func_80031CB4(D_8007D3FC, arg0);
}

void func_80031CB4(void *handlers, Ai *ai) {
    u16 hit;

    switch (ai->action) {
    case 0x0A:
        func_80031EC0((s32) handlers, ai);
        break;
    case 0x0B:
        func_80031FD4((s32) handlers, ai);
        break;
    case 0x32:
        func_80032064((s32) handlers, ai);
        break;
    case 0x33:
        func_80032064((s32) handlers, ai);
        break;
    case 0x3B:
    case 0x3C:
        func_8003212C((s32) handlers, ai);
        break;
    case 0x36:
    case 0x37:
        func_800322AC((s32) handlers, ai);
        break;
    case 0x1E:
        if (handlers == D_8007D280) {
            func_80032690((s32) handlers, ai);
        } else {
            func_800322E8((s32) handlers, ai);
        }
        break;
    case 0xF2:
        func_80032530((s32) handlers, ai);
        break;
    case 0x46:
        func_80032350((s32) handlers, ai);
        break;
    default:
        hit = func_8003DC3C(ai);
        if (hit != 0) {
            func_80032008(hit, (s32) handlers, ai);
        } else if (ai->action == 0x15) {
            func_80031F20((s32) handlers, ai);
        } else if (ai->action == 0x16) {
            func_80031F5C((s32) handlers, ai);
        } else if (ai->action == 0x17) {
            func_80031F98((s32) handlers, ai);
        } else {
            func_8003DB74(ai);
        }
        break;
    }
}

void func_80031EC0(s32 arg0, Ai *arg1) {
    if (arg1->state != 0) {
        if (arg1->unk_0C == 1) {
            arg1->state = 4;
            arg1->unk_0C = 0;
            arg1->action = 0x15;
            func_80032630(arg0, arg1);
        }
    } else {
        arg1->unk_0C = 0;
        arg1->state = 1;
        func_80032630(arg0, arg1);
    }
}

void func_80031F20(s32 arg0, Ai *arg1) {
    if (arg1->unk_0C == 1) {
        arg1->state = 5;
        arg1->unk_0C = 0;
        arg1->action = 0x16;
        func_80032630(arg0, arg1);
    }
}

void func_80031F5C(s32 arg0, Ai *arg1) {
    if (arg1->unk_0C == 1) {
        arg1->state = 6;
        arg1->unk_0C = 0;
        arg1->action = 0x17;
        func_80032630(arg0, arg1);
    }
}

void func_80031F98(s32 arg0, Ai *arg1) {
    if (arg1->unk_0C == 1) {
        arg1->state = 9;
        arg1->unk_0C = 0;
        arg1->action = 0x32;
        func_80032630(arg0, arg1);
    }
}

void func_80031FD4(s32 arg0, Ai *arg1) {
    if (arg1->unk_0C == 1) {
        func_8003DB74(arg1);
    }
}

void func_80032008(s16 arg0, s32 arg1, Ai *arg2) {
    if (arg0 != -1) {
        arg2->state = 9;
        arg2->unk_0C = 0;
        arg2->action = 0x32;
    } else {
        arg2->state = 0x10;
        arg2->unk_0C = 0;
        arg2->action = 0x33;
    }
    func_80032630(arg1, arg2);
}

void func_80032064(s32 arg0, Ai *arg1) {
    s16 var_v0;
    s32 var_v1;

    arg1->unk_34.s.hi = 0;
    if (arg1->unk_0C == 1) {
        arg1->unk_0C = 0;
        if (D_800AA248.cur_obj->pos_y.w <= 0x5F0000) {
            var_v1 = 0x30000;
            arg1->state = 0xB;
            var_v0 = 0x3C;
        } else {
            var_v1 = 0x2C000;
            arg1->state = 0xA;
            var_v0 = 0x3B;
        }
        arg1->action = var_v0;
        arg1->unk_24 = 1;
        D_800AA248.cur_obj->vel_y.w = var_v1;
        func_8003E788(arg1);
        D_800AA248.cur_obj->priority = 0x353;
        func_80032630(arg0, arg1);
    }
}

void func_8003212C(s32 arg0, Ai *ai) {
    s32 floor;
    BuildingItem *item;

    if (ai->unk_24 != 0) {
        ai->unk_24 = 0;
        D_800AA268.p->pos_y.w += 0x1C0000;
    }
    floor = 0xD90000;
    if (D_801FA960 >= 100) {
        floor = 0xE00000;
    }
    D_800AA248.cur_obj->pos_y.w += D_800AA248.cur_obj->vel_y.w;
    if (D_800AA248.cur_obj->pos_y.w >= floor) {
        D_800AA248.cur_obj->pos_y.w = floor;
        D_800AA248.cur_obj->priority = D_800AA248.cur_obj->pos_y.u.hi + 0xF23;
        D_800AA248.cur_obj->vel_y.w = 0;
        ai->unk_0C = 0;
        item = ai->unk_28.item;
        if (item->building != NULL && item->building->state == 4) {
            ai->state = 0x12;
            ai->action = 0x46;
            if (D_800AA248.cur_obj->flags & 0x10) {
                D_800AA248.cur_obj->vel_x.w = 0xC000;
                D_800AA248.cur_obj->unk_84 = 0x400;
            } else {
                D_800AA248.cur_obj->vel_x.w = -0xC000;
                D_800AA248.cur_obj->unk_84 = -0x400;
            }
        } else if (ai->state != 0xB) {
            ai->state = 0xC;
            ai->action = 0x36;
        } else {
            ai->state = 0xD;
            ai->action = 0x37;
        }
    }
    func_80032630(arg0, ai);
}

void func_800322AC(s32 arg0, Ai *arg1) {
    if (arg1->unk_0C == 1) {
        arg1->state = 0xE;
        arg1->unk_0C = 0;
        arg1->action = 0x1E;
        func_80032630(arg0, arg1);
    }
}

void func_800322E8(s32 arg0, Ai *arg1) {
    if (arg1->unk_0C == 1) {
        arg1->state = 0xF;
        arg1->action = 0x46;
        arg1->unk_0C = 0;
        if (D_800AA248.cur_obj->flags & 0x10) {
            D_800AA248.cur_obj->vel_x.w = 0x28000;
        } else {
            D_800AA248.cur_obj->vel_x.w = 0xFFFD8000;
        }
        func_80032630(arg0, arg1);
    }
}

void func_80032350(s32 arg0, Ai *ai) {
    s32 vel;
    s32 accel;
    s32 kind;
    GameObject *obj;

    D_800AA248.unk_4C = 0;
    accel = D_800AA248.cur_obj->unk_84;
    vel = D_800AA248.cur_obj->vel_x.w;
    if (accel != 0) {
        vel += accel;
        if (vel <= 0) {
            if (vel < -0x28000) {
                vel = -0x28000;
            }
        } else if (vel > 0x28000) {
            vel = 0x28000;
        }
        D_800AA268.p->vel_x.w = vel;
    }
    obj = D_800AA248.cur_obj;
    obj->pos_x.w = (vel + obj->pos_x.w) & D_801D8864.w;
    if (D_800AA248.cur_obj->unk_6C & 0x80) {
        kind = 1;
        if (D_800AA248.cur_obj->flags & 0x10) {
            kind = 2;
        }
        if (func_8004B6C4(ai->obj, 100, kind) == 1) {
            func_8003DAA0(ai);
        }
    } else {
        if (ai->unk_38 == 0) {
            if (func_8003E79C(obj, vel) == 1) {
                D_800AA248.cur_obj->flags ^= 0x10;
                D_800AA248.cur_obj->vel_x.w = -D_800AA248.cur_obj->vel_x.w;
                D_800AA248.cur_obj->unk_84 = -D_800AA248.cur_obj->unk_84;
                ai->unk_38 = 0xB4;
                return;
            }
        } else {
            ai->unk_38--;
        }
        if (D_800AA248.unk_4C != 0) {
            D_800AA248.cur_obj->vel_x.w = 0;
            D_800AA248.cur_obj->vel_y.w = 0;
            D_800AA248.cur_obj->unk_88 = 0;
            ai->action = 5;
        }
    }
}

void func_80032530(s32 arg0, Ai *ai) {
    s32 vy;
    s32 floor;

    vy = D_800AA248.cur_obj->pos_x.w - D_800AA248.cur_obj->vel_x.w;
    vy &= D_801D8864.w;
    D_800AA248.cur_obj->pos_x.w = vy;
    vy = D_800AA248.cur_obj->vel_y.w + D_800AA248.cur_obj->unk_88;
    if (vy > 0x60000) {
        vy = 0x60000;
    }
    D_800AA248.cur_obj->vel_y.w = vy;
    D_800AA248.cur_obj->pos_y.w += vy;
    floor = 0xD90000;
    if (D_801FA960 >= 100) {
        floor = 0xE00000;
    }
    if (D_800AA248.cur_obj->pos_y.w >= floor) {
        D_800AA248.cur_obj->vel_x.w = 0;
        D_800AA248.cur_obj->vel_y.w = 0;
        D_800AA248.cur_obj->unk_88 = 0;
        ai->action = 0x4E;
        ai->unk_0C = 0;
    } else if (ai->state != 0x11) {
        ai->state = 0x11;
        func_80032630(arg0, ai);
    }
}

void func_80032630(s32 handlers, Ai *r) {
    void (**h)(Ai *);

    h = (void (**)(Ai *)) handlers;
    h += r->state;
    (*h)(r);
}


void func_80032668(Ai *arg0) {
    func_80031CB4(D_8007D280, arg0);
}

void func_80032690(s32 n, Ai *r) {
    s32 v;

    if (r->unk_0C == 1) {
        r->state = 0xF;
        r->action = 0x46;
        r->unk_0C = 0;
        v = -0x8000;
        if (D_800AA248.cur_obj->flags & 0x10) {
            v = 0x8000;
        }
        D_800AA248.cur_obj->vel_x.w = v;
        D_800AA248.cur_obj->pos_y.u.hi += 5;
        func_80032630(n, r);
    }
}


void func_80032710(Ai *arg0) {
    func_80031CB4(D_8007D234, arg0);
}

void func_80032738(Ai *arg0) {
    func_80031CB4(D_8007D2CC, arg0);
}

void func_80032760(Ai *arg0) {
    func_80031CB4(D_8007D318, arg0);
}

void func_80032788(void) {
    func_8003EB5C(D_80091B98, D_800AA248.cur_obj);
}

void func_800327B4(void) {
    func_8003EB5C(D_80091BC8, D_800AA248.cur_obj);
}

void func_800327E0(void) {
    func_8003EB5C(D_80091BF8, D_800AA248.cur_obj);
}

void func_8003280C(void) {
    func_8003EB5C(D_80091C04, D_800AA248.cur_obj);
}

void func_80032838(void) {
    func_8003EB5C(D_80091C30, D_800AA248.cur_obj);
}

void func_80032864(void) {
    func_8003EB5C(D_80091C48, D_800AA248.cur_obj);
}

void func_80032890(void) {
    func_8003EB5C(D_80091C88, D_800AA248.cur_obj);
}

void func_800328BC(void) {
    func_8003EB5C(D_80091CC0, D_800AA248.cur_obj);
}

void func_800328E8(void) {
    func_8003EB5C(D_80091CF8, D_800AA248.cur_obj);
}

void func_80032914(void) {
    func_8003EB5C(D_80091D38, D_800AA248.cur_obj);
}

void func_80032940(void) {
    func_8003EB5C(D_80091D68, D_800AA248.cur_obj);
}

void func_8003296C(void) {
    func_8003EB5C(D_80091DC4, D_800AA248.cur_obj);
}

void func_80032998(void) {
    func_8003EB5C(D_80091D90, D_800AA248.cur_obj);
}

void func_800329C4(void) {
    func_8003EB5C(D_80091DD0, D_800AA248.cur_obj);
}

void func_800329F0(void) {
    func_8003EB5C(D_80091E04, D_800AA248.cur_obj);
}

void func_80032A1C(void) {
    func_8003EB5C(D_80091E34, D_800AA248.cur_obj);
}

void func_80032A48(void) {
    func_8003EB5C(D_80091E40, D_800AA248.cur_obj);
}

void func_80032A74(void) {
    func_8003EB5C(D_80091E80, D_800AA248.cur_obj);
}

void func_80032AA0(void) {
    func_8003EB5C(D_80091EF0, D_800AA248.cur_obj);
}

void func_80032ACC(void) {
    func_8003EB5C(D_80091F30, D_800AA248.cur_obj);
}

void func_80032AF8(void) {
    func_8003EB5C(D_80091F68, D_800AA248.cur_obj);
}

void func_80032B24(void) {
    func_8003EB5C(D_80091FA0, D_800AA248.cur_obj);
}

void func_80032B50(void) {
    func_8003EB5C(D_80091FE0, D_800AA248.cur_obj);
}

void func_80032B7C(void) {
    func_8003EB5C(D_80092010, D_800AA248.cur_obj);
}

void func_80032BA8(void) {
    func_8003EB5C(D_8009206C, D_800AA248.cur_obj);
}

void func_80032BD4(void) {
    func_8003EB5C(D_80092038, D_800AA248.cur_obj);
}

void func_80032C00(void) {
    func_8003EB5C(D_80092078, D_800AA248.cur_obj);
}

void func_80032C2C(void) {
    func_8003EB5C(D_800920A8, D_800AA248.cur_obj);
}

void func_80032C58(void) {
    func_8003EB5C(D_800920D8, D_800AA248.cur_obj);
}

void func_80032C84(void) {
    func_8003EB5C(D_800920E4, D_800AA248.cur_obj);
}

void func_80032CB0(void) {
    func_8003EB5C(D_80092124, D_800AA248.cur_obj);
}

void func_80032CDC(void) {
    func_8003EB5C(D_8009213C, D_800AA248.cur_obj);
}

void func_80032D08(void) {
    func_8003EB5C(D_80092164, D_800AA248.cur_obj);
}

void func_80032D34(void) {
    func_8003EB5C(D_8009219C, D_800AA248.cur_obj);
}

void func_80032D60(void) {
    func_8003EB5C(D_800921D4, D_800AA248.cur_obj);
}

void func_80032D8C(void) {
    func_8003EB5C(D_80092214, D_800AA248.cur_obj);
}

void func_80032DB8(void) {
    func_8003EB5C(D_80092244, D_800AA248.cur_obj);
}

void func_80032DE4(void) {
    func_8003EB5C(D_800922A0, D_800AA248.cur_obj);
}

void func_80032E10(void) {
    func_8003EB5C(D_8009226C, D_800AA248.cur_obj);
}

void func_80032E3C(void) {
    func_8003EB5C(D_800922AC, D_800AA248.cur_obj);
}

void func_80032E68(void) {
    func_8003EB5C(D_800922D4, D_800AA248.cur_obj);
}

void func_80032E94(void) {
    func_8003EB5C(D_80092304, D_800AA248.cur_obj);
}

void func_80032EC0(void) {
    func_8003EB5C(D_80092310, D_800AA248.cur_obj);
}

void func_80032EEC(void) {
    func_8003EB5C(D_80092338, D_800AA248.cur_obj);
}

void func_80032F18(void) {
    func_8003EB5C(D_80092350, D_800AA248.cur_obj);
}

void func_80032F44(void) {
    func_8003EB5C(D_80092384, D_800AA248.cur_obj);
}

void func_80032F70(void) {
    func_8003EB5C(D_800923BC, D_800AA248.cur_obj);
}

void func_80032F9C(void) {
    func_8003EB5C(D_800923F4, D_800AA248.cur_obj);
}

void func_80032FC8(void) {
    func_8003EB5C(D_80092404, D_800AA248.cur_obj);
}

void func_80032FF4(void) {
    func_8003EB5C(D_8009245C, D_800AA248.cur_obj);
}

void func_80033020(void) {
    func_8003EB5C(D_8009248C, D_800AA248.cur_obj);
}

void func_8003304C(void) {
    func_8003EB5C(D_800924E8, D_800AA248.cur_obj);
}

void func_80033078(void) {
    func_8003EB5C(D_800924B4, D_800AA248.cur_obj);
}

void func_800330A4(void) {
    func_8003EB5C(D_800924F4, D_800AA248.cur_obj);
}

void func_800330D0(void) {
    func_8003EB5C(D_80092534, D_800AA248.cur_obj);
}

void func_800330FC(void) {
    func_8003EB5C(D_80092574, D_800AA248.cur_obj);
}

void func_80033128(void) {
    func_8003EB5C(D_80092580, D_800AA248.cur_obj);
}

void func_80033154(void) {
    func_8003EB5C(D_800925C0, D_800AA248.cur_obj);
}

void func_80033180(void) {
    func_8003EB5C(D_800925D8, D_800AA248.cur_obj);
}

void func_800331AC(void) {
    func_8003EB5C(D_80092604, D_800AA248.cur_obj);
}

void func_800331D8(void) {
    func_8003EB5C(D_8009262C, D_800AA248.cur_obj);
}

void func_80033204(void) {
    func_8003EB5C(D_80092654, D_800AA248.cur_obj);
}

void func_80033230(void) {
    func_8003EB5C(D_8009268C, D_800AA248.cur_obj);
}

void func_8003325C(void) {
    func_8003EB5C(D_800926B4, D_800AA248.cur_obj);
}

void func_80033288(void) {
    func_8003EB5C(D_80092710, D_800AA248.cur_obj);
}

void func_800332B4(void) {
    func_8003EB5C(D_800926DC, D_800AA248.cur_obj);
}

void func_800332E0(void) {
    func_8003EB5C(D_8009271C, D_800AA248.cur_obj);
}

void func_8003330C(void) {
    func_8003EB5C(D_80092754, D_800AA248.cur_obj);
}

void func_80033338(void) {
    func_8003EB5C(D_8009278C, D_800AA248.cur_obj);
}

void func_80033364(void) {
    func_8003EB5C(D_80092798, D_800AA248.cur_obj);
}

void func_80033390(void) {
    func_8003EB5C(D_800927D4, D_800AA248.cur_obj);
}

void func_800333BC(void) {
    func_8003EB5C(D_800927EC, D_800AA248.cur_obj);
}

void func_800333E8(void) {
    func_8003EB5C(D_80092818, D_800AA248.cur_obj);
}

void func_80033414(void) {
    func_8003EB5C(D_80092840, D_800AA248.cur_obj);
}

void func_80033440(void) {
    func_8003EB5C(D_80092868, D_800AA248.cur_obj);
}

void func_8003346C(void) {
    func_8003EB5C(D_800928A0, D_800AA248.cur_obj);
}

void func_80033498(void) {
    func_8003EB5C(D_800928C8, D_800AA248.cur_obj);
}

void func_800334C4(void) {
    func_8003EB5C(D_80092924, D_800AA248.cur_obj);
}

void func_800334F0(void) {
    func_8003EB5C(D_800928F0, D_800AA248.cur_obj);
}

void func_8003351C(void) {
    func_8003EB5C(D_80092930, D_800AA248.cur_obj);
}

void func_80033548(void) {
    func_8003EB5C(D_8009296C, D_800AA248.cur_obj);
}

void func_80033574(void) {
    func_8003EB5C(D_800929A4, D_800AA248.cur_obj);
}

void func_800335A0(void) {
    func_8003EB5C(D_800929B0, D_800AA248.cur_obj);
}

void func_800335CC(void) {
    func_8003EB5C(D_800929D8, D_800AA248.cur_obj);
}

void func_800335F8(void) {
    func_8003EB5C(D_80092A64, D_800AA248.cur_obj);
}

void func_80033624(void) {
    func_8003EB5C(D_80092A8C, D_800AA248.cur_obj);
}

void func_80033650(void) {
    func_8003EB5C(D_80092AB4, D_800AA248.cur_obj);
}

void func_8003367C(void) {
    func_8003EB5C(D_80092ADC, D_800AA248.cur_obj);
}

void func_800336A8(void) {
    func_8003EB5C(D_80092B1C, D_800AA248.cur_obj);
}

void func_800336D4(void) {
    func_8003EB5C(D_80092B54, D_800AA248.cur_obj);
}

void func_80033700(void) {
    func_8003EB5C(D_80092B7C, D_800AA248.cur_obj);
}

void func_8003372C(void) {
    func_8003EB5C(D_80092BD8, D_800AA248.cur_obj);
}

void func_80033758(void) {
    func_8003EB5C(D_80092BA4, D_800AA248.cur_obj);
}

void func_80033784(void) {
    func_8003EB5C(D_800934A0, D_800AA248.cur_obj);
}

void func_800337B0(void) {
    func_8003EB5C(D_800934DC, D_800AA248.cur_obj);
}

void func_800337DC(void) {
    func_8003EB5C(D_80093538, D_800AA248.cur_obj);
}

void func_80033808(void) {
    func_8003EB5C(D_80093548, D_800AA248.cur_obj);
}

void func_80033834(void) {
    func_8003EB5C(D_8009363C, D_800AA248.cur_obj);
}

void func_80033860(void) {
    func_8003EB5C(D_80093698, D_800AA248.cur_obj);
}

void func_8003388C(void) {
    func_8003EB5C(D_80093768, D_800AA248.cur_obj);
}

void func_800338B8(void) {
    func_8003EB5C(D_800937A8, D_800AA248.cur_obj);
}

void func_800338E4(void) {
    func_8003EB5C(D_8009382C, D_800AA248.cur_obj);
}

void func_80033910(void) {
    func_8003EB5C(D_800937F4, D_800AA248.cur_obj);
}

void func_8003393C(void) {
    func_8003EB5C(D_80093864, D_800AA248.cur_obj);
}

void func_80033968(void) {
    func_8003EB5C(D_8009388C, D_800AA248.cur_obj);
}

void func_80033994(void) {
    func_8003EB5C(D_800937E8, D_800AA248.cur_obj);
}

void func_800339C0(void) {
    func_8003EB5C(D_800938AC, D_800AA248.cur_obj);
}

void func_800339EC(void) {
    func_8003EB5C(D_80092BE4, D_800AA248.cur_obj);
}

void func_80033A18(void) {
    func_8003EB5C(D_80092C20, D_800AA248.cur_obj);
}

void func_80033A44(void) {
    func_8003EB5C(D_80092C7C, D_800AA248.cur_obj);
}

void func_80033A70(void) {
    func_8003EB5C(D_80092C8C, D_800AA248.cur_obj);
}

void func_80033A9C(void) {
    func_8003EB5C(D_80092D88, D_800AA248.cur_obj);
}

void func_80033AC8(void) {
    func_8003EB5C(D_80092DE4, D_800AA248.cur_obj);
}

void func_80033AF4(void) {
    func_8003EB5C(D_80092EB4, D_800AA248.cur_obj);
}

void func_80033B20(void) {
    func_8003EB5C(D_80092EDC, D_800AA248.cur_obj);
}

void func_80033B4C(void) {
    func_8003EB5C(D_80092F48, D_800AA248.cur_obj);
}

void func_80033B78(void) {
    func_8003EB5C(D_80092F10, D_800AA248.cur_obj);
}

void func_80033BA4(void) {
    func_8003EB5C(D_80092F80, D_800AA248.cur_obj);
}

void func_80033BD0(void) {
    func_8003EB5C(D_80092FA8, D_800AA248.cur_obj);
}

void func_80033BFC(void) {
    func_8003EB5C(D_80092F04, D_800AA248.cur_obj);
}

void func_80033C28(void) {
    func_8003EB5C(D_80092FC8, D_800AA248.cur_obj);
}

void func_80033C54(void) {
    func_8003EB5C(D_80093008, D_800AA248.cur_obj);
}

void func_80033C80(void) {
    func_8003EB5C(D_80093064, D_800AA248.cur_obj);
}

void func_80033CAC(void) {
    func_8003EB5C(D_800930BC, D_800AA248.cur_obj);
}

void func_80033CD8(void) {
    func_8003EB5C(D_800930C8, D_800AA248.cur_obj);
}

void func_80033D04(void) {
    func_8003EB5C(D_8009314C, D_800AA248.cur_obj);
}

void func_80033D30(void) {
    func_8003EB5C(D_8009321C, D_800AA248.cur_obj);
}

void func_80033D5C(void) {
    func_8003EB5C(D_800932F4, D_800AA248.cur_obj);
}

void func_80033D88(void) {
    func_8003EB5C(D_80093324, D_800AA248.cur_obj);
}

void func_80033DB4(void) {
    func_8003EB5C(D_80093360, D_800AA248.cur_obj);
}

void func_80033DE0(void) {
    func_8003EB5C(D_80093370, D_800AA248.cur_obj);
}

void func_80033E0C(void) {
    func_8003EB5C(D_80093398, D_800AA248.cur_obj);
}

void func_80033E38(void) {
    func_8003EB5C(D_800933B0, D_800AA248.cur_obj);
}

void func_80033E64(void) {
    func_8003EB5C(D_80093354, D_800AA248.cur_obj);
}

void func_80033E90(void) {
    func_8003EB5C(D_800938EC, D_800AA248.cur_obj);
}

void func_80033EBC(void) {
    func_8003EB5C(D_8009393C, D_800AA248.cur_obj);
}

void func_80033EE8(void) {
    func_8003EB5C(D_80093988, D_800AA248.cur_obj);
}

void func_80033F14(void) {
    func_8003EB5C(D_80093994, D_800AA248.cur_obj);
}

void func_80033F40(void) {
    func_8003EB5C(D_800939CC, D_800AA248.cur_obj);
}

void func_80033F6C(void) {
    func_8003EB5C(D_80093A1C, D_800AA248.cur_obj);
}

void func_80033F98(void) {
    func_8003EB5C(D_80093AD4, D_800AA248.cur_obj);
}

void func_80033FC4(void) {
    func_8003EB5C(D_80093AFC, D_800AA248.cur_obj);
}

void func_80033FF0(void) {
    func_8003EB5C(D_80093B24, D_800AA248.cur_obj);
}

void func_8003401C(void) {
    func_8003EB5C(D_80093B3C, D_800AA248.cur_obj);
}

void func_80034048(void) {
    func_8003EB5C(D_80093B74, D_800AA248.cur_obj);
}

void func_80034074(void) {
    func_8003EB5C(D_80093B9C, D_800AA248.cur_obj);
}

void func_800340A0(void) {
    func_8003EB5C(D_8009397C, D_800AA248.cur_obj);
}

void func_800340CC(void) {
    func_8003EB5C(D_80093BBC, D_800AA248.cur_obj);
}

void func_800340F8(void) {
    func_8003EB5C(D_80093C00, D_800AA248.cur_obj);
}

void func_80034124(void) {
    func_8003EB5C(D_80093C28, D_800AA248.cur_obj);
}

void func_80034150(void) {
    func_8003EB5C(D_80093C50, D_800AA248.cur_obj);
}

void func_8003417C(void) {
    func_8003EB5C(D_80093C68, D_800AA248.cur_obj);
}

void func_800341A8(void) {
    func_8003EB5C(D_80093C80, D_800AA248.cur_obj);
}

void func_800341D4(void) {
    func_8003EB5C(D_80093CA4, D_800AA248.cur_obj);
}

void func_80034200(void) {
    func_8003EB5C(D_80093CD0, D_800AA248.cur_obj);
}

void func_8003422C(void) {
    func_8003EB5C(D_80093D10, D_800AA248.cur_obj);
}

void func_80034258(void) {
    func_8003EB5C(D_80093D50, D_800AA248.cur_obj);
}

void func_80034284(void) {
    func_8003EB5C(D_80093D60, D_800AA248.cur_obj);
}

void func_800342B0(void) {
    func_8003EB5C(D_80093DD8, D_800AA248.cur_obj);
}

void func_800342DC(void) {
    func_8003EB5C(D_80093E30, D_800AA248.cur_obj);
}

void func_80034308(void) {
    func_8003EB5C(D_80093EF8, D_800AA248.cur_obj);
}

void func_80034334(void) {
    func_8003EB5C(D_80093C5C, D_800AA248.cur_obj);
}

void func_80034360(void) {
    func_8003EB5C(D_80093F10, D_800AA248.cur_obj);
}

void func_8003438C(void) {
    D_800AA248.cur_obj->owner.ai->unk_34.s.hi = 1;
}

void func_800343A8(void) {
    D_800AA248.cur_obj->owner.ai->unk_34.s.hi = 0;
}

void func_800343C0(void) {
    func_8003EB5C(D_80093F44, D_800AA248.cur_obj);
}

void func_800343EC(void) {
    func_8003EB5C(D_80093F44, D_800AA248.cur_obj);
}

void building_bob_pickup(Building *b) {
    if (b->state < 0x20) {
        D_800AA268.p->vel_y.w = 0x2000;
        b->state++;
    } else if (b->state < 0x28) {
        D_800AA268.p->vel_y.w = 0;
        b->state++;
    } else if (b->state < 0x48) {
        D_800AA268.p->vel_y.w = -0x2000;
        b->state++;
    } else if (b->state < 0x50) {
        D_800AA268.p->vel_y.w = 0;
        b->state++;
    } else {
        b->state = 0;
    }
    D_800AA268.p->pos_y.w += D_800AA268.p->vel_y.w;
}

void building_update_pickup(Pickup *r) {
    D_800AA268.p = r->obj;
    if (r->kind == 0x12 || r->kind == 0x13) {
        building_bob_pickup((Building *) r);   /* bobs the object: counts in the record's halfword at 0x14 */
    }
    switch (r->unk_08) {
    case 1:
    case 0x3B:
        func_80034590(r);
        break;
    case 3:
        func_80034924(r);
        break;
    case 6:
        func_800349E0(r);
        break;
    case 4:
        func_80034898(r);
        break;
    case 5:
    case 9:
        func_800345F8(r);
        break;
    case 0x33:
        break;
    default:
        func_800360D8(r);
        break;
    }
}
