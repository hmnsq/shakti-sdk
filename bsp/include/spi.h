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
#جيڪڏهن_وصف_نه_ٿيل SPI_H
#وصف_ڪريو SPI_H

#ضمن<stdlib.h>
/*By default SPI0 is enabled at initialization.
  SPI0 is not available externally in TARGET=artix7_35t*/
#وصف_ڪريو SPI0_وٿي 0x00000000
#وصف_ڪريو SPI1_وٿي 0x00000100
#وصف_ڪريو SPI2_وٿي 0x00000200

#وصف_ڪريو SPI_CR1	     0x00020000
#وصف_ڪريو SPI_CR2	     0x00020004
#وصف_ڪريو SPI_SR       0x00020008
#وصف_ڪريو SPI_DR1	     0x0002000C
#وصف_ڪريو SPI_DR2	     0x00020010
#وصف_ڪريو SPI_DR3	     0x00020014
#وصف_ڪريو SPI_DR4	     0x00020018
#وصف_ڪريو SPI_DR5      0x0002001C
#وصف_ڪريو SPI_CRCPR    0x00020020
#وصف_ڪريو SPI_RXCRCR   0x00020024
#وصف_ڪريو SPI_TXCRCR   0x00020028

// defining SPI_CR1 register
#وصف_ڪريو SPI_CPHA	      (1 << 0)
#وصف_ڪريو SPI_CPOL	      (1 << 1)
#وصف_ڪريو SPI_MSTR	      (1 << 2)
#وصف_ڪريو SPI_BR(x)	      (x << 3)
#وصف_ڪريو SPI_SPE		      (1 << 6)
#وصف_ڪريو SPI_LSBFIRST	      (1 << 7)
#وصف_ڪريو SPI_SSI		      (1 << 8)
#وصف_ڪريو SPI_SSM		      (1 << 9)
#وصف_ڪريو SPI_RXONLY	      (1 << 10)
#وصف_ڪريو SPI_CRCL	      (1 << 11)
#وصف_ڪريو SPI_CCRCNEXT	      (1 << 12)
#وصف_ڪريو SPI_CRCEN	      (1 << 13)
#وصف_ڪريو SPI_BIDIOE	      (1 << 14)
#وصف_ڪريو SPI_BIDIMODE	      (1 << 15)
#وصف_ڪريو SPI_ڪل_بٽ_TX(x)  (x << 16)
#وصف_ڪريو SPI_ڪل_بٽ_RX(x)  (x << 24)

// defining SPI_CR2 register
#وصف_ڪريو SPI_RX_IMM_شروعات   (1 << 16)
#وصف_ڪريو SPI_RX_شروعات	   (1 << 15)
#وصف_ڪريو SPI_LDMA_TX	   (1 << 14)
#وصف_ڪريو SPI_LDMA_RX	   (1 << 13)
#وصف_ڪريو SPI_FRXTH	   (1 << 12)
#وصف_ڪريو SPI_DS(x)	   (x << 8)
#وصف_ڪريو SPI_TXEIE	   (1 << 7)
#وصف_ڪريو SPI_RXNEIE	   (1 << 6)
#وصف_ڪريو SPI_ERRIE	   (1 << 5)
#وصف_ڪريو SPI_FRF		   (1 << 4)
#وصف_ڪريو SPI_NSSP	   (1 << 3)
#وصف_ڪريو SPI_SSOE	   (1 << 2)
#وصف_ڪريو SPI_TXDMAEN	   (1 << 1)
#وصف_ڪريو SPI_RXDMAEN	   (1 << 0)

//defining SR register
#وصف_ڪريو SPI_FTLVL(x)	(x << 11)
#وصف_ڪريو SPI_FRLVL(x)	(x << 9)
#وصف_ڪريو SPI_FRE		(1 << 8)
#وصف_ڪريو SPI_OVR		(1 << 6)
#وصف_ڪريو SPI_MODF	(1 << 5)
#وصف_ڪريو SPI_CRCERR	(1 << 4)
#وصف_ڪريو TXE		(1 << 1)
#وصف_ڪريو RXNE		(1 << 0)

// function prototype

فراغ configure_spi(صحيح وٿي);
فراغ spi_init(فراغ);
فراغ سيٽ_spi(صحيح* addr, صحيح val);
فراغ bin(بنانشان n);
فراغ spi_tx_rx_شروعات(فراغ);
فراغ spi_enable(فراغ);
فراغ spi_rx_enable(فراغ);
فراغ flash_cmd_addr_معلومات(صحيح command, صحيح addr, صحيح معلومات_2);
فراغ flash_write(صحيح پتو, صحيح معلومات_2);
فراغ flash_erase(صحيح پتو);
صحيح get_spi(صحيح* addr);
صحيح ٻٽو_انگ_Extracted(صحيح عدد, صحيح k, صحيح p) ;
صحيح concat(صحيح x, صحيح y) ;
صحيح spi_rxne_enable(فراغ);
صحيح spi_notbusy(فراغ);
صحيح flash_write_enable(فراغ);
صحيح flash_clear_sr(فراغ);
صحيح flash_cmd_addr(صحيح command, صحيح addr);
صحيح flash_cmd_منزل_read(صحيح command, صحيح addr);
صحيح flash_read(صحيح پتو);
صحيح flash_cmd_read(صحيح command);
صحيح flash_حالت_رجسٽر_read(فراغ);
صحيح flash_device_id(فراغ);

#جيڪڏهن_پورو
