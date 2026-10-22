/***************************************************************************
 * Project           		: shakti devt board
 * Name of the file	     	: interrupt_demo.c
 * Brief Description of file    : A application to demonstrate working of plic
 * Name of Author    	        : Sathya Narayanan N
 * Email ID                     : sathya281@gmail.com

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
  @file interrupt_demo.c
  @brief A application to demonstrate working of plic
  @detail Thsi file contains an application to demonstrate the working of plic.
  The interrupts are enabled for a gpio pin. Once the button connected to the gpio
  pin is pressed. An interrupt is generated and it is handled by the isr.
 */

#அந்தர்பாவ "gpio.h"
#அந்தர்பாவ "uart.h"
#அந்தர்பாவ "utils.h"
#அந்தர்பாவ "traps.h"
#அந்தர்பாவ "platform.h"
#அந்தர்பாவ "plic_driver.h"
#அந்தர்பாவ "log.h"
#அந்தர்பாவ "defines.h"
#அந்தர்பாவ "memory.h"

வெறுமை handle_button_press(__attribute__((unused)) uint32_t இலக்கம்);

/** @fn handle_button_press
 * @brief a default handler to handle button press event
 * @param unsigned num
 * @return unsigned
 */
வெறுமை handle_button_press(__attribute__((unused)) uint32_t இலக்கம்)
{
	log_info("button pressed\n");

	/*
	   Assuming led is connected to GPIO1.
	   pin IO1 in pinaka
	   Set GPIO1 in GPIO_DIRECTION_CNTRL_REG to 1, for write.
	   Set GPIO1 to 1 to indicate output HIGH.
	 */

	write_word(GPIO_DIRECTION_CNTRL_REG, 0x0000002);
	write_word(GPIO_DATA_REG, 0x00FFFFFF);
}

/** @fn main
 * @brief sets up the environment for plic feature
 * @return int
 */
முழு முதன்மை(வெறுமை){
	பதிவு unsigned முழு retval;
	முழு i;

	//init plic module
	plic_init();

	//configure interrupt id 7
	configure_interrupt(PLIC_INTERRUPT_7);

	//set the corresponding isr for interrupt id 7
	isr_table[PLIC_INTERRUPT_7] = handle_button_press;

	// Enable Global (PLIC) interrupts.
	asm நிலையற்ற("li      t0, 8\t\n"
		     "csrrs   zero, mstatus, t0\t\n"
		    );

	// Enable Local (PLIC) interrupts.
	asm நிலையற்ற("li      t0, 0x800\t\n"
		     "csrrs   zero, mie, t0\t\n"
		    );

	asm நிலையற்ற(
		     "csrr %[retval], mstatus\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );

	log_debug("mstatus = %x\n", retval);

	asm நிலையற்ற(
		     "csrr %[retval], mie\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );

	log_debug("mie = %x\n", retval);

	asm நிலையற்ற(
		     "csrr %[retval], mip\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );

	log_debug("mip = %u\n", retval);

	போது(1){
		i++;

		எனில்((i%10000000) == 0){

			asm நிலையற்ற(
				     "csrr %[retval], mip\n"
				     :
				     [retval]
				     "=r"
				     (retval)
				    );
			log_debug("mip = %u\n", retval);
		}
	}
	திரும்பு 0;
}
