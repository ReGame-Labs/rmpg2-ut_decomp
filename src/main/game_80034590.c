/* A file of the game's code, named after its first function until its contents are understood: the records of
 * D_801FA9BC (UnkStructB1) and D_801FAC9C (NpcS, include/game_80034590.h) and their per-kind updaters.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "game.h"
#include "game_80034590.h"
#include "psyq/libc2.h"

/* Other units. */
ObjectDef *func_8001D110(void);
GameObject *func_8001DCB4(void);         /* spawns D_800AA248.unk_3C */
void func_8001E4B0(GameObject *mover);
void func_80029118(s32 a, s32 b);
void func_8004BFE0(void);
void func_80053D68(s32 n, Monster *player);
s32 func_8001EA78(void);
void func_8001F7CC(s32 a, s32 b);
u16 func_8004A9B0(void *a, s32 b, s32 c, s32 d, s32 e);
void func_8001BB68(GameObject *mover);
GameObject *func_8001EB9C(s32 a, s32 b, s32 c, s32 d, s32 color);
void func_8001BB88(GameObject *mover);
s16 func_8001EB10(s32 arg0, s32 arg1);
s32 *func_80025C08(void *list);
extern s32 D_8007DA48[];
extern s32 D_8007D470[];                /* speeds by kind - 1 (func_800360D8) */
void func_8003BD48(UnkStructB1 *npc);                /* the spawn list of D_801FAC9C */
void func_8001F724(s32 sound);
void func_80020D20();                /* called with the record and without it: no prototype in the original */
void func_800242A8(void);
s32 func_80025DF8(s32 n);
void func_8003EB5C(u8 *anim, GameObject *mover);
u16 func_8003BE34(UnkStructB1 *npc);
void func_8004CFC0(void);
void func_80054374(s32 n, Monster *player);
void func_80053C50(s32 n, Monster *player);
void func_8004A90C(Monster *player);
void func_800215C0(s16 x, s16 y);
void func_8003C080();                /* called with the position and without: no prototype in the original */
void func_800634D4(Monster *player, s32 n);
s32 abs(s32 n);

void func_80029D1C(void);
s32 func_8003B9C8(GameObject *mover, Monster *player);
void func_8005E0E8(Monster *player);
void func_8004BBC8(NpcS *npc);
void func_80020DDC(NpcS *npc);

/* This unit. */
u16 func_80036FD0(s16 x, s16 y, GameObject *mover);
u16 func_80036C30(Monster *player, NpcS *npc, GameObject *mover, s32 reach);
void func_800383F4(NpcS *npc);
void func_80038494(NpcS *npc);
void func_800384E8(NpcS *npc);
void func_80038AE8(NpcS *npc);
void func_80036818(NpcS *npc);
void func_80037A88(NpcS *npc);
void func_80037F20(NpcS *npc);
void func_80038348(NpcS *npc);
void func_8003A98C(NpcS *npc);
void func_8003B294(NpcS *npc);
void func_8003B3C8(NpcS *npc);
void func_80035260();                /* called without the record it takes: no prototype in the original */
void func_8003518C(UnkStructB1 *npc);
void func_80035330(UnkStructB1 *npc);
void func_800345F8(UnkStructB1 *npc);
void func_80034B68(s32 speed);
void func_800346FC(UnkStructB1 *npc);
s32 func_80036028(void);
u16 func_80039958(NpcS *npc);
void func_8003AAF8(NpcS *npc);
void func_80039A58(NpcS *npc);
void func_8003831C(void);
void func_800347E4(UnkStructB1 *npc, Anim *def);
void func_80036504(GameObject *a, GameObject *b, GameObject *c);
void func_80035B6C(UnkStructB1 *npc);
void func_80035EBC(UnkStructB1 *npc);
void func_8003585C(UnkStructB1 *npc);
void func_800358C8(UnkStructB1 *npc);
void func_80035928(UnkStructB1 *npc);
void func_8003599C(UnkStructB1 *npc);
void func_80035E80(UnkStructB1 *npc);
void func_80035F8C(UnkStructB1 *npc);
void func_80035DC0(UnkStructB1 *npc);
void func_80035BE8(UnkStructB1 *npc);
void func_80035A3C(UnkStructB1 *npc);
void func_80035B30(UnkStructB1 *npc);
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
Monster *func_80039B60(s32 x);
s32 func_80039B04(Monster *player, s32 x);
void func_80034988(UnkStructB1 *npc);
void func_80034C54(GameObject *mover);
void func_80034D28(UnkStructB1 *npc);
void func_80034DAC(UnkStructB1 *npc);
void func_80034E48(UnkStructB1 *npc);
void func_80035040(void);
void func_800351CC(UnkStructB1 *npc);
void func_800354A4();                /* called without the record it reads: no prototype in the original */
void func_80035464(UnkStructB1 *npc);
void func_80035550(UnkStructB1 *npc);
void func_80035590(UnkStructB1 *npc);
void func_80035620(UnkStructB1 *npc);
void func_80035A88(UnkStructB1 *npc);
void func_80035DFC(UnkStructB1 *npc);
void func_80035FF0(void);
void func_80036300(NpcS *npc);
void func_800369F8(NpcS *npc);
u16 func_80037574(s16 x, s16 y, GameObject *mover);
u16 func_8003761C(s16 x, s16 y, Monster *player, NpcS *npc);
void func_800376E0(NpcS *npc);
void func_80037960(NpcS *npc, GameObject *obj);
void func_80037BB4(NpcS *npc);
void func_80037C1C(NpcS *npc);
void func_80037CA0(NpcS *npc);
void func_80037CF4(NpcS *npc);
void func_80037D78(NpcS *npc);
void func_80037E1C(NpcS *npc);
void func_80037E78(NpcS *npc);
void func_80037EE0(NpcS *npc);
void func_800380C0(GameObject *mover);
void func_80038528(NpcS *npc);
void func_800385F4(NpcS *npc);
void func_80038754(NpcS *npc);
void func_80038800(NpcS *npc);
void func_80038838(NpcS *npc);
u16 func_80038C1C();                 /* called without the record it reads: no prototype in the original */
u16 func_80038F3C(u16 *out, NpcS *npc);
u16 func_800391F8(u16 *out, NpcS *npc);
u16 func_80039220(u16 *out, NpcS *npc);
void func_800398D4();                /* called without the record it reads: no prototype in the original */
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
extern Anim *D_8007D50C[];
extern Anim D_8008A538;
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
extern u8 D_8008A448[];
extern u8 D_8008A5A8[];
extern u8 D_8008A62C[];
extern u8 D_8008A8DC[];
extern u8 D_8008A908[];
extern u8 D_8008A938[];
extern u8 D_8008A998[];
extern u8 D_8008A9A4[];
extern void (*D_8007D558[])(void);  /* per kind */
extern void (*D_8007D5A4[])(void);  /* per kind */
extern u8 *D_8007D45C[];
extern u8 *D_8007DA68[];
extern u8 *D_8007DA78[][4];
extern u8 *D_8007DAB8[];
extern u8 D_8008A47C[];
extern u8 D_8008AA10[];
extern u8 D_8008A374[];
extern u8 D_80095EF0[];
extern u8 D_8009585C[];
extern u8 D_800958E0[];
extern u8 D_80095E24[];
extern u8 D_80095E68[];
extern u8 D_80095EAC[];
extern u8 D_80095874[];
extern GameObject *D_801FB44C[3];
extern u8 D_8008A9D4[];
extern u8 D_8008AA40[];
extern u8 D_8008AA34[];
extern u8 D_8008A9B0[];
extern u8 D_8008A968[];
extern u8 D_8008A914[];
extern u8 D_8008A4F4[];
extern Anim D_800960E0;
extern s32 D_801E1E14;
extern u8 D_800956C4[];
extern Anim *D_8007D448[];
extern u8 D_8008A59C[];
extern u8 D_8008A620[];
extern Anim D_8008A7E4;
extern Anim D_8008A828;
extern u8 D_800959D4[];
extern u8 D_8009594C[];
extern u8 D_80095800[];
extern u8 D_800957A4[];

void func_80034590(UnkStructB1 *npc) {
    npc->unk_08 = 2;
    npc->unk_1E = func_8001EB10(0x190, 0);
    npc->unk_22 = 0;
    func_8003EB5C(D_8007D4C0[npc->unk_06 - 1], D_800AA248.cur_obj);
}

void func_800345F8(UnkStructB1 *npc) {
    func_8001F724(5);
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    npc->unk_08 = 4;
    npc->unk_1C = 5;
    func_800347E4(npc, D_8007D50C[npc->unk_06 - 1]);
}

void func_80034670(void) {
    GameObject *saved = D_800AA248.cur_obj;
    ObjectDef *effect;
    u16 y;

    effect = func_8001D110();
    D_800AA248.new_def = effect;
    effect->pos_x.s.hi = ((u16 *)&D_800AA248.cur_obj->pos_x.w)[1];
    y = ((u16 *)&D_800AA248.cur_obj->pos_y.w)[1];
    effect->anim = &D_8008A538;
    effect->pos_y.s.hi = y;
    effect->flags = *(u16 *)&D_800AA248.cur_obj->priority + 1;
    effect->id = D_8008A538.id;
    func_8001DCB4();
    D_800AA248.cur_obj = saved;
}

void func_800346FC(UnkStructB1 *npc) {
    GameObject *saved = D_800AA248.cur_obj;
    Anim *table;
    GameObject *mover;
    ObjectDef *effect;

    func_8001F724(5);
    func_80029118(8, 8);
    mover = npc->unk_40;
    table = &D_8008A7A4;
    D_800AA248.new_def = func_8001D110();
    effect = D_800AA248.new_def;
    if (mover->flags & 0x10) {
        effect->pos_x.s.hi = ((s16 *)&mover->pos_x.w)[1] + 0x28;
    } else {
        effect->pos_x.s.hi = ((s16 *)&mover->pos_x.w)[1] - 0x28;
    }
    effect->pos_y.s.hi = ((s16 *)&mover->pos_y.w)[1] - 0x19;
    effect->anim = table;
    effect->flags = *(u16 *)&mover->priority + 1;
    effect->id = table->id;
    func_8001DCB4();
    func_8001E4B0(npc->unk_40);
    npc->unk_40 = NULL;
    D_800AA248.cur_obj = saved;
}

void func_800347E4(UnkStructB1 *npc, Anim *def) {
    GameObject *saved = D_800AA248.cur_obj;
    ObjectDef *effect;

    D_800AA248.new_def = func_8001D110();
    effect = D_800AA248.new_def;
    effect->pos_x.s.hi = ((u16 *)&D_800AA248.cur_obj->pos_x.w)[1];
    effect->pos_y.s.hi = ((u16 *)&D_800AA248.cur_obj->pos_y.w)[1];
    effect->anim = def;
    effect->flags = *(u16 *)&D_800AA248.cur_obj->priority + 1;
    effect->id = def->id;
    func_8001DCB4();
    if (npc->unk_40 != NULL) {
        func_800346FC(npc);
    }
    D_800AA248.cur_obj = saved;
}

void func_80034898(UnkStructB1 *npc) {
    u16 n = npc->unk_1C;
    GameObject *mover;

    if (n != 0) {
        npc->unk_1C = n - 1;
        return;
    }
    mover = npc->unk_40;
    if (mover != NULL) {
        func_8001E4B0(mover);
        npc->unk_40 = NULL;
    }
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    npc->unk_1C = 0x3B6;
    D_800AA248.cur_obj->pos_y.w = 0x02000000;
    func_8003C080();
}

void func_80034924(UnkStructB1 *npc) {
    func_8001F724(0x60);
    if (!((D_800AA248.cur_obj->flags ^ npc->unk_44) & 0x10)) {
        func_80034988(npc);
        return;
    }
    func_800345F8(npc);
}

void func_80034988(UnkStructB1 *npc) {
    void (*handler)(void) = D_8007D558[npc->unk_06 - 1];

    if (handler == NULL) {
        func_800345F8(npc);
        return;
    }
    handler();
}

void func_800349E0(UnkStructB1 *npc) {
    void (*handler)(void) = D_8007D5A4[npc->unk_06 - 1];

    if (handler == NULL) {
        func_800345F8(npc);
        return;
    }
    handler();
}

void func_80034A38(UnkStructB1 *npc) {
    func_80034B68(0x30000);
    D_800AA248.cur_obj->vel_y.w = -0xB0000;
    D_800AA248.cur_obj->pos_x.w += D_800AA248.cur_obj->vel_x.w;
    D_800AA248.cur_obj->priority = 0x4000;
    npc->unk_08 = 6;
    func_8003EB5C(D_8008A4F4, D_800AA248.cur_obj);
}

void func_80034AB4(UnkStructB1 *npc) {
    s32 speed;

    D_800AA248.cur_obj->pos_x.w += D_800AA248.cur_obj->vel_x.w;
    speed = D_800AA248.cur_obj->vel_y.w + 0x6500;
    if (speed > 0x80000) {
        speed = 0x80000;
    }
    D_800AA248.cur_obj->vel_y.w = speed;
    D_800AA248.cur_obj->pos_y.w += speed;
    if (D_800AA248.cur_obj->vel_y.w >= 0 && ((s16 *)&D_800AA248.cur_obj->pos_y.w)[1] >= 0xE2) {
        func_800345F8(npc);
    }
}

void func_80034B68(s32 speed) {
    if (D_800AA248.cur_obj->flags & 0x10) {
        speed = -speed;
    }
    D_800AA248.cur_obj->vel_x.w = speed;
}

void func_80034B94(UnkStructB1 *npc) {
    D_800AA248.cur_obj = npc->unk_00;
    switch (npc->unk_08) {
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
    ((u16 *)&D_800AA248.cur_obj->pos_y.w)[1] -= 0x14;
}

void func_80034C54(GameObject *mover) {
    mover->anim = (s32) D_8007D45C[mover->unk_68.u.lo];
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
    slot = D_800AA248.cur_obj->unk_68.u.hi + 1;
    if (slot < 3) {
        GameObject *mover = D_801FB44C[slot];

        if (mover != NULL) {
            func_80034C54(mover);
            D_801FB44C[slot] = NULL;
        }
    }
}

void func_80034D28(UnkStructB1 *npc) {
    func_8001F724(0x60);
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    npc->unk_08 = 4;
    npc->unk_0C = 0;
    if (npc->unk_06 == 0x17) {
        func_8003EB5C(D_8008A5A8, D_800AA248.cur_obj);
    } else {
        func_8003EB5C(D_8008A62C, D_800AA248.cur_obj);
    }
}

void func_80034DAC(UnkStructB1 *npc) {
    ObjectDef *effect;

    if (npc->unk_0C != 0) {
        func_8001F724(5);
        effect = func_8001D110();
        D_800AA248.new_def = effect;
        effect->pos_x.s.hi = ((u16 *)&D_800AA248.cur_obj->pos_x.w)[1];
        effect->pos_y.s.hi = ((u16 *)&D_800AA248.cur_obj->pos_y.w)[1] - 0x14;
        effect->anim = &D_8008A7A4;
        effect->flags = (u16)D_800AA248.cur_obj->priority + 1;
        effect->id = D_8008A7A4.id;
        func_8001DCB4();
        func_8003C080();
    }
}

/* 86.73%: the three spawned movers are right; the prologue's setup order, the loop counters' increments (placed before the mask load here, after the store in the original) and the register of the 0x17 constant at the end differ */
#ifdef NON_MATCHING
void func_80034E48(UnkStructB1 *npc) {
    GameObject *mover;
    GameObject **slot;
    GameObject *spawned;
    ObjectDef *effect;
    Anim *def;
    s32 kind;
    s32 i;
    s32 n;
    s32 step;
    s32 offset;

    i = 0;
    n = 1;
    mover = D_800AA248.cur_obj;
    slot = D_801FB44C;
    do {
        kind = 4;
        if (npc->unk_06 != 0x17) {
            kind = func_8001EA78() & 3;
        }
        def = D_8007D448[kind];
        effect = func_8001D110();
        D_800AA248.new_def = effect;
        effect->anim = def;
        effect->id = def->id;
        effect->flags = (u16)mover->priority;
        spawned = func_8001DCB4();
        *slot = spawned;
        spawned->flags = mover->flags;
        spawned->kind = 0x71A;
        spawned->unk_68.w = (i << 16) | kind;
        step = 0x68;
        if (npc->unk_06 == 0x17) {
            step = 0x64;
        }
        if (mover->flags & 0x10) {
            offset = n * step;
        } else {
            offset = n * -step;
        }
        ((s16 *)&spawned->pos_x.w)[1] = (((u16 *)&mover->pos_x.w)[1] + offset) & (D_801D8864.w >> 16);
        ((u16 *)&spawned->pos_y.w)[1] = ((u16 *)&mover->pos_y.w)[1];
        n++;
        i++;
        slot++;
    } while (i < 3);
    D_800AA268.p = mover;
    if (npc->unk_06 == 0x17) {
        mover->vel_x.w = 0x50000;
    } else {
        mover->vel_x.w = 0x20000;
    }
    if (D_800AA248.cur_obj->flags & 0x10) {
        D_800AA248.cur_obj->vel_x.w = -D_800AA248.cur_obj->vel_x.w;
    }
    if (npc->unk_06 == 0x17) {
        func_8003EB5C(D_8008A59C, D_800AA248.cur_obj);
    } else {
        func_8003EB5C(D_8008A620, D_800AA248.cur_obj);
    }
    npc->unk_08 = 2;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80034E48);
#endif

void func_80035040(void) {
    s32 i;

    D_800AA248.cur_obj->pos_x.w = (D_800AA248.cur_obj->pos_x.w + D_800AA248.cur_obj->vel_x.w) & D_801D8864.w;
    for (i = 0; i < 3; i++) {
        GameObject *mover = D_801FB44C[i];

        if (mover != NULL) {
            mover->pos_x.w = (mover->pos_x.w + D_800AA248.cur_obj->vel_x.w) & D_801D8864.w;
        }
    }
}

void func_800350C0(UnkStructB1 *npc) {
    GameObject *mover;
    u16 action;

    mover = npc->unk_00;
    D_800AA268.p = mover;
    mover->pos_y.w = 0x320000;
    action = npc->unk_08;
    if (action == 0x64) {
        func_80035260();
    } else if (action == 3) {
        func_800352A0(npc);
    } else if (action == 4) {
        func_80035330(npc);
    } else if (action == 1) {
        func_8003518C(npc);
    } else if (func_8003BE34(npc) == 1) {
        npc->unk_08 = 0x64;
        npc->unk_1C = 0x2EE;
        func_800242A8();
    }
}

void func_8003518C(UnkStructB1 *npc) {
    u16 n = npc->unk_1C;

    if (n == 0) {
        func_800351CC(npc);
        return;
    }
    npc->unk_1C = n - 1;
    func_800242A8();
}

void func_800351CC(UnkStructB1 *npc) {
    npc->unk_06 = 0x1B;
    npc->unk_3E = 0;
    D_800AA248.cur_obj->pos_x.w = D_801F9AC8.w - 0x19A0000;
    D_800AA248.cur_obj->pos_y.w = 0x320000;
    if (!(D_800AA248.cur_obj->flags & 0x10)) {
        D_800AA248.cur_obj->vel_x.w = 0x50000;
    } else {
        D_800AA248.cur_obj->vel_x.w = -0x50000;
    }
    npc->unk_08 = 2;
    func_8003EB5C(D_8008A488, D_800AA248.cur_obj);
}

void func_80035260(UnkStructB1 *npc) {
    u16 n = npc->unk_1C;

    if (n == 0) {
        func_800351CC(npc);
        return;
    }
    npc->unk_1C = n - 1;
    func_800242A8();
}

void func_800352A0(UnkStructB1 *npc) {
    func_8001F724(5);
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    D_800AA248.cur_obj->priority = 0x4000;
    npc->unk_08 = 4;
    npc->unk_1C = 0xF;
    func_8003EB5C(D_8008A448, D_800AA248.cur_obj);
    func_800215C0(((s16 *)&D_800AA248.cur_obj->pos_x.w)[1], ((s16 *)&D_800AA248.cur_obj->pos_y.w)[1]);
}

void func_80035330(UnkStructB1 *npc) {
    if (npc->unk_0C != 0) {
        npc->unk_1C = 0x384;
        npc->unk_08 = 0x64;
        func_800242A8();
        func_8003EB5C(D_8008A47C, D_800AA248.cur_obj);
    }
}

void func_8003537C(UnkStructB1 *npc) {
    D_800AA248.cur_obj = npc->unk_00;
    if (npc->unk_06 == 0x15) {
        func_80034418();
    }
    switch (npc->unk_08) {
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
            npc->unk_08 = 0x64;
            npc->unk_1C = 0x2EE;
            func_800242A8();
        }
        return;
    }
}

void func_80035464(UnkStructB1 *npc) {
    u16 n = npc->unk_1C;

    if (n == 0) {
        func_800354A4();
        return;
    }
    npc->unk_1C = n - 1;
    func_800242A8();
}

void func_800354A4(npc)
    UnkStructB1 *npc;
{
    npc->unk_3E = 0;
    D_800AA248.cur_obj->pos_x.w = D_801F9AC8.w - 0x19A0000;
    D_800AA248.cur_obj->pos_y.w = 0x320000;
    if (!(D_800AA248.cur_obj->flags & 0x10)) {
        D_800AA248.cur_obj->vel_x.w = 0x50000;
    } else {
        D_800AA248.cur_obj->vel_x.w = -0x50000;
    }
    npc->unk_08 = 2;
    if (npc->unk_06 == 0x15) {
        func_8003EB5C(D_8008AA40, D_800AA268.p);
    } else {
        func_8003EB5C(D_8008AA34, D_800AA268.p);
    }
}

void func_80035550(UnkStructB1 *npc) {
    u16 n = npc->unk_1C;

    if (n == 0) {
        func_800354A4();
        return;
    }
    npc->unk_1C = n - 1;
    func_800242A8();
}

void func_80035590(UnkStructB1 *npc) {
    func_8001F724(5);
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    D_800AA248.cur_obj->priority = 0x4000;
    npc->unk_08 = 4;
    npc->unk_1C = 0xF;
    func_8003EB5C(D_8008A9D4, D_800AA248.cur_obj);
    func_800215C0(((s16 *)&D_800AA248.cur_obj->pos_x.w)[1], ((s16 *)&D_800AA248.cur_obj->pos_y.w)[1]);
}

void func_80035620(UnkStructB1 *npc) {
    if (npc->unk_0C != 0) {
        npc->unk_1C = 0x384;
        npc->unk_08 = 0x64;
        func_800242A8();
        func_8003EB5C(D_8008AA10, D_800AA248.cur_obj);
    }
}

void func_8003566C(UnkStructB1 *npc) {
    D_800AA248.cur_obj = npc->unk_00;
    switch (npc->unk_08) {
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
        switch (npc->unk_0A) {
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
            D_800AA248.cur_obj->pos_x.w += D_800AA248.cur_obj->vel_x.w;
            if (D_800AA248.cur_obj->vel_x.w > 0) {
                if (((s16 *)&D_800AA248.cur_obj->pos_x.w)[1] <= D_801D376C) {
                    return;
                }
            } else {
                if (((s16 *)&D_800AA248.cur_obj->pos_x.w)[1] >= D_801D87B0) {
                    return;
                }
            }
            D_800AA248.cur_obj->vel_x.w = 0;
            D_800AA248.cur_obj->vel_y.w = 0x4000;
            npc->unk_0A = 3;
            npc->unk_1C = 1;
            func_8003EB5C(D_8008A938, D_800AA248.cur_obj);
            return;
        }
    }
}

void func_8003585C(UnkStructB1 *npc) {
    D_800AA248.cur_obj->pos_y.w += D_800AA248.cur_obj->vel_y.w;
    if (npc->unk_1C == 0) {
        npc->unk_0A = 1;
        D_800AA248.cur_obj->vel_y.w = 0x4000;
        func_8003EB5C(D_8008A9B0, D_800AA248.cur_obj);
    }
}

void func_800358C8(UnkStructB1 *npc) {
    D_800AA248.cur_obj->pos_y.w += D_800AA248.cur_obj->vel_y.w;
    if (D_800AA248.cur_obj->pos_y.w > 0x153FFFF) {
        func_80035A88(npc);
    }
}

void func_80035928(UnkStructB1 *npc) {
    D_800AA248.cur_obj->pos_y.w += D_800AA248.cur_obj->vel_y.w;
    if (D_800AA248.cur_obj->pos_y.w <= 0xFA0000) {
        npc->unk_0A = 2;
        npc->unk_1C = 1;
        func_8003EB5C(D_8008A968, D_800AA248.cur_obj);
    }
}

void func_8003599C(UnkStructB1 *npc) {
    D_800AA248.cur_obj->pos_y.w += D_800AA248.cur_obj->vel_y.w;
    if (D_800AA248.cur_obj->pos_y.w <= 0xF00000) {
        D_800AA248.cur_obj->pos_y.w = 0xF00000;
    }
    if (npc->unk_1C == 0) {
        npc->unk_0A = 4;
        D_800AA248.cur_obj->vel_x.w = (u16)npc->unk_20 == 0 ? 0x8000 : -0x8000;
        D_800AA248.cur_obj->vel_y.w = 0;
        func_8003EB5C(D_8008A914, D_800AA248.cur_obj);
    }
}

void func_80035A3C(UnkStructB1 *npc) {
    u16 n;

    D_800AA248.cur_obj->pos_y.w = 0x01900000;
    n = npc->unk_1C;
    if (n == 0) {
        func_80035A88(npc);
        return;
    }
    npc->unk_1C = n - 1;
}

void func_80035A88(UnkStructB1 *npc) {
    u8 *anim;

    npc->unk_0A = 0;
    npc->unk_20 = (npc->unk_20 + 1) & 1;
    if (npc->unk_20 == 0) {
        anim = D_8008A998;
        ((s16 *)&D_800AA248.cur_obj->pos_x.w)[1] = D_801D87B0 + 0xA;
    } else {
        anim = D_8008A9A4;
        ((s16 *)&D_800AA248.cur_obj->pos_x.w)[1] = D_801D376C - 0xA;
    }
    D_800AA248.cur_obj->pos_y.w = 0x01540000;
    D_800AA248.cur_obj->vel_y.w = -0x8000;
    npc->unk_08 = 2;
    func_8003EB5C(anim, D_800AA248.cur_obj);
}

void func_80035B30(UnkStructB1 *npc) {
    u16 n = npc->unk_1C;

    if (n == 0) {
        func_80035A88(npc);
        return;
    }
    npc->unk_1C = n - 1;
}

void func_80035B6C(UnkStructB1 *npc) {
    func_8001F724(5);
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    D_800AA248.cur_obj->priority = 0x1300;
    npc->unk_08 = 4;
    npc->unk_1C = 0x12;
    func_8003EB5C(D_8008AA28, D_800AA248.cur_obj);
    func_8004BFE0();
}

void func_80035BE8(UnkStructB1 *npc) {
    u16 n = npc->unk_1C;

    if (n == 0) {
        npc->unk_1C = 0xBE;
        npc->unk_08 = 0x33;
        D_800AA248.cur_obj->pos_x.w = 0x02000000;
        D_800AA248.cur_obj->pos_y.w = 0x02000000;
        func_8003C080(0x02000000);
        return;
    }
    npc->unk_1C = n - 1;
}

void func_80035C4C(UnkStructB1 *npc) {
    D_800AA248.cur_obj = npc->unk_00;
    switch (npc->unk_08) {
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
        if (D_800AA248.cur_obj->vel_x.w > 0) {
            D_800AA248.cur_obj->pos_x.w += D_800AA248.cur_obj->vel_x.w;
            if (((s16 *)&D_800AA248.cur_obj->pos_x.w)[1] > D_801D376C) {
                D_800AA248.cur_obj->vel_x.w = -0x6000;
                D_800AA248.cur_obj->flags |= 0x10;
            }
        } else {
            D_800AA248.cur_obj->pos_x.w += D_800AA248.cur_obj->vel_x.w;
            if (((s16 *)&D_800AA248.cur_obj->pos_x.w)[1] < D_801D87B0) {
                D_800AA248.cur_obj->vel_x.w = 0x6000;
                D_800AA248.cur_obj->flags &= ~0x10;
            }
        }
        return;
    }
}

void func_80035DC0(UnkStructB1 *npc) {
    u16 n = npc->unk_1C;

    if (n == 0) {
        func_80035DFC(npc);
        return;
    }
    npc->unk_1C = n - 1;
}

void func_80035DFC(UnkStructB1 *npc) {
    ((s16 *)&D_800AA248.cur_obj->pos_x.w)[1] = D_801D87B0 + 0x20;
    D_800AA248.cur_obj->pos_y.w = 0xF00000;
    D_800AA248.cur_obj->vel_x.w = 0x6000;
    npc->unk_08 = 2;
    if (npc->unk_06 == 0x1C) {
        func_8003EB5C(D_8008A908, D_800AA248.cur_obj);
    } else {
        func_8003EB5C(D_8008A8DC, D_800AA248.cur_obj);
    }
}

void func_80035E80(UnkStructB1 *npc) {
    u16 n = npc->unk_1C;

    if (n == 0) {
        func_80035DFC(npc);
        return;
    }
    npc->unk_1C = n - 1;
}

void func_80035EBC(UnkStructB1 *npc) {
    Monster *player;

    if (npc->unk_06 == 0x1C) {
        func_8001F724(5);
        D_800AA248.cur_obj->vel_x.w = 0;
        D_800AA248.cur_obj->vel_y.w = 0;
        D_800AA248.cur_obj->priority = 0x1300;
        npc->unk_08 = 4;
        npc->unk_1C = 0x12;
        func_8004BFE0();
        return;
    }
    player = npc->unk_54;
    player->action = 8;
    npc->unk_1C = 0x12;
    func_80053D68(0x28000, player);
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    ((s16 *)&D_800AA248.cur_obj->pos_y.w)[1] = 0x1F4;
    npc->unk_08 = 4;
}

void func_80035F8C(UnkStructB1 *npc) {
    u16 n = npc->unk_1C;

    if (n == 0) {
        npc->unk_1C = 0xBE;
        npc->unk_08 = 0x33;
        D_800AA248.cur_obj->pos_y.w = 0x02000000;
        D_800AA248.cur_obj->pos_x.w = 0x02000000;
        func_8003C080(0x02000000);
        return;
    }
    npc->unk_1C = n - 1;
}

void func_80035FF0(void) {
    s32 r = func_80036028();

    D_800AA248.cur_obj->vel_x.w = (r < 0) ? -0x20000 : 0x20000;
}

s32 func_80036028(void) {
    if (func_8001EB10(0xFF, 0) & 1) {
        D_800AA248.cur_obj->flags |= 0x10;
        D_800AA248.cur_obj->pos_x.w = D_801F9AC8.w + 0x2440000;
        D_800AA248.cur_obj->vel_x.w = -0x32000;
    } else {
        D_800AA248.cur_obj->flags &= ~0x10;
        D_800AA248.cur_obj->pos_x.w = D_801F9AC8.w - 0x19A0000;
        D_800AA248.cur_obj->vel_x.w = 0x32000;
    }
    return D_800AA248.cur_obj->vel_x.w;
}

void func_800360D8(UnkStructB1 *npc) {
    Monster *m;
    GameObject *obj;
    s16 d;
    s32 speed;
    u16 i;

    i = 7;
    if (D_800AA248.cur_obj->vel_x.w != 0) {
        if (npc->unk_06 >= 0xD && npc->unk_40 != NULL) {
            npc->unk_40->pos_x.u.hi = D_800AA248.cur_obj->pos_x.u.hi;
        }
        if (npc->unk_0A == 0) {
            func_8003BD48(npc);
            func_8003BE34(npc);
        }
        return;
    }
    do {
        m = &D_801E0B78[i];
        if ((m->unk_058 & 1) && m->unk_1DE != 0) {
            obj = m->obj;
            if (obj->pos_y.s.hi >= 0) {
                d = abs(D_800AA248.cur_obj->pos_x.s.hi - obj->pos_x.s.hi);
                if (((s16)D_800AA248.cur_obj->size.u.lo >> 2) + 0x10 >= d) {
                    if (npc->unk_06 < 0x14) {
                        speed = D_8007D470[npc->unk_06 - 1];
                    } else {
                        speed = 0x38000;
                    }
                    if (D_800AA248.cur_obj->flags & 0x10) {
                        speed = -speed;
                    }
                    D_800AA248.cur_obj->vel_x.w = speed;
                    func_8001F7CC(0x32, 0x4C);
                    return;
                }
            }
        }
    } while (--i != 0);
}

void func_80036298(void) {
    NpcS *npc = D_801FAC9C;
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

void func_80036300(NpcS *npc) {
    D_800AA268.p = npc->unk_0;
    func_80029D1C();
    func_80036818(npc);
    switch (npc->unk_6) {
    case 3:
        func_8004BBC8(npc);
        break;
    case 0x3B:
        func_80037A88(npc);
        break;
    case 0x3E:
    case 0x3F:
        func_80037F20(npc);
        break;
    case 0xF:
        func_80038348(npc);
        break;
    case 0x11:
    case 0x12:
        func_80020DDC(npc);
        break;
    case 0x31:
        func_8003A98C(npc);
        break;
    case 0x13:
        func_8003B294(npc);
        break;
    case 0x14:
    case 0x15:
        func_8003B3C8(npc);
        break;
    case 0x42:
        break;
    }
}

void func_800363E4(void) {
    NpcS *npc = D_801FAC9C;
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
void func_80036440(NpcS *npc, s32 depth) {
    GameObject *mover;
    ObjectDef *effect;
    s32 d;

    mover = func_8001EB9C(0, 0, 0, 0, 0xFFFFFF);
    mover->unk_40.w = -0x3E7;
    d = depth - 1;
    mover->priority = d;
    mover->flags = (mover->flags & ~0x20) | 0x400;
    mover->unk_6C |= 0x2000;
    npc->unk_70 = mover;
    func_8001BB68(mover);
    effect = func_8001D110();
    effect->id = 0x4F000986;
    effect->flags = d;
    D_800AA284 = effect;
    mover = func_8001DCB4();
    mover->flags |= 0x400;
    npc->unk_74 = mover;
    func_8001BB68(mover);
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80036440);
#endif

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80036504);

void func_80036818(NpcS *npc) {
    GameObject *a = npc->unk_70;
    GameObject *b = npc->unk_0;
    GameObject *c = npc->unk_74;

    if (a != NULL) {
        func_80036504(a, b, c);
    }
}

void func_8003684C(void) {
    SpawnItem *item;
    NpcS *npc;
    GameObject *obj;
    ObjectDef *def;
    Anim *anim;
    u16 n;

    func_800363E4();
    item = (SpawnItem *)func_80025C08(D_8007DA48);
    n = item->unk_04;
    item++;
    if (n == 0) {
        return;
    }
    if (n > 6) {
        n = 6;
    }
    npc = D_801FAC9C;
    D_801D8730 = n;
    do {
        D_800AA248.new_def = func_8001D110();
        def = D_800AA248.new_def;
        anim = item->anim;
        def->anim = anim;
        def->id = anim->id;
        npc->unk_A = 0;
        npc->unk_8 = 1;
        npc->unk_6 = item->unk_04;
        obj = func_8001DCB4();
        npc->unk_0 = obj;
        obj->owner.p = npc;
        obj->pos_x.u.hi = item->unk_06;
        obj->pos_y.u.hi = item->unk_08;
        obj->flags |= item->unk_0A;
        obj->priority = item->unk_0C;
        obj->kind = 0x713;
        if (item->unk_0E == -1) {
            npc->unk_1C = func_8001EB10(0xC8, 0x64);
        } else {
            npc->unk_1C = item->unk_0E;
        }
        if (npc->unk_6 == 0x11 || npc->unk_6 == 0x12) {
            func_80036440(npc, item->unk_0C);
        } else {
            obj->priority = obj->pos_y.u.hi + 0xF23;
        }
        item++;
        npc++;
    } while (--n != 0);
}

void func_800369F8(NpcS *npc) {
    memset(npc, 0, sizeof(NpcS));
    D_801D8730 = 0;
}

/* 99.61%: the live count and the constant 1 swap saved registers (s4 and s3 in the original) */
#ifdef NON_MATCHING
void func_80036A20(Monster *player) {
    u16 n;
    NpcS *npc;
    GameObject *mover;
    u16 kind;

    n = D_801D8730;
    npc = D_801FAC9C;
    if (n == 0) {
        return;
    }
    do {
        kind = npc->unk_6;
        mover = npc->unk_0;
        if (kind == 0x31 || kind == 0x13 || kind == 0x14 || (kind == 0x15 && npc->unk_8 != 0x63)) {
            if (func_8003B9C8(mover, player) != 0) {
                func_80037078(player, npc);
                return;
            }
        } else if (!(mover->unk_6C & 0x80) && (npc->unk_8 == 0x32 || npc->unk_8 == 2 || npc->unk_8 == 0x1E)) {
            switch (npc->unk_6) {
            case 0x3E:
            case 0x3F:
                if (npc->unk_8 != 0x1E && (u16)player->action != 4) {
                    if (func_80036C30(player, npc, mover, 0x1E) != 1) {
                        break;
                    }
                    if (npc->unk_8 == 0x1E) {
                        func_8005E0E8(player);
                        func_80053D68(8, player);
                        if (player->obj->pos_y.s.hi == 0xE1) {
                            player->action = 8;
                        }
                    }
                    return;
                }
                /* fallthrough */
            case 3:
            case 0xF:
            case 0x3B:
            case 0x3C:
            case 0x42:
                if (func_80036FD0((s16)player->pos.u.lo, (s16)player->pos.u.hi, mover) == 1) {
                    func_80037078(player, npc);
                    return;
                }
                break;
            case 0x11:
            case 0x12:
                if (func_80036C30(player, npc, mover, 0x14) == 1) {
                    return;
                }
                break;
            }
        }
        npc++;
    } while (--n != 0);
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80036A20);
#endif

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80036C30);

u16 func_80036FD0(s16 x, s16 y, GameObject *mover) {
    u16 pos;
    s32 dx;
    s32 dy;
    s32 half;
    u16 w;

    pos = ((s16 *)&mover->pos_x.w)[1];
    if ((s16)pos < D_801F9AC8.s.hi) {
        pos += (D_801D8864.w + 1) >> 16;
    }
    w = mover->size.u.lo;
    dx = abs((s16)(pos - x));
    if (((s16)w >> 1) >= dx) {
        pos = ((u16 *)&mover->pos_y.w)[1];
        half = (s16)mover->size.u.hi >> 1;
        dy = abs((s16)(pos - half - y));
        if (dy <= half + 4) {
            return 1;
        }
    }
    return 0;
}

void func_80037078(Monster *player, NpcS *npc) {
    player->unk_024++;
    func_80054374(0x28, player);
    func_800634D4(player, 4);
    npc->unk_8 = 3;
    npc->unk_60 = player;
    npc->unk_54 = D_800AA248.cur_obj->flags;
    npc->unk_5C = player->pos.u.lo;
    npc->unk_5E = player->pos.u.hi;
    if (player->unk_142 != 0) {
        npc->unk_1A += 0xA;
    }
    player->unk_18A = 1;
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_8003712C);

#ifdef NON_MATCHING
/* 99.85 %: the control flow and the saved registers are right; the first rectangle's x tests load the field into v1 (a0 in the original) */
u16 func_800372DC(s16 x, s16 y, Monster *player, NpcS *npc, s32 arg4) {
    func_80037960(npc, arg4);
    if ((x >= npc->unk_3E || x >= (s16)(npc->unk_3E - 4)) && (x <= npc->unk_40 || x <= (s16)(npc->unk_40 + 4)) &&
        (y >= npc->unk_44 || y >= (s16)(npc->unk_44 - 4)) && (y <= npc->unk_42 || y <= (s16)(npc->unk_42 + 4))) {
        goto hit;
    }
    if (x < npc->unk_46 && x < (s16)(npc->unk_46 - 4)) return 0;
    if (x > npc->unk_48 && x > (s16)(npc->unk_48 + 4)) return 0;
    if (y < npc->unk_4C && y < (s16)(npc->unk_4C - 4)) return 0;
    if (y > npc->unk_4A && y > (s16)(npc->unk_4A + 4)) return 0;
    if (player != NULL) {
        player->unk_024++;
        func_80054374(0x28, player);
        func_800634D4(player, 4);
    }
hit:
    return func_8003761C(x, y, player, npc);
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_800372DC);
#endif

u16 func_800374FC(s16 x, s16 y, NpcS *npc, GameObject *arg3) {
    MoverTarget *target = D_800AA248.cur_obj->unk_94.target;

    if (target != NULL) {
        NpcS *other = target->unk_4->owner.p;
        if (other != npc && other->unk_A != 2) {
            return func_80037574(x, y, arg3);
        }
    }
    return 0;
}

u16 func_80037574(s16 x, s16 y, GameObject *mover) {
    u16 pos;
    s32 dx;
    s32 dy;
    s32 half;
    u16 w;

    pos = ((s16 *)&mover->pos_x.w)[1];
    if ((s16)pos < D_801F9AC8.s.hi) {
        pos += (D_801D8864.w + 1) >> 16;
    }
    w = mover->size.u.lo;
    dx = abs((s16)(pos - x));
    if (((s16)w >> 1) >= dx) {
        pos = ((u16 *)&mover->pos_y.w)[1];
        half = (s16)mover->size.u.hi >> 1;
        dy = abs((s16)(pos - half - y));
        if (dy <= half + 4) {
            return 1;
        }
    }
    return 0;
}

u16 func_8003761C(s16 x, s16 y, Monster *player, NpcS *npc) {
    if (player == NULL) {
        return 0;
    }
    player->unk_024++;
    func_80054374(0x28, player);
    func_800634D4(player, 4);
    npc->unk_8 = 3;
    npc->unk_60 = player;
    npc->unk_54 = D_800AA248.cur_obj->flags;
    npc->unk_5C = x;
    npc->unk_5E = y;
    D_800AA248.cur_obj->unk_98 = npc;
    npc->unk_1A += 0xA;
    return 1;
}

void func_800376D8(void) {
}

#ifdef NON_MATCHING
/* 82.2 %: the twin of func_8003BD48 (game_8003B568), with the same difference: the original tests the loaded limit in v0 and copies it into a1, where every form tried loads it straight into one register */
void func_800376E0(NpcS *npc) {
    s32 limit;
    u16 x;
    u16 d;

    if (npc->unk_8 == 2) {
        limit = D_801FAC84;
        if (D_801FAC84 != 0) {
            x = D_800AA268.p->pos_x.u.hi;
            if (!(D_800AA268.p->flags & 0x10)) {
                d = limit - x;
            } else {
                d = (u16) D_801F9AB0 - x + 0x31;
            }
            if (d < 0x32) {
                npc->unk_A = 1;
            }
        } else if (D_801D37BC == 0) {
            limit = (s16)D_801FA98C;
            if ((s16)D_801FA98C != 0) {
                x = D_800AA268.p->pos_x.u.hi;
                if (!(D_800AA268.p->flags & 0x10)) {
                    d = limit - x;
                } else {
                    d = D_801FA990 - x + 0x31;
                }
                if (d < 0x32) {
                    npc->unk_A = 1;
                }
            }
        }
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_800376E0);
#endif

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_800377B4);

void func_80037960(NpcS *npc, GameObject *obj) {
    s16 x;
    u16 y;
    SpriteFrame *f;
    s16 a;
    s16 b;
    u16 v;
    u16 h;

    x = obj->pos_x.s.hi;
    if (x < D_801F9ACA) {
        x += (D_801D8864.w + 1) >> 16;
    }
    f = obj->frame;
    y = obj->pos_y.u.hi;
    v = f->unk_10;
    h = f->unk_12;
    if (obj->flags & 0x10) {
        v = -v;
    }
    a = v + x;
    npc->unk_3E = a;
    npc->unk_44 = h + y;
    v = f->unk_14;
    h = f->unk_16;
    if (obj->flags & 0x10) {
        v = -v;
    }
    b = v + x;
    npc->unk_40 = b;
    npc->unk_42 = h + y;
    if (obj->flags & 0x10) {
        npc->unk_40 = a;
        npc->unk_3E = b;
    }
    v = f->unk_18;
    h = f->unk_1A;
    if (obj->flags & 0x10) {
        v = -v;
    }
    a = v + x;
    npc->unk_46 = a;
    npc->unk_4C = h + y;
    v = f->unk_1C;
    h = f->unk_1E;
    if (obj->flags & 0x10) {
        v = -v;
    }
    b = v + x;
    npc->unk_48 = b;
    npc->unk_4A = h + y;
    if (obj->flags & 0x10) {
        npc->unk_48 = a;
        npc->unk_46 = b;
    }
}

void func_80037A88(NpcS *npc) {
    D_800AA248.cur_obj = npc->unk_0;
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
    D_800AA248.cur_obj->vel_x.w = D_801F9AC8.w - 0x19A0000;
    D_800AA248.cur_obj->vel_y.w = 0;
}

void func_80037C1C(NpcS *npc) {
    if (npc->unk_1C != 0) {
        npc->unk_1C--;
        D_800AA248.cur_obj->pos_y.w = 0x01900000;
        return;
    }
    func_80035FF0();
    func_800380C0(D_800AA248.cur_obj);
    npc->unk_8 = 2;
    npc->unk_22 = 0;
    func_8003EB5C(D_8008A374, D_800AA248.cur_obj);
}

void func_80037CA0(NpcS *npc) {
    if ((D_800AA248.cur_obj->flags ^ npc->unk_54) & 0x10) {
        func_80037E1C(npc);
        return;
    }
    func_80037CF4(npc);
}

void func_80037CF4(NpcS *npc) {
    func_80034B68(0x58000);
    D_800AA248.cur_obj->vel_y.w = -0x65529;
    D_800AA248.cur_obj->pos_x.w += D_800AA248.cur_obj->vel_x.w;
    D_800AA248.cur_obj->priority = 0x4000;
    npc->unk_8 = 0xD;
    func_8003EB5C(D_8008A398, D_800AA248.cur_obj);
}

void func_80037D78(NpcS *npc) {
    D_800AA248.cur_obj->pos_x.w += D_800AA248.cur_obj->vel_x.w;
    D_800AA248.cur_obj->vel_y.w += 0x6000;
    D_800AA248.cur_obj->pos_y.w += D_800AA248.cur_obj->vel_y.w;
    if (D_800AA248.cur_obj->vel_y.w >= 0 && D_800AA248.cur_obj->pos_y.w > 0xE10000) {
        func_80037E1C(npc);
    }
}

void func_80037E1C(NpcS *npc) {
    func_8001F724(5);
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    npc->unk_8 = 4;
    npc->unk_1C = 3;
    func_80034670();
}

void func_80037E78(NpcS *npc) {
    if (npc->unk_1C != 0) {
        npc->unk_1C--;
        return;
    }
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    npc->unk_8 = 0x33;
    D_800AA248.cur_obj->pos_y.w = 0x02000000;
    func_8003831C();
}

void func_80037EE0(NpcS *npc) {
    npc->unk_A = 0;
    D_800AA248.cur_obj->vel_x.w = -D_800AA248.cur_obj->vel_x.w;
    D_800AA248.cur_obj->flags ^= 0x10;
}

void func_80037F20(NpcS *npc) {
    D_800AA248.cur_obj = npc->unk_0;
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
    D_800AA248.cur_obj->pos_x.w = D_801F9AC8.w - 0x19A0000;
    D_800AA248.cur_obj->vel_y.w = 0;
}

void func_800380C0(GameObject *mover) {
    if (!(mover->flags & 0x10)) {
        mover->pos_y.w = 0xEB0000;
    } else {
        mover->pos_y.w = 0xE30000;
    }
    mover->priority = ((u16 *)&mover->pos_y.w)[1] + 0xF23;
}

void func_800380F0(NpcS *npc) {
    if (npc->unk_1C != 0) {
        npc->unk_1C--;
        D_800AA248.cur_obj->pos_y.w = 0x01900000;
        return;
    }
    func_80035FF0();
    func_800380C0(D_800AA248.cur_obj);
    npc->unk_8 = 2;
    npc->unk_22 = 0;
    if (npc->unk_6 == 0x3E) {
        func_8003EB5C(D_8008A3E0, D_800AA248.cur_obj);
    } else {
        func_8003EB5C(D_8008A414, D_800AA248.cur_obj);
    }
}

void func_80038198(NpcS *npc) {
    if (npc->unk_6 == 0x3E) {
        func_8003EB5C(D_8008A408, D_800AA248.cur_obj);
    } else {
        func_8003EB5C(D_8008A43C, D_800AA248.cur_obj);
    }
}

void func_800381E4(NpcS *npc) {
    func_8001F724(5);
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    npc->unk_8 = 4;
    npc->unk_1C = 3;
    func_80034670();
}

void func_80038240(NpcS *npc) {
    if (npc->unk_1C != 0) {
        npc->unk_1C--;
        return;
    }
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    npc->unk_8 = 0x33;
    D_800AA248.cur_obj->pos_y.w = 0x02000000;
    func_8003831C();
}

void func_800382A8(NpcS *npc) {
    npc->unk_A = 0;
    D_800AA248.cur_obj->vel_x.w = -D_800AA248.cur_obj->vel_x.w;
    D_800AA248.cur_obj->flags ^= 0x10;
}

void func_800382E8(void) {
    ((NpcS *)D_800AA248.cur_obj->owner.ai)->unk_1C = 0;
}

void func_80038300(void) {
    ((NpcS *)D_800AA248.cur_obj->owner.ai)->unk_C = 1;
}

void func_8003831C(void) {
    ((NpcS *)D_800AA248.cur_obj->owner.ai)->unk_6 = 0;
    func_8004CFC0();
}

void func_80038348(NpcS *npc) {
    D_800AA268.p = npc->unk_0;
    func_80020D20();
    switch (npc->unk_8) {
    case 1:
    case 0x3B:
        func_800383F4(npc);
        break;
    case 3:
        func_80038494(npc);
        break;
    case 4:
        func_80038800(npc);
        break;
    case 2:
        func_80038AE8(npc);
        break;
    case 0x32:
        func_800384E8(npc);
        break;
    }
}

void func_800383F4(NpcS *npc) {
    if (npc->unk_1C == 0) {
        if (func_80039C40(D_800AA248.cur_obj->pos_x.w, -0x280000, -0x280000) == 0) {
            npc->unk_6 = 0xF;
            npc->unk_8 = 2;
            func_8003EB5C(D_80095EF0, D_800AA248.cur_obj);
            func_8001BB88(D_800AA248.cur_obj);
        }
    } else {
        npc->unk_1C--;
        func_8001BB68(D_800AA248.cur_obj);
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
    switch (npc->unk_64->dir) {
    case 6:
    case 7:
    case 8:
        if (D_800AA248.cur_obj->flags & 0x10) {
            npc->unk_20 = 0;
        } else {
            npc->unk_20 = 1;
        }
        npc->unk_22 = 3;
        D_800AA248.cur_obj->vel_x.w = 0;
        break;
    case 2:
    case 3:
    case 4:
        if (!(D_800AA248.cur_obj->flags & 0x10)) {
            npc->unk_20 = 0;
        } else {
            npc->unk_20 = 1;
        }
        npc->unk_22 = 3;
        D_800AA248.cur_obj->vel_x.w = 0;
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

    if (D_800AA248.cur_obj->vel_x.w == 0) {
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
                facing = D_800AA248.cur_obj->flags & 0x10;
            }
            if (facing != 0) {
                speed = -speed;
            }
        } else {
            npc->unk_22 = 0x28;
            if (D_800AA248.cur_obj->flags & 0x10) {
                speed = -0x28000;
            } else {
                speed = 0x28000;
            }
        }
        D_800AA248.cur_obj->vel_x.w = speed;
        idx = npc->unk_2E & 3;
        if (npc->unk_20 == 1) {
            table = D_8007DA58;
        } else {
            table = D_8007DA68;
        }
        func_8003EB5C(table[idx], D_800AA248.cur_obj);
    }
    n = npc->unk_22 - 1;
    npc->unk_22 = n;
    if (n == 0 || func_80039958(npc) == 1) {
        npc->unk_22 = 0;
        D_800AA248.cur_obj->vel_x.w = 0;
        npc->unk_8 = 2;
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_800385F4);
#endif

void func_80038754(NpcS *npc) {
    Monster *player;

    func_8001F724(5);
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    player = npc->unk_64;
    npc->unk_8 = 4;
    npc->unk_1C = 3;
    if (player != NULL) {
        func_80053C50(0x80000, player);
        func_8004A90C(player);
        npc->unk_64 = NULL;
        player->unk_1D4 = 0;
    }
    func_800215C0(((s16 *)&D_800AA248.cur_obj->pos_x.w)[1], ((u16 *)&D_800AA248.cur_obj->pos_y.w)[1] - 0xA);
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

    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
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
        ((s16 *)&D_800AA248.cur_obj->pos_x.w)[1] = D_801D8864.w & func_8001EA78();
        func_80039A58(npc);
        return;
    }
    npc->unk_1C = 0x96;
    D_800AA248.cur_obj->pos_y.w = 0x02000000;
    func_8003831C();
}

#ifdef NON_MATCHING
/* 98.73 %: register choices only: the original builds both table addresses in a0 and adds the row before the index (row + which * 4); here which * 4 + row */
void func_80038920(NpcS *npc) {
    u16 which;
    u8 *anim;
    u8 **row;

    if (func_80038C1C() != 0) {
        return;
    }
    if (func_80039220(&which, npc) == 0) {
        if (npc->unk_C != 0) {
            func_8003EB5C(*(D_8007DA68 + (npc->unk_2E & 3)), D_800AA268.p);
        }
    } else {
        row = *(D_8007DA78 + (npc->unk_2C & 3));
        anim = row[which];
        if (anim != (u8 *)D_800AA268.p->anim) {
            func_8003EB5C(anim, D_800AA268.p);
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
                func_8003EB5C(D_80095E24, D_800AA248.cur_obj);
                return;
            case 2:
                func_8003EB5C(D_80095E68, D_800AA248.cur_obj);
                return;
            default:
                func_8003EB5C(D_80095EAC, D_800AA248.cur_obj);
                return;
            }
        }
    }
    func_80038920(npc);
}

#ifdef NON_MATCHING
/* 96.62 %: register choices only, as func_80038920: the table entry's address is built in v1 in the original */
void func_80038AE8(NpcS *npc) {
    Monster *player;

    player = npc->unk_64;
    if ((player == NULL || player->dir == 0 || player->dir == 5 || player->dir == 1) && npc->unk_2A == 4) {
        if (npc->unk_C != 0) {
            func_8003EB5C(D_8007DA68[npc->unk_2E & 3], D_800AA268.p);
        }
        return;
    }
    if (npc->unk_C == 0) {
        return;
    }
    if (D_800AA268.p->vel_x.w == 0) {
        npc->unk_C = 0;
        if (player != NULL && player->dir != 0 && player->dir != 5 && player->dir != 1) {
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
    D_800AA248.cur_obj->vel_x.w = 0;
    func_8003EB5C(D_8007DA68[npc->unk_2E & 3], D_800AA248.cur_obj);
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80038AE8);
#endif

u16 func_80038C1C(npc)
    NpcS *npc;
{
    s16 x;
    s16 mx;
    u16 i;
    Monster *m;

    x = D_800AA268.p->pos_x.s.hi;
    if (D_801F9ACA >= x && abs(x - D_801F9ACA) >= 200) {
        x += D_801D8866;
    }
    i = 7;
    do {
        m = &D_801E0B78[i];
        if (m->unk_058 & 1) {
            mx = m->obj->pos_x.s.hi;
            if (D_801F9AC8.s.hi >= mx && abs(mx - D_801F9AC8.s.hi) >= 200) {
                mx += D_801D8864.u.hi;
            }
            if (D_800AA248.cur_obj->flags & 0x10) {
                x += 0x30;
                if (x > mx) {
                    return 0;
                }
            } else {
                x -= 0x30;
                if (x < mx) {
                    return 0;
                }
            }
        }
    } while (--i != 0);
    npc->unk_4 = 0;
    func_8003EB5C(*(D_8007DAB8 + (npc->unk_2E & 3)), D_800AA268.p);
    return 1;
}

u16 func_80038DA8(NpcS *npc) {
    s16 x;
    s16 mx;
    u16 i;
    Monster *m;

    if (D_800AA268.p->unk_6C & 0x80) {
        return 0;
    }
    x = D_800AA268.p->pos_x.s.hi;
    if (D_801F9ACA >= x && abs(x - D_801F9ACA) >= 200) {
        x += D_801D8866;
    }
    i = 7;
    do {
        m = &D_801E0B78[i];
        if (m->unk_058 & 1) {
            mx = m->obj->pos_x.s.hi;
            if (D_801F9AC8.s.hi >= mx && abs(mx - D_801F9AC8.s.hi) >= 200) {
                mx += D_801D8864.u.hi;
            }
            if (D_800AA248.cur_obj->flags & 0x10) {
                x += 0x30;
                if (x < mx) {
                    continue;
                }
            } else {
                x -= 0x30;
                if (x > mx) {
                    continue;
                }
            }
            if (abs(x - mx) < 0x146) {
                return 1;
            }
        }
    } while (--i != 0);
    return 0;
}

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

void func_80039290(void) {
    NpcS *npc;
    u16 *info;
    u16 sound;
    u16 arg;
    u16 which;

    npc = D_800AA268.p->owner.p;
    if (npc->unk_2A == 0 || npc->unk_2A == 4) {
        goto count;
    }
    info = D_800AA268.p->arg.h;
    sound = *info++;
    arg = info[0];
    which = info[1];
    if (sound != 0) {
        func_8001F7CC(arg, sound);
    }
    if (func_8004A9B0(npc, which, 7, 0, 0) == 1) {
count:
        D_801E1E14++;
    } else {
        npc->unk_2A = 4;
        npc->unk_1C = 4;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80039358);

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_8003956C);

void func_80039890(void) {
    NpcS *npc = (NpcS *)D_800AA248.cur_obj->owner.ai;
    u16 *info;

    npc->unk_C = 1;
    info = D_800AA248.cur_obj->arg.h;
    npc->unk_2A = *info;
    npc->unk_2E = *info;
}

void func_800398D4(npc)
    NpcS *npc;
{
    GameObject *mover;
    ObjectDef *effect;

    mover = D_800AA248.cur_obj;
    effect = func_8001D110();
    D_800AA248.new_def = effect;
    effect->flags = (u16)mover->priority + 1;
    effect->pos_y.s.hi = npc->unk_5E - 0xA;
    effect->pos_x.s.hi = npc->unk_5C;
    effect->id = 0x4F0035F6;
    effect->anim = &D_800960E0;
    func_8001DCB4();
    D_800AA248.cur_obj = mover;
}

u16 func_80039958(NpcS *npc) {
    s32 speed;
    s32 *edge;
    s16 x;

    if (npc->unk_64 != NULL) {
        speed = D_800AA268.p->vel_x.w;
        edge = &D_801D3D98[D_801FA8A0[npc->unk_64->id - 1]];
        if (speed >= 0) {
            if (*edge > 0x16C0000) {
                speed = 0;
            }
        } else if (*edge <= 0x1FFFFF) {
            speed = 0;
        }
        if (speed == 0) {
            return 1;
        }
    }
    if (D_801FA98C == 0 || (x = ((s16 *)&D_800AA268.p->pos_x.w)[1], x < D_801FA98C - 0x10) || D_801FA990 + 0x10 < x) {
        return 0;
    }
    if (D_800AA268.p->vel_x.w <= 0) {
        return x >= D_801FA990;
    }
    return x <= D_801FA990;
}

void func_80039A58(NpcS *npc) {
    if (npc->unk_1C == 0) {
        if (func_80039C40(D_800AA248.cur_obj->pos_x.w, -0x280000, -0x280000) == 0) {
            npc->unk_6 = 0x31;
            npc->unk_8 = 2;
            npc->unk_1C = 0x3C;
            npc->unk_1A = 0;
            func_8003EB5C(D_8009585C, D_800AA248.cur_obj);
            func_8001BB88(D_800AA248.cur_obj);
        }
    } else {
        npc->unk_1C--;
        func_8001BB68(D_800AA248.cur_obj);
    }
}

s32 func_80039B04(Monster *player, s32 x) {
    s32 pos = player->obj->pos_x.w;

    if (abs(x - pos) > (D_801D8864.w + 1) / 2) {
        x += D_801D8864.w + 1;
    }
    return abs(x - pos);
}

Monster *func_80039B60(s32 x) {
    Monster *best = NULL;
    s32 bestDist = 0x1FFF0000;
    s32 i;

    for (i = 0; i < 3; i++) {
        s32 slot = func_80025DF8(i + 1);

        if (*(u16 *)&D_801E0B78[slot] != 0) {
            s32 pos = D_801E0B78[slot].obj->pos_x.w;
            s32 dist;

            if (pos < D_801F9AC8.w) {
                pos += D_801D8864.w;
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
    if (x < D_801F9AC8.w) {
        x += D_801D8864.w + 1;
    }
    if (x < D_801F9AC8.w + left || D_801F9AC8.w + (0x01900000 - right) < x) {
        return 0;
    }
    return 1;
}

s32 func_80039C98(s32 x, s32 left, s32 right) {
    if (x < D_801F9AC8.w) {
        x += D_801D8864.w + 1;
    }
    if ((D_801F9AC8.w < x && x < D_801F9AC8.w + left) ||
        (D_801F9AC8.w + (0x01900000 - right) < x && x < D_801F9AC8.w + 0x01900000)) {
        return 1;
    }
    return 0;
}

void func_80039D04(NpcS *npc) {
    s32 x;
    Monster *player;
    s32 px;
    s32 d;

    x = D_800AA248.cur_obj->pos_x.w;
    if (--npc->unk_1C == -1) {
        player = func_80039B60(x);
        if (player != NULL) {
            px = player->obj->pos_x.w;
            d = abs(x - px);
            if (d < (D_801D8864.w + 1) / 2) {
                if ((x < px && (D_800AA248.cur_obj->flags & 0x10)) || (px < x && !(D_800AA248.cur_obj->flags & 0x10))) {
                    goto turn;
                }
            }
            if (d > (D_801D8864.w + 1) / 2 &&
                ((px < x && (D_800AA268.p->flags & 0x10)) || (x < px && !(D_800AA268.p->flags & 0x10)))) {
            turn:
                npc->unk_1C = 0x3C;
                func_8003EB5C(D_8009594C, D_800AA248.cur_obj);
                npc->unk_24 = 0;
            } else if (func_80039C40(x, 0, 0) == 0) {
                npc->unk_8 = 0xF;
            } else {
                npc->unk_8 = 0x11;
                npc->unk_1C = 0;
            }
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_80039EC4);

void func_8003A0A8(NpcS *npc) {
    if (D_801FA990 != 0 || D_801FA98C != 0) {
        if (((s16 *)&D_800AA248.cur_obj->pos_x.w)[1] > D_801FA98C && ((s16 *)&D_800AA248.cur_obj->pos_x.w)[1] < D_801FA98C + 4 &&
            !(D_800AA248.cur_obj->flags & 0x10)) {
            goto stop;
        }
        if (((s16 *)&D_800AA248.cur_obj->pos_x.w)[1] < D_801FA990 && D_801FA990 - 4 < ((s16 *)&D_800AA248.cur_obj->pos_x.w)[1] &&
            (D_800AA248.cur_obj->flags & 0x10)) {
            goto stop;
        }
    }
    if (func_80039C40(D_800AA248.cur_obj->pos_x.w, 0x460000, 0x460000) == 0) {
        func_8003EB5C(D_80095874, D_800AA248.cur_obj);
        if (D_800AA248.cur_obj->flags & 0x10) {
            npc->unk_34 = -0x28000;
            D_800AA248.cur_obj->vel_x.w = 0;
            return;
        }
        npc->unk_34 = 0x28000;
        D_800AA248.cur_obj->vel_x.w = 0;
        return;
    }
stop:
    npc->unk_8 = 2;
    npc->unk_1C = 0x1E;
    func_8003EB5C(D_8009585C, D_800AA248.cur_obj);
    npc->unk_34 = 0;
    D_800AA248.cur_obj->vel_x.w = 0;
    npc->unk_24 = 0;
}

#ifdef NON_MATCHING
/* 99.78 %: the velocity lands in v1 here; the original reuses the flag test's v0 */
void func_8003A218(NpcS *npc) {
    Monster *player;
    s32 v;

    npc->unk_1C--;
    player = func_80039B60(D_800AA248.cur_obj->pos_x.w);
    if (player != NULL && func_80039B04(player, D_800AA248.cur_obj->pos_x.w) <= 0x77FFFF && npc->unk_1C > 0) {
        func_8003EB5C(D_800958E0, D_800AA248.cur_obj);
        v = 0x20000;
        if (!(D_800AA248.cur_obj->flags & 0x10)) {
            v = -0x20000;
        }
        npc->unk_34 = v;
        D_800AA248.cur_obj->vel_x.w = 0;
        return;
    }
    npc->unk_8 = 2;
    npc->unk_1C = 0x14;
    func_8003EB5C(D_8009585C, D_800AA248.cur_obj);
    npc->unk_34 = 0;
    D_800AA248.cur_obj->vel_x.w = 0;
    npc->unk_24 = 0;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_8003A218);
#endif

void func_8003A328(NpcS *npc, s32 arg1) {
    GameObject *mover;
    Anim *def;
    ObjectDef *effect;

    mover = D_800AA248.cur_obj;
    if ((u16)npc->unk_1A >= arg1) {
        func_8001F724(5);
        func_80029118(6, 8);
        if (npc->unk_6 == 0x14) {
            def = &D_8008A7E4;
        } else if (npc->unk_6 == 0x15) {
            def = &D_8008A828;
        } else {
            def = &D_8008A7A4;
        }
        effect = func_8001D110();
        D_800AA248.new_def = effect;
        effect->pos_x.s.hi = ((u16 *)&D_800AA248.cur_obj->pos_x.w)[1];
        effect->pos_y.s.hi = ((u16 *)&D_800AA248.cur_obj->pos_y.w)[1] - 0x19;
        effect->anim = def;
        effect->flags = (u16)D_800AA248.cur_obj->priority + 1;
        effect->id = def->id;
        func_8001DCB4();
        npc->unk_1C = 3;
        npc->unk_8 = 4;
    } else {
        func_8001F724(0x60);
        npc->unk_8 = 0xC;
        npc->unk_1C = 6;
        npc->unk_1A++;
        func_8003EB5C(D_800959D4, D_800AA248.cur_obj);
        if (D_800AA248.cur_obj->flags & 0x10) {
            npc->unk_34 = 0x70000;
        } else {
            npc->unk_34 = -0x70000;
        }
        D_800AA268.p->vel_x.w = 0;
    }
    D_800AA268.p = mover;
}

void func_8003A4A0(NpcS *npc) {
    u16 n;

    D_800AA248.cur_obj->vel_x.w = 0;
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
    GameObject *mover = D_800AA248.cur_obj;
    u16 *info = mover->arg.h;
    u16 sound = *info++;
    u16 arg = info[0];
    u16 which = info[1];

    if (!(mover->unk_6C & 0x80)) {
        if (sound != 0) {
            func_8001F7CC(arg, sound);
        }
        func_8004A9B0(0, which, 0x15, 0, 0);
    }
    D_800AA248.cur_obj = mover;
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_8003A5A0);

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_8003A744);

void func_8003A904(NpcS *npc) {
    npc->unk_2A = 1;
    switch (npc->unk_24) {
    case 0:
        func_8003EB5C(D_80095B18, D_800AA248.cur_obj);
        break;
    case 1:
        func_8003EB5C(D_80095AF0, D_800AA248.cur_obj);
        break;
    default:
        func_8003EB5C(D_80095AC8, D_800AA248.cur_obj);
        break;
    }
    npc->unk_8 = 2;
    npc->unk_1C = 0x14;
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_8003A98C);

void func_8003AA7C(NpcS *npc) {
    D_800AA248.cur_obj->priority = 0x4000;
    npc->unk_8 = 2;
    npc->unk_1C = 0x3C;
    func_8003EB5C(D_800956D0, D_800AA248.cur_obj);
    npc->unk_14 = 0;
    npc->unk_C = 1;
    ((s16 *)&D_800AA248.cur_obj->pos_y.w)[1] = 0x3C;
}

/* 93.12%: the original keeps the facing test as two arms joined by a jump, and rebuilds the address of D_800AA248 after the join (in s0); here the arms collapse into one conditional set and the address stays in one saved register throughout */
#ifdef NON_MATCHING
void func_8003AAF8(NpcS *npc) {
    s32 offset;

    if (npc->unk_1C == 0) {
        D_800AA248.cur_obj->priority = 0x50;
        if (D_800AA248.cur_obj->flags & 0x10) {
            offset = 0x1CC0000;
        } else {
            offset = -0x3C0000;
        }
        ((s16 *)&D_800AA248.cur_obj->pos_x.w)[1] = ((D_801F9AC8.w + offset) & D_801D8864.w) >> 16;
        ((s16 *)&D_800AA248.cur_obj->pos_y.w)[1] = 0x46;
        npc->unk_8 = 0x63;
        npc->unk_1C = (func_8001EA78() & 0x3F) + 0x78;
        func_8003EB5C(D_800956C4, D_800AA248.cur_obj);
        npc->unk_14 = 0;
        npc->unk_C = 1;
    } else {
        npc->unk_1C--;
        ((s16 *)&D_800AA268.p->pos_y.w)[1] = 0x258;
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_8003AAF8);
#endif

void func_8003ABE8(NpcS *npc) {
    if (D_800AA248.cur_obj->flags & 0x10) {
        npc->unk_34 = -0x40000;
    } else {
        npc->unk_34 = 0x40000;
    }
    D_800AA248.cur_obj->vel_x.w = 0;
    if (npc->unk_1C != 0) {
        npc->unk_1C--;
        return;
    }
    if (D_800AA248.cur_obj->unk_6C & 0x80) {
        func_8003AA7C(npc);
    }
}

/* 99.86%: one register pair swapped: the right-edge test loads D_801F9AC8 into v1 and the constant into v0 in the original, the other way round here */
#ifdef NON_MATCHING
void func_8003AC74(NpcS *npc) {
    s32 x;
    u16 t;
    u16 n;

    npc->unk_4++;
    t = npc->unk_14;
    if (t < 0x20) {
        D_800AA268.p->vel_y.w = 0x2000;
        npc->unk_14++;
    } else if (t < 0x28) {
        D_800AA268.p->vel_y.w = 0;
        npc->unk_14++;
    } else if (t < 0x48) {
        D_800AA268.p->vel_y.w = -0x2000;
        npc->unk_14++;
    } else if (t < 0x50) {
        D_800AA268.p->vel_y.w = 0;
        npc->unk_14++;
    } else {
        npc->unk_14 = 0;
    }
    if (npc->unk_C != 0) {
        x = D_800AA268.p->pos_x.w;
        if (func_80039C40(x, 0x50000, 0x50000) != 0) {
            n = npc->unk_24;
            if (n < 2 && npc->unk_4 >= 0x10) {
                if (n == 0) {
                    func_8001F7CC(0x64, 0x50);
                    func_8004A9B0(0, 5, 0x15, 0, 0);
                    func_8004A9B0(0, 5, 0x16, 0, 0);
                } else {
                    func_8001F7CC(0x64, 0x50);
                    func_8004A9B0(0, 6, 0x15, 0, 0);
                    func_8004A9B0(0, 6, 0x16, 0, 0);
                }
                npc->unk_4 = 0;
            }
        }
        if (func_80039C40(x, 0x320000, 0x320000) != 0) {
            if (x < D_801F9AC8.w) {
                x += D_801D8864.w + 1;
            }
            if (x < D_801F9AC8.w + 0xBE0000 && (D_800AA268.p->flags & 0x10)) {
                func_8003EB5C(D_80095800, D_800AA268.p);
                npc->unk_C = 0;
            } else if (D_801F9AC8.w + 0xD20000 < x && !(D_800AA268.p->flags & 0x10)) {
                func_8003EB5C(D_800957A4, D_800AA268.p);
                npc->unk_C = 0;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_8003AC74);
#endif

void func_8003AEA0(NpcS *npc) {
    if (func_80039C40(D_800AA248.cur_obj->pos_x.w, 0x460000, 0x460000) == 0) {
        if (D_800AA248.cur_obj->flags & 0x10) {
            npc->unk_34 = -0x48000;
            D_800AA248.cur_obj->vel_x.w = 0;
        } else {
            npc->unk_34 = 0x48000;
            D_800AA248.cur_obj->vel_x.w = 0;
        }
    } else {
        npc->unk_8 = 2;
        npc->unk_1C = 0x1E;
        npc->unk_34 = 0;
        D_800AA248.cur_obj->vel_x.w = 0;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_8003AF40);

void func_8003B1D0(NpcS *npc) {
    if (npc->unk_C != 0) {
        if (npc->unk_1C > 0) {
            npc->unk_1C--;
        }
        if (func_80039C40(D_800AA248.cur_obj->pos_x.w, 0xA0000, 0xA0000) == 0) {
            npc->unk_8 = 0x15;
            return;
        }
        if (npc->unk_1C == 0) {
            if (func_80039C98(D_800AA248.cur_obj->pos_x.w, 0x460000, 0x460000) != 0) {
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

    D_800AA248.cur_obj = npc->unk_0;
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

/* 98.32%: the original rebuilds the address of D_800AA248 into s1 once the countdown reaches zero (the earlier one ends there) and keeps the facing speed in v0; here the first address lives on and the speed lands in v1 */
#ifdef NON_MATCHING
void func_8003B3C8(NpcS *npc) {
    s32 speed;

    D_800AA248.cur_obj = npc->unk_0;
    func_80020D20();
    func_8003AC74(npc);
    switch (npc->unk_8) {
    case 1:
    case 0x3B:
        npc->unk_8 = 2;
        npc->unk_1C = 0x14;
        break;
    case 3:
        func_8003A328(npc, 0);
        break;
    case 4:
        func_80038800(npc);
        break;
    case 2:
        speed = -0x70000;
        if (!(D_800AA248.cur_obj->flags & 0x10)) {
            speed = 0x70000;
        }
        npc->unk_34 = speed;
        D_800AA248.cur_obj->vel_x.w = 0;
        if (--npc->unk_1C == 0) {
            if (!(D_800AA248.cur_obj->flags & 0x10)) {
                if (func_80039C98(D_800AA248.cur_obj->pos_x.w, 0xC80000, -0xA0000) != 0) {
                    goto hit;
                }
                if (!(D_800AA248.cur_obj->flags & 0x10)) {
                    goto done;
                }
            }
            if (func_80039C98(D_800AA268.p->pos_x.w, -0xA0000, 0xC80000) != 0) {
            hit:
                func_8001F7CC(0x32, 1);
                func_8004A9B0(npc, 0, 5, 0, 0);
            }
        done:
            npc->unk_1C = 5;
        }
        break;
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_80034590", func_8003B3C8);
#endif
