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

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_80057D90);

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

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_80058214);

void func_80058240(Entity *e) {
    func_80057B94(e, D_80084598);
}

void func_80058264(Entity *e) {
    func_80057B94(e, D_800845B4);
}

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_80058288);

void func_8005834C(Entity *e) {
    func_80057B94(e, D_80084640);
}

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_80058370);

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

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_80058680);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_800586AC);

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

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_800589DC);

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

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_80058AF0);

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

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_80058EB4);

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

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_800590C4);

void func_800590F4(Entity *e) {
    func_80057B94(e, D_80084D94);
}

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_80059118);

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

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_800591F8);

void func_80059270(Entity *e) {
    func_80057B94(e, D_80084E3C);
}

void func_80059294(Entity *e) {
    func_80057B94(e, D_80084DE8);
}

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_800592B8);

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

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005943C);

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

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_800595E4);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_80059610);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005963C);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_80059668);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_80059694);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_800596C0);

void func_800596EC(Entity *e) {
    func_80057B94(e, D_80085114);
}

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_80059710);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_800598F4);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_80059B00);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_80059B40);

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

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_80059C2C);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_80059D2C);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_80059F24);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005A0F0);

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

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005BB04);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005BC20);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005BF54);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005C1F8);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005C3C8);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005C578);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005C71C);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005C958);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005CAA4);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005CC54);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005CEC4);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005D034);

INCLUDE_ASM("asm/main/nonmatchings/game_80057C94", func_8005D0D8);

INCLUDE_RODATA("asm/main/nonmatchings/game_80057C94", D_800115B0);

INCLUDE_RODATA("asm/main/nonmatchings/game_80057C94", D_800115C0);

INCLUDE_RODATA("asm/main/nonmatchings/game_80057C94", D_800115C8);

INCLUDE_RODATA("asm/main/nonmatchings/game_80057C94", D_800115D0);
