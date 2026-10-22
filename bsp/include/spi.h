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
#यदि_अपरिभाषितम् SPI_H
#परिभाषय SPI_H

#अन्तर्भाव<stdlib.h>
/*By default SPI0 is enabled at initialization.
  SPI0 is not available externally in TARGET=artix7_35t*/
#परिभाषय SPI0_विस्थापनम् 0x00000000
#परिभाषय SPI1_विस्थापनम् 0x00000100
#परिभाषय SPI2_विस्थापनम् 0x00000200

#परिभाषय SPI_CR1	     0x00020000
#परिभाषय SPI_CR2	     0x00020004
#परिभाषय SPI_SR       0x00020008
#परिभाषय SPI_DR1	     0x0002000C
#परिभाषय SPI_DR2	     0x00020010
#परिभाषय SPI_DR3	     0x00020014
#परिभाषय SPI_DR4	     0x00020018
#परिभाषय SPI_DR5      0x0002001C
#परिभाषय SPI_CRCPR    0x00020020
#परिभाषय SPI_RXCRCR   0x00020024
#परिभाषय SPI_TXCRCR   0x00020028

// defining SPI_CR1 register
#परिभाषय SPI_CPHA	      (1 << 0)
#परिभाषय SPI_CPOL	      (1 << 1)
#परिभाषय SPI_MSTR	      (1 << 2)
#परिभाषय SPI_BR(x)	      (x << 3)
#परिभाषय SPI_SPE		      (1 << 6)
#परिभाषय SPI_LSBFIRST	      (1 << 7)
#परिभाषय SPI_SSI		      (1 << 8)
#परिभाषय SPI_SSM		      (1 << 9)
#परिभाषय SPI_RXONLY	      (1 << 10)
#परिभाषय SPI_CRCL	      (1 << 11)
#परिभाषय SPI_CCRCNEXT	      (1 << 12)
#परिभाषय SPI_CRCEN	      (1 << 13)
#परिभाषय SPI_BIDIOE	      (1 << 14)
#परिभाषय SPI_BIDIMODE	      (1 << 15)
#परिभाषय SPI_योग_द्वयङ्काः_TX(x)  (x << 16)
#परिभाषय SPI_योग_द्वयङ्काः_RX(x)  (x << 24)

// defining SPI_CR2 register
#परिभाषय SPI_RX_IMM_START   (1 << 16)
#परिभाषय SPI_RX_START	   (1 << 15)
#परिभाषय SPI_LDMA_TX	   (1 << 14)
#परिभाषय SPI_LDMA_RX	   (1 << 13)
#परिभाषय SPI_FRXTH	   (1 << 12)
#परिभाषय SPI_DS(x)	   (x << 8)
#परिभाषय SPI_TXEIE	   (1 << 7)
#परिभाषय SPI_RXNEIE	   (1 << 6)
#परिभाषय SPI_ERRIE	   (1 << 5)
#परिभाषय SPI_FRF		   (1 << 4)
#परिभाषय SPI_NSSP	   (1 << 3)
#परिभाषय SPI_SSOE	   (1 << 2)
#परिभाषय SPI_TXDMAEN	   (1 << 1)
#परिभाषय SPI_RXDMAEN	   (1 << 0)

//defining SR register
#परिभाषय SPI_FTLVL(x)	(x << 11)
#परिभाषय SPI_FRLVL(x)	(x << 9)
#परिभाषय SPI_FRE		(1 << 8)
#परिभाषय SPI_OVR		(1 << 6)
#परिभाषय SPI_MODF	(1 << 5)
#परिभाषय SPI_CRCERR	(1 << 4)
#परिभाषय TXE		(1 << 1)
#परिभाषय RXNE		(1 << 0)

// function prototype

शून्य configure_spi(पूर्णाङ्क विस्थापनम्);
शून्य spi_init(शून्य);
शून्य समुच्चयः_spi(पूर्णाङ्क* addr, पूर्णाङ्क val);
शून्य bin(अचिह्नित n);
शून्य spi_tx_rx_start(शून्य);
शून्य spi_enable(शून्य);
शून्य spi_rx_enable(शून्य);
शून्य flash_cmd_addr_दत्त(पूर्णाङ्क command, पूर्णाङ्क addr, पूर्णाङ्क दत्त_2);
शून्य flash_write(पूर्णाङ्क स्थानाङ्कः, पूर्णाङ्क दत्त_2);
शून्य flash_erase(पूर्णाङ्क स्थानाङ्कः);
पूर्णाङ्क get_spi(पूर्णाङ्क* addr);
पूर्णाङ्क bitExtracted(पूर्णाङ्क सङ्ख्या, पूर्णाङ्क k, पूर्णाङ्क p) ;
पूर्णाङ्क concat(पूर्णाङ्क x, पूर्णाङ्क y) ;
पूर्णाङ्क spi_rxne_enable(शून्य);
पूर्णाङ्क spi_notbusy(शून्य);
पूर्णाङ्क flash_write_enable(शून्य);
पूर्णाङ्क flash_clear_sr(शून्य);
पूर्णाङ्क flash_cmd_addr(पूर्णाङ्क command, पूर्णाङ्क addr);
पूर्णाङ्क flash_cmd_गन्तव्यम्_read(पूर्णाङ्क command, पूर्णाङ्क addr);
पूर्णाङ्क flash_read(पूर्णाङ्क स्थानाङ्कः);
पूर्णाङ्क flash_cmd_read(पूर्णाङ्क command);
पूर्णाङ्क flash_स्थितिः_पञ्जिकाकोशः_read(शून्य);
पूर्णाङ्क flash_device_id(शून्य);

#यदि_अन्तः
