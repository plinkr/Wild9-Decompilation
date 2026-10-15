// SPDX-License-Identifier: AGPL-3.0-or-later
#include "functions.h"

void func_8001DED4(void* arg0) {
    s32 temp_v1;
    s32 temp_v1_2;

    temp_v1 = M2C_FIELD(arg0, s32*, 0);
    if (temp_v1 & 4) {
        M2C_FIELD(arg0, s16*, 0xC) = -0x80;
    } else if (temp_v1 & 8) {
        M2C_FIELD(arg0, s16*, 0xC) = 0x80;
    } else {
        M2C_FIELD(arg0, s16*, 0xC) = 0;
    }
    temp_v1_2 = M2C_FIELD(arg0, s32*, 0);
    if (temp_v1_2 & 1) {
        M2C_FIELD(arg0, s16*, 0xE) = -0x80;
    } else if (temp_v1_2 & 2) {
        M2C_FIELD(arg0, s16*, 0xE) = 0x80;
    } else {
        M2C_FIELD(arg0, s16*, 0xE) = 0;
    }
    M2C_FIELD(arg0, s16*, 8) = 0;
    M2C_FIELD(arg0, s16*, 0xA) = 0;
}
