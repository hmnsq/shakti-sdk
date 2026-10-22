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

#تعریف_کرو DEBUG 1
#تعریف_کرو ERASE 1024

خارجي صحيح  حالت_2;

/** @fn void deploy()
 * @brief Deploys the hex file for a project to the flash device using QSPI
 * protocol. 
 */
فراغ deploy()
{
	صحيح ar_read,dum_انکڑے,i;
	صحيح write_پتہ = 0x0;
	صحيح ناپ_byte=0;
	صحيح *config_string = (ثابت صحيح*)0x80000000;
	صحيح* read_انکڑے_2 = (صحيح*)(0x90000000);

	qspi_init(27,0,3,1,15,1);
	waitfor(400);

	إذا(flashMemInit())
		أرجع -1;

	حالت_2=flash_Read_حالت_رجسٹر();

	لکھو("\t qspi status register %08x\n",حالت_2);

	إذا(flashWriteVolatileConfigReg(0x40404040)){
		لکھو("\t Volatile Configuration Register not Set -- Diagnose\n");
		أرجع -1;
	}

	حالت_2 = wait_for_wip();
	لکھو("\t qspi write  status register %08x\n",حالت_2);

	لكل(i=0;i<= write_انکڑے_2[0];i+=4)
	{
		إذا(i%ERASE==0)
		{
			eraseSector(0x21, write_پتہ);
		}

		لکھو("%x %x %x %x %d\n", write_انکڑے_2[i], write_انکڑے_2[i+1],
		       write_انکڑے_2[i+2], write_انکڑے_2[i+3], write_پتہ);

		ورقہ_پروگرام_Quad_SPI(write_انکڑے_2[i], write_انکڑے_2[i+1],
				   write_انکڑے_2[i+2], write_انکڑے_2[i+3],
				   write_پتہ);
		write_پتہ+=16;
	}

#إذا DEBUG
	waitfor(400);

	flash_Enable4_Byte_Addressing_منوال();
	flashQuadSPIDDRXip(0x000000, config_string);

	لكل(i=0;i<write_انکڑے_2[0];++i)
	{
		dum_انکڑے = get_qspi_shakti(read_انکڑے_2);
		waitfor(100);

		لکھو("\n dum_data  %x \n",dum_انکڑے);

		*config_string = dum_انکڑے;

		config_string++;

		read_انکڑے_2++;

		waitfor(100);

		reset_رکاوٹ_flags();

		waitfor(10);
	}
	config_string++;

	micron_disable_xip_volatile(0,0);
	waitfor(400);
	flashMemInit();
#جے_انت

	asm متطاير ("ebreak");
}

/** @fn void main()
 * @brief initiates by calling deploy function 
 */
فراغ مکھ(){

	deploy();
}
