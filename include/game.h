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
    /* 0x14 */ u16 unk_14;              /* a building item's frame: where a behaviour slot's object sits on each */
    /* 0x16 */ u16 unk_16;              /* part (func_8003DD70): (x, y) on the left part, */
    /* 0x18 */ u16 unk_18;              /* on the middle one, */
    /* 0x1A */ u16 unk_1A;
    /* 0x1C */ u16 unk_1C;              /* on the right one */
    /* 0x1E */ u16 unk_1E;
    /* 0x20 */ u16 unk_20;              /* a third point: x (a spawn origin) */
    /* 0x22 */ u16 unk_22;              /* y */
    /* 0x24 */ s16 unk_24;              /* a fourth point: x (where an Npc's second object sits, main_place_attached) */
    /* 0x26 */ s16 unk_26;              /* y */
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
    /* 0x24 */ union {
                   s32 w;                   /* the frame's first word, or its VRAM slot's (func_8001A554): the
                                             * texture's v and u, then the page (main_get_tpage) */
                   struct {
                       u8 v;
                       u8 u;
                   } uv;                    /* main_draw_objects reads the bytes */
               } tex;
    /* 0x28 */ Fixed unk_28;
    /* 0x2C */ Fixed unk_2C;            /* the frame's size too (func_8001E59C sets both): u.lo the width, u.hi the height */
    /* 0x30 */ Fixed size;              /* the frame's size: u.lo the width, u.hi the height */
    /* 0x34 */ SpriteFrame *frame;      /* the current frame's metrics */
    /* 0x38 */ s32 anim_frame;          /* the current animation frame id */
    /* 0x3C */ s32 last_frame;           /* the frame id func_8001A554 last set */
    /* 0x40 */ union {
                   struct GameObject *obj;  /* a link (main.c's list from D_801D8584) */
                   s32 w;                   /* a value; a box's width (main_create_box: the status bars, OVERATTR's
                                             * volume bars) */
                   s32 *ids;                /* the frames a cloud strip cycles (building.c, the sky) */
                   s32 prev_x;              /* a searchlight beam's foot: its x last frame (npc_place_searchlight) */
               } unk_40;
    /* 0x44 */ union {                  /* by kind */
                   s32 pc;                  /* the animation script's next command (an address) */
                   s32 height;              /* a box's height (main_create_box; the results bars, tour_update_results) */
                   s32 v;                   /* a value (OVERATTR's logo: a y, with unk_40.w its x) */
               } script;
    /* 0x48 */ s32 anim;                /* the current animation (an address: the script restarts there) */
    /* 0x4C */ u8 unk_4C;
    /* 0x4D */ u8 frames_left;           /* frames left on the animation command (every reader loads it with lbu) */
    /* 0x4E */ u8 unk_4E[0x02];
    /* 0x50 */ union {                  /* by kind */
                   struct GameObject *obj;  /* a link */
                   s32 cam_start;           /* OVERATTR's camera: its start point, y << 16 | x (tour_update_map) */
                   s32 count;               /* a monster's bomb (kind 0x73A): its bounces */
                   s32 xy;                  /* a quad box's corner, y << 16 | x (npc_place_searchlight) */
               } unk_50;
    /* 0x54 */ union {
                   s32 w;
                   s32 cam_end;             /* OVERATTR's camera: its end point, y << 16 | x */
                   s32 xy;                  /* a quad box's corner, y << 16 | x (npc_place_searchlight) */
               } unk_54;
    /* 0x58 */ u8 unk_58[0x04];
    /* 0x5C */ union {                  /* the operands of the script command being run */
                   void *p;
                   u16 *h;
                   s32 *w;
                   s32 cam_point;           /* OVERATTR's camera: its current point, y << 16 | x */
                   s32 xy;                  /* a quad box's corner, y << 16 | x (npc_place_searchlight) */
               } arg;
    /* 0x60 */ s32 unk_60;               /* a quad box's fourth corner, y << 16 | x (npc_place_searchlight) */
    /* 0x64 */ union {                  /* by kind */
                   s32 w;
                   s32 count;               /* a results bar: the tally shown so far (tour_update_results) */
               } unk_64;
    /* 0x68 */ union {                  /* a monster's body: its monster; an effect: two halfwords */
                   struct Monster *monster;
                   s32 w;
                   struct {
                       u16 lo;
                       u16 hi;
                   } u;
                   u16 *h;
               } unk_68;
    /* 0x6C */ u16 unk_6C;              /* 0x80: gone */
    /* 0x6E */ u16 vram_slot;            /* its VRAM slot (D_801F9AE4) while unk_6C & 0x400 (func_8001A554) */
    /* 0x70 */ u16 kind;                /* the id main_free_kind and func_8001EC74 select objects by (0x790 + a
                                         * monster's slot for the status sprites) */
    /* 0x72 */ u16 bank;                 /* its frame's bank, the id's bits 24-29 (D_801FA738; picks the CLUT row) */
    /* 0x74 */ u16 unk_74;
    /* 0x76 */ u8 unk_76[0x02];
    /* 0x78 */ union {
                   u32 w;                   /* 0x808080: neutral; -1: unlit (main_draw_objects) */
                   struct {
                       u8 b;
                       u8 g;
                       u8 r;
                   } rgb;
               } colour;
    /* 0x7C */ s32 unk_7C;
    /* 0x80 */ u16 priority;            /* the draw order: the list is kept sorted by it, highest first (main_resort_objects) */
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
    /* 0x98 */ union {
                   void *p;                 /* the record that grabbed it */
                   s32 result;              /* how a thrown object ended: 1 it hit a monster, 2 it fell (npc.c) */
               } unk_98;
    /* 0x9C */ s32 unk_9C;
    /* 0xA0 */ u8 unk_A0[0x2C];
} GameObject;                           /* 0xCC bytes */

/* A monster, a player's or the computer's: 0x220 bytes, in the array D_801E0B78 (by its number). */
typedef struct Monster {
    /* 0x000 */ u16 id;                        /* its number, 1..7 (a player's is 1-based) */
    /* 0x002 */ s16 lives_shown;                 /* the lives the panel shows (bonus_update_lives) */
    /* 0x004 */ s16 lives;                       /* its lives left; the score earns more (bonus_find_most_lives) */
    /* 0x006 */ u16 kind;                      /* the monster kind: 0x15 has its own thrown objects */
    /* 0x008 */ Fixed health;                  /* 0..0x44 (16.16): zero, it is out; a continue refills it */
    /* 0x00C */ Fixed health_shown;            /* eased towards health by 1/16 a frame; health_bar shows it */
    /* 0x010 */ Fixed meter;                   /* a second meter, 0..0x44 (16.16): a projectile's hit raises it
                                                * (func_8004C0E0); full, monster 5 gets its extra sprites */
    /* 0x014 */ Fixed meter_shown;             /* eased towards meter by 1/16 a frame (bonus_update_bars); meter_bar
                                                * shows it */
    /* 0x018 */ u16 unk_018;
    /* 0x01A */ u16 extra_uses;              /* & 0xF: the uses of monster 5's extra sprites left, 3 when its meter
                                                * fills (main.c) */
    /* 0x01C */ u16 unk_01C;                   /* a countdown set from a random draw */
    /* 0x01E */ u16 unk_01E;                   /* its id at spawn */
    /* 0x020 */ u16 unk_020;                   /* a tally for the results (OVERATTR's first bar) */
    /* 0x022 */ u16 unk_022;                   /* the step of a throw sequence, 0..4 */
    /* 0x024 */ u16 unk_024;                   /* a tally for the results (the second bar): eating a person or a
                                                * pickup adds one */
    /* 0x026 */ u16 unk_026;                   /* a tally for the results (the third bar): func_8003111C adds to it */
    /* 0x028 */ u16 unk_028;
    /* 0x02A */ u16 unk_02A;                   /* the kind of throw in progress, 0 none */
    /* 0x02C */ u8 unk_02C[0x08];
    /* 0x034 */ s32 score_shown;               /* the score the panel shows (bonus_update_score) */
    /* 0x038 */ s32 score;
    /* 0x03C */ u16 unk_03C;
    /* 0x03E */ u16 unk_03E;
    /* 0x040 */ s32 play_frames;             /* frames in play, actions 0x26 and 0x37 aside (main_update_monsters);
                                                * npc_pick_target prefers players past 0x1C20 */
    /* 0x044 */ s16 unk_044;
    /* 0x046 */ u16 unk_046;
    /* 0x048 */ u8 unk_048[0x0E];
    /* 0x056 */ u16 icon_kind;               /* the icon its status panel shows (bonus.c): 1, 2 by icon_timers, 5 (func_8004F910) */
    /* 0x058 */ u16 unk_058;                   /* flags; 1: in play */
    /* 0x05A */ u16 action;                    /* the state the script dispatcher runs */
    /* 0x05C */ u16 prev_action;             /* the action before a script set one (func_8004C738); func_8004CCAC
                                                * goes back to it */
    /* 0x05E */ s16 unk_05E;
    /* 0x060 */ u8 unk_060[0x04];
    /* 0x064 */ u16 unk_064;
    /* 0x066 */ u8 unk_066[0x02];
    /* 0x068 */ GameObject *obj;               /* its body */
    /* 0x06C */ GameObject *meter_bar;         /* status bars: boxes whose width (unk_40.w) is the value shown, */
    /* 0x070 */ GameObject *health_bar;        /* at most 0x44 (bonus_create_bars, bonus_update_bars) */
    /* 0x074 */ GameObject *portrait;          /* its portrait in the status panel, animated by id (bonus_update_lives) */
    /* 0x078 */ GameObject *lives_digits[2];   /* the digit sprites of lives */
    /* 0x080 */ GameObject *score_digits[6];   /* the digit sprites of score (bonus_create_score) */
    /* 0x098 */ GameObject *icons[3];          /* the status icons (bonus.c), [0] its body sprite too (func_8002CBF4) */
    /* 0x0A4 */ GameObject *bars[3];           /* the results bars, one per tally (OVERATTR, tour_create_bars) */
    /* 0x0B0 */ u8 unk_0B0[0x04];
    /* 0x0B4 */ GameObject *extra[5];          /* its own sprites (5's, 7's: kind 0x73A; 2-4 func_8002A1AC), or NULL */
    /* 0x0C8 */ u16 buttons;                   /* the pad's buttons held, pad bits >> 4 (main_update_input); & 0xF: the
                                                * direction bits, the index into the action's handler table (func_80027FD0) */
    /* 0x0CA */ u8 unk_0CA[0x02];
    /* 0x0CC */ u16 dir;                       /* the d-pad direction, 0 none (D_8007C124[pad bits & 0xF]); an index
                                                * into the per-file speed tables */
    /* 0x0CE */ s16 unk_0CE;
    /* 0x0D0 */ u16 pressed;                 /* the buttons pressed this frame (main_update_input), bits as buttons */
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
    /* 0x0EC */ u16 unk_0EC;
    /* 0x0EE */ s16 unk_0EE;
    /* 0x0F0 */ s32 unk_0F0;                   /* a change to its health, applied once (main_apply_health) */
    /* 0x0F4 */ s16 front_x;                   /* its front: pos_x plus or minus half its width, by its facing */
    /* 0x0F6 */ u16 unk_0F6;
    /* 0x0F8 */ u8 unk_0F8[0x02];
    /* 0x0FA */ u16 unk_0FA;
    /* 0x0FC */ u16 unk_0FC;
    /* 0x0FE */ u8 unk_0FE[0x02];
    /* 0x100 */ s32 unk_100;                   /* a horizontal speed, 16.16 */
    /* 0x104 */ s32 unk_104;                   /* a vertical acceleration, 16.16 */
    /* 0x108 */ s16 box_x0;                    /* two boxes, (x0, y0)-(x1, y1): monster_test_boxes says which one a */
    /* 0x10A */ s16 box_y0;                    /* point is in */
    /* 0x10C */ s16 box_x1;
    /* 0x10E */ s16 box_y1;
    /* 0x110 */ s16 box2_x0;
    /* 0x112 */ u16 box2_y0;
    /* 0x114 */ s16 box2_x1;
    /* 0x116 */ u16 box2_y1;
    /* 0x118 */ u16 hit_left;                  /* the hit box the pickups and the projectiles test */
    /* 0x11A */ u16 hit_top;
    /* 0x11C */ s16 hit_right;
    /* 0x11E */ u16 hit_bottom;
    /* 0x120 */ Fixed pos;                     /* its position: s.lo x, s.hi y */
    /* 0x124 */ u16 special_timer;           /* the special move's frames left, 300 for the charge (monster_anim.c) */
    /* 0x126 */ u16 unk_126;
    /* 0x128 */ u16 depth;                   /* its rank in depth among the monsters, 1, 4 or 8 by x (func_800268BC):
                                                * added to its priority (main_update_priority) */
    /* 0x12A */ u16 unk_12A;
    /* 0x12C */ u16 body_priority;           /* its body's priority at the start of the frame (main_update_monsters) */
    /* 0x12E */ u8 unk_12E[0x02];
    /* 0x130 */ u16 unk_130;                   /* 0x130..0x14A: countdowns, func_80029984 runs them all down */
    /* 0x132 */ u16 unk_132;
    /* 0x134 */ u8 unk_134[0x04];
    /* 0x138 */ u16 unk_138;
    /* 0x13A */ u8 unk_13A[0x02];
    /* 0x13C */ u16 unk_13C;
    /* 0x13E */ u16 idle_timer;                /* frames to its next idle animation (0x1A4) */
    /* 0x140 */ u16 icon_timers[3];            /* the frames left on each status icon (bonus.c shows them); [1] nonzero: the
                                                * vibration presets 0-3 run twice as strong and long */
    /* 0x146 */ s16 unk_146;
    /* 0x148 */ u16 unk_148;
    /* 0x14A */ u16 unk_14A;                   /* the last of the countdowns */
    /* 0x14C */ s32 unk_14C;
    /* 0x150 */ s16 unk_150;
    /* 0x152 */ u16 unk_152;
    /* 0x154 */ u8 unk_154[0x0C];
    /* 0x160 */ GameObject *holder;            /* an object it is carried by: monster_follow_holder places it there */
    /* 0x164 */ u16 unk_164;
    /* 0x166 */ u16 unk_166;
    /* 0x168 */ u16 unk_168;
    /* 0x16A */ u8 unk_16A[0x02];
    /* 0x16C */ GameObject *unk_16C;
    /* 0x170 */ u16 unk_170;
    /* 0x172 */ u8 unk_172[0x02];
    /* 0x174 */ s32 unk_174;                   /* -1 at spawn */
    /* 0x178 */ u16 unk_178;                   /* its id at spawn */
    /* 0x17A */ u16 idle_alt;                  /* toggled when idle_timer runs out: picks the other idle animation */
    /* 0x17C */ s32 unk_17C;
    /* 0x180 */ struct Monster *attacker;      /* the monster that hit it last (func_8005421C) */
    /* 0x184 */ u16 unk_184;
    /* 0x186 */ u16 unk_186;
    /* 0x188 */ u16 unk_188;
    /* 0x18A */ u16 unk_18A;
    /* 0x18C */ u16 unk_18C;
    /* 0x18E */ u16 unk_18E;
    /* 0x190 */ u8 unk_190[0x08];
    /* 0x198 */ s32 unk_198;
    /* 0x19C */ s32 unk_19C;
    /* 0x1A0 */ s32 unk_1A0;
    /* 0x1A4 */ s32 unk_1A4;
    /* 0x1A8 */ u8 unk_1A8[0x02];
    /* 0x1AA */ u16 unk_1AA;
    /* 0x1AC */ u16 unk_1AC;
    /* 0x1AE */ u16 unk_1AE;
    /* 0x1B0 */ u16 climb_side;                /* 0: not on a building; 1, 2: the side it climbs; 3 (func_80054D74) */
    /* 0x1B2 */ u16 climb_building;            /* the building, 1-based (monster_get_building) */
    /* 0x1B4 */ u16 climb_floor;               /* the building's item it is at */
    /* 0x1B6 */ u8 unk_1B6[0x06];
    /* 0x1BC */ u16 unk_1BC;
    /* 0x1BE */ u16 skip_building;             /* a building (Building.unk_01E) the scans leave out, 0 none */
    /* 0x1C0 */ s32 screen_y;                /* its body's y on the screen, 16.16 (main_update_screen_pos; also D_801D3DA8[]) */
    /* 0x1C4 */ Fixed screen_x;              /* its body's x on the screen (also D_801D3D9C[]) */
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
    /* 0x1E2 */ u16 unk_1E2;
    /* 0x1E4 */ s16 *unk_1E4;                  /* the demo's input script: 12-byte records (frame, direction, buttons), 0x7FFF ends it */
    /* 0x1E8 */ u8 unk_1E8[0x10];
    /* 0x1F8 */ s32 unk_1F8;
    /* 0x1FC */ GameObject *shadow;          /* its shadow, moved with it (func_800535E4) */
    /* 0x200 */ struct Monster *bump_target;   /* a monster it bounces off (func_80053204) */
    /* 0x204 */ u16 unk_204;
    /* 0x206 */ u8 unk_206[0x02];
    /* 0x208 */ s32 bounce_vy;               /* a bounce off another monster (func_80053204, func_800535E4): the
                                                * velocity, */
    /* 0x20C */ s32 bounce_vx;
    /* 0x210 */ s32 bounce_dy;               /* and what each frame adds to it, until it crosses zero */
    /* 0x214 */ s32 bounce_dx;
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
    /* 0x24 */ s32 unk_24;
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
    /* 0x14 */ s32 action;                     /* the monster's action, clamped, before the dispatch (monster_dispatch_action;
                                                * D_800AA25C) */
    /* 0x18 */ s32 unk_18;                     /* the argument of the current actor's handler (D_800AA260) */
    /* 0x1C */ union {
                   ObjectDef *def;
                   s32 n;                   /* a count (main_count_monsters) */
                   s32 flags;               /* the object's flags while its script runs (main_step_anim) */
               } unk_1C;
    /* 0x20 */ GameObject *cur_obj;            /* the object being updated (D_800AA268) */
    /* 0x24 */ s32 dir;                        /* a monster's direction, copied before its handlers run (D_800AA26C);
                                                * scratch: main_count_monsters's count */
    /* 0x28 */ union {
                   s32 n;                   /* a counter (pickup_hide_items: the items left in the building) */
                   s32 *p;                  /* a write pointer into a word list (main_step_anim) */
               } unk_28;
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
    /* 0x58 */ void (*on_create)(void);       /* the creation callback of an ObjectDef (func_8001DCB4) */
    /* 0x5C */ u8 unk_5C[0x04];
    /* 0x60 */ s32 def_flags;                  /* the ObjectDef stream's flags: which optional words follow
                                                * (func_8001DCB4; D_800AA2A8) */
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

/* The behaviour records: each drives one object (GameObject.owner points back to it). Five record sets share a head
 * (the object at 0x00, the kind at 0x06; Ai, Npc, Pickup and UnkStructB2 also the action at 0x08 and the "new state"
 * flag at 0x0C) but not a size: Ai and Actor are 0x40 bytes, Npc 0x78, Pickup 0x58, UnkStructB2 0x30, the strides of
 * their arrays. So each set is its own type, with the same names at the same offsets; a function takes the record its
 * callers pass (main.c's func_80020DDC chain is the Npc kinds 0x11 and 0x12's, not the Ai's), and the few that take
 * any record (func_8003C8D4, func_8003D4AC) are called with a cast.
 *
 * A behaviour slot: 0x40 bytes, in the array D_801D85C8 (D_801D870C in use). Each drives one object through the
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
                   struct BuildingPart *part;   /* the building part it holds (func_8003DD70) */
                   struct Actor *actor;
               } unk_10;
    /* 0x14 */ struct Monster *target;         /* the monster it goes for */
    /* 0x18 */ s16 timer;                      /* a countdown */
    /* 0x1A */ u16 unk_1A;
    /* 0x1C */ union {
                   struct Building *building;   /* the building of that part */
                   s16 s;                   /* a countdown */
               } unk_1C;
    /* 0x20 */ u8 unk_20[0x02];
    /* 0x22 */ u16 unk_22;                     /* a countdown; func_8003E6A4 copies it
                                                * into its order */
    /* 0x24 */ u16 unk_24;
    /* 0x26 */ s16 unk_26;
    /* 0x28 */ union {
                   struct BuildingItem *item;   /* the item of that part */
                   struct {
                       s16 lo;
                       s16 hi;
                   } s;
               } unk_28;
    /* 0x2C */ u8 unk_2C[0x02];
    /* 0x2E */ u16 delay;                      /* a countdown before it acts */
    /* 0x30 */ Fixed unk_30;
    /* 0x34 */ Fixed unk_34;
    /* 0x38 */ u16 unk_38;                     /* a countdown */
    /* 0x3A */ u16 unk_3A;
    /* 0x3C */ u16 unk_3C;
    /* 0x3E */ u8 unk_3E[0x02];
} Ai;                                   /* 0x40 bytes */

extern Ai D_801D85C8[];
extern u16 D_801D870C;

/* A thrown object's slot: 0x10 bytes, 21 in D_801E1CC4 (D_801D8724 in use), filled by func_8004A9B0 and run by
 * func_8004AD18 by its kind; npc.c makes and runs some kinds too (npc_create_throw, npc_update_throw, npc_create_shot,
 * npc_update_shot). */
typedef struct Throw {
    /* 0x00 */ GameObject *obj;
    /* 0x04 */ GameObject *thrower;            /* the current object when the throw was made (func_8004A9B0) */
    /* 0x08 */ u16 kind;                       /* func_8004AD18 dispatches on it */
    /* 0x0A */ u16 state;                      /* 1 in flight, 0x10 done */
    /* 0x0C */ s32 unk_0C;                     /* npc.c's kinds: added to the object's vel_y each frame, 16.16
                                                * (npc_create_throw sets it, npc_update_throw) */
} Throw;

extern Throw D_801E1CC4[];

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
    /* 0x1C */ void *unk_1C;                   /* what func_8002F688 shows on the item it destroys (func_8002FB38) */
    /* 0x20 */ s32 unk_20[0];                  /* its items' sprite ids, bottom up, 0-terminated (main_create_building_items) */
} BuildingDef;

/* What Building.unk_018 points to. */
typedef struct BuildingBlock {
    /* 0x00 */ GameObject *unk_00;             /* moved with the building */
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u16 unk_08;                     /* hit points? zero: destroyed */
    /* 0x0A */ u16 unk_0A;                     /* the item it belongs to (BuildingItem.unk_04) */
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;                     /* the bottom y */
    /* 0x10 */ s16 unk_10;                     /* set when hit */
    /* 0x12 */ u8 unk_12[0x0A];
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;                     /* the top y */
} BuildingBlock;

/* One of a building item's three parts; a behaviour slot takes one free part (Ai.unk_10.part, actor_pick_building_part). */
typedef struct BuildingPart {
    /* 0x00 */ GameObject *unk_00;
    /* 0x04 */ u16 unk_04;                     /* its side: 1 left, 2 right, else the middle (func_8003E59C) */
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ struct Ai *unk_08;               /* a behaviour slot (its object at 0) */
    /* 0x0C */ struct Ai *unk_0C;               /* another (func_8002CD24 passes it to func_8002CE40) */
    /* 0x10 */ GameObject *unk_10;
    /* 0x14 */ u16 unk_14;                     /* set to 1 when the item is made; a behaviour slot's kind once it leaves
                                                * (func_8003E6A4) */
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
    /* 0x004 */ u16 left;                      /* its box: the left wall's x, */
    /* 0x006 */ u16 bottom;                    /* the ground's y (top and right below) */
    /* 0x008 */ u16 priority;                  /* its depth, 0x200 or 0x300: the objects on it are drawn at it + 0x10.. and
                                                * the floor tables are picked by it */
    /* 0x00A */ s16 unk_00A;
    /* 0x00C */ s16 unk_00C;
    /* 0x00E */ s16 right;                     /* the right wall's x */
    /* 0x010 */ u16 unk_010;
    /* 0x012 */ u16 unk_012;
    /* 0x014 */ u16 state;                     /* 0, 2-5, 7, 8, 9 and up: falling, 0xD, 0xF, 0x10: gone */
    /* 0x016 */ u16 unk_016;
    /* 0x018 */ BuildingBlock *unk_018;
    /* 0x01C */ u16 unk_01C;
    /* 0x01E */ u16 unk_01E;                   /* its index + 1 */
    /* 0x020 */ BuildingDef *def;              /* the definition it was made from */
    /* 0x024 */ s16 left_side;                 /* who holds the left side: 0 free, else an index + 1 (func_8002D2CC */
    /* 0x026 */ s16 unk_026;                   /* compares the three with its argument); below 0 closed */
    /* 0x028 */ s16 right_side;                /* who holds the right side */
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
    /* 0x06C */ s32 unk_06C;
    /* 0x070 */ struct BuildingItem *unk_070;
    /* 0x074 */ u16 top;                       /* the roof's y */
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
    /* 0x04 */ s32 turn_player;                /* the player whose turn it is in a bonus round taken in turns
                                                * (cdload_get_next_player) */
    /* 0x08 */ s32 tally[3];                   /* per player (D_801FA8A0[monster id - 1] - 1): the bonus round's tally */
    /* 0x14 */ s32 round_timer;                /* the bonus round's time left in seconds, 0x14..0x3C by round (D_8007BD8C) */
    /* 0x18 */ u16 second_frames[4];           /* per player - 1: frames counted towards a second (bonus_update_counters) */
    /* 0x20 */ u32 award_frames;               /* frames since the awards screen opened (bonus_update_awards) */
    /* 0x24 */ GameObject *digits[4][3];       /* per player - 1: digit sprites (bonus_create_counter) */
    /* 0x54 */ s32 award_msg;                  /* the awards screen's title message (kind 0x7D0) */
    /* 0x58 */ s32 award_line_msgs[3];         /* the award messages sliding in (kinds 0x7D2, 0x7D3, 0x7D1; bonus_update_awards) */
    /* 0x64 */ s32 health_icons[3];            /* the award icons shown (bonus_give_awards), by kind: health, */
    /* 0x70 */ s32 meter_icons[3];             /* meter, */
    /* 0x7C */ s32 lives_icons[6];             /* extra lives */
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
    /* 0x26 */ s16 scroll_vx;                  /* the camera's x speed in pixels a frame (main_update_camera): thrown
                                                * objects add it to their speed (D_801D3D8A) */
    /* 0x28 */ s16 scroll_state;               /* the camera's vertical scroll: 0 still, 1 up, 2 down
                                                * (main_update_camera_y) */
    /* 0x2A */ u8 unk_2A[0x02];
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 max_y;                      /* the players' lowest and highest screen y (D_801D3DA8[]) this frame */
    /* 0x34 */ s32 min_y;                      /* (main_update_camera_y); min_y is also D_801D3D98[0] */
    /* 0x38 */ u8 unk_38[0x20];
    /* 0x58 */ s32 unk_58;
    /* 0x5C */ u16 unk_5C;
    /* 0x5E */ u16 unk_5E;
    /* 0x60 */ u8 unk_60[0x02];
    /* 0x62 */ u16 pause_state;                /* bits 0-1: the pause menu's state, 8-11: the unplugged pad's player,
                                                * 12-13: the pausing player (main_update_pause) */
} Unk1D3D64;

extern Unk1D3D64 D_801D3D64;

/* The frame's drawing state D_801FAC80 points to: the draw and display environments, the sky's two gouraud quads,
 * the ordering table at 0x148. */
typedef struct DrawState {
    /* 0x00 */ DRAWENV draw;
    /* 0x5C */ DISPENV disp;
    /* 0x70 */ POLY_G4 sky[2];              /* the sky's gradient: [0] from y 0 down to the horizon, [1] the 0xA0 pixels
                                             * above it (building.c sets the colours, main_draw_lists the y values) */
    /* 0xB8 */ POLY_F4 tiles[6];            /* six colour bars (main_init_system) */
    /* 0x148 */ unsigned long ot[4];        /* cleared reversed, drawn from ot[3] */
    /* 0x158 */ u8 prims[0x47E0];           /* the frame's primitives */
    /* 0x4938 */ u8 *next_prim;
    /* 0x493C */ u16 last_tpage;            /* the texture page the last DR_TPAGE set, 0xFFFF none */
    /* 0x493E */ u16 tpage;                 /* the page of the sprites added since: the list is drawn in reverse, so
                                             * the DR_TPAGE added after them sets it (main_draw_objects) */
} DrawState;                                /* two at D_801CA474, the frames' double buffer */

extern DrawState *D_801FAC80;

/* The text printer's state at D_801D8588 (func_8001EDE4 ... func_8001F61C). */
typedef struct TextState {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ void (*unk_04)(void);
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u16 pen_x;
    /* 0x0E */ u16 pen_y;
    /* 0x10 */ Fixed advance;               /* the advance per glyph: x in s.lo, a line feed in s.hi */
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
    /* 0x30 */ s16 space_width;             /* a space's advance: half the font's first glyph's width */
    /* 0x32 */ u16 unk_32;
    /* 0x34 */ u16 line_start;              /* the pen's x at the line's start (with the y at 0x36): a line feed goes
                                            * back to it */
    /* 0x36 */ u16 unk_36;
    /* 0x38 */ s16 unk_38;
    /* 0x3A */ u8 unk_3A;
    /* 0x3B */ u8 unk_3B;
    /* 0x3C */ s32 saved_pen;               /* pen_x and pen_y, saved around a glyph (main_print_text) */
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
    /* 0x14 */ s32 kind;                   /* the kind of the objects that show it (main_free_kind frees them) */
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
extern s16 D_801FA984[4];                /* per player: playing (the save copies a fourth word, menu_write_save) */
extern u8 D_800937E8[];
extern u8 D_800938AC[];
extern u8 D_80095678[];
extern Fixed D_801D8864;                 /* the level's width minus one: a mask positions wrap with (16.16) */
extern Fixed D_801F9AC8;                 /* the camera's x: the screen's left edge (16.16) */
extern s16 D_8007A68A;
extern u16 D_8007A696;
extern u16 D_8007A7D4;
extern s16 D_8007C976;                   /* the weather, drawn by func_8002A3A4: 1 rain (it slows climbing, monster_update_climb), 2 another */
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
extern s16 D_801D3D8A;                   /* D_801D3D64.scroll_vx */
extern s32 D_801D3D98[];
extern u16 D_801D8738;
extern u16 D_801D8740;
extern u16 D_801D87B0;                   /* the screen's left edge, in pixels */
extern u16 D_801D87B4;
extern u16 D_801D8866;                   /* the level width's integer half */
extern s16 D_801E0D4C;
extern u8 D_801E0D98[];                  /* D_801E0B78[1] */
extern u16 D_801E1C80;
extern s16 D_801E1CA4;                   /* main.c clears it; func_8009FF38 passes it to menu_create_player_slots */
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

/* A player's monster on the selection screen (menu_create_player_monster, main.c main_start_demo), 10 bytes. */
typedef struct {
    /* 0x00 */ u8 unk_00[0x04];
    /* 0x04 */ s16 unk_04;              /* the monster: indexes D_800A8EE4, D_800A8FA8 */
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
} OverattrPlayer;

extern OverattrPlayer D_800A8FD4[];

#endif /* GAME_H */
