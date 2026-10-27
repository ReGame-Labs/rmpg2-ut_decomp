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
typedef union {
    s32 v;
    struct {
        s16 frac;
        s16 i;
    } p;
} Fixed16;

typedef struct GameObject {
    /* 0x00 */ struct GameObject *next;
    /* 0x04 */ u8 unk_04[0x10];
    /* 0x14 */ Fixed16 pos_x;
    /* 0x18 */ Fixed16 pos_y;
    /* 0x1C */ u8 unk_1C[0x06];
    /* 0x22 */ u16 flags;              /* gameobject.h unk_20.f.flags */
    /* 0x24 */ u8 unk_24[0x04];
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ u8 unk_2C[0x14];
    /* 0x40 */ s32 unk_40;
    /* 0x44 */ u8 unk_44[0x04];
    /* 0x48 */ void *unk_48;           /* gameobject.h unk_48 */
    /* 0x4C */ u8 unk_4C;
    /* 0x4D */ s8 unk_4D;
    /* 0x4E */ u8 unk_4E[0x22];
    /* 0x70 */ u16 kind;               /* the id func_8001E450/func_8001EC74 select objects by */
    /* 0x72 */ u8 unk_72[0x02];
    /* 0x74 */ u16 unk_74;
    /* 0x76 */ u8 unk_76[0x02];
    /* 0x78 */ u32 unk_78;             /* a colour, 0xBBGGRR (0x808080 normal); -1 left alone by the fades */
    /* 0x7C */ u8 unk_7C[0x04];
    /* 0x80 */ s16 unk_80;
} GameObject;


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
    /* 0x00 */ u8 unk_00[0x20];
    /* 0x20 */ GameObject *cur_obj;    /* the object being updated (D_800AA268) */
    /* 0x24 */ u8 unk_24[0x18];
    /* 0x3C */ ObjectDef *new_def;     /* the object being created (D_800AA284) */
} GameState;

extern GameState D_800AA248;
extern GameObject D_801E28C0;          /* the object list's sentinel head */

/* ---- the executable's functions and data ---- */

ObjectDef *func_8001D110(void);        /* a fresh definition to fill in */
GameObject *func_8001DCB4();           /* creates the object of D_800AA248.new_def; no argument */
void func_8001E450(u16 kind);          /* frees every object of a kind */
void func_8001EC74(s32 kind, s32 value); /* sets unk_74 of every object of a kind */
void func_8001A420(void);
void func_80017B24(void);
void func_8001AC18(s32, s32);
/* What func_80025C08 picks from the list D_800A49D4: the three texts func_8009B19C prints. */
typedef struct {
    u8 *text[3];
} OverattrTexts;

OverattrTexts *func_80025C08(void *list);
void func_8001F39C(void *msg);         /* loads a text message into the printer */
void func_8001EDB0(void);              /* prints it, its text through sprintf */
void func_8001E4B0(GameObject *obj);   /* frees an object */
void func_8001E8C0(s32 kind, s32 arg1);
void func_8001F61C(u8 *text, s16 x, s16 y, s32 spacing, s32 arg4, s32 *glyphs, s32 kind, s32 arg7); /* draws a text */

extern s32 D_8007ABCC[];               /* a font's glyphs */
extern s32 D_8007AD4C[];               /* another font */
extern GameObject *D_801D373C[2];      /* the SELECT and BACK buttons */
extern s16 D_801F9AAC;                 /* the printer's normal colour */

void func_8001F724(u16 id);            /* plays a sound or a music by id; 0xFFFF stops */
void func_80062E44(void);
void func_80062D88(s32 volume);
void func_80062DA8(s32 volume);

extern s16 D_8007A684;                 /* the music test's track, 0..0x72 */
extern s16 D_8007A686;                 /* options, 15..90 by 5 */
extern s16 D_8007A688;                 /* options, 1..100 */
extern u16 D_8007A68A;                 /* a toggle */
extern u16 D_8007A68C;                 /* a toggle */
extern s16 D_8007A68E;                 /* 0..2, selects D_800A6F3C */
extern s16 D_8007A692;                 /* 0..0x1C */
extern u16 D_8007A694;                 /* a toggle */
extern u8 *D_8007C704[];               /* names, by index */
extern s16 D_801E1CB4;                 /* a volume, 0..0x7F (func_80062DA8) */
extern s16 D_801E2150;                 /* a volume, 0..0x7F (func_80062D88) */
extern s16 D_801F9944;
extern s16 D_801FA960;                 /* 0..0x7C */
extern s16 D_801D3D7C;
extern s16 D_801D885C;                 /* the lit menu item's value (func_8001EC74) */
extern s16 D_801E2148;
extern s16 D_801E289C;
extern s16 D_801FA984[3];              /* per player: playing */
extern s16 D_8007C974;
extern s16 D_8007A690;                 /* the number of players, 1..3 */
extern s32 D_800AA2DC;
extern u16 D_800AA2EC;                 /* the printer's colour */
extern s32 D_801F9AC8;
extern s32 D_801F9ACC;

/* A text message as func_8001F39C loads it into the printer (game_8001781C.h TextMessage). */
typedef struct {
    /* 0x00 */ s32 *glyphs;            /* the font */
    /* 0x04 */ s32 spacing;
    /* 0x08 */ u16 x;
    /* 0x0A */ u16 y;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ void (*layout)(void);   /* func_8001EDE4: centred */
    /* 0x14 */ s32 kind;               /* the kind of the objects that show it (func_8001E450 frees them) */
    /* 0x18 */ u8 text[1];             /* as long as the message */
} TextMessage;

void func_8001ED54(TextMessage *msg);  /* loads and prints a message */
void func_8001ECB4(u8 *dst, s16 value, s32 arg2); /* writes a number into a message's text */
extern u16 D_801E2A44;                 /* the printer's colour for the item under the cursor */

/* The text printer's state (game_8001781C.h TextState). */
typedef struct {
    /* 0x00 */ u8 unk_00[0x1C];
    /* 0x1C */ u8 *text;
} TextState;

extern TextState D_801D8588;
/* The screen's objects. */
extern struct {
    GameObject *unk_00;
    GameObject *obj[18];
} D_801E28F4;
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

/* A menu: record 0 holds the item count, a parent menu and the cursor, the items start at record 2. */
typedef struct MenuRecord {
    /* 0x00 */ s32 unk_00;             /* record 0: the item count */
    /* 0x04 */ struct MenuRecord *sub; /* record 0: another menu, whose item at the cursor is lit too */
    /* 0x08 */ s16 kind;               /* an item: the kind of its objects; record 0: the cursor */
    /* 0x0A */ u8 unk_0A[0x02];
} MenuRecord;

/* The cheat screen's lines: CITY, SOUNDFX, DAMAGE, LIVES, MOVIE. */
extern TextMessage D_800A6300;
extern TextMessage D_800A6338;
extern TextMessage D_800A6360;
extern TextMessage D_800A6384;
extern TextMessage D_800A63A8;
/* The values inside the first four lines' texts, reached as symbols of their own. */
extern u8 D_800A631E[];
extern u8 D_800A6359[];
extern u8 D_800A6380[];
extern u8 D_800A63A3[];
extern s16 D_800A92D0;                 /* the cheat screen's cursor, 0..4 */

extern MenuRecord *D_800A92C0;          /* the current menu */
extern MenuRecord *D_800A92D8;          /* the menu to open next */
extern s16 D_800A9870;                  /* the cursor in the next menu */
extern s16 D_800A9878;
extern s16 D_800A9898;
extern s16 D_800A9810[6];              /* the listed saves' text y */
extern s16 D_800A9820[6];              /* their text x */
extern s16 D_800A9830[6];              /* their slot */
extern s16 D_800A98B8;                 /* the memory-card screen's state */
extern s32 D_800A9228;                 /* the player slot before the last move */
extern u8 D_800A74E4[];                /* an animation script */
extern s16 D_800A92B0[3];              /* per player: the selection's state, 3 done */
extern u8 D_801D8800[3];               /* per player: a choice, 0..4 */
extern s16 D_800A9840;
extern s16 D_800A9800;
extern GameObject *D_800A9808[2];      /* the two volume bars */
extern u8 D_800A9890[6];                /* a name being entered, 5 letters */
extern TextMessage *D_800A6F48[5];      /* the name entry's letters */
extern MenuRecord D_800A6FCC[];
extern MenuRecord D_800A7014[];
extern MenuRecord D_800A7080[];
extern MenuRecord D_800A70A4[];
extern MenuRecord D_800A7104[];
extern MenuRecord D_800A714C[];
extern MenuRecord D_800A71A0[];
extern MenuRecord D_800A7284[];

extern s16 D_800A9888;                 /* the fade the objects' colours run (func_8009B478): 1 to black, 2 to white */
extern u8 D_800A49D4[];
extern u8 D_800A49E4[];
extern u8 D_800A49FC[];
extern u8 D_800A4A14[];

/* A saved game in the save file (0x74 bytes). */
typedef struct {
    /* 0x00 */ s16 unk_00;             /* the save's number: the newest is the largest */
    /* 0x02 */ s16 city;               /* an index into the city names D_8007C704 */
    /* 0x04 */ u8 unk_04[0x3A];
    /* 0x3E */ u16 unk_3E;
    /* 0x40 */ u16 unk_40;
    /* 0x42 */ u16 unk_42;
    /* 0x44 */ u16 unk_44;
    /* 0x46 */ u8 unk_46[3];
    /* 0x49 */ u8 unk_49[7];           /* the number of non-zero entries is printed as "%dP" */
    /* 0x50 */ u8 unk_50[0x08];
    /* 0x58 */ u16 unk_58[7];
    /* 0x66 */ u8 unk_66[0x02];
    /* 0x68 */ u16 unk_68;
    /* 0x6A */ u16 unk_6A;
    /* 0x6C */ u16 unk_6C;
    /* 0x6E */ u16 unk_6E;
    /* 0x70 */ u16 unk_70;
    /* 0x72 */ u8 unk_72[0x02];
} CardSlot;

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
    /* 0x240 */ CardSlot slots[6];
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

extern s16 D_800A6F3C[3 * 2];          /* per D_8007A68E: the values of D_8007A688 and D_8007A686 */
extern s16 D_800A6F78;
extern u8 *D_800A72D8[];               /* the movies' names */
extern s16 D_800A9860;                 /* frames left before the attract mode resumes, reset by a key */

extern s32 D_800A9220;                 /* the pad buttons pressed this frame (func_80099118) */
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
GameObject *func_80099138(OverattrPlacement *p);
void func_800A0CC0(void);
void func_8009E3C0(s32 kind, s32 value);
void func_8009E40C(void *list, s32 selected);
void func_8009E4D4(void);
void func_8009D0B0(void);
void func_800A1804(void);
void func_800A1B9C(void);
void func_800A2138(void);
void func_800A28DC(void);
void func_800A309C(void);

#endif /* OVERATTR_H */
