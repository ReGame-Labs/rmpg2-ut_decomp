#ifndef GAME_80057C94_H
#define GAME_80057C94_H

#include "common.h"
#include "game.h"

/* Declarations shared by game_80057C94, game_8003B568 and game_80034590. */

/* An entry of the spawn lists func_80025C08 picks (D_8007DDA4 for func_8003B6E0, D_800830AC for func_8003C3B0,
 * D_8007DA48 for func_8003684C): an animation and five halfwords the record takes over. The first entry of D_8007DDA4's list holds the count in
 * unk_04; D_800830AC's ends at an entry whose unk_04 is 0. */
typedef struct SpawnItem {
    /* 0x00 */ Anim *anim;
    /* 0x04 */ u16 unk_04;     /* the kind */
    /* 0x06 */ u16 unk_06;     /* x */
    /* 0x08 */ u16 unk_08;     /* y */
    /* 0x0A */ u16 unk_0A;     /* flags */
    /* 0x0C */ u16 unk_0C;
    /* 0x0E */ s16 unk_0E;     /* func_8003B6E0: -1 for a random countdown */
} SpawnItem;

/* The eight 0x58-byte records of D_801FA9BC (D_801E29B0 in use): each with an object, a kind (unk_06, 1..0x1C)
 * and a state (unk_08: 2 live, 3 taken); func_8005C71C hands one to the monster that touches it (unk_54). */
typedef struct UnkStructB1 {  /* provisional: a 0x58-byte record of the table at D_801FA9BC */
    GameObject *unk_00;
    s16 unk_04;
    u16 unk_06;
    u16 unk_08;
    s16 unk_0A;
    u8 pad_0C[0x8];
    Monster *unk_14;
    u8 pad_18[0x2];
    u16 unk_1A;
    u16 unk_1C;     /* a countdown (random 200..299 or from the spawn list) */
    u8 pad_1E[0x12];
    s32 unk_30;     /* y acceleration, 16.16 */
    s32 unk_34;     /* x acceleration, 16.16 */
    u8 pad_38[0x6];
    u16 unk_3E;
    GameObject *unk_40;
    u16 unk_44;
    u8 pad_46[0x8];
    u16 unk_4E;
    u16 unk_50;
    u8 pad_52[0x2];
    Monster *unk_54;
} UnkStructB1;

extern UnkStructB1 D_801FA9BC[];
extern u16 D_801E29B0;

#endif /* GAME_80057C94_H */
