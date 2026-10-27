/* OVERLAYS/OVERATTR.BIN: the pad edges and the attract screens (config/overattr.yaml). */
#include "common.h"
#include "overattr.h"
#include "psyq/libgpu.h"

s32 func_80099118(void) {
    return (D_800A9220 ^ D_800A9250) & D_800A9220;
}

GameObject *func_80099138(OverattrPlacement *p) {
    ObjectDef *def;
    GameObject *obj;

    D_800AA248.new_def = def = func_8001D110();
    def->id = p->id;
    def->pos_x.w = p->x << 16;
    def->pos_y.w = p->y << 16;
    def->flags = p->unk_0C;
    def->unk_06 |= 0x20;
    obj = func_8001DCB4();
    obj->flags |= p->flags;
    return obj;
}

void func_800991BC(void) {
    u16 n;
    GameObject **p;

    n = 0x13;
    p = D_801E28F4;
    do {
        *p++ = NULL;
    } while (--n != 0);
    D_801FA88C = 0;
}

void func_800991EC(void) {
    s32 i;
    s32 done;
    Monster *m;
    u8 *name;
    Monster *winner;

    done = 1;
    i = 0;
    do {
        m = &D_801E0B78[func_80025DF8(i + 1)];
        if (m->id != 0) {
            if ((u32) m->bars[0]->unk_64.count < m->unk_020) {
                m->bars[0]->unk_64.count++;
                done = 0;
                if ((u32) m->bars[0]->script.height < 0x46) {
                    m->bars[0]->script.height = m->bars[0]->unk_64.count * 2 + 0xB;
                    m->bars[0]->pos_y.s.hi = 0xCC - m->bars[0]->script.height;
                }
            }
            if ((u32) m->bars[1]->unk_64.count < m->unk_024) {
                m->bars[1]->unk_64.count++;
                done = 0;
                if ((u32) m->bars[1]->script.height < 0x46) {
                    m->bars[1]->script.height = m->bars[1]->unk_64.count * 2 + 0xB;
                    m->bars[1]->pos_y.s.hi = 0xCC - m->bars[1]->script.height;
                }
            }
            if ((u32) m->bars[2]->unk_64.count < m->unk_026) {
                m->bars[2]->unk_64.count++;
                done = 0;
                if ((u32) m->bars[2]->script.height < 0x46) {
                    m->bars[2]->script.height = m->bars[2]->unk_64.count * 2 + 0xB;
                    m->bars[2]->pos_y.s.hi = 0xCC - m->bars[2]->script.height;
                }
            }
        }
        i++;
    } while (i < 3);
    if (--D_801E29BC == 0) {
        D_801D3780++;
        func_8001E450(0x400);
    }
    if (done == 1 && D_800A9230 == done) {
        D_800A9230 = 0;
        if (D_801D8740 >= 2) {
            winner = D_800A9258;
            if (winner->id == 7 && D_801F9ABC != 0) {
                if (D_801F9ABC == 3) {
                    name = "??????";
                } else {
                    name = "NOOB MYUKUS";
                }
            } else {
                name = D_8007F8E0[winner->id - 1];
            }
            func_8001F61C(name, 0xC8, 0x64, 1, D_801F9AAC, D_8007ABCC, 0, 0x400);
            func_8001F61C("WINS", 0xC8, 0x8C, 1, D_801F9AAC, D_8007ABCC, 0, 0x400);
        }
        i = 0;
        do {
            i++;
            m = &D_801E0B78[func_80025DF8(i)];
            if (m->id != 0) {
                m->unk_020 = 0;
                m->unk_024 = 0;
                m->unk_026 = 0;
            }
        } while (i < 3);
    }
}

void func_8009951C(void) {
    s32 i;
    s32 x;
    Monster *m;

    for (i = 0; i < 3; i++) {
        m = &D_801E0B78[func_80025DF8(i + 1)];
        if (m->id != 0) {
            m->bars[0] = func_8001EB9C(0, 0, 0x10, 1, 0xFF00);
            x = i * 0x78;
            m->bars[0]->pos_x.s.hi = x + 0x2D;
            m->bars[0]->pos_y.s.hi = 0xCC;
            m->bars[0]->priority = 0x19;
            m->bars[0]->flags |= 0x400;
            m->bars[0]->unk_64.count = 0;
            m->bars[1] = func_8001EB9C(0, 0, 0x10, 1, 0xFFFF);
            m->bars[1]->pos_x.s.hi = x + 0x48;
            m->bars[1]->pos_y.s.hi = 0xCC;
            m->bars[1]->priority = 0x19;
            m->bars[1]->flags |= 0x400;
            m->bars[1]->unk_64.count = 0;
            m->bars[2] = func_8001EB9C(0, 0, 0x10, 1, 0xFF00FF);
            m->bars[2]->pos_x.s.hi = x + 0x65;
            m->bars[2]->pos_y.s.hi = 0xCC;
            m->bars[2]->priority = 0x19;
            m->bars[2]->flags |= 0x400;
            m->bars[2]->unk_64.count = 0;
        }
    }
}

void func_800996CC(void) {
    s16 scores[3];
    s16 best;
    u16 c;
    s16 a = 1;             /* the weights of the three tallies, by city */
    u16 b;
    s32 i;
    s32 j;
    Monster *m;
    OverattrPlacement *p;
    GameObject *obj;
    s32 id;

    D_801F9AC8.w = 0;
    D_801F9ACC.w = 0;
    func_8001A420();
    func_80017B24();
    func_8001AC18(0xA, 0x17);
    func_8001F7F8(0x8001);
    D_800A9230 = 1;
    func_8009F968(D_800A73C4, 4, 0x606060);
    best = 0;
    b = 1;
    c = 1;
    switch (D_801FA960 % 3) {
    case 0:
        a = 1;
        b = 4;
        break;
    case 1:
        a = 2;
        b = 1;
        break;
    case 2:
        a = 1;
        b = 1;
        c = 3;
        break;
    }
    for (i = 0; i < 3; i++) {
        scores[i] = 0;
        m = &D_801E0B78[func_80025DF8(i + 1)];
        id = m->id;
        if (id != 0) {
            p = D_800A353C;
            for (j = 0; j < 2; j++) {
                func_80099138(p++)->pos_x.s.hi = i * 0x78 + 0x1E;
            }
            func_80099138(&D_800A355C)->pos_x.s.hi = i * 0x78 + 0x23;
            scores[i] = m->unk_020 * a + b * m->unk_026 + c * m->unk_024;
            if (best < scores[i]) {
                best = scores[i];
                D_800A9258 = m;
            }
        }
    }
    for (i = 0; i < 3; i++) {
        m = &D_801E0B78[func_80025DF8(i + 1)];
        id = m->id;
        if (id != 0) {
            if (D_800A9258 == m) {
                p = &D_800A344C[id];
            } else {
                p = &D_800A34BC[id];
            }
            obj = func_80099138(p);
            obj->pos_x.s.hi = i * 0x78 + 0x4B;
            if (D_801F9ABC == 3 && id == 7) {
                obj->unk_74 = 0xF;
            } else if (D_801F9ABC == 4 && id == 7) {
                obj->unk_74 = 0x10;
            }
        }
    }
    func_8009951C();
    D_801E29BC = 0x1E0;
}

void func_800999F8(u32 which) {
    switch (which) {
    case 0:
        D_801E28F4[9]->pos_y.w = 0x180000;
        D_801E28F4[10]->pos_y.w = 0x1180000;
        D_801E28F4[11]->pos_y.w = 0x1180000;
        break;
    case 1:
        D_801E28F4[9]->pos_y.w = 0x1180000;
        D_801E28F4[10]->pos_y.w = 0x190000;
        D_801E28F4[11]->pos_y.w = 0x1180000;
        break;
    case 2:
        D_801E28F4[9]->pos_y.w = 0x1180000;
        D_801E28F4[10]->pos_y.w = 0x1180000;
        D_801E28F4[11]->pos_y.w = 0x180000;
        break;
    }
}

s32 func_80099A94(s32 *slot) {
    s32 i;

    for (i = *slot - 1; i >= 0; i--) {
        if (D_801FA984[i] == 0) {
            D_800A9228 = *slot;
            *slot = i;
            return 1;
        }
    }
    return 0;
}

s32 func_80099AF0(s32 *slot) {
    s32 i;

    for (i = *slot + 1; i < 3; i++) {
        if (D_801FA984[i] == 0) {
            D_800A9228 = *slot;
            *slot = i;
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_80099118", func_80099B54);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_80099118", func_8009A238);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_80099118", func_8009A708);

s32 func_8009AE40(s32 *step) {
    s32 t;
    GameObject *obj;
    GameObject *cam;
    GameObject **p;
    s32 i;
    s32 f;
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;
    s32 x;
    s32 y;

    t = *step;
    obj = D_801E28F4[0];
    if (D_801CA464 & 1) {
        if ((t & 0xF) < 5) {
            obj->pos_x.s.hi = -100;
            obj->pos_y.s.hi = -100;
        } else {
            obj->pos_x.s.hi = obj->unk_40.w;
            obj->pos_y.s.hi = obj->script.v;
        }
        t++;
        if (t >= 0x65) {
            return 0;
        }
    } else {
        obj = D_800A9270;
        if (D_800A9218 != 0) {
            if (D_800A9240 != 0) {
                if (--D_800A9238 == -1) {
                    if (D_800A9240 > 0) {
                        D_800A9240 = -(D_800A9240 + -1);
                    } else {
                        D_800A9240 = -(D_800A9240 + 1);
                    }
                    D_800A9238 = 2;
                }
                obj->pos_y.s.hi -= D_800A9240;
            }
        } else {
            obj->pos_y.s.hi -= D_800A9240;
            if (obj->pos_y.s.hi < 0x46) {
                D_800A9218 = 1;
                D_800A9240 = 6;
            }
        }
        obj = D_801E28F4[0];
        for (i = 0, p = D_801E2904; i < 3; i++, p++) {
            if (*p != NULL) {
                func_8009EE5C(*p, 0xFF);
            }
        }
        x1 = D_801E28F8[1]->pos_x.s.hi;
        f = ((t / 2) << 16) / 100;
        x0 = obj->pos_x.s.hi;
        y0 = obj->pos_y.s.hi;
        y1 = D_801E28F8[1]->pos_y.s.hi;
        cam = D_801E28F8[0];
        /* the camera's start, end and current points, y << 16 | x */
        cam->unk_50.cam_start = (y0 << 16) | x0;
        x = x0 + (((x1 - x0) * f) >> 16);
        cam->unk_54.cam_end = (y1 << 16) | x1;
        y = y0 + (((y1 - y0) * f) >> 16);
        cam->arg.cam_point = (y << 16) | x;
        x -= 0xC8;
        y -= 0x80;
        if (x < 0) {
            x = 0;
        }
        if (x > 0x190) {
            x = 0x190;
        }
        if (y < 0) {
            y = 0;
        }
        if (y > 0x100) {
            y = 0x100;
        }
        t++;
        D_801F9AC8.w = x << 16;
        D_801F9ACC.w = y << 16;
        if (t >= 0xC9) {
            func_80062E44();
            return 0;
        }
    }
    *step = t;
    return 1;
}

void func_8009B0F0(void) {
    s32 i;
    OverattrPlacement *p;

    func_8001A420();
    func_80017B24();
    func_8001AC18(0xA, 0x28);
    D_801D3D7C = 0;
    SetDispMask(1);
    i = 0;
    p = D_800A4430;
    do {
        func_80099138(p++);
        /* Class B: the inner loop counts the counter's references twice, so it gets s0 before the pointer (every
         * statement order, loop form and fresh variable leaves the two swapped). */
        LOOP_BLOCK(i++;);
    } while (i < 4);
}

u8 *func_8009B160(s16 n) {
    return func_80025C08(D_800A49D4)->text[n];
}

void func_8009B19C(void) {
    if (D_800AA2DC & 0x71C0) {
        D_800AA2EC = 0x44;
    }
    func_8001F39C(&D_800A49E4);
    D_801D8588.text = func_8009B160(0);
    func_8001EDB0();
    D_800AA2EC = 0x47;
    func_8001F39C(&D_800A49FC);
    D_801D8588.text = func_8009B160(1);
    func_8001EDB0();
    func_8001F39C(&D_800A4A14);
    D_801D8588.text = func_8009B160(2);
    func_8001EDB0();
}

void func_8009B23C(void) {
    ObjectDef *def;
    GameObject *obj;
    u8 *p;
    s32 hours;
    s32 minutes;
    u8 pm;

    func_8009B0F0();
    D_800AA2EC = 0x44;
    if (D_800AA2DC == 0) {
        func_8002A354(1);
    } else {
        def = func_8001D110();
        def->pos_x.s.hi = 0xC8;
        def->pos_y.s.hi = 0x3C;
        def->id = 0x0A003E84;
        def->flags = 0x7000;
        def->unk_06 |= 0x20;
        obj = func_8001DCB4();
        D_800AA268.p = obj;
        obj->kind = 0x400;
    }
    D_800AA2EC = 0x47;
    func_8009B19C();
    D_800AA2EC = 0x45;
    p = D_800A4488;
    p = func_8001ECB4(p + 4, D_8007C974 + 1, 0);
    *p++ = ' ';
    *p++ = ' ';
    *p++ = ' ';
    *p++ = ' ';
    *p++ = 'T';
    *p++ = 'I';
    *p++ = 'M';
    *p++ = 'E';
    *p++ = ' ';
    hours = D_801FB198 / 3600;
    minutes = (D_801FB198 % 3600) / 60;
    pm = 0;
    if (hours >= 12) {
        pm = 1;
        hours -= 12;
    }
    if (hours == 0) {
        hours = 12;
    }
    p = func_8001ECB4(p, hours, 0);
    *p = ':';
    p = func_8001ECB4(p + 1, minutes, 2);
    *p++ = ' ';
    if (pm) {
        *p = 'P';
    } else {
        *p = 'A';
    }
    p++;
    *p = 'M';
    p[1] = '\0';
    func_8001F39C(D_800A4470);
    D_801D8588.text = D_800A4488;
    func_8001EDB0();
    D_801D3780 = 1;
    D_801E29BC = 4;
    D_801CA468 = func_8002A300();
}
