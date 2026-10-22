// SPDX-License-Identifier: GPL-3.0 only

/*
 * Copyright (C) 2021 Vijai Kumar K <vijai@behindbytes.com>
 *
 * @file loopback.c
 * @brief UART LOOPBACK application.
 */

#अन्तर्भाव<uart.h>

/*
 * @fn void main()
 * @brief Uart loopback application
 */
शून्य main()
{
    printf("-- UART Loopback Test --\n");
    यावत्(1) {
        पूर्णाङ्क val = getchar();
        putchar(val);
    };
}
