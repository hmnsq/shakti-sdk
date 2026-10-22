// SPDX-License-Identifier: GPL-3.0 only

/*
 * Copyright (C) 2021 Vijai Kumar K <vijai@behindbytes.com>
 *
 * @file loopback.c
 * @brief UART LOOPBACK application.
 */

#അന്തര്ഭാവ<uart.h>

/*
 * @fn void main()
 * @brief Uart loopback application
 */
ശൂന്യം പ്രധാന()
{
    printf("-- UART Loopback Test --\n");
    ആകുമ്പോൾ(1) {
        പൂർണ്ണസംഖ്യ val = getchar();
        putchar(val);
    };
}
