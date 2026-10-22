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

#अन्तर्भाव "uart.h" //Includes the definitions of uart communication protocol//
#अन्तर्भाव "string.h"
#अन्तर्भाव "pinmux.h"
#अन्तर्भाव "i2c.h"
#अन्तर्भाव "log.h"
#अन्तर्भाव "bmp280.h"

// Replace the API KEY
#परिभाषय API_कुञ्चिका "PPI6OVOI1A2LGXMZ"

// UART 1 to communicate to ESP8266
#परिभाषय ESP_UART uart_instance[1]

// Using I2C 1 to connect to BMP280
#परिभाषय I2C i2c_instance[1]

/**
  * @fn int write_to_esp8266(char *data,uart_num sel,int baudrate)
  * @brief sends data to esp8266 using UART
  * @param data data that has to be sent to could
  * @param sel Uart that is connected to esp8266
  * @param baudrate Baudrate that is used to communicate with esp8266
*/

पूर्णाङ्क write_गन्तव्यम्_esp8266(वर्ण *दत्त_2)
{
	यावत् (*दत्त_2 != '\0')
	{
		write_uart_character(ESP_UART, *दत्त_2);
		दत्त_2++;
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

पूर्णाङ्क write_enter_गन्तव्यम्_esp8266()
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
पूर्णाङ्क read_from_esp8266(वर्ण *दत्त_2)
{
	पूर्णाङ्क ch;
	वर्ण *str = दत्त_2;
	वर्ण *test = दत्त_2;
	प्रति (पूर्णाङ्क i = 0; i < 198; i++)
	{
		read_uart_character(ESP_UART, &ch);
		*str = ch;
		str++;
		*str = '\0';
		यदि (वाक्ये_अन्विष(test, "OK") != रिक्त)
		{
			log_debug("read from esp8266 %s\n", test);
			प्रत्यागम;
		}
		यदि (वाक्ये_अन्विष(test, "ERROR") != रिक्त)
		{
			log_debug("read from esp8266 %s\n", test);
			प्रत्यागम;
		}
		यदि (वाक्ये_अन्विष(test, ">") != रिक्त)
		{
			log_debug("read from esp8266 %s\n", test);
			प्रत्यागम;
		}
		यदि (वाक्ये_अन्विष(test, "RECV") != रिक्त)
		{
			log_debug("read from esp8266 %s\n", test);
			प्रत्यागम;
		}
		यदि (वाक्ये_अन्विष(test, "IP") != रिक्त)
		{
			log_debug("read from esp8266 %s\n", test);
			प्रत्यागम;
		}
	}
	*str = '\0';
	प्रत्यागम 1;
}

/**
  * @fn void setup_esp8266()
  * @brief setup MUX mode in  esp8266
  * @details setup MUX mode in  esp8266
*/
शून्य सज्जता_esp8266()
{
	वर्ण दत्त_2[200];
	write_गन्तव्यम्_esp8266("AT");
	delay_loop(1000, 1000);
	read_from_esp8266(दत्त_2);

	प्रारूप_लिख("sending AT Echo off command to esp\n");
	write_गन्तव्यम्_esp8266("ATE0");
	delay_loop(50, 50);
	read_from_esp8266(दत्त_2);
	प्रारूप_लिख("write AT+CIPMUX\n");
	write_गन्तव्यम्_esp8266("AT+CIPMUX=0");
	delay_loop(50, 50);
	read_from_esp8266(दत्त_2);
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
शून्य transmit_दत्त(पूर्णाङ्क temperature, पूर्णाङ्क pressure)
{
	वर्ण दत्त_2[200];
	वर्ण send_दत्त_2[93];
	वर्ण CIPSEND[14];
	पूर्णाङ्क दीर्घता_2;
	sprintf(send_दत्त_2, "GET https://api.thingspeak.com/update?api_key=%s&field1=%u.%u&field2=%u.%u", API_कुञ्चिका, temperature / 100, temperature % 100, pressure / 1000, pressure % 1000);
	//sprintf(sendData,"GET https://api.thingspeak.com/update?api_key=%s&field1=%u.%u",API_KEY,temperature/100,temperature%100);
	दीर्घता_2 = वाक्यदैर्घ्यम्(send_दत्त_2);
	दीर्घता_2 = दीर्घता_2 + 2;
	sprintf(CIPSEND, "AT+CIPSEND=%d", दीर्घता_2);
	// Connect to Wifi using esp8266

	// Connect to Wifi using esp8266
	प्रारूप_लिख("\n Open connection to thingspeak.com\n");
	प्रारूप_लिख("\n sending  %s\n", send_दत्त_2);
	flush_uart(ESP_UART);
	write_गन्तव्यम्_esp8266("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80");
	read_from_esp8266(दत्त_2);
	प्रारूप_लिख(" data from esp :%s\n",दत्त_2);

	//delay_loop(2000,2000);
	प्रारूप_लिख("\n%s\n", CIPSEND);
	flush_uart(ESP_UART);
	write_गन्तव्यम्_esp8266(CIPSEND);
	read_from_esp8266(दत्त_2);
	प्रारूप_लिख(" data from esp :%s\n",दत्त_2);

	प्रारूप_लिख(" write Data\n");
	flush_uart(ESP_UART);
	write_गन्तव्यम्_esp8266(send_दत्त_2);

	//flush_uart(ESP_UART);
	write_enter_गन्तव्यम्_esp8266();
	//delay(100,100);
	read_from_esp8266(दत्त_2);
	प्रारूप_लिख(" data from esp :%s\n",दत्त_2);
	// disconnect from link
	प्रारूप_लिख(" write AT+CIPCLOSE\n");
	flush_uart(ESP_UART);
	write_गन्तव्यम्_esp8266("AT+CIPCLOSE");
	read_from_esp8266(दत्त_2);
}

/**
  * @fn void main()
  * @brief Entry point for the program
*/
शून्य मुख्यम्()
{
	पूर्णाङ्क i = 0;
	पूर्णाङ्क baudrate = 115200;
	पूर्णाङ्क transmit_गणनम् = 0;
	वर्ण दत्त_2[200];
	अचिह्नित पूर्णाङ्क अस्थायी_Read_मानम् = 0;
	अचिह्नित दीर्घ delay = 1000;
	uint32_t pressure = 0, temperature = 0;

	प्रारूप_लिख("\n setting PIN MUX config to 2 .... \n");
	*pinmux_config_reg = 0x5;
	प्रारूप_लिख("\n set PIN MUX config to 2 .... \n");
	समुच्चयः_baud_दरः(ESP_UART, baudrate);
	प्रारूप_लिख("\n Sending temperature data to cloud server!....\n");
	प्रारूप_लिख("\n Baud rate set to %d \n", baudrate);
	प्रारूप_लिख("\n Waiting to ESP8266 to initialize \n");
	delay_loop(1000, 1000);
	सज्जता_esp8266();
	सज्जता_bmp280();

	यावत् (1)
	{
		write_bmp280_पञ्जिकाकोशः(I2C, BMP280_CTRL_MEANS, BMP280_प्रसामान्यम्_बहुलकम्, delay); // Set it to NORMAL MODE
		//log_info("write to bmp280\n   ");
		यदि (0 == read_bmp280_पञ्जिकाकोशः(I2C, BMP280_स्थितिः_पञ्जिकाकोशः, &अस्थायी_Read_मानम्, delay))
		{
			//log_info("read from bmp280");
			delay_loop(50, 50);
			यदि (!(अस्थायी_Read_मानम् & 0x9))
			{
				//Read pressure and temperature values.
				read_bmp280_मानानि(I2C, 0xF7, &pressure, &temperature, delay);
				प्रारूप_लिख("\n temp is %u.%u Celcius", temperature / 100, temperature % 100);
				प्रारूप_लिख("\n pressure is %u.%u kpa", pressure / 1000, pressure % 1000);
				transmit_दत्त(temperature, pressure);
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
