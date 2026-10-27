/* The CD file reader (by index into the file table, with a checksum) and the overlay loader; docs/DISC_LAYOUT.md.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "cdload.h"
#include "psyq/libapi.h"
#include "psyq/libc2.h"
#include "psyq/libcd.h"
#include "psyq/libetc.h"
#include "psyq/libgpu.h"
#include "psyq/libspu.h"

void func_8002958C(void);
void *func_8001D110(void);
void func_8001DCB4(void);
void func_800415B4(void);
void func_8001B5E8(s32);
void func_800630E8(s32);
s32 func_800632E8(u32);
void func_800632CC(s32);
void func_80063E48(s32, s32);
s32 func_80063F30(void);
void func_800700CC(s32);
void func_80063DF8(s32);
void func_8006FC6C(void);
void func_8006FC8C(s32, s32 *);
void func_8006FEB4(void);
void func_800700A8(void);
void func_8006BBA0(s32, s32);
void func_8006BD60(s32);
void func_8006C8D8(s32, s32);
s32 func_8006C8B4(s32);
s32 func_8006C8F8(s32);
s16 func_8006EC18(void);
s32 func_80062F14(s32, s32, s32, s32, s32, s32, s32);

extern u8 D_801FA8A0[7];
extern s32 D_801FB49C[3];

/* The loaded file: its index, its data (the read buffer) and the read position (the fopen/fread emulation). */
extern s32 D_801FB4AC;
extern u8 *D_801FB4B0;
extern s32 D_801FB4B4;
extern u8 *D_801E1C78;

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

extern s32 D_80085264[];
extern u16 D_801D8728;
extern u16 D_801FA960;
extern u16 D_801FA964;

extern u8 D_80085274[];
extern s32 D_80085278;
extern s32 D_8008527C;
extern u8 *D_80016AC8;
extern u8 *D_80016ACC;

extern s32 D_801D3710;
extern s32 D_801D3764;          /* the data-ready callback the XA player replaced, -1 for none */
extern u16 D_801D8750;          /* the music playing, 0xFFFF for none */
extern CdlFILTER D_801FB4BC;
extern s32 D_8008A334[];        /* per XA track: its length (D_801E2A48 while it plays) */
extern s32 D_801E2A48;
extern s32 D_801E28EC;
extern s16 D_801E1CB4;
extern s32 D_801E0D48;
extern s32 D_801F991C;
extern s32 D_801FB4C0;
extern u8 *D_80085300;

/* What the sound driver reads its files with (func_800706C0): this file's stdio emulation, and parameters. */
typedef struct {
    /* 0x00 */ s32 (*open)(s32 index, s32 mode);
    /* 0x04 */ s32 (*read)(void *buf, s32 size, s32 count, s32 handle);
    /* 0x08 */ s32 (*seek)(s32 handle, s32 pos);
    /* 0x0C */ s32 (*size)(void);
    /* 0x10 */ s32 (*close)(s32 handle);
    /* 0x14 */ s32 (*load_spu)(s32 handle, s32 spuAddr, s32 size);
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
} SoundFileIO;

void func_800706C0(SoundFileIO *io);
s32 func_8006EE30(s32);
void func_8006F0D8(s32, void *, s32);
s32 func_8006E804(void *, s32);
void func_8006E8B4(void *, s32, s32, void *, s32);
void *func_8006EC08(void);
s32 func_8006E4F4(void);
s32 func_80070298(s32, s32);
s32 func_80070324(s32, s32, void *);
void *func_80062C10(s32 size);
void func_80062EB0(void);
void func_80063064(void);
s32 func_80061444(void *buf, s32 size, s32 count, s32 handle);
s32 func_800614E0(s32 handle, s32 pos);
s32 func_800614BC(void);
s32 func_800614B0(s32 handle);
s32 func_80061774(s32 handle, s32 spuAddr, s32 size);
s32 func_800613FC(s32 index, s32 mode);
s32 func_8006301C(s32 index, s32 spuAddr);
s32 func_80061ACC(u8 *src, u8 *dst);
s32 func_80061B4C(u8 *src, u8 *dst);
s32 func_80061D10(u8 *src, u8 *dst);
s32 func_80061F90(u8 *src, u8 *dst);
void func_800621F8(u8 *bits, u8 *table, u32 dims);
extern s16 D_80085304[];

/* Lists the players of the monsters in D_801FB49C, sorted, 99 for none. */
void func_80060F3C(void) {
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

s32 func_80061014(s32 arg0) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (arg0 == D_801FB49C[i]) {
            return D_801FB49C[i + 1];
        }
    }
    return D_801FB49C[0];
}

void func_80061068(s32 *arg0, s16 arg1, s16 arg2) {
    Unk800AA248Node *node;
    Body *saved;

    saved = D_800AA248.unk_20;
    node = func_8001D110();
    D_800AA248.unk_3C = node;
    node->unk_10.h.i = arg1;
    node->unk_14.h.i = arg2;
    node->unk_20 = 0x7000;
    node->unk_28 = arg0;
    node->unk_00 = *arg0;
    func_8001DCB4();
    D_800AA248.unk_20 = saved;
}

void func_800610E8(void) {
}

void func_800610F0(void) {
    D_800AA268.p->unk_80 = *D_800AA268.p->unk_5C;
}

void func_80061110(void) {
    D_800AA268.p->unk_18.w = 0x02000000;
    func_800415B4();
}

void func_8006113C(void) {
    D_800AA268.p->unk_90->unk_010.h.hi = 1;
}

void func_80061158(void) {
    D_800AA268.p->unk_90->unk_010.h.hi = 0;
}

s32 func_80061170(s32 index) {
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
            func_800630E8(1);
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

s32 func_800613FC(s32 index, s32 mode) {
    D_801FB4AC = index;
    D_801FB4B4 = 0;
    D_801FB4B0 = D_801E1C78;
    cdload_read_file(index, D_801E1C78);
    return index;
}

s32 func_80061444(void *buf, s32 size, s32 count, s32 handle) {
    s32 len;

    if (handle == -1) {
        return 0;
    }
    len = size * count;
    memcpy(buf, D_801FB4B0 + D_801FB4B4, len);
    D_801FB4B4 += len;
    return len;
}

s32 func_800614B0(s32 handle) {
    return handle != -1;
}

s32 func_800614BC(void) {
    return D_80089DA0[D_801FB4AC];
}

s32 func_800614E0(s32 handle, s32 pos) {
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

    offset = D_80085264[D_801D8728];
    if (D_801D8728 != 0) {
        p = (u8 *)(D_801FA964 + offset);
    } else {
        p = (u8 *)(D_801FA960 + offset);
    }
    file = *p;
    pair = (file - 0x54) * 2;
    file = pair + 0x54;
    if (which != 1) {
        file = pair + 0x55;
    }
    return file;
}

void func_80061668(s32 handle, s32 len, s32 spuAddr) {
    u8 *buf;
    u8 *prev;

    buf = D_801C41C0;
    prev = D_801C41C0 - 0x800;
    if (D_801FB4B8 != 0) {
        func_80061444(buf, len, 1, handle);
        SpuSetTransferStartAddr(spuAddr);
        SpuWrite(buf, len);
        D_801FB4A8 = 1;
        D_801FB4B8 = 0;
    } else if (D_801FB4A8 != 0) {
        func_80061444(prev, len, 1, handle);
        SpuIsTransferCompleted(SPU_TRANSFER_WAIT);
        SpuSetTransferStartAddr(spuAddr);
        SpuWrite(prev, len);
        D_801FB4A8 = 0;
    } else {
        func_80061444(buf, len, 1, handle);
        SpuIsTransferCompleted(SPU_TRANSFER_WAIT);
        SpuSetTransferStartAddr(spuAddr);
        SpuWrite(buf, len);
        D_801FB4A8 = 1;
    }
}

s32 func_80061774(s32 handle, s32 spuAddr, s32 size) {
    s32 left;
    s32 addr;

    left = size;
    addr = spuAddr;
    D_801FB4B8 = 1;
    while (left >= 0x800) {
        func_80061668(handle, 0x800, addr);
        left -= 0x800;
        addr += 0x800;
    }
    if (left != 0) {
        func_80061668(handle, left, addr);
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
/* 84.8%: dst is kept in a3 in the original (a1 here), which moves every case's argument setup */
#ifdef NON_MATCHING
s32 func_800619A4(u8 *dst, s32 arg1, u8 *src) {
    s32 size;
    u32 dims;

    switch (((s8 *)src)[3] & 0xF) {
    case 0:
        size = *(u32 *)src & 0xFFFFFF;
        memcpy(dst, src + 4, size);
        return size;
    case 1:
        return func_80061ACC(src, dst);
    case 2:
        return func_80061B4C(src, dst);
    case 3:
        return func_80061D10(src, dst);
    case 4:
        return func_80061F90(src, dst);
    case 5:
        func_800621F8(src + ((s32 *)src)[1], src + 12, ((u32 *)src)[2]);
        dims = ((u32 *)src)[2];
        return ((dims & 0xFFFF) + 3 & ~3) * ((dims >> 16) + 1 & ~1);
    }
    return 0;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/cdload", func_800619A4);
#endif

s32 func_80061ACC(u8 *src, u8 *dst) {
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

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80061B4C);

/* Takes the next 6-bit symbol of the stream: four per three bytes, most significant first. */
#define CDLOAD_GET6(x)                                      \
    switch (phase++) {                                      \
    case 0:                                                 \
        b0 = *in++;                                         \
        b1 = *in++;                                         \
        b2 = *in++;                                         \
        x = b0 >> 2;                                        \
        break;                                              \
    case 1:                                                 \
        x = (b1 >> 4) | ((b0 << 4) & 0x30);                 \
        break;                                              \
    case 2:                                                 \
        x = ((b1 << 2) & 0x3C) | (b2 >> 6);                 \
        break;                                              \
    case 3:                                                 \
        x = b2 & 0x3F;                                      \
        phase = 0;                                          \
        break;                                              \
    }

/* Unpacks a 6-bit RLE stream: a symbol below 32 repeats the next one that many times plus one, a symbol from 32
 * copies that many minus 31 symbols; the top two bits of byte 3 count the padding symbols at the end. */
/* Takes the next 6-bit symbol of the stream: four per three bytes, most significant first. */
#define CDLOAD_GET6(x)                                      \
    switch (phase++) {                                      \
    case 0:                                                 \
        b0 = *src++;                                         \
        b1 = *src++;                                         \
        b2 = *src++;                                         \
        x = b0 >> 2;                                        \
        break;                                              \
    case 1:                                                 \
        x = (b1 >> 4) | ((b0 << 4) & 0x30);                 \
        break;                                              \
    case 2:                                                 \
        x = ((b1 << 2) & 0x3C) | (b2 >> 6);                 \
        break;                                              \
    case 3:                                                 \
        x = b2 & 0x3F;                                      \
        phase = 0;                                          \
        break;                                              \
    }

/* Unpacks a 6-bit RLE stream: a symbol below 32 repeats the next one that many times plus one, a symbol from 32
 * copies that many minus 31 symbols; the top two bits of byte 3 count the padding symbols at the end. */
/* Takes the next 6-bit symbol of the stream: four per three bytes, most significant first. */
#define CDLOAD_GET6(x)                                      \
    switch (phase++) {                                      \
    case 0:                                                 \
        b0 = *src++;                                         \
        b1 = *src++;                                         \
        b2 = *src++;                                         \
        x = b0 >> 2;                                        \
        break;                                              \
    case 1:                                                 \
        x = (b1 >> 4) | ((b0 << 4) & 0x30);                 \
        break;                                              \
    case 2:                                                 \
        x = ((b1 << 2) & 0x3C) | (b2 >> 6);                 \
        break;                                              \
    case 3:                                                 \
        x = b2 & 0x3F;                                      \
        phase = 0;                                          \
        break;                                              \
    }

/* Unpacks a 6-bit RLE stream: a symbol below 32 repeats the next one that many times plus one, a symbol from 32
 * copies that many minus 31 symbols; the top two bits of byte 3 count the padding symbols at the end. */
s32 func_80061D10(u8 *src, u8 *dst) {
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
s32 func_80061F90(u8 *src, u8 *dst) {
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

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_800621F8);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80062868);

void *func_80062C10(s32 size) {
    u8 *p;

    p = (u8 *)(((u32)D_80085300 + 7) & ~7);
    D_80085300 = p + size;
    return p;
}

void func_80062C30(void) {
    SoundFileIO io;
    s32 size;
    s32 bank_size;
    void *buf;
    void *seqs;

    io.open = func_800613FC;
    io.read = func_80061444;
    io.seek = func_800614E0;
    io.size = func_800614BC;
    io.close = func_800614B0;
    io.load_spu = func_80061774;
    io.unk_20 = 0x78;
    io.unk_18 = 0;
    io.unk_1C = 0;
    io.unk_28 = 1;
    io.unk_24 = 1;
    func_800706C0(&io);
    size = func_8006EE30(0x4F);
    func_8006F0D8(0x4F, func_80062C10(size), size);
    bank_size = func_8006E804(func_8006EC08(), 0x50);
    buf = func_80062C10(bank_size);
    func_8006E8B4(func_8006EC08(), 0x50, 0, buf, bank_size);
    seqs = func_80062C10(func_80070298(0, func_8006E4F4()));
    func_80070324(0, func_8006E4F4(), seqs);
    D_801FB4C0 = 0x1010;
    func_80063064();
    func_80062EB0();
    D_801FB4C0 += func_8006301C(0, D_801FB4C0);
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

void func_80062E24(void) {
    func_8006FEB4();
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

s32 func_80062F14(s32 index, s32 spuAddr, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 reload) {
    s32 handle;
    s32 addr;
    s32 count;
    s32 i;
    s32 id;
    s32 size;

    handle = func_800613FC(index, 0);
    func_80061444(&D_801C49C0, 1, 0x800, handle);
    addr = spuAddr;
    count = D_801C49C0.count;
    for (i = 0; i < count; i++) {
        id = D_801C49C0.ids[i];
        if (func_8006C8F8(id) == 0 || reload != 0) {
            size = func_8006C8B4(id);
            func_80061774(handle, addr, size);
            func_8006C8D8(id, addr);
            addr += size;
        }
    }
    func_800614B0(handle);
    return addr - spuAddr;
}

s32 func_8006301C(s32 index, s32 spuAddr) {
    return func_80062F14(D_80085304[index], spuAddr, 0, 0, 0, 500, 0);
}

void func_80063064(void) {
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
    return func_800632E8(arg0);
}

void func_800630E8(s32 mode) {
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
        func_800630E8(0);
    }
}

void func_800632CC(s32 arg0) {
    D_801F991C = arg0;
    D_801E0D48++;
}

s32 func_800632E8(u32 track) {
    u8 param[4];

    D_801FB4BC.file = (track >> 4) + 1;
    D_801FB4BC.chan = (track & 0xF) + 1;
    if (CdControl(CdlSetfilter, (u8 *)&D_801FB4BC, NULL) == 0) {
        return 0;
    }
    D_801E0D48 = 0;
    D_801F991C = 0;
    D_801E2A48 = D_8008A334[track];
    D_801D3764 = CdReadyCallback(func_800632CC);
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
