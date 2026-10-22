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
#تعریف_کن PERIOD_ثبات     0x00000000	//16 bits (short)
#تعریف_کن DUTY_ثبات       0x00000004	//16 bits (short)
#تعریف_کن CONTROL_ثبات    0x00000008	//8 bits (char)
#تعریف_کن CLOCK_ثبات      0x0000000c	//16 bits (short)

// Control Register Individual Bits 
#تعریف_کن CLOCK_SELECTOR      0x00000001
#تعریف_کن PWM_ENABLE          0x00000002
#تعریف_کن PWM_شروع           0x00000004
#تعریف_کن CONTINUOUS_ONCE     0x00000008
#تعریف_کن PWM_OUTPUT_ENABLE   0x00000010
#تعریف_کن وقفه_2           0x00000020
#تعریف_کن READ_ONLY           0x00000040
#تعریف_کن RESET_COUNTER       0x00000080

// PWM Modules 
#تعریف_کن PWM_0 0
#تعریف_کن PWM_1 1
#تعریف_کن PWM_2 2
#تعریف_کن PWM_3 3
#تعریف_کن PWM_4 4
#تعریف_کن PWM_5 5

//function prototype
فراغ pwm_configure(صحيح module_عدد, صحيح clock_مقسوم_علیه, صحيح period, صحيح duty, bool external_clock);
فراغ pwm_شروع(صحيح module_عدد, صحيح نما);
صحيح pwm_check_continuous_نما(صحيح module_عدد);
فراغ pwm_clear_registers(صحيح module_عدد);
فراغ pwm_init(فراغ);
فراغ pwm_مجموعه_external_clock(صحيح module_عدد, bool مقدار);
فراغ pwm_مجموعه_clock(صحيح module_عدد, صحيح clock_مقسوم_علیه);
فراغ pwm_مجموعه_duty_چرخه(صحيح module_عدد, صحيح duty);
فراغ pwm_مجموعه_periodic_چرخه(صحيح module_عدد, صحيح period);
فراغ pwm_stop(صحيح module_عدد);
فراغ show_ثبات_مقادیر(صحيح module_عدد);
صحيح مجموعه_pwm_period_ثبات(صحيح module_عدد, صحيح مقدار);
صحيح مجموعه_pwm_duty_ثبات(صحيح module_عدد, صحيح مقدار);
صحيح مجموعه_pwm_control_ثبات(صحيح module_عدد, صحيح مقدار);
صحيح مجموعه_pwm_clock_ثبات(صحيح module_عدد, صحيح مقدار);
صحيح configure_control_ثبات_نما(صحيح نما);
فراغ pwm_use_external_clock(صحيح module_عدد, bool مقدار);

