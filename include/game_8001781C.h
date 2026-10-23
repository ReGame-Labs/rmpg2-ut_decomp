#ifndef GAME_8001781C_H
#define GAME_8001781C_H

#include "common.h"
#include "psyq/libc.h"
#include "psyq/libapi.h"
#include "psyq/libgpu.h"
#include "psyq/libetc.h"

/* Provisional types of src/main/game_8001781C.c, the first file of the game's code (main, the game loop, the
 * sprite objects). Field names are offsets until their meaning is known; the types are the ones the code's loads and
 * stores imply. */

/* A 16.16 fixed-point value read whole or by halves (the integer part is the high half), signed or unsigned as
 * the code needs. */
typedef union Fixed {
    s32 full;
    struct {
        s16 lo;
        s16 hi;
    } s;
    struct {
        u16 lo;
        u16 hi;
    } u;
} Fixed;

/* The image a sprite draws (reached through Sprite.unk_34). */
typedef struct SpriteImage {
    s32 unk_0;
    s32 unk_4;
    Fixed unk_8;
    s32 unk_C;
} SpriteImage;


/* A sprite object: linked (unk_68), its position at unk_14/unk_18 (16.16), with flags at unk_22 and unk_6C. */
typedef struct Sprite {
    struct Sprite *unk_0;
    struct Sprite *unk_4;
    s16 unk_8;
    s16 unk_A;
    s32 unk_C;
    s32 unk_10;
    Fixed unk_14;
    Fixed unk_18;
    Fixed unk_1C;
    u16 unk_20;
    u16 unk_22;
    s16 unk_24;
    s16 unk_26;
    Fixed unk_28;
    s32 unk_2C;
    Fixed unk_30;
    SpriteImage *unk_34;
    s32 unk_38;
    u16 unk_3C;
    u8 pad_3E[0x2];
    struct Sprite *unk_40;
    s32 unk_44;
    s32 unk_48;
    s8 unk_4C;
    s8 unk_4D;
    u8 pad_4E[0x2];
    struct Sprite *unk_50;
    u8 pad_54[0xC];
    s32 unk_60;
    u8 pad_64[0x4];
    struct Sprite *unk_68;
    u16 unk_6C;
    u16 unk_6E;
    u16 unk_70;
    u8 pad_72[0x2];
    u16 unk_74;
    u8 pad_76[0x2];
    s32 unk_78;
    s32 unk_7C;
    u16 unk_80;
    u16 unk_82;
    u8 pad_84[0x8];
    u8 unk_8C[0x4];
    void *unk_90;
    u8 pad_94[0x38];
} Sprite;

/* Three slots of freed resources (SpriteSlots.unk_C, unk_24, unk_3C ... released through func_8001E4B0). */
typedef struct SpriteSlots {
    Sprite *unk_0;
    u8 pad_4[0x8];
    Sprite *unk_C;
    u8 pad_10[0x4];
    struct Unk22D58 *unk_14;
    s32 unk_18;
    Sprite *unk_1C;
    u8 pad_20[0x4];
    Sprite *unk_24;
    u8 pad_28[0x4];
    struct Unk22D58 *unk_2C;
    s32 unk_30;
    Sprite *unk_34;
    u8 pad_38[0x4];
    Sprite *unk_3C;
    u8 pad_40[0x4];
    struct Unk22D58 *unk_44;
    s32 unk_48;
    Sprite *unk_4C;
} SpriteSlots;

/* The game's state block at 0x800AA248 (the current sprite at unk_20, 0x800AA268). */
typedef struct GameState {
    s32 unk_0;
    s32 unk_4;
    s32 unk_8;
    s32 unk_C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    struct Unk1D110 *unk_1C;
    Sprite *unk_20;
    s32 unk_24;
    s32 *unk_28;
    s32 unk_2C;
    s32 *unk_30;
    void *unk_34;
    s32 unk_38;
    void *unk_3C;
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
    u8 pad_58[0x8];
    s32 unk_60;
    u8 pad_64[0x10];
    s32 unk_74;
    u8 pad_78[0x2];
    u16 unk_7A;
    u8 pad_7C[0x4];
} GameState;

/* A monster (player or AI): its state machine at unk_5A, its sprite at unk_68. */
typedef struct Monster {
    u16 unk_0;
    u8 pad_2[0xE];
    s32 unk_10;
    u8 pad_14[0x6];
    u16 unk_1A;
    u8 pad_1C[0x20];
    u16 unk_3C;
    u16 unk_3E;
    u8 pad_40[0x6];
    u16 unk_46;
    u8 pad_48[0x10];
    u16 unk_58;
    u16 unk_5A;
    u16 unk_5C;
    u8 pad_5E[0xA];
    Sprite *unk_68;
    u8 pad_6C[0x48];
    s32 unk_B4[2];
    u8 pad_BC[0xC];
    u16 unk_C8;
    u8 pad_CA[0x2];
    u16 unk_CC;
    s16 unk_CE;
    u16 unk_D0;
    u8 pad_D2[0x2];
    s16 unk_D4;
    u8 pad_D6[0x2];
    s32 unk_D8;
    s16 unk_DC;
    s16 unk_DE;
    u8 pad_E0[0x24];
    s32 unk_104;
    u8 pad_108[0x1E];
    u16 unk_126;
    u16 unk_128;
    u8 pad_12A[0x2];
    u16 unk_12C;
    u8 pad_12E[0x10];
    s16 unk_13E;
    u16 unk_140;
    u8 pad_142[0x10];
    s16 unk_152;
    u8 pad_154[0x14];
    u16 unk_168;
    u8 pad_16A[0x20];
    s16 unk_18A;
    u16 unk_18C;
    u16 unk_18E;
    u8 pad_190[0x1A];
    u16 unk_1AA;
    u8 pad_1AC[0x4];
    u16 unk_1B0;
    u8 pad_1B2[0xC];
    u16 unk_1BE;
    u8 pad_1C0[0x1E];
    u16 unk_1DE;
    u16 unk_1E0;
    u8 pad_1E2[0x2];
    s16 *unk_1E4;           /* the demo's input script: 12-byte records (frame, direction, buttons), 0x7FFF ends it */
    u8 pad_1E8[0x10];
    s32 unk_1F8;
    u8 pad_1FC[0x24];
} Monster;

/* The block at 0x801D3D64. */
typedef struct Unk801D3D64 {
    u8 pad_0[0x1A];
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

/* The definition a building record is made from (its unk_20): a kind at unk_0 (4: not a building, func_80025124),
 * its size and the words copied into the record. */
typedef struct Unk25124Def {
    Fixed unk_0;
    u16 unk_4;
    u8 pad_6[0x2];
    s32 unk_8;
    s32 unk_C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
} Unk25124Def;

/* The 13 records of 0x584 bytes at 0x801D3DC8 (the buildings, and the other objects func_80025124 sets up): a
 * 0x98-byte head and 15 items of 0x54 bytes (a sprite each). */
typedef struct Unk1D3DC8Part {
    u8 pad_0[0x14];
    s16 unk_14;
    u8 pad_16[0x2];
} Unk1D3DC8Part;

typedef struct Unk1D3DC8Item {
    Sprite *unk_0;
    s16 unk_4;
    u8 pad_6[0x2];
    struct Unk1D3DC8 *unk_8;
    Unk1D3DC8Part unk_C;
    Unk1D3DC8Part unk_24;
    Unk1D3DC8Part unk_3C;
} Unk1D3DC8Item;

typedef struct Unk1D3DC8 {
    u16 unk_0;              /* the item count */
    u16 unk_2;
    s16 unk_4;              /* x */
    s16 unk_6;
    u16 unk_8;
    s16 unk_A;
    u8 pad_C[0x2];
    s16 unk_E;
    u8 pad_10[0x2];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x2];
    s32 unk_18;
    s16 unk_1C;
    s16 unk_1E;             /* its index + 1 */
    Unk25124Def *unk_20;
    u8 pad_24[0x6];
    s16 unk_2A;
    u8 pad_2C[0x8];
    s16 unk_34;
    s16 unk_36;
    u16 unk_38;
    s16 unk_3A[0xF];
    s16 unk_58;
    u8 pad_5A[0x2];
    s32 unk_5C;
    s32 unk_60;
    s32 unk_64;
    s32 unk_68;
    u8 pad_6C[0x4];
    Unk1D3DC8Item *unk_70;
    s16 unk_74;
    u8 pad_76[0x4];
    u16 unk_7A;
    u8 pad_7C[0x4];
    u16 unk_80;
    u8 pad_82[0x8];
    u16 unk_8A;
    s32 unk_8C;
    u8 pad_90[0x8];
    Unk1D3DC8Item items[15];
} Unk1D3DC8;

/* An entry of the building lists func_80025C08 returns (func_80024C2C): the definition, then the placement. */
typedef struct Unk24C2C {
    Unk25124Def *unk_0;
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

/* The record func_8001D110 hands out (a sprite's draw request?). */
typedef struct Unk1D110 {
    s32 unk_0;
    u8 pad_4[0x2];
    u16 unk_6;
    u8 pad_8[0x4];
    s32 unk_C;
    Fixed unk_10;           /* a position, whole or its integer half */
    Fixed unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    s32 unk_20;
    u8 pad_24[0x4];
    struct Anim *unk_28;
} Unk1D110;

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
    s32 unk_4;
    s32 unk_8;
} Unk1E638;

/* The sprite func_800299C4 drives (the "press start" banner?) at 0x801E2894: the sprite, a frame counter, a state. */
typedef struct Unk1E2894 {
    Sprite *unk_0;
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

/* A monster's behaviour state (the handlers func_80022490 ... func_80023080 run on the current sprite,
 * D_800AA268): its kind at unk_6, the state index at unk_A, "the state is new" at unk_C. */
typedef struct Unk22D58 {
    Sprite *unk_0;
    u8 pad_4[0x2];
    u16 unk_6;
    s16 unk_8;
    u16 unk_A;
    u16 unk_C;
    u8 pad_E[0x2];
    struct Monster *unk_10;
    u8 pad_14[0x8];
    s16 unk_1C;
    u8 pad_1E[0x4];
    s16 unk_22;
    s16 unk_24;
    s16 unk_26;
    u8 pad_28[0x2];
    s16 unk_2A;
    u8 pad_2C[0x4];
    s32 unk_30;
    s32 unk_34;
    s16 unk_38;
    u16 unk_3A;
    u8 pad_3C[0x4];
} Unk22D58;

typedef struct Unk233E0 {
    u8 pad_0[0x10];
    Monster *unk_10;
    u8 pad_14[0x12];
    s16 unk_26;
    s16 unk_28;
    u8 pad_2A[0x12];
    u16 unk_3C;
} Unk233E0;

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
