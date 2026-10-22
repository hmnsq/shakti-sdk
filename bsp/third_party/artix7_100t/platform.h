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

#अगर_अघोषित PLATFORM_H
#घोषणा PLATFORM_H

/*
 *@brief RISCV - C CLASS SOC Memory mapping
 */

#घोषणा CLINT_BASE 0x020000000
#घोषणा MTIME      0x0200BFF8
#घोषणा MTIMECMP   0x02004000
#घोषणा CLINT_भाजक   256

#घोषणा CLOCK_FREQUENCY 20000000

#घोषणा MCAUSE_INT         0x80000000
#घोषणा MCAUSE_CAUSE       0x7FFFFFFF

#घोषणा PINMUX_CONFIGURE_REG 0x40310

/*!Debugger Offset */
#घोषणा DBG_MEM_START 0x00000000

/*!Tightly Coupled Memory(TCM) Offset. Size 128mB */
#घोषणा TCM_MEM_START 0x80000000 /*! DDR3 Memory Start address */

/*!Tightly Coupled Memory(TCM) Size. Size 128kB */
#घोषणा TCM_MEM_आकार 0x8000000 /*! DDR3 Memory Size */

/*!Percentage of Free Memory to be used as stack (0-100). The remaining space will be used by heap */
#घोषणा ढेर_PERCENTAGE 50 /*! DDR3 Memory Size */

/*!Percentage of Free Memory to be used as stack (0-100). The remaining space will be used by heap */
#घोषणा HEAP_PERCENTAGE 50 /*! DDR3 Memory Size */

/*!Pulse Width Modulation Start Offsets */
#घोषणा PWM_BASE_ADDRESS 0x00030000 /*PWM Base address*/
#घोषणा PWM_MODULE_OFFSET 0x00000100 /*Offset value to be incremented for each interface*/

/*!Universal Synchronous Receiver Transmitter Interface Offsets */
#घोषणा UART0_START 0x00011300 /*! UART 0 */
#घोषणा UART_OFFSET 0x100
#घोषणा MAX_UART_गिनती 1

#घोषणा PINMUX_CONFIGURE_REG 0x40310

/*! Core Local Interruptor CLINT */


/*! Inter Integrated Circuit (I2C) Interface */
#घोषणा I2C0_BASE 0x020C0000 /*! I2C Start Address */
#घोषणा I2C_OFFSET 0x000
#घोषणा MAX_I2_C_गिनती 1

/*! Programmable Logic Interrupt Interface */
#घोषणा PLIC_BASE_ADDRESS 0x0C000000 /*! PLIC Interface Start */
#घोषणा PLIC_INTERRUPT_1   1
#घोषणा PLIC_INTERRUPT_2   2
#घोषणा PLIC_INTERRUPT_3   3
#घोषणा PLIC_INTERRUPT_4   4
#घोषणा PLIC_INTERRUPT_5   5
#घोषणा PLIC_INTERRUPT_6   6
#घोषणा PLIC_INTERRUPT_7   7
#घोषणा PLIC_INTERRUPT_8   8
#घोषणा PLIC_INTERRUPT_9   9
#घोषणा PLIC_INTERRUPT_10  10
#घोषणा PLIC_INTERRUPT_11  11
#घोषणा PLIC_INTERRUPT_12  12
#घोषणा PLIC_INTERRUPT_13  13
#घोषणा PLIC_INTERRUPT_14  14
#घोषणा PLIC_INTERRUPT_15  15
#घोषणा PLIC_INTERRUPT_16  16
#घोषणा PLIC_INTERRUPT_26  26

#घोषणा PLIC_MAX_INTERRUPT_SRC 26

/*!General Purpose Input / Output */
#घोषणा GPIO_START 0x020D0000 //GPIO Start Address */
#घोषणा GPIO_OFFSET 0x08 /*!Generic offset used to access GPIO registers*/

/*
 * General Purpose IOs supported
 */

#घोषणा GPIO0  (1 <<  0)
#घोषणा GPIO1  (1 <<  1)
#घोषणा GPIO2  (1 <<  2)
#घोषणा GPIO3  (1 <<  3)
#घोषणा GPIO4  (1 <<  4)
#घोषणा GPIO5  (1 <<  5)
#घोषणा GPIO6  (1 <<  6)
#घोषणा GPIO7  (1 <<  7)
#घोषणा GPIO8  (1 <<  8)
#घोषणा GPIO9  (1 <<  9)
#घोषणा GPIO10 (1 << 10)
#घोषणा GPIO11 (1 << 11)
#घोषणा GPIO12 (1 << 12)
#घोषणा GPIO13 (1 << 13)
#घोषणा GPIO14 (1 << 14)
#घोषणा GPIO15 (1 << 15)
#घोषणा GPIO16 (1 << 16)
#घोषणा GPIO17 (1 << 17)
#घोषणा GPIO18 (1 << 18)
#घोषणा GPIO19 (1 << 19)
#घोषणा GPIO20 (1 << 20)
#घोषणा GPIO21 (1 << 21)
#घोषणा GPIO22 (1 << 22)
#घोषणा GPIO23 (1 << 23)
#घोषणा GPIO24 (1 << 24)
#घोषणा GPIO25 (1 << 25)
#घोषणा GPIO26 (1 << 26)
#घोषणा GPIO27 (1 << 27)
#घोषणा GPIO28 (1 << 28)
#घोषणा GPIO29 (1 << 29)
#घोषणा GPIO30 (1 << 30)
#घोषणा GPIO31 (1 << 31)
#घोषणा GPIO_गिनती  0x20
//#define PLIC_GPIO_OFFSET 0

#पूर्ण_अगर
