#ifndef GAME_80034590_H
#define GAME_80034590_H

#include "common.h"
#include "game.h"

/* The records of game_80034590: 0x78 bytes each, six at D_801FAC9C (D_801D8730 counts them), each with a mover
 * (unk_0), a kind (unk_6), an action (unk_8) and a state (unk_A), updated by a dispatcher per kind on the action.
 * The later functions of the file read the same record with signed counters (NpcS below): a second declaration. */
typedef struct Npc {
    /* 0x00 */ Mover *unk_0;
    /* 0x04 */ u16 unk_4;
    /* 0x06 */ u16 unk_6;       /* the kind */
    /* 0x08 */ u16 unk_8;       /* the action */
    /* 0x0A */ u16 unk_A;
    /* 0x0C */ u16 unk_C;       /* 1 while the action is new */
    /* 0x0E */ u8 unk_E[0xC];
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
    /* 0x40 */ s16 unk_40;
    /* 0x42 */ s16 unk_42;
    /* 0x44 */ u16 unk_44;      /* the mover's flags when it was set up */
    /* 0x46 */ s16 unk_46;
    /* 0x48 */ s16 unk_48;
    /* 0x4A */ s16 unk_4A;
    /* 0x4C */ s16 unk_4C;
    /* 0x4E */ u16 unk_4E;
    /* 0x50 */ u8 unk_50[0x4];
    /* 0x54 */ u16 unk_54;      /* the mover's flags when it was set up */
    /* 0x56 */ u8 unk_56[0x6];
    /* 0x5C */ u16 unk_5C;
    /* 0x5E */ u16 unk_5E;
    /* 0x60 */ Player *unk_60;
    /* 0x64 */ Player *unk_64;
    /* 0x68 */ u8 unk_68[0x10];
} Npc;                      /* 0x78 */

/* The same record as the later functions declare it: signed counters. */
typedef struct NpcS {
    /* 0x00 */ Mover *unk_0;
    /* 0x04 */ u16 unk_4;
    /* 0x06 */ s16 unk_6;
    /* 0x08 */ u16 unk_8;
    /* 0x0A */ u16 unk_A;
    /* 0x0C */ u16 unk_C;
    /* 0x0E */ u8 unk_E[0xC];
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s16 unk_1C;
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
    /* 0x60 */ Player *unk_60;
    /* 0x64 */ Player *unk_64;
    /* 0x68 */ u8 unk_68[0x10];
} NpcS;

#endif /* GAME_80034590_H */
