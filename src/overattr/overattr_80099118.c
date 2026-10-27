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
    p = &D_801E28F4.unk_00;
    do {
        *p++ = NULL;
    } while (--n != 0);
    D_801FA88C = 0;
}

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_80099118", func_800991EC);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_80099118", func_8009951C);

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_80099118", func_800996CC);

void func_800999F8(u32 which) {
    switch (which) {
    case 0:
        D_801E28F4.obj[8]->pos_y.w = 0x180000;
        D_801E28F4.obj[9]->pos_y.w = 0x1180000;
        D_801E28F4.obj[10]->pos_y.w = 0x1180000;
        break;
    case 1:
        D_801E28F4.obj[8]->pos_y.w = 0x1180000;
        D_801E28F4.obj[9]->pos_y.w = 0x190000;
        D_801E28F4.obj[10]->pos_y.w = 0x1180000;
        break;
    case 2:
        D_801E28F4.obj[8]->pos_y.w = 0x1180000;
        D_801E28F4.obj[9]->pos_y.w = 0x1180000;
        D_801E28F4.obj[10]->pos_y.w = 0x180000;
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

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_80099118", func_8009AE40);

#ifdef NON_MATCHING
/* 98.4 %: the counter and the pointer swap s0/s1. */
void func_8009B0F0(void) {
    s32 i;
    OverattrPlacement *p;

    func_8001A420();
    i = 0;
    func_80017B24();
    func_8001AC18(0xA, 0x28);
    D_801D3D7C = 0;
    SetDispMask(1);
    p = D_800A4430;
    do {
        func_80099138(p++);
        i++;
    } while (i < 4);
}
#else
INCLUDE_ASM("asm/overattr/nonmatchings/overattr_80099118", func_8009B0F0);
#endif

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

INCLUDE_ASM("asm/overattr/nonmatchings/overattr_80099118", func_8009B23C);
