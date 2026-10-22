/**************************************************************************
 * Project           		: shakti devt board
 * Name of the file	     	: i2c_driver.c
 * Brief Description of file    : Demonstartes the working of i2c protocol.
 * Name of Author               : Kotteeswaran
 * Email id                     : kottee.1@gmail.com

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
  @file i2c_driver.c
  @brief Contains the driver routines for i2c driver using dedicated I2C pins.
  @detail This file has the driver support for i2c using dedicated i2c pins.
  This file contains init, configure, read and write routines*/

/* Enable these bits only when corresponding interrupt is needed.*/

#ಅನ್ತರ್ಭಾವ "i2c.h"//Includes the definitions of i2c communication protocol//
#ಅನ್ತರ್ಭಾವ "log.h"
#ಅನ್ತರ್ಭಾವ "utils.h"

/* Enable these bits only when corresponding interrupt is needed.*/

//#define USE_SA_WRITE_I2C_INTERRUPT 1
//#define USE_WRITE_I2C_INTERRUPT 1
//#define USE_READ_I2C_INTERRUPT 1

i2c_struct *i2c_instance[MAX_I2_C_ಎಣಿಕೆ];

/**
 * @fn void i2c_init()
 * @brief Initialises the i2c modules.
 * @details Initialises the i2c array modules to the max. no of i2c modules present
 */
ಶೂನ್ಯ i2c_init()
{
	ಗಾಗಿ(ಪೂರ್ಣಾಂಕ i=0; i< MAX_I2_C_ಎಣಿಕೆ; i++)
	{
		i2c_instance[i] = (i2c_struct*) (I2_C0_ತಳ + (i * I2_C_ಸ್ಥಾನಾಂತರ));
	}
}

/** @fn int config_i2c(i2c_struct * instance, unsigned char prescale_div, unsigned char scl_div)
 * @brief This routine configures the serial clock frequency count and
 *  prescaler count.
 * @details There are 4 registers which are configurable. This function
 *   writes into the registr based on the passed address. he serial clock count
 *   and prescalar count decides the frequency (sck) that needs to be used for
 *   the I2C serial communication. Then resets status register.
 * @param i2c_struct*
 * @param unsigned char prescale_div
 * @param unsigned char scl_div
 * @return REturns 0 if success; else returns -ENXIO.
 */
ಪೂರ್ಣಾಂಕ config_i2c(i2c_struct * instance, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ prescale_div, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ scl_div)
{
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ತಾತ್ಕಾಲಿಕ = 0;
	log_debug("\tI2C: Initializing the Controller\n");

	ಆದರೆ(prescale_div  != instance->prescale )
	{
		instance->prescale = prescale_div;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG 
		ತಾತ್ಕಾಲಿಕ = instance->prescale;

		ಆದರೆ((ತಾತ್ಕಾಲಿಕ | 0x00) != prescale_div)
		{
			log_error("\t Failed to write Prescale division Written Value: 0x%x; read Value: 0x%x\n", prescale_div, instance->prescale);
			ಹಿಂತಿರುಗಿ -ENXIO;
		}
		ಇಲ್ಲದಿದ್ದರೆ
		{
			log_debug("\tPrescaler successfully initalized\n");
		}
#ಆದರೆ_ಅಂತ್ಯ
	}

	ಆದರೆ(scl_div != instance->scl )
	{
		instance->scl = scl_div;  //Setting the I2C clock value to be 1, which will set the clock for module and prescaler clock


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ DEBUG 
		ತಾತ್ಕಾಲಿಕ = instance->scl;

		/* Just reading the written value to see if all is well -- Compiler should not optimize this load!!! Compiler can just optimize the store to pointer address followed by load pointer to a register to just an immediate load to the register since clock register is not used anywhere -- but the purpose is lost. Don't give compiler optimizations */
		ಆದರೆ((ತಾತ್ಕಾಲಿಕ | 0x00) != scl_div)
		{
			log_error("\tClock initialization failed Write Value: 0x%x; read Value: 0x%x\n", scl_div, ತಾತ್ಕಾಲಿಕ);
			ಹಿಂತಿರುಗಿ -ENXIO;
		}
		ಇಲ್ಲದಿದ್ದರೆ
		{
			log_debug("\tClock successfully initalized\n");
		}
#ಆದರೆ_ಅಂತ್ಯ
	}

	/* S1=0x80 S0 selected, serial interface off */
	log_debug("\tClearing the status register. \n");
	instance->control = I2C_PIN;

	// Reading set control Register Value to ensure sanctity
	log_debug("\tReading Status Register \n");
	ತಾತ್ಕಾಲಿಕ = instance->control;

	//Check whether the status register is cleared or not.
	ಆದರೆ((ತಾತ್ಕಾಲಿಕ & 0x7f) != 0){
		log_error("\tDevice Not Recognized\n");
		ಹಿಂತಿರುಗಿ -ENXIO;
	}

	log_debug("\tWaiting for a specified time\n ");
	waitfor(900); //1 Second software wait -- Should be 900000 but setting to 900 now since simulation is already slow
	log_debug("\tDone Waiting \n ");
	log_info("\nControl: %x; Status: %x", instance->control, instance->ಸ್ಥಿತಿ_3);
	/* Enable Serial Interface */
	instance->control = I2C_IDLE;
	waitfor(900); //1 Second software wait -- Should be 900000 but setting to 900 now since simulation is already slow

	ತಾತ್ಕಾಲಿಕ = instance->ಸ್ಥಿತಿ_3;

	/* Check to see if I2C is really in Idle and see if we can access the status register -- If not something wrong in initialization. This also verifies if Control is properly written since zero bit will be initialized to zero*/
	ಆದರೆ(ತಾತ್ಕಾಲಿಕ != (I2C_PIN | I2C_BB)){
		log_error("\n\tInitialization failed; Status Reg: %x\n", ತಾತ್ಕಾಲಿಕ);
		ಹಿಂತಿರುಗಿ -ENXIO;
	}

	log_info("\tI2C Initialization success\n");
	ಹಿಂತಿರುಗಿ 0;
}

/**
 * @fn int wait_till_I2c_bus_free(i2c_struct * instance)
 * @brief wait for the i2c bus to be freee.
 * @details once a I2C Transaction is started, the bus needs to be freed for other devices
 *    to use the bus. This function checks the busy bit in status register to become free 
 *    for a particular time. If it becomes free, returns 0, else negative value.
 * @param i2c_struct*
 * @return Returns 0 if the bus becomes free; else returns ETIMEDOUT.
 */
ಪೂರ್ಣಾಂಕ wait_till_I2c_bus_free(i2c_struct * instance)
{
	log_debug("\tCheck for I2C Bus Busy to be free.\n");
	ಪೂರ್ಣಾಂಕ timeout = DEF_TIMEOUT;
	ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_3;

	ಸ್ಥಿತಿ_3 = instance->ಸ್ಥಿತಿ_3;

	ಆಗ (!(ಸ್ಥಿತಿ_3 & I2C_BB) && --timeout) {
		waitfor(20000); /* wait for 100 us */
		ಸ್ಥಿತಿ_3 = instance->ಸ್ಥಿತಿ_3;
	}

	ಆದರೆ (timeout == 0) {
		log_error("\t Bus busy wait - timed out. Resetting\n");
		ಹಿಂತಿರುಗಿ ETIMEDOUT;
	}

	ಹಿಂತಿರುಗಿ 0;
}

/**
 * @fn int wait_till_txrx_operation_Completes(i2c_struct * instance, int *status)
 * @brief  Waits in the loop till the i2c tx/rx operation completes
 * @details The PIN bit in the status register becomes high when tx/rx operation 
 *     starts and becomes low once done. This function checks whether tx/rx operaiton is complete or not. 
 * @param i2c_struct* 
 * @param int *status  --> contents of the status register
 * @return zero if success; else -ETIMEOUT
 */
ಪೂರ್ಣಾಂಕ wait_till_txrx_operation_Completes(i2c_struct * instance, ಪೂರ್ಣಾಂಕ *ಸ್ಥಿತಿ_3)
{

	ಪೂರ್ಣಾಂಕ timeout = DEF_TIMEOUT;

	*ಸ್ಥಿತಿ_3 = instance->ಸ್ಥಿತಿ_3;

	ಆಗ ((*ಸ್ಥಿತಿ_3 & I2C_PIN) && --timeout) {
		waitfor(10000); /* wait for 100 us */
		*ಸ್ಥಿತಿ_3 = instance->ಸ್ಥಿತಿ_3;
	}

	ಆದರೆ (timeout == 0){
		log_info("\tWait for pin timed out\n");
		ಹಿಂತಿರುಗಿ ETIMEDOUT;
	}

	waitfor(10000); /* wait for 100 us */
	log_debug("\n I2C tx_rx operation is completed");
	ಹಿಂತಿರುಗಿ 0;
}

/**
 * @fn int sendbytes(i2c_struct * instance, const char *buf, int count, int last, int eni)
 * @brief  writes "n" number of bits over i2c bus.
 * @details Called when the user wants to write n number of bits over i2c bus.
 * @param i2c_struct*  --- i2c structure pointer
 * @param const char *buf --- Pointer to buffer which contains the data to be written.
 * @param int count --- No of bytes to be written.
 * @param int last --- If 1, I2C stop command can be sent
 * @param int eni  --- External Interrupt Control
 * @return Returns number of bytes written else EREMOTEIO.
 */
ಪೂರ್ಣಾಂಕ sendbytes(i2c_struct * instance, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *buf, ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2, ಪೂರ್ಣಾಂಕ ಕೊನೆಯ, ಪೂರ್ಣಾಂಕ eni)
{
	ಪೂರ್ಣಾಂಕ wrcount, ಸ್ಥಿತಿ_3, timeout;
	ಬರೆ("\tStarting Write Transaction -- Did you create tri1 nets for SDA and SCL in verilog?\n");
	ಗಾಗಿ (wrcount=0; wrcount<ಎಣಿಕೆ_2; ++wrcount) {
		instance->ದತ್ತಾಂಶ_2 = buf[wrcount];
		timeout = wait_till_txrx_operation_Completes(instance, &ಸ್ಥಿತಿ_3);
		ಆದರೆ (timeout) {
			ಬರೆ("\tTimeout happened - Write did not go through the BFM -- Diagnose\n");
			instance->control = I2C_STOP;
			ಹಿಂತಿರುಗಿ EREMOTEIO;
		}
		ಆದರೆ (ಸ್ಥಿತಿ_3 & I2C_LRB) { // What error is this?
			instance->control = I2C_STOP;//~
			ಬರೆ("\tSome status check failing\n");
			ಹಿಂತಿರುಗಿ EREMOTEIO;
		}
	}
	ಆದರೆ (ಕೊನೆಯ){
		ಬರೆ("\tLast byte sent : Issue a stop\n");
		instance->control = I2C_STOP;
	}
	ಇಲ್ಲದಿದ್ದರೆ{
		ಬರೆ("\tSending Rep Start and doing some other R/W transaction\n");

		ಆದರೆ(!eni)
			instance->control = I2C_REPSTART;
		ಇಲ್ಲದಿದ್ದರೆ
			instance->control = I2C_REPSTART_ENI;
	}

	ಹಿಂತಿರುಗಿ wrcount;
}

/**
 * @fn int readbytes(i2c_struct * instance, char *buf, int count, int last)
 * @brief Reads "n" number of bytes from I2C Bus
 * @details Reads n number of bytes over I2C Bus and store teh same in 
 *          "buf" pointer.
 * @param i2c_struct*  --- i2c structure pointer
 * @param const char *buf --- Pointer to buffer which contains the read data.
 * @param int count --- No of bytes to be read.
 * @param int last --- If 1, I2C stop command can be sent
 * @return Returns number of bytest read over i2c bus. else -1.
 */
ಪೂರ್ಣಾಂಕ readbytes(i2c_struct * instance, ಅಕ್ಷರ *buf, ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2, ಪೂರ್ಣಾಂಕ ಕೊನೆಯ)
{
	ಪೂರ್ಣಾಂಕ i, ಸ್ಥಿತಿ_3;
	ಪೂರ್ಣಾಂಕ wfp;

	/* increment number of bytes to read by one -- read dummy byte */
	ಗಾಗಿ (i = 0; i <= ಎಣಿಕೆ_2; i++) {
		wfp = wait_till_txrx_operation_Completes(instance, &ಸ್ಥಿತಿ_3);
		ಆದರೆ (wfp) {
			instance->control = I2C_STOP;
			ಹಿಂತಿರುಗಿ -1;
		}

		ಆದರೆ ((ಸ್ಥಿತಿ_3 & I2C_LRB) && (i != ಎಣಿಕೆ_2)) {
			instance->control = I2C_STOP;
			ಬರೆ("\tNo ack\n");
			ಹಿಂತಿರುಗಿ -1;
		}

		ಆದರೆ (i)
		{
			buf[i - 1] = instance->ದತ್ತಾಂಶ_2;
			ಬರೆ("\n Read Value: %x", buf[i - 1]);
		}
		ಇಲ್ಲದಿದ್ದರೆ
			instance->ದತ್ತಾಂಶ_2 = !instance->ದತ್ತಾಂಶ_2; /* dummy read */

		ಆದರೆ (i == ಎಣಿಕೆ_2 - 1) {
			instance->control = I2C_ESO;
		} ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (i == ಎಣಿಕೆ_2) {
			ಆದರೆ (ಕೊನೆಯ)
				instance->control = I2C_STOP;
			ಇಲ್ಲದಿದ್ದರೆ
				instance->control = I2C_REPSTART_ENI;
		}

	}

	ಹಿಂತಿರುಗಿ i-1; //excluding the dummy read
}

/**
 * @fn int i2c_send_slave_address(i2c_struct * instance, unsigned char slaveAddress, unsigned char rdWrCntrl, unsigned long delay)
 * @brief  Performs the intilization of i2c slave.
 * @details Writes slave addresss into the i2b to start write or read operation.
 * @param i2c_struct*
 * @param unsigned char slaveAddress
 * @param unsigned char rdWrCntrl
 * @param unsigned long delay
 * @return Zero if success; else non zero
 */
ಪೂರ್ಣಾಂಕ i2c_send_slave_ವಿಳಾಸ(i2c_struct * instance, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ slave_ವಿಳಾಸ, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ rdWrCntrl, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay)
{
	ಪೂರ್ಣಾಂಕ timeout;
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ತಾತ್ಕಾಲಿಕ = 0;
	ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_3 = 0;

	delay = delay;

	ಆದರೆ(rdWrCntrl == 0)
		slave_ವಿಳಾಸ |= I2C_WRITE;
	ಇಲ್ಲದಿದ್ದರೆ
		slave_ವಿಳಾಸ |= I2C_READ;

	//Writing the slave address that needs to be written into data register.
	instance->ದತ್ತಾಂಶ_2 = slave_ವಿಳಾಸ;
	log_debug("\tSlave Address 0x%x written into data register\n", slave_ವಿಳಾಸ);

	//Reads back the data register to confirm
	ತಾತ್ಕಾಲಿಕ = instance->ದತ್ತಾಂಶ_2; //Reads the slave address from I2C controller

	ಆದರೆ(slave_ವಿಳಾಸ != (ಪೂರ್ಣಾಂಕ)ತಾತ್ಕಾಲಿಕ)
	{
		log_error("\tSlave address is not matching; Written Add. Value: 0x%x; Read Add. Value: 0x%x\n", slave_ವಿಳಾಸ, ತಾತ್ಕಾಲಿಕ);
		log_error("\n There is some issue in AXI interface. Please check.");
		ಹಿಂತಿರುಗಿ EAXI_ERROR;
	}

	//Waits till the bus becomes free.
	ಆಗ(wait_till_I2c_bus_free(instance))
	{
		log_error("\tError in Waiting for BB\n");
		ಹಿಂತಿರುಗಿ EI2C_BUS_ERROR;
	}


	//Send the start condition and slave address to slave
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ USE_SA_WRITE_I2_C_ಅಡಚಣೆ
	instance->control = I2_C_ಆರಂಭ; //Sending the slave address to the I2C slave
	waitfor(900);
	//Wait for PIN to become low.
	timeout = wait_till_txrx_operation_Completes(instance, &ಸ್ಥಿತಿ_3);
	ಆದರೆ (timeout) {//Asking the controller to send a start signal to initiate the transaction
		ಬರೆ("\tTimeout happened - Write did not go through the BFM -- Diagnose\n");
		instance->control = I2C_STOP; //~
		ಹಿಂತಿರುಗಿ EI2C_PIN_ERROR;
	}

	ಆದರೆ (ಸ್ಥಿತಿ_3 & I2C_LRB) {
		instance->control = I2C_STOP; //~
		ಬರೆ("\tSome status check failing\n");
		ಹಿಂತಿರುಗಿ EI2C_LRB_ERROR;
	}

#ಇಲ್ಲದಿದ್ದರೆ
	i2c_complete_flag = 0;

	instance->control = I2_C_ಆರಂಭ_ENI; //Sending the slave address to the I2C slave
	ಆಗ(!i2c_complete_flag);
	log_info("\n Slave Address Write Operation is complete.");
	i2c_complete_flag = 0;
#ಆದರೆ_ಅಂತ್ಯ

	ಹಿಂತಿರುಗಿ I2C_SUCCESS;
}

/**
 * @fn int i2c_write_data(i2c_struct * instance, unsigned char writeData, unsigned char delay)
 * @brief I does the reading or writing from the address specified .
 * @details Writes one byte to the slave I2C DEVICE.
 * @param i2c_struct*, 
 * @param unsigned char writedata
 * @param unsigned char delay
 * @return Returns Zeron on success; else -EREMOTEIO
 */
ಪೂರ್ಣಾಂಕ i2c_write_ದತ್ತಾಂಶ(i2c_struct * instance, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ write_ದತ್ತಾಂಶ, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay)
{
	ಪೂರ್ಣಾಂಕ timeout;
	ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_3 = 0;
	delay = delay;

	instance->ದತ್ತಾಂಶ_2= write_ದತ್ತಾಂಶ;

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ USE_WRITE_I2_C_ಅಡಚಣೆ
	timeout = wait_till_txrx_operation_Completes(instance, &ಸ್ಥಿತಿ_3);
	ಆದರೆ (timeout) {
		ಬರೆ("\tTimeout happened - Write did not go through the BFM -- Diagnose\n");
		instance->control = I2C_STOP; //~
		ಹಿಂತಿರುಗಿ EREMOTEIO;
	}

	ಆದರೆ (ಸ್ಥಿತಿ_3 & I2C_LRB)
	{ // What error is this?
		instance->control = I2C_STOP; //~
		ಬರೆ("\tSome status check failing\n");
		ಹಿಂತಿರುಗಿ EI2C_LRB_ERROR;
	}
#ಇಲ್ಲದಿದ್ದರೆ
	i2c_complete_flag = 0;
	instance->control = I2C_STOP_ENI; //Sending the sslave address to the I2C slave

	ಆಗ(!i2c_complete_flag);
	log_info("\n Write Operation is complete.");
	i2c_complete_flag = 0;
#ಆದರೆ_ಅಂತ್ಯ

	ಹಿಂತಿರುಗಿ I2C_SUCCESS;
}

/**
 * @fn int i2c_read_data(i2c_struct * instance, unsigned char *read_data, unsigned char delay)
 * @brief It does the reading or writing from the address specified .
 * @details Reads a byte of data over I2C bus from the passed I2C location.
 * @param i2c_struct*
 * @param unsigned char  *read_data
 * @param unsigned char delay
 * @return Zero on success; else -ETIMEOUT
 */
//#define READ_INTERRUPT 1
ಪೂರ್ಣಾಂಕ i2c_read_ದತ್ತಾಂಶ(i2c_struct * instance, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *read_ದತ್ತಾಂಶ_2, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay)
{
	ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_3 = 0;

	/* Make a dummy read as per spec of the I2C controller */

	*read_ದತ್ತಾಂಶ_2 = instance->ದತ್ತಾಂಶ_2; //~

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ USE_WRITE_I2_C_ಅಡಚಣೆ	
	i2c_complete_flag = 0;
	instance->control = I2C_REPSTART_ENI; //~

	ಆಗ(!i2c_complete_flag);
	*read_ದತ್ತಾಂಶ_2 = instance->ದತ್ತಾಂಶ_2;

	ಬರೆ("\n I2C Read Data = %x", i2c_read_ದತ್ತಾಂಶ);
#ಇಲ್ಲದಿದ್ದರೆ
	ಆಗ(wait_till_txrx_operation_Completes(instance, &ಸ್ಥಿತಿ_3))
	{
		ಬರೆ("\twaiting for pin\n");
		waitfor(delay);
	}
#ಆದರೆ_ಅಂತ್ಯ
	ಹಿಂತಿರುಗಿ I2C_SUCCESS;
}


/**
 * @fn int i2c_read_data_nack(i2c_struct * instance, unsigned char *read_data, unsigned char delay)
 * @brief It does the reading or writing from the address specified .
 * @details Reads a byte of data over I2C bus from the passed I2C location. Then sends request to send 
 *          in the next byte.
 * @param i2c_struct*
 * @param unsigned char  *read_data
 * @param unsigned char delay
 * @return Zero on success; else -ETIMEOUT
 */
//#define READ_INTERRUPT 1
ಪೂರ್ಣಾಂಕ i2c_read_ದತ್ತಾಂಶ_nack(i2c_struct * instance, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *read_ದತ್ತಾಂಶ_2, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay)
{
	/* Make a dummy read as per spec of the I2C controller */
	*read_ದತ್ತಾಂಶ_2 = instance->ದತ್ತಾಂಶ_2; //~
	delay=delay;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ USE_WRITE_I2_C_ಅಡಚಣೆ
	i2c_complete_flag = 0;
	instance->control = I2C_REPSTART_ENI; //~
	ಆಗ(!i2c_complete_flag);
	*read_ದತ್ತಾಂಶ_2 = instance->ದತ್ತಾಂಶ_2;
	ಬರೆ("\n I2C Read Data = %x", i2c_read_ದತ್ತಾಂಶ);
#ಇಲ್ಲದಿದ್ದರೆ
/*
	while(wait_till_txrx_operation_Completes(instance, &status))
	{
		printf("\twaiting for pin\n");
		waitfor(delay);
	}
*/	
#ಆದರೆ_ಅಂತ್ಯ
	ಬರೆ("\n I2C Read Data = %x", *read_ದತ್ತಾಂಶ_2);
	ಹಿಂತಿರುಗಿ I2C_SUCCESS;
}

/**
 * @fn int i2c_send_interrupt_slave_address(i2c_struct * instance, unsigned char slaveAddress, unsigned char rdWrCntrl, unsigned long delay)
 * @brief Sends the slave address over I2C Bus.
 * @details Interrupt based routine to send slave address to the I2C slave device
 * @param i2c_struct*
 * @param unsigned char slaveAddress
 * @param unsigned char rdWrCntrl
 * @param unsigned long delay
 * @return Zero on success. Else corresponding error value.
 */
ಪೂರ್ಣಾಂಕ i2c_send_ಅಡಚಣೆ_slave_ವಿಳಾಸ(i2c_struct * instance, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ slave_ವಿಳಾಸ, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ rdWrCntrl, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay)
{
	ಪೂರ್ಣಾಂಕ timeout;
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ತಾತ್ಕಾಲಿಕ = 0;
	ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_3 = 0;
	delay = delay;

	ಆದರೆ(rdWrCntrl == 0)
		slave_ವಿಳಾಸ |= I2C_WRITE;
	ಇಲ್ಲದಿದ್ದರೆ
		slave_ವಿಳಾಸ |= I2C_READ;

	log_debug("\n\tSetting Slave Address : 0x%x\n", slave_ವಿಳಾಸ);/* Writes the slave address to I2C controller */
	//Writing the slave address that needs to be written into data register.
	instance->ದತ್ತಾಂಶ_2 = slave_ವಿಳಾಸ;
	log_debug("\tSlave Address is written into data register\n");

	//Reads back the data register to confirm
	ತಾತ್ಕಾಲಿಕ = instance->ದತ್ತಾಂಶ_2; //Reads the slave address from I2C controller
	log_debug("\tSet slave address read again, which is 0x%x\n",ತಾತ್ಕಾಲಿಕ);

	ಆದರೆ(slave_ವಿಳಾಸ != (ಪೂರ್ಣಾಂಕ)ತಾತ್ಕಾಲಿಕ)
	{
		log_error("\tSlave address is not matching; Written Add. Value: 0x%x; Read Add. Value: 0x%x\n", slave_ವಿಳಾಸ, ತಾತ್ಕಾಲಿಕ);
		log_error("\n There is some issue in AXI interface. Please check.");
		ಹಿಂತಿರುಗಿ EAXI_ERROR;
	}

	//Waits till the bus becomes free.
	ಆಗ(wait_till_I2c_bus_free(instance))
	{
		log_error("\tError in Waiting for BB\n");
		ಹಿಂತಿರುಗಿ EI2C_BUS_ERROR;
	}

	//Send the start condition and slave address to slave
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ USE_SA_WRITE_I2_C_ಅಡಚಣೆ
	instance->control = I2_C_ಆರಂಭ;; //Sending the slave address to the I2C slave
	//Wait for PIN to become low.
	timeout = wait_till_txrx_operation_Completes(instance, &ಸ್ಥಿತಿ_3);
	ಆದರೆ (timeout) {//Asking the controller to send a start signal to initiate the transaction
		ಬರೆ("\tTimeout happened - Write did not go through the BFM -- Diagnose\n");
		instance->control = I2C_STOP; //~
		ಹಿಂತಿರುಗಿ EI2C_PIN_ERROR;
	}

	ಆದರೆ (ಸ್ಥಿತಿ_3 & I2C_LRB) {
		instance->control = I2C_STOP; //~
		ಬರೆ("\tSome status check failing\n");
		ಹಿಂತಿರುಗಿ EI2C_LRB_ERROR;
	}
#ಇಲ್ಲದಿದ್ದರೆ
	i2c_complete_flag = 0;
	instance->control = I2C_REPSTART_ENI; //Sending the slave address to the I2C slave
	ಆಗ(!i2c_complete_flag);
	log_info("\n Slave Address Write Operation is complete.");
	i2c_complete_flag = 0;
#ಆದರೆ_ಅಂತ್ಯ
	log_info("\n Slave address is written successfully");
	ಹಿಂತಿರುಗಿ I2C_SUCCESS;
}

/**
 * @fn int i2c_read_interrupt_data(i2c_struct * instance, unsigned char *read_data, unsigned char delay, unsigned char last)
 * @brief  Interrupt based I2C read 
 * @details Interrupt based i2c read function to read from the I2C slave.
 * @param i2c_struct
 * @param unsigned char *read_data
 * @param unsigned char delay 
 * @param unsigned char last
 * @return Zero on success.
 */
ಪೂರ್ಣಾಂಕ i2c_read_ಅಡಚಣೆ_ದತ್ತಾಂಶ(i2c_struct * instance, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *read_ದತ್ತಾಂಶ_2, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ಕೊನೆಯ)
{
	ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_3 = 0;

	/* Make a dummy read as per spec of the I2C controller */
	*read_ದತ್ತಾಂಶ_2 = instance->ದತ್ತಾಂಶ_2;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ USE_READ_I2_C_ಅಡಚಣೆ	
	i2c_complete_flag = 0;

	ಆದರೆ(ಕೊನೆಯ)
	{
		instance->control = I2C_STOP_ENI; //~
		ಆಗ(!i2c_complete_flag);
	}
	ಇಲ್ಲದಿದ್ದರೆ
	{
		/* Needs to be tested */
		//			instance->control = I2C_REPSTART_ENI;
		//			printf("\n Call I2C rep. start eni");
		//			while(!i2c_complete_flag);
	}
	ಬರೆ("\n I2C Read Data = %x", *read_ದತ್ತಾಂಶ_2);
#ಇಲ್ಲದಿದ್ದರೆ
	ಆಗ(wait_till_txrx_operation_Completes(instance, &ಸ್ಥಿತಿ_3))
	{
		ಬರೆ("\twaiting for pin\n");
		waitfor(delay);
	}
	ಆದರೆ(!ಕೊನೆಯ)
	{
		ಬರೆ("\n Rep Start");				
		//				instance->control = I2C_REPSTART;
	}
	ಇಲ್ಲದಿದ್ದರೆ
	{
		ಬರೆ("\nCall I2C Stop");
		instance->control = I2C_STOP;
	}
#ಆದರೆ_ಅಂತ್ಯ
	ಹಿಂತಿರುಗಿ I2C_SUCCESS;
}

/**
 * @fn int i2c_write_interrupt_data(i2c_struct * instance, unsigned char writeData, unsigned char delay, unsigned char last)
 * @brief Interrupt based I2C write function.
 * @details Writes a byte of data into slave I2C bus using interrupt.
 * @param i2c_struct*
 * @param unsigned char writeData
 * @param unsigned char delay
 * @param unsigned char last
 * @return Zero on success. Else based on the error.
 */
ಪೂರ್ಣಾಂಕ i2c_write_ಅಡಚಣೆ_ದತ್ತಾಂಶ(i2c_struct * instance, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ write_ದತ್ತಾಂಶ, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ಕೊನೆಯ)
{
	ಪೂರ್ಣಾಂಕ timeout;
	ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_3 = 0;
	delay = delay;

	instance->ದತ್ತಾಂಶ_2 = write_ದತ್ತಾಂಶ;

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ USE_WRITE_I2_C_ಅಡಚಣೆ
	timeout = wait_till_txrx_operation_Completes(instance, &ಸ್ಥಿತಿ_3);
	ಆದರೆ (timeout) {
		ಬರೆ("\tTimeout happened - Write did not go through the BFM -- Diagnose\n");
		instance->control = I2C_STOP; //~
		ಹಿಂತಿರುಗಿ EREMOTEIO;
	}

	ಆದರೆ (ಸ್ಥಿತಿ_3 & I2C_LRB)
	{ // What error is this?
		instance->control = I2C_STOP;//~
		ಬರೆ("\tSome status check failing\n");
		ಹಿಂತಿರುಗಿ EI2C_LRB_ERROR;
	}

	ಆದರೆ(1 == ಕೊನೆಯ)
	{
		instance->control = I2C_STOP;;
		ಬರೆ("\tI2C Write Success and completes\n");
	}
#ಇಲ್ಲದಿದ್ದರೆ
	i2c_complete_flag = 0;

	ಆದರೆ(ಕೊನೆಯ)
	{
		instance->control = I2C_STOP_ENI; //Sending the sslave address to the I2C slave
		ಬರೆ("\n Calling stop eni write");
		ಆಗ(!i2c_complete_flag);
	}
	ಇಲ್ಲದಿದ್ದರೆ
	{
		//			instance->control = I2C_REPSTART_ENI;
		//			printf("\n Calling repstart eni write");
		//		while(!i2c_complete_flag);
	}
	log_info("\n Write Operation is complete.");
	i2c_complete_flag = 0;
#ಆದರೆ_ಅಂತ್ಯ
	ಹಿಂತಿರುಗಿ I2C_SUCCESS;
}
