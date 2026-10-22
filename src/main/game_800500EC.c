/* A file of the game's code, named after its first function until its contents are understood.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "entity.h"

void func_80031280(Entity *, Unk54728 *);
s32 func_80031714(Entity *);
void func_800376D8(Entity *);
void func_8003EF64(Entity *);
void func_80046F68(Entity *);
void func_8004D488(Entity *);
void func_8004FC00(s32, Entity *);
void func_800634D4(Entity *, s32);

extern s32 D_800AA250;
extern s32 D_800AA25C;
extern s32 D_800AA2DC;
extern u16 D_801D8740;
extern u32 D_801F9ACC;

void func_80050BBC(void);
void func_80050E58(Entity *);
void func_800510E8(Entity *);
void func_8005189C(Entity *);
void func_80051C9C(Entity *);
void func_80052798(Entity *);
void func_8005262C(Entity *);
void func_800524AC();
void func_80052E70(Entity *);
void func_800531C0(Entity *);
void func_8005382C(u16);
s32 func_80053B30(s16, s16, s16, s16, Entity *);
void func_80053C50(s32, Entity *);
void func_8005417C(Entity *);
void func_8005421C(Entity *);
Unk54728 *func_80054728(u16);
void func_80054A18();
void func_80054E1C(void);
void func_80054F18(void);
void func_80055014(void);
void func_80055110(void);
void func_80055454(Entity *, Unk54728 *);
void func_80055740(Entity *, Unk54728 *);
void func_80056598(void);
void func_80056F38(Entity *, Unk54728 *);
s32 func_800571D0(Entity *, Unk54728Sub18 *);
void func_800578E0(Entity *, Unk54728 *);
u16 func_80057AD8(Entity *, Unk54728 *, s32);
void func_800580F8(void);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800500EC);

void func_80050190(Entity *e) {
    if (!(e->unk_0C8 & 4)) {
        e->unk_05A = 0;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800501B0);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800504B4);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80050520);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_8005059C);

void func_8005061C(void) {
}

void func_80050624(Entity *e) {
    D_800AA268.p->unk_0C = 0;
    e->unk_104 = 0;
    if (e->unk_168 == 7) {
        func_80054F18();
    } else {
        func_80055110();
    }
}

void func_80050670(Entity *e) {
    D_800AA268.p->unk_0C = 0;
    e->unk_104 = 0;
    if (e->unk_168 == 7) {
        func_80054E1C();
    } else {
        func_80055014();
    }
}

void func_800506BC(Entity *e) {
    Unk54728 *obj;
    s16 x;

    obj = func_80054728(e->unk_1B2);
    if (obj != NULL) {
        if (e->unk_1B0 == 2) {
            x = obj->unk_0E;
            if (D_800AA268.p->unk_22 & 0x10) {
                x += 0x18;
            } else {
                x -= 0x18;
            }
            D_800AA268.p->unk_16 = x;
        } else if (e->unk_1B0 == 1) {
            x = obj->unk_04;
            if (D_800AA268.p->unk_22 & 0x10) {
                x += 0x18;
            } else {
                x -= 0x18;
            }
            D_800AA268.p->unk_16 = x;
        }
        func_800531C0(e);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80050774);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_8005086C);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800509EC);

void func_80050B40(Entity *e) {
    e->unk_05A = 0x4C;
    func_80050BBC();
    if (D_800AA268.p->unk_0C == 0 && D_800AA268.p->unk_10 == 0 && e->unk_100 == 0 && e->unk_104 == 0) {
        e->unk_05A = 0;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80050BBC);

void func_80050DAC(Entity *e) {
    func_80050E58(e);
    func_800531C0(e);
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80050DD8);

void func_80050E58(Entity *e) {
    u16 n;

    n = e->unk_1B0;
    D_800AA250 = n;
    if (n != 0) {
        func_80054A18();
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80050E88);

void func_800510BC(Entity *a, Entity *b) {
    Body *body;
    u16 flags;

    body = b->unk_068;
    flags = body->unk_22;
    if ((flags & 0x10) == (a->unk_068->unk_22 & 0x10)) {
        body->unk_22 = flags ^ 0x10;
    }
}

void func_800510E8(Entity *e) {
    func_80050E58(e);
    if (e->unk_104 == 0 || (D_800AA268.p->unk_10 >= 0 && D_800AA268.p->unk_18.h.i >= 0xE1)) {
        func_800531C0(e);
    }
}

void func_80051150(Entity *e, Entity *e2) {
    Body *body;
    s32 v;

    body = e2->unk_068;
    e2->unk_05A = 0xF;
    v = -0x20000;
    if (body->unk_22 & 0x10) {
        v = 0x20000;
    }
    body->unk_0C = v;
    func_8004FC00(1, e);
    func_8005417C(e);
    func_800510E8(e);
}

void func_800511B4(Entity *e, Entity *e2) {
    e2->unk_05A = 0x39;
    func_8004FC00(1, e);
    func_8005417C(e);
    func_800510E8(e);
}

void func_800511F8(Entity *e, Entity *e2) {
    e2->unk_05A = 0x22;
    func_800634D4(e2, 5);
    func_8004FC00(1, e);
    func_8005417C(e);
    func_800510E8(e);
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80051248);

void func_800512CC(Entity *e, Entity *e2) {
    Body *body;
    s32 v;

    body = e2->unk_068;
    e2->unk_05A = 0xA;
    v = -0x40000;
    if (body->unk_22 & 0x10) {
        v = 0x40000;
    }
    body->unk_0C = v;
    func_8004FC00(1, e);
    func_8005417C(e);
    func_800510E8(e);
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80051330);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800513EC);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80051410);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800514CC);

void func_800517C0(Entity *e) {
    e->unk_104 = 0x4000;
    e->unk_1B0 = 0;
    e->unk_1B2 = 0;
    if (D_800AA268.p->unk_10 > 0) {
        func_8005189C(e);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_8005180C);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_8005189C);

void func_8005199C(Entity *e) {
    func_800376D8(e);
    if (e->unk_05A == 0x53) {
        func_800531C0(e);
    } else if ((u16)(D_800AA268.p->unk_18.h.i - 0xC8) < 0x11) {
        func_8005421C(e);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80051A08);

void func_80051A48(Entity *e) {
    if (!(e->unk_0C8 & 4)) {
        e->unk_05A = 2;
    }
    func_80051C9C(e);
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80051A80);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80051B38);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80051C9C);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80051D8C);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80051E80);

void func_80052100(Entity *e) {
    func_80050E58(e);
    func_800531C0(e);
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_8005212C);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_8005222C);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800522F8);

void func_800523B8(Entity *e) {
    e->unk_1B0 = 0;
    e->unk_1B2 = 0;
    if (D_800AA268.p->unk_18.h.i >= 0xE1) {
        if (D_801D8740 < 2 || D_801F9ACC == 0 || D_801F9ACC > 0xFFF00000) {
            if ((u16)func_80031714(e) == 1) {
                func_800524AC(e);
                e->unk_05A = 0x35;
                D_800AA268.p->unk_18.h.i = 0xED;
            }
            func_800531C0(e);
        } else {
            func_800524AC(e);
            func_80052798(e);
        }
    } else if (e->unk_104 == 0) {
        e->unk_104 = 0x4000;
    }
}

void func_800524A4(void) {
}

void func_800524AC(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800524B4);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80052520);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_8005262C);

void func_800526A4(Entity *e) {
    if (e->unk_008 != 0) {
        func_80056598();
        if (e->unk_05A != 0x2C) {
            func_800531C0(e);
            return;
        }
    }
    if (D_800AA268.p->unk_18.h.i < 0xE1) {
        func_8005199C(e);
        return;
    }
    D_800AA268.p->unk_18.h.i = 0xE1;
    func_800376D8(e);
    func_8003EF64(e);
    func_80046F68(e);
    func_8004D488(e);
    if (D_801D8740 < 2 || D_801F9ACC == 0 || D_801F9ACC > 0xFFE00000) {
        func_8005262C(e);
    } else {
        func_80052798(e);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80052798);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80052880);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80052A0C);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80052A68);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80052ADC);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80052BE0);

void func_80052C7C(Entity *e) {
    func_80053C50(0x700, e);
    func_800531C0(e);
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80052CB0);

void func_80052DA8(Entity *e) {
    func_800531C0(e);
}

void func_80052DC8(Entity *e) {
    func_800531C0(e);
}

void func_80052DE8(Entity *e) {
    e->unk_046 = 1;
    func_800531C0(e);
}

void func_80052E0C(Entity *e) {
    func_800531C0(e);
    if (e->unk_05A == 1) {
        e->unk_05A = 0;
    }
}

void func_80052E44(Entity *e) {
    func_800531C0(e);
    func_80052E70(e);
}

void func_80052E70(Entity *e) {
    func_8005382C(e->unk_0CC);
}

void func_80052E94(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80052E9C);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800531C0);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80053204);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800535E4);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80053804);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_8005382C);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80053854);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80053970);

u16 func_80053AC4(s16 a, s16 b, s16 c, s16 d, Entity *e) {
    if (e->unk_0DC == 0 || e->unk_05A == 0x37) {
        return 0;
    }
    return func_80053B30(a, b, c, d, e);
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80053B30);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80053BE8);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80053C50);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80053D68);

void func_80053DE4(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80053DEC);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80053EA8);

void func_80053FDC(void) {
    Body *b;
    s32 v;

    b = D_800AA268.p;
    v = b->unk_10 + 0x3000;
    if (v > 0x60000) {
        v = 0x60000;
    }
    b->unk_18.w += v;
    b->unk_10 = v;
    if (b->unk_18.h.i >= 0xC0) {
        b->unk_80 = 0x319;
    } else {
        b->unk_44 = *b->unk_5C;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_8005404C);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800540D0);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_8005417C);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_8005421C);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80054374);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800543FC);

void func_800544D8(Entity *e, Body *dst, Body *src) {
    if (e->unk_05A == 0x47) {
        dst->unk_16 = src->unk_16;
        dst->unk_18.h.i = src->unk_18.h.i;
    } else if (e->unk_120.w != 0) {
        dst->unk_16 = e->unk_120.h.lo;
        dst->unk_18.h.i = e->unk_120.h.hi;
    }
    dst->unk_80 = src->unk_80 + 0x1000;
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_8005453C);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80054608);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80054728);

void func_8005478C(Entity *e) {
    Unk54728 *obj;

    obj = func_80054728(e->unk_1B2);
    if (obj != NULL && obj->unk_78 == 0 && obj->unk_58 == 0) {
        func_80031280(e, obj);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800547EC);

void func_80054A18(Entity *e) {
    func_800578E0(e, func_80054728(e->unk_1B2));
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80054A50);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80054BA4);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80054CF8);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80054D74);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80054E1C);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80054F18);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80055014);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80055110);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_8005520C);

void func_800553B0(Entity *e) {
    Unk54728 *obj;

    if (!(D_800AA2DC & 0x38)) {
        obj = func_80054728(e->unk_1B2);
        if (!func_80057AD8(e, obj, 1)) {
            func_80056F38(e, obj);
            func_800578E0(e, obj);
            if (D_800AA25C != 0xF && D_800AA25C != 2 && D_800AA25C != 0x4E) {
                func_80055454(e, obj);
            }
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80055454);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800554F8);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_8005558C);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80055600);

void func_800556AC(Entity *e) {
    Unk54728 *obj;

    obj = func_80054728(e->unk_1B2);
    if (!func_80057AD8(e, obj, 2)) {
        func_80056F38(e, obj);
        func_800578E0(e, obj);
        if (D_800AA25C != 0xF && D_800AA25C != 2 && D_800AA25C != 0x4E) {
            func_80055740(e, obj);
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80055740);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800557C8);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_8005584C);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800558AC);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80055948);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80055970);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80055AB8);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80055B68);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80055CA8);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80055FBC);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80056050);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800560A8);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80056134);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_8005618C);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800561CC);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80056258);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800562E4);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80056378);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_8005640C);

void func_80056488(Entity *e) {
    D_800AA268.p->unk_16 = func_80054728(e->unk_1B2)->unk_04 + 0x28;
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800564C0);

void func_800564D8(Entity *e) {
    D_800AA268.p->unk_16 = func_80054728(e->unk_1B2)->unk_0E - 0x28;
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80056510);

void func_80056528(Entity *e) {
    D_800AA268.p->unk_18.h.i = func_80054728(e->unk_1B2)->unk_74 + 0x30;
}

void func_80056560(Entity *e) {
    D_800AA268.p->unk_18.h.i = func_80054728(e->unk_1B2)->unk_74 + 8;
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80056598);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80056708);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800567E8);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80056840);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80056990);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80056A44);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80056AC8);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80056C18);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80056CCC);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80056E2C);

void func_80056E78(Entity *e) {
    D_800AA25C = 2;
    e->unk_05A = 2;
    func_800580F8();
    e->unk_1B0 = 0;
    e->unk_1B2 = 0;
    e->unk_1B4 = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80056EB8);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80056F38);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_8005703C);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80057088);

s32 func_800570D4(Entity *e, Unk54728Sub18 *p) {
    s32 x;

    x = p->unk_1E + 8;
    if (x < e->unk_10A || x >= e->unk_10E) {
        return 0;
    }
    return 1;
}

u16 func_80057110(Entity *e) {
    Unk54728Sub18 *p;

    p = func_80054728(e->unk_1B2)->unk_18;
    if (p != NULL && p->unk_1C == 2) {
        return func_800571D0(e, p);
    }
    return 0;
}

u16 func_80057170(Entity *e) {
    Unk54728Sub18 *p;

    p = func_80054728(e->unk_1B2)->unk_18;
    if (p != NULL && p->unk_1C == 1) {
        return func_800571D0(e, p);
    }
    return 0;
}

s32 func_800571D0(Entity *e, Unk54728Sub18 *p) {
    s32 x;

    x = p->unk_0E - 8;
    if (e->unk_10E < x || e->unk_10A >= x) {
        return 0;
    }
    return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_8005720C);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80057258);

s32 func_800572A4(Entity *e, Unk54728Sub18 *p) {
    s32 x;

    x = p->unk_1E + 8;
    if (x < e->unk_10A || x >= e->unk_10E) {
        x = p->unk_0E - 8;
        if (e->unk_10E < x || e->unk_10A >= x) {
            return 0;
        }
    }
    return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80057300);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800573C8);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800573EC);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800574EC);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800575F0);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800576B8);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800576DC);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800577DC);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_800578E0);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80057A08);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80057AD8);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80057B40);

void func_80057B78(void) {
    D_800AA268.p->unk_90->unk_028 = 1;
}

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80057B94);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80057BD4);

INCLUDE_ASM("asm/main/nonmatchings/game_800500EC", func_80057C38);

void func_80057C8C(void) {
}
