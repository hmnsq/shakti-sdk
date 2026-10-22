/***************************************************************************
 * Project                          : shakti devt board
 * Name of the file                 : spi.h
 * Brief Description of file        : Header to spi spansion driver
 * Name of Author                   : Kaustubh Ghormade
 * Email ID                         : kaustubh4347@gmail.com

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
 ***************************************************************************/
/**
 * @file spi.h
 * @brief Header to spi spansion driver
 * @detail this is the header file for spi_flash_w25q32.c,spi_spansion.c
 */
#నిర్వచితం_కాకపోతే SPI_H
#నిర్వచించు SPI_H

#అన్తర్భావ<stdlib.h>
/*By default SPI0 is enabled at initialization.
  SPI0 is not available externally in TARGET=artix7_35t*/
#నిర్వచించు SPI0_స్థానభ్రంశం 0x00000000
#నిర్వచించు SPI1_స్థానభ్రంశం 0x00000100
#నిర్వచించు SPI2_స్థానభ్రంశం 0x00000200

#నిర్వచించు SPI_CR1	     0x00020000
#నిర్వచించు SPI_CR2	     0x00020004
#నిర్వచించు SPI_SR       0x00020008
#నిర్వచించు SPI_DR1	     0x0002000C
#నిర్వచించు SPI_DR2	     0x00020010
#నిర్వచించు SPI_DR3	     0x00020014
#నిర్వచించు SPI_DR4	     0x00020018
#నిర్వచించు SPI_DR5      0x0002001C
#నిర్వచించు SPI_CRCPR    0x00020020
#నిర్వచించు SPI_RXCRCR   0x00020024
#నిర్వచించు SPI_TXCRCR   0x00020028

// defining SPI_CR1 register
#నిర్వచించు SPI_CPHA	      (1 << 0)
#నిర్వచించు SPI_CPOL	      (1 << 1)
#నిర్వచించు SPI_MSTR	      (1 << 2)
#నిర్వచించు SPI_BR(x)	      (x << 3)
#నిర్వచించు SPI_SPE		      (1 << 6)
#నిర్వచించు SPI_LSBFIRST	      (1 << 7)
#నిర్వచించు SPI_SSI		      (1 << 8)
#నిర్వచించు SPI_SSM		      (1 << 9)
#నిర్వచించు SPI_RXONLY	      (1 << 10)
#నిర్వచించు SPI_CRCL	      (1 << 11)
#నిర్వచించు SPI_CCRCNEXT	      (1 << 12)
#నిర్వచించు SPI_CRCEN	      (1 << 13)
#నిర్వచించు SPI_BIDIOE	      (1 << 14)
#నిర్వచించు SPI_BIDIMODE	      (1 << 15)
#నిర్వచించు SPI_మొత్తం_బిట్లు_TX(x)  (x << 16)
#నిర్వచించు SPI_మొత్తం_బిట్లు_RX(x)  (x << 24)

// defining SPI_CR2 register
#నిర్వచించు SPI_RX_IMM_ప్రారంభం   (1 << 16)
#నిర్వచించు SPI_RX_ప్రారంభం	   (1 << 15)
#నిర్వచించు SPI_LDMA_TX	   (1 << 14)
#నిర్వచించు SPI_LDMA_RX	   (1 << 13)
#నిర్వచించు SPI_FRXTH	   (1 << 12)
#నిర్వచించు SPI_DS(x)	   (x << 8)
#నిర్వచించు SPI_TXEIE	   (1 << 7)
#నిర్వచించు SPI_RXNEIE	   (1 << 6)
#నిర్వచించు SPI_ERRIE	   (1 << 5)
#నిర్వచించు SPI_FRF		   (1 << 4)
#నిర్వచించు SPI_NSSP	   (1 << 3)
#నిర్వచించు SPI_SSOE	   (1 << 2)
#నిర్వచించు SPI_TXDMAEN	   (1 << 1)
#నిర్వచించు SPI_RXDMAEN	   (1 << 0)

//defining SR register
#నిర్వచించు SPI_FTLVL(x)	(x << 11)
#నిర్వచించు SPI_FRLVL(x)	(x << 9)
#నిర్వచించు SPI_FRE		(1 << 8)
#నిర్వచించు SPI_OVR		(1 << 6)
#నిర్వచించు SPI_MODF	(1 << 5)
#నిర్వచించు SPI_CRCERR	(1 << 4)
#నిర్వచించు TXE		(1 << 1)
#నిర్వచించు RXNE		(1 << 0)

// function prototype

శూన్య configure_spi(పూర్ణాంకం స్థానభ్రంశం);
శూన్య spi_init(శూన్య);
శూన్య సమితి_spi(పూర్ణాంకం* addr, పూర్ణాంకం val);
శూన్య bin(గుర్తులేని n);
శూన్య spi_tx_rx_ప్రారంభం(శూన్య);
శూన్య spi_enable(శూన్య);
శూన్య spi_rx_enable(శూన్య);
శూన్య flash_cmd_addr_దత్తాంశం(పూర్ణాంకం command, పూర్ణాంకం addr, పూర్ణాంకం దత్తాంశం_2);
శూన్య flash_write(పూర్ణాంకం చిరునామా, పూర్ణాంకం దత్తాంశం_2);
శూన్య flash_erase(పూర్ణాంకం చిరునామా);
పూర్ణాంకం get_spi(పూర్ణాంకం* addr);
పూర్ణాంకం బిట్టు_Extracted(పూర్ణాంకం సంఖ్య, పూర్ణాంకం k, పూర్ణాంకం p) ;
పూర్ణాంకం concat(పూర్ణాంకం x, పూర్ణాంకం y) ;
పూర్ణాంకం spi_rxne_enable(శూన్య);
పూర్ణాంకం spi_notbusy(శూన్య);
పూర్ణాంకం flash_write_enable(శూన్య);
పూర్ణాంకం flash_clear_sr(శూన్య);
పూర్ణాంకం flash_cmd_addr(పూర్ణాంకం command, పూర్ణాంకం addr);
పూర్ణాంకం flash_cmd_గమ్యం_read(పూర్ణాంకం command, పూర్ణాంకం addr);
పూర్ణాంకం flash_read(పూర్ణాంకం చిరునామా);
పూర్ణాంకం flash_cmd_read(పూర్ణాంకం command);
పూర్ణాంకం flash_స్థితి_రిజిస్టరు_read(శూన్య);
పూర్ణాంకం flash_device_id(శూన్య);

#అయితే_ముగింపు
