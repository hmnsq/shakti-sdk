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

#ਅਨ੍ਤਰ੍ਭਾਵ "platform.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gpio.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gpio_i2c.h"

/** @fn extern void delay_loop(unsigned long , unsigned long)
 * @brief Maintains the required delay to perform an operation
 * @param unsigned long 
 * @param unsigned long
 */
ਬਾਹਰੀ ਖਾਲੀ delay_loop(ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ , ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ);

/** @fn static void SetSCLAsOutput()
 * @brief Function for configure GPIO 0 as SCL output.
 * @details This function will be called to make the scl line (defined by I2C_SCL)
 *             macro as output.
 * @warning This bit value can be changed as per I2C_SCL macro.
 */
ਸਥਿਰ ਖਾਲੀ ਸੈੱਟ_SCLAs_Output()
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ read_ਅੰਕੜੇ = 0;
	read_ਅੰਕੜੇ = read_ਸ਼ਬਦ(GPIO_DIRECTION_CNTRL_REG);
	write_ਸ਼ਬਦ(GPIO_DIRECTION_CNTRL_REG, (read_ਅੰਕੜੇ | I2C_SCL) );
	ਲਿਖੋ("SCL set as output\n");
}

/** @fn static void SetSdaDirection(int inOutCntrl)
 *  @brief Function for configure GPIO 0 as SCL output.
 * @details This function will be called to make the scl line (defined by I2C_SCL)
 *           macro as output.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param int inOutCntrl
 */
ਸਥਿਰ ਖਾਲੀ ਸੈੱਟ_Sda_Direction(ਪੂਰਨ ਵਿੱਚ_ਬਾਹਰਲਾ_Cntrl)
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ read_ਅੰਕੜੇ = 0;
	read_ਅੰਕੜੇ = read_ਸ਼ਬਦ(GPIO_DIRECTION_CNTRL_REG);

	ਜੇ (ਵਿੱਚ_ਬਾਹਰਲਾ_Cntrl) { // output
		write_ਸ਼ਬਦ(GPIO_DIRECTION_CNTRL_REG, (read_ਅੰਕੜੇ | I2C_SDA) );
		ਲਿਖੋ("\n\tSDA set as output\n");
	}
    ਨਹੀਂਤਾਂ {
		write_ਸ਼ਬਦ(GPIO_DIRECTION_CNTRL_REG, (read_ਅੰਕੜੇ & ~(I2C_SDA) ) );
		ਲਿਖੋ("\n\tSDA set as input\n");
	}
}

/** @fn static void start(unsigned char delay)
 * @brief Sending start condition for the I2C.
 * @details Start condition is making SDA low when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char delay
 */
ਸਥਿਰ ਖਾਲੀ ਸ਼ੁਰੂ(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ delay)
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ read_ਅੰਕੜੇ = 0;
	read_ਅੰਕੜੇ = read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG);

//	sda=1;
	write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) | I2C_SDA | I2C_SCL) );
	delay_loop(delay, delay);

//		scl=1;
	write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) | I2C_SCL) );
	delay_loop(delay, delay);

//		sda=0;
	write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) & ~(I2C_SDA)) );
	delay_loop(delay, delay);

//		scl=0;
	write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) & ~(I2C_SCL) ) );
	delay_loop(delay, delay);

	ਲਿਖੋ("\n\tI2C: I2C Start condition sent\n");
}

/** @fn static void stop(unsigned char delay)
 * @brief Sending stop condition for the I2C.
 * @details Stop condition is making SDA high when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char
 */
ਸਥਿਰ ਖਾਲੀ stop(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ delay)
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ read_ਅੰਕੜੇ = 0;
	read_ਅੰਕੜੇ = read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG);
//	sda=0;
	write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) & ~(I2C_SDA)) );
	delay_loop(delay, delay);

//	scl=1;
	write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) | I2C_SCL) );
	delay_loop(delay, delay);

//	sda=1;
	write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) | I2C_SDA) );
	delay_loop(delay, delay);
	ਲਿਖੋ("\n\tI2C: I2C Start condition sent\n");

}

/** @fn void I2cWriteByte(unsigned char writeData, unsigned char delay)
 * @brief Writes a byte to the I2C device.
 * @details Data is put on the SDA Line bit by bit and then makes the
 *  SCL from low to high to write..
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param writeData --> Value that needs to be written.
 * @param unsigned char delay
 */
ਖਾਲੀ I2cWriteByte(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ write_ਅੰਕੜੇ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ delay)
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ j = 0,k;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ read_ਅੰਕੜੇ = 0;
	read_ਅੰਕੜੇ = read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG);
	ਜਦੋਂ (j < 8)
	{
		k = write_ਅੰਕੜੇ;
		k = ( k << j ) & 0x80;
//		printf("\n\r i: %d; j: %d; k: %d", i, j, k);
//		sda=CY;
		ਜੇ (k == 0) {
			write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) & ~(I2C_SDA)) );
			delay_loop(delay, delay);
		}
		ਨਹੀਂਤਾਂ {
			write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) | I2C_SDA) );
			delay_loop(delay, delay);
		}

	//	scl=1;
		write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) | I2C_SCL) );
		delay_loop(delay, delay);

	//	scl=0;
		write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) & ~(I2C_SCL) ) );
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
ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ I2cReadByte(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ delay)
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ j = 0, i = 0;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਦੋਆਧਾਰੀ_ਅੰਕ_ਮੁੱਲ;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ read_ਅੰਕੜੇ = 0;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ read_Gpio_ਅੰਕੜੇ = 0;
	read_ਅੰਕੜੇ = read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG);

//	sda=1;
//Make SDA high
	ਜਦੋਂ (j < 8) {
	//	scl=1;
		write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) | I2C_SCL) );
		delay_loop(delay, delay);

//		d1 = sda;
		read_Gpio_ਅੰਕੜੇ = read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG)  & I2C_SDA;
		ਜੇ (read_Gpio_ਅੰਕੜੇ != 0)
			ਦੋਆਧਾਰੀ_ਅੰਕ_ਮੁੱਲ = 1;
		ਨਹੀਂਤਾਂ
			ਦੋਆਧਾਰੀ_ਅੰਕ_ਮੁੱਲ = 0;
	    read_ਅੰਕੜੇ = read_ਅੰਕੜੇ << 1;
		read_ਅੰਕੜੇ = read_ਅੰਕੜੇ | ਦੋਆਧਾਰੀ_ਅੰਕ_ਮੁੱਲ;
		delay_loop(delay, delay);

	//	scl=0;
		write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) & ~(I2C_SCL) ) );
		delay_loop(delay, delay);

		++j;
	}

	ਵਾਪਸ read_ਅੰਕੜੇ;
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
ਖਾਲੀ ReadAckForWrite(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ delay)
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ read_ਅੰਕੜੇ = 0;
	ਲਿਖੋ("\n\tI2C: I2C Read\n");
	read_ਅੰਕੜੇ = read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG);
	delay_loop(delay, delay);
//	scl=1;delay
	ਲਿਖੋ("\n\tI2C: I2C Write\n");
	write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਅੰਕੜੇ | I2C_SCL) );
	delay_loop(delay, delay);

		ਲਿਖੋ("\n\tI2C: I2C Write\n");
		read_ਅੰਕੜੇ = read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG)  & I2C_SDA;

//	scl=0;
	ਲਿਖੋ("\n\tI2C: I2C Write\n");
	write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) & ~(I2C_SCL) ) );
	delay_loop(delay, delay);
	ਲਿਖੋ("\n\tI2C: I2C ReadNackForWrite sent\n");

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
ਖਾਲੀ SendAckForRead(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ delay)
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ read_ਅੰਕੜੇ = 0;
  ਸੈੱਟ_Sda_Direction(GPIOD_IS_ਬਾਹਰਲਾ);

//	readData = read_word(GPIO_DATA_REG);

//	sda=0;
	write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) & ~(I2C_SDA)) );
	delay_loop(delay, delay);

//	scl=1;
	write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) | I2C_SCL) );
	delay_loop(delay, delay);

//	scl=0;
	write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) & ~(I2C_SCL) ) );
	delay_loop(delay, delay);

  ਸੈੱਟ_Sda_Direction(GPIOD_IS_ਵਿੱਚ);
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
ਖਾਲੀ SendNackForRead(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ delay)
 {
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ read_ਅੰਕੜੇ = 0;
  ਸੈੱਟ_Sda_Direction(GPIOD_IS_ਬਾਹਰਲਾ);

 //	readData = read_word(GPIO_DATA_REG);

 //	sda=0;
  write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG)  | (I2C_SDA)) );
  delay_loop(delay, delay);

 //	scl=1;
  write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) | I2C_SCL) );
  delay_loop(delay, delay);

 //	scl=0;
  write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) & ~(I2C_SCL) ) );
  delay_loop(delay, delay);

  ਸੈੱਟ_Sda_Direction(GPIOD_IS_ਵਿੱਚ);
 }

/** @fn void I2cInit()
 * @brief Configuring the SDA and SCL as OUTPUTS so that Start, Slave address
 *     ,and register address or register value that needs to be writen.
 * @details I2C master Inits makes the master ready for either read or write
 *      operation.
 * @warning This bit value can be changed as per I2C_SCL macro.
 */
ਖਾਲੀ I2cInit()
{
  ਸੈੱਟ_SCLAs_Output();
  ਸੈੱਟ_Sda_Direction(GPIOD_IS_ਬਾਹਰਲਾ);
  ਲਿਖੋ("Initialization successfully done");
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
ਖਾਲੀ I2c_Send_Slave_ਪਤਾ(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ slave_ਪਤਾ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ rdWrCntrl, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ delay)
{
  ਸੈੱਟ_Sda_Direction(GPIOD_IS_ਬਾਹਰਲਾ);

  ਲਿਖੋ("\n\tI2C: I2C Start\n");
  ਸ਼ੁਰੂ(delay);
  ਲਿਖੋ("\n\tI2C: I2C Send Bytes\n");
  ਜੇ(rdWrCntrl) {
     ਲਿਖੋ("\n\tI2C: I2C Write\n");
    I2cWriteByte( (slave_ਪਤਾ | I2C_READ), delay);
	}
  ਨਹੀਂਤਾਂ {
     ਲਿਖੋ("\n\tI2C: I2C Write\n");
    I2cWriteByte( (slave_ਪਤਾ | I2C_WRITE), delay);
	}
  //	sda=1;
  write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) | I2C_SDA) );
  delay_loop(delay, delay);

  ਲਿਖੋ("\n\tI2C: I2C Write Ack\n");
  ਸੈੱਟ_Sda_Direction(GPIOD_IS_ਵਿੱਚ);
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
ਖਾਲੀ I2c_Write_ਅੰਕੜੇ(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ write_ਅੰਕੜੇ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ delay)
{
  ਸੈੱਟ_Sda_Direction(GPIOD_IS_ਬਾਹਰਲਾ);
  ਲਿਖੋ("\n\tI2C: I2C Write\n");
  I2cWriteByte( write_ਅੰਕੜੇ, delay);
  //	sda=1;
  write_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG, (read_ਸ਼ਬਦ(GPIO_ਅੰਕੜੇ_REG) | I2C_SDA) );
  delay_loop(delay, delay);

  ਲਿਖੋ("\n\tI2C: I2C Write Ack\n");
  ਸੈੱਟ_Sda_Direction(GPIOD_IS_ਵਿੱਚ);
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
ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ I2c_Read_ਅੰਕੜੇ_Ack(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ delay)
{
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ read_ਅੰਕੜੇ = 0;
  ਸੈੱਟ_Sda_Direction(GPIOD_IS_ਵਿੱਚ);
	ਲਿਖੋ("\n\tI2C: I2C Read\n");
	read_ਅੰਕੜੇ = I2cReadByte(delay);
	ਸੈੱਟ_Sda_Direction(GPIOD_IS_ਬਾਹਰਲਾ);
	ਲਿਖੋ("\n\tI2C: I2C Read Ack\n");
	SendAckForRead(delay);
  ਵਾਪਸ read_ਅੰਕੜੇ;
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
ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ I2c_Read_ਅੰਕੜੇ_Nack(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ delay)
{
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ read_ਅੰਕੜੇ = 0;
  ਸੈੱਟ_Sda_Direction(GPIOD_IS_ਵਿੱਚ);
 	ਲਿਖੋ("\n\tI2C: I2C Read\n");
  read_ਅੰਕੜੇ = I2cReadByte(delay);
	ਸੈੱਟ_Sda_Direction(GPIOD_IS_ਬਾਹਰਲਾ);
  	ਲਿਖੋ("\n\tI2C: I2C Read NAck\n");
  	SendNackForRead(delay);
    ਵਾਪਸ read_ਅੰਕੜੇ;
}

/** @fn void I2cStart(unsigned char delay)
 * @brief Sending start condition for the I2C.
 * @details Start condition is making SDA low when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char delay
 */
ਖਾਲੀ I2c_ਸ਼ੁਰੂ(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ delay)
{
  ਲਿਖੋ("\n\tI2C: I2C start\n");
  ਸ਼ੁਰੂ(delay);
}

/** @fn void I2cStop(unsigned char delay)
 * @brief Sending stop condition for the I2C.
 * @details Stop condition is making SDA high when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char delay
 */
ਖਾਲੀ I2cStop(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ delay)
{
  ਲਿਖੋ("\n\tI2C: I2C stop\n");
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
ਖਾਲੀ I2c_Write_byte(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ slave_ਪਤਾ_2,ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ reg_ਪਤਾ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਅੰਕੜੇ_2, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ delay )
{
	I2c_Send_Slave_ਪਤਾ(slave_ਪਤਾ_2, I2C_WRITE, delay);
	I2c_Write_ਅੰਕੜੇ(reg_ਪਤਾ, delay);
	I2c_Write_ਅੰਕੜੇ(ਅੰਕੜੇ_2,delay);
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
ਪੂਰਨ I2c_Read_byte(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ slave_ਪਤਾ_2,ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ reg_ਪਤਾ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ delay)
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ read_ਅੰਕੜੇ;
	I2c_Send_Slave_ਪਤਾ(slave_ਪਤਾ_2, I2C_WRITE, delay);//selecting slave to be read
	I2c_Write_ਅੰਕੜੇ(reg_ਪਤਾ, delay);//selecting register to be read
	I2c_Send_Slave_ਪਤਾ(slave_ਪਤਾ_2, I2C_READ, delay);
	read_ਅੰਕੜੇ = I2c_Read_ਅੰਕੜੇ_Ack(delay);
	I2cStop(delay);
	ਵਾਪਸ (ਪੂਰਨ) read_ਅੰਕੜੇ;
}

 /** @fn int I2c_shakti_readbytes(char *buf, int count, int last, unsigned char delay)
 * @brief To burst read (i.e read multiple bytes byte of data)
 * @details Reads "n" number of bytes from the slave device with the passed slave address 
 * @param buff Buffer pointer which holds n number of read values
 * @param count to tell how many bytes to read
 * @param last decides whether to stop operation or not
 * @return int (No. of values(bytes) read)
 */
ਪੂਰਨ I2c_shakti_readbytes(ਅੱਖਰ *buf, ਪੂਰਨ ਗਿਣਤੀ_2, ਪੂਰਨ ਆਖਰੀ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ delay)
{
	ਲਿਖੋ("start reading the slave device\n");
	ਪੂਰਨ i = 0;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ PCF8584
	ਲਈ (i = 0; i <= ਗਿਣਤੀ_2; i++) {
		ਜੇ (i != 0 && i < ਗਿਣਤੀ_2) {
			readbuf[i]=I2c_Read_ਅੰਕੜੇ_Ack(delay);
		}
		ਨਹੀਂਤਾਂ ਜੇ(i==0) I2c_Read_ਅੰਕੜੇ_Ack(delay);//dummy read
		ਨਹੀਂਤਾਂ {
			readbuf[i] = I2c_Read_ਅੰਕੜੇ_Nack(delay);
		}
		/*The following loop is useful only  for eeprom*/
		ਜੇ (ਆਖਰੀ)  I2cStop(delay);
		ਨਹੀਂਤਾਂ  I2c_ਸ਼ੁਰੂ(delay);//sending repeated start
	}
	ਵਾਪਸ i-1; //excluding the dummy read
#ਨਹੀਂਤਾਂ
	ਲਈ (i = 0; i < ਗਿਣਤੀ_2-1; i++)
		*(buf + i) = I2c_Read_ਅੰਕੜੇ_Ack(delay);
	*(buf + i) = I2c_Read_ਅੰਕੜੇ_Nack(delay);

	/*The following loop is useful only  for eeprom*/
	ਜੇ (ਆਖਰੀ)
		I2cStop(delay);
	ਨਹੀਂਤਾਂ
		I2c_ਸ਼ੁਰੂ(delay);//sending repeated start
#ਜੇ_ਅੰਤ
	ਵਾਪਸ i+1;
}
