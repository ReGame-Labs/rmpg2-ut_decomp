#ifndef GAME_H
#define GAME_H

/* The game's shared types: one declaration per record, its fields named where the code shows their meaning and
 * unk_<offset> otherwise. Types local to one file stay in that file or its group's header. */

#include "common.h"
#include "psyq/libgpu.h"

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

/* An animation (the tables in .data from 0x8008AE40 on): a script whose first word is the sprite id an object made
 * from it starts with (ObjectDef.id). */
typedef struct Anim {
    /* 0x00 */ s32 id;
} Anim;

struct Monster;
struct Attacker;
struct BuildingItem;
struct Npc;
struct Actor;
struct Ai;
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
    /* 0x2C */ Fixed unk_2C;            /* the frame's size too (func_8001E59C sets both): u.lo the width, u.hi the height */
    /* 0x30 */ Fixed size;              /* the frame's size: u.lo the width, u.hi the height */
    /* 0x34 */ SpriteFrame *frame;      /* the current frame's metrics */
    /* 0x38 */ s32 anim_frame;          /* the current animation frame id */
    /* 0x3C */ u16 unk_3C;
    /* 0x3E */ u8 unk_3E[0x02];
    /* 0x40 */ union {
                   struct GameObject *obj;  /* a link (main.c's list from D_801D8584) */
                   s32 w;                   /* a value; a box's width (func_8001EB9C: the status bars, OVERATTR's
                                             * volume bars) */
               } unk_40;
    /* 0x44 */ union {                  /* by kind */
                   s32 pc;                  /* the animation script's next command (an address) */
                   s32 height;              /* a box's height (func_8001EB9C; the results bars, func_800991EC) */
                   s32 v;                   /* a value (OVERATTR's logo: a y, with unk_40.w its x) */
               } script;
    /* 0x48 */ s32 anim;                /* the current animation (an address: the script restarts there) */
    /* 0x4C */ u8 unk_4C;
    /* 0x4D */ s8 unk_4D;
    /* 0x4E */ u8 unk_4E[0x02];
    /* 0x50 */ union {                  /* by kind */
                   struct GameObject *obj;  /* a link */
                   s32 cam_start;           /* OVERATTR's camera: its start point, y << 16 | x (func_8009AE40) */
               } unk_50;
    /* 0x54 */ union {
                   s32 w;
                   s32 cam_end;             /* OVERATTR's camera: its end point, y << 16 | x */
               } unk_54;
    /* 0x58 */ u8 unk_58[0x04];
    /* 0x5C */ union {                  /* the operands of the script command being run */
                   void *p;
                   u16 *h;
                   s32 *w;
                   s32 cam_point;           /* OVERATTR's camera: its current point, y << 16 | x */
               } arg;
    /* 0x60 */ s32 unk_60;
    /* 0x64 */ union {                  /* by kind */
                   s32 w;
                   s32 count;               /* a results bar: the tally shown so far (func_800991EC) */
               } unk_64;
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
    /* 0x70 */ u16 kind;                /* the id func_8001E450 and func_8001EC74 select objects by (0x790 + a
                                         * monster's slot for the status sprites) */
    /* 0x72 */ u8 unk_72[0x02];
    /* 0x74 */ u16 unk_74;
    /* 0x76 */ u8 unk_76[0x02];
    /* 0x78 */ u32 colour;              /* 0x808080: neutral */
    /* 0x7C */ s32 unk_7C;
    /* 0x80 */ u16 priority;            /* the draw order: the list is kept sorted by it, highest first (func_8001E010) */
    /* 0x82 */ u16 unk_82;
    /* 0x84 */ s32 unk_84;              /* a horizontal acceleration, 16.16 */
    /* 0x88 */ s32 unk_88;
    /* 0x8C */ u16 unk_8C;              /* a lifetime in frames (a thrown object); 0x8C..0xCB is cleared at creation */
    /* 0x8E */ u8 unk_8E[0x02];
    /* 0x90 */ union {                  /* what drives this object */
                   void *p;
                   struct Monster *monster;
                   struct Attacker *attacker;
                   struct BuildingItem *item;
                   struct Building *building;
                   struct Npc *npc;
                   struct Actor *actor;
                   struct Ai *ai;
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
    /* 0x008 */ Fixed health;                  /* 0..0x44 (16.16): zero, it is out; a continue refills it */
    /* 0x00C */ Fixed health_shown;            /* eased towards health by 1/16 a frame; health_bar shows it */
    /* 0x010 */ Fixed meter;                   /* a second meter, 0..0x44 (16.16): a projectile's hit raises it
                                                * (func_8004C0E0); full, monster 5 gets its extra sprites */
    /* 0x014 */ Fixed meter_shown;             /* eased towards meter by 1/16 a frame (func_8005DBC4); meter_bar
                                                * shows it */
    /* 0x018 */ u8 unk_018[0x02];
    /* 0x01A */ u16 unk_01A;
    /* 0x01C */ u16 unk_01C;                   /* a countdown set from a random draw */
    /* 0x01E */ u8 unk_01E[0x02];
    /* 0x020 */ u16 unk_020;                   /* a tally for the results (OVERATTR's first bar) */
    /* 0x022 */ u16 unk_022;                   /* the step of a throw sequence, 0..4 */
    /* 0x024 */ u16 unk_024;                   /* a tally for the results (the second bar): eating a person or a
                                                * pickup adds one */
    /* 0x026 */ u16 unk_026;                   /* a tally for the results (the third bar): func_8003111C adds to it */
    /* 0x028 */ u16 unk_028;
    /* 0x02A */ u16 unk_02A;                   /* the kind of throw in progress, 0 none */
    /* 0x02C */ u8 unk_02C[0x08];
    /* 0x034 */ s32 unk_034;
    /* 0x038 */ s32 unk_038;
    /* 0x03C */ u16 unk_03C;
    /* 0x03E */ u16 unk_03E;
    /* 0x040 */ s32 unk_040;
    /* 0x044 */ s16 unk_044;
    /* 0x046 */ u16 unk_046;
    /* 0x048 */ u8 unk_048[0x0E];
    /* 0x056 */ s16 unk_056;
    /* 0x058 */ u16 unk_058;                   /* flags; 1: in play */
    /* 0x05A */ u16 action;                    /* the state the script dispatcher runs */
    /* 0x05C */ u16 unk_05C;
    /* 0x05E */ s16 unk_05E;
    /* 0x060 */ u8 unk_060[0x04];
    /* 0x064 */ u16 unk_064;
    /* 0x066 */ u8 unk_066[0x02];
    /* 0x068 */ GameObject *obj;               /* its body */
    /* 0x06C */ GameObject *meter_bar;         /* status bars: boxes whose width (unk_40.w) is the value shown, */
    /* 0x070 */ GameObject *health_bar;        /* at most 0x44 (func_8005D20C, func_8005DBC4) */
    /* 0x074 */ u8 unk_074[0x0C];
    /* 0x080 */ GameObject *unk_080[6];        /* the score's digit sprites */
    /* 0x098 */ GameObject *unk_098;
    /* 0x09C */ u8 unk_09C[0x08];
    /* 0x0A4 */ GameObject *bars[3];           /* the results bars, one per tally (OVERATTR, func_8009951C) */
    /* 0x0B0 */ u8 unk_0B0[0x04];
    /* 0x0B4 */ GameObject *extra[5];          /* its own sprites (5's, 7's: kind 0x73A; 2-4 func_8002A1AC), or NULL */
    /* 0x0C8 */ u16 buttons;                   /* the pad's buttons held, pad bits >> 4 (func_800273F4) */
    /* 0x0CA */ u8 unk_0CA[0x02];
    /* 0x0CC */ u16 dir;                       /* the d-pad direction, 0 none (D_8007C124[pad bits & 0xF]); an index
                                                * into the per-file speed tables */
    /* 0x0CE */ s16 unk_0CE;
    /* 0x0D0 */ u16 unk_0D0;
    /* 0x0D2 */ u8 unk_0D2[0x02];
    /* 0x0D4 */ s16 last_dir;                  /* the last direction other than 0 */
    /* 0x0D6 */ u8 unk_0D6[0x02];
    /* 0x0D8 */ s32 dir_frames;                /* the frames dir has stayed the same */
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
    /* 0x0F0 */ s32 unk_0F0;                   /* a change to its health, applied once (func_80029510) */
    /* 0x0F4 */ s16 front_x;                   /* its front: pos_x plus or minus half its width, by its facing */
    /* 0x0F6 */ u16 unk_0F6;
    /* 0x0F8 */ u8 unk_0F8[0x02];
    /* 0x0FA */ u16 unk_0FA;
    /* 0x0FC */ u16 unk_0FC;
    /* 0x0FE */ u8 unk_0FE[0x02];
    /* 0x100 */ s32 unk_100;                   /* a horizontal speed, 16.16 */
    /* 0x104 */ s32 unk_104;                   /* a vertical acceleration, 16.16 */
    /* 0x108 */ s16 box_x0;                    /* two boxes, (x0, y0)-(x1, y1): func_80053854 says which one a */
    /* 0x10A */ s16 box_y0;                    /* point is in */
    /* 0x10C */ s16 box_x1;
    /* 0x10E */ s16 box_y1;
    /* 0x110 */ s16 box2_x0;
    /* 0x112 */ u16 box2_y0;
    /* 0x114 */ s16 box2_x1;
    /* 0x116 */ u16 box2_y1;
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
    /* 0x13C */ u16 unk_13C;
    /* 0x13E */ u16 unk_13E;
    /* 0x140 */ u16 unk_140;
    /* 0x142 */ u16 unk_142;                   /* nonzero: the vibration presets 0-3 run twice as strong and long */
    /* 0x144 */ s16 unk_144;
    /* 0x146 */ s16 unk_146;
    /* 0x148 */ u8 unk_148[0x08];
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
    /* 0x180 */ struct Monster *attacker;      /* the monster that hit it last (func_8005421C) */
    /* 0x184 */ u16 unk_184;
    /* 0x186 */ u16 unk_186;
    /* 0x188 */ u16 unk_188;
    /* 0x18A */ u16 unk_18A;
    /* 0x18C */ u16 unk_18C;
    /* 0x18E */ u16 unk_18E;
    /* 0x190 */ u8 unk_190[0x1A];
    /* 0x1AA */ u16 unk_1AA;
    /* 0x1AC */ u16 unk_1AC;
    /* 0x1AE */ u16 unk_1AE;
    /* 0x1B0 */ u16 climb_side;                /* 0: not on a building; 1, 2: the side it climbs; 3 (func_80054D74) */
    /* 0x1B2 */ u16 climb_building;            /* the building, 1-based (func_80054728) */
    /* 0x1B4 */ u16 climb_floor;               /* the building's item it is at */
    /* 0x1B6 */ u8 unk_1B6[0x06];
    /* 0x1BC */ u16 unk_1BC;
    /* 0x1BE */ u16 skip_building;             /* a building (Building.unk_01E) the scans leave out, 0 none */
    /* 0x1C0 */ s32 unk_1C0;
    /* 0x1C4 */ Fixed unk_1C4;
    /* 0x1C8 */ s16 unk_1C8;
    /* 0x1CA */ s16 unk_1CA;
    /* 0x1CC */ u16 unk_1CC;
    /* 0x1CE */ u8 unk_1CE[0x02];
    /* 0x1D0 */ GameObject **unk_1D0;
    /* 0x1D4 */ struct MonsterLink *unk_1D4;   /* cleared when the player is dropped */
    /* 0x1D8 */ u16 unk_1D8;
    /* 0x1DA */ u8 unk_1DA[0x04];
    /* 0x1DE */ u16 unk_1DE;
    /* 0x1E0 */ u16 unk_1E0;
    /* 0x1E2 */ u8 unk_1E2[0x02];
    /* 0x1E4 */ s16 *unk_1E4;                  /* the demo's input script: 12-byte records (frame, direction, buttons), 0x7FFF ends it */
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
    /* 0x06 */ u16 unk_06;                     /* flags: 0x20 */
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
    /* 0x04 */ s32 unk_04;                     /* scratch: func_80056840's scan index, func_8004003C's "a player is
                                                * ahead" */
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;                     /* D_800AA254; scratch: monster.c's probe x, func_8004003C's "a
                                                * player is in play", func_800297B4's count */
    /* 0x10 */ s32 unk_10;                     /* D_800AA258; scratch: monster.c's probe y, func_800297B4's count */
    /* 0x14 */ s32 action;                     /* the monster's action, clamped, before the dispatch (func_800500EC;
                                                * D_800AA25C) */
    /* 0x18 */ s32 unk_18;                     /* the argument of the current actor's handler (D_800AA260) */
    /* 0x1C */ union {
                   ObjectDef *def;
                   s32 n;                   /* a count (func_8002958C) */
               } unk_1C;
    /* 0x20 */ GameObject *cur_obj;            /* the object being updated (D_800AA268) */
    /* 0x24 */ s32 unk_24;                     /* D_800AA26C */
    /* 0x28 */ s32 unk_28;                     /* a counter (func_8003C3B0: the items left in the building) */
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 *unk_30;
    /* 0x34 */ void *unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ ObjectDef *new_def;             /* the object being created (func_8001D110 hands it out; D_800AA284) */
    /* 0x40 */ s32 unk_40;                     /* scratch: func_80056840's buildings left to scan */
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ s32 unk_48;
    /* 0x4C */ s32 unk_4C;
    /* 0x50 */ s32 unk_50;
    /* 0x54 */ s32 unk_54;
    /* 0x58 */ u8 unk_58[0x08];
    /* 0x60 */ s32 unk_60;
    /* 0x64 */ u8 unk_64[0x10];
    /* 0x74 */ s32 unk_74;
    /* 0x78 */ s16 result;                     /* the last test's result, also returned (the current object gone,
                                                * a hit landed, a pad pressed...; D_800AA2C0) */
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

/* D_800AA248.new_def by its own name, a one-member struct for the same reason. */
typedef struct ObjectDefRef {
    ObjectDef *p;
} ObjectDefRef;

extern ObjectDefRef D_800AA284;

/* Other members of the state block by their own names. */
extern s32 D_800AA250;                  /* unk_08 */
extern s32 D_800AA260;                  /* unk_18 */
extern u16 D_800AA2C0;                  /* result */
extern s32 D_800AA2DC;                  /* unk_94 */

/* A behaviour slot: 0x40 bytes, in the array D_801D85C8 (D_801D870C in use). Each drives one object through the
 * handler table of its kind (func_80041A70 calls handlers[state]); the monsters' behaviours, the thrown objects.
 * The words from 0x10 on hold different things by kind. */
typedef struct Ai {
    /* 0x00 */ GameObject *obj;                /* the object it drives */
    /* 0x04 */ u16 unk_04;                     /* the player slot last targeted */
    /* 0x06 */ u16 kind;                       /* picks the handler table; 0x17 and 0x18 are special */
    /* 0x08 */ u16 action;                     /* the current action (a thrown object's kind: it indexes D_8007F680) */
    /* 0x0A */ u16 state;                      /* the index into the handler table */
    /* 0x0C */ u16 unk_0C;                     /* 1 while the state is new */
    /* 0x0E */ u16 unk_0E;
    /* 0x10 */ union {                  /* by kind */
                   void *p;
                   struct Monster *monster;
                   struct AiOrder *order;
                   struct Actor *actor;
               } unk_10;
    /* 0x14 */ struct Monster *target;         /* the monster it goes for */
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ u16 unk_1A;
    /* 0x1C */ union {
                   struct AiOrder *order;
                   s16 s;                   /* a countdown */
               } unk_1C;
    /* 0x20 */ u8 unk_20[0x02];
    /* 0x22 */ u16 unk_22;                     /* a countdown (func_800221BC: 0xB4 frames); func_8003E6A4 copies it
                                                * into its order */
    /* 0x24 */ u16 unk_24;
    /* 0x26 */ s16 unk_26;
    /* 0x28 */ union {
                   struct AiLink *link;
                   struct {
                       s16 lo;
                       s16 hi;
                   } s;
               } unk_28;
    /* 0x2C */ u8 unk_2C[0x02];
    /* 0x2E */ s16 unk_2E;
    /* 0x30 */ Fixed unk_30;
    /* 0x34 */ Fixed unk_34;
    /* 0x38 */ u16 unk_38;                     /* a countdown */
    /* 0x3A */ u16 start;                      /* the start position, an index into D_8007B358/D_8007B348 */
    /* 0x3C */ u16 unk_3C;
    /* 0x3E */ u8 unk_3E[0x02];
} Ai;                                   /* 0x40 bytes */

extern Ai D_801D85C8[];
extern u16 D_801D870C;

struct Building;

/* The definition a building is made from (Building.def). */
typedef struct BuildingDef {
    /* 0x00 */ Fixed unk_00;                   /* the kind in u.lo (4: not a building, func_80025124) */
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u8 unk_06[0x02];
    /* 0x08 */ s32 unk_08;                     /* copied into the building record (unk_05C..) */
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ SpriteFrame **frames;          /* its items' frames (Building.frames) */
    /* 0x18 */ s32 unk_18;
} BuildingDef;

/* What Building.unk_018 points to. */
typedef struct BuildingBlock {
    /* 0x00 */ GameObject *unk_00;             /* moved with the building */
    /* 0x04 */ u8 unk_04[0x04];
    /* 0x08 */ u16 unk_08;                     /* hit points? zero: destroyed */
    /* 0x0A */ u16 unk_0A;                     /* the item it belongs to (BuildingItem.unk_04) */
    /* 0x0C */ u8 unk_0C[0x02];
    /* 0x0E */ s16 unk_0E;                     /* the bottom y */
    /* 0x10 */ s16 unk_10;                     /* set when hit */
    /* 0x12 */ u8 unk_12[0x0A];
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;                     /* the top y */
} BuildingBlock;

/* One of a building item's three parts. */
typedef struct BuildingPart {
    /* 0x00 */ GameObject *unk_00;
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ struct Ai *unk_08;               /* a behaviour slot (its object at 0) */
    /* 0x0C */ struct Ai *unk_0C;               /* another (func_8002CD24 passes it to func_8002CE40) */
    /* 0x10 */ GameObject *unk_10;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ u16 unk_16;
} BuildingPart;

/* One of a building's 15 items: a sprite each. */
typedef struct BuildingItem {
    /* 0x00 */ GameObject *obj;                /* its sprite */
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ struct Building *building;      /* the building it is part of */
    /* 0x0C */ BuildingPart unk_0C;
    /* 0x24 */ BuildingPart unk_24;
    /* 0x3C */ BuildingPart unk_3C;
} BuildingItem;                         /* 0x54 bytes */

/* A building, 0x584 bytes: the array D_801D3DC8 (D_801E29A4 of them), set up by func_80025124 from a definition;
 * a 0x98-byte head and 15 items. */
typedef struct Building {
    /* 0x000 */ u16 unk_000;                   /* the item count */
    /* 0x002 */ u16 kind;                      /* its definition's (BuildingDef.unk_00): 2 or 3, the roof's x offset
                                                * 0x28 or 0x3C */
    /* 0x004 */ u16 unk_004;                   /* x */
    /* 0x006 */ u16 unk_006;
    /* 0x008 */ u16 unk_008;
    /* 0x00A */ s16 unk_00A;
    /* 0x00C */ s16 unk_00C;
    /* 0x00E */ s16 unk_00E;
    /* 0x010 */ u16 unk_010;
    /* 0x012 */ u16 unk_012;
    /* 0x014 */ u16 state;                     /* 0, 2-5, 7, 8, 9 and up: falling, 0xD, 0xF, 0x10: gone */
    /* 0x016 */ u16 unk_016;
    /* 0x018 */ BuildingBlock *unk_018;
    /* 0x01C */ u16 unk_01C;
    /* 0x01E */ u16 unk_01E;                   /* its index + 1 */
    /* 0x020 */ BuildingDef *def;              /* the definition it was made from */
    /* 0x024 */ s16 unk_024;
    /* 0x026 */ s16 unk_026;
    /* 0x028 */ s16 unk_028;
    /* 0x02A */ u16 unk_02A;
    /* 0x02C */ u16 unk_02C;
    /* 0x02E */ u16 unk_02E;
    /* 0x030 */ u16 unk_030;
    /* 0x032 */ u16 unk_032;
    /* 0x034 */ u16 unk_034;
    /* 0x036 */ u16 unk_036;
    /* 0x038 */ u16 unk_038;
    /* 0x03A */ u16 unk_03A[15];               /* one per item */
    /* 0x058 */ u16 unk_058;
    /* 0x05A */ u8 unk_05A[0x02];
    /* 0x05C */ void *unk_05C;                 /* from the definition */
    /* 0x060 */ void *unk_060;
    /* 0x064 */ void *unk_064;
    /* 0x068 */ SpriteFrame **frames;          /* from the definition: the items' frames, by item kind - 2 */
    /* 0x06C */ u8 unk_06C[0x04];
    /* 0x070 */ struct BuildingItem *unk_070;
    /* 0x074 */ u16 unk_074;
    /* 0x076 */ u16 unk_076;
    /* 0x078 */ u16 unk_078;
    /* 0x07A */ u16 unk_07A;
    /* 0x07C */ GameObject *unk_07C;
    /* 0x080 */ u16 roof;                      /* the roof's kind, 1..3 (D_8007CFD8[]), 0 none */
    /* 0x082 */ u16 unk_082;
    /* 0x084 */ GameObject *falling;           /* an object made over it (func_8002CA8C) that falls item by item as it
                                                * collapses (func_8002D9F8) */
    /* 0x088 */ u16 unk_088;
    /* 0x08A */ u16 unk_08A;
    /* 0x08C */ s32 unk_08C;
    /* 0x090 */ GameObject *unk_090;
    /* 0x094 */ s16 unk_094;                   /* claimed (func_8002F01C) */
    /* 0x096 */ u8 unk_096[0x02];
    /* 0x098 */ BuildingItem items[15];
} Building;                             /* 0x584 bytes */

extern Building D_801D3DC8[];
extern u16 D_801E29A4;

/* Level-wide flags and per-player counters at D_8007BD78 (.data of main.c; cleared as 0x94 bytes). */
typedef struct LevelFlags {
    /* 0x00 */ s32 flags;                      /* 0x20, 0x40 */
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08[4];                  /* per player (D_801FA8A0[monster id - 1] - 1) */
    /* 0x18 */ u8 unk_18[0x3C];
    /* 0x54 */ s32 unk_54;
    /* 0x58 */ u8 unk_58[0x3C];
} LevelFlags;

extern LevelFlags D_8007BD78;
extern u8 D_801FA8A0[7];                /* the player of each monster id (1-based), 0 for none */

/* The block at D_801D3D64. */
typedef struct Unk1D3D64 {
    /* 0x00 */ u8 unk_00[0x08];
    /* 0x08 */ s16 unk_08;                     /* D_801D3D6C */
    /* 0x0A */ u8 unk_0A[0x10];
    /* 0x1A */ u16 unk_1A;
    /* 0x1C */ u16 unk_1C;
    /* 0x1E */ u8 unk_1E[0x06];
    /* 0x24 */ s16 unk_24;
    /* 0x26 */ s16 unk_26;
    /* 0x28 */ s16 unk_28;
    /* 0x2A */ u8 unk_2A[0x02];
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ u8 unk_30[0x28];
    /* 0x58 */ s32 unk_58;
    /* 0x5C */ u16 unk_5C;
    /* 0x5E */ u16 unk_5E;
    /* 0x60 */ u8 unk_60[0x02];
    /* 0x62 */ u16 unk_62;
} Unk1D3D64;

extern Unk1D3D64 D_801D3D64;

/* The frame's drawing state D_801FAC80 points to: the draw and display environments, two gouraud quads (the sky's
 * gradient: their colour bytes at 0x74..0xB2), the ordering table at 0x154. */
typedef struct DrawState {
    /* 0x00 */ DRAWENV draw;
    /* 0x5C */ DISPENV disp;
    /* 0x70 */ u8 unk_70[0x04];
    /* 0x74 */ u8 unk_74;
    /* 0x75 */ u8 unk_75;
    /* 0x76 */ u8 unk_76;
    /* 0x77 */ u8 unk_77[0x5];
    /* 0x7C */ u8 unk_7C;
    /* 0x7D */ u8 unk_7D;
    /* 0x7E */ u8 unk_7E;
    /* 0x7F */ u8 unk_7F[0x5];
    /* 0x84 */ u8 unk_84;
    /* 0x85 */ u8 unk_85;
    /* 0x86 */ u8 unk_86;
    /* 0x87 */ u8 unk_87[0x5];
    /* 0x8C */ u8 unk_8C;
    /* 0x8D */ u8 unk_8D;
    /* 0x8E */ u8 unk_8E;
    /* 0x8F */ u8 unk_8F[0x9];
    /* 0x98 */ u8 unk_98;
    /* 0x99 */ u8 unk_99;
    /* 0x9A */ u8 unk_9A;
    /* 0x9B */ u8 unk_9B[0x5];
    /* 0xA0 */ u8 unk_A0;
    /* 0xA1 */ u8 unk_A1;
    /* 0xA2 */ u8 unk_A2;
    /* 0xA3 */ u8 unk_A3[0x5];
    /* 0xA8 */ u8 unk_A8;
    /* 0xA9 */ u8 unk_A9;
    /* 0xAA */ u8 unk_AA;
    /* 0xAB */ u8 unk_AB[0x5];
    /* 0xB0 */ u8 unk_B0;
    /* 0xB1 */ u8 unk_B1;
    /* 0xB2 */ u8 unk_B2;
    /* 0xB3 */ u8 unk_B3[0xA1];
    /* 0x154 */ unsigned long ot[1];
} DrawState;

extern DrawState *D_801FAC80;

/* The text printer's state at D_801D8588 (func_8001EDE4 ... func_8001F61C). */
typedef struct TextState {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ void (*unk_04)(void);
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u16 pen_x;
    /* 0x0E */ u16 pen_y;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 *glyphs;                /* the font */
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ u8 *text;                   /* the string being printed */
    /* 0x20 */ u16 unk_20;
    /* 0x22 */ u16 unk_22;
    /* 0x24 */ s32 flags;
    /* 0x28 */ u16 unk_28;
    /* 0x2A */ u16 unk_2A;
    /* 0x2C */ s16 unk_2C;
    /* 0x2E */ s16 unk_2E;
    /* 0x30 */ s16 unk_30;
    /* 0x32 */ u16 unk_32;
    /* 0x34 */ u16 unk_34;
    /* 0x36 */ u16 unk_36;
    /* 0x38 */ s16 unk_38;
    /* 0x3A */ u8 unk_3A;
    /* 0x3B */ u8 unk_3B;
    /* 0x3C */ s32 unk_3C;
} TextState;

extern TextState D_801D8588;

/* A text message as func_8001F39C loads it into the printer: the string follows at 0x18. */
typedef struct TextMessage {
    /* 0x00 */ s32 *glyphs;                /* the font */
    /* 0x04 */ s32 spacing;
    /* 0x08 */ u16 x;
    /* 0x0A */ u16 y;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ void (*layout)(void);       /* func_8001EDE4: centred */
    /* 0x14 */ s32 kind;                   /* the kind of the objects that show it (func_8001E450 frees them) */
    /* 0x18 */ u8 text[1];                 /* as long as the message */
} TextMessage;

/* Data shared by several files. */
extern s16 D_801E1CB4;                   /* the music volume, 0..0x7F */
extern s16 D_8007A688;                   /* an option, 1..100 */
extern s16 D_8007A68C;                   /* a toggle */
extern s16 D_8007A690;                   /* the number of players, 1..3 */
extern s16 D_8007A692;                   /* 0..0x1C */
extern s16 D_8007A694;                   /* the vibration option */
extern GameObject *D_801D373C[2];        /* the SELECT and BACK buttons */
extern u16 D_801D3780;
extern s16 D_801D3D7C;
extern u16 D_801D8750;                   /* the music playing, 0xFFFF for none */
extern u8 D_801D8800[3];                 /* per player: a choice, 0..4 */
extern u32 D_801E0D7C;                   /* the pad buttons pressed */
extern u8 *D_801E1C78;                   /* the file read buffer */
extern s16 D_801E2150;                   /* a volume, 0..0x7F (func_80062D88) */
extern s16 D_801E289C;
extern s16 D_801F9944;
extern s16 D_801F9ADC;
extern s16 D_801FA964;
extern u16 D_801FA968;
extern s16 D_801FA984[3];                /* per player: playing */
extern u8 D_800937E8[];
extern u8 D_800938AC[];
extern u8 D_80095678[];
extern Fixed D_801D8864;                 /* the level's width minus one: a mask positions wrap with (16.16) */
extern Fixed D_801F9AC8;                 /* the camera's x: the screen's left edge (16.16) */
extern s16 D_8007A68A;
extern u16 D_8007A696;
extern u16 D_8007A7D4;
extern s32 D_8007AD4C[];
extern s32 *D_80085114[];
extern Anim D_8008A7A4;
extern u8 D_8008E6AC[];
extern Anim D_8009556C;
extern s16 D_800AA2EC;
extern u16 D_801D36FC;                   /* the game mode */
extern u16 D_801D376C;                   /* the screen's right edge, in pixels */
extern u16 D_801D37B8;
extern u16 D_801D37BC;
extern s16 D_801D3D8A;                   /* D_801D3D64.unk_26 */
extern s32 D_801D3D98[];
extern u16 D_801D8738;
extern u16 D_801D8740;
extern u16 D_801D87B0;                   /* the screen's left edge, in pixels */
extern u16 D_801D87B4;
extern u16 D_801D8866;                   /* the level width's integer half */
extern s16 D_801E0D4C;
extern u8 D_801E0D98[];                  /* D_801E0B78[1] */
extern u16 D_801E1C80;
extern s16 D_801E1E40;
extern GameObject D_801E28C0;            /* the object list's sentinel head */
extern u16 D_801E2A50;
extern s16 D_801F9914;
extern s16 D_801F9A44[];
extern s16 D_801F9AB0;
extern s16 D_801F9ABC;
extern s16 D_801F9ACA;                   /* the camera x's integer half */
extern Fixed D_801F9ACC;                 /* the camera's y: the screen's top edge (16.16). A Fixed like the x, read
                                         * through .w: func_80056840 loads it after its stores into D_800AA248, which
                                         * only a member access allows. Not one record with D_801F9AC8: func_800210C8
                                         * addresses the two as separate symbols */
extern u16 D_801FA734;
extern s16 D_801FA890;
extern s16 D_801FA960;
extern u16 D_801FA98C;
extern u16 D_801FA990;
extern s32 D_801FA9A4;
extern s16 D_801FAC84;
extern s16 D_801FAC8C;
extern s16 D_801FAC90;
extern s32 D_801FB49C[];

#endif /* GAME_H */
