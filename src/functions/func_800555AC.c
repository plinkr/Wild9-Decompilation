// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

s32 func_800555AC(s32 port) {
    func_80055480();
    if (func_8005FB08(port) != 0) {
        return func_80055410();
    }
    return 6;
}
