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

#అన్తర్భావ "platform.h"
#అన్తర్భావ "gpio.h" // includes definitions of gpio pins and read, write functions//
#అన్తర్భావ "led_driver.h"
#అన్తర్భావ "utils.h"

/*! Define one of the the following macros to control LEDs in different ways. */
//#define CONTROL_INDIVIDUAL_LEDS  /*! Controls LEDs Individually */
//#define CONTROL_NORMAL_LEDS /*! Control Normal LEDs only */
//#define CONTROL_RGB_LEDX /*! Controls RGB LEDs individually */
//#define CONTROL_RGB_LEDS /*! controls RGB leds only */
//#define CONTROL_ALL_LEDS /*! Controls all LEDs */
#నిర్వచించు TOGGLE_LEDX /*! Toggles LEDs individually */
//#define TOGGLE_NORMAL_LEDX /*! Toggles Normal LEDx ONLY */
//#define TOGGLE_RGB_LEDX //!Toggles RGB leds only 
//#define TOGGLE_ALL_LEDX //Toggles all led

#నిర్వచించు DELAY1 1000
#నిర్వచించు DELAY2 1000

/** @fn void main()
 * @brief Performs the toggling operation  with the help of button.
 * @details Based on the uncommented macro. Performs the on/off/toggle 
 * operation on LEDS.     
 */
శూన్య ప్రధాన()
{
	//  write_word(GPIO_DIRECTION_CNTRL_REG, 0x0);
	//  write_word(GPIO_DATA_REG, 0x0);

#ఒకవేళ defined(ARTIX7_35T) || defined(ARTIX7_100T)

#నిర్వచితమైతే CONTROL_INDIVIDUAL_LEDS
	configure_ledx(LED0_B);
	configure_ledx(LED0_R);
	configure_ledx(LED0_G);
	configure_ledx(LED1_B);
	configure_ledx(LED1_R);
	configure_ledx(LED1_G);
	configure_ledx(LED2);
	configure_ledx(LED3);
#అయితే_ముగింపు

#నిర్వచితమైతే  CONTROL_RGB_LEDX
	configure_rgb_ledx(RGB_LED0);
	configure_rgb_ledx(RGB_LED1);
#అయితే_ముగింపు

#నిర్వచితమైతే  CONTROL_RGB_LEDS
	configure_rgb_leds();
#అయితే_ముగింపు

#నిర్వచితమైతే  CONTROL_సాధారణ_LEDS
	configure_సాధారణ_leds();
#అయితే_ముగింపు

#నిర్వచితమైతే CONTROL_ALL_LEDS
	configure_all_leds();
#అయితే_ముగింపు

#నిర్వచితమైతే TOGGLE_LEDX
	configure_ledx(LED0_B);
	configure_ledx(LED0_R);
	configure_ledx(LED0_G);
	configure_ledx(LED1_B);
	configure_ledx(LED1_R);
	configure_ledx(LED1_G);
	configure_ledx(LED2);
	configure_ledx(LED3);
#అయితే_ముగింపు

#నిర్వచితమైతే TOGGLE_సాధారణ_LEDX
	configure_సాధారణ_leds();
#అయితే_ముగింపు

#నిర్వచితమైతే TOGGLE_RGB_LEDX
	configure_rgb_leds();
#అయితే_ముగింపు

#నిర్వచితమైతే TOGGLE_ALL_LEDX
	configure_all_leds();
#అయితే_ముగింపు


	write_మాట(GPIO_దత్తాంశం_REG, 0x0);

	అయితే (1){
#నిర్వచితమైతే CONTROL_INDIVIDUAL_LEDS
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
#అయితే_ముగింపు

#నిర్వచితమైతే CONTROL_సాధారణ_LEDS
		turn_on_సాధారణ_leds();
		delay_loop(DELAY1, DELAY2);
		turn_off_సాధారణ_leds();
		delay_loop(DELAY1, DELAY2);
#అయితే_ముగింపు

#ఒకవేళ 0
#నిర్వచితమైతే CONTROL_RGB_LEDX
		turn_on_rgb_ledx( RGB_LED0);
		turn_on_rgb_ledx( RGB_LED1);
		delay_loop(DELAY1, DELAY2);
		turn_off_rgb_ledx( RGB_LED0);
		turn_off_rgb_ledx( RGB_LED1);
		delay_loop(DELAY1, DELAY2);
#అయితే_ముగింపు
#అయితే_ముగింపు
#నిర్వచితమైతే CONTROL_RGB_LEDX
		turn_on_rgb_ledx( RGB_LED0);
		turn_off_rgb_ledx( RGB_LED1);
		delay_loop(DELAY1, DELAY2);
		turn_off_rgb_ledx( RGB_LED0);
		turn_on_rgb_ledx( RGB_LED1);
		delay_loop(DELAY1, DELAY2);
#అయితే_ముగింపు

#నిర్వచితమైతే CONTROL_RGB_LEDS
		turn_on_rgb_leds();
		delay_loop(DELAY1, DELAY2);
		turn_off_rgb_leds();
		delay_loop(DELAY1, DELAY2);
#అయితే_ముగింపు


#నిర్వచితమైతే CONTROL_ALL_LEDS
		turn_on_all_leds();
		delay_loop(DELAY1, DELAY2);
		turn_off_all_leds();
		delay_loop(DELAY1, DELAY2);
		//  ToggleAllLeds(1000);
#అయితే_ముగింపు


#నిర్వచితమైతే TOGGLE_LEDX
		toggle_ledx(LED0_R, DELAY1, DELAY2);
		toggle_ledx(LED0_G, DELAY1, DELAY2);
		toggle_ledx(LED0_B, DELAY1, DELAY2);
		toggle_ledx(LED1_R, DELAY1, DELAY2);
		toggle_ledx(LED1_G, DELAY1, DELAY2);
		toggle_ledx(LED1_B, DELAY1, DELAY2);
		toggle_ledx(LED2, DELAY1, DELAY2);
		toggle_ledx(LED3, DELAY1, DELAY2);
#అయితే_ముగింపు

#నిర్వచితమైతే TOGGLE_సాధారణ_LEDX
		toggle_సాధారణ_leds(DELAY1, DELAY2);
#అయితే_ముగింపు

#నిర్వచితమైతే TOGGLE_RGB_LEDX
		toggle_rgb_leds(DELAY1, DELAY2);
#అయితే_ముగింపు

#నిర్వచితమైతే TOGGLE_ALL_LEDX
		toggle_all_leds(DELAY1, DELAY2);
#అయితే_ముగింపు
	}
#అయితే_ముగింపు
}
