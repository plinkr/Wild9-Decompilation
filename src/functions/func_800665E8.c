// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "decomp.h"
#include "functions.h"
#include "globals.h"

void func_800665E8(void* arg0) {
    s32 result = D_80076444(arg0);
    u8* p = M2C_FIELD(arg0, u8**, 0x3C);

    D_800764AC = result;
    *p = 0;
    func_8006549C(arg0, -2);
}
