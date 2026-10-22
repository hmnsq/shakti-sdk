/***************************************************************************
 * Project                         :  shakti devt board
 * Name of the file                :  deploy.c
 * Brief Description of file       :  Deploy elf into flash in board.
 * Name of Author    	           : 
 * Email ID                        : 

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
@file deploy.c
@brief Deploy elf into flash in board.
@detail Writes an array of hex values into the flash memory using QSPI.
*/

#include <stdint.h>
#include "uart.h"
#include "qspi.h"
#include "flashdata.h"

#define DEBUG 1
#define ERASE 1024

extern 정수  status;

/** @fn void deploy()
 * @brief Deploys the hex file for a project to the flash device using QSPI
 * protocol. 
 */
void deploy()
{
	정수 ar_read,dum_data,i;
	정수 write_address = 0x0;
	정수 size_byte=0;
	정수 *config_string = (const 정수*)0x80000000;
	정수* read_data = (정수*)(0x90000000);

	qspi_init(27,0,3,1,15,1);
	waitfor(400);

	만약(flashMemInit())
		반환 -1;

	status=flashReadStatusRegister();

	printf("\t qspi status register %08x\n",status);

	만약(flashWriteVolatileConfigReg(0x40404040)){
		printf("\t Volatile Configuration Register not Set -- Diagnose\n");
		반환 -1;
	}

	status = wait_for_wip();
	printf("\t qspi write  status register %08x\n",status);

	위해(i=0;i<= write_data[0];i+=4)
	{
		만약(i%ERASE==0)
		{
			eraseSector(0x21, write_address);
		}

		printf("%x %x %x %x %d\n", write_data[i], write_data[i+1],
		       write_data[i+2], write_data[i+3], write_address);

		pageProgramQuadSPI(write_data[i], write_data[i+1],
				   write_data[i+2], write_data[i+3],
				   write_address);
		write_address+=16;
	}

#만약 DEBUG
	waitfor(400);

	flashEnable4ByteAddressingMode();
	flashQuadSPIDDRXip(0x000000, config_string);

	위해(i=0;i<write_data[0];++i)
	{
		dum_data = get_qspi_shakti(read_data);
		waitfor(100);

		printf("\n dum_data  %x \n",dum_data);

		*config_string = dum_data;

		config_string++;

		read_data++;

		waitfor(100);

		reset_interrupt_flags();

		waitfor(10);
	}
	config_string++;

	micron_disable_xip_volatile(0,0);
	waitfor(400);
	flashMemInit();
#endif

	asm volatile ("ebreak");
}

/** @fn void main()
 * @brief initiates by calling deploy function 
 */
void main(){

	deploy();
}
