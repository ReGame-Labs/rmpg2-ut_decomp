#ifndef PSYQ_LIBC_H
#define PSYQ_LIBC_H

/* Psy-Q libc2 functions the game calls, declared from the game's own code (no SDK header is used). */

void *memset(void *dst, int value, unsigned int size);
void *memcpy(void *dst, const void *src, unsigned int size);
unsigned int strlen(const char *s);
char *strcpy(char *dst, const char *src);
int strcmp(const char *a, const char *b);
char *strchr(const char *s, int c);
char *strcat(char *dst, const char *src);
int sprintf(char *dst, const char *fmt, ...);
int printf(const char *fmt, ...);

#endif /* PSYQ_LIBC_H */
