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
#ضمن "gpio.h"
#ضمن "platform.h"
#ضمن "intruder_detection.h" 
#ضمن "log.h" 
/* global variable definition*/

صحيح pir_present_state = 0;
صحيح pir_پچھلا_state = 0;

صحيح panic_present_state=0;
صحيح panic_پچھلا_state=0;

صحيح alarm_present_state=0;
صحيح alarm_پچھلا_state=0;

صحيح پہلا_flag = 1; 
صحيح alarm_flag = 0;
صحيح deactivate_flag = 0;
صحيح alarm_counter_flag=1; //Default value 1
صحيح keypad_password_flag=0;

صحيح alarm_counter = 0;
صحيح keypad_counter= 0;

// initialize key and colrow to -1 indicate no key is pressed
صحيح کلید = -1;
صحيح خانہ_صف = -1;

بنانشانی صحيح صف_pins[ROWNUM];
بنانشانی صحيح خانہ_pins[COLNUM];
بنانشانی صحيح خانہ[4]={0, 1, 2, 3};
بنانشانی صحيح صف[4]={4, 5, 6, 7};
صحيح کلید_map[COLNUM][ROWNUM];
//Password
صحيح pass_انکڑے[PASS_عدد];

صحيح  کلید_جدول_2[4][4] =
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
فراغ write_gpio(بنانشانی لما gpio_pin, صحيح gpio_pin_منوال )
{
	بنانشانی لما read_انکڑے_2 = 0;
	read_انکڑے_2 = read_لفظ(GPIO_انکڑے_REG);

	إذا(gpio_pin_منوال == 1)
	{
		write_لفظ (GPIO_انکڑے_REG, ( read_انکڑے_2 | (gpio_pin ) ) );
	}
	وإلا
	{
                write_لفظ(GPIO_انکڑے_REG, ( read_انکڑے_2 & ( ~gpio_pin ) ) );  
	}

}

/** @fn pir_read_state
 * @brief Reads the State of the PIR Sensor Output 
 * @details Reads the status of the PIR Sensor and returns its state 
 * @param temp_read_data Present Register Data of GPIO 
 * @return 0- State (1->0 or 0->0); 1- State (0->1);2- State (1->1) 
 */
صحيح pir_read_state(بنانشانی لما عارضی_read_انکڑے)
{
  pir_present_state= ((PIR_وچ & عارضی_read_انکڑے) >>PIR_وتھ);  

  إذا( (pir_present_state == 1) && (pir_پچھلا_state == 0) ){
	//State of 0->1
   	log_debug("\nHuman Detected - Intrusion Alert %x -- %x ",pir_present_state,pir_پچھلا_state);
	pir_پچھلا_state = pir_present_state;
    أرجع 1;
  }
  وإلا إذا((pir_present_state == 1) && (pir_پچھلا_state == 1)) {
	//State of 1 -> 1
	log_debug("\nPIR Code 2 %x -- %x ",pir_present_state,pir_پچھلا_state);
	pir_پچھلا_state = pir_present_state;
	أرجع 2;
  }
  وإلا {
	//State of 1->0 and 0->0
   	log_debug("\nPIR Code 0 %x -- %x",pir_present_state,pir_پچھلا_state);
    pir_پچھلا_state = pir_present_state;
    أرجع 0;
  }
}


/** @fn panic_button_read_state
 * @brief Reads the State of the Panic Button 
 * @details Reads the state of the panic button and returns the panic 
 * @param temp_read_data Present Register Data of GPIO 
 * @return 0 - State (0->0 & 1->0) ;1 - State (0->1);2 - State (1->1) 
 */
صحيح panic_button_read_state(بنانشانی لما عارضی_read_انکڑے)
{
  panic_present_state= ( (PANIC_BUTTON & عارضی_read_انکڑے) >> PANIC_BUTTON_وتھ);  

  إذا( (panic_present_state == 1) && (panic_پچھلا_state == 0) ) {
	  log_debug("\nHuman Detected - Intrusion Alert %x -- %x ",pir_present_state,pir_پچھلا_state);
	  log_debug("\nSOS -Panic Button Activated");
	  panic_پچھلا_state = panic_present_state;
	  أرجع 1;
  }
  وإلا إذا( (panic_پچھلا_state == 1) && (panic_present_state == 1) ) {
	  //Function Returns 2 when mode is 1-1 (present and prev state)
	  log_debug("\nPanic -Code 2 %x -- %x ",pir_present_state,pir_پچھلا_state);
	  panic_پچھلا_state = panic_present_state;
	  أرجع 2;
  }
  وإلا {
	  log_debug("\nPanic -Code 0 %x -- %x",pir_present_state,pir_پچھلا_state);
	  panic_پچھلا_state = panic_present_state;
	  أرجع 0;
  }
}

/** @fn buzzer_tone
 * @brief Outputs the Buzzer Tone
 * @details Generates a tone for the buzzer module
 */
فراغ buzzer_tone()
{
	صحيح i=0;

	لكل (i = 0; i < 4; i++) {
		write_gpio(BUZZER,بلند);	//Buzzer generates sound
		delay(1);
		write_gpio(BUZZER,کم);		//No tone
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
فراغ  سیٹ_کلید_pins_map( بنانشانی صحيح*  صف, بنانشانی صحيح* خانہ, صحيح جدول[COLNUM][ROWNUM] )
{
	لكل(صحيح i = 0 ; i < COLNUM ; i++)	{
		خانہ_pins[i] = خانہ[i]; // set col
	}
	لكل(صحيح j = 0 ; j < ROWNUM ; j++) 	{
		صف_pins[j] = صف[j]; 	// set row
	}
	//Mapping table to its key map 
	لكل(صحيح i = 0 ; i < COLNUM ; i++) {
		لكل(صحيح j = 0 ; j < ROWNUM ; j++) {
			کلید_map[i][j] = جدول[i][j];
		}
	}
}

/** @fn getkey
 * @brief This function returns the corresponding value in the keymap
 * @details This function returns the value from key map 
 * @param col_row The input to return the correspoding mapped value in key_map table 
 * @return Returns the corresponding value based on the input from the key_map table
 */
صحيح get_کلید(صحيح خانہ_صف)
{
	أرجع کلید_map[خانہ_صف>>16][0xFFFF & خانہ_صف];
}

/** @fn get_col_row
 * @brief This function returns the column-row
 * @details Identifies the pressed key by making the corresponding coloumn
   low and reading the row values     
 * @return -1 - No keys pressed ; else - Returns the key pressed by the Keypad
 */
صحيح get_خانہ_صف(فراغ)
{
	صحيح خانہ_صف = 0;
	بنانشانی لما read_قدر = 0;
	بنانشانی لما عارضی_read_انکڑے = 0;

	//Masking Data Reg 
	عارضی_read_انکڑے = read_لفظ(GPIO_انکڑے_REG);
	write_لفظ(GPIO_انکڑے_REG,( عارضی_read_انکڑے | (0xF << OUTPINS_وتھ) ) );

	لكل(صحيح i= 0 ; i < COLNUM ; i++)
	{
		عارضی_read_انکڑے = read_لفظ(GPIO_انکڑے_REG);
		write_لفظ(GPIO_انکڑے_REG, ((0xF << OUTPINS_وتھ) & (~(0x1 <<i))));

		لكل(صحيح j = 0 ; j < ROWNUM ; j++) {
			read_قدر =  read_لفظ(GPIO_انکڑے_REG);
			log_debug("\n The read value is %lx; row_pins: %x", (read_قدر), صف_pins[j]);
			إذا( ( read_قدر & (1 << صف_pins[j] ) ) == 0 ) {
				log_debug("\n The read value is %lx; [i:%d; j:%d] row_pins: %d; key_map=%d", read_قدر, i, j, صف_pins[j], کلید_map[i][j]);
				أرجع کلید_map[i][j];
			}
		}

		عارضی_read_انکڑے = read_لفظ(GPIO_انکڑے_REG);
		write_لفظ(GPIO_انکڑے_REG,(عارضی_read_انکڑے | (0xF << OUTPINS_وتھ)));
	}
	أرجع -1;
}

/** @fn gpio_init
 * @brief This function initializes the GPIOs, Keypad and PIR Sensor. 
 * @details Initializing the GPIOs used by the sensors and keypad to its mode.    
 */
فراغ gpio_init()
{
	سیٹ_کلید_pins_map(صف, خانہ,کلید_جدول_2);

	//Configuring the Pin mode for pins for keypad
	بنانشانی لما read_انکڑے_2 = 0;

	read_انکڑے_2 = read_لفظ(GPIO_DIRECTION_CNTRL_REG);
	write_لفظ (GPIO_DIRECTION_CNTRL_REG, ( read_انکڑے_2 | (OUTPINS ) ) );

	//Configuring the Pin mode for GPIO pins for other peripherals
	read_انکڑے_2 = read_لفظ(GPIO_DIRECTION_CNTRL_REG);
	//Configure direction of GPIO pins (1 ---> Output, 0 --> input)
	write_لفظ(GPIO_DIRECTION_CNTRL_REG, ( read_انکڑے_2 | GPIO_OUTPINS ) );

	//All the LED initially set to LOW
	write_gpio(LED_P1,کم);
	write_gpio(LED_P2,کم);
	write_gpio(LED_P3,کم);
	write_gpio(LED_P4,کم);
	write_gpio(BUZZER,کم);
}

/** @fn main
 * @brief This is the first function called when the program is executed. 
 * @details Initializes the necessary devices and pins and then runs the main intruder detection program   
 * @return 0 
 */
صحيح مکھ()
{
	//Clearing the Data Register
	بنانشانی لما read_انکڑے_2 = 0;
	صحيح prev_خانہ_صف = 0;

	لکھو("\n\n\tIntrusion Detection System");
	gpio_init(); //Intialization of gpio 

	لکھو("\nInitialising...");

	طالما(1)
	{
		read_انکڑے_2 = read_لفظ(GPIO_انکڑے_REG);

		إذا(POWER_SWITCH & read_انکڑے_2) {
			إذا(پہلا_flag){
				//First time giving the sensor to calibrate 
				delay(30);
				لکھو("\nIntruder System activated");
				پہلا_flag=0;
				alarm_counter_flag =1;
			}
			//Intruder System - ON
			write_gpio(LED_P2,بلند);
			//Deactivation of Alarm Switch
		
			إذا(DEACTIVATE_SWITCH & read_انکڑے_2) {
				deactivate_flag =1;
			}
			وإلا {
				deactivate_flag =0;
			}

			صحيح عارضی_read_PIR  = pir_read_state(read_انکڑے_2);
			صحيح عارضی_read_panic = panic_button_read_state(read_انکڑے_2);
	
			alarm_present_state= ((عارضی_read_PIR > 0) || (عارضی_read_panic == 1) || alarm_flag == 1 ) && (deactivate_flag == 0);

			إذا(alarm_present_state == 1 && alarm_پچھلا_state == 0) {
				log_debug("\nAlarm state- %x   %x",alarm_پچھلا_state,alarm_present_state);

				إذا(عارضی_read_PIR == 1)
					لکھو("\nHuman Detection\nDeactivate to stop Alarm");
				وإلا إذا(عارضی_read_panic == 1)
					لکھو("\nPanic Button\nDeactivate to stop Alarm");
				//else {printf("\nDeactivate the Alarm to stop...");}

				write_gpio(LED_P1,بلند);
				buzzer_tone();
				alarm_flag = 1;
				alarm_پچھلا_state = alarm_present_state;

			}
			وإلا إذا(alarm_present_state == 1 && alarm_پچھلا_state == 1) {
				log_debug("\n%x   %x",alarm_پچھلا_state,alarm_present_state);
				write_gpio(LED_P1,بلند);
				buzzer_tone();
				alarm_flag =1;
				alarm_پچھلا_state = alarm_present_state;
				alarm_counter++;
				//printf("\n\t\t\t%x",alarm_counter);

				إذا(alarm_counter == ALARM_TIMER & ( alarm_counter_flag == 1 ))
				{
					write_gpio(LED_P3,بلند);
					لکھو("\nContacting Police for Assistance");

					alarm_counter_flag = 0;
					alarm_counter = 0;
				}
				وإلا إذا(alarm_counter == ALARM_TIMER) {
					//Making Sure the alarm counter does not overflow
					alarm_counter = 0;
				}

			}
			وإلا إذا(alarm_present_state == 0 && alarm_پچھلا_state == 1)
			{
				alarm_flag = 0;
				write_gpio(LED_P1,کم);


				write_gpio(LED_P3,کم);
				alarm_counter_flag = 1;
				alarm_counter= 0;

				لکھو("\nAlarm deactivated successfully");
				alarm_پچھلا_state = alarm_present_state;
			}
			وإلا {
				//Flags
				alarm_flag = 0;
				alarm_counter= 0;
				alarm_counter_flag = 1;

				//write_gpio(LED_P3,LOW);
				write_gpio(LED_P1,کم);
				alarm_پچھلا_state = alarm_present_state ;
			}

			خانہ_صف = get_خانہ_صف();
			//KeyPad Sensor 
			إذا( خانہ_صف != -1 ) {
				لکھو("\nThe %x Key Pressed", خانہ_صف);

				إذا( خانہ_صف == کلید_map[3][3]) {
					لکھو("\nEnter Password-");
				}
				delay(1);
			}
		}
		وإلا {
			//Intruder System Off
			write_gpio(LED_P2,کم);
			پہلا_flag = 1;
		}
		//end of infinite while loop
	}
	أرجع 0;
}
