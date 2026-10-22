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

#include "qspi.h"
#include "utils.h"
#include "log.h"
#define MEM_TYPE_N25Q256_ID 0x9d189d18

var_na fail_bit = 0;
ཧྲིལ status = 0;
/*! Pointer to QSPI registers */
ཧྲིལ* cr       =  (ཧྲིལ*) CR; /*! Control Register */
ཧྲིལ* dcr      =  (ཧྲིལ*) DCR; /*! Data Configuration Register */
ཧྲིལ* sr       =  (ཧྲིལ*) SR; /*! Status Register */
ཧྲིལ* fcr      =  (ཧྲིལ*) FCR; /* Flag Clear Register */
ཧྲིལ* ccr      =  (ཧྲིལ*) CCR; /* Commn. Configuration Register */
ཧྲིལ* ar       =  (ཧྲིལ*) AR; /*! Address Register */
ཧྲིལ* abr      =  (ཧྲིལ*) ABR; /*! Alternate Bytes Register */
ཧྲིལ* dr       =  (ཧྲིལ*) DR; /*! Data Register */
ཧྲིལ* dlr      =  (ཧྲིལ*) DLR; /*! Data Length Register */
ཧྲིལ* psmkr    =  (ཧྲིལ*) PSMKR; /*! Polling Status Mask Register */
ཧྲིལ* pir      =  (ཧྲིལ*) PIR; /*! Polling Interval Register */
ཧྲིལ* lprt     =  (ཧྲིལ*) LPRT; /*! Low power Time Register */
ཧྲིལ* startmm  =  (ཧྲིལ*) STARTMM; /*! Start Memory Map Register */
ཧྲིལ* endmm    =  (ཧྲིལ*) ENDMM; /*! End Memory Map Register */

/** @fn void set_qspi_shakti32(int* addr, int val)
 * @brief Writes 32 bit value into QSPI register.
 * @details Writes 32 bit value into passed address QSPI register.
 * @param int* addr --- Addresss where the data (val) needs to be written
 * @param int val ---  Data which needs to be written.
 */
void set_qspi_shakti32(ཧྲིལ* addr, ཧྲིལ val)
{
	*addr = val;
}

/** @fn void set_qspi_shakti16(int16_t* addr, int16_t val)
 * @brief Writes 16 bit value 
 * @details Writes 16 bit value into 16bit QSPI register 
 * @param 16bit int* addr --- Addresss where the data (val) needs to be written
 * @param 16bit int val ---  Data which needs to be written.
 */
void set_qspi_shakti16(int16_t* addr, int16_t val)
{
	*addr = val;
}

/** @fn void set_qspi_shakti8(char* addr, char val) 
 * @brief Writes 8 bit value.
 * @details Writes 8 bit value into 8 bit qspi register.
 * @param char* addr --- Addresss where the data (val) needs to be written
 * @param char val ---  Data which needs to be written.
 */
void set_qspi_shakti8(var_na* addr, var_na val)
{
	*addr= val;
}

/** @fn int get_qspi_shakti(int* addr)
 * @brief reads from qspi register
 * @details Reads from the passed QSPI register and returns the value.
 * @param int* addr --- 32 bit Read Addresss  
 * @return Read value -- Read value from the passed value.
 */
ཧྲིལ get_qspi_shakti(ཧྲིལ* addr)
{
	ལོག *addr;
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
void qspi_init(ཧྲིལ fsize, ཧྲིལ csht, ཧྲིལ prescaler, ཧྲིལ enable_interrupts, ཧྲིལ fthreshold, ཧྲིལ ck_mode){
	ཧྲིལ int_vector = enable_interrupts? (CR_TOIE|CR_SMIE|CR_FTIE|CR_TCIE|CR_TEIE) : 0; 
	set_qspi_shakti32(dcr,(DCR_FSIZE(fsize)|DCR_CSHT(csht)|DCR_CKMODE(ck_mode))); 
	set_qspi_shakti32(cr,(CR_PRESCALER(prescaler)|int_vector|CR_FTHRES(fthreshold)|CR_EN));
}

/** @fn void reset_interrupt_flags()
 * @brief Resets interrupt flags.
 * @details Before carrying out any flash access operations, the interrupt flags are cleared.
 */
void reset_interrupt_flags(){
	set_qspi_shakti32(fcr,(FCR_CTOF|FCR_CSMF|FCR_CTCF|FCR_CTEF)); //Resetting all the flags
}

/** @fn int wait_for_tcf(int status)
 * @brief Wait for the transfer complete flag.
 * @details WCF bit status register indicates the completion of flash 
 *  operation. The same is cheked here.
 * @param int status register read value.
 * @return Zero on success else -1
 */
ཧྲིལ wait_for_tcf(ཧྲིལ status){
	ཧྲིལ timeout = DEF_TIMEOUT; 

	status = get_qspi_shakti(sr);

	//    printf("status : %d looping?\n",status);

	སྐབས(!( status & 0x02 ) && --timeout){
		waitfor(1000);
		status=get_qspi_shakti(sr);
		printf("status: %08x in loop %d \n",status, !(status & 0x02));
	}
	གལ་སྲིད(timeout==0){
		printf("Request Timed out\n");
		ལོག -1;
	}
	ལོག 0;
}

/** @fn int check_fail_bit()
 * @brief Checks the value of fail_bit.
 * @details Checks the fail bit whether the value is zero or not.
 */
ཧྲིལ check_fail_bit(void){
	གལ་སྲིད(fail_bit){
		fail_bit = 0;
		ལོག -1;
	}
	དེ་མིན{
		fail_bit = 0;
		ལོག 0;
	}
}

/** @fn int flashReadStatusRegister()
 * @brief Reads flash status register
 * @details Reads flash status register contents
 * @return Status register value on success; else -1
 */
ཧྲིལ flashReadStatusRegister(){
	//    printf("\tReading the Status bits of the Flash\n");
	set_qspi_shakti32(dlr,4);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x05)|CCR_DMODE(SINGLE)));

	status = 0;
	waitfor(1000);
	ཧྲིལ ret = wait_for_tcf(status);
	waitfor(100);
	ཧྲིལ value = get_qspi_shakti(dr);
	//	printf("Read status register value %08x \n", value);
	reset_interrupt_flags();
	གལ་སྲིད(ret){
		printf("\tRead Status Register Failed\n");
		fail_bit = 1;
		ལོག -1;
	}
	དེ་མིན
		ལོག value;
}

/** @fn int wait_for_wip()
 * @brief Wait till a flash access is complete.
 * @details Reads the WIP bit in the status register to check the completion of flash access.
 * Useful during flash write operations.
 * @return Zero on Success
 */
ཧྲིལ wait_for_wip(void){
	ཧྲིལ status1;
	do{
		//  printf("\t Waiting for Wip \n");
		status1 = flashReadStatusRegister(0x05);
		གལ་སྲིད(check_fail_bit())
			ལོག -1;
		གལ་སྲིད(status1 & 0x0){
			printf("\tQSPI: Programming Error - Diagnose\n");
			ལོག -1;
		}
		waitfor(20000);
	}སྐབས(status1 & 0x01);
	//    printf("\t QSPI: Page Program/Erase Command Successfully Completed\n");
	ལོག 0;
}

/** @fn int micron_write_enable(int status)
 * @brief Enables the micron flash for write operation.
 * @details Enables micron flash for programming flash data.
 * @param int status --- Write enable status.
 * @return Zero on Success
 */
ཧྲིལ micron_write_enable(ཧྲིལ status){
	//  printf("\tWrite Enable\n");
	set_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x06)));
	ཧྲིལ ret = wait_for_tcf(status); //Indicating the completion of command -- Currently polling
	//  printf("Status : %d dcr : %d cr: %d ccr: %d \n",status,*dcr,*cr,*ccr);
	ལོག ret;
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
ཧྲིལ pageProgramSingleSPI(ཧྲིལ value1, ཧྲིལ value2, ཧྲིལ value3, ཧྲིལ value4, ཧྲིལ address){
	གལ་སྲིད(micron_write_enable(status)){
		printf("Panic: Write Enable Command Failed to execute");
		ལོག -1;
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
	ལོག wait_for_wip(); // Function which checks if WIP is done, indicating completion of Page Program
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
ཧྲིལ pageProgramQuadSPI(ཧྲིལ value1, ཧྲིལ value2, ཧྲིལ value3, ཧྲིལ value4, ཧྲིལ address){
	གལ་སྲིད(micron_write_enable(status)){
		printf("Panic: Write Enable Command Failed to execute");
		ལོག -1;
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
	ལོག wait_for_wip(); // Function which checks if WIP is done, indicating completion of Page Program
}

/** @fn int flashIdentificationDevice()
 * @brief Reads flash id code.
 * @details Reads flash identification code from the flash device and checks whether it valid.
 * @return Zero on success else -1
 */
ཧྲིལ flashIdentificationDevice(void){
	log_debug("\tReading the ID register and discovering the Flash Device\n");
	set_qspi_shakti32(dlr,4);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x90)|CCR_ADSIZE(THREEBYTE)|CCR_ADMODE(SINGLE)|CCR_DMODE(SINGLE)));
	set_qspi_shakti32(ar, 0);
	status = 0; // Useless Variable but still!!!!
	ཧྲིལ ret = wait_for_tcf(status);
	ཧྲིལ value = get_qspi_shakti(dr);
	log_info("\t device id %x\n",value);
	reset_interrupt_flags();
	གལ་སྲིད(value == MEM_TYPE_N25Q256_ID){
		printf("\tN25Q256 Device Detected \n");
		ལོག 0;
	}
	དེ་མིན{
		log_fatal("\t Device Not Detected - Diagnose %08x\n",value);
		ལོག -1;
	}
}

/** @fn int flashMemInit()
 * @brief Initialises flash memory 
 * @details Initialises flash device and check for id code.
 * @return Zero on success else -1
 */
ཧྲིལ flashMemInit(){  //Supposedly a set of routines to check if the memory/interface or whatever is proper
	ཧྲིལ ret = flashIdentificationDevice();
	གལ་སྲིད(ret==-1){
		log_fatal("Flash Mem Init Failed -- Quitting Program, Diagnose");
		ལོག ret;
	}
	དེ་མིན log_debug("Flash Mem Init Success\n");
	ལོག 0;
	//to fill in code
}


/** @fn int flashReadFlagRegister()
 * @brief Reads flash read flag. 
 * @details Reads the flash flag register.
 * @warning Not implemented now. Reserve for future.
 */
ཧྲིལ flashReadFlagRegister(void){
	ལོག 0;
}

/** @fn int flashWriteEnable()
 * @brief Enables flash enable bit
 * @details For any write operation into to flash device (erase, program, etc.)
 *        this enable bit needs to be enabled.
 * @return TCF status
 */
ཧྲིལ flashWriteEnable(void){
	printf("\tWrite Enable\n");
	set_qspi_shakti32(ccr,(CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x06)));
	ཧྲིལ ret = wait_for_tcf(0); //Indicating the completion of command -- Currently polling
	reset_interrupt_flags();
	ལོག ret; 
}

/** @fn int flashEnable4ByteAddressingMode()
 * @brief Selects the addressed mode.
 * @details Before accessing flash device, the number of bits used for (Q)SPI needs to be programmed.
 * @return Status of the performed operation; else -1
 */
ཧྲིལ flashEnable4ByteAddressingMode(void){  //Enable 4-byte addressing Mode and read the status to verify that it has happened correctly

	གལ་སྲིད(flashWriteEnable()){
		printf("\t Write Enable Failed \n");
		ལོག -1;
	}
	waitfor(100);
	set_qspi_shakti32(ccr,(CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xB7)));
	//  int status =0; 
	status = 0;
	ཧྲིལ ret = wait_for_tcf(status);
	reset_interrupt_flags();
	waitfor(100);
	//Checking Phase
	status = flashReadStatusRegister();
	printf("\t Status Value: %08x\n",status);
	གལ་སྲིད(status & 1)
		printf("\t 4-Byte Addressing Mode is Enabled\n");
	དེ་མིན
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
ཧྲིལ flashReadSingleSPI(ཧྲིལ dummy_cycles, ཧྲིལ read_address, ཧྲིལ instruction, ཧྲིལ data_words, ཧྲིལ adsize){
	set_qspi_shakti32(dlr,data_words);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(SINGLE)|CCR_DCYC(dummy_cycles)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_ADSIZE(adsize)|CCR_INSTRUCTION(instruction)));
	set_qspi_shakti32(ar,read_address);
	status = 0;
	ཧྲིལ ret = wait_for_tcf(status);
	ཧྲིལ value = get_qspi_shakti(dr);
	printf("\tThe Read Value: %08x\n",value);
	//    printf("\tThe Read Value: %08x\n",value);
	གལ་སྲིད(ret){
		printf("\t Read Value Failed \n");
		ལོག -1;
	}
	reset_interrupt_flags();
	ལོག value;
}

/** @fn int flashReadDualSPI(int address, int data_length)
 * @brief  Reads flash device over two io lines SPI.
 * @details Reads the flash device over two io lines for spi (IO1, IO2, CS, CLK) data
 * @param int address --- Address which needs to be read.
 * @param int data_length --- Number of Data bytes (data_words + 1) needs to be read 
 * @return Status of the performed operation; else -1
 */
ཧྲིལ flashReadDualSPI(ཧྲིལ address, ཧྲིལ data_length){
	set_qspi_shakti32(dlr,data_length); //DLR
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(DOUBLE)|CCR_DCYC(3)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBB)));
	set_qspi_shakti32(ar,address); 
	//    printf("Status : %08x dcr : %08x cr : %08x ccr : %08x dlr: %08x ar: %08x\n",status,*dcr,*cr,*ccr,*dlr,*ar);
	ཧྲིལ ret = wait_for_tcf(status);
	ཧྲིལ value = get_qspi_shakti(dr);
	printf("\tThe Read Value: %08x\n",value);	
	གལ་སྲིད(ret){
		printf("\t QSPI: Read Value failed\n");
		ལོག -1;
	}
	//*config_string = get_qspi_shakti(dr);
	//printf("\t Read Data is %08x\n",read_data);
	reset_interrupt_flags();
	ལོག value;
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
ཧྲིལ flashReadQuadSPI(ཧྲིལ dummy_cycles, ཧྲིལ read_address, ཧྲིལ instruction, ཧྲིལ data_words, ཧྲིལ adsize){
	set_qspi_shakti32(dlr,data_words);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DCYC(dummy_cycles)|CCR_ADSIZE(adsize)|CCR_ADMODE(QUAD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(instruction)));
	set_qspi_shakti32(ar,read_address);
	status = 0;
	ཧྲིལ ret = wait_for_tcf(status);
	ཧྲིལ value_1 = get_qspi_shakti(dr);
	ཧྲིལ value_2 = get_qspi_shakti(dr);
	ཧྲིལ value_3 = get_qspi_shakti(dr);
	ཧྲིལ value_4 = get_qspi_shakti(dr);
	printf("\tThe Read Value: %08x, %08x, %08x and %08x \n",value_1,value_2,value_3,value_4);
	གལ་སྲིད(ret){
		printf("\t Read Value Failed \n");
		ལོག -1; 
	}   
	reset_interrupt_flags();
	ལོག value_1;
}

/** @fn int flashSingleSPIXip(int addr, int* dest_addr) 
 * @brief Reads over single SPI XIP
 * @details Generic Read for xip SPI Read.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on success.
 */
ཧྲིལ flashSingleSPIXip(ཧྲིལ addr, ཧྲིལ* dest_addr){
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
	ལོག 0;
}

/** @fn int flashSingleSPIDDRXip(int addr, int* dest_addr)  
 * @brief Reads over DDR XIP mode.
 * @details Reads for DDR based XIP mode.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
ཧྲིལ flashSingleSPIDDRXip(ཧྲིལ addr, ཧྲིལ* dest_addr){
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
	ལོག 0;
}

/** @fn int flashDualSPIXip(int addr, int* dest_addr)
 * @brief Reads over XIP mode.
 * @details Reads for XIP mode using two io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
ཧྲིལ flashDualSPIXip(ཧྲིལ addr, ཧྲིལ* dest_addr){
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
	ལོག 0;
}

/** @fn int flashDualSPIDDRXip(int addr, int* dest_addr) 
 * @brief Reads over XIP mode.
 * @details Reads for DDR based XIP mode using two io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
ཧྲིལ flashDualSPIDDRXip(ཧྲིལ addr, ཧྲིལ* dest_addr){
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
	ལོག 0;
}

/** @fn int flashWriteVolatileConfigReg(int value) 
 * @brief Writes into flash volatile configuration register.
 * @details Writes the passed value into flash volatile configuration register.
 * @param int value needs to written into Write Volatile Config Register.
 * @return Zero on Success
 */
ཧྲིལ flashWriteVolatileConfigReg(ཧྲིལ value){
	printf("\t Setting Volatile Configuration Register with the Value: %08x\n",value);
	གལ་སྲིད(micron_write_enable(status)){
		printf("Panic: Write Enable Command Failed to execute\n");
		ལོག -1;
	}
	reset_interrupt_flags();
	//	flashReadStatusRegister();
	set_qspi_shakti32(dlr,DL(1));
	set_qspi_shakti8(dr,value);  //The value to be written into the VECR register to enable XIP. Indicating XIP to operate in Quad Mode
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x01)));
	waitfor(50);
	status=0;
	ཧྲིལ ret = wait_for_tcf(status);
	//    printf("Status : %d dcr : %d cr : %d ccr : %d dlr: %d dr: %d\n",status,*dcr,*cr,*ccr,*dlr,*dr);
	reset_interrupt_flags();
	waitfor(50);  //Giving Micron time to store the data
	ལོག ret;
}

/** @fn int flashQuadSPIXip(int addr, int* dest_addr)
 * @brief Reads over XIP mode.
 * @details Reads for DDR based XIP mode using quad io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
ཧྲིལ flashQuadSPIXip(ཧྲིལ addr, ཧྲིལ* dest_addr){
	གལ་སྲིད(flashWriteVolatileConfigReg(0x40404040)){
		printf("\t Volatile Configuration Register not Set -- Diagnose\n");
		ལོག -1;
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
	ལོག 0;
}

/** @fn int flashQuadSPIDDRXip(int addr, int* dest_addr)
 * @brief Reads over XIP mode.
 * @details Reads for DDR based XIP mode using four io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
ཧྲིལ flashQuadSPIDDRXip(ཧྲིལ addr, ཧྲིལ* dest_addr){
	གལ་སྲིད(flashWriteVolatileConfigReg(0x40404040)){
		printf("\t Volatile Configuration Register not Set -- Diagnose\n");
		ལོག -1;
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
	ལོག 0;
}

/** @fn int flash_Write_disable()
 * @brief disables write operation
 * @details Write operation can be possible only after enabling write enable register.
 *       Here this is disabled using this function.
 * @return Zero on Success
 */
ཧྲིལ flash_Write_disable(void){
	printf("\tWrite disable\n");
	set_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x04)));
	ཧྲིལ ret = wait_for_tcf(status); //Indicating the completion of command -- Currently polling
	printf("Status : %d dcr : %d cr: %d ccr: %d \n",status,*dcr,*cr,*ccr);
	reset_interrupt_flags();
	ལོག wait_for_wip();
}

/** @fn int eraseSector(int command, int address)
 * @brief Erases one sector 
 * @details Erases a complete sector which falls in the sector range.
 * @param int command --- Erase command (sector erase, block erase or chip erase)
 * @param int address --- Starting address of erase.
 * @return Zero on Success
 */
ཧྲིལ eraseSector(ཧྲིལ command, ཧྲིལ address){
	གལ་སྲིད(micron_write_enable(status)){
		printf("Panic: Write Enable Command Failed to execute");
		ལོག -1;
	}
	reset_interrupt_flags();
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(command)));
	set_qspi_shakti32(ar,address);
	waitfor(150);
	ཧྲིལ ret = wait_for_tcf(status);
	reset_interrupt_flags();
	ལོག wait_for_wip(); //For sector erase maybe estat should be checked
}

/** @fn int micron_volatile_write_enable(int status) 
 * @brief Enable for volatile write.
 * @details Enables micron flash for programming volatile config. register.
 * @param int --- status register value.
 * @return Zero on Success
 */
ཧྲིལ micron_volatile_write_enable(ཧྲིལ status){
	printf("\tVolatile Write Enable\n");
	set_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x50)));
	ཧྲིལ ret = wait_for_tcf(status); //Indicating the completion of command -- Currently polling
	printf("Status : %d dcr : %d cr: %d ccr: %d \n",status,*dcr,*cr,*ccr);
	ལོག ret;
}

/** @fn int micron_enable_4byte_addressing(int status) 
 * @brief Enables micron flash for 4 byte addressing.
 * @details Address can be passed as 3 bytes or 4 bytes before read or write 
 * operation. This function sets the number of address bytes to 4 bytes.
 * @param int --- status register value
 * @return Zero on Success
 */
ཧྲིལ micron_enable_4byte_addressing(ཧྲིལ status){
	printf("\t Enable 4 byte address \n");
	set_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xB7)));
	ཧྲིལ ret = wait_for_tcf(status); //Indicating the completion of command -- Currently polling
	printf("Status : %d dcr : %d cr: %d ccr: %d \n",status,*dcr,*cr,*ccr);
	ལོག ret;
}

/** @fn int micron_configure_xip_volatile(int status, int value)
 * @brief Configures the xip volatile config. register.
 * @details Configures the volatile config. register for xip Read mode.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
ཧྲིལ micron_configure_xip_volatile(ཧྲིལ status, ཧྲིལ value){
	log_debug("\tWrite Volatile Configuration Register\n");
	set_qspi_shakti32(dlr,DL(1));
	set_qspi_shakti8(dr,value);  //The value to be written into the VECR register to enable XIP. Indicating XIP to operate in Quad Mode
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x81)));
	waitfor(50);
	ཧྲིལ ret = wait_for_tcf(status);
	printf("Status : %d dcr : %d cr : %d ccr : %d dlr: %d dr: %d\n",status,*dcr,*cr,*ccr,*dlr,*dr);
	waitfor(50);  //Giving Micron time to store the data
	ལོག ret;
}

/** @fn int micron_disable_xip_volatile(int status, int value)
 * @brief Configures(disables) the xip volatile config. register.
 * @details Configures(disables) the volatile config. register for xip Read mode.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
ཧྲིལ micron_disable_xip_volatile(ཧྲིལ status, __attribute__ ((unused)) ཧྲིལ value){
	log_debug("\tWrite Volatile Configuration Register to exit XIP\n");
	set_qspi_shakti32(cr,(CR_PRESCALER(0x3)|CR_TOIE|CR_TCIE|CR_TEIE|CR_SMIE|CR_FTIE|CR_ABORT|CR_EN));
	waitfor(30);
	qspi_init(27,0,3,1,15,1);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DUMMY_BIT|CCR_DUMMY_CONFIRMATION|CCR_DCYC(8)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(NDATA)));
	set_qspi_shakti32(ar,0x00000); //Dummy address 
	set_qspi_shakti32(dlr,1);

	ཧྲིལ ret = wait_for_tcf(status);
	ཧྲིལ temp_data = get_qspi_shakti(dr);

	waitfor(50);
	reset_interrupt_flags();
	ལོག ret;
}

/** @fn int micron_read_id_cmd(int status, int value)
 * @brief Reads the id of the micron flash.
 * @details Micron flash is having a fixed value as ID during production. This 
 * value is read to confirm proper flash device.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
ཧྲིལ micron_read_id_cmd(ཧྲིལ status, ཧྲིལ value){
	log_debug("\tRead ID Command to see if the Protocol is Proper\n");
	set_qspi_shakti32(dlr,4);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x9E)|CCR_DMODE(SINGLE)));
	ཧྲིལ ret = wait_for_tcf(status);
	value = get_qspi_shakti(dr);
	printf("Read ID: %08x",value);
	ལོག ret;
}

/** @fn int micron_read_configuration_register(int status, int value)
 * @brief Reads configuration register. 
 * @details The configurartion register is read using this function.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
ཧྲིལ micron_read_configuration_register(ཧྲིལ status, ཧྲིལ value){
	printf("\tRead ID Command to see if the Protocol is Proper\n");
	set_qspi_shakti32(dlr,4);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBE)|CCR_DMODE(SINGLE)));
	ཧྲིལ ret = wait_for_tcf(status);
	value = get_qspi_shakti(dr);
	log_debug("Configuration Register Value: %08x",value);
	ལོག ret;
}
