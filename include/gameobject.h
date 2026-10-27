#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "common.h"
#include "game.h"

/* This group of units' view of the game's shared types (GameObject, Monster, Building, the level state); include/game.h,
 * entity.h, game_8001781C.h and game_8002A330.h hold other groups' views of the same objects, to be unified. */

struct Monster;
struct Attacker;

/* What func_8001D110 hands out to describe an object to create; func_8001DCB4 creates it from
 * GameState.new_def. */
typedef struct {
    /* 0x00 */ s32 id;                 /* the sprite/animation id */
    /* 0x04 */ u16 unk_04;             /* flags: 0x10 faces left (game_8004750C) */
    /* 0x06 */ u8 unk_06[0x06];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ Fixed pos_x;          /* written whole from an object's position, or its integer half alone */
    /* 0x14 */ Fixed pos_y;
    /* 0x18 */ u8 unk_18[0x04];
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 flags;
    /* 0x24 */ u8 unk_24[0x04];
    /* 0x28 */ void *anim;
} ObjectDef;


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

/* The level state at D_800AA248 (.bss). Fields from game_80043E28 and game_8004E574; the size is not known. */
typedef struct {
    /* 0x00 */ u8 unk_00[0x20];
    /* 0x20 */ GameObject *cur_obj;    /* the object being updated (D_800AA268) */
    /* 0x24 */ u8 unk_24[0x18];
    /* 0x3C */ ObjectDef *new_def;     /* the object being created */
    /* 0x40 */ u8 unk_40[0x0C];
    /* 0x4C */ s32 unk_4C;
    /* 0x50 */ u8 unk_50[0x28];
    /* 0x78 */ s16 unk_78;
    /* 0x7A */ s16 unk_7A;
} GameState;

extern GameState D_800AA248;

/* Level-wide flags and per-player counters at D_8007BD78 (.data of game_8001781C). */
typedef struct {
    /* 0x00 */ s32 flags;              /* bit 0x20, bit 0x40 */
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08[4];          /* per player (D_801FA8A0[monster id - 1] - 1) */
} LevelFlags;

extern LevelFlags D_8007BD78;
extern u8 D_801FA8A0[];                /* the player of each monster id (1-based), 0 for none */
extern s32 D_800AA2DC;
extern u16 D_800AA2C0;             /* 1 when a hit landed this frame */

#endif /* GAMEOBJECT_H */
