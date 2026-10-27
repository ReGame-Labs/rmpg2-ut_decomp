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

/* Appended for the movie player (overmove). */
void SetDefDispEnv(DISPENV *env, int x, int y, int w, int h);

/* Appended for the frame's draw lists (main). */
void AddPrim(void *ot, void *p);
unsigned short GetClut(int x, int y);
unsigned short GetTPage(int tp, int abr, int x, int y);

/* Appended for the frame's buffers (main.c main_init_system): the flat and gouraud quads and the tag macros. */
typedef struct P_TAG {
    unsigned addr: 24;
    unsigned len: 8;
    unsigned char r0, g0, b0, code;
} P_TAG;

typedef struct POLY_F4 {
    unsigned long tag;
    unsigned char r0, g0, b0, code;
    short x0, y0;
    short x1, y1;
    short x2, y2;
    short x3, y3;
} POLY_F4;

typedef struct POLY_G4 {
    unsigned long tag;
    unsigned char r0, g0, b0, code;
    short x0, y0;
    unsigned char r1, g1, b1, pad1;
    short x1, y1;
    unsigned char r2, g2, b2, pad2;
    short x2, y2;
    unsigned char r3, g3, b3, pad3;
    short x3, y3;
} POLY_G4;

#define setlen(p, _len) (((P_TAG *) (p))->len = (unsigned char) (_len))
#define setcode(p, _code) (((P_TAG *) (p))->code = (unsigned char) (_code))
#define setRGB0(p, _r0, _g0, _b0) ((p)->r0 = (_r0), (p)->g0 = (_g0), (p)->b0 = (_b0))
#define SetPolyF4(p) setlen(p, 5), setcode(p, 0x28)
#define SetPolyG4(p) setlen(p, 8), setcode(p, 0x38)

DRAWENV *SetDefDrawEnv(DRAWENV *env, int x, int y, int w, int h);

#endif /* PSYQ_LIBGPU_H */
