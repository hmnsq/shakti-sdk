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
void основной()
{
    printf("-- UART Loopback Test --\n");
    пока(1) {
        целое val = getchar();
        putchar(val);
    };
}
