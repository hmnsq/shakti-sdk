/*
platform.h - header file for moushik E class SoC

* Name of Author :  Sathya Narayanan N
* Email ID       : sathya281@gmail.com

 Copyright (C) 2019  IIT Madras. All rights reserved.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#جے_بنا_تعریف PLATFORM_H
#تعریف_کرو PLATFORM_H

/*
 *@brief RISCV - E CLASS SOC Memory mapping
 */

#تعریف_کرو CLOCK_FREQUENCY 40000000

/*! Core Local Interruptor CLINT */

#تعریف_کرو CLINT_ادھار 0x020000000
#تعریف_کرو MTIME      0x0200BFF8
#تعریف_کرو MTIMECMP   0x02004000
#تعریف_کرو CLINT_مقسوم_علیہ   16

#تعریف_کرو MCAUSE_INT         0x80000000
#تعریف_کرو MCAUSE_CAUSE       0x7FFFFFFF

#تعریف_کرو PINMUX_CONFIGURE_REG 0x40310

/*!Debugger Offset */
#تعریف_کرو DBG_MEM_شروع 0x00000010

/*!Tightly Coupled Memory(TCM) Offset. Size 128kB */
#تعریف_کرو TCM_MEM_شروع 0x80000000 /*! DDR3 Memory Start address */

/*!Tightly Coupled Memory(TCM) Size. Size 128kB */
#تعریف_کرو TCM_MEM_ناپ 0x20000 /*! DDR3 Memory Size */

/*!Percentage of Free Memory to be used as stack (0-100). The remaining space will be used by heap */
#تعریف_کرو ڈھیر_PERCENTAGE 50 /*! DDR3 Memory Size */

/*!Percentage of Free Memory to be used as stack (0-100). The remaining space will be used by heap */
#تعریف_کرو ڈھیر_PERCENTAGE_2 50 /*! DDR3 Memory Size */

/*!Pulse Width Modulation Start Offsets */
#تعریف_کرو PWM_ادھار_پتہ 0x00030000 /*PWM Base address*/
#تعریف_کرو PWM_MODULE_وتھ 0x00000100 /*Offset value to be incremented for each interface*/

/*!Serial Peripheral Interface Offsets */
#تعریف_کرو SPI0_شروع 0x00020000 /* Serial Peripheral Interface 0 */
#تعریف_کرو SPI1_شروع 0x00020100 /* Serial Peripheral Interface 1 */
#تعریف_کرو SPI2_شروع 0x00020200 /* Serial Peripheral Interface 2 */

/*!Universal Synchronous Receiver Transmitter Interface Offsets */
#تعریف_کرو UART0_شروع 0x00011300 /*! UART 0 */
#تعریف_کرو UART1_شروع 0x00011400 /*! UART 1 */
#تعریف_کرو UART2_شروع 0x00011500 /*! UART 2 */
#تعریف_کرو UART_وتھ 0x100
#تعریف_کرو UART_ادھار 0x11300
#تعریف_کرو MAX_UART_گنتی 3

#تعریف_کرو PINMUX_CONFIGURE_REG 0x40310


/*! Inter Integrated Circuit (I2C) Interface */
#تعریف_کرو I2_C0_ادھار 0x00040000
#تعریف_کرو I2_C_وتھ 0x400
#تعریف_کرو MAX_I2_C_گنتی 2

/*! Programmable Logic Interrupt Interface */
#تعریف_کرو PLIC_ادھار_پتہ 0x0C000000 /*! PLIC Interface Start */
#تعریف_کرو PLIC_رکاوٹ_1   1
#تعریف_کرو PLIC_رکاوٹ_2   2
#تعریف_کرو PLIC_رکاوٹ_3   3
#تعریف_کرو PLIC_رکاوٹ_4   4
#تعریف_کرو PLIC_رکاوٹ_5   5
#تعریف_کرو PLIC_رکاوٹ_6   6
#تعریف_کرو PLIC_رکاوٹ_7   7
#تعریف_کرو PLIC_رکاوٹ_8   8
#تعریف_کرو PLIC_رکاوٹ_9   9
#تعریف_کرو PLIC_رکاوٹ_10  10
#تعریف_کرو PLIC_رکاوٹ_11  11
#تعریف_کرو PLIC_رکاوٹ_12  12
#تعریف_کرو PLIC_رکاوٹ_13  13
#تعریف_کرو PLIC_رکاوٹ_14  14
#تعریف_کرو PLIC_رکاوٹ_15  15
#تعریف_کرو PLIC_رکاوٹ_16  16
#تعریف_کرو PLIC_رکاوٹ_17  17
#تعریف_کرو PLIC_رکاوٹ_18  18
#تعریف_کرو PLIC_رکاوٹ_19  19
#تعریف_کرو PLIC_رکاوٹ_20  20
#تعریف_کرو PLIC_رکاوٹ_21  21
#تعریف_کرو PLIC_رکاوٹ_22  22
#تعریف_کرو PLIC_رکاوٹ_23  23
#تعریف_کرو PLIC_رکاوٹ_24  24
#تعریف_کرو PLIC_رکاوٹ_25  25 //uart 0
#تعریف_کرو PLIC_رکاوٹ_26  26 //uart 1
#تعریف_کرو PLIC_رکاوٹ_27  27 //uart 2

#تعریف_کرو PLIC_MAX_رکاوٹ_SRC 28

/*!General Purpose Input / Output */
#تعریف_کرو GPIO_شروع 0x00040100 //GPIO Start Address */
#تعریف_کرو GPIO_وتھ 0x08 /*!Generic offset used to access GPIO registers*/
#تعریف_کرو PLIC_GPIO_وتھ 6

/*
 * General Purpose IOs supported
 */

#تعریف_کرو GPIO0  (1 <<  0)
#تعریف_کرو GPIO1  (1 <<  1)
#تعریف_کرو GPIO2  (1 <<  2)
#تعریف_کرو GPIO3  (1 <<  3)
#تعریف_کرو GPIO4  (1 <<  4)
#تعریف_کرو GPIO5  (1 <<  5)
#تعریف_کرو GPIO6  (1 <<  6)
#تعریف_کرو GPIO7  (1 <<  7)
#تعریف_کرو GPIO8  (1 <<  8)
#تعریف_کرو GPIO9  (1 <<  9)
#تعریف_کرو GPIO10 (1 << 10)
#تعریف_کرو GPIO11 (1 << 11)
#تعریف_کرو GPIO12 (1 << 12)
#تعریف_کرو GPIO13 (1 << 13)
#تعریف_کرو GPIO14 (1 << 14)
#تعریف_کرو GPIO15 (1 << 15)

#تعریف_کرو GPIO_گنتی  0x10

#جے_انت
