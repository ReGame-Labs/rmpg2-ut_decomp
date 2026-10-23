#ifndef ENTITY_H
#define ENTITY_H

/* This group of units' view of the game's shared types (Entity, Body, the current body); include/game.h has another
 * group's view (Mover, Ai, Actor), to be unified. The game's shared types, as the matched code shows them. Every struct here is provisional: only the fields the
 * matched functions touch are known, the rest is padding (unk_XX / pad_XX). Append new structs and fields; do not
 * reorder (several units are matched in parallel). */

#include "common.h"

/* A 16.16 value whose integer half the code also reads on its own (the high s16 at +2). */
typedef union {
    s32 w;
    struct {
        s16 frac;
        s16 i;
    } h;
} Fixed32;

/* A 32-bit field read whole and as two u16 halves. */
typedef union {
    s32 w;
    struct {
        u16 lo;
        u16 hi;
    } h;
} Half32;

/* What D_800AA268 points to, and Entity.unk_68: a moving object's position block ("body", provisional name) (x at 0x16, y at 0x1A and as the
 * 16.16 at 0x18, velocities at 0x0C / 0x10, a flag word at 0x22 whose 0x10 bit is a direction).
 * Fields from cdload and game_800500EC. */
struct Entity;

typedef struct Body {
    /* 0x00 */ struct Body *unk_00;          /* the next in the sprite list (D_801E28C0 is the sentinel head) */
    /* 0x04 */ u8 unk_04[0x8];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ Fixed32 unk_18;
    /* 0x1C */ u8 unk_1C[0x4];
    /* 0x20 */ u16 unk_20;
    /* 0x22 */ u16 unk_22;
    /* 0x24 */ u8 unk_24[0x4];
    /* 0x28 */ u32 unk_28;
    /* 0x2C */ u8 unk_2C[0x4];
    /* 0x30 */ u16 unk_30;
    /* 0x32 */ u16 unk_32;
    /* 0x34 */ u8 unk_34[0x10];
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ u8 unk_48[0x14];
    /* 0x5C */ s32 *unk_5C;
    /* 0x60 */ u8 unk_60[0xC];
    /* 0x6C */ u16 unk_6C;
    /* 0x6E */ u8 unk_6E[0x2];
    /* 0x70 */ u16 unk_70;      /* an id (0x790 + the monster's slot for the status sprites) */
    /* 0x72 */ u8 unk_72[0x6];
    /* 0x78 */ u32 unk_78;      /* a colour, 0x808080 = neutral */
    /* 0x7C */ u8 unk_7C[0x4];
    /* 0x80 */ s16 unk_80;
    /* 0x82 */ u8 unk_82[0xA];
    /* 0x8C */ u16 unk_8C;
    /* 0x8E */ u8 unk_8E[0x2];
    /* 0x90 */ struct Entity *unk_90;        /* the Entity this body belongs to */
} Body;

/* The current Body, at 0x800AA268. A one-member struct rather than a plain pointer: the code reloads it after
 * stores through Entity fields and caches it in a local across stores through it (docs/MATCHING.md "Structs,
 * globals and aliasing"). */
typedef struct {
    Body *p;
} BodyRef;

extern BodyRef D_800AA268;


/* What func_80054728(n) returns (game_800500EC): a 0x584-byte record (D_801D3DC8 holds them) with a pointer at 0x18 to a block holding s16s at 0x0E,
 * 0x1C, 0x1E. */
typedef struct Unk54728Sub18 {
    /* 0x00 */ u8 unk_00[0xE];
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ u8 unk_10[0xC];
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
} Unk54728Sub18;

/* The 0x54-byte items a city record holds from 0x98 (not read yet). */
typedef struct Unk54728Item {
    /* 0x00 */ u8 unk_00[0x6];
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ u8 unk_08[0x4C];
} Unk54728Item;

typedef struct Unk54728 {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u8 unk_02[2];
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u8 unk_06[0x2];
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ u8 unk_0A[0x4];
    /* 0x0E */ u16 unk_0E;
    /* 0x10 */ u16 unk_10;
    /* 0x12 */ u16 unk_12;
    /* 0x14 */ u16 unk_14;
    /* 0x16 */ u8 unk_16[0x2];
    /* 0x18 */ Unk54728Sub18 *unk_18;
    /* 0x1C */ u8 unk_1C[0x2];
    /* 0x1E */ u16 unk_1E;
    /* 0x20 */ u8 unk_20[0x4];
    /* 0x24 */ s16 unk_24;
    /* 0x26 */ u8 unk_26[0x2];
    /* 0x28 */ s16 unk_28;
    /* 0x2A */ u8 unk_2A[0x2E];
    /* 0x58 */ u16 unk_58;
    /* 0x5A */ u8 unk_5A[0x1A];
    /* 0x74 */ u16 unk_74;
    /* 0x76 */ u8 unk_76[2];
    /* 0x78 */ u16 unk_78;
    /* 0x7A */ u8 unk_7A[0x8];
    /* 0x82 */ u16 unk_82;
    /* 0x84 */ u8 unk_84[0x14];
    /* 0x98 */ Unk54728Item unk_98[15];     /* 0x54-byte items */
} Unk54728;                     /* 0x584: D_801D3DC8 is an array of them */

/* The object the state functions of game_800500EC and game_80057C94 take (the monsters and the other actors:
 * D_801E0B78 is an array of them, 0x220 bytes each): a state number at 0x5A, flags at 0xC8, its Body at 0x68,
 * timers at 0x100/0x104, an x range at 0x10A/0x10E, animation state at 0x1B0.. */
typedef struct Entity {
    /* 0x000 */ u16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ u8 unk_006[0x2];
    /* 0x008 */ s32 unk_008;
    /* 0x00C */ u8 unk_00C[4];
    /* 0x010 */ Half32 unk_010;              /* also two s16 halves (unk_012 = unk_010.h.hi) */
    /* 0x014 */ u8 unk_014[0x14];
    /* 0x028 */ s16 unk_028;
    /* 0x02A */ u8 unk_02A[0xA];
    /* 0x034 */ s32 unk_034;
    /* 0x038 */ s32 unk_038;
    /* 0x03C */ u8 unk_03C[0xA];
    /* 0x046 */ s16 unk_046;
    /* 0x048 */ u8 unk_048[0x10];
    /* 0x058 */ u16 unk_058;
    /* 0x05A */ u16 unk_05A;
    /* 0x05C */ u16 unk_05C;
    /* 0x05E */ s16 unk_05E;
    /* 0x060 */ u8 unk_060[0x8];
    /* 0x068 */ Body *unk_068;
    /* 0x06C */ Body *unk_06C;
    /* 0x070 */ Body *unk_070;
    /* 0x074 */ u8 unk_074[0xC];
    /* 0x080 */ Body *unk_080[6];           /* the score's digit sprites */
    /* 0x098 */ u8 unk_098[0x30];
    /* 0x0C8 */ u16 unk_0C8;
    /* 0x0CA */ u8 unk_0CA[2];
    /* 0x0CC */ u16 unk_0CC;
    /* 0x0CE */ u8 unk_0CE[0xE];
    /* 0x0DC */ u16 unk_0DC;
    /* 0x0DE */ u16 unk_0DE;
    /* 0x0E0 */ u8 unk_0E0[0x4];
    /* 0x0E4 */ u16 unk_0E4;
    /* 0x0E6 */ u8 unk_0E6[0xA];
    /* 0x0F0 */ s32 unk_0F0;
    /* 0x0F4 */ s16 unk_0F4;
    /* 0x0F6 */ u8 unk_0F6[0xA];
    /* 0x100 */ s32 unk_100;
    /* 0x104 */ s32 unk_104;
    /* 0x108 */ s16 unk_108;
    /* 0x10A */ s16 unk_10A;
    /* 0x10C */ s16 unk_10C;
    /* 0x10E */ s16 unk_10E;
    /* 0x110 */ u8 unk_110[0x10];
    /* 0x120 */ Half32 unk_120;
    /* 0x124 */ u8 unk_124[2];
    /* 0x126 */ s16 unk_126;
    /* 0x128 */ u8 unk_128[0x2];
    /* 0x12A */ u16 unk_12A;
    /* 0x12C */ u8 unk_12C[0x12];
    /* 0x13E */ u16 unk_13E;
    /* 0x140 */ u8 unk_140[0x24];
    /* 0x164 */ s16 unk_164;
    /* 0x166 */ u8 unk_166[0x2];
    /* 0x168 */ u16 unk_168;
    /* 0x16A */ u8 unk_16A[2];
    /* 0x16C */ void *unk_16C;
    /* 0x170 */ u8 unk_170[0xC];
    /* 0x17C */ s32 unk_17C;
    /* 0x180 */ u8 unk_180[0x4];
    /* 0x184 */ u16 unk_184;
    /* 0x186 */ u8 unk_186[0x2];
    /* 0x188 */ u16 unk_188;
    /* 0x18A */ u16 unk_18A;
    /* 0x18C */ s16 unk_18C;
    /* 0x18E */ u16 unk_18E;
    /* 0x190 */ u8 unk_190[0x20];
    /* 0x1B0 */ u16 unk_1B0;
    /* 0x1B2 */ u16 unk_1B2;
    /* 0x1B4 */ s16 unk_1B4;
    /* 0x1B6 */ u8 unk_1B6[0xA];
    /* 0x1C0 */ s32 unk_1C0;
    /* 0x1C4 */ u8 unk_1C4[0x4];
    /* 0x1C8 */ s16 unk_1C8;
    /* 0x1CA */ u8 unk_1CA[0x2];
    /* 0x1CC */ u16 unk_1CC;
    /* 0x1CE */ u8 unk_1CE[0x6];
    /* 0x1D4 */ struct EntityLink *unk_1D4;
    /* 0x1D8 */ u8 unk_1D8[0x48];
} Entity;

/* The game's global state block at 0x800AA248: splat split its fields into D_800AA248, D_800AA250, D_800AA25C,
 * D_800AA268, D_800AA2DC... Most code reaches them as separate globals (D_800AA250, D_800AA25C, D_800AA2DC are plain
 * scalars; D_800AA268 the BodyRef above); cdload's func_80061068 saves and restores the +0x20 member through this
 * struct around an allocation. Two views of the same bytes. */
typedef struct Unk800AA248 {
    /* 0x00 */ void *unk_00;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;                    /* = D_800AA254 */
    /* 0x10 */ s32 unk_10;                    /* = D_800AA258 */
    /* 0x14 */ s32 unk_14;                    /* = D_800AA25C */
    /* 0x18 */ u8 unk_18[8];
    /* 0x20 */ Body *unk_20;                  /* = D_800AA268 */
    /* 0x24 */ s32 unk_24;                    /* = D_800AA26C */
    /* 0x28 */ u8 unk_28[0x14];
    /* 0x3C */ void *unk_3C;                  /* an Unk800AA248Node (cdload.h) */
    /* 0x40 */ s32 unk_40;
    /* 0x44 */ u8 unk_44[0x50];
    /* 0x94 */ s32 unk_94;
} Unk800AA248;

extern Unk800AA248 D_800AA248;

/* The block at D_801D3D64 (game_800500EC reads two fields; another unit's view exists in include/game_8001781C.h). */
typedef struct Unk1D3D64 {
    /* 0x00 */ u8 unk_00[0x58];
    /* 0x58 */ s32 unk_58;
    /* 0x5C */ u8 unk_5C[2];
    /* 0x5E */ u16 unk_5E;
} Unk1D3D64;

extern Unk1D3D64 D_801D3D64;

/* What Entity.unk_1D4 points to: a link to another object's body (a target, a rider?). */
typedef struct EntityLink {
    /* 0x00 */ Body *unk_00;
    /* 0x04 */ u8 unk_04[2];
    /* 0x06 */ u16 unk_06;
} EntityLink;

/* The five 0x40-byte records at D_801D85C8 (the monsters' behaviour states; another unit's view is `Ai` in
 * include/game.h): a state at 0x08, a "new state" flag at 0x0C, a flag at 0x2E. */
typedef struct Unk1D85C8 {
    /* 0x00 */ u8 unk_00[8];
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ u8 unk_0A[2];
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ u8 unk_0E[0x20];
    /* 0x2E */ u16 unk_2E;
    /* 0x30 */ u8 unk_30[0x10];
} Unk1D85C8;

extern Unk1D85C8 D_801D85C8[5];

/* The flags word at D_8007BD78 (most units read it as a scalar; game_8005D198 also uses the word at +0x54). */
typedef struct Unk7BD78 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x50];
    /* 0x54 */ s32 unk_54;
} Unk7BD78;

#endif /* ENTITY_H */
