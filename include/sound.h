#ifndef SOUND_H
#define SOUND_H

/* The game's sound driver, WESS (wess.c, wess_seq.c, wess_spu.c and wess_trigger.c: the pieces linked between
 * the Psy-Q objects). It plays the disc's SOUND/RAMPAGE.WMD (the module: "SPSX", the sequences'
 * channel headers), RAMPAGE.WSD (the sequences: "SSEQ") and MAIN.LCD (the SPU samples) through libspu:
 * wess_seq.c is the sequencer (a command byte, its parameters, then a variable-length delay), wess.c the
 * SPU command set, the voice allocator, the loaders and the API, wess_spu.c the SPU's volumes and reverb,
 * wess_trigger.c the sequence trigger by type.
 * The types are by offset, from the matched functions. */

#include "common.h"

/* A voice record: a count at 0x05 and a state byte at 0x01 (func_8006BB60). */
typedef struct SoundVoice {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ s8 unk_01;
    /* 0x02 */ u8 unk_02[3];
    /* 0x05 */ u8 unk_05;
} SoundVoice;

/* A channel: the sequence pointer at 0x34, two s16 parameters read from it at 0x04 and 0x06. */
/* A word read whole and by bytes. */
typedef union SoundWord {
    s32 w;
    s16 h[2];
    u8 b[4];
} SoundWord;

typedef struct SoundChannel {
    /* 0x00 */ SoundWord unk_00;    /* flags (1 active, 2 muted, 4, 8 stopped, 0x10 timed, 0x20 looped, 0x40
                                     * position moved, 0x80 the sustain pedal); byte 1 the channel's index, byte 2
                                     * its sequence's slot, byte 3 its class (0 effects, 1 music) */
    /* 0x04 */ s16 unk_04;          /* set from a sequence byte (command 7) */
    /* 0x06 */ s16 unk_06;          /* set from a 16-bit sequence parameter (command 9) */
    /* 0x08 */ s32 delay;           /* the delay before the next command (a variable-length number) */
    /* 0x0C */ u8 unk_0C;
    /* 0x0D */ u8 unk_0D;           /* set from a sequence byte (command 12) */
    /* 0x0E */ u8 unk_0E;           /* set from a sequence byte (command 13) */
    /* 0x0F */ u8 unk_0F;
    /* 0x10 */ u8 cmd_set;          /* the command set (D_80087130[]) */
    /* 0x11 */ u8 unk_11;
    /* 0x12 */ u8 unk_12[0x2];
    /* 0x14 */ s16 ppq;             /* the pulses per quarter note (func_80070588) */
    /* 0x16 */ s16 tempo;           /* the quarter notes per minute, read from the sequence low byte first */
    /* 0x18 */ s16 label_count;     /* the number of labels */
    /* 0x1A */ u16 unk_1A;
    /* 0x1C */ s32 tick_step;       /* the time step per tick (func_80070588) */
    /* 0x20 */ u32 accum;           /* the time accumulator: 16.16 */
    /* 0x24 */ u32 delay_time;      /* the time elapsed towards delay */
    /* 0x28 */ u32 elapsed;         /* the time elapsed in all */
    /* 0x2C */ u32 end_time;        /* the end time when flag 0x10 is set */
    /* 0x30 */ u8 *seq_start;       /* the sequence's start */
    /* 0x34 */ u8 *seq;             /* the sequence pointer (func_80076C8C) */
    /* 0x38 */ s32 *labels;         /* the labels: offsets from seq_start */
    /* 0x3C */ u8 **stack_base;     /* the return stack's base, */
    /* 0x40 */ u8 **stack;          /* its pointer (popped by func_80077F2C), */
    /* 0x44 */ u8 **stack_end;      /* and its end */
    /* 0x48 */ s32 unk_48;
    /* 0x4C */ s32 unk_4C;
} SoundChannel;

struct SoundTrack;

/* A 16-byte slot of the driver's sequence table (SoundSeqTable.unk_20[]), one per sequence of the file. */
typedef struct SoundSlot {
    /* 0x00 */ u16 unk_00;          /* the number of channels (tracks) */
    /* 0x02 */ u8 method;           /* the packing method of its data, 0 none (func_800703D8) */
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ s32 unk_04;          /* the size of its data */
    /* 0x08 */ s32 unk_08;          /* its offset in the file, from the end of the table (D_801FDEB4) */
    /* 0x0C */ struct SoundTrack *unk_0C; /* its tracks once loaded (wess_read_sequence), NULL before */
} SoundSlot;

/* The module's header (the 32 bytes at the start of RAMPAGE.WMD, read into D_801FDEBC), then the sequence table. */
typedef struct SoundSeqTable {
    /* 0x00 */ s32 magic;           /* "SPSX" (D_8001709C) */
    /* 0x04 */ s32 version;         /* 2 */
    /* 0x08 */ u8 unk_08[0x10];
    /* 0x18 */ s32 unk_18;          /* the size of the data that follows the driver's tables (wess_module_size) */
    /* 0x1C */ u8 unk_1C[0x4];
    /* 0x20 */ SoundSlot *unk_20;
} SoundSeqTable;

typedef struct SoundDriver SoundDriver;

u8 *func_80076C8C(u8 *p, s32 *value);

/* The command handlers: D_80087F00[] the sequencer's own, indexed by a sequence's command byte; D_80087130[] one
 * table per command set (SoundChannel.cmd_set), the first being D_80087F00. Entry 1 takes the driver state, the
 * others a channel. */
typedef void (*SoundCmd)();
extern SoundCmd D_80087F00[];
extern SoundCmd *D_80087130[];

/* What a track points to (SoundTrack.unk_00): the channel's settings, copied in by wess_init_channel unless the
 * caller's SoundTrackOpts overrides them. */
typedef struct SoundTrackHeader {
    /* 0x00 */ u8 class;            /* the channel's class (its byte 3) */
    /* 0x01 */ u8 unk_01;           /* -> SoundChannel.unk_0C */
    /* 0x02 */ s16 unk_02;          /* -> unk_04 */
    /* 0x04 */ s16 unk_04;          /* -> unk_06 */
    /* 0x06 */ u8 unk_06;           /* -> unk_0D */
    /* 0x07 */ u8 unk_07;           /* -> unk_0E */
    /* 0x08 */ u8 unk_08;
    /* 0x09 */ u8 unk_09;           /* -> unk_0F */
    /* 0x0A */ s16 unk_0A;          /* -> ppq */
    /* 0x0C */ s16 unk_0C;          /* -> tempo */
    /* 0x0E */ u16 label_count;     /* -> label_count */
    /* 0x10 */ s32 data_size;       /* the sequence data's size */
} SoundTrackHeader;

/* A caller's overrides of a track's settings (wess_init_channel): a mask, then the values its bits select. */
typedef struct SoundTrackOpts {
    /* 0x00 */ s32 mask;            /* 1 unk_04, 2 unk_05, 4 unk_06, 8 unk_08, 0x10 mute by unk_0A, 0x20 unk_0C,
                                     * 0x40 a time limit unk_10, 0x80 looped, 0x100 unk_0B */
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ u8 unk_0B;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ u8 unk_0E[0x2];
    /* 0x10 */ s32 unk_10;
} SoundTrackOpts;

/* The second argument of wess_set_channel_data: a header, a word and the sequence's start. */
typedef struct SoundTrack {
    /* 0x00 */ SoundTrackHeader *unk_00;
    /* 0x04 */ s32 *unk_04;         /* the labels */
    /* 0x08 */ u8 *unk_08;          /* the sequence data */
} SoundTrack;

/* The sound bank's header (SoundDriver.unk_14): the counts of its four tables, packed one after the other from
 * unk_18 (each 8-aligned): patches (4 bytes), patch maps (SoundPatchmap), samples (SoundEntry), drum maps. */
typedef struct SoundBank {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s16 unk_04;          /* patches */
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;          /* patch maps */
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;          /* samples */
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s32 unk_10[2];
    /* 0x18 */ u8 *unk_18;
} SoundBank;

/* An 8-byte handler of the table SoundDriver.unk_10 points to: an id at 1 matched against the sequence's byte 1, a
 * 16-bit value at 2 and the function called with them. */
typedef struct SoundHandler {
    /* 0x00 */ u8 unk_00;           /* in use */
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ void (*unk_04)(u8, s16, struct SoundHandler *);
} SoundHandler;

/* A 0x18-byte sequence record (SoundDriver.unk_18[]), what a channel's byte 2 selects. */
typedef struct SoundSeqStat {
    /* 0x00 */ SoundWord unk_00;    /* flags (1 active); byte 1 cleared when its last channel stops; half 1 the
                                     * sequence's number (SoundSeqTable.unk_20[]) */
    /* 0x04 */ u8 unk_04;           /* channels allocated */
    /* 0x05 */ u8 unk_05;           /* channels playing */
    /* 0x06 */ u8 unk_06;           /* 0x80 at the start (wess_start_sequence) */
    /* 0x07 */ u8 unk_07;           /* 0x40 at the start */
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8 *unk_0C;          /* its channels' indices, 0xFF for a free entry */
    /* 0x10 */ u8 *unk_10;          /* per-sequence byte counters (commands 20, 22) */
    /* 0x14 */ u8 *unk_14;          /* more byte counters (commands 21, 23, 24) */
} SoundSeqStat;

/* The driver state (D_801FDF20; wess_get_driver returns it; D_80087FA0 is the sequencer's copy). */
struct SoundDriver {
    /* 0x00 */ u32 *unk_00;         /* the current time */
    /* 0x04 */ u8 unk_04;           /* sequences active */
    /* 0x05 */ u8 unk_05;           /* channels active */
    /* 0x06 */ u8 unk_06;           /* voices active */
    /* 0x07 */ u8 unk_07[0x2];
    /* 0x09 */ u8 unk_09;           /* the number of handlers in use */
    /* 0x0A */ u8 unk_0A;           /* the channel entries per sequence (SoundSeqStat.unk_0C) */
    /* 0x0B */ u8 unk_0B;
    /* 0x0C */ SoundSeqTable *unk_0C;
    /* 0x10 */ SoundHandler *unk_10;
    /* 0x14 */ SoundBank *unk_14;
    /* 0x18 */ SoundSeqStat *unk_18;
    /* 0x1C */ SoundChannel *unk_1C;
    /* 0x20 */ struct SoundNote *unk_20;
};

extern SoundDriver *D_801FDF20;

/* A patch map of the sound bank, 16 bytes: what a note of a patch plays (the voice's unk_08). */
typedef struct SoundPatchmap {
    /* 0x00 */ u8 unk_00;           /* the voice's priority */
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 volume;           /* 0..0x7F */
    /* 0x03 */ s8 pan;              /* added to the channel's pan, 0x40 the centre */
    /* 0x04 */ u8 root;             /* the sample's root note (SpuVoiceAttr.sample_note's high byte) */
    /* 0x05 */ u8 fine;             /* and its fine tuning (the low byte) */
    /* 0x06 */ u8 unk_06;           /* the lowest note it plays */
    /* 0x07 */ u8 unk_07;           /* the highest note */
    /* 0x08 */ s8 bend_down;        /* the pitch bend's range down, in semitones (wess_pitch_mod) */
    /* 0x09 */ s8 bend_up;          /* and up */
    /* 0x0A */ s16 unk_0A;          /* its sample (SoundEntry) */
    /* 0x0C */ u16 unk_0C;          /* the voice's ADSR word 1 (wess_start_voice) */
    /* 0x0E */ u16 unk_0E;          /* ADSR word 2; the release: bit 5 linear/exponential, bits 0-4 the rate */
} SoundPatchmap;

/* A patch of the sound bank, 4 bytes: a run of patch maps. */
typedef struct SoundPatch {
    /* 0x00 */ u8 unk_00;           /* the number of patch maps */
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ s16 unk_02;          /* the first one */
} SoundPatch;

/* A 0x14-byte voice record (D_801FDA78 holds D_801FDA7C of them): flags in the low bits of the first word (1 on,
 * 2 released), the SPU voice in its byte 2, the channel's index in its byte 3, the note at 5, the velocity at 6, a
 * held flag at 7 (the sustain pedal), the patch map at 8, the release's end time at 0x10. */
typedef struct SoundNote {
    /* 0x00 */ SoundWord unk_00;
    /* 0x04 */ u8 unk_04;           /* priority */
    /* 0x05 */ u8 unk_05;           /* note */
    /* 0x06 */ u8 unk_06;           /* velocity */
    /* 0x07 */ u8 unk_07;
    /* 0x08 */ SoundPatchmap *unk_08;
    /* 0x0C */ struct SoundEntry *unk_0C;
    /* 0x10 */ u32 unk_10;
} SoundNote;

/* A music note cut by a pause, to be played again (func_8006C084 records them in the queue D_80087100 points to,
 * func_8006BF80 replays them): the sequence, the channel, the note, the velocity, the patch map and the sample. */
typedef struct SoundEvent {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ u8 unk_06[0x2];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} SoundEvent;

typedef struct SoundEventQueue {
    /* 0x00 */ s32 unk_00;          /* the number of events */
    /* 0x04 */ s32 unk_04;          /* which notes are queued: 1 kind 1, 2 kind 0 */
    /* 0x08 */ SoundEvent unk_08[0x20];
} SoundEventQueue;

s32 wess_start_sequence(SoundSlot *slot, s32 n, s32 arg2, s32 arg3, SoundTrackOpts *opts);

/* A 12-byte record of the table at D_801FDA90 (the sound bank's entries?): a value at 4 and a slot at 8. */
typedef struct SoundEntry {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
} SoundEntry;

/* The 32-byte header of the sequence file (read by wess_sequence_header; "SSEQ" on the disc's RAMPAGE.WSD): a word at 0x18
 * the loader returns. */
typedef struct SoundFileHeader {
    /* 0x00 */ u8 unk_00[0x0E];
    /* 0x0E */ u16 count;           /* the number of sequences (D_801FDEA0, the bound wess_valid_sequence checks) */
    /* 0x10 */ u8 method;           /* the sequence table's packing method, 0 none (func_800703D8) */
    /* 0x11 */ u8 unk_11[0x03];
    /* 0x14 */ s32 packed_size;     /* the table's packed size */
    /* 0x18 */ s32 size;            /* its size */
    /* 0x1C */ s32 unk_1C;
} SoundFileHeader;

/* What the game hands func_800706C0 (cdload's cdload_init_sound fills one on the stack): the file access functions the
 * driver calls (cdload's stdio emulation), two tables copied into the driver and the timer's settings. The functions
 * are copied into the driver's own pointers (D_801FDF2C ...), which give their calls' types. */
typedef struct SoundInit {
    /* 0x00 */ s32 (*open)();
    /* 0x04 */ s32 (*read)();
    /* 0x08 */ s32 (*seek)();
    /* 0x0C */ s32 (*size)();
    /* 0x10 */ s32 (*close)();
    /* 0x14 */ s32 (*load_spu)();       /* uploads a file's samples to the SPU */
    /* 0x18 */ u8 *unk_18;          /* 0x80 bytes for func_8006BED0 */
    /* 0x1C */ u16 *unk_1C;         /* 0x80 halves for func_8006BF08 */
    /* 0x20 */ s32 rate;            /* the timer's ticks per second (func_800704E4) */
    /* 0x24 */ s32 unk_24;          /* the timer is installed when non-zero (func_800707BC) */
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
} SoundInit;

void func_800706C0(SoundInit *init);

extern s32 D_80087180;

#endif /* SOUND_H */
