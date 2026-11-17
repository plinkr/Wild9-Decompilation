// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"

/**
 * Resets the MDEC ("MDEC_rest"): func_80067AC8(mode), preceded by
 * func_800578F4 for mode 0.
 */
void func_80067808(s32 arg0) {
    if (arg0 == 0) {
        func_800578F4();
    }
    func_80067AC8(arg0);
}
