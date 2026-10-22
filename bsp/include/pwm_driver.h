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

#অন্তর্ভাব<stdbool.h>

// PWM Registers 
#define PERIOD_REGISTER     0x00000000	//16 bits (short)
#define DUTY_REGISTER       0x00000004	//16 bits (short)
#define CONTROL_REGISTER    0x00000008	//8 bits (char)
#define CLOCK_REGISTER      0x0000000c	//16 bits (short)

// Control Register Individual Bits 
#define CLOCK_SELECTOR      0x00000001
#define PWM_ENABLE          0x00000002
#define PWM_START           0x00000004
#define CONTINUOUS_ONCE     0x00000008
#define PWM_OUTPUT_ENABLE   0x00000010
#define INTERRUPT           0x00000020
#define READ_ONLY           0x00000040
#define RESET_গণক       0x00000080

// PWM Modules 
#define PWM_0 0
#define PWM_1 1
#define PWM_2 2
#define PWM_3 3
#define PWM_4 4
#define PWM_5 5

//function prototype
শূন্য pwm_configure(পূর্ণসংখ্যা module_সংখ্যা, পূর্ণসংখ্যা clock_ভাজক, পূর্ণসংখ্যা period, পূর্ণসংখ্যা duty, bool external_clock);
শূন্য pwm_start(পূর্ণসংখ্যা module_সংখ্যা, পূর্ণসংখ্যা mode);
পূর্ণসংখ্যা pwm_check_continuous_mode(পূর্ণসংখ্যা module_সংখ্যা);
শূন্য pwm_clear_registers(পূর্ণসংখ্যা module_সংখ্যা);
শূন্য pwm_init(শূন্য);
শূন্য pwm_set_external_clock(পূর্ণসংখ্যা module_সংখ্যা, bool মান);
শূন্য pwm_set_clock(পূর্ণসংখ্যা module_সংখ্যা, পূর্ণসংখ্যা clock_ভাজক);
শূন্য pwm_set_duty_cycle(পূর্ণসংখ্যা module_সংখ্যা, পূর্ণসংখ্যা duty);
শূন্য pwm_set_periodic_cycle(পূর্ণসংখ্যা module_সংখ্যা, পূর্ণসংখ্যা period);
শূন্য pwm_stop(পূর্ণসংখ্যা module_সংখ্যা);
শূন্য show_register_মানসমূহ(পূর্ণসংখ্যা module_সংখ্যা);
পূর্ণসংখ্যা set_pwm_period_register(পূর্ণসংখ্যা module_সংখ্যা, পূর্ণসংখ্যা মান);
পূর্ণসংখ্যা set_pwm_duty_register(পূর্ণসংখ্যা module_সংখ্যা, পূর্ণসংখ্যা মান);
পূর্ণসংখ্যা set_pwm_control_register(পূর্ণসংখ্যা module_সংখ্যা, পূর্ণসংখ্যা মান);
পূর্ণসংখ্যা set_pwm_clock_register(পূর্ণসংখ্যা module_সংখ্যা, পূর্ণসংখ্যা মান);
পূর্ণসংখ্যা configure_control_register_mode(পূর্ণসংখ্যা mode);
শূন্য pwm_use_external_clock(পূর্ণসংখ্যা module_সংখ্যা, bool মান);

