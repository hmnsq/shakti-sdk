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

#অন্তর্ভাৱ "uart.h"
#অন্তর্ভাৱ "gpio.h"
#অন্তর্ভাৱ "utils.h"

uart_struct *uart_instance[MAX_UART_গুনতি];

#define RTS GPIO4
//#define USE_INTERRUPT 

unsigned ৱর্ণ uart0_complete = 0;
unsigned ৱর্ণ uart1_complete = 0;
unsigned ৱর্ণ uart2_complete = 0;
unsigned পূর্ণাঙ্ক uart0_tx_isr_গুনতি = 0;
unsigned পূর্ণাঙ্ক uart0_rcv_isr_গুনতি = 0;
unsigned পূর্ণাঙ্ক uart1_tx_isr_গুনতি = 0;
unsigned পূর্ণাঙ্ক uart1_rcv_isr_গুনতি = 0;
unsigned পূর্ণাঙ্ক uart2_tx_isr_গুনতি = 0;
unsigned পূর্ণাঙ্ক uart2_rcv_isr_গুনতি = 0;

#ifdef USE_INTERRUPT
unsigned ৱর্ণ u0_rcv_char[UARTX_BUFFER_SIZE] = {'\0'};
unsigned ৱর্ণ u1_rcv_char[UARTX_BUFFER_SIZE] = {'\0'};
unsigned ৱর্ণ u2_rcv_char[UARTX_BUFFER_SIZE] = {'\0'};
#endif

/**
 * @fn void uart_init()
 * @brief Initialise UART Array 
 * @details Initialises given number of UART Arrays which has 
 *          complete set of UART registers.
 */
শূন্য uart_init()
{
	বাবে(পূর্ণাঙ্ক i=0; i< MAX_UART_গুনতি; i++)
	{
		uart_instance[i] = (uart_struct*) (UART0_START+i*UART_OFFSET);
	}
}

/**
 * @fn int getchar()
 * @brief Function to read a single character from the standard input device.
 * @details This function will be called to write a single character from the stdin.
 * @return integer equivalent of the received character.
 */
#undef getchar
পূর্ণাঙ্ক getchar()
{
	যেতিয়ালৈ((uart_instance[0]->status & STS_RX_NOT_EMPTY) == 0); 
	ঘূৰাই (uart_instance[0]->rcv_reg);
}

/**
 * @fn int putchar(int ch)
 * @brief Function to write a single character to the standard output device.
 * @details This function will be called to print a single character to the stdout by passing 
 * character as an integer.
 * @param character as int.
 * @return Zero
 */
#undef putchar
পূর্ণাঙ্ক putchar(পূর্ণাঙ্ক ch)
{
	যেতিয়ালৈ(uart_instance[0]->status & STS_TX_FULL);

	uart_instance[0]->tx_reg = ch;

	ঘূৰাই 0;
}

/**
 * @fn void set_baud_rate(uart_struct * UART, unsigned int baudrate)
 * @brief Function to initialize a specific UART with the baudrate.
 * @details This function will be called to initialize a specific UART by passing baudrate value
 * which in turn used to calculate the baud_count to set the baudrate.
 * @param UART instance
 * @param unsigned int baudrate
 */
শূন্য set_baud_rate(uart_struct *instance, unsigned পূর্ণাঙ্ক baudrate)
{
	unsigned পূর্ণাঙ্ক baud_গুনতি = 0;
	baud_গুনতি = CLOCK_FREQUENCY / (16 * baudrate);
	instance->baud = baud_গুনতি;
}

/**
 * @fn void enable_uart_interrupts(uart_struct * instance, unsigned char interrupt) 
 * @brief Function to enable the interrupts of a perticular uart instance.
 * @details This function will be called to enable the interrupts of a specific uart instance by passing
 * the interrupt's values.
 * @param uart instance 
 * @param unsigned char interrupt
 */
শূন্য enable_uart_interrupts(uart_struct * instance, unsigned ৱর্ণ interrupt)
{
	instance->ien = interrupt; 
}

#ifdef USE_RX_THRESHOLD
/**
 * @fn void set_uart_rx_threshold(uart_struct * instance, unsigned char rxthreshold)
 * @brief Funtion to set the threshold value of the Rx FIFO.
 * @details This function will be called to set the threshold value of the Rx FIFO of a specific uart instance
 * by passing the threshold value.
 * @param uart instance 
 * @param unsigned char rxthreshold
 */
শূন্য set_uart_rx_threshold(uart_struct * instance, unsigned ৱর্ণ rxthreshold)
{
	instance->rx_threshold = rxthreshold;
}
#endif

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
	যেতিয়ালৈ(instance->status & STS_TX_FULL);

	instance->tx_reg = prn_character;

	ঘূৰাই 0;
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
	uint8_t temp;

	কৰা
	{
		temp = ptr_string[i++];
		write_uart_character(instance, temp);
	} যেতিয়ালৈ(temp != 0);

	ঘূৰাই 0;
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
uint8_t read_uart_character(uart_struct * instance, ৱর্ণ * prn_character)
{
	uint8_t temp = 0;

	যেতিয়ালৈ ((instance->status & STS_RX_NOT_EMPTY) == 0);

	temp = instance->rcv_reg;
	*prn_character = temp;

	ঘূৰাই 1;
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
uint8_t read_uart_string(uart_struct * instance, ৱর্ণ * ptr_string)
{
	uint32_t i = 0;
	uint8_t temp = 0;

	যেতিয়ালৈ(1)
	{
		যেতিয়ালৈ ((instance->status & STS_RX_NOT_EMPTY) == 0);

		temp = instance->rcv_reg;
		ptr_string[i++] = temp;
		putchar(temp);

		যদি (temp == 0x0D)
		{
			ptr_string[i++] = 0x0A;
			ptr_string[i++] = 0x00;
			ঘূৰাই(i);
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
শূন্য flush_uart(uart_struct * instance)
{
	__attribute__((unused)) ৱর্ণ temp;

	যেতিয়ালৈ ((instance->status & STS_RX_NOT_EMPTY) != 0)
	{
		temp = instance->rcv_reg ;
	}
}

/*Enable USE_INTERRUPT in command line*/

#ifdef USE_INTERRUPT
/**
 * @fn unsigned char uart0_isr()
 * @brief Function to offer interrupt service routine for uart_instance[0].
 * @details This function will be called to offer interrupt service routine for UART0 to read the
 * array of characters by handling interrupts such as RX_threshold, Rx_full, and RX_not_empty
 * based on the Rx fifo status and handles accordingly.
 * @return Currently not returning any value
 */
unsigned ৱর্ণ uart0_isr()
{
	uint32_t read_মান = '\0';

	যদি(uart_instance[0]->status & STS_RX_THRESHOLD)
	{
		যেতিয়ালৈ(uart_instance[0]->status & STS_RX_NOT_EMPTY)
		{
			read_মান = uart_instance[0]->rcv_reg;
			u0_rcv_char[uart0_rcv_isr_গুনতি++] = read_মান;
			write_uart_character(uart_instance[0], read_মান);
		}
	}
	অন্যথা যদি(uart_instance[0]->status & STS_RX_FULL)
	{
		write_word(GPIO_DIRECTION_CNTRL_REG, RTS);
		write_word(GPIO_DATA_REG, read_word(GPIO_DATA_REG) | RTS);

		যেতিয়ালৈ(uart_instance[0]->status & STS_RX_NOT_EMPTY)
		{
			read_মান = uart_instance[0]->rcv_reg;
			u0_rcv_char[uart0_rcv_isr_গুনতি++] = read_মান;
			write_uart_character(uart_instance[0], read_মান);
		}
		write_word(GPIO_DATA_REG, read_word(GPIO_DATA_REG) & ~(RTS));
	}
	অন্যথা যদি(uart_instance[0]->status & STS_RX_NOT_EMPTY)
	{
		read_মান = uart_instance[0]->rcv_reg;
		u0_rcv_char[uart0_rcv_isr_গুনতি++] = read_মান;
		write_uart_character(uart_instance[0], read_মান);
	}
	ঘূৰাই 0;
}

/**
 * @fn unsigned char uart1_isr()
 * @brief Function to offer interrupt service routine for uart_instance[1].
 * @details This function will be called to offer interrupt service routine for uart_instance[1] to read the
 * array of characters by handling interrupts such as RX_threshold, Rx_full, and RX_not_empty
 * based on the Rx fifo status and handles accordingly.
 * @return Currently not returning any value
 */
unsigned ৱর্ণ uart1_isr()
{
	uint32_t read_মান = '\0';

	যদি(uart_instance[1]->status & STS_RX_THRESHOLD)
	{
		যেতিয়ালৈ(uart_instance[1]->status & STS_RX_NOT_EMPTY)
		{
			read_মান = uart_instance[1]->rcv_reg;
			u1_rcv_char[uart1_rcv_isr_গুনতি++] = read_মান;
			write_uart_character(uart_instance[1], read_মান);
		}
	}
	অন্যথা যদি(uart_instance[1]->status & STS_RX_FULL)
	{
		write_word(GPIO_DIRECTION_CNTRL_REG, RTS);
		write_word(GPIO_DATA_REG, read_word(GPIO_DATA_REG) | RTS);

		যেতিয়ালৈ(uart_instance[1]->status & STS_RX_NOT_EMPTY)
		{
			read_মান = uart_instance[1]->rcv_reg;
			u1_rcv_char[uart1_rcv_isr_গুনতি++] = read_মান;
			write_uart_character(uart_instance[1], read_মান);
		}
		write_word(GPIO_DATA_REG, read_word(GPIO_DATA_REG) & ~(RTS));
	}
	অন্যথা যদি(uart_instance[1]->status & STS_RX_NOT_EMPTY)
	{
		read_মান = uart_instance[1]->rcv_reg;
		u1_rcv_char[uart1_rcv_isr_গুনতি++] = read_মান;
		write_uart_character(uart_instance[1], read_মান);
	}
	ঘূৰাই 0;
}

/**
 * @fn unsigned char uart2_isr()
 * @brief Function to offer interrupt service routine for UART2.
 * @details This function will be called to offer interrupt service routine for UART2 to read the
 * array of characters by handling interrupts such as RX_threshold, Rx_full, and RX_not_empty
 * based on the Rx fifo status and handles accordingly.
 * @return Currently not returning any value
 */
unsigned ৱর্ণ uart2_isr()
{
	uint32_t read_মান = '\0';

	যদি(uart_instance[2]->status & STS_RX_THRESHOLD)
	{
		যেতিয়ালৈ(uart_instance[2]->status & STS_RX_NOT_EMPTY)
		{
			read_মান = uart_instance[2]->rcv_reg;
			u2_rcv_char[uart2_rcv_isr_গুনতি++] = read_মান;
			write_uart_character(uart_instance[2], read_মান);
		}
	}
	অন্যথা যদি(uart_instance[2]->status & STS_RX_FULL)
	{
		write_word(GPIO_DIRECTION_CNTRL_REG, RTS);
		write_word(GPIO_DATA_REG, read_word(GPIO_DATA_REG) | RTS);

		যেতিয়ালৈ(uart_instance[2]->status & STS_RX_NOT_EMPTY)
		{
			read_মান = uart_instance[2]->rcv_reg;
			u2_rcv_char[uart2_rcv_isr_গুনতি++] = read_মান;
			write_uart_character(uart_instance[2], read_মান);
		}
		write_word(GPIO_DATA_REG, read_word(GPIO_DATA_REG) & ~(RTS));
	}
	অন্যথা যদি(uart_instance[2]->status & STS_RX_NOT_EMPTY)
	{
		read_মান = uart_instance[2]->rcv_reg;
		u2_rcv_char[uart2_rcv_isr_গুনতি++] = read_মান;
		write_uart_character(uart_instance[2], read_মান);
	}
	ঘূৰাই 0;
}
#endif
