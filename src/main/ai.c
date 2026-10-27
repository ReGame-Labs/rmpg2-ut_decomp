/* The behaviour slots (Ai): the action dispatcher (ai_dispatch_action) and the state handlers of the Ai kinds 13 to 21,
 * with their animation states.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "npc.h"

void func_8003EB5C(u8 *table, GameObject *mover);
u16 func_8004A468(Ai *ai);    /* defined returning s32: its callers take the low half */
s32 func_8003DC3C(Ai *);
void func_8003DB74(Ai *ai);
void func_8003DAA0(Ai *ai);
void func_8003E788(Ai *ai);
u16 func_8003E79C(void);
u16 func_8004B6C4(GameObject *, s16, s32);
void func_8004E99C(void);
s32 abs(s32 x);                 /* GCC's builtin: inlined */

void ai_dispatch_action(const AiHandler *handlers, Ai *ai);
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
void ai_face_target(Ai *ai);

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
    ai_dispatch_action(D_8007E828, ai);
}

void func_80041634(Ai *ai) {
    ai_dispatch_action(D_8007E720, ai);
}

void func_8004165C(Ai *ai) {
    ai_dispatch_action(D_8007E880, ai);
}

void func_80041684(Ai *ai) {
    ai_dispatch_action(D_8007E8D8, ai);
}

void ai_dispatch_action(const AiHandler *handlers, Ai *ai) {
    u16 hit;

    switch (ai->action) {
    case 0xA:
        func_80041928(handlers, ai);
        break;
    case 0xB:
        func_80041A3C(handlers, ai);
        break;
    case 0x32:
        func_80041B2C(handlers, ai);
        break;
    case 0x33:
        func_80041B2C(handlers, ai);
        break;
    case 0x36:
        func_80041DA8(handlers, ai);
        break;
    case 0x37:
        func_80041DA8(handlers, ai);
        break;
    case 0x3B:
        func_80041C0C(handlers, ai);
        break;
    case 0x3C:
        func_80041C0C(handlers, ai);
        break;
    case 0x1E:
        func_80041DE4(handlers, ai);
        break;
    case 0xF2:
        func_80042008(handlers, ai);
        break;
    case 0x46:
        func_80041E54(handlers, ai);
        break;
    case 0x4D:
        if (handlers == D_8007E930) {
            func_800420F8(handlers, ai);
        }
        break;
    case 0x4C:
        if (handlers == D_8007E930) {
            func_80042134(handlers, ai);
        }
        break;
    default:
        hit = func_8003DC3C(ai);
        if (hit != 0) {
            func_80041AD0(hit, handlers, ai);
            return;
        }
        ai_face_target(ai);
        if (ai->action == 0x15) {
            func_80041988(handlers, ai);
        } else if (ai->action == 0x16) {
            func_800419C4(handlers, ai);
        } else if (ai->action == 0x17) {
            func_80041A00(handlers, ai);
        } else {
            func_8003DB74(ai);
        }
        break;
    }
}

void func_80041928(const AiHandler *handlers, Ai *ai) {
    if (ai->state != 0) {
        if (ai->unk_0C == 1) {
            ai->state = 4;
            ai->unk_0C = 0;
            ai->action = 0x15;
            func_80041A70(handlers, ai);
        }
    } else {
        ai->unk_0C = 0;
        ai->state = 1;
        func_80041A70(handlers, ai);
    }
}

void func_80041988(const AiHandler *handlers, Ai *ai) {
    if (ai->unk_0C == 1) {
        ai->state = 5;
        ai->unk_0C = 0;
        ai->action = 0x16;
        func_80041A70(handlers, ai);
    }
}

void func_800419C4(const AiHandler *handlers, Ai *ai) {
    if (ai->unk_0C == 1) {
        ai->state = 6;
        ai->unk_0C = 0;
        ai->action = 0x17;
        func_80041A70(handlers, ai);
    }
}

void func_80041A00(const AiHandler *handlers, Ai *ai) {
    if (ai->unk_0C == 1) {
        ai->state = 3;
        ai->unk_0C = 0;
        ai->action = 0xB;
        func_80041A70(handlers, ai);
    }
}

void func_80041A3C(const AiHandler *handlers, Ai *ai) {
    if (ai->unk_0C == 1) {
        func_8003DB74(ai);
    }
}

void func_80041A70(const AiHandler *handlers, Ai *ai) {
    const AiHandler *handler;

    handler = handlers;
    handler += ai->state;
    (*handler)(ai);
}

void func_80041AA8(Ai *ai) {
    ai_dispatch_action(D_8007E930, ai);
}

void func_80041AD0(s16 hit, const AiHandler *handlers, Ai *ai) {
    if (hit != -1) {
        ai->state = 9;
        ai->unk_0C = 0;
        ai->action = 0x32;
    } else {
        ai->state = 0xA;
        ai->unk_0C = 0;
        ai->action = 0x33;
    }
    func_80041A70(handlers, ai);
}

void func_80041B2C(const AiHandler *handlers, Ai *ai) {
    s32 speed;

    ai->unk_34.s.hi = 0;
    if (ai->unk_0C == 1) {
        ai->unk_0C = 0;
        if (D_800AA248.cur_obj->pos_y.w <= 0x5F0000) {
            speed = 0x30000;
            ai->state = 0xC;
            ai->action = 0x3C;
        } else {
            speed = 0x2C000;
            ai->state = 0xB;
            ai->action = 0x3B;
        }
        ai->unk_24 = 1;
        if ((u16)(ai->kind - 0x17) < 2) {
            speed = 0x1E000;
        }
        D_800AA248.cur_obj->vel_y.w = speed;
        func_8003E788(ai);
        D_800AA248.cur_obj->priority = 0x353;
        func_80041A70(handlers, ai);
    }
}

void func_80041C0C(const AiHandler *handlers, Ai *ai) {
    s32 limit;

    if (ai->unk_24 != 0) {
        ai->unk_24 = 0;
        D_800AA248.cur_obj->pos_y.w += 0x1C0000;
    }
    limit = 0xD90000;
    if (D_801FA960 >= 0x64) {
        limit = 0xE00000;
    }
    D_800AA248.cur_obj->pos_y.w += D_800AA248.cur_obj->vel_y.w;
    if (D_800AA248.cur_obj->pos_y.w >= limit) {
        if (ai->unk_28.link != NULL && ai->unk_28.link->unk_8 != NULL) {
            D_800AA248.cur_obj->pos_y.w = limit;
            D_800AA248.cur_obj->priority = ((s16 *)&D_800AA248.cur_obj->pos_y.w)[1] + 0xF23;
            D_800AA248.cur_obj->vel_y.w = 0;
            ai->unk_0C = 0;
            if (ai->unk_28.link->unk_8->unk_14 == 4) {
                ai->state = 0x15;
                ai->action = 0x46;
                if (D_800AA248.cur_obj->flags & 0x10) {
                    D_800AA248.cur_obj->vel_x.w = 0xC000;
                    D_800AA248.cur_obj->unk_84 = 0x400;
                } else {
                    D_800AA248.cur_obj->vel_x.w = -0xC000;
                    D_800AA248.cur_obj->unk_84 = -0x400;
                }
            } else {
                if (ai->state != 0xB) {
                    ai->state = 0xD;
                    ai->action = 0x36;
                } else {
                    ai->state = 0xE;
                    ai->action = 0x37;
                }
            }
        }
    }
    func_80041A70(handlers, ai);
}

void func_80041DA8(const AiHandler *handlers, Ai *ai) {
    if (ai->unk_0C == 1) {
        ai->state = 0xF;
        ai->unk_0C = 0;
        ai->action = 0x1E;
        func_80041A70(handlers, ai);
    }
}

void func_80041DE4(const AiHandler *handlers, Ai *ai) {
    ai->state = 0x10;
    ai->unk_0C = 0;
    ai->action = 0x46;
    if ((u16)(ai->kind - 0x17) >= 2) {
        if (D_800AA248.cur_obj->flags & 0x10) {
            D_800AA248.cur_obj->vel_x.w = 0x28000;
        } else {
            D_800AA248.cur_obj->vel_x.w = -0x28000;
        }
    }
    func_80041A70(handlers, ai);
}

void func_80041E54(const AiHandler *handlers, Ai *ai) {
    s32 vel;
    s32 accel;
    s32 kind;

    D_800AA248.unk_4C = 0;
    accel = D_800AA248.cur_obj->unk_84;
    vel = D_800AA248.cur_obj->vel_x.w;
    if (accel != 0) {
        vel += accel;
        if (vel < -0x28000) {
            vel = -0x28000;
        }
        D_800AA248.cur_obj->vel_x.w = vel;
    }
    D_800AA248.cur_obj->pos_x.w = (vel + D_800AA248.cur_obj->pos_x.w) & D_801D8864.w;
    if (D_800AA248.cur_obj->unk_6C & 0x80) {
        kind = 1;
        if (D_800AA248.cur_obj->flags & 0x10) {
            kind = 2;
        }
        if (func_8004B6C4(ai->obj, 0x64, kind) == 1) {
            func_8003DAA0(ai);
        }
    } else {
        if (ai->unk_38 == 0) {
            if (func_8003E79C() == 1) {
                D_800AA248.cur_obj->flags ^= 0x10;
                D_800AA248.cur_obj->vel_x.w = -D_800AA248.cur_obj->vel_x.w;
                D_800AA248.cur_obj->unk_84 = -D_800AA248.cur_obj->unk_84;
                ai->unk_38 = 0xB4;
                return;
            }
        } else {
            ai->unk_38--;
        }
        if (D_800AA248.unk_4C != 0) {
            D_800AA248.cur_obj->vel_x.w = 0;
            D_800AA248.cur_obj->vel_y.w = 0;
            D_800AA248.cur_obj->unk_88 = 0;
            ai->action = 5;
        }
    }
}

void func_80042008(const AiHandler *handlers, Ai *ai) {
    s32 vel;

    vel = D_800AA248.cur_obj->pos_x.w - D_800AA248.cur_obj->vel_x.w;
    vel &= D_801D8864.w;
    D_800AA248.cur_obj->pos_x.w = vel;
    vel = D_800AA248.cur_obj->vel_y.w + D_800AA248.cur_obj->unk_88;
    if (vel > 0x60000) {
        vel = 0x60000;
    }
    D_800AA248.cur_obj->vel_y.w = vel;
    D_800AA248.cur_obj->pos_y.w += vel;
    if (D_800AA248.cur_obj->pos_y.s.hi >= 0xD9) {
        D_800AA248.cur_obj->vel_x.w = 0;
        D_800AA248.cur_obj->vel_y.w = 0;
        D_800AA248.cur_obj->unk_88 = 0;
        ai->action = 0x4E;
        return;
    }
    if (ai->state != 0x14) {
        ai->state = 0x14;
        func_80041A70(handlers, ai);
    }
}

void func_800420F8(const AiHandler *handlers, Ai *ai) {
    if (ai->unk_0C == 1) {
        ai->state = 0x12;
        ai->unk_0C = 0;
        ai->action = 0x4C;
        func_80041A70(handlers, ai);
    }
}

void func_80042134(const AiHandler *handlers, Ai *ai) {
    if (ai->unk_0C == 1) {
        ai->state = 0x13;
        ai->unk_0C = 0;
        ai->action = 0x4D;
        func_80041A70(handlers, ai);
    }
}

void func_80042170(Ai *ai) {
    ai_dispatch_action(D_8007E6C8, ai);
}

void func_80042198(Ai *ai) {
    ai_dispatch_action(D_8007E778, ai);
}

void func_800421C0(Ai *ai) {
    ai_dispatch_action(D_8007E7D0, ai);
}

void func_800421E8(Ai *ai) {
    ai_dispatch_action(D_8007E988, ai);
}

void func_80042210(Ai *ai) {
    ai_dispatch_action(D_8007E9E0, ai);
}

void ai_face_target(Ai *ai) {
    GameObject *target;
    s16 tx;
    s16 x;
    s16 far;
    s16 near;

    if (ai->target != NULL) {
        target = ai->target->obj;
        if (target == NULL) {
            ai->target = NULL;
            return;
        }
        tx = target->pos_x.s.hi;
        x = D_800AA248.cur_obj->pos_x.s.hi;
        near = x;
        far = tx;
        if (abs(tx - x) >= 0x1C3) {
            if (D_801F9ACA >= tx) {
                far += (D_801D8864.w + 1) >> 16;
            } else {
                near += (D_801D8864.w + 1) >> 16;
            }
        }
        if ((near - 0xE > far && (D_800AA268.p->flags & 0x10)) ||
            (near < far && !(D_800AA268.p->flags & 0x10))) {
            func_8004E99C();
        }
    }
}

void func_80042358(void) {
    func_8003EB5C(D_8008E6AC, D_800AA248.cur_obj);
}

void func_80042384(void) {
    func_8003EB5C(D_8008E6EC, D_800AA248.cur_obj);
}

void func_800423B0(void) {
    func_8003EB5C(D_8008E724, D_800AA248.cur_obj);
}

void func_800423DC(void) {
    func_8003EB5C(D_8008E730, D_800AA248.cur_obj);
}

void func_80042408(void) {
    func_8003EB5C(D_8008E7A0, D_800AA248.cur_obj);
}

void func_80042434(void) {
    func_8003EB5C(D_8008E868, D_800AA248.cur_obj);
}

void func_80042460(void) {
    func_8003EB5C(D_8008E988, D_800AA248.cur_obj);
}

void func_8004248C(void) {
    func_8003EB5C(D_8008E994, D_800AA248.cur_obj);
}

void func_800424B8(void) {
    func_8003EB5C(D_8008E9AC, D_800AA248.cur_obj);
}

void func_800424E4(void) {
    func_8003EB5C(D_8008E9C4, D_800AA248.cur_obj);
}

void func_80042510(void) {
    func_8003EB5C(D_8008E988, D_800AA248.cur_obj);
}

void func_8004253C(void) {
    func_8003EB5C(D_8008EA44, D_800AA248.cur_obj);
}

void func_80042568(void) {
    func_8003EB5C(D_8008EA5C, D_800AA248.cur_obj);
}

void func_80042594(void) {
    func_8003EB5C(D_8008EA74, D_800AA248.cur_obj);
}

void func_800425C0(void) {
    func_8003EB5C(D_8008E988, D_800AA248.cur_obj);
}

void func_800425EC(void) {
    func_8003EB5C(D_8008EBD0, D_800AA248.cur_obj);
}

void func_80042618(void) {
    func_8003EB5C(D_8008EC00, D_800AA248.cur_obj);
}

void func_80042644(void) {
    func_8003EB5C(D_8008EC28, D_800AA248.cur_obj);
}

void func_80042670(Ai *ai) {
    u8 *tbl;

    switch (func_8004A468(ai)) {
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
    func_8003EB5C(tbl, D_800AA248.cur_obj);
}

void func_80042704(Ai *ai) {
    u8 *tbl;

    switch (func_8004A468(ai)) {
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
    func_8003EB5C(tbl, D_800AA248.cur_obj);
}

void func_800427A4(Ai *ai) {
    u8 *tbl;

    switch (func_8004A468(ai)) {
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
    func_8003EB5C(tbl, D_800AA248.cur_obj);
}

void func_80042844(void) {
    func_8003EB5C(D_8008EAD4, D_800AA248.cur_obj);
}

void func_80042870(void) {
    func_8003EB5C(D_8008EAFC, D_800AA248.cur_obj);
}

void func_8004289C(void) {
    func_8003EB5C(D_8008EB24, D_800AA248.cur_obj);
}

void func_800428C8(void) {
    func_8003EB5C(D_8008EB5C, D_800AA248.cur_obj);
}

void func_800428F4(void) {
    func_8003EB5C(D_8008EB84, D_800AA248.cur_obj);
}

void func_80042920(void) {
    func_8003EB5C(D_8008EB9C, D_800AA248.cur_obj);
}

void func_8004294C(void) {
    func_8003EB5C(D_8008E988, D_800AA248.cur_obj);
}

void func_80042978(void) {
    func_8003EB5C(D_80090290, D_800AA248.cur_obj);
}

void func_800429A4(Ai *ai) {
    u8 *tbl;

    switch (func_8004A468(ai)) {
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
    func_8003EB5C(tbl, D_800AA248.cur_obj);
}

void func_80042A38(Ai *ai) {
    u8 *tbl;

    switch (func_8004A468(ai)) {
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
    func_8003EB5C(tbl, D_800AA248.cur_obj);
}

void func_80042ACC(Ai *ai) {
    u8 *tbl;

    switch (func_8004A468(ai)) {
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
    func_8003EB5C(tbl, D_800AA248.cur_obj);
}

void func_80042B60(void) {
    func_8003EB5C(D_80090928, D_800AA248.cur_obj);
}

void func_80042B8C(void) {
    func_8003EB5C(D_80090960, D_800AA248.cur_obj);
}

void func_80042BB8(void) {
    func_8003EB5C(D_80090998, D_800AA248.cur_obj);
}

void func_80042BE4(void) {
    func_8003EB5C(D_80090D4C, D_800AA248.cur_obj);
}

void func_80042C10(void) {
    func_8003EB5C(D_80090D94, D_800AA248.cur_obj);
}

void func_80042C3C(void) {
    func_8003EB5C(D_80090DCC, D_800AA248.cur_obj);
}

void func_80042C68(void) {
    func_8003EB5C(D_80090E60, D_800AA248.cur_obj);
}

void func_80042C94(void) {
    func_8003EB5C(D_80090E98, D_800AA248.cur_obj);
}

void func_80042CC0(void) {
    func_8003EB5C(D_80090EE8, D_800AA248.cur_obj);
}

void func_80042CEC(void) {
    func_8003EB5C(D_80090DDC, D_800AA248.cur_obj);
}

void func_80042D18(void) {
    func_8003EB5C(D_80090DE8, D_800AA248.cur_obj);
}

void func_80042D44(void) {
    func_8003EB5C(D_80090DE8, D_800AA248.cur_obj);
}

void func_80042D70(void) {
    func_8003EB5C(D_80090AF4, D_800AA248.cur_obj);
}

void func_80042D9C(void) {
    func_8003EB5C(D_8008E988, D_800AA248.cur_obj);
}

void func_80042DC8(void) {
    func_8003EB5C(D_8008C724, D_800AA248.cur_obj);
}

void func_80042DF4(void) {
    func_8003EB5C(D_80090BD4, D_800AA248.cur_obj);
}

void func_80042E20(Ai *ai) {
    u8 *tbl;

    switch (func_8004A468(ai)) {
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
    func_8003EB5C(tbl, D_800AA248.cur_obj);
}

void func_80042EC0(Ai *ai) {
    u8 *tbl;

    switch (func_8004A468(ai)) {
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
    func_8003EB5C(tbl, D_800AA248.cur_obj);
}

void func_80042F60(Ai *ai) {
    u8 *tbl;

    switch (func_8004A468(ai)) {
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
    func_8003EB5C(tbl, D_800AA248.cur_obj);
}

void func_80043000(void) {
    func_8003EB5C(D_80097020, D_800AA248.cur_obj);
}

void func_8004302C(void) {
    func_8003EB5C(D_80097050, D_800AA248.cur_obj);
}

void func_80043058(void) {
    func_8003EB5C(D_80097078, D_800AA248.cur_obj);
}

void func_80043084(Ai *ai) {
    u8 *tbl;

    switch (func_8004A468(ai)) {
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
    func_8003EB5C(tbl, D_800AA248.cur_obj);
}
