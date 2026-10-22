// SPDX-License-Identifier: GPL-3.0 only

/*
 * Copyright (C) 2021 Vijai Kumar K <vijai@behindbytes.com>
 *
 * @file loopback.c
 * @brief UART LOOPBACK application.
 */

#અન્તર્ભાવ<uart.h>

/*
 * @fn void main()
 * @brief Uart loopback application
 */
શૂન્ય મુખ્ય()
{
    printf("-- UART Loopback Test --\n");
    જ્યારે(1) {
        પૂર્ણાંક val = getchar();
        putchar(val);
    };
}
