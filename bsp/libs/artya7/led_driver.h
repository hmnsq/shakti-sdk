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

#جيڪڏهن_وصف_نه_ٿيل LED_DRIVER_H
#وصف_ڪريو LED_DRIVER_H

#ضمن "platform.h" //Contains arty a7 gpio definitions.
#ضمن "gpio.h"  //Contains the methods to Access GPIOs

#إذا defined(ARTIX7_35T) || defined(ARTIX7_100T)
/*! RGB LED 0 defines */
#وصف_ڪريو LED0_R GPIO16 
#وصف_ڪريو LED0_G GPIO17
#وصف_ڪريو LED0_B GPIO18

/*! RGB LED 1 defines */
#وصف_ڪريو LED1_R GPIO19
#وصف_ڪريو LED1_G GPIO20
#وصف_ڪريو LED1_B GPIO21

/*! Normal LED 1 defines */
#وصف_ڪريو LED2 GPIO22

/*! Normal LED 2 defines */
#وصف_ڪريو LED3 GPIO23


/*! Combined RGB LED defines */
#وصف_ڪريو RGB0 (LED0_R | LED0_G | LED0_B )
#وصف_ڪريو RGB1 (LED1_R | LED1_G | LED1_B )

/*! Combined Normal LED defines */
#وصف_ڪريو عام_LEDS ( LED2 | LED3 )
#وصف_ڪريو RGB_LEDS ( RGB0 | RGB1 )

/*! Combines ALL LED defines */
#وصف_ڪريو ALL_LEDS (RGB_LEDS | عام_LEDS)


/*! Control for all LEDS */
#وصف_ڪريو عام_LED0 0
#وصف_ڪريو عام_LED1 1

#وصف_ڪريو RGB_LED0 0
#وصف_ڪريو RGB_LED1 1

// function prototype
فراغ configure_ledx(بنانشان ڊگهو pin_cntrl);
فراغ configure_rgb_ledx(بنانشان حرف led_no);
فراغ configure_عام_leds();
فراغ configure_rgb_leds();
فراغ configure_all_leds();
فراغ turn_on_ledx(بنانشان ڊگهو pin_cntrl);
فراغ turn_off_ledx(بنانشان ڊگهو pin_cntrl);
فراغ turn_on_عام_leds();
فراغ turn_off_عام_leds();
فراغ turn_on_rgb_ledx(بنانشان حرف led_no);
فراغ turn_off_rgb_ledx(بنانشان حرف led_no);
فراغ turn_on_rgb_leds();
فراغ turn_off_rgb_leds();
فراغ turn_on_all_leds();
فراغ turn_off_all_leds();
فراغ toggle_ledx(بنانشان ڊگهو pin_cntrl, بنانشان ڊگهو delay1, بنانشان ڊگهو delay2);
فراغ toggle_عام_leds( بنانشان ڊگهو delay1, بنانشان ڊگهو delay2 );
فراغ toggle_rgb_leds( بنانشان ڊگهو delay1, بنانشان ڊگهو delay2 );
فراغ toggle_all_leds( بنانشان ڊگهو delay1, بنانشان ڊگهو delay2);


#جيڪڏهن_پورو
#جيڪڏهن_پورو
