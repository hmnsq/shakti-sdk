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

#അന്തര്ഭാവ "qspi.h"
#അന്തര്ഭാവ "utils.h"
#അന്തര്ഭാവ "log.h"
#define MEM_TYPE_N25Q256_ID 0x9d189d18

അക്ഷരം fail_bit = 0;
പൂർണ്ണസംഖ്യ status = 0;
/*! Pointer to QSPI registers */
പൂർണ്ണസംഖ്യ* cr       =  (പൂർണ്ണസംഖ്യ*) CR; /*! Control Register */
പൂർണ്ണസംഖ്യ* dcr      =  (പൂർണ്ണസംഖ്യ*) DCR; /*! Data Configuration Register */
പൂർണ്ണസംഖ്യ* sr       =  (പൂർണ്ണസംഖ്യ*) SR; /*! Status Register */
പൂർണ്ണസംഖ്യ* fcr      =  (പൂർണ്ണസംഖ്യ*) FCR; /* Flag Clear Register */
പൂർണ്ണസംഖ്യ* ccr      =  (പൂർണ്ണസംഖ്യ*) CCR; /* Commn. Configuration Register */
പൂർണ്ണസംഖ്യ* ar       =  (പൂർണ്ണസംഖ്യ*) AR; /*! Address Register */
പൂർണ്ണസംഖ്യ* abr      =  (പൂർണ്ണസംഖ്യ*) ABR; /*! Alternate Bytes Register */
പൂർണ്ണസംഖ്യ* dr       =  (പൂർണ്ണസംഖ്യ*) DR; /*! Data Register */
പൂർണ്ണസംഖ്യ* dlr      =  (പൂർണ്ണസംഖ്യ*) DLR; /*! Data Length Register */
പൂർണ്ണസംഖ്യ* psmkr    =  (പൂർണ്ണസംഖ്യ*) PSMKR; /*! Polling Status Mask Register */
പൂർണ്ണസംഖ്യ* pir      =  (പൂർണ്ണസംഖ്യ*) PIR; /*! Polling Interval Register */
പൂർണ്ണസംഖ്യ* lprt     =  (പൂർണ്ണസംഖ്യ*) LPRT; /*! Low power Time Register */
പൂർണ്ണസംഖ്യ* startmm  =  (പൂർണ്ണസംഖ്യ*) STARTMM; /*! Start Memory Map Register */
പൂർണ്ണസംഖ്യ* endmm    =  (പൂർണ്ണസംഖ്യ*) ENDMM; /*! End Memory Map Register */

/** @fn void set_qspi_shakti32(int* addr, int val)
 * @brief Writes 32 bit value into QSPI register.
 * @details Writes 32 bit value into passed address QSPI register.
 * @param int* addr --- Addresss where the data (val) needs to be written
 * @param int val ---  Data which needs to be written.
 */
ശൂന്യം set_qspi_shakti32(പൂർണ്ണസംഖ്യ* addr, പൂർണ്ണസംഖ്യ val)
{
	*addr = val;
}

/** @fn void set_qspi_shakti16(int16_t* addr, int16_t val)
 * @brief Writes 16 bit value 
 * @details Writes 16 bit value into 16bit QSPI register 
 * @param 16bit int* addr --- Addresss where the data (val) needs to be written
 * @param 16bit int val ---  Data which needs to be written.
 */
ശൂന്യം set_qspi_shakti16(int16_t* addr, int16_t val)
{
	*addr = val;
}

/** @fn void set_qspi_shakti8(char* addr, char val) 
 * @brief Writes 8 bit value.
 * @details Writes 8 bit value into 8 bit qspi register.
 * @param char* addr --- Addresss where the data (val) needs to be written
 * @param char val ---  Data which needs to be written.
 */
ശൂന്യം set_qspi_shakti8(അക്ഷരം* addr, അക്ഷരം val)
{
	*addr= val;
}

/** @fn int get_qspi_shakti(int* addr)
 * @brief reads from qspi register
 * @details Reads from the passed QSPI register and returns the value.
 * @param int* addr --- 32 bit Read Addresss  
 * @return Read value -- Read value from the passed value.
 */
പൂർണ്ണസംഖ്യ get_qspi_shakti(പൂർണ്ണസംഖ്യ* addr)
{
	തിരികെ *addr;
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
ശൂന്യം qspi_init(പൂർണ്ണസംഖ്യ fsize, പൂർണ്ണസംഖ്യ csht, പൂർണ്ണസംഖ്യ prescaler, പൂർണ്ണസംഖ്യ enable_interrupts, പൂർണ്ണസംഖ്യ fthreshold, പൂർണ്ണസംഖ്യ ck_mode){
	പൂർണ്ണസംഖ്യ int_vector = enable_interrupts? (CR_TOIE|CR_SMIE|CR_FTIE|CR_TCIE|CR_TEIE) : 0; 
	set_qspi_shakti32(dcr,(DCR_FSIZE(fsize)|DCR_CSHT(csht)|DCR_CKMODE(ck_mode))); 
	set_qspi_shakti32(cr,(CR_PRESCALER(prescaler)|int_vector|CR_FTHRES(fthreshold)|CR_EN));
}

/** @fn void reset_interrupt_flags()
 * @brief Resets interrupt flags.
 * @details Before carrying out any flash access operations, the interrupt flags are cleared.
 */
ശൂന്യം reset_interrupt_flags(){
	set_qspi_shakti32(fcr,(FCR_CTOF|FCR_CSMF|FCR_CTCF|FCR_CTEF)); //Resetting all the flags
}

/** @fn int wait_for_tcf(int status)
 * @brief Wait for the transfer complete flag.
 * @details WCF bit status register indicates the completion of flash 
 *  operation. The same is cheked here.
 * @param int status register read value.
 * @return Zero on success else -1
 */
പൂർണ്ണസംഖ്യ wait_for_tcf(പൂർണ്ണസംഖ്യ status){
	പൂർണ്ണസംഖ്യ timeout = DEF_TIMEOUT; 

	status = get_qspi_shakti(sr);

	//    printf("status : %d looping?\n",status);

	ആകുമ്പോൾ(!( status & 0x02 ) && --timeout){
		waitfor(1000);
		status=get_qspi_shakti(sr);
		printf("status: %08x in loop %d \n",status, !(status & 0x02));
	}
	എങ്കിൽ(timeout==0){
		printf("Request Timed out\n");
		തിരികെ -1;
	}
	തിരികെ 0;
}

/** @fn int check_fail_bit()
 * @brief Checks the value of fail_bit.
 * @details Checks the fail bit whether the value is zero or not.
 */
പൂർണ്ണസംഖ്യ check_fail_bit(ശൂന്യം){
	എങ്കിൽ(fail_bit){
		fail_bit = 0;
		തിരികെ -1;
	}
	അല്ലെങ്കിൽ{
		fail_bit = 0;
		തിരികെ 0;
	}
}

/** @fn int flashReadStatusRegister()
 * @brief Reads flash status register
 * @details Reads flash status register contents
 * @return Status register value on success; else -1
 */
പൂർണ്ണസംഖ്യ flashReadStatusRegister(){
	//    printf("\tReading the Status bits of the Flash\n");
	set_qspi_shakti32(dlr,4);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x05)|CCR_DMODE(SINGLE)));

	status = 0;
	waitfor(1000);
	പൂർണ്ണസംഖ്യ ret = wait_for_tcf(status);
	waitfor(100);
	പൂർണ്ണസംഖ്യ മൂല്യം = get_qspi_shakti(dr);
	//	printf("Read status register value %08x \n", value);
	reset_interrupt_flags();
	എങ്കിൽ(ret){
		printf("\tRead Status Register Failed\n");
		fail_bit = 1;
		തിരികെ -1;
	}
	അല്ലെങ്കിൽ
		തിരികെ മൂല്യം;
}

/** @fn int wait_for_wip()
 * @brief Wait till a flash access is complete.
 * @details Reads the WIP bit in the status register to check the completion of flash access.
 * Useful during flash write operations.
 * @return Zero on Success
 */
പൂർണ്ണസംഖ്യ wait_for_wip(ശൂന്യം){
	പൂർണ്ണസംഖ്യ status1;
	ചെയ്യുക{
		//  printf("\t Waiting for Wip \n");
		status1 = flashReadStatusRegister(0x05);
		എങ്കിൽ(check_fail_bit())
			തിരികെ -1;
		എങ്കിൽ(status1 & 0x0){
			printf("\tQSPI: Programming Error - Diagnose\n");
			തിരികെ -1;
		}
		waitfor(20000);
	}ആകുമ്പോൾ(status1 & 0x01);
	//    printf("\t QSPI: Page Program/Erase Command Successfully Completed\n");
	തിരികെ 0;
}

/** @fn int micron_write_enable(int status)
 * @brief Enables the micron flash for write operation.
 * @details Enables micron flash for programming flash data.
 * @param int status --- Write enable status.
 * @return Zero on Success
 */
പൂർണ്ണസംഖ്യ micron_write_enable(പൂർണ്ണസംഖ്യ status){
	//  printf("\tWrite Enable\n");
	set_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x06)));
	പൂർണ്ണസംഖ്യ ret = wait_for_tcf(status); //Indicating the completion of command -- Currently polling
	//  printf("Status : %d dcr : %d cr: %d ccr: %d \n",status,*dcr,*cr,*ccr);
	തിരികെ ret;
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
പൂർണ്ണസംഖ്യ pageProgramSingleSPI(പൂർണ്ണസംഖ്യ value1, പൂർണ്ണസംഖ്യ value2, പൂർണ്ണസംഖ്യ value3, പൂർണ്ണസംഖ്യ value4, പൂർണ്ണസംഖ്യ address){
	എങ്കിൽ(micron_write_enable(status)){
		printf("Panic: Write Enable Command Failed to execute");
		തിരികെ -1;
	}
	reset_interrupt_flags(); 

	set_qspi_shakti32(dlr,DL(16));
	// set_qspi_shakti32(ccr,(CCR_DDRM | CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x12))); 
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x12)));
	set_qspi_shakti32(ar, address);        
	printf(" Address written %d \n",address); 
	set_qspi_shakti32(dr,value1);
	printf(" Value 1 written %d \n",value1);
	set_qspi_shakti32(dr,value2);
	printf(" Value 2 written %d \n",value2);
	set_qspi_shakti32(dr,value3);
	printf(" Value 3 written %d \n",value3);
	set_qspi_shakti32(dr,value4);
	printf(" Value 4 written %d \n",value4);
	waitfor(150); 
	wait_for_tcf(status);
	reset_interrupt_flags();
	തിരികെ wait_for_wip(); // Function which checks if WIP is done, indicating completion of Page Program
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
പൂർണ്ണസംഖ്യ pageProgramQuadSPI(പൂർണ്ണസംഖ്യ value1, പൂർണ്ണസംഖ്യ value2, പൂർണ്ണസംഖ്യ value3, പൂർണ്ണസംഖ്യ value4, പൂർണ്ണസംഖ്യ address){
	എങ്കിൽ(micron_write_enable(status)){
		printf("Panic: Write Enable Command Failed to execute");
		തിരികെ -1;
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
	തിരികെ wait_for_wip(); // Function which checks if WIP is done, indicating completion of Page Program
}

/** @fn int flashIdentificationDevice()
 * @brief Reads flash id code.
 * @details Reads flash identification code from the flash device and checks whether it valid.
 * @return Zero on success else -1
 */
പൂർണ്ണസംഖ്യ flashIdentificationDevice(ശൂന്യം){
	log_debug("\tReading the ID register and discovering the Flash Device\n");
	set_qspi_shakti32(dlr,4);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x90)|CCR_ADSIZE(THREEBYTE)|CCR_ADMODE(SINGLE)|CCR_DMODE(SINGLE)));
	set_qspi_shakti32(ar, 0);
	status = 0; // Useless Variable but still!!!!
	പൂർണ്ണസംഖ്യ ret = wait_for_tcf(status);
	പൂർണ്ണസംഖ്യ മൂല്യം = get_qspi_shakti(dr);
	log_info("\t device id %x\n",മൂല്യം);
	reset_interrupt_flags();
	എങ്കിൽ(മൂല്യം == MEM_TYPE_N25Q256_ID){
		printf("\tN25Q256 Device Detected \n");
		തിരികെ 0;
	}
	അല്ലെങ്കിൽ{
		log_fatal("\t Device Not Detected - Diagnose %08x\n",മൂല്യം);
		തിരികെ -1;
	}
}

/** @fn int flashMemInit()
 * @brief Initialises flash memory 
 * @details Initialises flash device and check for id code.
 * @return Zero on success else -1
 */
പൂർണ്ണസംഖ്യ flashMemInit(){  //Supposedly a set of routines to check if the memory/interface or whatever is proper
	പൂർണ്ണസംഖ്യ ret = flashIdentificationDevice();
	എങ്കിൽ(ret==-1){
		log_fatal("Flash Mem Init Failed -- Quitting Program, Diagnose");
		തിരികെ ret;
	}
	അല്ലെങ്കിൽ log_debug("Flash Mem Init Success\n");
	തിരികെ 0;
	//to fill in code
}


/** @fn int flashReadFlagRegister()
 * @brief Reads flash read flag. 
 * @details Reads the flash flag register.
 * @warning Not implemented now. Reserve for future.
 */
പൂർണ്ണസംഖ്യ flashReadFlagRegister(ശൂന്യം){
	തിരികെ 0;
}

/** @fn int flashWriteEnable()
 * @brief Enables flash enable bit
 * @details For any write operation into to flash device (erase, program, etc.)
 *        this enable bit needs to be enabled.
 * @return TCF status
 */
പൂർണ്ണസംഖ്യ flashWriteEnable(ശൂന്യം){
	printf("\tWrite Enable\n");
	set_qspi_shakti32(ccr,(CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x06)));
	പൂർണ്ണസംഖ്യ ret = wait_for_tcf(0); //Indicating the completion of command -- Currently polling
	reset_interrupt_flags();
	തിരികെ ret; 
}

/** @fn int flashEnable4ByteAddressingMode()
 * @brief Selects the addressed mode.
 * @details Before accessing flash device, the number of bits used for (Q)SPI needs to be programmed.
 * @return Status of the performed operation; else -1
 */
പൂർണ്ണസംഖ്യ flashEnable4ByteAddressingMode(ശൂന്യം){  //Enable 4-byte addressing Mode and read the status to verify that it has happened correctly

	എങ്കിൽ(flashWriteEnable()){
		printf("\t Write Enable Failed \n");
		തിരികെ -1;
	}
	waitfor(100);
	set_qspi_shakti32(ccr,(CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xB7)));
	//  int status =0; 
	status = 0;
	പൂർണ്ണസംഖ്യ ret = wait_for_tcf(status);
	reset_interrupt_flags();
	waitfor(100);
	//Checking Phase
	status = flashReadStatusRegister();
	printf("\t Status Value: %08x\n",status);
	എങ്കിൽ(status & 1)
		printf("\t 4-Byte Addressing Mode is Enabled\n");
	അല്ലെങ്കിൽ
		printf("\t 4-byte Addressing mode not Enabled\n");
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
പൂർണ്ണസംഖ്യ flashReadSingleSPI(പൂർണ്ണസംഖ്യ dummy_cycles, പൂർണ്ണസംഖ്യ read_address, പൂർണ്ണസംഖ്യ instruction, പൂർണ്ണസംഖ്യ data_വാക്കുകൾ, പൂർണ്ണസംഖ്യ adsize){
	set_qspi_shakti32(dlr,data_വാക്കുകൾ);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(SINGLE)|CCR_DCYC(dummy_cycles)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_ADSIZE(adsize)|CCR_INSTRUCTION(instruction)));
	set_qspi_shakti32(ar,read_address);
	status = 0;
	പൂർണ്ണസംഖ്യ ret = wait_for_tcf(status);
	പൂർണ്ണസംഖ്യ മൂല്യം = get_qspi_shakti(dr);
	printf("\tThe Read Value: %08x\n",മൂല്യം);
	//    printf("\tThe Read Value: %08x\n",value);
	എങ്കിൽ(ret){
		printf("\t Read Value Failed \n");
		തിരികെ -1;
	}
	reset_interrupt_flags();
	തിരികെ മൂല്യം;
}

/** @fn int flashReadDualSPI(int address, int data_length)
 * @brief  Reads flash device over two io lines SPI.
 * @details Reads the flash device over two io lines for spi (IO1, IO2, CS, CLK) data
 * @param int address --- Address which needs to be read.
 * @param int data_length --- Number of Data bytes (data_words + 1) needs to be read 
 * @return Status of the performed operation; else -1
 */
പൂർണ്ണസംഖ്യ flashReadDualSPI(പൂർണ്ണസംഖ്യ address, പൂർണ്ണസംഖ്യ data_length){
	set_qspi_shakti32(dlr,data_length); //DLR
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(DOUBLE)|CCR_DCYC(3)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBB)));
	set_qspi_shakti32(ar,address); 
	//    printf("Status : %08x dcr : %08x cr : %08x ccr : %08x dlr: %08x ar: %08x\n",status,*dcr,*cr,*ccr,*dlr,*ar);
	പൂർണ്ണസംഖ്യ ret = wait_for_tcf(status);
	പൂർണ്ണസംഖ്യ മൂല്യം = get_qspi_shakti(dr);
	printf("\tThe Read Value: %08x\n",മൂല്യം);	
	എങ്കിൽ(ret){
		printf("\t QSPI: Read Value failed\n");
		തിരികെ -1;
	}
	//*config_string = get_qspi_shakti(dr);
	//printf("\t Read Data is %08x\n",read_data);
	reset_interrupt_flags();
	തിരികെ മൂല്യം;
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
പൂർണ്ണസംഖ്യ flashReadQuadSPI(പൂർണ്ണസംഖ്യ dummy_cycles, പൂർണ്ണസംഖ്യ read_address, പൂർണ്ണസംഖ്യ instruction, പൂർണ്ണസംഖ്യ data_വാക്കുകൾ, പൂർണ്ണസംഖ്യ adsize){
	set_qspi_shakti32(dlr,data_വാക്കുകൾ);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DCYC(dummy_cycles)|CCR_ADSIZE(adsize)|CCR_ADMODE(QUAD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(instruction)));
	set_qspi_shakti32(ar,read_address);
	status = 0;
	പൂർണ്ണസംഖ്യ ret = wait_for_tcf(status);
	പൂർണ്ണസംഖ്യ മൂല്യം_1 = get_qspi_shakti(dr);
	പൂർണ്ണസംഖ്യ മൂല്യം_2_2 = get_qspi_shakti(dr);
	പൂർണ്ണസംഖ്യ മൂല്യം_3 = get_qspi_shakti(dr);
	പൂർണ്ണസംഖ്യ മൂല്യം_4 = get_qspi_shakti(dr);
	printf("\tThe Read Value: %08x, %08x, %08x and %08x \n",മൂല്യം_1,മൂല്യം_2_2,മൂല്യം_3,മൂല്യം_4);
	എങ്കിൽ(ret){
		printf("\t Read Value Failed \n");
		തിരികെ -1; 
	}   
	reset_interrupt_flags();
	തിരികെ മൂല്യം_1;
}

/** @fn int flashSingleSPIXip(int addr, int* dest_addr) 
 * @brief Reads over single SPI XIP
 * @details Generic Read for xip SPI Read.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on success.
 */
പൂർണ്ണസംഖ്യ flashSingleSPIXip(പൂർണ്ണസംഖ്യ addr, പൂർണ്ണസംഖ്യ* dest_addr){
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(SINGLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(7)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x0C)));
	set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0x00)|DCR_CKMODE(1)));
	set_qspi_shakti32(dlr,0x4);
	set_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	status=0;
	wait_for_tcf(status);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	printf("\n Fisrt value obtained through single read : %d \n ",*dest_addr);
	reset_interrupt_flags(); 
	printf("\t Trying XIP now\n");
	set_qspi_shakti32(ccr, (CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(SINGLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(7)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x0C)));
	set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0x00)|DCR_CKMODE(1))); 
	waitfor(25);
	തിരികെ 0;
}

/** @fn int flashSingleSPIDDRXip(int addr, int* dest_addr)  
 * @brief Reads over DDR XIP mode.
 * @details Reads for DDR based XIP mode.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
പൂർണ്ണസംഖ്യ flashSingleSPIDDRXip(പൂർണ്ണസംഖ്യ addr, പൂർണ്ണസംഖ്യ* dest_addr){
	set_qspi_shakti32(ccr,(CCR_DDRM|CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(SINGLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(15)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x0E)));
	set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0x00)|DCR_CKMODE(1)));
	set_qspi_shakti32(dlr,0x4);
	set_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	status=0;
	wait_for_tcf(status);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	reset_interrupt_flags(); 
	printf("\t Trying XIP now\n");
	set_qspi_shakti32(ccr, (CCR_DDRM|CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(SINGLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(14)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x0E)));
	set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0x00)|DCR_CKMODE(1))); 
	waitfor(25);
	തിരികെ 0;
}

/** @fn int flashDualSPIXip(int addr, int* dest_addr)
 * @brief Reads over XIP mode.
 * @details Reads for XIP mode using two io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
പൂർണ്ണസംഖ്യ flashDualSPIXip(പൂർണ്ണസംഖ്യ addr, പൂർണ്ണസംഖ്യ* dest_addr){
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(DOUBLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(3)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBB)));
	set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0xA0)|DCR_CKMODE(1)));
	set_qspi_shakti32(dlr,0x4);
	set_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	status=0;
	wait_for_tcf(status);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	printf("\n Fisrt value obtained through single read : %d \n ",*dest_addr);
	reset_interrupt_flags(); 
	printf("\t Trying XIP now\n");
	set_qspi_shakti32(ccr, (CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(DOUBLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(3)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(NDATA)));
	set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0xA0)|DCR_CKMODE(1))); 
	waitfor(25);
	തിരികെ 0;
}

/** @fn int flashDualSPIDDRXip(int addr, int* dest_addr) 
 * @brief Reads over XIP mode.
 * @details Reads for DDR based XIP mode using two io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
പൂർണ്ണസംഖ്യ flashDualSPIDDRXip(പൂർണ്ണസംഖ്യ addr, പൂർണ്ണസംഖ്യ* dest_addr){
	set_qspi_shakti32(ccr,(CCR_DDRM|CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(DOUBLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(6)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBE)));
	set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0xA0)|DCR_CKMODE(1)));
	set_qspi_shakti32(dlr,0x4);
	set_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	status=0;
	wait_for_tcf(status);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	reset_interrupt_flags(); 
	printf("\t Trying XIP now\n");
	set_qspi_shakti32(ccr, (CCR_DDRM|CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(DOUBLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(6)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(NDATA)));
	set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0xA0)|DCR_CKMODE(1))); 
	waitfor(25);
	തിരികെ 0;
}

/** @fn int flashWriteVolatileConfigReg(int value) 
 * @brief Writes into flash volatile configuration register.
 * @details Writes the passed value into flash volatile configuration register.
 * @param int value needs to written into Write Volatile Config Register.
 * @return Zero on Success
 */
പൂർണ്ണസംഖ്യ flashWriteVolatileConfigReg(പൂർണ്ണസംഖ്യ മൂല്യം){
	printf("\t Setting Volatile Configuration Register with the Value: %08x\n",മൂല്യം);
	എങ്കിൽ(micron_write_enable(status)){
		printf("Panic: Write Enable Command Failed to execute\n");
		തിരികെ -1;
	}
	reset_interrupt_flags();
	//	flashReadStatusRegister();
	set_qspi_shakti32(dlr,DL(1));
	set_qspi_shakti8(dr,മൂല്യം);  //The value to be written into the VECR register to enable XIP. Indicating XIP to operate in Quad Mode
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x01)));
	waitfor(50);
	status=0;
	പൂർണ്ണസംഖ്യ ret = wait_for_tcf(status);
	//    printf("Status : %d dcr : %d cr : %d ccr : %d dlr: %d dr: %d\n",status,*dcr,*cr,*ccr,*dlr,*dr);
	reset_interrupt_flags();
	waitfor(50);  //Giving Micron time to store the data
	തിരികെ ret;
}

/** @fn int flashQuadSPIXip(int addr, int* dest_addr)
 * @brief Reads over XIP mode.
 * @details Reads for DDR based XIP mode using quad io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
പൂർണ്ണസംഖ്യ flashQuadSPIXip(പൂർണ്ണസംഖ്യ addr, പൂർണ്ണസംഖ്യ* dest_addr){
	എങ്കിൽ(flashWriteVolatileConfigReg(0x40404040)){
		printf("\t Volatile Configuration Register not Set -- Diagnose\n");
		തിരികെ -1;
	}
	status = wait_for_wip();
	printf("\t qspi status register %08x\n",status);
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
	printf("\t Trying XIP now\n");
	set_qspi_shakti32(ccr, (CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(QUAD)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(5)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(NDATA)));
	set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0xA0)|DCR_CKMODE(1))); 
	waitfor(25);
	തിരികെ 0;
}

/** @fn int flashQuadSPIDDRXip(int addr, int* dest_addr)
 * @brief Reads over XIP mode.
 * @details Reads for DDR based XIP mode using four io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
പൂർണ്ണസംഖ്യ flashQuadSPIDDRXip(പൂർണ്ണസംഖ്യ addr, പൂർണ്ണസംഖ്യ* dest_addr){
	എങ്കിൽ(flashWriteVolatileConfigReg(0x40404040)){
		printf("\t Volatile Configuration Register not Set -- Diagnose\n");
		തിരികെ -1;
	}
	status = wait_for_wip();
	printf("\t qspi status register %08x\n",status);
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
	printf("\t Trying XIP now\n");
	set_qspi_shakti32(ccr, (CCR_DDRM|CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(QUAD)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(10)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(NDATA)));
	set_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_MODE_BYTE(0xA0)|DCR_CKMODE(1))); 
	waitfor(25);
	തിരികെ 0;
}

/** @fn int flash_Write_disable()
 * @brief disables write operation
 * @details Write operation can be possible only after enabling write enable register.
 *       Here this is disabled using this function.
 * @return Zero on Success
 */
പൂർണ്ണസംഖ്യ flash_Write_disable(ശൂന്യം){
	printf("\tWrite disable\n");
	set_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x04)));
	പൂർണ്ണസംഖ്യ ret = wait_for_tcf(status); //Indicating the completion of command -- Currently polling
	printf("Status : %d dcr : %d cr: %d ccr: %d \n",status,*dcr,*cr,*ccr);
	reset_interrupt_flags();
	തിരികെ wait_for_wip();
}

/** @fn int eraseSector(int command, int address)
 * @brief Erases one sector 
 * @details Erases a complete sector which falls in the sector range.
 * @param int command --- Erase command (sector erase, block erase or chip erase)
 * @param int address --- Starting address of erase.
 * @return Zero on Success
 */
പൂർണ്ണസംഖ്യ eraseSector(പൂർണ്ണസംഖ്യ command, പൂർണ്ണസംഖ്യ address){
	എങ്കിൽ(micron_write_enable(status)){
		printf("Panic: Write Enable Command Failed to execute");
		തിരികെ -1;
	}
	reset_interrupt_flags();
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(command)));
	set_qspi_shakti32(ar,address);
	waitfor(150);
	പൂർണ്ണസംഖ്യ ret = wait_for_tcf(status);
	reset_interrupt_flags();
	തിരികെ wait_for_wip(); //For sector erase maybe estat should be checked
}

/** @fn int micron_volatile_write_enable(int status) 
 * @brief Enable for volatile write.
 * @details Enables micron flash for programming volatile config. register.
 * @param int --- status register value.
 * @return Zero on Success
 */
പൂർണ്ണസംഖ്യ micron_volatile_write_enable(പൂർണ്ണസംഖ്യ status){
	printf("\tVolatile Write Enable\n");
	set_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x50)));
	പൂർണ്ണസംഖ്യ ret = wait_for_tcf(status); //Indicating the completion of command -- Currently polling
	printf("Status : %d dcr : %d cr: %d ccr: %d \n",status,*dcr,*cr,*ccr);
	തിരികെ ret;
}

/** @fn int micron_enable_4byte_addressing(int status) 
 * @brief Enables micron flash for 4 byte addressing.
 * @details Address can be passed as 3 bytes or 4 bytes before read or write 
 * operation. This function sets the number of address bytes to 4 bytes.
 * @param int --- status register value
 * @return Zero on Success
 */
പൂർണ്ണസംഖ്യ micron_enable_4byte_addressing(പൂർണ്ണസംഖ്യ status){
	printf("\t Enable 4 byte address \n");
	set_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xB7)));
	പൂർണ്ണസംഖ്യ ret = wait_for_tcf(status); //Indicating the completion of command -- Currently polling
	printf("Status : %d dcr : %d cr: %d ccr: %d \n",status,*dcr,*cr,*ccr);
	തിരികെ ret;
}

/** @fn int micron_configure_xip_volatile(int status, int value)
 * @brief Configures the xip volatile config. register.
 * @details Configures the volatile config. register for xip Read mode.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
പൂർണ്ണസംഖ്യ micron_configure_xip_volatile(പൂർണ്ണസംഖ്യ status, പൂർണ്ണസംഖ്യ മൂല്യം){
	log_debug("\tWrite Volatile Configuration Register\n");
	set_qspi_shakti32(dlr,DL(1));
	set_qspi_shakti8(dr,മൂല്യം);  //The value to be written into the VECR register to enable XIP. Indicating XIP to operate in Quad Mode
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x81)));
	waitfor(50);
	പൂർണ്ണസംഖ്യ ret = wait_for_tcf(status);
	printf("Status : %d dcr : %d cr : %d ccr : %d dlr: %d dr: %d\n",status,*dcr,*cr,*ccr,*dlr,*dr);
	waitfor(50);  //Giving Micron time to store the data
	തിരികെ ret;
}

/** @fn int micron_disable_xip_volatile(int status, int value)
 * @brief Configures(disables) the xip volatile config. register.
 * @details Configures(disables) the volatile config. register for xip Read mode.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
പൂർണ്ണസംഖ്യ micron_disable_xip_volatile(പൂർണ്ണസംഖ്യ status, __attribute__ ((unused)) പൂർണ്ണസംഖ്യ മൂല്യം){
	log_debug("\tWrite Volatile Configuration Register to exit XIP\n");
	set_qspi_shakti32(cr,(CR_PRESCALER(0x3)|CR_TOIE|CR_TCIE|CR_TEIE|CR_SMIE|CR_FTIE|CR_ABORT|CR_EN));
	waitfor(30);
	qspi_init(27,0,3,1,15,1);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DUMMY_BIT|CCR_DUMMY_CONFIRMATION|CCR_DCYC(8)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(NDATA)));
	set_qspi_shakti32(ar,0x00000); //Dummy address 
	set_qspi_shakti32(dlr,1);

	പൂർണ്ണസംഖ്യ ret = wait_for_tcf(status);
	പൂർണ്ണസംഖ്യ temp_data = get_qspi_shakti(dr);

	waitfor(50);
	reset_interrupt_flags();
	തിരികെ ret;
}

/** @fn int micron_read_id_cmd(int status, int value)
 * @brief Reads the id of the micron flash.
 * @details Micron flash is having a fixed value as ID during production. This 
 * value is read to confirm proper flash device.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
പൂർണ്ണസംഖ്യ micron_read_id_cmd(പൂർണ്ണസംഖ്യ status, പൂർണ്ണസംഖ്യ മൂല്യം){
	log_debug("\tRead ID Command to see if the Protocol is Proper\n");
	set_qspi_shakti32(dlr,4);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x9E)|CCR_DMODE(SINGLE)));
	പൂർണ്ണസംഖ്യ ret = wait_for_tcf(status);
	മൂല്യം = get_qspi_shakti(dr);
	printf("Read ID: %08x",മൂല്യം);
	തിരികെ ret;
}

/** @fn int micron_read_configuration_register(int status, int value)
 * @brief Reads configuration register. 
 * @details The configurartion register is read using this function.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
പൂർണ്ണസംഖ്യ micron_read_configuration_register(പൂർണ്ണസംഖ്യ status, പൂർണ്ണസംഖ്യ മൂല്യം){
	printf("\tRead ID Command to see if the Protocol is Proper\n");
	set_qspi_shakti32(dlr,4);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBE)|CCR_DMODE(SINGLE)));
	പൂർണ്ണസംഖ്യ ret = wait_for_tcf(status);
	മൂല്യം = get_qspi_shakti(dr);
	log_debug("Configuration Register Value: %08x",മൂല്യം);
	തിരികെ ret;
}
