// SPDX-License-Identifier: AGPL-3.0-or-later

// CFLAGS: -mno-split-addresses

#include "types.h"
#include "functions.h"
#include "globals.h"

/**
 * Loads the quantization tables of `env` into the MDEC command buffers and
 * sends both (func_80067BB8). Returns `env`.
 */
s32* func_800678C8(s32* env) {
    s32* src;
    s32* dst;
    s32 i;

    src = env;
    dst = D_800764D8;
    for (i = 15; i != -1; i--) {
        *dst++ = *src++;
    }
    dst = D_80076518;
    src = env + 16;
    for (i = 15; i != -1; i--) {
        *dst++ = *src++;
    }
    func_80067BB8((u32*)D_800764D4, 0x20);
    func_80067BB8((u32*)D_80076558, 0x20);
    return env;
}
