#ifndef PSYQ_LIBETC_H
#define PSYQ_LIBETC_H

/* Psy-Q libetc functions the game calls, declared from the game's own code (no SDK header is used). */

int VSync(int mode);
int ResetCallback(void);
int VSyncCallback(void (*f)(void));

#endif /* PSYQ_LIBETC_H */
