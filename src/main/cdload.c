/* The CD file reader (by index into the file table, with a checksum) and the overlay loader; docs/DISC_LAYOUT.md.
 * Also: a stdio emulation over the loaded file (what the sound driver reads its banks with), the unpackers of packed
 * files, the SPU upload of sound banks and the XA music player.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "cdload.h"
#include "sound.h"
#include "psyq/libapi.h"
#include "psyq/libc2.h"
#include "psyq/libcd.h"
#include "psyq/libetc.h"
#include "psyq/libgpu.h"
#include "psyq/libspu.h"

void func_8002958C(void);
ObjectDef *func_8001D110(void);
void func_8001DCB4(void);
void func_800415B4(void);
void func_8001B5E8(s32);
void cdload_stop_xa(s32);
s32 cdload_play_xa(u32);
void cdload_on_xa_ready(s32);
void func_80063E48(s32, s32);
s32 func_80063F30(void);
void func_800700CC(u8);
void func_80063DF8(s32);
void func_8006FC6C(void);
void func_8006FC8C(s32, s32 *);
void func_8006FEB4(s32);
void func_800700A8(void);
void func_8006BBA0(s32, s32);
void func_8006BD60(s32);
void func_8006C8D8(s32, s32);
s32 func_8006C8B4(s32);
s32 func_8006C8F8(s32);
s16 func_8006EC18(void);
s32 cdload_load_bank(s32, s32, s32, s32, s32, s32, s32);


/* The VLC image format (cdload_unpack method 5): a header of code tables, then the bit stream. Each table holds the
 * code lengths and bases of 13 literal codes (an index into the table's 8-byte pixel pairs) and 3 run codes (a run of
 * zero pairs); the decoder copies the chosen table into the scratchpad. */
typedef struct {
    u16 len[13];
} VlcLens;
typedef struct {
    u16 len[3];
} VlcRunLens;
typedef struct {
    s32 base[13];
} VlcBases;
typedef struct {
    s32 base[3];
} VlcRunBases;

typedef struct {
    s32 values;             /* the pixel pairs, from the end of the tables */
    u16 depth;              /* bits per pixel: 8 takes cdload_unpack_vlc8 */
    VlcLens lens;
    VlcRunLens run_lens;
    VlcBases bases;
    VlcRunBases run_bases;
} VlcTable;                 /* 0x68 */

typedef struct {
    u16 rows;               /* rows written per code */
    u16 count;
    VlcTable tables[1];     /* [count], picked by the stream's first 6 bits */
} VlcHeader;

/* The loaded file: its index, its data (the read buffer) and the read position (the fopen/fread emulation). */
extern s32 D_801FB4AC;
extern u8 *D_801FB4B0;
extern s32 D_801FB4B4;

/* The SPU upload's two sector buffers. */
extern u8 D_801C41C0[0x800];
/* A sound bank file's first sector: its sample count, then the sample numbers. */
typedef struct {
    s16 count;
    u16 ids[0x3FF];
} SoundBankHeader;
extern SoundBankHeader D_801C49C0;
extern s32 D_801FB4A8;
extern s32 D_801FB4B8;

extern u16 D_801D8728;   /* not in game.h: read unsigned here and in main.c, signed in actor.c */

/* The city file tables (in the .data before this file's), indexed by the city byte: the first is the identity from
 * 0x54, the three others five files each. */
extern u8 D_800851CC[];
extern u8 D_8008524C[];
extern u8 D_80085254[];
extern u8 D_8008525C[];

/* The city file table per D_801D8728. */
u8 *D_80085264[] = { D_800851CC, D_8008524C, D_80085254, D_8008525C };
/* The overlays' file indices: OVERATTR.BIN, OVERMOVE.BIN. */
u8 D_80085274[] = { 0x52, 0x53 };
/* The loaded overlay and city table, -1 for none. */
s32 D_80085278 = -1;
s32 D_8008527C = -1;
extern u8 *D_80016AC8;
extern u8 *D_80016ACC;

extern s32 D_801D3710;
extern s32 D_801D3764;          /* the data-ready callback the XA player replaced, -1 for none */
extern CdlFILTER D_801FB4BC;
extern s32 D_8008A334[];        /* per XA track: its length (D_801E2A48 while it plays) */
extern s32 D_801E2A48;
extern s32 D_801E28EC;
extern s32 D_801E0D48;
extern s32 D_801F991C;
extern s32 D_801FB4C0;


s32 func_8006EE30(s32);
void func_8006F0D8(s32, void *, s32);
s32 func_8006E804(SoundDriver *, s32);
void func_8006E8B4(void *, s32, s32, void *, s32);
SoundDriver *func_8006EC08(void);
s32 func_8006E4F4(void);
s32 func_80070298(s32, s32);
s32 func_80070324(s32, s32, void *);
void *cdload_alloc(s32 size);
void func_80062EB0(void);
void cdload_reset_xa(void);
s32 cdload_read(void *buf, s32 size, s32 count, s32 handle);
s32 cdload_seek(s32 handle, s32 pos);
s32 cdload_size(void);
s32 cdload_close(s32 handle);
s32 cdload_load_spu(s32 handle, s32 spuAddr, s32 size);
s32 cdload_open(s32 index, s32 mode);
s32 cdload_load_bank_by_number(s32 index, s32 spuAddr);
s32 cdload_unpack_rle8(u8 *src, u8 *dst);
s32 cdload_unpack_rle16(u8 *src, u8 *dst);
s32 cdload_unpack_rle6(u8 *src, u8 *dst);
s32 cdload_unpack_rle4(u8 *src, u8 *dst);
void cdload_unpack_vlc(VlcHeader *hdr, u32 *bits, u32 dims, u8 *dst);

/* Lists the players of the monsters in D_801FB49C, sorted, 99 for none. */
void cdload_sort_players(void) {
    s32 m;
    s32 i;
    s32 j;
    s32 n;

    func_8002958C();
    D_801FB49C[0] = D_801FB49C[1] = D_801FB49C[2] = 99;
    n = 0;
    for (m = 0; m < 7; m++) {
        if (D_801FA8A0[m] != 0) {
            D_801FB49C[n++] = D_801FA8A0[m];
        }
    }
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            s32 a = D_801FB49C[j];
            s32 b = D_801FB49C[j + 1];
            if (b < a) {
                D_801FB49C[j] = b;
                D_801FB49C[j + 1] = a;
            }
        }
    }
}

s32 cdload_get_next_player(s32 arg0) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (arg0 == D_801FB49C[i]) {
            return D_801FB49C[i + 1];
        }
    }
    return D_801FB49C[0];
}

void func_80061068(s32 *arg0, s16 arg1, s16 arg2) {
    ObjectDef *def;
    GameObject *saved;

    saved = D_800AA248.cur_obj;
    def = func_8001D110();
    D_800AA248.new_def = def;
    def->pos_x.s.hi = arg1;
    def->pos_y.s.hi = arg2;
    def->flags = 0x7000;
    def->anim = arg0;
    def->id = *arg0;
    func_8001DCB4();
    D_800AA248.cur_obj = saved;
}

void func_800610E8(void) {
}

void func_800610F0(void) {
    D_800AA268.p->priority = *D_800AA268.p->arg.w;
}

void func_80061110(void) {
    D_800AA268.p->pos_y.w = 0x02000000;
    func_800415B4();
}

void func_8006113C(void) {
    D_800AA268.p->owner.monster->meter.u.hi = 1;
}

void func_80061158(void) {
    D_800AA268.p->owner.monster->meter.u.hi = 0;
}

s32 cdload_file_size(s32 index) {
    return D_80089DA0[index];
}

/* Reads file `index` of the file table into buf, retrying until its checksum is right; returns its size. */
s32 cdload_read_file(s32 index, u8 *buf) {
    u8 param[8];
    s32 size;
    u32 sectors;
    s32 tries;
    s32 err;

retry:
    for (;;) {
        size = D_80089DA0[index];
        sectors = (u32)(size + 0x7FF) >> 11;
        if (D_801E28EC != 0 || D_801D3710 != 0) {
            cdload_stop_xa(1);
        }
        if (cdload_wait_sync() == 0) {
            CdReset(0);
        }
        tries = 5;
        do {
            param[0] = CdlModeSpeed;
            param[1] = 1;
            err = CdControl(CdlSetmode, param, NULL) == 0;
            if (!err && cdload_wait_sync() == 0) {
                err = 1;
            }
            VSync(3);
            if (!err && CdControl(CdlSetloc, (u8 *)&D_80089820[index], param) == 0) {
                err = 1;
            }
            if (!err && cdload_wait_sync() == 0) {
                err = 1;
            }
            if (!err && CdRead(sectors, (u32 *)buf, 0x80) == 0) {
                err = 1;
            }
            if (!err && cdload_wait_read_sync() == 0) {
                err = 1;
            }
            if (!err) {
                if (cdload_checksum(buf, size) == D_80010000[index]) {
                    return size;
                }
                err = 2;
            }
            CdReset(0);
            tries--;
            cdload_wait_sync();
        } while (tries != 0);
        VSync(3);
        if (err) {
            goto retry;
        }
        if (CdControl(CdlSetloc, (u8 *)D_80089820, param) == 0) {
            err = 1;
        }
        if (!err) {
            cdload_wait_sync();
        }
    }
}

s32 cdload_wait_sync(void) {
    u8 result[8];
    s32 r;
    s32 tries;

    tries = 600;
    do {
        r = CdSync(1, result);
        if (r == 0) {
            VSync(0);
        } else {
            return r == CdlComplete;
        }
    } while (--tries != 0);
    return 0;
}

s32 cdload_open(s32 index, s32 mode) {
    D_801FB4AC = index;
    D_801FB4B4 = 0;
    D_801FB4B0 = D_801E1C78;
    cdload_read_file(index, D_801E1C78);
    return index;
}

s32 cdload_read(void *buf, s32 size, s32 count, s32 handle) {
    s32 len;

    if (handle == -1) {
        return 0;
    }
    len = size * count;
    memcpy(buf, D_801FB4B0 + D_801FB4B4, len);
    D_801FB4B4 += len;
    return len;
}

s32 cdload_close(s32 handle) {
    return handle != -1;
}

s32 cdload_size(void) {
    return D_80089DA0[D_801FB4AC];
}

s32 cdload_seek(s32 handle, s32 pos) {
    D_801FB4B4 = pos;
    return 0;
}

s32 cdload_wait_read_sync(void) {
    u8 result[8];
    s32 r;
    s32 last;
    s32 tries;

    tries = 0x800000;
    last = 99999;
    do {
        r = CdReadSync(1, result);
        if (r == 0) {
            return 1;
        }
        if (r < 0) {
            return 0;
        }
        if (r >= last) {
            tries--;
        }
        last = r;
        VSync(0);
    } while (tries != 0);
    return 0;
}

s32 cdload_checksum(u8 *buf, s32 len) {
    s32 sum;
    s32 rem;
    u8 *pad;
    u32 i;
    u32 n;

    sum = 0;
    rem = len & 3;
    len = (len + 3) & ~3;
    if (rem != 0) {
        pad = buf + len;
        switch (rem) {
        case 1:
            *pad++ = 0;
        case 2:
            *pad++ = 0;
        case 3:
            *pad = 0;
        }
    }
    n = (u32)len >> 2;
    for (i = 0; i < n; i++) {
        sum ^= *(s32 *)buf;
        buf += 4;
    }
    return sum;
}

/* The file index of the current city's data: two files per city from 0x54, in the order of the city byte. */
s32 cdload_city_file_index(s32 which) {
    s32 offset;
    u8 *p;
    s32 pair;
    s32 file;

    offset = (s32)D_80085264[D_801D8728];   /* the index is added to the address as an integer */
    if (D_801D8728 != 0) {
        p = (u8 *)((u16) D_801FA964 + offset);   /* unsigned here (lhu), as D_801FA960 below */
    } else {
        p = (u8 *)((u16) D_801FA960 + offset);   /* an unsigned read here (lhu); game.h declares it s16 */
    }
    file = *p;
    pair = (file - 0x54) * 2;
    file = pair + 0x54;
    if (which != 1) {
        file = pair + 0x55;
    }
    return file;
}

void cdload_write_spu(s32 handle, s32 len, s32 spuAddr) {
    u8 *buf;
    u8 *prev;

    buf = D_801C41C0;
    prev = D_801C41C0 - 0x800;
    if (D_801FB4B8 != 0) {
        cdload_read(buf, len, 1, handle);
        SpuSetTransferStartAddr(spuAddr);
        SpuWrite(buf, len);
        D_801FB4A8 = 1;
        D_801FB4B8 = 0;
    } else if (D_801FB4A8 != 0) {
        cdload_read(prev, len, 1, handle);
        SpuIsTransferCompleted(SPU_TRANSFER_WAIT);
        SpuSetTransferStartAddr(spuAddr);
        SpuWrite(prev, len);
        D_801FB4A8 = 0;
    } else {
        cdload_read(buf, len, 1, handle);
        SpuIsTransferCompleted(SPU_TRANSFER_WAIT);
        SpuSetTransferStartAddr(spuAddr);
        SpuWrite(buf, len);
        D_801FB4A8 = 1;
    }
}

s32 cdload_load_spu(s32 handle, s32 spuAddr, s32 size) {
    s32 left;
    s32 addr;

    left = size;
    addr = spuAddr;
    D_801FB4B8 = 1;
    while (left >= 0x800) {
        cdload_write_spu(handle, 0x800, addr);
        left -= 0x800;
        addr += 0x800;
    }
    if (left != 0) {
        cdload_write_spu(handle, left, addr);
    }
    SpuIsTransferCompleted(SPU_TRANSFER_WAIT);
    return size;
}

void cdload_load_overlay(s32 n) {
    s32 tries;
    s32 size;

    if (n == D_80085278) {
        return;
    }
    if (n == 2) {
        D_80085278 = n;
        return;
    }
    DrawSync(0);
    VSync(0);
    DrawSync(0);
    tries = 3;
    EnterCriticalSection();
    FlushCache();
    ExitCriticalSection();
    do {
        size = cdload_read_file(D_80085274[n], D_801E1C78);
    } while (size == 0 && --tries > 0);
    if (size == 0) {
        func_8001B5E8(1);
    } else {
        memcpy(D_80016AC8, D_801E1C78, size);
    }
    D_80085278 = n;
}

void cdload_load_city_table(s32 index) {
    s32 tries;
    s32 size;

    DrawSync(0);
    VSync(0);
    DrawSync(0);
    tries = 3;
    EnterCriticalSection();
    FlushCache();
    ExitCriticalSection();
    do {
        size = cdload_read_file(index, D_801E1C78);
    } while (size == 0 && --tries > 0);
    if (size == 0) {
        func_8001B5E8(1);
    } else {
        memcpy(D_80016ACC, D_801E1C78, size);
    }
    D_8008527C = index;
}

/* Unpacks a packed file into dst by the method in the low nibble of its byte 3; returns the unpacked size. */
s32 cdload_unpack(u8 *dst, s32 arg1, u8 *src) {
    s32 size;
    s32 w;
    s32 h;

    switch ((*(s32 *)src >> 24) & 0xF) {
    case 0:
        size = *(u32 *)src & 0xFFFFFF;
        memcpy(dst, src + 4, size);
        return size;
    case 1:
        return cdload_unpack_rle8(src, dst);
    case 2:
        return cdload_unpack_rle16(src, dst);
    case 3:
        return cdload_unpack_rle6(src, dst);
    case 4:
        return cdload_unpack_rle4(src, dst);
    case 5:
        cdload_unpack_vlc((VlcHeader *)(src + ((s32 *)src)[1]), (u32 *)(src + 12), ((u32 *)src)[2], dst);
        w = ((u32 *)src)[2] & 0xFFFF;
        h = ((u32 *)src)[2] >> 16;
        w = (w + 3) & ~3;
        h = (h + 1) & ~1;
        return w * h;
    }
    return 0;
}

s32 cdload_unpack_rle8(u8 *src, u8 *dst) {
    s8 *in;
    u8 *out;
    u8 *end;
    s32 n;
    u8 b;

    out = dst;
    in = (s8 *)(src + 4);
    end = dst + (*(u32 *)src & 0xFFFFFF);
    while (out < end) {
        n = *in++;
        if (n < 0) {
            b = *(u8 *)in;
            in++;
            do {
                *out++ = b;
            } while (++n <= 0);
        } else {
            do {
                *out++ = *(u8 *)in;
                in++;
            } while (--n >= 0);
        }
    }
    return out - dst;
}

/* Unpacks a halfword RLE stream: a halfword without bit 15 is copied; one with it is a run of the colour in bits 9-14
 * (spread over both 5-bit fields' top bits), its length in bytes in bits 0-8. The runs are written 32 halfwords per loop,
 * entered through a computed goto (the table, a static, is in .data). */
/* Unpacks a halfword RLE stream: a halfword without bit 15 is copied; one with it is a run of the colour in bits 9-14
 * (spread over both 5-bit fields' top bits), its length in bytes in bits 0-8. The runs are written 32 halfwords per loop,
 * entered through a computed goto (the table, a static, is in .data). */
s32 cdload_unpack_rle16(u8 *src, u8 *dst) {
    static void *runs[32] = {
        &&run1, &&run2, &&run3, &&run4, &&run5, &&run6, &&run7, &&run8,
        &&run9, &&run10, &&run11, &&run12, &&run13, &&run14, &&run15, &&run16,
        &&run17, &&run18, &&run19, &&run20, &&run21, &&run22, &&run23, &&run24,
        &&run25, &&run26, &&run27, &&run28, &&run29, &&run30, &&run31, &&run32,
    };
    u16 *in;
    u16 *end;
    u16 *out;
    u16 code;
    s32 loops;
    s32 len;
    s32 n;
    s16 c;

    in = (u16 *)src;
    end = (u16 *)(src + (*(u32 *)src & 0xFFFFFF));
    out = (u16 *)dst;
    in += 2;
    while (in < end) {
        code = *in++;
        if (code & 0x8000) {
            len = (s16)(code & 0x1FF);
            c = code & 0x7E00;
            code = (c >> 1) | (c >> 9);
            loops = len >> 6;
            n = len & 0x3F;
            if (n == 0) {
                n = 0x40;
                loops--;
            }
            goto *runs[(n >> 1) - 1];
            do {
            run32:
                *out++ = code;
            run31:
                *out++ = code;
            run30:
                *out++ = code;
            run29:
                *out++ = code;
            run28:
                *out++ = code;
            run27:
                *out++ = code;
            run26:
                *out++ = code;
            run25:
                *out++ = code;
            run24:
                *out++ = code;
            run23:
                *out++ = code;
            run22:
                *out++ = code;
            run21:
                *out++ = code;
            run20:
                *out++ = code;
            run19:
                *out++ = code;
            run18:
                *out++ = code;
            run17:
                *out++ = code;
            run16:
                *out++ = code;
            run15:
                *out++ = code;
            run14:
                *out++ = code;
            run13:
                *out++ = code;
            run12:
                *out++ = code;
            run11:
                *out++ = code;
            run10:
                *out++ = code;
            run9:
                *out++ = code;
            run8:
                *out++ = code;
            run7:
                *out++ = code;
            run6:
                *out++ = code;
            run5:
                *out++ = code;
            run4:
                *out++ = code;
            run3:
                *out++ = code;
            run2:
                *out++ = code;
            run1:
                *out++ = code;
            } while (--loops != -1);
        } else {
                *out++ = code;
        }
    }
    return (u8 *)out - dst;
}

/* Takes the next 6-bit symbol of the stream: four per three bytes, most significant first. */
#define CDLOAD_GET6(x)                          \
    switch (phase++) {                          \
    case 0:                                     \
        b0 = *src++;                            \
        b1 = *src++;                            \
        b2 = *src++;                            \
        x = b0 >> 2;                            \
        break;                                  \
    case 1:                                     \
        x = (b1 >> 4) | ((b0 << 4) & 0x30);     \
        break;                                  \
    case 2:                                     \
        x = ((b1 << 2) & 0x3C) | (b2 >> 6);     \
        break;                                  \
    case 3:                                     \
        x = b2 & 0x3F;                          \
        phase = 0;                              \
        break;                                  \
    }

/* Unpacks a 6-bit RLE stream: a symbol below 32 repeats the next one that many times plus one, a symbol from 32
 * copies that many minus 31 symbols; the top two bits of byte 3 count the padding symbols at the end. */
s32 cdload_unpack_rle6(u8 *src, u8 *dst) {
    u8 *start;
    s32 count;
    s32 phase;
    s32 code;
    s32 value;
    u32 b0;
    u32 b1;
    u32 b2;

    start = dst;
    code = 0;
    value = code;
    b0 = code;
    b1 = code;
    b2 = code;
    count = (*(u32 *)src & 0xFFFFFF) - 4;
    count = count + count / 3 - (src[3] >> 6);
    src += 4;
    phase = code;
    while (count > 0) {
        CDLOAD_GET6(code);
        if (code < 32) {
            CDLOAD_GET6(value);
            count -= 2;
            for (; code >= 0; code--) {
                *dst++ = value;
            }
        } else {
            code -= 32;
            count -= code + 2;
            for (; code >= 0; code--) {
                CDLOAD_GET6(*dst++);
            }
        }
    }
    return dst - start;
}

/* Puts a 4-bit value into the output, two per byte, low nibble first. */
#define CDLOAD_PUT4(x)              \
    acc |= (x) << (half * 4);       \
    half ^= 1;                      \
    if (half == 0) {                \
        *dst++ = acc;               \
        acc = 0;                    \
    }

/* Unpacks a 4-bit RLE stream: 0x80 | n is n + 7 zeros, 0x0v n a run of n v, 0x1v-0x6v one to six v, 0x7n n + 3
 * nibbles packed two per byte, high first. */
s32 cdload_unpack_rle4(u8 *src, u8 *dst) {
    u8 *start;
    u8 *end;
    s32 half;
    u8 acc;
    s32 n;
    u8 c;

    start = dst;
    end = dst + ((s32)(*(u32 *)src & 0xFFFFFF) >> 1);
    src += 4;
    half = 0;
    acc = half;
    while (dst < end) {
        c = *src++;
        if (c & 0x80) {
            s32 zeros;

            for (zeros = (c & 0x7F) + 7; zeros > 0; zeros--) {
                CDLOAD_PUT4(0);
            }
        } else {
            n = c >> 4;
            c &= 0xF;
            switch (n) {
            case 0:
                for (n = *src++; n > 0; n--) {
                    CDLOAD_PUT4(c);
                }
                break;
            case 7:
                for (n = c + 3; n > 0; n--) {
                    c = *src++;
                    CDLOAD_PUT4(c >> 4);
                    if (--n == 0) {
                        break;
                    }
                    CDLOAD_PUT4(c & 0xF);
                }
                break;
            case 6:
                CDLOAD_PUT4(c);
            case 5:
                CDLOAD_PUT4(c);
            case 4:
                CDLOAD_PUT4(c);
            case 3:
                CDLOAD_PUT4(c);
            case 2:
                CDLOAD_PUT4(c);
            case 1:
                CDLOAD_PUT4(c);
                break;
            }
        }
    }
    return dst - start;
}

INCLUDE_ASM("asm/main/nonmatchings/cdload", cdload_unpack_vlc);

#ifdef NON_MATCHING
/* 95.82%: registers (cur/next/left take t1/t8/t0 for the original's t0/t7/t2) and the count/skip setup
 * order; the table copies match */
void cdload_unpack_vlc8(VlcHeader *hdr, u32 *in, u32 dims, u8 *dst) {
    VlcTable *t;
    u32 cur;
    u32 next;
    s32 left;

    s32 x;

    s32 k;
    u8 *values;
    u8 *row2;
    s32 *e;
    s32 w;
    s32 words;
    s32 count;
    s32 col;
    s32 skip;
    s32 rows;
    VlcLens *lens;
    VlcRunLens *run_lens;
    VlcBases *bases;
    VlcRunBases *run_bases;

    cur = *in++;
    next = *in++;
    left = 26;
    run_lens = (VlcRunLens *)0x1F80001A;
    bases = (VlcBases *)0x1F800020;
    run_bases = (VlcRunBases *)0x1F800054;
    lens = (VlcLens *)0x1F800000;
    rows = hdr->rows;
    t = &hdr->tables[cur >> 26];
    cur <<= 6;
    values = (u8 *)&hdr->tables[hdr->count] + t->values;
    *lens = t->lens;
    *bases = t->bases;
    w = dims & 0xFFFF;
    *run_lens = t->run_lens;
    *run_bases = t->run_bases;
    count = (w / 4) * (((s32)dims >> 16) / rows);
    words = w / 4;
    col = 0;
    skip = (rows - 1) * w;
    do {
            {
                s32 n;
            n = 4;
            x = 0;
            if (left < n) {
                x = cur >> (32 - n);
                cur = next;
                next = *in++;
                n -= left;
                left = 32;
            }
            x |= cur >> (32 - n);
            left -= n;
            cur <<= n;
            }
        if (x >= 13) {
            k = x - 13;
            {
                s32 n;
            n = run_lens->len[k];
            x = 0;
            if (left < n) {
                x = cur >> (32 - n);
                cur = next;
                next = *in++;
                n -= left;
                left = 32;
            }
            x |= cur >> (32 - n);
            left -= n;
            cur <<= n;
            }
            x += run_bases->base[k];
            count = count - 1 - x;
            for (; x >= 0; x--) {
                row2 = dst + w;
                *(s32 *)dst = 0;
                dst += 4;
                col++;
                *(s32 *)row2 = 0;
                if (col == words) {
                    dst += skip;
                    col = 0;
                }
            }
        } else {
            k = x;
            {
                s32 n;
            n = lens->len[k];
            x = 0;
            if (left < n) {
                n -= left;
                left = 32;
                x = cur >> (32 - lens->len[k]);
                cur = next;
                next = *in++;
            }
            x |= cur >> (32 - n);
            left -= n;
            cur <<= n;
            }
            row2 = dst + w;
            e = (s32 *)(values + (x + bases->base[k]) * 8);
            col++;
            *(s32 *)dst = e[0];
            dst += 4;
            *(s32 *)row2 = e[1];
            if (col == words) {
                dst += skip;
                col = 0;
            }
            count--;
        }
    } while (count > 0);
}
#else
INCLUDE_ASM("asm/main/nonmatchings/cdload", cdload_unpack_vlc8);
#endif

/* The bump allocator's arena and its next free byte. */
extern u8 D_800AA94C[0x5208];
u8 *D_80085300 = D_800AA94C;

void *cdload_alloc(s32 size) {
    u8 *p;

    p = (u8 *)(((u32)D_80085300 + 7) & ~7);
    D_80085300 = p + size;
    return p;
}

void cdload_init_sound(void) {
    SoundInit io;
    s32 size;
    s32 bank_size;
    void *buf;
    void *seqs;

    io.open = cdload_open;
    io.read = cdload_read;
    io.seek = cdload_seek;
    io.size = cdload_size;
    io.close = cdload_close;
    io.load_spu = cdload_load_spu;
    io.rate = 0x78;
    io.unk_18 = 0;
    io.unk_1C = 0;
    io.unk_28 = 1;
    io.unk_24 = 1;
    func_800706C0(&io);
    size = func_8006EE30(0x4F);
    func_8006F0D8(0x4F, cdload_alloc(size), size);
    bank_size = func_8006E804(func_8006EC08(), 0x50);
    buf = cdload_alloc(bank_size);
    func_8006E8B4(func_8006EC08(), 0x50, 0, buf, bank_size);
    seqs = cdload_alloc(func_80070298(0, func_8006E4F4()));
    func_80070324(0, func_8006E4F4(), seqs);
    D_801FB4C0 = 0x1010;
    cdload_reset_xa();
    func_80062EB0();
    D_801FB4C0 += cdload_load_bank_by_number(0, D_801FB4C0);
}

void func_80062D88(s32 arg0) {
    func_800700CC(arg0 & 0xFF);
}

void func_80062DA8(s32 arg0) {
    func_80063DF8((arg0 & 0xFF) << 7);
}

void func_80062DCC(void) {
    func_8006FC6C();
}

void func_80062DEC(s32 arg0, s32 arg1) {
    s32 param[6];

    param[0] = 1;
    ((s8 *)param)[4] = arg1 / 2;
    func_8006FC8C(arg0, param);
}

void func_80062E24(s32 arg0) {
    func_8006FEB4(arg0);
}

void func_80062E44(void) {
    func_800700A8();
}

void func_80062E64(void) {
    func_8006BBA0(1, 3);
}

void func_80062E88(void) {
    func_8006BD60(1);
}

void func_80062EA8(void) {
}

void func_80062EB0(void) {
    s32 i;
    s32 n;

    n = func_8006EC18();
    for (i = 0; i < n; i++) {
        func_8006C8D8(i, 0);
    }
    D_801FB4C0 = 0x1010;
}

s32 cdload_load_bank(s32 index, s32 spuAddr, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 reload) {
    s32 handle;
    s32 addr;
    s32 count;
    s32 i;
    s32 id;
    s32 size;

    handle = cdload_open(index, 0);
    cdload_read(&D_801C49C0, 1, 0x800, handle);
    addr = spuAddr;
    count = D_801C49C0.count;
    for (i = 0; i < count; i++) {
        id = D_801C49C0.ids[i];
        if (func_8006C8F8(id) == 0 || reload != 0) {
            size = func_8006C8B4(id);
            cdload_load_spu(handle, addr, size);
            func_8006C8D8(id, addr);
            addr += size;
        }
    }
    cdload_close(handle);
    return addr - spuAddr;
}

/* The bank file per bank number. */
s16 D_80085304[] = { 0x51 };

s32 cdload_load_bank_by_number(s32 index, s32 spuAddr) {
    return cdload_load_bank(D_80085304[index], spuAddr, 0, 0, 0, 500, 0);
}

void cdload_reset_xa(void) {
    D_801E28EC = 0;
    D_801D3710 = 0;
    D_801D3764 = -1;
}

s32 func_80063084(s32 arg0) {
    if (D_801E28EC != 0) {
        return -1;
    }
    if (D_801D3710 != 0) {
        CdControl(9, NULL, NULL);
        cdload_wait_sync();
    }
    return cdload_play_xa(arg0);
}

void cdload_stop_xa(s32 mode) {
    s32 i;

    if (mode == 1) {
        for (i = 60; i != 0; i--) {
            VSync(0);
        }
        if (cdload_wait_sync() == 0) {
            CdReset(0);
        }
    }
    CdControl(CdlPause, NULL, NULL);
    if (mode == 1 && cdload_wait_sync() == 0) {
        CdReset(0);
    }
    if (D_801D3764 != -1) {
        CdReadyCallback((void *)D_801D3764);
    }
    D_801E28EC = 0;
    D_801D3710 = 0;
    D_801D8750 = 0xFFFF;
}

void func_800631B4(void) {
    if (D_801E28EC != 0 || D_801D3710 != 0) {
        func_80063E48(0x7D, 0);
        while (func_80063F30() != 0) {
        }
        CdControl(9, NULL, NULL);
    }
}

void func_80063214(void) {
    if (D_801E28EC != 0 || D_801D3710 != 0) {
        func_80063E48(0x7D, D_801E1CB4 << 7);
        CdControl(0x1B, NULL, NULL);
    }
}

void func_80063270(void) {
    if (D_801E28EC != 0 || D_801D3710 != 0) {
        func_80063E48(0xFA, 0);
        while (func_80063F30() != 0) {
        }
        cdload_stop_xa(0);
    }
}

void cdload_on_xa_ready(s32 arg0) {
    D_801F991C = arg0;
    D_801E0D48++;
}

s32 cdload_play_xa(u32 track) {
    u8 param[4];

    D_801FB4BC.file = (track >> 4) + 1;
    D_801FB4BC.chan = (track & 0xF) + 1;
    if (CdControl(CdlSetfilter, (u8 *)&D_801FB4BC, NULL) == 0) {
        return 0;
    }
    D_801E0D48 = 0;
    D_801F991C = 0;
    D_801E2A48 = D_8008A334[track];
    D_801D3764 = CdReadyCallback(cdload_on_xa_ready);
    D_801E28EC = 1;
    D_801D3710 = 0;
    CdControl(CdlSetloc, (u8 *)D_80089820, NULL);
    param[0] = 0xC8;
    param[1] = 0;
    CdControl(CdlSetmode, param, NULL);
    CdControl(CdlReadS, NULL, NULL);
    func_80063E48(0x7D, D_801E1CB4 << 7);
    return 1;
}
