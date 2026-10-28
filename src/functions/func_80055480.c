// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

// Clears the four events in D_800778F8..D_8007790C by testing them.
void func_80055480(void) {
    func_800571F4(D_800778F8);
    func_800571F4(D_80077900);
    func_800571F4(D_80077908);
    func_800571F4(D_8007790C);
}
