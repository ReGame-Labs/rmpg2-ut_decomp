/* The sound driver WESS, its SPU layer on libspu: the SPU and reverb setup, the master and CD volumes and their fades
 * (docs/TOOLCHAIN.md "The sound driver: GCC 2.7.2").
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "sound.h"
#include "psyq/libspu.h"

void func_80063C7C(s16);
void func_80063CC0(s16);
void func_80063DF8(s32 v);
void func_80063F48(s32 v);
s32 func_80063F98(void);
u16 func_8007050C(void);

extern s32 D_800853C0;
extern SpuReverbAttr D_801FB530;
extern char D_801FB544[];

extern s32 D_800853C4;
extern s32 D_800853D0;
extern s32 D_800853D4;
extern s32 D_800853E0;
extern s32 D_800853E8;

extern s32 D_800853CC;
extern s32 D_800853E4;

void func_80063A88(s32 mode, s16 depth_left, s16 depth_right, s32 delay, s32 feedback) {
    s32 vol;
    s32 i;

    D_800853C4 = 0;
    vol = func_80063F98();
    for (i = vol; i >= 0; i--) {
        func_80063F48(i);
    }
    D_801FB530.mask = 0x1F;
    D_801FB530.mode = mode;
    D_801FB530.depth.left = depth_left;
    D_801FB530.depth.right = depth_right;
    D_801FB530.delay = delay;
    D_801FB530.feedback = feedback;
    SpuSetReverbModeParam(&D_801FB530);
    SpuSetReverbDepth(&D_801FB530);
    if (mode == 0) {
        SpuSetReverb(0);
    } else {
        SpuSetReverb(1);
    }
    for (i = 0; i < 20000; i++) {
    }
    for (i = 0; i <= vol; i++) {
        func_80063F48(i);
    }
    D_800853C4 = 1;
}

void func_80063BB0(void) {
    SpuCommonAttr attr;

    if (D_800853C0 == 0) {
        D_800853C4 = 0;
        func_80063F48(0);
        func_80063DF8(0);
        SpuInit();
        D_800853C0 = 1;
        SpuInitMalloc(1, D_801FB544);
        SpuSetTransferMode(0);
        func_80063A88(0, 0, 0, 0, 0);
        attr.mask = SPU_COMMON_MVOLL | SPU_COMMON_MVOLR | SPU_COMMON_CDVOLL | SPU_COMMON_CDVOLR | SPU_COMMON_CDREV |
                    SPU_COMMON_CDMIX;
        attr.mvol.left = 0x3FFF;
        attr.mvol.right = 0x3FFF;
        attr.cd.volume.left = 0x3CFF;
        attr.cd.volume.right = 0x3CFF;
        attr.cd.reverb = 0;
        attr.cd.mix = 1;
        SpuSetCommonAttr(&attr);
        func_80063F48(0x3FFF);
        func_80063DF8(0x3CFF);
        D_800853C4 = 1;
    }
}

void func_80063C7C(s16 vol) {
    SpuCommonAttr attr;

    D_800853C4 = 0;
    attr.mvol.left = vol;
    attr.mvol.right = vol;
    attr.mask = SPU_COMMON_MVOLL | SPU_COMMON_MVOLR;
    SpuSetCommonAttr(&attr);
    D_800853C4 = 1;
}

void func_80063CC0(s16 vol) {
    SpuCommonAttr attr;

    D_800853C4 = 0;
    attr.cd.volume.left = vol;
    attr.cd.volume.right = vol;
    attr.mask = SPU_COMMON_CDVOLL | SPU_COMMON_CDVOLR;
    SpuSetCommonAttr(&attr);
    D_800853C4 = 1;
}

extern s16 D_800853D6;
extern s32 D_800853D8;
extern s32 D_800853DC;
extern s16 D_800853EA;
extern s32 D_800853EC;
extern s32 D_800853F0;

void func_80063D04(void) {
    if (D_800853C4 != 0) {
        if (D_800853E4 > 0) {
            D_800853E4--;
            D_800853E8 += D_800853F0;
            if (D_800853E4 == 0) {
                D_800853E8 = D_800853EC;
            }
            D_800853E0 = D_800853EA;
            func_80063CC0(D_800853EA);
        }
        if (D_800853D0 > 0) {
            D_800853D0--;
            D_800853D4 += D_800853DC;
            if (D_800853D0 == 0) {
                D_800853D4 = D_800853D8;
            }
            D_800853CC = D_800853D6;
            func_80063C7C(D_800853D6);
        }
    }
}

void func_80063DF8(s32 v) {
    D_800853E0 = v;
    D_800853E8 = v << 16;
    D_800853C4 = 0;
    D_800853E4 = 0;
    func_80063CC0(v);
    D_800853C4 = 1;
}

void func_80063E48(s32 msec, s32 dest) {
    D_800853C4 = 0;
    if (D_80087180 != 0) {
        D_800853E4 = msec * func_8007050C() / 1000 + 1;
        D_800853EC = dest << 16;
        D_800853F0 = (D_800853EC - D_800853E8) / D_800853E4;
    } else {
        D_800853E4 = 0;
    }
    D_800853C4 = 1;
}

s32 func_80063F30(void) {
    return D_800853E4 >= 2;
}

void func_80063F48(s32 v) {
    D_800853CC = v;
    D_800853D4 = v << 16;
    D_800853C4 = 0;
    D_800853D0 = 0;
    func_80063C7C(v);
    D_800853C4 = 1;
}

s32 func_80063F98(void) {
    return D_800853CC;
}
