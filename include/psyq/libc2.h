#ifndef PSYQ_LIBC2_H
#define PSYQ_LIBC2_H

/* libc2, as the game calls it (no SDK header is used: docs/CONTRIBUTING.md). */

#include "common.h"

void *memcpy(void *dst, const void *src, u32 n);
void *memset(void *dst, int c, unsigned int n);

#endif /* PSYQ_LIBC2_H */
