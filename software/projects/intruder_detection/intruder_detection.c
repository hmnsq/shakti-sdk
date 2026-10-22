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
#ಅನ್ತರ್ಭಾವ "gpio.h"
#ಅನ್ತರ್ಭಾವ "platform.h"
#ಅನ್ತರ್ಭಾವ "intruder_detection.h" 
#ಅನ್ತರ್ಭಾವ "log.h" 
/* global variable definition*/

ಪೂರ್ಣಾಂಕ pir_present_state = 0;
ಪೂರ್ಣಾಂಕ pir_ಹಿಂದಿನ_state = 0;

ಪೂರ್ಣಾಂಕ panic_present_state=0;
ಪೂರ್ಣಾಂಕ panic_ಹಿಂದಿನ_state=0;

ಪೂರ್ಣಾಂಕ alarm_present_state=0;
ಪೂರ್ಣಾಂಕ alarm_ಹಿಂದಿನ_state=0;

ಪೂರ್ಣಾಂಕ ಮೊದಲ_flag = 1; 
ಪೂರ್ಣಾಂಕ alarm_flag = 0;
ಪೂರ್ಣಾಂಕ deactivate_flag = 0;
ಪೂರ್ಣಾಂಕ alarm_counter_flag=1; //Default value 1
ಪೂರ್ಣಾಂಕ keypad_password_flag=0;

ಪೂರ್ಣಾಂಕ alarm_counter = 0;
ಪೂರ್ಣಾಂಕ keypad_counter= 0;

// initialize key and colrow to -1 indicate no key is pressed
ಪೂರ್ಣಾಂಕ ಕೀಲಿ = -1;
ಪೂರ್ಣಾಂಕ ಲಂಬಸಾಲು_ಅಡ್ಡಸಾಲು = -1;

ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಅಡ್ಡಸಾಲು_pins[ROWNUM];
ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಲಂಬಸಾಲು_pins[COLNUM];
ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಲಂಬಸಾಲು[4]={0, 1, 2, 3};
ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಅಡ್ಡಸಾಲು[4]={4, 5, 6, 7};
ಪೂರ್ಣಾಂಕ ಕೀಲಿ_map[COLNUM][ROWNUM];
//Password
ಪೂರ್ಣಾಂಕ pass_ದತ್ತಾಂಶ[PASS_ಅಂಕೆ];

ಪೂರ್ಣಾಂಕ  ಕೀಲಿ_ಕೋಷ್ಟಕ_2[4][4] =
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
ಶೂನ್ಯ write_gpio(ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ gpio_pin, ಪೂರ್ಣಾಂಕ gpio_pin_ಬಹುಲಕ )
{
	ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ read_ದತ್ತಾಂಶ_2 = 0;
	read_ದತ್ತಾಂಶ_2 = read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG);

	ಆದರೆ(gpio_pin_ಬಹುಲಕ == 1)
	{
		write_ಶಬ್ದ (GPIO_ದತ್ತಾಂಶ_REG, ( read_ದತ್ತಾಂಶ_2 | (gpio_pin ) ) );
	}
	ಇಲ್ಲದಿದ್ದರೆ
	{
                write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, ( read_ದತ್ತಾಂಶ_2 & ( ~gpio_pin ) ) );  
	}

}

/** @fn pir_read_state
 * @brief Reads the State of the PIR Sensor Output 
 * @details Reads the status of the PIR Sensor and returns its state 
 * @param temp_read_data Present Register Data of GPIO 
 * @return 0- State (1->0 or 0->0); 1- State (0->1);2- State (1->1) 
 */
ಪೂರ್ಣಾಂಕ pir_read_state(ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ತಾತ್ಕಾಲಿಕ_read_ದತ್ತಾಂಶ)
{
  pir_present_state= ((PIR_ಒಳ & ತಾತ್ಕಾಲಿಕ_read_ದತ್ತಾಂಶ) >>PIR_ಸ್ಥಾನಾಂತರ);  

  ಆದರೆ( (pir_present_state == 1) && (pir_ಹಿಂದಿನ_state == 0) ){
	//State of 0->1
   	log_debug("\nHuman Detected - Intrusion Alert %x -- %x ",pir_present_state,pir_ಹಿಂದಿನ_state);
	pir_ಹಿಂದಿನ_state = pir_present_state;
    ಹಿಂತಿರುಗಿ 1;
  }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ((pir_present_state == 1) && (pir_ಹಿಂದಿನ_state == 1)) {
	//State of 1 -> 1
	log_debug("\nPIR Code 2 %x -- %x ",pir_present_state,pir_ಹಿಂದಿನ_state);
	pir_ಹಿಂದಿನ_state = pir_present_state;
	ಹಿಂತಿರುಗಿ 2;
  }
  ಇಲ್ಲದಿದ್ದರೆ {
	//State of 1->0 and 0->0
   	log_debug("\nPIR Code 0 %x -- %x",pir_present_state,pir_ಹಿಂದಿನ_state);
    pir_ಹಿಂದಿನ_state = pir_present_state;
    ಹಿಂತಿರುಗಿ 0;
  }
}


/** @fn panic_button_read_state
 * @brief Reads the State of the Panic Button 
 * @details Reads the state of the panic button and returns the panic 
 * @param temp_read_data Present Register Data of GPIO 
 * @return 0 - State (0->0 & 1->0) ;1 - State (0->1);2 - State (1->1) 
 */
ಪೂರ್ಣಾಂಕ panic_button_read_state(ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ತಾತ್ಕಾಲಿಕ_read_ದತ್ತಾಂಶ)
{
  panic_present_state= ( (PANIC_BUTTON & ತಾತ್ಕಾಲಿಕ_read_ದತ್ತಾಂಶ) >> PANIC_BUTTON_ಸ್ಥಾನಾಂತರ);  

  ಆದರೆ( (panic_present_state == 1) && (panic_ಹಿಂದಿನ_state == 0) ) {
	  log_debug("\nHuman Detected - Intrusion Alert %x -- %x ",pir_present_state,pir_ಹಿಂದಿನ_state);
	  log_debug("\nSOS -Panic Button Activated");
	  panic_ಹಿಂದಿನ_state = panic_present_state;
	  ಹಿಂತಿರುಗಿ 1;
  }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ( (panic_ಹಿಂದಿನ_state == 1) && (panic_present_state == 1) ) {
	  //Function Returns 2 when mode is 1-1 (present and prev state)
	  log_debug("\nPanic -Code 2 %x -- %x ",pir_present_state,pir_ಹಿಂದಿನ_state);
	  panic_ಹಿಂದಿನ_state = panic_present_state;
	  ಹಿಂತಿರುಗಿ 2;
  }
  ಇಲ್ಲದಿದ್ದರೆ {
	  log_debug("\nPanic -Code 0 %x -- %x",pir_present_state,pir_ಹಿಂದಿನ_state);
	  panic_ಹಿಂದಿನ_state = panic_present_state;
	  ಹಿಂತಿರುಗಿ 0;
  }
}

/** @fn buzzer_tone
 * @brief Outputs the Buzzer Tone
 * @details Generates a tone for the buzzer module
 */
ಶೂನ್ಯ buzzer_tone()
{
	ಪೂರ್ಣಾಂಕ i=0;

	ಗಾಗಿ (i = 0; i < 4; i++) {
		write_gpio(BUZZER,ಮೇಲಿನ);	//Buzzer generates sound
		delay(1);
		write_gpio(BUZZER,ಕೆಳಗಿನ);		//No tone
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
ಶೂನ್ಯ  ಗಣ_ಕೀಲಿ_pins_map( ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ*  ಅಡ್ಡಸಾಲು, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ* ಲಂಬಸಾಲು, ಪೂರ್ಣಾಂಕ ಕೋಷ್ಟಕ[COLNUM][ROWNUM] )
{
	ಗಾಗಿ(ಪೂರ್ಣಾಂಕ i = 0 ; i < COLNUM ; i++)	{
		ಲಂಬಸಾಲು_pins[i] = ಲಂಬಸಾಲು[i]; // set col
	}
	ಗಾಗಿ(ಪೂರ್ಣಾಂಕ j = 0 ; j < ROWNUM ; j++) 	{
		ಅಡ್ಡಸಾಲು_pins[j] = ಅಡ್ಡಸಾಲು[j]; 	// set row
	}
	//Mapping table to its key map 
	ಗಾಗಿ(ಪೂರ್ಣಾಂಕ i = 0 ; i < COLNUM ; i++) {
		ಗಾಗಿ(ಪೂರ್ಣಾಂಕ j = 0 ; j < ROWNUM ; j++) {
			ಕೀಲಿ_map[i][j] = ಕೋಷ್ಟಕ[i][j];
		}
	}
}

/** @fn getkey
 * @brief This function returns the corresponding value in the keymap
 * @details This function returns the value from key map 
 * @param col_row The input to return the correspoding mapped value in key_map table 
 * @return Returns the corresponding value based on the input from the key_map table
 */
ಪೂರ್ಣಾಂಕ get_ಕೀಲಿ(ಪೂರ್ಣಾಂಕ ಲಂಬಸಾಲು_ಅಡ್ಡಸಾಲು)
{
	ಹಿಂತಿರುಗಿ ಕೀಲಿ_map[ಲಂಬಸಾಲು_ಅಡ್ಡಸಾಲು>>16][0xFFFF & ಲಂಬಸಾಲು_ಅಡ್ಡಸಾಲು];
}

/** @fn get_col_row
 * @brief This function returns the column-row
 * @details Identifies the pressed key by making the corresponding coloumn
   low and reading the row values     
 * @return -1 - No keys pressed ; else - Returns the key pressed by the Keypad
 */
ಪೂರ್ಣಾಂಕ get_ಲಂಬಸಾಲು_ಅಡ್ಡಸಾಲು(ಶೂನ್ಯ)
{
	ಪೂರ್ಣಾಂಕ ಲಂಬಸಾಲು_ಅಡ್ಡಸಾಲು = 0;
	ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ read_ಮೌಲ್ಯ = 0;
	ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ತಾತ್ಕಾಲಿಕ_read_ದತ್ತಾಂಶ = 0;

	//Masking Data Reg 
	ತಾತ್ಕಾಲಿಕ_read_ದತ್ತಾಂಶ = read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG);
	write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG,( ತಾತ್ಕಾಲಿಕ_read_ದತ್ತಾಂಶ | (0xF << OUTPINS_ಸ್ಥಾನಾಂತರ) ) );

	ಗಾಗಿ(ಪೂರ್ಣಾಂಕ i= 0 ; i < COLNUM ; i++)
	{
		ತಾತ್ಕಾಲಿಕ_read_ದತ್ತಾಂಶ = read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG);
		write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, ((0xF << OUTPINS_ಸ್ಥಾನಾಂತರ) & (~(0x1 <<i))));

		ಗಾಗಿ(ಪೂರ್ಣಾಂಕ j = 0 ; j < ROWNUM ; j++) {
			read_ಮೌಲ್ಯ =  read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG);
			log_debug("\n The read value is %lx; row_pins: %x", (read_ಮೌಲ್ಯ), ಅಡ್ಡಸಾಲು_pins[j]);
			ಆದರೆ( ( read_ಮೌಲ್ಯ & (1 << ಅಡ್ಡಸಾಲು_pins[j] ) ) == 0 ) {
				log_debug("\n The read value is %lx; [i:%d; j:%d] row_pins: %d; key_map=%d", read_ಮೌಲ್ಯ, i, j, ಅಡ್ಡಸಾಲು_pins[j], ಕೀಲಿ_map[i][j]);
				ಹಿಂತಿರುಗಿ ಕೀಲಿ_map[i][j];
			}
		}

		ತಾತ್ಕಾಲಿಕ_read_ದತ್ತಾಂಶ = read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG);
		write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG,(ತಾತ್ಕಾಲಿಕ_read_ದತ್ತಾಂಶ | (0xF << OUTPINS_ಸ್ಥಾನಾಂತರ)));
	}
	ಹಿಂತಿರುಗಿ -1;
}

/** @fn gpio_init
 * @brief This function initializes the GPIOs, Keypad and PIR Sensor. 
 * @details Initializing the GPIOs used by the sensors and keypad to its mode.    
 */
ಶೂನ್ಯ gpio_init()
{
	ಗಣ_ಕೀಲಿ_pins_map(ಅಡ್ಡಸಾಲು, ಲಂಬಸಾಲು,ಕೀಲಿ_ಕೋಷ್ಟಕ_2);

	//Configuring the Pin mode for pins for keypad
	ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ read_ದತ್ತಾಂಶ_2 = 0;

	read_ದತ್ತಾಂಶ_2 = read_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG);
	write_ಶಬ್ದ (GPIO_DIRECTION_CNTRL_REG, ( read_ದತ್ತಾಂಶ_2 | (OUTPINS ) ) );

	//Configuring the Pin mode for GPIO pins for other peripherals
	read_ದತ್ತಾಂಶ_2 = read_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG);
	//Configure direction of GPIO pins (1 ---> Output, 0 --> input)
	write_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG, ( read_ದತ್ತಾಂಶ_2 | GPIO_OUTPINS ) );

	//All the LED initially set to LOW
	write_gpio(LED_P1,ಕೆಳಗಿನ);
	write_gpio(LED_P2,ಕೆಳಗಿನ);
	write_gpio(LED_P3,ಕೆಳಗಿನ);
	write_gpio(LED_P4,ಕೆಳಗಿನ);
	write_gpio(BUZZER,ಕೆಳಗಿನ);
}

/** @fn main
 * @brief This is the first function called when the program is executed. 
 * @details Initializes the necessary devices and pins and then runs the main intruder detection program   
 * @return 0 
 */
ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ()
{
	//Clearing the Data Register
	ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ read_ದತ್ತಾಂಶ_2 = 0;
	ಪೂರ್ಣಾಂಕ prev_ಲಂಬಸಾಲು_ಅಡ್ಡಸಾಲು = 0;

	ಬರೆ("\n\n\tIntrusion Detection System");
	gpio_init(); //Intialization of gpio 

	ಬರೆ("\nInitialising...");

	ಆಗ(1)
	{
		read_ದತ್ತಾಂಶ_2 = read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG);

		ಆದರೆ(POWER_SWITCH & read_ದತ್ತಾಂಶ_2) {
			ಆದರೆ(ಮೊದಲ_flag){
				//First time giving the sensor to calibrate 
				delay(30);
				ಬರೆ("\nIntruder System activated");
				ಮೊದಲ_flag=0;
				alarm_counter_flag =1;
			}
			//Intruder System - ON
			write_gpio(LED_P2,ಮೇಲಿನ);
			//Deactivation of Alarm Switch
		
			ಆದರೆ(DEACTIVATE_SWITCH & read_ದತ್ತಾಂಶ_2) {
				deactivate_flag =1;
			}
			ಇಲ್ಲದಿದ್ದರೆ {
				deactivate_flag =0;
			}

			ಪೂರ್ಣಾಂಕ ತಾತ್ಕಾಲಿಕ_read_PIR  = pir_read_state(read_ದತ್ತಾಂಶ_2);
			ಪೂರ್ಣಾಂಕ ತಾತ್ಕಾಲಿಕ_read_panic = panic_button_read_state(read_ದತ್ತಾಂಶ_2);
	
			alarm_present_state= ((ತಾತ್ಕಾಲಿಕ_read_PIR > 0) || (ತಾತ್ಕಾಲಿಕ_read_panic == 1) || alarm_flag == 1 ) && (deactivate_flag == 0);

			ಆದರೆ(alarm_present_state == 1 && alarm_ಹಿಂದಿನ_state == 0) {
				log_debug("\nAlarm state- %x   %x",alarm_ಹಿಂದಿನ_state,alarm_present_state);

				ಆದರೆ(ತಾತ್ಕಾಲಿಕ_read_PIR == 1)
					ಬರೆ("\nHuman Detection\nDeactivate to stop Alarm");
				ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ(ತಾತ್ಕಾಲಿಕ_read_panic == 1)
					ಬರೆ("\nPanic Button\nDeactivate to stop Alarm");
				//else {printf("\nDeactivate the Alarm to stop...");}

				write_gpio(LED_P1,ಮೇಲಿನ);
				buzzer_tone();
				alarm_flag = 1;
				alarm_ಹಿಂದಿನ_state = alarm_present_state;

			}
			ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ(alarm_present_state == 1 && alarm_ಹಿಂದಿನ_state == 1) {
				log_debug("\n%x   %x",alarm_ಹಿಂದಿನ_state,alarm_present_state);
				write_gpio(LED_P1,ಮೇಲಿನ);
				buzzer_tone();
				alarm_flag =1;
				alarm_ಹಿಂದಿನ_state = alarm_present_state;
				alarm_counter++;
				//printf("\n\t\t\t%x",alarm_counter);

				ಆದರೆ(alarm_counter == ALARM_TIMER & ( alarm_counter_flag == 1 ))
				{
					write_gpio(LED_P3,ಮೇಲಿನ);
					ಬರೆ("\nContacting Police for Assistance");

					alarm_counter_flag = 0;
					alarm_counter = 0;
				}
				ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ(alarm_counter == ALARM_TIMER) {
					//Making Sure the alarm counter does not overflow
					alarm_counter = 0;
				}

			}
			ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ(alarm_present_state == 0 && alarm_ಹಿಂದಿನ_state == 1)
			{
				alarm_flag = 0;
				write_gpio(LED_P1,ಕೆಳಗಿನ);


				write_gpio(LED_P3,ಕೆಳಗಿನ);
				alarm_counter_flag = 1;
				alarm_counter= 0;

				ಬರೆ("\nAlarm deactivated successfully");
				alarm_ಹಿಂದಿನ_state = alarm_present_state;
			}
			ಇಲ್ಲದಿದ್ದರೆ {
				//Flags
				alarm_flag = 0;
				alarm_counter= 0;
				alarm_counter_flag = 1;

				//write_gpio(LED_P3,LOW);
				write_gpio(LED_P1,ಕೆಳಗಿನ);
				alarm_ಹಿಂದಿನ_state = alarm_present_state ;
			}

			ಲಂಬಸಾಲು_ಅಡ್ಡಸಾಲು = get_ಲಂಬಸಾಲು_ಅಡ್ಡಸಾಲು();
			//KeyPad Sensor 
			ಆದರೆ( ಲಂಬಸಾಲು_ಅಡ್ಡಸಾಲು != -1 ) {
				ಬರೆ("\nThe %x Key Pressed", ಲಂಬಸಾಲು_ಅಡ್ಡಸಾಲು);

				ಆದರೆ( ಲಂಬಸಾಲು_ಅಡ್ಡಸಾಲು == ಕೀಲಿ_map[3][3]) {
					ಬರೆ("\nEnter Password-");
				}
				delay(1);
			}
		}
		ಇಲ್ಲದಿದ್ದರೆ {
			//Intruder System Off
			write_gpio(LED_P2,ಕೆಳಗಿನ);
			ಮೊದಲ_flag = 1;
		}
		//end of infinite while loop
	}
	ಹಿಂತಿರುಗಿ 0;
}
