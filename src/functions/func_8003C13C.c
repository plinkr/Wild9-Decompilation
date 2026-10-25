// SPDX-License-Identifier: AGPL-3.0-or-later

#include "functions.h"

void func_8003C13C(void* arg0) {
    void* var_v1;

    var_v1 = M2C_FIELD(arg0, void**, 8);
    if (var_v1 != NULL) {
        do {
            M2C_FIELD(var_v1, u16*, 0xC) =
                (u16)(M2C_FIELD(var_v1, u16*, 0xC) & 0xEFFD);
            var_v1 = M2C_FIELD(var_v1, void**, 4);
        } while (var_v1 != NULL);
    }
}
