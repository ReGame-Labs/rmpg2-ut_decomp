#ifndef MAIN_H
#define MAIN_H

#include "common.h"
#include "game.h"
#include "psyq/libc2.h"
#include "psyq/libapi.h"
#include "psyq/libgpu.h"
#include "psyq/libetc.h"
#include "npc.h"

/* Provisional types of src/main/main.c, the first file of the game's code (main, the game loop, the
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

/* An entry of the list at 0x8007BA40 (func_800252CC), ended by a NULL def: for the buildings made from def, what
 * to set to 1. code 0xFFFF: every item's parts (func_800253F0 0); 0xFFF0..0xFFFE: the three parts of item
 * 0xFFFF - code; 0x1FFFD..0x1FFFF: func_800253F0's selector 0x20000 - code; else the s16 at Building + code + 0xAC. */
typedef struct BuildingPatch {
    BuildingDef *def;
    s32 code;
} BuildingPatch;

/* A monster frame's boxes, the signed bytes from SpriteFrame + 0x0C (main_update_boxes): offsets from the object's
 * position, x mirrored when it faces left. box2, box: Monster.box2_*, box_*; hit: hit_*; point: Monster.pos (less
 * the frame's origin), 0 none. */
typedef struct FrameBoxes {
    s8 box2[4];
    s8 box[4];
    s8 hit[4];
    s8 point[2];
} FrameBoxes;
#define FRAME_BOXES(frame) ((FrameBoxes *) &(frame)->unk_0C)

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

/* Where an Npc's object starts (func_800210C8, the table D_8007B358 indexed by Npc.start): a position
 * relative to the camera, a speed, and flags for the object. */
typedef struct Unk7B358 {
    s32 x;
    s32 y;
    s32 vel_x;
    s32 vel_y;
    u16 flags;
} Unk7B358;

/* A glyph of the font (func_8001B128 maps a packed glyph index to one): its size at unk_4/unk_6. */
typedef struct Glyph {
    s32 unk_0;
    s16 unk_4;
    s16 unk_6;
} Glyph;

/* A step of an Npc's flight towards its target (func_80022EC0): the speed and the animation for one of 8x8
 * direction classes (the distances halved until both are below 8). */
typedef struct NpcStep {
    s32 vel_x;
    s32 vel_y;
    Anim *anim;
} NpcStep;

#endif /* MAIN_H */
