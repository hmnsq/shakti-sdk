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
#अन्तर्भाव "gpio.h"
#अन्तर्भाव "platform.h"
#अन्तर्भाव "intruder_detection.h" 
#अन्तर्भाव "log.h" 
/* global variable definition*/

पूर्णाङ्क pir_present_state = 0;
पूर्णाङ्क pir_previous_state = 0;

पूर्णाङ्क panic_present_state=0;
पूर्णाङ्क panic_previous_state=0;

पूर्णाङ्क alarm_present_state=0;
पूर्णाङ्क alarm_previous_state=0;

पूर्णाङ्क first_flag = 1; 
पूर्णाङ्क alarm_flag = 0;
पूर्णाङ्क deactivate_flag = 0;
पूर्णाङ्क alarm_गणक_flag=1; //Default value 1
पूर्णाङ्क keypad_password_flag=0;

पूर्णाङ्क alarm_गणक = 0;
पूर्णाङ्क keypad_गणक= 0;

// initialize key and colrow to -1 indicate no key is pressed
पूर्णाङ्क कुञ्चिका = -1;
पूर्णाङ्क col_row = -1;

अचिह्नित पूर्णाङ्क row_pins[ROWNUM];
अचिह्नित पूर्णाङ्क col_pins[COLNUM];
अचिह्नित पूर्णाङ्क col[4]={0, 1, 2, 3};
अचिह्नित पूर्णाङ्क row[4]={4, 5, 6, 7};
पूर्णाङ्क कुञ्चिका_map[COLNUM][ROWNUM];
//Password
पूर्णाङ्क pass_दत्त[PASS_अङ्कः];

पूर्णाङ्क  कुञ्चिका_सारणी_2[4][4] =
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
शून्य write_gpio(अचिह्नित दीर्घ gpio_pin, पूर्णाङ्क gpio_pin_बहुलकम् )
{
	अचिह्नित दीर्घ read_दत्त_2 = 0;
	read_दत्त_2 = read_word(GPIO_दत्त_REG);

	यदि(gpio_pin_बहुलकम् == 1)
	{
		write_word (GPIO_दत्त_REG, ( read_दत्त_2 | (gpio_pin ) ) );
	}
	अन्यथा
	{
                write_word(GPIO_दत्त_REG, ( read_दत्त_2 & ( ~gpio_pin ) ) );  
	}

}

/** @fn pir_read_state
 * @brief Reads the State of the PIR Sensor Output 
 * @details Reads the status of the PIR Sensor and returns its state 
 * @param temp_read_data Present Register Data of GPIO 
 * @return 0- State (1->0 or 0->0); 1- State (0->1);2- State (1->1) 
 */
पूर्णाङ्क pir_read_state(अचिह्नित दीर्घ अस्थायी_read_दत्त)
{
  pir_present_state= ((PIR_अन्तर् & अस्थायी_read_दत्त) >>PIR_विस्थापनम्);  

  यदि( (pir_present_state == 1) && (pir_previous_state == 0) ){
	//State of 0->1
   	log_debug("\nHuman Detected - Intrusion Alert %x -- %x ",pir_present_state,pir_previous_state);
	pir_previous_state = pir_present_state;
    प्रत्यागम 1;
  }
  अन्यथा यदि((pir_present_state == 1) && (pir_previous_state == 1)) {
	//State of 1 -> 1
	log_debug("\nPIR Code 2 %x -- %x ",pir_present_state,pir_previous_state);
	pir_previous_state = pir_present_state;
	प्रत्यागम 2;
  }
  अन्यथा {
	//State of 1->0 and 0->0
   	log_debug("\nPIR Code 0 %x -- %x",pir_present_state,pir_previous_state);
    pir_previous_state = pir_present_state;
    प्रत्यागम 0;
  }
}


/** @fn panic_button_read_state
 * @brief Reads the State of the Panic Button 
 * @details Reads the state of the panic button and returns the panic 
 * @param temp_read_data Present Register Data of GPIO 
 * @return 0 - State (0->0 & 1->0) ;1 - State (0->1);2 - State (1->1) 
 */
पूर्णाङ्क panic_button_read_state(अचिह्नित दीर्घ अस्थायी_read_दत्त)
{
  panic_present_state= ( (PANIC_BUTTON & अस्थायी_read_दत्त) >> PANIC_BUTTON_विस्थापनम्);  

  यदि( (panic_present_state == 1) && (panic_previous_state == 0) ) {
	  log_debug("\nHuman Detected - Intrusion Alert %x -- %x ",pir_present_state,pir_previous_state);
	  log_debug("\nSOS -Panic Button Activated");
	  panic_previous_state = panic_present_state;
	  प्रत्यागम 1;
  }
  अन्यथा यदि( (panic_previous_state == 1) && (panic_present_state == 1) ) {
	  //Function Returns 2 when mode is 1-1 (present and prev state)
	  log_debug("\nPanic -Code 2 %x -- %x ",pir_present_state,pir_previous_state);
	  panic_previous_state = panic_present_state;
	  प्रत्यागम 2;
  }
  अन्यथा {
	  log_debug("\nPanic -Code 0 %x -- %x",pir_present_state,pir_previous_state);
	  panic_previous_state = panic_present_state;
	  प्रत्यागम 0;
  }
}

/** @fn buzzer_tone
 * @brief Outputs the Buzzer Tone
 * @details Generates a tone for the buzzer module
 */
शून्य buzzer_tone()
{
	पूर्णाङ्क i=0;

	प्रति (i = 0; i < 4; i++) {
		write_gpio(BUZZER,उच्चः);	//Buzzer generates sound
		delay(1);
		write_gpio(BUZZER,नीचः);		//No tone
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
शून्य  समुच्चयः_कुञ्चिका_pins_map( अचिह्नित पूर्णाङ्क*  row, अचिह्नित पूर्णाङ्क* col, पूर्णाङ्क सारणी[COLNUM][ROWNUM] )
{
	प्रति(पूर्णाङ्क i = 0 ; i < COLNUM ; i++)	{
		col_pins[i] = col[i]; // set col
	}
	प्रति(पूर्णाङ्क j = 0 ; j < ROWNUM ; j++) 	{
		row_pins[j] = row[j]; 	// set row
	}
	//Mapping table to its key map 
	प्रति(पूर्णाङ्क i = 0 ; i < COLNUM ; i++) {
		प्रति(पूर्णाङ्क j = 0 ; j < ROWNUM ; j++) {
			कुञ्चिका_map[i][j] = सारणी[i][j];
		}
	}
}

/** @fn getkey
 * @brief This function returns the corresponding value in the keymap
 * @details This function returns the value from key map 
 * @param col_row The input to return the correspoding mapped value in key_map table 
 * @return Returns the corresponding value based on the input from the key_map table
 */
पूर्णाङ्क get_कुञ्चिका(पूर्णाङ्क col_row)
{
	प्रत्यागम कुञ्चिका_map[col_row>>16][0xFFFF & col_row];
}

/** @fn get_col_row
 * @brief This function returns the column-row
 * @details Identifies the pressed key by making the corresponding coloumn
   low and reading the row values     
 * @return -1 - No keys pressed ; else - Returns the key pressed by the Keypad
 */
पूर्णाङ्क get_col_row(शून्य)
{
	पूर्णाङ्क col_row = 0;
	अचिह्नित दीर्घ read_मानम् = 0;
	अचिह्नित दीर्घ अस्थायी_read_दत्त = 0;

	//Masking Data Reg 
	अस्थायी_read_दत्त = read_word(GPIO_दत्त_REG);
	write_word(GPIO_दत्त_REG,( अस्थायी_read_दत्त | (0xF << OUTPINS_विस्थापनम्) ) );

	प्रति(पूर्णाङ्क i= 0 ; i < COLNUM ; i++)
	{
		अस्थायी_read_दत्त = read_word(GPIO_दत्त_REG);
		write_word(GPIO_दत्त_REG, ((0xF << OUTPINS_विस्थापनम्) & (~(0x1 <<i))));

		प्रति(पूर्णाङ्क j = 0 ; j < ROWNUM ; j++) {
			read_मानम् =  read_word(GPIO_दत्त_REG);
			log_debug("\n The read value is %lx; row_pins: %x", (read_मानम्), row_pins[j]);
			यदि( ( read_मानम् & (1 << row_pins[j] ) ) == 0 ) {
				log_debug("\n The read value is %lx; [i:%d; j:%d] row_pins: %d; key_map=%d", read_मानम्, i, j, row_pins[j], कुञ्चिका_map[i][j]);
				प्रत्यागम कुञ्चिका_map[i][j];
			}
		}

		अस्थायी_read_दत्त = read_word(GPIO_दत्त_REG);
		write_word(GPIO_दत्त_REG,(अस्थायी_read_दत्त | (0xF << OUTPINS_विस्थापनम्)));
	}
	प्रत्यागम -1;
}

/** @fn gpio_init
 * @brief This function initializes the GPIOs, Keypad and PIR Sensor. 
 * @details Initializing the GPIOs used by the sensors and keypad to its mode.    
 */
शून्य gpio_init()
{
	समुच्चयः_कुञ्चिका_pins_map(row, col,कुञ्चिका_सारणी_2);

	//Configuring the Pin mode for pins for keypad
	अचिह्नित दीर्घ read_दत्त_2 = 0;

	read_दत्त_2 = read_word(GPIO_DIRECTION_CNTRL_REG);
	write_word (GPIO_DIRECTION_CNTRL_REG, ( read_दत्त_2 | (OUTPINS ) ) );

	//Configuring the Pin mode for GPIO pins for other peripherals
	read_दत्त_2 = read_word(GPIO_DIRECTION_CNTRL_REG);
	//Configure direction of GPIO pins (1 ---> Output, 0 --> input)
	write_word(GPIO_DIRECTION_CNTRL_REG, ( read_दत्त_2 | GPIO_OUTPINS ) );

	//All the LED initially set to LOW
	write_gpio(LED_P1,नीचः);
	write_gpio(LED_P2,नीचः);
	write_gpio(LED_P3,नीचः);
	write_gpio(LED_P4,नीचः);
	write_gpio(BUZZER,नीचः);
}

/** @fn main
 * @brief This is the first function called when the program is executed. 
 * @details Initializes the necessary devices and pins and then runs the main intruder detection program   
 * @return 0 
 */
पूर्णाङ्क मुख्यम्()
{
	//Clearing the Data Register
	अचिह्नित दीर्घ read_दत्त_2 = 0;
	पूर्णाङ्क पूर्व_col_row = 0;

	प्रारूप_लिख("\n\n\tIntrusion Detection System");
	gpio_init(); //Intialization of gpio 

	प्रारूप_लिख("\nInitialising...");

	यावत्(1)
	{
		read_दत्त_2 = read_word(GPIO_दत्त_REG);

		यदि(POWER_SWITCH & read_दत्त_2) {
			यदि(first_flag){
				//First time giving the sensor to calibrate 
				delay(30);
				प्रारूप_लिख("\nIntruder System activated");
				first_flag=0;
				alarm_गणक_flag =1;
			}
			//Intruder System - ON
			write_gpio(LED_P2,उच्चः);
			//Deactivation of Alarm Switch
		
			यदि(DEACTIVATE_SWITCH & read_दत्त_2) {
				deactivate_flag =1;
			}
			अन्यथा {
				deactivate_flag =0;
			}

			पूर्णाङ्क अस्थायी_read_PIR  = pir_read_state(read_दत्त_2);
			पूर्णाङ्क अस्थायी_read_panic = panic_button_read_state(read_दत्त_2);
	
			alarm_present_state= ((अस्थायी_read_PIR > 0) || (अस्थायी_read_panic == 1) || alarm_flag == 1 ) && (deactivate_flag == 0);

			यदि(alarm_present_state == 1 && alarm_previous_state == 0) {
				log_debug("\nAlarm state- %x   %x",alarm_previous_state,alarm_present_state);

				यदि(अस्थायी_read_PIR == 1)
					प्रारूप_लिख("\nHuman Detection\nDeactivate to stop Alarm");
				अन्यथा यदि(अस्थायी_read_panic == 1)
					प्रारूप_लिख("\nPanic Button\nDeactivate to stop Alarm");
				//else {printf("\nDeactivate the Alarm to stop...");}

				write_gpio(LED_P1,उच्चः);
				buzzer_tone();
				alarm_flag = 1;
				alarm_previous_state = alarm_present_state;

			}
			अन्यथा यदि(alarm_present_state == 1 && alarm_previous_state == 1) {
				log_debug("\n%x   %x",alarm_previous_state,alarm_present_state);
				write_gpio(LED_P1,उच्चः);
				buzzer_tone();
				alarm_flag =1;
				alarm_previous_state = alarm_present_state;
				alarm_गणक++;
				//printf("\n\t\t\t%x",alarm_counter);

				यदि(alarm_गणक == ALARM_TIMER & ( alarm_गणक_flag == 1 ))
				{
					write_gpio(LED_P3,उच्चः);
					प्रारूप_लिख("\nContacting Police for Assistance");

					alarm_गणक_flag = 0;
					alarm_गणक = 0;
				}
				अन्यथा यदि(alarm_गणक == ALARM_TIMER) {
					//Making Sure the alarm counter does not overflow
					alarm_गणक = 0;
				}

			}
			अन्यथा यदि(alarm_present_state == 0 && alarm_previous_state == 1)
			{
				alarm_flag = 0;
				write_gpio(LED_P1,नीचः);


				write_gpio(LED_P3,नीचः);
				alarm_गणक_flag = 1;
				alarm_गणक= 0;

				प्रारूप_लिख("\nAlarm deactivated successfully");
				alarm_previous_state = alarm_present_state;
			}
			अन्यथा {
				//Flags
				alarm_flag = 0;
				alarm_गणक= 0;
				alarm_गणक_flag = 1;

				//write_gpio(LED_P3,LOW);
				write_gpio(LED_P1,नीचः);
				alarm_previous_state = alarm_present_state ;
			}

			col_row = get_col_row();
			//KeyPad Sensor 
			यदि( col_row != -1 ) {
				प्रारूप_लिख("\nThe %x Key Pressed", col_row);

				यदि( col_row == कुञ्चिका_map[3][3]) {
					प्रारूप_लिख("\nEnter Password-");
				}
				delay(1);
			}
		}
		अन्यथा {
			//Intruder System Off
			write_gpio(LED_P2,नीचः);
			first_flag = 1;
		}
		//end of infinite while loop
	}
	प्रत्यागम 0;
}
