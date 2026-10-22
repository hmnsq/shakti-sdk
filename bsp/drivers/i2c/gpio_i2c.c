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

#अन्तर्भाव "platform.h"
#अन्तर्भाव "gpio.h"
#अन्तर्भाव "gpio_i2c.h"

/** @fn extern void delay_loop(unsigned long , unsigned long)
 * @brief Maintains the required delay to perform an operation
 * @param unsigned long 
 * @param unsigned long
 */
बाह्य शून्य delay_loop(अचिन्हित दीर्घ , अचिन्हित दीर्घ);

/** @fn static void SetSCLAsOutput()
 * @brief Function for configure GPIO 0 as SCL output.
 * @details This function will be called to make the scl line (defined by I2C_SCL)
 *             macro as output.
 * @warning This bit value can be changed as per I2C_SCL macro.
 */
स्थिर शून्य SetSCLAsOutput()
{
	अचिन्हित दीर्घ readData = 0;
	readData = read_word(GPIO_DIRECTION_CNTRL_REG);
	write_word(GPIO_DIRECTION_CNTRL_REG, (readData | I2C_SCL) );
	म_लिखो("SCL set as output\n");
}

/** @fn static void SetSdaDirection(int inOutCntrl)
 *  @brief Function for configure GPIO 0 as SCL output.
 * @details This function will be called to make the scl line (defined by I2C_SCL)
 *           macro as output.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param int inOutCntrl
 */
स्थिर शून्य SetSdaDirection(पूर्णांक inOutCntrl)
{
	अचिन्हित दीर्घ readData = 0;
	readData = read_word(GPIO_DIRECTION_CNTRL_REG);

	जर (inOutCntrl) { // output
		write_word(GPIO_DIRECTION_CNTRL_REG, (readData | I2C_SDA) );
		म_लिखो("\n\tSDA set as output\n");
	}
    अन्यथा {
		write_word(GPIO_DIRECTION_CNTRL_REG, (readData & ~(I2C_SDA) ) );
		म_लिखो("\n\tSDA set as input\n");
	}
}

/** @fn static void start(unsigned char delay)
 * @brief Sending start condition for the I2C.
 * @details Start condition is making SDA low when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char delay
 */
स्थिर शून्य start(अचिन्हित अक्षर delay)
{
	अचिन्हित दीर्घ readData = 0;
	readData = read_word(GPIO_DATA_REG);

//	sda=1;
	write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) | I2C_SDA | I2C_SCL) );
	delay_loop(delay, delay);

//		scl=1;
	write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) | I2C_SCL) );
	delay_loop(delay, delay);

//		sda=0;
	write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) & ~(I2C_SDA)) );
	delay_loop(delay, delay);

//		scl=0;
	write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) & ~(I2C_SCL) ) );
	delay_loop(delay, delay);

	म_लिखो("\n\tI2C: I2C Start condition sent\n");
}

/** @fn static void stop(unsigned char delay)
 * @brief Sending stop condition for the I2C.
 * @details Stop condition is making SDA high when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char
 */
स्थिर शून्य stop(अचिन्हित अक्षर delay)
{
	अचिन्हित दीर्घ readData = 0;
	readData = read_word(GPIO_DATA_REG);
//	sda=0;
	write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) & ~(I2C_SDA)) );
	delay_loop(delay, delay);

//	scl=1;
	write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) | I2C_SCL) );
	delay_loop(delay, delay);

//	sda=1;
	write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) | I2C_SDA) );
	delay_loop(delay, delay);
	म_लिखो("\n\tI2C: I2C Start condition sent\n");

}

/** @fn void I2cWriteByte(unsigned char writeData, unsigned char delay)
 * @brief Writes a byte to the I2C device.
 * @details Data is put on the SDA Line bit by bit and then makes the
 *  SCL from low to high to write..
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param writeData --> Value that needs to be written.
 * @param unsigned char delay
 */
शून्य I2cWriteByte(अचिन्हित अक्षर writeData, अचिन्हित अक्षर delay)
{
	अचिन्हित अक्षर j = 0,k;
	अचिन्हित दीर्घ readData = 0;
	readData = read_word(GPIO_DATA_REG);
	पर्यंत (j < 8)
	{
		k = writeData;
		k = ( k << j ) & 0x80;
//		printf("\n\r i: %d; j: %d; k: %d", i, j, k);
//		sda=CY;
		जर (k == 0) {
			write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) & ~(I2C_SDA)) );
			delay_loop(delay, delay);
		}
		अन्यथा {
			write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) | I2C_SDA) );
			delay_loop(delay, delay);
		}

	//	scl=1;
		write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) | I2C_SCL) );
		delay_loop(delay, delay);

	//	scl=0;
		write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) & ~(I2C_SCL) ) );
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
अचिन्हित अक्षर I2cReadByte(अचिन्हित अक्षर delay)
{
	अचिन्हित अक्षर j = 0, i = 0;
	अचिन्हित अक्षर bit_मूल्य;
	अचिन्हित अक्षर readData = 0;
  अचिन्हित दीर्घ readGpioData = 0;
	readData = read_word(GPIO_DATA_REG);

//	sda=1;
//Make SDA high
	पर्यंत (j < 8) {
	//	scl=1;
		write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) | I2C_SCL) );
		delay_loop(delay, delay);

//		d1 = sda;
		readGpioData = read_word(GPIO_DATA_REG)  & I2C_SDA;
		जर (readGpioData != 0)
			bit_मूल्य = 1;
		अन्यथा
			bit_मूल्य = 0;
	    readData = readData << 1;
		readData = readData | bit_मूल्य;
		delay_loop(delay, delay);

	//	scl=0;
		write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) & ~(I2C_SCL) ) );
		delay_loop(delay, delay);

		++j;
	}

	परत readData;
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
शून्य ReadAckForWrite(अचिन्हित अक्षर delay)
{
	अचिन्हित दीर्घ readData = 0;
	म_लिखो("\n\tI2C: I2C Read\n");
	readData = read_word(GPIO_DATA_REG);
	delay_loop(delay, delay);
//	scl=1;delay
	म_लिखो("\n\tI2C: I2C Write\n");
	write_word(GPIO_DATA_REG, (readData | I2C_SCL) );
	delay_loop(delay, delay);

		म_लिखो("\n\tI2C: I2C Write\n");
		readData = read_word(GPIO_DATA_REG)  & I2C_SDA;

//	scl=0;
	म_लिखो("\n\tI2C: I2C Write\n");
	write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) & ~(I2C_SCL) ) );
	delay_loop(delay, delay);
	म_लिखो("\n\tI2C: I2C ReadNackForWrite sent\n");

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
शून्य SendAckForRead(अचिन्हित अक्षर delay)
{
	अचिन्हित दीर्घ readData = 0;
  SetSdaDirection(GPIOD_IS_OUT);

//	readData = read_word(GPIO_DATA_REG);

//	sda=0;
	write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) & ~(I2C_SDA)) );
	delay_loop(delay, delay);

//	scl=1;
	write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) | I2C_SCL) );
	delay_loop(delay, delay);

//	scl=0;
	write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) & ~(I2C_SCL) ) );
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
शून्य SendNackForRead(अचिन्हित अक्षर delay)
 {
  अचिन्हित दीर्घ readData = 0;
  SetSdaDirection(GPIOD_IS_OUT);

 //	readData = read_word(GPIO_DATA_REG);

 //	sda=0;
  write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG)  | (I2C_SDA)) );
  delay_loop(delay, delay);

 //	scl=1;
  write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) | I2C_SCL) );
  delay_loop(delay, delay);

 //	scl=0;
  write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) & ~(I2C_SCL) ) );
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
शून्य I2cInit()
{
  SetSCLAsOutput();
  SetSdaDirection(GPIOD_IS_OUT);
  म_लिखो("Initialization successfully done");
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
शून्य I2cSendSlaveAddress(अचिन्हित अक्षर slaveAddress, अचिन्हित अक्षर rdWrCntrl, अचिन्हित अक्षर delay)
{
  SetSdaDirection(GPIOD_IS_OUT);

  म_लिखो("\n\tI2C: I2C Start\n");
  start(delay);
  म_लिखो("\n\tI2C: I2C Send Bytes\n");
  जर(rdWrCntrl) {
     म_लिखो("\n\tI2C: I2C Write\n");
    I2cWriteByte( (slaveAddress | I2C_READ), delay);
	}
  अन्यथा {
     म_लिखो("\n\tI2C: I2C Write\n");
    I2cWriteByte( (slaveAddress | I2C_WRITE), delay);
	}
  //	sda=1;
  write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) | I2C_SDA) );
  delay_loop(delay, delay);

  म_लिखो("\n\tI2C: I2C Write Ack\n");
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
शून्य I2cWriteData(अचिन्हित अक्षर writeData, अचिन्हित अक्षर delay)
{
  SetSdaDirection(GPIOD_IS_OUT);
  म_लिखो("\n\tI2C: I2C Write\n");
  I2cWriteByte( writeData, delay);
  //	sda=1;
  write_word(GPIO_DATA_REG, (read_word(GPIO_DATA_REG) | I2C_SDA) );
  delay_loop(delay, delay);

  म_लिखो("\n\tI2C: I2C Write Ack\n");
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
अचिन्हित अक्षर I2cReadDataAck(अचिन्हित अक्षर delay)
{
  अचिन्हित अक्षर readData = 0;
  SetSdaDirection(GPIOD_IS_IN);
	म_लिखो("\n\tI2C: I2C Read\n");
	readData = I2cReadByte(delay);
	SetSdaDirection(GPIOD_IS_OUT);
	म_लिखो("\n\tI2C: I2C Read Ack\n");
	SendAckForRead(delay);
  परत readData;
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
अचिन्हित अक्षर I2cReadDataNack(अचिन्हित अक्षर delay)
{
  अचिन्हित अक्षर readData = 0;
  SetSdaDirection(GPIOD_IS_IN);
 	म_लिखो("\n\tI2C: I2C Read\n");
  readData = I2cReadByte(delay);
	SetSdaDirection(GPIOD_IS_OUT);
  	म_लिखो("\n\tI2C: I2C Read NAck\n");
  	SendNackForRead(delay);
    परत readData;
}

/** @fn void I2cStart(unsigned char delay)
 * @brief Sending start condition for the I2C.
 * @details Start condition is making SDA low when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char delay
 */
शून्य I2cStart(अचिन्हित अक्षर delay)
{
  म_लिखो("\n\tI2C: I2C start\n");
  start(delay);
}

/** @fn void I2cStop(unsigned char delay)
 * @brief Sending stop condition for the I2C.
 * @details Stop condition is making SDA high when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char delay
 */
शून्य I2cStop(अचिन्हित अक्षर delay)
{
  म_लिखो("\n\tI2C: I2C stop\n");
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
शून्य I2c_Write_byte(अचिन्हित अक्षर slave_address,अचिन्हित अक्षर reg_address, अचिन्हित अक्षर data, अचिन्हित अक्षर delay )
{
	I2cSendSlaveAddress(slave_address, I2C_WRITE, delay);
	I2cWriteData(reg_address, delay);
	I2cWriteData(data,delay);
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
पूर्णांक I2c_Read_byte(अचिन्हित अक्षर slave_address,अचिन्हित अक्षर reg_address, अचिन्हित अक्षर delay)
{
	अचिन्हित अक्षर readData;
	I2cSendSlaveAddress(slave_address, I2C_WRITE, delay);//selecting slave to be read
	I2cWriteData(reg_address, delay);//selecting register to be read
	I2cSendSlaveAddress(slave_address, I2C_READ, delay);
	readData = I2cReadDataAck(delay);
	I2cStop(delay);
	परत (पूर्णांक) readData;
}

 /** @fn int I2c_shakti_readbytes(char *buf, int count, int last, unsigned char delay)
 * @brief To burst read (i.e read multiple bytes byte of data)
 * @details Reads "n" number of bytes from the slave device with the passed slave address 
 * @param buff Buffer pointer which holds n number of read values
 * @param count to tell how many bytes to read
 * @param last decides whether to stop operation or not
 * @return int (No. of values(bytes) read)
 */
पूर्णांक I2c_shakti_readbytes(अक्षर *buf, पूर्णांक मोजणी, पूर्णांक last, अचिन्हित अक्षर delay)
{
	म_लिखो("start reading the slave device\n");
	पूर्णांक i = 0;
#ifdef PCF8584
	साठी (i = 0; i <= मोजणी; i++) {
		जर (i != 0 && i < मोजणी) {
			readbuf[i]=I2cReadDataAck(delay);
		}
		अन्यथा जर(i==0) I2cReadDataAck(delay);//dummy read
		अन्यथा {
			readbuf[i] = I2cReadDataNack(delay);
		}
		/*The following loop is useful only  for eeprom*/
		जर (last)  I2cStop(delay);
		अन्यथा  I2cStart(delay);//sending repeated start
	}
	परत i-1; //excluding the dummy read
#अन्यथा
	साठी (i = 0; i < मोजणी-1; i++)
		*(buf + i) = I2cReadDataAck(delay);
	*(buf + i) = I2cReadDataNack(delay);

	/*The following loop is useful only  for eeprom*/
	जर (last)
		I2cStop(delay);
	अन्यथा
		I2cStart(delay);//sending repeated start
#endif
	परत i+1;
}
