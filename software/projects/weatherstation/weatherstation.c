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

#ਅਨ੍ਤਰ੍ਭਾਵ "uart.h"//Includes the definitions of uart communication protocol//
#ਅਨ੍ਤਰ੍ਭਾਵ "string.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pinmux.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LM75_SLAVE_ਪਤਾ 0x90//Defines the Starting address of slave
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ API_ਕੁੰਜੀ   "PPI6OVOI1A2LGXMZ"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ESP_UART uart_instance[1]
/**
  * @fn int write_to_esp8266(char *data)
  * @brief sends data to esp8266 using UART
  * @param data data that has to be sent to cloud
*/

ਪੂਰਨ write_ਮੰਜ਼ਿਲ_esp8266(ਅੱਖਰ *ਅੰਕੜੇ_2) {
	ਜਦੋਂ (*ਅੰਕੜੇ_2 != '\0') {
		write_uart_character(ESP_UART, *ਅੰਕੜੇ_2);
		ਅੰਕੜੇ_2++;
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

ਪੂਰਨ write_enter_ਮੰਜ਼ਿਲ_esp8266(){
	write_uart_character(ESP_UART,'\r');
	write_uart_character(ESP_UART,'\n');
}

/**
  * @fn int read_from_esp8266(char *data)
  * @brief Reads data sent by esp8266
  * @details Reads data sent by esp8266 until one of the key word is found
  * @param data responses read from esp8266, mainly used for logging
*/
ਪੂਰਨ read_from_esp8266(ਅੱਖਰ *ਅੰਕੜੇ_2) {
	ਪੂਰਨ ch;
	ਅੱਖਰ *str = ਅੰਕੜੇ_2;
	ਅੱਖਰ *test = ਅੰਕੜੇ_2;
	ਲਈ(ਪੂਰਨ i=0;i<198;i++) {
		read_uart_character(ESP_UART,&ch);
		//printf("read from esp %c  \n",ch);
		*str = ch;
		str++; 
		*str = '\0';
		//printf("read  %c\n",ch);
		ਜੇ(ਲੜੀ_ਖੋਜ(test,"OK") != ਨਿਰਾ)  {
			ਲਿਖੋ("read from esp8266 %s\n",test);
			ਵਾਪਸ;
		}
		ਜੇ(ਲੜੀ_ਖੋਜ(test,"ERROR") != ਨਿਰਾ) {
			ਲਿਖੋ("read from esp8266 %s\n",test);
			ਵਾਪਸ;
		}
		ਜੇ(ਲੜੀ_ਖੋਜ(test,">") != ਨਿਰਾ) {
			ਲਿਖੋ("read from esp8266 %s\n",test);
			ਵਾਪਸ;
		}
		ਜੇ(ਲੜੀ_ਖੋਜ(test,"RECV") != ਨਿਰਾ) {
			ਲਿਖੋ("read from esp8266 %s\n",test);
			ਵਾਪਸ;
		}
		ਜੇ(ਲੜੀ_ਖੋਜ(test,"IP") != ਨਿਰਾ) {
			ਲਿਖੋ("read from esp8266 %s\n",test);
			ਵਾਪਸ;
		}
	}
	*str = '\0';
	ਵਾਪਸ 1;
}

/**
  * @fn void setup_esp8266 ()
  * @brief setup esp8266
  * @details set up esp8266 to send data
*/
ਖਾਲੀ ਤਿਆਰੀ_esp8266(){
	ਅੱਖਰ ਅੰਕੜੇ_2[200];
	write_ਮੰਜ਼ਿਲ_esp8266("AT");
	delay(1);
	read_from_esp8266(ਅੰਕੜੇ_2);
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
	ਲਿਖੋ(" sending AT Echo off command to esp\n");
	write_ਮੰਜ਼ਿਲ_esp8266("ATE0");
	delay(1);
	read_from_esp8266(ਅੰਕੜੇ_2);
	ਲਿਖੋ(" write AT+CIPMUX\n");
	write_ਮੰਜ਼ਿਲ_esp8266("AT+CIPMUX=0");
	delay(1);
	read_from_esp8266(ਅੰਕੜੇ_2);
}
/**
  * @fn void transmit_data (int temperature )
  * @brief transmit temperature value to thingspeak.com using esp8266
  * @details Open http connection to thingspeak.com, using GET method send data and close the connection
  * @param temperature value that has to eb transmitted.
*/
ਖਾਲੀ transmit_ਅੰਕੜੇ(ਪੂਰਨ temperature) {
/***************************************************
    AT – response OK
    AT+CWLAP – list nearby available WiFi networks
    AT+CIPMUX=0
    AT+CIPSTART="TCP","api.thingspeak.com",80
    AT+CIPSEND=75
    GET https://api.thingspeak.com/update?api_key=PPI6OVOI1A2LGXMZ&field1=45

**************************************************/


	ਅੱਖਰ ਅੰਕੜੇ_2[200];
	ਅੱਖਰ send_ਅੰਕੜੇ_2[76];
	sprintf(send_ਅੰਕੜੇ_2,"GET https://api.thingspeak.com/update?api_key=%s&field1=%d",API_ਕੁੰਜੀ,temperature);
	//printf("\n send data %s\n",sendData);
	// Connect to Wifi using esp8266

		// Connect to Wifi using esp8266
		ਲਿਖੋ(" Open connection to thingspeak.com\n",ਅੰਕੜੇ_2);
		flush_uart(ESP_UART);
		write_ਮੰਜ਼ਿਲ_esp8266("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80");
		read_from_esp8266(ਅੰਕੜੇ_2);
		ਲਿਖੋ(" data from esp :%s\n",ਅੰਕੜੇ_2);
	
		//delay_loop(2000,2000);
		ਲਿਖੋ(" write AT+CIPSEND\n");
		flush_uart(ESP_UART);
		write_ਮੰਜ਼ਿਲ_esp8266("AT+CIPSEND=75");
		read_from_esp8266(ਅੰਕੜੇ_2);
		ਲਿਖੋ(" data from esp :%s\n",ਅੰਕੜੇ_2);
	
		ਲਿਖੋ(" write Data\n");
		flush_uart(ESP_UART);
		write_ਮੰਜ਼ਿਲ_esp8266(send_ਅੰਕੜੇ_2);
	
		//flush_uart(ESP_UART);
		write_enter_ਮੰਜ਼ਿਲ_esp8266();
		delay_loop(1000,1000);
		read_from_esp8266(ਅੰਕੜੇ_2);
		ਲਿਖੋ(" data from esp :%s\n",ਅੰਕੜੇ_2);
	
		// disconnect from link
		ਲਿਖੋ(" write AT+CIPCLOSE\n");
		flush_uart(ESP_UART);
		write_ਮੰਜ਼ਿਲ_esp8266("AT+CIPCLOSE");
		read_from_esp8266(ਅੰਕੜੇ_2);
		ਲਿਖੋ(" data from esp :%s\n",ਅੰਕੜੇ_2);

}

/**
  * @fn void main()
  * @brief Entry point for the program
  * @detail sets the pinmux to select UART1 to communicate with esp8266
  *      Set desired baudrate, get temperature from lm75 
  *      transmit data to thingspeak.com
*/
ਖਾਲੀ ਮੁੱਖ()
{	
	ਪੂਰਨ i=0;
	//int baudrate = 9600;
	ਪੂਰਨ baudrate = 115200;
	ਪੂਰਨ temperature = 24;
	ਪੂਰਨ transmit_ਗਿਣਤੀ = 0;
	ਅੱਖਰ ਅੰਕੜੇ_2[200];
   	ਲਿਖੋ("\n setting PIN MUX config to 2 .... \n");
    	*pinmux_config_reg = 0x5;
   	ਲਿਖੋ("\n set PIN MUX config to 2 .... \n");
	ਸੈੱਟ_baud_ਦਰ(ESP_UART,baudrate);	
	ਲਿਖੋ("\n Sending temperature data to cloud server!....\n");
	ਲਿਖੋ("\n Baud rate set to %d \n",baudrate);
	ਲਿਖੋ("\n Waiting to ESP8266 to initialize \n");
	delay(3);
	ਤਿਆਰੀ_esp8266();
	ਜਦੋਂ (1) {
 		temperature = temperature_ਮੁੱਲ();
		ਜੇ (temperature != 999)
			transmit_ਅੰਕੜੇ(temperature); 
		delay(60);

	}
}
