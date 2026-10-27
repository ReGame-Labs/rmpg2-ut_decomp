/* OVERLAYS/OVERATTR.BIN: the tour screens between cities: the results, the choice of a monster, the tour map and
 * the day and time before a city (config/overattr.yaml). */
#include "common.h"
#include "overattr.h"
#include "psyq/libgpu.h"

s32 tour_get_pressed(void) {
    return (D_800A9220 ^ D_800A9250) & D_800A9220;
}

GameObject *tour_place_object(OverattrPlacement *p) {
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

void tour_clear_objects(void) {
    u16 n;
    GameObject **p;

    n = 0x13;
    p = D_801E28F4;
    do {
        *p++ = NULL;
    } while (--n != 0);
    D_801FA88C = 0;
}

void tour_update_results(void) {
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
        main_free_kind(0x400);
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

void tour_create_bars(void) {
    s32 i;
    s32 x;
    Monster *m;

    for (i = 0; i < 3; i++) {
        m = &D_801E0B78[func_80025DF8(i + 1)];
        if (m->id != 0) {
            m->bars[0] = main_create_box(0, 0, 0x10, 1, 0xFF00);
            x = i * 0x78;
            m->bars[0]->pos_x.s.hi = x + 0x2D;
            m->bars[0]->pos_y.s.hi = 0xCC;
            m->bars[0]->priority = 0x19;
            m->bars[0]->flags |= 0x400;
            m->bars[0]->unk_64.count = 0;
            m->bars[1] = main_create_box(0, 0, 0x10, 1, 0xFFFF);
            m->bars[1]->pos_x.s.hi = x + 0x48;
            m->bars[1]->pos_y.s.hi = 0xCC;
            m->bars[1]->priority = 0x19;
            m->bars[1]->flags |= 0x400;
            m->bars[1]->unk_64.count = 0;
            m->bars[2] = main_create_box(0, 0, 0x10, 1, 0xFF00FF);
            m->bars[2]->pos_x.s.hi = x + 0x65;
            m->bars[2]->pos_y.s.hi = 0xCC;
            m->bars[2]->priority = 0x19;
            m->bars[2]->flags |= 0x400;
            m->bars[2]->unk_64.count = 0;
        }
    }
}

void tour_init_results(void) {
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
    menu_place_objects(D_800A73C4, 4, 0x606060);
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
                tour_place_object(p++)->pos_x.s.hi = i * 0x78 + 0x1E;
            }
            tour_place_object(&D_800A355C)->pos_x.s.hi = i * 0x78 + 0x23;
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
            obj = tour_place_object(p);
            obj->pos_x.s.hi = i * 0x78 + 0x4B;
            if (D_801F9ABC == 3 && id == 7) {
                obj->unk_74 = 0xF;
            } else if (D_801F9ABC == 4 && id == 7) {
                obj->unk_74 = 0x10;
            }
        }
    }
    tour_create_bars();
    D_801E29BC = 0x1E0;
}

void tour_show_slot(u32 which) {
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

s32 tour_move_slot_left(s32 *slot) {
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

s32 tour_move_slot_right(s32 *slot) {
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

s32 tour_update_selection(void) {
    GameObject *obj;
    s16 i;
    s32 slot;

    if (D_800A9248 < 0) {
        return ++D_800A9248 != 0;
    }
    if (++D_800A9248 > 0x4B0) {
        D_800A9248 = 0x32;
        /* `&` rather than `&&`: the original evaluates the last two tests together (sltiu, sltiu, and) */
        if (D_801FA984[0] == 0 && D_801FA984[1] == 0 & D_801FA984[2] == 0) {
            D_800AA2EC = 0x45;
            func_8001ED54(&D_800897FC);
            D_800A6F39 = 3;
        }
    }
    if (D_800A6F39 != 0) {
        /* back to the attract mode */
        if (--D_800A6F39 != 0) {
            return 1;
        }
        for (i = 0; i < 7; i++) {
            D_801FA8A0[i] = 0;
        }
        for (i = 0; i < 3; i++) {
            D_800A8FD4[i].unk_04 = i;
            D_800A8FD4[i].unk_06 = 0;
            D_800A8FD4[i].unk_08 = 0xB;
        }
        func_8001D17C();
        func_8001E758();
        func_8002497C();
        D_8007A7D4 |= 1;
        func_8001D084();
        D_801CA464 = 0;
        D_801E0D64 = 0;
        D_801D36FC = 0x130;
        D_801CA45C = 4;
        D_801D3780 = 2;
        for (i = 0; i < 0x28; i++) {
            D_801E28F4[i] = NULL;
        }
        func_80017B24();
        func_8001A420();
        func_8001A474();
        func_8001AC18(0xA, 0x1C);
        func_8001AA4C(0xB, 0x1D);
        func_8001F760();
        return 1;
    }
    obj = D_801E28F4[0];
    D_800A6F39 = 0;
    D_800A9250 = D_800A9220;
    D_800A9220 = D_801E0D7C & 0x3FFFFFFF;
    if (D_801F9944 != 0) {
        D_801F9944--;
    }
    if ((D_800A9220 & 0x04010040) && D_801F9944 == 0 && D_801FA984[0] == 0 &&
        D_801FA984[1] == 0 & D_801FA984[2] == 0) {
        D_800AA2EC = 0x45;
        func_8001ED54(&D_800897FC);
        func_8001F724(3);
        D_800A6F39 = 2;
    }
    func_80019268();
    if ((D_800A9220 & 0x401004) && D_801F9944 == 0) {
        if (tour_move_slot_left((s32 *)&obj->arg) != 0) {
            func_8001F724(0x4E);
            obj->unk_60++;
            obj->anim = D_800A43A4[D_800A3450[(s32)obj->arg.p]];
            obj->frames_left = 0;
            obj->unk_74 = D_800A43C0[D_800A3450[(s32)obj->arg.p]];
            tour_show_slot((s32)obj->arg.p);
            D_800A9218 = 0;
            D_800A9240 = 0xA;
            D_800A9238 = 2;
            D_800A9248 = 0x32;
        }
        D_801F9944 = 0xB;
    } else if ((D_800A9220 & 0x802008) && D_801F9944 == 0) {
        if (tour_move_slot_right((s32 *)&obj->arg) != 0) {
            func_8001F724(0x4E);
            obj->unk_60++;
            obj->anim = D_800A43A4[D_800A3450[(s32)obj->arg.p]];
            obj->frames_left = 0;
            obj->unk_74 = D_800A43C0[D_800A3450[(s32)obj->arg.p]];
            tour_show_slot((s32)obj->arg.p);
            D_800A9218 = 0;
            D_800A9240 = 0xA;
            D_800A9238 = 2;
            D_800A9248 = 0x32;
        }
        D_801F9944 = 0xB;
    } else if ((D_800A9220 & 0x01004010) && D_800A9248 > 0x32 && D_801F9944 == 0) {
        func_8001F724(3);
        D_801E289C = D_800A3450[(s32)obj->arg.p];
        switch ((u32)obj->arg.p) {
        case 0:
            D_801FA960 = 0x32;
            break;
        case 1:
            D_801FA960 = 0;
            break;
        case 2:
            D_801FA960 = 0x19;
            break;
        }
        D_800A9248 = -5;
        D_801FB198 = D_800A356C[D_801FA960];
        return 1;
    }
    if (obj->unk_60 == 0) {
        obj->pos_x.s.hi = D_800A40EC[(s32)obj->arg.p];
        obj->pos_y.s.hi = D_800A40F4[(s32)obj->arg.p];
    } else {
        obj->pos_x.s.hi = 0x1F4;
        obj->unk_60 = 0;
    }
    menu_animate(obj, 0xFF);
    slot = (s32)obj->arg.p;
    obj = D_800A9270[slot];
    D_800A9208 = slot;
    if (slot != D_800A9228) {
        D_800A9210 = 1;
    }
    if (D_800A9218 != 0) {
        if (D_800A9240 == 0) {
            return 1;
        }
        if (--D_800A9238 == -1) {
            if (D_800A9240 > 0) {
                D_800A9240 = -(D_800A9240 + -1);
            } else {
                D_800A9240 = -(D_800A9240 + 1);
            }
            D_800A9238 = 2;
        }
        obj->pos_y.s.hi -= D_800A9240;
    } else {
        obj->pos_y.s.hi -= D_800A9240;
        if (obj->pos_y.s.hi < 0xC8) {
            D_800A9218 = 1;
            D_800A9240 = 6;
        }
    }
    if (D_800A9210 == 1) {
        obj = D_800A9270[D_800A9228];
        obj->pos_x.s.hi += 0x1E;
        if (obj->pos_x.s.hi > 0x1F4) {
            obj->pos_x.s.hi = 0xC8;
            D_800A9210 = 0;
            obj->pos_y.s.hi = 0x120;
            D_800A9228 = D_800A9208;
        }
    }
    return 1;
}

void tour_init_selection(void) {
    s32 i;
    s32 j;
    s32 which;
    OverattrPlacement *p;
    ObjectDef *def;
    GameObject *obj;

    func_80017B24();
    if (D_801FA984[0] != 0 || D_801FA984[1] != 0 || D_801FA984[2] != 0) {
        func_800180E4();
    } else {
        menu_create_buttons();
    }
    func_8001A420();
    func_8001AA4C(0xB, 0x1E);
    func_8001AA4C(6, 0x27);
    D_801D3D7C = 0;
    SetDispMask(1);
    i = 0;
    p = D_800A3954;
    do {
        obj = tour_place_object(p++);
        obj->unk_6C &= ~0x20;
        i++;
    } while (i < 6);
    D_800A3450[0] = 4;
    D_800A3450[1] = 3;
    D_800A3450[2] = 5;
    D_800A9248 = 0;
    for (j = 0; j < 3; j++) {
        if (D_801FA8A0[D_800A3450[j]] != 0) {
            for (i = 0; i < 3; i++) {
                if (D_801FA8A0[i] == 0) {
                    D_800A3450[j] = i;
                    D_801FA8A0[i] = 0x63;
                    break;
                }
            }
        }
    }
    for (j = 0; j < 3; j++) {
        if (D_801FA8A0[j] == 0x63) {
            D_801FA8A0[j] = 0;
        }
    }
    if (D_801FA984[1] == 0) {
        which = 1;
    } else {
        which = (D_801FA984[0] != 0) * 2;
    }
    D_800AA248.new_def = def = func_8001D110();
    def->id = D_800A436C[D_800A3450[which]];
    def->pos_x.w = D_800A40EC[which] << 16;
    def->pos_y.w = D_800A40F4[which] << 16;
    def->flags = 0x14;
    def->unk_06 |= 0x20;
    obj = func_8001DCB4();
    D_801E28F4[0] = obj;
    obj->anim = D_800A43A4[D_800A3450[which]];
    obj->frames_left = 0;
    D_800A9228 = which;
    D_800A9208 = which;
    obj->unk_74 = D_800A43C0[D_800A3450[which]];
    obj->vel_x.w = 0;
    obj->vel_y.w = 0;
    obj->unk_60 = 0;
    obj->arg.p = (void *)which;
    D_800AA248.new_def = def = func_8001D110();
    def->id = D_800A4388[D_800A3450[0]];
    def->pos_x.w = 0xC80000;
    def->pos_y.w = 0x1200000;
    def->flags = 0x14;
    def->unk_06 |= 0x20;
    obj = func_8001DCB4();
    D_801E28F4[6] = obj;
    D_800A9270[0] = obj;
    D_800AA248.new_def = def = func_8001D110();
    def->id = D_800A4388[D_800A3450[1]];
    def->pos_x.w = 0xC80000;
    def->pos_y.w = 0x1200000;
    def->flags = 0x14;
    def->unk_06 |= 0x20;
    obj = func_8001DCB4();
    D_801E28F4[7] = obj;
    D_800A9270[1] = obj;
    D_800AA248.new_def = def = func_8001D110();
    def->id = D_800A4388[D_800A3450[2]];
    def->pos_x.w = 0xC80000;
    def->pos_y.w = 0x1200000;
    def->flags = 0x14;
    def->unk_06 |= 0x20;
    obj = func_8001DCB4();
    D_801E28F4[8] = obj;
    D_800A9270[2] = obj;
    D_800AA248.new_def = def = func_8001D110();
    def->id = 0x0B002FB0;
    def->pos_x.w = 0x1130000;
    def->pos_y.w = 0x1180000;
    def->flags = 0xC;
    def->unk_06 |= 0x20;
    D_801E28F4[9] = func_8001DCB4();
    D_800AA248.new_def = def = func_8001D110();
    def->id = 0x0B002FB8;
    def->pos_x.w = 0x1080000;
    def->pos_y.w = 0x190000;
    def->flags = 0xC;
    def->unk_06 |= 0x20;
    D_801E28F4[10] = func_8001DCB4();
    D_800AA248.new_def = def = func_8001D110();
    def->id = 0x0B002FB6;
    def->pos_x.w = 0x1080000;
    def->pos_y.w = 0x1180000;
    def->flags = 0xC;
    def->unk_06 |= 0x20;
    D_801E28F4[11] = func_8001DCB4();
    tour_show_slot(which);
    D_800A9218 = 0;
    D_800A9240 = 0xA;
    D_800A9238 = 2;
    D_800A9248 = 0;
    func_8001F724(0x4E);
}

void tour_init_map(void) {
    OverattrPlacement *p;
    s32 music;
    s32 i;
    s32 prev;
    s16 region;
    s16 x;
    s16 y;
    s16 cx;
    s16 cy;
    GameObject *obj;
    ObjectDef *def;
    s32 id;
    Monster *m;
    s32 n;

    p = D_800A3CB4;
    music = 0x20;
    if (D_801FA960 >= 25) {
        if (D_801FA960 < 50) {
            p = D_800A3DB4;
            music = 0x1F;
        } else if (D_801FA960 < 75) {
            p = D_800A3EB4;
            music = 0x21;
        } else if (D_801FA960 < 100) {
            p = D_800A3FB4;
            music = 0x22;
        } else if (D_801FA960 < 0x71) {
            p = D_800A3BB4;
            music = 0x23;
        } else if (D_801FA960 < 0x72) {
            if (D_801CA464 & 1) {
                p = D_800A39B4;
                music = 0x24;
            } else {
                p = D_800A3AB4;
                music = 0x25;
            }
        } else if (D_801FA960 < 0x7D) {
            p = D_800A39B4;
            music = 0x24;
        }
    }
    i = 0;
    D_8007C974++;
    D_801FB198 = D_800A356C[D_801FA960];
    func_8001A420();
    func_80017B24();
    func_8001AA4C(0xB, 0x1E);
    func_8001AA4C(1, music);
    D_801D3D7C = 0;
    SetDispMask(1);
    do {
        /* Class B: the inner loop counts the map pointer's references twice, so it gets s1 before the dot loop's
         * x pointer (statement orders, loop forms and a fresh pointer per loop leave p and the music swapped). */
        LOOP_BLOCK(obj = tour_place_object(p++););
        obj->unk_6C &= ~0x20;
        i++;
    } while (i < 16);
    if (D_801CA464 & 1) {
        prev = D_801FA960;
    } else {
        prev = D_801FA960 - 1;
    }
    region = D_801FA960 / 25;
    i = region * 25;
    if (D_801FA960 >= 0x71) {
        i = 0x71;
    }
    if (D_801FA960 != 0x71 || prev != 0x70) {
        if (i != D_801FA960) {
            p = &D_800A40B4[1];
            do {
                x = D_800A3760[i * 2];
                y = D_800A3760[i * 2 + 1];
                obj = tour_place_object(p);
                obj->pos_x.s.hi = x;
                obj->pos_y.s.hi = y;
                obj->unk_6C &= ~0x20;
                i++;
            } while (i < D_801FA960);
        } else {
            D_801CA464 |= 1;
        }
    }
    x = D_800A3760[prev * 2];
    y = D_800A3760[prev * 2 + 1];
    if (D_801FA960 == 0x71 && prev == 0x70) {
        x = 0xC1;
        y = 0x199;
    }
    cx = x - 0xC8;
    cy = y - 0x80;
    if (cx < 0) {
        cx = 0;
    }
    if (cx > 0x190) {
        cx = 0x190;
    }
    if (cy < 0) {
        cy = 0;
    }
    if (cy > 0x100) {
        cy = 0x100;
    }
    D_801F9AC8.w = cx << 16;
    D_801F9ACC.w = cy << 16;
    if (D_801CA464 & 1) {
        obj = tour_place_object(&D_800A40B4[0]);
        D_801E28F4[0] = obj;
        obj->unk_40.w = x;
        obj->pos_x.s.hi = x;
        obj->pos_y.s.hi = y;
        obj->script.v = y;
        obj->unk_6C &= ~0x20;
    } else {
        func_8001F6B4();
        func_8001F724(0x6C);
        p = &D_800A40B4[1];
        obj = tour_place_object(p);
        D_801E28F4[0] = obj;
        obj->pos_x.s.hi = x;
        obj->pos_y.s.hi = y;
        obj->unk_6C &= ~0x20;
        obj = main_create_box(0, 0, 0, 0, 0xFF0000);
        D_801E28F4[1] = obj;
        obj->priority = 0xF;
        obj->unk_6C |= 0x1000;
        obj = tour_place_object(p - 1);
        D_801E28F4[2] = obj;
        obj->pos_x.s.hi = D_800A3760[D_801FA960 * 2];
        obj->pos_y.s.hi = D_800A3760[D_801FA960 * 2 + 1];
        if (D_801FA960 == 0x71 && prev == 0x70) {
            obj->pos_x.s.hi = 0x2AA;
            obj->pos_y.s.hi = 0xA2;
        }
        obj->unk_6C &= ~0x20;
        D_800AA284.p = def = func_8001D110();
        def->pos_x.w = 0xC80000;
        def->pos_y.w = 0x1180000;
        def->id = 0x0B003E86;
        def->flags = 0x14;
        def->unk_06 |= 0x20;
        D_800A9270[0] = func_8001DCB4();
        D_800A9218 = 0;
        D_800A9240 = 0xA;
        D_800A9238 = 2;
    }
    if (!(D_801CA464 & 1)) {
        func_8001AA4C(6, 0x26);
        cx = 0xF0;
        cy = 0xE6;
        n = 0;
        D_801E2904[0] = NULL;
        D_801E2904[1] = NULL;
        D_801E2904[2] = NULL;
        i = 0;
        do {
            i++;
            m = &D_801E0B78[func_80025DF8(i)];
            id = m->id;
            if (id != 0) {
                cx -= 0x28;
            }
        } while (i < 3);
        i = 0;
        do {
            m = &D_801E0B78[func_80025DF8(i + 1)];
            id = m->id;
            if (id != 0) {
                D_800AA248.new_def = def = func_8001D110();
                def->id = D_800A43DC[id - 1];
                def->pos_x.w = cx << 16;
                def->pos_y.w = cy << 16;
                def->flags = 0x384;
                def->unk_06 |= 0x20;
                D_801E2904[n] = D_800AA248.cur_obj = func_8001DCB4();
                D_800AA248.cur_obj->anim = D_800A43F8[id - 1];
                D_800AA248.cur_obj->anim += (func_8001EA78() & 0xF) * 8;
                D_800AA248.cur_obj->frames_left = 0;
                if (id == 7) {
                    if (D_801F9ABC == 0) {
                        D_800AA248.cur_obj->unk_74 = D_800A4414[6];
                    } else if (D_801F9ABC == 3) {
                        D_800AA248.cur_obj->unk_74 = 8;
                    } else {
                        D_800AA248.cur_obj->unk_74 = id;
                    }
                } else {
                    D_800AA248.cur_obj->unk_74 = D_800A4414[id - 1];
                }
                cx += 0x50;
                n++;
                D_800AA248.cur_obj->flags |= 0x400;
            }
            i++;
        } while (i < 3);
    }
}

s32 tour_update_map(s32 *step) {
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
        obj = D_800A9270[0];
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
                menu_animate(*p, 0xFF);
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

void tour_create_time_screen(void) {
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
        tour_place_object(p++);
        /* Class B: the inner loop counts the counter's references twice, so it gets s0 before the pointer (every
         * statement order, loop form and fresh variable leaves the two swapped). */
        LOOP_BLOCK(i++;);
    } while (i < 4);
}

u8 *tour_get_goal_line(s16 n) {
    return func_80025C08(D_800A49D4)->text[n];
}

void tour_print_goal(void) {
    if (D_800AA2DC & 0x71C0) {
        D_800AA2EC = 0x44;
    }
    func_8001F39C(&D_800A49E4);
    D_801D8588.text = tour_get_goal_line(0);
    func_8001EDB0();
    D_800AA2EC = 0x47;
    func_8001F39C(&D_800A49FC);
    D_801D8588.text = tour_get_goal_line(1);
    func_8001EDB0();
    func_8001F39C(&D_800A4A14);
    D_801D8588.text = tour_get_goal_line(2);
    func_8001EDB0();
}

void tour_init_time_screen(void) {
    ObjectDef *def;
    GameObject *obj;
    u8 *p;
    s32 hours;
    s32 minutes;
    u8 pm;

    tour_create_time_screen();
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
    tour_print_goal();
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
