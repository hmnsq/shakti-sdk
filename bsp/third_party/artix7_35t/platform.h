/*
platform.h - header file for Artix 35 T E class SoC

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

#यदि_अपरिभाषितम् PLATFORM_H
#परिभाषय PLATFORM_H

/*
 *@brief RISCV - E CLASS SOC Memory mapping
 */

#परिभाषय CLOCK_FREQUENCY 50000000
#परिभाषय CLINT_आधारः 0x020000000
#परिभाषय MTIME      0x0200BFF8
#परिभाषय MTIMECMP   0x02004000
#परिभाषय CLINT_भाजकः   16

#परिभाषय MCAUSE_INT         0x80000000
#परिभाषय MCAUSE_CAUSE       0x7FFFFFFF

#परिभाषय PINMUX_CONFIGURE_REG 0x40310

/*!Debugger Offset */
#परिभाषय DBG_MEM_START 0x00000010

/*!Tightly Coupled Memory(TCM) Offset. Size 128kB */
#परिभाषय TCM_MEM_START 0x80000000 /*! DDR3 Memory Start address */

/*!Tightly Coupled Memory(TCM) Size. Size 128kB */
#परिभाषय TCM_MEM_आकार 0x20000 /*! DDR3 Memory Size */

/*!Percentage of Free Memory to be used as stack (0-100). The remaining space will be used by heap */
#परिभाषय राशिः_PERCENTAGE 50 /*! DDR3 Memory Size */

/*!Percentage of Free Memory to be used as stack (0-100). The remaining space will be used by heap */
#परिभाषय HEAP_PERCENTAGE 50 /*! DDR3 Memory Size */

/*!Pulse Width Modulation Start Offsets */
#परिभाषय PWM_आधारः_स्थानाङ्कः 0x00030000 /*PWM Base address*/
#परिभाषय PWM_MODULE_विस्थापनम् 0x00000100 /*Offset value to be incremented for each interface*/

/*!Serial Peripheral Interface Offsets */
#परिभाषय SPI0_START 0x00020000 /* Serial Peripheral Interface 0 */
#परिभाषय SPI1_START 0x00020100 /* Serial Peripheral Interface 1 */
#परिभाषय SPI2_START 0x00020200 /* Serial Peripheral Interface 2 */

/*!Universal Synchronous Receiver Transmitter Interface Offsets */
#परिभाषय UART0_START 0x00011300 /*! UART 0 */
#परिभाषय UART_विस्थापनम् 0x100
#परिभाषय MAX_UART_गणनम् 3


#परिभाषय PINMUX_CONFIGURE_REG 0x40310

/*! Core Local Interruptor CLINT */


/*! Inter Integrated Circuit (I2C) Interface */
#परिभाषय I2_C0_आधारः 0x00040000 /*! I2C Start Address */
#परिभाषय I2_C_विस्थापनम् 0x000
#परिभाषय MAX_I2_C_गणनम् 1


/*! Programmable Logic Interrupt Interface */
#परिभाषय PLIC_आधारः_स्थानाङ्कः 0x0C000000 /*! PLIC Interface Start */
#परिभाषय PLIC_व्यवधानम्_1   1
#परिभाषय PLIC_व्यवधानम्_2   2
#परिभाषय PLIC_व्यवधानम्_3   3
#परिभाषय PLIC_व्यवधानम्_4   4
#परिभाषय PLIC_व्यवधानम्_5   5
#परिभाषय PLIC_व्यवधानम्_6   6
#परिभाषय PLIC_व्यवधानम्_7   7
#परिभाषय PLIC_व्यवधानम्_8   8
#परिभाषय PLIC_व्यवधानम्_9   9
#परिभाषय PLIC_व्यवधानम्_10  10
#परिभाषय PLIC_व्यवधानम्_11  11
#परिभाषय PLIC_व्यवधानम्_12  12
#परिभाषय PLIC_व्यवधानम्_13  13
#परिभाषय PLIC_व्यवधानम्_14  14
#परिभाषय PLIC_व्यवधानम्_15  15
#परिभाषय PLIC_व्यवधानम्_16  16
#परिभाषय PLIC_व्यवधानम्_25  25 //uart 0
#परिभाषय PLIC_व्यवधानम्_26  26 //uart 1
#परिभाषय PLIC_व्यवधानम्_27  27 //uart 2
#परिभाषय PLIC_MAX_व्यवधानम्_SRC 28


/*!General Purpose Input Output */
#परिभाषय GPIO_START 0x00040100 //GPIO Start Address 
#परिभाषय GPIO_विस्थापनम् 0x08 /*!Generic offset used to access GPIO registers*/
#परिभाषय PLIC_GPIO_विस्थापनम् 6

/*
 * General Purpose IOs supported
 */

#परिभाषय GPIO0  (1 <<  0)
#परिभाषय GPIO1  (1 <<  1)
#परिभाषय GPIO2  (1 <<  2)
#परिभाषय GPIO3  (1 <<  3)
#परिभाषय GPIO4  (1 <<  4)
#परिभाषय GPIO5  (1 <<  5)
#परिभाषय GPIO6  (1 <<  6)
#परिभाषय GPIO7  (1 <<  7)
#परिभाषय GPIO8  (1 <<  8)
#परिभाषय GPIO9  (1 <<  9)
#परिभाषय GPIO10 (1 << 10)
#परिभाषय GPIO11 (1 << 11)
#परिभाषय GPIO12 (1 << 12)
#परिभाषय GPIO13 (1 << 13)
#परिभाषय GPIO14 (1 << 14)
#परिभाषय GPIO15 (1 << 15)
#परिभाषय GPIO16 (1 << 16)
#परिभाषय GPIO17 (1 << 17)
#परिभाषय GPIO18 (1 << 18)
#परिभाषय GPIO19 (1 << 19)
#परिभाषय GPIO20 (1 << 20)
#परिभाषय GPIO21 (1 << 21)
#परिभाषय GPIO22 (1 << 22)
#परिभाषय GPIO23 (1 << 23)
#परिभाषय GPIO24 (1 << 24)
#परिभाषय GPIO25 (1 << 25)
#परिभाषय GPIO26 (1 << 26)
#परिभाषय GPIO27 (1 << 27)
#परिभाषय GPIO28 (1 << 28)
#परिभाषय GPIO29 (1 << 29)
#परिभाषय GPIO30 (1 << 30)
#परिभाषय GPIO31 (1 << 31)
#परिभाषय GPIO_गणनम्  0x20

#यदि_अन्तः
