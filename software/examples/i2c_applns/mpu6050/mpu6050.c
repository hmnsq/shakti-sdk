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

#ಅನ್ತರ್ಭಾವ <stdint.h>//Includes the definitions of standard input/output functions//
#ಅನ್ತರ್ಭಾವ "i2c.h"
#ಅನ್ತರ್ಭಾವ "log.h"
#ಅನ್ತರ್ಭಾವ "uart.h"

#ವ್ಯಾಖ್ಯಾನಿಸು DELAY1 100
#ವ್ಯಾಖ್ಯಾನಿಸು DELAY2 50


#ವ್ಯಾಖ್ಯಾನಿಸು DELAY_ಮೌಲ್ಯ 900
#ಆದರೆ 1
#ವ್ಯಾಖ್ಯಾನಿಸು PRESCALER_ಎಣಿಕೆ 24
#ವ್ಯಾಖ್ಯಾನಿಸು SCLK_ಎಣಿಕೆ 9
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು PRESCALER_ಎಣಿಕೆ 8
#ವ್ಯಾಖ್ಯಾನಿಸು SCLK_ಎಣಿಕೆ 6
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿಸು I2C i2c_instance[1]
#ವ್ಯಾಖ್ಯಾನಿಸು RD_ದತ್ತಾಂಶ_CNT 14

#ವ್ಯಾಖ್ಯಾನಿಸು MPU6050_SLAVE_ವಿಳಾಸ 0xD0
#ವ್ಯಾಖ್ಯಾನಿಸು MPU_6050_OUTPUT_BEGIN 0x3B
#ವ್ಯಾಖ್ಯಾನಿಸು MPU6050_DLPF_CFG 0x20
#ವ್ಯಾಖ್ಯಾನಿಸು MPU6050_SMPL_DIV 0x19
#ವ್ಯಾಖ್ಯಾನಿಸು MPU6050_ವಿಳಾಸ   0x68
#ವ್ಯಾಖ್ಯಾನಿಸು DEV_ತಟಸ್ಥ  0X68
#ವ್ಯಾಖ್ಯಾನಿಸು DEV_ತಟಸ್ಥ_ದತ್ತಾಂಶ_REG 0X75
#ವ್ಯಾಖ್ಯಾನಿಸು MPU6050_REG_PWR_MGMT 0X6B
#ವ್ಯಾಖ್ಯಾನಿಸು MPU6050_RESET         0x80
#ವ್ಯಾಖ್ಯಾನಿಸು MPU6050_ACC_SENS_2G         0x00
#ವ್ಯಾಖ್ಯಾನಿಸು MPU6050_ACC_SENS_4G         0x08
#ವ್ಯಾಖ್ಯಾನಿಸು MPU6050_ACC_SENS_8G         0x10
#ವ್ಯಾಖ್ಯಾನಿಸು MPU6050_REG_GYRO_CONFIG      0x1B // Gyroscope Configuration
#ವ್ಯಾಖ್ಯಾನಿಸು MPU6050_REG_ACCEL_CONFIG     0x1C // Accelerometer Configuration
#ವ್ಯಾಖ್ಯಾನಿಸು MPU6050_GYRO_SENS_500D       0x08

#ವ್ಯಾಖ್ಯಾನಿಸು PI 3.141592654

ಅಕ್ಷರ readbuf[RD_ದತ್ತಾಂಶ_CNT];
ಪೂರ್ಣಾಂಕ AccX,AccY,AccZ;
ಪೂರ್ಣಾಂಕ accAngleX, accAngleY, GyroAngleX, GyroAngleY, GyroAngleZ;
ಪೂರ್ಣಾಂಕ roll, pitch, yaw;
ಪೂರ್ಣಾಂಕ AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
ಪೂರ್ಣಾಂಕ AccErrorX,AccErrory;
ಪೂರ್ಣಾಂಕ GyroX, GyroY, GyroZ;
ಪೂರ್ಣಾಂಕ c = 0;
ಪೂರ್ಣಾಂಕ i=0;

ಪೂರ್ಣಾಂಕ read_mpu6050_ರಿಜಿಸ್ಟರ್(i2c_struct * i2c_instance, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ reg_ಸ್ಥಾನಾಂತರ, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *read_ದತ್ತಾಂಶ_2, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ಉದ್ದಳತೆ_2, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay)
{
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ read_buf[4] = {'\0'};
	ಪೂರ್ಣಾಂಕ i = 0, j = 0,  k = 0, ಸ್ಥಿತಿ_3=0;
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ತಾತ್ಕಾಲಿಕ = 0;

//Writes the slave address for write
	i2c_send_slave_ವಿಳಾಸ(i2c_instance, MPU6050_SLAVE_ವಿಳಾಸ, I2C_WRITE, 800);
//Writes the pointer to address that needs to be read
	i2c_write_ದತ್ತಾಂಶ(i2c_instance, reg_ಸ್ಥಾನಾಂತರ, delay);
//Restarts the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_REPSTART;
	delay_loop(DELAY1, DELAY2);
//Writes the slave address for read
	i2c_write_ದತ್ತಾಂಶ(i2c_instance, MPU6050_SLAVE_ವಿಳಾಸ | I2C_READ, delay);
/* Make a dummy read as per spec of the I2C controller */
	i2c_instance->control = I2C_NACK;
	i2c_read_ದತ್ತಾಂಶ(i2c_instance, &ತಾತ್ಕಾಲಿಕ, delay);
//	printf("\n Reading the data");

	i2c_read_ದತ್ತಾಂಶ_nack(i2c_instance, &ತಾತ್ಕಾಲಿಕ, delay);
	*read_ದತ್ತಾಂಶ_2 = ತಾತ್ಕಾಲಿಕ;
//	delay_loop(DELAY1, DELAY2);
	i2c_instance->control = I2C_STOP;
	delay_loop(DELAY1, DELAY2);
	ಹಿಂತಿರುಗಿ 0;
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
ಪೂರ್ಣಾಂಕ read_mpu6050_registers(i2c_struct * i2c_instance, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ reg_ಸ್ಥಾನಾಂತರ, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *read_ತಾತ್ಕಾಲಿಕ, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ಉದ್ದಳತೆ_2, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay)
{
//	unsigned char read_buf[4] = {'\0'};
	ಪೂರ್ಣಾಂಕ i = 0, j = 0,  k = 0, ಸ್ಥಿತಿ_3=0;
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ತಾತ್ಕಾಲಿಕ = 0;

//Writes the slave address for write
	i2c_send_slave_ವಿಳಾಸ(i2c_instance, MPU6050_SLAVE_ವಿಳಾಸ, I2C_WRITE, delay);
//Writes the pointer to address that needs to be read
	i2c_write_ದತ್ತಾಂಶ(i2c_instance, reg_ಸ್ಥಾನಾಂತರ, delay);
//	delay_loop(DELAY1, DELAY2);
//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_REPSTART;
	delay_loop(DELAY1, DELAY2);

//Writes the slave address for read
	i2c_write_ದತ್ತಾಂಶ(i2c_instance, MPU6050_SLAVE_ವಿಳಾಸ + I2C_READ, delay);
//	i2c_send_slave_address(i2c_instance, MPU6050_SLAVE_ADDRESS, I2C_READ, delay);

/* Make a dummy read as per spec of the I2C controller */
	i2c_read_ದತ್ತಾಂಶ(i2c_instance, &ತಾತ್ಕಾಲಿಕ, delay);

//Reads the MSB Byte of temperature [D9 - D1]
	ಗಾಗಿ(i = 0; i < ಉದ್ದಳತೆ_2; i++)
	{
		ಆದರೆ(i == (ಉದ್ದಳತೆ_2 - 1) )
		{
			log_debug("\nSending nack");
			i2c_instance->control = I2C_NACK;
//			i2c_read_data_nack(i2c_instance, &temp, delay);
			i2c_read_ದತ್ತಾಂಶ(i2c_instance, &ತಾತ್ಕಾಲಿಕ, delay);
			ನಿಲ್ಲಿಸು;
			}
		ಇಲ್ಲದಿದ್ದರೆ
		{
			i2c_read_ದತ್ತಾಂಶ(i2c_instance, &ತಾತ್ಕಾಲಿಕ, delay);
		}
		log_debug("\n read data[%x]: %x", i, ತಾತ್ಕಾಲಿಕ);
		*read_ತಾತ್ಕಾಲಿಕ = ತಾತ್ಕಾಲಿಕ;
		*read_ತಾತ್ಕಾಲಿಕ++;
	}
	
	log_debug("\n Sending Stop condition");
	i2c_instance->control = I2C_STOP;
	ಹಿಂತಿರುಗಿ 0;
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
ಪೂರ್ಣಾಂಕ write_mpu6050_ರಿಜಿಸ್ಟರ್(i2c_struct * i2c_instance, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ reg_ಸ್ಥಾನಾಂತರ, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ *write_ಮೌಲ್ಯ, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay)
{
	i2c_instance->control = I2C_IDLE;
	delay_loop(DELAY1, DELAY2);
	i2c_send_slave_ವಿಳಾಸ(i2c_instance, MPU6050_SLAVE_ವಿಳಾಸ, I2C_WRITE, delay);
//	delay_loop(DELAY1, DELAY2);
	i2c_write_ದತ್ತಾಂಶ(i2c_instance, reg_ಸ್ಥಾನಾಂತರ, delay);
//	delay_loop(DELAY1, DELAY2);
	log_debug("\n write value: %x", *write_ಮೌಲ್ಯ);
	i2c_write_ದತ್ತಾಂಶ(i2c_instance,  ( *write_ಮೌಲ್ಯ & 0xff), delay);
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
ಪೂರ್ಣಾಂಕ write_mpu6050_registers(i2c_struct * i2c_instance, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ reg_ಸ್ಥಾನಾಂತರ, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ *write_ಮೌಲ್ಯ, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ಉದ್ದಳತೆ_2, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay)
{
	ಪೂರ್ಣಾಂಕ i = 0, j = 0,  k = 0, ಸ್ಥಿತಿ_3=0;
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ತಾತ್ಕಾಲಿಕ = 0;
	
	i2c_send_slave_ವಿಳಾಸ(i2c_instance, MPU6050_SLAVE_ವಿಳಾಸ, I2C_WRITE, delay);
	i2c_write_ದತ್ತಾಂಶ(i2c_instance, reg_ಸ್ಥಾನಾಂತರ, delay);
	delay_loop(DELAY1, DELAY2);
	
	ಆದರೆ(1 == ಉದ್ದಳತೆ_2)
	{
		i2c_write_ದತ್ತಾಂಶ(i2c_instance,  ( *write_ಮೌಲ್ಯ	& 0xff), delay);
	}
	ಇಲ್ಲದಿದ್ದರೆ
	{
		ಗಾಗಿ(i = 0; i < ಉದ್ದಳತೆ_2; i++)
		{
			i2c_write_ದತ್ತಾಂಶ(i2c_instance, (*write_ಮೌಲ್ಯ++ & 0xff), delay);

		}
	}

//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;
	delay_loop(DELAY1, DELAY2);
	ಹಿಂತಿರುಗಿ 0;
}

/*
   soft float library need to be added, if hardfloat not there
 */
ಶೂನ್ಯ measuring_ಮೌಲ್ಯ(ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay)
{
	// read accelerometer data
	read_mpu6050_registers(I2C, MPU_6050_OUTPUT_BEGIN, readbuf, RD_ದತ್ತಾಂಶ_CNT, delay);
	ಬರೆ("\n Read Buf: { ");
	ಗಾಗಿ(i = 0; i < RD_ದತ್ತಾಂಶ_CNT; i++)
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


ಶೂನ್ಯ calculate_imu_error(ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay)
{
	ಪೂರ್ಣಾಂಕ c=0;
	ಪೂರ್ಣಾಂಕ yaw;
	ದಶಮಾಂಶ accAngleX, accAngleY, GyroAngleX, GyroAngleY, GyroAngleZ;

	ಆಗ(c<200)
	{
		measuring_ಮೌಲ್ಯ(delay);

		AccErrorX = AccErrorX + (atan(AccY / ವರ್ಗಮೂಲ(ಘಾತ(AccX, 2)) + ಘಾತ(AccZ, 2)))* 180 / PI;
		AccErrorY = AccErrorY + (atan(AccY / ವರ್ಗಮೂಲ(ಘಾತ(AccX, 2)) + ಘಾತ(AccZ, 2)))* 180 / PI;

		GyroErrorX = GyroErrorX + (GyroX / 65.5);
		GyroErrorY = GyroErrorY + (GyroY / 65.5);
		GyroErrorZ = GyroErrorZ + (GyroZ / 65.5);
		c++;
	}
	c=0;
	AccErrorX = AccErrorX / 200;
	AccErrorY = AccErrorY / 200;

	accAngleX = (atan(AccY / ವರ್ಗಮೂಲ(ಘಾತ(AccX, 2) + ಘಾತ(AccZ, 2))) * 180 / PI) - AccErrorX; // AccErrorX
	accAngleY = (atan(-1 * AccX / ವರ್ಗಮೂಲ(ಘಾತ(AccY, 2) + ಘಾತ(AccZ, 2))) * 180 / PI) - AccErrorY; // AccErrory
	// sum all reading
	GyroErrorX = GyroErrorX / 200;
	GyroErrorY = GyroErrorY / 200;
	GyroErrorZ = GyroErrorZ / 200;

	GyroX = GyroX - GyroErrorX ; // GyroErrorX
	GyroY = GyroY - GyroErrorY; // GyroErrorY
	GyroZ = GyroZ - GyroErrorZ; // GyroErrorZ
}

ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ CheckForDeviceId(ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay)
{
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ readBuf = 0xFF;
	read_mpu6050_ರಿಜಿಸ್ಟರ್(I2C, DEV_ತಟಸ್ಥ_ದತ್ತಾಂಶ_REG, &readBuf, 1, delay);
	log_debug("\n Read Buf Value: %x", readBuf);
	ಹಿಂತಿರುಗಿ readBuf;
}

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ()
{
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ i = 0;
	ಪೂರ್ಣಾಂಕ timeout;
	ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay = 500;
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ write_buf[7] = {0x00};
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ಉದ್ದಳತೆ_2 = 0;

	log_debug("\tI2C: MPU6050 - ACC test\n");


	i2c_init();

	ಆದರೆ(config_i2c(I2C, PRESCALER_ಎಣಿಕೆ, SCLK_ಎಣಿಕೆ))
	{
			log_error("\tSomething Wrong In Initialization\n");
			ಹಿಂತಿರುಗಿ -1;
	}
	ಇಲ್ಲದಿದ್ದರೆ
		log_info("\tIntilization Happened Fine\n");

		ಆದರೆ(DEV_ತಟಸ್ಥ == CheckForDeviceId(delay))
		{
			log_info("Device ID Check Success");
		}
		ಇಲ್ಲದಿದ್ದರೆ
		{
			log_error("Could not verify Device identity");
		}
		write_buf[0] = 1;
		write_mpu6050_ರಿಜಿಸ್ಟರ್(I2C, MPU6050_REG_PWR_MGMT, &write_buf[0],  delay);
		write_buf[0] = MPU6050_GYRO_SENS_500D;
		write_mpu6050_ರಿಜಿಸ್ಟರ್(I2C, MPU6050_REG_GYRO_CONFIG, &write_buf[0], delay);
		write_buf[0] = 0x01;
		write_mpu6050_ರಿಜಿಸ್ಟರ್(I2C, 0x1B, &write_buf[0], delay);
		write_buf[0] = 0x01;
		write_mpu6050_ರಿಜಿಸ್ಟರ್(I2C, 0x1C, &write_buf[0], delay);
		write_buf[0] = 0x01;
		write_mpu6050_ರಿಜಿಸ್ಟರ್(I2C, 0x6B, &write_buf[0], delay);


	log_debug("\n Entering While loop");
	ಆಗ(1)
	{
		measuring_ಮೌಲ್ಯ(delay);
		delay_loop(2000, 1000);
	}

	ಹಿಂತಿರುಗಿ 0;
}

