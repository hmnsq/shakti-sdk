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

#ضمن <stdint.h>
#ضمن "uart.h"
#ضمن "qspi.h"
#ضمن "flashdata.h"

#تعریف_کړه DEBUG 1
#تعریف_کړه ERASE 1024

خارجي صحيح  حالت_2;

/** @fn void deploy()
 * @brief Deploys the hex file for a project to the flash device using QSPI
 * protocol. 
 */
فراغ deploy()
{
	صحيح ar_read,dum_معلومات,i;
	صحيح write_پته = 0x0;
	صحيح اندازه_byte=0;
	صحيح *config_string = (ثابت صحيح*)0x80000000;
	صحيح* read_معلومات_2 = (صحيح*)(0x90000000);

	qspi_init(27,0,3,1,15,1);
	waitfor(400);

	إذا(flashMemInit())
		أرجع -1;

	حالت_2=flash_Read_حالت_ثبتوونکی();

	چاپ_کړه("\t qspi status register %08x\n",حالت_2);

	إذا(flashWriteVolatileConfigReg(0x40404040)){
		چاپ_کړه("\t Volatile Configuration Register not Set -- Diagnose\n");
		أرجع -1;
	}

	حالت_2 = wait_for_wip();
	چاپ_کړه("\t qspi write  status register %08x\n",حالت_2);

	لكل(i=0;i<= write_معلومات_2[0];i+=4)
	{
		إذا(i%ERASE==0)
		{
			eraseSector(0x21, write_پته);
		}

		چاپ_کړه("%x %x %x %x %d\n", write_معلومات_2[i], write_معلومات_2[i+1],
		       write_معلومات_2[i+2], write_معلومات_2[i+3], write_پته);

		پاڼه_پروګرام_Quad_SPI(write_معلومات_2[i], write_معلومات_2[i+1],
				   write_معلومات_2[i+2], write_معلومات_2[i+3],
				   write_پته);
		write_پته+=16;
	}

#إذا DEBUG
	waitfor(400);

	flash_Enable4_Byte_Addressing_ډېرپېښ();
	flashQuadSPIDDRXip(0x000000, config_string);

	لكل(i=0;i<write_معلومات_2[0];++i)
	{
		dum_معلومات = get_qspi_shakti(read_معلومات_2);
		waitfor(100);

		چاپ_کړه("\n dum_data  %x \n",dum_معلومات);

		*config_string = dum_معلومات;

		config_string++;

		read_معلومات_2++;

		waitfor(100);

		reset_مداخله_flags();

		waitfor(10);
	}
	config_string++;

	micron_disable_xip_volatile(0,0);
	waitfor(400);
	flashMemInit();
#د_که_پای

	asm متطاير ("ebreak");
}

/** @fn void main()
 * @brief initiates by calling deploy function 
 */
فراغ اصلي(){

	deploy();
}
