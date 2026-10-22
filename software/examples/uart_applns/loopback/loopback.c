// SPDX-License-Identifier: GPL-3.0 only

/*
 * Copyright (C) 2021 Vijai Kumar K <vijai@behindbytes.com>
 *
 * @file loopback.c
 * @brief UART LOOPBACK application.
 */

#समावेश<uart.h>

/*
 * @fn void main()
 * @brief Uart loopback application
 */
व्योम मुख्य()
{
    म_लिखो("-- UART Loopback Test --\n");
    जबतक(1) {
        पूर्णांक val = अक्षर_लो();
        अक्षर_दो(val);
    };
}
