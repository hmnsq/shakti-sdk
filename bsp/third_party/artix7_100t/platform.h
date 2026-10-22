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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ PLATFORM_H
#ವ್ಯಾಖ್ಯಾನಿಸು PLATFORM_H

/*
 *@brief RISCV - C CLASS SOC Memory mapping
 */

#ವ್ಯಾಖ್ಯಾನಿಸು CLINT_ತಳ 0x020000000
#ವ್ಯಾಖ್ಯಾನಿಸು MTIME      0x0200BFF8
#ವ್ಯಾಖ್ಯಾನಿಸು MTIMECMP   0x02004000
#ವ್ಯಾಖ್ಯಾನಿಸು CLINT_ಭಾಜಕ   256

#ವ್ಯಾಖ್ಯಾನಿಸು CLOCK_FREQUENCY 20000000

#ವ್ಯಾಖ್ಯಾನಿಸು MCAUSE_INT         0x80000000
#ವ್ಯಾಖ್ಯಾನಿಸು MCAUSE_CAUSE       0x7FFFFFFF

#ವ್ಯಾಖ್ಯಾನಿಸು PINMUX_CONFIGURE_REG 0x40310

/*!Debugger Offset */
#ವ್ಯಾಖ್ಯಾನಿಸು DBG_MEM_ಆರಂಭ 0x00000000

/*!Tightly Coupled Memory(TCM) Offset. Size 128mB */
#ವ್ಯಾಖ್ಯಾನಿಸು TCM_MEM_ಆರಂಭ 0x80000000 /*! DDR3 Memory Start address */

/*!Tightly Coupled Memory(TCM) Size. Size 128kB */
#ವ್ಯಾಖ್ಯಾನಿಸು TCM_MEM_ಗಾತ್ರ 0x8000000 /*! DDR3 Memory Size */

/*!Percentage of Free Memory to be used as stack (0-100). The remaining space will be used by heap */
#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_PERCENTAGE 50 /*! DDR3 Memory Size */

/*!Percentage of Free Memory to be used as stack (0-100). The remaining space will be used by heap */
#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_PERCENTAGE_2 50 /*! DDR3 Memory Size */

/*!Pulse Width Modulation Start Offsets */
#ವ್ಯಾಖ್ಯಾನಿಸು PWM_ತಳ_ವಿಳಾಸ 0x00030000 /*PWM Base address*/
#ವ್ಯಾಖ್ಯಾನಿಸು PWM_MODULE_ಸ್ಥಾನಾಂತರ 0x00000100 /*Offset value to be incremented for each interface*/

/*!Universal Synchronous Receiver Transmitter Interface Offsets */
#ವ್ಯಾಖ್ಯಾನಿಸು UART0_ಆರಂಭ 0x00011300 /*! UART 0 */
#ವ್ಯಾಖ್ಯಾನಿಸು UART_ಸ್ಥಾನಾಂತರ 0x100
#ವ್ಯಾಖ್ಯಾನಿಸು MAX_UART_ಎಣಿಕೆ 1

#ವ್ಯಾಖ್ಯಾನಿಸು PINMUX_CONFIGURE_REG 0x40310

/*! Core Local Interruptor CLINT */


/*! Inter Integrated Circuit (I2C) Interface */
#ವ್ಯಾಖ್ಯಾನಿಸು I2_C0_ತಳ 0x020C0000 /*! I2C Start Address */
#ವ್ಯಾಖ್ಯಾನಿಸು I2_C_ಸ್ಥಾನಾಂತರ 0x000
#ವ್ಯಾಖ್ಯಾನಿಸು MAX_I2_C_ಎಣಿಕೆ 1

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
#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_ಅಡಚಣೆ_26  26

#ವ್ಯಾಖ್ಯಾನಿಸು PLIC_MAX_ಅಡಚಣೆ_SRC 26

/*!General Purpose Input / Output */
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO_ಆರಂಭ 0x020D0000 //GPIO Start Address */
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO_ಸ್ಥಾನಾಂತರ 0x08 /*!Generic offset used to access GPIO registers*/

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
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO16 (1 << 16)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO17 (1 << 17)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO18 (1 << 18)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO19 (1 << 19)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO20 (1 << 20)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO21 (1 << 21)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO22 (1 << 22)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO23 (1 << 23)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO24 (1 << 24)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO25 (1 << 25)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO26 (1 << 26)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO27 (1 << 27)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO28 (1 << 28)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO29 (1 << 29)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO30 (1 << 30)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO31 (1 << 31)
#ವ್ಯಾಖ್ಯಾನಿಸು GPIO_ಎಣಿಕೆ  0x20
//#define PLIC_GPIO_OFFSET 0

#ಆದರೆ_ಅಂತ್ಯ
