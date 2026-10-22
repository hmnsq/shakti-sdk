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

#अगर_अघोषित LED_DRIVER_H
#घोषणा LED_DRIVER_H

#समावेश "platform.h" //Contains arty a7 gpio definitions.
#समावेश "gpio.h"  //Contains the methods to Access GPIOs

#अगर defined(ARTIX7_35T) || defined(ARTIX7_100T)
/*! RGB LED 0 defines */
#घोषणा LED0_R GPIO16 
#घोषणा LED0_G GPIO17
#घोषणा LED0_B GPIO18

/*! RGB LED 1 defines */
#घोषणा LED1_R GPIO19
#घोषणा LED1_G GPIO20
#घोषणा LED1_B GPIO21

/*! Normal LED 1 defines */
#घोषणा LED2 GPIO22

/*! Normal LED 2 defines */
#घोषणा LED3 GPIO23


/*! Combined RGB LED defines */
#घोषणा RGB0 (LED0_R | LED0_G | LED0_B )
#घोषणा RGB1 (LED1_R | LED1_G | LED1_B )

/*! Combined Normal LED defines */
#घोषणा NORMAL_LEDS ( LED2 | LED3 )
#घोषणा RGB_LEDS ( RGB0 | RGB1 )

/*! Combines ALL LED defines */
#घोषणा ALL_LEDS (RGB_LEDS | NORMAL_LEDS)


/*! Control for all LEDS */
#घोषणा NORMAL_LED0 0
#घोषणा NORMAL_LED1 1

#घोषणा RGB_LED0 0
#घोषणा RGB_LED1 1

// function prototype
व्योम configure_ledx(अचिन्हित दीर्घ pin_cntrl);
व्योम configure_rgb_ledx(अचिन्हित अक्षर led_no);
व्योम configure_normal_leds();
व्योम configure_rgb_leds();
व्योम configure_all_leds();
व्योम turn_on_ledx(अचिन्हित दीर्घ pin_cntrl);
व्योम turn_off_ledx(अचिन्हित दीर्घ pin_cntrl);
व्योम turn_on_normal_leds();
व्योम turn_off_normal_leds();
व्योम turn_on_rgb_ledx(अचिन्हित अक्षर led_no);
व्योम turn_off_rgb_ledx(अचिन्हित अक्षर led_no);
व्योम turn_on_rgb_leds();
व्योम turn_off_rgb_leds();
व्योम turn_on_all_leds();
व्योम turn_off_all_leds();
व्योम toggle_ledx(अचिन्हित दीर्घ pin_cntrl, अचिन्हित दीर्घ delay1, अचिन्हित दीर्घ delay2);
व्योम toggle_normal_leds( अचिन्हित दीर्घ delay1, अचिन्हित दीर्घ delay2 );
व्योम toggle_rgb_leds( अचिन्हित दीर्घ delay1, अचिन्हित दीर्घ delay2 );
व्योम toggle_all_leds( अचिन्हित दीर्घ delay1, अचिन्हित दीर्घ delay2);


#पूर्ण_अगर
#पूर्ण_अगर
