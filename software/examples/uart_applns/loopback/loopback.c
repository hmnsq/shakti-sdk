// SPDX-License-Identifier: GPL-3.0 only

/*
 * Copyright (C) 2021 Vijai Kumar K <vijai@behindbytes.com>
 *
 * @file loopback.c
 * @brief UART LOOPBACK application.
 */

#ಅನ್ತರ್ಭಾವ<uart.h>

/*
 * @fn void main()
 * @brief Uart loopback application
 */
ಶೂನ್ಯ main()
{
    printf("-- UART Loopback Test --\n");
    ಯಾವತ್(1) {
        ಪೂರ್ಣಾಙ್ಕ val = getchar();
        putchar(val);
    };
}
