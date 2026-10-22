/***************************************************************************
 * Project           		: shakti devt board
 * Name of the file	     	: init.c
 * Brief Description of file    : source file for system initialization.
 * Name of Author    	        : Sathya Narayanan N & Abhinav Ramnath
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

 ****************************************************************************/
/**
@file init.c
@brief source file for system initialization
@detail This is the beginning part of a application beginning.
Different sections are initialized. main function is called. 
uart is initialized. Trap handler is initialized. 
Disable Xip for Aardonyx
*/

#అన్తర్భావ "traps.h"
#అన్తర్భావ "plic_driver.h"
#అన్తర్భావ "clint_driver.h"
#అన్తర్భావ "log.h"
#అన్తర్భావ "utils.h"
#అన్తర్భావ "qspi.h"
#అన్తర్భావ "platform.h"
#అన్తర్భావ "defines.h"
#అన్తర్భావ "uart.h"

బాహ్య శూన్య init(శూన్య);
బాహ్య శూన్య trap_నమోదు(శూన్య);
బాహ్య uart_struct *uart_instance[MAX_UART_లెక్క];

బాహ్య అక్షరం దొంతర_చివర[];
బాహ్య అక్షరం దొంతర[];
బాహ్య అక్షరం కుప్ప[];
బాహ్య అక్షరం కుప్ప_చివర[];

అక్షరం *దొంతర_చివర_2=(అక్షరం *)&దొంతర_చివర;
అక్షరం *దొంతర_ప్రారంభం=(అక్షరం *)&దొంతర;
అక్షరం *కుప్ప_ప్రారంభం=(అక్షరం *)&కుప్ప;
అక్షరం *కుప్ప_చివర_2=(అక్షరం *)&కుప్ప_చివర;

/** @fn void section_init()
 * @brief resets the different sections
 * @details Explicitly 0x0 or 0xffffffff is written all the addresses in different "write" sections of memory
 * @warning takes long time. so the caller is diabled as of now
 */
స్థిర శూన్య section_init(శూన్య)
{
#ఒకవేళ 0
	/*Enable below code only on need
	 */
	అయితే(కుప్ప_ప్రారంభం<=కుప్ప_చివర_2)
	{
		*కుప్ప_ప్రారంభం=0xff;
		కుప్ప_ప్రారంభం++;
	}

	అయితే(దొంతర_చివర_2>=దొంతర_ప్రారంభం)
	{
		*దొంతర_చివర_2=0x0;
		దొంతర_చివర_2--;
	}
#అయితే_ముగింపు

}

/** @fn void trap_init()
 * @brief Initialize the trap/interrupt callback routines with user defined handler.
 * @details Assign default handler for trap / interrupt that does not have user defined
 *          callback routines"
 */
స్థిర శూన్య trap_init(శూన్య)
{
	log_trace("trap_init entered \n ");

	mcause_అంతరాయం_పట్టిక[USER_SW_అంతరాయం]        = default_handler;
	mcause_అంతరాయం_పట్టిక[SUPER_SW_అంతరాయం]       = default_handler;
	mcause_అంతరాయం_పట్టిక[RESERVED_INTERRUPT0]      = default_handler;
	mcause_అంతరాయం_పట్టిక[MACH_SW_అంతరాయం]        = default_handler;
	mcause_అంతరాయం_పట్టిక[USER_TIMER_అంతరాయం]     = default_handler;
	mcause_అంతరాయం_పట్టిక[SUPER_TIMER_అంతరాయం]    = default_handler;
	mcause_అంతరాయం_పట్టిక[RESERVED_INTERRUPT1]      = default_handler;
	mcause_అంతరాయం_పట్టిక[MACH_TIMER_అంతరాయం]     = mach_clint_handler;
	mcause_అంతరాయం_పట్టిక[USER_EXT_అంతరాయం]       = default_handler;
	mcause_అంతరాయం_పట్టిక[SUPERVISOR_EXT_అంతరాయం] = default_handler;
	mcause_అంతరాయం_పట్టిక[RESERVED_INTERRUPT2]      = default_handler;
	mcause_అంతరాయం_పట్టిక[MACH_EXTERNAL_అంతరాయం]  = mach_plic_handler;
	mcause_అంతరాయం_పట్టిక[RESERVED_INTERRUPT3]      = default_handler;
	mcause_అంతరాయం_పట్టిక[RESERVED_INTERRUPT4]      = default_handler;
	mcause_అంతరాయం_పట్టిక[RESERVED_INTERRUPT5]      = default_handler;
	mcause_అంతరాయం_పట్టిక[RESERVED_INTERRUPT6]      = default_handler;

	mcause_trap_పట్టిక[INSTRUCTION_చిరునామా_MISALIGNED] =
		default_handler;
	mcause_trap_పట్టిక[INSTRUCTION_ACCESS_FAULT] =
		default_handler;
	mcause_trap_పట్టిక[ILLEGAL_INSTRUCTION] =
		default_handler;
	mcause_trap_పట్టిక[BREAKPOINT] =
		default_handler;
	mcause_trap_పట్టిక[ఎక్కించు_చిరునామా_MISALIGNED] =
		default_handler;
	mcause_trap_పట్టిక[ఎక్కించు_ACCESS_FAULT] =
		default_handler;
	mcause_trap_పట్టిక[STORE_AMO_చిరునామా_MISALIGNED] =
		default_handler;
	mcause_trap_పట్టిక[STORE_AMO_ACCESS_FAULT] =
		default_handler;
	mcause_trap_పట్టిక[ENVIRONMENT_CALL_FROM_U_బహుళకం] =
		default_handler;
	mcause_trap_పట్టిక[ENVIRONMENT_CALL_FROM_S_బహుళకం] =
		default_handler;
	mcause_trap_పట్టిక[RESERVED_TRAP1] =
		default_handler;
	mcause_trap_పట్టిక[ENVIRONMENT_CALL_FROM_M_బహుళకం] =
		default_handler;
	mcause_trap_పట్టిక[INSTRUCTION_పుట_FAULT] =
		default_handler;
	mcause_trap_పట్టిక[ఎక్కించు_పుట_FAULT] =
		default_handler;
	mcause_trap_పట్టిక[RESERVED_TRAP2] =
		default_handler;
	mcause_trap_పట్టిక[STORE_AMO_పుట_FAULT] =
		default_handler;

	log_trace("trap_init exited \n ");
}

/** @fn void init(void)
 * @brief initialize the necessary variables for system start
 */
శూన్య init(శూన్య)
{
//	section_init(); // uncomment on need basis
	uart_init();

	log_trace("init entered \n ");

#నిర్వచితమైతే AARDONYX
	micron_disable_xip_volatile(0,0);
	flashMemInit();
#అయితే_ముగింపు

	trap_init();

	ప్రధాన();

	log_trace("init exited\n");
}
