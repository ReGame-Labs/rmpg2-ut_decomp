#ifndef PSYQ_LIBGTE_H
#define PSYQ_LIBGTE_H

/* Psy-Q libgte functions the game uses, declared from the game's own code (no SDK header is used). */

void InitGeom(void);
void SetGeomScreen(long h);

/* Appended for the object drawer (main.c func_8001F9DC): angles in 4096ths of a turn, results 4096 = 1.0. */
int ratan2(int y, int x);
int rcos(int a);
int rsin(int a);

#endif /* PSYQ_LIBGTE_H */
