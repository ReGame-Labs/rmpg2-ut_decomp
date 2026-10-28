/* The actors: the twelve Actor records of D_801E1E48, loaded from the level's list, and the behaviour slots (Ai)
 * of D_801D85C8 around the game's current object, D_800AA248.cur_obj.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "game.h"
#include "npc.h"
#include "psyq/libc2.h"

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
s32 main_random_between(s32 arg0, s32 arg1);
void func_8001F724(u16);
void func_8003C894(Actor *actor);
void func_8003C8D4(Actor *actor);
void func_8004CFC0(void);
void func_80053D68(s32 arg0, Monster *player);
void func_80054374(s32 arg0, Monster *player);
void func_8005E0E8(Monster *player);
s32 bonus_get_round_kind(void);
struct AnimFrame *func_8001A784(s32 arg0);

typedef struct AnimFrame {
    /* 0x00 */ u8 unk_0[0x8];
    /* 0x08 */ u16 unk_8;
    /* 0x0A */ u16 unk_A;
} AnimFrame;
s32 abs(s32 x);                 /* GCC's builtin: inlined */

void func_8003CD5C(ActorEntry *entry);
void *func_8003D1F8(Actor *actor);
void func_8003D490(Actor *actor);
void func_8003D58C(Anim *anim);
void func_8003DAA0(Ai *ai);
s16 func_8003DCC8(Ai *ai);
void func_8003DD44(Ai *ai);
void func_8003DF34(Ai *ai);
BuildingItem *actor_pick_building_part(BuildingPart **part, Ai *ai);   /* the second argument is not used */
extern s16 D_8007DEC0[][8]; /* by item count - 3: 8 item numbers to pick from */
extern s16 D_8007DFA0;      /* the last building picked */
extern u16 D_801FA93C;      /* the picked part's side */
extern u16 D_801FA940;      /* the picked item's unk_04 */
extern u16 D_801FA944;      /* the picked building's index + 1 */
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
Building *func_8002F01C(void);
void func_8003ECF8(void);

/* What an actor of a kind is made of: its effect, its kind, its handlers and animations (0x14 bytes, D_80082138[]). */
typedef struct ActorDef {
    /* 0x00 */ Anim *unk_0;
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
s32 func_8003F150(Monster *player);
u16 func_80030338(GameObject *);
ObjectDef *func_8001D110(void);
GameObject *func_8001DCB4(void);       /* spawns D_800AA248.new_def */
void func_8004003C(s32 arg0, Ai *link);
s16 func_80053AC4(s16 x, s16 y, s32 w, s32 h, Monster *player);
void func_8003CCC0(void *);
void func_80040B94(Actor *actor);
void func_800634D4(Monster *, u32);

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
void actor_take_hit(Monster *player, Actor *actor);
u16 func_8003FC30(Monster *player, Actor *actor);
s16 func_8003FCD8(s32 arg0, s32 arg1);
void func_8003FF0C(s32 vel, s32 kind, Actor *actor);
void func_8004089C(Actor *actor);
void func_8004155C(u16 kind, Actor *actor);
Anim *func_80041598(Actor *actor);
void func_800415B4(void);

extern const AiHandler D_8007DEA0[];
extern ActorSound D_8007E1FC[];
extern void (*D_8007E1E4[])(Actor *actor);
extern void (*D_8007E244)(Actor *);
extern void (*D_8007E2CC)(Actor *);
extern void (*D_8007E398)(Actor *);
extern Anim D_80094AEC;
extern Anim D_80094514;
extern ActorDef D_80082138[];
extern u8 D_8007FFB0[];
extern s16 D_801D8718;
extern s16 D_801D8728;   /* not in game.h: this file reads it signed (lh), main.c unsigned (lhu) */
extern s16 D_801D871C;
extern Actor D_801E1E48[];
extern u16 D_801E28A4;
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

    if (mover->anim != (s32) anim) {
        if (*(u16 *)&mover->priority == 0) {
            mover->priority = ((AnimFrame *)func_8003D1F8(mover->owner.ai->unk_10.actor))->unk_8 - 1;
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
                ai->timer = 0x28;
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

void func_8003D228(UnkStructB2 *rec) {
    Anim *anim = NULL;

    switch (rec->kind) {
    case 0x2A:
        anim = &D_80094514;
        if (rec->unk_04 < 2) {
            return;
        }
        break;
    case 0x27:
    case 0x28:
    case 0x29:
    case 0x2B:
    case 0x2C:
        rec->unk_04 = 3;
        break;
    default:
        return;
    }
    if (rec->unk_0E != 0) {
        rec->unk_08 = 3;
        rec->unk_18 = 0x34;
        rec->unk_0E = 0;
        rec->unk_14 = NULL;
        if (rec->unk_04 != 3) {
            func_8001F7CC(0xC8, 0x2F);
            rec->unk_04 = 3;
            rec->unk_18 = -1;
            if (anim != NULL) {
                func_8003D58C(anim);
            }
        }
    }
}

void func_8003D30C(UnkStructB2 *rec) {
    switch (rec->kind) {
    case 0x34:
        if (rec->unk_0E != 0 && rec->unk_14 != NULL) {
            func_8001F724(0x11);
            rec->unk_14->health.w = 0x440000;
            func_8003C8D4((Actor *)rec);
            rec->unk_1C = 0;
        }
        break;
    case 0x35:
        if (rec->unk_0E != 0 && rec->unk_14 != NULL) {
            func_8001F724(0x11);
            rec->unk_14->meter.w = 0x440000;
            func_8003C8D4((Actor *)rec);
            rec->unk_1C = 0;
        }
        break;
    }
}

void func_8003D3CC(UnkStructB2 *rec) {
    Anim *anim = NULL;

    switch (rec->kind) {
    case 0x2F:
        anim = &D_80094AEC;
        if (rec->unk_04 < 2) {
            return;
        }
        break;
    case 0x2D:
    case 0x2E:
    case 0x30:
        rec->unk_04 = 3;
        break;
    default:
        return;
    }
    if (rec->unk_0E != 0) {
        rec->unk_0E = 0;
        rec->unk_14 = NULL;
        if (rec->unk_04 == 3) {
            func_8003D4AC((Ai *)rec);
        } else {
            rec->unk_04 = 3;
            rec->unk_08 = 6;
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
    D_800AA248.cur_obj->priority = 0xF00;
    if (ai->unk_10.part->unk_04 == 2) {
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
    if (D_800AA248.cur_obj->anim != (s32) anim) {
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

extern AiHandler D_8007DE44[];

void func_8003D71C(Ai *ai) {
    s32 x;
    Monster *target;
    u16 delay;

    D_800AA248.cur_obj = ai->obj;
    func_80029D1C();
    target = ai->target;
    D_800AA248.cur_obj->unk_68.monster = target;
    delay = ai->delay;
    if (delay != 0) {
        ai->delay = delay - 1;
        return;
    }
    switch (ai->action) {
    case 1:
        func_8003DD70(ai);
        return;
    case 2:
        func_8003D920(ai);
        return;
    case 3:
        func_8003DA58(ai);
        return;
    case 4:
        func_8003DBCC(ai);
        return;
    case 0xF0:
        func_8003DACC(ai);
        return;
    case 0xF1:
        func_8003DB2C(ai);
        return;
    case 0xF5:
        func_8003DAA0(ai);
        return;
    case 0x4E:
        func_8003D988(ai);
        return;
    case 5:
        func_8003D9D8(ai);
        return;
    }
    x = D_800AA268.p->pos_x.w - D_801F9AC8.w;
    x >>= 16;
    if (x < -0x4FF) {
        x += ((s16)D_801D8866 + 1) >> 16;
    }
    ai->unk_0E = x;
    if (ai->kind < 0x19) {
        D_8007DE44[ai->kind](ai);
    }
}

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
        D_800AA248.cur_obj->priority = 0x390;
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
        ai->unk_1A = ai->unk_10.part->unk_06;
        func_8003E630(ai);
        func_8003DD44(ai);
    }
}

s32 func_8003DC3C(Ai *ai) {
    u16 k;

    if (bonus_get_round_kind() == 3) {
        return 1;
    }
    k = ai->unk_1C.building->state;
    if (k != 0 && k != 2 && k != 3) {
        return -1;
    }
    if (ai->unk_1A != ai->unk_10.part->unk_06) {
        return 1;
    }
    if (ai->unk_28.item->unk_06 != 2) {
        return 0;
    }
    return -1;
}

s16 func_8003DCC8(Ai *ai) {
    Building *b;
    u16 kind;

    b = ai->unk_1C.building;
    if (b != NULL && ai->unk_28.item->unk_06 < 2) {
        if (ai->unk_10.part != NULL && ai->unk_10.part->unk_0C != NULL) {
            return -1;
        }
        kind = b->state;
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

void func_8003DD70(Ai *ai) {
    BuildingPart *part;
    BuildingItem *item;
    Building *b;
    GameObject *obj;
    SpriteFrame *frame;
    s32 n;

    n = (u16)ai->timer - 1;
    if (n > 0) {
        ai->timer = n;
        D_800AA248.cur_obj->pos_x.w = D_801F9AC8.w + 0xFE440000;
        D_800AA248.cur_obj->pos_y.w = 0x02000000;
        return;
    }
    item = actor_pick_building_part(&part, ai);
    if (item == NULL) {
        ai->timer = 0xF0;
        return;
    }
    ai->state = 1;
    ai->action = 2;
    if (item->unk_06 >= 2 || item->unk_04 == 0) {
        func_8003DAA0(ai);
        return;
    }
    ai->unk_28.item = item;
    ai->unk_10.part = part;
    part->unk_08 = ai;
    b = item->building;
    ai->unk_1C.building = b;
    obj = item->obj;
    frame = obj->frame;
    D_800AA248.cur_obj->priority = b->priority + 0x10;
    if (part->unk_04 == 2) {
        D_800AA248.cur_obj->flags |= 0x10;
        D_800AA248.cur_obj->pos_x.s.hi = obj->pos_x.s.hi + frame->unk_1C + 0xE;
        D_800AA248.cur_obj->pos_y.s.hi = obj->pos_y.s.hi + frame->unk_1E;
    } else if (part->unk_04 != 1) {
        D_800AA248.cur_obj->pos_x.s.hi = obj->pos_x.s.hi + frame->unk_18;
        D_800AA248.cur_obj->pos_y.s.hi = obj->pos_y.s.hi + frame->unk_1A;
    } else {
        D_800AA248.cur_obj->flags &= ~0x10;
        D_800AA248.cur_obj->pos_x.s.hi = obj->pos_x.s.hi + frame->unk_14;
        D_800AA248.cur_obj->pos_y.s.hi = obj->pos_y.s.hi + frame->unk_16;
    }
    func_8003DF34(ai);
}

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

extern void *D_8008AC94;
extern void *D_8008AD5C;
extern u8 D_8007E1D4[];
extern s16 D_801D8714;

void func_8003DFD4(void) {
    GameObject *saved;
    ObjectDef *def;
    Ai *ai;
    u16 *init;
    void **anim;
    u16 n;
    s16 y;

    saved = D_800AA248.cur_obj;
    func_8003DF70();
    if (D_801D8728 == 0xE && D_801D8714 == 2) {
        D_800AA248.cur_obj = saved;
        return;
    }
    init = func_80025C08(D_8007E1D4);
    n = 5;
    D_801D870C = n;
    y = 0;
    ai = D_801D85C8;
    do {
        def = D_800AA248.new_def = func_8001D110();
        if (D_801FA960 >= 0x5E && D_801FA960 != 0x63 && D_801D8728 == 0) {
            anim = &D_8008AD5C;
        } else {
            anim = &D_8008AC94;
        }
        def->anim = *anim;
        def->unk_0C = 0x781;
        ai->state = 0;
        if (D_801D36FC != 0x120) {
            ai->timer = main_random_between(0x64, 0x32) + 0x96;
        }
        ai->kind = *init;
        init++;
        ai->unk_34.u.lo = *init;
        ai->action = 1;
        def->flags = 0x353;
        D_800AA248.cur_obj = func_8001DCB4();
        init++;
        ai->obj = D_800AA248.cur_obj;
        D_800AA248.cur_obj->owner.p = ai;
        y += 0x12C;
        D_800AA248.cur_obj->pos_y.s.hi = y;
        if (bonus_get_round_kind() == 3) {
            ai->timer = 0;
            ai->delay = 0;
        } else {
            ai->delay = y;
        }
        if (ai->kind == 0) {
            ai->delay = 0x7FFF;
            ai->timer = 0x7FFF;
        }
        ai++;
    } while (--n != 0);
    D_800AA268.p = saved;
}

/* Picks a free part of a standing building for a behaviour slot: a random building (not the last one picked in the
 * modes of D_800AA2DC & 0xE00), then up to 5 random sides, then up to 7 items from the side's limit (or a random
 * row of D_8007DEC0 by item count). Returns the item and the part in *part, or NULL. */
BuildingItem *actor_pick_building_part(BuildingPart **part, Ai *ai) {
    Building *b;
    BuildingItem *item;
    BuildingPart *p;
    GameObject *obj;
    s16 *row;
    u16 count;
    u16 id;
    s16 idx;
    s16 tries;
    s16 s;
    s16 side;
    s16 limit;
    s16 k;
    s16 n;
    s32 r;

    count = D_801E29A4;
    /* The building count is read here both as u16 (lhu) and as s16 (lh); the other units read it as u16. */
    if (*(s16 *)&D_801E29A4 == 0) {
        goto fail;
    }
    idx = main_random_between(*(s16 *)&D_801E29A4, 0);
    if (idx == 0) {
        idx = count;
    }
    if (D_800AA2DC & 0xE00) {
        if (idx == D_8007DFA0 && *(s16 *)&D_801E29A4 >= 2) {
            if (idx < *(s16 *)&D_801E29A4) {
                idx++;
            } else {
                idx = 1;
            }
        }
        D_8007DFA0 = idx;
    }
    b = D_801D3DC8;
    tries = 0;
    b += idx - 1;
    for (;;) {
        if (b->state == 0 && b->unk_058 == 0) {
            obj = b->items[0].obj;
            if (D_800AA2DC & 0xE00) {
                goto found;
            }
            if (!(obj->unk_6C & 0x80)) {
                goto found;
            }
            item = b->unk_070;
            obj = item->obj;
            if (!(obj->unk_6C & 0x80)) {
            found:
                D_801FA944 = b->unk_01E;
                goto pick;
            }
        }
        if (tries >= 6) {
        fail:
            D_801FA940 = 0;
            D_801FA944 = 0;
            D_801FA93C = 0;
            *part = NULL;
            return NULL;
        }
        tries++;
        if (b->unk_01E < (s16)count) {
            b++;
        } else {
            b = D_801D3DC8;
        }
    }

pick:
    tries = 0;
retry:
    if (tries >= 5) {
        goto fail;
    }
    tries++;
    r = main_random_between(0x8000, 0);
    if (b->kind != 2) {
        s = r & 3;
        if (s != 0) {
            if (s != 3) {
                goto sides;
            }
        } else {
            s = 3;
        }
        limit = b->unk_026;
        goto have_limit;
    }
    s = (r & 1) + 1;
sides:
    if (s == 1) {
        limit = b->left_side;
    } else if (s == 2) {
        limit = b->right_side;
    } else {
        goto fail;
    }
have_limit:
    side = s;
    if (limit == 0) {
        count = b->unk_000;
        if ((s16)b->unk_000 >= 0x10) {
            goto fail;
        }
        n = count - 3;
        if (n < 0) {
            goto fail;
        }
        row = D_8007DEC0[n];
        row += main_random_between(0x8000, 0) & 7;
        limit = *row;
        if (limit == 0) {
            goto fail;
        }
    } else {
        if (limit < 0) {
            goto retry;
        }
        if (b->unk_000 == limit) {
            goto retry;
        }
        limit--;
    }
    tries = 0;
    item = &b->items[0];
    do {
        limit--;
        item++;
    } while (limit > 0);
first_part:
    if (side == 1) {
        p = &item->unk_0C;
    } else if (side == 2) {
        p = &item->unk_24;
    } else {
        p = &item->unk_3C;
    }
    for (;;) {
        k = item->unk_04;
        id = k;
        if (k < b->unk_000 && (u16)func_8003E59C(p, item, b) != 0) {
            goto success;
        }
        if (++tries >= 7) {
            goto fail;
        }
        item++;
        if (k >= b->unk_000) {
            item = &b->items[1];
            goto first_part;
        }
        p = (BuildingPart *)((BuildingItem *)p + 1); /* the same part of the next item */
    }
success:
    D_801FA940 = id;
    D_801FA93C = side;
    *part = p;
    return item;
}

s32 func_8003E59C(BuildingPart *part, BuildingItem *item, Building *b) {
    s16 limit;

    if (part->unk_08 == NULL && part->unk_14 == 0) {
        if (part->unk_04 == 1) {
            limit = b->left_side;
        } else if (part->unk_04 == 2) {
            limit = b->right_side;
        } else {
            limit = b->unk_026;
        }
        if (limit == 0 || (limit != -1 && item->unk_04 >= limit)) {
            return 1;
        }
    }
    return 0;
}

void func_8003E630(Ai *ai) {
    Monster *player;
    u16 i;
    u16 n;
    u16 max = 8;

    n = 8;
    i = ai->unk_04;
    do {
        i++;
        if (i >= max) {
            i = 1;
        }
        player = &D_801E0B78[i];
        if (player->unk_058 & 1) {
            break;
        }
    } while (--n != 0);
    ai->target = (Monster *)player;
    ai->unk_04 = i;
}

void func_8003E6A4(Ai *ai) {
    BuildingPart *part;
    GameObject *mover;
    u16 kind;

    part = ai->unk_10.part;
    if (part != NULL) {
        part->unk_08 = NULL;
        kind = ai->unk_22;
        if (kind != 0) {
            part->unk_14 = kind;
        }
    }
    ai->unk_30.u.hi++;
    mover = ai->obj;
    ai->unk_22 = 0;
    ai->unk_34.s.hi = 0;
    ai->state = 0;
    ai->unk_10.part = NULL;
    ai->unk_1C.building = NULL;
    ai->target = NULL;
    ai->unk_38 = 0;
    ai->unk_0C = 0;
    ((s16 *)&mover->pos_x.w)[1] = -0x190;
    ((s16 *)&mover->pos_y.w)[1] = -0x190;
    mover->vel_x.w = 0;
    mover->vel_y.w = 0;
    ai->action = 1;
    if (bonus_get_round_kind() == 3) {
        ai->timer = 0;
        ai->delay = 0;
        return;
    }
    ai->timer = main_random_between(0x258, 0x168);
}

void func_8003E764(Ai *ai) {
    memset(ai, 0, sizeof(Ai));
}

void func_8003E788(Ai *ai) {
    ai->unk_10.part->unk_08 = NULL;
    ai->unk_10.part = NULL;
}

s32 func_8003E79C(void) {
    s16 x;

    if (D_801D37B8 != 0) {
        x = D_800AA248.cur_obj->pos_x.s.hi;
        if (x >= D_801D37B8 && x <= D_801D87B4) {
            goto inside;
        }
    }
    func_80030338(D_800AA248.cur_obj);
    D_800AA248.result = 0;
    return 0;
inside:
    D_800AA248.unk_4C = 0;
    D_800AA248.result = 1;
    return 1;
}

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
        if (main_random_between(0x8000, 0) & 1) {
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
    if ((s32) anim == mover->anim) {
        D_800AA248.unk_7A = 1;
        mover->flags |= 0x800;
    } else {
        mover->anim = (s32) anim;
        mover->script.pc = (s32) anim;
        mover->unk_4C = 0;
        mover->frames_left = 0;
        mover->unk_64.w = 0;
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

    D_800AA268.p = actor->obj;
    func_80029D1C();
    if (actor->unk_4 == 0) {
        return;
    }
    if ((u16)actor->kind >= 0x11) {
        goto bad;
    }
    /* FAKE: the table and the index in one comma expression; the plain p[actor->unk_6] gives the kind another register
     * (a0 for v1), the only difference (99.2 %). */
    handler = *(p = actor->unk_20, p + actor->kind);
    if (handler == NULL) {
        return;
    }
    handler(actor);
    if (actor->unk_4 == 0) {
        return;
    }
    if ((u16)actor->kind < 0x11) {
        goto ok;
    }
bad:
    func_800415E0(actor);
    return;
ok:
    func_8004155C(actor->kind, actor);
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
    Anim *ed;
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
        effect->id = ed->id;
        actor->unk_8 = 0;
        p++;
        actor->kind = def->unk_4;
        effect->pos_x.s.hi = *p++;
        y = *p;
        effect->unk_0C = 0x745;
        effect->pos_y.s.hi = y;
        effect->flags = (s16)y + 0xF23;
        D_800AA248.cur_obj = func_8001DCB4();
        actor->obj = D_800AA248.cur_obj;
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
            mover = actor->obj;
            if (!(mover->unk_6C & 0x80) && actor->unk_12 == 0 && actor->unk_4 != 0x55 && actor->unk_4 != 0x54 &&
                actor->unk_4 != 0x56 && actor->unk_4 != 0x8E && actor->kind != 0 && actor->kind != 0xB &&
                actor->kind != 0xE && actor->kind != 1 && actor->kind != 5 && actor->kind != 6 &&
                actor->kind != 7 && actor->kind != 3) {
                d = abs(((s16 *)&mover->pos_x.w)[1] - px);
                if (d <= (((s16)mover->size.u.lo) >> 1) - 1) {
                    if (actor->kind != 0xA) {
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

void func_8003F114(Monster *player) {
    GameObject *saved = D_800AA248.cur_obj;

    func_8003F150(player);
    D_800AA248.cur_obj = saved;
}

s32 func_8003F150(Monster *player) {
    Actor *actor = D_801E1E48;
    GameObject *mover;
    u16 n = D_801E28A4;
    s16 kind;
    s16 x;
    s32 flip;
    u16 px;
    u16 py;

    if (n != 0) {
        px = player->pos.u.lo;
        py = player->pos.u.hi;
        do {
            mover = actor->obj;
            if (actor->unk_12 == 0 && actor->unk_4 != 0x56 && actor->unk_4 != 0x55 && actor->unk_4 != 0x8E) {
                kind = actor->kind;
                if (kind != 0 && kind != 0xB && kind != 0xE && kind != 1 && kind != 7 && kind != 3) {
                    x = mover->pos_x.s.hi;
                    if (x < D_801F9ACA) {
                        x += (D_801D8864.w + 1) >> 16;
                    }
                    if ((s16)abs(x - (s16)px) <= mover->size.s.lo) {
                        if ((s16)abs((s16)(mover->pos_y.u.hi - 5) - (s16)py) <= mover->size.s.hi) {
                            if (kind == 0xA) {
                                func_80054374(0x28, player);
                                func_800634D4(player, 4);
                                player->unk_024++;
                                actor->unk_28 = 1;
                            } else {
                                flip = D_800AA248.cur_obj->flags & 0x10;
                                D_800AA248.cur_obj = mover;
                                if (flip) {
                                    mover->vel_x.w = -0x48000;
                                } else {
                                    mover->vel_x.w = 0x48000;
                                }
                                D_800AA248.cur_obj->vel_y.w = -0x58000;
                                D_800AA248.cur_obj->unk_88 = 0x4000;
                                actor->kind = 6;
                                actor->unk_20 = &D_8007E398;
                                func_8004155C(6, actor);
                            }
                            player->unk_18A = 1;
                            return 1;
                        }
                    }
                }
            }
            actor++;
        } while (--n != 0);
    }
    return 0;
}

s32 func_8003F378(Monster *player) {
    Actor *actor = D_801E1E48;
    GameObject *mover;
    u16 n = D_801E28A4;
    s16 x;
    s16 y;

    if (n != 0) {
        do {
            if (actor->kind == 0xE) {
                mover = actor->obj;
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

u16 func_8003F4A8(s16 x0, s16 y0, s16 x1, s16 y1, s16 x2, s16 y2) {
    if (x0 >= x1 || y0 >= y1 || x1 >= x2 || y1 >= y2) {
        return 0;
    }
    return 1;
}

u16 func_8003F50C(Monster *player) {
    Actor *actor = D_801E1E48;
    GameObject *mover;
    u16 n = D_801E28A4;
    s16 x;
    s16 d;
    s32 t;
    s16 x0;
    u16 y0;
    s16 y1;

    if (n != 0) {
        do {
            if (actor->unk_12 == 0 && actor->unk_4 != 0 && actor->unk_4 != 0x55 &&
                (actor->unk_4 == 0x54 || actor->unk_4 == 0x8E || actor->kind == 0xE || player->unk_18E != 0 ||
                 player->unk_0EA == 4)) {
                mover = actor->obj;
                if (!(mover->unk_6C & 0x80) && ((actor->kind != 0 && actor->unk_28 == 0) || actor->unk_4 == 0x8E)) {
                    if (actor->kind != 0xE) {
                        x = mover->pos_x.s.hi;
                        if (x < D_801F9ACA) {
                            x += (D_801D8864.w + 1) >> 16;
                        }
                        d = abs(x - player->pos.s.lo);
                        if (((s16)mover->size.u.lo >> 1) + 8 >= d) {
                            t = player->pos.s.hi + 5;
                            d = abs(mover->pos_y.s.hi - t);
                            if (d < mover->size.s.hi) {
                            hit:
                                return func_8003FC30(player, actor);
                            }
                        }
                    } else {
                        x = mover->unk_1C.u.lo;
                        x0 = mover->pos_x.u.hi - x;
                        d = mover->unk_1C.u.hi;
                        y0 = mover->pos_y.u.hi - d;
                        d = mover->size.u.hi;
                        y1 = d + y0;
                        if (func_8003F4A8(x0, y0, player->pos.s.lo, player->pos.s.hi, x0, y1) == 1) {
                            goto hit;
                        }
                    }
                }
            }
            actor++;
        } while (--n != 0);
    }
    return 0;
}

void actor_take_hit(Monster *player, Actor *actor) {
    GameObject *obj = actor->obj;
    s32 kind;
    s32 vx;
    s32 score;

    if (actor->unk_4 == 0x54 || actor->kind == 0xE) {
        actor->unk_28 = 1;
        actor->unk_2C = player;
        actor->unk_3A = player->pos.u.lo;
        actor->unk_3C = player->pos.u.hi;
        return;
    }
    if (actor->kind == 0xB) {
        score = 0x5A;
        if (player->unk_1AC == 0) {
            score = 0x1E;
        }
        func_80054374(score, player);
        func_8005E0E8(player);
        player->unk_126 = 0;
        return;
    }
    actor->unk_28 = 1;
    if (actor->kind == 0xA) {
        func_80054374(0x28, player);
        func_800634D4(player, 4);
        player->unk_024++;
        return;
    }
    if (actor->kind == 1) {
        func_8003FB5C(player, actor);
        return;
    }
    if (actor->unk_4 == 0x12) {
        func_80040314(player);
    } else {
        score = 0x5A;
        if (player->unk_1AC == 0) {
            score = 0x1E;
        }
        func_80054374(score, player);
        func_8005E0E8(player);
    }
    kind = actor->kind;
    actor->unk_1C = D_800AA248.cur_obj->flags;
    if (kind != 3) {
        if (actor->unk_4 == 0x8E) {
            if (kind != 0) {
                func_80053D68(0x28000, player);
                player->action = 8;
                actor->obj->vel_x.w = (D_800AA248.cur_obj->flags & 0x10) ? -0x12000 : 0x12000;
                actor->obj->vel_y.w = -0x90000;
                actor->unk_20 = &D_8007E244;
                actor->unk_2C = player;
                func_8004155C(0, actor);
                return;
            }
            player->unk_020--;
            actor->unk_2C = player;
            switch (player->unk_0EA) {
            case 4:
                obj->vel_y.w = 0x80000;
                vx = 0x30000;
                if (D_800AA248.cur_obj->flags & 0x10) {
                    vx = -0x30000;
                }
                obj->vel_x.w = vx;
                break;
            case 1:
                obj->vel_y.w = -0x80000;
                obj->vel_x.w = -0x30000;
                break;
            case 2:
                obj->vel_y.w = -0x80000;
                obj->vel_x.w = 0x30000;
                break;
            default:
                obj->vel_y.w = -0x80000;
                vx = 0x30000;
                if (D_800AA268.p->flags & 0x10) {
                    vx = -0x30000;
                }
                obj->vel_x.w = vx;
                break;
            }
            player->unk_18A = 1;
            return;
        }
        func_80053D68(0x28000, player);
        if (player->prev_action == 0x4E || player->prev_action == 2) {
            return;
        }
        switch (actor->kind) {
        case 4:
        case 8:
        case 9:
        case 12:
        case 13:
            if (D_800AA248.cur_obj->pos_y.s.hi != 0xE1 || player->climb_side != 0 || player->unk_18E != 0) {
                if (actor->unk_4 == 0x56) {
                    player->unk_126 = 0x19;
                }
                actor->kind = 2;
                actor->unk_20 = &D_8007E2CC;
                func_80053D68(8, player);
                player->action = 8;
                return;
            }
            obj = actor->obj;
            player->action = 0x45;
            if (D_800AA248.cur_obj->flags & 0x10) {
                obj->vel_x.w = 0x6000;
                obj->pos_x.w = D_800AA248.cur_obj->pos_x.w - 0xF0000;
            } else {
                obj->vel_x.w = -0x6000;
                obj->pos_x.w = D_800AA248.cur_obj->pos_x.w + 0xF0000;
            }
            player->unk_1D0 = &actor->obj;
            return;
        }
    }
    func_80053D68(8, player);
    player->action = 8;
}

void func_8003FB5C(Monster *player, Actor *actor) {
    switch (actor->unk_4) {
    case 0x1F:
        func_80053C50(0x28000, player);
        if (player->prev_action != 2 && player->prev_action != 0x4E) {
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
        if (player->prev_action != 2 && player->prev_action != 0x4E) {
            player->action = 8;
            player->unk_126 = 1;
        }
        break;
    }
}

u16 func_8003FC30(Monster *player, Actor *actor) {
    if (actor->unk_14 == 0) {
        actor_take_hit(player, actor);
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
        if (!(D_800AA268.p->flags & 0x10)) {
            func_8003FE40(actor);
        } else {
            func_8003FE70(actor);
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
        D_800AA248.cur_obj->script.pc = (s32) *p;
    }
}

void func_80040294(void) {
    Anim **p;

    p = (Anim **)D_800AA248.cur_obj->arg.h;
    func_8004003C(D_800AA248.cur_obj->flags ^ 0x10, D_800AA248.cur_obj->owner.ai);
    if (abs(D_800AA248.unk_00) < 0x4B) {
        D_800AA248.cur_obj->script.pc = (s32) *p;
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
    effect->id = D_8009556C.id;
    mover = player->obj;
    effect->pos_x.s.hi = ((u16 *)&mover->pos_x.w)[1];
    effect->pos_y.s.hi = ((u16 *)&mover->pos_y.w)[1] | 0xC000;
    effect->flags = *(u16 *)&mover->priority - 1;
    D_800AA248.cur_obj = func_8001DCB4();
    D_800AA248.cur_obj->owner.monster = player;
    D_800AA248.cur_obj = saved;
}

void func_800403B4(Actor *actor) {
    GameObject *saved;

    saved = D_800AA248.cur_obj;
    D_800AA248.cur_obj = actor->obj;
    if (actor->unk_34 == NULL || actor->unk_34->unk_10 != 0) {
        func_8004155C(2, actor);
    }
    D_800AA248.cur_obj = saved;
}

void func_80040418(Actor *actor) {
    GameObject *mover;
    s32 v;
    s32 speed;

    mover = actor->obj;
    D_800AA248.cur_obj = mover;
    if (actor->unk_28 == 0) {
        if (actor->unk_10 == 0) {
            if (mover->unk_6C & 0x80) {
                return;
            }
            speed = 0x10000;
            switch (actor->unk_4) {
            case 0x2B:
                speed = 0x20000;
                break;
            case 0x24:
                speed = 0x5000;
                break;
            case 0x46:
                speed = 0x18000;
                break;
            case 0x45:
                speed = 0x10000;
                break;
            case 0x41:
                speed = 0x8000;
                break;
            }
            if (!(D_800AA268.p->flags & 0x10)) {
                speed = -speed;
            }
            D_800AA268.p->vel_x.w = speed;
            actor->unk_10 = 1;
        }
        v = D_800AA248.cur_obj->vel_x.w;
        if ((u16)func_8003E79C() == 1) {
            v = -v;
            D_800AA248.cur_obj->vel_x.w = v;
            D_800AA248.cur_obj->flags ^= 0x10;
        } else if (D_800AA248.unk_4C != 0) {
            func_8004155C(0x10, actor);
            return;
        }
        speed = D_800AA268.p->pos_x.w + v;
        speed &= D_801D8864.w;
        D_800AA268.p->pos_x.w = speed;
    } else {
        mover->vel_y.w = -0xA0000;
        D_800AA248.cur_obj->pos_y.w += -0x80000;
        func_8004155C(5, actor);
        func_80040B94(actor);
    }
}

void func_800405D8(Actor *actor) {
    GameObject *mover;

    mover = actor->obj;
    D_800AA248.cur_obj = mover;
    if (actor->unk_28 != 0) {
        mover->vel_y.w = -0xA0000;
        D_800AA248.cur_obj->pos_y.w += -0x80000;
        func_8004155C(5, actor);
        func_80040B94(actor);
    } else {
        mover->pos_x.w = (mover->vel_x.w + mover->pos_x.w) & D_801D8864.w;
    }
}

void func_80040668(void) {
}

void func_80040670(Actor *actor) {
    GameObject *mover;

    mover = actor->obj;
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

    mover = actor->obj;
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
    D_800AA268.p->pos_x.w = v & D_801D8864.w;
}

void func_80040824(Actor *actor) {
    D_800AA248.cur_obj = actor->obj;
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

    mover = actor->obj;
    D_800AA248.cur_obj = mover;
    mover->pos_y.w = 0x02000000;
    func_800415B4();
}

void func_80040930(Actor *actor) {
    GameObject *mover;
    s32 v;

    mover = actor->obj;
    D_800AA248.cur_obj = mover;
    v = mover->vel_x.w + mover->pos_x.w;
    v &= D_801D8864.w;
    mover->pos_x.w = v;
    v = D_800AA248.cur_obj->vel_y.w + 0x6500;
    D_800AA248.cur_obj->vel_y.w = v;
    D_800AA248.cur_obj->pos_y.w += v;
    if (v > 0 && D_800AA248.cur_obj->pos_y.w > 0xA5C100) {
        D_800AA248.cur_obj->pos_y.w = 0x2000000;
        func_800415B4();
    }
}

void func_800409CC(Actor *actor) {
    GameObject *mover;
    s32 v;

    mover = actor->obj;
    D_800AA248.cur_obj = mover;
    v = mover->pos_x.w + mover->vel_x.w;
    v &= D_801D8864.w;
    mover->pos_x.w = v;
    v = D_800AA248.cur_obj->vel_y.w + 0x6500;
    D_800AA248.cur_obj->vel_y.w = v;
    D_800AA248.cur_obj->pos_y.w += v;
    if (v > 0 && D_800AA248.cur_obj->pos_y.w > 0xE0FFFF) {
        D_800AA248.cur_obj->pos_y.w = 0xE10000;
        func_8004155C(7, actor);
        actor->unk_28 = 0;
    }
}

void func_80040A7C(Actor *actor) {
    GameObject *mover;

    mover = actor->obj;
    D_800AA248.cur_obj = mover;
    if (actor->unk_28 != 0) {
        mover->pos_y.w = 0x02000000;
        func_800415B4();
    }
}

void func_80040AB8(Actor *actor) {
    D_800AA248.cur_obj = actor->obj;
    if (actor->unk_28 != 0) {
        actor->unk_28 = 0;
        D_800AA248.cur_obj->pos_y.w = 0x2000000;
        func_800415B4();
    }
}

void func_80040B00(Actor *actor) {
    GameObject *mover;

    mover = actor->obj;
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

void func_80040CB8(Actor *actor) {
    u8 kind;

    D_800AA268.p = actor->obj;
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

void func_80040D68(Actor *actor) {
    GameObject *saved;
    AnimFrame *frame;
    s32 old_x;
    s32 old_y;
    s32 anchor;

    saved = D_800AA248.cur_obj;
    D_800AA248.cur_obj = actor->obj;
    if (actor->unk_30 == 0) {
        if (actor->unk_28 != 0) {
            actor->unk_32++;
            actor->unk_30 = 0x3C;
            func_80041344(actor->unk_32, actor);
            if (actor->unk_32 >= 4) {
                /* Keep the object in place across the change of animation: move it by the change of anchor. */
                old_x = D_800AA248.cur_obj->unk_1C.u.lo;
                old_y = D_800AA248.cur_obj->unk_1C.u.hi;
                func_8004155C(2, actor);
                frame = func_8001A784(*(s32 *)D_800AA248.cur_obj->anim);
                anchor = frame->unk_8;
                D_800AA248.cur_obj->pos_x.u.hi += anchor - old_x;
                anchor = frame->unk_A;
                D_800AA248.cur_obj->pos_y.u.hi += anchor - old_y;
            }
        }
    }
    if (actor->unk_30 != 0) {
        actor->unk_30--;
    }
    actor->unk_28 = 0;
    D_800AA248.cur_obj = saved;
}

void func_80040EA0(Actor *actor) {
    GameObject *mover;
    GameObject *saved;

    mover = actor->obj;
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
    D_800AA248.cur_obj->pos_x.w = D_801D8864.w & (D_800AA248.cur_obj->vel_x.w + D_800AA248.cur_obj->pos_x.w);
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

    mover = actor->obj;
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
    D_800AA248.cur_obj->pos_x.w = D_801D8864.w & (D_800AA248.cur_obj->vel_x.w + D_800AA248.cur_obj->pos_x.w);
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

    mover = actor->obj;
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
    D_800AA248.cur_obj->pos_x.w = D_801D8864.w & (D_800AA248.cur_obj->vel_x.w + D_800AA248.cur_obj->pos_x.w);
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

void func_800411E8(Actor *actor) {
    GameObject *saved;
    GameObject *mover;
    s32 d; /* one temporary for the speed, the distance and the bound: the original keeps all three in a1 */
    s16 target;
    s16 x;
    s32 v;

    saved = D_800AA248.cur_obj;
    D_800AA248.cur_obj = actor->obj;
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
        x = mover->pos_x.s.hi;
        d = abs(x - target);
        if (d < 0x32) {
            if (mover->vel_x.w != 0) {
                mover->unk_84 = 0;
            } else {
                mover->vel_x.w = 0x3500;
            }
        } else {
            d = target + 0x32;
            v = 0x300;
            if (d < x) {
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
    mover = actor->obj;
    D_800AA248.cur_obj = mover;
    if (!(mover->unk_6C & 0x80)) {
        mover->pos_x.w = (mover->vel_x.w + mover->pos_x.w) & D_801D8864.w;
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

    actor->kind = kind;
    anim = func_80041598(actor);
    if (anim != NULL) {
        func_8003EB5C(anim, D_800AA248.cur_obj);
    }
}

Anim *func_80041598(Actor *actor) {
    Anim **anims;

    anims = actor->unk_24;
    anims += actor->kind;
    return *anims;
}

void func_800415B4(void) {
    D_800AA248.cur_obj->owner.ai->unk_04 = 0;
    func_8004CFC0();
}

void func_800415E0(Actor *actor) {
    D_800AA248.cur_obj = actor->obj;
    actor->unk_4 = 0;
    func_8004CFC0();
}
