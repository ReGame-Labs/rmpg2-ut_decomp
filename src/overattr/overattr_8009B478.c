/* OVERLAYS/OVERATTR.BIN: the credits, the menus and the memory-card screens (config/overattr.yaml). */
#include "common.h"
#include "overattr.h"

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009B478);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009B598);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009B6DC);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009B7C4);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009B8A4);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009B980);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009BAA4);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009BB90);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009BC7C);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009BD0C);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009BD9C);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009BEB0);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009BF40);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009BF94);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009BFE8);

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

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009CD30);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009CE5C);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009CEC8);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009D0B0);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009D140);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009D20C);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009D31C);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009D42C);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009D504);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009D5E4);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009D6B0);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009D7B4);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009D948);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009DB38);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009DBFC);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009DCC0);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009DD3C);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009DE00);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009DEA8);

void func_8009DF60(void) {
    s32 i;

    for (i = 0x400; i < 0x4FF; i++) {
        func_8001E450(i & 0xFFFF);
    }
}

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009DF98);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009E114);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009E190);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009E238);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009E310);

void func_8009E3C0(s32 kind, s32 value) {
    GameObject *head;
    GameObject *obj;

    head = &D_801E28C0;
    obj = head->next;
    if (obj != head) {
        do {
            if (obj->kind == kind) {
                obj->unk_78 = value;
                obj->flags |= 0x500;
            }
            obj = obj->next;
        } while (obj != head);
    }
}

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009E40C);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009E4D4);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009E540);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009E5BC);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009E7D4);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009E8B8);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009EB74);

INCLUDE_RODATA("asm/overattr/nonmatchings/overattr_8009B478", D_80097F58);

INCLUDE_RODATA("asm/overattr/nonmatchings/overattr_8009B478", D_80098094);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009EE5C);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009F2F8);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009F554);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009F968);

INCLUDE_RODATA("asm/overattr/nonmatchings/overattr_8009B478", D_800980CC);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009F9E0);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009FB78);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009FC74);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009FEE4);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_8009FF38);

INCLUDE_RODATA("asm/overattr/nonmatchings/overattr_8009B478", D_800980E8);

INCLUDE_RODATA("asm/overattr/nonmatchings/overattr_8009B478", D_80098100);

INCLUDE_RODATA("asm/overattr/nonmatchings/overattr_8009B478", D_8009811C);

INCLUDE_RODATA("asm/overattr/nonmatchings/overattr_8009B478", D_80098128);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_800A0CC0);

INCLUDE_RODATA("asm/overattr/nonmatchings/overattr_8009B478", D_8009814C);

INCLUDE_RODATA("asm/overattr/nonmatchings/overattr_8009B478", D_80098164);

INCLUDE_RODATA("asm/overattr/nonmatchings/overattr_8009B478", jtbl_80098178);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_800A1258);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_800A1434);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_8009B478", func_800A1720);

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
        if (D_800A9300.unk_240[i].unk_00 == id) {
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
