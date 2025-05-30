/***************************************************************************
 * Project           		: shakti devt board
 * Name of the file	     	: gpt_driver.c
 * Brief Description of file    : source file for gpt.
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

 You should have reved a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
 ***************************************************************************/

/**
@file   gpt.c
@brief  Contains the driver routines for general purporse timer .
@detail The gpt driver helps in controlling all the general purporse timers.
This file contains all the function definitions for General Purpose Timer driver.
*/

#include "gpt.h"
#include "log.h"
#include "defines.h"

gpt_struct *gpt_instance[GPT_MAX_COUNT];

/** @fn gpt_init()
 * @brief initializes the gpt instances with the gpt counter's base address
 * @param[in]  none
 * @param[Out] none
 */
void gpt_init()
{
	int i=0;

	for(i=GPT_MAX_COUNT-1; i>=0; i--)
	gpt_instance[i] = GPT_BASE_ADDRESS + i*GPT_OFFSET;
	//printf("\ngpt_instance[%x]: %x", i, gpt_instance[i]);
}

/** @fn gpt_read_ctrl_reg 
 * @brief This function returns the value of gpt control register
 * @param[gpt_instance *n]
 * @param[uint16_t]
 */

gpt_struct* gpt_get_instance(uint32_t module_number)
{
	gpt_struct* instance = gpt_instance[module_number];
	//printf("\n gpt[%x]: %x", module_number, gpt_instance[module_number]) ;
	return (instance);
}

/** @fn gpt_read_ctrl_reg 
 * @brief This function returns the value of gpt control register
 * @param[gpt_instance *n]
 * @param[uint16_t]
 */
uint16_t gpt_read_ctrl_reg(gpt_struct *instance)
{
	return (instance->gpt_control);
}


/** @fn gpt_configure_pwm_duty_period
 * @brief This function, configures duty and period inpwm mode.
 * @details The gpt control register is configured in the following way
 * @param[uint32_t period, uint32_t duty]
 * @param[void function]
 */
void gpt_configure_pwm_duty_period(gpt_struct *instance, uint32_t period, uint32_t duty)
{
	gpt_write_cntr_ref_reg(instance, period);
	gpt_write_compare_reg(instance, duty);
//	printf("\n count ref value[%x]: %x", instance, instance->gpt_count_reference);
//	printf("\n compare value[%x]: %x", instance, instance->gpt_compare);
}


/** @fn gpt_configure_ctrl_reg
 * @brief This function, configures teh control reg for different modes
 * @details The gpt control register is configured in the following way
 *       1 Extract the instance id of the counter.
 *       2 set the mode for the instance
 *       3 enable interrupts for the mode
 *       4 set the clock by configuring clock register
 *       5 set the counter reference register, if needed
 *       6 enable gpt in the gpt control register.
 * @param[int,gpt_mode_e,gpt_int_e int_mode,uint8_t]
 * @param[uint8_t]
 */
gpt_struct* gpt_configure_ctrl_reg(uint8_t module, gpt_modes_e mode, gpt_int_e int_mode, uint16_t prescale, uint8_t clk_src)
{
	gpt_struct* instance = gpt_instance[module];
	printf("\nMODE selected:%x-",mode);
	printf("\n123");
	printf("\ninstance value: %x",instance);
	//instance->gpt_clk_control=GPT_CLK_EN;
	instance->gpt_control |= (mode << 2);
	printf("\n321");
	switch (mode)
	{
	case pwm:
		printf("\npwm mode");
		gpt_configure_clkctrl_reg(instance, prescale,clk_src,GPT_CLK_EN);
		break;
	case up_cntr:
		printf("up_cntr mode");
		gpt_configure_clkctrl_reg(instance, prescale,clk_src,GPT_CLK_EN);
		break;
	case down_cntr:
		printf("\ndown_cntr mode");
		gpt_configure_clkctrl_reg(instance, prescale,clk_src,GPT_CLK_EN);
		break;
	case updown_cntr:
		printf("\nupdown_cntr mode");
		gpt_configure_clkctrl_reg(instance, prescale,clk_src,GPT_CLK_EN);
		break;
	default:
		log_fatal("\nTrying to configure an unsupported mode");
		break;
	}
	
	printf("\ngpt_control after setting mode = %x",instance->gpt_control);
	if(int_mode != 0)
	{
		instance->gpt_control = (instance->gpt_control & ~GPT_INT_EN) | int_mode;
	}
	return instance;
}



/** @fn gpt_irq_handler
 * @brief This function handles the interrupts coming for gpt
 * @param[in] gpt_struct*,uintptr_t
 * @param[Out] none
 */
void gpt_irq_handler(gpt_struct* instance,uintptr_t int_id, uintptr_t epc)
{
	log_trace("\nmach_gpt_handler entered\n");
	uint32_t  interrupt_id;
	//log_info("gpt_control =%x\n",instance->gpt_control);
	log_trace("mach_gpt_handler exited\n");
}

/** @fn extract_bit_value 
 * @brief Given the position of a bit, the function extracts the value of a bit in register. 
 * @param[in] int 
 * @param[Out] uint32_t
 */
uint32_t extract_bit_value(gpt_struct* instance, int position)
{
	uint32_t value = 0;
	value = instance->gpt_clk_control & position;
	return value;
}

/** @fn gpt_configure_clkctrl_reg
 * @brief This function configures the clock for the gpt. 
 * @detail This function configures the clock source for GPT. The clock source
 * can be internal or external. Next. the prescaler value is also set up here.
 * @param[in] gpt_struct*,uint16_t,uint32_t
 * @param[Out] none
 */
void gpt_configure_clkctrl_reg(gpt_struct* instance, uint16_t prescale , uint32_t clk_src, uint32_t enable)
{
	uint32_t value = 0;
	value = (prescale << 1) | clk_src | enable;
	printf("instance->gpt_clk_control: %x\n", instance->gpt_clk_control);
	printf("1111\n");
	instance->gpt_clk_control = value;
	printf("instance->gpt_clk_control: %x\n", instance->gpt_clk_control);
	printf("\n");
}

/** @fn gpt_read_clkctrl_reg
 * @brief This function reads the value of clock control register and returns
 * it.
 * @param[in] gpt_struct
 * @param[Out] uint32_t
 */
uint32_t gpt_read_clkctrl_reg(gpt_struct* instance)
{
	return instance->gpt_clk_control;
}

/** @fn gpt_get_prescaler
 * @brief This function extracts the prescaler value from gpt clock control register and returns it.
 * @param[in] gpt_struct*
 * @param[Out] uint16_t
 */
uint16_t gpt_get_prescaler(gpt_struct* instance)
{
	return ((instance->gpt_clk_control & GPT_PRESCALE ) >> 1);
}

/** @fn gpt_get_clk_src
 * @brief This function extracts the clock source information from got clock
 * control register and returns it.
 * @detail The lsb of clock control register maintains the clock source.
 *	 0 - internal clock
 *	 1 - external clocl
 * @param[in] gpt_struct*
 * @param[Out] uint32_t
 */
uint32_t gpt_get_clk_src(gpt_struct* instance)
{
	return (instance->gpt_clk_control & GPT_CLKSRC);
}

/** @fn gpt_read_cntr_reg
 * @brief This function reads the gpt counter register and returns the value 
 * @param[in] gpt_struct*
 * @param[Out] uint32_t
 */
uint32_t gpt_read_cntr_reg(gpt_struct* instance)
{
	return instance->gpt_counter;
}


/** @fn gpt_read_repeatcount_reg
 * @brief This function reads the repeat counter register and returns the value 
 * @param[in] gpt_struct*
 * @param[Out] uint32_t
 */
uint32_t gpt_read_repeatcount_reg(gpt_struct* instance)
{
	return instance->gpt_repeat_count;
}

/** @fn gpt_read_compare_reg
 * @brief This function reads the compare register and returns the value
 * @param[in] gpt_struct*
 * @param[Out] uint32_t
 */
uint32_t gpt_read_compare_reg(gpt_struct* instance)
{
	return instance->gpt_compare;
}


/** @fn gpt_read_cntr_ref_reg
 * @brief This function reads the counter reference register and returns the value
 * @param[in] gpt_struct*
 * @param[Out] uint32_t
 */
uint32_t gpt_read_cntr_ref_reg(gpt_struct* instance)
{
	return instance->gpt_count_reference;
}

/** @fn gpt_read_capture_reg
 * @brief This function reads the capture register and returns the value
 * @param[in] gpt_struct*
 * @param[Out] uint32_t
 */
uint32_t gpt_read_capture_reg(gpt_struct* instance)
{
	return instance->gpt_capture;
}

/** @fn gpt_read_inputqual_reg
 * @brief This function reads the intput qualification register and returns the value
 * @param[in] gpt_struct*
 * @param[Out] uint32_t
 */
uint32_t gpt_read_inputqual_reg(gpt_struct* instance)
{
	return instance->gpt_input_qual;
}
/** @fn gpt_write_compare_reg
 * @brief This function writes the 'value' into the compare register.
 * @param[in] gpt_struct*
 * @param[Out] none
 */
void gpt_write_compare_reg(gpt_struct* instance, uint32_t value)
{
	instance->gpt_compare = value;
}

void gpt_write_clken_reg(gpt_struct* instance, uint8_t value)
{
	instance->gpt_clk_en = value;
}

/** @fn gpt_write_cntr_ref_reg
 * @brief This function writes the 'value' into the counter reference register.
 * @param[in] gpt_struct*,uint32_t
 * @param[Out] none
 */
void gpt_write_cntr_ref_reg(gpt_struct* instance, uint32_t value)
{
	instance->gpt_count_reference = value;
}

/** @fn gpt_write_inputqual_reg
 * @brief This function writes the 'value' into the input qualification register.
 * @brief 
 * @detail
 * @warning   
 * @param[in] gpt_struct*,uint8_t
 * @param[Out] none
 */
void gpt_write_inputqual_reg(gpt_struct* instance, uint8_t value)
{
	instance->gpt_input_qual = value;
}

/** @fn gpt_enable_interrupt  
 * @brief This function enables the interrupt bit corresponding to 'value' in the
 * function call.
 * @param[in] gpt_struct*,int_mode_e 
 * @param[Out] none
 */
void gpt_enable_interrupt(gpt_struct* instance, gpt_int_e value)
{
	instance->gpt_control |= value ;
}

/** @fn gpt_start 
 * @brief This function sets the enable bit to high in the gpt control register.
 * @param[in] gpt_struct* 
 * @param[Out] none
 */
void gpt_start(gpt_struct* instance)
{
	instance->gpt_control |= (GPT_EN | GPT_OUT_EN) ;
	//printf("gpt_control = %x",instance->gpt_control);
	//printf("\n");
}

/** @fn gpt_reset
 * @brief This function resets the gpt by writing into gpt control register
 * @param[in] gpt_struct*
 * @param[Out] none
 */
void gpt_reset(gpt_struct* instance)
{
	instance->gpt_control |= GPT_RESET;
}

void gpt_stop(gpt_struct* instance)
{
	instance->gpt_control |= GPT_RESET;
	instance->gpt_control &= ~(GPT_EN | GPT_OUT_EN);
}
void gpt_enable_repeatcount(gpt_struct* instance)
{
	instance->gpt_control |= GPT_CONTINUOUS_COUNT_EN;
}

void gpt_isr_handler0(gpt_struct* instance)
{

	printf("entered the gpt handler");

	if(!(instance->gpt_control & GPT_CONTINUOUS_COUNT_EN))
	{
		instance->gpt_control |= GPT_COUNT_RESET;
	}
}

void gpt_isr_handler1(gpt_struct* instance)
{
	printf("entered the gpt handler");

	if(!(instance->gpt_control & GPT_CONTINUOUS_COUNT_EN))
	{
		instance->gpt_control |= GPT_COUNT_RESET;
	}
 }

void gpt_isr_handler2(gpt_struct* instance)
{
	printf("entered the gpt handler");

	if(!(instance->gpt_control & GPT_CONTINUOUS_COUNT_EN))
	{
		instance->gpt_control |= GPT_COUNT_RESET;
	}
 }

void gpt_isr_handler3(gpt_struct* instance)
{
	printf("entered the gpt handler");

	if(!(instance->gpt_control & GPT_CONTINUOUS_COUNT_EN))
	{
		instance->gpt_control |= GPT_COUNT_RESET;
	}
 }
