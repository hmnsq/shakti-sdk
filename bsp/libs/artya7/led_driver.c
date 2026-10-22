/***************************************************************************
 * Project           		: shakti devt board
 * Name of the file	     	: led_driver.c
 * Brief Description of file    : Performs the I2C operations using gpio pins.
 * Name of Author    	        : Kotteeswaran
 * Email ID                     : kottee.1@gmail.com

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
  @file led_driver.c
  @brief Performs the I2C operations using gpio pins.
  @detail  Configures leds and maps to the gpio pins.
 */

#ఒకవేళ defined(ARTIX7_35T) || defined(ARTIX7_100T)

#అన్తర్భావ "platform.h"
#అన్తర్భావ "gpio.h"
#అన్తర్భావ "led_driver.h"
#అన్తర్భావ "utils.h"

 /** @fn void configure_ledx(unsigned long pin_cntrl)
 * @brief Configures Individual LED pins as output.
 * @details 8 GPIO pins are mapped to 8 LEDs. This function configures
 *          each LED as output pin.
 * @param unsigned long (pin_cntrl- Pin that needs to be configured as LED.)
 */
శూన్య configure_ledx(గుర్తులేని దీర్ఘ pin_cntrl)
{
	గుర్తులేని దీర్ఘ read_దత్తాంశం_2 = 0;
	read_దత్తాంశం_2 = read_మాట(GPIO_DIRECTION_CNTRL_REG);
	write_మాట(GPIO_DIRECTION_CNTRL_REG, ( read_దత్తాంశం_2 | pin_cntrl ) );
	తిరిగి ;
}

/** @fn void configure_rgb_ledx(unsigned char led_no)
 * @brief Configures Individual RGB LED pins as output.
 * @details 8 GPIO pins are mapped to 2 RGB LEDs. This function configures
 *          each LED as output pin.
 * @param unsigned char (led_no - RGB LED that needs to be configured.)
 */
శూన్య configure_rgb_ledx(గుర్తులేని అక్షరం led_no)
{
	గుర్తులేని దీర్ఘ read_దత్తాంశం_2 = 0;
	read_దత్తాంశం_2 = read_మాట(GPIO_DIRECTION_CNTRL_REG);
  ఒకవేళ (0 == led_no)
    write_మాట(GPIO_DIRECTION_CNTRL_REG, ( read_దత్తాంశం_2 | RGB0 ) );
  లేకపోతే ఒకవేళ (1 == led_no)
    write_మాట(GPIO_DIRECTION_CNTRL_REG, ( read_దత్తాంశం_2 | RGB1  ) );
  లేకపోతే
    రాయి("\nInvalid LED No. Permissable values [0,1]");
	తిరిగి ;
}

/*
 * @fn void configure_normal_leds()
 * @brief Configures Normal LEDs 3 & 4 as as output.
 * @details This function configures GPIO pins mapped to 
 *          Normal LEDs as output pins.
 */
శూన్య configure_సాధారణ_leds()
{
	గుర్తులేని దీర్ఘ read_దత్తాంశం_2 = 0;
	read_దత్తాంశం_2 = read_మాట(GPIO_DIRECTION_CNTRL_REG);
  	write_మాట(GPIO_DIRECTION_CNTRL_REG, ( read_దత్తాంశం_2 | సాధారణ_LEDS ) ) ;
	తిరిగి ;
}

/*
 * @fn void configure_rgb_leds()
 * @brief Configures RGB LEDs 0 & 1 as as output pins.
 * @details 8 GPIO pins are mapped to 2 normal LEDs. This function configures
 *          gpio pins mapped to both RGB LEDs as output pins.
 */
శూన్య configure_rgb_leds()
{
	గుర్తులేని దీర్ఘ read_దత్తాంశం_2 = 0;
	read_దత్తాంశం_2 = read_మాట(GPIO_DIRECTION_CNTRL_REG);
  	write_మాట(GPIO_DIRECTION_CNTRL_REG, ( read_దత్తాంశం_2 | ( RGB_LEDS ) ) );
	తిరిగి ;
}

/** @fn void configure_all_leds()
 * @brief Configures GPIO pins mapped to all LEDs as as output pins.
 * @details 8 GPIO pins are mapped to 2 normal LEDs. This function configures
 *          all GPIO pins mapped to all the LEDs as output pins.
 */
శూన్య configure_all_leds()
{
	గుర్తులేని దీర్ఘ read_దత్తాంశం_2 = 0;
	read_దత్తాంశం_2 = read_మాట(GPIO_DIRECTION_CNTRL_REG);
  	write_మాట(GPIO_DIRECTION_CNTRL_REG, ( read_దత్తాంశం_2 | ALL_LEDS ) );
	తిరిగి ;
}

/** @fn static void turn_on_ledx()
 * @brief turn ON the Individual LEDs.
 * @details This function switches ON the LED based on
 *          the GPIO pin position passed.
 * @param pin_cntrl - GPIO Pin position of the LED that needs to be switched ON.
 */
శూన్య turn_on_ledx(గుర్తులేని దీర్ఘ pin_cntrl)
{
	గుర్తులేని దీర్ఘ read_దత్తాంశం_2 = 0;
	read_దత్తాంశం_2 = read_మాట(GPIO_దత్తాంశం_REG);
	write_మాట(GPIO_దత్తాంశం_REG, ( read_దత్తాంశం_2 | pin_cntrl ) );
	తిరిగి ;
}

 /** @fn void turn_off_ledx(unsigned long pin_cntrl)
 * @brief turn OFF the Individual LEDs.
 * @details This function switches OFF the LED based on
 *          the GPIO pin position passed.
 * @param pin_cntrl - GPIO Pin position of the LED that needs to be switched OFF.
 */
శూన్య turn_off_ledx(గుర్తులేని దీర్ఘ pin_cntrl)
{
	గుర్తులేని దీర్ఘ read_దత్తాంశం_2 = 0;
	read_దత్తాంశం_2 = read_మాట(GPIO_దత్తాంశం_REG);
	write_మాట(GPIO_దత్తాంశం_REG, ( read_దత్తాంశం_2 & (~pin_cntrl) )   );
	తిరిగి ;
}

/** @fn  void turn_on_normal_leds()
 * @brief turn ON the all Normal LEDs.
 * @details This function switches ON the Normal LEDs
 */
శూన్య turn_on_సాధారణ_leds()
{
	గుర్తులేని దీర్ఘ read_దత్తాంశం_2 = 0;
	read_దత్తాంశం_2 = read_మాట(GPIO_దత్తాంశం_REG);
 	write_మాట(GPIO_దత్తాంశం_REG, ( read_దత్తాంశం_2 | సాధారణ_LEDS ) );
	తిరిగి ;
}

/** @fn void turn_off_normal_leds()
 * @brief turn OFF the all Normal LEDs.
 * @details This function switches ON both RGB LED.
 */
శూన్య turn_off_సాధారణ_leds()
{
	గుర్తులేని దీర్ఘ read_దత్తాంశం_2 = 0;
	read_దత్తాంశం_2 = read_మాట(GPIO_దత్తాంశం_REG);
	write_మాట(GPIO_దత్తాంశం_REG, ( read_దత్తాంశం_2 & (~సాధారణ_LEDS) ) );
	తిరిగి ;
}

/** @fn void turn_on_rgb_ledx(unsigned char led_no)
 * @brief turn ON the Individual RGB LED.
 * @details 8 GPIO pins are mapped to 2 RGB LEDs. This function switches
 *          on passed RGB LED.
 * @param unsigned char (RGB LED that needs to be switched On[0,1].)
 */
శూన్య turn_on_rgb_ledx(గుర్తులేని అక్షరం led_no)
{
	గుర్తులేని దీర్ఘ read_దత్తాంశం_2 = 0;
	read_దత్తాంశం_2 = read_మాట(GPIO_దత్తాంశం_REG);
  ఒకవేళ (0 == led_no)
    write_మాట(GPIO_దత్తాంశం_REG, ( read_దత్తాంశం_2 | RGB0 ) );
  లేకపోతే ఒకవేళ (1 == led_no)
    write_మాట(GPIO_దత్తాంశం_REG, ( read_దత్తాంశం_2 | RGB1 ) );
  లేకపోతే
    రాయి("\n RGB Led number is not valid [0,1]");
	తిరిగి ;
}

/** @fn void turn_off_rgb_ledx(unsigned char led_no)
 * @brief turn OFF the Individual RGB LED.
 * @details 8 GPIO pins are mapped to 2 RGB LEDs. This function switches
 *          OFF passed RGB LED.
 * @param unsigned char (RGB LED that needs to be switched OFF[0,1].)
 */
శూన్య turn_off_rgb_ledx(గుర్తులేని అక్షరం led_no)
{
	గుర్తులేని దీర్ఘ read_దత్తాంశం_2 = 0;
	read_దత్తాంశం_2 = read_మాట(GPIO_దత్తాంశం_REG);
  ఒకవేళ (0 == led_no)
	 write_మాట(GPIO_దత్తాంశం_REG, ( read_దత్తాంశం_2 & (~RGB0) ) );
  లేకపోతే ఒకవేళ (1 == led_no)
 	  write_మాట(GPIO_దత్తాంశం_REG, ( read_దత్తాంశం_2 & (~RGB1) ) );
  లేకపోతే
    రాయి("\n RGB Led number is not valid [0,1]");
	తిరిగి ;
}

/** @fn void turn_on_rgb_leds()
 * @brief turn ON the all RGB LEDs.
 * @details 8 GPIO pins are mapped to 2 RGB LEDs. This function switches
 *          ON both RGB LED.
 */
శూన్య turn_on_rgb_leds()
{
	గుర్తులేని దీర్ఘ read_దత్తాంశం_2 = 0;
	read_దత్తాంశం_2 = read_మాట(GPIO_దత్తాంశం_REG);
    write_మాట(GPIO_దత్తాంశం_REG, ( read_దత్తాంశం_2 | RGB_LEDS ) );
	తిరిగి ;
}

/** @fn void turn_off_rgb_leds()
 * @brief turn ON the all RGB LEDs.
 * @details This function switches ON both RGB LED.
 */
శూన్య turn_off_rgb_leds()
{
	గుర్తులేని దీర్ఘ read_దత్తాంశం_2 = 0;
	read_దత్తాంశం_2 = read_మాట(GPIO_దత్తాంశం_REG);
 	write_మాట(GPIO_దత్తాంశం_REG, ( read_దత్తాంశం_2 & (~RGB_LEDS) ) );
	తిరిగి ;
}

/** @fn void turn_on_all_leds()
 * @brief turn ON the all LEDs.
 * @details This function switches ON all LEDs.
 */
శూన్య turn_on_all_leds()
{
	గుర్తులేని దీర్ఘ read_దత్తాంశం_2 = 0;
	read_దత్తాంశం_2 = read_మాట(GPIO_దత్తాంశం_REG);
	write_మాట(GPIO_దత్తాంశం_REG, ( read_దత్తాంశం_2 | ALL_LEDS ) );
	తిరిగి ;
}

/** @fn void turn_off_all_leds()
 * @brief turn OFF the all LEDs.
 * @details This function switches OFF all LEDs.
 */
శూన్య turn_off_all_leds()
{
	గుర్తులేని దీర్ఘ read_దత్తాంశం_2 = 0;
	read_దత్తాంశం_2 = read_మాట(GPIO_దత్తాంశం_REG);
  write_మాట(GPIO_దత్తాంశం_REG, ( read_దత్తాంశం_2 & (~ALL_LEDS) ) );
	తిరిగి ;
}

 /** @fn void toggle_ledx(unsigned long pin_cntrl, unsigned long delay1, unsigned long delay2)
 * @brief Toggles the passed LED.
 * @details This function toggles given LED.
 * @param unsigned long pin_cntrl
 * @param unsigned long delay1
 * @param unsigned long delay2(Led that needs to be toggled, delay.)
 */
శూన్య toggle_ledx(గుర్తులేని దీర్ఘ pin_cntrl, గుర్తులేని దీర్ఘ delay1, గుర్తులేని దీర్ఘ delay2)
{
	గుర్తులేని దీర్ఘ read_దత్తాంశం_2 = 0;
	read_దత్తాంశం_2 = read_మాట(GPIO_దత్తాంశం_REG);
	write_మాట (GPIO_దత్తాంశం_REG, ( read_దత్తాంశం_2 | (pin_cntrl ) ) );
	delay_loop(delay1, delay2);
	write_మాట(GPIO_దత్తాంశం_REG, ( read_దత్తాంశం_2 & (~pin_cntrl) ) );
	delay_loop(delay1, delay2);
	తిరిగి ;
}

 /** @fn void toggle_normal_leds( unsigned long delay1, unsigned long delay2 )
 * @brief toggles normal LEDs.
 * @details This function toggles given both the 
 *          normal LEDs.
 * @param unsigned long delay1
 * @param unsigned long delay2
 */
శూన్య toggle_సాధారణ_leds( గుర్తులేని దీర్ఘ delay1, గుర్తులేని దీర్ఘ delay2 )
{
	గుర్తులేని దీర్ఘ read_దత్తాంశం_2 = 0;
	read_దత్తాంశం_2 = read_మాట(GPIO_దత్తాంశం_REG);
	write_మాట(GPIO_దత్తాంశం_REG, ( read_దత్తాంశం_2 | సాధారణ_LEDS ) );
	delay_loop(delay1, delay2);
 	write_మాట(GPIO_దత్తాంశం_REG, ( read_దత్తాంశం_2 & (~సాధారణ_LEDS) ) );
	delay_loop(delay1, delay2);
	తిరిగి ;
}

/** @fn void toggle_rgb_leds( unsigned long delay1, unsigned long delay2 )
 * @brief Toggles RGB LED.
 * @details This function toggles the RGB LEDs.
 * @param unsigned long delay1
 * @param unsigned long delay2
 */
శూన్య toggle_rgb_leds( గుర్తులేని దీర్ఘ delay1, గుర్తులేని దీర్ఘ delay2 )
{
	గుర్తులేని దీర్ఘ read_దత్తాంశం_2 = 0;
	read_దత్తాంశం_2 = read_మాట(GPIO_దత్తాంశం_REG);
	write_మాట(GPIO_దత్తాంశం_REG, ( read_దత్తాంశం_2 | RGB_LEDS ) );
	delay_loop(delay1, delay2);
 	write_మాట(GPIO_దత్తాంశం_REG, ( read_దత్తాంశం_2 & (~RGB_LEDS) ) );
	delay_loop(delay1, delay2);
	తిరిగి ;
}

/** @fn void toggle_all_leds( unsigned long delay1, unsigned long delay2)
 * @brief Toggles All LEDs.
 * @details This function toggles  all the LEDs with a delay.
 * @param unsigned long delay1
 * @param unsigned long delay2
 */
శూన్య toggle_all_leds( గుర్తులేని దీర్ఘ delay1, గుర్తులేని దీర్ఘ delay2)
{
	గుర్తులేని దీర్ఘ read_దత్తాంశం_2 = 0;
	read_దత్తాంశం_2 = read_మాట(GPIO_దత్తాంశం_REG);
	write_మాట(GPIO_దత్తాంశం_REG, ( read_దత్తాంశం_2 | ALL_LEDS ) );
	delay_loop(delay1, delay2);
	write_మాట(GPIO_దత్తాంశం_REG, ( read_దత్తాంశం_2 & (~ALL_LEDS) ) );
	delay_loop(delay1, delay2);
	తిరిగి ;
}
#అయితే_ముగింపు
