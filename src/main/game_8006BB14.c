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
u32 func_8007078C(s32);
long func_8007062C(void);
void func_800708EC(s32 h);
s32 func_800708C4(s32 h, s32 offset, s32 mode);
s32 func_80070898(void *dst, s32 size, s32 h);
void func_800707BC(void);
void func_8006ECD8(void);
void func_80070414(void);
void func_80070444(void);
void func_800700A8(void);
void func_8006ED5C(void);
void func_8006E4BC(s32);
u16 func_8007050C(void);
void func_8006CD78(SoundChannel *ch);
void func_8006DF68(SoundNote *);
void func_80076D5C(SoundChannel *ch);
void func_8006C204(SoundNote *v);
void func_8006DD48(SoundNote *v, SoundChannel *ch, SoundPatchmap *map, SoundEntry *sample, u8 note, u8 velocity);
void func_8006DDE4(SoundNote *v);
s32 func_8006E504(s32 n);
s32 func_8006E5F0(s32 n, s32 dst);
void func_80078A40(s32 n, s32 arg1);
void func_8006FCD4(s32, s32, s32);
s32 func_8006EA50(s32 n);
s32 func_8006E530(void);
void func_8006E59C(void);
s32 func_8006EB08(s32, s32);
s32 func_80070578(void);
void func_80063D04(void);
void func_80078088(void);
void func_800704E4(u16 v);
s32 func_8006ECF8(void);
void func_8006BED0(u8 *src);
void func_8006BF08(u16 *src);
void func_8006CA64(s32 bits);
void func_8006E014(SoundChannel *ch, SoundPatchmap *map, SoundEntry *sample, u8 note, u8 velocity);
void func_8006DEAC(SoundNote *v);

extern SoundEventQueue *D_80087100;
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
extern SoundBank *D_801FDA80;
extern SoundPatch *D_801FDA88;
extern SoundPatchmap *D_801FDA8C;
extern u8 *D_801FDA94;
extern s32 D_80087158;
extern s32 D_801FD97C;
extern u8 D_801FDC58[];
extern s32 D_801FDE9C;
extern s32 D_801FDEA4;
extern s32 (*D_801FDEA8)(s32, s32);
extern s32 D_801FDEAC;
extern s32 D_801FDEB0;
extern s32 (*D_801FDF34)(s32, s32, s32);
extern void (*D_801FDF3C)(s32);
extern s32 D_800870F4;
extern u8 D_800870F3;
extern s32 D_8008710C;
extern s32 D_80087110;
extern s16 D_8008718C;
extern s16 D_801FD9C0;
extern s32 D_801FDEA0;
extern s32 D_801FDF24;
extern s32 D_800870F8;
extern u8 D_801FDAD8[];
extern s32 D_800870FC;
extern u16 D_801FDB58[];
extern SoundEventQueue D_801FDC70;
extern SoundSeqStat *D_801FDA70;
extern SoundSeqStat *D_801FD9AC;
extern u8 D_801FDA10;
extern u8 D_801FDA14;
extern SoundNote *D_801FDA18;
extern SoundNote *D_801FDA78;
extern s32 D_801FDA7C;
extern u32 *D_801FDA84;
extern SoundDriver *D_801FDA6C;
extern SoundChannel *D_801FDA74;
extern SoundChannel *D_801FDA20;
extern SpuVoiceAttr D_801FDA98;
extern s32 D_801FDA24;
extern s32 D_801FDA28;
extern s32 D_801FDA2C;
extern s32 D_801FDA64;
extern SoundNote *D_801FDA68;
extern SoundFileHeader D_801FDE78;
extern u32 D_80087170;
extern SoundDriver *D_801FDE98;
extern s32 D_801FDEB8;
extern s32 (*D_801FDF44)(u8, s32, s32, s32, s32);
extern s32 D_80087184;
extern u32 D_80087188;
extern u32 D_80087194;
extern u8 D_800170A4[];
extern s32 (*D_801FDF2C)(s32, u8 *);
extern s32 (*D_801FDF30)(void *, s32, s32, s32);
extern s32 D_801FDF38;
extern s32 D_801FDF40;
extern s32 D_8008717C;

void func_8006BB14(SoundChannel *ch, SoundSeqStat *seq) {
    if (ch->unk_00.w & 8) {
        ch->unk_00.w &= ~2;
        ch->unk_00.w &= ~8;
        if (++seq->unk_05 != 0) {
            seq->unk_00.b[1] = 1;
        }
    }
}

void func_8006BB60(SoundChannel *ch, SoundSeqStat *seq) {
    s32 f;
    u8 n;

    f = ch->unk_00.w;
    if (!(f & 8)) {
        ch->unk_00.w = f | 0xA;
        n = seq->unk_05 - 1;
        seq->unk_05 = n;
        if (n == 0) {
            seq->unk_00.b[1] = 0;
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006BBA0);

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006BD60);

void func_8006BED0(u8 *src) {
    s32 i;

    for (i = 0; i < 0x80; i++) {
        D_801FDAD8[i] = *src++;
    }
    D_800870F8 = 1;
}

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

void func_8006BF44(s32 kinds) {
    D_80087100 = &D_801FDC70;
    if (D_80087100 != NULL) {
        D_80087100->unk_00 = 0;
        D_801FDC70.unk_04 = kinds;
    }
}

void func_8006BF70(void) {
    D_80087100 = 0;
}

void func_8006BF80(s16 a, u8 b, s32 arg2) {
    s32 i;

    for (i = 0; i < D_801FDC70.unk_00; i++) {
        if (b == D_801FDC70.unk_08[i].unk_02 && a == D_801FDC70.unk_08[i].unk_00 && D_801FDC70.unk_08[i].unk_08 != 0) {
            func_8006E014((SoundChannel *) arg2, (SoundPatchmap *) D_801FDC70.unk_08[i].unk_08,
                          (SoundEntry *) D_801FDC70.unk_08[i].unk_0C, D_801FDC70.unk_08[i].unk_04,
                          D_801FDC70.unk_08[i].unk_05);
            D_801FDC70.unk_08[i].unk_08 = 0;
        }
    }
}

void func_8006C084(SoundChannel *ch, s16 arg1, s16 arg2, u8 arg3, u8 arg4, s32 arg5, s32 arg6) {
    u8 kind;

    if (D_80087100 != NULL) {
        kind = ch->unk_00.b[3];
        if ((kind == 1 && (D_80087100->unk_04 & 1)) || (kind == 0 && (D_80087100->unk_04 & 2))) {
            if (D_80087100->unk_00 < 0x20) {
                D_80087100->unk_08[D_80087100->unk_00].unk_00 = arg1;
                D_80087100->unk_08[D_80087100->unk_00].unk_02 = arg2;
                D_80087100->unk_08[D_80087100->unk_00].unk_04 = arg3;
                D_80087100->unk_08[D_80087100->unk_00].unk_05 = arg4;
                D_80087100->unk_08[D_80087100->unk_00].unk_08 = arg5;
                D_80087100->unk_08[D_80087100->unk_00].unk_0C = arg6;
                D_80087100->unk_00++;
            }
        }
    }
}

void func_8006C19C(s32 n) {
    s32 v;

    D_800870F3 = 0x1F;
    D_800870F4 = n;
    v = 0x10000000;
    while (n < v && D_800870F3 != 0) {
        v >>= 1;
        D_800870F3--;
    }
}

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

void func_8006C91C(SoundDriver *drv) {
    D_801FDA6C = drv;
    D_801FDA84 = drv->unk_00;
    D_801FDA70 = drv->unk_18;
    D_801FDA74 = drv->unk_1C;
    D_801FDA78 = drv->unk_20;
    D_801FDA80 = drv->unk_14;
    D_801FDA7C = D_80087158;
    D_801FDA88 = D_801FDA80->unk_18;
    D_801FDA8C = (SoundPatchmap *) (((s32) D_801FDA88 + D_801FDA80->unk_04 * 4 + 7) & ~7);
    D_801FDA90 = (SoundEntry *) (((s32) D_801FDA8C + D_801FDA80->unk_08 * 16 + 7) & ~7);
    D_801FDA94 = (u8 *) (((s32) D_801FDA90 + D_801FDA80->unk_0C * 12 + 7) & ~7);
    func_80063BB0();
    for (D_801FD97C = 0; D_801FD97C < 24; D_801FD97C++) {
        D_801FDC58[D_801FD97C] = 0;
    }
}

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

void func_8006CCCC(SoundChannel *ch) {
    D_801FD9AC = &D_801FDA70[ch->unk_00.b[2]];
    func_8006CD78(ch);
    if (ch->unk_11 != 0) {
        ch->unk_00.w |= 8;
        if (--D_801FD9AC->unk_05 == 0) {
            D_801FD9AC->unk_00.b[1] = 0;
        }
    } else {
        func_80076D5C(ch);
    }
}

extern s32 D_801FD9B0;
extern s32 D_801FD9B4;
extern SoundNote *D_801FD9B8;
extern SoundSeqStat *D_801FD9BC;

void func_8006CD78(SoundChannel *ch) {
    D_801FD9B0 = ch->unk_11;
    if (D_801FD9B0 != 0) {
        D_801FD9B8 = D_801FDA78;
        D_801FD9B4 = D_801FDA7C;
        while (--D_801FD9B4 != -1) {
            if ((D_801FD9B8->unk_00.w & 1) && D_801FD9B8->unk_00.b[3] == ch->unk_00.b[1]) {
                if (D_80087100 != NULL && !(D_801FD9B8->unk_00.w & 2) && ch->unk_00.b[3] == 1) {
                    D_801FD9BC = &D_801FDA70[ch->unk_00.b[2]];
                    func_8006C084(ch, D_801FD9BC->unk_00.h[1], D_801FD9B8->unk_00.b[3], D_801FD9B8->unk_05,
                                  D_801FD9B8->unk_06, (s32) D_801FD9B8->unk_08, (s32) D_801FD9B8->unk_0C);
                }
                func_8006DEAC(D_801FD9B8);
                if (--D_801FD9B0 == 0) {
                    break;
                }
            }
            D_801FD9B8++;
        }
    }
}

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

void func_8006DD48(SoundNote *v, SoundChannel *ch, SoundPatchmap *map, SoundEntry *sample, u8 note, u8 velocity) {
    v->unk_00.w = (v->unk_00.w | 1) & ~2;
    v->unk_00.b[3] = ch->unk_00.b[1];
    v->unk_04 = map->unk_00;
    v->unk_05 = note;
    v->unk_06 = velocity;
    v->unk_07 = 0;
    v->unk_08 = map;
    v->unk_0C = sample;
    v->unk_10 = *D_801FDA84;
    ch->unk_11++;
    D_801FDA6C->unk_06++;
    func_8006C204(v);
}

void func_8006DDE4(SoundNote *v) {
    D_801FDA20 = &D_801FDA74[v->unk_00.b[3]];
    D_801FDA6C->unk_06--;
    if (--D_801FDA20->unk_11 == 0 && (D_801FDA20->unk_00.w & 0xA) == 8) {
        func_80076D5C(D_801FDA20);
    }
    v->unk_00.w &= ~1;
    v->unk_00.w &= ~2;
}

void func_8006DEAC(SoundNote *v) {
    D_801FDA24 = 1 << v->unk_00.b[2];
    D_801FDA98.voice = D_801FDA24;
    D_801FDA98.mask = 0x4400;
    D_801FDA98.r_mode = 7;
    D_801FDA98.rr = D_800870F3;
    SpuSetVoiceAttr(&D_801FDA98);
    func_8006CA64(D_801FDA24);
    v->unk_00.w |= 2;
    v->unk_10 = *D_801FDA84 + (0x10000000 >> (0x1F - D_800870F3));
}

void func_8006DF68(SoundNote *v) {
    D_801FDA28 = 1 << v->unk_00.b[2];
    func_8006CA64(D_801FDA28);
    if (v->unk_08->unk_0E & 0x20) {
        D_801FDA2C = 0x10000000 >> (0x1F - (v->unk_08->unk_0E & 0x1F));
    } else {
        D_801FDA2C = 0x5DC0000 >> (0x1F - (v->unk_08->unk_0E & 0x1F));
    }
    v->unk_00.w |= 2;
    v->unk_10 = *D_801FDA84 + D_801FDA2C;
}

extern s32 D_801FDA30;
extern s32 D_801FDA34;
extern SoundNote *D_801FDA38;
extern SoundNote *D_801FDA3C;
extern s32 D_801FDA40;
extern u32 D_801FDA44;

void func_8006E014(SoundChannel *ch, SoundPatchmap *map, SoundEntry *sample, u8 note, u8 velocity) {
    SoundNote *v;

    D_801FDA40 = 0x100;
    D_801FDA3C = NULL;
    D_801FDA44 = -1;
    D_801FDA34 = 0;
    D_801FDA38 = D_801FDA78;
    D_801FDA30 = D_801FDA7C;
    while (--D_801FDA30 != -1) {
        v = D_801FDA38;
        if (!(v->unk_00.w & 1)) {
            func_8006DD48(v, ch, map, sample, note, velocity);
            D_801FDA34 = 0;
            break;
        }
        if (v->unk_04 <= map->unk_00) {
            if (v->unk_04 < D_801FDA40) {
                D_801FDA34 = 1;
                D_801FDA40 = v->unk_04;
                D_801FDA44 = v->unk_10;
                D_801FDA3C = v;
            } else if (v->unk_00.w & 2) {
                if (!(D_801FDA3C->unk_00.w & 2) || v->unk_10 < D_801FDA44) {
                D_801FDA34 = 1;
                D_801FDA40 = v->unk_04;
                D_801FDA44 = v->unk_10;
                D_801FDA3C = v;
            }
            } else if (!(D_801FDA3C->unk_00.w & 2) && v->unk_10 < D_801FDA44) {
                D_801FDA34 = 1;
                D_801FDA40 = v->unk_04;
                D_801FDA44 = v->unk_10;
                D_801FDA3C = v;
            }
        }
        D_801FDA38++;
    }
    if (D_801FDA34 != 0) {
        func_8006DDE4(D_801FDA3C);
        func_8006DD48(D_801FDA3C, ch, map, sample, note, velocity);
    }
}

extern s32 D_801FDA48;
extern u8 D_801FDA4C;
extern u8 D_801FDA50;
extern u8 D_801FDA54;
extern SoundPatch *D_801FDA58;
extern SoundPatchmap *D_801FDA5C;
extern SoundEntry *D_801FDA60;

void func_8006E244(SoundChannel *ch) {
    D_801FDA4C = ch->unk_34[1];
    D_801FDA50 = ch->unk_34[2];
    D_801FDA58 = &D_801FDA88[ch->unk_04];
    D_801FDA54 = D_801FDA58->unk_00;
    D_801FDA48 = 0;
    while (--D_801FDA54 != 0xFF) {
        D_801FDA5C = &D_801FDA8C[D_801FDA58->unk_02 + D_801FDA48];
        D_801FDA60 = &D_801FDA90[D_801FDA5C->unk_0A];
        if (D_801FDA60->unk_08 != 0 && D_801FDA5C->unk_06 <= D_801FDA4C && D_801FDA4C <= D_801FDA5C->unk_07) {
            func_8006E014(ch, D_801FDA5C, D_801FDA60, D_801FDA4C, D_801FDA50);
        }
        D_801FDA48++;
    }
}

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

s32 func_8006E504(s32 n) {
    if (n < 0 || n >= D_801FDEA0) {
        return 0;
    }
    return 1;
}

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

s32 func_8006E804(SoundDriver *drv, s32 name) {
    s32 r;

    r = 0;
    D_801FDE9C = name;
    D_801FDE98 = drv;
    if (drv != NULL) {
        if (func_8006E530() == 0) {
            func_8006E4BC(1);
            return 0;
        }
        if (func_800708C4(D_801FDEB0, 0, 0) != 0) {
            func_8006E4BC(3);
            return 0;
        }
        if (func_80070898(&D_801FDE78, 32, D_801FDEB0) != 32) {
            func_8006E4BC(2);
            return 0;
        }
        r = D_801FDE78.unk_18;
        func_8006E59C();
    }
    return r;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006E8B4);

s32 func_8006EA50(s32 n) {
    s32 size;
    SoundSlot *slot;
    s32 tracks;

    size = 0;
    if (D_801FDEB8 != 0) {
        if (!func_8006E504(n)) {
            return 0;
        }
        slot = &D_801FDE98->unk_0C->unk_20[n];
        tracks = slot->unk_00;
        if (D_80087170 < tracks) {
            return 0;
        }
        if (slot->unk_0C == 0) {
            tracks *= 12;
            tracks += tracks & 4;
            size = slot->unk_04 + tracks;
        }
    }
    return size;
}

s32 func_8006EB08(s32 n, s32 dst) {
    s32 size;

    size = 0;
    if (D_801FDEB8 != 0) {
        if (!func_8006E504(n)) {
            return 0;
        }
        if (D_801FDE98->unk_0C->unk_20[n].unk_0C == 0) {
            size = func_8006E5F0(n, dst);
        }
    }
    return size;
}

void func_8006EBA4(s32 arg0) {
    if (D_80087128 != NULL) {
        D_80087128(D_8008712C, arg0);
    }
}

void func_8006EBDC(u8 *p, u32 n) {
    while (n-- != 0) {
        *p++ = 0;
    }
}

SoundDriver *func_8006EC08(void) {
    return D_801FDF20;
}

s16 func_8006EC18(void) {
    if (D_801FDF20 != NULL) {
        return D_801FDF20->unk_14->unk_0C;
    }
    return 0;
}

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

void func_8006EDAC(void) {
    if (D_80087110 != 0) {
        func_800700A8();
        func_80070444();
        D_80087130[0][1](D_801FDF20);
        D_80087130[1][1](D_801FDF20);
        func_8006ED5C();
        D_80087110 = 0;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006EE30);

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006F0D8);

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006F634);

void func_8006F8F8(SoundChannel *ch, SoundTrack *track) {
    u8 *seq;

    ch->unk_4C = track->unk_00->unk_10;
    ch->unk_1A = track->unk_00->unk_0E;
    seq = track->unk_08;
    ch->unk_30 = seq;
    ch->unk_34 = func_80076C8C(seq, &ch->unk_08);
    ch->unk_38 = track->unk_04;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006F96C);

void func_8006FC6C(s32 n) {
    func_80078A40(n, 0);
}

void func_8006FC8C(s32 n, s32 arg1) {
    func_8006F96C(&D_801FDF20->unk_0C->unk_20[n], n, 0, 0, arg1);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006FCD4);

void func_8006FEB4(s32 arg0) {
    func_8006FCD4(arg0, 0, 0);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_8006FED8);

void func_800700A8(void) {
    func_8006FED8(0, 0);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8006BB14", func_800700CC);

s32 func_80070298(s32 first, s32 count) {
    s32 done;
    s32 seq;

    done = 0;
    if (D_801FDEB8 != 0) {
        seq = first;
        if (count == 0) {
            return 0;
        }
        while (--count != -1) {
            done += func_8006EA50(seq);
            seq++;
        }
    }
    return done;
}

s32 func_80070324(s32 first, s32 count, s32 dst) {
    s32 done;

    done = 0;
    if (D_801FDEB8 != 0) {
        if (func_8006E530() == 0 || count == 0) {
            return 0;
        }
        while (--count != -1) {
            done += func_8006EB08(first, dst + done);
            first++;
        }
        func_8006E59C();
    }
    return done;
}

s32 func_800703D8(u8 a, s32 b, s32 c, s32 d, s32 e) {
    if (D_801FDF44 != NULL) {
        return D_801FDF44(a, b, c, d, e);
    }
    return -1;
}

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

void func_800704E4(u16 v) {
    D_8008718C = v;
    func_8007051C();
}

u16 func_8007050C(void) {
    return D_8008718C;
}

void func_8007051C(void) {
    D_801FDF24 = 0x3E80000 / func_8007050C();
}

s32 func_80070578(void) {
    return D_801FDF24;
}

u32 func_80070588(s16 ips, s16 ppq, s16 qpm) {
    return ((u64) qpm * ((u64) ppq << 16) / 60) / (u64) ips;
}

long func_8007062C(void) {
    D_80087184++;
    D_80087194 += func_80070578();
    D_80087188 += D_80087194 >> 16;
    D_80087194 &= 0xFFFF;
    func_80063D04();
    if (D_80087190 != 0) {
        func_80078088();
    }
    return 0;
}

void func_800706C0(SoundInit *init) {
    s32 rate;

    D_801FDF2C = init->unk_00;
    D_801FDF30 = init->unk_04;
    D_801FDF34 = init->unk_08;
    D_801FDF38 = init->unk_0C;
    D_801FDF3C = init->unk_10;
    D_801FDF40 = init->unk_14;
    if (init->unk_18 != NULL) {
        func_8006BED0(init->unk_18);
    }
    if (init->unk_1C != NULL) {
        func_8006BF08(init->unk_1C);
    }
    rate = init->unk_20;
    D_80087178 = init->unk_24;
    D_8008717C = init->unk_28;
    func_800704E4(rate);
    func_8007051C();
    func_8006ECF8();
}

u32 func_8007078C(s32 rate) {
    return 100000000 / (u32) (rate * 24);
}

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

s32 func_80070868(s32 arg0) {
    return D_801FDF2C(arg0, D_800170A4);
}

s32 func_80070898(void *dst, s32 size, s32 h) {
    return D_801FDF30(dst, size, 1, h);
}

s32 func_800708C4(s32 h, s32 offset, s32 mode) {
    return D_801FDF34(h, offset, mode);
}

void func_800708EC(s32 h) {
    D_801FDF3C(h);
}
