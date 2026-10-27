#ifndef BONUS_H
#define BONUS_H

/* The declarations of src/main/bonus.c: its own functions and what it calls and reads elsewhere. */

#include "game.h"

s32 func_8001A3AC(void);
void func_8001BB68(GameObject *);
void func_8001BB88(GameObject *);
ObjectDef *func_8001D110(void);
GameObject *func_8001DCB4(void);
void func_8001E4B0(GameObject *);
void main_free_kind(s32);
GameObject *main_create_box(s32, s32, s32, s32, s32);
void func_8001ED54(TextMessage *);
void func_8001EE24(void);
void func_8001F724(u16);
void main_set_frame(s32, u16, GameObject *);
s32 func_80025DF8(s32);
s32 cdload_get_next_player(s32);
s32 func_80031714(Monster *);
void func_8005E124(Monster *, s32);
void func_8005E19C(Monster *, s32);
void func_8005E2D8(void);
void bonus_start_round(void);
void func_8005F12C(void);
void bonus_create_counter(s32, s32);
void bonus_save_health(void);
void bonus_give_awards(s32, s32);
void bonus_award_places(void);
void bonus_restore_health(void);
void func_8006036C(s32 *, s32, s32, s32, s32, u8 *);
void func_800603FC(s32 *, s32, s32, s32, s32);
void func_80060A7C(s32, u32, s32);
void func_80060BA8(void);
void func_80060D44(Monster *);
void func_80062E44(void);
void func_800636B0(void);

extern Anim D_80016A84;
extern s32 D_8007BD7C;
extern s32 D_8007BD8C;                  /* D_8007BD78.round_timer by its own name */
extern s32 D_80084314[];                /* the finishing animations, by place */
extern s32 D_80084328[];                /* the race's place boundaries (x) */
extern u32 D_8008433C[];                /* the score round's place boundaries */
extern s32 D_80084304[];                /* the slot icons' animations, by Monster.icon_kind */
extern s32 D_80084298[];                /* the lives counter's animations, by monster id - 1 */
extern s32 D_8008427C[];                /* the portrait animations, by monster id - 1 */
extern s32 D_800842B4[];
extern s32 D_800842DC[];
extern TextMessage D_80089604;
extern TextMessage D_80089624;
extern TextMessage D_80089644;
extern u8 D_80089678[];
extern u8 D_8008969C[];
extern u8 D_800896C0[];
extern u16 D_801FB464;
extern s16 D_801FB468;
extern s16 D_801FB46C;
extern TextMessage D_801FB470;           /* the message func_8006036C builds */
extern s32 D_8007ABCC[];                /* a font's glyphs */
extern s32 D_801FB474;                   /* D_801FB470.spacing */

#endif /* BONUS_H */
