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

#यदि_अपरिभाषितम् I2C_H
#परिभाषय I2C_H

#अन्तर्भाव "platform.h"

#परिभाषय ETIMEOUT -60
#परिभाषय DEF_TIMEOUT 60
#परिभाषय ETIMEDOUT -80
#परिभाषय ENXIO -82
#परिभाषय EREMOTEIO -81

#परिभाषय I2C_SUCCESS 0
#परिभाषय EAXI_ERROR -1
#परिभाषय EI2C_BUS_ERROR -2
#परिभाषय EI2C_PIN_ERROR -3
#परिभाषय EI2C_LRB_ERROR -4

#परिभाषय I2C_PIN	0x80
#परिभाषय I2C_ESO	0x40
#परिभाषय I2C_ES1	0x20
#परिभाषय I2C_ES2	0x10
#परिभाषय I2C_ENI	0x08
#परिभाषय I2C_STA	0x04
#परिभाषय I2C_STO	0x02
#परिभाषय I2C_ACK	0x01

#परिभाषय I2C_INI 0x40   /* 1 if not initialized */
#परिभाषय I2C_STS 0x20
#परिभाषय I2C_BER 0x10
#परिभाषय I2C_AD0 0x08
#परिभाषय I2C_LRB 0x08
#परिभाषय I2C_AAS 0x04
#परिभाषय I2C_LAB 0x02
#परिभाषय I2C_BB  0x01

#परिभाषय I2C_START         (I2C_PIN | I2C_ESO | I2C_STA | I2C_ACK)
#परिभाषय I2C_START_ENI     (I2C_PIN | I2C_ESO | I2C_STA | I2C_ACK | I2C_ENI)
#परिभाषय I2C_STOP          (I2C_PIN | I2C_ESO | I2C_STO | I2C_ACK)
#परिभाषय I2C_REPSTART      (                 I2C_ESO | I2C_STA | I2C_ACK)
#परिभाषय I2C_REPSTART_ENI  (                 I2C_ESO | I2C_STA | I2C_ACK | I2C_ENI)
#परिभाषय I2C_IDLE          (I2C_PIN | I2C_ESO                  | I2C_ACK)
#परिभाषय I2C_NACK          (I2C_ESO  )
#परिभाषय I2C_STOP_ENI          (I2C_PIN | I2C_ESO | I2C_STO | I2C_ACK | I2C_ENI)

#परिभाषय I2C_READ 1
#परिभाषय I2C_WRITE 0

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

अचिह्नित वर्ण i2c_complete_flag;
अचिह्नित पूर्णाङ्क i2c_read_मानम्;

/* Struct to access I2C registers as 32 bit registers */
प्रकारनिर्देश संरचना
{
/* 0x00 */
	अचिह्नित पूर्णाङ्क  prescale;     /*! Prescale Register */
	अचिह्नित पूर्णाङ्क   prescale_rsvd;

/* 0x08 */
	अचिह्नित पूर्णाङ्क   control;
	अचिह्नित पूर्णाङ्क   control_rsvd;

/* 0x10 */
	अचिह्नित पूर्णाङ्क  दत्त_2;	 /*! Prescale Register */
	अचिह्नित पूर्णाङ्क   दत्त_rsvd;

/* 0x18 */
	अचिह्नित पूर्णाङ्क  स्थितिः_2;	 /*! Prescale Register */
	अचिह्नित पूर्णाङ्क   स्थितिः_rsvd;

/* 0x20 */
	अचिह्नित पूर्णाङ्क  s01;	 /*! Prescale Register */
	अचिह्नित पूर्णाङ्क   s01_rsvd;

/* 0x28 */
	अचिह्नित पूर्णाङ्क  s3;	 /*! Prescale Register */
	अचिह्नित पूर्णाङ्क   s3_rsvd;

/* 0x30 */
	अचिह्नित पूर्णाङ्क  time;	 /*! Prescale Register */
	अचिह्नित पूर्णाङ्क   time_rsvd;

/* 0x38 */
	अचिह्नित पूर्णाङ्क  scl;	 /*! Prescale Register */
	अचिह्नित पूर्णाङ्क   scl_rsvd;
} i2c_struct;

शून्य i2c_init(शून्य);
पूर्णाङ्क config_i2c(i2c_struct *,अचिह्नित वर्ण prescale_div, अचिह्नित वर्ण scl_div);
पूर्णाङ्क wait_till_I2c_bus_free(i2c_struct *);
पूर्णाङ्क wait_till_txrx_operation_Completes(i2c_struct *,पूर्णाङ्क *स्थितिः_2);
पूर्णाङ्क sendbytes(i2c_struct *, ध्रुव वर्ण *buf, पूर्णाङ्क गणनम्, पूर्णाङ्क चरमः, पूर्णाङ्क eni);
पूर्णाङ्क readbytes(i2c_struct *,वर्ण *buf, पूर्णाङ्क गणनम्, पूर्णाङ्क चरमः);
पूर्णाङ्क i2c_send_slave_स्थानाङ्कः(i2c_struct *,अचिह्नित वर्ण slave_स्थानाङ्कः, अचिह्नित
			   वर्ण rdWrCntrl, अचिह्नित दीर्घ delay);
पूर्णाङ्क i2c_write_दत्त(i2c_struct *,अचिह्नित वर्ण write_दत्त, अचिह्नित वर्ण delay);
पूर्णाङ्क i2c_read_दत्त(i2c_struct *,अचिह्नित वर्ण *read_दत्त_2, अचिह्नित वर्ण delay);
पूर्णाङ्क i2c_send_व्यवधानम्_slave_स्थानाङ्कः(i2c_struct * instance, अचिह्नित वर्ण
				     slave_स्थानाङ्कः, अचिह्नित वर्ण rdWrCntrl,
				     अचिह्नित दीर्घ delay);
पूर्णाङ्क i2c_read_व्यवधानम्_दत्त(i2c_struct * instance, अचिह्नित वर्ण *read_दत्त_2,
			    अचिह्नित वर्ण delay, अचिह्नित वर्ण चरमः);
पूर्णाङ्क i2c_write_व्यवधानम्_दत्त(i2c_struct * instance, अचिह्नित वर्ण write_दत्त,
			     अचिह्नित वर्ण delay, अचिह्नित वर्ण चरमः);
पूर्णाङ्क i2c_read_दत्त_nack(i2c_struct * instance, अचिह्नित वर्ण *read_दत्त_2, अचिह्नित
		       वर्ण delay);

बाह्य i2c_struct *i2c_instance[MAX_I2_C_गणनम्];

#यदि_अन्तः
