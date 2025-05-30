/***************************************************************************
 * Project               	    		: shakti devt board
 * Name of the file	            		: gpt_dwncntrall.c
 * Brief Description of file            : implementing downcounter mode in gpt
 * Name of Author    	                : kotteeswaran
 * Email ID                             : kottee.1@gmail.com


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

uint8_t dwncntr_sts[2] = {0};

/** @fn gpt_timer_interrupt() 
 * @brief gpt timer interrupt for all gpt down counters
 * @details Gets the gpt instance, checks for the underflow interrupt, clear the count value and set the status variable.
 * @warning No warning
 * @param[in] interrupt id. 
 * @param[Out] returns 0
 */

unsigned gpt_timer_interrupt (unsigned num)
{
	gpt_struct* instance = NULL;
	//log_info("\tgpt pwm interrupt %d Occured\n", num);
	instance = gpt_instance[0];
	uint16_t status = instance->gpt_control;
	uint16_t status1 = status;	
	status = status & 0x87FF;
	uint16_t status_new = status;
	switch(num)
	{
		case 23:
		    instance = gpt_instance[0];
			if ( status1 & 0x4000 )
			{
				status_new |= 0x4000;
				if(status1 & 0x400)
				{
					dwncntr_sts[0] = 1;
					instance->gpt_control |= 0x20; // Reset counter
					instance->gpt_control &= 0xFFDF; //Disable reset counter
				}
			}
			instance->gpt_control = status_new;
			break;
		case 24:
		    instance = gpt_instance[1];
			if ( status1 & 0x4000 )
			{
				
				status_new |= 0x4000;
				if(status1 & 0x400)
				{
					dwncntr_sts[1] = 1;
					instance->gpt_control |= 0x20; // Reset counter
					instance->gpt_control &= 0xFFDF; //Disable reset counter
				}
			}
			instance->gpt_control = status_new;
			break;

			case 41:
		    instance = gpt_instance[2];
			if ( status1 & 0x4000 )
			{
				status_new |= 0x4000;
				if(status1 & 0x400)
				{
					dwncntr_sts[0] = 1;
					instance->gpt_control |= 0x20; // Reset counter
					instance->gpt_control &= 0xFFDF; //Disable reset counter
				}
			}
			instance->gpt_control = status_new;
			break;
		case 42:
		    instance = gpt_instance[3];
			if ( status1 & 0x4000 )
			{
				
				status_new |= 0x4000;
				if(status1 & 0x400)
				{
					dwncntr_sts[1] = 1;
					instance->gpt_control |= 0x20; // Reset counter
					instance->gpt_control &= 0xFFDF; //Disable reset counter
				}
			}
			instance->gpt_control = status_new;
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
	// plic_init();
	log_info("\n\n\n **** GPT DOWN COUNTER MODE UNDERFLOW INTERRUPT TEST CODE ****\n\n\n");
	instance = gpt_get_instance(module);
	printf("\n Clock Enable address is %x", instance);
	//instance->gpt_clk_control=GPT_CLK_EN;
	instance->gpt_clk_control=GPT_CLK_EN | 0x2000;//16 th bit enable in clk control reg and prescale value write for async reset
	printf("\nclk_enable in clk ctrl reg=%x",instance->gpt_clk_control);
#ifdef 	ALL
	for(module = MODULE_NO; module < 2; module ++)
#else
	module = MODULE_NO;
	printf("\ngpt %x module", module);
#endif
	{
		instance = gpt_configure_ctrl_reg(module,down_cntr,under_flow,10000, 0x0); //clk_src = 0 internal clock is used
		 printf("\n instance[%x]->gpt_clk_control1: %x",  module, instance->gpt_clk_control);
		instance->gpt_control |= 0x20; // Reset counter
		instance->gpt_control &= 0xFFDF; //Disable reset counter
		printf("\n after disable  %x", instance->gpt_control);
		configure_interrupt(PLIC_INTERRUPT_23 + module);
		isr_table[PLIC_INTERRUPT_23 + module] = gpt_timer_interrupt;
		instance->gpt_count_reference = 10000; //Disable reset counter
		enable_machine_global_interrupts();
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
			printf("\n instance[%x]->gpt_counter: %x",  module, instance->gpt_counter);	
		}
		if (1 == dwncntr_sts[0])
		{
			log_info("\n GPT 0 Underflow");
			dwncntr_sts[0] = 0;
		}
		if (1 == dwncntr_sts[1])
		{
			log_info("\n GPT 1 Underflow\n\n");
			dwncntr_sts[1] = 0;
		}
		if (1 == dwncntr_sts[2])
		{
			log_info("\n GPT 2 Underflow");
			dwncntr_sts[2] = 0;
		}
		if (1 == dwncntr_sts[3])
		{
			log_info("\n GPT 3 Underflow\n\n");
			dwncntr_sts[3] = 0;
		}
	}
	return 0;
}

