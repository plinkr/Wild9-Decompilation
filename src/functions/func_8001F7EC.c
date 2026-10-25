// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"

s32 func_8001F7EC(s32 arg0) {
    return func_80024300(func_8001F7B4() & 0xFFFF, arg0, 0x10);
}
