#ifndef GAME_80043E28_H
#define GAME_80043E28_H

#include "game.h"

/* game_80043E28: the attackers (the military units that hunt the monsters): a pool of four, each driving one
 * GameObject through a state machine of handlers (one function per state and type). */
typedef struct Attacker {
    /* 0x00 */ GameObject *obj;
    /* 0x04 */ u16 type;               /* 0: free slot; 1..0xB index D_8007F1F4 */
    /* 0x06 */ u16 state;
    /* 0x08 */ u8 unk_08[0x02];
    /* 0x0A */ u16 unk_0A;
    /* 0x0C */ u8 unk_0C[0x04];
    /* 0x10 */ s32 unk_10;             /* a vertical acceleration, 16.16 */
    /* 0x14 */ s16 timer;
    /* 0x16 */ u16 unk_16;
    /* 0x18 */ u16 unk_18;
    /* 0x1A */ u8 unk_1A[0x02];
    /* 0x1C */ struct Monster *hit_by;   /* the monster that hit it */
    /* 0x20 */ u16 unk_20;
    /* 0x22 */ u16 unk_22;
} Attacker;                            /* 0x24 bytes */

extern Attacker D_801FA8A8[4];
extern u16 D_801E1C84;                 /* attackers in use */
extern s32 D_8007F1F4[];               /* the sprite id per attacker type */
extern u16 D_8007F224[2];

#endif /* GAME_80043E28_H */
