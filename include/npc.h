#ifndef NPC_H
#define NPC_H

#include "common.h"
#include "game.h"
#include "pickup.h"     /* the Pickup records of the first part of npc.c */

/* Types of npc.c, actor.c, ai.c and game_80043118.c. */

/* What GameObject.unk_94 points at for some objects: a record holding another object (npc.c). */
typedef struct MoverTarget {
    /* 0x00 */ u8 unk_0[0x4];
    /* 0x04 */ GameObject *unk_4;
} MoverTarget;


/* A state handler; the first argument is the table it was called from. */
typedef void (*AiHandler)(Ai *ai);

/* A thing on screen with a mover and an animation set, driven by a state (unk_4) and a kind (unk_6): the
 * actors of actor.c. */
typedef struct Actor {
    /* 0x00 */ GameObject *obj;
    /* 0x04 */ u16 unk_4;       /* the state; 2 and 6 are tested, 11 is a bound */
    /* 0x06 */ s16 kind;        /* the index into unk_24 */
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
 * Pickup records of D_801FA9BC (include/pickup.h), the rest (from func_80036298) the 0x78-byte Npc records of
 * D_801FAC9C. */

/* The records of D_801FAC9C: 0x78 bytes each, six (D_801D8730 counts them), made from the spawn list D_8007DA48 by
 * func_8003684C; each with an object, a kind, an action and a state, updated by a dispatcher per kind on the action
 * (func_80036300). The head is the behaviour records' (game.h, Ai); kinds 0x11 and 0x12 run main.c's func_80020DDC,
 * which reaches 0x50. */
typedef struct Npc {
    /* 0x00 */ GameObject *obj;            /* the object it drives */
    /* 0x04 */ u16 unk_04;                 /* the player slot last targeted (func_800377B4) */
    /* 0x06 */ u16 kind;                   /* picks the dispatcher (func_80036300) */
    /* 0x08 */ u16 action;                 /* the current action */
    /* 0x0A */ u16 state;                  /* the index into the action's handler table */
    /* 0x0C */ u16 unk_0C;                 /* 1 while the state is new */
    /* 0x0E */ u8 unk_0E[0x2];
    /* 0x10 */ Monster *unk_10;            /* the monster it goes for (func_800377B4 picks it) */
    /* 0x14 */ u16 unk_14;
    /* 0x16 */ u8 unk_16[0x4];
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ u16 unk_20;
    /* 0x22 */ u16 unk_22;
    /* 0x24 */ u16 aim;                    /* the slope band, 0..2 (D_8007DB04 holds the animations [old][new]); 3 in
                                            * func_80020EDC's tables */
    /* 0x26 */ s16 unk_26;
    /* 0x28 */ s16 target_y;               /* the y it flies to (func_80023B20) */
    /* 0x2A */ u16 unk_2A;
    /* 0x2C */ u16 unk_2C;
    /* 0x2E */ u16 unk_2E;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ u16 unk_38;
    /* 0x3A */ u16 start;                  /* the start position, an index into D_8007B358/D_8007B348 */
    /* 0x3C */ u16 unk_3C;
    /* 0x3E */ s16 unk_3E;
    /* 0x40 */ s16 unk_40;
    /* 0x42 */ s16 unk_42;
    /* 0x44 */ s16 unk_44;
    /* 0x46 */ s16 unk_46;
    /* 0x48 */ s16 unk_48;
    /* 0x4A */ s16 unk_4A;
    /* 0x4C */ s16 unk_4C;
    /* 0x4E */ u16 unk_4E;
    /* 0x50 */ GameObject *unk_50;         /* a second object it makes (kinds 0x11, 0x12: func_80020EDC) */
    /* 0x54 */ u16 unk_54;
    /* 0x56 */ u16 unk_56;                 /* another player slot (func_800377B4) */
    /* 0x58 */ u16 unk_58;                 /* toggled by func_800377B4: which way it picks */
    /* 0x5A */ u8 unk_5A[0x2];
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

/* The speeds of the throws npc.c makes (func_80039358), by kind 1..3: the object's velocity and the Throw's vertical
 * acceleration (Throw.unk_0C). */
typedef struct NpcThrowSpeed {
    s32 vel_x;
    s32 vel_y;
    s32 accel_y;
} NpcThrowSpeed;

extern NpcThrowSpeed D_8007DAC8[];
extern Anim D_80095F80;
extern Anim D_80095FA4;
extern Anim D_80095FC8;

/* The throw kinds npc.c makes (func_8004A9B0 calls the first two) and runs (func_8004AD18's handlers). */
u16 func_80039358(Monster *m, u16 a, u16 kind, Throw *t);
u16 func_8003A5A0(u16 a, u16 kind, Throw *t, s32 alt);
void func_8003956C(Throw *t);
void func_8003A744(Throw *t);

#endif /* NPC_H */
