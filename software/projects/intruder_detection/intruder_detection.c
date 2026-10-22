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
#ਅਨ੍ਤਰ੍ਭਾਵ "gpio.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "platform.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "intruder_detection.h" 
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h" 
/* global variable definition*/

ਪੂਰਨ pir_present_state = 0;
ਪੂਰਨ pir_ਪਿਛਲਾ_state = 0;

ਪੂਰਨ panic_present_state=0;
ਪੂਰਨ panic_ਪਿਛਲਾ_state=0;

ਪੂਰਨ alarm_present_state=0;
ਪੂਰਨ alarm_ਪਿਛਲਾ_state=0;

ਪੂਰਨ ਪਹਿਲਾ_flag = 1; 
ਪੂਰਨ alarm_flag = 0;
ਪੂਰਨ deactivate_flag = 0;
ਪੂਰਨ alarm_counter_flag=1; //Default value 1
ਪੂਰਨ keypad_password_flag=0;

ਪੂਰਨ alarm_counter = 0;
ਪੂਰਨ keypad_counter= 0;

// initialize key and colrow to -1 indicate no key is pressed
ਪੂਰਨ ਕੁੰਜੀ = -1;
ਪੂਰਨ ਖਾਨਾ_ਪੰਕਤੀ = -1;

ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਪੰਕਤੀ_pins[ROWNUM];
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਖਾਨਾ_pins[COLNUM];
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਖਾਨਾ[4]={0, 1, 2, 3};
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਪੰਕਤੀ[4]={4, 5, 6, 7};
ਪੂਰਨ ਕੁੰਜੀ_map[COLNUM][ROWNUM];
//Password
ਪੂਰਨ pass_ਅੰਕੜੇ[PASS_ਅੰਕ];

ਪੂਰਨ  ਕੁੰਜੀ_ਸਾਰਣੀ_2[4][4] =
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
ਖਾਲੀ write_gpio(ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ gpio_pin, ਪੂਰਨ gpio_pin_ਬਹੁਲਕ )
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ read_ਅੰਕੜੇ_2 = 0;
	read_ਅੰਕੜੇ_2 = read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG);

	ਜੇ(gpio_pin_ਬਹੁਲਕ == 1)
	{
		write_ਸ਼ਬਦ (GPIO_ਅੰਕੜੇ_REG, ( read_ਅੰਕੜੇ_2 | (gpio_pin ) ) );
	}
	ਨਹੀਂਤਾਂ
	{
                write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, ( read_ਅੰਕੜੇ_2 & ( ~gpio_pin ) ) );  
	}

}

/** @fn pir_read_state
 * @brief Reads the State of the PIR Sensor Output 
 * @details Reads the status of the PIR Sensor and returns its state 
 * @param temp_read_data Present Register Data of GPIO 
 * @return 0- State (1->0 or 0->0); 1- State (0->1);2- State (1->1) 
 */
ਪੂਰਨ pir_read_state(ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਆਰਜ਼ੀ_read_ਅੰਕੜੇ)
{
  pir_present_state= ((PIR_ਵਿੱਚ & ਆਰਜ਼ੀ_read_ਅੰਕੜੇ) >>PIR_ਵਿੱਥ);  

  ਜੇ( (pir_present_state == 1) && (pir_ਪਿਛਲਾ_state == 0) ){
	//State of 0->1
   	log_debug("\nHuman Detected - Intrusion Alert %x -- %x ",pir_present_state,pir_ਪਿਛਲਾ_state);
	pir_ਪਿਛਲਾ_state = pir_present_state;
    ਵਾਪਸ 1;
  }
  ਨਹੀਂਤਾਂ ਜੇ((pir_present_state == 1) && (pir_ਪਿਛਲਾ_state == 1)) {
	//State of 1 -> 1
	log_debug("\nPIR Code 2 %x -- %x ",pir_present_state,pir_ਪਿਛਲਾ_state);
	pir_ਪਿਛਲਾ_state = pir_present_state;
	ਵਾਪਸ 2;
  }
  ਨਹੀਂਤਾਂ {
	//State of 1->0 and 0->0
   	log_debug("\nPIR Code 0 %x -- %x",pir_present_state,pir_ਪਿਛਲਾ_state);
    pir_ਪਿਛਲਾ_state = pir_present_state;
    ਵਾਪਸ 0;
  }
}


/** @fn panic_button_read_state
 * @brief Reads the State of the Panic Button 
 * @details Reads the state of the panic button and returns the panic 
 * @param temp_read_data Present Register Data of GPIO 
 * @return 0 - State (0->0 & 1->0) ;1 - State (0->1);2 - State (1->1) 
 */
ਪੂਰਨ panic_button_read_state(ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਆਰਜ਼ੀ_read_ਅੰਕੜੇ)
{
  panic_present_state= ( (PANIC_BUTTON & ਆਰਜ਼ੀ_read_ਅੰਕੜੇ) >> PANIC_BUTTON_ਵਿੱਥ);  

  ਜੇ( (panic_present_state == 1) && (panic_ਪਿਛਲਾ_state == 0) ) {
	  log_debug("\nHuman Detected - Intrusion Alert %x -- %x ",pir_present_state,pir_ਪਿਛਲਾ_state);
	  log_debug("\nSOS -Panic Button Activated");
	  panic_ਪਿਛਲਾ_state = panic_present_state;
	  ਵਾਪਸ 1;
  }
  ਨਹੀਂਤਾਂ ਜੇ( (panic_ਪਿਛਲਾ_state == 1) && (panic_present_state == 1) ) {
	  //Function Returns 2 when mode is 1-1 (present and prev state)
	  log_debug("\nPanic -Code 2 %x -- %x ",pir_present_state,pir_ਪਿਛਲਾ_state);
	  panic_ਪਿਛਲਾ_state = panic_present_state;
	  ਵਾਪਸ 2;
  }
  ਨਹੀਂਤਾਂ {
	  log_debug("\nPanic -Code 0 %x -- %x",pir_present_state,pir_ਪਿਛਲਾ_state);
	  panic_ਪਿਛਲਾ_state = panic_present_state;
	  ਵਾਪਸ 0;
  }
}

/** @fn buzzer_tone
 * @brief Outputs the Buzzer Tone
 * @details Generates a tone for the buzzer module
 */
ਖਾਲੀ buzzer_tone()
{
	ਪੂਰਨ i=0;

	ਲਈ (i = 0; i < 4; i++) {
		write_gpio(BUZZER,ਉੱਚਾ);	//Buzzer generates sound
		delay(1);
		write_gpio(BUZZER,ਨੀਵਾਂ);		//No tone
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
ਖਾਲੀ  ਸੈੱਟ_ਕੁੰਜੀ_pins_map( ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ*  ਪੰਕਤੀ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ* ਖਾਨਾ, ਪੂਰਨ ਸਾਰਣੀ[COLNUM][ROWNUM] )
{
	ਲਈ(ਪੂਰਨ i = 0 ; i < COLNUM ; i++)	{
		ਖਾਨਾ_pins[i] = ਖਾਨਾ[i]; // set col
	}
	ਲਈ(ਪੂਰਨ j = 0 ; j < ROWNUM ; j++) 	{
		ਪੰਕਤੀ_pins[j] = ਪੰਕਤੀ[j]; 	// set row
	}
	//Mapping table to its key map 
	ਲਈ(ਪੂਰਨ i = 0 ; i < COLNUM ; i++) {
		ਲਈ(ਪੂਰਨ j = 0 ; j < ROWNUM ; j++) {
			ਕੁੰਜੀ_map[i][j] = ਸਾਰਣੀ[i][j];
		}
	}
}

/** @fn getkey
 * @brief This function returns the corresponding value in the keymap
 * @details This function returns the value from key map 
 * @param col_row The input to return the correspoding mapped value in key_map table 
 * @return Returns the corresponding value based on the input from the key_map table
 */
ਪੂਰਨ get_ਕੁੰਜੀ(ਪੂਰਨ ਖਾਨਾ_ਪੰਕਤੀ)
{
	ਵਾਪਸ ਕੁੰਜੀ_map[ਖਾਨਾ_ਪੰਕਤੀ>>16][0xFFFF & ਖਾਨਾ_ਪੰਕਤੀ];
}

/** @fn get_col_row
 * @brief This function returns the column-row
 * @details Identifies the pressed key by making the corresponding coloumn
   low and reading the row values     
 * @return -1 - No keys pressed ; else - Returns the key pressed by the Keypad
 */
ਪੂਰਨ get_ਖਾਨਾ_ਪੰਕਤੀ(ਖਾਲੀ)
{
	ਪੂਰਨ ਖਾਨਾ_ਪੰਕਤੀ = 0;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ read_ਮੁੱਲ = 0;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਆਰਜ਼ੀ_read_ਅੰਕੜੇ = 0;

	//Masking Data Reg 
	ਆਰਜ਼ੀ_read_ਅੰਕੜੇ = read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG);
	write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG,( ਆਰਜ਼ੀ_read_ਅੰਕੜੇ | (0xF << OUTPINS_ਵਿੱਥ) ) );

	ਲਈ(ਪੂਰਨ i= 0 ; i < COLNUM ; i++)
	{
		ਆਰਜ਼ੀ_read_ਅੰਕੜੇ = read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG);
		write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, ((0xF << OUTPINS_ਵਿੱਥ) & (~(0x1 <<i))));

		ਲਈ(ਪੂਰਨ j = 0 ; j < ROWNUM ; j++) {
			read_ਮੁੱਲ =  read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG);
			log_debug("\n The read value is %lx; row_pins: %x", (read_ਮੁੱਲ), ਪੰਕਤੀ_pins[j]);
			ਜੇ( ( read_ਮੁੱਲ & (1 << ਪੰਕਤੀ_pins[j] ) ) == 0 ) {
				log_debug("\n The read value is %lx; [i:%d; j:%d] row_pins: %d; key_map=%d", read_ਮੁੱਲ, i, j, ਪੰਕਤੀ_pins[j], ਕੁੰਜੀ_map[i][j]);
				ਵਾਪਸ ਕੁੰਜੀ_map[i][j];
			}
		}

		ਆਰਜ਼ੀ_read_ਅੰਕੜੇ = read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG);
		write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG,(ਆਰਜ਼ੀ_read_ਅੰਕੜੇ | (0xF << OUTPINS_ਵਿੱਥ)));
	}
	ਵਾਪਸ -1;
}

/** @fn gpio_init
 * @brief This function initializes the GPIOs, Keypad and PIR Sensor. 
 * @details Initializing the GPIOs used by the sensors and keypad to its mode.    
 */
ਖਾਲੀ gpio_init()
{
	ਸੈੱਟ_ਕੁੰਜੀ_pins_map(ਪੰਕਤੀ, ਖਾਨਾ,ਕੁੰਜੀ_ਸਾਰਣੀ_2);

	//Configuring the Pin mode for pins for keypad
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ read_ਅੰਕੜੇ_2 = 0;

	read_ਅੰਕੜੇ_2 = read_ਸ਼ਬਦ(GPIO_DIRECTION_CNTRL_REG);
	write_ਸ਼ਬਦ (GPIO_DIRECTION_CNTRL_REG, ( read_ਅੰਕੜੇ_2 | (OUTPINS ) ) );

	//Configuring the Pin mode for GPIO pins for other peripherals
	read_ਅੰਕੜੇ_2 = read_ਸ਼ਬਦ(GPIO_DIRECTION_CNTRL_REG);
	//Configure direction of GPIO pins (1 ---> Output, 0 --> input)
	write_ਸ਼ਬਦ(GPIO_DIRECTION_CNTRL_REG, ( read_ਅੰਕੜੇ_2 | GPIO_OUTPINS ) );

	//All the LED initially set to LOW
	write_gpio(LED_P1,ਨੀਵਾਂ);
	write_gpio(LED_P2,ਨੀਵਾਂ);
	write_gpio(LED_P3,ਨੀਵਾਂ);
	write_gpio(LED_P4,ਨੀਵਾਂ);
	write_gpio(BUZZER,ਨੀਵਾਂ);
}

/** @fn main
 * @brief This is the first function called when the program is executed. 
 * @details Initializes the necessary devices and pins and then runs the main intruder detection program   
 * @return 0 
 */
ਪੂਰਨ ਮੁੱਖ()
{
	//Clearing the Data Register
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ read_ਅੰਕੜੇ_2 = 0;
	ਪੂਰਨ prev_ਖਾਨਾ_ਪੰਕਤੀ = 0;

	ਲਿਖੋ("\n\n\tIntrusion Detection System");
	gpio_init(); //Intialization of gpio 

	ਲਿਖੋ("\nInitialising...");

	ਜਦੋਂ(1)
	{
		read_ਅੰਕੜੇ_2 = read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG);

		ਜੇ(POWER_SWITCH & read_ਅੰਕੜੇ_2) {
			ਜੇ(ਪਹਿਲਾ_flag){
				//First time giving the sensor to calibrate 
				delay(30);
				ਲਿਖੋ("\nIntruder System activated");
				ਪਹਿਲਾ_flag=0;
				alarm_counter_flag =1;
			}
			//Intruder System - ON
			write_gpio(LED_P2,ਉੱਚਾ);
			//Deactivation of Alarm Switch
		
			ਜੇ(DEACTIVATE_SWITCH & read_ਅੰਕੜੇ_2) {
				deactivate_flag =1;
			}
			ਨਹੀਂਤਾਂ {
				deactivate_flag =0;
			}

			ਪੂਰਨ ਆਰਜ਼ੀ_read_PIR  = pir_read_state(read_ਅੰਕੜੇ_2);
			ਪੂਰਨ ਆਰਜ਼ੀ_read_panic = panic_button_read_state(read_ਅੰਕੜੇ_2);
	
			alarm_present_state= ((ਆਰਜ਼ੀ_read_PIR > 0) || (ਆਰਜ਼ੀ_read_panic == 1) || alarm_flag == 1 ) && (deactivate_flag == 0);

			ਜੇ(alarm_present_state == 1 && alarm_ਪਿਛਲਾ_state == 0) {
				log_debug("\nAlarm state- %x   %x",alarm_ਪਿਛਲਾ_state,alarm_present_state);

				ਜੇ(ਆਰਜ਼ੀ_read_PIR == 1)
					ਲਿਖੋ("\nHuman Detection\nDeactivate to stop Alarm");
				ਨਹੀਂਤਾਂ ਜੇ(ਆਰਜ਼ੀ_read_panic == 1)
					ਲਿਖੋ("\nPanic Button\nDeactivate to stop Alarm");
				//else {printf("\nDeactivate the Alarm to stop...");}

				write_gpio(LED_P1,ਉੱਚਾ);
				buzzer_tone();
				alarm_flag = 1;
				alarm_ਪਿਛਲਾ_state = alarm_present_state;

			}
			ਨਹੀਂਤਾਂ ਜੇ(alarm_present_state == 1 && alarm_ਪਿਛਲਾ_state == 1) {
				log_debug("\n%x   %x",alarm_ਪਿਛਲਾ_state,alarm_present_state);
				write_gpio(LED_P1,ਉੱਚਾ);
				buzzer_tone();
				alarm_flag =1;
				alarm_ਪਿਛਲਾ_state = alarm_present_state;
				alarm_counter++;
				//printf("\n\t\t\t%x",alarm_counter);

				ਜੇ(alarm_counter == ALARM_TIMER & ( alarm_counter_flag == 1 ))
				{
					write_gpio(LED_P3,ਉੱਚਾ);
					ਲਿਖੋ("\nContacting Police for Assistance");

					alarm_counter_flag = 0;
					alarm_counter = 0;
				}
				ਨਹੀਂਤਾਂ ਜੇ(alarm_counter == ALARM_TIMER) {
					//Making Sure the alarm counter does not overflow
					alarm_counter = 0;
				}

			}
			ਨਹੀਂਤਾਂ ਜੇ(alarm_present_state == 0 && alarm_ਪਿਛਲਾ_state == 1)
			{
				alarm_flag = 0;
				write_gpio(LED_P1,ਨੀਵਾਂ);


				write_gpio(LED_P3,ਨੀਵਾਂ);
				alarm_counter_flag = 1;
				alarm_counter= 0;

				ਲਿਖੋ("\nAlarm deactivated successfully");
				alarm_ਪਿਛਲਾ_state = alarm_present_state;
			}
			ਨਹੀਂਤਾਂ {
				//Flags
				alarm_flag = 0;
				alarm_counter= 0;
				alarm_counter_flag = 1;

				//write_gpio(LED_P3,LOW);
				write_gpio(LED_P1,ਨੀਵਾਂ);
				alarm_ਪਿਛਲਾ_state = alarm_present_state ;
			}

			ਖਾਨਾ_ਪੰਕਤੀ = get_ਖਾਨਾ_ਪੰਕਤੀ();
			//KeyPad Sensor 
			ਜੇ( ਖਾਨਾ_ਪੰਕਤੀ != -1 ) {
				ਲਿਖੋ("\nThe %x Key Pressed", ਖਾਨਾ_ਪੰਕਤੀ);

				ਜੇ( ਖਾਨਾ_ਪੰਕਤੀ == ਕੁੰਜੀ_map[3][3]) {
					ਲਿਖੋ("\nEnter Password-");
				}
				delay(1);
			}
		}
		ਨਹੀਂਤਾਂ {
			//Intruder System Off
			write_gpio(LED_P2,ਨੀਵਾਂ);
			ਪਹਿਲਾ_flag = 1;
		}
		//end of infinite while loop
	}
	ਵਾਪਸ 0;
}
