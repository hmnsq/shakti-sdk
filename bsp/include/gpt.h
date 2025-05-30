/************************************************************************
 * Project           		: shakti devt board
 * Name of the file	     	: gpt.h
 * Brief Description of file    : Header file for gpt.
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
 ************************************************************************/
/**
 * @file gpt.h
 * @project shakti devt board
 * @brief Header file for gpt
 */

#ifndef GPT_H
#define GPT_H
#include <stdint.h>
#include "platform.h"

#define GPT_STATUS_COMPLETE 0X8000
#define GPT_CLK_EN 0X01
/*
   gpt control register bit extraction macros
 */

//#define GPT_INPUT_CAPTURE        0x00008000  
//#define GPT_INPUT_CAPTURE_LOW        0x00000000   //for active low input capture 
//#define GPT_INPUT_CAPTURE_HIGH       0x00008000  // for  active high input capture 
#define GPT_CNTR_UNDERFLOW           0x00004000
#define GPT_CNTR_OVERFLOW            0x00002000
#define GPT_PWM_RISE                 0x00001000
#define GPT_PWM_FALL                 0x00000800
#define GPT_CNTR_UNDERFLOW_INTR_EN   0x00000400
#define GPT_CNTR_OVERFLOW_INTR_EN    0x00000200
#define GPT_PWM_RISE_INTR_EN         0x00000100
#define GPT_PWM_FALL_INTR_EN         0x00000080
#define GPT_CONTINUOUS_COUNT_EN      0x00000040
#define GPT_COUNT_RESET              0x00000020
#define GPT_OUT_EN                   0x00000010
#define GPT_MODE(x)                  (x << 2)
#define GPT_RESET                    0x00000002
#define GPT_EN                       0x00000001
#define GPT_CLK_EN                   0x00020000

#define GPT_INT_EN                   0x00000780 //Unknown define please change value

#define GPT_PRESCALE  0x0001fffe
#define GPT_CLKSRC    0X00000001
#define GPT_CLK_FRAME 0x01ffff

#define INT_CLK_REF 0
#define EXT_CLK_REF 1


/*
   GP Timer has four modes - a simple PWM mode, upcounter,
   down counter and up-down counter. The required mode is
   selected through GPTMODE bits in GPTCONTROL register.
 */

typedef enum{
	pwm         = 0x00000000,
	up_cntr     = 0x00000001,
	down_cntr   = 0x00000002,
	updown_cntr = 0x00000003
}gpt_modes_e;


typedef enum
{
	none      = 0x00000000,
	pwm_fall  = 0x00000080,
	pwm_rise  = 0x00000100,
	over_flow  = 0x00000200,
	under_flow = 0x00000400,
	updown    = 0x00000600
}gpt_int_e;


/* Struct to access GPT registers as 32 bit registers */
typedef struct
{
	volatile uint16_t  gpt_control;	         /*! gpt control register */
	volatile uint16_t  reserved;              /*! reserved for future use */
	volatile uint32_t  gpt_clk_control;       /*! gpt clock control register */
	volatile uint32_t  gpt_counter;	         /*! gpt counter register */
	volatile uint32_t  gpt_repeat_count;      /*! gpt repeat count register */
	volatile uint32_t  gpt_compare;           /*! gpt compare register */
	volatile uint32_t  gpt_count_reference;  /*! gpt count reference register */
	volatile uint32_t  gpt_capture;           /*! gpt capture register */
	volatile uint8_t   gpt_input_qual;        /*! gpt intput qualification register */
	volatile uint8_t  reserved0;              /*! reserved for future use */
	volatile int16_t  reserved1;              /*! reserved for future use */
	volatile uint8_t gpt_clk_en;
	volatile uint8_t  reserved2;
	volatile uint16_t  reserved3;
	
} gpt_struct;

extern gpt_struct *gpt_instance[GPT_MAX_COUNT];

void gpt_init(void);
void gpt_configure_clkctrl_reg(gpt_struct*, uint16_t, uint32_t,uint32_t);
void gpt_irq_handler(gpt_struct*, uintptr_t, uintptr_t);
void gpt_write_cntr_reg(gpt_struct*);
void gpt_enable_repeatcount(gpt_struct*);
void gpt_write_compare_reg(gpt_struct*, uint32_t);
void gpt_write_cntr_ref_reg(gpt_struct*,uint32_t);
void gpt_write_capture_reg(gpt_struct*,uint32_t);
void gpt_write_inputqual_reg(gpt_struct*,uint8_t);
void gpt_enable_interrupt(gpt_struct*,gpt_int_e);
void gpt_start(gpt_struct*);
void gpt_reset(gpt_struct*);
void gpt_isr_handler0(gpt_struct*);
void gpt_isr_handler1(gpt_struct*);
void gpt_isr_handler2(gpt_struct*);
void gpt_isr_handler3(gpt_struct*);
uint16_t gpt_read_ctrl_reg(gpt_struct*);
uint16_t gpt_get_prescaler(gpt_struct*);
uint32_t extract_bit_value(gpt_struct*, int);
uint32_t gpt_read_clkctrl_reg(gpt_struct*);
uint32_t gpt_get_clk_src(gpt_struct*);
uint32_t gpt_read_cntr_reg(gpt_struct*);
uint32_t gpt_read_repeatcount_reg(gpt_struct*);
uint32_t gpt_read_compare_reg(gpt_struct*);
uint32_t gpt_read_cntr_ref_reg(gpt_struct*);
uint32_t gpt_read_capture_reg(gpt_struct*);
uint32_t gpt_read_inputqual_reg(gpt_struct*);
uint64_t get_timer_value(void);
gpt_struct* gpt_get_instance(uint32_t);
gpt_struct*  gpt_configure_ctrl_reg(uint8_t, gpt_modes_e, gpt_int_e,uint16_t, uint8_t);
void gpt_configure_pwm_duty_period(gpt_struct * , uint32_t , uint32_t );
#endif
