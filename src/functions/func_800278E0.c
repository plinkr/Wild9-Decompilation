// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "globals.h"

// Binds `sprite` to the object registered at `index` in D_8007C8C0. When the
// slot is in use, gives the sprite its default geometry and returns 1.
s32 func_800278E0(D_800278E0_Sprite* sprite, s32 index) {
    void* obj;

    if (index < 0xA0) {
        obj = D_8007C8C0[index].obj;
        sprite->obj = obj;
        // The goto keeps the ROM's `bnez` and puts the defaults after the
        // `return 0` block; a plain nested `if` inverts the branch.
        if (obj != NULL) {
            goto in_use;
        }
    }
    return 0;

in_use:
    sprite->unkC = 0;
    sprite->unkD = 0;
    sprite->unk0 = 0;
    sprite->unk2 = 0x100;
    sprite->unk8 = 0x80;
    sprite->unk9 = 0x80;
    sprite->unkA = 0x80;
    sprite->unk4 = 0x100;
    return 1;
}
