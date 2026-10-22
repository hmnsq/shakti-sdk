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

#اگر_تعریف_نشده PLATFORM_H
#تعریف_کن PLATFORM_H

/*
 *@brief RISCV - E CLASS SOC Memory mapping
 */

/*! Core Local Interruptor CLINT */
#تعریف_کن CLINT_پایه 0x020000000
#تعریف_کن MTIME      0x0200BFF8
#تعریف_کن MTIMECMP   0x02004000
#تعریف_کن CLINT_مقسوم_علیه   256

#تعریف_کن CLOCK_FREQUENCY 50000000

/*!Debugger Offset */
#تعریف_کن DBG_MEM_شروع 0x00000010

/*!Tightly Coupled Memory(TCM) Offset. Size 256mB */
#تعریف_کن TCM_MEM_شروع 0x80000000 /*! DDR3 Memory Start address */
#تعریف_کن TCM_MEM_اندازه 0x10000000 /*! DDR3 Memory Size */

/*!Percentage of Free Memory to be used as stack (0-100). The remaining space will be used by heap */
#تعریف_کن پشته_PERCENTAGE 50 /*! DDR3 Memory Size */

/*!Percentage of Free Memory to be used as stack (0-100). The remaining space will be used by heap */
#تعریف_کن انباشته_PERCENTAGE 50 /*! DDR3 Memory Size */

/*!Pulse Width Modulation Start Offsets */
#تعریف_کن PWM_پایه_آدرس 0x00030000 /*PWM Base address*/
#تعریف_کن PWM_MODULE_جابه_جایی 0x00000100 /*Offset value to be incremented for each interface*/

/*!Serial Peripheral Interface Offsets */
#تعریف_کن SPI0_شروع 0x00020000 /* Serial Peripheral Interface 0 */
#تعریف_کن SPI1_شروع 0x00020100 /* Serial Peripheral Interface 1 */

/*!Universal Synchronous Receiver Transmitter Interface Offsets */
#تعریف_کن UART0_شروع 0x00011300 /*! UART 0 */
#تعریف_کن UART_جابه_جایی 0x100
#تعریف_کن MAX_UART_شمار 3

/*! Inter Integrated Circuit (I2C) Interface */
#تعریف_کن I2_C0_پایه 0x00040000 /*! I2C Start Address */
#تعریف_کن I2_C_جابه_جایی 0x1400
#تعریف_کن MAX_I2_C_شمار 2

/*! Xilinx Analog to Digital converter */
#تعریف_کن XADC_پایه_آدرس 0x00041000

/*! pinmux*/
#تعریف_کن PINMUX_شروع 0x41500 
#تعریف_کن PINMUX_CONFIGURE_REG 0x41510

/*! Programmable Logic Interrupt Interface */
#تعریف_کن PLIC_پایه_آدرس 0x0C000000 /*! PLIC Interface Start */
#تعریف_کن PLIC_وقفه_1   1	/* PWM 0   */
#تعریف_کن PLIC_وقفه_2   2	/* PWM 1   */
#تعریف_کن PLIC_وقفه_3   3	/* PWM 2   */
#تعریف_کن PLIC_وقفه_4   4	/* PWM 3   */
#تعریف_کن PLIC_وقفه_5   5	/* PWM 4   */
#تعریف_کن PLIC_وقفه_6   6	/* PWM 5   */
#تعریف_کن PLIC_وقفه_7   7	/* GPIO 0  */
#تعریف_کن PLIC_وقفه_8   8	/* GPIO 1  */
#تعریف_کن PLIC_وقفه_9   9	/* GPIO 2  */
#تعریف_کن PLIC_وقفه_10  10	/* GPIO 3  */
#تعریف_کن PLIC_وقفه_11  11	/* GPIO 4  */
#تعریف_کن PLIC_وقفه_12  12	/* GPIO 5  */
#تعریف_کن PLIC_وقفه_13  13	/* GPIO 6  */
#تعریف_کن PLIC_وقفه_14  14	/* GPIO 7  */
#تعریف_کن PLIC_وقفه_15  15	/* GPIO 8  */
#تعریف_کن PLIC_وقفه_16  16	/* GPIO 9  */
#تعریف_کن PLIC_وقفه_17  17	/* GPIO 10 */
#تعریف_کن PLIC_وقفه_18  18	/* GPIO 11 */
#تعریف_کن PLIC_وقفه_19  19	/* GPIO 12 */
#تعریف_کن PLIC_وقفه_20  20	/* GPIO 13 */
#تعریف_کن PLIC_وقفه_21  21	/* GPIO 14 */
#تعریف_کن PLIC_وقفه_22  22	/* GPIO 15 */
#تعریف_کن PLIC_وقفه_23  23	/* I2C 0   */
#تعریف_کن PLIC_وقفه_24  24	/* I2C 1   */
#تعریف_کن PLIC_وقفه_25  25 	/* uart 0  */
#تعریف_کن PLIC_وقفه_26  26 	/* uart 1  */
#تعریف_کن PLIC_وقفه_27  27 	/* uart 2  */
#تعریف_کن PLIC_MAX_وقفه_SRC 28

/*!General Purpose Input / Output */
#تعریف_کن GPIO_شروع 0x00040100 //GPIO Start Address */
#تعریف_کن GPIO_جابه_جایی 0x08 /*!Generic offset used to access GPIO registers*/
#تعریف_کن PLIC_GPIO_جابه_جایی 6

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

#پایان_اگر
