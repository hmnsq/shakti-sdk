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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "uart.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "qspi.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "flashdata.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEBUG 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ERASE 1024

ਬਾਹਰੀ ਪੂਰਨ  ਸਥਿਤੀ_2;

/** @fn void deploy()
 * @brief Deploys the hex file for a project to the flash device using QSPI
 * protocol. 
 */
ਖਾਲੀ deploy()
{
	ਪੂਰਨ ar_read,dum_ਅੰਕੜੇ,i;
	ਪੂਰਨ write_ਪਤਾ = 0x0;
	ਪੂਰਨ ਮਾਪ_byte=0;
	ਪੂਰਨ *config_string = (ਅਚਲ ਪੂਰਨ*)0x80000000;
	ਪੂਰਨ* read_ਅੰਕੜੇ_2 = (ਪੂਰਨ*)(0x90000000);

	qspi_init(27,0,3,1,15,1);
	waitfor(400);

	ਜੇ(flashMemInit())
		ਵਾਪਸ -1;

	ਸਥਿਤੀ_2=flash_Read_ਸਥਿਤੀ_ਰਜਿਸਟਰ();

	ਲਿਖੋ("\t qspi status register %08x\n",ਸਥਿਤੀ_2);

	ਜੇ(flashWriteVolatileConfigReg(0x40404040)){
		ਲਿਖੋ("\t Volatile Configuration Register not Set -- Diagnose\n");
		ਵਾਪਸ -1;
	}

	ਸਥਿਤੀ_2 = wait_for_wip();
	ਲਿਖੋ("\t qspi write  status register %08x\n",ਸਥਿਤੀ_2);

	ਲਈ(i=0;i<= write_ਅੰਕੜੇ_2[0];i+=4)
	{
		ਜੇ(i%ERASE==0)
		{
			eraseSector(0x21, write_ਪਤਾ);
		}

		ਲਿਖੋ("%x %x %x %x %d\n", write_ਅੰਕੜੇ_2[i], write_ਅੰਕੜੇ_2[i+1],
		       write_ਅੰਕੜੇ_2[i+2], write_ਅੰਕੜੇ_2[i+3], write_ਪਤਾ);

		ਪੰਨਾ_ਪ੍ਰੋਗਰਾਮ_Quad_SPI(write_ਅੰਕੜੇ_2[i], write_ਅੰਕੜੇ_2[i+1],
				   write_ਅੰਕੜੇ_2[i+2], write_ਅੰਕੜੇ_2[i+3],
				   write_ਪਤਾ);
		write_ਪਤਾ+=16;
	}

#ਜੇ DEBUG
	waitfor(400);

	flash_Enable4_Byte_Addressing_ਬਹੁਲਕ();
	flashQuadSPIDDRXip(0x000000, config_string);

	ਲਈ(i=0;i<write_ਅੰਕੜੇ_2[0];++i)
	{
		dum_ਅੰਕੜੇ = get_qspi_shakti(read_ਅੰਕੜੇ_2);
		waitfor(100);

		ਲਿਖੋ("\n dum_data  %x \n",dum_ਅੰਕੜੇ);

		*config_string = dum_ਅੰਕੜੇ;

		config_string++;

		read_ਅੰਕੜੇ_2++;

		waitfor(100);

		reset_ਰੁਕਾਵਟ_flags();

		waitfor(10);
	}
	config_string++;

	micron_disable_xip_volatile(0,0);
	waitfor(400);
	flashMemInit();
#ਜੇ_ਅੰਤ

	asm ਅਸਥਿਰ ("ebreak");
}

/** @fn void main()
 * @brief initiates by calling deploy function 
 */
ਖਾਲੀ ਮੁੱਖ(){

	deploy();
}
