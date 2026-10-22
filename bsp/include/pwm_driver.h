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

#അന്തര്ഭാവ<stdbool.h>

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
ശൂന്യം pwm_configure(പൂർണ്ണസംഖ്യ module_സംഖ്യ, പൂർണ്ണസംഖ്യ clock_ഹാരകം, പൂർണ്ണസംഖ്യ period, പൂർണ്ണസംഖ്യ duty, bool external_clock);
ശൂന്യം pwm_start(പൂർണ്ണസംഖ്യ module_സംഖ്യ, പൂർണ്ണസംഖ്യ mode);
പൂർണ്ണസംഖ്യ pwm_check_continuous_mode(പൂർണ്ണസംഖ്യ module_സംഖ്യ);
ശൂന്യം pwm_clear_registers(പൂർണ്ണസംഖ്യ module_സംഖ്യ);
ശൂന്യം pwm_init(ശൂന്യം);
ശൂന്യം pwm_set_external_clock(പൂർണ്ണസംഖ്യ module_സംഖ്യ, bool മൂല്യം);
ശൂന്യം pwm_set_clock(പൂർണ്ണസംഖ്യ module_സംഖ്യ, പൂർണ്ണസംഖ്യ clock_ഹാരകം);
ശൂന്യം pwm_set_duty_cycle(പൂർണ്ണസംഖ്യ module_സംഖ്യ, പൂർണ്ണസംഖ്യ duty);
ശൂന്യം pwm_set_periodic_cycle(പൂർണ്ണസംഖ്യ module_സംഖ്യ, പൂർണ്ണസംഖ്യ period);
ശൂന്യം pwm_stop(പൂർണ്ണസംഖ്യ module_സംഖ്യ);
ശൂന്യം show_register_മൂല്യങ്ങൾ(പൂർണ്ണസംഖ്യ module_സംഖ്യ);
പൂർണ്ണസംഖ്യ set_pwm_period_register(പൂർണ്ണസംഖ്യ module_സംഖ്യ, പൂർണ്ണസംഖ്യ മൂല്യം);
പൂർണ്ണസംഖ്യ set_pwm_duty_register(പൂർണ്ണസംഖ്യ module_സംഖ്യ, പൂർണ്ണസംഖ്യ മൂല്യം);
പൂർണ്ണസംഖ്യ set_pwm_control_register(പൂർണ്ണസംഖ്യ module_സംഖ്യ, പൂർണ്ണസംഖ്യ മൂല്യം);
പൂർണ്ണസംഖ്യ set_pwm_clock_register(പൂർണ്ണസംഖ്യ module_സംഖ്യ, പൂർണ്ണസംഖ്യ മൂല്യം);
പൂർണ്ണസംഖ്യ configure_control_register_mode(പൂർണ്ണസംഖ്യ mode);
ശൂന്യം pwm_use_external_clock(പൂർണ്ണസംഖ്യ module_സംഖ്യ, bool മൂല്യം);

