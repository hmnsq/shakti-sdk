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

#ਅਨ੍ਤਰ੍ਭਾਵ "qspi.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "utils.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MEM_TYPE_N25Q256_ID 0x9d189d18

ਅੱਖਰ fail_ਦੋਆਧਾਰੀ_ਅੰਕ = 0;
ਪੂਰਨ ਸਥਿਤੀ_2 = 0;
/*! Pointer to QSPI registers */
ਪੂਰਨ* cr       =  (ਪੂਰਨ*) CR; /*! Control Register */
ਪੂਰਨ* dcr      =  (ਪੂਰਨ*) DCR; /*! Data Configuration Register */
ਪੂਰਨ* sr       =  (ਪੂਰਨ*) SR; /*! Status Register */
ਪੂਰਨ* fcr      =  (ਪੂਰਨ*) FCR; /* Flag Clear Register */
ਪੂਰਨ* ccr      =  (ਪੂਰਨ*) CCR; /* Commn. Configuration Register */
ਪੂਰਨ* ar       =  (ਪੂਰਨ*) AR; /*! Address Register */
ਪੂਰਨ* abr      =  (ਪੂਰਨ*) ABR; /*! Alternate Bytes Register */
ਪੂਰਨ* dr       =  (ਪੂਰਨ*) DR; /*! Data Register */
ਪੂਰਨ* dlr      =  (ਪੂਰਨ*) DLR; /*! Data Length Register */
ਪੂਰਨ* psmkr    =  (ਪੂਰਨ*) PSMKR; /*! Polling Status Mask Register */
ਪੂਰਨ* pir      =  (ਪੂਰਨ*) PIR; /*! Polling Interval Register */
ਪੂਰਨ* lprt     =  (ਪੂਰਨ*) LPRT; /*! Low power Time Register */
ਪੂਰਨ* startmm  =  (ਪੂਰਨ*) STARTMM; /*! Start Memory Map Register */
ਪੂਰਨ* endmm    =  (ਪੂਰਨ*) ENDMM; /*! End Memory Map Register */

/** @fn void set_qspi_shakti32(int* addr, int val)
 * @brief Writes 32 bit value into QSPI register.
 * @details Writes 32 bit value into passed address QSPI register.
 * @param int* addr --- Addresss where the data (val) needs to be written
 * @param int val ---  Data which needs to be written.
 */
ਖਾਲੀ ਸੈੱਟ_qspi_shakti32(ਪੂਰਨ* addr, ਪੂਰਨ val)
{
	*addr = val;
}

/** @fn void set_qspi_shakti16(int16_t* addr, int16_t val)
 * @brief Writes 16 bit value 
 * @details Writes 16 bit value into 16bit QSPI register 
 * @param 16bit int* addr --- Addresss where the data (val) needs to be written
 * @param 16bit int val ---  Data which needs to be written.
 */
ਖਾਲੀ ਸੈੱਟ_qspi_shakti16(int16_t* addr, int16_t val)
{
	*addr = val;
}

/** @fn void set_qspi_shakti8(char* addr, char val) 
 * @brief Writes 8 bit value.
 * @details Writes 8 bit value into 8 bit qspi register.
 * @param char* addr --- Addresss where the data (val) needs to be written
 * @param char val ---  Data which needs to be written.
 */
ਖਾਲੀ ਸੈੱਟ_qspi_shakti8(ਅੱਖਰ* addr, ਅੱਖਰ val)
{
	*addr= val;
}

/** @fn int get_qspi_shakti(int* addr)
 * @brief reads from qspi register
 * @details Reads from the passed QSPI register and returns the value.
 * @param int* addr --- 32 bit Read Addresss  
 * @return Read value -- Read value from the passed value.
 */
ਪੂਰਨ get_qspi_shakti(ਪੂਰਨ* addr)
{
	ਵਾਪਸ *addr;
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
ਖਾਲੀ qspi_init(ਪੂਰਨ fsize, ਪੂਰਨ csht, ਪੂਰਨ prescaler, ਪੂਰਨ enable_interrupts, ਪੂਰਨ fthreshold, ਪੂਰਨ ck_ਬਹੁਲਕ){
	ਪੂਰਨ int_ਸਦਿਸ਼ = enable_interrupts? (CR_TOIE|CR_SMIE|CR_FTIE|CR_TCIE|CR_TEIE) : 0; 
	ਸੈੱਟ_qspi_shakti32(dcr,(DCR_FSIZE(fsize)|DCR_CSHT(csht)|DCR_CKMODE(ck_ਬਹੁਲਕ))); 
	ਸੈੱਟ_qspi_shakti32(cr,(CR_PRESCALER(prescaler)|int_ਸਦਿਸ਼|CR_FTHRES(fthreshold)|CR_EN));
}

/** @fn void reset_interrupt_flags()
 * @brief Resets interrupt flags.
 * @details Before carrying out any flash access operations, the interrupt flags are cleared.
 */
ਖਾਲੀ reset_ਰੁਕਾਵਟ_flags(){
	ਸੈੱਟ_qspi_shakti32(fcr,(FCR_CTOF|FCR_CSMF|FCR_CTCF|FCR_CTEF)); //Resetting all the flags
}

/** @fn int wait_for_tcf(int status)
 * @brief Wait for the transfer complete flag.
 * @details WCF bit status register indicates the completion of flash 
 *  operation. The same is cheked here.
 * @param int status register read value.
 * @return Zero on success else -1
 */
ਪੂਰਨ wait_for_tcf(ਪੂਰਨ ਸਥਿਤੀ_2){
	ਪੂਰਨ timeout = DEF_TIMEOUT; 

	ਸਥਿਤੀ_2 = get_qspi_shakti(sr);

	//    printf("status : %d looping?\n",status);

	ਜਦੋਂ(!( ਸਥਿਤੀ_2 & 0x02 ) && --timeout){
		waitfor(1000);
		ਸਥਿਤੀ_2=get_qspi_shakti(sr);
		ਲਿਖੋ("status: %08x in loop %d \n",ਸਥਿਤੀ_2, !(ਸਥਿਤੀ_2 & 0x02));
	}
	ਜੇ(timeout==0){
		ਲਿਖੋ("Request Timed out\n");
		ਵਾਪਸ -1;
	}
	ਵਾਪਸ 0;
}

/** @fn int check_fail_bit()
 * @brief Checks the value of fail_bit.
 * @details Checks the fail bit whether the value is zero or not.
 */
ਪੂਰਨ check_fail_ਦੋਆਧਾਰੀ_ਅੰਕ(ਖਾਲੀ){
	ਜੇ(fail_ਦੋਆਧਾਰੀ_ਅੰਕ){
		fail_ਦੋਆਧਾਰੀ_ਅੰਕ = 0;
		ਵਾਪਸ -1;
	}
	ਨਹੀਂਤਾਂ{
		fail_ਦੋਆਧਾਰੀ_ਅੰਕ = 0;
		ਵਾਪਸ 0;
	}
}

/** @fn int flashReadStatusRegister()
 * @brief Reads flash status register
 * @details Reads flash status register contents
 * @return Status register value on success; else -1
 */
ਪੂਰਨ flash_Read_ਸਥਿਤੀ_ਰਜਿਸਟਰ(){
	//    printf("\tReading the Status bits of the Flash\n");
	ਸੈੱਟ_qspi_shakti32(dlr,4);
	ਸੈੱਟ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x05)|CCR_DMODE(SINGLE)));

	ਸਥਿਤੀ_2 = 0;
	waitfor(1000);
	ਪੂਰਨ ret = wait_for_tcf(ਸਥਿਤੀ_2);
	waitfor(100);
	ਪੂਰਨ ਮੁੱਲ = get_qspi_shakti(dr);
	//	printf("Read status register value %08x \n", value);
	reset_ਰੁਕਾਵਟ_flags();
	ਜੇ(ret){
		ਲਿਖੋ("\tRead Status Register Failed\n");
		fail_ਦੋਆਧਾਰੀ_ਅੰਕ = 1;
		ਵਾਪਸ -1;
	}
	ਨਹੀਂਤਾਂ
		ਵਾਪਸ ਮੁੱਲ;
}

/** @fn int wait_for_wip()
 * @brief Wait till a flash access is complete.
 * @details Reads the WIP bit in the status register to check the completion of flash access.
 * Useful during flash write operations.
 * @return Zero on Success
 */
ਪੂਰਨ wait_for_wip(ਖਾਲੀ){
	ਪੂਰਨ status1;
	ਕਰੋ{
		//  printf("\t Waiting for Wip \n");
		status1 = flash_Read_ਸਥਿਤੀ_ਰਜਿਸਟਰ(0x05);
		ਜੇ(check_fail_ਦੋਆਧਾਰੀ_ਅੰਕ())
			ਵਾਪਸ -1;
		ਜੇ(status1 & 0x0){
			ਲਿਖੋ("\tQSPI: Programming Error - Diagnose\n");
			ਵਾਪਸ -1;
		}
		waitfor(20000);
	}ਜਦੋਂ(status1 & 0x01);
	//    printf("\t QSPI: Page Program/Erase Command Successfully Completed\n");
	ਵਾਪਸ 0;
}

/** @fn int micron_write_enable(int status)
 * @brief Enables the micron flash for write operation.
 * @details Enables micron flash for programming flash data.
 * @param int status --- Write enable status.
 * @return Zero on Success
 */
ਪੂਰਨ micron_write_enable(ਪੂਰਨ ਸਥਿਤੀ_2){
	//  printf("\tWrite Enable\n");
	ਸੈੱਟ_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x06)));
	ਪੂਰਨ ret = wait_for_tcf(ਸਥਿਤੀ_2); //Indicating the completion of command -- Currently polling
	//  printf("Status : %d dcr : %d cr: %d ccr: %d \n",status,*dcr,*cr,*ccr);
	ਵਾਪਸ ret;
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
ਪੂਰਨ ਪੰਨਾ_ਪ੍ਰੋਗਰਾਮ_Single_SPI(ਪੂਰਨ value1, ਪੂਰਨ value2, ਪੂਰਨ value3, ਪੂਰਨ value4, ਪੂਰਨ ਪਤਾ){
	ਜੇ(micron_write_enable(ਸਥਿਤੀ_2)){
		ਲਿਖੋ("Panic: Write Enable Command Failed to execute");
		ਵਾਪਸ -1;
	}
	reset_ਰੁਕਾਵਟ_flags(); 

	ਸੈੱਟ_qspi_shakti32(dlr,DL(16));
	// set_qspi_shakti32(ccr,(CCR_DDRM | CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x12))); 
	ਸੈੱਟ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x12)));
	ਸੈੱਟ_qspi_shakti32(ar, ਪਤਾ);        
	ਲਿਖੋ(" Address written %d \n",ਪਤਾ); 
	ਸੈੱਟ_qspi_shakti32(dr,value1);
	ਲਿਖੋ(" Value 1 written %d \n",value1);
	ਸੈੱਟ_qspi_shakti32(dr,value2);
	ਲਿਖੋ(" Value 2 written %d \n",value2);
	ਸੈੱਟ_qspi_shakti32(dr,value3);
	ਲਿਖੋ(" Value 3 written %d \n",value3);
	ਸੈੱਟ_qspi_shakti32(dr,value4);
	ਲਿਖੋ(" Value 4 written %d \n",value4);
	waitfor(150); 
	wait_for_tcf(ਸਥਿਤੀ_2);
	reset_ਰੁਕਾਵਟ_flags();
	ਵਾਪਸ wait_for_wip(); // Function which checks if WIP is done, indicating completion of Page Program
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
ਪੂਰਨ ਪੰਨਾ_ਪ੍ਰੋਗਰਾਮ_Quad_SPI(ਪੂਰਨ value1, ਪੂਰਨ value2, ਪੂਰਨ value3, ਪੂਰਨ value4, ਪੂਰਨ ਪਤਾ){
	ਜੇ(micron_write_enable(ਸਥਿਤੀ_2)){
		ਲਿਖੋ("Panic: Write Enable Command Failed to execute");
		ਵਾਪਸ -1;
	}
	reset_ਰੁਕਾਵਟ_flags(); 

	ਸੈੱਟ_qspi_shakti32(dlr,DL(16));
	// set_qspi_shakti32(ccr,(CCR_DDRM | CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x12))); 
	ਸੈੱਟ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(QUAD)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x34))); 
	ਸੈੱਟ_qspi_shakti32(ar, ਪਤਾ);
	ਸੈੱਟ_qspi_shakti32(dr,value1);
	ਸੈੱਟ_qspi_shakti32(dr,value2);
	ਸੈੱਟ_qspi_shakti32(dr,value3);
	ਸੈੱਟ_qspi_shakti32(dr,value4);
	waitfor(150); 
	wait_for_tcf(ਸਥਿਤੀ_2);
	reset_ਰੁਕਾਵਟ_flags();
	ਵਾਪਸ wait_for_wip(); // Function which checks if WIP is done, indicating completion of Page Program
}

/** @fn int flashIdentificationDevice()
 * @brief Reads flash id code.
 * @details Reads flash identification code from the flash device and checks whether it valid.
 * @return Zero on success else -1
 */
ਪੂਰਨ flashIdentificationDevice(ਖਾਲੀ){
	log_debug("\tReading the ID register and discovering the Flash Device\n");
	ਸੈੱਟ_qspi_shakti32(dlr,4);
	ਸੈੱਟ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x90)|CCR_ADSIZE(THREEBYTE)|CCR_ADMODE(SINGLE)|CCR_DMODE(SINGLE)));
	ਸੈੱਟ_qspi_shakti32(ar, 0);
	ਸਥਿਤੀ_2 = 0; // Useless Variable but still!!!!
	ਪੂਰਨ ret = wait_for_tcf(ਸਥਿਤੀ_2);
	ਪੂਰਨ ਮੁੱਲ = get_qspi_shakti(dr);
	log_info("\t device id %x\n",ਮੁੱਲ);
	reset_ਰੁਕਾਵਟ_flags();
	ਜੇ(ਮੁੱਲ == MEM_TYPE_N25Q256_ID){
		ਲਿਖੋ("\tN25Q256 Device Detected \n");
		ਵਾਪਸ 0;
	}
	ਨਹੀਂਤਾਂ{
		log_fatal("\t Device Not Detected - Diagnose %08x\n",ਮੁੱਲ);
		ਵਾਪਸ -1;
	}
}

/** @fn int flashMemInit()
 * @brief Initialises flash memory 
 * @details Initialises flash device and check for id code.
 * @return Zero on success else -1
 */
ਪੂਰਨ flashMemInit(){  //Supposedly a set of routines to check if the memory/interface or whatever is proper
	ਪੂਰਨ ret = flashIdentificationDevice();
	ਜੇ(ret==-1){
		log_fatal("Flash Mem Init Failed -- Quitting Program, Diagnose");
		ਵਾਪਸ ret;
	}
	ਨਹੀਂਤਾਂ log_debug("Flash Mem Init Success\n");
	ਵਾਪਸ 0;
	//to fill in code
}


/** @fn int flashReadFlagRegister()
 * @brief Reads flash read flag. 
 * @details Reads the flash flag register.
 * @warning Not implemented now. Reserve for future.
 */
ਪੂਰਨ flash_Read_Flag_ਰਜਿਸਟਰ(ਖਾਲੀ){
	ਵਾਪਸ 0;
}

/** @fn int flashWriteEnable()
 * @brief Enables flash enable bit
 * @details For any write operation into to flash device (erase, program, etc.)
 *        this enable bit needs to be enabled.
 * @return TCF status
 */
ਪੂਰਨ flashWriteEnable(ਖਾਲੀ){
	ਲਿਖੋ("\tWrite Enable\n");
	ਸੈੱਟ_qspi_shakti32(ccr,(CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x06)));
	ਪੂਰਨ ret = wait_for_tcf(0); //Indicating the completion of command -- Currently polling
	reset_ਰੁਕਾਵਟ_flags();
	ਵਾਪਸ ret; 
}

/** @fn int flashEnable4ByteAddressingMode()
 * @brief Selects the addressed mode.
 * @details Before accessing flash device, the number of bits used for (Q)SPI needs to be programmed.
 * @return Status of the performed operation; else -1
 */
ਪੂਰਨ flash_Enable4_Byte_Addressing_ਬਹੁਲਕ(ਖਾਲੀ){  //Enable 4-byte addressing Mode and read the status to verify that it has happened correctly

	ਜੇ(flashWriteEnable()){
		ਲਿਖੋ("\t Write Enable Failed \n");
		ਵਾਪਸ -1;
	}
	waitfor(100);
	ਸੈੱਟ_qspi_shakti32(ccr,(CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xB7)));
	//  int status =0; 
	ਸਥਿਤੀ_2 = 0;
	ਪੂਰਨ ret = wait_for_tcf(ਸਥਿਤੀ_2);
	reset_ਰੁਕਾਵਟ_flags();
	waitfor(100);
	//Checking Phase
	ਸਥਿਤੀ_2 = flash_Read_ਸਥਿਤੀ_ਰਜਿਸਟਰ();
	ਲਿਖੋ("\t Status Value: %08x\n",ਸਥਿਤੀ_2);
	ਜੇ(ਸਥਿਤੀ_2 & 1)
		ਲਿਖੋ("\t 4-Byte Addressing Mode is Enabled\n");
	ਨਹੀਂਤਾਂ
		ਲਿਖੋ("\t 4-byte Addressing mode not Enabled\n");
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
ਪੂਰਨ flashReadSingleSPI(ਪੂਰਨ dummy_ਚੱਕਰਾਂ, ਪੂਰਨ read_ਪਤਾ, ਪੂਰਨ instruction, ਪੂਰਨ ਅੰਕੜੇ_ਸ਼ਬਦ, ਪੂਰਨ adsize){
	ਸੈੱਟ_qspi_shakti32(dlr,ਅੰਕੜੇ_ਸ਼ਬਦ);
	ਸੈੱਟ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(SINGLE)|CCR_DCYC(dummy_ਚੱਕਰਾਂ)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_ADSIZE(adsize)|CCR_INSTRUCTION(instruction)));
	ਸੈੱਟ_qspi_shakti32(ar,read_ਪਤਾ);
	ਸਥਿਤੀ_2 = 0;
	ਪੂਰਨ ret = wait_for_tcf(ਸਥਿਤੀ_2);
	ਪੂਰਨ ਮੁੱਲ = get_qspi_shakti(dr);
	ਲਿਖੋ("\tThe Read Value: %08x\n",ਮੁੱਲ);
	//    printf("\tThe Read Value: %08x\n",value);
	ਜੇ(ret){
		ਲਿਖੋ("\t Read Value Failed \n");
		ਵਾਪਸ -1;
	}
	reset_ਰੁਕਾਵਟ_flags();
	ਵਾਪਸ ਮੁੱਲ;
}

/** @fn int flashReadDualSPI(int address, int data_length)
 * @brief  Reads flash device over two io lines SPI.
 * @details Reads the flash device over two io lines for spi (IO1, IO2, CS, CLK) data
 * @param int address --- Address which needs to be read.
 * @param int data_length --- Number of Data bytes (data_words + 1) needs to be read 
 * @return Status of the performed operation; else -1
 */
ਪੂਰਨ flashReadDualSPI(ਪੂਰਨ ਪਤਾ, ਪੂਰਨ ਅੰਕੜੇ_ਲੰਮਾਈ){
	ਸੈੱਟ_qspi_shakti32(dlr,ਅੰਕੜੇ_ਲੰਮਾਈ); //DLR
	ਸੈੱਟ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(DOUBLE)|CCR_DCYC(3)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBB)));
	ਸੈੱਟ_qspi_shakti32(ar,ਪਤਾ); 
	//    printf("Status : %08x dcr : %08x cr : %08x ccr : %08x dlr: %08x ar: %08x\n",status,*dcr,*cr,*ccr,*dlr,*ar);
	ਪੂਰਨ ret = wait_for_tcf(ਸਥਿਤੀ_2);
	ਪੂਰਨ ਮੁੱਲ = get_qspi_shakti(dr);
	ਲਿਖੋ("\tThe Read Value: %08x\n",ਮੁੱਲ);	
	ਜੇ(ret){
		ਲਿਖੋ("\t QSPI: Read Value failed\n");
		ਵਾਪਸ -1;
	}
	//*config_string = get_qspi_shakti(dr);
	//printf("\t Read Data is %08x\n",read_data);
	reset_ਰੁਕਾਵਟ_flags();
	ਵਾਪਸ ਮੁੱਲ;
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
ਪੂਰਨ flashReadQuadSPI(ਪੂਰਨ dummy_ਚੱਕਰਾਂ, ਪੂਰਨ read_ਪਤਾ, ਪੂਰਨ instruction, ਪੂਰਨ ਅੰਕੜੇ_ਸ਼ਬਦ, ਪੂਰਨ adsize){
	ਸੈੱਟ_qspi_shakti32(dlr,ਅੰਕੜੇ_ਸ਼ਬਦ);
	ਸੈੱਟ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DCYC(dummy_ਚੱਕਰਾਂ)|CCR_ADSIZE(adsize)|CCR_ADMODE(QUAD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(instruction)));
	ਸੈੱਟ_qspi_shakti32(ar,read_ਪਤਾ);
	ਸਥਿਤੀ_2 = 0;
	ਪੂਰਨ ret = wait_for_tcf(ਸਥਿਤੀ_2);
	ਪੂਰਨ ਮੁੱਲ_1 = get_qspi_shakti(dr);
	ਪੂਰਨ ਮੁੱਲ_2_2 = get_qspi_shakti(dr);
	ਪੂਰਨ ਮੁੱਲ_3 = get_qspi_shakti(dr);
	ਪੂਰਨ ਮੁੱਲ_4 = get_qspi_shakti(dr);
	ਲਿਖੋ("\tThe Read Value: %08x, %08x, %08x and %08x \n",ਮੁੱਲ_1,ਮੁੱਲ_2_2,ਮੁੱਲ_3,ਮੁੱਲ_4);
	ਜੇ(ret){
		ਲਿਖੋ("\t Read Value Failed \n");
		ਵਾਪਸ -1; 
	}   
	reset_ਰੁਕਾਵਟ_flags();
	ਵਾਪਸ ਮੁੱਲ_1;
}

/** @fn int flashSingleSPIXip(int addr, int* dest_addr) 
 * @brief Reads over single SPI XIP
 * @details Generic Read for xip SPI Read.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on success.
 */
ਪੂਰਨ flashSingleSPIXip(ਪੂਰਨ addr, ਪੂਰਨ* dest_addr){
	ਸੈੱਟ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(SINGLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(7)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x0C)));
	ਸੈੱਟ_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_ਬਹੁਲਕ_BYTE(0x00)|DCR_CKMODE(1)));
	ਸੈੱਟ_qspi_shakti32(dlr,0x4);
	ਸੈੱਟ_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	ਸਥਿਤੀ_2=0;
	wait_for_tcf(ਸਥਿਤੀ_2);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	ਲਿਖੋ("\n Fisrt value obtained through single read : %d \n ",*dest_addr);
	reset_ਰੁਕਾਵਟ_flags(); 
	ਲਿਖੋ("\t Trying XIP now\n");
	ਸੈੱਟ_qspi_shakti32(ccr, (CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(SINGLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(7)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x0C)));
	ਸੈੱਟ_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_ਬਹੁਲਕ_BYTE(0x00)|DCR_CKMODE(1))); 
	waitfor(25);
	ਵਾਪਸ 0;
}

/** @fn int flashSingleSPIDDRXip(int addr, int* dest_addr)  
 * @brief Reads over DDR XIP mode.
 * @details Reads for DDR based XIP mode.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
ਪੂਰਨ flashSingleSPIDDRXip(ਪੂਰਨ addr, ਪੂਰਨ* dest_addr){
	ਸੈੱਟ_qspi_shakti32(ccr,(CCR_DDRM|CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(SINGLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(15)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x0E)));
	ਸੈੱਟ_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_ਬਹੁਲਕ_BYTE(0x00)|DCR_CKMODE(1)));
	ਸੈੱਟ_qspi_shakti32(dlr,0x4);
	ਸੈੱਟ_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	ਸਥਿਤੀ_2=0;
	wait_for_tcf(ਸਥਿਤੀ_2);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	reset_ਰੁਕਾਵਟ_flags(); 
	ਲਿਖੋ("\t Trying XIP now\n");
	ਸੈੱਟ_qspi_shakti32(ccr, (CCR_DDRM|CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(SINGLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(14)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x0E)));
	ਸੈੱਟ_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_ਬਹੁਲਕ_BYTE(0x00)|DCR_CKMODE(1))); 
	waitfor(25);
	ਵਾਪਸ 0;
}

/** @fn int flashDualSPIXip(int addr, int* dest_addr)
 * @brief Reads over XIP mode.
 * @details Reads for XIP mode using two io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
ਪੂਰਨ flashDualSPIXip(ਪੂਰਨ addr, ਪੂਰਨ* dest_addr){
	ਸੈੱਟ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(DOUBLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(3)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBB)));
	ਸੈੱਟ_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_ਬਹੁਲਕ_BYTE(0xA0)|DCR_CKMODE(1)));
	ਸੈੱਟ_qspi_shakti32(dlr,0x4);
	ਸੈੱਟ_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	ਸਥਿਤੀ_2=0;
	wait_for_tcf(ਸਥਿਤੀ_2);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	ਲਿਖੋ("\n Fisrt value obtained through single read : %d \n ",*dest_addr);
	reset_ਰੁਕਾਵਟ_flags(); 
	ਲਿਖੋ("\t Trying XIP now\n");
	ਸੈੱਟ_qspi_shakti32(ccr, (CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(DOUBLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(3)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(NDATA)));
	ਸੈੱਟ_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_ਬਹੁਲਕ_BYTE(0xA0)|DCR_CKMODE(1))); 
	waitfor(25);
	ਵਾਪਸ 0;
}

/** @fn int flashDualSPIDDRXip(int addr, int* dest_addr) 
 * @brief Reads over XIP mode.
 * @details Reads for DDR based XIP mode using two io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
ਪੂਰਨ flashDualSPIDDRXip(ਪੂਰਨ addr, ਪੂਰਨ* dest_addr){
	ਸੈੱਟ_qspi_shakti32(ccr,(CCR_DDRM|CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(DOUBLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(6)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBE)));
	ਸੈੱਟ_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_ਬਹੁਲਕ_BYTE(0xA0)|DCR_CKMODE(1)));
	ਸੈੱਟ_qspi_shakti32(dlr,0x4);
	ਸੈੱਟ_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	ਸਥਿਤੀ_2=0;
	wait_for_tcf(ਸਥਿਤੀ_2);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	reset_ਰੁਕਾਵਟ_flags(); 
	ਲਿਖੋ("\t Trying XIP now\n");
	ਸੈੱਟ_qspi_shakti32(ccr, (CCR_DDRM|CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(DOUBLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(6)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(NDATA)));
	ਸੈੱਟ_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_ਬਹੁਲਕ_BYTE(0xA0)|DCR_CKMODE(1))); 
	waitfor(25);
	ਵਾਪਸ 0;
}

/** @fn int flashWriteVolatileConfigReg(int value) 
 * @brief Writes into flash volatile configuration register.
 * @details Writes the passed value into flash volatile configuration register.
 * @param int value needs to written into Write Volatile Config Register.
 * @return Zero on Success
 */
ਪੂਰਨ flashWriteVolatileConfigReg(ਪੂਰਨ ਮੁੱਲ){
	ਲਿਖੋ("\t Setting Volatile Configuration Register with the Value: %08x\n",ਮੁੱਲ);
	ਜੇ(micron_write_enable(ਸਥਿਤੀ_2)){
		ਲਿਖੋ("Panic: Write Enable Command Failed to execute\n");
		ਵਾਪਸ -1;
	}
	reset_ਰੁਕਾਵਟ_flags();
	//	flashReadStatusRegister();
	ਸੈੱਟ_qspi_shakti32(dlr,DL(1));
	ਸੈੱਟ_qspi_shakti8(dr,ਮੁੱਲ);  //The value to be written into the VECR register to enable XIP. Indicating XIP to operate in Quad Mode
	ਸੈੱਟ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x01)));
	waitfor(50);
	ਸਥਿਤੀ_2=0;
	ਪੂਰਨ ret = wait_for_tcf(ਸਥਿਤੀ_2);
	//    printf("Status : %d dcr : %d cr : %d ccr : %d dlr: %d dr: %d\n",status,*dcr,*cr,*ccr,*dlr,*dr);
	reset_ਰੁਕਾਵਟ_flags();
	waitfor(50);  //Giving Micron time to store the data
	ਵਾਪਸ ret;
}

/** @fn int flashQuadSPIXip(int addr, int* dest_addr)
 * @brief Reads over XIP mode.
 * @details Reads for DDR based XIP mode using quad io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
ਪੂਰਨ flashQuadSPIXip(ਪੂਰਨ addr, ਪੂਰਨ* dest_addr){
	ਜੇ(flashWriteVolatileConfigReg(0x40404040)){
		ਲਿਖੋ("\t Volatile Configuration Register not Set -- Diagnose\n");
		ਵਾਪਸ -1;
	}
	ਸਥਿਤੀ_2 = wait_for_wip();
	ਲਿਖੋ("\t qspi status register %08x\n",ਸਥਿਤੀ_2);
	reset_ਰੁਕਾਵਟ_flags();
	ਸੈੱਟ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(5)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xEC)));
	ਸੈੱਟ_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_ਬਹੁਲਕ_BYTE(0xA0)|DCR_CKMODE(1)));
	ਸੈੱਟ_qspi_shakti32(dlr,0x4);
	ਸੈੱਟ_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	ਸਥਿਤੀ_2=0;
	wait_for_tcf(ਸਥਿਤੀ_2);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	reset_ਰੁਕਾਵਟ_flags(); 
	ਲਿਖੋ("\t Trying XIP now\n");
	ਸੈੱਟ_qspi_shakti32(ccr, (CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(QUAD)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(5)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(NDATA)));
	ਸੈੱਟ_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_ਬਹੁਲਕ_BYTE(0xA0)|DCR_CKMODE(1))); 
	waitfor(25);
	ਵਾਪਸ 0;
}

/** @fn int flashQuadSPIDDRXip(int addr, int* dest_addr)
 * @brief Reads over XIP mode.
 * @details Reads for DDR based XIP mode using four io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
ਪੂਰਨ flashQuadSPIDDRXip(ਪੂਰਨ addr, ਪੂਰਨ* dest_addr){
	ਜੇ(flashWriteVolatileConfigReg(0x40404040)){
		ਲਿਖੋ("\t Volatile Configuration Register not Set -- Diagnose\n");
		ਵਾਪਸ -1;
	}
	ਸਥਿਤੀ_2 = wait_for_wip();
	ਲਿਖੋ("\t qspi status register %08x\n",ਸਥਿਤੀ_2);
	reset_ਰੁਕਾਵਟ_flags();
	ਸੈੱਟ_qspi_shakti32(ccr,(CCR_DDRM|CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(10)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xEE)));
	ਸੈੱਟ_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_ਬਹੁਲਕ_BYTE(0xA0)|DCR_CKMODE(1)));
	ਸੈੱਟ_qspi_shakti32(dlr,0x4);
	ਸੈੱਟ_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	ਸਥਿਤੀ_2=0;
	wait_for_tcf(ਸਥਿਤੀ_2);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	reset_ਰੁਕਾਵਟ_flags(); 
	ਲਿਖੋ("\t Trying XIP now\n");
	ਸੈੱਟ_qspi_shakti32(ccr, (CCR_DDRM|CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(QUAD)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(10)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(NDATA)));
	ਸੈੱਟ_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_ਬਹੁਲਕ_BYTE(0xA0)|DCR_CKMODE(1))); 
	waitfor(25);
	ਵਾਪਸ 0;
}

/** @fn int flash_Write_disable()
 * @brief disables write operation
 * @details Write operation can be possible only after enabling write enable register.
 *       Here this is disabled using this function.
 * @return Zero on Success
 */
ਪੂਰਨ flash_Write_disable(ਖਾਲੀ){
	ਲਿਖੋ("\tWrite disable\n");
	ਸੈੱਟ_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x04)));
	ਪੂਰਨ ret = wait_for_tcf(ਸਥਿਤੀ_2); //Indicating the completion of command -- Currently polling
	ਲਿਖੋ("Status : %d dcr : %d cr: %d ccr: %d \n",ਸਥਿਤੀ_2,*dcr,*cr,*ccr);
	reset_ਰੁਕਾਵਟ_flags();
	ਵਾਪਸ wait_for_wip();
}

/** @fn int eraseSector(int command, int address)
 * @brief Erases one sector 
 * @details Erases a complete sector which falls in the sector range.
 * @param int command --- Erase command (sector erase, block erase or chip erase)
 * @param int address --- Starting address of erase.
 * @return Zero on Success
 */
ਪੂਰਨ eraseSector(ਪੂਰਨ command, ਪੂਰਨ ਪਤਾ){
	ਜੇ(micron_write_enable(ਸਥਿਤੀ_2)){
		ਲਿਖੋ("Panic: Write Enable Command Failed to execute");
		ਵਾਪਸ -1;
	}
	reset_ਰੁਕਾਵਟ_flags();
	ਸੈੱਟ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(command)));
	ਸੈੱਟ_qspi_shakti32(ar,ਪਤਾ);
	waitfor(150);
	ਪੂਰਨ ret = wait_for_tcf(ਸਥਿਤੀ_2);
	reset_ਰੁਕਾਵਟ_flags();
	ਵਾਪਸ wait_for_wip(); //For sector erase maybe estat should be checked
}

/** @fn int micron_volatile_write_enable(int status) 
 * @brief Enable for volatile write.
 * @details Enables micron flash for programming volatile config. register.
 * @param int --- status register value.
 * @return Zero on Success
 */
ਪੂਰਨ micron_volatile_write_enable(ਪੂਰਨ ਸਥਿਤੀ_2){
	ਲਿਖੋ("\tVolatile Write Enable\n");
	ਸੈੱਟ_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x50)));
	ਪੂਰਨ ret = wait_for_tcf(ਸਥਿਤੀ_2); //Indicating the completion of command -- Currently polling
	ਲਿਖੋ("Status : %d dcr : %d cr: %d ccr: %d \n",ਸਥਿਤੀ_2,*dcr,*cr,*ccr);
	ਵਾਪਸ ret;
}

/** @fn int micron_enable_4byte_addressing(int status) 
 * @brief Enables micron flash for 4 byte addressing.
 * @details Address can be passed as 3 bytes or 4 bytes before read or write 
 * operation. This function sets the number of address bytes to 4 bytes.
 * @param int --- status register value
 * @return Zero on Success
 */
ਪੂਰਨ micron_enable_4byte_addressing(ਪੂਰਨ ਸਥਿਤੀ_2){
	ਲਿਖੋ("\t Enable 4 byte address \n");
	ਸੈੱਟ_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xB7)));
	ਪੂਰਨ ret = wait_for_tcf(ਸਥਿਤੀ_2); //Indicating the completion of command -- Currently polling
	ਲਿਖੋ("Status : %d dcr : %d cr: %d ccr: %d \n",ਸਥਿਤੀ_2,*dcr,*cr,*ccr);
	ਵਾਪਸ ret;
}

/** @fn int micron_configure_xip_volatile(int status, int value)
 * @brief Configures the xip volatile config. register.
 * @details Configures the volatile config. register for xip Read mode.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
ਪੂਰਨ micron_configure_xip_volatile(ਪੂਰਨ ਸਥਿਤੀ_2, ਪੂਰਨ ਮੁੱਲ){
	log_debug("\tWrite Volatile Configuration Register\n");
	ਸੈੱਟ_qspi_shakti32(dlr,DL(1));
	ਸੈੱਟ_qspi_shakti8(dr,ਮੁੱਲ);  //The value to be written into the VECR register to enable XIP. Indicating XIP to operate in Quad Mode
	ਸੈੱਟ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x81)));
	waitfor(50);
	ਪੂਰਨ ret = wait_for_tcf(ਸਥਿਤੀ_2);
	ਲਿਖੋ("Status : %d dcr : %d cr : %d ccr : %d dlr: %d dr: %d\n",ਸਥਿਤੀ_2,*dcr,*cr,*ccr,*dlr,*dr);
	waitfor(50);  //Giving Micron time to store the data
	ਵਾਪਸ ret;
}

/** @fn int micron_disable_xip_volatile(int status, int value)
 * @brief Configures(disables) the xip volatile config. register.
 * @details Configures(disables) the volatile config. register for xip Read mode.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
ਪੂਰਨ micron_disable_xip_volatile(ਪੂਰਨ ਸਥਿਤੀ_2, __attribute__ ((ਅਣਵਰਤਿਆ)) ਪੂਰਨ ਮੁੱਲ){
	log_debug("\tWrite Volatile Configuration Register to exit XIP\n");
	ਸੈੱਟ_qspi_shakti32(cr,(CR_PRESCALER(0x3)|CR_TOIE|CR_TCIE|CR_TEIE|CR_SMIE|CR_FTIE|CR_ABORT|CR_EN));
	waitfor(30);
	qspi_init(27,0,3,1,15,1);
	ਸੈੱਟ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DUMMY_ਦੋਆਧਾਰੀ_ਅੰਕ|CCR_DUMMY_CONFIRMATION|CCR_DCYC(8)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(NDATA)));
	ਸੈੱਟ_qspi_shakti32(ar,0x00000); //Dummy address 
	ਸੈੱਟ_qspi_shakti32(dlr,1);

	ਪੂਰਨ ret = wait_for_tcf(ਸਥਿਤੀ_2);
	ਪੂਰਨ ਆਰਜ਼ੀ_ਅੰਕੜੇ = get_qspi_shakti(dr);

	waitfor(50);
	reset_ਰੁਕਾਵਟ_flags();
	ਵਾਪਸ ret;
}

/** @fn int micron_read_id_cmd(int status, int value)
 * @brief Reads the id of the micron flash.
 * @details Micron flash is having a fixed value as ID during production. This 
 * value is read to confirm proper flash device.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
ਪੂਰਨ micron_read_id_cmd(ਪੂਰਨ ਸਥਿਤੀ_2, ਪੂਰਨ ਮੁੱਲ){
	log_debug("\tRead ID Command to see if the Protocol is Proper\n");
	ਸੈੱਟ_qspi_shakti32(dlr,4);
	ਸੈੱਟ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x9E)|CCR_DMODE(SINGLE)));
	ਪੂਰਨ ret = wait_for_tcf(ਸਥਿਤੀ_2);
	ਮੁੱਲ = get_qspi_shakti(dr);
	ਲਿਖੋ("Read ID: %08x",ਮੁੱਲ);
	ਵਾਪਸ ret;
}

/** @fn int micron_read_configuration_register(int status, int value)
 * @brief Reads configuration register. 
 * @details The configurartion register is read using this function.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
ਪੂਰਨ micron_read_configuration_ਰਜਿਸਟਰ(ਪੂਰਨ ਸਥਿਤੀ_2, ਪੂਰਨ ਮੁੱਲ){
	ਲਿਖੋ("\tRead ID Command to see if the Protocol is Proper\n");
	ਸੈੱਟ_qspi_shakti32(dlr,4);
	ਸੈੱਟ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBE)|CCR_DMODE(SINGLE)));
	ਪੂਰਨ ret = wait_for_tcf(ਸਥਿਤੀ_2);
	ਮੁੱਲ = get_qspi_shakti(dr);
	log_debug("Configuration Register Value: %08x",ਮੁੱਲ);
	ਵਾਪਸ ret;
}
