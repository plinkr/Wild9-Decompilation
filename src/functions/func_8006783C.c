// SPDX-License-Identifier: AGPL-3.0-or-later

// CFLAGS: -mno-split-addresses

#include "types.h"
#include "globals.h"

/**
 * Copies the MDEC environment (two 16-word quantization tables and the 32-word
 * DCT table) into `env` and returns it.
 */
s32* func_8006783C(s32* env) {
    s32* src;
    s32* dst;
    s32 i;

    dst = env;
    src = D_800764D8;
    for (i = 15; i != -1; i--) {
        *dst++ = *src++;
    }
    dst = env + 16;
    src = D_80076518;
    for (i = 15; i != -1; i--) {
        *dst++ = *src++;
    }
    dst = env + 32;
    src = D_8007655C;
    for (i = 31; i != -1; i--) {
        *dst++ = *src++;
    }
    return env;
}
