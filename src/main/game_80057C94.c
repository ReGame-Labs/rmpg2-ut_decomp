/* A file of the game's code, named after its first function until its contents are understood.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "cdload.h"
#include "entity.h"

void func_8001F724(s32);
void func_80029118(s32, s32);
void func_8004C38C(void);
void func_80057B94(Entity *, s32 *);
void func_80057BD4(u16, Entity *, s32 *);
void func_80057C38(u16, Entity *, s32 *);

extern s32 D_800AA250;
Unk54728 *func_80054728(u16);
void func_8004A90C(Entity *, Entity *);
void func_8002CFAC(Entity *, Unk54728 *);
void func_8002E278(Entity *, Unk54728 *);
void func_80059710(Entity *, s16, s16);
s32 func_80025DF8(s32);
void func_8001F7CC(s32, s32);
void func_8003D71C(Unk1D85C8 *);
void func_80058680(Entity *, u16);
extern s32 D_800AA2DC;
extern s32 D_80084E58[];
extern s32 D_80084E74[];
extern s32 D_8008496C[];
extern s32 D_80084988[];
extern s32 D_80084E20[];
extern s32 D_8008481C[];
extern s32 D_80084DB0[];
extern s32 D_8008465C[];
void func_80059270(Entity *);
void func_80059294(Entity *);
void func_800595E4(Entity *);
void func_800531C0(Entity *);
s16 func_8001EB10(s32, s32);
void func_8002D370(Entity *, Unk54728Item *, Unk54728 *);
void func_8002DBF4(s32, s32, Entity *, Unk54728Item *);
Unk54728Item *func_8002ED30(s32, Unk54728Item *);
u16 func_8002F558(Unk54728 *);
void func_8003089C(s32, Entity *);
u16 func_8004F7A4(Unk54728 *, s16);
s32 func_8005BC20(s16, s16, s32, s32, Body *, s32);
void func_80053C50(s32, Entity *);
extern Unk54728 D_801D3DC8[];
extern s16 D_801E29A4;
extern s16 D_8007A68A;
extern u16 D_801D8740;
extern s32 D_801FB49C[];
extern Unk54728 D_801D3844[];
extern Entity D_801E0B78[];
extern u8 D_801FA8A0[];
extern u16 D_801D870C;
extern Unk800AA248Node *D_800AA284;
extern s32 D_80016A30;
extern s32 D_80084F54[];
extern s32 D_800845EC[];
extern s32 D_800850F8[];
extern s32 D_800843D8[];
extern s32 D_800843F4[];
extern s32 D_80084790[];
extern s32 D_800847AC[];
extern s32 D_800847C8[];

Unk800AA248Node *func_8001D110(void);
void *func_8001DCB4(void);

void func_80057E54();
void func_80057F28();
s32 func_80057F98(u16, Entity *);
void func_80058734();
void func_8005883C();
void func_80058984();

/* The animation scripts (seven words each; game_80057C94's .data). */
extern s32 D_8008434C[];
extern s32 D_80084368[];
extern s32 D_80084384[];
extern s32 D_800843A0[];
extern s32 D_800843BC[];
extern s32 D_80084410[];
extern s32 D_8008442C[];
extern s32 D_80084448[];
extern s32 D_80084464[];
extern s32 D_80084480[];
extern s32 D_8008449C[];
extern s32 D_80084598[];
extern s32 D_800845B4[];
extern s32 D_80084608[];
extern s32 D_80084624[];
extern s32 D_80084640[];
extern s32 D_80084678[];
extern s32 D_80084694[];
extern s32 D_800846B0[];
extern s32 D_800846CC[];
extern s32 D_800846E8[];
extern s32 D_80084704[];
extern s32 D_80084720[];
extern s32 D_8008473C[];
extern s32 D_80084758[];
extern s32 D_80084774[];
extern s32 D_80084800[];
extern s32 D_8008488C[];
extern s32 D_800848A8[];
extern s32 D_800848C4[];
extern s32 D_800848E0[];
extern s32 D_800848FC[];
extern s32 D_80084918[];
extern s32 D_80084934[];
extern s32 D_80084950[];
extern s32 D_800849A4[];
extern s32 D_800849C0[];
extern s32 D_800849DC[];
extern s32 D_800849F8[];
extern s32 D_80084A14[];
extern s32 D_80084A4C[];
extern s32 D_80084A84[];
extern s32 D_80084AA0[];
extern s32 D_80084ABC[];
extern s32 D_80084AD8[];
extern s32 D_80084AF4[];
extern s32 D_80084B10[];
extern s32 D_80084B2C[];
extern s32 D_80084B48[];
extern s32 D_80084B64[];
extern s32 D_80084B80[];
extern s32 D_80084B9C[];
extern s32 D_80084BB8[];
extern s32 D_80084BD4[];
extern s32 D_80084C0C[];
extern s32 D_80084C28[];
extern s32 D_80084C44[];
extern s32 D_80084C60[];
extern s32 D_80084C7C[];
extern s32 D_80084C98[];
extern s32 D_80084CB4[];
extern s32 D_80084CEC[];
extern s32 D_80084D08[];
extern s32 D_80084D24[];
extern s32 D_80084D40[];
extern s32 D_80084D5C[];
extern s32 D_80084D78[];
extern s32 D_80084D94[];
extern s32 D_80084DCC[];
extern s32 D_80084DE8[];
extern s32 D_80084E04[];
extern s32 D_80084E3C[];
extern s32 D_80084E90[];
extern s32 D_80084EAC[];
extern s32 D_80084EC8[];
extern s32 D_80084EE4[];
extern s32 D_80084F00[];
extern s32 D_80084F1C[];
extern s32 D_80084F38[];
extern s32 D_80084F70[];
extern s32 D_80084F8C[];
extern s32 D_80084FA8[];
extern s32 D_80084FC4[];
extern s32 D_80084FE0[];
extern s32 D_80084FFC[];
extern s32 D_800850C0[];
extern s32 D_800850DC[];
extern s32 D_80085114[];
extern s32 D_80085130[];
extern s32 D_8008514C[];
extern s32 D_80085168[];

void func_80057C94(Entity *e) {
    u16 move;
    u16 kind;

    move = e->unk_0CC;
    kind = e->unk_168;
    if (move == 0) {
        if (e->unk_13E == 0) {
            kind = 0;
        }
    } else {
        kind = move;
        e->unk_13E = 0x1A4;
    }
    if (kind == 0 && e->unk_008 <= 0xF0000) {
        func_80057B94(e, D_80084A4C);
        return;
    }
    if (D_800AA268.p->unk_22 & 0x10) {
        func_80057C38(kind, e, D_80084368);
    } else {
        func_80057C38(kind, e, D_80084384);
    }
}

void func_80057D4C(Entity *e) {
    s32 kind;

    if (e->unk_0CC != 0) {
        kind = e->unk_0CC;
    } else {
        kind = e->unk_168;
    }
    func_80057C38(kind, e, D_8008434C);
    func_8004C38C();
}

void func_80057D90(Entity *e) {
    e->unk_13E = 0x1A4;
    if (e->unk_168 == 7) {
        func_80057B94(e, D_800843D8);
    } else {
        func_80057B94(e, D_800843F4);
    }
}

void func_80057DD8(Entity *e) {
    s32 anim;
    u16 type;

    e->unk_05A = 3;
    anim = e->unk_1B0;
    D_800AA250 = anim;
    if ((u32)(anim - 1) < 2) {
        func_80058984(e);
        return;
    }
    type = e->unk_05C;
    if (type == 2 || type == 0x4E) {
        func_80057F28(e);
        return;
    }
    func_80057E54(e);
}

#ifdef NON_MATCHING
/* 96.8%: the original keeps the call's result in a2 (the register the script pointer takes afterwards). */
void func_80057E54(Entity *e) {
    s32 *script;
    s32 r;
    u16 kind;
    u16 move;

    move = e->unk_0CC;
    kind = move;
    if (move == 0) {
        move = e->unk_168;
        kind = move;
    }
    r = func_80057F98(kind, e);
    if (!(D_800AA268.p->unk_22 & 0x10)) {
        if (r != 0) {
            script = D_8008449C;
        } else {
            script = D_8008442C;
            if (e->unk_1B0 != 3) {
                script = D_80084464;
            }
        }
    } else if (r != 0) {
        script = D_80084480;
    } else {
        script = D_80084410;
        if (e->unk_1B0 != 3) {
            script = D_80084448;
        }
    }
    func_80057BD4(move, e, script);
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_80057E54);
#endif

void func_80057F28(Entity *e) {
    s32 *script;
    u16 kind;

    e->unk_05A = 0x11;
    if (D_800AA268.p->unk_22 & 0x10) {
        script = D_800843BC;
    } else {
        script = D_800843A0;
    }
    kind = e->unk_0CC;
    if (kind == 0) {
        kind = e->unk_168;
    }
    func_80057BD4(kind, e, script);
}

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_80057F98);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_800580F8);

extern s32 D_800845D0[];

void func_80058214(Entity *e) {
    e->unk_1C8 = 0;
    e->unk_05E = 0;
    func_80057B94(e, D_800845D0);
}

void func_80058240(Entity *e) {
    func_80057B94(e, D_80084598);
}

void func_80058264(Entity *e) {
    func_80057B94(e, D_800845B4);
}

#ifdef NON_MATCHING
/* 87.8%: register and load order around the direction branches */
void func_80058288(Entity *e) {
    Unk54728 *u;
    s32 *table;
    Body *b;
    u16 x;
    u16 dir;
    u16 v;

    u = func_80054728(e->unk_1B2);
    b = D_800AA268.p;
    table = D_800845EC;
    x = b->unk_16;
    if (u != NULL) {
        dir = e->unk_1B0;
        if (dir == 2) {
            v = u->unk_0E;
            if (b->unk_22 & 0x10) {
                x = v + 8;
            } else {
                x = v - 4;
                table = D_800850F8;
            }
        } else if (dir == 1) {
            v = u->unk_04;
            if (b->unk_22 & 0x10) {
                x = v + 4;
                table = D_800850F8;
            } else {
                x = v - 8;
            }
        }
    }
    D_800AA268.p->unk_16 = x;
    func_80057B94(e, table);
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_80058288);
#endif

void func_8005834C(Entity *e) {
    func_80057B94(e, D_80084640);
}

void func_80058370(Entity *e) {
    e->unk_1B2 = 0;
    e->unk_1B4 = 0;
    if ((D_800AA2DC & 0x7000) && e->unk_184 != 0) {
        func_800595E4(e);
    } else {
        func_80057B94(e, D_8008465C);
    }
}

void func_800583CC(Entity *e) {
    s32 *script;
    u16 anim;

    anim = e->unk_1B0;
    script = D_80084678;
    if (anim != 0 && anim != 3) {
        script = D_80084694;
    }
    func_80057B94(e, script);
}

void func_80058410(Entity *e) {
    s32 *script;
    u16 anim;

    anim = e->unk_1B0;
    script = D_800846B0;
    if (anim != 0 && anim != 3) {
        script = D_800846CC;
    }
    func_80057B94(e, script);
}

void func_80058454(Entity *e) {
    s32 *script;
    u16 anim;

    anim = e->unk_1B0;
    script = D_800846E8;
    if (anim != 0 && anim != 3) {
        script = D_80084704;
    }
    func_80057B94(e, script);
}

void func_80058498(Entity *e) {
    s32 *script;
    u16 anim;

    anim = e->unk_1B0;
    script = D_80084720;
    if (anim != 0 && anim != 3) {
        script = D_8008473C;
    }
    func_80057B94(e, script);
}

void func_800584DC(Entity *e) {
    s32 v;
    u16 anim;

    anim = e->unk_1B0;
    v = 0x20000;
    if (anim == 1) {
        v = -0x20000;
        goto set;
    }
    if (anim == 2) {
set:
        e->unk_100 = v;
        D_800AA268.p->unk_10 = -0x30000;
        e->unk_104 = 0x4000;
        e->unk_1B0 = 0;
        e->unk_1B2 = 0;
        e->unk_1B4 = 0;
        e->unk_100 = 0;
    }
    func_80057B94(e, D_80084758);
}

void func_80058550(Entity *e) {
    s32 v;

    v = 0x20000;
    if (e->unk_1B0 != 0) {
        if (e->unk_168 != 7) {
            v = -0x20000;
        }
        e->unk_100 = v;
        D_800AA268.p->unk_10 = -0x30000;
        e->unk_104 = 0x4000;
        e->unk_1B0 = 0;
        e->unk_1B2 = 0;
        e->unk_1B4 = 0;
        e->unk_100 = 0;
    }
    func_80057B94(e, D_80084774);
}

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_800585C0);

extern s32 D_800847E4[];

void func_80058680(Entity *e, u16 arg1) {
    e->unk_05A = 0x16;
    func_80057B94(e, D_800847E4);
}

void func_800586AC(Entity *e) {
    u16 kind;
    u16 n;
    u16 dir;

    kind = e->unk_0CC;
    n = e->unk_168;
    if (kind != 0) {
        n = kind;
    }
    dir = e->unk_1B0;
    if (dir == 1) {
        D_800AA268.p->unk_22 &= 0xFFEF;
    } else if (dir == 2) {
        D_800AA268.p->unk_22 |= 0x10;
    }
    func_80057C38(n, e, D_8008481C);
}

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_80058734);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005883C);

void func_80058944(Entity *e) {
    if (e->unk_1B0 == 2) {
        func_8005883C();
    } else {
        func_80058734();
    }
}

void func_80058984(Entity *e) {
    s32 *script;
    u16 move;
    u16 kind;

    move = e->unk_0CC;
    kind = e->unk_168;
    if (move != 0) {
        kind = move;
    }
    if (e->unk_1B0 == 1) {
        script = D_8008488C;
    } else {
        script = D_800848A8;
    }
    func_80057BD4(kind, e, script);
}

void func_800589DC(Entity *e, s32 *table) {
    u16 kind;
    u16 n;

    kind = e->unk_0CC;
    n = e->unk_168;
    if (kind != 0) {
        n = kind;
    }
    func_80057C38(n, e, table);
}

void func_80058A18(Entity *e) {
    func_80057B94(e, D_800848C4);
}

void func_80058A3C(Entity *e) {
    func_80057B94(e, D_80084934);
}

void func_80058A60(Entity *e) {
    func_80057B94(e, D_80084950);
}

void func_80058A84(Entity *e) {
    func_80057B94(e, D_800848E0);
}

void func_80058AA8(Entity *e) {
    func_80057B94(e, D_800848FC);
}

void func_80058ACC(Entity *e) {
    func_80057B94(e, D_80084918);
}

void func_80058AF0(Entity *e) {
    u16 dir;

    dir = e->unk_1B0;
    if (dir == 0 || dir == 3) {
        func_80057B94(e, D_8008496C);
    } else {
        func_80057B94(e, D_80084988);
    }
}

void func_80058B3C(Entity *e) {
    func_80057B94(e, D_800849A4);
}

void func_80058B60(Entity *e) {
    func_80057B94(e, D_800849C0);
}

void func_80058B84(Entity *e) {
    func_80057B94(e, D_800849DC);
}

void func_80058BA8(Entity *e) {
    func_80057B94(e, D_800849F8);
}

void func_80058BCC(Entity *e) {
    func_80057B94(e, D_80084A14);
}

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_80058BF0);

void func_80058C6C(Entity *e) {
    func_80057B94(e, D_80084A84);
}

void func_80058C90(Entity *e) {
    func_80057B94(e, D_80084B10);
}

void func_80058CB4(Entity *e) {
    func_80057B94(e, D_80084AA0);
}

void func_80058CD8(Entity *e) {
    func_80057B94(e, D_80084ABC);
}

void func_80058CFC(Entity *e) {
    func_80057B94(e, D_80084AD8);
}

void func_80058D20(Entity *e) {
    func_80057B94(e, D_80084AF4);
}

void func_80058D44(Entity *e) {
    func_80057B94(e, D_80084B2C);
}

void func_80058D68(Entity *e) {
    func_80057B94(e, D_80084B48);
}

void func_80058D8C(Entity *e) {
    func_80057B94(e, D_80084B64);
}

void func_80058DB0(Entity *e) {
    func_80057C38(e->unk_0CC, e, D_80084B80);
}

void func_80058DDC(Entity *e) {
    func_80057B94(e, D_80084B9C);
}

void func_80058E00(Entity *e) {
    func_80057B94(e, D_80084BB8);
}

void func_80058E24(Entity *e) {
    func_80057B94(e, D_80084C60);
}

void func_80058E48(Entity *e) {
    func_80057B94(e, D_80084C7C);
}

void func_80058E6C(Entity *e) {
    func_80057B94(e, D_80084624);
}

void func_80058E90(Entity *e) {
    func_80057B94(e, D_80084BD4);
}

extern s32 D_80084BF0[];

void func_80058EB4(Entity *e) {
    e->unk_1C8 = 0;
    e->unk_05E = 0;
    e->unk_1CC = 0;
    e->unk_044 = 0;
    func_80057B94(e, D_80084BF0);
}

void func_80058EE8(Entity *e) {
    func_80057B94(e, D_80084C28);
}

void func_80058F0C(Entity *e) {
    func_80057B94(e, D_80084608);
}

void func_80058F30(Entity *e) {
    func_80057B94(e, D_80084C44);
}

void func_80058F54(Entity *e) {
    func_80057B94(e, D_80084C0C);
}

void func_80058F78(Entity *e) {
    func_80057B94(e, D_80084800);
}

void func_80058F9C(Entity *e) {
    func_80057B94(e, D_80084C98);
}

void func_80058FC0(void) {
}

void func_80058FC8(Entity *e) {
    func_80057B94(e, D_80084CB4);
}

void func_80058FEC(Entity *e) {
    func_80057B94(e, D_80084CEC);
}

void func_80059010(Entity *e) {
    func_80057B94(e, D_80084D08);
}

void func_80059034(Entity *e) {
    s32 *script;

    if ((u16)(e->unk_1B0 - 1) < 2) {
        script = D_80084D40;
    } else {
        script = D_80084D24;
    }
    func_80057B94(e, script);
}

void func_8005907C(Entity *e) {
    func_80057B94(e, D_80084D5C);
}

void func_800590A0(Entity *e) {
    func_80057B94(e, D_80084D78);
}

extern s32 D_80084544[];

void func_800590C4(Entity *e) {
    e->unk_1BE = 0;
    e->unk_05A = 2;
    func_80057B94(e, D_80084544);
}

void func_800590F4(Entity *e) {
    func_80057B94(e, D_80084D94);
}

void func_80059118(Entity *e) {
    s32 vx;

    e->unk_100 = 0;
    e->unk_104 = 0;
    D_800AA248.unk_20->unk_10 = 0;
    vx = 0x1C000;
    if (D_800AA248.unk_20->unk_22 & 0x10) {
        vx = 0xFFFE4000;
    }
    D_800AA248.unk_20->unk_0C = vx;
    func_80057B94(e, D_80084DB0);
}

void func_80059180(Entity *e) {
    Body *saved;
    void *node;

    if (e->unk_16C == NULL) {
        saved = D_800AA248.unk_20;
        func_8001D110()->unk_20 = 0x5000;
        node = func_8001DCB4();
        D_800AA248.unk_20 = node;
        e->unk_16C = node;
        D_800AA248.unk_20 = saved;
    }
    func_80057B94(e, D_80084DCC);
}

#ifdef NON_MATCHING
/* 91.5%: the branch layout after the direction range check */
void func_800591F8(Entity *e, s32 *table) {
    u16 dir;

    dir = e->unk_1B0;
    if (dir != 3) {
        if (((dir - 1) & 0xFFFF) < 2) {
            func_80059270(e);
            return;
        }
        if (D_800AA268.p->unk_18.h.i != 0xE1) {
            func_80057B94(e, D_80084E20);
            return;
        }
    }
    func_80059294(e);
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_800591F8);
#endif

void func_80059270(Entity *e) {
    func_80057B94(e, D_80084E3C);
}

void func_80059294(Entity *e) {
    func_80057B94(e, D_80084DE8);
}

void func_800592B8(Entity *e) {
    s32 *table;
    u16 dir;

    dir = e->unk_1B0;
    if (dir == 3) {
        table = D_80084E58;
    } else if (dir == 0) {
        table = D_80084E58;
    } else {
        table = D_80084E74;
    }
    func_80057B94(e, table);
}

void func_80059300(Entity *e) {
    func_80057B94(e, D_80084E90);
}

void func_80059324(Entity *e) {
    e->unk_126 = 0;
    if (e->unk_18E == 0) {
        func_80057B94(e, D_80084EAC);
    } else {
        e->unk_05A = 0;
    }
}

void func_80059364(Entity *e) {
    func_80057B94(e, D_80084E04);
}

void func_80059388(Entity *e) {
    func_80057B94(e, D_80084EC8);
}

void func_800593AC(Entity *e) {
    func_80057B94(e, D_80084EE4);
}

void func_800593D0(Entity *e) {
    func_80057B94(e, D_80084F00);
}

void func_800593F4(Entity *e) {
    func_80057B94(e, D_80084F1C);
}

void func_80059418(Entity *e) {
    func_80057B94(e, D_80084F38);
}

void func_8005943C(Entity *e) {
    EntityLink *link;
    Body *b;

    if (e == NULL || (link = e->unk_1D4) == NULL || (b = link->unk_00) == NULL || (link->unk_06 != 0 && !(b->unk_6C & 0x80))) {
        func_80057C38(e->unk_0CC, e, D_80084F54);
        return;
    }
    e->unk_1D4 = NULL;
    func_8004A90C(e, e);
}

void func_800594C4(Entity *e) {
    func_80057B94(e, D_80084F70);
}

void func_800594E8(Entity *e) {
    s32 *script;
    u16 anim;

    anim = e->unk_1B0;
    if (anim == 0 || anim == 3) {
        script = D_80084FC4;
    } else {
        script = D_80084FE0;
    }
    func_80057B94(e, script);
}

void func_80059530(Entity *e) {
    s32 *script;
    u16 anim;

    anim = e->unk_1B0;
    if (anim == 0 || anim == 3) {
        script = D_80084F8C;
    } else {
        script = D_80084FA8;
    }
    func_80057B94(e, script);
}

void func_80059578(Entity *e) {
    func_80057B94(e, D_80084FFC);
}

void func_8005959C(Entity *e) {
    func_80057B94(e, D_800850C0);
}

void func_800595C0(Entity *e) {
    func_80057B94(e, D_800850DC);
}

extern s32 D_80085018[];

void func_800595E4(Entity *e) {
    e->unk_184 = 1;
    func_80057B94(e, D_80085018);
}

extern s32 D_80085034[];

void func_80059610(Entity *e) {
    e->unk_184 = 1;
    func_80057B94(e, D_80085034);
}

extern s32 D_80085050[];

void func_8005963C(Entity *e) {
    e->unk_184 = 1;
    func_80057B94(e, D_80085050);
}

extern s32 D_8008506C[];

void func_80059668(Entity *e) {
    e->unk_184 = 1;
    func_80057B94(e, D_8008506C);
}

extern s32 D_80085088[];

void func_80059694(Entity *e) {
    e->unk_184 = 1;
    func_80057B94(e, D_80085088);
}

extern s32 D_800850A4[];

void func_800596C0(Entity *e) {
    e->unk_184 = 1;
    func_80057B94(e, D_800850A4);
}

void func_800596EC(Entity *e) {
    func_80057B94(e, D_80085114);
}

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_80059710);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_800598F4);

#ifdef NON_MATCHING
/* 97.2%: the state block's base lands in a2 instead of a1 */
void func_80059B00(void) {
    Entity *e;
    s32 v;

    e = D_800AA248.unk_20->unk_90;
    if (e->unk_168 == 7) {
        v = 0xFFFA0000;
    } else {
        v = 0x50000;
    }
    e->unk_100 = v | 0x8000;
    D_800AA248.unk_20->unk_0C = v | 0x8000;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_80059B00);
#endif

void func_80059B40(void) {
    Entity *e;

    e = D_800AA248.unk_20->unk_90;
    if (e->unk_168 == 7) {
        e->unk_168 = 3;
        D_800AA248.unk_20->unk_22 &= 0xFFEF;
        return;
    }
    e->unk_168 = 7;
    D_800AA248.unk_20->unk_22 |= 0x10;
}

void func_80059BA8(void) {
    func_80029118(8, 0xC);
    func_8001F724(0x59);
}

void func_80059BD4(void) {
    func_80029118(2, 4);
    func_8001F724(0x21);
}

void func_80059C00(void) {
    func_80029118(2, 4);
    func_8001F724(0x20);
}

#ifdef NON_MATCHING
/* 99.1%: the state compares are made on a u16-truncated copy (andi) in the original; a local for it makes GCC hoist a constant out of the loop */
void func_80059C2C(void) {
    Body *saved;
    Unk1D85C8 *ai;
    u16 n;

    saved = D_800AA268.p;
    func_8001F7CC(0xFF, 0x21);
    func_80029118(9, 0x10);
    if (D_801D870C != 0) {
        ai = D_801D85C8;
        n = 5;
        do {
            if (ai->unk_2E == 0 && ((u32) (ai->unk_08 - 2) < 2U || ai->unk_08 == 0xA || ai->unk_08 == 0xB || ai->unk_08 == 4 || (u32) (ai->unk_08 - 0x15) < 5U)) {
                ai->unk_0C = 1;
                ai->unk_08 = 0x33;
                ai->unk_2E = 0;
                func_8003D71C(ai);
            }
            ai++;
        } while (--n != 0);
    }
    D_800AA268.p = saved;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_80059C2C);
#endif

void func_80059D2C(void) {
    Body *saved;
    Entity *e;
    Unk54728 *u;
    Entity *other;
    s16 i;
    s32 n;
    s32 state;

    saved = D_800AA268.p;
    e = saved->unk_90;
    func_80029118(0xB, 0x12);
    e->unk_010.w = 0;
    if (e->unk_1B0 == 3 && D_800AA2DC == 0) {
        u = &D_801D3844[e->unk_1B2];
        i = 0;
        if ((u32) (u->unk_58 - 2) >= 2U) {
            if (u->unk_14 < 4) {
                u->unk_10 = u->unk_12;
            }
            if (u->unk_58 == 0) {
                func_8002E278(e, u);
            }
        } else {
            do {
                func_8002CFAC(e, u);
                i++;
            } while (i < 0xA);
        }
    } else {
        if (e->unk_188 < 8) {
            func_80059710(e, 8, 0x78);
        }
        for (n = 1; n < 4; n++) {
            if (n != D_801FA8A0[e->unk_000 - 1]) {
                other = &D_801E0B78[func_80025DF8(n)];
                state = other->unk_05A;
                if ((u32) (state - 0x34) >= 2U && (u16) state != 0x2A && (u16) state != 0x37 && (u16) state != 0x3B && (u16) state != 0x63 && (u16) state != 0x47) {
                    other->unk_05A = 0xA;
                }
            }
        }
    }
    D_800AA268.p = saved;
}

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_80059F24);

void func_8005A0F0(void) {
    Body *saved;
    Entity *e;

    saved = D_800AA248.unk_20;
    e = saved->unk_90;
    if (e->unk_068->unk_18.h.i >= 0xE1) {
        func_800531C0(e);
    }
    D_800AA248.unk_20 = saved;
}

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005A154);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005A2F4);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005A7C4);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005A964);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005AE28);

void func_8005B85C(Entity *e) {
    func_80057B94(e, D_80085130);
}

void func_8005B880(Entity *e) {
    func_80057B94(e, D_80085168);
}

void func_8005B8A4(Entity *e) {
    func_80057B94(e, D_8008514C);
}

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005B8C8);

void func_8005BB04(Entity *e, s16 want, s16 max, Unk54728 *u) {
    s16 i;

    if (D_800AA2DC != 0) {
        e->unk_188 += want;
        return;
    }
    i = 0;
    u->unk_14 = 1;
    do {
        if (u->unk_58 != 1) {
            e->unk_188++;
            if (u->unk_14 < 4) {
                func_8002D370(e, &u->unk_98[func_8001EB10(u->unk_00 - 2, 0)], u);
            }
        }
        i++;
    } while ((s32) e->unk_188 < want && i < max);
}

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005BC20);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005BF54);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005C1F8);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005C3C8);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005C578);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005C71C);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005C958);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005CAA4);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005CC54);

void func_8005CEC4(Body *b, Entity *skip) {
    Entity *e;
    Body *eb;
    s16 i;

    for (i = 0; i < (s32) D_801D8740; i++) {
        e = &D_801E0B78[func_80025DF8(D_801FB49C[i])];
        if (e != NULL && skip != e) {
            eb = e->unk_068;
            if (eb != NULL && e->unk_000 != 0 && e->unk_05A < 7) {
                if (func_8005BC20(b->unk_16, b->unk_18.h.i - ((s16) b->unk_32 >> 1), (s16) b->unk_30 >> 1, (s16) b->unk_32 >> 1, eb, 4) != 0) {
                    func_8001F724(0x14);
                    if (D_8007A68A != 0) {
                        func_80053C50(0x28000, e);
                    }
                    e->unk_05A = 0xA;
                }
            }
        }
    }
}

void func_8005D034(s32 x, s32 y, s32 flags) {
    Unk800AA248Node *node;

    func_8001F724(5);
    node = func_8001D110();
    D_800AA248.unk_3C = node;
    node->unk_20 = 0x1006;
    node->unk_28 = &D_80016A30;
    node->unk_14.w = (y << 0x10) + 0xFFF60000;
    node->unk_00 = D_80016A30;
    if (flags & 0x10) {
        node->unk_10.w = (x << 0x10) + 0xFFC00000;
    } else {
        node->unk_10.w = (x << 0x10) + 0x400000;
    }
    func_8001DCB4();
}

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005D0D8);

INCLUDE_RODATA("asm/main/nonmatchings/game_80057C94", D_800115B0);

INCLUDE_RODATA("asm/main/nonmatchings/game_80057C94", D_800115C0);

INCLUDE_RODATA("asm/main/nonmatchings/game_80057C94", D_800115C8);

INCLUDE_RODATA("asm/main/nonmatchings/game_80057C94", D_800115D0);
