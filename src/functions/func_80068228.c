// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

/**
 * Expands the compressed stream at D_80076654 into `dst`, then decodes the
 * result in place with a 16-bit xor chain (each halfword from +8 on is xored
 * with the one 8 bytes before it).
 *
 * Tokens below 0xF0 are runs of `token + 1` bytes: literals when the current
 * offset is 0, copies from `offset` bytes back otherwise. 0xF0 clears the
 * offset and 0xF1..0xFF set it to ((token << 8) | next byte) - 0xF0FF; an
 * offset of 0xF00 ends the stream.
 */
void func_80068228(u8* dst) {
    s32 offset = 0;
    // !FAKE: pinning `src` to $a3 reproduces the original register allocation.
    register u8* src asm("a3") = D_80076654;
    u8* out = dst;
    s32 len;
    s32 count;
    // !FAKE: the limit lives in a variable so that its `ori` lands in the
    // preheader of the second loop.
    s32 limit;
    u8 token;

    for (;;) {
        token = *src;
        src++;
        len = token;
        if ((u32)len < 0xF0) {
            if (offset != 0) {
                while (len >= 0) {
                    *out = *(out - offset);
                    out++;
                    len--;
                }
            } else {
                while (len >= 0) {
                    *out = *src;
                    src++;
                    out++;
                    len--;
                }
            }
        } else if (len == 0xF0) {
            offset = 0;
        } else {
            offset = ((len << 8) | *src) - 0xF0FF;
            src++;
        }
        if (offset == 0xF00) {
            break;
        }
    }

    count = 4;
    limit = 0x87FF;
    dst += 8;
    do {
        *(u16*)dst ^= *(u16*)(dst - 8);
        dst += 2;
        count++;
    } while (count <= limit);
}
