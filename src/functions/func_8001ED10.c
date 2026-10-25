// SPDX-License-Identifier: AGPL-3.0-or-later

#include "functions.h"
#include "globals.h"

void func_8001ED10(void) {
    void* var_v0;

    var_v0 = (void*)D_80075F0C;
    if (var_v0 != NULL) {
        do {
            var_v0 = M2C_FIELD(var_v0, void**, 4);
        } while (var_v0 != NULL);
    }
}
