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

#ଅନ୍ତର୍ଭାଵ "qspi.h"
#ଅନ୍ତର୍ଭାଵ "utils.h"
#ଅନ୍ତର୍ଭାଵ "log.h"
#define MEM_TYPE_N25Q256_ID 0x9d189d18

ଅକ୍ଷର fail_bit = 0;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା status = 0;
/*! Pointer to QSPI registers */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା* cr       =  (ପୂର୍ଣ୍ଣସଂଖ୍ୟା*) CR; /*! Control Register */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା* dcr      =  (ପୂର୍ଣ୍ଣସଂଖ୍ୟା*) DCR; /*! Data Configuration Register */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା* sr       =  (ପୂର୍ଣ୍ଣସଂଖ୍ୟା*) SR; /*! Status Register */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା* fcr      =  (ପୂର୍ଣ୍ଣସଂଖ୍ୟା*) FCR; /* Flag Clear Register */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା* ccr      =  (ପୂର୍ଣ୍ଣସଂଖ୍ୟା*) CCR; /* Commn. Configuration Register */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା* ar       =  (ପୂର୍ଣ୍ଣସଂଖ୍ୟା*) AR; /*! Address Register */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା* abr      =  (ପୂର୍ଣ୍ଣସଂଖ୍ୟା*) ABR; /*! Alternate Bytes Register */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା* dr       =  (ପୂର୍ଣ୍ଣସଂଖ୍ୟା*) DR; /*! Data Register */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା* dlr      =  (ପୂର୍ଣ୍ଣସଂଖ୍ୟା*) DLR; /*! Data Length Register */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା* psmkr    =  (ପୂର୍ଣ୍ଣସଂଖ୍ୟା*) PSMKR; /*! Polling Status Mask Register */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା* pir      =  (ପୂର୍ଣ୍ଣସଂଖ୍ୟା*) PIR; /*! Polling Interval Register */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା* lprt     =  (ପୂର୍ଣ୍ଣସଂଖ୍ୟା*) LPRT; /*! Low power Time Register */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା* startmm  =  (ପୂର୍ଣ୍ଣସଂଖ୍ୟା*) STARTMM; /*! Start Memory Map Register */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା* endmm    =  (ପୂର୍ଣ୍ଣସଂଖ୍ୟା*) ENDMM; /*! End Memory Map Register */

/** @fn void set_qspi_shakti32(int* addr, int val)
 * @brief Writes 32 bit value into QSPI register.
 * @details Writes 32 bit value into passed address QSPI register.
 * @param int* addr --- Addresss where the data (val) needs to be written
 * @param int val ---  Data which needs to be written.
 */
ଶୂନ୍ୟ set_qspi_shakti32(ପୂର୍ଣ୍ଣସଂଖ୍ୟା* addr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା val)
{
	*addr = val;
}

/** @fn void set_qspi_shakti16(int16_t* addr, int16_t val)
 * @brief Writes 16 bit value 
 * @details Writes 16 bit value into 16bit QSPI register 
 * @param 16bit int* addr --- Addresss where the data (val) needs to be written
 * @param 16bit int val ---  Data which needs to be written.
 */
ଶୂନ୍ୟ set_qspi_shakti16(int16_t* addr, int16_t val)
{
	*addr = val;
}

/** @fn void set_qspi_shakti8(char* addr, char val) 
 * @brief Writes 8 bit value.
 * @details Writes 8 bit value into 8 bit qspi register.
 * @param char* addr --- Addresss where the data (val) needs to be written
 * @param char val ---  Data which needs to be written.
 */
ଶୂନ୍ୟ set_qspi_shakti8(ଅକ୍ଷର* addr, ଅକ୍ଷର val)
{
	*addr= val;
}

/** @fn int get_qspi_shakti(int* addr)
 * @brief reads from qspi register
 * @details Reads from the passed QSPI register and returns the value.
 * @param int* addr --- 32 bit Read Addresss  
 * @return Read value -- Read value from the passed value.
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା get_qspi_shakti(ପୂର୍ଣ୍ଣସଂଖ୍ୟା* addr)
{
	ଫେରନ୍ତୁ *addr;
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
ଶୂନ୍ୟ qspi_init(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fsize, ପୂର୍ଣ୍ଣସଂଖ୍ୟା csht, ପୂର୍ଣ୍ଣସଂଖ୍ୟା prescaler, ପୂର୍ଣ୍ଣସଂଖ୍ୟା enable_interrupts, ପୂର୍ଣ୍ଣସଂଖ୍ୟା fthreshold, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ck_mode){
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା int_vector = enable_interrupts? (CR_TOIE|CR_SMIE|CR_FTIE|CR_TCIE|CR_TEIE) : 0; 
	set_qspi_shakti32(dcr,(DCR_FSIZE(fsize)|DCR_CSHT(csht)|DCR_CKMODE(ck_mode))); 
	set_qspi_shakti32(cr,(CR_PRESCALER(prescaler)|int_vector|CR_FTHRES(fthreshold)|CR_EN));
}

/** @fn void reset_interrupt_flags()
 * @brief Resets interrupt flags.
 * @details Before carrying out any flash access operations, the interrupt flags are cleared.
 */
ଶୂନ୍ୟ reset_interrupt_flags(){
	set_qspi_shakti32(fcr,(FCR_CTOF|FCR_CSMF|FCR_CTCF|FCR_CTEF)); //Resetting all the flags
}

/** @fn int wait_for_tcf(int status)
 * @brief Wait for the transfer complete flag.
 * @details WCF bit status register indicates the completion of flash 
 *  operation. The same is cheked here.
 * @param int status register read value.
 * @return Zero on success else -1
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା wait_for_tcf(ପୂର୍ଣ୍ଣସଂଖ୍ୟା status){
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା timeout = DEF_TIMEOUT; 

	status = get_qspi_shakti(sr);

	//    printf("status : %d looping?\n",status);

	ଯେତେବେଳେ(!( status & 0x02 ) && --timeout){
		waitfor(1000);
		status=get_qspi_shakti(sr);
		printf("status: %08x in loop %d \n",status, !(status & 0x02));
	}
	ଯଦି(timeout==0){
		printf("Request Timed out\n");
		ଫେରନ୍ତୁ -1;
	}
	ଫେରନ୍ତୁ 0;
}

/** @fn int check_fail_bit()
 * @brief Checks the value of fail_bit.
 * @details Checks the fail bit whether the value is zero or not.
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା check_fail_bit(ଶୂନ୍ୟ){
	ଯଦି(fail_bit){
		fail_bit = 0;
		ଫେରନ୍ତୁ -1;
	}
	ଅନ୍ୟଥା{
		fail_bit = 0;
		ଫେରନ୍ତୁ 0;
	}
}

/** @fn int flashReadStatusRegister()
 * @brief Reads flash status register
 * @details Reads flash status register contents
 * @return Status register value on success; else -1
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashReadStatusRegister(){
	//    printf("\tReading the Status bits of the Flash\n");
	set_qspi_shakti32(dlr,4);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x05)|CCR_DMODE(SINGLE)));

	status = 0;
	waitfor(1000);
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = wait_for_tcf(status);
	waitfor(100);
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୂଲ୍ୟ = get_qspi_shakti(dr);
	//	printf("Read status register value %08x \n", value);
	reset_interrupt_flags();
	ଯଦି(ret){
		printf("\tRead Status Register Failed\n");
		fail_bit = 1;
		ଫେରନ୍ତୁ -1;
	}
	ଅନ୍ୟଥା
		ଫେରନ୍ତୁ ମୂଲ୍ୟ;
}

/** @fn int wait_for_wip()
 * @brief Wait till a flash access is complete.
 * @details Reads the WIP bit in the status register to check the completion of flash access.
 * Useful during flash write operations.
 * @return Zero on Success
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା wait_for_wip(ଶୂନ୍ୟ){
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା status1;
	କର{
		//  printf("\t Waiting for Wip \n");
		status1 = flashReadStatusRegister(0x05);
		ଯଦି(check_fail_bit())
			ଫେରନ୍ତୁ -1;
		ଯଦି(status1 & 0x0){
			printf("\tQSPI: Programming Error - Diagnose\n");
			ଫେରନ୍ତୁ -1;
		}
		waitfor(20000);
	}ଯେତେବେଳେ(status1 & 0x01);
	//    printf("\t QSPI: Page Program/Erase Command Successfully Completed\n");
	ଫେରନ୍ତୁ 0;
}

/** @fn int micron_write_enable(int status)
 * @brief Enables the micron flash for write operation.
 * @details Enables micron flash for programming flash data.
 * @param int status --- Write enable status.
 * @return Zero on Success
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା micron_write_enable(ପୂର୍ଣ୍ଣସଂଖ୍ୟା status){
	//  printf("\tWrite Enable\n");
	set_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x06)));
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = wait_for_tcf(status); //Indicating the completion of command -- Currently polling
	//  printf("Status : %d dcr : %d cr: %d ccr: %d \n",status,*dcr,*cr,*ccr);
	ଫେରନ୍ତୁ ret;
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
ପୂର୍ଣ୍ଣସଂଖ୍ୟା pageProgramSingleSPI(ପୂର୍ଣ୍ଣସଂଖ୍ୟା value1, ପୂର୍ଣ୍ଣସଂଖ୍ୟା value2, ପୂର୍ଣ୍ଣସଂଖ୍ୟା value3, ପୂର୍ଣ୍ଣସଂଖ୍ୟା value4, ପୂର୍ଣ୍ଣସଂଖ୍ୟା address){
	ଯଦି(micron_write_enable(status)){
		printf("Panic: Write Enable Command Failed to execute");
		ଫେରନ୍ତୁ -1;
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
	ଫେରନ୍ତୁ wait_for_wip(); // Function which checks if WIP is done, indicating completion of Page Program
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
ପୂର୍ଣ୍ଣସଂଖ୍ୟା pageProgramQuadSPI(ପୂର୍ଣ୍ଣସଂଖ୍ୟା value1, ପୂର୍ଣ୍ଣସଂଖ୍ୟା value2, ପୂର୍ଣ୍ଣସଂଖ୍ୟା value3, ପୂର୍ଣ୍ଣସଂଖ୍ୟା value4, ପୂର୍ଣ୍ଣସଂଖ୍ୟା address){
	ଯଦି(micron_write_enable(status)){
		printf("Panic: Write Enable Command Failed to execute");
		ଫେରନ୍ତୁ -1;
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
	ଫେରନ୍ତୁ wait_for_wip(); // Function which checks if WIP is done, indicating completion of Page Program
}

/** @fn int flashIdentificationDevice()
 * @brief Reads flash id code.
 * @details Reads flash identification code from the flash device and checks whether it valid.
 * @return Zero on success else -1
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashIdentificationDevice(ଶୂନ୍ୟ){
	log_debug("\tReading the ID register and discovering the Flash Device\n");
	set_qspi_shakti32(dlr,4);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x90)|CCR_ADSIZE(THREEBYTE)|CCR_ADMODE(SINGLE)|CCR_DMODE(SINGLE)));
	set_qspi_shakti32(ar, 0);
	status = 0; // Useless Variable but still!!!!
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = wait_for_tcf(status);
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୂଲ୍ୟ = get_qspi_shakti(dr);
	log_info("\t device id %x\n",ମୂଲ୍ୟ);
	reset_interrupt_flags();
	ଯଦି(ମୂଲ୍ୟ == MEM_TYPE_N25Q256_ID){
		printf("\tN25Q256 Device Detected \n");
		ଫେରନ୍ତୁ 0;
	}
	ଅନ୍ୟଥା{
		log_fatal("\t Device Not Detected - Diagnose %08x\n",ମୂଲ୍ୟ);
		ଫେରନ୍ତୁ -1;
	}
}

/** @fn int flashMemInit()
 * @brief Initialises flash memory 
 * @details Initialises flash device and check for id code.
 * @return Zero on success else -1
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashMemInit(){  //Supposedly a set of routines to check if the memory/interface or whatever is proper
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = flashIdentificationDevice();
	ଯଦି(ret==-1){
		log_fatal("Flash Mem Init Failed -- Quitting Program, Diagnose");
		ଫେରନ୍ତୁ ret;
	}
	ଅନ୍ୟଥା log_debug("Flash Mem Init Success\n");
	ଫେରନ୍ତୁ 0;
	//to fill in code
}


/** @fn int flashReadFlagRegister()
 * @brief Reads flash read flag. 
 * @details Reads the flash flag register.
 * @warning Not implemented now. Reserve for future.
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashReadFlagRegister(ଶୂନ୍ୟ){
	ଫେରନ୍ତୁ 0;
}

/** @fn int flashWriteEnable()
 * @brief Enables flash enable bit
 * @details For any write operation into to flash device (erase, program, etc.)
 *        this enable bit needs to be enabled.
 * @return TCF status
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashWriteEnable(ଶୂନ୍ୟ){
	printf("\tWrite Enable\n");
	set_qspi_shakti32(ccr,(CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x06)));
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = wait_for_tcf(0); //Indicating the completion of command -- Currently polling
	reset_interrupt_flags();
	ଫେରନ୍ତୁ ret; 
}

/** @fn int flashEnable4ByteAddressingMode()
 * @brief Selects the addressed mode.
 * @details Before accessing flash device, the number of bits used for (Q)SPI needs to be programmed.
 * @return Status of the performed operation; else -1
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashEnable4ByteAddressingMode(ଶୂନ୍ୟ){  //Enable 4-byte addressing Mode and read the status to verify that it has happened correctly

	ଯଦି(flashWriteEnable()){
		printf("\t Write Enable Failed \n");
		ଫେରନ୍ତୁ -1;
	}
	waitfor(100);
	set_qspi_shakti32(ccr,(CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xB7)));
	//  int status =0; 
	status = 0;
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = wait_for_tcf(status);
	reset_interrupt_flags();
	waitfor(100);
	//Checking Phase
	status = flashReadStatusRegister();
	printf("\t Status Value: %08x\n",status);
	ଯଦି(status & 1)
		printf("\t 4-Byte Addressing Mode is Enabled\n");
	ଅନ୍ୟଥା
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
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashReadSingleSPI(ପୂର୍ଣ୍ଣସଂଖ୍ୟା dummy_cycles, ପୂର୍ଣ୍ଣସଂଖ୍ୟା read_address, ପୂର୍ଣ୍ଣସଂଖ୍ୟା instruction, ପୂର୍ଣ୍ଣସଂଖ୍ୟା data_ଶବ୍ଦଗୁଡ଼ିକ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା adsize){
	set_qspi_shakti32(dlr,data_ଶବ୍ଦଗୁଡ଼ିକ);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(SINGLE)|CCR_DCYC(dummy_cycles)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_ADSIZE(adsize)|CCR_INSTRUCTION(instruction)));
	set_qspi_shakti32(ar,read_address);
	status = 0;
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = wait_for_tcf(status);
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୂଲ୍ୟ = get_qspi_shakti(dr);
	printf("\tThe Read Value: %08x\n",ମୂଲ୍ୟ);
	//    printf("\tThe Read Value: %08x\n",value);
	ଯଦି(ret){
		printf("\t Read Value Failed \n");
		ଫେରନ୍ତୁ -1;
	}
	reset_interrupt_flags();
	ଫେରନ୍ତୁ ମୂଲ୍ୟ;
}

/** @fn int flashReadDualSPI(int address, int data_length)
 * @brief  Reads flash device over two io lines SPI.
 * @details Reads the flash device over two io lines for spi (IO1, IO2, CS, CLK) data
 * @param int address --- Address which needs to be read.
 * @param int data_length --- Number of Data bytes (data_words + 1) needs to be read 
 * @return Status of the performed operation; else -1
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashReadDualSPI(ପୂର୍ଣ୍ଣସଂଖ୍ୟା address, ପୂର୍ଣ୍ଣସଂଖ୍ୟା data_length){
	set_qspi_shakti32(dlr,data_length); //DLR
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(DOUBLE)|CCR_DCYC(3)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBB)));
	set_qspi_shakti32(ar,address); 
	//    printf("Status : %08x dcr : %08x cr : %08x ccr : %08x dlr: %08x ar: %08x\n",status,*dcr,*cr,*ccr,*dlr,*ar);
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = wait_for_tcf(status);
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୂଲ୍ୟ = get_qspi_shakti(dr);
	printf("\tThe Read Value: %08x\n",ମୂଲ୍ୟ);	
	ଯଦି(ret){
		printf("\t QSPI: Read Value failed\n");
		ଫେରନ୍ତୁ -1;
	}
	//*config_string = get_qspi_shakti(dr);
	//printf("\t Read Data is %08x\n",read_data);
	reset_interrupt_flags();
	ଫେରନ୍ତୁ ମୂଲ୍ୟ;
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
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashReadQuadSPI(ପୂର୍ଣ୍ଣସଂଖ୍ୟା dummy_cycles, ପୂର୍ଣ୍ଣସଂଖ୍ୟା read_address, ପୂର୍ଣ୍ଣସଂଖ୍ୟା instruction, ପୂର୍ଣ୍ଣସଂଖ୍ୟା data_ଶବ୍ଦଗୁଡ଼ିକ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା adsize){
	set_qspi_shakti32(dlr,data_ଶବ୍ଦଗୁଡ଼ିକ);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DCYC(dummy_cycles)|CCR_ADSIZE(adsize)|CCR_ADMODE(QUAD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(instruction)));
	set_qspi_shakti32(ar,read_address);
	status = 0;
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = wait_for_tcf(status);
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୂଲ୍ୟ_1 = get_qspi_shakti(dr);
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୂଲ୍ୟ_2_2 = get_qspi_shakti(dr);
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୂଲ୍ୟ_3 = get_qspi_shakti(dr);
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୂଲ୍ୟ_4 = get_qspi_shakti(dr);
	printf("\tThe Read Value: %08x, %08x, %08x and %08x \n",ମୂଲ୍ୟ_1,ମୂଲ୍ୟ_2_2,ମୂଲ୍ୟ_3,ମୂଲ୍ୟ_4);
	ଯଦି(ret){
		printf("\t Read Value Failed \n");
		ଫେରନ୍ତୁ -1; 
	}   
	reset_interrupt_flags();
	ଫେରନ୍ତୁ ମୂଲ୍ୟ_1;
}

/** @fn int flashSingleSPIXip(int addr, int* dest_addr) 
 * @brief Reads over single SPI XIP
 * @details Generic Read for xip SPI Read.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on success.
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashSingleSPIXip(ପୂର୍ଣ୍ଣସଂଖ୍ୟା addr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା* dest_addr){
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
	ଫେରନ୍ତୁ 0;
}

/** @fn int flashSingleSPIDDRXip(int addr, int* dest_addr)  
 * @brief Reads over DDR XIP mode.
 * @details Reads for DDR based XIP mode.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashSingleSPIDDRXip(ପୂର୍ଣ୍ଣସଂଖ୍ୟା addr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା* dest_addr){
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
	ଫେରନ୍ତୁ 0;
}

/** @fn int flashDualSPIXip(int addr, int* dest_addr)
 * @brief Reads over XIP mode.
 * @details Reads for XIP mode using two io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashDualSPIXip(ପୂର୍ଣ୍ଣସଂଖ୍ୟା addr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା* dest_addr){
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
	ଫେରନ୍ତୁ 0;
}

/** @fn int flashDualSPIDDRXip(int addr, int* dest_addr) 
 * @brief Reads over XIP mode.
 * @details Reads for DDR based XIP mode using two io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashDualSPIDDRXip(ପୂର୍ଣ୍ଣସଂଖ୍ୟା addr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା* dest_addr){
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
	ଫେରନ୍ତୁ 0;
}

/** @fn int flashWriteVolatileConfigReg(int value) 
 * @brief Writes into flash volatile configuration register.
 * @details Writes the passed value into flash volatile configuration register.
 * @param int value needs to written into Write Volatile Config Register.
 * @return Zero on Success
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashWriteVolatileConfigReg(ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୂଲ୍ୟ){
	printf("\t Setting Volatile Configuration Register with the Value: %08x\n",ମୂଲ୍ୟ);
	ଯଦି(micron_write_enable(status)){
		printf("Panic: Write Enable Command Failed to execute\n");
		ଫେରନ୍ତୁ -1;
	}
	reset_interrupt_flags();
	//	flashReadStatusRegister();
	set_qspi_shakti32(dlr,DL(1));
	set_qspi_shakti8(dr,ମୂଲ୍ୟ);  //The value to be written into the VECR register to enable XIP. Indicating XIP to operate in Quad Mode
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x01)));
	waitfor(50);
	status=0;
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = wait_for_tcf(status);
	//    printf("Status : %d dcr : %d cr : %d ccr : %d dlr: %d dr: %d\n",status,*dcr,*cr,*ccr,*dlr,*dr);
	reset_interrupt_flags();
	waitfor(50);  //Giving Micron time to store the data
	ଫେରନ୍ତୁ ret;
}

/** @fn int flashQuadSPIXip(int addr, int* dest_addr)
 * @brief Reads over XIP mode.
 * @details Reads for DDR based XIP mode using quad io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashQuadSPIXip(ପୂର୍ଣ୍ଣସଂଖ୍ୟା addr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା* dest_addr){
	ଯଦି(flashWriteVolatileConfigReg(0x40404040)){
		printf("\t Volatile Configuration Register not Set -- Diagnose\n");
		ଫେରନ୍ତୁ -1;
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
	ଫେରନ୍ତୁ 0;
}

/** @fn int flashQuadSPIDDRXip(int addr, int* dest_addr)
 * @brief Reads over XIP mode.
 * @details Reads for DDR based XIP mode using four io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flashQuadSPIDDRXip(ପୂର୍ଣ୍ଣସଂଖ୍ୟା addr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା* dest_addr){
	ଯଦି(flashWriteVolatileConfigReg(0x40404040)){
		printf("\t Volatile Configuration Register not Set -- Diagnose\n");
		ଫେରନ୍ତୁ -1;
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
	ଫେରନ୍ତୁ 0;
}

/** @fn int flash_Write_disable()
 * @brief disables write operation
 * @details Write operation can be possible only after enabling write enable register.
 *       Here this is disabled using this function.
 * @return Zero on Success
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା flash_Write_disable(ଶୂନ୍ୟ){
	printf("\tWrite disable\n");
	set_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x04)));
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = wait_for_tcf(status); //Indicating the completion of command -- Currently polling
	printf("Status : %d dcr : %d cr: %d ccr: %d \n",status,*dcr,*cr,*ccr);
	reset_interrupt_flags();
	ଫେରନ୍ତୁ wait_for_wip();
}

/** @fn int eraseSector(int command, int address)
 * @brief Erases one sector 
 * @details Erases a complete sector which falls in the sector range.
 * @param int command --- Erase command (sector erase, block erase or chip erase)
 * @param int address --- Starting address of erase.
 * @return Zero on Success
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା eraseSector(ପୂର୍ଣ୍ଣସଂଖ୍ୟା command, ପୂର୍ଣ୍ଣସଂଖ୍ୟା address){
	ଯଦି(micron_write_enable(status)){
		printf("Panic: Write Enable Command Failed to execute");
		ଫେରନ୍ତୁ -1;
	}
	reset_interrupt_flags();
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(command)));
	set_qspi_shakti32(ar,address);
	waitfor(150);
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = wait_for_tcf(status);
	reset_interrupt_flags();
	ଫେରନ୍ତୁ wait_for_wip(); //For sector erase maybe estat should be checked
}

/** @fn int micron_volatile_write_enable(int status) 
 * @brief Enable for volatile write.
 * @details Enables micron flash for programming volatile config. register.
 * @param int --- status register value.
 * @return Zero on Success
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା micron_volatile_write_enable(ପୂର୍ଣ୍ଣସଂଖ୍ୟା status){
	printf("\tVolatile Write Enable\n");
	set_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x50)));
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = wait_for_tcf(status); //Indicating the completion of command -- Currently polling
	printf("Status : %d dcr : %d cr: %d ccr: %d \n",status,*dcr,*cr,*ccr);
	ଫେରନ୍ତୁ ret;
}

/** @fn int micron_enable_4byte_addressing(int status) 
 * @brief Enables micron flash for 4 byte addressing.
 * @details Address can be passed as 3 bytes or 4 bytes before read or write 
 * operation. This function sets the number of address bytes to 4 bytes.
 * @param int --- status register value
 * @return Zero on Success
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା micron_enable_4byte_addressing(ପୂର୍ଣ୍ଣସଂଖ୍ୟା status){
	printf("\t Enable 4 byte address \n");
	set_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xB7)));
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = wait_for_tcf(status); //Indicating the completion of command -- Currently polling
	printf("Status : %d dcr : %d cr: %d ccr: %d \n",status,*dcr,*cr,*ccr);
	ଫେରନ୍ତୁ ret;
}

/** @fn int micron_configure_xip_volatile(int status, int value)
 * @brief Configures the xip volatile config. register.
 * @details Configures the volatile config. register for xip Read mode.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା micron_configure_xip_volatile(ପୂର୍ଣ୍ଣସଂଖ୍ୟା status, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୂଲ୍ୟ){
	log_debug("\tWrite Volatile Configuration Register\n");
	set_qspi_shakti32(dlr,DL(1));
	set_qspi_shakti8(dr,ମୂଲ୍ୟ);  //The value to be written into the VECR register to enable XIP. Indicating XIP to operate in Quad Mode
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x81)));
	waitfor(50);
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = wait_for_tcf(status);
	printf("Status : %d dcr : %d cr : %d ccr : %d dlr: %d dr: %d\n",status,*dcr,*cr,*ccr,*dlr,*dr);
	waitfor(50);  //Giving Micron time to store the data
	ଫେରନ୍ତୁ ret;
}

/** @fn int micron_disable_xip_volatile(int status, int value)
 * @brief Configures(disables) the xip volatile config. register.
 * @details Configures(disables) the volatile config. register for xip Read mode.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା micron_disable_xip_volatile(ପୂର୍ଣ୍ଣସଂଖ୍ୟା status, __attribute__ ((unused)) ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୂଲ୍ୟ){
	log_debug("\tWrite Volatile Configuration Register to exit XIP\n");
	set_qspi_shakti32(cr,(CR_PRESCALER(0x3)|CR_TOIE|CR_TCIE|CR_TEIE|CR_SMIE|CR_FTIE|CR_ABORT|CR_EN));
	waitfor(30);
	qspi_init(27,0,3,1,15,1);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DUMMY_BIT|CCR_DUMMY_CONFIRMATION|CCR_DCYC(8)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(NDATA)));
	set_qspi_shakti32(ar,0x00000); //Dummy address 
	set_qspi_shakti32(dlr,1);

	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = wait_for_tcf(status);
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା temp_data = get_qspi_shakti(dr);

	waitfor(50);
	reset_interrupt_flags();
	ଫେରନ୍ତୁ ret;
}

/** @fn int micron_read_id_cmd(int status, int value)
 * @brief Reads the id of the micron flash.
 * @details Micron flash is having a fixed value as ID during production. This 
 * value is read to confirm proper flash device.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା micron_read_id_cmd(ପୂର୍ଣ୍ଣସଂଖ୍ୟା status, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୂଲ୍ୟ){
	log_debug("\tRead ID Command to see if the Protocol is Proper\n");
	set_qspi_shakti32(dlr,4);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x9E)|CCR_DMODE(SINGLE)));
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = wait_for_tcf(status);
	ମୂଲ୍ୟ = get_qspi_shakti(dr);
	printf("Read ID: %08x",ମୂଲ୍ୟ);
	ଫେରନ୍ତୁ ret;
}

/** @fn int micron_read_configuration_register(int status, int value)
 * @brief Reads configuration register. 
 * @details The configurartion register is read using this function.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା micron_read_configuration_register(ପୂର୍ଣ୍ଣସଂଖ୍ୟା status, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୂଲ୍ୟ){
	printf("\tRead ID Command to see if the Protocol is Proper\n");
	set_qspi_shakti32(dlr,4);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBE)|CCR_DMODE(SINGLE)));
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = wait_for_tcf(status);
	ମୂଲ୍ୟ = get_qspi_shakti(dr);
	log_debug("Configuration Register Value: %08x",ମୂଲ୍ୟ);
	ଫେରନ୍ତୁ ret;
}
