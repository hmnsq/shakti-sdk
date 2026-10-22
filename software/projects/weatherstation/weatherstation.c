/***************************************************************************
* Project           			:  shakti devt board
* Name of the file	     		:  weatherstation.c
* Brief Description of file             :  A sample project to demonstrate 
					   integration of temperature sensor 
                                           and transmission of data to a website
* Name of Author    	                :  Anand Kumar S
* Email ID                              :  007334@imail.iitm.ac.in

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

  * 1. ESP8266 is configured to baud rate 9600
  * 2. ESP8266 is set in station mode
  * 3. ESP8266 is configured to connect to access point.
  * 4. A channel to receive data is configured in thingspeak.com
  * 5. Change the API_key in the weatherstation.c

*/

#ضمن "uart.h"//Includes the definitions of uart communication protocol//
#ضمن "string.h"
#ضمن "pinmux.h"

#وصف_ڪريو LM75_SLAVE_پتو 0x90//Defines the Starting address of slave
#وصف_ڪريو API_ڪنجي   "PPI6OVOI1A2LGXMZ"
#وصف_ڪريو ESP_UART uart_instance[1]
/**
  * @fn int write_to_esp8266(char *data)
  * @brief sends data to esp8266 using UART
  * @param data data that has to be sent to cloud
*/

صحيح write_منزل_esp8266(حرف *معلومات_2) {
	طالما (*معلومات_2 != '\0') {
		write_uart_character(ESP_UART, *معلومات_2);
		معلومات_2++;
	}
	write_uart_character(ESP_UART,'\r');
	write_uart_character(ESP_UART,'\n');

}

/**
  * @fn int write_enter_to_esp8266()
  * @brief sends carriage return and new line charector to esp8266
  * @detail sends carriage return and new line charector to esp8266
  *         this method is neeed to indicate end to data transmission
*/

صحيح write_enter_منزل_esp8266(){
	write_uart_character(ESP_UART,'\r');
	write_uart_character(ESP_UART,'\n');
}

/**
  * @fn int read_from_esp8266(char *data)
  * @brief Reads data sent by esp8266
  * @details Reads data sent by esp8266 until one of the key word is found
  * @param data responses read from esp8266, mainly used for logging
*/
صحيح read_from_esp8266(حرف *معلومات_2) {
	صحيح ch;
	حرف *str = معلومات_2;
	حرف *test = معلومات_2;
	لكل(صحيح i=0;i<198;i++) {
		read_uart_character(ESP_UART,&ch);
		//printf("read from esp %c  \n",ch);
		*str = ch;
		str++; 
		*str = '\0';
		//printf("read  %c\n",ch);
		إذا(لڙي_ڳولا(test,"OK") != عدم)  {
			لکو("read from esp8266 %s\n",test);
			أرجع;
		}
		إذا(لڙي_ڳولا(test,"ERROR") != عدم) {
			لکو("read from esp8266 %s\n",test);
			أرجع;
		}
		إذا(لڙي_ڳولا(test,">") != عدم) {
			لکو("read from esp8266 %s\n",test);
			أرجع;
		}
		إذا(لڙي_ڳولا(test,"RECV") != عدم) {
			لکو("read from esp8266 %s\n",test);
			أرجع;
		}
		إذا(لڙي_ڳولا(test,"IP") != عدم) {
			لکو("read from esp8266 %s\n",test);
			أرجع;
		}
	}
	*str = '\0';
	أرجع 1;
}

/**
  * @fn void setup_esp8266 ()
  * @brief setup esp8266
  * @details set up esp8266 to send data
*/
فراغ تياري_esp8266(){
	حرف معلومات_2[200];
	write_منزل_esp8266("AT");
	delay(1);
	read_from_esp8266(معلومات_2);
/*
	printf(" set esp8266 as AP\n");
	write_to_esp8266("AT+CWMODE=1");
	delay(1);
	read_from_esp8266(data);
	printf(" Connect esp8266 to AP \n");
	write_to_esp8266("AT+CWJAP=\"SSID\",\"PASSWORD\"");
	delay(3);
	read_from_esp8266(data);
*/
	لکو(" sending AT Echo off command to esp\n");
	write_منزل_esp8266("ATE0");
	delay(1);
	read_from_esp8266(معلومات_2);
	لکو(" write AT+CIPMUX\n");
	write_منزل_esp8266("AT+CIPMUX=0");
	delay(1);
	read_from_esp8266(معلومات_2);
}
/**
  * @fn void transmit_data (int temperature )
  * @brief transmit temperature value to thingspeak.com using esp8266
  * @details Open http connection to thingspeak.com, using GET method send data and close the connection
  * @param temperature value that has to eb transmitted.
*/
فراغ transmit_معلومات(صحيح temperature) {
/***************************************************
    AT – response OK
    AT+CWLAP – list nearby available WiFi networks
    AT+CIPMUX=0
    AT+CIPSTART="TCP","api.thingspeak.com",80
    AT+CIPSEND=75
    GET https://api.thingspeak.com/update?api_key=PPI6OVOI1A2LGXMZ&field1=45

**************************************************/


	حرف معلومات_2[200];
	حرف send_معلومات_2[76];
	sprintf(send_معلومات_2,"GET https://api.thingspeak.com/update?api_key=%s&field1=%d",API_ڪنجي,temperature);
	//printf("\n send data %s\n",sendData);
	// Connect to Wifi using esp8266

		// Connect to Wifi using esp8266
		لکو(" Open connection to thingspeak.com\n",معلومات_2);
		flush_uart(ESP_UART);
		write_منزل_esp8266("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80");
		read_from_esp8266(معلومات_2);
		لکو(" data from esp :%s\n",معلومات_2);
	
		//delay_loop(2000,2000);
		لکو(" write AT+CIPSEND\n");
		flush_uart(ESP_UART);
		write_منزل_esp8266("AT+CIPSEND=75");
		read_from_esp8266(معلومات_2);
		لکو(" data from esp :%s\n",معلومات_2);
	
		لکو(" write Data\n");
		flush_uart(ESP_UART);
		write_منزل_esp8266(send_معلومات_2);
	
		//flush_uart(ESP_UART);
		write_enter_منزل_esp8266();
		delay_loop(1000,1000);
		read_from_esp8266(معلومات_2);
		لکو(" data from esp :%s\n",معلومات_2);
	
		// disconnect from link
		لکو(" write AT+CIPCLOSE\n");
		flush_uart(ESP_UART);
		write_منزل_esp8266("AT+CIPCLOSE");
		read_from_esp8266(معلومات_2);
		لکو(" data from esp :%s\n",معلومات_2);

}

/**
  * @fn void main()
  * @brief Entry point for the program
  * @detail sets the pinmux to select UART1 to communicate with esp8266
  *      Set desired baudrate, get temperature from lm75 
  *      transmit data to thingspeak.com
*/
فراغ مکيه()
{	
	صحيح i=0;
	//int baudrate = 9600;
	صحيح baudrate = 115200;
	صحيح temperature = 24;
	صحيح transmit_ڳڻپ = 0;
	حرف معلومات_2[200];
   	لکو("\n setting PIN MUX config to 2 .... \n");
    	*pinmux_config_reg = 0x5;
   	لکو("\n set PIN MUX config to 2 .... \n");
	سيٽ_baud_شرح(ESP_UART,baudrate);	
	لکو("\n Sending temperature data to cloud server!....\n");
	لکو("\n Baud rate set to %d \n",baudrate);
	لکو("\n Waiting to ESP8266 to initialize \n");
	delay(3);
	تياري_esp8266();
	طالما (1) {
 		temperature = temperature_قدر();
		إذا (temperature != 999)
			transmit_معلومات(temperature); 
		delay(60);

	}
}
