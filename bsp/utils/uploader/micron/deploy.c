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

#అన్తర్భావ <stdint.h>
#అన్తర్భావ "uart.h"
#అన్తర్భావ "qspi.h"
#అన్తర్భావ "flashdata.h"

#నిర్వచించు DEBUG 1
#నిర్వచించు ERASE 1024

బాహ్య పూర్ణాంకం  స్థితి_3;

/** @fn void deploy()
 * @brief Deploys the hex file for a project to the flash device using QSPI
 * protocol. 
 */
శూన్య deploy()
{
	పూర్ణాంకం ar_read,dum_దత్తాంశం,i;
	పూర్ణాంకం write_చిరునామా = 0x0;
	పూర్ణాంకం కొలత_byte=0;
	పూర్ణాంకం *config_string = (స్థిరరాశి పూర్ణాంకం*)0x80000000;
	పూర్ణాంకం* read_దత్తాంశం_2 = (పూర్ణాంకం*)(0x90000000);

	qspi_init(27,0,3,1,15,1);
	waitfor(400);

	ఒకవేళ(flashMemInit())
		తిరిగి -1;

	స్థితి_3=flash_Read_స్థితి_రిజిస్టరు();

	రాయి("\t qspi status register %08x\n",స్థితి_3);

	ఒకవేళ(flashWriteVolatileConfigReg(0x40404040)){
		రాయి("\t Volatile Configuration Register not Set -- Diagnose\n");
		తిరిగి -1;
	}

	స్థితి_3 = wait_for_wip();
	రాయి("\t qspi write  status register %08x\n",స్థితి_3);

	కొరకు(i=0;i<= write_దత్తాంశం_2[0];i+=4)
	{
		ఒకవేళ(i%ERASE==0)
		{
			eraseSector(0x21, write_చిరునామా);
		}

		రాయి("%x %x %x %x %d\n", write_దత్తాంశం_2[i], write_దత్తాంశం_2[i+1],
		       write_దత్తాంశం_2[i+2], write_దత్తాంశం_2[i+3], write_చిరునామా);

		పుట_కార్యక్రమం_Quad_SPI(write_దత్తాంశం_2[i], write_దత్తాంశం_2[i+1],
				   write_దత్తాంశం_2[i+2], write_దత్తాంశం_2[i+3],
				   write_చిరునామా);
		write_చిరునామా+=16;
	}

#ఒకవేళ DEBUG
	waitfor(400);

	flash_Enable4_Byte_Addressing_బహుళకం();
	flashQuadSPIDDRXip(0x000000, config_string);

	కొరకు(i=0;i<write_దత్తాంశం_2[0];++i)
	{
		dum_దత్తాంశం = get_qspi_shakti(read_దత్తాంశం_2);
		waitfor(100);

		రాయి("\n dum_data  %x \n",dum_దత్తాంశం);

		*config_string = dum_దత్తాంశం;

		config_string++;

		read_దత్తాంశం_2++;

		waitfor(100);

		reset_అంతరాయం_flags();

		waitfor(10);
	}
	config_string++;

	micron_disable_xip_volatile(0,0);
	waitfor(400);
	flashMemInit();
#అయితే_ముగింపు

	asm అస్థిర ("ebreak");
}

/** @fn void main()
 * @brief initiates by calling deploy function 
 */
శూన్య ప్రధాన(){

	deploy();
}
