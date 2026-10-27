/* The controllers' vibration: requests by monster (its player's pad port), the presets, and the per-frame pulse.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "game_800633EC.h"

s32 func_80025DF8(s32 player);
void func_800633EC(Monster *monster, s32 level, s32 time);
void func_8006366C(u8 ports, u8 level, u8 time, u8 ramp_down);
void func_800636D8(s32 port);
void func_80063710(s32 port);
void func_800638B0(RumbleRequest *request);
void func_80063A2C(RumbleRequest *request);

extern u8 D_801C51C8[][2];      /* the PadSetAct buffers, one per port: the motor byte first */
extern Rumble D_801FB4C4[3];
extern RumblePreset D_80085308[];
extern RumbleCue D_80085328[19];

void func_800633EC(Monster *monster, s32 level, s32 time) {
    u32 masks[3] = { 1, 2, 4 };
    s32 port;

    if (monster != NULL && level != 0 && time != 0 && (D_801D36FC == 0x150 || D_801D36FC == 0x240) &&
        D_801FA968 != 1 && monster->id != 0) {
        port = D_801FA8A0[monster->id - 1] - 1;
        if (port >= 0) {
            func_8006366C(masks[port], level, time, 0);
        }
    }
}

void func_800634B0(Monster *monster, s32 time) {
    func_800633EC(monster, 0x40, time);
}

void func_800634D4(Monster *monster, u32 preset) {
    s32 level = D_80085308[preset].level;
    s32 time = D_80085308[preset].time;

    if (monster->unk_142 != 0 && preset < 4) {
        level *= 2;
        if (level > 0x40) {
            level = 0x40;
        }
        time *= 2;
    }
    func_800633EC(monster, level, time);
}

void func_8006353C(s32 preset) {
    s32 level = D_80085308[preset].level;
    s32 time = D_80085308[preset].time;

    func_800633EC(&D_801E0B78[func_80025DF8(1)], level, time);
    func_800633EC(&D_801E0B78[func_80025DF8(2)], level, time);
    func_800633EC(&D_801E0B78[func_80025DF8(3)], level, time);
}

void func_800635F4(Monster *monster, s32 pc) {
    u32 i;
    s32 slot;

    if (monster->id != 0) {
        slot = monster->id - 1;
        for (i = 0; i < 19; i++) {
            if (D_80085328[i].pcs[slot] == pc) {
                func_800633EC(monster, D_80085328[i].preset.level, D_80085328[i].preset.time);
                return;
            }
        }
    }
}

void func_8006366C(u8 ports, u8 level, u8 time, u8 ramp_down) {
    RumbleRequest request;

    request.ports = ports;
    request.ramp_up = 0;
    request.ramp_down = ramp_down;
    request.time = time;
    request.level = level;
    func_800638B0(&request);
}

void func_800636B0(void) {
    RumbleRequest request;

    request.ports = 7;
    func_80063A2C(&request);
}

void func_800636D8(s32 port) {
    D_801FB4C4[port].motor_on = 1;
    D_801C51C8[port][0] = 1;
}

void func_80063710(s32 port) {
    D_801FB4C4[port].motor_on = 0;
    D_801C51C8[port][0] = 0;
}

void func_80063744(void) {
    Rumble *r;
    s32 i;

    if (D_8007A694 != 0) {
        for (i = 0; i < 3; i++) {
            r = &D_801FB4C4[i];
            if (r->active != 0) {
                if (--r->time == 0 || (r->level == 0 && r->ramp_up == 0)) {
                    func_80063710(i);
                    r->active = 0;
                } else {
                    r->duty += r->level;
                    if (r->duty >= 0x40) {
                        if (r->motor_on == 0) {
                            func_800636D8(i);
                        }
                        r->duty -= 0x40;
                    } else if (r->motor_on != 0) {
                        func_80063710(i);
                    }
                    if (r->ramp_up != 0) {
                        r->level += r->step;
                        if (r->level >= r->target) {
                            r->level = r->target;
                            r->ramp_up = 0;
                        }
                    } else if (r->ramp_down != 0) {
                        if (r->step >= r->level) {
                            func_80063710(i);
                            r->active = 0;
                        } else {
                            r->level -= r->step;
                        }
                    }
                }
            }
        }
    }
}

void func_800638B0(RumbleRequest *request) {
    Rumble *r;
    s32 i;

    for (i = 0; i < 3; i++) {
        r = &D_801FB4C4[i];
        if (!(request->ports & (1 << i))) {
            continue;
        }
        if (r->active != 0 && request->time + 4 < r->time && request->level - 8 < r->target) {
            continue;
        }
        r->active = 1;
        func_80063710(i);
        r->target = request->level;
        r->time = request->time;
        r->ramp_up = request->ramp_up;
        r->ramp_down = request->ramp_down;
        r->duty = 0;
        if (request->ramp_up != 0 || request->ramp_down != 0) {
            if (request->ramp_down != 0 && request->ramp_up != 0) {
                r->step = request->level / (request->time >> 1);
            } else {
                r->step = request->level / request->time;
            }
            if (request->ramp_up != 0) {
                r->level = 0;
                continue;
            }
        } else {
            r->step = 0;
        }
        r->level = request->level;
    }
}

void func_80063A2C(RumbleRequest *request) {
    Rumble *r;
    s32 i;

    for (i = 0, r = D_801FB4C4; i < 3; i++, r++) {
        r->active = 0;
        func_80063710(i);
    }
}
