// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

void func_8001D9B8(s32 arg0, s32 arg1) {
    register u8* dst asm("v0");

    if (((D_8007B37C != 0) && (D_8007754C != 6)) || ((arg1 & 0xFF) == 0)) {
        // !FAKE: building the address in v0 keeps the +1 in the store offset
        // (sb a1,1(v0)) instead of folding it into %lo(D_800776F8)
        dst = (u8*)(arg0 << 1);
        dst += (s32)D_800776F8;
        dst[1] = arg1;
    }
}
