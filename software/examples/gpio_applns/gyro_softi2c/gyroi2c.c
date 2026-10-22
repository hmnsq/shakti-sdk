/***************************************************************************
 * Project           		: shakti devt board
 * Name of the file	     	: gyroi2c.c 
 * Brief Description of file    : Measurement of Coordinates x,y,z with the usage of i2c 
 * Name of Author    	        : Kotteeswaran
 * Email ID                     : kottee.1@gmail.com
 
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

******************************************************************************/
/**
@file gyroi2c.c
@brief Measurement of Coordinates x,y,z with the usage of i2c 
@detail 
*/ 

#अन्तर्भाव"gpio_i2c.h"

#परिभाषय I2C_WRITE 0
#परिभाषय I2C_READ 1

#परिभाषय MPU6050_SLAVE_स्थानाङ्कः      0xD0
#परिभाषय MPU_6050_OUTPUT_BEGIN      0x3B
#परिभाषय MPU6050_DLPF_CFG           0x20
#परिभाषय MPU6050_SMPL_DIV           0x19
#परिभाषय MPU6050_स्थानाङ्कः            0x68 
#परिभाषय DEV_तटस्थः               0X68
#परिभाषय DEV_तटस्थः_दत्त_REG      0X75
#परिभाषय MPU6050_REG_PWR_MGMT       0X6B
#परिभाषय MPU6050_RESET              0x80
#परिभाषय MPU6050_ACC_SENS_8G        0x10
#परिभाषय MPU6050_REG_GYRO_CONFIG    0x1B // Gyroscope Configuration
#परिभाषय MPU6050_REG_ACCEL_CONFIG   0x1C // Accelerometer Configuration
#परिभाषय MPU6050_GYRO_SENS_500D     0x08

#परिभाषय PI 3.141592654

वर्ण readbuf[20];
पूर्णाङ्क AccX,AccY,AccZ;
पूर्णाङ्क accAngleX, accAngleY, GyroAngleX, GyroAngleY, GyroAngleZ;
पूर्णाङ्क roll, pitch, yaw;
पूर्णाङ्क AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
पूर्णाङ्क AccErrorX,AccErrory;
पूर्णाङ्क GyroX, GyroY, GyroZ;
पूर्णाङ्क c = 0;
पूर्णाङ्क i=0;
स्थिर अचिह्नित वर्ण delay = 100;

//   soft float library need to be added, if hardfloat not there
 
 /** @fn void measuring value()
 * @brief  determines the x,y,z axes in terms of 16-bit
 * @details  In addition to measurements error adjustments is also made.  
 */
शून्य measuring_मानम्()
{
	// read accelerometer data
	I2c_Send_Slave_स्थानाङ्कः(MPU6050_SLAVE_स्थानाङ्कः, I2C_WRITE, delay);//selecting slave to be read
	I2c_Write_दत्त(MPU_6050_OUTPUT_BEGIN, delay);//selecting register to be read
	I2c_Send_Slave_स्थानाङ्कः(MPU6050_SLAVE_स्थानाङ्कः, I2C_READ, delay);
	I2c_shakti_readbytes(readbuf,14,1, delay);//to read the output values
	प्रारूप_लिख("helloworld inside measuring value\n");

	AccX = (readbuf[0]<<8 |readbuf[1]) / 4096; //16-bit X-axis data
	AccY = (readbuf[2]<<8 |readbuf[3]) / 4096; //16-bit Y-axis data
	AccZ = (readbuf[4]<<8 |readbuf[5]) / 4096; //16-bit Z-axis data

	GyroX = (readbuf[8]<<8 |readbuf[9]) / 65.5 ; 
	GyroY = (readbuf[10]<<8 |readbuf[11]) / 65.5; 
	GyroZ = (readbuf[12]<<8 |readbuf[13]) / 65.5;

	// Correct the outputs with the calculated error values
	GyroX = GyroX + GyroErrorX ;   // GyroErrorX
	GyroY = GyroY - GyroErrorY;    // GyroErrorY
	GyroZ = GyroZ + GyroErrorZ;    // GyroErrorZ
}

/** @fn int main()
 * @brief contains function calls for configuring different parameters.
 * @details determines whether the initalisation as well as verfication is done properly or not 
 * @return int
 */
पूर्णाङ्क मुख्यम्()
{
	I2cInit();//configuring data and clocks as output lines

	प्रारूप_लिख("MPU6050 i2c Init completed\n");

	यदि (DEV_तटस्थः == I2c_Read_byte(MPU6050_SLAVE_स्थानाङ्कः, DEV_तटस्थः_दत्त_REG, delay)){
		प्रारूप_लिख("DEVICE SUCCESFULLY VERIFIED");
	}
	अन्यथा{
		प्रारूप_लिख("something went wrong , device identity not verified");
	}
	//configuring power management register
	I2c_Write_byte(MPU6050_SLAVE_स्थानाङ्कः, MPU6050_REG_PWR_MGMT, MPU6050_RESET, delay);

	delay_loop(1000,1000);   // we can use waitfor() function also (delay time to reset the device and initialisations proper)

	//setting internal clock of MPU6050
	I2c_Write_byte(MPU6050_SLAVE_स्थानाङ्कः, MPU6050_REG_PWR_MGMT, 0x00, delay);

	// configuring accelerometer -set sensitivity scale factor +-8g
	I2c_Write_byte(MPU6050_SLAVE_स्थानाङ्कः, MPU6050_REG_ACCEL_CONFIG, MPU6050_ACC_SENS_8G, delay);

	// configuring gyroscope-set  sensitivity scale factor to +-500deg/sec
	I2c_Write_byte(MPU6050_SLAVE_स्थानाङ्कः, MPU6050_REG_GYRO_CONFIG, MPU6050_GYRO_SENS_500D, delay);

	// configuirng gyroscope output rate as 1khz
	I2c_Write_byte(MPU6050_SLAVE_स्थानाङ्कः, MPU6050_DLPF_CFG,0x01, delay);

	// configuring sample divider to 99(i.e sample rate= gyroscope output rate /(1+sample divider))
	I2c_Write_byte(MPU6050_SLAVE_स्थानाङ्कः, MPU6050_SMPL_DIV, 0x63, delay);//set sample rate to 10

	यावत् (1){
		measuring_मानम्();
		प्रारूप_लिख("AccErrorX: %d,AccErrMPU6050_SLAVE_ADDRESSorX");
		प्रारूप_लिख("AccErrorY: %d,AccErrorY");
		प्रारूप_लिख("GyroErrorX: %d,GyroErrorX");
		प्रारूप_लिख("GyroErrorY: %d,GyroErrorY");
		प्रारूप_लिख("GyroErrorZ %d,GyroErrorZ");
	}

	प्रत्यागम 0;
}

/** @fn void calculate_imu_error()
 * @brief 
 * @details 
 * @warning  
 */
शून्य calculate_imu_error()
{
	पूर्णाङ्क c = 0;
	पूर्णाङ्क yaw;
	भिन्न accAngleX, accAngleY, GyroAngleX, GyroAngleY, GyroAngleZ;

	यावत् (c < 200){
		measuring_मानम्();

		AccErrorX = AccErrorX + (atan(AccY / वर्गमूलम्(घातः(AccX, 2)) + घातः(AccZ, 2))) * 180 / PI;
		AccErrorY = AccErrorY + (atan(AccY / वर्गमूलम्(घातः(AccX, 2)) + घातः(AccZ, 2))) * 180 / PI;

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

	GyroX = GyroX - GyroErrorX ;     // GyroErrorX
	GyroY = GyroY - GyroErrorY;      // GyroErrorY
	GyroZ = GyroZ - GyroErrorZ;      // GyroErrorZ
}
