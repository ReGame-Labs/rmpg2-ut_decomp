#ifndef PICKUP_H
#define PICKUP_H

#include "common.h"
#include "building.h"   /* the declarations building shares with it */
#include "monster_anim.h"   /* the records of D_801FA9BC */

/* Declarations of src/main/pickup.c: provisional types from the code's own use; refined as functions match. */



extern s16 D_801F9980;
extern s16 D_801F9984;
extern s16 D_801F9988;
extern s32 D_801FA72C;

void func_8001E4B0(GameObject *);
void func_8001F724(u16);
void func_8004CFC0(void);
void func_8005DD48(Monster *);

void func_80029D1C(void);
/* The handlers of the D_801FA9BC records by kind (pickup_update): building.c and npc.c. */
void building_update_pickup(Pickup *r);
void func_80034B94(Pickup *r);
void func_800350C0(Pickup *r);
void func_8003537C(Pickup *r);
void func_8003566C(Pickup *r);
void func_80035C4C(Pickup *r);

void pickup_update_all(void);
void pickup_update(Pickup *);
void pickup_clear_all(void);
void pickup_clear(Pickup *);
void func_8003C130(void);
void func_8003C344(void);
void func_8003C080(void);
void func_8003C0AC(void);
void func_8003C0C8(void);
void func_8003C0E0(void);
void func_8003BD48(Pickup *);
void func_8003BF34(GameObject *, Pickup *, u16);   /* the third argument is not used */
extern u8 D_8008A494[];
extern u8 D_8008A4A0[];
extern u8 D_8008A4B8[];
extern u8 D_8008A4C4[];
void func_8003C1C0(u16, UnkStructB2 *);
void func_8003C674();                  /* empty; func_8003C3B0 passes it two arguments */
BuildingPart *func_8003C67C(Building *u, UnkStructB2 *rec);
void func_8003CE24(BuildingPart *p, ObjectDef *def, UnkStructB2 *rec, s32 arg3);
void func_8003C894(void **arg0);
void func_8003C8D4(Pickup *arg0);
void func_8003C934(Pickup *);
void func_8003C9E8(Pickup *arg0);
typedef struct UnkStructB4 {  /* provisional: 8-byte records of D_8007DDD4 (an animation and a value per step) */
    void *unk_00;
    u16 unk_04;
} UnkStructB4;
extern UnkStructB4 D_8007DDD4[];
extern void (*D_8007DDB4[8])(void);
s32 pickup_test_touch(GameObject *, Monster *);
void func_8003CA28(Pickup *arg0);
void func_8003CA70(Pickup *);
void func_8003CADC(Monster *arg0);
void func_8003CB30(Monster *arg0);
void func_8003CCA8(void);
void func_8003CCC0(void *);
void func_8003CB68(s16, Monster *);
void func_8003CEA0(Anim *, GameObject *);
extern s32 D_800830BC[];
u16 func_8003C858(BuildingPart *, s32, s32);
u16 func_8003CC84(BuildingPart *, s32);
void func_8003C2D4(u16, UnkStructB2 *);
/* The handlers of the D_801D3824 records by kind (func_8003C1C0), in actor.c. */
void func_8003D03C(UnkStructB2 *rec);
void func_8003D0D4(UnkStructB2 *rec);
void func_8003D11C(UnkStructB2 *rec);
void func_8003D228(UnkStructB2 *rec);
void func_8003D30C(UnkStructB2 *rec);
void func_8003D3CC(UnkStructB2 *rec);
void func_8003D5C8(void);

#endif /* PICKUP_H */
