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
void หลัก()
{
    printf("-- UART Loopback Test --\n");
    ขณะ(1) {
        จำนวนเต็ม val = getchar();
        putchar(val);
    };
}
