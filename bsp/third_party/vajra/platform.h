/*
platform.h - header file for vajra C class SoC on artix7_100t

* Name of Author  : Sathya Narayanan N
* Email ID        : sathya281@gmail.com

 Copyright (C) 2020  IIT Madras. All rights reserved.

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
/*********c-rv64imacsu-100t*********
 SPI   * 2
 GPIO  * 32
 UART  * 3
 I2C   * 2
 PLIC  * 1
 CLINT * 1
 XADC  * 1
 DDR   : 256MB
 Boot
 PWM   * 6
 pinmux
************************************/

#अगर_अघोषित PLATFORM_H
#घोषणा PLATFORM_H

/*
 *@brief RISCV - C CLASS SOC Memory mapping
 */

/*! Core Local Interruptor CLINT */
#घोषणा CLINT_BASE 0x020000000
#घोषणा MTIME      0x0200BFF8
#घोषणा MTIMECMP   0x02004000
#घोषणा CLINT_भाजक   256

#घोषणा CLOCK_FREQUENCY 50000000

/*!Debugger Offset */
#घोषणा DBG_MEM_START 0x00000010

/*!Tightly Coupled Memory(TCM) Offset. Size 256mB */
#घोषणा TCM_MEM_START 0x80000000 /*! DDR3 Memory Start address */
#घोषणा TCM_MEM_आकार 0x10000000 /*! DDR3 Memory Size */

/*!Percentage of Free Memory to be used as stack (0-100). The remaining space will be used by heap */
#घोषणा ढेर_PERCENTAGE 50 /*! DDR3 Memory Size */

/*!Percentage of Free Memory to be used as stack (0-100). The remaining space will be used by heap */
#घोषणा HEAP_PERCENTAGE 50 /*! DDR3 Memory Size */

/*!Pulse Width Modulation Start Offsets */
#घोषणा PWM_BASE_ADDRESS 0x00030000 /*PWM Base address*/
#घोषणा PWM_MODULE_OFFSET 0x00000100 /*Offset value to be incremented for each interface*/

/*!Serial Peripheral Interface Offsets */
#घोषणा SPI0_START 0x00020000 /* Serial Peripheral Interface 0 */
#घोषणा SPI1_START 0x00020100 /* Serial Peripheral Interface 1 */

/*!Universal Synchronous Receiver Transmitter Interface Offsets */
#घोषणा UART0_START 0x00011300 /*! UART 0 */
#घोषणा UART_OFFSET 0x100
#घोषणा MAX_UART_गिनती 3

/*! Inter Integrated Circuit (I2C) Interface */
#घोषणा I2C0_BASE 0x00040000 /*! I2C Start Address */
#घोषणा I2C_OFFSET 0x1400
#घोषणा MAX_I2_C_गिनती 2

/*! Xilinx Analog to Digital converter */
#घोषणा XADC_BASE_ADDRESS 0x00041000

/*!Ethernet */
#घोषणा ETHERNET_BASE 0x00044000

/*! pinmux*/
#घोषणा PINMUX_START 0x41500 
#घोषणा PINMUX_CONFIGURE_REG 0x41510

/*! Programmable Logic Interrupt Interface */
#घोषणा PLIC_BASE_ADDRESS 0x0C000000 /*! PLIC Interface Start */
#घोषणा PLIC_INTERRUPT_1   1	/* PWM 0   */
#घोषणा PLIC_INTERRUPT_2   2	/* PWM 1   */
#घोषणा PLIC_INTERRUPT_3   3	/* PWM 2   */
#घोषणा PLIC_INTERRUPT_4   4	/* PWM 3   */
#घोषणा PLIC_INTERRUPT_5   5	/* PWM 4   */
#घोषणा PLIC_INTERRUPT_6   6	/* PWM 5   */
#घोषणा PLIC_INTERRUPT_7   7	/* GPIO 0  */
#घोषणा PLIC_INTERRUPT_8   8	/* GPIO 1  */
#घोषणा PLIC_INTERRUPT_9   9	/* GPIO 2  */
#घोषणा PLIC_INTERRUPT_10  10	/* GPIO 3  */
#घोषणा PLIC_INTERRUPT_11  11	/* GPIO 4  */
#घोषणा PLIC_INTERRUPT_12  12	/* GPIO 5  */
#घोषणा PLIC_INTERRUPT_13  13	/* GPIO 6  */
#घोषणा PLIC_INTERRUPT_14  14	/* GPIO 7  */
#घोषणा PLIC_INTERRUPT_15  15	/* GPIO 8  */
#घोषणा PLIC_INTERRUPT_16  16	/* GPIO 9  */
#घोषणा PLIC_INTERRUPT_17  17	/* GPIO 10 */
#घोषणा PLIC_INTERRUPT_18  18	/* GPIO 11 */
#घोषणा PLIC_INTERRUPT_19  19	/* GPIO 12 */
#घोषणा PLIC_INTERRUPT_20  20	/* GPIO 13 */
#घोषणा PLIC_INTERRUPT_21  21	/* GPIO 14 */
#घोषणा PLIC_INTERRUPT_22  22	/* GPIO 15 */
#घोषणा PLIC_INTERRUPT_23  23	/* I2C 0   */
#घोषणा PLIC_INTERRUPT_24  24	/* I2C 1   */
#घोषणा PLIC_INTERRUPT_25  25 	/* uart 0  */
#घोषणा PLIC_INTERRUPT_26  26 	/* uart 1  */
#घोषणा PLIC_INTERRUPT_27  27 	/* uart 2  */
#घोषणा PLIC_MAX_INTERRUPT_SRC 28

/*!General Purpose Input / Output */
#घोषणा GPIO_START 0x00040100 //GPIO Start Address */
#घोषणा GPIO_OFFSET 0x08 /*!Generic offset used to access GPIO registers*/
#घोषणा PLIC_GPIO_OFFSET 6

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

#पूर्ण_अगर
