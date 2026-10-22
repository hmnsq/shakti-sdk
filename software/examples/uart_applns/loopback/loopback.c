// SPDX-License-Identifier: GPL-3.0 only

/*
 * Copyright (C) 2021 Vijai Kumar K <vijai@behindbytes.com>
 *
 * @file loopback.c
 * @brief UART LOOPBACK application.
 */

#ଅନ୍ତର୍ଭାଵ<uart.h>

/*
 * @fn void main()
 * @brief Uart loopback application
 */
ଶୂନ୍ୟ ମୁଖ୍ୟ()
{
    printf("-- UART Loopback Test --\n");
    ଯେତେବେଳେ(1) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା val = getchar();
        putchar(val);
    };
}
