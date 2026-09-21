// SPDX-License-Identifier: AGPL-3.0-or-later

#include "types.h"
#include "functions.h"
#include "globals.h"
#include "include_asm.h"
#include "decomp.h"

void func_800110F8(UnkStruct* target, UnkStruct* source) {
    if (source->unk4 != 0) {
        register UnkStruct* out = target;

        // Must reside in $a1 to reproduce the original binary's register
        // allocation. The s32 type is intentional: although 16-bit values are
        // loaded/stored, treating it as 32-bit guides the compiler to pick $a1.
        register s32 temp asm("a1");

        s32 newOffset;

        temp = out->unk6;
        out->unk1E = temp;

        out->unk18 = out->unk0;
        out->unk1A = out->unk2;
        out->unk1C = out->unk4;
        out->unk20 = out->unk8;
        out->unk22 = out->unkA;
        out->unk26 = out->unkE;

        newOffset = (source->unk28 + out->unk10 - source->unk8) & 0xFFF;

        temp = out->unk12;
        out->unk2A = temp;

        out->unk28 = newOffset;
    }
}
