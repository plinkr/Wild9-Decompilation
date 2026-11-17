// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

/**
 * Starts the DMA of MDEC output into `dst`: waits for the output side
 * (func_80067D68), then programs the channel registers with `dst` and `size`
 * in 32-word blocks.
 */
void func_80067C48(s32 dst, u32 size) {
    func_80067D68();

    *D_8007661C |= 0x88;
    *D_800765F8 = 0;
    *D_800765F0 = dst;
    *D_800765F4 = ((size >> 5) << 16) | 0x20;
    *D_800765F8 = 0x01000200;
}
