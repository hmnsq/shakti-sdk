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

#అన్తర్భావ <stdint.h>//Includes the definitions of standard input/output functions//
#అన్తర్భావ "i2c.h"
#అన్తర్భావ "log.h"
#అన్తర్భావ "uart.h"

#నిర్వచించు DELAY1 100
#నిర్వచించు DELAY2 50


#నిర్వచించు DELAY_విలువ 900
#ఒకవేళ 1
#నిర్వచించు PRESCALER_లెక్క 24
#నిర్వచించు SCLK_లెక్క 9
#లేకపోతే
#నిర్వచించు PRESCALER_లెక్క 8
#నిర్వచించు SCLK_లెక్క 6
#అయితే_ముగింపు
#నిర్వచించు I2C i2c_instance[1]
#నిర్వచించు RD_దత్తాంశం_CNT 14

#నిర్వచించు MPU6050_SLAVE_చిరునామా 0xD0
#నిర్వచించు MPU_6050_OUTPUT_BEGIN 0x3B
#నిర్వచించు MPU6050_DLPF_CFG 0x20
#నిర్వచించు MPU6050_SMPL_DIV 0x19
#నిర్వచించు MPU6050_చిరునామా   0x68
#నిర్వచించు DEV_తటస్థం  0X68
#నిర్వచించు DEV_తటస్థం_దత్తాంశం_REG 0X75
#నిర్వచించు MPU6050_REG_PWR_MGMT 0X6B
#నిర్వచించు MPU6050_RESET         0x80
#నిర్వచించు MPU6050_ACC_SENS_2G         0x00
#నిర్వచించు MPU6050_ACC_SENS_4G         0x08
#నిర్వచించు MPU6050_ACC_SENS_8G         0x10
#నిర్వచించు MPU6050_REG_GYRO_CONFIG      0x1B // Gyroscope Configuration
#నిర్వచించు MPU6050_REG_ACCEL_CONFIG     0x1C // Accelerometer Configuration
#నిర్వచించు MPU6050_GYRO_SENS_500D       0x08

#నిర్వచించు PI 3.141592654

అక్షరం readbuf[RD_దత్తాంశం_CNT];
పూర్ణాంకం AccX,AccY,AccZ;
పూర్ణాంకం accAngleX, accAngleY, GyroAngleX, GyroAngleY, GyroAngleZ;
పూర్ణాంకం roll, pitch, yaw;
పూర్ణాంకం AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
పూర్ణాంకం AccErrorX,AccErrory;
పూర్ణాంకం GyroX, GyroY, GyroZ;
పూర్ణాంకం c = 0;
పూర్ణాంకం i=0;

పూర్ణాంకం read_mpu6050_రిజిస్టరు(i2c_struct * i2c_instance, గుర్తులేని పూర్ణాంకం reg_స్థానభ్రంశం, గుర్తులేని అక్షరం *read_దత్తాంశం_2, గుర్తులేని అక్షరం నిడివి_2, గుర్తులేని దీర్ఘ delay)
{
	గుర్తులేని అక్షరం read_buf[4] = {'\0'};
	పూర్ణాంకం i = 0, j = 0,  k = 0, స్థితి_3=0;
	గుర్తులేని అక్షరం తాత్కాలిక = 0;

//Writes the slave address for write
	i2c_send_slave_చిరునామా(i2c_instance, MPU6050_SLAVE_చిరునామా, I2C_WRITE, 800);
//Writes the pointer to address that needs to be read
	i2c_write_దత్తాంశం(i2c_instance, reg_స్థానభ్రంశం, delay);
//Restarts the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_REPSTART;
	delay_loop(DELAY1, DELAY2);
//Writes the slave address for read
	i2c_write_దత్తాంశం(i2c_instance, MPU6050_SLAVE_చిరునామా | I2C_READ, delay);
/* Make a dummy read as per spec of the I2C controller */
	i2c_instance->control = I2C_NACK;
	i2c_read_దత్తాంశం(i2c_instance, &తాత్కాలిక, delay);
//	printf("\n Reading the data");

	i2c_read_దత్తాంశం_nack(i2c_instance, &తాత్కాలిక, delay);
	*read_దత్తాంశం_2 = తాత్కాలిక;
//	delay_loop(DELAY1, DELAY2);
	i2c_instance->control = I2C_STOP;
	delay_loop(DELAY1, DELAY2);
	తిరిగి 0;
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
పూర్ణాంకం read_mpu6050_registers(i2c_struct * i2c_instance, గుర్తులేని పూర్ణాంకం reg_స్థానభ్రంశం, గుర్తులేని అక్షరం *read_తాత్కాలిక, గుర్తులేని అక్షరం నిడివి_2, గుర్తులేని దీర్ఘ delay)
{
//	unsigned char read_buf[4] = {'\0'};
	పూర్ణాంకం i = 0, j = 0,  k = 0, స్థితి_3=0;
	గుర్తులేని అక్షరం తాత్కాలిక = 0;

//Writes the slave address for write
	i2c_send_slave_చిరునామా(i2c_instance, MPU6050_SLAVE_చిరునామా, I2C_WRITE, delay);
//Writes the pointer to address that needs to be read
	i2c_write_దత్తాంశం(i2c_instance, reg_స్థానభ్రంశం, delay);
//	delay_loop(DELAY1, DELAY2);
//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_REPSTART;
	delay_loop(DELAY1, DELAY2);

//Writes the slave address for read
	i2c_write_దత్తాంశం(i2c_instance, MPU6050_SLAVE_చిరునామా + I2C_READ, delay);
//	i2c_send_slave_address(i2c_instance, MPU6050_SLAVE_ADDRESS, I2C_READ, delay);

/* Make a dummy read as per spec of the I2C controller */
	i2c_read_దత్తాంశం(i2c_instance, &తాత్కాలిక, delay);

//Reads the MSB Byte of temperature [D9 - D1]
	కొరకు(i = 0; i < నిడివి_2; i++)
	{
		ఒకవేళ(i == (నిడివి_2 - 1) )
		{
			log_debug("\nSending nack");
			i2c_instance->control = I2C_NACK;
//			i2c_read_data_nack(i2c_instance, &temp, delay);
			i2c_read_దత్తాంశం(i2c_instance, &తాత్కాలిక, delay);
			ఆపు;
			}
		లేకపోతే
		{
			i2c_read_దత్తాంశం(i2c_instance, &తాత్కాలిక, delay);
		}
		log_debug("\n read data[%x]: %x", i, తాత్కాలిక);
		*read_తాత్కాలిక = తాత్కాలిక;
		*read_తాత్కాలిక++;
	}
	
	log_debug("\n Sending Stop condition");
	i2c_instance->control = I2C_STOP;
	తిరిగి 0;
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
పూర్ణాంకం write_mpu6050_రిజిస్టరు(i2c_struct * i2c_instance, గుర్తులేని పూర్ణాంకం reg_స్థానభ్రంశం, గుర్తులేని పూర్ణాంకం *write_విలువ, గుర్తులేని దీర్ఘ delay)
{
	i2c_instance->control = I2C_IDLE;
	delay_loop(DELAY1, DELAY2);
	i2c_send_slave_చిరునామా(i2c_instance, MPU6050_SLAVE_చిరునామా, I2C_WRITE, delay);
//	delay_loop(DELAY1, DELAY2);
	i2c_write_దత్తాంశం(i2c_instance, reg_స్థానభ్రంశం, delay);
//	delay_loop(DELAY1, DELAY2);
	log_debug("\n write value: %x", *write_విలువ);
	i2c_write_దత్తాంశం(i2c_instance,  ( *write_విలువ & 0xff), delay);
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
పూర్ణాంకం write_mpu6050_registers(i2c_struct * i2c_instance, గుర్తులేని పూర్ణాంకం reg_స్థానభ్రంశం, గుర్తులేని పూర్ణాంకం *write_విలువ, గుర్తులేని అక్షరం నిడివి_2, గుర్తులేని దీర్ఘ delay)
{
	పూర్ణాంకం i = 0, j = 0,  k = 0, స్థితి_3=0;
	గుర్తులేని పూర్ణాంకం తాత్కాలిక = 0;
	
	i2c_send_slave_చిరునామా(i2c_instance, MPU6050_SLAVE_చిరునామా, I2C_WRITE, delay);
	i2c_write_దత్తాంశం(i2c_instance, reg_స్థానభ్రంశం, delay);
	delay_loop(DELAY1, DELAY2);
	
	ఒకవేళ(1 == నిడివి_2)
	{
		i2c_write_దత్తాంశం(i2c_instance,  ( *write_విలువ	& 0xff), delay);
	}
	లేకపోతే
	{
		కొరకు(i = 0; i < నిడివి_2; i++)
		{
			i2c_write_దత్తాంశం(i2c_instance, (*write_విలువ++ & 0xff), delay);

		}
	}

//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;
	delay_loop(DELAY1, DELAY2);
	తిరిగి 0;
}

/*
   soft float library need to be added, if hardfloat not there
 */
శూన్య measuring_విలువ(గుర్తులేని దీర్ఘ delay)
{
	// read accelerometer data
	read_mpu6050_registers(I2C, MPU_6050_OUTPUT_BEGIN, readbuf, RD_దత్తాంశం_CNT, delay);
	రాయి("\n Read Buf: { ");
	కొరకు(i = 0; i < RD_దత్తాంశం_CNT; i++)
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


శూన్య calculate_imu_error(గుర్తులేని దీర్ఘ delay)
{
	పూర్ణాంకం c=0;
	పూర్ణాంకం yaw;
	దశాంశం accAngleX, accAngleY, GyroAngleX, GyroAngleY, GyroAngleZ;

	అయితే(c<200)
	{
		measuring_విలువ(delay);

		AccErrorX = AccErrorX + (atan(AccY / వర్గమూలం(ఘాతం(AccX, 2)) + ఘాతం(AccZ, 2)))* 180 / PI;
		AccErrorY = AccErrorY + (atan(AccY / వర్గమూలం(ఘాతం(AccX, 2)) + ఘాతం(AccZ, 2)))* 180 / PI;

		GyroErrorX = GyroErrorX + (GyroX / 65.5);
		GyroErrorY = GyroErrorY + (GyroY / 65.5);
		GyroErrorZ = GyroErrorZ + (GyroZ / 65.5);
		c++;
	}
	c=0;
	AccErrorX = AccErrorX / 200;
	AccErrorY = AccErrorY / 200;

	accAngleX = (atan(AccY / వర్గమూలం(ఘాతం(AccX, 2) + ఘాతం(AccZ, 2))) * 180 / PI) - AccErrorX; // AccErrorX
	accAngleY = (atan(-1 * AccX / వర్గమూలం(ఘాతం(AccY, 2) + ఘాతం(AccZ, 2))) * 180 / PI) - AccErrorY; // AccErrory
	// sum all reading
	GyroErrorX = GyroErrorX / 200;
	GyroErrorY = GyroErrorY / 200;
	GyroErrorZ = GyroErrorZ / 200;

	GyroX = GyroX - GyroErrorX ; // GyroErrorX
	GyroY = GyroY - GyroErrorY; // GyroErrorY
	GyroZ = GyroZ - GyroErrorZ; // GyroErrorZ
}

గుర్తులేని అక్షరం CheckForDeviceId(గుర్తులేని దీర్ఘ delay)
{
	గుర్తులేని అక్షరం readBuf = 0xFF;
	read_mpu6050_రిజిస్టరు(I2C, DEV_తటస్థం_దత్తాంశం_REG, &readBuf, 1, delay);
	log_debug("\n Read Buf Value: %x", readBuf);
	తిరిగి readBuf;
}

పూర్ణాంకం ప్రధాన()
{
	గుర్తులేని అక్షరం i = 0;
	పూర్ణాంకం timeout;
	గుర్తులేని దీర్ఘ delay = 500;
	గుర్తులేని పూర్ణాంకం write_buf[7] = {0x00};
	గుర్తులేని అక్షరం నిడివి_2 = 0;

	log_debug("\tI2C: MPU6050 - ACC test\n");


	i2c_init();

	ఒకవేళ(config_i2c(I2C, PRESCALER_లెక్క, SCLK_లెక్క))
	{
			log_error("\tSomething Wrong In Initialization\n");
			తిరిగి -1;
	}
	లేకపోతే
		log_info("\tIntilization Happened Fine\n");

		ఒకవేళ(DEV_తటస్థం == CheckForDeviceId(delay))
		{
			log_info("Device ID Check Success");
		}
		లేకపోతే
		{
			log_error("Could not verify Device identity");
		}
		write_buf[0] = 1;
		write_mpu6050_రిజిస్టరు(I2C, MPU6050_REG_PWR_MGMT, &write_buf[0],  delay);
		write_buf[0] = MPU6050_GYRO_SENS_500D;
		write_mpu6050_రిజిస్టరు(I2C, MPU6050_REG_GYRO_CONFIG, &write_buf[0], delay);
		write_buf[0] = 0x01;
		write_mpu6050_రిజిస్టరు(I2C, 0x1B, &write_buf[0], delay);
		write_buf[0] = 0x01;
		write_mpu6050_రిజిస్టరు(I2C, 0x1C, &write_buf[0], delay);
		write_buf[0] = 0x01;
		write_mpu6050_రిజిస్టరు(I2C, 0x6B, &write_buf[0], delay);


	log_debug("\n Entering While loop");
	అయితే(1)
	{
		measuring_విలువ(delay);
		delay_loop(2000, 1000);
	}

	తిరిగి 0;
}

