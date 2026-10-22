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

#ifndef I2C_H
#define I2C_H

#include "platform.h"

#define ETIMEOUT -60
#define DEF_TIMEOUT 60
#define ETIMEDOUT -80
#define ENXIO -82
#define EREMOTEIO -81

#define I2C_SUCCESS 0
#define EAXI_ERROR -1
#define EI2C_BUS_ERROR -2
#define EI2C_PIN_ERROR -3
#define EI2C_LRB_ERROR -4

#define I2C_PIN	0x80
#define I2C_ESO	0x40
#define I2C_ES1	0x20
#define I2C_ES2	0x10
#define I2C_ENI	0x08
#define I2C_STA	0x04
#define I2C_STO	0x02
#define I2C_ACK	0x01

#define I2C_INI 0x40   /* 1 if not initialized */
#define I2C_STS 0x20
#define I2C_BER 0x10
#define I2C_AD0 0x08
#define I2C_LRB 0x08
#define I2C_AAS 0x04
#define I2C_LAB 0x02
#define I2C_BB  0x01

#define I2C_START         (I2C_PIN | I2C_ESO | I2C_STA | I2C_ACK)
#define I2C_START_ENI     (I2C_PIN | I2C_ESO | I2C_STA | I2C_ACK | I2C_ENI)
#define I2C_STOP          (I2C_PIN | I2C_ESO | I2C_STO | I2C_ACK)
#define I2C_REPSTART      (                 I2C_ESO | I2C_STA | I2C_ACK)
#define I2C_REPSTART_ENI  (                 I2C_ESO | I2C_STA | I2C_ACK | I2C_ENI)
#define I2C_IDLE          (I2C_PIN | I2C_ESO                  | I2C_ACK)
#define I2C_NACK          (I2C_ESO  )
#define I2C_STOP_ENI          (I2C_PIN | I2C_ESO | I2C_STO | I2C_ACK | I2C_ENI)

#define I2C_READ 1
#define I2C_WRITE 0

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

unsigned char i2c_complete_flag;
unsigned цяло i2c_read_value;

/* Struct to access I2C registers as 32 bit registers */
typedef struct
{
/* 0x00 */
	unsigned цяло  prescale;     /*! Prescale Register */
	unsigned цяло   prescale_rsvd;

/* 0x08 */
	unsigned цяло   control;
	unsigned цяло   control_rsvd;

/* 0x10 */
	unsigned цяло  data;	 /*! Prescale Register */
	unsigned цяло   data_rsvd;

/* 0x18 */
	unsigned цяло  status;	 /*! Prescale Register */
	unsigned цяло   status_rsvd;

/* 0x20 */
	unsigned цяло  s01;	 /*! Prescale Register */
	unsigned цяло   s01_rsvd;

/* 0x28 */
	unsigned цяло  s3;	 /*! Prescale Register */
	unsigned цяло   s3_rsvd;

/* 0x30 */
	unsigned цяло  time;	 /*! Prescale Register */
	unsigned цяло   time_rsvd;

/* 0x38 */
	unsigned цяло  scl;	 /*! Prescale Register */
	unsigned цяло   scl_rsvd;
} i2c_struct;

void i2c_init(void);
цяло config_i2c(i2c_struct *,unsigned char prescale_div, unsigned char scl_div);
цяло wait_till_I2c_bus_free(i2c_struct *);
цяло wait_till_txrx_operation_Completes(i2c_struct *,цяло *status);
цяло sendbytes(i2c_struct *, const char *buf, цяло count, цяло last, цяло eni);
цяло readbytes(i2c_struct *,char *buf, цяло count, цяло last);
цяло i2c_send_slave_address(i2c_struct *,unsigned char slaveAddress, unsigned
			   char rdWrCntrl, unsigned long delay);
цяло i2c_write_data(i2c_struct *,unsigned char writeData, unsigned char delay);
цяло i2c_read_data(i2c_struct *,unsigned char *read_data, unsigned char delay);
цяло i2c_send_interrupt_slave_address(i2c_struct * instance, unsigned char
				     slaveAddress, unsigned char rdWrCntrl,
				     unsigned long delay);
цяло i2c_read_interrupt_data(i2c_struct * instance, unsigned char *read_data,
			    unsigned char delay, unsigned char last);
цяло i2c_write_interrupt_data(i2c_struct * instance, unsigned char writeData,
			     unsigned char delay, unsigned char last);
цяло i2c_read_data_nack(i2c_struct * instance, unsigned char *read_data, unsigned
		       char delay);

extern i2c_struct *i2c_instance[MAX_I2C_COUNT];

#endif
