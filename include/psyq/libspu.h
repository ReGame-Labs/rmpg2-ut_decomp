#ifndef PSYQ_LIBSPU_H
#define PSYQ_LIBSPU_H

/* libspu, as the game calls it (no SDK header is used: docs/CONTRIBUTING.md). */

#include "common.h"

#define SPU_TRANSFER_WAIT 1

u32 SpuSetTransferStartAddr(u32 addr);
u32 SpuWrite(u8 *addr, u32 size);
s32 SpuIsTransferCompleted(s32 flag);

#endif /* PSYQ_LIBSPU_H */
