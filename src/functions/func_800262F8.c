// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

// Registers `obj` in the D_8007C8C0 slot given by its first word, and resets
// that slot's counter.
void func_800262F8(s32* obj) {
    if (*obj < 0xA0) {
        D_8007C8C0[*obj].obj = obj;
        D_8007C8C0[*obj].count = 0;
    }
}
