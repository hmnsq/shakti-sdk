// SPDX-License-Identifier: GPL-3.0 only

/*
 * Copyright (C) 2021 Vijai Kumar K <vijai@behindbytes.com>
 *
 * @file loopback.c
 * @brief UART LOOPBACK application.
 */

#அந்தர்பாவ<uart.h>

/*
 * @fn void main()
 * @brief Uart loopback application
 */
வெறுமை முதன்மை()
{
    printf("-- UART Loopback Test --\n");
    போது(1) {
        முழு val = getchar();
        putchar(val);
    };
}
