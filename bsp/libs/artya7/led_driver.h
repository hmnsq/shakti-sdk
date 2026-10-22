/***************************************************************************
 * Project           		    : shakti devt board
 * Name of the file	            : led_driver.h
 * Brief Description of file        : Header file for leds
 * Name of Author    	            : Kotteeswaran
 * Email ID                         : kottee.1@gmail.com

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
 * @file led_driver.h
 * @brief  All the definitions are very specific to ARTY A7 (35T & 100T) boards
 */

#که_نه_تعریف_شوی LED_DRIVER_H
#تعریف_کړه LED_DRIVER_H

#ضمن "platform.h" //Contains arty a7 gpio definitions.
#ضمن "gpio.h"  //Contains the methods to Access GPIOs

#إذا defined(ARTIX7_35T) || defined(ARTIX7_100T)
/*! RGB LED 0 defines */
#تعریف_کړه LED0_R GPIO16 
#تعریف_کړه LED0_G GPIO17
#تعریف_کړه LED0_B GPIO18

/*! RGB LED 1 defines */
#تعریف_کړه LED1_R GPIO19
#تعریف_کړه LED1_G GPIO20
#تعریف_کړه LED1_B GPIO21

/*! Normal LED 1 defines */
#تعریف_کړه LED2 GPIO22

/*! Normal LED 2 defines */
#تعریف_کړه LED3 GPIO23


/*! Combined RGB LED defines */
#تعریف_کړه RGB0 (LED0_R | LED0_G | LED0_B )
#تعریف_کړه RGB1 (LED1_R | LED1_G | LED1_B )

/*! Combined Normal LED defines */
#تعریف_کړه نورمال_LEDS ( LED2 | LED3 )
#تعریف_کړه RGB_LEDS ( RGB0 | RGB1 )

/*! Combines ALL LED defines */
#تعریف_کړه ALL_LEDS (RGB_LEDS | نورمال_LEDS)


/*! Control for all LEDS */
#تعریف_کړه نورمال_LED0 0
#تعریف_کړه نورمال_LED1 1

#تعریف_کړه RGB_LED0 0
#تعریف_کړه RGB_LED1 1

// function prototype
فراغ configure_ledx(بینښه اوږد pin_cntrl);
فراغ configure_rgb_ledx(بینښه حرف led_no);
فراغ configure_نورمال_leds();
فراغ configure_rgb_leds();
فراغ configure_all_leds();
فراغ turn_on_ledx(بینښه اوږد pin_cntrl);
فراغ turn_off_ledx(بینښه اوږد pin_cntrl);
فراغ turn_on_نورمال_leds();
فراغ turn_off_نورمال_leds();
فراغ turn_on_rgb_ledx(بینښه حرف led_no);
فراغ turn_off_rgb_ledx(بینښه حرف led_no);
فراغ turn_on_rgb_leds();
فراغ turn_off_rgb_leds();
فراغ turn_on_all_leds();
فراغ turn_off_all_leds();
فراغ toggle_ledx(بینښه اوږد pin_cntrl, بینښه اوږد delay1, بینښه اوږد delay2);
فراغ toggle_نورمال_leds( بینښه اوږد delay1, بینښه اوږد delay2 );
فراغ toggle_rgb_leds( بینښه اوږد delay1, بینښه اوږد delay2 );
فراغ toggle_all_leds( بینښه اوږد delay1, بینښه اوږد delay2);


#د_که_پای
#د_که_پای
