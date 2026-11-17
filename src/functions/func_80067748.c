// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

/**
 * Stores `arg0` in D_8007F6FC and latches the current value of the root
 * counter 1 register (0x1F801120) in D_8007B198.
 */
void func_80067748(s32 arg0) {
    D_8007F6FC = arg0;
    D_8007B198 = *(volatile u16*)0x1F801120;
}
