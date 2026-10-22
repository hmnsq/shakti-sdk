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

#అన్తర్భావ<stdbool.h>

// PWM Registers 
#నిర్వచించు PERIOD_రిజిస్టరు     0x00000000	//16 bits (short)
#నిర్వచించు DUTY_రిజిస్టరు       0x00000004	//16 bits (short)
#నిర్వచించు CONTROL_రిజిస్టరు    0x00000008	//8 bits (char)
#నిర్వచించు CLOCK_రిజిస్టరు      0x0000000c	//16 bits (short)

// Control Register Individual Bits 
#నిర్వచించు CLOCK_SELECTOR      0x00000001
#నిర్వచించు PWM_ENABLE          0x00000002
#నిర్వచించు PWM_ప్రారంభం           0x00000004
#నిర్వచించు CONTINUOUS_ONCE     0x00000008
#నిర్వచించు PWM_OUTPUT_ENABLE   0x00000010
#నిర్వచించు అంతరాయం_2           0x00000020
#నిర్వచించు READ_ONLY           0x00000040
#నిర్వచించు RESET_COUNTER       0x00000080

// PWM Modules 
#నిర్వచించు PWM_0 0
#నిర్వచించు PWM_1 1
#నిర్వచించు PWM_2 2
#నిర్వచించు PWM_3 3
#నిర్వచించు PWM_4 4
#నిర్వచించు PWM_5 5

//function prototype
శూన్య pwm_configure(పూర్ణాంకం module_సంఖ్య, పూర్ణాంకం clock_భాజకం, పూర్ణాంకం period, పూర్ణాంకం duty, bool external_clock);
శూన్య pwm_ప్రారంభం(పూర్ణాంకం module_సంఖ్య, పూర్ణాంకం బహుళకం);
పూర్ణాంకం pwm_check_continuous_బహుళకం(పూర్ణాంకం module_సంఖ్య);
శూన్య pwm_clear_registers(పూర్ణాంకం module_సంఖ్య);
శూన్య pwm_init(శూన్య);
శూన్య pwm_సమితి_external_clock(పూర్ణాంకం module_సంఖ్య, bool విలువ);
శూన్య pwm_సమితి_clock(పూర్ణాంకం module_సంఖ్య, పూర్ణాంకం clock_భాజకం);
శూన్య pwm_సమితి_duty_చక్రం(పూర్ణాంకం module_సంఖ్య, పూర్ణాంకం duty);
శూన్య pwm_సమితి_periodic_చక్రం(పూర్ణాంకం module_సంఖ్య, పూర్ణాంకం period);
శూన్య pwm_stop(పూర్ణాంకం module_సంఖ్య);
శూన్య show_రిజిస్టరు_విలువలు(పూర్ణాంకం module_సంఖ్య);
పూర్ణాంకం సమితి_pwm_period_రిజిస్టరు(పూర్ణాంకం module_సంఖ్య, పూర్ణాంకం విలువ);
పూర్ణాంకం సమితి_pwm_duty_రిజిస్టరు(పూర్ణాంకం module_సంఖ్య, పూర్ణాంకం విలువ);
పూర్ణాంకం సమితి_pwm_control_రిజిస్టరు(పూర్ణాంకం module_సంఖ్య, పూర్ణాంకం విలువ);
పూర్ణాంకం సమితి_pwm_clock_రిజిస్టరు(పూర్ణాంకం module_సంఖ్య, పూర్ణాంకం విలువ);
పూర్ణాంకం configure_control_రిజిస్టరు_బహుళకం(పూర్ణాంకం బహుళకం);
శూన్య pwm_use_external_clock(పూర్ణాంకం module_సంఖ్య, bool విలువ);

