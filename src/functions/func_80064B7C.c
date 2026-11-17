// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

/**
 * Looks up the state of `port` through D_80076440 and forwards it to
 * func_800663F0.
 */
s32 func_80064B7C(s32 port, s32 arg1, s32 arg2) {
    return func_800663F0(D_80076440(port), arg1, arg2);
}
