/***************************************************************************
* Project               	 : shakti devt board
* Name of the file	         : pwm_driver.h
* Brief Description of file      : Header file for PWM Driver.
* Name of Author    	         : Abhinav Ramnath
* Email ID                       : abhinavramnath13@gmail.com

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
 * @file pwm_driver.h
 * @brief Header file for PWM Driver.
 * @detail the header file for the pwm module which is used to change the frequency, period and duty registers
 */

#ضمن<stdbool.h>

// PWM Registers 
#وصف_ڪريو PERIOD_رجسٽر     0x00000000	//16 bits (short)
#وصف_ڪريو DUTY_رجسٽر       0x00000004	//16 bits (short)
#وصف_ڪريو CONTROL_رجسٽر    0x00000008	//8 bits (char)
#وصف_ڪريو CLOCK_رجسٽر      0x0000000c	//16 bits (short)

// Control Register Individual Bits 
#وصف_ڪريو CLOCK_SELECTOR      0x00000001
#وصف_ڪريو PWM_ENABLE          0x00000002
#وصف_ڪريو PWM_شروعات           0x00000004
#وصف_ڪريو CONTINUOUS_ONCE     0x00000008
#وصف_ڪريو PWM_OUTPUT_ENABLE   0x00000010
#وصف_ڪريو مداخلت_2           0x00000020
#وصف_ڪريو READ_ONLY           0x00000040
#وصف_ڪريو RESET_COUNTER       0x00000080

// PWM Modules 
#وصف_ڪريو PWM_0 0
#وصف_ڪريو PWM_1 1
#وصف_ڪريو PWM_2 2
#وصف_ڪريو PWM_3 3
#وصف_ڪريو PWM_4 4
#وصف_ڪريو PWM_5 5

//function prototype
فراغ pwm_configure(صحيح module_عدد, صحيح clock_ورهائيندڙ, صحيح period, صحيح duty, bool external_clock);
فراغ pwm_شروعات(صحيح module_عدد, صحيح گهڻائي);
صحيح pwm_check_continuous_گهڻائي(صحيح module_عدد);
فراغ pwm_clear_registers(صحيح module_عدد);
فراغ pwm_init(فراغ);
فراغ pwm_سيٽ_external_clock(صحيح module_عدد, bool قدر);
فراغ pwm_سيٽ_clock(صحيح module_عدد, صحيح clock_ورهائيندڙ);
فراغ pwm_سيٽ_duty_چڪر(صحيح module_عدد, صحيح duty);
فراغ pwm_سيٽ_periodic_چڪر(صحيح module_عدد, صحيح period);
فراغ pwm_stop(صحيح module_عدد);
فراغ show_رجسٽر_قدرون(صحيح module_عدد);
صحيح سيٽ_pwm_period_رجسٽر(صحيح module_عدد, صحيح قدر);
صحيح سيٽ_pwm_duty_رجسٽر(صحيح module_عدد, صحيح قدر);
صحيح سيٽ_pwm_control_رجسٽر(صحيح module_عدد, صحيح قدر);
صحيح سيٽ_pwm_clock_رجسٽر(صحيح module_عدد, صحيح قدر);
صحيح configure_control_رجسٽر_گهڻائي(صحيح گهڻائي);
فراغ pwm_use_external_clock(صحيح module_عدد, bool قدر);

