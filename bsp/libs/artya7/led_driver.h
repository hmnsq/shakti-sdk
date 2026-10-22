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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ LED_DRIVER_H
#ವ್ಯಾಖ್ಯಾನಿಸು LED_DRIVER_H

#ಅನ್ತರ್ಭಾವ "platform.h" //Contains arty a7 gpio definitions.
#ಅನ್ತರ್ಭಾವ "gpio.h"  //Contains the methods to Access GPIOs

#ಆದರೆ defined(ARTIX7_35T) || defined(ARTIX7_100T)
/*! RGB LED 0 defines */
#ವ್ಯಾಖ್ಯಾನಿಸು LED0_R GPIO16 
#ವ್ಯಾಖ್ಯಾನಿಸು LED0_G GPIO17
#ವ್ಯಾಖ್ಯಾನಿಸು LED0_B GPIO18

/*! RGB LED 1 defines */
#ವ್ಯಾಖ್ಯಾನಿಸು LED1_R GPIO19
#ವ್ಯಾಖ್ಯಾನಿಸು LED1_G GPIO20
#ವ್ಯಾಖ್ಯಾನಿಸು LED1_B GPIO21

/*! Normal LED 1 defines */
#ವ್ಯಾಖ್ಯಾನಿಸು LED2 GPIO22

/*! Normal LED 2 defines */
#ವ್ಯಾಖ್ಯಾನಿಸು LED3 GPIO23


/*! Combined RGB LED defines */
#ವ್ಯಾಖ್ಯಾನಿಸು RGB0 (LED0_R | LED0_G | LED0_B )
#ವ್ಯಾಖ್ಯಾನಿಸು RGB1 (LED1_R | LED1_G | LED1_B )

/*! Combined Normal LED defines */
#ವ್ಯಾಖ್ಯಾನಿಸು ಸಾಮಾನ್ಯ_LEDS ( LED2 | LED3 )
#ವ್ಯಾಖ್ಯಾನಿಸು RGB_LEDS ( RGB0 | RGB1 )

/*! Combines ALL LED defines */
#ವ್ಯಾಖ್ಯಾನಿಸು ALL_LEDS (RGB_LEDS | ಸಾಮಾನ್ಯ_LEDS)


/*! Control for all LEDS */
#ವ್ಯಾಖ್ಯಾನಿಸು ಸಾಮಾನ್ಯ_LED0 0
#ವ್ಯಾಖ್ಯಾನಿಸು ಸಾಮಾನ್ಯ_LED1 1

#ವ್ಯಾಖ್ಯಾನಿಸು RGB_LED0 0
#ವ್ಯಾಖ್ಯಾನಿಸು RGB_LED1 1

// function prototype
ಶೂನ್ಯ configure_ledx(ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ pin_cntrl);
ಶೂನ್ಯ configure_rgb_ledx(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ led_no);
ಶೂನ್ಯ configure_ಸಾಮಾನ್ಯ_leds();
ಶೂನ್ಯ configure_rgb_leds();
ಶೂನ್ಯ configure_all_leds();
ಶೂನ್ಯ turn_on_ledx(ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ pin_cntrl);
ಶೂನ್ಯ turn_off_ledx(ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ pin_cntrl);
ಶೂನ್ಯ turn_on_ಸಾಮಾನ್ಯ_leds();
ಶೂನ್ಯ turn_off_ಸಾಮಾನ್ಯ_leds();
ಶೂನ್ಯ turn_on_rgb_ledx(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ led_no);
ಶೂನ್ಯ turn_off_rgb_ledx(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ led_no);
ಶೂನ್ಯ turn_on_rgb_leds();
ಶೂನ್ಯ turn_off_rgb_leds();
ಶೂನ್ಯ turn_on_all_leds();
ಶೂನ್ಯ turn_off_all_leds();
ಶೂನ್ಯ toggle_ledx(ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ pin_cntrl, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay1, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay2);
ಶೂನ್ಯ toggle_ಸಾಮಾನ್ಯ_leds( ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay1, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay2 );
ಶೂನ್ಯ toggle_rgb_leds( ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay1, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay2 );
ಶೂನ್ಯ toggle_all_leds( ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay1, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay2);


#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ
