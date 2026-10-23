/* A file of the game's code, named after its first function until its contents are understood.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "game.h"

void func_8003EB5C(u8 *table, Mover *mover);
u16 func_8004A468(void);

extern u8 D_80096D44[];
extern u8 D_80096D84[];
extern u8 D_80096DBC[];
extern u8 D_80096DC8[];
extern u8 D_80096E38[];
extern u8 D_80096F00[];
extern u8 D_8008C864[];
extern u8 D_8008C894[];
extern u8 D_8008C8BC[];
extern u8 D_8008C8C8[];
extern u8 D_8008C938[];
extern u8 D_8008C9A8[];
extern u8 D_8008CA18[];
extern u8 D_8008CA88[];
extern u8 D_8008CAF8[];
extern u8 D_8008CB68[];
extern u8 D_8008CBD8[];
extern u8 D_8008CC48[];
extern u8 D_8008CCB8[];
extern u8 D_8008CD28[];
extern u8 D_8008CD98[];
extern u8 D_8008CE08[];
extern u8 D_8008CE78[];
extern u8 D_8008CF40[];
extern u8 D_8008D008[];
extern u8 D_8008D0D0[];
extern u8 D_8008D198[];
extern u8 D_8008D260[];
extern u8 D_8008D328[];
extern u8 D_8008D3F0[];
extern u8 D_8008D4B8[];
extern u8 D_8008D4E0[];
extern u8 D_8008D548[];
extern u8 D_8008D580[];
extern u8 D_8008D5C0[];
extern u8 D_8008D508[];
extern u8 D_8008D514[];
extern u8 D_8008C858[];
extern u8 D_8008D6CC[];
extern u8 D_8008D714[];
extern u8 D_8008D75C[];
extern u8 D_8008D768[];
extern u8 D_8008D954[];
extern u8 D_8008DB64[];
extern u8 D_8008DD50[];
extern u8 D_8008DF60[];
extern u8 D_8008E170[];
extern u8 D_8008E35C[];
extern u8 D_8008D7F4[];
extern u8 D_8008DA04[];
extern u8 D_8008DC14[];
extern u8 D_8008DE00[];
extern u8 D_8008E010[];
extern u8 D_8008E220[];
extern u8 D_8008E40C[];
extern u8 D_8008D8A4[];
extern u8 D_8008DAB4[];
extern u8 D_8008DCA0[];
extern u8 D_8008DEB0[];
extern u8 D_8008E0C0[];
extern u8 D_8008E2D0[];
extern u8 D_8008E4BC[];
extern u8 D_8008E56C[];
extern u8 D_8008E594[];
extern u8 D_8008E5BC[];
extern u8 D_8008E63C[];
extern u8 D_8008E674[];
extern u8 D_8008E5F4[];
extern u8 D_8008E608[];
extern u8 D_8008D6C0[];
extern u8 D_8008E6AC[];
/* The same empty table under the other names the original gave it, one per range class of func_8004A468 (the
 * link put them at one address: config/aliases.ld). */
extern u8 D_8008E6AC_1[];
extern u8 D_8008E6AC_2[];
extern u8 D_8008E6AC_3[];
extern u8 D_8008E6AC_4[];

void func_80043118(void) {
    func_8003EB5C(D_80096D44, D_800AA248.unk_20);
}

void func_80043144(void) {
    func_8003EB5C(D_80096D84, D_800AA248.unk_20);
}

void func_80043170(void) {
    func_8003EB5C(D_80096DBC, D_800AA248.unk_20);
}

void func_8004319C(void) {
    func_8003EB5C(D_80096DC8, D_800AA248.unk_20);
}

void func_800431C8(void) {
    func_8003EB5C(D_80096E38, D_800AA248.unk_20);
}

void func_800431F4(void) {
    func_8003EB5C(D_80096F00, D_800AA248.unk_20);
}

void func_80043220(void) {
    func_8003EB5C(D_8008C864, D_800AA248.unk_20);
}

void func_8004324C(void) {
    func_8003EB5C(D_8008C894, D_800AA248.unk_20);
}

void func_80043278(void) {
    func_8003EB5C(D_8008C8BC, D_800AA248.unk_20);
}

void func_800432A4(void) {
    u8 *tbl;

    switch (func_8004A468()) {
    case 0:
        tbl = D_8008C8C8;
        break;
    case 1: case 2:
        tbl = D_8008C938;
        break;
    case 3: case 4:
        tbl = D_8008C9A8;
        break;
    case 5: case 6:
        tbl = D_8008CA18;
        break;
    default:
        tbl = D_8008CA88;
        break;
    }
    func_8003EB5C(tbl, D_800AA248.unk_20);
}

void func_80043338(void) {
    u8 *tbl;

    switch (func_8004A468()) {
    case 0:
        tbl = D_8008CAF8;
        break;
    case 1:
        tbl = D_8008CB68;
        break;
    case 2:
        tbl = D_8008CBD8;
        break;
    case 3:
        tbl = D_8008CC48;
        break;
    case 4:
        tbl = D_8008CCB8;
        break;
    case 5:
        tbl = D_8008CD28;
        break;
    case 6:
        tbl = D_8008CD98;
        break;
    default:
        tbl = D_8008CE08;
        break;
    }
    func_8003EB5C(tbl, D_800AA248.unk_20);
}

void func_800433F0(void) {
    u8 *tbl;

    switch (func_8004A468()) {
    case 0:
        tbl = D_8008CE78;
        break;
    case 1:
        tbl = D_8008CF40;
        break;
    case 2:
        tbl = D_8008D008;
        break;
    case 3:
        tbl = D_8008D0D0;
        break;
    case 4:
        tbl = D_8008D198;
        break;
    case 5:
        tbl = D_8008D260;
        break;
    case 6:
        tbl = D_8008D328;
        break;
    default:
        tbl = D_8008D3F0;
        break;
    }
    func_8003EB5C(tbl, D_800AA248.unk_20);
}

void func_800434A8(void) {
    func_8003EB5C(D_8008D4B8, D_800AA248.unk_20);
}

void func_800434D4(void) {
    func_8003EB5C(D_8008D4E0, D_800AA248.unk_20);
}

void func_80043500(void) {
    func_8003EB5C(D_8008D548, D_800AA248.unk_20);
}

void func_8004352C(void) {
    func_8003EB5C(D_8008D548, D_800AA248.unk_20);
}

void func_80043558(void) {
    func_8003EB5C(D_8008D580, D_800AA248.unk_20);
}

void func_80043584(void) {
    func_8003EB5C(D_8008D5C0, D_800AA248.unk_20);
}

void func_800435B0(void) {
    func_8003EB5C(D_8008D508, D_800AA248.unk_20);
}

void func_800435DC(void) {
    func_8003EB5C(D_8008D514, D_800AA248.unk_20);
}

void func_80043608(void) {
    func_8003EB5C(D_8008C858, D_800AA248.unk_20);
}

void func_80043634(void) {
    func_8003EB5C(D_8008D6CC, D_800AA248.unk_20);
}

void func_80043660(void) {
    func_8003EB5C(D_8008D714, D_800AA248.unk_20);
}

void func_8004368C(void) {
    func_8003EB5C(D_8008D75C, D_800AA248.unk_20);
}

void func_800436B8(void) {
    u8 *tbl;

    switch (func_8004A468()) {
    case 1:
        tbl = D_8008D768;
        break;
    case 2:
        tbl = D_8008D954;
        break;
    case 3:
        tbl = D_8008DB64;
        break;
    case 4:
        tbl = D_8008DD50;
        break;
    case 5:
        tbl = D_8008DF60;
        break;
    case 6:
        tbl = D_8008E170;
        break;
    default:
        tbl = D_8008E35C;
        break;
    }
    func_8003EB5C(tbl, D_800AA248.unk_20);
}

void func_80043768(void) {
    u8 *tbl;

    switch (func_8004A468()) {
    case 1:
        tbl = D_8008D7F4;
        break;
    case 2:
        tbl = D_8008DA04;
        break;
    case 3:
        tbl = D_8008DC14;
        break;
    case 4:
        tbl = D_8008DE00;
        break;
    case 5:
        tbl = D_8008E010;
        break;
    case 6:
        tbl = D_8008E220;
        break;
    default:
        tbl = D_8008E40C;
        break;
    }
    func_8003EB5C(tbl, D_800AA248.unk_20);
}

void func_80043818(void) {
    u8 *tbl;

    switch (func_8004A468()) {
    case 1:
        tbl = D_8008D8A4;
        break;
    case 2:
        tbl = D_8008DAB4;
        break;
    case 3:
        tbl = D_8008DCA0;
        break;
    case 4:
        tbl = D_8008DEB0;
        break;
    case 5:
        tbl = D_8008E0C0;
        break;
    case 6:
        tbl = D_8008E2D0;
        break;
    default:
        tbl = D_8008E4BC;
        break;
    }
    func_8003EB5C(tbl, D_800AA248.unk_20);
}

void func_800438C8(void) {
    func_8003EB5C(D_8008E56C, D_800AA248.unk_20);
}

void func_800438F4(void) {
    func_8003EB5C(D_8008E594, D_800AA248.unk_20);
}

void func_80043920(void) {
    func_8003EB5C(D_8008E5BC, D_800AA248.unk_20);
}

void func_8004394C(void) {
    func_8003EB5C(D_8008E5BC, D_800AA248.unk_20);
}

void func_80043978(void) {
    func_8003EB5C(D_8008E63C, D_800AA248.unk_20);
}

void func_800439A4(void) {
    func_8003EB5C(D_8008E674, D_800AA248.unk_20);
}

void func_800439D0(void) {
    func_8003EB5C(D_8008E5F4, D_800AA248.unk_20);
}

void func_800439FC(void) {
    func_8003EB5C(D_8008E608, D_800AA248.unk_20);
}

void func_80043A28(void) {
    func_8003EB5C(D_8008D6C0, D_800AA248.unk_20);
}

void func_80043A54(void) {
    func_8003EB5C(D_8008E6AC, D_800AA248.unk_20);
}

void func_80043A80(void) {
    func_8003EB5C(D_8008E6AC, D_800AA248.unk_20);
}

void func_80043AAC(void) {
    func_8003EB5C(D_8008E6AC, D_800AA248.unk_20);
}

void func_80043AD8(void) {
    func_8003EB5C(D_8008E6AC, D_800AA248.unk_20);
}

void func_80043B04(void) {
    func_8003EB5C(D_8008E6AC, D_800AA248.unk_20);
}

void func_80043B30(void) {
    func_8003EB5C(D_8008E6AC, D_800AA248.unk_20);
}

void func_80043B5C(void) {
    func_8003EB5C(D_8008E6AC, D_800AA248.unk_20);
}

void func_80043B88(void) {
    func_8003EB5C(D_8008E6AC, D_800AA248.unk_20);
}

void func_80043BB4(void) {
    func_8003EB5C(D_8008E6AC, D_800AA248.unk_20);
}

void func_80043BE0(void) {
    func_8003EB5C(D_8008E6AC, D_800AA248.unk_20);
}

void func_80043C0C(void) {
    switch (func_8004A468()) {
    case 0:
        func_8003EB5C(D_8008E6AC, D_800AA248.unk_20);
        break;
    case 1: case 2:
        func_8003EB5C(D_8008E6AC_1, D_800AA248.unk_20);
        break;
    case 3: case 4:
        func_8003EB5C(D_8008E6AC_2, D_800AA248.unk_20);
        break;
    case 5: case 6:
        func_8003EB5C(D_8008E6AC_3, D_800AA248.unk_20);
        break;
    default:
        func_8003EB5C(D_8008E6AC_4, D_800AA248.unk_20);
        break;
    }
}

void func_80043CC0(void) {
    switch (func_8004A468()) {
    case 0:
        func_8003EB5C(D_8008E6AC, D_800AA248.unk_20);
        break;
    case 1: case 2:
        func_8003EB5C(D_8008E6AC_1, D_800AA248.unk_20);
        break;
    case 3: case 4:
        func_8003EB5C(D_8008E6AC_2, D_800AA248.unk_20);
        break;
    case 5: case 6:
        func_8003EB5C(D_8008E6AC_3, D_800AA248.unk_20);
        break;
    default:
        func_8003EB5C(D_8008E6AC_4, D_800AA248.unk_20);
        break;
    }
}

void func_80043D74(void) {
    switch (func_8004A468()) {
    case 0:
        func_8003EB5C(D_8008E6AC, D_800AA248.unk_20);
        break;
    case 1: case 2:
        func_8003EB5C(D_8008E6AC_1, D_800AA248.unk_20);
        break;
    case 3: case 4:
        func_8003EB5C(D_8008E6AC_2, D_800AA248.unk_20);
        break;
    case 5: case 6:
        func_8003EB5C(D_8008E6AC_3, D_800AA248.unk_20);
        break;
    default:
        func_8003EB5C(D_8008E6AC_4, D_800AA248.unk_20);
        break;
    }
}
