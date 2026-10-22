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
#تعریف_کړه PERIOD_ثبتوونکی     0x00000000	//16 bits (short)
#تعریف_کړه DUTY_ثبتوونکی       0x00000004	//16 bits (short)
#تعریف_کړه CONTROL_ثبتوونکی    0x00000008	//8 bits (char)
#تعریف_کړه CLOCK_ثبتوونکی      0x0000000c	//16 bits (short)

// Control Register Individual Bits 
#تعریف_کړه CLOCK_SELECTOR      0x00000001
#تعریف_کړه PWM_ENABLE          0x00000002
#تعریف_کړه PWM_پیل           0x00000004
#تعریف_کړه CONTINUOUS_ONCE     0x00000008
#تعریف_کړه PWM_OUTPUT_ENABLE   0x00000010
#تعریف_کړه مداخله_2           0x00000020
#تعریف_کړه READ_ONLY           0x00000040
#تعریف_کړه RESET_COUNTER       0x00000080

// PWM Modules 
#تعریف_کړه PWM_0 0
#تعریف_کړه PWM_1 1
#تعریف_کړه PWM_2 2
#تعریف_کړه PWM_3 3
#تعریف_کړه PWM_4 4
#تعریف_کړه PWM_5 5

//function prototype
فراغ pwm_configure(صحيح module_شمېره, صحيح clock_وېشونکی, صحيح period, صحيح duty, bool external_clock);
فراغ pwm_پیل(صحيح module_شمېره, صحيح ډېرپېښ);
صحيح pwm_check_continuous_ډېرپېښ(صحيح module_شمېره);
فراغ pwm_clear_registers(صحيح module_شمېره);
فراغ pwm_init(فراغ);
فراغ pwm_سېټ_external_clock(صحيح module_شمېره, bool ارزښت);
فراغ pwm_سېټ_clock(صحيح module_شمېره, صحيح clock_وېشونکی);
فراغ pwm_سېټ_duty_دوره(صحيح module_شمېره, صحيح duty);
فراغ pwm_سېټ_periodic_دوره(صحيح module_شمېره, صحيح period);
فراغ pwm_stop(صحيح module_شمېره);
فراغ show_ثبتوونکی_ارزښتونه(صحيح module_شمېره);
صحيح سېټ_pwm_period_ثبتوونکی(صحيح module_شمېره, صحيح ارزښت);
صحيح سېټ_pwm_duty_ثبتوونکی(صحيح module_شمېره, صحيح ارزښت);
صحيح سېټ_pwm_control_ثبتوونکی(صحيح module_شمېره, صحيح ارزښت);
صحيح سېټ_pwm_clock_ثبتوونکی(صحيح module_شمېره, صحيح ارزښت);
صحيح configure_control_ثبتوونکی_ډېرپېښ(صحيح ډېرپېښ);
فراغ pwm_use_external_clock(صحيح module_شمېره, bool ارزښت);

