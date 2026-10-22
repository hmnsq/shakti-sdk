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

#समावेश<stdbool.h>

// PWM Registers 
#घोषणा PERIOD_REGISTER     0x00000000	//16 bits (short)
#घोषणा DUTY_REGISTER       0x00000004	//16 bits (short)
#घोषणा CONTROL_REGISTER    0x00000008	//8 bits (char)
#घोषणा CLOCK_REGISTER      0x0000000c	//16 bits (short)

// Control Register Individual Bits 
#घोषणा CLOCK_SELECTOR      0x00000001
#घोषणा PWM_ENABLE          0x00000002
#घोषणा PWM_START           0x00000004
#घोषणा CONTINUOUS_ONCE     0x00000008
#घोषणा PWM_OUTPUT_ENABLE   0x00000010
#घोषणा INTERRUPT           0x00000020
#घोषणा READ_ONLY           0x00000040
#घोषणा RESET_गणक       0x00000080

// PWM Modules 
#घोषणा PWM_0 0
#घोषणा PWM_1 1
#घोषणा PWM_2 2
#घोषणा PWM_3 3
#घोषणा PWM_4 4
#घोषणा PWM_5 5

//function prototype
व्योम pwm_configure(पूर्णांक module_संख्या, पूर्णांक clock_भाजक, पूर्णांक period, पूर्णांक duty, bool external_clock);
व्योम pwm_start(पूर्णांक module_संख्या, पूर्णांक mode);
पूर्णांक pwm_check_continuous_mode(पूर्णांक module_संख्या);
व्योम pwm_clear_registers(पूर्णांक module_संख्या);
व्योम pwm_init(व्योम);
व्योम pwm_set_external_clock(पूर्णांक module_संख्या, bool मूल्य);
व्योम pwm_set_clock(पूर्णांक module_संख्या, पूर्णांक clock_भाजक);
व्योम pwm_set_duty_cycle(पूर्णांक module_संख्या, पूर्णांक duty);
व्योम pwm_set_periodic_cycle(पूर्णांक module_संख्या, पूर्णांक period);
व्योम pwm_stop(पूर्णांक module_संख्या);
व्योम show_register_मूल्यावली(पूर्णांक module_संख्या);
पूर्णांक set_pwm_period_register(पूर्णांक module_संख्या, पूर्णांक मूल्य);
पूर्णांक set_pwm_duty_register(पूर्णांक module_संख्या, पूर्णांक मूल्य);
पूर्णांक set_pwm_control_register(पूर्णांक module_संख्या, पूर्णांक मूल्य);
पूर्णांक set_pwm_clock_register(पूर्णांक module_संख्या, पूर्णांक मूल्य);
पूर्णांक configure_control_register_mode(पूर्णांक mode);
व्योम pwm_use_external_clock(पूर्णांक module_संख्या, bool मूल्य);

