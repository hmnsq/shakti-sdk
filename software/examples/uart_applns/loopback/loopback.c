// SPDX-License-Identifier: GPL-3.0 only

/*
 * Copyright (C) 2021 Vijai Kumar K <vijai@behindbytes.com>
 *
 * @file loopback.c
 * @brief UART LOOPBACK application.
 */

#ضمن<uart.h>

/*
 * @fn void main()
 * @brief Uart loopback application
 */
فراغ مکھ()
{
    لکھو("-- UART Loopback Test --\n");
    طالما(1) {
        صحيح val = getchar();
        حرف_لکھو(val);
    };
}
