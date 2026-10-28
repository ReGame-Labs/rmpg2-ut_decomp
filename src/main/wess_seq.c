/* The sound driver WESS, its sequencer: the per-tick engine and the 36 sequence commands (a command byte, its
 * parameters, then a variable-length delay; docs/TOOLCHAIN.md "The sound driver: GCC 2.7.2").
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"

extern u8 D_801FE0C4;
extern u8 D_801FE0CC;
extern u8 D_801FE0D0;
#include "sound.h"

extern s16 D_801FE0C8;

extern s32 D_801FE0B0;
extern u8 D_801FE0B4;
extern SoundDriver *D_80087FA0;
extern u8 D_80087F94;
extern SoundChannel *D_80087F98;
extern SoundSeqStat *D_80087F9C;
extern u32 D_80087160;                  /* the channel count (wess.c) */
extern s32 D_80087164;
extern s32 D_80087168;
extern s32 D_8008716C;
extern u8 D_80088364[];

u16 func_8007050C(void);
u32 func_80070588(s16, s16, s16);

u8 *func_80076C8C(u8 *p, s32 *value) {
    D_801FE0B0 = *p++;
    if (D_801FE0B0 & 0x80) {
        D_801FE0B0 &= 0x7F;
        do {
            D_801FE0B0 = (D_801FE0B0 << 7) + ((D_801FE0B4 = *p++) & 0x7F);
        } while (D_801FE0B4 & 0x80);
    }
    *value = D_801FE0B0;
    return p;
}

void func_80076D04(SoundDriver *drv) {
    D_80087FA0 = drv;
    D_80087F98 = drv->unk_1C;
    D_80087F9C = drv->unk_18;
    D_80087F94 = D_80087160;
}

void func_80076D3C(void) {
}

void func_80076D44(void) {
}

void func_80076D4C(void) {
}

void func_80076D54(void) {
}

extern SoundSeqStat *D_801FE0B8;
extern u8 *D_801FE0BC;
extern s32 D_801FE0C0;

void func_80076D5C(SoundChannel *ch) {
    SoundSeqStat *seq;

    seq = &D_80087FA0->unk_18[ch->unk_00.b[2]];
    D_801FE0B8 = seq;
    if (!(ch->unk_00.w & 8)) {
        ch->unk_00.w |= 8;
        if (--seq->unk_05 == 0) {
            D_801FE0B8->unk_00.b[1] = 0;
        }
    }
    if (!(ch->unk_00.w & 4)) {
        D_801FE0C0 = D_80087FA0->unk_0A;
        D_801FE0BC = D_801FE0B8->unk_0C;
        while (--D_801FE0C0 != -1) {
            if (*D_801FE0BC == ch->unk_00.b[1]) {
                *D_801FE0BC++ = 0xFF;
                break;
            }
            D_801FE0BC++;
        }
        ch->unk_00.w &= ~1;
        D_80087FA0->unk_05--;
        if (--D_801FE0B8->unk_04 == 0) {
            D_801FE0B8->unk_00.w &= ~1;
            D_80087FA0->unk_04--;
        }
    }
    ch->unk_00.w &= ~0x10;
}

void func_80076F08(void) {
}

void func_80076F10(SoundChannel *ch) {
    u8 v;

    v = ch->seq[1];
    D_801FE0C4 = v;
    ch->unk_04 = v;
}

void func_80076F2C(void) {
}

void func_80076F34(SoundChannel *ch) {
    u8 *p;
    s16 v;

    p = ch->seq;
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

    v = ch->seq[1];
    D_801FE0CC = v;
    ch->unk_0D = v;
}

void func_80076F88(SoundChannel *ch) {
    u8 v;

    v = ch->seq[1];
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
                seq = ch->seq;
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

extern s16 D_801FE0E0;
extern u8 *D_801FE0E4;
extern u8 *D_801FE0E8;

void func_800770E8(SoundChannel *ch) {
    D_801FE0E8 = D_80087F9C[ch->unk_00.b[2]].unk_10 + ch->seq[1];
    if (*D_801FE0E8 != 0) {
        if (*D_801FE0E8 == 0xFF) {
            *D_801FE0E8 = ch->seq[2];
        }
        D_801FE0E0 = ch->seq[3] | (ch->seq[4] << 8);
        if (D_801FE0E0 >= 0 && D_801FE0E0 < ch->label_count) {
            D_801FE0E4 = (u8 *) ch->labels[D_801FE0E0];
            D_801FE0E4 += (s32) ch->seq_start;
            ch->seq = D_801FE0E4;
            ch->delay = 0;
            ch->unk_00.w |= 0x40;
        }
    }
}

extern s16 D_801FE0EC;
extern u8 *D_801FE0F0;
extern u8 *D_801FE0F4;

void func_800771D4(SoundChannel *ch) {
    D_801FE0F4 = D_80087F9C[ch->unk_00.b[2]].unk_14 + ch->seq[1];
    if (*D_801FE0F4 != 0) {
        if (*D_801FE0F4 == 0xFF) {
            *D_801FE0F4 = ch->seq[2];
        } else {
            *D_801FE0F4 = *D_801FE0F4 - 1;
        }
        D_801FE0EC = ch->seq[3] | (ch->seq[4] << 8);
        if (D_801FE0EC >= 0 && D_801FE0EC < ch->label_count) {
            D_801FE0F0 = (u8 *) ch->labels[D_801FE0EC];
            D_801FE0F0 += (s32) ch->seq_start;
            ch->seq = D_801FE0F0;
            ch->delay = 0;
            ch->unk_00.w |= 0x40;
        }
    }
}

extern u8 D_801FE0F8;
extern u8 *D_801FE0FC;

void func_800772C8(SoundChannel *ch) {
    if (ch->seq[1] == 0xFF) {
        D_801FE0F8 = D_80087164;
        D_801FE0FC = D_80087F9C[ch->unk_00.b[2]].unk_10;
        while (D_801FE0F8-- != 0) {
            *D_801FE0FC++ = 0xFF;
        }
    } else {
        D_801FE0FC = D_80087F9C[ch->unk_00.b[2]].unk_10 + ch->seq[1];
        *D_801FE0FC = 0xFF;
    }
}

extern u8 D_801FE100;
extern u8 *D_801FE104;

void func_800773BC(SoundChannel *ch) {
    if (ch->seq[1] == 0xFF) {
        D_801FE100 = D_80087168;
        D_801FE104 = D_80087F9C[ch->unk_00.b[2]].unk_14;
        while (D_801FE100-- != 0) {
            *D_801FE104++ = 0xFF;
        }
    } else {
        D_801FE104 = D_80087F9C[ch->unk_00.b[2]].unk_14 + ch->seq[1];
        *D_801FE104 = 0xFF;
    }
}

extern u8 *D_801FE108;

void func_800774B0(SoundChannel *ch) {
    D_801FE108 = D_80087F9C[ch->unk_00.b[2]].unk_14 + ch->seq[1];
    *D_801FE108 = ch->seq[2];
}

extern s16 D_801FE10C;
extern u8 D_801FE110;
extern u8 *D_801FE114;
extern SoundChannel *D_801FE118;
extern SoundSeqStat *D_801FE11C;

void func_800774F4(SoundChannel *ch) {
    D_801FE11C = &D_80087F9C[ch->unk_00.b[2]];
    D_801FE10C = D_80087FA0->unk_0C->unk_20[D_801FE11C->unk_00.h[1]].unk_00;
    D_801FE110 = D_801FE11C->unk_04;
    D_801FE114 = D_801FE11C->unk_0C;
    while (--D_801FE10C != -1) {
        if (*D_801FE114 != 0xFF) {
            D_801FE118 = &D_80087F98[*D_801FE114];
            D_801FE118->tempo = ch->seq[1] | (ch->seq[2] << 8);
            D_801FE118->tick_step = func_80070588(func_8007050C(), D_801FE118->ppq, D_801FE118->tempo);
            if (--D_801FE110 == 0) {
                break;
            }
        }
        D_801FE114++;
    }
}

extern s16 D_801FE120;
extern s16 D_801FE124;
extern u8 *D_801FE128;
extern u8 D_801FE12C;
extern u8 *D_801FE130;
extern SoundChannel *D_801FE134;
extern SoundSeqStat *D_801FE138;

void func_80077670(SoundChannel *ch) {
    D_801FE120 = ch->seq[1] | (ch->seq[2] << 8);
    if (D_801FE120 >= 0 && D_801FE120 < ch->label_count) {
        D_801FE138 = &D_80087F9C[ch->unk_00.b[2]];
        D_801FE124 = D_80087FA0->unk_0C->unk_20[D_801FE138->unk_00.h[1]].unk_00;
        D_801FE12C = D_801FE138->unk_04;
        D_801FE130 = D_801FE138->unk_0C;
        while (--D_801FE124 != -1) {
            if (*D_801FE130 != 0xFF) {
                D_801FE134 = &D_80087F98[*D_801FE130];
                *D_801FE134->stack++ = D_801FE134->seq + D_80088364[26];
                D_801FE128 = (u8 *) D_801FE134->labels[D_801FE120];
                D_801FE128 += (s32) D_801FE134->seq_start;
                D_801FE134->seq = D_801FE128;
                D_801FE134->delay = 0;
                D_801FE134->unk_00.w |= 0x40;
                if (--D_801FE12C == 0) {
                    break;
                }
            }
            D_801FE130++;
        }
    }
}

extern s16 D_801FE13C;
extern s16 D_801FE140;
extern u8 *D_801FE144;
extern u8 D_801FE148;
extern u8 *D_801FE14C;
extern SoundChannel *D_801FE150;
extern SoundSeqStat *D_801FE154;

void func_80077848(SoundChannel *ch) {
    D_801FE13C = ch->seq[1] | (ch->seq[2] << 8);
    if (D_801FE13C >= 0 && D_801FE13C < ch->label_count) {
        D_801FE154 = &D_80087F9C[ch->unk_00.b[2]];
        D_801FE140 = D_80087FA0->unk_0C->unk_20[D_801FE154->unk_00.h[1]].unk_00;
        D_801FE148 = D_801FE154->unk_04;
        D_801FE14C = D_801FE154->unk_0C;
        while (--D_801FE140 != -1) {
            if (*D_801FE14C != 0xFF) {
                D_801FE150 = &D_80087F98[*D_801FE14C];
                D_801FE144 = (u8 *) D_801FE150->labels[D_801FE13C];
                D_801FE144 += (s32) D_801FE150->seq_start;
                D_801FE150->seq = D_801FE144;
                D_801FE150->delay = 0;
                D_801FE150->unk_00.w |= 0x40;
                if (--D_801FE148 == 0) {
                    break;
                }
            }
            D_801FE14C++;
        }
    }
}

extern s16 D_801FE158;
extern u8 D_801FE15C;
extern u8 *D_801FE160;
extern SoundChannel *D_801FE164;
extern SoundSeqStat *D_801FE168;

void func_800779E8(SoundChannel *ch) {
    D_801FE168 = &D_80087F9C[ch->unk_00.b[2]];
    D_801FE158 = D_80087FA0->unk_0C->unk_20[D_801FE168->unk_00.h[1]].unk_00;
    D_801FE15C = D_801FE168->unk_04;
    D_801FE160 = D_801FE168->unk_0C;
    while (--D_801FE158 != -1) {
        if (*D_801FE160 != 0xFF) {
            D_801FE164 = &D_80087F98[*D_801FE160];
            D_801FE164->stack--;
            D_801FE164->seq = *D_801FE164->stack;
            D_801FE164->delay = 0;
            D_801FE164->unk_00.w |= 0x40;
            if (--D_801FE15C == 0) {
                break;
            }
        }
        D_801FE160++;
    }
}

extern SoundSeqStat *D_801FE16C;
extern SoundChannel *D_801FE170;
extern u8 *D_801FE174;
extern s32 D_801FE178;
extern s32 D_801FE17C;

void func_80077B2C(SoundChannel *ch) {
    if (!(ch->unk_00.w & 4)) {
        D_801FE16C = &D_80087FA0->unk_18[ch->unk_00.b[2]];
        D_801FE178 = D_801FE16C->unk_04;
        D_801FE17C = D_80087FA0->unk_0A;
        D_801FE174 = D_801FE16C->unk_0C;
        while (--D_801FE17C != -1) {
            if (*D_801FE174 != 0xFF) {
                D_801FE170 = &D_80087F98[*D_801FE174];
                D_80087130[D_801FE170->cmd_set][5](D_801FE170);
                if (--D_801FE178 == 0) {
                    break;
                }
            }
            D_801FE174++;
        }
    } else {
        D_801FE16C = &D_80087FA0->unk_18[ch->unk_00.b[2]];
        D_801FE178 = D_801FE16C->unk_04;
        D_801FE17C = D_80087FA0->unk_0A;
        D_801FE174 = D_801FE16C->unk_0C;
        while (--D_801FE17C != -1) {
            if (*D_801FE174 != 0xFF) {
                D_801FE170 = &D_80087F98[*D_801FE174];
                D_80087130[D_801FE170->cmd_set][5](D_801FE170);
                if (--D_801FE178 == 0) {
                    break;
                }
            }
            D_801FE174++;
        }
        ch->unk_00.w |= 0x40;
    }
}


void func_80077DC4(SoundChannel *ch) {
    u8 *p;

    p = ch->seq;
    ch->tempo = p[1] | (p[2] << 8);
    ch->tick_step = func_80070588(func_8007050C(), ch->ppq, ch->tempo);
}

void func_80077E20(SoundChannel *ch) {
    s16 label;

    label = ch->seq[1] | (ch->seq[2] << 8);
    if (label >= 0 && label < ch->label_count) {
        *ch->stack++ = ch->seq + D_80088364[26];
        ch->seq = (u8 *) (ch->labels[label] + (s32) ch->seq_start);
        ch->delay = 0;
        ch->unk_00.w |= 0x40;
    }
}

void func_80077EBC(SoundChannel *ch) {
    s16 label;

    label = ch->seq[1] | (ch->seq[2] << 8);
    if (label >= 0 && label < ch->label_count) {
        ch->seq = (u8 *) (ch->labels[label] + (s32) ch->seq_start);
        ch->delay = 0;
        ch->unk_00.w |= 0x40;
    }
}

void func_80077F2C(SoundChannel *ch) {
    u8 **sp;
    u8 *seq;

    sp = ch->stack;
    ch->stack = sp - 1;
    seq = sp[-1];
    ch->seq = seq;
    ch->seq = func_80076C8C(seq, &ch->delay);
    ch->delay = 0;
    ch->unk_00.w |= 0x40;
}

void func_80077F84(SoundChannel *ch) {
    if (!(ch->unk_00.w & 4)) {
        if (!(ch->unk_00.w & 0x20) || ch->elapsed < 0x10) {
            D_80087130[ch->cmd_set][5](ch);
        } else {
            ch->unk_00.w |= 0x40;
            ch->seq = ch->seq_start;
            ch->seq = func_80076C8C(ch->seq, &ch->delay);
        }
    } else if ((ch->unk_00.w & 0x20) && ch->elapsed >= 0x10) {
        ch->unk_00.w |= 0x40;
        ch->seq = ch->seq_start;
        ch->seq = func_80076C8C(ch->seq, &ch->delay);
    } else {
        D_80087130[ch->cmd_set][5](ch);
        ch->unk_00.w |= 0x40;
    }
}

void func_80078080(void) {
}

extern SoundChannel *D_801FE180;
extern u8 D_801FE184;
extern s32 D_801FE188;
extern s32 D_801FE18C;

void func_80078088(void) {
    D_801FE184 = D_80087FA0->unk_05;
    if (D_801FE184 != 0) {
        D_801FE180 = D_80087F98;
        D_801FE188 = D_80087F94;
        while (--D_801FE188 != -1) {
            if (D_801FE180->unk_00.w & 1) {
                if (!(D_801FE180->unk_00.w & 8)) {
                    D_801FE180->accum += D_801FE180->tick_step;
                    D_801FE180->elapsed += D_801FE180->accum >> 16;
                    D_801FE180->delay_time += D_801FE180->accum >> 16;
                    D_801FE180->accum &= 0xFFFF;
                    if ((D_801FE180->unk_00.w & 0x10) && D_801FE180->end_time <= D_801FE180->elapsed) {
                        D_80087130[D_801FE180->cmd_set][5](D_801FE180);
                    } else {
                        while (D_801FE180->delay <= D_801FE180->delay_time && (D_801FE180->unk_00.w & 9) == 1) {
                            D_801FE180->delay_time -= D_801FE180->delay;
                            D_801FE18C = *D_801FE180->seq;
                            if (D_801FE18C >= 7 && D_801FE18C < 19) {
                                D_80087130[D_801FE180->cmd_set][D_801FE18C](D_801FE180);
                                D_801FE180->seq += D_80088364[D_801FE18C];
                                D_801FE180->seq = func_80076C8C(D_801FE180->seq, &D_801FE180->delay);
                            } else if (D_801FE18C >= 19 && D_801FE18C < 36) {
                                D_80087F00[D_801FE18C](D_801FE180);
                                if ((D_801FE180->unk_00.w & 0x41) == 1) {
                                    D_801FE180->seq += D_80088364[D_801FE18C];
                                    D_801FE180->seq = func_80076C8C(D_801FE180->seq, &D_801FE180->delay);
                                } else {
                                    D_801FE180->unk_00.w &= ~0x40;
                                }
                            } else {
                                D_80087F00[29](D_801FE180);
                            }
                        }
                    }
                }
                if (--D_801FE184 == 0) {
                    break;
                }
            }
            D_801FE180++;
        }
    }
    D_80087130[D_80087F98->cmd_set][2](D_80087F98);
}
