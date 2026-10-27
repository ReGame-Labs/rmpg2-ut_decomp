#ifndef GAME_H
#define GAME_H

/* The game's shared types: one declaration per record, its fields named where the code shows their meaning and
 * unk_<offset> otherwise. Types local to one file stay in that file or its group's header. */

#include "common.h"

/* A 16.16 fixed-point value (positions, velocities), read whole or by its halves: the fraction at +0, the integer
 * part at +2 (little-endian), signed or unsigned as the code needs. */
typedef union Fixed {
    s32 w;
    struct {
        s16 lo;
        s16 hi;
    } s;
    struct {
        u16 lo;
        u16 hi;
    } u;
} Fixed;

#endif /* GAME_H */
