#ifndef GAME_8001781C_H
#define GAME_8001781C_H

#include "common.h"
#include "game.h"
#include "psyq/libc2.h"
#include "psyq/libapi.h"
#include "psyq/libgpu.h"
#include "psyq/libetc.h"

/* Provisional types of src/main/game_8001781C.c, the first file of the game's code (main, the game loop, the
 * sprite objects). Field names are offsets until their meaning is known; the types are the ones the code's loads and
 * stores imply. */


/* A 0x14-byte record of the 1024-entry table at 0x801C542C. */
typedef struct Unk1C542C {
    s16 unk_0;              /* -1 when free */
    u8 pad_2[0x2];
    s32 unk_4;              /* the VRAM position: x in 0x80 steps (bank) and 0x10 steps (column) */
    s32 unk_8;              /* the VRAM y: bit 8 picks the lower half, bits 5-7 the row */
    s32 unk_C;              /* width */
    s32 unk_10;             /* height */
} Unk1C542C;

/* A 0x10-byte record of the table at 0x801F9AE4 (func_8001B350): a use count and the slot it holds. */
typedef struct Unk1F9AE4 {
    u8 pad_0[0x4];
    s16 unk_4;
    u8 pad_6[0x2];
    s32 unk_8;
    s32 unk_C;
} Unk1F9AE4;

/* An entry of the building lists func_80025C08 returns (func_80024C2C): the definition, then the placement. */
typedef struct Unk24C2C {
    BuildingDef *unk_0;
    s32 unk_4;
    u16 unk_8;
    u16 unk_A;
    u16 unk_C;
    u8 pad_E[0x2];
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x2];
} Unk24C2C;

/* The object of func_80029510: a value at unk_8 clamped to 0x440000. */
typedef struct Unk29510 {
    u8 pad_0[0x8];
    s32 unk_8;
    u8 pad_C[0x58];
    u16 unk_64;
    u8 pad_66[0x2];
    u8 pad_68[0x88];
    s32 unk_F0;
} Unk29510;

/* An 8-byte record of the two 20-entry tables at 0x801FA738 and 0x801FA7EC. */
typedef struct UnkFA738 {
    s32 unk_0;
    s16 unk_4;
    s16 unk_6;
} UnkFA738;

typedef struct Unk1E638 {
    u8 pad_0[0x4];
    Fixed unk_4;
    s32 unk_8;
} Unk1E638;

/* The sprite func_800299C4 drives (the "press start" banner?) at 0x801E2894: the sprite, a frame counter, a state. */
typedef struct Unk1E2894 {
    GameObject *unk_0;
    u16 unk_4;
    s16 unk_6;
} Unk1E2894;


/* A sprite bank's header (func_8001AD1C loads its images): the counts of 256x256 and 256x128 images. */
typedef struct Unk1AD1C {
    u8 pad_0[0x4];
    u32 unk_4;
    u32 unk_8;
} Unk1AD1C;

/* The word at 0x801F9A30, a vertical speed (0x20000, 0x80000, -0x20000). A one-member struct: GCC 2.8 keeps its
 * stores in order with the stores into D_801D3D64 only then (func_80028160). */
typedef struct Unk1F9A30 {
    s32 unk_0;
} Unk1F9A30;

/* A glyph of the font (func_8001B128 maps a packed glyph index to one): its size at unk_4/unk_6. */
typedef struct Glyph {
    s32 unk_0;
    s16 unk_4;
    s16 unk_6;
} Glyph;

#endif /* GAME_8001781C_H */
