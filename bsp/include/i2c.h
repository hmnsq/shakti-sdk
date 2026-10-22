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

#اگر_تعریف_نشده I2C_H
#تعریف_کن I2C_H

#ضمن "platform.h"

#تعریف_کن ETIMEOUT -60
#تعریف_کن DEF_TIMEOUT 60
#تعریف_کن ETIMEDOUT -80
#تعریف_کن ENXIO -82
#تعریف_کن EREMOTEIO -81

#تعریف_کن I2C_SUCCESS 0
#تعریف_کن EAXI_ERROR -1
#تعریف_کن EI2C_BUS_ERROR -2
#تعریف_کن EI2C_PIN_ERROR -3
#تعریف_کن EI2C_LRB_ERROR -4

#تعریف_کن I2C_PIN	0x80
#تعریف_کن I2C_ESO	0x40
#تعریف_کن I2C_ES1	0x20
#تعریف_کن I2C_ES2	0x10
#تعریف_کن I2C_ENI	0x08
#تعریف_کن I2C_STA	0x04
#تعریف_کن I2C_STO	0x02
#تعریف_کن I2C_ACK	0x01

#تعریف_کن I2C_INI 0x40   /* 1 if not initialized */
#تعریف_کن I2C_STS 0x20
#تعریف_کن I2C_BER 0x10
#تعریف_کن I2C_AD0 0x08
#تعریف_کن I2C_LRB 0x08
#تعریف_کن I2C_AAS 0x04
#تعریف_کن I2C_LAB 0x02
#تعریف_کن I2C_BB  0x01

#تعریف_کن I2_C_شروع         (I2C_PIN | I2C_ESO | I2C_STA | I2C_ACK)
#تعریف_کن I2_C_شروع_ENI     (I2C_PIN | I2C_ESO | I2C_STA | I2C_ACK | I2C_ENI)
#تعریف_کن I2C_STOP          (I2C_PIN | I2C_ESO | I2C_STO | I2C_ACK)
#تعریف_کن I2C_REPSTART      (                 I2C_ESO | I2C_STA | I2C_ACK)
#تعریف_کن I2C_REPSTART_ENI  (                 I2C_ESO | I2C_STA | I2C_ACK | I2C_ENI)
#تعریف_کن I2C_IDLE          (I2C_PIN | I2C_ESO                  | I2C_ACK)
#تعریف_کن I2C_NACK          (I2C_ESO  )
#تعریف_کن I2C_STOP_ENI          (I2C_PIN | I2C_ESO | I2C_STO | I2C_ACK | I2C_ENI)

#تعریف_کن I2C_READ 1
#تعریف_کن I2C_WRITE 0

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

بیعلامت حرف i2c_complete_flag;
بیعلامت صحيح i2c_read_مقدار;

/* Struct to access I2C registers as 32 bit registers */
تعريفنوع بنية
{
/* 0x00 */
	بیعلامت صحيح  prescale;     /*! Prescale Register */
	بیعلامت صحيح   prescale_rsvd;

/* 0x08 */
	بیعلامت صحيح   control;
	بیعلامت صحيح   control_rsvd;

/* 0x10 */
	بیعلامت صحيح  داده_2;	 /*! Prescale Register */
	بیعلامت صحيح   داده_rsvd;

/* 0x18 */
	بیعلامت صحيح  وضعیت_2;	 /*! Prescale Register */
	بیعلامت صحيح   وضعیت_rsvd;

/* 0x20 */
	بیعلامت صحيح  s01;	 /*! Prescale Register */
	بیعلامت صحيح   s01_rsvd;

/* 0x28 */
	بیعلامت صحيح  s3;	 /*! Prescale Register */
	بیعلامت صحيح   s3_rsvd;

/* 0x30 */
	بیعلامت صحيح  زمان;	 /*! Prescale Register */
	بیعلامت صحيح   زمان_rsvd;

/* 0x38 */
	بیعلامت صحيح  scl;	 /*! Prescale Register */
	بیعلامت صحيح   scl_rsvd;
} i2c_struct;

فراغ i2c_init(فراغ);
صحيح config_i2c(i2c_struct *,بیعلامت حرف prescale_div, بیعلامت حرف scl_div);
صحيح wait_till_I2c_bus_free(i2c_struct *);
صحيح wait_till_txrx_operation_Completes(i2c_struct *,صحيح *وضعیت_2);
صحيح sendbytes(i2c_struct *, ثابت حرف *buf, صحيح شمار, صحيح آخرین, صحيح eni);
صحيح readbytes(i2c_struct *,حرف *buf, صحيح شمار, صحيح آخرین);
صحيح i2c_send_slave_آدرس(i2c_struct *,بیعلامت حرف slave_آدرس, بیعلامت
			   حرف rdWrCntrl, بیعلامت دراز delay);
صحيح i2c_write_داده(i2c_struct *,بیعلامت حرف write_داده, بیعلامت حرف delay);
صحيح i2c_read_داده(i2c_struct *,بیعلامت حرف *read_داده_2, بیعلامت حرف delay);
صحيح i2c_send_وقفه_slave_آدرس(i2c_struct * instance, بیعلامت حرف
				     slave_آدرس, بیعلامت حرف rdWrCntrl,
				     بیعلامت دراز delay);
صحيح i2c_read_وقفه_داده(i2c_struct * instance, بیعلامت حرف *read_داده_2,
			    بیعلامت حرف delay, بیعلامت حرف آخرین);
صحيح i2c_write_وقفه_داده(i2c_struct * instance, بیعلامت حرف write_داده,
			     بیعلامت حرف delay, بیعلامت حرف آخرین);
صحيح i2c_read_داده_nack(i2c_struct * instance, بیعلامت حرف *read_داده_2, بیعلامت
		       حرف delay);

خارجي i2c_struct *i2c_instance[MAX_I2_C_شمار];

#پایان_اگر
