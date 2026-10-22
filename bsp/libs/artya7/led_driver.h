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

#यदि_अपरिभाषितम् LED_DRIVER_H
#परिभाषय LED_DRIVER_H

#अन्तर्भाव "platform.h" //Contains arty a7 gpio definitions.
#अन्तर्भाव "gpio.h"  //Contains the methods to Access GPIOs

#यदि defined(ARTIX7_35T) || defined(ARTIX7_100T)
/*! RGB LED 0 defines */
#परिभाषय LED0_R GPIO16 
#परिभाषय LED0_G GPIO17
#परिभाषय LED0_B GPIO18

/*! RGB LED 1 defines */
#परिभाषय LED1_R GPIO19
#परिभाषय LED1_G GPIO20
#परिभाषय LED1_B GPIO21

/*! Normal LED 1 defines */
#परिभाषय LED2 GPIO22

/*! Normal LED 2 defines */
#परिभाषय LED3 GPIO23


/*! Combined RGB LED defines */
#परिभाषय RGB0 (LED0_R | LED0_G | LED0_B )
#परिभाषय RGB1 (LED1_R | LED1_G | LED1_B )

/*! Combined Normal LED defines */
#परिभाषय प्रसामान्यम्_LEDS ( LED2 | LED3 )
#परिभाषय RGB_LEDS ( RGB0 | RGB1 )

/*! Combines ALL LED defines */
#परिभाषय ALL_LEDS (RGB_LEDS | प्रसामान्यम्_LEDS)


/*! Control for all LEDS */
#परिभाषय प्रसामान्यम्_LED0 0
#परिभाषय प्रसामान्यम्_LED1 1

#परिभाषय RGB_LED0 0
#परिभाषय RGB_LED1 1

// function prototype
शून्य configure_ledx(अचिह्नित दीर्घ pin_cntrl);
शून्य configure_rgb_ledx(अचिह्नित वर्ण led_no);
शून्य configure_प्रसामान्यम्_leds();
शून्य configure_rgb_leds();
शून्य configure_all_leds();
शून्य turn_on_ledx(अचिह्नित दीर्घ pin_cntrl);
शून्य turn_off_ledx(अचिह्नित दीर्घ pin_cntrl);
शून्य turn_on_प्रसामान्यम्_leds();
शून्य turn_off_प्रसामान्यम्_leds();
शून्य turn_on_rgb_ledx(अचिह्नित वर्ण led_no);
शून्य turn_off_rgb_ledx(अचिह्नित वर्ण led_no);
शून्य turn_on_rgb_leds();
शून्य turn_off_rgb_leds();
शून्य turn_on_all_leds();
शून्य turn_off_all_leds();
शून्य toggle_ledx(अचिह्नित दीर्घ pin_cntrl, अचिह्नित दीर्घ delay1, अचिह्नित दीर्घ delay2);
शून्य toggle_प्रसामान्यम्_leds( अचिह्नित दीर्घ delay1, अचिह्नित दीर्घ delay2 );
शून्य toggle_rgb_leds( अचिह्नित दीर्घ delay1, अचिह्नित दीर्घ delay2 );
शून्य toggle_all_leds( अचिह्नित दीर्घ delay1, अचिह्नित दीर्घ delay2);


#यदि_अन्तः
#यदि_अन्तः
