#ifndef GAME_8004E574_H
#define GAME_8004E574_H

#include "gameobject.h"

/* game_8004E574: the monsters' script commands. The speed tables, one pair per Monster.unk_0CC value. */
typedef struct {
    /* 0x00 */ s32 speed;              /* Monster.unk_100 */
    /* 0x04 */ s32 vel_y;              /* GameObject.vel_y */
} SpeedPair;

extern SpeedPair D_8007F710[];         /* facing right */
extern SpeedPair D_8007F758[];         /* facing left */
extern SpeedPair D_8007F7A0[];
extern SpeedPair D_8007F7E8[];         /* monster kind 7 */
extern SpeedPair D_8007F830[];
extern SpeedPair D_8007F878[];
extern u16 D_8007F8C0[];               /* per monster kind (index kind - 1) */
extern u16 D_8007F8D0[];


#endif /* GAME_8004E574_H */
