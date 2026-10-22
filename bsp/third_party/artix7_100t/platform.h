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

#اگر_تعریف_نشده PLATFORM_H
#تعریف_کن PLATFORM_H

/*
 *@brief RISCV - C CLASS SOC Memory mapping
 */

#تعریف_کن CLINT_پایه 0x020000000
#تعریف_کن MTIME      0x0200BFF8
#تعریف_کن MTIMECMP   0x02004000
#تعریف_کن CLINT_مقسوم_علیه   256

#تعریف_کن CLOCK_FREQUENCY 20000000

#تعریف_کن MCAUSE_INT         0x80000000
#تعریف_کن MCAUSE_CAUSE       0x7FFFFFFF

#تعریف_کن PINMUX_CONFIGURE_REG 0x40310

/*!Debugger Offset */
#تعریف_کن DBG_MEM_شروع 0x00000000

/*!Tightly Coupled Memory(TCM) Offset. Size 128mB */
#تعریف_کن TCM_MEM_شروع 0x80000000 /*! DDR3 Memory Start address */

/*!Tightly Coupled Memory(TCM) Size. Size 128kB */
#تعریف_کن TCM_MEM_اندازه 0x8000000 /*! DDR3 Memory Size */

/*!Percentage of Free Memory to be used as stack (0-100). The remaining space will be used by heap */
#تعریف_کن پشته_PERCENTAGE 50 /*! DDR3 Memory Size */

/*!Percentage of Free Memory to be used as stack (0-100). The remaining space will be used by heap */
#تعریف_کن انباشته_PERCENTAGE 50 /*! DDR3 Memory Size */

/*!Pulse Width Modulation Start Offsets */
#تعریف_کن PWM_پایه_آدرس 0x00030000 /*PWM Base address*/
#تعریف_کن PWM_MODULE_جابه_جایی 0x00000100 /*Offset value to be incremented for each interface*/

/*!Universal Synchronous Receiver Transmitter Interface Offsets */
#تعریف_کن UART0_شروع 0x00011300 /*! UART 0 */
#تعریف_کن UART_جابه_جایی 0x100
#تعریف_کن MAX_UART_شمار 1

#تعریف_کن PINMUX_CONFIGURE_REG 0x40310

/*! Core Local Interruptor CLINT */


/*! Inter Integrated Circuit (I2C) Interface */
#تعریف_کن I2_C0_پایه 0x020C0000 /*! I2C Start Address */
#تعریف_کن I2_C_جابه_جایی 0x000
#تعریف_کن MAX_I2_C_شمار 1

/*! Programmable Logic Interrupt Interface */
#تعریف_کن PLIC_پایه_آدرس 0x0C000000 /*! PLIC Interface Start */
#تعریف_کن PLIC_وقفه_1   1
#تعریف_کن PLIC_وقفه_2   2
#تعریف_کن PLIC_وقفه_3   3
#تعریف_کن PLIC_وقفه_4   4
#تعریف_کن PLIC_وقفه_5   5
#تعریف_کن PLIC_وقفه_6   6
#تعریف_کن PLIC_وقفه_7   7
#تعریف_کن PLIC_وقفه_8   8
#تعریف_کن PLIC_وقفه_9   9
#تعریف_کن PLIC_وقفه_10  10
#تعریف_کن PLIC_وقفه_11  11
#تعریف_کن PLIC_وقفه_12  12
#تعریف_کن PLIC_وقفه_13  13
#تعریف_کن PLIC_وقفه_14  14
#تعریف_کن PLIC_وقفه_15  15
#تعریف_کن PLIC_وقفه_16  16
#تعریف_کن PLIC_وقفه_26  26

#تعریف_کن PLIC_MAX_وقفه_SRC 26

/*!General Purpose Input / Output */
#تعریف_کن GPIO_شروع 0x020D0000 //GPIO Start Address */
#تعریف_کن GPIO_جابه_جایی 0x08 /*!Generic offset used to access GPIO registers*/

/*
 * General Purpose IOs supported
 */

#تعریف_کن GPIO0  (1 <<  0)
#تعریف_کن GPIO1  (1 <<  1)
#تعریف_کن GPIO2  (1 <<  2)
#تعریف_کن GPIO3  (1 <<  3)
#تعریف_کن GPIO4  (1 <<  4)
#تعریف_کن GPIO5  (1 <<  5)
#تعریف_کن GPIO6  (1 <<  6)
#تعریف_کن GPIO7  (1 <<  7)
#تعریف_کن GPIO8  (1 <<  8)
#تعریف_کن GPIO9  (1 <<  9)
#تعریف_کن GPIO10 (1 << 10)
#تعریف_کن GPIO11 (1 << 11)
#تعریف_کن GPIO12 (1 << 12)
#تعریف_کن GPIO13 (1 << 13)
#تعریف_کن GPIO14 (1 << 14)
#تعریف_کن GPIO15 (1 << 15)
#تعریف_کن GPIO16 (1 << 16)
#تعریف_کن GPIO17 (1 << 17)
#تعریف_کن GPIO18 (1 << 18)
#تعریف_کن GPIO19 (1 << 19)
#تعریف_کن GPIO20 (1 << 20)
#تعریف_کن GPIO21 (1 << 21)
#تعریف_کن GPIO22 (1 << 22)
#تعریف_کن GPIO23 (1 << 23)
#تعریف_کن GPIO24 (1 << 24)
#تعریف_کن GPIO25 (1 << 25)
#تعریف_کن GPIO26 (1 << 26)
#تعریف_کن GPIO27 (1 << 27)
#تعریف_کن GPIO28 (1 << 28)
#تعریف_کن GPIO29 (1 << 29)
#تعریف_کن GPIO30 (1 << 30)
#تعریف_کن GPIO31 (1 << 31)
#تعریف_کن GPIO_شمار  0x20
//#define PLIC_GPIO_OFFSET 0

#پایان_اگر
