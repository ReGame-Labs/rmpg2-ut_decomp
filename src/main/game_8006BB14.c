/* A piece of the game's own code between Psy-Q library objects: the sound driver on libspu (docs/TOOLCHAIN.md).
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "sound.h"
#include "psyq/libapi.h"
#include "psyq/libspu.h"

void func_80063BB0(void);
void func_8006FED8(s32, s32);
s32 func_80070868(s32);
void func_8007043C();
void func_8007051C(void);
s32 func_8007078C(s32);
long func_8007062C();
void func_800708EC();
void func_800707BC(void);
void func_8006ECD8(void);
void func_80070414(void);
void func_80070444(void);
void func_800700A8(void);
void func_8006ED5C(void);
void func_8006E4BC(s32);
u16 func_8007050C(void);

extern s32 D_80087100;
extern s32 D_80087104;
extern s32 D_80087118;
extern s32 D_8008711C;
extern s32 (*D_80087128)(s32, s32);
extern s32 D_8008712C;
extern s32 D_80087178;
extern s32 D_80087180;
extern s32 D_80087190;
extern s32 D_80087198;
extern s32 D_8008719C;
extern u8 D_801FDA1C;
extern SoundEntry *D_801FDA90;
extern s32 D_801FDE9C;
extern s32 D_801FDEA4;
extern s32 (*D_801FDEA8)(s32, s32);
extern s32 D_801FDEAC;
extern s32 D_801FDEB0;
extern s32 (*D_801FDF34)();
extern s32 (*D_801FDF3C)();

extern s32 D_800870F4;
extern s32 D_8008710C;
extern s32 D_80087110;
extern s16 D_8008718C;
extern s16 D_801FD9C0;
extern s32 D_801FDEA0;
extern s32 D_801FDF24;

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006BB14);

void func_8006BB60(s32 *flags, SoundVoice *v) {
    s32 f;
    u8 n;

    f = *flags;
    if (!(f & 8)) {
        *flags = f | 0xA;
        n = v->unk_05 - 1;
        v->unk_05 = n;
        if (n == 0) {
            v->unk_01 = 0;
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006BBA0);

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006BD60);

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006BED0);

extern s32 D_800870FC;
extern u16 D_801FDB58[];

void func_8006BF08(u16 *src) {
    s32 i;
    u16 *dst;

    for (i = 0, dst = D_801FDB58; i < 0x80; i++) {
        *dst = *src;
        src++;
        dst++;
    }
    D_800870FC = 1;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006BF44);

void func_8006BF70(void) {
    D_80087100 = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006BF80);

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006C084);

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006C19C);

s32 func_8006C1F4(void) {
    return D_800870F4;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006C204);

s32 func_8006C8B4(s32 n) {
    return D_801FDA90[n].unk_04;
}

void func_8006C8D8(s32 n, s32 v) {
    D_801FDA90[n].unk_08 = v;
}

s32 func_8006C8F8(s32 n) {
    return D_801FDA90[n].unk_08;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006C91C);

void func_8006CA44(void) {
    SpuQuit();
}

void func_8006CA64(s32 bits) {
    D_80087104 |= bits;
}

void func_8006CA84(void) {
    if (D_80087104 != 0) {
        SpuSetKey(0, D_80087104);
        D_80087104 = 0;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006CAB8);

void func_8006CCBC(void) {
}

void func_8006CCC4(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006CCCC);

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006CD78);

void func_8006CEE4(SoundChannel *ch) {
    u8 *p;
    s16 v;

    p = ch->unk_34;
    v = p[1] | (p[2] << 8);
    D_801FD9C0 = v;
    ch->unk_04 = v;
}

void func_8006CF0C(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006CF14);

void func_8006D17C(void) {
}

void func_8006D184(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006D18C);

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006D6E4);

extern u8 D_801FDA10;
extern u8 D_801FDA14;
extern SoundNote *D_801FDA18;
extern SoundNote *D_801FDA78;
extern s32 D_801FDA7C;
void func_8006DF68(SoundNote *);

void func_8006DBC0(SoundChannel *ch) {
    u8 n;

    if (ch->unk_34[1] == 0) {
        n = ch->unk_11;
        ch->unk_00.w |= 0x80;
        D_801FDA10 = n;
        if (n != 0) {
            D_801FDA18 = D_801FDA78;
            D_801FDA14 = D_801FDA7C;
            while (D_801FDA14-- != 0) {
                if ((D_801FDA18->unk_00.w & 3) == 1 && D_801FDA18->unk_00.b[3] == ch->unk_00.b[1]
                    && D_801FDA18->unk_07 != 0) {
                    D_801FDA18->unk_07 = 0;
                    func_8006DF68(D_801FDA18);
                    if (--D_801FDA10 == 0) {
                        return;
                    }
                }
                D_801FDA18++;
            }
        }
    } else {
        ch->unk_00.w &= ~0x80;
    }
}

void func_8006DD10(SoundChannel *ch) {
    u8 v;

    v = ch->unk_34[1];
    D_801FDA1C = v;
    if (ch->unk_0C != v) {
        ch->unk_0C = v;
    }
}

void func_8006DD40(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006DD48);

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006DDE4);

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006DEAC);

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006DF68);

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006E014);

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006E244);

extern s32 D_801FDA64;
extern SoundNote *D_801FDA68;

void func_8006E3B8(SoundChannel *ch) {
    D_801FDA68 = D_801FDA78;
    D_801FDA64 = D_801FDA7C;
    while (--D_801FDA64 != -1) {
        if ((D_801FDA68->unk_00.w & 3) == 1 && D_801FDA68->unk_05 == ch->unk_34[1]
            && D_801FDA68->unk_00.b[3] == ch->unk_00.b[1]) {
            if (ch->unk_00.w & 0x80) {
                func_8006DF68(D_801FDA68);
            } else {
                D_801FDA68->unk_07 = 1;
            }
        }
        D_801FDA68++;
    }
}

void func_8006E4BC(s32 arg0) {
    if (D_801FDEA8 != NULL) {
        D_801FDEA8(D_801FDEAC, arg0);
    }
}

s32 func_8006E4F4(void) {
    return D_801FDEA0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006E504);

s32 func_8006E530(void) {
    if (D_801FDEA4 == 0) {
        D_801FDEB0 = func_80070868(D_801FDE9C);
        if (D_801FDEB0 == 0) {
            func_8006E4BC(1);
            return 0;
        }
    }
    D_801FDEA4++;
    return 1;
}

void func_8006E59C(void) {
    if (D_801FDEA4 == 1) {
        func_800708EC(D_801FDEB0);
    }
    if (D_801FDEA4 > 0) {
        D_801FDEA4--;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006E5F0);

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006E804);

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006E8B4);

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006EA50);

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006EB08);

void func_8006EBA4(s32 arg0) {
    if (D_80087128 != NULL) {
        D_80087128(D_8008712C, arg0);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006EBDC);

SoundDriver *func_8006EC08(void) {
    return D_801FDF20;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006EC18);

s32 func_8006EC48(void) {
    return D_8008710C != 0;
}

s32 func_8006EC58(void) {
    return D_80087110 != 0;
}

s32 func_8006EC68(s32 n) {
    if (n < 0 || n >= func_8006E4F4()) {
        return 0;
    }
    return D_801FDF20->unk_0C->unk_20[n].unk_0C != 0;
}

void func_8006ECD8(void) {
    func_800707BC();
}

s32 func_8006ECF8(void) {
    s32 r;

    r = 0;
    if (D_8008710C == 0) {
        func_80070444();
        if (D_80087180 == 0) {
            func_8006ECD8();
        }
        func_80070414();
        D_8008710C = 1;
        r = 1;
    }
    return r;
}

void func_8006ED5C(void) {
    if (D_80087118 != 0) {
        if (D_8008711C != 0) {
            func_8007043C(D_8008711C);
            D_8008711C = 0;
        }
        D_80087118 = 0;
    }
}

extern SoundHooks *D_80087130;
extern SoundHooks *D_80087134;

void func_8006EDAC(void) {
    if (D_80087110 != 0) {
        func_800700A8();
        func_80070444();
        D_80087130->unk_04(D_801FDF20);
        D_80087134->unk_04(D_801FDF20);
        func_8006ED5C();
        D_80087110 = 0;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006EE30);

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006F0D8);

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006F634);

u8 *func_80076C8C(s32, s32 *);

void func_8006F8F8(SoundChannel *ch, SoundTrack *track) {
    s32 seq;

    ch->unk_4C = track->unk_00->unk_10;
    ch->unk_1A = track->unk_00->unk_0E;
    seq = track->unk_08;
    ch->unk_30 = seq;
    ch->unk_34 = func_80076C8C(seq, &ch->unk_08);
    ch->unk_38 = track->unk_04;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006F96C);

void func_80078A40(s32 n, s32 arg1);

void func_8006FC6C(s32 n) {
    func_80078A40(n, 0);
}

void func_8006FC8C(s32 n, s32 arg1) {
    func_8006F96C(&D_801FDF20->unk_0C->unk_20[n], n, 0, 0, arg1);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006FCD4);

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006FEB4);

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006FED8);

void func_800700A8(void) {
    func_8006FED8(0, 0);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_800700CC);

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_80070298);

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_80070324);

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_800703D8);

void func_80070414(void) {
    func_80063BB0();
}

s32 func_80070434(void) {
    return 0;
}

void func_8007043C(void) {
}

void func_80070444(void) {
    D_80087190 = 0;
}

void func_80070454(void) {
    D_80087190 = 1;
}

void func_80070468(void) {
    if (++D_80087198 == 1) {
        EnterCriticalSection();
    }
}

void func_800704A8(void) {
    if (--D_80087198 == 0) {
        ExitCriticalSection();
    }
}

void func_800704E4(s16 v) {
    D_8008718C = v;
    func_8007051C();
}

u16 func_8007050C(void) {
    return D_8008718C;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8007051C);

s32 func_80070578(void) {
    return D_801FDF24;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_80070588);

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8007062C);

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_800706C0);

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8007078C);

void func_800707BC(void) {
    D_80087190 = 0;
    if (D_80087178 != 0) {
        EnterCriticalSection();
        D_8008719C = OpenEvent(0xF2000002, 2, 0x1000, func_8007062C);
        EnableEvent(D_8008719C);
        SetRCnt(0xF2000002, func_8007078C(func_8007050C()), 0x1000);
        StartRCnt(0xF2000002);
        D_80087180 = 1;
        ExitCriticalSection();
    }
}

extern u8 D_800170A4[];
extern s32 (*D_801FDF2C)(s32, u8 *);

s32 func_80070868(s32 arg0) {
    return D_801FDF2C(arg0, D_800170A4);
}

extern s32 (*D_801FDF30)(s32, s32, s32, s32);

s32 func_80070898(s32 arg0, s32 arg1, s32 arg2) {
    return D_801FDF30(arg0, arg1, 1, arg2);
}

void func_800708C4(void) {
    D_801FDF34();
}

void func_800708EC(void) {
    D_801FDF3C();
}
