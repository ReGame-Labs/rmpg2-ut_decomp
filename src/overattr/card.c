/* OVERLAYS/OVERATTR.BIN, the memory-card file: the MemCard* calls on the save file BASLUS-00742RAMPAGE, its
 * header and the title in Shift-JIS (config/overattr.yaml). */
#include "common.h"
#include "overattr.h"
#include "psyq/libmcrd.h"
#include "psyq/libc2.h"

s32 card_get_status(void) {
    long cmd;
    long result;
    s32 chan;

    chan = 0;
    for (;;) {
        switch (MemCardSync(1, &cmd, &result)) {
        case 0:
            break;
        case -1:
            MemCardExist(chan);
            break;
        case 1:
            switch (cmd) {
            case 1:
                if (result == 0 || result == 3) {
                    MemCardAccept(chan);
                    break;
                }
                return 1;
            case 2:
                switch (result) {
                case 0:
                    return 0;
                case 3:
                    MemCardAccept(chan);
                    break;
                case 4:
                    return 2;
                default:
                    return 1;
                }
                break;
            }
            break;
        }
    }
}

s32 card_read_save(CardSave *save) {
    long cmd;
    long result;
    s32 state;
    s32 retries;
    s32 chan;

    state = 0;
    chan = 0;
    retries = 0;
    for (;;) {
        switch (state) {
        case 0:
            switch (MemCardSync(1, &cmd, &result)) {
            case 0:
                break;
            case -1:
                MemCardExist(chan);
                break;
            case 1:
                switch (cmd) {
                case 1:
                    if (result == 0 || result == 3) {
                        MemCardAccept(chan);
                        break;
                    }
                    return 1;
                case 2:
                    switch (result) {
                    case 0:
                        state = 1;
                        break;
                    case 3:
                        MemCardAccept(chan);
                        break;
                    case 4:
                        return 2;
                    default:
                        return 1;
                    }
                    break;
                }
                break;
            }
            break;
        case 1:
            MemCardReadFile(chan, "BASLUS-00742RAMPAGE", save, 0, 0x500);
            MemCardSync(0, &cmd, &result);
            switch (result) {
            case 0:
                return (card_calc_checksum(save) != save->checksum) ? 4 : 0;
            case 2:
                if (++retries >= 7) {
                    return 1;
                }
                state = 0;
                break;
            case 1:
                return 1;
            case 3:
                state = 0;
                break;
            case 5:
                card_init_save(save);
                return 6;
            }
            break;
        }
    }
}

s32 card_write_save(CardSave *save) {
    long cmd;
    long result;
    s32 retries;
    s32 state;
    s32 chan;

    state = 0;
    chan = 0;
    retries = 0;
    for (;;) {
        switch (state) {
        case 0:
            switch (MemCardSync(1, &cmd, &result)) {
            case 0:
                break;
            case -1:
                MemCardExist(chan);
                break;
            case 1:
                switch (cmd) {
                case 1:
                    if (result == 0 || result == 3) {
                        MemCardAccept(chan);
                        break;
                    }
                    return 1;
                case 2:
                    switch (result) {
                    case 0:
                    case 3:
                        state = 1;
                        retries = 0;
                        break;
                    case 4:
                        if (++retries >= 7) {
                            return 2;
                        }
                        MemCardAccept(chan);
                        break;
                    default:
                        return 1;
                    }
                    break;
                }
                break;
            }
            break;
        case 1:
            switch (result = MemCardCreateFile(chan, "BASLUS-00742RAMPAGE", 1)) {
            case 0:
            case 6:
                state = 2;
                retries = 0;
                break;
            case 1:
                state = 0;
                retries = 0;
                break;
            case 2:
            case 7:
                if (++retries >= 7) {
                    return 3;
                }
                break;
            case 4:
                if (++retries >= 7) {
                    return 2;
                }
                break;
            }
            break;
        case 2:
            MemCardWriteFile(chan, "BASLUS-00742RAMPAGE", save, 0, 0x500);
            MemCardSync(0, &cmd, &result);
            switch (result) {
            case 0:
                return 0;
            case 4:
                if (++retries >= 7) {
                    return 2;
                }
                break;
            case 5:
                state = 1;
                retries = 0;
                break;
            case 1:
            case 2:
            case 3:
            default:
                if (++retries >= 7) {
                    return 1;
                }
                break;
            }
            break;
        }
    }
}

s32 card_format(void) {
    long cmd;
    long result;
    s32 state;
    s32 retries;
    s32 chan;

    state = 0;
    chan = 0;
    retries = 0;
    for (;;) {
        switch (state) {
        case 0:
            switch (MemCardSync(1, &cmd, &result)) {
            case 0:
                break;
            case -1:
                MemCardExist(chan);
                break;
            case 1:
                switch (cmd) {
                case 1:
                    switch (result) {
                    case 0:
                        MemCardAccept(chan);
                        break;
                    case 3:
                        return 5;
                    default:
                        return 1;
                    }
                    break;
                case 2:
                    switch (result) {
                    case 0:
                    case 3:
                        return 5;
                    case 4:
                        state = 1;
                        break;
                    default:
                        return 1;
                    }
                    break;
                }
                break;
            }
            break;
        case 1:
            switch (result = MemCardFormat(chan)) {
            case 0:
                return 0;
            case 1:
                return 1;
            case 2:
            default:
                if (++retries >= 7) {
                    return 1;
                }
                state = 0;
                break;
            }
            break;
        }
    }
}

s32 card_calc_checksum(CardSave *save) {
    s32 sum;
    u32 i;
    s32 saved;

    sum = 0;
    saved = save->checksum;
    save->checksum = 0;
    for (i = 0; i < 0x140; i++) {
        sum ^= ((s32 *) save)[i];
    }
    save->checksum = saved;
    return sum;
}

void card_init_save(CardSave *save) {
    s32 i;

    memset(save, 0, 0x500);
    save->magic[0] = 'S';
    save->magic[1] = 'C';
    save->icon_type = 0x11;
    save->blocks = 1;
    card_string_to_sjis(save->title, "RAMPAGE 2: UNIVERSAL TOUR       ");
    save->clut = D_800A33E0;
    save->icon = D_800A3360;
    save->unk_200 = 0;
    for (i = 0; i < 6; i++) {
        save->unk_204[i] = 1;
    }
    save->checksum = card_calc_checksum(save);
}

#ifdef NON_MATCHING
/* 99.2 %: the punctuation table's address and the index swap v0/v1. */
s16 card_ascii_to_sjis(u8 c) {
    s32 run;
    u8 skip;
    s32 code;
    s32 first;

    run = 0;
    skip = 0;
    if ((u8) (c - ' ') < 16) {
        skip = 1;
    } else if ((u8) (c - '0') < 10) {
    } else if ((u8) (c - ':') < 7) {
        skip = 11;
    } else if ((u8) (c - 'A') < 26) {
        run = 1;
    } else if ((u8) (c - '[') < 6) {
        skip = 37;
    } else if ((u8) (c - 'a') < 26) {
        run = 2;
    } else if ((u8) (c - '{') < 4) {
        skip = 63;
    } else {
        return 0;
    }
    if (skip != 0) {
        first = skip + 0x1F;
        code = D_800A340C[c - first];
    } else {
        code = D_800A3400[run].sjis + c - D_800A3400[run].ascii;
    }
    return ((code & 0xFF) << 8) | ((code & 0xFF00) >> 8);
}
#else
INCLUDE_ASM("asm/overattr/nonmatchings/card", card_ascii_to_sjis);
#endif

void card_string_to_sjis(s16 *dst, u8 *src) {
    while (*src != 0) {
        *dst++ = card_ascii_to_sjis(*src++);
    }
}
