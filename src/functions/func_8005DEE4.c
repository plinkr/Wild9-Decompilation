// SPDX-License-Identifier: AGPL-3.0-or-later
#include "functions.h"
#include "globals.h"

void func_8005DEE4(void) {
    *D_80075E7C = (*D_80075E7C & 0xF0FFFFFF) | 0x22000000;
}
