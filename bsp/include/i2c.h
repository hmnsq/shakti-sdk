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

#অন্তর্ভাব "platform.h"

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

unsigned অক্ষর i2c_complete_flag;
unsigned পূর্ণসংখ্যা i2c_read_মান;

/* Struct to access I2C registers as 32 bit registers */
প্রকারলেখ কাঠামো
{
/* 0x00 */
	unsigned পূর্ণসংখ্যা  prescale;     /*! Prescale Register */
	unsigned পূর্ণসংখ্যা   prescale_rsvd;

/* 0x08 */
	unsigned পূর্ণসংখ্যা   control;
	unsigned পূর্ণসংখ্যা   control_rsvd;

/* 0x10 */
	unsigned পূর্ণসংখ্যা  তথ্য_2;	 /*! Prescale Register */
	unsigned পূর্ণসংখ্যা   তথ্য_rsvd;

/* 0x18 */
	unsigned পূর্ণসংখ্যা  status;	 /*! Prescale Register */
	unsigned পূর্ণসংখ্যা   status_rsvd;

/* 0x20 */
	unsigned পূর্ণসংখ্যা  s01;	 /*! Prescale Register */
	unsigned পূর্ণসংখ্যা   s01_rsvd;

/* 0x28 */
	unsigned পূর্ণসংখ্যা  s3;	 /*! Prescale Register */
	unsigned পূর্ণসংখ্যা   s3_rsvd;

/* 0x30 */
	unsigned পূর্ণসংখ্যা  time;	 /*! Prescale Register */
	unsigned পূর্ণসংখ্যা   time_rsvd;

/* 0x38 */
	unsigned পূর্ণসংখ্যা  scl;	 /*! Prescale Register */
	unsigned পূর্ণসংখ্যা   scl_rsvd;
} i2c_struct;

শূন্য i2c_init(শূন্য);
পূর্ণসংখ্যা config_i2c(i2c_struct *,unsigned অক্ষর prescale_div, unsigned অক্ষর scl_div);
পূর্ণসংখ্যা wait_till_I2c_bus_free(i2c_struct *);
পূর্ণসংখ্যা wait_till_txrx_operation_Completes(i2c_struct *,পূর্ণসংখ্যা *status);
পূর্ণসংখ্যা sendbytes(i2c_struct *, ধ্রুবক অক্ষর *buf, পূর্ণসংখ্যা গুনতি, পূর্ণসংখ্যা last, পূর্ণসংখ্যা eni);
পূর্ণসংখ্যা readbytes(i2c_struct *,অক্ষর *buf, পূর্ণসংখ্যা গুনতি, পূর্ণসংখ্যা last);
পূর্ণসংখ্যা i2c_send_slave_address(i2c_struct *,unsigned অক্ষর slaveAddress, unsigned
			   অক্ষর rdWrCntrl, unsigned long delay);
পূর্ণসংখ্যা i2c_write_তথ্য(i2c_struct *,unsigned অক্ষর write_তথ্য, unsigned অক্ষর delay);
পূর্ণসংখ্যা i2c_read_তথ্য(i2c_struct *,unsigned অক্ষর *read_তথ্য_2, unsigned অক্ষর delay);
পূর্ণসংখ্যা i2c_send_interrupt_slave_address(i2c_struct * instance, unsigned অক্ষর
				     slaveAddress, unsigned অক্ষর rdWrCntrl,
				     unsigned long delay);
পূর্ণসংখ্যা i2c_read_interrupt_তথ্য(i2c_struct * instance, unsigned অক্ষর *read_তথ্য_2,
			    unsigned অক্ষর delay, unsigned অক্ষর last);
পূর্ণসংখ্যা i2c_write_interrupt_তথ্য(i2c_struct * instance, unsigned অক্ষর write_তথ্য,
			     unsigned অক্ষর delay, unsigned অক্ষর last);
পূর্ণসংখ্যা i2c_read_তথ্য_nack(i2c_struct * instance, unsigned অক্ষর *read_তথ্য_2, unsigned
		       অক্ষর delay);

বাহ্যিক i2c_struct *i2c_instance[MAX_I2_C_গুনতি];

#endif
