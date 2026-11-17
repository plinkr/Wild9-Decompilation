// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

/**
 * Looks up the state of `port` through D_80076440 and forwards it to
 * func_800662A4.
 */
s32 func_80064B44(s32 port, void* arg1) {
    return func_800662A4(D_80076440(port), arg1);
}
