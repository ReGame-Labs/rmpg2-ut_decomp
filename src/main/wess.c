/* The sound driver WESS (the "SPSX" module): its API (the sequences' start, stop, pause and volume), the SPU command
 * set and the voice allocator on libspu, the sequence loader, the timer, and the file access through the game's
 * functions (docs/TOOLCHAIN.md "The sound driver: GCC 2.7.2").
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "sound.h"
#include "psyq/libapi.h"
#include "psyq/libspu.h"

void func_80063BB0(void);
void func_8006FED8(s32 set_rate, s32 rate);
void func_8006FCD4(s32 n, s32 set_rate, s32 rate);
s32 func_8006EC68(s32 n);
s32 func_8006C1F4(void);
void func_8006C19C(s32 n);
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
void wess_report_error(s32);
u16 func_8007050C(void);
u32 func_80070588(s16 ips, s16 ppq, s16 qpm);
void func_8006CD78(SoundChannel *ch);
void func_8006DF68(SoundNote *);
void func_80076D5C(SoundChannel *ch);
void wess_start_voice(SoundNote *v);
void func_8006DD48(SoundNote *v, SoundChannel *ch, SoundPatchmap *map, SoundEntry *sample, u8 note, u8 velocity);
void func_8006DDE4(SoundNote *v);
s32 wess_valid_sequence(s32 n);
s32 wess_read_sequence(s32 n, s32 dst);
void func_80078A40(s32 n, s32 arg1);
s32 wess_sequence_size(s32 n);
s32 wess_open_sequence_file(void);
void wess_close_sequence_file(void);
s32 func_800703D8(u8 a, s32 b, s32 c, s32 d, s32 e);
s32 wess_load_sequence(s32, s32);
s32 func_80070578(void);
void func_80063D04(void);
void func_80078088(void);
void func_800704E4(u16 v);
s32 func_8006ECF8(void);
void func_8006BED0(u8 *src);
void func_8006BF08(u16 *src);
void func_8006CA64(s32 bits);
s32 func_8006EC58(void);
void func_80070468(void);
void func_800704A8(void);
void func_8006BF44(s32 kinds);
void func_8006BF70(void);
void func_8006BF80(s16 seq, u8 track, SoundChannel *ch);
void func_8006E014(SoundChannel *ch, SoundPatchmap *map, SoundEntry *sample, u8 note, u8 velocity);
void func_8006DEAC(SoundNote *v);

extern SoundEventQueue *D_80087100;
extern s32 D_80087104;
extern s32 D_80087118;
extern s32 D_8008711C;
extern s32 (*D_80087128)(s32, s32);
extern s32 D_8008712C;
extern s32 D_80087178;
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
extern s32 D_8008715C;
extern s32 D_80087160;
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
extern u8 D_800870F0;                  /* the effects' master volume */
extern u8 D_800870F1;                  /* the music's master volume */
extern u8 D_800870F2;                  /* the panning: 0 none, 1 stereo, 2 reversed */
extern s16 D_801FDBD8;                 /* D_801FDB58[0x40], the centre, by its own name */
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
extern s32 D_801FDEB4;                 /* the file offset past the sequence table */
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

void func_8006BBA0(s32 mute, s32 kinds) {
    s32 seqs;
    s32 active;
    SoundSeqStat *seq;
    s32 playing;
    s32 entries;
    u8 *idx;
    SoundChannel *ch;

    if (!func_8006EC58()) {
        return;
    }
    func_80070468();
    if (mute == 1) {
        func_8006BF44(kinds);
    }
    seqs = D_8008715C;
    active = D_801FDF20->unk_04;
    seq = D_801FDF20->unk_18;
    if (active != 0) {
        while (--seqs != -1) {
            if (seq->unk_00.w & 1) {
                playing = seq->unk_04;
                entries = D_801FDF20->unk_0A;
                idx = seq->unk_0C;
                while (--entries != -1) {
                    if (*idx != 0xFF) {
                        ch = &D_801FDF20->unk_1C[*idx];
                        if (mute == 1) {
                            D_80087130[ch->unk_10][6](ch);
                        }
                        func_8006BB60(ch, seq);
                        if (--playing == 0) {
                            break;
                        }
                    }
                    idx++;
                }
                if (--active == 0) {
                    break;
                }
            }
            seq++;
        }
    }
    if (mute == 1) {
        func_8006BF70();
    }
    func_800704A8();
}

void func_8006BD60(s32 replay) {
    s32 seqs;
    s32 active;
    SoundSeqStat *seq;
    s32 playing;
    s32 entries;
    u8 *idx;
    SoundChannel *ch;

    if (!func_8006EC58()) {
        return;
    }
    func_80070468();
    seqs = D_8008715C;
    active = D_801FDF20->unk_04;
    seq = D_801FDF20->unk_18;
    if (active != 0) {
        while (--seqs != -1) {
            if (seq->unk_00.w & 1) {
                playing = seq->unk_04;
                entries = D_801FDF20->unk_0A;
                idx = seq->unk_0C;
                while (--entries != -1) {
                    if (*idx != 0xFF) {
                        ch = &D_801FDF20->unk_1C[*idx];
                        func_8006BB14(ch, seq);
                        if (replay != 0) {
                            func_8006BF80(seq->unk_00.h[1], *idx, ch);
                        }
                        if (--playing == 0) {
                            break;
                        }
                    }
                    idx++;
                }
                if (--active == 0) {
                    break;
                }
            }
            seq++;
        }
    }
    func_800704A8();
}

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

void func_8006BF80(s16 seq, u8 track, SoundChannel *ch) {
    s32 i;

    for (i = 0; i < D_801FDC70.unk_00; i++) {
        if (track == D_801FDC70.unk_08[i].unk_02 && seq == D_801FDC70.unk_08[i].unk_00 && D_801FDC70.unk_08[i].unk_08 != 0) {
            func_8006E014(ch, (SoundPatchmap *) D_801FDC70.unk_08[i].unk_08,
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

extern s32 D_801FD964;
extern s32 D_801FD968;
extern s32 D_801FD96C;
extern s32 D_801FD970;
extern SoundChannel *D_801FD974;
extern s16 D_801FD978;

void wess_start_voice(SoundNote *v) {
    s32 root;

    D_801FDA98.voice = 1 << v->unk_00.b[2];
    D_801FDA98.mask = 0x600E3;
    D_801FD974 = &D_801FDA74[v->unk_00.b[3]];
    if (D_801FD974->unk_0C != 0) {
        if (D_801FDC58[v->unk_00.b[2]] == 0) {
            SpuSetReverbVoice(1, D_801FDA98.voice);
            D_801FDC58[v->unk_00.b[2]] = 0x7F;
        }
    } else if (D_801FDC58[v->unk_00.b[2]] != 0) {
        SpuSetReverbVoice(0, D_801FDA98.voice);
        D_801FDC58[v->unk_00.b[2]] = 0;
    }
    if (D_800870F2 != 0) {
        D_801FD978 = D_801FD974->unk_0E + v->unk_08->pan - 0x40;
        if (D_801FD978 > 0x7F) {
            D_801FD978 = 0x7F;
        }
        if (D_801FD978 < 0) {
            D_801FD978 = 0;
        }
    } else {
        D_801FD978 = 0x40;
    }
    if (D_800870F8 != 0) {
        if (D_801FD974->unk_00.b[3] == 0) {
            D_801FD970 = (D_801FDAD8[v->unk_06] * D_801FDAD8[v->unk_08->volume] * D_801FDAD8[D_801FD974->unk_0D] *
                          D_801FDAD8[D_800870F0]) >> 21;
        } else {
            D_801FD970 = (D_801FDAD8[v->unk_06] * D_801FDAD8[v->unk_08->volume] * D_801FDAD8[D_801FD974->unk_0D] *
                          D_801FDAD8[D_800870F1]) >> 21;
        }
    } else if (D_801FD974->unk_00.b[3] == 0) {
        D_801FD970 = (v->unk_06 * v->unk_08->volume * D_801FD974->unk_0D * D_800870F0) >> 21;
    } else {
        D_801FD970 = (v->unk_06 * v->unk_08->volume * D_801FD974->unk_0D * D_800870F1) >> 21;
    }
    if (D_801FD970 != 0) {
        if (D_800870FC != 0) {
            if (D_800870F2 == 0) {
                D_801FDA98.volume.left = (D_801FDBD8 * (D_801FD970 + 1)) >> 7;
                D_801FDA98.volume.right = (D_801FDBD8 * (D_801FD970 + 1)) >> 7;
            } else if (D_800870F2 == 1) {
                D_801FDA98.volume.left = ((s16)D_801FDB58[0x7F - D_801FD978] * (D_801FD970 + 1)) >> 7;
                D_801FDA98.volume.right = ((s16)D_801FDB58[D_801FD978] * (D_801FD970 + 1)) >> 7;
            } else {
                D_801FDA98.volume.right = ((s16)D_801FDB58[0x7F - D_801FD978] * (D_801FD970 + 1)) >> 7;
                D_801FDA98.volume.left = ((s16)D_801FDB58[D_801FD978] * (D_801FD970 + 1)) >> 7;
            }
        } else if (D_800870F2 == 0) {
            D_801FDA98.volume.left = D_801FD970 << 6;
            D_801FDA98.volume.right = D_801FD970 << 6;
        } else if (D_800870F2 == 1) {
            D_801FDA98.volume.left = ((D_801FD970 << 7) * (0x80 - D_801FD978)) >> 7;
            D_801FDA98.volume.right = ((D_801FD970 << 7) * (D_801FD978 + 1)) >> 7;
        } else {
            D_801FDA98.volume.right = ((D_801FD970 << 7) * (0x80 - D_801FD978)) >> 7;
            D_801FDA98.volume.left = ((D_801FD970 << 7) * (D_801FD978 + 1)) >> 7;
        }
    } else {
        D_801FDA98.volume.left = 0;
        D_801FDA98.volume.right = 0;
    }
    if (D_801FD974->unk_06 == 0) {
        D_801FDA98.note = v->unk_05 << 8;
    } else if (D_801FD974->unk_06 > 0) {
        D_801FD964 = D_801FD974->unk_06 * v->unk_08->bend_up + 0x20;
        D_801FD968 = D_801FD964 >> 13;
        D_801FD96C = (D_801FD964 & 0x1FFF) >> 6;
        D_801FDA98.note = ((v->unk_05 + D_801FD968) << 8) | D_801FD96C;
    } else {
        D_801FD964 = 0x20 - D_801FD974->unk_06 * v->unk_08->bend_down;
        D_801FD968 = (D_801FD964 >> 13) + 1;
        D_801FD96C = 0x80 - ((D_801FD964 & 0x1FFF) >> 6);
        if (D_801FD96C == 0x80) {
            D_801FD96C = 0;
            D_801FD968 = D_801FD964 >> 13;
        }
        D_801FDA98.note = ((v->unk_05 - D_801FD968) << 8) | (D_801FD96C & 0x7F);
    }
    root = (v->unk_08->root << 8) | v->unk_08->fine;
    D_801FDA98.sample_note = root;
    D_801FDA98.addr = v->unk_0C->unk_08;
    D_801FDA98.adsr1 = v->unk_08->unk_0C;
    D_801FDA98.adsr2 = v->unk_08->unk_0E;
    SpuSetKeyOnWithAttr(&D_801FDA98);
}

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

extern s32 D_801FD980;
extern s32 D_801FD984;
extern SoundNote *D_801FD988;
extern s32 D_801FD98C;
extern s32 D_801FD990;
extern u8 D_801FD994[24];

void func_8006CAB8(void) {
    D_801FD980 = D_801FDA6C->unk_06;
    if (D_801FD980 != 0) {
        D_801FD988 = D_801FDA78;
        D_801FD984 = D_801FDA7C;
        while (--D_801FD984 != -1) {
            if ((D_801FD988->unk_00.w & 3) == 3 && *D_801FDA84 > D_801FD988->unk_10) {
                func_8006DDE4(D_801FD988);
                if (--D_801FD980 == 0) {
                    break;
                }
            }
            D_801FD988++;
        }
    }
    if (D_8008717C != 0) {
        SpuGetAllKeysStatus(D_801FD994);
        D_801FD98C = 24;
        D_801FD990 = 0;
        D_801FD988 = D_801FDA78;
        while (--D_801FD98C != -1) {
            if ((D_801FD988->unk_00.w & 1) && D_801FD994[D_801FD990] == 0) {
                func_8006DDE4(D_801FD988);
            }
            D_801FD990++;
            D_801FD988++;
        }
    }
    func_8006CA84();
}

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

extern s32 D_801FD9C4;
extern s32 D_801FD9C8;
extern s32 D_801FD9CC;
extern s32 D_801FD9D0;
extern s32 D_801FD9D4;
extern SoundNote *D_801FD9D8;
extern s16 D_801FD9DC;

void wess_pitch_mod(SoundChannel *ch) {
    u8 *p;
    s16 v;

    p = ch->unk_34;
    D_801FD9DC = p[1] | (p[2] << 8);
    if (ch->unk_06 != D_801FD9DC) {
        ch->unk_06 = D_801FD9DC;
        D_801FD9C4 = ch->unk_11;
        if (D_801FD9C4 != 0) {
            D_801FD9D8 = D_801FDA78;
            D_801FD9C8 = D_801FDA7C;
            while (--D_801FD9C8 != -1) {
                if ((D_801FD9D8->unk_00.w & 1) && D_801FD9D8->unk_00.b[3] == ch->unk_00.b[1]) {
                    D_801FDA98.voice = 1 << D_801FD9D8->unk_00.b[2];
                    D_801FDA98.mask = 0x20;
                    if (ch->unk_06 == 0) {
                        D_801FDA98.note = D_801FD9D8->unk_05 << 8;
                    } else if (ch->unk_06 > 0) {
                        D_801FD9CC = ch->unk_06 * D_801FD9D8->unk_08->bend_up + 0x20;
                        D_801FD9D0 = D_801FD9CC >> 13;
                        D_801FD9D4 = (D_801FD9CC & 0x1FFF) >> 6;
                        D_801FDA98.note = ((D_801FD9D8->unk_05 + D_801FD9D0) << 8) | D_801FD9D4;
                    } else {
                        D_801FD9CC = 0x20 - ch->unk_06 * D_801FD9D8->unk_08->bend_down;
                        D_801FD9D0 = (D_801FD9CC >> 13) + 1;
                        D_801FD9D4 = 0x80 - ((D_801FD9CC & 0x1FFF) >> 6);
                        if (D_801FD9D4 == 0x80) {
                            D_801FD9D4 = 0;
                            D_801FD9D0 = D_801FD9CC >> 13;
                        }
                        D_801FDA98.note = ((D_801FD9D8->unk_05 - D_801FD9D0) << 8) | (D_801FD9D4 & 0x7F);
                    }
                    SpuSetVoiceAttr(&D_801FDA98);
                    if (--D_801FD9C4 == 0) {
                        break;
                    }
                }
                D_801FD9D8++;
            }
        }
    }
}

void func_8006D17C(void) {
}

void func_8006D184(void) {
}

extern s32 D_801FD9E0;
extern s32 D_801FD9E4;
extern s32 D_801FD9E8;
extern SoundNote *D_801FD9EC;
extern s16 D_801FD9F0;
extern u8 D_801FD9F4;

void wess_volume_mod(SoundChannel *ch) {
    D_801FD9F4 = ch->unk_34[1];
    if (ch->unk_0D != D_801FD9F4) {
        ch->unk_0D = D_801FD9F4;
        D_801FD9E0 = ch->unk_11;
        if (D_801FD9E0 != 0) {
            D_801FD9EC = D_801FDA78;
            D_801FD9E4 = D_801FDA7C;
            while (--D_801FD9E4 != -1) {
                if ((D_801FD9EC->unk_00.w & 1) && D_801FD9EC->unk_00.b[3] == ch->unk_00.b[1]) {
                    if (D_800870F2 != 0) {
                        D_801FD9F0 = ch->unk_0E + D_801FD9EC->unk_08->pan - 0x40;
                        if (D_801FD9F0 > 0x7F) {
                            D_801FD9F0 = 0x7F;
                        }
                        if (D_801FD9F0 < 0) {
                            D_801FD9F0 = 0;
                        }
                    } else {
                        D_801FD9F0 = 0x40;
                    }
                    if (D_800870F8 != 0) {
                        if (ch->unk_00.b[3] == 0) {
                            D_801FD9E8 = (D_801FDAD8[D_801FD9EC->unk_06] * D_801FDAD8[D_801FD9EC->unk_08->volume] *
                                          D_801FDAD8[ch->unk_0D] * D_801FDAD8[D_800870F0]) >> 21;
                        } else {
                            D_801FD9E8 = (D_801FDAD8[D_801FD9EC->unk_06] * D_801FDAD8[D_801FD9EC->unk_08->volume] *
                                          D_801FDAD8[ch->unk_0D] * D_801FDAD8[D_800870F1]) >> 21;
                        }
                    } else if (ch->unk_00.b[3] == 0) {
                        D_801FD9E8 = (D_801FD9EC->unk_06 * D_801FD9EC->unk_08->volume * ch->unk_0D * D_800870F0) >> 21;
                    } else {
                        D_801FD9E8 = (D_801FD9EC->unk_06 * D_801FD9EC->unk_08->volume * ch->unk_0D * D_800870F1) >> 21;
                    }
                    D_801FDA98.voice = 1 << D_801FD9EC->unk_00.b[2];
                    D_801FDA98.mask = 3;
                    if (D_801FD9E8 != 0) {
                        if (D_800870FC != 0) {
                            if (D_800870F2 == 0) {
                                D_801FDA98.volume.left = (D_801FDBD8 * (D_801FD9E8 + 1)) >> 7;
                                D_801FDA98.volume.right = (D_801FDBD8 * (D_801FD9E8 + 1)) >> 7;
                            } else if (D_800870F2 == 1) {
                                D_801FDA98.volume.left = ((s16)D_801FDB58[0x7F - D_801FD9F0] * (D_801FD9E8 + 1)) >> 7;
                                D_801FDA98.volume.right = ((s16)D_801FDB58[D_801FD9F0] * (D_801FD9E8 + 1)) >> 7;
                            } else {
                                D_801FDA98.volume.right = ((s16)D_801FDB58[0x7F - D_801FD9F0] * (D_801FD9E8 + 1)) >> 7;
                                D_801FDA98.volume.left = ((s16)D_801FDB58[D_801FD9F0] * (D_801FD9E8 + 1)) >> 7;
                            }
                        } else if (D_800870F2 == 0) {
                            D_801FDA98.volume.left = D_801FD9E8 << 6;
                            D_801FDA98.volume.right = D_801FD9E8 << 6;
                        } else if (D_800870F2 == 1) {
                            D_801FDA98.volume.left = ((D_801FD9E8 << 7) * (0x80 - D_801FD9F0)) >> 7;
                            D_801FDA98.volume.right = ((D_801FD9E8 << 7) * (D_801FD9F0 + 1)) >> 7;
                        } else {
                            D_801FDA98.volume.right = ((D_801FD9E8 << 7) * (0x80 - D_801FD9F0)) >> 7;
                            D_801FDA98.volume.left = ((D_801FD9E8 << 7) * (D_801FD9F0 + 1)) >> 7;
                        }
                    } else {
                        D_801FDA98.volume.left = 0;
                        D_801FDA98.volume.right = 0;
                    }
                    SpuSetVoiceAttr(&D_801FDA98);
                    if (--D_801FD9E0 == 0) {
                        break;
                    }
                }
                D_801FD9EC++;
            }
        }
    }
}

extern s32 D_801FD9F8;
extern s32 D_801FD9FC;
extern s32 D_801FDA00;
extern SoundNote *D_801FDA04;
extern s16 D_801FDA08;
extern u8 D_801FDA0C;

void wess_pan_mod(SoundChannel *ch) {
    D_801FDA0C = ch->unk_34[1];
    if (ch->unk_0E != D_801FDA0C) {
        ch->unk_0E = D_801FDA0C;
        if (D_800870F2 != 0) {
            D_801FD9F8 = ch->unk_11;
            if (D_801FD9F8 != 0) {
                D_801FDA04 = D_801FDA78;
                D_801FD9FC = D_801FDA7C;
                while (--D_801FD9FC != -1) {
                    if ((D_801FDA04->unk_00.w & 1) && D_801FDA04->unk_00.b[3] == ch->unk_00.b[1]) {
                        D_801FDA08 = ch->unk_0E + D_801FDA04->unk_08->pan - 0x40;
                        if (D_801FDA08 > 0x7F) {
                            D_801FDA08 = 0x7F;
                        }
                        if (D_801FDA08 < 0) {
                            D_801FDA08 = 0;
                        }
                        if (D_800870F8 != 0) {
                            if (ch->unk_00.b[3] == 0) {
                                D_801FDA00 = (D_801FDAD8[D_801FDA04->unk_06] * D_801FDAD8[D_801FDA04->unk_08->volume] *
                                              D_801FDAD8[ch->unk_0D] * D_801FDAD8[D_800870F0]) >> 21;
                            } else {
                                D_801FDA00 = (D_801FDAD8[D_801FDA04->unk_06] * D_801FDAD8[D_801FDA04->unk_08->volume] *
                                              D_801FDAD8[ch->unk_0D] * D_801FDAD8[D_800870F1]) >> 21;
                            }
                        } else if (ch->unk_00.b[3] == 0) {
                            D_801FDA00 = (D_801FDA04->unk_06 * D_801FDA04->unk_08->volume * ch->unk_0D * D_800870F0) >> 21;
                        } else {
                            D_801FDA00 = (D_801FDA04->unk_06 * D_801FDA04->unk_08->volume * ch->unk_0D * D_800870F1) >> 21;
                        }
                        D_801FDA98.voice = 1 << D_801FDA04->unk_00.b[2];
                        D_801FDA98.mask = 3;
                        if (D_801FDA00 != 0) {
                            if (D_800870FC != 0) {
                                if (D_800870F2 == 1) {
                                    D_801FDA98.volume.left = ((s16)D_801FDB58[0x7F - D_801FDA08] * (D_801FDA00 + 1)) >> 7;
                                    D_801FDA98.volume.right = ((s16)D_801FDB58[D_801FDA08] * (D_801FDA00 + 1)) >> 7;
                                } else {
                                    D_801FDA98.volume.right = ((s16)D_801FDB58[0x7F - D_801FDA08] * (D_801FDA00 + 1)) >> 7;
                                    D_801FDA98.volume.left = ((s16)D_801FDB58[D_801FDA08] * (D_801FDA00 + 1)) >> 7;
                                }
                            } else if (D_800870F2 == 1) {
                                D_801FDA98.volume.left = ((D_801FDA00 << 7) * (0x80 - D_801FDA08)) >> 7;
                                D_801FDA98.volume.right = ((D_801FDA00 << 7) * (D_801FDA08 + 1)) >> 7;
                            } else {
                                D_801FDA98.volume.right = ((D_801FDA00 << 7) * (0x80 - D_801FDA08)) >> 7;
                                D_801FDA98.volume.left = ((D_801FDA00 << 7) * (D_801FDA08 + 1)) >> 7;
                            }
                        } else {
                            D_801FDA98.volume.left = 0;
                            D_801FDA98.volume.right = 0;
                        }
                        SpuSetVoiceAttr(&D_801FDA98);
                        if (--D_801FD9F8 == 0) {
                            break;
                        }
                    }
                    D_801FDA04++;
                }
            }
        }
    }
}

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
    wess_start_voice(v);
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

void wess_report_error(s32 arg0) {
    if (D_801FDEA8 != NULL) {
        D_801FDEA8(D_801FDEAC, arg0);
    }
}

s32 wess_sequence_count(void) {
    return D_801FDEA0;
}

s32 wess_valid_sequence(s32 n) {
    if (n < 0 || n >= D_801FDEA0) {
        return 0;
    }
    return 1;
}

s32 wess_open_sequence_file(void) {
    if (D_801FDEA4 == 0) {
        D_801FDEB0 = func_80070868(D_801FDE9C);
        if (D_801FDEB0 == 0) {
            wess_report_error(1);
            return 0;
        }
    }
    D_801FDEA4++;
    return 1;
}

void wess_close_sequence_file(void) {
    if (D_801FDEA4 == 1) {
        func_800708EC(D_801FDEB0);
    }
    if (D_801FDEA4 > 0) {
        D_801FDEA4--;
    }
}

s32 wess_read_sequence(s32 n, s32 dst) {
    SoundSlot *slot;
    s32 tracks;
    s32 start;
    s32 offset;
    s32 size;
    u8 *p;
    s32 i;

    start = dst;
    if (D_801FDEB8 != 0) {
        if (!wess_valid_sequence(n)) {
            return 0;
        }
        slot = &D_801FDE98->unk_0C->unk_20[n];
        tracks = slot->unk_00;
        if (D_80087170 < tracks) {
            return 0;
        }
        slot->unk_0C = (SoundTrack *) dst;
        dst += slot->unk_00 * 12;
        dst += dst & 1;
        dst += dst & 2;
        dst += dst & 4;
        p = (u8 *) dst;
        dst += slot->unk_04;
        offset = slot->unk_08 + D_801FDEB4;
        if (slot->method == 0) {
            if (wess_open_sequence_file() == 0) {
                wess_report_error(1);
                return 0;
            }
            if (func_800708C4(D_801FDEB0, offset, 0) != 0) {
                wess_report_error(3);
                return 0;
            }
            size = slot->unk_04;
            if (size != func_80070898(p, size, D_801FDEB0)) {
                wess_report_error(2);
                return 0;
            }
            wess_close_sequence_file();
        } else if (func_800703D8(slot->method, D_801FDE9C, offset, (s32) p, slot->unk_04) < 0) {
            return 0;
        }
        for (i = 0; i < tracks; i++) {
            slot->unk_0C[i].unk_00 = (SoundTrackHeader *) p;
            p += sizeof(SoundTrackHeader);
            slot->unk_0C[i].unk_04 = (s32 *) p;
            p += (s16) slot->unk_0C[i].unk_00->label_count * 4;
            slot->unk_0C[i].unk_08 = p;
            p += slot->unk_0C[i].unk_00->data_size;
        }
    }
    return dst - start;
}

s32 wess_sequence_header(SoundDriver *drv, s32 name) {
    s32 r;

    r = 0;
    D_801FDE9C = name;
    D_801FDE98 = drv;
    if (drv != NULL) {
        if (wess_open_sequence_file() == 0) {
            wess_report_error(1);
            return 0;
        }
        if (func_800708C4(D_801FDEB0, 0, 0) != 0) {
            wess_report_error(3);
            return 0;
        }
        if (func_80070898(&D_801FDE78, 32, D_801FDEB0) != 32) {
            wess_report_error(2);
            return 0;
        }
        r = D_801FDE78.size;
        wess_close_sequence_file();
    }
    return r;
}

s32 wess_load_sequence_table(SoundDriver *drv, s32 name, s32 keep, SoundSlot *table) {
    s32 r;
    s32 n;

    r = 0;
    D_801FDEB8 = 0;
    D_801FDE9C = name;
    D_801FDE98 = drv;
    if (drv != NULL) {
        if (wess_open_sequence_file() == 0) {
            wess_report_error(1);
            return 0;
        }
        if (func_800708C4(D_801FDEB0, 0, 0) != 0) {
            wess_report_error(3);
            return 0;
        }
        n = 32;
        if (func_80070898(&D_801FDE78, n, D_801FDEB0) != n) {
            wess_report_error(2);
            return 0;
        }
        r = D_801FDE78.size;
        D_801FDEA0 = D_801FDE78.count;
        D_801FDE98->unk_0C->unk_20 = table;
        if (D_801FDE78.method == 0) {
            n = D_801FDE78.size;
            if (n != func_80070898(D_801FDE98->unk_0C->unk_20, n, D_801FDEB0)) {
                wess_report_error(2);
                return 0;
            }
            D_801FDEB4 = D_801FDE78.size + 32;
        } else {
            if (func_800703D8(D_801FDE78.method, D_801FDE9C, 32, (s32) D_801FDE98->unk_0C->unk_20, D_801FDE78.size) < 0) {
                return 0;
            }
            D_801FDEB4 = D_801FDE78.packed_size + 32;
        }
        if (keep != 1) {
            wess_close_sequence_file();
        }
        D_801FDEB8 = 1;
    }
    return r;
}

s32 wess_sequence_size(s32 n) {
    s32 size;
    SoundSlot *slot;
    s32 tracks;

    size = 0;
    if (D_801FDEB8 != 0) {
        if (!wess_valid_sequence(n)) {
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

s32 wess_load_sequence(s32 n, s32 dst) {
    s32 size;

    size = 0;
    if (D_801FDEB8 != 0) {
        if (!wess_valid_sequence(n)) {
            return 0;
        }
        if (D_801FDE98->unk_0C->unk_20[n].unk_0C == 0) {
            size = wess_read_sequence(n, dst);
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
    if (n < 0 || n >= wess_sequence_count()) {
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

extern s32 D_8001709C;
extern s32 D_80087108;
extern s32 D_80087164;
extern s32 D_80087168;
extern s32 D_8008716C;
extern s32 D_80087174;
extern SoundSeqTable D_801FDEBC;
extern SoundBank D_801FDEE0;
extern SoundDriver D_801FDEFC;

#ifdef NON_MATCHING
/* 89.12%: the size sums: the original reads D_8008715C, D_80087160 and D_8008716C before the driver's stores and
 * the loop's sums in other registers; the rest is the original's (size 0x2A4, original 0x2A8). */
s32 wess_module_size(s32 name) {
    u8 *mem;
    u32 i;
    s32 n;
    SoundDriver *drv;

    if (name == 0) {
        return 0;
    }
    D_80087108 = func_80070868(name);
    if (D_80087108 == 0) {
        func_8006EBA4(1);
        return D_80087110;
    }
    n = 0x20;
    D_801FDEFC.unk_00 = &D_80087188;
    D_801FDF20 = &D_801FDEFC;
    D_801FDEFC.unk_0C = &D_801FDEBC;
    D_801FDEFC.unk_14 = &D_801FDEE0;
    D_801FDEFC.unk_07[0] = D_80087158;
    if (func_80070898(&D_801FDEBC, n, D_80087108) != n) {
        func_8006EBA4(2);
        return 0;
    }
    if (D_801FDF20->unk_0C->magic != D_8001709C) {
        return 0;
    }
    if (D_801FDF20->unk_0C->version != 2) {
        return 0;
    }
    n = 0x18;
    if (func_80070898(&D_801FDEE0, n, D_80087108) != n) {
        func_8006EBA4(2);
        return 0;
    }
    func_800708EC(D_80087108);
    drv = D_801FDF20;
    mem = (u8 *) 8;
    drv->unk_14->unk_18 = mem;
    drv->unk_0A = D_80087170;
    mem += drv->unk_0C->unk_18;
    drv->unk_18 = (SoundSeqStat *) mem;
    mem += D_8008715C * sizeof(SoundSeqStat);
    drv->unk_1C = (SoundChannel *) mem;
    mem += D_80087160 * sizeof(SoundChannel);
    drv->unk_20 = (SoundNote *) mem;
    mem += drv->unk_07[0] * sizeof(SoundNote);
    drv->unk_10 = (SoundHandler *) mem;
    mem += D_8008716C * sizeof(SoundHandler);
    for (i = 0; i < D_8008715C; i++) {
        mem += D_80087164;
        mem += (s32) mem & 1;
        mem += (s32) mem & 2;
        mem += D_80087168;
        mem += (s32) mem & 1;
        mem += (s32) mem & 2;
        mem += D_801FDF20->unk_0A;
        mem += (s32) mem & 1;
        mem += (s32) mem & 2;
    }
    D_801FDF20->unk_0B = D_80087174;
    for (i = 0; i < D_80087160; i++) {
        mem += D_801FDF20->unk_0B * 4;
    }
    mem += (s32) mem & 1;
    mem += (s32) mem & 2;
    return (s32) mem;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/wess", wess_module_size);
#endif

#ifdef NON_MATCHING
/* 98.58%: register choice only: the loop counters get a1 (the original's a2), the fill pointer a0 (a1), so
 * the loop's other temporaries shift by one register */
extern s32 D_80087120;
extern s32 D_80087124;

s32 wess_load_module(s32 name, s32 buf, s32 size) {
    u8 *mem;
    s32 i;
    u32 j;
    s32 len;
    u8 *idx;
    s32 count;

    if (D_80087110 != 0) {
        func_8006EDAC();
    }
    if (buf == 0) {
        D_80087118 = 1;
        D_8008711C = func_80070434(size);
        if (D_8008711C == 0) {
            return D_80087110;
        }
    } else {
        D_80087118 = 0;
        D_8008711C = buf;
    }
    D_80087124 = size;
    func_8006EBDC((u8 *)D_8008711C, size);
    if (func_8006EC48() == 0 || name == 0) {
        func_8006ED5C();
        return D_80087110;
    }
    D_80087108 = func_80070868(name);
    if (D_80087108 == 0) {
        func_8006EBA4(1);
        func_8006ED5C();
        return D_80087110;
    }
    size = 0x20;
    D_801FDEFC.unk_00 = &D_80087188;
    D_801FDF20 = &D_801FDEFC;
    D_801FDEFC.unk_0C = &D_801FDEBC;
    D_801FDEFC.unk_14 = &D_801FDEE0;
    D_801FDEFC.unk_07[0] = D_80087158;
    if (func_80070898(&D_801FDEBC, size, D_80087108) != size) {
        goto read_error;
    }
    if (D_801FDF20->unk_0C->magic != D_8001709C || D_801FDF20->unk_0C->version != 2) {
        goto error;
    }
    size = 0x18;
    if (func_80070898(&D_801FDEE0, size, D_80087108) != size) {
        goto read_error;
    }
    mem = (u8 *)D_8008711C;
    mem += (s32)mem & 1;
    mem += (s32)mem & 2;
    mem += (s32)mem & 4;
    D_801FDF20->unk_14->unk_18 = mem;
    len = D_801FDF20->unk_0C->unk_18;
    mem += len;
    if (D_801FDF20->unk_0C->unk_08[8] == 0) {
        if (len != func_80070898(D_801FDF20->unk_14->unk_18, len, D_80087108)) {
        read_error:
            func_8006EBA4(2);
        error:
            func_8006ED5C();
            return 0;
        }
        func_800708EC(D_80087108);
    } else {
        func_800708EC(D_80087108);
        if (func_800703D8(D_801FDF20->unk_0C->unk_08[8], name, 0x38, (s32)D_801FDF20->unk_14->unk_18,
                          D_801FDF20->unk_0C->unk_18) < 0) {
            return 0;
        }
    }
    D_801FDF20->unk_18 = (SoundSeqStat *)mem;
    mem += D_8008715C * sizeof(SoundSeqStat);
    D_801FDF20->unk_1C = (SoundChannel *)mem;
    mem += D_80087160 * sizeof(SoundChannel);
    D_801FDF20->unk_20 = (SoundNote *)mem;
    mem += D_801FDF20->unk_07[0] * sizeof(SoundNote);
    for (i = 0; i < D_801FDF20->unk_07[0]; i++) {
        D_801FDF20->unk_20[i].unk_00.b[1] = 1;
        D_801FDF20->unk_20[i].unk_00.b[2] = i;
    }
    D_801FDF20->unk_10 = (SoundHandler *)mem;
    mem += D_8008716C * sizeof(SoundHandler);
    D_801FDF20->unk_0A = D_80087170;
    for (j = 0; j < D_8008715C; j++) {
        D_801FDF20->unk_18[j].unk_10 = mem;
        mem += D_80087164;
        mem += (s32)mem & 1;
        mem += (s32)mem & 2;
        D_801FDF20->unk_18[j].unk_14 = mem;
        mem += D_80087168;
        mem += (s32)mem & 1;
        mem += (s32)mem & 2;
        idx = mem;
        D_801FDF20->unk_18[j].unk_0C = mem;
        count = D_801FDF20->unk_0A;
        mem += count;
        mem += (s32)mem & 1;
        mem += (s32)mem & 2;
        while (--count != -1) {
            *idx++ = 0xFF;
        }
    }
    D_801FDF20->unk_0B = D_80087174;
    for (j = 0; j < D_80087160; j++) {
        D_801FDF20->unk_1C[j].unk_00.b[1] = j;
        D_801FDF20->unk_1C[j].unk_3C = (u8 **)mem;
        mem += D_801FDF20->unk_0B * 4;
        D_801FDF20->unk_1C[j].unk_44 = (u8 **)mem;
    }
    mem += (s32)mem & 1;
    mem += (s32)mem & 2;
    D_80087130[0][0](D_801FDF20);
    D_80087130[1][0](D_801FDF20);
    D_80087120 = (s32)mem;
    D_80087110 = 1;
    func_80070454();
    return 1;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/wess", wess_load_module);
#endif

void wess_init_channel(SoundChannel *ch, SoundTrack *track, SoundTrackOpts *opts) {
    s32 mask;

    ch->unk_00.w |= 1;
    ch->unk_00.w &= ~0x10;
    ch->unk_00.w &= ~0x20;
    ch->unk_00.w &= ~0x40;
    ch->unk_00.w |= 0x80;
    ch->unk_00.b[3] = track->unk_00->class;
    ch->unk_10 = 1;
    ch->unk_11 = 0;
    ch->unk_14 = track->unk_00->unk_0A;
    ch->unk_20 = 0;
    ch->unk_24 = 0;
    ch->unk_28 = 0;
    ch->unk_40 = ch->unk_3C;
    ch->unk_18 = track->unk_00->label_count;
    ch->unk_48 = track->unk_00->data_size;
    ch->unk_0F = track->unk_00->unk_09;
    if (opts == NULL || opts->mask == 0) {
        mask = 0;
    } else {
        mask = opts->mask;
    }
    if (mask & 1) {
        ch->unk_0D = opts->unk_04;
    } else {
        ch->unk_0D = track->unk_00->unk_06;
    }
    if (mask & 2) {
        ch->unk_0E = opts->unk_05;
    } else {
        ch->unk_0E = track->unk_00->unk_07;
    }
    if (mask & 4) {
        ch->unk_04 = opts->unk_06;
    } else {
        ch->unk_04 = track->unk_00->unk_02;
    }
    if (mask & 8) {
        ch->unk_06 = opts->unk_08;
    } else {
        ch->unk_06 = track->unk_00->unk_04;
    }
    if ((mask & 0x10) && ((ch->unk_0F >> opts->unk_0A) & 1)) {
        ch->unk_00.w |= 2;
    } else {
        ch->unk_00.w &= ~2;
    }
    if (mask & 0x20) {
        ch->unk_16 = opts->unk_0C;
    } else {
        ch->unk_16 = track->unk_00->unk_0C;
    }
    ch->unk_1C = func_80070588(func_8007050C(), ch->unk_14, ch->unk_16);
    if (mask & 0x40) {
        ch->unk_2C = ch->unk_28 + opts->unk_10;
        ch->unk_00.w |= 0x10;
    } else {
        ch->unk_00.w &= ~0x10;
    }
    if (mask & 0x80) {
        ch->unk_00.w |= 0x20;
    } else {
        ch->unk_00.w &= ~0x20;
    }
    if (mask & 0x100) {
        ch->unk_0C = opts->unk_0B;
    } else {
        ch->unk_0C = track->unk_00->unk_01;
    }
}

void wess_set_channel_data(SoundChannel *ch, SoundTrack *track) {
    u8 *seq;

    ch->unk_4C = track->unk_00->data_size;
    ch->unk_1A = track->unk_00->label_count;
    seq = track->unk_08;
    ch->unk_30 = seq;
    ch->unk_34 = func_80076C8C(seq, &ch->unk_08);
    ch->unk_38 = track->unk_04;
}

#ifdef NON_MATCHING
/* 98.90%: the channel's address adds the base to the index (addu s1,v1,v0), the original the index to the base, and
 * the slot pointer is reloaded from the stack one instruction earlier; the index forms &p[i], p + i, p += i give
 * the same. An integer sum, (SoundChannel *)((s32)i * sizeof(SoundChannel) + (s32)D_801FDF20->unk_1C), gives the
 * original's addu (98.95%); no form of the track's address moves the reload. */
s32 wess_start_sequence(SoundSlot *slot, s32 n, s32 arg2, s32 arg3, SoundTrackOpts *opts) {
    u8 seq;
    u8 max;
    u8 i;
    u8 started;
    s16 tracks;
    u8 *idx;
    SoundSeqStat *stat;
    SoundChannel *ch;
    SoundTrack *track;

    if (func_8006EC68(n) == 0) {
        return 0;
    }
    seq = 0;
    func_80070468();
    max = D_8008715C;
    for (; seq < max; seq++) {
        if (!(D_801FDF20->unk_18[seq].unk_00.w & 1)) {
            break;
        }
    }
    started = 0;
    if (seq == max) {
        func_800704A8();
        return 0;
    }
    stat = &D_801FDF20->unk_18[seq];
    tracks = slot->unk_00;
    max = D_80087160;
    idx = stat->unk_0C;
    for (i = 0; i < max; i++) {
        ch = &D_801FDF20->unk_1C[i];
        if (!(ch->unk_00.w & 1)) {
            track = &slot->unk_0C[started];
            ch->unk_00.b[2] = seq;
            wess_init_channel(ch, track, opts);
            wess_set_channel_data(ch, track);
            if (arg3 != 0) {
                ch->unk_00.w |= 0xC;
            } else {
                ch->unk_00.w &= ~4;
                ch->unk_00.w &= ~8;
                stat->unk_05++;
            }
            started++;
            stat->unk_04++;
            D_801FDF20->unk_05++;
            *idx++ = i;
            if (--tracks == 0) {
                break;
            }
        }
    }
    if (started) {
        stat->unk_00.h[1] = n;
        stat->unk_08 = arg2;
        if (arg3 != 0) {
            stat->unk_00.w |= 2;
            stat->unk_00.b[1] = 0;
        } else {
            stat->unk_00.w &= ~2;
            stat->unk_00.b[1] = 1;
        }
        stat->unk_06 = 0x80;
        stat->unk_07 = 0x40;
        stat->unk_00.w |= 1;
        D_801FDF20->unk_04++;
    }
    func_800704A8();
    if (started) {
        return seq + 1;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/wess", wess_start_sequence);
#endif

void func_8006FC6C(s32 n) {
    func_80078A40(n, 0);
}

void wess_start_sequence_with(s32 n, SoundTrackOpts *opts) {
    wess_start_sequence(&D_801FDF20->unk_0C->unk_20[n], n, 0, 0, opts);
}

void func_8006FCD4(s32 n, s32 set_rate, s32 rate) {
    u8 seqs;
    u8 active;
    SoundSeqStat *seq;
    s32 playing;
    s32 entries;
    u8 *idx;
    SoundChannel *ch;
    s32 old;

    old = 0;
    if (!func_8006EC68(n)) {
        return;
    }
    func_80070468();
    seqs = D_8008715C;
    active = D_801FDF20->unk_04;
    seq = D_801FDF20->unk_18;
    if (active != 0) {
        if (set_rate) {
            old = func_8006C1F4();
            func_8006C19C(rate);
        }
        while (seqs-- != 0) {
            if (seq->unk_00.w & 1) {
                if (seq->unk_00.h[1] == n) {
                    playing = seq->unk_04;
                    entries = D_801FDF20->unk_0A;
                    idx = seq->unk_0C;
                    while (--entries != -1) {
                        if (*idx != 0xFF) {
                            ch = &D_801FDF20->unk_1C[*idx];
                            D_80087130[ch->unk_10][5](ch);
                            if (--playing == 0) {
                                break;
                            }
                        }
                        idx++;
                    }
                }
                if (--active == 0) {
                    break;
                }
            }
            seq++;
        }
        if (set_rate) {
            func_8006C19C(old);
        }
    }
    func_800704A8();
}

void func_8006FEB4(s32 arg0) {
    func_8006FCD4(arg0, 0, 0);
}

void func_8006FED8(s32 set_rate, s32 rate) {
    u8 seqs;
    u8 active;
    SoundSeqStat *seq;
    s32 playing;
    s32 entries;
    u8 *idx;
    SoundChannel *ch;
    s32 old;

    old = 0;
    if (!func_8006EC58()) {
        return;
    }
    func_80070468();
    seqs = D_8008715C;
    active = D_801FDF20->unk_04;
    seq = D_801FDF20->unk_18;
    if (active != 0) {
        if (set_rate) {
            old = func_8006C1F4();
            func_8006C19C(rate);
        }
        while (seqs-- != 0) {
            if (seq->unk_00.w & 1) {
                playing = seq->unk_04;
                entries = D_801FDF20->unk_0A;
                idx = seq->unk_0C;
                while (--entries != -1) {
                    if (*idx != 0xFF) {
                        ch = &D_801FDF20->unk_1C[*idx];
                        D_80087130[ch->unk_10][5](ch);
                        if (--playing == 0) {
                            break;
                        }
                    }
                    idx++;
                }
                if (--active == 0) {
                    break;
                }
            }
            seq++;
        }
        if (set_rate) {
            func_8006C19C(old);
        }
    }
    func_800704A8();
}

void func_800700A8(void) {
    func_8006FED8(0, 0);
}

void func_800700CC(u8 volume) {
    u8 seqs;
    u8 active;
    SoundSeqStat *seq;
    s32 playing;
    s32 entries;
    u8 *idx;
    SoundChannel *ch;
    u8 *pos;
    u8 cmd[2];

    if (!func_8006EC58()) {
        return;
    }
    D_800870F0 = volume;
    func_80070468();
    seqs = D_8008715C;
    active = D_801FDF20->unk_04;
    seq = D_801FDF20->unk_18;
    if (active != 0) {
        while (seqs-- != 0) {
            if (seq->unk_00.w & 1) {
                playing = seq->unk_04;
                entries = D_801FDF20->unk_0A;
                idx = seq->unk_0C;
                while (--entries != -1) {
                    if (*idx != 0xFF) {
                        ch = &D_801FDF20->unk_1C[*idx];
                        if (ch->unk_00.b[3] == 0) {
                            pos = ch->unk_34;
                            ch->unk_34 = cmd;
                            cmd[0] = 12;
                            ch->unk_34[1] = ch->unk_0D;
                            ch->unk_0D = 0;
                            D_80087130[ch->unk_10][12](ch);
                            ch->unk_34 = pos;
                        }
                        if (--playing == 0) {
                            break;
                        }
                    }
                    idx++;
                }
                if (--active == 0) {
                    break;
                }
            }
            seq++;
        }
    }
    func_800704A8();
}

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
            done += wess_sequence_size(seq);
            seq++;
        }
    }
    return done;
}

s32 func_80070324(s32 first, s32 count, s32 dst) {
    s32 done;

    done = 0;
    if (D_801FDEB8 != 0) {
        if (wess_open_sequence_file() == 0 || count == 0) {
            return 0;
        }
        while (--count != -1) {
            done += wess_load_sequence(first, dst + done);
            first++;
        }
        wess_close_sequence_file();
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

    D_801FDF2C = init->open;
    D_801FDF30 = init->read;
    D_801FDF34 = init->seek;
    D_801FDF38 = (s32) init->size;
    D_801FDF3C = (void (*)(s32)) init->close;
    D_801FDF40 = (s32) init->load_spu;
    if (init->unk_18 != NULL) {
        func_8006BED0(init->unk_18);
    }
    if (init->unk_1C != NULL) {
        func_8006BF08(init->unk_1C);
    }
    rate = init->rate;
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
