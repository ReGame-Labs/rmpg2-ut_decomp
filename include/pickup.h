#ifndef PICKUP_H
#define PICKUP_H

#include "common.h"
#include "game.h"

/* The records of src/main/pickup.c: the pickups, the spawn lists' entries and the records of D_801D3824. Only
 * game.h is included: npc.h and monster_anim.h include this header, and pickup.c includes building.h itself. */

/* An entry of the spawn lists func_80025C08 picks (D_8007DDA4 for pickup_spawn_all, D_800830AC for func_8003C3B0,
 * D_8007DA48 for func_8003684C): an animation and five halfwords the record takes over. The first entry of D_8007DDA4's list holds the count in
 * unk_04; D_800830AC's ends at an entry whose unk_04 is 0. */
typedef struct SpawnItem {
    /* 0x00 */ Anim *anim;
    /* 0x04 */ u16 unk_04;     /* the kind */
    /* 0x06 */ u16 unk_06;     /* x */
    /* 0x08 */ u16 unk_08;     /* y */
    /* 0x0A */ u16 unk_0A;     /* flags */
    /* 0x0C */ u16 unk_0C;
    /* 0x0E */ s16 unk_0E;     /* pickup_spawn_all: -1 for a random countdown */
} SpawnItem;

/* The eight 0x58-byte records of D_801FA9BC (D_801E29B0 in use), made from the spawn list D_8007DDA4 by
 * pickup_spawn_all: each with an object, a kind (unk_06, 1..0x1C) and a state (unk_08: 1 new, 2 live, 3 taken).
 * pickup_update runs the kind's handler (building_update_pickup for 1..19 in building.c, the others in the first part of
 * npc.c); the pickup checks (pickup_collect, func_8005BF54, func_8005C71C, func_8005CC54) hand one to the
 * monster that touches it (unk_54). Their head is the behaviour records' (game.h, Ai), and matches the 0x78-byte Npc up to 0x38. */
typedef struct Pickup {
    /* 0x00 */ GameObject *obj;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ u16 kind;       /* pickup_update picks its handler */
    /* 0x08 */ u16 unk_08;     /* the state */
    /* 0x0A */ u16 unk_0A;
    /* 0x0C */ u16 unk_0C;     /* 1 while the state is new */
    /* 0x0E */ u8 pad_0E[0x6];
    /* 0x14 */ Monster *unk_14;
    /* 0x18 */ u8 pad_18[0x2];
    /* 0x1A */ u16 unk_1A;
    /* 0x1C */ u16 unk_1C;     /* a countdown (random 200..299 or from the spawn list) */
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ u8 pad_24[0xC];
    /* 0x30 */ s32 unk_30;     /* y acceleration, 16.16 (func_8003BE34) */
    /* 0x34 */ s32 unk_34;     /* x acceleration, 16.16 */
    /* 0x38 */ u8 pad_38[0x6];
    /* 0x3E */ u16 unk_3E;
    /* 0x40 */ GameObject *unk_40;  /* a second sprite (kinds 0xD..0x11) */
    /* 0x44 */ u16 unk_44;     /* the taker's flags */
    /* 0x46 */ u8 pad_46[0x8];
    /* 0x4E */ u16 unk_4E;     /* the taker's position */
    /* 0x50 */ u16 unk_50;
    /* 0x52 */ u8 pad_52[0x2];
    /* 0x54 */ Monster *unk_54;  /* the monster that took it */
} Pickup;

extern Pickup D_801FA9BC[];
extern u16 D_801E29B0;

/* The 0x30-byte records of D_801D3824 (D_801D8738 of them), made from the spawn list D_800830AC by func_8003C3B0;
 * func_8003C1C0 runs the handler of their kind (func_8003C2D4), in actor.c. */
typedef struct UnkStructB2 {  /* provisional */
    /* 0x00 */ GameObject *obj;
    /* 0x04 */ u16 unk_04;     /* 1: in use */
    /* 0x06 */ u16 kind;       /* func_8003D30C: 0x34 refills a health, 0x35 a meter */
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ u16 unk_0A;
    /* 0x0C */ u16 unk_0C;
    /* 0x0E */ u16 unk_0E;     /* tested, then cleared, by its handlers (func_8003D228, func_8003D30C) */
    /* 0x10 */ BuildingPart *unk_10;
    /* 0x14 */ Monster *unk_14;  /* a monster: kind 0x34 refills its health, 0x35 its meter (func_8003D30C) */
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ u16 unk_1A;
    /* 0x1C */ u16 unk_1C;
    /* 0x1E */ u8 pad_1E[0x12];
} UnkStructB2;

extern UnkStructB2 D_801D3824[];

#endif /* PICKUP_H */
