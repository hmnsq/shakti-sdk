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

#جيڪڏهن_وصف_نه_ٿيل PLATFORM_H
#وصف_ڪريو PLATFORM_H

/*
 *@brief RISCV - E CLASS SOC Memory mapping
 */

#وصف_ڪريو CLOCK_FREQUENCY 40000000

/*! Core Local Interruptor CLINT */

#وصف_ڪريو CLINT_بنياد 0x020000000
#وصف_ڪريو MTIME      0x0200BFF8
#وصف_ڪريو MTIMECMP   0x02004000
#وصف_ڪريو CLINT_ورهائيندڙ   16

#وصف_ڪريو MCAUSE_INT         0x80000000
#وصف_ڪريو MCAUSE_CAUSE       0x7FFFFFFF

#وصف_ڪريو PINMUX_CONFIGURE_REG 0x40310

/*!Debugger Offset */
#وصف_ڪريو DBG_MEM_شروعات 0x00000010

/*!Tightly Coupled Memory(TCM) Offset. Size 128kB */
#وصف_ڪريو TCM_MEM_شروعات 0x80000000 /*! DDR3 Memory Start address */

/*!Tightly Coupled Memory(TCM) Size. Size 128kB */
#وصف_ڪريو TCM_MEM_سائيز 0x20000 /*! DDR3 Memory Size */

/*!Percentage of Free Memory to be used as stack (0-100). The remaining space will be used by heap */
#وصف_ڪريو ڍير_PERCENTAGE 50 /*! DDR3 Memory Size */

/*!Percentage of Free Memory to be used as stack (0-100). The remaining space will be used by heap */
#وصف_ڪريو ڍير_PERCENTAGE_2 50 /*! DDR3 Memory Size */

/*!Pulse Width Modulation Start Offsets */
#وصف_ڪريو PWM_بنياد_پتو 0x00030000 /*PWM Base address*/
#وصف_ڪريو PWM_MODULE_وٿي 0x00000100 /*Offset value to be incremented for each interface*/

/*!Serial Peripheral Interface Offsets */
#وصف_ڪريو SPI0_شروعات 0x00020000 /* Serial Peripheral Interface 0 */
#وصف_ڪريو SPI1_شروعات 0x00020100 /* Serial Peripheral Interface 1 */
#وصف_ڪريو SPI2_شروعات 0x00020200 /* Serial Peripheral Interface 2 */

/*!Universal Synchronous Receiver Transmitter Interface Offsets */
#وصف_ڪريو UART0_شروعات 0x00011300 /*! UART 0 */
#وصف_ڪريو UART1_شروعات 0x00011400 /*! UART 1 */
#وصف_ڪريو UART2_شروعات 0x00011500 /*! UART 2 */
#وصف_ڪريو UART_وٿي 0x100
#وصف_ڪريو UART_بنياد 0x11300
#وصف_ڪريو MAX_UART_ڳڻپ 3

#وصف_ڪريو PINMUX_CONFIGURE_REG 0x40310


/*! Inter Integrated Circuit (I2C) Interface */
#وصف_ڪريو I2_C0_بنياد 0x00040000
#وصف_ڪريو I2_C_وٿي 0x400
#وصف_ڪريو MAX_I2_C_ڳڻپ 2

/*! Programmable Logic Interrupt Interface */
#وصف_ڪريو PLIC_بنياد_پتو 0x0C000000 /*! PLIC Interface Start */
#وصف_ڪريو PLIC_مداخلت_1   1
#وصف_ڪريو PLIC_مداخلت_2   2
#وصف_ڪريو PLIC_مداخلت_3   3
#وصف_ڪريو PLIC_مداخلت_4   4
#وصف_ڪريو PLIC_مداخلت_5   5
#وصف_ڪريو PLIC_مداخلت_6   6
#وصف_ڪريو PLIC_مداخلت_7   7
#وصف_ڪريو PLIC_مداخلت_8   8
#وصف_ڪريو PLIC_مداخلت_9   9
#وصف_ڪريو PLIC_مداخلت_10  10
#وصف_ڪريو PLIC_مداخلت_11  11
#وصف_ڪريو PLIC_مداخلت_12  12
#وصف_ڪريو PLIC_مداخلت_13  13
#وصف_ڪريو PLIC_مداخلت_14  14
#وصف_ڪريو PLIC_مداخلت_15  15
#وصف_ڪريو PLIC_مداخلت_16  16
#وصف_ڪريو PLIC_مداخلت_17  17
#وصف_ڪريو PLIC_مداخلت_18  18
#وصف_ڪريو PLIC_مداخلت_19  19
#وصف_ڪريو PLIC_مداخلت_20  20
#وصف_ڪريو PLIC_مداخلت_21  21
#وصف_ڪريو PLIC_مداخلت_22  22
#وصف_ڪريو PLIC_مداخلت_23  23
#وصف_ڪريو PLIC_مداخلت_24  24
#وصف_ڪريو PLIC_مداخلت_25  25 //uart 0
#وصف_ڪريو PLIC_مداخلت_26  26 //uart 1
#وصف_ڪريو PLIC_مداخلت_27  27 //uart 2

#وصف_ڪريو PLIC_MAX_مداخلت_SRC 28

/*!General Purpose Input / Output */
#وصف_ڪريو GPIO_شروعات 0x00040100 //GPIO Start Address */
#وصف_ڪريو GPIO_وٿي 0x08 /*!Generic offset used to access GPIO registers*/
#وصف_ڪريو PLIC_GPIO_وٿي 6

/*
 * General Purpose IOs supported
 */

#وصف_ڪريو GPIO0  (1 <<  0)
#وصف_ڪريو GPIO1  (1 <<  1)
#وصف_ڪريو GPIO2  (1 <<  2)
#وصف_ڪريو GPIO3  (1 <<  3)
#وصف_ڪريو GPIO4  (1 <<  4)
#وصف_ڪريو GPIO5  (1 <<  5)
#وصف_ڪريو GPIO6  (1 <<  6)
#وصف_ڪريو GPIO7  (1 <<  7)
#وصف_ڪريو GPIO8  (1 <<  8)
#وصف_ڪريو GPIO9  (1 <<  9)
#وصف_ڪريو GPIO10 (1 << 10)
#وصف_ڪريو GPIO11 (1 << 11)
#وصف_ڪريو GPIO12 (1 << 12)
#وصف_ڪريو GPIO13 (1 << 13)
#وصف_ڪريو GPIO14 (1 << 14)
#وصف_ڪريو GPIO15 (1 << 15)

#وصف_ڪريو GPIO_ڳڻپ  0x10

#جيڪڏهن_پورو
