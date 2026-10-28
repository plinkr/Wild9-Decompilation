// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

void func_8004D590(s32 arg0, void* arg1, s32* arg2) {
    s32 zero[3];

    zero[2] = 0;
    zero[1] = 0;
    zero[0] = 0;
    func_80027B64(1, &arg2[1], zero, M2C_FIELD(arg1, s8*, 0x1D5) == -1);
}
