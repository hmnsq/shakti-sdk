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

#અન્તર્ભાવ "qspi.h"
#અન્તર્ભાવ "utils.h"
#અન્તર્ભાવ "log.h"
#define MEM_TYPE_N25Q256_ID 0x9d189d18

અક્ષર fail_bit = 0;
પૂર્ણાંક status = 0;
/*! Pointer to QSPI registers */
પૂર્ણાંક* cr       =  (પૂર્ણાંક*) CR; /*! Control Register */
પૂર્ણાંક* dcr      =  (પૂર્ણાંક*) DCR; /*! Data Configuration Register */
પૂર્ણાંક* sr       =  (પૂર્ણાંક*) SR; /*! Status Register */
પૂર્ણાંક* fcr      =  (પૂર્ણાંક*) FCR; /* Flag Clear Register */
પૂર્ણાંક* ccr      =  (પૂર્ણાંક*) CCR; /* Commn. Configuration Register */
પૂર્ણાંક* ar       =  (પૂર્ણાંક*) AR; /*! Address Register */
પૂર્ણાંક* abr      =  (પૂર્ણાંક*) ABR; /*! Alternate Bytes Register */
પૂર્ણાંક* dr       =  (પૂર્ણાંક*) DR; /*! Data Register */
પૂર્ણાંક* dlr      =  (પૂર્ણાંક*) DLR; /*! Data Length Register */
પૂર્ણાંક* psmkr    =  (પૂર્ણાંક*) PSMKR; /*! Polling Status Mask Register */
પૂર્ણાંક* pir      =  (પૂર્ણાંક*) PIR; /*! Polling Interval Register */
પૂર્ણાંક* lprt     =  (પૂર્ણાંક*) LPRT; /*! Low power Time Register */
પૂર્ણાંક* startmm  =  (પૂર્ણાંક*) STARTMM; /*! Start Memory Map Register */
પૂર્ણાંક* endmm    =  (પૂર્ણાંક*) ENDMM; /*! End Memory Map Register */

/** @fn void set_qspi_shakti32(int* addr, int val)
 * @brief Writes 32 bit value into QSPI register.
 * @details Writes 32 bit value into passed address QSPI register.
 * @param int* addr --- Addresss where the data (val) needs to be written
 * @param int val ---  Data which needs to be written.
 */
શૂન્ય set_qspi_shakti32(પૂર્ણાંક* addr, પૂર્ણાંક val)
{
	*addr = val;
}

/** @fn void set_qspi_shakti16(int16_t* addr, int16_t val)
 * @brief Writes 16 bit value 
 * @details Writes 16 bit value into 16bit QSPI register 
 * @param 16bit int* addr --- Addresss where the data (val) needs to be written
 * @param 16bit int val ---  Data which needs to be written.
 */
શૂન્ય set_qspi_shakti16(int16_t* addr, int16_t val)
{
	*addr = val;
}

/** @fn void set_qspi_shakti8(char* addr, char val) 
 * @brief Writes 8 bit value.
 * @details Writes 8 bit value into 8 bit qspi register.
 * @param char* addr --- Addresss where the data (val) needs to be written
 * @param char val ---  Data which needs to be written.
 */
શૂન્ય set_qspi_shakti8(અક્ષર* addr, અક્ષર val)
{
	*addr= val;
}

/** @fn int get_qspi_shakti(int* addr)
 * @brief reads from qspi register
 * @details Reads from the passed QSPI register and returns the value.
 * @param int* addr --- 32 bit Read Addresss  
 * @return Read value -- Read value from the passed value.
 */
પૂર્ણાંક get_qspi_shakti(પૂર્ણાંક* addr)
{
	પાછા *addr;
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
શૂન્ય qspi_init(પૂર્ણાંક fsize, પૂર્ણાંક csht, પૂર્ણાંક prescaler, પૂર્ણાંક enable_interrupts, પૂર્ણાંક fthreshold, પૂર્ણાંક ck_mode){
	પૂર્ણાંક int_vector = enable_interrupts? (CR_TOIE|CR_SMIE|CR_FTIE|CR_TCIE|CR_TEIE) : 0; 
	set_qspi_shakti32(dcr,(DCR_FSIZE(fsize)|DCR_CSHT(csht)|DCR_CKMODE(ck_mode))); 
	set_qspi_shakti32(cr,(CR_PRESCALER(prescaler)|int_vector|CR_FTHRES(fthreshold)|CR_EN));
}

/** @fn void reset_interrupt_flags()
 * @brief Resets interrupt flags.
 * @details Before carrying out any flash access operations, the interrupt flags are cleared.
 */
શૂન્ય reset_interrupt_flags(){
	set_qspi_shakti32(fcr,(FCR_CTOF|FCR_CSMF|FCR_CTCF|FCR_CTEF)); //Resetting all the flags
}

/** @fn int wait_for_tcf(int status)
 * @brief Wait for the transfer complete flag.
 * @details WCF bit status register indicates the completion of flash 
 *  operation. The same is cheked here.
 * @param int status register read value.
 * @return Zero on success else -1
 */
પૂર્ણાંક wait_for_tcf(પૂર્ણાંક status){
	પૂર્ણાંક timeout = DEF_TIMEOUT; 

	status = get_qspi_shakti(sr);

	//    printf("status : %d looping?\n",status);

	જ્યારે(!( status & 0x02 ) && --timeout){
		waitfor(1000);
		status=get_qspi_shakti(sr);
		printf("status: %08x in loop %d \n",status, !(status & 0x02));
	}
	જો(timeout==0){
		printf("Request Timed out\n");
		પાછા -1;
	}
	પાછા 0;
}

/** @fn int check_fail_bit()
 * @brief Checks the value of fail_bit.
 * @details Checks the fail bit whether the value is zero or not.
 */
પૂર્ણાંક check_fail_bit(શૂન્ય){
	જો(fail_bit){
		fail_bit = 0;
		પાછા -1;
	}
	નહીંતર{
		fail_bit = 0;
		પાછા 0;
	}
}

/** @fn int flashReadStatusRegister()
 * @brief Reads flash status register
 * @details Reads flash status register contents
 * @return Status register value on success; else -1
 */
પૂર્ણાંક flashReadStatusRegister(){
	//    printf("\tReading the Status bits of the Flash\n");
	set_qspi_shakti32(dlr,4);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x05)|CCR_DMODE(SINGLE)));

	status = 0;
	waitfor(1000);
	પૂર્ણાંક ret = wait_for_tcf(status);
	waitfor(100);
	પૂર્ણાંક કિંમત = get_qspi_shakti(dr);
	//	printf("Read status register value %08x \n", value);
	reset_interrupt_flags();
	જો(ret){
		printf("\tRead Status Register Failed\n");
		fail_bit = 1;
		પાછા -1;
	}
	નહીંતર
		પાછા કિંમત;
}

/** @fn int wait_for_wip()
 * @brief Wait till a flash access is complete.
 * @details Reads the WIP bit in the status register to check the completion of flash access.
 * Useful during flash write operations.
 * @return Zero on Success
 */
પૂર્ણાંક wait_for_wip(શૂન્ય){
	પૂર્ણાંક status1;
	કરો{
		//  printf("\t Waiting for Wip \n");
		status1 = flashReadStatusRegister(0x05);
		જો(check_fail_bit())
			પાછા -1;
		જો(status1 & 0x0){
			printf("\tQSPI: Programming Error - Diagnose\n");
			પાછા -1;
		}
		waitfor(20000);
	}જ્યારે(status1 & 0x01);
	//    printf("\t QSPI: Page Program/Erase Command Successfully Completed\n");
	પાછા 0;
}

/** @fn int micron_write_enable(int status)
 * @brief Enables the micron flash for write operation.
 * @details Enables micron flash for programming flash data.
 * @param int status --- Write enable status.
 * @return Zero on Success
 */
પૂર્ણાંક micron_write_enable(પૂર્ણાંક status){
	//  printf("\tWrite Enable\n");
	set_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x06)));
	પૂર્ણાંક ret = wait_for_tcf(status); //Indicating the completion of command -- Currently polling
	//  printf("Status : %d dcr : %d cr: %d ccr: %d \n",status,*dcr,*cr,*ccr);
	પાછા ret;
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
પૂર્ણાંક pageProgramSingleSPI(પૂર્ણાંક value1, પૂર્ણાંક value2, પૂર્ણાંક value3, પૂર્ણાંક value4, પૂર્ણાંક address){
	જો(micron_write_enable(status)){
		printf("Panic: Write Enable Command Failed to execute");
		પાછા -1;
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
	પાછા wait_for_wip(); // Function which checks if WIP is done, indicating completion of Page Program
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
પૂર્ણાંક pageProgramQuadSPI(પૂર્ણાંક value1, પૂર્ણાંક value2, પૂર્ણાંક value3, પૂર્ણાંક value4, પૂર્ણાંક address){
	જો(micron_write_enable(status)){
		printf("Panic: Write Enable Command Failed to execute");
		પાછા -1;
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
	પાછા wait_for_wip(); // Function which checks if WIP is done, indicating completion of Page Program
}

/** @fn int flashIdentificationDevice()
 * @brief Reads flash id code.
 * @details Reads flash identification code from the flash device and checks whether it valid.
 * @return Zero on success else -1
 */
પૂર્ણાંક flashIdentificationDevice(શૂન્ય){
	log_debug("\tReading the ID register and discovering the Flash Device\n");
	set_qspi_shakti32(dlr,4);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x90)|CCR_ADSIZE(THREEBYTE)|CCR_ADMODE(SINGLE)|CCR_DMODE(SINGLE)));
	set_qspi_shakti32(ar, 0);
	status = 0; // Useless Variable but still!!!!
	પૂર્ણાંક ret = wait_for_tcf(status);
	પૂર્ણાંક કિંમત = get_qspi_shakti(dr);
	log_info("\t device id %x\n",કિંમત);
	reset_interrupt_flags();
	જો(કિંમત == MEM_TYPE_N25Q256_ID){
		printf("\tN25Q256 Device Detected \n");
		પાછા 0;
	}
	નહીંતર{
		log_fatal("\t Device Not Detected - Diagnose %08x\n",કિંમત);
		પાછા -1;
	}
}

/** @fn int flashMemInit()
 * @brief Initialises flash memory 
 * @details Initialises flash device and check for id code.
 * @return Zero on success else -1
 */
પૂર્ણાંક flashMemInit(){  //Supposedly a set of routines to check if the memory/interface or whatever is proper
	પૂર્ણાંક ret = flashIdentificationDevice();
	જો(ret==-1){
		log_fatal("Flash Mem Init Failed -- Quitting Program, Diagnose");
		પાછા ret;
	}
	નહીંતર log_debug("Flash Mem Init Success\n");
	પાછા 0;
	//to fill in code
}


/** @fn int flashReadFlagRegister()
 * @brief Reads flash read flag. 
 * @details Reads the flash flag register.
 * @warning Not implemented now. Reserve for future.
 */
પૂર્ણાંક flashReadFlagRegister(શૂન્ય){
	પાછા 0;
}

/** @fn int flashWriteEnable()
 * @brief Enables flash enable bit
 * @details For any write operation into to flash device (erase, program, etc.)
 *        this enable bit needs to be enabled.
 * @return TCF status
 */
પૂર્ણાંક flashWriteEnable(શૂન્ય){
	printf("\tWrite Enable\n");
	set_qspi_shakti32(ccr,(CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x06)));
	પૂર્ણાંક ret = wait_for_tcf(0); //Indicating the completion of command -- Currently polling
	reset_interrupt_flags();
	પાછા ret; 
}

/** @fn int flashEnable4ByteAddressingMode()
 * @brief Selects the addressed mode.
 * @details Before accessing flash device, the number of bits used for (Q)SPI needs to be programmed.
 * @return Status of the performed operation; else -1
 */
પૂર્ણાંક flashEnable4ByteAddressingMode(શૂન્ય){  //Enable 4-byte addressing Mode and read the status to verify that it has happened correctly

	જો(flashWriteEnable()){
		printf("\t Write Enable Failed \n");
		પાછા -1;
	}
	waitfor(100);
	set_qspi_shakti32(ccr,(CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xB7)));
	//  int status =0; 
	status = 0;
	પૂર્ણાંક ret = wait_for_tcf(status);
	reset_interrupt_flags();
	waitfor(100);
	//Checking Phase
	status = flashReadStatusRegister();
	printf("\t Status Value: %08x\n",status);
	જો(status & 1)
		printf("\t 4-Byte Addressing Mode is Enabled\n");
	નહીંતર
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
પૂર્ણાંક flashReadSingleSPI(પૂર્ણાંક dummy_cycles, પૂર્ણાંક read_address, પૂર્ણાંક instruction, પૂર્ણાંક data_શબ્દો, પૂર્ણાંક adsize){
	set_qspi_shakti32(dlr,data_શબ્દો);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(SINGLE)|CCR_DCYC(dummy_cycles)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_ADSIZE(adsize)|CCR_INSTRUCTION(instruction)));
	set_qspi_shakti32(ar,read_address);
	status = 0;
	પૂર્ણાંક ret = wait_for_tcf(status);
	પૂર્ણાંક કિંમત = get_qspi_shakti(dr);
	printf("\tThe Read Value: %08x\n",કિંમત);
	//    printf("\tThe Read Value: %08x\n",value);
	જો(ret){
		printf("\t Read Value Failed \n");
		પાછા -1;
	}
	reset_interrupt_flags();
	પાછા કિંમત;
}

/** @fn int flashReadDualSPI(int address, int data_length)
 * @brief  Reads flash device over two io lines SPI.
 * @details Reads the flash device over two io lines for spi (IO1, IO2, CS, CLK) data
 * @param int address --- Address which needs to be read.
 * @param int data_length --- Number of Data bytes (data_words + 1) needs to be read 
 * @return Status of the performed operation; else -1
 */
પૂર્ણાંક flashReadDualSPI(પૂર્ણાંક address, પૂર્ણાંક data_length){
	set_qspi_shakti32(dlr,data_length); //DLR
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(DOUBLE)|CCR_DCYC(3)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBB)));
	set_qspi_shakti32(ar,address); 
	//    printf("Status : %08x dcr : %08x cr : %08x ccr : %08x dlr: %08x ar: %08x\n",status,*dcr,*cr,*ccr,*dlr,*ar);
	પૂર્ણાંક ret = wait_for_tcf(status);
	પૂર્ણાંક કિંમત = get_qspi_shakti(dr);
	printf("\tThe Read Value: %08x\n",કિંમત);	
	જો(ret){
		printf("\t QSPI: Read Value failed\n");
		પાછા -1;
	}
	//*config_string = get_qspi_shakti(dr);
	//printf("\t Read Data is %08x\n",read_data);
	reset_interrupt_flags();
	પાછા કિંમત;
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
પૂર્ણાંક flashReadQuadSPI(પૂર્ણાંક dummy_cycles, પૂર્ણાંક read_address, પૂર્ણાંક instruction, પૂર્ણાંક data_શબ્દો, પૂર્ણાંક adsize){
	set_qspi_shakti32(dlr,data_શબ્દો);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DCYC(dummy_cycles)|CCR_ADSIZE(adsize)|CCR_ADMODE(QUAD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(instruction)));
	set_qspi_shakti32(ar,read_address);
	status = 0;
	પૂર્ણાંક ret = wait_for_tcf(status);
	પૂર્ણાંક કિંમત_1 = get_qspi_shakti(dr);
	પૂર્ણાંક કિંમત_2_2 = get_qspi_shakti(dr);
	પૂર્ણાંક કિંમત_3 = get_qspi_shakti(dr);
	પૂર્ણાંક કિંમત_4 = get_qspi_shakti(dr);
	printf("\tThe Read Value: %08x, %08x, %08x and %08x \n",કિંમત_1,કિંમત_2_2,કિંમત_3,કિંમત_4);
	જો(ret){
		printf("\t Read Value Failed \n");
		પાછા -1; 
	}   
	reset_interrupt_flags();
	પાછા કિંમત_1;
}

/** @fn int flashSingleSPIXip(int addr, int* dest_addr) 
 * @brief Reads over single SPI XIP
 * @details Generic Read for xip SPI Read.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on success.
 */
પૂર્ણાંક flashSingleSPIXip(પૂર્ણાંક addr, પૂર્ણાંક* dest_addr){
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
	પાછા 0;
}

/** @fn int flashSingleSPIDDRXip(int addr, int* dest_addr)  
 * @brief Reads over DDR XIP mode.
 * @details Reads for DDR based XIP mode.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
પૂર્ણાંક flashSingleSPIDDRXip(પૂર્ણાંક addr, પૂર્ણાંક* dest_addr){
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
	પાછા 0;
}

/** @fn int flashDualSPIXip(int addr, int* dest_addr)
 * @brief Reads over XIP mode.
 * @details Reads for XIP mode using two io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
પૂર્ણાંક flashDualSPIXip(પૂર્ણાંક addr, પૂર્ણાંક* dest_addr){
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
	પાછા 0;
}

/** @fn int flashDualSPIDDRXip(int addr, int* dest_addr) 
 * @brief Reads over XIP mode.
 * @details Reads for DDR based XIP mode using two io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
પૂર્ણાંક flashDualSPIDDRXip(પૂર્ણાંક addr, પૂર્ણાંક* dest_addr){
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
	પાછા 0;
}

/** @fn int flashWriteVolatileConfigReg(int value) 
 * @brief Writes into flash volatile configuration register.
 * @details Writes the passed value into flash volatile configuration register.
 * @param int value needs to written into Write Volatile Config Register.
 * @return Zero on Success
 */
પૂર્ણાંક flashWriteVolatileConfigReg(પૂર્ણાંક કિંમત){
	printf("\t Setting Volatile Configuration Register with the Value: %08x\n",કિંમત);
	જો(micron_write_enable(status)){
		printf("Panic: Write Enable Command Failed to execute\n");
		પાછા -1;
	}
	reset_interrupt_flags();
	//	flashReadStatusRegister();
	set_qspi_shakti32(dlr,DL(1));
	set_qspi_shakti8(dr,કિંમત);  //The value to be written into the VECR register to enable XIP. Indicating XIP to operate in Quad Mode
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x01)));
	waitfor(50);
	status=0;
	પૂર્ણાંક ret = wait_for_tcf(status);
	//    printf("Status : %d dcr : %d cr : %d ccr : %d dlr: %d dr: %d\n",status,*dcr,*cr,*ccr,*dlr,*dr);
	reset_interrupt_flags();
	waitfor(50);  //Giving Micron time to store the data
	પાછા ret;
}

/** @fn int flashQuadSPIXip(int addr, int* dest_addr)
 * @brief Reads over XIP mode.
 * @details Reads for DDR based XIP mode using quad io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
પૂર્ણાંક flashQuadSPIXip(પૂર્ણાંક addr, પૂર્ણાંક* dest_addr){
	જો(flashWriteVolatileConfigReg(0x40404040)){
		printf("\t Volatile Configuration Register not Set -- Diagnose\n");
		પાછા -1;
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
	પાછા 0;
}

/** @fn int flashQuadSPIDDRXip(int addr, int* dest_addr)
 * @brief Reads over XIP mode.
 * @details Reads for DDR based XIP mode using four io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
પૂર્ણાંક flashQuadSPIDDRXip(પૂર્ણાંક addr, પૂર્ણાંક* dest_addr){
	જો(flashWriteVolatileConfigReg(0x40404040)){
		printf("\t Volatile Configuration Register not Set -- Diagnose\n");
		પાછા -1;
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
	પાછા 0;
}

/** @fn int flash_Write_disable()
 * @brief disables write operation
 * @details Write operation can be possible only after enabling write enable register.
 *       Here this is disabled using this function.
 * @return Zero on Success
 */
પૂર્ણાંક flash_Write_disable(શૂન્ય){
	printf("\tWrite disable\n");
	set_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x04)));
	પૂર્ણાંક ret = wait_for_tcf(status); //Indicating the completion of command -- Currently polling
	printf("Status : %d dcr : %d cr: %d ccr: %d \n",status,*dcr,*cr,*ccr);
	reset_interrupt_flags();
	પાછા wait_for_wip();
}

/** @fn int eraseSector(int command, int address)
 * @brief Erases one sector 
 * @details Erases a complete sector which falls in the sector range.
 * @param int command --- Erase command (sector erase, block erase or chip erase)
 * @param int address --- Starting address of erase.
 * @return Zero on Success
 */
પૂર્ણાંક eraseSector(પૂર્ણાંક command, પૂર્ણાંક address){
	જો(micron_write_enable(status)){
		printf("Panic: Write Enable Command Failed to execute");
		પાછા -1;
	}
	reset_interrupt_flags();
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(command)));
	set_qspi_shakti32(ar,address);
	waitfor(150);
	પૂર્ણાંક ret = wait_for_tcf(status);
	reset_interrupt_flags();
	પાછા wait_for_wip(); //For sector erase maybe estat should be checked
}

/** @fn int micron_volatile_write_enable(int status) 
 * @brief Enable for volatile write.
 * @details Enables micron flash for programming volatile config. register.
 * @param int --- status register value.
 * @return Zero on Success
 */
પૂર્ણાંક micron_volatile_write_enable(પૂર્ણાંક status){
	printf("\tVolatile Write Enable\n");
	set_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x50)));
	પૂર્ણાંક ret = wait_for_tcf(status); //Indicating the completion of command -- Currently polling
	printf("Status : %d dcr : %d cr: %d ccr: %d \n",status,*dcr,*cr,*ccr);
	પાછા ret;
}

/** @fn int micron_enable_4byte_addressing(int status) 
 * @brief Enables micron flash for 4 byte addressing.
 * @details Address can be passed as 3 bytes or 4 bytes before read or write 
 * operation. This function sets the number of address bytes to 4 bytes.
 * @param int --- status register value
 * @return Zero on Success
 */
પૂર્ણાંક micron_enable_4byte_addressing(પૂર્ણાંક status){
	printf("\t Enable 4 byte address \n");
	set_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xB7)));
	પૂર્ણાંક ret = wait_for_tcf(status); //Indicating the completion of command -- Currently polling
	printf("Status : %d dcr : %d cr: %d ccr: %d \n",status,*dcr,*cr,*ccr);
	પાછા ret;
}

/** @fn int micron_configure_xip_volatile(int status, int value)
 * @brief Configures the xip volatile config. register.
 * @details Configures the volatile config. register for xip Read mode.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
પૂર્ણાંક micron_configure_xip_volatile(પૂર્ણાંક status, પૂર્ણાંક કિંમત){
	log_debug("\tWrite Volatile Configuration Register\n");
	set_qspi_shakti32(dlr,DL(1));
	set_qspi_shakti8(dr,કિંમત);  //The value to be written into the VECR register to enable XIP. Indicating XIP to operate in Quad Mode
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x81)));
	waitfor(50);
	પૂર્ણાંક ret = wait_for_tcf(status);
	printf("Status : %d dcr : %d cr : %d ccr : %d dlr: %d dr: %d\n",status,*dcr,*cr,*ccr,*dlr,*dr);
	waitfor(50);  //Giving Micron time to store the data
	પાછા ret;
}

/** @fn int micron_disable_xip_volatile(int status, int value)
 * @brief Configures(disables) the xip volatile config. register.
 * @details Configures(disables) the volatile config. register for xip Read mode.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
પૂર્ણાંક micron_disable_xip_volatile(પૂર્ણાંક status, __attribute__ ((unused)) પૂર્ણાંક કિંમત){
	log_debug("\tWrite Volatile Configuration Register to exit XIP\n");
	set_qspi_shakti32(cr,(CR_PRESCALER(0x3)|CR_TOIE|CR_TCIE|CR_TEIE|CR_SMIE|CR_FTIE|CR_ABORT|CR_EN));
	waitfor(30);
	qspi_init(27,0,3,1,15,1);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DUMMY_BIT|CCR_DUMMY_CONFIRMATION|CCR_DCYC(8)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(NDATA)));
	set_qspi_shakti32(ar,0x00000); //Dummy address 
	set_qspi_shakti32(dlr,1);

	પૂર્ણાંક ret = wait_for_tcf(status);
	પૂર્ણાંક temp_data = get_qspi_shakti(dr);

	waitfor(50);
	reset_interrupt_flags();
	પાછા ret;
}

/** @fn int micron_read_id_cmd(int status, int value)
 * @brief Reads the id of the micron flash.
 * @details Micron flash is having a fixed value as ID during production. This 
 * value is read to confirm proper flash device.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
પૂર્ણાંક micron_read_id_cmd(પૂર્ણાંક status, પૂર્ણાંક કિંમત){
	log_debug("\tRead ID Command to see if the Protocol is Proper\n");
	set_qspi_shakti32(dlr,4);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x9E)|CCR_DMODE(SINGLE)));
	પૂર્ણાંક ret = wait_for_tcf(status);
	કિંમત = get_qspi_shakti(dr);
	printf("Read ID: %08x",કિંમત);
	પાછા ret;
}

/** @fn int micron_read_configuration_register(int status, int value)
 * @brief Reads configuration register. 
 * @details The configurartion register is read using this function.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
પૂર્ણાંક micron_read_configuration_register(પૂર્ણાંક status, પૂર્ણાંક કિંમત){
	printf("\tRead ID Command to see if the Protocol is Proper\n");
	set_qspi_shakti32(dlr,4);
	set_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBE)|CCR_DMODE(SINGLE)));
	પૂર્ણાંક ret = wait_for_tcf(status);
	કિંમત = get_qspi_shakti(dr);
	log_debug("Configuration Register Value: %08x",કિંમત);
	પાછા ret;
}
