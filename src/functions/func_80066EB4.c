// SPDX-License-Identifier: AGPL-3.0-or-later
#include "functions.h"

void func_80066EB4(void* arg0) {
    u8 temp_v0;

    temp_v0 = M2C_FIELD(arg0, u8*, 0x37);
    M2C_FIELD(arg0, u8*, 0x37) = 0U;
    M2C_FIELD(arg0, u8*, 0x38) = temp_v0;
}
