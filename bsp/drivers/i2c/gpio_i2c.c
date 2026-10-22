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

#অন্তর্ভাব "platform.h"
#অন্তর্ভাব "gpio.h"
#অন্তর্ভাব "gpio_i2c.h"

/** @fn extern void delay_loop(unsigned long , unsigned long)
 * @brief Maintains the required delay to perform an operation
 * @param unsigned long 
 * @param unsigned long
 */
বাহ্যিক শূন্য delay_loop(unsigned long , unsigned long);

/** @fn static void SetSCLAsOutput()
 * @brief Function for configure GPIO 0 as SCL output.
 * @details This function will be called to make the scl line (defined by I2C_SCL)
 *             macro as output.
 * @warning This bit value can be changed as per I2C_SCL macro.
 */
স্থির শূন্য SetSCLAsOutput()
{
	unsigned long read_তথ্য = 0;
	read_তথ্য = read_word(GPIO_DIRECTION_CNTRL_REG);
	write_word(GPIO_DIRECTION_CNTRL_REG, (read_তথ্য | I2C_SCL) );
	printf("SCL set as output\n");
}

/** @fn static void SetSdaDirection(int inOutCntrl)
 *  @brief Function for configure GPIO 0 as SCL output.
 * @details This function will be called to make the scl line (defined by I2C_SCL)
 *           macro as output.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param int inOutCntrl
 */
স্থির শূন্য SetSdaDirection(পূর্ণসংখ্যা inOutCntrl)
{
	unsigned long read_তথ্য = 0;
	read_তথ্য = read_word(GPIO_DIRECTION_CNTRL_REG);

	যদি (inOutCntrl) { // output
		write_word(GPIO_DIRECTION_CNTRL_REG, (read_তথ্য | I2C_SDA) );
		printf("\n\tSDA set as output\n");
	}
    অন্যথা {
		write_word(GPIO_DIRECTION_CNTRL_REG, (read_তথ্য & ~(I2C_SDA) ) );
		printf("\n\tSDA set as input\n");
	}
}

/** @fn static void start(unsigned char delay)
 * @brief Sending start condition for the I2C.
 * @details Start condition is making SDA low when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char delay
 */
স্থির শূন্য start(unsigned অক্ষর delay)
{
	unsigned long read_তথ্য = 0;
	read_তথ্য = read_word(GPIO_তথ্য_REG);

//	sda=1;
	write_word(GPIO_তথ্য_REG, (read_word(GPIO_তথ্য_REG) | I2C_SDA | I2C_SCL) );
	delay_loop(delay, delay);

//		scl=1;
	write_word(GPIO_তথ্য_REG, (read_word(GPIO_তথ্য_REG) | I2C_SCL) );
	delay_loop(delay, delay);

//		sda=0;
	write_word(GPIO_তথ্য_REG, (read_word(GPIO_তথ্য_REG) & ~(I2C_SDA)) );
	delay_loop(delay, delay);

//		scl=0;
	write_word(GPIO_তথ্য_REG, (read_word(GPIO_তথ্য_REG) & ~(I2C_SCL) ) );
	delay_loop(delay, delay);

	printf("\n\tI2C: I2C Start condition sent\n");
}

/** @fn static void stop(unsigned char delay)
 * @brief Sending stop condition for the I2C.
 * @details Stop condition is making SDA high when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char
 */
স্থির শূন্য stop(unsigned অক্ষর delay)
{
	unsigned long read_তথ্য = 0;
	read_তথ্য = read_word(GPIO_তথ্য_REG);
//	sda=0;
	write_word(GPIO_তথ্য_REG, (read_word(GPIO_তথ্য_REG) & ~(I2C_SDA)) );
	delay_loop(delay, delay);

//	scl=1;
	write_word(GPIO_তথ্য_REG, (read_word(GPIO_তথ্য_REG) | I2C_SCL) );
	delay_loop(delay, delay);

//	sda=1;
	write_word(GPIO_তথ্য_REG, (read_word(GPIO_তথ্য_REG) | I2C_SDA) );
	delay_loop(delay, delay);
	printf("\n\tI2C: I2C Start condition sent\n");

}

/** @fn void I2cWriteByte(unsigned char writeData, unsigned char delay)
 * @brief Writes a byte to the I2C device.
 * @details Data is put on the SDA Line bit by bit and then makes the
 *  SCL from low to high to write..
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param writeData --> Value that needs to be written.
 * @param unsigned char delay
 */
শূন্য I2cWriteByte(unsigned অক্ষর write_তথ্য, unsigned অক্ষর delay)
{
	unsigned অক্ষর j = 0,k;
	unsigned long read_তথ্য = 0;
	read_তথ্য = read_word(GPIO_তথ্য_REG);
	যখন (j < 8)
	{
		k = write_তথ্য;
		k = ( k << j ) & 0x80;
//		printf("\n\r i: %d; j: %d; k: %d", i, j, k);
//		sda=CY;
		যদি (k == 0) {
			write_word(GPIO_তথ্য_REG, (read_word(GPIO_তথ্য_REG) & ~(I2C_SDA)) );
			delay_loop(delay, delay);
		}
		অন্যথা {
			write_word(GPIO_তথ্য_REG, (read_word(GPIO_তথ্য_REG) | I2C_SDA) );
			delay_loop(delay, delay);
		}

	//	scl=1;
		write_word(GPIO_তথ্য_REG, (read_word(GPIO_তথ্য_REG) | I2C_SCL) );
		delay_loop(delay, delay);

	//	scl=0;
		write_word(GPIO_তথ্য_REG, (read_word(GPIO_তথ্য_REG) & ~(I2C_SCL) ) );
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
unsigned অক্ষর I2cReadByte(unsigned অক্ষর delay)
{
	unsigned অক্ষর j = 0, i = 0;
	unsigned অক্ষর bit_মান;
	unsigned অক্ষর read_তথ্য = 0;
  unsigned long read_Gpio_তথ্য = 0;
	read_তথ্য = read_word(GPIO_তথ্য_REG);

//	sda=1;
//Make SDA high
	যখন (j < 8) {
	//	scl=1;
		write_word(GPIO_তথ্য_REG, (read_word(GPIO_তথ্য_REG) | I2C_SCL) );
		delay_loop(delay, delay);

//		d1 = sda;
		read_Gpio_তথ্য = read_word(GPIO_তথ্য_REG)  & I2C_SDA;
		যদি (read_Gpio_তথ্য != 0)
			bit_মান = 1;
		অন্যথা
			bit_মান = 0;
	    read_তথ্য = read_তথ্য << 1;
		read_তথ্য = read_তথ্য | bit_মান;
		delay_loop(delay, delay);

	//	scl=0;
		write_word(GPIO_তথ্য_REG, (read_word(GPIO_তথ্য_REG) & ~(I2C_SCL) ) );
		delay_loop(delay, delay);

		++j;
	}

	ফেরত read_তথ্য;
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
শূন্য ReadAckForWrite(unsigned অক্ষর delay)
{
	unsigned long read_তথ্য = 0;
	printf("\n\tI2C: I2C Read\n");
	read_তথ্য = read_word(GPIO_তথ্য_REG);
	delay_loop(delay, delay);
//	scl=1;delay
	printf("\n\tI2C: I2C Write\n");
	write_word(GPIO_তথ্য_REG, (read_তথ্য | I2C_SCL) );
	delay_loop(delay, delay);

		printf("\n\tI2C: I2C Write\n");
		read_তথ্য = read_word(GPIO_তথ্য_REG)  & I2C_SDA;

//	scl=0;
	printf("\n\tI2C: I2C Write\n");
	write_word(GPIO_তথ্য_REG, (read_word(GPIO_তথ্য_REG) & ~(I2C_SCL) ) );
	delay_loop(delay, delay);
	printf("\n\tI2C: I2C ReadNackForWrite sent\n");

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
শূন্য SendAckForRead(unsigned অক্ষর delay)
{
	unsigned long read_তথ্য = 0;
  SetSdaDirection(GPIOD_IS_OUT);

//	readData = read_word(GPIO_DATA_REG);

//	sda=0;
	write_word(GPIO_তথ্য_REG, (read_word(GPIO_তথ্য_REG) & ~(I2C_SDA)) );
	delay_loop(delay, delay);

//	scl=1;
	write_word(GPIO_তথ্য_REG, (read_word(GPIO_তথ্য_REG) | I2C_SCL) );
	delay_loop(delay, delay);

//	scl=0;
	write_word(GPIO_তথ্য_REG, (read_word(GPIO_তথ্য_REG) & ~(I2C_SCL) ) );
	delay_loop(delay, delay);

  SetSdaDirection(GPIOD_IS_IN);
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
শূন্য SendNackForRead(unsigned অক্ষর delay)
 {
  unsigned long read_তথ্য = 0;
  SetSdaDirection(GPIOD_IS_OUT);

 //	readData = read_word(GPIO_DATA_REG);

 //	sda=0;
  write_word(GPIO_তথ্য_REG, (read_word(GPIO_তথ্য_REG)  | (I2C_SDA)) );
  delay_loop(delay, delay);

 //	scl=1;
  write_word(GPIO_তথ্য_REG, (read_word(GPIO_তথ্য_REG) | I2C_SCL) );
  delay_loop(delay, delay);

 //	scl=0;
  write_word(GPIO_তথ্য_REG, (read_word(GPIO_তথ্য_REG) & ~(I2C_SCL) ) );
  delay_loop(delay, delay);

  SetSdaDirection(GPIOD_IS_IN);
 }

/** @fn void I2cInit()
 * @brief Configuring the SDA and SCL as OUTPUTS so that Start, Slave address
 *     ,and register address or register value that needs to be writen.
 * @details I2C master Inits makes the master ready for either read or write
 *      operation.
 * @warning This bit value can be changed as per I2C_SCL macro.
 */
শূন্য I2cInit()
{
  SetSCLAsOutput();
  SetSdaDirection(GPIOD_IS_OUT);
  printf("Initialization successfully done");
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
শূন্য I2cSendSlaveAddress(unsigned অক্ষর slaveAddress, unsigned অক্ষর rdWrCntrl, unsigned অক্ষর delay)
{
  SetSdaDirection(GPIOD_IS_OUT);

  printf("\n\tI2C: I2C Start\n");
  start(delay);
  printf("\n\tI2C: I2C Send Bytes\n");
  যদি(rdWrCntrl) {
     printf("\n\tI2C: I2C Write\n");
    I2cWriteByte( (slaveAddress | I2C_READ), delay);
	}
  অন্যথা {
     printf("\n\tI2C: I2C Write\n");
    I2cWriteByte( (slaveAddress | I2C_WRITE), delay);
	}
  //	sda=1;
  write_word(GPIO_তথ্য_REG, (read_word(GPIO_তথ্য_REG) | I2C_SDA) );
  delay_loop(delay, delay);

  printf("\n\tI2C: I2C Write Ack\n");
  SetSdaDirection(GPIOD_IS_IN);
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
শূন্য I2c_Write_তথ্য(unsigned অক্ষর write_তথ্য, unsigned অক্ষর delay)
{
  SetSdaDirection(GPIOD_IS_OUT);
  printf("\n\tI2C: I2C Write\n");
  I2cWriteByte( write_তথ্য, delay);
  //	sda=1;
  write_word(GPIO_তথ্য_REG, (read_word(GPIO_তথ্য_REG) | I2C_SDA) );
  delay_loop(delay, delay);

  printf("\n\tI2C: I2C Write Ack\n");
  SetSdaDirection(GPIOD_IS_IN);
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
unsigned অক্ষর I2c_Read_তথ্য_Ack(unsigned অক্ষর delay)
{
  unsigned অক্ষর read_তথ্য = 0;
  SetSdaDirection(GPIOD_IS_IN);
	printf("\n\tI2C: I2C Read\n");
	read_তথ্য = I2cReadByte(delay);
	SetSdaDirection(GPIOD_IS_OUT);
	printf("\n\tI2C: I2C Read Ack\n");
	SendAckForRead(delay);
  ফেরত read_তথ্য;
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
unsigned অক্ষর I2c_Read_তথ্য_Nack(unsigned অক্ষর delay)
{
  unsigned অক্ষর read_তথ্য = 0;
  SetSdaDirection(GPIOD_IS_IN);
 	printf("\n\tI2C: I2C Read\n");
  read_তথ্য = I2cReadByte(delay);
	SetSdaDirection(GPIOD_IS_OUT);
  	printf("\n\tI2C: I2C Read NAck\n");
  	SendNackForRead(delay);
    ফেরত read_তথ্য;
}

/** @fn void I2cStart(unsigned char delay)
 * @brief Sending start condition for the I2C.
 * @details Start condition is making SDA low when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char delay
 */
শূন্য I2cStart(unsigned অক্ষর delay)
{
  printf("\n\tI2C: I2C start\n");
  start(delay);
}

/** @fn void I2cStop(unsigned char delay)
 * @brief Sending stop condition for the I2C.
 * @details Stop condition is making SDA high when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char delay
 */
শূন্য I2cStop(unsigned অক্ষর delay)
{
  printf("\n\tI2C: I2C stop\n");
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
শূন্য I2c_Write_byte(unsigned অক্ষর slave_address,unsigned অক্ষর reg_address, unsigned অক্ষর তথ্য_2, unsigned অক্ষর delay )
{
	I2cSendSlaveAddress(slave_address, I2C_WRITE, delay);
	I2c_Write_তথ্য(reg_address, delay);
	I2c_Write_তথ্য(তথ্য_2,delay);
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
পূর্ণসংখ্যা I2c_Read_byte(unsigned অক্ষর slave_address,unsigned অক্ষর reg_address, unsigned অক্ষর delay)
{
	unsigned অক্ষর read_তথ্য;
	I2cSendSlaveAddress(slave_address, I2C_WRITE, delay);//selecting slave to be read
	I2c_Write_তথ্য(reg_address, delay);//selecting register to be read
	I2cSendSlaveAddress(slave_address, I2C_READ, delay);
	read_তথ্য = I2c_Read_তথ্য_Ack(delay);
	I2cStop(delay);
	ফেরত (পূর্ণসংখ্যা) read_তথ্য;
}

 /** @fn int I2c_shakti_readbytes(char *buf, int count, int last, unsigned char delay)
 * @brief To burst read (i.e read multiple bytes byte of data)
 * @details Reads "n" number of bytes from the slave device with the passed slave address 
 * @param buff Buffer pointer which holds n number of read values
 * @param count to tell how many bytes to read
 * @param last decides whether to stop operation or not
 * @return int (No. of values(bytes) read)
 */
পূর্ণসংখ্যা I2c_shakti_readbytes(অক্ষর *buf, পূর্ণসংখ্যা গুনতি, পূর্ণসংখ্যা last, unsigned অক্ষর delay)
{
	printf("start reading the slave device\n");
	পূর্ণসংখ্যা i = 0;
#ifdef PCF8584
	জন্য (i = 0; i <= গুনতি; i++) {
		যদি (i != 0 && i < গুনতি) {
			readbuf[i]=I2c_Read_তথ্য_Ack(delay);
		}
		অন্যথা যদি(i==0) I2c_Read_তথ্য_Ack(delay);//dummy read
		অন্যথা {
			readbuf[i] = I2c_Read_তথ্য_Nack(delay);
		}
		/*The following loop is useful only  for eeprom*/
		যদি (last)  I2cStop(delay);
		অন্যথা  I2cStart(delay);//sending repeated start
	}
	ফেরত i-1; //excluding the dummy read
#অন্যথা
	জন্য (i = 0; i < গুনতি-1; i++)
		*(buf + i) = I2c_Read_তথ্য_Ack(delay);
	*(buf + i) = I2c_Read_তথ্য_Nack(delay);

	/*The following loop is useful only  for eeprom*/
	যদি (last)
		I2cStop(delay);
	অন্যথা
		I2cStart(delay);//sending repeated start
#endif
	ফেরত i+1;
}
