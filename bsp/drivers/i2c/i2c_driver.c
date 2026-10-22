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

#అన్తర్భావ "i2c.h"//Includes the definitions of i2c communication protocol//
#అన్తర్భావ "log.h"
#అన్తర్భావ "utils.h"

/* Enable these bits only when corresponding interrupt is needed.*/

//#define USE_SA_WRITE_I2C_INTERRUPT 1
//#define USE_WRITE_I2C_INTERRUPT 1
//#define USE_READ_I2C_INTERRUPT 1

i2c_struct *i2c_instance[MAX_I2_C_లెక్క];

/**
 * @fn void i2c_init()
 * @brief Initialises the i2c modules.
 * @details Initialises the i2c array modules to the max. no of i2c modules present
 */
శూన్య i2c_init()
{
	కొరకు(పూర్ణాంకం i=0; i< MAX_I2_C_లెక్క; i++)
	{
		i2c_instance[i] = (i2c_struct*) (I2_C0_పునాది + (i * I2_C_స్థానభ్రంశం));
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
పూర్ణాంకం config_i2c(i2c_struct * instance, గుర్తులేని అక్షరం prescale_div, గుర్తులేని అక్షరం scl_div)
{
	గుర్తులేని అక్షరం తాత్కాలిక = 0;
	log_debug("\tI2C: Initializing the Controller\n");

	ఒకవేళ(prescale_div  != instance->prescale )
	{
		instance->prescale = prescale_div;
#నిర్వచితమైతే DEBUG 
		తాత్కాలిక = instance->prescale;

		ఒకవేళ((తాత్కాలిక | 0x00) != prescale_div)
		{
			log_error("\t Failed to write Prescale division Written Value: 0x%x; read Value: 0x%x\n", prescale_div, instance->prescale);
			తిరిగి -ENXIO;
		}
		లేకపోతే
		{
			log_debug("\tPrescaler successfully initalized\n");
		}
#అయితే_ముగింపు
	}

	ఒకవేళ(scl_div != instance->scl )
	{
		instance->scl = scl_div;  //Setting the I2C clock value to be 1, which will set the clock for module and prescaler clock


#నిర్వచితమైతే DEBUG 
		తాత్కాలిక = instance->scl;

		/* Just reading the written value to see if all is well -- Compiler should not optimize this load!!! Compiler can just optimize the store to pointer address followed by load pointer to a register to just an immediate load to the register since clock register is not used anywhere -- but the purpose is lost. Don't give compiler optimizations */
		ఒకవేళ((తాత్కాలిక | 0x00) != scl_div)
		{
			log_error("\tClock initialization failed Write Value: 0x%x; read Value: 0x%x\n", scl_div, తాత్కాలిక);
			తిరిగి -ENXIO;
		}
		లేకపోతే
		{
			log_debug("\tClock successfully initalized\n");
		}
#అయితే_ముగింపు
	}

	/* S1=0x80 S0 selected, serial interface off */
	log_debug("\tClearing the status register. \n");
	instance->control = I2C_PIN;

	// Reading set control Register Value to ensure sanctity
	log_debug("\tReading Status Register \n");
	తాత్కాలిక = instance->control;

	//Check whether the status register is cleared or not.
	ఒకవేళ((తాత్కాలిక & 0x7f) != 0){
		log_error("\tDevice Not Recognized\n");
		తిరిగి -ENXIO;
	}

	log_debug("\tWaiting for a specified time\n ");
	waitfor(900); //1 Second software wait -- Should be 900000 but setting to 900 now since simulation is already slow
	log_debug("\tDone Waiting \n ");
	log_info("\nControl: %x; Status: %x", instance->control, instance->స్థితి_3);
	/* Enable Serial Interface */
	instance->control = I2C_IDLE;
	waitfor(900); //1 Second software wait -- Should be 900000 but setting to 900 now since simulation is already slow

	తాత్కాలిక = instance->స్థితి_3;

	/* Check to see if I2C is really in Idle and see if we can access the status register -- If not something wrong in initialization. This also verifies if Control is properly written since zero bit will be initialized to zero*/
	ఒకవేళ(తాత్కాలిక != (I2C_PIN | I2C_BB)){
		log_error("\n\tInitialization failed; Status Reg: %x\n", తాత్కాలిక);
		తిరిగి -ENXIO;
	}

	log_info("\tI2C Initialization success\n");
	తిరిగి 0;
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
పూర్ణాంకం wait_till_I2c_bus_free(i2c_struct * instance)
{
	log_debug("\tCheck for I2C Bus Busy to be free.\n");
	పూర్ణాంకం timeout = DEF_TIMEOUT;
	పూర్ణాంకం స్థితి_3;

	స్థితి_3 = instance->స్థితి_3;

	అయితే (!(స్థితి_3 & I2C_BB) && --timeout) {
		waitfor(20000); /* wait for 100 us */
		స్థితి_3 = instance->స్థితి_3;
	}

	ఒకవేళ (timeout == 0) {
		log_error("\t Bus busy wait - timed out. Resetting\n");
		తిరిగి ETIMEDOUT;
	}

	తిరిగి 0;
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
పూర్ణాంకం wait_till_txrx_operation_Completes(i2c_struct * instance, పూర్ణాంకం *స్థితి_3)
{

	పూర్ణాంకం timeout = DEF_TIMEOUT;

	*స్థితి_3 = instance->స్థితి_3;

	అయితే ((*స్థితి_3 & I2C_PIN) && --timeout) {
		waitfor(10000); /* wait for 100 us */
		*స్థితి_3 = instance->స్థితి_3;
	}

	ఒకవేళ (timeout == 0){
		log_info("\tWait for pin timed out\n");
		తిరిగి ETIMEDOUT;
	}

	waitfor(10000); /* wait for 100 us */
	log_debug("\n I2C tx_rx operation is completed");
	తిరిగి 0;
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
పూర్ణాంకం sendbytes(i2c_struct * instance, స్థిరరాశి అక్షరం *buf, పూర్ణాంకం లెక్క, పూర్ణాంకం చివరి, పూర్ణాంకం eni)
{
	పూర్ణాంకం wrcount, స్థితి_3, timeout;
	రాయి("\tStarting Write Transaction -- Did you create tri1 nets for SDA and SCL in verilog?\n");
	కొరకు (wrcount=0; wrcount<లెక్క; ++wrcount) {
		instance->దత్తాంశం_2 = buf[wrcount];
		timeout = wait_till_txrx_operation_Completes(instance, &స్థితి_3);
		ఒకవేళ (timeout) {
			రాయి("\tTimeout happened - Write did not go through the BFM -- Diagnose\n");
			instance->control = I2C_STOP;
			తిరిగి EREMOTEIO;
		}
		ఒకవేళ (స్థితి_3 & I2C_LRB) { // What error is this?
			instance->control = I2C_STOP;//~
			రాయి("\tSome status check failing\n");
			తిరిగి EREMOTEIO;
		}
	}
	ఒకవేళ (చివరి){
		రాయి("\tLast byte sent : Issue a stop\n");
		instance->control = I2C_STOP;
	}
	లేకపోతే{
		రాయి("\tSending Rep Start and doing some other R/W transaction\n");

		ఒకవేళ(!eni)
			instance->control = I2C_REPSTART;
		లేకపోతే
			instance->control = I2C_REPSTART_ENI;
	}

	తిరిగి wrcount;
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
పూర్ణాంకం readbytes(i2c_struct * instance, అక్షరం *buf, పూర్ణాంకం లెక్క, పూర్ణాంకం చివరి)
{
	పూర్ణాంకం i, స్థితి_3;
	పూర్ణాంకం wfp;

	/* increment number of bytes to read by one -- read dummy byte */
	కొరకు (i = 0; i <= లెక్క; i++) {
		wfp = wait_till_txrx_operation_Completes(instance, &స్థితి_3);
		ఒకవేళ (wfp) {
			instance->control = I2C_STOP;
			తిరిగి -1;
		}

		ఒకవేళ ((స్థితి_3 & I2C_LRB) && (i != లెక్క)) {
			instance->control = I2C_STOP;
			రాయి("\tNo ack\n");
			తిరిగి -1;
		}

		ఒకవేళ (i)
		{
			buf[i - 1] = instance->దత్తాంశం_2;
			రాయి("\n Read Value: %x", buf[i - 1]);
		}
		లేకపోతే
			instance->దత్తాంశం_2 = !instance->దత్తాంశం_2; /* dummy read */

		ఒకవేళ (i == లెక్క - 1) {
			instance->control = I2C_ESO;
		} లేకపోతే ఒకవేళ (i == లెక్క) {
			ఒకవేళ (చివరి)
				instance->control = I2C_STOP;
			లేకపోతే
				instance->control = I2C_REPSTART_ENI;
		}

	}

	తిరిగి i-1; //excluding the dummy read
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
పూర్ణాంకం i2c_send_slave_చిరునామా(i2c_struct * instance, గుర్తులేని అక్షరం slave_చిరునామా, గుర్తులేని అక్షరం rdWrCntrl, గుర్తులేని దీర్ఘ delay)
{
	పూర్ణాంకం timeout;
	గుర్తులేని అక్షరం తాత్కాలిక = 0;
	పూర్ణాంకం స్థితి_3 = 0;

	delay = delay;

	ఒకవేళ(rdWrCntrl == 0)
		slave_చిరునామా |= I2C_WRITE;
	లేకపోతే
		slave_చిరునామా |= I2C_READ;

	//Writing the slave address that needs to be written into data register.
	instance->దత్తాంశం_2 = slave_చిరునామా;
	log_debug("\tSlave Address 0x%x written into data register\n", slave_చిరునామా);

	//Reads back the data register to confirm
	తాత్కాలిక = instance->దత్తాంశం_2; //Reads the slave address from I2C controller

	ఒకవేళ(slave_చిరునామా != (పూర్ణాంకం)తాత్కాలిక)
	{
		log_error("\tSlave address is not matching; Written Add. Value: 0x%x; Read Add. Value: 0x%x\n", slave_చిరునామా, తాత్కాలిక);
		log_error("\n There is some issue in AXI interface. Please check.");
		తిరిగి EAXI_ERROR;
	}

	//Waits till the bus becomes free.
	అయితే(wait_till_I2c_bus_free(instance))
	{
		log_error("\tError in Waiting for BB\n");
		తిరిగి EI2C_BUS_ERROR;
	}


	//Send the start condition and slave address to slave
#నిర్వచితం_కాకపోతే USE_SA_WRITE_I2_C_అంతరాయం
	instance->control = I2_C_ప్రారంభం; //Sending the slave address to the I2C slave
	waitfor(900);
	//Wait for PIN to become low.
	timeout = wait_till_txrx_operation_Completes(instance, &స్థితి_3);
	ఒకవేళ (timeout) {//Asking the controller to send a start signal to initiate the transaction
		రాయి("\tTimeout happened - Write did not go through the BFM -- Diagnose\n");
		instance->control = I2C_STOP; //~
		తిరిగి EI2C_PIN_ERROR;
	}

	ఒకవేళ (స్థితి_3 & I2C_LRB) {
		instance->control = I2C_STOP; //~
		రాయి("\tSome status check failing\n");
		తిరిగి EI2C_LRB_ERROR;
	}

#లేకపోతే
	i2c_complete_flag = 0;

	instance->control = I2_C_ప్రారంభం_ENI; //Sending the slave address to the I2C slave
	అయితే(!i2c_complete_flag);
	log_info("\n Slave Address Write Operation is complete.");
	i2c_complete_flag = 0;
#అయితే_ముగింపు

	తిరిగి I2C_SUCCESS;
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
పూర్ణాంకం i2c_write_దత్తాంశం(i2c_struct * instance, గుర్తులేని అక్షరం write_దత్తాంశం, గుర్తులేని అక్షరం delay)
{
	పూర్ణాంకం timeout;
	పూర్ణాంకం స్థితి_3 = 0;
	delay = delay;

	instance->దత్తాంశం_2= write_దత్తాంశం;

#నిర్వచితం_కాకపోతే USE_WRITE_I2_C_అంతరాయం
	timeout = wait_till_txrx_operation_Completes(instance, &స్థితి_3);
	ఒకవేళ (timeout) {
		రాయి("\tTimeout happened - Write did not go through the BFM -- Diagnose\n");
		instance->control = I2C_STOP; //~
		తిరిగి EREMOTEIO;
	}

	ఒకవేళ (స్థితి_3 & I2C_LRB)
	{ // What error is this?
		instance->control = I2C_STOP; //~
		రాయి("\tSome status check failing\n");
		తిరిగి EI2C_LRB_ERROR;
	}
#లేకపోతే
	i2c_complete_flag = 0;
	instance->control = I2C_STOP_ENI; //Sending the sslave address to the I2C slave

	అయితే(!i2c_complete_flag);
	log_info("\n Write Operation is complete.");
	i2c_complete_flag = 0;
#అయితే_ముగింపు

	తిరిగి I2C_SUCCESS;
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
పూర్ణాంకం i2c_read_దత్తాంశం(i2c_struct * instance, గుర్తులేని అక్షరం *read_దత్తాంశం_2, గుర్తులేని అక్షరం delay)
{
	పూర్ణాంకం స్థితి_3 = 0;

	/* Make a dummy read as per spec of the I2C controller */

	*read_దత్తాంశం_2 = instance->దత్తాంశం_2; //~

#నిర్వచితమైతే USE_WRITE_I2_C_అంతరాయం	
	i2c_complete_flag = 0;
	instance->control = I2C_REPSTART_ENI; //~

	అయితే(!i2c_complete_flag);
	*read_దత్తాంశం_2 = instance->దత్తాంశం_2;

	రాయి("\n I2C Read Data = %x", i2c_read_దత్తాంశం);
#లేకపోతే
	అయితే(wait_till_txrx_operation_Completes(instance, &స్థితి_3))
	{
		రాయి("\twaiting for pin\n");
		waitfor(delay);
	}
#అయితే_ముగింపు
	తిరిగి I2C_SUCCESS;
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
పూర్ణాంకం i2c_read_దత్తాంశం_nack(i2c_struct * instance, గుర్తులేని అక్షరం *read_దత్తాంశం_2, గుర్తులేని అక్షరం delay)
{
	/* Make a dummy read as per spec of the I2C controller */
	*read_దత్తాంశం_2 = instance->దత్తాంశం_2; //~
	delay=delay;

#నిర్వచితమైతే USE_WRITE_I2_C_అంతరాయం
	i2c_complete_flag = 0;
	instance->control = I2C_REPSTART_ENI; //~
	అయితే(!i2c_complete_flag);
	*read_దత్తాంశం_2 = instance->దత్తాంశం_2;
	రాయి("\n I2C Read Data = %x", i2c_read_దత్తాంశం);
#లేకపోతే
/*
	while(wait_till_txrx_operation_Completes(instance, &status))
	{
		printf("\twaiting for pin\n");
		waitfor(delay);
	}
*/	
#అయితే_ముగింపు
	రాయి("\n I2C Read Data = %x", *read_దత్తాంశం_2);
	తిరిగి I2C_SUCCESS;
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
పూర్ణాంకం i2c_send_అంతరాయం_slave_చిరునామా(i2c_struct * instance, గుర్తులేని అక్షరం slave_చిరునామా, గుర్తులేని అక్షరం rdWrCntrl, గుర్తులేని దీర్ఘ delay)
{
	పూర్ణాంకం timeout;
	గుర్తులేని అక్షరం తాత్కాలిక = 0;
	పూర్ణాంకం స్థితి_3 = 0;
	delay = delay;

	ఒకవేళ(rdWrCntrl == 0)
		slave_చిరునామా |= I2C_WRITE;
	లేకపోతే
		slave_చిరునామా |= I2C_READ;

	log_debug("\n\tSetting Slave Address : 0x%x\n", slave_చిరునామా);/* Writes the slave address to I2C controller */
	//Writing the slave address that needs to be written into data register.
	instance->దత్తాంశం_2 = slave_చిరునామా;
	log_debug("\tSlave Address is written into data register\n");

	//Reads back the data register to confirm
	తాత్కాలిక = instance->దత్తాంశం_2; //Reads the slave address from I2C controller
	log_debug("\tSet slave address read again, which is 0x%x\n",తాత్కాలిక);

	ఒకవేళ(slave_చిరునామా != (పూర్ణాంకం)తాత్కాలిక)
	{
		log_error("\tSlave address is not matching; Written Add. Value: 0x%x; Read Add. Value: 0x%x\n", slave_చిరునామా, తాత్కాలిక);
		log_error("\n There is some issue in AXI interface. Please check.");
		తిరిగి EAXI_ERROR;
	}

	//Waits till the bus becomes free.
	అయితే(wait_till_I2c_bus_free(instance))
	{
		log_error("\tError in Waiting for BB\n");
		తిరిగి EI2C_BUS_ERROR;
	}

	//Send the start condition and slave address to slave
#నిర్వచితం_కాకపోతే USE_SA_WRITE_I2_C_అంతరాయం
	instance->control = I2_C_ప్రారంభం;; //Sending the slave address to the I2C slave
	//Wait for PIN to become low.
	timeout = wait_till_txrx_operation_Completes(instance, &స్థితి_3);
	ఒకవేళ (timeout) {//Asking the controller to send a start signal to initiate the transaction
		రాయి("\tTimeout happened - Write did not go through the BFM -- Diagnose\n");
		instance->control = I2C_STOP; //~
		తిరిగి EI2C_PIN_ERROR;
	}

	ఒకవేళ (స్థితి_3 & I2C_LRB) {
		instance->control = I2C_STOP; //~
		రాయి("\tSome status check failing\n");
		తిరిగి EI2C_LRB_ERROR;
	}
#లేకపోతే
	i2c_complete_flag = 0;
	instance->control = I2C_REPSTART_ENI; //Sending the slave address to the I2C slave
	అయితే(!i2c_complete_flag);
	log_info("\n Slave Address Write Operation is complete.");
	i2c_complete_flag = 0;
#అయితే_ముగింపు
	log_info("\n Slave address is written successfully");
	తిరిగి I2C_SUCCESS;
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
పూర్ణాంకం i2c_read_అంతరాయం_దత్తాంశం(i2c_struct * instance, గుర్తులేని అక్షరం *read_దత్తాంశం_2, గుర్తులేని అక్షరం delay, గుర్తులేని అక్షరం చివరి)
{
	పూర్ణాంకం స్థితి_3 = 0;

	/* Make a dummy read as per spec of the I2C controller */
	*read_దత్తాంశం_2 = instance->దత్తాంశం_2;

#నిర్వచితమైతే USE_READ_I2_C_అంతరాయం	
	i2c_complete_flag = 0;

	ఒకవేళ(చివరి)
	{
		instance->control = I2C_STOP_ENI; //~
		అయితే(!i2c_complete_flag);
	}
	లేకపోతే
	{
		/* Needs to be tested */
		//			instance->control = I2C_REPSTART_ENI;
		//			printf("\n Call I2C rep. start eni");
		//			while(!i2c_complete_flag);
	}
	రాయి("\n I2C Read Data = %x", *read_దత్తాంశం_2);
#లేకపోతే
	అయితే(wait_till_txrx_operation_Completes(instance, &స్థితి_3))
	{
		రాయి("\twaiting for pin\n");
		waitfor(delay);
	}
	ఒకవేళ(!చివరి)
	{
		రాయి("\n Rep Start");				
		//				instance->control = I2C_REPSTART;
	}
	లేకపోతే
	{
		రాయి("\nCall I2C Stop");
		instance->control = I2C_STOP;
	}
#అయితే_ముగింపు
	తిరిగి I2C_SUCCESS;
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
పూర్ణాంకం i2c_write_అంతరాయం_దత్తాంశం(i2c_struct * instance, గుర్తులేని అక్షరం write_దత్తాంశం, గుర్తులేని అక్షరం delay, గుర్తులేని అక్షరం చివరి)
{
	పూర్ణాంకం timeout;
	పూర్ణాంకం స్థితి_3 = 0;
	delay = delay;

	instance->దత్తాంశం_2 = write_దత్తాంశం;

#నిర్వచితం_కాకపోతే USE_WRITE_I2_C_అంతరాయం
	timeout = wait_till_txrx_operation_Completes(instance, &స్థితి_3);
	ఒకవేళ (timeout) {
		రాయి("\tTimeout happened - Write did not go through the BFM -- Diagnose\n");
		instance->control = I2C_STOP; //~
		తిరిగి EREMOTEIO;
	}

	ఒకవేళ (స్థితి_3 & I2C_LRB)
	{ // What error is this?
		instance->control = I2C_STOP;//~
		రాయి("\tSome status check failing\n");
		తిరిగి EI2C_LRB_ERROR;
	}

	ఒకవేళ(1 == చివరి)
	{
		instance->control = I2C_STOP;;
		రాయి("\tI2C Write Success and completes\n");
	}
#లేకపోతే
	i2c_complete_flag = 0;

	ఒకవేళ(చివరి)
	{
		instance->control = I2C_STOP_ENI; //Sending the sslave address to the I2C slave
		రాయి("\n Calling stop eni write");
		అయితే(!i2c_complete_flag);
	}
	లేకపోతే
	{
		//			instance->control = I2C_REPSTART_ENI;
		//			printf("\n Calling repstart eni write");
		//		while(!i2c_complete_flag);
	}
	log_info("\n Write Operation is complete.");
	i2c_complete_flag = 0;
#అయితే_ముగింపు
	తిరిగి I2C_SUCCESS;
}
