#ifndef GAME_8004C064_H
#define GAME_8004C064_H

#include "gameobject.h"

/* What a thrown object does when it hits a monster, by its kind (Ai.action). */
typedef void (*ProjectileHitFn)(Ai *p, Monster *m);
extern ProjectileHitFn D_8007F680[];

#endif /* GAME_8004C064_H */
