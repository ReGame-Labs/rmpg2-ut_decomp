#ifndef SOUND_H
#define SOUND_H

/* The game's sound driver (the game_8006BB14, game_80076C8C, game_80063A88 and game_800633EC units: the pieces
 * linked between the Psy-Q objects). Provisional types, from the matched functions. */

#include "common.h"

/* A voice record: a count at 0x05 and a state byte at 0x01 (func_8006BB60). */
typedef struct SoundVoice {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ s8 unk_01;
    /* 0x02 */ u8 unk_02[3];
    /* 0x05 */ u8 unk_05;
} SoundVoice;

/* A channel: the sequence pointer at 0x34, two s16 parameters read from it at 0x04 and 0x06. */
typedef struct SoundChannel {
    /* 0x00 */ s32 unk_00;          /* flags; 0x40 */
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8 unk_0C;
    /* 0x0D */ u8 unk_0D;
    /* 0x0E */ u8 unk_0E;
    /* 0x0F */ u8 unk_0F[0x5];
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;          /* a 16-bit parameter read from the sequence, low byte first */
    /* 0x18 */ u8 unk_18[0x2];
    /* 0x1A */ u16 unk_1A;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ u8 unk_20[0x10];
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ u8 *unk_34;          /* the sequence pointer (func_80076C8C) */
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ u8 unk_3C[0x4];
    /* 0x40 */ s32 *unk_40;         /* a return stack: popped by func_80077F2C */
    /* 0x44 */ u8 unk_44[0x8];
    /* 0x4C */ s32 unk_4C;
} SoundChannel;

/* A 16-byte slot of the driver's sequence table (SoundSeqTable.unk_20[]): a sequence pointer at 0x0C. */
typedef struct SoundSlot {
    /* 0x00 */ u8 unk_00[0xC];
    /* 0x0C */ s32 unk_0C;
} SoundSlot;

typedef struct SoundSeqTable {
    /* 0x00 */ u8 unk_00[0x20];
    /* 0x20 */ SoundSlot *unk_20;
} SoundSeqTable;

/* The driver state D_801FDF20 points to (func_8006EC08 returns it). */
typedef struct SoundDriver {
    /* 0x00 */ u8 unk_00[0xC];
    /* 0x0C */ SoundSeqTable *unk_0C;
} SoundDriver;

extern SoundDriver *D_801FDF20;

/* A pair of driver hooks (D_80087130, D_80087134): a function at 4 called with the driver state. */
typedef struct SoundHooks {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ void (*unk_04)(SoundDriver *);
} SoundHooks;

/* What a track points to (SoundTrack.unk_00): a u16 at 0x0E and a word at 0x10 copied into the channel. */
typedef struct SoundTrackHeader {
    /* 0x00 */ u8 unk_00[0xE];
    /* 0x0E */ u16 unk_0E;
    /* 0x10 */ s32 unk_10;
} SoundTrackHeader;

/* The second argument of func_8006F8F8: a header, a word and the sequence's start. */
typedef struct SoundTrack {
    /* 0x00 */ SoundTrackHeader *unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
} SoundTrack;

void func_8006F96C(SoundSlot *slot, s32 n, s32 arg2, s32 arg3, s32 arg4);

/* A 12-byte record of the table at D_801FDA90 (the sound bank's entries?): a value at 4 and a slot at 8. */
typedef struct SoundEntry {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
} SoundEntry;

#endif /* SOUND_H */
