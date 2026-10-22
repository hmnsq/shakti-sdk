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
#define MEM_TYPE_N25Q256_ID 0x9d189d18

अक्षर fail_bit = 0;
पूर्णांक status = 0;
/*! Pointer to QSPI registers */
पूर्णांक* cr       =  (पूर्णांक*) CR; /*! Control Register */
पूर्णांक* dcr      =  (पूर्णांक*) DCR; /*! Data Configuration Register */
पूर्णांक* sr       =  (पूर्णांक*) SR; /*! Status Register */
पूर्णांक* fcr      =  (पूर्णांक*) FCR; /* Flag Clear Register */
पूर्णांक* ccr      =  (पूर्णांक*) CCR; /* Commn. Configuration Register */
पूर्णांक* ar       =  (पूर्णांक*) AR; /*! Address Register */
पूर्णांक* abr      =  (पूर्णांक*) ABR; /*! Alternate Bytes Register */
पूर्णांक* dr       =  (पूर्णांक*) DR; /*! Data Register */
पूर्णांक* dlr      =  (पूर्णांक*) DLR; /*! Data Length Register */
पूर्णांक* psmkr    =  (पूर्णांक*) PSMKR; /*! Polling Status Mask Register */
पूर्णांक* pir      =  (पूर्णांक*) PIR; /*! Polling Interval Register */
पूर्णांक* lprt     =  (पूर्णांक*) LPRT; /*! Low power Time Register */
पूर्णांक* startmm  =  (पूर्णांक*) STARTMM; /*! Start Memory Map Register */
पूर्णांक* endmm    =  (पूर्णांक*) ENDMM; /*! End Memory Map Register */

/** @fn void set_qspi_shakti32(int* addr, int val)
 * @brief Writes 32 bit value into QSPI register.
 * @details Writes 32 bit value into passed address QSPI register.
 * @param int* addr --- Addresss where the data (val) needs to be written
 * @param int val ---  Data which needs to be written.
 */
शून्य set_qspi_shakti32(पूर्णांक* addr, पूर्णांक val)
{
	*addr = val;
}

/** @fn void set_qspi_shakti16(int16_t* addr, int16_t val)
 * @brief Writes 16 bit value 
 * @details Writes 16 bit value into 16bit QSPI register 
 * @param 16bit int* addr --- Addresss where the data (val) needs to be written
 * @param 16bit int val ---  Data which needs to be written.
 */
शून्य set_qspi_shakti16(int16_t* addr, int16_t val)
{
	*addr = val;
}

/** @fn void set_qspi_shakti8(char* addr, char val) 
 * @brief Writes 8 bit value.
 * @details Writes 8 bit value into 8 bit qspi register.
 * @param char* addr --- Addresss where the data (val) needs to be written
 * @param char val ---  Data which needs to be written.
 */
शून्य set_qspi_shakti8(अक्षर* addr, अक्षर val)
{
	*addr= val;
}

/** @fn int get_qspi_shakti(int* addr)
 * @brief reads from qspi register
 * @details Reads from the passed QSPI register and returns the value.
 * @param int* addr --- 32 bit Read Addresss  
 * @return Read value -- Read value from the passed value.
 */
पूर्णांक get_qspi_shakti(पूर्णांक* addr)
{
	परत *addr;
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
शून्य qspi_init(पूर्णांक fsize, पूर्णांक csht, पूर्णांक prescaler, पूर्णांक enable_interrupts, पूर्णांक fthreshold, पूर्णांक ck_mode){
	पूर्णांक int_vector = enable_interrupts? (CR_TOIE|CR_SMIE|CR_FTIE|CR_TCIE|CR_TEIE) : 0; 
	set_qspi_shakti32(dcr,(DCR_FSIZE(fsize)|DCR_CSHT(csht)|DCR_CKMODE(ck_mode))); 
	set_qspi_shakti32(cr,(CR_PRESCALER(prescaler)|int_vector|CR_FTHRES(fthreshold)|CR_EN));
}

/** @fn void reset_interrupt_flags()
 * @brief Resets interrupt flags.
 * @details Before carrying out any flash access operations, the interrupt flags are cleared.
 */
शून्य reset_interrupt_flags(){
	set_qspi_shakti32(fcr,(FCR_CTOF|FCR_CSMF|FCR_CTCF|FCR_CTEF)); //Resetting all the flags
}

/** @fn int wait_for_tcf(int status)
 * @brief Wait for the transfer complete flag.
 * @details WCF bit status register indicates the completion of flash 
 *  operation. The same is cheked here.
 * @param int status register read value.
 * @return Zero on success else -1
 */
पूर्णांक wait_for_tcf(पूर्णांक status){
	पूर्णांक timeout = DEF_TIMEOUT; 

	status = get_qspi_shakti(sr);

	//    printf("status : %d looping?\n",status);

	पर्यंत(!( status & 0x02 ) && --timeout){
		waitfor(1000);
		status=get_qspi_shakti(sr);
		म_लिखो("status: %08x in loop %d \n",status, !(status & 0x02));
	}
	जर(timeout==0){
		म_लिखो("Request Timed out\n");
		परत -1;
	}
	परत 0;
}

/** @fn int check_fail_bit()
 * @brief Checks the value of fail_bit.
 * @details Checks the fail bit whether the value is zero or not.
 */
पूर्णांक check_fail_bit(शून्य){
	जर(fail_bit){
		fail_bit = 0;
		परत -1;
	}
	अन्यथा{
		fail_bit = 0;
		परत 0;
	}
}

/** @fn int flashReadStatusRegister()
 * @brief Reads flash status register
 * @details Reads flash status register contents
 * @return Status register value on success; else -1
 */
पूर्णांक flashReadStatusRegister(){
	//    printf("\tReading the Status bits of the Flash\n");
	set_qspi_shakti32(dlr,4);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x05)|CCR_DMODE(SINGLE)));

	status = 0;
	waitfor(1000);
	पूर्णांक ret = wait_for_tcf(status);
	waitfor(100);
	पूर्णांक मूल्य = get_qspi_shakti(dr);
	//	printf("Read status register value %08x \n", value);
	reset_interrupt_flags();
	जर(ret){
		म_लिखो("\tRead Status Register Failed\n");
		fail_bit = 1;
		परत -1;
	}
	अन्यथा
		परत मूल्य;
}

/** @fn int wait_for_wip()
 * @brief Wait till a flash access is complete.
 * @details Reads the WIP bit in the status register to check the completion of flash access.
 * Useful during flash write operations.
 * @return Zero on Success
 */
पूर्णांक wait_for_wip(शून्य){
	पूर्णांक status1;
	करा{
		//  printf("\t Waiting for Wip \n");
		status1 = flashReadStatusRegister(0x05);
		जर(check_fail_bit())
			परत -1;
		जर(status1 & 0x0){
			म_लिखो("\tQSPI: Programming Error - Diagnose\n");
			परत -1;
		}
		waitfor(20000);
	}पर्यंत(status1 & 0x01);
	//    printf("\t QSPI: Page Program/Erase Command Successfully Completed\n");
	परत 0;
}

/** @fn int micron_write_enable(int status)
 * @brief Enables the micron flash for write operation.
 * @details Enables micron flash for programming flash data.
 * @param int status --- Write enable status.
 * @return Zero on Success
 */
पूर्णांक micron_write_enable(पूर्णांक status){
	//  printf("\tWrite Enable\n");
	set_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x06)));
	पूर्णांक ret = wait_for_tcf(status); //Indicating the completion of command -- Currently polling
	//  printf("Status : %d dcr : %d cr: %d ccr: %d \n",status,*dcr,*cr,*ccr);
	परत ret;
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
पूर्णांक pageProgramSingleSPI(पूर्णांक value1, पूर्णांक value2, पूर्णांक value3, पूर्णांक value4, पूर्णांक address){
	जर(micron_write_enable(status)){
		म_लिखो("Panic: Write Enable Command Failed to execute");
		परत -1;
	}
	reset_interrupt_flags(); 

	set_qspi_shakti32(dlr,DL(16));
	// set_qspi_shakti32(ccr,(CCR_DDRM | CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x12))); 
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x12)));
	set_qspi_shakti32(ar, address);        
	म_लिखो(" Address written %d \n",address); 
	set_qspi_shakti32(dr,value1);
	म_लिखो(" Value 1 written %d \n",value1);
	set_qspi_shakti32(dr,value2);
	म_लिखो(" Value 2 written %d \n",value2);
	set_qspi_shakti32(dr,value3);
	म_लिखो(" Value 3 written %d \n",value3);
	set_qspi_shakti32(dr,value4);
	म_लिखो(" Value 4 written %d \n",value4);
	waitfor(150); 
	wait_for_tcf(status);
	reset_interrupt_flags();
	परत wait_for_wip(); // Function which checks if WIP is done, indicating completion of Page Program
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
पूर्णांक pageProgramQuadSPI(पूर्णांक value1, पूर्णांक value2, पूर्णांक value3, पूर्णांक value4, पूर्णांक address){
	जर(micron_write_enable(status)){
		म_लिखो("Panic: Write Enable Command Failed to execute");
		परत -1;
	}
	reset_interrupt_flags(); 

	set_qspi_shakti32(dlr,DL(16));
	// set_qspi_shakti32(ccr,(CCR_DDRM | CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x12))); 
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(QUAD)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x34))); 
	set_qspi_shakti32(ar, address);
	set_qspi_shakti32(dr,value1);
	set_qspi_shakti32(dr,value2);
	set_qspi_shakti32(dr,value3);
	set_qspi_shakti32(dr,value4);
	waitfor(150); 
	wait_for_tcf(status);
	reset_interrupt_flags();
	परत wait_for_wip(); // Function which checks if WIP is done, indicating completion of Page Program
}

/** @fn int flashIdentificationDevice()
 * @brief Reads flash id code.
 * @details Reads flash identification code from the flash device and checks whether it valid.
 * @return Zero on success else -1
 */
पूर्णांक flashIdentificationDevice(शून्य){
	log_debug("\tReading the ID register and discovering the Flash Device\n");
	set_qspi_shakti32(dlr,4);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x90)|CCR_ADSIZE(THREEBYTE)|CCR_ADMODE(SINGLE)|CCR_DMODE(SINGLE)));
	set_qspi_shakti32(ar, 0);
	status = 0; // Useless Variable but still!!!!
	पूर्णांक ret = wait_for_tcf(status);
	पूर्णांक मूल्य = get_qspi_shakti(dr);
	log_info("\t device id %x\n",मूल्य);
	reset_interrupt_flags();
	जर(मूल्य == MEM_TYPE_N25Q256_ID){
		म_लिखो("\tN25Q256 Device Detected \n");
		परत 0;
	}
	अन्यथा{
		log_fatal("\t Device Not Detected - Diagnose %08x\n",मूल्य);
		परत -1;
	}
}

/** @fn int flashMemInit()
 * @brief Initialises flash memory 
 * @details Initialises flash device and check for id code.
 * @return Zero on success else -1
 */
पूर्णांक flashMemInit(){  //Supposedly a set of routines to check if the memory/interface or whatever is proper
	पूर्णांक ret = flashIdentificationDevice();
	जर(ret==-1){
		log_fatal("Flash Mem Init Failed -- Quitting Program, Diagnose");
		परत ret;
	}
	अन्यथा log_debug("Flash Mem Init Success\n");
	परत 0;
	//to fill in code
}


/** @fn int flashReadFlagRegister()
 * @brief Reads flash read flag. 
 * @details Reads the flash flag register.
 * @warning Not implemented now. Reserve for future.
 */
पूर्णांक flashReadFlagRegister(शून्य){
	परत 0;
}

/** @fn int flashWriteEnable()
 * @brief Enables flash enable bit
 * @details For any write operation into to flash device (erase, program, etc.)
 *        this enable bit needs to be enabled.
 * @return TCF status
 */
पूर्णांक flashWriteEnable(शून्य){
	म_लिखो("\tWrite Enable\n");
	set_qspi_shakti32(ccr,(CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x06)));
	पूर्णांक ret = wait_for_tcf(0); //Indicating the completion of command -- Currently polling
	reset_interrupt_flags();
	परत ret; 
}

/** @fn int flashEnable4ByteAddressingMode()
 * @brief Selects the addressed mode.
 * @details Before accessing flash device, the number of bits used for (Q)SPI needs to be programmed.
 * @return Status of the performed operation; else -1
 */
पूर्णांक flashEnable4ByteAddressingMode(शून्य){  //Enable 4-byte addressing Mode and read the status to verify that it has happened correctly

	जर(flashWriteEnable()){
		म_लिखो("\t Write Enable Failed \n");
		परत -1;
	}
	waitfor(100);
	set_qspi_shakti32(ccr,(CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xB7)));
	//  int status =0; 
	status = 0;
	पूर्णांक ret = wait_for_tcf(status);
	reset_interrupt_flags();
	waitfor(100);
	//Checking Phase
	status = flashReadStatusRegister();
	म_लिखो("\t Status Value: %08x\n",status);
	जर(status & 1)
		म_लिखो("\t 4-Byte Addressing Mode is Enabled\n");
	अन्यथा
		म_लिखो("\t 4-byte Addressing mode not Enabled\n");
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
पूर्णांक flashReadSingleSPI(पूर्णांक dummy_cycles, पूर्णांक read_address, पूर्णांक instruction, पूर्णांक data_शब्द, पूर्णांक adsize){
	set_qspi_shakti32(dlr,data_शब्द);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(SINGLE)|CCR_DCYC(dummy_cycles)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_ADSIZE(adsize)|CCR_INSTRUCTION(instruction)));
	set_qspi_shakti32(ar,read_address);
	status = 0;
	पूर्णांक ret = wait_for_tcf(status);
	पूर्णांक मूल्य = get_qspi_shakti(dr);
	म_लिखो("\tThe Read Value: %08x\n",मूल्य);
	//    printf("\tThe Read Value: %08x\n",value);
	जर(ret){
		म_लिखो("\t Read Value Failed \n");
		परत -1;
	}
	reset_interrupt_flags();
	परत मूल्य;
}

/** @fn int flashReadDualSPI(int address, int data_length)
 * @brief  Reads flash device over two io lines SPI.
 * @details Reads the flash device over two io lines for spi (IO1, IO2, CS, CLK) data
 * @param int address --- Address which needs to be read.
 * @param int data_length --- Number of Data bytes (data_words + 1) needs to be read 
 * @return Status of the performed operation; else -1
 */
पूर्णांक flashReadDualSPI(पूर्णांक address, पूर्णांक data_length){
	set_qspi_shakti32(dlr,data_length); //DLR
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(DOUBLE)|CCR_DCYC(3)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBB)));
	set_qspi_shakti32(ar,address); 
	//    printf("Status : %08x dcr : %08x cr : %08x ccr : %08x dlr: %08x ar: %08x\n",status,*dcr,*cr,*ccr,*dlr,*ar);
	पूर्णांक ret = wait_for_tcf(status);
	पूर्णांक मूल्य = get_qspi_shakti(dr);
	म_लिखो("\tThe Read Value: %08x\n",मूल्य);	
	जर(ret){
		म_लिखो("\t QSPI: Read Value failed\n");
		परत -1;
	}
	//*config_string = get_qspi_shakti(dr);
	//printf("\t Read Data is %08x\n",read_data);
	reset_interrupt_flags();
	परत मूल्य;
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
पूर्णांक flashReadQuadSPI(पूर्णांक dummy_cycles, पूर्णांक read_address, पूर्णांक instruction, पूर्णांक data_शब्द, पूर्णांक adsize){
	set_qspi_shakti32(dlr,data_शब्द);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DCYC(dummy_cycles)|CCR_ADSIZE(adsize)|CCR_ADMODE(QUAD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(instruction)));
	set_qspi_shakti32(ar,read_address);
	status = 0;
	पूर्णांक ret = wait_for_tcf(status);
	पूर्णांक मूल्य_1 = get_qspi_shakti(dr);
	पूर्णांक मूल्य_2_2 = get_qspi_shakti(dr);
	पूर्णांक मूल्य_3 = get_qspi_shakti(dr);
	पूर्णांक मूल्य_4 = get_qspi_shakti(dr);
	म_लिखो("\tThe Read Value: %08x, %08x, %08x and %08x \n",मूल्य_1,मूल्य_2_2,मूल्य_3,मूल्य_4);
	जर(ret){
		म_लिखो("\t Read Value Failed \n");
		परत -1; 
	}   
	reset_interrupt_flags();
	परत मूल्य_1;
}

/** @fn int flashSingleSPIXip(int addr, int* dest_addr) 
 * @brief Reads over single SPI XIP
 * @details Generic Read for xip SPI Read.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on success.
 */
पूर्णांक flashSingleSPIXip(पूर्णांक addr, पूर्णांक* dest_addr){
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(SINGLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(7)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x0C)));
	set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0x00)|DCR_CKMODE(1)));
	set_qspi_shakti32(dlr,0x4);
	set_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	status=0;
	wait_for_tcf(status);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	म_लिखो("\n Fisrt value obtained through single read : %d \n ",*dest_addr);
	reset_interrupt_flags(); 
	म_लिखो("\t Trying XIP now\n");
	set_qspi_shakti32(ccr, (CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(SINGLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(7)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x0C)));
	set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0x00)|DCR_CKMODE(1))); 
	waitfor(25);
	परत 0;
}

/** @fn int flashSingleSPIDDRXip(int addr, int* dest_addr)  
 * @brief Reads over DDR XIP mode.
 * @details Reads for DDR based XIP mode.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
पूर्णांक flashSingleSPIDDRXip(पूर्णांक addr, पूर्णांक* dest_addr){
	set_qspi_shakti32(ccr,(CCR_DDRM|CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(SINGLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(15)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x0E)));
	set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0x00)|DCR_CKMODE(1)));
	set_qspi_shakti32(dlr,0x4);
	set_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	status=0;
	wait_for_tcf(status);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	reset_interrupt_flags(); 
	म_लिखो("\t Trying XIP now\n");
	set_qspi_shakti32(ccr, (CCR_DDRM|CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(SINGLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(14)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x0E)));
	set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0x00)|DCR_CKMODE(1))); 
	waitfor(25);
	परत 0;
}

/** @fn int flashDualSPIXip(int addr, int* dest_addr)
 * @brief Reads over XIP mode.
 * @details Reads for XIP mode using two io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
पूर्णांक flashDualSPIXip(पूर्णांक addr, पूर्णांक* dest_addr){
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(DOUBLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(3)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBB)));
	set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0xA0)|DCR_CKMODE(1)));
	set_qspi_shakti32(dlr,0x4);
	set_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	status=0;
	wait_for_tcf(status);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	म_लिखो("\n Fisrt value obtained through single read : %d \n ",*dest_addr);
	reset_interrupt_flags(); 
	म_लिखो("\t Trying XIP now\n");
	set_qspi_shakti32(ccr, (CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(DOUBLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(3)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(NDATA)));
	set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0xA0)|DCR_CKMODE(1))); 
	waitfor(25);
	परत 0;
}

/** @fn int flashDualSPIDDRXip(int addr, int* dest_addr) 
 * @brief Reads over XIP mode.
 * @details Reads for DDR based XIP mode using two io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
पूर्णांक flashDualSPIDDRXip(पूर्णांक addr, पूर्णांक* dest_addr){
	set_qspi_shakti32(ccr,(CCR_DDRM|CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(DOUBLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(6)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBE)));
	set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0xA0)|DCR_CKMODE(1)));
	set_qspi_shakti32(dlr,0x4);
	set_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	status=0;
	wait_for_tcf(status);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	reset_interrupt_flags(); 
	म_लिखो("\t Trying XIP now\n");
	set_qspi_shakti32(ccr, (CCR_DDRM|CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(DOUBLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(6)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(NDATA)));
	set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0xA0)|DCR_CKMODE(1))); 
	waitfor(25);
	परत 0;
}

/** @fn int flashWriteVolatileConfigReg(int value) 
 * @brief Writes into flash volatile configuration register.
 * @details Writes the passed value into flash volatile configuration register.
 * @param int value needs to written into Write Volatile Config Register.
 * @return Zero on Success
 */
पूर्णांक flashWriteVolatileConfigReg(पूर्णांक मूल्य){
	म_लिखो("\t Setting Volatile Configuration Register with the Value: %08x\n",मूल्य);
	जर(micron_write_enable(status)){
		म_लिखो("Panic: Write Enable Command Failed to execute\n");
		परत -1;
	}
	reset_interrupt_flags();
	//	flashReadStatusRegister();
	set_qspi_shakti32(dlr,DL(1));
	set_qspi_shakti8(dr,मूल्य);  //The value to be written into the VECR register to enable XIP. Indicating XIP to operate in Quad Mode
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x01)));
	waitfor(50);
	status=0;
	पूर्णांक ret = wait_for_tcf(status);
	//    printf("Status : %d dcr : %d cr : %d ccr : %d dlr: %d dr: %d\n",status,*dcr,*cr,*ccr,*dlr,*dr);
	reset_interrupt_flags();
	waitfor(50);  //Giving Micron time to store the data
	परत ret;
}

/** @fn int flashQuadSPIXip(int addr, int* dest_addr)
 * @brief Reads over XIP mode.
 * @details Reads for DDR based XIP mode using quad io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
पूर्णांक flashQuadSPIXip(पूर्णांक addr, पूर्णांक* dest_addr){
	जर(flashWriteVolatileConfigReg(0x40404040)){
		म_लिखो("\t Volatile Configuration Register not Set -- Diagnose\n");
		परत -1;
	}
	status = wait_for_wip();
	म_लिखो("\t qspi status register %08x\n",status);
	reset_interrupt_flags();
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(5)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xEC)));
	set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0xA0)|DCR_CKMODE(1)));
	set_qspi_shakti32(dlr,0x4);
	set_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	status=0;
	wait_for_tcf(status);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	reset_interrupt_flags(); 
	म_लिखो("\t Trying XIP now\n");
	set_qspi_shakti32(ccr, (CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(QUAD)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(5)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(NDATA)));
	set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0xA0)|DCR_CKMODE(1))); 
	waitfor(25);
	परत 0;
}

/** @fn int flashQuadSPIDDRXip(int addr, int* dest_addr)
 * @brief Reads over XIP mode.
 * @details Reads for DDR based XIP mode using four io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
पूर्णांक flashQuadSPIDDRXip(पूर्णांक addr, पूर्णांक* dest_addr){
	जर(flashWriteVolatileConfigReg(0x40404040)){
		म_लिखो("\t Volatile Configuration Register not Set -- Diagnose\n");
		परत -1;
	}
	status = wait_for_wip();
	म_लिखो("\t qspi status register %08x\n",status);
	reset_interrupt_flags();
	set_qspi_shakti32(ccr,(CCR_DDRM|CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(10)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xEE)));
	set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0xA0)|DCR_CKMODE(1)));
	set_qspi_shakti32(dlr,0x4);
	set_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	status=0;
	wait_for_tcf(status);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	reset_interrupt_flags(); 
	म_लिखो("\t Trying XIP now\n");
	set_qspi_shakti32(ccr, (CCR_DDRM|CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(QUAD)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(10)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(NDATA)));
	set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0xA0)|DCR_CKMODE(1))); 
	waitfor(25);
	परत 0;
}

/** @fn int flash_Write_disable()
 * @brief disables write operation
 * @details Write operation can be possible only after enabling write enable register.
 *       Here this is disabled using this function.
 * @return Zero on Success
 */
पूर्णांक flash_Write_disable(शून्य){
	म_लिखो("\tWrite disable\n");
	set_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x04)));
	पूर्णांक ret = wait_for_tcf(status); //Indicating the completion of command -- Currently polling
	म_लिखो("Status : %d dcr : %d cr: %d ccr: %d \n",status,*dcr,*cr,*ccr);
	reset_interrupt_flags();
	परत wait_for_wip();
}

/** @fn int eraseSector(int command, int address)
 * @brief Erases one sector 
 * @details Erases a complete sector which falls in the sector range.
 * @param int command --- Erase command (sector erase, block erase or chip erase)
 * @param int address --- Starting address of erase.
 * @return Zero on Success
 */
पूर्णांक eraseSector(पूर्णांक command, पूर्णांक address){
	जर(micron_write_enable(status)){
		म_लिखो("Panic: Write Enable Command Failed to execute");
		परत -1;
	}
	reset_interrupt_flags();
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(command)));
	set_qspi_shakti32(ar,address);
	waitfor(150);
	पूर्णांक ret = wait_for_tcf(status);
	reset_interrupt_flags();
	परत wait_for_wip(); //For sector erase maybe estat should be checked
}

/** @fn int micron_volatile_write_enable(int status) 
 * @brief Enable for volatile write.
 * @details Enables micron flash for programming volatile config. register.
 * @param int --- status register value.
 * @return Zero on Success
 */
पूर्णांक micron_volatile_write_enable(पूर्णांक status){
	म_लिखो("\tVolatile Write Enable\n");
	set_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x50)));
	पूर्णांक ret = wait_for_tcf(status); //Indicating the completion of command -- Currently polling
	म_लिखो("Status : %d dcr : %d cr: %d ccr: %d \n",status,*dcr,*cr,*ccr);
	परत ret;
}

/** @fn int micron_enable_4byte_addressing(int status) 
 * @brief Enables micron flash for 4 byte addressing.
 * @details Address can be passed as 3 bytes or 4 bytes before read or write 
 * operation. This function sets the number of address bytes to 4 bytes.
 * @param int --- status register value
 * @return Zero on Success
 */
पूर्णांक micron_enable_4byte_addressing(पूर्णांक status){
	म_लिखो("\t Enable 4 byte address \n");
	set_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xB7)));
	पूर्णांक ret = wait_for_tcf(status); //Indicating the completion of command -- Currently polling
	म_लिखो("Status : %d dcr : %d cr: %d ccr: %d \n",status,*dcr,*cr,*ccr);
	परत ret;
}

/** @fn int micron_configure_xip_volatile(int status, int value)
 * @brief Configures the xip volatile config. register.
 * @details Configures the volatile config. register for xip Read mode.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
पूर्णांक micron_configure_xip_volatile(पूर्णांक status, पूर्णांक मूल्य){
	log_debug("\tWrite Volatile Configuration Register\n");
	set_qspi_shakti32(dlr,DL(1));
	set_qspi_shakti8(dr,मूल्य);  //The value to be written into the VECR register to enable XIP. Indicating XIP to operate in Quad Mode
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x81)));
	waitfor(50);
	पूर्णांक ret = wait_for_tcf(status);
	म_लिखो("Status : %d dcr : %d cr : %d ccr : %d dlr: %d dr: %d\n",status,*dcr,*cr,*ccr,*dlr,*dr);
	waitfor(50);  //Giving Micron time to store the data
	परत ret;
}

/** @fn int micron_disable_xip_volatile(int status, int value)
 * @brief Configures(disables) the xip volatile config. register.
 * @details Configures(disables) the volatile config. register for xip Read mode.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
पूर्णांक micron_disable_xip_volatile(पूर्णांक status, __attribute__ ((unused)) पूर्णांक मूल्य){
	log_debug("\tWrite Volatile Configuration Register to exit XIP\n");
	set_qspi_shakti32(cr,(CR_PRESCALER(0x3)|CR_TOIE|CR_TCIE|CR_TEIE|CR_SMIE|CR_FTIE|CR_ABORT|CR_EN));
	waitfor(30);
	qspi_init(27,0,3,1,15,1);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DUMMY_BIT|CCR_DUMMY_CONFIRMATION|CCR_DCYC(8)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(NDATA)));
	set_qspi_shakti32(ar,0x00000); //Dummy address 
	set_qspi_shakti32(dlr,1);

	पूर्णांक ret = wait_for_tcf(status);
	पूर्णांक temp_data = get_qspi_shakti(dr);

	waitfor(50);
	reset_interrupt_flags();
	परत ret;
}

/** @fn int micron_read_id_cmd(int status, int value)
 * @brief Reads the id of the micron flash.
 * @details Micron flash is having a fixed value as ID during production. This 
 * value is read to confirm proper flash device.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
पूर्णांक micron_read_id_cmd(पूर्णांक status, पूर्णांक मूल्य){
	log_debug("\tRead ID Command to see if the Protocol is Proper\n");
	set_qspi_shakti32(dlr,4);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x9E)|CCR_DMODE(SINGLE)));
	पूर्णांक ret = wait_for_tcf(status);
	मूल्य = get_qspi_shakti(dr);
	म_लिखो("Read ID: %08x",मूल्य);
	परत ret;
}

/** @fn int micron_read_configuration_register(int status, int value)
 * @brief Reads configuration register. 
 * @details The configurartion register is read using this function.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
पूर्णांक micron_read_configuration_register(पूर्णांक status, पूर्णांक मूल्य){
	म_लिखो("\tRead ID Command to see if the Protocol is Proper\n");
	set_qspi_shakti32(dlr,4);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBE)|CCR_DMODE(SINGLE)));
	पूर्णांक ret = wait_for_tcf(status);
	मूल्य = get_qspi_shakti(dr);
	log_debug("Configuration Register Value: %08x",मूल्य);
	परत ret;
}
