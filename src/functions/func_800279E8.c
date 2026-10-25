// SPDX-License-Identifier: AGPL-3.0-or-later

#include "functions.h"
#include "globals.h"

// Releases the nodes D_80077B14 and D_80077754, then empties the list
// D_80077980 (head) / D_800779A0 (tail) and its counter.
void func_800279E8(void) {
    func_8001EA44(D_80077B14);
    func_8001EA44(D_80077754);
    D_80077904 = 0;
    D_80077B14 = NULL;
    D_80077980 = NULL;
    D_800779A0 = NULL;
}
