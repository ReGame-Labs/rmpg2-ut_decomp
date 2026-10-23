/* The first file of the game's code: main and the functions up to func_8002A308.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "game_8001781C.h"

/* decls:begin */
void func_80063084(s32, s32);
extern s32 D_8007B100[];
extern u8 D_801F998C[];
extern u8 *D_801F9AD8;
extern u16 D_8007BFEC[];
extern u16 D_8007BFD4[];
extern u16 D_8007BFBC[];
void func_80024C08(void *);
void func_8001C02C(void);
void func_8001C83C(void);
extern s16 D_801CA464;
extern s16 D_801D87C8;
void func_80017758(void);
extern s16 D_801F9A44[];
extern s16 D_801F9ADC;
extern s16 D_801F9ABC;
extern u16 D_800AA2C8;
void func_80017C04(void);
u16 func_8001828C(void);
void func_8001B858(void);
extern u32 D_801FA894;
extern s16 D_8007A692;
extern u16 D_8007A696;
extern s16 D_8007A698;
extern u16 D_8007A7D4;
extern u8 D_8007ED64[];
extern u8 D_8007EFA4[];
extern u8 D_8007F1E4[];
extern u8 D_80083414[];
extern u8 D_80083654[];
extern TextMessage D_800895A8;
extern TextMessage D_800897FC;
extern Sprite *D_800AA268;
extern GameState D_800AA248;
extern s16 D_800AA2C2;
extern TextState D_801D8588;
extern u32 D_801D8868[];
extern u8 D_801FAF7C[];
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
extern s16 D_801D3758;
extern s32 D_801D375C;
extern s32 D_801D3760;
extern u16 D_801D3768;
extern u16 D_801D3770;
extern s16 D_801D3778;
extern u16 D_801D3780;
extern s16 D_801D3D6C;
extern s16 D_801D3D8C;
extern u16 D_801D3DC6;
extern Sprite *D_801D8584;
extern s16 D_801D8708;
extern s16 D_801D870C;
extern u16 D_801D8720;
extern u16 D_801E28C8;
extern u16 D_801D8728;
extern s16 D_801D8738;
extern u16 D_801D8740;
extern s16 D_801D8744;
extern s32 D_801D8754;
extern Sprite *D_801D8764;
extern u16 D_801D87A0;
extern s16 D_801D87FC;
extern u8 D_801D8800[];
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
extern Unk1E2894 D_801E2894;
extern Sprite D_801E28C0;
extern s16 D_801E28DC;
extern s16 D_801E2994;
extern u16 D_801E29A4;
extern Sprite D_801E29A8;
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
extern u16 D_801FAF6C;
extern u16 D_801FAF6E;
extern u16 D_801FAF70;
extern s16 D_801FB18C;
void MemCardInit(s32);
void MemCardStart(void);
void cdload_load_overlay(s32);
void func_800193B8(void);
void func_80019764(void);
void func_80019890(void);
void func_80019984(s32);
void func_8001A1C8(void);
void func_8001A474(void);
SpriteImage *func_8001A554(s32, Sprite *);
void func_8001B350();
void func_8001B694(void);
void func_8001BA98(void);
void func_8001C404(void);
void func_8001D184();
void func_8001D7D0(void);
s32 func_8001D998(Sprite *);
void func_8001DF98(void);
void func_8001E0AC(void);
void func_8001E450(s32);
void func_8001E4B0(Sprite *);
void func_8001E664(Fixed *, s32, Fixed *, s32 *);
s32 func_8001B660(s32);
extern s16 D_800AA2C0;
void func_8001E700(Sprite *);
void func_8001E7C8(Sprite *);
s16 func_8001EA10(void);
s32 func_8001EAC4(s32);
void func_8001F2B0(void);
void func_8001F358(void);
void func_8001F39C(TextMessage *);
void func_8001F6B4(void);
void func_8001F7F8(s32);
void func_8001F848(void);
void func_8001F9DC(void);
void func_800205AC(void);
void func_80022EC0(void);
void func_80023080(Unk22D58 *);
void func_800242A8(void);
void func_80024530(Sprite *, Sprite *);
void func_8002469C(s32 *, s16, s16);
void func_80023CFC(Unk22D58 *ai);
void func_800256CC(SpriteSlots *);
void *func_80025C08(void *);
s32 func_80019B08(s32, s32, s32, s16);
s32 func_80019DAC(s32, s32, s32, s16);
extern s16 D_801D876C[];
void func_80025E68(void);
void func_8002A72C(void);
void func_8002AF28(void);
void func_800377B4(Unk22D58 *);
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
void func_80019ADC(s32 arg0);
void func_8001A420(void);
void func_8001A454(void);
void func_8001B054(Sprite *arg0);
void func_8001B098(Sprite *arg0);
void func_8001B5E8(s32 arg0);
void func_8001B7F4(void);
void func_8001B848(void);
void func_8001BB60(Monster *, s32);
void func_8001BB68(Sprite *arg0);
void func_8001BB88(Sprite *arg0);
void func_8001BBA8(Monster *, s32);
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
void func_8001E638(Unk1E638 *arg0, s32 arg1, Fixed *arg2, s32 *arg3);
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
void func_8001ED54(TextMessage *arg0);
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
void func_800233E0(Unk22D58 *arg0);
void func_80023F64(Unk22D58 *arg0);
void func_800240F0(Unk22D58 *arg0);
void func_8002423C(Unk22D58 *arg0);
void func_80024280(void);
void func_800242A0(void);
void func_80024508(Sprite *arg0);
void func_800245F8(void);
void func_80024954(void);
void func_8002495C(void);
void func_80024964(void);
void func_8002496C(Sprite *);
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
void func_80028140(s32 arg0, Monster *arg1, s32 arg2);
void func_800284D8(void);
void func_80028508(void);
void func_8002994C(void);
void func_80029B54(void);
void func_80029CF8(void);
s32 func_8002A300(void);
u16 func_8002A308(void);
extern u16 D_801E1C90[];
extern u16 D_801E1C98[];
extern u8 D_800AA900[][0x22];
extern u16 D_800AFB78[];
s32 func_80018DBC(void *, u16, s16, s16);
u16 func_80023474(Unk22D58 *);
void func_80024418(s16 *, s16 *, Unk22D58 *);
extern u16 D_801FA898[];
void func_80019268(void);
extern s16 D_801D36F8;
extern s16 D_801F9A34;
extern s16 D_801FA890;
extern Monster D_801E0B78[];
s32 func_80017C80(s32 arg0);
extern s16 D_801D3D7C;
void func_80020CE4(s32 arg0, s32 arg1);
u16 func_8001D844(void);
void func_8001D598(void);
extern s16 D_801D872C;
extern s16 D_801E28A0;
extern s16 D_801F9944;
extern u16 D_801F9AE0;
extern s32 D_801E28E0;
void func_8001BDCC(void);
extern UnkFA738 D_801FA7EC[];
void func_8001A534(s32 arg0, s16 arg1, s32 arg2);
extern UnkFA738 D_801FA738[];
void func_8001A514(s32 arg0, s32 arg1, s32 arg2);
void func_80024C08(void *arg0);
void func_8001D15C(void *dst, void *src, s32 size);
extern Unk1D110 D_801CA430;
extern u8 D_8007AB34[];
s16 func_8003FCD8(s32, s16);
void func_800585C0(void *);
Sprite *func_8001E204(void);
extern s16 D_801E2998;
extern s8 D_801FA8A0[];
extern Unk7BD78 D_8007BD78;
void func_80017964(void);
extern Unk801D3D64 D_801D3D64;
extern s32 D_801FA72C;
extern u16 D_800AA2E0;
extern u16 D_800AA2E8;
void func_80017B98(void);
void func_8001A220(void);
extern u16 D_801F9A3C;
extern Unk1C542C D_801C542C[];
extern Unk1F9AE4 D_801F9AE4[];
extern u8 D_800B09C0[];
extern u16 D_8007C1D4[];
extern u16 D_8007BA20[];
extern u16 D_801E289A;
void func_8001A870(s32, u8 *);
void func_80061170(s32);
s32 cdload_read_file(s32, void *);
extern s32 D_801D3D9C[];
void func_80062DCC(s32);
s32 func_8001A0E4(s32);
extern u8 *D_801F9948;
s32 func_80025DF8(s32);
extern u16 D_801D37B4;
extern u16 D_801E0D38;
extern u16 D_801FA95C;
extern u16 D_801FA968;
extern u16 D_801FA994;
extern u16 D_801FA99C;
void func_80017B24(void);
void func_8001AC18(s32, s32);
Sprite *func_8001DCB4();   /* no argument: it reads D_800AA284 (the callers' a0 is incidental) */
void func_80062C30(void);
void func_800A30B4(void);
extern u8 D_800A5DD8[];
extern u8 D_800A5E18[];
extern u8 D_800A5E54[];
extern u8 D_800A5E88[];
extern u8 D_800A5EC0[];
extern u8 D_800A5F00[];
extern u8 D_800A5F40[];
extern u8 D_800A5F84[];
void func_8001BBB0(void);
void func_800543FC(void);
extern u16 D_8007AB60;
void func_8001D1C8(void);
void func_8001E174(void);
void func_8001E2F8(Sprite *arg0);
void func_8005DBC4(s32, Unk29510 *, s32);
void func_80029510(Unk29510 *arg0);
void func_80024BB4(void);
void func_80025B3C(Unk1D3DC8 *);
void func_80025B7C(Unk1D3DC8Item *);
void func_8003044C(void);
extern Unk1D3DC8 D_801D3DC8[];
void func_80024AEC(void);
void func_8001E39C(void *);
void func_80029C6C(Monster *arg0);
extern s16 D_801F9914;
void func_80026A6C(void);
Unk1D110 *func_8001D110(void);
extern Unk1D110 *D_800AA284;
void func_8002503C(Unk1D3DC8 *, Sprite *);
void func_800252CC(Unk1D3DC8 *);
void func_80025124(Unk1D3DC8 *);
void func_80024E08(Unk1D3DC8 *);
void func_800258C8(void);
extern u8 D_80082E94[];
s32 func_8005F208(void);
u16 func_80029B80(void);
extern Unk25124Def D_800135E8;
extern Unk25124Def D_8001687C;
extern u16 D_8007C124[];
extern u16 D_8007C144[];
extern u32 D_801E0D7C;
extern s16 D_801D3D8A;
extern u16 D_801FA734;
extern Anim D_80093F78;
extern Anim D_80093FAC;
u16 func_80023C58(s16 arg0, Unk22D58 *ai);
u16 func_80023AC0(Unk22D58 *ai);
s32 func_80026D54(Monster *);
s32 func_80026D90(Monster *);
s32 func_80027348();   /* (Monster *): the callers that pass nothing still have it in a0 */
void func_80026C4C(Monster *arg0);
s32 func_800272FC();   /* (Monster *), as func_80027348 */
s32 func_800272B0();
void func_800580F8(void *);
void func_80026F98(Monster *arg0);
void func_80020AF4(s32);
void func_800273F4(Monster *, s32);
void func_80027394(void);
extern s32 D_801C51D0;
s32 func_8001A0A0(void);
extern u8 D_8007AB70[];
extern u16 D_8007AB84[];
void func_8001D6A0(void);
extern s32 D_801E299C;
extern s32 D_801FA974;
extern Unk1FAC80 *D_801FAC80;
Glyph *func_8001B128(u32);
void func_8001EEA0(void);
void func_8001EDE4(void);
void func_8001EE24(void);
void func_8001EE60(void);
s32 func_8001F50C(u8 *);
void func_8001F464(void);
void func_8001F400(void);
extern Anim D_8008AE40;
extern Anim D_8008AE8C;
extern Anim D_8008AF24;
extern Anim D_8008B248;
extern Anim D_8008B558;
extern Anim D_8008B898;
extern Anim D_80097340;
extern Anim D_80097374;
extern Anim D_800973DC;
extern Anim D_80097640;
extern Anim D_80097950;
extern Anim D_80097DF0;
extern Anim D_8008B9C8;
extern Anim D_80097C90;
extern Anim D_8008B358;
extern Anim D_8008B458;
extern Anim D_80097750;
extern Anim D_80097850;
extern s32 D_801D8864;
extern s32 D_801F9AC8;
s32 func_8003EB5C(Anim *, Sprite *);
void func_800377B4(Unk22D58 *);
u16 func_80023CB8(void);
s16 func_8002439C(Unk22D58 *);
u16 func_8002326C(s16);
u16 func_80023620(Unk22D58 *);
u16 func_80023B20(Unk22D58 *);
u16 func_80023114();   /* no parameter (it works on D_800AA268); func_8002180C passes its state anyway */
u16 func_800231E4(Unk22D58 *);
void func_80023FAC(void);
void func_800232D8(Unk22D58 *);
extern u8 D_8007B080[];
extern u16 D_801D8750;
extern s32 D_801F9ACC;
void func_80063270(void);
void func_8003DAA0(Unk22D58 *);
void func_8002075C(void);
extern u16 *D_8007A7C0[];
extern u8 D_801E2154[];
extern u16 D_801FB188;
void func_8002A1AC(Monster *, s32);
void func_8005A2F4(Monster *, s32);
void func_8005A964(Monster *);
extern u8 D_800105A8[];
extern s32 D_8007AD4C[];
extern s16 D_800AA300[11][8][8];
extern Sprite *D_801D373C;
extern u16 D_801D8866;
extern s16 D_801F9ACA;
extern s16 D_801FA984[];
void func_8001F61C(u8 *, s16, s16, s32, s32, s32 *, s32, s32);
u16 func_80025C54(void *);
/* decls:end */

/* 85 %: GCC 2.8.1 emits a call to __main at the start of any function named main (the target defines no init section); the original has none. The rest of the body is in place; whether the original was built with a compiler configured otherwise is open */
#ifdef NON_MATCHING
void main(void) {
    func_80017758();
    func_80018CB0();
    func_80017A40();
    D_801D8750 = 0xFFFF;
    D_801F9A44[0] = 0;
    D_801F9A44[1] = 0;
    D_801F9A44[2] = 0;
    D_801F9A44[3] = 1;
    D_801F9A44[4] = 1;
    D_801F9A44[5] = 1;
    D_801F9A44[6] = 1;
    D_801F9ADC = 0;
    D_801F9ABC = 0;
    for (;;) {
        func_80017964();
        func_80018D10(1);
        for (;;) {
            func_80018CD0();
            if (D_800AA2C8 == 0) {
                D_800AA2C8++;
                func_80017C04();
                if (D_801F9A34 > 0) {
                    D_801F9A34--;
                }
                if (func_8001828C() == 1) {
                    break;
                }
                func_8001B7F4();
                if (D_801D3D64.unk_62 == 0) {
                    func_8001B858();
                }
            }
            if (D_800AA2E0 != 0) {
                D_800AA2C8 = 0;
                D_800AA2E8 = 0;
                D_800AA2E0 = 0;
            }
            func_8001EA78();
            func_8001DF98();
            func_8001D8E8();
            func_80018CF0();
        }
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", main);
#endif

void func_80017964(void) {
    D_801D36FC = 0x110;
    D_801F9AE0 = 0;
    D_801E29BC = 0;
    D_801D3780 = 0;
    D_801FA9A4 = 0;
    D_801E2998 = 1;
    D_801FA9B8 = 0;
    memset(&D_8007BD78, 0, 0x94);
    D_801FA8A0[0] = 0;
    D_801FA8A0[1] = 0;
    D_801FA8A0[2] = 0;
    D_801FA8A0[3] = 0;
    D_801FA8A0[4] = 0;
    D_801FA8A0[5] = 0;
    D_801FA8A0[6] = 0;
    func_8001E9C4(GetRCnt(0xF2000001), GetRCnt(0xF2000001));
    func_8001B848();
    func_8001E0AC();
    func_8001E980();
}

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

void func_80017B98(void) {
    if (D_801D3D64.unk_62 == 0) {
        D_801D3D64.unk_1C += 1;
        D_800AA2E8 += 1;
        D_801FA72C += 1;
        D_801F9954 += 1;
    }
    D_800AA2E0 += 1;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80017C04);

s32 func_80017C80(s32 arg0) {
    u16 temp_v1;
    Monster *temp_a1;

    temp_a1 = &D_801E0B78[arg0 & 0xFFFF];
    if ((D_801D36F8 != 0) || (D_801FA890 != 0) || (D_801F9A34 > 0) || (temp_a1->unk_0 == 0) || (temp_v1 = temp_a1->unk_5A, (temp_v1 == 0x1F)) || (temp_v1 == 0x37) || (temp_v1 == 0x26) || (temp_a1->unk_46 != 0) || ((D_801D36FC != 0x240) && (D_801D36FC != 0x150) && (D_801D36FC != 0x220)) || ((D_801E1E40 == 0) && (D_801D36FC == 0x150)) || ((D_801D3758 < 5) && (D_801D36FC == 0x220))) {
        return 0;
    }
    return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80017D8C);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80017F14);

void func_80018008(void) {
    func_8001E450(0x7FE);
    D_8007A698 = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001802C);

#ifdef NON_MATCHING
/* 80.2 %: register allocation around the two constants 0x4F002808 and 0x7000 */
void func_800180E4(void) {
    Unk1D110 *request;
    Sprite *sprite;
    s32 kind;

    kind = 0x7000;
    request = func_8001D110();
    D_800AA284 = request;
    request->unk_10.full = 0xA00000;
    request->unk_14.full = 0xD70000;
    request->unk_0 = 0x4F002808;
    request->unk_20 = kind;
    request->unk_6 |= 0x20;
    sprite = func_8001DCB4(kind);
    D_801D373C = sprite;
    sprite->unk_70 = 0x550;
    func_8001F61C(D_800105A8, 0xB9, 0xD6, 1, 0x46, D_8007AD4C, 1, 0x550);
    sprite = D_801E28C0.unk_0;
    if (sprite != &D_801E28C0) {
        do {
            if (sprite->unk_70 == 0x550) {
                sprite->unk_78 = 0x808080;
            }
            sprite = sprite->unk_0;
        } while (sprite != &D_801E28C0);
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800180E4);
#endif

void func_800181D0(void) {
    s32 bit;
    s32 i;

    bit = 1;
    for (i = 0; i < 8; i++) {
        if ((s16) D_8007A696 & bit) {
            switch (i) {
            case 0:
                func_8001F7CC(0x3C, 0x1D);
                break;
            case 1:
                func_8001F7CC(0x3C, 0x2A);
                break;
            case 2:
                func_8001F7CC(0x64, 4);
                break;
            case 3:
                func_8001F7CC(0x8C, 0x6D);
                break;
            }
        }
        bit <<= 1;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001828C);

void func_80018BD4(s32 from, u16 to) {
    Sprite *head;
    Sprite *sprite;

    head = &D_801E28C0;
    sprite = head->unk_0;
    if (sprite != head) {
        do {
            if (sprite->unk_74 == from) {
                sprite->unk_74 = to;
            }
            sprite = sprite->unk_0;
        } while (sprite != head);
    }
}

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

void func_80019268(void) {
    s32 i;
    u16 *dst;
    u16 *src;
    u16 v;

    i = 0;
    dst = D_801FA898;
    src = D_801E1C90;
    do {
        v = *src;
        src++;
        i++;
        *dst = v;
        dst++;
    } while (i < 3);
}

u16 *func_800192A0(void) {
    s16 i;
    s16 k;
    s16 total;

    for (i = 0; i < 3; i++) {
        D_801E1C90[i] = 0;
    }
    k = 0;
    total = 0;
    for (; k < 2; k++) {
        if (total >= 3) {
            break;
        }
        total += func_80018DBC(D_800AA900[k], 3 - total, total, k);
    }
    for (i = 0; i < 3; i++) {
        D_801E1C98[i] = D_801E1C90[i];
    }
    return D_800AFB78;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800193B8);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80019764);

void func_80019890(void) {
    u32 color;

    DrawSync(0);
    VSync(0);
    D_801FA974 = D_801E299C;
    color = D_801FA9A4;
    D_801FAC80->draw.r0 = color >> 0x10;
    D_801FAC80->draw.g0 = color >> 8;
    D_801FAC80->draw.b0 = color;
    PutDispEnv(&D_801FAC80->disp);
    PutDrawEnv(&D_801FAC80->draw);
    DrawOTag(D_801FAC80->ot);
}

u16 func_80019920(u16 bits, u16 which) {
    u16 result;
    u16 *p;
    s32 i;

    result = 0;
    p = D_8007A7C0[which];
    i = 0;
    while (bits != 0 && i < 16) {
        if (bits & 1) {
            result |= *p;
        }
        bits >>= 1;
        p++;
        i++;
    }
    return result;
}

void func_80019984(s32 arg0) {
    u16 bits;

    D_801FA894 = D_801E0D7C;
    D_801E0D7C = 0;
    func_800192A0();
    bits = func_80019920(D_800AFB78[2], ((arg0 & 0xFFFF) && (D_801D3DC6 == 0)) ? D_801D8800[2] : 0);
    D_801E0D7C |= bits << 20;
    bits = func_80019920(D_800AFB78[1], ((arg0 & 0xFFFF) && (D_801D3DC6 == 0)) ? D_801D8800[1] : 0);
    D_801E0D7C |= bits << 10;
    bits = func_80019920(D_800AFB78[0], ((arg0 & 0xFFFF) && (D_801D3DC6 == 0)) ? D_801D8800[0] : 0);
    D_801E0D7C |= bits;
}

void func_80019ABC(s32 arg0) {
    SetDispMask(arg0 & 0xFFFF);
}

void func_80019ADC(s32 arg0) {
    memset(D_801E1C78, 0, 0x10000);
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80019B08);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80019DAC);

s32 func_8001A0A0(void) {
    s32 index;

    do {
        index = (u8) D_801C51D0 | 0x200;
        D_801C51D0 += 1;
    } while (D_801C542C[index].unk_0 != -1);
    return index;
}

s32 func_8001A0E4(s32 index) {
    Unk1C542C *e;
    s32 y;
    s32 x;
    s32 bank;
    s32 col;
    s32 row;
    s32 w;
    s32 h;
    s32 wc;
    s32 hc;
    s32 i;
    s32 j;

    e = &D_801C542C[index];
    e->unk_0 = -1;
    y = e->unk_8;
    x = e->unk_4 - 0x100;
    bank = x >> 7;
    e->unk_4 = x;
    col = (x & 0x7F) >> 4;
    if (y >> 8) {
        bank += 6;
    }
    row = (y & 0xFF) >> 5;
    w = e->unk_C * 2;
    h = e->unk_10;
    wc = w >> 5;
    if (w & 0x1F) {
        wc++;
    }
    hc = h >> 5;
    if (h & 0x1F) {
        hc++;
    }
    for (j = 0; j < hc; j++) {
        for (i = 0; i < wc; i++) {
            D_800AA300[bank][j + row][i + col] = 0;
        }
    }
    return 0;
}

void func_8001A1C8(void) {
    s16 fill;
    s32 i;

    if (D_801F9A3C == 0) {
        func_8001A220();
        fill = -1;
        for (i = 0x3FF; i >= 0; i--) {
            D_801C542C[i].unk_0 = fill;
        }
        func_80019ADC(0);
    }
}

void func_8001A220(void) {
    s32 i;
    s32 j;
    s32 k;
    s16 fill;

    for (i = 0; i < 11; i++) {
        for (j = 0; j < 8; j++) {
            for (k = 0; k < 8; k++) {
                D_800AA300[i][j][k] = 0;
            }
        }
    }
    for (j = 0; j < 8; j++) {
        for (k = 0; k < 8; k++) {
            D_800AA300[0][j][k] = 2;
            D_800AA300[6][j][k] = 2;
        }
    }
    for (j = 0; j < 8; j++) {
        for (k = 4; k < 8; k++) {
            D_800AA300[10][j][k] = 2;
        }
    }
    fill = -1;
    for (i = 20; i >= 0; i--) {
        D_801D876C[i] = fill;
    }
    for (i = 0; i < 0xC4; i++) {
        memset(&D_801F9AE4[i], 0, 0x10);
        D_801F9AE4[i].unk_4 = 0;
    }
    for (i = 0; i < 0x2134; i++) {
        if (!(D_801D8868[i] & 0x80000000)) {
            D_801D8868[i] = 0;
        }
    }
}

s32 func_8001A3AC(void) {
    s32 count;
    s32 i;
    s32 j;
    s32 k;

    count = 0;
    for (k = 0; k < 11; k++) {
        for (j = 0; j < 8; j++) {
            for (i = 0; i < 8; i++) {
                if (D_800AA300[k][j][i] == 0) {
                    count++;
                }
            }
        }
    }
    return count;
}

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

void func_8001A474(void) {
    s32 i;

    if (D_801F9A3C == 0) {
        for (i = 0; i < 0x14; i++) {
            if (i != 0xF) {
                memset(&D_801FA738[i], 0xFF, 8);
                memset(&D_801FA7EC[i], 0xFF, 8);
            }
        }
        D_801F9948 = D_801E1C78;
    }
}

void func_8001A514(s32 arg0, s32 arg1, s32 arg2) {
    UnkFA738 *temp_a0;

    temp_a0 = &D_801FA738[arg0 & 0xFFFF];
    temp_a0->unk_0 = arg2;
    temp_a0->unk_4 = arg1;
}

void func_8001A534(s32 arg0, s16 arg1, s32 arg2) {
    UnkFA738 *temp_a0;

    temp_a0 = &D_801FA7EC[arg0 & 0xFFFF];
    temp_a0->unk_0 = arg2;
    temp_a0->unk_4 = arg1;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001A554);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001A784);

u16 func_8001A820(s32 index, s32 id) {
    UnkFA738 *e = &D_801FA738[index & 0xFFFF];

    return (u16) e->unk_4 == (u16) id;
}

s32 func_8001A848(s32 index, s32 id) {
    UnkFA738 *e = &D_801FA7EC[index & 0xFFFF];

    return (u16) e->unk_4 == (u16) id;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001A870);

s32 func_8001AA4C(s32 arg0, s32 arg1) {
    s32 bank;
    s32 file;

    bank = arg0 & 0xFFFF;
    file = arg1 & 0xFFFF;
    if (func_8001A820(bank, file)) {
        return 1;
    }
    func_80061170(file);
    if (cdload_read_file(file, D_801F9948) == 0) {
        return 0;
    }
    func_8001A870(bank, D_801F9948);
    D_801F9948 += 4;
    func_8001A514(bank, file, (s32) D_801F9948);
    func_8001B0D8((s32 *) (D_801F9948 + *(s32 *) D_801F9948), 0);
    D_801F9948 += *(s32 *) D_801F9948;
    if (D_801F9948 - D_800B09C0 > 0x114800) {
        func_8001B5E8(4);
    }
    return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001AB30);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001AC18);

/* 89 %: the loop invariants (id << 16, id | 0x8000, the table base) are set up in another order and the second loop keeps -1 and 0x8000 in saved registers */
#ifdef NON_MATCHING
void func_8001AD1C(Unk1AD1C *bank, s32 addr, s16 id) {
    u32 i;
    s32 slot;
    s16 id2;

    i = 0;
    if (bank->unk_4 != 0) {
        id2 = id | 0x8000;
        do {
            slot = func_80019B08(addr, 0x100, 0x100, id);
            if (slot == -1) {
                func_8001B5E8(5);
            }
            addr += 0x10000;
            D_801D876C[slot * 2] = id2;
            D_801D876C[slot * 2 + 1] = id2;
            i++;
        } while (i < bank->unk_4);
    }
    i = 0;
    if (bank->unk_8 != 0) {
        do {
            slot = func_80019DAC(addr, 0x100, 0x100, id);
            if (slot == -1) {
                func_8001B5E8(6);
            }
            addr += 0x8000;
            D_801D876C[slot] = id;
            i++;
        } while (i < bank->unk_8);
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001AD1C);
#endif

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

/* 83 %: the original copies the argument (move a2,a0) and walks two pointers from it, the first loop load ordered before the second */
#ifdef NON_MATCHING
void func_8001B0D8(s32 *p, s32 flags) {
    s32 *q;

    if (p[1] != 0) {
        q = p + 1;
        do {
            D_801D8868[*p] = *q | flags;
            q += 2;
            p += 2;
        } while (*q != 0);
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001B0D8);
#endif

Glyph *func_8001B128(u32 arg0) {
    u32 index;

    index = (arg0 & 0xFFFFFF) >> 1;
    return (Glyph *) (D_801FA738[(arg0 >> 24) & 0x3F].unk_0 + (D_801D8868[index] & 0x7FFFFFFF));
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001B178);

void func_8001B350(s32 index) {
    Unk1F9AE4 *rec;

    rec = &D_801F9AE4[index & 0xFFFF];
    if (rec->unk_4 > 0) {
        if (--rec->unk_4 == 0) {
            func_8001A0E4(rec->unk_C);
            rec->unk_8 = 0;
            rec->unk_C = -1;
        }
    } else {
        func_8001B5E8(8);
    }
}

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

s32 func_8001B660(s32 id) {
    if (id < 0) {
        return id;
    }
    return D_801FA7EC[(u32) id >> 28].unk_0 + (((u32) id << 4) >> 4);
}

#ifdef NON_MATCHING
/* 95.7 %: the two registers of the first sum are swapped and the monster table's base address is formed before the first call instead of after it. */
void func_8001B694(void) {
    u16 sum;

    sum = D_801F9950 + D_801D37B4;
    D_801D37B4 = sum;
    if ((s16) sum > 0) {
        D_801D37B4 = 0;
    }
    if (D_801D3D64.unk_1A != 0) {
        D_801D3D64.unk_1A = (u16) (D_801D3D64.unk_1A - 1);
    }
    D_801E0D38 += D_801F9954;
    if ((s16) D_801E0D38 >= 0x3C) {
        D_801E0D38 = 0;
        if ((D_801FA968 == 0) && (D_801D36FC == 0x150)) {
            if (D_801E0B78[func_80025DF8(1)].unk_0 != 0) {
                D_801FA95C += 1;
            }
            if (D_801E0B78[func_80025DF8(2)].unk_0 != 0) {
                D_801FA99C += 1;
            }
            if (D_801E0B78[func_80025DF8(3)].unk_0 != 0) {
                D_801FA994 += 1;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001B694);
#endif

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

void func_8001B858(void) {
    D_801E28A0 = 0;
    func_80027394();
    switch (D_801D36FC) {
    case 0x270:
        D_801D36FC = 0x110;
        break;
    case 0x110:
        cdload_load_overlay(0);
        func_8001BBB0();
        break;
    case 0x120:
        D_801D87C8 = 0;
        D_8007A7D4 |= 1;
        func_8001BDCC();
        break;
    case 0x130:
        D_801D87C8 = 0;
        func_8001BECC();
        break;
    case 0x140:
        D_801D87C8 = 0;
        D_801CA464 = 1;
        D_8007A7D4 |= 1;
        if (D_801FA960 == 0) {
            D_801CA464 = 3;
        }
        D_801D36FC = 0x200;
        break;
    case 0x200:
        D_801D87C8 = 0;
        func_8001C02C();
        break;
    case 0x210:
        cdload_load_overlay(2);
        func_8001C77C();
        break;
    case 0x230:
        cdload_load_overlay(2);
        break;
    case 0x150:
        func_8001C784();
        break;
    case 0x160:
        func_8001C83C();
        break;
    case 0x170:
        D_801D87C8 = 0;
        func_8001D018();
        break;
    case 0x220:
        func_8001C834();
        break;
    case 0x260:
        cdload_load_overlay(3);
        D_801D87C8 = 0;
        break;
    case 0x180:
    case 0x240:
        break;
    }
}

void func_8001BA98(void) {
    Monster *monster;
    u16 i;

    i = 7;
    do {
        monster = &D_801E0B78[i];
        if (monster->unk_46 != 0) {
            func_8001BB60(monster, i);
        } else if ((monster->unk_1E0 != 2) && (monster->unk_0 != 0) &&
                   ((monster->unk_5A == 0x37) || (monster->unk_5A == 0x26)) && (monster->unk_1F8 == 0)) {
            func_8001BBA8(monster, i);
        }
    } while (--i != 0);
}

void func_8001BB60(Monster *monster, s32 index) {
}

void func_8001BB68(Sprite *arg0) {
    if (arg0 != NULL) {
        arg0->unk_18.u.hi = (u16) (arg0->unk_18.u.hi | 0xC000);
    }
}

void func_8001BB88(Sprite *arg0) {
    if (arg0 != NULL) {
        arg0->unk_18.u.hi = (u16) (arg0->unk_18.u.hi & 0x3FFF);
    }
}

void func_8001BBA8(Monster *monster, s32 index) {
}

#ifdef NON_MATCHING
/* 96.1 %: the constant 0x0A0041C8 is formed in another register and its two halves are not spread around the other stores. */
void func_8001BBB0(void) {
    Unk1D110 *temp_v0;

    if (D_801D3780 == 0) {
        D_801D3780 = 1;
        D_801E29BC = 0;
        if (D_801D3770 == 0) {
            func_80017B24();
            func_8001A420();
            func_8001AC18(0xA, 0x1B);
            D_800AA2EC = 0x51;
            func_8001ED54(&D_800A5DD8);
            func_8001ED54(&D_800A5E18);
            func_8001ED54(&D_800A5E54);
            func_8001ED54(&D_800A5E88);
            func_8001ED54(&D_800A5EC0);
            func_8001ED54(&D_800A5F00);
            func_8001ED54(&D_800A5F40);
            func_8001ED54(&D_800A5F84);
            temp_v0 = func_8001D110();
            D_800AA284 = temp_v0;
            temp_v0->unk_0 = 0x0A0041C8;
            temp_v0->unk_10.full = 0x930000;
            temp_v0->unk_14.full = 0x1E0000;
            temp_v0->unk_20 = 0x14;
            temp_v0->unk_6 |= 0x20;
            func_8001DCB4(0x14);
            D_801E29BC = 2;
            D_801CA468 = func_8002A300();
            func_800A30B4();
            return;
        }
        goto block_4;
    }
block_4:
    if (D_801E29BC != 0) {
        D_801E29BC = (u16) D_801E29BC - 1;
        return;
    }
    if (D_801D3770 == 0) {
        func_80062C30();
        func_80062DA8((u8) D_801E1CB4);
        func_80062D88((u8) D_801E2150);
    }
    D_801D3780 = 0;
    D_801F9AE0 = 0;
    D_801E29BC = 0x78;
    func_8001CFB4();
    D_801D36FC = 0x130;
    D_801CA45C = 0;
    func_8001D17C();
    func_8001E758();
    if (D_801D3770 == 0) {
        cdload_load_overlay(1);
        func_80017B24();
        func_800A9890(0x1A);
        func_800A9890(0x1C);
    }
    cdload_load_overlay(0);
    D_801D3770 = 1;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001BBB0);
#endif

s16 func_8001BDBC(void) {
    return D_801CA468;
}

void func_8001BDCC(void) {
    D_801E28A0 = 1;
    if ((func_8001BDBC() != 0) || (func_8002A308() == 0)) {
        D_801D3778 = 0x3C;
        if (func_8001D844() == 0) {
            func_8001D598();
            return;
        }
    } else if (D_801D87FC != 0) {
        if (D_801E28E0 == 0) {
            func_8001D598();
            return;
        }
    }
    D_801D3780 = 0;
    D_801D87FC = 0;
    D_801E29BC = 2;
    D_801D36FC = 0x130;
    D_801CA45C = 0;
    func_8001D184();
    D_801F9AE0 = 0;
    func_80024AA0();
    func_8001D77C();
    D_801D872C = 0;
    D_801CA468 = func_8002A300();
    D_801F9944 = 0x16;
    D_801E0D64 = 0;
}

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

Unk1D110 *func_8001D110(void) {
    func_8001D15C(&D_801CA430, &D_8007AB34, 0x2C);
    D_800AA248.unk_1C = &D_801CA430;
    D_800AA248.unk_3C = &D_801CA430;
    return &D_801CA430;
}

void func_8001D15C(void *dst, void *src, s32 size) {
    memcpy(dst, src, size & 0xFFFF);
}

void func_8001D17C(void) {
}

void func_8001D184(void) {
    Sprite *saved;

    saved = D_800AA248.unk_20;
    func_8001D0C0();
    D_800AA248.unk_20 = saved;
}

void func_8001D1C0(void) {
}

void func_8001D1C8(void) {
    s32 i;
    s8 *p;

    i = 6;
    p = &D_801FA8A0[i];
    do {
        *p = 0;
        i -= 1;
        p -= 1;
    } while (i >= 0);
    D_8007AB60 += 1;
    D_8007A7D4 |= 1;
    func_8001D084();
    func_8001F6B4();
    cdload_load_overlay(0);
    func_8001D17C();
    func_8001E758();
    func_8001D0C0();
    func_800543FC();
    D_801D36FC = 0x130;
    D_801CA45C = 0;
    D_801E29BC = 0;
    D_801D3778 = 0;
    D_801FA960 = 0;
    D_801E1CAC = 0;
    D_801D3780 = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001D28C);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001D4B8);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001D598);

void func_8001D6A0(void) {
    u16 temp_v0;
    u8 temp_v1;

    D_801D3780 = 0;
    if ((D_801F9AE0 != 1) && (D_801F9AE0 != 7) && (D_801F9AE0 != 0xC)) {
        temp_v1 = D_8007AB70[D_801F9AE0];
        if (temp_v1 == 1) {
            D_801F9A3C = (s16) temp_v1;
        }
        if ((D_801F9AE0 == 3) || (D_801F9AE0 == 9) || (D_801F9AE0 == 0xE)) {
            D_801FA9A4 = 0;
        }
        func_8001D184();
        D_801F9A3C = 0;
    }
    temp_v0 = D_801F9AE0 + 1;
    D_801F9AE0 = temp_v0;
    if ((u32) (temp_v0 & 0xFFFF) >= 0x12U) {
        D_801F9AE0 = 0;
    }
    D_801E29BC = D_8007AB84[D_801F9AE0];
}

void func_8001D77C(void) {
    D_801D3780 = 0;
    func_8001D7A8();
    func_8001D184();
}

void func_8001D7A8(void) {
    func_8001F6B4();
    func_8001D7D0();
}

void func_8001D7D0(void) {
    s32 i;
    s8 *p;

    func_8001D17C();
    D_8007A7D4 |= 1;
    func_8001D084();
    D_801D375C = 0;
    D_801D3760 = 0;
    func_8001E758();
    func_80017B88();
    i = 6;
    p = &D_801FA8A0[i];
    do {
        *p = 0;
        i -= 1;
        p -= 1;
    } while (i >= 0);
}

u16 func_8001D844(void) {
    if (D_801E0D7C != 0) {
        D_800AA2C0 = 1;
        return 1;
    }
    D_800AA2C0 = 0;
    return 0;
}

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

#ifdef NON_MATCHING
/* 98.1 %: register names only (the list head's address is kept in t0/t1 in the original, v1/t0 here) */
void func_8001E010(void) {
    Sprite *sprite;
    Sprite *next;
    Sprite *pos;
    Sprite *prev;

    sprite = D_801E28C0.unk_0;
    if (sprite->unk_0 != sprite) {
        D_801E28C0.unk_0 = &D_801E28C0;
        D_801E28C0.unk_4 = &D_801E28C0;
        if (sprite != &D_801E28C0) {
            do {
                pos = D_801E28C0.unk_0;
                next = sprite->unk_0;
                while (pos != &D_801E28C0 && pos->unk_80 >= sprite->unk_80) {
                    pos = pos->unk_0;
                }
                prev = pos->unk_4;
                sprite->unk_0 = pos;
                sprite->unk_4 = prev;
                pos->unk_4->unk_0 = sprite;
                pos->unk_4 = sprite;
                sprite = next;
            } while (sprite != &D_801E28C0);
        }
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001E010);
#endif

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001E0AC);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001E174);

Sprite *func_8001E204(void) {
    u16 temp_v0;
    Sprite *temp_s0;

    temp_s0 = D_801E1C7C;
    if (temp_s0 == NULL) {
        D_800AA2C2 = 1;
        return NULL;
    }
    temp_v0 = D_801D3768 - 1;
    D_801D3768 = temp_v0;
    if ((temp_v0 << 0x10) == 0) {
        if (temp_s0 != D_801D8764) {
            func_8001B5E8(0xD);
        }
        D_801D8764 = 0;
    }
    D_801E1C7C = temp_s0->unk_0;
    memset(temp_s0, 0, 0xCC);
    temp_s0->unk_22 = 0x8000;
    D_800AA2C2 = 0;
    return temp_s0;
}

s32 func_8001E2B8(Sprite *arg0) {
    memset(arg0->unk_8C, 0, 0x40);
    arg0->unk_60 = 0;
    D_800AA2C2 = 0;
    return 0;
}

void func_8001E2F8(Sprite *arg0) {
    Sprite *head;
    Sprite *prev;
    Sprite *p;
    u16 key;

    func_8001E174();
    head = arg0->unk_0;
    if (head == NULL) {
        if (arg0->unk_82 != 1) {
            p = &D_801E28C0;
        } else {
            p = &D_801E29A8;
        }
        head = p;
        p = p->unk_0;
        key = arg0->unk_80;
        while ((p != head) && ((s16) key < p->unk_80)) {
            p = p->unk_0;
        }
        prev = p->unk_4;
        arg0->unk_0 = p;
        prev->unk_0 = arg0;
        p->unk_4 = arg0;
        arg0->unk_4 = prev;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001E39C);

void func_8001E450(s32 kind) {
    Sprite *head;
    Sprite *sprite;
    Sprite *next;

    head = &D_801E28C0;
    sprite = head->unk_0;
    do {
        next = sprite->unk_0;
        if (sprite->unk_70 == (u16) kind) {
            func_8001E4B0(sprite);
        }
        sprite = next;
    } while (sprite != head);
}

void func_8001E4B0(Sprite *sprite) {
    func_8001E174();
    if (!(sprite->unk_22 & 0x8000)) {
        for (;;) {
        }
    }
    sprite->unk_22 &= 0x7FFF;
    if (sprite->unk_6C & 0x4000) {
        func_8001E7C8(sprite);
    }
    func_8001E39C(sprite);
    func_8002496C(sprite);
    func_8001E528(sprite);
}

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

s32 func_8001E59C(Sprite *sprite, s32 image) {
    SpriteImage *img;
    s32 offset;
    s32 size;

    img = func_8001A554(image, sprite);
    func_80024974(img->unk_C);
    if (D_800AA248.unk_7A == 1) {
        return 1;
    }
    sprite->unk_74 = 0xFFFF;
    sprite->unk_78 = -1;
    sprite->unk_34 = img;
    offset = img->unk_4;
    sprite->unk_22 = 0;
    sprite->unk_2C = offset;
    sprite->unk_30.full = offset;
    size = img->unk_8.full;
    sprite->unk_28.full = 0x02000200;
    sprite->unk_7C = size;
    sprite->unk_1C.full = size;
    D_800AA248.unk_7A = 0;
    return 0;
}

void func_8001E638(Unk1E638 *arg0, s32 arg1, Fixed *arg2, s32 *arg3) {
    arg2->full = arg0->unk_8;
    func_8001E664(&arg0->unk_4, arg1 & 0xFFFF, arg2, arg3);
}

void func_8001E664(Fixed *width, s32 flags, Fixed *pos, s32 *y) {
    s32 x;
    s32 hi;
    s32 w;

    x = pos->u.lo << 16;
    hi = pos->u.hi << 16;
    w = (width->u.lo - 1) << 16;
    if (flags & 0x10) {
        x = w - x;
    }
    *y = hi;
    pos->full = x;
}

void func_8001E698(Sprite *arg0, s32 arg1) {
    arg0->unk_44 = arg1;
    arg0->unk_48 = arg1;
    arg0->unk_4D = 0;
    arg0->unk_22 = (u16) (arg0->unk_22 | 0x800);
    func_8001E6CC(arg0);
}

void func_8001E6CC(Sprite *arg0) {
    if (!(arg0->unk_6C & 0x4000)) {
        func_8001E700(arg0);
    }
}

void func_8001E700(Sprite *sprite) {
    Sprite *head;

    if (sprite->unk_6C & 0x4000) {
        func_8001B5E8(0x10);
    }
    sprite->unk_6C |= 0x4000;
    head = D_801D8584;
    D_801D8584 = sprite;
    sprite->unk_40 = head;
}

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

void func_8001E7C8(Sprite *arg0) {
    Sprite *next;
    Sprite *p;

    if (!(arg0->unk_6C & 0x4000)) {
        func_8001B5E8(0x10);
    }
    arg0->unk_6C = (u16) (arg0->unk_6C & 0xBFFF);
    func_80020AF4(arg0);
    next = D_801D8584;
    if (arg0 == next) {
        next = arg0->unk_40;
        D_801D8584 = next;
        return;
    }
    do {
        p = next;
        next = p->unk_40;
        if (next == NULL) {
            func_8001B5E8(0x11);
        }
    } while (next != arg0);
    p->unk_40 = arg0->unk_40;
}

void func_8001E878(void) {
    D_800AA248.unk_0 = *D_800AA248.unk_20->unk_5C++;
    if (D_800AA248.unk_0 == 0) {
        D_800AA248.unk_7A = 1;
    } else {
        D_800AA248.unk_7A = 0;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001E8C0);

void func_8001E94C(s32 arg0, s32 arg1, Sprite *arg2) {
    SpriteImage *temp_v1;

    temp_v1 = arg2->unk_34;
    arg2->unk_28.s.lo = (s16) (arg0 - temp_v1->unk_8.u.lo);
    arg2->unk_28.s.hi = (s16) (arg1 - temp_v1->unk_8.u.hi);
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

#ifdef NON_MATCHING
/* 99.2 %: the two shifts of `mix` come out in the other order (prev first); with the other operand order the
 * registers a1/a2 swap instead. The random number generator (its state D_801FAF6C/6E/70). */
s16 func_8001EA10(void) {
    u16 prev;
    u16 next;
    s32 mix;
    s16 result;

    prev = D_801FAF6E;
    next = prev + 1;
    mix = ((prev * 8) + (D_801FAF6C << 5)) - 1;
    D_801FAF6E = next;
    result = prev ^ ((D_801FAF70 ^ mix) - D_801FAF6C);
    if ((D_801FAF6C << 0x10) < (next << 0x10)) {
        D_801FAF6E = prev + 2;
    }
    D_801FAF70 = D_801FAF6C;
    D_801FAF6C = (u16) result;
    return result;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001EA10);
#endif

s32 func_8001EA78(void) {
    s16 temp_s0;
    s32 temp_lo;

    temp_s0 = func_8001EA10();
    temp_lo = temp_s0 * func_8001EA10();
    D_801E0D6C = temp_lo;
    return temp_lo;
}

/* 84 %: the original's divu keeps the assembler's divide-by-zero check (bnez/break 7); the C, whose divisor is known non-zero on that path, gets none */
#ifdef NON_MATCHING
s32 func_8001EAC4(s32 range) {
    if (range == 0) {
        return 0;
    }
    return func_8001EA78() % (u32) range + 1;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001EAC4);
#endif

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

void func_8001EC74(s32 kind, s16 value) {
    Sprite *head;
    Sprite *sprite;

    head = &D_801E28C0;
    sprite = head->unk_0;
    if (sprite != head) {
        do {
            if (sprite->unk_70 == kind) {
                sprite->unk_74 = value;
            }
            sprite = sprite->unk_0;
        } while (sprite != head);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001ECB4);

void func_8001ED54(TextMessage *arg0) {
    func_8001F39C(arg0);
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

void func_8001EDE4(void) {
    D_801D8588.unk_20 = 0x8002;
    D_801D8588.unk_24 = 0x10001;
    D_801D8588.unk_28 = 0x8101;
    func_8001EEA0();
}

void func_8001EE24(void) {
    D_801D8588.unk_20 = 0x8002;
    D_801D8588.unk_24 = 0x10000;
    D_801D8588.unk_28 = 0x8101;
    func_8001EEA0();
}

void func_8001EE60(void) {
    D_801D8588.unk_20 = 0x8002;
    D_801D8588.unk_24 = 0x10002;
    D_801D8588.unk_28 = 0x8101;
    func_8001EEA0();
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001EEA0);

void func_8001F268(void) {
}

void func_8001F270(void) {
    u16 y;

    y = D_801D8588.unk_36 + D_801D8588.unk_32;
    D_801D8588.unk_C = D_801D8588.unk_34;
    D_801D8588.unk_E = y;
    D_801D8588.unk_36 = y;
    func_8001F464();
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001F2B0);

void func_8001F358(void) {
    sprintf(D_801FAF7C, D_801D8588.unk_1C);
    D_801D8588.unk_1C = D_801FAF7C;
}

void func_8001F39C(TextMessage *msg) {
    D_801D8588.unk_0 = 0;
    D_801D8588.unk_4 = msg->unk_10;
    D_801D8588.unk_8 = msg->unk_C;
    D_801D8588.unk_C = msg->unk_8;
    D_801D8588.unk_E = msg->unk_A;
    D_801D8588.unk_10 = msg->unk_4;
    D_801D8588.unk_14 = msg->unk_0;
    D_801D8588.unk_18 = msg->unk_14;
    D_801D8588.unk_1C = msg->unk_18;
}

void func_8001F400(void) {
    Glyph *glyph;

    glyph = func_8001B128(D_801D8588.unk_14[0x27]);
    D_801D8588.unk_30 = glyph->unk_4 >> 1;
    D_801D8588.unk_32 = glyph->unk_6 + (glyph->unk_6 >> 1);
}

void func_8001F464(void) {
    s32 shift;
    s32 kind;

    kind = D_801D8588.unk_24 & 3;
    shift = 0;
    if (kind != 1) {
        if (kind != 0) {
            if (kind == 2) {
                shift = func_8001F50C(D_801D8588.unk_1C);
            }
        }
    } else {
        shift = (s16) func_8001F50C(D_801D8588.unk_1C) >> 1;
    }
    D_801D8588.unk_C -= shift;
}

void func_8001F4EC(void) {
}

void func_8001F4F4(void) {
    D_801D8588.unk_2E = 1;
    D_801D8588.unk_2C = 1;
}

s32 func_8001F50C(u8 *text) {
    s32 saved0;
    s32 saved30;
    s32 saved10;
    s32 width;
    u8 *p;
    u8 c;

    saved0 = D_801D8588.unk_0;
    saved30 = *(s32 *) &D_801D8588.unk_30;
    saved10 = D_801D8588.unk_10;
    p = text;
    func_8001F400();
    c = *p;
    width = 0;
    while (c != 0 && c != 13 && c != 10) {
        if (D_801D8588.unk_24 & 0x2000) {
            width += (s16) D_801D8588.unk_10;
        } else {
            if (c == 0x20) {
                width += D_801D8588.unk_30 + (s16) D_801D8588.unk_10;
            } else {
                width += func_8001B128(D_801D8588.unk_14[*p - 0x21])->unk_4 + (s16) D_801D8588.unk_10;
            }
        }
        p++;
        c = *p;
    }
    D_801D8588.unk_0 = saved0;
    *(s32 *) &D_801D8588.unk_30 = saved30;
    D_801D8588.unk_10 = saved10;
    return width;
}

void func_8001F61C(u8 *text, s16 x, s16 y, s32 spacing, s32 arg4, s32 *glyphs, s32 kind, s32 arg7) {
    D_801D8588.unk_0 = 0;
    D_800AA2EC = arg4;
    if (kind == 0) {
        D_801D8588.unk_4 = func_8001EDE4;
    } else if (kind == 1) {
        D_801D8588.unk_4 = func_8001EE24;
    } else {
        D_801D8588.unk_4 = func_8001EE60;
    }
    D_801D8588.unk_8 = arg4;
    D_801D8588.unk_C = x;
    D_801D8588.unk_E = y;
    D_801D8588.unk_10 = spacing;
    D_801D8588.unk_14 = glyphs;
    D_801D8588.unk_18 = arg7;
    D_801D8588.unk_1C = text;
    func_8001ED7C();
}

void func_8001F6B4(void) {
    func_80062E44();
    D_801D8750 = 0xFFFF;
    func_80063270();
}

void func_8001F6E4(void) {
    func_800631B4();
}

void func_8001F704(void) {
    func_80063214();
}

void func_8001F724(u16 id) {
    if (id == 0xFFFF) {
        func_8001F6B4();
    } else {
        func_80062DCC(id);
    }
}

void func_8001F760(void) {
    func_8001F7F8(2);
}

void func_8001F780(void) {
    u8 value;

    if (D_800AA2DC != 0) {
        value = 2;
    } else {
        value = D_8007B080[D_801FA960];
    }
    func_8001F7F8(value);
}

void func_8001F7CC(s32 arg0, s32 arg1) {
    func_80062DEC(arg1 & 0xFFFF, arg0 & 0xFFFF, 0);
}

/* 97 %: the table base and the index swap registers (base in v1, index in v0 in the original) */
#ifdef NON_MATCHING
void func_8001F7F8(s32 id) {
    s32 word;

    if ((id & 0xFFFF) != D_801D8750) {
        word = D_8007B100[(id & 0x7FFF) - 1];
        D_801D8750 = id;
        func_80063084(word, id);
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001F7F8);
#endif

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001F848);

void func_8001F9BC(void) {
    func_8001F9DC();
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8001F9DC);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800205AC);

void func_80020704(void) {
    for (D_800AA248.unk_20 = D_801D8584; D_800AA248.unk_20 != NULL; D_800AA248.unk_20 = D_800AA248.unk_20->unk_40) {
        func_8002075C();
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8002075C);

#ifdef NON_MATCHING
/* 98.8 %: register names only (the entry read into v0 in the original, a0 here) */
void func_80020AF4(s32 id) {
    s32 *p;
    s32 *dst;
    s32 key;
    s32 value;

    D_800AA248.unk_0 = id;
    if (D_801FB188 != 0) {
        p = D_800AA248.unk_30;
        if ((u8 *) p < D_801E2154 || D_801E2154 + 0x740 < (u8 *) p) {
            func_8001B5E8(0xB);
        }
        do {
            key = *p++;
            D_800AA248.unk_38 = key;
            if (key == 0) {
                return;
            }
            value = *p++;
            D_800AA248.unk_38 = value;
        } while (value != D_800AA248.unk_0);
        do {
            dst = p - 2;
            key = *p++;
            dst[0] = key;
            dst[1] = *p++;
        } while (key != 0);
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80020AF4);
#endif

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80020BA0);

void func_80020CE4(s32 arg0, s32 arg1) {
    D_801D3D7C = 0;
    SetDispMask(1);
    D_801FA9A4 = arg1 & 0xFFFF;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80020D20);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80020DDC);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80020EDC);

void func_80020FC8(Sprite *arg0) {
    Sprite *temp_a0;

    temp_a0 = arg0->unk_50;
    if (temp_a0 != NULL) {
        func_8001E4B0(temp_a0);
        arg0->unk_50 = NULL;
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

void func_80021644(Unk22D58 *ai) {
    if (ai->unk_C != 0) {
        ai->unk_1C = 0x5A;
        ai->unk_8 = 0x64;
        func_800242A8();
        func_8002423C(ai);
        ai->unk_A = 0;
        if (ai->unk_6 == 0x11) {
            func_8003EB5C(&D_80097DF0, D_800AA268);
        } else {
            func_8003EB5C(&D_8008B9C8, D_800AA268);
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800216C8);

void func_8002180C(Unk22D58 *ai) {
    Anim *anim;

    if (D_800AA248.unk_20->unk_6C & 0x80) {
        if (D_801D8740 == 0) {
            func_80023F64(ai);
            return;
        }
        func_80023064((s16) (D_801F9ACE + 0x75));
        func_800232AC(0x36000);
        ai->unk_C = 0;
        return;
    }
    if (ai->unk_C != 2) {
        func_800232AC(0x36000);
        if (func_80023114(ai) == 1) {
            ai->unk_C = 2;
            D_800AA248.unk_20->unk_C >>= 2;
            D_800AA248.unk_20->unk_10 = 0;
            ai->unk_30 = 0;
            if (ai->unk_6 == 0x11) {
                func_8003EB5C(&D_80097950, D_800AA248.unk_20);
            } else {
                func_8003EB5C(&D_8008B558, D_800AA248.unk_20);
            }
            return;
        }
        if (ai->unk_6 == 0x11) {
            if (ai->unk_3A != 2) {
                anim = &D_80097340;
            } else {
                anim = &D_80097640;
            }
        } else {
            if (ai->unk_3A != 2) {
                anim = &D_8008AE40;
            } else {
                anim = &D_8008B248;
            }
        }
        func_8003EB5C(anim, D_800AA248.unk_20);
        if (func_80023C58(D_801F9ACE + 0x75, ai) == 0) {
            D_800AA248.unk_20->unk_C = 0;
            return;
        }
        if (ai->unk_3A == 2) {
            ai->unk_C = ai->unk_3A;
            D_800AA248.unk_20->unk_C >>= 2;
            D_800AA248.unk_20->unk_10 = 0;
            ai->unk_30 = 0;
            ai->unk_3A = 0;
            func_800232D8(ai);
            func_80023CFC(ai);
            return;
        }
        ai->unk_3A = 0;
        ai->unk_C = 0;
        D_800AA248.unk_20->unk_10 = 0;
        ai->unk_30 = 0;
        ai->unk_A++;
        func_800232AC(0x36000);
        if (ai->unk_6 == 0x11) {
            func_8003EB5C(&D_80097340, D_800AA248.unk_20);
        } else {
            func_8003EB5C(&D_8008AE40, D_800AA248.unk_20);
        }
    }
}

void func_80021A80(Unk22D58 *ai) {
    if (ai->unk_C != 0) {
        ai->unk_C = 0;
        D_800AA248.unk_20->unk_C = 0;
        D_800AA248.unk_20->unk_10 = 0;
        ai->unk_30 = 0;
        ai->unk_34 = 0;
        ai->unk_A++;
    }
}

void func_80021ACC(Unk22D58 *ai) {
    ai->unk_C = 0;
    if (ai->unk_6 == 0x11) {
        func_8003EB5C(&D_80097340, D_800AA268);
    } else {
        func_8003EB5C(&D_8008AE40, D_800AA268);
    }
    if (func_80023C58(D_801F9ACE + 0xA5, ai) == 1) {
        ai->unk_A++;
        func_800232AC(0x36000);
        D_800AA268->unk_10 = 0;
        ai->unk_30 = 0;
        return;
    }
    D_800AA268->unk_C = 0;
    ai->unk_34 = 0;
}

void func_80021B94(Unk22D58 *ai) {
    ai->unk_C = 0;
    if (ai->unk_6 == 0x11) {
        func_8003EB5C(&D_80097340, D_800AA268);
    } else {
        func_8003EB5C(&D_8008AE40, D_800AA268);
    }
    if (func_80023C58(D_801F9ACE + 0x45, ai) == 1) {
        ai->unk_A++;
        func_800232AC(0x36000);
        D_800AA268->unk_10 = 0;
        ai->unk_30 = 0;
        return;
    }
    D_800AA268->unk_C = 0;
    ai->unk_34 = 0;
}

void func_80021C5C(Unk22D58 *ai) {
    ai->unk_C = 0;
    if (ai->unk_6 == 0x11) {
        func_8003EB5C(&D_80097340, D_800AA268);
    } else {
        func_8003EB5C(&D_8008AE40, D_800AA268);
    }
    if (func_80023C58(D_801F9ACE + 0xC5, ai) == 1) {
        ai->unk_A++;
        func_800232AC(0x36000);
        D_800AA268->unk_10 = 0;
        ai->unk_30 = 0;
        return;
    }
    D_800AA268->unk_C = 0;
    ai->unk_34 = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80021D24);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80021DA8);

void func_80021FDC(Unk22D58 *ai) {
    s16 a;
    s16 b;
    s32 result;
    s16 side;

    if (ai->unk_C != 0) {
        if (ai->unk_6 == 0x11) {
            func_8003EB5C(&D_80097640, D_800AA268);
        } else {
            func_8003EB5C(&D_8008B248, D_800AA268);
        }
        result = func_80023474(ai);
        if (result == 1) {
            func_80023CFC(ai);
            ai->unk_C = 0;
            ai->unk_A++;
            D_800AA248.unk_20->unk_C = 0;
            D_800AA248.unk_20->unk_10 = 0;
            ai->unk_30 = 0;
            ai->unk_2A = result;
            ai->unk_22 = 0x30;
            func_80024418(&a, &b, ai);
            side = 2;
            if (b < a) {
                side = 1;
            }
            ai->unk_38 = side;
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800220D0);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800221BC);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800222E8);

/* 92 %: the result is masked into its own register before the stores and the four stores are scheduled in source order; the C copies the result and moves the counter's store first */
#ifdef NON_MATCHING
void func_8002235C(Unk22D58 *ai) {
    u16 result;

    if (ai->unk_C != 0) {
        if (ai->unk_6 == 0x11) {
            func_8003EB5C(&D_80097640, D_800AA268);
        } else {
            func_8003EB5C(&D_8008B248, D_800AA268);
        }
        result = func_80023AC0(ai);
        if (result == 1) {
            ai->unk_2A = result;
            ai->unk_22 = 0x30;
            ai->unk_C = 0;
            ai->unk_A++;
            if (ai->unk_38 != 2) {
                if (ai->unk_6 == 0x11) {
                    func_8003EB5C(&D_80097750, D_800AA268);
                } else {
                    func_8003EB5C(&D_8008B358, D_800AA268);
                }
            } else {
                if (ai->unk_6 == 0x11) {
                    func_8003EB5C(&D_80097850, D_800AA268);
                } else {
                    func_8003EB5C(&D_8008B458, D_800AA268);
                }
            }
            return;
        }
        D_800AA268->unk_C = 0;
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8002235C);
#endif

void func_80022490(Unk22D58 *ai) {
    if (ai->unk_C == 0) {
        if (D_800AA268->unk_C != 0) {
            goto done;
        }
    } else {
        if (D_800AA268->unk_C == 0) {
            if (ai->unk_6 == 0x11) {
                func_8003EB5C(&D_80097640, D_800AA268);
            } else {
                func_8003EB5C(&D_8008B248, D_800AA268);
            }
        } else if (ai->unk_6 == 0x11) {
            func_8003EB5C(&D_80097340, D_800AA268);
        } else {
            func_8003EB5C(&D_8008AE40, D_800AA268);
        }
    done:
        if (func_80023B20(ai) == 1) {
            ai->unk_2A = 0;
            ai->unk_22 = 0x30;
            ai->unk_A++;
        }
    }
}

void func_80022578(Unk22D58 *ai) {
    if (ai->unk_C != 0) {
        if (ai->unk_6 == 0x11) {
            func_8003EB5C(&D_80097340, D_800AA268);
        } else {
            func_8003EB5C(&D_8008AE40, D_800AA268);
        }
        if (func_80023620(ai) == 1) {
            ai->unk_22 = 0x30;
            ai->unk_A++;
            ai->unk_C = 0;
            if (ai->unk_6 == 0x11) {
                func_8003EB5C(&D_80097C90, D_800AA268);
            } else {
                func_8003EB5C(&D_8008B898, D_800AA268);
            }
        }
    }
}

void func_80022640(Unk22D58 *ai) {
    if (func_80023114() == 0) {
        if (ai->unk_30 == 0) {
            func_800232D8(ai);
            if (func_800231E4(ai) == 1) {
                ai->unk_30 = -0x380;
            } else {
                ai->unk_2A = 1;
            }
            if (ai->unk_6 == 0x11) {
                func_8003EB5C(&D_80097374, D_800AA268);
            } else {
                func_8003EB5C(&D_8008AE8C, D_800AA268);
            }
        }
    } else {
        ai->unk_C = 0;
        ai->unk_2A = 0;
        ai->unk_A++;
        D_800AA248.unk_20->unk_C >>= 2;
        if (ai->unk_6 == 0x11) {
            func_8003EB5C(&D_80097950, D_800AA248.unk_20);
        } else {
            func_8003EB5C(&D_8008B558, D_800AA248.unk_20);
        }
    }
}

void func_80022744(Unk22D58 *ai) {
    if (func_80023114() == 0) {
        ai->unk_2A = 0;
        if (ai->unk_6 == 0x11) {
            func_8003EB5C(&D_80097340, D_800AA268);
        } else {
            func_8003EB5C(&D_8008AE40, D_800AA268);
        }
    } else {
        ai->unk_C = 0;
        ai->unk_2A = 0;
        ai->unk_A++;
        D_800AA248.unk_20->unk_C >>= 2;
        if (ai->unk_6 == 0x11) {
            func_8003EB5C(&D_80097950, D_800AA248.unk_20);
        } else {
            func_8003EB5C(&D_8008B558, D_800AA248.unk_20);
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80022814);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80022AC8);

void func_80022B64(Unk22D58 *ai) {
    if (ai->unk_C != 0) {
        ai->unk_C = 0;
        D_800AA248.unk_20->unk_C = 0;
        ai->unk_A = 3;
        if (ai->unk_6 == 0x11) {
            func_8003EB5C(&D_800973DC, D_800AA248.unk_20);
        } else {
            func_8003EB5C(&D_8008AF24, D_800AA248.unk_20);
        }
    }
}

void func_80022BD8(Unk22D58 *ai) {
    if (func_80023CB8() == 1) {
        ai->unk_C = 0;
        ai->unk_A = 4;
        func_800232AC(0x36000);
        D_800AA248.unk_20->unk_10 = 0;
        ai->unk_30 = 0;
        if (ai->unk_6 == 0x11) {
            func_8003EB5C(&D_80097340, D_800AA248.unk_20);
        } else {
            func_8003EB5C(&D_8008AE40, D_800AA248.unk_20);
        }
    }
}

void func_80022C68(Unk22D58 *ai) {
    s16 kind;

    if (ai->unk_10 == NULL) {
        func_800377B4(ai);
    }
    func_800232D8(ai);
    kind = func_8002439C(ai);
    if (kind == 1) {
        func_800232AC(0x28000);
        return;
    }
    if (func_8002326C(kind) == 1) {
        if (ai->unk_6 == 0x11) {
            func_8003EB5C(&D_80097C90, D_800AA268);
        } else {
            func_8003EB5C(&D_8008B898, D_800AA268);
        }
        ai->unk_C = 0;
    } else {
        ai->unk_C = 1;
    }
    D_800AA268->unk_C >>= 1;
    ai->unk_A = 5;
}

void func_80022D58(Unk22D58 *arg0) {
    if (arg0->unk_C != 0) {
        arg0->unk_A = 6;
        func_80022EC0();
        arg0->unk_2A = 1;
    }
}

void func_80022D98(Unk22D58 *ai) {
    if (func_80023114() == 1 || D_800AA268->unk_10 == 0 || D_800AA268->unk_18.s.hi >= 0xC0) {
        func_800232AC(0x28000);
        ai->unk_30 = 0;
        D_800AA248.unk_20->unk_10 = 0;
        ai->unk_A = 7;
        ai->unk_2A = 0;
        if (ai->unk_6 == 0x11) {
            func_8003EB5C(&D_80097340, D_800AA248.unk_20);
        } else {
            func_8003EB5C(&D_8008AE40, D_800AA248.unk_20);
        }
    }
}

void func_80022E58(Unk22D58 *ai) {
    func_80023FAC();
    if (ai->unk_C != 2) {
        if (ai->unk_6 == 0x11) {
            func_8003EB5C(&D_80097340, D_800AA268);
        } else {
            func_8003EB5C(&D_8008AE40, D_800AA268);
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80022EC0);

void func_80023064(s32 arg0) {
    D_800AA268->unk_18.u.hi = (s16) (D_801F9ACE + arg0);
}

void func_80023080(Unk22D58 *ai) {
    func_8002423C(ai);
    D_800AA248.unk_20->unk_22 &= ~0x10;
    ai->unk_8 = 1;
    ai->unk_1C = func_8001EB10(0xC8, 0x64);
    D_800AA248.unk_20->unk_18.full = 0x02000000;
    D_800AA248.unk_20->unk_14.full = 0x02000000;
    ai->unk_A = 0;
    D_800AA248.unk_20->unk_C = 0;
    D_800AA248.unk_20->unk_10 = 0;
    ai->unk_30 = 0;
}

#ifdef NON_MATCHING
/* 88.9 %: the second branch keeps the address of D_801F9AC8 in a register across the block and reuses it; the C reloads it */
u16 func_80023114(void) {
    s32 x;
    s32 d;
    s32 dist;

    x = D_800AA268->unk_14.full;
    if (D_800AA268->unk_C < 0) {
        if (D_801F9AC8 >= x) {
            x += D_801D8864;
        }
        x -= D_801F9AC8;
        return x <= 0x480000;
    }
    if (D_800AA268->unk_C > 0) {
        if (D_801F9AC8 >= x) {
            d = x - D_801F9AC8;
            dist = d;
            if (d < 0) {
                dist = -dist;
            }
            if (dist > 0xC7FFFF) {
                x += D_801D8864;
            }
        }
        d = x - D_801F9AC8;
        return (u32) (d + 0xFEA20000) <= 0x01C20000;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80023114);
#endif

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800231E4);

u16 func_8002326C(s16 x) {
    if (D_800AA268->unk_22 & 0x10) {
        return x <= 0;
    }
    return x >= 0;
}

void func_800232AC(s32 arg0) {
    s32 var_a0;

    var_a0 = arg0;
    if (D_800AA268->unk_22 & 0x10) {
        var_a0 = -var_a0;
    }
    D_800AA268->unk_C = var_a0;
}

void func_800232D8(Unk22D58 *ai) {
    Monster *target;
    Sprite *sprite;
    s16 y;
    u16 x;

    target = ai->unk_10;
    if (target != NULL) {
        sprite = target->unk_68;
        if (!(target->unk_58 & 1) || (target->unk_5A == 0x37)) {
            func_800377B4(ai);
            target = ai->unk_10;
            if ((target == NULL) || !(target->unk_58 & 1) || (target->unk_5A == 0x37)) {
                ai->unk_28 = 0x64;
                ai->unk_26 = (D_801F9ACA + 0xC8) & D_801D8866;
                return;
            }
            sprite = target->unk_68;
        }
        y = sprite->unk_18.u.hi - 0x16;
        if (y >= 0xE1) {
            y = 0x64;
        }
        ai->unk_28 = y;
        x = sprite->unk_14.u.hi;
        if (sprite->unk_22 & 0x10) {
            ai->unk_26 = x - 1;
        } else {
            ai->unk_26 = x + 0x10;
        }
    }
}

void func_800233E0(Unk22D58 *arg0) {
    s16 var_v0;
    Monster *temp_v0;
    Sprite *temp_v1;

    temp_v0 = arg0->unk_10;
    if (temp_v0 != NULL) {
        temp_v1 = temp_v0->unk_68;
        if (temp_v1 == NULL) {
            func_800377B4(arg0);
            return;
        }
        arg0->unk_28 = (s16) (temp_v1->unk_18.u.hi - 0x1E);
        arg0->unk_3C = (u16) temp_v1->unk_22;
        if (temp_v1->unk_22 & 0x10) {
            var_v0 = temp_v1->unk_14.u.hi - 1;
        } else {
            var_v0 = temp_v1->unk_14.u.hi + 0x10;
        }
        arg0->unk_26 = var_v0;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80023474);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80023620);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80023764);

#ifdef NON_MATCHING
/* 99.9 %: one instruction, the negation of the copy (negu v0,v0) comes out as negu v0,v1 */
u16 func_800239F4(Unk22D58 *ai) {
    Monster *target;
    Sprite *sprite;
    s32 dy;
    s32 ady;
    s32 speed;

    target = ai->unk_10;
    if (target != NULL) {
        sprite = target->unk_68;
        if (sprite == NULL) {
            func_800377B4(ai);
            return func_800239F4(ai);
        }
        dy = (s16) ((sprite->unk_18.u.hi - 0x58) - D_800AA268->unk_18.u.hi);
        ady = dy;
        if (dy < 0) {
            ady = -ady;
        }
        if (ady < 0xB) {
            D_800AA268->unk_10 = 0;
            return 1;
        }
        speed = 0xFFFE0000;
        if (dy >= 0) {
            speed = 0x10000;
        }
        D_800AA268->unk_10 = speed | 0x8000;
        return 0;
    }
    D_800AA268->unk_10 = 0x18000;
    return 0;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800239F4);
#endif

#ifdef NON_MATCHING
/* 99.8 %: the negation reads the copy's register in the original (negu v0, v0), the s16 delta's here. */
u16 func_80023AC0(Unk22D58 *ai) {
    s16 delta;
    s32 dist;
    s32 step;

    delta = ai->unk_28 - D_800AA268->unk_18.u.hi;
    dist = delta;
    if (delta < 0) {
        dist = -dist;
    }
    if (dist < 0xB) {
        D_800AA268->unk_10 = 0;
        return 1;
    }
    step = 0xFFFE0000;
    if (delta >= 0) {
        step = 0x10000;
    }
    D_800AA268->unk_10 = step | 0x8000;
    return 0;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80023AC0);
#endif

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80023B20);

#ifdef NON_MATCHING
/* 99.8 %: the negation reads the copy's register in the original (negu v0, v0), the s16 delta's here. */
u16 func_80023C58(s16 arg0, Unk22D58 *ai) {
    s16 delta;
    s32 dist;
    s32 step;

    delta = arg0 - D_800AA268->unk_18.u.hi;
    dist = delta;
    if (delta < 0) {
        dist = -dist;
    }
    if (dist < 0xB) {
        D_800AA268->unk_10 = 0;
        return 1;
    }
    step = 0xFFFE0000;
    if (delta >= 0) {
        step = 0x10000;
    }
    D_800AA268->unk_10 = step | 0x8000;
    return 0;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80023C58);
#endif

u16 func_80023CB8(void) {
    if (D_800AA268->unk_18.full - D_801F9ACC <= 0x2FFFFF) {
        return 1;
    }
    D_800AA268->unk_10 = 0xFFFE8000;
    return 0;
}

void func_80023CFC(Unk22D58 *ai) {
    Monster *target;
    Sprite *sprite;
    u16 tx;
    u16 mx;
    s32 dx;

    target = ai->unk_10;
    if (target != NULL) {
        sprite = target->unk_68;
        if (sprite == NULL) {
            func_800377B4(ai);
            return;
        }
        tx = sprite->unk_14.u.hi;
        mx = D_800AA268->unk_14.u.hi;
        dx = (s16) (tx - mx);
        if (dx < 0) {
            dx = -dx;
        }
        if (dx >= 0x258) {
            if ((s16) mx >= D_801F9ACA) {
                tx += D_801D8866;
            } else {
                mx += D_801D8866;
            }
        }
        if ((s16) mx >= (s16) tx) {
            ai->unk_38 = 1;
            if (ai->unk_6 == 0x11) {
                func_8003EB5C(&D_80097850, D_800AA268);
            } else {
                func_8003EB5C(&D_8008B458, D_800AA268);
            }
        } else {
            ai->unk_38 = 2;
            if (ai->unk_6 == 0x11) {
                func_8003EB5C(&D_80097750, D_800AA268);
            } else {
                func_8003EB5C(&D_8008B358, D_800AA268);
            }
        }
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80023E30);

void func_80023F64(Unk22D58 *arg0) {
    if (D_800AA268->unk_6C & 0x80) {
        func_800242A0();
        func_80023080(arg0);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80023FAC);

void func_800240F0(Unk22D58 *arg0) {
    if (D_800AA268->unk_6C & 0x80) {
        func_800242A0();
        func_80023080(arg0);
    }
}

/* 79 %: the search loop keeps its test at the top (no rotation) and copies k on the way out; while, for(;;), do-while and goto forms all rotate it or keep the extra copy */
#ifdef NON_MATCHING
u16 func_80024138(Unk22D58 *ai) {
    s32 used;
    s16 k;
    s32 bit;

    if (D_801E289A == 0) {
        used = D_801E2A50 & 7;
        if (used == 7) {
            used = 0;
        }
        k = func_8001EB10(0x1F, 0) & 3;
        if (k == 3) {
            k = 0;
        }
    loop:
        if (used & D_8007BA20[k]) {
            if (++k >= 3) {
                k = 0;
            }
            goto loop;
        }
        ai->unk_24 = k;
        bit = 1;
        if (k != 0) {
            bit = 4;
            if (k == 1) {
                bit = 2;
            }
        }
        D_801E2A50 = used | bit;
        return k;
    }
    ai->unk_24 = 3;
    return 3;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80024138);
#endif

void func_8002423C(Unk22D58 *arg0) {
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

void func_800242A8(void) {
    D_800AA248.unk_20->unk_14.full = D_801F9AC8 - 0x1BC0000;
    D_800AA248.unk_20->unk_18.full = 0x2000000;
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800242D8);

/* 93 %: the second block loads the sprite's x into a temporary and copies it (lh v0; move v1,v0) and leaves the branch delay slot empty; the C loads it straight into its variable */
#ifdef NON_MATCHING
s16 func_8002439C(Unk22D58 *ai) {
    s16 x;
    s32 mx;
    s32 d;

    x = ai->unk_26;
    if (x < D_801F9ACA) {
        x += D_801D8866;
    }
    mx = D_800AA268->unk_14.s.hi;
    if (mx < D_801F9ACA) {
        mx += D_801D8866;
    }
    d = (s16) (mx - x);
    if (d < 0) {
        d = -d;
    }
    return d < 0x60;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8002439C);
#endif

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

void func_8002469C(s32 *p, s16 arg1, s16 arg2) {
    u16 count;
    s32 word;
    s32 x;
    s32 y;
    Unk1D110 *request;
    Sprite *sprite;
    s16 top;
    u16 right;

    count = *(u16 *) p;
    p++;
    if (count != 0) {
        do {
            word = *p++;
            x = *p++;
            y = *p++;
            request = func_8001D110();
            request->unk_1C = 1;
            request->unk_20 = arg2;
            request->unk_C = arg1;
            request->unk_0 = word & 0xFF7FFFFF;
            D_800AA248.unk_3C = request;
            sprite = func_8001DCB4();
            sprite->unk_14.u.hi = x;
            sprite->unk_8 = x;
            top = sprite->unk_1C.u.hi + (y - sprite->unk_30.u.hi);
            sprite->unk_A = top;
            sprite->unk_18.s.hi = top;
            if (arg2 != 0x300) {
                sprite->unk_6C |= 0x10;
            }
            if (word & 0x800000) {
                sprite->unk_22 |= 0x10;
                right = sprite->unk_14.u.hi + sprite->unk_30.u.lo;
                sprite->unk_8 = right;
                sprite->unk_14.u.hi = right;
            }
        } while (--count != 0);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800247E4);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8002488C);

void func_80024954(void) {
}

void func_8002495C(void) {
}

void func_80024964(void) {
}

void func_8002496C(Sprite *sprite) {
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

u16 func_800249B8(s32 arg0) {
    s32 result;

    result = arg0;
    if (D_801D8728 == 0) {
        if (func_80025C54(NULL) == 1) {
            result = 0x200;
        } else if (D_801FA984[0] != 0 && D_801FA984[1] != 0 && D_801FA984[2] != 0 && D_801FA960 < 0x4B) {
            D_801E1CAC = 0x4B;
            D_801FA960 = 0x4B;
        } else {
            D_801E1CAC++;
            D_801FA960++;
        }
    } else {
        D_800AA2DC = 0;
        D_801E28DC = 0;
        D_801D8728 = 0;
        D_801E1CAC++;
        D_801FA960++;
    }
    return result;
}

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

void func_80024AEC(void) {
    Unk1D3DC8 *block;
    u16 i;
    u16 j;

    block = D_801D3DC8;
    i = 0xD;
    D_801E29A4 = 0;
    D_801E1E40 = 0;
    D_801FA890 = 0;
    do {
        func_80025B3C(block);
        j = 0xF;
        do {
            func_80025B7C(&block->items[0xF - j]);
        } while (--j != 0);
        block += 1;
    } while (--i != 0);
    func_80024BB4();
    func_8003044C();
}

void func_80024BB4(void) {
    u8 *p;
    u16 i;

    p = D_801F998C;
    D_801F9AD8 = p;
    i = 5;
    do {
        func_80024C08(p);
    } while (--i != 0);
}

void func_80024C08(void *arg0) {
    memset(arg0, 0, 0x20);
}

/* 91 %: the height sum keeps -9 as an addiu on the definition's size before adding the x (the C narrows it to a 0xFFF7 constant hoisted out of the loop), and the definition pointer lands in a0 instead of a1 */
#ifdef NON_MATCHING
void func_80024C2C(void) {
    Unk24C2C *e;
    Unk1D3DC8 *rec;
    Unk25124Def *def;
    s16 n;
    u16 type;
    s16 tile;

    func_80024AEC();
    n = 0;
    rec = D_801D3DC8;
    e = func_80025C08(D_80082E94);
    do {
        def = e->unk_0;
        rec->unk_1E = ++n;
        rec->unk_20 = def;
        rec->unk_80 = e->unk_C;
        rec->unk_7A = e->unk_A;
        rec->unk_18 = e->unk_4;
        rec->unk_8A = e->unk_8;
        rec->unk_A = e->unk_14;
        rec->unk_14 = 0;
        rec->unk_8 = type = e->unk_12;
        if (type != 0x200) {
            tile = 0xC5;
            if (type == 0x300) {
                tile = 0xD5;
            }
        } else {
            tile = 0xCD;
        }
        rec->unk_6 = tile;
        rec->unk_4 = e->unk_10;
        rec->unk_E = e->unk_10 + (s16) (def->unk_4 - 9);
        if (def->unk_0.full != 4) {
            rec->unk_5C = def->unk_8;
            rec->unk_60 = def->unk_C;
            rec->unk_64 = def->unk_10;
            rec->unk_68 = def->unk_14;
            rec->unk_8C = def->unk_18;
            rec->unk_2 = def->unk_0.u.lo;
            rec->unk_1C = func_8001EB10(0x1E, 0) % 2 + 1;
            rec->unk_34 = 1;
            rec->unk_36 = 1;
            rec->unk_2A = 1;
            func_80024E08(rec);
        } else {
            func_80025124(rec);
        }
        rec++;
        e++;
    } while (e->unk_0 != NULL);
    D_801E29A4 = n;
    D_801E1E40 = n;
    func_800258C8();
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80024C2C);
#endif

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80024E08);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8002503C);

void func_80025124(Unk1D3DC8 *rec) {
    Unk25124Def *def;
    Unk1D110 *request;
    Sprite *sprite;
    Unk1D3DC8Item *item;
    u16 kind;

    def = rec->unk_20;
    rec->unk_58 = 1;
    rec->unk_5C = def->unk_C;
    rec->unk_60 = def->unk_10;
    rec->unk_2 = def->unk_0.u.lo;
    request = func_8001D110();
    request->unk_C = 0x728;
    request->unk_14.u.hi = rec->unk_6;
    request->unk_10.u.hi = rec->unk_4;
    kind = rec->unk_8;
    item = &rec->items[0];
    if (def->unk_8 != 0) {
        request->unk_0 = def->unk_8;
        D_800AA284 = request;
        sprite = func_8001DCB4();
        rec->items[0].unk_0 = sprite;
        sprite->unk_90 = item;
        sprite->unk_80 = kind;
        item->unk_8 = rec;
        item->unk_4 = 1;
        rec->unk_0 = 1;
        rec->unk_A = 0;
        rec->unk_70 = item;
        if (def == &D_800135E8) {
            rec->unk_74 = sprite->unk_18.u.hi - 0x5C;
            sprite->unk_70 = 0x72A;
            rec->unk_58 = 2;
            rec->unk_12 = 2;
            func_8002503C(rec, sprite);
        } else if (def == &D_8001687C) {
            rec->unk_74 = sprite->unk_18.u.hi - 0x3E;
            sprite->unk_70 = 0x72A;
            rec->unk_58 = 3;
            rec->unk_12 = 0x7D;
        } else {
            rec->unk_12 = 5;
            if ((D_800AA2DC != 0) && (func_8005F208() == 4)) {
                u16 y = sprite->unk_18.u.hi;

                rec->unk_58 = 0;
                rec->unk_74 = y - 0x1F;
            } else {
                rec->unk_74 = sprite->unk_18.u.hi - 0x3E;
            }
        }
        func_800252CC(rec);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800252CC);

void func_800253F0(Unk1D3DC8 *block, u32 which) {
    u16 n;
    Unk1D3DC8Item *item;
    Unk1D3DC8Part *part;

    n = block->unk_0;
    if (n != 0) {
        item = block->items;
        n--;
        if (n != 0) {
            do {
                part = &item->unk_C;
                if (which < 2) {
                    part->unk_14 = 1;
                }
                part = &item->unk_24;
                if (which == 0 || which == 3) {
                    part->unk_14 = 1;
                }
                part++;
                if (which == 0 || which == 2) {
                    part->unk_14 = 1;
                }
                item++;
            } while (--n != 0);
        }
    }
}

void func_8002546C(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80025474);

void func_800255E0(SpriteSlots *arg0) {
    Sprite *temp_a0;
    Sprite *temp_a0_2;
    Sprite *temp_a0_3;

    temp_a0 = arg0->unk_C;
    if (temp_a0 != NULL) {
        func_8001E4B0(temp_a0);
    }
    temp_a0_2 = arg0->unk_24;
    if (temp_a0_2 != NULL) {
        func_8001E4B0(temp_a0_2);
    }
    temp_a0_3 = arg0->unk_3C;
    if (temp_a0_3 != NULL) {
        func_8001E4B0(temp_a0_3);
    }
}

void func_80025648(SpriteSlots *arg0) {
    Sprite *temp_a0;
    Sprite *temp_a0_2;
    Sprite *temp_a0_3;

    temp_a0 = arg0->unk_1C;
    if (temp_a0 != NULL) {
        func_8001E4B0(temp_a0);
    }
    temp_a0_2 = arg0->unk_34;
    if (temp_a0_2 != NULL) {
        func_8001E4B0(temp_a0_2);
    }
    temp_a0_3 = arg0->unk_4C;
    if (temp_a0_3 != NULL) {
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

void func_800256CC(SpriteSlots *slots) {
    Unk22D58 *ai;
    Sprite *current;

    ai = slots->unk_14;
    current = D_800AA248.unk_20;
    if (ai != NULL) {
        D_800AA248.unk_20 = ai->unk_0;
        func_8003DAA0(ai);
    }
    ai = slots->unk_2C;
    if (ai != NULL) {
        D_800AA248.unk_20 = ai->unk_0;
        func_8003DAA0(ai);
    }
    ai = slots->unk_44;
    if (ai != NULL) {
        D_800AA248.unk_20 = ai->unk_0;
        func_8003DAA0(ai);
    }
    D_800AA248.unk_20 = current;
}

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
    Sprite *temp_a0;

    temp_a0 = arg0->unk_0;
    if (temp_a0 != NULL) {
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
    Sprite *temp_a0;

    temp_a0 = arg0->unk_0;
    if (temp_a0 != NULL) {
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

void func_80025B3C(Unk1D3DC8 *block) {
    if ((u32) block >= (u32) D_801D3DC8 && (u32) block < (u32) &D_801D3DC8[13]) {
        memset(block, 0, 0x98);
    }
}

void func_80025B7C(Unk1D3DC8Item *item) {
    if ((u32) item >= (u32) D_801D3DC8 && (u32) item <= (u32) &D_801D3DC8[13]) {
        memset(item, 0, sizeof(Unk1D3DC8Item));
    }
}

void func_80025BBC(Unk1D3DC8 *block) {
    s16 *p;
    u16 n;

    p = block->unk_3A;
    if (block->unk_38 == 0) {
        n = block->unk_0;
        block->unk_36 = 1;
        block->unk_38 = n + 9;
        n--;
        do {
            *p++ = 1;
        } while (--n != 0);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80025C08);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80025C54);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80025DF8);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80025E68);

void func_800267CC(Monster *monster) {
    s32 i;

    i = 0;
    if (monster->unk_0 == 5 && monster->unk_10 == 0x440000 && !(monster->unk_1A & 0xF)) {
        monster->unk_1A |= 3;
        func_8002A1AC(monster, 3);
        i = 0;
    }
    for (i = 0; i < 2; i++) {
        if (monster->unk_B4[i] != 0) {
            switch (monster->unk_0) {
            case 5:
                func_8005A2F4(monster, i);
                break;
            case 7:
                func_8005A964(monster);
                break;
            }
        }
    }
}

void func_800268BC(void) {
    u16 x3;
    u16 x1;
    u16 x2;
    Monster *m1;
    Monster *m2;
    Monster *m3;
    s16 r2;
    s16 r1;
    s16 r3;

    x3 = 0;
    x2 = 0;
    x1 = 0;
    m1 = &D_801E0B78[func_80025DF8(1)];
    m2 = &D_801E0B78[func_80025DF8(2)];
    m3 = &D_801E0B78[func_80025DF8(3)];
    if ((m1->unk_0 != 0) && (m3->unk_68 != NULL)) {
        x1 = m1->unk_68->unk_18.u.hi;
    }
    if ((m2->unk_0 != 0) && (m3->unk_68 != NULL)) {
        x2 = m2->unk_68->unk_18.u.hi;
    }
    if ((m3->unk_0 != 0) && (m3->unk_68 != NULL)) {
        x3 = m3->unk_68->unk_18.u.hi;
    }
    if ((s16) x1 <= (s16) x2) {
        if ((s16) x1 < (s16) x3) {
            if ((s16) x3 >= (s16) x2) {
                r3 = 8;
                r2 = 4;
                r1 = 1;
            } else {
                r2 = 8;
                r1 = 4;
                r3 = 1;
            }
        } else {
            r2 = 8;
            r1 = 4;
            r3 = 1;
        }
    } else {
        if ((s16) x3 >= (s16) x1) {
            r3 = 8;
            r1 = 4;
            r2 = 1;
        } else {
            if ((s16) x3 < (s16) x2) {
                r1 = 8;
                r2 = 4;
                r3 = 1;
            } else {
                r1 = 8;
                r3 = 4;
                r2 = 1;
            }
        }
    }
    m1->unk_128 = r1;
    m2->unk_128 = r2;
    m3->unk_128 = r3;
}

void func_80026A6C(void) {
    s16 var_a0;
    Monster *temp_s1;
    u16 var_s2;
    u16 var_s4;
    u16 var_s5;
    Monster *temp_a0;
    Monster *temp_s3;
    Sprite *temp_v1;
    Sprite *temp_v1_2;
    Sprite *temp_v1_3;

    var_s2 = 0xE1;
    var_s5 = 0xE1;
    var_s4 = 0xE1;
    temp_s3 = &D_801E0B78[func_80025DF8(1)];
    temp_s1 = &D_801E0B78[func_80025DF8(2)];
    temp_a0 = &D_801E0B78[func_80025DF8(3)];
    if (temp_s3->unk_0 != 0) {
        temp_v1 = temp_s3->unk_68;
        if (temp_v1 != NULL) {
            var_s4 = temp_v1->unk_18.u.hi;
        }
    }
    if (temp_s1->unk_0 != 0) {
        temp_v1_2 = temp_s1->unk_68;
        if (temp_v1_2 != NULL) {
            var_s5 = temp_v1_2->unk_18.u.hi;
        }
    }
    if (temp_a0->unk_0 != 0) {
        temp_v1_3 = temp_a0->unk_68;
        if (temp_v1_3 != NULL) {
            var_s2 = temp_v1_3->unk_18.u.hi;
        }
    }
    var_a0 = (s16) var_s4;
    if (var_a0 > (s16) var_s5) {
        if ((s16) var_s2 < (s16) var_s5) {
            D_801F9914 = (s16) var_s2;
        } else {
            D_801F9914 = (s16) var_s5;
        }
        return;
    }
    if (var_a0 > (s16) var_s2) {
        D_801F9914 = (s16) var_s2;
    } else {
        D_801F9914 = (s16) var_s4;
    }
}

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

#ifdef NON_MATCHING
/* 89.8 %: the zero stored into unk_3C/unk_3E goes through a register in the original (a variable that is 0 on both paths). */
void func_80026C4C(Monster *arg0) {
    u16 value;

    if ((arg0->unk_D0 & 2) && !(func_80027348() & 0xFFFF) && !(func_80026D54(arg0) & 0xFFFF)) {
        if (arg0->unk_18E == 0) {
            value = arg0->unk_3C;
            if ((value == 0) || (value = 0, ((func_80026D90(arg0) & 0xFFFF) == 0))) {
                arg0->unk_3E = value;
                arg0->unk_3C = value;
            }
            arg0->unk_18A = 0;
            func_80026CFC(arg0);
            return;
        }
        arg0->unk_5A = 0x40;
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80026C4C);
#endif

void func_80026CFC(Monster *arg0) {
    u16 temp_v1;

    D_800AA248.unk_38 = arg0->unk_0;
    func_80026E0C(arg0);
    temp_v1 = arg0->unk_5A;
    if ((temp_v1 != 2) && (temp_v1 != 0x4E)) {
        func_80026DE4(arg0)(arg0);
    }
}

s32 func_80026D54(Monster *monster) {
    u16 state;

    state = monster->unk_5A;
    if (state != 2 && state != 0x4E && state != 0x11 && monster->unk_5C == 0x16) {
        return 1;
    }
    return 0;
}

s32 func_80026D90(Monster *monster) {
    if (D_801D36FC == 0x240) {
        return 1;
    }
    switch (monster->unk_5A) {
    case 0:
    case 1:
    case 5:
    case 6:
        return 0;
    }
    return 1;
}

void (*func_80026DE4(void *arg0))(void *) {
    D_800AA248.unk_38 = ((Monster *) arg0)->unk_58;
    D_800AA248.unk_0 = ((Monster *) arg0)->unk_0;
    return func_800585C0;
}

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

#ifdef NON_MATCHING
/* 89.9 %: the call's argument is set up early and the (u16)(state - 5) truncation is kept in the original. */
void func_80026F98(Monster *arg0) {
    u16 temp_v1;

    D_800AA248.unk_20 = arg0->unk_68;
    if ((arg0->unk_D0 & 4) && !(func_800272FC() & 0xFFFF)) {
        temp_v1 = arg0->unk_5A;
        if (temp_v1 == 0x53) {
            arg0->unk_5A = 0x54U;
            return;
        }
        arg0->unk_152 = (u16) (temp_v1 - 5) < 2;
        arg0->unk_5A = 2U;
        func_800580F8(arg0);
        if (arg0->unk_18E == 0) {
            arg0->unk_5A = 0x4EU;
        }
        arg0->unk_1B0 = 0;
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80026F98);
#endif

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8002703C);

s32 func_800272B0(Monster *monster) {
    u16 *p;

    for (p = D_8007BFBC; *p != 0xFFFF; p++) {
        if (*p == monster->unk_5A) {
            return 0;
        }
    }
    return 1;
}

s32 func_800272FC(Monster *monster) {
    u16 *p;

    for (p = D_8007BFD4; *p != 0xFFFF; p++) {
        if (*p == monster->unk_5A) {
            return 0;
        }
    }
    return 1;
}

s32 func_80027348(Monster *monster) {
    u16 *p;

    for (p = D_8007BFEC; *p != 0xFFFF; p++) {
        if (*p == monster->unk_5A) {
            return 0;
        }
    }
    return 1;
}

void func_80027394(void) {
    s32 i;

    i = 0;
    do {
        i += 1;
        func_800273F4(&D_801E0B78[func_80025DF8(i)], i & 0xFFFF);
    } while (i < 3);
}

/* 99.8 %: the raw load of the previous direction (unk_CC) lands in a0 instead of v1 before its andi into s0, in both
 * branches; every other instruction matches (variable sharing, declaration order and types tried). */
#ifdef NON_MATCHING
void func_800273F4(Monster *monster, s32 arg1) {
    s16 *script;
    u16 buttons;
    u16 held;
    u16 dir;
    u16 prevDir;
    u32 bits;
    u16 raw;
    s32 key;

    if (D_801D36FC == 0x120) {
        if ((D_801F9AE0 == 2) || (D_801F9AE0 == 8) || (D_801F9AE0 == 0xD)) {
            script = monster->unk_1E4;
            if (script != NULL) {
                if ((D_801D3758 > script[0]) && (script[0] != 0x7FFF)) {
                    monster->unk_1E4 = script + 3;
                    script += 3;
                }
                buttons = script[2];
                if (buttons != 0) {
                    monster->unk_13E = 0x1A4;
                }
                held = monster->unk_C8;
                monster->unk_C8 = buttons;
                func_8002808C(buttons, held, monster);
                dir = script[1];
                if (dir != 0) {
                    monster->unk_13E = 0x1A4;
                }
                prevDir = monster->unk_CC;
                monster->unk_CC = dir;
                func_80028140(prevDir, monster, dir);
                func_80028140(prevDir, monster, dir);
                if (dir != 0) {
                    monster->unk_D4 = dir;
                }
                if (prevDir == dir) {
                    monster->unk_D8++;
                } else {
                    monster->unk_D8 = 0;
                }
            }
            return;
        }
    }
    key = arg1 & 0xFFFF;
    if (key != 0) {
        raw = D_801E0D7C >> D_8007C144[key - 1];
    } else {
        raw = 0;
    }
    bits = raw & 0x3FF;
    buttons = bits >> 4;
    if (buttons != 0) {
        monster->unk_13E = 0x1A4;
    }
    held = monster->unk_C8;
    monster->unk_C8 = buttons;
    func_8002808C(buttons, held, monster);
    dir = D_8007C124[bits & 0xF];
    if (dir != 0) {
        monster->unk_13E = 0x1A4;
    }
    prevDir = monster->unk_CC;
    monster->unk_CC = dir;
    func_80028140(prevDir, monster, dir);
    if (dir != 0) {
        monster->unk_D4 = dir;
    }
    if (prevDir == dir) {
        monster->unk_D8++;
    } else {
        monster->unk_D8 = 0;
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800273F4);
#endif

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800275F8);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80027878);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80027908);

void func_80027AB0(void) {
    s32 *p;
    s32 *q;
    s32 id;
    s32 i;

    p = D_801D3D9C;
    q = D_801D3D9C + 3;
    for (id = 1; id < 4; id++) {
        for (i = 0; i < 7; i++) {
            if ((u8) D_801FA8A0[i] == id) {
                break;
            }
        }
        if (i == 7) {
            *p = 0x12C0000;
            *q = 0;
        }
        p++;
        q++;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80027B20);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80027B78);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80027CB8);

void func_80027FC8(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80027FD0);

void func_8002808C(u16 buttons, u16 held, Monster *monster) {
    s16 pressed;
    u16 count;

    count = monster->unk_18C;
    pressed = 0;
    if ((buttons & 1) && !(held & 1)) {
        pressed = 1;
        count++;
    }
    if ((buttons & 2) && !(held & 2)) {
        pressed |= 2;
        count++;
    }
    if ((buttons & 4) && !(held & 4)) {
        pressed |= 4;
        count++;
    }
    if ((buttons & 8) && !(held & 8)) {
        pressed |= 8;
        count++;
    }
    monster->unk_D0 = pressed;
    monster->unk_18C = count;
    if (buttons & 4) {
        if (monster->unk_1AA == 0) {
            monster->unk_1AA = 1;
        }
    } else {
        monster->unk_1AA = 0;
    }
}

void func_80028140(s32 arg0, Monster *arg1, s32 arg2) {
    if ((arg0 & 0xFFFF) != (arg2 & 0xFFFF)) {
        arg1->unk_CE = arg2;
        return;
    }
    arg1->unk_CE = 0;
}

/* 78 %: the four stores come out in another order (the original stores the first word between the two halfwords); source order and other orders tried */
#ifdef NON_MATCHING
void func_80028160(void) {
    D_801D3D64.unk_26 = 0;
    D_801F9A30 = 0;
    D_801D3D64.unk_28 = 0;
    D_801F9ACC = 0;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80028160);
#endif

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

#ifdef NON_MATCHING
/* 84.7 %: register allocation (both inputs copied, the result built from a copy of the larger one) */
s16 func_80028ADC(s32 a, s32 b) {
    s32 lo;
    s32 hi;
    s32 mid;

    lo = a;
    hi = b;
    if ((s16) a >= (s16) b) {
        lo = b;
        hi = a;
    }
    mid = hi;
    return mid - ((s16) (mid - lo) >> 1);
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80028ADC);
#endif

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80028B1C);

void func_80029118(s16 arg0, u16 arg1) {
    if (D_801D3D64.unk_5E < arg0) {
        if (D_801D3D64.unk_5C & 1) {
            D_801F9ACC -= D_801D3D64.unk_5E << 16;
        }
        D_801D3D64.unk_5E = arg0;
        D_801D3D64.unk_5C = arg1;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80029170);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_800291DC);

#ifdef NON_MATCHING
/* 97.6 %: the original re-materializes a zero step (move v0, zero) on the unk_64 path; the step lives in another register here. */
void func_80029510(Unk29510 *arg0) {
    s32 old;
    s32 value;

    value = arg0->unk_8;
    old = value;
    if ((arg0->unk_F0 != 0) || (arg0->unk_64 != 0)) {
        value = arg0->unk_8 + arg0->unk_F0;
        if (value >= 0) {
            if (value > 0x440000) {
                value = 0x440000;
            }
            arg0->unk_F0 = 0;
            arg0->unk_8 = value;
        } else {
            value = 0;
            arg0->unk_F0 = 0;
            arg0->unk_8 = 0;
        }
    }
    func_8005DBC4(old, arg0, value);
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80029510);
#endif

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8002958C);

void func_800297B4(void) {
    Monster *monster;

    D_800AA248.unk_C = 0;
    D_800AA248.unk_10 = 0;
    D_800AA248.unk_8 = 7;
    do {
        monster = &D_801E0B78[D_800AA248.unk_8];
        if (monster->unk_58 & 1) {
            if (monster->unk_1B0 != 0) {
                D_800AA248.unk_10++;
            }
            if (monster->unk_1DE != 0) {
                D_800AA248.unk_C++;
            }
        }
    } while (--D_800AA248.unk_8 != 0);
    D_801E28C8 = D_800AA248.unk_C;
    D_801D8720 = D_800AA248.unk_10;
}

void func_8002987C(Monster *monster) {
    u16 action;
    s16 found;
    u16 *p;

    if ((D_800AA2DC != 0) && (D_8007BD78.unk_0 & 0x100)) {
        monster->unk_DC = 0;
        return;
    }
    action = monster->unk_5A;
    if ((action == 0x37) || (action == 0x26)) {
        return;
    }
    found = 0;
    if ((monster->unk_126 != 0x19) && !(monster->unk_68->unk_6C & 0x80) && (monster->unk_140 == 0)) {
        for (p = D_8007C1D4; *p != 0xFFFF; p++) {
            if (*p == action) {
                found = 1;
                break;
            }
        }
    }
    monster->unk_DC = found;
}

void func_8002994C(void) {
    if (D_801FB18C == 1) {
        D_801FB18C = func_8005E5C8();
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80029984);

void func_800299C4(void) {
    Sprite *sprite;
    Unk1D110 *request;
    s32 count;

    sprite = D_801E2894.unk_0;
    if ((D_801E1E40 == 0) || (D_801FA890 > 0) || (D_801FA734 != 0) || (D_801D3D8A != 0) || (D_801F9ACC != 0)) {
        if (sprite != NULL) {
            D_801E2894.unk_4 = 0;
            sprite->unk_18.s.hi = 0x190;
            D_801E2894.unk_6 = 0;
        }
    } else {
        count = D_801E2894.unk_4 + 1;
        if (count >= 0xB4) {
            if (sprite == NULL) {
                request = func_8001D110();
                D_800AA284 = request;
                request->unk_20 = 0x7000;
                request->unk_28 = &D_80093F78;
                request->unk_10.s.hi = 0x150;
                request->unk_0 = 0x4F0000A2;
                request->unk_14.s.hi = 0x190;
                request->unk_6 |= 0x20;
                sprite = func_8001DCB4();
                D_801E2894.unk_0 = sprite;
                sprite->unk_90 = &D_801E2894;
                D_801E2894.unk_6 = 1;
                return;
            }
            D_801E2894.unk_6 = 1;
            sprite->unk_18.s.hi = 0x7C;
            if (func_80029B80()) {
                sprite->unk_14.s.hi = 0x30;
                func_8003EB5C(&D_80093FAC, sprite);
            } else {
                sprite->unk_14.s.hi = 0x150;
                func_8003EB5C(&D_80093F78, sprite);
            }
            return;
        }
        D_801E2894.unk_4 = count;
        if (sprite != NULL) {
            sprite->unk_18.s.hi = 0x190;
            D_801E2894.unk_6 = 0;
        }
    }
}

void func_80029B54(void) {
    memset(&D_801E2894, 0, 8);
}

/* 93 %: the distance's sign extension and the abs land in other registers (sll/sra into a0 before the negu) */
#ifdef NON_MATCHING
u16 func_80029B80(void) {
    u16 count;
    s32 result;
    s16 best;
    s16 dist;
    s16 d;
    s16 cx;
    Unk1D3DC8 *building;

    count = D_801E29A4;
    result = 0;
    best = 0x270F;
    cx = (D_801F9ACA + 0xC8) & D_801D8866;
    if (count != 0) {
        building = D_801D3DC8;
        do {
            if (building->unk_14 < 9) {
                dist = func_8003FCD8((building->unk_4 + building->unk_E) >> 1, cx);
                d = dist;
                if (dist < 0) {
                    d = -d;
                }
                if (best >= d) {
                    best = d;
                    result = dist < 1;
                }
            }
            building++;
        } while (--count != 0);
    }
    return result;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80029B80);
#endif

void func_80029C6C(Monster *arg0) {
    Sprite *sprite;
    u16 state;

    sprite = D_800AA268 = arg0->unk_68;
    if (sprite != NULL) {
        state = arg0->unk_5A;
        if (((state != 2) && (state != 0x4E)) || (arg0->unk_1BE == 0) || (sprite->unk_10 > 0)) {
            if (arg0->unk_12C != sprite->unk_80) {
                func_8001E39C(sprite);
                func_8001E2F8(sprite);
            }
        }
    }
}

void func_80029CF8(void) {
    D_800AA268->unk_22 = (u16) ((D_800AA268->unk_22 & 0xFF90) | 2);
}

void func_80029D1C(void) {
    u32 flags;

    if (D_800AA268 != NULL) {
        flags = D_800AA268->unk_22;
        flags &= 0xFFF0;
        flags |= 2;
        if (flags & 0x40) {
            flags &= 0xFF72;
        }
        D_800AA268->unk_22 = flags;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_80029D5C);

INCLUDE_ASM("asm/main/nonmatchings/game_8001781C", func_8002A1AC);

s32 func_8002A300(void) {
    return 1;
}

u16 func_8002A308(void) {
    func_8001CFE4();
    return D_801D87A0;
}
