/* The non-player characters: the six 0x78-byte Npc records of D_801FAC9C (include/npc.h) and their per-kind
 * updaters. The file starts with the per-kind handlers of the Pickup records of D_801FA9BC (pickup.c).
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "game.h"
#include "npc.h"
#include "psyq/libc2.h"

/* Other units. */
ObjectDef *func_8001D110(void);
GameObject *func_8001DCB4(void);         /* spawns D_800AA248.unk_3C */
void func_8001E4B0(GameObject *mover);
void func_80029118(s16, u16);
void func_8004BFE0(void);
void func_80053D68(s32 n, Monster *player);
s32 func_8001EA78(void);
void func_8001F7CC(s32 a, s32 b);
u16 func_8004A9B0(void *a, s32 b, s32 c, s32 d, s32 e);
void func_8001BB68(GameObject *mover);
GameObject *main_create_box(s32 a, s32 b, s32 c, s32 d, s32 color);
void func_8001BB88(GameObject *mover);
s16 func_8001EB10(s32 arg0, s32 arg1);
s32 *func_80025C08(void *list);
extern s32 D_8007DA48[];
extern s32 D_8007D470[];                /* speeds by kind - 1 (func_800360D8) */
void func_8003BD48(Pickup *npc);                /* the spawn list of D_801FAC9C */
void func_8001F724(u16);
void func_80020D20();                /* called with the record and without it: no prototype in the original */
void func_800242A8(void);
s32 func_80025DF8(s32 n);
void func_8003EB5C(u8 *anim, GameObject *mover);
u16 func_8003BE34(Pickup *npc);
void func_8004CFC0(void);
void func_80054374(s32 n, Monster *player);
void func_80053C50(s32 n, Monster *player);
void func_8004A90C(Monster *player);
void func_800215C0(s16 x, s16 y);
void func_8003C080();                /* called with the position and without: no prototype in the original */
void func_800634D4(Monster *, u32);
s32 abs(s32 n);

void func_80029D1C(void);
s32 pickup_test_touch(GameObject *mover, Monster *player);
void func_8005E0E8(Monster *player);
void func_8004BBC8(Npc *npc);
void func_80020DDC(Npc *npc);

/* This unit. */
u16 func_80036FD0(s16 x, s16 y, GameObject *mover);
u16 func_80036C30(Monster *player, Npc *npc, GameObject *mover, s32 reach);
void func_800383F4(Npc *npc);
void func_80038494(Npc *npc);
void func_800384E8(Npc *npc);
void func_80038AE8(Npc *npc);
void func_80036818(Npc *npc);
void func_80037A88(Npc *npc);
void func_80037F20(Npc *npc);
void func_80038348(Npc *npc);
void func_8003A98C(Npc *npc);
void npc_update_aim(Npc *npc);
void func_8003A218(Npc *npc);
void func_8003B294(Npc *npc);
void func_8003B3C8(Npc *npc);
void func_80035260();                /* called without the record it takes: no prototype in the original */
void func_8003518C(Pickup *npc);
void func_80035330(Pickup *npc);
void func_800345F8(Pickup *npc);
void func_80034B68(s32 speed);
void func_800346FC(Pickup *npc);
s32 func_80036028(void);
u16 func_80039958(Npc *npc);
void func_8003AAF8(Npc *npc);
void func_80039A58(Npc *npc);
void func_8003831C(void);
void func_800347E4(Pickup *npc, Anim *def);
void func_80036504(GameObject *a, GameObject *b, GameObject *c);
void func_80035B6C(Pickup *npc);
void func_80035EBC(Pickup *npc);
void func_8003585C(Pickup *npc);
void func_800358C8(Pickup *npc);
void func_80035928(Pickup *npc);
void func_8003599C(Pickup *npc);
void func_80035E80(Pickup *npc);
void func_80035F8C(Pickup *npc);
void func_80035DC0(Pickup *npc);
void func_80035BE8(Pickup *npc);
void func_80035A3C(Pickup *npc);
void func_80035B30(Pickup *npc);
void building_bob_pickup(void);
void func_80034670(void);                /* called with the record and without: no prototype in the original */
void func_8003AA7C(Npc *npc);
u16 func_80038DA8(Npc *npc);
void func_800380F0(Npc *npc);
void func_80038058(Npc *npc);
void func_80038198(Npc *npc);
void func_800381E4(Npc *npc);
void func_80038240(Npc *npc);
void func_800382A8(Npc *npc);
void func_80038A2C(Npc *npc);
void func_80038920(Npc *npc);
Monster *func_80039B60(s32 x);
s32 func_80039B04(Monster *player, s32 x);
void func_80034988(Pickup *npc);
void func_80034C54(GameObject *mover);
void func_80034D28(Pickup *npc);
void func_80034DAC(Pickup *npc);
void func_80034E48(Pickup *npc);
void func_80035040(void);
void func_800351CC(Pickup *npc);
void func_800354A4();                /* called without the record it reads: no prototype in the original */
void func_80035464(Pickup *npc);
void func_80035550(Pickup *npc);
void func_80035590(Pickup *npc);
void func_80035620(Pickup *npc);
void func_80035A88(Pickup *npc);
void func_80035DFC(Pickup *npc);
void func_80035FF0(void);
void func_80036300(Npc *npc);
void func_800369F8(Npc *npc);
u16 func_80037574(s16 x, s16 y, GameObject *mover);
u16 func_8003761C(s16 x, s16 y, Monster *player, Npc *npc);
void func_800376E0(Npc *npc);
void func_80037960(Npc *npc, GameObject *obj);
void func_80037BB4(Npc *npc);
void func_80037C1C(Npc *npc);
void func_80037CA0(Npc *npc);
void func_80037CF4(Npc *npc);
void func_80037D78(Npc *npc);
void func_80037E1C(Npc *npc);
void func_80037E78(Npc *npc);
void func_80037EE0(Npc *npc);
void func_800380C0(GameObject *mover);
void func_80038528(Npc *npc);
void func_800385F4(Npc *npc);
void func_80038754(Npc *npc);
void func_80038800(Npc *npc);
void func_80038838(Npc *npc);
u16 func_80038C1C();                 /* called without the record it reads: no prototype in the original */
u16 func_80038F3C(u16 *out, Npc *npc);
u16 func_800391F8(u16 *out, Npc *npc);
u16 func_80039220(u16 *out, Npc *npc);
void func_800398D4();                /* called without the record it reads: no prototype in the original */
s32 func_80039C40(s32 x, s32 left, s32 right);
s32 func_80039C98(s32 x, s32 left, s32 right);
void func_8003A328(Npc *npc, s32 arg1);
void func_8003ABE8(Npc *npc);
void func_8003AC74(Npc *npc);
void func_8003AEA0(Npc *npc);
void func_8003AF40(Npc *npc);
void func_8003B1D0(Npc *npc);

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
u16 monster_test_boxes(s16 x, s16 y, Monster *m);
void func_8004EFAC(void);
void func_800531C0(Monster *);
extern u8 D_80096018[];
extern u8 D_80096084[];
extern s32 D_8007DB28[];
extern Anim D_80091B24;
void func_8004AE2C(s32);
extern Anim D_8008C828;

void func_80034590(Pickup *npc) {
    npc->unk_08 = 2;
    npc->unk_1E = func_8001EB10(0x190, 0);
    npc->unk_22 = 0;
    func_8003EB5C(D_8007D4C0[npc->kind - 1], D_800AA248.cur_obj);
}

void func_800345F8(Pickup *npc) {
    func_8001F724(5);
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    npc->unk_08 = 4;
    npc->unk_1C = 5;
    func_800347E4(npc, D_8007D50C[npc->kind - 1]);
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

void func_800346FC(Pickup *npc) {
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

void func_800347E4(Pickup *npc, Anim *def) {
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

void func_80034898(Pickup *npc) {
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

void func_80034924(Pickup *npc) {
    func_8001F724(0x60);
    if (!((D_800AA248.cur_obj->flags ^ npc->unk_44) & 0x10)) {
        func_80034988(npc);
        return;
    }
    func_800345F8(npc);
}

void func_80034988(Pickup *npc) {
    void (*handler)(void) = D_8007D558[npc->kind - 1];

    if (handler == NULL) {
        func_800345F8(npc);
        return;
    }
    handler();
}

void func_800349E0(Pickup *npc) {
    void (*handler)(void) = D_8007D5A4[npc->kind - 1];

    if (handler == NULL) {
        func_800345F8(npc);
        return;
    }
    handler();
}

void func_80034A38(Pickup *npc) {
    func_80034B68(0x30000);
    D_800AA248.cur_obj->vel_y.w = -0xB0000;
    D_800AA248.cur_obj->pos_x.w += D_800AA248.cur_obj->vel_x.w;
    D_800AA248.cur_obj->priority = 0x4000;
    npc->unk_08 = 6;
    func_8003EB5C(D_8008A4F4, D_800AA248.cur_obj);
}

void func_80034AB4(Pickup *npc) {
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

void func_80034B94(Pickup *npc) {
    D_800AA248.cur_obj = npc->obj;
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

void func_80034D28(Pickup *npc) {
    func_8001F724(0x60);
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    npc->unk_08 = 4;
    npc->unk_0C = 0;
    if (npc->kind == 0x17) {
        func_8003EB5C(D_8008A5A8, D_800AA248.cur_obj);
    } else {
        func_8003EB5C(D_8008A62C, D_800AA248.cur_obj);
    }
}

void func_80034DAC(Pickup *npc) {
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

#ifdef NON_MATCHING
/* 92.84%: 92.8 %: the original masks with D_801D8866 loaded signed (lh) and steps n after the x store; the prologue
 * sets up the hoisted constants before n = 1 */
void func_80034E48(Pickup *npc) {
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
    s32 x;

    mover = D_800AA248.cur_obj;
    i = 0;
    n = 1;
    slot = D_801FB44C;
    do {
        kind = 4;
        if (npc->kind != 0x17) {
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
        if (npc->kind == 0x17) {
            step = 0x64;
        }
        if (mover->flags & 0x10) {
            offset = n * step;
        } else {
            offset = n * -step;
        }
        x = mover->pos_x.u.hi + offset;
        x &= (s16)D_801D8866;
        spawned->pos_x.s.hi = x;
        ((u16 *)&spawned->pos_y.w)[1] = ((u16 *)&mover->pos_y.w)[1];
        n++;
        slot++;
        i++;
    } while (i < 3);
    D_800AA268.p = mover;
    if (npc->kind == 0x17) {
        mover->vel_x.w = 0x50000;
    } else {
        mover->vel_x.w = 0x20000;
    }
    if (D_800AA248.cur_obj->flags & 0x10) {
        D_800AA248.cur_obj->vel_x.w = -D_800AA248.cur_obj->vel_x.w;
    }
    if (npc->kind == 0x17) {
        func_8003EB5C(D_8008A59C, D_800AA248.cur_obj);
    } else {
        func_8003EB5C(D_8008A620, D_800AA248.cur_obj);
    }
    npc->unk_08 = 2;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/npc", func_80034E48);
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

void func_800350C0(Pickup *npc) {
    GameObject *mover;
    u16 action;

    mover = npc->obj;
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

void func_8003518C(Pickup *npc) {
    u16 n = npc->unk_1C;

    if (n == 0) {
        func_800351CC(npc);
        return;
    }
    npc->unk_1C = n - 1;
    func_800242A8();
}

void func_800351CC(Pickup *npc) {
    npc->kind = 0x1B;
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

void func_80035260(Pickup *npc) {
    u16 n = npc->unk_1C;

    if (n == 0) {
        func_800351CC(npc);
        return;
    }
    npc->unk_1C = n - 1;
    func_800242A8();
}

void func_800352A0(Pickup *npc) {
    func_8001F724(5);
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    D_800AA248.cur_obj->priority = 0x4000;
    npc->unk_08 = 4;
    npc->unk_1C = 0xF;
    func_8003EB5C(D_8008A448, D_800AA248.cur_obj);
    func_800215C0(((s16 *)&D_800AA248.cur_obj->pos_x.w)[1], ((s16 *)&D_800AA248.cur_obj->pos_y.w)[1]);
}

void func_80035330(Pickup *npc) {
    if (npc->unk_0C != 0) {
        npc->unk_1C = 0x384;
        npc->unk_08 = 0x64;
        func_800242A8();
        func_8003EB5C(D_8008A47C, D_800AA248.cur_obj);
    }
}

void func_8003537C(Pickup *npc) {
    D_800AA248.cur_obj = npc->obj;
    if (npc->kind == 0x15) {
        building_bob_pickup();
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

void func_80035464(Pickup *npc) {
    u16 n = npc->unk_1C;

    if (n == 0) {
        func_800354A4();
        return;
    }
    npc->unk_1C = n - 1;
    func_800242A8();
}

void func_800354A4(npc)
    Pickup *npc;
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
    if (npc->kind == 0x15) {
        func_8003EB5C(D_8008AA40, D_800AA268.p);
    } else {
        func_8003EB5C(D_8008AA34, D_800AA268.p);
    }
}

void func_80035550(Pickup *npc) {
    u16 n = npc->unk_1C;

    if (n == 0) {
        func_800354A4();
        return;
    }
    npc->unk_1C = n - 1;
    func_800242A8();
}

void func_80035590(Pickup *npc) {
    func_8001F724(5);
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    D_800AA248.cur_obj->priority = 0x4000;
    npc->unk_08 = 4;
    npc->unk_1C = 0xF;
    func_8003EB5C(D_8008A9D4, D_800AA248.cur_obj);
    func_800215C0(((s16 *)&D_800AA248.cur_obj->pos_x.w)[1], ((s16 *)&D_800AA248.cur_obj->pos_y.w)[1]);
}

void func_80035620(Pickup *npc) {
    if (npc->unk_0C != 0) {
        npc->unk_1C = 0x384;
        npc->unk_08 = 0x64;
        func_800242A8();
        func_8003EB5C(D_8008AA10, D_800AA248.cur_obj);
    }
}

void func_8003566C(Pickup *npc) {
    D_800AA248.cur_obj = npc->obj;
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

void func_8003585C(Pickup *npc) {
    D_800AA248.cur_obj->pos_y.w += D_800AA248.cur_obj->vel_y.w;
    if (npc->unk_1C == 0) {
        npc->unk_0A = 1;
        D_800AA248.cur_obj->vel_y.w = 0x4000;
        func_8003EB5C(D_8008A9B0, D_800AA248.cur_obj);
    }
}

void func_800358C8(Pickup *npc) {
    D_800AA248.cur_obj->pos_y.w += D_800AA248.cur_obj->vel_y.w;
    if (D_800AA248.cur_obj->pos_y.w > 0x153FFFF) {
        func_80035A88(npc);
    }
}

void func_80035928(Pickup *npc) {
    D_800AA248.cur_obj->pos_y.w += D_800AA248.cur_obj->vel_y.w;
    if (D_800AA248.cur_obj->pos_y.w <= 0xFA0000) {
        npc->unk_0A = 2;
        npc->unk_1C = 1;
        func_8003EB5C(D_8008A968, D_800AA248.cur_obj);
    }
}

void func_8003599C(Pickup *npc) {
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

void func_80035A3C(Pickup *npc) {
    u16 n;

    D_800AA248.cur_obj->pos_y.w = 0x01900000;
    n = npc->unk_1C;
    if (n == 0) {
        func_80035A88(npc);
        return;
    }
    npc->unk_1C = n - 1;
}

void func_80035A88(Pickup *npc) {
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

void func_80035B30(Pickup *npc) {
    u16 n = npc->unk_1C;

    if (n == 0) {
        func_80035A88(npc);
        return;
    }
    npc->unk_1C = n - 1;
}

void func_80035B6C(Pickup *npc) {
    func_8001F724(5);
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    D_800AA248.cur_obj->priority = 0x1300;
    npc->unk_08 = 4;
    npc->unk_1C = 0x12;
    func_8003EB5C(D_8008AA28, D_800AA248.cur_obj);
    func_8004BFE0();
}

void func_80035BE8(Pickup *npc) {
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

void func_80035C4C(Pickup *npc) {
    D_800AA248.cur_obj = npc->obj;
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

void func_80035DC0(Pickup *npc) {
    u16 n = npc->unk_1C;

    if (n == 0) {
        func_80035DFC(npc);
        return;
    }
    npc->unk_1C = n - 1;
}

void func_80035DFC(Pickup *npc) {
    ((s16 *)&D_800AA248.cur_obj->pos_x.w)[1] = D_801D87B0 + 0x20;
    D_800AA248.cur_obj->pos_y.w = 0xF00000;
    D_800AA248.cur_obj->vel_x.w = 0x6000;
    npc->unk_08 = 2;
    if (npc->kind == 0x1C) {
        func_8003EB5C(D_8008A908, D_800AA248.cur_obj);
    } else {
        func_8003EB5C(D_8008A8DC, D_800AA248.cur_obj);
    }
}

void func_80035E80(Pickup *npc) {
    u16 n = npc->unk_1C;

    if (n == 0) {
        func_80035DFC(npc);
        return;
    }
    npc->unk_1C = n - 1;
}

void func_80035EBC(Pickup *npc) {
    Monster *player;

    if (npc->kind == 0x1C) {
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

void func_80035F8C(Pickup *npc) {
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

void func_800360D8(Pickup *npc) {
    Monster *m;
    GameObject *obj;
    s16 d;
    s32 speed;
    u16 i;

    i = 7;
    if (D_800AA248.cur_obj->vel_x.w != 0) {
        if (npc->kind >= 0xD && npc->unk_40 != NULL) {
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
                    if (npc->kind < 0x14) {
                        speed = D_8007D470[npc->kind - 1];
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

void func_80036300(Npc *npc) {
    D_800AA268.p = npc->obj;
    func_80029D1C();
    func_80036818(npc);
    switch (npc->kind) {
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
    Npc *npc = D_801FAC9C;
    u16 n = 6;

    do {
        func_800369F8(npc);
        npc++;
    } while (--n != 0);
    D_801D8730 = n;
    D_801E2A50 = n;
}

void func_80036440(Npc *npc, s32 depth) {
    GameObject *mover;
    ObjectDef *effect;
    s32 d;

    mover = main_create_box(0, 0, 0, 0, 0xFFFFFF);
    d = depth - 1;
    mover->priority = d;
    mover->unk_40.w = -0x3E7;
    mover->flags = (mover->flags & ~0x20) | 0x400;
    mover->unk_6C |= 0x2000;
    npc->unk_70 = mover;
    func_8001BB68(mover);
    effect = func_8001D110();
    effect->id = 0x4F000986;
    effect->flags = d;
    D_800AA284.p = effect;
    mover = func_8001DCB4();
    mover->flags |= 0x400;
    npc->unk_74 = mover;
    func_8001BB68(mover);
}

INCLUDE_ASM("asm/main/nonmatchings/npc", func_80036504);

void func_80036818(Npc *npc) {
    GameObject *a = npc->unk_70;
    GameObject *b = npc->obj;
    GameObject *c = npc->unk_74;

    if (a != NULL) {
        func_80036504(a, b, c);
    }
}

void func_8003684C(void) {
    SpawnItem *item;
    Npc *npc;
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
        npc->state = 0;
        npc->action = 1;
        npc->kind = item->unk_04;
        obj = func_8001DCB4();
        npc->obj = obj;
        obj->owner.npc = npc;
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
        if (npc->kind == 0x11 || npc->kind == 0x12) {
            func_80036440(npc, item->unk_0C);
        } else {
            obj->priority = obj->pos_y.u.hi + 0xF23;
        }
        item++;
        npc++;
    } while (--n != 0);
}

void func_800369F8(Npc *npc) {
    memset(npc, 0, sizeof(Npc));
    D_801D8730 = 0;
}

void func_80036A20(Monster *player) {
    u16 n;
    Npc *npc;
    GameObject *mover;
    u16 kind;

    n = D_801D8730;
    npc = D_801FAC9C;
    if (n == 0) {
        return;
    }
    do {
        kind = npc->kind;
        mover = npc->obj;
        if (kind == 0x31 || kind == 0x13 || kind == 0x14 || (kind == 0x15 && npc->action != 0x63)) {
            if (pickup_test_touch(mover, player) != 0) {
                func_80037078(player, npc);
                return;
            }
        } else if (!(mover->unk_6C & 0x80) && (npc->action == 0x32 || npc->action == 2 || npc->action == 0x1E)) {
            switch (npc->kind) {
            case 0x3E:
            case 0x3F:
                if (npc->action != 0x1E && (u16)player->action != 4) {
                    if (func_80036C30(player, npc, mover, 0x1E) != 1) {
                        break;
                    }
                    if (npc->action == 0x1E) {
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
                /* Class B: the block's loop notes count the constant 1 twice, so it gets s3 before the live count
                 * (return for break, case order and a fresh variable leave the two swapped). */
                LOOP_BLOCK(
                    if (func_80036C30(player, npc, mover, 0x14) == 1) {
                        return;
                    }
                    break;
                );
            }
        }
        npc++;
    } while (--n != 0);
}

INCLUDE_ASM("asm/main/nonmatchings/npc", func_80036C30);

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

void func_80037078(Monster *player, Npc *npc) {
    player->unk_024++;
    func_80054374(0x28, player);
    func_800634D4(player, 4);
    npc->action = 3;
    npc->unk_60 = player;
    npc->unk_54 = D_800AA248.cur_obj->flags;
    npc->unk_5C = player->pos.u.lo;
    npc->unk_5E = player->pos.u.hi;
    if (player->icon_timers[1] != 0) {
        npc->unk_1A += 0xA;
    }
    player->unk_18A = 1;
}

#ifdef NON_MATCHING
/* 76.88%: 76.9 %: the case order and the calls are the original's; the original sign-extends x and y once (s1, s2)
 * and keeps a copy of each (fp, s7) for the call to func_800372DC; here the shifted values stay live and x, y spill */
u16 func_800372DC(s16 x, s16 y, Monster *player, Npc *npc, s32 arg4);
u16 func_800374FC(s16 x, s16 y, Npc *npc, GameObject *mover);

u16 func_8003712C(s16 x, s16 y, Monster *player) {
    Npc *npc;
    GameObject *obj;
    u16 n;
    u16 hit;

    n = D_801D8730;
    npc = D_801FAC9C;
    if (n == 0) {
        return 0;
    }
    do {
        obj = npc->obj;
        if (!(obj->unk_6C & 0x80) && (npc->action == 0x32 || npc->action == 2)) {
            switch (npc->kind) {
            case 0x42:
                if (player->unk_18E != 1) {
                    hit = func_800374FC(x, y, npc, obj);
                } else {
                    hit = func_80037574(x, y, obj);
                }
                if (hit == 1) {
                    return func_8003761C(x, y, player, npc);
                }
                break;
            case 0xF:
            case 0x3E:
                if (func_80037574(x, y, obj) == 1) {
                    return func_8003761C(x, y, player, npc);
                }
                break;
            case 0x12:
                if (func_800372DC(x, y, player, npc, (s32)obj) == 1) {
                    return func_8003761C(x, y, player, npc);
                }
                break;
            }
        }
        npc++;
    } while (--n != 0);
    return 0;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/npc", func_8003712C);
#endif

#ifdef NON_MATCHING
/* 99.85%: 99.85 %: the first rectangle's lhu temporaries (global, they cross the beqz) take v1 first in global-
 * alloc; the original's a0 needs v1 excluded: a v1 conflict or a v1 preference of the lower-priority s16 x (88) */
u16 func_800372DC(s16 x, s16 y, Monster *player, Npc *npc, s32 arg4) {
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
INCLUDE_ASM("asm/main/nonmatchings/npc", func_800372DC);
#endif

u16 func_800374FC(s16 x, s16 y, Npc *npc, GameObject *arg3) {
    MoverTarget *target = D_800AA248.cur_obj->unk_94.target;

    if (target != NULL) {
        Npc *other = target->unk_4->owner.npc;
        if (other != npc && other->state != 2) {
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

u16 func_8003761C(s16 x, s16 y, Monster *player, Npc *npc) {
    if (player == NULL) {
        return 0;
    }
    player->unk_024++;
    func_80054374(0x28, player);
    func_800634D4(player, 4);
    npc->action = 3;
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
/* 82.2 %: the twin of func_8003BD48 (pickup.c), with the same difference: the original tests the loaded limit in v0 and copies it into a1, where every form tried loads it straight into one register */
void func_800376E0(Npc *npc) {
    s32 limit;
    u16 x;
    u16 d;

    if (npc->action == 2) {
        limit = D_801FAC84;
        if (D_801FAC84 != 0) {
            x = D_800AA268.p->pos_x.u.hi;
            if (!(D_800AA268.p->flags & 0x10)) {
                d = limit - x;
            } else {
                d = (u16) D_801F9AB0 - x + 0x31;
            }
            if (d < 0x32) {
                npc->state = 1;
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
                    npc->state = 1;
                }
            }
        }
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/npc", func_800376E0);
#endif

#ifdef NON_MATCHING
/* 94.25%: the original keeps the slot bound 8 in a register (sltu against t0) and counts with a2/a1 where this C
 * uses sltiu and a3/a2; first draft after the Npc typing */
void func_800377B4(Npc *npc) {
    u16 i;
    u16 slot;
    u16 best;
    Monster *m;

    npc->unk_58 ^= 1;
    if (D_801D8740 == 0) {
        npc->unk_10 = NULL;
        npc->unk_56 = 0;
        return;
    }
    best = 0;
    if (npc->unk_58 == 0) {
        i = 7;
        slot = npc->unk_04;
        do {
            slot++;
            if (slot >= 8) {
                slot = 1;
            }
            m = &D_801E0B78[slot];
            if (m->unk_058 & 1) {
                break;
            }
        } while (--i != 0);
        npc->unk_10 = m;
        npc->unk_04 = slot;
        return;
    }
    i = 7;
    slot = 1;
    do {
        m = &D_801E0B78[slot];
        if ((m->unk_058 & 1) && m->unk_040 >= 0x1C20 && m->unk_040 >= best) {
            best = m->unk_040;
        }
        slot++;
    } while (--i != 0);
    i = 7;
    slot = npc->unk_56;
    do {
        slot++;
        if (slot >= 8) {
            slot = 1;
        }
        m = &D_801E0B78[slot];
        if (m->unk_058 & 1) {
            if (m->unk_040 + 0x12C < best) {
                break;
            }
        } else {
            i++;
        }
    } while (--i != 0);
    npc->unk_10 = m;
    npc->unk_56 = slot;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/npc", func_800377B4);
#endif

void func_80037960(Npc *npc, GameObject *obj) {
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

void func_80037A88(Npc *npc) {
    D_800AA248.cur_obj = npc->obj;
    switch (npc->action) {
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
        if (npc->state != 0) {
            func_80037EE0(npc);
            return;
        }
        func_80020D20(npc);
        func_800376E0(npc);
        return;
    }
}

void func_80037BB4(Npc *npc) {
    if (npc->unk_1C == 0) {
        func_80037C1C(npc);
        return;
    }
    npc->unk_1C--;
    D_800AA248.cur_obj->vel_x.w = D_801F9AC8.w - 0x19A0000;
    D_800AA248.cur_obj->vel_y.w = 0;
}

void func_80037C1C(Npc *npc) {
    if (npc->unk_1C != 0) {
        npc->unk_1C--;
        D_800AA248.cur_obj->pos_y.w = 0x01900000;
        return;
    }
    func_80035FF0();
    func_800380C0(D_800AA248.cur_obj);
    npc->action = 2;
    npc->unk_22 = 0;
    func_8003EB5C(D_8008A374, D_800AA248.cur_obj);
}

void func_80037CA0(Npc *npc) {
    if ((D_800AA248.cur_obj->flags ^ npc->unk_54) & 0x10) {
        func_80037E1C(npc);
        return;
    }
    func_80037CF4(npc);
}

void func_80037CF4(Npc *npc) {
    func_80034B68(0x58000);
    D_800AA248.cur_obj->vel_y.w = -0x65529;
    D_800AA248.cur_obj->pos_x.w += D_800AA248.cur_obj->vel_x.w;
    D_800AA248.cur_obj->priority = 0x4000;
    npc->action = 0xD;
    func_8003EB5C(D_8008A398, D_800AA248.cur_obj);
}

void func_80037D78(Npc *npc) {
    D_800AA248.cur_obj->pos_x.w += D_800AA248.cur_obj->vel_x.w;
    D_800AA248.cur_obj->vel_y.w += 0x6000;
    D_800AA248.cur_obj->pos_y.w += D_800AA248.cur_obj->vel_y.w;
    if (D_800AA248.cur_obj->vel_y.w >= 0 && D_800AA248.cur_obj->pos_y.w > 0xE10000) {
        func_80037E1C(npc);
    }
}

void func_80037E1C(Npc *npc) {
    func_8001F724(5);
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    npc->action = 4;
    npc->unk_1C = 3;
    func_80034670();
}

void func_80037E78(Npc *npc) {
    if (npc->unk_1C != 0) {
        npc->unk_1C--;
        return;
    }
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    npc->action = 0x33;
    D_800AA248.cur_obj->pos_y.w = 0x02000000;
    func_8003831C();
}

void func_80037EE0(Npc *npc) {
    npc->state = 0;
    D_800AA248.cur_obj->vel_x.w = -D_800AA248.cur_obj->vel_x.w;
    D_800AA248.cur_obj->flags ^= 0x10;
}

void func_80037F20(Npc *npc) {
    D_800AA248.cur_obj = npc->obj;
    switch (npc->action) {
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
        if (npc->state != 0) {
            func_800382A8(npc);
            return;
        }
        func_80020D20(npc);
        func_800376E0(npc);
        return;
    }
}

void func_80038058(Npc *npc) {
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

void func_800380F0(Npc *npc) {
    if (npc->unk_1C != 0) {
        npc->unk_1C--;
        D_800AA248.cur_obj->pos_y.w = 0x01900000;
        return;
    }
    func_80035FF0();
    func_800380C0(D_800AA248.cur_obj);
    npc->action = 2;
    npc->unk_22 = 0;
    if (npc->kind == 0x3E) {
        func_8003EB5C(D_8008A3E0, D_800AA248.cur_obj);
    } else {
        func_8003EB5C(D_8008A414, D_800AA248.cur_obj);
    }
}

void func_80038198(Npc *npc) {
    if (npc->kind == 0x3E) {
        func_8003EB5C(D_8008A408, D_800AA248.cur_obj);
    } else {
        func_8003EB5C(D_8008A43C, D_800AA248.cur_obj);
    }
}

void func_800381E4(Npc *npc) {
    func_8001F724(5);
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    npc->action = 4;
    npc->unk_1C = 3;
    func_80034670();
}

void func_80038240(Npc *npc) {
    if (npc->unk_1C != 0) {
        npc->unk_1C--;
        return;
    }
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    npc->action = 0x33;
    D_800AA248.cur_obj->pos_y.w = 0x02000000;
    func_8003831C();
}

void func_800382A8(Npc *npc) {
    npc->state = 0;
    D_800AA248.cur_obj->vel_x.w = -D_800AA248.cur_obj->vel_x.w;
    D_800AA248.cur_obj->flags ^= 0x10;
}

void func_800382E8(void) {
    D_800AA248.cur_obj->owner.npc->unk_1C = 0;
}

void func_80038300(void) {
    D_800AA248.cur_obj->owner.npc->unk_0C = 1;
}

void func_8003831C(void) {
    D_800AA248.cur_obj->owner.npc->kind = 0;
    func_8004CFC0();
}

void func_80038348(Npc *npc) {
    D_800AA268.p = npc->obj;
    func_80020D20();
    switch (npc->action) {
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

void func_800383F4(Npc *npc) {
    if (npc->unk_1C == 0) {
        if (func_80039C40(D_800AA248.cur_obj->pos_x.w, -0x280000, -0x280000) == 0) {
            npc->kind = 0xF;
            npc->action = 2;
            func_8003EB5C(D_80095EF0, D_800AA248.cur_obj);
            func_8001BB88(D_800AA248.cur_obj);
        }
    } else {
        npc->unk_1C--;
        func_8001BB68(D_800AA248.cur_obj);
    }
}

void func_80038494(Npc *npc) {
    u16 n = npc->unk_1A;

    if (n >= 2) {
        func_80038754(npc);
        return;
    }
    npc->unk_1A = n + 1;
    npc->action = 0x32;
    npc->unk_20 = 1;
    func_800398D4();
}

void func_800384E8(Npc *npc) {
    if (npc->unk_64 == NULL) {
        func_800385F4(npc);
        return;
    }
    func_80038528(npc);
}

void func_80038528(Npc *npc) {
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

void func_800385F4(Npc *npc) {
    s32 speed;
    u16 n;

    if (D_800AA248.cur_obj->vel_x.w == 0) {
        u8 **table;
        s32 idx;

        if (npc->unk_20 == 1) {
            speed = 0x28000;
            npc->unk_22 = 0x14;
            if (npc->unk_64 == NULL) {
                idx = npc->unk_54;
            } else {
                speed = -0x28000;
                idx = D_800AA248.cur_obj->flags;
            }
            if (idx & 0x10) {
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
        D_800AA268.p->vel_x.w = speed;
        idx = npc->unk_2E & 3;
        if (npc->unk_20 == 1) {
            table = D_8007DA58;
        } else {
            table = D_8007DA68;
        }
        table += idx;
        func_8003EB5C(*table, D_800AA268.p);
    }
    n = npc->unk_22 - 1;
    npc->unk_22 = n;
    if (n == 0 || func_80039958(npc) == 1) {
        npc->unk_22 = 0;
        D_800AA268.p->vel_x.w = 0;
        npc->action = 2;
    }
}

void func_80038754(Npc *npc) {
    Monster *player;

    func_8001F724(5);
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    player = npc->unk_64;
    npc->action = 4;
    npc->unk_1C = 3;
    if (player != NULL) {
        func_80053C50(0x80000, player);
        func_8004A90C(player);
        npc->unk_64 = NULL;
        player->unk_1D4 = 0;
    }
    func_800215C0(((s16 *)&D_800AA248.cur_obj->pos_x.w)[1], ((u16 *)&D_800AA248.cur_obj->pos_y.w)[1] - 0xA);
}

void func_80038800(Npc *npc) {
    if (npc->unk_1C != 0) {
        npc->unk_1C--;
        return;
    }
    func_80038838(npc);
}

void func_80038838(Npc *npc) {
    u16 kind;

    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    kind = npc->kind;
    if (kind == 0x13) {
        npc->action = 1;
        npc->unk_1C = (func_8001EA78() & 0xFF) + 0x190;
        npc->unk_34 = 0;
        npc->unk_30 = 0;
        func_8003AAF8(npc);
        return;
    }
    if (kind == 0x31) {
        npc->action = 1;
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

void func_80038920(Npc *npc) {
    u16 which;
    u8 *anim;
    u8 **row;

    if (func_80038C1C() != 0) {
        return;
    }
    if (func_80039220(&which, npc) == 0) {
        if (npc->unk_0C != 0) {
            row = D_8007DA68 + (npc->unk_2E & 3);
            func_8003EB5C(*row, D_800AA268.p);
        }
    } else {
        row = D_8007DA78[npc->unk_2C & 3];
        row += which;
        anim = *row;
        if (anim != (u8 *)D_800AA268.p->anim) {
            func_8003EB5C(anim, D_800AA268.p);
            return;
        }
        if (npc->unk_4E != 0) {
            if (npc->unk_64 != NULL) {
                func_80038528(npc);
                return;
            }
            npc->action = 0x32;
            npc->unk_20 = 0;
            npc->unk_04 = 0;
        }
    }
}

void func_80038A2C(Npc *npc) {
    u16 move = npc->unk_2A;

    if (move != 0) {
        npc->unk_2C = move;
        if (func_80038DA8(npc) != 0) {
            s32 kind = npc->unk_2A;

            npc->unk_04++;
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

void func_80038AE8(Npc *npc) {
    Monster *player;
    u8 **p;

    player = npc->unk_64;
    if ((player == NULL || player->dir == 0 || player->dir == 5 || player->dir == 1) && npc->unk_2A == 4) {
        if (npc->unk_0C != 0) {
            p = D_8007DA68 + (npc->unk_2E & 3);
            func_8003EB5C(*p, D_800AA268.p);
        }
        return;
    }
    if (npc->unk_0C == 0) {
        return;
    }
    if (D_800AA268.p->vel_x.w == 0) {
        npc->unk_0C = 0;
        if (player != NULL && player->dir != 0 && player->dir != 5 && player->dir != 1) {
            npc->action = 0x32;
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
    p = D_8007DA68 + (npc->unk_2E & 3);
    func_8003EB5C(*p, D_800AA248.cur_obj);
}

u16 func_80038C1C(npc)
    Npc *npc;
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
    npc->unk_04 = 0;
    func_8003EB5C(*(D_8007DAB8 + (npc->unk_2E & 3)), D_800AA268.p);
    return 1;
}

u16 func_80038DA8(Npc *npc) {
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

#ifdef NON_MATCHING
/* 85.43%: 85.4 %: the counting part matches but for the registers of the three counts; the original's choice part
 * has three state blocks, one per level, each reached from two cases by cross-jumping, with the state in v1; here
 * the blocks merge differently */
u16 func_80038F3C(u16 *out, Npc *npc) {
    Monster *m;
    u16 high;
    u16 mid;
    u16 low;
    u16 i;
    u16 level;
    u16 state;

    high = 0;
    mid = 0;
    low = 0;
    if (npc->unk_64 != NULL) {
        switch (npc->unk_64->dir) {
        case 0:
            return func_800391F8(out, npc);
        case 1:
        case 2:
        case 8:
            low = 1;
            if (npc->unk_2C == 3) {
                low = 0;
                mid = 1;
            }
            break;
        default:
            high = 1;
            if (npc->unk_2C < 2) {
                high = 0;
                mid = 1;
            }
            break;
        }
    } else {
        i = 7;
        do {
            m = &D_801E0B78[i];
            if ((m->unk_058 & 1) && m->action != 0x1F) {
                if (m->climb_side == 0 || m->obj->pos_y.s.hi >= 0xD1) {
                    low++;
                } else if (m->obj->pos_y.s.hi >= 0x71) {
                    mid++;
                } else {
                    high++;
                }
            }
        } while (--i != 0);
    }
    D_800AA248.unk_18 = high | (low | mid);
    *out = D_800AA248.unk_18;
    if (*out == 0) {
        return 0;
    }
    switch (npc->unk_2C) {
    case 1:
        if (mid >= high) {
            if (mid == 0 && npc->unk_04 == 0) {
                return func_800391F8(out, npc);
            }
            state = mid ? 1 : 3;
            if (npc->unk_64 != NULL) {
                state = 3;
            }
            npc->unk_04 = state;
            level = 2;
        } else {
            state = high ? 1 : 3;
            if (npc->unk_64 != NULL) {
                state = 3;
            }
            npc->unk_04 = state;
            level = 3;
        }
        break;
    case 2:
        if (high >= low) {
            if (high == 0 && npc->unk_04 == 0) {
                return func_800391F8(out, npc);
            }
            state = high ? 1 : 3;
            if (npc->unk_64 != NULL) {
                state = 3;
            }
            npc->unk_04 = state;
            level = 3;
        } else {
            state = low ? 1 : 3;
            if (npc->unk_64 != NULL) {
                state = 3;
            }
            npc->unk_04 = state;
            level = 1;
        }
        break;
    default:
        if (mid >= low) {
            if (mid != 0) {
                state = mid ? 1 : 3;
                if (npc->unk_64 != NULL) {
                    state = 3;
                }
                npc->unk_04 = state;
                level = 2;
            } else if (npc->unk_04 != 0) {
                state = low ? 1 : 3;
                if (npc->unk_64 != NULL) {
                    state = 3;
                }
                npc->unk_04 = state;
                level = 1;
            } else {
                return func_800391F8(out, npc);
            }
        } else {
            state = low ? 1 : 3;
            if (npc->unk_64 != NULL) {
                state = 3;
            }
            npc->unk_04 = state;
            level = 1;
        }
        break;
    }
    *out = level;
    return 1;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/npc", func_80038F3C);
#endif

u16 func_800391F8(u16 *out, Npc *npc) {
    *out = npc->unk_2C;
    if (npc->unk_64 != NULL) {
        npc->unk_04 = 3;
    }
    return 1;
}

u16 func_80039220(u16 *out, Npc *npc) {
    u16 state = npc->unk_04;

    if (state != 0) {
        if (state < 3) {
            return func_800391F8(out, npc);
        }
        if (npc->unk_4E != 0) {
            npc->action = 0x32;
            npc->unk_20 = 0;
            npc->unk_04 = 0;
        }
        return 0;
    }
    return func_80038F3C(out, npc);
}

void func_80039290(void) {
    Npc *npc;
    u16 *info;
    u16 sound;
    u16 arg;
    u16 which;

    npc = D_800AA268.p->owner.npc;
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

u16 npc_create_throw(Monster *m, u16 a, u16 kind, Throw *t) {
    GameObject *saved;
    ObjectDef *def;
    GameObject *cur;
    SpriteFrame *fr;
    s16 dx;
    s16 dy;
    s16 x;
    GameObject *obj;
    NpcThrowSpeed *sp;
    s32 vx;

    saved = D_800AA248.cur_obj;
    def = func_8001D110();
    D_800AA248.new_def = def;
    cur = D_800AA248.cur_obj;
    fr = cur->frame;
    dx = fr->unk_20 - fr->origin.u.lo;
    x = dx;
    dy = fr->unk_22 - fr->origin.u.hi;
    if (cur->flags & 0x10) {
        x = -dx;
        def->unk_04 |= 0x10;
    }
    def->pos_x.s.hi = D_800AA248.cur_obj->pos_x.s.hi + x;
    def->pos_y.s.hi = D_800AA248.cur_obj->pos_y.s.hi + dy;
    def->flags = 0x1005;
    def->unk_0C = 0x726;
    def->id = 0x4F0000D6;
    switch (a) {
        case 3:
            def->anim = &D_80095FC8;
            break;
        case 2:
            def->anim = &D_80095FA4;
            break;
        case 1:
            def->anim = &D_80095F80;
            break;
    }
    obj = func_8001DCB4();
    D_800AA248.cur_obj = obj;
    if (obj != NULL) {
        t->obj = obj;
        t->kind = kind;
        t->state = 1;
        D_800AA248.cur_obj->unk_94.p = t;
        sp = &D_8007DAC8[a];
        t->unk_0C = sp->accel_y;
        D_800AA248.cur_obj->vel_y.w = sp->vel_y;
        vx = sp->vel_x;
        if (D_800AA248.cur_obj->flags & 0x10) {
            vx = -vx;
        }
        D_800AA248.cur_obj->vel_x.w = vx;
        D_800AA248.cur_obj->unk_8C = 8;
        D_800AA248.cur_obj->owner.monster = m;
        D_800AA248.cur_obj = saved;
        return 0;
    }
    D_800AA248.cur_obj = saved;
    D_801E1E14++;
    return 1;
}

void npc_update_throw(Throw *t) {
    GameObject *saved = D_800AA248.cur_obj;
    Monster *m;
    GameObject *body;
    u16 i;
    s32 v;
    Npc *npc;

    if (t->state == 0x10 || t->state == 1) {
        if (saved->unk_98 == (void *) 2) {
            t->state = 0x10;
            func_8003EB5C(D_80096084, D_800AA248.cur_obj);
        } else if (saved->unk_98 == (void *) 1) {
            t->state = 0x10;
            func_8003EB5C(D_80096018, D_800AA248.cur_obj);
        } else {
            v = saved->vel_x.w;
            if (v <= 0) {
                if (D_801D3D8A < 0) {
                    v += D_801D3D8A;
                }
            } else if (D_801D3D8A > 0) {
                v += D_801D3D8A;
            }
            D_800AA248.cur_obj->pos_x.w = (D_800AA248.cur_obj->pos_x.w + v) & D_801D8864.w;
            v = D_800AA248.cur_obj->vel_y.w + t->unk_0C;
            if (v > 0x90000) {
                v = 0x90000;
            }
            D_800AA248.cur_obj->vel_y.w = v;
            D_800AA248.cur_obj->pos_y.w += v;
            if (D_800AA248.cur_obj->pos_y.s.hi >= 0xD9) {
                goto fall;
            }
            i = 7;
            do {
                m = &D_801E0B78[i];
                if ((m->unk_058 & 1) && !((body = m->obj)->unk_6C & 0x80)) {
                    v = monster_test_boxes(D_800AA248.cur_obj->pos_x.s.hi, D_800AA248.cur_obj->pos_y.s.hi, m);
                    if (v != 0) {
                        func_80053C50(0x54000, m);
                        func_8004EFAC();
                        t->state = 0x10;
                        D_800AA248.cur_obj->unk_98 = (void *) 1;
                        if (body->pos_y.s.hi <= 0xE0) {
                            m->action = 0xF;
                        } else if ((D_800AA248.cur_obj->flags & 0x10) == (body->flags & 0x10)) {
                            m->action = 0x22;
                        } else {
                            m->action = 0xA;
                            func_800531C0(m);
                        }
                        goto end;
                    }
                }
            } while (--i != 0);
            npc = t->thrower->owner.npc;
            if (npc != NULL) {
                m = npc->unk_64;
                if ((m == NULL || D_800AA268.p->vel_y.w < -0x70000) && D_800AA268.p->vel_y.w >= 0) {
                    v = D_800AA268.p->unk_8C - 1;
                    if (v == 0) {
                    fall:
                        D_800AA268.p->unk_98 = (void *) 2;
                    } else {
                        D_800AA268.p->unk_8C = v;
                    }
                }
            }
        }
    }
end:
    D_800AA268.p = saved;
}

void func_80039890(void) {
    Npc *npc = D_800AA248.cur_obj->owner.npc;
    u16 *info;

    npc->unk_0C = 1;
    info = D_800AA248.cur_obj->arg.h;
    npc->unk_2A = *info;
    npc->unk_2E = *info;
}

void func_800398D4(npc)
    Npc *npc;
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

u16 func_80039958(Npc *npc) {
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

void func_80039A58(Npc *npc) {
    if (npc->unk_1C == 0) {
        if (func_80039C40(D_800AA248.cur_obj->pos_x.w, -0x280000, -0x280000) == 0) {
            npc->kind = 0x31;
            npc->action = 2;
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

void func_80039D04(Npc *npc) {
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
                npc->aim = 0;
            } else if (func_80039C40(x, 0, 0) == 0) {
                npc->action = 0xF;
            } else {
                npc->action = 0x11;
                npc->unk_1C = 0;
            }
        }
    }
}

extern u8 *D_8007DB04[];

void npc_update_aim(Npc *npc) {
    Monster *player;
    s32 dx;
    s32 dy;
    s32 anim;
    s32 dir;

    dir = 0;
    if (--npc->unk_1C == -1) {
        player = func_80039B60(D_800AA248.cur_obj->pos_x.w);
        if (player != NULL) {
            dx = func_80039B04(player, D_800AA248.cur_obj->pos_x.w) >> 16;
            dy = D_800AA248.cur_obj->pos_y.w - player->obj->pos_y.w;
            if (dx == 0) {
                dy = 0;
            } else {
                dy /= dx;
            }
            if (dy < 0x4000) {
                switch (npc->aim) {
                case 0:
                    anim = 0;
                    dir = 0;
                    break;
                case 1:
                    anim = 3;
                    dir = 0;
                    break;
                default:
                    anim = 6;
                    dir = 0;
                    break;
                }
            } else if (dy <= 0x7FFF) {
                switch (dir) {
                case 0:
                    anim = 1;
                    dir = 1;
                    break;
                case 1:
                    anim = 4;
                    dir = 1;
                    break;
                default:
                    anim = 7;
                    dir = 1;
                    break;
                }
            } else {
                switch (dir) {
                case 0:
                    anim = 2;
                    dir = 2;
                    break;
                case 1:
                    anim = 5;
                    dir = 2;
                    break;
                default:
                    anim = 8;
                    dir = 2;
                    break;
                }
            }
            if (dir == npc->aim) {
                npc->action = 0x12;
                npc->unk_1C = 1;
                return;
            }
            func_8003EB5C(D_8007DB04[anim], D_800AA268.p);
            npc->action = 2;
            npc->unk_1C = 0x1E;
            npc->aim = dir;
        }
    }
}

void func_8003A0A8(Npc *npc) {
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
    npc->action = 2;
    npc->unk_1C = 0x1E;
    func_8003EB5C(D_8009585C, D_800AA248.cur_obj);
    npc->unk_34 = 0;
    D_800AA248.cur_obj->vel_x.w = 0;
    npc->aim = 0;
}

void func_8003A218(Npc *npc) {
    Monster *player;

    npc->unk_1C--;
    player = func_80039B60(D_800AA248.cur_obj->pos_x.w);
    if (player != NULL && func_80039B04(player, D_800AA248.cur_obj->pos_x.w) <= 0x77FFFF && npc->unk_1C > 0) {
        func_8003EB5C(D_800958E0, D_800AA248.cur_obj);
        if (D_800AA248.cur_obj->flags & 0x10) {
            npc->unk_34 = 0x20000;
            D_800AA248.cur_obj->vel_x.w = 0;
        } else {
            npc->unk_34 = -0x20000;
            D_800AA248.cur_obj->vel_x.w = 0;
        }
        return;
    }
    npc->action = 2;
    npc->unk_1C = 0x14;
    func_8003EB5C(D_8009585C, D_800AA248.cur_obj);
    npc->unk_34 = 0;
    D_800AA248.cur_obj->vel_x.w = 0;
    npc->aim = 0;
}

void func_8003A328(Npc *npc, s32 arg1) {
    GameObject *mover;
    Anim *def;
    ObjectDef *effect;

    mover = D_800AA248.cur_obj;
    if ((u16)npc->unk_1A >= arg1) {
        func_8001F724(5);
        func_80029118(6, 8);
        if (npc->kind == 0x14) {
            def = &D_8008A7E4;
        } else if (npc->kind == 0x15) {
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
        npc->action = 4;
    } else {
        func_8001F724(0x60);
        npc->action = 0xC;
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

void func_8003A4A0(Npc *npc) {
    u16 n;

    D_800AA248.cur_obj->vel_x.w = 0;
    n = npc->unk_1C - 1;
    npc->unk_1C = n;
    npc->unk_34 = npc->unk_34 * 6 / 7;
    if ((s16)n == -1) {
        npc->action = 0x10;
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

u16 npc_create_shot(u16 a, u16 kind, Throw *t, s32 alt) {
    GameObject *saved;
    ObjectDef *def;
    SpriteFrame *fr;
    s16 dx;
    s16 dy;
    GameObject *obj;
    s32 *sp;
    s32 vx;

    saved = D_800AA248.cur_obj;
    D_800AA248.new_def = func_8001D110();
    def = D_800AA248.new_def;
    fr = D_800AA248.cur_obj->frame;
    if (alt == 0) {
        dy = fr->unk_22 - fr->origin.u.hi;
        dx = fr->unk_20 - fr->origin.u.lo;
    } else {
        dy = fr->unk_26 - fr->origin.u.hi;
        dx = fr->unk_24 - fr->origin.u.lo;
    }
    if (D_800AA248.cur_obj->flags & 0x10) {
        dx = -dx;
        def->unk_04 |= 0x10;
    }
    def->pos_x.s.hi = D_800AA248.cur_obj->pos_x.s.hi + dx;
    def->pos_y.s.hi = D_800AA248.cur_obj->pos_y.s.hi + dy;
    def->flags = 0x1005;
    def->id = 0x4F002E0A;
    def->anim = &D_80091B24;
    obj = func_8001DCB4();
    D_800AA248.cur_obj = obj;
    if (obj == NULL) {
        D_800AA248.cur_obj = saved;
        return 1;
    }
    t->obj = obj;
    t->kind = kind;
    t->state = 1;
    D_800AA248.cur_obj->unk_94.p = t;
    sp = &D_8007DB28[a * 2];
    D_800AA248.cur_obj->vel_y.w = sp[1];
    D_800AA248.cur_obj->vel_x.w = (saved->flags & 0x10) ? -sp[0] : sp[0];
    D_800AA248.cur_obj->unk_8C = 0x18;
    D_800AA248.cur_obj = saved;
    return 0;
}

void npc_update_shot(Throw *t) {
    GameObject *saved = D_800AA268.p;
    Monster *m;
    s32 vx;
    u16 i;
    u16 hit;

    if (t->state == 1) {
        if (saved->unk_6C & 0x80) {
            func_8004AE2C(1);
        } else {
            vx = saved->vel_x.w;
            if (vx <= 0) {
                if (D_801D3D8A < 0) {
                    vx += D_801D3D8A;
                }
            } else if (D_801D3D8A > 0) {
                vx += D_801D3D8A;
            }
            vx += D_800AA248.cur_obj->pos_x.w;
            D_800AA248.cur_obj->pos_x.w = vx & D_801D8864.w;
            D_800AA248.cur_obj->pos_y.w += D_800AA248.cur_obj->vel_y.w;
            i = 7;
            do {
                m = &D_801E0B78[i];
                if ((m->unk_058 & 1) && !(m->obj->unk_6C & 0x80) && m->icon_timers[0] == 0) {
                    hit = monster_test_boxes(D_800AA248.cur_obj->pos_x.s.hi, D_800AA248.cur_obj->pos_y.s.hi, m);
                    if (hit != 0) {
                        func_80053C50(0xA000, m);
                        t->state = 0x10;
                        func_8001E698(D_800AA248.cur_obj, &D_8008C828);
                        break;
                    }
                }
            } while (--i != 0);
        }
    }
    D_800AA268.p = saved;
}

void func_8003A904(Npc *npc) {
    npc->unk_2A = 1;
    switch (npc->aim) {
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
    npc->action = 2;
    npc->unk_1C = 0x14;
}

void func_8003A98C(Npc *npc) {
    D_800AA268.p = npc->obj;
    func_80020D20();
    switch (npc->action) {
    case 1:
    case 0x3B:
        func_80039A58(npc);
        break;
    case 2:
        func_80039D04(npc);
        break;
    case 0xF:
        func_8003A0A8(npc);
        break;
    case 0x10:
        func_8003A218(npc);
        break;
    case 0x11:
        npc_update_aim(npc);
        break;
    case 3:
        func_8003A328(npc, 3);
        break;
    case 4:
        func_80038800(npc);
        break;
    case 0xC:
        func_8003A4A0(npc);
        break;
    case 0x12:
        func_8003A904(npc);
        break;
    }
}

void func_8003AA7C(Npc *npc) {
    D_800AA248.cur_obj->priority = 0x4000;
    npc->action = 2;
    npc->unk_1C = 0x3C;
    func_8003EB5C(D_800956D0, D_800AA248.cur_obj);
    npc->unk_14 = 0;
    npc->unk_0C = 1;
    ((s16 *)&D_800AA248.cur_obj->pos_y.w)[1] = 0x3C;
}

void func_8003AAF8(Npc *npc) {
    if (npc->unk_1C == 0) {
        D_800AA248.cur_obj->priority = 0x50;
        if (D_800AA248.cur_obj->flags & 0x10) {
            D_800AA248.cur_obj->pos_x.s.hi = ((D_801F9AC8.w + 0x1CC0000) & D_801D8864.w) >> 16;
        } else {
            D_800AA248.cur_obj->pos_x.s.hi = ((D_801F9AC8.w - 0x3C0000) & D_801D8864.w) >> 16;
        }
        D_800AA248.cur_obj->pos_y.s.hi = 0x46;
        npc->action = 0x63;
        npc->unk_1C = (func_8001EA78() & 0x3F) + 0x78;
        func_8003EB5C(D_800956C4, D_800AA248.cur_obj);
        npc->unk_14 = 0;
        npc->unk_0C = 1;
    } else {
        npc->unk_1C--;
        D_800AA268.p->pos_y.s.hi = 0x258;
    }
}

void func_8003ABE8(Npc *npc) {
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

#ifdef NON_MATCHING
/* 99.85%: 99.85 %: the original ties the sum to the constant (op 2), so the tie with the reloaded D_801F9AC8 (op 1)
 * failed: that load was not a block-local pseudo dying once */
void func_8003AC74(Npc *npc) {
    s32 x;
    u16 t;
    u16 n;

    npc->unk_04++;
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
    if (npc->unk_0C != 0) {
        x = D_800AA268.p->pos_x.w;
        if (func_80039C40(x, 0x50000, 0x50000) != 0) {
            n = npc->aim;
            if (n < 2 && npc->unk_04 >= 0x10) {
                if (n == 0) {
                    func_8001F7CC(0x64, 0x50);
                    func_8004A9B0(0, 5, 0x15, 0, 0);
                    func_8004A9B0(0, 5, 0x16, 0, 0);
                } else {
                    func_8001F7CC(0x64, 0x50);
                    func_8004A9B0(0, 6, 0x15, 0, 0);
                    func_8004A9B0(0, 6, 0x16, 0, 0);
                }
                npc->unk_04 = 0;
            }
        }
        if (func_80039C40(x, 0x320000, 0x320000) != 0) {
            if (x < D_801F9AC8.w) {
                x += D_801D8864.w + 1;
            }
            if (x < D_801F9AC8.w + 0xBE0000 && (D_800AA268.p->flags & 0x10)) {
                func_8003EB5C(D_80095800, D_800AA268.p);
                npc->unk_0C = 0;
            } else if (D_801F9AC8.w + 0xD20000 < x && !(D_800AA268.p->flags & 0x10)) {
                func_8003EB5C(D_800957A4, D_800AA268.p);
                npc->unk_0C = 0;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/npc", func_8003AC74);
#endif

void func_8003AEA0(Npc *npc) {
    if (func_80039C40(D_800AA248.cur_obj->pos_x.w, 0x460000, 0x460000) == 0) {
        if (D_800AA248.cur_obj->flags & 0x10) {
            npc->unk_34 = -0x48000;
            D_800AA248.cur_obj->vel_x.w = 0;
        } else {
            npc->unk_34 = 0x48000;
            D_800AA248.cur_obj->vel_x.w = 0;
        }
    } else {
        npc->action = 2;
        npc->unk_1C = 0x1E;
        npc->unk_34 = 0;
        D_800AA248.cur_obj->vel_x.w = 0;
    }
}

extern u8 D_800956F4[];
extern u8 D_80095720[];

void func_8003AF40(Npc *npc) {
    switch (npc->aim) {
    case 0:
        if (D_800AA248.cur_obj->flags & 0x10) {
            func_8003EB5C(D_80095720, D_800AA248.cur_obj);
            npc->unk_34 = -0x1000;
            D_800AA248.cur_obj->vel_x.w = 0x12000;
        } else {
            func_8003EB5C(D_800956F4, D_800AA248.cur_obj);
            npc->unk_34 = 0x1000;
            D_800AA248.cur_obj->vel_x.w = -0x12000;
        }
        npc->unk_1C = 0x78;
        npc->aim = 1;
        break;
    case 1:
        npc->unk_1C--;
        D_800AA248.cur_obj->pos_y.w += (0xAA0000 - D_800AA248.cur_obj->pos_y.w) >> 4;
        if (D_800AA248.cur_obj->pos_y.w > 0xAA0000) {
            D_800AA248.cur_obj->pos_y.w = 0xAA0000;
        }
        if (npc->unk_1C == 0) {
            npc->aim = 2;
            npc->unk_34 = 0;
        }
        break;
    case 2:
        D_800AA248.cur_obj->pos_y.w -= (D_800AA248.cur_obj->pos_y.w - 0x500000) >> 5;
        D_800AA248.cur_obj->vel_x.w >>= 1;
        if (D_800AA248.cur_obj->pos_y.s.hi < 0x50) {
            D_800AA248.cur_obj->pos_y.w = 0x500000;
            npc->unk_1C = func_8001EA78() & 7;
            npc->action = 2;
            npc->aim = 0;
        }
        break;
    case 3:
        if (--npc->unk_1C == 0) {
            npc->unk_34 = 0;
            D_800AA268.p->vel_x.w = 0;
            npc->action = 2;
            npc->unk_1C = 1;
            npc->aim = 0;
        }
        if (func_80039C98(D_800AA248.cur_obj->pos_x.w, 0x320000, 0x320000) != 0) {
            npc->unk_34 = 0;
            D_800AA248.cur_obj->vel_x.w = 0;
            npc->action = 2;
            npc->unk_1C = 1;
        } else if (D_800AA248.cur_obj->flags & 0x10) {
            npc->unk_34 = 0x1E000;
            D_800AA248.cur_obj->vel_x.w = 0;
        } else {
            npc->unk_34 = -0x1E000;
            D_800AA248.cur_obj->vel_x.w = 0;
        }
        break;
    }
}

void func_8003B1D0(Npc *npc) {
    if (npc->unk_0C != 0) {
        if (npc->unk_1C > 0) {
            npc->unk_1C--;
        }
        if (func_80039C40(D_800AA248.cur_obj->pos_x.w, 0xA0000, 0xA0000) == 0) {
            npc->action = 0x15;
            return;
        }
        if (npc->unk_1C == 0) {
            if (func_80039C98(D_800AA248.cur_obj->pos_x.w, 0x460000, 0x460000) != 0) {
                npc->action = 0x16;
                npc->aim = 0;
                return;
            }
            npc->action = 0x16;
            npc->aim = 3;
            npc->unk_1C = 0x14;
        }
    }
}

void func_8003B294(Npc *npc) {
    u16 action;

    D_800AA248.cur_obj = npc->obj;
    func_80020D20(npc);
    action = npc->action;
    if (action != 0x63 && action != 1) {
        func_8003AC74(npc);
    }
    switch (npc->action) {
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

void func_8003B3C8(Npc *npc) {
    D_800AA248.cur_obj = npc->obj;
    func_80020D20();
    func_8003AC74(npc);
    switch (npc->action) {
    case 1:
    case 0x3B:
        npc->action = 2;
        npc->unk_1C = 0x14;
        break;
    case 3:
        func_8003A328(npc, 0);
        break;
    case 4:
        func_80038800(npc);
        break;
    case 2:
        if (D_800AA248.cur_obj->flags & 0x10) {
            npc->unk_34 = -0x70000;
            D_800AA248.cur_obj->vel_x.w = 0;
        } else {
            npc->unk_34 = 0x70000;
            D_800AA248.cur_obj->vel_x.w = 0;
        }
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
