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

#అన్తర్భావ "uart.h"
#అన్తర్భావ "gpio.h"
#అన్తర్భావ "utils.h"

uart_struct *uart_instance[MAX_UART_లెక్క];

#నిర్వచించు RTS GPIO4
//#define USE_INTERRUPT 

గుర్తులేని అక్షరం uart0_complete = 0;
గుర్తులేని అక్షరం uart1_complete = 0;
గుర్తులేని అక్షరం uart2_complete = 0;
గుర్తులేని పూర్ణాంకం uart0_tx_isr_లెక్క = 0;
గుర్తులేని పూర్ణాంకం uart0_rcv_isr_లెక్క = 0;
గుర్తులేని పూర్ణాంకం uart1_tx_isr_లెక్క = 0;
గుర్తులేని పూర్ణాంకం uart1_rcv_isr_లెక్క = 0;
గుర్తులేని పూర్ణాంకం uart2_tx_isr_లెక్క = 0;
గుర్తులేని పూర్ణాంకం uart2_rcv_isr_లెక్క = 0;

#నిర్వచితమైతే USE_అంతరాయం
గుర్తులేని అక్షరం u0_rcv_char[UARTX_బఫరు_కొలత] = {'\0'};
గుర్తులేని అక్షరం u1_rcv_char[UARTX_బఫరు_కొలత] = {'\0'};
గుర్తులేని అక్షరం u2_rcv_char[UARTX_బఫరు_కొలత] = {'\0'};
#అయితే_ముగింపు

/**
 * @fn void uart_init()
 * @brief Initialise UART Array 
 * @details Initialises given number of UART Arrays which has 
 *          complete set of UART registers.
 */
శూన్య uart_init()
{
	కొరకు(పూర్ణాంకం i=0; i< MAX_UART_లెక్క; i++)
	{
		uart_instance[i] = (uart_struct*) (UART0_ప్రారంభం+i*UART_స్థానభ్రంశం);
	}
}

/**
 * @fn int getchar()
 * @brief Function to read a single character from the standard input device.
 * @details This function will be called to write a single character from the stdin.
 * @return integer equivalent of the received character.
 */
#నిర్వచనం_రద్దు getchar
పూర్ణాంకం getchar()
{
	అయితే((uart_instance[0]->స్థితి_3 & STS_RX_NOT_ఖాళీలు) == 0); 
	తిరిగి (uart_instance[0]->rcv_reg);
}

/**
 * @fn int putchar(int ch)
 * @brief Function to write a single character to the standard output device.
 * @details This function will be called to print a single character to the stdout by passing 
 * character as an integer.
 * @param character as int.
 * @return Zero
 */
#నిర్వచనం_రద్దు అక్షరం_రాయి
పూర్ణాంకం అక్షరం_రాయి(పూర్ణాంకం ch)
{
	అయితే(uart_instance[0]->స్థితి_3 & STS_TX_నిండిన);

	uart_instance[0]->tx_reg = ch;

	తిరిగి 0;
}

/**
 * @fn void set_baud_rate(uart_struct * UART, unsigned int baudrate)
 * @brief Function to initialize a specific UART with the baudrate.
 * @details This function will be called to initialize a specific UART by passing baudrate value
 * which in turn used to calculate the baud_count to set the baudrate.
 * @param UART instance
 * @param unsigned int baudrate
 */
శూన్య సమితి_baud_రేటు(uart_struct *instance, గుర్తులేని పూర్ణాంకం baudrate)
{
	గుర్తులేని పూర్ణాంకం baud_లెక్క = 0;
	baud_లెక్క = CLOCK_FREQUENCY / (16 * baudrate);
	instance->baud = baud_లెక్క;
}

/**
 * @fn void enable_uart_interrupts(uart_struct * instance, unsigned char interrupt) 
 * @brief Function to enable the interrupts of a perticular uart instance.
 * @details This function will be called to enable the interrupts of a specific uart instance by passing
 * the interrupt's values.
 * @param uart instance 
 * @param unsigned char interrupt
 */
శూన్య enable_uart_interrupts(uart_struct * instance, గుర్తులేని అక్షరం అంతరాయం)
{
	instance->ien = అంతరాయం; 
}

#నిర్వచితమైతే USE_RX_పరిమితి
/**
 * @fn void set_uart_rx_threshold(uart_struct * instance, unsigned char rxthreshold)
 * @brief Funtion to set the threshold value of the Rx FIFO.
 * @details This function will be called to set the threshold value of the Rx FIFO of a specific uart instance
 * by passing the threshold value.
 * @param uart instance 
 * @param unsigned char rxthreshold
 */
శూన్య సమితి_uart_rx_పరిమితి(uart_struct * instance, గుర్తులేని అక్షరం rxthreshold)
{
	instance->rx_పరిమితి = rxthreshold;
}
#అయితే_ముగింపు

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
	అయితే(instance->స్థితి_3 & STS_TX_నిండిన);

	instance->tx_reg = prn_character;

	తిరిగి 0;
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
	uint8_t తాత్కాలిక;

	చేయి
	{
		తాత్కాలిక = ptr_string[i++];
		write_uart_character(instance, తాత్కాలిక);
	} అయితే(తాత్కాలిక != 0);

	తిరిగి 0;
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
uint8_t read_uart_character(uart_struct * instance, అక్షరం * prn_character)
{
	uint8_t తాత్కాలిక = 0;

	అయితే ((instance->స్థితి_3 & STS_RX_NOT_ఖాళీలు) == 0);

	తాత్కాలిక = instance->rcv_reg;
	*prn_character = తాత్కాలిక;

	తిరిగి 1;
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
uint8_t read_uart_string(uart_struct * instance, అక్షరం * ptr_string)
{
	uint32_t i = 0;
	uint8_t తాత్కాలిక = 0;

	అయితే(1)
	{
		అయితే ((instance->స్థితి_3 & STS_RX_NOT_ఖాళీలు) == 0);

		తాత్కాలిక = instance->rcv_reg;
		ptr_string[i++] = తాత్కాలిక;
		అక్షరం_రాయి(తాత్కాలిక);

		ఒకవేళ (తాత్కాలిక == 0x0D)
		{
			ptr_string[i++] = 0x0A;
			ptr_string[i++] = 0x00;
			తిరిగి(i);
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
శూన్య flush_uart(uart_struct * instance)
{
	__attribute__((వాడని)) అక్షరం తాత్కాలిక;

	అయితే ((instance->స్థితి_3 & STS_RX_NOT_ఖాళీలు) != 0)
	{
		తాత్కాలిక = instance->rcv_reg ;
	}
}

/*Enable USE_INTERRUPT in command line*/

#నిర్వచితమైతే USE_అంతరాయం
/**
 * @fn unsigned char uart0_isr()
 * @brief Function to offer interrupt service routine for uart_instance[0].
 * @details This function will be called to offer interrupt service routine for UART0 to read the
 * array of characters by handling interrupts such as RX_threshold, Rx_full, and RX_not_empty
 * based on the Rx fifo status and handles accordingly.
 * @return Currently not returning any value
 */
గుర్తులేని అక్షరం uart0_isr()
{
	uint32_t read_విలువ = '\0';

	ఒకవేళ(uart_instance[0]->స్థితి_3 & STS_RX_పరిమితి)
	{
		అయితే(uart_instance[0]->స్థితి_3 & STS_RX_NOT_ఖాళీలు)
		{
			read_విలువ = uart_instance[0]->rcv_reg;
			u0_rcv_char[uart0_rcv_isr_లెక్క++] = read_విలువ;
			write_uart_character(uart_instance[0], read_విలువ);
		}
	}
	లేకపోతే ఒకవేళ(uart_instance[0]->స్థితి_3 & STS_RX_నిండిన)
	{
		write_మాట(GPIO_DIRECTION_CNTRL_REG, RTS);
		write_మాట(GPIO_దత్తాంశం_REG, read_మాట(GPIO_దత్తాంశం_REG) | RTS);

		అయితే(uart_instance[0]->స్థితి_3 & STS_RX_NOT_ఖాళీలు)
		{
			read_విలువ = uart_instance[0]->rcv_reg;
			u0_rcv_char[uart0_rcv_isr_లెక్క++] = read_విలువ;
			write_uart_character(uart_instance[0], read_విలువ);
		}
		write_మాట(GPIO_దత్తాంశం_REG, read_మాట(GPIO_దత్తాంశం_REG) & ~(RTS));
	}
	లేకపోతే ఒకవేళ(uart_instance[0]->స్థితి_3 & STS_RX_NOT_ఖాళీలు)
	{
		read_విలువ = uart_instance[0]->rcv_reg;
		u0_rcv_char[uart0_rcv_isr_లెక్క++] = read_విలువ;
		write_uart_character(uart_instance[0], read_విలువ);
	}
	తిరిగి 0;
}

/**
 * @fn unsigned char uart1_isr()
 * @brief Function to offer interrupt service routine for uart_instance[1].
 * @details This function will be called to offer interrupt service routine for uart_instance[1] to read the
 * array of characters by handling interrupts such as RX_threshold, Rx_full, and RX_not_empty
 * based on the Rx fifo status and handles accordingly.
 * @return Currently not returning any value
 */
గుర్తులేని అక్షరం uart1_isr()
{
	uint32_t read_విలువ = '\0';

	ఒకవేళ(uart_instance[1]->స్థితి_3 & STS_RX_పరిమితి)
	{
		అయితే(uart_instance[1]->స్థితి_3 & STS_RX_NOT_ఖాళీలు)
		{
			read_విలువ = uart_instance[1]->rcv_reg;
			u1_rcv_char[uart1_rcv_isr_లెక్క++] = read_విలువ;
			write_uart_character(uart_instance[1], read_విలువ);
		}
	}
	లేకపోతే ఒకవేళ(uart_instance[1]->స్థితి_3 & STS_RX_నిండిన)
	{
		write_మాట(GPIO_DIRECTION_CNTRL_REG, RTS);
		write_మాట(GPIO_దత్తాంశం_REG, read_మాట(GPIO_దత్తాంశం_REG) | RTS);

		అయితే(uart_instance[1]->స్థితి_3 & STS_RX_NOT_ఖాళీలు)
		{
			read_విలువ = uart_instance[1]->rcv_reg;
			u1_rcv_char[uart1_rcv_isr_లెక్క++] = read_విలువ;
			write_uart_character(uart_instance[1], read_విలువ);
		}
		write_మాట(GPIO_దత్తాంశం_REG, read_మాట(GPIO_దత్తాంశం_REG) & ~(RTS));
	}
	లేకపోతే ఒకవేళ(uart_instance[1]->స్థితి_3 & STS_RX_NOT_ఖాళీలు)
	{
		read_విలువ = uart_instance[1]->rcv_reg;
		u1_rcv_char[uart1_rcv_isr_లెక్క++] = read_విలువ;
		write_uart_character(uart_instance[1], read_విలువ);
	}
	తిరిగి 0;
}

/**
 * @fn unsigned char uart2_isr()
 * @brief Function to offer interrupt service routine for UART2.
 * @details This function will be called to offer interrupt service routine for UART2 to read the
 * array of characters by handling interrupts such as RX_threshold, Rx_full, and RX_not_empty
 * based on the Rx fifo status and handles accordingly.
 * @return Currently not returning any value
 */
గుర్తులేని అక్షరం uart2_isr()
{
	uint32_t read_విలువ = '\0';

	ఒకవేళ(uart_instance[2]->స్థితి_3 & STS_RX_పరిమితి)
	{
		అయితే(uart_instance[2]->స్థితి_3 & STS_RX_NOT_ఖాళీలు)
		{
			read_విలువ = uart_instance[2]->rcv_reg;
			u2_rcv_char[uart2_rcv_isr_లెక్క++] = read_విలువ;
			write_uart_character(uart_instance[2], read_విలువ);
		}
	}
	లేకపోతే ఒకవేళ(uart_instance[2]->స్థితి_3 & STS_RX_నిండిన)
	{
		write_మాట(GPIO_DIRECTION_CNTRL_REG, RTS);
		write_మాట(GPIO_దత్తాంశం_REG, read_మాట(GPIO_దత్తాంశం_REG) | RTS);

		అయితే(uart_instance[2]->స్థితి_3 & STS_RX_NOT_ఖాళీలు)
		{
			read_విలువ = uart_instance[2]->rcv_reg;
			u2_rcv_char[uart2_rcv_isr_లెక్క++] = read_విలువ;
			write_uart_character(uart_instance[2], read_విలువ);
		}
		write_మాట(GPIO_దత్తాంశం_REG, read_మాట(GPIO_దత్తాంశం_REG) & ~(RTS));
	}
	లేకపోతే ఒకవేళ(uart_instance[2]->స్థితి_3 & STS_RX_NOT_ఖాళీలు)
	{
		read_విలువ = uart_instance[2]->rcv_reg;
		u2_rcv_char[uart2_rcv_isr_లెక్క++] = read_విలువ;
		write_uart_character(uart_instance[2], read_విలువ);
	}
	తిరిగి 0;
}
#అయితే_ముగింపు
