/* The bonus rounds (D_800AA2DC, one bit per round: "READY!", "SET!", "GO!", "BONUS AWARDS!!") and the status panel:
 * each player's health and meter bars and score digits.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "game.h"
#include "bonus.h"
#include "psyq/libc2.h"

extern u16 D_801D3D80;                   /* D_801D3D64.unk_1C */

s32 func_8005D198(void) {
    return func_8001A3AC() >= 0x46;
}

void func_8005D1BC(s32 arg0, s32 n) {
    main_free_kind((u16)(n + 0x790));
    main_free_kind((u16)(n + 0x798));
    main_free_kind((u16)(n + 0x7A8));
    main_free_kind((u16)(n + 0x7A0));
}

void bonus_create_bars(Monster *e) {
    GameObject *saved;
    GameObject *s;
    s32 x;
    s16 x2;

    saved = D_800AA248.cur_obj;
    x = (D_801FA8A0[e->id - 1] - 2) * 0x78;
    s = main_create_box(0, 0, 0x44, 4, 0xFF00);
    x2 = x + 0xA6;
    s->pos_x.s.hi = x2;
    s->pos_y.s.hi = 0x18;
    s->priority = 0x501;
    s->kind = e->id + 0x790;
    e->health_bar = s;
    s = main_create_box(0, 0, 0, 2, 0xFF00FF);
    s->pos_x.s.hi = x2;
    s->pos_y.s.hi = 0x22;
    s->priority = 0x501;
    s->kind = e->id + 0x790;
    e->meter_bar = s;
    func_8001D110()->id = 0x4F000992;
    s = func_8001DCB4();
    s->pos_x.s.hi = x + 0x96;
    s->pos_y.s.hi = 0x1D;
    s->priority = 0x500;
    s->unk_6C |= 0x20;
    s->kind = e->id + 0x790;
    D_800AA248.cur_obj = saved;
}

void bonus_create_lives(Monster *e) {
    GameObject *saved;
    ObjectDef *def;
    s32 dy;
    u16 frame;
    s16 y;
    s16 x;
    s32 v;
    s32 i;

    dy = 0;
    saved = D_800AA268.p;
    if (D_800AA2DC != 0 && (D_8007BD78.flags & 0x10)) {
        dy = -0xF;
    }
    D_800AA284.p = func_8001D110();
    def = D_800AA284.p;
    def->pos_x.s.hi = (D_801FA8A0[e->id - 1] - 2) * 0x78 + 0x96;
    /* Class B: the block's loop notes count the frame's three sets twice, so it gets s6 before the monster, as
     * in the original (the plain if, the set orders and the frame's type leave the two swapped); the same shape in
     * bonus_create_lives and bonus_give_awards, a macro's block, likely. */
    LOOP_BLOCK(
        if (e->id == 7 && D_801F9ABC != 0) {
            if (D_801F9ABC == 3) {
                frame = 0x53;
                def->id = 0x4F003EB2;
            } else {
                frame = 0x54;
                def->id = 0x4F003EB0;
            }
        } else {
            def->id = D_8008427C[e->id - 1];
            frame = 0xFFFF;
        }
    );
    y = dy + 0x30;
    def->pos_y.s.hi = y;
    def->flags = 0x4FF;
    def->unk_06 |= 0x20;
    D_800AA248.cur_obj = func_8001DCB4();
    D_800AA248.cur_obj->kind = e->id + 0x798;
    e->portrait = D_800AA248.cur_obj;
    def->pos_x.s.hi = (D_801FA8A0[e->id - 1] - 2) * 0x78 + 0xE6;
    def->id = D_80084298[e->id - 1];
    def->pos_y.s.hi = y;
    def->unk_06 |= 0x20;
    def->flags = 0x4FF;
    D_800AA248.cur_obj = func_8001DCB4();
    D_800AA248.cur_obj->kind = e->id + 0x7A8;
    D_800AA248.cur_obj->unk_74 = frame;
    v = e->lives;
    x = (D_801FA8A0[e->id - 1] - 2) * 0x78 + 0xF1;
    for (i = 0; i < 2; i++) {
        def->pos_x.s.hi = x;
        x -= 8;
        def->id = D_800842B4[v % 10];
        def->pos_y.s.hi = dy + 0x30;
        def->unk_06 |= 0x20;
        def->flags = 0x4FF;
        D_800AA248.cur_obj = func_8001DCB4();
        D_800AA248.cur_obj->kind = e->id + 0x7A8;
        v /= 10;
        e->lives_digits[i] = D_800AA248.cur_obj;
    }
    D_800AA268.p = saved;
}

void bonus_create_score(Monster *e) {
    GameObject *saved;
    ObjectDef *def;
    s32 x;
    s16 dx;
    s32 v;
    s32 i;

    saved = D_800AA248.cur_obj;
    D_800AA248.new_def = func_8001D110();
    def = D_800AA248.new_def;
    x = (D_801FA8A0[e->id - 1] - 2) * 0x78;
    def->id = 0x4F0021DE;
    def->pos_y.s.hi = 0x30;
    def->unk_06 |= 0x20;
    def->flags = 0x4FF;
    def->pos_x.s.hi = x + 0x96;
    D_800AA248.cur_obj = func_8001DCB4();
    dx = x + 0xF1;
    D_800AA248.cur_obj->kind = e->id + 0x7A0;
    v = e->score;
    for (i = 0; i < 6; i++) {
        def->pos_x.s.hi = dx;
        dx -= 8;
        def->id = D_800842B4[v % 10];
        def->pos_y.s.hi = 0x30;
        def->flags = 0x4FF;
        def->unk_06 |= 0x20;
        D_800AA248.cur_obj = func_8001DCB4();
        D_800AA248.cur_obj->kind = e->id + 0x7A0;
        v /= 10;
        e->score_digits[i] = D_800AA248.cur_obj;
    }
    D_800AA268.p = saved;
}

void bonus_update_score(Monster *e) {
    GameObject *saved;
    GameObject *digit;
    s32 v;
    s32 i;

    saved = D_800AA268.p;
    if (e->id != 0) {
        if (e->score != e->score_shown) {
            func_8005E19C(e, 0x7A0);
            if (D_800AA2DC == 0 || (!(D_8007BD78.flags & 0x10) && (D_800AA2DC & 1))) {
                func_8005E124(e, 0x7A8);
                func_8005E124(e, 0x798);
            }
        }
        v = e->score;
        e->score_shown = v;
        for (i = 0; i < 6; i++) {
            digit = e->score_digits[i];
            if (digit != NULL) {
                main_set_frame(D_800842B4[v % 10], digit->flags, digit);
                v /= 10;
            }
        }
        D_800AA268.p = saved;
    }
}

Monster *bonus_find_most_lives(Monster *skip) {
    Monster *e;
    Monster *found;
    s16 best;
    s16 v;
    s32 i;

    best = 0;
    found = NULL;
    if (D_8007A68C != 0) {
        for (i = 0; i < 7; i++) {
            e = &D_801E0B78[i];
            if (skip != e && e->id != 0) {
                v = e->lives;
                if (v > 0 && best < v && (v != 1 || e->health.w > 0x10FFFF)) {
                    best = e->lives;
                    found = e;
                }
            }
        }
    }
    return found;
}

void bonus_update_lives(Monster *e) {
    GameObject *saved;
    GameObject *face;
    s32 i;
    s32 v;
    u16 id;

    id = e->id;
    saved = D_800AA268.p;
    if (id == 0) {
        return;
    }
    face = e->portrait;
    if (e->unk_1CC == 1) {
        if (bonus_find_most_lives(e) != NULL) {
            func_8005E124(e, 0x7A0);
            func_8005E124(e, 0x7A8);
            func_8005E19C(e, 0x798);
            if (face != NULL) {
                main_set_frame(0x4F00417E, face->flags, face);
            }
            return;
        }
    } else if (face != NULL) {
        if (D_801F9ABC == 3 && id == 7) {
            main_set_frame(0x4F003EB2, face->flags, face);
        } else if (D_801F9ABC == 4 && e->id == 7) {
            main_set_frame(0x4F003EB0, face->flags, face);
        } else {
            main_set_frame(D_8008427C[e->id - 1], face->flags, face);
        }
    }
    if (e->lives != e->lives_shown) {
        func_8005E124(e, 0x7A0);
        func_8005E19C(e, 0x798);
        func_8005E19C(e, 0x7A8);
    }
    v = e->lives;
    e->lives_shown = v;
    if (v >= 0) {
        for (i = 0; i < 2; i++) {
            if (e->lives_digits[i] != NULL) {
                face = e->lives_digits[i];
                main_set_frame(D_800842B4[v % 10], face->flags, face);
                v /= 10;
            }
        }
    }
    D_800AA268.p = saved;
}

void bonus_update_bars(s32 old, Monster *m, s32 value) {
    s32 v; /* FAKE: one scratch for the colour bits and the eased meter: a variable live in two blocks keeps the
            * load of D_801D3D80 out of the shift's register */

    if (m->id == 0) {
        return;
    }
    if (m->meter_bar != NULL) {
        D_800AA248.cur_obj = m->meter_bar;
        D_800AA248.cur_obj->unk_40.w = m->meter_shown.s.hi;
        if ((u32) D_800AA248.cur_obj->unk_40.w > 0x44) {
            D_800AA248.cur_obj->unk_40.w = 0x44;
        }
        if (D_800AA248.cur_obj->unk_40.w == 0x44) {
            D_800AA248.cur_obj->colour.w &= 0xFF00FF;
            v = D_801D3D80 << 10;
            D_800AA248.cur_obj->colour.w |= v & 0xE000;
        } else {
            D_800AA248.cur_obj->colour.w = 0xFF00FF;
        }
        if (m->meter_shown.w != m->meter.w) {
            m->meter_shown.w += (m->meter.w - m->meter_shown.w) >> 4;
            v = m->meter_shown.w;
            if (abs(v - m->meter.w) <= 0xFFFF) {
                m->meter_shown.w = m->meter.w;
            }
        }
    }
    if (m->health_bar != NULL) {
        D_800AA248.cur_obj = m->health_bar;
        D_800AA248.cur_obj->unk_40.w = m->health_shown.s.hi;
        if ((u32) D_800AA248.cur_obj->unk_40.w > 0x44) {
            D_800AA248.cur_obj->unk_40.w = 0x44;
        }
        if (m->health_shown.w != m->health.w) {
            m->health_shown.w += (m->health.w - m->health_shown.w) >> 4;
            if (abs(m->health_shown.w - m->health.w) <= 0xFFFF) {
                m->health_shown.w = m->health.w;
            }
        }
    }
}

void bonus_add_icon(Monster *e) {
    GameObject *saved;
    GameObject *obj;
    ObjectDef *def;
    s32 i;
    s32 x;

    saved = D_800AA268.p;
    x = (D_801FA8A0[e->id - 1] - 2) * 0x78 + 0x96;
    for (i = 0; i < 3; i++) {
        obj = e->icons[i];
        if (obj != NULL) {
            if (e->icon_kind == obj->unk_64.w) {
                return;
            }
            x = obj->size.u.lo + 4 + x;
        }
    }
    for (i = 0; i < 3; i++) {
        if (e->icons[i] == NULL) {
            D_800AA248.new_def = func_8001D110();
            def = D_800AA248.new_def;
            def->id = D_80084304[e->icon_kind];
            def->pos_y.s.hi = 0x40;
            def->unk_06 |= 0x20;
            def->flags = 0x4FF;
            D_800AA248.cur_obj = func_8001DCB4();
            D_800AA248.cur_obj->kind = e->id + 0x790;
            e->icons[i] = D_800AA248.cur_obj;
            D_800AA248.cur_obj->unk_64.w = e->icon_kind;
            D_800AA248.cur_obj->pos_x.s.hi = x + D_800AA248.cur_obj->size.s.lo / 2;
            switch (e->icon_kind) {
            case 1:
                D_800AA248.cur_obj->unk_68.h = &e->icon_timers[0];
                break;
            case 2:
                D_800AA248.cur_obj->unk_68.h = &e->icon_timers[1];
                break;
            default:
                D_800AA248.cur_obj->unk_68.h = &e->icon_timers[2];
                break;
            }
            break;
        }
    }
    D_800AA268.p = saved;
}

void bonus_update_icons(Monster *e) {
    s16 used[3];
    GameObject *obj;
    s32 i;
    s16 x;
    s32 half;
    u16 v;

    memset(used, 0, sizeof(used));
    i = 0;
    if (D_801FA8A0[e->id - 1] == 0) {
        return;
    }
    x = (D_801FA8A0[e->id - 1] - 2) * 0x78 + 0x96;
    for (; i < 3; i++) {
        obj = e->icons[i];
        if (obj != NULL) {
            half = (s16) obj->size.u.lo / 2;
            if (obj->pos_x.s.hi - half == x) {
                x = obj->pos_x.u.hi + half + 4;
                used[i] = 1;
                i = -1;
            }
        }
    }
    for (i = 0; i < 3; i++) {
        obj = e->icons[i];
        if (used[i] == 0 && obj != NULL) {
            obj->pos_x.s.hi--;
        }
    }
    for (i = 0; i < 3; i++) {
        obj = e->icons[i];
        if (obj != NULL) {
            v = *obj->unk_68.h;
            if (v == 0) {
                func_8001E4B0(obj);
                e->icons[i] = NULL;
            } else if (v < 0x40) {
                if ((v & 0xF) < 7) {
                    func_8001BB88(obj);
                } else {
                    func_8001BB68(obj);
                }
            }
        }
    }
}

void func_8005E0E0(void) {
}

void func_8005E0E8(GameObject *b) {
    s32 vy;

    b->unk_20++;
    vy = b->vel_y.w + 0x58000;
    b->vel_y.w = vy;
    if (vy > 0x440000) {
        b->vel_y.w = 0x440000;
    }
}

void func_8005E124(Monster *e, s32 base) {
    GameObject *s;
    GameObject *head;

    head = &D_801E28C0;
    s = head->next;
    if (s != head) {
        do {
            if (s->kind == base + e->id) {
                func_8001BB68(s);
            }
            s = s->next;
        } while (s != head);
    }
}

void func_8005E19C(Monster *e, s32 base) {
    GameObject *s;
    GameObject *head;

    head = &D_801E28C0;
    s = head->next;
    if (s != head) {
        do {
            if (s->kind == base + e->id) {
                func_8001BB88(s);
            }
            s = s->next;
        } while (s != head);
    }
}

void func_8005E214(void) {
    u8 *table;

    D_801FB46C = 1;
    if (D_800AA2DC & 0x30) {
        table = NULL;
        switch (D_8007BD7C) {
        case 0:
        case 1:
            table = D_80089678;
            break;
        case 2:
            table = D_8008969C;
            break;
        case 3:
            table = D_800896C0;
            break;
        }
        if (table != NULL) {
            func_8006036C(D_8007AD4C, 0x9B, 0x50, 0x44, 0x402, table);
        }
    }
    D_800AA2EC = 0x47;
    func_8001ED54(&D_80089604);
}

void func_8005E2D8(void) {
    s16 t;

    if (D_801FB46C != 0) {
        t = D_801FB46C + 1;
        D_801FB46C = t;
        switch (t) {
        case 0x3C:
            main_free_kind(0x401);
            func_8001ED54(&D_80089624);
            break;
        case 0x78:
            main_free_kind(0x401);
            func_8001ED54(&D_80089644);
            break;
        case 0xB4:
            main_free_kind(0x401);
            main_free_kind(0x402);
            D_801FB46C = 0;
            break;
        }
    }
}

void func_8005E398(void) {
    D_801FB468 = 0;
    if (D_800AA2DC != 0) {
        bonus_start_round();
    }
}

void func_8005E3CC(void) {
    switch (D_800AA2DC) {
    case 1:
    case 2:
    case 4:
    case 8:
    case 0x10:
    case 0x20:
    case 0x40:
    case 0x80:
    case 0x100:
    case 0x200:
    case 0x400:
    case 0x800:
    case 0x1000:
    case 0x2000:
    case 0x4000:
        func_8005E2D8();
        break;
    }
}

s32 func_8005E4E4(void) {
    switch (D_800AA2DC) {
    case 1:
        return 4;
    case 2:
    case 4:
    case 0x40:
    case 0x80:
    case 0x100:
    case 0x1000:
    case 0x2000:
    case 0x4000:
        return 1;
    case 8:
    case 0x10:
    case 0x20:
        return 2;
    }
    return 0;
}

s32 func_8005E5C8(void) {
    switch (D_800AA2DC) {
    case 1:
    case 2:
    case 4:
        if (D_801FB46C != 0) {
            return 1;
        }
        break;
    }
    return 0;
}

void bonus_check_round_end(void) {
    Building *b;
    Building *cur;
    Monster *m;
    Monster *other;
    s32 i;
    s32 n;
    u16 k;
    s16 count;

    D_800AA250 = 7;
    if (D_801FB468 != 0) {
        return;
    }
    switch (D_800AA2DC) {
    case 1:
    case 2:
    case 4:
        b = D_801D3DC8;
        cur = b;
        k = 0;
        count = 0;
        do {
            if (cur->unk_058 == 0 && cur->state == 0x11) {
                count++;
                if (D_801D8740 >= 2) {
                    break;
                }
            }
            cur = ++b;
        } while (k++ < (s16)D_801E29A4);
        if (D_801D8740 == 1 && count == 2) {
            if (D_801FB468 == 0) {
                D_801FB468 = D_801FB49C[0];
            }
            D_801FA890 = 0x1E0;
            return;
        }
        if (D_801D8740 >= 2 && count != 0) {
            if (D_801FB468 == 0) {
                D_801FB468 = D_801FB49C[k];
            }
            D_801FA890 = 0x1E0;
            return;
        }
        if (D_8007BD78.round_timer == 0) {
            D_801FA890 = 0x1E0;
            D_801FB468 = 1;
            D_8007BD78.unk_18[0] = count;
            D_8007BD78.flags |= 0x100000;
            return;
        }
        bonus_update_counters(0);
        break;
    case 8:
    case 0x10:
    case 0x20:
        if (D_8007BD78.round_timer == 0) {
            if (D_8007BD78.unk_04 == D_801FB49C[D_801D8740 - 1]) {
                D_801FA890 = 0x1E0;
                D_801FB468 = 1;
                return;
            }
            D_8007BD78.unk_04 = cdload_get_next_player(D_8007BD78.unk_04);
            D_8007BD78.round_timer = 0x14;
            D_8007BD78.unk_18[3] = 0;
            D_8007BD78.flags |= 0x200;
            if (D_8007BD78.digits[3][1] != NULL) {
                func_8001E4B0(D_8007BD78.digits[3][1]);
                D_8007BD78.digits[3][1] = NULL;
            }
            if (D_8007BD78.digits[3][0] != NULL) {
                func_8001E4B0(D_8007BD78.digits[3][0]);
                D_8007BD78.digits[3][0] = NULL;
            }
            bonus_create_counter(4, 4);
        }
        bonus_update_counters(1);
        m = &D_801E0B78[func_80025DF8(D_801FB49C[D_801D8740 - 1])];
        if (m->unk_1DE != 0) {
            m = &D_801E0B78[func_80025DF8(D_8007BD7C)];
            m->unk_100 = 0;
            m->obj->vel_x.w = 0;
            if ((u16)func_80031714(m) == 0) {
                m->action = 0;
            }
            D_801FB468 = 1;
            D_801FA890 = 0x1E0;
            return;
        }
        m = &D_801E0B78[func_80025DF8(D_8007BD78.unk_04)];
        if (m->unk_1DE != 0) {
            D_8007BD78.flags |= 0x200;
            m = &D_801E0B78[func_80025DF8(D_8007BD78.unk_04)];
            m->unk_100 = 0;
            m->obj->vel_x.w = 0;
            if ((u16)func_80031714(m) == 0) {
                m->action = 0;
            }
            D_8007BD78.unk_18[3] = 0;
            D_8007BD78.round_timer = 0;
        }
        break;
    case 0x40:
    case 0x80:
    case 0x100:
        if (D_8007BD78.round_timer != 0) {
            bonus_update_counters(2);
            break;
        }
        for (i = 0; i < D_801D8740; i++) {
            D_8007BD78.unk_08[D_801FB49C[i] - 1] = (D_8007BD78.unk_08[D_801FB49C[i] - 1] << 16) | D_8007BD78.unk_18[D_801FB49C[i] - 1];
        }
        D_801FB468 = 0;
        for (i = 1; i < D_801D8740; i++) {
            if ((u32)D_8007BD78.unk_08[D_801FB49C[D_801FB468] - 1] <= (u32)D_8007BD78.unk_08[D_801FB49C[i] - 1]) {
                D_801FB468 = i;
            }
        }
        D_801FB468 = D_801FB49C[D_801FB468];
        D_801FA890 = 0x1E0;
        break;
    case 0x200:
    case 0x400:
    case 0x800:
        if (D_8007BD8C != 0) {
            bonus_update_counters(3);
            break;
        }
        D_801FA890 = 0x1E0;
        D_801FB468 = 1;
        break;
    case 0x1000:
    case 0x2000:
    case 0x4000:
        func_80060BA8();
        if (D_8007BD78.round_timer == 0) {
            D_801FB468 = 0;
            D_8007BD78.flags |= 0x100000;
            for (i = 1; i < D_801D8740; i++) {
                m = &D_801E0B78[func_80025DF8(D_801FB49C[D_801FB468])];
                other = &D_801E0B78[func_80025DF8(D_801FB49C[i])];
                if (m->health.w > other->health.w) {
                    D_8007BD78.flags &= ~0x100000;
                } else {
                    if (m->health.w < other->health.w) {
                        D_8007BD78.flags &= ~0x100000;
                    }
                    D_801FB468 = i;
                }
            }
            D_801FA890 = 0x1E0;
            D_8007A68A = D_801FB464;
            D_801FB468 = D_801FB49C[D_801FB468];
            break;
        }
        n = 0;
        for (i = 0; i < D_801D8740; i++) {
            m = &D_801E0B78[func_80025DF8(D_801FB49C[i])];
            if ((m->unk_058 & 1) && m->unk_184 == 0) {
                n++;
                D_801FB468 = D_801FB49C[i];
            }
        }
        if (n < 2) {
            D_801FA890 = 0x1E0;
            D_8007A68A = D_801FB464;
            break;
        }
        D_801FB468 = 0;
        bonus_update_counters(4);
        break;
    }
}

void bonus_start_round(void) {
    Monster *e;
    u16 saved;

    D_800AA250 = 7;
    func_8005E214();
    bonus_save_health();
    func_80062E44();
    switch (D_800AA2DC) {
    case 1:
    case 2:
    case 4:
        D_8007BD78.flags |= 0x480;
        if (D_801D8740 == 1) {
            D_8007BD78.round_timer = 0x2D;
        } else {
            D_8007BD78.round_timer = 0x3C;
        }
        bonus_create_counter(4, 4);
        break;
    case 8:
    case 0x10:
    case 0x20:
        D_8007BD78.round_timer = 0x14;
        D_8007BD78.flags |= 0x5C0;
        bonus_create_counter(4, 4);
        func_8005F12C();
        break;
    case 0x40:
    case 0x80:
    case 0x100:
        D_8007BD78.round_timer = 0x3C;
        D_8007BD78.flags |= 0x4C0;
        bonus_create_counter(4, 4);
        break;
    case 0x200:
    case 0x400:
    case 0x800:
        if (D_801D8740 == 1) {
            D_8007BD8C = 0x1E;
        } else {
            D_8007BD8C = 0x2D;
        }
        D_8007BD78.flags |= 0x440;
        bonus_create_counter(4, 4);
        break;
    case 0x1000:
    case 0x2000:
    case 0x4000:
        saved = D_8007A68A;
        D_8007A68A = 1;
        D_8007BD78.round_timer = 0x2D;
        D_801FB464 = saved;
        D_8007BD78.flags |= 0xC0;
        bonus_create_counter(4, 4);
        do {
            e = &D_801E0B78[D_800AA248.unk_08];
            if (e->unk_058 & 1) {
                e->unk_184 = 0;
                e->unk_0F0 = 0;
                e->health.w = 0x440000;
                func_80060D44(e);
            }
        } while (--D_800AA248.unk_08 != 0);
        break;
    }
}

void func_8005F12C(void) {
    Monster *e;
    s32 i;

    D_8007BD78.flags |= 0x80;
    D_8007BD78.unk_04 = D_801FB49C[0];
    for (i = 0; i < (s32) D_801D8740; i++) {
        e = &D_801E0B78[func_80025DF8(D_801FB49C[i])];
        if (e->unk_058 & 1) {
            e->climb_side = 3;
            e->climb_building = 1;
            e->obj->pos_x.s.hi = 0x82 - i * 0x28;
        }
    }
}

s32 bonus_get_round_kind(void) {
    switch (D_800AA2DC) {
    case 1:
    case 2:
    case 4:
        return 0;
    case 8:
    case 0x10:
    case 0x20:
        return 1;
    case 0x40:
    case 0x80:
    case 0x100:
        return 2;
    case 0x200:
    case 0x400:
    case 0x800:
        return 3;
    case 0x1000:
    case 0x2000:
    case 0x4000:
        return 4;
    }
    return -1;
}

#ifdef NON_MATCHING
/* 99.38%: registers only: x and i swap s2/s3. The per-arm pos_x/id stores (merged by cross-jumping) give the
 * original's store order; global-alloc then ranks x (16 refs over 114 insns, priority 0.56) above i (10 over 78,
 * 0.38); the original allocates i first (i and kind share s2). Declared s16, x gets the original's registers (cse
 * moves the first-part stores onto the SImode sum, so x drops to 14 refs, 0.37) but keeps that sum in v1 and copies
 * it into x (one move, size +4, 99.3 %); stepwise, reordered and cast forms of the first x keep the copy; a single
 * pos_x store or an id variable lose the store order */
void bonus_create_counter(s32 kind, s32 n) {
    GameObject *saved;
    ObjectDef *def;
    s32 y;
    s32 count;
    s32 v;
    s32 x;
    s32 i;

    saved = D_800AA248.cur_obj;
    D_800AA248.new_def = func_8001D110();
    def = D_800AA248.new_def;
    if (n < 4) {
        x = (n - 2) * 0x78 + 0x96;
        y = 0;
        v = 0;
        count = 3;
        if (kind == 1) {
            def->pos_x.s.hi = x;
            def->id = 0x4F00230A;
        } else {
            def->pos_x.s.hi = x;
            def->id = 0x4F0021DE;
        }
        def->pos_y.s.hi = y + 0x30;
        def->flags = 0x500;
        def->unk_06 |= 0x20;
        D_800AA268.p = func_8001DCB4();
        D_800AA268.p->kind = n + 0x7B0;
    } else {
        x = 0x64;
        y = 0xAA;
        count = 2;
        v = D_8007BD8C;
    }
    x += 0x5B;
    for (i = 0; i < count; i++) {
        def->pos_x.s.hi = x;
        if (n < 4) {
            def->id = D_800842B4[v % 10];
        } else {
            def->id = D_800842DC[v % 10];
        }
        def->pos_y.s.hi = y + 0x30;
        def->unk_06 |= 0x20;
        def->flags = n < 4 ? 0x500 : 0x7000;
        D_800AA248.cur_obj = func_8001DCB4();
        D_800AA248.cur_obj->kind = n + 0x7B0;
        D_8007BD78.digits[n - 1][i] = D_800AA248.cur_obj;
        v /= 10;
        if (n < 4) {
            x -= 8;
        } else {
            x -= 0xE;
            D_800AA248.cur_obj->unk_74 = 0x47;
        }
    }
    D_800AA268.p = saved;
    D_8007BD78.flags |= 0x10;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/bonus", bonus_create_counter);
#endif

#ifdef NON_MATCHING
/* 99.83%: global-alloc order in case 2: the inner loop's copy of &D_801FB49C[n] (loop.c's hoist of the inner
 * invariant, rewritten as a copy of the outer giv: set at depth 2, one use at depth 3, 5 refs over 34 insns, 0.29)
 * outranks the D_8007BD78 base (14 over 170, 0.25), so the copy takes s4; the base needs 16 refs or a live length
 * of 142 to come first. Loop-variable (j for the inner loop changes the size: the original shares i with the round-
 * timer loop), ++/+= and loop-bound forms tried */
void bonus_update_counters(s32 round) {
    Monster *m;
    GameObject *obj;
    s32 v;
    s32 i;
    s32 j;
    s32 n;

    if (D_801FB46C != 0) {
        return;
    }
    switch (round) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        if (!(D_8007BD78.flags & 0x10)) {
            return;
        }
        if (!(D_8007BD78.flags & 0x200)) {
            D_8007BD78.unk_18[3]++;
        }
        if (D_8007BD78.unk_18[3] == 0x3C) {
            D_8007BD78.unk_18[3] = 0;
            if (D_8007BD78.round_timer != 0) {
                D_8007BD78.round_timer--;
            }
            v = D_8007BD78.round_timer;
            if (v < 10 && D_8007BD78.digits[3][1] != NULL) {
                func_8001E4B0(D_8007BD78.digits[3][1]);
                D_8007BD78.digits[3][1] = NULL;
            }
            if (v == 0 && D_8007BD78.digits[3][0] != NULL) {
                func_8001E4B0(D_8007BD78.digits[3][0]);
                D_8007BD78.digits[3][0] = NULL;
            }
            for (i = 0; i < 2; i++) {
                obj = D_8007BD78.digits[3][i];
                if (obj != NULL) {
                    main_set_frame(D_800842DC[v % 10], obj->flags, obj);
                    v /= 10;
                }
            }
        }
        break;
    }
    switch (round) {
    case 2:
        for (n = 0; n < D_801D8740; n++) {
            m = &D_801E0B78[func_80025DF8(D_801FB49C[n])];
            if (bonus_get_round_kind() != 2 || m->climb_side == 3) {
                D_8007BD78.unk_18[D_801FB49C[n] - 1]++;
            }
            if (D_8007BD78.unk_18[D_801FB49C[n] - 1] == 0x3C) {
                D_8007BD78.unk_08[D_801FB49C[n] - 1]++;
                D_8007BD78.unk_18[D_801FB49C[n] - 1] = 0;
                v = D_8007BD78.unk_08[D_801FB49C[n] - 1];
                for (i = 0; i < 3; i++) {
                    obj = D_8007BD78.digits[D_801FB49C[n] - 1][i];
                    if (obj != NULL) {
                        main_set_frame(D_800842B4[v % 10], obj->flags, obj);
                        v /= 10;
                    }
                }
            }
        }
        break;
    case 3:
        if (D_8007BD78.flags & 0x20) {
            for (n = 0; n < D_801D8740; n++) {
                v = D_8007BD78.unk_08[D_801FB49C[n] - 1];
                for (j = 0; j < 3; j++) {
                    obj = D_8007BD78.digits[D_801FB49C[n] - 1][j];
                    if (obj != NULL) {
                        main_set_frame(D_800842B4[v % 10], obj->flags, obj);
                        v /= 10;
                    }
                }
            }
            D_8007BD78.flags &= ~0x20;
        }
        break;
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/bonus", bonus_update_counters);
#endif

void bonus_save_health(void) {
    Monster *e;
    s32 i;

    for (i = 0; i < (s32) D_801D8740; i++) {
        e = &D_801E0B78[func_80025DF8(D_801FB49C[i])];
        e->unk_0F0 = 0;
        e->unk_17C = e->health.w;
        e->lives_shown = e->lives;
    }
}

void bonus_restore_health(void) {
    Monster *e;
    s32 i;

    for (i = 0; i < (s32) D_801D8740; i++) {
        e = &D_801E0B78[func_80025DF8(D_801FB49C[i])];
        e->unk_0F0 = 0;
        e->health.w = e->unk_17C;
    }
}

void bonus_award_places(void) {
    Monster *m;
    s32 i;
    s32 k;
    s16 best;
    s32 bestx;
    s16 x;
    u32 score;

    D_8007BD78.flags |= 0x10000;
    switch (D_800AA2DC) {
    case 1:
    case 2:
    case 4:
        if (!(D_8007BD78.flags & 0x100000)) {
            bonus_give_awards(D_801FB468, 0xD);
        } else if (D_801D8740 == 1 && D_8007BD78.unk_18[0] == D_801D8740) {
            bonus_give_awards(D_801FB468, 0xD);
        }
        break;
    case 8:
    case 0x10:
    case 0x20:
        bestx = 0;
        best = -1;
        for (i = 0; i < D_801D8740; i++) {
            m = &D_801E0B78[func_80025DF8(D_801FB49C[i])];
            if ((u16) func_80031714(m) != 1 && m->obj->pos_y.s.hi >= 0xD7) {
                x = m->obj->pos_x.s.hi;
                for (k = 0; k < 5; k++) {
                    if (x < D_80084328[k]) {
                        break;
                    }
                }
                if (k != 0 && (best == -1 || bestx < x)) {
                    best = D_801FB49C[i];
                    bestx = x;
                }
                bonus_give_awards(D_801FB49C[i], D_80084314[k]);
            }
        }
        D_801FB468 = best;
        break;
    case 0x40:
    case 0x80:
    case 0x100:
        if (D_8007BD78.unk_08[D_801FB468 - 1] == 0) {
            D_801FB468 = -1;
        } else {
            bonus_give_awards(D_801FB468, 0xD);
        }
        break;
    case 0x200:
    case 0x400:
    case 0x800:
        bestx = 0;
        best = -1;
        for (i = 0; i < D_801D8740; i++) {
            m = &D_801E0B78[func_80025DF8(D_801FB49C[i])];
            score = D_8007BD78.unk_08[D_801FB49C[i] - 1];
            for (k = 0; k < 4; k++) {
                if (score < D_8008433C[k]) {
                    break;
                }
            }
            if (k != 0 && (best == -1 || (u32) bestx < score)) {
                best = D_801FB49C[i];
                bestx = score;
            }
            bonus_give_awards(D_801FB49C[i], D_80084314[k]);
        }
        D_801FB468 = best;
        break;
    case 0x1000:
    case 0x2000:
    case 0x4000:
        bonus_give_awards(D_801FB468, 0xD);
        break;
    }
}

void bonus_give_awards(s32 player, s32 awards) {
    Monster *m;
    ObjectDef *def;
    u16 frame;
    s32 i;
    s32 kind;

    if (awards == 0) {
        return;
    }
    if (D_8007BD78.flags & 0x100000) {
        D_801FB468 = -1;
        return;
    }
    m = &D_801E0B78[func_80025DF8(player)];
    def = func_8001D110();
    switch (player) {
    case 1:
        D_8007BD78.flags |= 0x1000000;
        break;
    case 2:
        D_8007BD78.flags |= 0x2000000;
        break;
    case 3:
        D_8007BD78.flags |= 0x4000000;
        break;
    }
    /* Class B: the block's loop notes count the frame's three sets twice, so it gets s4 before the D_800AA248 base, as
     * in the original (the plain if, the set orders and the frame's type leave the two swapped); the same shape in
     * bonus_create_lives and bonus_give_awards, a macro's block, likely. */
    LOOP_BLOCK(
        if (m->id == 7 && D_801F9ABC != 0) {
            if (D_801F9ABC == 3) {
                frame = 0x53;
            } else {
                frame = 0x54;
            }
        } else {
            frame = 0xFFFF;
        }
    );
    i = 0;
    if (awards & 1) {
        m->lives++;
        m->lives_shown++;
        for (i = 0; i < 6; i++) {
            if (D_8007BD78.lives_icons[i] == 0) {
                break;
            }
        }
        kind = 0x7E0;
        def->pos_x.s.hi = i * 0x11 + 0xDC;
        def->id = D_80084298[m->id - 1];
        def->pos_y.s.hi = 0x6C;
        def->flags = 0x7001;
        def->unk_06 |= 0x20;
        D_800AA248.cur_obj = func_8001DCB4();
        D_800AA248.cur_obj->kind = kind;
        D_800AA248.cur_obj->unk_74 = frame;
        D_8007BD78.lives_icons[i] = kind;
        func_80060A7C(kind, 0, 1);
        if (awards & 2) {
            i++;
            m->lives++;
            m->lives_shown++;
            def->pos_x.s.hi = i * 0x11 + 0xDC;
            def->id = D_80084298[m->id - 1];
            def->pos_y.s.hi = 0x6C;
            def->flags = 0x7001;
            def->unk_06 |= 0x20;
            D_800AA248.cur_obj = func_8001DCB4();
            D_800AA248.cur_obj->kind = kind;
            D_800AA248.cur_obj->unk_74 = frame;
            D_8007BD78.lives_icons[i] = kind;
            func_80060A7C(kind, 0, 1);
        }
    }
    for (i = 0; i < 3; i++) {
        if (D_8007BD78.health_icons[i] == 0) {
            break;
        }
    }
    if (awards & 4) {
        kind = 0x7E1;
        m->health.w = 0x440000;
        m->unk_17C = 0x440000;
        m->unk_01A &= 0xFFF0;
        def->pos_x.s.hi = i * 0x11 + 0xDC;
        def->id = D_80084298[m->id - 1];
        def->pos_y.s.hi = 0x85;
        def->unk_06 |= 0x20;
        def->flags = 0x7001;
        D_800AA248.cur_obj = func_8001DCB4();
        D_800AA248.cur_obj->kind = kind;
        D_800AA248.cur_obj->unk_74 = frame;
        D_8007BD78.health_icons[i] = kind;
        func_80060A7C(kind, 0, 1);
    }
    for (i = 0; i < 3; i++) {
        if (D_8007BD78.meter_icons[i] == 0) {
            break;
        }
    }
    if (awards & 8) {
        kind = 0x7E2;
        m->meter.w = 0x440000;
        def->pos_x.s.hi = i * 0x11 + 0xDC;
        def->id = D_80084298[m->id - 1];
        def->pos_y.s.hi = 0x9E;
        def->unk_06 |= 0x20;
        def->flags = 0x7001;
        D_800AA248.cur_obj = func_8001DCB4();
        D_800AA248.cur_obj->kind = kind;
        D_800AA248.cur_obj->unk_74 = frame;
        D_8007BD78.meter_icons[i] = kind;
        func_80060A7C(kind, 0, 1);
    }
}

void func_8006036C(s32 *glyphs, s32 x, s32 y, s32 n, s32 kind, u8 *text) {
    if (glyphs == D_8007ABCC) {
        D_801FB474 = 2;
    } else {
        D_801FB474 = 1;
    }
    D_800AA2EC = n;
    D_801FB470.glyphs = glyphs;
    D_801FB470.x = x;
    D_801FB470.y = y;
    D_801FB470.unk_0C = n;
    D_801FB470.layout = func_8001EE24;
    D_801FB470.kind = kind;
    strcpy(D_801FB470.text, text);
    func_8001ED54(&D_801FB470);
}

void func_800603FC(s32 *id, s32 dx, s32 dy, s32 x, s32 y) {
    GameObject *s;
    GameObject *hit;
    GameObject *head;
    u32 c;

    if (*id != 0) {
        head = &D_801E28C0;
        s = head->next;
        hit = NULL;
        if (s != head) {
            do {
                if (s->kind == *id) {
                    c = s->colour.w;
                    s->pos_y.s.hi += dy;
                    s->unk_28.w = (s->unk_28.w & 0xFFFF) | (s->pos_y.s.hi << 16);
                    s->pos_x.s.hi += dx;
                    s->unk_28.w = (s->unk_28.w & 0xFFFF0000) | s->pos_x.u.hi;
                    if (c <= 0x80807F) {
                        s->colour.w = c + 0x40404;
                    } else if (c > 0x808080) {
                        s->colour.w = 0x808080;
                    }
                    hit = s;
                }
                s = s->next;
            } while (s != head);
        }
        if (hit != NULL && hit->pos_x.s.hi == x && hit->pos_y.s.hi == y) {
            func_80060A7C(*id, 0x808080, 1);
            func_8001F724(5);
            *id = 0;
        }
    }
}

void bonus_update_awards(void) {
    GameObject *box;
    Monster *m;
    s32 i;
    s32 bit;

    if (D_800AA2DC == 0 || !(D_8007BD78.flags & 0x8000)) {
        return;
    }
    if (!(D_8007BD78.flags & 0x10000)) {
        bonus_award_places();
    }
    if (!(D_8007BD78.flags & 0x800)) {
        func_800636B0();
        box = main_create_box(0x46, 0x3C, 0x104, 0x73, 0);
        box->priority = 0x7000;
        box->kind = 0x7D4;
        box->flags |= 0x40C;
        box->unk_6C |= 0x20;
        D_8007BD78.unk_20 = 0;
        D_8007BD78.flags |= 0x800;
        func_8006036C(D_8007AD4C, 0x78, 0x46, 0x44, 0x7D0, "BONUS AWARDS!!");
        D_8007BD78.unk_54 = 0x7D0;
        func_80060A7C(0x7D0, 0x404040, 1);
    }
    if (!(D_8007BD78.flags & 0x4000) && D_8007BD78.unk_20 > 0x3C) {
        D_8007BD78.flags |= 0x24000;
        func_8006036C(D_8007AD4C, 0x6E, 0x69, 0x47, 0x7D1, "LIFE");
        D_8007BD78.unk_58[2] = 0x7D1;
        func_80060A7C(0x7D1, 0x404040, 1);
    }
    if (!(D_8007BD78.flags & 0x1000) && D_8007BD78.unk_20 > 0x78) {
        D_8007BD78.flags |= 0x41000;
        func_8006036C(D_8007AD4C, 0x6E, 0x82, 0x47, 0x7D2, "HEALTH");
        D_8007BD78.unk_58[0] = 0x7D2;
        func_80060A7C(0x7D2, 0x404040, 1);
    }
    if (!(D_8007BD78.flags & 0x2000) && D_8007BD78.unk_20 > 0xB4) {
        D_8007BD78.flags |= 0x82000;
        func_8006036C(D_8007AD4C, 0x6E, 0x9B, 0x47, 0x7D3, "POWER");
        D_8007BD78.unk_58[1] = 0x7D3;
        func_80060A7C(0x7D3, 0x404040, 1);
    }
    if (D_8007BD78.unk_54 != 0) {
        func_800603FC(&D_8007BD78.unk_54, 0, 5, 0x78, 0x4B);
    }
    if (D_8007BD78.unk_58[2] != 0) {
        func_800603FC(&D_8007BD78.unk_58[2], 0xA, 0, 0x78, 0x69);
    }
    if (D_8007BD78.unk_58[0] != 0) {
        func_800603FC(&D_8007BD78.unk_58[0], 0xA, 0, 0x78, 0x82);
    }
    if (D_8007BD78.unk_58[1] != 0) {
        func_800603FC(&D_8007BD78.unk_58[1], 0xA, 0, 0x78, 0x9B);
    }
    if (D_8007BD78.unk_58[2] == 0 && (D_8007BD78.flags & 0x20000)) {
        func_80060A7C(0x7E0, 0x40404, 2);
    }
    if (D_8007BD78.unk_58[0] == 0 && (D_8007BD78.flags & 0x40000)) {
        func_80060A7C(0x7E1, 0x40404, 2);
    }
    if (D_8007BD78.unk_58[1] == 0 && (D_8007BD78.flags & 0x80000)) {
        func_80060A7C(0x7E2, 0x40404, 2);
    }
    if (D_8007BD78.flags & 0x07000000) {
        for (i = 0; i < D_801D8740; i++) {
            m = &D_801E0B78[func_80025DF8(D_801FB49C[i])];
            if (m != NULL && (m->action == 0 || m->obj->pos_y.s.hi == 0xE1 || m->climb_side == 3)) {
                switch (D_801FB49C[i]) {
                case 1:
                    if (D_8007BD78.flags & 0x01000000) {
                        m->action = 0x62;
                    }
                    break;
                case 2:
                    if (D_8007BD78.flags & 0x02000000) {
                        m->action = 0x62;
                    }
                    break;
                case 3:
                    if (D_8007BD78.flags & 0x04000000) {
                        m->action = 0x62;
                    }
                    break;
                }
            }
        }
    }
    if (D_801FA890 <= 0) {
        bonus_restore_health();
        memset(&D_8007BD78, 0, sizeof(D_8007BD78));
    }
    D_8007BD78.unk_20++;
}

void func_80060A7C(s32 id, u32 color, s32 mode) {
    GameObject *s;
    GameObject *head;

    head = &D_801E28C0;
    s = head->next;
    if (s != head) {
        do {
            if (s->kind == id) {
                if (mode & 1) {
                    s->colour.w = color;
                    if (color != 0x808080) {
                        s->flags |= 0x500;
                    } else {
                        s->flags &= 0xFAFF;
                    }
                } else if (mode & 4) {
                    s->colour.w = color;
                    if (color != 0x808080) {
                        s->flags |= 0x40C;
                    } else {
                        s->flags &= 0xFBF3;
                    }
                } else {
                    s->colour.w += color;
                    if (s->colour.w > 0x808080U) {
                        s->colour.w = 0x808080;
                        s->flags &= 0xFAFF;
                        switch (id) {
                        case 0x7E0:
                            D_8007BD78.flags &= 0xFFFDFFFF;
                            break;
                        case 0x7E1:
                            D_8007BD78.flags &= 0xFFFBFFFF;
                            break;
                        case 0x7E2:
                            D_8007BD78.flags &= 0xFFF7FFFF;
                            break;
                        }
                    }
                }
            }
            s = s->next;
        } while (s != head);
    }
}

void func_80060BA8(void) {
    Monster *e;
    u16 state;
    s32 i;

    if (D_800AA2DC & 0x7000) {
        for (i = 0; i < (s32) D_801D8740; i++) {
            e = &D_801E0B78[func_80025DF8(D_801FB49C[i])];
            if (e->health.w <= 0x40000 && e->unk_184 == 0) {
                e->health.w = 0;
                if (e->climb_side != 0 || (state = e->action) == 0x23 || state == 0xF || state == 0x17) {
                    if (e->action != 0x23) {
                        e->action = 0x1D;
                    }
                } else {
                    switch (e->action) {
                    case 0x1C:
                    case 0x39:
                        e->action = 0x5B;
                        break;
                    case 0xA:
                    case 0x1D:
                    case 0x24:
                    case 0x2F:
                        e->action = 0x59;
                        break;
                    case 0xB:
                    case 0x22:
                    case 0x23:
                        e->action = 0x5A;
                        break;
                    case 0x28:
                        e->action = 0x5C;
                        break;
                    case 0x3A:
                        e->action = 0x5E;
                        break;
                    case 0x1E:
                    case 0x29:
                        e->action = 0x5D;
                        break;
                    default:
                        e->action = 0x59;
                        return;
                    }
                }
                e->unk_0DC = 0;
                e->unk_184 = 1;
            }
        }
    }
}

void func_80060D44(Monster *e) {
    switch (D_801FA8A0[e->id - 1]) {
    case 1:
        e->unk_168 = 3;
        break;
    default:
        if (!(D_801E0B78[1].unk_058 & 1)) {
            e->unk_168 = 3;
        }
        break;
    case 2:
    case 3:
        e->obj->flags |= 0x10;
        e->unk_168 = 7;
        break;
    }
}

void func_80060DCC(void) {
    GameObject *saved;
    ObjectDef *node;

    saved = D_800AA268.p;
    switch (D_801FA960) {
    case 0x18:
    case 0x31:
    case 0x4A:
    case 0x63:
        if (D_801FA890 == 0) {
            D_800AA268.p = saved;
            return;
        }
        if (!(D_8007BD78.flags & 0x800)) {
            node = func_8001D110();
            node->anim = &D_80016A84;
            node->id = D_80016A84.id;
            node->pos_x.s.hi = 0xC8;
            node->pos_y.s.hi = 0xFA;
            node->flags = 0x7000;
            node->unk_0C = 0x7D0;
            node->unk_06 |= 0x20;
            D_800AA248.cur_obj = func_8001DCB4();
            D_801FA890 += 0x28;
            func_80060A7C(D_8007BD78.unk_54, 0x40404, 1);
            D_8007BD78.unk_54 = 0x7D0;
            D_800AA248.cur_obj = saved;
            D_8007BD78.flags |= 0x800;
            return;
        }
        if (D_8007BD78.unk_54 != 0) {
            func_800603FC(&D_8007BD78.unk_54, 0, -5, 0xC8, 0x3C);
        }
        D_800AA268.p = saved;
        break;
    default:
        D_800AA268.p = saved;
        break;
    }
}
