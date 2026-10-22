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

#define DEBUG 1
#define ERASE 1024

बाह्य पूर्णांक  status;

/** @fn void deploy()
 * @brief Deploys the hex file for a project to the flash device using QSPI
 * protocol. 
 */
शून्य deploy()
{
	पूर्णांक ar_read,dum_data,i;
	पूर्णांक write_address = 0x0;
	पूर्णांक size_byte=0;
	पूर्णांक *config_string = (स्थिरांक पूर्णांक*)0x80000000;
	पूर्णांक* read_data = (पूर्णांक*)(0x90000000);

	qspi_init(27,0,3,1,15,1);
	waitfor(400);

	जर(flashMemInit())
		परत -1;

	status=flashReadStatusRegister();

	म_लिखो("\t qspi status register %08x\n",status);

	जर(flashWriteVolatileConfigReg(0x40404040)){
		म_लिखो("\t Volatile Configuration Register not Set -- Diagnose\n");
		परत -1;
	}

	status = wait_for_wip();
	म_लिखो("\t qspi write  status register %08x\n",status);

	साठी(i=0;i<= write_data[0];i+=4)
	{
		जर(i%ERASE==0)
		{
			eraseSector(0x21, write_address);
		}

		म_लिखो("%x %x %x %x %d\n", write_data[i], write_data[i+1],
		       write_data[i+2], write_data[i+3], write_address);

		pageProgramQuadSPI(write_data[i], write_data[i+1],
				   write_data[i+2], write_data[i+3],
				   write_address);
		write_address+=16;
	}

#जर DEBUG
	waitfor(400);

	flashEnable4ByteAddressingMode();
	flashQuadSPIDDRXip(0x000000, config_string);

	साठी(i=0;i<write_data[0];++i)
	{
		dum_data = get_qspi_shakti(read_data);
		waitfor(100);

		म_लिखो("\n dum_data  %x \n",dum_data);

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

	यंत्र अस्थिर ("ebreak");
}

/** @fn void main()
 * @brief initiates by calling deploy function 
 */
शून्य main(){

	deploy();
}
