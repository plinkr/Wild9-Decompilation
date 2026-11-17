// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

/**
 * Starts the DMA of an MDEC input block: waits for the input side
 * (func_80067CD4), then programs the channel registers with the data after the
 * header word, `size` in 32-word blocks, and writes the header to the MDEC.
 */
void func_80067BB8(u32* block, u32 size) {
    func_80067CD4();

    *D_8007661C |= 0x88;
    *D_800765E4 = (s32)(block + 1);
    *D_800765E8 = ((size >> 5) << 16) | 0x20;
    *D_80076614 = *block;
    *D_800765EC = 0x01000201;
}
