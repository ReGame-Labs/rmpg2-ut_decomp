#ifndef GAME_8003B568_H
#define GAME_8003B568_H

#include "common.h"
#include "game_8002A330.h"   /* the actor record (UnkStruct1) and D_800AA268 */

/* Declarations of src/main/game_8003B568.c: provisional types from the code's own use; refined as functions match. */

typedef struct UnkStructB1 {  /* provisional: a 0x58-byte record of the table at D_801FA9BC */
    UnkStruct4 *unk_00;
    s16 unk_04;
    u16 unk_06;
    u16 unk_08;
    s16 unk_0A;
    u8 pad_0C[0x8];
    UnkStruct1 *unk_14;
    u8 pad_18[0x2];
    u16 unk_1A;
    u8 pad_1C[0x14];
    s32 unk_30;     /* y acceleration, 16.16 */
    s32 unk_34;     /* x acceleration, 16.16 */
    u8 pad_38[0x6];
    u16 unk_3E;
    UnkStruct4 *unk_40;
    u8 pad_44[0x14];
} UnkStructB1;

typedef struct UnkStructB3 {  /* provisional: what a 0x30-byte record's unk_10 points to (a kind at 6) */
    u8 pad_00[0x4];
    u16 unk_04;
    u16 unk_06;
    s32 unk_08;
    s32 unk_0C;
} UnkStructB3;

typedef struct UnkStructB2 {  /* provisional: a 0x30-byte record of the table at D_801D3824 (D_801D8738 of them) */
    s32 unk_00;
    u16 unk_04;
    u8 pad_06[0xA];
    UnkStructB3 *unk_10;
    u8 pad_14[0x8];
    u16 unk_1C;
    u8 pad_1E[0x12];
} UnkStructB2;

extern UnkStructB2 D_801D3824[];
extern u16 D_801D8738;
extern u16 D_801E1C80;
extern s16 D_801F9980;
extern s16 D_801F9984;
extern s16 D_801F9988;
extern u16 D_801E29B0;
extern UnkStructB1 D_801FA9BC[];

void func_8001E4B0(void *);
void func_8001F724(s32);
void func_8004CFC0(void);
void func_8005DD48(UnkStruct1 *);

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
void func_8003BF34(UnkStruct4 *, UnkStructB1 *, u16);   /* the third argument is not used */
extern u16 D_801D37BC;
extern s16 D_801F9AB0;
extern s16 D_801FA98C;
extern s16 D_801FA990;
extern s16 D_801FAC84;
extern u8 D_8008A494[];
extern u8 D_8008A4A0[];
extern u8 D_8008A4B8[];
extern u8 D_8008A4C4[];
void func_8003C1C0(u16, UnkStructB2 *);
void func_8003C674(void);
void func_8003C894(void **arg0);
void func_8003C8D4(UnkStructB1 *arg0);
void func_8003C934(UnkStructB1 *);
void func_8003C9E8(UnkStructB1 *arg0);
typedef struct UnkStructB4 {  /* provisional: 8-byte records of D_8007DDD4 (an animation and a value per step) */
    void *unk_00;
    u16 unk_04;
} UnkStructB4;
extern UnkStructB4 D_8007DDD4[];
void func_80054374(u16, UnkStruct1 *);
extern s16 D_801F9ACA;
extern void (*D_8007DDB4[8])(void);
s32 func_8003B9C8(UnkStruct4 *, UnkStruct7 *);
void func_8003CA28(UnkStructB1 *arg0);
void func_8003CA70(UnkStructB1 *);
void func_8003CADC(UnkStruct1 *arg0);
void func_8003CB30(UnkStruct1 *arg0);
void func_8003CCA8(void);
void func_8003CCC0(void *);
void func_8003CB68(s16, UnkStruct1 *);
void func_8003CEA0(s32, s32);
extern s32 D_800830BC[];
u16 func_8003C858(UnkStructB3 *, s32, s32);
u16 func_8003CC84(UnkStructB3 *, s32);
void func_8003C2D4(u16, UnkStructB2 *);

#endif /* GAME_8003B568_H */
