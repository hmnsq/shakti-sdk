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

#ਅਨ੍ਤਰ੍ਭਾਵ "uart.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gpio.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "utils.h"

uart_struct *uart_instance[MAX_UART_ਗਿਣਤੀ];

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RTS GPIO4
//#define USE_INTERRUPT 

ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ uart0_complete = 0;
ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ uart1_complete = 0;
ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ uart2_complete = 0;
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ uart0_tx_isr_ਗਿਣਤੀ = 0;
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ uart0_rcv_isr_ਗਿਣਤੀ = 0;
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ uart1_tx_isr_ਗਿਣਤੀ = 0;
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ uart1_rcv_isr_ਗਿਣਤੀ = 0;
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ uart2_tx_isr_ਗਿਣਤੀ = 0;
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ uart2_rcv_isr_ਗਿਣਤੀ = 0;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ USE_ਰੁਕਾਵਟ
ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ u0_rcv_char[UARTX_ਬਫਰ_ਮਾਪ] = {'\0'};
ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ u1_rcv_char[UARTX_ਬਫਰ_ਮਾਪ] = {'\0'};
ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ u2_rcv_char[UARTX_ਬਫਰ_ਮਾਪ] = {'\0'};
#ਜੇ_ਅੰਤ

/**
 * @fn void uart_init()
 * @brief Initialise UART Array 
 * @details Initialises given number of UART Arrays which has 
 *          complete set of UART registers.
 */
ਖਾਲੀ uart_init()
{
	ਲਈ(ਪੂਰਨ i=0; i< MAX_UART_ਗਿਣਤੀ; i++)
	{
		uart_instance[i] = (uart_struct*) (UART0_ਸ਼ੁਰੂ+i*UART_ਵਿੱਥ);
	}
}

/**
 * @fn int getchar()
 * @brief Function to read a single character from the standard input device.
 * @details This function will be called to write a single character from the stdin.
 * @return integer equivalent of the received character.
 */
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ getchar
ਪੂਰਨ getchar()
{
	ਜਦੋਂ((uart_instance[0]->ਸਥਿਤੀ_2 & STS_RX_NOT_ਖਾਲੀ_ਥਾਵਾਂ) == 0); 
	ਵਾਪਸ (uart_instance[0]->rcv_reg);
}

/**
 * @fn int putchar(int ch)
 * @brief Function to write a single character to the standard output device.
 * @details This function will be called to print a single character to the stdout by passing 
 * character as an integer.
 * @param character as int.
 * @return Zero
 */
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ ਅੱਖਰ_ਲਿਖੋ
ਪੂਰਨ ਅੱਖਰ_ਲਿਖੋ(ਪੂਰਨ ch)
{
	ਜਦੋਂ(uart_instance[0]->ਸਥਿਤੀ_2 & STS_TX_ਭਰਿਆ);

	uart_instance[0]->tx_reg = ch;

	ਵਾਪਸ 0;
}

/**
 * @fn void set_baud_rate(uart_struct * UART, unsigned int baudrate)
 * @brief Function to initialize a specific UART with the baudrate.
 * @details This function will be called to initialize a specific UART by passing baudrate value
 * which in turn used to calculate the baud_count to set the baudrate.
 * @param UART instance
 * @param unsigned int baudrate
 */
ਖਾਲੀ ਸੈੱਟ_baud_ਦਰ(uart_struct *instance, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ baudrate)
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ baud_ਗਿਣਤੀ = 0;
	baud_ਗਿਣਤੀ = CLOCK_FREQUENCY / (16 * baudrate);
	instance->baud = baud_ਗਿਣਤੀ;
}

/**
 * @fn void enable_uart_interrupts(uart_struct * instance, unsigned char interrupt) 
 * @brief Function to enable the interrupts of a perticular uart instance.
 * @details This function will be called to enable the interrupts of a specific uart instance by passing
 * the interrupt's values.
 * @param uart instance 
 * @param unsigned char interrupt
 */
ਖਾਲੀ enable_uart_interrupts(uart_struct * instance, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਰੁਕਾਵਟ)
{
	instance->ien = ਰੁਕਾਵਟ; 
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ USE_RX_ਹੱਦ
/**
 * @fn void set_uart_rx_threshold(uart_struct * instance, unsigned char rxthreshold)
 * @brief Funtion to set the threshold value of the Rx FIFO.
 * @details This function will be called to set the threshold value of the Rx FIFO of a specific uart instance
 * by passing the threshold value.
 * @param uart instance 
 * @param unsigned char rxthreshold
 */
ਖਾਲੀ ਸੈੱਟ_uart_rx_ਹੱਦ(uart_struct * instance, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ rxthreshold)
{
	instance->rx_ਹੱਦ = rxthreshold;
}
#ਜੇ_ਅੰਤ

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
	ਜਦੋਂ(instance->ਸਥਿਤੀ_2 & STS_TX_ਭਰਿਆ);

	instance->tx_reg = prn_character;

	ਵਾਪਸ 0;
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
	uint8_t ਆਰਜ਼ੀ;

	ਕਰੋ
	{
		ਆਰਜ਼ੀ = ptr_string[i++];
		write_uart_character(instance, ਆਰਜ਼ੀ);
	} ਜਦੋਂ(ਆਰਜ਼ੀ != 0);

	ਵਾਪਸ 0;
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
uint8_t read_uart_character(uart_struct * instance, ਅੱਖਰ * prn_character)
{
	uint8_t ਆਰਜ਼ੀ = 0;

	ਜਦੋਂ ((instance->ਸਥਿਤੀ_2 & STS_RX_NOT_ਖਾਲੀ_ਥਾਵਾਂ) == 0);

	ਆਰਜ਼ੀ = instance->rcv_reg;
	*prn_character = ਆਰਜ਼ੀ;

	ਵਾਪਸ 1;
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
uint8_t read_uart_string(uart_struct * instance, ਅੱਖਰ * ptr_string)
{
	uint32_t i = 0;
	uint8_t ਆਰਜ਼ੀ = 0;

	ਜਦੋਂ(1)
	{
		ਜਦੋਂ ((instance->ਸਥਿਤੀ_2 & STS_RX_NOT_ਖਾਲੀ_ਥਾਵਾਂ) == 0);

		ਆਰਜ਼ੀ = instance->rcv_reg;
		ptr_string[i++] = ਆਰਜ਼ੀ;
		ਅੱਖਰ_ਲਿਖੋ(ਆਰਜ਼ੀ);

		ਜੇ (ਆਰਜ਼ੀ == 0x0D)
		{
			ptr_string[i++] = 0x0A;
			ptr_string[i++] = 0x00;
			ਵਾਪਸ(i);
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
ਖਾਲੀ flush_uart(uart_struct * instance)
{
	__attribute__((ਅਣਵਰਤਿਆ)) ਅੱਖਰ ਆਰਜ਼ੀ;

	ਜਦੋਂ ((instance->ਸਥਿਤੀ_2 & STS_RX_NOT_ਖਾਲੀ_ਥਾਵਾਂ) != 0)
	{
		ਆਰਜ਼ੀ = instance->rcv_reg ;
	}
}

/*Enable USE_INTERRUPT in command line*/

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ USE_ਰੁਕਾਵਟ
/**
 * @fn unsigned char uart0_isr()
 * @brief Function to offer interrupt service routine for uart_instance[0].
 * @details This function will be called to offer interrupt service routine for UART0 to read the
 * array of characters by handling interrupts such as RX_threshold, Rx_full, and RX_not_empty
 * based on the Rx fifo status and handles accordingly.
 * @return Currently not returning any value
 */
ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ uart0_isr()
{
	uint32_t read_ਮੁੱਲ = '\0';

	ਜੇ(uart_instance[0]->ਸਥਿਤੀ_2 & STS_RX_ਹੱਦ)
	{
		ਜਦੋਂ(uart_instance[0]->ਸਥਿਤੀ_2 & STS_RX_NOT_ਖਾਲੀ_ਥਾਵਾਂ)
		{
			read_ਮੁੱਲ = uart_instance[0]->rcv_reg;
			u0_rcv_char[uart0_rcv_isr_ਗਿਣਤੀ++] = read_ਮੁੱਲ;
			write_uart_character(uart_instance[0], read_ਮੁੱਲ);
		}
	}
	ਨਹੀਂਤਾਂ ਜੇ(uart_instance[0]->ਸਥਿਤੀ_2 & STS_RX_ਭਰਿਆ)
	{
		write_ਸ਼ਬਦ(GPIO_DIRECTION_CNTRL_REG, RTS);
		write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) | RTS);

		ਜਦੋਂ(uart_instance[0]->ਸਥਿਤੀ_2 & STS_RX_NOT_ਖਾਲੀ_ਥਾਵਾਂ)
		{
			read_ਮੁੱਲ = uart_instance[0]->rcv_reg;
			u0_rcv_char[uart0_rcv_isr_ਗਿਣਤੀ++] = read_ਮੁੱਲ;
			write_uart_character(uart_instance[0], read_ਮੁੱਲ);
		}
		write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) & ~(RTS));
	}
	ਨਹੀਂਤਾਂ ਜੇ(uart_instance[0]->ਸਥਿਤੀ_2 & STS_RX_NOT_ਖਾਲੀ_ਥਾਵਾਂ)
	{
		read_ਮੁੱਲ = uart_instance[0]->rcv_reg;
		u0_rcv_char[uart0_rcv_isr_ਗਿਣਤੀ++] = read_ਮੁੱਲ;
		write_uart_character(uart_instance[0], read_ਮੁੱਲ);
	}
	ਵਾਪਸ 0;
}

/**
 * @fn unsigned char uart1_isr()
 * @brief Function to offer interrupt service routine for uart_instance[1].
 * @details This function will be called to offer interrupt service routine for uart_instance[1] to read the
 * array of characters by handling interrupts such as RX_threshold, Rx_full, and RX_not_empty
 * based on the Rx fifo status and handles accordingly.
 * @return Currently not returning any value
 */
ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ uart1_isr()
{
	uint32_t read_ਮੁੱਲ = '\0';

	ਜੇ(uart_instance[1]->ਸਥਿਤੀ_2 & STS_RX_ਹੱਦ)
	{
		ਜਦੋਂ(uart_instance[1]->ਸਥਿਤੀ_2 & STS_RX_NOT_ਖਾਲੀ_ਥਾਵਾਂ)
		{
			read_ਮੁੱਲ = uart_instance[1]->rcv_reg;
			u1_rcv_char[uart1_rcv_isr_ਗਿਣਤੀ++] = read_ਮੁੱਲ;
			write_uart_character(uart_instance[1], read_ਮੁੱਲ);
		}
	}
	ਨਹੀਂਤਾਂ ਜੇ(uart_instance[1]->ਸਥਿਤੀ_2 & STS_RX_ਭਰਿਆ)
	{
		write_ਸ਼ਬਦ(GPIO_DIRECTION_CNTRL_REG, RTS);
		write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) | RTS);

		ਜਦੋਂ(uart_instance[1]->ਸਥਿਤੀ_2 & STS_RX_NOT_ਖਾਲੀ_ਥਾਵਾਂ)
		{
			read_ਮੁੱਲ = uart_instance[1]->rcv_reg;
			u1_rcv_char[uart1_rcv_isr_ਗਿਣਤੀ++] = read_ਮੁੱਲ;
			write_uart_character(uart_instance[1], read_ਮੁੱਲ);
		}
		write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) & ~(RTS));
	}
	ਨਹੀਂਤਾਂ ਜੇ(uart_instance[1]->ਸਥਿਤੀ_2 & STS_RX_NOT_ਖਾਲੀ_ਥਾਵਾਂ)
	{
		read_ਮੁੱਲ = uart_instance[1]->rcv_reg;
		u1_rcv_char[uart1_rcv_isr_ਗਿਣਤੀ++] = read_ਮੁੱਲ;
		write_uart_character(uart_instance[1], read_ਮੁੱਲ);
	}
	ਵਾਪਸ 0;
}

/**
 * @fn unsigned char uart2_isr()
 * @brief Function to offer interrupt service routine for UART2.
 * @details This function will be called to offer interrupt service routine for UART2 to read the
 * array of characters by handling interrupts such as RX_threshold, Rx_full, and RX_not_empty
 * based on the Rx fifo status and handles accordingly.
 * @return Currently not returning any value
 */
ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ uart2_isr()
{
	uint32_t read_ਮੁੱਲ = '\0';

	ਜੇ(uart_instance[2]->ਸਥਿਤੀ_2 & STS_RX_ਹੱਦ)
	{
		ਜਦੋਂ(uart_instance[2]->ਸਥਿਤੀ_2 & STS_RX_NOT_ਖਾਲੀ_ਥਾਵਾਂ)
		{
			read_ਮੁੱਲ = uart_instance[2]->rcv_reg;
			u2_rcv_char[uart2_rcv_isr_ਗਿਣਤੀ++] = read_ਮੁੱਲ;
			write_uart_character(uart_instance[2], read_ਮੁੱਲ);
		}
	}
	ਨਹੀਂਤਾਂ ਜੇ(uart_instance[2]->ਸਥਿਤੀ_2 & STS_RX_ਭਰਿਆ)
	{
		write_ਸ਼ਬਦ(GPIO_DIRECTION_CNTRL_REG, RTS);
		write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) | RTS);

		ਜਦੋਂ(uart_instance[2]->ਸਥਿਤੀ_2 & STS_RX_NOT_ਖਾਲੀ_ਥਾਵਾਂ)
		{
			read_ਮੁੱਲ = uart_instance[2]->rcv_reg;
			u2_rcv_char[uart2_rcv_isr_ਗਿਣਤੀ++] = read_ਮੁੱਲ;
			write_uart_character(uart_instance[2], read_ਮੁੱਲ);
		}
		write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) & ~(RTS));
	}
	ਨਹੀਂਤਾਂ ਜੇ(uart_instance[2]->ਸਥਿਤੀ_2 & STS_RX_NOT_ਖਾਲੀ_ਥਾਵਾਂ)
	{
		read_ਮੁੱਲ = uart_instance[2]->rcv_reg;
		u2_rcv_char[uart2_rcv_isr_ਗਿਣਤੀ++] = read_ਮੁੱਲ;
		write_uart_character(uart_instance[2], read_ਮੁੱਲ);
	}
	ਵਾਪਸ 0;
}
#ਜੇ_ਅੰਤ
