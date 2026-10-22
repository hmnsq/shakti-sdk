/***************************************************************************
 * Project           	         : shakti devt board
 * Name of the file	     	 : qspi_micron.c
 * Brief Description of file     : source file for qspi_micron
 * Name of Author    	         : Vishvesh
 * Email ID                      : vishu.vivek@gmail.com

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
  @file qspi_micron.c
  @brief Contains the driver routines for QSPI interface.
  @detail The QSPI module driver supports QSPI driver routines for micron flash device.
 */

#అన్తర్భావ "qspi.h"
#అన్తర్భావ "utils.h"
#అన్తర్భావ "log.h"
#నిర్వచించు MEM_TYPE_N25Q256_ID 0x9d189d18

అక్షరం fail_బిట్టు = 0;
పూర్ణాంకం స్థితి_3 = 0;
/*! Pointer to QSPI registers */
పూర్ణాంకం* cr       =  (పూర్ణాంకం*) CR; /*! Control Register */
పూర్ణాంకం* dcr      =  (పూర్ణాంకం*) DCR; /*! Data Configuration Register */
పూర్ణాంకం* sr       =  (పూర్ణాంకం*) SR; /*! Status Register */
పూర్ణాంకం* fcr      =  (పూర్ణాంకం*) FCR; /* Flag Clear Register */
పూర్ణాంకం* ccr      =  (పూర్ణాంకం*) CCR; /* Commn. Configuration Register */
పూర్ణాంకం* ar       =  (పూర్ణాంకం*) AR; /*! Address Register */
పూర్ణాంకం* abr      =  (పూర్ణాంకం*) ABR; /*! Alternate Bytes Register */
పూర్ణాంకం* dr       =  (పూర్ణాంకం*) DR; /*! Data Register */
పూర్ణాంకం* dlr      =  (పూర్ణాంకం*) DLR; /*! Data Length Register */
పూర్ణాంకం* psmkr    =  (పూర్ణాంకం*) PSMKR; /*! Polling Status Mask Register */
పూర్ణాంకం* pir      =  (పూర్ణాంకం*) PIR; /*! Polling Interval Register */
పూర్ణాంకం* lprt     =  (పూర్ణాంకం*) LPRT; /*! Low power Time Register */
పూర్ణాంకం* startmm  =  (పూర్ణాంకం*) STARTMM; /*! Start Memory Map Register */
పూర్ణాంకం* endmm    =  (పూర్ణాంకం*) ENDMM; /*! End Memory Map Register */

/** @fn void set_qspi_shakti32(int* addr, int val)
 * @brief Writes 32 bit value into QSPI register.
 * @details Writes 32 bit value into passed address QSPI register.
 * @param int* addr --- Addresss where the data (val) needs to be written
 * @param int val ---  Data which needs to be written.
 */
శూన్య సమితి_qspi_shakti32(పూర్ణాంకం* addr, పూర్ణాంకం val)
{
	*addr = val;
}

/** @fn void set_qspi_shakti16(int16_t* addr, int16_t val)
 * @brief Writes 16 bit value 
 * @details Writes 16 bit value into 16bit QSPI register 
 * @param 16bit int* addr --- Addresss where the data (val) needs to be written
 * @param 16bit int val ---  Data which needs to be written.
 */
శూన్య సమితి_qspi_shakti16(int16_t* addr, int16_t val)
{
	*addr = val;
}

/** @fn void set_qspi_shakti8(char* addr, char val) 
 * @brief Writes 8 bit value.
 * @details Writes 8 bit value into 8 bit qspi register.
 * @param char* addr --- Addresss where the data (val) needs to be written
 * @param char val ---  Data which needs to be written.
 */
శూన్య సమితి_qspi_shakti8(అక్షరం* addr, అక్షరం val)
{
	*addr= val;
}

/** @fn int get_qspi_shakti(int* addr)
 * @brief reads from qspi register
 * @details Reads from the passed QSPI register and returns the value.
 * @param int* addr --- 32 bit Read Addresss  
 * @return Read value -- Read value from the passed value.
 */
పూర్ణాంకం get_qspi_shakti(పూర్ణాంకం* addr)
{
	తిరిగి *addr;
}

/** @fn void qspi_init(int fsize, int csht, int prescaler, int enable_interrupts, int fthreshold, int ck_mode)
 * @brief Initialises the qspi
 * @details Initialises the qspi registers for carrying out flash access operations.
 * @param int fsize --- No of address bits(fsize+1) required to address flash memory.
 * @param int csht --- Chip select high time (csht + 1 is the CS high time between flash commands).
 * @param int prescaler --- System clock divide factor (QSPI Clock = system clock / (prescaler clock + 1)
 * @param int ---  enable_interrupts that need to be enabled.
 * @param int --- FIFO threshold Level
 * @param int ck_mode --- Clock mode selection (Mode 0 and Mode 3)
 */
శూన్య qspi_init(పూర్ణాంకం fsize, పూర్ణాంకం csht, పూర్ణాంకం prescaler, పూర్ణాంకం enable_interrupts, పూర్ణాంకం fthreshold, పూర్ణాంకం ck_బహుళకం){
	పూర్ణాంకం int_సదిశ = enable_interrupts? (CR_TOIE|CR_SMIE|CR_FTIE|CR_TCIE|CR_TEIE) : 0; 
	సమితి_qspi_shakti32(dcr,(DCR_FSIZE(fsize)|DCR_CSHT(csht)|DCR_CKMODE(ck_బహుళకం))); 
	సమితి_qspi_shakti32(cr,(CR_PRESCALER(prescaler)|int_సదిశ|CR_FTHRES(fthreshold)|CR_EN));
}

/** @fn void reset_interrupt_flags()
 * @brief Resets interrupt flags.
 * @details Before carrying out any flash access operations, the interrupt flags are cleared.
 */
శూన్య reset_అంతరాయం_flags(){
	సమితి_qspi_shakti32(fcr,(FCR_CTOF|FCR_CSMF|FCR_CTCF|FCR_CTEF)); //Resetting all the flags
}

/** @fn int wait_for_tcf(int status)
 * @brief Wait for the transfer complete flag.
 * @details WCF bit status register indicates the completion of flash 
 *  operation. The same is cheked here.
 * @param int status register read value.
 * @return Zero on success else -1
 */
పూర్ణాంకం wait_for_tcf(పూర్ణాంకం స్థితి_3){
	పూర్ణాంకం timeout = DEF_TIMEOUT; 

	స్థితి_3 = get_qspi_shakti(sr);

	//    printf("status : %d looping?\n",status);

	అయితే(!( స్థితి_3 & 0x02 ) && --timeout){
		waitfor(1000);
		స్థితి_3=get_qspi_shakti(sr);
		రాయి("status: %08x in loop %d \n",స్థితి_3, !(స్థితి_3 & 0x02));
	}
	ఒకవేళ(timeout==0){
		రాయి("Request Timed out\n");
		తిరిగి -1;
	}
	తిరిగి 0;
}

/** @fn int check_fail_bit()
 * @brief Checks the value of fail_bit.
 * @details Checks the fail bit whether the value is zero or not.
 */
పూర్ణాంకం check_fail_బిట్టు(శూన్య){
	ఒకవేళ(fail_బిట్టు){
		fail_బిట్టు = 0;
		తిరిగి -1;
	}
	లేకపోతే{
		fail_బిట్టు = 0;
		తిరిగి 0;
	}
}

/** @fn int flashReadStatusRegister()
 * @brief Reads flash status register
 * @details Reads flash status register contents
 * @return Status register value on success; else -1
 */
పూర్ణాంకం flash_Read_స్థితి_రిజిస్టరు(){
	//    printf("\tReading the Status bits of the Flash\n");
	సమితి_qspi_shakti32(dlr,4);
	సమితి_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x05)|CCR_DMODE(SINGLE)));

	స్థితి_3 = 0;
	waitfor(1000);
	పూర్ణాంకం ret = wait_for_tcf(స్థితి_3);
	waitfor(100);
	పూర్ణాంకం విలువ = get_qspi_shakti(dr);
	//	printf("Read status register value %08x \n", value);
	reset_అంతరాయం_flags();
	ఒకవేళ(ret){
		రాయి("\tRead Status Register Failed\n");
		fail_బిట్టు = 1;
		తిరిగి -1;
	}
	లేకపోతే
		తిరిగి విలువ;
}

/** @fn int wait_for_wip()
 * @brief Wait till a flash access is complete.
 * @details Reads the WIP bit in the status register to check the completion of flash access.
 * Useful during flash write operations.
 * @return Zero on Success
 */
పూర్ణాంకం wait_for_wip(శూన్య){
	పూర్ణాంకం status1;
	చేయి{
		//  printf("\t Waiting for Wip \n");
		status1 = flash_Read_స్థితి_రిజిస్టరు(0x05);
		ఒకవేళ(check_fail_బిట్టు())
			తిరిగి -1;
		ఒకవేళ(status1 & 0x0){
			రాయి("\tQSPI: Programming Error - Diagnose\n");
			తిరిగి -1;
		}
		waitfor(20000);
	}అయితే(status1 & 0x01);
	//    printf("\t QSPI: Page Program/Erase Command Successfully Completed\n");
	తిరిగి 0;
}

/** @fn int micron_write_enable(int status)
 * @brief Enables the micron flash for write operation.
 * @details Enables micron flash for programming flash data.
 * @param int status --- Write enable status.
 * @return Zero on Success
 */
పూర్ణాంకం micron_write_enable(పూర్ణాంకం స్థితి_3){
	//  printf("\tWrite Enable\n");
	సమితి_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x06)));
	పూర్ణాంకం ret = wait_for_tcf(స్థితి_3); //Indicating the completion of command -- Currently polling
	//  printf("Status : %d dcr : %d cr: %d ccr: %d \n",status,*dcr,*cr,*ccr);
	తిరిగి ret;
}

/** @fn int pageProgramSingleSPI(int value1, int value2, int value3, int value4, int address)
 * @brief Writes into page of flash over single SPI.
 * @details Writes into micron flash page memory over legacy SPI
 * @param int value1 -- Value (MSB 32 bit) that needs to be written
 * @param int value2 -- Second 32 bit that neds to be written.
 * @param int value3 --- Third 32 bit that needs to be written.
 * @param int value4 --- Fourth 32 bit that needs to be written.
 * @param int address --- Address where data needs to be written.
 * @return Zero on Success else -1
 */
పూర్ణాంకం పుట_కార్యక్రమం_Single_SPI(పూర్ణాంకం value1, పూర్ణాంకం value2, పూర్ణాంకం value3, పూర్ణాంకం value4, పూర్ణాంకం చిరునామా){
	ఒకవేళ(micron_write_enable(స్థితి_3)){
		రాయి("Panic: Write Enable Command Failed to execute");
		తిరిగి -1;
	}
	reset_అంతరాయం_flags(); 

	సమితి_qspi_shakti32(dlr,DL(16));
	// set_qspi_shakti32(ccr,(CCR_DDRM | CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x12))); 
	సమితి_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x12)));
	సమితి_qspi_shakti32(ar, చిరునామా);        
	రాయి(" Address written %d \n",చిరునామా); 
	సమితి_qspi_shakti32(dr,value1);
	రాయి(" Value 1 written %d \n",value1);
	సమితి_qspi_shakti32(dr,value2);
	రాయి(" Value 2 written %d \n",value2);
	సమితి_qspi_shakti32(dr,value3);
	రాయి(" Value 3 written %d \n",value3);
	సమితి_qspi_shakti32(dr,value4);
	రాయి(" Value 4 written %d \n",value4);
	waitfor(150); 
	wait_for_tcf(స్థితి_3);
	reset_అంతరాయం_flags();
	తిరిగి wait_for_wip(); // Function which checks if WIP is done, indicating completion of Page Program
}

/** @fn int pageProgramQuadSPI(int value1, int value2, int value3, int value4, int address)
 * @brief Writes a page over QSPI
 * @details Writes a page over Quad SPI lines.
 * @param int value1 -- Value (MSB 32 bit) that needs to be written
 * @param int value2 -- Second 32 bit that neds to be written.
 * @param int value3 --- Third 32 bit that needs to be written.
 * @param int value4 --- Fourth 32 bit that needs to be written.
 * @param int address --- Address where data needs to be written.
 * @return Zero on success else -1
 */
పూర్ణాంకం పుట_కార్యక్రమం_Quad_SPI(పూర్ణాంకం value1, పూర్ణాంకం value2, పూర్ణాంకం value3, పూర్ణాంకం value4, పూర్ణాంకం చిరునామా){
	ఒకవేళ(micron_write_enable(స్థితి_3)){
		రాయి("Panic: Write Enable Command Failed to execute");
		తిరిగి -1;
	}
	reset_అంతరాయం_flags(); 

	సమితి_qspi_shakti32(dlr,DL(16));
	// set_qspi_shakti32(ccr,(CCR_DDRM | CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x12))); 
	సమితి_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(QUAD)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x34))); 
	సమితి_qspi_shakti32(ar, చిరునామా);
	సమితి_qspi_shakti32(dr,value1);
	సమితి_qspi_shakti32(dr,value2);
	సమితి_qspi_shakti32(dr,value3);
	సమితి_qspi_shakti32(dr,value4);
	waitfor(150); 
	wait_for_tcf(స్థితి_3);
	reset_అంతరాయం_flags();
	తిరిగి wait_for_wip(); // Function which checks if WIP is done, indicating completion of Page Program
}

/** @fn int flashIdentificationDevice()
 * @brief Reads flash id code.
 * @details Reads flash identification code from the flash device and checks whether it valid.
 * @return Zero on success else -1
 */
పూర్ణాంకం flashIdentificationDevice(శూన్య){
	log_debug("\tReading the ID register and discovering the Flash Device\n");
	సమితి_qspi_shakti32(dlr,4);
	సమితి_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x90)|CCR_ADSIZE(THREEBYTE)|CCR_ADMODE(SINGLE)|CCR_DMODE(SINGLE)));
	సమితి_qspi_shakti32(ar, 0);
	స్థితి_3 = 0; // Useless Variable but still!!!!
	పూర్ణాంకం ret = wait_for_tcf(స్థితి_3);
	పూర్ణాంకం విలువ = get_qspi_shakti(dr);
	log_info("\t device id %x\n",విలువ);
	reset_అంతరాయం_flags();
	ఒకవేళ(విలువ == MEM_TYPE_N25Q256_ID){
		రాయి("\tN25Q256 Device Detected \n");
		తిరిగి 0;
	}
	లేకపోతే{
		log_fatal("\t Device Not Detected - Diagnose %08x\n",విలువ);
		తిరిగి -1;
	}
}

/** @fn int flashMemInit()
 * @brief Initialises flash memory 
 * @details Initialises flash device and check for id code.
 * @return Zero on success else -1
 */
పూర్ణాంకం flashMemInit(){  //Supposedly a set of routines to check if the memory/interface or whatever is proper
	పూర్ణాంకం ret = flashIdentificationDevice();
	ఒకవేళ(ret==-1){
		log_fatal("Flash Mem Init Failed -- Quitting Program, Diagnose");
		తిరిగి ret;
	}
	లేకపోతే log_debug("Flash Mem Init Success\n");
	తిరిగి 0;
	//to fill in code
}


/** @fn int flashReadFlagRegister()
 * @brief Reads flash read flag. 
 * @details Reads the flash flag register.
 * @warning Not implemented now. Reserve for future.
 */
పూర్ణాంకం flash_Read_Flag_రిజిస్టరు(శూన్య){
	తిరిగి 0;
}

/** @fn int flashWriteEnable()
 * @brief Enables flash enable bit
 * @details For any write operation into to flash device (erase, program, etc.)
 *        this enable bit needs to be enabled.
 * @return TCF status
 */
పూర్ణాంకం flashWriteEnable(శూన్య){
	రాయి("\tWrite Enable\n");
	సమితి_qspi_shakti32(ccr,(CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x06)));
	పూర్ణాంకం ret = wait_for_tcf(0); //Indicating the completion of command -- Currently polling
	reset_అంతరాయం_flags();
	తిరిగి ret; 
}

/** @fn int flashEnable4ByteAddressingMode()
 * @brief Selects the addressed mode.
 * @details Before accessing flash device, the number of bits used for (Q)SPI needs to be programmed.
 * @return Status of the performed operation; else -1
 */
పూర్ణాంకం flash_Enable4_Byte_Addressing_బహుళకం(శూన్య){  //Enable 4-byte addressing Mode and read the status to verify that it has happened correctly

	ఒకవేళ(flashWriteEnable()){
		రాయి("\t Write Enable Failed \n");
		తిరిగి -1;
	}
	waitfor(100);
	సమితి_qspi_shakti32(ccr,(CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xB7)));
	//  int status =0; 
	స్థితి_3 = 0;
	పూర్ణాంకం ret = wait_for_tcf(స్థితి_3);
	reset_అంతరాయం_flags();
	waitfor(100);
	//Checking Phase
	స్థితి_3 = flash_Read_స్థితి_రిజిస్టరు();
	రాయి("\t Status Value: %08x\n",స్థితి_3);
	ఒకవేళ(స్థితి_3 & 1)
		రాయి("\t 4-Byte Addressing Mode is Enabled\n");
	లేకపోతే
		రాయి("\t 4-byte Addressing mode not Enabled\n");
}

/** @fn int flashReadSingleSPI(int dummy_cycles, int read_address, int instruction, int data_words, int adsize)
 * @brief Reads flash device over single SPI.
 * @details Reads the flash device over single spi (MOSI, MISO, CS, CLK)
 * @param int dummy_cycles -- No of dummy cycles needs to be added.
 * @param int read_address --- Address from where data needs to be read.
 * @param int instruction --- Read instruction (command) that needs to be sent.
 * @param int data_words --- Number of Data bytes (data_words + 1) needs to be read 
 * @param int adsize --- Address Size (8, 16, 24 & 32 bit address) 
 * @return Status of the performed operation; else -1
 */
పూర్ణాంకం flashReadSingleSPI(పూర్ణాంకం dummy_చక్రాలు, పూర్ణాంకం read_చిరునామా, పూర్ణాంకం instruction, పూర్ణాంకం దత్తాంశం_పదాలు, పూర్ణాంకం adsize){
	సమితి_qspi_shakti32(dlr,దత్తాంశం_పదాలు);
	సమితి_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(SINGLE)|CCR_DCYC(dummy_చక్రాలు)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_ADSIZE(adsize)|CCR_INSTRUCTION(instruction)));
	సమితి_qspi_shakti32(ar,read_చిరునామా);
	స్థితి_3 = 0;
	పూర్ణాంకం ret = wait_for_tcf(స్థితి_3);
	పూర్ణాంకం విలువ = get_qspi_shakti(dr);
	రాయి("\tThe Read Value: %08x\n",విలువ);
	//    printf("\tThe Read Value: %08x\n",value);
	ఒకవేళ(ret){
		రాయి("\t Read Value Failed \n");
		తిరిగి -1;
	}
	reset_అంతరాయం_flags();
	తిరిగి విలువ;
}

/** @fn int flashReadDualSPI(int address, int data_length)
 * @brief  Reads flash device over two io lines SPI.
 * @details Reads the flash device over two io lines for spi (IO1, IO2, CS, CLK) data
 * @param int address --- Address which needs to be read.
 * @param int data_length --- Number of Data bytes (data_words + 1) needs to be read 
 * @return Status of the performed operation; else -1
 */
పూర్ణాంకం flashReadDualSPI(పూర్ణాంకం చిరునామా, పూర్ణాంకం దత్తాంశం_నిడివి){
	సమితి_qspi_shakti32(dlr,దత్తాంశం_నిడివి); //DLR
	సమితి_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(DOUBLE)|CCR_DCYC(3)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBB)));
	సమితి_qspi_shakti32(ar,చిరునామా); 
	//    printf("Status : %08x dcr : %08x cr : %08x ccr : %08x dlr: %08x ar: %08x\n",status,*dcr,*cr,*ccr,*dlr,*ar);
	పూర్ణాంకం ret = wait_for_tcf(స్థితి_3);
	పూర్ణాంకం విలువ = get_qspi_shakti(dr);
	రాయి("\tThe Read Value: %08x\n",విలువ);	
	ఒకవేళ(ret){
		రాయి("\t QSPI: Read Value failed\n");
		తిరిగి -1;
	}
	//*config_string = get_qspi_shakti(dr);
	//printf("\t Read Data is %08x\n",read_data);
	reset_అంతరాయం_flags();
	తిరిగి విలువ;
}

/** @fn int flashReadQuadSPI(int dummy_cycles, int read_address, int instruction, int data_words, int adsize)
 * @brief  Reads flash device over four io lines SPI.
 * @details Reads the flash device over two io lines for spi (IO1, IO2, IO3, IO4, CS, CLK) data
 * @param int dummy_cycles -- No of dummy cycles needs to be added.
 * @param int read_address --- Address from where data needs to be read.
 * @param int instruction --- Read instruction (command) that needs to be sent.
 * @param int data_words --- Number of Data bytes (data_words + 1) needs to be read 
 * @param int adsize --- Address Size (8, 16, 24 & 32 bit address) 
 * @return Status of the performed operation; else -1
 */
పూర్ణాంకం flashReadQuadSPI(పూర్ణాంకం dummy_చక్రాలు, పూర్ణాంకం read_చిరునామా, పూర్ణాంకం instruction, పూర్ణాంకం దత్తాంశం_పదాలు, పూర్ణాంకం adsize){
	సమితి_qspi_shakti32(dlr,దత్తాంశం_పదాలు);
	సమితి_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DCYC(dummy_చక్రాలు)|CCR_ADSIZE(adsize)|CCR_ADMODE(QUAD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(instruction)));
	సమితి_qspi_shakti32(ar,read_చిరునామా);
	స్థితి_3 = 0;
	పూర్ణాంకం ret = wait_for_tcf(స్థితి_3);
	పూర్ణాంకం విలువ_1 = get_qspi_shakti(dr);
	పూర్ణాంకం విలువ_2_2 = get_qspi_shakti(dr);
	పూర్ణాంకం విలువ_3 = get_qspi_shakti(dr);
	పూర్ణాంకం విలువ_4 = get_qspi_shakti(dr);
	రాయి("\tThe Read Value: %08x, %08x, %08x and %08x \n",విలువ_1,విలువ_2_2,విలువ_3,విలువ_4);
	ఒకవేళ(ret){
		రాయి("\t Read Value Failed \n");
		తిరిగి -1; 
	}   
	reset_అంతరాయం_flags();
	తిరిగి విలువ_1;
}

/** @fn int flashSingleSPIXip(int addr, int* dest_addr) 
 * @brief Reads over single SPI XIP
 * @details Generic Read for xip SPI Read.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on success.
 */
పూర్ణాంకం flashSingleSPIXip(పూర్ణాంకం addr, పూర్ణాంకం* dest_addr){
	సమితి_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(SINGLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(7)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x0C)));
	సమితి_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_బహుళకం_BYTE(0x00)|DCR_CKMODE(1)));
	సమితి_qspi_shakti32(dlr,0x4);
	సమితి_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	స్థితి_3=0;
	wait_for_tcf(స్థితి_3);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	రాయి("\n Fisrt value obtained through single read : %d \n ",*dest_addr);
	reset_అంతరాయం_flags(); 
	రాయి("\t Trying XIP now\n");
	సమితి_qspi_shakti32(ccr, (CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(SINGLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(7)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x0C)));
	సమితి_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_బహుళకం_BYTE(0x00)|DCR_CKMODE(1))); 
	waitfor(25);
	తిరిగి 0;
}

/** @fn int flashSingleSPIDDRXip(int addr, int* dest_addr)  
 * @brief Reads over DDR XIP mode.
 * @details Reads for DDR based XIP mode.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
పూర్ణాంకం flashSingleSPIDDRXip(పూర్ణాంకం addr, పూర్ణాంకం* dest_addr){
	సమితి_qspi_shakti32(ccr,(CCR_DDRM|CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(SINGLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(15)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x0E)));
	సమితి_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_బహుళకం_BYTE(0x00)|DCR_CKMODE(1)));
	సమితి_qspi_shakti32(dlr,0x4);
	సమితి_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	స్థితి_3=0;
	wait_for_tcf(స్థితి_3);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	reset_అంతరాయం_flags(); 
	రాయి("\t Trying XIP now\n");
	సమితి_qspi_shakti32(ccr, (CCR_DDRM|CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(SINGLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(14)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x0E)));
	సమితి_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_బహుళకం_BYTE(0x00)|DCR_CKMODE(1))); 
	waitfor(25);
	తిరిగి 0;
}

/** @fn int flashDualSPIXip(int addr, int* dest_addr)
 * @brief Reads over XIP mode.
 * @details Reads for XIP mode using two io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
పూర్ణాంకం flashDualSPIXip(పూర్ణాంకం addr, పూర్ణాంకం* dest_addr){
	సమితి_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(DOUBLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(3)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBB)));
	సమితి_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_బహుళకం_BYTE(0xA0)|DCR_CKMODE(1)));
	సమితి_qspi_shakti32(dlr,0x4);
	సమితి_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	స్థితి_3=0;
	wait_for_tcf(స్థితి_3);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	రాయి("\n Fisrt value obtained through single read : %d \n ",*dest_addr);
	reset_అంతరాయం_flags(); 
	రాయి("\t Trying XIP now\n");
	సమితి_qspi_shakti32(ccr, (CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(DOUBLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(3)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(NDATA)));
	సమితి_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_బహుళకం_BYTE(0xA0)|DCR_CKMODE(1))); 
	waitfor(25);
	తిరిగి 0;
}

/** @fn int flashDualSPIDDRXip(int addr, int* dest_addr) 
 * @brief Reads over XIP mode.
 * @details Reads for DDR based XIP mode using two io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
పూర్ణాంకం flashDualSPIDDRXip(పూర్ణాంకం addr, పూర్ణాంకం* dest_addr){
	సమితి_qspi_shakti32(ccr,(CCR_DDRM|CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(DOUBLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(6)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBE)));
	సమితి_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_బహుళకం_BYTE(0xA0)|DCR_CKMODE(1)));
	సమితి_qspi_shakti32(dlr,0x4);
	సమితి_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	స్థితి_3=0;
	wait_for_tcf(స్థితి_3);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	reset_అంతరాయం_flags(); 
	రాయి("\t Trying XIP now\n");
	సమితి_qspi_shakti32(ccr, (CCR_DDRM|CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(DOUBLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(6)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(NDATA)));
	సమితి_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_బహుళకం_BYTE(0xA0)|DCR_CKMODE(1))); 
	waitfor(25);
	తిరిగి 0;
}

/** @fn int flashWriteVolatileConfigReg(int value) 
 * @brief Writes into flash volatile configuration register.
 * @details Writes the passed value into flash volatile configuration register.
 * @param int value needs to written into Write Volatile Config Register.
 * @return Zero on Success
 */
పూర్ణాంకం flashWriteVolatileConfigReg(పూర్ణాంకం విలువ){
	రాయి("\t Setting Volatile Configuration Register with the Value: %08x\n",విలువ);
	ఒకవేళ(micron_write_enable(స్థితి_3)){
		రాయి("Panic: Write Enable Command Failed to execute\n");
		తిరిగి -1;
	}
	reset_అంతరాయం_flags();
	//	flashReadStatusRegister();
	సమితి_qspi_shakti32(dlr,DL(1));
	సమితి_qspi_shakti8(dr,విలువ);  //The value to be written into the VECR register to enable XIP. Indicating XIP to operate in Quad Mode
	సమితి_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x01)));
	waitfor(50);
	స్థితి_3=0;
	పూర్ణాంకం ret = wait_for_tcf(స్థితి_3);
	//    printf("Status : %d dcr : %d cr : %d ccr : %d dlr: %d dr: %d\n",status,*dcr,*cr,*ccr,*dlr,*dr);
	reset_అంతరాయం_flags();
	waitfor(50);  //Giving Micron time to store the data
	తిరిగి ret;
}

/** @fn int flashQuadSPIXip(int addr, int* dest_addr)
 * @brief Reads over XIP mode.
 * @details Reads for DDR based XIP mode using quad io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
పూర్ణాంకం flashQuadSPIXip(పూర్ణాంకం addr, పూర్ణాంకం* dest_addr){
	ఒకవేళ(flashWriteVolatileConfigReg(0x40404040)){
		రాయి("\t Volatile Configuration Register not Set -- Diagnose\n");
		తిరిగి -1;
	}
	స్థితి_3 = wait_for_wip();
	రాయి("\t qspi status register %08x\n",స్థితి_3);
	reset_అంతరాయం_flags();
	సమితి_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(5)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xEC)));
	సమితి_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_బహుళకం_BYTE(0xA0)|DCR_CKMODE(1)));
	సమితి_qspi_shakti32(dlr,0x4);
	సమితి_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	స్థితి_3=0;
	wait_for_tcf(స్థితి_3);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	reset_అంతరాయం_flags(); 
	రాయి("\t Trying XIP now\n");
	సమితి_qspi_shakti32(ccr, (CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(QUAD)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(5)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(NDATA)));
	సమితి_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_బహుళకం_BYTE(0xA0)|DCR_CKMODE(1))); 
	waitfor(25);
	తిరిగి 0;
}

/** @fn int flashQuadSPIDDRXip(int addr, int* dest_addr)
 * @brief Reads over XIP mode.
 * @details Reads for DDR based XIP mode using four io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
పూర్ణాంకం flashQuadSPIDDRXip(పూర్ణాంకం addr, పూర్ణాంకం* dest_addr){
	ఒకవేళ(flashWriteVolatileConfigReg(0x40404040)){
		రాయి("\t Volatile Configuration Register not Set -- Diagnose\n");
		తిరిగి -1;
	}
	స్థితి_3 = wait_for_wip();
	రాయి("\t qspi status register %08x\n",స్థితి_3);
	reset_అంతరాయం_flags();
	సమితి_qspi_shakti32(ccr,(CCR_DDRM|CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(10)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xEE)));
	సమితి_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_బహుళకం_BYTE(0xA0)|DCR_CKMODE(1)));
	సమితి_qspi_shakti32(dlr,0x4);
	సమితి_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	స్థితి_3=0;
	wait_for_tcf(స్థితి_3);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	reset_అంతరాయం_flags(); 
	రాయి("\t Trying XIP now\n");
	సమితి_qspi_shakti32(ccr, (CCR_DDRM|CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(QUAD)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(10)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(NDATA)));
	సమితి_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_బహుళకం_BYTE(0xA0)|DCR_CKMODE(1))); 
	waitfor(25);
	తిరిగి 0;
}

/** @fn int flash_Write_disable()
 * @brief disables write operation
 * @details Write operation can be possible only after enabling write enable register.
 *       Here this is disabled using this function.
 * @return Zero on Success
 */
పూర్ణాంకం flash_Write_disable(శూన్య){
	రాయి("\tWrite disable\n");
	సమితి_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x04)));
	పూర్ణాంకం ret = wait_for_tcf(స్థితి_3); //Indicating the completion of command -- Currently polling
	రాయి("Status : %d dcr : %d cr: %d ccr: %d \n",స్థితి_3,*dcr,*cr,*ccr);
	reset_అంతరాయం_flags();
	తిరిగి wait_for_wip();
}

/** @fn int eraseSector(int command, int address)
 * @brief Erases one sector 
 * @details Erases a complete sector which falls in the sector range.
 * @param int command --- Erase command (sector erase, block erase or chip erase)
 * @param int address --- Starting address of erase.
 * @return Zero on Success
 */
పూర్ణాంకం eraseSector(పూర్ణాంకం command, పూర్ణాంకం చిరునామా){
	ఒకవేళ(micron_write_enable(స్థితి_3)){
		రాయి("Panic: Write Enable Command Failed to execute");
		తిరిగి -1;
	}
	reset_అంతరాయం_flags();
	సమితి_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(command)));
	సమితి_qspi_shakti32(ar,చిరునామా);
	waitfor(150);
	పూర్ణాంకం ret = wait_for_tcf(స్థితి_3);
	reset_అంతరాయం_flags();
	తిరిగి wait_for_wip(); //For sector erase maybe estat should be checked
}

/** @fn int micron_volatile_write_enable(int status) 
 * @brief Enable for volatile write.
 * @details Enables micron flash for programming volatile config. register.
 * @param int --- status register value.
 * @return Zero on Success
 */
పూర్ణాంకం micron_volatile_write_enable(పూర్ణాంకం స్థితి_3){
	రాయి("\tVolatile Write Enable\n");
	సమితి_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x50)));
	పూర్ణాంకం ret = wait_for_tcf(స్థితి_3); //Indicating the completion of command -- Currently polling
	రాయి("Status : %d dcr : %d cr: %d ccr: %d \n",స్థితి_3,*dcr,*cr,*ccr);
	తిరిగి ret;
}

/** @fn int micron_enable_4byte_addressing(int status) 
 * @brief Enables micron flash for 4 byte addressing.
 * @details Address can be passed as 3 bytes or 4 bytes before read or write 
 * operation. This function sets the number of address bytes to 4 bytes.
 * @param int --- status register value
 * @return Zero on Success
 */
పూర్ణాంకం micron_enable_4byte_addressing(పూర్ణాంకం స్థితి_3){
	రాయి("\t Enable 4 byte address \n");
	సమితి_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xB7)));
	పూర్ణాంకం ret = wait_for_tcf(స్థితి_3); //Indicating the completion of command -- Currently polling
	రాయి("Status : %d dcr : %d cr: %d ccr: %d \n",స్థితి_3,*dcr,*cr,*ccr);
	తిరిగి ret;
}

/** @fn int micron_configure_xip_volatile(int status, int value)
 * @brief Configures the xip volatile config. register.
 * @details Configures the volatile config. register for xip Read mode.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
పూర్ణాంకం micron_configure_xip_volatile(పూర్ణాంకం స్థితి_3, పూర్ణాంకం విలువ){
	log_debug("\tWrite Volatile Configuration Register\n");
	సమితి_qspi_shakti32(dlr,DL(1));
	సమితి_qspi_shakti8(dr,విలువ);  //The value to be written into the VECR register to enable XIP. Indicating XIP to operate in Quad Mode
	సమితి_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x81)));
	waitfor(50);
	పూర్ణాంకం ret = wait_for_tcf(స్థితి_3);
	రాయి("Status : %d dcr : %d cr : %d ccr : %d dlr: %d dr: %d\n",స్థితి_3,*dcr,*cr,*ccr,*dlr,*dr);
	waitfor(50);  //Giving Micron time to store the data
	తిరిగి ret;
}

/** @fn int micron_disable_xip_volatile(int status, int value)
 * @brief Configures(disables) the xip volatile config. register.
 * @details Configures(disables) the volatile config. register for xip Read mode.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
పూర్ణాంకం micron_disable_xip_volatile(పూర్ణాంకం స్థితి_3, __attribute__ ((వాడని)) పూర్ణాంకం విలువ){
	log_debug("\tWrite Volatile Configuration Register to exit XIP\n");
	సమితి_qspi_shakti32(cr,(CR_PRESCALER(0x3)|CR_TOIE|CR_TCIE|CR_TEIE|CR_SMIE|CR_FTIE|CR_ABORT|CR_EN));
	waitfor(30);
	qspi_init(27,0,3,1,15,1);
	సమితి_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DUMMY_బిట్టు|CCR_DUMMY_CONFIRMATION|CCR_DCYC(8)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(NDATA)));
	సమితి_qspi_shakti32(ar,0x00000); //Dummy address 
	సమితి_qspi_shakti32(dlr,1);

	పూర్ణాంకం ret = wait_for_tcf(స్థితి_3);
	పూర్ణాంకం తాత్కాలిక_దత్తాంశం = get_qspi_shakti(dr);

	waitfor(50);
	reset_అంతరాయం_flags();
	తిరిగి ret;
}

/** @fn int micron_read_id_cmd(int status, int value)
 * @brief Reads the id of the micron flash.
 * @details Micron flash is having a fixed value as ID during production. This 
 * value is read to confirm proper flash device.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
పూర్ణాంకం micron_read_id_cmd(పూర్ణాంకం స్థితి_3, పూర్ణాంకం విలువ){
	log_debug("\tRead ID Command to see if the Protocol is Proper\n");
	సమితి_qspi_shakti32(dlr,4);
	సమితి_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x9E)|CCR_DMODE(SINGLE)));
	పూర్ణాంకం ret = wait_for_tcf(స్థితి_3);
	విలువ = get_qspi_shakti(dr);
	రాయి("Read ID: %08x",విలువ);
	తిరిగి ret;
}

/** @fn int micron_read_configuration_register(int status, int value)
 * @brief Reads configuration register. 
 * @details The configurartion register is read using this function.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
పూర్ణాంకం micron_read_configuration_రిజిస్టరు(పూర్ణాంకం స్థితి_3, పూర్ణాంకం విలువ){
	రాయి("\tRead ID Command to see if the Protocol is Proper\n");
	సమితి_qspi_shakti32(dlr,4);
	సమితి_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBE)|CCR_DMODE(SINGLE)));
	పూర్ణాంకం ret = wait_for_tcf(స్థితి_3);
	విలువ = get_qspi_shakti(dr);
	log_debug("Configuration Register Value: %08x",విలువ);
	తిరిగి ret;
}
