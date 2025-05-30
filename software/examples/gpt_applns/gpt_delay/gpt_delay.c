/***************************************************************************
 * Project           			        : shakti devt board
 * Name of the file	     		        : gpt_delay.c
 * Brief Description of file            : implemeting different delay for gpt
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
#include <stddef.h>
#include "traps.h"
#include "platform.h"
#include "plic_driver.h"
#include "log.h"
#include "defines.h"
#include "pinmux.h"
#include "gpiov2.h"
#include "gpt.h"
#include "uart.h"
// #define ALL 1

#define MODULE_NO 0


/** @fn handle_button_press 
 * @brief 
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
uint8_t period_counter=0;
 uint8_t timer_intr_flag;
unsigned gpt_timer_interrupt (unsigned num)
{
	gpt_struct* instance = NULL;
	instance = gpt_instance[0];	
	    gpiov2_instance->toggle  = GPIO0;
	    gpiov2_instance->toggle = 0;
		period_counter++;
		if(period_counter>=10)
		{
			gpt_stop(instance);
			timer_intr_flag = 1;
			period_counter=0;
		}	
			
}

// Function to generate a delay in microseconds
void delay_us(uint32_t delay) {

	timer_intr_flag=0;
    config_gpt(0, delay,GPT_CLK_EN);
	while (!timer_intr_flag) {
       
    }
    }

// Function to generate a delay in milliseconds
void delay_ms(uint32_t delay) {
	
	timer_intr_flag=0;
	config_gpt(1, delay,GPT_CLK_EN);
	while (!timer_intr_flag) {
       
    }
   
}

// Function to generate a delay in seconds(2 sec)
void delay_seconds(uint32_t delay) {
	timer_intr_flag=0;
	config_gpt(2, delay,GPT_CLK_EN);
	while (!timer_intr_flag){
		
    }
    
}

void config_gpt(int delay_mode, uint32_t delay_value,uint32_t clk_en)
{
	gpt_struct* instance = NULL;
	uint32_t count_value=0;
	instance = gpt_instance[0];
	log_debug("\nconfig gpt function entered");
	{
			if (delay_mode == 0) {
				printf("d=%d",delay_value);
			// Microseconds
			log_info("\nif loop entered 0");
			instance->gpt_clk_control =(clk_en |(4 << 1)); 
			log_info("\ntest 0"); 
			count_value = 10 * delay_value; 
			log_info("\n c=%d",count_value);
			printf("\n counter_value=%x", instance->gpt_count_reference);   
			instance->gpt_count_reference = count_value;
			log_info("\ntest 1");  
			instance->gpt_compare = (1 * delay_value) / 2;
			log_info("\ntest 2"); 
		} else if (delay_mode == 1) {
			
			// Milliseconds
			log_info("\nif loop entered 1");
			printf("d=%d",delay_value);
			instance->gpt_clk_control = (clk_en |(49 << 1));         
			printf("\n Configured Clock");
			instance->gpt_count_reference = (1000 * delay_value);  
			instance->gpt_compare = (1000 * delay_value) / 2;
			printf("\n Configured Count Ref");
		} else if(delay_mode == 2) {
			
			// Seconds
			log_info("\nif loop entered 2");
			printf("\n d=%d",delay_value);       
			printf("\n Configured Clock");
			instance->gpt_clk_control = (clk_en |(499 << 1));        
			instance->gpt_count_reference = (100000 * delay_value);  
			printf("\n Configured Count Ref");  
		}else{
			log_debug("\nunsupported mode");
		}
		instance->gpt_control = 0x254;
		printf("\n configure control");
		printf("\ncounter_value=%x",instance->gpt_count_reference);
		printf("\nclock_value=%x",instance->gpt_clk_control);
		gpt_start(instance);
		printf("\n Starting GPT");
	}
	
}


/** @fn main 
 * @brief 
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
int main(void){
	uint8_t module = 0;
gpt_struct* instance = NULL;
 gpiov2_init();
  	gpt_init();
    // plic_init();
	log_info("\n ****GPT UP COUNTER OVERFLOW TEST CODE**** \n");
    instance = gpt_get_instance(module);
	printf("\n Clock Ena address is %x", instance);
    instance->gpt_clk_control=GPT_CLK_EN;//16 th bit enable in clk control reg
	printf("\nclk_enable in clk ctrl reg=%x",instance->gpt_clk_control);
    gpiov2_instance->direction = GPIO0;
	printf("\n gpiov2_instance->direction: %x", gpiov2_instance->direction);
	
	instance->gpt_count_reference = 10000;
	printf("counter_value=%x", instance->gpt_count_reference);
	configure_interrupt(PLIC_INTERRUPT_23);
	isr_table[PLIC_INTERRUPT_23] = gpt_timer_interrupt;
	enable_machine_global_interrupts();
	delay_us(100);
	delay_ms(100);
	delay_seconds(2);
	printf("counter_value=%x", instance->gpt_count_reference);
	printf("clock_value=%x",instance->gpt_clk_control);
	while(1);
	return 0;
}