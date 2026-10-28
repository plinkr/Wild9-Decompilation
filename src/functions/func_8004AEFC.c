// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

// Copies the five words at +0x44..+0x54 from `src` to `dst`.
void func_8004AEFC(void* src, void* dst) {
    M2C_FIELD(dst, s32*, 0x44) = M2C_FIELD(src, s32*, 0x44);
    M2C_FIELD(dst, s32*, 0x48) = M2C_FIELD(src, s32*, 0x48);
    M2C_FIELD(dst, s32*, 0x4C) = M2C_FIELD(src, s32*, 0x4C);
    M2C_FIELD(dst, s32*, 0x50) = M2C_FIELD(src, s32*, 0x50);
    M2C_FIELD(dst, s32*, 0x54) = M2C_FIELD(src, s32*, 0x54);
}
