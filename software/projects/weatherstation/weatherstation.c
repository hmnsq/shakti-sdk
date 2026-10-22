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

#ಅನ್ತರ್ಭಾವ "uart.h"//Includes the definitions of uart communication protocol//
#ಅನ್ತರ್ಭಾವ "string.h"
#ಅನ್ತರ್ಭಾವ "pinmux.h"

#ವ್ಯಾಖ್ಯಾನಿಸು LM75_SLAVE_ವಿಳಾಸ 0x90//Defines the Starting address of slave
#ವ್ಯಾಖ್ಯಾನಿಸು API_ಕೀಲಿ   "PPI6OVOI1A2LGXMZ"
#ವ್ಯಾಖ್ಯಾನಿಸು ESP_UART uart_instance[1]
/**
  * @fn int write_to_esp8266(char *data)
  * @brief sends data to esp8266 using UART
  * @param data data that has to be sent to cloud
*/

ಪೂರ್ಣಾಂಕ write_ಗಮ್ಯ_esp8266(ಅಕ್ಷರ *ದತ್ತಾಂಶ_2) {
	ಆಗ (*ದತ್ತಾಂಶ_2 != '\0') {
		write_uart_character(ESP_UART, *ದತ್ತಾಂಶ_2);
		ದತ್ತಾಂಶ_2++;
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

ಪೂರ್ಣಾಂಕ write_enter_ಗಮ್ಯ_esp8266(){
	write_uart_character(ESP_UART,'\r');
	write_uart_character(ESP_UART,'\n');
}

/**
  * @fn int read_from_esp8266(char *data)
  * @brief Reads data sent by esp8266
  * @details Reads data sent by esp8266 until one of the key word is found
  * @param data responses read from esp8266, mainly used for logging
*/
ಪೂರ್ಣಾಂಕ read_from_esp8266(ಅಕ್ಷರ *ದತ್ತಾಂಶ_2) {
	ಪೂರ್ಣಾಂಕ ch;
	ಅಕ್ಷರ *str = ದತ್ತಾಂಶ_2;
	ಅಕ್ಷರ *test = ದತ್ತಾಂಶ_2;
	ಗಾಗಿ(ಪೂರ್ಣಾಂಕ i=0;i<198;i++) {
		read_uart_character(ESP_UART,&ch);
		//printf("read from esp %c  \n",ch);
		*str = ch;
		str++; 
		*str = '\0';
		//printf("read  %c\n",ch);
		ಆದರೆ(ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(test,"OK") != ಖಾಲಿ)  {
			ಬರೆ("read from esp8266 %s\n",test);
			ಹಿಂತಿರುಗಿ;
		}
		ಆದರೆ(ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(test,"ERROR") != ಖಾಲಿ) {
			ಬರೆ("read from esp8266 %s\n",test);
			ಹಿಂತಿರುಗಿ;
		}
		ಆದರೆ(ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(test,">") != ಖಾಲಿ) {
			ಬರೆ("read from esp8266 %s\n",test);
			ಹಿಂತಿರುಗಿ;
		}
		ಆದರೆ(ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(test,"RECV") != ಖಾಲಿ) {
			ಬರೆ("read from esp8266 %s\n",test);
			ಹಿಂತಿರುಗಿ;
		}
		ಆದರೆ(ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(test,"IP") != ಖಾಲಿ) {
			ಬರೆ("read from esp8266 %s\n",test);
			ಹಿಂತಿರುಗಿ;
		}
	}
	*str = '\0';
	ಹಿಂತಿರುಗಿ 1;
}

/**
  * @fn void setup_esp8266 ()
  * @brief setup esp8266
  * @details set up esp8266 to send data
*/
ಶೂನ್ಯ ಸಿದ್ಧತೆ_esp8266(){
	ಅಕ್ಷರ ದತ್ತಾಂಶ_2[200];
	write_ಗಮ್ಯ_esp8266("AT");
	delay(1);
	read_from_esp8266(ದತ್ತಾಂಶ_2);
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
	ಬರೆ(" sending AT Echo off command to esp\n");
	write_ಗಮ್ಯ_esp8266("ATE0");
	delay(1);
	read_from_esp8266(ದತ್ತಾಂಶ_2);
	ಬರೆ(" write AT+CIPMUX\n");
	write_ಗಮ್ಯ_esp8266("AT+CIPMUX=0");
	delay(1);
	read_from_esp8266(ದತ್ತಾಂಶ_2);
}
/**
  * @fn void transmit_data (int temperature )
  * @brief transmit temperature value to thingspeak.com using esp8266
  * @details Open http connection to thingspeak.com, using GET method send data and close the connection
  * @param temperature value that has to eb transmitted.
*/
ಶೂನ್ಯ transmit_ದತ್ತಾಂಶ(ಪೂರ್ಣಾಂಕ temperature) {
/***************************************************
    AT – response OK
    AT+CWLAP – list nearby available WiFi networks
    AT+CIPMUX=0
    AT+CIPSTART="TCP","api.thingspeak.com",80
    AT+CIPSEND=75
    GET https://api.thingspeak.com/update?api_key=PPI6OVOI1A2LGXMZ&field1=45

**************************************************/


	ಅಕ್ಷರ ದತ್ತಾಂಶ_2[200];
	ಅಕ್ಷರ send_ದತ್ತಾಂಶ_2[76];
	sprintf(send_ದತ್ತಾಂಶ_2,"GET https://api.thingspeak.com/update?api_key=%s&field1=%d",API_ಕೀಲಿ,temperature);
	//printf("\n send data %s\n",sendData);
	// Connect to Wifi using esp8266

		// Connect to Wifi using esp8266
		ಬರೆ(" Open connection to thingspeak.com\n",ದತ್ತಾಂಶ_2);
		flush_uart(ESP_UART);
		write_ಗಮ್ಯ_esp8266("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80");
		read_from_esp8266(ದತ್ತಾಂಶ_2);
		ಬರೆ(" data from esp :%s\n",ದತ್ತಾಂಶ_2);
	
		//delay_loop(2000,2000);
		ಬರೆ(" write AT+CIPSEND\n");
		flush_uart(ESP_UART);
		write_ಗಮ್ಯ_esp8266("AT+CIPSEND=75");
		read_from_esp8266(ದತ್ತಾಂಶ_2);
		ಬರೆ(" data from esp :%s\n",ದತ್ತಾಂಶ_2);
	
		ಬರೆ(" write Data\n");
		flush_uart(ESP_UART);
		write_ಗಮ್ಯ_esp8266(send_ದತ್ತಾಂಶ_2);
	
		//flush_uart(ESP_UART);
		write_enter_ಗಮ್ಯ_esp8266();
		delay_loop(1000,1000);
		read_from_esp8266(ದತ್ತಾಂಶ_2);
		ಬರೆ(" data from esp :%s\n",ದತ್ತಾಂಶ_2);
	
		// disconnect from link
		ಬರೆ(" write AT+CIPCLOSE\n");
		flush_uart(ESP_UART);
		write_ಗಮ್ಯ_esp8266("AT+CIPCLOSE");
		read_from_esp8266(ದತ್ತಾಂಶ_2);
		ಬರೆ(" data from esp :%s\n",ದತ್ತಾಂಶ_2);

}

/**
  * @fn void main()
  * @brief Entry point for the program
  * @detail sets the pinmux to select UART1 to communicate with esp8266
  *      Set desired baudrate, get temperature from lm75 
  *      transmit data to thingspeak.com
*/
ಶೂನ್ಯ ಮುಖ್ಯ()
{	
	ಪೂರ್ಣಾಂಕ i=0;
	//int baudrate = 9600;
	ಪೂರ್ಣಾಂಕ baudrate = 115200;
	ಪೂರ್ಣಾಂಕ temperature = 24;
	ಪೂರ್ಣಾಂಕ transmit_ಎಣಿಕೆ = 0;
	ಅಕ್ಷರ ದತ್ತಾಂಶ_2[200];
   	ಬರೆ("\n setting PIN MUX config to 2 .... \n");
    	*pinmux_config_reg = 0x5;
   	ಬರೆ("\n set PIN MUX config to 2 .... \n");
	ಗಣ_baud_ದರ(ESP_UART,baudrate);	
	ಬರೆ("\n Sending temperature data to cloud server!....\n");
	ಬರೆ("\n Baud rate set to %d \n",baudrate);
	ಬರೆ("\n Waiting to ESP8266 to initialize \n");
	delay(3);
	ಸಿದ್ಧತೆ_esp8266();
	ಆಗ (1) {
 		temperature = temperature_ಮೌಲ್ಯ();
		ಆದರೆ (temperature != 999)
			transmit_ದತ್ತಾಂಶ(temperature); 
		delay(60);

	}
}
