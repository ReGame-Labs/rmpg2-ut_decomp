/* A file of the game's code, named after its first function until its contents are understood: the records of
 * D_801FAC9C (Npc, include/game_80034590.h) and their per-kind updaters.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "game.h"
#include "game_80034590.h"

/* Other units. */
Effect *func_8001D110(void);
Mover *func_8001DCB4(void);         /* spawns D_800AA248.unk_3C */
void func_8001E4B0(Mover *mover);
void func_80029118(s32 a, s32 b);
void func_8004BFE0(void);
void func_80053D68(s32 n, Player *player);
s32 func_8001EA78(void);
void func_8001F7CC(s32 a, s32 b);
void func_8004A9B0(s32 a, s32 b, s32 c, s32 d, s32 e);
void func_8001BB68(Mover *mover);
Mover *func_8001EB9C(s32 a, s32 b, s32 c, s32 d, s32 color);
void func_8001BB88(Mover *mover);
s16 func_8001EB10(s32 arg0, s32 arg1);
void func_8001F724(s32 sound);
void func_80020D20(void *npc);
void func_800242A8(void);
s32 func_80025DF8(s32 n);
void func_8003EB5C(u8 *anim, Mover *mover);
u16 func_8003BE34(Npc *npc);
void func_8004CFC0(void);
void func_80054374(s32 n, Player *player);
void func_80053C50(s32 n, Player *player);
void func_8004A90C(Player *player);
void func_800215C0(s16 x, s16 y);
void func_8003C080();                /* called with the position and without: no prototype in the original */
void func_800634D4(Player *player, s32 n);
void *memset(void *s, s32 c, u32 n);
s32 abs(s32 n);

/* This unit. */
void func_800345F8(Npc *npc);
void func_80034B68(s32 speed);
void func_800346FC(Npc *npc);
s32 func_80036028(void);
u16 func_80039958(NpcS *npc);
void func_8003AAF8(NpcS *npc);
void func_80039A58(NpcS *npc);
void func_8003831C(void);
void func_800347E4(Npc *npc, EffectDef *def);
void func_80036504(Mover *a, Mover *b, Mover *c);
void func_80035B6C(Npc *npc);
void func_80035EBC(Npc *npc);
void func_8003585C(Npc *npc);
void func_800358C8(Npc *npc);
void func_80035928(Npc *npc);
void func_8003599C(Npc *npc);
void func_80035E80(Npc *npc);
void func_80035F8C(Npc *npc);
void func_80035DC0(Npc *npc);
void func_80035BE8(Npc *npc);
void func_80035A3C(Npc *npc);
void func_80035B30(Npc *npc);
void func_80034418(void);
void func_80034670();                /* called with the record and without: no prototype in the original */
void func_8003AA7C(NpcS *npc);
u16 func_80038DA8(NpcS *npc);
void func_800380F0(NpcS *npc);
void func_80038058(NpcS *npc);
void func_80038198(NpcS *npc);
void func_800381E4(NpcS *npc);
void func_80038240(NpcS *npc);
void func_800382A8(NpcS *npc);
void func_80038A2C(NpcS *npc);
void func_80038920(NpcS *npc);
Player *func_80039B60(s32 x);
s32 func_80039B04(Player *player, s32 x);
void func_80034988(Npc *npc);
void func_80034C54(Mover *mover);
void func_80034D28(Npc *npc);
void func_80034DAC(Npc *npc);
void func_80034E48(Npc *npc);
void func_80035040(void);
void func_800351CC(Npc *npc);
void func_800354A4(void);
void func_80035464(Npc *npc);
void func_80035550(Npc *npc);
void func_80035590(Npc *npc);
void func_80035620(Npc *npc);
void func_80035A88(Npc *npc);
void func_80035DFC(Npc *npc);
void func_80035FF0(void);
void func_80036300(Npc *npc);
void func_800369F8(Npc *npc);
u16 func_80037574(s16 x, s16 y, s32 arg2);
u16 func_8003761C(s16 x, s16 y, Player *player, NpcS *npc);
void func_800376E0(NpcS *npc);
void func_80037960(NpcS *npc, s32 arg1);
void func_80037BB4(NpcS *npc);
void func_80037C1C(NpcS *npc);
void func_80037CA0(NpcS *npc);
void func_80037CF4(NpcS *npc);
void func_80037D78(NpcS *npc);
void func_80037E1C(NpcS *npc);
void func_80037E78(NpcS *npc);
void func_80037EE0(NpcS *npc);
void func_800380C0(Mover *mover);
void func_80038528(NpcS *npc);
void func_800385F4(NpcS *npc);
void func_80038754(NpcS *npc);
void func_80038800(NpcS *npc);
void func_80038838(NpcS *npc);
u16 func_80038C1C(void);
u16 func_80038F3C(u16 *out, NpcS *npc);
u16 func_800391F8(u16 *out, NpcS *npc);
u16 func_80039220(u16 *out, NpcS *npc);
void func_800398D4(void);
s32 func_80039C40(s32 x, s32 left, s32 right);
s32 func_80039C98(s32 x, s32 left, s32 right);
void func_8003A328(NpcS *npc, s32 arg1);
void func_8003AAF8(NpcS *npc);
void func_8003ABE8(NpcS *npc);
void func_8003AC74(NpcS *npc);
void func_8003AEA0(NpcS *npc);
void func_8003AF40(NpcS *npc);
void func_8003B1D0(NpcS *npc);

extern u8 *D_8007D4C0[];           /* animations per kind */
extern EffectDef *D_8007D50C[];
extern EffectDef D_8008A7A4;
extern EffectDef D_8008A538;
extern u8 D_8008A3E0[];
extern u8 D_8008A414[];
extern u8 D_8008A408[];
extern u8 D_8008A43C[];
extern u8 D_8008A398[];
extern u8 D_8008AA28[];
extern u8 D_80095AC8[];
extern u8 D_80095AF0[];
extern u8 D_80095B18[];
extern u8 D_800956D0[];
extern u8 *D_8007DA58[];
extern u8 D_8008A488[];
extern u8 D_8008A5A8[];
extern u8 D_8008A62C[];
extern u8 D_8008A8DC[];
extern u8 D_8008A908[];
extern u8 D_8008A938[];
extern u8 D_8008A998[];
extern u8 D_8008A9A4[];
extern u16 D_801D376C;             /* the screen's right edge, in pixels */
extern u16 D_801D87B0;             /* the screen's left edge, in pixels */
extern void (*D_8007D558[])(void);  /* per kind */
extern void (*D_8007D5A4[])(void);  /* per kind */
extern u8 *D_8007D45C[];
extern u8 *D_8007DA68[];
extern u8 *D_8007DA78[][4];
extern u8 D_8008A47C[];
extern u8 D_8008AA10[];
extern u8 D_8008A374[];
extern u8 D_80095EF0[];
extern u8 D_8009585C[];
extern u8 D_800958E0[];
extern Effect *D_800AA284;     /* D_800AA248.unk_3C by its own name */
extern Mover *D_800AA268;      /* D_800AA248.unk_20 by its own name (func_80038920 reads it so) */
extern u8 D_80095E24[];
extern u8 D_80095E68[];
extern u8 D_80095EAC[];
extern u8 D_80095874[];
extern s32 D_801D8864[];           /* [0]: the world's width minus one, a mask (16.16); the code reloads it across struct stores */
extern s32 D_801F9AC8[];           /* [0]: the screen's left edge (16.16); reloaded across struct stores like D_801D8864 */
extern u16 D_801D8730;              /* how many of D_801FAC9C are live */
extern s16 D_801E2A50;
extern Npc D_801FAC9C[6];
extern Mover *D_801FB44C[3];
extern u16 D_801FA98C;
extern u16 D_801FA990;
extern Player D_801E0B78[3];

void func_80034590(Npc *npc) {
    npc->unk_8 = 2;
    npc->unk_1E = func_8001EB10(0x190, 0);
    npc->unk_22 = 0;
    func_8003EB5C(D_8007D4C0[npc->unk_6 - 1], D_800AA248.unk_20);
}

void func_800345F8(Npc *npc) {
    func_8001F724(5);
    D_800AA248.unk_20->unk_C = 0;
    D_800AA248.unk_20->unk_10 = 0;
    npc->unk_8 = 4;
    npc->unk_1C = 5;
    func_800347E4(npc, D_8007D50C[npc->unk_6 - 1]);
}

void func_80034670(void) {
    Mover *saved = D_800AA248.unk_20;
    Effect *effect;
    u16 y;

    effect = func_8001D110();
    D_800AA248.unk_3C = effect;
    effect->unk_12 = ((u16 *)&D_800AA248.unk_20->unk_14)[1];
    y = ((u16 *)&D_800AA248.unk_20->unk_18)[1];
    effect->unk_28 = &D_8008A538;
    effect->unk_16 = y;
    effect->unk_20 = *(u16 *)&D_800AA248.unk_20->unk_80 + 1;
    effect->unk_0 = D_8008A538.unk_0;
    func_8001DCB4();
    D_800AA248.unk_20 = saved;
}

void func_800346FC(Npc *npc) {
    Mover *saved = D_800AA248.unk_20;
    EffectDef *table;
    Mover *mover;
    Effect *effect;

    func_8001F724(5);
    func_80029118(8, 8);
    mover = npc->unk_40;
    table = &D_8008A7A4;
    D_800AA248.unk_3C = func_8001D110();
    effect = D_800AA248.unk_3C;
    if (mover->unk_22 & 0x10) {
        effect->unk_12 = ((s16 *)&mover->unk_14)[1] + 0x28;
    } else {
        effect->unk_12 = ((s16 *)&mover->unk_14)[1] - 0x28;
    }
    effect->unk_16 = ((s16 *)&mover->unk_18)[1] - 0x19;
    effect->unk_28 = table;
    effect->unk_20 = *(u16 *)&mover->unk_80 + 1;
    effect->unk_0 = table->unk_0;
    func_8001DCB4();
    func_8001E4B0(npc->unk_40);
    npc->unk_40 = NULL;
    D_800AA248.unk_20 = saved;
}

void func_800347E4(Npc *npc, EffectDef *def) {
    Mover *saved = D_800AA248.unk_20;
    Effect *effect;

    D_800AA248.unk_3C = func_8001D110();
    effect = D_800AA248.unk_3C;
    effect->unk_12 = ((u16 *)&D_800AA248.unk_20->unk_14)[1];
    effect->unk_16 = ((u16 *)&D_800AA248.unk_20->unk_18)[1];
    effect->unk_28 = def;
    effect->unk_20 = *(u16 *)&D_800AA248.unk_20->unk_80 + 1;
    effect->unk_0 = def->unk_0;
    func_8001DCB4();
    if (npc->unk_40 != NULL) {
        func_800346FC(npc);
    }
    D_800AA248.unk_20 = saved;
}

void func_80034898(Npc *npc) {
    u16 n = npc->unk_1C;
    Mover *mover;

    if (n != 0) {
        npc->unk_1C = n - 1;
        return;
    }
    mover = npc->unk_40;
    if (mover != NULL) {
        func_8001E4B0(mover);
        npc->unk_40 = NULL;
    }
    D_800AA248.unk_20->unk_C = 0;
    D_800AA248.unk_20->unk_10 = 0;
    npc->unk_1C = 0x3B6;
    D_800AA248.unk_20->unk_18 = 0x02000000;
    func_8003C080();
}

void func_80034924(Npc *npc) {
    func_8001F724(0x60);
    if (!((D_800AA248.unk_20->unk_22 ^ npc->unk_44) & 0x10)) {
        func_80034988(npc);
        return;
    }
    func_800345F8(npc);
}

void func_80034988(Npc *npc) {
    void (*handler)(void) = D_8007D558[npc->unk_6 - 1];

    if (handler == NULL) {
        func_800345F8(npc);
        return;
    }
    handler();
}

void func_800349E0(Npc *npc) {
    void (*handler)(void) = D_8007D5A4[npc->unk_6 - 1];

    if (handler == NULL) {
        func_800345F8(npc);
        return;
    }
    handler();
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80034A38);

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80034AB4);

void func_80034B68(s32 speed) {
    if (D_800AA248.unk_20->unk_22 & 0x10) {
        speed = -speed;
    }
    D_800AA248.unk_20->unk_C = speed;
}

void func_80034B94(Npc *npc) {
    D_800AA248.unk_20 = npc->unk_0;
    switch (npc->unk_8) {
    case 1:
        func_80034E48(npc);
        return;
    case 2:
        func_80035040();
        return;
    case 3:
        func_80034D28(npc);
        return;
    case 4:
        func_80034DAC(npc);
        return;
    }
}

void func_80034C34(void) {
    ((u16 *)&D_800AA248.unk_20->unk_18)[1] -= 0x14;
}

void func_80034C54(Mover *mover) {
    mover->unk_48 = (Anim *)D_8007D45C[mover->unk_68];
}

void func_80034C74(void) {
    func_8001F724(0x62);
    if (D_801FB44C[0] != NULL) {
        func_80034C54(D_801FB44C[0]);
        D_801FB44C[0] = NULL;
    }
}

void func_80034CB8(void) {
    s32 slot;

    func_8001F724(0x62);
    slot = D_800AA248.unk_20->unk_6A + 1;
    if (slot < 3) {
        Mover *mover = D_801FB44C[slot];

        if (mover != NULL) {
            func_80034C54(mover);
            D_801FB44C[slot] = NULL;
        }
    }
}

void func_80034D28(Npc *npc) {
    func_8001F724(0x60);
    D_800AA248.unk_20->unk_C = 0;
    D_800AA248.unk_20->unk_10 = 0;
    npc->unk_8 = 4;
    npc->unk_C = 0;
    if (npc->unk_6 == 0x17) {
        func_8003EB5C(D_8008A5A8, D_800AA248.unk_20);
    } else {
        func_8003EB5C(D_8008A62C, D_800AA248.unk_20);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80034DAC);

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80034E48);

void func_80035040(void) {
    s32 i;

    D_800AA248.unk_20->unk_14 = (D_800AA248.unk_20->unk_14 + D_800AA248.unk_20->unk_C) & D_801D8864[0];
    for (i = 0; i < 3; i++) {
        Mover *mover = D_801FB44C[i];

        if (mover != NULL) {
            mover->unk_14 = (mover->unk_14 + D_800AA248.unk_20->unk_C) & D_801D8864[0];
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_800350C0);

void func_8003518C(Npc *npc) {
    u16 n = npc->unk_1C;

    if (n == 0) {
        func_800351CC(npc);
        return;
    }
    npc->unk_1C = n - 1;
    func_800242A8();
}

void func_800351CC(Npc *npc) {
    npc->unk_6 = 0x1B;
    npc->unk_3E = 0;
    D_800AA248.unk_20->unk_14 = D_801F9AC8[0] - 0x19A0000;
    D_800AA248.unk_20->unk_18 = 0x320000;
    if (!(D_800AA248.unk_20->unk_22 & 0x10)) {
        D_800AA248.unk_20->unk_C = 0x50000;
    } else {
        D_800AA248.unk_20->unk_C = -0x50000;
    }
    npc->unk_8 = 2;
    func_8003EB5C(D_8008A488, D_800AA248.unk_20);
}

void func_80035260(Npc *npc) {
    u16 n = npc->unk_1C;

    if (n == 0) {
        func_800351CC(npc);
        return;
    }
    npc->unk_1C = n - 1;
    func_800242A8();
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_800352A0);

void func_80035330(Npc *npc) {
    if (npc->unk_C != 0) {
        npc->unk_1C = 0x384;
        npc->unk_8 = 0x64;
        func_800242A8();
        func_8003EB5C(D_8008A47C, D_800AA248.unk_20);
    }
}

void func_8003537C(Npc *npc) {
    D_800AA248.unk_20 = npc->unk_0;
    if (npc->unk_6 == 0x15) {
        func_80034418();
    }
    switch (npc->unk_8) {
    case 0x64:
        func_80035550(npc);
        return;
    case 3:
        func_80035590(npc);
        return;
    case 4:
        func_80035620(npc);
        return;
    case 1:
        func_80035464(npc);
        return;
    default:
        if (func_8003BE34(npc) == 1) {
            npc->unk_8 = 0x64;
            npc->unk_1C = 0x2EE;
            func_800242A8();
        }
        return;
    }
}

void func_80035464(Npc *npc) {
    u16 n = npc->unk_1C;

    if (n == 0) {
        func_800354A4();
        return;
    }
    npc->unk_1C = n - 1;
    func_800242A8();
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_800354A4);

void func_80035550(Npc *npc) {
    u16 n = npc->unk_1C;

    if (n == 0) {
        func_800354A4();
        return;
    }
    npc->unk_1C = n - 1;
    func_800242A8();
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80035590);

void func_80035620(Npc *npc) {
    if (npc->unk_C != 0) {
        npc->unk_1C = 0x384;
        npc->unk_8 = 0x64;
        func_800242A8();
        func_8003EB5C(D_8008AA10, D_800AA248.unk_20);
    }
}

void func_8003566C(Npc *npc) {
    D_800AA248.unk_20 = npc->unk_0;
    switch (npc->unk_8) {
    case 0x64:
        func_80035B30(npc);
        return;
    case 5:
    case 3:
        func_80035B6C(npc);
    case 4:
        func_80035BE8(npc);
        return;
    case 1:
        func_80035A3C(npc);
        return;
    case 0x33:
        return;
    default:
        switch (npc->unk_A) {
        case 0:
            func_80035928(npc);
            return;
        case 1:
            func_800358C8(npc);
            return;
        case 2:
            func_8003599C(npc);
            return;
        case 3:
            func_8003585C(npc);
            return;
        default:
            D_800AA248.unk_20->unk_14 += D_800AA248.unk_20->unk_C;
            if (D_800AA248.unk_20->unk_C > 0) {
                if (((s16 *)&D_800AA248.unk_20->unk_14)[1] <= D_801D376C) {
                    return;
                }
            } else {
                if (((s16 *)&D_800AA248.unk_20->unk_14)[1] >= D_801D87B0) {
                    return;
                }
            }
            D_800AA248.unk_20->unk_C = 0;
            D_800AA248.unk_20->unk_10 = 0x4000;
            npc->unk_A = 3;
            npc->unk_1C = 1;
            func_8003EB5C(D_8008A938, D_800AA248.unk_20);
            return;
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_8003585C);

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_800358C8);

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80035928);

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_8003599C);

void func_80035A3C(Npc *npc) {
    u16 n;

    D_800AA248.unk_20->unk_18 = 0x01900000;
    n = npc->unk_1C;
    if (n == 0) {
        func_80035A88(npc);
        return;
    }
    npc->unk_1C = n - 1;
}

void func_80035A88(Npc *npc) {
    u8 *anim;

    npc->unk_A = 0;
    npc->unk_20 = (npc->unk_20 + 1) & 1;
    if (npc->unk_20 == 0) {
        anim = D_8008A998;
        ((s16 *)&D_800AA248.unk_20->unk_14)[1] = D_801D87B0 + 0xA;
    } else {
        anim = D_8008A9A4;
        ((s16 *)&D_800AA248.unk_20->unk_14)[1] = D_801D376C - 0xA;
    }
    D_800AA248.unk_20->unk_18 = 0x01540000;
    D_800AA248.unk_20->unk_10 = -0x8000;
    npc->unk_8 = 2;
    func_8003EB5C(anim, D_800AA248.unk_20);
}

void func_80035B30(Npc *npc) {
    u16 n = npc->unk_1C;

    if (n == 0) {
        func_80035A88(npc);
        return;
    }
    npc->unk_1C = n - 1;
}

void func_80035B6C(Npc *npc) {
    func_8001F724(5);
    D_800AA248.unk_20->unk_C = 0;
    D_800AA248.unk_20->unk_10 = 0;
    D_800AA248.unk_20->unk_80 = 0x1300;
    npc->unk_8 = 4;
    npc->unk_1C = 0x12;
    func_8003EB5C(D_8008AA28, D_800AA248.unk_20);
    func_8004BFE0();
}

void func_80035BE8(Npc *npc) {
    u16 n = npc->unk_1C;

    if (n == 0) {
        npc->unk_1C = 0xBE;
        npc->unk_8 = 0x33;
        D_800AA248.unk_20->unk_14 = 0x02000000;
        D_800AA248.unk_20->unk_18 = 0x02000000;
        func_8003C080(0x02000000);
        return;
    }
    npc->unk_1C = n - 1;
}

void func_80035C4C(Npc *npc) {
    D_800AA248.unk_20 = npc->unk_0;
    switch (npc->unk_8) {
    case 0x64:
        func_80035E80(npc);
        return;
    case 5:
    case 3:
        func_80035EBC(npc);
        return;
    case 4:
        func_80035F8C(npc);
        return;
    case 1:
        func_80035DC0(npc);
        return;
    case 0x33:
        return;
    default:
        if (D_800AA248.unk_20->unk_C > 0) {
            D_800AA248.unk_20->unk_14 += D_800AA248.unk_20->unk_C;
            if (((s16 *)&D_800AA248.unk_20->unk_14)[1] > D_801D376C) {
                D_800AA248.unk_20->unk_C = -0x6000;
                D_800AA248.unk_20->unk_22 |= 0x10;
            }
        } else {
            D_800AA248.unk_20->unk_14 += D_800AA248.unk_20->unk_C;
            if (((s16 *)&D_800AA248.unk_20->unk_14)[1] < D_801D87B0) {
                D_800AA248.unk_20->unk_C = 0x6000;
                D_800AA248.unk_20->unk_22 &= ~0x10;
            }
        }
        return;
    }
}

void func_80035DC0(Npc *npc) {
    u16 n = npc->unk_1C;

    if (n == 0) {
        func_80035DFC(npc);
        return;
    }
    npc->unk_1C = n - 1;
}

void func_80035DFC(Npc *npc) {
    ((s16 *)&D_800AA248.unk_20->unk_14)[1] = D_801D87B0 + 0x20;
    D_800AA248.unk_20->unk_18 = 0xF00000;
    D_800AA248.unk_20->unk_C = 0x6000;
    npc->unk_8 = 2;
    if (npc->unk_6 == 0x1C) {
        func_8003EB5C(D_8008A908, D_800AA248.unk_20);
    } else {
        func_8003EB5C(D_8008A8DC, D_800AA248.unk_20);
    }
}

void func_80035E80(Npc *npc) {
    u16 n = npc->unk_1C;

    if (n == 0) {
        func_80035DFC(npc);
        return;
    }
    npc->unk_1C = n - 1;
}

void func_80035EBC(Npc *npc) {
    Player *player;

    if (npc->unk_6 == 0x1C) {
        func_8001F724(5);
        D_800AA248.unk_20->unk_C = 0;
        D_800AA248.unk_20->unk_10 = 0;
        D_800AA248.unk_20->unk_80 = 0x1300;
        npc->unk_8 = 4;
        npc->unk_1C = 0x12;
        func_8004BFE0();
        return;
    }
    player = npc->unk_54;
    player->unk_5A = 8;
    npc->unk_1C = 0x12;
    func_80053D68(0x28000, player);
    D_800AA248.unk_20->unk_C = 0;
    D_800AA248.unk_20->unk_10 = 0;
    ((s16 *)&D_800AA248.unk_20->unk_18)[1] = 0x1F4;
    npc->unk_8 = 4;
}

void func_80035F8C(Npc *npc) {
    u16 n = npc->unk_1C;

    if (n == 0) {
        npc->unk_1C = 0xBE;
        npc->unk_8 = 0x33;
        D_800AA248.unk_20->unk_18 = 0x02000000;
        D_800AA248.unk_20->unk_14 = 0x02000000;
        func_8003C080(0x02000000);
        return;
    }
    npc->unk_1C = n - 1;
}

void func_80035FF0(void) {
    s32 r = func_80036028();

    D_800AA248.unk_20->unk_C = (r < 0) ? -0x20000 : 0x20000;
}

s32 func_80036028(void) {
    if (func_8001EB10(0xFF, 0) & 1) {
        D_800AA248.unk_20->unk_22 |= 0x10;
        D_800AA248.unk_20->unk_14 = D_801F9AC8[0] + 0x2440000;
        D_800AA248.unk_20->unk_C = -0x32000;
    } else {
        D_800AA248.unk_20->unk_22 &= ~0x10;
        D_800AA248.unk_20->unk_14 = D_801F9AC8[0] - 0x19A0000;
        D_800AA248.unk_20->unk_C = 0x32000;
    }
    return D_800AA248.unk_20->unk_C;
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_800360D8);

void func_80036298(void) {
    Npc *npc = D_801FAC9C;
    u16 n = D_801D8730;

    if (n != 0) {
        if (n >= 7) {
            n = 6;
        }
        do {
            func_80036300(npc);
            npc++;
        } while (--n != 0);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80036300);

void func_800363E4(void) {
    Npc *npc = D_801FAC9C;
    u16 n = 6;

    do {
        func_800369F8(npc);
        npc++;
    } while (--n != 0);
    D_801D8730 = n;
    D_801E2A50 = n;
}

#ifdef NON_MATCHING
/* 95.59 %: the scheduler loads unk_22 before the unk_40 store in the original (here after); the statements and types are right */
void func_80036440(Npc *npc, s32 depth) {
    Mover *mover;
    Effect *effect;
    s32 d;

    mover = func_8001EB9C(0, 0, 0, 0, 0xFFFFFF);
    mover->unk_40 = -0x3E7;
    d = depth - 1;
    mover->unk_80 = d;
    mover->unk_22 = (mover->unk_22 & ~0x20) | 0x400;
    mover->unk_6C |= 0x2000;
    npc->unk_70 = mover;
    func_8001BB68(mover);
    effect = func_8001D110();
    effect->unk_0 = 0x4F000986;
    effect->unk_20 = d;
    D_800AA284 = effect;
    mover = func_8001DCB4();
    mover->unk_22 |= 0x400;
    npc->unk_74 = mover;
    func_8001BB68(mover);
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80036440);
#endif

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80036504);

void func_80036818(Npc *npc) {
    Mover *a = npc->unk_70;
    Mover *b = npc->unk_0;
    Mover *c = npc->unk_74;

    if (a != NULL) {
        func_80036504(a, b, c);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_8003684C);

void func_800369F8(Npc *npc) {
    memset(npc, 0, sizeof(Npc));
    D_801D8730 = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80036A20);

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80036C30);

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80036FD0);

void func_80037078(Player *player, NpcS *npc) {
    player->unk_24++;
    func_80054374(0x28, player);
    func_800634D4(player, 4);
    npc->unk_8 = 3;
    npc->unk_60 = player;
    npc->unk_54 = D_800AA248.unk_20->unk_22;
    npc->unk_5C = player->unk_120;
    npc->unk_5E = player->unk_122;
    if (player->unk_142 != 0) {
        npc->unk_1A += 0xA;
    }
    player->unk_18A = 1;
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_8003712C);

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_800372DC);

u16 func_800374FC(s16 x, s16 y, Npc *npc, s32 arg3) {
    MoverTarget *target = D_800AA248.unk_20->unk_94;

    if (target != NULL) {
        Npc *other = (Npc *)target->unk_4->unk_90;
        if (other != npc && other->unk_A != 2) {
            return func_80037574(x, y, arg3);
        }
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80037574);

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_8003761C);

void func_800376D8(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_800376E0);

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_800377B4);

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80037960);

void func_80037A88(NpcS *npc) {
    D_800AA248.unk_20 = npc->unk_0;
    switch (npc->unk_8) {
    case 0x64:
        func_80037BB4(npc);
        return;
    case 3:
        func_80037CA0(npc);
        return;
    case 0xD:
        func_80037D78(npc);
        return;
    case 0x3B:
    case 1:
        func_80037C1C(npc);
        return;
    case 5:
        func_80037E1C(npc);
        return;
    case 4:
        func_80037E78(npc);
        return;
    case 0x33:
        return;
    default:
        if (npc->unk_A != 0) {
            func_80037EE0(npc);
            return;
        }
        func_80020D20(npc);
        func_800376E0(npc);
        return;
    }
}

void func_80037BB4(NpcS *npc) {
    if (npc->unk_1C == 0) {
        func_80037C1C(npc);
        return;
    }
    npc->unk_1C--;
    D_800AA248.unk_20->unk_C = D_801F9AC8[0] - 0x19A0000;
    D_800AA248.unk_20->unk_10 = 0;
}

void func_80037C1C(NpcS *npc) {
    if (npc->unk_1C != 0) {
        npc->unk_1C--;
        D_800AA248.unk_20->unk_18 = 0x01900000;
        return;
    }
    func_80035FF0();
    func_800380C0(D_800AA248.unk_20);
    npc->unk_8 = 2;
    npc->unk_22 = 0;
    func_8003EB5C(D_8008A374, D_800AA248.unk_20);
}

void func_80037CA0(NpcS *npc) {
    if ((D_800AA248.unk_20->unk_22 ^ npc->unk_54) & 0x10) {
        func_80037E1C(npc);
        return;
    }
    func_80037CF4(npc);
}

void func_80037CF4(NpcS *npc) {
    func_80034B68(0x58000);
    D_800AA248.unk_20->unk_10 = -0x65529;
    D_800AA248.unk_20->unk_14 += D_800AA248.unk_20->unk_C;
    D_800AA248.unk_20->unk_80 = 0x4000;
    npc->unk_8 = 0xD;
    func_8003EB5C(D_8008A398, D_800AA248.unk_20);
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80037D78);

void func_80037E1C(NpcS *npc) {
    func_8001F724(5);
    D_800AA248.unk_20->unk_C = 0;
    D_800AA248.unk_20->unk_10 = 0;
    npc->unk_8 = 4;
    npc->unk_1C = 3;
    func_80034670();
}

void func_80037E78(NpcS *npc) {
    if (npc->unk_1C != 0) {
        npc->unk_1C--;
        return;
    }
    D_800AA248.unk_20->unk_C = 0;
    D_800AA248.unk_20->unk_10 = 0;
    npc->unk_8 = 0x33;
    D_800AA248.unk_20->unk_18 = 0x02000000;
    func_8003831C();
}

void func_80037EE0(NpcS *npc) {
    npc->unk_A = 0;
    D_800AA248.unk_20->unk_C = -D_800AA248.unk_20->unk_C;
    D_800AA248.unk_20->unk_22 ^= 0x10;
}

void func_80037F20(NpcS *npc) {
    D_800AA248.unk_20 = npc->unk_0;
    switch (npc->unk_8) {
    case 0x64:
        func_80038058(npc);
        return;
    case 0x1E:
        func_80038198(npc);
        return;
    case 0x3B:
    case 1:
        func_800380F0(npc);
        return;
    case 3:
    case 5:
        func_800381E4(npc);
        return;
    case 4:
        func_80038240(npc);
        return;
    case 0xD:
    case 0x33:
        return;
    default:
        if (npc->unk_A != 0) {
            func_800382A8(npc);
            return;
        }
        func_80020D20(npc);
        func_800376E0(npc);
        return;
    }
}

void func_80038058(NpcS *npc) {
    if (npc->unk_1C == 0) {
        func_800380F0(npc);
        return;
    }
    npc->unk_1C--;
    D_800AA248.unk_20->unk_14 = D_801F9AC8[0] - 0x19A0000;
    D_800AA248.unk_20->unk_10 = 0;
}

void func_800380C0(Mover *mover) {
    if (!(mover->unk_22 & 0x10)) {
        mover->unk_18 = 0xEB0000;
    } else {
        mover->unk_18 = 0xE30000;
    }
    mover->unk_80 = ((u16 *)&mover->unk_18)[1] + 0xF23;
}

void func_800380F0(NpcS *npc) {
    if (npc->unk_1C != 0) {
        npc->unk_1C--;
        D_800AA248.unk_20->unk_18 = 0x01900000;
        return;
    }
    func_80035FF0();
    func_800380C0(D_800AA248.unk_20);
    npc->unk_8 = 2;
    npc->unk_22 = 0;
    if (npc->unk_6 == 0x3E) {
        func_8003EB5C(D_8008A3E0, D_800AA248.unk_20);
    } else {
        func_8003EB5C(D_8008A414, D_800AA248.unk_20);
    }
}

void func_80038198(NpcS *npc) {
    if (npc->unk_6 == 0x3E) {
        func_8003EB5C(D_8008A408, D_800AA248.unk_20);
    } else {
        func_8003EB5C(D_8008A43C, D_800AA248.unk_20);
    }
}

void func_800381E4(NpcS *npc) {
    func_8001F724(5);
    D_800AA248.unk_20->unk_C = 0;
    D_800AA248.unk_20->unk_10 = 0;
    npc->unk_8 = 4;
    npc->unk_1C = 3;
    func_80034670();
}

void func_80038240(NpcS *npc) {
    if (npc->unk_1C != 0) {
        npc->unk_1C--;
        return;
    }
    D_800AA248.unk_20->unk_C = 0;
    D_800AA248.unk_20->unk_10 = 0;
    npc->unk_8 = 0x33;
    D_800AA248.unk_20->unk_18 = 0x02000000;
    func_8003831C();
}

void func_800382A8(NpcS *npc) {
    npc->unk_A = 0;
    D_800AA248.unk_20->unk_C = -D_800AA248.unk_20->unk_C;
    D_800AA248.unk_20->unk_22 ^= 0x10;
}

void func_800382E8(void) {
    ((NpcS *)D_800AA248.unk_20->unk_90)->unk_1C = 0;
}

void func_80038300(void) {
    ((NpcS *)D_800AA248.unk_20->unk_90)->unk_C = 1;
}

void func_8003831C(void) {
    ((NpcS *)D_800AA248.unk_20->unk_90)->unk_6 = 0;
    func_8004CFC0();
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80038348);

void func_800383F4(NpcS *npc) {
    if (npc->unk_1C == 0) {
        if (func_80039C40(D_800AA248.unk_20->unk_14, -0x280000, -0x280000) == 0) {
            npc->unk_6 = 0xF;
            npc->unk_8 = 2;
            func_8003EB5C(D_80095EF0, D_800AA248.unk_20);
            func_8001BB88(D_800AA248.unk_20);
        }
    } else {
        npc->unk_1C--;
        func_8001BB68(D_800AA248.unk_20);
    }
}

void func_80038494(NpcS *npc) {
    u16 n = npc->unk_1A;

    if (n >= 2) {
        func_80038754(npc);
        return;
    }
    npc->unk_1A = n + 1;
    npc->unk_8 = 0x32;
    npc->unk_20 = 1;
    func_800398D4();
}

void func_800384E8(NpcS *npc) {
    if (npc->unk_64 == NULL) {
        func_800385F4(npc);
        return;
    }
    func_80038528(npc);
}

void func_80038528(NpcS *npc) {
    switch (npc->unk_64->unk_CC) {
    case 6:
    case 7:
    case 8:
        if (D_800AA248.unk_20->unk_22 & 0x10) {
            npc->unk_20 = 0;
        } else {
            npc->unk_20 = 1;
        }
        npc->unk_22 = 3;
        D_800AA248.unk_20->unk_C = 0;
        break;
    case 2:
    case 3:
    case 4:
        if (!(D_800AA248.unk_20->unk_22 & 0x10)) {
            npc->unk_20 = 0;
        } else {
            npc->unk_20 = 1;
        }
        npc->unk_22 = 3;
        D_800AA248.unk_20->unk_C = 0;
        break;
    default:
        npc->unk_22 = 1;
        break;
    }
    func_800385F4(npc);
}

#ifdef NON_MATCHING
/* 11 instructions differ: the flags read into `facing` keep their own register (a1) before the `andi` in the
 * original; every variant tried ties the two. */
void func_800385F4(NpcS *npc) {
    s32 speed;
    u16 n;

    if (D_800AA248.unk_20->unk_C == 0) {
        u8 **table;
        s32 idx;

        if (npc->unk_20 == 1) {
            u16 facing;

            speed = 0x28000;
            npc->unk_22 = 0x14;
            if (npc->unk_64 == NULL) {
                facing = npc->unk_54 & 0x10;
            } else {
                speed = -0x28000;
                facing = D_800AA248.unk_20->unk_22 & 0x10;
            }
            if (facing != 0) {
                speed = -speed;
            }
        } else {
            npc->unk_22 = 0x28;
            if (D_800AA248.unk_20->unk_22 & 0x10) {
                speed = -0x28000;
            } else {
                speed = 0x28000;
            }
        }
        D_800AA248.unk_20->unk_C = speed;
        idx = npc->unk_2E & 3;
        if (npc->unk_20 == 1) {
            table = D_8007DA58;
        } else {
            table = D_8007DA68;
        }
        func_8003EB5C(table[idx], D_800AA248.unk_20);
    }
    n = npc->unk_22 - 1;
    npc->unk_22 = n;
    if (n == 0 || func_80039958(npc) == 1) {
        npc->unk_22 = 0;
        D_800AA248.unk_20->unk_C = 0;
        npc->unk_8 = 2;
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_800385F4);
#endif

void func_80038754(NpcS *npc) {
    Player *player;

    func_8001F724(5);
    D_800AA248.unk_20->unk_C = 0;
    D_800AA248.unk_20->unk_10 = 0;
    player = npc->unk_64;
    npc->unk_8 = 4;
    npc->unk_1C = 3;
    if (player != NULL) {
        func_80053C50(0x80000, player);
        func_8004A90C(player);
        npc->unk_64 = NULL;
        player->unk_1D4 = 0;
    }
    func_800215C0(((s16 *)&D_800AA248.unk_20->unk_14)[1], ((u16 *)&D_800AA248.unk_20->unk_18)[1] - 0xA);
}

void func_80038800(NpcS *npc) {
    if (npc->unk_1C != 0) {
        npc->unk_1C--;
        return;
    }
    func_80038838(npc);
}

void func_80038838(NpcS *npc) {
    u16 kind;

    D_800AA248.unk_20->unk_C = 0;
    D_800AA248.unk_20->unk_10 = 0;
    kind = npc->unk_6;
    if (kind == 0x13) {
        npc->unk_8 = 1;
        npc->unk_1C = (func_8001EA78() & 0xFF) + 0x190;
        npc->unk_34 = 0;
        npc->unk_30 = 0;
        func_8003AAF8(npc);
        return;
    }
    if (kind == 0x31) {
        npc->unk_8 = 1;
        npc->unk_1C = (func_8001EA78() & 0xFF) + 0x12C;
        npc->unk_34 = 0;
        npc->unk_30 = 0;
        ((s16 *)&D_800AA248.unk_20->unk_14)[1] = D_801D8864[0] & func_8001EA78();
        func_80039A58(npc);
        return;
    }
    npc->unk_1C = 0x96;
    D_800AA248.unk_20->unk_18 = 0x02000000;
    func_8003831C();
}

#ifdef NON_MATCHING
/* 95.60 %: register choices only: the table entries' addresses are built in a0 in the original (v1/v0 here) */
void func_80038920(NpcS *npc) {
    u16 which;
    u8 *anim;

    if (func_80038C1C() != 0) {
        return;
    }
    if (func_80039220(&which, npc) == 0) {
        if (npc->unk_C != 0) {
            func_8003EB5C(*(D_8007DA68 + (npc->unk_2E & 3)), D_800AA268);
        }
    } else {
        anim = *(*(D_8007DA78 + (npc->unk_2C & 3)) + which);
        if (anim != (u8 *)D_800AA268->unk_48) {
            func_8003EB5C(anim, D_800AA268);
            return;
        }
        if (npc->unk_4E != 0) {
            if (npc->unk_64 != NULL) {
                func_80038528(npc);
                return;
            }
            npc->unk_8 = 0x32;
            npc->unk_20 = 0;
            npc->unk_4 = 0;
        }
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80038920);
#endif

void func_80038A2C(NpcS *npc) {
    u16 move = npc->unk_2A;

    if (move != 0) {
        npc->unk_2C = move;
        if (func_80038DA8(npc) != 0) {
            s32 kind = npc->unk_2A;

            npc->unk_4++;
            switch (kind) {
            case 3:
                func_8003EB5C(D_80095E24, D_800AA248.unk_20);
                return;
            case 2:
                func_8003EB5C(D_80095E68, D_800AA248.unk_20);
                return;
            default:
                func_8003EB5C(D_80095EAC, D_800AA248.unk_20);
                return;
            }
        }
    }
    func_80038920(npc);
}

#ifdef NON_MATCHING
/* 96.62 %: register choices only, as func_80038920: the table entry's address is built in v1 in the original */
void func_80038AE8(NpcS *npc) {
    Player *player;

    player = npc->unk_64;
    if ((player == NULL || player->unk_CC == 0 || player->unk_CC == 5 || player->unk_CC == 1) && npc->unk_2A == 4) {
        if (npc->unk_C != 0) {
            func_8003EB5C(D_8007DA68[npc->unk_2E & 3], D_800AA268);
        }
        return;
    }
    if (npc->unk_C == 0) {
        return;
    }
    if (D_800AA268->unk_C == 0) {
        npc->unk_C = 0;
        if (player != NULL && player->unk_CC != 0 && player->unk_CC != 5 && player->unk_CC != 1) {
            npc->unk_8 = 0x32;
            func_80038528(npc);
            return;
        }
        if (npc->unk_1C == 0) {
            func_80038A2C(npc);
            return;
        }
        npc->unk_1C--;
    }
    D_800AA248.unk_20->unk_C = 0;
    func_8003EB5C(D_8007DA68[npc->unk_2E & 3], D_800AA248.unk_20);
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80038AE8);
#endif

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80038C1C);

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80038DA8);

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80038F3C);

u16 func_800391F8(u16 *out, NpcS *npc) {
    *out = npc->unk_2C;
    if (npc->unk_64 != NULL) {
        npc->unk_4 = 3;
    }
    return 1;
}

u16 func_80039220(u16 *out, NpcS *npc) {
    u16 state = npc->unk_4;

    if (state != 0) {
        if (state < 3) {
            return func_800391F8(out, npc);
        }
        if (npc->unk_4E != 0) {
            npc->unk_8 = 0x32;
            npc->unk_20 = 0;
            npc->unk_4 = 0;
        }
        return 0;
    }
    return func_80038F3C(out, npc);
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80039290);

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80039358);

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_8003956C);

void func_80039890(void) {
    NpcS *npc = (NpcS *)D_800AA248.unk_20->unk_90;
    u16 *info;

    npc->unk_C = 1;
    info = D_800AA248.unk_20->unk_5C;
    npc->unk_2A = *info;
    npc->unk_2E = *info;
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_800398D4);

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80039958);

void func_80039A58(NpcS *npc) {
    if (npc->unk_1C == 0) {
        if (func_80039C40(D_800AA248.unk_20->unk_14, -0x280000, -0x280000) == 0) {
            npc->unk_6 = 0x31;
            npc->unk_8 = 2;
            npc->unk_1C = 0x3C;
            npc->unk_1A = 0;
            func_8003EB5C(D_8009585C, D_800AA248.unk_20);
            func_8001BB88(D_800AA248.unk_20);
        }
    } else {
        npc->unk_1C--;
        func_8001BB68(D_800AA248.unk_20);
    }
}

s32 func_80039B04(Player *player, s32 x) {
    s32 pos = player->unk_68->unk_14;

    if (abs(x - pos) > (D_801D8864[0] + 1) / 2) {
        x += D_801D8864[0] + 1;
    }
    return abs(x - pos);
}

Player *func_80039B60(s32 x) {
    Player *best = NULL;
    s32 bestDist = 0x1FFF0000;
    s32 i;

    for (i = 0; i < 3; i++) {
        s32 slot = func_80025DF8(i + 1);

        if (*(u16 *)&D_801E0B78[slot] != 0) {
            s32 pos = D_801E0B78[slot].unk_68->unk_14;
            s32 dist;

            if (pos < D_801F9AC8[0]) {
                pos += D_801D8864[0];
            }
            dist = abs(pos - x);
            if (dist < bestDist) {
                bestDist = dist;
                best = &D_801E0B78[slot];
            }
        }
    }
    return best;
}

s32 func_80039C40(s32 x, s32 left, s32 right) {
    if (x < D_801F9AC8[0]) {
        x += D_801D8864[0] + 1;
    }
    if (x < D_801F9AC8[0] + left || D_801F9AC8[0] + (0x01900000 - right) < x) {
        return 0;
    }
    return 1;
}

s32 func_80039C98(s32 x, s32 left, s32 right) {
    if (x < D_801F9AC8[0]) {
        x += D_801D8864[0] + 1;
    }
    if ((D_801F9AC8[0] < x && x < D_801F9AC8[0] + left) ||
        (D_801F9AC8[0] + (0x01900000 - right) < x && x < D_801F9AC8[0] + 0x01900000)) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80039D04);

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80039EC4);

void func_8003A0A8(NpcS *npc) {
    if (D_801FA990 != 0 || D_801FA98C != 0) {
        if (((s16 *)&D_800AA248.unk_20->unk_14)[1] > D_801FA98C && ((s16 *)&D_800AA248.unk_20->unk_14)[1] < D_801FA98C + 4 &&
            !(D_800AA248.unk_20->unk_22 & 0x10)) {
            goto stop;
        }
        if (((s16 *)&D_800AA248.unk_20->unk_14)[1] < D_801FA990 && D_801FA990 - 4 < ((s16 *)&D_800AA248.unk_20->unk_14)[1] &&
            (D_800AA248.unk_20->unk_22 & 0x10)) {
            goto stop;
        }
    }
    if (func_80039C40(D_800AA248.unk_20->unk_14, 0x460000, 0x460000) == 0) {
        func_8003EB5C(D_80095874, D_800AA248.unk_20);
        if (D_800AA248.unk_20->unk_22 & 0x10) {
            npc->unk_34 = -0x28000;
            D_800AA248.unk_20->unk_C = 0;
            return;
        }
        npc->unk_34 = 0x28000;
        D_800AA248.unk_20->unk_C = 0;
        return;
    }
stop:
    npc->unk_8 = 2;
    npc->unk_1C = 0x1E;
    func_8003EB5C(D_8009585C, D_800AA248.unk_20);
    npc->unk_34 = 0;
    D_800AA248.unk_20->unk_C = 0;
    npc->unk_24 = 0;
}

#ifdef NON_MATCHING
/* 99.78 %: the velocity lands in v1 here; the original reuses the flag test's v0 */
void func_8003A218(NpcS *npc) {
    Player *player;
    s32 v;

    npc->unk_1C--;
    player = func_80039B60(D_800AA248.unk_20->unk_14);
    if (player != NULL && func_80039B04(player, D_800AA248.unk_20->unk_14) <= 0x77FFFF && npc->unk_1C > 0) {
        func_8003EB5C(D_800958E0, D_800AA248.unk_20);
        v = 0x20000;
        if (!(D_800AA248.unk_20->unk_22 & 0x10)) {
            v = -0x20000;
        }
        npc->unk_34 = v;
        D_800AA248.unk_20->unk_C = 0;
        return;
    }
    npc->unk_8 = 2;
    npc->unk_1C = 0x14;
    func_8003EB5C(D_8009585C, D_800AA248.unk_20);
    npc->unk_34 = 0;
    D_800AA248.unk_20->unk_C = 0;
    npc->unk_24 = 0;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_8003A218);
#endif

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_8003A328);

void func_8003A4A0(Npc *npc) {
    u16 n;

    D_800AA248.unk_20->unk_C = 0;
    n = npc->unk_1C - 1;
    npc->unk_1C = n;
    npc->unk_34 = npc->unk_34 * 6 / 7;
    if ((s16)n == -1) {
        npc->unk_8 = 0x10;
        npc->unk_34 = 0;
        npc->unk_1C = 0x28;
    }
}

void func_8003A520(void) {
    Mover *mover = D_800AA248.unk_20;
    u16 *info = mover->unk_5C;
    u16 sound = *info++;
    u16 arg = info[0];
    u16 which = info[1];

    if (!(mover->unk_6C & 0x80)) {
        if (sound != 0) {
            func_8001F7CC(arg, sound);
        }
        func_8004A9B0(0, which, 0x15, 0, 0);
    }
    D_800AA248.unk_20 = mover;
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_8003A5A0);

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_8003A744);

void func_8003A904(NpcS *npc) {
    npc->unk_2A = 1;
    switch (npc->unk_24) {
    case 0:
        func_8003EB5C(D_80095B18, D_800AA248.unk_20);
        break;
    case 1:
        func_8003EB5C(D_80095AF0, D_800AA248.unk_20);
        break;
    default:
        func_8003EB5C(D_80095AC8, D_800AA248.unk_20);
        break;
    }
    npc->unk_8 = 2;
    npc->unk_1C = 0x14;
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_8003A98C);

void func_8003AA7C(NpcS *npc) {
    D_800AA248.unk_20->unk_80 = 0x4000;
    npc->unk_8 = 2;
    npc->unk_1C = 0x3C;
    func_8003EB5C(D_800956D0, D_800AA248.unk_20);
    npc->unk_14 = 0;
    npc->unk_C = 1;
    ((s16 *)&D_800AA248.unk_20->unk_18)[1] = 0x3C;
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_8003AAF8);

void func_8003ABE8(NpcS *npc) {
    if (D_800AA248.unk_20->unk_22 & 0x10) {
        npc->unk_34 = -0x40000;
    } else {
        npc->unk_34 = 0x40000;
    }
    D_800AA248.unk_20->unk_C = 0;
    if (npc->unk_1C != 0) {
        npc->unk_1C--;
        return;
    }
    if (D_800AA248.unk_20->unk_6C & 0x80) {
        func_8003AA7C(npc);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_8003AC74);

void func_8003AEA0(NpcS *npc) {
    if (func_80039C40(D_800AA248.unk_20->unk_14, 0x460000, 0x460000) == 0) {
        if (D_800AA248.unk_20->unk_22 & 0x10) {
            npc->unk_34 = -0x48000;
            D_800AA248.unk_20->unk_C = 0;
        } else {
            npc->unk_34 = 0x48000;
            D_800AA248.unk_20->unk_C = 0;
        }
    } else {
        npc->unk_8 = 2;
        npc->unk_1C = 0x1E;
        npc->unk_34 = 0;
        D_800AA248.unk_20->unk_C = 0;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_8003AF40);

void func_8003B1D0(NpcS *npc) {
    if (npc->unk_C != 0) {
        if (npc->unk_1C > 0) {
            npc->unk_1C--;
        }
        if (func_80039C40(D_800AA248.unk_20->unk_14, 0xA0000, 0xA0000) == 0) {
            npc->unk_8 = 0x15;
            return;
        }
        if (npc->unk_1C == 0) {
            if (func_80039C98(D_800AA248.unk_20->unk_14, 0x460000, 0x460000) != 0) {
                npc->unk_8 = 0x16;
                npc->unk_24 = 0;
                return;
            }
            npc->unk_8 = 0x16;
            npc->unk_24 = 3;
            npc->unk_1C = 0x14;
        }
    }
}

void func_8003B294(NpcS *npc) {
    u16 action;

    D_800AA248.unk_20 = npc->unk_0;
    func_80020D20(npc);
    action = npc->unk_8;
    if (action != 0x63 && action != 1) {
        func_8003AC74(npc);
    }
    switch (npc->unk_8) {
    case 0x3B:
    case 1:
        func_8003AAF8(npc);
        return;
    case 2:
        func_8003B1D0(npc);
        return;
    case 0x63:
        func_8003ABE8(npc);
        return;
    case 0x15:
        func_8003AEA0(npc);
        return;
    case 0x16:
        func_8003AF40(npc);
        return;
    case 3:
        func_8003A328(npc, 0);
        return;
    case 4:
        func_80038800(npc);
        return;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_8003B3C8);
