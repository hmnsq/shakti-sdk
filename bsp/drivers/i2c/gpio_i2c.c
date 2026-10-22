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

#समावेश "platform.h"
#समावेश "gpio.h"
#समावेश "gpio_i2c.h"

/** @fn extern void delay_loop(unsigned long , unsigned long)
 * @brief Maintains the required delay to perform an operation
 * @param unsigned long 
 * @param unsigned long
 */
बाह्य व्योम delay_loop(अचिन्हित दीर्घ , अचिन्हित दीर्घ);

/** @fn static void SetSCLAsOutput()
 * @brief Function for configure GPIO 0 as SCL output.
 * @details This function will be called to make the scl line (defined by I2C_SCL)
 *             macro as output.
 * @warning This bit value can be changed as per I2C_SCL macro.
 */
अटल व्योम SetSCLAsOutput()
{
	अचिन्हित दीर्घ read_तथ्य = 0;
	read_तथ्य = read_word(GPIO_DIRECTION_CNTRL_REG);
	write_word(GPIO_DIRECTION_CNTRL_REG, (read_तथ्य | I2C_SCL) );
	म_लिखो("SCL set as output\n");
}

/** @fn static void SetSdaDirection(int inOutCntrl)
 *  @brief Function for configure GPIO 0 as SCL output.
 * @details This function will be called to make the scl line (defined by I2C_SCL)
 *           macro as output.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param int inOutCntrl
 */
अटल व्योम SetSdaDirection(पूर्णांक inOutCntrl)
{
	अचिन्हित दीर्घ read_तथ्य = 0;
	read_तथ्य = read_word(GPIO_DIRECTION_CNTRL_REG);

	अगर (inOutCntrl) { // output
		write_word(GPIO_DIRECTION_CNTRL_REG, (read_तथ्य | I2C_SDA) );
		म_लिखो("\n\tSDA set as output\n");
	}
    अन्यथा {
		write_word(GPIO_DIRECTION_CNTRL_REG, (read_तथ्य & ~(I2C_SDA) ) );
		म_लिखो("\n\tSDA set as input\n");
	}
}

/** @fn static void start(unsigned char delay)
 * @brief Sending start condition for the I2C.
 * @details Start condition is making SDA low when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char delay
 */
अटल व्योम start(अचिन्हित अक्षर delay)
{
	अचिन्हित दीर्घ read_तथ्य = 0;
	read_तथ्य = read_word(GPIO_तथ्य_REG);

//	sda=1;
	write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG) | I2C_SDA | I2C_SCL) );
	delay_loop(delay, delay);

//		scl=1;
	write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG) | I2C_SCL) );
	delay_loop(delay, delay);

//		sda=0;
	write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG) & ~(I2C_SDA)) );
	delay_loop(delay, delay);

//		scl=0;
	write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG) & ~(I2C_SCL) ) );
	delay_loop(delay, delay);

	म_लिखो("\n\tI2C: I2C Start condition sent\n");
}

/** @fn static void stop(unsigned char delay)
 * @brief Sending stop condition for the I2C.
 * @details Stop condition is making SDA high when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char
 */
अटल व्योम stop(अचिन्हित अक्षर delay)
{
	अचिन्हित दीर्घ read_तथ्य = 0;
	read_तथ्य = read_word(GPIO_तथ्य_REG);
//	sda=0;
	write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG) & ~(I2C_SDA)) );
	delay_loop(delay, delay);

//	scl=1;
	write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG) | I2C_SCL) );
	delay_loop(delay, delay);

//	sda=1;
	write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG) | I2C_SDA) );
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
व्योम I2cWriteByte(अचिन्हित अक्षर write_तथ्य, अचिन्हित अक्षर delay)
{
	अचिन्हित अक्षर j = 0,k;
	अचिन्हित दीर्घ read_तथ्य = 0;
	read_तथ्य = read_word(GPIO_तथ्य_REG);
	जबतक (j < 8)
	{
		k = write_तथ्य;
		k = ( k << j ) & 0x80;
//		printf("\n\r i: %d; j: %d; k: %d", i, j, k);
//		sda=CY;
		अगर (k == 0) {
			write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG) & ~(I2C_SDA)) );
			delay_loop(delay, delay);
		}
		अन्यथा {
			write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG) | I2C_SDA) );
			delay_loop(delay, delay);
		}

	//	scl=1;
		write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG) | I2C_SCL) );
		delay_loop(delay, delay);

	//	scl=0;
		write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG) & ~(I2C_SCL) ) );
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
	अचिन्हित अक्षर read_तथ्य = 0;
  अचिन्हित दीर्घ read_Gpio_तथ्य = 0;
	read_तथ्य = read_word(GPIO_तथ्य_REG);

//	sda=1;
//Make SDA high
	जबतक (j < 8) {
	//	scl=1;
		write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG) | I2C_SCL) );
		delay_loop(delay, delay);

//		d1 = sda;
		read_Gpio_तथ्य = read_word(GPIO_तथ्य_REG)  & I2C_SDA;
		अगर (read_Gpio_तथ्य != 0)
			bit_मूल्य = 1;
		अन्यथा
			bit_मूल्य = 0;
	    read_तथ्य = read_तथ्य << 1;
		read_तथ्य = read_तथ्य | bit_मूल्य;
		delay_loop(delay, delay);

	//	scl=0;
		write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG) & ~(I2C_SCL) ) );
		delay_loop(delay, delay);

		++j;
	}

	वापस read_तथ्य;
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
व्योम ReadAckForWrite(अचिन्हित अक्षर delay)
{
	अचिन्हित दीर्घ read_तथ्य = 0;
	म_लिखो("\n\tI2C: I2C Read\n");
	read_तथ्य = read_word(GPIO_तथ्य_REG);
	delay_loop(delay, delay);
//	scl=1;delay
	म_लिखो("\n\tI2C: I2C Write\n");
	write_word(GPIO_तथ्य_REG, (read_तथ्य | I2C_SCL) );
	delay_loop(delay, delay);

		म_लिखो("\n\tI2C: I2C Write\n");
		read_तथ्य = read_word(GPIO_तथ्य_REG)  & I2C_SDA;

//	scl=0;
	म_लिखो("\n\tI2C: I2C Write\n");
	write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG) & ~(I2C_SCL) ) );
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
व्योम SendAckForRead(अचिन्हित अक्षर delay)
{
	अचिन्हित दीर्घ read_तथ्य = 0;
  SetSdaDirection(GPIOD_IS_OUT);

//	readData = read_word(GPIO_DATA_REG);

//	sda=0;
	write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG) & ~(I2C_SDA)) );
	delay_loop(delay, delay);

//	scl=1;
	write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG) | I2C_SCL) );
	delay_loop(delay, delay);

//	scl=0;
	write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG) & ~(I2C_SCL) ) );
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
व्योम SendNackForRead(अचिन्हित अक्षर delay)
 {
  अचिन्हित दीर्घ read_तथ्य = 0;
  SetSdaDirection(GPIOD_IS_OUT);

 //	readData = read_word(GPIO_DATA_REG);

 //	sda=0;
  write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG)  | (I2C_SDA)) );
  delay_loop(delay, delay);

 //	scl=1;
  write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG) | I2C_SCL) );
  delay_loop(delay, delay);

 //	scl=0;
  write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG) & ~(I2C_SCL) ) );
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
व्योम I2cInit()
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
व्योम I2cSendSlaveAddress(अचिन्हित अक्षर slaveAddress, अचिन्हित अक्षर rdWrCntrl, अचिन्हित अक्षर delay)
{
  SetSdaDirection(GPIOD_IS_OUT);

  म_लिखो("\n\tI2C: I2C Start\n");
  start(delay);
  म_लिखो("\n\tI2C: I2C Send Bytes\n");
  अगर(rdWrCntrl) {
     म_लिखो("\n\tI2C: I2C Write\n");
    I2cWriteByte( (slaveAddress | I2C_READ), delay);
	}
  अन्यथा {
     म_लिखो("\n\tI2C: I2C Write\n");
    I2cWriteByte( (slaveAddress | I2C_WRITE), delay);
	}
  //	sda=1;
  write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG) | I2C_SDA) );
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
व्योम I2c_Write_तथ्य(अचिन्हित अक्षर write_तथ्य, अचिन्हित अक्षर delay)
{
  SetSdaDirection(GPIOD_IS_OUT);
  म_लिखो("\n\tI2C: I2C Write\n");
  I2cWriteByte( write_तथ्य, delay);
  //	sda=1;
  write_word(GPIO_तथ्य_REG, (read_word(GPIO_तथ्य_REG) | I2C_SDA) );
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
अचिन्हित अक्षर I2c_Read_तथ्य_Ack(अचिन्हित अक्षर delay)
{
  अचिन्हित अक्षर read_तथ्य = 0;
  SetSdaDirection(GPIOD_IS_IN);
	म_लिखो("\n\tI2C: I2C Read\n");
	read_तथ्य = I2cReadByte(delay);
	SetSdaDirection(GPIOD_IS_OUT);
	म_लिखो("\n\tI2C: I2C Read Ack\n");
	SendAckForRead(delay);
  वापस read_तथ्य;
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
अचिन्हित अक्षर I2c_Read_तथ्य_Nack(अचिन्हित अक्षर delay)
{
  अचिन्हित अक्षर read_तथ्य = 0;
  SetSdaDirection(GPIOD_IS_IN);
 	म_लिखो("\n\tI2C: I2C Read\n");
  read_तथ्य = I2cReadByte(delay);
	SetSdaDirection(GPIOD_IS_OUT);
  	म_लिखो("\n\tI2C: I2C Read NAck\n");
  	SendNackForRead(delay);
    वापस read_तथ्य;
}

/** @fn void I2cStart(unsigned char delay)
 * @brief Sending start condition for the I2C.
 * @details Start condition is making SDA low when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char delay
 */
व्योम I2cStart(अचिन्हित अक्षर delay)
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
व्योम I2cStop(अचिन्हित अक्षर delay)
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
व्योम I2c_Write_byte(अचिन्हित अक्षर slave_address,अचिन्हित अक्षर reg_address, अचिन्हित अक्षर तथ्य_2, अचिन्हित अक्षर delay )
{
	I2cSendSlaveAddress(slave_address, I2C_WRITE, delay);
	I2c_Write_तथ्य(reg_address, delay);
	I2c_Write_तथ्य(तथ्य_2,delay);
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
	अचिन्हित अक्षर read_तथ्य;
	I2cSendSlaveAddress(slave_address, I2C_WRITE, delay);//selecting slave to be read
	I2c_Write_तथ्य(reg_address, delay);//selecting register to be read
	I2cSendSlaveAddress(slave_address, I2C_READ, delay);
	read_तथ्य = I2c_Read_तथ्य_Ack(delay);
	I2cStop(delay);
	वापस (पूर्णांक) read_तथ्य;
}

 /** @fn int I2c_shakti_readbytes(char *buf, int count, int last, unsigned char delay)
 * @brief To burst read (i.e read multiple bytes byte of data)
 * @details Reads "n" number of bytes from the slave device with the passed slave address 
 * @param buff Buffer pointer which holds n number of read values
 * @param count to tell how many bytes to read
 * @param last decides whether to stop operation or not
 * @return int (No. of values(bytes) read)
 */
पूर्णांक I2c_shakti_readbytes(अक्षर *buf, पूर्णांक गिनती, पूर्णांक last, अचिन्हित अक्षर delay)
{
	म_लिखो("start reading the slave device\n");
	पूर्णांक i = 0;
#अगर_घोषित PCF8584
	क्रम (i = 0; i <= गिनती; i++) {
		अगर (i != 0 && i < गिनती) {
			readbuf[i]=I2c_Read_तथ्य_Ack(delay);
		}
		अन्यथा अगर(i==0) I2c_Read_तथ्य_Ack(delay);//dummy read
		अन्यथा {
			readbuf[i] = I2c_Read_तथ्य_Nack(delay);
		}
		/*The following loop is useful only  for eeprom*/
		अगर (last)  I2cStop(delay);
		अन्यथा  I2cStart(delay);//sending repeated start
	}
	वापस i-1; //excluding the dummy read
#अन्यथा
	क्रम (i = 0; i < गिनती-1; i++)
		*(buf + i) = I2c_Read_तथ्य_Ack(delay);
	*(buf + i) = I2c_Read_तथ्य_Nack(delay);

	/*The following loop is useful only  for eeprom*/
	अगर (last)
		I2cStop(delay);
	अन्यथा
		I2cStart(delay);//sending repeated start
#पूर्ण_अगर
	वापस i+1;
}
