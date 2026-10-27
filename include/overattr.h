#ifndef OVERATTR_H
#define OVERATTR_H

/* OVERLAYS/OVERATTR.BIN: the attract mode, the credits and the memory-card screens (src/overattr/overattr.c).
 *
 * The executable's records are include/game.h's; this header declares the executable's functions and data the
 * overlay uses, then the overlay's own. */

#include "common.h"
#include "game.h"

/* ---- the executable's functions and data ---- */

ObjectDef *func_8001D110(void);        /* a fresh definition to fill in */
GameObject *func_8001DCB4();           /* creates the object of D_800AA248.new_def; no argument */
void main_free_kind(u16 kind);          /* frees every object of a kind */
void func_8001EC74(s32 kind, s32 value); /* sets unk_74 of every object of a kind */
void func_8001A420(void);
void func_80017B24(void);
void func_8001AC18(s32, s32);
void func_8001F7F8(s32 id);
void func_8002A354(s32 arg0);
void func_80019268(void);
void func_8001A474(void);
void func_8001F760(void);
s32 func_8001AA4C(s32 arg0, s32 arg1);
void func_8001EB3C(void);
void func_8001E94C(s32 x, s32 y, GameObject *obj);   /* moves an object's sprite */
extern s16 D_801CA45C;                 /* the attract screen's state */
extern s16 D_801D872C;
extern u16 D_801F9AE0;
s32 func_8002A300(void);
extern s16 D_801CA464;
extern s16 D_801CA468;
extern u32 D_801FB198;                 /* the time of day in minutes */
/* What func_80025C08 picks from the list D_800A49D4: the three texts func_8009B19C prints. */
typedef struct {
    u8 *text[3];
} OverattrTexts;

OverattrTexts *func_80025C08(void *list);
void func_8001F39C(void *msg);         /* loads a text message into the printer */
void func_8001EDB0(void);              /* prints it, its text through sprintf */
void func_8001E4B0(GameObject *obj);   /* frees an object */
void main_free_kind_masked(s16 kind, s16 mask);
void func_8001F61C(u8 *text, s16 x, s16 y, s32 spacing, s32 arg4, s32 *glyphs, s32 kind, s32 arg7); /* draws a text */

extern s32 D_8007ABCC[];               /* a font's glyphs */
GameObject *main_create_box(s32 x, s32 y, s32 w, s32 h, s32 colour); /* creates a coloured box */
s32 func_80025DF8(s32 player);          /* the monster number of a player */
extern u8 *D_8007F8E0[];               /* the monsters' names, by number - 1 */
extern Monster *D_800A9258;             /* the round's winner (func_800996CC) */
extern s32 D_800A9230;
extern s16 D_801E29BC;
extern s16 D_801F9AAC;                 /* the printer's normal colour */

void func_8001F724(u16 id);            /* plays a sound or a music by id; 0xFFFF stops */
void func_80062E44(void);
void func_80062D88(s32 volume);
void func_80062DA8(s32 volume);

extern s16 D_8007A684;                 /* the music test's track, 0..0x72 */
extern s16 D_8007A686;                 /* options, 15..90 by 5 */
extern s16 D_8007A68E;                 /* 0..2, selects D_800A6F3C */
extern u8 *D_8007C704[];               /* names, by index */
extern s16 D_801D885C;                 /* the lit menu item's value (func_8001EC74) */
extern s16 D_801E2148;
extern s16 D_8007C974;


void func_8001ED54(TextMessage *msg);  /* loads and prints a message */
u8 *func_8001ECB4(u8 *dst, s32 value, s32 digits); /* writes a number into a text, returns the end */
extern u16 D_801E2A44;                 /* the printer's colour for the item under the cursor */

/* The screen's objects (func_800991BC clears 19). */
extern GameObject *D_801E28F4[];
/* Its [1] and [4] reached as symbols of their own (func_8009AE40): only these give its code. */
extern GameObject *D_801E28F8[];
extern GameObject *D_801E2904[];
extern s16 D_801F9A4A;
extern s16 D_801F9A4C;
extern s16 D_801F9A4E;
extern s16 D_801F9A50;
extern s16 D_801FA88C;
extern GameObject *D_800A9270[3];       /* the three monsters of the selection screen (func_8009A238); [0] drops in */
extern s32 D_800A9218;                 /* 1 once it has landed */
extern s32 D_800A9240;                 /* its speed, bouncing to rest */
extern s32 D_800A9238;                 /* frames to the next bounce */
GameObject *menu_animate(GameObject *obj, s32 arg1);

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
extern OverattrPlacement D_800A344C[];  /* the winner's portrait, by monster number */
extern OverattrPlacement D_800A34BC[];  /* the others' portraits, by monster number */
extern OverattrPlacement D_800A353C[2];
extern OverattrPlacement D_800A355C;
extern OverattrPlacement D_800A73C4[4];

typedef struct { u32 colors[8]; } CardClut;   /* the save icon's 16-colour CLUT, two per word */
typedef struct { u32 pixels[32]; } CardIcon;  /* a 16x16 4-bit icon frame */

/* A menu: record 0 holds the item count, a parent menu and the cursor, the items start at record 2. */
typedef struct MenuRecord {
    /* 0x00 */ s32 unk_00;             /* record 0: the item count; an item: its TextMessage */
    /* 0x04 */ struct MenuRecord *sub; /* record 0: another menu, whose item at the cursor is lit too; an item:
                                        * its action, a void (*)(void) (menu_update_name_entry) */
    /* 0x08 */ s16 kind;               /* an item: the kind of its objects; record 0: the cursor */
    /* 0x0A */ u8 unk_0A[0x02];
} MenuRecord;

/* The cheat screen's lines: CITY, SOUNDFX, DAMAGE, LIVES, MOVIE. */
extern TextMessage D_800A6300;
extern TextMessage D_800A6338;
extern TextMessage D_800A6360;
extern TextMessage D_800A6384;
extern TextMessage D_800A63A8;
/* The options screen's lines, by the option's value. */
extern TextMessage D_800A6494;
extern TextMessage D_800A64C0;
extern TextMessage D_800A64EC;
extern TextMessage D_800A6514;
extern TextMessage D_800A6540;
extern TextMessage D_800A656C;
extern TextMessage D_800A6598;
extern TextMessage D_800A65C4;
extern TextMessage D_800A65EC;
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
extern s16 D_800A9868;                 /* the format screen's state */
extern s16 D_800A9858;
extern u16 D_801E28B8;                 /* the memory card's slot */
extern s16 D_800A9810[6];              /* the listed saves' text y */
extern s16 D_800A9820[6];              /* their text x */
extern s16 D_800A9830[6];              /* their slot */
extern s16 D_800A98B8;                 /* the memory-card screen's state */
extern s32 D_800A9228;                 /* the player slot before the last move */
extern u8 D_800A74E4[];                /* an animation script */
extern u8 D_800A7510[];
extern u8 D_800A751C[];
extern s32 D_800A74A8[3];              /* per player slot: the sprite of a player in the game */
extern s32 D_800A74B4[3];              /* and of an empty slot */
extern u8 *D_800A74C0[3];              /* their animations */
extern u8 *D_800A74CC[3];
/* The player slots' objects (menu_create_player_slots): D_801E294C[0..2] and [6..8], D_801E2958 between them. */
extern GameObject *D_801E294C[];
extern GameObject *D_801E2958[3];
extern s16 D_800A92A8[3];
extern s16 D_800A92B0[3];              /* per player: the selection's state, 3 done */
extern s16 D_800A9840;
extern s16 D_800A9800;
extern GameObject *D_800A9808[2];      /* the two volume bars */
extern GameObject *D_800A92F8[2];      /* their markers */
extern u8 D_800A9890[6];                /* a name being entered, 5 letters */
extern TextMessage *D_800A6F48[5];      /* the name entry's letters */
extern u8 *D_8007A69C[7];               /* the names that unlock something (menu_update_name_entry) */
extern void (*D_800A6F5C[7])(void);     /* what each unlocks */
/* The player bars (menu_create_player_bars): three per player, in D_801E28F4[player * 3 + 31..33]. */
extern s16 D_800A734C[];                /* their lengths, by player * 3 + bar */
extern s16 D_800A92E0[];                /* the lengths shown */
extern s16 D_800A98A0[];
extern u8 D_800A747C[];                 /* animations */
extern u8 D_800A7444[];
extern u8 D_800A7454[];
extern s32 D_800A8EE4[];
extern s32 D_800A8FA8[];
extern s32 D_800A8F00[];
extern u32 D_800A8FF4[];
extern u16 D_800A900C;
extern u8 D_800AA244[];
extern s16 D_800AA2CC[];
extern s16 D_800A9850[];
extern u16 D_800A8FC4[];                /* per monster: its sound when chosen */
extern u16 D_8007C144[];
extern s16 D_800A92A0;                 /* the format question's state: 0 ask, 3 answer, 4 format */
extern u8 D_80098260[];                /* "YES" */
extern u8 D_80098264[];                /* "NO" */
void func_80018C14(void);
void menu_format_card(void);
extern s16 D_801FA958;
extern s16 D_800A9880;
s32 menu_find_used_slot(void);               /* the first used save slot, -1 for none */
void func_800A32CC(void);
s32 menu_list_saves(void);
extern TextMessage D_800A6400;
extern s16 D_800A9848;                 /* the delete question's answer: 0 yes, 1 no */
extern s16 D_801F9AB8;
extern s16 D_801D3778;
/* The controls screen (menu_draw_controls): per player, the button layout's pictures and labels. */
extern u16 *D_8007A7C0[];               /* the layouts: [4..7] the buttons 0x10, 0x20, 0x40, 0x80 */
extern TextMessage D_800A6718;
extern TextMessage D_800A6738;
extern TextMessage D_800A6758;
extern TextMessage D_800A6778;
extern s32 D_800A6F7C[4];
extern s16 D_800A6F8C[3];
extern s16 D_800A6F94[];
extern s16 D_800A6FAC[3];
extern s16 D_800A6FB4[4];
extern s16 D_800A6FBC[3];
extern s16 D_801E0D64;
void menu_load_slot(s32 slot);           /* loads a saved game from the save file's slot */
extern u16 D_801D883C;                 /* saved with the game (menu_write_save) */
extern s32 D_801E1CA8;
extern s16 D_801D8728;
s32 menu_find_save(s32 id);             /* the slot of a save number, -1 for none */                /* per player: the shift of its pad bits */
void main_set_frame(s32, u16, GameObject *);
extern MenuRecord D_800A6FCC[];
extern MenuRecord D_800A7014[];
extern MenuRecord D_800A7080[];
extern MenuRecord D_800A70A4[];
extern MenuRecord D_800A7104[];
extern MenuRecord D_800A714C[];
extern MenuRecord D_800A71A0[];
extern MenuRecord D_800A7200[];
extern MenuRecord D_800A7248[];
extern MenuRecord D_800A7284[];

extern s16 D_800A9888;                 /* the fade the objects' colours run (menu_update_fade): 1 to black, 2 to white */
extern u8 D_800A49D4[];
extern u8 D_800A49E4[];
extern u8 D_800A49FC[];
extern u8 D_800A4A14[];
extern u8 D_800A4470[];                /* the time line's message */
extern u8 D_800A4488[];                /* its text */

/* A saved game in the save file (0x74 bytes). */
typedef struct {
    /* 0x00 */ s16 unk_00;             /* the save's number: the newest is the largest */
    /* 0x02 */ s16 city;               /* an index into the city names D_8007C704 */
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ s16 unk_0A;              /* D_801E1CA8 */
    /* 0x0C */ u16 monster[3];         /* per player: the monster's number (menu_write_save) */
    /* 0x12 */ u16 unk_12[3];
    /* 0x18 */ s32 health[3];
    /* 0x24 */ s32 meter[3];
    /* 0x30 */ s32 unk_30[3];
    /* 0x3C */ u16 mode;               /* D_801D36FC */
    /* 0x3E */ u16 unk_3E;
    /* 0x40 */ u16 unk_40;
    /* 0x42 */ u16 unk_42;
    /* 0x44 */ u16 unk_44;
    /* 0x46 */ u8 unk_46[3];
    /* 0x49 */ u8 unk_49[7];           /* the number of non-zero entries is printed as "%dP" */
    /* 0x50 */ u16 unk_50[4];
    /* 0x58 */ u16 unk_58[7];
    /* 0x66 */ u16 unk_66;
    /* 0x68 */ u16 unk_68;
    /* 0x6A */ u16 unk_6A;
    /* 0x6C */ u16 unk_6C;
    /* 0x6E */ u16 unk_6E;
    /* 0x70 */ u16 unk_70;
    /* 0x72 */ u16 unk_72;
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
extern u8 D_800A6F39;                  /* frames before the title's next screen */
extern s16 D_800A92B8;                 /* the credits' next line */
extern s16 D_800A9298;                 /* frames to the credits' next line */
extern s16 D_800A90F4[];               /* per credits line: the frames to the next, -1 at the end */
extern u8 *D_800A9010[];               /* the credits' lines */
extern s16 D_800A9168[];               /* their colours */
extern OverattrPlacement D_800A40FC[4];
extern s16 D_800A92C8;                 /* the PRESS START blink */
extern OverattrPlacement D_800A7384[4];
extern TextMessage D_800897FC;
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

/* The monster selection screen (func_8009A238). */
void func_800180E4(void);               /* the SELECT button alone */
void func_8009F9E0(void);               /* the SELECT and BACK buttons */
extern s32 D_800A3450[3];               /* the three monsters offered (0-based numbers), a player's own replaced */
extern s32 D_800A436C[];                /* per monster: the selection cursor's sprite */
extern s32 D_800A43A4[];                /* its animation */
extern s32 D_800A43C0[];                /* its unk_74 */
extern s32 D_800A4388[];                /* per monster: its picture */
extern s16 D_800A40EC[];                /* per player slot: the cursor's x */
extern s16 D_800A40F4[];                /* and y */
extern OverattrPlacement D_800A3954[6];
extern s32 D_800A9208;                  /* the player slot choosing */
extern s16 D_800A9248;
extern s32 D_800A356C[];                /* per city: the time of day it starts at (func_80099B54) */
extern s32 D_800A9210;                  /* 1 while the previous monster slides out */
void func_8001D084(void);
void func_8001D17C(void);
void func_8001E758(void);
void func_8002497C(void);

/* The tour map (func_8009A708): the cities in groups of 25, each group a map of its own. */
void func_8001F6B4(void);
s32 func_8001EA78(void);                /* a random number */
extern s16 D_800A3760[];                /* per city: its x, y on the map */
extern OverattrPlacement D_800A39B4[16];  /* the maps' pictures */
extern OverattrPlacement D_800A3AB4[16];
extern OverattrPlacement D_800A3BB4[16];
extern OverattrPlacement D_800A3CB4[16];
extern OverattrPlacement D_800A3DB4[16];
extern OverattrPlacement D_800A3EB4[16];
extern OverattrPlacement D_800A3FB4[16];
extern OverattrPlacement D_800A40B4[2];  /* the current city's marker, a visited city's dot */
extern s32 D_800A43DC[];                /* per monster: its icon's sprite */
extern s32 D_800A43F8[];                /* its animation */
extern s32 D_800A4414[];                /* its unk_74 */

/* overattr_80099118.c */
GameObject *func_80099138(OverattrPlacement *p);
void menu_update_load_screen(void);
void menu_place_objects(OverattrPlacement *p, s32 n, s32 color);
void menu_set_colour(s32 kind, s32 value);
void menu_fade_others(void *list, s32 selected);
void menu_light_items(void *list, s32 selected, s32 lit, s32 normal);
void menu_fade_out(void);
void func_8009CE5C(void);
void func_8009D0B0(void);
void menu_check_card(void);
void menu_ask_format(void);
void menu_delete_save(void);
void menu_write_save(void);
void func_800A309C(void);

#endif /* OVERATTR_H */
