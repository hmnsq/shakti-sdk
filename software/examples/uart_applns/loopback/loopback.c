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
শূন্য প্রধান()
{
    printf("-- UART Loopback Test --\n");
    যখন(1) {
        পূর্ণসংখ্যা val = getchar();
        putchar(val);
    };
}
