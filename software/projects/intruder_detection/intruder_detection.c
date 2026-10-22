/***************************************************************************
* Project				:  shakti devt board
* Name of the file			:  intruder_detection.c
* Brief Description of file		:  Intruder detection with keypad and PIR sensors.
* Name of Author			:  Sambhav Jain
* Email ID				:  sambhav.jv@gmail.com 
   
 Copyright (C) 2020  IIT Madras. All rights reserved.

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
@file intruder_detection.c
@brief Intruder detection using PIR Sensors and Keypad 
@detail Intruder detection using PIR Sensors for detection of intruder and Keypad for interfacing, locking and unlocking the device.
*/

/***********************************************************
*		Pin Definitions
************************************************************/
// GPIOx       - Pin Mapped
//     	0       -Keypad Top Line-4   	(Output)
//		1       -Keypad Top Line-3		(Output)
// 		2       -Keypad Top Line-2		(Output)
//		3       -Keypad Top Line-1		(Output)
//		4       -Keypad Bottom Line-4	(Output)
//		5       -Keypad Bottom Line-3	(Output)
//		6       -Keypad Bottom Line-2	(Output)
//		7       -Keypad Bottom Line-1	(Output)
//		Gnd		-Keypad Bottom Line-5	
//		Vcc		-Keypad Bottom Line-6	
 

//		8		-PIR Sensor Output Pin	(Input)
//		16		-LED P1					(Output)
//		19		-LED P2					(Output)
//		11		-Buzzer					(Output)
//		18		-LED P3					(Output)
//		21		-LED P4					(Output)
//		28		-Panic Button			(Input)
//		24		-Power Switch   		(Input)
//		25		-Deactivation Switch	(Input)

/***********************************************************
*		Include File Definitions
************************************************************/
#అన్తర్భావ "gpio.h"
#అన్తర్భావ "platform.h"
#అన్తర్భావ "intruder_detection.h" 
#అన్తర్భావ "log.h" 
/* global variable definition*/

పూర్ణాంకం pir_present_state = 0;
పూర్ణాంకం pir_మునుపటి_state = 0;

పూర్ణాంకం panic_present_state=0;
పూర్ణాంకం panic_మునుపటి_state=0;

పూర్ణాంకం alarm_present_state=0;
పూర్ణాంకం alarm_మునుపటి_state=0;

పూర్ణాంకం మొదటి_flag = 1; 
పూర్ణాంకం alarm_flag = 0;
పూర్ణాంకం deactivate_flag = 0;
పూర్ణాంకం alarm_counter_flag=1; //Default value 1
పూర్ణాంకం keypad_password_flag=0;

పూర్ణాంకం alarm_counter = 0;
పూర్ణాంకం keypad_counter= 0;

// initialize key and colrow to -1 indicate no key is pressed
పూర్ణాంకం కీలకం = -1;
పూర్ణాంకం నిలువు_అడ్డువరుస = -1;

గుర్తులేని పూర్ణాంకం అడ్డువరుస_pins[ROWNUM];
గుర్తులేని పూర్ణాంకం నిలువు_pins[COLNUM];
గుర్తులేని పూర్ణాంకం నిలువు[4]={0, 1, 2, 3};
గుర్తులేని పూర్ణాంకం అడ్డువరుస[4]={4, 5, 6, 7};
పూర్ణాంకం కీలకం_map[COLNUM][ROWNUM];
//Password
పూర్ణాంకం pass_దత్తాంశం[PASS_అంకె];

పూర్ణాంకం  కీలకం_పట్టిక_2[4][4] =
{
	{  1,  4,  7,  0},
	{  2,  5,  8, 15},
	{  3,  6,  9, 14},
	{ 10, 11, 12, 13}
};

/** @fn write_gpio
 * @brief This function Writes to the Data Register 
 * @details Writing to specific GPIO Pins to set to HIGH or LOW 
 * @param  gpio_pin The pin number for which the function sets HIGH or LOW
 * @param gpio_pin_mode Mode = 0 - Sets the GPIO Pin to LOW, 1- Sets the GPIO Pin to HIGH 
 */
శూన్య write_gpio(గుర్తులేని దీర్ఘ gpio_pin, పూర్ణాంకం gpio_pin_బహుళకం )
{
	గుర్తులేని దీర్ఘ read_దత్తాంశం_2 = 0;
	read_దత్తాంశం_2 = read_మాట(GPIO_దత్తాంశం_REG);

	ఒకవేళ(gpio_pin_బహుళకం == 1)
	{
		write_మాట (GPIO_దత్తాంశం_REG, ( read_దత్తాంశం_2 | (gpio_pin ) ) );
	}
	లేకపోతే
	{
                write_మాట(GPIO_దత్తాంశం_REG, ( read_దత్తాంశం_2 & ( ~gpio_pin ) ) );  
	}

}

/** @fn pir_read_state
 * @brief Reads the State of the PIR Sensor Output 
 * @details Reads the status of the PIR Sensor and returns its state 
 * @param temp_read_data Present Register Data of GPIO 
 * @return 0- State (1->0 or 0->0); 1- State (0->1);2- State (1->1) 
 */
పూర్ణాంకం pir_read_state(గుర్తులేని దీర్ఘ తాత్కాలిక_read_దత్తాంశం)
{
  pir_present_state= ((PIR_లోపల & తాత్కాలిక_read_దత్తాంశం) >>PIR_స్థానభ్రంశం);  

  ఒకవేళ( (pir_present_state == 1) && (pir_మునుపటి_state == 0) ){
	//State of 0->1
   	log_debug("\nHuman Detected - Intrusion Alert %x -- %x ",pir_present_state,pir_మునుపటి_state);
	pir_మునుపటి_state = pir_present_state;
    తిరిగి 1;
  }
  లేకపోతే ఒకవేళ((pir_present_state == 1) && (pir_మునుపటి_state == 1)) {
	//State of 1 -> 1
	log_debug("\nPIR Code 2 %x -- %x ",pir_present_state,pir_మునుపటి_state);
	pir_మునుపటి_state = pir_present_state;
	తిరిగి 2;
  }
  లేకపోతే {
	//State of 1->0 and 0->0
   	log_debug("\nPIR Code 0 %x -- %x",pir_present_state,pir_మునుపటి_state);
    pir_మునుపటి_state = pir_present_state;
    తిరిగి 0;
  }
}


/** @fn panic_button_read_state
 * @brief Reads the State of the Panic Button 
 * @details Reads the state of the panic button and returns the panic 
 * @param temp_read_data Present Register Data of GPIO 
 * @return 0 - State (0->0 & 1->0) ;1 - State (0->1);2 - State (1->1) 
 */
పూర్ణాంకం panic_button_read_state(గుర్తులేని దీర్ఘ తాత్కాలిక_read_దత్తాంశం)
{
  panic_present_state= ( (PANIC_BUTTON & తాత్కాలిక_read_దత్తాంశం) >> PANIC_BUTTON_స్థానభ్రంశం);  

  ఒకవేళ( (panic_present_state == 1) && (panic_మునుపటి_state == 0) ) {
	  log_debug("\nHuman Detected - Intrusion Alert %x -- %x ",pir_present_state,pir_మునుపటి_state);
	  log_debug("\nSOS -Panic Button Activated");
	  panic_మునుపటి_state = panic_present_state;
	  తిరిగి 1;
  }
  లేకపోతే ఒకవేళ( (panic_మునుపటి_state == 1) && (panic_present_state == 1) ) {
	  //Function Returns 2 when mode is 1-1 (present and prev state)
	  log_debug("\nPanic -Code 2 %x -- %x ",pir_present_state,pir_మునుపటి_state);
	  panic_మునుపటి_state = panic_present_state;
	  తిరిగి 2;
  }
  లేకపోతే {
	  log_debug("\nPanic -Code 0 %x -- %x",pir_present_state,pir_మునుపటి_state);
	  panic_మునుపటి_state = panic_present_state;
	  తిరిగి 0;
  }
}

/** @fn buzzer_tone
 * @brief Outputs the Buzzer Tone
 * @details Generates a tone for the buzzer module
 */
శూన్య buzzer_tone()
{
	పూర్ణాంకం i=0;

	కొరకు (i = 0; i < 4; i++) {
		write_gpio(BUZZER,ఎగువ);	//Buzzer generates sound
		delay(1);
		write_gpio(BUZZER,దిగువ);		//No tone
		delay(1);
    }
}


/** @fn set_pins
 * @brief This function sets the pins for the row and column
 * 			and maps the table to its keymap
 * @details This function sets the mapping of pin for row and column. 
 * @param row pointer address which sets row pins   
 * @param col pointer address which sets column pins
 * @param table Array which maps the table to the key map 
 */
శూన్య  సమితి_కీలకం_pins_map( గుర్తులేని పూర్ణాంకం*  అడ్డువరుస, గుర్తులేని పూర్ణాంకం* నిలువు, పూర్ణాంకం పట్టిక[COLNUM][ROWNUM] )
{
	కొరకు(పూర్ణాంకం i = 0 ; i < COLNUM ; i++)	{
		నిలువు_pins[i] = నిలువు[i]; // set col
	}
	కొరకు(పూర్ణాంకం j = 0 ; j < ROWNUM ; j++) 	{
		అడ్డువరుస_pins[j] = అడ్డువరుస[j]; 	// set row
	}
	//Mapping table to its key map 
	కొరకు(పూర్ణాంకం i = 0 ; i < COLNUM ; i++) {
		కొరకు(పూర్ణాంకం j = 0 ; j < ROWNUM ; j++) {
			కీలకం_map[i][j] = పట్టిక[i][j];
		}
	}
}

/** @fn getkey
 * @brief This function returns the corresponding value in the keymap
 * @details This function returns the value from key map 
 * @param col_row The input to return the correspoding mapped value in key_map table 
 * @return Returns the corresponding value based on the input from the key_map table
 */
పూర్ణాంకం get_కీలకం(పూర్ణాంకం నిలువు_అడ్డువరుస)
{
	తిరిగి కీలకం_map[నిలువు_అడ్డువరుస>>16][0xFFFF & నిలువు_అడ్డువరుస];
}

/** @fn get_col_row
 * @brief This function returns the column-row
 * @details Identifies the pressed key by making the corresponding coloumn
   low and reading the row values     
 * @return -1 - No keys pressed ; else - Returns the key pressed by the Keypad
 */
పూర్ణాంకం get_నిలువు_అడ్డువరుస(శూన్య)
{
	పూర్ణాంకం నిలువు_అడ్డువరుస = 0;
	గుర్తులేని దీర్ఘ read_విలువ = 0;
	గుర్తులేని దీర్ఘ తాత్కాలిక_read_దత్తాంశం = 0;

	//Masking Data Reg 
	తాత్కాలిక_read_దత్తాంశం = read_మాట(GPIO_దత్తాంశం_REG);
	write_మాట(GPIO_దత్తాంశం_REG,( తాత్కాలిక_read_దత్తాంశం | (0xF << OUTPINS_స్థానభ్రంశం) ) );

	కొరకు(పూర్ణాంకం i= 0 ; i < COLNUM ; i++)
	{
		తాత్కాలిక_read_దత్తాంశం = read_మాట(GPIO_దత్తాంశం_REG);
		write_మాట(GPIO_దత్తాంశం_REG, ((0xF << OUTPINS_స్థానభ్రంశం) & (~(0x1 <<i))));

		కొరకు(పూర్ణాంకం j = 0 ; j < ROWNUM ; j++) {
			read_విలువ =  read_మాట(GPIO_దత్తాంశం_REG);
			log_debug("\n The read value is %lx; row_pins: %x", (read_విలువ), అడ్డువరుస_pins[j]);
			ఒకవేళ( ( read_విలువ & (1 << అడ్డువరుస_pins[j] ) ) == 0 ) {
				log_debug("\n The read value is %lx; [i:%d; j:%d] row_pins: %d; key_map=%d", read_విలువ, i, j, అడ్డువరుస_pins[j], కీలకం_map[i][j]);
				తిరిగి కీలకం_map[i][j];
			}
		}

		తాత్కాలిక_read_దత్తాంశం = read_మాట(GPIO_దత్తాంశం_REG);
		write_మాట(GPIO_దత్తాంశం_REG,(తాత్కాలిక_read_దత్తాంశం | (0xF << OUTPINS_స్థానభ్రంశం)));
	}
	తిరిగి -1;
}

/** @fn gpio_init
 * @brief This function initializes the GPIOs, Keypad and PIR Sensor. 
 * @details Initializing the GPIOs used by the sensors and keypad to its mode.    
 */
శూన్య gpio_init()
{
	సమితి_కీలకం_pins_map(అడ్డువరుస, నిలువు,కీలకం_పట్టిక_2);

	//Configuring the Pin mode for pins for keypad
	గుర్తులేని దీర్ఘ read_దత్తాంశం_2 = 0;

	read_దత్తాంశం_2 = read_మాట(GPIO_DIRECTION_CNTRL_REG);
	write_మాట (GPIO_DIRECTION_CNTRL_REG, ( read_దత్తాంశం_2 | (OUTPINS ) ) );

	//Configuring the Pin mode for GPIO pins for other peripherals
	read_దత్తాంశం_2 = read_మాట(GPIO_DIRECTION_CNTRL_REG);
	//Configure direction of GPIO pins (1 ---> Output, 0 --> input)
	write_మాట(GPIO_DIRECTION_CNTRL_REG, ( read_దత్తాంశం_2 | GPIO_OUTPINS ) );

	//All the LED initially set to LOW
	write_gpio(LED_P1,దిగువ);
	write_gpio(LED_P2,దిగువ);
	write_gpio(LED_P3,దిగువ);
	write_gpio(LED_P4,దిగువ);
	write_gpio(BUZZER,దిగువ);
}

/** @fn main
 * @brief This is the first function called when the program is executed. 
 * @details Initializes the necessary devices and pins and then runs the main intruder detection program   
 * @return 0 
 */
పూర్ణాంకం ప్రధాన()
{
	//Clearing the Data Register
	గుర్తులేని దీర్ఘ read_దత్తాంశం_2 = 0;
	పూర్ణాంకం prev_నిలువు_అడ్డువరుస = 0;

	రాయి("\n\n\tIntrusion Detection System");
	gpio_init(); //Intialization of gpio 

	రాయి("\nInitialising...");

	అయితే(1)
	{
		read_దత్తాంశం_2 = read_మాట(GPIO_దత్తాంశం_REG);

		ఒకవేళ(POWER_SWITCH & read_దత్తాంశం_2) {
			ఒకవేళ(మొదటి_flag){
				//First time giving the sensor to calibrate 
				delay(30);
				రాయి("\nIntruder System activated");
				మొదటి_flag=0;
				alarm_counter_flag =1;
			}
			//Intruder System - ON
			write_gpio(LED_P2,ఎగువ);
			//Deactivation of Alarm Switch
		
			ఒకవేళ(DEACTIVATE_SWITCH & read_దత్తాంశం_2) {
				deactivate_flag =1;
			}
			లేకపోతే {
				deactivate_flag =0;
			}

			పూర్ణాంకం తాత్కాలిక_read_PIR  = pir_read_state(read_దత్తాంశం_2);
			పూర్ణాంకం తాత్కాలిక_read_panic = panic_button_read_state(read_దత్తాంశం_2);
	
			alarm_present_state= ((తాత్కాలిక_read_PIR > 0) || (తాత్కాలిక_read_panic == 1) || alarm_flag == 1 ) && (deactivate_flag == 0);

			ఒకవేళ(alarm_present_state == 1 && alarm_మునుపటి_state == 0) {
				log_debug("\nAlarm state- %x   %x",alarm_మునుపటి_state,alarm_present_state);

				ఒకవేళ(తాత్కాలిక_read_PIR == 1)
					రాయి("\nHuman Detection\nDeactivate to stop Alarm");
				లేకపోతే ఒకవేళ(తాత్కాలిక_read_panic == 1)
					రాయి("\nPanic Button\nDeactivate to stop Alarm");
				//else {printf("\nDeactivate the Alarm to stop...");}

				write_gpio(LED_P1,ఎగువ);
				buzzer_tone();
				alarm_flag = 1;
				alarm_మునుపటి_state = alarm_present_state;

			}
			లేకపోతే ఒకవేళ(alarm_present_state == 1 && alarm_మునుపటి_state == 1) {
				log_debug("\n%x   %x",alarm_మునుపటి_state,alarm_present_state);
				write_gpio(LED_P1,ఎగువ);
				buzzer_tone();
				alarm_flag =1;
				alarm_మునుపటి_state = alarm_present_state;
				alarm_counter++;
				//printf("\n\t\t\t%x",alarm_counter);

				ఒకవేళ(alarm_counter == ALARM_TIMER & ( alarm_counter_flag == 1 ))
				{
					write_gpio(LED_P3,ఎగువ);
					రాయి("\nContacting Police for Assistance");

					alarm_counter_flag = 0;
					alarm_counter = 0;
				}
				లేకపోతే ఒకవేళ(alarm_counter == ALARM_TIMER) {
					//Making Sure the alarm counter does not overflow
					alarm_counter = 0;
				}

			}
			లేకపోతే ఒకవేళ(alarm_present_state == 0 && alarm_మునుపటి_state == 1)
			{
				alarm_flag = 0;
				write_gpio(LED_P1,దిగువ);


				write_gpio(LED_P3,దిగువ);
				alarm_counter_flag = 1;
				alarm_counter= 0;

				రాయి("\nAlarm deactivated successfully");
				alarm_మునుపటి_state = alarm_present_state;
			}
			లేకపోతే {
				//Flags
				alarm_flag = 0;
				alarm_counter= 0;
				alarm_counter_flag = 1;

				//write_gpio(LED_P3,LOW);
				write_gpio(LED_P1,దిగువ);
				alarm_మునుపటి_state = alarm_present_state ;
			}

			నిలువు_అడ్డువరుస = get_నిలువు_అడ్డువరుస();
			//KeyPad Sensor 
			ఒకవేళ( నిలువు_అడ్డువరుస != -1 ) {
				రాయి("\nThe %x Key Pressed", నిలువు_అడ్డువరుస);

				ఒకవేళ( నిలువు_అడ్డువరుస == కీలకం_map[3][3]) {
					రాయి("\nEnter Password-");
				}
				delay(1);
			}
		}
		లేకపోతే {
			//Intruder System Off
			write_gpio(LED_P2,దిగువ);
			మొదటి_flag = 1;
		}
		//end of infinite while loop
	}
	తిరిగి 0;
}
