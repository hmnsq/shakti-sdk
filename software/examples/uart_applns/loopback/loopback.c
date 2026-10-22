// SPDX-License-Identifier: GPL-3.0 only

/*
 * Copyright (C) 2021 Vijai Kumar K <vijai@behindbytes.com>
 *
 * @file loopback.c
 * @brief UART LOOPBACK application.
 */

#شامل<uart.h>

/*
 * @fn void main()
 * @brief Uart loopback application
 */
تهی اصلی()
{
    printf("-- UART Loopback Test --\n");
    وقتی(1) {
        صحیح val = getchar();
        putchar(val);
    };
}
