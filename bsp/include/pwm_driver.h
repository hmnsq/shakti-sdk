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

#ਅਨ੍ਤਰ੍ਭਾਵ<stdbool.h>

// PWM Registers 
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PERIOD_ਰਜਿਸਟਰ     0x00000000	//16 bits (short)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DUTY_ਰਜਿਸਟਰ       0x00000004	//16 bits (short)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CONTROL_ਰਜਿਸਟਰ    0x00000008	//8 bits (char)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CLOCK_ਰਜਿਸਟਰ      0x0000000c	//16 bits (short)

// Control Register Individual Bits 
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CLOCK_SELECTOR      0x00000001
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PWM_ENABLE          0x00000002
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PWM_ਸ਼ੁਰੂ           0x00000004
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CONTINUOUS_ONCE     0x00000008
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PWM_OUTPUT_ENABLE   0x00000010
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਰੁਕਾਵਟ_2           0x00000020
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ READ_ONLY           0x00000040
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RESET_COUNTER       0x00000080

// PWM Modules 
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PWM_0 0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PWM_1 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PWM_2 2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PWM_3 3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PWM_4 4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PWM_5 5

//function prototype
ਖਾਲੀ pwm_configure(ਪੂਰਨ module_ਸੰਖਿਆ, ਪੂਰਨ clock_ਭਾਜਕ, ਪੂਰਨ period, ਪੂਰਨ duty, bool external_clock);
ਖਾਲੀ pwm_ਸ਼ੁਰੂ(ਪੂਰਨ module_ਸੰਖਿਆ, ਪੂਰਨ ਬਹੁਲਕ);
ਪੂਰਨ pwm_check_continuous_ਬਹੁਲਕ(ਪੂਰਨ module_ਸੰਖਿਆ);
ਖਾਲੀ pwm_clear_registers(ਪੂਰਨ module_ਸੰਖਿਆ);
ਖਾਲੀ pwm_init(ਖਾਲੀ);
ਖਾਲੀ pwm_ਸੈੱਟ_external_clock(ਪੂਰਨ module_ਸੰਖਿਆ, bool ਮੁੱਲ);
ਖਾਲੀ pwm_ਸੈੱਟ_clock(ਪੂਰਨ module_ਸੰਖਿਆ, ਪੂਰਨ clock_ਭਾਜਕ);
ਖਾਲੀ pwm_ਸੈੱਟ_duty_ਚੱਕਰ(ਪੂਰਨ module_ਸੰਖਿਆ, ਪੂਰਨ duty);
ਖਾਲੀ pwm_ਸੈੱਟ_periodic_ਚੱਕਰ(ਪੂਰਨ module_ਸੰਖਿਆ, ਪੂਰਨ period);
ਖਾਲੀ pwm_stop(ਪੂਰਨ module_ਸੰਖਿਆ);
ਖਾਲੀ show_ਰਜਿਸਟਰ_ਮੁੱਲਾਂ(ਪੂਰਨ module_ਸੰਖਿਆ);
ਪੂਰਨ ਸੈੱਟ_pwm_period_ਰਜਿਸਟਰ(ਪੂਰਨ module_ਸੰਖਿਆ, ਪੂਰਨ ਮੁੱਲ);
ਪੂਰਨ ਸੈੱਟ_pwm_duty_ਰਜਿਸਟਰ(ਪੂਰਨ module_ਸੰਖਿਆ, ਪੂਰਨ ਮੁੱਲ);
ਪੂਰਨ ਸੈੱਟ_pwm_control_ਰਜਿਸਟਰ(ਪੂਰਨ module_ਸੰਖਿਆ, ਪੂਰਨ ਮੁੱਲ);
ਪੂਰਨ ਸੈੱਟ_pwm_clock_ਰਜਿਸਟਰ(ਪੂਰਨ module_ਸੰਖਿਆ, ਪੂਰਨ ਮੁੱਲ);
ਪੂਰਨ configure_control_ਰਜਿਸਟਰ_ਬਹੁਲਕ(ਪੂਰਨ ਬਹੁਲਕ);
ਖਾਲੀ pwm_use_external_clock(ਪੂਰਨ module_ਸੰਖਿਆ, bool ਮੁੱਲ);

