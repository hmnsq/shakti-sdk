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

#अन्तर्भाव "platform.h"

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

unsigned वर्ण i2c_complete_flag;
unsigned पूर्णाङ्क i2c_read_मानम्;

/* Struct to access I2C registers as 32 bit registers */
प्रकारनिर्देश संरचना
{
/* 0x00 */
	unsigned पूर्णाङ्क  prescale;     /*! Prescale Register */
	unsigned पूर्णाङ्क   prescale_rsvd;

/* 0x08 */
	unsigned पूर्णाङ्क   control;
	unsigned पूर्णाङ्क   control_rsvd;

/* 0x10 */
	unsigned पूर्णाङ्क  data;	 /*! Prescale Register */
	unsigned पूर्णाङ्क   data_rsvd;

/* 0x18 */
	unsigned पूर्णाङ्क  status;	 /*! Prescale Register */
	unsigned पूर्णाङ्क   status_rsvd;

/* 0x20 */
	unsigned पूर्णाङ्क  s01;	 /*! Prescale Register */
	unsigned पूर्णाङ्क   s01_rsvd;

/* 0x28 */
	unsigned पूर्णाङ्क  s3;	 /*! Prescale Register */
	unsigned पूर्णाङ्क   s3_rsvd;

/* 0x30 */
	unsigned पूर्णाङ्क  time;	 /*! Prescale Register */
	unsigned पूर्णाङ्क   time_rsvd;

/* 0x38 */
	unsigned पूर्णाङ्क  scl;	 /*! Prescale Register */
	unsigned पूर्णाङ्क   scl_rsvd;
} i2c_struct;

शून्य i2c_init(शून्य);
पूर्णाङ्क config_i2c(i2c_struct *,unsigned वर्ण prescale_div, unsigned वर्ण scl_div);
पूर्णाङ्क wait_till_I2c_bus_free(i2c_struct *);
पूर्णाङ्क wait_till_txrx_operation_Completes(i2c_struct *,पूर्णाङ्क *status);
पूर्णाङ्क sendbytes(i2c_struct *, ध्रुव वर्ण *buf, पूर्णाङ्क गणनम्, पूर्णाङ्क last, पूर्णाङ्क eni);
पूर्णाङ्क readbytes(i2c_struct *,वर्ण *buf, पूर्णाङ्क गणनम्, पूर्णाङ्क last);
पूर्णाङ्क i2c_send_slave_address(i2c_struct *,unsigned वर्ण slaveAddress, unsigned
			   वर्ण rdWrCntrl, unsigned long delay);
पूर्णाङ्क i2c_write_data(i2c_struct *,unsigned वर्ण writeData, unsigned वर्ण delay);
पूर्णाङ्क i2c_read_data(i2c_struct *,unsigned वर्ण *read_data, unsigned वर्ण delay);
पूर्णाङ्क i2c_send_interrupt_slave_address(i2c_struct * instance, unsigned वर्ण
				     slaveAddress, unsigned वर्ण rdWrCntrl,
				     unsigned long delay);
पूर्णाङ्क i2c_read_interrupt_data(i2c_struct * instance, unsigned वर्ण *read_data,
			    unsigned वर्ण delay, unsigned वर्ण last);
पूर्णाङ्क i2c_write_interrupt_data(i2c_struct * instance, unsigned वर्ण writeData,
			     unsigned वर्ण delay, unsigned वर्ण last);
पूर्णाङ्क i2c_read_data_nack(i2c_struct * instance, unsigned वर्ण *read_data, unsigned
		       वर्ण delay);

बाह्य i2c_struct *i2c_instance[MAX_I2_C_गणनम्];

#endif
