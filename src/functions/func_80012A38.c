// SPDX-License-Identifier: AGPL-3.0-or-later
// https://decomp.me/scratch/hjdaU

#include "types.h"
#include "functions.h"
#include "globals.h"

void func_80012A38(void) {
    s32 var_a2;
    s32 var_a2_2;
    s32 var_a2_3;
    register u32 temp_s0 asm("s0");
    register u32 temp_s1 asm("s1");
    register u8* buffer asm("s3");
    register u8* renderBuffer asm("s0");
    register s32 row asm("s4") = 0xA;
    register s32 y asm("s2");
    register void* object asm("s5");
    register u8* data asm("s1");
    register u8* callBuffer asm("a0");
    register u8* callFormat asm("a1");
    register void* temp_v1 asm("v1");
    register s32 index asm("v0");

    temp_s1 = func_8001EC9C();
    temp_s0 = func_8001ED3C() >> 10;
    func_80058FE4(
        D_8007C7A8, D_80068718, temp_s1 >> 10, temp_s0, func_8001ED54());
    buffer = D_8007C7A8;
    func_80025F44(buffer, row, row, 2);
    func_80058FE4(
        buffer, D_80068738, (D_80077B7C * 0x64 + 0x80) >> 9, D_80077B7C);
    func_80025F44(buffer, row, 0x19, 2);
    func_80058FE4(buffer, D_80068758, D_800777AC / 320, D_800777AC, D_80077B9C);
    func_80025F44(buffer, row, 0x23, 2);
    func_80058FE4(buffer, D_8006877C, D_8007783C);
    func_80025F44(buffer, row, 0x32, 2);
    func_80058FE4(buffer, D_80068794, D_80077818);
    func_80025F44(buffer, row, 0x3C, 2);
    func_80058FE4(buffer, D_800687AC, D_8007784C, D_800778AC);
    func_80025F44(buffer, row, 0x50, 2);
    func_80058FE4(buffer, D_800687C8, D_80077B30);
    func_80025F44(buffer, row, 0x64, 2);
    func_80058FE4(buffer, D_800687E4, D_80077B64);
    func_80025F44(buffer, row, 0x6E, 2);
    func_80058FE4(buffer, D_80068800, D_80077830, D_80077BF4, D_800777EC);
    func_80025F44(buffer, row, 0x7D, 2);
    func_80058FE4(buffer, D_80068820, D_8007794C, 0x24,
                  ((u32)D_8007794C * 0x24 + 0x3FF) >> 10);
    func_80025F44(buffer, row, 0x87, 2);
    func_80058FE4(buffer, D_80068840, D_80077814);
    func_80025F44(buffer, row, 0x91, 2);

    if (D_80077938 != 0) {
        object = *(void**)((u8*)D_80077938 + 0x10);
        temp_v1 = *(void**)((u8*)object + 0x2D0);
        if (temp_v1 != 0) {
            y = 0xA0;
            index = *(s16*)((u8*)object + 0x2DA);
            data = (u8*)(*(s32*)((u8*)temp_v1 + 4)) + (index << 5);

            callBuffer = buffer;
            callFormat = D_800774CC;
            __asm__ volatile("" : "+r"(callBuffer), "+r"(callFormat));
            if (data[1] < 0xC) {
                var_a2 = D_80069D94[data[1]];
            } else {
                var_a2 = D_80069DC0;
            }
            func_80058FE4(callBuffer, callFormat, var_a2);
            renderBuffer = D_8007C7A8;
            func_80025F44(renderBuffer, row, y, 0);
            y += 0xA;

            callBuffer = renderBuffer;
            callFormat = D_800774CC;
            __asm__ volatile("" : "+r"(callBuffer), "+r"(callFormat));
            if (data[2] < 3) {
                var_a2_2 = D_80069DC4[data[2]];
            } else {
                var_a2_2 = D_80069DD0;
            }
            func_80058FE4(callBuffer, callFormat, var_a2_2);
            func_80025F44(renderBuffer, row, y, 0);
            y += 0xA;

            callBuffer = renderBuffer;
            callFormat = D_800774CC;
            __asm__ volatile("" : "+r"(callBuffer), "+r"(callFormat));
            if (data[3] < 3) {
                var_a2_3 = D_80069DC4[data[3]];
            } else {
                var_a2_3 = D_80069DD0;
            }
            func_80058FE4(callBuffer, callFormat, var_a2_3);
            func_80025F44(renderBuffer, row, y, 0);
            y += 0xF;

            func_80025F44(D_80068858, row, y, 2);
            y += 0xA;
            func_80058FE4(renderBuffer, D_800774D0,
                          *(u16*)((u8*)*(void**)((u8*)D_8007748C + 4) + 2));
            func_80025F44(renderBuffer, row + 0x28, y, 0);
            func_80058FE4(
                renderBuffer, D_800774D0, *(s16*)((u8*)object + 0x2DA));
            func_80025F44(renderBuffer, row + 0x58, y, 0);
            func_80058FE4(
                renderBuffer, D_800774D0, *(s16*)((u8*)object + 0x2DC));
            func_80025F44(renderBuffer, row | 0x90, y, 0);
            func_80058FE4(
                renderBuffer, D_800774D4, *(s32*)((u8*)object + 0x2FC) >> 12);
            func_80025F44(renderBuffer, row + 0xAE, y, 0);
        }
    }
}
