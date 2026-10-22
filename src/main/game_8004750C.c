/* The monsters' attacks and the objects they throw: script commands that spawn and drive them, the hit tests
 * against monsters, and the attack table. Named after its first function until the rest is understood.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "gameobject.h"
#include "psyq/libc2.h"

void func_8001E4B0(GameObject *obj);                        /* free an object */
void func_8001F724(s32 sound);
void func_8001F7CC(s32 sound, s32 variant);
u16 *func_80025C08(void *);
s32 func_80025DF8(s32 player);
void func_80029118(s32, s32);
void func_80053C50(s32, Monster *m);
void func_8006353C(s32);
void func_8004A9B0(s32, s32, s32, s32, s32);
void func_8004B204(void);
void func_8004B3D0(void);
void func_8004AEA4(void *slot);
u16 func_8004B6C4(GameObject *obj, s16 range, s32 mode);
void func_8004EFAC(void);
void func_8004AF80(void);
void func_8004AF1C();

extern u8 D_8007F634[];
extern s16 D_801D8850;
extern s16 D_801D8724;
extern u8 D_801E1CC4[];                /* 21 slots of 0x10 bytes */
extern u8 D_801F9A54[];                /* 3 records of 0x1C bytes */
extern u16 D_801E2A4C;
extern s16 D_801E2A54;
extern u16 D_801E1C8C;
extern s16 D_801E1C80;
extern s16 D_801E0D60;
extern s16 D_801E28D0;
extern s16 D_801E28F0;
extern s32 D_801FA7D8;
extern s16 D_801E0D4C;

/* A thrown object's bookkeeping (func_8004B660). */
typedef struct {
    /* 0x00 */ GameObject *obj;
    /* 0x04 */ u8 unk_04[0x0A];
    /* 0x0E */ u16 armed;
} Throw;

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004750C);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80047554);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_800475F4);

void func_800476A8(void) {
    u8 *slot;
    u16 n;

    n = 0x15;
    slot = D_801E1CC4;
    do {
        func_8004AEA4(slot);
        slot += 0x10;
    } while (--n != 0);
    D_801D8724 = n;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_800476FC);

#ifdef NON_MATCHING
/* 98%: register names only: the original tests the object's flags in v1 and keeps the operands' address in v0, here the other way round */
void func_80047780(void) {
    GameObject *saved = D_800AA248.cur_obj;
    u16 *arg = saved->arg.h;
    u16 variant = arg[0];
    u16 sound = arg[1];

    if (!(saved->unk_6C & 0x80)) {
        if (variant != 0) {
            func_8001F7CC(sound, variant);
        }
        func_8004A9B0(0, 0, 23, 0, 0);
    }
    D_800AA248.cur_obj = saved;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80047780);
#endif

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_800477F0);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004799C);

#ifdef NON_MATCHING
/* 98%: register names only: the original tests the object's flags in v1 and keeps the operands' address in v0, here the other way round */
void func_80047A1C(void) {
    GameObject *saved = D_800AA248.cur_obj;
    u16 *arg = saved->arg.h;
    u16 variant = arg[0];
    u16 sound = arg[1];

    if (!(saved->unk_6C & 0x80)) {
        if (variant != 0) {
            func_8001F7CC(sound, variant);
        }
        func_8004A9B0(0, 0, 2, 0, 0);
    }
    D_800AA248.cur_obj = saved;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80047A1C);
#endif

#ifdef NON_MATCHING
/* 98%: register names only: the original tests the object's flags in v1 and keeps the operands' address in v0, here the other way round */
void func_80047A8C(void) {
    GameObject *saved = D_800AA248.cur_obj;
    u16 *arg = saved->arg.h;
    u16 variant = arg[0];
    u16 sound = arg[1];

    if (!(saved->unk_6C & 0x80)) {
        if (variant != 0) {
            func_8001F7CC(sound, variant);
        }
        func_8004A9B0(0, 0, 8, 0, 0);
    }
    D_800AA248.cur_obj = saved;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80047A8C);
#endif

#ifdef NON_MATCHING
/* 98%: register names only: the original tests the object's flags in v1 and keeps the operands' address in v0, here the other way round */
void func_80047AFC(void) {
    GameObject *saved = D_800AA248.cur_obj;
    u16 *arg = saved->arg.h;
    u16 variant = arg[0];
    u16 sound = arg[1];

    if (!(saved->unk_6C & 0x80)) {
        if (variant != 0) {
            func_8001F7CC(sound, variant);
        }
        func_8004A9B0(0, 0, 11, 0, 0);
    }
    D_800AA248.cur_obj = saved;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80047AFC);
#endif

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80047B6C);

#ifdef NON_MATCHING
/* 98%: register names only: the original tests the object's flags in v1 and keeps the operands' address in v0, here the other way round */
void func_80047C9C(void) {
    GameObject *saved = D_800AA248.cur_obj;
    u16 *arg = saved->arg.h;
    u16 variant = arg[0];
    u16 sound = arg[1];

    if (!(saved->unk_6C & 0x80)) {
        if (variant != 0) {
            func_8001F7CC(sound, variant);
        }
        func_8004A9B0(0, 0, 3, 0, 0);
    }
    D_800AA248.cur_obj = saved;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80047C9C);
#endif

#ifdef NON_MATCHING
/* 98%: register names only: the original tests the object's flags in v1 and keeps the operands' address in v0, here the other way round */
void func_80047D0C(void) {
    GameObject *saved = D_800AA248.cur_obj;
    u16 *arg = saved->arg.h;
    u16 variant = arg[0];
    u16 sound = arg[1];

    if (!(saved->unk_6C & 0x80)) {
        if (variant != 0) {
            func_8001F7CC(sound, variant);
        }
        func_8004A9B0(0, 0, 4, 0, 0);
    }
    D_800AA248.cur_obj = saved;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80047D0C);
#endif

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80047D7C);

void func_80047DCC(void) {
    D_800AA248.cur_obj->script_pc = *D_800AA248.cur_obj->arg.w;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80047DEC);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80047EA0);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80047F64);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80048070);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_800481FC);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80048384);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80048558);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004874C);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_800488B8);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_800489C0);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80048B98);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80048D4C);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80048E6C);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80048F60);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_800490D4);

void func_8004928C(void) {
    if (D_800AA248.cur_obj->vel_y.v <= -0x10000) {
        D_800AA248.cur_obj->script_pc = *D_800AA248.cur_obj->arg.w;
    }
}

void func_800492C8(void) {
    if (D_800AA248.cur_obj->vel_y.v <= 0x10000) {
        D_800AA248.cur_obj->script_pc = *D_800AA248.cur_obj->arg.w;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80049304);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_800494B4);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80049650);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80049850);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_800499F4);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80049B9C);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80049D90);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_80049E10);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004A044);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004A1F8);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004A468);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004A51C);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004A698);

void func_8004A90C(Monster *m) {
    m->action = 0x20;
    m->obj->vel_y.v = 0xFFF70000;
    m->unk_104 = 0x4000;
    m->unk_100 = 0;
    m->unk_1B0 = 0;
    m->unk_1B2 = 0;
    m->unk_1B4 = 0;
}

#ifdef NON_MATCHING
/* 99%: register names only: the action in v0 and the side in v1 in the original */
void func_8004A93C(Monster *m) {
    s16 action;
    u16 side = m->unk_1B0;

    if (side != 0) {
        action = 0x3A;
        if (side != 3) {
            func_8004EFAC();
            action = 0x12;
        }
    } else {
        action = 0x3A;
        if (m->obj->pos_y.p.i < 0xE1) {
            func_8004EFAC();
            action = 0xF;
        }
    }
    m->action = action;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004A93C);
#endif

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004A9B0);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004AC84);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004AD18);

void func_8004AE2C(void) {
    void *other = D_800AA248.cur_obj->unk_94;

    func_8001E4B0(D_800AA248.cur_obj);
    if (other != NULL) {
        func_8004AEA4(other);
    }
    if (D_801D8724 != 0) {
        D_801D8724 = (u16) D_801D8724 - 1;
    }
}

void func_8004AE84(void) {
    D_800AA248.cur_obj->vel_x.v >>= 1;
}

void func_8004AEA4(void *slot) {
    memset(slot, 0, 0x10);
}

void func_8004AEC8(void) {
    D_800AA248.cur_obj->owner.monster->unk_02A = 0;
}

void func_8004AEE0(void) {
    D_801D8850 = 3;
    func_8004AF1C(*func_80025C08(D_8007F634));
}

/* Defined the old way: func_8004AEE0 above passes it a u16 it reads from a table. */
void func_8004AF1C(arg0)
s16 arg0;
{
    D_801E1C80 = arg0;
    D_801E2A54 = 1;
    D_801E2A4C = 1;
    D_801E1C8C = 0;
    D_801E0D60 = 0;
    D_801E28D0 = 0;
    D_801E28F0 = 0;
    D_801FA7D8 = 0x64;
    func_8004AF80();
}

void func_8004AF80(void) {
    u8 *rec;
    u16 n;

    rec = D_801F9A54;
    n = 3;
    do {
        memset(rec, 0, 0x1C);
        rec += 0x1C;
    } while (--n != 0);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004AFD4);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004B038);

void func_8004B17C(void) {
    if (D_801E1C8C == 1) {
        func_8004B1C8();
        return;
    }
    if (D_801E1C8C < 4) {
        func_8004B3D0();
    }
}

void func_8004B1C8(void) {
    if (D_801E2A4C == 1) {
        func_8004B204();
        D_801E2A54 = 6;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004B204);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004B3D0);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004B540);

u16 func_8004B660(Throw *t, GameObject *target, s16 range, s32 mode) {
    u16 armed = t->armed;

    if (target->unk_6C & 0x80) {
        if (armed != 0) {
            return func_8004B6C4(t->obj, range, mode & 0xFFFF);
        }
    } else if (armed == 0) {
        t->armed = 1;
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004B6C4);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004B754);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004B80C);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004B990);

void func_8004BAC0(void) {
    s32 i;
    s32 id;
    Monster *m;
    u16 action;

    i = 0;
    do {
        id = func_80025DF8(i + 1);
        if (D_801FA8A0[id - 1] != 0) {
            m = &D_801E0B78[id];
            action = m->action;
            if (action != 0x37 && action != 0x26 && D_801E0D4C == 0) {
                func_80053C50(0x1E0000, m);
                func_8001F724(0x64);
                action = m->action;
                if ((u16) (action - 0x34) >= 2 && action != 0x2A && action != 0x63 && action != 0x47) {
                    m->action = 0xA;
                }
            }
        }
        i++;
    } while (i < 3);
    func_80029118(0xC, 0x10);
    func_8006353C(7);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004BBC8);

INCLUDE_ASM("asm/main/nonmatchings/game_8004750C", func_8004BFE0);
