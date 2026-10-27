#ifndef GAME_80034590_H
#define GAME_80034590_H

#include "common.h"
#include "game.h"

/* The group's views of the shared records (game_80034590, game_8003CD08, game_8004160C, game_80043118). */

/* A moving thing in the world: positions are 16.16 fixed point, read as s16 integer parts where the code needs
 * them (unk_16, unk_1A). Reached through D_800AA248.unk_20 by the AI handlers (game_8004160C). */
typedef struct Anim Anim;
typedef struct AiOrder AiOrder;   /* animation data in the tables linked after the libraries; not read yet */

/* What a mover's unk_94 points at: a record holding another mover (game_80034590). */
typedef struct MoverTarget {
    /* 0x00 */ u8 unk_0[0x4];
    /* 0x04 */ GameObject *unk_4;
} MoverTarget;

typedef struct MoverLink {
    /* 0x00 */ u8 unk_0[0x4];
    /* 0x04 */ s16 unk_4;
    /* 0x06 */ u8 unk_6[0x6];
    /* 0x0C */ s16 unk_C;
    /* 0x0E */ u8 unk_E[0x2];
    /* 0x10 */ struct Actor *unk_10;  /* game_8003CD08: func_8003CEA0 */
} MoverLink;

/* The state of a monster's behaviour, driven by a table of state handlers (game_8004160C: func_80041A70 calls
 * handlers[unk_A](handlers, ai)). */
typedef struct Ai {
    /* 0x00 */ GameObject *unk_0;    /* the monster's mover */
    /* 0x04 */ u16 unk_4;       /* the player slot last targeted (game_8003CD08: func_8003E630) */
    /* 0x06 */ u16 unk_6;       /* a kind; 0x17 and 0x18 are special */
    /* 0x08 */ s16 unk_8;       /* the current action */
    /* 0x0A */ u16 unk_A;       /* the state: the index into the handler table */
    /* 0x0C */ u16 unk_C;       /* 1 while the state is new */
    /* 0x0E */ u16 unk_E;       /* game_8003CD08: func_8003D11C */
    /* 0x10 */ AiOrder *unk_10;
    /* 0x14 */ struct AiTarget *unk_14;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ u16 unk_1A;
    /* 0x1C */ AiOrder *unk_1C;
    /* 0x20 */ u8 unk_20[0x2];
    /* 0x22 */ u16 unk_22;
    /* 0x24 */ u16 unk_24;
    /* 0x26 */ u8 unk_26[0x2];
    /* 0x28 */ struct AiLink *unk_28;
    /* 0x2C */ u8 unk_2C[0x2];
    /* 0x2E */ s16 unk_2E;
    /* 0x30 */ u8 unk_30[0x2];
    /* 0x32 */ u16 unk_32;
    /* 0x34 */ u16 unk_34;
    /* 0x36 */ s16 unk_36;
    /* 0x38 */ u16 unk_38;      /* a countdown */
    /* 0x3A */ u8 unk_3A[0x6];
} Ai;                       /* 0x40: D_801D85C8 holds five */

struct AiOrder {
    /* 0x00 */ u8 unk_0[0x4];
    /* 0x04 */ u16 unk_4;
    /* 0x06 */ u16 unk_6;
    /* 0x08 */ s32 unk_8;
    /* 0x0C */ s32 unk_C;
    /* 0x10 */ u8 unk_10[0x4];
    /* 0x14 */ u16 unk_14;
};

typedef struct AiLink {
    /* 0x00 */ u8 unk_0[0x6];
    /* 0x06 */ u16 unk_6;
    /* 0x08 */ struct AiLinkInfo *unk_8;
} AiLink;

typedef struct AiLinkInfo {
    /* 0x00 */ u8 unk_0[0x14];
    /* 0x14 */ u16 unk_14;
} AiLinkInfo;

typedef struct AiTarget {
    /* 0x00 */ u8 unk_0[0x68];
    /* 0x68 */ GameObject *unk_68;
} AiTarget;

/* A state handler; the first argument is the table it was called from. */
typedef void (*AiHandler)(Ai *ai);

/* A thing on screen with a mover and an animation set, driven by a state (unk_4) and a kind (unk_6): the
 * actors of game_8003CD08. */
typedef struct Actor {
    /* 0x00 */ GameObject *unk_0;
    /* 0x04 */ u16 unk_4;       /* the state; 2 and 6 are tested, 11 is a bound */
    /* 0x06 */ s16 unk_6;       /* the kind: the index into unk_24 */
    /* 0x08 */ s16 unk_8;
    /* 0x0A */ u8 unk_A[0x4];
    /* 0x0E */ u16 unk_E;
    /* 0x10 */ u16 unk_10;      /* the facing step (game_8003CD08: func_8003FD30) */
    /* 0x12 */ u16 unk_12;      /* game_8003CD08: func_8003EF64 skips the actor when set */
    /* 0x14 */ u16 unk_14;
    /* 0x16 */ u16 unk_16;
    /* 0x18 */ u8 unk_18[0x4];
    /* 0x1C */ u16 unk_1C;
    /* 0x1E */ u8 unk_1E[0x2];
    /* 0x20 */ void (**unk_20)(struct Actor *);  /* one handler per kind (game_8003CD08: func_8003EC40) */
    /* 0x24 */ Anim **unk_24;   /* one animation per kind */
    /* 0x28 */ u16 unk_28;
    /* 0x2A */ u16 unk_2A;
    /* 0x2C */ Monster *unk_2C;
    /* 0x30 */ u16 unk_30;      /* a countdown */
    /* 0x32 */ u16 unk_32;
    /* 0x34 */ struct ActorLink *unk_34;
    /* 0x38 */ s16 unk_38;      /* a target x (game_8003CD08: func_800411E8) */
    /* 0x3A */ s16 unk_3A;      /* a position pair (game_8003CD08: func_80041344 passes them signed) */
    /* 0x3C */ s16 unk_3C;
    /* 0x3E */ u16 unk_3E;      /* the index into D_8007E1E4 (game_8003CD08: func_80040B94) */
} Actor;                    /* 0x40: D_801E1E48 holds twelve */

typedef struct ActorLink {
    /* 0x00 */ u8 unk_0[0x4];
    /* 0x04 */ u16 unk_4;       /* an x offset (game_8003CD08: func_8003ED4C) */
    /* 0x06 */ u8 unk_6[0xA];
    /* 0x10 */ u16 unk_10;
} ActorLink;

/* The game's globals at 0x800AA248 (.bss): the fields are those the code reaches through its address. */
typedef struct GameGlobals {
    /* 0x00 */ s32 unk_0;       /* game_8003CD08: func_80040294 */
    /* 0x04 */ s32 unk_4;
    /* 0x08 */ u8 unk_8[0x4];
    /* 0x0C */ s32 unk_C;       /* game_8003CD08: func_8004022C */
    /* 0x10 */ u8 unk_10[0x10];
    /* 0x20 */ GameObject *unk_20;   /* the monster being moved */
    /* 0x24 */ u8 unk_24[0x18];
    /* 0x3C */ struct Effect *unk_3C;  /* the effect being set up (game_80034590: what func_8001D110 returns) */
    /* 0x40 */ u8 unk_40[0xC];
    /* 0x4C */ s32 unk_4C;
    /* 0x50 */ u8 unk_50[0x28];
    /* 0x78 */ s16 unk_78;      /* game_8003CD08: func_8003E79C's result */
    /* 0x7A */ u16 unk_7A;      /* func_8003EB5C's result: 1 when the animation was already current */
} GameGlobals;

extern GameGlobals D_800AA248;


/* The records of game_80034590: 0x78 bytes each, six at D_801FAC9C (D_801D8730 counts them), each with a mover
 * (unk_0), a kind (unk_6), an action (unk_8) and a state (unk_A), updated by a dispatcher per kind on the action.
 * The later functions of the file read the same record with signed counters (NpcS below): a second declaration. */
/* What an Npc's unk_14 points at: two velocities set when it is hit (game_8003CD08: func_8003D30C). */
typedef struct NpcTarget {
    /* 0x00 */ u8 unk_0[0x8];
    /* 0x08 */ s32 unk_8;
    /* 0x0C */ u8 unk_C[0x4];
    /* 0x10 */ s32 unk_10;
} NpcTarget;

typedef struct Npc {
    /* 0x00 */ GameObject *unk_0;
    /* 0x04 */ u16 unk_4;
    /* 0x06 */ u16 unk_6;       /* the kind */
    /* 0x08 */ u16 unk_8;       /* the action */
    /* 0x0A */ u16 unk_A;
    /* 0x0C */ u16 unk_C;       /* 1 while the action is new */
    /* 0x0E */ u16 unk_E;       /* game_8003CD08: func_8003D30C */
    /* 0x10 */ u8 unk_10[0x4];
    /* 0x14 */ struct NpcTarget *unk_14;  /* game_8003CD08: func_8003D30C */
    /* 0x18 */ s16 unk_18;      /* game_8003CD08: func_8003D228 */
    /* 0x1A */ u16 unk_1A;
    /* 0x1C */ u16 unk_1C;      /* a countdown */
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ s16 unk_24;
    /* 0x26 */ u8 unk_26[0x4];
    /* 0x2A */ u16 unk_2A;
    /* 0x2C */ u16 unk_2C;
    /* 0x2E */ u16 unk_2E;
    /* 0x30 */ u8 unk_30[0x4];
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ u8 unk_38[0x6];
    /* 0x3E */ s16 unk_3E;
    /* 0x40 */ GameObject *unk_40;
    /* 0x44 */ u16 unk_44;      /* the mover's flags when it was set up */
    /* 0x46 */ s16 unk_46;
    /* 0x48 */ s16 unk_48;
    /* 0x4A */ s16 unk_4A;
    /* 0x4C */ s16 unk_4C;
    /* 0x4E */ u16 unk_4E;
    /* 0x50 */ u8 unk_50[0x4];
    /* 0x54 */ Monster *unk_54;
    /* 0x58 */ u8 unk_58[0x4];
    /* 0x5C */ u16 unk_5C;
    /* 0x5E */ u16 unk_5E;
    /* 0x60 */ Monster *unk_60;
    /* 0x64 */ Monster *unk_64;
    /* 0x68 */ u8 unk_68[0x8];
    /* 0x70 */ GameObject *unk_70;
    /* 0x74 */ GameObject *unk_74;
} Npc;                      /* 0x78 */

/* The same record as the later functions declare it: signed counters. */
typedef struct NpcS {
    /* 0x00 */ GameObject *unk_0;
    /* 0x04 */ u16 unk_4;
    /* 0x06 */ u16 unk_6;
    /* 0x08 */ u16 unk_8;
    /* 0x0A */ u16 unk_A;
    /* 0x0C */ u16 unk_C;
    /* 0x0E */ u8 unk_E[0x6];
    /* 0x14 */ u16 unk_14;
    /* 0x16 */ u8 unk_16[0x4];
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ u16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ u16 unk_24;
    /* 0x26 */ u8 unk_26[0x4];
    /* 0x2A */ u16 unk_2A;
    /* 0x2C */ u16 unk_2C;
    /* 0x2E */ u16 unk_2E;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ u8 unk_38[0x6];
    /* 0x3E */ s16 unk_3E;
    /* 0x40 */ s16 unk_40;
    /* 0x42 */ s16 unk_42;
    /* 0x44 */ s16 unk_44;
    /* 0x46 */ s16 unk_46;
    /* 0x48 */ s16 unk_48;
    /* 0x4A */ s16 unk_4A;
    /* 0x4C */ s16 unk_4C;
    /* 0x4E */ u16 unk_4E;
    /* 0x50 */ u8 unk_50[0x4];
    /* 0x54 */ u16 unk_54;
    /* 0x56 */ u8 unk_56[0x6];
    /* 0x5C */ u16 unk_5C;
    /* 0x5E */ u16 unk_5E;
    /* 0x60 */ Monster *unk_60;
    /* 0x64 */ Monster *unk_64;
    /* 0x68 */ u8 unk_68[0x10];
} NpcS;

/* What func_8001D110 returns and func_8001DCB4 takes: an effect to spawn, described by a table (unk_28, its first
 * word copied to unk_0) at a position (unk_12, unk_16). */
typedef struct EffectDef {
    /* 0x00 */ s32 unk_0;       /* copied into the effect's unk_0 */
} EffectDef;

typedef struct Effect {
    /* 0x00 */ s32 unk_0;
    /* 0x04 */ u8 unk_4[0x8];
    /* 0x0C */ s32 unk_C;       /* game_8003CD08: func_8003ED4C */
    /* 0x10 */ u8 unk_10[0x2];
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ u8 unk_14[0x2];
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ u8 unk_18[0x8];
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ u8 unk_24[0x4];
    /* 0x28 */ EffectDef *unk_28;
} Effect;

#endif /* GAME_80034590_H */
