/***************************************************************************
 * Project           		: shakti devt board
 * Name of the file	     	: plic_driver.c
 * Brief Description of file    : source file for plic.
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
  @file plic_driver.c
  @brief source file for plic driver
  @detail This file contains the driver code for plic device. The functions to
  setup each plic registers, isr routine and plic interrupt handler are here.
 */

#ضمن "pwm_driver.h"
#ضمن "plic_driver.h"
#ضمن "platform.h"
#ضمن "log.h"
#ضمن "stddef.h"
#ضمن "gpio.h"
#ضمن "utils.h"

/*
   Global interrupt data maintenance structure
 */

plic_fptr_t isr_جدول[PLIC_MAX_وقفه_SRC];
وقفه_داده_t hart0_وقفه_ماتریس[PLIC_MAX_وقفه_SRC];

/** @fn void interrupt_complete(uint32_t interrupt_id)
 * @brief write the int_id to complete register
 * @details Signals completion of interrupt. From s/w side the interrupt claim/complete register is written with the interrupt id.
 * @param uint32_t interrupt_id
 */
فراغ وقفه_complete(uint32_t وقفه_id)
{
	log_trace("\ninterrupt_complete entered\n");

	uint32_t *claim_addr =  (uint32_t *) (PLIC_پایه_آدرس +
					      PLIC_CLAIM_جابه_جایی);

	*claim_addr = وقفه_id;
	hart0_وقفه_ماتریس[وقفه_id].state = SERVICED;
	hart0_وقفه_ماتریس[وقفه_id].شمار++;

	log_debug("interrupt id %d, state changed to %d\n", وقفه_id,
		  hart0_وقفه_ماتریس[وقفه_id].state);

	log_debug("وقفه id = %x \n reset مقصد افتراضي مقادیر state = %x \
		  \n اولویت = %x\n شمار = %x\n", \
		  hart0_وقفه_ماتریس[وقفه_id].id, \
		  hart0_وقفه_ماتریس[وقفه_id].state, \
		  hart0_وقفه_ماتریس[وقفه_id].اولویت, \
		  hart0_وقفه_ماتریس[وقفه_id].شمار);

	log_trace("interrupt_complete exited\n");
}

/** @fn uint32_t interrupt_claim_request()
 * @brief know the id of the interrupt
 * @details read the interrupt claim register to know the interrupt id
 *           of the highest priority pending interrupt
 * @return uint32_t
 */
uint32_t وقفه_claim_request()
{
	uint32_t *وقفه_claim_آدرس = عدم;
	uint32_t وقفه_id;

	log_trace("\ninterrupt_claim_request entered\n");

	/*
	   return the interrupt id. This will be used to index into the plic isr table.
	   From the isr table, the exact isr will be called

	   refer https://gitlab.com/shaktiproject/uncore/devices/blob/master/plic/plic.bsv as on 26/8/2019
	 */

	وقفه_claim_آدرس = (uint32_t *)(PLIC_پایه_آدرس +
					       PLIC_CLAIM_جابه_جایی);

	وقفه_id = *وقفه_claim_آدرس;

	log_debug("interrupt id [%x] claimed  at address %x\n", وقفه_id,
		  وقفه_claim_آدرس );

	log_trace("interrupt_claim_request exited\n");

	أرجع وقفه_id;
}

/** @fn void mach_plic_handler(uintptr_t int_id, uintptr_t epc)
 * @brief handle machine mode plic interrupts
 * @details find the int id that caused of interrupt, 
 *	    process it and complete the interrupt.
 * @param uintptr_t int_id
 * @param uintptr_t epc
 */
فراغ mach_plic_handler( __attribute__((استفادهنشده)) uintptr_t int_id, __attribute__((استفادهنشده)) uintptr_t epc)
{
	uint32_t  وقفه_id;

	log_trace("\nmach_plic_handler entered\n");

	وقفه_id = وقفه_claim_request();

	log_debug("interrupt id claimed = %x\n", وقفه_id);

	إذا (وقفه_id <= 0 || وقفه_id > PLIC_MAX_وقفه_SRC)
	{
		log_fatal("Fatal error, interrupt id [%x] claimed is wrong\n", وقفه_id);
	}

	/*
	   clear IP bit ?

	   After the highest-priority pending interrupt is claimed by a target and the corresponding
	   IP bit is cleared, other lower-priority pending interrupts might then become visible to
	   the target, and so the PLIC EIP bit might not be cleared after a claim

	   reference - risc v priv spec v1.10 section 7.10 Interrupt Claims
	 */

	/*change state to active*/
	hart0_وقفه_ماتریس[وقفه_id].state = فعال;

	log_debug("interrupt id %d, state changed to %d\n",
		  وقفه_id,hart0_وقفه_ماتریس[وقفه_id].state);

	/*call relevant interrupt service routine*/
	isr_جدول[وقفه_id](وقفه_id);

	وقفه_complete(وقفه_id);

	log_debug("interrupt id %d complete \n", وقفه_id);

	log_trace("\nmach_plic_handler exited\n");
}

/** @fn uint32_t isr_default(uint32_t interrupt_id) 
 * @brief default interrupt service routine
 * @details Default isr. Use it when you dont know what to do with interrupts
 * @param uint32_t interrupt_id
 * @return uint32_t
 */
فراغ isr_default(uint32_t وقفه_id)
{
	log_trace("\nisr_default entered\n");

	إذا( وقفه_id > 0 && وقفه_id < 7 )  //PWM Interrupts
	{
		/*
		   Assuming 6 pwm's are there
		 */

		إذا(pwm_check_continuous_نما((6-وقفه_id)) == 0)
		{
			مجموعه_pwm_control_ثبات((6-وقفه_id),0x80);
		}
	}

	log_info("interrupt [%d] serviced\n",وقفه_id);

	log_trace("\nisr_default exited\n");
}

/** @fn void interrupt_enable(uint32_t interrupt_id)
 * @brief enable the interrupt
 * @details A single bit that enables an interrupt. The bit position corresponds to the interrupt id
 * @param uint32_t interrupt_id
 */
فراغ وقفه_enable(uint32_t وقفه_id)
{
	uint8_t *وقفه_enable_addr;
	uint8_t current_مقدار = 0x00, new_مقدار;

	log_trace("\ninterrupt_enable entered \n");

	log_debug("interrupt_id = %x\n", وقفه_id);

	log_debug("PLIC BASE ADDRESS = %x, PLIC ENABLE OFFSET = %x\n" \
			,PLIC_پایه_آدرس, PLIC_ENABLE_جابه_جایی);
	وقفه_enable_addr = (uint8_t *) (PLIC_پایه_آدرس +
			PLIC_ENABLE_جابه_جایی +
			((وقفه_id) >> 3));

	current_مقدار = *وقفه_enable_addr;

	log_debug("interrupt_enable_addr = %x current_value = %x \n", \
			وقفه_enable_addr, current_مقدار);

	/*set the bit corresponding to the interrupt src*/
	new_مقدار = current_مقدار | (0x1 << (وقفه_id % 8));

	*((uint8_t*)وقفه_enable_addr) = new_مقدار;

	log_debug("value read: new_value = %x\n", new_مقدار);

	log_trace("\ninterrupt_enable exited \n");
}

/** @fn void interrupt_disable(uint32_t interrupt_id) 
 * @brief disable an interrupt
 * @details A single bit that enables an interrupt.
 *          The bit position corresponds to the interrupt id
 * @param uint32_t interrupt_id
 */
فراغ وقفه_disable(uint32_t وقفه_id)
{
	uint8_t *وقفه_disable_addr = 0;
	uint8_t current_مقدار = 0x00, new_مقدار;

	log_trace("\ninterrupt_disable entered \n");

	log_debug("interrupt_id = %x\n", وقفه_id);

	log_debug("PLIC BASE ADDRESS = %x, PLIC ENABLE OFFSET = %x interrupt_id = %x\n",
		  PLIC_پایه_آدرس, PLIC_ENABLE_جابه_جایی, وقفه_id);

	وقفه_disable_addr = (uint8_t *) (PLIC_پایه_آدرس +
					      PLIC_ENABLE_جابه_جایی +
					      (وقفه_id >> 3));

	current_مقدار = *وقفه_disable_addr;

	log_debug("interrupt_disable_addr = %x current_value = %x \n",
		  وقفه_disable_addr, current_مقدار);

	/*unset the bit corresponding to the interrupt src*/
	new_مقدار = current_مقدار & (~(0x1 << (وقفه_id % 8)));

	*وقفه_disable_addr = new_مقدار;

	hart0_وقفه_ماتریس[وقفه_id].state = INACTIVE;

	log_debug("interrupt id %d, state changed to %d\n",
		  وقفه_id,hart0_وقفه_ماتریس[وقفه_id].state);

	log_trace("interrupt_disable exited\n");
}

/** @fn void set_interrupt_threshold(uint32_t priority_value)
 * @brief set priority threshold for all interrupts
 * @details set a threshold on interrrupt priority. Any interruptthat has lesser priority than the threshold is ignored.
 * @param uint32_t priority_value
 */
فراغ مجموعه_وقفه_آستانه(uint32_t اولویت_مقدار)
{
	log_trace("\nset interrupt_threshold entered\n");

	uint32_t *وقفه_آستانه_اولویت = عدم;

	وقفه_آستانه_اولویت = (uint32_t *) (PLIC_پایه_آدرس +
						     PLIC_آستانه_جابه_جایی);

	*وقفه_آستانه_اولویت = اولویت_مقدار;

	log_debug("plic threshold set to %d\n", *وقفه_آستانه_اولویت);

	log_trace("set interrupt_threshold exited\n");
}

/** @fn void set_interrupt_priority(uint32_t priority_value, uint32_t int_id)
 * @brief set priority for an interrupt source
 * @details set priority for each interrupt. This is a 4 byte field.
 * @param uint32_t priority_value
 * @param uint32_t int_id
 */
فراغ مجموعه_وقفه_اولویت(uint32_t اولویت_مقدار, uint32_t int_id)
{
	log_trace("\n set interrupt priority entered %x\n", اولویت_مقدار);

	uint32_t * وقفه_اولویت_آدرس;

	/*
	   base address + priority offset + 4*interruptId
	 */

	وقفه_اولویت_آدرس = (uint32_t *) (PLIC_پایه_آدرس +
						   PLIC_اولویت_جابه_جایی +
						   (int_id <<
						    PLIC_اولویت_لغزش_در_هر_INT));

	log_debug("interrupt_priority_address = %x\n", وقفه_اولویت_آدرس);

	log_debug("current data at interrupt_priority_address = %x\n", *وقفه_اولویت_آدرس);

	*وقفه_اولویت_آدرس = اولویت_مقدار;

	log_debug(" new data at interrupt_priority_address = %x\n", *وقفه_اولویت_آدرس);

	log_trace("set interrupt priority exited\n");
}

/** @fn void configure_interrupt_pin(uint32_t id)
 * @brief configure a gpio pin for each interrupt
 * @details enable the corresponding gpio pin for a interrupt as read.
 * @param uint32_t id
 */
فراغ configure_وقفه_pin( __attribute__((استفادهنشده)) uint32_t id)
{
	log_trace("\nconfigure interrupt pin entered\n");

	uint32_t read_داده_2;

	/*
	   GPIO0 -> Int id 7
	   GPIO15 -> Int id 21
	   Refer platform.h for full memory map.
	 */

	read_داده_2 = read_کلمه(GPIO_DIRECTION_CNTRL_REG);

	log_debug("GPIO DIRECTION REGISTER VALUE = %x\n", read_داده_2);

	write_کلمه(GPIO_DIRECTION_CNTRL_REG, (read_داده_2) & \
		   (0xFFFFFFFF & ~(1 << (id-7))));

	log_debug("Data written to GPIO DIRECTION CTRL REG = %x\n", \
		  read_کلمه(GPIO_DIRECTION_CNTRL_REG));

	log_trace("configure interrupt pin exited\n");
}

/** @fn void plic_init
 * @brief intitializes the plic module
 * @details Intitializes the plic registers to default values.
 *          Sets up the plic meta data table. Assigns the plic
 *          handler to mcause_interrupt_table.,By default interrupts are disabled.
 */
فراغ plic_init()
{
	uint32_t int_id = 0;

	log_trace("\nplic_init entered\n");

	/*Assign service routine for external interrupt in machine mode*/
	mcause_وقفه_جدول[MACH_EXTERNAL_وقفه] = mach_plic_handler;

	log_debug("Assigned mach_plic_handler to trap id : %d\n", MACH_EXTERNAL_وقفه);

	/*
	   risc v priv spec v1.10 section 7.5 onwards

	   Global interrupt sources are assigned small uint32_teger identifiers, beginning at the value 1.
	   An interrupt ID of 0 is reserved to mean “no interrupt”.

	   The priority value 0 is reserved to mean “never interrupt”,
	   and interrupt priority increases with increasing integer values.
	 */

	hart0_وقفه_ماتریس[0].state = INACTIVE;
	hart0_وقفه_ماتریس[0].id = 0;
	hart0_وقفه_ماتریس[0].اولویت = 0;
	hart0_وقفه_ماتریس[0].شمار = 0;

	لكل(int_id = 1; int_id < PLIC_MAX_وقفه_SRC; int_id++)
	{
		hart0_وقفه_ماتریس[int_id].state = INACTIVE;
		hart0_وقفه_ماتریس[int_id].id = int_id;
		hart0_وقفه_ماتریس[int_id].اولویت = PLIC_اولویت_3;
		hart0_وقفه_ماتریس[int_id].شمار = 0;

		log_debug("\n************************************************");

		/*Disable all interrupts at the beginning*/
		وقفه_disable(int_id);

		/*assign a default isr for all interrupts*/
		isr_جدول[int_id] = isr_default;

		/*set priority for all interrupts*/

		مجموعه_وقفه_اولویت(PLIC_اولویت_3, int_id);

		log_debug("\ninterrupt id = %x \nreset مقصد افتراضي مقادیر state = %x \
			  \npriority = %x\ncount = %x\n \
			  \n*************************************************",
			  hart0_وقفه_ماتریس[int_id].id, \
			  hart0_وقفه_ماتریس[int_id].state, \
			  hart0_وقفه_ماتریس[int_id].اولویت, \
			  hart0_وقفه_ماتریس[int_id].شمار);
	}

	/* An isr for each and every unique interrupt source has to be added explicitly at init time*/

	/*Enable required interrupts
	  interrupt_enable(int_id);
	 */
	/*set threshold value for interrupts*/
	مجموعه_وقفه_آستانه(PLIC_اولویت_2);

	log_trace("plic_init exited \n");
}

/** @fn void configure_interrupt(uint32_t int_id)
 * @brief configure the interrupt pin and enable bit
 * @details Enables the interrupt and corresponding physical pin (id needed).
 *          This function needs to be part of interrupt trigger and handling flow
 * @warning Here it is assumed, to have a one to one mapping
 *          between interrupt enable bit and interrupt pin
 * @param uint32_t int_id
 */
فراغ configure_وقفه(uint32_t int_id)
{
	log_trace("\nconfigure_interrupt entered \n");

	/*
	   Call only for GPIO pins
	 */
	إذا(int_id >6 && int_id < 22)
	{
		configure_وقفه_pin(int_id);
	}

	وقفه_enable(int_id);

	log_trace("configure_interrupt exited \n");
}
