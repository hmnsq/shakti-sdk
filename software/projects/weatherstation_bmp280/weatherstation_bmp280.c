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

#অন্তর্ভাব "uart.h" //Includes the definitions of uart communication protocol//
#অন্তর্ভাব "string.h"
#অন্তর্ভাব "pinmux.h"
#অন্তর্ভাব "i2c.h"
#অন্তর্ভাব "log.h"
#অন্তর্ভাব "bmp280.h"

// Replace the API KEY
#define API_চাবি "PPI6OVOI1A2LGXMZ"

// UART 1 to communicate to ESP8266
#define ESP_UART uart_instance[1]

// Using I2C 1 to connect to BMP280
#define I2C i2c_instance[1]

/**
  * @fn int write_to_esp8266(char *data,uart_num sel,int baudrate)
  * @brief sends data to esp8266 using UART
  * @param data data that has to be sent to could
  * @param sel Uart that is connected to esp8266
  * @param baudrate Baudrate that is used to communicate with esp8266
*/

পূর্ণসংখ্যা write_to_esp8266(অক্ষর *তথ্য_2)
{
	যখন (*তথ্য_2 != '\0')
	{
		write_uart_character(ESP_UART, *তথ্য_2);
		তথ্য_2++;
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

পূর্ণসংখ্যা write_enter_to_esp8266()
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
পূর্ণসংখ্যা read_from_esp8266(অক্ষর *তথ্য_2)
{
	পূর্ণসংখ্যা ch;
	অক্ষর *str = তথ্য_2;
	অক্ষর *test = তথ্য_2;
	জন্য (পূর্ণসংখ্যা i = 0; i < 198; i++)
	{
		read_uart_character(ESP_UART, &ch);
		*str = ch;
		str++;
		*str = '\0';
		যদি (strstr(test, "OK") != ফাঁকা)
		{
			log_debug("read from esp8266 %s\n", test);
			ফেরত;
		}
		যদি (strstr(test, "ERROR") != ফাঁকা)
		{
			log_debug("read from esp8266 %s\n", test);
			ফেরত;
		}
		যদি (strstr(test, ">") != ফাঁকা)
		{
			log_debug("read from esp8266 %s\n", test);
			ফেরত;
		}
		যদি (strstr(test, "RECV") != ফাঁকা)
		{
			log_debug("read from esp8266 %s\n", test);
			ফেরত;
		}
		যদি (strstr(test, "IP") != ফাঁকা)
		{
			log_debug("read from esp8266 %s\n", test);
			ফেরত;
		}
	}
	*str = '\0';
	ফেরত 1;
}

/**
  * @fn void setup_esp8266()
  * @brief setup MUX mode in  esp8266
  * @details setup MUX mode in  esp8266
*/
শূন্য setup_esp8266()
{
	অক্ষর তথ্য_2[200];
	write_to_esp8266("AT");
	delay_loop(1000, 1000);
	read_from_esp8266(তথ্য_2);

	printf("sending AT Echo off command to esp\n");
	write_to_esp8266("ATE0");
	delay_loop(50, 50);
	read_from_esp8266(তথ্য_2);
	printf("write AT+CIPMUX\n");
	write_to_esp8266("AT+CIPMUX=0");
	delay_loop(50, 50);
	read_from_esp8266(তথ্য_2);
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
শূন্য transmit_তথ্য(পূর্ণসংখ্যা temperature, পূর্ণসংখ্যা pressure)
{
	অক্ষর তথ্য_2[200];
	অক্ষর send_তথ্য_2[93];
	অক্ষর CIPSEND[14];
	পূর্ণসংখ্যা দৈর্ঘ্য_2;
	sprintf(send_তথ্য_2, "GET https://api.thingspeak.com/update?api_key=%s&field1=%u.%u&field2=%u.%u", API_চাবি, temperature / 100, temperature % 100, pressure / 1000, pressure % 1000);
	//sprintf(sendData,"GET https://api.thingspeak.com/update?api_key=%s&field1=%u.%u",API_KEY,temperature/100,temperature%100);
	দৈর্ঘ্য_2 = strlen(send_তথ্য_2);
	দৈর্ঘ্য_2 = দৈর্ঘ্য_2 + 2;
	sprintf(CIPSEND, "AT+CIPSEND=%d", দৈর্ঘ্য_2);
	// Connect to Wifi using esp8266

	// Connect to Wifi using esp8266
	printf("\n Open connection to thingspeak.com\n");
	printf("\n sending  %s\n", send_তথ্য_2);
	flush_uart(ESP_UART);
	write_to_esp8266("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80");
	read_from_esp8266(তথ্য_2);
	printf(" data from esp :%s\n",তথ্য_2);

	//delay_loop(2000,2000);
	printf("\n%s\n", CIPSEND);
	flush_uart(ESP_UART);
	write_to_esp8266(CIPSEND);
	read_from_esp8266(তথ্য_2);
	printf(" data from esp :%s\n",তথ্য_2);

	printf(" write Data\n");
	flush_uart(ESP_UART);
	write_to_esp8266(send_তথ্য_2);

	//flush_uart(ESP_UART);
	write_enter_to_esp8266();
	//delay(100,100);
	read_from_esp8266(তথ্য_2);
	printf(" data from esp :%s\n",তথ্য_2);
	// disconnect from link
	printf(" write AT+CIPCLOSE\n");
	flush_uart(ESP_UART);
	write_to_esp8266("AT+CIPCLOSE");
	read_from_esp8266(তথ্য_2);
}

/**
  * @fn void main()
  * @brief Entry point for the program
*/
শূন্য প্রধান()
{
	পূর্ণসংখ্যা i = 0;
	পূর্ণসংখ্যা baudrate = 115200;
	পূর্ণসংখ্যা transmit_গুনতি = 0;
	অক্ষর তথ্য_2[200];
	unsigned পূর্ণসংখ্যা অস্থায়ী_Read_মান = 0;
	unsigned long delay = 1000;
	uint32_t pressure = 0, temperature = 0;

	printf("\n setting PIN MUX config to 2 .... \n");
	*pinmux_config_reg = 0x5;
	printf("\n set PIN MUX config to 2 .... \n");
	set_baud_rate(ESP_UART, baudrate);
	printf("\n Sending temperature data to cloud server!....\n");
	printf("\n Baud rate set to %d \n", baudrate);
	printf("\n Waiting to ESP8266 to initialize \n");
	delay_loop(1000, 1000);
	setup_esp8266();
	setup_bmp280();

	যখন (1)
	{
		write_bmp280_register(I2C, BMP280_CTRL_MEANS, BMP280_NORMAL_MODE, delay); // Set it to NORMAL MODE
		//log_info("write to bmp280\n   ");
		যদি (0 == read_bmp280_register(I2C, BMP280_STATUS_REGISTER, &অস্থায়ী_Read_মান, delay))
		{
			//log_info("read from bmp280");
			delay_loop(50, 50);
			যদি (!(অস্থায়ী_Read_মান & 0x9))
			{
				//Read pressure and temperature values.
				read_bmp280_মানসমূহ(I2C, 0xF7, &pressure, &temperature, delay);
				printf("\n temp is %u.%u Celcius", temperature / 100, temperature % 100);
				printf("\n pressure is %u.%u kpa", pressure / 1000, pressure % 1000);
				transmit_তথ্য(temperature, pressure);
			}
		}
		অন্যথা
		{
			//Display the error
			log_error("\nTemperature read failed.");
		}
		delay_loop(1000, 1000);
	}
}
