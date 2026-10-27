#ifndef PSYQ_LIBSPU_H
#define PSYQ_LIBSPU_H

/* libspu, as the game calls it (no SDK header is used: docs/CONTRIBUTING.md). */

#include "common.h"

#define SPU_TRANSFER_WAIT 1

u32 SpuSetTransferStartAddr(u32 addr);
u32 SpuWrite(u8 *addr, u32 size);
s32 SpuIsTransferCompleted(s32 flag);
void SpuSetKey(s32 on_off, u32 voice_bit);
void SpuQuit(void);

/* The attribute blocks the sound driver fills (field offsets from its stack frames). */
typedef struct SpuVolume {
    s16 left;
    s16 right;
} SpuVolume;

typedef struct SpuExtAttr {
    SpuVolume volume;
    s32 reverb;
    s32 mix;
} SpuExtAttr;

typedef struct SpuCommonAttr {
    u32 mask;
    SpuVolume mvol;
    SpuVolume mvolmode;
    SpuVolume mvolx;
    SpuExtAttr cd;
    SpuExtAttr ext;
} SpuCommonAttr;

#define SPU_COMMON_MVOLL (1 << 0)
#define SPU_COMMON_MVOLR (1 << 1)
#define SPU_COMMON_CDVOLL (1 << 6)
#define SPU_COMMON_CDVOLR (1 << 7)
#define SPU_COMMON_CDREV (1 << 8)
#define SPU_COMMON_CDMIX (1 << 9)

typedef struct SpuReverbAttr {
    u32 mask;
    s32 mode;
    SpuVolume depth;
    s32 delay;
    s32 feedback;
} SpuReverbAttr;

void SpuInit(void);
s32 SpuInitMalloc(s32 num, char *top);
void SpuSetTransferMode(s32 mode);
void SpuSetCommonAttr(SpuCommonAttr *attr);
s32 SpuSetReverbModeParam(SpuReverbAttr *attr);
void SpuSetReverbDepth(SpuReverbAttr *attr);
s32 SpuSetReverb(s32 on_off);

#endif /* PSYQ_LIBSPU_H */
