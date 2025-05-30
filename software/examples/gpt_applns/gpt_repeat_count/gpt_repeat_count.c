/***************************************************************************
 * Project               	    		: shakti devt board
 * Name of the file	            		: gpt_repeat_count.c
 * Brief Description of file            : example code for implementing continuous count.
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
#include  "platform.h"
#include <stddef.h>
#include "uart.h"
#define MODULE_NO 0
//#define ALL 1

/** @fn main() 
 * @brief main function that runs the code
 * @details runs the code
 * @warning No warning
 * @param[in] No input parameter 
 * @param[Out] No output parameter
 */
int main()
{
	gpt_struct* instance = NULL;
	uint8_t module = 0;
	// plic_init();
	gpt_init();
	log_info("\n ****GPT UP COUNTER REPEAT COUNT TEST **** \n");
	instance = gpt_get_instance(module);
	printf("\n Clock Ena address is %x", instance);
   	//instance->gpt_clk_control=GPT_CLK_EN;
	instance->gpt_clk_control=GPT_CLK_EN | 0x2000;//16 th bit enable in clk control reg and prescale value write for async reset
	printf("\nclk_enable in clk ctrl reg=%x",instance->gpt_clk_control);
#ifdef 	ALL
	for(module = MODULE_NO; module < 4; module ++)
#else
	module = MODULE_NO;
	
#endif
	{
		instance = gpt_configure_ctrl_reg(module, up_cntr,none, 10000, 0x0); //clk_src = 0 internal clock is used
		printf("\n instance[%x]->gpt_clk_control1: %x",  module, instance->gpt_clk_control);
		instance->gpt_control |= 0x20; // Reset counter
		instance->gpt_control &= 0xFFDF; //Disable reset counter
		printf("\n after disable  %x", instance->gpt_control);
		gpt_enable_repeatcount(instance);	//for enabling repeat count (in continuous count mode)
		instance->gpt_count_reference = 10000; //Disable reset counter
		gpt_start(instance);	
	}
	module = MODULE_NO;
	while(1)
	{
#ifdef 	ALL
	for(module = MODULE_NO; module < 4; module ++)
#else
	module = MODULE_NO;
#endif
		{
			gpt_struct* instance = gpt_instance[module];	
			printf("\ninstance[%x]->gpt_counter: %x",  module, instance->gpt_counter);
			printf("\ninstance[%x]->gpt_repeat_count: %x\n\n\n",  module, instance->gpt_repeat_count);
		}	
	}
	return 0;
}
