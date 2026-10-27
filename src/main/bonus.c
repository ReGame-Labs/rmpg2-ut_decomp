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

INCLUDE_ASM("asm/main/nonmatchings/bonus", func_8005D364);

#ifdef NON_MATCHING
/* 92.10%: 92.1 %: the first block's schedule: the original stores new_def through the copy of &D_800AA248 (s5) and
 * orders the definition's stores unk_06, id, pos_y, flags around the table read */
void bonus_create_score(Monster *e) {
    GameObject *saved;
    ObjectDef *def;
    s32 x;
    s16 dx;
    s32 v;
    s32 i;

    saved = D_800AA248.cur_obj;
    def = func_8001D110();
    D_800AA248.new_def = def;
    x = (D_801FA8A0[e->id - 1] - 2) * 0x78;
    def->id = 0x4F0021DE;
    def->pos_y.s.hi = 0x30;
    def->flags = 0x4FF;
    def->unk_06 |= 0x20;
    def->pos_x.s.hi = x + 0x96;
    D_800AA248.cur_obj = func_8001DCB4();
    dx = x + 0xF1;
    D_800AA248.cur_obj->kind = e->id + 0x7A0;
    v = e->unk_038;
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
        e->unk_080[i] = D_800AA248.cur_obj;
    }
    D_800AA268.p = saved;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/bonus", bonus_create_score);
#endif

void bonus_update_score(Monster *e) {
    GameObject *saved;
    GameObject *digit;
    s32 v;
    s32 i;

    saved = D_800AA268.p;
    if (e->id != 0) {
        if (e->unk_038 != e->unk_034) {
            func_8005E19C(e, 0x7A0);
            if (D_800AA2DC == 0 || (!(D_8007BD78.flags & 0x10) && (D_800AA2DC & 1))) {
                func_8005E124(e, 0x7A8);
                func_8005E124(e, 0x798);
            }
        }
        v = e->unk_038;
        e->unk_034 = v;
        for (i = 0; i < 6; i++) {
            digit = e->unk_080[i];
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
                v = e->unk_004;
                if (v > 0 && best < v && (v != 1 || e->health.w > 0x10FFFF)) {
                    best = e->unk_004;
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
    face = e->unk_074;
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
    if (e->unk_004 != e->unk_002) {
        func_8005E124(e, 0x7A0);
        func_8005E19C(e, 0x798);
        func_8005E19C(e, 0x7A8);
    }
    v = e->unk_004;
    e->unk_002 = v;
    if (v >= 0) {
        for (i = 0; i < 2; i++) {
            if (e->unk_078[i] != NULL) {
                face = e->unk_078[i];
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
            D_800AA248.cur_obj->colour &= 0xFF00FF;
            v = D_801D3D80 << 10;
            D_800AA248.cur_obj->colour |= v & 0xE000;
        } else {
            D_800AA248.cur_obj->colour = 0xFF00FF;
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

INCLUDE_ASM("asm/main/nonmatchings/bonus", func_8005DD48);

INCLUDE_ASM("asm/main/nonmatchings/bonus", func_8005DF2C);

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
        func_8005EE54();
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

INCLUDE_ASM("asm/main/nonmatchings/bonus", func_8005E60C);

INCLUDE_ASM("asm/main/nonmatchings/bonus", func_8005EE54);

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

s32 func_8005F208(void) {
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

INCLUDE_ASM("asm/main/nonmatchings/bonus", func_8005F33C);

INCLUDE_ASM("asm/main/nonmatchings/bonus", func_8005F5B8);

void func_8005F9FC(void) {
    Monster *e;
    s32 i;

    for (i = 0; i < (s32) D_801D8740; i++) {
        e = &D_801E0B78[func_80025DF8(D_801FB49C[i])];
        e->unk_0F0 = 0;
        e->unk_17C = e->health.w;
        e->unk_002 = e->unk_004;
    }
}

void func_8005FA8C(void) {
    Monster *e;
    s32 i;

    for (i = 0; i < (s32) D_801D8740; i++) {
        e = &D_801E0B78[func_80025DF8(D_801FB49C[i])];
        e->unk_0F0 = 0;
        e->health.w = e->unk_17C;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/bonus", func_8005FB14);

INCLUDE_ASM("asm/main/nonmatchings/bonus", func_8005FEF4);

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
                    c = s->colour;
                    s->pos_y.s.hi += dy;
                    s->unk_28.w = (s->unk_28.w & 0xFFFF) | (s->pos_y.s.hi << 16);
                    s->pos_x.s.hi += dx;
                    s->unk_28.w = (s->unk_28.w & 0xFFFF0000) | s->pos_x.u.hi;
                    if (c <= 0x80807F) {
                        s->colour = c + 0x40404;
                    } else if (c > 0x808080) {
                        s->colour = 0x808080;
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

INCLUDE_ASM("asm/main/nonmatchings/bonus", func_80060524);

void func_80060A7C(s32 id, u32 color, s32 mode) {
    GameObject *s;
    GameObject *head;

    head = &D_801E28C0;
    s = head->next;
    if (s != head) {
        do {
            if (s->kind == id) {
                if (mode & 1) {
                    s->colour = color;
                    if (color != 0x808080) {
                        s->flags |= 0x500;
                    } else {
                        s->flags &= 0xFAFF;
                    }
                } else if (mode & 4) {
                    s->colour = color;
                    if (color != 0x808080) {
                        s->flags |= 0x40C;
                    } else {
                        s->flags &= 0xFBF3;
                    }
                } else {
                    s->colour += color;
                    if (s->colour > 0x808080U) {
                        s->colour = 0x808080;
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
