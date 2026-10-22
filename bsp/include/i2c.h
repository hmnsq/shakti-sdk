/**************************************************************************
 * Project           	         : shakti devt board
 * Name of the file	         : i2c.h
 * Brief Description of file     : header file for i2c
 * Name of Author    	         : Kotteeswaran 
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
*****************************************************************************/
/**
 * @file i2c.h
 * @brief  Header file for i2c
 * @detail this is the header file for i2c_driver.c
 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ I2C_H
#ವ್ಯಾಖ್ಯಾನಿಸು I2C_H

#ಅನ್ತರ್ಭಾವ "platform.h"

#ವ್ಯಾಖ್ಯಾನಿಸು ETIMEOUT -60
#ವ್ಯಾಖ್ಯಾನಿಸು DEF_TIMEOUT 60
#ವ್ಯಾಖ್ಯಾನಿಸು ETIMEDOUT -80
#ವ್ಯಾಖ್ಯಾನಿಸು ENXIO -82
#ವ್ಯಾಖ್ಯಾನಿಸು EREMOTEIO -81

#ವ್ಯಾಖ್ಯಾನಿಸು I2C_SUCCESS 0
#ವ್ಯಾಖ್ಯಾನಿಸು EAXI_ERROR -1
#ವ್ಯಾಖ್ಯಾನಿಸು EI2C_BUS_ERROR -2
#ವ್ಯಾಖ್ಯಾನಿಸು EI2C_PIN_ERROR -3
#ವ್ಯಾಖ್ಯಾನಿಸು EI2C_LRB_ERROR -4

#ವ್ಯಾಖ್ಯಾನಿಸು I2C_PIN	0x80
#ವ್ಯಾಖ್ಯಾನಿಸು I2C_ESO	0x40
#ವ್ಯಾಖ್ಯಾನಿಸು I2C_ES1	0x20
#ವ್ಯಾಖ್ಯಾನಿಸು I2C_ES2	0x10
#ವ್ಯಾಖ್ಯಾನಿಸು I2C_ENI	0x08
#ವ್ಯಾಖ್ಯಾನಿಸು I2C_STA	0x04
#ವ್ಯಾಖ್ಯಾನಿಸು I2C_STO	0x02
#ವ್ಯಾಖ್ಯಾನಿಸು I2C_ACK	0x01

#ವ್ಯಾಖ್ಯಾನಿಸು I2C_INI 0x40   /* 1 if not initialized */
#ವ್ಯಾಖ್ಯಾನಿಸು I2C_STS 0x20
#ವ್ಯಾಖ್ಯಾನಿಸು I2C_BER 0x10
#ವ್ಯಾಖ್ಯಾನಿಸು I2C_AD0 0x08
#ವ್ಯಾಖ್ಯಾನಿಸು I2C_LRB 0x08
#ವ್ಯಾಖ್ಯಾನಿಸು I2C_AAS 0x04
#ವ್ಯಾಖ್ಯಾನಿಸು I2C_LAB 0x02
#ವ್ಯಾಖ್ಯಾನಿಸು I2C_BB  0x01

#ವ್ಯಾಖ್ಯಾನಿಸು I2_C_ಆರಂಭ         (I2C_PIN | I2C_ESO | I2C_STA | I2C_ACK)
#ವ್ಯಾಖ್ಯಾನಿಸು I2_C_ಆರಂಭ_ENI     (I2C_PIN | I2C_ESO | I2C_STA | I2C_ACK | I2C_ENI)
#ವ್ಯಾಖ್ಯಾನಿಸು I2C_STOP          (I2C_PIN | I2C_ESO | I2C_STO | I2C_ACK)
#ವ್ಯಾಖ್ಯಾನಿಸು I2C_REPSTART      (                 I2C_ESO | I2C_STA | I2C_ACK)
#ವ್ಯಾಖ್ಯಾನಿಸು I2C_REPSTART_ENI  (                 I2C_ESO | I2C_STA | I2C_ACK | I2C_ENI)
#ವ್ಯಾಖ್ಯಾನಿಸು I2C_IDLE          (I2C_PIN | I2C_ESO                  | I2C_ACK)
#ವ್ಯಾಖ್ಯಾನಿಸು I2C_NACK          (I2C_ESO  )
#ವ್ಯಾಖ್ಯಾನಿಸು I2C_STOP_ENI          (I2C_PIN | I2C_ESO | I2C_STO | I2C_ACK | I2C_ENI)

#ವ್ಯಾಖ್ಯಾನಿಸು I2C_READ 1
#ವ್ಯಾಖ್ಯಾನಿಸು I2C_WRITE 0

/*
`define     S2             8'h00
`define     Control        8'h08
`define     S0             8'h10
`define     Status         8'h18
`define     S01            8'h20
`define     S3             8'h28
`define     Time           8'h30
`define     SCL            8'h38
*/

ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ i2c_complete_flag;
ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i2c_read_ಮೌಲ್ಯ;

/* Struct to access I2C registers as 32 bit registers */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
/* 0x00 */
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ  prescale;     /*! Prescale Register */
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ   prescale_rsvd;

/* 0x08 */
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ   control;
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ   control_rsvd;

/* 0x10 */
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ  ದತ್ತಾಂಶ_2;	 /*! Prescale Register */
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ   ದತ್ತಾಂಶ_rsvd;

/* 0x18 */
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ  ಸ್ಥಿತಿ_3;	 /*! Prescale Register */
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ   ಸ್ಥಿತಿ_rsvd;

/* 0x20 */
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ  s01;	 /*! Prescale Register */
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ   s01_rsvd;

/* 0x28 */
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ  s3;	 /*! Prescale Register */
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ   s3_rsvd;

/* 0x30 */
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ  ಸಮಯ;	 /*! Prescale Register */
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ   ಸಮಯ_rsvd;

/* 0x38 */
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ  scl;	 /*! Prescale Register */
	ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ   scl_rsvd;
} i2c_struct;

ಶೂನ್ಯ i2c_init(ಶೂನ್ಯ);
ಪೂರ್ಣಾಂಕ config_i2c(i2c_struct *,ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ prescale_div, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ scl_div);
ಪೂರ್ಣಾಂಕ wait_till_I2c_bus_free(i2c_struct *);
ಪೂರ್ಣಾಂಕ wait_till_txrx_operation_Completes(i2c_struct *,ಪೂರ್ಣಾಂಕ *ಸ್ಥಿತಿ_3);
ಪೂರ್ಣಾಂಕ sendbytes(i2c_struct *, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *buf, ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2, ಪೂರ್ಣಾಂಕ ಕೊನೆಯ, ಪೂರ್ಣಾಂಕ eni);
ಪೂರ್ಣಾಂಕ readbytes(i2c_struct *,ಅಕ್ಷರ *buf, ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2, ಪೂರ್ಣಾಂಕ ಕೊನೆಯ);
ಪೂರ್ಣಾಂಕ i2c_send_slave_ವಿಳಾಸ(i2c_struct *,ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ slave_ವಿಳಾಸ, ಚಿಹ್ನೆರಹಿತ
			   ಅಕ್ಷರ rdWrCntrl, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay);
ಪೂರ್ಣಾಂಕ i2c_write_ದತ್ತಾಂಶ(i2c_struct *,ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ write_ದತ್ತಾಂಶ, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay);
ಪೂರ್ಣಾಂಕ i2c_read_ದತ್ತಾಂಶ(i2c_struct *,ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *read_ದತ್ತಾಂಶ_2, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay);
ಪೂರ್ಣಾಂಕ i2c_send_ಅಡಚಣೆ_slave_ವಿಳಾಸ(i2c_struct * instance, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ
				     slave_ವಿಳಾಸ, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ rdWrCntrl,
				     ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ delay);
ಪೂರ್ಣಾಂಕ i2c_read_ಅಡಚಣೆ_ದತ್ತಾಂಶ(i2c_struct * instance, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *read_ದತ್ತಾಂಶ_2,
			    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ಕೊನೆಯ);
ಪೂರ್ಣಾಂಕ i2c_write_ಅಡಚಣೆ_ದತ್ತಾಂಶ(i2c_struct * instance, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ write_ದತ್ತಾಂಶ,
			     ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ delay, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ಕೊನೆಯ);
ಪೂರ್ಣಾಂಕ i2c_read_ದತ್ತಾಂಶ_nack(i2c_struct * instance, ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *read_ದತ್ತಾಂಶ_2, ಚಿಹ್ನೆರಹಿತ
		       ಅಕ್ಷರ delay);

ಬಾಹ್ಯ i2c_struct *i2c_instance[MAX_I2_C_ಎಣಿಕೆ];

#ಆದರೆ_ಅಂತ್ಯ
