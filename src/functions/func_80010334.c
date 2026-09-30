// SPDX-License-Identifier: AGPL-3.0-or-later
// https://decomp.me/scratch/EyxOb
// WIP

#include "types.h"
#include "functions.h"
#include "func_types.h"
#include "globals.h"

void func_80010334(void) {
    s32* object;
    s32 one = 1;
    s32* inputState;
    s32 minusOne;
    register s32* spSave asm("sp");
    s32 result;
    s32 two;

    func_8005F870();
    func_800578F4();
    func_80059F78(0);
    func_800605F8();
    func_8005515C();
    func_80059C94(0);
    func_80055200();
    func_8001DE60(0);
    func_8001DA00();
    func_8004EB38();
    func_8005CE8C();
    func_8001F660();

    D_80077484 = 0;
    {
        register s32 fparg asm("a0") = (s32)func_800100CC;
        __asm__ volatile("" : "+r"(fparg));
        func_80057984((void (*)(void))fparg);
    }
    func_80059F18(func_800101A4);
    func_800550DC();
    object = D_8007B350;
    __asm__ volatile("" : "+r"(object));

    object[3] = 4;
    object[5] = 0x100;
    object[4] = 0x100;
    object[0x19] = 2;
    object[6] = 1;
    object[0x14] = -1;
    object[0x0B] = 1;

    func_8005706C(3);
    func_8005706C(5);
    func_8005706C(4);

    D_80077484 = 0;
    D_80077978 = 0;
    D_800779A8 = 0;
    object[1] = 0x11;
    func_80015224();

    D_80077484 = 0;
    D_80077978 = 0;
    D_800779A8 = 0;
    object[1] = 0x28;
    func_80015224();

    object[1] = 0x29;
    object[1] = 0x29;
    inputState = D_8007C788;
    D_8007C788[0] = 0;
    D_8007C788[1] = 0;

    while (1) {
        minusOne = -1;
        func_80059F78(0);
        func_80055100();

        D_80077484 = 0;
        D_80077978 = 0;
        D_800779A8 = 0;
        D_80077484 = 0;
        D_80077978 = 0;
        D_800779A8 = 0;
        func_80015224();

        D_800774C4 = one;
        func_80055100();
        func_80055138();
        func_8001F78C();
        D_80077478 = minusOne;

        if (func_8001576C() == 0) {
            D_800774C4 = 0;
            func_8005A010(0);
            continue;
        }

        D_80077A74 = -2;
        D_800774C4 = 0;
        D_8007C788[0] = 0;
        D_8007C788[1] = 0;
        func_8001DE60(1);
        D_80077670 = 0;
        func_8005A010(0);
        ((F576C4)func_800576C4)(0);

        if (object[0x0D] == 0x29) {
            D_8007754C = 0;
        } else {
            func_8001D89C();
        }

        func_80059F78(1);
        {
            register s32* scratch asm("t0");
            register s32* addr asm("a2");
            addr = (s32*)0x1F8003FC;
            __asm__ volatile("" : "+r"(addr));
            scratch = addr;
            *(s32**)scratch = spSave;
            scratch = (s32*)((u32)scratch - 4);
            __asm__ volatile("" : "+r"(scratch));
            spSave = scratch;
        }

        if (object[0x43] == 0) {
            do {
                func_80010000();
                func_8001DAAC();

                if (D_8007754C == 6) {
                    if ((D_8007C788[1] != 0) || (D_8007C788[0] & 0x2000)) {
                        object[0x44] = one;
                    }
                    if ((D_8007754C == 6) && (object[0xC2] != 0)) {
                        object[0x44] = one;
                    }
                }

                if ((D_8007754C == 5) && (D_8007C788[1] & 0x2000)) {
                    object[0x44] = one;
                }

                if (object[0x0F] <= 0) {
                    object[0x0F] = 0x3C;
                    object[0x14] = minusOne;
                    object[1] = 0x29;
                    object[0x44] = one;
                    object[0x12] = 0;
                }

                if (object[0x44] != 0) {
                    if (object[0x45] == 0) {
                        object[0x45] = one;
                        object[0x0C] = minusOne;
                    } else if (object[0x0C] == 0) {
                        object[0x43] = one;
                    }
                }

                func_8001F010();
                D_8007797C = 0;
                D_80077800 = 0;
                D_80077818 = 0;
                D_8007783C = 0;
                D_8007784C = 0;
                D_80077B18 = 0;

                D_80077958 = func_80055194();
                func_8001EB58();
                D_80077958 = func_800551B8(D_80077958);
                D_800777B4 = func_80055194();
                func_80025DF4();
                D_800777B4 = func_800551B8(D_800777B4);
                D_800779B4 = func_80055194();
                func_80026340();
                D_800779B4 = func_800551B8(D_800779B4);
                D_8007788C = func_80055194();
                func_8001BBC8();
                D_8007788C = func_800551B8(D_8007788C);
                D_8007785C = func_80055194();
                func_8001F69C();
                D_8007785C = func_800551B8(D_8007785C);
                D_80077B94 = func_80055194();
                func_80050628();
                D_80077B94 = func_800551B8(D_80077B94);
                D_800779B0 = func_80055194();
                func_8001DF7C(0);
                func_8001DF7C(1);
                D_800779B0 = func_800551B8(D_800779B0);
                func_80016128();
                D_8007787C = func_80055194();
                func_8001F160();
                D_8007787C = func_800551B8(D_8007787C);
                func_80011B24();

                if (object[0xC2] == 0) {
                    D_80077BB0 = func_80055194();
                    func_80027790();
                }
                func_8002733C();
                if (object[0xC2] == 0) {
                    D_80077BB0 = func_800551B8(D_80077BB0);
                }

                func_800120A4();
                if (object[0xCB] & 4) {
                    func_80019DAC(D_8007747C);
                }

                if (object[0xC2] == 0) {
                    D_80077A84 = func_80055194();
                    func_80020BA4();
                    D_80077A84 = func_800551B8(D_80077A84);
                }

                func_80025CE8();
                D_80077B7C = ((F576C4)func_800576C4)(1) - D_800779E4;
                D_80077B9C = func_80055194();
                func_8005A010(0);
                D_80077B9C = func_800551B8(D_80077B9C);
                D_80077484 = one;
                D_80077978 = D_80077948;
                D_800779A8 = (s32)D_800779A4 + 0xFFC;
                ((F576C4)func_800576C4)(2);
                D_800779E4 = ((F576C4)func_800576C4)(1);
            } while (object[0x43] == 0);
        }

        {
            s32 flag = D_8007754C;

            if ((flag != 0) && (object[0x0D] != 0x29)) {
                if (flag & 4) {
                    object[0x12] = 0;
                    object[0x14] = minusOne;
                    object[0x32] |= 0x2000;
                }
                func_8001D8D0(flag);
            }
        }

        func_8001DA00();
        func_8004EC68();
        func_8001D490();
        spSave = (s32*)((u32)spSave + 4);
        spSave = *(s32**)spSave;
        func_800279E8();

        if (object[0x12] == one) {
            object[3] = 4;
            object[0x12] = 0;
            object[1] = 0x2B;
            object[0x14] = 0;
        }

        if (object[0x12] == 2) {
            s32 countdown;
            register s32 nextState asm("v0");

            countdown = object[0x40];
            object[0x12] = 0;
            object[0x15] = countdown;

            if (countdown >= 0x64) {
                object[0x15] = 0x63;
            } else if (countdown < 0) {
                object[0x15] = 0;
            }

            if (object[0xFE] != 0) {
                result = ((object[0xFE] * 0x64) / object[0xFF]) + 2;
                object[0x16] = result;
                if (result >= 0x64) {
                    object[0x16] = 0x63;
                }
            } else {
                object[0x16] = 0;
            }

            if (object[0x0D] == 0x18) {
                func_8005706C(0);
                func_8005706C(6);
                D_80077484 = 0;
                D_80077978 = 0;
                D_800779A8 = 0;
                object[1] = 0xF;
                func_80015224();
                object[3] = 4;
                __asm__ volatile("" ::: "memory");
                object[0x14] = minusOne;
                object[2] = 0;
                nextState = 0x29;
                __asm__ volatile("" : "+r"(nextState));
                object[6] = one;
            } else {
                register s32 flag asm("v0");
                flag = object[0x32] & 0x2000;
                if (!flag) {
                    nextState = 0x2C;
                } else {
                    nextState = 0x29;
                }
            }
            object[1] = nextState;
        }

        if (object[0x10] > 0) {
            continue;
        }

        object[0x10] = 0x384;

        two = 2;
        if (D_80077480 == two) {
            object[1] = one;
            D_80077480 = one;
            continue;
        }

        object[1] = two;
        D_80077480 = two;
        continue;
    }
}
