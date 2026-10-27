#ifndef CDLOAD_H
#define CDLOAD_H

/* The CD file reader and the overlay loader (src/main/cdload.c). Files are read by index into the file table
 * (docs/DISC_LAYOUT.md "The file table"), not by name. */

#include "common.h"
#include "psyq/libcd.h"
#include "game.h"

/* The file table: a CdlLOC, a size and a checksum (the exclusive-or of the words) per file, in disc order. */
extern CdlLOC D_80089820[];
extern s32 D_80089DA0[];
extern s32 D_80010000[];
extern u8 *D_801E1C78;                  /* the file read buffer */

#endif /* CDLOAD_H */
