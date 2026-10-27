#ifndef VIBRATE_H
#define VIBRATE_H

/* The controllers' vibration (src/main/vibrate.c): one record per pad port, run once a frame by
 * func_80063744, which pulses the motor byte of the port's PadSetAct buffer (D_801C51C8) by a duty cycle. */

#include "common.h"
#include "game.h"

/* A vibration request (func_800638B0): the ports it is for, the ramps, the strength and the duration. */
typedef struct {
    /* 0x00 */ u32 ports;           /* bit n: port n */
    /* 0x04 */ s32 ramp_up;         /* nonzero: from zero up to the level */
    /* 0x08 */ s32 ramp_down;       /* nonzero: from the level down to zero */
    /* 0x0C */ u32 level;           /* the duty cycle, 0x40 = always on */
    /* 0x10 */ u32 time;            /* frames */
    /* 0x14 */ s32 unk_14;
} RumbleRequest;

/* A port's vibration state (D_801FB4C4[3]). */
typedef struct {
    /* 0x00 */ s32 active;
    /* 0x04 */ s32 motor_on;        /* the motor byte is set */
    /* 0x08 */ s32 ramp_up;
    /* 0x0C */ s32 ramp_down;
    /* 0x10 */ u32 level;           /* the current duty cycle */
    /* 0x14 */ u32 target;          /* the requested one */
    /* 0x18 */ u32 step;            /* the ramps' step per frame */
    /* 0x1C */ u32 time;            /* frames left */
    /* 0x20 */ u32 duty;            /* the duty-cycle accumulator: the motor runs on each carry past 0x40 */
} Rumble;

/* A strength and a duration (D_80085308[8]: the presets by number). */
typedef struct {
    /* 0x00 */ s16 level;
    /* 0x02 */ s16 time;
} RumblePreset;

/* The vibration of a monster's animation-script position (D_80085328[19]): per monster id (1-based), the script
 * address that triggers it. */
typedef struct {
    /* 0x00 */ s32 *pcs;
    /* 0x04 */ RumblePreset preset;
} RumbleCue;

#endif /* VIBRATE_H */
