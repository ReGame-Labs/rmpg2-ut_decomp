#ifndef PSYQ_LIBC2_H
#define PSYQ_LIBC2_H

/* libc2, as the game calls it (no SDK header is used: docs/CONTRIBUTING.md). Every C library function the game
 * links comes from libc2 (config/main.yaml). */

#include "common.h"

void *memcpy(void *dst, const void *src, u32 n);
void *memset(void *dst, int c, unsigned int n);
unsigned int strlen(const char *s);
char *strcpy(char *dst, const char *src);
int strcmp(const char *a, const char *b);
char *strchr(const char *s, int c);
char *strcat(char *dst, const char *src);
int sprintf(char *dst, const char *fmt, ...);
int printf(const char *fmt, ...);

#endif /* PSYQ_LIBC2_H */
