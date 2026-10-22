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

#ಅನ್ತರ್ಭಾವ "qspi.h"
#ಅನ್ತರ್ಭಾವ "utils.h"
#ಅನ್ತರ್ಭಾವ "log.h"
#ವ್ಯಾಖ್ಯಾನಿಸು MEM_TYPE_N25Q256_ID 0x9d189d18

ಅಕ್ಷರ fail_ಬಿಟ್ = 0;
ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_3 = 0;
/*! Pointer to QSPI registers */
ಪೂರ್ಣಾಂಕ* cr       =  (ಪೂರ್ಣಾಂಕ*) CR; /*! Control Register */
ಪೂರ್ಣಾಂಕ* dcr      =  (ಪೂರ್ಣಾಂಕ*) DCR; /*! Data Configuration Register */
ಪೂರ್ಣಾಂಕ* sr       =  (ಪೂರ್ಣಾಂಕ*) SR; /*! Status Register */
ಪೂರ್ಣಾಂಕ* fcr      =  (ಪೂರ್ಣಾಂಕ*) FCR; /* Flag Clear Register */
ಪೂರ್ಣಾಂಕ* ccr      =  (ಪೂರ್ಣಾಂಕ*) CCR; /* Commn. Configuration Register */
ಪೂರ್ಣಾಂಕ* ar       =  (ಪೂರ್ಣಾಂಕ*) AR; /*! Address Register */
ಪೂರ್ಣಾಂಕ* abr      =  (ಪೂರ್ಣಾಂಕ*) ABR; /*! Alternate Bytes Register */
ಪೂರ್ಣಾಂಕ* dr       =  (ಪೂರ್ಣಾಂಕ*) DR; /*! Data Register */
ಪೂರ್ಣಾಂಕ* dlr      =  (ಪೂರ್ಣಾಂಕ*) DLR; /*! Data Length Register */
ಪೂರ್ಣಾಂಕ* psmkr    =  (ಪೂರ್ಣಾಂಕ*) PSMKR; /*! Polling Status Mask Register */
ಪೂರ್ಣಾಂಕ* pir      =  (ಪೂರ್ಣಾಂಕ*) PIR; /*! Polling Interval Register */
ಪೂರ್ಣಾಂಕ* lprt     =  (ಪೂರ್ಣಾಂಕ*) LPRT; /*! Low power Time Register */
ಪೂರ್ಣಾಂಕ* startmm  =  (ಪೂರ್ಣಾಂಕ*) STARTMM; /*! Start Memory Map Register */
ಪೂರ್ಣಾಂಕ* endmm    =  (ಪೂರ್ಣಾಂಕ*) ENDMM; /*! End Memory Map Register */

/** @fn void set_qspi_shakti32(int* addr, int val)
 * @brief Writes 32 bit value into QSPI register.
 * @details Writes 32 bit value into passed address QSPI register.
 * @param int* addr --- Addresss where the data (val) needs to be written
 * @param int val ---  Data which needs to be written.
 */
ಶೂನ್ಯ ಗಣ_qspi_shakti32(ಪೂರ್ಣಾಂಕ* addr, ಪೂರ್ಣಾಂಕ val)
{
	*addr = val;
}

/** @fn void set_qspi_shakti16(int16_t* addr, int16_t val)
 * @brief Writes 16 bit value 
 * @details Writes 16 bit value into 16bit QSPI register 
 * @param 16bit int* addr --- Addresss where the data (val) needs to be written
 * @param 16bit int val ---  Data which needs to be written.
 */
ಶೂನ್ಯ ಗಣ_qspi_shakti16(int16_t* addr, int16_t val)
{
	*addr = val;
}

/** @fn void set_qspi_shakti8(char* addr, char val) 
 * @brief Writes 8 bit value.
 * @details Writes 8 bit value into 8 bit qspi register.
 * @param char* addr --- Addresss where the data (val) needs to be written
 * @param char val ---  Data which needs to be written.
 */
ಶೂನ್ಯ ಗಣ_qspi_shakti8(ಅಕ್ಷರ* addr, ಅಕ್ಷರ val)
{
	*addr= val;
}

/** @fn int get_qspi_shakti(int* addr)
 * @brief reads from qspi register
 * @details Reads from the passed QSPI register and returns the value.
 * @param int* addr --- 32 bit Read Addresss  
 * @return Read value -- Read value from the passed value.
 */
ಪೂರ್ಣಾಂಕ get_qspi_shakti(ಪೂರ್ಣಾಂಕ* addr)
{
	ಹಿಂತಿರುಗಿ *addr;
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
ಶೂನ್ಯ qspi_init(ಪೂರ್ಣಾಂಕ fsize, ಪೂರ್ಣಾಂಕ csht, ಪೂರ್ಣಾಂಕ prescaler, ಪೂರ್ಣಾಂಕ enable_interrupts, ಪೂರ್ಣಾಂಕ fthreshold, ಪೂರ್ಣಾಂಕ ck_ಬಹುಲಕ){
	ಪೂರ್ಣಾಂಕ int_ಸದಿಶ = enable_interrupts? (CR_TOIE|CR_SMIE|CR_FTIE|CR_TCIE|CR_TEIE) : 0; 
	ಗಣ_qspi_shakti32(dcr,(DCR_FSIZE(fsize)|DCR_CSHT(csht)|DCR_CKMODE(ck_ಬಹುಲಕ))); 
	ಗಣ_qspi_shakti32(cr,(CR_PRESCALER(prescaler)|int_ಸದಿಶ|CR_FTHRES(fthreshold)|CR_EN));
}

/** @fn void reset_interrupt_flags()
 * @brief Resets interrupt flags.
 * @details Before carrying out any flash access operations, the interrupt flags are cleared.
 */
ಶೂನ್ಯ reset_ಅಡಚಣೆ_flags(){
	ಗಣ_qspi_shakti32(fcr,(FCR_CTOF|FCR_CSMF|FCR_CTCF|FCR_CTEF)); //Resetting all the flags
}

/** @fn int wait_for_tcf(int status)
 * @brief Wait for the transfer complete flag.
 * @details WCF bit status register indicates the completion of flash 
 *  operation. The same is cheked here.
 * @param int status register read value.
 * @return Zero on success else -1
 */
ಪೂರ್ಣಾಂಕ wait_for_tcf(ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_3){
	ಪೂರ್ಣಾಂಕ timeout = DEF_TIMEOUT; 

	ಸ್ಥಿತಿ_3 = get_qspi_shakti(sr);

	//    printf("status : %d looping?\n",status);

	ಆಗ(!( ಸ್ಥಿತಿ_3 & 0x02 ) && --timeout){
		waitfor(1000);
		ಸ್ಥಿತಿ_3=get_qspi_shakti(sr);
		ಬರೆ("status: %08x in loop %d \n",ಸ್ಥಿತಿ_3, !(ಸ್ಥಿತಿ_3 & 0x02));
	}
	ಆದರೆ(timeout==0){
		ಬರೆ("Request Timed out\n");
		ಹಿಂತಿರುಗಿ -1;
	}
	ಹಿಂತಿರುಗಿ 0;
}

/** @fn int check_fail_bit()
 * @brief Checks the value of fail_bit.
 * @details Checks the fail bit whether the value is zero or not.
 */
ಪೂರ್ಣಾಂಕ check_fail_ಬಿಟ್(ಶೂನ್ಯ){
	ಆದರೆ(fail_ಬಿಟ್){
		fail_ಬಿಟ್ = 0;
		ಹಿಂತಿರುಗಿ -1;
	}
	ಇಲ್ಲದಿದ್ದರೆ{
		fail_ಬಿಟ್ = 0;
		ಹಿಂತಿರುಗಿ 0;
	}
}

/** @fn int flashReadStatusRegister()
 * @brief Reads flash status register
 * @details Reads flash status register contents
 * @return Status register value on success; else -1
 */
ಪೂರ್ಣಾಂಕ flash_Read_ಸ್ಥಿತಿ_ರಿಜಿಸ್ಟರ್(){
	//    printf("\tReading the Status bits of the Flash\n");
	ಗಣ_qspi_shakti32(dlr,4);
	ಗಣ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x05)|CCR_DMODE(SINGLE)));

	ಸ್ಥಿತಿ_3 = 0;
	waitfor(1000);
	ಪೂರ್ಣಾಂಕ ret = wait_for_tcf(ಸ್ಥಿತಿ_3);
	waitfor(100);
	ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ = get_qspi_shakti(dr);
	//	printf("Read status register value %08x \n", value);
	reset_ಅಡಚಣೆ_flags();
	ಆದರೆ(ret){
		ಬರೆ("\tRead Status Register Failed\n");
		fail_ಬಿಟ್ = 1;
		ಹಿಂತಿರುಗಿ -1;
	}
	ಇಲ್ಲದಿದ್ದರೆ
		ಹಿಂತಿರುಗಿ ಮೌಲ್ಯ;
}

/** @fn int wait_for_wip()
 * @brief Wait till a flash access is complete.
 * @details Reads the WIP bit in the status register to check the completion of flash access.
 * Useful during flash write operations.
 * @return Zero on Success
 */
ಪೂರ್ಣಾಂಕ wait_for_wip(ಶೂನ್ಯ){
	ಪೂರ್ಣಾಂಕ status1;
	ಮಾಡು{
		//  printf("\t Waiting for Wip \n");
		status1 = flash_Read_ಸ್ಥಿತಿ_ರಿಜಿಸ್ಟರ್(0x05);
		ಆದರೆ(check_fail_ಬಿಟ್())
			ಹಿಂತಿರುಗಿ -1;
		ಆದರೆ(status1 & 0x0){
			ಬರೆ("\tQSPI: Programming Error - Diagnose\n");
			ಹಿಂತಿರುಗಿ -1;
		}
		waitfor(20000);
	}ಆಗ(status1 & 0x01);
	//    printf("\t QSPI: Page Program/Erase Command Successfully Completed\n");
	ಹಿಂತಿರುಗಿ 0;
}

/** @fn int micron_write_enable(int status)
 * @brief Enables the micron flash for write operation.
 * @details Enables micron flash for programming flash data.
 * @param int status --- Write enable status.
 * @return Zero on Success
 */
ಪೂರ್ಣಾಂಕ micron_write_enable(ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_3){
	//  printf("\tWrite Enable\n");
	ಗಣ_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x06)));
	ಪೂರ್ಣಾಂಕ ret = wait_for_tcf(ಸ್ಥಿತಿ_3); //Indicating the completion of command -- Currently polling
	//  printf("Status : %d dcr : %d cr: %d ccr: %d \n",status,*dcr,*cr,*ccr);
	ಹಿಂತಿರುಗಿ ret;
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
ಪೂರ್ಣಾಂಕ ಪುಟ_ಕಾರ್ಯಕ್ರಮ_Single_SPI(ಪೂರ್ಣಾಂಕ value1, ಪೂರ್ಣಾಂಕ value2, ಪೂರ್ಣಾಂಕ value3, ಪೂರ್ಣಾಂಕ value4, ಪೂರ್ಣಾಂಕ ವಿಳಾಸ){
	ಆದರೆ(micron_write_enable(ಸ್ಥಿತಿ_3)){
		ಬರೆ("Panic: Write Enable Command Failed to execute");
		ಹಿಂತಿರುಗಿ -1;
	}
	reset_ಅಡಚಣೆ_flags(); 

	ಗಣ_qspi_shakti32(dlr,DL(16));
	// set_qspi_shakti32(ccr,(CCR_DDRM | CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x12))); 
	ಗಣ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x12)));
	ಗಣ_qspi_shakti32(ar, ವಿಳಾಸ);        
	ಬರೆ(" Address written %d \n",ವಿಳಾಸ); 
	ಗಣ_qspi_shakti32(dr,value1);
	ಬರೆ(" Value 1 written %d \n",value1);
	ಗಣ_qspi_shakti32(dr,value2);
	ಬರೆ(" Value 2 written %d \n",value2);
	ಗಣ_qspi_shakti32(dr,value3);
	ಬರೆ(" Value 3 written %d \n",value3);
	ಗಣ_qspi_shakti32(dr,value4);
	ಬರೆ(" Value 4 written %d \n",value4);
	waitfor(150); 
	wait_for_tcf(ಸ್ಥಿತಿ_3);
	reset_ಅಡಚಣೆ_flags();
	ಹಿಂತಿರುಗಿ wait_for_wip(); // Function which checks if WIP is done, indicating completion of Page Program
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
ಪೂರ್ಣಾಂಕ ಪುಟ_ಕಾರ್ಯಕ್ರಮ_Quad_SPI(ಪೂರ್ಣಾಂಕ value1, ಪೂರ್ಣಾಂಕ value2, ಪೂರ್ಣಾಂಕ value3, ಪೂರ್ಣಾಂಕ value4, ಪೂರ್ಣಾಂಕ ವಿಳಾಸ){
	ಆದರೆ(micron_write_enable(ಸ್ಥಿತಿ_3)){
		ಬರೆ("Panic: Write Enable Command Failed to execute");
		ಹಿಂತಿರುಗಿ -1;
	}
	reset_ಅಡಚಣೆ_flags(); 

	ಗಣ_qspi_shakti32(dlr,DL(16));
	// set_qspi_shakti32(ccr,(CCR_DDRM | CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x12))); 
	ಗಣ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(QUAD)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x34))); 
	ಗಣ_qspi_shakti32(ar, ವಿಳಾಸ);
	ಗಣ_qspi_shakti32(dr,value1);
	ಗಣ_qspi_shakti32(dr,value2);
	ಗಣ_qspi_shakti32(dr,value3);
	ಗಣ_qspi_shakti32(dr,value4);
	waitfor(150); 
	wait_for_tcf(ಸ್ಥಿತಿ_3);
	reset_ಅಡಚಣೆ_flags();
	ಹಿಂತಿರುಗಿ wait_for_wip(); // Function which checks if WIP is done, indicating completion of Page Program
}

/** @fn int flashIdentificationDevice()
 * @brief Reads flash id code.
 * @details Reads flash identification code from the flash device and checks whether it valid.
 * @return Zero on success else -1
 */
ಪೂರ್ಣಾಂಕ flashIdentificationDevice(ಶೂನ್ಯ){
	log_debug("\tReading the ID register and discovering the Flash Device\n");
	ಗಣ_qspi_shakti32(dlr,4);
	ಗಣ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x90)|CCR_ADSIZE(THREEBYTE)|CCR_ADMODE(SINGLE)|CCR_DMODE(SINGLE)));
	ಗಣ_qspi_shakti32(ar, 0);
	ಸ್ಥಿತಿ_3 = 0; // Useless Variable but still!!!!
	ಪೂರ್ಣಾಂಕ ret = wait_for_tcf(ಸ್ಥಿತಿ_3);
	ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ = get_qspi_shakti(dr);
	log_info("\t device id %x\n",ಮೌಲ್ಯ);
	reset_ಅಡಚಣೆ_flags();
	ಆದರೆ(ಮೌಲ್ಯ == MEM_TYPE_N25Q256_ID){
		ಬರೆ("\tN25Q256 Device Detected \n");
		ಹಿಂತಿರುಗಿ 0;
	}
	ಇಲ್ಲದಿದ್ದರೆ{
		log_fatal("\t Device Not Detected - Diagnose %08x\n",ಮೌಲ್ಯ);
		ಹಿಂತಿರುಗಿ -1;
	}
}

/** @fn int flashMemInit()
 * @brief Initialises flash memory 
 * @details Initialises flash device and check for id code.
 * @return Zero on success else -1
 */
ಪೂರ್ಣಾಂಕ flashMemInit(){  //Supposedly a set of routines to check if the memory/interface or whatever is proper
	ಪೂರ್ಣಾಂಕ ret = flashIdentificationDevice();
	ಆದರೆ(ret==-1){
		log_fatal("Flash Mem Init Failed -- Quitting Program, Diagnose");
		ಹಿಂತಿರುಗಿ ret;
	}
	ಇಲ್ಲದಿದ್ದರೆ log_debug("Flash Mem Init Success\n");
	ಹಿಂತಿರುಗಿ 0;
	//to fill in code
}


/** @fn int flashReadFlagRegister()
 * @brief Reads flash read flag. 
 * @details Reads the flash flag register.
 * @warning Not implemented now. Reserve for future.
 */
ಪೂರ್ಣಾಂಕ flash_Read_Flag_ರಿಜಿಸ್ಟರ್(ಶೂನ್ಯ){
	ಹಿಂತಿರುಗಿ 0;
}

/** @fn int flashWriteEnable()
 * @brief Enables flash enable bit
 * @details For any write operation into to flash device (erase, program, etc.)
 *        this enable bit needs to be enabled.
 * @return TCF status
 */
ಪೂರ್ಣಾಂಕ flashWriteEnable(ಶೂನ್ಯ){
	ಬರೆ("\tWrite Enable\n");
	ಗಣ_qspi_shakti32(ccr,(CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x06)));
	ಪೂರ್ಣಾಂಕ ret = wait_for_tcf(0); //Indicating the completion of command -- Currently polling
	reset_ಅಡಚಣೆ_flags();
	ಹಿಂತಿರುಗಿ ret; 
}

/** @fn int flashEnable4ByteAddressingMode()
 * @brief Selects the addressed mode.
 * @details Before accessing flash device, the number of bits used for (Q)SPI needs to be programmed.
 * @return Status of the performed operation; else -1
 */
ಪೂರ್ಣಾಂಕ flash_Enable4_Byte_Addressing_ಬಹುಲಕ(ಶೂನ್ಯ){  //Enable 4-byte addressing Mode and read the status to verify that it has happened correctly

	ಆದರೆ(flashWriteEnable()){
		ಬರೆ("\t Write Enable Failed \n");
		ಹಿಂತಿರುಗಿ -1;
	}
	waitfor(100);
	ಗಣ_qspi_shakti32(ccr,(CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xB7)));
	//  int status =0; 
	ಸ್ಥಿತಿ_3 = 0;
	ಪೂರ್ಣಾಂಕ ret = wait_for_tcf(ಸ್ಥಿತಿ_3);
	reset_ಅಡಚಣೆ_flags();
	waitfor(100);
	//Checking Phase
	ಸ್ಥಿತಿ_3 = flash_Read_ಸ್ಥಿತಿ_ರಿಜಿಸ್ಟರ್();
	ಬರೆ("\t Status Value: %08x\n",ಸ್ಥಿತಿ_3);
	ಆದರೆ(ಸ್ಥಿತಿ_3 & 1)
		ಬರೆ("\t 4-Byte Addressing Mode is Enabled\n");
	ಇಲ್ಲದಿದ್ದರೆ
		ಬರೆ("\t 4-byte Addressing mode not Enabled\n");
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
ಪೂರ್ಣಾಂಕ flashReadSingleSPI(ಪೂರ್ಣಾಂಕ dummy_ಚಕ್ರಗಳು, ಪೂರ್ಣಾಂಕ read_ವಿಳಾಸ, ಪೂರ್ಣಾಂಕ instruction, ಪೂರ್ಣಾಂಕ ದತ್ತಾಂಶ_ಪದಗಳು, ಪೂರ್ಣಾಂಕ adsize){
	ಗಣ_qspi_shakti32(dlr,ದತ್ತಾಂಶ_ಪದಗಳು);
	ಗಣ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(SINGLE)|CCR_DCYC(dummy_ಚಕ್ರಗಳು)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_ADSIZE(adsize)|CCR_INSTRUCTION(instruction)));
	ಗಣ_qspi_shakti32(ar,read_ವಿಳಾಸ);
	ಸ್ಥಿತಿ_3 = 0;
	ಪೂರ್ಣಾಂಕ ret = wait_for_tcf(ಸ್ಥಿತಿ_3);
	ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ = get_qspi_shakti(dr);
	ಬರೆ("\tThe Read Value: %08x\n",ಮೌಲ್ಯ);
	//    printf("\tThe Read Value: %08x\n",value);
	ಆದರೆ(ret){
		ಬರೆ("\t Read Value Failed \n");
		ಹಿಂತಿರುಗಿ -1;
	}
	reset_ಅಡಚಣೆ_flags();
	ಹಿಂತಿರುಗಿ ಮೌಲ್ಯ;
}

/** @fn int flashReadDualSPI(int address, int data_length)
 * @brief  Reads flash device over two io lines SPI.
 * @details Reads the flash device over two io lines for spi (IO1, IO2, CS, CLK) data
 * @param int address --- Address which needs to be read.
 * @param int data_length --- Number of Data bytes (data_words + 1) needs to be read 
 * @return Status of the performed operation; else -1
 */
ಪೂರ್ಣಾಂಕ flashReadDualSPI(ಪೂರ್ಣಾಂಕ ವಿಳಾಸ, ಪೂರ್ಣಾಂಕ ದತ್ತಾಂಶ_ಉದ್ದಳತೆ){
	ಗಣ_qspi_shakti32(dlr,ದತ್ತಾಂಶ_ಉದ್ದಳತೆ); //DLR
	ಗಣ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(DOUBLE)|CCR_DCYC(3)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBB)));
	ಗಣ_qspi_shakti32(ar,ವಿಳಾಸ); 
	//    printf("Status : %08x dcr : %08x cr : %08x ccr : %08x dlr: %08x ar: %08x\n",status,*dcr,*cr,*ccr,*dlr,*ar);
	ಪೂರ್ಣಾಂಕ ret = wait_for_tcf(ಸ್ಥಿತಿ_3);
	ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ = get_qspi_shakti(dr);
	ಬರೆ("\tThe Read Value: %08x\n",ಮೌಲ್ಯ);	
	ಆದರೆ(ret){
		ಬರೆ("\t QSPI: Read Value failed\n");
		ಹಿಂತಿರುಗಿ -1;
	}
	//*config_string = get_qspi_shakti(dr);
	//printf("\t Read Data is %08x\n",read_data);
	reset_ಅಡಚಣೆ_flags();
	ಹಿಂತಿರುಗಿ ಮೌಲ್ಯ;
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
ಪೂರ್ಣಾಂಕ flashReadQuadSPI(ಪೂರ್ಣಾಂಕ dummy_ಚಕ್ರಗಳು, ಪೂರ್ಣಾಂಕ read_ವಿಳಾಸ, ಪೂರ್ಣಾಂಕ instruction, ಪೂರ್ಣಾಂಕ ದತ್ತಾಂಶ_ಪದಗಳು, ಪೂರ್ಣಾಂಕ adsize){
	ಗಣ_qspi_shakti32(dlr,ದತ್ತಾಂಶ_ಪದಗಳು);
	ಗಣ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DCYC(dummy_ಚಕ್ರಗಳು)|CCR_ADSIZE(adsize)|CCR_ADMODE(QUAD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(instruction)));
	ಗಣ_qspi_shakti32(ar,read_ವಿಳಾಸ);
	ಸ್ಥಿತಿ_3 = 0;
	ಪೂರ್ಣಾಂಕ ret = wait_for_tcf(ಸ್ಥಿತಿ_3);
	ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ_1 = get_qspi_shakti(dr);
	ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ_2_2 = get_qspi_shakti(dr);
	ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ_3 = get_qspi_shakti(dr);
	ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ_4 = get_qspi_shakti(dr);
	ಬರೆ("\tThe Read Value: %08x, %08x, %08x and %08x \n",ಮೌಲ್ಯ_1,ಮೌಲ್ಯ_2_2,ಮೌಲ್ಯ_3,ಮೌಲ್ಯ_4);
	ಆದರೆ(ret){
		ಬರೆ("\t Read Value Failed \n");
		ಹಿಂತಿರುಗಿ -1; 
	}   
	reset_ಅಡಚಣೆ_flags();
	ಹಿಂತಿರುಗಿ ಮೌಲ್ಯ_1;
}

/** @fn int flashSingleSPIXip(int addr, int* dest_addr) 
 * @brief Reads over single SPI XIP
 * @details Generic Read for xip SPI Read.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on success.
 */
ಪೂರ್ಣಾಂಕ flashSingleSPIXip(ಪೂರ್ಣಾಂಕ addr, ಪೂರ್ಣಾಂಕ* dest_addr){
	ಗಣ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(SINGLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(7)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x0C)));
	ಗಣ_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_ಬಹುಲಕ_BYTE(0x00)|DCR_CKMODE(1)));
	ಗಣ_qspi_shakti32(dlr,0x4);
	ಗಣ_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	ಸ್ಥಿತಿ_3=0;
	wait_for_tcf(ಸ್ಥಿತಿ_3);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	ಬರೆ("\n Fisrt value obtained through single read : %d \n ",*dest_addr);
	reset_ಅಡಚಣೆ_flags(); 
	ಬರೆ("\t Trying XIP now\n");
	ಗಣ_qspi_shakti32(ccr, (CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(SINGLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(7)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x0C)));
	ಗಣ_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_ಬಹುಲಕ_BYTE(0x00)|DCR_CKMODE(1))); 
	waitfor(25);
	ಹಿಂತಿರುಗಿ 0;
}

/** @fn int flashSingleSPIDDRXip(int addr, int* dest_addr)  
 * @brief Reads over DDR XIP mode.
 * @details Reads for DDR based XIP mode.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
ಪೂರ್ಣಾಂಕ flashSingleSPIDDRXip(ಪೂರ್ಣಾಂಕ addr, ಪೂರ್ಣಾಂಕ* dest_addr){
	ಗಣ_qspi_shakti32(ccr,(CCR_DDRM|CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(SINGLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(15)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x0E)));
	ಗಣ_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_ಬಹುಲಕ_BYTE(0x00)|DCR_CKMODE(1)));
	ಗಣ_qspi_shakti32(dlr,0x4);
	ಗಣ_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	ಸ್ಥಿತಿ_3=0;
	wait_for_tcf(ಸ್ಥಿತಿ_3);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	reset_ಅಡಚಣೆ_flags(); 
	ಬರೆ("\t Trying XIP now\n");
	ಗಣ_qspi_shakti32(ccr, (CCR_DDRM|CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(SINGLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(14)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x0E)));
	ಗಣ_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_ಬಹುಲಕ_BYTE(0x00)|DCR_CKMODE(1))); 
	waitfor(25);
	ಹಿಂತಿರುಗಿ 0;
}

/** @fn int flashDualSPIXip(int addr, int* dest_addr)
 * @brief Reads over XIP mode.
 * @details Reads for XIP mode using two io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
ಪೂರ್ಣಾಂಕ flashDualSPIXip(ಪೂರ್ಣಾಂಕ addr, ಪೂರ್ಣಾಂಕ* dest_addr){
	ಗಣ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(DOUBLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(3)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBB)));
	ಗಣ_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_ಬಹುಲಕ_BYTE(0xA0)|DCR_CKMODE(1)));
	ಗಣ_qspi_shakti32(dlr,0x4);
	ಗಣ_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	ಸ್ಥಿತಿ_3=0;
	wait_for_tcf(ಸ್ಥಿತಿ_3);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	ಬರೆ("\n Fisrt value obtained through single read : %d \n ",*dest_addr);
	reset_ಅಡಚಣೆ_flags(); 
	ಬರೆ("\t Trying XIP now\n");
	ಗಣ_qspi_shakti32(ccr, (CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(DOUBLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(3)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(NDATA)));
	ಗಣ_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_ಬಹುಲಕ_BYTE(0xA0)|DCR_CKMODE(1))); 
	waitfor(25);
	ಹಿಂತಿರುಗಿ 0;
}

/** @fn int flashDualSPIDDRXip(int addr, int* dest_addr) 
 * @brief Reads over XIP mode.
 * @details Reads for DDR based XIP mode using two io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
ಪೂರ್ಣಾಂಕ flashDualSPIDDRXip(ಪೂರ್ಣಾಂಕ addr, ಪೂರ್ಣಾಂಕ* dest_addr){
	ಗಣ_qspi_shakti32(ccr,(CCR_DDRM|CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(DOUBLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(6)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBE)));
	ಗಣ_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_ಬಹುಲಕ_BYTE(0xA0)|DCR_CKMODE(1)));
	ಗಣ_qspi_shakti32(dlr,0x4);
	ಗಣ_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	ಸ್ಥಿತಿ_3=0;
	wait_for_tcf(ಸ್ಥಿತಿ_3);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	reset_ಅಡಚಣೆ_flags(); 
	ಬರೆ("\t Trying XIP now\n");
	ಗಣ_qspi_shakti32(ccr, (CCR_DDRM|CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(DOUBLE)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(6)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(DOUBLE)|CCR_IMODE(NDATA)));
	ಗಣ_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_ಬಹುಲಕ_BYTE(0xA0)|DCR_CKMODE(1))); 
	waitfor(25);
	ಹಿಂತಿರುಗಿ 0;
}

/** @fn int flashWriteVolatileConfigReg(int value) 
 * @brief Writes into flash volatile configuration register.
 * @details Writes the passed value into flash volatile configuration register.
 * @param int value needs to written into Write Volatile Config Register.
 * @return Zero on Success
 */
ಪೂರ್ಣಾಂಕ flashWriteVolatileConfigReg(ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ){
	ಬರೆ("\t Setting Volatile Configuration Register with the Value: %08x\n",ಮೌಲ್ಯ);
	ಆದರೆ(micron_write_enable(ಸ್ಥಿತಿ_3)){
		ಬರೆ("Panic: Write Enable Command Failed to execute\n");
		ಹಿಂತಿರುಗಿ -1;
	}
	reset_ಅಡಚಣೆ_flags();
	//	flashReadStatusRegister();
	ಗಣ_qspi_shakti32(dlr,DL(1));
	ಗಣ_qspi_shakti8(dr,ಮೌಲ್ಯ);  //The value to be written into the VECR register to enable XIP. Indicating XIP to operate in Quad Mode
	ಗಣ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x01)));
	waitfor(50);
	ಸ್ಥಿತಿ_3=0;
	ಪೂರ್ಣಾಂಕ ret = wait_for_tcf(ಸ್ಥಿತಿ_3);
	//    printf("Status : %d dcr : %d cr : %d ccr : %d dlr: %d dr: %d\n",status,*dcr,*cr,*ccr,*dlr,*dr);
	reset_ಅಡಚಣೆ_flags();
	waitfor(50);  //Giving Micron time to store the data
	ಹಿಂತಿರುಗಿ ret;
}

/** @fn int flashQuadSPIXip(int addr, int* dest_addr)
 * @brief Reads over XIP mode.
 * @details Reads for DDR based XIP mode using quad io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
ಪೂರ್ಣಾಂಕ flashQuadSPIXip(ಪೂರ್ಣಾಂಕ addr, ಪೂರ್ಣಾಂಕ* dest_addr){
	ಆದರೆ(flashWriteVolatileConfigReg(0x40404040)){
		ಬರೆ("\t Volatile Configuration Register not Set -- Diagnose\n");
		ಹಿಂತಿರುಗಿ -1;
	}
	ಸ್ಥಿತಿ_3 = wait_for_wip();
	ಬರೆ("\t qspi status register %08x\n",ಸ್ಥಿತಿ_3);
	reset_ಅಡಚಣೆ_flags();
	ಗಣ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(5)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xEC)));
	ಗಣ_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_ಬಹುಲಕ_BYTE(0xA0)|DCR_CKMODE(1)));
	ಗಣ_qspi_shakti32(dlr,0x4);
	ಗಣ_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	ಸ್ಥಿತಿ_3=0;
	wait_for_tcf(ಸ್ಥಿತಿ_3);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	reset_ಅಡಚಣೆ_flags(); 
	ಬರೆ("\t Trying XIP now\n");
	ಗಣ_qspi_shakti32(ccr, (CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(QUAD)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(5)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(NDATA)));
	ಗಣ_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_ಬಹುಲಕ_BYTE(0xA0)|DCR_CKMODE(1))); 
	waitfor(25);
	ಹಿಂತಿರುಗಿ 0;
}

/** @fn int flashQuadSPIDDRXip(int addr, int* dest_addr)
 * @brief Reads over XIP mode.
 * @details Reads for DDR based XIP mode using four io bits for data.
 * @param int addr --- Flash Address from where XIP reads needs to be performed.
 * @param int* dest_addr --- RAM location to where the data needs to be copied.
 * @return Zero on Success
 */
ಪೂರ್ಣಾಂಕ flashQuadSPIDDRXip(ಪೂರ್ಣಾಂಕ addr, ಪೂರ್ಣಾಂಕ* dest_addr){
	ಆದರೆ(flashWriteVolatileConfigReg(0x40404040)){
		ಬರೆ("\t Volatile Configuration Register not Set -- Diagnose\n");
		ಹಿಂತಿರುಗಿ -1;
	}
	ಸ್ಥಿತಿ_3 = wait_for_wip();
	ಬರೆ("\t qspi status register %08x\n",ಸ್ಥಿತಿ_3);
	reset_ಅಡಚಣೆ_flags();
	ಗಣ_qspi_shakti32(ccr,(CCR_DDRM|CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(10)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xEE)));
	ಗಣ_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_ಬಹುಲಕ_BYTE(0xA0)|DCR_CKMODE(1)));
	ಗಣ_qspi_shakti32(dlr,0x4);
	ಗಣ_qspi_shakti32(ar, addr); //Address where the Config_string is situated in the micron nand flash memory
	ಸ್ಥಿತಿ_3=0;
	wait_for_tcf(ಸ್ಥಿತಿ_3);
	waitfor(100); 
	*dest_addr = get_qspi_shakti(dr);
	reset_ಅಡಚಣೆ_flags(); 
	ಬರೆ("\t Trying XIP now\n");
	ಗಣ_qspi_shakti32(ccr, (CCR_DDRM|CCR_FMODE(CCR_FMODE_MMAPD)|CCR_DMODE(QUAD)|CCR_DUMMY_CONFIRMATION|CCR_DCYC(10)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(NDATA)));
	ಗಣ_qspi_shakti32(dcr,(DCR_FSIZE(27)|DCR_ಬಹುಲಕ_BYTE(0xA0)|DCR_CKMODE(1))); 
	waitfor(25);
	ಹಿಂತಿರುಗಿ 0;
}

/** @fn int flash_Write_disable()
 * @brief disables write operation
 * @details Write operation can be possible only after enabling write enable register.
 *       Here this is disabled using this function.
 * @return Zero on Success
 */
ಪೂರ್ಣಾಂಕ flash_Write_disable(ಶೂನ್ಯ){
	ಬರೆ("\tWrite disable\n");
	ಗಣ_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x04)));
	ಪೂರ್ಣಾಂಕ ret = wait_for_tcf(ಸ್ಥಿತಿ_3); //Indicating the completion of command -- Currently polling
	ಬರೆ("Status : %d dcr : %d cr: %d ccr: %d \n",ಸ್ಥಿತಿ_3,*dcr,*cr,*ccr);
	reset_ಅಡಚಣೆ_flags();
	ಹಿಂತಿರುಗಿ wait_for_wip();
}

/** @fn int eraseSector(int command, int address)
 * @brief Erases one sector 
 * @details Erases a complete sector which falls in the sector range.
 * @param int command --- Erase command (sector erase, block erase or chip erase)
 * @param int address --- Starting address of erase.
 * @return Zero on Success
 */
ಪೂರ್ಣಾಂಕ eraseSector(ಪೂರ್ಣಾಂಕ command, ಪೂರ್ಣಾಂಕ ವಿಳಾಸ){
	ಆದರೆ(micron_write_enable(ಸ್ಥಿತಿ_3)){
		ಬರೆ("Panic: Write Enable Command Failed to execute");
		ಹಿಂತಿರುಗಿ -1;
	}
	reset_ಅಡಚಣೆ_flags();
	ಗಣ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(command)));
	ಗಣ_qspi_shakti32(ar,ವಿಳಾಸ);
	waitfor(150);
	ಪೂರ್ಣಾಂಕ ret = wait_for_tcf(ಸ್ಥಿತಿ_3);
	reset_ಅಡಚಣೆ_flags();
	ಹಿಂತಿರುಗಿ wait_for_wip(); //For sector erase maybe estat should be checked
}

/** @fn int micron_volatile_write_enable(int status) 
 * @brief Enable for volatile write.
 * @details Enables micron flash for programming volatile config. register.
 * @param int --- status register value.
 * @return Zero on Success
 */
ಪೂರ್ಣಾಂಕ micron_volatile_write_enable(ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_3){
	ಬರೆ("\tVolatile Write Enable\n");
	ಗಣ_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x50)));
	ಪೂರ್ಣಾಂಕ ret = wait_for_tcf(ಸ್ಥಿತಿ_3); //Indicating the completion of command -- Currently polling
	ಬರೆ("Status : %d dcr : %d cr: %d ccr: %d \n",ಸ್ಥಿತಿ_3,*dcr,*cr,*ccr);
	ಹಿಂತಿರುಗಿ ret;
}

/** @fn int micron_enable_4byte_addressing(int status) 
 * @brief Enables micron flash for 4 byte addressing.
 * @details Address can be passed as 3 bytes or 4 bytes before read or write 
 * operation. This function sets the number of address bytes to 4 bytes.
 * @param int --- status register value
 * @return Zero on Success
 */
ಪೂರ್ಣಾಂಕ micron_enable_4byte_addressing(ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_3){
	ಬರೆ("\t Enable 4 byte address \n");
	ಗಣ_qspi_shakti32(ccr,(CCR_ADSIZE(FOURBYTE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xB7)));
	ಪೂರ್ಣಾಂಕ ret = wait_for_tcf(ಸ್ಥಿತಿ_3); //Indicating the completion of command -- Currently polling
	ಬರೆ("Status : %d dcr : %d cr: %d ccr: %d \n",ಸ್ಥಿತಿ_3,*dcr,*cr,*ccr);
	ಹಿಂತಿರುಗಿ ret;
}

/** @fn int micron_configure_xip_volatile(int status, int value)
 * @brief Configures the xip volatile config. register.
 * @details Configures the volatile config. register for xip Read mode.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
ಪೂರ್ಣಾಂಕ micron_configure_xip_volatile(ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_3, ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ){
	log_debug("\tWrite Volatile Configuration Register\n");
	ಗಣ_qspi_shakti32(dlr,DL(1));
	ಗಣ_qspi_shakti8(dr,ಮೌಲ್ಯ);  //The value to be written into the VECR register to enable XIP. Indicating XIP to operate in Quad Mode
	ಗಣ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDWR)|CCR_DMODE(SINGLE)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x81)));
	waitfor(50);
	ಪೂರ್ಣಾಂಕ ret = wait_for_tcf(ಸ್ಥಿತಿ_3);
	ಬರೆ("Status : %d dcr : %d cr : %d ccr : %d dlr: %d dr: %d\n",ಸ್ಥಿತಿ_3,*dcr,*cr,*ccr,*dlr,*dr);
	waitfor(50);  //Giving Micron time to store the data
	ಹಿಂತಿರುಗಿ ret;
}

/** @fn int micron_disable_xip_volatile(int status, int value)
 * @brief Configures(disables) the xip volatile config. register.
 * @details Configures(disables) the volatile config. register for xip Read mode.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
ಪೂರ್ಣಾಂಕ micron_disable_xip_volatile(ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_3, __attribute__ ((ಬಳಸದ)) ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ){
	log_debug("\tWrite Volatile Configuration Register to exit XIP\n");
	ಗಣ_qspi_shakti32(cr,(CR_PRESCALER(0x3)|CR_TOIE|CR_TCIE|CR_TEIE|CR_SMIE|CR_FTIE|CR_ABORT|CR_EN));
	waitfor(30);
	qspi_init(27,0,3,1,15,1);
	ಗಣ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_DMODE(QUAD)|CCR_DUMMY_ಬಿಟ್|CCR_DUMMY_CONFIRMATION|CCR_DCYC(8)|CCR_ADSIZE(FOURBYTE)|CCR_ADMODE(QUAD)|CCR_IMODE(NDATA)));
	ಗಣ_qspi_shakti32(ar,0x00000); //Dummy address 
	ಗಣ_qspi_shakti32(dlr,1);

	ಪೂರ್ಣಾಂಕ ret = wait_for_tcf(ಸ್ಥಿತಿ_3);
	ಪೂರ್ಣಾಂಕ ತಾತ್ಕಾಲಿಕ_ದತ್ತಾಂಶ = get_qspi_shakti(dr);

	waitfor(50);
	reset_ಅಡಚಣೆ_flags();
	ಹಿಂತಿರುಗಿ ret;
}

/** @fn int micron_read_id_cmd(int status, int value)
 * @brief Reads the id of the micron flash.
 * @details Micron flash is having a fixed value as ID during production. This 
 * value is read to confirm proper flash device.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
ಪೂರ್ಣಾಂಕ micron_read_id_cmd(ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_3, ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ){
	log_debug("\tRead ID Command to see if the Protocol is Proper\n");
	ಗಣ_qspi_shakti32(dlr,4);
	ಗಣ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0x9E)|CCR_DMODE(SINGLE)));
	ಪೂರ್ಣಾಂಕ ret = wait_for_tcf(ಸ್ಥಿತಿ_3);
	ಮೌಲ್ಯ = get_qspi_shakti(dr);
	ಬರೆ("Read ID: %08x",ಮೌಲ್ಯ);
	ಹಿಂತಿರುಗಿ ret;
}

/** @fn int micron_read_configuration_register(int status, int value)
 * @brief Reads configuration register. 
 * @details The configurartion register is read using this function.
 * @param int --- status register value
 * @param int value  --- Values that needs to be configured.
 * @return Zero on Success
 */
ಪೂರ್ಣಾಂಕ micron_read_configuration_ರಿಜಿಸ್ಟರ್(ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_3, ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ){
	ಬರೆ("\tRead ID Command to see if the Protocol is Proper\n");
	ಗಣ_qspi_shakti32(dlr,4);
	ಗಣ_qspi_shakti32(ccr,(CCR_FMODE(CCR_FMODE_INDRD)|CCR_IMODE(SINGLE)|CCR_INSTRUCTION(0xBE)|CCR_DMODE(SINGLE)));
	ಪೂರ್ಣಾಂಕ ret = wait_for_tcf(ಸ್ಥಿತಿ_3);
	ಮೌಲ್ಯ = get_qspi_shakti(dr);
	log_debug("Configuration Register Value: %08x",ಮೌಲ್ಯ);
	ಹಿಂತಿರುಗಿ ret;
}
