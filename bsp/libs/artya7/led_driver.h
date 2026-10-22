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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ LED_DRIVER_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LED_DRIVER_H

#ਅਨ੍ਤਰ੍ਭਾਵ "platform.h" //Contains arty a7 gpio definitions.
#ਅਨ੍ਤਰ੍ਭਾਵ "gpio.h"  //Contains the methods to Access GPIOs

#ਜੇ defined(ARTIX7_35T) || defined(ARTIX7_100T)
/*! RGB LED 0 defines */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LED0_R GPIO16 
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LED0_G GPIO17
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LED0_B GPIO18

/*! RGB LED 1 defines */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LED1_R GPIO19
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LED1_G GPIO20
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LED1_B GPIO21

/*! Normal LED 1 defines */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LED2 GPIO22

/*! Normal LED 2 defines */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LED3 GPIO23


/*! Combined RGB LED defines */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB0 (LED0_R | LED0_G | LED0_B )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB1 (LED1_R | LED1_G | LED1_B )

/*! Combined Normal LED defines */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸਾਧਾਰਨ_LEDS ( LED2 | LED3 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB_LEDS ( RGB0 | RGB1 )

/*! Combines ALL LED defines */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALL_LEDS (RGB_LEDS | ਸਾਧਾਰਨ_LEDS)


/*! Control for all LEDS */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸਾਧਾਰਨ_LED0 0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸਾਧਾਰਨ_LED1 1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB_LED0 0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB_LED1 1

// function prototype
ਖਾਲੀ configure_ledx(ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ pin_cntrl);
ਖਾਲੀ configure_rgb_ledx(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ led_no);
ਖਾਲੀ configure_ਸਾਧਾਰਨ_leds();
ਖਾਲੀ configure_rgb_leds();
ਖਾਲੀ configure_all_leds();
ਖਾਲੀ turn_on_ledx(ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ pin_cntrl);
ਖਾਲੀ turn_off_ledx(ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ pin_cntrl);
ਖਾਲੀ turn_on_ਸਾਧਾਰਨ_leds();
ਖਾਲੀ turn_off_ਸਾਧਾਰਨ_leds();
ਖਾਲੀ turn_on_rgb_ledx(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ led_no);
ਖਾਲੀ turn_off_rgb_ledx(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ led_no);
ਖਾਲੀ turn_on_rgb_leds();
ਖਾਲੀ turn_off_rgb_leds();
ਖਾਲੀ turn_on_all_leds();
ਖਾਲੀ turn_off_all_leds();
ਖਾਲੀ toggle_ledx(ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ pin_cntrl, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ delay1, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ delay2);
ਖਾਲੀ toggle_ਸਾਧਾਰਨ_leds( ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ delay1, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ delay2 );
ਖਾਲੀ toggle_rgb_leds( ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ delay1, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ delay2 );
ਖਾਲੀ toggle_all_leds( ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ delay1, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ delay2);


#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ
