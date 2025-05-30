/***************************************************************************
 * Project               	    		: GPT PWM Testcase
 * Name of the file	            		: gpt_pwm_sim.c
 * Brief Description of file            : verify the PWM mode functionality in simulation.

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
#include "pinmux.h"
#include <stddef.h>
#include "uart.h"
#define ALL 1
//#define MODULE_NO 1
#define GPT_TIMER0_INTERRUPT PLIC_INTERRUPT_23

unsigned gpt_pwm_interrupt (unsigned num)
{
	gpt_struct* instance = NULL;
	uint16_t status;
    uint16_t status1;
    uint16_t status_new;
	//log_info("\tgpt pwm interrupt %d Occured\n", num);
switch(num)
	{
	case GPT_TIMER0_INTERRUPT + 0:
		instance = gpt_instance[0];
		status = instance->gpt_control;
		status1 = status;	
		status = status & 0x87FF;
		status_new = status;
		if(status1 & 0x800)
		{
			status_new |= 0x800;
			if(status1 & 0x80)
			{
				instance->gpt_control &= 0xF7FF;
				printf("\n GPT %x fall", num);//DisablePWM fall int 
			}
		}
		if ( status1 & 0x1000 )
		{
			status_new |= 0x1000;
			if(status1 & 0x100)
			{
				instance->gpt_control &= 0xEFFF; //
				printf("\n GPT %x rise", num);
			}
		}
		instance->gpt_control = status_new;
		break;
	case GPT_TIMER0_INTERRUPT + 1:
		instance = gpt_instance[1];
		status = instance->gpt_control;
		status1 = status;	
		status = status & 0x87FF;
		status_new = status;
		if(status1 & 0x800)
		{
			status_new |= 0x800;
			if(status1 & 0x80)
			{
				instance->gpt_control &= 0xF7FF; //DisablePWM fall int
				printf("\n GPT %x fall", num);	
			}
		}
		if ( status1 & 0x1000 )
		{
			status_new |= 0x1000;
			if(status1 & 0x100)
			{
				instance->gpt_control &= 0xEFFF; //DisablePWM rise int
				printf("\n GPT %x rise", num);
			}
		}
		instance->gpt_control = status_new;
		break;
	case GPT_TIMER0_INTERRUPT + 2:
		instance = gpt_instance[2];
		status = instance->gpt_control;
		status1 = status;	
		status = status & 0x87FF;
		status_new = status;
		if(status1 & 0x800)
		{
			status_new |= 0x800;
			if(status1 & 0x80)
			{
				instance->gpt_control &= 0xF7FF; //DisablePWM fall int
				printf("\n GPT %x fall", num);	
			}
			}
		if ( status1 & 0x1000 )
		{
			status_new |= 0x1000;
		    if(status1 & 0x100)
			{
				instance->gpt_control &= 0xEFFF; //DisablePWM rise int
				printf("\n GPT %x rise", num);
			}
		}
		instance->gpt_control = status_new;
		break;
	case GPT_TIMER0_INTERRUPT + 3:
		instance = gpt_instance[3];
		status = instance->gpt_control;
	  	status1 = status;	
		status = status & 0x87FF;
		status_new = status;
		if(status1 & 0x800)
		{
			status_new |= 0x800;
			if(status1 & 0x80)
			{
				instance->gpt_control &= 0xF7FF; //DisablePWM fall int
				printf("\n GPT %x fall", num);	
			}
		}
		if ( status1 & 0x1000 )
		{
			status_new |= 0x1000;
			if(status1 & 0x100)
			{
				instance->gpt_control &= 0xEFFF; //DisablePWM rise int
				printf("\n GPT %x rise", num);
			}
		}
		instance->gpt_control = status_new;
		break;
	
	return 0;
	}
}

int main()
{
	uint8_t module = 0;
	uint16_t int_id = GPT_TIMER0_INTERRUPT;
	gpt_struct* instance = NULL;
	gpt_init();
  	// plic_init();
	log_info("\n\n\n **** GPT PWM FUNCTIONALITY TEST CODE ****\n\n\n");
	#ifdef 	ALL
	for(module = 0; module < GPT_MAX_COUNT; module ++)
#else
	module = MODULE_NO;
	printf("\ngpt %x module", module);
#endif
	{
	instance = gpt_get_instance(module);
	printf("\n Clock Ena address is %x", instance);
    //instance->gpt_clk_control=GPT_CLK_EN;
	instance->gpt_clk_control=GPT_CLK_EN | 0x2000;//16 th bit enable in clk control reg and prescale value write for async reset
	printf("\nclk_enable in clk ctrl reg=%x",instance->gpt_clk_control);
	}
	//while(1);
#ifdef 	ALL
	for(module = 0; module < GPT_MAX_COUNT; module ++)
#else
	module = MODULE_NO;
	printf("\ngpt %x module", module);
#endif
	{
	printf("\n In GPT PWM mode");
	instance = gpt_configure_ctrl_reg(module, pwm,pwm_rise | pwm_fall,0x1000, 0x0); //clk_src = 0 internal clock is used
	printf("\n instance[%x]->gpt_clk_control1: %x",  module, instance->gpt_clk_control);
	printf("\n after disable  %x", instance->gpt_control);
	instance->gpt_control |= 0x20; // Reset counter
	instance->gpt_control &= 0xFFDF; //Disable reset counter
	isr_table[int_id] = gpt_pwm_interrupt;
	configure_interrupt(int_id);
	int_id++;
    // configure_interrupt(PLIC_INTERRUPT_39 + module);
	// isr_table[PLIC_INTERRUPT_39 + module] = gpt_pwm_interrupt;
	instance->gpt_count_reference = 100;//cycle period is set
	instance->gpt_compare = 50;//Duty cycle of the pulse is set 
	enable_machine_global_interrupts();
    gpt_start(instance);
	}
// 	#ifdef 	ALL
// 		for(module = 0; module < 4; module ++)
// #endif
// 		{
// 			gpt_struct* instance = gpt_instance[module];
// 			gpt_start(instance);
// 		}
  return 0;
}
