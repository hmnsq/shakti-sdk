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

#ضمن"gpio_i2c.h"

#تعریف_کن I2C_WRITE 0
#تعریف_کن I2C_READ 1

#تعریف_کن MPU6050_SLAVE_آدرس      0xD0
#تعریف_کن MPU_6050_OUTPUT_BEGIN      0x3B
#تعریف_کن MPU6050_DLPF_CFG           0x20
#تعریف_کن MPU6050_SMPL_DIV           0x19
#تعریف_کن MPU6050_آدرس            0x68 
#تعریف_کن DEV_عنصر_خنثی               0X68
#تعریف_کن DEV_عنصر_خنثی_داده_REG      0X75
#تعریف_کن MPU6050_REG_PWR_MGMT       0X6B
#تعریف_کن MPU6050_RESET              0x80
#تعریف_کن MPU6050_ACC_SENS_8G        0x10
#تعریف_کن MPU6050_REG_GYRO_CONFIG    0x1B // Gyroscope Configuration
#تعریف_کن MPU6050_REG_ACCEL_CONFIG   0x1C // Accelerometer Configuration
#تعریف_کن MPU6050_GYRO_SENS_500D     0x08

#تعریف_کن PI 3.141592654

حرف readbuf[20];
صحيح AccX,AccY,AccZ;
صحيح accAngleX, accAngleY, GyroAngleX, GyroAngleY, GyroAngleZ;
صحيح roll, pitch, yaw;
صحيح AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
صحيح AccErrorX,AccErrory;
صحيح GyroX, GyroY, GyroZ;
صحيح c = 0;
صحيح i=0;
ساكن بیعلامت حرف delay = 100;

//   soft float library need to be added, if hardfloat not there
 
 /** @fn void measuring value()
 * @brief  determines the x,y,z axes in terms of 16-bit
 * @details  In addition to measurements error adjustments is also made.  
 */
فراغ measuring_مقدار()
{
	// read accelerometer data
	I2c_Send_Slave_آدرس(MPU6050_SLAVE_آدرس, I2C_WRITE, delay);//selecting slave to be read
	I2c_Write_داده(MPU_6050_OUTPUT_BEGIN, delay);//selecting register to be read
	I2c_Send_Slave_آدرس(MPU6050_SLAVE_آدرس, I2C_READ, delay);
	I2c_shakti_readbytes(readbuf,14,1, delay);//to read the output values
	چاپ_کن("helloworld inside measuring value\n");

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
صحيح اصلی()
{
	I2cInit();//configuring data and clocks as output lines

	چاپ_کن("MPU6050 i2c Init completed\n");

	إذا (DEV_عنصر_خنثی == I2c_Read_byte(MPU6050_SLAVE_آدرس, DEV_عنصر_خنثی_داده_REG, delay)){
		چاپ_کن("DEVICE SUCCESFULLY VERIFIED");
	}
	وإلا{
		چاپ_کن("something went wrong , device identity not verified");
	}
	//configuring power management register
	I2c_Write_byte(MPU6050_SLAVE_آدرس, MPU6050_REG_PWR_MGMT, MPU6050_RESET, delay);

	delay_loop(1000,1000);   // we can use waitfor() function also (delay time to reset the device and initialisations proper)

	//setting internal clock of MPU6050
	I2c_Write_byte(MPU6050_SLAVE_آدرس, MPU6050_REG_PWR_MGMT, 0x00, delay);

	// configuring accelerometer -set sensitivity scale factor +-8g
	I2c_Write_byte(MPU6050_SLAVE_آدرس, MPU6050_REG_ACCEL_CONFIG, MPU6050_ACC_SENS_8G, delay);

	// configuring gyroscope-set  sensitivity scale factor to +-500deg/sec
	I2c_Write_byte(MPU6050_SLAVE_آدرس, MPU6050_REG_GYRO_CONFIG, MPU6050_GYRO_SENS_500D, delay);

	// configuirng gyroscope output rate as 1khz
	I2c_Write_byte(MPU6050_SLAVE_آدرس, MPU6050_DLPF_CFG,0x01, delay);

	// configuring sample divider to 99(i.e sample rate= gyroscope output rate /(1+sample divider))
	I2c_Write_byte(MPU6050_SLAVE_آدرس, MPU6050_SMPL_DIV, 0x63, delay);//set sample rate to 10

	طالما (1){
		measuring_مقدار();
		چاپ_کن("AccErrorX: %d,AccErrMPU6050_SLAVE_ADDRESSorX");
		چاپ_کن("AccErrorY: %d,AccErrorY");
		چاپ_کن("GyroErrorX: %d,GyroErrorX");
		چاپ_کن("GyroErrorY: %d,GyroErrorY");
		چاپ_کن("GyroErrorZ %d,GyroErrorZ");
	}

	أرجع 0;
}

/** @fn void calculate_imu_error()
 * @brief 
 * @details 
 * @warning  
 */
فراغ calculate_imu_error()
{
	صحيح c = 0;
	صحيح yaw;
	عائم accAngleX, accAngleY, GyroAngleX, GyroAngleY, GyroAngleZ;

	طالما (c < 200){
		measuring_مقدار();

		AccErrorX = AccErrorX + (atan(AccY / جذر(توان(AccX, 2)) + توان(AccZ, 2))) * 180 / PI;
		AccErrorY = AccErrorY + (atan(AccY / جذر(توان(AccX, 2)) + توان(AccZ, 2))) * 180 / PI;

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

	GyroX = GyroX - GyroErrorX ;     // GyroErrorX
	GyroY = GyroY - GyroErrorY;      // GyroErrorY
	GyroZ = GyroZ - GyroErrorZ;      // GyroErrorZ
}
