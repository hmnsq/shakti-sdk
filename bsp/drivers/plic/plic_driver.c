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

#అన్తర్భావ "pwm_driver.h"
#అన్తర్భావ "plic_driver.h"
#అన్తర్భావ "platform.h"
#అన్తర్భావ "log.h"
#అన్తర్భావ "stddef.h"
#అన్తర్భావ "gpio.h"
#అన్తర్భావ "utils.h"

/*
   Global interrupt data maintenance structure
 */

plic_fptr_t isr_పట్టిక[PLIC_MAX_అంతరాయం_SRC];
అంతరాయం_దత్తాంశం_t hart0_అంతరాయం_మాతృక[PLIC_MAX_అంతరాయం_SRC];

/** @fn void interrupt_complete(uint32_t interrupt_id)
 * @brief write the int_id to complete register
 * @details Signals completion of interrupt. From s/w side the interrupt claim/complete register is written with the interrupt id.
 * @param uint32_t interrupt_id
 */
శూన్య అంతరాయం_complete(uint32_t అంతరాయం_id)
{
	log_trace("\ninterrupt_complete entered\n");

	uint32_t *claim_addr =  (uint32_t *) (PLIC_పునాది_చిరునామా +
					      PLIC_CLAIM_స్థానభ్రంశం);

	*claim_addr = అంతరాయం_id;
	hart0_అంతరాయం_మాతృక[అంతరాయం_id].state = SERVICED;
	hart0_అంతరాయం_మాతృక[అంతరాయం_id].లెక్క++;

	log_debug("interrupt id %d, state changed to %d\n", అంతరాయం_id,
		  hart0_అంతరాయం_మాతృక[అంతరాయం_id].state);

	log_debug("అంతరాయం id = %x \n reset గమ్యం అప్రమేయ విలువలు state = %x \
		  \n ప్రాధాన్యత = %x\n లెక్క = %x\n", \
		  hart0_అంతరాయం_మాతృక[అంతరాయం_id].id, \
		  hart0_అంతరాయం_మాతృక[అంతరాయం_id].state, \
		  hart0_అంతరాయం_మాతృక[అంతరాయం_id].ప్రాధాన్యత, \
		  hart0_అంతరాయం_మాతృక[అంతరాయం_id].లెక్క);

	log_trace("interrupt_complete exited\n");
}

/** @fn uint32_t interrupt_claim_request()
 * @brief know the id of the interrupt
 * @details read the interrupt claim register to know the interrupt id
 *           of the highest priority pending interrupt
 * @return uint32_t
 */
uint32_t అంతరాయం_claim_request()
{
	uint32_t *అంతరాయం_claim_చిరునామా = ఖాళీ;
	uint32_t అంతరాయం_id;

	log_trace("\ninterrupt_claim_request entered\n");

	/*
	   return the interrupt id. This will be used to index into the plic isr table.
	   From the isr table, the exact isr will be called

	   refer https://gitlab.com/shaktiproject/uncore/devices/blob/master/plic/plic.bsv as on 26/8/2019
	 */

	అంతరాయం_claim_చిరునామా = (uint32_t *)(PLIC_పునాది_చిరునామా +
					       PLIC_CLAIM_స్థానభ్రంశం);

	అంతరాయం_id = *అంతరాయం_claim_చిరునామా;

	log_debug("interrupt id [%x] claimed  at address %x\n", అంతరాయం_id,
		  అంతరాయం_claim_చిరునామా );

	log_trace("interrupt_claim_request exited\n");

	తిరిగి అంతరాయం_id;
}

/** @fn void mach_plic_handler(uintptr_t int_id, uintptr_t epc)
 * @brief handle machine mode plic interrupts
 * @details find the int id that caused of interrupt, 
 *	    process it and complete the interrupt.
 * @param uintptr_t int_id
 * @param uintptr_t epc
 */
శూన్య mach_plic_handler( __attribute__((వాడని)) uintptr_t int_id, __attribute__((వాడని)) uintptr_t epc)
{
	uint32_t  అంతరాయం_id;

	log_trace("\nmach_plic_handler entered\n");

	అంతరాయం_id = అంతరాయం_claim_request();

	log_debug("interrupt id claimed = %x\n", అంతరాయం_id);

	ఒకవేళ (అంతరాయం_id <= 0 || అంతరాయం_id > PLIC_MAX_అంతరాయం_SRC)
	{
		log_fatal("Fatal error, interrupt id [%x] claimed is wrong\n", అంతరాయం_id);
	}

	/*
	   clear IP bit ?

	   After the highest-priority pending interrupt is claimed by a target and the corresponding
	   IP bit is cleared, other lower-priority pending interrupts might then become visible to
	   the target, and so the PLIC EIP bit might not be cleared after a claim

	   reference - risc v priv spec v1.10 section 7.10 Interrupt Claims
	 */

	/*change state to active*/
	hart0_అంతరాయం_మాతృక[అంతరాయం_id].state = చురుకైన;

	log_debug("interrupt id %d, state changed to %d\n",
		  అంతరాయం_id,hart0_అంతరాయం_మాతృక[అంతరాయం_id].state);

	/*call relevant interrupt service routine*/
	isr_పట్టిక[అంతరాయం_id](అంతరాయం_id);

	అంతరాయం_complete(అంతరాయం_id);

	log_debug("interrupt id %d complete \n", అంతరాయం_id);

	log_trace("\nmach_plic_handler exited\n");
}

/** @fn uint32_t isr_default(uint32_t interrupt_id) 
 * @brief default interrupt service routine
 * @details Default isr. Use it when you dont know what to do with interrupts
 * @param uint32_t interrupt_id
 * @return uint32_t
 */
శూన్య isr_default(uint32_t అంతరాయం_id)
{
	log_trace("\nisr_default entered\n");

	ఒకవేళ( అంతరాయం_id > 0 && అంతరాయం_id < 7 )  //PWM Interrupts
	{
		/*
		   Assuming 6 pwm's are there
		 */

		ఒకవేళ(pwm_check_continuous_బహుళకం((6-అంతరాయం_id)) == 0)
		{
			సమితి_pwm_control_రిజిస్టరు((6-అంతరాయం_id),0x80);
		}
	}

	log_info("interrupt [%d] serviced\n",అంతరాయం_id);

	log_trace("\nisr_default exited\n");
}

/** @fn void interrupt_enable(uint32_t interrupt_id)
 * @brief enable the interrupt
 * @details A single bit that enables an interrupt. The bit position corresponds to the interrupt id
 * @param uint32_t interrupt_id
 */
శూన్య అంతరాయం_enable(uint32_t అంతరాయం_id)
{
	uint8_t *అంతరాయం_enable_addr;
	uint8_t current_విలువ = 0x00, new_విలువ;

	log_trace("\ninterrupt_enable entered \n");

	log_debug("interrupt_id = %x\n", అంతరాయం_id);

	log_debug("PLIC BASE ADDRESS = %x, PLIC ENABLE OFFSET = %x\n" \
			,PLIC_పునాది_చిరునామా, PLIC_ENABLE_స్థానభ్రంశం);
	అంతరాయం_enable_addr = (uint8_t *) (PLIC_పునాది_చిరునామా +
			PLIC_ENABLE_స్థానభ్రంశం +
			((అంతరాయం_id) >> 3));

	current_విలువ = *అంతరాయం_enable_addr;

	log_debug("interrupt_enable_addr = %x current_value = %x \n", \
			అంతరాయం_enable_addr, current_విలువ);

	/*set the bit corresponding to the interrupt src*/
	new_విలువ = current_విలువ | (0x1 << (అంతరాయం_id % 8));

	*((uint8_t*)అంతరాయం_enable_addr) = new_విలువ;

	log_debug("value read: new_value = %x\n", new_విలువ);

	log_trace("\ninterrupt_enable exited \n");
}

/** @fn void interrupt_disable(uint32_t interrupt_id) 
 * @brief disable an interrupt
 * @details A single bit that enables an interrupt.
 *          The bit position corresponds to the interrupt id
 * @param uint32_t interrupt_id
 */
శూన్య అంతరాయం_disable(uint32_t అంతరాయం_id)
{
	uint8_t *అంతరాయం_disable_addr = 0;
	uint8_t current_విలువ = 0x00, new_విలువ;

	log_trace("\ninterrupt_disable entered \n");

	log_debug("interrupt_id = %x\n", అంతరాయం_id);

	log_debug("PLIC BASE ADDRESS = %x, PLIC ENABLE OFFSET = %x interrupt_id = %x\n",
		  PLIC_పునాది_చిరునామా, PLIC_ENABLE_స్థానభ్రంశం, అంతరాయం_id);

	అంతరాయం_disable_addr = (uint8_t *) (PLIC_పునాది_చిరునామా +
					      PLIC_ENABLE_స్థానభ్రంశం +
					      (అంతరాయం_id >> 3));

	current_విలువ = *అంతరాయం_disable_addr;

	log_debug("interrupt_disable_addr = %x current_value = %x \n",
		  అంతరాయం_disable_addr, current_విలువ);

	/*unset the bit corresponding to the interrupt src*/
	new_విలువ = current_విలువ & (~(0x1 << (అంతరాయం_id % 8)));

	*అంతరాయం_disable_addr = new_విలువ;

	hart0_అంతరాయం_మాతృక[అంతరాయం_id].state = INACTIVE;

	log_debug("interrupt id %d, state changed to %d\n",
		  అంతరాయం_id,hart0_అంతరాయం_మాతృక[అంతరాయం_id].state);

	log_trace("interrupt_disable exited\n");
}

/** @fn void set_interrupt_threshold(uint32_t priority_value)
 * @brief set priority threshold for all interrupts
 * @details set a threshold on interrrupt priority. Any interruptthat has lesser priority than the threshold is ignored.
 * @param uint32_t priority_value
 */
శూన్య సమితి_అంతరాయం_పరిమితి(uint32_t ప్రాధాన్యత_విలువ)
{
	log_trace("\nset interrupt_threshold entered\n");

	uint32_t *అంతరాయం_పరిమితి_ప్రాధాన్యత = ఖాళీ;

	అంతరాయం_పరిమితి_ప్రాధాన్యత = (uint32_t *) (PLIC_పునాది_చిరునామా +
						     PLIC_పరిమితి_స్థానభ్రంశం);

	*అంతరాయం_పరిమితి_ప్రాధాన్యత = ప్రాధాన్యత_విలువ;

	log_debug("plic threshold set to %d\n", *అంతరాయం_పరిమితి_ప్రాధాన్యత);

	log_trace("set interrupt_threshold exited\n");
}

/** @fn void set_interrupt_priority(uint32_t priority_value, uint32_t int_id)
 * @brief set priority for an interrupt source
 * @details set priority for each interrupt. This is a 4 byte field.
 * @param uint32_t priority_value
 * @param uint32_t int_id
 */
శూన్య సమితి_అంతరాయం_ప్రాధాన్యత(uint32_t ప్రాధాన్యత_విలువ, uint32_t int_id)
{
	log_trace("\n set interrupt priority entered %x\n", ప్రాధాన్యత_విలువ);

	uint32_t * అంతరాయం_ప్రాధాన్యత_చిరునామా;

	/*
	   base address + priority offset + 4*interruptId
	 */

	అంతరాయం_ప్రాధాన్యత_చిరునామా = (uint32_t *) (PLIC_పునాది_చిరునామా +
						   PLIC_ప్రాధాన్యత_స్థానభ్రంశం +
						   (int_id <<
						    PLIC_ప్రాధాన్యత_జరుపు_చొప్పున_INT));

	log_debug("interrupt_priority_address = %x\n", అంతరాయం_ప్రాధాన్యత_చిరునామా);

	log_debug("current data at interrupt_priority_address = %x\n", *అంతరాయం_ప్రాధాన్యత_చిరునామా);

	*అంతరాయం_ప్రాధాన్యత_చిరునామా = ప్రాధాన్యత_విలువ;

	log_debug(" new data at interrupt_priority_address = %x\n", *అంతరాయం_ప్రాధాన్యత_చిరునామా);

	log_trace("set interrupt priority exited\n");
}

/** @fn void configure_interrupt_pin(uint32_t id)
 * @brief configure a gpio pin for each interrupt
 * @details enable the corresponding gpio pin for a interrupt as read.
 * @param uint32_t id
 */
శూన్య configure_అంతరాయం_pin( __attribute__((వాడని)) uint32_t id)
{
	log_trace("\nconfigure interrupt pin entered\n");

	uint32_t read_దత్తాంశం_2;

	/*
	   GPIO0 -> Int id 7
	   GPIO15 -> Int id 21
	   Refer platform.h for full memory map.
	 */

	read_దత్తాంశం_2 = read_మాట(GPIO_DIRECTION_CNTRL_REG);

	log_debug("GPIO DIRECTION REGISTER VALUE = %x\n", read_దత్తాంశం_2);

	write_మాట(GPIO_DIRECTION_CNTRL_REG, (read_దత్తాంశం_2) & \
		   (0xFFFFFFFF & ~(1 << (id-7))));

	log_debug("Data written to GPIO DIRECTION CTRL REG = %x\n", \
		  read_మాట(GPIO_DIRECTION_CNTRL_REG));

	log_trace("configure interrupt pin exited\n");
}

/** @fn void plic_init
 * @brief intitializes the plic module
 * @details Intitializes the plic registers to default values.
 *          Sets up the plic meta data table. Assigns the plic
 *          handler to mcause_interrupt_table.,By default interrupts are disabled.
 */
శూన్య plic_init()
{
	uint32_t int_id = 0;

	log_trace("\nplic_init entered\n");

	/*Assign service routine for external interrupt in machine mode*/
	mcause_అంతరాయం_పట్టిక[MACH_EXTERNAL_అంతరాయం] = mach_plic_handler;

	log_debug("Assigned mach_plic_handler to trap id : %d\n", MACH_EXTERNAL_అంతరాయం);

	/*
	   risc v priv spec v1.10 section 7.5 onwards

	   Global interrupt sources are assigned small uint32_teger identifiers, beginning at the value 1.
	   An interrupt ID of 0 is reserved to mean “no interrupt”.

	   The priority value 0 is reserved to mean “never interrupt”,
	   and interrupt priority increases with increasing integer values.
	 */

	hart0_అంతరాయం_మాతృక[0].state = INACTIVE;
	hart0_అంతరాయం_మాతృక[0].id = 0;
	hart0_అంతరాయం_మాతృక[0].ప్రాధాన్యత = 0;
	hart0_అంతరాయం_మాతృక[0].లెక్క = 0;

	కొరకు(int_id = 1; int_id < PLIC_MAX_అంతరాయం_SRC; int_id++)
	{
		hart0_అంతరాయం_మాతృక[int_id].state = INACTIVE;
		hart0_అంతరాయం_మాతృక[int_id].id = int_id;
		hart0_అంతరాయం_మాతృక[int_id].ప్రాధాన్యత = PLIC_ప్రాధాన్యత_3;
		hart0_అంతరాయం_మాతృక[int_id].లెక్క = 0;

		log_debug("\n************************************************");

		/*Disable all interrupts at the beginning*/
		అంతరాయం_disable(int_id);

		/*assign a default isr for all interrupts*/
		isr_పట్టిక[int_id] = isr_default;

		/*set priority for all interrupts*/

		సమితి_అంతరాయం_ప్రాధాన్యత(PLIC_ప్రాధాన్యత_3, int_id);

		log_debug("\ninterrupt id = %x \nreset గమ్యం అప్రమేయ విలువలు state = %x \
			  \npriority = %x\ncount = %x\n \
			  \n*************************************************",
			  hart0_అంతరాయం_మాతృక[int_id].id, \
			  hart0_అంతరాయం_మాతృక[int_id].state, \
			  hart0_అంతరాయం_మాతృక[int_id].ప్రాధాన్యత, \
			  hart0_అంతరాయం_మాతృక[int_id].లెక్క);
	}

	/* An isr for each and every unique interrupt source has to be added explicitly at init time*/

	/*Enable required interrupts
	  interrupt_enable(int_id);
	 */
	/*set threshold value for interrupts*/
	సమితి_అంతరాయం_పరిమితి(PLIC_ప్రాధాన్యత_2);

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
శూన్య configure_అంతరాయం(uint32_t int_id)
{
	log_trace("\nconfigure_interrupt entered \n");

	/*
	   Call only for GPIO pins
	 */
	ఒకవేళ(int_id >6 && int_id < 22)
	{
		configure_అంతరాయం_pin(int_id);
	}

	అంతరాయం_enable(int_id);

	log_trace("configure_interrupt exited \n");
}
