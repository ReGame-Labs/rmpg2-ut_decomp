#ifndef GAME_H
#define GAME_H

/* Types shared by several units. A struct is added here once its fields are known from the code that uses it;
 * fields not yet understood are unk_<offset>. */

#include "common.h"

/* A moving thing in the world: positions are 16.16 fixed point, read as s16 integer parts where the code needs
 * them (unk_16, unk_1A). Reached through D_800AA248.unk_20 by the AI handlers (game_8004160C). */
typedef struct Anim Anim;
typedef struct AiOrder AiOrder;   /* animation data in the tables linked after the libraries; not read yet */

typedef struct Mover {
    /* 0x00 */ u8 unk_0[0xC];
    /* 0x0C */ s32 unk_C;       /* a velocity, 16.16 */
    /* 0x10 */ s32 unk_10;      /* a velocity, 16.16 */
    /* 0x14 */ s32 unk_14;      /* a position, 16.16, wrapped with D_801D8864 */
    /* 0x18 */ s32 unk_18;      /* a position, 16.16 */
    /* 0x1C */ u8 unk_1C[0x6];
    /* 0x22 */ u16 unk_22;      /* flags; 0x10: facing */
    /* 0x24 */ u8 unk_24[0x20];
    /* 0x44 */ Anim *unk_44;
    /* 0x48 */ Anim *unk_48;    /* the current animation (func_8003EB5C) */
    /* 0x4C */ s8 unk_4C;
    /* 0x4D */ s8 unk_4D;
    /* 0x4E */ u8 unk_4E[0x16];
    /* 0x64 */ s32 unk_64;
    /* 0x68 */ u16 unk_68;      /* an animation index (game_80034590: func_80034C54) */
    /* 0x6A */ u16 unk_6A;      /* game_80034590: func_80034CB8 */
    /* 0x6C */ u16 unk_6C;      /* flags; 0x80 */
    /* 0x6E */ u8 unk_6E[0x12];
    /* 0x80 */ s16 unk_80;
    /* 0x82 */ u8 unk_82[0x2];
    /* 0x84 */ s32 unk_84;
    /* 0x88 */ s32 unk_88;
    /* 0x8C */ u8 unk_8C[0x4];
    /* 0x90 */ struct MoverLink *unk_90;
    /* 0x94 */ struct MoverTarget *unk_94;  /* game_80034590: func_800374FC */
} Mover;

/* What a mover's unk_94 points at: a record holding another mover (game_80034590). */
typedef struct MoverTarget {
    /* 0x00 */ u8 unk_0[0x4];
    /* 0x04 */ Mover *unk_4;
} MoverTarget;

typedef struct MoverLink {
    /* 0x00 */ u8 unk_0[0x4];
    /* 0x04 */ s16 unk_4;
    /* 0x06 */ u8 unk_6[0x6];
    /* 0x0C */ s16 unk_C;
} MoverLink;

/* The state of a monster's behaviour, driven by a table of state handlers (game_8004160C: func_80041A70 calls
 * handlers[unk_A](handlers, ai)). */
typedef struct Ai {
    /* 0x00 */ Mover *unk_0;    /* the monster's mover */
    /* 0x04 */ u8 unk_4[0x2];
    /* 0x06 */ u16 unk_6;       /* a kind; 0x17 and 0x18 are special */
    /* 0x08 */ s16 unk_8;       /* the current action */
    /* 0x0A */ u16 unk_A;       /* the state: the index into the handler table */
    /* 0x0C */ u16 unk_C;       /* 1 while the state is new */
    /* 0x0E */ u8 unk_E[0x2];
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
    /* 0x68 */ Mover *unk_68;
} AiTarget;

/* A state handler; the first argument is the table it was called from. */
typedef void (*AiHandler)(Ai *ai);

/* A player's monster as the game drives it (game_8003CD08: the actor files call into it); large and mostly
 * unknown. */
typedef struct Player {
    /* 0x000 */ u8 unk_0[0x24];
    /* 0x024 */ u16 unk_24;
    /* 0x026 */ u16 unk_26;
    /* 0x028 */ u16 unk_28;
    /* 0x02A */ u8 unk_2A[0x30];
    /* 0x05A */ s16 unk_5A;
    /* 0x05C */ u8 unk_5C[0xC];
    /* 0x068 */ Mover *unk_68;     /* the player's monster's mover (game_80034590: func_80039B60) */
    /* 0x06C */ u8 unk_6C[0x60];
    /* 0x0CC */ u16 unk_CC;      /* game_80034590: func_80038528 */
    /* 0x0CE */ u8 unk_CE[0x52];
    /* 0x120 */ u16 unk_120;
    /* 0x122 */ u16 unk_122;
    /* 0x124 */ u8 unk_124[0x2];
    /* 0x126 */ s16 unk_126;
    /* 0x128 */ u8 unk_128[0x1A];
    /* 0x142 */ u16 unk_142;     /* game_80034590: func_80037078 */
    /* 0x144 */ u8 unk_144[0x46];
    /* 0x18A */ s16 unk_18A;
    /* 0x18C */ u8 unk_18C[0x20];
    /* 0x1AC */ u16 unk_1AC;
    /* 0x1AE */ u8 unk_1AE[0x26];
    /* 0x1D4 */ s32 unk_1D4;     /* game_80034590: func_80038754 clears it when the player is dropped */
    /* 0x1D8 */ u8 unk_1D8[0x2C];
    /* 0x204 */ u16 unk_204;
    /* 0x206 */ u8 unk_206[0x1A];
} Player;                   /* 0x220: D_801E0B78 holds three, one per player slot */

/* A thing on screen with a mover and an animation set, driven by a state (unk_4) and a kind (unk_6): the
 * actors of game_8003CD08. */
typedef struct Actor {
    /* 0x00 */ Mover *unk_0;
    /* 0x04 */ u16 unk_4;       /* the state; 2 and 6 are tested, 11 is a bound */
    /* 0x06 */ s16 unk_6;       /* the kind: the index into unk_24 */
    /* 0x08 */ s16 unk_8;
    /* 0x0A */ u8 unk_A[0x4];
    /* 0x0E */ u16 unk_E;
    /* 0x10 */ u8 unk_10[0x4];
    /* 0x14 */ u16 unk_14;
    /* 0x16 */ u16 unk_16;
    /* 0x18 */ u8 unk_18[0x4];
    /* 0x1C */ u16 unk_1C;
    /* 0x1E */ u8 unk_1E[0x6];
    /* 0x24 */ Anim **unk_24;   /* one animation per kind */
    /* 0x28 */ u16 unk_28;
    /* 0x2A */ u16 unk_2A;
    /* 0x2C */ Player *unk_2C;
    /* 0x30 */ u16 unk_30;      /* a countdown */
    /* 0x32 */ u16 unk_32;
    /* 0x34 */ struct ActorLink *unk_34;
    /* 0x38 */ u8 unk_38[0x2];
    /* 0x3A */ u16 unk_3A;
    /* 0x3C */ u16 unk_3C;
    /* 0x3E */ u8 unk_3E[0x2];
} Actor;                    /* 0x40: D_801E1E48 holds twelve */

typedef struct ActorLink {
    /* 0x00 */ u8 unk_0[0x10];
    /* 0x10 */ u16 unk_10;
} ActorLink;

/* The game's globals at 0x800AA248 (.bss): the fields are those the code reaches through its address. */
typedef struct GameGlobals {
    /* 0x00 */ u8 unk_0[0x4];
    /* 0x04 */ s32 unk_4;
    /* 0x08 */ u8 unk_8[0x18];
    /* 0x20 */ Mover *unk_20;   /* the monster being moved */
    /* 0x24 */ u8 unk_24[0x18];
    /* 0x3C */ struct Effect *unk_3C;  /* the effect being set up (game_80034590: what func_8001D110 returns) */
    /* 0x40 */ u8 unk_40[0xC];
    /* 0x4C */ s32 unk_4C;
    /* 0x50 */ u8 unk_50[0x2A];
    /* 0x7A */ u16 unk_7A;      /* func_8003EB5C's result: 1 when the animation was already current */
} GameGlobals;

extern GameGlobals D_800AA248;

#endif /* GAME_H */
