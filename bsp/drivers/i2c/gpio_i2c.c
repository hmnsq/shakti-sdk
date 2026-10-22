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

#ضمن "platform.h"
#ضمن "gpio.h"
#ضمن "gpio_i2c.h"

/** @fn extern void delay_loop(unsigned long , unsigned long)
 * @brief Maintains the required delay to perform an operation
 * @param unsigned long 
 * @param unsigned long
 */
خارجي فراغ delay_loop(بینښه اوږد , بینښه اوږد);

/** @fn static void SetSCLAsOutput()
 * @brief Function for configure GPIO 0 as SCL output.
 * @details This function will be called to make the scl line (defined by I2C_SCL)
 *             macro as output.
 * @warning This bit value can be changed as per I2C_SCL macro.
 */
ساكن فراغ سېټ_SCLAs_Output()
{
	بینښه اوږد read_معلومات = 0;
	read_معلومات = read_کلمه(GPIO_DIRECTION_CNTRL_REG);
	write_کلمه(GPIO_DIRECTION_CNTRL_REG, (read_معلومات | I2C_SCL) );
	چاپ_کړه("SCL set as output\n");
}

/** @fn static void SetSdaDirection(int inOutCntrl)
 *  @brief Function for configure GPIO 0 as SCL output.
 * @details This function will be called to make the scl line (defined by I2C_SCL)
 *           macro as output.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param int inOutCntrl
 */
ساكن فراغ سېټ_Sda_Direction(صحيح دننه_بهر_Cntrl)
{
	بینښه اوږد read_معلومات = 0;
	read_معلومات = read_کلمه(GPIO_DIRECTION_CNTRL_REG);

	إذا (دننه_بهر_Cntrl) { // output
		write_کلمه(GPIO_DIRECTION_CNTRL_REG, (read_معلومات | I2C_SDA) );
		چاپ_کړه("\n\tSDA set as output\n");
	}
    وإلا {
		write_کلمه(GPIO_DIRECTION_CNTRL_REG, (read_معلومات & ~(I2C_SDA) ) );
		چاپ_کړه("\n\tSDA set as input\n");
	}
}

/** @fn static void start(unsigned char delay)
 * @brief Sending start condition for the I2C.
 * @details Start condition is making SDA low when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char delay
 */
ساكن فراغ پیل(بینښه حرف delay)
{
	بینښه اوږد read_معلومات = 0;
	read_معلومات = read_کلمه(GPIO_معلومات_REG);

//	sda=1;
	write_کلمه(GPIO_معلومات_REG, (read_کلمه(GPIO_معلومات_REG) | I2C_SDA | I2C_SCL) );
	delay_loop(delay, delay);

//		scl=1;
	write_کلمه(GPIO_معلومات_REG, (read_کلمه(GPIO_معلومات_REG) | I2C_SCL) );
	delay_loop(delay, delay);

//		sda=0;
	write_کلمه(GPIO_معلومات_REG, (read_کلمه(GPIO_معلومات_REG) & ~(I2C_SDA)) );
	delay_loop(delay, delay);

//		scl=0;
	write_کلمه(GPIO_معلومات_REG, (read_کلمه(GPIO_معلومات_REG) & ~(I2C_SCL) ) );
	delay_loop(delay, delay);

	چاپ_کړه("\n\tI2C: I2C Start condition sent\n");
}

/** @fn static void stop(unsigned char delay)
 * @brief Sending stop condition for the I2C.
 * @details Stop condition is making SDA high when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char
 */
ساكن فراغ stop(بینښه حرف delay)
{
	بینښه اوږد read_معلومات = 0;
	read_معلومات = read_کلمه(GPIO_معلومات_REG);
//	sda=0;
	write_کلمه(GPIO_معلومات_REG, (read_کلمه(GPIO_معلومات_REG) & ~(I2C_SDA)) );
	delay_loop(delay, delay);

//	scl=1;
	write_کلمه(GPIO_معلومات_REG, (read_کلمه(GPIO_معلومات_REG) | I2C_SCL) );
	delay_loop(delay, delay);

//	sda=1;
	write_کلمه(GPIO_معلومات_REG, (read_کلمه(GPIO_معلومات_REG) | I2C_SDA) );
	delay_loop(delay, delay);
	چاپ_کړه("\n\tI2C: I2C Start condition sent\n");

}

/** @fn void I2cWriteByte(unsigned char writeData, unsigned char delay)
 * @brief Writes a byte to the I2C device.
 * @details Data is put on the SDA Line bit by bit and then makes the
 *  SCL from low to high to write..
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param writeData --> Value that needs to be written.
 * @param unsigned char delay
 */
فراغ I2cWriteByte(بینښه حرف write_معلومات, بینښه حرف delay)
{
	بینښه حرف j = 0,k;
	بینښه اوږد read_معلومات = 0;
	read_معلومات = read_کلمه(GPIO_معلومات_REG);
	طالما (j < 8)
	{
		k = write_معلومات;
		k = ( k << j ) & 0x80;
//		printf("\n\r i: %d; j: %d; k: %d", i, j, k);
//		sda=CY;
		إذا (k == 0) {
			write_کلمه(GPIO_معلومات_REG, (read_کلمه(GPIO_معلومات_REG) & ~(I2C_SDA)) );
			delay_loop(delay, delay);
		}
		وإلا {
			write_کلمه(GPIO_معلومات_REG, (read_کلمه(GPIO_معلومات_REG) | I2C_SDA) );
			delay_loop(delay, delay);
		}

	//	scl=1;
		write_کلمه(GPIO_معلومات_REG, (read_کلمه(GPIO_معلومات_REG) | I2C_SCL) );
		delay_loop(delay, delay);

	//	scl=0;
		write_کلمه(GPIO_معلومات_REG, (read_کلمه(GPIO_معلومات_REG) & ~(I2C_SCL) ) );
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
بینښه حرف I2cReadByte(بینښه حرف delay)
{
	بینښه حرف j = 0, i = 0;
	بینښه حرف بټ_ارزښت;
	بینښه حرف read_معلومات = 0;
  بینښه اوږد read_Gpio_معلومات = 0;
	read_معلومات = read_کلمه(GPIO_معلومات_REG);

//	sda=1;
//Make SDA high
	طالما (j < 8) {
	//	scl=1;
		write_کلمه(GPIO_معلومات_REG, (read_کلمه(GPIO_معلومات_REG) | I2C_SCL) );
		delay_loop(delay, delay);

//		d1 = sda;
		read_Gpio_معلومات = read_کلمه(GPIO_معلومات_REG)  & I2C_SDA;
		إذا (read_Gpio_معلومات != 0)
			بټ_ارزښت = 1;
		وإلا
			بټ_ارزښت = 0;
	    read_معلومات = read_معلومات << 1;
		read_معلومات = read_معلومات | بټ_ارزښت;
		delay_loop(delay, delay);

	//	scl=0;
		write_کلمه(GPIO_معلومات_REG, (read_کلمه(GPIO_معلومات_REG) & ~(I2C_SCL) ) );
		delay_loop(delay, delay);

		++j;
	}

	أرجع read_معلومات;
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
فراغ ReadAckForWrite(بینښه حرف delay)
{
	بینښه اوږد read_معلومات = 0;
	چاپ_کړه("\n\tI2C: I2C Read\n");
	read_معلومات = read_کلمه(GPIO_معلومات_REG);
	delay_loop(delay, delay);
//	scl=1;delay
	چاپ_کړه("\n\tI2C: I2C Write\n");
	write_کلمه(GPIO_معلومات_REG, (read_معلومات | I2C_SCL) );
	delay_loop(delay, delay);

		چاپ_کړه("\n\tI2C: I2C Write\n");
		read_معلومات = read_کلمه(GPIO_معلومات_REG)  & I2C_SDA;

//	scl=0;
	چاپ_کړه("\n\tI2C: I2C Write\n");
	write_کلمه(GPIO_معلومات_REG, (read_کلمه(GPIO_معلومات_REG) & ~(I2C_SCL) ) );
	delay_loop(delay, delay);
	چاپ_کړه("\n\tI2C: I2C ReadNackForWrite sent\n");

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
فراغ SendAckForRead(بینښه حرف delay)
{
	بینښه اوږد read_معلومات = 0;
  سېټ_Sda_Direction(GPIOD_IS_بهر);

//	readData = read_word(GPIO_DATA_REG);

//	sda=0;
	write_کلمه(GPIO_معلومات_REG, (read_کلمه(GPIO_معلومات_REG) & ~(I2C_SDA)) );
	delay_loop(delay, delay);

//	scl=1;
	write_کلمه(GPIO_معلومات_REG, (read_کلمه(GPIO_معلومات_REG) | I2C_SCL) );
	delay_loop(delay, delay);

//	scl=0;
	write_کلمه(GPIO_معلومات_REG, (read_کلمه(GPIO_معلومات_REG) & ~(I2C_SCL) ) );
	delay_loop(delay, delay);

  سېټ_Sda_Direction(GPIOD_IS_دننه);
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
فراغ SendNackForRead(بینښه حرف delay)
 {
  بینښه اوږد read_معلومات = 0;
  سېټ_Sda_Direction(GPIOD_IS_بهر);

 //	readData = read_word(GPIO_DATA_REG);

 //	sda=0;
  write_کلمه(GPIO_معلومات_REG, (read_کلمه(GPIO_معلومات_REG)  | (I2C_SDA)) );
  delay_loop(delay, delay);

 //	scl=1;
  write_کلمه(GPIO_معلومات_REG, (read_کلمه(GPIO_معلومات_REG) | I2C_SCL) );
  delay_loop(delay, delay);

 //	scl=0;
  write_کلمه(GPIO_معلومات_REG, (read_کلمه(GPIO_معلومات_REG) & ~(I2C_SCL) ) );
  delay_loop(delay, delay);

  سېټ_Sda_Direction(GPIOD_IS_دننه);
 }

/** @fn void I2cInit()
 * @brief Configuring the SDA and SCL as OUTPUTS so that Start, Slave address
 *     ,and register address or register value that needs to be writen.
 * @details I2C master Inits makes the master ready for either read or write
 *      operation.
 * @warning This bit value can be changed as per I2C_SCL macro.
 */
فراغ I2cInit()
{
  سېټ_SCLAs_Output();
  سېټ_Sda_Direction(GPIOD_IS_بهر);
  چاپ_کړه("Initialization successfully done");
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
فراغ I2c_Send_Slave_پته(بینښه حرف slave_پته, بینښه حرف rdWrCntrl, بینښه حرف delay)
{
  سېټ_Sda_Direction(GPIOD_IS_بهر);

  چاپ_کړه("\n\tI2C: I2C Start\n");
  پیل(delay);
  چاپ_کړه("\n\tI2C: I2C Send Bytes\n");
  إذا(rdWrCntrl) {
     چاپ_کړه("\n\tI2C: I2C Write\n");
    I2cWriteByte( (slave_پته | I2C_READ), delay);
	}
  وإلا {
     چاپ_کړه("\n\tI2C: I2C Write\n");
    I2cWriteByte( (slave_پته | I2C_WRITE), delay);
	}
  //	sda=1;
  write_کلمه(GPIO_معلومات_REG, (read_کلمه(GPIO_معلومات_REG) | I2C_SDA) );
  delay_loop(delay, delay);

  چاپ_کړه("\n\tI2C: I2C Write Ack\n");
  سېټ_Sda_Direction(GPIOD_IS_دننه);
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
فراغ I2c_Write_معلومات(بینښه حرف write_معلومات, بینښه حرف delay)
{
  سېټ_Sda_Direction(GPIOD_IS_بهر);
  چاپ_کړه("\n\tI2C: I2C Write\n");
  I2cWriteByte( write_معلومات, delay);
  //	sda=1;
  write_کلمه(GPIO_معلومات_REG, (read_کلمه(GPIO_معلومات_REG) | I2C_SDA) );
  delay_loop(delay, delay);

  چاپ_کړه("\n\tI2C: I2C Write Ack\n");
  سېټ_Sda_Direction(GPIOD_IS_دننه);
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
بینښه حرف I2c_Read_معلومات_Ack(بینښه حرف delay)
{
  بینښه حرف read_معلومات = 0;
  سېټ_Sda_Direction(GPIOD_IS_دننه);
	چاپ_کړه("\n\tI2C: I2C Read\n");
	read_معلومات = I2cReadByte(delay);
	سېټ_Sda_Direction(GPIOD_IS_بهر);
	چاپ_کړه("\n\tI2C: I2C Read Ack\n");
	SendAckForRead(delay);
  أرجع read_معلومات;
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
بینښه حرف I2c_Read_معلومات_Nack(بینښه حرف delay)
{
  بینښه حرف read_معلومات = 0;
  سېټ_Sda_Direction(GPIOD_IS_دننه);
 	چاپ_کړه("\n\tI2C: I2C Read\n");
  read_معلومات = I2cReadByte(delay);
	سېټ_Sda_Direction(GPIOD_IS_بهر);
  	چاپ_کړه("\n\tI2C: I2C Read NAck\n");
  	SendNackForRead(delay);
    أرجع read_معلومات;
}

/** @fn void I2cStart(unsigned char delay)
 * @brief Sending start condition for the I2C.
 * @details Start condition is making SDA low when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char delay
 */
فراغ I2c_پیل(بینښه حرف delay)
{
  چاپ_کړه("\n\tI2C: I2C start\n");
  پیل(delay);
}

/** @fn void I2cStop(unsigned char delay)
 * @brief Sending stop condition for the I2C.
 * @details Stop condition is making SDA high when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char delay
 */
فراغ I2cStop(بینښه حرف delay)
{
  چاپ_کړه("\n\tI2C: I2C stop\n");
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
فراغ I2c_Write_byte(بینښه حرف slave_پته_2,بینښه حرف reg_پته, بینښه حرف معلومات_2, بینښه حرف delay )
{
	I2c_Send_Slave_پته(slave_پته_2, I2C_WRITE, delay);
	I2c_Write_معلومات(reg_پته, delay);
	I2c_Write_معلومات(معلومات_2,delay);
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
صحيح I2c_Read_byte(بینښه حرف slave_پته_2,بینښه حرف reg_پته, بینښه حرف delay)
{
	بینښه حرف read_معلومات;
	I2c_Send_Slave_پته(slave_پته_2, I2C_WRITE, delay);//selecting slave to be read
	I2c_Write_معلومات(reg_پته, delay);//selecting register to be read
	I2c_Send_Slave_پته(slave_پته_2, I2C_READ, delay);
	read_معلومات = I2c_Read_معلومات_Ack(delay);
	I2cStop(delay);
	أرجع (صحيح) read_معلومات;
}

 /** @fn int I2c_shakti_readbytes(char *buf, int count, int last, unsigned char delay)
 * @brief To burst read (i.e read multiple bytes byte of data)
 * @details Reads "n" number of bytes from the slave device with the passed slave address 
 * @param buff Buffer pointer which holds n number of read values
 * @param count to tell how many bytes to read
 * @param last decides whether to stop operation or not
 * @return int (No. of values(bytes) read)
 */
صحيح I2c_shakti_readbytes(حرف *buf, صحيح شمېر, صحيح وروستی, بینښه حرف delay)
{
	چاپ_کړه("start reading the slave device\n");
	صحيح i = 0;
#که_تعریف_شوی PCF8584
	لكل (i = 0; i <= شمېر; i++) {
		إذا (i != 0 && i < شمېر) {
			readbuf[i]=I2c_Read_معلومات_Ack(delay);
		}
		وإلا إذا(i==0) I2c_Read_معلومات_Ack(delay);//dummy read
		وإلا {
			readbuf[i] = I2c_Read_معلومات_Nack(delay);
		}
		/*The following loop is useful only  for eeprom*/
		إذا (وروستی)  I2cStop(delay);
		وإلا  I2c_پیل(delay);//sending repeated start
	}
	أرجع i-1; //excluding the dummy read
#وإلا
	لكل (i = 0; i < شمېر-1; i++)
		*(buf + i) = I2c_Read_معلومات_Ack(delay);
	*(buf + i) = I2c_Read_معلومات_Nack(delay);

	/*The following loop is useful only  for eeprom*/
	إذا (وروستی)
		I2cStop(delay);
	وإلا
		I2c_پیل(delay);//sending repeated start
#د_که_پای
	أرجع i+1;
}
