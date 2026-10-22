#ifndef PSYQ_LIBCD_H
#define PSYQ_LIBCD_H

/* libcd, as the game calls it (no SDK header is used: docs/CONTRIBUTING.md). */

#include "common.h"

typedef struct {
    u8 minute;
    u8 second;
    u8 sector;
    u8 track;
} CdlLOC;

/* CdControl commands used by the game. */
#define CdlSetloc 0x02
#define CdlSetmode 0x0E

/* CdSync / CdReadSync results. */
#define CdlComplete 0x02

#define CdlModeSpeed 0x80

s32 CdReset(s32 mode);
s32 CdControl(u8 com, u8 *param, u8 *result);
s32 CdSync(s32 mode, u8 *result);
s32 CdRead(s32 sectors, u32 *buf, s32 mode);
s32 CdReadSync(s32 mode, u8 *result);

#endif /* PSYQ_LIBCD_H */
