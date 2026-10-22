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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ PLATFORM_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLATFORM_H

/*
 *@brief RISCV - E CLASS SOC Memory mapping
 */

/*! Core Local Interruptor CLINT */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CLINT_ਅਧਾਰ 0x020000000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MTIME      0x0200BFF8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MTIMECMP   0x02004000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CLINT_ਭਾਜਕ   256

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CLOCK_FREQUENCY 50000000

/*!Debugger Offset */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DBG_MEM_ਸ਼ੁਰੂ 0x00000010

/*!Tightly Coupled Memory(TCM) Offset. Size 256mB */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TCM_MEM_ਸ਼ੁਰੂ 0x80000000 /*! DDR3 Memory Start address */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TCM_MEM_ਮਾਪ 0x10000000 /*! DDR3 Memory Size */

/*!Percentage of Free Memory to be used as stack (0-100). The remaining space will be used by heap */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_PERCENTAGE 50 /*! DDR3 Memory Size */

/*!Percentage of Free Memory to be used as stack (0-100). The remaining space will be used by heap */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_PERCENTAGE_2 50 /*! DDR3 Memory Size */

/*!Pulse Width Modulation Start Offsets */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PWM_ਅਧਾਰ_ਪਤਾ 0x00030000 /*PWM Base address*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PWM_MODULE_ਵਿੱਥ 0x00000100 /*Offset value to be incremented for each interface*/

/*!Serial Peripheral Interface Offsets */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI0_ਸ਼ੁਰੂ 0x00020000 /* Serial Peripheral Interface 0 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI1_ਸ਼ੁਰੂ 0x00020100 /* Serial Peripheral Interface 1 */

/*!Universal Synchronous Receiver Transmitter Interface Offsets */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ UART0_ਸ਼ੁਰੂ 0x00011300 /*! UART 0 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ UART_ਵਿੱਥ 0x100
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_UART_ਗਿਣਤੀ 3

/*! Inter Integrated Circuit (I2C) Interface */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2_C0_ਅਧਾਰ 0x00040000 /*! I2C Start Address */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2_C_ਵਿੱਥ 0x1400
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_I2_C_ਗਿਣਤੀ 2

/*! Xilinx Analog to Digital converter */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XADC_ਅਧਾਰ_ਪਤਾ 0x00041000

/*! pinmux*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PINMUX_ਸ਼ੁਰੂ 0x41500 
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PINMUX_CONFIGURE_REG 0x41510

/*! Programmable Logic Interrupt Interface */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਅਧਾਰ_ਪਤਾ 0x0C000000 /*! PLIC Interface Start */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਰੁਕਾਵਟ_1   1	/* PWM 0   */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਰੁਕਾਵਟ_2   2	/* PWM 1   */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਰੁਕਾਵਟ_3   3	/* PWM 2   */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਰੁਕਾਵਟ_4   4	/* PWM 3   */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਰੁਕਾਵਟ_5   5	/* PWM 4   */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਰੁਕਾਵਟ_6   6	/* PWM 5   */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਰੁਕਾਵਟ_7   7	/* GPIO 0  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਰੁਕਾਵਟ_8   8	/* GPIO 1  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਰੁਕਾਵਟ_9   9	/* GPIO 2  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਰੁਕਾਵਟ_10  10	/* GPIO 3  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਰੁਕਾਵਟ_11  11	/* GPIO 4  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਰੁਕਾਵਟ_12  12	/* GPIO 5  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਰੁਕਾਵਟ_13  13	/* GPIO 6  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਰੁਕਾਵਟ_14  14	/* GPIO 7  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਰੁਕਾਵਟ_15  15	/* GPIO 8  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਰੁਕਾਵਟ_16  16	/* GPIO 9  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਰੁਕਾਵਟ_17  17	/* GPIO 10 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਰੁਕਾਵਟ_18  18	/* GPIO 11 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਰੁਕਾਵਟ_19  19	/* GPIO 12 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਰੁਕਾਵਟ_20  20	/* GPIO 13 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਰੁਕਾਵਟ_21  21	/* GPIO 14 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਰੁਕਾਵਟ_22  22	/* GPIO 15 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਰੁਕਾਵਟ_23  23	/* I2C 0   */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਰੁਕਾਵਟ_24  24	/* I2C 1   */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਰੁਕਾਵਟ_25  25 	/* uart 0  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਰੁਕਾਵਟ_26  26 	/* uart 1  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_ਰੁਕਾਵਟ_27  27 	/* uart 2  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_MAX_ਰੁਕਾਵਟ_SRC 28

/*!General Purpose Input / Output */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO_ਸ਼ੁਰੂ 0x00040100 //GPIO Start Address */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO_ਵਿੱਥ 0x08 /*!Generic offset used to access GPIO registers*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PLIC_GPIO_ਵਿੱਥ 6

/*
 * General Purpose IOs supported
 */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO0  (1 <<  0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO1  (1 <<  1)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO2  (1 <<  2)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO3  (1 <<  3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO4  (1 <<  4)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO5  (1 <<  5)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO6  (1 <<  6)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO7  (1 <<  7)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO8  (1 <<  8)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO9  (1 <<  9)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO10 (1 << 10)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO11 (1 << 11)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO12 (1 << 12)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO13 (1 << 13)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO14 (1 << 14)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO15 (1 << 15)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO16 (1 << 16)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO17 (1 << 17)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO18 (1 << 18)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO19 (1 << 19)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO20 (1 << 20)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO21 (1 << 21)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO22 (1 << 22)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO23 (1 << 23)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO24 (1 << 24)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO25 (1 << 25)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO26 (1 << 26)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO27 (1 << 27)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO28 (1 << 28)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO29 (1 << 29)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO30 (1 << 30)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO31 (1 << 31)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GPIO_ਗਿਣਤੀ  0x20

#ਜੇ_ਅੰਤ
