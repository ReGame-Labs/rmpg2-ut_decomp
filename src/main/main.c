/* The first file of the game's code: main and the game loop, the game modes, the object pool and its draw lists,
 * the text printer, the random numbers and the sound calls, and the functions up to func_8002A308.
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "main.h"

/* decls:begin */
extern s32 D_801D3DA8[];
s32 func_80063084(s32);
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
extern u16 D_800AA2C8;
void main_update_pressed(void);
u16 func_8001828C(void);
void func_8001B858(void);
extern u32 D_801FA894;
extern s16 D_8007A698;
extern u8 D_8007ED64[];
extern u8 D_8007EFA4[];
extern u8 D_8007F1E4[];
extern u8 D_80083414[];
extern u8 D_80083654[];
extern TextMessage D_800895A8;
extern TextMessage D_800897FC;
extern s16 D_800AA2C2;
extern u32 D_801D8868[];
extern u8 D_801FAF7C[];
extern s16 D_800AA2D4;
extern s32 D_800AA944;
extern s32 D_800AA948;
extern u16 D_800AFB74;
extern s32 D_801C51C0;
extern s32 D_801C51C4;
extern u16 D_801CA42C;
extern s16 D_801CA45C;
extern s16 D_801CA468;
extern s16 D_801D3704;
extern s16 D_801D3758;
extern s32 D_801D375C;
extern s32 D_801D3760;
extern u16 D_801D3768;
extern u16 D_801D3770;
extern s16 D_801D3778;
extern s16 D_801D3D6C;
extern s16 D_801D3D8C;
extern u16 D_801D3DC6;
extern GameObject *D_801D8584;
extern s16 D_801D8708;
extern u16 D_801D8720;
extern u16 D_801E28C8;
extern u16 D_801D8728;   /* not in game.h: this file reads it unsigned (lhu), actor.c signed (lh) */
extern s16 D_801D8744;
extern s32 D_801D8754;
extern GameObject *D_801D8764;
extern u16 D_801D87A0;
extern s16 D_801D87FC;
extern s16 D_801D8848;
extern s16 D_801D8854;
extern s16 D_801E0D64;
extern s32 D_801E0D6C;
extern GameObject *D_801E1C7C;
extern s16 D_801E1CA4;
extern s16 D_801E1CAC;
extern u16 D_801E1CB0;
extern s16 D_801E1E18;
extern Unk1E2894 D_801E2894;
extern s16 D_801E28DC;
extern s16 D_801E2994;
extern GameObject D_801E29A8;
extern s16 D_801E29B4;
extern s16 D_801E29BC;
extern s16 D_801E2A68;
extern s16 D_801F9918;
extern u16 D_801F9950;
extern u16 D_801F9954;
extern s16 D_801F9958;
extern u16 D_801F995C;
extern Unk1F9A30 D_801F9A30;
extern u16 D_801F9A40;
extern u16 D_801F9ACE;
extern s16 D_801F9AD0;
extern s16 D_801FA7E8[];
extern s16 D_801FA938;
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
void main_begin_frame(void);
void func_80019890(void);
void func_80019984(s32);
void func_8001A1C8(void);
void func_8001A474(void);
SpriteFrame *func_8001A554(s32, GameObject *);
void func_8001B350();
void func_8001B694(void);
void func_8001BA98(void);
void func_8001C404(void);
void func_8001D184(void);
void func_8001D7D0(void);
s32 func_8001D998(GameObject *);
void main_sort_objects(void);
void main_init_objects(void);
void main_free_kind(s32);
void func_8001E4B0(GameObject *);
void func_8001E664(Fixed *, s32, Fixed *, s32 *);
s32 func_8001B660(s32);
void func_8001E700(GameObject *);
void func_8001E7C8(GameObject *);
s16 func_8001EA10(void);
s32 func_8001EAC4(s32);
void func_8001F2B0(void);
void func_8001F358(void);
void func_8001F39C(TextMessage *);
void func_8001F6B4(void);
void func_8001F7F8(s32);
void main_draw_lists(void);
void func_8001F9DC(GameObject *head, GameObject *end);
void func_800205AC(void);
void func_80022EC0(Npc *npc);
void func_80023080(Npc *);
void func_800242A8(void);
void main_place_attached(GameObject *, Npc *);   /* the second argument is not used */
void func_8002469C(s32 *, s16, s16);
void func_80023CFC(Npc *npc);
void func_800256CC(BuildingItem *);
void *func_80025C08(void *);
s32 main_load_image_8bit(s32, s32, s16, s16);
s32 main_load_image_4bit(s32, s32, s16, s16);
extern s16 D_801D876C[];
void func_80025E68(void);
void building_update_sky_colours(void);
void building_update_sky(void);
void npc_pick_target(Npc *);
void func_8003C894(s32);
void func_80044D34(void);
void func_80057DD8(void);
void func_8005E3CC(void);
s32 func_8005E5C8(void);
void bonus_check_round_end(void);
void bonus_update_awards(void);
void func_80060DCC(void);
void func_80062D88(s32);
void func_80062DA8(s32);
void func_80062DEC(s32, s32, s32);
void func_80062E24(s32);
void func_80062E44(void);
void func_80062EA8(s32);
void func_800631B4(void);
void func_80063214(void);
void func_8009FC74(void);
s32 func_8009FF38(void);
s32 func_800A9890(s32);
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
void func_8001B054(GameObject *arg0);
void func_8001B098(GameObject *arg0);
void func_8001B5E8(s32 arg0);
void func_8001B7F4(void);
void func_8001B848(void);
void func_8001BB60(Monster *, s32);
void func_8001BB68(GameObject *arg0);
void func_8001BB88(GameObject *arg0);
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
s32 func_8001E2B8(GameObject *arg0);
void func_8001E528(GameObject *arg0);
void func_8001E638(Unk1E638 *arg0, s32 arg1, Fixed *arg2, s32 *arg3);
void func_8001E698(GameObject *arg0, s32 arg1);
void func_8001E6CC(GameObject *arg0);
void func_8001E758(void);
void func_8001E7A0(void);
void func_8001E94C(s32 arg0, s32 arg1, GameObject *arg2);
void func_8001E978(GameObject *obj);
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
void func_8001F9BC(GameObject *head, GameObject *end);
void func_80020FC8(Npc *npc);
void func_80021034(Npc *npc);
void func_8002107C(Npc *npc);
void func_80022D58(Npc *npc);
void func_80023064(s32 arg0);
void func_800232AC(s32 arg0);
void func_800233E0(Npc *npc);
void func_80023F64(Npc *npc);
void func_800240F0(Npc *npc);
void func_8002423C(Npc *npc);
void func_80024280(void);
void func_800242A0(void);
void func_80024508(Npc *npc);
void func_800245F8(void);
void func_80024954(void);
void func_8002495C(void);
void func_80024964(s32, GameObject *);
void func_8002496C(GameObject *);
s32 func_80024974(s32 arg0);
void func_8002497C(void);
void func_80024AA0(void);
void func_8002546C(Building *);
void func_800255E0(BuildingItem *arg0);
void func_80025648(BuildingItem *arg0);
void func_800256B0(BuildingItem *arg0);
void func_8002575C(BuildingItem *arg0);
void func_800257C4(BuildingItem *arg0);
void func_800257F0(BuildingItem *arg0);
void func_80025848(BuildingItem *arg0);
void func_80025898(BuildingItem *arg0);
void func_80025B10(void);
void func_80026BC4(Monster *arg0);
void func_80026CFC(Monster *arg0);
void func_80026E0C(Monster *arg0);
void func_80026F58(Monster *arg0);
void func_80027FC8(void);
void func_80028140(u16 arg0, Monster *arg1, u16 arg2);
void main_start_scroll_down(void);
void main_start_scroll_up(void);
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
u16 main_approach_xy(Npc *);
void main_unwrap_target_x(s16 *, s16 *, Npc *);
extern u16 D_801FA898[];
void func_80019268(void);
extern s16 D_801D36F8;
extern s16 D_801F9A34;
u16 func_80017C80(u16 id);
void func_80020CE4(s32 arg0, s32 arg1);
u16 func_8001D844(void);
void func_8001D598(void);
extern s16 D_801D872C;
extern s16 D_801E28A0;
extern u16 D_801F9AE0;
extern s32 D_801E28E0;
void func_8001BDCC(void);
extern UnkFA738 D_801FA7EC[];
void func_8001A534(s32 arg0, s32 arg1, s32 arg2);
extern UnkFA738 D_801FA738[];
void func_8001A514(s32 arg0, s32 arg1, s32 arg2);
void func_8001D15C(void *dst, void *src, s32 size);
extern ObjectDef D_801CA430;
extern ObjectDef D_8007AB34;     /* the template func_8001D110 copies */
s16 func_8003FCD8(s32, s32);
void func_800585C0(Monster *);
GameObject *func_8001E204(void);
extern s16 D_801E2998;
void func_80017964(void);
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
s32 main_load_cluts(s32, u8 *);
s32 cdload_file_size(s32);
s32 cdload_read_file(s32, u8 *);
extern s32 D_801D3D9C[];
void func_80062DCC(s32);
s32 func_8001A0E4(s32);
extern u8 *D_801F9948;
s32 func_80025DF8(s32);
extern u16 D_801D37B4;
extern u16 D_801E0D38;
extern u16 D_801FA95C;
extern u16 D_801FA994;
extern u16 D_801FA99C;
void func_80017B24(void);
s32 func_8001AC18(s32, s32);
GameObject *func_8001DCB4();   /* no argument: it reads D_800AA284 (the callers' a0 is incidental) */
void cdload_init_sound(void);
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
void func_8001E174(GameObject *obj);
void func_8001E2F8(GameObject *arg0);
void bonus_update_bars(s32, Monster *, s32);
void main_apply_health(Monster *arg0);
void func_80024BB4(void);
void func_80025B3C(Building *);
void func_80025B7C(BuildingItem *);
void func_8003044C(void);
void func_80024AEC(void);
void func_8001E39C(GameObject *);
void func_80029C6C(Monster *arg0);
void func_80026A6C(void);
ObjectDef *func_8001D110(void);
void func_8002503C(Building *, GameObject *);
void func_800252CC(Building *);
void func_80025124(Building *);
void func_80024E08(Building *);
void main_set_building_sides(void);
extern u8 D_80082E94[];
s32 bonus_get_round_kind(void);
u16 func_80029B80(void);
extern BuildingDef D_800135E8;
extern BuildingDef D_8001687C;
extern u16 D_8007C124[];
extern u16 D_8007C144[];
extern Anim D_80093F78;
extern Anim D_80093FAC;
u16 func_80023C58(s16 arg0, Npc *npc);
u16 func_80023AC0(Npc *npc);
s32 func_80026D54(Monster *);
s32 func_80026D90(Monster *);
s32 func_80027348();   /* (Monster *): the callers that pass nothing still have it in a0 */
void func_80026C4C(Monster *arg0);
s32 func_800272FC();   /* (Monster *), as func_80027348 */
u16 func_800272B0(Monster *);
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
s32 func_8003EB5C(Anim *, GameObject *);
u16 func_80023CB8(void);
s16 func_8002439C(Npc *);
u16 func_8002326C(s16);
u16 main_approach_x(Npc *);
u16 main_approach_y(Npc *);
u16 func_80023114();   /* no parameter (it works on D_800AA268.p); func_8002180C passes its state anyway */
u16 func_800231E4(Npc *);
void func_80023FAC(Npc *npc);
void func_800232D8(Npc *);
extern u8 D_8007B080[];
void func_80063270(void);
void func_8003DAA0(Ai *);
void main_step_anim(void);
extern u16 *D_8007A7C0[];
extern u8 D_801E2154[];
extern u16 D_801FB188;
void func_8002A1AC(Monster *, s16);
void monster_anim_update_projectile(Monster *, s32);
void monster_anim_update_bomb(Monster *);
extern u8 D_800105A8[];
extern s16 D_800AA300[11][8][8];
void func_8001F61C(u8 *, s16, s16, s32, s32, s32 *, s32, s32);
u16 main_check_bonus_round(void *);
extern void (*D_8007BE20[])(Monster *);
void func_80023E30(Npc *);
void main_set_frame(s32, s32, GameObject *);
extern s16 D_8007A6F8[];
extern s16 D_801F9AB8;
extern s16 D_801FAC7C;
extern u16 D_801E2A44;
void func_8001B0D8(s32 *, s32);
void func_8006036C(s32 *, s32, s32, s32, s32, u8 *);
void func_800210C8(Npc *);
extern Unk7B358 *D_8007B358[];
extern Anim D_8008B744;
extern Anim D_80097B3C;
extern Unk7B358 *D_8007B348[];
extern s16 D_8007A6E8[];
u16 main_follow_monster(Npc *);
void func_800242D8(Npc *);
extern Anim D_8008B27C;
extern Anim D_80097674;
extern s32 D_80013654[];
extern s32 D_800136A4[];
extern GameObject *D_801D874C;
void func_80020EDC(Npc *);
void func_80021418(Npc *);
void func_800211F4(Npc *);
void func_80021384(Npc *);
void func_80021644(Npc *);
void func_800216C8(Npc *);
extern GameObject D_801E2A80[];
extern GameObject D_801F9910[];
extern u8 *D_801D85A4;   /* D_801D8588.text by its own name */
extern u32 D_801D377C;
extern Anim D_8008ADB0;
extern Anim D_8008AE08;
extern Anim D_8008AE08_alt;   /* the same table (config/aliases.ld) */
extern Anim D_80097DC0;
extern Anim D_8008B9E4;
/* The handler tables of func_80020EDC: by Npc.aim & 3, then by state & 0x1F. */
extern void (**D_8007B2C0[4])(Npc *);
extern NpcStep *D_8007B660[];
extern NpcStep *D_8007B980[];
void main_wrap_layer_x(GameObject *obj, s32 left, s32 right);
extern s16 D_801FA7E4[];
extern void (*D_8007C14C[])(Monster *);
extern void (*D_8007C170[])(Monster *);
extern void (*D_8007C194[])(Monster *);
extern u16 D_801E1E44;
extern u16 D_801F9AD4;
extern u16 D_801E29C4;
/* decls:end */

/* main: config/aliases.ld gives it its name (GCC 2.8.1 would start a function named main with a call to __main). */
void game_main(void) {
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
restart:
    func_80017964();
    func_80018D10(1);
    for (;;) {
        func_80018CD0();
        if (D_800AA2C8 == 0) {
            D_800AA2C8++;
            main_update_pressed();
            if (D_801F9A34 > 0) {
                D_801F9A34--;
            }
            if (func_8001828C() == 1) {
                goto restart;
            }
            func_8001B7F4();
            if (D_801D3D64.unk_62 == 0) {
                func_8001B858();
            }
        }
        if (D_800AA2E0 != 0) {
            D_800AA2E0 = D_800AA2E8 = D_800AA2C8 = 0;
        }
        func_8001EA78();
        main_sort_objects();
        func_8001D8E8();
        func_80018CF0();
    }
}

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
    main_init_objects();
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

void func_80017B24(void) {
    GameObject *saved;

    D_801D8708 = 0;
    D_801F9AD0 = 0;
    D_800AA2D4 = 0;
    D_801D3D64.unk_08 = 0;
    saved = D_800AA248.cur_obj;
    func_80017B90();
    func_8001E980();
    D_800AA248.cur_obj = saved;
}

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

void main_update_pressed(void) {
    u32 pressed;
    u32 cur;
    u32 prev;

    cur = D_801E0D7C;
    prev = D_801D377C;
    cur &= 0x10040100;
    D_801D377C = cur;
    pressed = 0;
    if (cur & 0x100) {
        pressed = ((prev & 0x100) == 0) << 8;
    }
    if ((cur & 0x40000) && !(prev & 0x40000)) {
        pressed |= 0x40000;
    }
    if ((cur & 0x10000000) && !(prev & 0x10000000)) {
        pressed |= 0x10000000;
    }
    D_801E28E0 = pressed;
}

u16 func_80017C80(u16 id) {
    u16 temp_v1;
    Monster *temp_a1;

    temp_a1 = &D_801E0B78[id];
    if ((D_801D36F8 != 0) || (D_801FA890 != 0) || (D_801F9A34 > 0) || (temp_a1->id == 0) || (temp_v1 = temp_a1->action, (temp_v1 == 0x1F)) || (temp_v1 == 0x37) || (temp_v1 == 0x26) || (temp_a1->unk_046 != 0) || ((D_801D36FC != 0x240) && (D_801D36FC != 0x150) && (D_801D36FC != 0x220)) || ((D_801E1E40 == 0) && (D_801D36FC == 0x150)) || ((D_801D3758 < 5) && (D_801D36FC == 0x220))) {
        return 0;
    }
    return 1;
}

u16 func_80017D8C(void) {
    s32 player;
    s32 id;
    s32 count;
    s32 winner;
    u8 who;

    winner = 0;
    count = 0;
    for (player = 0; player < 3; player++) {
        if (D_801E1C90[player] == 0 && D_801FA898[player] != 0) {
            for (id = 0; id < 7; id++) {
                who = D_801FA8A0[id];
                if (who == player + 1 && func_80017C80(id + 1) == 1) {
                    if (++D_8007A6E8[player] >= 3) {
                        winner = who;
                        count++;
                    }
                }
            }
        } else {
            D_8007A6E8[player] = 0;
            D_801FA898[player] = D_801E1C90[player];
        }
    }
    if (count != 0 && count == D_801D8740 && (u16) count >= 2) {
        return 0xFF;
    }
    return winner;
}

void func_80017F14(s16 x, s16 y, GameObject *link, s32 script) {
    GameObject *saved;
    GameObject *obj;
    ObjectDef *def;

    saved = D_800AA248.cur_obj;
    if (D_8007A698 == 0) {
        def = func_8001D110();
        def->pos_x.s.hi = x;
        def->pos_y.s.hi = y;
        def->flags = 0x6FFF;
        obj = func_8001DCB4();
        D_800AA248.cur_obj = obj;
        obj->unk_40.obj = link;
        D_800AA248.cur_obj->script.pc = script;
        D_800AA248.cur_obj->colour = 0;
        D_800AA248.cur_obj->flags |= 0x40C;
        D_8007A698 = 1;
        D_800AA248.cur_obj->unk_6C |= 0x20;
        D_800AA248.cur_obj->kind = 0x7FE;
    }
    D_800AA248.cur_obj = saved;
}

void func_80018008(void) {
    main_free_kind(0x7FE);
    D_8007A698 = 0;
}

void func_8001802C(s32 player) {
    Monster *monster;
    u16 *buttons;

    D_801E0D7C = 0;
    monster = &D_801E0B78[func_80025DF8(player + 1)];
    if (monster->id != 0) {
        buttons = &D_8007A7C0[D_801D8800[player]][6];
        D_801E0D7C |= *buttons << D_8007C144[player];
        monster->buttons = *buttons >> 4;
    }
}

void func_800180E4(void) {
    ObjectDef *request;
    GameObject *obj;
    GameObject *head;
    GameObject *sprite;

    request = func_8001D110();
    D_800AA284.p = request;
    request->pos_x.w = 0xA00000;
    request->pos_y.w = 0xD70000;
    request->id = 0x4F002808;
    request->flags = 0x7000;
    request->unk_06 |= 0x20;
    obj = func_8001DCB4();
    D_801D373C[0] = obj;
    obj->kind = 0x550;
    func_8001F61C("SELECT", 0xB9, 0xD6, 1, 0x46, D_8007AD4C, 1, 0x550);
    head = &D_801E28C0;
    sprite = head->next;
    if (sprite != head) {
        do {
            if (sprite->kind == 0x550) {
                sprite->colour = 0x808080;
            }
            sprite = sprite->next;
        } while (sprite != head);
    }
}

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001828C);

void func_80018BD4(s32 from, s32 to) {
    GameObject *head;
    GameObject *sprite;

    head = &D_801E28C0;
    sprite = head->next;
    if (sprite != head) {
        do {
            if (sprite->unk_74 == from) {
                sprite->unk_74 = to;
            }
            sprite = sprite->next;
        } while (sprite != head);
    }
}

void func_80018C14(void) {
    s16 prev;

    if (--D_801FAC7C <= 0) {
        prev = D_801F9AB8;
        if (++D_801F9AB8 >= 10) {
            D_801F9AB8 = 0;
        }
        D_801E2A44 = D_8007A6F8[D_801F9AB8];
        func_80018BD4(D_8007A6F8[prev], D_8007A6F8[D_801F9AB8]);
        D_801FAC7C = 4;
    }
}

void func_80018CB0(void) {
    func_800193B8();
}

void func_80018CD0(void) {
    main_begin_frame();
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

INCLUDE_ASM("asm/main/nonmatchings/main", func_80018DBC);

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

INCLUDE_ASM("asm/main/nonmatchings/main", func_800193B8);

void main_begin_frame(void) {
    D_801FAC80 = (D_801FAC80 == &D_801CA474[0]) ? &D_801CA474[1] : &D_801CA474[0];
    ClearOTagR(D_801FAC80->ot, 4);
    D_801FAC80->next_prim = D_801FAC80->prims;
    D_801FAC80->unk_493E = 0xFFFF;
    D_801FAC80->unk_493C = 0xFFFF;
    func_80018D38();
    func_80063744();
    if (D_801E28EC != 0) {
        if ((u32) D_801E0D48 >= (u32) D_801E2A48 || D_801F991C == 4) {
            if (D_801D8750 != 0xFFFF) {
                D_8007A71C = D_801D8750;
                cdload_stop_xa(0);
            }
            if (!(D_8007A71C & 0x8000)) {
                func_8001F7F8((u16) D_8007A71C);
            }
        } else if (D_801F991C == 5) {
            D_8007A71C = D_801D8750;
            cdload_stop_xa(0);
            if (!(D_8007A71C & 0x8000)) {
                func_8001F7F8((u16) D_8007A71C);
            }
        }
    }
}

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
    DrawOTag(&D_801FAC80->ot[3]);
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

s32 main_load_image_8bit(s32 pixels, s32 w, s16 h, s16 slot) {
    Unk1C542C *e;
    RECT rect;
    s32 cols;
    s32 rows;
    s32 page;
    s32 row;
    s32 col;
    s32 i;
    s32 j;
    s32 busy;
    s32 width;
    s32 x;
    s32 y;

    cols = (s16) ((w + 1) & ~1) >> 5;
    e = &D_801C542C[slot];
    width = (w + 1) & ~1;
    if (width & 0x1F) {
        cols++;
    }
    rows = (s16) h >> 5;
    if (h & 0x1F) {
        rows++;
    }
    for (page = 0; page < 11; page++) {
        for (row = 0; row <= 8 - rows; row++) {
            for (col = 0; col <= 8 - cols; col++) {
                busy = 0;
                for (i = 0; i < rows; i++) {
                    for (j = 0; j < cols; j++) {
                        if (D_800AA300[page][i + row][j + col] != 0) {
                            busy = 1;
                            break;
                        }
                    }
                }
                if (busy == 0) {
                    for (i = 0; i < rows; i++) {
                        for (j = 0; j < cols; j++) {
                            D_800AA300[page][i + row][j + col] = 1;
                        }
                    }
                    x = (page % 6) << 7;
                    y = (page / 6) << 8;
                    e->unk_0 = GetTPage(1, 0, x + 0x100, y);
                    e->unk_2 = (col << 13) | (row << 5);
                    rect.w = (s16) width >> 1;
                    rect.h = h;
                    rect.x = x + 0x100 + col * 16;
                    rect.y = y + (row << 5);
                    e->unk_8 = rect.y;
                    e->unk_4 = rect.x;
                    e->unk_C = rect.w;
                    e->unk_10 = rect.h;
                    LoadImage(&rect, (unsigned long *) pixels);
                    return page;
                }
            }
        }
    }
    return -1;
}

#ifdef NON_MATCHING
/* 98.46%: 98.5 %: the original computes the halved width into a1 and copies it into s7, so it extends (s16) width
 * again for rect.w; here GCC knows the value is extended and drops the shifts (two instructions). The 8-bit version
 * of main_load_image_8bit: half-width 128-pixel tpages, two per page */
s32 main_load_image_4bit(s32 pixels, s32 w, s16 h, s16 slot) {
    Unk1C542C *e;
    RECT rect;
    s32 width;
    s32 cols;
    s32 rows;
    s32 page;
    s32 half;
    s32 row;
    s32 col;
    s32 i;
    s32 j;
    s32 busy;
    s32 x;
    s32 y;

    cols = ((s16) ((w + 1) & ~1) >> 1) >> 5;
    e = &D_801C542C[slot];
    width = (s16) ((w + 1) & ~1) >> 1;
    if (width & 0x1F) {
        cols++;
    }
    rows = (s16) h >> 5;
    if (h & 0x1F) {
        rows++;
    }
    for (page = 0; page < 11; page++) {
        for (half = 0; half < 8; half += 4) {
            for (row = 0; row <= 8 - rows; row++) {
                for (col = half; col <= half + 4 - cols; col++) {
                    busy = 0;
                    for (i = 0; i < rows; i++) {
                        for (j = 0; j < cols; j++) {
                            if (D_800AA300[page][i + row][j + col] != 0) {
                                busy = 1;
                                break;
                            }
                        }
                    }
                    if (busy == 0) {
                        for (i = 0; i < rows; i++) {
                            for (j = 0; j < cols; j++) {
                                D_800AA300[page][i + row][j + col] = 1;
                            }
                        }
                        page = page * 2 + half / 4;
                        x = (page % 12) << 6;
                        y = (page / 12) << 8;
                        e->unk_0 = GetTPage(0, 0, x + 0x100, y);
                        rect.w = ((s16) width + 1) >> 1;
                        rect.h = h;
                        rect.x = x + 0x100 + (col - half) * 16;
                        rect.y = y + (row << 5);
                        e->unk_2 = ((col - half) << 14) | (row << 5);
                        e->unk_4 = rect.x;
                        e->unk_8 = rect.y;
                        e->unk_C = rect.w;
                        e->unk_10 = rect.h;
                        LoadImage(&rect, (unsigned long *) pixels);
                        return page;
                    }
                }
            }
        }
    }
    return -1;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/main", main_load_image_4bit);
#endif

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

void func_8001A534(s32 arg0, s32 arg1, s32 arg2) {
    UnkFA738 *temp_a0;

    temp_a0 = &D_801FA7EC[arg0 & 0xFFFF];
    temp_a0->unk_0 = arg2;
    temp_a0->unk_4 = arg1;
}

#ifdef NON_MATCHING
/* 97.14%: 97.1 %: in both slot branches the original forms D_801F9AE4's address after the slot's index (sll), here
 * between the andi and the sll. Maps a frame id to its SpriteFrame (bank D_801FA738[id >> 24] + offset
 * D_801D8868[id >> 1]), takes a VRAM slot for it unless the frame is resident (0x40000000), and keeps the frame's
 * tpage word in obj->unk_24 */
SpriteFrame *func_8001A554(s32 id, GameObject *obj) {
    SpriteFrame *frame;
    u32 index;
    u16 b;
    u16 flags;
    u16 slot;

    if ((obj->unk_6C & 0x400) && obj->unk_3C != id) {
        obj->unk_6C &= 0xFBFF;
        func_8001B350(obj->unk_6E);
    }
    if (id < 0) {
        frame = (SpriteFrame *) id;
        obj->unk_6C |= 8;
        obj->unk_24 = frame->unk_00;
    } else {
        index = (u32) (id & 0xFFFFFF) >> 1;
        obj->unk_72 = b = ((u32) id >> 24) & 0x3F;
        obj->anim_frame = id;
        if (index >= 0x2135) {
            index = 0;
            b = 0xF;
        }
        frame = (SpriteFrame *) (D_801FA738[b].unk_0 + (D_801D8868[index] & 0x7FFFFFFF));
        if ((D_801D8868[index] & 0x7FFFFFFF) == 0) {
            id = D_8007AD4C[(func_8001EB10(0x8000, 0xE) & 0x1F) + 10];
            frame = (SpriteFrame *) func_8001B128(id);
            obj->unk_24 = frame->unk_00;
        }
        if (frame->unk_00 & 0x40000000) {
            obj->unk_6C |= 8;
            obj->unk_24 = frame->unk_00;
        } else if (obj->unk_3C != id || !(obj->unk_6C & 0x400)) {
            flags = obj->unk_6C;
            obj->unk_6C = flags & 0xFFF7;
            if (!(flags & 0x80)) {
                obj->unk_6C = (flags & 0xFFF7) | 0x400;
                if (frame->unk_00 & 0x20000000) {
                    obj->unk_24 = (D_801F9AE4 + (obj->unk_6E = main_alloc_vram_slot(frame, D_801FA738[b].unk_0, 1)))->unk_0.w | 0x20000000;
                } else {
                    obj->unk_24 = (D_801F9AE4 + (obj->unk_6E = main_alloc_vram_slot(frame, D_801FA738[b].unk_0, 0)))->unk_0.w;
                }
            }
        }
    }
    obj->unk_3C = id;
    return frame;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/main", func_8001A554);
#endif

s32 func_8001A784(u32 id) {
    u32 index;

    if ((s32) id >= 0) {
        index = (id & 0xFFFFFF) >> 1;
        id = D_801FA738[(id >> 24) & 0x3F].unk_0 + (D_801D8868[index] & 0x7FFFFFFF);
        if ((D_801D8868[index] & 0x7FFFFFFF) == 0) {
            id = D_8007AD4C[(func_8001EB10(0x8000, 0xE) & 0x1F) + 10];
        }
    }
    return id;
}

u16 func_8001A820(s32 index, s32 id) {
    UnkFA738 *e = &D_801FA738[index & 0xFFFF];

    return (u16) e->unk_4 == (u16) id;
}

u16 func_8001A848(s32 index, s32 id) {
    UnkFA738 *e = &D_801FA7EC[index & 0xFFFF];

    return (u16) e->unk_4 == (u16) id;
}

/* Loads a bank's CLUTs into VRAM at (D_800AA944, D_800AA948) and appends their ids to D_801C51D4, the bank's first
 * one at D_800AFB54[bank]. The data: a word offset to a header (its size at +4), then runs of a count and the
 * colours; every colour after a run's first gets the transparency bit. */
s32 main_load_cluts(s32 bank, u8 *data) {
    u16 *slot;
    u16 buf[256];
    RECT rect;
    u8 *hdr;
    u16 *dst;
    u16 *src;
    u16 *end;
    u16 count;
    s32 i;
    u16 clut;
    u16 n;

    slot = &D_800AFB54[bank & 0xFFFF];
    dst = buf;
    hdr = data + *(s32 *) data;
    src = (u16 *) (hdr + 0xA);
    end = (u16 *) (hdr + *(s32 *) (hdr + 4) + 8);
    n = D_800AFB74;
    *slot = n;
    count = *(u16 *) (hdr + 8);
    if (count != 0) {
        do {
            for (i = 0; i < count; i++) {
                dst[i] = *src++;
                if (i != 0) {
                    dst[i] |= 0x8000;
                }
            }
            if (D_800AA944 & 0xF) {
                D_800AA944 = (D_800AA944 & 0xFFF0) + 0x10;
            }
            if (count + D_800AA944 > 0x180) {
                D_800AA944 = 0;
                D_800AA948++;
                if (D_800AA948 >= 0x1F0) {
                    if (D_800AA948 >= 0x200) {
                        break;
                    }
                } else if (D_800AA948 >= 0x100) {
                    D_800AA948 = 0x1F0;
                }
            }
            clut = GetClut(D_800AA944, D_800AA948);
            n = D_800AFB74++;
            D_801C51D4[n] = clut;
            rect.w = count;
            rect.x = D_800AA944;
            rect.y = D_800AA948;
            rect.h = 1;
            LoadImage(&rect, (unsigned long *) buf);
            DrawSync(0);
            D_800AA944 += count;
            if (src >= end) {
                break;
            }
            count = *src++;
        } while (count != 0);
    }
    return 0;
}

s32 func_8001AA4C(s32 arg0, s32 arg1) {
    s32 bank;
    s32 file;

    bank = arg0 & 0xFFFF;
    file = arg1 & 0xFFFF;
    if (func_8001A820(bank, file)) {
        return 1;
    }
    cdload_file_size(file);
    if (cdload_read_file(file, D_801F9948) == 0) {
        return 0;
    }
    main_load_cluts(bank, D_801F9948);
    D_801F9948 += 4;
    func_8001A514(bank, file, (s32) D_801F9948);
    func_8001B0D8((s32 *) (D_801F9948 + *(s32 *) D_801F9948), 0);
    D_801F9948 += *(s32 *) D_801F9948;
    if (D_801F9948 - D_800B09C0 > 0x114800) {
        func_8001B5E8(4);
    }
    return 1;
}

s32 func_8001AB30(s32 arg0, s32 arg1) {
    s32 bank;
    s32 file;
    s32 size;

    bank = arg0 & 0xFFFF;
    file = arg1 & 0xFFFF;
    if (!func_8001A848(bank, file)) {
        D_801F9948 = (u8 *) (((s32) D_801F9948 + 3) & ~3);
        size = cdload_file_size(file);
        if (cdload_read_file(file, D_801F9948) == 0) {
            return 0;
        }
        size = (size + 3) & ~3;
        func_8001A534(bank, file, (s32) D_801F9948);
        D_801F9948 += size;
        if (D_801F9948 - D_800B09C0 > 0x114800) {
            func_8001B5E8(4);
        }
    }
    return 1;
}

s32 func_8001AC18(s32 arg0, s32 arg1) {
    s32 bank;
    s32 file;
    u8 *base;
    u8 *data;
    u8 *images;

    bank = arg0 & 0xFFFF;
    file = arg1 & 0xFFFF;
    if (!func_8001A820(bank, file)) {
        cdload_file_size(file);
        if (cdload_read_file(file, D_801F9948) == 0) {
            return 0;
        }
        main_load_cluts(bank, D_801F9948);
        base = D_801F9948;
        data = base + 4;
        func_8001A514(bank, file, (s32) data);
        func_8001B0D8((s32 *) (data + *(s32 *) data), 0);
        images = data + ((s32 *) data)[3];
        if (images - D_800B09C0 > 0x114800) {
            func_8001B5E8(4);
        }
        func_8001AD1C(data, images, bank);
        D_801F9948 = data + *(s32 *) data;
    }
    return 1;
}

void func_8001AD1C(Unk1AD1C *bank, s32 addr, s16 id) {
    u32 i;
    s32 slot;

    i = 0;
    if (bank->unk_4 != 0) {
        do {
            slot = main_load_image_8bit(addr, 0x100, 0x100, id);
            if (slot == -1) {
                func_8001B5E8(5);
            }
            addr += 0x10000;
            D_801D876C[slot * 2] = (u16) id | 0x8000;
            D_801D876C[slot * 2 + 1] = (u16) id | 0x8000;
            i++;
        } while (i < bank->unk_4);
    }
    i = 0;
    if (bank->unk_8 != 0) {
        do {
            slot = main_load_image_4bit(addr, 0x100, 0x100, id);
            if (slot == -1) {
                func_8001B5E8(6);
            }
            D_801D876C[slot] = id;
            addr += 0x8000;
            i++;
        } while (i < bank->unk_8);
    }
}

u16 main_get_tpage(GameObject *obj, u16 mode) {
    Unk1F9AE4 *rec;
    u32 word;
    u16 id;
    u16 nth;
    s16 i;
    s32 n;

    n = 0;
    word = obj->unk_24;
    if (obj->unk_6C & 0x400) {
        rec = &D_801F9AE4[obj->unk_6E];
        if (mode & 0x400) {
            return rec->unk_0.u.hi | ((mode & 0x300) >> 3);
        }
        return rec->unk_0.u.hi;
    }
    id = (word >> 24) & 0x9F;
    nth = (word >> 16) & 0xFF;
    if (word & 0x20000000) {
        for (i = 0; i < 0x18; i++) {
            if (D_801D876C[i] == id && !(D_801D876C[i] & 0x8000) && n++ == nth) {
                return GetTPage(0, (mode & 0x300) >> 8, (i % 12) * 64 + 0x100, (i / 12) * 256);
            }
        }
    } else {
        for (i = 0; i < 0x18; i += 2) {
            if ((D_801D876C[i] & 0x8000) && (D_801D876C[i] & 0x7FFF) == id && n++ == nth) {
                return GetTPage(1, (mode & 0x300) >> 8, (i % 12) * 64 + 0x100, (i / 12) * 256);
            }
        }
    }
    return 0;
}

void func_8001B054(GameObject *arg0) {
    u16 temp_v1;

    temp_v1 = arg0->unk_6C | 0x80;
    arg0->unk_6C = temp_v1;
    if (temp_v1 & 0x400) {
        arg0->unk_6C = (u16) (temp_v1 & 0xFBFF);
        func_8001B350(arg0->unk_6E, arg0);
    }
}

void func_8001B098(GameObject *arg0) {
    u16 temp_v0;

    temp_v0 = arg0->unk_6C;
    arg0->unk_6C = (u16) (temp_v0 & 0xFF7F);
    if (!(temp_v0 & 0x408)) {
        func_8001A554(arg0->anim_frame, arg0);
    }
}

void func_8001B0D8(s32 *p, s32 flags) {
    if (p[1] != 0) {
        do {
            D_801D8868[p[0]] = p[1] | flags;
            p += 2;
        } while (p[1] != 0);
    }
}

Glyph *func_8001B128(u32 arg0) {
    u32 index;

    index = (arg0 & 0xFFFFFF) >> 1;
    return (Glyph *) (D_801FA738[(arg0 >> 24) & 0x3F].unk_0 + (D_801D8868[index] & 0x7FFFFFFF));
}

s32 main_load_font(void) {
    RECT rect;
    u8 *data;
    u8 *pixels;
    u32 id;
    u32 index;

    cdload_file_size(0x19);
    if (cdload_read_file(0x19, D_800B09C0) == 0) {
        return 0;
    }
    main_load_cluts(0xF, D_800B09C0);
    data = D_800B09C0 + 4;
    func_8001A514(0xF, 0x19, (s32) data);
    rect.w = 0x40;
    rect.h = 0x100;
    pixels = data + *(s32 *) (data + 0xC);
    rect.x = 0x340;
    rect.y = 0x100;
    LoadImage(&rect, (unsigned long *) pixels);
    pixels += 0x8000;
    rect.x = 0x380;
    rect.y = 0x100;
    LoadImage(&rect, (unsigned long *) pixels);
    rect.x = 0x3C0;
    rect.y = 0x100;
    LoadImage(&rect, (unsigned long *) (pixels + 0x8000));
    DrawSync(0);
    DrawSync(0);
    DrawSync(0);
    D_801D876C[21] = 0xF;
    D_801D876C[22] = 0xF;
    D_801D876C[23] = 0xF;
    func_8001B0D8((s32 *) (data + *(s32 *) (D_800B09C0 + 4)), 0x80000000);
    D_801F9A3C = 0;
    D_801E1C78 = D_801F9948 = data + *(s32 *) (D_800B09C0 + 4);
    D_801C51C0 = D_800AA944;
    D_801C51C4 = D_800AA948;
    id = D_8007AB34.id;
    index = (id & 0xFFFFFF) >> 1;
    D_801CA42C = D_800AFB74;
    D_8007AB34.id = D_801FA738[(id >> 24) & 0x3F].unk_0 + (D_801D8868[index] & 0x7FFFFFFF);
    return 1;
}

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

s32 main_alloc_vram_slot(SpriteFrame *frame, s32 base, u16 mode) {
    Unk1F9AE4 *rec;
    Unk1C542C *slot;
    s32 i;
    s32 free;
    s32 size;
    s32 used;

    free = -1;
    rec = D_801F9AE4;
    for (i = 0; i < 0xC4; i++, rec++) {
        if (rec->unk_8 == (s32) frame) {
            rec->unk_4++;
            return i;
        }
        if (free == -1 && rec->unk_4 == 0) {
            free = i;
        }
    }
    if (free == -1) {
        func_8001B5E8(9);
    }
    rec = &D_801F9AE4[free];
    rec->unk_4 = 1;
    rec->unk_8 = (s32) frame;
    rec->unk_C = func_8001A0A0();
    size = frame->size.s.lo;
    size = (size + 1) & ~1;
    size *= frame->size.s.hi;
    size = (size + 3) & ~3;
    if (D_801FA974 - size < (s32) D_801F9948) {
        DrawSync(0);
        D_801FA974 = D_801E299C;
    }
    D_801FA974 -= size;
    cdload_unpack((u8 *) D_801FA974, 0, (u8 *) (frame->unk_00 + base), 0);
    if (mode == 1) {
        main_load_image_4bit(D_801FA974, frame->size.s.lo, frame->size.s.hi, rec->unk_C);
    } else {
        main_load_image_8bit(D_801FA974, frame->size.s.lo, frame->size.s.hi, rec->unk_C);
    }
    used = D_801E299C - D_801FA974;
    if (D_8007A710 < used) {
        D_8007A710 = used;
    }
    slot = &D_801C542C[rec->unk_C];
    rec->unk_0.w = (slot->unk_0 << 16) | slot->unk_2;
    return free;
}

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

void func_8001B694(void) {
    u16 step;
    Monster *m;

    step = D_801F9950;
    D_801D37B4 += step;
    if ((s16) D_801D37B4 > 0) {
        D_801D37B4 = 0;
    }
    if (D_801D3D64.unk_1A != 0) {
        D_801D3D64.unk_1A = (u16) (D_801D3D64.unk_1A - 1);
    }
    D_801E0D38 += D_801F9954;
    if ((s16) D_801E0D38 >= 0x3C) {
        D_801E0D38 = 0;
        if ((D_801FA968 == 0) && (D_801D36FC == 0x150)) {
            m = &D_801E0B78[func_80025DF8(1)];
            if (m->id != 0) {
                D_801FA95C += 1;
            }
            m = &D_801E0B78[func_80025DF8(2)];
            if (m->id != 0) {
                D_801FA99C += 1;
            }
            m = &D_801E0B78[func_80025DF8(3)];
            if (m->id != 0) {
                D_801FA994 += 1;
            }
        }
    }
}

void func_8001B7F4(void) {
    u16 temp_v1;

    main_sort_objects();
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
        if (monster->unk_046 != 0) {
            func_8001BB60(monster, i);
        } else if ((monster->unk_1E0 != 2) && (monster->id != 0) &&
                   ((monster->action == 0x37) || (monster->action == 0x26)) && (monster->unk_1F8 == 0)) {
            func_8001BBA8(monster, i);
        }
    } while (--i != 0);
}

void func_8001BB60(Monster *monster, s32 index) {
}

void func_8001BB68(GameObject *arg0) {
    if (arg0 != NULL) {
        arg0->pos_y.u.hi = (u16) (arg0->pos_y.u.hi | 0xC000);
    }
}

void func_8001BB88(GameObject *arg0) {
    if (arg0 != NULL) {
        arg0->pos_y.u.hi = (u16) (arg0->pos_y.u.hi & 0x3FFF);
    }
}

void func_8001BBA8(Monster *monster, s32 index) {
}

void func_8001BBB0(void) {
    ObjectDef *temp_v0;

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
            D_800AA284.p = temp_v0;
            temp_v0->id = 0x0A0041C8;
            temp_v0->pos_x.w = 0x930000;
            temp_v0->pos_y.w = 0x1E0000;
            temp_v0->flags = 0x14;
            temp_v0->unk_06 |= 0x20;
            func_8001DCB4();
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
        cdload_init_sound();
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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001C02C);

void func_8001C3C4(void) {
    func_8001C404();
}

u8 func_8001C3E4(s16 id) {
    return D_801FA8A0[id];
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001C404);

void func_8001C77C(void) {
}

void func_8001C784(void) {
    D_801D3758 += 1;
    func_8001CFE4();
    func_80025E68();
    building_update_sky_colours();
    building_update_sky();
    func_8005E3CC();
    bonus_check_round_end();
    bonus_update_awards();
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

INCLUDE_RODATA("asm/main/nonmatchings/main", D_800105C8);

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001C83C);

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

ObjectDef *func_8001D110(void) {
    func_8001D15C(&D_801CA430, &D_8007AB34, 0x2C);
    D_800AA248.unk_1C.def = &D_801CA430;
    D_800AA248.new_def = &D_801CA430;
    return &D_801CA430;
}

void func_8001D15C(void *dst, void *src, s32 size) {
    memcpy(dst, src, size & 0xFFFF);
}

void func_8001D17C(void) {
}

void func_8001D184(void) {
    GameObject *saved;

    saved = D_800AA248.cur_obj;
    func_8001D0C0();
    D_800AA248.cur_obj = saved;
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

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001D28C);

void func_8001D4B8(void) {
    s16 phase;

    D_801FA968 = 1;
    D_801D36FC = 0x150;
    phase = D_801E29BC % 60;
    if (phase == 59) {
        func_8006036C(D_8007AD4C, 0xA3, 0xD7, 0x44, 0x402, "DEMO");
    } else if (phase == 30) {
        main_free_kind(0x402);
    }
    func_8001C784();
    D_801D36FC = 0x120;
    D_801FA968 = 0;
}

void func_8001D28C(void);

void func_8001D598(void) {
    s32 overlay;

    switch (D_801F9AE0) {
    case 1:
    case 2:
    case 3:
    case 7:
    case 8:
    case 9:
    case 12:
    case 13:
    case 14:
        overlay = 2;
        break;
    default:
        overlay = 0;
        break;
    }
    cdload_load_overlay(overlay);
    if (D_801E29BC == -1) {
        func_8001D6A0();
        return;
    }
    switch (D_801F9AE0) {
    case 2:
    case 8:
    case 13:
        D_801E29BC--;
        func_8001D4B8();
        return;
    case 1:
    case 7:
    case 12:
        func_8001D28C();
        return;
    case 3:
    case 9:
    case 14:
        func_8001D1C8();
        return;
    default:
        D_801D3780 = 0;
        D_801F9AE0 = 0;
        return;
    }
}

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

s32 func_8001D878(void) {
    s32 result;
    s32 k;
    s32 i;

    result = 0;
    for (k = 0; k < 3; k++) {
        for (i = 0; i < 7; i++) {
            if ((u8) D_801FA8A0[i] == k + 1) {
                result |= D_801E0D7C & (0x3FF << (k * 10));
            }
        }
    }
    return result;
}

void func_8001D8E8(void) {
    s32 temp_s0;

    if ((D_801F9A40 != 0) && (D_801F995C == 0)) {
        D_801E29B4 = 0;
        D_801D8744 = 0;
        temp_s0 = func_8001D950();
        D_801E29B4 = temp_s0 + func_8001D974();
        main_draw_lists();
    }
}

s32 func_8001D950(void) {
    return func_8001D998(&D_801E28C0) & 0xFFFF;
}

s32 func_8001D974(void) {
    return func_8001D998(&D_801E29A8) & 0xFFFF;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001D998);

GameObject *func_8001DCB4(void) {
    u16 *p;
    GameObject *obj;

    p = (u16 *) D_800AA248.new_def;
    D_800AA248.unk_04 = *(s32 *) p;
    p += 2;
    obj = func_8001E204();
    if (obj == NULL) {
        func_8001B5E8(0);
    }
    func_8001E59C(obj, D_800AA248.unk_04);
    D_800AA248.unk_74 = *p++;
    D_800AA248.unk_44 = *p++;
    obj->unk_6C |= D_800AA248.unk_44;
    if (D_800AA248.unk_74 & 0x10) {
        main_set_frame(D_800AA248.unk_04, (u16) D_800AA248.unk_74, obj);
    } else {
        obj->flags |= D_800AA248.unk_74;
    }
    D_800AA248.unk_60 = *(s32 *) p;
    p += 2;
    D_800AA248.unk_38 = 0x7FF;
    if (D_800AA248.unk_60 & 0x40) {
        D_800AA248.unk_74 = *(s32 *) p;
        p += 2;
        if (D_800AA248.unk_74 != 0) {
            D_800AA248.unk_38 = D_800AA248.unk_74;
        }
    }
    obj->kind = D_800AA248.unk_38;
    if (D_800AA248.unk_60 & 0x20) {
        D_800AA248.unk_54 = *(s32 *) p;
        p += 2;
        D_800AA248.unk_50 = *(s32 *) p;
        p += 2;
        D_800AA248.unk_4C = *(s32 *) p;
        p += 2;
        if (D_800AA248.unk_44 & 0x8000) {
            D_800AA248.unk_54 >>= 16;
            D_800AA248.unk_50 >>= 16;
            obj->pos_x.s.hi = obj->unk_28.s.lo = (u16) D_800AA248.unk_54 - obj->unk_1C.u.lo;
            obj->pos_y.s.hi = obj->unk_28.s.hi = (u16) D_800AA248.unk_50 - obj->unk_1C.u.hi;
        } else {
            obj->pos_x.w = D_800AA248.unk_54;
            obj->pos_y.w = D_800AA248.unk_50;
        }
    }
    D_800AA248.unk_38 = 0;
    D_800AA248.unk_74 = 0;
    if (D_800AA248.unk_60 & 1) {
        D_800AA248.unk_74 = *(s32 *) p;
        p += 2;
        if (D_800AA248.unk_74 != 0) {
            D_800AA248.unk_38 = D_800AA248.unk_74;
        }
    }
    obj->unk_82 = D_800AA248.unk_38;
    D_800AA248.unk_38 = 0;
    if (D_800AA248.unk_60 & 2) {
        D_800AA248.unk_38 = *(s32 *) p;
        p += 2;
    }
    obj->priority = D_800AA248.unk_38;
    if (D_800AA248.unk_60 & 4) {
        D_800AA248.unk_74 = *(s32 *) p;
        p += 2;
        if (D_800AA248.unk_74 != 0) {
            func_80024964(D_800AA248.unk_74, obj);
        }
    }
    if (D_800AA248.unk_60 & 8) {
        D_800AA248.unk_74 = *(s32 *) p;
        p += 2;
        if (D_800AA248.unk_74 != 0) {
            func_8001E698(obj, D_800AA248.unk_74);
        }
    }
    if (D_800AA248.unk_60 & 0x10) {
        D_800AA248.unk_58 = *(void (**)(void)) p;
        if (D_800AA248.unk_58 != NULL) {
            D_800AA248.unk_00 = (s32) obj;
            D_800AA248.unk_58();
        }
    }
    if (D_800AA2A8 & 0x80) {
        func_8001E2F8(obj);
    }
    return obj;
}

/* One pass of a bubble sort of the object list by priority. The loop is entered at its advance at the bottom, as
 * the original's layout has it (jump.c's copy of the exit test before the loop would differ). */
void main_sort_objects(void) {
    GameObject *head;
    GameObject *cur;
    GameObject *obj;
    GameObject *p;
    s16 last;

    head = &D_801E28C0;
    cur = head;
    last = 0x7FFF;
    goto next;
    while (obj != head) {
        if (last < (s16) obj->priority) {
            p = cur->prev;
            p->next = obj;
            obj->prev = p;
            p = obj->next;
            cur->next = p;
            obj->next = cur;
            cur->prev = obj;
            p->prev = cur;
        } else {
            cur = obj;
            last = obj->priority;
        }
    next:
        obj = cur->next;
    }
}

void main_resort_objects(void) {
    GameObject *head;
    GameObject *sprite;
    GameObject *next;
    GameObject *pos;
    GameObject *prev;

    head = &D_801E28C0;
    sprite = head->next;
    if (sprite->next != sprite) {
        head->next = head;
        head->prev = head;
        if (sprite != head) {
            do {
                pos = D_801E28C0.next;
                next = sprite->next;
                while (pos != &D_801E28C0 && pos->priority >= sprite->priority) {
                    pos = pos->next;
                }
                prev = pos->prev;
                sprite->next = pos;
                sprite->prev = prev;
                pos->prev->next = sprite;
                pos->prev = sprite;
                sprite = next;
            } while (sprite != head);
        }
    }
}

void main_init_objects(void) {
    GameObject *obj;
    GameObject *last;
    u16 n;

    D_801FA7E8[0] = 0;
    D_801FA7E8[1] = 0;
    D_801FA7E4[0] = 0x180;
    D_801FA7E4[1] = 0xF0;
    D_801D8584 = NULL;
    obj = &D_801E28C0;
    obj->next = obj;
    obj->prev = obj;
    obj = &D_801E29A8;
    obj->next = obj;
    obj->prev = obj;
    memset(D_801E2A80, 0, sizeof(GameObject) * 460);
    obj = D_801E2A80;
    D_801E1C7C = obj;
    n = D_801D3768 = 460;
    do {
        last = obj;
        obj++;
        last->next = obj;
    } while (--n != 0);
    last->next = NULL;
    D_801D8764 = last;
}

void func_8001E174(GameObject *obj) {
    if (obj < D_801E2A80 || obj >= D_801F9910) {
        func_8001B5E8(0xE);
    }
    if (((u32) obj - (u32) D_801E2A80) % sizeof(GameObject) != 0) {
        func_8001B5E8(0xE);
    }
}

GameObject *func_8001E204(void) {
    u16 temp_v0;
    GameObject *temp_s0;

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
    D_801E1C7C = temp_s0->next;
    memset(temp_s0, 0, 0xCC);
    temp_s0->flags = 0x8000;
    D_800AA2C2 = 0;
    return temp_s0;
}

s32 func_8001E2B8(GameObject *arg0) {
    memset(&arg0->unk_8C, 0, 0x40);
    arg0->unk_60 = 0;
    D_800AA2C2 = 0;
    return 0;
}

void func_8001E2F8(GameObject *arg0) {
    GameObject *head;
    GameObject *prev;
    GameObject *p;
    u16 key;

    func_8001E174(arg0);
    head = arg0->next;
    if (head == NULL) {
        if (arg0->unk_82 != 1) {
            p = &D_801E28C0;
        } else {
            p = &D_801E29A8;
        }
        head = p;
        p = p->next;
        key = arg0->priority;
        while ((p != head) && ((s16) key < p->priority)) {
            p = p->next;
        }
        prev = p->prev;
        arg0->next = p;
        prev->next = arg0;
        p->prev = arg0;
        arg0->prev = prev;
    }
}

void func_8001E39C(GameObject *obj) {
    GameObject *next;
    GameObject *prev;

    if (obj->next != NULL) {
        prev = obj->prev;
        next = obj->next;
        if (prev != &D_801E28C0 && prev != &D_801E29A8 && next != &D_801E28C0 && next != &D_801E29A8 &&
            (prev < D_801E2A80 || prev > D_801F9910 || next < D_801E2A80 || next > D_801F9910)) {
            func_8001E978(obj);
        }
        prev->next = next;
        next->prev = prev;
        obj->next = NULL;
    }
}

void main_free_kind(s32 kind) {
    GameObject *head;
    GameObject *sprite;
    GameObject *next;

    head = &D_801E28C0;
    sprite = head->next;
    do {
        next = sprite->next;
        if (sprite->kind == (u16) kind) {
            func_8001E4B0(sprite);
        }
        sprite = next;
    } while (sprite != head);
}

void func_8001E4B0(GameObject *sprite) {
    func_8001E174(sprite);
    if (!(sprite->flags & 0x8000)) {
        for (;;) {
        }
    }
    sprite->flags &= 0x7FFF;
    if (sprite->unk_6C & 0x4000) {
        func_8001E7C8(sprite);
    }
    func_8001E39C(sprite);
    func_8002496C(sprite);
    func_8001E528(sprite);
}

void func_8001E528(GameObject *arg0) {
    if (arg0->unk_6C & 0x400) {
        func_8001B350(arg0->unk_6E);
    }
    D_801D3768 += 1;
    if (D_801D8764 != NULL) {
        D_801D8764->next = arg0;
    } else {
        D_801E1C7C = arg0;
    }
    D_801D8764 = arg0;
}

s32 func_8001E59C(GameObject *sprite, s32 image) {
    SpriteFrame *img;
    s32 offset;
    s32 size;

    img = func_8001A554(image, sprite);
    func_80024974(img->unk_0C);
    if (D_800AA248.unk_7A == 1) {
        return 1;
    }
    sprite->unk_74 = 0xFFFF;
    sprite->colour = -1;
    sprite->frame = img;
    offset = img->size.w;
    sprite->flags = 0;
    sprite->unk_2C.w = offset;
    sprite->size.w = offset;
    size = img->origin.w;
    sprite->unk_28.w = 0x02000200;
    sprite->unk_7C = size;
    sprite->unk_1C.w = size;
    D_800AA248.unk_7A = 0;
    return 0;
}

void func_8001E638(Unk1E638 *arg0, s32 arg1, Fixed *arg2, s32 *arg3) {
    arg2->w = arg0->unk_8;
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
    pos->w = x;
}

void func_8001E698(GameObject *arg0, s32 arg1) {
    arg0->script.pc = arg1;
    arg0->anim = arg1;
    arg0->frames_left = 0;
    arg0->flags = (u16) (arg0->flags | 0x800);
    func_8001E6CC(arg0);
}

void func_8001E6CC(GameObject *arg0) {
    if (!(arg0->unk_6C & 0x4000)) {
        func_8001E700(arg0);
    }
}

void func_8001E700(GameObject *sprite) {
    GameObject *head;

    if (sprite->unk_6C & 0x4000) {
        func_8001B5E8(0x10);
    }
    sprite->unk_6C |= 0x4000;
    head = D_801D8584;
    D_801D8584 = sprite;
    sprite->unk_40.obj = head;
}

void func_8001E758(void) {
    if (D_801D8584 != 0) {
        do {
            func_8001E7C8(D_801D8584);
        } while (D_801D8584 != 0);
    }
}

void func_8001E7A0(void) {
    func_8001E7C8(D_800AA268.p);
}

void func_8001E7C8(GameObject *arg0) {
    GameObject *next;
    GameObject *p;

    if (!(arg0->unk_6C & 0x4000)) {
        func_8001B5E8(0x10);
    }
    arg0->unk_6C = (u16) (arg0->unk_6C & 0xBFFF);
    func_80020AF4(arg0);
    next = D_801D8584;
    if (arg0 == next) {
        next = arg0->unk_40.obj;
        D_801D8584 = next;
        return;
    }
    do {
        p = next;
        next = p->unk_40.obj;
        if (next == NULL) {
            func_8001B5E8(0x11);
        }
    } while (next != arg0);
    p->unk_40.obj = arg0->unk_40.obj;
}

void func_8001E878(void) {
    D_800AA248.unk_00 = *D_800AA248.cur_obj->arg.w++;
    if (D_800AA248.unk_00 == 0) {
        D_800AA248.unk_7A = 1;
    } else {
        D_800AA248.unk_7A = 0;
    }
}

/* Frees every object whose kind matches under the mask. Entered at the advance, as main_sort_objects. */
void main_free_kind_masked(s16 kind, s16 mask) {
    GameObject *head;
    GameObject *next;
    GameObject *sprite;

    kind &= mask;
    head = &D_801E28C0;
    sprite = head;
    goto advance;
    while (sprite != head) {
        if ((sprite->kind & mask) == kind) {
            next = sprite->next;
            func_8001E4B0(sprite);
            sprite = next;
        } else {
        advance:
            sprite = sprite->next;
        }
    }
}

void func_8001E94C(s32 arg0, s32 arg1, GameObject *arg2) {
    SpriteFrame *temp_v1;

    temp_v1 = arg2->frame;
    arg2->unk_28.s.lo = (s16) (arg0 - temp_v1->origin.u.lo);
    arg2->unk_28.s.hi = (s16) (arg1 - temp_v1->origin.u.hi);
}

void func_8001E978(GameObject *obj) {
}

void func_8001E980(void) {
    func_8001A1C8();
    func_8001A474();
    func_8002495C();
    func_80024954();
    D_801D3D6C = 0;
    main_init_objects();
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
INCLUDE_ASM("asm/main/nonmatchings/main", func_8001EA10);
#endif

s32 func_8001EA78(void) {
    s16 temp_s0;
    s32 temp_lo;

    temp_s0 = func_8001EA10();
    temp_lo = temp_s0 * func_8001EA10();
    D_801E0D6C = temp_lo;
    return temp_lo;
}

s32 func_8001EAC4(s32 range) {
    if (range == 0) {
        return 0;
    }
    return func_8001EA78() % (u32) range + 1;
}

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

GameObject *main_create_box(s16 x, s16 y, s16 width, s16 height, u32 colour) {
    GameState *g;
    ObjectDef *def;

    g = &D_800AA248;
    def = func_8001D110();
    def->pos_x.s.hi = x;
    def->pos_y.s.hi = y;
    def->flags = 0x7000;
    g->cur_obj = func_8001DCB4();
    g->cur_obj->unk_40.w = width;
    g->cur_obj->script.height = height;
    g->cur_obj->colour = colour;
    g->cur_obj->flags |= 0xC;
    g->cur_obj->unk_6C |= 0x20;
    return g->cur_obj;
}

void func_8001EC74(s32 kind, s16 value) {
    GameObject *head;
    GameObject *sprite;

    head = &D_801E28C0;
    sprite = head->next;
    if (sprite != head) {
        do {
            if (sprite->kind == kind) {
                sprite->unk_74 = value;
            }
            sprite = sprite->next;
        } while (sprite != head);
    }
}

u8 *func_8001ECB4(u8 *dst, s32 value, s32 width) {
    s32 digits[8];
    s32 count;
    s32 i;
    u8 *end;

    count = 0;
    do {
        digits[count] = value;
        value /= 10;
        digits[count] -= value * 10;
        count++;
        width--;
    } while (value != 0 || width > 0);
    end = dst + count;
    dst = end;
    *end = 0;
    for (i = 0; i < count; i++) {
        *--dst = digits[i] + '0';
    }
    return end;
}

void func_8001ED54(TextMessage *arg0) {
    func_8001F39C(arg0);
    func_8001ED7C();
}

extern s32 (*D_801D858C)();

void func_8001ED7C(void) {
    func_8001F2B0();
    D_801D858C();
}

void func_8001EDB0(void) {
    func_8001F358();
    D_801D858C();
}

void func_8001EDE4(void) {
    D_801D8588.unk_20 = 0x8002;
    D_801D8588.flags = 0x10001;
    D_801D8588.unk_28 = 0x8101;
    func_8001EEA0();
}

void func_8001EE24(void) {
    D_801D8588.unk_20 = 0x8002;
    D_801D8588.flags = 0x10000;
    D_801D8588.unk_28 = 0x8101;
    func_8001EEA0();
}

void func_8001EE60(void) {
    D_801D8588.unk_20 = 0x8002;
    D_801D8588.flags = 0x10002;
    D_801D8588.unk_28 = 0x8101;
    func_8001EEA0();
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001EEA0);

void func_8001F268(void) {
}

void func_8001F270(void) {
    u16 y;

    y = D_801D8588.unk_36 + D_801D8588.unk_32;
    D_801D8588.pen_x = D_801D8588.unk_34;
    D_801D8588.pen_y = y;
    D_801D8588.unk_36 = y;
    func_8001F464();
}

#ifdef NON_MATCHING
/* 98.57%: 98.6 %: the original adds 0x80000000 (addu), every C form of the RAM range test gives subu here (also in
 * a standalone file); the rest matches. Formats the text with the word after its terminator, dereferenced when it
 * is a word-aligned RAM address */
void func_8001F2B0(void) {
    s32 word;

    word = *(s32 *) (((s32) D_801D8588.text + strlen(D_801D8588.text) + 4) & ~3);
    if ((u32) (word + 0x80000000) <= 0x1FFFFF && !(word & 3)) {
        sprintf(D_801FAF7C, D_801D8588.text, *(s32 *) word);
    } else {
        sprintf(D_801FAF7C, D_801D85A4);
    }
    D_801D85A4 = D_801FAF7C;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/main", func_8001F2B0);
#endif

void func_8001F358(void) {
    sprintf(D_801FAF7C, D_801D8588.text);
    D_801D8588.text = D_801FAF7C;
}

void func_8001F39C(TextMessage *msg) {
    D_801D8588.unk_00 = 0;
    D_801D8588.unk_04 = msg->layout;
    D_801D8588.unk_08 = msg->unk_0C;
    D_801D8588.pen_x = msg->x;
    D_801D8588.pen_y = msg->y;
    D_801D8588.unk_10 = msg->spacing;
    D_801D8588.glyphs = msg->glyphs;
    D_801D8588.unk_18 = msg->kind;
    D_801D8588.text = msg->text;
}

void func_8001F400(void) {
    Glyph *glyph;

    glyph = func_8001B128(D_801D8588.glyphs[0x27]);
    D_801D8588.unk_30 = glyph->unk_4 >> 1;
    D_801D8588.unk_32 = glyph->unk_6 + (glyph->unk_6 >> 1);
}

void func_8001F464(void) {
    s32 shift;
    s32 kind;

    kind = D_801D8588.flags & 3;
    shift = 0;
    if (kind != 1) {
        if (kind != 0) {
            if (kind == 2) {
                shift = func_8001F50C(D_801D8588.text);
            }
        }
    } else {
        shift = (s16) func_8001F50C(D_801D8588.text) >> 1;
    }
    D_801D8588.pen_x -= shift;
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

    saved0 = D_801D8588.unk_00;
    saved30 = *(s32 *) &D_801D8588.unk_30;
    saved10 = D_801D8588.unk_10;
    p = text;
    func_8001F400();
    c = *p;
    width = 0;
    while (c != 0 && c != 13 && c != 10) {
        if (D_801D8588.flags & 0x2000) {
            width += (s16) D_801D8588.unk_10;
        } else {
            if (c == 0x20) {
                width += D_801D8588.unk_30 + (s16) D_801D8588.unk_10;
            } else {
                width += func_8001B128(D_801D8588.glyphs[*p - 0x21])->unk_4 + (s16) D_801D8588.unk_10;
            }
        }
        p++;
        c = *p;
    }
    D_801D8588.unk_00 = saved0;
    *(s32 *) &D_801D8588.unk_30 = saved30;
    D_801D8588.unk_10 = saved10;
    return width;
}

void func_8001F61C(u8 *text, s16 x, s16 y, s32 spacing, s32 arg4, s32 *glyphs, s32 kind, s32 arg7) {
    D_801D8588.unk_00 = 0;
    D_800AA2EC = arg4;
    if (kind == 0) {
        D_801D8588.unk_04 = func_8001EDE4;
    } else if (kind == 1) {
        D_801D8588.unk_04 = func_8001EE24;
    } else {
        D_801D8588.unk_04 = func_8001EE60;
    }
    D_801D8588.unk_08 = arg4;
    D_801D8588.pen_x = x;
    D_801D8588.pen_y = y;
    D_801D8588.unk_10 = spacing;
    D_801D8588.glyphs = glyphs;
    D_801D8588.unk_18 = arg7;
    D_801D8588.text = text;
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

void func_8001F7F8(s32 id) {
    if ((u16) id != D_801D8750) {
        D_801D8750 = id;
        func_80063084(D_8007B100[(id & 0x7FFF) - 1]);
    }
}

void main_draw_lists(void) {
    s32 bottom;

    bottom = 0x91;
    if (D_801FA960 >= 100) {
        bottom = 0xF0;
    }
    func_8001F9BC(&D_801E28C0, &D_801E28C0);
    func_8001F9BC(&D_801E29A8, &D_801E29A8);
    if (D_801D36FC == 0x150 || (D_801D36FC == 0x160 && D_801FA960 != 0x7C)
        || (D_801D36FC == 0x120 && D_801F9AE0 == 2)) {
        if (D_801F9A38 != 0) {
            D_801FAC80->unk_7A = -(D_801F9ACC.w >> 16);
            D_801FAC80->unk_82 = -(D_801F9ACC.w >> 16);
            D_801FAC80->unk_8A = bottom - (D_801F9ACC.w >> 16);
            D_801FAC80->unk_92 = bottom - (D_801F9ACC.w >> 16);
            D_801FAC80->unk_9E = -0xA0 - (D_801F9ACC.w >> 16);
            D_801FAC80->unk_A6 = -0xA0 - (D_801F9ACC.w >> 16);
            D_801FAC80->unk_AE = -(D_801F9ACC.w >> 16);
            D_801FAC80->unk_B6 = -(D_801F9ACC.w >> 16);
            AddPrim(D_801FAC80->ot, D_801FAC80->unk_70);
            AddPrim(D_801FAC80->ot, &D_801FAC80->unk_94);
        }
    }
}

void func_8001F9BC(GameObject *head, GameObject *end) {
    func_8001F9DC(head, end);
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_8001F9DC);

#ifdef NON_MATCHING
/* 78.53%: 78.5 %: the loop body matches; the original keeps the list address in a2 with a copy in s1 across
 * func_80020704, copies the two hoisted %hi values into other saved registers after the call, and stores unk_34
 * between the terminator and unk_28. Runs the calls queued at D_801E2154: words of a handler address and its
 * object, 0 or -1 ends */
void func_800205AC(void) {
    s32 *list;
    s32 *p;

    list = (s32 *) D_801E2154;
    D_801D370C = D_800AA248.unk_38;
    D_800AA248.unk_38 = 0x10;
    D_800AA248.unk_2C = 0x807F;
    D_800AA248.dir = 0x08000800;
    D_801FA730 = 0;
    D_800AA248.unk_28.p = list;
    D_800AA248.unk_10 = (s16) D_801F9950;
    if (D_801D8584 != NULL) {
        func_80020704();
    }
    *D_800AA248.unk_28.p++ = 0;
    D_800AA248.unk_34 = &D_801F9A2C;
    D_801FB188 = 1;
    p = list;
    for (;;) {
        s32 fn;

        D_800AA248.unk_00 = *p++;
        if (D_800AA248.unk_00 == 0) {
            break;
        }
        if (D_800AA248.unk_00 == -1) {
            break;
        }
        fn = D_800AA248.unk_00 & 0x8FFFFFFC;
        D_800AA248.unk_00 = fn;
        D_801FA730++;
        D_800AA248.cur_obj = (GameObject *) *p++;
        D_800AA248.unk_30 = p;
        if ((fn & 0x80000000) != (fn & 0xFF000000)) {
            func_8001B5E8(0x13);
        }
        ((void (*)(void)) D_800AA248.unk_00)();
        p = D_800AA248.unk_30;
    }
    D_801FB188 = 0;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/main", func_800205AC);
#endif

void func_80020704(void) {
    for (D_800AA248.cur_obj = D_801D8584; D_800AA248.cur_obj != NULL; D_800AA248.cur_obj = D_800AA248.cur_obj->unk_40.obj) {
        main_step_anim();
    }
}

/* One step of the current object's animation script. A command's first word is a frame reference: an id, or the
 * frame's address (negative as an s32, see func_8001A554); odd for none. */
void main_step_anim(void) {
    s32 *p;
    s32 cmd;
    s32 flags;
    s32 set;
    SpriteFrame *frame;
    GameObject *obj;
    Fixed off;
    Fixed pos;
    Fixed o;

    D_800AA248.unk_18 = D_800AA248.cur_obj->frames_left - D_800AA248.unk_10;
    if (D_800AA248.unk_18 <= 0) {
        D_800AA248.cur_obj->unk_64.w++;
        p = (s32 *) func_8001B660(D_800AA248.cur_obj->script.pc);
        frame = (SpriteFrame *) *p++;
        if (frame == NULL) {
            p = (s32 *) func_8001B660(D_800AA248.cur_obj->anim);
            frame = (SpriteFrame *) *p++;
        }
        D_800AA248.unk_10 = D_800AA248.cur_obj->unk_6C;
        D_800AA248.unk_1C.flags = flags = D_800AA248.cur_obj->flags;
        D_800AA248.unk_18 = cmd = *(u16 *) p;
        if (cmd & 0x8000) {
            set = ((u16 *) p)[1];
            D_800AA248.unk_38 = set ^ flags;
            D_800AA248.action = set;
            D_800AA248.unk_1C.flags = (flags & 0xFFEF) | set;
        }
        p++;
        if (cmd & 0x1000) {
            D_800AA248.unk_38 = *p++;
            *D_800AA248.unk_28.p = D_800AA248.unk_38;
            *++D_800AA248.unk_28.p = (s32) D_800AA248.cur_obj;
            D_800AA248.unk_28.p++;
            D_800AA248.unk_38 &= 0x70000003;
            if (D_800AA248.unk_38 != 0) {
                D_800AA248.cur_obj->arg.p = p;
                p += (u32) (D_800AA248.unk_38 + 1) >> 1;
            }
        }
        if (!((s32) frame & 1)) {
            frame = func_8001A554((s32) frame, D_800AA248.cur_obj);
            D_800AA248.cur_obj->frame = frame;
            D_800AA248.unk_08 = D_800AA248.unk_2C & D_800AA248.unk_1C.flags;
            if (D_800AA248.unk_10 & 0x8000) {
                D_800AA248.unk_38 = D_800AA248.cur_obj->flags;
                D_800AA248.cur_obj->flags = D_800AA248.unk_08;
                D_800AA248.cur_obj->unk_2C.w = frame->size.w;
                D_800AA248.cur_obj->size.w = frame->size.w;
                obj = D_800AA248.cur_obj;
                off.w = obj->unk_7C;
                if (D_800AA248.unk_38 & 0x10) {
                    off.s.lo = -off.s.lo;
                }
                if (D_800AA248.unk_38 & 0x20) {
                    off.s.hi = -off.s.hi;
                }
                pos = obj->unk_28;
                pos.s.lo += off.s.lo;
                pos.s.hi += off.s.hi;
                o = frame->origin;
                if (D_800AA248.unk_08 & 0x10) {
                    o.s.lo = -o.s.lo;
                }
                if (D_800AA248.unk_08 & 0x20) {
                    o.s.hi = -o.s.hi;
                }
                pos.s.lo -= o.s.lo;
                pos.s.hi -= o.s.hi;
                obj->unk_28 = pos;
                D_800AA248.cur_obj->pos_x.s.hi = pos.s.lo;
                D_800AA248.cur_obj->pos_y.s.hi = pos.s.hi;
            } else {
                D_800AA248.cur_obj->flags = D_800AA248.unk_08;
                D_800AA248.cur_obj->unk_2C.w = frame->size.w;
            }
            D_800AA248.cur_obj->unk_7C = frame->origin.w;
            D_800AA248.cur_obj->unk_1C.w = frame->origin.w;
        }
        if (p != NULL) {
            D_800AA268.p->script.pc = (s32) p;
        }
        D_800AA248.unk_18 &= 0xFFF;
        if (D_800AA248.unk_18 == 0) {
            D_800AA248.unk_18 = D_800AA248.cur_obj->unk_4C;
        }
        D_800AA248.unk_10 = (s16) D_801F9950;
    }
    D_800AA248.cur_obj->frames_left = D_800AA248.unk_18;
}

void func_80020AF4(s32 id) {
    s32 *p;
    s32 *dst;
    s32 key;
    s32 value;

    D_800AA248.unk_00 = id;
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
            key = *p++;
            D_800AA248.unk_38 = key;
        } while (key != D_800AA248.unk_00);
        do {
            dst = p - 2;
            value = *p++;
            dst[0] = value;
            dst[1] = *p++;
        } while (value != 0);
    }
}

void main_set_frame(s32 id, s32 flags, GameObject *obj) {
    SpriteFrame *frame;
    Fixed origin;
    Fixed off;
    Fixed pos;
    Fixed o;
    u16 f;

    frame = func_8001A554(id, obj);
    origin = frame->origin;
    f = flags & 0x8F7F;
    obj->frame = frame;
    o = frame->size;
    obj->unk_2C = o;
    if (obj->unk_6C & 0x8000) {
        off.w = obj->unk_7C;
        obj->size = o;
        if (obj->flags & 0x10) {
            off.s.lo = -off.s.lo;
        }
        if (obj->flags & 0x20) {
            off.s.hi = -off.s.hi;
        }
        pos.s.lo = obj->unk_28.s.lo + off.s.lo;
        pos.s.hi = obj->unk_28.s.hi + off.s.hi;
        o = origin;
        if (flags & 0x10) {
            o.s.lo = -origin.s.lo;
        }
        if (flags & 0x20) {
            o.s.hi = -origin.s.hi;
        }
        pos.s.lo -= o.s.lo;
        pos.s.hi -= o.s.hi;
        obj->unk_28 = pos;
        obj->pos_x.s.hi = pos.s.lo;
        obj->pos_y.s.hi = pos.s.hi;
    }
    obj->flags = f;
    obj->unk_7C = origin.w;
    obj->unk_1C = origin;
}

void func_80020CE4(s32 arg0, s32 arg1) {
    D_801D3D7C = 0;
    SetDispMask(1);
    D_801FA9A4 = arg1 & 0xFFFF;
}

#ifdef NON_MATCHING
/* 99.36%: 99.36 %: expand_binop swaps (vel + v) into (v + vel) whenever the target is v or vel is still a MEM; the
 * original's (plus vel v) in v's register needs vel in a register and a target other than v (combine then folding
 * the copy) */
s32 func_80020D20(Npc *npc) {
    s32 v;

    v = npc->unk_30;
    v = D_800AA248.cur_obj->vel_y.w + v;
    D_800AA248.cur_obj->vel_y.w = v;
    D_800AA248.cur_obj->pos_y.w += v;
    v = npc->unk_34;
    v = D_800AA248.cur_obj->vel_x.w + v;
    D_800AA248.cur_obj->vel_x.w = v;
    v = D_800AA248.cur_obj->pos_x.w + v;
    v &= D_801D8864.w;
    D_800AA248.cur_obj->pos_x.w = v;
    if (npc->unk_4E != 0) {
        return (u8) D_800AA248.cur_obj->unk_6C >> 7;
    }
    if (!(D_800AA248.cur_obj->unk_6C & 0x80)) {
        npc->unk_4E = 1;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/main", func_80020D20);
#endif

void func_80020DDC(Npc *npc) {
    D_800AA268.p = npc->obj;
    switch (npc->action) {
        case 0x64:
            func_800211F4(npc);
            break;
        case 0x63:
            func_80021384(npc);
            break;
        case 3:
            func_80021418(npc);
            break;
        case 0x14:
            func_800216C8(npc);
            break;
        case 4:
            func_80021644(npc);
            break;
        case 1:
            func_80020FC8(npc);
            break;
        case 2:
            func_80020EDC(npc);
            break;
        default:
            npc->action = 1;
            break;
    }
}

void func_80020EDC(Npc *npc) {
    GameObject *saved;
    ObjectDef *def;

    saved = D_800AA248.cur_obj;
    func_80020D20(npc);
    if (npc->unk_50 == NULL) {
        def = D_800AA248.new_def = func_8001D110();
        def->id = 0x8000084;
        def->flags = D_800AA248.cur_obj->priority + 1;
        D_800AA248.cur_obj = func_8001DCB4();
        npc->unk_50 = D_800AA248.cur_obj;
        D_800AA248.cur_obj->owner.npc = npc;
        D_800AA248.cur_obj->kind = 0x713;
        D_800AA248.cur_obj = saved;
    }
    func_80024508(npc);
    D_8007B2C0[npc->aim & 3][npc->state & 0x1F](npc);
}

void func_80020FC8(Npc *npc) {
    GameObject *temp_a0;

    temp_a0 = npc->unk_50;
    if (temp_a0 != NULL) {
        func_8001E4B0(temp_a0);
        npc->unk_50 = NULL;
    }
    if (D_801E1CB0 == 0) {
        if (D_801D8740 != 0) {
            npc->action = 0x64;
        }
        func_800242A8();
    }
}

void func_80021034(Npc *npc) {
    if (D_8007A696 & 4) {
        func_80062E24(4);
        D_8007A696 &= 0xFFFB;
    }
}

void func_8002107C(Npc *npc) {
    if (!(D_8007A696 & 4)) {
        func_8001F7CC(0x64, 4);
        D_8007A696 |= 4;
    }
}

void func_800210C8(Npc *npc) {
    Unk7B358 *start;

    D_800AA248.cur_obj->unk_6C &= 0xFFEF;
    npc_pick_target(npc);
    start = D_8007B358[npc->start];
    D_800AA248.cur_obj->pos_x.w = D_801F9AC8.w + start->x;
    D_800AA248.cur_obj->pos_y.w = D_801F9ACC.w + start->y;
    D_800AA248.cur_obj->vel_x.w = start->vel_x;
    D_800AA248.cur_obj->vel_y.w = start->vel_y;
    D_800AA248.cur_obj->flags &= 0xFFEF;
    D_800AA248.cur_obj->flags |= start->flags;
    D_800AA248.cur_obj->priority = 0x4000;
    npc->action = 2;
    npc->unk_2A = 0;
    npc->unk_0C = 0;
    if (npc->kind == 0x11) {
        func_8003EB5C(&D_80097340, D_800AA248.cur_obj);
    } else {
        func_8003EB5C(&D_8008AE40, D_800AA248.cur_obj);
    }
}

void func_800211F4(Npc *npc) {
    Unk7B358 *start;

    if (D_801E1CB0 == 0) {
        if (npc->unk_1C != 0) {
            npc->unk_1C--;
            func_800242A8();
            return;
        }
        func_80024138(npc);
        if (npc->aim != 3) {
            npc->start = func_8001EB10(7, 0) & 1;
        } else {
            npc->start = 1;
        }
        start = D_8007B348[npc->start];
        D_800AA248.cur_obj->pos_x.w = start->x;
        D_800AA248.cur_obj->pos_y.w = D_801F9ACC.w + start->y;
        D_800AA248.cur_obj->vel_x.w = start->vel_x;
        D_800AA248.cur_obj->vel_y.w = start->vel_y;
        D_800AA248.cur_obj->flags &= 0xFFEF;
        D_800AA248.cur_obj->flags |= start->flags;
        D_800AA248.cur_obj->unk_6C |= 0x10;
        D_800AA248.cur_obj->priority = 0x50;
        npc->action = 0x63;
        npc->unk_22 = 0;
        npc->unk_2A = 0;
        npc->unk_0C = 0;
        npc->unk_1C = 0x122;
        func_8002107C(npc);
        if (npc->kind == 0x11) {
            func_8003EB5C(&D_80097DF0, D_800AA248.cur_obj);
        } else {
            func_8003EB5C(&D_8008B9C8, D_800AA248.cur_obj);
        }
    }
}

void func_80021384(Npc *npc) {
    D_800AA248.cur_obj->pos_x.w += D_800AA248.cur_obj->vel_x.w;
    D_800AA248.cur_obj->pos_y.w += D_800AA248.cur_obj->vel_y.w;
    if (npc->unk_1C != 0) {
        npc->unk_1C--;
        return;
    }
    if (D_800AA248.cur_obj->unk_6C & 0x80) {
        func_800210C8(npc);
    }
}

void func_80021418(Npc *npc) {
    func_8001F724(5);
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    npc->unk_2A = 0;
    D_800AA248.cur_obj->priority = 0x4000;
    npc->action = 4;
    npc->unk_1C = 0xF;
    if (npc->kind == 0x11) {
        func_8003EB5C(&D_80097DC0, D_800AA248.cur_obj);
    } else {
        func_8003EB5C(&D_8008B9E4, D_800AA248.cur_obj);
    }
    if (npc->unk_50 != NULL) {
        func_8001E4B0(npc->unk_50);
        npc->unk_50 = NULL;
    }
    func_800214D8(npc);
}

void func_800214D8(Npc *npc) {
    GameObject *saved;
    ObjectDef *def;
    Anim *anim;

    saved = D_800AA248.cur_obj;
    def = D_800AA248.new_def = func_8001D110();
    func_80021034(npc);
    if (npc->kind == 0x11) {
        anim = &D_8008A7A4;
    } else if (D_800AA248.cur_obj->pos_y.s.hi >= 0xF1) {
        anim = &D_8008AE08_alt;
    } else {
        anim = &D_8008AE08;
    }
    def->anim = anim;
    def->id = anim->id;
    def->pos_x.s.hi = D_800AA248.cur_obj->pos_x.s.hi;
    def->pos_y.s.hi = D_800AA248.cur_obj->pos_y.s.hi - 0x14;
    def->flags = 0x4100;
    func_8001DCB4();
    D_800AA248.cur_obj = saved;
}

void func_800215C0(s16 x, s16 y) {
    GameObject *saved;
    ObjectDef *def;

    saved = D_800AA248.cur_obj;
    def = D_800AA248.new_def = func_8001D110();
    def->pos_x.s.hi = x;
    def->pos_y.s.hi = y;
    def->flags = saved->priority + 1;
    def->anim = &D_8008ADB0;
    def->id = 0x4F0035B6;
    func_8001DCB4();
    D_800AA248.cur_obj = saved;
}

void func_80021644(Npc *npc) {
    if (npc->unk_0C != 0) {
        npc->unk_1C = 0x5A;
        npc->action = 0x64;
        func_800242A8();
        func_8002423C(npc);
        npc->state = 0;
        if (npc->kind == 0x11) {
            func_8003EB5C(&D_80097DF0, D_800AA268.p);
        } else {
            func_8003EB5C(&D_8008B9C8, D_800AA268.p);
        }
    }
}

void func_800216C8(Npc *npc) {
    Anim *anim;

    if (npc->kind == 0x11) {
        anim = &D_80097B3C;
    } else {
        anim = &D_8008B744;
    }
    if (D_800AA248.cur_obj->anim != (s32) anim) {
        D_800AA248.cur_obj->vel_x.w >>= 1;
        npc->unk_1C = 0x40;
        npc->unk_30 = 0x1000;
        func_8003EB5C(anim, D_800AA248.cur_obj);
        return;
    }
    if (npc->unk_1C == 0) {
        npc->action = 3;
        return;
    }
    npc->unk_1C--;
    D_800AA248.cur_obj->pos_x.w += D_800AA248.cur_obj->vel_x.w;
    D_800AA248.cur_obj->vel_y.w += 0x1000;
    if (D_800AA248.cur_obj->vel_y.w > 0x8000) {
        D_800AA248.cur_obj->vel_y.w = 0x8000;
    }
    D_800AA248.cur_obj->pos_y.w += D_800AA248.cur_obj->vel_y.w;
    if (D_800AA248.cur_obj->pos_y.s.hi >= 0xF1) {
        npc->action = 3;
        return;
    }
    func_80024508(npc);
}

void func_8002180C(Npc *npc) {
    Anim *anim;

    if (D_800AA248.cur_obj->unk_6C & 0x80) {
        if (D_801D8740 == 0) {
            func_80023F64(npc);
            return;
        }
        func_80023064((s16) (D_801F9ACE + 0x75));
        func_800232AC(0x36000);
        npc->unk_0C = 0;
        return;
    }
    if (npc->unk_0C != 2) {
        func_800232AC(0x36000);
        if (func_80023114(npc) == 1) {
            npc->unk_0C = 2;
            D_800AA248.cur_obj->vel_x.w >>= 2;
            D_800AA248.cur_obj->vel_y.w = 0;
            npc->unk_30 = 0;
            if (npc->kind == 0x11) {
                func_8003EB5C(&D_80097950, D_800AA248.cur_obj);
            } else {
                func_8003EB5C(&D_8008B558, D_800AA248.cur_obj);
            }
            return;
        }
        if (npc->kind == 0x11) {
            if (npc->start != 2) {
                anim = &D_80097340;
            } else {
                anim = &D_80097640;
            }
        } else {
            if (npc->start != 2) {
                anim = &D_8008AE40;
            } else {
                anim = &D_8008B248;
            }
        }
        func_8003EB5C(anim, D_800AA248.cur_obj);
        if (func_80023C58(D_801F9ACE + 0x75, npc) == 0) {
            D_800AA248.cur_obj->vel_x.w = 0;
            return;
        }
        if (npc->start == 2) {
            npc->unk_0C = npc->start;
            D_800AA248.cur_obj->vel_x.w >>= 2;
            D_800AA248.cur_obj->vel_y.w = 0;
            npc->unk_30 = 0;
            npc->start = 0;
            func_800232D8(npc);
            func_80023CFC(npc);
            return;
        }
        npc->start = 0;
        npc->unk_0C = 0;
        D_800AA248.cur_obj->vel_y.w = 0;
        npc->unk_30 = 0;
        npc->state++;
        func_800232AC(0x36000);
        if (npc->kind == 0x11) {
            func_8003EB5C(&D_80097340, D_800AA248.cur_obj);
        } else {
            func_8003EB5C(&D_8008AE40, D_800AA248.cur_obj);
        }
    }
}

void func_80021A80(Npc *npc) {
    if (npc->unk_0C != 0) {
        npc->unk_0C = 0;
        D_800AA248.cur_obj->vel_x.w = 0;
        D_800AA248.cur_obj->vel_y.w = 0;
        npc->unk_30 = 0;
        npc->unk_34 = 0;
        npc->state++;
    }
}

void func_80021ACC(Npc *npc) {
    npc->unk_0C = 0;
    if (npc->kind == 0x11) {
        func_8003EB5C(&D_80097340, D_800AA268.p);
    } else {
        func_8003EB5C(&D_8008AE40, D_800AA268.p);
    }
    if (func_80023C58(D_801F9ACE + 0xA5, npc) == 1) {
        npc->state++;
        func_800232AC(0x36000);
        D_800AA268.p->vel_y.w = 0;
        npc->unk_30 = 0;
        return;
    }
    D_800AA268.p->vel_x.w = 0;
    npc->unk_34 = 0;
}

void func_80021B94(Npc *npc) {
    npc->unk_0C = 0;
    if (npc->kind == 0x11) {
        func_8003EB5C(&D_80097340, D_800AA268.p);
    } else {
        func_8003EB5C(&D_8008AE40, D_800AA268.p);
    }
    if (func_80023C58(D_801F9ACE + 0x45, npc) == 1) {
        npc->state++;
        func_800232AC(0x36000);
        D_800AA268.p->vel_y.w = 0;
        npc->unk_30 = 0;
        return;
    }
    D_800AA268.p->vel_x.w = 0;
    npc->unk_34 = 0;
}

void func_80021C5C(Npc *npc) {
    npc->unk_0C = 0;
    if (npc->kind == 0x11) {
        func_8003EB5C(&D_80097340, D_800AA268.p);
    } else {
        func_8003EB5C(&D_8008AE40, D_800AA268.p);
    }
    if (func_80023C58(D_801F9ACE + 0xC5, npc) == 1) {
        npc->state++;
        func_800232AC(0x36000);
        D_800AA268.p->vel_y.w = 0;
        npc->unk_30 = 0;
        return;
    }
    D_800AA268.p->vel_x.w = 0;
    npc->unk_34 = 0;
}

void func_80021D24(Npc *npc) {
    npc->unk_0C = 0;
    if (npc->kind == 0x11) {
        func_8003EB5C(&D_80097340, D_800AA268.p);
    } else {
        func_8003EB5C(&D_8008AE40, D_800AA268.p);
    }
    npc->state = 0;
    func_800232AC(0x36000);
    npc->unk_30 = 0;
    D_800AA268.p->vel_y.w = 0;
    npc_pick_target(npc);
}

void func_80021DA8(Npc *npc) {
    s32 result;

    if (D_800AA248.cur_obj->unk_6C & 0x80) {
        if (D_801D8740 == 0) {
            func_80023F64(npc);
            return;
        }
        func_800242D8(npc);
        func_800232AC(0x36000);
        npc->unk_30 = 0;
        D_800AA248.cur_obj->vel_y.w = 0;
        return;
    }
    if (npc->unk_0C != 2) {
        func_800232AC(0x36000);
        if (npc->start == 2) {
            npc->unk_0C = 2;
            D_800AA248.cur_obj->vel_x.w >>= 2;
            D_800AA248.cur_obj->vel_y.w = 0;
            npc->unk_30 = 0;
            npc->start = 0;
            if (npc->kind == 0x11) {
                func_8003EB5C(&D_80097674, D_800AA248.cur_obj);
            } else {
                func_8003EB5C(&D_8008B27C, D_800AA248.cur_obj);
            }
            return;
        }
        if (func_80023114(npc) == 1) {
            npc->unk_0C = 2;
            D_800AA248.cur_obj->vel_x.w >>= 2;
            D_800AA248.cur_obj->vel_y.w = 0;
            npc->unk_30 = 0;
            if (npc->kind == 0x11) {
                func_8003EB5C(&D_80097950, D_800AA248.cur_obj);
            } else {
                func_8003EB5C(&D_8008B558, D_800AA248.cur_obj);
            }
            return;
        }
        if (npc->kind == 0x11) {
            func_8003EB5C(&D_80097340, D_800AA248.cur_obj);
        } else {
            func_8003EB5C(&D_8008AE40, D_800AA248.cur_obj);
        }
        result = main_follow_monster(npc);
        if (result == 1) {
            npc->unk_0C = 0;
            D_800AA248.cur_obj->vel_x.w = 0;
            D_800AA248.cur_obj->vel_y.w = 0;
            npc->unk_30 = 0;
            func_800233E0(npc);
            npc->state = result;
            if (npc->kind == 0x11) {
                func_8003EB5C(&D_80097C90, D_800AA248.cur_obj);
            } else {
                func_8003EB5C(&D_8008B898, D_800AA248.cur_obj);
            }
        }
    }
}

void func_80021FDC(Npc *npc) {
    s16 a;
    s16 b;
    s32 result;
    s16 side;

    if (npc->unk_0C != 0) {
        if (npc->kind == 0x11) {
            func_8003EB5C(&D_80097640, D_800AA268.p);
        } else {
            func_8003EB5C(&D_8008B248, D_800AA268.p);
        }
        result = main_approach_xy(npc);
        if (result == 1) {
            func_80023CFC(npc);
            npc->unk_0C = 0;
            npc->state++;
            D_800AA248.cur_obj->vel_x.w = 0;
            D_800AA248.cur_obj->vel_y.w = 0;
            npc->unk_30 = 0;
            npc->unk_2A = result;
            npc->unk_22 = 0x30;
            main_unwrap_target_x(&a, &b, npc);
            side = 2;
            if (b < a) {
                side = 1;
            }
            npc->unk_38 = side;
        }
    }
}

void func_800220D0(Npc *npc) {
    if (npc->unk_0C != 0) {
        if (npc->kind == 0x11) {
            func_8003EB5C(&D_800973DC, D_800AA268.p);
        } else {
            func_8003EB5C(&D_8008AF24, D_800AA268.p);
        }
        if (npc->unk_22 != 0) {
            npc->unk_22--;
            return;
        }
        npc->unk_0C = 0;
        npc->unk_2A = 0;
        npc->unk_22 = 0x30;
        npc->state++;
        npc->unk_38 = (npc->unk_38 == 1) ? 2 : 1;
        func_800232D8(npc);
        if (npc->kind == 0x11) {
            func_8003EB5C(&D_80097C90, D_800AA268.p);
        } else {
            func_8003EB5C(&D_8008B898, D_800AA268.p);
        }
    }
}

void func_800221BC(Npc *npc) {
    s16 x;

    if (D_800AA248.cur_obj->pos_y.s.hi < 0xF1) {
        D_800AA248.cur_obj->vel_y.w = 0x18000;
        npc->unk_22 = 0;
        npc->unk_2A = 0;
        if (npc->unk_0C != 0) {
            if (npc->kind == 0x11) {
                func_8003EB5C(&D_80097340, D_800AA248.cur_obj);
            } else {
                func_8003EB5C(&D_8008AE40, D_800AA248.cur_obj);
            }
        }
    } else if (npc->unk_22 == 0) {
        npc->unk_0C = 0;
        D_800AA248.cur_obj->vel_x.w = 0;
        D_800AA248.cur_obj->vel_y.w = 0;
        npc->unk_30 = 0;
        npc->unk_22 = 0xB4;
        if (D_801FA98C != 0) {
            x = D_800AA248.cur_obj->pos_x.s.hi;
            if (x >= D_801FA98C && D_801FA990 >= x) {
                npc->unk_22 = 1;
            }
        }
    } else if (--npc->unk_22 == 0) {
        npc->unk_0C = 0;
        npc->state++;
    }
}

void func_800222E8(Npc *npc) {
    D_800AA248.cur_obj->vel_y.w = 0xFFFE8000;
    if (npc->kind == 0x11) {
        func_8003EB5C(&D_80097340, D_800AA248.cur_obj);
    } else {
        func_8003EB5C(&D_8008AE40, D_800AA248.cur_obj);
    }
    func_80023E30(npc);
}

void func_8002235C(Npc *npc) {
    u16 result;

    if (npc->unk_0C != 0) {
        if (npc->kind == 0x11) {
            func_8003EB5C(&D_80097640, D_800AA268.p);
        } else {
            func_8003EB5C(&D_8008B248, D_800AA268.p);
        }
        result = func_80023AC0(npc);
        if (result == 1) {
            npc->unk_2A = 1;
            npc->unk_0C = 0;
            npc->unk_22 = 0x30;
            npc->state++;
            if (npc->unk_38 != 2) {
                if (npc->kind == 0x11) {
                    func_8003EB5C(&D_80097750, D_800AA268.p);
                } else {
                    func_8003EB5C(&D_8008B358, D_800AA268.p);
                }
            } else {
                if (npc->kind == 0x11) {
                    func_8003EB5C(&D_80097850, D_800AA268.p);
                } else {
                    func_8003EB5C(&D_8008B458, D_800AA268.p);
                }
            }
            return;
        }
        D_800AA268.p->vel_x.w = 0;
    }
}

void func_80022490(Npc *npc) {
    if (npc->unk_0C == 0) {
        if (D_800AA268.p->vel_x.w != 0) {
            goto done;
        }
    } else {
        if (D_800AA268.p->vel_x.w == 0) {
            if (npc->kind == 0x11) {
                func_8003EB5C(&D_80097640, D_800AA268.p);
            } else {
                func_8003EB5C(&D_8008B248, D_800AA268.p);
            }
        } else if (npc->kind == 0x11) {
            func_8003EB5C(&D_80097340, D_800AA268.p);
        } else {
            func_8003EB5C(&D_8008AE40, D_800AA268.p);
        }
    done:
        if (main_approach_y(npc) == 1) {
            npc->unk_2A = 0;
            npc->unk_22 = 0x30;
            npc->state++;
        }
    }
}

void func_80022578(Npc *npc) {
    if (npc->unk_0C != 0) {
        if (npc->kind == 0x11) {
            func_8003EB5C(&D_80097340, D_800AA268.p);
        } else {
            func_8003EB5C(&D_8008AE40, D_800AA268.p);
        }
        if (main_approach_x(npc) == 1) {
            npc->unk_22 = 0x30;
            npc->state++;
            npc->unk_0C = 0;
            if (npc->kind == 0x11) {
                func_8003EB5C(&D_80097C90, D_800AA268.p);
            } else {
                func_8003EB5C(&D_8008B898, D_800AA268.p);
            }
        }
    }
}

void func_80022640(Npc *npc) {
    if (func_80023114() == 0) {
        if (npc->unk_30 == 0) {
            func_800232D8(npc);
            if (func_800231E4(npc) == 1) {
                npc->unk_30 = -0x380;
            } else {
                npc->unk_2A = 1;
            }
            if (npc->kind == 0x11) {
                func_8003EB5C(&D_80097374, D_800AA268.p);
            } else {
                func_8003EB5C(&D_8008AE8C, D_800AA268.p);
            }
        }
    } else {
        npc->unk_0C = 0;
        npc->unk_2A = 0;
        npc->state++;
        D_800AA248.cur_obj->vel_x.w >>= 2;
        if (npc->kind == 0x11) {
            func_8003EB5C(&D_80097950, D_800AA248.cur_obj);
        } else {
            func_8003EB5C(&D_8008B558, D_800AA248.cur_obj);
        }
    }
}

void func_80022744(Npc *npc) {
    if (func_80023114() == 0) {
        npc->unk_2A = 0;
        if (npc->kind == 0x11) {
            func_8003EB5C(&D_80097340, D_800AA268.p);
        } else {
            func_8003EB5C(&D_8008AE40, D_800AA268.p);
        }
    } else {
        npc->unk_0C = 0;
        npc->unk_2A = 0;
        npc->state++;
        D_800AA248.cur_obj->vel_x.w >>= 2;
        if (npc->kind == 0x11) {
            func_8003EB5C(&D_80097950, D_800AA248.cur_obj);
        } else {
            func_8003EB5C(&D_8008B558, D_800AA248.cur_obj);
        }
    }
}

u16 func_800239F4(Npc *npc);

u16 func_800239F4(Npc *npc);

void func_80022814(Npc *npc) {
    if (D_800AA248.cur_obj->unk_6C & 0x80) {
        if (D_801D8740 == 0) {
            func_80023F64(npc);
            return;
        }
        func_800242D8(npc);
        func_800232AC(0x36000);
        npc->unk_0C = 0;
        return;
    }
    if (npc->unk_0C != 2) {
        func_800232AC(0x36000);
        if (func_80023114(npc) == 1) {
            npc->unk_0C = 2;
            D_800AA248.cur_obj->vel_x.w >>= 2;
            D_800AA248.cur_obj->vel_y.w = 0;
            npc->unk_30 = 0;
            if (npc->kind == 0x11) {
                func_8003EB5C(&D_80097950, D_800AA248.cur_obj);
            } else {
                func_8003EB5C(&D_8008B558, D_800AA248.cur_obj);
            }
            return;
        }
        if (npc->start == 2) {
            if (npc->kind == 0x11) {
                func_8003EB5C(&D_80097640, D_800AA248.cur_obj);
            } else {
                func_8003EB5C(&D_8008B248, D_800AA248.cur_obj);
            }
        } else {
            if (npc->kind == 0x11) {
                func_8003EB5C(&D_800973DC, D_800AA248.cur_obj);
            } else {
                func_8003EB5C(&D_8008AF24, D_800AA248.cur_obj);
            }
        }
        if (func_800239F4(npc) == 1) {
            if (npc->start == 2) {
                npc->unk_0C = npc->start;
                D_800AA248.cur_obj->vel_x.w >>= 2;
                D_800AA248.cur_obj->vel_y.w = 0;
                npc->unk_30 = 0;
                npc->start = 0;
                if (npc->kind == 0x11) {
                    func_8003EB5C(&D_80097674, D_800AA248.cur_obj);
                } else {
                    func_8003EB5C(&D_8008B27C, D_800AA248.cur_obj);
                }
                return;
            }
            npc->start = 0;
            npc->unk_0C = 0;
            D_800AA248.cur_obj->vel_y.w = 0;
            npc->unk_30 = 0;
            npc->state = 1;
            func_800232AC(0x36000);
            if (npc->kind == 0x11) {
                func_8003EB5C(&D_80097340, D_800AA248.cur_obj);
            } else {
                func_8003EB5C(&D_8008AE40, D_800AA248.cur_obj);
            }
            return;
        }
        D_800AA248.cur_obj->vel_x.w = 0;
        if (npc->kind == 0x11) {
            func_8003EB5C(&D_800973DC, D_800AA248.cur_obj);
        } else {
            func_8003EB5C(&D_8008AF24, D_800AA248.cur_obj);
        }
    }
}

void func_80022AC8(Npc *npc) {
    if (func_80023114() == 1) {
        npc->state = 2;
        npc->unk_0C = 0;
        D_800AA248.cur_obj->vel_x.w >>= 2;
        D_800AA248.cur_obj->vel_y.w = -0x8000;
        npc->unk_30 = 0;
        if (npc->kind == 0x11) {
            func_8003EB5C(&D_80097950, D_800AA248.cur_obj);
        } else {
            func_8003EB5C(&D_8008B558, D_800AA248.cur_obj);
        }
    }
}

void func_80022B64(Npc *npc) {
    if (npc->unk_0C != 0) {
        npc->unk_0C = 0;
        D_800AA248.cur_obj->vel_x.w = 0;
        npc->state = 3;
        if (npc->kind == 0x11) {
            func_8003EB5C(&D_800973DC, D_800AA248.cur_obj);
        } else {
            func_8003EB5C(&D_8008AF24, D_800AA248.cur_obj);
        }
    }
}

void func_80022BD8(Npc *npc) {
    if (func_80023CB8() == 1) {
        npc->unk_0C = 0;
        npc->state = 4;
        func_800232AC(0x36000);
        D_800AA248.cur_obj->vel_y.w = 0;
        npc->unk_30 = 0;
        if (npc->kind == 0x11) {
            func_8003EB5C(&D_80097340, D_800AA248.cur_obj);
        } else {
            func_8003EB5C(&D_8008AE40, D_800AA248.cur_obj);
        }
    }
}

void func_80022C68(Npc *npc) {
    s16 kind;

    if (npc->unk_10 == NULL) {
        npc_pick_target(npc);
    }
    func_800232D8(npc);
    kind = func_8002439C(npc);
    if (kind == 1) {
        func_800232AC(0x28000);
        return;
    }
    if (func_8002326C(kind) == 1) {
        if (npc->kind == 0x11) {
            func_8003EB5C(&D_80097C90, D_800AA268.p);
        } else {
            func_8003EB5C(&D_8008B898, D_800AA268.p);
        }
        npc->unk_0C = 0;
    } else {
        npc->unk_0C = 1;
    }
    D_800AA268.p->vel_x.w >>= 1;
    npc->state = 5;
}

void func_80022D58(Npc *npc) {
    if (npc->unk_0C != 0) {
        npc->state = 6;
        func_80022EC0(npc);
        npc->unk_2A = 1;
    }
}

void func_80022D98(Npc *npc) {
    if (func_80023114() == 1 || D_800AA268.p->vel_y.w == 0 || D_800AA268.p->pos_y.s.hi >= 0xC0) {
        func_800232AC(0x28000);
        npc->unk_30 = 0;
        D_800AA248.cur_obj->vel_y.w = 0;
        npc->state = 7;
        npc->unk_2A = 0;
        if (npc->kind == 0x11) {
            func_8003EB5C(&D_80097340, D_800AA248.cur_obj);
        } else {
            func_8003EB5C(&D_8008AE40, D_800AA248.cur_obj);
        }
    }
}

void func_80022E58(Npc *npc) {
    func_80023FAC(npc);
    if (npc->unk_0C != 2) {
        if (npc->kind == 0x11) {
            func_8003EB5C(&D_80097340, D_800AA268.p);
        } else {
            func_8003EB5C(&D_8008AE40, D_800AA268.p);
        }
    }
}

#ifdef NON_MATCHING
/* 90.64%: 90.6 %: the table part now matches but for registers (step in a1, the original v1); the start keeps x - y
 * in v1 and copies it to a0 after the pos_y load, the original copies it to a3 before */
void func_80022EC0(Npc *npc) {
    s16 x;
    s16 y;
    s16 dx;
    s16 dy;
    NpcStep **table;
    NpcStep *step;
    s32 v;

    main_unwrap_target_x(&x, &y, npc);
    dx = x - y;
    x = y;
    y = npc->target_y;
    y -= D_800AA268.p->pos_y.s.hi;
    if (dx > 0) {
        D_800AA268.p->flags &= 0xFFEF;
    } else {
        D_800AA268.p->flags |= 0x10;
    }
    x = dx >= 0 ? dx : -dx;
    dy = y >= 0 ? y : -y;
    if (dy != 0 && x >= 8) {
        do {
            dy >>= 1;
            x >>= 1;
        } while (dy >= 8 || x >= 8);
    }
    {
        s32 i = x & 7;
        s32 j = dy & 7;
        x = i;
        if (npc->kind == 0x11) {
            table = D_8007B660;
        } else {
            table = D_8007B980;
        }
        step = table[j];
        step += i;
    }
    v = step->vel_x;
    if (D_800AA248.cur_obj->vel_x.w & 0x10) {
        v = -v;
    }
    D_800AA248.cur_obj->vel_x.w = v;
    v = step->vel_y;
    D_800AA248.cur_obj->vel_y.w = y > 0 ? v : -v;
    func_8003EB5C(step->anim, D_800AA248.cur_obj);
}
#else
INCLUDE_ASM("asm/main/nonmatchings/main", func_80022EC0);
#endif

void func_80023064(s32 arg0) {
    D_800AA268.p->pos_y.u.hi = (s16) (D_801F9ACE + arg0);
}

void func_80023080(Npc *npc) {
    func_8002423C(npc);
    D_800AA248.cur_obj->flags &= ~0x10;
    npc->action = 1;
    npc->unk_1C = func_8001EB10(0xC8, 0x64);
    D_800AA248.cur_obj->pos_y.w = 0x02000000;
    D_800AA248.cur_obj->pos_x.w = 0x02000000;
    npc->state = 0;
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    npc->unk_30 = 0;
}

#ifdef NON_MATCHING
/* 88.9 %: the second branch keeps the address of D_801F9AC8 in a register across the block and reuses it; the C reloads it */
u16 func_80023114() {
    s32 x;
    s32 d;
    s32 dist;

    x = D_800AA268.p->pos_x.w;
    if (D_800AA268.p->vel_x.w < 0) {
        if (D_801F9AC8.w >= x) {
            x += D_801D8864.w;
        }
        x -= D_801F9AC8.w;
        return x <= 0x480000;
    }
    if (D_800AA268.p->vel_x.w > 0) {
        if (D_801F9AC8.w >= x) {
            d = x - D_801F9AC8.w;
            dist = d;
            if (d < 0) {
                dist = -dist;
            }
            if (dist > 0xC7FFFF) {
                x += D_801D8864.w;
            }
        }
        d = x - D_801F9AC8.w;
        return (u32) (d + 0xFEA20000) <= 0x01C20000;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/main", func_80023114);
#endif

u16 func_800231E4(Npc *npc) {
    s16 x;
    s16 limit;

    func_800232D8(npc);
    main_unwrap_target_x(&x, &limit, npc);
    if (D_800AA268.p->vel_x.w >= 0) {
        x += 0x50;
        return limit >= x;
    }
    x -= 0x50;
    return x >= limit;
}

u16 func_8002326C(s16 x) {
    if (D_800AA268.p->flags & 0x10) {
        return x <= 0;
    }
    return x >= 0;
}

void func_800232AC(s32 arg0) {
    s32 var_a0;

    var_a0 = arg0;
    if (D_800AA268.p->flags & 0x10) {
        var_a0 = -var_a0;
    }
    D_800AA268.p->vel_x.w = var_a0;
}

void func_800232D8(Npc *npc) {
    Monster *target;
    GameObject *sprite;
    s16 y;
    u16 x;

    target = npc->unk_10;
    if (target != NULL) {
        sprite = target->obj;
        if (!(target->unk_058 & 1) || (target->action == 0x37)) {
            npc_pick_target(npc);
            target = npc->unk_10;
            if ((target == NULL) || !(target->unk_058 & 1) || (target->action == 0x37)) {
                npc->target_y = 0x64;
                npc->unk_26 = (D_801F9ACA + 0xC8) & D_801D8866;
                return;
            }
            sprite = target->obj;
        }
        y = sprite->pos_y.u.hi - 0x16;
        if (y >= 0xE1) {
            y = 0x64;
        }
        npc->target_y = y;
        x = sprite->pos_x.u.hi;
        if (sprite->flags & 0x10) {
            npc->unk_26 = x - 1;
        } else {
            npc->unk_26 = x + 0x10;
        }
    }
}

void func_800233E0(Npc *npc) {
    s16 var_v0;
    Monster *temp_v0;
    GameObject *temp_v1;

    temp_v0 = npc->unk_10;
    if (temp_v0 != NULL) {
        temp_v1 = temp_v0->obj;
        if (temp_v1 == NULL) {
            npc_pick_target(npc);
            return;
        }
        npc->target_y = (s16) (temp_v1->pos_y.u.hi - 0x1E);
        npc->unk_3C = (u16) temp_v1->flags;
        if (temp_v1->flags & 0x10) {
            var_v0 = temp_v1->pos_x.u.hi - 1;
        } else {
            var_v0 = temp_v1->pos_x.u.hi + 0x10;
        }
        npc->unk_26 = var_v0;
    }
}

u16 main_approach_xy(Npc *npc) {
    s16 x;
    s16 cx;
    u16 dir;
    s32 d;

    x = npc->target_y - D_800AA248.cur_obj->pos_y.s.hi;
    if ((x >= 0 ? x : -x) < 0xB) {
        D_800AA248.cur_obj->vel_x.w = 0;
        D_800AA248.cur_obj->vel_y.w = 0;
        return 1;
    }
    dir = 8;
    if (x < 0) {
        dir = 4;
    }
    main_unwrap_target_x(&x, &cx, npc);
    if (npc->unk_3C & 0x10) {
        if (cx < x) {
            dir |= 1;
        } else {
            d = cx - x;
            if (d < 0) {
                d = -d;
            }
            cx = d;
            if (cx < 0x60) {
                dir |= 1;
            } else if (cx > 0x70) {
                dir |= 2;
            }
        }
    } else {
        if (cx > x) {
            dir |= 2;
        } else {
            d = cx - x;
            if (d < 0) {
                d = -d;
            }
            cx = d;
            if (cx < 0x60) {
                dir |= 2;
            } else if (cx > 0x70) {
                dir |= 1;
            }
        }
    }
    if (dir != 0) {
        D_800AA248.cur_obj->vel_x.w = D_8007B9A0[dir * 2];
        D_800AA248.cur_obj->vel_y.w = D_8007B9A0[dir * 2 + 1];
        return 0;
    }
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    return 1;
}

u16 main_approach_x(Npc *npc) {
    s16 x;
    s16 cx;
    u16 dir;
    s32 d;

    main_unwrap_target_x(&x, &cx, npc);
    dir = 0;
    if (npc->unk_38 == 1) {
        if (cx > x) {
            dir = 2;
        } else {
            d = x - cx;
            if (d < 0) {
                d = -d;
            }
            cx = d;
            if (cx < 0x60) {
                dir = 2;
            } else if (cx > 0x70) {
                dir = 1;
            }
        }
    } else {
        if (cx < x) {
            dir = 1;
        } else {
            d = x - cx;
            if (d < 0) {
                d = -d;
            }
            cx = d;
            if (cx < 0x60) {
                dir = 1;
            } else if (cx > 0x70) {
                dir = 2;
            }
        }
    }
    if (dir == 0) {
        D_800AA248.cur_obj->vel_x.w = 0;
        D_800AA248.cur_obj->vel_y.w = 0;
        return 1;
    }
    D_800AA248.cur_obj->vel_x.w = D_8007B9A0[dir * 2];
    D_800AA248.cur_obj->vel_y.w = D_8007B9A0[dir * 2 + 1];
    return 0;
}

u16 main_follow_monster(Npc *npc) {
    GameObject *body;
    s16 tx;
    s16 cx;
    s16 d;
    s32 t;

    if (npc->unk_10 == NULL) {
        return 0;
    }
    body = npc->unk_10->obj;
    if (body == NULL) {
        npc_pick_target(npc);
        return 0;
    }
    if (body->flags & 0x10) {
        tx = body->pos_x.u.hi + body->size.u.lo - 10;
    } else {
        tx = body->pos_x.u.hi + body->size.u.lo;
    }
    cx = D_800AA268.p->pos_x.u.hi;
    if (!(D_800AA268.p->flags & 0x10)) {
        cx += D_800AA268.p->size.u.lo;
    }
    t = tx - cx;
    if (t < 0) {
        t = -t;
    }
    if (t >= 700) {
        if (tx >= (s16) D_801D8866) {
            cx += D_801D8866;
        } else {
            tx += D_801D8866;
        }
    }
    d = tx - cx;
    if ((d >= 0 ? d : -d) < 0x61) {
        if (d <= 0) {
            if (D_800AA248.cur_obj->flags & 0x10) {
                npc->unk_0C = 2;
                if (npc->kind == 0x11) {
                    func_8003EB5C(&D_80097950, D_800AA248.cur_obj);
                } else {
                    func_8003EB5C(&D_8008B558, D_800AA248.cur_obj);
                }
            }
        } else {
            if (!(D_800AA248.cur_obj->flags & 0x10)) {
                npc->unk_0C = 2;
                if (npc->kind == 0x11) {
                    func_8003EB5C(&D_80097950, D_800AA248.cur_obj);
                } else {
                    func_8003EB5C(&D_8008B558, D_800AA248.cur_obj);
                }
            }
        }
        D_800AA268.p->vel_x.w = 0;
        return 1;
    }
    if (d <= 0) {
        if (!(D_800AA248.cur_obj->flags & 0x10)) {
            npc->unk_0C = 2;
            if (npc->kind == 0x11) {
                func_8003EB5C(&D_80097950, D_800AA248.cur_obj);
            } else {
                func_8003EB5C(&D_8008B558, D_800AA248.cur_obj);
            }
        }
    } else {
        if (D_800AA248.cur_obj->flags & 0x10) {
            npc->unk_0C = 2;
            if (npc->kind == 0x11) {
                func_8003EB5C(&D_80097950, D_800AA248.cur_obj);
            } else {
                func_8003EB5C(&D_8008B558, D_800AA248.cur_obj);
            }
        }
    }
    D_800AA268.p->vel_y.w = 0;
    func_800232AC(0x28000);
    return 0;
}

u16 func_800239F4(Npc *npc) {
    Monster *target;
    GameObject *sprite;
    s32 dy;
    s32 ady;
    s32 speed;

    target = npc->unk_10;
    if (target != NULL) {
        sprite = target->obj;
        if (sprite == NULL) {
            npc_pick_target(npc);
            return func_800239F4(npc);
        }
        dy = (s16) ((sprite->pos_y.u.hi - 0x58) - D_800AA268.p->pos_y.u.hi);
        ady = (dy >= 0) ? dy : -dy;
        if (ady < 0xB) {
            D_800AA268.p->vel_y.w = 0;
            return 1;
        }
        speed = 0xFFFE0000;
        if (dy >= 0) {
            speed = 0x10000;
        }
        D_800AA268.p->vel_y.w = speed | 0x8000;
        return 0;
    }
    D_800AA268.p->vel_y.w = 0x18000;
    return 0;
}

u16 func_80023AC0(Npc *npc) {
    s16 delta;
    s32 dist;
    s32 step;

    delta = npc->target_y - D_800AA268.p->pos_y.u.hi;
    dist = (delta >= 0) ? delta : -delta;
    if (dist < 0xB) {
        D_800AA268.p->vel_y.w = 0;
        return 1;
    }
    step = 0xFFFE0000;
    if (delta >= 0) {
        step = 0x10000;
    }
    D_800AA268.p->vel_y.w = step | 0x8000;
    return 0;
}

u16 main_approach_y(Npc *npc) {
    s16 delta;
    s32 dist;

    delta = npc->target_y - 0x6C;
    delta -= D_800AA268.p->pos_y.u.hi;
    if ((delta >= 0 ? delta : -delta) < 0xB) {
        D_800AA268.p->vel_y.w = 0;
        return 1;
    }
    if (delta >= 0) {
        D_800AA268.p->vel_y.w = 0x18000;
    } else {
        D_800AA268.p->vel_y.w = -0x18000;
    }
    dist = delta;
    if (dist < 0) {
        dist = -dist;
    }
    if (dist < 0x1F && D_800AA248.cur_obj->vel_x.w == 0) {
        npc->unk_0C = 0;
        if (npc->unk_38 != 1) {
            D_800AA248.cur_obj->vel_x.w = 0x10000;
            if (npc->kind == 0x11) {
                func_8003EB5C(&D_80097750, D_800AA248.cur_obj);
            } else {
                func_8003EB5C(&D_8008B358, D_800AA248.cur_obj);
            }
        } else {
            D_800AA248.cur_obj->vel_x.w = -0x10000;
            if (npc->kind == 0x11) {
                func_8003EB5C(&D_80097850, D_800AA248.cur_obj);
            } else {
                func_8003EB5C(&D_8008B458, D_800AA248.cur_obj);
            }
        }
    }
    return 0;
}

u16 func_80023C58(s16 arg0, Npc *npc) {
    s16 delta;
    s32 dist;
    s32 step;

    delta = arg0 - D_800AA268.p->pos_y.u.hi;
    dist = (delta >= 0) ? delta : -delta;
    if (dist < 0xB) {
        D_800AA268.p->vel_y.w = 0;
        return 1;
    }
    step = 0xFFFE0000;
    if (delta >= 0) {
        step = 0x10000;
    }
    D_800AA268.p->vel_y.w = step | 0x8000;
    return 0;
}

u16 func_80023CB8(void) {
    if (D_800AA268.p->pos_y.w - D_801F9ACC.w <= 0x2FFFFF) {
        return 1;
    }
    D_800AA268.p->vel_y.w = 0xFFFE8000;
    return 0;
}

void func_80023CFC(Npc *npc) {
    Monster *target;
    GameObject *sprite;
    u16 tx;
    u16 mx;
    s32 dx;

    target = npc->unk_10;
    if (target != NULL) {
        sprite = target->obj;
        if (sprite == NULL) {
            npc_pick_target(npc);
            return;
        }
        tx = sprite->pos_x.u.hi;
        mx = D_800AA268.p->pos_x.u.hi;
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
            npc->unk_38 = 1;
            if (npc->kind == 0x11) {
                func_8003EB5C(&D_80097850, D_800AA268.p);
            } else {
                func_8003EB5C(&D_8008B458, D_800AA268.p);
            }
        } else {
            npc->unk_38 = 2;
            if (npc->kind == 0x11) {
                func_8003EB5C(&D_80097750, D_800AA268.p);
            } else {
                func_8003EB5C(&D_8008B358, D_800AA268.p);
            }
        }
    }
}

void func_80023E30(Npc *npc) {
    GameObject *obj;
    s32 vx;
    s32 d;

    if (D_801D8740 == 0) {
        func_80023F64(npc);
        return;
    }
    obj = D_800AA268.p;
    d = obj->pos_y.w - D_801F9ACC.w;
    if (d <= 0x2FFFFF) {
        vx = obj->vel_x.w;
        if (vx != 0) {
            if (vx > 0) {
                s32 t = vx - D_801F9AC8.w;

                d = t >= 0 ? t : -t;
                if (d > 0x15E0000) {
                    goto out;
                }
            } else {
                s32 t = vx - D_801F9AC8.w;

                d = t >= 0 ? t : -t;
                if (d < 0) {
                    goto out;
                }
            }
        }
        if (!(obj->unk_6C & 0x80)) {
            return;
        }
    }
out:
    if ((D_800AA268.p->unk_6C & 0x80) || D_801E289A != 0) {
        func_80023F64(npc);
        return;
    }
    npc->unk_1C = 0;
    npc->unk_22 = 0;
    npc->state = 0;
    npc->unk_2A = 0;
    npc_pick_target(npc);
}

void func_80023F64(Npc *npc) {
    if (D_800AA268.p->unk_6C & 0x80) {
        func_800242A0();
        func_80023080(npc);
    }
}

void func_80023FAC(Npc *npc) {
    if (D_801D8740 == 0) {
        func_800240F0(npc);
        return;
    }
    if (D_800AA248.cur_obj->vel_x.w != 0) {
        if (func_80023114(npc) == 1) {
            npc->unk_0C = 2;
            npc->unk_2A = 0;
            D_800AA248.cur_obj->vel_x.w = 0;
            D_800AA248.cur_obj->vel_y.w = -0x28000;
            if (npc->kind == 0x11) {
                func_8003EB5C(&D_80097950, D_800AA248.cur_obj);
            } else {
                func_8003EB5C(&D_8008B558, D_800AA248.cur_obj);
            }
        }
    } else if (D_800AA248.cur_obj->pos_y.w - D_801F9ACC.w <= 0x2FFFFF) {
        if ((D_800AA248.cur_obj->unk_6C & 0x80) || D_801E289A != 0) {
            func_800240F0(npc);
            return;
        }
        npc->unk_1C = 0;
        npc->unk_22 = 0;
        npc->unk_2A = 0;
        npc_pick_target(npc);
        npc->state = 3;
    }
}

void func_800240F0(Npc *npc) {
    if (D_800AA268.p->unk_6C & 0x80) {
        func_800242A0();
        func_80023080(npc);
    }
}

#ifdef NON_MATCHING
/* 86.15%: 86.2 %: used and k now copy the masked value as the original does; the loop still uses used in s0
 * directly (the original copies it to a1 and hoists the table address to a2), and the bit selection reuses the
 * loop's sign-extended k where the original copies k at the exit */
u16 func_80024138(Npc *npc) {
    s16 used;
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
        npc->aim = k;
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
    npc->aim = 3;
    return 3;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/main", func_80024138);
#endif

void func_8002423C(Npc *npc) {
    s16 temp_v1;
    s32 var_a0;

    temp_v1 = npc->aim;
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
    D_800AA248.cur_obj->pos_x.w = D_801F9AC8.w - 0x1BC0000;
    D_800AA248.cur_obj->pos_y.w = 0x2000000;
}

#ifdef NON_MATCHING
/* 92.55%: 92.6 %: with -fno-cse-skip-blocks this C gives the original's reload of pos_x in the last branch, so the
 * original's CFG stopped cse there (an if/else for x does, 97.1 %, but then x and dx share a register); x and dx
 * also swap v1/a1 */
void func_800242D8(Npc *npc) {
    GameObject *obj;
    s16 dx;
    s16 x;

    obj = D_800AA268.p;
    dx = obj->pos_x.s.hi - D_801F9ACA;
    x = dx;
    if ((dx >= 0 ? dx : -dx) >= 0x2BC) {
        x = D_801D8866 + dx;
    }
    if (obj->flags & 0x10) {
        if (x > 0x258) {
            x -= 0x258;
        }
        obj->pos_x.s.hi = x + D_801D8866;
    } else if (x < -0x96) {
        obj->pos_x.s.hi += 0x96;
    }
    func_80024508(npc);
}
#else
INCLUDE_ASM("asm/main/nonmatchings/main", func_800242D8);
#endif

/* 93 %: the second block loads the sprite's x into a temporary and copies it (lh v0; move v1,v0) and leaves the branch delay slot empty; the C loads it straight into its variable */
#ifdef NON_MATCHING
s16 func_8002439C(Npc *npc) {
    s16 x;
    s32 mx;
    s32 d;

    x = npc->unk_26;
    if (x < D_801F9ACA) {
        x += D_801D8866;
    }
    mx = D_800AA268.p->pos_x.s.hi;
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
INCLUDE_ASM("asm/main/nonmatchings/main", func_8002439C);
#endif

#ifdef NON_MATCHING
/* 80.55%: the two loads of unk_26 merge into one lh (the original loads it lhu for x and again lh for the
 * difference); the absolute values live in a2, the original's in v0 */
void main_unwrap_target_x(s16 *px, s16 *pcur, Npc *npc) {
    u16 x;
    s16 cur;
    u16 half;
    s16 d;

    x = (u16) npc->unk_26;
    cur = D_800AA268.p->pos_x.s.hi;
    half = D_801D8866;
    {
        s32 t = npc->unk_26 - cur;
        if (t < 0) {
            t = -t;
        }
        d = t;
    }
    if (d >= (s16) half >> 1) {
        s32 t = D_801F9ACA - cur;
        if (t < 0) {
            t = -t;
        }
        d = t;
        if (d >= (s16) half >> 1) {
            x += half;
        } else {
            cur += half;
        }
    }
    *px = x;
    *pcur = cur;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/main", main_unwrap_target_x);
#endif

void func_800244A8(void) {
    GameObject *obj;
    GameObject *owner;
    GameObject *part;
    s32 *arg;

    obj = D_800AA248.cur_obj;
    owner = obj->owner.p;
    part = owner->unk_50.obj;
    arg = obj->arg.w;
    if (part != NULL) {
        D_800AA248.cur_obj = part;
        main_set_frame(*arg, 0x8002, part);
    }
    D_800AA248.cur_obj = obj;
}

void func_80024508(Npc *npc) {
    main_place_attached(npc->unk_50, npc);
}

void main_place_attached(GameObject *obj, Npc *npc) {
    SpriteFrame *fr;
    s32 dx;
    s32 dy;
    s32 x;

    if (obj != NULL) {
        fr = D_800AA268.p->frame;
        dx = fr->unk_24 - fr->origin.s.lo; 
        x = D_800AA268.p->pos_x.s.hi; 
        dy = fr->unk_26 - fr->origin.s.hi; 
        if (D_800AA268.p->flags & 0x10) {
            dx = -dx;
            obj->flags |= 0x10;
        } else {
            obj->flags &= ~0x10;
        }
        x += dx;
        x <<= 16;
        if (D_800AA268.p->unk_6C & 0x80) {
            obj->pos_x.w = x;
        } else {
            obj->pos_x.w = x & D_801D8864.w;
        }
        obj->pos_y.s.hi = D_800AA268.p->pos_y.s.hi + dy;
    }
}

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
    ObjectDef *request;
    GameObject *sprite;
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
            request->flags = arg2;
            request->unk_0C = arg1;
            request->id = word & 0xFF7FFFFF;
            D_800AA248.new_def = request;
            sprite = func_8001DCB4();
            sprite->pos_x.u.hi = x;
            sprite->unk_08.s.lo = x;
            top = sprite->unk_1C.u.hi + (y - sprite->size.u.hi);
            sprite->unk_08.s.hi = top;
            sprite->pos_y.s.hi = top;
            if (arg2 != 0x300) {
                sprite->unk_6C |= 0x10;
            }
            if (word & 0x800000) {
                sprite->flags |= 0x10;
                right = sprite->pos_x.u.hi + sprite->size.u.lo;
                sprite->unk_08.s.lo = right;
                sprite->pos_x.u.hi = right;
            }
        } while (--count != 0);
    }
}

#ifdef NON_MATCHING
/* 96.07%: the order and the operations match; the width and the distance swap registers (a0/v1), and the left
 * branch shifts the width into v0 where the original uses v1 */
void main_wrap_layer_x(GameObject *obj, s32 left, s32 right) {
    s32 x;
    s32 width;
    s32 d;

    x = obj->pos_x.w;
    if (D_801D3D8A <= 0) {
        x += right;
        if (x > 0) {
            d = obj->size.s.lo << 16;
            d -= 1;
            width = D_801D8864.w & 0x3FFFFFF;
            d -= width;
            if (d < 0) {
                d = -d;
            }
            if (x >= d) {
                x = x - (width + 1);
            }
        }
    } else {
        x += left;
        if (x < 0 && (obj->size.s.lo << 16) + x <= 0) {
            x = x + (1 + (D_801D8864.w & 0x3FFFFFF));
        }
    }
    obj->pos_x.w = x;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/main", main_wrap_layer_x);
#endif

#ifdef NON_MATCHING
/* 89.70%: loop.c hoists 0x510 but not 0x500 (the original keeps both in s3/s2), and the sentinel is copied into s1
 * instead of built there; one call with the bounds in locals hoists both but loses the per-case a0 */
void main_scroll_layers(void) {
    GameObject *obj;

    if (D_801D3D8A != 0) {
        for (obj = D_801E29A8.next; obj != &D_801E29A8; obj = obj->next) {
            switch (obj->kind) {
                case 0x520:
                    main_wrap_layer_x(obj, -0x4000, 0x4000);
                    break;
                case 0x500:
                    main_wrap_layer_x(obj, -0x10000, 0x10000);
                    break;
                case 0x510:
                    main_wrap_layer_x(obj, -0x8000, 0x8000);
                    break;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/main", main_scroll_layers);
#endif

void func_80024954(void) {
}

void func_8002495C(void) {
}

void func_80024964(s32 arg0, GameObject *obj) {
}

void func_8002496C(GameObject *sprite) {
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
        if (main_check_bonus_round(NULL) == 1) {
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
    Building *block;
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

void main_create_buildings(void) {
    Unk24C2C *e;
    Building *rec;
    BuildingDef *def;
    s16 n;
    u16 type;
    s16 tile;
    s32 w;

    func_80024AEC();
    n = 0;
    rec = D_801D3DC8;
    e = func_80025C08(D_80082E94);
    do {
        def = e->unk_0;
        rec->unk_01E = ++n;
        rec->def = def;
        rec->roof = e->unk_C;
        rec->unk_07A = e->unk_A;
        rec->unk_018 = e->unk_4;
        rec->unk_08A = e->unk_8;
        rec->unk_00A = e->unk_14;
        type = e->unk_12;
        rec->state = 0;
        rec->priority = type;
        switch (rec->priority) {
        case 0x300:
            tile = 0xD5;
            break;
        case 0x200:
            tile = 0xCD;
            break;
        default:
            tile = 0xC5;
            break;
        }
        rec->bottom = tile;
        w = def->unk_04 - 9;
        rec->left = e->unk_10;
        rec->right = e->unk_10 + w;
        if (def->unk_00.w != 4) {
            rec->unk_05C = def->unk_08;
            rec->unk_060 = def->unk_0C;
            rec->unk_064 = def->unk_10;
            rec->frames = def->frames;
            rec->unk_08C = def->unk_18;
            rec->kind = def->unk_00.u.lo;
            rec->unk_01C = func_8001EB10(0x1E, 0) % 2 + 1;
            rec->unk_034 = 1;
            rec->unk_036 = 1;
            rec->unk_02A = 1;
            func_80024E08(rec);
        } else {
            func_80025124(rec);
        }
        rec++;
        e++;
    } while (e->unk_0 != NULL);
    D_801E29A4 = n;
    D_801E1E40 = n;
    main_set_building_sides();
}

#ifdef NON_MATCHING
/* 72.10%: 72 %: the original keeps the address of D_80011BA4 computed twice and one compare of def against it (an
 * if/else-if on D_80011BA4/_alt whose bodies vanished after flow); without that remnant the loop is smaller,
 * %hi(D_801F9948) is hoisted into a saved register and priority spills to the stack */
extern u8 D_80011BA4[];
extern u8 D_80011BA4_alt[];
extern s16 D_8007A686;
extern s32 D_800AA25C;
void func_80025474(Building *b);

void func_80024E08(Building *rec) {
    ObjectDef *req;
    BuildingItem *item;
    GameObject *obj;
    SpriteFrame *frame;
    BuildingDef *def;
    s32 *ids;
    s32 id;
    s16 i;
    s16 y;
    u16 prio;
    u16 count;
    s32 unused;

    req = func_8001D110();
    item = rec->items;
    i = 1;
    req->unk_0C = 0x710;
    req->pos_x.s.hi = rec->left;
    y = rec->bottom - 0x1D;
    prio = rec->priority;
    def = rec->def;
    memset(D_801F9948, 0, 0xCC);
    ids = def->unk_20;
    id = def->unk_20[0];
    if (id != 0) {
        do {
            req->id = id;
            frame = func_8001A554(id, (GameObject *) D_801F9948);
            if (i != 1) {
                y -= frame->size.u.hi;
            }
            req->pos_y.s.hi = y;
            if (rec->def == (BuildingDef *) D_80011BA4) {
                unused = 1;
            } else if (rec->def == (BuildingDef *) D_80011BA4_alt) {
                unused = 2;
            }
            D_800AA284.p = req;
            obj = func_8001DCB4();
            item->obj = obj;
            obj->owner.p = item;
            obj->priority = prio;
            item->unk_04 = i;
            if (i != 1) {
                obj->priority = rec->priority - 9;
            }
            item->building = rec;
            item->unk_24.unk_04 = 2;
            item->unk_0C.unk_04 = 1;
            item->unk_3C.unk_04 = 3;
            item++;
            ids++;
            id = *ids;
            i++;
        } while (id != 0);
    }
    item--;
    rec->unk_070 = item;
    obj = item->obj;
    count = i - 1;
    rec->state = 0;
    rec->unk_000 = count;
    rec->top = obj->pos_y.u.hi + obj->size.u.hi - 0xC;
    func_80025BBC(rec);
    func_8002546C(rec);
    func_800252CC(rec);
    D_800AA25C = rec->kind;
    rec->unk_012 = ((rec->kind * (((s16) (count - 1) - 1) * 3) + 2) * (D_8007A686 << 16)) / 100 >> 16;
    if (rec->unk_018 != NULL) {
        func_80025474(rec);
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/main", func_80024E08);
#endif

void func_8002503C(Building *building, GameObject *obj) {
    GameObject *saved;
    GameObject *sprite;
    ObjectDef *def;

    saved = D_800AA248.cur_obj;
    def = D_800AA248.new_def = func_8001D110();
    if (D_801FA960 == 0x63) {
        def->anim = D_800136A4;
    } else {
        def->anim = D_80013654;
    }
    def->id = *(s32 *) def->anim;
    def->unk_1C = 0;
    def->pos_x.s.hi = building->left + 0x2F;
    def->pos_y.s.hi = building->bottom - 0x3A;
    def->flags = obj->priority + 1;
    sprite = func_8001DCB4();
    sprite->kind = 0x728;
    D_801D874C = sprite;
    sprite->priority = obj->priority + 1;
    D_800AA268.p = saved;
}

void func_80025124(Building *rec) {
    BuildingDef *def;
    ObjectDef *request;
    GameObject *sprite;
    BuildingItem *item;
    u16 kind;

    def = rec->def;
    rec->unk_058 = 1;
    rec->unk_05C = (void *) def->unk_0C;
    rec->unk_060 = (void *) def->unk_10;
    rec->kind = def->unk_00.u.lo;
    request = func_8001D110();
    request->unk_0C = 0x728;
    request->pos_y.u.hi = rec->bottom;
    request->pos_x.u.hi = rec->left;
    kind = rec->priority;
    item = &rec->items[0];
    if (def->unk_08 != 0) {
        request->id = def->unk_08;
        D_800AA284.p = request;
        sprite = func_8001DCB4();
        rec->items[0].obj = sprite;
        sprite->owner.p = item;
        sprite->priority = kind;
        item->building = rec;
        item->unk_04 = 1;
        rec->unk_000 = 1;
        rec->unk_00A = 0;
        rec->unk_070 = item;
        if (def == &D_800135E8) {
            rec->top = sprite->pos_y.u.hi - 0x5C;
            sprite->kind = 0x72A;
            rec->unk_058 = 2;
            rec->unk_012 = 2;
            func_8002503C(rec, sprite);
        } else if (def == &D_8001687C) {
            rec->top = sprite->pos_y.u.hi - 0x3E;
            sprite->kind = 0x72A;
            rec->unk_058 = 3;
            rec->unk_012 = 0x7D;
        } else {
            rec->unk_012 = 5;
            if ((D_800AA2DC != 0) && (bonus_get_round_kind() == 4)) {
                u16 y = sprite->pos_y.u.hi;

                rec->unk_058 = 0;
                rec->top = y - 0x1F;
            } else {
                rec->top = sprite->pos_y.u.hi - 0x3E;
            }
        }
        func_800252CC(rec);
    }
}

extern BuildingPatch D_8007BA40[];

void func_800252CC(Building *building) {
    BuildingDef *def;
    BuildingPatch *p;
    BuildingItem *item;
    s32 code;

    def = building->def;
    func_800253F0(building, 2);
    for (p = D_8007BA40; p->def != NULL; p++) {
        if (p->def == def) {
            code = p->code;
            if (code == 0xFFFF) {
                func_800253F0(building, 0);
            } else if ((u32) (code - 0xFFF0) < 15) {
                item = building->items;
                item += 0xFFFF - code;
                item->unk_0C.unk_14 = 1;
                item->unk_24.unk_14 = 1;
                item->unk_3C.unk_14 = 1;
            } else if ((u32) (code - 0x1FFFD) < 3) {
                func_800253F0(building, 0x20000 - code);
            } else {
                *(s16 *) (code + (s32) building + 0xAC) = 1;
            }
        }
    }
}

void func_800253F0(Building *block, u32 which) {
    u16 n;
    BuildingItem *item;
    BuildingPart *part;

    n = block->unk_000;
    if (n != 0) {
        item = block->items;
        n--;
        if (n != 0) {
            do {
                part = &item->unk_0C;
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

void func_8002546C(Building *rec) {
}

#ifdef NON_MATCHING
/* 94.53%: 94.5 %: the sum y and last swap registers (a1/a3), which moves last's subtract out of the branch's delay
 * slot; statement and declaration orders tried */
void func_80025474(Building *b) {
    BuildingBlock *blk;
    ObjectDef *def;
    GameObject *obj;
    GameObject *top;
    s16 n;
    s16 last;
    s16 k;
    s32 y;
    s16 h;

    if (b->unk_018 != NULL) {
        blk = (BuildingBlock *) D_801F9AD8;
        def = func_8001D110();
        def->unk_0C = 0x719;
        def->flags = 0x300;
        blk->unk_1C = 2;
        blk->unk_0C = def->pos_x.s.hi = b->right + 1;
        n = b->unk_08A;
        last = b->unk_000 - 1;
        top = b->unk_070->obj;
        y = top->pos_y.u.hi + top->size.u.hi;
        if (n < 2) {
            n = 2;
        }
        if (last < n) {
            n = last;
        }
        blk->unk_0A = n;
        k = last - n;
        for (; k != 0; k--) {
            y += 0x18;
        }
        def->pos_y.s.hi = y + 0xC;
        def->anim = *(void **) b->unk_018;
        def->id = *(s32 *) def->anim;
        blk->unk_04 = ((s32 *) b->unk_018)[1];
        def->flags = b->priority;
        D_800AA284.p = def;
        obj = func_8001DCB4();
        h = obj->pos_y.s.hi - obj->unk_1C.s.hi;
        blk->unk_0E = h;
        blk->unk_00 = obj;
        blk->unk_1E = h + obj->size.u.hi;
        b->unk_018 = blk;
        obj->unk_94.p = blk;
        obj->owner.building = b;
        blk++;
        D_801F9AD8 = (u8 *) blk;
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/main", func_80025474);
#endif

void func_800255E0(BuildingItem *arg0) {
    GameObject *temp_a0;
    GameObject *temp_a0_2;
    GameObject *temp_a0_3;

    temp_a0 = arg0->unk_0C.unk_00;
    if (temp_a0 != NULL) {
        func_8001E4B0(temp_a0);
    }
    temp_a0_2 = arg0->unk_24.unk_00;
    if (temp_a0_2 != NULL) {
        func_8001E4B0(temp_a0_2);
    }
    temp_a0_3 = arg0->unk_3C.unk_00;
    if (temp_a0_3 != NULL) {
        func_8001E4B0(temp_a0_3);
    }
}

void func_80025648(BuildingItem *arg0) {
    GameObject *temp_a0;
    GameObject *temp_a0_2;
    GameObject *temp_a0_3;

    temp_a0 = arg0->unk_0C.unk_10;
    if (temp_a0 != NULL) {
        func_8001E4B0(temp_a0);
    }
    temp_a0_2 = arg0->unk_24.unk_10;
    if (temp_a0_2 != NULL) {
        func_8001E4B0(temp_a0_2);
    }
    temp_a0_3 = arg0->unk_3C.unk_10;
    if (temp_a0_3 != NULL) {
        func_8001E4B0(temp_a0_3);
    }
}

void func_800256B0(BuildingItem *arg0) {
    arg0->unk_0C.unk_00 = 0;
    arg0->unk_0C.unk_10 = 0;
    arg0->unk_24.unk_00 = 0;
    arg0->unk_24.unk_10 = 0;
    arg0->unk_3C.unk_00 = 0;
    arg0->unk_3C.unk_10 = 0;
}

void func_800256CC(BuildingItem *slots) {
    Ai *ai;
    GameObject *current;

    ai = slots->unk_0C.unk_08;
    current = D_800AA248.cur_obj;
    if (ai != NULL) {
        D_800AA248.cur_obj = ai->obj;
        func_8003DAA0(ai);
    }
    ai = slots->unk_24.unk_08;
    if (ai != NULL) {
        D_800AA248.cur_obj = ai->obj;
        func_8003DAA0(ai);
    }
    ai = slots->unk_3C.unk_08;
    if (ai != NULL) {
        D_800AA248.cur_obj = ai->obj;
        func_8003DAA0(ai);
    }
    D_800AA248.cur_obj = current;
}

void func_8002575C(BuildingItem *arg0) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;

    temp_a0 = (s32) arg0->unk_0C.unk_0C;
    if (temp_a0 != 0) {
        func_8003C894(temp_a0);
    }
    temp_a0_2 = (s32) arg0->unk_24.unk_0C;
    if (temp_a0_2 != 0) {
        func_8003C894(temp_a0_2);
    }
    temp_a0_3 = (s32) arg0->unk_3C.unk_0C;
    if (temp_a0_3 != 0) {
        func_8003C894(temp_a0_3);
    }
}

void func_800257C4(BuildingItem *arg0) {
    func_800255E0(arg0);
    func_80025648(arg0);
}

void func_800257F0(BuildingItem *arg0) {
    GameObject *temp_a0;

    temp_a0 = arg0->obj;
    if (temp_a0 != NULL) {
        func_8001E4B0(temp_a0);
        func_800255E0(arg0);
        func_80025648(arg0);
        func_800256CC(arg0);
        func_8002575C(arg0);
    }
}

void func_80025848(BuildingItem *arg0) {
    if (arg0->obj != 0) {
        func_800255E0(arg0);
        func_80025648(arg0);
        func_800256CC(arg0);
        func_8002575C(arg0);
    }
}

void func_80025898(BuildingItem *arg0) {
    GameObject *temp_a0;

    temp_a0 = arg0->obj;
    if (temp_a0 != NULL) {
        func_8001E4B0(temp_a0);
    }
}

void main_set_building_sides(void) {
    Building *b;
    Building *o;
    u32 pri;
    u16 i;
    u16 n;
    u16 side;
    u16 ol;
    u16 bl;
    u16 br;
    u16 orr;

    b = D_801D3DC8;
    i = D_801E29A4;
    if (i == 0) {
        return;
    }
    pri = b->priority;
    while (pri != 0x200) {
        b++;
        if (--i == 0) {
            break;
        }
        pri = b->priority;
    }
    if (pri != 0x200) {
        return;
    }
    n = D_801E29A4;
again:
    o = D_801D3DC8;
    do {
        if (pri < o->priority) {
            ol = o->left;
            bl = b->left;
            br = b->right;
            orr = o->right;
            if ((s16) ol > (s16) bl || (s16) orr <= (s16) br) {
                if ((s16) ol < (s16) bl) {
                    if ((s16) bl < (s16) orr) {
                        side = o->unk_000;
                        if (side >= b->unk_000) {
                            side = -1;
                        } else if (side == 1) {
                            side = 4;
                        } else {
                            side++;
                        }
                        b->left_side = side;
                        if ((s16) orr - (s16) bl > 0x28) {
                            b->unk_026 = side;
                        }
                    }
                } else if ((s16) ol < (s16) br) {
                    if ((s16) orr >= (s16) br || (s16) br - (s16) orr < 0x14) {
                        side = o->unk_000;
                        if (side >= b->unk_000) {
                            side = -1;
                        } else if (side == 1) {
                            side = 4;
                        } else {
                            side++;
                        }
                        b->right_side = side;
                        if ((s16) br - (s16) ol > 0x28) {
                            b->unk_026 = side;
                        }
                    }
                }
            } else {
                side = o->unk_000;
                if (side >= b->unk_000) {
                    side = -1;
                } else if (side == 1) {
                    side = 4;
                } else {
                    side++;
                }
                b->left_side = side;
                b->right_side = side;
                b->unk_026 = side;
            }
        }
        o++;
    } while (--n != 0);
    n = D_801E29A4;
    while (b->unk_01E != n) {
        b++;
        pri = b->priority;
        if (pri == 0x200) {
            goto again;
        }
    }
}

void func_80025B10(void) {
    if (D_801E1E40 == 0) {
        D_801D3780 = 0;
        D_801D36FC = 0x160;
    }
}

void func_80025B3C(Building *block) {
    if ((u32) block >= (u32) D_801D3DC8 && (u32) block < (u32) &D_801D3DC8[13]) {
        memset(block, 0, 0x98);
    }
}

void func_80025B7C(BuildingItem *item) {
    if ((u32) item >= (u32) D_801D3DC8 && (u32) item <= (u32) &D_801D3DC8[13]) {
        memset(item, 0, sizeof(BuildingItem));
    }
}

void func_80025BBC(Building *block) {
    s16 *p;
    u16 n;

    p = block->unk_03A;
    if (block->unk_038 == 0) {
        n = block->unk_000;
        block->unk_036 = 1;
        block->unk_038 = n + 9;
        n--;
        do {
            *p++ = 1;
        } while (--n != 0);
    }
}

void *func_80025C08(void *list) {
    void **table;
    u16 index;

    table = ((void ***) list)[D_801D8728];
    if (D_801D8728 != 0) {
        index = D_801FA964;
    } else {
        index = D_801FA960;
    }
    return table[index];
}

u16 main_check_bonus_round(void *arg0) {
    s16 level = D_801FA960 % 25;
    switch (level) {
    case 4:
        D_800AA2DC |= 1 << (D_801D8740 - 1);
        break;
    case 9:
        D_800AA2DC |= 1 << (D_801D8740 + 2);
        break;
    case 14:
        D_800AA2DC |= 1 << (D_801D8740 + 8);
        break;
    case 19:
        if (D_801D8740 >= 2) {
            D_800AA2DC |= 1 << (D_801D8740 + 5);
        } else {
            D_800AA2DC |= 1 << (D_801D8740 - 1);
        }
        break;
    case 23:
        if (D_801D8740 >= 2) {
            D_800AA2DC |= 1 << (D_801D8740 + 11);
        } else {
            D_800AA2DC |= 1 << (D_801D8740 + 8);
        }
        break;
    }
    if (D_800AA2DC != 0) {
        D_801D8728 = D_801D8740;
        D_801FA964 = bonus_get_round_kind();
        D_801D3780 = 99;
        return 1;
    }
    return 0;
}

s32 func_80025DF8(s32 id) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if ((u8) D_801FA8A0[i] == id) {
            return i + 1;
        }
    }
    for (i = 0; i < 7; i++) {
        if ((u8) D_801FA8A0[i] == 0) {
            return i + 1;
        }
    }
    return 1;
}

INCLUDE_ASM("asm/main/nonmatchings/main", func_80025E68);

void func_800267CC(Monster *monster) {
    s32 i;

    i = 0;
    if (monster->id == 5 && monster->meter.w == 0x440000 && !(monster->unk_01A & 0xF)) {
        monster->unk_01A |= 3;
        func_8002A1AC(monster, 3);
        i = 0;
    }
    for (i = 0; i < 2; i++) {
        if (monster->extra[i] != NULL) {
            switch (monster->id) {
            case 5:
                monster_anim_update_projectile(monster, i);
                break;
            case 7:
                monster_anim_update_bomb(monster);
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
    if ((m1->id != 0) && (m3->obj != NULL)) {
        x1 = m1->obj->pos_y.u.hi;
    }
    if ((m2->id != 0) && (m3->obj != NULL)) {
        x2 = m2->obj->pos_y.u.hi;
    }
    if ((m3->id != 0) && (m3->obj != NULL)) {
        x3 = m3->obj->pos_y.u.hi;
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
    GameObject *temp_v1;
    GameObject *temp_v1_2;
    GameObject *temp_v1_3;

    var_s2 = 0xE1;
    var_s5 = 0xE1;
    var_s4 = 0xE1;
    temp_s3 = &D_801E0B78[func_80025DF8(1)];
    temp_s1 = &D_801E0B78[func_80025DF8(2)];
    temp_a0 = &D_801E0B78[func_80025DF8(3)];
    if (temp_s3->id != 0) {
        temp_v1 = temp_s3->obj;
        if (temp_v1 != NULL) {
            var_s4 = temp_v1->pos_y.u.hi;
        }
    }
    if (temp_s1->id != 0) {
        temp_v1_2 = temp_s1->obj;
        if (temp_v1_2 != NULL) {
            var_s5 = temp_v1_2->pos_y.u.hi;
        }
    }
    if (temp_a0->id != 0) {
        temp_v1_3 = temp_a0->obj;
        if (temp_v1_3 != NULL) {
            var_s2 = temp_v1_3->pos_y.u.hi;
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
    GameObject *temp_v1;

    temp_v1 = arg0->obj;
    D_800AA268.p = temp_v1;
    if ((temp_v1 != 0) && (arg0->dir == 0)) {
        var_a1 = 3;
        if (arg0->unk_168 == 7) {
            var_a1 = 7;
        }
        arg0->last_dir = var_a1;
    }
}

void func_80026C04(Monster *monster) {
    void (**handler)(Monster *);

    D_800AA268.p = monster->obj;
    handler = &D_8007BE20[monster->action];
    (*handler)(monster);
}

void func_80026C4C(Monster *arg0) {
    u16 value;

    if ((arg0->unk_0D0 & 2) && !(func_80027348() & 0xFFFF) && !(func_80026D54(arg0) & 0xFFFF)) {
        if (arg0->unk_18E == 0) {
            value = arg0->unk_03C;
            if (value != 0) {
                if (func_80026D90(arg0) & 0xFFFF) {
                    goto skip;
                }
                value = 0;
            }
            arg0->unk_03E = value;
            arg0->unk_03C = value;
        skip:
            arg0->unk_18A = 0;
            func_80026CFC(arg0);
            return;
        }
        arg0->action = 0x40;
    }
}

void func_80026CFC(Monster *arg0) {
    u16 temp_v1;

    D_800AA248.unk_38 = arg0->id;
    func_80026E0C(arg0);
    temp_v1 = arg0->action;
    if ((temp_v1 != 2) && (temp_v1 != 0x4E)) {
        func_80026DE4(arg0)(arg0);
    }
}

s32 func_80026D54(Monster *monster) {
    u16 state;

    state = monster->action;
    if (state != 2 && state != 0x4E && state != 0x11 && monster->unk_05C == 0x16) {
        return 1;
    }
    return 0;
}

s32 func_80026D90(Monster *monster) {
    if (D_801D36FC == 0x240) {
        return 1;
    }
    switch (monster->action) {
    case 0:
    case 1:
    case 5:
    case 6:
        return 0;
    }
    return 1;
}

void (*func_80026DE4(void *arg0))(void *) {
    D_800AA248.unk_38 = ((Monster *) arg0)->unk_058;
    D_800AA248.unk_00 = ((Monster *) arg0)->id;
    return func_800585C0;
}

void func_80026E0C(Monster *arg0) {
    s32 temp_v1;
    u16 temp_v0;

    temp_v0 = arg0->action;
    temp_v1 = temp_v0 & 0xFFFF;
    arg0->unk_05C = temp_v0;
    if ((temp_v1 == 2) || (temp_v1 == 0x4E)) {
        if (arg0->unk_104 == 0) {
            arg0->unk_104 = 0x4000;
            D_800AA268.p->vel_y.w = 0xFFFB0000;
        }
        arg0->action = 0x16U;
        return;
    }
    arg0->action = 4U;
}

void func_80026E6C(Monster *m) {
    if ((m->unk_0D0 & 1) && func_800272B0(m) == 0) {
        if (m->action == 2) {
            if (m->unk_104 == 0 || D_800AA268.p->vel_y.w == 0) {
                return;
            }
        } else if (m->action == 0x53) {
            m->action = 0x54;
            return;
        } else if (m->action == 0x2C && m->unk_104 != 0 && D_800AA268.p->vel_y.w != 0) {
            m->unk_05C = 2;
            func_80026F58(m);
            return;
        }
        m->unk_05C = m->action;
        func_80026F58(m);
    }
}

void func_80026F58(Monster *arg0) {
    D_800AA248.unk_38 = arg0->id;
    arg0->action = 3;
    arg0->unk_0DE = 1;
    arg0->unk_18A = 0;
    arg0->unk_126 = 0;
    func_80057DD8();
}

#ifdef NON_MATCHING
/* 89.9 %: the call's argument is set up early and the (u16)(state - 5) truncation is kept in the original. */
void func_80026F98(Monster *arg0) {
    u16 temp_v1;

    D_800AA248.cur_obj = arg0->obj;
    if ((arg0->unk_0D0 & 4) && !(func_800272FC() & 0xFFFF)) {
        temp_v1 = arg0->action;
        if (temp_v1 == 0x53) {
            arg0->action = 0x54U;
            return;
        }
        arg0->unk_152 = (u16) (temp_v1 - 5) < 2;
        arg0->action = 2U;
        func_800580F8(arg0);
        if (arg0->unk_18E == 0) {
            arg0->action = 0x4EU;
        }
        arg0->climb_side = 0;
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/main", func_80026F98);
#endif

extern s16 D_80084278;

void main_use_full_meter(Monster *m) {
    u16 action;
    s16 n;

    if ((m->unk_0D0 & 8) && (D_800AA2DC == 0 || (D_800AA2DC & 0x7000)) && m->meter.w == 0x440000) {
        switch (m->id) {
        case 1:
        case 2:
            if (m->obj->pos_y.w == 0xE10000 && m->action < 2) {
                goto end_power;
            }
            break;
        case 3:
        case 4:
        case 7:
            if (m->action < 2) {
                if (m->id == 3) {
                    m->meter.w = 0;
                }
                goto end_power;
            }
            break;
        case 5:
            if (m->action != 0x63 && D_80084278 == 0
                && (m->action < 2 || m->action == 5 || m->action == 6 || m->action == 2 || m->action == 0x19)) {
                action = m->action;
                if (action == 1 || action == 5 || action == 6 || action == 0) {
                    func_800531C0(m);
                    m->unk_05C = m->action;
                    m->action = 0x63;
                } else if (action == 2 || action == 0x19) {
                    if (m->obj->vel_y.s.hi != 0) {
                        m->unk_05C = action;
                        m->action = 0x63;
                    }
                }
                if (m->action == 0x63) {
                    if ((m->unk_01A & 0xF) != 0) {
                        n = (m->unk_01A & 0xF) - 1;
                        m->unk_01A &= 0xFFF0;
                        m->unk_01A |= n;
                        if (n < 3 && m->extra[n + 2] != NULL) {
                            func_8001E4B0(m->extra[n + 2]);
                            m->extra[n + 2] = NULL;
                        }
                        if (!(m->unk_01A & 0xF)) {
                            m->meter.w = 0;
                        }
                    } else {
                        m->meter.w = 0;
                    }
                }
            }
            break;
        case 6:
            if (m->action < 2 || m->action == 5 || m->action == 6) {
            end_power:
                func_800531C0(m);
                m->action = 0x63;
                m->unk_188 = 0;
                m->extra[0] = NULL;
            }
            break;
        }
    }
}

u16 func_800272B0(Monster *monster) {
    u16 *p;

    for (p = D_8007BFBC; *p != 0xFFFF; p++) {
        if (*p == monster->action) {
            return 0;
        }
    }
    return 1;
}

s32 func_800272FC(Monster *monster) {
    u16 *p;

    for (p = D_8007BFD4; *p != 0xFFFF; p++) {
        if (*p == monster->action) {
            return 0;
        }
    }
    return 1;
}

s32 func_80027348(Monster *monster) {
    u16 *p;

    for (p = D_8007BFEC; *p != 0xFFFF; p++) {
        if (*p == monster->action) {
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
                    monster->idle_timer = 0x1A4;
                }
                held = monster->buttons;
                monster->buttons = buttons;
                func_8002808C(buttons, held, monster);
                dir = script[1];
                if (dir != 0) {
                    monster->idle_timer = 0x1A4;
                }
                prevDir = monster->dir;
                monster->dir = dir;
                func_80028140(prevDir, monster, dir);
                func_80028140(prevDir, monster, dir);
                if (dir != 0) {
                    monster->last_dir = dir;
                }
                if (prevDir == dir) {
                    monster->dir_frames++;
                } else {
                    monster->dir_frames = 0;
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
        monster->idle_timer = 0x1A4;
    }
    held = monster->buttons;
    monster->buttons = buttons;
    func_8002808C(buttons, held, monster);
    dir = D_8007C124[bits & 0xF];
    if (dir != 0) {
        monster->idle_timer = 0x1A4;
    }
    prevDir = monster->dir;
    monster->dir = dir;
    func_80028140(prevDir, monster, dir);
    if (dir != 0) {
        monster->last_dir = dir;
    }
    if (prevDir == dir) {
        monster->dir_frames++;
    } else {
        monster->dir_frames = 0;
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/main", func_800273F4);
#endif

extern s16 D_801D3DB2[];
s32 func_80027878(Monster *m);

void main_move_monster(Monster *m) {
    GameObject *obj;
    s32 vx;
    s32 vel;
    s16 dir;
    s32 y;
    s32 t;

    if (m->action == 0x53 || m->action == 0x57) {
        return;
    }
    obj = m->obj;
    D_800AA268.p = obj;
    vel = vx = obj->vel_x.w;
    if (vx != 0) {
        if ((u16) m->unk_1C8 != 0) {
            goto clamp;
        }
        if (m->action == 0x37 || m->action == 0x2F) {
            goto clamp;
        }
        if (m->action == 2) {
            vel >>= 1;
        } else {
            vel >>= 2;
        }
        vel = -vel;
        if (vel > 0x10000) {
            vel = 0x10000;
        } else if (vel < -0x10000) {
            vel = -0x10000;
        }
    }
    vel += vx;
    if (m->unk_100 != 0) {
        vel += m->unk_100;
    } else if (vx >= -0x800 && vx <= 0x800) {
        m->unk_100 = 0;
        obj->vel_x.w = 0;
        goto vertical;
    }
clamp:
    t = *(D_801D3D98 + D_801FA8A0[m->id - 1]);
    if (vel >= 0) {
        dir = 1;
        if (t > 0x16C0000 && t <= 0x1C20000) {
            vel = 0;
        }
    } else {
        dir = -1;
        if (t < 0x200000 || t > 0x1C1FFFF) {
            vel = 0;
        }
    }
    *(D_801D3DB2 + D_801FA8A0[m->id - 1]) = dir;
    t = obj->pos_x.w;
    if (vel > 0x58000) {
        vel = 0x58000;
    } else if (vel < -0x58000) {
        vel = -0x58000;
    }
    obj->vel_x.w = vel;
    t += vel;
    t &= D_801D8864.w;
    obj->pos_x.w = t;
vertical:
    if (obj->vel_y.w != 0 || m->unk_104 != 0) {
        if ((u16) func_80027878(m) == 0) {
            vel = obj->vel_y.w;
            t = m->unk_104 + vel;
            if (t > 0xC0000) {
                t = 0xC0000;
            }
            obj->vel_y.w = t;
            if (t != 0) {
                y = obj->pos_y.w + t;
                if (m->climb_side == 0 && y > 0xE0FFFF && m->action != 0x1F) {
                    y = 0xE10000;
                }
                obj->pos_y.w = y;
            }
        }
    }
}

s32 func_80027878(Monster *m) {
    GameObject *obj;
    s32 vel;
    s32 y;

    if (m->unk_18E == 0 && m->climb_side == 0) {
        return 0;
    }
    obj = D_800AA268.p;
    y = obj->pos_y.w;
    vel = obj->vel_y.w;
    y += vel;
    y -= D_801F9ACC.w;
    if (vel == 0) {
        return 0;
    }
    if (vel < 0) {
        if (y > 0x5FFFFF) {
            return 0;
        }
        if (m->unk_104 < 0) {
            return 1;
        }
        obj->vel_y.w = 0;
        return 0;
    }
    return y > 0x107FFFF;
}

void main_update_screen_pos(Monster *m) {
    s32 width;
    s32 edge;
    s32 *px;
    s32 *py;
    GameObject *obj;
    s32 pos;
    s32 cam;
    u8 slot;

    width = D_801D8864.w + 1;
    edge = width - 0x1900000;
    slot = D_801FA8A0[m->id - 1];
    px = &D_801D3D98[slot];
    py = &(D_801D3D98 + 3)[slot];
    if (!(m->unk_058 & 1) || (u16) m->unk_05E != 0 || (u16) m->unk_1C8 != 0) {
        *px = 0x12C0000;
        *py = 0x12C0000;
        m->unk_1C0 = 0x12C0000;
        return;
    }
    obj = m->obj;
    D_800AA268.p = obj;
    cam = D_801F9AC8.w;
    pos = obj->pos_x.w;
    if (cam >= edge && pos < edge) {
        pos += width;
    }
    pos -= cam;
    *px = pos;
    m->unk_1C4.w = pos;
    pos = obj->pos_y.w;
    pos -= D_801F9ACC.w;
    if (m->climb_side == 0) {
        switch (m->action) {
        case 0x2C:
            if (D_801D8740 != D_801F9AD4) {
                break;
            }
        case 0x2:
        case 0x11:
        case 0x16:
        case 0x19:
        case 0x4E:
        case 0x57:
            if (pos < *py) {
                pos = *py;
            }
            break;
        }
    }
    if (pos == 0) {
        pos = 1;
    }
    *py = pos;
    m->unk_1C0 = pos;
}

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

void main_reset_screen_pos(u16 id, Monster *monster) {
    u8 *p;
    u8 *tbl;
    s32 *a;
    s32 *b;

    tbl = D_801FA8A0;
    p = tbl + (id - 1);
    if (*p != 0) {
        a = D_801D3D9C;
        b = D_801D3DA8;
        a += *p - 1;
        b += *p - 1;
        *a = 0x12C0000;
        *b = 0;
        monster->unk_1C0 = 0;
    }
}

void main_update_priority(Monster *m) {
    GameObject *obj;
    Building *b;
    u16 action;
    u16 top;
    u16 n;
    u16 prio;

    obj = m->obj;
    D_800AA268.p = obj;
    action = m->action;
    if (action == 0x1F || action == 0x57 || action == 0x37) {
        return;
    }
    if (action == 0x10) {
        if (m->climb_building != 0) {
            b = monster_get_building(m->climb_building);
            if (b != NULL) {
                n = m->unk_128 + 9;
                obj->priority = b->priority - n;
            }
        }
        return;
    }
    if ((action == 2 || action == 0x4E) && m->skip_building != 0 && obj->vel_y.w <= 0) {
        return;
    }
    if (m->climb_side == 0) {
        prio = m->unk_128 + 0x1000;
    } else {
        if (m->climb_building == 0) {
            return;
        }
        b = monster_get_building(m->climb_building);
        if (b == NULL) {
            return;
        }
        top = b->priority;
        n = m->unk_128;
        if (m->action == 9 || m->climb_side == 3) {
            n += 9;
            prio = top - n;
        } else {
            prio = n + 0x32 + top;
        }
    }
    obj->priority = prio;
}

void main_update_boxes(Monster *m) {
    GameObject *obj;
    SpriteFrame *frame;
    s16 x;
    u16 y;
    u16 ox;
    u16 oy;
    s16 d;
    s16 dy;
    s16 a;
    s16 b;

    obj = m->obj;
    if (obj->unk_6C & 0x80) {
        m->pos.s.lo = 0;
        m->pos.s.hi = 0;
        m->box2_x0 = 0;
        m->box2_x1 = 0;
        m->box_x0 = 0;
        m->box_x1 = 0;
        m->hit_left = 0;
        m->hit_top = 0;
        m->hit_right = 0;
        m->hit_bottom = 0;
        return;
    }
    x = obj->pos_x.s.hi;
    frame = obj->frame;
    ox = frame->origin.u.lo;
    oy = frame->origin.u.hi;
    if (x < D_801F9ACA) {
        x += (D_801D8864.w + 1) >> 16;
    }
    y = obj->pos_y.u.hi;
    m->pos.s.lo = 0;
    m->pos.s.hi = 0;
    m->hit_left = 0;
    m->hit_top = 0;
    m->hit_right = 0;
    m->hit_bottom = 0;
    if (FRAME_BOXES(frame)->hit[0] != FRAME_BOXES(frame)->hit[2]) {
        d = FRAME_BOXES(frame)->hit[0];
        dy = FRAME_BOXES(frame)->hit[1];
        if (obj->flags & 0x10) {
            d = -d;
        }
        m->hit_left = d + x;
        m->hit_top = dy + y;
        d = FRAME_BOXES(frame)->hit[2];
        dy = FRAME_BOXES(frame)->hit[3];
        if (obj->flags & 0x10) {
            d = -d;
        }
        m->hit_right = d + x;
        m->hit_bottom = dy + y;
        if (obj->flags & 0x10) {
            d = m->hit_left;
            m->hit_left = m->hit_right;
            m->hit_right = d;
        }
    }
    if (FRAME_BOXES(frame)->point[0] != 0) {
        d = FRAME_BOXES(frame)->point[0] - ox;
        dy = FRAME_BOXES(frame)->point[1] - oy;
        if (obj->flags & 0x10) {
            d = -d;
        }
        m->pos.s.lo = d + x;
        m->pos.s.hi = dy + y;
    }
    if (m->unk_0DC == 0) {
        m->box2_x0 = 0;
        m->box2_x1 = 0;
        m->box_x0 = 0;
        m->box_x1 = 0;
        return;
    }
    if (m->action == 0x37) {
        m->box_x0 = x - 10;
        m->box_x1 = x + 10;
        m->box_y0 = y - 10;
        m->box_y1 = y;
        m->box2_x0 = 0;
        m->box2_x1 = 0;
        m->box2_y0 = 0;
        m->box2_y1 = 0;
        return;
    }
    d = FRAME_BOXES(frame)->box2[0];
    dy = FRAME_BOXES(frame)->box2[1];
    if (obj->flags & 0x10) {
        d = -d;
    }
    a = d + x;
    m->box2_x0 = a;
    m->box2_y0 = dy + y;
    d = FRAME_BOXES(frame)->box2[2];
    dy = FRAME_BOXES(frame)->box2[3];
    if (obj->flags & 0x10) {
        d = -d;
    }
    b = d + x;
    m->box2_x1 = b;
    m->box2_y1 = dy + y;
    if (obj->flags & 0x10) {
        m->box2_x1 = a;
        m->box2_x0 = b;
    }
    d = FRAME_BOXES(frame)->box[0];
    dy = FRAME_BOXES(frame)->box[1];
    if (obj->flags & 0x10) {
        d = -d;
    }
    a = d + x;
    m->box_x0 = a;
    m->box_y0 = dy + y;
    d = FRAME_BOXES(frame)->box[2];
    dy = FRAME_BOXES(frame)->box[3];
    if (obj->flags & 0x10) {
        d = -d;
    }
    b = d + x;
    m->box_x1 = b;
    m->box_y1 = dy + y;
    if (obj->flags & 0x10) {
        m->box_x1 = a;
        m->box_x0 = b;
    }
}

void func_80027FC8(void) {
}

void func_80027FD0(Monster *m) {
    u32 dir;
    void (**table)(Monster *);

    dir = 0;
    if (m->health.w != 0 && m->action != 0x60) {
        dir = m->buttons;
    }
    dir &= 0xF;
    if (dir >= 9) {
        dir = 0;
    }
    table = D_8007C170;
    if (m->action == 0x4D) {
        table = D_8007C14C;
    } else if (m->action == 2 || m->action == 0x4E || m->unk_05C == 2 || m->unk_05C == 0x4E) {
        table = D_8007C194;
    }
    table = &table[dir];
    (*table)(m);
}

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
    monster->unk_0D0 = pressed;
    monster->unk_18C = count;
    if (buttons & 4) {
        if (monster->unk_1AA == 0) {
            monster->unk_1AA = 1;
        }
    } else {
        monster->unk_1AA = 0;
    }
}

void func_80028140(u16 arg0, Monster *arg1, u16 arg2) {
    if (arg0 != arg2) {
        arg1->unk_0CE = arg2;
        return;
    }
    arg1->unk_0CE = 0;
}

void main_reset_camera_y(void) {
    D_801D3D64.unk_26 = 0;
    D_801F9A30.unk_0 = 0;
    D_801D3D64.unk_28 = 0;
    D_801F9ACC.w = 0;
}

#ifdef NON_MATCHING
/* 98.40%: 98.4 %: flags and the D_801D3D64 pointer swap s0/s1; d = vel2 loads vel2 straight into d where the
 * original loads it into v0 and copies it */
extern u16 D_801D3700;
extern s32 D_8007BD7C;
extern s32 D_801D3D90;
extern s16 D_801FA724;
extern s16 D_801FA728;
extern s16 D_801FA9A8;
void func_80028B1C(void);
void func_800288B0(s32 *vel2, s32 *vel1);
void func_80029D5C(s32, s32);

void func_80028184(void) {
    s32 flags;
    s32 vel2;
    s32 vel1;
    s32 speed;
    s32 x;
    s32 d;
    s32 cam;
    Unk1D3D64 *scroll;

    flags = func_8005E4E4();
    if (flags == 1 || D_801D8740 == 0 || D_801D3700 != 0 || D_801E1CB0 != 0
        || (scroll = &D_801D3D64)->unk_24 != 0) {
        main_reset_camera_y();
        return;
    }
    if (flags & 2) {
        func_80029D5C(flags, D_8007BD7C);
        return;
    }
    func_80028B1C();
    func_800288B0(&vel2, &vel1);
    x = D_801FA9A8;
    speed = scroll->unk_26 << 16;
    if (speed != 0) {
        if (speed > 0) {
            d = vel2;
            if (vel1 >= d) {
                d = vel1;
            }
            if (x >= 0xD3) {
                d += 0x10000;
                if (d < speed) {
                    d = speed;
                }
            } else if (x >= 0xBF) {
                goto clamp_right;
            } else {
                goto stop;
            }
        } else {
            d = vel2;
            if (vel1 <= d) {
                d = vel1;
            }
            if (x < 0xBE) {
                d -= 0x10000;
                if (d > speed) {
                    d = speed;
                }
            } else if (x < 0xD3) {
                goto clamp_left;
            } else {
                goto stop;
            }
        }
    } else {
        if (D_801D8740 < 2) {
            if (x > 0x12C) {
                goto right;
            }
            if (x < 0x64) {
                goto left;
            }
            goto stop;
        }
        if (x > 0xF0) {
            if (vel2 >= 0) {
                x = D_801FA724;
                if (x >= 0x12C) {
                    goto right;
                }
            }
            if (vel1 < 0) {
                goto stop;
            }
            x = D_801FA728;
            if (x < 0x12C) {
                goto stop;
            }
        right:
            d = vel2;
            if (vel1 >= d) {
                d = vel1;
            }
            D_801D3D90 = d;
            if (x > 0x12C) {
                d += 0x10000;
            } else if (x < 0xDD) {
                d = 0x10000;
            } else {
            clamp_right:
                if (d < 0x10000) {
                    d = 0x10000;
                }
            }
        } else if (x < 0xA0) {
            if (vel2 <= 0) {
                x = D_801FA724;
                if (x < 0x65) {
                    goto left;
                }
            }
            if (vel1 > 0) {
                goto stop;
            }
            x = D_801FA728;
            if (x >= 0x65) {
                goto stop;
            }
        left:
            d = vel2;
            if (vel1 <= d) {
                d = vel1;
            }
            D_801D3D90 = d;
            if (x < 0x64) {
                d -= 0x10000;
            } else if (x >= 0xB4) {
                d = -0x10000;
            } else {
            clamp_left:
                if (d > -0x10000) {
                    d = -0x10000;
                }
            }
        } else {
        stop:
            scroll->unk_26 = 0;
            scroll->unk_2C = 0;
            goto done;
        }
    }
    if (!(flags & 4)) {
        cam = D_801F9AC8.w;
        if (d < 0) {
            d = -d & 0xFFFF0000;
            d = -d;
        } else {
            d &= 0xFFFF0000;
        }
        cam += d;
        D_801D3D8A = d >> 16;
        D_801F9AC8.w = cam & D_801D8864.w;
    }
done:
    main_update_camera_y();
}
#else
INCLUDE_ASM("asm/main/nonmatchings/main", func_80028184);
#endif

void main_start_scroll_down(void) {
    s32 var_v1;

    var_v1 = 0x20000;
    if (D_801D8720 == 0) {
        var_v1 = 0x80000;
    }
    D_801F9A30.unk_0 = var_v1;
    D_801D3D8C = 2;
}

void main_start_scroll_up(void) {
    D_801F9A30.unk_0 = 0xFFFE0000;
    D_801D3D8C = 1;
}

extern u16 D_801D3700;
extern s16 D_801D3DBE;

void main_update_camera_y(void) {
    s32 *p;
    s32 y;
    s32 max;                /* the lowest player's y; the camera's y below, as in the original */
    s32 min;                /* the highest player's y */
    u16 maxi;
    u16 mini;
    Monster *mon;
    GameObject *obj;

    max = -1;
    maxi = 1;
    mini = 1;
    min = 0x77770000;
    p = D_801D3DA8;
    y = *p++;
    if (y != 0) {
        max = y;
        min = max;
    }
    y = *p++;
    if (y != 0) {
        if (y >= max) {
            maxi = 2;
            max = y;
        }
        if (y <= min) {
            mini = 2;
            min = y;
        }
    }
    y = *p;
    if (y != 0) {
        if (y >= max) {
            maxi = 3;
            max = y;
        }
        if (y <= min) {
            mini = 3;
            min = y;
        }
    }
    D_801D3D64.unk_30 = max;
    D_801D3D64.unk_34 = min;
    if (D_801D3D64.unk_28 == 0) {
        if (D_801E28C8 != 0) {
        high:
            if (min > 0x87FFFF && max > 0xEFFFFF) {
                mon = &D_801E0B78[func_80025DF8(maxi)];
                obj = mon->obj;
                if (obj->vel_y.w > 0) {
                    goto rise;
                }
            }
            if (min > 0xA7FFFF && max <= 0xDFFFFF) {
                return;
            }
            goto rise;
        } else if (D_801E1CB0 != 0 || D_801D3700 != 0
                   || ((Fixed *) &D_801D3D64.unk_58)->u.hi != 0) {   /* D_801D3DBE, read through the block */
            max = D_801F9ACC.w;
            if (max == 0) {
                return;
            }
            D_801D3DBE = 1;
        rise:
            main_start_scroll_down();
        } else {
            if (max <= 0xF00000 && min <= 0x700000) {
                mon = &D_801E0B78[func_80025DF8(mini)];
                obj = mon->obj;
                if (obj->vel_y.w < 0) {
                    goto sink;
                }
            }
            if (max > 0xB80000 || min > 0x800000) {
                goto high;
            }
        sink:
            main_start_scroll_up();
        }
    } else if (D_801D3D64.unk_28 == 1) {
        if (min <= 0x77FFFF && max <= 0xEFFFFF) {
            max = D_801F9ACC.w + D_801F9A30.unk_0;
            D_801F9ACC.w = max;
            if (max > -0x14C0000) {
                return;
            }
            max = -0x14C0000;
            D_801F9ACC.w = max;
        }
        goto stop;
    } else if (D_801D3D64.unk_28 == 2) {
        if (((Fixed *) &D_801D3D64.unk_58)->u.hi == 0 && (max <= 0xC00000 || min <= 0x800000)) {
            goto stop;
        }
        max = D_801F9ACC.w + D_801F9A30.unk_0;
        D_801F9ACC.w = max;
        if (max > 0) {
            goto zero;
        }
        if (max <= 0xFFE7FFF) {     /* always, max being <= 0 here: the original's constant */
            return;
        }
        mon = &D_801E0B78[func_80025DF8(mini)];
        obj = mon->obj;
        if (obj->pos_x.s.hi >= 0x71) {
            return;
        }
        goto zero;
    stop:
        if (D_801F9ACC.w >= 0) {
        zero:
            D_801F9ACC.w = 0;
        }
        D_801F9A30.unk_0 = 0;
        D_801D3D8C = 0;
    }
}

#ifdef NON_MATCHING
/* 96.69%: 96.7 %: each case's load of m1->obj sits before the second call's li a0 (the original has li a0 first, so
 * its three tails cross-jump from the load); then x1/x2 get a3/a2 instead of t1/t0 */
extern s16 D_801D8844;
extern s16 D_801FA724;
extern s16 D_801FA728;
extern s16 D_801FA9A8;
s16 func_80028ADC(s32, s32);

void func_800288B0(s32 *vel2, s32 *vel1) {
    Monster *m1;
    Monster *m2;
    GameObject *o1;
    GameObject *o2;
    s32 left;
    s32 width;
    u16 x1;
    u16 x2;
    s32 result;
    u16 cam;

    switch (D_801D8844) {
    case 1:
        m1 = &D_801E0B78[func_80025DF8(1)];
        o1 = m1->obj;
        m2 = &D_801E0B78[func_80025DF8(2)];
        break;
    case 2:
        m1 = &D_801E0B78[func_80025DF8(1)];
        o1 = m1->obj;
        m2 = &D_801E0B78[func_80025DF8(3)];
        break;
    default:
        m1 = &D_801E0B78[func_80025DF8(2)];
        o1 = m1->obj;
        m2 = &D_801E0B78[func_80025DF8(3)];
        break;
    }
    o2 = m2->obj;
    if (o2 == NULL) {
        o2 = o1;
    }
    if (o1 == NULL) {
        o1 = o2;
    }
    x1 = o1->pos_x.s.hi;
    x2 = o2->pos_x.s.hi;
    width = (s16) D_801D8866 + 1;
    cam = D_801F9ACA;
    left = (s16) D_801D8866 - 399;
    if (D_801F9ACA >= left) {
        if ((s16) x1 <= left) {
            x1 += width;
        }
        if ((s16) x2 <= left) {
            x2 += width;
        }
    }
    x1 -= cam;
    x2 -= cam;
    if (m1->action == 0x37 || m1->action == 0x26 || (u16) m1->unk_1C8 != 0 || m1->id == 0) {
        result = (s16) x2;
        *vel2 = o2->vel_x.w;
        *vel1 = 0;
    } else {
        *vel1 = o1->vel_x.w;
        if ((u16) m2->unk_1C8 != 0 || m2->action == 0x37 || m2->action == 0x26 || m2->id == 0) {
            *vel2 = 0;
            result = (s16) x1;
        } else {
            *vel2 = o2->vel_x.w;
            D_801FA724 = x2;
            D_801FA728 = x1;
            result = func_80028ADC((s16) x2, (s16) x1);
        }
    }
    D_801FA9A8 = result;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/main", func_800288B0);
#endif

/* 91.3 %: the result is computed from a copy of the larger value (move v0,a2) in the original; the C computes it in place */
#ifdef NON_MATCHING
s16 func_80028ADC(s32 a, s32 b) {
    s16 lo;
    s16 hi;

    lo = a;
    hi = b;
    if ((s16) b <= (s16) a) {
        lo = b;
        hi = a;
    }
    return hi - ((s16) (hi - lo) >> 1);
}
#else
INCLUDE_ASM("asm/main/nonmatchings/main", func_80028ADC);
#endif

INCLUDE_ASM("asm/main/nonmatchings/main", func_80028B1C);

void func_80029118(s16 arg0, u16 arg1) {
    if (D_801D3D64.unk_5E < arg0) {
        if (D_801D3D64.unk_5C & 1) {
            D_801F9ACC.w -= D_801D3D64.unk_5E << 16;
        }
        D_801D3D64.unk_5E = arg0;
        D_801D3D64.unk_5C = arg1;
    }
}

void func_80029170(void) {
    if (D_801D3D64.unk_5C != 0) {
        if (D_801D3D64.unk_5C & 1) {
            D_801F9ACC.w -= D_801D3D64.unk_5E << 16;
        } else {
            D_801F9ACC.w += D_801D3D64.unk_5E << 16;
        }
        D_801D3D64.unk_5C--;
        return;
    }
    D_801D3D64.unk_5E = 0;
}

#ifdef NON_MATCHING
/* 95.49%: 95.5 %: the original keeps 0x37 from the first compare in a2 and stores it (m->action = 0x37), the C
 * loads it again (one instruction more); action - 9 is computed before the 0x34 test, the original after it */
s32 func_800291DC(Monster *m, GameObject *obj) {
    u16 action;
    u16 next;
    u16 i;
    Monster *other;
    u16 id;

    if (!(m->unk_058 & 1) || m->unk_046 != 0) {
        return 0;
    }
    if (m->action == 0x37 || m->action == 0x26) {
        if (m->lives == 0) {
            if ((u16) m->unk_05E == 0) {
                return 0;
            }
            func_8005D1BC((s32) m, m->id);
            m->unk_058 &= ~1;
            D_801FA8A0[m->id - 1] = 0;
            m->id = 0;
            D_8007A7D4 |= 1;
            building_clear_monster(m);
            m->unk_046 = 1;
            D_8007A7D4 &= ~1;
            if (m->obj != NULL) {
                func_8001E4B0(m->obj);
                m->obj = NULL;
            }
            main_free_kind((u16) (m->id + 0x790));
            m->unk_178 = 0;
            cdload_sort_players();
            return 1;
        }
    } else if (m->action == 0x60) {
        m->health.w = 0;
        return 0;
    } else {
        if (m->health.w > 0xFFFF) {
            return 0;
        }
        if (m->action == 0x63 || m->action == 0x2A || m->action == 0x47) {
            return 0;
        }
        m->health.w = 0;
        if (m->lives == 0) {
            if (m->unk_18E == 0) {
                if (m->climb_side != 0) {
                    m->action = 0xF;
                } else if (obj->pos_y.u.hi < 0xE1 || obj->pos_y.u.hi >= 0xF9) {
                    m->action = 0xF;
                    func_8001F724(0x72);
                } else {
                    next = m->action;
                    action = next - 9;
                    if (next == 0x34 || next == 0x35) {
                        m->action = 0x26;
                    } else if (action < 6) {
                        return 0;
                    } else {
                        m->action = 0x37;
                    }
                    m->unk_0DC = 0;
                    m->unk_0E4 = 0;
                    m->unk_0E6 = 0;
                    func_8001F724(0x72);
                    if (D_801F9ACC.w != 0) {
                        id = m->id;
                        i = 7;
                        do {
                            if (id != i) {
                                other = &D_801E0B78[i];
                                if ((other->unk_058 & 1) && other->climb_side != 0) {
                                    other->action = 0xF;
                                }
                            }
                        } while (--i != 0);
                    }
                }
            } else {
                m->health.w = 0x50000;
            }
            return 0;
        }
    }
    m->health.w = 0x440000;
    m->unk_018 = 1;
    m->unk_14C = 0;
    m->unk_040 = 0;
    m->lives--;
    func_8001F724(0x14);
    func_8001F724(0x72);
    action = m->action;
    if (action == 0x26) {
        next = 0x34;
    } else if (action == 0x37) {
        next = 0xE;
    } else if (m->climb_side != 0 || obj->pos_y.s.hi < 0xE1 || obj->pos_y.s.hi >= 0xF9) {
        next = 0xF;
    } else if (action >= 0x34 && action <= 0x35) {
        return 0;
    } else {
        next = 0xA;
    }
    m->action = next;
    return 0;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/main", func_800291DC);
#endif

void main_apply_health(Monster *arg0) {
    s32 old;
    s32 value;
    s32 delta;

    value = arg0->health.w;
    old = value;
    if (arg0->unk_0F0 != 0) {
        delta = arg0->unk_0F0;
    } else if (arg0->unk_064 != 0) {
        delta = 0;
    } else {
        goto done;
    }
    value += delta;
    if (value >= 0) {
        if (value > 0x440000) {
            value = 0x440000;
        }
        arg0->unk_0F0 = 0;
        arg0->health.w = value;
    } else {
        value = 0;
        arg0->unk_0F0 = 0;
        arg0->health.w = 0;
    }
done:
    bonus_update_bars(old, arg0, value);
}

void main_count_monsters(void) {
    Monster *m;
    s32 i;
    u16 result;

    D_800AA248.unk_0C = 0;
    D_800AA248.unk_10 = 0;
    D_800AA248.action = 0;
    D_800AA248.unk_1C.n = 0;
    D_800AA248.dir = 0;
    D_800AA248.unk_08 = 7;
    do {
        m = &D_801E0B78[D_800AA248.unk_08];
        if (m->unk_058 & 1) {
            if (m->action == 0x37 || m->action == 0x26) {
                if (m->unk_01C != 0) {
                    D_800AA248.unk_10++;
                    continue;
                }
                D_800AA248.dir++;
            }
            D_800AA248.unk_0C++;
            if (m->unk_01C != 0 || m->action == 0x1F) {
                D_800AA248.unk_10++;
            } else if (m->action == 0) {
                D_800AA248.action++;
            } else if (m->action == 0x2C) {
                D_800AA248.unk_1C.n++;
            }
        }
    } while (--D_800AA248.unk_08 != 0);
    i = 0;
    D_801D8740 = D_800AA248.unk_0C;
    result = 0;
    D_801E1CB0 = D_800AA248.unk_10;
    D_801E1E44 = D_800AA248.action;
    D_801F9AD4 = D_800AA248.unk_1C.n;
    D_801E29C4 = D_800AA248.dir;
    while (i < D_801D8740) {
        m = &D_801E0B78[func_80025DF8(D_801FB49C[i])];
        if (m->lives != 0 || m->health.s.hi != 0) {
            result = D_801D8740;
            break;
        }
        i++;
    }
    D_801D8740 = result;
}

void func_800297B4(void) {
    Monster *monster;

    D_800AA248.unk_0C = 0;
    D_800AA248.unk_10 = 0;
    D_800AA248.unk_08 = 7;
    do {
        monster = &D_801E0B78[D_800AA248.unk_08];
        if (monster->unk_058 & 1) {
            if (monster->climb_side != 0) {
                D_800AA248.unk_10++;
            }
            if (monster->unk_1DE != 0) {
                D_800AA248.unk_0C++;
            }
        }
    } while (--D_800AA248.unk_08 != 0);
    D_801E28C8 = D_800AA248.unk_0C;
    D_801D8720 = D_800AA248.unk_10;
}

void func_8002987C(Monster *monster) {
    u16 action;
    s16 found;
    u16 *p;

    if ((D_800AA2DC != 0) && (D_8007BD78.flags & 0x100)) {
        monster->unk_0DC = 0;
        return;
    }
    action = monster->action;
    if ((action == 0x37) || (action == 0x26)) {
        return;
    }
    found = 0;
    if ((monster->unk_126 != 0x19) && !(monster->obj->unk_6C & 0x80) && (monster->icon_timers[0] == 0)) {
        for (p = D_8007C1D4; *p != 0xFFFF; p++) {
            if (*p == action) {
                found = 1;
                break;
            }
        }
    }
    monster->unk_0DC = found;
}

void func_8002994C(void) {
    if (D_801FB18C == 1) {
        D_801FB18C = func_8005E5C8();
    }
}

void func_80029984(Monster *m) {
    u16 *p;

    for (p = &m->unk_130; p <= &m->unk_14A; p++) {
        if (*p != 0) {
            (*p)--;
        }
    }
}

void func_800299C4(void) {
    GameObject *sprite;
    ObjectDef *request;
    s32 count;

    sprite = D_801E2894.unk_0;
    if ((D_801E1E40 == 0) || (D_801FA890 > 0) || (D_801FA734 != 0) || (D_801D3D8A != 0) || (D_801F9ACC.w != 0)) {
        if (sprite != NULL) {
            D_801E2894.unk_4 = 0;
            sprite->pos_y.s.hi = 0x190;
            D_801E2894.unk_6 = 0;
        }
    } else {
        count = D_801E2894.unk_4 + 1;
        if (count >= 0xB4) {
            if (sprite == NULL) {
                request = func_8001D110();
                D_800AA284.p = request;
                request->flags = 0x7000;
                request->anim = &D_80093F78;
                request->pos_x.s.hi = 0x150;
                request->id = 0x4F0000A2;
                request->pos_y.s.hi = 0x190;
                request->unk_06 |= 0x20;
                sprite = func_8001DCB4();
                D_801E2894.unk_0 = sprite;
                sprite->owner.p = &D_801E2894;
                D_801E2894.unk_6 = 1;
                return;
            }
            D_801E2894.unk_6 = 1;
            sprite->pos_y.s.hi = 0x7C;
            if (func_80029B80()) {
                sprite->pos_x.s.hi = 0x30;
                func_8003EB5C(&D_80093FAC, sprite);
            } else {
                sprite->pos_x.s.hi = 0x150;
                func_8003EB5C(&D_80093F78, sprite);
            }
            return;
        }
        D_801E2894.unk_4 = count;
        if (sprite != NULL) {
            sprite->pos_y.s.hi = 0x190;
            D_801E2894.unk_6 = 0;
        }
    }
}

void func_80029B54(void) {
    memset(&D_801E2894, 0, 8);
}

u16 func_80029B80(void) {
    u16 count;
    u16 result;
    s16 best;
    s16 dist;
    s32 d;
    s16 cx;
    Building *building;

    count = D_801E29A4;
    result = 0;
    best = 0x270F;
    cx = (D_801F9ACA + 0xC8) & D_801D8866;
    if (count != 0) {
        building = D_801D3DC8;
        do {
            if (building->state < 9) {
                dist = func_8003FCD8(((s16) building->left + building->right) >> 1, cx);
                d = dist >= 0 ? dist : -dist;
                if (d <= best) {
                    best = d;
                    result = dist < 1;
                }
            }
            building++;
        } while (--count != 0);
    }
    return result;
}

void func_80029C6C(Monster *arg0) {
    GameObject *sprite;
    u16 state;

    sprite = D_800AA268.p = arg0->obj;
    if (sprite != NULL) {
        state = arg0->action;
        if (((state != 2) && (state != 0x4E)) || (arg0->skip_building == 0) || (sprite->vel_y.w > 0)) {
            if (arg0->unk_12C != sprite->priority) {
                func_8001E39C(sprite);
                func_8001E2F8(sprite);
            }
        }
    }
}

void func_80029CF8(void) {
    D_800AA268.p->flags = (u16) ((D_800AA268.p->flags & 0xFF90) | 2);
}

void func_80029D1C(void) {
    u32 flags;

    if (D_800AA268.p != NULL) {
        flags = D_800AA268.p->flags;
        flags &= 0xFFF0;
        flags |= 2;
        if (flags & 0x40) {
            flags &= 0xFF72;
        }
        D_800AA268.p->flags = flags;
    }
}

#ifdef NON_MATCHING
/* 91.81%: 91.8 %: a first draft, the logic complete; registers differ from the start (the original keeps mode in s5
 * and sx in s6), the screen x is computed into a2 and copied to sx, and the dy, dx sums still reassociate */
extern s32 D_8007BD7C;
void func_8005E214(void);

void func_80029D5C(s32 mode, s32 player) {
    Monster *m;
    s32 bonus;
    s32 boost;
    u16 camx;
    u16 camy;
    u16 sx;
    u16 ox;
    u16 oy;
    u16 right;
    u16 edge;
    u16 dx;
    u16 dy;
    u16 x;
    s32 flags;

    sx = 0;
    boost = 0;
    m = NULL;
    dx = 0;
    dy = 0;
    bonus = 0;
    if (D_800AA2DC != 0) {
        bonus = bonus_get_round_kind();
    }
    camx = D_801F9ACA;
    camy = D_801F9ACE;
    if (mode == 2) {
        if (D_8007BD7C <= 0) {
            return;
        }
        m = &D_801E0B78[func_80025DF8(player)];
        right = camx + 0x131;
        edge = right;
        ox = m->obj->pos_x.u.hi;
        oy = m->obj->pos_y.u.hi;
        if ((s16) D_801D8866 < (s16) right) {
            edge = right - D_801D8866;
        }
        x = ox;
        if ((s16) camx < (s16) ox && (s16) ox < (s16) edge) {
            x = ox - camx;
        }
        sx = x;
        if (m->action == 2 || m->action == 0x19) {
            boost = 2;
        } else {
            boost = 0;
        }
        if ((s16) x >= 0x132) {
            dx = m->obj->vel_x.u.hi + boost;
            if ((s16) x - 0x131 < (s16) dx) {
                dx = x - 0x131;
            }
            D_8007BD78.flags |= 2;
        } else if ((s16) x < 0x5A) {
            dx = m->obj->vel_x.u.hi - boost;
            if ((s16) dx < (s16) x - 0x5A) {
                dx = x - 0x5A;
            }
        }
        flags = D_8007BD78.flags;
        if (flags & 0x200) {
            if (D_801F9AC8.s.hi <= 0 || (D_801F9AC8.s.hi = D_801F9AC8.u.hi - 5) <= 0) {
                D_801F9AC8.s.hi = 0;
                D_8007BD78.flags = flags & ~0x200;
                func_8005E214();
            }
        }
        oy -= 0xE1;
        if (((s16) camy - (s16) oy >= 0x6F || (D_8007BD78.flags & 4)) && m->action != 2 && m->action != 0x2C) {
            dy = camy - 0x6E;
            dy = oy - dy;
            D_8007BD78.flags |= 4;
            if ((s16) dy < -4) {
                dy = -4;
            } else if ((s16) dy == 0) {
                D_8007BD78.flags &= ~4;
            }
        } else if ((s16) oy - ((s16) camy - 0x32) > 0) {
            dy = camy - 0x32;
            dy = oy - dy;
            if ((s16) dy >= 5) {
                dy = 4;
            }
            if (-(s16) camy < (s16) dy) {
                dy = -camy;
            }
        }
    }
    if (D_8007BD78.flags & 3) {
        if ((s16) sx < 0xAB) {
            dx -= 5;
            dx -= boost;
        } else if ((s16) sx >= 0xBE) {
            dx += 5;
            dx = boost + dx;
        } else {
            dx = m->obj->vel_x.s.hi;
            if (dx == 0) {
                D_8007BD78.flags &= ~3;
            }
        }
    }
    if (bonus == 1 && (s16) dx < 0) {
        dx = 0;
    }
    x = D_801F9AC8.u.hi + dx;
    D_801F9AC8.u.hi = x;
    D_801F9ACC.u.hi += dy;
    if ((s16) D_801D8866 < (s16) x) {
        D_801F9AC8.s.hi = x - D_801D8866;
    } else if ((s16) x < 0) {
        D_801F9AC8.s.hi = x + D_801D8866;
    }
    if (D_801F9ACC.s.hi > 0) {
        D_801F9ACC.s.hi = 0;
    }
    if (D_801F9AC8.s.hi >= 0x667) {
        D_801F9AC8.s.hi = 0x666;
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/main", func_80029D5C);
#endif

void func_8002A1AC(Monster *m, s16 count) {
    GameObject *saved;
    ObjectDef *def;
    s32 i;
    s32 player;

    saved = D_800AA248.cur_obj;
    if (m->extra[2] == NULL && (D_800AA2DC == 0 || (D_800AA2DC & 0x7000))) {
        player = D_801FA8A0[m->id - 1];
        def = D_800AA248.new_def = func_8001D110();
        for (i = 0; i < count; i++) {
            def->id = 0x4F0035B6;
            def->pos_x.s.hi = (player - 2) * 0x78 + 0x9B + i * 0xF;
            def->pos_y.s.hi = 0x3F;
            def->flags = 0x500;
            def->unk_06 |= 0x20;
            D_800AA248.cur_obj = func_8001DCB4();
            D_800AA248.cur_obj->kind = m->id + 0x790;
            m->extra[i + 2] = D_800AA248.cur_obj;
        }
        D_800AA268.p = saved;
    }
}

s32 func_8002A300(void) {
    return 1;
}

u16 func_8002A308(void) {
    func_8001CFE4();
    return D_801D87A0;
}
