#ifndef NPC_H
#define NPC_H

#include "common.h"
#include "game.h"
#include "monster_anim.h"

/* Types of npc.c, actor.c, ai.c and game_80043118.c. */

typedef struct AiOrder AiOrder;

/* What GameObject.unk_94 points at for some objects: a record holding another object (npc.c). */
typedef struct MoverTarget {
    /* 0x00 */ u8 unk_0[0x4];
    /* 0x04 */ GameObject *unk_4;
} MoverTarget;

struct AiOrder {
    /* 0x00 */ u8 unk_0[0x4];
    /* 0x04 */ u16 unk_4;
    /* 0x06 */ u16 unk_6;
    /* 0x08 */ s32 unk_8;
    /* 0x0C */ s32 unk_C;
    /* 0x10 */ u8 unk_10[0x4];
    /* 0x14 */ u16 unk_14;
};

typedef struct AiLink {
    /* 0x00 */ GameObject *unk_0;
    /* 0x04 */ u16 unk_4;
    /* 0x06 */ u16 unk_6;
    /* 0x08 */ struct AiLinkInfo *unk_8;
} AiLink;

typedef struct AiLinkInfo {
    /* 0x00 */ u8 unk_0[0x8];
    /* 0x08 */ u16 unk_8;
    /* 0x0A */ u8 unk_A[0xA];
    /* 0x14 */ u16 unk_14;
} AiLinkInfo;

/* A state handler; the first argument is the table it was called from. */
typedef void (*AiHandler)(Ai *ai);

/* A thing on screen with a mover and an animation set, driven by a state (unk_4) and a kind (unk_6): the
 * actors of actor.c. */
typedef struct Actor {
    /* 0x00 */ GameObject *unk_0;
    /* 0x04 */ u16 unk_4;       /* the state; 2 and 6 are tested, 11 is a bound */
    /* 0x06 */ s16 unk_6;       /* the kind: the index into unk_24 */
    /* 0x08 */ s16 unk_8;
    /* 0x0A */ u8 unk_A[0x4];
    /* 0x0E */ u16 unk_E;
    /* 0x10 */ u16 unk_10;      /* the facing step (actor.c: func_8003FD30) */
    /* 0x12 */ u16 unk_12;      /* actor.c: func_8003EF64 skips the actor when set */
    /* 0x14 */ u16 unk_14;
    /* 0x16 */ u16 unk_16;
    /* 0x18 */ u8 unk_18[0x4];
    /* 0x1C */ u16 unk_1C;
    /* 0x1E */ u8 unk_1E[0x2];
    /* 0x20 */ void (**unk_20)(struct Actor *);  /* one handler per kind (actor.c: func_8003EC40) */
    /* 0x24 */ Anim **unk_24;   /* one animation per kind */
    /* 0x28 */ u16 unk_28;
    /* 0x2A */ u16 unk_2A;
    /* 0x2C */ Monster *unk_2C;
    /* 0x30 */ u16 unk_30;      /* a countdown */
    /* 0x32 */ u16 unk_32;
    /* 0x34 */ struct ActorLink *unk_34;
    /* 0x38 */ s16 unk_38;      /* a target x (actor.c: func_800411E8) */
    /* 0x3A */ s16 unk_3A;      /* a position pair (actor.c: func_80041344 passes them signed) */
    /* 0x3C */ s16 unk_3C;
    /* 0x3E */ u16 unk_3E;      /* the index into D_8007E1E4 (actor.c: func_80040B94) */
} Actor;                    /* 0x40: D_801E1E48 holds twelve */

typedef struct ActorLink {
    /* 0x00 */ u8 unk_0[0x4];
    /* 0x04 */ u16 unk_4;       /* an x offset (actor.c: func_8003ED4C) */
    /* 0x06 */ u8 unk_6[0xA];
    /* 0x10 */ u16 unk_10;
} ActorLink;


/* npc.c handles two record sets: the first part of the file (func_80034590 .. func_800360D8) the 0x58-byte
 * Pickup records of D_801FA9BC (include/monster_anim.h), the rest (from func_80036298) the 0x78-byte Npc records of
 * D_801FAC9C. */

/* The records of D_801FAC9C: 0x78 bytes each, six (D_801D8730 counts them), made from the spawn list D_8007DA48 by
 * func_8003684C; each with a mover (unk_0), a kind (unk_6), an action (unk_8) and a state (unk_A), updated by a
 * dispatcher per kind on the action (func_80036300). */
typedef struct Npc {
    /* 0x00 */ GameObject *unk_0;
    /* 0x04 */ u16 unk_4;
    /* 0x06 */ u16 unk_6;
    /* 0x08 */ u16 unk_8;
    /* 0x0A */ u16 unk_A;
    /* 0x0C */ u16 unk_C;
    /* 0x0E */ u8 unk_E[0x6];
    /* 0x14 */ u16 unk_14;
    /* 0x16 */ u8 unk_16[0x4];
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ u16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ u16 unk_24;
    /* 0x26 */ u8 unk_26[0x4];
    /* 0x2A */ u16 unk_2A;
    /* 0x2C */ u16 unk_2C;
    /* 0x2E */ u16 unk_2E;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ u8 unk_38[0x6];
    /* 0x3E */ s16 unk_3E;
    /* 0x40 */ s16 unk_40;
    /* 0x42 */ s16 unk_42;
    /* 0x44 */ s16 unk_44;
    /* 0x46 */ s16 unk_46;
    /* 0x48 */ s16 unk_48;
    /* 0x4A */ s16 unk_4A;
    /* 0x4C */ s16 unk_4C;
    /* 0x4E */ u16 unk_4E;
    /* 0x50 */ u8 unk_50[0x4];
    /* 0x54 */ u16 unk_54;
    /* 0x56 */ u8 unk_56[0x6];
    /* 0x5C */ u16 unk_5C;
    /* 0x5E */ u16 unk_5E;
    /* 0x60 */ Monster *unk_60;
    /* 0x64 */ Monster *unk_64;
    /* 0x68 */ u8 unk_68[0x8];
    /* 0x70 */ GameObject *unk_70;
    /* 0x74 */ GameObject *unk_74;
} Npc;                      /* 0x78 */

extern Npc D_801FAC9C[6];
extern u16 D_801D8730;                   /* how many of D_801FAC9C are live */

#endif /* NPC_H */
