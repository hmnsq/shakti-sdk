// SPDX-License-Identifier: GPL-3.0 only

/*
 * Copyright (C) 2021 Vijai Kumar K <vijai@behindbytes.com>
 *
 * @file loopback.c
 * @brief UART LOOPBACK application.
 */

#অন্তর্ভাব<uart.h>

/*
 * @fn void main()
 * @brief Uart loopback application
 */
শূন্য main()
{
    printf("-- UART Loopback Test --\n");
    যাবত্(1) {
        পূর্ণাঙ্ক val = getchar();
        putchar(val);
    };
}
