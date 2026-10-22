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

#अन्तर्भाव <string.h>
#अन्तर्भाव "uart.h"
#अन्तर्भाव "pinmux.h"
#अन्तर्भाव "i2c.h"
#अन्तर्भाव "log.h"

#परिभाषय LORA_UART uart_instance[1]
#परिभाषय BAUDRATE 9600
#परिभाषय दीर्घता_3 100


/** @fn int read_from_lora(char *data)
 * @brief Reads data sent by lora module.
 * @param data responses read from lora module, mainly used for logging
 */
पूर्णाङ्क read_from_lora(वर्ण *दत्त_2)
{
	पूर्णाङ्क ch;
	वर्ण *str = दत्त_2;
	वर्ण *test = दत्त_2;
	प्रति (पूर्णाङ्क i = 0; i < 98; i++)
	{
		read_uart_character(LORA_UART, &ch);
		*str = ch;
		str++;
		यदि (ch == '\n')
		{
			भङ्ग;
		}
	}
	प्रत्यागम;	
}


/** @fn int write_enter_to_lora()
 * @brief sends carriage return and new line charector to lora.
 * @details sends carriage return and new line charector to lora,
 *  		this method is neeed to indicate end to data transmission.
 */
पूर्णाङ्क write_enter_गन्तव्यम्_lora()
{
	write_uart_character(LORA_UART, '\r');
	write_uart_character(LORA_UART, '\n');
	प्रत्यागम 0;
}


/** @fn int write_to_lora(char *data) 
 * @brief sends data to Lora using UART.
 * @param data send data from one Lora to another Lora module.
 */
शून्य write_गन्तव्यम्_lora(वर्ण *दत्त_2)
{
	यावत् (*दत्त_2 != '\0')
	{
		write_uart_character(LORA_UART, *दत्त_2);
		दत्त_2++;
	}
	write_enter_गन्तव्यम्_lora();
}


/** @fn void receive_data()
 * @brief the data can be received to the LORA module
 * @details when another LORA module used to send data, it will receive the message.
 */
शून्य receive_दत्त()
{
	वर्ण दत्त_2[दीर्घता_3];

	स्मृतिं_पूरय(दत्त_2, 0, दीर्घता_3);
	flush_uart(LORA_UART);
	प्रारूप_लिख("\n Receiving DATA ...... ... .. .");
	read_from_lora(दत्त_2);
	प्रारूप_लिख("\n Data from LORA module: %s", दत्त_2);
}


/** @fn void check_set_lora_value()
 * @brief It helps to check the value set by the user, to the LORA module.
 * @details Through AT commands, the set values can be checked by these functions.
 */
शून्य check_समुच्चयः_lora_मानम्()
{
	वर्ण दत्त_2[दीर्घता_3];

	स्मृतिं_पूरय(दत्त_2, 0, दीर्घता_3);
	flush_uart(LORA_UART);
	प्रारूप_लिख("\n Finding the Mode set for LORA module");
	write_गन्तव्यम्_lora("AT+MODE?");
	read_from_lora(दत्त_2);
	प्रारूप_लिख("\n Data from LORA module: %s", दत्त_2);

	स्मृतिं_पूरय(दत्त_2, 0, दीर्घता_3);
	flush_uart(LORA_UART);
	प्रारूप_लिख("\n Finding the Address set to the LORA module");
	write_गन्तव्यम्_lora("AT+ADDRESS?");
	read_from_lora(दत्त_2);
	प्रारूप_लिख("\n Data from LORA module: %s", दत्त_2);

	स्मृतिं_पूरय(दत्त_2, 0, दीर्घता_3);
	flush_uart(LORA_UART);
	प्रारूप_लिख("\n Finding the BAND set for the LORA module");
	write_गन्तव्यम्_lora("AT+BAND?");
	read_from_lora(दत्त_2);
	प्रारूप_लिख("\n Data from LORA module: %s", दत्त_2);
}


/** @fn void setup_lora()
 * @brief all the necessary features can be set by thsese.
 * @details through AT commands the LORA module can be set and make it usable.
 */
शून्य सज्जता_lora()
{
	वर्ण दत्त_2[दीर्घता_3];

	// memset(data, 0, LENGTH);
	// flush_uart(LORA_UART);
	// printf("\n Writing AT+RESET");
	// write_to_lora("AT+RESET");
	// read_from_lora(data);
	// printf("\n Data from LORA module: %s", data);

	स्मृतिं_पूरय(दत्त_2, 0, दीर्घता_3);
	flush_uart(LORA_UART);
	प्रारूप_लिख("\n Writing AT");
	write_गन्तव्यम्_lora("AT");
	read_from_lora(दत्त_2);
	प्रारूप_लिख("\n Data from LORA module: %s", दत्त_2);

	स्मृतिं_पूरय(दत्त_2, 0, दीर्घता_3);
	flush_uart(LORA_UART);
	प्रारूप_लिख("\n Writing AT+MODE = 0");
	write_गन्तव्यम्_lora("AT+MODE=0");
	read_from_lora(दत्त_2);
	प्रारूप_लिख("\n Data from LORA module: %s", दत्त_2);

	स्मृतिं_पूरय(दत्त_2, 0, दीर्घता_3);
	flush_uart(LORA_UART);
	प्रारूप_लिख("\n Writing AT+ADDRESS = 0");
	write_गन्तव्यम्_lora("AT+ADDRESS=0");
	read_from_lora(दत्त_2);
	प्रारूप_लिख("\n Data from LORA module: %s", दत्त_2);

	स्मृतिं_पूरय(दत्त_2, 0, दीर्घता_3);
	flush_uart(LORA_UART);
	प्रारूप_लिख("\n Writing AT+BAND = 865000000");
	write_गन्तव्यम्_lora("AT+BAND=865000000");
	read_from_lora(दत्त_2);
	प्रारूप_लिख("\n Data from LORA module: %s", दत्त_2);
}


/** @fn void main()
 * @brief formats AT commands  to be setup, check and receive data to Lora module.
 * @details formats the data in AT commands and sends to Lora module in  sequence
 *          Setup the Lora module with the address, baud rate  
 *          Receive data 
 */
शून्य मुख्यम्()
{
	प्रारूप_लिख("\n Setting PIN MUX config to 2 ...... \n");
	*pinmux_config_reg = 0x5;

	प्रारूप_लिख("\n Setting the BAUDRATE to: %d .... \n", BAUDRATE);
	समुच्चयः_baud_दरः(LORA_UART, BAUDRATE);

	/* To setup the LORA Module */
	// setup_lora();

	/* If you want to check that value is set correctly or not */
	// check_set_lora_value();

	/* Receiving Data */
	यावत् (1) 
	{
		receive_दत्त();
		delay_loop(1000, 1000);
	}
	
}