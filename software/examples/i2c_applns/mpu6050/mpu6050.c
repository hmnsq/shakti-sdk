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

#تعریف_کرو DELAY1 100
#تعریف_کرو DELAY2 50


#تعریف_کرو DELAY_قدر 900
#إذا 1
#تعریف_کرو PRESCALER_گنتی 24
#تعریف_کرو SCLK_گنتی 9
#وإلا
#تعریف_کرو PRESCALER_گنتی 8
#تعریف_کرو SCLK_گنتی 6
#جے_انت
#تعریف_کرو I2C i2c_instance[1]
#تعریف_کرو RD_انکڑے_CNT 14

#تعریف_کرو MPU6050_SLAVE_پتہ 0xD0
#تعریف_کرو MPU_6050_OUTPUT_BEGIN 0x3B
#تعریف_کرو MPU6050_DLPF_CFG 0x20
#تعریف_کرو MPU6050_SMPL_DIV 0x19
#تعریف_کرو MPU6050_پتہ   0x68
#تعریف_کرو DEV_پچھان_تت  0X68
#تعریف_کرو DEV_پچھان_تت_انکڑے_REG 0X75
#تعریف_کرو MPU6050_REG_PWR_MGMT 0X6B
#تعریف_کرو MPU6050_RESET         0x80
#تعریف_کرو MPU6050_ACC_SENS_2G         0x00
#تعریف_کرو MPU6050_ACC_SENS_4G         0x08
#تعریف_کرو MPU6050_ACC_SENS_8G         0x10
#تعریف_کرو MPU6050_REG_GYRO_CONFIG      0x1B // Gyroscope Configuration
#تعریف_کرو MPU6050_REG_ACCEL_CONFIG     0x1C // Accelerometer Configuration
#تعریف_کرو MPU6050_GYRO_SENS_500D       0x08

#تعریف_کرو PI 3.141592654

حرف readbuf[RD_انکڑے_CNT];
صحيح AccX,AccY,AccZ;
صحيح accAngleX, accAngleY, GyroAngleX, GyroAngleY, GyroAngleZ;
صحيح roll, pitch, yaw;
صحيح AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
صحيح AccErrorX,AccErrory;
صحيح GyroX, GyroY, GyroZ;
صحيح c = 0;
صحيح i=0;

صحيح read_mpu6050_رجسٹر(i2c_struct * i2c_instance, بنانشانی صحيح reg_وتھ, بنانشانی حرف *read_انکڑے_2, بنانشانی حرف لمائی_2, بنانشانی لما delay)
{
	بنانشانی حرف read_buf[4] = {'\0'};
	صحيح i = 0, j = 0,  k = 0, حالت_2=0;
	بنانشانی حرف عارضی = 0;

//Writes the slave address for write
	i2c_send_slave_پتہ(i2c_instance, MPU6050_SLAVE_پتہ, I2C_WRITE, 800);
//Writes the pointer to address that needs to be read
	i2c_write_انکڑے(i2c_instance, reg_وتھ, delay);
//Restarts the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_REPSTART;
	delay_loop(DELAY1, DELAY2);
//Writes the slave address for read
	i2c_write_انکڑے(i2c_instance, MPU6050_SLAVE_پتہ | I2C_READ, delay);
/* Make a dummy read as per spec of the I2C controller */
	i2c_instance->control = I2C_NACK;
	i2c_read_انکڑے(i2c_instance, &عارضی, delay);
//	printf("\n Reading the data");

	i2c_read_انکڑے_nack(i2c_instance, &عارضی, delay);
	*read_انکڑے_2 = عارضی;
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
صحيح read_mpu6050_registers(i2c_struct * i2c_instance, بنانشانی صحيح reg_وتھ, بنانشانی حرف *read_عارضی, بنانشانی حرف لمائی_2, بنانشانی لما delay)
{
//	unsigned char read_buf[4] = {'\0'};
	صحيح i = 0, j = 0,  k = 0, حالت_2=0;
	بنانشانی حرف عارضی = 0;

//Writes the slave address for write
	i2c_send_slave_پتہ(i2c_instance, MPU6050_SLAVE_پتہ, I2C_WRITE, delay);
//Writes the pointer to address that needs to be read
	i2c_write_انکڑے(i2c_instance, reg_وتھ, delay);
//	delay_loop(DELAY1, DELAY2);
//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_REPSTART;
	delay_loop(DELAY1, DELAY2);

//Writes the slave address for read
	i2c_write_انکڑے(i2c_instance, MPU6050_SLAVE_پتہ + I2C_READ, delay);
//	i2c_send_slave_address(i2c_instance, MPU6050_SLAVE_ADDRESS, I2C_READ, delay);

/* Make a dummy read as per spec of the I2C controller */
	i2c_read_انکڑے(i2c_instance, &عارضی, delay);

//Reads the MSB Byte of temperature [D9 - D1]
	لكل(i = 0; i < لمائی_2; i++)
	{
		إذا(i == (لمائی_2 - 1) )
		{
			log_debug("\nSending nack");
			i2c_instance->control = I2C_NACK;
//			i2c_read_data_nack(i2c_instance, &temp, delay);
			i2c_read_انکڑے(i2c_instance, &عارضی, delay);
			اكسر;
			}
		وإلا
		{
			i2c_read_انکڑے(i2c_instance, &عارضی, delay);
		}
		log_debug("\n read data[%x]: %x", i, عارضی);
		*read_عارضی = عارضی;
		*read_عارضی++;
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
صحيح write_mpu6050_رجسٹر(i2c_struct * i2c_instance, بنانشانی صحيح reg_وتھ, بنانشانی صحيح *write_قدر, بنانشانی لما delay)
{
	i2c_instance->control = I2C_IDLE;
	delay_loop(DELAY1, DELAY2);
	i2c_send_slave_پتہ(i2c_instance, MPU6050_SLAVE_پتہ, I2C_WRITE, delay);
//	delay_loop(DELAY1, DELAY2);
	i2c_write_انکڑے(i2c_instance, reg_وتھ, delay);
//	delay_loop(DELAY1, DELAY2);
	log_debug("\n write value: %x", *write_قدر);
	i2c_write_انکڑے(i2c_instance,  ( *write_قدر & 0xff), delay);
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
صحيح write_mpu6050_registers(i2c_struct * i2c_instance, بنانشانی صحيح reg_وتھ, بنانشانی صحيح *write_قدر, بنانشانی حرف لمائی_2, بنانشانی لما delay)
{
	صحيح i = 0, j = 0,  k = 0, حالت_2=0;
	بنانشانی صحيح عارضی = 0;
	
	i2c_send_slave_پتہ(i2c_instance, MPU6050_SLAVE_پتہ, I2C_WRITE, delay);
	i2c_write_انکڑے(i2c_instance, reg_وتھ, delay);
	delay_loop(DELAY1, DELAY2);
	
	إذا(1 == لمائی_2)
	{
		i2c_write_انکڑے(i2c_instance,  ( *write_قدر	& 0xff), delay);
	}
	وإلا
	{
		لكل(i = 0; i < لمائی_2; i++)
		{
			i2c_write_انکڑے(i2c_instance, (*write_قدر++ & 0xff), delay);

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
فراغ measuring_قدر(بنانشانی لما delay)
{
	// read accelerometer data
	read_mpu6050_registers(I2C, MPU_6050_OUTPUT_BEGIN, readbuf, RD_انکڑے_CNT, delay);
	لکھو("\n Read Buf: { ");
	لكل(i = 0; i < RD_انکڑے_CNT; i++)
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


فراغ calculate_imu_error(بنانشانی لما delay)
{
	صحيح c=0;
	صحيح yaw;
	عائم accAngleX, accAngleY, GyroAngleX, GyroAngleY, GyroAngleZ;

	طالما(c<200)
	{
		measuring_قدر(delay);

		AccErrorX = AccErrorX + (atan(AccY / جذر(قوت(AccX, 2)) + قوت(AccZ, 2)))* 180 / PI;
		AccErrorY = AccErrorY + (atan(AccY / جذر(قوت(AccX, 2)) + قوت(AccZ, 2)))* 180 / PI;

		GyroErrorX = GyroErrorX + (GyroX / 65.5);
		GyroErrorY = GyroErrorY + (GyroY / 65.5);
		GyroErrorZ = GyroErrorZ + (GyroZ / 65.5);
		c++;
	}
	c=0;
	AccErrorX = AccErrorX / 200;
	AccErrorY = AccErrorY / 200;

	accAngleX = (atan(AccY / جذر(قوت(AccX, 2) + قوت(AccZ, 2))) * 180 / PI) - AccErrorX; // AccErrorX
	accAngleY = (atan(-1 * AccX / جذر(قوت(AccY, 2) + قوت(AccZ, 2))) * 180 / PI) - AccErrorY; // AccErrory
	// sum all reading
	GyroErrorX = GyroErrorX / 200;
	GyroErrorY = GyroErrorY / 200;
	GyroErrorZ = GyroErrorZ / 200;

	GyroX = GyroX - GyroErrorX ; // GyroErrorX
	GyroY = GyroY - GyroErrorY; // GyroErrorY
	GyroZ = GyroZ - GyroErrorZ; // GyroErrorZ
}

بنانشانی حرف CheckForDeviceId(بنانشانی لما delay)
{
	بنانشانی حرف readBuf = 0xFF;
	read_mpu6050_رجسٹر(I2C, DEV_پچھان_تت_انکڑے_REG, &readBuf, 1, delay);
	log_debug("\n Read Buf Value: %x", readBuf);
	أرجع readBuf;
}

صحيح مکھ()
{
	بنانشانی حرف i = 0;
	صحيح timeout;
	بنانشانی لما delay = 500;
	بنانشانی صحيح write_buf[7] = {0x00};
	بنانشانی حرف لمائی_2 = 0;

	log_debug("\tI2C: MPU6050 - ACC test\n");


	i2c_init();

	إذا(config_i2c(I2C, PRESCALER_گنتی, SCLK_گنتی))
	{
			log_error("\tSomething Wrong In Initialization\n");
			أرجع -1;
	}
	وإلا
		log_info("\tIntilization Happened Fine\n");

		إذا(DEV_پچھان_تت == CheckForDeviceId(delay))
		{
			log_info("Device ID Check Success");
		}
		وإلا
		{
			log_error("Could not verify Device identity");
		}
		write_buf[0] = 1;
		write_mpu6050_رجسٹر(I2C, MPU6050_REG_PWR_MGMT, &write_buf[0],  delay);
		write_buf[0] = MPU6050_GYRO_SENS_500D;
		write_mpu6050_رجسٹر(I2C, MPU6050_REG_GYRO_CONFIG, &write_buf[0], delay);
		write_buf[0] = 0x01;
		write_mpu6050_رجسٹر(I2C, 0x1B, &write_buf[0], delay);
		write_buf[0] = 0x01;
		write_mpu6050_رجسٹر(I2C, 0x1C, &write_buf[0], delay);
		write_buf[0] = 0x01;
		write_mpu6050_رجسٹر(I2C, 0x6B, &write_buf[0], delay);


	log_debug("\n Entering While loop");
	طالما(1)
	{
		measuring_قدر(delay);
		delay_loop(2000, 1000);
	}

	أرجع 0;
}

