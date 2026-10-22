#ifndef GAME_8001781C_H
#define GAME_8001781C_H

#include "common.h"
#include "psyq/libc.h"

/* Provisional types of src/main/game_8001781C.c, the first file of the game's code (main, the game loop, the
 * sprite objects). Field names are offsets until their meaning is known; the types are the ones the code's loads and
 * stores imply. */

/* The image a sprite draws (reached through Sprite.unk_34). */
typedef struct SpriteImage {
    u8 pad_0[0x8];
    u16 unk_8;
    u16 unk_A;
} SpriteImage;

/* A sprite object: linked (unk_68), with flags at unk_1A, unk_22 and unk_6C. */
typedef struct Sprite {
    struct Sprite *unk_0;
    u8 pad_4[0x4];
    s16 unk_8;
    s16 unk_A;
    s32 unk_C;
    s32 unk_10;
    s16 unk_14;
    u16 unk_16;
    s16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
    u16 unk_22;
    s16 unk_24;
    s16 unk_26;
    s16 unk_28;
    s16 unk_2A;
    s32 unk_2C;
    s32 unk_30;
    SpriteImage *unk_34;
    s32 unk_38;
    u16 unk_3C;
    u8 pad_3E[0x6];
    s32 unk_44;
    s32 unk_48;
    s8 unk_4C;
    s8 unk_4D;
    u8 pad_4E[0x2];
    s32 unk_50;
    u8 pad_54[0xC];
    s32 unk_60;
    u8 pad_64[0x4];
    struct Sprite *unk_68;
    u16 unk_6C;
    u16 unk_6E;
    u8 pad_70[0x1C];
    u8 unk_8C[0x40];
} Sprite;

/* Three slots of freed resources (SpriteSlots.unk_C, unk_24, unk_3C ... released through func_8001E4B0). */
typedef struct SpriteSlots {
    s32 unk_0;
    u8 pad_4[0x8];
    s32 unk_C;
    u8 pad_10[0x8];
    s32 unk_18;
    s32 unk_1C;
    u8 pad_20[0x4];
    s32 unk_24;
    u8 pad_28[0x8];
    s32 unk_30;
    s32 unk_34;
    u8 pad_38[0x4];
    s32 unk_3C;
    u8 pad_40[0x8];
    s32 unk_48;
    s32 unk_4C;
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
    s32 unk_1C;
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
    s16 unk_7A;
    u8 pad_7C[0x4];
} GameState;

/* A monster (player or AI): its state machine at unk_5A, its sprite at unk_68. */
typedef struct Monster {
    u16 unk_0;
    u8 pad_2[0x58];
    u16 unk_5A;
    u16 unk_5C;
    u8 pad_5E[0xA];
    Sprite *unk_68;
    u8 pad_6C[0x60];
    u16 unk_CC;
    s16 unk_CE;
    u8 pad_D0[0x4];
    s16 unk_D4;
    u8 pad_D6[0x8];
    s16 unk_DE;
    u8 pad_E0[0x24];
    s32 unk_104;
    u8 pad_108[0x1E];
    s16 unk_126;
    u8 pad_128[0x40];
    u16 unk_168;
    u8 pad_16A[0x20];
    s16 unk_18A;
} Monster;

typedef struct Unk1E638 {
    u8 pad_0[0x4];
    s32 unk_4;
    s32 unk_8;
} Unk1E638;

typedef struct Unk22D58 {
    u8 pad_0[0xA];
    s16 unk_A;
    u16 unk_C;
    u8 pad_E[0x1C];
    s16 unk_2A;
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

#endif /* GAME_8001781C_H */
