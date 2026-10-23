/* A piece of the game's own code between Psy-Q library objects: the sound driver on libspu (docs/TOOLCHAIN.md).
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"

extern u8 D_801FE0C4;
extern u8 D_801FE0CC;
extern u8 D_801FE0D0;
#include "sound.h"

extern s16 D_801FE0C8;

INCLUDE_ASM("asm/main/nonmatchings/game_80076C8C", func_80076C8C);

INCLUDE_ASM("asm/main/nonmatchings/game_80076C8C", func_80076D04);

void func_80076D3C(void) {
}

void func_80076D44(void) {
}

void func_80076D4C(void) {
}

void func_80076D54(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_80076C8C", func_80076D5C);

void func_80076F08(void) {
}

void func_80076F10(SoundChannel *ch) {
    u8 v;

    v = ch->unk_34[1];
    D_801FE0C4 = v;
    ch->unk_04 = v;
}

void func_80076F2C(void) {
}

void func_80076F34(SoundChannel *ch) {
    u8 *p;
    s16 v;

    p = ch->unk_34;
    v = p[1] | (p[2] << 8);
    D_801FE0C8 = v;
    ch->unk_06 = v;
}

void func_80076F5C(void) {
}

void func_80076F64(void) {
}

void func_80076F6C(SoundChannel *ch) {
    u8 v;

    v = ch->unk_34[1];
    D_801FE0CC = v;
    ch->unk_0D = v;
}

void func_80076F88(SoundChannel *ch) {
    u8 v;

    v = ch->unk_34[1];
    D_801FE0D0 = v;
    ch->unk_0E = v;
}

void func_80076FA4(void) {
}

void func_80076FAC(void) {
}

void func_80076FB4(void) {
}

void func_80076FBC(void) {
}

void func_80076FC4(void) {
}

extern SoundHandlerTable *D_80087FA0;
extern s32 D_8008716C;
extern u8 D_801FE0D4;
extern u8 D_801FE0D8;
extern SoundHandler *D_801FE0DC;

void func_80076FCC(SoundChannel *ch) {
    u8 *seq;
    s16 value;

    D_801FE0D8 = D_80087FA0->unk_09;
    if (D_801FE0D8 != 0) {
        D_801FE0DC = D_80087FA0->unk_10;
        D_801FE0D4 = D_8008716C;
        while (D_801FE0D4-- != 0) {
            if (D_801FE0DC->unk_00 != 0) {
                seq = ch->unk_34;
                if (D_801FE0DC->unk_01 == seq[1]) {
                    value = seq[2] | (seq[3] << 8);
                    D_801FE0DC->unk_02 = value;
                    D_801FE0DC->unk_04(D_801FE0DC->unk_01, value, D_801FE0DC);
                    return;
                }
                if (--D_801FE0D8 == 0) {
                    return;
                }
            }
            D_801FE0DC++;
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_80076C8C", func_800770E8);

INCLUDE_ASM("asm/main/nonmatchings/game_80076C8C", func_800771D4);

INCLUDE_ASM("asm/main/nonmatchings/game_80076C8C", func_800772C8);

INCLUDE_ASM("asm/main/nonmatchings/game_80076C8C", func_800773BC);

INCLUDE_ASM("asm/main/nonmatchings/game_80076C8C", func_800774B0);

INCLUDE_ASM("asm/main/nonmatchings/game_80076C8C", func_800774F4);

INCLUDE_ASM("asm/main/nonmatchings/game_80076C8C", func_80077670);

INCLUDE_ASM("asm/main/nonmatchings/game_80076C8C", func_80077848);

INCLUDE_ASM("asm/main/nonmatchings/game_80076C8C", func_800779E8);

INCLUDE_ASM("asm/main/nonmatchings/game_80076C8C", func_80077B2C);

s16 func_8007050C(void);
s32 func_80070588(s16, s16, s16);

void func_80077DC4(SoundChannel *ch) {
    u8 *p;

    p = ch->unk_34;
    ch->unk_16 = p[1] | (p[2] << 8);
    ch->unk_1C = func_80070588(func_8007050C(), ch->unk_14, ch->unk_16);
}

INCLUDE_ASM("asm/main/nonmatchings/game_80076C8C", func_80077E20);

INCLUDE_ASM("asm/main/nonmatchings/game_80076C8C", func_80077EBC);

u8 *func_80076C8C(s32, s32 *);

void func_80077F2C(SoundChannel *ch) {
    s32 *sp;
    s32 seq;

    sp = ch->unk_40;
    ch->unk_40 = sp - 1;
    seq = sp[-1];
    ch->unk_34 = (u8 *) seq;
    ch->unk_34 = func_80076C8C(seq, &ch->unk_08);
    ch->unk_08 = 0;
    ch->unk_00.w |= 0x40;
}

INCLUDE_ASM("asm/main/nonmatchings/game_80076C8C", func_80077F84);

void func_80078080(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_80076C8C", func_80078088);
