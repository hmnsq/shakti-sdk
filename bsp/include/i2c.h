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

#جے_بنا_تعریف I2C_H
#تعریف_کرو I2C_H

#ضمن "platform.h"

#تعریف_کرو ETIMEOUT -60
#تعریف_کرو DEF_TIMEOUT 60
#تعریف_کرو ETIMEDOUT -80
#تعریف_کرو ENXIO -82
#تعریف_کرو EREMOTEIO -81

#تعریف_کرو I2C_SUCCESS 0
#تعریف_کرو EAXI_ERROR -1
#تعریف_کرو EI2C_BUS_ERROR -2
#تعریف_کرو EI2C_PIN_ERROR -3
#تعریف_کرو EI2C_LRB_ERROR -4

#تعریف_کرو I2C_PIN	0x80
#تعریف_کرو I2C_ESO	0x40
#تعریف_کرو I2C_ES1	0x20
#تعریف_کرو I2C_ES2	0x10
#تعریف_کرو I2C_ENI	0x08
#تعریف_کرو I2C_STA	0x04
#تعریف_کرو I2C_STO	0x02
#تعریف_کرو I2C_ACK	0x01

#تعریف_کرو I2C_INI 0x40   /* 1 if not initialized */
#تعریف_کرو I2C_STS 0x20
#تعریف_کرو I2C_BER 0x10
#تعریف_کرو I2C_AD0 0x08
#تعریف_کرو I2C_LRB 0x08
#تعریف_کرو I2C_AAS 0x04
#تعریف_کرو I2C_LAB 0x02
#تعریف_کرو I2C_BB  0x01

#تعریف_کرو I2_C_شروع         (I2C_PIN | I2C_ESO | I2C_STA | I2C_ACK)
#تعریف_کرو I2_C_شروع_ENI     (I2C_PIN | I2C_ESO | I2C_STA | I2C_ACK | I2C_ENI)
#تعریف_کرو I2C_STOP          (I2C_PIN | I2C_ESO | I2C_STO | I2C_ACK)
#تعریف_کرو I2C_REPSTART      (                 I2C_ESO | I2C_STA | I2C_ACK)
#تعریف_کرو I2C_REPSTART_ENI  (                 I2C_ESO | I2C_STA | I2C_ACK | I2C_ENI)
#تعریف_کرو I2C_IDLE          (I2C_PIN | I2C_ESO                  | I2C_ACK)
#تعریف_کرو I2C_NACK          (I2C_ESO  )
#تعریف_کرو I2C_STOP_ENI          (I2C_PIN | I2C_ESO | I2C_STO | I2C_ACK | I2C_ENI)

#تعریف_کرو I2C_READ 1
#تعریف_کرو I2C_WRITE 0

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

بنانشانی حرف i2c_complete_flag;
بنانشانی صحيح i2c_read_قدر;

/* Struct to access I2C registers as 32 bit registers */
تعريفنوع بنية
{
/* 0x00 */
	بنانشانی صحيح  prescale;     /*! Prescale Register */
	بنانشانی صحيح   prescale_rsvd;

/* 0x08 */
	بنانشانی صحيح   control;
	بنانشانی صحيح   control_rsvd;

/* 0x10 */
	بنانشانی صحيح  انکڑے_2;	 /*! Prescale Register */
	بنانشانی صحيح   انکڑے_rsvd;

/* 0x18 */
	بنانشانی صحيح  حالت_2;	 /*! Prescale Register */
	بنانشانی صحيح   حالت_rsvd;

/* 0x20 */
	بنانشانی صحيح  s01;	 /*! Prescale Register */
	بنانشانی صحيح   s01_rsvd;

/* 0x28 */
	بنانشانی صحيح  s3;	 /*! Prescale Register */
	بنانشانی صحيح   s3_rsvd;

/* 0x30 */
	بنانشانی صحيح  ویلا;	 /*! Prescale Register */
	بنانشانی صحيح   ویلا_rsvd;

/* 0x38 */
	بنانشانی صحيح  scl;	 /*! Prescale Register */
	بنانشانی صحيح   scl_rsvd;
} i2c_struct;

فراغ i2c_init(فراغ);
صحيح config_i2c(i2c_struct *,بنانشانی حرف prescale_div, بنانشانی حرف scl_div);
صحيح wait_till_I2c_bus_free(i2c_struct *);
صحيح wait_till_txrx_operation_Completes(i2c_struct *,صحيح *حالت_2);
صحيح sendbytes(i2c_struct *, ثابت حرف *buf, صحيح گنتی, صحيح آخری, صحيح eni);
صحيح readbytes(i2c_struct *,حرف *buf, صحيح گنتی, صحيح آخری);
صحيح i2c_send_slave_پتہ(i2c_struct *,بنانشانی حرف slave_پتہ, بنانشانی
			   حرف rdWrCntrl, بنانشانی لما delay);
صحيح i2c_write_انکڑے(i2c_struct *,بنانشانی حرف write_انکڑے, بنانشانی حرف delay);
صحيح i2c_read_انکڑے(i2c_struct *,بنانشانی حرف *read_انکڑے_2, بنانشانی حرف delay);
صحيح i2c_send_رکاوٹ_slave_پتہ(i2c_struct * instance, بنانشانی حرف
				     slave_پتہ, بنانشانی حرف rdWrCntrl,
				     بنانشانی لما delay);
صحيح i2c_read_رکاوٹ_انکڑے(i2c_struct * instance, بنانشانی حرف *read_انکڑے_2,
			    بنانشانی حرف delay, بنانشانی حرف آخری);
صحيح i2c_write_رکاوٹ_انکڑے(i2c_struct * instance, بنانشانی حرف write_انکڑے,
			     بنانشانی حرف delay, بنانشانی حرف آخری);
صحيح i2c_read_انکڑے_nack(i2c_struct * instance, بنانشانی حرف *read_انکڑے_2, بنانشانی
		       حرف delay);

خارجي i2c_struct *i2c_instance[MAX_I2_C_گنتی];

#جے_انت
