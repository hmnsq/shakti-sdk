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
#تعریف_کرو PERIOD_رجسٹر     0x00000000	//16 bits (short)
#تعریف_کرو DUTY_رجسٹر       0x00000004	//16 bits (short)
#تعریف_کرو CONTROL_رجسٹر    0x00000008	//8 bits (char)
#تعریف_کرو CLOCK_رجسٹر      0x0000000c	//16 bits (short)

// Control Register Individual Bits 
#تعریف_کرو CLOCK_SELECTOR      0x00000001
#تعریف_کرو PWM_ENABLE          0x00000002
#تعریف_کرو PWM_شروع           0x00000004
#تعریف_کرو CONTINUOUS_ONCE     0x00000008
#تعریف_کرو PWM_OUTPUT_ENABLE   0x00000010
#تعریف_کرو رکاوٹ_2           0x00000020
#تعریف_کرو READ_ONLY           0x00000040
#تعریف_کرو RESET_COUNTER       0x00000080

// PWM Modules 
#تعریف_کرو PWM_0 0
#تعریف_کرو PWM_1 1
#تعریف_کرو PWM_2 2
#تعریف_کرو PWM_3 3
#تعریف_کرو PWM_4 4
#تعریف_کرو PWM_5 5

//function prototype
فراغ pwm_configure(صحيح module_نمبر, صحيح clock_مقسوم_علیہ, صحيح period, صحيح duty, bool external_clock);
فراغ pwm_شروع(صحيح module_نمبر, صحيح منوال);
صحيح pwm_check_continuous_منوال(صحيح module_نمبر);
فراغ pwm_clear_registers(صحيح module_نمبر);
فراغ pwm_init(فراغ);
فراغ pwm_سیٹ_external_clock(صحيح module_نمبر, bool قدر);
فراغ pwm_سیٹ_clock(صحيح module_نمبر, صحيح clock_مقسوم_علیہ);
فراغ pwm_سیٹ_duty_چکر(صحيح module_نمبر, صحيح duty);
فراغ pwm_سیٹ_periodic_چکر(صحيح module_نمبر, صحيح period);
فراغ pwm_stop(صحيح module_نمبر);
فراغ show_رجسٹر_اقدار(صحيح module_نمبر);
صحيح سیٹ_pwm_period_رجسٹر(صحيح module_نمبر, صحيح قدر);
صحيح سیٹ_pwm_duty_رجسٹر(صحيح module_نمبر, صحيح قدر);
صحيح سیٹ_pwm_control_رجسٹر(صحيح module_نمبر, صحيح قدر);
صحيح سیٹ_pwm_clock_رجسٹر(صحيح module_نمبر, صحيح قدر);
صحيح configure_control_رجسٹر_منوال(صحيح منوال);
فراغ pwm_use_external_clock(صحيح module_نمبر, bool قدر);

