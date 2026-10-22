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
बाह्य शून्य delay_loop(अचिह्नित दीर्घ , अचिह्नित दीर्घ);

/** @fn static void SetSCLAsOutput()
 * @brief Function for configure GPIO 0 as SCL output.
 * @details This function will be called to make the scl line (defined by I2C_SCL)
 *             macro as output.
 * @warning This bit value can be changed as per I2C_SCL macro.
 */
स्थिर शून्य समुच्चयः_SCLAs_Output()
{
	अचिह्नित दीर्घ read_दत्त = 0;
	read_दत्त = read_word(GPIO_DIRECTION_CNTRL_REG);
	write_word(GPIO_DIRECTION_CNTRL_REG, (read_दत्त | I2C_SCL) );
	प्रारूप_लिख("SCL set as output\n");
}

/** @fn static void SetSdaDirection(int inOutCntrl)
 *  @brief Function for configure GPIO 0 as SCL output.
 * @details This function will be called to make the scl line (defined by I2C_SCL)
 *           macro as output.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param int inOutCntrl
 */
स्थिर शून्य समुच्चयः_Sda_Direction(पूर्णाङ्क अन्तर्_बहिर्गमनम्_Cntrl)
{
	अचिह्नित दीर्घ read_दत्त = 0;
	read_दत्त = read_word(GPIO_DIRECTION_CNTRL_REG);

	यदि (अन्तर्_बहिर्गमनम्_Cntrl) { // output
		write_word(GPIO_DIRECTION_CNTRL_REG, (read_दत्त | I2C_SDA) );
		प्रारूप_लिख("\n\tSDA set as output\n");
	}
    अन्यथा {
		write_word(GPIO_DIRECTION_CNTRL_REG, (read_दत्त & ~(I2C_SDA) ) );
		प्रारूप_लिख("\n\tSDA set as input\n");
	}
}

/** @fn static void start(unsigned char delay)
 * @brief Sending start condition for the I2C.
 * @details Start condition is making SDA low when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char delay
 */
स्थिर शून्य start(अचिह्नित वर्ण delay)
{
	अचिह्नित दीर्घ read_दत्त = 0;
	read_दत्त = read_word(GPIO_दत्त_REG);

//	sda=1;
	write_word(GPIO_दत्त_REG, (read_word(GPIO_दत्त_REG) | I2C_SDA | I2C_SCL) );
	delay_loop(delay, delay);

//		scl=1;
	write_word(GPIO_दत्त_REG, (read_word(GPIO_दत्त_REG) | I2C_SCL) );
	delay_loop(delay, delay);

//		sda=0;
	write_word(GPIO_दत्त_REG, (read_word(GPIO_दत्त_REG) & ~(I2C_SDA)) );
	delay_loop(delay, delay);

//		scl=0;
	write_word(GPIO_दत्त_REG, (read_word(GPIO_दत्त_REG) & ~(I2C_SCL) ) );
	delay_loop(delay, delay);

	प्रारूप_लिख("\n\tI2C: I2C Start condition sent\n");
}

/** @fn static void stop(unsigned char delay)
 * @brief Sending stop condition for the I2C.
 * @details Stop condition is making SDA high when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char
 */
स्थिर शून्य stop(अचिह्नित वर्ण delay)
{
	अचिह्नित दीर्घ read_दत्त = 0;
	read_दत्त = read_word(GPIO_दत्त_REG);
//	sda=0;
	write_word(GPIO_दत्त_REG, (read_word(GPIO_दत्त_REG) & ~(I2C_SDA)) );
	delay_loop(delay, delay);

//	scl=1;
	write_word(GPIO_दत्त_REG, (read_word(GPIO_दत्त_REG) | I2C_SCL) );
	delay_loop(delay, delay);

//	sda=1;
	write_word(GPIO_दत्त_REG, (read_word(GPIO_दत्त_REG) | I2C_SDA) );
	delay_loop(delay, delay);
	प्रारूप_लिख("\n\tI2C: I2C Start condition sent\n");

}

/** @fn void I2cWriteByte(unsigned char writeData, unsigned char delay)
 * @brief Writes a byte to the I2C device.
 * @details Data is put on the SDA Line bit by bit and then makes the
 *  SCL from low to high to write..
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param writeData --> Value that needs to be written.
 * @param unsigned char delay
 */
शून्य I2cWriteByte(अचिह्नित वर्ण write_दत्त, अचिह्नित वर्ण delay)
{
	अचिह्नित वर्ण j = 0,k;
	अचिह्नित दीर्घ read_दत्त = 0;
	read_दत्त = read_word(GPIO_दत्त_REG);
	यावत् (j < 8)
	{
		k = write_दत्त;
		k = ( k << j ) & 0x80;
//		printf("\n\r i: %d; j: %d; k: %d", i, j, k);
//		sda=CY;
		यदि (k == 0) {
			write_word(GPIO_दत्त_REG, (read_word(GPIO_दत्त_REG) & ~(I2C_SDA)) );
			delay_loop(delay, delay);
		}
		अन्यथा {
			write_word(GPIO_दत्त_REG, (read_word(GPIO_दत्त_REG) | I2C_SDA) );
			delay_loop(delay, delay);
		}

	//	scl=1;
		write_word(GPIO_दत्त_REG, (read_word(GPIO_दत्त_REG) | I2C_SCL) );
		delay_loop(delay, delay);

	//	scl=0;
		write_word(GPIO_दत्त_REG, (read_word(GPIO_दत्त_REG) & ~(I2C_SCL) ) );
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
अचिह्नित वर्ण I2cReadByte(अचिह्नित वर्ण delay)
{
	अचिह्नित वर्ण j = 0, i = 0;
	अचिह्नित वर्ण bit_मानम्;
	अचिह्नित वर्ण read_दत्त = 0;
  अचिह्नित दीर्घ read_Gpio_दत्त = 0;
	read_दत्त = read_word(GPIO_दत्त_REG);

//	sda=1;
//Make SDA high
	यावत् (j < 8) {
	//	scl=1;
		write_word(GPIO_दत्त_REG, (read_word(GPIO_दत्त_REG) | I2C_SCL) );
		delay_loop(delay, delay);

//		d1 = sda;
		read_Gpio_दत्त = read_word(GPIO_दत्त_REG)  & I2C_SDA;
		यदि (read_Gpio_दत्त != 0)
			bit_मानम् = 1;
		अन्यथा
			bit_मानम् = 0;
	    read_दत्त = read_दत्त << 1;
		read_दत्त = read_दत्त | bit_मानम्;
		delay_loop(delay, delay);

	//	scl=0;
		write_word(GPIO_दत्त_REG, (read_word(GPIO_दत्त_REG) & ~(I2C_SCL) ) );
		delay_loop(delay, delay);

		++j;
	}

	प्रत्यागम read_दत्त;
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
शून्य ReadAckForWrite(अचिह्नित वर्ण delay)
{
	अचिह्नित दीर्घ read_दत्त = 0;
	प्रारूप_लिख("\n\tI2C: I2C Read\n");
	read_दत्त = read_word(GPIO_दत्त_REG);
	delay_loop(delay, delay);
//	scl=1;delay
	प्रारूप_लिख("\n\tI2C: I2C Write\n");
	write_word(GPIO_दत्त_REG, (read_दत्त | I2C_SCL) );
	delay_loop(delay, delay);

		प्रारूप_लिख("\n\tI2C: I2C Write\n");
		read_दत्त = read_word(GPIO_दत्त_REG)  & I2C_SDA;

//	scl=0;
	प्रारूप_लिख("\n\tI2C: I2C Write\n");
	write_word(GPIO_दत्त_REG, (read_word(GPIO_दत्त_REG) & ~(I2C_SCL) ) );
	delay_loop(delay, delay);
	प्रारूप_लिख("\n\tI2C: I2C ReadNackForWrite sent\n");

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
शून्य SendAckForRead(अचिह्नित वर्ण delay)
{
	अचिह्नित दीर्घ read_दत्त = 0;
  समुच्चयः_Sda_Direction(GPIOD_IS_बहिर्गमनम्);

//	readData = read_word(GPIO_DATA_REG);

//	sda=0;
	write_word(GPIO_दत्त_REG, (read_word(GPIO_दत्त_REG) & ~(I2C_SDA)) );
	delay_loop(delay, delay);

//	scl=1;
	write_word(GPIO_दत्त_REG, (read_word(GPIO_दत्त_REG) | I2C_SCL) );
	delay_loop(delay, delay);

//	scl=0;
	write_word(GPIO_दत्त_REG, (read_word(GPIO_दत्त_REG) & ~(I2C_SCL) ) );
	delay_loop(delay, delay);

  समुच्चयः_Sda_Direction(GPIOD_IS_अन्तर्);
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
शून्य SendNackForRead(अचिह्नित वर्ण delay)
 {
  अचिह्नित दीर्घ read_दत्त = 0;
  समुच्चयः_Sda_Direction(GPIOD_IS_बहिर्गमनम्);

 //	readData = read_word(GPIO_DATA_REG);

 //	sda=0;
  write_word(GPIO_दत्त_REG, (read_word(GPIO_दत्त_REG)  | (I2C_SDA)) );
  delay_loop(delay, delay);

 //	scl=1;
  write_word(GPIO_दत्त_REG, (read_word(GPIO_दत्त_REG) | I2C_SCL) );
  delay_loop(delay, delay);

 //	scl=0;
  write_word(GPIO_दत्त_REG, (read_word(GPIO_दत्त_REG) & ~(I2C_SCL) ) );
  delay_loop(delay, delay);

  समुच्चयः_Sda_Direction(GPIOD_IS_अन्तर्);
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
  समुच्चयः_SCLAs_Output();
  समुच्चयः_Sda_Direction(GPIOD_IS_बहिर्गमनम्);
  प्रारूप_लिख("Initialization successfully done");
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
शून्य I2c_Send_Slave_स्थानाङ्कः(अचिह्नित वर्ण slave_स्थानाङ्कः, अचिह्नित वर्ण rdWrCntrl, अचिह्नित वर्ण delay)
{
  समुच्चयः_Sda_Direction(GPIOD_IS_बहिर्गमनम्);

  प्रारूप_लिख("\n\tI2C: I2C Start\n");
  start(delay);
  प्रारूप_लिख("\n\tI2C: I2C Send Bytes\n");
  यदि(rdWrCntrl) {
     प्रारूप_लिख("\n\tI2C: I2C Write\n");
    I2cWriteByte( (slave_स्थानाङ्कः | I2C_READ), delay);
	}
  अन्यथा {
     प्रारूप_लिख("\n\tI2C: I2C Write\n");
    I2cWriteByte( (slave_स्थानाङ्कः | I2C_WRITE), delay);
	}
  //	sda=1;
  write_word(GPIO_दत्त_REG, (read_word(GPIO_दत्त_REG) | I2C_SDA) );
  delay_loop(delay, delay);

  प्रारूप_लिख("\n\tI2C: I2C Write Ack\n");
  समुच्चयः_Sda_Direction(GPIOD_IS_अन्तर्);
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
शून्य I2c_Write_दत्त(अचिह्नित वर्ण write_दत्त, अचिह्नित वर्ण delay)
{
  समुच्चयः_Sda_Direction(GPIOD_IS_बहिर्गमनम्);
  प्रारूप_लिख("\n\tI2C: I2C Write\n");
  I2cWriteByte( write_दत्त, delay);
  //	sda=1;
  write_word(GPIO_दत्त_REG, (read_word(GPIO_दत्त_REG) | I2C_SDA) );
  delay_loop(delay, delay);

  प्रारूप_लिख("\n\tI2C: I2C Write Ack\n");
  समुच्चयः_Sda_Direction(GPIOD_IS_अन्तर्);
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
अचिह्नित वर्ण I2c_Read_दत्त_Ack(अचिह्नित वर्ण delay)
{
  अचिह्नित वर्ण read_दत्त = 0;
  समुच्चयः_Sda_Direction(GPIOD_IS_अन्तर्);
	प्रारूप_लिख("\n\tI2C: I2C Read\n");
	read_दत्त = I2cReadByte(delay);
	समुच्चयः_Sda_Direction(GPIOD_IS_बहिर्गमनम्);
	प्रारूप_लिख("\n\tI2C: I2C Read Ack\n");
	SendAckForRead(delay);
  प्रत्यागम read_दत्त;
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
अचिह्नित वर्ण I2c_Read_दत्त_Nack(अचिह्नित वर्ण delay)
{
  अचिह्नित वर्ण read_दत्त = 0;
  समुच्चयः_Sda_Direction(GPIOD_IS_अन्तर्);
 	प्रारूप_लिख("\n\tI2C: I2C Read\n");
  read_दत्त = I2cReadByte(delay);
	समुच्चयः_Sda_Direction(GPIOD_IS_बहिर्गमनम्);
  	प्रारूप_लिख("\n\tI2C: I2C Read NAck\n");
  	SendNackForRead(delay);
    प्रत्यागम read_दत्त;
}

/** @fn void I2cStart(unsigned char delay)
 * @brief Sending start condition for the I2C.
 * @details Start condition is making SDA low when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char delay
 */
शून्य I2cStart(अचिह्नित वर्ण delay)
{
  प्रारूप_लिख("\n\tI2C: I2C start\n");
  start(delay);
}

/** @fn void I2cStop(unsigned char delay)
 * @brief Sending stop condition for the I2C.
 * @details Stop condition is making SDA high when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char delay
 */
शून्य I2cStop(अचिह्नित वर्ण delay)
{
  प्रारूप_लिख("\n\tI2C: I2C stop\n");
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
शून्य I2c_Write_byte(अचिह्नित वर्ण slave_स्थानाङ्कः_2,अचिह्नित वर्ण reg_स्थानाङ्कः, अचिह्नित वर्ण दत्त_2, अचिह्नित वर्ण delay )
{
	I2c_Send_Slave_स्थानाङ्कः(slave_स्थानाङ्कः_2, I2C_WRITE, delay);
	I2c_Write_दत्त(reg_स्थानाङ्कः, delay);
	I2c_Write_दत्त(दत्त_2,delay);
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
पूर्णाङ्क I2c_Read_byte(अचिह्नित वर्ण slave_स्थानाङ्कः_2,अचिह्नित वर्ण reg_स्थानाङ्कः, अचिह्नित वर्ण delay)
{
	अचिह्नित वर्ण read_दत्त;
	I2c_Send_Slave_स्थानाङ्कः(slave_स्थानाङ्कः_2, I2C_WRITE, delay);//selecting slave to be read
	I2c_Write_दत्त(reg_स्थानाङ्कः, delay);//selecting register to be read
	I2c_Send_Slave_स्थानाङ्कः(slave_स्थानाङ्कः_2, I2C_READ, delay);
	read_दत्त = I2c_Read_दत्त_Ack(delay);
	I2cStop(delay);
	प्रत्यागम (पूर्णाङ्क) read_दत्त;
}

 /** @fn int I2c_shakti_readbytes(char *buf, int count, int last, unsigned char delay)
 * @brief To burst read (i.e read multiple bytes byte of data)
 * @details Reads "n" number of bytes from the slave device with the passed slave address 
 * @param buff Buffer pointer which holds n number of read values
 * @param count to tell how many bytes to read
 * @param last decides whether to stop operation or not
 * @return int (No. of values(bytes) read)
 */
पूर्णाङ्क I2c_shakti_readbytes(वर्ण *buf, पूर्णाङ्क गणनम्, पूर्णाङ्क चरमः, अचिह्नित वर्ण delay)
{
	प्रारूप_लिख("start reading the slave device\n");
	पूर्णाङ्क i = 0;
#यदि_परिभाषितम् PCF8584
	प्रति (i = 0; i <= गणनम्; i++) {
		यदि (i != 0 && i < गणनम्) {
			readbuf[i]=I2c_Read_दत्त_Ack(delay);
		}
		अन्यथा यदि(i==0) I2c_Read_दत्त_Ack(delay);//dummy read
		अन्यथा {
			readbuf[i] = I2c_Read_दत्त_Nack(delay);
		}
		/*The following loop is useful only  for eeprom*/
		यदि (चरमः)  I2cStop(delay);
		अन्यथा  I2cStart(delay);//sending repeated start
	}
	प्रत्यागम i-1; //excluding the dummy read
#अन्यथा
	प्रति (i = 0; i < गणनम्-1; i++)
		*(buf + i) = I2c_Read_दत्त_Ack(delay);
	*(buf + i) = I2c_Read_दत्त_Nack(delay);

	/*The following loop is useful only  for eeprom*/
	यदि (चरमः)
		I2cStop(delay);
	अन्यथा
		I2cStart(delay);//sending repeated start
#यदि_अन्तः
	प्रत्यागम i+1;
}
