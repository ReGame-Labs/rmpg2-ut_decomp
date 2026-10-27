#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "common.h"
#include "game.h"

/* This group of units' view of the game's shared types (GameObject, Monster, Building, the level state); include/game.h,
 * entity.h, game_8001781C.h and game_8002A330.h hold other groups' views of the same objects, to be unified. */

struct Monster;
struct Attacker;

/* A building (a record of D_801D3DC8, 0x584 bytes; D_801E29A4 holds the count). Fields from game_8004E574 and game_8004C064. */
typedef struct {
    /* 0x000 */ u8 unk_000[0x32];
    /* 0x032 */ u16 unk_032;
    /* 0x034 */ u8 unk_034[0x24];
    /* 0x058 */ u16 unk_058;
    /* 0x05A */ u8 unk_05A[0x1E];
    /* 0x078 */ u16 unk_078;
    /* 0x07A */ u8 unk_07A[0x50A];
} Building;                            /* 0x584 bytes */

extern Building D_801D3DC8[];

/* Level-wide flags and per-player counters at D_8007BD78 (.data of game_8001781C). */
typedef struct {
    /* 0x00 */ s32 flags;              /* bit 0x20, bit 0x40 */
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08[4];          /* per player (D_801FA8A0[monster id - 1] - 1) */
} LevelFlags;

extern LevelFlags D_8007BD78;
extern u8 D_801FA8A0[];                /* the player of each monster id (1-based), 0 for none */

#endif /* GAMEOBJECT_H */
