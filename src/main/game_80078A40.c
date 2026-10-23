/* A piece of the game's own code between Psy-Q library objects: the sound driver on libspu (docs/TOOLCHAIN.md).
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "sound.h"

void func_80078A40(s32 n, s32 arg1) {
    func_8006F96C(&D_801FDF20->unk_0C->unk_20[n], n, arg1, 0, 0);
}
