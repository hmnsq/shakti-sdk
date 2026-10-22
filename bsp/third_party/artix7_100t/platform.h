/*
platform.h - header file for Artix 100T C class SoC

* Name of Author : Sathya Narayanan N
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
 *@brief RISCV - C CLASS SOC Memory mapping
 */

#تعریف_کرو CLINT_ادھار 0x020000000
#تعریف_کرو MTIME      0x0200BFF8
#تعریف_کرو MTIMECMP   0x02004000
#تعریف_کرو CLINT_مقسوم_علیہ   256

#تعریف_کرو CLOCK_FREQUENCY 20000000

#تعریف_کرو MCAUSE_INT         0x80000000
#تعریف_کرو MCAUSE_CAUSE       0x7FFFFFFF

#تعریف_کرو PINMUX_CONFIGURE_REG 0x40310

/*!Debugger Offset */
#تعریف_کرو DBG_MEM_شروع 0x00000000

/*!Tightly Coupled Memory(TCM) Offset. Size 128mB */
#تعریف_کرو TCM_MEM_شروع 0x80000000 /*! DDR3 Memory Start address */

/*!Tightly Coupled Memory(TCM) Size. Size 128kB */
#تعریف_کرو TCM_MEM_ناپ 0x8000000 /*! DDR3 Memory Size */

/*!Percentage of Free Memory to be used as stack (0-100). The remaining space will be used by heap */
#تعریف_کرو ڈھیر_PERCENTAGE 50 /*! DDR3 Memory Size */

/*!Percentage of Free Memory to be used as stack (0-100). The remaining space will be used by heap */
#تعریف_کرو ڈھیر_PERCENTAGE_2 50 /*! DDR3 Memory Size */

/*!Pulse Width Modulation Start Offsets */
#تعریف_کرو PWM_ادھار_پتہ 0x00030000 /*PWM Base address*/
#تعریف_کرو PWM_MODULE_وتھ 0x00000100 /*Offset value to be incremented for each interface*/

/*!Universal Synchronous Receiver Transmitter Interface Offsets */
#تعریف_کرو UART0_شروع 0x00011300 /*! UART 0 */
#تعریف_کرو UART_وتھ 0x100
#تعریف_کرو MAX_UART_گنتی 1

#تعریف_کرو PINMUX_CONFIGURE_REG 0x40310

/*! Core Local Interruptor CLINT */


/*! Inter Integrated Circuit (I2C) Interface */
#تعریف_کرو I2_C0_ادھار 0x020C0000 /*! I2C Start Address */
#تعریف_کرو I2_C_وتھ 0x000
#تعریف_کرو MAX_I2_C_گنتی 1

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
#تعریف_کرو PLIC_رکاوٹ_26  26

#تعریف_کرو PLIC_MAX_رکاوٹ_SRC 26

/*!General Purpose Input / Output */
#تعریف_کرو GPIO_شروع 0x020D0000 //GPIO Start Address */
#تعریف_کرو GPIO_وتھ 0x08 /*!Generic offset used to access GPIO registers*/

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
#تعریف_کرو GPIO16 (1 << 16)
#تعریف_کرو GPIO17 (1 << 17)
#تعریف_کرو GPIO18 (1 << 18)
#تعریف_کرو GPIO19 (1 << 19)
#تعریف_کرو GPIO20 (1 << 20)
#تعریف_کرو GPIO21 (1 << 21)
#تعریف_کرو GPIO22 (1 << 22)
#تعریف_کرو GPIO23 (1 << 23)
#تعریف_کرو GPIO24 (1 << 24)
#تعریف_کرو GPIO25 (1 << 25)
#تعریف_کرو GPIO26 (1 << 26)
#تعریف_کرو GPIO27 (1 << 27)
#تعریف_کرو GPIO28 (1 << 28)
#تعریف_کرو GPIO29 (1 << 29)
#تعریف_کرو GPIO30 (1 << 30)
#تعریف_کرو GPIO31 (1 << 31)
#تعریف_کرو GPIO_گنتی  0x20
//#define PLIC_GPIO_OFFSET 0

#جے_انت
