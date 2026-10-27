#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "common.h"
#include "game.h"

/* This group of units' view of the game's shared types (GameObject, Monster, Building, the level state); include/game.h,
 * entity.h, game_8001781C.h and game_8002A330.h hold other groups' views of the same objects, to be unified. */

struct Monster;
struct Attacker;

/* Level-wide flags and per-player counters at D_8007BD78 (.data of game_8001781C). */
typedef struct {
    /* 0x00 */ s32 flags;              /* bit 0x20, bit 0x40 */
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08[4];          /* per player (D_801FA8A0[monster id - 1] - 1) */
} LevelFlags;

extern LevelFlags D_8007BD78;
extern u8 D_801FA8A0[];                /* the player of each monster id (1-based), 0 for none */

#endif /* GAMEOBJECT_H */
