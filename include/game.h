#ifndef GAME_H
#define GAME_H

/* The game's shared types: one declaration per record, its fields named where the code shows their meaning and
 * unk_<offset> otherwise. Types local to one file stay in that file or its group's header. */

#include "common.h"

/* A 16.16 fixed-point value (positions, velocities), read whole or by its halves: the fraction at +0, the integer
 * part at +2 (little-endian), signed or unsigned as the code needs. */
typedef union Fixed {
    s32 w;
    struct {
        s16 lo;
        s16 hi;
    } s;
    struct {
        u16 lo;
        u16 hi;
    } u;
} Fixed;

struct Monster;
struct Attacker;
struct UnkStruct2;
struct Npc;
struct Actor;
struct MoverLink;
struct MoverTarget;

/* A sprite frame's metrics (GameObject.frame): its size and origin, then points the code places things at. */
typedef struct SpriteFrame {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ Fixed size;              /* u.lo: the width, u.hi: the height */
    /* 0x08 */ Fixed origin;            /* u.lo: the x offset, u.hi: the y offset */
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u16 unk_10;              /* a second point: x (a throw's origin) */
    /* 0x12 */ u16 unk_12;              /* y */
    /* 0x14 */ u16 unk_14;
    /* 0x16 */ u16 unk_16;
    /* 0x18 */ u16 unk_18;
    /* 0x1A */ u16 unk_1A;
    /* 0x1C */ u16 unk_1C;
    /* 0x1E */ u16 unk_1E;
    /* 0x20 */ u16 unk_20;              /* a third point: x (a spawn origin) */
    /* 0x22 */ u16 unk_22;              /* y */
} SpriteFrame;

/* A sprite object of the level, 0xCC bytes: a monster's body, a vehicle, a projectile, an effect, a building's
 * part... Created from an ObjectDef (func_8001D110, func_8001DCB4), freed by func_8001E4B0; func_8003EB5C and
 * func_8001E698 start an animation. The objects are kept in a list (next, prev; D_801E28C0 is its sentinel head);
 * D_800AA248.cur_obj is the one being updated. */
typedef struct GameObject {
    /* 0x00 */ struct GameObject *next;
    /* 0x04 */ struct GameObject *prev;
    /* 0x08 */ Fixed unk_08;
    /* 0x0C */ Fixed vel_x;
    /* 0x10 */ Fixed vel_y;
    /* 0x14 */ Fixed pos_x;             /* wrapped at the level's width, D_801D8864 */
    /* 0x18 */ Fixed pos_y;
    /* 0x1C */ Fixed unk_1C;
    /* 0x20 */ u16 unk_20;
    /* 0x22 */ u16 flags;               /* 0x10: faces left; 0x20 */
    /* 0x24 */ u8 unk_24[0x04];
    /* 0x28 */ Fixed unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ Fixed size;              /* the frame's size: u.lo the width, u.hi the height */
    /* 0x34 */ SpriteFrame *frame;      /* the current frame's metrics */
    /* 0x38 */ s32 anim_frame;          /* the current animation frame id */
    /* 0x3C */ u16 unk_3C;
    /* 0x3E */ u8 unk_3E[0x02];
    /* 0x40 */ struct GameObject *unk_40;
    /* 0x44 */ s32 script_pc;           /* the animation script's next command (an address) */
    /* 0x48 */ s32 unk_48;              /* the current animation (an address) */
    /* 0x4C */ u8 unk_4C;
    /* 0x4D */ s8 unk_4D;
    /* 0x4E */ u8 unk_4E[0x02];
    /* 0x50 */ struct GameObject *unk_50;
    /* 0x54 */ u8 unk_54[0x08];
    /* 0x5C */ union {                  /* the operands of the script command being run */
                   void *p;
                   u16 *h;
                   s32 *w;
               } arg;
    /* 0x60 */ s32 unk_60;
    /* 0x64 */ s32 unk_64;
    /* 0x68 */ union {                  /* a monster's body: its monster; an effect: two halfwords */
                   struct Monster *monster;
                   s32 w;
                   struct {
                       u16 lo;
                       u16 hi;
                   } u;
               } unk_68;
    /* 0x6C */ u16 unk_6C;              /* 0x80: gone */
    /* 0x6E */ u16 unk_6E;
    /* 0x70 */ u16 unk_70;              /* an id (0x790 + a monster's slot for the status sprites) */
    /* 0x72 */ u8 unk_72[0x02];
    /* 0x74 */ u16 unk_74;
    /* 0x76 */ u8 unk_76[0x02];
    /* 0x78 */ u32 colour;              /* 0x808080: neutral */
    /* 0x7C */ s32 unk_7C;
    /* 0x80 */ u16 unk_80;
    /* 0x82 */ u16 unk_82;
    /* 0x84 */ s32 unk_84;              /* a horizontal acceleration, 16.16 */
    /* 0x88 */ s32 unk_88;
    /* 0x8C */ u16 unk_8C;              /* a lifetime in frames (a thrown object); 0x8C..0xCB is cleared at creation */
    /* 0x8E */ u8 unk_8E[0x02];
    /* 0x90 */ union {                  /* what drives this object */
                   void *p;
                   struct Monster *monster;
                   struct Attacker *attacker;
                   struct UnkStruct2 *item;
                   struct Npc *npc;
                   struct Actor *actor;
                   struct MoverLink *link;
               } owner;
    /* 0x94 */ union {                  /* a second monster (the other side of a grab), or a thrown object's slot */
                   struct Monster *monster;
                   struct MoverTarget *target;
                   void *p;
               } unk_94;
    /* 0x98 */ void *unk_98;            /* the record that grabbed it */
    /* 0x9C */ s32 unk_9C;
    /* 0xA0 */ u8 unk_A0[0x2C];
} GameObject;                           /* 0xCC bytes */

#endif /* GAME_H */
