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

#شامل <stdint.h>
#شامل "uart.h"
#شامل "qspi.h"
#شامل "flashdata.h"

#تعریف_کرو DEBUG 1
#تعریف_کرو ERASE 1024

خارجی صحیح  حالت_3;

/** @fn void deploy()
 * @brief Deploys the hex file for a project to the flash device using QSPI
 * protocol. 
 */
خالی deploy()
{
	صحیح ar_read,dum_ڈیٹا,i;
	صحیح write_پتہ = 0x0;
	صحیح سائز_byte=0;
	صحیح *config_string = (ثابت صحیح*)0x80000000;
	صحیح* read_ڈیٹا_2 = (صحیح*)(0x90000000);

	qspi_init(27,0,3,1,15,1);
	waitfor(400);

	اگر(flashMemInit())
		واپس -1;

	حالت_3=flash_Read_حالت_رجسٹر();

	لکھو("\t qspi status register %08x\n",حالت_3);

	اگر(flashWriteVolatileConfigReg(0x40404040)){
		لکھو("\t Volatile Configuration Register not Set -- Diagnose\n");
		واپس -1;
	}

	حالت_3 = wait_for_wip();
	لکھو("\t qspi write  status register %08x\n",حالت_3);

	برائے(i=0;i<= write_ڈیٹا_2[0];i+=4)
	{
		اگر(i%ERASE==0)
		{
			eraseSector(0x21, write_پتہ);
		}

		لکھو("%x %x %x %x %d\n", write_ڈیٹا_2[i], write_ڈیٹا_2[i+1],
		       write_ڈیٹا_2[i+2], write_ڈیٹا_2[i+3], write_پتہ);

		صفحہ_پروگرام_Quad_SPI(write_ڈیٹا_2[i], write_ڈیٹا_2[i+1],
				   write_ڈیٹا_2[i+2], write_ڈیٹا_2[i+3],
				   write_پتہ);
		write_پتہ+=16;
	}

#اگر DEBUG
	waitfor(400);

	flash_Enable4_Byte_Addressing_منوال();
	flashQuadSPIDDRXip(0x000000, config_string);

	برائے(i=0;i<write_ڈیٹا_2[0];++i)
	{
		dum_ڈیٹا = get_qspi_shakti(read_ڈیٹا_2);
		waitfor(100);

		لکھو("\n dum_data  %x \n",dum_ڈیٹا);

		*config_string = dum_ڈیٹا;

		config_string++;

		read_ڈیٹا_2++;

		waitfor(100);

		reset_مداخلت_flags();

		waitfor(10);
	}
	config_string++;

	micron_disable_xip_volatile(0,0);
	waitfor(400);
	flashMemInit();
#اگر_ختم

	asm متلون ("ebreak");
}

/** @fn void main()
 * @brief initiates by calling deploy function 
 */
خالی مین(){

	deploy();
}
