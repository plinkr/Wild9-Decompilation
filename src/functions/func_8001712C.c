// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"
#include "decomp.h"

void func_8001712C(void) {
    s32 i = 0;
    void** p = D_80081218;

    do {
        void* node = *p;

        if (node != NULL) {
            do {
                func_80016F64(node);
                node = M2C_FIELD(node, void**, 4);
            } while (node != NULL);
        }

        i++;
        p++;
    } while (i < 15);
}
