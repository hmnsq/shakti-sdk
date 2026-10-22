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

#ضمن "uart.h" //Includes the definitions of uart communication protocol//
#ضمن "string.h"
#ضمن "pinmux.h"
#ضمن "i2c.h"
#ضمن "log.h"
#ضمن "bmp280.h"

// Replace the API KEY
#تعریف_کن API_کلید "PPI6OVOI1A2LGXMZ"

// UART 1 to communicate to ESP8266
#تعریف_کن ESP_UART uart_instance[1]

// Using I2C 1 to connect to BMP280
#تعریف_کن I2C i2c_instance[1]

/**
  * @fn int write_to_esp8266(char *data,uart_num sel,int baudrate)
  * @brief sends data to esp8266 using UART
  * @param data data that has to be sent to could
  * @param sel Uart that is connected to esp8266
  * @param baudrate Baudrate that is used to communicate with esp8266
*/

صحيح write_مقصد_esp8266(حرف *داده_2)
{
	طالما (*داده_2 != '\0')
	{
		write_uart_character(ESP_UART, *داده_2);
		داده_2++;
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

صحيح write_enter_مقصد_esp8266()
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
صحيح read_from_esp8266(حرف *داده_2)
{
	صحيح ch;
	حرف *str = داده_2;
	حرف *test = داده_2;
	لكل (صحيح i = 0; i < 198; i++)
	{
		read_uart_character(ESP_UART, &ch);
		*str = ch;
		str++;
		*str = '\0';
		إذا (جستجوی_رشته(test, "OK") != عدم)
		{
			log_debug("read from esp8266 %s\n", test);
			أرجع;
		}
		إذا (جستجوی_رشته(test, "ERROR") != عدم)
		{
			log_debug("read from esp8266 %s\n", test);
			أرجع;
		}
		إذا (جستجوی_رشته(test, ">") != عدم)
		{
			log_debug("read from esp8266 %s\n", test);
			أرجع;
		}
		إذا (جستجوی_رشته(test, "RECV") != عدم)
		{
			log_debug("read from esp8266 %s\n", test);
			أرجع;
		}
		إذا (جستجوی_رشته(test, "IP") != عدم)
		{
			log_debug("read from esp8266 %s\n", test);
			أرجع;
		}
	}
	*str = '\0';
	أرجع 1;
}

/**
  * @fn void setup_esp8266()
  * @brief setup MUX mode in  esp8266
  * @details setup MUX mode in  esp8266
*/
فراغ راهاندازی_esp8266()
{
	حرف داده_2[200];
	write_مقصد_esp8266("AT");
	delay_loop(1000, 1000);
	read_from_esp8266(داده_2);

	چاپ_کن("sending AT Echo off command to esp\n");
	write_مقصد_esp8266("ATE0");
	delay_loop(50, 50);
	read_from_esp8266(داده_2);
	چاپ_کن("write AT+CIPMUX\n");
	write_مقصد_esp8266("AT+CIPMUX=0");
	delay_loop(50, 50);
	read_from_esp8266(داده_2);
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
فراغ transmit_داده(صحيح temperature, صحيح pressure)
{
	حرف داده_2[200];
	حرف send_داده_2[93];
	حرف CIPSEND[14];
	صحيح درازی_2;
	sprintf(send_داده_2, "GET https://api.thingspeak.com/update?api_key=%s&field1=%u.%u&field2=%u.%u", API_کلید, temperature / 100, temperature % 100, pressure / 1000, pressure % 1000);
	//sprintf(sendData,"GET https://api.thingspeak.com/update?api_key=%s&field1=%u.%u",API_KEY,temperature/100,temperature%100);
	درازی_2 = طول_رشته(send_داده_2);
	درازی_2 = درازی_2 + 2;
	sprintf(CIPSEND, "AT+CIPSEND=%d", درازی_2);
	// Connect to Wifi using esp8266

	// Connect to Wifi using esp8266
	چاپ_کن("\n Open connection to thingspeak.com\n");
	چاپ_کن("\n sending  %s\n", send_داده_2);
	flush_uart(ESP_UART);
	write_مقصد_esp8266("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80");
	read_from_esp8266(داده_2);
	چاپ_کن(" data from esp :%s\n",داده_2);

	//delay_loop(2000,2000);
	چاپ_کن("\n%s\n", CIPSEND);
	flush_uart(ESP_UART);
	write_مقصد_esp8266(CIPSEND);
	read_from_esp8266(داده_2);
	چاپ_کن(" data from esp :%s\n",داده_2);

	چاپ_کن(" write Data\n");
	flush_uart(ESP_UART);
	write_مقصد_esp8266(send_داده_2);

	//flush_uart(ESP_UART);
	write_enter_مقصد_esp8266();
	//delay(100,100);
	read_from_esp8266(داده_2);
	چاپ_کن(" data from esp :%s\n",داده_2);
	// disconnect from link
	چاپ_کن(" write AT+CIPCLOSE\n");
	flush_uart(ESP_UART);
	write_مقصد_esp8266("AT+CIPCLOSE");
	read_from_esp8266(داده_2);
}

/**
  * @fn void main()
  * @brief Entry point for the program
*/
فراغ اصلی()
{
	صحيح i = 0;
	صحيح baudrate = 115200;
	صحيح transmit_شمار = 0;
	حرف داده_2[200];
	بیعلامت صحيح موقت_Read_مقدار = 0;
	بیعلامت دراز delay = 1000;
	uint32_t pressure = 0, temperature = 0;

	چاپ_کن("\n setting PIN MUX config to 2 .... \n");
	*pinmux_config_reg = 0x5;
	چاپ_کن("\n set PIN MUX config to 2 .... \n");
	مجموعه_baud_نرخ(ESP_UART, baudrate);
	چاپ_کن("\n Sending temperature data to cloud server!....\n");
	چاپ_کن("\n Baud rate set to %d \n", baudrate);
	چاپ_کن("\n Waiting to ESP8266 to initialize \n");
	delay_loop(1000, 1000);
	راهاندازی_esp8266();
	راهاندازی_bmp280();

	طالما (1)
	{
		write_bmp280_ثبات(I2C, BMP280_CTRL_MEANS, BMP280_نرمال_نما, delay); // Set it to NORMAL MODE
		//log_info("write to bmp280\n   ");
		إذا (0 == read_bmp280_ثبات(I2C, BMP280_وضعیت_ثبات, &موقت_Read_مقدار, delay))
		{
			//log_info("read from bmp280");
			delay_loop(50, 50);
			إذا (!(موقت_Read_مقدار & 0x9))
			{
				//Read pressure and temperature values.
				read_bmp280_مقادیر(I2C, 0xF7, &pressure, &temperature, delay);
				چاپ_کن("\n temp is %u.%u Celcius", temperature / 100, temperature % 100);
				چاپ_کن("\n pressure is %u.%u kpa", pressure / 1000, pressure % 1000);
				transmit_داده(temperature, pressure);
			}
		}
		وإلا
		{
			//Display the error
			log_error("\nTemperature read failed.");
		}
		delay_loop(1000, 1000);
	}
}
