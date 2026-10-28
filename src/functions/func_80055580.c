// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"

// Formats the memory card named `name`.
void func_80055580(char* name) {
    char buffer[0x40];

    func_80058554(buffer, name);
    func_80057284(buffer);
}
