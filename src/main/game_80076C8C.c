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

INCLUDE_ASM("asm/main/nonmatchings/game_80076C8C", func_80076FCC);

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

INCLUDE_ASM("asm/main/nonmatchings/game_80076C8C", func_80077DC4);

INCLUDE_ASM("asm/main/nonmatchings/game_80076C8C", func_80077E20);

INCLUDE_ASM("asm/main/nonmatchings/game_80076C8C", func_80077EBC);

INCLUDE_ASM("asm/main/nonmatchings/game_80076C8C", func_80077F2C);

INCLUDE_ASM("asm/main/nonmatchings/game_80076C8C", func_80077F84);

void func_80078080(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_80076C8C", func_80078088);
