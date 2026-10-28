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
void main_update_attract(void);
extern s16 D_801CA464;
extern s16 D_801D87C8;
void func_80017758(void);
extern u16 D_800AA2C8;
void main_update_pressed(void);
u16 main_update_pause(void);
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
void main_init_system(void);
void main_begin_frame(void);
void func_80019890(void);
void func_80019984(s32);
void func_8001A1C8(void);
void func_8001A474(void);
SpriteFrame *func_8001A554(s32, GameObject *);
void func_8001B350();
void func_8001B694(void);
void func_8001BA98(void);
void main_init_level(void);
void func_8001D184(void);
void func_8001D7D0(void);
s32 main_cull_objects(GameObject *);
void main_sort_objects(void);
void main_init_objects(void);
void main_free_kind(s32);
void func_8001E4B0(GameObject *);
void func_8001E664(Fixed *, s32, Fixed *, s32 *);
s32 func_8001B660(s32);
void func_8001E700(GameObject *);
void func_8001E7C8(GameObject *);
s16 main_random(void);
s32 main_random_range(s32);
void func_8001F2B0(void);
void func_8001F358(void);
void func_8001F39C(TextMessage *);
void func_8001F6B4(void);
void func_8001F7F8(s32);
void main_draw_lists(void);
void main_draw_objects(GameObject *head, GameObject *end);
void main_run_calls(void);
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
void main_update_monsters(void);
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
void main_free_pause_box(void);
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
void main_seed_random(s16 arg0, s16 arg1);
s32 func_8001EA78(void);
s32 main_random_between(s32 arg0, s32 arg1);
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
s32 main_read_pad(u8 *, u16, s16, s16);
u16 main_approach_xy(Npc *);
void main_unwrap_target_x(s16 *, s16 *, Npc *);
extern u16 D_801FA898[];
void func_80019268(void);
extern s16 D_801D36F8;
extern s16 D_801F9A34;
u16 main_can_pause(u16 id);
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
extern MainDemo D_8007AB60;
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
void main_create_building_items(Building *);
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
void main_update_input(Monster *, s32);
void func_80027394(void);
extern s32 D_801C51D0;
s32 func_8001A0A0(void);
extern u8 D_8007AB70[];
extern u16 D_8007AB84[];
void func_8001D6A0(void);
extern s32 D_801E299C;
extern s32 D_801FA974;
Glyph *func_8001B128(u32);
void main_print_text(void);
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
            if (main_update_pause() == 1) {
                goto restart;
            }
            func_8001B7F4();
            if (D_801D3D64.pause_state == 0) {
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
    main_seed_random(GetRCnt(0xF2000001), GetRCnt(0xF2000001));
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
    if (D_801D3D64.pause_state == 0) {
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

u16 main_can_pause(u16 id) {
    u16 temp_v1;
    Monster *temp_a1;

    temp_a1 = &D_801E0B78[id];
    if ((D_801D36F8 != 0) || (D_801FA890 != 0) || (D_801F9A34 > 0) || (temp_a1->id == 0) || (temp_v1 = temp_a1->action, (temp_v1 == 0x1F)) || (temp_v1 == 0x37) || (temp_v1 == 0x26) || (temp_a1->unk_046 != 0) || ((D_801D36FC != 0x240) && (D_801D36FC != 0x150) && (D_801D36FC != 0x220)) || ((D_801E1E40 == 0) && (D_801D36FC == 0x150)) || ((D_801D3758 < 5) && (D_801D36FC == 0x220))) {
        return 0;
    }
    return 1;
}

u16 main_find_unplugged_pad(void) {
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
                if (who == player + 1 && main_can_pause(id + 1) == 1) {
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

void main_create_pause_box(s16 x, s16 y, GameObject *link, s32 script) {
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
        D_800AA248.cur_obj->colour.w = 0;
        D_800AA248.cur_obj->flags |= 0x40C;
        D_8007A698 = 1;
        D_800AA248.cur_obj->unk_6C |= 0x20;
        D_800AA248.cur_obj->kind = 0x7FE;
    }
    D_800AA248.cur_obj = saved;
}

void main_free_pause_box(void) {
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
                sprite->colour.w = 0x808080;
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

/* The pause menu's keys per player: its pad's buttons in D_801E0D7C (each player's bits shifted by D_8007C144). */
typedef struct {
    /* 0x00 */ u32 pause;     /* START */
    /* 0x04 */ u32 confirm;
    /* 0x08 */ u32 move;      /* up and down */
    /* 0x0C */ u16 owner;     /* player << 12, as D_801D3D64.pause_state holds the pausing player */
    /* 0x0E */ u16 pad_0E;
} MainPauseKeys;

extern MainPauseKeys main_pause_keys[3];
extern s32 main_pause_cursor;   /* the menu's cursor: 0 the first line, 1 the second */
extern s32 main_pause_delay;   /* frames before the menu reads the pad again */
extern s32 D_800AA2C4;   /* the printed message's %d */
extern TextMessage D_80089374;
extern TextMessage D_80089398;
extern TextMessage D_800893BC;
extern TextMessage D_800893E0;
extern TextMessage D_80089400;
extern TextMessage D_8008941C;
extern TextMessage D_80089438;
extern TextMessage D_80089460;
extern TextMessage D_8008948C;
extern TextMessage D_800894B4;
extern TextMessage D_800894D8;
extern TextMessage D_8008950C;
extern TextMessage D_80089534;
extern TextMessage D_80089560;
void func_80060A7C(s32, u32, s32);
void func_80062E64(void);
void func_80062E88(void);
void func_800636B0(void);

/* The pause handler, once per frame: an unplugged pad pauses the game with a message until it is back; START pauses;
 * the menu is CONTINUE/QUIT, then ABORT GAME YES/NO. Returns 1 when the player quits to the menu. The pause block
 * is shared with the replugged pad's path through the label, as the original's code is. */
u16 main_update_pause(void) {
    s16 who;    /* the player whose pad was unplugged (0xFF: no pad at all), then each monster's player */
    u16 flags;  /* D_801D3D64.pause_state: bits 0-1 the menu state, 8-11 the unplugged pad's player, 12-13 the pausing player */
    s16 player;
    s16 i;      /* also the pausing player in the menu states */
    OverattrPlayer *p;

    if (main_pause_delay != 0) {
        main_pause_delay--;
    }
    who = main_find_unplugged_pad();
    if ((who != 0 && (D_801D36FC == 0x150 || D_801D36FC == 0x240 || D_801D36FC == 0x220)) || (D_801D3D64.pause_state & 0xF00)) {
        if (!(D_801D3D64.pause_state & 0xF00)) {
            main_cycle_highlight();
            if (D_801D3D64.pause_state & 3) {
                main_free_kind(0x300);
                main_free_kind(0x301);
                main_free_kind(0x302);
                main_free_kind(0x303);
                main_free_kind(0x304);
                main_free_kind(0x305);
            }
            func_8001F6E4();
            func_80062E64();
            main_create_pause_box(0x50, 0x3C, (GameObject *)0xF0, 0x5A);
            D_800AA2EC = 0x44;
            if (who == 0xFF) {
                func_8001ED54(&D_80089438);
                func_8001ED54(&D_80089460);
                func_8001ED54(&D_8008948C);
                func_8001ED54(&D_800894B4);
                who = 1;
            } else {
                D_800AA2C4 = who;
                func_8001ED54(&D_800894D8);
                func_8001ED54(&D_8008950C);
                func_8001ED54(&D_80089534);
                func_8001ED54(&D_80089560);
            }
            D_801D3D64.pause_state |= who << 8;
        } else {
            player = (D_801D3D64.pause_state & 0xF00) >> 8;
            if (D_801FA898[player - 1] == D_801E1C90[player - 1]) {
                main_free_kind(0x300);
                main_free_kind(0x550);
                D_801D3D64.pause_state &= 0xF0FF;
                main_cycle_highlight();
                switch (D_801D3D64.pause_state & 3) {
                case 2:
                    D_800AA2EC = 0x44;
                    func_8001ED54(&D_80089374);
                    D_800AA2EC = D_801E2A44;
                    func_8001ED54(&D_800893BC);
                    D_800AA2EC = 0x47;
                    func_8001ED54(&D_800893E0);
                    main_pause_cursor = 0;
                    break;
                case 3:
                    main_pause_cursor = 1;
                    D_800AA2EC = 0x44;
                    func_8001ED54(&D_80089398);
                    D_800AA2EC = D_801E2A44;
                    func_8001ED54(&D_8008941C);
                    D_800AA2EC = 0x47;
                    func_8001ED54(&D_80089400);
                    break;
                default:
                    player--;
                    goto pause;
                }
            }
        }
        return 0;
    }
    flags = D_801D3D64.pause_state;
    switch (flags & 3) {
    case 0:
        if (D_801E28E0 != 0) {
            i = 0;
            while (i < 7) {
                who = D_801FA8A0[i];
                if (who != 0) {
                    player = who - 1;
                    if ((D_801E28E0 & main_pause_keys[player].pause) && main_can_pause(i + 1) == 1) {
                    pause:
                        main_pause_cursor = 0;
                        main_pause_delay = 12;
                        D_801D3DC6 = main_pause_keys[player].owner | 1;
                        func_800636B0();
                        func_8001F6E4();
                        func_80062E64();
                        main_create_pause_box(0x50, 0x3C, (GameObject *)0xF0, 0x5A);
                        D_800AA2EC = 0x44;
                        func_8001ED54(&D_80089374);
                        func_800180E4();
                        func_80060A7C(0x401, 0, 4);
                        func_80060A7C(0x402, 0, 4);
                        func_80060A7C(0x7B4, 0, 4);
                        return 0;
                    }
                }
                i++;
            }
        }
        break;
    case 1:
        D_801D3D64.pause_state = (flags & 0xFFFC) | 2;
        main_cycle_highlight();
        D_800AA2EC = D_801E2A44;
        func_8001ED54(&D_800893BC);
        D_800AA2EC = 0x47;
        func_8001ED54(&D_800893E0);
        break;
    case 2:
        i = (flags & 0x3000) >> 12;
        main_cycle_highlight();
        if ((D_801E0D7C & main_pause_keys[i].confirm) && main_pause_delay == 0) {
            main_free_kind(0x302);
            main_free_kind(0x303);
            main_pause_delay = 12;
            func_8001F724(3);
            func_8001802C(i);
            if (main_pause_cursor == 0) {
                D_801D3D64.pause_state = 0;
                main_free_kind(0x301);
                main_free_kind(0x550);
                func_8001F704();
                func_80062E88();
                func_800181D0();
                main_free_pause_box();
                func_80060A7C(0x401, 0x808080, 4);
                func_80060A7C(0x402, 0x808080, 4);
                func_80060A7C(0x7B4, 0x808080, 4);
            } else {
                main_pause_cursor = 1;
                D_801D3D64.pause_state |= 3;
                main_free_kind(0x301);
                D_800AA2EC = 0x44;
                func_8001ED54(&D_80089398);
                D_800AA2EC = D_801E2A44;
                func_8001ED54(&D_8008941C);
                D_800AA2EC = 0x47;
                func_8001ED54(&D_80089400);
            }
        } else if ((D_801E0D7C & main_pause_keys[i].move) && main_pause_delay == 0) {
            main_free_kind(0x302);
            main_free_kind(0x303);
            main_pause_delay = 12;
            func_8001F724(0x1E);
            if (main_pause_cursor == 0) {
                main_pause_cursor = 1;
                D_800AA2EC = 0x47;
                func_8001ED54(&D_800893BC);
                D_800AA2EC = D_801E2A44;
                func_8001ED54(&D_800893E0);
            } else {
                main_pause_cursor = 0;
                D_800AA2EC = D_801E2A44;
                func_8001ED54(&D_800893BC);
                D_800AA2EC = 0x47;
                func_8001ED54(&D_800893E0);
            }
        }
        break;
    case 3:
        i = (flags & 0x3000) >> 12;
        main_cycle_highlight();
        if ((D_801E0D7C & main_pause_keys[i].confirm) && main_pause_delay == 0) {
            main_free_kind(0x304);
            main_free_kind(0x305);
            main_pause_delay = 12;
            func_8001F724(3);
            func_8001802C(i);
            if (main_pause_cursor == 1) {
                D_801D3D64.pause_state = 0;
                main_free_kind(0x301);
                main_free_kind(0x550);
                func_8001F704();
                func_80062E88();
                main_free_pause_box();
                func_80060A7C(0x401, 0x808080, 4);
                func_80060A7C(0x402, 0x808080, 4);
                func_80060A7C(0x7B4, 0x808080, 4);
            } else {
                D_801D3D64.pause_state = 0;
                func_8001F6B4();
                D_801FA984[0] = 0;
                D_801FA984[1] = 0;
                D_801FA984[2] = 0;
                D_801FA984[3] = 0;
                for (i = 0; i < 7; i++) {
                    D_801FA8A0[i] = 0;
                }
                for (i = 0; i < 3; i++) {
                    p = &D_800A8FD4[i];
                    p->unk_04 = i;
                    p->unk_06 = 0;
                    p->unk_08 = 11;
                }
                D_801E0D64 = 0;
                D_801FA960 = 0;
                D_801D8728 = 0;
                D_800AA2DC = 0;
                memset(&D_8007BD78, 0, 0x94);
                func_8001D17C();
                func_8001E758();
                func_8002497C();
                D_8007A7D4 |= 1;
                func_8001D084();
                return 1;
            }
        } else if ((D_801E0D7C & main_pause_keys[i].move) && main_pause_delay == 0) {
            main_free_kind(0x304);
            main_free_kind(0x305);
            main_pause_delay = 12;
            func_8001F724(0x1E);
            if (main_pause_cursor == 1) {
                main_pause_cursor = 0;
                D_800AA2EC = 0x47;
                func_8001ED54(&D_8008941C);
                D_800AA2EC = D_801E2A44;
                func_8001ED54(&D_80089400);
            } else {
                main_pause_cursor = 1;
                D_800AA2EC = D_801E2A44;
                func_8001ED54(&D_8008941C);
                D_800AA2EC = 0x47;
                func_8001ED54(&D_80089400);
            }
        }
        break;
    }
    return 0;
}

void main_recolour_objects(s32 from, s32 to) {
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

void main_cycle_highlight(void) {
    s16 prev;

    if (--D_801FAC7C <= 0) {
        prev = D_801F9AB8;
        if (++D_801F9AB8 >= 10) {
            D_801F9AB8 = 0;
        }
        D_801E2A44 = D_8007A6F8[D_801F9AB8];
        main_recolour_objects(D_8007A6F8[prev], D_8007A6F8[D_801F9AB8]);
        D_801FAC7C = 4;
    }
}

void func_80018CB0(void) {
    main_init_system();
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

#ifdef NON_MATCHING
/* 93.14%: register allocation. With chan0 an s16 (port << 4) it gets no register, as in the original, and the
 * hoisted D_801E1C90 takes fp. What remains: the original gives buttons (D_800AFB78, set in the prologue) s7 and
 * leaves the multitap loop's hoisted constant 1 without a register (li t0,1 at each use, and reload_cse's sllv by
 * t0); here the constant 1 (7 refs over 196 insns, priority 0.071) ranks above buttons (7 refs over 348, 0.040) and
 * buttons is rematerialised at each use. Buttons would need 9 refs, or the constant 1 one ref less. The original
 * also reloads chan0 with lhu from its stack slot in the single-pad path (here recomputed from port). The pad
 * reader: a multitap's four pads or one, the buttons inverted, the analog stick as d-pad bits */
s32 main_read_pad(u8 *buf, u16 n, s16 base, s16 port) {
    s16 chan0;
    u16 chan;
    u16 state;
    u16 i;
    u8 *pad;
    u16 *buttons = D_800AFB78;

    if (buf[0] != 0) {
        for (i = base; i < n; i++) {
            D_801E1C90[base] = 0;
        }
        return 1;
    }
    chan0 = port << 4;
    if (buf[1] == 0x80) {
        D_801E28B8[(s16) chan0 >> 4] = 1;
        for (i = 0; i < n; i++) {
            chan = i + chan0;
            state = PadGetState(chan);
            if (state == 1) {
                D_800AA2F0[i + base] = 0;
            }
            if (D_800AA2F0[i + base] == 0) {
                PadSetAct(chan, D_801C51C8[i + base], 2);
                if (state == 6 && PadSetActAlign(chan, D_8007A714) != 0) {
                    D_800AA2F0[i + base] = 1;
                }
            }
            pad = &buf[i * 8 + 2];
            if (pad[0] == 0 && (pad[1] == 0x41 || pad[1] == 0x73)) {
                D_801E1C90[i + base] = 1;
                buttons[i + base] = ~((pad[2] << 8) | pad[3]);
                if (pad[1] == 0x73) {
                    if (pad[7] < 0x50) {
                        buttons[i + base] |= 0x1000;
                    }
                    if (pad[7] > 0xB0) {
                        buttons[i + base] |= 0x4000;
                    }
                    if (pad[6] < 0x50) {
                        buttons[i + base] |= 0x8000;
                    }
                    if (pad[6] > 0xB0) {
                        buttons[i + base] |= 0x2000;
                    }
                }
            } else {
                D_801E1C90[i + base] = 0;
                buttons[i + base] = 0;
            }
        }
        if (n < 4) {
            return (s16) n;
        }
        return 4;
    }
    D_801E28B8[(s16) chan0 >> 4] = 0;
    state = PadGetState(chan0);
    if (state == 1) {
        D_800AA2F0[base] = 0;
    }
    if (D_800AA2F0[base] == 0) {
        PadSetAct(chan0, D_801C51C8[base], 2);
        if (state == 6 && PadSetActAlign(chan0, D_8007A714) != 0) {
            D_800AA2F0[base] = 1;
        }
    }
    if (buf[1] == 0x41 || buf[1] == 0x73) {
        D_801E1C90[base] = 1;
        buttons[base] = ~((buf[2] << 8) | buf[3]);
        if (buf[1] == 0x73) {
            if (buf[7] < 0x50) {
                buttons[base] |= 0x1000;
            }
            if (buf[7] > 0xB0) {
                buttons[base] |= 0x4000;
            }
            if (buf[6] < 0x50) {
                buttons[base] |= 0x8000;
            }
            if (buf[6] > 0xB0) {
                buttons[base] |= 0x2000;
            }
        }
    } else {
        D_801E1C90[base] = 0;
        buttons[base] = 0;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/main", main_read_pad);
#endif

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
        total += main_read_pad(D_800AA900[k], 3 - total, total, k);
    }
    for (i = 0; i < 3; i++) {
        D_801E1C98[i] = D_801E1C90[i];
    }
    return D_800AFB78;
}

#ifdef NON_MATCHING
/* 96.93%: everything up to the tile loop matches. What remains is loop.c. The original's inner loop moved, in insn
 * order, the jump table, D_801CA474+0xB8 (its own lui/addiu, D_801CA52C), 5, 40 and D_801CA474, not 400; the outer
 * loop then moved the first five of them again and stopped at 40 (each already-moved value doubles insn_count),
 * which is why 40 and D_801CA474 are set in the outer body. Here the inner loop moves the 7-insn i*0x4940 chain
 * between the base and 5, so the threshold (58 without calls, -3 per moved value) is 25 at 5 against 53 insns, and
 * cse2 derives D_801CA474 from the hoisted +0xB8 base. 5 and 40 are moved only when about four values precede them,
 * so the original's tile address had no i*0x4940 product in the inner loop ahead of the setlen constants; a
 * DrawState pointer per outer pass removes it but also the two symbol bases (90.7 %). The start-up: callbacks, CD,
 * pads, the two frame buffers, VRAM cleared, the font */
void main_init_system(void) {
    RECT rect;
    s32 colour;
    s32 i;
    s32 j;

    ResetCallback();
    D_801F9948 = D_801E1C78 = D_800B09C0;
    CdInit();
    func_80018D84();
    PadInitMtap(D_800AA900[0], D_800AA900[1]);
    for (i = 0; i < 3; i++) {
        D_801E1C98[i] = 0;
        D_801E1C90[i] = 0;
        D_800AA2F0[i] = 0;
        D_801C51C8[i][0] = 0;
        D_801C51C8[i][1] = 0;
    }
    PadStartCom();
    ChangeClearPAD(0);
    ResetGraph(0);
    SetGraphDebug(0);
    InitGeom();
    VSync(0);
    SetDefDrawEnv(&D_801CA474[0].draw, 0, 0, 0x180, 0xF0);
    SetDefDispEnv(&D_801CA474[0].disp, 0, 0x100, 0x180, 0xF0);
    SetDefDrawEnv(&D_801CA474[1].draw, 0, 0x100, 0x180, 0xF0);
    SetDefDispEnv(&D_801CA474[1].disp, 0, 0, 0x180, 0xF0);
    SetGeomScreen(0x400);
    D_801CA474[0].draw.isbg = 1;
    D_801CA474[1].draw.isbg = 1;
    setRGB0(&D_801CA474[0].draw, 0, 0, 0);
    setRGB0(&D_801CA474[1].draw, 0, 0, 0);
    for (i = 0; i < 2; i++) {
        SetPolyG4(&D_801CA474[i].sky[0]);
        SetPolyG4(&D_801CA474[i].sky[1]);
        D_801CA474[i].sky[0].x0 = 0;
        D_801CA474[i].sky[0].x1 = 0x190;
        D_801CA474[i].sky[0].x2 = 0;
        D_801CA474[i].sky[0].x3 = 0x190;
        D_801CA474[i].sky[1].x0 = 0;
        D_801CA474[i].sky[1].x1 = 0x190;
        D_801CA474[i].sky[1].x2 = 0;
        D_801CA474[i].sky[1].x3 = 0x190;
    }
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 6; j++) {
            switch (j) {
            case 0:
                colour = 0xFF0000;
                break;
            case 1:
                colour = 0xFF00;
                break;
            case 2:
                colour = 0xFF;
                break;
            case 3:
                colour = 0xFFFFFF;
                break;
            case 4:
                colour = 0;
                break;
            case 5:
                colour = 0xFF00FF;
                break;
            }
            SetPolyF4(&D_801CA474[i].tiles[j]);
            D_801CA474[i].tiles[j].x1 = 0x190;
            D_801CA474[i].tiles[j].x3 = 0x190;
            D_801CA474[i].tiles[j].r0 = colour >> 16;
            D_801CA474[i].tiles[j].g0 = colour >> 8;
            D_801CA474[i].tiles[j].x0 = 0;
            D_801CA474[i].tiles[j].x2 = 0;
            D_801CA474[i].tiles[j].b0 = colour;
        }
    }
    D_801FAC80 = D_801FAC80 == &D_801CA474[0] ? &D_801CA474[1] : &D_801CA474[0];
    D_801FA974 = D_801E299C = (s32) &D_801C51C0;
    EnterCriticalSection();
    VSyncCallback(func_80017B98);
    ExitCriticalSection();
    memset(D_800B09C0, 0, 0x10000);
    memset(D_801D8868, 0, 0x84D0);
    rect.w = 0x80;
    rect.h = 0x100;
    for (i = 0; i < 0x400; i += 0x80) {
        rect.x = i;
        rect.y = 0;
        LoadImage(&rect, (u32 *) D_800B09C0);
        rect.x = i;
        rect.y = 0x100;
        LoadImage(&rect, (u32 *) D_800B09C0);
        DrawSync(0);
    }
    func_8001A454();
    main_load_font();
    D_801D3D7C = 0;
    SetDispMask(1);
}
#else
INCLUDE_ASM("asm/main/nonmatchings/main", main_init_system);
#endif

void main_begin_frame(void) {
    D_801FAC80 = (D_801FAC80 == &D_801CA474[0]) ? &D_801CA474[1] : &D_801CA474[0];
    ClearOTagR(D_801FAC80->ot, 4);
    D_801FAC80->next_prim = D_801FAC80->prims;
    D_801FAC80->tpage = 0xFFFF;
    D_801FAC80->last_tpage = 0xFFFF;
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

s32 main_load_image_4bit(s32 pixels, s32 w, s16 h, s16 slot) {
    Unk1C542C *e;
    RECT rect;
    s16 width;
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
                        rect.w = (width + 1) >> 1;
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

SpriteFrame *func_8001A554(s32 id, GameObject *obj) {
    SpriteFrame *frame;
    u32 index;
    u16 b;
    u16 flags;
    Unk1F9AE4 *e;

    if ((obj->unk_6C & 0x400) && obj->last_frame != id) {
        obj->unk_6C &= 0xFBFF;
        func_8001B350(obj->vram_slot);
    }
    if (id < 0) {
        frame = (SpriteFrame *) id;
        obj->unk_6C |= 8;
        obj->tex.w = frame->unk_00;
    } else {
        index = (u32) (id & 0xFFFFFF) >> 1;
        obj->bank = b = ((u32) id >> 24) & 0x3F;
        obj->anim_frame = id;
        if (index >= 0x2135) {
            index = 0;
            b = 0xF;
        }
        frame = (SpriteFrame *) (D_801FA738[b].unk_0 + (D_801D8868[index] & 0x7FFFFFFF));
        if ((D_801D8868[index] & 0x7FFFFFFF) == 0) {
            id = D_8007AD4C[(main_random_between(0x8000, 0xE) & 0x1F) + 10];
            frame = (SpriteFrame *) func_8001B128(id);
            obj->tex.w = frame->unk_00;
        }
        if (frame->unk_00 & 0x40000000) {
            obj->unk_6C |= 8;
            obj->tex.w = frame->unk_00;
        } else if (obj->last_frame != id || !(obj->unk_6C & 0x400)) {
            flags = obj->unk_6C;
            obj->unk_6C = flags & 0xFFF7;
            if (!(flags & 0x80)) {
                obj->unk_6C = (flags & 0xFFF7) | 0x400;
                if (frame->unk_00 & 0x20000000) {
                    obj->vram_slot = main_alloc_vram_slot(frame, D_801FA738[b].unk_0, 1);
                    e = &D_801F9AE4[obj->vram_slot];
                    obj->tex.w = e->unk_0.w | 0x20000000;
                } else {
                    obj->vram_slot = main_alloc_vram_slot(frame, D_801FA738[b].unk_0, 0);
                    e = &D_801F9AE4[obj->vram_slot];
                    obj->tex.w = e->unk_0.w;
                }
            }
        }
    }
    obj->last_frame = id;
    return frame;
}

s32 func_8001A784(u32 id) {
    u32 index;

    if ((s32) id >= 0) {
        index = (id & 0xFFFFFF) >> 1;
        id = D_801FA738[(id >> 24) & 0x3F].unk_0 + (D_801D8868[index] & 0x7FFFFFFF);
        if ((D_801D8868[index] & 0x7FFFFFFF) == 0) {
            id = D_8007AD4C[(main_random_between(0x8000, 0xE) & 0x1F) + 10];
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
    word = obj->tex.w;
    if (obj->unk_6C & 0x400) {
        rec = &D_801F9AE4[obj->vram_slot];
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
        func_8001B350(arg0->vram_slot, arg0);
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
        main_run_calls();
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
        main_update_attract();
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

void func_8009A238(void);
void func_8009A708(void);
s32 func_8009AE40(s32 *point);
s32 func_80099B54(void);
void func_8009B23C(void);
extern s32 D_801CA460;
extern s16 D_801D87C4;
extern s32 D_8007AAB8[];
extern TextMessage D_80089584;

void func_8001C02C(void) {
    switch (D_801D3780) {
    case 0:
        if (D_801CA464 & 2) {
            func_8009A238();
            D_801D3780 = 0x64;
            return;
        }
        if ((s16) (D_801FA960 % 25) != 0) {
            func_8009A708();
            D_801CA460 = 0;
            D_801D3780 = 0x62;
            return;
        }
        D_801CA45C = 1;
        D_801D3780 = 0x63;
        D_801CA464 &= ~1;
        return;
    case 0x62:
        if (func_8009AE40(&D_801CA460) == 0) {
            D_801D3780 = 0x63;
            D_801CA45C = 1;
            D_801CA464 &= ~1;
        }
        return;
    case 0x63:
        if ((s16) (D_801FA960 % 25) == 0) {
            if (D_801FA984[0] == 0 && D_801FA984[1] == 0 && D_801FA984[2] == 0) {
                cdload_load_overlay(1);
                func_800A9890(0xE);
                cdload_load_overlay(0);
                D_801D3780 = 0x65;
                goto finish;
            }
            D_801D3780 = 0x65;
            return;
        }
        D_801D3780 = 0x65;
        return;
    case 0x64:
        if (func_80099B54() == 0) {
            D_801D3780 = 0;
            D_801CA464 &= ~2;
        }
        return;
    case 0x65:
        switch (D_801FA960) {
        case 0x18:
        case 0x31:
        case 0x4A:
            if (D_801E289C >= 3) {
                cdload_load_overlay(1);
                func_800A9890(D_8007AAB8[D_801E289C - 3]);
                cdload_load_overlay(0);
            }
        }
    finish:
        D_801FB18C = 1;
        func_8009B23C();
        return;
    }
    if (D_801D3780 >= 3) {
        if (--D_801CA460 == 0) {
            D_801D3780 = 1;
            main_free_kind(0x4FF);
        }
    } else if (D_801D3780 == 2) {
        cdload_load_overlay(2);
    } else if (D_801E29BC != 0) {
        if (--D_801E29BC == 3) {
            if (D_801D87C4 == -1 || !(D_801D87C4 & 3)) {
                main_free_kind(0x4FF);
                func_8001ED54(&D_80089584);
            }
        }
    } else {
        cdload_load_overlay(2);
        func_8001C3C4();
        D_801E29BC = -1;
    }
}

void func_8001C3C4(void) {
    main_init_level();
}

s16 main_get_monster_player(s16 id) {
    return D_801FA8A0[id];
}

s32 cdload_city_file_index(s32 arg0);
void cdload_load_city_table(s32 file);
void cdload_sort_players(void);
void func_8002B988(void);
void func_80031444(void);
void func_8003684C(void);
void pickup_hide_items(void);
void func_8003DFD4(void);
void func_8003ED4C(void);
void func_80043F30(void);
void func_800476A8(void);
void func_8004AEE0(void);
void func_8005E398(void);
void pickup_spawn_all(void);
extern u16 D_8007AAC4[];
extern s16 D_80084278;
extern s16 D_801D8580;
extern s16 D_801D87C0;
extern u16 D_801D8860;
extern s16 D_801E1C88;
extern s16 D_801E1E20;
extern s16 D_801FA980;

void main_init_level(void) {
    s32 banks[7][2] = {
        { 2, 0x2B }, { 3, 0x2C }, { 4, 0x2D }, { 0xE, 0x2E }, { 9, 0x2F }, { 0xC, 0x30 }, { 0xD, 0x31 },
    };
    u16 i;

    D_801E1C88 = -1;
    cdload_sort_players();
    D_80084278 = 0;
    D_801FA9B8 = 1;
    D_801D3758 = 0;
    D_8007A698 = 0;
    D_801D3D64.scroll_vx = 0;
    D_801D3D64.unk_2C = 0;
    D_801D3D64.scroll_state = 0;
    D_801D3D64.unk_24 = 0;
    D_801F9ACC.w = 0;
    D_801F9AC8.w = 0;
    D_801D87C8 = 0;
    D_8007BD78.flags &= ~0x7800;
    func_8001D17C();
    func_8001E758();
    func_8001F6B4();
    D_8007A696 = 0;
    func_8001A1C8();
    func_8001A474();
    func_8002497C();
    func_8001D084();
    if (D_801FA960 == 0x63) {
        D_801E289C = 6;
    }
    cdload_load_city_table(cdload_city_file_index(1) & 0xFFFF);
    i = cdload_city_file_index(0);
    func_8001A420();
    func_8001AC18(8, i);
    switch (D_801FA960) {
    case 0x18:
    case 0x31:
    case 0x4A:
    case 0x63:
        if (main_get_monster_player(D_801E289C) == 0) {
            func_8001AA4C((u16) banks[D_801E289C][0], (u16) banks[D_801E289C][1]);
        }
        break;
    }
    func_8001AA4C(1, 1);
    D_801F9A3C = 1;
    func_80017B24();
    D_801F9A3C = 0;
    func_8002B988();
    i = 0;
    D_8007A7D4 &= ~1;
    while (D_8007AAC4[i] <= D_801E1E18) {
        if (D_8007AAC4[i] == 0xFFFF) {
            break;
        }
        i++;
    }
    D_801D8580 = i;
    func_8005E398();
    func_80031444();
    main_create_buildings();
    func_8003684C();
    pickup_spawn_all();
    pickup_hide_items();
    if (D_800AA2DC == 0 || !(D_8007BD78.flags & 0x80)) {
        func_8003DFD4();
    }
    func_8003ED4C();
    func_80043F30();
    func_800476A8();
    func_80029B54();
    D_801D87C0 = 7;
    D_801D87C8 = 0x3FF;
    D_801F9A34 = 0xA;
    func_8004AEE0();
    D_801E1E20 = 0;
    main_resort_objects();
    D_801D3D7C = 1;
    SetDispMask(0);
    func_80020CE4(0, D_801D8860);
    D_801FA980 = 1;
    D_801D36FC = 0x150;
    func_8001F6B4();
    func_8001F780();
}

void func_8001C77C(void) {
}

void func_8001C784(void) {
    D_801D3758 += 1;
    func_8001CFE4();
    main_update_monsters();
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

/* The attract screen's state machine (D_801D3780), its screens in OVERATTR (func_800996CC, func_800991EC,
 * func_8009C828). The state is read from the global each time: its copy for the switch and the store of 2 (the
 * known state) into D_800A9840 come from that */
void func_800991EC(void);
void func_800996CC(void);
s32 func_8009C828(void);  /* menu_update_credits in OVERATTR */
void func_800A1720(s16 id);
extern s32 D_8007AAE0[];
extern s32 D_8007AAFC[];
extern TextMessage D_800897A0;
extern TextMessage D_800897C4;
extern TextMessage D_800897E0;
extern s32 D_800A9220;
extern s32 D_800A9250;
extern s16 D_800A9298;
extern s16 D_800A92A0;
extern s16 D_800A92B8;
extern s16 D_800A92D0;
extern u16 D_800A9840;
extern s16 D_800A9898;
extern s16 D_800A98B8;
extern s16 D_801F9AAC;
extern s16 D_801FB468;

void main_update_attract(void) {
    s32 i;
    s32 id;

    if (D_800AA2DC != 0) {
        func_80017B24();
        D_801D3780 = 5;
    }
    if (D_801D3780 != 0) {
        if (D_801D3780 >= 5) {
            switch (D_801D3780) {
            case 5:
                if (D_800AA2DC != 0) {
                    switch ((s16) (D_801FA960 % 25)) {
                    case 4:
                    case 9:
                    case 14:
                    case 19:
                    case 23:
                        if (D_801FB468 != -1) {
                            for (i = 0; i < 7; i++) {
                                if (D_801FA8A0[i] == D_801FB468) {
                                    cdload_load_overlay(1);
                                    func_800A9890(D_8007AAFC[(func_8001EA78() & 1) + i * 2]);
                                    cdload_load_overlay(0);
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }
                switch (D_801FA960) {
                case 0x18:
                case 0x31:
                case 0x4A:
                case 0x63:
                    cdload_load_overlay(1);
                    func_800A9890(D_8007AAE0[D_801E289C]);
                    if (D_801FA960 == 0x63) {
                        id = 0x10;
                        goto play;
                    }
                    if (D_801FA984[0] != 0 && D_801FA984[1] != 0 && D_801FA984[2] != 0) {
                        id = 0xF;
                        goto play;
                    }
                    goto done;
                case 0x70:
                    cdload_load_overlay(1);
                    id = 0x1B;
                    goto play;
                case 0x7C:
                    cdload_load_overlay(1);
                    id = 0;
                play:
                    func_800A9890(id);
                done:
                    cdload_load_overlay(0);
                    D_801CA45C = 1;
                    D_801D3780 = 0x65;
                    func_80017B24();
                    return;
                }
                goto reset;
            case 8:
                if (func_8009C828() == 0) {
                    D_801FA960 = 0;
                    D_801F9AE0 = 0;
                    D_801E29BC = 0x78;
                    D_801D36FC = 0x130;
                    D_801D3780 = 0;
                    D_801CA45C = 0;
                    func_8001D17C();
                    func_8001E758();
                }
                return;
            case 6:
            case 7:
            default:
            reset:
                D_801D3780 = 0;
                D_801E29BC = 0x78;
                if (D_801FA960 == 0x7C) {
                    D_801D3780 = 8;
                    D_800A92B8 = 0;
                    D_800A9298 = 0;
                    func_8009C828();
                    return;
                }
                if (D_800AA2DC != 0) {
                    D_801D36FC = func_800249B8(func_8001CFAC() & 0xFFFF);
                    cdload_load_overlay(0);
                    func_8001C02C();
                    return;
                }
                D_801D36FC = func_800249B8(func_8001CFAC() & 0xFFFF);
                return;
            }
        }
        if (D_801D3780 == 1) {
            func_800991EC();
            return;
        }
        if ((s16) (D_801FA960 % 5) != 0 || D_801FA960 == 0) {
            D_801D3780 = 5;
            return;
        }
        if (D_801D3780 == 2) {
            func_800180E4();
            D_800AA2EC = 0x44;
            func_8001ED54(&D_800897A0);
            D_800AA2EC = 0x47;
            func_8001ED54(&D_800897E0);
            D_800AA2EC = 0x45;
            func_8001ED54(&D_800897C4);
            D_800A92D0 = 0;
            D_800A9840 = 2;
            D_801E2A44 = 0x45;
            D_801F9AAC = 0x47;
            D_801D3780++;
            return;
        }
        if (D_801D3780 == 3) {
            if (D_801F9944 != 0) {
                D_801F9944--;
            }
            func_80019268();
            D_800A9250 = D_800A9220;
            D_800A9220 = D_801E0D7C & 0x3FFFFFFF;
            if ((D_800A9220 & 0x100401) && D_801F9944 == 0) {
                if (--D_800A92D0 < 0) {
                    D_800A92D0 = D_800A9840 - 1;
                }
                D_801F9944 = 0xB;
                D_801D872C /= 2;
                func_8001F724(0x1E);
            } else if ((D_800A9220 & 0x200802) && D_801F9944 == 0) {
                if (++D_800A92D0 >= (s16) D_800A9840) {
                    D_800A92D0 = 0;
                }
                D_801F9944 = 0xB;
                D_801D872C /= 2;
                func_8001F724(0x1E);
            } else if ((D_800A9220 & 0x01004010) && D_801F9944 == 0) {
                D_801F9944 = 0xB;
                D_801D872C /= 2;
                D_801D3780++;
                main_free_kind(0x550);
                if (D_800A92D0 == 0) {
                    D_800A9898 = 1;
                    D_800A98B8 = 0;
                    D_800A92A0 = 0;
                    D_801E29BC = 5;
                } else {
                    D_800A9898 = 1;
                    D_800A98B8 = 4;
                }
            }
            if (D_800A92D0 == 0) {
                func_8001EC74(0x405, (s16) D_801E2A44);
                func_8001EC74(0x406, D_801F9AAC);
            } else {
                func_8001EC74(0x405, D_801F9AAC);
                func_8001EC74(0x406, (s16) D_801E2A44);
            }
            main_cycle_highlight();
            return;
        }
        func_800A1720(D_801FA960);
    } else {
        cdload_load_overlay(0);
        func_8001F6B4();
        func_80062EA8(1);
        func_800996CC();
        D_801D3780 = 1;
    }
}

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
    D_8007AB60.count += 1;
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

extern MainDemoDef D_8007A7D8[];
extern s16 D_801FA96C;

void main_start_demo(void) {
    MainDemo *demo;
    MainDemoDef *def;
    Monster *monster;
    u16 k;
    s32 i;
    s8 *p;

    D_801FA96C = 0;
    for (i = 0; i < 3; i++) {
        D_800A8FD4[i].unk_04 = i;
        D_800A8FD4[i].unk_06 = 0;
        D_800A8FD4[i].unk_08 = 0xB;
    }
    D_8007A7D4 |= 1;
    func_8001D084();
    demo = &D_8007AB60;
    D_801D8854 = 2;
    D_801D8728 = 0;
    k = demo->count % 3;
    D_801E1CAC = D_801FA960 = D_801E1E18 = D_801FA964 = D_8007A7D8[(u16) (demo->count % 3)].unk_0;
    def = &D_8007A7D8[k];
    cdload_load_overlay(2);
    i = 6;
    p = &D_801FA8A0[i];
    do {
        *p = 0;
        i -= 1;
        p -= 1;
    } while (i >= 0);
    D_801FA8A0[def->monster[0]] = demo->script[0] != NULL;
    D_801FA8A0[def->monster[1]] = (demo->script[1] != NULL) * 2;
    D_801FA9B8 = 0;
    func_8001C02C();
    D_801D36FC = 0x120;
    D_801E0D64 = 0;
    if (demo->script[0] != NULL) {
        monster = &D_801E0B78[func_80025DF8(1)];
        D_801E0D64 = 1;
        monster->unk_1E4 = demo->script[0];
        monster->unk_1E0 = 2;
    }
    if (demo->script[1] != NULL) {
        monster = &D_801E0B78[func_80025DF8(2)];
        D_801E0D64 |= 2;
        monster->unk_1E4 = demo->script[1];
        monster->unk_1E0 = 2;
    }
    if (demo->script[2] != NULL) {
        monster = &D_801E0B78[3];
        D_801E0D64 |= 4;
        monster->unk_1E4 = demo->script[2];
        monster->unk_1E0 = 2;
    }
}

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

void main_start_demo(void);

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
        main_start_demo();
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
    return main_cull_objects(&D_801E28C0) & 0xFFFF;
}

s32 func_8001D974(void) {
    return main_cull_objects(&D_801E29A8) & 0xFFFF;
}

#ifdef NON_MATCHING
/* 85.59%: register allocation and four copies: the original keeps copies of inline arguments still live after the
 * call (box in t5 and a2, off in t4, pos in a0). Its frame is 8 bytes larger (0x38) with slots never accessed: the
 * block expand_inline_function reserves (assign_stack_temp) when an inlined body refers to its own frame or
 * incoming arguments. A helper that writes the low half of an uninitialised Fixed first (r.s.lo = a.s.lo + b.s.lo;
 * r.s.hi = ...) reserves exactly 8 bytes (s0 at 24), but loses the mask of the first argument's other half that the
 * original's arithmetic shows (it modifies a copy of its first argument); a helper doing both is not found. Results
 * used directly (main_pair_add(box, scr).s.lo) reserve 16 bytes. The wrap add's high half uses srl in the original
 * (an unsigned half) */
static inline Fixed main_pair_add(Fixed a, Fixed b) {
    a.s.lo += b.s.lo;
    a.s.hi += b.s.hi;
    return a;
}

static inline Fixed main_pair_sub(Fixed a, Fixed b) {
    a.s.lo -= b.s.lo;
    a.s.hi -= b.s.hi;
    return a;
}
s32 main_cull_objects(GameObject *head) {
    GameObject *obj;
    GameObject *prev;
    u16 count;
    u16 flags;
    Fixed size;
    Fixed box;
    Fixed org;
    Fixed pos;
    Fixed y;
    Fixed d;
    Fixed off;
    Fixed scr;
    Fixed end;
    Fixed wrap;

    obj = head;
    count = 0;
    for (;;) {
        prev = obj;
        obj = obj->next;
        if (obj == NULL || obj == prev || obj == head) {
            break;
        }
        size = obj->unk_2C;
        box = size;
        box.s.lo -= 1;
        obj->size = size;
        flags = obj->unk_6C;
        if (flags & 0x8000) {
            continue;
        }
        pos = obj->pos_x;
        y = obj->pos_y;
        org.w = obj->unk_7C;
        if (!(flags & 0x20)) {
            if (!(flags & 0x10)) {
                pos.w -= D_801F9AC8.w;
            }
            y.w -= D_801F9ACC.w;
        }
        pos.s.lo = pos.s.hi;
        pos.s.hi = y.s.hi;
        d = main_pair_sub(box, org);
        off.w = 0;
        if (obj->flags & 0x10) {
            org.s.lo = d.s.lo;
            off.s.lo = box.s.lo;
        }
        scr = main_pair_sub(pos, org);
        obj->unk_28 = main_pair_add(off, scr);
        if (scr.s.lo < D_801FA7E4[0] + 0x40 && scr.s.hi < D_801FA7E4[1] + 0x20) {
            end = main_pair_add(box, scr);
            if (D_801FA7E8[1] - 0x20 < end.s.hi) {
                if (D_801FA7E8[0] - 0x80 < end.s.lo) {
                    goto visible;
                }
                wrap.w = 0;
                wrap.s.lo = D_801D8866 + 1;
                pos = main_pair_add(pos, wrap);
                scr = main_pair_sub(pos, org);
                obj->unk_28 = main_pair_add(off, scr);
                if (scr.s.lo < D_801FA7E4[0] + 0x40 && D_801FA7E8[0] - 0x80 < (s16) (box.s.lo + scr.s.lo)) {
                    goto visible;
                }
            }
        }
        goto hidden;
    visible:
        count++;
        func_8001B098(obj);
        continue;
    hidden:
        func_8001B054(obj);
    }
    return count;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/main", main_cull_objects);
#endif

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
    D_800AA248.def_flags = *(s32 *) p;
    p += 2;
    D_800AA248.unk_38 = 0x7FF;
    if (D_800AA248.def_flags & 0x40) {
        D_800AA248.unk_74 = *(s32 *) p;
        p += 2;
        if (D_800AA248.unk_74 != 0) {
            D_800AA248.unk_38 = D_800AA248.unk_74;
        }
    }
    obj->kind = D_800AA248.unk_38;
    if (D_800AA248.def_flags & 0x20) {
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
    if (D_800AA248.def_flags & 1) {
        D_800AA248.unk_74 = *(s32 *) p;
        p += 2;
        if (D_800AA248.unk_74 != 0) {
            D_800AA248.unk_38 = D_800AA248.unk_74;
        }
    }
    obj->unk_82 = D_800AA248.unk_38;
    D_800AA248.unk_38 = 0;
    if (D_800AA248.def_flags & 2) {
        D_800AA248.unk_38 = *(s32 *) p;
        p += 2;
    }
    obj->priority = D_800AA248.unk_38;
    if (D_800AA248.def_flags & 4) {
        D_800AA248.unk_74 = *(s32 *) p;
        p += 2;
        if (D_800AA248.unk_74 != 0) {
            func_80024964(D_800AA248.unk_74, obj);
        }
    }
    if (D_800AA248.def_flags & 8) {
        D_800AA248.unk_74 = *(s32 *) p;
        p += 2;
        if (D_800AA248.unk_74 != 0) {
            func_8001E698(obj, D_800AA248.unk_74);
        }
    }
    if (D_800AA248.def_flags & 0x10) {
        D_800AA248.on_create = *(void (**)(void)) p;
        if (D_800AA248.on_create != NULL) {
            D_800AA248.unk_00 = (s32) obj;
            D_800AA248.on_create();
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
        func_8001B350(arg0->vram_slot);
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
    sprite->colour.w = -1;
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

void main_seed_random(s16 arg0, s16 arg1) {
    D_801FAF70 = arg0;
    D_801FAF6C = arg1;
    D_801FAF6E = (arg0 * arg1) / 3;
}

/* The random number generator: its state is D_801FAF6C/6E/70 (seeded by main_seed_random). */
s16 main_random(void) {
    u16 prev;
    u16 seed;
    u16 next;
    s16 result;

    prev = D_801FAF6E;
    seed = D_801FAF6C;
    next = prev + 1;
    D_801FAF6E = next;
    result = prev ^ ((D_801FAF70 ^ ((seed << 5) + (prev << 3) - 1)) - seed);
    if ((seed << 0x10) < (next << 0x10)) {
        D_801FAF6E = prev + 2;
    }
    D_801FAF70 = seed;
    D_801FAF6C = (u16) result;
    return result;
}

s32 func_8001EA78(void) {
    s16 temp_s0;
    s32 temp_lo;

    temp_s0 = main_random();
    temp_lo = temp_s0 * main_random();
    D_801E0D6C = temp_lo;
    return temp_lo;
}

s32 main_random_range(s32 range) {
    if (range == 0) {
        return 0;
    }
    return func_8001EA78() % (u32) range + 1;
}

s32 main_random_between(s32 arg0, s32 arg1) {
    return arg1 + main_random_range(arg0 - arg1);
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
    g->cur_obj->colour.w = colour;
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
    main_print_text();
}

void func_8001EE24(void) {
    D_801D8588.unk_20 = 0x8002;
    D_801D8588.flags = 0x10000;
    D_801D8588.unk_28 = 0x8101;
    main_print_text();
}

void func_8001EE60(void) {
    D_801D8588.unk_20 = 0x8002;
    D_801D8588.flags = 0x10002;
    D_801D8588.unk_28 = 0x8101;
    main_print_text();
}

#ifdef NON_MATCHING
/* 98.71%: the size matches; the frame is 0x40 (original 0x48: one more 4-byte slot, at 24, never accessed) and
 * three registers differ: the original loads the glyph code into s1, copies it to s3 (the anim_frame) after
 * func_8001B128 and gives the glyph s1; here id keeps the code in s1 throughout and the glyph takes s3. With 0x2000
 * clear the original reloads pen_y after adding the width, a dead lhu: pen_y was written back unchanged and
 * reload_cse deleted the store. Written here as id reused for that round trip, which gives the dead load and the
 * original's s1/s2. The unused slot, the dead load and s3 fit one variable that reload took out of its register
 * after global allocation (its slot comes after the one of &off) and served with reload registers (s3, then v1),
 * delete_output_reload removing its stack stores: the code's copy and the pen_y round trip were one variable, but
 * no form found makes it lose its register here. Prints D_801D8588's text: a sprite per glyph, control codes below
 * 0x20 through D_8007B04C */
extern void (*D_8007B04C[])(void);
extern GameObject *D_801FB17C;

void main_print_text(void) {
    Fixed off;
    Glyph *glyph;
    u32 id;
    s32 saved0;
    s32 saved34;
    s32 saved8;
    s32 saved30;
    s32 saved10;
    s16 width;

    D_801FB17C = NULL;
    func_8001F400();
    func_8001F4EC();
    func_8001F4F4();
    if (D_801D8588.advance.s.hi != 0) {
        D_801D8588.unk_32 = D_801D8588.advance.s.hi;
        D_801D8588.advance.s.hi = 0;
    }
    *(s32 *) &D_801D8588.line_start = *(s32 *) &D_801D8588.pen_x;
    func_8001F464();
    for (D_801D8588.unk_3A = *D_801D8588.text; D_801D8588.unk_3A != 0; D_801D8588.unk_3A = *D_801D8588.text) {
        D_801D8588.unk_38 = 0;
        D_801D8588.text++;
        if (D_801D8588.unk_3A > 0x20) {
            saved10 = D_801D8588.advance.w;
            saved0 = D_801D8588.unk_00;
            saved34 = *(s32 *) &D_801D8588.line_start;
            saved8 = D_801D8588.unk_08;
            saved30 = *(s32 *) &D_801D8588.space_width;
            id = D_801D8588.glyphs[D_801D8588.unk_3A - 0x21];
            glyph = func_8001B128(id);
            func_8001E638((Unk1E638 *) glyph, D_801D8588.unk_20, (Fixed *) &D_801D8588.space_width, &off.w);
            if (D_801D8588.flags & 0x10000) {
            if ((D_800AA248.cur_obj = func_8001E204()) != NULL) {
                D_800AA248.cur_obj->frame = (SpriteFrame *) glyph;
                D_800AA248.cur_obj->anim_frame = id;
                D_800AA248.cur_obj->unk_2C.w = ((Unk1E638 *) glyph)->unk_4.w;
                D_800AA248.cur_obj->tex.w = glyph->unk_0;
                D_800AA248.cur_obj->unk_74 = D_800AA2EC;
                D_800AA248.cur_obj->colour.w = 0xFFFFFFFF;
                D_800AA248.cur_obj->bank = 0xF;
                D_800AA248.cur_obj->unk_28.s.lo = D_800AA248.cur_obj->pos_x.s.hi = D_801D8588.pen_x - D_801D8588.unk_32;
                D_800AA248.cur_obj->unk_28.s.hi = D_800AA248.cur_obj->pos_y.s.hi = D_801D8588.pen_y - off.s.hi;
                D_800AA248.cur_obj->unk_20 = D_801D8588.unk_20;
                D_800AA248.cur_obj->unk_20 = 0;
                D_800AA248.cur_obj->kind = D_801D8588.unk_18;
                D_800AA248.cur_obj->unk_6C = D_801D8588.unk_28 | 8;
                D_800AA248.cur_obj->size.w = D_800AA248.cur_obj->unk_2C.w;
                D_800AA248.cur_obj->priority = 0x7000;
                D_800AA248.cur_obj->unk_82 = 0;
                if (D_801FB17C == NULL) {
                    D_801FB17C = D_800AA248.cur_obj;
                }
                if (D_801D8588.unk_38 == 0 && !(D_801D8588.flags & 0x20000)) {
                    func_8001E2F8(D_800AA248.cur_obj);
                }
            }
            if (D_801D8588.unk_38 != 0) {
                D_801D8588.unk_00 = saved0;
                *(s32 *) &D_801D8588.line_start = saved34;
                D_801D8588.unk_08 = saved8;
                *(s32 *) &D_801D8588.space_width = saved30;
                D_801D8588.advance.w = saved10;
                *(s32 *) &D_801D8588.pen_x = D_801D8588.saved_pen;
                continue;
            }
            width = glyph->unk_4;
            if (!(D_801D8588.flags & 0x2000)) {
                id = D_801D8588.pen_y;
                D_801D8588.pen_x += width;
                D_801D8588.pen_y = id;
            }
            D_801D8588.unk_00 = saved0;
            D_801D8588.advance.w = saved10;
            *(s32 *) &D_801D8588.line_start = saved34;
            D_801D8588.unk_08 = saved8;
            *(s32 *) &D_801D8588.space_width = saved30;
            D_801D8588.pen_x += D_801D8588.advance.s.lo;
            D_801D8588.pen_y += D_801D8588.advance.s.hi;
            } else {
                func_8001B5E8(2);
                continue;
            }
        } else if (D_801D8588.unk_3A < 0x20) {
            D_8007B04C[D_801D8588.unk_3A - 1]();
            continue;
        } else {
            D_801D8588.unk_3A = 0;
            D_801D8588.saved_pen = *(s32 *) &D_801D8588.pen_x;
            if (!(D_801D8588.flags & 0x2000)) {
                D_801D8588.pen_x += D_801D8588.space_width;
            }
            D_801D8588.pen_x += D_801D8588.advance.s.lo;
            D_801D8588.pen_y += D_801D8588.advance.s.hi;
        }
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/main", main_print_text);
#endif

void func_8001F268(void) {
}

void func_8001F270(void) {
    u16 y;

    y = D_801D8588.unk_36 + D_801D8588.unk_32;
    D_801D8588.pen_x = D_801D8588.line_start;
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
    D_801D8588.advance.w = msg->spacing;
    D_801D8588.glyphs = msg->glyphs;
    D_801D8588.unk_18 = msg->kind;
    D_801D8588.text = msg->text;
}

void func_8001F400(void) {
    Glyph *glyph;

    glyph = func_8001B128(D_801D8588.glyphs[0x27]);
    D_801D8588.space_width = glyph->unk_4 >> 1;
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
    saved30 = *(s32 *) &D_801D8588.space_width;
    saved10 = D_801D8588.advance.w;
    p = text;
    func_8001F400();
    c = *p;
    width = 0;
    while (c != 0 && c != 13 && c != 10) {
        if (D_801D8588.flags & 0x2000) {
            width += D_801D8588.advance.s.lo;
        } else {
            if (c == 0x20) {
                width += D_801D8588.space_width + D_801D8588.advance.s.lo;
            } else {
                width += func_8001B128(D_801D8588.glyphs[*p - 0x21])->unk_4 + D_801D8588.advance.s.lo;
            }
        }
        p++;
        c = *p;
    }
    D_801D8588.unk_00 = saved0;
    *(s32 *) &D_801D8588.space_width = saved30;
    D_801D8588.advance.w = saved10;
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
    D_801D8588.advance.w = spacing;
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
            D_801FAC80->sky[0].y0 = -(D_801F9ACC.w >> 16);
            D_801FAC80->sky[0].y1 = -(D_801F9ACC.w >> 16);
            D_801FAC80->sky[0].y2 = bottom - (D_801F9ACC.w >> 16);
            D_801FAC80->sky[0].y3 = bottom - (D_801F9ACC.w >> 16);
            D_801FAC80->sky[1].y0 = -0xA0 - (D_801F9ACC.w >> 16);
            D_801FAC80->sky[1].y1 = -0xA0 - (D_801F9ACC.w >> 16);
            D_801FAC80->sky[1].y2 = -(D_801F9ACC.w >> 16);
            D_801FAC80->sky[1].y3 = -(D_801F9ACC.w >> 16);
            AddPrim(D_801FAC80->ot, D_801FAC80->sky);
            AddPrim(D_801FAC80->ot, &D_801FAC80->sky[1]);
        }
    }
}

void func_8001F9BC(GameObject *head, GameObject *end) {
    main_draw_objects(head, end);
}

extern u32 D_801FB41C;  /* the lit sprites' colour (building.c) */

/* Draws the object list: boxes (POLY_F4; a line of width 3 for 0x1000, a free quad for 0x2000), sprites (SPRT) and
 * flipped sprites (POLY_FT4), with a DR_TPAGE whenever the texture page changes. The colour block's gotos give the
 * original's block order (the unlit case last, falling into the test). The final reset of page is never read again:
 * it is the original's (it keeps page and tpage in two registers) */
void main_draw_objects(GameObject *head, GameObject *end) {
    GameObject *obj;
    POLY_F4 *box;
    SPRT *sprt;
    POLY_FT4 *ft4;
    DR_TPAGE *tp;
    s32 x0, y0, x1, y1, x2, y2;
    s32 ax, ay, bx, by, cx, cy, dx, dy;
    s32 angle;
    s16 page;
    u16 tpage;
    s32 mode;
    s32 du, dv;
    u8 lit;
    s16 rgb[3];
    s32 u, v;
    s32 w, h;
    u8 cr, cg, cb;

    for (obj = head->next; obj != end; obj = obj->next) {
        if (obj->unk_6C & 0x80) {
            continue;
        }
        if (obj->flags & 0xC) {
            box = (POLY_F4 *) D_801FAC80->next_prim;
            if ((u8 *) (box + 1) >= (u8 *) &D_801FAC80->next_prim) {
                func_8001B5E8(0x14);
            }
            D_801FAC80->next_prim += sizeof(POLY_F4);
            setlen(box, 5);
            setcode(box, 0x28);
            if (obj->unk_6C & 0x1000) {
                x0 = obj->unk_50.cam_start & 0xFFFF;
                y0 = (u32) obj->unk_50.cam_start >> 16;
                x1 = obj->unk_54.w & 0xFFFF;
                y1 = (u32) obj->unk_54.w >> 16;
                x2 = obj->arg.cam_point & 0xFFFF;
                y2 = (u32) obj->arg.cam_point >> 16;
                angle = ratan2(x1 - x0, y0 - y1);
                ax = x0 + (-(rcos(angle) * 3) >> 12);
                ay = y0 + (-(rsin(angle) * 3) >> 12);
                bx = x0 + ((rcos(angle) * 3) >> 12);
                by = y0 + ((rsin(angle) * 3) >> 12);
                cx = x2 + (-(rcos(angle) * 3) >> 12);
                cy = y2 + (-(rsin(angle) * 3) >> 12);
                dx = x2 + ((rcos(angle) * 3) >> 12);
                dy = y2 + ((rsin(angle) * 3) >> 12);
                box->x0 = ax - (D_801F9AC8.w >> 16) - 8;
                box->y0 = ay - (D_801F9ACC.w >> 16) - 8;
                box->x1 = bx - (D_801F9AC8.w >> 16) - 8;
                box->y1 = by - (D_801F9ACC.w >> 16) - 8;
                box->x2 = cx - (D_801F9AC8.w >> 16) - 8;
                box->y2 = cy - (D_801F9ACC.w >> 16) - 8;
                box->x3 = dx - (D_801F9AC8.w >> 16) - 8;
                box->y3 = dy - (D_801F9ACC.w >> 16) - 8;
            } else if (obj->unk_6C & 0x2000) {
                box->x0 = (obj->unk_50.cam_start & 0xFFFF) - 8;
                box->y0 = ((u32) obj->unk_50.cam_start >> 16) - 8;
                box->x1 = (obj->unk_54.w & 0xFFFF) - 8;
                box->y1 = ((u32) obj->unk_54.w >> 16) - 8;
                box->x2 = (obj->arg.cam_point & 0xFFFF) - 8;
                box->y2 = ((u32) obj->arg.cam_point >> 16) - 8;
                box->x3 = (obj->unk_60 & 0xFFFF) - 8;
                box->y3 = ((u32) obj->unk_60 >> 16) - 8;
            } else {
                box->x0 = obj->pos_x.u.hi - 8;
                box->y0 = obj->pos_y.u.hi;
                box->x1 = obj->pos_x.u.hi - 8 + obj->unk_40.w;
                box->y1 = obj->pos_y.u.hi;
                box->x2 = obj->pos_x.u.hi - 8;
                box->y2 = obj->pos_y.u.hi + obj->script.height;
                box->x3 = obj->pos_x.u.hi - 8 + obj->unk_40.w;
                box->y3 = obj->pos_y.u.hi + obj->script.height;
            }
            /* the colour's bytes: 0x78 blue, 0x79 green, 0x7A red */
            cr = obj->colour.rgb.r;
            cg = obj->colour.rgb.g;
            cb = obj->colour.rgb.b;
            box->r0 = cr;
            box->g0 = cg;
            box->b0 = cb;
            if (obj->flags & 0x400) {
                box->code |= 2;
            } else {
                box->code &= ~2;
            }
            AddPrim(D_801FAC80->ot, box);
            continue;
        }
        if (!(obj->unk_6C & 0x408)) {
            func_8001A554(obj->anim_frame, obj);
        }
        tpage = page = main_get_tpage(obj, obj->flags & 0x700);
        if (D_801FAC80->tpage != page) {
            if (D_801FAC80->last_tpage != D_801FAC80->tpage) {
                tp = (DR_TPAGE *) D_801FAC80->next_prim;
                D_801FAC80->next_prim += sizeof(DR_TPAGE);
                SetDrawTPage(tp, 0, 0, D_801FAC80->tpage);
                AddPrim(D_801FAC80->ot, tp);
                D_801FAC80->last_tpage = D_801FAC80->tpage;
            }
            D_801FAC80->tpage = page;
        }
        mode = (obj->flags & 0x30) >> 4;
        if (mode == 0) {
            sprt = (SPRT *) D_801FAC80->next_prim;
            D_801FAC80->next_prim += sizeof(SPRT);
            setlen(sprt, 4);
            setcode(sprt, 0x64);
            sprt->x0 = obj->unk_28.u.lo - 8;
            sprt->y0 = obj->unk_28.u.hi - 8;
            sprt->w = obj->size.u.lo;
            sprt->h = obj->size.u.hi;
            sprt->u0 = obj->tex.uv.u;
            sprt->v0 = obj->tex.uv.v;
            if (obj->colour.w == 0xFFFFFFFF) {
                if (obj->kind >= 0x500 && obj->kind < 0x780) {
                    rgb[0] = (D_801FB41C >> 16) & 0xFF;
                    rgb[1] = (D_801FB41C >> 8) & 0xFF;
                    lit = 1;
                    rgb[2] = D_801FB41C & 0xFF;
                    goto sprt_lit;
                }
            } else {
                rgb[0] = (obj->colour.w >> 16) & 0xFF;
                rgb[1] = (obj->colour.w >> 8) & 0xFF;
                lit = 1;
                rgb[2] = obj->colour.w & 0xFF;
                goto sprt_lit;
            }
            lit = 0;
sprt_lit:
            if (lit) {
                sprt->code &= ~1;
                sprt->r0 = rgb[0];
                sprt->g0 = rgb[1];
                sprt->b0 = rgb[2];
            } else {
                sprt->code |= 1;
            }
            if (obj->flags & 0x400) {
                sprt->code |= 2;
            } else {
                sprt->code &= ~2;
            }
            sprt->clut = (obj->unk_74 != 0xFFFF) ? D_801C51D4[D_800AFB54[obj->bank] + obj->unk_74]
                                                   : D_801C51D4[D_800AFB54[obj->bank] + obj->frame->unk_0C];
            AddPrim(D_801FAC80->ot, sprt);
            continue;
        }
        ft4 = (POLY_FT4 *) D_801FAC80->next_prim;
        D_801FAC80->next_prim += sizeof(POLY_FT4);
        setlen(ft4, 9);
        setcode(ft4, 0x2C);
        switch (mode) {
        case 1:
            ft4->x0 = obj->unk_28.s.lo - 8;
            ft4->y0 = obj->unk_28.s.hi - 8;
            ft4->x1 = obj->unk_28.s.lo - obj->size.s.lo - 9;
            ft4->y1 = obj->unk_28.s.hi - 8;
            ft4->x2 = obj->unk_28.s.lo - 8;
            ft4->y2 = obj->unk_28.s.hi + obj->size.s.hi - 8;
            ft4->x3 = obj->unk_28.s.lo - obj->size.s.lo - 9;
            ft4->y3 = obj->unk_28.s.hi + obj->size.s.hi - 8;
            break;
        case 2:
            ft4->x0 = obj->unk_28.s.lo - 8;
            ft4->y0 = obj->unk_28.s.hi - 8;
            ft4->x1 = obj->size.s.lo + (obj->unk_28.s.lo - 8);
            ft4->y1 = obj->unk_28.s.hi - 8;
            ft4->x2 = obj->unk_28.s.lo - 8;
            ft4->y2 = obj->unk_28.s.hi - obj->size.s.hi - 8;
            ft4->x3 = obj->size.s.lo + (obj->unk_28.s.lo - 8);
            ft4->y3 = obj->unk_28.s.hi - obj->size.s.hi - 8;
            break;
        case 3:
            ft4->x0 = obj->unk_28.s.lo - 8;
            ft4->y0 = obj->unk_28.s.hi - 8;
            ft4->x1 = obj->unk_28.s.lo - obj->size.s.lo - 9;
            ft4->y1 = obj->unk_28.s.hi - 8;
            ft4->x2 = obj->unk_28.s.lo - 8;
            ft4->y2 = obj->unk_28.s.hi - obj->size.s.hi - 8;
            ft4->x3 = obj->unk_28.s.lo - obj->size.s.lo - 9;
            ft4->y3 = obj->unk_28.s.hi - obj->size.s.hi - 8;
            break;
        default:
            printf("ILLEGAL MODE\n");
            func_8001B5E8(0xA);
            break;
        }
        if (obj->colour.w == 0xFFFFFFFF) {
            if (obj->kind >= 0x500 && obj->kind < 0x780) {
                rgb[0] = (D_801FB41C >> 16) & 0xFF;
                rgb[1] = (D_801FB41C >> 8) & 0xFF;
                lit = 1;
                rgb[2] = D_801FB41C & 0xFF;
                goto quad_lit;
            }
        } else {
            rgb[0] = (obj->colour.w >> 16) & 0xFF;
            rgb[1] = (obj->colour.w >> 8) & 0xFF;
            lit = 1;
            rgb[2] = obj->colour.w & 0xFF;
            goto quad_lit;
        }
        lit = 0;
quad_lit:
        if (lit) {
            ft4->code &= ~1;
            ft4->r0 = rgb[0];
            ft4->g0 = rgb[1];
            ft4->b0 = rgb[2];
        } else {
            ft4->code |= 1;
        }
        if (obj->flags & 0x400) {
            ft4->code |= 2;
        } else {
            ft4->code &= ~2;
        }
        u = obj->tex.uv.u;
        v = obj->tex.uv.v;
        w = obj->size.s.lo;
        h = obj->size.s.hi;
        du = ft4->x3 - ft4->x0;
        dv = ft4->y3 - ft4->y0;
        if (du < 0) {
            u--;
            if (u < 0) {
                u = 0;
                w--;
            }
        }
        if (dv < 0) {
            v--;
            if (v < 0) {
                v = 0;
                h--;
            }
        }
        if (u + w >= 0x100) {
            w--;
        }
        if (v + h >= 0x100) {
            h--;
        }
        ft4->u0 = u;
        ft4->v0 = v;
        ft4->u1 = u + w;
        ft4->v1 = v;
        ft4->u2 = u;
        ft4->v2 = v + h;
        ft4->u3 = u + w;
        ft4->v3 = v + h;
        ft4->tpage = tpage;
        ft4->clut = (obj->unk_74 != 0xFFFF) ? D_801C51D4[D_800AFB54[obj->bank] + obj->unk_74]
                                               : D_801C51D4[D_800AFB54[obj->bank] + obj->frame->unk_0C];
        AddPrim(D_801FAC80->ot, ft4);
    }
    if (D_801FAC80->last_tpage != D_801FAC80->tpage) {
        tp = (DR_TPAGE *) D_801FAC80->next_prim;
        if ((u8 *) (tp + 1) >= (u8 *) &D_801FAC80->next_prim) {
            func_8001B5E8(0x14);
        }
        D_801FAC80->next_prim += sizeof(DR_TPAGE);
        SetDrawTPage(tp, 0, 0, D_801FAC80->tpage);
        AddPrim(D_801FAC80->ot, tp);
        D_801FAC80->last_tpage = D_801FAC80->tpage = page = 0xFFFF;
    }
}

void main_run_calls(void) {
    s32 *list;
    s32 *p;
    s32 *q;

    q = (s32 *) D_801E2154;
    D_801FA730 = 0;
    D_801D370C = D_800AA248.unk_38;
    D_800AA248.unk_38 = 0x10;
    D_800AA248.unk_2C = 0x807F;
    D_800AA248.dir = 0x08000800;
    D_800AA248.unk_28.p = q;
    list = q;
    D_800AA248.unk_10 = (s16) D_801F9950;
    if (D_801D8584 != NULL) {
        func_80020704();
    }
    q = D_800AA248.unk_28.p;
    *q++ = 0;
    D_800AA248.unk_34 = &D_801F9A2C;
    D_800AA248.unk_28.p = q;
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

s32 func_80020D20(Npc *npc) {
    s32 v;
    s32 t;

    t = npc->unk_30;
    v = D_800AA248.cur_obj->vel_y.w + t;
    D_800AA248.cur_obj->vel_y.w = v;
    D_800AA248.cur_obj->pos_y.w += v;
    t = npc->unk_34;
    v = D_800AA248.cur_obj->vel_x.w + t;
    D_800AA248.cur_obj->vel_x.w = v;
    t = D_800AA248.cur_obj->pos_x.w + v;
    t &= D_801D8864.w;
    D_800AA248.cur_obj->pos_x.w = t;
    if (npc->unk_4E != 0) {
        return (u8) D_800AA248.cur_obj->unk_6C >> 7;
    }
    if (!(D_800AA248.cur_obj->unk_6C & 0x80)) {
        npc->unk_4E = 1;
    }
    return 1;
}

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
        main_pick_free_aim(npc);
        if (npc->aim != 3) {
            npc->start = main_random_between(7, 0) & 1;
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
            npc->side = side;
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
        npc->side = (npc->side == 1) ? 2 : 1;
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
            if (npc->side != 2) {
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

/* dx is set twice (dx = x; dx -= y), which gives the original's load, subtract and copy; the x = y store is the
 * original's (x is address-taken, so it stays). Each table arm indexes on its own, so the loads come in the
 * original's order. */
void func_80022EC0(Npc *npc) {
    s16 x;
    s16 y;
    s16 dx;
    s16 dy;
    NpcStep *step;
    s32 v;

    main_unwrap_target_x(&x, &y, npc);
    dx = x;
    dx -= y;
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
    x &= 7;
    dy &= 7;
    if (npc->kind == 0x11) {
        step = D_8007B660[dy] + x;
    } else {
        step = D_8007B980[dy] + x;
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

void func_80023064(s32 arg0) {
    D_800AA268.p->pos_y.u.hi = (s16) (D_801F9ACE + arg0);
}

void func_80023080(Npc *npc) {
    func_8002423C(npc);
    D_800AA248.cur_obj->flags &= ~0x10;
    npc->action = 1;
    npc->unk_1C = main_random_between(0xC8, 0x64);
    D_800AA248.cur_obj->pos_y.w = 0x02000000;
    D_800AA248.cur_obj->pos_x.w = 0x02000000;
    npc->state = 0;
    D_800AA248.cur_obj->vel_x.w = 0;
    D_800AA248.cur_obj->vel_y.w = 0;
    npc->unk_30 = 0;
}

/* The camera clamp's shape (func_80053204): c is set again from D_801F9AC8 at the end of the inner block, so cse
 * reloads the camera there through the %hi it still holds. */
u16 func_80023114() {
    s32 x;
    s32 c;
    s32 d;

    x = D_800AA268.p->pos_x.w;
    if (D_800AA268.p->vel_x.w < 0) {
        if (D_801F9AC8.w >= x) {
            x += D_801D8864.w;
        }
        x -= D_801F9AC8.w;
        return x <= 0x480000;
    }
    if (D_800AA268.p->vel_x.w > 0) {
        c = D_801F9AC8.w;
        if (c >= x) {
            d = x - c;
            c = d >= 0 ? d : -d;
            if (c > 0xC7FFFF) {
                x += D_801D8864.w;
            }
            c = D_801F9AC8.w;
        }
        x -= c;
        return (u32) (x + 0xFEA20000) <= 0x01C20000;
    }
    return 0;
}

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
                npc->target_x = (D_801F9ACA + 0xC8) & D_801D8866;
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
            npc->target_x = x - 1;
        } else {
            npc->target_x = x + 0x10;
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
        npc->target_flags = (u16) temp_v1->flags;
        if (temp_v1->flags & 0x10) {
            var_v0 = temp_v1->pos_x.u.hi - 1;
        } else {
            var_v0 = temp_v1->pos_x.u.hi + 0x10;
        }
        npc->target_x = var_v0;
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
    if (npc->target_flags & 0x10) {
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
    if (npc->side == 1) {
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
        if (npc->side != 1) {
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
            npc->side = 1;
            if (npc->kind == 0x11) {
                func_8003EB5C(&D_80097850, D_800AA268.p);
            } else {
                func_8003EB5C(&D_8008B458, D_800AA268.p);
            }
        } else {
            npc->side = 2;
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

u16 main_pick_free_aim(Npc *npc) {
    s16 used;
    s16 k;
    s32 bit;
    s16 sel;

    if (D_801E289A == 0) {
        used = D_801E2A50 & 7;
        if (used == 7) {
            used = 0;
        }
        k = main_random_between(0x1F, 0) & 3;
        if (k == 3) {
            k = 0;
        }
        for (;;) {
            sel = k;
            if (used & D_8007BA20[k]) {
                if (++k >= 3) {
                    k = 0;
                }
                continue;
            }
            break;
        }
        npc->aim = k;
        if (sel == 0) {
            bit = 1;
        } else if (sel == 1) {
            bit = 2;
        } else {
            bit = 4;
        }
        used |= bit;
        D_801E2A50 = used;
        return k;
    }
    npc->aim = 3;
    return 3;
}

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

s32 abs(s32); /* GCC's builtin: inlined */

/* x is set from pos_x, then reused for the distance, so cse forgets the field and the last branch reloads it. */
void func_800242D8(Npc *npc) {
    GameObject *obj;
    s16 dx;
    s16 x;

    obj = D_800AA268.p;
    x = obj->pos_x.s.hi;
    dx = x - D_801F9ACA;
    x = dx;
    if (abs(dx) >= 0x2BC) {
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

s16 func_8002439C(Npc *npc) {
    s16 x;
    s16 mx;

    x = npc->target_x;
    if (x < D_801F9ACA) {
        x += D_801D8866;
    }
    mx = D_800AA268.p->pos_x.s.hi;
    if (mx < D_801F9ACA) {
        mx += D_801D8866;
    }
    return abs((s16) (mx - x)) < 0x60;
}

void main_unwrap_target_x(s16 *px, s16 *pcur, Npc *npc) {
    s32 x;
    s16 cur;
    s32 width;
    s16 d;
    s32 w;

    x = (u16) npc->target_x;
    cur = D_800AA268.p->pos_x.s.hi;
    width = D_801D8866;
    w = (s16) width;
    d = abs(npc->target_x - cur);
    if (d >= w >> 1) {
        d = abs(D_801F9ACA - cur);
        if (d >= w >> 1) {
            x += width;
        } else {
            cur += width;
        }
    }
    *px = x;
    *pcur = cur;
}

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
/* 97.61%: 97.6 %: the order and the operations match (abs() is GCC's builtin; d reused in the left branch). Only d
 * and width swap registers (a0/v1): with d = size << 16; d -= 1, d is set twice, so local-alloc does not tie the lh
 * temporary to it (lh v0, as the original) and sched2 places the load as the original, but nothing local holds v1,
 * so the 0x3FFFFFF constant takes v1, width prefers it and d gets a0. Writing (size << 16) - 1 makes the shift a
 * block-local in v1 (the constant then takes a0 and d v1, as the original) but local-alloc ties the lh temporary to
 * it (lh v1; sll v1,v1) and sched2 moves the load down (99.76 % with -fno-schedule-insns2). The original has both:
 * the lh in v0 and the shift in a v1 local not tied to it */
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
            d = abs(d);
            if (x >= d) {
                x = x - (width + 1);
            }
        }
    } else {
        x += left;
        if (x < 0) {
            d = obj->size.s.lo << 16;
            d += x;
            if (d <= 0) {
                x = x + (1 + (D_801D8864.w & 0x3FFFFFF));
            }
        }
    }
    obj->pos_x.w = x;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/main", main_wrap_layer_x);
#endif

void main_scroll_layers(void) {
    GameObject *obj;
    GameObject *head;

    if (D_801D3D8A != 0) {
        head = &D_801E29A8;
        for (obj = head->next; obj != head; obj = obj->next) {
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
            rec->unk_01C = main_random_between(0x1E, 0) % 2 + 1;
            rec->unk_034 = 1;
            rec->unk_036 = 1;
            rec->unk_02A = 1;
            main_create_building_items(rec);
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
/* 94.13%: 94.1 %: the structure matches (two compares against D_80011BA4 whose bodies flow deletes, the parts
 * through a BuildingPart pointer so loop.c reduces only the +4/+8 givs, count kept apart from i). Left: global-
 * alloc puts y in s3 and rec in s4 (y 9 refs/61 live, 0.44, above rec 24/222, 0.43; the original's y life is about
 * 63, statement orders trade it against req's); cse2 merges the memset's %hi(D_801F9948) with the copy loop.c
 * hoists, and that pseudo takes s7 where the original rematerializes it; the division's p takes v1 and its sign
 * shift is scheduled before the mfhi (the original a1, after) */
extern u8 D_80011BA4[];
extern u8 D_80011BA4_alt[];
extern s16 D_8007A686;
extern s32 D_800AA25C;
void func_80025474(Building *b);

void main_create_building_items(Building *rec) {
    ObjectDef *req;
    BuildingItem *item;
    GameObject *obj;
    SpriteFrame *frame;
    BuildingDef *def;
    BuildingPart *part;
    s32 *ids;
    s32 id;
    s16 i;
    s16 y;
    u16 prio;
    u16 count;
    s32 n;
    s32 kind;

    req = func_8001D110();
    item = rec->items;
    req->unk_0C = 0x710;
    i = 1;
    y = rec->bottom;
    req->pos_x.s.hi = rec->left;
    prio = rec->priority;
    def = rec->def;
    y -= 0x1D;
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
            /* The bodies only set frame, which the next pass overwrites: cse keeps them (frame's use comes
             * earlier in the loop), flow deletes them, and jump2 then leaves the first compare and the
             * second one's address load, as in the original */
            if (rec->def == (BuildingDef *) D_80011BA4) {
                frame = (SpriteFrame *) 0;
            } else if (rec->def == (BuildingDef *) D_80011BA4_alt) {
                frame = (SpriteFrame *) 0;
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
            part = &item->unk_0C;
            part->unk_04 = 1;
            part = &item->unk_24;
            part->unk_04 = 2;
            part++;
            part->unk_04 = 3;
            item++;
            ids++;
            id = *ids;
            i++;
        } while (id != 0);
    }
    item--;
    rec->unk_070 = item;
    obj = item->obj;
    i--; /* count = i - 1 would let cse fold the later count - 1 into i - 2 */
    count = i;
    rec->top = obj->pos_y.u.hi + obj->size.u.hi - 0xC;
    rec->state = 0;
    rec->unk_000 = count;
    func_80025BBC(rec);
    func_8002546C(rec);
    func_800252CC(rec);
    count--;
    n = ((s16) count - 1) * 3;
    kind = rec->kind;
    D_800AA25C = kind;
    rec->unk_012 = ((kind * n + 2) * (D_8007A686 << 16)) / 100 >> 16;
    if (rec->unk_018 != NULL) {
        func_80025474(rec);
    }
}
#else
INCLUDE_ASM("asm/main/nonmatchings/main", main_create_building_items);
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
/* 99.89%: 99.9 %: only the loop counter's register differs (v1, the original a1). The size goes through its own
 * variable so that expand_binop keeps (pos + size) with the size loaded first (no swap: the target is not the
 * second operand), which frees a1 for last; n > last orders the shifts; blk->unk_00 is stored after unk_1E. The
 * counter (5 refs, live 8) is global-alloc's first pseudo and takes the first free register, v1; the original's
 * counter shares last's a1, as if allocated after last (counter forms, types and reuses of last or n tried) */
void func_80025474(Building *b) {
    BuildingBlock *blk;
    ObjectDef *def;
    GameObject *obj;
    GameObject *top;
    s16 n;
    s16 last;
    s16 k;
    s32 y;
    s32 sz;
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
        sz = top->size.u.hi;
        y = top->pos_y.u.hi + sz;
        if (n < 2) {
            n = 2;
        }
        if (n > last) {
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
        blk->unk_1E = h + obj->size.u.hi;
        blk->unk_00 = obj;
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

extern u16 D_801D3700;
extern u16 D_801E0D70;
extern u16 D_801D3754;
extern u16 D_801D873C;
extern s16 D_801FA980;
extern s16 D_801E1C88;
extern s16 D_801FB46C;
extern s16 D_801FB468;
extern u8 D_801FA8A6;
extern s32 D_801FA7D8;
extern u8 *D_8007F8E0[];
extern u8 *D_8007A69C[];
extern TextMessage D_800888DC;
extern TextMessage D_80088908;
extern TextMessage D_8008892C;
extern TextMessage D_8008894C;
extern TextMessage D_80088970;
extern TextMessage D_80088990;
void func_800268BC(void);
void main_scroll_layers(void);
void main_count_monsters(void);
s32 func_8005E4E4(void);
void func_80053DE4(Monster *);
void func_80027FD0(Monster *, u16);
s32 func_8003F378(Monster *);
void monster_dispatch_action(Monster *, GameObject *, u16);
void func_800267CC(Monster *);
u16 func_800291DC(Monster *, GameObject *);
void func_80026C04(Monster *);
void main_move_monster(Monster *);
void func_8002987C(Monster *);
void main_update_boxes(Monster *);
void main_update_screen_pos(Monster *);
void main_update_priority(Monster *);
void func_80055CA8(Monster *);
void func_80029984(Monster *);
void main_reset_screen_pos(u16, Monster *);
void bonus_update_score(Monster *);
void bonus_update_lives(Monster *);
void bonus_update_icons(Monster *);
void func_80027AB0(void);
void func_800297B4(void);
void main_update_camera(void);
void building_update_all(void);
void func_800636B0(void);
void cdload_sort_players(void);
s32 func_8001D878(void);
void func_80029170(void);
void func_8003D6C4(void);
void func_8003C130(void);
void func_80036298(void);
void pickup_update_all(void);
void func_8003EBC0(void);
void func_80043F84(void);
void func_8004AC84(void);
void func_8004B038(void);
void func_800299C4(void);
void func_8002A354(s32);

void main_update_monsters(void) {
    char text[40];
    u8 *name;
    Monster *m;
    u16 t;
    GameObject *obj;
    u16 i;

    func_8002994C();
    D_801D3700 = 0;
    D_801E0D70 = 0;
    D_801D3754 = 0;
    D_801D873C = 0;
    D_801D8744++;
    func_800268BC();
    func_80026A6C();
    if (D_801D3D8A != 0) {
        main_scroll_layers();
    }
    main_count_monsters();
    i = 7;
    do {
        m = &D_801E0B78[i];
        obj = D_800AA268.p = m->obj;
        if (m->id != 0 && obj != NULL) {
            func_80029CF8();
            m->body_priority = obj->priority;
            if (m->unk_058 & 1) {
                if (D_801FB18C != 0) {
                    m->dir = 0;
                    m->buttons = 0;
                } else if ((func_8005E4E4() & 2) && D_801FB46C == 0) {
                    if (&D_801E0B78[func_80025DF8(D_8007BD78.turn_player)] == m && D_801D8740 != D_801E28C8
                        && !(D_8007BD78.flags & 0x200)) {
                        func_80053DE4(m);
                        func_80027FD0(m, i);
                    } else {
                        m->dir = 0;
                        m->buttons = 0;
                    }
                } else if (D_800AA2DC == 0 || D_801FB46C == 0) {
                    func_80053DE4(m);
                    func_80027FD0(m, i);
                } else {
                    m->dir = 0;
                    m->buttons = 0;
                }
                func_8003F378(m);
                func_80026BC4(m);
                monster_dispatch_action(m, obj, i);
                func_800267CC(m);
                main_apply_health(m);
                if (D_800AA2DC == 0 && func_800291DC(m, obj) == 1) {
                    goto reset;
                }
                if (m->action != 0x37 && m->action != 0x26) {
                    m->play_frames++;
                }
                func_80026C04(m);
                main_move_monster(m);
            }
            if (m->action != 0x1F) {
                func_8002987C(m);
                main_update_boxes(m);
                main_update_screen_pos(m);
                main_update_priority(m);
                func_80055CA8(m);
                func_80029984(m);
            }
        } else {
        reset:
            main_reset_screen_pos(i, m);
        }
        func_80029C6C(m);
        bonus_update_score(m);
        bonus_update_lives(m);
        bonus_update_icons(m);
        if ((m->action == 0x26 || m->action == 0x37) && m->unk_1CC != 4) {
            D_801D3700 = 1;
        }
    } while (--i != 0);
    func_80027AB0();
    main_count_monsters();
    func_800297B4();
    main_update_camera();
    if (D_801FA980 == 0) {
        D_801FA980 = 1;
        building_update_all();
    } else {
        if (D_800AA2DC != 0) {
            if (D_801FA890 != 0) {
                D_801FB18C = 2;
                m = &D_801E0B78[func_80025DF8(D_801FB468)];
                if (D_801FA890 == 0x1E0) {
                    D_801E0D70 = D_801FB468;
                }
                if ((u16) (m->climb_side - 1) < 2) {
                    m->pressed |= 4;
                    func_80026F98(m);
                }
                func_800636B0();
                if (--D_801FA890 == 0) {
                    D_801E1E40 = 0;
                }
            }
        } else if (D_801D873C == 0) {
            cdload_sort_players();
            main_count_monsters();
            if (D_801E1CB0 == 0) {
                if (D_801FA890 != 0 && D_801D8740 != 0) {
                    if (D_801FA890 == 0x78) {
                        D_801E0D70 = 1;
                    }
                    if (D_801E1C88 == 0) {
                        if (D_801F9944 > 0) {
                            D_801F9944--;
                        } else if (func_8001D878() != 0) {
                            D_801E1C88 = -1;
                        }
                    }
                    if ((D_801FA890 += D_801E1C88) == 0) {
                        D_801E1E40 = 0;
                    }
                    func_800636B0();
                } else if (D_801D8740 == 0) {
                    t = D_801D36F8;
                    if (t == 0) {
                        D_801D3754 = 1;
                        t = 0x1E0;
                    }
                    D_801D36F8 = t - 1;
                    if (D_801D36F8 == 0) {
                        D_801E0D4C = 1;
                    }
                }
            }
        }
        func_80029170();
        building_update_all();
        func_8003D6C4();
        func_8003C130();
        func_80036298();
        pickup_update_all();
        func_8003EBC0();
        func_80043F84();
        func_8004AC84();
        func_8004B038();
        func_8001D1C0();
        func_800299C4();
    }
    if (D_801E0D70 != 0) {
        func_800636B0();
        if (D_800AA2DC != 0 && D_801E0D70 != 0) {
            D_8007BD78.flags |= 0x8000;
            return;
        }
        D_801FB18C = 2;
        switch (D_801FA960) {
        case 24:
        case 49:
        case 74:
        case 99:
            if (D_801E289C == 6 && D_801FA8A6 != 0) {
                name = "??????";
            } else {
                name = D_8007F8E0[D_801E289C];
            }
            func_8001F61C(name, 200, 100, 1, 0x45, D_8007AD4C, 0, 0x400);
            func_8001F61C("HAS BEEN FREED!", 200, 125, 1, 0x45, D_8007AD4C, 0, 0x400);
            if (D_801E289C >= 3) {
                D_801E1C88 = 0;
                D_801F9944 = 30;
                if (D_801E289C == 6 && D_801FA8A6 != 0) {
                    sprintf(text, "PASSWORD: %s", D_8007A69C[4]);
                } else {
                    sprintf(text, "PASSWORD: %s", D_8007A69C[D_801E289C - 3]);
                }
                func_8001F61C(text, 200, 150, 1, 0x45, D_8007AD4C, 0, 0x400);
                func_8001F61C("PRESS ANY BUTTON", 200, 175, 1, 0x47, D_8007AD4C, 0, 0x400);
            }
            switch (D_801FA960 / 25) {
            case 0:
                D_801FA984[1] = 1;
                break;
            case 1:
                D_801FA984[2] = 1;
                break;
            case 2:
                D_801FA984[0] = 1;
                break;
            }
            if (D_801FA984[0] == 0 || D_801FA984[1] == 0 || D_801FA984[2] == 0) {
                D_801CA464 |= 2;
            }
            break;
        default:
            D_800AA2EC = 0x47;
            func_8002A354(0);
            if (D_801FA7D8 == 0x64) {
                func_8001ED54(&D_8008892C);
                func_8001ED54(&D_80088908);
            } else {
                func_8001ED54(&D_8008894C);
                func_8001ED54(&D_800888DC);
            }
            break;
        }
    } else if (D_801D3754 != 0) {
        func_800636B0();
        D_800AA2EC = 0x47;
        func_8001ED54(&D_80088970);
        func_8001ED54(&D_80088990);
    }
}

void func_800267CC(Monster *monster) {
    s32 i;

    i = 0;
    if (monster->id == 5 && monster->meter.w == 0x440000 && !(monster->extra_uses & 0xF)) {
        monster->extra_uses |= 3;
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
    m1->depth = r1;
    m2->depth = r2;
    m3->depth = r3;
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

    if ((arg0->pressed & 2) && !(func_80027348() & 0xFFFF) && !(func_80026D54(arg0) & 0xFFFF)) {
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
    if (state != 2 && state != 0x4E && state != 0x11 && monster->prev_action == 0x16) {
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
    arg0->prev_action = temp_v0;
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
    if ((m->pressed & 1) && func_800272B0(m) == 0) {
        if (m->action == 2) {
            if (m->unk_104 == 0 || D_800AA268.p->vel_y.w == 0) {
                return;
            }
        } else if (m->action == 0x53) {
            m->action = 0x54;
            return;
        } else if (m->action == 0x2C && m->unk_104 != 0 && D_800AA268.p->vel_y.w != 0) {
            m->prev_action = 2;
            func_80026F58(m);
            return;
        }
        m->prev_action = m->action;
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

/* func_800272FC takes the monster: the caller passes it, and the move into a0 (already holding it) is deleted only
 * after reload. Until then a0 is set twice, so sched1 does not lift the later call's argument move. */
void func_80026F98(Monster *m) {
    u16 action;

    D_800AA268.p = m->obj;
    if ((m->pressed & 4) && !(func_800272FC(m) & 0xFFFF)) {
        action = m->action;
        if (action == 0x53) {
            m->action = 0x54;
        } else {
            m->unk_152 = (u16) (action - 5) < 2;
            m->action = 2;
            func_800580F8(m);
            if (m->unk_18E == 0) {
                m->action = 0x4E;
            }
            m->climb_side = 0;
        }
    }
}

extern s16 D_80084278;

void main_use_full_meter(Monster *m) {
    u16 action;
    s16 n;

    if ((m->pressed & 8) && (D_800AA2DC == 0 || (D_800AA2DC & 0x7000)) && m->meter.w == 0x440000) {
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
                    m->prev_action = m->action;
                    m->action = 0x63;
                } else if (action == 2 || action == 0x19) {
                    if (m->obj->vel_y.s.hi != 0) {
                        m->prev_action = action;
                        m->action = 0x63;
                    }
                }
                if (m->action == 0x63) {
                    if ((m->extra_uses & 0xF) != 0) {
                        n = (m->extra_uses & 0xF) - 1;
                        m->extra_uses &= 0xFFF0;
                        m->extra_uses |= n;
                        if (n < 3 && m->extra[n + 2] != NULL) {
                            func_8001E4B0(m->extra[n + 2]);
                            m->extra[n + 2] = NULL;
                        }
                        if (!(m->extra_uses & 0xF)) {
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
        main_update_input(&D_801E0B78[func_80025DF8(i)], i & 0xFFFF);
    } while (i < 3);
}

/* Reads a monster's pad (or its demo script when the demo runs): buttons and direction, with their change
 * handlers. One variable holds the new buttons, then the previous direction. */
void main_update_input(Monster *monster, s32 arg1) {
    s16 *script;
    u16 buttons;
    u16 held;
    u16 dir;
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
                buttons = monster->dir;
                monster->dir = dir;
                func_80028140(buttons, monster, dir);
                func_80028140(buttons, monster, dir);
                if (dir != 0) {
                    monster->last_dir = dir;
                }
                if (buttons == dir) {
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
    buttons = monster->dir;
    monster->dir = dir;
    func_80028140(buttons, monster, dir);
    if (dir != 0) {
        monster->last_dir = dir;
    }
    if (buttons == dir) {
        monster->dir_frames++;
    } else {
        monster->dir_frames = 0;
    }
}

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
        m->screen_y = 0x12C0000;
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
    m->screen_x.w = pos;
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
    m->screen_y = pos;
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
        monster->screen_y = 0;
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
                n = m->depth + 9;
                obj->priority = b->priority - n;
            }
        }
        return;
    }
    if ((action == 2 || action == 0x4E) && m->skip_building != 0 && obj->vel_y.w <= 0) {
        return;
    }
    if (m->climb_side == 0) {
        prio = m->depth + 0x1000;
    } else {
        if (m->climb_building == 0) {
            return;
        }
        b = monster_get_building(m->climb_building);
        if (b == NULL) {
            return;
        }
        top = b->priority;
        n = m->depth;
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

void func_80027FD0(Monster *m, u16 index) {
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
    } else if (m->action == 2 || m->action == 0x4E || m->prev_action == 2 || m->prev_action == 0x4E) {
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
    monster->pressed = pressed;
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
    D_801D3D64.scroll_vx = 0;
    D_801F9A30.unk_0 = 0;
    D_801D3D64.scroll_state = 0;
    D_801F9ACC.w = 0;
}

extern s32 D_8007BD7C;
extern s32 D_801D3D90;
extern s16 D_801FA724;
extern s16 D_801FA728;
extern s16 D_801FA9A8;
void main_find_camera_pair(void);
void func_800288B0(s32 *vel2, s32 *vel1);
void main_track_player(s32, s32);

void main_update_camera(void) {
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
        main_track_player(flags, D_8007BD7C);
        return;
    }
    main_find_camera_pair();
    func_800288B0(&vel2, &vel1);
    x = D_801FA9A8;
    speed = scroll->scroll_vx << 16;
    if (speed != 0) {
        if (speed > 0) {
            if (vel1 >= vel2) {
                d = vel1;
            } else {
                d = vel2;
            }
            if (x >= 0xD3) {
                d += 0x10000;
                if (d < speed) {
                    d = speed;
                }
            } else if (x >= 0xBF) {
                goto clamp_right;
            } else {
                scroll->scroll_vx = 0;
                scroll->unk_2C = 0;
                goto done;
            }
        } else {
            if (vel1 <= vel2) {
                d = vel1;
            } else {
                d = vel2;
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
            if (vel1 >= vel2) {
                d = vel1;
            } else {
                d = vel2;
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
            if (vel1 <= vel2) {
                d = vel1;
            } else {
                d = vel2;
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
            scroll->scroll_vx = 0;
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
    D_801D3D64.max_y = max;
    D_801D3D64.min_y = min;
    if (D_801D3D64.scroll_state == 0) {
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
    } else if (D_801D3D64.scroll_state == 1) {
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
    } else if (D_801D3D64.scroll_state == 2) {
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
/* 96.69%: 96.7 %: each case's load of m1->obj sits before the second call's li a0. In the original, reorg put li
 * a0,2 in case 1's jump delay slot and the tails cross-jump from the lw, so sched1 had placed the li before the lw
 * in each case. Both are ready together, of equal priority, and sched1 breaks the tie by RTL order (the arg move is
 * emitted right before the call, after the lw), unless the lw sets a once-set live pseudo (birthing_insn_p: top
 * priority, placed last), which o1, set in each case and by the NULL fix-up, is not. Moving the second call after
 * the switch (a per-case player index) gives the li/lw order but loses the D_801E0B78 base held in s0 across the
 * join, which only the per-case tails cross-jumped after allocation give. x1/x2 then get a3/a2 instead of t1/t0 */
extern s16 D_801D8844;
s16 main_get_midpoint(s32, s32);

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
            result = main_get_midpoint((s16) x2, (s16) x1);
        }
    }
    D_801FA9A8 = result;
}
#else
INCLUDE_ASM("asm/main/nonmatchings/main", func_800288B0);
#endif

s16 main_get_midpoint(s32 a, s32 b) {
    s16 mid = 0; /* never read: set before the blocks, it becomes cse's canonical copy of hi (the move v0) */
    s16 lo;
    s16 hi;

    lo = a;
    hi = b;
    if ((s16) b <= (s16) a) {
        lo = b;
        hi = a;
    }
    mid = hi;
    return mid - ((s16) (mid - lo) >> 1);
}

extern s16 D_801D8844;
extern s16 D_801E1E24[8];
s16 main_get_midpoint(s32, s32);
s32 abs(s32);

/* The camera's two tracked monsters: for each pair of the three players' monsters in play, their x distance and
 * midpoint (D_801E1E24[0..2], [4..6]; a lone monster's x in [4..7]); D_801D8844 picks the farthest (1..4). */
void main_find_camera_pair(void) {
    Monster *m;
    Monster *other;
    s16 xa;
    s16 xb;
    s16 mid;
    s16 k;
    u16 i;
    s16 *dist;
    s16 *mids;
    s16 cam;
    s16 left;
    s16 width;
    s16 cam2;
    s16 left2;
    s16 width2;

    width = D_801D8866 + 1;
    left = D_801D8866 - 399;
    left2 = D_801D8866 - 399;
    width2 = D_801D8866 + 1;
    dist = D_801E1E24;
    for (i = 0; i < 8; i++) {
        *dist++ = 0;
    }
    cam = D_801F9ACA;
    m = &D_801E0B78[func_80025DF8(1)];
    cam2 = cam;
    if ((m->unk_058 & 1) && m->action != 0x37 && m->action != 0x26) {
        xa = m->obj->pos_x.s.hi;
        if (cam >= left && xa < left) {
            xa += width;
        }
        xa += cam;
        other = &D_801E0B78[func_80025DF8(2)];
        if (other->action == 0x37 || other->action == 0x26 || (u16) other->unk_1C8 != 0 || !(other->unk_058 & 1)) {
            D_801E1E24[4] = xa;
        } else {
            xb = other->obj->pos_x.s.hi;
            if (cam2 >= left2 && xb < left2) {
                xb += width2;
            }
            xb += cam2;
            mid = main_get_midpoint(xb, xa);
            xa = abs(xa);
            xb = abs(xb);
            xb = abs(xb - xa);
            D_801E1E24[4] = mid;
            D_801E1E24[0] = xb;
        }
        other = &D_801E0B78[func_80025DF8(3)];
        if (other->action == 0x37 || other->action == 0x26 || (u16) other->unk_1C8 != 0 || !(other->unk_058 & 1)) {
            D_801E1E24[5] = xa;
        } else {
            xb = other->obj->pos_x.s.hi;
            if (cam2 >= left2 && xb < left2) {
                xb += width2;
            }
            xb += cam2;
            mid = main_get_midpoint(xb, xa);
            xa = abs(xa);
            xb = abs(xb);
            xb = abs(xb - xa);
            D_801E1E24[5] = mid;
            D_801E1E24[1] = xb;
        }
    }
    m = &D_801E0B78[func_80025DF8(2)];
    if ((m->unk_058 & 1) && m->action != 0x37 && m->action != 0x26 && (u16) m->unk_1C8 == 0) {
        xa = m->obj->pos_x.s.hi;
        if (cam >= left && xa < left) {
            xa += width;
        }
        xa += cam;
        other = &D_801E0B78[func_80025DF8(3)];
        if (other->action == 0x37 || other->action == 0x26 || (u16) other->unk_1C8 != 0 || !(other->unk_058 & 1)) {
            D_801E1E24[6] = xa;
        } else {
            xb = other->obj->pos_x.s.hi;
            if (cam2 >= left2 && xb < left2) {
                xb += width2;
            }
            xb += cam2;
            mid = main_get_midpoint(xb, xa);
            xa = abs(xa);
            xb = abs(xb);
            xb = abs(xb - xa);
            D_801E1E24[6] = mid;
            D_801E1E24[2] = xb;
        }
    } else {
        m = &D_801E0B78[func_80025DF8(3)];
        if ((m->unk_058 & 1) && m->action != 0x37 && m->action != 0x26 && D_801D8740 == 1) {
            xa = m->obj->pos_x.s.hi;
            if (cam >= left && xa < left) {
                xa += width;
            }
            xa += cam;
            D_801E1E24[7] = xa;
        }
    }
    /* cam, left and width serve again: a distance, its midpoint, the largest distance */
    D_800AA248.unk_00 = 4;
    dist = D_801E1E24;
    mids = D_801E1E24 + 4;
    width = -1;
    do {
        left = *dist++;
        cam = *mids++;
        if (left >= width && cam != 0) {
            width = left;
            cam = D_800AA248.unk_00;
            k = cam - 4;
            D_801D8844 = abs(k) + 1;
        }
    } while (--D_800AA248.unk_00 != 0);
}

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
/* 95.77%: 95.8 %: the original keeps 0x37 from the first compare in a2 and stores it (m->action = 0x37) where the C
 * loads it again (cse's path is longer here). Its two range tests (action - 9 < 6, action - 0x34 < 2) keep an andi
 * that combine folds here: a u16 d = action - 9 set before the 0x34/0x35 test (another block) keeps the first andi
 * and gives the original's size (94.8 % by objdiff, registers then differ); the end test's andi folds in every
 * placement tried (a u16 temporary, a reread of m->action, & 0xFFFF with an unsigned compare) */
u16 func_800291DC(Monster *m, GameObject *obj) {
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
                    action = m->action;
                    if (action == 0x34 || action == 0x35) {
                        m->action = 0x26;
                    } else if ((u16) (action - 9) < 6) {
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
    m->play_frames = 0;
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
    } else if ((u16) (action - 0x34) < 2) {
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
            if (arg0->body_priority != sprite->priority) {
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

void func_8005E214(void);

void main_track_player(s32 mode, s32 player) {
    Monster *m;
    s32 bonus;
    u16 boost;
    u16 camx;
    u16 camy;
    u16 sx;
    u16 oy;
    u16 right;
    u16 edge;
    u16 dx;
    s16 dy;
    u16 x;
    s32 flags;
    u16 cam;
    s32 top;

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
        sx = m->obj->pos_x.u.hi;
        edge = right;
        x = sx;
        oy = m->obj->pos_y.u.hi;
        if ((s16) D_801D8866 < (s16) right) {
            edge = right - D_801D8866;
        }
        if ((s16) sx > (s16) camx && (s16) sx < (s16) edge) {
            x = sx - camx;
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
            D_8007BD78.flags |= 4;
            dy = camy - 0x6E;
            dy = oy - dy;
            if (dy < -4) {
                dy = -4;
            } else if (dy == 0) {
                D_8007BD78.flags &= ~4;
            }
        } else if ((s16) oy - (top = (s16) camy - 0x32) > 0) { /* FAKE: top keeps camy - 0x32 a value of its own:
            * inline, fold reassociates oy - (camy - 0x32) into (oy + 0x32) - camy; a statement before the test
            * computes it in another block */
            dy = camy - 0x32;
            dy = oy - dy;
            if (dy >= 5) {
                dy = 4;
            }
            if (dy > -(s16) camy) {
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
            if (m->obj->vel_x.s.hi == 0) {
                D_8007BD78.flags &= ~3;
            }
        }
    }
    if (bonus == 1 && (s16) dx < 0) {
        dx = 0;
    }
    cam = D_801F9AC8.u.hi + dx;
    D_801F9AC8.u.hi = cam;
    D_801F9ACC.u.hi += dy;
    if ((s16) D_801D8866 < (s16) cam) {
        D_801F9AC8.s.hi = cam - D_801D8866;
    } else if ((s16) cam < 0) {
        D_801F9AC8.s.hi = cam + D_801D8866;
    }
    if (D_801F9ACC.s.hi > 0) {
        D_801F9ACC.s.hi = 0;
    }
    if (D_801F9AC8.s.hi >= 0x667) {
        D_801F9AC8.s.hi = 0x666;
    }
}

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
