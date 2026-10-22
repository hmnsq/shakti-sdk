// SPDX-License-Identifier: GPL-3.0 only

/*
 * Copyright (C) 2021 Vijai Kumar K <vijai@behindbytes.com>
 *
 * @file loopback.c
 * @brief UART LOOPBACK application.
 */

#ਅਨ੍ਤਰ੍ਭਾਵ<uart.h>

/*
 * @fn void main()
 * @brief Uart loopback application
 */
ਖਾਲੀ ਮੁੱਖ()
{
    ਲਿਖੋ("-- UART Loopback Test --\n");
    ਜਦੋਂ(1) {
        ਪੂਰਨ val = getchar();
        ਅੱਖਰ_ਲਿਖੋ(val);
    };
}
