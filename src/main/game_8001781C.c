/* The first file of the game's code: main and the functions up to func_8002A308.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "game_8001781C.h"

/* decls:begin */
extern s16 D_8007A692;
extern u16 D_8007A696;
extern s16 D_8007A698;
extern u16 D_8007A7D4;
extern u8 D_8007ED64[];
extern u8 D_8007EFA4[];
extern u8 D_8007F1E4[];
extern u8 D_80083414[];
extern u8 D_80083654[];
extern u8 D_800895A8[];
extern u8 D_800897FC[];
extern Sprite *D_800AA268;
extern GameState D_800AA248;
extern s16 D_800AA2C2;
extern s16 D_800AA2D4;
extern s32 D_800AA2DC;
extern s16 D_800AA2EC;
extern s32 D_800AA944;
extern s32 D_800AA948;
extern u16 D_800AFB74;
extern s32 D_801C51C0;
extern s32 D_801C51C4;
extern u16 D_801CA42C;
extern s16 D_801CA45C;
extern s16 D_801CA468;
extern u16 D_801D36FC;
extern s16 D_801D3704;
extern u16 D_801D3758;
extern s32 D_801D375C;
extern s32 D_801D3760;
extern u16 D_801D3768;
extern s16 D_801D3770;
extern s16 D_801D3778;
extern u16 D_801D3780;
extern s16 D_801D3D6C;
extern s16 D_801D3D8C;
extern u16 D_801D3DC6;
extern Sprite *D_801D8584;
extern s16 D_801D8708;
extern s16 D_801D870C;
extern u16 D_801D8720;
extern s16 D_801D8728;
extern s16 D_801D8738;
extern u16 D_801D8740;
extern s16 D_801D8744;
extern s32 D_801D8754;
extern Sprite *D_801D8764;
extern u16 D_801D87A0;
extern s16 D_801D87FC;
extern s8 D_801D8800[];
extern s16 D_801D8848;
extern s16 D_801D8854;
extern s16 D_801E0D4C;
extern s16 D_801E0D64;
extern s32 D_801E0D6C;
extern u8 D_801E0D98[];
extern void *D_801E1C78;
extern Sprite *D_801E1C7C;
extern s16 D_801E1CA4;
extern s16 D_801E1CAC;
extern u16 D_801E1CB0;
extern s16 D_801E1CB4;
extern s16 D_801E1E18;
extern s16 D_801E1E40;
extern s16 D_801E2150;
extern u8 D_801E2894[];
extern void * D_801E28C0[];
extern s16 D_801E28DC;
extern s16 D_801E2994;
extern s16 D_801E29A4;
extern u8 D_801E29A8[];
extern s16 D_801E29B4;
extern s16 D_801E29BC;
extern u16 D_801E2A50;
extern s16 D_801E2A68;
extern s16 D_801F9918;
extern u16 D_801F9950;
extern u16 D_801F9954;
extern s16 D_801F9958;
extern u16 D_801F995C;
extern s32 D_801F9A30;
extern u16 D_801F9A40;
extern u16 D_801F9ACE;
extern s16 D_801F9AD0;
extern s16 D_801FA7E8[];
extern s16 D_801FA938;
extern s16 D_801FA960;
extern s16 D_801FA964;
extern s32 D_801FA9A4;
extern s16 D_801FA9B8;
extern s16 D_801FAC94;
extern s16 D_801FAF6C;
extern s16 D_801FAF6E;
extern s16 D_801FAF70;
extern s16 D_801FB18C;
void DrawSync(s32);
void MemCardInit(s32);
void MemCardStart(void);
void SetDispMask(s32);
void VSync(s32);
void cdload_load_overlay(s32);
void func_800193B8(void);
void func_80019764(void);
void func_80019890(void);
void func_80019984(s32);
void func_8001A1C8(void);
void func_8001A474(void);
void func_8001A554(s32, void *);
void func_8001B350();
void func_8001B694(void);
void func_8001BA98(void);
void func_8001C404(void);
void func_8001D184(void);
void func_8001D7D0(void);
s32 func_8001D998(void *);
void func_8001DF98(void);
void func_8001E0AC(void);
void func_8001E450(s32);
void func_8001E4B0(s32);
void func_8001E664(void *, s32);
void func_8001E700(void);
void func_8001E7C8(Sprite *);
s16 func_8001EA10(void);
s32 func_8001EAC4(s32);
void func_8001F2B0(void);
void func_8001F358(void);
void func_8001F39C(void);
void func_8001F6B4(void);
void func_8001F7F8(s32);
void func_8001F848(void);
void func_8001F9DC(void);
void func_800205AC(void);
void func_80022EC0(void);
void func_80023080(s32);
void func_800242A8(void);
void func_80024530(s32, void *);
void func_8002469C(s32, s32, s32);
void func_800256CC(SpriteSlots *);
s32 func_80025C08(void *);
void func_80025E68(void);
void func_8002A72C(void);
void func_8002AF28(void);
void func_800377B4(void);
void func_8003C894(s32);
void func_80044D34(void);
void func_80057DD8(void);
void func_8005E3CC(void);
s16 func_8005E5C8(void);
void func_8005E60C(void);
void func_80060524(void);
void func_80060DCC(void);
void func_80062D88(u8);
void func_80062DA8(u8);
void func_80062DEC(s32, s32, s32);
void func_80062E24(s32);
void func_80062E44(void);
void func_80062EA8(s32);
void func_800631B4(void);
void func_80063214(void);
void func_8009FC74(void);
s32 func_8009FF38(void);
void func_800A9890(s16);
void (*func_80026DE4(void *))(void *);

void func_80017A40(void);
void func_80017AC8(void);
void func_80017B88(void);
void func_80017B90(void);
void func_80018008(void);
void func_80018CB0(void);
void func_80018CD0(void);
void func_80018CF0(void);
void func_80018D10(s16 arg0);
void func_80018D38(void);
void func_80018D84(void);
void func_80019ABC(s32 arg0);
void func_80019ADC(void);
void func_8001A420(void);
void func_8001A454(void);
void func_8001B054(Sprite *arg0);
void func_8001B098(Sprite *arg0);
void func_8001B5E8(s32 arg0);
void func_8001B7F4(void);
void func_8001B848(void);
void func_8001BB60(void);
void func_8001BB68(Sprite *arg0);
void func_8001BB88(Sprite *arg0);
void func_8001BBA8(void);
s16 func_8001BDBC(void);
void func_8001BECC(void);
void func_8001C3C4(void);
void func_8001C77C(void);
void func_8001C784(void);
void func_8001C834(void);
s32 func_8001CFAC(void);
void func_8001CFB4(void);
void func_8001CFE4(void);
void func_8001D018(void);
void func_8001D084(void);
void func_8001D0C0(void);
void func_8001D17C(void);
void func_8001D1C0(void);
void func_8001D77C(void);
void func_8001D7A8(void);
void func_8001D8E8(void);
s32 func_8001D950(void);
s32 func_8001D974(void);
s32 func_8001E2B8(Sprite *arg0);
void func_8001E528(Sprite *arg0);
void func_8001E638(Unk1E638 *arg0, s32 arg1, s32 *arg2);
void func_8001E698(Sprite *arg0, s32 arg1);
void func_8001E6CC(Sprite *arg0);
void func_8001E758(void);
void func_8001E7A0(void);
void func_8001E94C(s32 arg0, s32 arg1, Sprite *arg2);
void func_8001E978(void);
void func_8001E980(void);
void func_8001E9C4(s16 arg0, s16 arg1);
s32 func_8001EA78(void);
s32 func_8001EB10(s32 arg0, s32 arg1);
void func_8001EB3C(void);
void func_8001ED54(void *arg0);
void func_8001ED7C(void);
void func_8001EDB0(void);
void func_8001F268(void);
void func_8001F4EC(void);
void func_8001F6E4(void);
void func_8001F704(void);
void func_8001F760(void);
void func_8001F7CC(s32 arg0, s32 arg1);
void func_8001F9BC(void);
void func_80020FC8(Sprite *arg0);
void func_80021034(void);
void func_8002107C(void);
void func_80022D58(Unk22D58 *arg0);
void func_80023064(s32 arg0);
void func_800232AC(s32 arg0);
void func_800233E0(Unk233E0 *arg0);
void func_80023F64(s32 arg0);
void func_800240F0(s32 arg0);
void func_8002423C(Sprite *arg0);
void func_80024280(void);
void func_800242A0(void);
void func_80024508(Sprite *arg0);
void func_800245F8(void);
void func_80024954(void);
void func_8002495C(void);
void func_80024964(void);
void func_8002496C(void);
s32 func_80024974(s32 arg0);
void func_8002497C(void);
void func_80024AA0(void);
void func_8002546C(void);
void func_800255E0(SpriteSlots *arg0);
void func_80025648(SpriteSlots *arg0);
void func_800256B0(SpriteSlots *arg0);
void func_8002575C(SpriteSlots *arg0);
void func_800257C4(SpriteSlots *arg0);
void func_800257F0(SpriteSlots *arg0);
void func_80025848(SpriteSlots *arg0);
void func_80025898(SpriteSlots *arg0);
void func_80025B10(void);
void func_80026BC4(Monster *arg0);
void func_80026CFC(Monster *arg0);
void func_80026E0C(Monster *arg0);
void func_80026F58(Monster *arg0);
void func_80027FC8(void);
void func_80028140(s32 arg0, Monster *arg1, s16 arg2);
void func_800284D8(void);
void func_80028508(void);
void func_8002994C(void);
void func_80029B54(void);
void func_80029CF8(void);
s32 func_8002A300(void);
u16 func_8002A308(void);
/* decls:end */

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", main);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80017964);

void func_80017A40(void) {
    D_801E1CB4 = 0x2E;
    D_801E2150 = 0x55;
    D_801E1CA4 = 0;
    D_801E2994 = 0;
    D_801FA938 = 0;
    D_801D3770 = 0;
    D_800AA2EC = 0x45;
    func_80062DA8((u8) D_801E1CB4);
    func_80062D88((u8) D_801E2150);
    D_801D8800[0] = 0;
    D_801D8800[1] = 0;
    D_801D8800[2] = 0;
}

void func_80017AC8(void) {
    D_801D8708 = 0;
    D_801F9AD0 = 0;
    D_800AA2D4 = 0;
    D_801FA9A4 = 0;
    func_8001EB3C();
    D_801D3D6C = 0;
    func_80018D10(0);
    func_80017B90();
    func_8001E980();
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80017B24);

void func_80017B88(void) {
}

void func_80017B90(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80017B98);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80017C04);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80017C80);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80017D8C);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80017F14);

void func_80018008(void) {
    func_8001E450(0x7FE);
    D_8007A698 = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001802C);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800180E4);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800181D0);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001828C);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80018BD4);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80018C14);

void func_80018CB0(void) {
    func_800193B8();
}

void func_80018CD0(void) {
    func_80019764();
}

void func_80018CF0(void) {
    func_80019890();
}

void func_80018D10(s16 arg0) {
    D_801F9A40 = arg0;
    func_80019ABC(arg0 & 0xFFFF);
}

void func_80018D38(void) {
    s32 var_a0;

    var_a0 = 0;
    if ((D_801D36FC == 0x150) || (D_801D36FC == 0x220) || (D_801D36FC == 0x240)) {
        var_a0 = 1;
    }
    func_80019984(var_a0);
}

void func_80018D84(void) {
    DrawSync(0);
    VSync(0);
    MemCardInit(0);
    MemCardStart();
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80018DBC);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80019268);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800192A0);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800193B8);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80019764);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80019890);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80019920);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80019984);

void func_80019ABC(s32 arg0) {
    SetDispMask(arg0 & 0xFFFF);
}

void func_80019ADC(void) {
    memset(D_801E1C78, 0, 0x10000);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80019B08);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80019DAC);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001A0A0);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001A0E4);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001A1C8);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001A220);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001A3AC);

void func_8001A420(void) {
    D_800AA944 = D_801C51C0;
    D_800AA948 = D_801C51C4;
    D_800AFB74 = D_801CA42C;
}

void func_8001A454(void) {
    D_800AFB74 = 0;
    D_800AA944 = 0;
    D_800AA948 = 0xF0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001A474);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001A514);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001A534);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001A554);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001A784);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001A820);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001A848);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001A870);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001AA4C);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001AB30);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001AC18);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001AD1C);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001AE70);

void func_8001B054(Sprite *arg0) {
    u16 temp_v1;

    temp_v1 = arg0->unk_6C | 0x80;
    arg0->unk_6C = temp_v1;
    if (temp_v1 & 0x400) {
        arg0->unk_6C = (u16) (temp_v1 & 0xFBFF);
        func_8001B350(arg0->unk_6E, arg0);
    }
}

void func_8001B098(Sprite *arg0) {
    u16 temp_v0;

    temp_v0 = arg0->unk_6C;
    arg0->unk_6C = (u16) (temp_v0 & 0xFF7F);
    if (!(temp_v0 & 0x408)) {
        func_8001A554(arg0->unk_38, arg0);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001B0D8);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001B128);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001B178);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001B350);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001B3C4);

void func_8001B5E8(s32 arg0) {
    func_8001D17C();
    func_8001E758();
    func_8001D184();
    func_80018D10(1);
    D_801D8754 = arg0;
    func_8001ED54(&D_800895A8);
    func_8001D8E8();
    func_80018CF0();
    func_80018CD0();
    func_8001D8E8();
    func_80018CF0();
    func_80018CD0();
loop_1:
    goto loop_1;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001B660);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001B694);

void func_8001B7F4(void) {
    u16 temp_v1;

    func_8001DF98();
    if (D_801D3DC6 == 0) {
        func_8001B694();
        func_800205AC();
    }
    temp_v1 = D_801F9954;
    D_801F9954 = 0;
    D_801F9950 = temp_v1;
}

void func_8001B848(void) {
    D_801F9950 = 1;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001B858);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001BA98);

void func_8001BB60(void) {
}

void func_8001BB68(Sprite *arg0) {
    if (arg0 != NULL) {
        arg0->unk_1A = (u16) (arg0->unk_1A | 0xC000);
    }
}

void func_8001BB88(Sprite *arg0) {
    if (arg0 != NULL) {
        arg0->unk_1A = (u16) (arg0->unk_1A & 0x3FFF);
    }
}

void func_8001BBA8(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001BBB0);

s16 func_8001BDBC(void) {
    return D_801CA468;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001BDCC);

void func_8001BECC(void) {
    s16 temp_v0;

    if (D_801CA45C == 0) {
        D_801FA9B8 = 0;
        cdload_load_overlay(0);
        func_80062EA8(2);
        D_801CA45C = 1;
    }
    if (((u32) ((u16) D_801CA45C - 1) < 2U) || ((s16) (u16) D_801CA45C == 5)) {
        func_8009FC74();
        goto block_10;
    }
    if ((s16) (u16) D_801CA45C != 3) {
        if (((s16) (u16) D_801CA45C == 4) && (func_8009FF38() != 0)) {
            func_8001D184();
            cdload_load_overlay(1);
            func_800A9890(D_8007A692);
            D_801CA45C = 0;
            return;
        }
        goto block_10;
    }
block_10:
    if (D_801D3780 == 4) {
        if (D_801D3778 == 2) {
            D_800AA2EC = 0x45;
            func_8001ED54(&D_800897FC);
        }
        temp_v0 = (u16) D_801D3778 - 1;
        D_801D3778 = temp_v0;
        if ((temp_v0 << 0x10) != 0) {
            D_800AA2C2 = 0;
            return;
        }
        D_801D87FC = 0;
        D_801E29BC = 2;
        D_801D3780 = 0;
        D_801D36FC = 0x140;
        goto block_16;
    }
block_16:
    D_800AA2DC = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001C02C);

void func_8001C3C4(void) {
    func_8001C404();
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001C3E4);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001C404);

void func_8001C77C(void) {
}

void func_8001C784(void) {
    D_801D3758 += 1;
    func_8001CFE4();
    func_80025E68();
    func_8002A72C();
    func_8002AF28();
    func_8005E3CC();
    func_8005E60C();
    func_80060524();
    func_80060DCC();
    if (D_801D36FC != 0x120) {
        func_8001BA98();
        func_80025B10();
        if (D_801E0D4C != 0) {
            D_801D3780 = 0;
            D_801E0D4C = 0;
            D_801D36FC = 0x170;
            func_80062E44();
        }
    }
}

void func_8001C834(void) {
}

INCLUDE_RODATA("asm/main/nonmatchings/game_8001781C", D_800105C8);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001C83C);

s32 func_8001CFAC(void) {
    return 0x200;
}

void func_8001CFB4(void) {
    if ((func_8001BDBC() << 0x10) != 0) {
        D_801D87A0 = 0;
    }
}

void func_8001CFE4(void) {
    if ((func_8001BDBC() << 0x10) != 0) {
        D_801D87A0 = 0x28;
    }
}

void func_8001D018(void) {
    func_8001CFB4();
    func_8001D17C();
    func_8001E758();
    func_8001D0C0();
    func_80024AA0();
    D_801D3780 = 0;
    D_801E29BC = 0;
    D_801E0D64 = 0;
    func_8001EB3C();
    func_8001D184();
    D_801D36FC = 0x110;
}

void func_8001D084(void) {
    if (D_8007A7D4 & 1) {
        memset(&D_801E0D98, 0, 0xEE0);
    }
}

void func_8001D0C0(void) {
    D_801D375C = 0;
    D_801D3760 = 0;
    func_80017AC8();
    D_801FA7E8[0] = 0;
    D_801FA7E8[1] = 0;
    D_801D3D6C = 1;
    func_80018D10(1);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001D110);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001D15C);

void func_8001D17C(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001D184);

void func_8001D1C0(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001D1C8);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001D28C);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001D4B8);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001D598);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001D6A0);

void func_8001D77C(void) {
    D_801D3780 = 0;
    func_8001D7A8();
    func_8001D184();
}

void func_8001D7A8(void) {
    func_8001F6B4();
    func_8001D7D0();
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001D7D0);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001D844);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001D878);

void func_8001D8E8(void) {
    s32 temp_s0;

    if ((D_801F9A40 != 0) && (D_801F995C == 0)) {
        D_801E29B4 = 0;
        D_801D8744 = 0;
        temp_s0 = func_8001D950();
        D_801E29B4 = temp_s0 + func_8001D974();
        func_8001F848();
    }
}

s32 func_8001D950(void) {
    return func_8001D998(&D_801E28C0) & 0xFFFF;
}

s32 func_8001D974(void) {
    return func_8001D998(&D_801E29A8) & 0xFFFF;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001D998);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001DCB4);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001DF98);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001E010);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001E0AC);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001E174);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001E204);

s32 func_8001E2B8(Sprite *arg0) {
    memset(arg0->unk_8C, 0, 0x40);
    arg0->unk_60 = 0;
    D_800AA2C2 = 0;
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001E2F8);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001E39C);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001E450);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001E4B0);

void func_8001E528(Sprite *arg0) {
    if (arg0->unk_6C & 0x400) {
        func_8001B350(arg0->unk_6E);
    }
    D_801D3768 += 1;
    if (D_801D8764 != NULL) {
        D_801D8764->unk_0 = arg0;
    } else {
        D_801E1C7C = arg0;
    }
    D_801D8764 = arg0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001E59C);

void func_8001E638(Unk1E638 *arg0, s32 arg1, s32 *arg2) {
    *arg2 = arg0->unk_8;
    func_8001E664(&arg0->unk_4, arg1 & 0xFFFF);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001E664);

void func_8001E698(Sprite *arg0, s32 arg1) {
    arg0->unk_44 = arg1;
    arg0->unk_48 = arg1;
    arg0->unk_4D = 0;
    arg0->unk_22 = (u16) (arg0->unk_22 | 0x800);
    func_8001E6CC(arg0);
}

void func_8001E6CC(Sprite *arg0) {
    if (!(arg0->unk_6C & 0x4000)) {
        func_8001E700();
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001E700);

void func_8001E758(void) {
    if (D_801D8584 != 0) {
        do {
            func_8001E7C8(D_801D8584);
        } while (D_801D8584 != 0);
    }
}

void func_8001E7A0(void) {
    func_8001E7C8(D_800AA268);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001E7C8);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001E878);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001E8C0);

void func_8001E94C(s32 arg0, s32 arg1, Sprite *arg2) {
    SpriteImage *temp_v1;

    temp_v1 = arg2->unk_34;
    arg2->unk_28 = (s16) (arg0 - temp_v1->unk_8);
    arg2->unk_2A = (s16) (arg1 - temp_v1->unk_A);
}

void func_8001E978(void) {
}

void func_8001E980(void) {
    func_8001A1C8();
    func_8001A474();
    func_8002495C();
    func_80024954();
    D_801D3D6C = 0;
    func_8001E0AC();
}

void func_8001E9C4(s16 arg0, s16 arg1) {
    D_801FAF70 = arg0;
    D_801FAF6C = arg1;
    D_801FAF6E = (arg0 * arg1) / 3;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001EA10);

s32 func_8001EA78(void) {
    s16 temp_s0;
    s32 temp_lo;

    temp_s0 = func_8001EA10();
    temp_lo = temp_s0 * func_8001EA10();
    D_801E0D6C = temp_lo;
    return temp_lo;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001EAC4);

s32 func_8001EB10(s32 arg0, s32 arg1) {
    return arg1 + func_8001EAC4(arg0 - arg1);
}

void func_8001EB3C(void) {
    s32 temp_s1;

    temp_s1 = D_801FA9A4;
    D_801FA9A4 = 0;
    func_80018CD0();
    func_80018CF0();
    func_80018CD0();
    func_80018CF0();
    func_80018CD0();
    func_80018CF0();
    D_801FA9A4 = temp_s1;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001EB9C);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001EC74);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001ECB4);

void func_8001ED54(void *arg0) {
    func_8001F39C();
    func_8001ED7C();
}

extern s32 (*D_801D858C)();

void func_8001ED7C(void) {
    func_8001F2B0();
    D_801D858C();
}

extern s32 (*D_801D858C)();

void func_8001EDB0(void) {
    func_8001F358();
    D_801D858C();
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001EDE4);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001EE24);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001EE60);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001EEA0);

void func_8001F268(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001F270);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001F2B0);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001F358);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001F39C);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001F400);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001F464);

void func_8001F4EC(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001F4F4);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001F50C);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001F61C);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001F6B4);

void func_8001F6E4(void) {
    func_800631B4();
}

void func_8001F704(void) {
    func_80063214();
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001F724);

void func_8001F760(void) {
    func_8001F7F8(2);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001F780);

void func_8001F7CC(s32 arg0, s32 arg1) {
    func_80062DEC(arg1 & 0xFFFF, arg0 & 0xFFFF, 0);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001F7F8);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001F848);

void func_8001F9BC(void) {
    func_8001F9DC();
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001F9DC);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800205AC);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80020704);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8002075C);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80020AF4);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80020BA0);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80020CE4);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80020D20);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80020DDC);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80020EDC);

void func_80020FC8(Sprite *arg0) {
    s32 temp_a0;

    temp_a0 = arg0->unk_50;
    if (temp_a0 != 0) {
        func_8001E4B0(temp_a0);
        arg0->unk_50 = 0;
    }
    if (D_801E1CB0 == 0) {
        if (D_801D8740 != 0) {
            arg0->unk_8 = 0x64;
        }
        func_800242A8();
    }
}

void func_80021034(void) {
    if (D_8007A696 & 4) {
        func_80062E24(4);
        D_8007A696 &= 0xFFFB;
    }
}

void func_8002107C(void) {
    if (!(D_8007A696 & 4)) {
        func_8001F7CC(0x64, 4);
        D_8007A696 |= 4;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800210C8);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800211F4);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80021384);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80021418);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800214D8);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800215C0);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80021644);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800216C8);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8002180C);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80021A80);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80021ACC);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80021B94);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80021C5C);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80021D24);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80021DA8);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80021FDC);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800220D0);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800221BC);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800222E8);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8002235C);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80022490);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80022578);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80022640);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80022744);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80022814);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80022AC8);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80022B64);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80022BD8);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80022C68);

void func_80022D58(Unk22D58 *arg0) {
    if (arg0->unk_C != 0) {
        arg0->unk_A = 6;
        func_80022EC0();
        arg0->unk_2A = 1;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80022D98);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80022E58);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80022EC0);

void func_80023064(s32 arg0) {
    D_800AA268->unk_1A = (s16) (D_801F9ACE + arg0);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80023080);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80023114);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800231E4);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8002326C);

void func_800232AC(s32 arg0) {
    s32 var_a0;

    var_a0 = arg0;
    if (D_800AA268->unk_22 & 0x10) {
        var_a0 = -var_a0;
    }
    D_800AA268->unk_C = var_a0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800232D8);

void func_800233E0(Unk233E0 *arg0) {
    s16 var_v0;
    Monster *temp_v0;
    Sprite *temp_v1;

    temp_v0 = arg0->unk_10;
    if (temp_v0 != NULL) {
        temp_v1 = temp_v0->unk_68;
        if (temp_v1 == NULL) {
            func_800377B4();
            return;
        }
        arg0->unk_28 = (s16) (temp_v1->unk_1A - 0x1E);
        arg0->unk_3C = (u16) temp_v1->unk_22;
        if (temp_v1->unk_22 & 0x10) {
            var_v0 = temp_v1->unk_16 - 1;
        } else {
            var_v0 = temp_v1->unk_16 + 0x10;
        }
        arg0->unk_26 = var_v0;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80023474);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80023620);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80023764);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800239F4);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80023AC0);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80023B20);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80023C58);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80023CB8);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80023CFC);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80023E30);

void func_80023F64(s32 arg0) {
    if (D_800AA268->unk_6C & 0x80) {
        func_800242A0();
        func_80023080(arg0);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80023FAC);

void func_800240F0(s32 arg0) {
    if (D_800AA268->unk_6C & 0x80) {
        func_800242A0();
        func_80023080(arg0);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80024138);

void func_8002423C(Sprite *arg0) {
    s16 temp_v1;
    s32 var_a0;

    temp_v1 = arg0->unk_24;
    if (temp_v1 != 3) {
        var_a0 = 1;
        if (temp_v1 != 0) {
            var_a0 = 4;
            if (temp_v1 == 1) {
                var_a0 = 2;
            }
        }
        D_801E2A50 |= var_a0;
    }
}

void func_80024280(void) {
    func_80044D34();
}

void func_800242A0(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800242A8);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800242D8);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8002439C);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80024418);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800244A8);

void func_80024508(Sprite *arg0) {
    func_80024530(arg0->unk_50, arg0);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80024530);

void func_800245F8(void) {
    func_8002469C(func_80025C08(&D_8007EFA4), 0x520, 0x100);
    func_8002469C(func_80025C08(&D_8007ED64), 0x500, 0x200);
    func_8002469C(func_80025C08(&D_8007F1E4), 0x510, 0x199);
    func_8002469C(func_80025C08(&D_80083414), 0x540, 0x300);
    func_8002469C(func_80025C08(&D_80083654), 0x714, 0x300);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8002469C);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800247E4);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8002488C);

void func_80024954(void) {
}

void func_8002495C(void) {
}

void func_80024964(void) {
}

void func_8002496C(void) {
}

s32 func_80024974(s32 arg0) {
    return arg0;
}

void func_8002497C(void) {
    D_801E29A4 = 0;
    D_801D870C = 0;
    D_801D8738 = 0;
    D_801FAC94 = 0;
    D_801F9958 = 0;
    D_801F9918 = 0;
    D_801E2A68 = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800249B8);

void func_80024AA0(void) {
    D_801E1CAC = 0;
    D_801FA960 = 0;
    D_801E1E18 = 0;
    D_801FA964 = 0;
    D_801D8854 = 0;
    D_801D8728 = 0;
    D_801E28DC = 0;
    D_801D3704 = 0;
    D_801D8848 = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80024AEC);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80024BB4);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80024C08);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80024C2C);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80024E08);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8002503C);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80025124);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800252CC);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800253F0);

void func_8002546C(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80025474);

void func_800255E0(SpriteSlots *arg0) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;

    temp_a0 = arg0->unk_C;
    if (temp_a0 != 0) {
        func_8001E4B0(temp_a0);
    }
    temp_a0_2 = arg0->unk_24;
    if (temp_a0_2 != 0) {
        func_8001E4B0(temp_a0_2);
    }
    temp_a0_3 = arg0->unk_3C;
    if (temp_a0_3 != 0) {
        func_8001E4B0(temp_a0_3);
    }
}

void func_80025648(SpriteSlots *arg0) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;

    temp_a0 = arg0->unk_1C;
    if (temp_a0 != 0) {
        func_8001E4B0(temp_a0);
    }
    temp_a0_2 = arg0->unk_34;
    if (temp_a0_2 != 0) {
        func_8001E4B0(temp_a0_2);
    }
    temp_a0_3 = arg0->unk_4C;
    if (temp_a0_3 != 0) {
        func_8001E4B0(temp_a0_3);
    }
}

void func_800256B0(SpriteSlots *arg0) {
    arg0->unk_C = 0;
    arg0->unk_1C = 0;
    arg0->unk_24 = 0;
    arg0->unk_34 = 0;
    arg0->unk_3C = 0;
    arg0->unk_4C = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800256CC);

void func_8002575C(SpriteSlots *arg0) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;

    temp_a0 = arg0->unk_18;
    if (temp_a0 != 0) {
        func_8003C894(temp_a0);
    }
    temp_a0_2 = arg0->unk_30;
    if (temp_a0_2 != 0) {
        func_8003C894(temp_a0_2);
    }
    temp_a0_3 = arg0->unk_48;
    if (temp_a0_3 != 0) {
        func_8003C894(temp_a0_3);
    }
}

void func_800257C4(SpriteSlots *arg0) {
    func_800255E0(arg0);
    func_80025648(arg0);
}

void func_800257F0(SpriteSlots *arg0) {
    s32 temp_a0;

    temp_a0 = arg0->unk_0;
    if (temp_a0 != 0) {
        func_8001E4B0(temp_a0);
        func_800255E0(arg0);
        func_80025648(arg0);
        func_800256CC(arg0);
        func_8002575C(arg0);
    }
}

void func_80025848(SpriteSlots *arg0) {
    if (arg0->unk_0 != 0) {
        func_800255E0(arg0);
        func_80025648(arg0);
        func_800256CC(arg0);
        func_8002575C(arg0);
    }
}

void func_80025898(SpriteSlots *arg0) {
    s32 temp_a0;

    temp_a0 = arg0->unk_0;
    if (temp_a0 != 0) {
        func_8001E4B0(temp_a0);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800258C8);

void func_80025B10(void) {
    if (D_801E1E40 == 0) {
        D_801D3780 = 0;
        D_801D36FC = 0x160;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80025B3C);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80025B7C);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80025BBC);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80025C08);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80025C54);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80025DF8);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80025E68);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800267CC);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800268BC);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80026A6C);

void func_80026BC4(Monster *arg0) {
    s16 var_a1;
    Sprite *temp_v1;

    temp_v1 = arg0->unk_68;
    D_800AA268 = temp_v1;
    if ((temp_v1 != 0) && (arg0->unk_CC == 0)) {
        var_a1 = 3;
        if (arg0->unk_168 == 7) {
            var_a1 = 7;
        }
        arg0->unk_D4 = var_a1;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80026C04);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80026C4C);

void func_80026CFC(Monster *arg0) {
    u16 temp_v1;

    D_800AA248.unk_38 = arg0->unk_0;
    func_80026E0C(arg0);
    temp_v1 = arg0->unk_5A;
    if ((temp_v1 != 2) && (temp_v1 != 0x4E)) {
        func_80026DE4(arg0)(arg0);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80026D54);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80026D90);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80026DE4);

void func_80026E0C(Monster *arg0) {
    s32 temp_v1;
    u16 temp_v0;

    temp_v0 = arg0->unk_5A;
    temp_v1 = temp_v0 & 0xFFFF;
    arg0->unk_5C = temp_v0;
    if ((temp_v1 == 2) || (temp_v1 == 0x4E)) {
        if (arg0->unk_104 == 0) {
            arg0->unk_104 = 0x4000;
            D_800AA268->unk_10 = 0xFFFB0000;
        }
        arg0->unk_5A = 0x16U;
        return;
    }
    arg0->unk_5A = 4U;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80026E6C);

void func_80026F58(Monster *arg0) {
    D_800AA248.unk_38 = arg0->unk_0;
    arg0->unk_5A = 3;
    arg0->unk_DE = 1;
    arg0->unk_18A = 0;
    arg0->unk_126 = 0;
    func_80057DD8();
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80026F98);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8002703C);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800272B0);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800272FC);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80027348);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80027394);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800273F4);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800275F8);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80027878);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80027908);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80027AB0);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80027B20);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80027B78);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80027CB8);

void func_80027FC8(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80027FD0);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8002808C);

void func_80028140(s32 arg0, Monster *arg1, s16 arg2) {
    if ((arg0 & 0xFFFF) != (arg2 & 0xFFFF)) {
        arg1->unk_CE = arg2;
        return;
    }
    arg1->unk_CE = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80028160);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80028184);

void func_800284D8(void) {
    s32 var_v1;

    var_v1 = 0x20000;
    if (D_801D8720 == 0) {
        var_v1 = 0x80000;
    }
    D_801F9A30 = var_v1;
    D_801D3D8C = 2;
}

void func_80028508(void) {
    D_801F9A30 = 0xFFFE0000;
    D_801D3D8C = 1;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80028524);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800288B0);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80028ADC);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80028B1C);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80029118);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80029170);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800291DC);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80029510);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8002958C);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800297B4);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8002987C);

void func_8002994C(void) {
    if (D_801FB18C == 1) {
        D_801FB18C = func_8005E5C8();
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80029984);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800299C4);

void func_80029B54(void) {
    memset(&D_801E2894, 0, 8);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80029B80);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80029C6C);

void func_80029CF8(void) {
    D_800AA268->unk_22 = (u16) ((D_800AA268->unk_22 & 0xFF90) | 2);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80029D1C);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80029D5C);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8002A1AC);

s32 func_8002A300(void) {
    return 1;
}

u16 func_8002A308(void) {
    func_8001CFE4();
    return D_801D87A0;
}
