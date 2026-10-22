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

#جيڪڏهن_وصف_نه_ٿيل I2C_H
#وصف_ڪريو I2C_H

#ضمن "platform.h"

#وصف_ڪريو ETIMEOUT -60
#وصف_ڪريو DEF_TIMEOUT 60
#وصف_ڪريو ETIMEDOUT -80
#وصف_ڪريو ENXIO -82
#وصف_ڪريو EREMOTEIO -81

#وصف_ڪريو I2C_SUCCESS 0
#وصف_ڪريو EAXI_ERROR -1
#وصف_ڪريو EI2C_BUS_ERROR -2
#وصف_ڪريو EI2C_PIN_ERROR -3
#وصف_ڪريو EI2C_LRB_ERROR -4

#وصف_ڪريو I2C_PIN	0x80
#وصف_ڪريو I2C_ESO	0x40
#وصف_ڪريو I2C_ES1	0x20
#وصف_ڪريو I2C_ES2	0x10
#وصف_ڪريو I2C_ENI	0x08
#وصف_ڪريو I2C_STA	0x04
#وصف_ڪريو I2C_STO	0x02
#وصف_ڪريو I2C_ACK	0x01

#وصف_ڪريو I2C_INI 0x40   /* 1 if not initialized */
#وصف_ڪريو I2C_STS 0x20
#وصف_ڪريو I2C_BER 0x10
#وصف_ڪريو I2C_AD0 0x08
#وصف_ڪريو I2C_LRB 0x08
#وصف_ڪريو I2C_AAS 0x04
#وصف_ڪريو I2C_LAB 0x02
#وصف_ڪريو I2C_BB  0x01

#وصف_ڪريو I2_C_شروعات         (I2C_PIN | I2C_ESO | I2C_STA | I2C_ACK)
#وصف_ڪريو I2_C_شروعات_ENI     (I2C_PIN | I2C_ESO | I2C_STA | I2C_ACK | I2C_ENI)
#وصف_ڪريو I2C_STOP          (I2C_PIN | I2C_ESO | I2C_STO | I2C_ACK)
#وصف_ڪريو I2C_REPSTART      (                 I2C_ESO | I2C_STA | I2C_ACK)
#وصف_ڪريو I2C_REPSTART_ENI  (                 I2C_ESO | I2C_STA | I2C_ACK | I2C_ENI)
#وصف_ڪريو I2C_IDLE          (I2C_PIN | I2C_ESO                  | I2C_ACK)
#وصف_ڪريو I2C_NACK          (I2C_ESO  )
#وصف_ڪريو I2C_STOP_ENI          (I2C_PIN | I2C_ESO | I2C_STO | I2C_ACK | I2C_ENI)

#وصف_ڪريو I2C_READ 1
#وصف_ڪريو I2C_WRITE 0

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

بنانشان حرف i2c_complete_flag;
بنانشان صحيح i2c_read_قدر;

/* Struct to access I2C registers as 32 bit registers */
تعريفنوع بنية
{
/* 0x00 */
	بنانشان صحيح  prescale;     /*! Prescale Register */
	بنانشان صحيح   prescale_rsvd;

/* 0x08 */
	بنانشان صحيح   control;
	بنانشان صحيح   control_rsvd;

/* 0x10 */
	بنانشان صحيح  معلومات_2;	 /*! Prescale Register */
	بنانشان صحيح   معلومات_rsvd;

/* 0x18 */
	بنانشان صحيح  حالت_2;	 /*! Prescale Register */
	بنانشان صحيح   حالت_rsvd;

/* 0x20 */
	بنانشان صحيح  s01;	 /*! Prescale Register */
	بنانشان صحيح   s01_rsvd;

/* 0x28 */
	بنانشان صحيح  s3;	 /*! Prescale Register */
	بنانشان صحيح   s3_rsvd;

/* 0x30 */
	بنانشان صحيح  وقت;	 /*! Prescale Register */
	بنانشان صحيح   وقت_rsvd;

/* 0x38 */
	بنانشان صحيح  scl;	 /*! Prescale Register */
	بنانشان صحيح   scl_rsvd;
} i2c_struct;

فراغ i2c_init(فراغ);
صحيح config_i2c(i2c_struct *,بنانشان حرف prescale_div, بنانشان حرف scl_div);
صحيح wait_till_I2c_bus_free(i2c_struct *);
صحيح wait_till_txrx_operation_Completes(i2c_struct *,صحيح *حالت_2);
صحيح sendbytes(i2c_struct *, ثابت حرف *buf, صحيح ڳڻپ, صحيح آخري, صحيح eni);
صحيح readbytes(i2c_struct *,حرف *buf, صحيح ڳڻپ, صحيح آخري);
صحيح i2c_send_slave_پتو(i2c_struct *,بنانشان حرف slave_پتو, بنانشان
			   حرف rdWrCntrl, بنانشان ڊگهو delay);
صحيح i2c_write_معلومات(i2c_struct *,بنانشان حرف write_معلومات, بنانشان حرف delay);
صحيح i2c_read_معلومات(i2c_struct *,بنانشان حرف *read_معلومات_2, بنانشان حرف delay);
صحيح i2c_send_مداخلت_slave_پتو(i2c_struct * instance, بنانشان حرف
				     slave_پتو, بنانشان حرف rdWrCntrl,
				     بنانشان ڊگهو delay);
صحيح i2c_read_مداخلت_معلومات(i2c_struct * instance, بنانشان حرف *read_معلومات_2,
			    بنانشان حرف delay, بنانشان حرف آخري);
صحيح i2c_write_مداخلت_معلومات(i2c_struct * instance, بنانشان حرف write_معلومات,
			     بنانشان حرف delay, بنانشان حرف آخري);
صحيح i2c_read_معلومات_nack(i2c_struct * instance, بنانشان حرف *read_معلومات_2, بنانشان
		       حرف delay);

خارجي i2c_struct *i2c_instance[MAX_I2_C_ڳڻپ];

#جيڪڏهن_پورو
