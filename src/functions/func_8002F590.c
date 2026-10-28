// SPDX-License-Identifier: AGPL-3.0-or-later

#include "functions.h"

void func_8002F590(void* arg0) {
    u8 buffer[0x60];
    u8* base = M2C_FIELD(arg0, u8**, 0x10);

    func_8002EF38(base + 0xF8, arg0, base, buffer);
    func_8002F384(buffer);
}
