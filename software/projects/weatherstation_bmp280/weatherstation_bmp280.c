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

#అన్తర్భావ "uart.h" //Includes the definitions of uart communication protocol//
#అన్తర్భావ "string.h"
#అన్తర్భావ "pinmux.h"
#అన్తర్భావ "i2c.h"
#అన్తర్భావ "log.h"
#అన్తర్భావ "bmp280.h"

// Replace the API KEY
#నిర్వచించు API_కీలకం "PPI6OVOI1A2LGXMZ"

// UART 1 to communicate to ESP8266
#నిర్వచించు ESP_UART uart_instance[1]

// Using I2C 1 to connect to BMP280
#నిర్వచించు I2C i2c_instance[1]

/**
  * @fn int write_to_esp8266(char *data,uart_num sel,int baudrate)
  * @brief sends data to esp8266 using UART
  * @param data data that has to be sent to could
  * @param sel Uart that is connected to esp8266
  * @param baudrate Baudrate that is used to communicate with esp8266
*/

పూర్ణాంకం write_గమ్యం_esp8266(అక్షరం *దత్తాంశం_2)
{
	అయితే (*దత్తాంశం_2 != '\0')
	{
		write_uart_character(ESP_UART, *దత్తాంశం_2);
		దత్తాంశం_2++;
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

పూర్ణాంకం write_enter_గమ్యం_esp8266()
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
పూర్ణాంకం read_from_esp8266(అక్షరం *దత్తాంశం_2)
{
	పూర్ణాంకం ch;
	అక్షరం *str = దత్తాంశం_2;
	అక్షరం *test = దత్తాంశం_2;
	కొరకు (పూర్ణాంకం i = 0; i < 198; i++)
	{
		read_uart_character(ESP_UART, &ch);
		*str = ch;
		str++;
		*str = '\0';
		ఒకవేళ (అక్షరశ్రేణి_శోధన(test, "OK") != ఖాళీ)
		{
			log_debug("read from esp8266 %s\n", test);
			తిరిగి;
		}
		ఒకవేళ (అక్షరశ్రేణి_శోధన(test, "ERROR") != ఖాళీ)
		{
			log_debug("read from esp8266 %s\n", test);
			తిరిగి;
		}
		ఒకవేళ (అక్షరశ్రేణి_శోధన(test, ">") != ఖాళీ)
		{
			log_debug("read from esp8266 %s\n", test);
			తిరిగి;
		}
		ఒకవేళ (అక్షరశ్రేణి_శోధన(test, "RECV") != ఖాళీ)
		{
			log_debug("read from esp8266 %s\n", test);
			తిరిగి;
		}
		ఒకవేళ (అక్షరశ్రేణి_శోధన(test, "IP") != ఖాళీ)
		{
			log_debug("read from esp8266 %s\n", test);
			తిరిగి;
		}
	}
	*str = '\0';
	తిరిగి 1;
}

/**
  * @fn void setup_esp8266()
  * @brief setup MUX mode in  esp8266
  * @details setup MUX mode in  esp8266
*/
శూన్య అమరిక_esp8266()
{
	అక్షరం దత్తాంశం_2[200];
	write_గమ్యం_esp8266("AT");
	delay_loop(1000, 1000);
	read_from_esp8266(దత్తాంశం_2);

	రాయి("sending AT Echo off command to esp\n");
	write_గమ్యం_esp8266("ATE0");
	delay_loop(50, 50);
	read_from_esp8266(దత్తాంశం_2);
	రాయి("write AT+CIPMUX\n");
	write_గమ్యం_esp8266("AT+CIPMUX=0");
	delay_loop(50, 50);
	read_from_esp8266(దత్తాంశం_2);
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
శూన్య transmit_దత్తాంశం(పూర్ణాంకం temperature, పూర్ణాంకం pressure)
{
	అక్షరం దత్తాంశం_2[200];
	అక్షరం send_దత్తాంశం_2[93];
	అక్షరం CIPSEND[14];
	పూర్ణాంకం నిడివి_2;
	sprintf(send_దత్తాంశం_2, "GET https://api.thingspeak.com/update?api_key=%s&field1=%u.%u&field2=%u.%u", API_కీలకం, temperature / 100, temperature % 100, pressure / 1000, pressure % 1000);
	//sprintf(sendData,"GET https://api.thingspeak.com/update?api_key=%s&field1=%u.%u",API_KEY,temperature/100,temperature%100);
	నిడివి_2 = అక్షరశ్రేణి_పొడవు(send_దత్తాంశం_2);
	నిడివి_2 = నిడివి_2 + 2;
	sprintf(CIPSEND, "AT+CIPSEND=%d", నిడివి_2);
	// Connect to Wifi using esp8266

	// Connect to Wifi using esp8266
	రాయి("\n Open connection to thingspeak.com\n");
	రాయి("\n sending  %s\n", send_దత్తాంశం_2);
	flush_uart(ESP_UART);
	write_గమ్యం_esp8266("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80");
	read_from_esp8266(దత్తాంశం_2);
	రాయి(" data from esp :%s\n",దత్తాంశం_2);

	//delay_loop(2000,2000);
	రాయి("\n%s\n", CIPSEND);
	flush_uart(ESP_UART);
	write_గమ్యం_esp8266(CIPSEND);
	read_from_esp8266(దత్తాంశం_2);
	రాయి(" data from esp :%s\n",దత్తాంశం_2);

	రాయి(" write Data\n");
	flush_uart(ESP_UART);
	write_గమ్యం_esp8266(send_దత్తాంశం_2);

	//flush_uart(ESP_UART);
	write_enter_గమ్యం_esp8266();
	//delay(100,100);
	read_from_esp8266(దత్తాంశం_2);
	రాయి(" data from esp :%s\n",దత్తాంశం_2);
	// disconnect from link
	రాయి(" write AT+CIPCLOSE\n");
	flush_uart(ESP_UART);
	write_గమ్యం_esp8266("AT+CIPCLOSE");
	read_from_esp8266(దత్తాంశం_2);
}

/**
  * @fn void main()
  * @brief Entry point for the program
*/
శూన్య ప్రధాన()
{
	పూర్ణాంకం i = 0;
	పూర్ణాంకం baudrate = 115200;
	పూర్ణాంకం transmit_లెక్క = 0;
	అక్షరం దత్తాంశం_2[200];
	గుర్తులేని పూర్ణాంకం తాత్కాలిక_Read_విలువ = 0;
	గుర్తులేని దీర్ఘ delay = 1000;
	uint32_t pressure = 0, temperature = 0;

	రాయి("\n setting PIN MUX config to 2 .... \n");
	*pinmux_config_reg = 0x5;
	రాయి("\n set PIN MUX config to 2 .... \n");
	సమితి_baud_రేటు(ESP_UART, baudrate);
	రాయి("\n Sending temperature data to cloud server!....\n");
	రాయి("\n Baud rate set to %d \n", baudrate);
	రాయి("\n Waiting to ESP8266 to initialize \n");
	delay_loop(1000, 1000);
	అమరిక_esp8266();
	అమరిక_bmp280();

	అయితే (1)
	{
		write_bmp280_రిజిస్టరు(I2C, BMP280_CTRL_MEANS, BMP280_సాధారణ_బహుళకం, delay); // Set it to NORMAL MODE
		//log_info("write to bmp280\n   ");
		ఒకవేళ (0 == read_bmp280_రిజిస్టరు(I2C, BMP280_స్థితి_రిజిస్టరు, &తాత్కాలిక_Read_విలువ, delay))
		{
			//log_info("read from bmp280");
			delay_loop(50, 50);
			ఒకవేళ (!(తాత్కాలిక_Read_విలువ & 0x9))
			{
				//Read pressure and temperature values.
				read_bmp280_విలువలు(I2C, 0xF7, &pressure, &temperature, delay);
				రాయి("\n temp is %u.%u Celcius", temperature / 100, temperature % 100);
				రాయి("\n pressure is %u.%u kpa", pressure / 1000, pressure % 1000);
				transmit_దత్తాంశం(temperature, pressure);
			}
		}
		లేకపోతే
		{
			//Display the error
			log_error("\nTemperature read failed.");
		}
		delay_loop(1000, 1000);
	}
}
