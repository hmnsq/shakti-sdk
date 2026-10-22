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

#अन्तर्भाव "uart.h"//Includes the definitions of uart communication protocol//
#अन्तर्भाव "string.h"
#अन्तर्भाव "pinmux.h"

#परिभाषय LM75_SLAVE_स्थानाङ्कः 0x90//Defines the Starting address of slave
#परिभाषय API_कुञ्चिका   "PPI6OVOI1A2LGXMZ"
#परिभाषय ESP_UART uart_instance[1]
/**
  * @fn int write_to_esp8266(char *data)
  * @brief sends data to esp8266 using UART
  * @param data data that has to be sent to cloud
*/

पूर्णाङ्क write_गन्तव्यम्_esp8266(वर्ण *दत्त_2) {
	यावत् (*दत्त_2 != '\0') {
		write_uart_character(ESP_UART, *दत्त_2);
		दत्त_2++;
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

पूर्णाङ्क write_enter_गन्तव्यम्_esp8266(){
	write_uart_character(ESP_UART,'\r');
	write_uart_character(ESP_UART,'\n');
}

/**
  * @fn int read_from_esp8266(char *data)
  * @brief Reads data sent by esp8266
  * @details Reads data sent by esp8266 until one of the key word is found
  * @param data responses read from esp8266, mainly used for logging
*/
पूर्णाङ्क read_from_esp8266(वर्ण *दत्त_2) {
	पूर्णाङ्क ch;
	वर्ण *str = दत्त_2;
	वर्ण *test = दत्त_2;
	प्रति(पूर्णाङ्क i=0;i<198;i++) {
		read_uart_character(ESP_UART,&ch);
		//printf("read from esp %c  \n",ch);
		*str = ch;
		str++; 
		*str = '\0';
		//printf("read  %c\n",ch);
		यदि(वाक्ये_अन्विष(test,"OK") != रिक्त)  {
			प्रारूप_लिख("read from esp8266 %s\n",test);
			प्रत्यागम;
		}
		यदि(वाक्ये_अन्विष(test,"ERROR") != रिक्त) {
			प्रारूप_लिख("read from esp8266 %s\n",test);
			प्रत्यागम;
		}
		यदि(वाक्ये_अन्विष(test,">") != रिक्त) {
			प्रारूप_लिख("read from esp8266 %s\n",test);
			प्रत्यागम;
		}
		यदि(वाक्ये_अन्विष(test,"RECV") != रिक्त) {
			प्रारूप_लिख("read from esp8266 %s\n",test);
			प्रत्यागम;
		}
		यदि(वाक्ये_अन्विष(test,"IP") != रिक्त) {
			प्रारूप_लिख("read from esp8266 %s\n",test);
			प्रत्यागम;
		}
	}
	*str = '\0';
	प्रत्यागम 1;
}

/**
  * @fn void setup_esp8266 ()
  * @brief setup esp8266
  * @details set up esp8266 to send data
*/
शून्य सज्जता_esp8266(){
	वर्ण दत्त_2[200];
	write_गन्तव्यम्_esp8266("AT");
	delay(1);
	read_from_esp8266(दत्त_2);
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
	प्रारूप_लिख(" sending AT Echo off command to esp\n");
	write_गन्तव्यम्_esp8266("ATE0");
	delay(1);
	read_from_esp8266(दत्त_2);
	प्रारूप_लिख(" write AT+CIPMUX\n");
	write_गन्तव्यम्_esp8266("AT+CIPMUX=0");
	delay(1);
	read_from_esp8266(दत्त_2);
}
/**
  * @fn void transmit_data (int temperature )
  * @brief transmit temperature value to thingspeak.com using esp8266
  * @details Open http connection to thingspeak.com, using GET method send data and close the connection
  * @param temperature value that has to eb transmitted.
*/
शून्य transmit_दत्त(पूर्णाङ्क temperature) {
/***************************************************
    AT – response OK
    AT+CWLAP – list nearby available WiFi networks
    AT+CIPMUX=0
    AT+CIPSTART="TCP","api.thingspeak.com",80
    AT+CIPSEND=75
    GET https://api.thingspeak.com/update?api_key=PPI6OVOI1A2LGXMZ&field1=45

**************************************************/


	वर्ण दत्त_2[200];
	वर्ण send_दत्त_2[76];
	sprintf(send_दत्त_2,"GET https://api.thingspeak.com/update?api_key=%s&field1=%d",API_कुञ्चिका,temperature);
	//printf("\n send data %s\n",sendData);
	// Connect to Wifi using esp8266

		// Connect to Wifi using esp8266
		प्रारूप_लिख(" Open connection to thingspeak.com\n",दत्त_2);
		flush_uart(ESP_UART);
		write_गन्तव्यम्_esp8266("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80");
		read_from_esp8266(दत्त_2);
		प्रारूप_लिख(" data from esp :%s\n",दत्त_2);
	
		//delay_loop(2000,2000);
		प्रारूप_लिख(" write AT+CIPSEND\n");
		flush_uart(ESP_UART);
		write_गन्तव्यम्_esp8266("AT+CIPSEND=75");
		read_from_esp8266(दत्त_2);
		प्रारूप_लिख(" data from esp :%s\n",दत्त_2);
	
		प्रारूप_लिख(" write Data\n");
		flush_uart(ESP_UART);
		write_गन्तव्यम्_esp8266(send_दत्त_2);
	
		//flush_uart(ESP_UART);
		write_enter_गन्तव्यम्_esp8266();
		delay_loop(1000,1000);
		read_from_esp8266(दत्त_2);
		प्रारूप_लिख(" data from esp :%s\n",दत्त_2);
	
		// disconnect from link
		प्रारूप_लिख(" write AT+CIPCLOSE\n");
		flush_uart(ESP_UART);
		write_गन्तव्यम्_esp8266("AT+CIPCLOSE");
		read_from_esp8266(दत्त_2);
		प्रारूप_लिख(" data from esp :%s\n",दत्त_2);

}

/**
  * @fn void main()
  * @brief Entry point for the program
  * @detail sets the pinmux to select UART1 to communicate with esp8266
  *      Set desired baudrate, get temperature from lm75 
  *      transmit data to thingspeak.com
*/
शून्य मुख्यम्()
{	
	पूर्णाङ्क i=0;
	//int baudrate = 9600;
	पूर्णाङ्क baudrate = 115200;
	पूर्णाङ्क temperature = 24;
	पूर्णाङ्क transmit_गणनम् = 0;
	वर्ण दत्त_2[200];
   	प्रारूप_लिख("\n setting PIN MUX config to 2 .... \n");
    	*pinmux_config_reg = 0x5;
   	प्रारूप_लिख("\n set PIN MUX config to 2 .... \n");
	समुच्चयः_baud_दरः(ESP_UART,baudrate);	
	प्रारूप_लिख("\n Sending temperature data to cloud server!....\n");
	प्रारूप_लिख("\n Baud rate set to %d \n",baudrate);
	प्रारूप_लिख("\n Waiting to ESP8266 to initialize \n");
	delay(3);
	सज्जता_esp8266();
	यावत् (1) {
 		temperature = temperature_मानम्();
		यदि (temperature != 999)
			transmit_दत्त(temperature); 
		delay(60);

	}
}
