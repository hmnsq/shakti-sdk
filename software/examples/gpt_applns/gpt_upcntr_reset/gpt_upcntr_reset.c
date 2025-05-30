/***************************************************************************
 * Project               	    		:  shakti devt board
 * Name of the file	            		:  gpt_upcntr_reset.c
 * Brief Description of file             : example for upcounter reset for gpt
 * Name of Author    	                :  kotteeswaran
 * Email ID                              : kottee.1@gmail.com

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

#include "gpt.h"
#include "plic_driver.h"
#include "platform.h"
#include <stddef.h>
#include "uart.h"
#define MODULE_NO 0
#define ALL 1

uint8_t upcntr_sts[2] = {0};


/** @fn gpt_timer_interrupt() 
 * @brief gpt timer interrupt for all gpt up counters
 * @details Gets the gpt instance, checks for the overflow interrupt, clear the count value and set the status variable.
 * @warning No warning
 * @param[in] interrupt id. 
 * @param[Out] returns 0
 */
unsigned gpt_timer_interrupt (unsigned num)
{
	gpt_struct* instance = NULL;
	log_info("\tgpt interrupt %x Occured\n", num);

	switch(num)
	{
		case 23:
			instance = gpt_instance[0];
			if ( instance->gpt_control & 0x2000 )
			{
				//printf(" \n\n interrupt isr called******\n\n");
				upcntr_sts[0] = 1;
				instance->gpt_control |= 0x20; // Reset counter
				instance->gpt_control &= 0xFFDF; //Disable reset counter
			}
			break;
			
		case 24:
		    instance = gpt_instance[1];
			if ( instance->gpt_control & 0x2000 )
			{
				//printf(" \n\n$$$$ module 1 interrupt isr called******\n\n");
				upcntr_sts[1] = 1;
				instance->gpt_control |= 0x20; // Reset counter
				instance->gpt_control &= 0xFFDF; //Disable reset counter
			}
			break;
			
	}
	return 0;
}

/** @fn main() 
 * @brief main function that runs the code
 * @details runs the code
 * @warning No warning
 * @param[in] No input parameter 
 * @param[Out] No output parameter
 */
int main()
{
	uint8_t module = 0;
	gpt_struct* instance = NULL;
		gpt_init();
		log_info("\n ****GPT COUNTER RESET TEST CODE**** \n");
		instance = gpt_get_instance(module);
		printf("\n Clock Ena address is %x", instance);
		//instance->gpt_clk_en=GPT_CLK_EN;
    	instance->gpt_clk_control=GPT_CLK_EN;//16 th bit enable
		printf("\nclk_enable in clk ctrl reg=%x",instance->gpt_clk_control);
	

#ifdef 	ALL
	for(module = MODULE_NO; module < 2; module ++)
#else
	module = MODULE_NO;
#endif
		{
			instance = gpt_configure_ctrl_reg(module, up_cntr,none, 0x0, 0x0); //clk_src = 0 internal clock is used
			printf("\n instance[%x]->gpt_clk_control1: %x",  module, instance->gpt_clk_control);
			instance->gpt_control |= 0x20; 
			printf("\n after disable  %x", instance->gpt_control);
			// 	isr_table[PLIC_INTERRUPT_11 + module] = 	gpt_timer_interrupt;
			// configure_interrupt(PLIC_INTERRUPT_11 + module);
			//enable_machine_global_interrupts();
			instance->gpt_count_reference = 100000; 
			gpt_start(instance);
		}

	module = MODULE_NO;
	while(1)
	{
#ifdef 	ALL
	for(module = MODULE_NO; module < 2; module ++)
#else
	module = MODULE_NO;
#endif
		{
			
			gpt_struct* instance = gpt_instance[module];
			
			log_debug("\n instance[%x]->gpt_control: %x", module, instance->gpt_control);
			printf("\n instance[%x]->gpt_counter: %x",  module, instance->gpt_counter);
			instance->gpt_control |= 0x0275;
		}
		// log_debug("\n\n");
		// if(1 == upcntr_sts[0] )
		// {
		// 	printf("\n GPT 0 Overflow");
		// 	upcntr_sts[0] = 0;
		// }
		// if(1 == upcntr_sts[1] )
		// {
		// 	printf("\n GPT 1 Overflow");
		// 	upcntr_sts[1] = 0;
		// }

		// delay_loop(6000, 1000);
	}

	return 0;
}

        