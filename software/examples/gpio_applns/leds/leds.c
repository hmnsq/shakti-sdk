/***************************************************************************
 * Project           	       : shakti devt board
 * Name of the file	       : leds.c
 * Brief Description of file   : Control an led with the help of a button, gpio based.
 * Name of Author    	       : Kotteeswaran
 * Email ID                    : kottee.1@gmail.com

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
@file leds.c
@brief Contains the driver routines to glow LEDs.
@detail Switches ON/OFF/TOGGLE the LEDs.
*/

#ಅನ್ತರ್ಭಾವ "platform.h"
#ಅನ್ತರ್ಭಾವ "gpio.h" // includes definitions of gpio pins and read, write functions//
#ಅನ್ತರ್ಭಾವ "led_driver.h"
#ಅನ್ತರ್ಭಾವ "utils.h"

/*! Define one of the the following macros to control LEDs in different ways. */
//#define CONTROL_INDIVIDUAL_LEDS  /*! Controls LEDs Individually */
//#define CONTROL_NORMAL_LEDS /*! Control Normal LEDs only */
//#define CONTROL_RGB_LEDX /*! Controls RGB LEDs individually */
//#define CONTROL_RGB_LEDS /*! controls RGB leds only */
//#define CONTROL_ALL_LEDS /*! Controls all LEDs */
#ವ್ಯಾಖ್ಯಾನಿಸು TOGGLE_LEDX /*! Toggles LEDs individually */
//#define TOGGLE_NORMAL_LEDX /*! Toggles Normal LEDx ONLY */
//#define TOGGLE_RGB_LEDX //!Toggles RGB leds only 
//#define TOGGLE_ALL_LEDX //Toggles all led

#ವ್ಯಾಖ್ಯಾನಿಸು DELAY1 1000
#ವ್ಯಾಖ್ಯಾನಿಸು DELAY2 1000

/** @fn void main()
 * @brief Performs the toggling operation  with the help of button.
 * @details Based on the uncommented macro. Performs the on/off/toggle 
 * operation on LEDS.     
 */
ಶೂನ್ಯ ಮುಖ್ಯ()
{
	//  write_word(GPIO_DIRECTION_CNTRL_REG, 0x0);
	//  write_word(GPIO_DATA_REG, 0x0);

#ಆದರೆ defined(ARTIX7_35T) || defined(ARTIX7_100T)

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONTROL_INDIVIDUAL_LEDS
	configure_ledx(LED0_B);
	configure_ledx(LED0_R);
	configure_ledx(LED0_G);
	configure_ledx(LED1_B);
	configure_ledx(LED1_R);
	configure_ledx(LED1_G);
	configure_ledx(LED2);
	configure_ledx(LED3);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ  CONTROL_RGB_LEDX
	configure_rgb_ledx(RGB_LED0);
	configure_rgb_ledx(RGB_LED1);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ  CONTROL_RGB_LEDS
	configure_rgb_leds();
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ  CONTROL_ಸಾಮಾನ್ಯ_LEDS
	configure_ಸಾಮಾನ್ಯ_leds();
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONTROL_ALL_LEDS
	configure_all_leds();
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TOGGLE_LEDX
	configure_ledx(LED0_B);
	configure_ledx(LED0_R);
	configure_ledx(LED0_G);
	configure_ledx(LED1_B);
	configure_ledx(LED1_R);
	configure_ledx(LED1_G);
	configure_ledx(LED2);
	configure_ledx(LED3);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TOGGLE_ಸಾಮಾನ್ಯ_LEDX
	configure_ಸಾಮಾನ್ಯ_leds();
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TOGGLE_RGB_LEDX
	configure_rgb_leds();
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TOGGLE_ALL_LEDX
	configure_all_leds();
#ಆದರೆ_ಅಂತ್ಯ


	write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, 0x0);

	ಆಗ (1){
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONTROL_INDIVIDUAL_LEDS
		delay_loop(DELAY1, DELAY2);
		turn_on_ledx( LED0_G);
		delay_loop(DELAY1, DELAY2);
		turn_on_ledx( LED0_B);
		delay_loop(DELAY1, DELAY2);
		turn_off_ledx( LED0_R);
		delay_loop(DELAY1, DELAY2);
		turn_off_ledx( LED0_G);
		delay_loop(DELAY1, DELAY2);
		turn_off_ledx( LED0_B);
		delay_loop(DELAY1, DELAY2);

		turn_on_ledx( LED1_R);
		delay_loop(DELAY1, DELAY2);
		turn_on_ledx( LED1_G);
		delay_loop(DELAY1, DELAY2);
		turn_on_ledx( LED1_B);
		delay_loop(DELAY1, DELAY2);
		turn_off_ledx( LED1_R);
		delay_loop(DELAY1, DELAY2);
		turn_off_ledx( LED1_G);
		delay_loop(DELAY1, DELAY2);
		turn_off_ledx( LED1_B);
		delay_loop(DELAY1, DELAY2);


		turn_on_ledx( LED2);
		delay_loop(DELAY1, DELAY2);
		turn_on_ledx( LED3);
		delay_loop(DELAY1, DELAY2);
		turn_off_ledx( LED2);
		delay_loop(DELAY1, DELAY2);
		turn_off_ledx( LED3);
		delay_loop(DELAY1, DELAY2);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONTROL_ಸಾಮಾನ್ಯ_LEDS
		turn_on_ಸಾಮಾನ್ಯ_leds();
		delay_loop(DELAY1, DELAY2);
		turn_off_ಸಾಮಾನ್ಯ_leds();
		delay_loop(DELAY1, DELAY2);
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ 0
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONTROL_RGB_LEDX
		turn_on_rgb_ledx( RGB_LED0);
		turn_on_rgb_ledx( RGB_LED1);
		delay_loop(DELAY1, DELAY2);
		turn_off_rgb_ledx( RGB_LED0);
		turn_off_rgb_ledx( RGB_LED1);
		delay_loop(DELAY1, DELAY2);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONTROL_RGB_LEDX
		turn_on_rgb_ledx( RGB_LED0);
		turn_off_rgb_ledx( RGB_LED1);
		delay_loop(DELAY1, DELAY2);
		turn_off_rgb_ledx( RGB_LED0);
		turn_on_rgb_ledx( RGB_LED1);
		delay_loop(DELAY1, DELAY2);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONTROL_RGB_LEDS
		turn_on_rgb_leds();
		delay_loop(DELAY1, DELAY2);
		turn_off_rgb_leds();
		delay_loop(DELAY1, DELAY2);
#ಆದರೆ_ಅಂತ್ಯ


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CONTROL_ALL_LEDS
		turn_on_all_leds();
		delay_loop(DELAY1, DELAY2);
		turn_off_all_leds();
		delay_loop(DELAY1, DELAY2);
		//  ToggleAllLeds(1000);
#ಆದರೆ_ಅಂತ್ಯ


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TOGGLE_LEDX
		toggle_ledx(LED0_R, DELAY1, DELAY2);
		toggle_ledx(LED0_G, DELAY1, DELAY2);
		toggle_ledx(LED0_B, DELAY1, DELAY2);
		toggle_ledx(LED1_R, DELAY1, DELAY2);
		toggle_ledx(LED1_G, DELAY1, DELAY2);
		toggle_ledx(LED1_B, DELAY1, DELAY2);
		toggle_ledx(LED2, DELAY1, DELAY2);
		toggle_ledx(LED3, DELAY1, DELAY2);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TOGGLE_ಸಾಮಾನ್ಯ_LEDX
		toggle_ಸಾಮಾನ್ಯ_leds(DELAY1, DELAY2);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TOGGLE_RGB_LEDX
		toggle_rgb_leds(DELAY1, DELAY2);
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ TOGGLE_ALL_LEDX
		toggle_all_leds(DELAY1, DELAY2);
#ಆದರೆ_ಅಂತ್ಯ
	}
#ಆದರೆ_ಅಂತ್ಯ
}
