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

#ಅನ್ತರ್ಭಾವ "platform.h"
#ಅನ್ತರ್ಭಾವ "gpio.h"
#ಅನ್ತರ್ಭಾವ "gpio_i2c.h"

/** @fn extern void delay_loop(unsigned long , unsigned long)
 * @brief Maintains the required delay to perform an operation
 * @param unsigned long 
 * @param unsigned long
 */
ಬಾಹ್ಯ ಶೂನ್ಯ delay_loop(ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ , ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ);

/** @fn static void SetSCLAsOutput()
 * @brief Function for configure GPIO 0 as SCL output.
 * @details This function will be called to make the scl line (defined by I2C_SCL)
 *             macro as output.
 * @warning This bit value can be changed as per I2C_SCL macro.
 */
ಸ್ಥಿರ ಶೂನ್ಯ ಗಣ_SCLAs_Output()
{
	ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ read_ದತ್ತಾಂಶ = 0;
	read_ದತ್ತಾಂಶ = read_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG);
	write_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG, (read_ದತ್ತಾಂಶ | I2C_SCL) );
	ಬರೆ("SCL set as output\n");
}

/** @fn static void SetSdaDirection(int inOutCntrl)
 *  @brief Function for configure GPIO 0 as SCL output.
 * @details This function will be called to make the scl line (defined by I2C_SCL)
 *           macro as output.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param int inOutCntrl
 */
ಸ್ಥಿರ ಶೂನ್ಯ ಗಣ_Sda_Direction(ಪೂರ್ಣಾಂಕ ಒಳ_ಹೊರಹೋಗು_Cntrl)
{
	ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ read_ದತ್ತಾಂಶ = 0;
	read_ದತ್ತಾಂಶ = read_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG);

	ಆದರೆ (ಒಳ_ಹೊರಹೋಗು_Cntrl) { // output
		write_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG, (read_ದತ್ತಾಂಶ | I2C_SDA) );
		ಬರೆ("\n\tSDA set as output\n");
	}
    ಇಲ್ಲದಿದ್ದರೆ {
		write_ಶಬ್ದ(GPIO_DIRECTION_CNTRL_REG, (read_ದತ್ತಾಂಶ & ~(I2C_SDA) ) );
		ಬರೆ("\n\tSDA set as input\n");
	}
}

/** @fn static void start(unsigned char delay)
 * @brief Sending start condition for the I2C.
 * @details Start condition is making SDA low when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char delay
 */
ಸ್ಥಿರ ಶೂನ್ಯ ಆರಂಭ(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay)
{
	ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ read_ದತ್ತಾಂಶ = 0;
	read_ದತ್ತಾಂಶ = read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG);

//	sda=1;
	write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) | I2C_SDA | I2C_SCL) );
	delay_loop(delay, delay);

//		scl=1;
	write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) | I2C_SCL) );
	delay_loop(delay, delay);

//		sda=0;
	write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) & ~(I2C_SDA)) );
	delay_loop(delay, delay);

//		scl=0;
	write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) & ~(I2C_SCL) ) );
	delay_loop(delay, delay);

	ಬರೆ("\n\tI2C: I2C Start condition sent\n");
}

/** @fn static void stop(unsigned char delay)
 * @brief Sending stop condition for the I2C.
 * @details Stop condition is making SDA high when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char
 */
ಸ್ಥಿರ ಶೂನ್ಯ stop(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay)
{
	ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ read_ದತ್ತಾಂಶ = 0;
	read_ದತ್ತಾಂಶ = read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG);
//	sda=0;
	write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) & ~(I2C_SDA)) );
	delay_loop(delay, delay);

//	scl=1;
	write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) | I2C_SCL) );
	delay_loop(delay, delay);

//	sda=1;
	write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) | I2C_SDA) );
	delay_loop(delay, delay);
	ಬರೆ("\n\tI2C: I2C Start condition sent\n");

}

/** @fn void I2cWriteByte(unsigned char writeData, unsigned char delay)
 * @brief Writes a byte to the I2C device.
 * @details Data is put on the SDA Line bit by bit and then makes the
 *  SCL from low to high to write..
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param writeData --> Value that needs to be written.
 * @param unsigned char delay
 */
ಶೂನ್ಯ I2cWriteByte(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ write_ದತ್ತಾಂಶ, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay)
{
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ j = 0,k;
	ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ read_ದತ್ತಾಂಶ = 0;
	read_ದತ್ತಾಂಶ = read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG);
	ಆಗ (j < 8)
	{
		k = write_ದತ್ತಾಂಶ;
		k = ( k << j ) & 0x80;
//		printf("\n\r i: %d; j: %d; k: %d", i, j, k);
//		sda=CY;
		ಆದರೆ (k == 0) {
			write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) & ~(I2C_SDA)) );
			delay_loop(delay, delay);
		}
		ಇಲ್ಲದಿದ್ದರೆ {
			write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) | I2C_SDA) );
			delay_loop(delay, delay);
		}

	//	scl=1;
		write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) | I2C_SCL) );
		delay_loop(delay, delay);

	//	scl=0;
		write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) & ~(I2C_SCL) ) );
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
ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ I2cReadByte(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay)
{
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ j = 0, i = 0;
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ಬಿಟ್_ಮೌಲ್ಯ;
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ read_ದತ್ತಾಂಶ = 0;
  ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ read_Gpio_ದತ್ತಾಂಶ = 0;
	read_ದತ್ತಾಂಶ = read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG);

//	sda=1;
//Make SDA high
	ಆಗ (j < 8) {
	//	scl=1;
		write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) | I2C_SCL) );
		delay_loop(delay, delay);

//		d1 = sda;
		read_Gpio_ದತ್ತಾಂಶ = read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG)  & I2C_SDA;
		ಆದರೆ (read_Gpio_ದತ್ತಾಂಶ != 0)
			ಬಿಟ್_ಮೌಲ್ಯ = 1;
		ಇಲ್ಲದಿದ್ದರೆ
			ಬಿಟ್_ಮೌಲ್ಯ = 0;
	    read_ದತ್ತಾಂಶ = read_ದತ್ತಾಂಶ << 1;
		read_ದತ್ತಾಂಶ = read_ದತ್ತಾಂಶ | ಬಿಟ್_ಮೌಲ್ಯ;
		delay_loop(delay, delay);

	//	scl=0;
		write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) & ~(I2C_SCL) ) );
		delay_loop(delay, delay);

		++j;
	}

	ಹಿಂತಿರುಗಿ read_ದತ್ತಾಂಶ;
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
ಶೂನ್ಯ ReadAckForWrite(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay)
{
	ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ read_ದತ್ತಾಂಶ = 0;
	ಬರೆ("\n\tI2C: I2C Read\n");
	read_ದತ್ತಾಂಶ = read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG);
	delay_loop(delay, delay);
//	scl=1;delay
	ಬರೆ("\n\tI2C: I2C Write\n");
	write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ದತ್ತಾಂಶ | I2C_SCL) );
	delay_loop(delay, delay);

		ಬರೆ("\n\tI2C: I2C Write\n");
		read_ದತ್ತಾಂಶ = read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG)  & I2C_SDA;

//	scl=0;
	ಬರೆ("\n\tI2C: I2C Write\n");
	write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) & ~(I2C_SCL) ) );
	delay_loop(delay, delay);
	ಬರೆ("\n\tI2C: I2C ReadNackForWrite sent\n");

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
ಶೂನ್ಯ SendAckForRead(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay)
{
	ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ read_ದತ್ತಾಂಶ = 0;
  ಗಣ_Sda_Direction(GPIOD_IS_ಹೊರಹೋಗು);

//	readData = read_word(GPIO_DATA_REG);

//	sda=0;
	write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) & ~(I2C_SDA)) );
	delay_loop(delay, delay);

//	scl=1;
	write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) | I2C_SCL) );
	delay_loop(delay, delay);

//	scl=0;
	write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) & ~(I2C_SCL) ) );
	delay_loop(delay, delay);

  ಗಣ_Sda_Direction(GPIOD_IS_ಒಳ);
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
ಶೂನ್ಯ SendNackForRead(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay)
 {
  ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ read_ದತ್ತಾಂಶ = 0;
  ಗಣ_Sda_Direction(GPIOD_IS_ಹೊರಹೋಗು);

 //	readData = read_word(GPIO_DATA_REG);

 //	sda=0;
  write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG)  | (I2C_SDA)) );
  delay_loop(delay, delay);

 //	scl=1;
  write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) | I2C_SCL) );
  delay_loop(delay, delay);

 //	scl=0;
  write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) & ~(I2C_SCL) ) );
  delay_loop(delay, delay);

  ಗಣ_Sda_Direction(GPIOD_IS_ಒಳ);
 }

/** @fn void I2cInit()
 * @brief Configuring the SDA and SCL as OUTPUTS so that Start, Slave address
 *     ,and register address or register value that needs to be writen.
 * @details I2C master Inits makes the master ready for either read or write
 *      operation.
 * @warning This bit value can be changed as per I2C_SCL macro.
 */
ಶೂನ್ಯ I2cInit()
{
  ಗಣ_SCLAs_Output();
  ಗಣ_Sda_Direction(GPIOD_IS_ಹೊರಹೋಗು);
  ಬರೆ("Initialization successfully done");
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
ಶೂನ್ಯ I2c_Send_Slave_ವಿಳಾಸ(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ slave_ವಿಳಾಸ, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ rdWrCntrl, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay)
{
  ಗಣ_Sda_Direction(GPIOD_IS_ಹೊರಹೋಗು);

  ಬರೆ("\n\tI2C: I2C Start\n");
  ಆರಂಭ(delay);
  ಬರೆ("\n\tI2C: I2C Send Bytes\n");
  ಆದರೆ(rdWrCntrl) {
     ಬರೆ("\n\tI2C: I2C Write\n");
    I2cWriteByte( (slave_ವಿಳಾಸ | I2C_READ), delay);
	}
  ಇಲ್ಲದಿದ್ದರೆ {
     ಬರೆ("\n\tI2C: I2C Write\n");
    I2cWriteByte( (slave_ವಿಳಾಸ | I2C_WRITE), delay);
	}
  //	sda=1;
  write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) | I2C_SDA) );
  delay_loop(delay, delay);

  ಬರೆ("\n\tI2C: I2C Write Ack\n");
  ಗಣ_Sda_Direction(GPIOD_IS_ಒಳ);
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
ಶೂನ್ಯ I2c_Write_ದತ್ತಾಂಶ(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ write_ದತ್ತಾಂಶ, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay)
{
  ಗಣ_Sda_Direction(GPIOD_IS_ಹೊರಹೋಗು);
  ಬರೆ("\n\tI2C: I2C Write\n");
  I2cWriteByte( write_ದತ್ತಾಂಶ, delay);
  //	sda=1;
  write_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG, (read_ಶಬ್ದ(GPIO_ದತ್ತಾಂಶ_REG) | I2C_SDA) );
  delay_loop(delay, delay);

  ಬರೆ("\n\tI2C: I2C Write Ack\n");
  ಗಣ_Sda_Direction(GPIOD_IS_ಒಳ);
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
ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ I2c_Read_ದತ್ತಾಂಶ_Ack(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay)
{
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ read_ದತ್ತಾಂಶ = 0;
  ಗಣ_Sda_Direction(GPIOD_IS_ಒಳ);
	ಬರೆ("\n\tI2C: I2C Read\n");
	read_ದತ್ತಾಂಶ = I2cReadByte(delay);
	ಗಣ_Sda_Direction(GPIOD_IS_ಹೊರಹೋಗು);
	ಬರೆ("\n\tI2C: I2C Read Ack\n");
	SendAckForRead(delay);
  ಹಿಂತಿರುಗಿ read_ದತ್ತಾಂಶ;
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
ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ I2c_Read_ದತ್ತಾಂಶ_Nack(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay)
{
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ read_ದತ್ತಾಂಶ = 0;
  ಗಣ_Sda_Direction(GPIOD_IS_ಒಳ);
 	ಬರೆ("\n\tI2C: I2C Read\n");
  read_ದತ್ತಾಂಶ = I2cReadByte(delay);
	ಗಣ_Sda_Direction(GPIOD_IS_ಹೊರಹೋಗು);
  	ಬರೆ("\n\tI2C: I2C Read NAck\n");
  	SendNackForRead(delay);
    ಹಿಂತಿರುಗಿ read_ದತ್ತಾಂಶ;
}

/** @fn void I2cStart(unsigned char delay)
 * @brief Sending start condition for the I2C.
 * @details Start condition is making SDA low when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char delay
 */
ಶೂನ್ಯ I2c_ಆರಂಭ(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay)
{
  ಬರೆ("\n\tI2C: I2C start\n");
  ಆರಂಭ(delay);
}

/** @fn void I2cStop(unsigned char delay)
 * @brief Sending stop condition for the I2C.
 * @details Stop condition is making SDA high when clock is high.
 * @warning This bit value can be changed as per I2C_SCL macro.
 * @param unsigned char delay
 */
ಶೂನ್ಯ I2cStop(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay)
{
  ಬರೆ("\n\tI2C: I2C stop\n");
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
ಶೂನ್ಯ I2c_Write_byte(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ slave_ವಿಳಾಸ_2,ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ reg_ವಿಳಾಸ, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ದತ್ತಾಂಶ_2, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay )
{
	I2c_Send_Slave_ವಿಳಾಸ(slave_ವಿಳಾಸ_2, I2C_WRITE, delay);
	I2c_Write_ದತ್ತಾಂಶ(reg_ವಿಳಾಸ, delay);
	I2c_Write_ದತ್ತಾಂಶ(ದತ್ತಾಂಶ_2,delay);
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
ಪೂರ್ಣಾಂಕ I2c_Read_byte(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ slave_ವಿಳಾಸ_2,ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ reg_ವಿಳಾಸ, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay)
{
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ read_ದತ್ತಾಂಶ;
	I2c_Send_Slave_ವಿಳಾಸ(slave_ವಿಳಾಸ_2, I2C_WRITE, delay);//selecting slave to be read
	I2c_Write_ದತ್ತಾಂಶ(reg_ವಿಳಾಸ, delay);//selecting register to be read
	I2c_Send_Slave_ವಿಳಾಸ(slave_ವಿಳಾಸ_2, I2C_READ, delay);
	read_ದತ್ತಾಂಶ = I2c_Read_ದತ್ತಾಂಶ_Ack(delay);
	I2cStop(delay);
	ಹಿಂತಿರುಗಿ (ಪೂರ್ಣಾಂಕ) read_ದತ್ತಾಂಶ;
}

 /** @fn int I2c_shakti_readbytes(char *buf, int count, int last, unsigned char delay)
 * @brief To burst read (i.e read multiple bytes byte of data)
 * @details Reads "n" number of bytes from the slave device with the passed slave address 
 * @param buff Buffer pointer which holds n number of read values
 * @param count to tell how many bytes to read
 * @param last decides whether to stop operation or not
 * @return int (No. of values(bytes) read)
 */
ಪೂರ್ಣಾಂಕ I2c_shakti_readbytes(ಅಕ್ಷರ *buf, ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2, ಪೂರ್ಣಾಂಕ ಕೊನೆಯ, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay)
{
	ಬರೆ("start reading the slave device\n");
	ಪೂರ್ಣಾಂಕ i = 0;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ PCF8584
	ಗಾಗಿ (i = 0; i <= ಎಣಿಕೆ_2; i++) {
		ಆದರೆ (i != 0 && i < ಎಣಿಕೆ_2) {
			readbuf[i]=I2c_Read_ದತ್ತಾಂಶ_Ack(delay);
		}
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ(i==0) I2c_Read_ದತ್ತಾಂಶ_Ack(delay);//dummy read
		ಇಲ್ಲದಿದ್ದರೆ {
			readbuf[i] = I2c_Read_ದತ್ತಾಂಶ_Nack(delay);
		}
		/*The following loop is useful only  for eeprom*/
		ಆದರೆ (ಕೊನೆಯ)  I2cStop(delay);
		ಇಲ್ಲದಿದ್ದರೆ  I2c_ಆರಂಭ(delay);//sending repeated start
	}
	ಹಿಂತಿರುಗಿ i-1; //excluding the dummy read
#ಇಲ್ಲದಿದ್ದರೆ
	ಗಾಗಿ (i = 0; i < ಎಣಿಕೆ_2-1; i++)
		*(buf + i) = I2c_Read_ದತ್ತಾಂಶ_Ack(delay);
	*(buf + i) = I2c_Read_ದತ್ತಾಂಶ_Nack(delay);

	/*The following loop is useful only  for eeprom*/
	ಆದರೆ (ಕೊನೆಯ)
		I2cStop(delay);
	ಇಲ್ಲದಿದ್ದರೆ
		I2c_ಆರಂಭ(delay);//sending repeated start
#ಆದರೆ_ಅಂತ್ಯ
	ಹಿಂತಿರುಗಿ i+1;
}
