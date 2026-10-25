// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"
#include "decomp.h"

void func_8001608C(void) {
    s32 i = 0;
    void** p = D_80081218;

    for (; i < 15; i++, p++) {
        void* node = *p;

        if (node == NULL) {
            continue;
        }

        do {
            u8* obj = M2C_FIELD(node, void**, 0x10);

            if ((M2C_FIELD(obj, u16*, 4) & 0x211) == 0) {
                void* fn = M2C_FIELD(obj, void**, 0x400);

                if (fn != NULL) {
                    ((void (*)(void*))fn)(node);
                }
            }

            node = M2C_FIELD(node, void**, 4);
        } while (node != NULL);
    }
}
