/* A file of the game's code, named after its first function until its contents are understood.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "entity.h"
#include "cdload.h"

s32 func_8001A3AC(void);
void func_8001E450(s32);
void func_8001ED54(s32 *);
void func_8005EE54(void);

extern s32 D_80089624[];
extern s32 D_80089644[];
extern s32 D_800AA2DC;
void func_8005E2D8(void);
void func_8006036C(s32 *, s32, s32, s32, s32, s32 *);
void func_80020BA0(s32, u16, Body *);
void func_8005E124(Entity *, s32);
void func_8005E19C(Entity *, s32);
void func_800603FC(s32 *, s32, s32, s32, s32);
s32 func_80025DF8(s32);
extern s32 D_8007AD4C;
extern s32 D_8007BD7C;
extern s32 D_80089604[];
extern s32 D_80089678[];
extern s32 D_8008969C[];
extern s32 D_800896C0[];
extern s16 D_800AA2EC;
extern s32 D_800842B4[];
extern u16 D_801D8740;
extern s32 D_801FB49C[];
extern s32 D_80016A84;
extern s16 D_801FA890;
extern s16 D_801FA960;
void func_8001F724(s32);
Body *func_8001EB9C(s32, s32, s32, s32, s32);
Unk800AA248Node *func_8001D110(void);
Body *func_8001DCB4(void);
void func_80060A7C(s32, u32, s32);
extern Unk7BD78 D_8007BD78;
extern s16 D_8007A68C;
extern Body D_801E28C0;
extern Entity D_801E0B78[];
extern u8 D_801FA8A0[];
extern s16 D_801FB468;
extern s16 D_801FB46C;

s32 func_8005D198(void) {
    return func_8001A3AC() >= 0x46;
}

void func_8005D1BC(s32 arg0, s32 n) {
    func_8001E450((u16)(n + 0x790));
    func_8001E450((u16)(n + 0x798));
    func_8001E450((u16)(n + 0x7A8));
    func_8001E450((u16)(n + 0x7A0));
}

void func_8005D20C(Entity *e) {
    Body *saved;
    Body *s;
    s32 x;
    s16 x2;

    saved = D_800AA248.unk_20;
    x = (D_801FA8A0[e->unk_000 - 1] - 2) * 0x78;
    s = func_8001EB9C(0, 0, 0x44, 4, 0xFF00);
    x2 = x + 0xA6;
    s->unk_16 = x2;
    s->unk_18.h.i = 0x18;
    s->unk_80 = 0x501;
    s->unk_70 = e->unk_000 + 0x790;
    e->unk_070 = s;
    s = func_8001EB9C(0, 0, 0, 2, 0xFF00FF);
    s->unk_16 = x2;
    s->unk_18.h.i = 0x22;
    s->unk_80 = 0x501;
    s->unk_70 = e->unk_000 + 0x790;
    e->unk_06C = s;
    func_8001D110()->unk_00 = 0x4F000992;
    s = func_8001DCB4();
    s->unk_16 = x + 0x96;
    s->unk_18.h.i = 0x1D;
    s->unk_80 = 0x500;
    s->unk_6C |= 0x20;
    s->unk_70 = e->unk_000 + 0x790;
    D_800AA248.unk_20 = saved;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005D364);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005D644);

void func_8005D7D8(Entity *e) {
    Body *saved;
    Body *digit;
    s32 v;
    s32 i;

    saved = D_800AA268.p;
    if (e->unk_000 != 0) {
        if (e->unk_038 != e->unk_034) {
            func_8005E19C(e, 0x7A0);
            if (D_800AA2DC == 0 || (!(D_8007BD78.unk_00 & 0x10) && (D_800AA2DC & 1))) {
                func_8005E124(e, 0x7A8);
                func_8005E124(e, 0x798);
            }
        }
        v = e->unk_038;
        e->unk_034 = v;
        for (i = 0; i < 6; i++) {
            digit = e->unk_080[i];
            if (digit != NULL) {
                func_80020BA0(D_800842B4[v % 10], digit->unk_22, digit);
                v /= 10;
            }
        }
        D_800AA268.p = saved;
    }
}

Entity *func_8005D918(Entity *skip) {
    Entity *e;
    Entity *found;
    s16 best;
    s16 v;
    s32 i;

    best = 0;
    found = NULL;
    if (D_8007A68C != 0) {
        for (i = 0; i < 7; i++) {
            e = &D_801E0B78[i];
            if (skip != e && e->unk_000 != 0) {
                v = e->unk_004;
                if (v > 0 && best < v && (v != 1 || e->unk_008 > 0x10FFFF)) {
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

void func_8005E0E8(Body *b) {
    s32 vy;

    b->unk_20++;
    vy = b->unk_10 + 0x58000;
    b->unk_10 = vy;
    if (vy > 0x440000) {
        b->unk_10 = 0x440000;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005E124);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005E19C);

void func_8005E214(void) {
    s32 *table;

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
            func_8006036C(&D_8007AD4C, 0x9B, 0x50, 0x44, 0x402, table);
        }
    }
    D_800AA2EC = 0x47;
    func_8001ED54(D_80089604);
}

void func_8005E2D8(void) {
    s16 t;

    if (D_801FB46C != 0) {
        t = D_801FB46C + 1;
        D_801FB46C = t;
        switch (t) {
        case 0x3C:
            func_8001E450(0x401);
            func_8001ED54(D_80089624);
            break;
        case 0x78:
            func_8001E450(0x401);
            func_8001ED54(D_80089644);
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

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005E5C8);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005E60C);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005EE54);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005F12C);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005F208);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005F33C);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005F5B8);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005F9FC);

void func_8005FA8C(void) {
    Entity *e;
    s32 i;

    for (i = 0; i < (s32) D_801D8740; i++) {
        e = &D_801E0B78[func_80025DF8(D_801FB49C[i])];
        e->unk_0F0 = 0;
        e->unk_008 = e->unk_17C;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005FB14);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8005FEF4);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_8006036C);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_800603FC);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_80060524);

void func_80060A7C(s32 id, u32 color, s32 mode) {
    Body *s;
    Body *head;

    head = &D_801E28C0;
    s = head->unk_00;
    if (s != head) {
        do {
            if (s->unk_70 == id) {
                if (mode & 1) {
                    s->unk_78 = color;
                    if (color != 0x808080) {
                        s->unk_22 |= 0x500;
                    } else {
                        s->unk_22 &= 0xFAFF;
                    }
                } else if (mode & 4) {
                    s->unk_78 = color;
                    if (color != 0x808080) {
                        s->unk_22 |= 0x40C;
                    } else {
                        s->unk_22 &= 0xFBF3;
                    }
                } else {
                    s->unk_78 += color;
                    if (s->unk_78 > 0x808080U) {
                        s->unk_78 = 0x808080;
                        s->unk_22 &= 0xFAFF;
                        switch (id) {
                        case 0x7E0:
                            D_8007BD78.unk_00 &= 0xFFFDFFFF;
                            break;
                        case 0x7E1:
                            D_8007BD78.unk_00 &= 0xFFFBFFFF;
                            break;
                        case 0x7E2:
                            D_8007BD78.unk_00 &= 0xFFF7FFFF;
                            break;
                        }
                    }
                }
            }
            s = s->unk_00;
        } while (s != head);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_80060BA8);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_80060D44);

INCLUDE_ASM("asm/main/nonmatchings/game_8005D198", func_80060DCC);
