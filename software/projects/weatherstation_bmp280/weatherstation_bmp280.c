/***************************************************************************
* Project           			:  shakti devt board
* Name of the file	     		:  weatherstation.c
* Brief Description of file     :  A sample project to demonstrate 
					   integration of temperature sensor 
                                           and transmission of data to a website
* Name of Author    	        :  Anand Kumar S
* Email ID                      :  007334@imail.iitm.ac.in

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
/**
  * @file weatherstation.c
  * @brief sample project using temperature sensor and esp8266
  * @details Sample project to demonstrate integration of temperature sensor and
  * transmission of data to a website.
  * LM75 sensor is used to collect ambient temperature, ESP8266 module is  used to
  * send data to thingspeak.com
  * Prerequisite:

  * 1. ESP8266 is configured to baud rate 115200
  * 2. ESP8266 is set in station mode
  * 3. ESP8266 is configured to connect to access point.
  * 4. A channel to receive data is configured in thingspeak.com
  * 5. Change the API_key in the weatherstation.c

*/

#समावेश "uart.h" //Includes the definitions of uart communication protocol//
#समावेश "string.h"
#समावेश "pinmux.h"
#समावेश "i2c.h"
#समावेश "log.h"
#समावेश "bmp280.h"

// Replace the API KEY
#घोषणा API_कुंजी "PPI6OVOI1A2LGXMZ"

// UART 1 to communicate to ESP8266
#घोषणा ESP_UART uart_instance[1]

// Using I2C 1 to connect to BMP280
#घोषणा I2C i2c_instance[1]

/**
  * @fn int write_to_esp8266(char *data,uart_num sel,int baudrate)
  * @brief sends data to esp8266 using UART
  * @param data data that has to be sent to could
  * @param sel Uart that is connected to esp8266
  * @param baudrate Baudrate that is used to communicate with esp8266
*/

पूर्णांक write_to_esp8266(अक्षर *तथ्य_2)
{
	जबतक (*तथ्य_2 != '\0')
	{
		write_uart_character(ESP_UART, *तथ्य_2);
		तथ्य_2++;
	}
	write_uart_character(ESP_UART, '\r');
	write_uart_character(ESP_UART, '\n');
}

/**
  * @fn int write_to_esp8266(char *data,uart_num sel,int baudrate)
  * @brief sends carriage return and new line charector to esp8266
  * @detail sends carriage return and new line charector to esp8266
  *         this method is neeed to indicate end to data transmission
  * @param data data that has to be sent to could
  * @param sel Uart that is connected to esp8266
  * @param baudrate Baudrate that is used to communicate with esp8266
*/

पूर्णांक write_enter_to_esp8266()
{
	write_uart_character(ESP_UART, '\r');
	write_uart_character(ESP_UART, '\n');
}

/**
  * @fn int read_from_esp8266(char *data,uart_num sel,int baudrate)
  * @brief Reads data sent by esp8266
  * @details Reads data sent by esp8266 until one of the key word is found
  * @param data responses read from esp8266, mainly used for logging
  * @param sel Uart that is connected to esp8266
  * @param baudrate Baudrate that is used to communicate with esp8266
*/
पूर्णांक read_from_esp8266(अक्षर *तथ्य_2)
{
	पूर्णांक ch;
	अक्षर *str = तथ्य_2;
	अक्षर *test = तथ्य_2;
	क्रम (पूर्णांक i = 0; i < 198; i++)
	{
		read_uart_character(ESP_UART, &ch);
		*str = ch;
		str++;
		*str = '\0';
		अगर (म_माला(test, "OK") != शून्य)
		{
			log_debug("read from esp8266 %s\n", test);
			वापस;
		}
		अगर (म_माला(test, "ERROR") != शून्य)
		{
			log_debug("read from esp8266 %s\n", test);
			वापस;
		}
		अगर (म_माला(test, ">") != शून्य)
		{
			log_debug("read from esp8266 %s\n", test);
			वापस;
		}
		अगर (म_माला(test, "RECV") != शून्य)
		{
			log_debug("read from esp8266 %s\n", test);
			वापस;
		}
		अगर (म_माला(test, "IP") != शून्य)
		{
			log_debug("read from esp8266 %s\n", test);
			वापस;
		}
	}
	*str = '\0';
	वापस 1;
}

/**
  * @fn void setup_esp8266()
  * @brief setup MUX mode in  esp8266
  * @details setup MUX mode in  esp8266
*/
व्योम setup_esp8266()
{
	अक्षर तथ्य_2[200];
	write_to_esp8266("AT");
	delay_loop(1000, 1000);
	read_from_esp8266(तथ्य_2);

	म_लिखो("sending AT Echo off command to esp\n");
	write_to_esp8266("ATE0");
	delay_loop(50, 50);
	read_from_esp8266(तथ्य_2);
	म_लिखो("write AT+CIPMUX\n");
	write_to_esp8266("AT+CIPMUX=0");
	delay_loop(50, 50);
	read_from_esp8266(तथ्य_2);
}
/**
  * @fn void transmit_data(int temperature, int baudrate)
  * @brief formats AT commands  to be sent to esp8266
  * @details formats the data in AT commands and sends to esp8266 in  sequence
  *      Open connection to server (thingspeak.com in this example)
  *      Send data to the server 
  *      Close connection
  * @param temperature temperate that has to be sent to database in cloud
  * @param baudrate baudrate used to communicate with esp8266
*/
व्योम transmit_तथ्य(पूर्णांक temperature, पूर्णांक pressure)
{
	अक्षर तथ्य_2[200];
	अक्षर send_तथ्य_2[93];
	अक्षर CIPSEND[14];
	पूर्णांक लंबाई_2;
	प्र_लिखो(send_तथ्य_2, "GET https://api.thingspeak.com/update?api_key=%s&field1=%u.%u&field2=%u.%u", API_कुंजी, temperature / 100, temperature % 100, pressure / 1000, pressure % 1000);
	//sprintf(sendData,"GET https://api.thingspeak.com/update?api_key=%s&field1=%u.%u",API_KEY,temperature/100,temperature%100);
	लंबाई_2 = म_माप(send_तथ्य_2);
	लंबाई_2 = लंबाई_2 + 2;
	प्र_लिखो(CIPSEND, "AT+CIPSEND=%d", लंबाई_2);
	// Connect to Wifi using esp8266

	// Connect to Wifi using esp8266
	म_लिखो("\n Open connection to thingspeak.com\n");
	म_लिखो("\n sending  %s\n", send_तथ्य_2);
	flush_uart(ESP_UART);
	write_to_esp8266("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80");
	read_from_esp8266(तथ्य_2);
	म_लिखो(" data from esp :%s\n",तथ्य_2);

	//delay_loop(2000,2000);
	म_लिखो("\n%s\n", CIPSEND);
	flush_uart(ESP_UART);
	write_to_esp8266(CIPSEND);
	read_from_esp8266(तथ्य_2);
	म_लिखो(" data from esp :%s\n",तथ्य_2);

	म_लिखो(" write Data\n");
	flush_uart(ESP_UART);
	write_to_esp8266(send_तथ्य_2);

	//flush_uart(ESP_UART);
	write_enter_to_esp8266();
	//delay(100,100);
	read_from_esp8266(तथ्य_2);
	म_लिखो(" data from esp :%s\n",तथ्य_2);
	// disconnect from link
	म_लिखो(" write AT+CIPCLOSE\n");
	flush_uart(ESP_UART);
	write_to_esp8266("AT+CIPCLOSE");
	read_from_esp8266(तथ्य_2);
}

/**
  * @fn void main()
  * @brief Entry point for the program
*/
व्योम मुख्य()
{
	पूर्णांक i = 0;
	पूर्णांक baudrate = 115200;
	पूर्णांक transmit_गिनती = 0;
	अक्षर तथ्य_2[200];
	अचिन्हित पूर्णांक अस्थायी_Read_मूल्य = 0;
	अचिन्हित दीर्घ delay = 1000;
	uint32_t pressure = 0, temperature = 0;

	म_लिखो("\n setting PIN MUX config to 2 .... \n");
	*pinmux_config_reg = 0x5;
	म_लिखो("\n set PIN MUX config to 2 .... \n");
	set_baud_rate(ESP_UART, baudrate);
	म_लिखो("\n Sending temperature data to cloud server!....\n");
	म_लिखो("\n Baud rate set to %d \n", baudrate);
	म_लिखो("\n Waiting to ESP8266 to initialize \n");
	delay_loop(1000, 1000);
	setup_esp8266();
	setup_bmp280();

	जबतक (1)
	{
		write_bmp280_register(I2C, BMP280_CTRL_MEANS, BMP280_NORMAL_MODE, delay); // Set it to NORMAL MODE
		//log_info("write to bmp280\n   ");
		अगर (0 == read_bmp280_register(I2C, BMP280_STATUS_REGISTER, &अस्थायी_Read_मूल्य, delay))
		{
			//log_info("read from bmp280");
			delay_loop(50, 50);
			अगर (!(अस्थायी_Read_मूल्य & 0x9))
			{
				//Read pressure and temperature values.
				read_bmp280_मूल्यावली(I2C, 0xF7, &pressure, &temperature, delay);
				म_लिखो("\n temp is %u.%u Celcius", temperature / 100, temperature % 100);
				म_लिखो("\n pressure is %u.%u kpa", pressure / 1000, pressure % 1000);
				transmit_तथ्य(temperature, pressure);
			}
		}
		अन्यथा
		{
			//Display the error
			log_error("\nTemperature read failed.");
		}
		delay_loop(1000, 1000);
	}
}
