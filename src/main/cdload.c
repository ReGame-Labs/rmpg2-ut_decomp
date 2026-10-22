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
s32 func_800632E8(s32);
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
extern s32 D_801D3764;
extern s32 D_801E28EC;
extern s16 D_801E1CB4;
extern s32 D_801E0D48;
extern s32 D_801F991C;
extern s32 D_801FB4C0;
extern u8 *D_80085300;
extern s16 D_80085304[];

#ifdef NON_MATCHING
/* 92.9%: the order of the first loop's setup (i = 0 and the array bases) and p assigned through a temporary differ */
void func_80060F3C(void) {
    s32 i;
    s32 j;
    s32 *p;

    func_8002958C();
    p = D_801FB49C;
    D_801FB49C[2] = 0x63;
    D_801FB49C[1] = 0x63;
    D_801FB49C[0] = 0x63;
    for (i = 0; i < 7; i++) {
        if (D_801FA8A0[i] != 0) {
            *p++ = D_801FA8A0[i];
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
#else
INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80060F3C);
#endif

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
    node->unk_12 = arg1;
    node->unk_16 = arg2;
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
    D_800AA268.p->unk_90->unk_012 = 1;
}

void func_80061158(void) {
    D_800AA268.p->unk_90->unk_012 = 0;
}

s32 func_80061170(s32 index) {
    return D_80089DA0[index];
}

INCLUDE_ASM("asm/main/nonmatchings/cdload", cdload_read_file);

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

s32 func_800613FC(s32 index) {
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

#ifdef NON_MATCHING
/* 99.6%: the city byte is loaded into a register of its own (v1) in the original */
s32 cdload_city_file_index(s32 which) {
    s32 offset;
    u8 *p;
    s32 city;
    s32 index;
    s32 r;

    offset = D_80085264[D_801D8728];
    if (D_801D8728 != 0) {
        p = (u8 *)(D_801FA964 + offset);
    } else {
        p = (u8 *)(D_801FA960 + offset);
    }
    city = *p;
    index = (city - 0x54) * 2;
    r = index + 0x54;
    if (which != 1) {
        r = index + 0x55;
    }
    return r;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/cdload", cdload_city_file_index);
#endif

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

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_800619A4);

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

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80061D10);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80061F90);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_800621F8);

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80062868);

void *func_80062C10(s32 size) {
    u8 *p;

    p = (u8 *)(((u32)D_80085300 + 7) & ~7);
    D_80085300 = p + size;
    return p;
}

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80062C30);

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

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_80062F14);

void func_8006301C(s32 index, s32 spuAddr) {
    func_80062F14(D_80085304[index], spuAddr, 0, 0, 0, 500, 0);
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

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_800630E8);

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

INCLUDE_ASM("asm/main/nonmatchings/cdload", func_800632E8);
