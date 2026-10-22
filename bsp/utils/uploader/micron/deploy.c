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

#अन्तर्भाव <stdint.h>
#अन्तर्भाव "uart.h"
#अन्तर्भाव "qspi.h"
#अन्तर्भाव "flashdata.h"

#परिभाषय DEBUG 1
#परिभाषय ERASE 1024

बाह्य पूर्णाङ्क  स्थितिः_2;

/** @fn void deploy()
 * @brief Deploys the hex file for a project to the flash device using QSPI
 * protocol. 
 */
शून्य deploy()
{
	पूर्णाङ्क ar_read,dum_दत्त,i;
	पूर्णाङ्क write_स्थानाङ्कः = 0x0;
	पूर्णाङ्क आकार_byte=0;
	पूर्णाङ्क *config_string = (ध्रुव पूर्णाङ्क*)0x80000000;
	पूर्णाङ्क* read_दत्त_2 = (पूर्णाङ्क*)(0x90000000);

	qspi_init(27,0,3,1,15,1);
	waitfor(400);

	यदि(flashMemInit())
		प्रत्यागम -1;

	स्थितिः_2=flash_Read_स्थितिः_पञ्जिकाकोशः();

	प्रारूप_लिख("\t qspi status register %08x\n",स्थितिः_2);

	यदि(flashWriteVolatileConfigReg(0x40404040)){
		प्रारूप_लिख("\t Volatile Configuration Register not Set -- Diagnose\n");
		प्रत्यागम -1;
	}

	स्थितिः_2 = wait_for_wip();
	प्रारूप_लिख("\t qspi write  status register %08x\n",स्थितिः_2);

	प्रति(i=0;i<= write_दत्त_2[0];i+=4)
	{
		यदि(i%ERASE==0)
		{
			eraseSector(0x21, write_स्थानाङ्कः);
		}

		प्रारूप_लिख("%x %x %x %x %d\n", write_दत्त_2[i], write_दत्त_2[i+1],
		       write_दत्त_2[i+2], write_दत्त_2[i+3], write_स्थानाङ्कः);

		page_क्रमादेशः_Quad_SPI(write_दत्त_2[i], write_दत्त_2[i+1],
				   write_दत्त_2[i+2], write_दत्त_2[i+3],
				   write_स्थानाङ्कः);
		write_स्थानाङ्कः+=16;
	}

#यदि DEBUG
	waitfor(400);

	flash_Enable4_Byte_Addressing_बहुलकम्();
	flashQuadSPIDDRXip(0x000000, config_string);

	प्रति(i=0;i<write_दत्त_2[0];++i)
	{
		dum_दत्त = get_qspi_shakti(read_दत्त_2);
		waitfor(100);

		प्रारूप_लिख("\n dum_data  %x \n",dum_दत्त);

		*config_string = dum_दत्त;

		config_string++;

		read_दत्त_2++;

		waitfor(100);

		reset_व्यवधानम्_flags();

		waitfor(10);
	}
	config_string++;

	micron_disable_xip_volatile(0,0);
	waitfor(400);
	flashMemInit();
#यदि_अन्तः

	asm चञ्चल ("ebreak");
}

/** @fn void main()
 * @brief initiates by calling deploy function 
 */
शून्य मुख्यम्(){

	deploy();
}
