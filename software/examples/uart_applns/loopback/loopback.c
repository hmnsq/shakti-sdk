// SPDX-License-Identifier: GPL-3.0 only

/*
 * Copyright (C) 2021 Vijai Kumar K <vijai@behindbytes.com>
 *
 * @file loopback.c
 * @brief UART LOOPBACK application.
 */

#అన్తర్భావ<uart.h>

/*
 * @fn void main()
 * @brief Uart loopback application
 */
శూన్య ప్రధాన()
{
    రాయి("-- UART Loopback Test --\n");
    అయితే(1) {
        పూర్ణాంకం val = getchar();
        అక్షరం_రాయి(val);
    };
}
