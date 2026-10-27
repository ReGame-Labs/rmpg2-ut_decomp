#ifndef GAME_8001781C_H
#define GAME_8001781C_H

#include "common.h"
#include "game.h"
#include "psyq/libc.h"
#include "psyq/libapi.h"
#include "psyq/libgpu.h"
#include "psyq/libetc.h"

/* Provisional types of src/main/game_8001781C.c, the first file of the game's code (main, the game loop, the
 * sprite objects). Field names are offsets until their meaning is known; the types are the ones the code's loads and
 * stores imply. */


/* Three slots of freed resources (SpriteSlots.unk_C, unk_24, unk_3C ... released through func_8001E4B0). */
typedef struct SpriteSlots {
    GameObject *unk_0;
    u8 pad_4[0x8];
    GameObject *unk_C;
    u8 pad_10[0x4];
    struct Ai *unk_14;
    s32 unk_18;
    GameObject *unk_1C;
    u8 pad_20[0x4];
    GameObject *unk_24;
    u8 pad_28[0x4];
    struct Ai *unk_2C;
    s32 unk_30;
    GameObject *unk_34;
    u8 pad_38[0x4];
    GameObject *unk_3C;
    u8 pad_40[0x4];
    struct Ai *unk_44;
    s32 unk_48;
    GameObject *unk_4C;
} SpriteSlots;

/* The block at 0x801D3D64. */
typedef struct Unk801D3D64 {
    u8 pad_0[0x8];
    s16 unk_8;              /* = D_801D3D6C */
    u8 pad_A[0x10];
    u16 unk_1A;
    u16 unk_1C;
    u8 pad_1E[0x6];
    s16 unk_24;
    s16 unk_26;
    s16 unk_28;
    u8 pad_2A[0x2];
    s32 unk_2C;
    u8 pad_30[0x2C];
    u16 unk_5C;
    u16 unk_5E;
    u8 pad_60[0x2];
    u16 unk_62;
} Unk801D3D64;

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

/* The frame's drawing state at D_801FAC80: the draw and display environments, the ordering table at 0x154. */
typedef struct Unk1FAC80 {
    DRAWENV draw;
    DISPENV disp;
    u8 pad_70[0xE4];
    unsigned long ot[1];
} Unk1FAC80;

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

/* The level flags at 0x8007BD78 (cleared as 0x94 bytes). */
typedef struct Unk7BD78 {
    s32 unk_0;
    u8 pad_4[0x90];
} Unk7BD78;

/* An animation (the tables in .data from 0x8008AE40 on); opaque here. */
typedef struct Anim Anim;

/* A glyph of the font (func_8001B128 maps a packed glyph index to one): its size at unk_4/unk_6. */
typedef struct Glyph {
    s32 unk_0;
    s16 unk_4;
    s16 unk_6;
} Glyph;

/* The text printer's state at 0x801D8588 (func_8001EDE4 ... func_8001F61C): the string at unk_1C, the pen at
 * unk_C/unk_E, the glyph table at unk_14, the flags at unk_24. */
typedef struct TextState {
    s32 unk_0;
    void (*unk_4)(void);
    s32 unk_8;
    u16 unk_C;
    u16 unk_E;
    s32 unk_10;
    s32 *unk_14;
    s32 unk_18;
    u8 *unk_1C;
    u16 unk_20;
    u16 unk_22;
    s32 unk_24;
    u16 unk_28;
    u16 unk_2A;
    s16 unk_2C;
    s16 unk_2E;
    s16 unk_30;
    u16 unk_32;
    u16 unk_34;
    u16 unk_36;
    s16 unk_38;
    u8 unk_3A;
    u8 pad_3B;
    s32 unk_3C;
} TextState;

/* A text message record as func_8001F39C loads it into the printer: the string follows at 0x18. */
typedef struct TextMessage {
    s32 *unk_0;
    s32 unk_4;
    u16 unk_8;
    u16 unk_A;
    s32 unk_C;
    void (*unk_10)(void);
    s32 unk_14;
    u8 unk_18[1];
} TextMessage;

#endif /* GAME_8001781C_H */
