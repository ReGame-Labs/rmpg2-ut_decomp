#ifndef CDLOAD_H
#define CDLOAD_H

/* The CD file reader and the overlay loader (src/main/cdload.c). Files are read by index into the file table
 * (docs/DISC_LAYOUT.md "The file table"), not by name. */

#include "common.h"
#include "psyq/libcd.h"

/* The file table: a CdlLOC, a size and a checksum (the exclusive-or of the words) per file, in disc order. */
extern CdlLOC D_80089820[];
extern s32 D_80089DA0[];
extern s32 D_80010000[];

/* The object func_8001D110 allocates (a display-list node?); only the fields cdload touches are known. */
typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0xE];
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ u8 unk_18[8];
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 *unk_28;
} Unk800AA248Node;

/* The global at 0x800AA248 (a struct, not a pointer). */
typedef struct {
    /* 0x00 */ u8 unk_00[0x20];
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ u8 unk_24[0x18];
    /* 0x3C */ Unk800AA248Node *unk_3C;
} Unk800AA248;

extern Unk800AA248 D_800AA248;

/* What the pointer at 0x800AA268 points to (the game's main state?); only the fields cdload touches are known. */
typedef struct {
    /* 0x00 */ u8 unk_00[0x12];
    /* 0x12 */ s16 unk_12;
} Unk800AA268Sub90;

typedef struct {
    /* 0x00 */ u8 unk_00[0x18];
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ u8 unk_1C[0x40];
    /* 0x5C */ u16 *unk_5C;
    /* 0x60 */ u8 unk_60[0x20];
    /* 0x80 */ u16 unk_80;
    /* 0x82 */ u8 unk_82[0xE];
    /* 0x90 */ Unk800AA268Sub90 *unk_90;
} Unk800AA268;

extern Unk800AA268 *D_800AA268;

#endif /* CDLOAD_H */
