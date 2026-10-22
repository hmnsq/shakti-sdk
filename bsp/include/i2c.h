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

#که_نه_تعریف_شوی I2C_H
#تعریف_کړه I2C_H

#ضمن "platform.h"

#تعریف_کړه ETIMEOUT -60
#تعریف_کړه DEF_TIMEOUT 60
#تعریف_کړه ETIMEDOUT -80
#تعریف_کړه ENXIO -82
#تعریف_کړه EREMOTEIO -81

#تعریف_کړه I2C_SUCCESS 0
#تعریف_کړه EAXI_ERROR -1
#تعریف_کړه EI2C_BUS_ERROR -2
#تعریف_کړه EI2C_PIN_ERROR -3
#تعریف_کړه EI2C_LRB_ERROR -4

#تعریف_کړه I2C_PIN	0x80
#تعریف_کړه I2C_ESO	0x40
#تعریف_کړه I2C_ES1	0x20
#تعریف_کړه I2C_ES2	0x10
#تعریف_کړه I2C_ENI	0x08
#تعریف_کړه I2C_STA	0x04
#تعریف_کړه I2C_STO	0x02
#تعریف_کړه I2C_ACK	0x01

#تعریف_کړه I2C_INI 0x40   /* 1 if not initialized */
#تعریف_کړه I2C_STS 0x20
#تعریف_کړه I2C_BER 0x10
#تعریف_کړه I2C_AD0 0x08
#تعریف_کړه I2C_LRB 0x08
#تعریف_کړه I2C_AAS 0x04
#تعریف_کړه I2C_LAB 0x02
#تعریف_کړه I2C_BB  0x01

#تعریف_کړه I2_C_پیل         (I2C_PIN | I2C_ESO | I2C_STA | I2C_ACK)
#تعریف_کړه I2_C_پیل_ENI     (I2C_PIN | I2C_ESO | I2C_STA | I2C_ACK | I2C_ENI)
#تعریف_کړه I2C_STOP          (I2C_PIN | I2C_ESO | I2C_STO | I2C_ACK)
#تعریف_کړه I2C_REPSTART      (                 I2C_ESO | I2C_STA | I2C_ACK)
#تعریف_کړه I2C_REPSTART_ENI  (                 I2C_ESO | I2C_STA | I2C_ACK | I2C_ENI)
#تعریف_کړه I2C_IDLE          (I2C_PIN | I2C_ESO                  | I2C_ACK)
#تعریف_کړه I2C_NACK          (I2C_ESO  )
#تعریف_کړه I2C_STOP_ENI          (I2C_PIN | I2C_ESO | I2C_STO | I2C_ACK | I2C_ENI)

#تعریف_کړه I2C_READ 1
#تعریف_کړه I2C_WRITE 0

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

بینښه حرف i2c_complete_flag;
بینښه صحيح i2c_read_ارزښت;

/* Struct to access I2C registers as 32 bit registers */
تعريفنوع بنية
{
/* 0x00 */
	بینښه صحيح  prescale;     /*! Prescale Register */
	بینښه صحيح   prescale_rsvd;

/* 0x08 */
	بینښه صحيح   control;
	بینښه صحيح   control_rsvd;

/* 0x10 */
	بینښه صحيح  معلومات_2;	 /*! Prescale Register */
	بینښه صحيح   معلومات_rsvd;

/* 0x18 */
	بینښه صحيح  حالت_2;	 /*! Prescale Register */
	بینښه صحيح   حالت_rsvd;

/* 0x20 */
	بینښه صحيح  s01;	 /*! Prescale Register */
	بینښه صحيح   s01_rsvd;

/* 0x28 */
	بینښه صحيح  s3;	 /*! Prescale Register */
	بینښه صحيح   s3_rsvd;

/* 0x30 */
	بینښه صحيح  وخت;	 /*! Prescale Register */
	بینښه صحيح   وخت_rsvd;

/* 0x38 */
	بینښه صحيح  scl;	 /*! Prescale Register */
	بینښه صحيح   scl_rsvd;
} i2c_struct;

فراغ i2c_init(فراغ);
صحيح config_i2c(i2c_struct *,بینښه حرف prescale_div, بینښه حرف scl_div);
صحيح wait_till_I2c_bus_free(i2c_struct *);
صحيح wait_till_txrx_operation_Completes(i2c_struct *,صحيح *حالت_2);
صحيح sendbytes(i2c_struct *, ثابت حرف *buf, صحيح شمېر, صحيح وروستی, صحيح eni);
صحيح readbytes(i2c_struct *,حرف *buf, صحيح شمېر, صحيح وروستی);
صحيح i2c_send_slave_پته(i2c_struct *,بینښه حرف slave_پته, بینښه
			   حرف rdWrCntrl, بینښه اوږد delay);
صحيح i2c_write_معلومات(i2c_struct *,بینښه حرف write_معلومات, بینښه حرف delay);
صحيح i2c_read_معلومات(i2c_struct *,بینښه حرف *read_معلومات_2, بینښه حرف delay);
صحيح i2c_send_مداخله_slave_پته(i2c_struct * instance, بینښه حرف
				     slave_پته, بینښه حرف rdWrCntrl,
				     بینښه اوږد delay);
صحيح i2c_read_مداخله_معلومات(i2c_struct * instance, بینښه حرف *read_معلومات_2,
			    بینښه حرف delay, بینښه حرف وروستی);
صحيح i2c_write_مداخله_معلومات(i2c_struct * instance, بینښه حرف write_معلومات,
			     بینښه حرف delay, بینښه حرف وروستی);
صحيح i2c_read_معلومات_nack(i2c_struct * instance, بینښه حرف *read_معلومات_2, بینښه
		       حرف delay);

خارجي i2c_struct *i2c_instance[MAX_I2_C_شمېر];

#د_که_پای
