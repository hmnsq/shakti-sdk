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

#ضمن <stdint.h>//Includes the definitions of standard input/output functions//
#ضمن "i2c.h"
#ضمن "log.h"
#ضمن "uart.h"

#تعریف_کړه DELAY1 100
#تعریف_کړه DELAY2 50


#تعریف_کړه DELAY_ارزښت 900
#إذا 1
#تعریف_کړه PRESCALER_شمېر 24
#تعریف_کړه SCLK_شمېر 9
#وإلا
#تعریف_کړه PRESCALER_شمېر 8
#تعریف_کړه SCLK_شمېر 6
#د_که_پای
#تعریف_کړه I2C i2c_instance[1]
#تعریف_کړه RD_معلومات_CNT 14

#تعریف_کړه MPU6050_SLAVE_پته 0xD0
#تعریف_کړه MPU_6050_OUTPUT_BEGIN 0x3B
#تعریف_کړه MPU6050_DLPF_CFG 0x20
#تعریف_کړه MPU6050_SMPL_DIV 0x19
#تعریف_کړه MPU6050_پته   0x68
#تعریف_کړه DEV_بې_اغېزه_عنصر  0X68
#تعریف_کړه DEV_بې_اغېزه_عنصر_معلومات_REG 0X75
#تعریف_کړه MPU6050_REG_PWR_MGMT 0X6B
#تعریف_کړه MPU6050_RESET         0x80
#تعریف_کړه MPU6050_ACC_SENS_2G         0x00
#تعریف_کړه MPU6050_ACC_SENS_4G         0x08
#تعریف_کړه MPU6050_ACC_SENS_8G         0x10
#تعریف_کړه MPU6050_REG_GYRO_CONFIG      0x1B // Gyroscope Configuration
#تعریف_کړه MPU6050_REG_ACCEL_CONFIG     0x1C // Accelerometer Configuration
#تعریف_کړه MPU6050_GYRO_SENS_500D       0x08

#تعریف_کړه PI 3.141592654

حرف readbuf[RD_معلومات_CNT];
صحيح AccX,AccY,AccZ;
صحيح accAngleX, accAngleY, GyroAngleX, GyroAngleY, GyroAngleZ;
صحيح roll, pitch, yaw;
صحيح AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
صحيح AccErrorX,AccErrory;
صحيح GyroX, GyroY, GyroZ;
صحيح c = 0;
صحيح i=0;

صحيح read_mpu6050_ثبتوونکی(i2c_struct * i2c_instance, بینښه صحيح reg_دننه_واټن, بینښه حرف *read_معلومات_2, بینښه حرف اوږدتیا_2, بینښه اوږد delay)
{
	بینښه حرف read_buf[4] = {'\0'};
	صحيح i = 0, j = 0,  k = 0, حالت_2=0;
	بینښه حرف لنډمهاله = 0;

//Writes the slave address for write
	i2c_send_slave_پته(i2c_instance, MPU6050_SLAVE_پته, I2C_WRITE, 800);
//Writes the pointer to address that needs to be read
	i2c_write_معلومات(i2c_instance, reg_دننه_واټن, delay);
//Restarts the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_REPSTART;
	delay_loop(DELAY1, DELAY2);
//Writes the slave address for read
	i2c_write_معلومات(i2c_instance, MPU6050_SLAVE_پته | I2C_READ, delay);
/* Make a dummy read as per spec of the I2C controller */
	i2c_instance->control = I2C_NACK;
	i2c_read_معلومات(i2c_instance, &لنډمهاله, delay);
//	printf("\n Reading the data");

	i2c_read_معلومات_nack(i2c_instance, &لنډمهاله, delay);
	*read_معلومات_2 = لنډمهاله;
//	delay_loop(DELAY1, DELAY2);
	i2c_instance->control = I2C_STOP;
	delay_loop(DELAY1, DELAY2);
	أرجع 0;
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
صحيح read_mpu6050_registers(i2c_struct * i2c_instance, بینښه صحيح reg_دننه_واټن, بینښه حرف *read_لنډمهاله, بینښه حرف اوږدتیا_2, بینښه اوږد delay)
{
//	unsigned char read_buf[4] = {'\0'};
	صحيح i = 0, j = 0,  k = 0, حالت_2=0;
	بینښه حرف لنډمهاله = 0;

//Writes the slave address for write
	i2c_send_slave_پته(i2c_instance, MPU6050_SLAVE_پته, I2C_WRITE, delay);
//Writes the pointer to address that needs to be read
	i2c_write_معلومات(i2c_instance, reg_دننه_واټن, delay);
//	delay_loop(DELAY1, DELAY2);
//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_REPSTART;
	delay_loop(DELAY1, DELAY2);

//Writes the slave address for read
	i2c_write_معلومات(i2c_instance, MPU6050_SLAVE_پته + I2C_READ, delay);
//	i2c_send_slave_address(i2c_instance, MPU6050_SLAVE_ADDRESS, I2C_READ, delay);

/* Make a dummy read as per spec of the I2C controller */
	i2c_read_معلومات(i2c_instance, &لنډمهاله, delay);

//Reads the MSB Byte of temperature [D9 - D1]
	لكل(i = 0; i < اوږدتیا_2; i++)
	{
		إذا(i == (اوږدتیا_2 - 1) )
		{
			log_debug("\nSending nack");
			i2c_instance->control = I2C_NACK;
//			i2c_read_data_nack(i2c_instance, &temp, delay);
			i2c_read_معلومات(i2c_instance, &لنډمهاله, delay);
			اكسر;
			}
		وإلا
		{
			i2c_read_معلومات(i2c_instance, &لنډمهاله, delay);
		}
		log_debug("\n read data[%x]: %x", i, لنډمهاله);
		*read_لنډمهاله = لنډمهاله;
		*read_لنډمهاله++;
	}
	
	log_debug("\n Sending Stop condition");
	i2c_instance->control = I2C_STOP;
	أرجع 0;
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
صحيح write_mpu6050_ثبتوونکی(i2c_struct * i2c_instance, بینښه صحيح reg_دننه_واټن, بینښه صحيح *write_ارزښت, بینښه اوږد delay)
{
	i2c_instance->control = I2C_IDLE;
	delay_loop(DELAY1, DELAY2);
	i2c_send_slave_پته(i2c_instance, MPU6050_SLAVE_پته, I2C_WRITE, delay);
//	delay_loop(DELAY1, DELAY2);
	i2c_write_معلومات(i2c_instance, reg_دننه_واټن, delay);
//	delay_loop(DELAY1, DELAY2);
	log_debug("\n write value: %x", *write_ارزښت);
	i2c_write_معلومات(i2c_instance,  ( *write_ارزښت & 0xff), delay);
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
صحيح write_mpu6050_registers(i2c_struct * i2c_instance, بینښه صحيح reg_دننه_واټن, بینښه صحيح *write_ارزښت, بینښه حرف اوږدتیا_2, بینښه اوږد delay)
{
	صحيح i = 0, j = 0,  k = 0, حالت_2=0;
	بینښه صحيح لنډمهاله = 0;
	
	i2c_send_slave_پته(i2c_instance, MPU6050_SLAVE_پته, I2C_WRITE, delay);
	i2c_write_معلومات(i2c_instance, reg_دننه_واټن, delay);
	delay_loop(DELAY1, DELAY2);
	
	إذا(1 == اوږدتیا_2)
	{
		i2c_write_معلومات(i2c_instance,  ( *write_ارزښت	& 0xff), delay);
	}
	وإلا
	{
		لكل(i = 0; i < اوږدتیا_2; i++)
		{
			i2c_write_معلومات(i2c_instance, (*write_ارزښت++ & 0xff), delay);

		}
	}

//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;
	delay_loop(DELAY1, DELAY2);
	أرجع 0;
}

/*
   soft float library need to be added, if hardfloat not there
 */
فراغ measuring_ارزښت(بینښه اوږد delay)
{
	// read accelerometer data
	read_mpu6050_registers(I2C, MPU_6050_OUTPUT_BEGIN, readbuf, RD_معلومات_CNT, delay);
	چاپ_کړه("\n Read Buf: { ");
	لكل(i = 0; i < RD_معلومات_CNT; i++)
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


فراغ calculate_imu_error(بینښه اوږد delay)
{
	صحيح c=0;
	صحيح yaw;
	عائم accAngleX, accAngleY, GyroAngleX, GyroAngleY, GyroAngleZ;

	طالما(c<200)
	{
		measuring_ارزښت(delay);

		AccErrorX = AccErrorX + (atan(AccY / جذر(توان(AccX, 2)) + توان(AccZ, 2)))* 180 / PI;
		AccErrorY = AccErrorY + (atan(AccY / جذر(توان(AccX, 2)) + توان(AccZ, 2)))* 180 / PI;

		GyroErrorX = GyroErrorX + (GyroX / 65.5);
		GyroErrorY = GyroErrorY + (GyroY / 65.5);
		GyroErrorZ = GyroErrorZ + (GyroZ / 65.5);
		c++;
	}
	c=0;
	AccErrorX = AccErrorX / 200;
	AccErrorY = AccErrorY / 200;

	accAngleX = (atan(AccY / جذر(توان(AccX, 2) + توان(AccZ, 2))) * 180 / PI) - AccErrorX; // AccErrorX
	accAngleY = (atan(-1 * AccX / جذر(توان(AccY, 2) + توان(AccZ, 2))) * 180 / PI) - AccErrorY; // AccErrory
	// sum all reading
	GyroErrorX = GyroErrorX / 200;
	GyroErrorY = GyroErrorY / 200;
	GyroErrorZ = GyroErrorZ / 200;

	GyroX = GyroX - GyroErrorX ; // GyroErrorX
	GyroY = GyroY - GyroErrorY; // GyroErrorY
	GyroZ = GyroZ - GyroErrorZ; // GyroErrorZ
}

بینښه حرف CheckForDeviceId(بینښه اوږد delay)
{
	بینښه حرف readBuf = 0xFF;
	read_mpu6050_ثبتوونکی(I2C, DEV_بې_اغېزه_عنصر_معلومات_REG, &readBuf, 1, delay);
	log_debug("\n Read Buf Value: %x", readBuf);
	أرجع readBuf;
}

صحيح اصلي()
{
	بینښه حرف i = 0;
	صحيح timeout;
	بینښه اوږد delay = 500;
	بینښه صحيح write_buf[7] = {0x00};
	بینښه حرف اوږدتیا_2 = 0;

	log_debug("\tI2C: MPU6050 - ACC test\n");


	i2c_init();

	إذا(config_i2c(I2C, PRESCALER_شمېر, SCLK_شمېر))
	{
			log_error("\tSomething Wrong In Initialization\n");
			أرجع -1;
	}
	وإلا
		log_info("\tIntilization Happened Fine\n");

		إذا(DEV_بې_اغېزه_عنصر == CheckForDeviceId(delay))
		{
			log_info("Device ID Check Success");
		}
		وإلا
		{
			log_error("Could not verify Device identity");
		}
		write_buf[0] = 1;
		write_mpu6050_ثبتوونکی(I2C, MPU6050_REG_PWR_MGMT, &write_buf[0],  delay);
		write_buf[0] = MPU6050_GYRO_SENS_500D;
		write_mpu6050_ثبتوونکی(I2C, MPU6050_REG_GYRO_CONFIG, &write_buf[0], delay);
		write_buf[0] = 0x01;
		write_mpu6050_ثبتوونکی(I2C, 0x1B, &write_buf[0], delay);
		write_buf[0] = 0x01;
		write_mpu6050_ثبتوونکی(I2C, 0x1C, &write_buf[0], delay);
		write_buf[0] = 0x01;
		write_mpu6050_ثبتوونکی(I2C, 0x6B, &write_buf[0], delay);


	log_debug("\n Entering While loop");
	طالما(1)
	{
		measuring_ارزښت(delay);
		delay_loop(2000, 1000);
	}

	أرجع 0;
}

