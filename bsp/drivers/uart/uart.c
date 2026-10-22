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

#ಅನ್ತರ್ಭಾವ "uart.h"
#ಅನ್ತರ್ಭಾವ "gpio.h"
#ಅನ್ತರ್ಭಾವ "utils.h"

uart_struct *uart_instance[MAX_UART_ಎಣಿಕೆ];

#ವ್ಯಾಖ್ಯಾನಿಸು RTS GPIO4
//#define USE_INTERRUPT 

ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ uart0_complete = 0;
ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ uart1_complete = 0;
ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ uart2_complete = 0;
ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ uart0_tx_isr_ಎಣಿಕೆ = 0;
ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ uart0_rcv_isr_ಎಣಿಕೆ = 0;
ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ uart1_tx_isr_ಎಣಿಕೆ = 0;
ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ uart1_rcv_isr_ಎಣಿಕೆ = 0;
ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ uart2_tx_isr_ಎಣಿಕೆ = 0;
ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ uart2_rcv_isr_ಎಣಿಕೆ = 0;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ USE_ಅಡಚಣೆ
ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ u0_rcv_char[UARTX_ಬಫರ್_ಗಾತ್ರ] = {'\0'};
ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ u1_rcv_char[UARTX_ಬಫರ್_ಗಾತ್ರ] = {'\0'};
ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ u2_rcv_char[UARTX_ಬಫರ್_ಗಾತ್ರ] = {'\0'};
#ಆದರೆ_ಅಂತ್ಯ

/**
 * @fn void uart_init()
 * @brief Initialise UART Array 
 * @details Initialises given number of UART Arrays which has 
 *          complete set of UART registers.
 */
ಶೂನ್ಯ uart_init()
{
	ಗಾಗಿ(ಪೂರ್ಣಾಂಕ i=0; i< MAX_UART_ಎಣಿಕೆ; i++)
	{
		uart_instance[i] = (uart_struct*) (UART0_ಆರಂಭ+i*UART_ಸ್ಥಾನಾಂತರ);
	}
}

/**
 * @fn int getchar()
 * @brief Function to read a single character from the standard input device.
 * @details This function will be called to write a single character from the stdin.
 * @return integer equivalent of the received character.
 */
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು getchar
ಪೂರ್ಣಾಂಕ getchar()
{
	ಆಗ((uart_instance[0]->ಸ್ಥಿತಿ_3 & STS_RX_NOT_ಖಾಲಿಗಳು) == 0); 
	ಹಿಂತಿರುಗಿ (uart_instance[0]->rcv_reg);
}

/**
 * @fn int putchar(int ch)
 * @brief Function to write a single character to the standard output device.
 * @details This function will be called to print a single character to the stdout by passing 
 * character as an integer.
 * @param character as int.
 * @return Zero
 */
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು ಅಕ್ಷರ_ಬರೆ
ಪೂರ್ಣಾಂಕ ಅಕ್ಷರ_ಬರೆ(ಪೂರ್ಣಾಂಕ ch)
{
	ಆಗ(uart_instance[0]->ಸ್ಥಿತಿ_3 & STS_TX_ತುಂಬಿದ);

	uart_instance[0]->tx_reg = ch;

	ಹಿಂತಿರುಗಿ 0;
}

/**
 * @fn void set_baud_rate(uart_struct * UART, unsigned int baudrate)
 * @brief Function to initialize a specific UART with the baudrate.
 * @details This function will be called to initialize a specific UART by passing baudrate value
 * which in turn used to calculate the baud_count to set the baudrate.
 * @param UART instance
 * @param unsigned int baudrate
 */
ಶೂನ್ಯ ಗಣ_baud_ದರ(uart_struct *instance, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ baudrate)
{
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ baud_ಎಣಿಕೆ = 0;
	baud_ಎಣಿಕೆ = CLOCK_FREQUENCY / (16 * baudrate);
	instance->baud = baud_ಎಣಿಕೆ;
}

/**
 * @fn void enable_uart_interrupts(uart_struct * instance, unsigned char interrupt) 
 * @brief Function to enable the interrupts of a perticular uart instance.
 * @details This function will be called to enable the interrupts of a specific uart instance by passing
 * the interrupt's values.
 * @param uart instance 
 * @param unsigned char interrupt
 */
ಶೂನ್ಯ enable_uart_interrupts(uart_struct * instance, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ಅಡಚಣೆ)
{
	instance->ien = ಅಡಚಣೆ; 
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ USE_RX_ಮಿತಿ
/**
 * @fn void set_uart_rx_threshold(uart_struct * instance, unsigned char rxthreshold)
 * @brief Funtion to set the threshold value of the Rx FIFO.
 * @details This function will be called to set the threshold value of the Rx FIFO of a specific uart instance
 * by passing the threshold value.
 * @param uart instance 
 * @param unsigned char rxthreshold
 */
ಶೂನ್ಯ ಗಣ_uart_rx_ಮಿತಿ(uart_struct * instance, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ rxthreshold)
{
	instance->rx_ಮಿತಿ = rxthreshold;
}
#ಆದರೆ_ಅಂತ್ಯ

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
	ಆಗ(instance->ಸ್ಥಿತಿ_3 & STS_TX_ತುಂಬಿದ);

	instance->tx_reg = prn_character;

	ಹಿಂತಿರುಗಿ 0;
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
	uint8_t ತಾತ್ಕಾಲಿಕ;

	ಮಾಡು
	{
		ತಾತ್ಕಾಲಿಕ = ptr_string[i++];
		write_uart_character(instance, ತಾತ್ಕಾಲಿಕ);
	} ಆಗ(ತಾತ್ಕಾಲಿಕ != 0);

	ಹಿಂತಿರುಗಿ 0;
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
uint8_t read_uart_character(uart_struct * instance, ಅಕ್ಷರ * prn_character)
{
	uint8_t ತಾತ್ಕಾಲಿಕ = 0;

	ಆಗ ((instance->ಸ್ಥಿತಿ_3 & STS_RX_NOT_ಖಾಲಿಗಳು) == 0);

	ತಾತ್ಕಾಲಿಕ = instance->rcv_reg;
	*prn_character = ತಾತ್ಕಾಲಿಕ;

	ಹಿಂತಿರುಗಿ 1;
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
uint8_t read_uart_string(uart_struct * instance, ಅಕ್ಷರ * ptr_string)
{
	uint32_t i = 0;
	uint8_t ತಾತ್ಕಾಲಿಕ = 0;

	ಆಗ(1)
	{
		ಆಗ ((instance->ಸ್ಥಿತಿ_3 & STS_RX_NOT_ಖಾಲಿಗಳು) == 0);

		ತಾತ್ಕಾಲಿಕ = instance->rcv_reg;
		ptr_string[i++] = ತಾತ್ಕಾಲಿಕ;
		ಅಕ್ಷರ_ಬರೆ(ತಾತ್ಕಾಲಿಕ);

		ಆದರೆ (ತಾತ್ಕಾಲಿಕ == 0x0D)
		{
			ptr_string[i++] = 0x0A;
			ptr_string[i++] = 0x00;
			ಹಿಂತಿರುಗಿ(i);
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
ಶೂನ್ಯ flush_uart(uart_struct * instance)
{
	__attribute__((ಬಳಸದ)) ಅಕ್ಷರ ತಾತ್ಕಾಲಿಕ;

	ಆಗ ((instance->ಸ್ಥಿತಿ_3 & STS_RX_NOT_ಖಾಲಿಗಳು) != 0)
	{
		ತಾತ್ಕಾಲಿಕ = instance->rcv_reg ;
	}
}

/*Enable USE_INTERRUPT in command line*/

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ USE_ಅಡಚಣೆ
/**
 * @fn unsigned char uart0_isr()
 * @brief Function to offer interrupt service routine for uart_instance[0].
 * @details This function will be called to offer interrupt service routine for UART0 to read the
 * array of characters by handling interrupts such as RX_threshold, Rx_full, and RX_not_empty
 * based on the Rx fifo status and handles accordingly.
 * @return Currently not returning any value
 */
ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ uart0_isr()
{
	uint32_t read_ಮೌಲ್ಯ = '\0';

	ಆದರೆ(uart_instance[0]->ಸ್ಥಿತಿ_3 & STS_RX_ಮಿತಿ)
	{
		ಆಗ(uart_instance[0]->ಸ್ಥಿತಿ_3 & STS_RX_NOT_ಖಾಲಿಗಳು)
		{
			read_ಮೌಲ್ಯ = uart_instance[0]->rcv_reg;
			u0_rcv_char[uart0_rcv_isr_ಎಣಿಕೆ++] = read_ಮೌಲ್ಯ;
			write_uart_character(uart_instance[0], read_ಮೌಲ್ಯ);
		}
	}
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ(uart_instance[0]->ಸ್ಥಿತಿ_3 & STS_RX_ತುಂಬಿದ)
	{
		write_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG, RTS);
		write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) | RTS);

		ಆಗ(uart_instance[0]->ಸ್ಥಿತಿ_3 & STS_RX_NOT_ಖಾಲಿಗಳು)
		{
			read_ಮೌಲ್ಯ = uart_instance[0]->rcv_reg;
			u0_rcv_char[uart0_rcv_isr_ಎಣಿಕೆ++] = read_ಮೌಲ್ಯ;
			write_uart_character(uart_instance[0], read_ಮೌಲ್ಯ);
		}
		write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) & ~(RTS));
	}
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ(uart_instance[0]->ಸ್ಥಿತಿ_3 & STS_RX_NOT_ಖಾಲಿಗಳು)
	{
		read_ಮೌಲ್ಯ = uart_instance[0]->rcv_reg;
		u0_rcv_char[uart0_rcv_isr_ಎಣಿಕೆ++] = read_ಮೌಲ್ಯ;
		write_uart_character(uart_instance[0], read_ಮೌಲ್ಯ);
	}
	ಹಿಂತಿರುಗಿ 0;
}

/**
 * @fn unsigned char uart1_isr()
 * @brief Function to offer interrupt service routine for uart_instance[1].
 * @details This function will be called to offer interrupt service routine for uart_instance[1] to read the
 * array of characters by handling interrupts such as RX_threshold, Rx_full, and RX_not_empty
 * based on the Rx fifo status and handles accordingly.
 * @return Currently not returning any value
 */
ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ uart1_isr()
{
	uint32_t read_ಮೌಲ್ಯ = '\0';

	ಆದರೆ(uart_instance[1]->ಸ್ಥಿತಿ_3 & STS_RX_ಮಿತಿ)
	{
		ಆಗ(uart_instance[1]->ಸ್ಥಿತಿ_3 & STS_RX_NOT_ಖಾಲಿಗಳು)
		{
			read_ಮೌಲ್ಯ = uart_instance[1]->rcv_reg;
			u1_rcv_char[uart1_rcv_isr_ಎಣಿಕೆ++] = read_ಮೌಲ್ಯ;
			write_uart_character(uart_instance[1], read_ಮೌಲ್ಯ);
		}
	}
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ(uart_instance[1]->ಸ್ಥಿತಿ_3 & STS_RX_ತುಂಬಿದ)
	{
		write_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG, RTS);
		write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) | RTS);

		ಆಗ(uart_instance[1]->ಸ್ಥಿತಿ_3 & STS_RX_NOT_ಖಾಲಿಗಳು)
		{
			read_ಮೌಲ್ಯ = uart_instance[1]->rcv_reg;
			u1_rcv_char[uart1_rcv_isr_ಎಣಿಕೆ++] = read_ಮೌಲ್ಯ;
			write_uart_character(uart_instance[1], read_ಮೌಲ್ಯ);
		}
		write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) & ~(RTS));
	}
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ(uart_instance[1]->ಸ್ಥಿತಿ_3 & STS_RX_NOT_ಖಾಲಿಗಳು)
	{
		read_ಮೌಲ್ಯ = uart_instance[1]->rcv_reg;
		u1_rcv_char[uart1_rcv_isr_ಎಣಿಕೆ++] = read_ಮೌಲ್ಯ;
		write_uart_character(uart_instance[1], read_ಮೌಲ್ಯ);
	}
	ಹಿಂತಿರುಗಿ 0;
}

/**
 * @fn unsigned char uart2_isr()
 * @brief Function to offer interrupt service routine for UART2.
 * @details This function will be called to offer interrupt service routine for UART2 to read the
 * array of characters by handling interrupts such as RX_threshold, Rx_full, and RX_not_empty
 * based on the Rx fifo status and handles accordingly.
 * @return Currently not returning any value
 */
ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ uart2_isr()
{
	uint32_t read_ಮೌಲ್ಯ = '\0';

	ಆದರೆ(uart_instance[2]->ಸ್ಥಿತಿ_3 & STS_RX_ಮಿತಿ)
	{
		ಆಗ(uart_instance[2]->ಸ್ಥಿತಿ_3 & STS_RX_NOT_ಖಾಲಿಗಳು)
		{
			read_ಮೌಲ್ಯ = uart_instance[2]->rcv_reg;
			u2_rcv_char[uart2_rcv_isr_ಎಣಿಕೆ++] = read_ಮೌಲ್ಯ;
			write_uart_character(uart_instance[2], read_ಮೌಲ್ಯ);
		}
	}
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ(uart_instance[2]->ಸ್ಥಿತಿ_3 & STS_RX_ತುಂಬಿದ)
	{
		write_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG, RTS);
		write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) | RTS);

		ಆಗ(uart_instance[2]->ಸ್ಥಿತಿ_3 & STS_RX_NOT_ಖಾಲಿಗಳು)
		{
			read_ಮೌಲ್ಯ = uart_instance[2]->rcv_reg;
			u2_rcv_char[uart2_rcv_isr_ಎಣಿಕೆ++] = read_ಮೌಲ್ಯ;
			write_uart_character(uart_instance[2], read_ಮೌಲ್ಯ);
		}
		write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) & ~(RTS));
	}
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ(uart_instance[2]->ಸ್ಥಿತಿ_3 & STS_RX_NOT_ಖಾಲಿಗಳು)
	{
		read_ಮೌಲ್ಯ = uart_instance[2]->rcv_reg;
		u2_rcv_char[uart2_rcv_isr_ಎಣಿಕೆ++] = read_ಮೌಲ್ಯ;
		write_uart_character(uart_instance[2], read_ಮೌಲ್ಯ);
	}
	ಹಿಂತಿರುಗಿ 0;
}
#ಆದರೆ_ಅಂತ್ಯ
