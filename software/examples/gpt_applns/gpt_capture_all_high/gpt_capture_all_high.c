/***************************************************************************
 * Project               	    		:  shakti devt board
 * Name of the file	            		:  gpt_capture_all.c
 * Brief Description of file            :  check the functionality of GPT capture mode when set to active high
 * Name of Author    	                :  Kotteeswaran
 * Email ID                              : kottee.off@gmail.com
 *
 * Copyright (C) 2019  IIT Madras. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 ****************************************************************************/

#include "gpt.h"
#include "plic_driver.h"
#include "gpiov2.h"
#include "pinmux.h"
#include "platform.h"
#include <stddef.h>
#include "uart.h"
#define MODULE_NO 0
#define ALL 1



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
	printf("capture high test code\n");
	// plic_init();
	gpt_init();		
	instance = gpt_get_instance(module);
	printf("\n Clock Ena address is %x", instance);
   	//instance->gpt_clk_control=GPT_CLK_EN;
	instance->gpt_clk_control=GPT_CLK_EN | 0x2000;//16 th bit enable in clk control reg and prescale value write for async reset
	printf("\nclk_enable in clk ctrl reg=%x",instance->gpt_clk_control);
#ifdef 	ALL
	for(module = MODULE_NO; module < GPT_MAX_COUNT; module ++)
#else
	module = MODULE_NO;
#endif	
{
		instance = gpt_configure_ctrl_reg(module, up_cntr,none, 10000, 0x0); //clk_src = 0 internal clock is used
		printf("\n instance[%x]->gpt_clk_control1: %x",  module, instance->gpt_clk_control);
		instance->gpt_control |= 0x20; // Reset counter
		instance->gpt_control &= 0xFFDF; //Disable reset counter
		printf("\n after disable  %x", instance->gpt_control);
		instance->gpt_count_reference = 10000; //Disable reset counter
		printf("\n instance[%x]->gpt_control1: %x",  module, instance->gpt_control);
		instance->gpt_control = 0x8075;
		printf("\n after instance[%x]->gpt_control1: %x",  module, instance->gpt_control);
		gpt_start(instance);
}

	module = MODULE_NO;
	while(1)
	{
#ifdef 	ALL
	for(module = MODULE_NO; module < GPT_MAX_COUNT; module ++)
#else
	module = MODULE_NO;
#endif
		{
			gpt_struct* instance = gpt_instance[module];
			printf("\n instance[%x]->gpt_counter: %x",  module, instance->gpt_counter);
			printf("\n instance[%x]->gpt_capture: %x\n\n",  module, instance->gpt_capture);
			delay_loop(1000,1000);
		}


	}
	return 0;
}

