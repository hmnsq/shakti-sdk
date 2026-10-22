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

#شامل "uart.h" //Includes the definitions of uart communication protocol//
#شامل "string.h"
#شامل "pinmux.h"
#شامل "i2c.h"
#شامل "log.h"
#شامل "bmp280.h"

// Replace the API KEY
#تعریف_کرو API_کلید "PPI6OVOI1A2LGXMZ"

// UART 1 to communicate to ESP8266
#تعریف_کرو ESP_UART uart_instance[1]

// Using I2C 1 to connect to BMP280
#تعریف_کرو I2C i2c_instance[1]

/**
  * @fn int write_to_esp8266(char *data,uart_num sel,int baudrate)
  * @brief sends data to esp8266 using UART
  * @param data data that has to be sent to could
  * @param sel Uart that is connected to esp8266
  * @param baudrate Baudrate that is used to communicate with esp8266
*/

صحیح write_مقصد_esp8266(حرف *ڈیٹا_2)
{
	جب (*ڈیٹا_2 != '\0')
	{
		write_uart_character(ESP_UART, *ڈیٹا_2);
		ڈیٹا_2++;
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

صحیح write_enter_مقصد_esp8266()
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
صحیح read_from_esp8266(حرف *ڈیٹا_2)
{
	صحیح ch;
	حرف *str = ڈیٹا_2;
	حرف *test = ڈیٹا_2;
	برائے (صحیح i = 0; i < 198; i++)
	{
		read_uart_character(ESP_UART, &ch);
		*str = ch;
		str++;
		*str = '\0';
		اگر (لڑی_تلاش(test, "OK") != تہی)
		{
			log_debug("read from esp8266 %s\n", test);
			واپس;
		}
		اگر (لڑی_تلاش(test, "ERROR") != تہی)
		{
			log_debug("read from esp8266 %s\n", test);
			واپس;
		}
		اگر (لڑی_تلاش(test, ">") != تہی)
		{
			log_debug("read from esp8266 %s\n", test);
			واپس;
		}
		اگر (لڑی_تلاش(test, "RECV") != تہی)
		{
			log_debug("read from esp8266 %s\n", test);
			واپس;
		}
		اگر (لڑی_تلاش(test, "IP") != تہی)
		{
			log_debug("read from esp8266 %s\n", test);
			واپس;
		}
	}
	*str = '\0';
	واپس 1;
}

/**
  * @fn void setup_esp8266()
  * @brief setup MUX mode in  esp8266
  * @details setup MUX mode in  esp8266
*/
خالی تیاری_esp8266()
{
	حرف ڈیٹا_2[200];
	write_مقصد_esp8266("AT");
	delay_loop(1000, 1000);
	read_from_esp8266(ڈیٹا_2);

	لکھو("sending AT Echo off command to esp\n");
	write_مقصد_esp8266("ATE0");
	delay_loop(50, 50);
	read_from_esp8266(ڈیٹا_2);
	لکھو("write AT+CIPMUX\n");
	write_مقصد_esp8266("AT+CIPMUX=0");
	delay_loop(50, 50);
	read_from_esp8266(ڈیٹا_2);
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
خالی transmit_ڈیٹا(صحیح temperature, صحیح pressure)
{
	حرف ڈیٹا_2[200];
	حرف send_ڈیٹا_2[93];
	حرف CIPSEND[14];
	صحیح لمبائی_2;
	sprintf(send_ڈیٹا_2, "GET https://api.thingspeak.com/update?api_key=%s&field1=%u.%u&field2=%u.%u", API_کلید, temperature / 100, temperature % 100, pressure / 1000, pressure % 1000);
	//sprintf(sendData,"GET https://api.thingspeak.com/update?api_key=%s&field1=%u.%u",API_KEY,temperature/100,temperature%100);
	لمبائی_2 = لڑی_لمبائی(send_ڈیٹا_2);
	لمبائی_2 = لمبائی_2 + 2;
	sprintf(CIPSEND, "AT+CIPSEND=%d", لمبائی_2);
	// Connect to Wifi using esp8266

	// Connect to Wifi using esp8266
	لکھو("\n Open connection to thingspeak.com\n");
	لکھو("\n sending  %s\n", send_ڈیٹا_2);
	flush_uart(ESP_UART);
	write_مقصد_esp8266("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80");
	read_from_esp8266(ڈیٹا_2);
	لکھو(" data from esp :%s\n",ڈیٹا_2);

	//delay_loop(2000,2000);
	لکھو("\n%s\n", CIPSEND);
	flush_uart(ESP_UART);
	write_مقصد_esp8266(CIPSEND);
	read_from_esp8266(ڈیٹا_2);
	لکھو(" data from esp :%s\n",ڈیٹا_2);

	لکھو(" write Data\n");
	flush_uart(ESP_UART);
	write_مقصد_esp8266(send_ڈیٹا_2);

	//flush_uart(ESP_UART);
	write_enter_مقصد_esp8266();
	//delay(100,100);
	read_from_esp8266(ڈیٹا_2);
	لکھو(" data from esp :%s\n",ڈیٹا_2);
	// disconnect from link
	لکھو(" write AT+CIPCLOSE\n");
	flush_uart(ESP_UART);
	write_مقصد_esp8266("AT+CIPCLOSE");
	read_from_esp8266(ڈیٹا_2);
}

/**
  * @fn void main()
  * @brief Entry point for the program
*/
خالی مین()
{
	صحیح i = 0;
	صحیح baudrate = 115200;
	صحیح transmit_گنتی = 0;
	حرف ڈیٹا_2[200];
	غیرعلامتی صحیح عارضی_Read_قدر = 0;
	غیرعلامتی طویل delay = 1000;
	uint32_t pressure = 0, temperature = 0;

	لکھو("\n setting PIN MUX config to 2 .... \n");
	*pinmux_config_reg = 0x5;
	لکھو("\n set PIN MUX config to 2 .... \n");
	سیٹ_baud_شرح(ESP_UART, baudrate);
	لکھو("\n Sending temperature data to cloud server!....\n");
	لکھو("\n Baud rate set to %d \n", baudrate);
	لکھو("\n Waiting to ESP8266 to initialize \n");
	delay_loop(1000, 1000);
	تیاری_esp8266();
	تیاری_bmp280();

	جب (1)
	{
		write_bmp280_رجسٹر(I2C, BMP280_CTRL_MEANS, BMP280_معمول_منوال, delay); // Set it to NORMAL MODE
		//log_info("write to bmp280\n   ");
		اگر (0 == read_bmp280_رجسٹر(I2C, BMP280_حالت_رجسٹر, &عارضی_Read_قدر, delay))
		{
			//log_info("read from bmp280");
			delay_loop(50, 50);
			اگر (!(عارضی_Read_قدر & 0x9))
			{
				//Read pressure and temperature values.
				read_bmp280_اقدار(I2C, 0xF7, &pressure, &temperature, delay);
				لکھو("\n temp is %u.%u Celcius", temperature / 100, temperature % 100);
				لکھو("\n pressure is %u.%u kpa", pressure / 1000, pressure % 1000);
				transmit_ڈیٹا(temperature, pressure);
			}
		}
		ورنہ
		{
			//Display the error
			log_error("\nTemperature read failed.");
		}
		delay_loop(1000, 1000);
	}
}
