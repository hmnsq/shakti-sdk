/***************************************************************************
* Project           			:  shakti devt board
* Name of the file	     		:  lora_receive.c
* Brief Description of file     :  It used to receive data wirelessly
* Name of Author    	        :  Soutrick Roy Chowdhury
* Email ID                      :  soutrickofficial@gmail.com

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

***************************************************************************/
/*
  * @file lora_receive.c
  * @brief sample program used to recive the word "HELLO" wirelessly
  * @details It used to recive the required data wirelessly

  * * Prerequisite:-	
  * 1. Lora module is configured to baud rate 9600
  * 2. Lora module is set to Active Mode
  * 3. Lora module set Baud Rate to 865000000 Hz
  * 4. Lora module set the address to 0
  * 5. Lora module receive the data 
*/

#ضمن <string.h>
#ضمن "uart.h"
#ضمن "pinmux.h"
#ضمن "i2c.h"
#ضمن "log.h"

#تعریف_کرو LORA_UART uart_instance[1]
#تعریف_کرو BAUDRATE 9600
#تعریف_کرو لمائی_3 100


/** @fn int read_from_lora(char *data)
 * @brief Reads data sent by lora module.
 * @param data responses read from lora module, mainly used for logging
 */
صحيح read_from_lora(حرف *انکڑے_2)
{
	صحيح ch;
	حرف *str = انکڑے_2;
	حرف *test = انکڑے_2;
	لكل (صحيح i = 0; i < 98; i++)
	{
		read_uart_character(LORA_UART, &ch);
		*str = ch;
		str++;
		إذا (ch == '\n')
		{
			اكسر;
		}
	}
	أرجع;	
}


/** @fn int write_enter_to_lora()
 * @brief sends carriage return and new line charector to lora.
 * @details sends carriage return and new line charector to lora,
 *  		this method is neeed to indicate end to data transmission.
 */
صحيح write_enter_منزل_lora()
{
	write_uart_character(LORA_UART, '\r');
	write_uart_character(LORA_UART, '\n');
	أرجع 0;
}


/** @fn int write_to_lora(char *data) 
 * @brief sends data to Lora using UART.
 * @param data send data from one Lora to another Lora module.
 */
فراغ write_منزل_lora(حرف *انکڑے_2)
{
	طالما (*انکڑے_2 != '\0')
	{
		write_uart_character(LORA_UART, *انکڑے_2);
		انکڑے_2++;
	}
	write_enter_منزل_lora();
}


/** @fn void receive_data()
 * @brief the data can be received to the LORA module
 * @details when another LORA module used to send data, it will receive the message.
 */
فراغ receive_انکڑے()
{
	حرف انکڑے_2[لمائی_3];

	memset(انکڑے_2, 0, لمائی_3);
	flush_uart(LORA_UART);
	لکھو("\n Receiving DATA ...... ... .. .");
	read_from_lora(انکڑے_2);
	لکھو("\n Data from LORA module: %s", انکڑے_2);
}


/** @fn void check_set_lora_value()
 * @brief It helps to check the value set by the user, to the LORA module.
 * @details Through AT commands, the set values can be checked by these functions.
 */
فراغ check_سیٹ_lora_قدر()
{
	حرف انکڑے_2[لمائی_3];

	memset(انکڑے_2, 0, لمائی_3);
	flush_uart(LORA_UART);
	لکھو("\n Finding the Mode set for LORA module");
	write_منزل_lora("AT+MODE?");
	read_from_lora(انکڑے_2);
	لکھو("\n Data from LORA module: %s", انکڑے_2);

	memset(انکڑے_2, 0, لمائی_3);
	flush_uart(LORA_UART);
	لکھو("\n Finding the Address set to the LORA module");
	write_منزل_lora("AT+ADDRESS?");
	read_from_lora(انکڑے_2);
	لکھو("\n Data from LORA module: %s", انکڑے_2);

	memset(انکڑے_2, 0, لمائی_3);
	flush_uart(LORA_UART);
	لکھو("\n Finding the BAND set for the LORA module");
	write_منزل_lora("AT+BAND?");
	read_from_lora(انکڑے_2);
	لکھو("\n Data from LORA module: %s", انکڑے_2);
}


/** @fn void setup_lora()
 * @brief all the necessary features can be set by thsese.
 * @details through AT commands the LORA module can be set and make it usable.
 */
فراغ تیاری_lora()
{
	حرف انکڑے_2[لمائی_3];

	// memset(data, 0, LENGTH);
	// flush_uart(LORA_UART);
	// printf("\n Writing AT+RESET");
	// write_to_lora("AT+RESET");
	// read_from_lora(data);
	// printf("\n Data from LORA module: %s", data);

	memset(انکڑے_2, 0, لمائی_3);
	flush_uart(LORA_UART);
	لکھو("\n Writing AT");
	write_منزل_lora("AT");
	read_from_lora(انکڑے_2);
	لکھو("\n Data from LORA module: %s", انکڑے_2);

	memset(انکڑے_2, 0, لمائی_3);
	flush_uart(LORA_UART);
	لکھو("\n Writing AT+MODE = 0");
	write_منزل_lora("AT+MODE=0");
	read_from_lora(انکڑے_2);
	لکھو("\n Data from LORA module: %s", انکڑے_2);

	memset(انکڑے_2, 0, لمائی_3);
	flush_uart(LORA_UART);
	لکھو("\n Writing AT+ADDRESS = 0");
	write_منزل_lora("AT+ADDRESS=0");
	read_from_lora(انکڑے_2);
	لکھو("\n Data from LORA module: %s", انکڑے_2);

	memset(انکڑے_2, 0, لمائی_3);
	flush_uart(LORA_UART);
	لکھو("\n Writing AT+BAND = 865000000");
	write_منزل_lora("AT+BAND=865000000");
	read_from_lora(انکڑے_2);
	لکھو("\n Data from LORA module: %s", انکڑے_2);
}


/** @fn void main()
 * @brief formats AT commands  to be setup, check and receive data to Lora module.
 * @details formats the data in AT commands and sends to Lora module in  sequence
 *          Setup the Lora module with the address, baud rate  
 *          Receive data 
 */
فراغ مکھ()
{
	لکھو("\n Setting PIN MUX config to 2 ...... \n");
	*pinmux_config_reg = 0x5;

	لکھو("\n Setting the BAUDRATE to: %d .... \n", BAUDRATE);
	سیٹ_baud_شرح(LORA_UART, BAUDRATE);

	/* To setup the LORA Module */
	تیاری_lora();

	/* If you want to check that value is set correctly or not */
	check_سیٹ_lora_قدر();

	receive_انکڑے();
}