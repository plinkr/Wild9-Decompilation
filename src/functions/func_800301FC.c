// SPDX-License-Identifier: AGPL-3.0-or-later

#include "functions.h"
#include "globals.h"

// Twin of func_8003023C that passes the table D_8006E594 instead of the
// pointer at +0x50.
void func_800301FC(void* arg0) {
    if (M2C_FIELD(arg0, u16*, 0x12) == 1) {
        func_800306DC(D_8006E594, 0, arg0 + 0x14, M2C_FIELD(arg0, s32*, 0x50));
    }
}
