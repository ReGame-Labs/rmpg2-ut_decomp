/* OVERLAYS/OVERATTR.BIN: the credits, the menus and the memory-card screens (config/overattr.yaml). */
#include "common.h"
#include "overattr.h"
#include "psyq/libc2.h"

void menu_update_fade(void) {
    GameObject *head;
    GameObject *obj;

    head = &D_801E28C0;
    switch (D_800A9888) {
    case 1:
        obj = head->next;
        if (obj != head) {
            do {
                if ((obj->flags & 0x100) && obj->colour.w != -1) {
                    if (obj->colour.w != 0) {
                        obj->colour.w -= 0x40404;
                    } else {
                        obj->colour.w = 0;
                        D_800A9888 = 0;
                    }
                }
                obj = obj->next;
            } while (obj != head);
        }
        break;
    case 2:
        obj = head->next;
        if (obj != head) {
            do {
                if ((obj->flags & 0x100) && obj->colour.w != -1) {
                    if (obj->colour.w <= 0x80807F) {
                        obj->colour.w += 0x40404;
                    } else {
                        obj->colour.w = 0x808080;
                        D_800A9888 = 0;
                        obj->flags &= ~0x500;
                    }
                }
                obj = obj->next;
            } while (obj != head);
        }
        break;
    }
}

void func_8009B598(void) {
    if ((D_800A9220 & 0x401004) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        if (--D_8007A684 < 0) {
            D_8007A684 = 0x72;
        }
        func_80062E44();
        func_8001F724(D_8007A684);
    } else if ((D_800A9220 & 0x802008) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        if (++D_8007A684 >= 0x73) {
            D_8007A684 = 0;
        }
        func_80062E44();
        func_8001F724(D_8007A684);
    } else if ((D_800A9220 & 0x1004010) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        func_80062E44();
        func_8001F724(D_8007A684);
    }
}

void func_8009B6DC(void) {
    if ((D_800A9220 & 0x401004) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        D_8007A686 -= 5;
        if (D_8007A686 < 0xF) {
            D_8007A686 = 0x5A;
        }
        func_8001F724(0x2F);
    } else if ((D_800A9220 & 0x802008) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        D_8007A686 += 5;
        if (D_8007A686 >= 0x5B) {
            D_8007A686 = 0xF;
        }
        func_8001F724(0x30);
    }
}

void func_8009B7C4(void) {
    if ((D_800A9220 & 0x401004) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        if (--D_8007A688 <= 0) {
            D_8007A688 = 0x64;
        }
        func_8001F724(0x2F);
    } else if ((D_800A9220 & 0x802008) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        if (++D_8007A688 >= 0x65) {
            D_8007A688 = 1;
        }
        func_8001F724(0x30);
    }
}

void func_8009B8A4(void) {
    if ((D_800A9220 & 0x401004) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        if (--D_801FA960 < 0) {
            D_801FA960 = 0x7C;
        }
        func_8001F724(0x2F);
    } else if ((D_800A9220 & 0x802008) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        if (++D_801FA960 >= 0x7D) {
            D_801FA960 = 0;
        }
        func_8001F724(0x30);
    }
}

void func_8009B980(void) {
    if ((D_800A9220 & 0x401004) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        if (--D_8007A692 < 0) {
            D_8007A692 = 0x1C;
        }
        func_8001F724(0x2F);
    } else if ((D_800A9220 & 0x802008) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        if (++D_8007A692 >= 0x1D) {
            D_8007A692 = 0;
        }
        func_8001F724(0x30);
    } else if ((D_800A9220 & 0x1004010) && D_801F9944 == 0) {
        D_800A6F78 = 1;
    }
}

void func_8009BAA4(void) {
    if ((D_800A9220 & 0x401004) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        D_801E2150 -= 3;
        if (D_801E2150 < 0) {
            D_801E2150 = 0;
        }
        func_8001F724(0x1E);
    } else if ((D_800A9220 & 0x802008) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        D_801E2150 += 3;
        if (D_801E2150 >= 0x80) {
            D_801E2150 = 0x7F;
        }
        func_8001F724(0x1E);
    }
    func_80062D88((u8) D_801E2150);
}

void func_8009BB90(void) {
    if ((D_800A9220 & 0x401004) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        D_801E1CB4 -= 3;
        if (D_801E1CB4 < 0) {
            D_801E1CB4 = 0;
        }
        func_8001F724(0x1E);
    } else if ((D_800A9220 & 0x802008) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        D_801E1CB4 += 3;
        if (D_801E1CB4 >= 0x80) {
            D_801E1CB4 = 0x7F;
        }
        func_8001F724(0x1E);
    }
    func_80062DA8((u8) D_801E1CB4);
}

void func_8009BC7C(void) {
    if ((D_800A9220 & 0x401004) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        D_8007A68A ^= 1;
        func_8001F724(0x1E);
    } else if ((D_800A9220 & 0x802008) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        D_8007A68A ^= 1;
        func_8001F724(0x1E);
    }
}

void func_8009BD0C(void) {
    if ((D_800A9220 & 0x401004) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        D_8007A68C ^= 1;
        func_8001F724(0x1E);
    } else if ((D_800A9220 & 0x802008) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        D_8007A68C ^= 1;
        func_8001F724(0x1E);
    }
}

void func_8009BD9C(void) {
    if ((D_800A9220 & 0x401004) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        if (--D_8007A68E < 0) {
            D_8007A68E = 2;
        }
        func_8001F724(0x1E);
    } else if ((D_800A9220 & 0x802008) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        if (++D_8007A68E >= 3) {
            D_8007A68E = 0;
        }
        func_8001F724(0x1E);
    }
    D_8007A688 = D_800A6F3C[D_8007A68E * 2];
    D_8007A686 = D_800A6F3C[D_8007A68E * 2 + 1];
}

void func_8009BEB0(void) {
    if ((D_800A9220 & 0x401004) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        D_8007A694 ^= 1;
        func_8001F724(0x1E);
    } else if ((D_800A9220 & 0x802008) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        D_8007A694 ^= 1;
        func_8001F724(0x1E);
    }
}

void func_8009BF40(u8 *dst, s32 index) {
    u8 *src;
    s32 i;

    src = D_8007C704[index];
    i = 0;
    if (*src != 0) {
        do {
            dst[i++] = *src++;
        } while (*src != 0);
    }
    dst[i] = 0;
}

void func_8009BF94(u8 *dst, s32 index) {
    u8 *src;
    s32 i;

    src = D_800A72D8[index];
    i = 0;
    if (*src != 0) {
        do {
            dst[i++] = *src++;
        } while (*src != 0);
    }
    dst[i] = 0;
}

#ifdef NON_MATCHING
/* 99.24%: registers only. The movie line's text address (3 refs over 136 insns, priority 0.02) comes last in
 * global-alloc's order, after the %hi of D_801F9AAC and of D_800A92D0 (6 refs over ~95, 0.13 and 0.12), and gets s3;
 * the original gives it s1, i.e. allocates it before them, which needs a priority above 0.13 (a life under 24 insns
 * for 3 refs): the original's address was not this one long pseudo. A user variable for it, a TextMessage pointer
 * and the struct forms of the first four strings (&D_800A6300.text[6], ...: cse then reuses them, 95% and less)
 * do not change it */
void menu_draw_cheats(void) {
    func_8009BF40(D_800A631E, D_801FA960);
    func_8001ECB4(D_800A6359, D_8007A684, 0);
    func_8001ECB4(D_800A6380, D_8007A686, 0);
    func_8001ECB4(D_800A63A3, D_8007A688, 0);
    func_8009BF94(&D_800A63A8.text[7], D_8007A692);
    main_free_kind(0x421);
    main_free_kind(0x422);
    main_free_kind(0x423);
    main_free_kind(0x424);
    main_free_kind(0x425);
    D_800AA2EC = D_801F9AAC;
    if (D_800A92D0 == 0) {
        D_800AA2EC = D_801E2A44;
    }
    func_8001ED54(&D_800A6300);
    D_800AA2EC = D_801F9AAC;
    if (D_800A92D0 == 1) {
        D_800AA2EC = D_801E2A44;
    }
    func_8001ED54(&D_800A6338);
    D_800AA2EC = D_801F9AAC;
    if (D_800A92D0 == 2) {
        D_800AA2EC = D_801E2A44;
    }
    func_8001ED54(&D_800A6360);
    D_800AA2EC = D_801F9AAC;
    if (D_800A92D0 == 3) {
        D_800AA2EC = D_801E2A44;
    }
    func_8001ED54(&D_800A6384);
    D_800AA2EC = D_801F9AAC;
    if (D_800A92D0 == 4) {
        D_800AA2EC = D_801E2A44;
    }
    func_8001ED54(&D_800A63A8);
}
#else
INCLUDE_ASM("asm/overattr/nonmatchings/menu", menu_draw_cheats);
#endif

void func_8009C1AC(void) {
    menu_update_load_screen();
}

void menu_update_name_entry(void) {
    MenuRecord *menu = D_800A92C0;
    s32 i;

    if ((D_800A9220 & 0x401004) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        if (--D_800A92D0 < 0) {
            D_800A92D0 = D_800A9840 - 1;
        }
        menu_light_items(menu, D_800A92D0, (s16) D_801E2A44, D_801F9AAC);
        D_801F9944 = 0xB;
        D_801D872C /= 2;
        func_8001F724(0x1E);
    } else if ((D_800A9220 & 0x802008) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        if (++D_800A92D0 >= D_800A9840) {
            D_800A92D0 = 0;
        }
        menu_light_items(D_800A92C0, D_800A92D0, (s16) D_801E2A44, D_801F9AAC);
        D_801F9944 = 0xB;
        D_801D872C /= 2;
        func_8001F724(0x1E);
    } else if ((D_800A9220 & 0x01304C13) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        D_800A92C0[D_800A92D0 + 2].sub.fn();
        D_801F9944 = 0xB;
        D_801D872C /= 2;
        if (D_800A92D0 == 5) {
            return;
        }
    } else if ((D_800A9220 & 0x04010040) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        if (menu->sub.menu != NULL) {
            D_800A92D8 = menu->sub.menu;
            D_800A9800 = 1;
            D_800A9870 = menu->kind;
            func_8001F724(3);
            menu_fade_out();
            D_801F9944 = 0xB;
            D_801D872C /= 2;
            return;
        }
    }
    for (i = 0; i < 5; i++) {
        D_800A6F48[i]->text[0] = D_800A9890[i];
        main_free_kind(i + 0x421);
        func_8001ED54((TextMessage *) D_800A92C0[i + 2].unk_00);
    }
    menu_light_items(D_800A92C0, D_800A92D0, (s16) D_801E2A44, D_801F9AAC);
    for (i = 0; i < 7; i++) {
        if (strcmp(D_800A9890, D_8007A69C[i]) == 0) {
            D_800A6F5C[i]();
            func_8001F724(3);
            D_800A92D8 = menu->sub.menu;
            D_800A9800 = 1;
            D_800A9870 = menu->kind;
            func_8001F724(3);
            menu_fade_out();
        }
    }
    main_cycle_highlight();
}

INCLUDE_RODATA("asm/overattr/nonmatchings/menu", D_80097F58);

void menu_edit_name(void) {

    if ((D_800A9220 & 0x100401) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        func_8001F724(0x1E);
        if (D_800A9890[D_800A92D0] == '9') {
            D_800A9890[D_800A92D0] = 'B';
        } else if (D_800A9890[D_800A92D0] == 'Z') {
            D_800A9890[D_800A92D0] = '0';
        } else {
            D_800A9890[D_800A92D0]++;
        }
        if (strchr("AEIOU", D_800A9890[D_800A92D0]) != NULL) {
            D_800A9890[D_800A92D0]++;
        }
    }
    if ((D_800A9220 & 0x200802) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        func_8001F724(0x1E);
        if (D_800A9890[D_800A92D0] == 'B') {
            D_800A9890[D_800A92D0] = '9';
        } else if (D_800A9890[D_800A92D0] == '0') {
            D_800A9890[D_800A92D0] = 'Z';
        } else {
            D_800A9890[D_800A92D0]--;
        }
        if (strchr("AEIOU", D_800A9890[D_800A92D0]) != NULL) {
            D_800A9890[D_800A92D0]--;
        }
    }
    if ((D_800A9220 & 0x01004010) && D_801F9944 == 0) {
        D_800A9860 = 0x708;
        func_8001F724(0x1E);
        if (D_800A92D0 < 5) {
            D_800A92D0++;
        }
    }
}

void func_8009C7B0(void) {
    D_801F9ADC = 1;
}

void func_8009C7C0(void) {
    D_801F9A4A = 0;
}

void func_8009C7CC(void) {
    D_801F9A4C = 0;
}

void func_8009C7D8(void) {
    D_801F9A4E = 0;
}

void func_8009C7E4(void) {
    D_801F9A50 = 0;
    D_801F9ABC = 0;
}

void func_8009C7F8(void) {
    D_801F9A50 = 0;
    D_801F9ABC = 3;
}

void func_8009C810(void) {
    D_801F9A50 = 0;
    D_801F9ABC = 4;
}

s32 menu_update_credits(void) {
    GameObject *obj;
    GameObject *next;
    GameObject *head;

    if (D_800A92B8 == 0 && D_800A9298 == 0) {
        func_80017B24();
        func_8001A420();
        func_8001A474();
        func_8001AA4C(1, 0x2A);
        func_8001AC18(0xA, 0x1A);
        D_801FA9A4 = 0;
        func_8001EB3C();
        D_801D3D7C = 0;
        SetDispMask(1);
        func_8001F7F8(0xA);
        menu_place_objects(D_800A40FC, 4, 0x606060);
    }
    if (D_800A90F4[D_800A92B8] == -1) {
        if (D_800A9298 == 0) {
            D_800A9298 = 0x384;
        }
    }
    if (D_800A90F4[D_800A92B8] == -1 && D_800A9298 == 0x190) {
        return 0;
    }
    if (D_800A9298 == 0) {
        func_8001F61C(D_800A9010[D_800A92B8], 0xC8, 0x104, 1, D_800A9168[D_800A92B8], D_8007ABCC, 0, 0x400);
        D_800A9298 = D_800A90F4[D_800A92B8];
        D_800A92B8++;
    } else {
        D_800A9298--;
    }
    if (!(D_800A9298 & 1)) {
        head = &D_801E28C0;
        obj = head->next;
        while (obj != head) {
            next = obj->next;
            if (obj->kind == 0x400) {
                obj->pos_y.s.hi--;
                func_8001E94C(obj->pos_x.s.hi, obj->pos_y.s.hi, obj);
                if (obj->pos_y.s.hi < -10) {
                    func_8001E4B0(obj);
                }
            }
            obj = next;
        }
    }
    return 1;
}

#ifdef NON_MATCHING
/* 81.21%: the shape is the original's (size 0x2A4, original 0x2C8); the loops' registers differ: the original
 * spills i, &D_800A6FBC[i] and i * 2, and steps the picture table's index as (k - 4) * 4. */
void menu_draw_controls(void) {
    u16 *cfg[3];
    s32 i;
    s32 k;
    s32 n;
    s32 j;
    s32 obj;
    s32 kind;
    s32 end;
    s16 *base;

    for (i = 0; i < 3; i++) {
        if (D_800A92A8[i] != D_801D8800[i]) {
            D_800A92A8[i] = D_801D8800[i];
            obj = i * 4;
            base = &D_800A6FBC[i];
            cfg[i] = D_8007A7C0[D_801D8800[i]];
            kind = *base;
            end = kind + 4;
            n = 0;
            for (; kind < end; kind++) {
                main_free_kind(kind);
            }
            for (k = 4, j = 0; k < 8; k++, j++) {
                switch (cfg[i][k]) {
                case 0x10:
                    D_800A6718.x = D_800A6FAC[i];
                    D_800A6718.y = D_800A6FB4[n];
                    D_800A6718.kind = *base + n;
                    func_8001ED54(&D_800A6718);
                    break;
                case 0x20:
                    D_800A6738.x = D_800A6FAC[i];
                    D_800A6738.y = D_800A6FB4[n];
                    D_800A6738.kind = *base + n;
                    func_8001ED54(&D_800A6738);
                    break;
                case 0x40:
                    D_800A6758.x = D_800A6FAC[i];
                    D_800A6758.y = D_800A6FB4[n];
                    D_800A6758.kind = *base + n;
                    func_8001ED54(&D_800A6758);
                    break;
                case 0x80:
                    D_800A6778.x = D_800A6FAC[i];
                    D_800A6778.y = D_800A6FB4[n];
                    D_800A6778.kind = *base + n;
                    func_8001ED54(&D_800A6778);
                    break;
                default:
                    continue;
                }
                main_set_frame(D_800A6F7C[j], D_801E28F4[obj]->flags, D_801E28F4[obj]);
                D_801E28F4[obj]->pos_x.s.hi = D_800A6F8C[i];
                D_801E28F4[obj]->pos_y.s.hi = D_800A6F94[obj];
                n++;
                obj++;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/overattr/nonmatchings/menu", menu_draw_controls);
#endif

void func_8009CD30(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (D_800A92B0[i] != 3) {
            if ((D_800A9220 & (4 << (i * 10))) && D_801F9944 == 0) {
                D_800A9860 = 0x708;
                if (D_801D8800[i] == 0) {
                    D_801D8800[i] = 4;
                } else {
                    D_801D8800[i]--;
                }
                func_8001F724(0x1E);
            } else if ((D_800A9220 & (8 << (i * 10))) && D_801F9944 == 0) {
                D_800A9860 = 0x708;
                if (D_801D8800[i] == 4) {
                    D_801D8800[i] = 0;
                } else {
                    D_801D8800[i]++;
                }
                func_8001F724(0x1E);
            }
        }
    }
}

void func_8009CE5C(void) {
    if (D_800A9808[0] != NULL) {
        D_800A9808[0]->unk_40.w = (D_801E2150 * 0x9A) >> 7;
        D_800A9808[1]->unk_40.w = (D_801E1CB4 * 0x9A) >> 7;
    }
}

void menu_draw_options(void) {
    main_free_kind(0x442);
    main_free_kind(0x443);
    main_free_kind(0x402);
    main_free_kind(0x403);
    D_800AA2EC = D_801F9AAC;
    if (D_800A92D0 == 0) {
        D_800AA2EC = D_801E2A44;
    }
    if (D_8007A68A == 1) {
        func_8001ED54(&D_800A6494);
    } else {
        func_8001ED54(&D_800A64C0);
    }
    D_800AA2EC = D_801F9AAC;
    if (D_800A92D0 == 1) {
        D_800AA2EC = D_801E2A44;
    }
    if (D_8007A68C == 1) {
        func_8001ED54(&D_800A64EC);
    } else {
        func_8001ED54(&D_800A6514);
    }
    D_800AA2EC = D_801F9AAC;
    if (D_800A92D0 == 2) {
        D_800AA2EC = D_801E2A44;
    }
    switch (D_8007A68E) {
    case 0:
        func_8001ED54(&D_800A6540);
        break;
    case 1:
        func_8001ED54(&D_800A656C);
        break;
    case 2:
        func_8001ED54(&D_800A6598);
        break;
    }
    D_800AA2EC = D_801F9AAC;
    if (D_800A92D0 == 3) {
        D_800AA2EC = D_801E2A44;
    }
    if (D_8007A694 == 1) {
        func_8001ED54(&D_800A65C4);
    } else {
        func_8001ED54(&D_800A65EC);
    }
}

void func_8009D0B0(void) {
    if ((u16) (D_801FA960 - 1) < 0x18) {
        D_801E289C = 3;
    } else if ((u16) (D_801FA960 - 0x1A) < 0x18) {
        D_801E289C = 5;
    } else if ((u16) (D_801FA960 - 0x33) < 0x18) {
        D_801E289C = 4;
    }
    if (D_801FA960 >= 0x4B) {
        D_801FA984[0] = 1;
        D_801FA984[1] = 1;
        D_801FA984[2] = 1;
    }
}

void func_8009D140(void) {
    if ((D_800A9220 & 0x1004010) && D_801F9944 == 0) {
        D_800A92D8 = D_800A7014;
        D_800A9870 = 0;
        D_801E2148 = 6;
        D_801D3780 = 5;
        func_8001EC74(D_800A92C0[D_800A92D0 + 2].kind, D_801D885C);
        func_8001F724(3);
        menu_fade_others(D_800A92C0, D_800A92D0);
        D_800A9878 = 0;
    }
}

void func_8009D20C(void) {
    if ((D_800A9220 & 0x10) && D_801F9944 == 0) {
        D_801E2148 = 2;
        D_801D3780 = 5;
        func_8001EC74(D_800A92C0[D_800A92D0 + 2].kind, D_801D885C);
        func_8001F724(3);
        menu_fade_others(D_800A92C0, D_800A92D0);
        D_801FA984[0] = 0;
        D_801FA984[1] = 0;
        D_801FA984[2] = 0;
        D_8007C974 = 0;
        D_8007A690 = 1;
        func_8009D0B0();
    } else if ((D_800A9220 & 0x1004000) && D_801F9944 == 0) {
        func_8001F724(0x69);
    }
}

void func_8009D31C(void) {
    if ((D_800A9220 & 0x4010) && D_801F9944 == 0) {
        D_801E2148 = 2;
        D_801D3780 = 5;
        func_8001EC74(D_800A92C0[D_800A92D0 + 2].kind, D_801D885C);
        func_8001F724(3);
        menu_fade_others(D_800A92C0, D_800A92D0);
        D_801FA984[0] = 0;
        D_801FA984[1] = 0;
        D_801FA984[2] = 0;
        D_8007C974 = 0;
        D_8007A690 = 2;
        func_8009D0B0();
    } else if ((D_800A9220 & 0x1000000) && D_801F9944 == 0) {
        func_8001F724(0x69);
    }
}

void func_8009D42C(void) {
    if ((D_800A9220 & 0x1004010) && D_801F9944 == 0) {
        D_801E2148 = 2;
        D_801D3780 = 5;
        func_8001EC74(D_800A92C0[D_800A92D0 + 2].kind, D_801D885C);
        func_8001F724(3);
        menu_fade_others(D_800A92C0, D_800A92D0);
        D_801FA984[0] = 0;
        D_801FA984[1] = 0;
        D_801FA984[2] = 0;
        D_8007C974 = 0;
        D_8007A690 = 3;
        func_8009D0B0();
    }
}

void func_8009D504(void) {
    if ((D_800A9220 & 0x1004010) && D_801F9944 == 0) {
        if (D_801F9ADC != 0) {
            D_800A92D8 = D_800A714C;
        } else {
            D_800A92D8 = D_800A7104;
        }
        D_800A9870 = 0;
        D_801E2148 = 6;
        D_801D3780 = 5;
        func_8001EC74(D_800A92C0[D_800A92D0 + 2].kind, D_801D885C);
        func_8001F724(3);
        menu_fade_others(D_800A92C0, D_800A92D0);
    }
}

void func_8009D5E4(void) {
    if ((D_800A9220 & 0x1004010) && D_801F9944 == 0) {
        D_800A92D8 = D_800A7080;
        D_800A9870 = 0;
        D_801E2148 = 6;
        D_801D3780 = 5;
        func_8001EC74(D_800A92C0[D_800A92D0 + 2].kind, D_801D885C);
        func_8001F724(3);
        menu_fade_others(D_800A92C0, D_800A92D0);
        D_800A9878 = 0;
    }
}

void func_8009D6B0(void) {
    s32 i;

    if ((D_800A9220 & 0x1004010) && D_801F9944 == 0) {
        D_800A92D8 = D_800A70A4;
        D_800A9870 = 0;
        D_801E2148 = 6;
        D_801D3780 = 5;
        func_8001EC74(D_800A92C0[D_800A92D0 + 2].kind, D_801D885C);
        func_8001F724(3);
        menu_fade_others(D_800A92C0, D_800A92D0);
    }
    for (i = 0; i < 5; i++) {
        D_800A6F48[i]->text[0] = 'B';
        D_800A9890[i] = 'B';
    }
    D_800A9890[5] = 0;
}

void menu_start_player_select(void) {
    s32 n;
    s32 i;
    s32 j;
    ObjectDef *def;

    if ((D_800A9220 & 0x01004010) && D_801F9944 == 0) {
        n = 0;
        D_800A92D8 = D_800A7200;
        D_800A9870 = 0;
        D_801E2148 = 6;
        D_801D3780 = 5;
        func_8001EC74(D_800A92C0[D_800A92D0 + 2].kind, D_801D885C);
        func_8001F724(3);
        menu_fade_others(D_800A92C0, D_800A92D0);
        for (i = 0; i < 3; i++) {
            D_800A92A8[i] = -1;
            D_800A92B0[i] = i;
            for (j = 0; j < 4; j++) {
                D_800AA248.new_def = def = func_8001D110();
                def->id = 0x4F002804;
                def->pos_x.w = 0x1F40000;
                def->pos_y.w = 0x1F40000;
                def->flags = 0x14;
                def->unk_06 |= 0x20;
                D_801E28F4[n++] = func_8001DCB4();
            }
        }
    }
}

void func_8009D948(void) {
    ObjectDef *def;

    if ((D_800A9220 & 0x01004010) && D_801F9944 == 0) {
        D_800A92D8 = D_800A7248;
        D_800A9870 = 0;
        D_801E2148 = 6;
        D_801D3780 = 5;
        func_8001EC74(D_800A92C0[D_800A92D0 + 2].kind, D_801D885C);
        func_8001F724(3);
        menu_fade_others(D_800A92C0, D_800A92D0);
        D_800AA248.new_def = def = func_8001D110();
        def->id = 0x4A002FBA;
        def->pos_x.w = 0x1F40000;
        def->pos_y.w = 0x6E0000;
        def->flags = 0x14;
        def->unk_06 |= 0x20;
        D_800A92F8[0] = func_8001DCB4();
        D_800AA248.new_def = def = func_8001D110();
        def->id = 0x4A002FBA;
        def->pos_x.w = 0x1F40000;
        def->pos_y.w = 0xA80000;
        def->flags = 0x14;
        def->unk_06 |= 0x20;
        D_800A92F8[1] = func_8001DCB4();
        D_800A9808[0] = main_create_box(0, 0, 0x4B, 5, 0xFF00);
        D_800A9808[0]->pos_x.s.hi = 0x1F4;
        D_800A9808[0]->pos_y.s.hi = 0x69;
        D_800A9808[0]->priority = 0x32;
        D_800A9808[0]->kind = 0x400;
        D_800A9808[1] = main_create_box(0, 0, 0x32, 5, 0xFF00);
        D_800A9808[1]->pos_x.s.hi = 0x1F4;
        D_800A9808[1]->pos_y.s.hi = 0xA3;
        D_800A9808[1]->priority = 0x32;
        D_800A9808[1]->kind = 0x400;
        func_8009CE5C();
    }
}

void func_8009DB38(void) {
    if ((D_800A9220 & 0x1004010) && D_801F9944 == 0) {
        D_800A92D8 = D_800A71A0;
        D_800A9870 = 0;
        D_801E2148 = 6;
        D_801D3780 = 5;
        func_8001EC74(D_800A92C0[D_800A92D0 + 2].kind, D_801D885C);
        func_8001F724(3);
        menu_fade_others(D_800A92C0, D_800A92D0);
    }
}

void func_8009DBFC(void) {
    if ((D_800A9220 & 0x1004010) && D_801F9944 == 0) {
        D_800A92D8 = D_800A7284;
        D_800A9870 = 0;
        D_801E2148 = 6;
        D_801D3780 = 5;
        func_8001EC74(D_800A92C0[D_800A92D0 + 2].kind, D_801D885C);
        func_8001F724(3);
        menu_fade_others(D_800A92C0, D_800A92D0);
    }
}

void menu_back(void) {
    MenuRecord *menu;

    menu = D_800A92C0;
    if ((D_800A9220 & 0x1004010) && D_801F9944 == 0) {
        D_800A9800 = 1;
        D_800A92D8 = menu[0].sub.menu;
        D_800A9870 = menu[0].kind;
        func_8001F724(3);
        menu_fade_out();
    }
}

void func_8009DD3C(void) {
    if ((D_800A9220 & 0x1004010) && D_801F9944 == 0) {
        D_800A92D8 = D_800A6FCC;
        D_800A9870 = 0;
        D_801E2148 = 0xC;
        D_801D3780 = 5;
        func_8001EC74(D_800A92C0[D_800A92D0 + 2].kind, D_801D885C);
        func_8001F724(3);
        menu_fade_others(D_800A92C0, D_800A92D0);
    }
}

void func_8009DE00(void) {
    MenuRecord *menu;
    s32 i;

    menu = D_800A92C0;
    if ((D_800A9220 & 0x1004010) && D_801F9944 == 0) {
        D_800A9800 = 1;
        D_800A92D8 = menu[0].sub.menu;
        D_800A9870 = menu[0].kind;
        func_8001F724(3);
        menu_fade_out();
    }
    for (i = 0; i < 12; i++) {
        menu_set_colour(0x400, 0x808080);
    }
}

void menu_free_others(void *list, s32 selected) {
    MenuRecord *menu;
    s32 i;

    menu = list;
    for (i = 2; i <= menu->unk_00 + 1; i++) {
        if (selected != i - 2) {
            main_free_kind(menu[i].kind);
        }
    }
    if (menu->sub.menu != NULL) {
        i = menu->kind;
        main_free_kind(menu->sub.menu[i + 2].kind);
    }
}

void menu_free_all(void) {
    s32 i;

    for (i = 0x400; i < 0x4FF; i++) {
        main_free_kind(i);
    }
}

s16 menu_draw(void *list, s32 selected, s32 lit, s32 normal) {
    MenuRecord *menu;
    MenuRecord *item;
    GameObject *head;
    GameObject *obj;
    s32 i;
    s32 kind;

    menu = list;
    for (i = 2; i <= menu->unk_00 + 1; i++) {
        if (selected == i - 2) {
            D_800AA2EC = lit;
        } else {
            D_800AA2EC = normal;
        }
        func_8001ED54((TextMessage *) menu[i].unk_00);
    }
    if (D_800A9800 == 1 && menu != D_800A6FCC) {
        i = menu->kind + 2;
        D_800AA2EC = D_801D885C;
        func_8001ED54((TextMessage *) menu->sub.menu[i].unk_00);
        kind = menu->sub.menu[i].kind;
        menu_set_colour(kind, 0);
        head = &D_801E28C0;
        obj = head->next;
        if (obj != head) {
            do {
                if (obj->kind == kind) {
                    obj->pos_y.w = 0x200000;
                    obj->unk_28.w = (u16) obj->unk_28.w | (obj->pos_y.s.hi << 16);
                }
                obj = obj->next;
            } while (obj != head);
        }
    }
    return menu->unk_00;
}

s32 menu_slide_kind(s32 kind, s32 y) {
    GameObject *head;
    GameObject *obj;
    s32 done;

    head = &D_801E28C0;
    obj = head->next;
    done = 0;
    if (obj != head) {
        do {
            if (obj->kind == kind) {
                obj->pos_y.w -= (obj->pos_y.w - y) >> 4;
                obj->unk_28.w = (u16) obj->unk_28.w | (obj->pos_y.s.hi << 16);
                if (obj->pos_y.s.hi == y >> 16) {
                    done = 1;
                }
            }
            obj = obj->next;
        } while (obj != head);
    }
    return done;
}

void menu_light_items(void *list, s32 selected, s32 lit, s32 normal) {
    MenuRecord *menu;
    s32 i;

    menu = list;
    for (i = 2; i <= menu[0].unk_00 + 1; i++) {
        if (selected == i - 2) {
            func_8001EC74(menu[i].kind, lit);
        } else {
            func_8001EC74(menu[i].kind, normal);
        }
    }
}

void menu_light_choices(void *list, s32 lit, s32 normal) {
    MenuRecord *menu;
    s32 i;

    menu = list;
    for (i = 2; i <= menu[0].unk_00 + 1; i++) {
        if (D_800A92B0[0] == i - 2 || D_800A92B0[1] == i - 2 || D_800A92B0[2] == i - 2) {
            func_8001EC74(menu[i].kind, lit);
        } else {
            func_8001EC74(menu[i].kind, normal);
        }
    }
}

void func_8009E310(s32 lit, s32 normal) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (D_800A92D0 == i) {
            func_8001EC74(0x450 + i, lit);
        } else {
            func_8001EC74(0x450 + i, normal);
        }
    }
    if (D_800A92D0 == D_800A9840) {
        func_8001EC74(0x499, lit);
    } else {
        func_8001EC74(0x499, normal);
    }
}

void menu_set_colour(s32 kind, s32 value) {
    GameObject *head;
    GameObject *obj;

    head = &D_801E28C0;
    obj = head->next;
    if (obj != head) {
        do {
            if (obj->kind == kind) {
                obj->colour.w = value;
                obj->flags |= 0x500;
            }
            obj = obj->next;
        } while (obj != head);
    }
}

void menu_fade_others(void *list, s32 selected) {
    MenuRecord *menu;
    s32 i;

    menu = list;
    for (i = 2; i <= menu[0].unk_00 + 1; i++) {
        if (selected != i - 2) {
            menu_set_colour(menu[i].kind, 0x808080);
        }
    }
    if (menu[0].sub.menu != NULL) {
        i = menu[0].kind;
        menu_set_colour(menu[0].sub.menu[i + 2].kind, 0x808080);
    }
    D_800A9888 = 1;
}

void menu_fade_out(void) {
    GameObject *head;
    GameObject *obj;

    head = &D_801E28C0;
    obj = head->next;
    if (obj != head) {
        do {
            if ((u32) (obj->kind - 0x400) < 0x100) {
                obj->colour.w = 0x808080;
                obj->flags |= 0x500;
            }
            obj = obj->next;
        } while (obj != head);
    }
    D_800A9888 = 1;
    D_801D3780 = 8;
}

void menu_fade_in(MenuRecord *menu) {
    s32 i;

    for (i = 2; i <= menu[0].unk_00 + 1; i++) {
        menu_set_colour(menu[i].kind, 0);
    }
    D_800A9888 = 2;
}

/* func_8009FF38 passes D_801E1CA4, which this never reads. */
void menu_create_player_slots(s32 unused) {
    ObjectDef *def;
    u8 *anim;
    s32 i;

    for (i = 0; i < 3; i++) {
        def = D_800AA248.new_def = func_8001D110();
        def->id = 0x4A002618;
        def->pos_y.w = 0xBA0000;
        def->pos_x.w = (i * 0x78 + 0x25) << 16;
        def->flags = 0x1F5;
        def->unk_06 |= 0x20;
        D_800AA248.cur_obj = func_8001DCB4();
        D_801E294C[i] = D_800AA248.cur_obj;
        D_800AA248.cur_obj->anim = (s32) D_800A7510;
        D_800AA248.cur_obj->frames_left = 0;
        def->pos_y.w = 0x8C0000;
        def->id = 0x4A001888;
        def->pos_x.w = (i * 0x78 + 0x28) << 16;
        def->flags = 0x1F2;
        def->unk_06 |= 0x20;
        D_800AA248.cur_obj = func_8001DCB4();
        *(D_801E294C + i + 6) = D_800AA248.cur_obj;
        D_800AA248.cur_obj->anim = (s32) D_800A751C;
        D_800AA248.cur_obj->frames_left = 0;
        if (i < D_8007A690) {
            anim = D_800A74C0[i];
            def->id = D_800A74A8[i];
        } else {
            anim = D_800A74CC[i];
            def->id = D_800A74B4[i];
        }
        def->unk_06 |= 0x20;
        def->pos_x.w = (i * 0x78 + 0x2D) << 16;
        def->pos_y.w = 0x880000;
        def->flags = 0x1F3;
        D_800AA248.cur_obj = func_8001DCB4();
        D_801E2958[i] = D_800AA248.cur_obj;
        D_800AA248.cur_obj->anim = (s32) anim;
        D_800AA248.cur_obj->frames_left = 0;
    }
}

void func_8009E7D4(s16 n) {
    GameObject *saved;
    ObjectDef *def;

    saved = D_800AA248.cur_obj;
    D_800AA248.new_def = def = func_8001D110();
    def->id = 0x4A00004E;
    def->pos_x.w = ((n - 1) * 0x78 + 0x91) << 16;
    def->pos_y.w = 0xBE0000;
    def->flags = 0x1F8;
    def->unk_06 |= 0x20;
    D_800AA248.cur_obj = func_8001DCB4();
    *(D_801E28F4 + n + 1) = D_800AA248.cur_obj;
    D_800AA248.cur_obj->anim = (s32) D_800A74E4;
    D_800AA248.cur_obj->frames_left = 0;
    D_800AA248.cur_obj->flags |= 0x400;
    D_800AA248.cur_obj = saved;
}

void menu_create_player_bars(s16 player, s16 flag) {
    s32 x;
    s32 y;
    u8 *anim;
    s32 bx;
    s32 by;
    GameObject *bar0;
    GameObject *bar1;
    GameObject *bar2;
    ObjectDef *def;

    y = 0x190000;
    anim = NULL;
    x = ((player - 1) * 0x78 + 0x9C) << 16;
    if (flag != 0) {
        y = -0x200000;
        anim = D_800A747C;
    }
    bx = (x + 0x90000) >> 16;
    by = y >> 16;
    bar0 = main_create_box(bx, by - 1, D_800A734C[player * 3], 7, 0xFF0000);
    *(D_801E28F4 + player * 3 + 31) = bar0;
    bar0->priority = 0x1F1;
    bar0->anim = (s32) anim;
    bar0->flags |= 0x400;
    bar1 = main_create_box(bx, by + 9, D_800A734C[player * 3 + 1], 7, 0xFF00);
    *(D_801E28F4 + player * 3 + 32) = bar1;
    bar1->priority = 0x1F1;
    bar1->anim = (s32) anim;
    bar1->flags |= 0x400;
    bar2 = main_create_box(bx, by + 19, D_800A734C[player * 3 + 2], 7, 0xFFFF);
    *(D_801E28F4 + player * 3 + 33) = bar2;
    bar2->priority = 0x1F1;
    bar2->anim = (s32) anim;
    bar2->flags |= 0x400;
    D_800A98A0[player * 3] = D_800A92E0[player * 3] = D_800A734C[player * 3];
    D_800A98A0[player * 3 + 1] = D_800A92E0[player * 3 + 1] = D_800A734C[player * 3 + 1];
    D_800A98A0[player * 3 + 2] = D_800A92E0[player * 3 + 2] = D_800A734C[player * 3 + 2];
    D_800AA248.new_def = def = func_8001D110();
    def->id = 0x4A001DD6;
    def->pos_x.w = x;
    def->pos_y.w = y;
    def->flags = 0x1F2;
    def->unk_06 |= 0x20;
    D_800AA248.cur_obj = func_8001DCB4();
    *(D_801E28F4 + player + 16) = D_800AA248.cur_obj;
    D_800AA248.cur_obj->anim = (s32) D_800A7444;
    D_800AA248.cur_obj->frames_left = 0;
    if (flag != 0) {
        D_800AA248.cur_obj->anim = (s32) D_800A7454;
    }
}

void menu_create_player_monster(s16 player, s16 flag) {
    ObjectDef *def;
    GameObject *obj;
    s32 x;

    D_800A8FD4[player].unk_08 = 0xB;
    D_800A8FD4[player].unk_04 = player;
    D_800A8FD4[player].unk_06 = 0;
    D_800AA244[player] = 0;
    D_800AA2CC[player] = 0;
    def = D_800AA248.new_def = func_8001D110();
    def->id = D_800A8EE4[D_800A8FD4[player].unk_04];
    def->pos_x.w = ((player - 1) * 0x78 + 0xCD) << 16;
    def->pos_y.w = 0xBE0000;
    def->flags = 0x1F4;
    def->unk_06 |= 0x20;
    D_800AA248.cur_obj = func_8001DCB4();
    *(D_801E28F4 + player + 13) = D_800AA248.cur_obj;
    D_800AA248.cur_obj->anim = D_800A8F00[player];
    D_800AA248.cur_obj->frames_left = 0;
    if (player == 6) {
        if (D_801F9ABC == 0) {
            D_800AA248.cur_obj->unk_74 = D_800A900C;
        } else if (D_801F9ABC == 3) {
            D_800AA248.cur_obj->unk_74 = 7;
        } else {
            D_800AA248.cur_obj->unk_74 = 8;
        }
    } else {
        D_800AA248.cur_obj->unk_74 = D_800A8FF4[player];
    }
    def->id = D_800A8FA8[D_800A8FD4[player].unk_04];
    def->flags = 0x258;
    def->unk_06 |= 0x20;
    D_800AA248.cur_obj = func_8001DCB4();
    *(D_801E28F4 + player + 19) = D_800AA248.cur_obj;
    main_set_frame(D_800A8FA8[D_800A8FD4[player].unk_04], D_800AA248.cur_obj->flags, D_800AA248.cur_obj);
    x = (player - 1) * 0x78 + 0xC8;
    D_800AA248.cur_obj->pos_x.w = (x - (s16) D_800AA248.cur_obj->frame->size.u.lo / 2) << 16;
    D_800AA248.cur_obj->pos_y.w = 0xC80000;
    D_800A9850[player] = 1;
    if (flag != 0) {
        obj = *(D_801E28F4 + player + 13);
        obj->anim = D_800A8F00[player + 0x1C];
        obj->pos_y.w = -0x140000;
    }
}

GameObject *menu_animate(GameObject *obj, s32 player) {
    s32 op;
    s32 arg;
    s32 id;
    s32 x;
    s32 frames;
    GameObject *name;

    if (obj != NULL) {
        obj->pos_y.w += obj->vel_y.w;
        obj->vel_y.w += obj->unk_64.w;
        if (player < 3) {
            obj->pos_y.s.hi += D_800AA2CC[player];
        }
        if (obj->frames_left == 0) {
            do {
                op = ((s32 *) obj->anim)[0];
                arg = ((s32 *) obj->anim)[1];
                switch (op) {
                case 0:
                    obj->anim = arg;
                    break;
                case 1:
                    obj->priority = arg;
                    obj->anim += 8;
                    break;
                case 2:
                    obj->vel_y.w = arg;
                    obj->unk_64.w = ((s32 *) obj->anim)[2];
                    obj->anim += 12;
                    break;
                case 3:
                    if (obj->pos_y.s.hi > 0xBE) {
                        obj->pos_y.w = 0xBE0000;
                        obj->vel_y.w = 0;
                        obj->unk_64.w = 0;
                        obj->anim += 4;
                    } else {
                        obj->anim -= 8;
                    }
                    break;
                case 4:
                    if (obj->pos_y.s.hi > 0x15E) {
                        obj->pos_y.w = -0x140000;
                        obj->vel_y.w = 0;
                        obj->unk_64.w = 0;
                        obj->anim = D_800A8F00[D_800A8FD4[player].unk_04 + 0x1C];
                        obj->frames_left = 0;
                        name = *(D_801E28F4 + player + 19);
                        if (D_800A8FD4[player].unk_04 == 6) {
                            if (D_801F9ABC == 0) {
                                obj->unk_74 = D_800A8FF4[D_800A8FD4[player].unk_04];
                                D_800A92E0[player * 3] = D_800A734C[D_800A8FD4[player].unk_04 * 3];
                                D_800A92E0[player * 3 + 1] = D_800A734C[D_800A8FD4[player].unk_04 * 3 + 1];
                                D_800A92E0[player * 3 + 2] = D_800A734C[D_800A8FD4[player].unk_04 * 3 + 2];
                                main_set_frame(D_800A8FA8[D_800A8FD4[player].unk_04], name->flags, name);
                            } else if (D_801F9ABC == 3) {
                                obj->unk_74 = 7;
                                D_800A92E0[player * 3] = D_800A734C[21];
                                D_800A92E0[player * 3 + 1] = D_800A734C[22];
                                D_800A92E0[player * 3 + 2] = D_800A734C[23];
                                main_set_frame(0x4F003EB2, name->flags, name);
                            } else {
                                obj->unk_74 = 8;
                                D_800A92E0[player * 3] = D_800A734C[24];
                                D_800A92E0[player * 3 + 1] = D_800A734C[25];
                                D_800A92E0[player * 3 + 2] = D_800A734C[26];
                                main_set_frame(0x4F003EB0, name->flags, name);
                            }
                        } else {
                            obj->unk_74 = D_800A8FF4[D_800A8FD4[player].unk_04];
                            D_800A92E0[player * 3] = D_800A734C[D_800A8FD4[player].unk_04 * 3];
                            D_800A92E0[player * 3 + 1] = D_800A734C[D_800A8FD4[player].unk_04 * 3 + 1];
                            D_800A92E0[player * 3 + 2] = D_800A734C[D_800A8FD4[player].unk_04 * 3 + 2];
                            main_set_frame(D_800A8FA8[D_800A8FD4[player].unk_04], name->flags, name);
                        }
                        x = (player - 1) * 0x78 + 0xC8;
                        name->pos_x.w = (x - (s16) name->frame->size.u.lo / 2) << 16;
                    } else {
                        obj->anim -= 8;
                    }
                    break;
                case 5:
                    obj->anim -= 8;
                    break;
                case 7:
                    D_800AA244[player] = arg;
                    obj->anim += 8;
                    break;
                case 8:
                    D_800AA2CC[player] = arg;
                    obj->pos_y.s.hi += arg;
                    obj->anim += 8;
                    func_8009E7D4(player);
                    func_8001F724(5);
                    func_8001F724(0x44);
                    break;
                case 10:
                    func_8001F724(arg);
                    obj->anim += 8;
                    break;
                case 9:
                    func_8001E4B0(obj);
                    return NULL;
                }
            } while (op < 0xB);
            id = ((s32 *) obj->anim)[0];
            frames = ((s32 *) obj->anim)[1];
            if (id != 0xDEAD) {
                main_set_frame(id, obj->flags, obj);
            }
            obj->frames_left = frames;
            obj->anim += 8;
        } else {
            obj->frames_left--;
        }
    }
    return obj;
}

void menu_update_player_select(void) {
    s32 i;
    s32 j;
    s32 d;
    GameObject *obj;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            d = (D_800A92E0[i * 3 + j] - D_800A98A0[i * 3 + j]) >> 3;
            if (d != 0) {
                D_800A98A0[i * 3 + j] += d;
            } else {
                D_800A98A0[i * 3 + j] = D_800A92E0[i * 3 + j];
            }
            if (*(D_801E28F4 + i * 3 + j + 31) != NULL) {
                (*(D_801E28F4 + i * 3 + j + 31))->unk_40.w = D_800A98A0[i * 3 + j];
            }
        }
    }
    for (i = 0; i < 3; i++) {
        menu_animate(*(D_801E28F4 + i + 13), i);
    }
    for (i = 0; i < 3; i++) {
        menu_animate(*(D_801E28F4 + i + 22), i);
        menu_animate(*(D_801E28F4 + i + 28), i);
        menu_animate(*(D_801E28F4 + i + 25), i);
        menu_animate(*(D_801E28F4 + i + 16), 0xFF);
        for (j = 0; j < 3; j++) {
            obj = *(D_801E28F4 + i * 3 + j + 31);
            if (obj != NULL && obj->anim != 0) {
                menu_animate(obj, 0xFF);
            }
        }
        D_801E28F8[i] = menu_animate(D_801E28F8[i], i);
    }
    for (i = 0; i < 3; i++) {
        if (D_800AA2CC[i] != 0) {
            if (D_800AA2CC[i] < 0) {
                D_800AA2CC[i]++;
            }
            D_800AA2CC[i] = -D_800AA2CC[i];
        }
    }
}

void menu_choose_monsters(s32 unused, s32 *timer) {
    s32 i;
    OverattrPlayer *rec;
    s32 j;
    s32 found;
    s16 m;
    s32 monster;
    u16 pad;
    GameObject *obj;

    for (i = 0, rec = D_800A8FD4; i < 3; i++, rec++) {
        monster = rec->unk_04;
        pad = (u32) tour_get_pressed() >> D_8007C144[i];
        obj = *(D_801E28F4 + i + 13);
        if (obj == NULL) {
            continue;
        }
        if (rec->unk_08 != 0) {
            rec->unk_08--;
        } else if (rec->unk_06 != 0) {
            if ((pad & 0x10) && D_800AA244[i] == 1) {
                D_800A9860 = 0x708;
                obj->anim = D_800A8F00[rec->unk_04 + 0xE];
                obj->frames_left = 0;
                rec->unk_06 = 0;
                D_800AA244[i] = 0;
                D_801FA8A0[rec->unk_04] = 0;
                *timer = 0xE10;
            }
        } else if ((pad & 0x110) && D_800AA244[i] == 0) {
            found = 0;
            D_800A9860 = 0x708;
            for (j = 0; j < 3; j++) {
                if (D_800A8FD4[j].unk_04 == rec->unk_04 && D_800A8FD4[j].unk_06 == 1 && j != i) {
                    found = 1;
                }
            }
            rec->unk_08 = 0xB;
            if (found == 0) {
                rec->unk_06 = 1;
                D_801FA8A0[rec->unk_04] = i + 1;
                func_8001F724(D_800A8FC4[rec->unk_04]);
                obj->anim = D_800A8F00[rec->unk_04 + 0x23];
                obj->frames_left = 0;
            }
            *timer = 0xE10;
        } else if ((pad & 0xA) && D_800AA244[i] == 0) {
            D_800A9860 = 0x708;
            do {
                found = 0;
                if (rec->unk_04 != 6) {
                    m = rec->unk_04 + 1;
                } else {
                    m = 0;
                }
                rec->unk_04 = m;
                if (D_801F9A44[m] != 0) {
                    found = 1;
                }
                for (j = 0; j < 3; j++) {
                    if (D_800A8FD4[j].unk_04 == m && D_800A8FD4[j].unk_06 == 1 && j != i) {
                        found = 1;
                        break;
                    }
                }
            } while (found);
            func_8001F724(0x2D);
            rec->unk_08 = 0xB;
            obj->anim = D_800A8F00[monster + 0x15];
            obj->frames_left = 0;
            *timer = 0xE10;
        } else if (((pad & 4) || (pad & 1)) && D_800AA244[i] == 0) {
            D_800A9860 = 0x708;
            do {
                found = 0;
                if (rec->unk_04 != 0) {
                    m = rec->unk_04 - 1;
                } else {
                    m = 6;
                }
                rec->unk_04 = m;
                if (D_801F9A44[m] != 0) {
                    found = 1;
                }
                for (j = 0; j < 3; j++) {
                    if (D_800A8FD4[j].unk_04 == m && D_800A8FD4[j].unk_06 == 1 && j != i) {
                        found = 1;
                        break;
                    }
                }
            } while (found);
            func_8001F724(0x2D);
            rec->unk_08 = 0xB;
            obj->anim = D_800A8F00[monster + 0x15];
            obj->frames_left = 0;
            *timer = 0xE10;
        } else if (pad & 0x40) {
            func_8001F724(3);
            *timer = 1;
        }
    }
}

void menu_place_objects(OverattrPlacement *p, s32 n, s32 color) {
    s32 i;
    OverattrPlacement *q;

    D_801F9AC8.w = 0;
    D_801F9ACC.w = 0;
    q = p;
    for (i = 0; i < n; i++) {
        tour_place_object(q++)->colour.w = color;
    }
}

void menu_create_buttons(void) {
    ObjectDef *def;
    GameObject *head;
    GameObject *obj;

    D_800AA248.new_def = def = func_8001D110();
    def->id = 0x4F002808;
    def->pos_x.w = 0x320000;
    def->pos_y.w = 0xD70000;
    def->flags = 0x1FE;
    def->unk_06 |= 0x20;
    D_801D373C[0] = func_8001DCB4();
    D_801D373C[0]->kind = 0x550;
    D_801D373C[0]->colour.w = 0x808080;
    D_800AA248.new_def = def = func_8001D110();
    def->id = 0x4F00280A;
    def->pos_x.w = 0x10E0000;
    def->pos_y.w = 0xD70000;
    def->flags = 0x1FE;
    def->unk_06 |= 0x20;
    D_801D373C[1] = func_8001DCB4();
    D_801D373C[1]->kind = 0x550;
    D_801D373C[1]->colour.w = 0x808080;
    func_8001F61C("SELECT", 0x4B, 0xD6, 1, 0x46, D_8007AD4C, 1, 0x550);
    func_8001F61C("BACK", 0x127, 0xD6, 1, 0x46, D_8007AD4C, 1, 0x550);
    head = &D_801E28C0;
    obj = head->next;
    if (obj != head) {
        do {
            if (obj->kind == 0x550) {
                obj->colour.w = 0x808080;
            }
            obj = obj->next;
        } while (obj != head);
    }
}

void menu_create_select_button(void) {
    ObjectDef *def;
    GameObject *head;
    GameObject *obj;

    D_800AA248.new_def = def = func_8001D110();
    def->pos_x.w = 0x320000;
    def->pos_y.w = 0xD70000;
    def->id = 0x4F002808;
    def->flags = 0x1FE;
    def->unk_06 |= 0x20;
    D_801D373C[0] = func_8001DCB4();
    D_801D373C[0]->kind = 0x550;
    D_801D373C[0]->colour.w = 0x808080;
    func_8001F61C("SELECT", 0x4B, 0xD6, 1, 0x46, D_8007AD4C, 1, 0x550);
    head = &D_801E28C0;
    obj = head->next;
    if (obj != head) {
        do {
            if (obj->kind == 0x550) {
                obj->colour.w = 0x808080;
            }
            obj = obj->next;
        } while (obj != head);
    }
}

void menu_update_title(void) {
    s32 state;

    func_80019268();
    D_800A9250 = D_800A9220;
    D_800A9220 = D_801E0D7C & 0x3FFFFFFF;
    if (D_800A6F39 != 0) {
        if (--D_800A6F39 != 0) {
            return;
        }
        D_801D3780 = 0;
        D_801CA45C = 4;
        D_800A9860 = 0x708;
        D_801F9944 = 0xB;
        D_801D872C /= 2;
    }
    D_800A6F39 = 0;
    if (D_801CA45C == 1) {
        func_80017B24();
        func_8001A420();
        func_8001A474();
        func_8001AC18(0xA, 0x29);
        func_8001F760();
        D_801CA45C = 2;
        menu_place_objects(D_800A7384, 4, 0x808080);
        D_801E29BC = 0x708;
        D_800A92C8 = 0x3C;
        D_801D3D7C = 0;
        SetDispMask(1);
    }
    state = D_801CA45C;
    if (state == 2) {
        if (D_800A92C8 == 0x3C) {
            func_8001F61C("PRESS START", 0xC8, 0xD2, 1, 0x45, D_8007ABCC, 0, 0x400);
        }
        if (D_800A92C8 == 0) {
            main_free_kind(0x400);
            D_800A92C8 = 0x5B;
        }
        D_800A92C8--;
        if (D_800A9220 & 0x11044110) {
            main_free_kind(0x400);
            func_8001F724(3);
            D_800AA2EC = 0x45;
            func_8001ED54(&D_800897FC);
            D_800A6F39 = state;
            return;
        }
    }
    if (D_801E29BC == 0) {
        D_801CA45C = 3;
        D_801E29BC = 0x3C;
        D_801F9AE0 = 1;
        D_801D36FC = 0x120;
        D_801D3780 = 0x63;
    }
    D_801E29BC--;
}

void menu_free_objects(void) {
    GameObject *head;
    GameObject *obj;
    GameObject *next;

    head = &D_801E28C0;
    obj = head->next;
    if (obj != head) {
        do {
            next = obj->next;
            if (obj != NULL) {
                func_8001E4B0(obj);
            }
            obj = next;
        } while (obj != head);
    }
}

s16 func_8009FF38(void) {
    MenuRecord *menu;
    MenuRecord *cur;                    /* the current menu, whose record 1 holds its per-frame function */
    s32 i;
    s32 all;
    s32 bit;

    D_800A6F78 = 0;
    menu_update_fade();
    func_80019268();
    D_800A9250 = D_800A9220;
    D_800A9220 = D_801E0D7C & 0x3FFFFFFF;
    if (--D_800A9860 <= 0) {
        func_80062E44();
        D_801CA45C = 0;
        return 0;
    }
    if (D_801F9944 != 0) {
        D_801F9944--;
    }
    switch (D_801D3780) {
    case 0:
        for (i = 0; i < 7; i++) {
            D_801FA8A0[i] = 0;
        }
        D_801E0D64 = 0;
        D_801F9944 = 0xB;
        func_80017B24();
        func_8001A420();
        func_8001A474();
        func_8001AC18(0xA, 0x1C);
        func_8001AA4C(0xB, 0x1D);
        func_8001F760();
        D_801D3780 = 1;
    case 1:
    main_menu:
        menu_place_objects(D_800A73C4, 4, 0x404040);
        D_800A92C0 = NULL;
        D_801E0D64 = 0;
        D_801F9944 = 0xB;
        D_800A9888 = 0;
        D_800A9870 = 0;
        D_800A92D8 = D_800A6FCC;
        D_801D885C = 0x44;
        D_801E2A44 = 0x45;
        D_801F9AAC = 0x47;
        menu_create_buttons();
        D_801D3780 = 6;
        break;
    case 6:
        menu = D_800A92D8;
        if (D_800A9800 == 0) {
            menu->sub.menu = D_800A92C0;
            menu->kind = D_800A92D0;
        }
        D_800A92C0 = D_800A92D8;
        D_800A92D0 = D_800A9870;
        D_800A9840 = menu_draw(D_800A92D8, D_800A9870, (s16) D_801E2A44, D_801F9AAC);
        if (menu == D_800A7200) {
            menu_draw_controls();
            for (i = 0; i < 12; i++) {
                D_801E28F4[i]->kind = 0x400;
                D_801E28F4[i]->flags |= 0x500;
                D_801E28F4[i]->colour.w = 0;
            }
            for (i = 0; i < 3; i++) {
                menu_set_colour(D_800A6FBC[i], 0);
                menu_set_colour(D_800A6FBC[i] + 1, 0);
                menu_set_colour(D_800A6FBC[i] + 2, 0);
                menu_set_colour(D_800A6FBC[i] + 3, 0);
            }
        } else if (menu == D_800A7248) {
            for (i = 0; i < 2; i++) {
                D_800A92F8[i]->kind = 0x400;
                D_800A92F8[i]->flags |= 0x500;
                D_800A92F8[i]->colour.w = 0;
                D_800A92F8[i]->pos_x.s.hi = 0x6E;
                D_800A9808[i]->pos_x.s.hi = 0x7C;
            }
        }
        cur = D_800A92C0;
        D_801D3780 = 7;
        if (cur[1].sub.fn != NULL) {
            cur[1].sub.fn();
        }
        menu_fade_in(D_800A92C0);
        break;
    case 7:
        if (D_800A9888 == 0) {
            D_801D3780 = 0xFF;
        }
        break;
    case 8:
        if (D_800A9888 == 0) {
            menu_free_all();
            D_801D3780 = 6;
        }
        break;
    case 2:
        menu_free_objects();
        D_801FA958 = -1;
        menu_place_objects(D_800A7404, 4, 0x808080);
        menu_create_player_slots(D_801E1CA4);
        for (i = 0; i < 3; i++) {
            /* the player's picture, its slot object and its bar frame */
            D_800A9850[i] = 0;
            *(D_801E28F4 + 13 + i) = NULL;
            *(D_801E28F4 + 1 + i) = NULL;
            *(D_801E28F4 + 16 + i) = NULL;
        }
        for (i = 0; i < 3; i++) {
            D_800A8FD4[i].unk_04 = i;
            D_800A8FD4[i].unk_06 = 0;
            D_800A8FD4[i].unk_08 = 0xB;
            D_800AA244[i] = 0;
            D_800AA2CC[i] = 0;
        }
        for (i = 0; i < 7; i++) {
            D_801FA8A0[i] = 0;
        }
        D_801E0D64 = 0;
        for (i = 0; i < D_8007A690; i++) {
            menu_create_player_monster(i, 0);
            menu_create_player_bars(i, 0);
        }
        D_801D3780 = 0xD;
        D_800A9290 = 0xE10;
        break;
    case 0xD:
        menu_create_buttons();
        D_801D3780 = 3;
        break;
    case 3:
        menu_update_player_select();
        if (--D_800A9290 != 0) {
            all = 1;
            menu_choose_monsters(2, &D_800A9290);
            D_801E0D64 = 0;
            for (i = 0; i < 7; i++) {
                if (D_801FA8A0[i] != 0) {
                    D_801E0D64 |= D_800A6FC4[D_801FA8A0[i]];
                }
            }
            for (i = 0; i < 3; i++) {
                if (D_800A9850[i] == 1 && D_800AA244[i] != D_800A9850[i]) {
                    all = 0;
                }
            }
            if (all == 1) {
                main_free_kind(0x401);
                main_free_kind(0x402);
                main_free_kind(0x403);
                D_801D3780 = 4;
                D_801D3778 = 0x3C;
            } else {
                D_801D872C = 0x32;
            }
        } else {
            tour_clear_objects();
            D_801E0D64 = 0;
            D_801F9944 = 0xB;
            menu_free_objects();
            goto main_menu;
        }
        break;
    case 4:
        break;
    case 5:
        if (menu_slide_kind(D_800A92C0[D_800A92D0 + 2].kind, 0x200000) != 0) {
            menu_free_others(D_800A92C0, D_800A92D0);
            D_801D3780 = D_801E2148;
        }
        break;
    case 0xFF:
        if (D_800A92C0 == D_800A7200) {
            D_801D3780 = 9;
        } else if (D_800A92C0 == D_800A70A4) {
            D_801D3780 = 0xA;
        } else {
            cur = D_800A92C0;
            D_800A9800 = 0;
            main_cycle_highlight();
            menu = cur;
            if (cur[1].sub.fn != NULL) {
                cur[1].sub.fn();
            }
            if ((D_800A9220 & 0x100401) && D_801F9944 == 0) {
                D_800A9860 = 0x708;
                if (--D_800A92D0 < 0) {
                    D_800A92D0 = D_800A9840 - 1;
                }
                menu_light_items(D_800A92C0, D_800A92D0, (s16) D_801E2A44, D_801F9AAC);
                D_801F9944 = 0xB;
                D_801D872C /= 2;
                func_8001F724(0x1E);
            } else if ((D_800A9220 & 0x200802) && D_801F9944 == 0) {
                D_800A9860 = 0x708;
                if (++D_800A92D0 >= D_800A9840) {
                    D_800A92D0 = 0;
                }
                menu_light_items(D_800A92C0, D_800A92D0, (s16) D_801E2A44, D_801F9AAC);
                D_801F9944 = 0xB;
                D_801D872C /= 2;
                func_8001F724(0x1E);
            } else if ((D_800A9220 & 0x1C0701C) && D_801F9944 == 0) {
                D_800A9860 = 0x708;
                D_800A92C0[D_800A92D0 + 2].sub.fn();
                D_801F9944 = 0xB;
                D_801D872C /= 2;
            } else if ((D_800A9220 & 0x4010040) && D_801F9944 == 0) {
                D_800A9860 = 0x708;
                if (D_800A92C0 == D_800A6FCC) {
                    D_800A9860 = 0;
                }
                if (menu->sub.menu != NULL) {
                    D_800A92D8 = menu->sub.menu;
                    D_800A9800 = 1;
                    D_800A9870 = menu->kind;
                    func_8001F724(3);
                    menu_fade_out();
                    D_801F9944 = 0xB;
                    D_801D872C /= 2;
                }
            }
        }
        break;
    case 9:
        cur = D_800A92C0;
        D_800A9800 = 0;
        menu = cur;
        if (cur[1].sub.fn != NULL) {
            cur[1].sub.fn();
        }
        for (i = 0; i < 3; i++) {
            bit = 1 << (i * 10);
            if ((D_800A9220 & bit) && D_801F9944 == 0) {
                D_800A9860 = 0x708;
                if (D_800A92B0[i] == 3) {
                    D_800A92B0[i] = i;
                } else {
                    D_800A92B0[i] = 3;
                }
                D_801F9944 = 0xB;
                D_801D872C /= 2;
                func_8001F724(0x1E);
            } else if ((D_800A9220 & (2 << (i * 10))) && D_801F9944 == 0) {
                D_800A9860 = 0x708;
                if (D_800A92B0[i] == 3) {
                    D_800A92B0[i] = i;
                } else {
                    D_800A92B0[i] = 3;
                }
                D_801F9944 = 0xB;
                D_801D872C /= 2;
                func_8001F724(0x1E);
            }
        }
        menu_light_choices(D_800A92C0, (s16) D_801E2A44, D_801F9AAC);
        main_cycle_highlight();
        if ((D_800A9220 & 0x1C0701C) && D_801F9944 == 0) {
            D_800A9860 = 0x708;
            if (D_800A9220 & 0x1C) {
                D_800A92C0[D_800A92B0[0] + 2].sub.fn();
            } else if (D_800A9220 & 0x7000) {
                D_800A92C0[D_800A92B2 + 2].sub.fn();
            } else if (D_800A9220 & 0x1C00000) {
                D_800A92C0[D_800A92B4 + 2].sub.fn();
            }
            D_801F9944 = 0xB;
            D_801D872C /= 2;
        } else if ((D_800A9220 & 0x4010040) && D_801F9944 == 0) {
            D_800A9860 = 0x708;
            if (menu->sub.menu != NULL) {
                D_800A92D8 = menu->sub.menu;
                D_800A9800 = 1;
                D_800A9870 = menu->kind;
                func_8001F724(3);
                menu_fade_out();
                D_801F9944 = 0xB;
                D_801D872C /= 2;
                for (i = 0; i < 12; i++) {
                    menu_set_colour(0x400, 0x808080);
                }
            }
        }
        break;
    case 0xA:
        cur = D_800A92C0;
        D_800A9800 = 0;
        if (cur[1].sub.fn != NULL) {
            cur[1].sub.fn();
        }
        break;
    }
    return D_800A6F78;
}

void menu_update_load_screen(void) {
    s32 status;
    MenuRecord *menu = D_800A92C0;

    switch (D_800A9878) {
    case 0:
        func_8001F61C("ACCESSING MEMORY CARD", 0xC8, 0x5A, 1, D_801F9AAC, D_8007ABCC, 0, 0x400);
        D_801E29BC = 0xA;
        D_800A9878 = 0xC;
        break;
    case 12:
        if (D_801E29BC-- > 0) {
            break;
        }
        status = card_get_status();
        main_free_kind(0x400);
        if (status == 2) {
            D_801E29BC = 0x96;
            D_800A9878 = 1;
            func_8001F61C("THE MEMORY CARD IN MEMORY", 0xC8, 0x5A, 1, D_801F9AAC, D_8007ABCC, 0, 0x400);
            if (D_801E28B8 == 0) {
                func_8001F61C("CARD SLOT 1", 0xC8, 0x78, 1, D_801F9AAC, D_8007ABCC, 0, 0x400);
            } else {
                func_8001F61C("CARD SLOT 1A", 0xC8, 0x78, 1, D_801F9AAC, D_8007ABCC, 0, 0x400);
            }
            func_8001F61C("IS NOT FORMATTED", 0xC8, 0x96, 1, D_801F9AAC, D_8007ABCC, 0, 0x400);
        }
        if (status == 1) {
            D_801E29BC = 0x96;
            D_800A9878 = status;
            func_8001F61C("THERE IS NO MEMORY CARD", 0xC8, 0x5A, 0, D_801F9AAC, D_8007ABCC, 0, 0x400);
            func_8001F61C("INSERTED IN MEMORY", 0xC8, 0x78, 0, D_801F9AAC, D_8007ABCC, 0, 0x400);
            if (D_801E28B8 == 0) {
                func_8001F61C("CARD SLOT 1", 0xC8, 0x96, 0, D_801F9AAC, D_8007ABCC, 0, 0x400);
            } else {
                func_8001F61C("CARD SLOT 1A", 0xC8, 0x96, 0, D_801F9AAC, D_8007ABCC, 0, 0x400);
            }
        }
        if (status == 0) {
            D_801E29BC = 3;
            D_800A9878 = 2;
            func_800A32CC();
        }
        break;
    case 1:
        if (D_801E29BC > 0) {
            D_801E29BC--;
        } else {
            menu_back();
        }
        break;
    case 2:
        if (D_801E29BC-- > 0) {
            break;
        }
        D_801E29BC = 0x5DC;
        status = card_read_save(&D_800A9300);
        D_800A9878 = 3;
        D_801D3780 = 0xA;
        main_free_kind(0x400);
        if (status != 0) {
            card_init_save(&D_800A9300);
            D_800A9840 = 0;
        } else {
            D_800A9840 = menu_list_saves();
        }
        break;
    case 3:
        if ((D_800A9220 & 0x100401) && D_801F9944 == 0) {
            if (--D_800A92D0 < 0) {
                D_800A92D0 = D_800A9840;
            }
            D_801F9944 = 0xB;
            D_801D872C /= 2;
            func_8001F724(0x1E);
        } else if ((D_800A9220 & 0x200802) && D_801F9944 == 0) {
            if (++D_800A92D0 > D_800A9840) {
                D_800A92D0 = 0;
            }
            D_801F9944 = 0xB;
            D_801D872C /= 2;
            func_8001F724(0x1E);
        } else if ((D_800A9220 & 0x01004010) && D_801F9944 == 0) {
            if (D_800A92D0 == D_800A9840) {
                menu_back();
                break;
            }
            D_801D3778 = 0x1E;
            D_801E0D64 = 1;
            menu_load_slot(D_800A9830[D_800A92D0]);
            D_801F9944 = 0xB;
            D_801D872C /= 2;
        } else if ((D_800A9220 & 0x04010040) && D_801F9944 == 0 && menu[0].sub.menu != NULL) {
            D_800A92D8 = menu[0].sub.menu;
            D_800A9800 = 1;
            D_800A9870 = menu[0].kind;
            func_8001F724(3);
            menu_fade_out();
            D_801F9944 = 0xB;
            D_801D872C /= 2;
        }
        func_8009E310((s16) D_801E2A44, D_801F9AAC);
        main_cycle_highlight();
        break;
    }
}

s32 menu_list_saves(void) {
    char buf[0x18];
    s32 limit;
    s32 n;
    s32 slot;
    s32 best;
    s32 i;
    s32 j;
    s32 count;
    s32 city;
    u8 *name;

    limit = 10000000;
    n = 0;
    slot = 0;
    for (;;) {
        best = -1;
        for (i = 0; i < 6; i++) {
            if (D_800A9300.unk_204[i] == 0 && best < D_800A9300.slots[i].unk_00 && D_800A9300.slots[i].unk_00 < limit) {
                slot = i;
                best = D_800A9300.slots[i].unk_00;
            }
        }
        if (best == -1) {
            return n;
        }
        count = 0;
        for (j = 0; j < 7; j++) {
            if (D_800A9300.slots[slot].unk_49[j] != 0) {
                count++;
            }
        }
        city = D_800A9300.slots[slot].city;
        name = D_8007C704[city];
        D_800A9830[n] = slot;
        D_800A9820[n] = 0x20;
        D_800A9810[n] = n * 23 + 60;
        sprintf(buf, "%s   %dP", name, count);
        func_8001F61C(buf, D_800A9820[n], D_800A9810[n], 1, D_801F9AAC, D_8007AD4C, 1, 0x450 + n);
        n++;
        limit = best;
    }
}

void menu_load_slot(s32 slot) {
    s32 i;
    Monster *m;

    D_801FA958 = D_800A9300.slots[slot].unk_00;
    D_801FA960 = D_800A9300.slots[slot].city;
    D_801D883C = D_800A9300.slots[slot].unk_04;
    D_801FA964 = D_800A9300.slots[slot].unk_06;
    D_801D8728 = D_800A9300.slots[slot].unk_08;
    D_801E1CA8 = D_800A9300.slots[slot].unk_0A;
    D_801D36FC = D_800A9300.slots[slot].mode;
    D_801E289C = D_800A9300.slots[slot].unk_66;
    D_801FA984[0] = D_800A9300.slots[slot].unk_50[0];
    D_801FA984[1] = D_800A9300.slots[slot].unk_50[1];
    D_801FA984[2] = D_800A9300.slots[slot].unk_50[2];
    D_801FA984[3] = D_800A9300.slots[slot].unk_50[3];
    for (i = 0; i < 7; i++) {
        m = &D_801E0B78[i + 1];
        m->action = 0;
        m->unk_01C = 0;
        m->unk_1CC = 0;
        m->id = 0;
        m->unk_058 = 0;
        D_801F9A44[i] = D_800A9300.slots[slot].unk_58[i];
        D_801FA8A0[i] = D_800A9300.slots[slot].unk_49[i];
    }
    for (i = 0; i < 3; i++) {
        m = &D_801E0B78[func_80025DF8(i + 1)];
        m->id = D_800A9300.slots[slot].monster[i];
        m->lives = D_800A9300.slots[slot].unk_12[i];
        m->lives_shown = D_800A9300.slots[slot].unk_12[i];
        m->health.w = D_800A9300.slots[slot].health[i];
        m->meter.w = D_800A9300.slots[slot].meter[i];
        m->score = D_800A9300.slots[slot].unk_30[i];
        D_801D8800[i] = D_800A9300.slots[slot].unk_46[i];
    }
    D_801E1CB4 = D_800A9300.slots[slot].unk_42;
    D_8007A7D4 &= ~1;
    D_8007A694 = D_800A9300.slots[slot].unk_3E;
    D_801E2150 = D_800A9300.slots[slot].unk_40;
    D_8007A68A = D_800A9300.slots[slot].unk_44;
    D_8007A68C = D_800A9300.slots[slot].unk_68;
    D_801F9ABC = D_800A9300.slots[slot].unk_6A;
    D_8007A686 = D_800A9300.slots[slot].unk_6C;
    D_8007A688 = D_800A9300.slots[slot].unk_6E;
    D_8007A68E = D_800A9300.slots[slot].unk_70;
    D_8007C974 = D_800A9300.slots[slot].unk_72;
    func_80062DA8((u8) D_801E1CB4);
    func_80062D88((u8) D_801E2150);
}

void menu_update_save_screen(void) {
    D_801D885C = 0x44;
    if (D_800A9898 == 1) {
        D_800A9898 = 0;
        main_free_kind_masked(0x400, -0x100);
    }
    switch (D_800A98B8) {
    case 0:
        menu_check_card();
        break;
    case 6:
        menu_ask_format();
        break;
    case 1:
        menu_delete_save();
        break;
    case 2:
        menu_write_save();
        break;
    case 5:
        D_801D3780++;
        break;
    case 4:
        func_800A309C();
        D_800A98B8 = 5;
        break;
    }
}

void menu_check_card(void) {
    s32 status;

    switch (D_800A92A0) {
    case 0:
        if (D_801E29BC == 5) {
            func_8001F61C("ACCESSING MEMORY CARD", 0xC8, 0x5A, 1, D_801F9AAC, D_8007ABCC, 0, 0x400);
        }
        if (D_801E29BC-- > 0) {
            break;
        }
        status = card_get_status();
        main_free_kind_masked(0x400, -0x100);
        if (status == 2) {
            D_800A9898 = 1;
            D_800A92A0 = 0;
            D_800A98B8 = 6;
            break;
        }
        if (status == 1) {
            D_801E29BC = 0x96;
            D_800A92A0 = status;
            func_8001F61C("THERE IS NO MEMORY CARD", 0xC8, 0x5A, 0, D_801F9AAC, D_8007ABCC, 0, 0x400);
            func_8001F61C("INSERTED IN MEMORY", 0xC8, 0x78, 0, D_801F9AAC, D_8007ABCC, 0, 0x400);
            if (D_801E28B8 == 0) {
                func_8001F61C("CARD SLOT 1", 0xC8, 0x96, 0, D_801F9AAC, D_8007ABCC, 0, 0x400);
            } else {
                func_8001F61C("CARD SLOT 1A", 0xC8, 0x96, 0, D_801F9AAC, D_8007ABCC, 0, 0x400);
            }
            break;
        }
        if (status == 0) {
            D_801E29BC = 0x1E;
            D_800A92A0 = 2;
            func_800A32CC();
            break;
        }
        /* fallthrough: an unexpected status gives up as case 1 does */
    case 1:
        if (D_801E29BC > 0) {
            D_801E29BC--;
        } else {
            main_free_kind_masked(0x400, -0x100);
            D_801D3780 -= 2;
        }
        break;
    case 2:
        if (D_801E29BC == 30) {
            D_801E29BC--;
        } else if (D_801E29BC == 29) {
            D_801E29BC--;
            if (card_read_save(&D_800A9300) == 0) {
                if (D_801FA958 != -1 || menu_find_used_slot() >= 0) {
                    D_800A9858 = 0;
                    D_800A9898 = 1;
                    D_800A92A0 = 5;
                } else {
                    D_800A9898 = 1;
                    D_800A92A0 = 0xA;
                }
            } else {
                card_init_save(&D_800A9300);
                if (menu_find_used_slot() >= 0) {
                    D_800A9858 = 0;
                    D_800A9898 = 1;
                    D_800A92A0 = 5;
                } else {
                    D_800A9898 = 1;
                    D_800A92A0 = 0xA;
                }
            }
        }
        break;
    case 5:
        if (D_801E29BC > 0) {
            D_801E29BC--;
        } else {
            D_800A9858 = 0;
            D_800A9898 = 1;
            D_800A98B8 = 2;
        }
        break;
    case 10:
        if (D_801E29BC > 0) {
            D_801E29BC--;
        } else {
            D_800A98B8 = 1;
            D_800A9880 = 0;
        }
        break;
    }
}

s32 menu_find_used_slot(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (D_800A9300.unk_204[i] != 0) {
            return i;
        }
    }
    return -1;
}

void menu_ask_format(void) {
    switch (D_800A92A0) {
    case 0:
        func_8001F61C("THE MEMORY CARD IN MEMORY", 0xC8, 0x2D, 1, D_801F9AAC, D_8007AD4C, 0, 0x400);
        if (D_801E28B8 == 0) {
            func_8001F61C("CARD SLOT 1 IS", 0xC8, 0x41, 1, D_801F9AAC, D_8007AD4C, 0, 0x400);
        } else {
            func_8001F61C("CARD SLOT 1A IS", 0xC8, 0x41, 1, D_801F9AAC, D_8007AD4C, 0, 0x400);
        }
        func_8001F61C("NOT FORMATTED", 0xC8, 0x55, 1, D_801F9AAC, D_8007AD4C, 0, 0x400);
        func_8001F61C("DO YOU WANT TO FORMAT", 0xC8, 0x6E, 1, D_801F9AAC, D_8007ABCC, 0, 0x400);
        func_8001F61C("THE MEMORY CARD ?", 0xC8, 0x8C, 1, D_801F9AAC, D_8007ABCC, 0, 0x400);
        func_8001F61C(D_80098260, 0xC8, 0xAA, 1, D_801F9AAC, D_8007AD4C, 0, 0x405);
        func_8001F61C(D_80098264, 0xC8, 0xBE, 1, D_801F9AAC, D_8007AD4C, 0, 0x406);
        D_800A92A0 = 3;
        D_800A92D0 = 1;
        break;
    case 3:
        if (D_801F9944 != 0) {
            D_801F9944--;
        }
        func_80019268();
        D_800A9250 = D_800A9220;
        D_800A9220 = D_801E0D7C & 0x3FFFFFFF;
        if ((D_800A9220 & 0x100401) && D_801F9944 == 0) {
            D_801F9944 = 0xB;
            D_800A92D0 ^= 1;
            D_801D872C /= 2;
            func_8001F724(0x1E);
        } else if ((D_800A9220 & 0x200802) && D_801F9944 == 0) {
            D_801F9944 = 0xB;
            D_800A92D0 ^= 1;
            D_801D872C /= 2;
            func_8001F724(0x1E);
        } else if ((D_800A9220 & 0x01004010) && D_801F9944 == 0) {
            D_801F9944 = 0x15;
            if (D_800A92D0 == 1) {
                main_free_kind_masked(0x400, -0x100);
                D_801D3780 -= 2;
                return;
            }
            card_init_save(&D_800A9300);
            D_800A92A0 = 4;
            D_800A9868 = 0;
            D_800A9898 = 1;
        }
        if (D_800A92D0 == 0) {
            func_8001EC74(0x405, (s16) D_801E2A44);
            func_8001EC74(0x406, D_801F9AAC);
        } else {
            func_8001EC74(0x405, D_801F9AAC);
            func_8001EC74(0x406, (s16) D_801E2A44);
        }
        break;
    case 4:
        menu_format_card();
        break;
    }
    main_cycle_highlight();
}

INCLUDE_RODATA("asm/overattr/nonmatchings/menu", D_80098260);

INCLUDE_RODATA("asm/overattr/nonmatchings/menu", D_80098264);

void menu_format_card(void) {
    s32 state;
    s32 status;

    state = D_800A9868;
    switch (state) {
    case 0:
        status = card_get_status();
        if (status != 2) {
            main_free_kind_masked(0x400, -0x100);
            D_801D3780 -= 2;
            break;
        }
        D_801E29BC = 0x1E;
        D_800A9868 = status;
        func_8001F61C("FORMATTING THE MEMORY", 0xC8, 0x5A, 1, D_801F9AAC, D_8007ABCC, 0, 0x400);
        func_8001F61C("CARD IN MEMORY", 0xC8, 0x78, 1, D_801F9AAC, D_8007ABCC, 0, 0x400);
        if (D_801E28B8 == 0) {
            func_8001F61C("CARD SLOT 1", 0xC8, 0x96, 1, D_801F9AAC, D_8007ABCC, 0, 0x400);
        } else {
            func_8001F61C("CARD SLOT 1A", 0xC8, 0x96, 1, D_801F9AAC, D_8007ABCC, 0, 0x400);
        }
        break;
    case 2:
        if (D_801E29BC-- < 0) {
            if (card_format() == 0) {
                D_800A9858 = 0;
                D_800A9898 = 1;
                D_800A98B8 = state;
            } else {
                D_801D3780 -= 2;
                main_free_kind_masked(0x400, -0x100);
            }
        }
        break;
    }
}

void menu_delete_save(void) {
    switch (D_800A9880) {
    case 0:
        D_801F9AAC = 0x47;
        D_801E2A44 = 0x45;
        D_801D885C = 0x44;
        D_801F9AB8 = 0;
        func_8001F61C("THERE IS NO FREE SAVE", 0xC8, 0x3C, 0, D_801F9AAC, D_8007ABCC, 0, 0x400);
        func_8001F61C("GAME SLOT.", 0xC8, 0x5A, 0, D_801F9AAC, D_8007ABCC, 0, 0x400);
        func_8001F61C("DELETE A SLOT TO SAVE", 0xC8, 0x78, 0, D_801F9AAC, D_8007ABCC, 0, 0x400);
        func_8001F61C("THIS NEW GAME.", 0xC8, 0x96, 0, D_801F9AAC, D_8007ABCC, 0, 0x400);
        D_801E29BC = 0x96;
        D_800A9880 = 0xB;
        break;
    case 11:
        if (D_801E29BC-- < 0) {
            main_free_kind(0x400);
            D_800A9880 = 3;
            D_800A9840 = menu_list_saves();
            D_800AA2EC = (s16) D_801E2A44;
            func_8001F61C("DELETE GAMES", 0xC8, 0x20, 0, D_801D885C, D_8007ABCC, 0, 0x400);
            func_8001ED54(&D_800A6400);
            menu_create_select_button();
        }
        break;
    case 3:
        if (D_801F9944 != 0) {
            D_801F9944--;
        }
        func_80019268();
        D_800A9250 = D_800A9220;
        D_800A9220 = D_801E0D7C & 0x3FFFFFFF;
        if ((D_800A9220 & 0x100401) && D_801F9944 == 0) {
            if (--D_800A92D0 < 0) {
                D_800A92D0 = D_800A9840;
            }
            D_801F9944 = 0xB;
            D_801D872C /= 2;
            func_8001F724(0x1E);
        } else if ((D_800A9220 & 0x200802) && D_801F9944 == 0) {
            if (++D_800A92D0 > D_800A9840) {
                D_800A92D0 = 0;
            }
            D_801F9944 = 0xB;
            D_801D872C /= 2;
            func_8001F724(0x1E);
        } else if ((D_800A9220 & 0x01004010) && D_801F9944 == 0) {
            if (D_800A92D0 == D_800A9840) {
                main_free_kind_masked(0x400, -0x100);
                D_801F9944 = 0xB;
                D_801D3780 -= 2;
                D_801D872C /= 2;
                return;
            }
            D_800A9848 = 1;
            D_800A9880 = 0xD;
            main_free_kind_masked(0x400, -0x100);
            D_801F9944 = 0xB;
            D_801D872C /= 2;
        } else if ((D_800A9220 & 0x04010040) && D_801F9944 == 0) {
            func_8001F724(3);
            menu_back();
            D_801F9944 = 0xB;
            D_801D872C /= 2;
        }
        func_8009E310((s16) D_801E2A44, D_801F9AAC);
        break;
    case 13:
        func_8001F61C("ARE YOU SURE?", 0xC8, 0x50, 1, D_801D885C, D_8007ABCC, 0, 0x400);
        func_8001F61C(D_80098260, 0xC8, 0x6E, 1, D_801F9AAC, D_8007AD4C, 0, 0x405);
        func_8001F61C(D_80098264, 0xC8, 0x82, 1, (s16) D_801E2A44, D_8007AD4C, 0, 0x406);
        D_800A9880 = 0xE;
        break;
    case 14:
        if (D_801F9944 != 0) {
            D_801F9944--;
        }
        func_80019268();
        D_800A9250 = D_800A9220;
        D_800A9220 = D_801E0D7C & 0x3FFFFFFF;
        if ((D_800A9220 & 0x100401) && D_801F9944 == 0) {
            D_801F9944 = 0xB;
            D_800A9848 ^= 1;
            D_801D872C /= 2;
            func_8001F724(0x1E);
        } else if ((D_800A9220 & 0x200802) && D_801F9944 == 0) {
            D_801F9944 = 0xB;
            D_800A9848 ^= 1;
            D_801D872C /= 2;
            func_8001F724(0x1E);
        } else if ((D_800A9220 & 0x01004010) && D_801F9944 == 0) {
            if (D_800A9848 == 0) {
                D_800A9858 = 0;
                D_800A9898 = 1;
                D_800A98B8 = 2;
                D_800A9300.unk_204[D_800A9830[D_800A92D0]] = 1;
            } else {
                main_free_kind_masked(0x550, -0x100);
                main_free_kind_masked(0x400, -0x100);
                D_801D3780 -= 2;
            }
            D_801F9944 = 0xB;
            D_801D872C /= 2;
        }
        if (D_800A9848 == 0) {
            func_8001EC74(0x405, (s16) D_801E2A44);
            func_8001EC74(0x406, D_801F9AAC);
        } else {
            func_8001EC74(0x405, D_801F9AAC);
            func_8001EC74(0x406, (s16) D_801E2A44);
        }
        break;
    }
    main_cycle_highlight();
}

s32 menu_find_save(s32 id) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (D_800A9300.slots[i].unk_00 == id) {
            return i;
        }
    }
    return -1;
}

void menu_write_save(void) {
    s32 slot;
    s32 i;
    s32 status;
    Monster *m;
    u8 buf[24];

    switch (D_800A9858) {
    case 0:
        if (D_801FA958 != -1) {
            slot = menu_find_save(D_801FA958);
            if (slot == -1) {
                D_801E29BC = 0x78;
                D_800A9858 = 0xF;
                break;
            }
        } else {
            slot = menu_find_used_slot();
        }
        D_800A9300.unk_204[slot] = 0;
        D_800A9300.slots[slot].unk_00 = D_800A9300.unk_200++;
        sprintf(buf, "%s", D_8007C704[D_801FA960]);
        D_800A9300.slots[slot].unk_04 = D_801D883C;
        D_800A9300.slots[slot].city = D_801FA960;
        D_800A9300.slots[slot].unk_06 = D_801FA964;
        D_800A9300.slots[slot].unk_08 = D_801D8728;
        D_800A9300.slots[slot].unk_0A = D_801E1CA8;
        D_800A9300.slots[slot].mode = D_801D36FC;
        D_800A9300.slots[slot].unk_66 = D_801E289C;
        D_800A9300.slots[slot].unk_50[0] = D_801FA984[0];
        D_800A9300.slots[slot].unk_50[1] = D_801FA984[1];
        D_800A9300.slots[slot].unk_50[2] = D_801FA984[2];
        D_800A9300.slots[slot].unk_50[3] = D_801FA984[3];
        for (i = 0; i < 3; i++) {
            m = &D_801E0B78[func_80025DF8(i + 1)];
            D_800A9300.slots[slot].monster[i] = m->id;
            D_800A9300.slots[slot].unk_12[i] = m->lives;
            D_800A9300.slots[slot].health[i] = m->health.w;
            D_800A9300.slots[slot].meter[i] = m->meter.w;
            D_800A9300.slots[slot].unk_30[i] = m->score;
            D_800A9300.slots[slot].unk_46[i] = D_801D8800[i];
        }
        for (i = 0; i < 7; i++) {
            D_800A9300.slots[slot].unk_58[i] = D_801F9A44[i];
            D_800A9300.slots[slot].unk_49[i] = D_801FA8A0[i];
        }
        D_800A9300.slots[slot].unk_3E = D_8007A694;
        D_800A9300.slots[slot].unk_40 = D_801E2150;
        D_800A9300.slots[slot].unk_42 = D_801E1CB4;
        D_800A9300.slots[slot].unk_44 = D_8007A68A;
        D_800A9300.slots[slot].unk_68 = D_8007A68C;
        D_800A9300.slots[slot].unk_6A = D_801F9ABC;
        D_800A9300.slots[slot].unk_6C = D_8007A686;
        D_800A9300.slots[slot].unk_6E = D_8007A688;
        D_800A9300.slots[slot].unk_70 = D_8007A68E;
        D_800A9300.slots[slot].unk_72 = D_8007C974;
        D_800A9300.checksum = card_calc_checksum(&D_800A9300);
        func_8001F61C("SAVING GAME", 0xC8, 0x5A, 1, D_801F9AAC, D_8007ABCC, 0, 0x400);
        D_800A9858 = 0xB;
        D_801E29BC = 0x1E;
        break;
    case 11:
        if (D_801E29BC-- < 0) {
            D_800A9858 = 5;
            D_801E29BC = 0xB4;
        }
        break;
    case 5:
        status = card_write_save(&D_800A9300);
        if (status == 0) {
            D_800A9898 = 1;
            D_800A9858 = 6;
        }
        if (status == 2) {
            D_800A9898 = 1;
            D_800A98B8 = 6;
        }
        if (status == 1) {
            D_800A9898 = 1;
            D_800A9858 = 8;
        }
        if (status == 3) {
            D_800A9898 = 1;
            D_800A9858 = 9;
        }
        break;
    case 6:
        if (D_801E29BC == 0xB4) {
            D_801FA958 = D_800A9300.unk_200 - 1;
            func_8001F61C("GAME SAVED", 0xC8, 0x5A, 1, D_801F9AAC, D_8007ABCC, 0, 0x400);
            sprintf(buf, "%s", D_8007C704[D_801FA960]);
            func_8001F61C(buf, 0xC8, 0x78, 1, D_801F9AAC, D_8007AD4C, 0, 0x400);
        }
        if (D_801E29BC-- < 0) {
            D_800A9898 = 1;
            D_800A98B8 = 5;
        }
        break;
    case 8:
        if (D_801E29BC == 0xB4) {
            func_8001F61C("THERE IS NO MEMORY CARD", 0xC8, 0x5A, 1, D_801F9AAC, D_8007ABCC, 0, 0x400);
            func_8001F61C("INSERTED IN MEMORY", 0xC8, 0x78, 1, D_801F9AAC, D_8007ABCC, 0, 0x400);
            if (D_801E28B8 == 0) {
                func_8001F61C("CARD SLOT 1", 0xC8, 0x96, 1, D_801F9AAC, D_8007ABCC, 0, 0x400);
            } else {
                func_8001F61C("CARD SLOT 1A", 0xC8, 0x96, 1, D_801F9AAC, D_8007ABCC, 0, 0x400);
            }
        }
        if (D_801E29BC-- < 0) {
            main_free_kind_masked(0x400, -0x100);
            D_801D3780 -= 2;
        }
        break;
    case 9:
        if (D_801E29BC == 0xB4) {
            func_8001F61C("THE MEMORY CARD IN MEMORY", 0xC8, 0x5A, 1, D_801F9AAC, D_8007ABCC, 0, 0x400);
            if (D_801E28B8 == 0) {
                func_8001F61C("CARD SLOT 1 IS FULL", 0xC8, 0x78, 1, D_801F9AAC, D_8007ABCC, 0, 0x400);
            } else {
                func_8001F61C("CARD SLOT 1A IS FULL", 0xC8, 0x78, 1, D_801F9AAC, D_8007ABCC, 0, 0x400);
            }
        }
        if (D_801E29BC-- < 0) {
            main_free_kind_masked(0x400, -0x100);
            D_801D3780 -= 2;
        }
        break;
    case 15:
        if (D_801E29BC == 0xB4) {
            func_8001F61C("A NEW MEMORY CARD", 0xC8, 0x5A, 1, D_801F9AAC, D_8007ABCC, 0, 0x400);
            func_8001F61C("HAS BEEN DETECTED", 0xC8, 0x78, 1, D_801F9AAC, D_8007ABCC, 0, 0x400);
        }
        if (D_801E29BC-- < 0) {
            D_801FA958 = -1;
            main_free_kind_masked(0x400, -0x100);
            D_801D3780 -= 2;
        }
        break;
    }
}

void func_800A309C(void) {
    D_801D3780 += 1;
}

void menu_load_newest_save(void) {
    s32 limit;
    s32 slot;
    s32 best;
    s32 i;
    s32 j;

    limit = 10000000;
    slot = 0;
    if (card_get_status() == 0) {
        if (card_read_save(&D_800A9300) != 0) {
            card_init_save(&D_800A9300);
            return;
        }
        best = -1;
        for (i = 0; i < 6; i++) {
            if (D_800A9300.unk_204[i] == 0 && best < D_800A9300.slots[i].unk_00 && D_800A9300.slots[i].unk_00 < limit) {
                slot = i;
                best = D_800A9300.slots[i].unk_00;
            }
        }
        if (best != -1) {
            for (j = 0; j < 7; j++) {
                D_801F9A44[j] = D_800A9300.slots[slot].unk_58[j];
            }
            for (j = 0; j < 3; j++) {
                D_801D8800[j] = D_800A9300.slots[slot].unk_46[j];
            }
            D_8007A694 = D_800A9300.slots[slot].unk_3E;
            D_801E2150 = D_800A9300.slots[slot].unk_40;
            D_801E1CB4 = D_800A9300.slots[slot].unk_42;
            D_8007A68A = D_800A9300.slots[slot].unk_44;
            D_8007A68C = D_800A9300.slots[slot].unk_68;
            D_801F9ABC = D_800A9300.slots[slot].unk_6A;
            D_8007A686 = D_800A9300.slots[slot].unk_6C;
            D_8007A688 = D_800A9300.slots[slot].unk_6E;
            D_8007A68E = D_800A9300.slots[slot].unk_70;
            D_8007A688 = D_800A6F3C[D_8007A68E * 2];
            D_8007A686 = D_800A6F3C[D_8007A68E * 2 + 1];
        }
    }
}

INCLUDE_RODATA("asm/overattr/nonmatchings/menu", D_800983F0);

void func_800A32CC(void) {
    func_8001F61C("LOADING PREVIOUSLY", 200, 90, 1, D_801F9AAC, D_8007ABCC, 0, 0x400);
    func_8001F61C("SAVED GAMES", 200, 120, 1, D_801F9AAC, D_8007ABCC, 0, 0x400);
}
