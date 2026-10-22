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

#include<stdbool.h>

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
#define RESET_COUNTER       0x00000080

// PWM Modules 
#define PWM_0 0
#define PWM_1 1
#define PWM_2 2
#define PWM_3 3
#define PWM_4 4
#define PWM_5 5

//function prototype
void pwm_configure(ціле module_number, ціле clock_divisor, ціле period, ціле duty, bool external_clock);
void pwm_start(ціле module_number, ціле mode);
ціле pwm_check_continuous_mode(ціле module_number);
void pwm_clear_registers(ціле module_number);
void pwm_init(void);
void pwm_set_external_clock(ціле module_number, bool value);
void pwm_set_clock(ціле module_number, ціле clock_divisor);
void pwm_set_duty_cycle(ціле module_number, ціле duty);
void pwm_set_periodic_cycle(ціле module_number, ціле period);
void pwm_stop(ціле module_number);
void show_register_values(ціле module_number);
ціле set_pwm_period_register(ціле module_number, ціле value);
ціле set_pwm_duty_register(ціле module_number, ціле value);
ціле set_pwm_control_register(ціле module_number, ціле value);
ціле set_pwm_clock_register(ціле module_number, ціле value);
ціле configure_control_register_mode(ціле mode);
void pwm_use_external_clock(ціле module_number, bool value);

