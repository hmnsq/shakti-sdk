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

#अगर defined(ARTIX7_35T) || defined(ARTIX7_100T)

#समावेश "platform.h"
#समावेश "gpio.h"
#समावेश "led_driver.h"
#समावेश "utils.h"

 /** @fn void configure_ledx(unsigned long pin_cntrl)
 * @brief Configures Individual LED pins as output.
 * @details 8 GPIO pins are mapped to 8 LEDs. This function configures
 *          each LED as output pin.
 * @param unsigned long (pin_cntrl- Pin that needs to be configured as LED.)
 */
व्योम configure_ledx(अचिन्हित दीर्घ pin_cntrl)
{
	अचिन्हित दीर्घ read_तथ्य_2 = 0;
	read_तथ्य_2 = read_word(GPIO_DIRECTION_CNTRL_REG);
	write_word(GPIO_DIRECTION_CNTRL_REG, ( read_तथ्य_2 | pin_cntrl ) );
	वापस ;
}

/** @fn void configure_rgb_ledx(unsigned char led_no)
 * @brief Configures Individual RGB LED pins as output.
 * @details 8 GPIO pins are mapped to 2 RGB LEDs. This function configures
 *          each LED as output pin.
 * @param unsigned char (led_no - RGB LED that needs to be configured.)
 */
व्योम configure_rgb_ledx(अचिन्हित अक्षर led_no)
{
	अचिन्हित दीर्घ read_तथ्य_2 = 0;
	read_तथ्य_2 = read_word(GPIO_DIRECTION_CNTRL_REG);
  अगर (0 == led_no)
    write_word(GPIO_DIRECTION_CNTRL_REG, ( read_तथ्य_2 | RGB0 ) );
  अन्यथा अगर (1 == led_no)
    write_word(GPIO_DIRECTION_CNTRL_REG, ( read_तथ्य_2 | RGB1  ) );
  अन्यथा
    म_लिखो("\nInvalid LED No. Permissable values [0,1]");
	वापस ;
}

/*
 * @fn void configure_normal_leds()
 * @brief Configures Normal LEDs 3 & 4 as as output.
 * @details This function configures GPIO pins mapped to 
 *          Normal LEDs as output pins.
 */
व्योम configure_normal_leds()
{
	अचिन्हित दीर्घ read_तथ्य_2 = 0;
	read_तथ्य_2 = read_word(GPIO_DIRECTION_CNTRL_REG);
  	write_word(GPIO_DIRECTION_CNTRL_REG, ( read_तथ्य_2 | NORMAL_LEDS ) ) ;
	वापस ;
}

/*
 * @fn void configure_rgb_leds()
 * @brief Configures RGB LEDs 0 & 1 as as output pins.
 * @details 8 GPIO pins are mapped to 2 normal LEDs. This function configures
 *          gpio pins mapped to both RGB LEDs as output pins.
 */
व्योम configure_rgb_leds()
{
	अचिन्हित दीर्घ read_तथ्य_2 = 0;
	read_तथ्य_2 = read_word(GPIO_DIRECTION_CNTRL_REG);
  	write_word(GPIO_DIRECTION_CNTRL_REG, ( read_तथ्य_2 | ( RGB_LEDS ) ) );
	वापस ;
}

/** @fn void configure_all_leds()
 * @brief Configures GPIO pins mapped to all LEDs as as output pins.
 * @details 8 GPIO pins are mapped to 2 normal LEDs. This function configures
 *          all GPIO pins mapped to all the LEDs as output pins.
 */
व्योम configure_all_leds()
{
	अचिन्हित दीर्घ read_तथ्य_2 = 0;
	read_तथ्य_2 = read_word(GPIO_DIRECTION_CNTRL_REG);
  	write_word(GPIO_DIRECTION_CNTRL_REG, ( read_तथ्य_2 | ALL_LEDS ) );
	वापस ;
}

/** @fn static void turn_on_ledx()
 * @brief turn ON the Individual LEDs.
 * @details This function switches ON the LED based on
 *          the GPIO pin position passed.
 * @param pin_cntrl - GPIO Pin position of the LED that needs to be switched ON.
 */
व्योम turn_on_ledx(अचिन्हित दीर्घ pin_cntrl)
{
	अचिन्हित दीर्घ read_तथ्य_2 = 0;
	read_तथ्य_2 = read_word(GPIO_तथ्य_REG);
	write_word(GPIO_तथ्य_REG, ( read_तथ्य_2 | pin_cntrl ) );
	वापस ;
}

 /** @fn void turn_off_ledx(unsigned long pin_cntrl)
 * @brief turn OFF the Individual LEDs.
 * @details This function switches OFF the LED based on
 *          the GPIO pin position passed.
 * @param pin_cntrl - GPIO Pin position of the LED that needs to be switched OFF.
 */
व्योम turn_off_ledx(अचिन्हित दीर्घ pin_cntrl)
{
	अचिन्हित दीर्घ read_तथ्य_2 = 0;
	read_तथ्य_2 = read_word(GPIO_तथ्य_REG);
	write_word(GPIO_तथ्य_REG, ( read_तथ्य_2 & (~pin_cntrl) )   );
	वापस ;
}

/** @fn  void turn_on_normal_leds()
 * @brief turn ON the all Normal LEDs.
 * @details This function switches ON the Normal LEDs
 */
व्योम turn_on_normal_leds()
{
	अचिन्हित दीर्घ read_तथ्य_2 = 0;
	read_तथ्य_2 = read_word(GPIO_तथ्य_REG);
 	write_word(GPIO_तथ्य_REG, ( read_तथ्य_2 | NORMAL_LEDS ) );
	वापस ;
}

/** @fn void turn_off_normal_leds()
 * @brief turn OFF the all Normal LEDs.
 * @details This function switches ON both RGB LED.
 */
व्योम turn_off_normal_leds()
{
	अचिन्हित दीर्घ read_तथ्य_2 = 0;
	read_तथ्य_2 = read_word(GPIO_तथ्य_REG);
	write_word(GPIO_तथ्य_REG, ( read_तथ्य_2 & (~NORMAL_LEDS) ) );
	वापस ;
}

/** @fn void turn_on_rgb_ledx(unsigned char led_no)
 * @brief turn ON the Individual RGB LED.
 * @details 8 GPIO pins are mapped to 2 RGB LEDs. This function switches
 *          on passed RGB LED.
 * @param unsigned char (RGB LED that needs to be switched On[0,1].)
 */
व्योम turn_on_rgb_ledx(अचिन्हित अक्षर led_no)
{
	अचिन्हित दीर्घ read_तथ्य_2 = 0;
	read_तथ्य_2 = read_word(GPIO_तथ्य_REG);
  अगर (0 == led_no)
    write_word(GPIO_तथ्य_REG, ( read_तथ्य_2 | RGB0 ) );
  अन्यथा अगर (1 == led_no)
    write_word(GPIO_तथ्य_REG, ( read_तथ्य_2 | RGB1 ) );
  अन्यथा
    म_लिखो("\n RGB Led number is not valid [0,1]");
	वापस ;
}

/** @fn void turn_off_rgb_ledx(unsigned char led_no)
 * @brief turn OFF the Individual RGB LED.
 * @details 8 GPIO pins are mapped to 2 RGB LEDs. This function switches
 *          OFF passed RGB LED.
 * @param unsigned char (RGB LED that needs to be switched OFF[0,1].)
 */
व्योम turn_off_rgb_ledx(अचिन्हित अक्षर led_no)
{
	अचिन्हित दीर्घ read_तथ्य_2 = 0;
	read_तथ्य_2 = read_word(GPIO_तथ्य_REG);
  अगर (0 == led_no)
	 write_word(GPIO_तथ्य_REG, ( read_तथ्य_2 & (~RGB0) ) );
  अन्यथा अगर (1 == led_no)
 	  write_word(GPIO_तथ्य_REG, ( read_तथ्य_2 & (~RGB1) ) );
  अन्यथा
    म_लिखो("\n RGB Led number is not valid [0,1]");
	वापस ;
}

/** @fn void turn_on_rgb_leds()
 * @brief turn ON the all RGB LEDs.
 * @details 8 GPIO pins are mapped to 2 RGB LEDs. This function switches
 *          ON both RGB LED.
 */
व्योम turn_on_rgb_leds()
{
	अचिन्हित दीर्घ read_तथ्य_2 = 0;
	read_तथ्य_2 = read_word(GPIO_तथ्य_REG);
    write_word(GPIO_तथ्य_REG, ( read_तथ्य_2 | RGB_LEDS ) );
	वापस ;
}

/** @fn void turn_off_rgb_leds()
 * @brief turn ON the all RGB LEDs.
 * @details This function switches ON both RGB LED.
 */
व्योम turn_off_rgb_leds()
{
	अचिन्हित दीर्घ read_तथ्य_2 = 0;
	read_तथ्य_2 = read_word(GPIO_तथ्य_REG);
 	write_word(GPIO_तथ्य_REG, ( read_तथ्य_2 & (~RGB_LEDS) ) );
	वापस ;
}

/** @fn void turn_on_all_leds()
 * @brief turn ON the all LEDs.
 * @details This function switches ON all LEDs.
 */
व्योम turn_on_all_leds()
{
	अचिन्हित दीर्घ read_तथ्य_2 = 0;
	read_तथ्य_2 = read_word(GPIO_तथ्य_REG);
	write_word(GPIO_तथ्य_REG, ( read_तथ्य_2 | ALL_LEDS ) );
	वापस ;
}

/** @fn void turn_off_all_leds()
 * @brief turn OFF the all LEDs.
 * @details This function switches OFF all LEDs.
 */
व्योम turn_off_all_leds()
{
	अचिन्हित दीर्घ read_तथ्य_2 = 0;
	read_तथ्य_2 = read_word(GPIO_तथ्य_REG);
  write_word(GPIO_तथ्य_REG, ( read_तथ्य_2 & (~ALL_LEDS) ) );
	वापस ;
}

 /** @fn void toggle_ledx(unsigned long pin_cntrl, unsigned long delay1, unsigned long delay2)
 * @brief Toggles the passed LED.
 * @details This function toggles given LED.
 * @param unsigned long pin_cntrl
 * @param unsigned long delay1
 * @param unsigned long delay2(Led that needs to be toggled, delay.)
 */
व्योम toggle_ledx(अचिन्हित दीर्घ pin_cntrl, अचिन्हित दीर्घ delay1, अचिन्हित दीर्घ delay2)
{
	अचिन्हित दीर्घ read_तथ्य_2 = 0;
	read_तथ्य_2 = read_word(GPIO_तथ्य_REG);
	write_word (GPIO_तथ्य_REG, ( read_तथ्य_2 | (pin_cntrl ) ) );
	delay_loop(delay1, delay2);
	write_word(GPIO_तथ्य_REG, ( read_तथ्य_2 & (~pin_cntrl) ) );
	delay_loop(delay1, delay2);
	वापस ;
}

 /** @fn void toggle_normal_leds( unsigned long delay1, unsigned long delay2 )
 * @brief toggles normal LEDs.
 * @details This function toggles given both the 
 *          normal LEDs.
 * @param unsigned long delay1
 * @param unsigned long delay2
 */
व्योम toggle_normal_leds( अचिन्हित दीर्घ delay1, अचिन्हित दीर्घ delay2 )
{
	अचिन्हित दीर्घ read_तथ्य_2 = 0;
	read_तथ्य_2 = read_word(GPIO_तथ्य_REG);
	write_word(GPIO_तथ्य_REG, ( read_तथ्य_2 | NORMAL_LEDS ) );
	delay_loop(delay1, delay2);
 	write_word(GPIO_तथ्य_REG, ( read_तथ्य_2 & (~NORMAL_LEDS) ) );
	delay_loop(delay1, delay2);
	वापस ;
}

/** @fn void toggle_rgb_leds( unsigned long delay1, unsigned long delay2 )
 * @brief Toggles RGB LED.
 * @details This function toggles the RGB LEDs.
 * @param unsigned long delay1
 * @param unsigned long delay2
 */
व्योम toggle_rgb_leds( अचिन्हित दीर्घ delay1, अचिन्हित दीर्घ delay2 )
{
	अचिन्हित दीर्घ read_तथ्य_2 = 0;
	read_तथ्य_2 = read_word(GPIO_तथ्य_REG);
	write_word(GPIO_तथ्य_REG, ( read_तथ्य_2 | RGB_LEDS ) );
	delay_loop(delay1, delay2);
 	write_word(GPIO_तथ्य_REG, ( read_तथ्य_2 & (~RGB_LEDS) ) );
	delay_loop(delay1, delay2);
	वापस ;
}

/** @fn void toggle_all_leds( unsigned long delay1, unsigned long delay2)
 * @brief Toggles All LEDs.
 * @details This function toggles  all the LEDs with a delay.
 * @param unsigned long delay1
 * @param unsigned long delay2
 */
व्योम toggle_all_leds( अचिन्हित दीर्घ delay1, अचिन्हित दीर्घ delay2)
{
	अचिन्हित दीर्घ read_तथ्य_2 = 0;
	read_तथ्य_2 = read_word(GPIO_तथ्य_REG);
	write_word(GPIO_तथ्य_REG, ( read_तथ्य_2 | ALL_LEDS ) );
	delay_loop(delay1, delay2);
	write_word(GPIO_तथ्य_REG, ( read_तथ्य_2 & (~ALL_LEDS) ) );
	delay_loop(delay1, delay2);
	वापस ;
}
#पूर्ण_अगर
