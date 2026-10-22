/*************************************************************************
 * Project           	       : shakti devt board
 * Name of the file	       : mpu6050.c
 * Brief Description of file   : Contains the driver routines to configure and read mpu6050.
 * Name of Author              : Kotteeswaran
 * Email ID                    : kottee.1@gmail.com

 Copyright (C) 2020  IIT Madras. All rights reserved.

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
@file   mpu6050.c
@brief  Contains the driver routines to write and read all locations of mpu6050.
@detail I2C based routines to write and read all locations of mpu6050.
*/

#समावेश <stdint.h>//Includes the definitions of standard input/output functions//
#समावेश "i2c.h"
#समावेश "log.h"
#समावेश "uart.h"

#घोषणा DELAY1 100
#घोषणा DELAY2 50


#घोषणा DELAY_मूल्य 900
#अगर 1
#घोषणा PRESCALER_गिनती 24
#घोषणा SCLK_गिनती 9
#अन्यथा
#घोषणा PRESCALER_गिनती 8
#घोषणा SCLK_गिनती 6
#पूर्ण_अगर
#घोषणा I2C i2c_instance[1]
#घोषणा RD_तथ्य_CNT 14

#घोषणा MPU6050_SLAVE_ADDRESS 0xD0
#घोषणा MPU_6050_OUTPUT_BEGIN 0x3B
#घोषणा MPU6050_DLPF_CFG 0x20
#घोषणा MPU6050_SMPL_DIV 0x19
#घोषणा MPU6050_ADDRESS   0x68
#घोषणा DEV_IDENTITY  0X68
#घोषणा DEV_IDENTITY_तथ्य_REG 0X75
#घोषणा MPU6050_REG_PWR_MGMT 0X6B
#घोषणा MPU6050_RESET         0x80
#घोषणा MPU6050_ACC_SENS_2G         0x00
#घोषणा MPU6050_ACC_SENS_4G         0x08
#घोषणा MPU6050_ACC_SENS_8G         0x10
#घोषणा MPU6050_REG_GYRO_CONFIG      0x1B // Gyroscope Configuration
#घोषणा MPU6050_REG_ACCEL_CONFIG     0x1C // Accelerometer Configuration
#घोषणा MPU6050_GYRO_SENS_500D       0x08

#घोषणा PI 3.141592654

अक्षर readbuf[RD_तथ्य_CNT];
पूर्णांक AccX,AccY,AccZ;
पूर्णांक accAngleX, accAngleY, GyroAngleX, GyroAngleY, GyroAngleZ;
पूर्णांक roll, pitch, yaw;
पूर्णांक AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
पूर्णांक AccErrorX,AccErrory;
पूर्णांक GyroX, GyroY, GyroZ;
पूर्णांक c = 0;
पूर्णांक i=0;

पूर्णांक read_mpu6050_register(i2c_struct * i2c_instance, अचिन्हित पूर्णांक reg_offset, अचिन्हित अक्षर *read_तथ्य_2, अचिन्हित अक्षर लंबाई_2, अचिन्हित दीर्घ delay)
{
	अचिन्हित अक्षर read_buf[4] = {'\0'};
	पूर्णांक i = 0, j = 0,  k = 0, status=0;
	अचिन्हित अक्षर अस्थायी = 0;

//Writes the slave address for write
	i2c_send_slave_address(i2c_instance, MPU6050_SLAVE_ADDRESS, I2C_WRITE, 800);
//Writes the pointer to address that needs to be read
	i2c_write_तथ्य(i2c_instance, reg_offset, delay);
//Restarts the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_REPSTART;
	delay_loop(DELAY1, DELAY2);
//Writes the slave address for read
	i2c_write_तथ्य(i2c_instance, MPU6050_SLAVE_ADDRESS | I2C_READ, delay);
/* Make a dummy read as per spec of the I2C controller */
	i2c_instance->control = I2C_NACK;
	i2c_read_तथ्य(i2c_instance, &अस्थायी, delay);
//	printf("\n Reading the data");

	i2c_read_तथ्य_nack(i2c_instance, &अस्थायी, delay);
	*read_तथ्य_2 = अस्थायी;
//	delay_loop(DELAY1, DELAY2);
	i2c_instance->control = I2C_STOP;
	delay_loop(DELAY1, DELAY2);
	वापस 0;
}

/** @fn int read_mpu6050_registers(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int *readTemp, unsigned char length, unsigned long delay)
 * @brief Reads the ADC value from PCF8591
 * @details Reads 4 ADC values from PCF8591 over I2C interface
 * @param i2c_struct*
 * @param reg_offset
 * @param *readTemp
 * @param length
 * @param delay
 * @return read status (zero on success)
 */
पूर्णांक read_mpu6050_registers(i2c_struct * i2c_instance, अचिन्हित पूर्णांक reg_offset, अचिन्हित अक्षर *read_अस्थायी, अचिन्हित अक्षर लंबाई_2, अचिन्हित दीर्घ delay)
{
//	unsigned char read_buf[4] = {'\0'};
	पूर्णांक i = 0, j = 0,  k = 0, status=0;
	अचिन्हित अक्षर अस्थायी = 0;

//Writes the slave address for write
	i2c_send_slave_address(i2c_instance, MPU6050_SLAVE_ADDRESS, I2C_WRITE, delay);
//Writes the pointer to address that needs to be read
	i2c_write_तथ्य(i2c_instance, reg_offset, delay);
//	delay_loop(DELAY1, DELAY2);
//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_REPSTART;
	delay_loop(DELAY1, DELAY2);

//Writes the slave address for read
	i2c_write_तथ्य(i2c_instance, MPU6050_SLAVE_ADDRESS + I2C_READ, delay);
//	i2c_send_slave_address(i2c_instance, MPU6050_SLAVE_ADDRESS, I2C_READ, delay);

/* Make a dummy read as per spec of the I2C controller */
	i2c_read_तथ्य(i2c_instance, &अस्थायी, delay);

//Reads the MSB Byte of temperature [D9 - D1]
	क्रम(i = 0; i < लंबाई_2; i++)
	{
		अगर(i == (लंबाई_2 - 1) )
		{
			log_debug("\nSending nack");
			i2c_instance->control = I2C_NACK;
//			i2c_read_data_nack(i2c_instance, &temp, delay);
			i2c_read_तथ्य(i2c_instance, &अस्थायी, delay);
			अवरोध;
			}
		अन्यथा
		{
			i2c_read_तथ्य(i2c_instance, &अस्थायी, delay);
		}
		log_debug("\n read data[%x]: %x", i, अस्थायी);
		*read_अस्थायी = अस्थायी;
		*read_अस्थायी++;
	}
	
	log_debug("\n Sending Stop condition");
	i2c_instance->control = I2C_STOP;
	वापस 0;
}




/** @fn int write_pcf8591_registers(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int *write_value, unsigned char length, unsigned long delay)
 * @brief WRites into PCF8591 Register
 * @details WRites the passed value into passed PCF8591 Register (address) over I2C interface.
 * @param i2c_struct*
 * @param reg_offset
 * @param write_value
 * @param length
 * @param delay
 * @return Write status (Zero on success)
 */
पूर्णांक write_mpu6050_register(i2c_struct * i2c_instance, अचिन्हित पूर्णांक reg_offset, अचिन्हित पूर्णांक *write_मूल्य, अचिन्हित दीर्घ delay)
{
	i2c_instance->control = I2C_IDLE;
	delay_loop(DELAY1, DELAY2);
	i2c_send_slave_address(i2c_instance, MPU6050_SLAVE_ADDRESS, I2C_WRITE, delay);
//	delay_loop(DELAY1, DELAY2);
	i2c_write_तथ्य(i2c_instance, reg_offset, delay);
//	delay_loop(DELAY1, DELAY2);
	log_debug("\n write value: %x", *write_मूल्य);
	i2c_write_तथ्य(i2c_instance,  ( *write_मूल्य & 0xff), delay);
	//Stops the I2C transaction to start reading the temperature value.
//	delay_loop(DELAY1, DELAY2);
	i2c_instance->control = I2C_STOP;
	delay_loop(DELAY1, DELAY2);

}



/** @fn int write_pcf8591_registers(i2c_struct * i2c_instance, unsigned int reg_offset, unsigned int *write_value, unsigned char length, unsigned long delay)
 * @brief WRites into PCF8591 Register
 * @details WRites the passed value into passed PCF8591 Register (address) over I2C interface.
 * @param i2c_struct*
 * @param reg_offset
 * @param write_value
 * @param length
 * @param delay
 * @return Write status (Zero on success)
 */
पूर्णांक write_mpu6050_registers(i2c_struct * i2c_instance, अचिन्हित पूर्णांक reg_offset, अचिन्हित पूर्णांक *write_मूल्य, अचिन्हित अक्षर लंबाई_2, अचिन्हित दीर्घ delay)
{
	पूर्णांक i = 0, j = 0,  k = 0, status=0;
	अचिन्हित पूर्णांक अस्थायी = 0;
	
	i2c_send_slave_address(i2c_instance, MPU6050_SLAVE_ADDRESS, I2C_WRITE, delay);
	i2c_write_तथ्य(i2c_instance, reg_offset, delay);
	delay_loop(DELAY1, DELAY2);
	
	अगर(1 == लंबाई_2)
	{
		i2c_write_तथ्य(i2c_instance,  ( *write_मूल्य	& 0xff), delay);
	}
	अन्यथा
	{
		क्रम(i = 0; i < लंबाई_2; i++)
		{
			i2c_write_तथ्य(i2c_instance, (*write_मूल्य++ & 0xff), delay);

		}
	}

//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;
	delay_loop(DELAY1, DELAY2);
	वापस 0;
}

/*
   soft float library need to be added, if hardfloat not there
 */
व्योम measuring_मूल्य(अचिन्हित दीर्घ delay)
{
	// read accelerometer data
	read_mpu6050_registers(I2C, MPU_6050_OUTPUT_BEGIN, readbuf, RD_तथ्य_CNT, delay);
	म_लिखो("\n Read Buf: { ");
	क्रम(i = 0; i < RD_तथ्य_CNT; i++)
	{
		log_info(" %x, ", readbuf[i] );
		}
	log_info(" }\n" ); 
/*	AccX = (readbuf[0]<<8 |readbuf[1]) / 4096; //16-bit X-axis data
	AccY = (readbuf[2]<<8 |readbuf[3]) / 4096; //16-bit Y-axis data
	AccZ = (readbuf[4]<<8 |readbuf[5]) / 4096; //16-bit Z-axis data

	GyroX = (readbuf[8]<<8 |readbuf[9]) /65.5 ; //
	GyroY = (readbuf[10]<<8 |readbuf[11]) / 65.5; //
	GyroZ = (readbuf[12]<<8 |readbuf[13]) / 65.5;

	// Correct the outputs with the calculated error values
	GyroX = GyroX + GyroErrorX ; // GyroErrorX
	GyroY = GyroY - GyroErrorY; // GyroErrorY
	GyroZ = GyroZ + GyroErrorZ; // GyroErrorZ
*/
}


व्योम calculate_imu_error(अचिन्हित दीर्घ delay)
{
	पूर्णांक c=0;
	पूर्णांक yaw;
	भग्न accAngleX, accAngleY, GyroAngleX, GyroAngleY, GyroAngleZ;

	जबतक(c<200)
	{
		measuring_मूल्य(delay);

		AccErrorX = AccErrorX + (atan(AccY / वर्ग_मूल(घात(AccX, 2)) + घात(AccZ, 2)))* 180 / PI;
		AccErrorY = AccErrorY + (atan(AccY / वर्ग_मूल(घात(AccX, 2)) + घात(AccZ, 2)))* 180 / PI;

		GyroErrorX = GyroErrorX + (GyroX / 65.5);
		GyroErrorY = GyroErrorY + (GyroY / 65.5);
		GyroErrorZ = GyroErrorZ + (GyroZ / 65.5);
		c++;
	}
	c=0;
	AccErrorX = AccErrorX / 200;
	AccErrorY = AccErrorY / 200;

	accAngleX = (atan(AccY / वर्ग_मूल(घात(AccX, 2) + घात(AccZ, 2))) * 180 / PI) - AccErrorX; // AccErrorX
	accAngleY = (atan(-1 * AccX / वर्ग_मूल(घात(AccY, 2) + घात(AccZ, 2))) * 180 / PI) - AccErrorY; // AccErrory
	// sum all reading
	GyroErrorX = GyroErrorX / 200;
	GyroErrorY = GyroErrorY / 200;
	GyroErrorZ = GyroErrorZ / 200;

	GyroX = GyroX - GyroErrorX ; // GyroErrorX
	GyroY = GyroY - GyroErrorY; // GyroErrorY
	GyroZ = GyroZ - GyroErrorZ; // GyroErrorZ
}

अचिन्हित अक्षर CheckForDeviceId(अचिन्हित दीर्घ delay)
{
	अचिन्हित अक्षर readBuf = 0xFF;
	read_mpu6050_register(I2C, DEV_IDENTITY_तथ्य_REG, &readBuf, 1, delay);
	log_debug("\n Read Buf Value: %x", readBuf);
	वापस readBuf;
}

पूर्णांक मुख्य()
{
	अचिन्हित अक्षर i = 0;
	पूर्णांक timeout;
	अचिन्हित दीर्घ delay = 500;
	अचिन्हित पूर्णांक write_buf[7] = {0x00};
	अचिन्हित अक्षर लंबाई_2 = 0;

	log_debug("\tI2C: MPU6050 - ACC test\n");


	i2c_init();

	अगर(config_i2c(I2C, PRESCALER_गिनती, SCLK_गिनती))
	{
			log_error("\tSomething Wrong In Initialization\n");
			वापस -1;
	}
	अन्यथा
		log_info("\tIntilization Happened Fine\n");

		अगर(DEV_IDENTITY == CheckForDeviceId(delay))
		{
			log_info("Device ID Check Success");
		}
		अन्यथा
		{
			log_error("Could not verify Device identity");
		}
		write_buf[0] = 1;
		write_mpu6050_register(I2C, MPU6050_REG_PWR_MGMT, &write_buf[0],  delay);
		write_buf[0] = MPU6050_GYRO_SENS_500D;
		write_mpu6050_register(I2C, MPU6050_REG_GYRO_CONFIG, &write_buf[0], delay);
		write_buf[0] = 0x01;
		write_mpu6050_register(I2C, 0x1B, &write_buf[0], delay);
		write_buf[0] = 0x01;
		write_mpu6050_register(I2C, 0x1C, &write_buf[0], delay);
		write_buf[0] = 0x01;
		write_mpu6050_register(I2C, 0x6B, &write_buf[0], delay);


	log_debug("\n Entering While loop");
	जबतक(1)
	{
		measuring_मूल्य(delay);
		delay_loop(2000, 1000);
	}

	वापस 0;
}

