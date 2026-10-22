#ifndef GAME_8004C064_H
#define GAME_8004C064_H

#include "gameobject.h"

/* A projectile or piece of debris in flight: a record of D_801D85C8 (0x40 bytes; D_801D870C holds the count).
 * Fields from game_8004C064. */
typedef struct {
    /* 0x00 */ GameObject *obj;
    /* 0x04 */ u8 unk_04[0x04];
    /* 0x08 */ u16 kind;               /* 0x1E, 0x46..0x4D: the thrown kinds; indexes D_8007F680 when it hits */
    /* 0x0A */ u8 unk_0A[0x02];
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ u16 unk_0E;
    /* 0x10 */ u8 unk_10[0x26];
    /* 0x36 */ u16 unk_36;
    /* 0x38 */ u8 unk_38[0x08];
} Projectile;                          /* 0x40 bytes */

extern Projectile D_801D85C8[];
extern u16 D_801D870C;

typedef void (*ProjectileHitFn)(Projectile *p, Monster *m);
extern ProjectileHitFn D_8007F680[];   /* by Projectile.kind */

#endif /* GAME_8004C064_H */
