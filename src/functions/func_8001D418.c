// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

void func_8001D418(void) {
    u8 buf[4];
    s32 value;

    buf[0] = 0xFF;
    buf[1] = 0;
    buf[2] = 0xFF;
    buf[3] = 0;
    func_80060C60(buf);
    func_8005F664(1);
    value = (D_8007B364 * 0x266600) >> 16;
    func_8005F644(value, value);
}
