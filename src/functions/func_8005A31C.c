// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

void func_8005A31C(void* arg0, void* arg1) {
    func_8005A078(D_8006963C, arg0);
    M2C_FIELD(D_80075470, void (**)(void*, void*, s32, void*), 0x8)(
        M2C_FIELD(D_80075470, void**, 0x1C), arg0, 8, arg1);
}
