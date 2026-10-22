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

#ಅನ್ತರ್ಭಾವ "uart.h" //Includes the definitions of uart communication protocol//
#ಅನ್ತರ್ಭಾವ "string.h"
#ಅನ್ತರ್ಭಾವ "pinmux.h"
#ಅನ್ತರ್ಭಾವ "i2c.h"
#ಅನ್ತರ್ಭಾವ "log.h"
#ಅನ್ತರ್ಭಾವ "bmp280.h"

// Replace the API KEY
#ವ್ಯಾಖ್ಯಾನಿಸು API_ಕೀಲಿ "PPI6OVOI1A2LGXMZ"

// UART 1 to communicate to ESP8266
#ವ್ಯಾಖ್ಯಾನಿಸು ESP_UART uart_instance[1]

// Using I2C 1 to connect to BMP280
#ವ್ಯಾಖ್ಯಾನಿಸು I2C i2c_instance[1]

/**
  * @fn int write_to_esp8266(char *data,uart_num sel,int baudrate)
  * @brief sends data to esp8266 using UART
  * @param data data that has to be sent to could
  * @param sel Uart that is connected to esp8266
  * @param baudrate Baudrate that is used to communicate with esp8266
*/

ಪೂರ್ಣಾಂಕ write_ಗಮ್ಯ_esp8266(ಅಕ್ಷರ *ದತ್ತಾಂಶ_2)
{
	ಆಗ (*ದತ್ತಾಂಶ_2 != '\0')
	{
		write_uart_character(ESP_UART, *ದತ್ತಾಂಶ_2);
		ದತ್ತಾಂಶ_2++;
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

ಪೂರ್ಣಾಂಕ write_enter_ಗಮ್ಯ_esp8266()
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
ಪೂರ್ಣಾಂಕ read_from_esp8266(ಅಕ್ಷರ *ದತ್ತಾಂಶ_2)
{
	ಪೂರ್ಣಾಂಕ ch;
	ಅಕ್ಷರ *str = ದತ್ತಾಂಶ_2;
	ಅಕ್ಷರ *test = ದತ್ತಾಂಶ_2;
	ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 198; i++)
	{
		read_uart_character(ESP_UART, &ch);
		*str = ch;
		str++;
		*str = '\0';
		ಆದರೆ (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(test, "OK") != ಖಾಲಿ)
		{
			log_debug("read from esp8266 %s\n", test);
			ಹಿಂತಿರುಗಿ;
		}
		ಆದರೆ (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(test, "ERROR") != ಖಾಲಿ)
		{
			log_debug("read from esp8266 %s\n", test);
			ಹಿಂತಿರುಗಿ;
		}
		ಆದರೆ (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(test, ">") != ಖಾಲಿ)
		{
			log_debug("read from esp8266 %s\n", test);
			ಹಿಂತಿರುಗಿ;
		}
		ಆದರೆ (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(test, "RECV") != ಖಾಲಿ)
		{
			log_debug("read from esp8266 %s\n", test);
			ಹಿಂತಿರುಗಿ;
		}
		ಆದರೆ (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(test, "IP") != ಖಾಲಿ)
		{
			log_debug("read from esp8266 %s\n", test);
			ಹಿಂತಿರುಗಿ;
		}
	}
	*str = '\0';
	ಹಿಂತಿರುಗಿ 1;
}

/**
  * @fn void setup_esp8266()
  * @brief setup MUX mode in  esp8266
  * @details setup MUX mode in  esp8266
*/
ಶೂನ್ಯ ಸಿದ್ಧತೆ_esp8266()
{
	ಅಕ್ಷರ ದತ್ತಾಂಶ_2[200];
	write_ಗಮ್ಯ_esp8266("AT");
	delay_loop(1000, 1000);
	read_from_esp8266(ದತ್ತಾಂಶ_2);

	ಬರೆ("sending AT Echo off command to esp\n");
	write_ಗಮ್ಯ_esp8266("ATE0");
	delay_loop(50, 50);
	read_from_esp8266(ದತ್ತಾಂಶ_2);
	ಬರೆ("write AT+CIPMUX\n");
	write_ಗಮ್ಯ_esp8266("AT+CIPMUX=0");
	delay_loop(50, 50);
	read_from_esp8266(ದತ್ತಾಂಶ_2);
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
ಶೂನ್ಯ transmit_ದತ್ತಾಂಶ(ಪೂರ್ಣಾಂಕ temperature, ಪೂರ್ಣಾಂಕ pressure)
{
	ಅಕ್ಷರ ದತ್ತಾಂಶ_2[200];
	ಅಕ್ಷರ send_ದತ್ತಾಂಶ_2[93];
	ಅಕ್ಷರ CIPSEND[14];
	ಪೂರ್ಣಾಂಕ ಉದ್ದಳತೆ_2;
	sprintf(send_ದತ್ತಾಂಶ_2, "GET https://api.thingspeak.com/update?api_key=%s&field1=%u.%u&field2=%u.%u", API_ಕೀಲಿ, temperature / 100, temperature % 100, pressure / 1000, pressure % 1000);
	//sprintf(sendData,"GET https://api.thingspeak.com/update?api_key=%s&field1=%u.%u",API_KEY,temperature/100,temperature%100);
	ಉದ್ದಳತೆ_2 = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(send_ದತ್ತಾಂಶ_2);
	ಉದ್ದಳತೆ_2 = ಉದ್ದಳತೆ_2 + 2;
	sprintf(CIPSEND, "AT+CIPSEND=%d", ಉದ್ದಳತೆ_2);
	// Connect to Wifi using esp8266

	// Connect to Wifi using esp8266
	ಬರೆ("\n Open connection to thingspeak.com\n");
	ಬರೆ("\n sending  %s\n", send_ದತ್ತಾಂಶ_2);
	flush_uart(ESP_UART);
	write_ಗಮ್ಯ_esp8266("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80");
	read_from_esp8266(ದತ್ತಾಂಶ_2);
	ಬರೆ(" data from esp :%s\n",ದತ್ತಾಂಶ_2);

	//delay_loop(2000,2000);
	ಬರೆ("\n%s\n", CIPSEND);
	flush_uart(ESP_UART);
	write_ಗಮ್ಯ_esp8266(CIPSEND);
	read_from_esp8266(ದತ್ತಾಂಶ_2);
	ಬರೆ(" data from esp :%s\n",ದತ್ತಾಂಶ_2);

	ಬರೆ(" write Data\n");
	flush_uart(ESP_UART);
	write_ಗಮ್ಯ_esp8266(send_ದತ್ತಾಂಶ_2);

	//flush_uart(ESP_UART);
	write_enter_ಗಮ್ಯ_esp8266();
	//delay(100,100);
	read_from_esp8266(ದತ್ತಾಂಶ_2);
	ಬರೆ(" data from esp :%s\n",ದತ್ತಾಂಶ_2);
	// disconnect from link
	ಬರೆ(" write AT+CIPCLOSE\n");
	flush_uart(ESP_UART);
	write_ಗಮ್ಯ_esp8266("AT+CIPCLOSE");
	read_from_esp8266(ದತ್ತಾಂಶ_2);
}

/**
  * @fn void main()
  * @brief Entry point for the program
*/
ಶೂನ್ಯ ಮುಖ್ಯ()
{
	ಪೂರ್ಣಾಂಕ i = 0;
	ಪೂರ್ಣಾಂಕ baudrate = 115200;
	ಪೂರ್ಣಾಂಕ transmit_ಎಣಿಕೆ = 0;
	ಅಕ್ಷರ ದತ್ತಾಂಶ_2[200];
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ತಾತ್ಕಾಲಿಕ_Read_ಮೌಲ್ಯ = 0;
	ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay = 1000;
	uint32_t pressure = 0, temperature = 0;

	ಬರೆ("\n setting PIN MUX config to 2 .... \n");
	*pinmux_config_reg = 0x5;
	ಬರೆ("\n set PIN MUX config to 2 .... \n");
	ಗಣ_baud_ದರ(ESP_UART, baudrate);
	ಬರೆ("\n Sending temperature data to cloud server!....\n");
	ಬರೆ("\n Baud rate set to %d \n", baudrate);
	ಬರೆ("\n Waiting to ESP8266 to initialize \n");
	delay_loop(1000, 1000);
	ಸಿದ್ಧತೆ_esp8266();
	ಸಿದ್ಧತೆ_bmp280();

	ಆಗ (1)
	{
		write_bmp280_ರಿಜಿಸ್ಟರ್(I2C, BMP280_CTRL_MEANS, BMP280_ಸಾಮಾನ್ಯ_ಬಹುಲಕ, delay); // Set it to NORMAL MODE
		//log_info("write to bmp280\n   ");
		ಆದರೆ (0 == read_bmp280_ರಿಜಿಸ್ಟರ್(I2C, BMP280_ಸ್ಥಿತಿ_ರಿಜಿಸ್ಟರ್, &ತಾತ್ಕಾಲಿಕ_Read_ಮೌಲ್ಯ, delay))
		{
			//log_info("read from bmp280");
			delay_loop(50, 50);
			ಆದರೆ (!(ತಾತ್ಕಾಲಿಕ_Read_ಮೌಲ್ಯ & 0x9))
			{
				//Read pressure and temperature values.
				read_bmp280_ಮೌಲ್ಯಗಳು(I2C, 0xF7, &pressure, &temperature, delay);
				ಬರೆ("\n temp is %u.%u Celcius", temperature / 100, temperature % 100);
				ಬರೆ("\n pressure is %u.%u kpa", pressure / 1000, pressure % 1000);
				transmit_ದತ್ತಾಂಶ(temperature, pressure);
			}
		}
		ಇಲ್ಲದಿದ್ದರೆ
		{
			//Display the error
			log_error("\nTemperature read failed.");
		}
		delay_loop(1000, 1000);
	}
}
