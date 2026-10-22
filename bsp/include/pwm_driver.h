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

#अन्तर्भाव<stdbool.h>

// PWM Registers 
#परिभाषय PERIOD_पञ्जिकाकोशः     0x00000000	//16 bits (short)
#परिभाषय DUTY_पञ्जिकाकोशः       0x00000004	//16 bits (short)
#परिभाषय CONTROL_पञ्जिकाकोशः    0x00000008	//8 bits (char)
#परिभाषय CLOCK_पञ्जिकाकोशः      0x0000000c	//16 bits (short)

// Control Register Individual Bits 
#परिभाषय CLOCK_SELECTOR      0x00000001
#परिभाषय PWM_ENABLE          0x00000002
#परिभाषय PWM_START           0x00000004
#परिभाषय CONTINUOUS_ONCE     0x00000008
#परिभाषय PWM_OUTPUT_ENABLE   0x00000010
#परिभाषय व्यवधानम्_2           0x00000020
#परिभाषय READ_ONLY           0x00000040
#परिभाषय RESET_गणक       0x00000080

// PWM Modules 
#परिभाषय PWM_0 0
#परिभाषय PWM_1 1
#परिभाषय PWM_2 2
#परिभाषय PWM_3 3
#परिभाषय PWM_4 4
#परिभाषय PWM_5 5

//function prototype
शून्य pwm_configure(पूर्णाङ्क module_सङ्ख्या, पूर्णाङ्क clock_भाजकः, पूर्णाङ्क period, पूर्णाङ्क duty, bool external_clock);
शून्य pwm_start(पूर्णाङ्क module_सङ्ख्या, पूर्णाङ्क बहुलकम्);
पूर्णाङ्क pwm_check_continuous_बहुलकम्(पूर्णाङ्क module_सङ्ख्या);
शून्य pwm_clear_registers(पूर्णाङ्क module_सङ्ख्या);
शून्य pwm_init(शून्य);
शून्य pwm_समुच्चयः_external_clock(पूर्णाङ्क module_सङ्ख्या, bool मानम्);
शून्य pwm_समुच्चयः_clock(पूर्णाङ्क module_सङ्ख्या, पूर्णाङ्क clock_भाजकः);
शून्य pwm_समुच्चयः_duty_आवृत्तिः(पूर्णाङ्क module_सङ्ख्या, पूर्णाङ्क duty);
शून्य pwm_समुच्चयः_periodic_आवृत्तिः(पूर्णाङ्क module_सङ्ख्या, पूर्णाङ्क period);
शून्य pwm_stop(पूर्णाङ्क module_सङ्ख्या);
शून्य show_पञ्जिकाकोशः_मानानि(पूर्णाङ्क module_सङ्ख्या);
पूर्णाङ्क समुच्चयः_pwm_period_पञ्जिकाकोशः(पूर्णाङ्क module_सङ्ख्या, पूर्णाङ्क मानम्);
पूर्णाङ्क समुच्चयः_pwm_duty_पञ्जिकाकोशः(पूर्णाङ्क module_सङ्ख्या, पूर्णाङ्क मानम्);
पूर्णाङ्क समुच्चयः_pwm_control_पञ्जिकाकोशः(पूर्णाङ्क module_सङ्ख्या, पूर्णाङ्क मानम्);
पूर्णाङ्क समुच्चयः_pwm_clock_पञ्जिकाकोशः(पूर्णाङ्क module_सङ्ख्या, पूर्णाङ्क मानम्);
पूर्णाङ्क configure_control_पञ्जिकाकोशः_बहुलकम्(पूर्णाङ्क बहुलकम्);
शून्य pwm_use_external_clock(पूर्णाङ्क module_सङ्ख्या, bool मानम्);

