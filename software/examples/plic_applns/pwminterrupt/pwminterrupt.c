/***************************************************************************
 * Project           		: shakti devt board
 * Name of the file	     	: pwminterrupt.c
 * Brief Description of file    : pwm interrupt .
 * Name of Author    	        : Sathya Narayanan N  & Abhinav Ramnath
 * Email ID                     : sathya281@gmail.com & abhinavramnath13@gmail.com 

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
@file pwminterrupt
@brief A application to demonstrate working of pwm interrupts
@detail This file contains an application to demonstrate the working of pwm
 interrupts. The interrupts are enabled for a pwm module. The pwm module is
 confiured for interrupt mode and pwm registers are setup appropriately.
 Once the pwm timer overflows, an interrupt is generated and it is handled
 by the isr.
*/

#ਅਨ੍ਤਰ੍ਭਾਵ "gpio.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "uart.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "traps.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "platform.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "plic_driver.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "memory.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pwm_driver.h"

/** @fn unsigned handle_pwm_interrupt (uint32_t num)
 * @brief  Default handler to handle pwm interrupt,
 *         the interrupt has to be cleared by doing a reset.
 * @param unsigned num
 * @return unsigned
 */
ਖਾਲੀ handle_pwm_ਰੁਕਾਵਟ( uint32_t ਅੰਕ)
{
	ਜੇ(pwm_check_continuous_ਬਹੁਲਕ((6-ਅੰਕ)) == 0)
	{
		ਸੈੱਟ_pwm_control_ਰਜਿਸਟਰ((6-ਅੰਕ),0x80);
	}
	log_info("pwm interrupt handled\n");
}

/** @fn void main(void)
 * @brief sets up the environment for pwn interrupt feature
  */
ਖਾਲੀ ਮੁੱਖ(ਖਾਲੀ){

	ਰਜਿਸਟਰ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ retval;
	ਪੂਰਨ i;

	plic_init();

	/*
	   Configure pwm module interrupt
	 */
	configure_ਰੁਕਾਵਟ(PLIC_ਰੁਕਾਵਟ_2);
	isr_ਸਾਰਣੀ[PLIC_ਰੁਕਾਵਟ_2] = handle_pwm_ਰੁਕਾਵਟ;

	// Enable Global (PLIC) interrupts.
	asm ਅਸਥਿਰ("li      t0, 8\t\n"
		     "csrrs   zero, mstatus, t0\t\n"
		    );

	asm ਅਸਥਿਰ("li      t0, 0x800\t\n"
		     "csrrs   zero, mie, t0\t\n"
		    );

	asm ਅਸਥਿਰ(
		     "csrr %[retval], mstatus\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );

	log_debug(" mstatus = %x\n", retval);

	asm ਅਸਥਿਰ(
		     "csrr %[retval], mie\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );

	log_debug("mie = %x\n", retval);

	asm ਅਸਥਿਰ(
		     "csrr %[retval], mip\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );

	log_debug(" mip  = %x\n", retval);

/*uncomment to test PWM 0 interrupts (interrupt ID - 5)
	pwm_configure(PWM_0,0xffff,0xff,0x01,false);
	pwm_start(PWM_0,2);
*/
/*uncomment to test PWM 1 interrupts (interrupt ID - 4)
	pwm_configure(PWM_1,0xffff,0xff,0x01,false);
	pwm_start(PWM_1,2);
*/
/*uncomment to test PWM 2 interrupts (interrupt ID - 3)
	pwm_configure(PWM_2,0xffff,0xff,0x01,false); 
	pwm_start(PWM_2,2);
*/
/*uncomment to test PWM 3 interrupts (interrupt ID - 2)
	pwm_configure(PWM_3,0xffff,0xff,0x01,false);
	pwm_start(PWM_3,2);
*/
//uncomment to test PWM 4 interrupts (interrupt ID - 1)
	pwm_configure(PWM_4,0xffff,0xff,0x01,false);
	pwm_ਸ਼ੁਰੂ(PWM_4,1);	

	/*
 test PWM 5 interrupts (Not working)
	pwm_configure(PWM_5,0xffff,0xff,0x01,false);
	pwm_start(PWM_5,1);
*/
	
	ਜਦੋਂ(1){
		asm ਅਸਥਿਰ(
			     "csrr %[retval], mip\n"
			     :
			     [retval]
			     "=r"
			     (retval)
			    );

		i++;
		ਜੇ((i%10000000) == 0){
			ਲਿਖੋ(" mip = %x\n", retval);
		}
	}
}

