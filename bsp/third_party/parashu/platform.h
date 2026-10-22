/*
platform.h - header file for parashu E class SoC on artix7_100t

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
/***********e-rv32imac-100t******
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
*********************************/

#که_نه_تعریف_شوی PLATFORM_H
#تعریف_کړه PLATFORM_H

/*
 *@brief RISCV - E CLASS SOC Memory mapping
 */

/*! Core Local Interruptor CLINT */
#تعریف_کړه CLINT_بنسټ 0x020000000
#تعریف_کړه MTIME      0x0200BFF8
#تعریف_کړه MTIMECMP   0x02004000
#تعریف_کړه CLINT_وېشونکی   256

#تعریف_کړه CLOCK_FREQUENCY 50000000

/*!Debugger Offset */
#تعریف_کړه DBG_MEM_پیل 0x00000010

/*!Tightly Coupled Memory(TCM) Offset. Size 256mB */
#تعریف_کړه TCM_MEM_پیل 0x80000000 /*! DDR3 Memory Start address */
#تعریف_کړه TCM_MEM_اندازه 0x10000000 /*! DDR3 Memory Size */

/*!Percentage of Free Memory to be used as stack (0-100). The remaining space will be used by heap */
#تعریف_کړه ډېری_PERCENTAGE 50 /*! DDR3 Memory Size */

/*!Percentage of Free Memory to be used as stack (0-100). The remaining space will be used by heap */
#تعریف_کړه ډېرۍ_PERCENTAGE 50 /*! DDR3 Memory Size */

/*!Pulse Width Modulation Start Offsets */
#تعریف_کړه PWM_بنسټ_پته 0x00030000 /*PWM Base address*/
#تعریف_کړه PWM_MODULE_دننه_واټن 0x00000100 /*Offset value to be incremented for each interface*/

/*!Serial Peripheral Interface Offsets */
#تعریف_کړه SPI0_پیل 0x00020000 /* Serial Peripheral Interface 0 */
#تعریف_کړه SPI1_پیل 0x00020100 /* Serial Peripheral Interface 1 */

/*!Universal Synchronous Receiver Transmitter Interface Offsets */
#تعریف_کړه UART0_پیل 0x00011300 /*! UART 0 */
#تعریف_کړه UART_دننه_واټن 0x100
#تعریف_کړه MAX_UART_شمېر 3

/*! Inter Integrated Circuit (I2C) Interface */
#تعریف_کړه I2_C0_بنسټ 0x00040000 /*! I2C Start Address */
#تعریف_کړه I2_C_دننه_واټن 0x1400
#تعریف_کړه MAX_I2_C_شمېر 2

/*! Xilinx Analog to Digital converter */
#تعریف_کړه XADC_بنسټ_پته 0x00041000

/*! pinmux*/
#تعریف_کړه PINMUX_پیل 0x41500 
#تعریف_کړه PINMUX_CONFIGURE_REG 0x41510

/*! Programmable Logic Interrupt Interface */
#تعریف_کړه PLIC_بنسټ_پته 0x0C000000 /*! PLIC Interface Start */
#تعریف_کړه PLIC_مداخله_1   1	/* PWM 0   */
#تعریف_کړه PLIC_مداخله_2   2	/* PWM 1   */
#تعریف_کړه PLIC_مداخله_3   3	/* PWM 2   */
#تعریف_کړه PLIC_مداخله_4   4	/* PWM 3   */
#تعریف_کړه PLIC_مداخله_5   5	/* PWM 4   */
#تعریف_کړه PLIC_مداخله_6   6	/* PWM 5   */
#تعریف_کړه PLIC_مداخله_7   7	/* GPIO 0  */
#تعریف_کړه PLIC_مداخله_8   8	/* GPIO 1  */
#تعریف_کړه PLIC_مداخله_9   9	/* GPIO 2  */
#تعریف_کړه PLIC_مداخله_10  10	/* GPIO 3  */
#تعریف_کړه PLIC_مداخله_11  11	/* GPIO 4  */
#تعریف_کړه PLIC_مداخله_12  12	/* GPIO 5  */
#تعریف_کړه PLIC_مداخله_13  13	/* GPIO 6  */
#تعریف_کړه PLIC_مداخله_14  14	/* GPIO 7  */
#تعریف_کړه PLIC_مداخله_15  15	/* GPIO 8  */
#تعریف_کړه PLIC_مداخله_16  16	/* GPIO 9  */
#تعریف_کړه PLIC_مداخله_17  17	/* GPIO 10 */
#تعریف_کړه PLIC_مداخله_18  18	/* GPIO 11 */
#تعریف_کړه PLIC_مداخله_19  19	/* GPIO 12 */
#تعریف_کړه PLIC_مداخله_20  20	/* GPIO 13 */
#تعریف_کړه PLIC_مداخله_21  21	/* GPIO 14 */
#تعریف_کړه PLIC_مداخله_22  22	/* GPIO 15 */
#تعریف_کړه PLIC_مداخله_23  23	/* I2C 0   */
#تعریف_کړه PLIC_مداخله_24  24	/* I2C 1   */
#تعریف_کړه PLIC_مداخله_25  25 	/* uart 0  */
#تعریف_کړه PLIC_مداخله_26  26 	/* uart 1  */
#تعریف_کړه PLIC_مداخله_27  27 	/* uart 2  */
#تعریف_کړه PLIC_MAX_مداخله_SRC 28

/*!General Purpose Input / Output */
#تعریف_کړه GPIO_پیل 0x00040100 //GPIO Start Address */
#تعریف_کړه GPIO_دننه_واټن 0x08 /*!Generic offset used to access GPIO registers*/
#تعریف_کړه PLIC_GPIO_دننه_واټن 6

/*
 * General Purpose IOs supported
 */

#تعریف_کړه GPIO0  (1 <<  0)
#تعریف_کړه GPIO1  (1 <<  1)
#تعریف_کړه GPIO2  (1 <<  2)
#تعریف_کړه GPIO3  (1 <<  3)
#تعریف_کړه GPIO4  (1 <<  4)
#تعریف_کړه GPIO5  (1 <<  5)
#تعریف_کړه GPIO6  (1 <<  6)
#تعریف_کړه GPIO7  (1 <<  7)
#تعریف_کړه GPIO8  (1 <<  8)
#تعریف_کړه GPIO9  (1 <<  9)
#تعریف_کړه GPIO10 (1 << 10)
#تعریف_کړه GPIO11 (1 << 11)
#تعریف_کړه GPIO12 (1 << 12)
#تعریف_کړه GPIO13 (1 << 13)
#تعریف_کړه GPIO14 (1 << 14)
#تعریف_کړه GPIO15 (1 << 15)
#تعریف_کړه GPIO16 (1 << 16)
#تعریف_کړه GPIO17 (1 << 17)
#تعریف_کړه GPIO18 (1 << 18)
#تعریف_کړه GPIO19 (1 << 19)
#تعریف_کړه GPIO20 (1 << 20)
#تعریف_کړه GPIO21 (1 << 21)
#تعریف_کړه GPIO22 (1 << 22)
#تعریف_کړه GPIO23 (1 << 23)
#تعریف_کړه GPIO24 (1 << 24)
#تعریف_کړه GPIO25 (1 << 25)
#تعریف_کړه GPIO26 (1 << 26)
#تعریف_کړه GPIO27 (1 << 27)
#تعریف_کړه GPIO28 (1 << 28)
#تعریف_کړه GPIO29 (1 << 29)
#تعریف_کړه GPIO30 (1 << 30)
#تعریف_کړه GPIO31 (1 << 31)
#تعریف_کړه GPIO_شمېر  0x20

#د_که_پای
