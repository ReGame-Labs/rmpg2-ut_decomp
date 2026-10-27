/* A file of the game's code, named after its first function until its contents are understood.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "game.h"
#include "game_8005D198.h"
#include "psyq/libc2.h"

s32 func_8005D198(void) {
    return func_8001A3AC() >= 0x46;
}

void func_8005D1BC(s32 arg0, s32 n) {
    func_8001E450((u16)(n + 0x790));
    func_8001E450((u16)(n + 0x798));
    func_8001E450((u16)(n + 0x7A8));
    func_8001E450((u16)(n + 0x7A0));
}

void func_8005D20C(Monster *e) {
    GameObject *saved;
    GameObject *s;
    s32 x;
    s16 x2;

    saved = D_800AA248.cur_obj;
    x = (D_801FA8A0[e->id - 1] - 2) * 0x78;
    s = func_8001EB9C(0, 0, 0x44, 4, 0xFF00);
    x2 = x + 0xA6;
    s->pos_x.s.hi = x2;
    s->pos_y.s.hi = 0x18;
    s->unk_80 = 0x501;
    s->kind = e->id + 0x790;
    e->unk_070 = s;
    s = func_8001EB9C(0, 0, 0, 2, 0xFF00FF);
    s->pos_x.s.hi = x2;
    s->pos_y.s.hi = 0x22;
    s->unk_80 = 0x501;
    s->kind = e->id + 0x790;
    e->unk_06C = s;
    func_8001D110()->id = 0x4F000992;
    s = func_8001DCB4();
    s->pos_x.s.hi = x + 0x96;
    s->pos_y.s.hi = 0x1D;
    s->unk_80 = 0x500;
    s->unk_6C |= 0x20;
    s->kind = e->id + 0x790;
    D_800AA248.cur_obj = saved;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005D364);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005D644);

void func_8005D7D8(Monster *e) {
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
                func_80020BA0(D_800842B4[v % 10], digit->flags, digit);
                v /= 10;
            }
        }
        D_800AA268.p = saved;
    }
}

Monster *func_8005D918(Monster *skip) {
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
                if (v > 0 && best < v && (v != 1 || e->unk_008.w > 0x10FFFF)) {
                    best = e->unk_004;
                    found = e;
                }
            }
        }
    }
    return found;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005D9BC);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005DBC4);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005DD48);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005DF2C);

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
            func_8001E450(0x401);
            func_8001ED54(&D_80089624);
            break;
        case 0x78:
            func_8001E450(0x401);
            func_8001ED54(&D_80089644);
            break;
        case 0xB4:
            func_8001E450(0x401);
            func_8001E450(0x402);
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

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005E4E4);

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

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005E60C);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005EE54);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005F12C);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005F208);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005F33C);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005F5B8);

void func_8005F9FC(void) {
    Monster *e;
    s32 i;

    for (i = 0; i < (s32) D_801D8740; i++) {
        e = &D_801E0B78[func_80025DF8(D_801FB49C[i])];
        e->unk_0F0 = 0;
        e->unk_17C = e->unk_008.w;
        e->unk_002 = e->unk_004;
    }
}

void func_8005FA8C(void) {
    Monster *e;
    s32 i;

    for (i = 0; i < (s32) D_801D8740; i++) {
        e = &D_801E0B78[func_80025DF8(D_801FB49C[i])];
        e->unk_0F0 = 0;
        e->unk_008.w = e->unk_17C;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005FB14);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005FEF4);

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

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_80060524);

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

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_80060BA8);

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
