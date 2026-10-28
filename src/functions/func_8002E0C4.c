// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"

// Command handler (table D_8006E7EC).
void func_8002E0C4(void* arg0) {
    void* target = M2C_FIELD(arg0, void**, 0x44);

    func_80022644(
        &M2C_FIELD(target, s32*, 0x2C), M2C_FIELD(arg0, s32*, 0x18), 1);
}
