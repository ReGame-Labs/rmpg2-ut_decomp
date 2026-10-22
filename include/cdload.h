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
    /* 0x04 */ u8 unk_04[0x2];
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ u8 unk_08[0x4];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ Fixed32 unk_10;          /* a position, 16.16; its integer half is unk_10.h.i */
    /* 0x14 */ Fixed32 unk_14;
    /* 0x18 */ u8 unk_18[8];
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 *unk_28;
} Unk800AA248Node;

#endif /* CDLOAD_H */
