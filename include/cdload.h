#ifndef CDLOAD_H
#define CDLOAD_H

/* The CD file reader and the overlay loader (src/main/cdload.c). Files are read by index into the file table
 * (docs/DISC_LAYOUT.md "The file table"), not by name. */

#include "common.h"
#include "psyq/libcd.h"
#include "entity.h"

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

#endif /* CDLOAD_H */
