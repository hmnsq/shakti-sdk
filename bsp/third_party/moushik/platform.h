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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ PLATFORM_H
#ವ್ಯಾಖ್ಯಾನಿಸು PLATFORM_H

/*
 *@brief RISCV - E CLASS SOC Memory mapping
 */

#ವ್ಯಾಖ್ಯಾನಿಸು CLOCK_FREQUENCY 40000000

/*! Core Local Interruptor CLINT */

#ವ್ಯಾಖ್ಯಾನಿಸು CLINT_ತಳ 0x020000000
#ವ್ಯಾಖ್ಯಾನಿಸು MTIME      0x0200BFF8
#ವ್ಯಾಖ್ಯಾನಿಸು MTIMECMP   0x02004000
#ವ್ಯಾಖ್ಯಾನಿಸು CLINT_ಭಾಜಕ   16

#ವ್ಯಾಖ್ಯಾನಿಸು MCAUSE_INT         0x80000000
#ವ್ಯಾಖ್ಯಾನಿಸು MCAUSE_CAUSE       0x7FFFFFFF

#ವ್ಯಾಖ್ಯಾನಿಸು PINMUX_CONFIGURE_REG 0x40310

/*!Debugger Offset */
#ವ್ಯಾಖ್ಯಾನಿಸು DBG_MEM_ಆರಂಭ 0x00000010

/*!Tightly Coupled Memory(TCM) Offset. Size 128kB */
#ವ್ಯಾಖ್ಯಾನಿಸು TCM_MEM_ಆರಂಭ 0x80000000 /*! DDR3 Memory Start address */

/*!Tightly Coupled Memory(TCM) Size. Size 128kB */
#ವ್ಯಾಖ್ಯಾನಿಸು TCM_MEM_ಗಾತ್ರ 0x20000 /*! DDR3 Memory Size */

/*!Percentage of Free Memory to be used as stack (0-100). The remaining space will be used by heap */
#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_PERCENTAGE 50 /*! DDR3 Memory Size */

/*!Percentage of Free Memory to be used as stack (0-100). The remaining space will be used by heap */
#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_PERCENTAGE_2 50 /*! DDR3 Memory Size */

/*!Pulse Width Modulation Start Offsets */
#ವ್ಯಾಖ್ಯಾನಿಸು PWM_ತಳ_ವಿಳಾಸ 0x00030000 /*PWM Base address*/
#ವ್ಯಾಖ್ಯಾನಿಸು PWM_MODULE_ಸ್ಥಾನಾಂತರ 0x00000100 /*Offset value to be incremented for each interface*/

/*!Serial Peripheral Interface Offsets */
#ವ್ಯಾಖ್ಯಾನಿಸು SPI0_ಆರಂಭ 0x00020000 /* Serial Peripheral Interface 0 */
#ವ್ಯಾಖ್ಯಾನಿಸು SPI1_ಆರಂಭ 0x00020100 /* Serial Peripheral Interface 1 */
#ವ್ಯಾಖ್ಯಾನಿಸು SPI2_ಆರಂಭ 0x00020200 /* Serial Peripheral Interface 2 */

/*!Universal Synchronous Receiver Transmitter Interface Offsets */
#ವ್ಯಾಖ್ಯಾನಿಸು UART0_ಆರಂಭ 0x00011300 /*! UART 0 */
#ವ್ಯಾಖ್ಯಾನಿಸು UART1_ಆರಂಭ 0x00011400 /*! UART 1 */
#ವ್ಯಾಖ್ಯಾನಿಸು UART2_ಆರಂಭ 0x00011500 /*! UART 2 */
#ವ್ಯಾಖ್ಯಾನಿಸು UART_ಸ್ಥಾನಾಂತರ 0x100
#ವ್ಯಾಖ್ಯಾನಿಸು UART_ತಳ 0x11300
#ವ್ಯಾಖ್ಯಾನಿಸು MAX_UART_ಎಣಿಕೆ 3

#ವ್ಯಾಖ್ಯಾನಿಸು PINMUX_CONFIGURE_REG 0x40310


/*! Inter Integrated Circuit (I2C) Interface */
#ವ್ಯಾಖ್ಯಾನಿಸು I2_C0_ತಳ 0x00040000
#ವ್ಯಾಖ್ಯಾನಿಸು I2_C_ಸ್ಥಾನಾಂತರ 0x400
#ವ್ಯಾಖ್ಯಾನಿಸು MAX_I2_C_ಎಣಿಕೆ 2

/*! Programmable Logic Interrupt Interface */
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ತಳ_ವಿಳಾಸ 0x0C000000 /*! PLIC Interface Start */
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಅಡಚಣೆ_1   1
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಅಡಚಣೆ_2   2
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಅಡಚಣೆ_3   3
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಅಡಚಣೆ_4   4
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಅಡಚಣೆ_5   5
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಅಡಚಣೆ_6   6
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಅಡಚಣೆ_7   7
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಅಡಚಣೆ_8   8
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಅಡಚಣೆ_9   9
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಅಡಚಣೆ_10  10
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಅಡಚಣೆ_11  11
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಅಡಚಣೆ_12  12
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಅಡಚಣೆ_13  13
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಅಡಚಣೆ_14  14
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಅಡಚಣೆ_15  15
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಅಡಚಣೆ_16  16
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಅಡಚಣೆ_17  17
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಅಡಚಣೆ_18  18
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಅಡಚಣೆ_19  19
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಅಡಚಣೆ_20  20
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಅಡಚಣೆ_21  21
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಅಡಚಣೆ_22  22
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಅಡಚಣೆ_23  23
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಅಡಚಣೆ_24  24
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಅಡಚಣೆ_25  25 //uart 0
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಅಡಚಣೆ_26  26 //uart 1
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಅಡಚಣೆ_27  27 //uart 2

#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_MAX_ಅಡಚಣೆ_SRC 28

/*!General Purpose Input / Output */
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO_ಆರಂಭ 0x00040100 //GPIO Start Address */
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO_ಸ್ಥಾನಾಂತರ 0x08 /*!Generic offset used to access GPIO registers*/
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_GPIO_ಸ್ಥಾನಾಂತರ 6

/*
 * General Purpose IOs supported
 */

#ವ್ಯಾಖ್ಯಾನಿಸು GPIO0  (1 <<  0)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO1  (1 <<  1)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO2  (1 <<  2)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO3  (1 <<  3)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO4  (1 <<  4)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO5  (1 <<  5)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO6  (1 <<  6)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO7  (1 <<  7)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO8  (1 <<  8)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO9  (1 <<  9)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO10 (1 << 10)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO11 (1 << 11)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO12 (1 << 12)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO13 (1 << 13)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO14 (1 << 14)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO15 (1 << 15)

#ವ್ಯಾಖ್ಯಾನಿಸು GPIO_ಎಣಿಕೆ  0x10

#ಆದರೆ_ಅಂತ್ಯ
