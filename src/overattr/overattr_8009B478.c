/* OVERLAYS/OVERATTR.BIN: the credits, the menus and the memory-card screens (config/overattr.yaml). */
#include "common.h"
#include "overattr.h"
#include "psyq/libc2.h"

void func_8009B478(void) {
    GameObject *head;
    GameObject *obj;

    head = &D_801E28C0;
    switch (D_800A9888) {
    case 1:
        obj = head->next;
        if (obj != head) {
            do {
                if ((obj->flags & 0x100) && obj->colour != -1) {
                    if (obj->colour != 0) {
                        obj->colour -= 0x40404;
                    } else {
                        obj->colour = 0;
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
                if ((obj->flags & 0x100) && obj->colour != -1) {
                    if (obj->colour <= 0x80807F) {
                        obj->colour += 0x40404;
                    } else {
                        obj->colour = 0x808080;
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
/* 99.3 %: the movie line's text address is in s3, the original's s1 (s1/s2 hold the colour's and the cursor's %hi). */
void func_8009BFE8(void) {
    func_8009BF40(D_800A631E, D_801FA960);
    func_8001ECB4(D_800A6359, D_8007A684, 0);
    func_8001ECB4(D_800A6380, D_8007A686, 0);
    func_8001ECB4(D_800A63A3, D_8007A688, 0);
    func_8009BF94(&D_800A63A8.text[7], D_8007A692);
    func_8001E450(0x421);
    func_8001E450(0x422);
    func_8001E450(0x423);
    func_8001E450(0x424);
    func_8001E450(0x425);
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
INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009BFE8);
#endif

void func_8009C1AC(void) {
    func_800A0CC0();
}

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009C1CC);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009C5A4);

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

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009C828);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009CA68);

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

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009CEC8);

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
        func_8009E40C(D_800A92C0, D_800A92D0);
        D_800A9878 = 0;
    }
}

void func_8009D20C(void) {
    if ((D_800A9220 & 0x10) && D_801F9944 == 0) {
        D_801E2148 = 2;
        D_801D3780 = 5;
        func_8001EC74(D_800A92C0[D_800A92D0 + 2].kind, D_801D885C);
        func_8001F724(3);
        func_8009E40C(D_800A92C0, D_800A92D0);
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
        func_8009E40C(D_800A92C0, D_800A92D0);
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
        func_8009E40C(D_800A92C0, D_800A92D0);
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
        func_8009E40C(D_800A92C0, D_800A92D0);
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
        func_8009E40C(D_800A92C0, D_800A92D0);
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
        func_8009E40C(D_800A92C0, D_800A92D0);
    }
    for (i = 0; i < 5; i++) {
        D_800A6F48[i]->text[0] = 'B';
        D_800A9890[i] = 'B';
    }
    D_800A9890[5] = 0;
}

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009D7B4);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009D948);

void func_8009DB38(void) {
    if ((D_800A9220 & 0x1004010) && D_801F9944 == 0) {
        D_800A92D8 = D_800A71A0;
        D_800A9870 = 0;
        D_801E2148 = 6;
        D_801D3780 = 5;
        func_8001EC74(D_800A92C0[D_800A92D0 + 2].kind, D_801D885C);
        func_8001F724(3);
        func_8009E40C(D_800A92C0, D_800A92D0);
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
        func_8009E40C(D_800A92C0, D_800A92D0);
    }
}

void func_8009DCC0(void) {
    MenuRecord *menu;

    menu = D_800A92C0;
    if ((D_800A9220 & 0x1004010) && D_801F9944 == 0) {
        D_800A9800 = 1;
        D_800A92D8 = menu[0].sub;
        D_800A9870 = menu[0].kind;
        func_8001F724(3);
        func_8009E4D4();
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
        func_8009E40C(D_800A92C0, D_800A92D0);
    }
}

void func_8009DE00(void) {
    MenuRecord *menu;
    s32 i;

    menu = D_800A92C0;
    if ((D_800A9220 & 0x1004010) && D_801F9944 == 0) {
        D_800A9800 = 1;
        D_800A92D8 = menu[0].sub;
        D_800A9870 = menu[0].kind;
        func_8001F724(3);
        func_8009E4D4();
    }
    for (i = 0; i < 12; i++) {
        func_8009E3C0(0x400, 0x808080);
    }
}

void func_8009DEA8(void *list, s32 selected) {
    MenuRecord *menu;
    s32 i;

    menu = list;
    for (i = 2; i <= menu->unk_00 + 1; i++) {
        if (selected != i - 2) {
            func_8001E450(menu[i].kind);
        }
    }
    if (menu->sub != NULL) {
        i = menu->kind;
        func_8001E450(menu->sub[i + 2].kind);
    }
}

void func_8009DF60(void) {
    s32 i;

    for (i = 0x400; i < 0x4FF; i++) {
        func_8001E450(i);
    }
}

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009DF98);

s32 func_8009E114(s32 kind, s32 y) {
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

void func_8009E190(void *list, s32 selected, s32 lit, s32 normal) {
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

void func_8009E238(void *list, s32 lit, s32 normal) {
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

void func_8009E3C0(s32 kind, s32 value) {
    GameObject *head;
    GameObject *obj;

    head = &D_801E28C0;
    obj = head->next;
    if (obj != head) {
        do {
            if (obj->kind == kind) {
                obj->colour = value;
                obj->flags |= 0x500;
            }
            obj = obj->next;
        } while (obj != head);
    }
}

void func_8009E40C(void *list, s32 selected) {
    MenuRecord *menu;
    s32 i;

    menu = list;
    for (i = 2; i <= menu[0].unk_00 + 1; i++) {
        if (selected != i - 2) {
            func_8009E3C0(menu[i].kind, 0x808080);
        }
    }
    if (menu[0].sub != NULL) {
        i = menu[0].kind;
        func_8009E3C0(menu[0].sub[i + 2].kind, 0x808080);
    }
    D_800A9888 = 1;
}

void func_8009E4D4(void) {
    GameObject *head;
    GameObject *obj;

    head = &D_801E28C0;
    obj = head->next;
    if (obj != head) {
        do {
            if ((u32) (obj->kind - 0x400) < 0x100) {
                obj->colour = 0x808080;
                obj->flags |= 0x500;
            }
            obj = obj->next;
        } while (obj != head);
    }
    D_800A9888 = 1;
    D_801D3780 = 8;
}

void func_8009E540(MenuRecord *menu) {
    s32 i;

    for (i = 2; i <= menu[0].unk_00 + 1; i++) {
        func_8009E3C0(menu[i].kind, 0);
    }
    D_800A9888 = 2;
}

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009E5BC);

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
    *(D_801E28F4.obj + n) = D_800AA248.cur_obj;
    D_800AA248.cur_obj->unk_48 = (s32) D_800A74E4;
    D_800AA248.cur_obj->unk_4D = 0;
    D_800AA248.cur_obj->flags |= 0x400;
    D_800AA248.cur_obj = saved;
}

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009E8B8);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009EB74);

INCLUDE_RODATA("asm/overattr/nonmatchings/overattr_8009B478", D_80097F58);

INCLUDE_RODATA("asm/overattr/nonmatchings/overattr_8009B478", D_80098094);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009EE5C);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009F2F8);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009F554);

void func_8009F968(OverattrPlacement *p, s32 n, s32 color) {
    s32 i;
    OverattrPlacement *q;

    D_801F9AC8.w = 0;
    D_801F9ACC = 0;
    q = p;
    for (i = 0; i < n; i++) {
        func_80099138(q++)->colour = color;
    }
}

void func_8009F9E0(void) {
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
    D_801D373C[0]->colour = 0x808080;
    D_800AA248.new_def = def = func_8001D110();
    def->id = 0x4F00280A;
    def->pos_x.w = 0x10E0000;
    def->pos_y.w = 0xD70000;
    def->flags = 0x1FE;
    def->unk_06 |= 0x20;
    D_801D373C[1] = func_8001DCB4();
    D_801D373C[1]->kind = 0x550;
    D_801D373C[1]->colour = 0x808080;
    func_8001F61C("SELECT", 0x4B, 0xD6, 1, 0x46, D_8007AD4C, 1, 0x550);
    func_8001F61C("BACK", 0x127, 0xD6, 1, 0x46, D_8007AD4C, 1, 0x550);
    head = &D_801E28C0;
    obj = head->next;
    if (obj != head) {
        do {
            if (obj->kind == 0x550) {
                obj->colour = 0x808080;
            }
            obj = obj->next;
        } while (obj != head);
    }
}

void func_8009FB78(void) {
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
    D_801D373C[0]->colour = 0x808080;
    func_8001F61C("SELECT", 0x4B, 0xD6, 1, 0x46, D_8007AD4C, 1, 0x550);
    head = &D_801E28C0;
    obj = head->next;
    if (obj != head) {
        do {
            if (obj->kind == 0x550) {
                obj->colour = 0x808080;
            }
            obj = obj->next;
        } while (obj != head);
    }
}

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009FC74);

void func_8009FEE4(void) {
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

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009FF38);

INCLUDE_RODATA("asm/overattr/nonmatchings/overattr_8009B478", D_800980E8);

INCLUDE_RODATA("asm/overattr/nonmatchings/overattr_8009B478", D_80098100);

INCLUDE_RODATA("asm/overattr/nonmatchings/overattr_8009B478", D_8009811C);

INCLUDE_RODATA("asm/overattr/nonmatchings/overattr_8009B478", D_80098128);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_800A0CC0);

INCLUDE_RODATA("asm/overattr/nonmatchings/overattr_8009B478", D_8009814C);

INCLUDE_RODATA("asm/overattr/nonmatchings/overattr_8009B478", D_80098164);

INCLUDE_RODATA("asm/overattr/nonmatchings/overattr_8009B478", jtbl_80098178);

#ifdef NON_MATCHING
/* 81.7 %: the city names' address is hoisted into s7 (a frame 8 bytes larger); the original reloads it. */
s32 func_800A1258(void) {
    char buf[0x18];
    s32 limit;
    s32 n;
    s32 slot;
    s32 best;
    s32 y;
    s32 i;
    s32 count;

    limit = 10000000;
    n = 0;
    slot = 0;
    y = 60;
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
        for (i = 0; i < 7; i++) {
            if (D_800A9300.slots[slot].unk_49[i] != 0) {
                count++;
            }
        }
        D_800A9830[n] = slot;
        D_800A9820[n] = 0x20;
        D_800A9810[n] = y;
        y += 23;
        sprintf(buf, "%s   %dP", D_8007C704[D_800A9300.slots[slot].city], count);
        func_8001F61C(buf, D_800A9820[n], D_800A9810[n], 1, D_801F9AAC, D_8007AD4C, 1, 0x450 + n);
        n++;
        limit = best;
    }
}
#else
INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_800A1258);
#endif

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_800A1434);

void func_800A1720(void) {
    D_801D885C = 0x44;
    if (D_800A9898 == 1) {
        D_800A9898 = 0;
        func_8001E8C0(0x400, -0x100);
    }
    switch (D_800A98B8) {
    case 0:
        func_800A1804();
        break;
    case 6:
        func_800A1B9C();
        break;
    case 1:
        func_800A2138();
        break;
    case 2:
        func_800A28DC();
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

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_800A1804);

s32 func_800A1B60(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (D_800A9300.unk_204[i] != 0) {
            return i;
        }
    }
    return -1;
}

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_800A1B9C);

INCLUDE_RODATA("asm/overattr/nonmatchings/overattr_8009B478", D_80098260);

INCLUDE_RODATA("asm/overattr/nonmatchings/overattr_8009B478", D_80098264);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_800A1F8C);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_800A2138);

s32 func_800A28A0(s32 id) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (D_800A9300.slots[i].unk_00 == id) {
            return i;
        }
    }
    return -1;
}

INCLUDE_RODATA("asm/overattr/nonmatchings/overattr_8009B478", D_8009833C);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_800A28DC);

void func_800A309C(void) {
    D_801D3780 += 1;
}

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_800A30B4);

INCLUDE_RODATA("asm/overattr/nonmatchings/overattr_8009B478", D_800983F0);

void func_800A32CC(void) {
    func_8001F61C("LOADING PREVIOUSLY", 200, 90, 1, D_801F9AAC, D_8007ABCC, 0, 0x400);
    func_8001F61C("SAVED GAMES", 200, 120, 1, D_801F9AAC, D_8007ABCC, 0, 0x400);
}
