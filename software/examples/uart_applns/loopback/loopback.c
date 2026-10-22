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
ಶೂನ್ಯ ಮುಖ್ಯ()
{
    ಬರೆ("-- UART Loopback Test --\n");
    ಆಗ(1) {
        ಪೂರ್ಣಾಂಕ val = getchar();
        ಅಕ್ಷರ_ಬರೆ(val);
    };
}
