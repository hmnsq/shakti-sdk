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

#ਅਨ੍ਤਰ੍ਭਾਵ "pwm_driver.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "plic_driver.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "platform.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "stddef.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gpio.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "utils.h"

/*
   Global interrupt data maintenance structure
 */

plic_fptr_t isr_ਸਾਰਣੀ[PLIC_MAX_ਰੁਕਾਵਟ_SRC];
ਰੁਕਾਵਟ_ਅੰਕੜੇ_t hart0_ਰੁਕਾਵਟ_ਮੈਟ੍ਰਿਕਸ[PLIC_MAX_ਰੁਕਾਵਟ_SRC];

/** @fn void interrupt_complete(uint32_t interrupt_id)
 * @brief write the int_id to complete register
 * @details Signals completion of interrupt. From s/w side the interrupt claim/complete register is written with the interrupt id.
 * @param uint32_t interrupt_id
 */
ਖਾਲੀ ਰੁਕਾਵਟ_complete(uint32_t ਰੁਕਾਵਟ_id)
{
	log_trace("\ninterrupt_complete entered\n");

	uint32_t *claim_addr =  (uint32_t *) (PLIC_ਅਧਾਰ_ਪਤਾ +
					      PLIC_CLAIM_ਵਿੱਥ);

	*claim_addr = ਰੁਕਾਵਟ_id;
	hart0_ਰੁਕਾਵਟ_ਮੈਟ੍ਰਿਕਸ[ਰੁਕਾਵਟ_id].state = SERVICED;
	hart0_ਰੁਕਾਵਟ_ਮੈਟ੍ਰਿਕਸ[ਰੁਕਾਵਟ_id].ਗਿਣਤੀ_2++;

	log_debug("interrupt id %d, state changed to %d\n", ਰੁਕਾਵਟ_id,
		  hart0_ਰੁਕਾਵਟ_ਮੈਟ੍ਰਿਕਸ[ਰੁਕਾਵਟ_id].state);

	log_debug("ਰੁਕਾਵਟ id = %x \n reset ਮੰਜ਼ਿਲ ਮੂਲ ਮੁੱਲਾਂ state = %x \
		  \n ਤਰਜੀਹ = %x\n ਗਿਣਤੀ_2 = %x\n", \
		  hart0_ਰੁਕਾਵਟ_ਮੈਟ੍ਰਿਕਸ[ਰੁਕਾਵਟ_id].id, \
		  hart0_ਰੁਕਾਵਟ_ਮੈਟ੍ਰਿਕਸ[ਰੁਕਾਵਟ_id].state, \
		  hart0_ਰੁਕਾਵਟ_ਮੈਟ੍ਰਿਕਸ[ਰੁਕਾਵਟ_id].ਤਰਜੀਹ, \
		  hart0_ਰੁਕਾਵਟ_ਮੈਟ੍ਰਿਕਸ[ਰੁਕਾਵਟ_id].ਗਿਣਤੀ_2);

	log_trace("interrupt_complete exited\n");
}

/** @fn uint32_t interrupt_claim_request()
 * @brief know the id of the interrupt
 * @details read the interrupt claim register to know the interrupt id
 *           of the highest priority pending interrupt
 * @return uint32_t
 */
uint32_t ਰੁਕਾਵਟ_claim_request()
{
	uint32_t *ਰੁਕਾਵਟ_claim_ਪਤਾ = ਨਿਰਾ;
	uint32_t ਰੁਕਾਵਟ_id;

	log_trace("\ninterrupt_claim_request entered\n");

	/*
	   return the interrupt id. This will be used to index into the plic isr table.
	   From the isr table, the exact isr will be called

	   refer https://gitlab.com/shaktiproject/uncore/devices/blob/master/plic/plic.bsv as on 26/8/2019
	 */

	ਰੁਕਾਵਟ_claim_ਪਤਾ = (uint32_t *)(PLIC_ਅਧਾਰ_ਪਤਾ +
					       PLIC_CLAIM_ਵਿੱਥ);

	ਰੁਕਾਵਟ_id = *ਰੁਕਾਵਟ_claim_ਪਤਾ;

	log_debug("interrupt id [%x] claimed  at address %x\n", ਰੁਕਾਵਟ_id,
		  ਰੁਕਾਵਟ_claim_ਪਤਾ );

	log_trace("interrupt_claim_request exited\n");

	ਵਾਪਸ ਰੁਕਾਵਟ_id;
}

/** @fn void mach_plic_handler(uintptr_t int_id, uintptr_t epc)
 * @brief handle machine mode plic interrupts
 * @details find the int id that caused of interrupt, 
 *	    process it and complete the interrupt.
 * @param uintptr_t int_id
 * @param uintptr_t epc
 */
ਖਾਲੀ mach_plic_handler( __attribute__((ਅਣਵਰਤਿਆ)) uintptr_t int_id, __attribute__((ਅਣਵਰਤਿਆ)) uintptr_t epc)
{
	uint32_t  ਰੁਕਾਵਟ_id;

	log_trace("\nmach_plic_handler entered\n");

	ਰੁਕਾਵਟ_id = ਰੁਕਾਵਟ_claim_request();

	log_debug("interrupt id claimed = %x\n", ਰੁਕਾਵਟ_id);

	ਜੇ (ਰੁਕਾਵਟ_id <= 0 || ਰੁਕਾਵਟ_id > PLIC_MAX_ਰੁਕਾਵਟ_SRC)
	{
		log_fatal("Fatal error, interrupt id [%x] claimed is wrong\n", ਰੁਕਾਵਟ_id);
	}

	/*
	   clear IP bit ?

	   After the highest-priority pending interrupt is claimed by a target and the corresponding
	   IP bit is cleared, other lower-priority pending interrupts might then become visible to
	   the target, and so the PLIC EIP bit might not be cleared after a claim

	   reference - risc v priv spec v1.10 section 7.10 Interrupt Claims
	 */

	/*change state to active*/
	hart0_ਰੁਕਾਵਟ_ਮੈਟ੍ਰਿਕਸ[ਰੁਕਾਵਟ_id].state = ਸਰਗਰਮ;

	log_debug("interrupt id %d, state changed to %d\n",
		  ਰੁਕਾਵਟ_id,hart0_ਰੁਕਾਵਟ_ਮੈਟ੍ਰਿਕਸ[ਰੁਕਾਵਟ_id].state);

	/*call relevant interrupt service routine*/
	isr_ਸਾਰਣੀ[ਰੁਕਾਵਟ_id](ਰੁਕਾਵਟ_id);

	ਰੁਕਾਵਟ_complete(ਰੁਕਾਵਟ_id);

	log_debug("interrupt id %d complete \n", ਰੁਕਾਵਟ_id);

	log_trace("\nmach_plic_handler exited\n");
}

/** @fn uint32_t isr_default(uint32_t interrupt_id) 
 * @brief default interrupt service routine
 * @details Default isr. Use it when you dont know what to do with interrupts
 * @param uint32_t interrupt_id
 * @return uint32_t
 */
ਖਾਲੀ isr_default(uint32_t ਰੁਕਾਵਟ_id)
{
	log_trace("\nisr_default entered\n");

	ਜੇ( ਰੁਕਾਵਟ_id > 0 && ਰੁਕਾਵਟ_id < 7 )  //PWM Interrupts
	{
		/*
		   Assuming 6 pwm's are there
		 */

		ਜੇ(pwm_check_continuous_ਬਹੁਲਕ((6-ਰੁਕਾਵਟ_id)) == 0)
		{
			ਸੈੱਟ_pwm_control_ਰਜਿਸਟਰ((6-ਰੁਕਾਵਟ_id),0x80);
		}
	}

	log_info("interrupt [%d] serviced\n",ਰੁਕਾਵਟ_id);

	log_trace("\nisr_default exited\n");
}

/** @fn void interrupt_enable(uint32_t interrupt_id)
 * @brief enable the interrupt
 * @details A single bit that enables an interrupt. The bit position corresponds to the interrupt id
 * @param uint32_t interrupt_id
 */
ਖਾਲੀ ਰੁਕਾਵਟ_enable(uint32_t ਰੁਕਾਵਟ_id)
{
	uint8_t *ਰੁਕਾਵਟ_enable_addr;
	uint8_t current_ਮੁੱਲ = 0x00, new_ਮੁੱਲ;

	log_trace("\ninterrupt_enable entered \n");

	log_debug("interrupt_id = %x\n", ਰੁਕਾਵਟ_id);

	log_debug("PLIC BASE ADDRESS = %x, PLIC ENABLE OFFSET = %x\n" \
			,PLIC_ਅਧਾਰ_ਪਤਾ, PLIC_ENABLE_ਵਿੱਥ);
	ਰੁਕਾਵਟ_enable_addr = (uint8_t *) (PLIC_ਅਧਾਰ_ਪਤਾ +
			PLIC_ENABLE_ਵਿੱਥ +
			((ਰੁਕਾਵਟ_id) >> 3));

	current_ਮੁੱਲ = *ਰੁਕਾਵਟ_enable_addr;

	log_debug("interrupt_enable_addr = %x current_value = %x \n", \
			ਰੁਕਾਵਟ_enable_addr, current_ਮੁੱਲ);

	/*set the bit corresponding to the interrupt src*/
	new_ਮੁੱਲ = current_ਮੁੱਲ | (0x1 << (ਰੁਕਾਵਟ_id % 8));

	*((uint8_t*)ਰੁਕਾਵਟ_enable_addr) = new_ਮੁੱਲ;

	log_debug("value read: new_value = %x\n", new_ਮੁੱਲ);

	log_trace("\ninterrupt_enable exited \n");
}

/** @fn void interrupt_disable(uint32_t interrupt_id) 
 * @brief disable an interrupt
 * @details A single bit that enables an interrupt.
 *          The bit position corresponds to the interrupt id
 * @param uint32_t interrupt_id
 */
ਖਾਲੀ ਰੁਕਾਵਟ_disable(uint32_t ਰੁਕਾਵਟ_id)
{
	uint8_t *ਰੁਕਾਵਟ_disable_addr = 0;
	uint8_t current_ਮੁੱਲ = 0x00, new_ਮੁੱਲ;

	log_trace("\ninterrupt_disable entered \n");

	log_debug("interrupt_id = %x\n", ਰੁਕਾਵਟ_id);

	log_debug("PLIC BASE ADDRESS = %x, PLIC ENABLE OFFSET = %x interrupt_id = %x\n",
		  PLIC_ਅਧਾਰ_ਪਤਾ, PLIC_ENABLE_ਵਿੱਥ, ਰੁਕਾਵਟ_id);

	ਰੁਕਾਵਟ_disable_addr = (uint8_t *) (PLIC_ਅਧਾਰ_ਪਤਾ +
					      PLIC_ENABLE_ਵਿੱਥ +
					      (ਰੁਕਾਵਟ_id >> 3));

	current_ਮੁੱਲ = *ਰੁਕਾਵਟ_disable_addr;

	log_debug("interrupt_disable_addr = %x current_value = %x \n",
		  ਰੁਕਾਵਟ_disable_addr, current_ਮੁੱਲ);

	/*unset the bit corresponding to the interrupt src*/
	new_ਮੁੱਲ = current_ਮੁੱਲ & (~(0x1 << (ਰੁਕਾਵਟ_id % 8)));

	*ਰੁਕਾਵਟ_disable_addr = new_ਮੁੱਲ;

	hart0_ਰੁਕਾਵਟ_ਮੈਟ੍ਰਿਕਸ[ਰੁਕਾਵਟ_id].state = INACTIVE;

	log_debug("interrupt id %d, state changed to %d\n",
		  ਰੁਕਾਵਟ_id,hart0_ਰੁਕਾਵਟ_ਮੈਟ੍ਰਿਕਸ[ਰੁਕਾਵਟ_id].state);

	log_trace("interrupt_disable exited\n");
}

/** @fn void set_interrupt_threshold(uint32_t priority_value)
 * @brief set priority threshold for all interrupts
 * @details set a threshold on interrrupt priority. Any interruptthat has lesser priority than the threshold is ignored.
 * @param uint32_t priority_value
 */
ਖਾਲੀ ਸੈੱਟ_ਰੁਕਾਵਟ_ਹੱਦ(uint32_t ਤਰਜੀਹ_ਮੁੱਲ)
{
	log_trace("\nset interrupt_threshold entered\n");

	uint32_t *ਰੁਕਾਵਟ_ਹੱਦ_ਤਰਜੀਹ = ਨਿਰਾ;

	ਰੁਕਾਵਟ_ਹੱਦ_ਤਰਜੀਹ = (uint32_t *) (PLIC_ਅਧਾਰ_ਪਤਾ +
						     PLIC_ਹੱਦ_ਵਿੱਥ);

	*ਰੁਕਾਵਟ_ਹੱਦ_ਤਰਜੀਹ = ਤਰਜੀਹ_ਮੁੱਲ;

	log_debug("plic threshold set to %d\n", *ਰੁਕਾਵਟ_ਹੱਦ_ਤਰਜੀਹ);

	log_trace("set interrupt_threshold exited\n");
}

/** @fn void set_interrupt_priority(uint32_t priority_value, uint32_t int_id)
 * @brief set priority for an interrupt source
 * @details set priority for each interrupt. This is a 4 byte field.
 * @param uint32_t priority_value
 * @param uint32_t int_id
 */
ਖਾਲੀ ਸੈੱਟ_ਰੁਕਾਵਟ_ਤਰਜੀਹ(uint32_t ਤਰਜੀਹ_ਮੁੱਲ, uint32_t int_id)
{
	log_trace("\n set interrupt priority entered %x\n", ਤਰਜੀਹ_ਮੁੱਲ);

	uint32_t * ਰੁਕਾਵਟ_ਤਰਜੀਹ_ਪਤਾ;

	/*
	   base address + priority offset + 4*interruptId
	 */

	ਰੁਕਾਵਟ_ਤਰਜੀਹ_ਪਤਾ = (uint32_t *) (PLIC_ਅਧਾਰ_ਪਤਾ +
						   PLIC_ਤਰਜੀਹ_ਵਿੱਥ +
						   (int_id <<
						    PLIC_ਤਰਜੀਹ_ਖਿਸਕਾਓ_ਪ੍ਰਤੀ_INT));

	log_debug("interrupt_priority_address = %x\n", ਰੁਕਾਵਟ_ਤਰਜੀਹ_ਪਤਾ);

	log_debug("current data at interrupt_priority_address = %x\n", *ਰੁਕਾਵਟ_ਤਰਜੀਹ_ਪਤਾ);

	*ਰੁਕਾਵਟ_ਤਰਜੀਹ_ਪਤਾ = ਤਰਜੀਹ_ਮੁੱਲ;

	log_debug(" new data at interrupt_priority_address = %x\n", *ਰੁਕਾਵਟ_ਤਰਜੀਹ_ਪਤਾ);

	log_trace("set interrupt priority exited\n");
}

/** @fn void configure_interrupt_pin(uint32_t id)
 * @brief configure a gpio pin for each interrupt
 * @details enable the corresponding gpio pin for a interrupt as read.
 * @param uint32_t id
 */
ਖਾਲੀ configure_ਰੁਕਾਵਟ_pin( __attribute__((ਅਣਵਰਤਿਆ)) uint32_t id)
{
	log_trace("\nconfigure interrupt pin entered\n");

	uint32_t read_ਅੰਕੜੇ_2;

	/*
	   GPIO0 -> Int id 7
	   GPIO15 -> Int id 21
	   Refer platform.h for full memory map.
	 */

	read_ਅੰਕੜੇ_2 = read_ਸ਼ਬਦ(GPIO_DIRECTION_CNTRL_REG);

	log_debug("GPIO DIRECTION REGISTER VALUE = %x\n", read_ਅੰਕੜੇ_2);

	write_ਸ਼ਬਦ(GPIO_DIRECTION_CNTRL_REG, (read_ਅੰਕੜੇ_2) & \
		   (0xFFFFFFFF & ~(1 << (id-7))));

	log_debug("Data written to GPIO DIRECTION CTRL REG = %x\n", \
		  read_ਸ਼ਬਦ(GPIO_DIRECTION_CNTRL_REG));

	log_trace("configure interrupt pin exited\n");
}

/** @fn void plic_init
 * @brief intitializes the plic module
 * @details Intitializes the plic registers to default values.
 *          Sets up the plic meta data table. Assigns the plic
 *          handler to mcause_interrupt_table.,By default interrupts are disabled.
 */
ਖਾਲੀ plic_init()
{
	uint32_t int_id = 0;

	log_trace("\nplic_init entered\n");

	/*Assign service routine for external interrupt in machine mode*/
	mcause_ਰੁਕਾਵਟ_ਸਾਰਣੀ[MACH_EXTERNAL_ਰੁਕਾਵਟ] = mach_plic_handler;

	log_debug("Assigned mach_plic_handler to trap id : %d\n", MACH_EXTERNAL_ਰੁਕਾਵਟ);

	/*
	   risc v priv spec v1.10 section 7.5 onwards

	   Global interrupt sources are assigned small uint32_teger identifiers, beginning at the value 1.
	   An interrupt ID of 0 is reserved to mean “no interrupt”.

	   The priority value 0 is reserved to mean “never interrupt”,
	   and interrupt priority increases with increasing integer values.
	 */

	hart0_ਰੁਕਾਵਟ_ਮੈਟ੍ਰਿਕਸ[0].state = INACTIVE;
	hart0_ਰੁਕਾਵਟ_ਮੈਟ੍ਰਿਕਸ[0].id = 0;
	hart0_ਰੁਕਾਵਟ_ਮੈਟ੍ਰਿਕਸ[0].ਤਰਜੀਹ = 0;
	hart0_ਰੁਕਾਵਟ_ਮੈਟ੍ਰਿਕਸ[0].ਗਿਣਤੀ_2 = 0;

	ਲਈ(int_id = 1; int_id < PLIC_MAX_ਰੁਕਾਵਟ_SRC; int_id++)
	{
		hart0_ਰੁਕਾਵਟ_ਮੈਟ੍ਰਿਕਸ[int_id].state = INACTIVE;
		hart0_ਰੁਕਾਵਟ_ਮੈਟ੍ਰਿਕਸ[int_id].id = int_id;
		hart0_ਰੁਕਾਵਟ_ਮੈਟ੍ਰਿਕਸ[int_id].ਤਰਜੀਹ = PLIC_ਤਰਜੀਹ_3;
		hart0_ਰੁਕਾਵਟ_ਮੈਟ੍ਰਿਕਸ[int_id].ਗਿਣਤੀ_2 = 0;

		log_debug("\n************************************************");

		/*Disable all interrupts at the beginning*/
		ਰੁਕਾਵਟ_disable(int_id);

		/*assign a default isr for all interrupts*/
		isr_ਸਾਰਣੀ[int_id] = isr_default;

		/*set priority for all interrupts*/

		ਸੈੱਟ_ਰੁਕਾਵਟ_ਤਰਜੀਹ(PLIC_ਤਰਜੀਹ_3, int_id);

		log_debug("\ninterrupt id = %x \nreset ਮੰਜ਼ਿਲ ਮੂਲ ਮੁੱਲਾਂ state = %x \
			  \npriority = %x\ncount = %x\n \
			  \n*************************************************",
			  hart0_ਰੁਕਾਵਟ_ਮੈਟ੍ਰਿਕਸ[int_id].id, \
			  hart0_ਰੁਕਾਵਟ_ਮੈਟ੍ਰਿਕਸ[int_id].state, \
			  hart0_ਰੁਕਾਵਟ_ਮੈਟ੍ਰਿਕਸ[int_id].ਤਰਜੀਹ, \
			  hart0_ਰੁਕਾਵਟ_ਮੈਟ੍ਰਿਕਸ[int_id].ਗਿਣਤੀ_2);
	}

	/* An isr for each and every unique interrupt source has to be added explicitly at init time*/

	/*Enable required interrupts
	  interrupt_enable(int_id);
	 */
	/*set threshold value for interrupts*/
	ਸੈੱਟ_ਰੁਕਾਵਟ_ਹੱਦ(PLIC_ਤਰਜੀਹ_2);

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
ਖਾਲੀ configure_ਰੁਕਾਵਟ(uint32_t int_id)
{
	log_trace("\nconfigure_interrupt entered \n");

	/*
	   Call only for GPIO pins
	 */
	ਜੇ(int_id >6 && int_id < 22)
	{
		configure_ਰੁਕਾਵਟ_pin(int_id);
	}

	ਰੁਕਾਵਟ_enable(int_id);

	log_trace("configure_interrupt exited \n");
}
