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
    /* 0x00 */ u8 unk_00[0xC];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ Fixed32 unk_18;
    /* 0x1C */ u8 unk_1C[6];
    /* 0x22 */ u16 unk_22;
    /* 0x24 */ u8 unk_24[0x20];
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ u8 unk_48[0x14];
    /* 0x5C */ s32 *unk_5C;
    /* 0x60 */ u8 unk_60[0x20];
    /* 0x80 */ s16 unk_80;
    /* 0x82 */ u8 unk_82[0xE];
    /* 0x90 */ struct Entity *unk_90;        /* the Entity this body belongs to */
} Body;

/* The current Body, at 0x800AA268. A one-member struct rather than a plain pointer: the code reloads it after
 * stores through Entity fields and caches it in a local across stores through it (docs/MATCHING.md "Structs,
 * globals and aliasing"). */
typedef struct {
    Body *p;
} BodyRef;

extern BodyRef D_800AA268;


/* What func_80054728(n) returns (game_800500EC): a record with a pointer at 0x18 to a block holding s16s at 0x0E,
 * 0x1C, 0x1E. */
typedef struct Unk54728Sub18 {
    /* 0x00 */ u8 unk_00[0xE];
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ u8 unk_10[0xC];
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
} Unk54728Sub18;

typedef struct Unk54728 {
    /* 0x00 */ u8 unk_00[4];
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u8 unk_06[8];
    /* 0x0E */ u16 unk_0E;
    /* 0x10 */ u8 unk_10[8];
    /* 0x18 */ Unk54728Sub18 *unk_18;
    /* 0x1C */ u8 unk_1C[0x3C];
    /* 0x58 */ u16 unk_58;
    /* 0x5A */ u8 unk_5A[0x1A];
    /* 0x74 */ u16 unk_74;
    /* 0x76 */ u8 unk_76[2];
    /* 0x78 */ u16 unk_78;
} Unk54728;

/* The object the state functions of game_800500EC and game_80057C94 take (the monsters and the other actors:
 * D_801E0B78 is an array of them, 0x220 bytes each): a state number at 0x5A, flags at 0xC8, its Body at 0x68,
 * timers at 0x100/0x104, an x range at 0x10A/0x10E, animation state at 0x1B0.. */
typedef struct Entity {
    /* 0x000 */ u16 unk_000;
    /* 0x002 */ u8 unk_002[6];
    /* 0x008 */ s32 unk_008;
    /* 0x00C */ u8 unk_00C[4];
    /* 0x010 */ s16 unk_010;
    /* 0x012 */ s16 unk_012;
    /* 0x014 */ u8 unk_014[0x14];
    /* 0x028 */ s16 unk_028;
    /* 0x02A */ u8 unk_02A[0x1C];
    /* 0x046 */ s16 unk_046;
    /* 0x048 */ u8 unk_048[0x12];
    /* 0x05A */ u16 unk_05A;
    /* 0x05C */ u16 unk_05C;
    /* 0x05E */ u8 unk_05E[0xA];
    /* 0x068 */ Body *unk_068;
    /* 0x06C */ u8 unk_06C[0x5C];
    /* 0x0C8 */ u16 unk_0C8;
    /* 0x0CA */ u8 unk_0CA[2];
    /* 0x0CC */ u16 unk_0CC;
    /* 0x0CE */ u8 unk_0CE[0xE];
    /* 0x0DC */ u16 unk_0DC;
    /* 0x0DE */ u8 unk_0DE[0x22];
    /* 0x100 */ s32 unk_100;
    /* 0x104 */ s32 unk_104;
    /* 0x108 */ u8 unk_108[2];
    /* 0x10A */ s16 unk_10A;
    /* 0x10C */ u8 unk_10C[2];
    /* 0x10E */ s16 unk_10E;
    /* 0x110 */ u8 unk_110[0x10];
    /* 0x120 */ Half32 unk_120;
    /* 0x124 */ u8 unk_124[2];
    /* 0x126 */ s16 unk_126;
    /* 0x128 */ u8 unk_128[0x16];
    /* 0x13E */ u16 unk_13E;
    /* 0x140 */ u8 unk_140[0x28];
    /* 0x168 */ u16 unk_168;
    /* 0x16A */ u8 unk_16A[2];
    /* 0x16C */ void *unk_16C;
    /* 0x170 */ u8 unk_170[0x18];
    /* 0x188 */ u16 unk_188;
    /* 0x18A */ u8 unk_18A[4];
    /* 0x18E */ u16 unk_18E;
    /* 0x190 */ u8 unk_190[0x20];
    /* 0x1B0 */ u16 unk_1B0;
    /* 0x1B2 */ u16 unk_1B2;
    /* 0x1B4 */ s16 unk_1B4;
    /* 0x1B6 */ u8 unk_1B6[0x1E];
    /* 0x1D4 */ void *unk_1D4;
    /* 0x1D8 */ u8 unk_1D8[0x48];
} Entity;

/* The game's global state block at 0x800AA248: splat split its fields into D_800AA248, D_800AA250, D_800AA25C,
 * D_800AA268, D_800AA2DC... Most code reaches them as separate globals (D_800AA250, D_800AA25C, D_800AA2DC are plain
 * scalars; D_800AA268 the BodyRef above); cdload's func_80061068 saves and restores the +0x20 member through this
 * struct around an allocation. Two views of the same bytes. */
typedef struct Unk800AA248 {
    /* 0x00 */ u8 unk_00[8];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8 unk_0C[8];
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ u8 unk_18[8];
    /* 0x20 */ Body *unk_20;                  /* = D_800AA268 */
    /* 0x24 */ u8 unk_24[0x18];
    /* 0x3C */ void *unk_3C;                  /* an Unk800AA248Node (cdload.h) */
    /* 0x40 */ u8 unk_40[0x54];
    /* 0x94 */ s32 unk_94;
} Unk800AA248;

extern Unk800AA248 D_800AA248;

#endif /* ENTITY_H */
