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

#شامل "platform.h"
#شامل "gpio.h"
#شامل "gpio_i2c.h"

/** @fn extern void delay_loop(unsigned long , unsigned long)
 * @brief Maintains the required delay to perform an operation
 * @param unsigned long 
 * @param unsigned long
 */
خارجی خالی delay_loop(غیرعلامتی طویل , غیرعلامتی طویل);

/** @fn static void SetSCLAsOutput()
 * @brief Function for configure GPIO 0 as SCL output.
 * @details This function will be called to make the scl line (defined by I2C_SCL)
 *             macro as output.
 * @warning This bit value can be changed as per I2C_SCL macro.
 */
ساکن خالی سیٹ_SCLAs_Output()
{
	غیرعلامتی طویل read_ڈیٹا = 0;
	read_ڈیٹا = read_لفظ(GPIO_DIRECTION_CNTRL_REG);
	write_لفظ(GPIO_DIRECTION_CNTRL_REG, (read_ڈیٹا | I2C_SCL) );
	لکھو("SCL set as output\n");
}

/** @fn static void SetSdaDirection(int inOutCntrl)
 *  @brief Function for configure GPIO 0 as SCL output.
 * @details This function will be called to make the scl line (defined by I2C_SCL)
 *           macro as output.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param int inOutCntrl
 */
ساکن خالی سیٹ_Sda_Direction(صحیح اندر_برآمد_Cntrl)
{
	غیرعلامتی طویل read_ڈیٹا = 0;
	read_ڈیٹا = read_لفظ(GPIO_DIRECTION_CNTRL_REG);

	اگر (اندر_برآمد_Cntrl) { // output
		write_لفظ(GPIO_DIRECTION_CNTRL_REG, (read_ڈیٹا | I2C_SDA) );
		لکھو("\n\tSDA set as output\n");
	}
    ورنہ {
		write_لفظ(GPIO_DIRECTION_CNTRL_REG, (read_ڈیٹا & ~(I2C_SDA) ) );
		لکھو("\n\tSDA set as input\n");
	}
}

/** @fn static void start(unsigned char delay)
 * @brief Sending start condition for the I2C.
 * @details Start condition is making SDA low when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char delay
 */
ساکن خالی آغاز(غیرعلامتی حرف delay)
{
	غیرعلامتی طویل read_ڈیٹا = 0;
	read_ڈیٹا = read_لفظ(GPIO_ڈیٹا_REG);

//	sda=1;
	write_لفظ(GPIO_ڈیٹا_REG, (read_لفظ(GPIO_ڈیٹا_REG) | I2C_SDA | I2C_SCL) );
	delay_loop(delay, delay);

//		scl=1;
	write_لفظ(GPIO_ڈیٹا_REG, (read_لفظ(GPIO_ڈیٹا_REG) | I2C_SCL) );
	delay_loop(delay, delay);

//		sda=0;
	write_لفظ(GPIO_ڈیٹا_REG, (read_لفظ(GPIO_ڈیٹا_REG) & ~(I2C_SDA)) );
	delay_loop(delay, delay);

//		scl=0;
	write_لفظ(GPIO_ڈیٹا_REG, (read_لفظ(GPIO_ڈیٹا_REG) & ~(I2C_SCL) ) );
	delay_loop(delay, delay);

	لکھو("\n\tI2C: I2C Start condition sent\n");
}

/** @fn static void stop(unsigned char delay)
 * @brief Sending stop condition for the I2C.
 * @details Stop condition is making SDA high when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char
 */
ساکن خالی stop(غیرعلامتی حرف delay)
{
	غیرعلامتی طویل read_ڈیٹا = 0;
	read_ڈیٹا = read_لفظ(GPIO_ڈیٹا_REG);
//	sda=0;
	write_لفظ(GPIO_ڈیٹا_REG, (read_لفظ(GPIO_ڈیٹا_REG) & ~(I2C_SDA)) );
	delay_loop(delay, delay);

//	scl=1;
	write_لفظ(GPIO_ڈیٹا_REG, (read_لفظ(GPIO_ڈیٹا_REG) | I2C_SCL) );
	delay_loop(delay, delay);

//	sda=1;
	write_لفظ(GPIO_ڈیٹا_REG, (read_لفظ(GPIO_ڈیٹا_REG) | I2C_SDA) );
	delay_loop(delay, delay);
	لکھو("\n\tI2C: I2C Start condition sent\n");

}

/** @fn void I2cWriteByte(unsigned char writeData, unsigned char delay)
 * @brief Writes a byte to the I2C device.
 * @details Data is put on the SDA Line bit by bit and then makes the
 *  SCL from low to high to write..
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param writeData --> Value that needs to be written.
 * @param unsigned char delay
 */
خالی I2cWriteByte(غیرعلامتی حرف write_ڈیٹا, غیرعلامتی حرف delay)
{
	غیرعلامتی حرف j = 0,k;
	غیرعلامتی طویل read_ڈیٹا = 0;
	read_ڈیٹا = read_لفظ(GPIO_ڈیٹا_REG);
	جب (j < 8)
	{
		k = write_ڈیٹا;
		k = ( k << j ) & 0x80;
//		printf("\n\r i: %d; j: %d; k: %d", i, j, k);
//		sda=CY;
		اگر (k == 0) {
			write_لفظ(GPIO_ڈیٹا_REG, (read_لفظ(GPIO_ڈیٹا_REG) & ~(I2C_SDA)) );
			delay_loop(delay, delay);
		}
		ورنہ {
			write_لفظ(GPIO_ڈیٹا_REG, (read_لفظ(GPIO_ڈیٹا_REG) | I2C_SDA) );
			delay_loop(delay, delay);
		}

	//	scl=1;
		write_لفظ(GPIO_ڈیٹا_REG, (read_لفظ(GPIO_ڈیٹا_REG) | I2C_SCL) );
		delay_loop(delay, delay);

	//	scl=0;
		write_لفظ(GPIO_ڈیٹا_REG, (read_لفظ(GPIO_ڈیٹا_REG) & ~(I2C_SCL) ) );
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
غیرعلامتی حرف I2cReadByte(غیرعلامتی حرف delay)
{
	غیرعلامتی حرف j = 0, i = 0;
	غیرعلامتی حرف ثنائی_ہندسہ_قدر;
	غیرعلامتی حرف read_ڈیٹا = 0;
  غیرعلامتی طویل read_Gpio_ڈیٹا = 0;
	read_ڈیٹا = read_لفظ(GPIO_ڈیٹا_REG);

//	sda=1;
//Make SDA high
	جب (j < 8) {
	//	scl=1;
		write_لفظ(GPIO_ڈیٹا_REG, (read_لفظ(GPIO_ڈیٹا_REG) | I2C_SCL) );
		delay_loop(delay, delay);

//		d1 = sda;
		read_Gpio_ڈیٹا = read_لفظ(GPIO_ڈیٹا_REG)  & I2C_SDA;
		اگر (read_Gpio_ڈیٹا != 0)
			ثنائی_ہندسہ_قدر = 1;
		ورنہ
			ثنائی_ہندسہ_قدر = 0;
	    read_ڈیٹا = read_ڈیٹا << 1;
		read_ڈیٹا = read_ڈیٹا | ثنائی_ہندسہ_قدر;
		delay_loop(delay, delay);

	//	scl=0;
		write_لفظ(GPIO_ڈیٹا_REG, (read_لفظ(GPIO_ڈیٹا_REG) & ~(I2C_SCL) ) );
		delay_loop(delay, delay);

		++j;
	}

	واپس read_ڈیٹا;
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
خالی ReadAckForWrite(غیرعلامتی حرف delay)
{
	غیرعلامتی طویل read_ڈیٹا = 0;
	لکھو("\n\tI2C: I2C Read\n");
	read_ڈیٹا = read_لفظ(GPIO_ڈیٹا_REG);
	delay_loop(delay, delay);
//	scl=1;delay
	لکھو("\n\tI2C: I2C Write\n");
	write_لفظ(GPIO_ڈیٹا_REG, (read_ڈیٹا | I2C_SCL) );
	delay_loop(delay, delay);

		لکھو("\n\tI2C: I2C Write\n");
		read_ڈیٹا = read_لفظ(GPIO_ڈیٹا_REG)  & I2C_SDA;

//	scl=0;
	لکھو("\n\tI2C: I2C Write\n");
	write_لفظ(GPIO_ڈیٹا_REG, (read_لفظ(GPIO_ڈیٹا_REG) & ~(I2C_SCL) ) );
	delay_loop(delay, delay);
	لکھو("\n\tI2C: I2C ReadNackForWrite sent\n");

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
خالی SendAckForRead(غیرعلامتی حرف delay)
{
	غیرعلامتی طویل read_ڈیٹا = 0;
  سیٹ_Sda_Direction(GPIOD_IS_برآمد);

//	readData = read_word(GPIO_DATA_REG);

//	sda=0;
	write_لفظ(GPIO_ڈیٹا_REG, (read_لفظ(GPIO_ڈیٹا_REG) & ~(I2C_SDA)) );
	delay_loop(delay, delay);

//	scl=1;
	write_لفظ(GPIO_ڈیٹا_REG, (read_لفظ(GPIO_ڈیٹا_REG) | I2C_SCL) );
	delay_loop(delay, delay);

//	scl=0;
	write_لفظ(GPIO_ڈیٹا_REG, (read_لفظ(GPIO_ڈیٹا_REG) & ~(I2C_SCL) ) );
	delay_loop(delay, delay);

  سیٹ_Sda_Direction(GPIOD_IS_اندر);
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
خالی SendNackForRead(غیرعلامتی حرف delay)
 {
  غیرعلامتی طویل read_ڈیٹا = 0;
  سیٹ_Sda_Direction(GPIOD_IS_برآمد);

 //	readData = read_word(GPIO_DATA_REG);

 //	sda=0;
  write_لفظ(GPIO_ڈیٹا_REG, (read_لفظ(GPIO_ڈیٹا_REG)  | (I2C_SDA)) );
  delay_loop(delay, delay);

 //	scl=1;
  write_لفظ(GPIO_ڈیٹا_REG, (read_لفظ(GPIO_ڈیٹا_REG) | I2C_SCL) );
  delay_loop(delay, delay);

 //	scl=0;
  write_لفظ(GPIO_ڈیٹا_REG, (read_لفظ(GPIO_ڈیٹا_REG) & ~(I2C_SCL) ) );
  delay_loop(delay, delay);

  سیٹ_Sda_Direction(GPIOD_IS_اندر);
 }

/** @fn void I2cInit()
 * @brief Configuring the SDA and SCL as OUTPUTS so that Start, Slave address
 *     ,and register address or register value that needs to be writen.
 * @details I2C master Inits makes the master ready for either read or write
 *      operation.
 * @warning This bit value can be changed as per I2C_SCL macro.
 */
خالی I2cInit()
{
  سیٹ_SCLAs_Output();
  سیٹ_Sda_Direction(GPIOD_IS_برآمد);
  لکھو("Initialization successfully done");
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
خالی I2c_Send_Slave_پتہ(غیرعلامتی حرف slave_پتہ, غیرعلامتی حرف rdWrCntrl, غیرعلامتی حرف delay)
{
  سیٹ_Sda_Direction(GPIOD_IS_برآمد);

  لکھو("\n\tI2C: I2C Start\n");
  آغاز(delay);
  لکھو("\n\tI2C: I2C Send Bytes\n");
  اگر(rdWrCntrl) {
     لکھو("\n\tI2C: I2C Write\n");
    I2cWriteByte( (slave_پتہ | I2C_READ), delay);
	}
  ورنہ {
     لکھو("\n\tI2C: I2C Write\n");
    I2cWriteByte( (slave_پتہ | I2C_WRITE), delay);
	}
  //	sda=1;
  write_لفظ(GPIO_ڈیٹا_REG, (read_لفظ(GPIO_ڈیٹا_REG) | I2C_SDA) );
  delay_loop(delay, delay);

  لکھو("\n\tI2C: I2C Write Ack\n");
  سیٹ_Sda_Direction(GPIOD_IS_اندر);
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
خالی I2c_Write_ڈیٹا(غیرعلامتی حرف write_ڈیٹا, غیرعلامتی حرف delay)
{
  سیٹ_Sda_Direction(GPIOD_IS_برآمد);
  لکھو("\n\tI2C: I2C Write\n");
  I2cWriteByte( write_ڈیٹا, delay);
  //	sda=1;
  write_لفظ(GPIO_ڈیٹا_REG, (read_لفظ(GPIO_ڈیٹا_REG) | I2C_SDA) );
  delay_loop(delay, delay);

  لکھو("\n\tI2C: I2C Write Ack\n");
  سیٹ_Sda_Direction(GPIOD_IS_اندر);
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
غیرعلامتی حرف I2c_Read_ڈیٹا_Ack(غیرعلامتی حرف delay)
{
  غیرعلامتی حرف read_ڈیٹا = 0;
  سیٹ_Sda_Direction(GPIOD_IS_اندر);
	لکھو("\n\tI2C: I2C Read\n");
	read_ڈیٹا = I2cReadByte(delay);
	سیٹ_Sda_Direction(GPIOD_IS_برآمد);
	لکھو("\n\tI2C: I2C Read Ack\n");
	SendAckForRead(delay);
  واپس read_ڈیٹا;
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
غیرعلامتی حرف I2c_Read_ڈیٹا_Nack(غیرعلامتی حرف delay)
{
  غیرعلامتی حرف read_ڈیٹا = 0;
  سیٹ_Sda_Direction(GPIOD_IS_اندر);
 	لکھو("\n\tI2C: I2C Read\n");
  read_ڈیٹا = I2cReadByte(delay);
	سیٹ_Sda_Direction(GPIOD_IS_برآمد);
  	لکھو("\n\tI2C: I2C Read NAck\n");
  	SendNackForRead(delay);
    واپس read_ڈیٹا;
}

/** @fn void I2cStart(unsigned char delay)
 * @brief Sending start condition for the I2C.
 * @details Start condition is making SDA low when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char delay
 */
خالی I2c_آغاز(غیرعلامتی حرف delay)
{
  لکھو("\n\tI2C: I2C start\n");
  آغاز(delay);
}

/** @fn void I2cStop(unsigned char delay)
 * @brief Sending stop condition for the I2C.
 * @details Stop condition is making SDA high when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char delay
 */
خالی I2cStop(غیرعلامتی حرف delay)
{
  لکھو("\n\tI2C: I2C stop\n");
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
خالی I2c_Write_byte(غیرعلامتی حرف slave_پتہ_2,غیرعلامتی حرف reg_پتہ, غیرعلامتی حرف ڈیٹا_2, غیرعلامتی حرف delay )
{
	I2c_Send_Slave_پتہ(slave_پتہ_2, I2C_WRITE, delay);
	I2c_Write_ڈیٹا(reg_پتہ, delay);
	I2c_Write_ڈیٹا(ڈیٹا_2,delay);
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
صحیح I2c_Read_byte(غیرعلامتی حرف slave_پتہ_2,غیرعلامتی حرف reg_پتہ, غیرعلامتی حرف delay)
{
	غیرعلامتی حرف read_ڈیٹا;
	I2c_Send_Slave_پتہ(slave_پتہ_2, I2C_WRITE, delay);//selecting slave to be read
	I2c_Write_ڈیٹا(reg_پتہ, delay);//selecting register to be read
	I2c_Send_Slave_پتہ(slave_پتہ_2, I2C_READ, delay);
	read_ڈیٹا = I2c_Read_ڈیٹا_Ack(delay);
	I2cStop(delay);
	واپس (صحیح) read_ڈیٹا;
}

 /** @fn int I2c_shakti_readbytes(char *buf, int count, int last, unsigned char delay)
 * @brief To burst read (i.e read multiple bytes byte of data)
 * @details Reads "n" number of bytes from the slave device with the passed slave address 
 * @param buff Buffer pointer which holds n number of read values
 * @param count to tell how many bytes to read
 * @param last decides whether to stop operation or not
 * @return int (No. of values(bytes) read)
 */
صحیح I2c_shakti_readbytes(حرف *buf, صحیح گنتی, صحیح آخری, غیرعلامتی حرف delay)
{
	لکھو("start reading the slave device\n");
	صحیح i = 0;
#اگر_تعریف_شدہ PCF8584
	برائے (i = 0; i <= گنتی; i++) {
		اگر (i != 0 && i < گنتی) {
			readbuf[i]=I2c_Read_ڈیٹا_Ack(delay);
		}
		ورنہ اگر(i==0) I2c_Read_ڈیٹا_Ack(delay);//dummy read
		ورنہ {
			readbuf[i] = I2c_Read_ڈیٹا_Nack(delay);
		}
		/*The following loop is useful only  for eeprom*/
		اگر (آخری)  I2cStop(delay);
		ورنہ  I2c_آغاز(delay);//sending repeated start
	}
	واپس i-1; //excluding the dummy read
#ورنہ
	برائے (i = 0; i < گنتی-1; i++)
		*(buf + i) = I2c_Read_ڈیٹا_Ack(delay);
	*(buf + i) = I2c_Read_ڈیٹا_Nack(delay);

	/*The following loop is useful only  for eeprom*/
	اگر (آخری)
		I2cStop(delay);
	ورنہ
		I2c_آغاز(delay);//sending repeated start
#اگر_ختم
	واپس i+1;
}
