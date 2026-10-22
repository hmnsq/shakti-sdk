/***************************************************************************
* Project           		: shakti devt board
* Name of the file	     	: gpio_i2c.c
* Brief Description of file     : Performs the I2C operations using gpio pins.
* Name of Author    	        : Kotteeswaran
* Email ID                      : kottee.1@gmail.com

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
@file gpio_i2c.c
@brief Contains the driver routines for i2c driver using gpio pins.
@detail The gpio_i2c module driver supports i2c driver routines
using gpio pins.
*/

#అన్తర్భావ "platform.h"
#అన్తర్భావ "gpio.h"
#అన్తర్భావ "gpio_i2c.h"

/** @fn extern void delay_loop(unsigned long , unsigned long)
 * @brief Maintains the required delay to perform an operation
 * @param unsigned long 
 * @param unsigned long
 */
బాహ్య శూన్య delay_loop(గుర్తులేని దీర్ఘ , గుర్తులేని దీర్ఘ);

/** @fn static void SetSCLAsOutput()
 * @brief Function for configure GPIO 0 as SCL output.
 * @details This function will be called to make the scl line (defined by I2C_SCL)
 *             macro as output.
 * @warning This bit value can be changed as per I2C_SCL macro.
 */
స్థిర శూన్య సమితి_SCLAs_Output()
{
	గుర్తులేని దీర్ఘ read_దత్తాంశం = 0;
	read_దత్తాంశం = read_మాట(GPIO_DIRECTION_CNTRL_REG);
	write_మాట(GPIO_DIRECTION_CNTRL_REG, (read_దత్తాంశం | I2C_SCL) );
	రాయి("SCL set as output\n");
}

/** @fn static void SetSdaDirection(int inOutCntrl)
 *  @brief Function for configure GPIO 0 as SCL output.
 * @details This function will be called to make the scl line (defined by I2C_SCL)
 *           macro as output.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param int inOutCntrl
 */
స్థిర శూన్య సమితి_Sda_Direction(పూర్ణాంకం లోపల_బహిర్గతం_Cntrl)
{
	గుర్తులేని దీర్ఘ read_దత్తాంశం = 0;
	read_దత్తాంశం = read_మాట(GPIO_DIRECTION_CNTRL_REG);

	ఒకవేళ (లోపల_బహిర్గతం_Cntrl) { // output
		write_మాట(GPIO_DIRECTION_CNTRL_REG, (read_దత్తాంశం | I2C_SDA) );
		రాయి("\n\tSDA set as output\n");
	}
    లేకపోతే {
		write_మాట(GPIO_DIRECTION_CNTRL_REG, (read_దత్తాంశం & ~(I2C_SDA) ) );
		రాయి("\n\tSDA set as input\n");
	}
}

/** @fn static void start(unsigned char delay)
 * @brief Sending start condition for the I2C.
 * @details Start condition is making SDA low when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char delay
 */
స్థిర శూన్య ప్రారంభం(గుర్తులేని అక్షరం delay)
{
	గుర్తులేని దీర్ఘ read_దత్తాంశం = 0;
	read_దత్తాంశం = read_మాట(GPIO_దత్తాంశం_REG);

//	sda=1;
	write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG) | I2C_SDA | I2C_SCL) );
	delay_loop(delay, delay);

//		scl=1;
	write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG) | I2C_SCL) );
	delay_loop(delay, delay);

//		sda=0;
	write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG) & ~(I2C_SDA)) );
	delay_loop(delay, delay);

//		scl=0;
	write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG) & ~(I2C_SCL) ) );
	delay_loop(delay, delay);

	రాయి("\n\tI2C: I2C Start condition sent\n");
}

/** @fn static void stop(unsigned char delay)
 * @brief Sending stop condition for the I2C.
 * @details Stop condition is making SDA high when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char
 */
స్థిర శూన్య stop(గుర్తులేని అక్షరం delay)
{
	గుర్తులేని దీర్ఘ read_దత్తాంశం = 0;
	read_దత్తాంశం = read_మాట(GPIO_దత్తాంశం_REG);
//	sda=0;
	write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG) & ~(I2C_SDA)) );
	delay_loop(delay, delay);

//	scl=1;
	write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG) | I2C_SCL) );
	delay_loop(delay, delay);

//	sda=1;
	write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG) | I2C_SDA) );
	delay_loop(delay, delay);
	రాయి("\n\tI2C: I2C Start condition sent\n");

}

/** @fn void I2cWriteByte(unsigned char writeData, unsigned char delay)
 * @brief Writes a byte to the I2C device.
 * @details Data is put on the SDA Line bit by bit and then makes the
 *  SCL from low to high to write..
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param writeData --> Value that needs to be written.
 * @param unsigned char delay
 */
శూన్య I2cWriteByte(గుర్తులేని అక్షరం write_దత్తాంశం, గుర్తులేని అక్షరం delay)
{
	గుర్తులేని అక్షరం j = 0,k;
	గుర్తులేని దీర్ఘ read_దత్తాంశం = 0;
	read_దత్తాంశం = read_మాట(GPIO_దత్తాంశం_REG);
	అయితే (j < 8)
	{
		k = write_దత్తాంశం;
		k = ( k << j ) & 0x80;
//		printf("\n\r i: %d; j: %d; k: %d", i, j, k);
//		sda=CY;
		ఒకవేళ (k == 0) {
			write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG) & ~(I2C_SDA)) );
			delay_loop(delay, delay);
		}
		లేకపోతే {
			write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG) | I2C_SDA) );
			delay_loop(delay, delay);
		}

	//	scl=1;
		write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG) | I2C_SCL) );
		delay_loop(delay, delay);

	//	scl=0;
		write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG) & ~(I2C_SCL) ) );
		delay_loop(delay, delay);
		++j;
	}
}

/** @fn unsigned char I2cReadByte(unsigned char delay)
 * @brief Reads a byte from the I2C device.
 * @details Clock line is made low to high and the slave puts the Data
 *  bit on the SDA line and master stores the value to form a byte.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char delay
 * @return unsigned char (returns the value of readData).
 */
గుర్తులేని అక్షరం I2cReadByte(గుర్తులేని అక్షరం delay)
{
	గుర్తులేని అక్షరం j = 0, i = 0;
	గుర్తులేని అక్షరం బిట్టు_విలువ;
	గుర్తులేని అక్షరం read_దత్తాంశం = 0;
  గుర్తులేని దీర్ఘ read_Gpio_దత్తాంశం = 0;
	read_దత్తాంశం = read_మాట(GPIO_దత్తాంశం_REG);

//	sda=1;
//Make SDA high
	అయితే (j < 8) {
	//	scl=1;
		write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG) | I2C_SCL) );
		delay_loop(delay, delay);

//		d1 = sda;
		read_Gpio_దత్తాంశం = read_మాట(GPIO_దత్తాంశం_REG)  & I2C_SDA;
		ఒకవేళ (read_Gpio_దత్తాంశం != 0)
			బిట్టు_విలువ = 1;
		లేకపోతే
			బిట్టు_విలువ = 0;
	    read_దత్తాంశం = read_దత్తాంశం << 1;
		read_దత్తాంశం = read_దత్తాంశం | బిట్టు_విలువ;
		delay_loop(delay, delay);

	//	scl=0;
		write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG) & ~(I2C_SCL) ) );
		delay_loop(delay, delay);

		++j;
	}

	తిరిగి read_దత్తాంశం;
}

/** @fn void ReadAckForWrite(unsigned char delay)
 * @brief After the write operation is done the slave will send Ack
 *        if there is slave.
 * @details Clock line is made low to high and the slave puts the Data
 *        bit on the SDA line and master stores the value to form a byte.
 * @warning The code will be in while loop if the slave is not
 *        responding.
 * @param unsigned char delay
 */
శూన్య ReadAckForWrite(గుర్తులేని అక్షరం delay)
{
	గుర్తులేని దీర్ఘ read_దత్తాంశం = 0;
	రాయి("\n\tI2C: I2C Read\n");
	read_దత్తాంశం = read_మాట(GPIO_దత్తాంశం_REG);
	delay_loop(delay, delay);
//	scl=1;delay
	రాయి("\n\tI2C: I2C Write\n");
	write_మాట(GPIO_దత్తాంశం_REG, (read_దత్తాంశం | I2C_SCL) );
	delay_loop(delay, delay);

		రాయి("\n\tI2C: I2C Write\n");
		read_దత్తాంశం = read_మాట(GPIO_దత్తాంశం_REG)  & I2C_SDA;

//	scl=0;
	రాయి("\n\tI2C: I2C Write\n");
	write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG) & ~(I2C_SCL) ) );
	delay_loop(delay, delay);
	రాయి("\n\tI2C: I2C ReadNackForWrite sent\n");

}

/** @fn void SendAckForRead(unsigned char delay)
 * @brief After the READ operation is done the master will send Ack
 *         to slave.
 * @details The ack is sent by setting the SDA line low and then one SCL
 *         transition..
 * @warning The code will be in while loop if the slave is not
 *        responding.
 * @param unsigned char delay
 */
శూన్య SendAckForRead(గుర్తులేని అక్షరం delay)
{
	గుర్తులేని దీర్ఘ read_దత్తాంశం = 0;
  సమితి_Sda_Direction(GPIOD_IS_బహిర్గతం);

//	readData = read_word(GPIO_DATA_REG);

//	sda=0;
	write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG) & ~(I2C_SDA)) );
	delay_loop(delay, delay);

//	scl=1;
	write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG) | I2C_SCL) );
	delay_loop(delay, delay);

//	scl=0;
	write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG) & ~(I2C_SCL) ) );
	delay_loop(delay, delay);

  సమితి_Sda_Direction(GPIOD_IS_లోపల);
}

/** @fn void SendNackForRead(unsigned char delay)
 * @brief After the READ operation is done the master will send Nack
 *         to slave if it wants to terminates the I2C communication.
 * @details The ack is sent by setting the SDA line high and then one SCL
 *         transition..
 * @warning The code will be in while loop if the slave is not
 *         responding.
 * @param unsigned char delay
 */
శూన్య SendNackForRead(గుర్తులేని అక్షరం delay)
 {
  గుర్తులేని దీర్ఘ read_దత్తాంశం = 0;
  సమితి_Sda_Direction(GPIOD_IS_బహిర్గతం);

 //	readData = read_word(GPIO_DATA_REG);

 //	sda=0;
  write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG)  | (I2C_SDA)) );
  delay_loop(delay, delay);

 //	scl=1;
  write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG) | I2C_SCL) );
  delay_loop(delay, delay);

 //	scl=0;
  write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG) & ~(I2C_SCL) ) );
  delay_loop(delay, delay);

  సమితి_Sda_Direction(GPIOD_IS_లోపల);
 }

/** @fn void I2cInit()
 * @brief Configuring the SDA and SCL as OUTPUTS so that Start, Slave address
 *     ,and register address or register value that needs to be writen.
 * @details I2C master Inits makes the master ready for either read or write
 *      operation.
 * @warning This bit value can be changed as per I2C_SCL macro.
 */
శూన్య I2cInit()
{
  సమితి_SCLAs_Output();
  సమితి_Sda_Direction(GPIOD_IS_బహిర్గతం);
  రాయి("Initialization successfully done");
}

/** @fn void I2cSendSlaveAddress(unsigned char slaveAddress, unsigned char rdWrCntrl, unsigned char delay)
 * @brief Sends the slave address to the I2C device and check for acknowledge
 *       from the slave.
 * @details The master has to send the slave address along with read or write
 *    control to to access the internal registers of the I2C slave. The slave device
 *    will respond its presence by sending ack from its side
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char (Slave Address), unsigned char (delay)
 * @param unsigned char (Read / Write Control (0 --> Write, 1 --> Read)).
 * @param unsigned char delay
 */
శూన్య I2c_Send_Slave_చిరునామా(గుర్తులేని అక్షరం slave_చిరునామా, గుర్తులేని అక్షరం rdWrCntrl, గుర్తులేని అక్షరం delay)
{
  సమితి_Sda_Direction(GPIOD_IS_బహిర్గతం);

  రాయి("\n\tI2C: I2C Start\n");
  ప్రారంభం(delay);
  రాయి("\n\tI2C: I2C Send Bytes\n");
  ఒకవేళ(rdWrCntrl) {
     రాయి("\n\tI2C: I2C Write\n");
    I2cWriteByte( (slave_చిరునామా | I2C_READ), delay);
	}
  లేకపోతే {
     రాయి("\n\tI2C: I2C Write\n");
    I2cWriteByte( (slave_చిరునామా | I2C_WRITE), delay);
	}
  //	sda=1;
  write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG) | I2C_SDA) );
  delay_loop(delay, delay);

  రాయి("\n\tI2C: I2C Write Ack\n");
  సమితి_Sda_Direction(GPIOD_IS_లోపల);
    ReadAckForWrite(delay);
}

/** @fn void I2cWriteData(unsigned char writeData, unsigned char delay)
 * @brief Complete function to write a byte in to the I2C slave device.
 * @details When writing a byte, the master has to send the data first and then
 *       it needs to wait for acknowledge from the slave.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char(Data that needs to be written (can be either register address,
 *    or register value.)
 * @param unsigned char delay
 */
శూన్య I2c_Write_దత్తాంశం(గుర్తులేని అక్షరం write_దత్తాంశం, గుర్తులేని అక్షరం delay)
{
  సమితి_Sda_Direction(GPIOD_IS_బహిర్గతం);
  రాయి("\n\tI2C: I2C Write\n");
  I2cWriteByte( write_దత్తాంశం, delay);
  //	sda=1;
  write_మాట(GPIO_దత్తాంశం_REG, (read_మాట(GPIO_దత్తాంశం_REG) | I2C_SDA) );
  delay_loop(delay, delay);

  రాయి("\n\tI2C: I2C Write Ack\n");
  సమితి_Sda_Direction(GPIOD_IS_లోపల);
  ReadAckForWrite(delay);
}

/** @fn unsigned char I2cReadDataAck(unsigned char delay)
 * @brief Sends ack for the read byte.
 * @details Ack is sent to the slave so that it can make sure the data is read,
 *      by the master so that slave can send next data.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char delay
 * @return unsigned char (returns the value of readData)
 */
గుర్తులేని అక్షరం I2c_Read_దత్తాంశం_Ack(గుర్తులేని అక్షరం delay)
{
  గుర్తులేని అక్షరం read_దత్తాంశం = 0;
  సమితి_Sda_Direction(GPIOD_IS_లోపల);
	రాయి("\n\tI2C: I2C Read\n");
	read_దత్తాంశం = I2cReadByte(delay);
	సమితి_Sda_Direction(GPIOD_IS_బహిర్గతం);
	రాయి("\n\tI2C: I2C Read Ack\n");
	SendAckForRead(delay);
  తిరిగి read_దత్తాంశం;
}

/** @fn unsigned char I2cReadDataNack(unsigned char delay)
 * @brief Reads a byte from the I2C device.
 * @details Whenever the master wants to read register or memory from a device,
 *      the master can perform this action and respond with Nack to terminate the
 *      transfer.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char delay
 * @return unsigned char (returns the value of readData)
 */
గుర్తులేని అక్షరం I2c_Read_దత్తాంశం_Nack(గుర్తులేని అక్షరం delay)
{
  గుర్తులేని అక్షరం read_దత్తాంశం = 0;
  సమితి_Sda_Direction(GPIOD_IS_లోపల);
 	రాయి("\n\tI2C: I2C Read\n");
  read_దత్తాంశం = I2cReadByte(delay);
	సమితి_Sda_Direction(GPIOD_IS_బహిర్గతం);
  	రాయి("\n\tI2C: I2C Read NAck\n");
  	SendNackForRead(delay);
    తిరిగి read_దత్తాంశం;
}

/** @fn void I2cStart(unsigned char delay)
 * @brief Sending start condition for the I2C.
 * @details Start condition is making SDA low when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char delay
 */
శూన్య I2c_ప్రారంభం(గుర్తులేని అక్షరం delay)
{
  రాయి("\n\tI2C: I2C start\n");
  ప్రారంభం(delay);
}

/** @fn void I2cStop(unsigned char delay)
 * @brief Sending stop condition for the I2C.
 * @details Stop condition is making SDA high when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char delay
 */
శూన్య I2cStop(గుర్తులేని అక్షరం delay)
{
  రాయి("\n\tI2C: I2C stop\n");
  stop(delay);
}

 /** @fn void I2c_Write_byte(unsigned char slave_address,unsigned char reg_address, unsigned char data, unsigned char delay )
 * @brief To write one byte of data into a particular register of a particular slave
 * @details Write one byte of data into the particulart register of slave device with given slave address 
 * @param unsigned char slave address
 * @param unsigned char register address
 * @param unsigned char data to be written
 * @param unsigned char delay
 */
శూన్య I2c_Write_byte(గుర్తులేని అక్షరం slave_చిరునామా_2,గుర్తులేని అక్షరం reg_చిరునామా, గుర్తులేని అక్షరం దత్తాంశం_2, గుర్తులేని అక్షరం delay )
{
	I2c_Send_Slave_చిరునామా(slave_చిరునామా_2, I2C_WRITE, delay);
	I2c_Write_దత్తాంశం(reg_చిరునామా, delay);
	I2c_Write_దత్తాంశం(దత్తాంశం_2,delay);
	I2cStop(delay);
}

 /** @fn int I2c_Read_byte(unsigned char slave_address,unsigned char reg_address, unsigned char delay)
 * @brief To read one byte of data from a particular register of a particular slave
 * @detailsReads one byte of data from the particulart register of slave device with given slave address  
 * @param unsigned char(slave address)
 * @param unsigned char(register address)
 * @param unsigned char delay 
 * @return int (readdata)
 */
పూర్ణాంకం I2c_Read_byte(గుర్తులేని అక్షరం slave_చిరునామా_2,గుర్తులేని అక్షరం reg_చిరునామా, గుర్తులేని అక్షరం delay)
{
	గుర్తులేని అక్షరం read_దత్తాంశం;
	I2c_Send_Slave_చిరునామా(slave_చిరునామా_2, I2C_WRITE, delay);//selecting slave to be read
	I2c_Write_దత్తాంశం(reg_చిరునామా, delay);//selecting register to be read
	I2c_Send_Slave_చిరునామా(slave_చిరునామా_2, I2C_READ, delay);
	read_దత్తాంశం = I2c_Read_దత్తాంశం_Ack(delay);
	I2cStop(delay);
	తిరిగి (పూర్ణాంకం) read_దత్తాంశం;
}

 /** @fn int I2c_shakti_readbytes(char *buf, int count, int last, unsigned char delay)
 * @brief To burst read (i.e read multiple bytes byte of data)
 * @details Reads "n" number of bytes from the slave device with the passed slave address 
 * @param buff Buffer pointer which holds n number of read values
 * @param count to tell how many bytes to read
 * @param last decides whether to stop operation or not
 * @return int (No. of values(bytes) read)
 */
పూర్ణాంకం I2c_shakti_readbytes(అక్షరం *buf, పూర్ణాంకం లెక్క, పూర్ణాంకం చివరి, గుర్తులేని అక్షరం delay)
{
	రాయి("start reading the slave device\n");
	పూర్ణాంకం i = 0;
#నిర్వచితమైతే PCF8584
	కొరకు (i = 0; i <= లెక్క; i++) {
		ఒకవేళ (i != 0 && i < లెక్క) {
			readbuf[i]=I2c_Read_దత్తాంశం_Ack(delay);
		}
		లేకపోతే ఒకవేళ(i==0) I2c_Read_దత్తాంశం_Ack(delay);//dummy read
		లేకపోతే {
			readbuf[i] = I2c_Read_దత్తాంశం_Nack(delay);
		}
		/*The following loop is useful only  for eeprom*/
		ఒకవేళ (చివరి)  I2cStop(delay);
		లేకపోతే  I2c_ప్రారంభం(delay);//sending repeated start
	}
	తిరిగి i-1; //excluding the dummy read
#లేకపోతే
	కొరకు (i = 0; i < లెక్క-1; i++)
		*(buf + i) = I2c_Read_దత్తాంశం_Ack(delay);
	*(buf + i) = I2c_Read_దత్తాంశం_Nack(delay);

	/*The following loop is useful only  for eeprom*/
	ఒకవేళ (చివరి)
		I2cStop(delay);
	లేకపోతే
		I2c_ప్రారంభం(delay);//sending repeated start
#అయితే_ముగింపు
	తిరిగి i+1;
}
