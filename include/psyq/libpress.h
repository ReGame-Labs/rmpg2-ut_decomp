#ifndef PSYQ_LIBPRESS_H
#define PSYQ_LIBPRESS_H

/* libpress (the MDEC movie decoder), as the movie player calls it; linked into OVERMOVE.BIN. */

#include "common.h"

void DecDCTReset(s32 mode);
void DecDCTin(u32 *buf, s32 mode);
void DecDCTout(u32 *buf, s32 size);
s32 DecDCToutCallback(void (*func)(void));
s32 DecDCTvlc(u32 *bs, u32 *buf);

#endif /* PSYQ_LIBPRESS_H */
