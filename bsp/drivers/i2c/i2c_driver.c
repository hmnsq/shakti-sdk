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

#ضمن "i2c.h"//Includes the definitions of i2c communication protocol//
#ضمن "log.h"
#ضمن "utils.h"

/* Enable these bits only when corresponding interrupt is needed.*/

//#define USE_SA_WRITE_I2C_INTERRUPT 1
//#define USE_WRITE_I2C_INTERRUPT 1
//#define USE_READ_I2C_INTERRUPT 1

i2c_struct *i2c_instance[MAX_I2_C_شمار];

/**
 * @fn void i2c_init()
 * @brief Initialises the i2c modules.
 * @details Initialises the i2c array modules to the max. no of i2c modules present
 */
فراغ i2c_init()
{
	لكل(صحيح i=0; i< MAX_I2_C_شمار; i++)
	{
		i2c_instance[i] = (i2c_struct*) (I2_C0_پایه + (i * I2_C_جابه_جایی));
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
صحيح config_i2c(i2c_struct * instance, بیعلامت حرف prescale_div, بیعلامت حرف scl_div)
{
	بیعلامت حرف موقت = 0;
	log_debug("\tI2C: Initializing the Controller\n");

	إذا(prescale_div  != instance->prescale )
	{
		instance->prescale = prescale_div;
#اگر_تعریف_شده DEBUG 
		موقت = instance->prescale;

		إذا((موقت | 0x00) != prescale_div)
		{
			log_error("\t Failed to write Prescale division Written Value: 0x%x; read Value: 0x%x\n", prescale_div, instance->prescale);
			أرجع -ENXIO;
		}
		وإلا
		{
			log_debug("\tPrescaler successfully initalized\n");
		}
#پایان_اگر
	}

	إذا(scl_div != instance->scl )
	{
		instance->scl = scl_div;  //Setting the I2C clock value to be 1, which will set the clock for module and prescaler clock


#اگر_تعریف_شده DEBUG 
		موقت = instance->scl;

		/* Just reading the written value to see if all is well -- Compiler should not optimize this load!!! Compiler can just optimize the store to pointer address followed by load pointer to a register to just an immediate load to the register since clock register is not used anywhere -- but the purpose is lost. Don't give compiler optimizations */
		إذا((موقت | 0x00) != scl_div)
		{
			log_error("\tClock initialization failed Write Value: 0x%x; read Value: 0x%x\n", scl_div, موقت);
			أرجع -ENXIO;
		}
		وإلا
		{
			log_debug("\tClock successfully initalized\n");
		}
#پایان_اگر
	}

	/* S1=0x80 S0 selected, serial interface off */
	log_debug("\tClearing the status register. \n");
	instance->control = I2C_PIN;

	// Reading set control Register Value to ensure sanctity
	log_debug("\tReading Status Register \n");
	موقت = instance->control;

	//Check whether the status register is cleared or not.
	إذا((موقت & 0x7f) != 0){
		log_error("\tDevice Not Recognized\n");
		أرجع -ENXIO;
	}

	log_debug("\tWaiting for a specified time\n ");
	waitfor(900); //1 Second software wait -- Should be 900000 but setting to 900 now since simulation is already slow
	log_debug("\tDone Waiting \n ");
	log_info("\nControl: %x; Status: %x", instance->control, instance->وضعیت_2);
	/* Enable Serial Interface */
	instance->control = I2C_IDLE;
	waitfor(900); //1 Second software wait -- Should be 900000 but setting to 900 now since simulation is already slow

	موقت = instance->وضعیت_2;

	/* Check to see if I2C is really in Idle and see if we can access the status register -- If not something wrong in initialization. This also verifies if Control is properly written since zero bit will be initialized to zero*/
	إذا(موقت != (I2C_PIN | I2C_BB)){
		log_error("\n\tInitialization failed; Status Reg: %x\n", موقت);
		أرجع -ENXIO;
	}

	log_info("\tI2C Initialization success\n");
	أرجع 0;
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
صحيح wait_till_I2c_bus_free(i2c_struct * instance)
{
	log_debug("\tCheck for I2C Bus Busy to be free.\n");
	صحيح timeout = DEF_TIMEOUT;
	صحيح وضعیت_2;

	وضعیت_2 = instance->وضعیت_2;

	طالما (!(وضعیت_2 & I2C_BB) && --timeout) {
		waitfor(20000); /* wait for 100 us */
		وضعیت_2 = instance->وضعیت_2;
	}

	إذا (timeout == 0) {
		log_error("\t Bus busy wait - timed out. Resetting\n");
		أرجع ETIMEDOUT;
	}

	أرجع 0;
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
صحيح wait_till_txrx_operation_Completes(i2c_struct * instance, صحيح *وضعیت_2)
{

	صحيح timeout = DEF_TIMEOUT;

	*وضعیت_2 = instance->وضعیت_2;

	طالما ((*وضعیت_2 & I2C_PIN) && --timeout) {
		waitfor(10000); /* wait for 100 us */
		*وضعیت_2 = instance->وضعیت_2;
	}

	إذا (timeout == 0){
		log_info("\tWait for pin timed out\n");
		أرجع ETIMEDOUT;
	}

	waitfor(10000); /* wait for 100 us */
	log_debug("\n I2C tx_rx operation is completed");
	أرجع 0;
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
صحيح sendbytes(i2c_struct * instance, ثابت حرف *buf, صحيح شمار, صحيح آخرین, صحيح eni)
{
	صحيح wrcount, وضعیت_2, timeout;
	چاپ_کن("\tStarting Write Transaction -- Did you create tri1 nets for SDA and SCL in verilog?\n");
	لكل (wrcount=0; wrcount<شمار; ++wrcount) {
		instance->داده_2 = buf[wrcount];
		timeout = wait_till_txrx_operation_Completes(instance, &وضعیت_2);
		إذا (timeout) {
			چاپ_کن("\tTimeout happened - Write did not go through the BFM -- Diagnose\n");
			instance->control = I2C_STOP;
			أرجع EREMOTEIO;
		}
		إذا (وضعیت_2 & I2C_LRB) { // What error is this?
			instance->control = I2C_STOP;//~
			چاپ_کن("\tSome status check failing\n");
			أرجع EREMOTEIO;
		}
	}
	إذا (آخرین){
		چاپ_کن("\tLast byte sent : Issue a stop\n");
		instance->control = I2C_STOP;
	}
	وإلا{
		چاپ_کن("\tSending Rep Start and doing some other R/W transaction\n");

		إذا(!eni)
			instance->control = I2C_REPSTART;
		وإلا
			instance->control = I2C_REPSTART_ENI;
	}

	أرجع wrcount;
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
صحيح readbytes(i2c_struct * instance, حرف *buf, صحيح شمار, صحيح آخرین)
{
	صحيح i, وضعیت_2;
	صحيح wfp;

	/* increment number of bytes to read by one -- read dummy byte */
	لكل (i = 0; i <= شمار; i++) {
		wfp = wait_till_txrx_operation_Completes(instance, &وضعیت_2);
		إذا (wfp) {
			instance->control = I2C_STOP;
			أرجع -1;
		}

		إذا ((وضعیت_2 & I2C_LRB) && (i != شمار)) {
			instance->control = I2C_STOP;
			چاپ_کن("\tNo ack\n");
			أرجع -1;
		}

		إذا (i)
		{
			buf[i - 1] = instance->داده_2;
			چاپ_کن("\n Read Value: %x", buf[i - 1]);
		}
		وإلا
			instance->داده_2 = !instance->داده_2; /* dummy read */

		إذا (i == شمار - 1) {
			instance->control = I2C_ESO;
		} وإلا إذا (i == شمار) {
			إذا (آخرین)
				instance->control = I2C_STOP;
			وإلا
				instance->control = I2C_REPSTART_ENI;
		}

	}

	أرجع i-1; //excluding the dummy read
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
صحيح i2c_send_slave_آدرس(i2c_struct * instance, بیعلامت حرف slave_آدرس, بیعلامت حرف rdWrCntrl, بیعلامت دراز delay)
{
	صحيح timeout;
	بیعلامت حرف موقت = 0;
	صحيح وضعیت_2 = 0;

	delay = delay;

	إذا(rdWrCntrl == 0)
		slave_آدرس |= I2C_WRITE;
	وإلا
		slave_آدرس |= I2C_READ;

	//Writing the slave address that needs to be written into data register.
	instance->داده_2 = slave_آدرس;
	log_debug("\tSlave Address 0x%x written into data register\n", slave_آدرس);

	//Reads back the data register to confirm
	موقت = instance->داده_2; //Reads the slave address from I2C controller

	إذا(slave_آدرس != (صحيح)موقت)
	{
		log_error("\tSlave address is not matching; Written Add. Value: 0x%x; Read Add. Value: 0x%x\n", slave_آدرس, موقت);
		log_error("\n There is some issue in AXI interface. Please check.");
		أرجع EAXI_ERROR;
	}

	//Waits till the bus becomes free.
	طالما(wait_till_I2c_bus_free(instance))
	{
		log_error("\tError in Waiting for BB\n");
		أرجع EI2C_BUS_ERROR;
	}


	//Send the start condition and slave address to slave
#اگر_تعریف_نشده USE_SA_WRITE_I2_C_وقفه
	instance->control = I2_C_شروع; //Sending the slave address to the I2C slave
	waitfor(900);
	//Wait for PIN to become low.
	timeout = wait_till_txrx_operation_Completes(instance, &وضعیت_2);
	إذا (timeout) {//Asking the controller to send a start signal to initiate the transaction
		چاپ_کن("\tTimeout happened - Write did not go through the BFM -- Diagnose\n");
		instance->control = I2C_STOP; //~
		أرجع EI2C_PIN_ERROR;
	}

	إذا (وضعیت_2 & I2C_LRB) {
		instance->control = I2C_STOP; //~
		چاپ_کن("\tSome status check failing\n");
		أرجع EI2C_LRB_ERROR;
	}

#وإلا
	i2c_complete_flag = 0;

	instance->control = I2_C_شروع_ENI; //Sending the slave address to the I2C slave
	طالما(!i2c_complete_flag);
	log_info("\n Slave Address Write Operation is complete.");
	i2c_complete_flag = 0;
#پایان_اگر

	أرجع I2C_SUCCESS;
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
صحيح i2c_write_داده(i2c_struct * instance, بیعلامت حرف write_داده, بیعلامت حرف delay)
{
	صحيح timeout;
	صحيح وضعیت_2 = 0;
	delay = delay;

	instance->داده_2= write_داده;

#اگر_تعریف_نشده USE_WRITE_I2_C_وقفه
	timeout = wait_till_txrx_operation_Completes(instance, &وضعیت_2);
	إذا (timeout) {
		چاپ_کن("\tTimeout happened - Write did not go through the BFM -- Diagnose\n");
		instance->control = I2C_STOP; //~
		أرجع EREMOTEIO;
	}

	إذا (وضعیت_2 & I2C_LRB)
	{ // What error is this?
		instance->control = I2C_STOP; //~
		چاپ_کن("\tSome status check failing\n");
		أرجع EI2C_LRB_ERROR;
	}
#وإلا
	i2c_complete_flag = 0;
	instance->control = I2C_STOP_ENI; //Sending the sslave address to the I2C slave

	طالما(!i2c_complete_flag);
	log_info("\n Write Operation is complete.");
	i2c_complete_flag = 0;
#پایان_اگر

	أرجع I2C_SUCCESS;
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
صحيح i2c_read_داده(i2c_struct * instance, بیعلامت حرف *read_داده_2, بیعلامت حرف delay)
{
	صحيح وضعیت_2 = 0;

	/* Make a dummy read as per spec of the I2C controller */

	*read_داده_2 = instance->داده_2; //~

#اگر_تعریف_شده USE_WRITE_I2_C_وقفه	
	i2c_complete_flag = 0;
	instance->control = I2C_REPSTART_ENI; //~

	طالما(!i2c_complete_flag);
	*read_داده_2 = instance->داده_2;

	چاپ_کن("\n I2C Read Data = %x", i2c_read_داده);
#وإلا
	طالما(wait_till_txrx_operation_Completes(instance, &وضعیت_2))
	{
		چاپ_کن("\twaiting for pin\n");
		waitfor(delay);
	}
#پایان_اگر
	أرجع I2C_SUCCESS;
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
صحيح i2c_read_داده_nack(i2c_struct * instance, بیعلامت حرف *read_داده_2, بیعلامت حرف delay)
{
	/* Make a dummy read as per spec of the I2C controller */
	*read_داده_2 = instance->داده_2; //~
	delay=delay;

#اگر_تعریف_شده USE_WRITE_I2_C_وقفه
	i2c_complete_flag = 0;
	instance->control = I2C_REPSTART_ENI; //~
	طالما(!i2c_complete_flag);
	*read_داده_2 = instance->داده_2;
	چاپ_کن("\n I2C Read Data = %x", i2c_read_داده);
#وإلا
/*
	while(wait_till_txrx_operation_Completes(instance, &status))
	{
		printf("\twaiting for pin\n");
		waitfor(delay);
	}
*/	
#پایان_اگر
	چاپ_کن("\n I2C Read Data = %x", *read_داده_2);
	أرجع I2C_SUCCESS;
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
صحيح i2c_send_وقفه_slave_آدرس(i2c_struct * instance, بیعلامت حرف slave_آدرس, بیعلامت حرف rdWrCntrl, بیعلامت دراز delay)
{
	صحيح timeout;
	بیعلامت حرف موقت = 0;
	صحيح وضعیت_2 = 0;
	delay = delay;

	إذا(rdWrCntrl == 0)
		slave_آدرس |= I2C_WRITE;
	وإلا
		slave_آدرس |= I2C_READ;

	log_debug("\n\tSetting Slave Address : 0x%x\n", slave_آدرس);/* Writes the slave address to I2C controller */
	//Writing the slave address that needs to be written into data register.
	instance->داده_2 = slave_آدرس;
	log_debug("\tSlave Address is written into data register\n");

	//Reads back the data register to confirm
	موقت = instance->داده_2; //Reads the slave address from I2C controller
	log_debug("\tSet slave address read again, which is 0x%x\n",موقت);

	إذا(slave_آدرس != (صحيح)موقت)
	{
		log_error("\tSlave address is not matching; Written Add. Value: 0x%x; Read Add. Value: 0x%x\n", slave_آدرس, موقت);
		log_error("\n There is some issue in AXI interface. Please check.");
		أرجع EAXI_ERROR;
	}

	//Waits till the bus becomes free.
	طالما(wait_till_I2c_bus_free(instance))
	{
		log_error("\tError in Waiting for BB\n");
		أرجع EI2C_BUS_ERROR;
	}

	//Send the start condition and slave address to slave
#اگر_تعریف_نشده USE_SA_WRITE_I2_C_وقفه
	instance->control = I2_C_شروع;; //Sending the slave address to the I2C slave
	//Wait for PIN to become low.
	timeout = wait_till_txrx_operation_Completes(instance, &وضعیت_2);
	إذا (timeout) {//Asking the controller to send a start signal to initiate the transaction
		چاپ_کن("\tTimeout happened - Write did not go through the BFM -- Diagnose\n");
		instance->control = I2C_STOP; //~
		أرجع EI2C_PIN_ERROR;
	}

	إذا (وضعیت_2 & I2C_LRB) {
		instance->control = I2C_STOP; //~
		چاپ_کن("\tSome status check failing\n");
		أرجع EI2C_LRB_ERROR;
	}
#وإلا
	i2c_complete_flag = 0;
	instance->control = I2C_REPSTART_ENI; //Sending the slave address to the I2C slave
	طالما(!i2c_complete_flag);
	log_info("\n Slave Address Write Operation is complete.");
	i2c_complete_flag = 0;
#پایان_اگر
	log_info("\n Slave address is written successfully");
	أرجع I2C_SUCCESS;
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
صحيح i2c_read_وقفه_داده(i2c_struct * instance, بیعلامت حرف *read_داده_2, بیعلامت حرف delay, بیعلامت حرف آخرین)
{
	صحيح وضعیت_2 = 0;

	/* Make a dummy read as per spec of the I2C controller */
	*read_داده_2 = instance->داده_2;

#اگر_تعریف_شده USE_READ_I2_C_وقفه	
	i2c_complete_flag = 0;

	إذا(آخرین)
	{
		instance->control = I2C_STOP_ENI; //~
		طالما(!i2c_complete_flag);
	}
	وإلا
	{
		/* Needs to be tested */
		//			instance->control = I2C_REPSTART_ENI;
		//			printf("\n Call I2C rep. start eni");
		//			while(!i2c_complete_flag);
	}
	چاپ_کن("\n I2C Read Data = %x", *read_داده_2);
#وإلا
	طالما(wait_till_txrx_operation_Completes(instance, &وضعیت_2))
	{
		چاپ_کن("\twaiting for pin\n");
		waitfor(delay);
	}
	إذا(!آخرین)
	{
		چاپ_کن("\n Rep Start");				
		//				instance->control = I2C_REPSTART;
	}
	وإلا
	{
		چاپ_کن("\nCall I2C Stop");
		instance->control = I2C_STOP;
	}
#پایان_اگر
	أرجع I2C_SUCCESS;
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
صحيح i2c_write_وقفه_داده(i2c_struct * instance, بیعلامت حرف write_داده, بیعلامت حرف delay, بیعلامت حرف آخرین)
{
	صحيح timeout;
	صحيح وضعیت_2 = 0;
	delay = delay;

	instance->داده_2 = write_داده;

#اگر_تعریف_نشده USE_WRITE_I2_C_وقفه
	timeout = wait_till_txrx_operation_Completes(instance, &وضعیت_2);
	إذا (timeout) {
		چاپ_کن("\tTimeout happened - Write did not go through the BFM -- Diagnose\n");
		instance->control = I2C_STOP; //~
		أرجع EREMOTEIO;
	}

	إذا (وضعیت_2 & I2C_LRB)
	{ // What error is this?
		instance->control = I2C_STOP;//~
		چاپ_کن("\tSome status check failing\n");
		أرجع EI2C_LRB_ERROR;
	}

	إذا(1 == آخرین)
	{
		instance->control = I2C_STOP;;
		چاپ_کن("\tI2C Write Success and completes\n");
	}
#وإلا
	i2c_complete_flag = 0;

	إذا(آخرین)
	{
		instance->control = I2C_STOP_ENI; //Sending the sslave address to the I2C slave
		چاپ_کن("\n Calling stop eni write");
		طالما(!i2c_complete_flag);
	}
	وإلا
	{
		//			instance->control = I2C_REPSTART_ENI;
		//			printf("\n Calling repstart eni write");
		//		while(!i2c_complete_flag);
	}
	log_info("\n Write Operation is complete.");
	i2c_complete_flag = 0;
#پایان_اگر
	أرجع I2C_SUCCESS;
}
