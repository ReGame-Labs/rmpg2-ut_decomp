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

/* A monster, a player's or the computer's: 0x220 bytes, in the array D_801E0B78 (by its number). */
typedef struct Monster {
    /* 0x000 */ u16 id;                        /* its number, 1..7 (a player's is 1-based) */
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ u16 kind;                      /* the monster kind: 0x15 has its own thrown objects */
    /* 0x008 */ Fixed unk_008;
    /* 0x00C */ u8 unk_00C[0x04];
    /* 0x010 */ Fixed unk_010;                 /* a vertical speed, 16.16 */
    /* 0x014 */ struct Monster *target;       /* the monster this one is attacking */
    /* 0x018 */ u8 unk_018[0x02];
    /* 0x01A */ u16 unk_01A;
    /* 0x01C */ u16 unk_01C;                   /* a countdown set from a random draw */
    /* 0x01E */ u8 unk_01E[0x04];
    /* 0x022 */ u16 unk_022;                   /* the step of a throw sequence, 0..4 */
    /* 0x024 */ u16 unk_024;
    /* 0x026 */ u16 unk_026;
    /* 0x028 */ u16 unk_028;
    /* 0x02A */ u16 unk_02A;                   /* the kind of throw in progress, 0 none */
    /* 0x02C */ u8 unk_02C[0x08];
    /* 0x034 */ s32 unk_034;
    /* 0x038 */ s32 unk_038;
    /* 0x03C */ u16 unk_03C;
    /* 0x03E */ u16 unk_03E;
    /* 0x040 */ u8 unk_040[0x04];
    /* 0x044 */ s16 unk_044;
    /* 0x046 */ u16 unk_046;
    /* 0x048 */ u8 unk_048[0x0E];
    /* 0x056 */ s16 unk_056;
    /* 0x058 */ u16 unk_058;                   /* flags; 1: in play */
    /* 0x05A */ u16 action;                    /* the state the script dispatcher runs */
    /* 0x05C */ u16 unk_05C;
    /* 0x05E */ s16 unk_05E;
    /* 0x060 */ u8 unk_060[0x08];
    /* 0x068 */ GameObject *obj;              /* its body */
    /* 0x06C */ GameObject *unk_06C;
    /* 0x070 */ GameObject *unk_070;
    /* 0x074 */ u8 unk_074[0x0C];
    /* 0x080 */ GameObject *unk_080[6];       /* the score's digit sprites */
    /* 0x098 */ GameObject *unk_098;
    /* 0x09C */ u8 unk_09C[0x18];
    /* 0x0B4 */ s32 unk_0B4[2];
    /* 0x0BC */ u8 unk_0BC[0x0C];
    /* 0x0C8 */ u16 unk_0C8;
    /* 0x0CA */ u8 unk_0CA[0x02];
    /* 0x0CC */ u16 unk_0CC;                   /* an index into the per-file speed tables */
    /* 0x0CE */ s16 unk_0CE;
    /* 0x0D0 */ u16 unk_0D0;
    /* 0x0D2 */ u8 unk_0D2[0x02];
    /* 0x0D4 */ s16 unk_0D4;
    /* 0x0D6 */ u8 unk_0D6[0x02];
    /* 0x0D8 */ s32 unk_0D8;
    /* 0x0DC */ u16 unk_0DC;
    /* 0x0DE */ u16 unk_0DE;
    /* 0x0E0 */ s16 unk_0E0;
    /* 0x0E2 */ s16 unk_0E2;
    /* 0x0E4 */ u16 unk_0E4;
    /* 0x0E6 */ u16 unk_0E6;
    /* 0x0E8 */ u8 unk_0E8[0x02];
    /* 0x0EA */ u16 unk_0EA;
    /* 0x0EC */ u8 unk_0EC[0x02];
    /* 0x0EE */ s16 unk_0EE;
    /* 0x0F0 */ s32 unk_0F0;
    /* 0x0F4 */ s16 unk_0F4;
    /* 0x0F6 */ u16 unk_0F6;
    /* 0x0F8 */ u8 unk_0F8[0x02];
    /* 0x0FA */ u16 unk_0FA;
    /* 0x0FC */ u16 unk_0FC;
    /* 0x0FE */ u8 unk_0FE[0x02];
    /* 0x100 */ s32 unk_100;                   /* a horizontal speed, 16.16 */
    /* 0x104 */ s32 unk_104;                   /* a vertical acceleration, 16.16 */
    /* 0x108 */ s16 unk_108;
    /* 0x10A */ s16 unk_10A;                   /* an x range: 0x10A..0x10E */
    /* 0x10C */ s16 unk_10C;
    /* 0x10E */ s16 unk_10E;
    /* 0x110 */ u8 unk_110[0x08];
    /* 0x118 */ u16 unk_118;                   /* the hit box: left, top, right, bottom */
    /* 0x11A */ u16 unk_11A;
    /* 0x11C */ s16 unk_11C;
    /* 0x11E */ u16 unk_11E;
    /* 0x120 */ Fixed pos;                     /* its position: s.lo x, s.hi y */
    /* 0x124 */ u8 unk_124[0x02];
    /* 0x126 */ u16 unk_126;
    /* 0x128 */ u16 unk_128;
    /* 0x12A */ u16 unk_12A;
    /* 0x12C */ u16 unk_12C;
    /* 0x12E */ u8 unk_12E[0x04];
    /* 0x132 */ u16 unk_132;
    /* 0x134 */ u8 unk_134[0x04];
    /* 0x138 */ u16 unk_138;
    /* 0x13A */ u8 unk_13A[0x02];
    /* 0x13C */ s16 unk_13C;
    /* 0x13E */ s16 unk_13E;
    /* 0x140 */ u16 unk_140;
    /* 0x142 */ u16 unk_142;
    /* 0x144 */ u8 unk_144[0x0C];
    /* 0x150 */ s16 unk_150;
    /* 0x152 */ s16 unk_152;
    /* 0x154 */ u8 unk_154[0x10];
    /* 0x164 */ s16 unk_164;
    /* 0x166 */ u16 unk_166;
    /* 0x168 */ u16 unk_168;
    /* 0x16A */ u8 unk_16A[0x02];
    /* 0x16C */ GameObject *unk_16C;
    /* 0x170 */ u16 unk_170;
    /* 0x172 */ u8 unk_172[0x0A];
    /* 0x17C */ s32 unk_17C;
    /* 0x180 */ struct Monster *unk_180;
    /* 0x184 */ u16 unk_184;
    /* 0x186 */ u8 unk_186[0x02];
    /* 0x188 */ u16 unk_188;
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
    /* 0x1BE */ u16 unk_1BE;
    /* 0x1C0 */ s32 unk_1C0;
    /* 0x1C4 */ Fixed unk_1C4;
    /* 0x1C8 */ s16 unk_1C8;
    /* 0x1CA */ s16 unk_1CA;
    /* 0x1CC */ u16 unk_1CC;
    /* 0x1CE */ u8 unk_1CE[0x02];
    /* 0x1D0 */ GameObject **unk_1D0;
    /* 0x1D4 */ struct MonsterLink *unk_1D4;  /* cleared when the player is dropped */
    /* 0x1D8 */ u16 unk_1D8;
    /* 0x1DA */ u8 unk_1DA[0x04];
    /* 0x1DE */ u16 unk_1DE;
    /* 0x1E0 */ u16 unk_1E0;
    /* 0x1E2 */ u8 unk_1E2[0x02];
    /* 0x1E4 */ s16 * unk_1E4;                 /* the demo's input script: 12-byte records (frame, direction, buttons), 0x7FFF ends it */
    /* 0x1E8 */ u8 unk_1E8[0x10];
    /* 0x1F8 */ s32 unk_1F8;
    /* 0x1FC */ u8 unk_1FC[0x04];
    /* 0x200 */ s32 unk_200;
    /* 0x204 */ u16 unk_204;
    /* 0x206 */ u8 unk_206[0x02];
    /* 0x208 */ s32 unk_208;
    /* 0x20C */ s32 unk_20C;
    /* 0x210 */ s32 unk_210;
    /* 0x214 */ s32 unk_214;
    /* 0x218 */ GameObject *unk_218;
    /* 0x21C */ u8 unk_21C[0x04];
} Monster;                              /* 0x220 bytes */


extern Monster D_801E0B78[];

/* What Monster.unk_1D4 points to: a link to another object's body (a target, a rider?). */
typedef struct MonsterLink {
    /* 0x00 */ GameObject *unk_00;
    /* 0x04 */ u8 unk_04[0x02];
    /* 0x06 */ u16 unk_06;
} MonsterLink;

/* What func_8001D110 hands out to describe an object to create (D_800AA248.new_def); func_8001DCB4 creates it. */
typedef struct ObjectDef {
    /* 0x00 */ s32 id;                         /* the sprite/animation id (the first word of anim) */
    /* 0x04 */ u16 unk_04;                     /* flags: 0x10 faces left */
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ u8 unk_08[0x04];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ Fixed pos_x;                    /* written whole from an object's position, or its integer half alone */
    /* 0x14 */ Fixed pos_y;
    /* 0x18 */ u8 unk_18[0x04];
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 flags;
    /* 0x24 */ u8 unk_24[0x04];
    /* 0x28 */ void *anim;                     /* the animation data */
} ObjectDef;

/* The game's state block at 0x800AA248 (.bss). Some of its members are also reached by their own symbols
 * (D_800AA268 = cur_obj, D_800AA284 = new_def, D_800AA2DC = unk_94): the two forms give different code, so each
 * function keeps the form the original used. */
typedef struct GameState {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;                     /* D_800AA254 */
    /* 0x10 */ s32 unk_10;                     /* D_800AA258 */
    /* 0x14 */ s32 unk_14;                     /* D_800AA25C */
    /* 0x18 */ s32 unk_18;                     /* the argument of the current actor's handler (D_800AA260) */
    /* 0x1C */ ObjectDef *unk_1C;
    /* 0x20 */ GameObject *cur_obj;            /* the object being updated (D_800AA268) */
    /* 0x24 */ s32 unk_24;                     /* D_800AA26C */
    /* 0x28 */ s32 *unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 *unk_30;
    /* 0x34 */ void *unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ ObjectDef *new_def;             /* the object being created (func_8001D110 hands it out; D_800AA284) */
    /* 0x40 */ s32 unk_40;
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ s32 unk_48;
    /* 0x4C */ s32 unk_4C;
    /* 0x50 */ s32 unk_50;
    /* 0x54 */ s32 unk_54;
    /* 0x58 */ u8 unk_58[0x08];
    /* 0x60 */ s32 unk_60;
    /* 0x64 */ u8 unk_64[0x10];
    /* 0x74 */ s32 unk_74;
    /* 0x78 */ s16 unk_78;                     /* set when the current object is gone */
    /* 0x7A */ u16 unk_7A;                     /* 1 when the animation func_8003EB5C starts was already current */
    /* 0x7C */ u8 unk_7C[0x18];
    /* 0x94 */ s32 unk_94;                     /* D_800AA2DC */
} GameState;

extern GameState D_800AA248;

/* D_800AA248.cur_obj by its own name. A one-member struct rather than a plain pointer: GCC 2.8 keeps its stores
 * ordered with struct-field accesses only then (docs/MATCHING.md "Structs, globals and aliasing"). */
typedef struct GameObjectRef {
    GameObject *p;
} GameObjectRef;

extern GameObjectRef D_800AA268;

/* Other members of the state block by their own names. */
extern s32 D_800AA260;                  /* unk_18 */
extern ObjectDef *D_800AA284;           /* new_def */
extern u16 D_800AA2C0;                  /* 1 when a hit landed this frame */
extern s32 D_800AA2DC;                  /* unk_94 */

#endif /* GAME_H */
