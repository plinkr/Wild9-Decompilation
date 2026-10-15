// SPDX-License-Identifier: AGPL-3.0-or-later
#include "functions.h"
#include "globals.h"

void func_8003023C(void* arg0) {
    if (M2C_FIELD(arg0, u16*, 0x12) == 1) {
        func_800306DC(M2C_FIELD(arg0, s32*, 0x50), 0, arg0 + 0x14, 0);
    }
}
