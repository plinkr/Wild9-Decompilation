// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

void func_8001D1B4(void) {
    if (!(D_80077894 & 0x10)) {
        func_8001CDB0();
    } else {
        func_8001C8A8();
    }
}
