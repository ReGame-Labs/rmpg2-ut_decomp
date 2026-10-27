#ifndef OVERATTR_H
#define OVERATTR_H

/* OVERLAYS/OVERATTR.BIN: the attract mode, the credits and the memory-card screens (src/overattr/overattr.c).
 *
 * The executable's records below declare only the fields this overlay uses, named after include/gameobject.h's
 * view; they will move to include/game.h with the other views of the same objects. */

#include "common.h"

/* ---- the executable's records (to move to include/game.h) ---- */

/* A sprite object of the level (gameobject.h GameObject; game_8001781C's Sprite), linked through `next` in the
 * sorted list whose sentinel head is D_801E28C0. */
typedef struct GameObject {
    /* 0x00 */ struct GameObject *next;
    /* 0x04 */ u8 unk_04[0x1E];
    /* 0x22 */ u16 flags;              /* gameobject.h unk_20.f.flags */
    /* 0x24 */ u8 unk_24[0x4C];
    /* 0x70 */ u16 kind;               /* the id func_8001E450/func_8001EC74 select objects by */
    /* 0x72 */ u8 unk_72[0x02];
    /* 0x74 */ u16 unk_74;
    /* 0x76 */ u8 unk_76[0x02];
    /* 0x78 */ s32 unk_78;
} GameObject;

typedef union {
    s32 v;
    struct {
        s16 frac;
        s16 i;
    } p;
} Fixed16;

/* What func_8001D110 hands out to describe an object to create (gameobject.h ObjectDef). */
typedef struct {
    /* 0x00 */ s32 id;                 /* the sprite/animation id */
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u16 unk_06;             /* flags: 0x20 */
    /* 0x08 */ u8 unk_08[0x08];
    /* 0x10 */ Fixed16 pos_x;
    /* 0x14 */ Fixed16 pos_y;
    /* 0x18 */ u8 unk_18[0x08];
    /* 0x20 */ s32 flags;
} ObjectDef;

/* The level state at D_800AA248 (gameobject.h GameState). */
typedef struct {
    /* 0x00 */ u8 unk_00[0x3C];
    /* 0x3C */ ObjectDef *new_def;     /* the object being created (D_800AA284) */
} GameState;

extern GameState D_800AA248;
extern GameObject D_801E28C0;          /* the object list's sentinel head */

/* ---- the executable's functions and data ---- */

ObjectDef *func_8001D110(void);        /* a fresh definition to fill in */
GameObject *func_8001DCB4();           /* creates the object of D_800AA248.new_def; no argument */
void func_8001E450(s32 kind);          /* frees every object of a kind */
void func_8001A420(void);
void func_80017B24(void);
void func_8001AC18(s32, s32);
void func_8001F61C(u8 *text, s16 x, s16 y, s32 spacing, s32 arg4, s32 *glyphs, s32 kind, s32 arg7); /* draws a text */

extern s32 D_8007ABCC[];               /* a font's glyphs */
extern s16 D_801F9AAC;

extern s16 D_801D3D7C;
extern s32 D_801E28F4[];
extern s16 D_801F9A4A;
extern s16 D_801F9A4C;
extern s16 D_801F9A4E;
extern s16 D_801F9A50;
extern s16 D_801F9ABC;
extern s16 D_801F9ADC;
extern s16 D_801FA88C;
extern u16 D_801D3780;

/* ---- the overlay's own types and data ---- */

/* An object placed at a screen's start (func_80099138). */
typedef struct {
    /* 0x00 */ s32 id;
    /* 0x04 */ u16 flags;              /* or-ed into the object's flags */
    /* 0x06 */ u8 unk_06[0x02];
    /* 0x08 */ s16 x;
    /* 0x0A */ s16 y;
    /* 0x0C */ u16 unk_0C;             /* the definition's flags */
    /* 0x0E */ u8 unk_0E[0x02];
} OverattrPlacement;

extern OverattrPlacement D_800A4430[4];

typedef struct { u32 colors[8]; } CardClut;   /* the save icon's 16-colour CLUT, two per word */
typedef struct { u32 pixels[32]; } CardIcon;  /* a 16x16 4-bit icon frame */

/* The save file's 0x500 bytes (card.c): the memory-card header, then the game's data, with an XOR checksum. */
typedef struct {
    /* 0x000 */ u8 magic[2];           /* "SC" */
    /* 0x002 */ u8 icon_type;          /* 0x11: one icon frame */
    /* 0x003 */ u8 blocks;             /* 1 */
    /* 0x004 */ s16 title[32];         /* Shift-JIS, big-endian */
    /* 0x044 */ u8 unk_044[0x1C];
    /* 0x060 */ CardClut clut;
    /* 0x080 */ CardIcon icon;
    /* 0x100 */ u8 unk_100[0x100];
    /* 0x200 */ s32 unk_200;
    /* 0x204 */ s32 unk_204[6];
    /* 0x21C */ u8 unk_21C[0x1C];
    /* 0x238 */ s32 checksum;          /* the XOR of the 0x140 words with this one zero */
    /* 0x23C */ u8 unk_23C[0x04];
    /* 0x240 */ struct {
                   s16 unk_00;
                   u8 unk_02[0x72];
               } unk_240[6];
    /* 0x4F8 */ u8 unk_4F8[0x08];
} CardSave;

extern CardSave D_800A9300;

/* The Shift-JIS code of the first character of each ASCII run: digits, capitals, small letters. */
typedef struct {
    u16 sjis;
    u16 ascii;
} CardSjisRun;

extern CardSjisRun D_800A3400[3];
extern u16 D_800A340C[];               /* the Shift-JIS codes of the ASCII punctuation, in ASCII order */
extern CardIcon D_800A3360;            /* the save icon */
extern CardClut D_800A33E0;            /* its CLUT */

extern s32 D_800A9220;
extern s32 D_800A9250;

/* card.c */
s32 card_get_status(void);
s32 card_read_save(CardSave *save);
s32 card_write_save(CardSave *save);
s32 card_format(void);
s32 card_calc_checksum(CardSave *save);
void card_init_save(CardSave *save);
s16 card_ascii_to_sjis(u8 c);
void card_string_to_sjis(s16 *dst, u8 *src);

/* overattr_80099118.c */
void func_80099138(OverattrPlacement *p);
void func_800A0CC0(void);

#endif /* OVERATTR_H */
