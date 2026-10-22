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

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ "uart.h"
#ಅನ್ತರ್ಭಾವ "qspi.h"
#ಅನ್ತರ್ಭಾವ "flashdata.h"

#ವ್ಯಾಖ್ಯಾನಿಸು DEBUG 1
#ವ್ಯಾಖ್ಯಾನಿಸು ERASE 1024

ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ  ಸ್ಥಿತಿ_3;

/** @fn void deploy()
 * @brief Deploys the hex file for a project to the flash device using QSPI
 * protocol. 
 */
ಶೂನ್ಯ deploy()
{
	ಪೂರ್ಣಾಂಕ ar_read,dum_ದತ್ತಾಂಶ,i;
	ಪೂರ್ಣಾಂಕ write_ವಿಳಾಸ = 0x0;
	ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_byte=0;
	ಪೂರ್ಣಾಂಕ *config_string = (ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ*)0x80000000;
	ಪೂರ್ಣಾಂಕ* read_ದತ್ತಾಂಶ_2 = (ಪೂರ್ಣಾಂಕ*)(0x90000000);

	qspi_init(27,0,3,1,15,1);
	waitfor(400);

	ಆದರೆ(flashMemInit())
		ಹಿಂತಿರುಗಿ -1;

	ಸ್ಥಿತಿ_3=flash_Read_ಸ್ಥಿತಿ_ರಿಜಿಸ್ಟರ್();

	ಬರೆ("\t qspi status register %08x\n",ಸ್ಥಿತಿ_3);

	ಆದರೆ(flashWriteVolatileConfigReg(0x40404040)){
		ಬರೆ("\t Volatile Configuration Register not Set -- Diagnose\n");
		ಹಿಂತಿರುಗಿ -1;
	}

	ಸ್ಥಿತಿ_3 = wait_for_wip();
	ಬರೆ("\t qspi write  status register %08x\n",ಸ್ಥಿತಿ_3);

	ಗಾಗಿ(i=0;i<= write_ದತ್ತಾಂಶ_2[0];i+=4)
	{
		ಆದರೆ(i%ERASE==0)
		{
			eraseSector(0x21, write_ವಿಳಾಸ);
		}

		ಬರೆ("%x %x %x %x %d\n", write_ದತ್ತಾಂಶ_2[i], write_ದತ್ತಾಂಶ_2[i+1],
		       write_ದತ್ತಾಂಶ_2[i+2], write_ದತ್ತಾಂಶ_2[i+3], write_ವಿಳಾಸ);

		ಪುಟ_ಕಾರ್ಯಕ್ರಮ_Quad_SPI(write_ದತ್ತಾಂಶ_2[i], write_ದತ್ತಾಂಶ_2[i+1],
				   write_ದತ್ತಾಂಶ_2[i+2], write_ದತ್ತಾಂಶ_2[i+3],
				   write_ವಿಳಾಸ);
		write_ವಿಳಾಸ+=16;
	}

#ಆದರೆ DEBUG
	waitfor(400);

	flash_Enable4_Byte_Addressing_ಬಹುಲಕ();
	flashQuadSPIDDRXip(0x000000, config_string);

	ಗಾಗಿ(i=0;i<write_ದತ್ತಾಂಶ_2[0];++i)
	{
		dum_ದತ್ತಾಂಶ = get_qspi_shakti(read_ದತ್ತಾಂಶ_2);
		waitfor(100);

		ಬರೆ("\n dum_data  %x \n",dum_ದತ್ತಾಂಶ);

		*config_string = dum_ದತ್ತಾಂಶ;

		config_string++;

		read_ದತ್ತಾಂಶ_2++;

		waitfor(100);

		reset_ಅಡಚಣೆ_flags();

		waitfor(10);
	}
	config_string++;

	micron_disable_xip_volatile(0,0);
	waitfor(400);
	flashMemInit();
#ಆದರೆ_ಅಂತ್ಯ

	asm ಅಸ್ಥಿರ ("ebreak");
}

/** @fn void main()
 * @brief initiates by calling deploy function 
 */
ಶೂನ್ಯ ಮುಖ್ಯ(){

	deploy();
}
