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

#నిర్వచితం_కాకపోతే PLATFORM_H
#నిర్వచించు PLATFORM_H

/*
 *@brief RISCV - C CLASS SOC Memory mapping
 */

/*! Core Local Interruptor CLINT */
#నిర్వచించు CLINT_పునాది 0x020000000
#నిర్వచించు MTIME      0x0200BFF8
#నిర్వచించు MTIMECMP   0x02004000
#నిర్వచించు CLINT_భాజకం   256

#నిర్వచించు CLOCK_FREQUENCY 50000000

/*!Debugger Offset */
#నిర్వచించు DBG_MEM_ప్రారంభం 0x00000010

/*!Tightly Coupled Memory(TCM) Offset. Size 256mB */
#నిర్వచించు TCM_MEM_ప్రారంభం 0x80000000 /*! DDR3 Memory Start address */
#నిర్వచించు TCM_MEM_కొలత 0x10000000 /*! DDR3 Memory Size */

/*!Percentage of Free Memory to be used as stack (0-100). The remaining space will be used by heap */
#నిర్వచించు దొంతర_PERCENTAGE 50 /*! DDR3 Memory Size */

/*!Percentage of Free Memory to be used as stack (0-100). The remaining space will be used by heap */
#నిర్వచించు కుప్ప_PERCENTAGE 50 /*! DDR3 Memory Size */

/*!Pulse Width Modulation Start Offsets */
#నిర్వచించు PWM_పునాది_చిరునామా 0x00030000 /*PWM Base address*/
#నిర్వచించు PWM_MODULE_స్థానభ్రంశం 0x00000100 /*Offset value to be incremented for each interface*/

/*!Serial Peripheral Interface Offsets */
#నిర్వచించు SPI0_ప్రారంభం 0x00020000 /* Serial Peripheral Interface 0 */
#నిర్వచించు SPI1_ప్రారంభం 0x00020100 /* Serial Peripheral Interface 1 */

/*!Universal Synchronous Receiver Transmitter Interface Offsets */
#నిర్వచించు UART0_ప్రారంభం 0x00011300 /*! UART 0 */
#నిర్వచించు UART_స్థానభ్రంశం 0x100
#నిర్వచించు MAX_UART_లెక్క 3

/*! Inter Integrated Circuit (I2C) Interface */
#నిర్వచించు I2_C0_పునాది 0x00040000 /*! I2C Start Address */
#నిర్వచించు I2_C_స్థానభ్రంశం 0x1400
#నిర్వచించు MAX_I2_C_లెక్క 2

/*! Xilinx Analog to Digital converter */
#నిర్వచించు XADC_పునాది_చిరునామా 0x00041000

/*!Ethernet */
#నిర్వచించు ETHERNET_పునాది 0x00044000

/*! pinmux*/
#నిర్వచించు PINMUX_ప్రారంభం 0x41500 
#నిర్వచించు PINMUX_CONFIGURE_REG 0x41510

/*! Programmable Logic Interrupt Interface */
#నిర్వచించు PLIC_పునాది_చిరునామా 0x0C000000 /*! PLIC Interface Start */
#నిర్వచించు PLIC_అంతరాయం_1   1	/* PWM 0   */
#నిర్వచించు PLIC_అంతరాయం_2   2	/* PWM 1   */
#నిర్వచించు PLIC_అంతరాయం_3   3	/* PWM 2   */
#నిర్వచించు PLIC_అంతరాయం_4   4	/* PWM 3   */
#నిర్వచించు PLIC_అంతరాయం_5   5	/* PWM 4   */
#నిర్వచించు PLIC_అంతరాయం_6   6	/* PWM 5   */
#నిర్వచించు PLIC_అంతరాయం_7   7	/* GPIO 0  */
#నిర్వచించు PLIC_అంతరాయం_8   8	/* GPIO 1  */
#నిర్వచించు PLIC_అంతరాయం_9   9	/* GPIO 2  */
#నిర్వచించు PLIC_అంతరాయం_10  10	/* GPIO 3  */
#నిర్వచించు PLIC_అంతరాయం_11  11	/* GPIO 4  */
#నిర్వచించు PLIC_అంతరాయం_12  12	/* GPIO 5  */
#నిర్వచించు PLIC_అంతరాయం_13  13	/* GPIO 6  */
#నిర్వచించు PLIC_అంతరాయం_14  14	/* GPIO 7  */
#నిర్వచించు PLIC_అంతరాయం_15  15	/* GPIO 8  */
#నిర్వచించు PLIC_అంతరాయం_16  16	/* GPIO 9  */
#నిర్వచించు PLIC_అంతరాయం_17  17	/* GPIO 10 */
#నిర్వచించు PLIC_అంతరాయం_18  18	/* GPIO 11 */
#నిర్వచించు PLIC_అంతరాయం_19  19	/* GPIO 12 */
#నిర్వచించు PLIC_అంతరాయం_20  20	/* GPIO 13 */
#నిర్వచించు PLIC_అంతరాయం_21  21	/* GPIO 14 */
#నిర్వచించు PLIC_అంతరాయం_22  22	/* GPIO 15 */
#నిర్వచించు PLIC_అంతరాయం_23  23	/* I2C 0   */
#నిర్వచించు PLIC_అంతరాయం_24  24	/* I2C 1   */
#నిర్వచించు PLIC_అంతరాయం_25  25 	/* uart 0  */
#నిర్వచించు PLIC_అంతరాయం_26  26 	/* uart 1  */
#నిర్వచించు PLIC_అంతరాయం_27  27 	/* uart 2  */
#నిర్వచించు PLIC_MAX_అంతరాయం_SRC 28

/*!General Purpose Input / Output */
#నిర్వచించు GPIO_ప్రారంభం 0x00040100 //GPIO Start Address */
#నిర్వచించు GPIO_స్థానభ్రంశం 0x08 /*!Generic offset used to access GPIO registers*/
#నిర్వచించు PLIC_GPIO_స్థానభ్రంశం 6

/*
 * General Purpose IOs supported
 */

#నిర్వచించు GPIO0  (1 <<  0)
#నిర్వచించు GPIO1  (1 <<  1)
#నిర్వచించు GPIO2  (1 <<  2)
#నిర్వచించు GPIO3  (1 <<  3)
#నిర్వచించు GPIO4  (1 <<  4)
#నిర్వచించు GPIO5  (1 <<  5)
#నిర్వచించు GPIO6  (1 <<  6)
#నిర్వచించు GPIO7  (1 <<  7)
#నిర్వచించు GPIO8  (1 <<  8)
#నిర్వచించు GPIO9  (1 <<  9)
#నిర్వచించు GPIO10 (1 << 10)
#నిర్వచించు GPIO11 (1 << 11)
#నిర్వచించు GPIO12 (1 << 12)
#నిర్వచించు GPIO13 (1 << 13)
#నిర్వచించు GPIO14 (1 << 14)
#నిర్వచించు GPIO15 (1 << 15)
#నిర్వచించు GPIO16 (1 << 16)
#నిర్వచించు GPIO17 (1 << 17)
#నిర్వచించు GPIO18 (1 << 18)
#నిర్వచించు GPIO19 (1 << 19)
#నిర్వచించు GPIO20 (1 << 20)
#నిర్వచించు GPIO21 (1 << 21)
#నిర్వచించు GPIO22 (1 << 22)
#నిర్వచించు GPIO23 (1 << 23)
#నిర్వచించు GPIO24 (1 << 24)
#నిర్వచించు GPIO25 (1 << 25)
#నిర్వచించు GPIO26 (1 << 26)
#నిర్వచించు GPIO27 (1 << 27)
#నిర్వచించు GPIO28 (1 << 28)
#నిర్వచించు GPIO29 (1 << 29)
#నిర్వచించు GPIO30 (1 << 30)
#నిర్వచించు GPIO31 (1 << 31)
#నిర్వచించు GPIO_లెక్క  0x20

#అయితే_ముగింపు
