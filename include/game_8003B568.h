#ifndef GAME_8003B568_H
#define GAME_8003B568_H

#include "common.h"
#include "game_8002A330.h"   /* the actor record (UnkStruct1) and D_800AA268 */

/* Declarations of src/main/game_8003B568.c: provisional types from the code's own use; refined as functions match. */

typedef struct UnkStructB1 {  /* provisional: a 0x58-byte record of the table at D_801FA9BC */
    void *unk_00;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0xC];
    UnkStruct1 *unk_14;
    u8 pad_18[0x2];
    u16 unk_1A;
    u8 pad_1C[0x3C];
} UnkStructB1;

extern u16 D_801E1C80;
extern u16 D_801E29B0;
extern UnkStructB1 D_801FA9BC[];

void func_8001E4B0(void *);
void func_8001F724(s32);
void func_8004CFC0(void);
void func_8005DD48(UnkStruct1 *);

void func_8003B568(void);
void func_8003B5D0(UnkStructB1 *);
void func_8003C080(void);
void func_8003C0AC(void);
void func_8003C0C8(void);
void func_8003C0E0(void);
void func_8003C674(void);
void func_8003C894(void **arg0);
void func_8003C8D4(UnkStructB1 *arg0);
void func_8003C934(UnkStructB1 *);
void func_8003C9E8(UnkStructB1 *arg0);
void func_8003CA28(UnkStructB1 *arg0);
void func_8003CA70(void);
void func_8003CADC(UnkStruct1 *arg0);
void func_8003CB30(UnkStruct1 *arg0);
void func_8003CCA8(void);
void func_8003CCC0(void *);

#endif /* GAME_8003B568_H */
