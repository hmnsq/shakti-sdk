// SPDX-License-Identifier: GPL-3.0 only

/*
 * Copyright (C) 2021 Vijai Kumar K <vijai@behindbytes.com>
 *
 * @file loopback.c
 * @brief UART LOOPBACK application.
 */

#include<uart.h>

/*
 * @fn void main()
 * @brief Uart loopback application
 */
void 主要()
{
    printf("-- UART Loopback Test --\n");
    当(1) {
        整数 val = getchar();
        putchar(val);
    };
}
