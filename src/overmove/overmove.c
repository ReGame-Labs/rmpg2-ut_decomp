/* OVERLAYS/OVERMOVE.BIN: the movie player (libpress's MDEC decoding is in psyq/libpress/), loaded at 0x80097EA4 by
 * cdload_load_overlay(1); the executable calls func_800A9890 with a movie number. docs/DISC_LAYOUT.md "Overlays". */
#include "common.h"
#include "overmove.h"
#include "cdload.h"
#include "psyq/libcd.h"
#include "psyq/libetc.h"
#include "psyq/libgpu.h"
#include "psyq/libpress.h"
#include "psyq/libspu.h"

/* The executable's. */
void func_80018CD0(void);
void func_80018CF0(void);
void func_80018D38(void);
void func_80019ADC(s32 arg0);
void func_80063DF8(s32 volume);
void func_80063E48(s32 arg0, s32 volume);
extern s32 D_801FA9A4;
extern s16 D_801E1CB4;          /* the music volume */
extern u8 *D_801E1C78;          /* the file read buffer */
extern u32 D_801E0D7C;          /* the buttons pressed */
extern s32 D_801FCEC0;          /* libcd's StCdIntrFlag */

s32 overmove_play_stream(CdlLOC *loc, s32 movie);
void overmove_set_dec_env(MovieDecEnv *dec, s32 x0, s32 y0, s32 x1, s32 y1);
void overmove_init_stream(CdlLOC *loc, void (*callback)(void));
void overmove_slice_done(void);
void overmove_next_vlc(MovieDecEnv *dec);
u32 *overmove_next_frame(MovieDecEnv *dec);
void overmove_sync(MovieDecEnv *dec, s32 mode);
void overmove_kick_cd(CdlLOC *loc);

extern Movie overmove_movies[];
extern s32 overmove_width;          /* the movie's width and height */
extern s32 overmove_height;
extern MovieDecEnv overmove_dec;
extern u32 *overmove_ring;         /* the stream's ring buffer */
extern u32 *overmove_vlcbuf0;         /* the VLC buffers */
extern u32 *overmove_vlcbuf1;
extern u16 *overmove_imgbuf0;         /* the slice buffers */
extern u16 *overmove_imgbuf1;
extern s32 overmove_start_frame;          /* the first frame */
extern u32 overmove_end_frame;          /* the last frame */
extern s32 overmove_end_reached;          /* the last frame was read */
extern s16 overmove_frames;          /* frames shown */

/* Plays movie `movie`; returns 1 or 2 when a button skipped it, 0 otherwise. */
s32 func_800A9890(s32 movie) {
    s32 volume;
    s32 result;

    D_801FA9A4 = 0;
    func_80018CD0();
    func_80018CF0();
    func_80018CD0();
    func_80018CF0();
    volume = D_801E1CB4 << 8;
    if (volume >= 0x4000) {
        volume = 0x3FFF;
    }
    func_80063E48(0x7D, volume);
    overmove_start_frame = overmove_movies[movie].start;
    overmove_end_frame = overmove_movies[movie].end;
    overmove_ring = (u32 *)D_801E1C78;
    overmove_vlcbuf0 = (u32 *)(D_801E1C78 + 0x10000);
    overmove_vlcbuf1 = overmove_vlcbuf0 + 0xA000;
    overmove_imgbuf0 = (u16 *)(overmove_vlcbuf1 + 0xA000);
    overmove_imgbuf1 = overmove_imgbuf0 + 0x1680;
    if (overmove_end_frame != 0) {
        result = overmove_play_stream(&D_80089820[overmove_movies[movie].file], movie);
    } else {
        result = 0;
    }
    func_80063E48(0x7D, D_801E1CB4 << 7);
    SetDispMask(0);
    func_80018CD0();
    func_80018CF0();
    func_80018CD0();
    func_80018CF0();
    overmove_frames = 0;
    return result;
}

s32 overmove_play_stream(CdlLOC *loc, s32 movie) {
    DISPENV disp;
    DRAWENV draw;
    s32 result;
    s32 min;
    s32 shown;

    result = 0;
    func_80019ADC(1);
    SetDispMask(0);
    overmove_set_dec_env(&overmove_dec, 0, 0, 480, 0);
    overmove_init_stream(loc, overmove_slice_done);
    overmove_next_vlc(&overmove_dec);
    overmove_end_reached = 0;
    for (;;) {
        overmove_frames++;
        DecDCTin(overmove_dec.vlcbuf[overmove_dec.vlcid], 3);
        DecDCTout((u32 *)overmove_dec.imgbuf[overmove_dec.imgid], overmove_dec.slice.w * overmove_dec.slice.h / 2);
        overmove_next_vlc(&overmove_dec);
        overmove_sync(&overmove_dec, 0);
        VSync(0);
        shown = overmove_dec.rectid == 0;   /* the frame not being decoded into */
        SetDefDispEnv(&disp, shown * 480, 0, 480, 240);
        disp.disp.w = disp.disp.w * 2 / 3;
        disp.isrgb24 = 1;
        PutDispEnv(&disp);
        SetDispMask(1);
        func_80018D38();
        if (overmove_end_reached == 1) {
            result = 0;
            break;
        }
        if (movie == 0x1C || movie == 0x1A) {
            min = 120;
        } else {
            min = 50;
        }
        if (overmove_frames > min) {
            if ((D_801E0D7C & 0x10040100) && result == 0) {
                result = 1;
                break;
            }
            if ((D_801E0D7C & 0x01004010) && result == 0) {
                result = 2;
                break;
            }
        }
    }
    func_80063DF8(0);
    DecDCToutCallback(NULL);
    DecDCTReset(0);
    StUnSetRing();
    SpuSetMute(1);
    SetDispMask(0);
    CdControlB(CdlPause, NULL, NULL);
    ResetGraph(3);
    func_80019ADC(1);
    SpuSetMute(0);
    SetDispMask(1);
    return result;
}

void overmove_set_dec_env(MovieDecEnv *dec, s32 x0, s32 y0, s32 x1, s32 y1) {
    dec->vlcbuf[0] = overmove_vlcbuf0;
    dec->vlcbuf[1] = overmove_vlcbuf1;
    dec->vlcid = 0;
    dec->imgbuf[0] = overmove_imgbuf0;
    dec->imgbuf[1] = overmove_imgbuf1;
    dec->imgid = 0;
    dec->rect[0].x = x0;
    dec->rect[0].y = y0;
    dec->rect[1].x = x1;
    dec->rect[1].y = y1;
    dec->rectid = 0;
    dec->slice.x = x0;
    dec->slice.y = y0;
    dec->slice.w = 24;
    dec->isdone = 0;
}

void overmove_init_stream(CdlLOC *loc, void (*callback)(void)) {
    DecDCTReset(0);
    DecDCToutCallback(callback);
    StSetRing(overmove_ring, 32);
    StSetStream(1, overmove_start_frame, -1, NULL, NULL);
    overmove_kick_cd(loc);
}

/* The MDEC's slice-done callback: sends the slice to VRAM and starts the next one. */
void overmove_slice_done(void) {
    RECT snap;
    s32 id;

    if (D_801FCEC0 != 0) {
        StCdInterrupt();
        D_801FCEC0 = 0;
    }
    id = overmove_dec.imgid;
    snap = overmove_dec.slice;
    overmove_dec.imgid = overmove_dec.imgid ? 0 : 1;
    overmove_dec.slice.x += overmove_dec.slice.w;
    if (overmove_dec.slice.x < overmove_dec.rect[overmove_dec.rectid].x + overmove_dec.rect[overmove_dec.rectid].w) {
        DecDCTout((u32 *)overmove_dec.imgbuf[overmove_dec.imgid], overmove_dec.slice.w * overmove_dec.slice.h / 2);
    } else {
        overmove_dec.isdone = 1;
        overmove_dec.rectid = overmove_dec.rectid == 0;
        overmove_dec.slice.x = overmove_dec.rect[overmove_dec.rectid].x;
        overmove_dec.slice.y = overmove_dec.rect[overmove_dec.rectid].y;
    }
    LoadImage(&snap, (unsigned long *)overmove_dec.imgbuf[id]);
}

/* Decodes the next frame's bitstream into the other VLC buffer. */
void overmove_next_vlc(MovieDecEnv *dec) {
    s32 cnt;
    u32 *next;

    cnt = 0x800000;
    while ((next = overmove_next_frame(dec)) == NULL) {
        if (--cnt == 0) {
            return;
        }
    }
    dec->vlcid = dec->vlcid == 0;
    DecDCTvlc(next, dec->vlcbuf[dec->vlcid]);
    StFreeRing(next);
}

/* Waits for the next frame in the ring; clears the frame buffers when the size changes. */
u32 *overmove_next_frame(MovieDecEnv *dec) {
    RECT rect;
    u32 *addr;
    StHEADER *sector;
    s32 cnt;

    cnt = 0x800000;
    while (StGetNext(&addr, (u32 **)&sector)) {
        if (--cnt == 0) {
            return NULL;
        }
    }
    if (sector->frameCount >= overmove_end_frame) {
        overmove_end_reached = 1;
    }
    if (overmove_width != sector->width || overmove_height != sector->height) {
        rect.x = 0;
        rect.y = 0;
        rect.w = 960;
        rect.h = 240;
        ClearImage(&rect, 0, 0, 0);
        overmove_width = sector->width;
        overmove_height = sector->height;
    }
    dec->rect[0].w = dec->rect[1].w = overmove_width * 3 / 2;
    dec->rect[0].h = dec->rect[1].h = overmove_height;
    dec->slice.h = overmove_height;
    return addr;
}

/* Waits for the frame's last slice. */
void overmove_sync(MovieDecEnv *dec, s32 mode) {
    volatile s32 cnt = 0x800000;

    while (dec->isdone == 0) {
        if (--cnt == 0) {
            dec->isdone = 1;
            dec->rectid = dec->rectid == 0;
            dec->slice.x = dec->rect[dec->rectid].x;
            dec->slice.y = dec->rect[dec->rectid].y;
        }
    }
    dec->isdone = 0;
}

/* Seeks to the movie and starts streaming. */
void overmove_kick_cd(CdlLOC *loc) {
    SpuSetMute(0);
    do {
        while (CdControl(CdlSetloc, (u8 *)loc, NULL) == 0) {
        }
    } while (CdRead2(CdlModeStream | CdlModeSpeed | CdlModeRT) == 0);
}
