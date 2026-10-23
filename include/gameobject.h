#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "common.h"

/* This group of units' view of the game's shared types (GameObject, Monster, Building, the level state); include/game.h,
 * entity.h, game_8001781C.h and game_8002A330.h hold other groups' views of the same objects, to be unified. */

/* A 16.16 fixed-point coordinate whose integer half the code reads on its own (little-endian: the fraction at +0,
 * the integer at +2). */
typedef union {
    s32 v;
    struct {
        s16 frac;
        s16 i;
    } p;
} Fixed16;

struct Monster;
struct Attacker;

/* A sprite object of the level: a monster, a vehicle, a projectile... (created from an ObjectDef through
 * func_8001D110/func_8001DCB4, freed by func_8001E4B0; func_8003EB5C and func_8001E698 start an animation).
 * Fields from game_80043E28 and game_8004E574; the size is not known. */
typedef struct GameObject {
    /* 0x00 */ s32 unk_00;             /* the sprite/animation id it was created from */
    /* 0x04 */ u8 unk_04[0x04];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ Fixed16 vel_x;
    /* 0x10 */ Fixed16 vel_y;
    /* 0x14 */ Fixed16 pos_x;
    /* 0x18 */ Fixed16 pos_y;
    /* 0x1C */ u8 unk_1C[0x04];
    /* 0x20 */ union {
                   s32 word;           /* written whole at creation */
                   struct {
                       u16 lo;
                       u16 flags;      /* bit 0x10: faces left; bit 0x20 */
                   } f;
               } unk_20;
    /* 0x24 */ u8 unk_24[0x0C];
    /* 0x30 */ u16 width;              /* twice the half-width */
    /* 0x32 */ u16 height;             /* twice the half-height */
    /* 0x34 */ struct SpriteFrame *frame; /* the current frame's metrics */
    /* 0x38 */ s32 anim_frame;         /* the current animation frame id */
    /* 0x3C */ u8 unk_3C[0x08];
    /* 0x44 */ s32 script_pc;          /* the animation script's next command (an address) */
    /* 0x48 */ s32 unk_48;
    /* 0x4C */ u8 unk_4C;
    /* 0x4D */ s8 unk_4D;
    /* 0x4E */ u8 unk_4E[0x0E];
    /* 0x5C */ union {                 /* the operands of the script command being run */
                   void *p;
                   u16 *h;
                   s32 *w;
               } arg;
    /* 0x60 */ u8 unk_60[0x04];
    /* 0x64 */ s32 unk_64;
    /* 0x68 */ struct GameObject *unk_68;
    /* 0x6C */ u16 unk_6C;             /* bit 0x80: gone */
    /* 0x6E */ u8 unk_6E[0x02];
    /* 0x70 */ s16 unk_70;
    /* 0x72 */ u8 unk_72[0x02];
    /* 0x74 */ u16 unk_74;
    /* 0x76 */ u8 unk_76[0x0A];
    /* 0x80 */ u16 unk_80;
    /* 0x82 */ u8 unk_82[0x02];
    /* 0x84 */ s32 unk_84;             /* a horizontal acceleration, 16.16 */
    /* 0x88 */ s32 unk_88;
    /* 0x8C */ u8 unk_8C[0x04];
    /* 0x90 */ union {                 /* what drives this object */
                   void *p;
                   struct Monster *monster;
                   struct Attacker *attacker;
               } owner;
    /* 0x94 */ union {                 /* a second monster (the other side of a grab), or a thrown object's slot */
                   struct Monster *monster;
                   void *p;
               } unk_94;
    /* 0x98 */ u8 unk_98[0x04];
    /* 0x9C */ s32 unk_9C;
} GameObject;

/* A sprite frame's metrics (GameObject.frame). Fields from game_8004C064. */
typedef struct SpriteFrame {
    /* 0x00 */ u8 unk_00[0x04];
    /* 0x04 */ u16 unk_04;             /* width */
    /* 0x06 */ u16 unk_06;             /* height */
    /* 0x08 */ u16 unk_08;             /* x offset */
    /* 0x0A */ u16 unk_0A;             /* y offset */
    /* 0x0C */ u8 unk_0C[0x04];
    /* 0x10 */ u16 unk_10;             /* a second point: x (game_8004750C, the throw's origin) */
    /* 0x12 */ u16 unk_12;             /* y */
    /* 0x14 */ u8 unk_14[0x0C];
    /* 0x20 */ u16 unk_20;             /* a third point: x (game_8004750C, a spawn origin) */
    /* 0x22 */ u16 unk_22;             /* y */
} SpriteFrame;

/* What func_8001D110 hands out to describe an object to create; func_8001DCB4 creates it from
 * GameState.new_def. */
typedef struct {
    /* 0x00 */ s32 id;                 /* the sprite/animation id */
    /* 0x04 */ u16 unk_04;             /* flags: 0x10 faces left (game_8004750C) */
    /* 0x06 */ u8 unk_06[0x06];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ Fixed16 pos_x;          /* written whole from an object's position, or its integer half alone */
    /* 0x14 */ Fixed16 pos_y;
    /* 0x18 */ u8 unk_18[0x04];
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 flags;
    /* 0x24 */ u8 unk_24[0x04];
    /* 0x28 */ void *anim;
} ObjectDef;

/* A monster (a player's or the computer's), 0x220 bytes, in the array D_801E0B78 (index = Monster.id). Fields from
 * game_8004E574. */
typedef struct Monster {
    /* 0x000 */ u16 id;                /* 1..7 */
    /* 0x002 */ u8 unk_002[0x02];
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ u8 unk_006[0x02];
    /* 0x008 */ Fixed16 unk_008;
    /* 0x00C */ u8 unk_00C[0x04];
    /* 0x010 */ s32 unk_010;           /* a vertical speed, 16.16 */
    /* 0x014 */ struct Monster *target;  /* the monster this one is attacking (game_8004750C) */
    /* 0x018 */ u8 unk_018[0x04];
    /* 0x01C */ u16 unk_01C;           /* a countdown set from a random draw (game_8004750C) */
    /* 0x01E */ u8 unk_01E[0x04];
    /* 0x022 */ u16 unk_022;           /* the step of a throw sequence, 0..4 (game_8004750C) */
    /* 0x024 */ u8 unk_024[0x04];
    /* 0x028 */ u16 unk_028;
    /* 0x02A */ u16 unk_02A;           /* the kind of throw in progress, 0 none (game_8004750C) */
    /* 0x02C */ u8 unk_02C[0x10];
    /* 0x03C */ u16 unk_03C;
    /* 0x03E */ u16 unk_03E;
    /* 0x040 */ u8 unk_040[0x16];
    /* 0x056 */ s16 unk_056;
    /* 0x058 */ u16 unk_058;
    /* 0x05A */ u16 action;            /* the state the script dispatcher runs */
    /* 0x05C */ u16 unk_05C;
    /* 0x05E */ s16 unk_05E;
    /* 0x060 */ u8 unk_060[0x08];
    /* 0x068 */ GameObject *obj;
    /* 0x06C */ u8 unk_06C[0x5C];
    /* 0x0C8 */ u16 unk_0C8;
    /* 0x0CA */ u8 unk_0CA[0x02];
    /* 0x0CC */ u16 unk_0CC;           /* an index into the per-file speed tables */
    /* 0x0CE */ u8 unk_0CE[0x02];
    /* 0x0D0 */ u16 unk_0D0;
    /* 0x0D2 */ u8 unk_0D2[0x06];
    /* 0x0D8 */ s32 unk_0D8;
    /* 0x0DC */ u16 unk_0DC;
    /* 0x0DE */ u8 unk_0DE[0x02];
    /* 0x0E0 */ s16 unk_0E0;
    /* 0x0E2 */ s16 unk_0E2;
    /* 0x0E4 */ u16 unk_0E4;
    /* 0x0E6 */ u16 unk_0E6;
    /* 0x0E8 */ u8 unk_0E8[0x02];
    /* 0x0EA */ u16 unk_0EA;
    /* 0x0EC */ u8 unk_0EC[0x02];
    /* 0x0EE */ s16 unk_0EE;
    /* 0x0F0 */ u8 unk_0F0[0x06];
    /* 0x0F6 */ u16 unk_0F6;
    /* 0x0F8 */ u8 unk_0F8[0x02];
    /* 0x0FA */ u16 unk_0FA;
    /* 0x0FC */ u16 unk_0FC;
    /* 0x0FE */ u8 unk_0FE[0x02];
    /* 0x100 */ s32 unk_100;           /* a horizontal speed, 16.16 */
    /* 0x104 */ s32 unk_104;           /* a vertical acceleration, 16.16 */
    /* 0x108 */ u8 unk_108[0x10];
    /* 0x118 */ u16 unk_118;           /* the hit box: left, top, right, bottom */
    /* 0x11A */ u16 unk_11A;
    /* 0x11C */ s16 unk_11C;
    /* 0x11E */ u16 unk_11E;
    /* 0x120 */ s16 x;
    /* 0x122 */ s16 y;
    /* 0x124 */ u8 unk_124[0x02];
    /* 0x126 */ u16 unk_126;
    /* 0x128 */ u8 unk_128[0x02];
    /* 0x12A */ u16 unk_12A;
    /* 0x12C */ u8 unk_12C[0x06];
    /* 0x132 */ u16 unk_132;
    /* 0x134 */ u8 unk_134[0x04];
    /* 0x138 */ u16 unk_138;
    /* 0x13A */ u8 unk_13A[0x04];
    /* 0x13E */ s16 unk_13E;
    /* 0x140 */ u16 unk_140;
    /* 0x142 */ u16 unk_142;
    /* 0x144 */ u8 unk_144[0x0C];
    /* 0x150 */ s16 unk_150;
    /* 0x152 */ u16 unk_152;
    /* 0x154 */ u8 unk_154[0x12];
    /* 0x166 */ u16 unk_166;
    /* 0x168 */ u16 unk_168;
    /* 0x16A */ u8 unk_16A[0x02];
    /* 0x16C */ GameObject *unk_16C;
    /* 0x170 */ u16 unk_170;
    /* 0x172 */ u8 unk_172[0x0E];
    /* 0x180 */ struct Monster *unk_180;
    /* 0x184 */ s16 unk_184;
    /* 0x186 */ u8 unk_186[0x04];
    /* 0x18A */ u16 unk_18A;
    /* 0x18C */ u16 unk_18C;
    /* 0x18E */ u16 unk_18E;
    /* 0x190 */ u8 unk_190[0x1A];
    /* 0x1AA */ u16 unk_1AA;
    /* 0x1AC */ u16 unk_1AC;
    /* 0x1AE */ u16 unk_1AE;
    /* 0x1B0 */ u16 unk_1B0;
    /* 0x1B2 */ u16 unk_1B2;
    /* 0x1B4 */ u16 unk_1B4;
    /* 0x1B6 */ u8 unk_1B6[0x06];
    /* 0x1BC */ u16 unk_1BC;
    /* 0x1BE */ u8 unk_1BE[0x06];
    /* 0x1C4 */ Fixed16 unk_1C4;
    /* 0x1C8 */ s16 unk_1C8;
    /* 0x1CA */ s16 unk_1CA;
    /* 0x1CC */ s16 unk_1CC;
    /* 0x1CE */ u8 unk_1CE[0x02];
    /* 0x1D0 */ GameObject **unk_1D0;
    /* 0x1D4 */ u8 unk_1D4[0x04];
    /* 0x1D8 */ u16 unk_1D8;
    /* 0x1DA */ u8 unk_1DA[0x46];
} Monster;                             /* 0x220 bytes */

extern Monster D_801E0B78[];

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
