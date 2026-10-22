#ifndef PSYQ_LIBGPU_H
#define PSYQ_LIBGPU_H

/* Psy-Q libgpu types and functions the game uses, declared from the game's own code (no SDK header is used).
 * The structures follow the library's documented layout: DRAWENV is 0x5C bytes, DISPENV 0x14. */

typedef struct RECT {
    short x, y, w, h;
} RECT;

typedef struct DR_ENV {
    unsigned long tag;
    unsigned long code[15];
} DR_ENV;

typedef struct DRAWENV {
    RECT clip;
    RECT tw;
    short ofs[2];
    short tpage;
    char dtd;
    char dfe;
    unsigned char isbg;
    unsigned char r0, g0, b0;
    DR_ENV dr_env;
} DRAWENV;

typedef struct DISPENV {
    RECT disp;
    RECT screen;
    unsigned char isinter;
    unsigned char isrgb24;
    unsigned char pad0, pad1;
} DISPENV;

int ResetGraph(int mode);
int SetGraphDebug(int level);
int DrawSync(int mode);
unsigned int SetDispMask(int mask);
DRAWENV *PutDrawEnv(DRAWENV *env);
DISPENV *PutDispEnv(DISPENV *env);
int DrawOTag(unsigned long *p);
int ClearOTagR(unsigned long *ot, int n);
int LoadImage(RECT *rect, unsigned long *p);
int ClearImage(RECT *rect, unsigned char r, unsigned char g, unsigned char b);

#endif /* PSYQ_LIBGPU_H */
