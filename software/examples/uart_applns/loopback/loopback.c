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
خالی مین()
{
    لکھو("-- UART Loopback Test --\n");
    جب(1) {
        صحیح val = getchar();
        حرف_لکھو(val);
    };
}
