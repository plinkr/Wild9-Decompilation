// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"
#include "include_asm.h"
#include "decomp.h"

void func_800101A4(void) {
    if (D_800778FC != 0) {
        D_800777AC = func_800551B8(D_80077488);
        D_800778FC = 0;
    }
}
