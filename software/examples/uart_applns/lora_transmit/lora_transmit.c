/***************************************************************************
* Project           			:  shakti devt board
* Name of the file	     		:  lora_transmit.c
* Brief Description of file     :  It used to send data wirelessly
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
  * @file lora_transmit.c
  * @brief sample program used to send word "HELLO" wirelessly
  * @details It used to send the required data wirelessly

  * * Prerequisite:-
  * 1. Lora module is configured to baud rate 9600
  * 2. Lora module is set to Active Mode
  * 3. Lora module set Baud Rate to 865000000 Hz
  * 4. Lora module set the address to 1
  * 5. Lora module send the data by specifing the length
*/

#समावेश <string.h>
#समावेश "uart.h"
#समावेश "pinmux.h"
#समावेश "i2c.h"
#समावेश "log.h"

#घोषणा LORA_UART uart_instance[1]
#घोषणा BAUDRATE 9600
#घोषणा लंबाई_3 100

/** @fn int read_from_lora(char *data)
 * @brief reads data sent by lora module using UART
 * @param data responses read from lora module is stored in it
 */
पूर्णांक read_from_lora(अक्षर *तथ्य_2)
{
	पूर्णांक ch;
	अक्षर *str = तथ्य_2;
	अक्षर *test = तथ्य_2;
	क्रम (पूर्णांक i = 0; i < 98; i++)
	{
		read_uart_character(LORA_UART, &ch);
		*str = ch;
		str++;
		अगर (ch == '\n')
		{
			अवरोध;
		}
	}
	वापस;	
}


/** @fn int write_enter_to_lora()
 * @brief sends carriage return and new line charector to lora.
 * @details sends carriage return and new line charector to lora,
 *  		this method is neeed to indicate end to data transmission.
 */
पूर्णांक write_enter_to_lora()
{
	write_uart_character(LORA_UART, '\r');
	write_uart_character(LORA_UART, '\n');
	वापस 0;
}


/** @fn int write_to_lora(char *data) 
 * @brief sends data to Lora using UART.
 * @param data send data from one Lora to another Lora module.
 */
व्योम write_to_lora(अक्षर *तथ्य_2)
{
	जबतक (*तथ्य_2 != '\0')
	{
		write_uart_character(LORA_UART, *तथ्य_2);
		तथ्य_2++;
	}
	write_enter_to_lora();
}


/** @fn void send_data()
 * @brief It helps to send the required data or message to another LORA module
 * @details Through AT commands the message can be send from one LORA to another LORA module.
 */
व्योम send_तथ्य()
{
	अक्षर तथ्य_2[लंबाई_3];

	स_रखो(तथ्य_2, 0, लंबाई_3);
	flush_uart(LORA_UART);
	म_लिखो("\n Sending DATA from");
	write_to_lora("AT+SEND=0,5,Hello");
	read_from_lora(तथ्य_2);
	म_लिखो("\n Data from LORA module: %s", तथ्य_2);
}



/** @fn void check_set_lora_value()
 * @brief It helps to check the value set by the user, to the LORA module.
 * @details Through AT commands, the set values can be checked by these functions.
 */
व्योम check_set_lora_मूल्य()
{
	अक्षर तथ्य_2[लंबाई_3];

	स_रखो(तथ्य_2, 0, लंबाई_3);
	flush_uart(LORA_UART);
	म_लिखो("\n Finding the Mode set for LORA module");
	write_to_lora("AT+MODE?");
	read_from_lora(तथ्य_2);
	म_लिखो("\n Data from LORA module: %s", तथ्य_2);

	स_रखो(तथ्य_2, 0, लंबाई_3);
	flush_uart(LORA_UART);
	म_लिखो("\n Finding the Address set to the LORA module");
	write_to_lora("AT+ADDRESS?");
	read_from_lora(तथ्य_2);
	म_लिखो("\n Data from LORA module: %s", तथ्य_2);

	स_रखो(तथ्य_2, 0, लंबाई_3);
	flush_uart(LORA_UART);
	म_लिखो("\n Finding the BAND set for the LORA module");
	write_to_lora("AT+BAND?");
	read_from_lora(तथ्य_2);
	म_लिखो("\n Data from LORA module: %s", तथ्य_2);
}


/** @fn void setup_lora()
 * @brief all the necessary features can be set by thsese.
 * @details through AT commands the LORA module can be set and make it usable.
 */
व्योम setup_lora()
{
	अक्षर तथ्य_2[लंबाई_3];

	स_रखो(तथ्य_2, 0, लंबाई_3);
	flush_uart(LORA_UART);
	म_लिखो("\n Writing AT");
	write_to_lora("AT");
	read_from_lora(तथ्य_2);
	म_लिखो("\n Data from LORA module: %s", तथ्य_2);

	स_रखो(तथ्य_2, 0, लंबाई_3);
	flush_uart(LORA_UART);
	म_लिखो("\n Writing AT+MODE = 0");
	write_to_lora("AT+MODE=0");
	read_from_lora(तथ्य_2);
	म_लिखो("\n Data from LORA module: %s", तथ्य_2);

	स_रखो(तथ्य_2, 0, लंबाई_3);
	flush_uart(LORA_UART);
	म_लिखो("\n Writing AT+ADDRESS = 1");
	write_to_lora("AT+ADDRESS=1");
	read_from_lora(तथ्य_2);
	म_लिखो("\n Data from LORA module: %s", तथ्य_2);

	स_रखो(तथ्य_2, 0, लंबाई_3);
	flush_uart(LORA_UART);
	म_लिखो("\n Writing AT+BAND = 865000000");
	write_to_lora("AT+BAND=865000000");
	read_from_lora(तथ्य_2);
	म_लिखो("\n Data from LORA module: %s", तथ्य_2);
}


/** @fn void main()
 * @brief formats AT commands  to be setup, check and transmit data to Lora module.
 * @details formats the data in AT commands and sends to Lora module in  sequence
 *          Setup the Lora module with the address, baud rate  
 *          Send data 
 */
व्योम मुख्य()
{
	म_लिखो("\n Setting PIN MUX config to 2 ...... \n");
	*pinmux_config_reg = 0x5;

	म_लिखो("\n Setting the BAUDRATE to: %d .... \n", BAUDRATE);
	set_baud_rate(LORA_UART, BAUDRATE);

	/* To Setup the LORA Module */
	setup_lora();

	/* If you want to check that value is set correctly or not.*/
	check_set_lora_मूल्य();
	
	send_तथ्य();
}