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

#ಅನ್ತರ್ಭಾವ<stdbool.h>

// PWM Registers 
#ವ್ಯಾಖ್ಯಾನಿಸು PERIOD_ರಿಜಿಸ್ಟರ್     0x00000000	//16 bits (short)
#ವ್ಯಾಖ್ಯಾನಿಸು DUTY_ರಿಜಿಸ್ಟರ್       0x00000004	//16 bits (short)
#ವ್ಯಾಖ್ಯಾನಿಸು CONTROL_ರಿಜಿಸ್ಟರ್    0x00000008	//8 bits (char)
#ವ್ಯಾಖ್ಯಾನಿಸು CLOCK_ರಿಜಿಸ್ಟರ್      0x0000000c	//16 bits (short)

// Control Register Individual Bits 
#ವ್ಯಾಖ್ಯಾನಿಸು CLOCK_SELECTOR      0x00000001
#ವ್ಯಾಖ್ಯಾನಿಸು PWM_ENABLE          0x00000002
#ವ್ಯಾಖ್ಯಾನಿಸು PWM_ಆರಂಭ           0x00000004
#ವ್ಯಾಖ್ಯಾನಿಸು CONTINUOUS_ONCE     0x00000008
#ವ್ಯಾಖ್ಯಾನಿಸು PWM_OUTPUT_ENABLE   0x00000010
#ವ್ಯಾಖ್ಯಾನಿಸು ಅಡಚಣೆ_2           0x00000020
#ವ್ಯಾಖ್ಯಾನಿಸು READ_ONLY           0x00000040
#ವ್ಯಾಖ್ಯಾನಿಸು RESET_COUNTER       0x00000080

// PWM Modules 
#ವ್ಯಾಖ್ಯಾನಿಸು PWM_0 0
#ವ್ಯಾಖ್ಯಾನಿಸು PWM_1 1
#ವ್ಯಾಖ್ಯಾನಿಸು PWM_2 2
#ವ್ಯಾಖ್ಯಾನಿಸು PWM_3 3
#ವ್ಯಾಖ್ಯಾನಿಸು PWM_4 4
#ವ್ಯಾಖ್ಯಾನಿಸು PWM_5 5

//function prototype
ಶೂನ್ಯ pwm_configure(ಪೂರ್ಣಾಂಕ module_ಸಂಖ್ಯೆ, ಪೂರ್ಣಾಂಕ clock_ಭಾಜಕ, ಪೂರ್ಣಾಂಕ period, ಪೂರ್ಣಾಂಕ duty, bool external_clock);
ಶೂನ್ಯ pwm_ಆರಂಭ(ಪೂರ್ಣಾಂಕ module_ಸಂಖ್ಯೆ, ಪೂರ್ಣಾಂಕ ಬಹುಲಕ);
ಪೂರ್ಣಾಂಕ pwm_check_continuous_ಬಹುಲಕ(ಪೂರ್ಣಾಂಕ module_ಸಂಖ್ಯೆ);
ಶೂನ್ಯ pwm_clear_registers(ಪೂರ್ಣಾಂಕ module_ಸಂಖ್ಯೆ);
ಶೂನ್ಯ pwm_init(ಶೂನ್ಯ);
ಶೂನ್ಯ pwm_ಗಣ_external_clock(ಪೂರ್ಣಾಂಕ module_ಸಂಖ್ಯೆ, bool ಮೌಲ್ಯ);
ಶೂನ್ಯ pwm_ಗಣ_clock(ಪೂರ್ಣಾಂಕ module_ಸಂಖ್ಯೆ, ಪೂರ್ಣಾಂಕ clock_ಭಾಜಕ);
ಶೂನ್ಯ pwm_ಗಣ_duty_ಚಕ್ರ(ಪೂರ್ಣಾಂಕ module_ಸಂಖ್ಯೆ, ಪೂರ್ಣಾಂಕ duty);
ಶೂನ್ಯ pwm_ಗಣ_periodic_ಚಕ್ರ(ಪೂರ್ಣಾಂಕ module_ಸಂಖ್ಯೆ, ಪೂರ್ಣಾಂಕ period);
ಶೂನ್ಯ pwm_stop(ಪೂರ್ಣಾಂಕ module_ಸಂಖ್ಯೆ);
ಶೂನ್ಯ show_ರಿಜಿಸ್ಟರ್_ಮೌಲ್ಯಗಳು(ಪೂರ್ಣಾಂಕ module_ಸಂಖ್ಯೆ);
ಪೂರ್ಣಾಂಕ ಗಣ_pwm_period_ರಿಜಿಸ್ಟರ್(ಪೂರ್ಣಾಂಕ module_ಸಂಖ್ಯೆ, ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ);
ಪೂರ್ಣಾಂಕ ಗಣ_pwm_duty_ರಿಜಿಸ್ಟರ್(ಪೂರ್ಣಾಂಕ module_ಸಂಖ್ಯೆ, ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ);
ಪೂರ್ಣಾಂಕ ಗಣ_pwm_control_ರಿಜಿಸ್ಟರ್(ಪೂರ್ಣಾಂಕ module_ಸಂಖ್ಯೆ, ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ);
ಪೂರ್ಣಾಂಕ ಗಣ_pwm_clock_ರಿಜಿಸ್ಟರ್(ಪೂರ್ಣಾಂಕ module_ಸಂಖ್ಯೆ, ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ);
ಪೂರ್ಣಾಂಕ configure_control_ರಿಜಿಸ್ಟರ್_ಬಹುಲಕ(ಪೂರ್ಣಾಂಕ ಬಹುಲಕ);
ಶೂನ್ಯ pwm_use_external_clock(ಪೂರ್ಣಾಂಕ module_ಸಂಖ್ಯೆ, bool ಮೌಲ್ಯ);

