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

#నిర్వచితం_కాకపోతే LED_DRIVER_H
#నిర్వచించు LED_DRIVER_H

#అన్తర్భావ "platform.h" //Contains arty a7 gpio definitions.
#అన్తర్భావ "gpio.h"  //Contains the methods to Access GPIOs

#ఒకవేళ defined(ARTIX7_35T) || defined(ARTIX7_100T)
/*! RGB LED 0 defines */
#నిర్వచించు LED0_R GPIO16 
#నిర్వచించు LED0_G GPIO17
#నిర్వచించు LED0_B GPIO18

/*! RGB LED 1 defines */
#నిర్వచించు LED1_R GPIO19
#నిర్వచించు LED1_G GPIO20
#నిర్వచించు LED1_B GPIO21

/*! Normal LED 1 defines */
#నిర్వచించు LED2 GPIO22

/*! Normal LED 2 defines */
#నిర్వచించు LED3 GPIO23


/*! Combined RGB LED defines */
#నిర్వచించు RGB0 (LED0_R | LED0_G | LED0_B )
#నిర్వచించు RGB1 (LED1_R | LED1_G | LED1_B )

/*! Combined Normal LED defines */
#నిర్వచించు సాధారణ_LEDS ( LED2 | LED3 )
#నిర్వచించు RGB_LEDS ( RGB0 | RGB1 )

/*! Combines ALL LED defines */
#నిర్వచించు ALL_LEDS (RGB_LEDS | సాధారణ_LEDS)


/*! Control for all LEDS */
#నిర్వచించు సాధారణ_LED0 0
#నిర్వచించు సాధారణ_LED1 1

#నిర్వచించు RGB_LED0 0
#నిర్వచించు RGB_LED1 1

// function prototype
శూన్య configure_ledx(గుర్తులేని దీర్ఘ pin_cntrl);
శూన్య configure_rgb_ledx(గుర్తులేని అక్షరం led_no);
శూన్య configure_సాధారణ_leds();
శూన్య configure_rgb_leds();
శూన్య configure_all_leds();
శూన్య turn_on_ledx(గుర్తులేని దీర్ఘ pin_cntrl);
శూన్య turn_off_ledx(గుర్తులేని దీర్ఘ pin_cntrl);
శూన్య turn_on_సాధారణ_leds();
శూన్య turn_off_సాధారణ_leds();
శూన్య turn_on_rgb_ledx(గుర్తులేని అక్షరం led_no);
శూన్య turn_off_rgb_ledx(గుర్తులేని అక్షరం led_no);
శూన్య turn_on_rgb_leds();
శూన్య turn_off_rgb_leds();
శూన్య turn_on_all_leds();
శూన్య turn_off_all_leds();
శూన్య toggle_ledx(గుర్తులేని దీర్ఘ pin_cntrl, గుర్తులేని దీర్ఘ delay1, గుర్తులేని దీర్ఘ delay2);
శూన్య toggle_సాధారణ_leds( గుర్తులేని దీర్ఘ delay1, గుర్తులేని దీర్ఘ delay2 );
శూన్య toggle_rgb_leds( గుర్తులేని దీర్ఘ delay1, గుర్తులేని దీర్ఘ delay2 );
శూన్య toggle_all_leds( గుర్తులేని దీర్ఘ delay1, గుర్తులేని దీర్ఘ delay2);


#అయితే_ముగింపు
#అయితే_ముగింపు
