// SPDX-License-Identifier: AGPL-3.0-or-later
#include "functions.h"

void func_8002E3CC(void* arg0) {
    void* temp_v1;
    void* temp_v1_2;

    temp_v1 = M2C_FIELD(arg0, void**, 0x48);
    M2C_FIELD(temp_v1, u16*, 4) = (u16)(M2C_FIELD(temp_v1, u16*, 4) + 0xC);
    temp_v1_2 = M2C_FIELD(arg0, void**, 0x48);
    if ((s16)M2C_FIELD(temp_v1_2, u16*, 4) >= 0x181) {
        M2C_FIELD(temp_v1_2, u16*, 4) = 0x180U;
    }
}
