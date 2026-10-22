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

#समावेश"gpio_i2c.h"

#घोषणा I2C_WRITE 0
#घोषणा I2C_READ 1

#घोषणा MPU6050_SLAVE_ADDRESS      0xD0
#घोषणा MPU_6050_OUTPUT_BEGIN      0x3B
#घोषणा MPU6050_DLPF_CFG           0x20
#घोषणा MPU6050_SMPL_DIV           0x19
#घोषणा MPU6050_ADDRESS            0x68 
#घोषणा DEV_IDENTITY               0X68
#घोषणा DEV_IDENTITY_तथ्य_REG      0X75
#घोषणा MPU6050_REG_PWR_MGMT       0X6B
#घोषणा MPU6050_RESET              0x80
#घोषणा MPU6050_ACC_SENS_8G        0x10
#घोषणा MPU6050_REG_GYRO_CONFIG    0x1B // Gyroscope Configuration
#घोषणा MPU6050_REG_ACCEL_CONFIG   0x1C // Accelerometer Configuration
#घोषणा MPU6050_GYRO_SENS_500D     0x08

#घोषणा PI 3.141592654

अक्षर readbuf[20];
पूर्णांक AccX,AccY,AccZ;
पूर्णांक accAngleX, accAngleY, GyroAngleX, GyroAngleY, GyroAngleZ;
पूर्णांक roll, pitch, yaw;
पूर्णांक AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
पूर्णांक AccErrorX,AccErrory;
पूर्णांक GyroX, GyroY, GyroZ;
पूर्णांक c = 0;
पूर्णांक i=0;
अटल अचिन्हित अक्षर delay = 100;

//   soft float library need to be added, if hardfloat not there
 
 /** @fn void measuring value()
 * @brief  determines the x,y,z axes in terms of 16-bit
 * @details  In addition to measurements error adjustments is also made.  
 */
व्योम measuring_मूल्य()
{
	// read accelerometer data
	I2cSendSlaveAddress(MPU6050_SLAVE_ADDRESS, I2C_WRITE, delay);//selecting slave to be read
	I2c_Write_तथ्य(MPU_6050_OUTPUT_BEGIN, delay);//selecting register to be read
	I2cSendSlaveAddress(MPU6050_SLAVE_ADDRESS, I2C_READ, delay);
	I2c_shakti_readbytes(readbuf,14,1, delay);//to read the output values
	म_लिखो("helloworld inside measuring value\n");

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
पूर्णांक मुख्य()
{
	I2cInit();//configuring data and clocks as output lines

	म_लिखो("MPU6050 i2c Init completed\n");

	अगर (DEV_IDENTITY == I2c_Read_byte(MPU6050_SLAVE_ADDRESS, DEV_IDENTITY_तथ्य_REG, delay)){
		म_लिखो("DEVICE SUCCESFULLY VERIFIED");
	}
	अन्यथा{
		म_लिखो("something went wrong , device identity not verified");
	}
	//configuring power management register
	I2c_Write_byte(MPU6050_SLAVE_ADDRESS, MPU6050_REG_PWR_MGMT, MPU6050_RESET, delay);

	delay_loop(1000,1000);   // we can use waitfor() function also (delay time to reset the device and initialisations proper)

	//setting internal clock of MPU6050
	I2c_Write_byte(MPU6050_SLAVE_ADDRESS, MPU6050_REG_PWR_MGMT, 0x00, delay);

	// configuring accelerometer -set sensitivity scale factor +-8g
	I2c_Write_byte(MPU6050_SLAVE_ADDRESS, MPU6050_REG_ACCEL_CONFIG, MPU6050_ACC_SENS_8G, delay);

	// configuring gyroscope-set  sensitivity scale factor to +-500deg/sec
	I2c_Write_byte(MPU6050_SLAVE_ADDRESS, MPU6050_REG_GYRO_CONFIG, MPU6050_GYRO_SENS_500D, delay);

	// configuirng gyroscope output rate as 1khz
	I2c_Write_byte(MPU6050_SLAVE_ADDRESS, MPU6050_DLPF_CFG,0x01, delay);

	// configuring sample divider to 99(i.e sample rate= gyroscope output rate /(1+sample divider))
	I2c_Write_byte(MPU6050_SLAVE_ADDRESS, MPU6050_SMPL_DIV, 0x63, delay);//set sample rate to 10

	जबतक (1){
		measuring_मूल्य();
		म_लिखो("AccErrorX: %d,AccErrMPU6050_SLAVE_ADDRESSorX");
		म_लिखो("AccErrorY: %d,AccErrorY");
		म_लिखो("GyroErrorX: %d,GyroErrorX");
		म_लिखो("GyroErrorY: %d,GyroErrorY");
		म_लिखो("GyroErrorZ %d,GyroErrorZ");
	}

	वापस 0;
}

/** @fn void calculate_imu_error()
 * @brief 
 * @details 
 * @warning  
 */
व्योम calculate_imu_error()
{
	पूर्णांक c = 0;
	पूर्णांक yaw;
	भग्न accAngleX, accAngleY, GyroAngleX, GyroAngleY, GyroAngleZ;

	जबतक (c < 200){
		measuring_मूल्य();

		AccErrorX = AccErrorX + (atan(AccY / वर्ग_मूल(घात(AccX, 2)) + घात(AccZ, 2))) * 180 / PI;
		AccErrorY = AccErrorY + (atan(AccY / वर्ग_मूल(घात(AccX, 2)) + घात(AccZ, 2))) * 180 / PI;

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

	GyroX = GyroX - GyroErrorX ;     // GyroErrorX
	GyroY = GyroY - GyroErrorY;      // GyroErrorY
	GyroZ = GyroZ - GyroErrorZ;      // GyroErrorZ
}
