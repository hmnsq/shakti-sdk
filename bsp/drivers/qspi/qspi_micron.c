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

#अन्तर्भाव "qspi.h"
#अन्तर्भाव "utils.h"
#अन्तर्भाव "log.h"
#परिभाषय MEM_TYPE_N25Q256_ID 0x9d189d18

वर्ण fail_bit = 0;
पूर्णाङ्क स्थितिः_2 = 0;
/*! Pointer to QSPI registers */
पूर्णाङ्क* cr       =  (पूर्णाङ्क*) CR; /*! Control Register */
पूर्णाङ्क* dcr      =  (पूर्णाङ्क*) DCR; /*! Data Configuration Register */
पूर्णाङ्क* sr       =  (पूर्णाङ्क*) SR; /*! Status Register */
पूर्णाङ्क* fcr      =  (पूर्णाङ्क*) FCR; /* Flag Clear Register */
पूर्णाङ्क* ccr      =  (पूर्णाङ्क*) CCR; /* Commn. Configuration Register */
पूर्णाङ्क* ar       =  (पूर्णाङ्क*) AR; /*! Address Register */
पूर्णाङ्क* abr      =  (पूर्णाङ्क*) ABR; /*! Alternate Bytes Register */
पूर्णाङ्क* dr       =  (पूर्णाङ्क*) DR; /*! Data Register */
पूर्णाङ्क* dlr      =  (पूर्णाङ्क*) DLR; /*! Data Length Register */
पूर्णाङ्क* psmkr    =  (पूर्णाङ्क*) PSMKR; /*! Polling Status Mask Register */
पूर्णाङ्क* pir      =  (पूर्णाङ्क*) PIR; /*! Polling Interval Register */
पूर्णाङ्क* lprt     =  (पूर्णाङ्क*) LPRT; /*! Low power Time Register */
पूर्णाङ्क* startmm  =  (पूर्णाङ्क*) STARTMM; /*! Start Memory Map Register */
पूर्णाङ्क* endmm    =  (पूर्णाङ्क*) ENDMM; /*! End Memory Map Register */

/** @fn void set_qspi_shakti32(int* addr, int val)
 * @brief Writes 32 bit value into QSPI register.
 * @details Writes 32 bit value into passed address QSPI register.
 * @param int* addr --- Addresss where the data (val) needs to be written
 * @param int val ---  Data which needs to be written.
 */
शून्य समुच्चयः_qspi_shakti32(पूर्णाङ्क* addr, पूर्णाङ्क val)
{
	*addr = val;
}

/** @fn void set_qspi_shakti16(int16_t* addr, int16_t val)
 * @brief Writes 16 bit value 
 * @details Writes 16 bit value into 16bit QSPI register 
 * @param 16bit int* addr --- Addresss where the data (val) needs to be written
 * @param 16bit int val ---  Data which needs to be written.
 */
शून्य समुच्चयः_qspi_shakti16(int16_t* addr, int16_t val)
{
	*addr = val;
}

/** @fn void set_qspi_shakti8(char* addr, char val) 
 * @brief Writes 8 bit value.
 * @details Writes 8 bit value into 8 bit qspi register.
 * @param char* addr --- Addresss where the data (val) needs to be written
 * @param char val ---  Data which needs to be written.
 */
शून्य समुच्चयः_qspi_shakti8(वर्ण* addr, वर्ण val)
{
	*addr= val;
}

/** @fn int get_qspi_shakti(int* addr)
 * @brief reads from qspi register
 * @details Reads from the passed QSPI register and returns the value.
 * @param int* addr --- 32 bit Read Addresss  
 * @return Read value -- Read value from the passed value.
 */
पूर्णाङ्क get_qspi_shakti(पूर्णाङ्क* addr)
{
	प्रत्यागम *addr;
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
शून्य qspi_init(पूर्णाङ्क fsize, पूर्णाङ्क csht, पूर्णाङ्क prescaler, पूर्णाङ्क enable_interrupts, पूर्णाङ्क fthreshold, पूर्णाङ्क ck_बहुलकम्){
	पूर्णाङ्क int_सदिशम् = enable_interrupts? (CR_TOIE|CR_SMIE|CR_FTIE|CR_TCIE|CR_TEIE) : 0; 
	समुच्चयः_qspi_shakti32(dcr,(DCR_FSIZE(fsize)|DCR_CSHT(csht)|DCR_CKMODE(ck_बहुलकम्))); 
	समुच्चयः_qspi_shakti32(cr,(CR_PRESCALER(prescaler)|int_सदिशम्|CR_FTHRES(fthreshold)|CR_EN));
}

/** @fn void reset_interrupt_flags()
 * @brief Resets interrupt flags.
 * @details Before carrying out any flash access operations, the interrupt flags are cleared.
 */
शून्य reset_व्यवधानम्_flags(){
	समुच्चयः_qspi_shakti32(fcr,(FCR_CTOF|FCR_CSMF|FCR_CTCF|FCR_CTEF)); //Resetting all the flags
}

/** @fn int wait_for_tcf(int status)
 * @brief Wait for the transfer complete flag.
 * @details WCF bit status register indicates the completion of flash 
 *  operation. The same is cheked here.
 * @param int status register read value.
 * @return Zero on success else -1
 */
पूर्णाङ्क wait_for_tcf(पूर्णाङ्क स्थितिः_2){
	पूर्णाङ्क timeout = DEF_TIMEOUT; 

	स्थितिः_2 = get_qspi_shakti(sr);

	//    printf("status : %d looping?\n",status);

	यावत्(!( स्थितिः_2 & 0x02 ) && --timeout){
		waitfor(1000);
		स्थितिः_2=get_qspi_shakti(sr);
		प्रारूप_लिख("status: %08x in loop %d \n",स्थितिः_2, !(स्थितिः_2 & 0x02));
	}
	यदि(timeout==0){
		प्रारूप_लिख("Request Timed out\n");
		प्रत्यागम -1;
	}
	प्रत्यागम 0;
}

/** @fn int check_fail_bit()
 * @brief Checks the value of fail_bit.
 * @details Checks the fail bit whether the value is zero or not.
 */
पूर्णाङ्क check_fail_bit(शून्य){
	यदि(fail_bit){
		fail_bit = 0;
		प्रत्यागम -1;
	}
	अन्यथा{
		fail_bit = 0;
		प्रत्यागम 0;
	}
}

/** @fn int flashReadStatusRegister()
 * @brief Reads flash status register
 * @details Reads flash status register contents
 * @return Status register value on success; else -1
 */
पूर्णाङ्क flash_Read_स्थितिः_पञ्जिकाकोशः(){
	//    printf("\tReading the Status bits of the Flash\n");
	समुच्चयः_qspi_shakti32(dlr,4);
	समुच्चयः_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x05)|CCR_DMODE(SINGLE)));

	स्थितिः_2 = 0;
	waitfor(1000);
	पूर्णाङ्क ret = wait_for_tcf(स्थितिः_2);
	waitfor(100);
	पूर्णाङ्क मानम् = get_qspi_shakti(dr);
	//	printf("Read status register value %08x \n", value);
	reset_व्यवधानम्_flags();
	यदि(ret){
		प्रारूप_लिख("\tRead Status Register Failed\n");
		fail_bit = 1;
		प्रत्यागम -1;
	}
	अन्यथा
		प्रत्यागम मानम्;
}

/** @fn int wait_for_wip()
 * @brief Wait till a flash access is complete.
 * @details Reads the WIP bit in the status register to check the completion of flash access.
 * Useful during flash write operations.
 * @return Zero on Success
 */
पूर्णाङ्क wait_for_wip(शून्य){
	पूर्णाङ्क status1;
	कुरु{
		//  printf("\t Waiting for Wip \n");
		status1 = flash_Read_स्थितिः_पञ्जिकाकोशः(0x05);
		यदि(check_fail_bit())
			प्रत्यागम -1;
		यदि(status1 & 0x0){
			प्रारूप_लिख("\tQSPI: Programming Error - Diagnose\n");
			प्रत्यागम -1;
		}
		waitfor(20000);
	}यावत्(status1 & 0x01);
	//    printf("\t QSPI: Page Program/Erase Command Successfully Completed\n");
	प्रत्यागम 0;
}

/** @fn int micron_write_enable(int status)
 * @brief Enables the micron flash for write operation.
 * @details Enables micron flash for programming flash data.
 * @param int status --- Write enable status.
 * @return Zero on Success
 */
पूर्णाङ्क micron_write_enable(पूर्णाङ्क स्थितिः_2){
	//  printf("\tWrite Enable\n");
	समुच्चयः_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x06)));
	पूर्णाङ्क ret = wait_for_tcf(स्थितिः_2); //Indicating the completion of command -- Currently polling
	//  printf("Status : %d dcr : %d cr: %d ccr: %d \n",status,*dcr,*cr,*ccr);
	प्रत्यागम ret;
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
पूर्णाङ्क page_क्रमादेशः_Single_SPI(पूर्णाङ्क value1, पूर्णाङ्क value2, पूर्णाङ्क value3, पूर्णाङ्क value4, पूर्णाङ्क स्थानाङ्कः){
	यदि(micron_write_enable(स्थितिः_2)){
		प्रारूप_लिख("Panic: Write Enable Command Failed to execute");
		प्रत्यागम -1;
	}
	reset_व्यवधानम्_flags(); 

	समुच्चयः_qspi_shakti32(dlr,DL(16));
	// set_qspi_shakti32(ccr,(CCR_DDRM | CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x12))); 
	समुच्चयः_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x12)));
	समुच्चयः_qspi_shakti32(ar, स्थानाङ्कः);        
	प्रारूप_लिख(" Address written %d \n",स्थानाङ्कः); 
	समुच्चयः_qspi_shakti32(dr,value1);
	प्रारूप_लिख(" Value 1 written %d \n",value1);
	समुच्चयः_qspi_shakti32(dr,value2);
	प्रारूप_लिख(" Value 2 written %d \n",value2);
	समुच्चयः_qspi_shakti32(dr,value3);
	प्रारूप_लिख(" Value 3 written %d \n",value3);
	समुच्चयः_qspi_shakti32(dr,value4);
	प्रारूप_लिख(" Value 4 written %d \n",value4);
	waitfor(150); 
	wait_for_tcf(स्थितिः_2);
	reset_व्यवधानम्_flags();
	प्रत्यागम wait_for_wip(); // Function which checks if WIP is done, indicating completion of Page Program
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
पूर्णाङ्क page_क्रमादेशः_Quad_SPI(पूर्णाङ्क value1, पूर्णाङ्क value2, पूर्णाङ्क value3, पूर्णाङ्क value4, पूर्णाङ्क स्थानाङ्कः){
	यदि(micron_write_enable(स्थितिः_2)){
		प्रारूप_लिख("Panic: Write Enable Command Failed to execute");
		प्रत्यागम -1;
	}
	reset_व्यवधानम्_flags(); 

	समुच्चयः_qspi_shakti32(dlr,DL(16));
	// set_qspi_shakti32(ccr,(CCR_DDRM | CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x12))); 
	समुच्चयः_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(QUAD)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x34))); 
	समुच्चयः_qspi_shakti32(ar, स्थानाङ्कः);
	समुच्चयः_qspi_shakti32(dr,value1);
	समुच्चयः_qspi_shakti32(dr,value2);
	समुच्चयः_qspi_shakti32(dr,value3);
	समुच्चयः_qspi_shakti32(dr,value4);
	waitfor(150); 
	wait_for_tcf(स्थितिः_2);
	reset_व्यवधानम्_flags();
	प्रत्यागम wait_for_wip(); // Function which checks if WIP is done, indicating completion of Page Program
}

/** @fn int flashIdentificationDevice()
 * @brief Reads flash id code.
 * @details Reads flash identification code from the flash device and checks whether it valid.
 * @return Zero on success else -1
 */
पूर्णाङ्क flashIdentificationDevice(शून्य){
	log_debug("\tReading the ID register and discovering the Flash Device\n");
	समुच्चयः_qspi_shakti32(dlr,4);
	समुच्चयः_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x90)|CCR_ADSIZE(THREEBYTE)|CCR_ADMODE(SINGLE)|CCR_DMODE(SINGLE)));
	समुच्चयः_qspi_shakti32(ar, 0);
	स्थितिः_2 = 0; // Useless Variable but still!!!!
	पूर्णाङ्क ret = wait_for_tcf(स्थितिः_2);
	पूर्णाङ्क मानम् = get_qspi_shakti(dr);
	log_info("\t device id %x\n",मानम्);
	reset_व्यवधानम्_flags();
	यदि(मानम् == MEM_TYPE_N25Q256_ID){
		प्रारूप_लिख("\tN25Q256 Device Detected \n");
		प्रत्यागम 0;
	}
	अन्यथा{
		log_fatal("\t Device Not Detected - Diagnose %08x\n",मानम्);
		प्रत्यागम -1;
	}
}

/** @fn int flashMemInit()
 * @brief Initialises flash memory 
 * @details Initialises flash device and check for id code.
 * @return Zero on success else -1
 */
पूर्णाङ्क flashMemInit(){  //Supposedly a set of routines to check if the memory/interface or whatever is proper
	पूर्णाङ्क ret = flashIdentificationDevice();
	यदि(ret==-1){
		log_fatal("Flash Mem Init Failed -- Quitting Program, Diagnose");
		प्रत्यागम ret;
	}
	अन्यथा log_debug("Flash Mem Init Success\n");
	प्रत्यागम 0;
	//to fill in code
}


/** @fn int flashReadFlagRegister()
 * @brief Reads flash read flag. 
 * @details Reads the flash flag register.
 * @warning Not implemented now. Reserve for future.
 */
पूर्णाङ्क flash_Read_Flag_पञ्जिकाकोशः(शून्य){
	प्रत्यागम 0;
}

/** @fn int flashWriteEnable()
 * @brief Enables flash enable bit
 * @details For any write operation into to flash device (erase, program, etc.)
 *        this enable bit needs to be enabled.
 * @return TCF status
 */
पूर्णाङ्क flashWriteEnable(शून्य){
	प्रारूप_लिख("\tWrite Enable\n");
	समुच्चयः_qspi_shakti32(ccr,(CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x06)));
	पूर्णाङ्क ret = wait_for_tcf(0); //Indicating the completion of command -- Currently polling
	reset_व्यवधानम्_flags();
	प्रत्यागम ret; 
}

/** @fn int flashEnable4ByteAddressingMode()
 * @brief Selects the addressed mode.
 * @details Before accessing flash device, the number of bits used for (Q)SPI needs to be programmed.
 * @return Status of the performed operation; else -1
 */
पूर्णाङ्क flash_Enable4_Byte_Addressing_बहुलकम्(शून्य){  //Enable 4-byte addressing Mode and read the status to verify that it has happened correctly

	यदि(flashWriteEnable()){
		प्रारूप_लिख("\t Write Enable Failed \n");
		प्रत्यागम -1;
	}
	waitfor(100);
	समुच्चयः_qspi_shakti32(ccr,(CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xB7)));
	//  int status =0; 
	स्थितिः_2 = 0;
	पूर्णाङ्क ret = wait_for_tcf(स्थितिः_2);
	reset_व्यवधानम्_flags();
	waitfor(100);
	//Checking Phase
	स्थितिः_2 = flash_Read_स्थितिः_पञ्जिकाकोशः();
	प्रारूप_लिख("\t Status Value: %08x\n",स्थितिः_2);
	यदि(स्थितिः_2 & 1)
		प्रारूप_लिख("\t 4-Byte Addressing Mode is Enabled\n");
	अन्यथा
		प्रारूप_लिख("\t 4-byte Addressing mode not Enabled\n");
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
पूर्णाङ्क flashReadSingleSPI(पूर्णाङ्क dummy_आवृत्तयः, पूर्णाङ्क read_स्थानाङ्कः, पूर्णाङ्क instruction, पूर्णाङ्क दत्त_शब्दाः, पूर्णाङ्क adsize){
	समुच्चयः_qspi_shakti32(dlr,दत्त_शब्दाः);
	समुच्चयः_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(SINGLE)|CCR_DCYC(dummy_आवृत्तयः)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_ADSIZE(adsize)|CCR_INSTRUCTION(instruction)));
	समुच्चयः_qspi_shakti32(ar,read_स्थानाङ्कः);
	स्थितिः_2 = 0;
	पूर्णाङ्क ret = wait_for_tcf(स्थितिः_2);
	पूर्णाङ्क मानम् = get_qspi_shakti(dr);
	प्रारूप_लिख("\tThe Read Value: %08x\n",मानम्);
	//    printf("\tThe Read Value: %08x\n",value);
	यदि(ret){
		प्रारूप_लिख("\t Read Value Failed \n");
		प्रत्यागम -1;
	}
	reset_व्यवधानम्_flags();
	प्रत्यागम मानम्;
}

/** @fn int flashReadDualSPI(int address, int data_length)
 * @brief  Reads flash device over two io lines SPI.
 * @details Reads the flash device over two io lines for spi (IO1, IO2, CS, CLK) data
 * @param int address --- Address which needs to be read.
 * @param int data_length --- Number of Data bytes (data_words + 1) needs to be read 
 * @return Status of the performed operation; else -1
 */
पूर्णाङ्क flashReadDualSPI(पूर्णाङ्क स्थानाङ्कः, पूर्णाङ्क दत्त_दीर्घता){
	समुच्चयः_qspi_shakti32(dlr,दत्त_दीर्घता); //DLR
	समुच्चयः_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(DOUBLE)|CCR_DCYC(3)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBB)));
	समुच्चयः_qspi_shakti32(ar,स्थानाङ्कः); 
	//    printf("Status : %08x dcr : %08x cr : %08x ccr : %08x dlr: %08x ar: %08x\n",status,*dcr,*cr,*ccr,*dlr,*ar);
	पूर्णाङ्क ret = wait_for_tcf(स्थितिः_2);
	पूर्णाङ्क मानम् = get_qspi_shakti(dr);
	प्रारूप_लिख("\tThe Read Value: %08x\n",मानम्);	
	यदि(ret){
		प्रारूप_लिख("\t QSPI: Read Value failed\n");
		प्रत्यागम -1;
	}
	//*config_string = get_qspi_shakti(dr);
	//printf("\t Read Data is %08x\n",read_data);
	reset_व्यवधानम्_flags();
	प्रत्यागम मानम्;
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
पूर्णाङ्क flashReadQuadSPI(पूर्णाङ्क dummy_आवृत्तयः, पूर्णाङ्क read_स्थानाङ्कः, पूर्णाङ्क instruction, पूर्णाङ्क दत्त_शब्दाः, पूर्णाङ्क adsize){
	समुच्चयः_qspi_shakti32(dlr,दत्त_शब्दाः);
	समुच्चयः_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DCYC(dummy_आवृत्तयः)|CCR_ADSIZE(adsize)|CCR_ADMODE(QUAD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(instruction)));
	समुच्चयः_qspi_shakti32(ar,read_स्थानाङ्कः);
	स्थितिः_2 = 0;
	पूर्णाङ्क ret = wait_for_tcf(स्थितिः_2);
	पूर्णाङ्क मानम्_1 = get_qspi_shakti(dr);
	पूर्णाङ्क मानम्_2_2 = get_qspi_shakti(dr);
	पूर्णाङ्क मानम्_3 = get_qspi_shakti(dr);
	पूर्णाङ्क मानम्_4 = get_qspi_shakti(dr);
	प्रारूप_लिख("\tThe Read Value: %08x, %08x, %08x and %08x \n",मानम्_1,मानम्_2_2,मानम्_3,मानम्_4);
	यदि(ret){
		प्रारूप_लिख("\t Read Value Failed \n");
		प्रत्यागम -1; 
	}   
	reset_व्यवधानम्_flags();
	प्रत्यागम मानम्_1;
}

/** @fn int flashSingleSPIXip(int addr, int* dest_addr) 
 * @brief Reads over single SPI XIP
 * @details Generic Read for xip SPI Read.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on success.
 */
पूर्णाङ्क flashSingleSPIXip(पूर्णाङ्क addr, पूर्णाङ्क* dest_addr){
	समुच्चयः_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(SINGLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(7)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x0C)));
	समुच्चयः_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_बहुलकम्_BYTE(0x00)|DCR_CKMODE(1)));
	समुच्चयः_qspi_shakti32(dlr,0x4);
	समुच्चयः_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	स्थितिः_2=0;
	wait_for_tcf(स्थितिः_2);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	प्रारूप_लिख("\n Fisrt value obtained through single read : %d \n ",*dest_addr);
	reset_व्यवधानम्_flags(); 
	प्रारूप_लिख("\t Trying XIP now\n");
	समुच्चयः_qspi_shakti32(ccr, (CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(SINGLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(7)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x0C)));
	समुच्चयः_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_बहुलकम्_BYTE(0x00)|DCR_CKMODE(1))); 
	waitfor(25);
	प्रत्यागम 0;
}

/** @fn int flashSingleSPIDDRXip(int addr, int* dest_addr)  
 * @brief Reads over DDR XIP mode.
 * @details Reads for DDR based XIP mode.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
पूर्णाङ्क flashSingleSPIDDRXip(पूर्णाङ्क addr, पूर्णाङ्क* dest_addr){
	समुच्चयः_qspi_shakti32(ccr,(CCR_DDRM|CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(SINGLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(15)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x0E)));
	समुच्चयः_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_बहुलकम्_BYTE(0x00)|DCR_CKMODE(1)));
	समुच्चयः_qspi_shakti32(dlr,0x4);
	समुच्चयः_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	स्थितिः_2=0;
	wait_for_tcf(स्थितिः_2);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	reset_व्यवधानम्_flags(); 
	प्रारूप_लिख("\t Trying XIP now\n");
	समुच्चयः_qspi_shakti32(ccr, (CCR_DDRM|CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(SINGLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(14)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x0E)));
	समुच्चयः_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_बहुलकम्_BYTE(0x00)|DCR_CKMODE(1))); 
	waitfor(25);
	प्रत्यागम 0;
}

/** @fn int flashDualSPIXip(int addr, int* dest_addr)
 * @brief Reads over XIP mode.
 * @details Reads for XIP mode using two io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
पूर्णाङ्क flashDualSPIXip(पूर्णाङ्क addr, पूर्णाङ्क* dest_addr){
	समुच्चयः_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(DOUBLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(3)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBB)));
	समुच्चयः_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_बहुलकम्_BYTE(0xA0)|DCR_CKMODE(1)));
	समुच्चयः_qspi_shakti32(dlr,0x4);
	समुच्चयः_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	स्थितिः_2=0;
	wait_for_tcf(स्थितिः_2);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	प्रारूप_लिख("\n Fisrt value obtained through single read : %d \n ",*dest_addr);
	reset_व्यवधानम्_flags(); 
	प्रारूप_लिख("\t Trying XIP now\n");
	समुच्चयः_qspi_shakti32(ccr, (CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(DOUBLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(3)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(NDATA)));
	समुच्चयः_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_बहुलकम्_BYTE(0xA0)|DCR_CKMODE(1))); 
	waitfor(25);
	प्रत्यागम 0;
}

/** @fn int flashDualSPIDDRXip(int addr, int* dest_addr) 
 * @brief Reads over XIP mode.
 * @details Reads for DDR based XIP mode using two io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
पूर्णाङ्क flashDualSPIDDRXip(पूर्णाङ्क addr, पूर्णाङ्क* dest_addr){
	समुच्चयः_qspi_shakti32(ccr,(CCR_DDRM|CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(DOUBLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(6)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBE)));
	समुच्चयः_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_बहुलकम्_BYTE(0xA0)|DCR_CKMODE(1)));
	समुच्चयः_qspi_shakti32(dlr,0x4);
	समुच्चयः_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	स्थितिः_2=0;
	wait_for_tcf(स्थितिः_2);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	reset_व्यवधानम्_flags(); 
	प्रारूप_लिख("\t Trying XIP now\n");
	समुच्चयः_qspi_shakti32(ccr, (CCR_DDRM|CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(DOUBLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(6)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(NDATA)));
	समुच्चयः_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_बहुलकम्_BYTE(0xA0)|DCR_CKMODE(1))); 
	waitfor(25);
	प्रत्यागम 0;
}

/** @fn int flashWriteVolatileConfigReg(int value) 
 * @brief Writes into flash volatile configuration register.
 * @details Writes the passed value into flash volatile configuration register.
 * @param int value needs to written into Write Volatile Config Register.
 * @return Zero on Success
 */
पूर्णाङ्क flashWriteVolatileConfigReg(पूर्णाङ्क मानम्){
	प्रारूप_लिख("\t Setting Volatile Configuration Register with the Value: %08x\n",मानम्);
	यदि(micron_write_enable(स्थितिः_2)){
		प्रारूप_लिख("Panic: Write Enable Command Failed to execute\n");
		प्रत्यागम -1;
	}
	reset_व्यवधानम्_flags();
	//	flashReadStatusRegister();
	समुच्चयः_qspi_shakti32(dlr,DL(1));
	समुच्चयः_qspi_shakti8(dr,मानम्);  //The value to be written into the VECR register to enable XIP. Indicating XIP to operate in Quad Mode
	समुच्चयः_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x01)));
	waitfor(50);
	स्थितिः_2=0;
	पूर्णाङ्क ret = wait_for_tcf(स्थितिः_2);
	//    printf("Status : %d dcr : %d cr : %d ccr : %d dlr: %d dr: %d\n",status,*dcr,*cr,*ccr,*dlr,*dr);
	reset_व्यवधानम्_flags();
	waitfor(50);  //Giving Micron time to store the data
	प्रत्यागम ret;
}

/** @fn int flashQuadSPIXip(int addr, int* dest_addr)
 * @brief Reads over XIP mode.
 * @details Reads for DDR based XIP mode using quad io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
पूर्णाङ्क flashQuadSPIXip(पूर्णाङ्क addr, पूर्णाङ्क* dest_addr){
	यदि(flashWriteVolatileConfigReg(0x40404040)){
		प्रारूप_लिख("\t Volatile Configuration Register not Set -- Diagnose\n");
		प्रत्यागम -1;
	}
	स्थितिः_2 = wait_for_wip();
	प्रारूप_लिख("\t qspi status register %08x\n",स्थितिः_2);
	reset_व्यवधानम्_flags();
	समुच्चयः_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(5)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xEC)));
	समुच्चयः_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_बहुलकम्_BYTE(0xA0)|DCR_CKMODE(1)));
	समुच्चयः_qspi_shakti32(dlr,0x4);
	समुच्चयः_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	स्थितिः_2=0;
	wait_for_tcf(स्थितिः_2);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	reset_व्यवधानम्_flags(); 
	प्रारूप_लिख("\t Trying XIP now\n");
	समुच्चयः_qspi_shakti32(ccr, (CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(QUAD)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(5)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(NDATA)));
	समुच्चयः_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_बहुलकम्_BYTE(0xA0)|DCR_CKMODE(1))); 
	waitfor(25);
	प्रत्यागम 0;
}

/** @fn int flashQuadSPIDDRXip(int addr, int* dest_addr)
 * @brief Reads over XIP mode.
 * @details Reads for DDR based XIP mode using four io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
पूर्णाङ्क flashQuadSPIDDRXip(पूर्णाङ्क addr, पूर्णाङ्क* dest_addr){
	यदि(flashWriteVolatileConfigReg(0x40404040)){
		प्रारूप_लिख("\t Volatile Configuration Register not Set -- Diagnose\n");
		प्रत्यागम -1;
	}
	स्थितिः_2 = wait_for_wip();
	प्रारूप_लिख("\t qspi status register %08x\n",स्थितिः_2);
	reset_व्यवधानम्_flags();
	समुच्चयः_qspi_shakti32(ccr,(CCR_DDRM|CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(10)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xEE)));
	समुच्चयः_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_बहुलकम्_BYTE(0xA0)|DCR_CKMODE(1)));
	समुच्चयः_qspi_shakti32(dlr,0x4);
	समुच्चयः_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	स्थितिः_2=0;
	wait_for_tcf(स्थितिः_2);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	reset_व्यवधानम्_flags(); 
	प्रारूप_लिख("\t Trying XIP now\n");
	समुच्चयः_qspi_shakti32(ccr, (CCR_DDRM|CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(QUAD)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(10)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(NDATA)));
	समुच्चयः_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_बहुलकम्_BYTE(0xA0)|DCR_CKMODE(1))); 
	waitfor(25);
	प्रत्यागम 0;
}

/** @fn int flash_Write_disable()
 * @brief disables write operation
 * @details Write operation can be possible only after enabling write enable register.
 *       Here this is disabled using this function.
 * @return Zero on Success
 */
पूर्णाङ्क flash_Write_disable(शून्य){
	प्रारूप_लिख("\tWrite disable\n");
	समुच्चयः_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x04)));
	पूर्णाङ्क ret = wait_for_tcf(स्थितिः_2); //Indicating the completion of command -- Currently polling
	प्रारूप_लिख("Status : %d dcr : %d cr: %d ccr: %d \n",स्थितिः_2,*dcr,*cr,*ccr);
	reset_व्यवधानम्_flags();
	प्रत्यागम wait_for_wip();
}

/** @fn int eraseSector(int command, int address)
 * @brief Erases one sector 
 * @details Erases a complete sector which falls in the sector range.
 * @param int command --- Erase command (sector erase, block erase or chip erase)
 * @param int address --- Starting address of erase.
 * @return Zero on Success
 */
पूर्णाङ्क eraseSector(पूर्णाङ्क command, पूर्णाङ्क स्थानाङ्कः){
	यदि(micron_write_enable(स्थितिः_2)){
		प्रारूप_लिख("Panic: Write Enable Command Failed to execute");
		प्रत्यागम -1;
	}
	reset_व्यवधानम्_flags();
	समुच्चयः_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(command)));
	समुच्चयः_qspi_shakti32(ar,स्थानाङ्कः);
	waitfor(150);
	पूर्णाङ्क ret = wait_for_tcf(स्थितिः_2);
	reset_व्यवधानम्_flags();
	प्रत्यागम wait_for_wip(); //For sector erase maybe estat should be checked
}

/** @fn int micron_volatile_write_enable(int status) 
 * @brief Enable for volatile write.
 * @details Enables micron flash for programming volatile config. register.
 * @param int --- status register value.
 * @return Zero on Success
 */
पूर्णाङ्क micron_volatile_write_enable(पूर्णाङ्क स्थितिः_2){
	प्रारूप_लिख("\tVolatile Write Enable\n");
	समुच्चयः_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x50)));
	पूर्णाङ्क ret = wait_for_tcf(स्थितिः_2); //Indicating the completion of command -- Currently polling
	प्रारूप_लिख("Status : %d dcr : %d cr: %d ccr: %d \n",स्थितिः_2,*dcr,*cr,*ccr);
	प्रत्यागम ret;
}

/** @fn int micron_enable_4byte_addressing(int status) 
 * @brief Enables micron flash for 4 byte addressing.
 * @details Address can be passed as 3 bytes or 4 bytes before read or write 
 * operation. This function sets the number of address bytes to 4 bytes.
 * @param int --- status register value
 * @return Zero on Success
 */
पूर्णाङ्क micron_enable_4byte_addressing(पूर्णाङ्क स्थितिः_2){
	प्रारूप_लिख("\t Enable 4 byte address \n");
	समुच्चयः_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xB7)));
	पूर्णाङ्क ret = wait_for_tcf(स्थितिः_2); //Indicating the completion of command -- Currently polling
	प्रारूप_लिख("Status : %d dcr : %d cr: %d ccr: %d \n",स्थितिः_2,*dcr,*cr,*ccr);
	प्रत्यागम ret;
}

/** @fn int micron_configure_xip_volatile(int status, int value)
 * @brief Configures the xip volatile config. register.
 * @details Configures the volatile config. register for xip Read mode.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
पूर्णाङ्क micron_configure_xip_volatile(पूर्णाङ्क स्थितिः_2, पूर्णाङ्क मानम्){
	log_debug("\tWrite Volatile Configuration Register\n");
	समुच्चयः_qspi_shakti32(dlr,DL(1));
	समुच्चयः_qspi_shakti8(dr,मानम्);  //The value to be written into the VECR register to enable XIP. Indicating XIP to operate in Quad Mode
	समुच्चयः_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x81)));
	waitfor(50);
	पूर्णाङ्क ret = wait_for_tcf(स्थितिः_2);
	प्रारूप_लिख("Status : %d dcr : %d cr : %d ccr : %d dlr: %d dr: %d\n",स्थितिः_2,*dcr,*cr,*ccr,*dlr,*dr);
	waitfor(50);  //Giving Micron time to store the data
	प्रत्यागम ret;
}

/** @fn int micron_disable_xip_volatile(int status, int value)
 * @brief Configures(disables) the xip volatile config. register.
 * @details Configures(disables) the volatile config. register for xip Read mode.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
पूर्णाङ्क micron_disable_xip_volatile(पूर्णाङ्क स्थितिः_2, __attribute__ ((अप्रयुक्तम्)) पूर्णाङ्क मानम्){
	log_debug("\tWrite Volatile Configuration Register to exit XIP\n");
	समुच्चयः_qspi_shakti32(cr,(CR_PRESCALER(0x3)|CR_TOIE|CR_TCIE|CR_TEIE|CR_SMIE|CR_FTIE|CR_ABORT|CR_EN));
	waitfor(30);
	qspi_init(27,0,3,1,15,1);
	समुच्चयः_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DUMMY_BIT|CCR_DUMMY_CONFIRMATION|CCR_DCYC(8)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(NDATA)));
	समुच्चयः_qspi_shakti32(ar,0x00000); //Dummy address 
	समुच्चयः_qspi_shakti32(dlr,1);

	पूर्णाङ्क ret = wait_for_tcf(स्थितिः_2);
	पूर्णाङ्क अस्थायी_दत्त = get_qspi_shakti(dr);

	waitfor(50);
	reset_व्यवधानम्_flags();
	प्रत्यागम ret;
}

/** @fn int micron_read_id_cmd(int status, int value)
 * @brief Reads the id of the micron flash.
 * @details Micron flash is having a fixed value as ID during production. This 
 * value is read to confirm proper flash device.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
पूर्णाङ्क micron_read_id_cmd(पूर्णाङ्क स्थितिः_2, पूर्णाङ्क मानम्){
	log_debug("\tRead ID Command to see if the Protocol is Proper\n");
	समुच्चयः_qspi_shakti32(dlr,4);
	समुच्चयः_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x9E)|CCR_DMODE(SINGLE)));
	पूर्णाङ्क ret = wait_for_tcf(स्थितिः_2);
	मानम् = get_qspi_shakti(dr);
	प्रारूप_लिख("Read ID: %08x",मानम्);
	प्रत्यागम ret;
}

/** @fn int micron_read_configuration_register(int status, int value)
 * @brief Reads configuration register. 
 * @details The configurartion register is read using this function.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
पूर्णाङ्क micron_read_configuration_पञ्जिकाकोशः(पूर्णाङ्क स्थितिः_2, पूर्णाङ्क मानम्){
	प्रारूप_लिख("\tRead ID Command to see if the Protocol is Proper\n");
	समुच्चयः_qspi_shakti32(dlr,4);
	समुच्चयः_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBE)|CCR_DMODE(SINGLE)));
	पूर्णाङ्क ret = wait_for_tcf(स्थितिः_2);
	मानम् = get_qspi_shakti(dr);
	log_debug("Configuration Register Value: %08x",मानम्);
	प्रत्यागम ret;
}
