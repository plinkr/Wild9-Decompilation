// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

s32 func_800555E8(s32 port) {
    s32 result;

    func_80055480();
    if (func_8005FB08(port) != 0) {
        result = func_80055410();
    } else {
        result = 6;
    }
    if (result == 3) {
        func_80055538();
        if (func_8005FB68(port) == 1) {
            result = func_800554C8();
        } else {
            result = 6;
        }
    }
    if (result == 0) {
        func_80055480();
        func_8005FB18(port);
        result = func_80055410();
        if (result == 3) {
            result = 4;
        }
    }
    return result;
}
