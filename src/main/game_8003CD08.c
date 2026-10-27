/* A file of the game's code, named after its first function until its contents are understood: the actors
 * (Actor) and the monsters' behaviour states (Ai) around the game's current mover, D_800AA248.unk_20.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "game.h"
#include "game_80034590.h"

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

void func_8001E698(GameObject *mover, Anim *anim);
s32 func_8001EB10(s32 arg0, s32 arg1);
void func_8001F724(s32 arg0);
void func_8003C894(Actor *actor);
void func_8003C8D4(Actor *actor);
void func_8004CFC0(void);
void func_80053D68(s32 arg0, Monster *player);
void func_80054374(s32 arg0, Monster *player);
void func_8005E0E8(Monster *player);
s32 func_8005F208(void);
struct AnimFrame *func_8001A784(s32 arg0);

typedef struct AnimFrame {
    /* 0x00 */ u8 unk_0[0x8];
    /* 0x08 */ u16 unk_8;
    /* 0x0A */ u16 unk_A;
} AnimFrame;
void *memset(void *dst, s32 c, u32 n);
s32 abs(s32 x);                 /* GCC's builtin: inlined */

void func_8003CD5C(ActorEntry *entry);
void *func_8003D1F8(Actor *actor);
void func_8003D490(Actor *actor);
void func_8003D58C(Anim *anim);
void func_8003DAA0(Ai *ai);
s16 func_8003DCC8(Ai *ai);
void func_8003DD44(Ai *ai);
void func_8003DF34(Ai *ai);
void func_8003D71C(Ai *ai);
void func_8003E630(Ai *ai);
void func_8003E764(Ai *ai);
void func_8003EF40(Actor *actor);
void func_8003FE14(Actor *actor);
void func_8003FE40(Actor *actor);
void func_8003FE70(Actor *actor);
void func_8003FD30(Actor *actor);
void func_80029D1C(void);
u16 *func_80025C08(void *list);
ActorLink *func_8002F01C(void);
void func_8003ECF8(void);

/* What an actor of a kind is made of: its effect, its kind, its handlers and animations (0x14 bytes, D_80082138[]). */
typedef struct ActorDef {
    /* 0x00 */ EffectDef *unk_0;
    /* 0x04 */ u16 unk_4;
    /* 0x06 */ u8 unk_6[0x2];
    /* 0x08 */ void (**unk_8)(Actor *);
    /* 0x0C */ Anim **unk_C;
    /* 0x10 */ u16 unk_10;
    /* 0x12 */ u16 unk_12;
} ActorDef;
void func_8001F7CC(s32 a, s32 b);
u16 func_8003712C(s16 x, s16 y, Monster *player);
void func_800415E0(Actor *actor);
void func_8003D4AC(Ai *ai);
void func_8003FEE4(Actor *actor);
void func_80041344(u16 arg0, Actor *actor);
void func_80024964(s32 arg0, GameObject *mover);
void func_8001E2F8(GameObject *mover);
void func_8001E39C(GameObject *mover);
void func_80053C50(s32 arg0, Monster *player);
void func_80061068(s32 arg0, s16 arg1, s16 arg2);
void func_8001E4B0(GameObject *mover);
void func_8003F150(void);
void func_80030338(GameObject *mover);
ObjectDef *func_8001D110(void);
GameObject *func_8001DCB4(void);       /* spawns D_800AA248.unk_3C */
void func_8004003C(s32 arg0, Ai *link);
s16 func_80053AC4(s16 x, s16 y, s32 w, s32 h, Monster *player);
void func_8003CCC0(Ai *link);
void func_80040B94(Actor *actor);
void func_800634D4(Monster *player, s32 arg1);

/* A sound and an argument per kind of actor hit (the file's .data). */
typedef struct ActorSound {
    /* 0x00 */ s32 unk_0;
    /* 0x04 */ u16 unk_4;
    /* 0x06 */ u8 unk_6[0x2];
} ActorSound;

/* A 0x18-byte slot of an actor list entry, holding an actor at 0xC: two per entry, at 0xC and 0x24. */
typedef struct ActorSlot {
    /* 0x00 */ u8 unk_0[0xC];
    /* 0x0C */ Actor *unk_C;
    /* 0x10 */ u8 unk_10[0x8];
} ActorSlot;
void func_800413BC(u16 arg0, Actor *actor);
void func_8003E6A4(Ai *ai);
u16 func_8003EB5C(Anim *anim, GameObject *mover);
void func_8003EC40(Actor *actor);
void func_8003F74C(Monster *player, Actor *actor);
s16 func_8003FCD8(s32 arg0, s32 arg1);
void func_8003FF0C(s32 vel, s32 kind, Actor *actor);
void func_8004089C(Actor *actor);
void func_8004155C(u16 kind, Actor *actor);
Anim *func_80041598(Actor *actor);
void func_800415B4(void);

extern const AiHandler D_8007DEA0[];
extern ActorSound D_8007E1FC[];
extern void (*D_8007E1E4[])(Actor *actor);
extern Anim D_80094AEC;
extern Anim D_80094514;
extern ActorDef D_80082138[];
extern u8 D_8007FFB0[];
extern u16 D_801D36FC;        /* the game mode */
extern u16 D_801D37B8;
extern u16 D_801D87B4;
extern EffectDef D_8009556C;
extern s16 D_801D8728;
extern s16 D_801D8718;
extern s16 D_801D871C;
extern s32 D_801D8864;
extern u16 D_801D8866;
extern u16 D_801D8738;
extern Actor D_801E1E48[];
extern u16 D_801E1C80;
extern u16 D_801E28A4;
extern s16 D_801FA960;
extern Anim D_80094350;
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

void func_8003CE24(Actor *actor, ObjectDef *effect) {
    GameObject *mover;
    SpriteFrame *frame;
    u8 *p;

    if (actor->unk_4 == 1) {
        p = (u8 *)actor - 0xC;
    } else {
        p = (u8 *)actor - 0x24;
    }
    mover = *(GameObject **)p;
    frame = mover->frame;
    switch (actor->unk_4) {
    case 2:
        effect->pos_x.s.hi = ((u16 *)&mover->pos_x.w)[1] + frame->unk_1C;
        effect->pos_y.s.hi = ((u16 *)&mover->pos_y.w)[1] + frame->unk_1E;
        break;
    default:
        effect->pos_x.s.hi = ((u16 *)&mover->pos_x.w)[1] + frame->unk_14;
        effect->pos_y.s.hi = ((u16 *)&mover->pos_y.w)[1] + frame->unk_16;
        break;
    }
}

void func_8003CEA0(Anim *anim, GameObject *mover) {
    Actor *actor;
    GameObject *o;

    if (mover->unk_48 != anim) {
        if (*(u16 *)&mover->unk_80 == 0) {
            mover->unk_80 = ((AnimFrame *)func_8003D1F8(mover->owner.ai->unk_10.actor))->unk_8 - 1;
        }
        func_80024964(0, mover);
        func_8001E698(mover, anim);
        actor = mover->owner.ai->unk_10.actor;
        if (actor->unk_4 == 1) {
            o = *(GameObject **)((u8 *)actor - 0xC);
            ((u16 *)&mover->pos_x.w)[1] = ((u16 *)&o->pos_x.w)[1] + o->frame->unk_10;
            ((u16 *)&mover->pos_y.w)[1] = ((u16 *)&o->pos_y.w)[1] + o->frame->unk_12;
        } else if (actor->unk_4 == 2) {
            o = *(GameObject **)((u8 *)actor - 0x24);
            ((u16 *)&mover->pos_x.w)[1] = ((u16 *)&o->pos_x.w)[1] + o->frame->unk_20;
            ((u16 *)&mover->pos_y.w)[1] = ((u16 *)&o->pos_y.w)[1] + o->frame->unk_22;
        } else {
            o = *(GameObject **)((u8 *)actor - 0x3C);
            ((u16 *)&mover->pos_x.w)[1] = ((u16 *)&o->pos_x.w)[1] + o->frame->unk_18;
            ((u16 *)&mover->pos_y.w)[1] = ((u16 *)&o->pos_y.w)[1] + o->frame->unk_1A;
        }
    }
}

void func_8003CFEC(void) {
    GameObject *mover = D_800AA268.p;
    u16 *info = mover->arg.h;

    if (!(mover->unk_6C & 0x80) && D_801D36FC != 0x220) {
        func_8001F724(*info);
    }
}

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

void func_8003D0D4(Actor *actor) {
    if (actor->unk_4 == 2) {
        func_8003D490(actor);
    } else if (actor->unk_4 == 6) {
        func_8003C8D4(actor);
    }
}

void func_8003D11C(Ai *ai) {
    s32 k = ai->kind;

    if (k < 0x3B) {
        if (k >= 0x36) {
            if (ai->unk_0E != 0) {
                ai->unk_18 = 0x28;
                ai->unk_0E = 0;
            }
        }
    }
}

void func_8003D158(GameObject *mover) {
    s32 v;

    v = mover->vel_x.w;
    if (v != 0) {
        if (abs(v) <= 0x20000) {
            mover->vel_x.w = v + mover->unk_84;
        }
        mover->pos_x.w += mover->vel_x.w;
    }
    v = mover->vel_y.w;
    if (v != 0) {
        if (abs(v) <= 0x30000) {
            mover->vel_y.w = v + mover->unk_88;
        }
        mover->pos_y.w += mover->vel_y.w;
    }
}

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

void func_8003D228(Npc *npc) {
    Anim *anim = NULL;

    switch (npc->unk_6) {
    case 0x2A:
        anim = &D_80094514;
        if (npc->unk_4 < 2) {
            return;
        }
        break;
    case 0x27:
    case 0x28:
    case 0x29:
    case 0x2B:
    case 0x2C:
        npc->unk_4 = 3;
        break;
    default:
        return;
    }
    if (npc->unk_E != 0) {
        npc->unk_8 = 3;
        npc->unk_18 = 0x34;
        npc->unk_E = 0;
        npc->unk_14 = NULL;
        if (npc->unk_4 != 3) {
            func_8001F7CC(0xC8, 0x2F);
            npc->unk_4 = 3;
            npc->unk_18 = -1;
            if (anim != NULL) {
                func_8003D58C(anim);
            }
        }
    }
}

void func_8003D30C(Npc *npc) {
    switch (npc->unk_6) {
    case 0x34:
        if (npc->unk_E != 0 && npc->unk_14 != NULL) {
            func_8001F724(0x11);
            npc->unk_14->unk_8 = 0x440000;
            func_8003C8D4((Actor *)npc);
            npc->unk_1C = 0;
        }
        break;
    case 0x35:
        if (npc->unk_E != 0 && npc->unk_14 != NULL) {
            func_8001F724(0x11);
            npc->unk_14->unk_10 = 0x440000;
            func_8003C8D4((Actor *)npc);
            npc->unk_1C = 0;
        }
        break;
    }
}

void func_8003D3CC(Npc *npc) {
    Anim *anim = NULL;

    switch (npc->unk_6) {
    case 0x2F:
        anim = &D_80094AEC;
        if (npc->unk_4 < 2) {
            return;
        }
        break;
    case 0x2D:
    case 0x2E:
    case 0x30:
        npc->unk_4 = 3;
        break;
    default:
        return;
    }
    if (npc->unk_E != 0) {
        npc->unk_E = 0;
        npc->unk_14 = NULL;
        if (npc->unk_4 == 3) {
            func_8003D4AC((Ai *)npc);
        } else {
            npc->unk_4 = 3;
            npc->unk_8 = 6;
            if (anim != NULL) {
                func_8003D58C(anim);
            }
        }
    }
}

void func_8003D490(Actor *actor) {
    if (actor->unk_E != 0) {
        actor->unk_4 = 6;
    }
}

void func_8003D4AC(Ai *ai) {
    ai->action = 6;
    D_800AA248.cur_obj->unk_80 = 0xF00;
    if (ai->unk_10.order->unk_4 == 2) {
        D_800AA248.cur_obj->flags |= 0x10;
    }
    func_8003D58C(&D_80094350);
}

void func_8003D51C(Ai *ai) {
    switch ((u16)ai->action) {
    case 1:
        ai->action = 0;
        break;
    case 3:
    case 6:
        ai->action = 2;
        break;
    case 9:
        ai->action = 6;
        break;
    case 8:
        ai->action = 7;
        break;
    case 5:
    case 10:
        ai->action = 5;
        break;
    }
}

void func_8003D58C(Anim *anim) {
    if (D_800AA248.cur_obj->unk_48 != anim) {
        func_8001E698(D_800AA248.cur_obj, anim);
    }
}

void func_8003D5C8(void) {
    func_8003CCC0(D_800AA248.cur_obj->owner.ai);
    func_8001E4B0(D_800AA248.cur_obj);
}

void func_8003D60C(ActorList *list) {
    u8 *entry;
    ActorSlot *slot;
    Actor *actor;
    u16 n;

    if (D_801D8738 != 0) {
        n = list->count;
        entry = (u8 *)list->entries;
        do {
            slot = (ActorSlot *)(entry + 0xC);
            actor = slot->unk_C;
            if (actor != NULL && actor->unk_1C == 3 && actor->unk_4 >= 9) {
                actor->unk_4 = 0x12;
                slot->unk_C = NULL;
            }
            slot++;
            actor = slot->unk_C;
            if (actor != NULL && actor->unk_1C == 3 && actor->unk_4 >= 9) {
                actor->unk_4 = 0x12;
                slot->unk_C = NULL;
            }
            entry += 0x54;
        } while (--n != 0);
    }
}

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
    if (ai->unk_0C == 1) {
        ai->state = 3;
        ai->unk_0C = 0;
        ai->action = 4;
        func_8003DF34(ai);
    }
}

void func_8003D988(Ai *ai) {
    if (ai->unk_0C != 0) {
        func_8003DAA0(ai);
        return;
    }
    if (ai->state != 4) {
        ai->state = 4;
        func_8003DF34(ai);
    }
}

void func_8003D9D8(Ai *ai) {
    if (ai->unk_0C != 0) {
        func_8003DAA0(ai);
        return;
    }
    if (ai->state != 5) {
        ai->state = 5;
        func_8003DF34(ai);
        D_800AA248.cur_obj->unk_80 = 0x390;
        func_8001E39C(D_800AA248.cur_obj);
        func_8001E2F8(D_800AA248.cur_obj);
    }
}

void func_8003DA58(Ai *ai) {
    if (func_8003DCC8(ai) != 0 || ai->unk_0C == 1) {
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
    ai->unk_0C = 1;
    ai->unk_22 = 1;
    ai->state = 7;
    ai->action = 0xF1;
    func_8003DF34(ai);
}

void func_8003DB2C(Ai *ai) {
    if (func_8003DCC8(ai) != 0 || ai->unk_0C != 0) {
        func_8003DAA0(ai);
    }
}

void func_8003DB74(Ai *ai) {
    if (func_8003DCC8(ai) != 0) {
        func_8003DAA0(ai);
        return;
    }
    ai->state = 2;
    ai->unk_0C = 0;
    ai->action = 3;
    func_8003DF34(ai);
}

void func_8003DBCC(Ai *ai) {
    if (func_8003DCC8(ai) != 0) {
        func_8003DAA0(ai);
        return;
    }
    if (ai->unk_0C == 1) {
        ai->unk_1A = ai->unk_10.order->unk_6;
        func_8003E630(ai);
        func_8003DD44(ai);
    }
}

s32 func_8003DC3C(Ai *ai) {
    u16 k;

    if (func_8005F208() == 3) {
        return 1;
    }
    k = ai->unk_1C.order->unk_14;
    if (k != 0 && k != 2 && k != 3) {
        return -1;
    }
    if (ai->unk_1A != ai->unk_10.order->unk_6) {
        return 1;
    }
    if (ai->unk_28.link->unk_6 != 2) {
        return 0;
    }
    return -1;
}

s16 func_8003DCC8(Ai *ai) {
    AiOrder *order;
    u16 kind;

    order = ai->unk_1C.order;
    if (order != NULL && ai->unk_28.link->unk_6 < 2) {
        if (ai->unk_10.order != NULL && ai->unk_10.order->unk_C != 0) {
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
    if (ai->unk_30.u.hi == 1) {
        ai->kind = ai->unk_34.u.lo;
    }
    ai->state = 0;
    ai->action = 0xA;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003DD70);

void func_8003DF34(Ai *ai) {
    D_8007DEA0[ai->state](ai);
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

s32 func_8003E59C(AiOrder *order, Actor *actor, Monster *player) {
    s16 limit;

    if (order->unk_8 == 0 && order->unk_14 == 0) {
        if (order->unk_4 == 1) {
            limit = player->unk_024;
        } else if (order->unk_4 == 2) {
            limit = player->unk_028;
        } else {
            limit = player->unk_026;
        }
        if (limit == 0 || (limit != -1 && actor->unk_4 >= limit)) {
            return 1;
        }
    }
    return 0;
}

#ifdef NON_MATCHING
/* 89.31 %: the loop's exit by count undoes the last i++ (addiu a1,a1,-1 after the loop) and the bound 8 sits in a register; the loop shape is right */
void func_8003E630(Ai *ai) {
    Monster *player;
    u16 i;
    u16 n;
    u16 max = 8;

    n = 8;
    i = ai->unk_04 + 1;
    do {
        if (i >= max) {
            i = 1;
        }
        player = &D_801E0B78[i];
        if (player->unk_058 & 1) {
            break;
        }
        i++;
    } while (--n != 0);
    ai->unk_14 = (Monster *)player;
    ai->unk_04 = i;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003E630);
#endif

void func_8003E6A4(Ai *ai) {
    AiOrder *order;
    GameObject *mover;
    u16 kind;

    order = ai->unk_10.order;
    if (order != NULL) {
        order->unk_8 = 0;
        kind = ai->unk_22;
        if (kind != 0) {
            order->unk_14 = kind;
        }
    }
    ai->unk_30.u.hi++;
    mover = ai->obj;
    ai->unk_22 = 0;
    ai->unk_34.s.hi = 0;
    ai->state = 0;
    ai->unk_10.order = NULL;
    ai->unk_1C.order = 0;
    ai->unk_14 = NULL;
    ai->unk_38 = 0;
    ai->unk_0C = 0;
    ((s16 *)&mover->pos_x.w)[1] = -0x190;
    ((s16 *)&mover->pos_y.w)[1] = -0x190;
    mover->vel_x.w = 0;
    mover->vel_y.w = 0;
    ai->action = 1;
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
    ai->unk_10.order->unk_8 = 0;
    ai->unk_10.order = NULL;
}

#ifdef NON_MATCHING
/* 73.78 %: the success block is placed after the fail block in the original (an if/else whose fail arm is the fallthrough) and the result is copied through v1 before the store */
s32 func_8003E79C(void) {
    s16 x;

    if (D_801D37B8 != 0) {
        x = ((s16 *)&D_800AA248.cur_obj->pos_x.w)[1];
        if (x >= D_801D37B8 && x <= D_801D87B4) {
            D_800AA248.unk_4C = 0;
            D_800AA248.unk_78 = 1;
            return 1;
        }
    }
    func_80030338(D_800AA248.cur_obj);
    D_800AA248.unk_78 = 0;
    return 0;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003E79C);
#endif

void func_8003E830(void) {
    if (D_801FA960 >= 0x5E && D_801FA960 != 0x63 && D_801D8728 == 0) {
        func_8003EB5C(&D_8008ACA4, D_800AA248.cur_obj);
    } else {
        func_8003EB5C(&D_8008ABDC, D_800AA248.cur_obj);
    }
}

void func_8003E89C(void) {
    if (D_801FA960 >= 0x5E && D_801FA960 != 0x63 && D_801D8728 == 0) {
        func_8003EB5C(&D_8008AD60, D_800AA248.cur_obj);
    } else {
        func_8003EB5C(&D_8008AC98, D_800AA248.cur_obj);
    }
}

void func_8003E908(void) {
    if (D_801FA960 >= 0x5E && D_801FA960 != 0x63 && D_801D8728 == 0) {
        func_8003EB5C(&D_8008ACCC, D_800AA248.cur_obj);
    } else {
        func_8003EB5C(&D_8008AC04, D_800AA248.cur_obj);
    }
}

void func_8003E974(void) {
    if (D_801FA960 >= 0x5E && D_801FA960 != 0x63 && D_801D8728 == 0) {
        func_8003EB5C(&D_8008ACF4, D_800AA248.cur_obj);
    } else {
        func_8003EB5C(&D_8008AC2C, D_800AA248.cur_obj);
    }
}

void func_8003E9E0(void) {
    if (D_801FA960 >= 0x5E && D_801FA960 != 0x63 && D_801D8728 == 0) {
        func_8003EB5C(&D_8008AD44, D_800AA248.cur_obj);
    } else {
        func_8003EB5C(&D_8008AC7C, D_800AA248.cur_obj);
    }
}

void func_8003EA4C(void) {
    if (D_801FA960 >= 0x5E && D_801FA960 != 0x63 && D_801D8728 == 0) {
        func_8003EB5C(&D_8008AD1C, D_800AA248.cur_obj);
    } else {
        func_8003EB5C(&D_8008AC54, D_800AA248.cur_obj);
    }
}

void func_8003EAB8(Ai *ai) {
    Anim *anim;

    if (ai->unk_0C == 0) {
        if (func_8001EB10(0x8000, 0) & 1) {
            anim = &D_8008AB4C;
        } else {
            anim = &D_8008AB80;
        }
        func_8003EB5C(anim, D_800AA248.cur_obj);
    }
}

void func_8003EB14(void) {
    func_8003EB5C(&D_8008AAFC, D_800AA248.cur_obj);
}

void func_8003EB40(void) {
    D_800AA248.cur_obj->owner.ai->unk_0C = 1;
}

u16 func_8003EB5C(Anim *anim, GameObject *mover) {
    if (anim == mover->unk_48) {
        D_800AA248.unk_7A = 1;
        mover->flags |= 0x800;
    } else {
        mover->unk_48 = anim;
        mover->script_pc = anim;
        mover->unk_4C = 0;
        mover->unk_4D = 0;
        mover->unk_64 = 0;
        mover->flags |= 0x800;
        D_800AA248.unk_7A = 0;
    }
    return D_800AA248.unk_7A;
}

void func_8003EBC0(void) {
    Actor *actor;
    GameObject *saved;
    u16 n;

    actor = D_801E1E48;
    n = D_801E28A4;
    saved = D_800AA248.cur_obj;
    if (n != 0) {
        if (n >= 0xD) {
            n = 0xC;
        }
        do {
            func_8003EC40(actor);
            actor++;
        } while (--n != 0);
    }
    D_800AA248.cur_obj = saved;
}

void func_8003EC40(Actor *actor) {
    void (**p)(Actor *);
    void (*handler)(Actor *);

    D_800AA268.p = actor->unk_0;
    func_80029D1C();
    if (actor->unk_4 == 0) {
        return;
    }
    if ((u16)actor->unk_6 >= 0x11) {
        goto bad;
    }
    /* FAKE: the table and the index in one comma expression; the plain p[actor->unk_6] gives the kind another register
     * (a0 for v1), the only difference (99.2 %). */
    handler = *(p = actor->unk_20, p + actor->unk_6);
    if (handler == NULL) {
        return;
    }
    handler(actor);
    if (actor->unk_4 == 0) {
        return;
    }
    if ((u16)actor->unk_6 < 0x11) {
        goto ok;
    }
bad:
    func_800415E0(actor);
    return;
ok:
    func_8004155C(actor->unk_6, actor);
}

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

void func_8003ED4C(void) {
    u16 *p;
    u16 n;
    Actor *actor;
    ActorDef *def;
    ObjectDef *effect;
    ActorLink *link;
    EffectDef *ed;
    u16 kind;
    u16 y;

    func_8003ECF8();
    p = func_80025C08(D_8007FFB0);
    n = *p++;
    if (n == 0) {
        D_801E28A4 = 0;
        return;
    }
    if (n >= 0xD) {
        n = 0xC;
    }
    D_801E28A4 = n;
    actor = D_801E1E48;
    do {
        effect = func_8001D110();
        D_800AA248.new_def = effect;
        kind = *p;
        actor->unk_4 = kind;
        def = &D_80082138[kind];
        ed = def->unk_0;
        effect->anim = ed;
        effect->id = ed->unk_0;
        actor->unk_8 = 0;
        p++;
        actor->unk_6 = def->unk_4;
        effect->pos_x.s.hi = *p++;
        y = *p;
        effect->unk_0C = 0x745;
        effect->pos_y.s.hi = y;
        effect->flags = (s16)y + 0xF23;
        D_800AA248.cur_obj = func_8001DCB4();
        actor->unk_0 = D_800AA248.cur_obj;
        D_800AA248.cur_obj->owner.actor = actor;
        p++;
        actor->unk_38 = ((u16 *)&D_800AA248.cur_obj->pos_x.w)[1];
        D_800AA248.cur_obj->flags |= *p;
        actor->unk_20 = def->unk_8;
        actor->unk_24 = def->unk_C;
        p++;
        actor->unk_3E = def->unk_10;
        actor->unk_14 = def->unk_12;
        if (actor->unk_4 >= 0x54 && actor->unk_4 <= 0x55) {
            link = func_8002F01C();
            actor->unk_34 = link;
            if (link != NULL) {
                ((u16 *)&D_800AA248.cur_obj->pos_x.w)[1] += link->unk_4;
            }
        }
        actor++;
    } while (--n != 0);
}

void func_8003EF40(Actor *actor) {
    memset(actor, 0, sizeof(Actor));
}

void func_8003EF64(Monster *player) {
    GameObject *saved;
    GameObject *mover;
    Actor *actor = D_801E1E48;
    s16 px;
    s16 d;
    u16 n;

    n = D_801E28A4;
    saved = D_800AA268.p;
    if (n != 0) {
        mover = player->obj;
        px = ((s16 *)&mover->pos_x.w)[1];
        do {
            mover = actor->unk_0;
            if (!(mover->unk_6C & 0x80) && actor->unk_12 == 0 && actor->unk_4 != 0x55 && actor->unk_4 != 0x54 &&
                actor->unk_4 != 0x56 && actor->unk_4 != 0x8E && actor->unk_6 != 0 && actor->unk_6 != 0xB &&
                actor->unk_6 != 0xE && actor->unk_6 != 1 && actor->unk_6 != 5 && actor->unk_6 != 6 &&
                actor->unk_6 != 7 && actor->unk_6 != 3) {
                d = abs(((s16 *)&mover->pos_x.w)[1] - px);
                if (d <= (((s16)mover->size.u.lo) >> 1) - 1) {
                    if (actor->unk_6 != 0xA) {
                        D_800AA268.p = mover;
                        func_8004155C(7, actor);
                    } else if (((s16 *)&mover->pos_y.w)[1] == 0xE2) {
                        func_80054374(0x28, player);
                        func_800634D4(player, 4);
                        player->unk_024++;
                        actor->unk_28 = 1;
                    }
                    break;
                }
            }
            actor++;
        } while (--n != 0);
    }
    D_800AA268.p = saved;
}

void func_8003F114(void) {
    GameObject *saved = D_800AA248.cur_obj;

    func_8003F150();
    D_800AA248.cur_obj = saved;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003F150);

s32 func_8003F378(Monster *player) {
    Actor *actor = D_801E1E48;
    GameObject *mover;
    u16 n = D_801E28A4;
    s16 x;
    s16 y;

    if (n != 0) {
        do {
            if (actor->unk_6 == 0xE) {
                mover = actor->unk_0;
                if (!(mover->unk_6C & 0x80)) {
                    x = (((u16 *)&mover->pos_x.w)[1] - mover->unk_1C.u.lo) + (((s16)mover->size.u.lo) >> 1);
                    y = (((u16 *)&mover->pos_y.w)[1] - mover->unk_1C.u.hi) + (((s16)mover->size.u.hi) >> 1);
                    actor->unk_3A = x;
                    actor->unk_3C = y;
                    if (func_80053AC4(x, y, ((s16)mover->size.u.lo) >> 1, ((s16)mover->size.u.hi) >> 1, player) != 0) {
                        actor->unk_28 = 1;
                        actor->unk_2C = player;
                        player->unk_18A = 1;
                        return 1;
                    }
                }
            }
            actor++;
        } while (--n != 0);
    }
    return 0;
}

s32 func_8003F4A8(s16 x0, s16 y0, s16 x1, s16 y1, s16 x2, s16 y2) {
    if (x0 >= x1 || y0 >= y1 || x1 >= x2 || y1 >= y2) {
        return 0;
    }
    return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003F50C);

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003F74C);

void func_8003FB5C(Monster *player, Actor *actor) {
    switch (actor->unk_4) {
    case 0x1F:
        func_80053C50(0x28000, player);
        if (player->unk_05C != 2 && player->unk_05C != 0x4E) {
            player->action = 0x49;
            player->unk_126 = 1;
        }
        break;
    case 0x77:
    case 0x7A:
    case 0x7C:
        func_80053D68(8, player);
        player->action = 8;
        break;
    default:
        func_80053C50(0x28000, player);
        if (player->unk_05C != 2 && player->unk_05C != 0x4E) {
            player->action = 8;
            player->unk_126 = 1;
        }
        break;
    }
}

s32 func_8003FC30(Monster *player, Actor *actor) {
    if (actor->unk_14 == 0) {
        func_8003F74C(player, actor);
    }
    player->unk_18A = 1;
    return 1;
}

void func_8003FC70(s16 *dx, s16 *dy, GameObject *from, GameObject *to) {
    if (from == NULL || to == NULL) {
        *dx = 0xA;
        *dy = 0xC;
        return;
    }
    *dy = ((u16 *)&to->pos_y.w)[1] - ((u16 *)&from->pos_y.w)[1];
    *dx = func_8003FCD8(((s16 *)&to->pos_x.w)[1], ((s16 *)&from->pos_x.w)[1]);
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

#ifdef NON_MATCHING
/* 89.39 %: the right shape and calls; the original keeps three copies of the facing test (the v >= 2 one is not cross-jumped into the last one) and the neg path jumps into the first */
void func_8003FD30(Actor *actor) {
    u16 v;

    v = actor->unk_10;
    actor->unk_10 = 0;
    if (v == 1) {
        if (D_800AA268.p->flags & 0x10) {
            func_8003FE40(actor);
        } else {
            func_8003FE70(actor);
        }
    } else if (v >= 2) {
        if (D_800AA268.p->flags & 0x10) {
            func_8003FE70(actor);
        } else {
            func_8003FE40(actor);
        }
    } else if (D_800AA248.unk_00 < 0) {
        actor->unk_10 = 2;
        if (D_800AA248.cur_obj->flags & 0x10) {
            func_8003FE40(actor);
        } else {
            func_8003FE70(actor);
        }
    } else {
        actor->unk_10 = 1;
        if (!(D_800AA248.cur_obj->flags & 0x10)) {
            func_8003FE40(actor);
        } else {
            func_8003FE70(actor);
        }
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_8003FD30);
#endif

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
        if (D_800AA248.unk_04 != 0) {
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
    if (!(D_800AA248.cur_obj->flags & 0x10)) {
        vel = -vel;
    }
    D_800AA248.cur_obj->vel_x.w = vel;
    func_8004155C(kind, actor);
}

void func_8003FF54(void) {
    Actor *actor = D_800AA248.cur_obj->owner.actor;

    if (*(u16 *)&actor->unk_8 != 0) {
        goto stop;
    }
    func_8004003C(D_800AA248.cur_obj->flags, (Ai *)actor);
    if (D_800AA248.unk_0C != 0) {
        if (actor->unk_4 != 0x2F && abs(D_800AA248.unk_00) < 0x41) {
            goto turn;
        }
        if (D_800AA248.unk_04 == 0) {
            goto walk;
        }
    }
    func_8003FE14(actor);
    return;
walk:
    func_8003FEE4(actor);
    return;
turn:
    func_8003FD30(actor);
    return;
stop:
    func_8003FE70(actor);
}

void func_8004003C(s32 arg0, Ai *arg1) {
    s16 dx;
    s16 dy;
    u16 i;
    u16 best;
    s32 best_dx;
    Monster *player;
    s16 reach;

    i = 7;
    best = 9999;
    best_dx = 9999;
    D_800AA248.unk_04 = 0;
    D_800AA248.unk_0C = 0;
    D_800AA248.cur_obj->unk_68.monster = NULL;
    do {
        player = &D_801E0B78[i];
        if (player->unk_058 & 1) {
            D_800AA248.unk_0C = 1;
            reach = player->unk_1DE;
            func_8003FC70(&dx, &dy, player->obj, D_800AA248.cur_obj);
            if (dx >= 0) {
                if (!(D_800AA248.cur_obj->flags & 0x10)) {
                    D_800AA248.unk_04 = 1;
                }
            } else if (D_800AA248.cur_obj->flags & 0x10) {
                D_800AA248.unk_04 = 1;
            }
            if (reach != 0 && abs(dx) <= best) {
                best = reach;
                best_dx = dx;
                D_800AA248.cur_obj->unk_68.monster = player;
            }
        }
    } while (--i != 0);
    D_800AA248.unk_00 = best_dx;
}

void func_800401AC(void) {
    func_8004003C(D_800AA248.cur_obj->flags, D_800AA248.cur_obj->owner.ai);
    if (D_800AA248.unk_00 > 0) {
        D_800AA248.cur_obj->flags &= ~0x10;
    } else {
        D_800AA248.cur_obj->flags |= 0x10;
    }
}

void func_8004022C(void) {
    Anim **p;

    p = (Anim **)D_800AA248.cur_obj->arg.h;
    func_8004003C(D_800AA248.cur_obj->flags ^ 0x10, D_800AA248.cur_obj->owner.ai);
    if (D_800AA248.unk_0C != 0) {
        D_800AA248.cur_obj->script_pc = *p;
    }
}

void func_80040294(void) {
    Anim **p;

    p = (Anim **)D_800AA248.cur_obj->arg.h;
    func_8004003C(D_800AA248.cur_obj->flags ^ 0x10, D_800AA248.cur_obj->owner.ai);
    if (abs(D_800AA248.unk_00) < 0x4B) {
        D_800AA248.cur_obj->script_pc = *p;
    }
}

void func_80040314(Monster *player) {
    GameObject *saved;
    ObjectDef *effect;
    GameObject *mover;

    saved = D_800AA248.cur_obj;
    effect = func_8001D110();
    D_800AA248.new_def = effect;
    effect->anim = &D_8009556C;
    effect->id = D_8009556C.unk_0;
    mover = player->obj;
    effect->pos_x.s.hi = ((u16 *)&mover->pos_x.w)[1];
    effect->pos_y.s.hi = ((u16 *)&mover->pos_y.w)[1] | 0xC000;
    effect->flags = *(u16 *)&mover->unk_80 - 1;
    D_800AA248.cur_obj = func_8001DCB4();
    D_800AA248.cur_obj->owner.monster = player;
    D_800AA248.cur_obj = saved;
}

void func_800403B4(Actor *actor) {
    GameObject *saved;

    saved = D_800AA248.cur_obj;
    D_800AA248.cur_obj = actor->unk_0;
    if (actor->unk_34 == NULL || actor->unk_34->unk_10 != 0) {
        func_8004155C(2, actor);
    }
    D_800AA248.cur_obj = saved;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_80040418);

void func_800405D8(Actor *actor) {
    GameObject *mover;

    mover = actor->unk_0;
    D_800AA248.cur_obj = mover;
    if (actor->unk_28 != 0) {
        mover->vel_y.w = -0xA0000;
        D_800AA248.cur_obj->pos_y.w += -0x80000;
        func_8004155C(5, actor);
        func_80040B94(actor);
    } else {
        mover->pos_x.w = (mover->vel_x.w + mover->pos_x.w) & D_801D8864;
    }
}

void func_80040668(void) {
}

void func_80040670(Actor *actor) {
    GameObject *mover;

    mover = actor->unk_0;
    D_800AA248.cur_obj = mover;
    if (actor->unk_28 != 0) {
        mover->vel_y.w = -0xA0000;
        D_800AA248.cur_obj->pos_y.w += -0x80000;
        func_8004155C(5, actor);
        func_80040B94(actor);
    }
    D_800AA248.unk_4C = 0;
    func_8003E79C();
    if (D_800AA248.unk_4C != 0) {
        func_8004155C(0x10, actor);
    }
}

void func_80040704(Actor *actor) {
    GameObject *mover;
    s32 v;

    mover = actor->unk_0;
    D_800AA248.cur_obj = mover;
    if (actor->unk_28 != 0) {
        mover->vel_y.w = -0xA0000;
        D_800AA248.cur_obj->pos_y.w += -0x80000;
        func_8004155C(5, actor);
        func_80040B94(actor);
        D_800AA248.cur_obj->vel_x.w = 0;
        return;
    }
    v = mover->vel_x.w;
    if ((u16)func_8003E79C() == 1) {
        v = -v;
        D_800AA248.cur_obj->vel_x.w = v;
        if (D_800AA248.cur_obj->flags & 0x10) {
            D_800AA248.cur_obj->flags &= ~0x10;
        } else {
            D_800AA248.cur_obj->flags |= 0x10;
        }
    } else if (D_800AA248.unk_4C != 0) {
        func_8004155C(0x10, actor);
        return;
    }
    v += D_800AA268.p->pos_x.w;
    D_800AA268.p->pos_x.w = v & D_801D8864;
}

void func_80040824(Actor *actor) {
    D_800AA248.cur_obj = actor->unk_0;
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
    Monster *player;
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
        player->action = 8;
    }
}

void func_80040900(Actor *actor) {
    GameObject *mover;

    mover = actor->unk_0;
    D_800AA248.cur_obj = mover;
    mover->pos_y.w = 0x02000000;
    func_800415B4();
}

#ifdef NON_MATCHING
/* 97.05 %: register names only (the mover in v0, the sum in a1) */
void func_80040930(Actor *actor) {
    GameObject *mover;
    s32 v;

    mover = actor->unk_0;
    D_800AA248.cur_obj = mover;
    v = (mover->vel_x.w + mover->pos_x.w) & D_801D8864;
    mover->pos_x.w = v;
    v = D_800AA248.cur_obj->vel_y.w + 0x6500;
    D_800AA248.cur_obj->vel_y.w = v;
    D_800AA248.cur_obj->pos_y.w += v;
    if (v > 0 && D_800AA248.cur_obj->pos_y.w > 0xA5C100) {
        D_800AA248.cur_obj->pos_y.w = 0x2000000;
        func_800415B4();
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_80040930);
#endif

#ifdef NON_MATCHING
/* 96.48 %: register names only, as func_80040930 */
void func_800409CC(Actor *actor) {
    GameObject *mover;
    s32 v;

    mover = actor->unk_0;
    D_800AA248.cur_obj = mover;
    mover->pos_x.w = (mover->pos_x.w + mover->vel_x.w) & D_801D8864;
    v = D_800AA248.cur_obj->vel_y.w + 0x6500;
    D_800AA248.cur_obj->vel_y.w = v;
    D_800AA248.cur_obj->pos_y.w += v;
    if (v > 0 && D_800AA248.cur_obj->pos_y.w > 0xE0FFFF) {
        D_800AA248.cur_obj->pos_y.w = 0xE10000;
        func_8004155C(7, actor);
        actor->unk_28 = 0;
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_800409CC);
#endif

void func_80040A7C(Actor *actor) {
    GameObject *mover;

    mover = actor->unk_0;
    D_800AA248.cur_obj = mover;
    if (actor->unk_28 != 0) {
        mover->pos_y.w = 0x02000000;
        func_800415B4();
    }
}

void func_80040AB8(Actor *actor) {
    D_800AA248.cur_obj = actor->unk_0;
    if (actor->unk_28 != 0) {
        actor->unk_28 = 0;
        D_800AA248.cur_obj->pos_y.w = 0x2000000;
        func_800415B4();
    }
}

void func_80040B00(Actor *actor) {
    GameObject *mover;

    mover = actor->unk_0;
    D_800AA248.cur_obj = mover;
    if (actor->unk_28 != 0) {
        mover->vel_y.w = -0xA0000;
        D_800AA248.cur_obj->pos_y.w += -0x80000;
        func_8004155C(5, actor);
        func_80040B94(actor);
    } else if ((s16)actor->unk_12 != 0 && (s16)actor->unk_12 == -1) {
        func_8004155C(4, actor);
    }
}

void func_80040B94(Actor *actor) {
    if (actor->unk_3E >= 1 && actor->unk_3E <= 5) {
        D_8007E1E4[actor->unk_3E](actor);
    }
}

void func_80040BE4(void) {
}

void func_80040BEC(void) {
    if (!(D_800AA248.cur_obj->unk_6C & 0x80)) {
        func_8001F724(0x13);
    }
}

void func_80040C28(void) {
    if (!(D_800AA248.cur_obj->unk_6C & 0x80)) {
        func_8001F724(6);
    }
}

void func_80040C64(void) {
    if (!(D_800AA248.cur_obj->unk_6C & 0x80)) {
        func_8001F724(0);
    }
}

void func_80040CA0(void) {
}

void func_80040CA8(void) {
}

void func_80040CB0(void) {
}

#ifdef NON_MATCHING
/* 97.61 %: in case 0 the original loads a fresh 1 for actor->unk_28 while kind (= 1, in s0) is live; here the store reuses s0 */
void func_80040CB8(Actor *actor) {
    u16 kind;

    D_800AA268.p = actor->unk_0;
    if (actor->unk_28 != 0) {
        switch (actor->unk_14) {
        case 2:
            kind = 3;
            break;
        case 0:
            kind = 1;
            func_8004155C(1, actor);
            actor->unk_28 = 1;
            break;
        case 3:
            kind = 3;
            break;
        default:
            actor->unk_14 = 0;
            kind = 4;
            break;
        }
        func_8004155C(kind, actor);
        actor->unk_28 = 0;
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_80040CB8);
#endif

/* 99.2%: the mover pointer and the frame's offsets get a0/a1 in the other order around the x/y adjustment */
#ifdef NON_MATCHING
/* 98.59 %: the deltas frame->unk_8 - x and frame->unk_A - y land in s0/s1 (x's and y's registers) in the
 * original, in temporaries here. */
void func_80040D68(Actor *actor) {
    GameObject *saved;
    AnimFrame *frame;
    s32 x;
    s32 y;

    saved = D_800AA248.cur_obj;
    D_800AA248.cur_obj = actor->unk_0;
    if (actor->unk_30 == 0) {
        if (actor->unk_28 != 0) {
            actor->unk_32++;
            actor->unk_30 = 0x3C;
            func_80041344(actor->unk_32, actor);
            if (actor->unk_32 >= 4) {
                x = ((u16 *)&D_800AA248.cur_obj->unk_1C.u.lo)[0];
                y = ((u16 *)&D_800AA248.cur_obj->unk_1C.u.lo)[1];
                func_8004155C(2, actor);
                frame = func_8001A784(*(s32 *)D_800AA248.cur_obj->unk_48);
                x = frame->unk_8 - x;
                ((u16 *)&D_800AA248.cur_obj->pos_x.w)[1] += x;
                y = frame->unk_A - y;
                ((u16 *)&D_800AA248.cur_obj->pos_y.w)[1] += y;
            }
        }
    }
    if (actor->unk_30 != 0) {
        actor->unk_30--;
    }
    actor->unk_28 = 0;
    D_800AA248.cur_obj = saved;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_80040D68);
#endif

void func_80040EA0(Actor *actor) {
    GameObject *mover;
    GameObject *saved;

    mover = actor->unk_0;
    saved = D_800AA248.cur_obj;
    D_800AA248.cur_obj = mover;
    if (mover->unk_6C & 0x80) {
        if (actor->unk_16 != 0) {
            func_800415B4();
            D_800AA248.cur_obj = saved;
            return;
        }
    } else {
        actor->unk_16 = 1;
    }
    D_800AA248.cur_obj->pos_x.w = D_801D8864 & (D_800AA248.cur_obj->vel_x.w + D_800AA248.cur_obj->pos_x.w);
    if (actor->unk_30 == 0) {
        if (actor->unk_28 != 0) {
            actor->unk_30 = 0x3C;
            actor->unk_32++;
            if (actor->unk_32 != 0) {
                func_8004155C(2, actor);
            }
        }
    }
    D_800AA248.cur_obj = saved;
}

void func_80040F84(Actor *actor) {
    GameObject *saved;
    GameObject *mover;

    mover = actor->unk_0;
    saved = D_800AA248.cur_obj;
    D_800AA248.cur_obj = mover;
    if (mover->unk_6C & 0x80) {
        if (actor->unk_16 != 0) {
            func_800415B4();
        } else {
            D_800AA248.cur_obj = saved;
            return;
        }
    } else {
        actor->unk_16 = 1;
    }
    D_800AA248.cur_obj->pos_x.w = D_801D8864 & (D_800AA248.cur_obj->vel_x.w + D_800AA248.cur_obj->pos_x.w);
    if (actor->unk_30 == 0) {
        if (actor->unk_28 != 0) {
            actor->unk_30 = 0x3C;
            actor->unk_2C->unk_218 = D_800AA248.cur_obj;
            actor->unk_32++;
            if (actor->unk_32 != 0) {
                func_8004155C(2, actor);
            }
        }
    }
    if (actor->unk_30 != 0) {
        actor->unk_30--;
    }
    actor->unk_28 = 0;
    D_800AA268.p = saved;
}

void func_800410AC(Actor *actor) {
    GameObject *mover;
    GameObject *saved;

    mover = actor->unk_0;
    saved = D_800AA248.cur_obj;
    D_800AA248.cur_obj = mover;
    if (mover->unk_6C & 0x80) {
        if (actor->unk_16 != 0) {
            func_800415B4();
            D_800AA248.cur_obj = saved;
            return;
        }
    } else {
        actor->unk_16 = 1;
    }
    D_800AA248.cur_obj->pos_x.w = D_801D8864 & (D_800AA248.cur_obj->vel_x.w + D_800AA248.cur_obj->pos_x.w);
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
    D_800AA248.cur_obj = saved;
}

#ifdef NON_MATCHING
/* 95.34 %: register names only: the original holds &D_800AA248 in a0 (so reorg hoists its lui into the first branch's delay slot) and the velocity sum in a1; here a1 and a0 */
void func_800411E8(Actor *actor) {
    GameObject *saved;
    GameObject *mover;
    s32 d;
    s16 target;
    s16 x;
    s32 v;

    saved = D_800AA248.cur_obj;
    D_800AA248.cur_obj = actor->unk_0;
    if (actor->unk_30 == 0 && actor->unk_28 != 0) {
        actor->unk_32++;
        actor->unk_30 = 0x3C;
        func_80041344(actor->unk_32, actor);
        if (actor->unk_32 >= 4) {
            func_8004155C(2, actor);
        }
    } else {
        d = D_800AA248.cur_obj->unk_84 + D_800AA248.cur_obj->vel_x.w;
        D_800AA248.cur_obj->vel_x.w = d;
        D_800AA248.cur_obj->pos_x.w += d;
        mover = D_800AA248.cur_obj;
        target = actor->unk_38;
        x = ((s16 *)&mover->pos_x.w)[1];
        if (abs(x - target) < 0x32) {
            if (mover->vel_x.w != 0) {
                mover->unk_84 = 0;
            } else {
                mover->vel_x.w = 0x3500;
            }
        } else {
            v = 0x300;
            if (target + 0x32 < x) {
                v = -0x300;
            }
            mover->unk_84 = v;
        }
    }
    if (actor->unk_30 != 0) {
        actor->unk_30--;
    }
    actor->unk_28 = 0;
    D_800AA268.p = saved;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8003CD08", func_800411E8);
#endif

void func_80041344(u16 kind, Actor *actor) {
    ActorSound *sound;
    Monster *player;

    if (kind >= 7) {
        kind = 6;
    }
    sound = &D_8007E1FC[kind];
    player = actor->unk_2C;
    if (player != NULL) {
        func_80054374(sound->unk_4, player);
    }
    func_80061068(sound->unk_0, actor->unk_3A, actor->unk_3C);
}

void func_800413BC(u16 kind, Actor *actor) {
    ActorSound *sound;
    Monster *player;

    if (kind >= 2) {
        kind = 1;
    }
    sound = &D_8007E1FC[kind];
    player = actor->unk_2C;
    if (player != NULL) {
        func_80054374(sound->unk_4, player);
    }
    func_80061068(sound->unk_0, actor->unk_3A, actor->unk_3C);
}

void func_80041434(void) {
}

void func_8004143C(Actor *actor) {
    GameObject *mover;
    s32 v;

    if (actor->unk_4 != 0x8E) {
        return;
    }
    mover = actor->unk_0;
    D_800AA248.cur_obj = mover;
    if (!(mover->unk_6C & 0x80)) {
        mover->pos_x.w = (mover->vel_x.w + mover->pos_x.w) & D_801D8864;
        v = D_800AA248.cur_obj->vel_y.w + 0x4000;
        D_800AA248.cur_obj->pos_y.w += v;
        if (v >= 0 && ((s16 *)&D_800AA248.cur_obj->pos_y.w)[1] >= 0xDC) {
            func_8001F7CC(0xBE, 0x6F);
            v -= v >> 4;
            if (v < 0x20000) {
                v = 0x20000;
            }
            v = -v;
        }
        D_800AA248.cur_obj->vel_y.w = v;
        if (func_8003712C(((s16 *)&D_800AA248.cur_obj->pos_x.w)[1], ((s16 *)&D_800AA248.cur_obj->pos_y.w)[1],
                          actor->unk_2C) != 1) {
            return;
        }
    }
    func_800415B4();
}

void func_8004155C(u16 kind, Actor *actor) {
    Anim *anim;

    actor->unk_6 = kind;
    anim = func_80041598(actor);
    if (anim != NULL) {
        func_8003EB5C(anim, D_800AA248.cur_obj);
    }
}

Anim *func_80041598(Actor *actor) {
    Anim **anims;

    anims = actor->unk_24;
    anims += actor->unk_6;
    return *anims;
}

void func_800415B4(void) {
    D_800AA248.cur_obj->owner.ai->unk_04 = 0;
    func_8004CFC0();
}

void func_800415E0(Actor *actor) {
    D_800AA248.cur_obj = actor->unk_0;
    actor->unk_4 = 0;
    func_8004CFC0();
}
