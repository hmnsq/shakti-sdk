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

#अन्तर्भाव <stdint.h>//Includes the definitions of standard input/output functions//
#अन्तर्भाव "i2c.h"
#अन्तर्भाव "log.h"
#अन्तर्भाव "uart.h"

#परिभाषय DELAY1 100
#परिभाषय DELAY2 50


#परिभाषय DELAY_मानम् 900
#यदि 1
#परिभाषय PRESCALER_गणनम् 24
#परिभाषय SCLK_गणनम् 9
#अन्यथा
#परिभाषय PRESCALER_गणनम् 8
#परिभाषय SCLK_गणनम् 6
#यदि_अन्तः
#परिभाषय I2C i2c_instance[1]
#परिभाषय RD_दत्त_CNT 14

#परिभाषय MPU6050_SLAVE_स्थानाङ्कः 0xD0
#परिभाषय MPU_6050_OUTPUT_BEGIN 0x3B
#परिभाषय MPU6050_DLPF_CFG 0x20
#परिभाषय MPU6050_SMPL_DIV 0x19
#परिभाषय MPU6050_स्थानाङ्कः   0x68
#परिभाषय DEV_तटस्थः  0X68
#परिभाषय DEV_तटस्थः_दत्त_REG 0X75
#परिभाषय MPU6050_REG_PWR_MGMT 0X6B
#परिभाषय MPU6050_RESET         0x80
#परिभाषय MPU6050_ACC_SENS_2G         0x00
#परिभाषय MPU6050_ACC_SENS_4G         0x08
#परिभाषय MPU6050_ACC_SENS_8G         0x10
#परिभाषय MPU6050_REG_GYRO_CONFIG      0x1B // Gyroscope Configuration
#परिभाषय MPU6050_REG_ACCEL_CONFIG     0x1C // Accelerometer Configuration
#परिभाषय MPU6050_GYRO_SENS_500D       0x08

#परिभाषय PI 3.141592654

वर्ण readbuf[RD_दत्त_CNT];
पूर्णाङ्क AccX,AccY,AccZ;
पूर्णाङ्क accAngleX, accAngleY, GyroAngleX, GyroAngleY, GyroAngleZ;
पूर्णाङ्क roll, pitch, yaw;
पूर्णाङ्क AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
पूर्णाङ्क AccErrorX,AccErrory;
पूर्णाङ्क GyroX, GyroY, GyroZ;
पूर्णाङ्क c = 0;
पूर्णाङ्क i=0;

पूर्णाङ्क read_mpu6050_पञ्जिकाकोशः(i2c_struct * i2c_instance, अचिह्नित पूर्णाङ्क reg_विस्थापनम्, अचिह्नित वर्ण *read_दत्त_2, अचिह्नित वर्ण दीर्घता_2, अचिह्नित दीर्घ delay)
{
	अचिह्नित वर्ण read_buf[4] = {'\0'};
	पूर्णाङ्क i = 0, j = 0,  k = 0, स्थितिः_2=0;
	अचिह्नित वर्ण अस्थायी = 0;

//Writes the slave address for write
	i2c_send_slave_स्थानाङ्कः(i2c_instance, MPU6050_SLAVE_स्थानाङ्कः, I2C_WRITE, 800);
//Writes the pointer to address that needs to be read
	i2c_write_दत्त(i2c_instance, reg_विस्थापनम्, delay);
//Restarts the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_REPSTART;
	delay_loop(DELAY1, DELAY2);
//Writes the slave address for read
	i2c_write_दत्त(i2c_instance, MPU6050_SLAVE_स्थानाङ्कः | I2C_READ, delay);
/* Make a dummy read as per spec of the I2C controller */
	i2c_instance->control = I2C_NACK;
	i2c_read_दत्त(i2c_instance, &अस्थायी, delay);
//	printf("\n Reading the data");

	i2c_read_दत्त_nack(i2c_instance, &अस्थायी, delay);
	*read_दत्त_2 = अस्थायी;
//	delay_loop(DELAY1, DELAY2);
	i2c_instance->control = I2C_STOP;
	delay_loop(DELAY1, DELAY2);
	प्रत्यागम 0;
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
पूर्णाङ्क read_mpu6050_registers(i2c_struct * i2c_instance, अचिह्नित पूर्णाङ्क reg_विस्थापनम्, अचिह्नित वर्ण *read_अस्थायी, अचिह्नित वर्ण दीर्घता_2, अचिह्नित दीर्घ delay)
{
//	unsigned char read_buf[4] = {'\0'};
	पूर्णाङ्क i = 0, j = 0,  k = 0, स्थितिः_2=0;
	अचिह्नित वर्ण अस्थायी = 0;

//Writes the slave address for write
	i2c_send_slave_स्थानाङ्कः(i2c_instance, MPU6050_SLAVE_स्थानाङ्कः, I2C_WRITE, delay);
//Writes the pointer to address that needs to be read
	i2c_write_दत्त(i2c_instance, reg_विस्थापनम्, delay);
//	delay_loop(DELAY1, DELAY2);
//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_REPSTART;
	delay_loop(DELAY1, DELAY2);

//Writes the slave address for read
	i2c_write_दत्त(i2c_instance, MPU6050_SLAVE_स्थानाङ्कः + I2C_READ, delay);
//	i2c_send_slave_address(i2c_instance, MPU6050_SLAVE_ADDRESS, I2C_READ, delay);

/* Make a dummy read as per spec of the I2C controller */
	i2c_read_दत्त(i2c_instance, &अस्थायी, delay);

//Reads the MSB Byte of temperature [D9 - D1]
	प्रति(i = 0; i < दीर्घता_2; i++)
	{
		यदि(i == (दीर्घता_2 - 1) )
		{
			log_debug("\nSending nack");
			i2c_instance->control = I2C_NACK;
//			i2c_read_data_nack(i2c_instance, &temp, delay);
			i2c_read_दत्त(i2c_instance, &अस्थायी, delay);
			भङ्ग;
			}
		अन्यथा
		{
			i2c_read_दत्त(i2c_instance, &अस्थायी, delay);
		}
		log_debug("\n read data[%x]: %x", i, अस्थायी);
		*read_अस्थायी = अस्थायी;
		*read_अस्थायी++;
	}
	
	log_debug("\n Sending Stop condition");
	i2c_instance->control = I2C_STOP;
	प्रत्यागम 0;
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
पूर्णाङ्क write_mpu6050_पञ्जिकाकोशः(i2c_struct * i2c_instance, अचिह्नित पूर्णाङ्क reg_विस्थापनम्, अचिह्नित पूर्णाङ्क *write_मानम्, अचिह्नित दीर्घ delay)
{
	i2c_instance->control = I2C_IDLE;
	delay_loop(DELAY1, DELAY2);
	i2c_send_slave_स्थानाङ्कः(i2c_instance, MPU6050_SLAVE_स्थानाङ्कः, I2C_WRITE, delay);
//	delay_loop(DELAY1, DELAY2);
	i2c_write_दत्त(i2c_instance, reg_विस्थापनम्, delay);
//	delay_loop(DELAY1, DELAY2);
	log_debug("\n write value: %x", *write_मानम्);
	i2c_write_दत्त(i2c_instance,  ( *write_मानम् & 0xff), delay);
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
पूर्णाङ्क write_mpu6050_registers(i2c_struct * i2c_instance, अचिह्नित पूर्णाङ्क reg_विस्थापनम्, अचिह्नित पूर्णाङ्क *write_मानम्, अचिह्नित वर्ण दीर्घता_2, अचिह्नित दीर्घ delay)
{
	पूर्णाङ्क i = 0, j = 0,  k = 0, स्थितिः_2=0;
	अचिह्नित पूर्णाङ्क अस्थायी = 0;
	
	i2c_send_slave_स्थानाङ्कः(i2c_instance, MPU6050_SLAVE_स्थानाङ्कः, I2C_WRITE, delay);
	i2c_write_दत्त(i2c_instance, reg_विस्थापनम्, delay);
	delay_loop(DELAY1, DELAY2);
	
	यदि(1 == दीर्घता_2)
	{
		i2c_write_दत्त(i2c_instance,  ( *write_मानम्	& 0xff), delay);
	}
	अन्यथा
	{
		प्रति(i = 0; i < दीर्घता_2; i++)
		{
			i2c_write_दत्त(i2c_instance, (*write_मानम्++ & 0xff), delay);

		}
	}

//Stops the I2C transaction to start reading the temperature value.
	i2c_instance->control = I2C_STOP;
	delay_loop(DELAY1, DELAY2);
	प्रत्यागम 0;
}

/*
   soft float library need to be added, if hardfloat not there
 */
शून्य measuring_मानम्(अचिह्नित दीर्घ delay)
{
	// read accelerometer data
	read_mpu6050_registers(I2C, MPU_6050_OUTPUT_BEGIN, readbuf, RD_दत्त_CNT, delay);
	प्रारूप_लिख("\n Read Buf: { ");
	प्रति(i = 0; i < RD_दत्त_CNT; i++)
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


शून्य calculate_imu_error(अचिह्नित दीर्घ delay)
{
	पूर्णाङ्क c=0;
	पूर्णाङ्क yaw;
	भिन्न accAngleX, accAngleY, GyroAngleX, GyroAngleY, GyroAngleZ;

	यावत्(c<200)
	{
		measuring_मानम्(delay);

		AccErrorX = AccErrorX + (atan(AccY / वर्गमूलम्(घातः(AccX, 2)) + घातः(AccZ, 2)))* 180 / PI;
		AccErrorY = AccErrorY + (atan(AccY / वर्गमूलम्(घातः(AccX, 2)) + घातः(AccZ, 2)))* 180 / PI;

		GyroErrorX = GyroErrorX + (GyroX / 65.5);
		GyroErrorY = GyroErrorY + (GyroY / 65.5);
		GyroErrorZ = GyroErrorZ + (GyroZ / 65.5);
		c++;
	}
	c=0;
	AccErrorX = AccErrorX / 200;
	AccErrorY = AccErrorY / 200;

	accAngleX = (atan(AccY / वर्गमूलम्(घातः(AccX, 2) + घातः(AccZ, 2))) * 180 / PI) - AccErrorX; // AccErrorX
	accAngleY = (atan(-1 * AccX / वर्गमूलम्(घातः(AccY, 2) + घातः(AccZ, 2))) * 180 / PI) - AccErrorY; // AccErrory
	// sum all reading
	GyroErrorX = GyroErrorX / 200;
	GyroErrorY = GyroErrorY / 200;
	GyroErrorZ = GyroErrorZ / 200;

	GyroX = GyroX - GyroErrorX ; // GyroErrorX
	GyroY = GyroY - GyroErrorY; // GyroErrorY
	GyroZ = GyroZ - GyroErrorZ; // GyroErrorZ
}

अचिह्नित वर्ण CheckForDeviceId(अचिह्नित दीर्घ delay)
{
	अचिह्नित वर्ण readBuf = 0xFF;
	read_mpu6050_पञ्जिकाकोशः(I2C, DEV_तटस्थः_दत्त_REG, &readBuf, 1, delay);
	log_debug("\n Read Buf Value: %x", readBuf);
	प्रत्यागम readBuf;
}

पूर्णाङ्क मुख्यम्()
{
	अचिह्नित वर्ण i = 0;
	पूर्णाङ्क timeout;
	अचिह्नित दीर्घ delay = 500;
	अचिह्नित पूर्णाङ्क write_buf[7] = {0x00};
	अचिह्नित वर्ण दीर्घता_2 = 0;

	log_debug("\tI2C: MPU6050 - ACC test\n");


	i2c_init();

	यदि(config_i2c(I2C, PRESCALER_गणनम्, SCLK_गणनम्))
	{
			log_error("\tSomething Wrong In Initialization\n");
			प्रत्यागम -1;
	}
	अन्यथा
		log_info("\tIntilization Happened Fine\n");

		यदि(DEV_तटस्थः == CheckForDeviceId(delay))
		{
			log_info("Device ID Check Success");
		}
		अन्यथा
		{
			log_error("Could not verify Device identity");
		}
		write_buf[0] = 1;
		write_mpu6050_पञ्जिकाकोशः(I2C, MPU6050_REG_PWR_MGMT, &write_buf[0],  delay);
		write_buf[0] = MPU6050_GYRO_SENS_500D;
		write_mpu6050_पञ्जिकाकोशः(I2C, MPU6050_REG_GYRO_CONFIG, &write_buf[0], delay);
		write_buf[0] = 0x01;
		write_mpu6050_पञ्जिकाकोशः(I2C, 0x1B, &write_buf[0], delay);
		write_buf[0] = 0x01;
		write_mpu6050_पञ्जिकाकोशः(I2C, 0x1C, &write_buf[0], delay);
		write_buf[0] = 0x01;
		write_mpu6050_पञ्जिकाकोशः(I2C, 0x6B, &write_buf[0], delay);


	log_debug("\n Entering While loop");
	यावत्(1)
	{
		measuring_मानम्(delay);
		delay_loop(2000, 1000);
	}

	प्रत्यागम 0;
}

