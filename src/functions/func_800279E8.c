// SPDX-License-Identifier: AGPL-3.0-or-later

#include "functions.h"
#include "globals.h"

// Frees the node pool D_80077B14 and the sprite pool D_80077754, then empties
// the free list (D_80077980), the active list (D_800779A0) and its counter.
void func_800279E8(void) {
    func_8001EA44(D_80077B14);
    func_8001EA44(D_80077754);
    D_80077904 = 0;
    D_80077B14 = NULL;
    D_80077980 = NULL;
    D_800779A0 = NULL;
}
