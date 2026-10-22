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

#अगर_अघोषित I2C_H
#घोषणा I2C_H

#समावेश "platform.h"

#घोषणा ETIMEOUT -60
#घोषणा DEF_TIMEOUT 60
#घोषणा ETIMEDOUT -80
#घोषणा ENXIO -82
#घोषणा EREMOTEIO -81

#घोषणा I2C_SUCCESS 0
#घोषणा EAXI_ERROR -1
#घोषणा EI2C_BUS_ERROR -2
#घोषणा EI2C_PIN_ERROR -3
#घोषणा EI2C_LRB_ERROR -4

#घोषणा I2C_PIN	0x80
#घोषणा I2C_ESO	0x40
#घोषणा I2C_ES1	0x20
#घोषणा I2C_ES2	0x10
#घोषणा I2C_ENI	0x08
#घोषणा I2C_STA	0x04
#घोषणा I2C_STO	0x02
#घोषणा I2C_ACK	0x01

#घोषणा I2C_INI 0x40   /* 1 if not initialized */
#घोषणा I2C_STS 0x20
#घोषणा I2C_BER 0x10
#घोषणा I2C_AD0 0x08
#घोषणा I2C_LRB 0x08
#घोषणा I2C_AAS 0x04
#घोषणा I2C_LAB 0x02
#घोषणा I2C_BB  0x01

#घोषणा I2C_START         (I2C_PIN | I2C_ESO | I2C_STA | I2C_ACK)
#घोषणा I2C_START_ENI     (I2C_PIN | I2C_ESO | I2C_STA | I2C_ACK | I2C_ENI)
#घोषणा I2C_STOP          (I2C_PIN | I2C_ESO | I2C_STO | I2C_ACK)
#घोषणा I2C_REPSTART      (                 I2C_ESO | I2C_STA | I2C_ACK)
#घोषणा I2C_REPSTART_ENI  (                 I2C_ESO | I2C_STA | I2C_ACK | I2C_ENI)
#घोषणा I2C_IDLE          (I2C_PIN | I2C_ESO                  | I2C_ACK)
#घोषणा I2C_NACK          (I2C_ESO  )
#घोषणा I2C_STOP_ENI          (I2C_PIN | I2C_ESO | I2C_STO | I2C_ACK | I2C_ENI)

#घोषणा I2C_READ 1
#घोषणा I2C_WRITE 0

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

अचिन्हित अक्षर i2c_complete_flag;
अचिन्हित पूर्णांक i2c_read_मूल्य;

/* Struct to access I2C registers as 32 bit registers */
प्रकार काष्ठा
{
/* 0x00 */
	अचिन्हित पूर्णांक  prescale;     /*! Prescale Register */
	अचिन्हित पूर्णांक   prescale_rsvd;

/* 0x08 */
	अचिन्हित पूर्णांक   control;
	अचिन्हित पूर्णांक   control_rsvd;

/* 0x10 */
	अचिन्हित पूर्णांक  तथ्य_2;	 /*! Prescale Register */
	अचिन्हित पूर्णांक   तथ्य_rsvd;

/* 0x18 */
	अचिन्हित पूर्णांक  status;	 /*! Prescale Register */
	अचिन्हित पूर्णांक   status_rsvd;

/* 0x20 */
	अचिन्हित पूर्णांक  s01;	 /*! Prescale Register */
	अचिन्हित पूर्णांक   s01_rsvd;

/* 0x28 */
	अचिन्हित पूर्णांक  s3;	 /*! Prescale Register */
	अचिन्हित पूर्णांक   s3_rsvd;

/* 0x30 */
	अचिन्हित पूर्णांक  समय;	 /*! Prescale Register */
	अचिन्हित पूर्णांक   time_rsvd;

/* 0x38 */
	अचिन्हित पूर्णांक  scl;	 /*! Prescale Register */
	अचिन्हित पूर्णांक   scl_rsvd;
} i2c_struct;

व्योम i2c_init(व्योम);
पूर्णांक config_i2c(i2c_struct *,अचिन्हित अक्षर prescale_div, अचिन्हित अक्षर scl_div);
पूर्णांक wait_till_I2c_bus_free(i2c_struct *);
पूर्णांक wait_till_txrx_operation_Completes(i2c_struct *,पूर्णांक *status);
पूर्णांक sendbytes(i2c_struct *, स्थिर अक्षर *buf, पूर्णांक गिनती, पूर्णांक last, पूर्णांक eni);
पूर्णांक readbytes(i2c_struct *,अक्षर *buf, पूर्णांक गिनती, पूर्णांक last);
पूर्णांक i2c_send_slave_address(i2c_struct *,अचिन्हित अक्षर slaveAddress, अचिन्हित
			   अक्षर rdWrCntrl, अचिन्हित दीर्घ delay);
पूर्णांक i2c_write_तथ्य(i2c_struct *,अचिन्हित अक्षर write_तथ्य, अचिन्हित अक्षर delay);
पूर्णांक i2c_read_तथ्य(i2c_struct *,अचिन्हित अक्षर *read_तथ्य_2, अचिन्हित अक्षर delay);
पूर्णांक i2c_send_interrupt_slave_address(i2c_struct * instance, अचिन्हित अक्षर
				     slaveAddress, अचिन्हित अक्षर rdWrCntrl,
				     अचिन्हित दीर्घ delay);
पूर्णांक i2c_read_interrupt_तथ्य(i2c_struct * instance, अचिन्हित अक्षर *read_तथ्य_2,
			    अचिन्हित अक्षर delay, अचिन्हित अक्षर last);
पूर्णांक i2c_write_interrupt_तथ्य(i2c_struct * instance, अचिन्हित अक्षर write_तथ्य,
			     अचिन्हित अक्षर delay, अचिन्हित अक्षर last);
पूर्णांक i2c_read_तथ्य_nack(i2c_struct * instance, अचिन्हित अक्षर *read_तथ्य_2, अचिन्हित
		       अक्षर delay);

बाह्य i2c_struct *i2c_instance[MAX_I2_C_गिनती];

#पूर्ण_अगर
