#ifndef OVERMOVE_H
#define OVERMOVE_H

/* The movie player in OVERLAYS/OVERMOVE.BIN (src/overmove/overmove.c): the shape of the Psy-Q movie sample, the
 * frames decoded by the MDEC in 24-bit slices into two frame buffers side by side. The decoder's fields keep the
 * sample's names. */

#include "common.h"
#include "psyq/libgpu.h"

/* The decoding state (overmove_dec): two VLC buffers, two slice buffers, the two frame rectangles in VRAM and the
 * slice being decoded. */
typedef struct {
    /* 0x00 */ u32 *vlcbuf[2];
    /* 0x08 */ s32 vlcid;
    /* 0x0C */ u16 *imgbuf[2];
    /* 0x14 */ s32 imgid;
    /* 0x18 */ RECT rect[2];
    /* 0x28 */ s32 rectid;
    /* 0x2C */ RECT slice;
    /* 0x34 */ s32 isdone;
} MovieDecEnv;

/* A movie (overmove_movies[], by movie number): its file, its first and last frame; no last frame: none. */
typedef struct {
    /* 0x00 */ s32 file;
    /* 0x04 */ s16 start;
    /* 0x06 */ s16 end;
} Movie;

#endif /* OVERMOVE_H */
