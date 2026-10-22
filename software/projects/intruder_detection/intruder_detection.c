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
#অন্তর্ভাব "gpio.h"
#অন্তর্ভাব "platform.h"
#অন্তর্ভাব "intruder_detection.h" 
#অন্তর্ভাব "log.h" 
/* global variable definition*/

পূর্ণসংখ্যা pir_present_state = 0;
পূর্ণসংখ্যা pir_previous_state = 0;

পূর্ণসংখ্যা panic_present_state=0;
পূর্ণসংখ্যা panic_previous_state=0;

পূর্ণসংখ্যা alarm_present_state=0;
পূর্ণসংখ্যা alarm_previous_state=0;

পূর্ণসংখ্যা first_flag = 1; 
পূর্ণসংখ্যা alarm_flag = 0;
পূর্ণসংখ্যা deactivate_flag = 0;
পূর্ণসংখ্যা alarm_গণক_flag=1; //Default value 1
পূর্ণসংখ্যা keypad_password_flag=0;

পূর্ণসংখ্যা alarm_গণক = 0;
পূর্ণসংখ্যা keypad_গণক= 0;

// initialize key and colrow to -1 indicate no key is pressed
পূর্ণসংখ্যা চাবি = -1;
পূর্ণসংখ্যা col_row = -1;

unsigned পূর্ণসংখ্যা row_pins[ROWNUM];
unsigned পূর্ণসংখ্যা col_pins[COLNUM];
unsigned পূর্ণসংখ্যা col[4]={0, 1, 2, 3};
unsigned পূর্ণসংখ্যা row[4]={4, 5, 6, 7};
পূর্ণসংখ্যা চাবি_map[COLNUM][ROWNUM];
//Password
পূর্ণসংখ্যা pass_তথ্য[PASS_অঙ্ক];

পূর্ণসংখ্যা  চাবি_Table[4][4] =
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
শূন্য write_gpio(unsigned long gpio_pin, পূর্ণসংখ্যা gpio_pin_mode )
{
	unsigned long read_তথ্য_2 = 0;
	read_তথ্য_2 = read_word(GPIO_তথ্য_REG);

	যদি(gpio_pin_mode == 1)
	{
		write_word (GPIO_তথ্য_REG, ( read_তথ্য_2 | (gpio_pin ) ) );
	}
	অন্যথা
	{
                write_word(GPIO_তথ্য_REG, ( read_তথ্য_2 & ( ~gpio_pin ) ) );  
	}

}

/** @fn pir_read_state
 * @brief Reads the State of the PIR Sensor Output 
 * @details Reads the status of the PIR Sensor and returns its state 
 * @param temp_read_data Present Register Data of GPIO 
 * @return 0- State (1->0 or 0->0); 1- State (0->1);2- State (1->1) 
 */
পূর্ণসংখ্যা pir_read_state(unsigned long অস্থায়ী_read_তথ্য)
{
  pir_present_state= ((PIR_IN & অস্থায়ী_read_তথ্য) >>PIR_OFFSET);  

  যদি( (pir_present_state == 1) && (pir_previous_state == 0) ){
	//State of 0->1
   	log_debug("\nHuman Detected - Intrusion Alert %x -- %x ",pir_present_state,pir_previous_state);
	pir_previous_state = pir_present_state;
    ফেরত 1;
  }
  অন্যথা যদি((pir_present_state == 1) && (pir_previous_state == 1)) {
	//State of 1 -> 1
	log_debug("\nPIR Code 2 %x -- %x ",pir_present_state,pir_previous_state);
	pir_previous_state = pir_present_state;
	ফেরত 2;
  }
  অন্যথা {
	//State of 1->0 and 0->0
   	log_debug("\nPIR Code 0 %x -- %x",pir_present_state,pir_previous_state);
    pir_previous_state = pir_present_state;
    ফেরত 0;
  }
}


/** @fn panic_button_read_state
 * @brief Reads the State of the Panic Button 
 * @details Reads the state of the panic button and returns the panic 
 * @param temp_read_data Present Register Data of GPIO 
 * @return 0 - State (0->0 & 1->0) ;1 - State (0->1);2 - State (1->1) 
 */
পূর্ণসংখ্যা panic_button_read_state(unsigned long অস্থায়ী_read_তথ্য)
{
  panic_present_state= ( (PANIC_BUTTON & অস্থায়ী_read_তথ্য) >> PANIC_BUTTON_OFFSET);  

  যদি( (panic_present_state == 1) && (panic_previous_state == 0) ) {
	  log_debug("\nHuman Detected - Intrusion Alert %x -- %x ",pir_present_state,pir_previous_state);
	  log_debug("\nSOS -Panic Button Activated");
	  panic_previous_state = panic_present_state;
	  ফেরত 1;
  }
  অন্যথা যদি( (panic_previous_state == 1) && (panic_present_state == 1) ) {
	  //Function Returns 2 when mode is 1-1 (present and prev state)
	  log_debug("\nPanic -Code 2 %x -- %x ",pir_present_state,pir_previous_state);
	  panic_previous_state = panic_present_state;
	  ফেরত 2;
  }
  অন্যথা {
	  log_debug("\nPanic -Code 0 %x -- %x",pir_present_state,pir_previous_state);
	  panic_previous_state = panic_present_state;
	  ফেরত 0;
  }
}

/** @fn buzzer_tone
 * @brief Outputs the Buzzer Tone
 * @details Generates a tone for the buzzer module
 */
শূন্য buzzer_tone()
{
	পূর্ণসংখ্যা i=0;

	জন্য (i = 0; i < 4; i++) {
		write_gpio(BUZZER,উপরের);	//Buzzer generates sound
		delay(1);
		write_gpio(BUZZER,নিচের);		//No tone
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
শূন্য  set_চাবি_pins_map( unsigned পূর্ণসংখ্যা*  row, unsigned পূর্ণসংখ্যা* col, পূর্ণসংখ্যা table[COLNUM][ROWNUM] )
{
	জন্য(পূর্ণসংখ্যা i = 0 ; i < COLNUM ; i++)	{
		col_pins[i] = col[i]; // set col
	}
	জন্য(পূর্ণসংখ্যা j = 0 ; j < ROWNUM ; j++) 	{
		row_pins[j] = row[j]; 	// set row
	}
	//Mapping table to its key map 
	জন্য(পূর্ণসংখ্যা i = 0 ; i < COLNUM ; i++) {
		জন্য(পূর্ণসংখ্যা j = 0 ; j < ROWNUM ; j++) {
			চাবি_map[i][j] = table[i][j];
		}
	}
}

/** @fn getkey
 * @brief This function returns the corresponding value in the keymap
 * @details This function returns the value from key map 
 * @param col_row The input to return the correspoding mapped value in key_map table 
 * @return Returns the corresponding value based on the input from the key_map table
 */
পূর্ণসংখ্যা get_চাবি(পূর্ণসংখ্যা col_row)
{
	ফেরত চাবি_map[col_row>>16][0xFFFF & col_row];
}

/** @fn get_col_row
 * @brief This function returns the column-row
 * @details Identifies the pressed key by making the corresponding coloumn
   low and reading the row values     
 * @return -1 - No keys pressed ; else - Returns the key pressed by the Keypad
 */
পূর্ণসংখ্যা get_col_row(শূন্য)
{
	পূর্ণসংখ্যা col_row = 0;
	unsigned long read_মান = 0;
	unsigned long অস্থায়ী_read_তথ্য = 0;

	//Masking Data Reg 
	অস্থায়ী_read_তথ্য = read_word(GPIO_তথ্য_REG);
	write_word(GPIO_তথ্য_REG,( অস্থায়ী_read_তথ্য | (0xF << OUTPINS_OFFSET) ) );

	জন্য(পূর্ণসংখ্যা i= 0 ; i < COLNUM ; i++)
	{
		অস্থায়ী_read_তথ্য = read_word(GPIO_তথ্য_REG);
		write_word(GPIO_তথ্য_REG, ((0xF << OUTPINS_OFFSET) & (~(0x1 <<i))));

		জন্য(পূর্ণসংখ্যা j = 0 ; j < ROWNUM ; j++) {
			read_মান =  read_word(GPIO_তথ্য_REG);
			log_debug("\n The read value is %lx; row_pins: %x", (read_মান), row_pins[j]);
			যদি( ( read_মান & (1 << row_pins[j] ) ) == 0 ) {
				log_debug("\n The read value is %lx; [i:%d; j:%d] row_pins: %d; key_map=%d", read_মান, i, j, row_pins[j], চাবি_map[i][j]);
				ফেরত চাবি_map[i][j];
			}
		}

		অস্থায়ী_read_তথ্য = read_word(GPIO_তথ্য_REG);
		write_word(GPIO_তথ্য_REG,(অস্থায়ী_read_তথ্য | (0xF << OUTPINS_OFFSET)));
	}
	ফেরত -1;
}

/** @fn gpio_init
 * @brief This function initializes the GPIOs, Keypad and PIR Sensor. 
 * @details Initializing the GPIOs used by the sensors and keypad to its mode.    
 */
শূন্য gpio_init()
{
	set_চাবি_pins_map(row, col,চাবি_Table);

	//Configuring the Pin mode for pins for keypad
	unsigned long read_তথ্য_2 = 0;

	read_তথ্য_2 = read_word(GPIO_DIRECTION_CNTRL_REG);
	write_word (GPIO_DIRECTION_CNTRL_REG, ( read_তথ্য_2 | (OUTPINS ) ) );

	//Configuring the Pin mode for GPIO pins for other peripherals
	read_তথ্য_2 = read_word(GPIO_DIRECTION_CNTRL_REG);
	//Configure direction of GPIO pins (1 ---> Output, 0 --> input)
	write_word(GPIO_DIRECTION_CNTRL_REG, ( read_তথ্য_2 | GPIO_OUTPINS ) );

	//All the LED initially set to LOW
	write_gpio(LED_P1,নিচের);
	write_gpio(LED_P2,নিচের);
	write_gpio(LED_P3,নিচের);
	write_gpio(LED_P4,নিচের);
	write_gpio(BUZZER,নিচের);
}

/** @fn main
 * @brief This is the first function called when the program is executed. 
 * @details Initializes the necessary devices and pins and then runs the main intruder detection program   
 * @return 0 
 */
পূর্ণসংখ্যা প্রধান()
{
	//Clearing the Data Register
	unsigned long read_তথ্য_2 = 0;
	পূর্ণসংখ্যা পূর্ব_col_row = 0;

	printf("\n\n\tIntrusion Detection System");
	gpio_init(); //Intialization of gpio 

	printf("\nInitialising...");

	যখন(1)
	{
		read_তথ্য_2 = read_word(GPIO_তথ্য_REG);

		যদি(POWER_SWITCH & read_তথ্য_2) {
			যদি(first_flag){
				//First time giving the sensor to calibrate 
				delay(30);
				printf("\nIntruder System activated");
				first_flag=0;
				alarm_গণক_flag =1;
			}
			//Intruder System - ON
			write_gpio(LED_P2,উপরের);
			//Deactivation of Alarm Switch
		
			যদি(DEACTIVATE_SWITCH & read_তথ্য_2) {
				deactivate_flag =1;
			}
			অন্যথা {
				deactivate_flag =0;
			}

			পূর্ণসংখ্যা অস্থায়ী_read_PIR  = pir_read_state(read_তথ্য_2);
			পূর্ণসংখ্যা অস্থায়ী_read_panic = panic_button_read_state(read_তথ্য_2);
	
			alarm_present_state= ((অস্থায়ী_read_PIR > 0) || (অস্থায়ী_read_panic == 1) || alarm_flag == 1 ) && (deactivate_flag == 0);

			যদি(alarm_present_state == 1 && alarm_previous_state == 0) {
				log_debug("\nAlarm state- %x   %x",alarm_previous_state,alarm_present_state);

				যদি(অস্থায়ী_read_PIR == 1)
					printf("\nHuman Detection\nDeactivate to stop Alarm");
				অন্যথা যদি(অস্থায়ী_read_panic == 1)
					printf("\nPanic Button\nDeactivate to stop Alarm");
				//else {printf("\nDeactivate the Alarm to stop...");}

				write_gpio(LED_P1,উপরের);
				buzzer_tone();
				alarm_flag = 1;
				alarm_previous_state = alarm_present_state;

			}
			অন্যথা যদি(alarm_present_state == 1 && alarm_previous_state == 1) {
				log_debug("\n%x   %x",alarm_previous_state,alarm_present_state);
				write_gpio(LED_P1,উপরের);
				buzzer_tone();
				alarm_flag =1;
				alarm_previous_state = alarm_present_state;
				alarm_গণক++;
				//printf("\n\t\t\t%x",alarm_counter);

				যদি(alarm_গণক == ALARM_TIMER & ( alarm_গণক_flag == 1 ))
				{
					write_gpio(LED_P3,উপরের);
					printf("\nContacting Police for Assistance");

					alarm_গণক_flag = 0;
					alarm_গণক = 0;
				}
				অন্যথা যদি(alarm_গণক == ALARM_TIMER) {
					//Making Sure the alarm counter does not overflow
					alarm_গণক = 0;
				}

			}
			অন্যথা যদি(alarm_present_state == 0 && alarm_previous_state == 1)
			{
				alarm_flag = 0;
				write_gpio(LED_P1,নিচের);


				write_gpio(LED_P3,নিচের);
				alarm_গণক_flag = 1;
				alarm_গণক= 0;

				printf("\nAlarm deactivated successfully");
				alarm_previous_state = alarm_present_state;
			}
			অন্যথা {
				//Flags
				alarm_flag = 0;
				alarm_গণক= 0;
				alarm_গণক_flag = 1;

				//write_gpio(LED_P3,LOW);
				write_gpio(LED_P1,নিচের);
				alarm_previous_state = alarm_present_state ;
			}

			col_row = get_col_row();
			//KeyPad Sensor 
			যদি( col_row != -1 ) {
				printf("\nThe %x Key Pressed", col_row);

				যদি( col_row == চাবি_map[3][3]) {
					printf("\nEnter Password-");
				}
				delay(1);
			}
		}
		অন্যথা {
			//Intruder System Off
			write_gpio(LED_P2,নিচের);
			first_flag = 1;
		}
		//end of infinite while loop
	}
	ফেরত 0;
}
