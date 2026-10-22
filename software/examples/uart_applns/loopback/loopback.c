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
    म_लिखो("-- UART Loopback Test --\n");
    जबसम्म(1) {
        पूर्णाङ्क val = अक्षर_लो();
        अक्षर_दो(val);
    };
}
