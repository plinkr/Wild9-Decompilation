// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "decomp.h"
#include "globals.h"

typedef struct ListNode {
    u8 pad0[0x8];
    struct ListNode* next; /* 0x08 */
    u8 padC[0x4];
    s32 unk10; /* 0x10 */
} ListNode;

u32 func_8001EC9C(void) {
    ListNode* node;
    u32 total = 0;

    for (node = D_8007D1B0[0]; node != NULL; node = node->next) {
        total -= node->unk10;
    }
    return total;
}
