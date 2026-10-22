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

#جيڪڏهن_وصف_نه_ٿيل PLATFORM_H
#وصف_ڪريو PLATFORM_H

/*
 *@brief RISCV - E CLASS SOC Memory mapping
 */

/*! Core Local Interruptor CLINT */
#وصف_ڪريو CLINT_بنياد 0x020000000
#وصف_ڪريو MTIME      0x0200BFF8
#وصف_ڪريو MTIMECMP   0x02004000
#وصف_ڪريو CLINT_ورهائيندڙ   256

#وصف_ڪريو CLOCK_FREQUENCY 50000000

/*!Debugger Offset */
#وصف_ڪريو DBG_MEM_شروعات 0x00000010

/*!Tightly Coupled Memory(TCM) Offset. Size 256mB */
#وصف_ڪريو TCM_MEM_شروعات 0x80000000 /*! DDR3 Memory Start address */
#وصف_ڪريو TCM_MEM_سائيز 0x10000000 /*! DDR3 Memory Size */

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

/*!Universal Synchronous Receiver Transmitter Interface Offsets */
#وصف_ڪريو UART0_شروعات 0x00011300 /*! UART 0 */
#وصف_ڪريو UART_وٿي 0x100
#وصف_ڪريو MAX_UART_ڳڻپ 3

/*! Inter Integrated Circuit (I2C) Interface */
#وصف_ڪريو I2_C0_بنياد 0x00040000 /*! I2C Start Address */
#وصف_ڪريو I2_C_وٿي 0x1400
#وصف_ڪريو MAX_I2_C_ڳڻپ 2

/*! Xilinx Analog to Digital converter */
#وصف_ڪريو XADC_بنياد_پتو 0x00041000

/*! pinmux*/
#وصف_ڪريو PINMUX_شروعات 0x41500 
#وصف_ڪريو PINMUX_CONFIGURE_REG 0x41510

/*! Programmable Logic Interrupt Interface */
#وصف_ڪريو PLIC_بنياد_پتو 0x0C000000 /*! PLIC Interface Start */
#وصف_ڪريو PLIC_مداخلت_1   1	/* PWM 0   */
#وصف_ڪريو PLIC_مداخلت_2   2	/* PWM 1   */
#وصف_ڪريو PLIC_مداخلت_3   3	/* PWM 2   */
#وصف_ڪريو PLIC_مداخلت_4   4	/* PWM 3   */
#وصف_ڪريو PLIC_مداخلت_5   5	/* PWM 4   */
#وصف_ڪريو PLIC_مداخلت_6   6	/* PWM 5   */
#وصف_ڪريو PLIC_مداخلت_7   7	/* GPIO 0  */
#وصف_ڪريو PLIC_مداخلت_8   8	/* GPIO 1  */
#وصف_ڪريو PLIC_مداخلت_9   9	/* GPIO 2  */
#وصف_ڪريو PLIC_مداخلت_10  10	/* GPIO 3  */
#وصف_ڪريو PLIC_مداخلت_11  11	/* GPIO 4  */
#وصف_ڪريو PLIC_مداخلت_12  12	/* GPIO 5  */
#وصف_ڪريو PLIC_مداخلت_13  13	/* GPIO 6  */
#وصف_ڪريو PLIC_مداخلت_14  14	/* GPIO 7  */
#وصف_ڪريو PLIC_مداخلت_15  15	/* GPIO 8  */
#وصف_ڪريو PLIC_مداخلت_16  16	/* GPIO 9  */
#وصف_ڪريو PLIC_مداخلت_17  17	/* GPIO 10 */
#وصف_ڪريو PLIC_مداخلت_18  18	/* GPIO 11 */
#وصف_ڪريو PLIC_مداخلت_19  19	/* GPIO 12 */
#وصف_ڪريو PLIC_مداخلت_20  20	/* GPIO 13 */
#وصف_ڪريو PLIC_مداخلت_21  21	/* GPIO 14 */
#وصف_ڪريو PLIC_مداخلت_22  22	/* GPIO 15 */
#وصف_ڪريو PLIC_مداخلت_23  23	/* I2C 0   */
#وصف_ڪريو PLIC_مداخلت_24  24	/* I2C 1   */
#وصف_ڪريو PLIC_مداخلت_25  25 	/* uart 0  */
#وصف_ڪريو PLIC_مداخلت_26  26 	/* uart 1  */
#وصف_ڪريو PLIC_مداخلت_27  27 	/* uart 2  */
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
#وصف_ڪريو GPIO16 (1 << 16)
#وصف_ڪريو GPIO17 (1 << 17)
#وصف_ڪريو GPIO18 (1 << 18)
#وصف_ڪريو GPIO19 (1 << 19)
#وصف_ڪريو GPIO20 (1 << 20)
#وصف_ڪريو GPIO21 (1 << 21)
#وصف_ڪريو GPIO22 (1 << 22)
#وصف_ڪريو GPIO23 (1 << 23)
#وصف_ڪريو GPIO24 (1 << 24)
#وصف_ڪريو GPIO25 (1 << 25)
#وصف_ڪريو GPIO26 (1 << 26)
#وصف_ڪريو GPIO27 (1 << 27)
#وصف_ڪريو GPIO28 (1 << 28)
#وصف_ڪريو GPIO29 (1 << 29)
#وصف_ڪريو GPIO30 (1 << 30)
#وصف_ڪريو GPIO31 (1 << 31)
#وصف_ڪريو GPIO_ڳڻپ  0x20

#جيڪڏهن_پورو
