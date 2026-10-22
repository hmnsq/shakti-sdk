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

#شامل<stdbool.h>

// PWM Registers 
#تعریف_کرو PERIOD_رجسٹر     0x00000000	//16 bits (short)
#تعریف_کرو DUTY_رجسٹر       0x00000004	//16 bits (short)
#تعریف_کرو CONTROL_رجسٹر    0x00000008	//8 bits (char)
#تعریف_کرو CLOCK_رجسٹر      0x0000000c	//16 bits (short)

// Control Register Individual Bits 
#تعریف_کرو CLOCK_SELECTOR      0x00000001
#تعریف_کرو PWM_ENABLE          0x00000002
#تعریف_کرو PWM_آغاز           0x00000004
#تعریف_کرو CONTINUOUS_ONCE     0x00000008
#تعریف_کرو PWM_OUTPUT_ENABLE   0x00000010
#تعریف_کرو مداخلت_2           0x00000020
#تعریف_کرو READ_ONLY           0x00000040
#تعریف_کرو RESET_شمار       0x00000080

// PWM Modules 
#تعریف_کرو PWM_0 0
#تعریف_کرو PWM_1 1
#تعریف_کرو PWM_2 2
#تعریف_کرو PWM_3 3
#تعریف_کرو PWM_4 4
#تعریف_کرو PWM_5 5

//function prototype
خالی pwm_configure(صحیح module_نمبر, صحیح clock_مقسوم_علیہ, صحیح period, صحیح duty, bool external_clock);
خالی pwm_آغاز(صحیح module_نمبر, صحیح منوال);
صحیح pwm_check_continuous_منوال(صحیح module_نمبر);
خالی pwm_clear_registers(صحیح module_نمبر);
خالی pwm_init(خالی);
خالی pwm_سیٹ_external_clock(صحیح module_نمبر, bool قدر);
خالی pwm_سیٹ_clock(صحیح module_نمبر, صحیح clock_مقسوم_علیہ);
خالی pwm_سیٹ_duty_چکر(صحیح module_نمبر, صحیح duty);
خالی pwm_سیٹ_periodic_چکر(صحیح module_نمبر, صحیح period);
خالی pwm_stop(صحیح module_نمبر);
خالی show_رجسٹر_اقدار(صحیح module_نمبر);
صحیح سیٹ_pwm_period_رجسٹر(صحیح module_نمبر, صحیح قدر);
صحیح سیٹ_pwm_duty_رجسٹر(صحیح module_نمبر, صحیح قدر);
صحیح سیٹ_pwm_control_رجسٹر(صحیح module_نمبر, صحیح قدر);
صحیح سیٹ_pwm_clock_رجسٹر(صحیح module_نمبر, صحیح قدر);
صحیح configure_control_رجسٹر_منوال(صحیح منوال);
خالی pwm_use_external_clock(صحیح module_نمبر, bool قدر);

