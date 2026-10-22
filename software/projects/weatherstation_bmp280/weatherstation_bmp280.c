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
#وصف_ڪريو API_ڪنجي "PPI6OVOI1A2LGXMZ"

// UART 1 to communicate to ESP8266
#وصف_ڪريو ESP_UART uart_instance[1]

// Using I2C 1 to connect to BMP280
#وصف_ڪريو I2C i2c_instance[1]

/**
  * @fn int write_to_esp8266(char *data,uart_num sel,int baudrate)
  * @brief sends data to esp8266 using UART
  * @param data data that has to be sent to could
  * @param sel Uart that is connected to esp8266
  * @param baudrate Baudrate that is used to communicate with esp8266
*/

صحيح write_منزل_esp8266(حرف *معلومات_2)
{
	طالما (*معلومات_2 != '\0')
	{
		write_uart_character(ESP_UART, *معلومات_2);
		معلومات_2++;
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

صحيح write_enter_منزل_esp8266()
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
صحيح read_from_esp8266(حرف *معلومات_2)
{
	صحيح ch;
	حرف *str = معلومات_2;
	حرف *test = معلومات_2;
	لكل (صحيح i = 0; i < 198; i++)
	{
		read_uart_character(ESP_UART, &ch);
		*str = ch;
		str++;
		*str = '\0';
		إذا (لڙي_ڳولا(test, "OK") != عدم)
		{
			log_debug("read from esp8266 %s\n", test);
			أرجع;
		}
		إذا (لڙي_ڳولا(test, "ERROR") != عدم)
		{
			log_debug("read from esp8266 %s\n", test);
			أرجع;
		}
		إذا (لڙي_ڳولا(test, ">") != عدم)
		{
			log_debug("read from esp8266 %s\n", test);
			أرجع;
		}
		إذا (لڙي_ڳولا(test, "RECV") != عدم)
		{
			log_debug("read from esp8266 %s\n", test);
			أرجع;
		}
		إذا (لڙي_ڳولا(test, "IP") != عدم)
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
فراغ تياري_esp8266()
{
	حرف معلومات_2[200];
	write_منزل_esp8266("AT");
	delay_loop(1000, 1000);
	read_from_esp8266(معلومات_2);

	لکو("sending AT Echo off command to esp\n");
	write_منزل_esp8266("ATE0");
	delay_loop(50, 50);
	read_from_esp8266(معلومات_2);
	لکو("write AT+CIPMUX\n");
	write_منزل_esp8266("AT+CIPMUX=0");
	delay_loop(50, 50);
	read_from_esp8266(معلومات_2);
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
فراغ transmit_معلومات(صحيح temperature, صحيح pressure)
{
	حرف معلومات_2[200];
	حرف send_معلومات_2[93];
	حرف CIPSEND[14];
	صحيح ڊيگهائي_2;
	sprintf(send_معلومات_2, "GET https://api.thingspeak.com/update?api_key=%s&field1=%u.%u&field2=%u.%u", API_ڪنجي, temperature / 100, temperature % 100, pressure / 1000, pressure % 1000);
	//sprintf(sendData,"GET https://api.thingspeak.com/update?api_key=%s&field1=%u.%u",API_KEY,temperature/100,temperature%100);
	ڊيگهائي_2 = لڙي_ڊيگهه(send_معلومات_2);
	ڊيگهائي_2 = ڊيگهائي_2 + 2;
	sprintf(CIPSEND, "AT+CIPSEND=%d", ڊيگهائي_2);
	// Connect to Wifi using esp8266

	// Connect to Wifi using esp8266
	لکو("\n Open connection to thingspeak.com\n");
	لکو("\n sending  %s\n", send_معلومات_2);
	flush_uart(ESP_UART);
	write_منزل_esp8266("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80");
	read_from_esp8266(معلومات_2);
	لکو(" data from esp :%s\n",معلومات_2);

	//delay_loop(2000,2000);
	لکو("\n%s\n", CIPSEND);
	flush_uart(ESP_UART);
	write_منزل_esp8266(CIPSEND);
	read_from_esp8266(معلومات_2);
	لکو(" data from esp :%s\n",معلومات_2);

	لکو(" write Data\n");
	flush_uart(ESP_UART);
	write_منزل_esp8266(send_معلومات_2);

	//flush_uart(ESP_UART);
	write_enter_منزل_esp8266();
	//delay(100,100);
	read_from_esp8266(معلومات_2);
	لکو(" data from esp :%s\n",معلومات_2);
	// disconnect from link
	لکو(" write AT+CIPCLOSE\n");
	flush_uart(ESP_UART);
	write_منزل_esp8266("AT+CIPCLOSE");
	read_from_esp8266(معلومات_2);
}

/**
  * @fn void main()
  * @brief Entry point for the program
*/
فراغ مکيه()
{
	صحيح i = 0;
	صحيح baudrate = 115200;
	صحيح transmit_ڳڻپ = 0;
	حرف معلومات_2[200];
	بنانشان صحيح عارضي_Read_قدر = 0;
	بنانشان ڊگهو delay = 1000;
	uint32_t pressure = 0, temperature = 0;

	لکو("\n setting PIN MUX config to 2 .... \n");
	*pinmux_config_reg = 0x5;
	لکو("\n set PIN MUX config to 2 .... \n");
	سيٽ_baud_شرح(ESP_UART, baudrate);
	لکو("\n Sending temperature data to cloud server!....\n");
	لکو("\n Baud rate set to %d \n", baudrate);
	لکو("\n Waiting to ESP8266 to initialize \n");
	delay_loop(1000, 1000);
	تياري_esp8266();
	تياري_bmp280();

	طالما (1)
	{
		write_bmp280_رجسٽر(I2C, BMP280_CTRL_MEANS, BMP280_عام_گهڻائي, delay); // Set it to NORMAL MODE
		//log_info("write to bmp280\n   ");
		إذا (0 == read_bmp280_رجسٽر(I2C, BMP280_حالت_رجسٽر, &عارضي_Read_قدر, delay))
		{
			//log_info("read from bmp280");
			delay_loop(50, 50);
			إذا (!(عارضي_Read_قدر & 0x9))
			{
				//Read pressure and temperature values.
				read_bmp280_قدرون(I2C, 0xF7, &pressure, &temperature, delay);
				لکو("\n temp is %u.%u Celcius", temperature / 100, temperature % 100);
				لکو("\n pressure is %u.%u kpa", pressure / 1000, pressure % 1000);
				transmit_معلومات(temperature, pressure);
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
