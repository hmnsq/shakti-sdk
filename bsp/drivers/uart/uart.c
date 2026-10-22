/****************************************************************************
 * Project                               : shakti devt board
 * Name of the file                      : uart.c
 * Brief Description of file             : src  file for uart
 * Name of Author                        : Kotteeswaran and Niketan Shahapur
 * Email ID                              : <kottee.1@gmail.com>  <niketanshahpur@gmail.com> 

 Copyright (C) 2019 IIT Madras. All rights reserved.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *****************************************************************************/
/**
  @file uart.c
  @brief Contains the driver routines for UART interface.
  @detail The UART driver .has software functions to configure, transmit 
  and receive over UART interface.
 */

#ضمن "uart.h"
#ضمن "gpio.h"
#ضمن "utils.h"

uart_struct *uart_instance[MAX_UART_ڳڻپ];

#وصف_ڪريو RTS GPIO4
//#define USE_INTERRUPT 

بنانشان حرف uart0_complete = 0;
بنانشان حرف uart1_complete = 0;
بنانشان حرف uart2_complete = 0;
بنانشان صحيح uart0_tx_isr_ڳڻپ = 0;
بنانشان صحيح uart0_rcv_isr_ڳڻپ = 0;
بنانشان صحيح uart1_tx_isr_ڳڻپ = 0;
بنانشان صحيح uart1_rcv_isr_ڳڻپ = 0;
بنانشان صحيح uart2_tx_isr_ڳڻپ = 0;
بنانشان صحيح uart2_rcv_isr_ڳڻپ = 0;

#جيڪڏهن_وصف_ٿيل USE_مداخلت
بنانشان حرف u0_rcv_char[UARTX_بفر_سائيز] = {'\0'};
بنانشان حرف u1_rcv_char[UARTX_بفر_سائيز] = {'\0'};
بنانشان حرف u2_rcv_char[UARTX_بفر_سائيز] = {'\0'};
#جيڪڏهن_پورو

/**
 * @fn void uart_init()
 * @brief Initialise UART Array 
 * @details Initialises given number of UART Arrays which has 
 *          complete set of UART registers.
 */
فراغ uart_init()
{
	لكل(صحيح i=0; i< MAX_UART_ڳڻپ; i++)
	{
		uart_instance[i] = (uart_struct*) (UART0_شروعات+i*UART_وٿي);
	}
}

/**
 * @fn int getchar()
 * @brief Function to read a single character from the standard input device.
 * @details This function will be called to write a single character from the stdin.
 * @return integer equivalent of the received character.
 */
#وصف_رد getchar
صحيح getchar()
{
	طالما((uart_instance[0]->حالت_2 & STS_RX_NOT_خالي_جايون) == 0); 
	أرجع (uart_instance[0]->rcv_reg);
}

/**
 * @fn int putchar(int ch)
 * @brief Function to write a single character to the standard output device.
 * @details This function will be called to print a single character to the stdout by passing 
 * character as an integer.
 * @param character as int.
 * @return Zero
 */
#وصف_رد اکر_لکو
صحيح اکر_لکو(صحيح ch)
{
	طالما(uart_instance[0]->حالت_2 & STS_TX_ڀريل);

	uart_instance[0]->tx_reg = ch;

	أرجع 0;
}

/**
 * @fn void set_baud_rate(uart_struct * UART, unsigned int baudrate)
 * @brief Function to initialize a specific UART with the baudrate.
 * @details This function will be called to initialize a specific UART by passing baudrate value
 * which in turn used to calculate the baud_count to set the baudrate.
 * @param UART instance
 * @param unsigned int baudrate
 */
فراغ سيٽ_baud_شرح(uart_struct *instance, بنانشان صحيح baudrate)
{
	بنانشان صحيح baud_ڳڻپ = 0;
	baud_ڳڻپ = CLOCK_FREQUENCY / (16 * baudrate);
	instance->baud = baud_ڳڻپ;
}

/**
 * @fn void enable_uart_interrupts(uart_struct * instance, unsigned char interrupt) 
 * @brief Function to enable the interrupts of a perticular uart instance.
 * @details This function will be called to enable the interrupts of a specific uart instance by passing
 * the interrupt's values.
 * @param uart instance 
 * @param unsigned char interrupt
 */
فراغ enable_uart_interrupts(uart_struct * instance, بنانشان حرف مداخلت)
{
	instance->ien = مداخلت; 
}

#جيڪڏهن_وصف_ٿيل USE_RX_حد
/**
 * @fn void set_uart_rx_threshold(uart_struct * instance, unsigned char rxthreshold)
 * @brief Funtion to set the threshold value of the Rx FIFO.
 * @details This function will be called to set the threshold value of the Rx FIFO of a specific uart instance
 * by passing the threshold value.
 * @param uart instance 
 * @param unsigned char rxthreshold
 */
فراغ سيٽ_uart_rx_حد(uart_struct * instance, بنانشان حرف rxthreshold)
{
	instance->rx_حد = rxthreshold;
}
#جيڪڏهن_پورو

/**
 * @fn uint32_t write_uart_character(uart_struct * instance, uint8_t prn_character)
 * @brief Function to write a single character to a specific uart instance. 
 * @details This function will be called to write a character to a specific uart instance by passing the
 * character.
 * @param uart instance
 * @param character.
 */
uint32_t write_uart_character(uart_struct * instance, uint8_t prn_character)
{
	طالما(instance->حالت_2 & STS_TX_ڀريل);

	instance->tx_reg = prn_character;

	أرجع 0;
}

/**
 * @fn uint32_t write_uart_string(uart_struct * instance, uint8_t * ptr_string)
 * @brief Function to write a string to a specific uart instance.
 * @details This function will be called to write a string to a specific uart instance by passing the
 * string.
 * @param uart instance 
 * @param string.
 * @return Zero
 */
uint32_t write_uart_string(uart_struct * instance, uint8_t * ptr_string)
{
	uint32_t i = 0;
	uint8_t عارضي;

	افعل
	{
		عارضي = ptr_string[i++];
		write_uart_character(instance, عارضي);
	} طالما(عارضي != 0);

	أرجع 0;
}

/**
 * @fn uint8_t read_uart_character(instance_TypeDef * instance, char * prn_character)
 * @brief Function to read a character from a specific instance.
 * @details This function will be called to read a character from a specific uart instance by passing the
 * character pointer to store the character.
 * @param uart instance 
 * @param pointer to a character.
 * @return number of characters read
 */
uint8_t read_uart_character(uart_struct * instance, حرف * prn_character)
{
	uint8_t عارضي = 0;

	طالما ((instance->حالت_2 & STS_RX_NOT_خالي_جايون) == 0);

	عارضي = instance->rcv_reg;
	*prn_character = عارضي;

	أرجع 1;
}

/**
 * @fn uint8_t read_uart_string(uart_struct * instance, char * ptr_string)
 * @brief Function to read a string from a specific uart instance.
 * @details This function will be called to read a string, one character at a time from a 
 * specific uart instance by passing the array in which to store the string by reference using pointers.
 * @param UART instance
 * @param pointer to an array of character.
 * @return length of the received string
 */
uint8_t read_uart_string(uart_struct * instance, حرف * ptr_string)
{
	uint32_t i = 0;
	uint8_t عارضي = 0;

	طالما(1)
	{
		طالما ((instance->حالت_2 & STS_RX_NOT_خالي_جايون) == 0);

		عارضي = instance->rcv_reg;
		ptr_string[i++] = عارضي;
		اکر_لکو(عارضي);

		إذا (عارضي == 0x0D)
		{
			ptr_string[i++] = 0x0A;
			ptr_string[i++] = 0x00;
			أرجع(i);
		}
	}
}

/**
 * @fn void flush_uart((uart_struct * instance)
 * @brief Function to flush the UART fifo queue.
 * @details This function will be called to flush the previous values stored in the UART fifo queue by
 * passing UART number for different offset addresses.
 * @param UART instance.
 */
فراغ flush_uart(uart_struct * instance)
{
	__attribute__((اڻ_استعمال_ٿيل)) حرف عارضي;

	طالما ((instance->حالت_2 & STS_RX_NOT_خالي_جايون) != 0)
	{
		عارضي = instance->rcv_reg ;
	}
}

/*Enable USE_INTERRUPT in command line*/

#جيڪڏهن_وصف_ٿيل USE_مداخلت
/**
 * @fn unsigned char uart0_isr()
 * @brief Function to offer interrupt service routine for uart_instance[0].
 * @details This function will be called to offer interrupt service routine for UART0 to read the
 * array of characters by handling interrupts such as RX_threshold, Rx_full, and RX_not_empty
 * based on the Rx fifo status and handles accordingly.
 * @return Currently not returning any value
 */
بنانشان حرف uart0_isr()
{
	uint32_t read_قدر = '\0';

	إذا(uart_instance[0]->حالت_2 & STS_RX_حد)
	{
		طالما(uart_instance[0]->حالت_2 & STS_RX_NOT_خالي_جايون)
		{
			read_قدر = uart_instance[0]->rcv_reg;
			u0_rcv_char[uart0_rcv_isr_ڳڻپ++] = read_قدر;
			write_uart_character(uart_instance[0], read_قدر);
		}
	}
	وإلا إذا(uart_instance[0]->حالت_2 & STS_RX_ڀريل)
	{
		write_لفظ(GPIO_DIRECTION_CNTRL_REG, RTS);
		write_لفظ(GPIO_معلومات_REG, read_لفظ(GPIO_معلومات_REG) | RTS);

		طالما(uart_instance[0]->حالت_2 & STS_RX_NOT_خالي_جايون)
		{
			read_قدر = uart_instance[0]->rcv_reg;
			u0_rcv_char[uart0_rcv_isr_ڳڻپ++] = read_قدر;
			write_uart_character(uart_instance[0], read_قدر);
		}
		write_لفظ(GPIO_معلومات_REG, read_لفظ(GPIO_معلومات_REG) & ~(RTS));
	}
	وإلا إذا(uart_instance[0]->حالت_2 & STS_RX_NOT_خالي_جايون)
	{
		read_قدر = uart_instance[0]->rcv_reg;
		u0_rcv_char[uart0_rcv_isr_ڳڻپ++] = read_قدر;
		write_uart_character(uart_instance[0], read_قدر);
	}
	أرجع 0;
}

/**
 * @fn unsigned char uart1_isr()
 * @brief Function to offer interrupt service routine for uart_instance[1].
 * @details This function will be called to offer interrupt service routine for uart_instance[1] to read the
 * array of characters by handling interrupts such as RX_threshold, Rx_full, and RX_not_empty
 * based on the Rx fifo status and handles accordingly.
 * @return Currently not returning any value
 */
بنانشان حرف uart1_isr()
{
	uint32_t read_قدر = '\0';

	إذا(uart_instance[1]->حالت_2 & STS_RX_حد)
	{
		طالما(uart_instance[1]->حالت_2 & STS_RX_NOT_خالي_جايون)
		{
			read_قدر = uart_instance[1]->rcv_reg;
			u1_rcv_char[uart1_rcv_isr_ڳڻپ++] = read_قدر;
			write_uart_character(uart_instance[1], read_قدر);
		}
	}
	وإلا إذا(uart_instance[1]->حالت_2 & STS_RX_ڀريل)
	{
		write_لفظ(GPIO_DIRECTION_CNTRL_REG, RTS);
		write_لفظ(GPIO_معلومات_REG, read_لفظ(GPIO_معلومات_REG) | RTS);

		طالما(uart_instance[1]->حالت_2 & STS_RX_NOT_خالي_جايون)
		{
			read_قدر = uart_instance[1]->rcv_reg;
			u1_rcv_char[uart1_rcv_isr_ڳڻپ++] = read_قدر;
			write_uart_character(uart_instance[1], read_قدر);
		}
		write_لفظ(GPIO_معلومات_REG, read_لفظ(GPIO_معلومات_REG) & ~(RTS));
	}
	وإلا إذا(uart_instance[1]->حالت_2 & STS_RX_NOT_خالي_جايون)
	{
		read_قدر = uart_instance[1]->rcv_reg;
		u1_rcv_char[uart1_rcv_isr_ڳڻپ++] = read_قدر;
		write_uart_character(uart_instance[1], read_قدر);
	}
	أرجع 0;
}

/**
 * @fn unsigned char uart2_isr()
 * @brief Function to offer interrupt service routine for UART2.
 * @details This function will be called to offer interrupt service routine for UART2 to read the
 * array of characters by handling interrupts such as RX_threshold, Rx_full, and RX_not_empty
 * based on the Rx fifo status and handles accordingly.
 * @return Currently not returning any value
 */
بنانشان حرف uart2_isr()
{
	uint32_t read_قدر = '\0';

	إذا(uart_instance[2]->حالت_2 & STS_RX_حد)
	{
		طالما(uart_instance[2]->حالت_2 & STS_RX_NOT_خالي_جايون)
		{
			read_قدر = uart_instance[2]->rcv_reg;
			u2_rcv_char[uart2_rcv_isr_ڳڻپ++] = read_قدر;
			write_uart_character(uart_instance[2], read_قدر);
		}
	}
	وإلا إذا(uart_instance[2]->حالت_2 & STS_RX_ڀريل)
	{
		write_لفظ(GPIO_DIRECTION_CNTRL_REG, RTS);
		write_لفظ(GPIO_معلومات_REG, read_لفظ(GPIO_معلومات_REG) | RTS);

		طالما(uart_instance[2]->حالت_2 & STS_RX_NOT_خالي_جايون)
		{
			read_قدر = uart_instance[2]->rcv_reg;
			u2_rcv_char[uart2_rcv_isr_ڳڻپ++] = read_قدر;
			write_uart_character(uart_instance[2], read_قدر);
		}
		write_لفظ(GPIO_معلومات_REG, read_لفظ(GPIO_معلومات_REG) & ~(RTS));
	}
	وإلا إذا(uart_instance[2]->حالت_2 & STS_RX_NOT_خالي_جايون)
	{
		read_قدر = uart_instance[2]->rcv_reg;
		u2_rcv_char[uart2_rcv_isr_ڳڻپ++] = read_قدر;
		write_uart_character(uart_instance[2], read_قدر);
	}
	أرجع 0;
}
#جيڪڏهن_پورو
