/* A file of the game's code, named after its first function until its contents are understood: the actors
 * (Actor) and the monsters' behaviour states (Ai) around the game's current mover, D_800AA248.unk_20.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "game.h"

/* A stage's record of its actors: a count, then 0x54-byte entries from 0x98. */
typedef struct ActorList {
    /* 0x00 */ u16 count;
    /* 0x02 */ u8 unk_2[0x96];
    /* 0x98 */ u8 entries[1][0x54];
} ActorList;

typedef struct ActorEntry {
    /* 0x00 */ u8 unk_0[0x18];
    /* 0x18 */ Actor *unk_18;
    /* 0x1C */ u8 unk_1C[0x14];
    /* 0x30 */ Actor *unk_30;
} ActorEntry;

typedef struct ActorPair {
    /* 0x00 */ u8 unk_0[0xC];
    /* 0x0C */ Actor *unk_C;
    /* 0x10 */ u8 unk_10[0x14];
    /* 0x24 */ Actor *unk_24;
} ActorPair;

void func_8001E698(Mover *mover, Anim *anim);
s32 func_8001EB10(s32 arg0, s32 arg1);
void func_8001F724(s32 arg0);
void func_8003C894(Actor *actor);
void func_8003C8D4(Actor *actor);
void func_8004CFC0(void);
void func_80053D68(s32 arg0, Player *player);
void func_80054374(s32 arg0, Player *player);
void func_8005E0E8(Player *player);
s32 func_8005F208(void);
struct AnimFrame *func_8001A784(s32 arg0);

typedef struct AnimFrame {
    /* 0x00 */ u8 unk_0[0x8];
    /* 0x08 */ u16 unk_8;
    /* 0x0A */ u16 unk_A;
} AnimFrame;
void *memset(void *dst, s32 c, u32 n);

void func_8003CD5C(ActorEntry *entry);
void func_8003DAA0(Ai *ai);
s16 func_8003DCC8(Ai *ai);
void func_8003DD44(Ai *ai);
void func_8003DF34(Ai *ai);
void func_8003D71C(Ai *ai);
void func_8003E630(Ai *ai);
void func_8003E764(Ai *ai);
void func_8003EF40(Actor *actor);
void func_8003FE14(Actor *actor);
void func_8003FEE4(Actor *actor);
void func_80041344(u16 arg0, Actor *actor);
void func_800413BC(u16 arg0, Actor *actor);
void func_8003E6A4(Ai *ai);
u16 func_8003EB5C(Anim *anim, Mover *mover);
void func_8003EC40(Actor *actor);
void func_8003F74C(Player *player, Actor *actor);
s16 func_8003FCD8(s32 arg0, s32 arg1);
void func_8003FF0C(s32 vel, s32 kind, Actor *actor);
void func_8004089C(Actor *actor);
void func_8004155C(u16 kind, Actor *actor);
Anim *func_80041598(Actor *actor);
void func_800415B4(void);

extern const AiHandler D_8007DEA0[];
extern s16 D_801D8728;
extern Ai D_801D85C8[];
extern u16 D_801D870C;
extern s16 D_801D8718;
extern s16 D_801D871C;
extern s32 D_801D8864;
extern u16 D_801D8866;
extern u16 D_801D8738;
extern Actor D_801E1E48[];
extern u16 D_801E1C80;
extern u16 D_801E28A4;
extern s16 D_801FA960;
extern Anim D_8008AAFC, D_8008AB4C, D_8008AB80, D_8008ABDC, D_8008AC04, D_8008AC2C, D_8008AC54, D_8008AC7C, D_8008AC98,
    D_8008ACA4, D_8008ACCC, D_8008ACF4, D_8008AD1C, D_8008AD44, D_8008AD60;


void func_8003CD08(ActorList *list) {
    ActorEntry *entry;
    u16 n;

    if (D_801D8738 != 0) {
        n = list->count;
        entry = (ActorEntry *)list->entries;
        do {
            func_8003CD5C(entry);
            entry = (ActorEntry *)((u8 *)entry + 0x54);
        } while (--n != 0);
    }
}

void func_8003CD5C(ActorEntry *entry) {
    Actor *actor;

    actor = entry->unk_18;
    if (actor != NULL) {
        func_8003C894(actor);
    }
    actor = entry->unk_30;
    if (actor != NULL) {
        func_8003C894(actor);
    }
}

void func_8003CDAC(u8 *arg0) {
    ActorPair *pair;
    Actor *actor;

    pair = (ActorPair *)(arg0 + 0xC);
    actor = pair->unk_C;
    if (actor != NULL && actor->unk_4 < 0xB) {
        func_8003C894(actor);
    }
    actor = pair->unk_24;
    if (actor != NULL && actor->unk_4 < 0xB) {
        func_8003C894(actor);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003CE24);

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003CEA0);

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003CFEC);

void func_8003D03C(Actor *actor) {
    if (actor->unk_4 == 2 && actor->unk_E != 0) {
        actor->unk_E = 0;
        func_8001F724(0x6E);
        actor->unk_2A++;
        if (actor->unk_2A >= 5) {
            if (D_801E1C80 >= 0x539) {
                D_801E1C80 = 0x538;
            }
            actor->unk_4 = 6;
            func_8003C8D4(actor);
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003D0D4);

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003D11C);

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003D158);

void *func_8003D1F8(Actor *actor) {
    u8 *p = (u8 *)actor;

    if (actor->unk_4 != 1) {
        if (actor->unk_4 == 2) {
            p -= 0x18;
        } else {
            p -= 0x30;
        }
    }
    return *(void **)(p - 4);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003D228);

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003D30C);

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003D3CC);

void func_8003D490(Actor *actor) {
    if (actor->unk_E != 0) {
        actor->unk_4 = 6;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003D4AC);

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003D51C);

void func_8003D58C(Anim *anim) {
    if (D_800AA248.unk_20->unk_48 != anim) {
        func_8001E698(D_800AA248.unk_20, anim);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003D5C8);

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003D60C);

void func_8003D6C4(void) {
    Ai *ai;
    u16 n;

    if (D_801D870C != 0) {
        ai = D_801D85C8;
        n = 5;
        do {
            func_8003D71C(ai);
            ai++;
        } while (--n != 0);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003D71C);

void func_8003D918(void) {
}

void func_8003D920(Ai *ai) {
    if (func_8003DCC8(ai) != 0) {
        func_8003DAA0(ai);
        return;
    }
    if (ai->unk_C == 1) {
        ai->unk_A = 3;
        ai->unk_C = 0;
        ai->unk_8 = 4;
        func_8003DF34(ai);
    }
}

void func_8003D988(Ai *ai) {
    if (ai->unk_C != 0) {
        func_8003DAA0(ai);
        return;
    }
    if (ai->unk_A != 4) {
        ai->unk_A = 4;
        func_8003DF34(ai);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003D9D8);

void func_8003DA58(Ai *ai) {
    if (func_8003DCC8(ai) != 0 || ai->unk_C == 1) {
        func_8003DAA0(ai);
    }
}

void func_8003DAA0(Ai *ai) {
    func_8003E6A4(ai);
    func_8003DF34(ai);
}

void func_8003DACC(Ai *ai) {
    if (func_8003DCC8(ai) != 0) {
        func_8003DAA0(ai);
        return;
    }
    ai->unk_C = 1;
    ai->unk_22 = 1;
    ai->unk_A = 7;
    ai->unk_8 = 0xF1;
    func_8003DF34(ai);
}

void func_8003DB2C(Ai *ai) {
    if (func_8003DCC8(ai) != 0 || ai->unk_C != 0) {
        func_8003DAA0(ai);
    }
}

void func_8003DB74(Ai *ai) {
    if (func_8003DCC8(ai) != 0) {
        func_8003DAA0(ai);
        return;
    }
    ai->unk_A = 2;
    ai->unk_C = 0;
    ai->unk_8 = 3;
    func_8003DF34(ai);
}

void func_8003DBCC(Ai *ai) {
    if (func_8003DCC8(ai) != 0) {
        func_8003DAA0(ai);
        return;
    }
    if (ai->unk_C == 1) {
        ai->unk_1A = ai->unk_10->unk_6;
        func_8003E630(ai);
        func_8003DD44(ai);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003DC3C);

s16 func_8003DCC8(Ai *ai) {
    AiOrder *order;
    u16 kind;

    order = ai->unk_1C;
    if (order != NULL && ai->unk_28->unk_6 < 2) {
        if (ai->unk_10 != NULL && ai->unk_10->unk_C != 0) {
            return -1;
        }
        kind = order->unk_14;
        if (kind == 0 || kind == 2) {
            return 0;
        }
    }
    return -1;
}

void func_8003DD44(Ai *ai) {
    if (ai->unk_32 == 1) {
        ai->unk_6 = ai->unk_34;
    }
    ai->unk_A = 0;
    ai->unk_8 = 0xA;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003DD70);

void func_8003DF34(Ai *ai) {
    D_8007DEA0[ai->unk_A](ai);
}

void func_8003DF70(void) {
    Ai *ai;
    u16 n;

    ai = D_801D85C8;
    n = 5;
    do {
        func_8003E764(ai);
        ai++;
    } while (--n != 0);
    D_801D8718 = 0;
    D_801D871C = 0;
    D_801D870C = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003DFD4);

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003E1C8);

s32 func_8003E59C(AiOrder *order, Actor *actor, Player *player) {
    s16 limit;

    if (order->unk_8 == 0 && order->unk_14 == 0) {
        if (order->unk_4 == 1) {
            limit = player->unk_24;
        } else if (order->unk_4 == 2) {
            limit = player->unk_28;
        } else {
            limit = player->unk_26;
        }
        if (limit == 0 || (limit != -1 && actor->unk_4 >= limit)) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003E630);

void func_8003E6A4(Ai *ai) {
    AiOrder *order;
    Mover *mover;
    u16 kind;

    order = ai->unk_10;
    if (order != NULL) {
        order->unk_8 = 0;
        kind = ai->unk_22;
        if (kind != 0) {
            order->unk_14 = kind;
        }
    }
    ai->unk_32++;
    mover = ai->unk_0;
    ai->unk_22 = 0;
    ai->unk_36 = 0;
    ai->unk_A = 0;
    ai->unk_10 = NULL;
    ai->unk_1C = 0;
    ai->unk_14 = NULL;
    ai->unk_38 = 0;
    ai->unk_C = 0;
    ((s16 *)&mover->unk_14)[1] = -0x190;
    ((s16 *)&mover->unk_18)[1] = -0x190;
    mover->unk_C = 0;
    mover->unk_10 = 0;
    ai->unk_8 = 1;
    if (func_8005F208() == 3) {
        ai->unk_18 = 0;
        ai->unk_2E = 0;
        return;
    }
    ai->unk_18 = func_8001EB10(0x258, 0x168);
}

void func_8003E764(Ai *ai) {
    memset(ai, 0, sizeof(Ai));
}

void func_8003E788(Ai *ai) {
    ai->unk_10->unk_8 = 0;
    ai->unk_10 = NULL;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003E79C);

void func_8003E830(void) {
    if (D_801FA960 >= 0x5E && D_801FA960 != 0x63 && D_801D8728 == 0) {
        func_8003EB5C(&D_8008ACA4, D_800AA248.unk_20);
    } else {
        func_8003EB5C(&D_8008ABDC, D_800AA248.unk_20);
    }
}

void func_8003E89C(void) {
    if (D_801FA960 >= 0x5E && D_801FA960 != 0x63 && D_801D8728 == 0) {
        func_8003EB5C(&D_8008AD60, D_800AA248.unk_20);
    } else {
        func_8003EB5C(&D_8008AC98, D_800AA248.unk_20);
    }
}

void func_8003E908(void) {
    if (D_801FA960 >= 0x5E && D_801FA960 != 0x63 && D_801D8728 == 0) {
        func_8003EB5C(&D_8008ACCC, D_800AA248.unk_20);
    } else {
        func_8003EB5C(&D_8008AC04, D_800AA248.unk_20);
    }
}

void func_8003E974(void) {
    if (D_801FA960 >= 0x5E && D_801FA960 != 0x63 && D_801D8728 == 0) {
        func_8003EB5C(&D_8008ACF4, D_800AA248.unk_20);
    } else {
        func_8003EB5C(&D_8008AC2C, D_800AA248.unk_20);
    }
}

void func_8003E9E0(void) {
    if (D_801FA960 >= 0x5E && D_801FA960 != 0x63 && D_801D8728 == 0) {
        func_8003EB5C(&D_8008AD44, D_800AA248.unk_20);
    } else {
        func_8003EB5C(&D_8008AC7C, D_800AA248.unk_20);
    }
}

void func_8003EA4C(void) {
    if (D_801FA960 >= 0x5E && D_801FA960 != 0x63 && D_801D8728 == 0) {
        func_8003EB5C(&D_8008AD1C, D_800AA248.unk_20);
    } else {
        func_8003EB5C(&D_8008AC54, D_800AA248.unk_20);
    }
}

void func_8003EAB8(Ai *ai) {
    Anim *anim;

    if (ai->unk_C == 0) {
        if (func_8001EB10(0x8000, 0) & 1) {
            anim = &D_8008AB4C;
        } else {
            anim = &D_8008AB80;
        }
        func_8003EB5C(anim, D_800AA248.unk_20);
    }
}

void func_8003EB14(void) {
    func_8003EB5C(&D_8008AAFC, D_800AA248.unk_20);
}

void func_8003EB40(void) {
    D_800AA248.unk_20->unk_90->unk_C = 1;
}

u16 func_8003EB5C(Anim *anim, Mover *mover) {
    if (anim == mover->unk_48) {
        D_800AA248.unk_7A = 1;
        mover->unk_22 |= 0x800;
    } else {
        mover->unk_48 = anim;
        mover->unk_44 = anim;
        mover->unk_4C = 0;
        mover->unk_4D = 0;
        mover->unk_64 = 0;
        mover->unk_22 |= 0x800;
        D_800AA248.unk_7A = 0;
    }
    return D_800AA248.unk_7A;
}

void func_8003EBC0(void) {
    Actor *actor;
    Mover *saved;
    u16 n;

    actor = D_801E1E48;
    n = D_801E28A4;
    saved = D_800AA248.unk_20;
    if (n != 0) {
        if (n >= 0xD) {
            n = 0xC;
        }
        do {
            func_8003EC40(actor);
            actor++;
        } while (--n != 0);
    }
    D_800AA248.unk_20 = saved;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003EC40);

void func_8003ECF8(void) {
    Actor *actor;
    u16 n;

    actor = D_801E1E48;
    n = 0xC;
    do {
        func_8003EF40(actor);
        actor++;
    } while (--n != 0);
    D_801E28A4 = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003ED4C);

void func_8003EF40(Actor *actor) {
    memset(actor, 0, sizeof(Actor));
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003EF64);

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003F114);

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003F150);

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003F378);

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003F4A8);

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003F50C);

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003F74C);

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003FB5C);

s32 func_8003FC30(Player *player, Actor *actor) {
    if (actor->unk_14 == 0) {
        func_8003F74C(player, actor);
    }
    player->unk_18A = 1;
    return 1;
}

void func_8003FC70(s16 *dx, s16 *dy, Mover *from, Mover *to) {
    if (from == NULL || to == NULL) {
        *dx = 0xA;
        *dy = 0xC;
        return;
    }
    *dy = ((u16 *)&to->unk_18)[1] - ((u16 *)&from->unk_18)[1];
    *dx = func_8003FCD8(((s16 *)&to->unk_14)[1], ((s16 *)&from->unk_14)[1]);
}

s16 func_8003FCD8(s32 arg0, s32 arg1) {
    u16 wrap;
    s16 d;
    s16 half;
    s16 r;

    wrap = D_801D8866;
    d = arg0 - arg1;
    half = (s16)wrap >> 1;
    r = d;
    if (d >= 0) {
        if (d >= half) {
            r = d - wrap;
        }
    } else if (-half >= d) {
        r = wrap + d;
    }
    return r;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003FD30);

void func_8003FE14(Actor *actor) {
    actor->unk_E = 0;
    func_8003FF0C(0, 9, actor);
}

void func_8003FE40(Actor *actor) {
    actor->unk_8 = 1;
    func_8003FF0C(0, 0xC, actor);
}

void func_8003FE70(Actor *actor) {
    if (actor->unk_E != 0) {
        if (D_800AA248.unk_4 != 0) {
            func_8003FE14(actor);
            return;
        }
        func_8003FEE4(actor);
        return;
    }
    actor->unk_8 = 0;
    actor->unk_E = 1;
    func_8003FF0C(0x20000, 0xD, actor);
}

void func_8003FEE4(Actor *actor) {
    func_8003FF0C(0, 0xC, actor);
}

void func_8003FF0C(s32 vel, s32 kind, Actor *actor) {
    if (!(D_800AA248.unk_20->unk_22 & 0x10)) {
        vel = -vel;
    }
    D_800AA248.unk_20->unk_C = vel;
    func_8004155C(kind, actor);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003FF54);

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8004003C);

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_800401AC);

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8004022C);

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_80040294);

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_80040314);

void func_800403B4(Actor *actor) {
    Mover *saved;

    saved = D_800AA248.unk_20;
    D_800AA248.unk_20 = actor->unk_0;
    if (actor->unk_34 == NULL || actor->unk_34->unk_10 != 0) {
        func_8004155C(2, actor);
    }
    D_800AA248.unk_20 = saved;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_80040418);

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_800405D8);

void func_80040668(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_80040670);

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_80040704);

void func_80040824(Actor *actor) {
    D_800AA248.unk_20 = actor->unk_0;
    if (actor->unk_28 == 0) {
        if (actor->unk_34 == NULL || actor->unk_34->unk_10 != 0) {
            func_8004155C(2, actor);
        }
    } else {
        func_8004089C(actor);
        func_8004155C(2, actor);
    }
}

void func_8004089C(Actor *actor) {
    Player *player;
    s32 n;

    player = actor->unk_2C;
    if (player != NULL) {
        n = 0x5A;
        if (player->unk_1AC == 0) {
            n = 0x1E;
        }
        func_80054374(n, player);
        func_8005E0E8(player);
        func_80053D68(8, player);
        player->unk_5A = 8;
    }
}

void func_80040900(Actor *actor) {
    Mover *mover;

    mover = actor->unk_0;
    D_800AA248.unk_20 = mover;
    mover->unk_18 = 0x02000000;
    func_800415B4();
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_80040930);

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_800409CC);

void func_80040A7C(Actor *actor) {
    Mover *mover;

    mover = actor->unk_0;
    D_800AA248.unk_20 = mover;
    if (actor->unk_28 != 0) {
        mover->unk_18 = 0x02000000;
        func_800415B4();
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_80040AB8);

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_80040B00);

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_80040B94);

void func_80040BE4(void) {
}

void func_80040BEC(void) {
    if (!(D_800AA248.unk_20->unk_6C & 0x80)) {
        func_8001F724(0x13);
    }
}

void func_80040C28(void) {
    if (!(D_800AA248.unk_20->unk_6C & 0x80)) {
        func_8001F724(6);
    }
}

void func_80040C64(void) {
    if (!(D_800AA248.unk_20->unk_6C & 0x80)) {
        func_8001F724(0);
    }
}

void func_80040CA0(void) {
}

void func_80040CA8(void) {
}

void func_80040CB0(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_80040CB8);

/* 99.2%: the mover pointer and the frame's offsets get a0/a1 in the other order around the x/y adjustment */
#ifdef NON_MATCHING
void func_80040D68(Actor *actor) {
    Mover *saved;
    AnimFrame *frame;
    s32 x;
    s32 y;

    saved = D_800AA248.unk_20;
    D_800AA248.unk_20 = actor->unk_0;
    if (actor->unk_30 == 0) {
        if (actor->unk_28 != 0) {
            actor->unk_32++;
            actor->unk_30 = 0x3C;
            func_80041344(actor->unk_32, actor);
            if (actor->unk_32 >= 4) {
                x = ((u16 *)&D_800AA248.unk_20->unk_1C)[0];
                y = ((u16 *)&D_800AA248.unk_20->unk_1C)[1];
                func_8004155C(2, actor);
                frame = func_8001A784(*(s32 *)D_800AA248.unk_20->unk_48);
                x = frame->unk_8 - x;
                ((u16 *)&D_800AA248.unk_20->unk_14)[1] += x;
                y = frame->unk_A - y;
                ((u16 *)&D_800AA248.unk_20->unk_18)[1] += y;
            }
        }
    }
    if (actor->unk_30 != 0) {
        actor->unk_30--;
    }
    actor->unk_28 = 0;
    D_800AA248.unk_20 = saved;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_80040D68);
#endif

void func_80040EA0(Actor *actor) {
    Mover *mover;
    Mover *saved;

    mover = actor->unk_0;
    saved = D_800AA248.unk_20;
    D_800AA248.unk_20 = mover;
    if (mover->unk_6C & 0x80) {
        if (actor->unk_16 != 0) {
            func_800415B4();
            D_800AA248.unk_20 = saved;
            return;
        }
    } else {
        actor->unk_16 = 1;
    }
    D_800AA248.unk_20->unk_14 = D_801D8864 & (D_800AA248.unk_20->unk_C + D_800AA248.unk_20->unk_14);
    if (actor->unk_30 == 0) {
        if (actor->unk_28 != 0) {
            actor->unk_30 = 0x3C;
            actor->unk_32++;
            if (actor->unk_32 != 0) {
                func_8004155C(2, actor);
            }
        }
    }
    D_800AA248.unk_20 = saved;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_80040F84);

void func_800410AC(Actor *actor) {
    Mover *mover;
    Mover *saved;

    mover = actor->unk_0;
    saved = D_800AA248.unk_20;
    D_800AA248.unk_20 = mover;
    if (mover->unk_6C & 0x80) {
        if (actor->unk_16 != 0) {
            func_800415B4();
            D_800AA248.unk_20 = saved;
            return;
        }
    } else {
        actor->unk_16 = 1;
    }
    D_800AA248.unk_20->unk_14 = D_801D8864 & (D_800AA248.unk_20->unk_C + D_800AA248.unk_20->unk_14);
    if (actor->unk_30 == 0) {
        if (actor->unk_28 != 0) {
            actor->unk_32++;
            actor->unk_30 = 0x3C;
            func_800413BC(actor->unk_32, actor);
            actor->unk_2C->unk_204++;
            if (actor->unk_32 != 0) {
                func_8004155C(2, actor);
            }
        }
    }
    if (actor->unk_30 != 0) {
        actor->unk_30--;
    }
    actor->unk_28 = 0;
    D_800AA248.unk_20 = saved;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_800411E8);

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_80041344);

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_800413BC);

void func_80041434(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8004143C);

void func_8004155C(u16 kind, Actor *actor) {
    Anim *anim;

    actor->unk_6 = kind;
    anim = func_80041598(actor);
    if (anim != NULL) {
        func_8003EB5C(anim, D_800AA248.unk_20);
    }
}

Anim *func_80041598(Actor *actor) {
    Anim **anims;

    anims = actor->unk_24;
    anims += actor->unk_6;
    return *anims;
}

void func_800415B4(void) {
    D_800AA248.unk_20->unk_90->unk_4 = 0;
    func_8004CFC0();
}

void func_800415E0(Actor *actor) {
    D_800AA248.unk_20 = actor->unk_0;
    actor->unk_4 = 0;
    func_8004CFC0();
}
