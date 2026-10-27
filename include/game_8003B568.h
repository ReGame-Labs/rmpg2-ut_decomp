#ifndef GAME_8003B568_H
#define GAME_8003B568_H

#include "common.h"
#include "game_8002A330.h"   /* the declarations game_8002A330 shares with it */
#include "game_80057C94.h"   /* the records of D_801FA9BC */

/* Declarations of src/main/game_8003B568.c: provisional types from the code's own use; refined as functions match. */



typedef struct UnkStructB2 {  /* provisional: a 0x30-byte record of the table at D_801D3824 (D_801D8738 of them) */
    GameObject *unk_00;
    u16 unk_04;     /* 1: in use */
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u8 pad_0E[0x2];
    BuildingPart *unk_10;
    u8 pad_14[0x4];
    s16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u8 pad_1E[0x12];
} UnkStructB2;

extern UnkStructB2 D_801D3824[];
extern s16 D_801F9980;
extern s16 D_801F9984;
extern s16 D_801F9988;
extern s32 D_801FA72C;

void func_8001E4B0(void *);
void func_8001F724(s32);
void func_8004CFC0(void);
void func_8005DD48(Monster *);

void func_80029D1C(void);
/* The handlers of the D_801FA9BC records by kind (func_8003B5D0): game_8002A330 and game_80034590. */
void func_800344B8(UnkStructB1 *r);
void func_80034B94(UnkStructB1 *r);
void func_800350C0(UnkStructB1 *r);
void func_8003537C(UnkStructB1 *r);
void func_8003566C(UnkStructB1 *r);
void func_80035C4C(UnkStructB1 *r);

void func_8003B568(void);
void func_8003B5D0(UnkStructB1 *);
void func_8003B68C(void);
void func_8003B9A0(UnkStructB1 *);
void func_8003C130(void);
void func_8003C344(void);
void func_8003C080(void);
void func_8003C0AC(void);
void func_8003C0C8(void);
void func_8003C0E0(void);
void func_8003BD48(UnkStructB1 *);
void func_8003BF34(GameObject *, UnkStructB1 *, u16);   /* the third argument is not used */
extern u8 D_8008A494[];
extern u8 D_8008A4A0[];
extern u8 D_8008A4B8[];
extern u8 D_8008A4C4[];
void func_8003C1C0(u16, UnkStructB2 *);
void func_8003C674();                  /* empty; func_8003C3B0 passes it two arguments */
BuildingPart *func_8003C67C(Building *u, UnkStructB2 *rec);
void func_8003CE24(BuildingPart *p, ObjectDef *def, UnkStructB2 *rec, s32 arg3);
void func_8003C894(void **arg0);
void func_8003C8D4(UnkStructB1 *arg0);
void func_8003C934(UnkStructB1 *);
void func_8003C9E8(UnkStructB1 *arg0);
typedef struct UnkStructB4 {  /* provisional: 8-byte records of D_8007DDD4 (an animation and a value per step) */
    void *unk_00;
    u16 unk_04;
} UnkStructB4;
extern UnkStructB4 D_8007DDD4[];
void func_80054374(u16, Monster *);
extern void (*D_8007DDB4[8])(void);
s32 func_8003B9C8(GameObject *, Monster *);
void func_8003CA28(UnkStructB1 *arg0);
void func_8003CA70(UnkStructB1 *);
void func_8003CADC(Monster *arg0);
void func_8003CB30(Monster *arg0);
void func_8003CCA8(void);
void func_8003CCC0(void *);
void func_8003CB68(s16, Monster *);
void func_8003CEA0(s32, s32);
extern s32 D_800830BC[];
u16 func_8003C858(BuildingPart *, s32, s32);
u16 func_8003CC84(BuildingPart *, s32);
void func_8003C2D4(u16, UnkStructB2 *);
/* The handlers of the D_801D3824 records by kind (func_8003C1C0), in game_8003CD08. */
void func_8003D03C(UnkStructB2 *rec);
void func_8003D0D4(UnkStructB2 *rec);
void func_8003D11C(UnkStructB2 *rec);
void func_8003D228(UnkStructB2 *rec);
void func_8003D30C(UnkStructB2 *rec);
void func_8003D3CC(UnkStructB2 *rec);
void func_8003D5C8(void);

#endif /* GAME_8003B568_H */
