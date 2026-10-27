/* The sound driver WESS: the sequence trigger by type, a piece of its own between Psy-Q library objects
 * (docs/TOOLCHAIN.md "The sound driver: GCC 2.7.2").
 * The boundaries and their evidence: config/main.yaml (docs/MATCHING.md "Splitting a target into files"). */
#include "common.h"
#include "sound.h"

void func_80078A40(s32 n, s32 arg1) {
    wess_start_sequence(&D_801FDF20->unk_0C->unk_20[n], n, arg1, 0, 0);
}
