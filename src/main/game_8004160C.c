/* A file of the game's code, named after its first function until its contents are understood.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "game.h"

void func_8003EB5C(u8 *table, Mover *mover);
u16 func_8004A468(void);
s16 func_8003DC3C(Ai *ai);
void func_8003DB74(Ai *ai);
void func_8003DAA0(Ai *ai);
void func_8003E788(Ai *ai, s32 arg1);
u16 func_8003E79C(Mover *mover, s32 arg1);
u16 func_8004B6C4(s32 arg0, s32 arg1, s32 arg2);
void func_8004E99C(s16 arg0, s16 arg1);

void func_800416AC(const AiHandler *handlers, Ai *ai);
void func_80041928(const AiHandler *handlers, Ai *ai);
void func_80041988(const AiHandler *handlers, Ai *ai);
void func_800419C4(const AiHandler *handlers, Ai *ai);
void func_80041A00(const AiHandler *handlers, Ai *ai);
void func_80041A3C(const AiHandler *handlers, Ai *ai);
void func_80041A70(const AiHandler *handlers, Ai *ai);
void func_80041B2C(const AiHandler *handlers, Ai *ai);
void func_80041C0C(const AiHandler *handlers, Ai *ai);
void func_80041DA8(const AiHandler *handlers, Ai *ai);
void func_80041DE4(const AiHandler *handlers, Ai *ai);
void func_80041E54(const AiHandler *handlers, Ai *ai);
void func_80042008(const AiHandler *handlers, Ai *ai);
void func_800420F8(const AiHandler *handlers, Ai *ai);
void func_80042134(const AiHandler *handlers, Ai *ai);
void func_80041AD0(s16 hit, const AiHandler *handlers, Ai *ai);
void func_80042238(Ai *ai);

extern s32 D_801D8864;
extern s16 D_801FA960;
extern s16 D_801F9ACA;
extern const AiHandler D_8007E828[];
extern const AiHandler D_8007E720[];
extern const AiHandler D_8007E880[];
extern const AiHandler D_8007E8D8[];
extern const AiHandler D_8007E930[];
extern const AiHandler D_8007E6C8[];
extern const AiHandler D_8007E778[];
extern const AiHandler D_8007E7D0[];
extern const AiHandler D_8007E988[];
extern const AiHandler D_8007E9E0[];
extern u8 D_8008E6AC[];
extern u8 D_8008E6EC[];
extern u8 D_8008E724[];
extern u8 D_8008E730[];
extern u8 D_8008E7A0[];
extern u8 D_8008E868[];
extern u8 D_8008E988[];
extern u8 D_8008E994[];
extern u8 D_8008E9AC[];
extern u8 D_8008E9C4[];
extern u8 D_8008EA44[];
extern u8 D_8008EA5C[];
extern u8 D_8008EA74[];
extern u8 D_8008EBD0[];
extern u8 D_8008EC00[];
extern u8 D_8008EC28[];
extern u8 D_8008EC34[];
extern u8 D_8008ECC0[];
extern u8 D_8008ED4C[];
extern u8 D_8008EDD8[];
extern u8 D_8008EE64[];
extern u8 D_8008EFF0[];
extern u8 D_8008F0F0[];
extern u8 D_8008F1F0[];
extern u8 D_8008F2F0[];
extern u8 D_8008F3F0[];
extern u8 D_8008F4F0[];
extern u8 D_8008F864[];
extern u8 D_8008F9D8[];
extern u8 D_8008FB4C[];
extern u8 D_8008FCC0[];
extern u8 D_8008FE34[];
extern u8 D_8008FFA8[];
extern u8 D_8008EAD4[];
extern u8 D_8008EAFC[];
extern u8 D_8008EB24[];
extern u8 D_8008EB5C[];
extern u8 D_8008EB84[];
extern u8 D_8008EB9C[];
extern u8 D_80090290[];
extern u8 D_800902C0[];
extern u8 D_800903E4[];
extern u8 D_80090508[];
extern u8 D_8009062C[];
extern u8 D_80090750[];
extern u8 D_80090330[];
extern u8 D_80090454[];
extern u8 D_80090578[];
extern u8 D_8009069C[];
extern u8 D_800907C0[];
extern u8 D_80090374[];
extern u8 D_80090498[];
extern u8 D_800905BC[];
extern u8 D_800906E0[];
extern u8 D_80090804[];
extern u8 D_80090928[];
extern u8 D_80090960[];
extern u8 D_80090998[];
extern u8 D_80090D4C[];
extern u8 D_80090D94[];
extern u8 D_80090DCC[];
extern u8 D_80090E60[];
extern u8 D_80090E98[];
extern u8 D_80090EE8[];
extern u8 D_80090DDC[];
extern u8 D_80090DE8[];
extern u8 D_80090AF4[];
extern u8 D_8008C724[];
extern u8 D_80090BD4[];
extern u8 D_80090F68[];
extern u8 D_800910A4[];
extern u8 D_800911E0[];
extern u8 D_800912F0[];
extern u8 D_80091400[];
extern u8 D_8009153C[];
extern u8 D_80090FE0[];
extern u8 D_8009111C[];
extern u8 D_80091258[];
extern u8 D_80091368[];
extern u8 D_80091478[];
extern u8 D_800915B4[];
extern u8 D_80091058[];
extern u8 D_80091194[];
extern u8 D_800912A4[];
extern u8 D_800913B4[];
extern u8 D_800914F0[];
extern u8 D_8009162C[];
extern u8 D_80097020[];
extern u8 D_80097050[];
extern u8 D_80097078[];
extern u8 D_80097084[];
extern u8 D_80097110[];
extern u8 D_8009719C[];
extern u8 D_80097228[];
extern u8 D_800972B4[];

void func_8004160C(Ai *ai) {
    func_800416AC(D_8007E828, ai);
}

void func_80041634(Ai *ai) {
    func_800416AC(D_8007E720, ai);
}

void func_8004165C(Ai *ai) {
    func_800416AC(D_8007E880, ai);
}

void func_80041684(Ai *ai) {
    func_800416AC(D_8007E8D8, ai);
}

/* 77%: the two switches' dispatch and the default path differ in layout */
#ifdef NON_MATCHING
void func_800416AC(const AiHandler *handlers, Ai *ai) {
    s16 hit;

    switch (ai->unk_8) {
    case 0xA:
        func_80041928(handlers, ai);
        return;
    case 0xB:
        func_80041A3C(handlers, ai);
        return;
    case 0x32:
    case 0x33:
        func_80041B2C(handlers, ai);
        return;
    case 0x36:
    case 0x37:
        func_80041DA8(handlers, ai);
        return;
    case 0x3B:
    case 0x3C:
        func_80041C0C(handlers, ai);
        return;
    case 0x1E:
        func_80041DE4(handlers, ai);
        return;
    case 0xF2:
        func_80042008(handlers, ai);
        return;
    case 0x46:
        func_80041E54(handlers, ai);
        return;
    case 0x4D:
        if (handlers == D_8007E930) {
            func_800420F8(handlers, ai);
        }
        return;
    case 0x4C:
        if (handlers == D_8007E930) {
            func_80042134(handlers, ai);
        }
        return;
    default:
        hit = func_8003DC3C(ai);
        if (hit != 0) {
            func_80041AD0(hit, handlers, ai);
            return;
        }
        func_80042238(ai);
        switch (ai->unk_8) {
        case 0x15:
            func_80041988(handlers, ai);
            return;
        case 0x16:
            func_800419C4(handlers, ai);
            return;
        case 0x17:
            func_80041A00(handlers, ai);
            return;
        default:
            func_8003DB74(ai);
            return;
        }
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004160C", func_800416AC);
#endif

void func_80041928(const AiHandler *handlers, Ai *ai) {
    if (ai->unk_A != 0) {
        if (ai->unk_C == 1) {
            ai->unk_A = 4;
            ai->unk_C = 0;
            ai->unk_8 = 0x15;
            func_80041A70(handlers, ai);
        }
    } else {
        ai->unk_C = 0;
        ai->unk_A = 1;
        func_80041A70(handlers, ai);
    }
}

void func_80041988(const AiHandler *handlers, Ai *ai) {
    if (ai->unk_C == 1) {
        ai->unk_A = 5;
        ai->unk_C = 0;
        ai->unk_8 = 0x16;
        func_80041A70(handlers, ai);
    }
}

void func_800419C4(const AiHandler *handlers, Ai *ai) {
    if (ai->unk_C == 1) {
        ai->unk_A = 6;
        ai->unk_C = 0;
        ai->unk_8 = 0x17;
        func_80041A70(handlers, ai);
    }
}

void func_80041A00(const AiHandler *handlers, Ai *ai) {
    if (ai->unk_C == 1) {
        ai->unk_A = 3;
        ai->unk_C = 0;
        ai->unk_8 = 0xB;
        func_80041A70(handlers, ai);
    }
}

void func_80041A3C(const AiHandler *handlers, Ai *ai) {
    if (ai->unk_C == 1) {
        func_8003DB74(ai);
    }
}

/* 98.6%: the original adds the index into the table register (addu a0,a0,v0) and reads through it */
#ifdef NON_MATCHING
void func_80041A70(const AiHandler *handlers, Ai *ai) {
    (*(handlers + ai->unk_A))(ai);
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004160C", func_80041A70);
#endif

void func_80041AA8(Ai *ai) {
    func_800416AC(D_8007E930, ai);
}

/* 94.5%: the two stores at the join come in the other order and the handlers move fills the delay slot */
#ifdef NON_MATCHING
void func_80041AD0(s16 hit, const AiHandler *handlers, Ai *ai) {
    s16 action;

    if (hit != -1) {
        ai->unk_A = 9;
        action = 0x32;
    } else {
        ai->unk_A = 0xA;
        action = 0x33;
    }
    ai->unk_C = 0;
    ai->unk_8 = action;
    func_80041A70(handlers, ai);
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004160C", func_80041AD0);
#endif

/* 92.7%: scheduling of the constant and the argument moves before the call */
#ifdef NON_MATCHING
void func_80041B2C(const AiHandler *handlers, Ai *ai) {
    s32 speed;

    ai->unk_36 = 0;
    if (ai->unk_C == 1) {
        ai->unk_C = 0;
        if (D_800AA248.unk_20->unk_18 <= 0x5F0000) {
            speed = 0x30000;
            ai->unk_A = 0xC;
            ai->unk_8 = 0x3C;
        } else {
            speed = 0x2C000;
            ai->unk_A = 0xB;
            ai->unk_8 = 0x3B;
        }
        ai->unk_24 = 1;
        if ((u16)(ai->unk_6 - 0x17) < 2) {
            speed = 0x1E000;
        }
        D_800AA248.unk_20->unk_10 = speed;
        func_8003E788(ai, speed);
        D_800AA248.unk_20->unk_80 = 0x353;
        func_80041A70(handlers, ai);
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004160C", func_80041B2C);
#endif

void func_80041C0C(const AiHandler *handlers, Ai *ai) {
    s32 limit;

    if (ai->unk_24 != 0) {
        ai->unk_24 = 0;
        D_800AA248.unk_20->unk_18 += 0x1C0000;
    }
    limit = 0xD90000;
    if (D_801FA960 >= 0x64) {
        limit = 0xE00000;
    }
    D_800AA248.unk_20->unk_18 += D_800AA248.unk_20->unk_10;
    if (D_800AA248.unk_20->unk_18 >= limit) {
        if (ai->unk_28 != NULL && ai->unk_28->unk_8 != NULL) {
            D_800AA248.unk_20->unk_18 = limit;
            D_800AA248.unk_20->unk_80 = ((s16 *)&D_800AA248.unk_20->unk_18)[1] + 0xF23;
            D_800AA248.unk_20->unk_10 = 0;
            ai->unk_C = 0;
            if (ai->unk_28->unk_8->unk_14 == 4) {
                ai->unk_A = 0x15;
                ai->unk_8 = 0x46;
                if (D_800AA248.unk_20->unk_22 & 0x10) {
                    D_800AA248.unk_20->unk_C = 0xC000;
                    D_800AA248.unk_20->unk_84 = 0x400;
                } else {
                    D_800AA248.unk_20->unk_C = -0xC000;
                    D_800AA248.unk_20->unk_84 = -0x400;
                }
            } else {
                if (ai->unk_A != 0xB) {
                    ai->unk_A = 0xD;
                    ai->unk_8 = 0x36;
                } else {
                    ai->unk_A = 0xE;
                    ai->unk_8 = 0x37;
                }
            }
        }
    }
    func_80041A70(handlers, ai);
}

void func_80041DA8(const AiHandler *handlers, Ai *ai) {
    if (ai->unk_C == 1) {
        ai->unk_A = 0xF;
        ai->unk_C = 0;
        ai->unk_8 = 0x1E;
        func_80041A70(handlers, ai);
    }
}

/* 98.2%: the mover pointer gets v1 and the velocity v0 in the original */
#ifdef NON_MATCHING
void func_80041DE4(const AiHandler *handlers, Ai *ai) {
    s32 vel;

    ai->unk_A = 0x10;
    ai->unk_C = 0;
    ai->unk_8 = 0x46;
    if ((u16)(ai->unk_6 - 0x17) >= 2) {
        vel = 0x20000;
        if (!(D_800AA248.unk_20->unk_22 & 0x10)) {
            vel = -0x30000;
        }
        vel |= 0x8000;
        D_800AA248.unk_20->unk_C = vel;
    }
    func_80041A70(handlers, ai);
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004160C", func_80041DE4);
#endif

/* 99.9%: the reload of the mover pointer gets v1, not a0 */
#ifdef NON_MATCHING
void func_80041E54(const AiHandler *handlers, Ai *ai) {
    s32 vel;
    s32 accel;
    s32 kind;

    D_800AA248.unk_4C = 0;
    accel = D_800AA248.unk_20->unk_84;
    vel = D_800AA248.unk_20->unk_C;
    if (accel != 0) {
        vel += accel;
        if (vel < -0x28000) {
            vel = -0x28000;
        }
        D_800AA248.unk_20->unk_C = vel;
    }
    D_800AA248.unk_20->unk_14 = (vel + D_800AA248.unk_20->unk_14) & D_801D8864;
    if (D_800AA248.unk_20->unk_6C & 0x80) {
        kind = 1;
        if (D_800AA248.unk_20->unk_22 & 0x10) {
            kind = 2;
        }
        if (func_8004B6C4(ai->unk_0, 0x64, kind) == 1) {
            func_8003DAA0(ai);
        }
    } else {
        if (ai->unk_38 == 0) {
            if (func_8003E79C(D_800AA248.unk_20, vel) == 1) {
                D_800AA248.unk_20->unk_22 ^= 0x10;
                D_800AA248.unk_20->unk_C = -D_800AA248.unk_20->unk_C;
                D_800AA248.unk_20->unk_84 = -D_800AA248.unk_20->unk_84;
                ai->unk_38 = 0xB4;
                return;
            }
        } else {
            ai->unk_38--;
        }
        if (D_800AA248.unk_4C != 0) {
            D_800AA248.unk_20->unk_C = 0;
            D_800AA248.unk_20->unk_10 = 0;
            D_800AA248.unk_20->unk_88 = 0;
            ai->unk_8 = 5;
        }
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004160C", func_80041E54);
#endif

/* 97.9%: register allocation of the mover pointer and the velocity */
#ifdef NON_MATCHING
void func_80042008(const AiHandler *handlers, Ai *ai) {
    s32 vel;

    D_800AA248.unk_20->unk_14 = (D_800AA248.unk_20->unk_14 - D_800AA248.unk_20->unk_C) & D_801D8864;
    vel = D_800AA248.unk_20->unk_10 + D_800AA248.unk_20->unk_88;
    if (vel > 0x60000) {
        vel = 0x60000;
    }
    D_800AA248.unk_20->unk_10 = vel;
    D_800AA248.unk_20->unk_18 += vel;
    if (((s16 *)&D_800AA248.unk_20->unk_18)[1] >= 0xD9) {
        D_800AA248.unk_20->unk_C = 0;
        D_800AA248.unk_20->unk_10 = 0;
        D_800AA248.unk_20->unk_88 = 0;
        ai->unk_8 = 0x4E;
        return;
    }
    if (ai->unk_A != 0x14) {
        ai->unk_A = 0x14;
        func_80041A70(handlers, ai);
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004160C", func_80042008);
#endif

void func_800420F8(const AiHandler *handlers, Ai *ai) {
    if (ai->unk_C == 1) {
        ai->unk_A = 0x12;
        ai->unk_C = 0;
        ai->unk_8 = 0x4C;
        func_80041A70(handlers, ai);
    }
}

void func_80042134(const AiHandler *handlers, Ai *ai) {
    if (ai->unk_C == 1) {
        ai->unk_A = 0x13;
        ai->unk_C = 0;
        ai->unk_8 = 0x4D;
        func_80041A70(handlers, ai);
    }
}

void func_80042170(Ai *ai) {
    func_800416AC(D_8007E6C8, ai);
}

void func_80042198(Ai *ai) {
    func_800416AC(D_8007E778, ai);
}

void func_800421C0(Ai *ai) {
    func_800416AC(D_8007E7D0, ai);
}

void func_800421E8(Ai *ai) {
    func_800416AC(D_8007E988, ai);
}

void func_80042210(Ai *ai) {
    func_800416AC(D_8007E9E0, ai);
}

/* 89.8%: the far/near s16 copies: the original keeps the target x in a1 without a second load */
#ifdef NON_MATCHING
void func_80042238(Ai *ai) {
    Mover *target;
    s16 tx;
    s16 x;
    s16 far;
    s16 near;
    s32 dist;

    if (ai->unk_14 != NULL) {
        target = ai->unk_14->unk_68;
        if (target == NULL) {
            ai->unk_14 = NULL;
            return;
        }
        tx = ((s16 *)&target->unk_14)[1];
        x = ((s16 *)&D_800AA248.unk_20->unk_14)[1];
        near = x;
        dist = tx - x;
        if (dist < 0) {
            dist = -dist;
        }
        far = tx;
        if (dist >= 0x1C3) {
            if (D_801F9ACA >= tx) {
                far += (D_801D8864 + 1) >> 16;
            } else {
                near += (D_801D8864 + 1) >> 16;
            }
        }
        if ((far < near - 0xE && (D_800AA248.unk_20->unk_22 & 0x10)) ||
            (near < far && !(D_800AA248.unk_20->unk_22 & 0x10))) {
            func_8004E99C(near, tx);
        }
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004160C", func_80042238);
#endif

void func_80042358(void) {
    func_8003EB5C(D_8008E6AC, D_800AA248.unk_20);
}

void func_80042384(void) {
    func_8003EB5C(D_8008E6EC, D_800AA248.unk_20);
}

void func_800423B0(void) {
    func_8003EB5C(D_8008E724, D_800AA248.unk_20);
}

void func_800423DC(void) {
    func_8003EB5C(D_8008E730, D_800AA248.unk_20);
}

void func_80042408(void) {
    func_8003EB5C(D_8008E7A0, D_800AA248.unk_20);
}

void func_80042434(void) {
    func_8003EB5C(D_8008E868, D_800AA248.unk_20);
}

void func_80042460(void) {
    func_8003EB5C(D_8008E988, D_800AA248.unk_20);
}

void func_8004248C(void) {
    func_8003EB5C(D_8008E994, D_800AA248.unk_20);
}

void func_800424B8(void) {
    func_8003EB5C(D_8008E9AC, D_800AA248.unk_20);
}

void func_800424E4(void) {
    func_8003EB5C(D_8008E9C4, D_800AA248.unk_20);
}

void func_80042510(void) {
    func_8003EB5C(D_8008E988, D_800AA248.unk_20);
}

void func_8004253C(void) {
    func_8003EB5C(D_8008EA44, D_800AA248.unk_20);
}

void func_80042568(void) {
    func_8003EB5C(D_8008EA5C, D_800AA248.unk_20);
}

void func_80042594(void) {
    func_8003EB5C(D_8008EA74, D_800AA248.unk_20);
}

void func_800425C0(void) {
    func_8003EB5C(D_8008E988, D_800AA248.unk_20);
}

void func_800425EC(void) {
    func_8003EB5C(D_8008EBD0, D_800AA248.unk_20);
}

void func_80042618(void) {
    func_8003EB5C(D_8008EC00, D_800AA248.unk_20);
}

void func_80042644(void) {
    func_8003EB5C(D_8008EC28, D_800AA248.unk_20);
}

void func_80042670(void) {
    u8 *tbl;

    switch (func_8004A468()) {
    case 0:
        tbl = D_8008EC34;
        break;
    case 1: case 2:
        tbl = D_8008ECC0;
        break;
    case 3: case 4:
        tbl = D_8008ED4C;
        break;
    case 5: case 6:
        tbl = D_8008EDD8;
        break;
    default:
        tbl = D_8008EE64;
        break;
    }
    func_8003EB5C(tbl, D_800AA248.unk_20);
}

void func_80042704(void) {
    u8 *tbl;

    switch (func_8004A468()) {
    case 0: case 1:
        tbl = D_8008EFF0;
        break;
    case 2:
        tbl = D_8008F0F0;
        break;
    case 3:
        tbl = D_8008F1F0;
        break;
    case 4:
        tbl = D_8008F2F0;
        break;
    case 5:
        tbl = D_8008F3F0;
        break;
    default:
        tbl = D_8008F4F0;
        break;
    }
    func_8003EB5C(tbl, D_800AA248.unk_20);
}

void func_800427A4(void) {
    u8 *tbl;

    switch (func_8004A468()) {
    case 0: case 1:
        tbl = D_8008F864;
        break;
    case 2:
        tbl = D_8008F9D8;
        break;
    case 3:
        tbl = D_8008FB4C;
        break;
    case 4:
        tbl = D_8008FCC0;
        break;
    case 5:
        tbl = D_8008FE34;
        break;
    default:
        tbl = D_8008FFA8;
        break;
    }
    func_8003EB5C(tbl, D_800AA248.unk_20);
}

void func_80042844(void) {
    func_8003EB5C(D_8008EAD4, D_800AA248.unk_20);
}

void func_80042870(void) {
    func_8003EB5C(D_8008EAFC, D_800AA248.unk_20);
}

void func_8004289C(void) {
    func_8003EB5C(D_8008EB24, D_800AA248.unk_20);
}

void func_800428C8(void) {
    func_8003EB5C(D_8008EB5C, D_800AA248.unk_20);
}

void func_800428F4(void) {
    func_8003EB5C(D_8008EB84, D_800AA248.unk_20);
}

void func_80042920(void) {
    func_8003EB5C(D_8008EB9C, D_800AA248.unk_20);
}

void func_8004294C(void) {
    func_8003EB5C(D_8008E988, D_800AA248.unk_20);
}

void func_80042978(void) {
    func_8003EB5C(D_80090290, D_800AA248.unk_20);
}

void func_800429A4(void) {
    u8 *tbl;

    switch (func_8004A468()) {
    case 0:
        tbl = D_800902C0;
        break;
    case 1: case 2:
        tbl = D_800903E4;
        break;
    case 3: case 4:
        tbl = D_80090508;
        break;
    case 5: case 6:
        tbl = D_8009062C;
        break;
    default:
        tbl = D_80090750;
        break;
    }
    func_8003EB5C(tbl, D_800AA248.unk_20);
}

void func_80042A38(void) {
    u8 *tbl;

    switch (func_8004A468()) {
    case 0:
        tbl = D_80090330;
        break;
    case 1: case 2:
        tbl = D_80090454;
        break;
    case 3: case 4:
        tbl = D_80090578;
        break;
    case 5: case 6:
        tbl = D_8009069C;
        break;
    default:
        tbl = D_800907C0;
        break;
    }
    func_8003EB5C(tbl, D_800AA248.unk_20);
}

void func_80042ACC(void) {
    u8 *tbl;

    switch (func_8004A468()) {
    case 0:
        tbl = D_80090374;
        break;
    case 1: case 2:
        tbl = D_80090498;
        break;
    case 3: case 4:
        tbl = D_800905BC;
        break;
    case 5: case 6:
        tbl = D_800906E0;
        break;
    default:
        tbl = D_80090804;
        break;
    }
    func_8003EB5C(tbl, D_800AA248.unk_20);
}

void func_80042B60(void) {
    func_8003EB5C(D_80090928, D_800AA248.unk_20);
}

void func_80042B8C(void) {
    func_8003EB5C(D_80090960, D_800AA248.unk_20);
}

void func_80042BB8(void) {
    func_8003EB5C(D_80090998, D_800AA248.unk_20);
}

void func_80042BE4(void) {
    func_8003EB5C(D_80090D4C, D_800AA248.unk_20);
}

void func_80042C10(void) {
    func_8003EB5C(D_80090D94, D_800AA248.unk_20);
}

void func_80042C3C(void) {
    func_8003EB5C(D_80090DCC, D_800AA248.unk_20);
}

void func_80042C68(void) {
    func_8003EB5C(D_80090E60, D_800AA248.unk_20);
}

void func_80042C94(void) {
    func_8003EB5C(D_80090E98, D_800AA248.unk_20);
}

void func_80042CC0(void) {
    func_8003EB5C(D_80090EE8, D_800AA248.unk_20);
}

void func_80042CEC(void) {
    func_8003EB5C(D_80090DDC, D_800AA248.unk_20);
}

void func_80042D18(void) {
    func_8003EB5C(D_80090DE8, D_800AA248.unk_20);
}

void func_80042D44(void) {
    func_8003EB5C(D_80090DE8, D_800AA248.unk_20);
}

void func_80042D70(void) {
    func_8003EB5C(D_80090AF4, D_800AA248.unk_20);
}

void func_80042D9C(void) {
    func_8003EB5C(D_8008E988, D_800AA248.unk_20);
}

void func_80042DC8(void) {
    func_8003EB5C(D_8008C724, D_800AA248.unk_20);
}

void func_80042DF4(void) {
    func_8003EB5C(D_80090BD4, D_800AA248.unk_20);
}

void func_80042E20(void) {
    u8 *tbl;

    switch (func_8004A468()) {
    case 0: case 1:
        tbl = D_80090F68;
        break;
    case 2:
        tbl = D_800910A4;
        break;
    case 3:
        tbl = D_800911E0;
        break;
    case 4:
        tbl = D_800912F0;
        break;
    case 5:
        tbl = D_80091400;
        break;
    default:
        tbl = D_8009153C;
        break;
    }
    func_8003EB5C(tbl, D_800AA248.unk_20);
}

void func_80042EC0(void) {
    u8 *tbl;

    switch (func_8004A468()) {
    case 0: case 1:
        tbl = D_80090FE0;
        break;
    case 2:
        tbl = D_8009111C;
        break;
    case 3:
        tbl = D_80091258;
        break;
    case 4:
        tbl = D_80091368;
        break;
    case 5:
        tbl = D_80091478;
        break;
    default:
        tbl = D_800915B4;
        break;
    }
    func_8003EB5C(tbl, D_800AA248.unk_20);
}

void func_80042F60(void) {
    u8 *tbl;

    switch (func_8004A468()) {
    case 0: case 1:
        tbl = D_80091058;
        break;
    case 2:
        tbl = D_80091194;
        break;
    case 3:
        tbl = D_800912A4;
        break;
    case 4:
        tbl = D_800913B4;
        break;
    case 5:
        tbl = D_800914F0;
        break;
    default:
        tbl = D_8009162C;
        break;
    }
    func_8003EB5C(tbl, D_800AA248.unk_20);
}

void func_80043000(void) {
    func_8003EB5C(D_80097020, D_800AA248.unk_20);
}

void func_8004302C(void) {
    func_8003EB5C(D_80097050, D_800AA248.unk_20);
}

void func_80043058(void) {
    func_8003EB5C(D_80097078, D_800AA248.unk_20);
}

void func_80043084(void) {
    u8 *tbl;

    switch (func_8004A468()) {
    case 0:
        tbl = D_80097084;
        break;
    case 1: case 2:
        tbl = D_80097110;
        break;
    case 3: case 4:
        tbl = D_8009719C;
        break;
    case 5: case 6:
        tbl = D_80097228;
        break;
    default:
        tbl = D_800972B4;
        break;
    }
    func_8003EB5C(tbl, D_800AA248.unk_20);
}
