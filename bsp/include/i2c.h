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

#నిర్వచితం_కాకపోతే I2C_H
#నిర్వచించు I2C_H

#అన్తర్భావ "platform.h"

#నిర్వచించు ETIMEOUT -60
#నిర్వచించు DEF_TIMEOUT 60
#నిర్వచించు ETIMEDOUT -80
#నిర్వచించు ENXIO -82
#నిర్వచించు EREMOTEIO -81

#నిర్వచించు I2C_SUCCESS 0
#నిర్వచించు EAXI_ERROR -1
#నిర్వచించు EI2C_BUS_ERROR -2
#నిర్వచించు EI2C_PIN_ERROR -3
#నిర్వచించు EI2C_LRB_ERROR -4

#నిర్వచించు I2C_PIN	0x80
#నిర్వచించు I2C_ESO	0x40
#నిర్వచించు I2C_ES1	0x20
#నిర్వచించు I2C_ES2	0x10
#నిర్వచించు I2C_ENI	0x08
#నిర్వచించు I2C_STA	0x04
#నిర్వచించు I2C_STO	0x02
#నిర్వచించు I2C_ACK	0x01

#నిర్వచించు I2C_INI 0x40   /* 1 if not initialized */
#నిర్వచించు I2C_STS 0x20
#నిర్వచించు I2C_BER 0x10
#నిర్వచించు I2C_AD0 0x08
#నిర్వచించు I2C_LRB 0x08
#నిర్వచించు I2C_AAS 0x04
#నిర్వచించు I2C_LAB 0x02
#నిర్వచించు I2C_BB  0x01

#నిర్వచించు I2_C_ప్రారంభం         (I2C_PIN | I2C_ESO | I2C_STA | I2C_ACK)
#నిర్వచించు I2_C_ప్రారంభం_ENI     (I2C_PIN | I2C_ESO | I2C_STA | I2C_ACK | I2C_ENI)
#నిర్వచించు I2C_STOP          (I2C_PIN | I2C_ESO | I2C_STO | I2C_ACK)
#నిర్వచించు I2C_REPSTART      (                 I2C_ESO | I2C_STA | I2C_ACK)
#నిర్వచించు I2C_REPSTART_ENI  (                 I2C_ESO | I2C_STA | I2C_ACK | I2C_ENI)
#నిర్వచించు I2C_IDLE          (I2C_PIN | I2C_ESO                  | I2C_ACK)
#నిర్వచించు I2C_NACK          (I2C_ESO  )
#నిర్వచించు I2C_STOP_ENI          (I2C_PIN | I2C_ESO | I2C_STO | I2C_ACK | I2C_ENI)

#నిర్వచించు I2C_READ 1
#నిర్వచించు I2C_WRITE 0

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

గుర్తులేని అక్షరం i2c_complete_flag;
గుర్తులేని పూర్ణాంకం i2c_read_విలువ;

/* Struct to access I2C registers as 32 bit registers */
రకనిర్వచనం నిర్మాణం
{
/* 0x00 */
	గుర్తులేని పూర్ణాంకం  prescale;     /*! Prescale Register */
	గుర్తులేని పూర్ణాంకం   prescale_rsvd;

/* 0x08 */
	గుర్తులేని పూర్ణాంకం   control;
	గుర్తులేని పూర్ణాంకం   control_rsvd;

/* 0x10 */
	గుర్తులేని పూర్ణాంకం  దత్తాంశం_2;	 /*! Prescale Register */
	గుర్తులేని పూర్ణాంకం   దత్తాంశం_rsvd;

/* 0x18 */
	గుర్తులేని పూర్ణాంకం  స్థితి_3;	 /*! Prescale Register */
	గుర్తులేని పూర్ణాంకం   స్థితి_rsvd;

/* 0x20 */
	గుర్తులేని పూర్ణాంకం  s01;	 /*! Prescale Register */
	గుర్తులేని పూర్ణాంకం   s01_rsvd;

/* 0x28 */
	గుర్తులేని పూర్ణాంకం  s3;	 /*! Prescale Register */
	గుర్తులేని పూర్ణాంకం   s3_rsvd;

/* 0x30 */
	గుర్తులేని పూర్ణాంకం  సమయం;	 /*! Prescale Register */
	గుర్తులేని పూర్ణాంకం   సమయం_rsvd;

/* 0x38 */
	గుర్తులేని పూర్ణాంకం  scl;	 /*! Prescale Register */
	గుర్తులేని పూర్ణాంకం   scl_rsvd;
} i2c_struct;

శూన్య i2c_init(శూన్య);
పూర్ణాంకం config_i2c(i2c_struct *,గుర్తులేని అక్షరం prescale_div, గుర్తులేని అక్షరం scl_div);
పూర్ణాంకం wait_till_I2c_bus_free(i2c_struct *);
పూర్ణాంకం wait_till_txrx_operation_Completes(i2c_struct *,పూర్ణాంకం *స్థితి_3);
పూర్ణాంకం sendbytes(i2c_struct *, స్థిరరాశి అక్షరం *buf, పూర్ణాంకం లెక్క, పూర్ణాంకం చివరి, పూర్ణాంకం eni);
పూర్ణాంకం readbytes(i2c_struct *,అక్షరం *buf, పూర్ణాంకం లెక్క, పూర్ణాంకం చివరి);
పూర్ణాంకం i2c_send_slave_చిరునామా(i2c_struct *,గుర్తులేని అక్షరం slave_చిరునామా, గుర్తులేని
			   అక్షరం rdWrCntrl, గుర్తులేని దీర్ఘ delay);
పూర్ణాంకం i2c_write_దత్తాంశం(i2c_struct *,గుర్తులేని అక్షరం write_దత్తాంశం, గుర్తులేని అక్షరం delay);
పూర్ణాంకం i2c_read_దత్తాంశం(i2c_struct *,గుర్తులేని అక్షరం *read_దత్తాంశం_2, గుర్తులేని అక్షరం delay);
పూర్ణాంకం i2c_send_అంతరాయం_slave_చిరునామా(i2c_struct * instance, గుర్తులేని అక్షరం
				     slave_చిరునామా, గుర్తులేని అక్షరం rdWrCntrl,
				     గుర్తులేని దీర్ఘ delay);
పూర్ణాంకం i2c_read_అంతరాయం_దత్తాంశం(i2c_struct * instance, గుర్తులేని అక్షరం *read_దత్తాంశం_2,
			    గుర్తులేని అక్షరం delay, గుర్తులేని అక్షరం చివరి);
పూర్ణాంకం i2c_write_అంతరాయం_దత్తాంశం(i2c_struct * instance, గుర్తులేని అక్షరం write_దత్తాంశం,
			     గుర్తులేని అక్షరం delay, గుర్తులేని అక్షరం చివరి);
పూర్ణాంకం i2c_read_దత్తాంశం_nack(i2c_struct * instance, గుర్తులేని అక్షరం *read_దత్తాంశం_2, గుర్తులేని
		       అక్షరం delay);

బాహ్య i2c_struct *i2c_instance[MAX_I2_C_లెక్క];

#అయితే_ముగింపు
