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
#که_نه_تعریف_شوی SPI_H
#تعریف_کړه SPI_H

#ضمن<stdlib.h>
/*By default SPI0 is enabled at initialization.
  SPI0 is not available externally in TARGET=artix7_35t*/
#تعریف_کړه SPI0_دننه_واټن 0x00000000
#تعریف_کړه SPI1_دننه_واټن 0x00000100
#تعریف_کړه SPI2_دننه_واټن 0x00000200

#تعریف_کړه SPI_CR1	     0x00020000
#تعریف_کړه SPI_CR2	     0x00020004
#تعریف_کړه SPI_SR       0x00020008
#تعریف_کړه SPI_DR1	     0x0002000C
#تعریف_کړه SPI_DR2	     0x00020010
#تعریف_کړه SPI_DR3	     0x00020014
#تعریف_کړه SPI_DR4	     0x00020018
#تعریف_کړه SPI_DR5      0x0002001C
#تعریف_کړه SPI_CRCPR    0x00020020
#تعریف_کړه SPI_RXCRCR   0x00020024
#تعریف_کړه SPI_TXCRCR   0x00020028

// defining SPI_CR1 register
#تعریف_کړه SPI_CPHA	      (1 << 0)
#تعریف_کړه SPI_CPOL	      (1 << 1)
#تعریف_کړه SPI_MSTR	      (1 << 2)
#تعریف_کړه SPI_BR(x)	      (x << 3)
#تعریف_کړه SPI_SPE		      (1 << 6)
#تعریف_کړه SPI_LSBFIRST	      (1 << 7)
#تعریف_کړه SPI_SSI		      (1 << 8)
#تعریف_کړه SPI_SSM		      (1 << 9)
#تعریف_کړه SPI_RXONLY	      (1 << 10)
#تعریف_کړه SPI_CRCL	      (1 << 11)
#تعریف_کړه SPI_CCRCNEXT	      (1 << 12)
#تعریف_کړه SPI_CRCEN	      (1 << 13)
#تعریف_کړه SPI_BIDIOE	      (1 << 14)
#تعریف_کړه SPI_BIDIMODE	      (1 << 15)
#تعریف_کړه SPI_ټول_بټونه_TX(x)  (x << 16)
#تعریف_کړه SPI_ټول_بټونه_RX(x)  (x << 24)

// defining SPI_CR2 register
#تعریف_کړه SPI_RX_IMM_پیل   (1 << 16)
#تعریف_کړه SPI_RX_پیل	   (1 << 15)
#تعریف_کړه SPI_LDMA_TX	   (1 << 14)
#تعریف_کړه SPI_LDMA_RX	   (1 << 13)
#تعریف_کړه SPI_FRXTH	   (1 << 12)
#تعریف_کړه SPI_DS(x)	   (x << 8)
#تعریف_کړه SPI_TXEIE	   (1 << 7)
#تعریف_کړه SPI_RXNEIE	   (1 << 6)
#تعریف_کړه SPI_ERRIE	   (1 << 5)
#تعریف_کړه SPI_FRF		   (1 << 4)
#تعریف_کړه SPI_NSSP	   (1 << 3)
#تعریف_کړه SPI_SSOE	   (1 << 2)
#تعریف_کړه SPI_TXDMAEN	   (1 << 1)
#تعریف_کړه SPI_RXDMAEN	   (1 << 0)

//defining SR register
#تعریف_کړه SPI_FTLVL(x)	(x << 11)
#تعریف_کړه SPI_FRLVL(x)	(x << 9)
#تعریف_کړه SPI_FRE		(1 << 8)
#تعریف_کړه SPI_OVR		(1 << 6)
#تعریف_کړه SPI_MODF	(1 << 5)
#تعریف_کړه SPI_CRCERR	(1 << 4)
#تعریف_کړه TXE		(1 << 1)
#تعریف_کړه RXNE		(1 << 0)

// function prototype

فراغ configure_spi(صحيح دننه_واټن);
فراغ spi_init(فراغ);
فراغ سېټ_spi(صحيح* addr, صحيح val);
فراغ bin(بینښه n);
فراغ spi_tx_rx_پیل(فراغ);
فراغ spi_enable(فراغ);
فراغ spi_rx_enable(فراغ);
فراغ flash_cmd_addr_معلومات(صحيح command, صحيح addr, صحيح معلومات_2);
فراغ flash_write(صحيح پته, صحيح معلومات_2);
فراغ flash_erase(صحيح پته);
صحيح get_spi(صحيح* addr);
صحيح بټ_Extracted(صحيح شمېره, صحيح k, صحيح p) ;
صحيح concat(صحيح x, صحيح y) ;
صحيح spi_rxne_enable(فراغ);
صحيح spi_notbusy(فراغ);
صحيح flash_write_enable(فراغ);
صحيح flash_clear_sr(فراغ);
صحيح flash_cmd_addr(صحيح command, صحيح addr);
صحيح flash_cmd_منزل_read(صحيح command, صحيح addr);
صحيح flash_read(صحيح پته);
صحيح flash_cmd_read(صحيح command);
صحيح flash_حالت_ثبتوونکی_read(فراغ);
صحيح flash_device_id(فراغ);

#د_که_پای
