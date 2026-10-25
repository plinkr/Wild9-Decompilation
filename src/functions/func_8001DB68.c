// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"

s32 func_8001DB68(u16* flags, u16 mask) {
    s32 result;

    result = (flags[0] & mask) != 0;
    if (flags[1] & mask) {
        result |= 0x2;
    }
    if (flags[2] & mask) {
        result |= 0x4;
    }
    if (flags[3] & mask) {
        result |= 0x8;
    }
    if (flags[7] & mask) {
        result |= 0x40;
    }
    if (flags[6] & mask) {
        result |= 0x20;
    }
    if (flags[4] & mask) {
        result |= 0x10;
    }
    if (flags[5] & mask) {
        result |= 0x80;
    }
    if (flags[9] & mask) {
        result |= 0x100;
    }
    if (flags[11] & mask) {
        result |= 0x200;
    }
    if (flags[8] & mask) {
        result |= 0x400;
    }
    if (mask & flags[10]) {
        result |= 0x800;
    }
    if (mask & flags[13]) {
        result |= 0x1000;
    }
    if (mask & flags[12]) {
        result |= 0x2000;
    }
    if (mask & flags[14]) {
        result |= 0x4000;
    }
    if (mask & flags[15]) {
        result |= 0x8000;
    }
    return result;
}
