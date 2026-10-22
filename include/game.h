#ifndef GAME_H
#define GAME_H

/* Types shared by several units. A struct is added here once its fields are known from the code that uses it;
 * fields not yet understood are unk_<offset>. */

#include "common.h"

/* A moving thing in the world: positions are 16.16 fixed point, read as s16 integer parts where the code needs
 * them (unk_16, unk_1A). Reached through D_800AA248.unk_20 by the AI handlers (game_8004160C). */
typedef struct Mover {
    /* 0x00 */ u8 unk_0[0xC];
    /* 0x0C */ s32 unk_C;       /* a velocity, 16.16 */
    /* 0x10 */ s32 unk_10;      /* a velocity, 16.16 */
    /* 0x14 */ s32 unk_14;      /* a position, 16.16, wrapped with D_801D8864 */
    /* 0x18 */ s32 unk_18;      /* a position, 16.16 */
    /* 0x1C */ u8 unk_1C[0x6];
    /* 0x22 */ u16 unk_22;      /* flags; 0x10: facing */
    /* 0x24 */ u8 unk_24[0x48];
    /* 0x6C */ u16 unk_6C;      /* flags; 0x80 */
    /* 0x6E */ u8 unk_6E[0x12];
    /* 0x80 */ s16 unk_80;
    /* 0x82 */ u8 unk_82[0x2];
    /* 0x84 */ s32 unk_84;
    /* 0x88 */ s32 unk_88;
} Mover;

/* The state of a monster's behaviour, driven by a table of state handlers (game_8004160C: func_80041A70 calls
 * handlers[unk_A](handlers, ai)). */
typedef struct Ai {
    /* 0x00 */ s32 unk_0;
    /* 0x04 */ u8 unk_4[0x2];
    /* 0x06 */ u16 unk_6;       /* a kind; 0x17 and 0x18 are special */
    /* 0x08 */ s16 unk_8;       /* the current action */
    /* 0x0A */ u16 unk_A;       /* the state: the index into the handler table */
    /* 0x0C */ u16 unk_C;       /* 1 while the state is new */
    /* 0x0E */ u8 unk_E[0x6];
    /* 0x14 */ struct AiTarget *unk_14;
    /* 0x18 */ u8 unk_18[0xC];
    /* 0x24 */ u16 unk_24;
    /* 0x26 */ u8 unk_26[0x2];
    /* 0x28 */ struct AiLink *unk_28;
    /* 0x2C */ u8 unk_2C[0xA];
    /* 0x36 */ s16 unk_36;
    /* 0x38 */ u16 unk_38;      /* a countdown */
} Ai;

typedef struct AiLink {
    /* 0x00 */ u8 unk_0[0x8];
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

/* The game's globals at 0x800AA248 (.bss): the fields are those the code reaches through its address. */
typedef struct GameGlobals {
    /* 0x00 */ u8 unk_0[0x20];
    /* 0x20 */ Mover *unk_20;   /* the monster being moved */
    /* 0x24 */ u8 unk_24[0x28];
    /* 0x4C */ s32 unk_4C;
} GameGlobals;

extern GameGlobals D_800AA248;

#endif /* GAME_H */
