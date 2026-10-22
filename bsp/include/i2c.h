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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ I2C_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_H

#ਅਨ੍ਤਰ੍ਭਾਵ "platform.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ETIMEOUT -60
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEF_TIMEOUT 60
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ETIMEDOUT -80
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ENXIO -82
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EREMOTEIO -81

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_SUCCESS 0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EAXI_ERROR -1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EI2C_BUS_ERROR -2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EI2C_PIN_ERROR -3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EI2C_LRB_ERROR -4

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_PIN	0x80
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_ESO	0x40
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_ES1	0x20
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_ES2	0x10
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_ENI	0x08
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_STA	0x04
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_STO	0x02
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_ACK	0x01

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_INI 0x40   /* 1 if not initialized */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_STS 0x20
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_BER 0x10
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_AD0 0x08
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_LRB 0x08
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_AAS 0x04
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_LAB 0x02
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_BB  0x01

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2_C_ਸ਼ੁਰੂ         (I2C_PIN | I2C_ESO | I2C_STA | I2C_ACK)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2_C_ਸ਼ੁਰੂ_ENI     (I2C_PIN | I2C_ESO | I2C_STA | I2C_ACK | I2C_ENI)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_STOP          (I2C_PIN | I2C_ESO | I2C_STO | I2C_ACK)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_REPSTART      (                 I2C_ESO | I2C_STA | I2C_ACK)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_REPSTART_ENI  (                 I2C_ESO | I2C_STA | I2C_ACK | I2C_ENI)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_IDLE          (I2C_PIN | I2C_ESO                  | I2C_ACK)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_NACK          (I2C_ESO  )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_STOP_ENI          (I2C_PIN | I2C_ESO | I2C_STO | I2C_ACK | I2C_ENI)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_READ 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ I2C_WRITE 0

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

ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ i2c_complete_flag;
ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i2c_read_ਮੁੱਲ;

/* Struct to access I2C registers as 32 bit registers */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
/* 0x00 */
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ  prescale;     /*! Prescale Register */
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ   prescale_rsvd;

/* 0x08 */
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ   control;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ   control_rsvd;

/* 0x10 */
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ  ਅੰਕੜੇ_2;	 /*! Prescale Register */
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ   ਅੰਕੜੇ_rsvd;

/* 0x18 */
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ  ਸਥਿਤੀ_2;	 /*! Prescale Register */
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ   ਸਥਿਤੀ_rsvd;

/* 0x20 */
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ  s01;	 /*! Prescale Register */
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ   s01_rsvd;

/* 0x28 */
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ  s3;	 /*! Prescale Register */
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ   s3_rsvd;

/* 0x30 */
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ  ਸਮਾਂ;	 /*! Prescale Register */
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ   ਸਮਾਂ_rsvd;

/* 0x38 */
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ  scl;	 /*! Prescale Register */
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ   scl_rsvd;
} i2c_struct;

ਖਾਲੀ i2c_init(ਖਾਲੀ);
ਪੂਰਨ config_i2c(i2c_struct *,ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ prescale_div, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ scl_div);
ਪੂਰਨ wait_till_I2c_bus_free(i2c_struct *);
ਪੂਰਨ wait_till_txrx_operation_Completes(i2c_struct *,ਪੂਰਨ *ਸਥਿਤੀ_2);
ਪੂਰਨ sendbytes(i2c_struct *, ਅਚਲ ਅੱਖਰ *buf, ਪੂਰਨ ਗਿਣਤੀ_2, ਪੂਰਨ ਆਖਰੀ, ਪੂਰਨ eni);
ਪੂਰਨ readbytes(i2c_struct *,ਅੱਖਰ *buf, ਪੂਰਨ ਗਿਣਤੀ_2, ਪੂਰਨ ਆਖਰੀ);
ਪੂਰਨ i2c_send_slave_ਪਤਾ(i2c_struct *,ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ slave_ਪਤਾ, ਬਿਨਾਨਿਸ਼ਾਨੀ
			   ਅੱਖਰ rdWrCntrl, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ delay);
ਪੂਰਨ i2c_write_ਅੰਕੜੇ(i2c_struct *,ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ write_ਅੰਕੜੇ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ delay);
ਪੂਰਨ i2c_read_ਅੰਕੜੇ(i2c_struct *,ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *read_ਅੰਕੜੇ_2, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ delay);
ਪੂਰਨ i2c_send_ਰੁਕਾਵਟ_slave_ਪਤਾ(i2c_struct * instance, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ
				     slave_ਪਤਾ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ rdWrCntrl,
				     ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ delay);
ਪੂਰਨ i2c_read_ਰੁਕਾਵਟ_ਅੰਕੜੇ(i2c_struct * instance, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *read_ਅੰਕੜੇ_2,
			    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ delay, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਆਖਰੀ);
ਪੂਰਨ i2c_write_ਰੁਕਾਵਟ_ਅੰਕੜੇ(i2c_struct * instance, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ write_ਅੰਕੜੇ,
			     ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ delay, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਆਖਰੀ);
ਪੂਰਨ i2c_read_ਅੰਕੜੇ_nack(i2c_struct * instance, ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *read_ਅੰਕੜੇ_2, ਬਿਨਾਨਿਸ਼ਾਨੀ
		       ਅੱਖਰ delay);

ਬਾਹਰੀ i2c_struct *i2c_instance[MAX_I2_C_ਗਿਣਤੀ];

#ਜੇ_ਅੰਤ
