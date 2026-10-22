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
#جے_بنا_تعریف SPI_H
#تعریف_کرو SPI_H

#ضمن<stdlib.h>
/*By default SPI0 is enabled at initialization.
  SPI0 is not available externally in TARGET=artix7_35t*/
#تعریف_کرو SPI0_وتھ 0x00000000
#تعریف_کرو SPI1_وتھ 0x00000100
#تعریف_کرو SPI2_وتھ 0x00000200

#تعریف_کرو SPI_CR1	     0x00020000
#تعریف_کرو SPI_CR2	     0x00020004
#تعریف_کرو SPI_SR       0x00020008
#تعریف_کرو SPI_DR1	     0x0002000C
#تعریف_کرو SPI_DR2	     0x00020010
#تعریف_کرو SPI_DR3	     0x00020014
#تعریف_کرو SPI_DR4	     0x00020018
#تعریف_کرو SPI_DR5      0x0002001C
#تعریف_کرو SPI_CRCPR    0x00020020
#تعریف_کرو SPI_RXCRCR   0x00020024
#تعریف_کرو SPI_TXCRCR   0x00020028

// defining SPI_CR1 register
#تعریف_کرو SPI_CPHA	      (1 << 0)
#تعریف_کرو SPI_CPOL	      (1 << 1)
#تعریف_کرو SPI_MSTR	      (1 << 2)
#تعریف_کرو SPI_BR(x)	      (x << 3)
#تعریف_کرو SPI_SPE		      (1 << 6)
#تعریف_کرو SPI_LSBFIRST	      (1 << 7)
#تعریف_کرو SPI_SSI		      (1 << 8)
#تعریف_کرو SPI_SSM		      (1 << 9)
#تعریف_کرو SPI_RXONLY	      (1 << 10)
#تعریف_کرو SPI_CRCL	      (1 << 11)
#تعریف_کرو SPI_CCRCNEXT	      (1 << 12)
#تعریف_کرو SPI_CRCEN	      (1 << 13)
#تعریف_کرو SPI_BIDIOE	      (1 << 14)
#تعریف_کرو SPI_BIDIMODE	      (1 << 15)
#تعریف_کرو SPI_کل_بٹ_TX(x)  (x << 16)
#تعریف_کرو SPI_کل_بٹ_RX(x)  (x << 24)

// defining SPI_CR2 register
#تعریف_کرو SPI_RX_IMM_شروع   (1 << 16)
#تعریف_کرو SPI_RX_شروع	   (1 << 15)
#تعریف_کرو SPI_LDMA_TX	   (1 << 14)
#تعریف_کرو SPI_LDMA_RX	   (1 << 13)
#تعریف_کرو SPI_FRXTH	   (1 << 12)
#تعریف_کرو SPI_DS(x)	   (x << 8)
#تعریف_کرو SPI_TXEIE	   (1 << 7)
#تعریف_کرو SPI_RXNEIE	   (1 << 6)
#تعریف_کرو SPI_ERRIE	   (1 << 5)
#تعریف_کرو SPI_FRF		   (1 << 4)
#تعریف_کرو SPI_NSSP	   (1 << 3)
#تعریف_کرو SPI_SSOE	   (1 << 2)
#تعریف_کرو SPI_TXDMAEN	   (1 << 1)
#تعریف_کرو SPI_RXDMAEN	   (1 << 0)

//defining SR register
#تعریف_کرو SPI_FTLVL(x)	(x << 11)
#تعریف_کرو SPI_FRLVL(x)	(x << 9)
#تعریف_کرو SPI_FRE		(1 << 8)
#تعریف_کرو SPI_OVR		(1 << 6)
#تعریف_کرو SPI_MODF	(1 << 5)
#تعریف_کرو SPI_CRCERR	(1 << 4)
#تعریف_کرو TXE		(1 << 1)
#تعریف_کرو RXNE		(1 << 0)

// function prototype

فراغ configure_spi(صحيح وتھ);
فراغ spi_init(فراغ);
فراغ سیٹ_spi(صحيح* addr, صحيح val);
فراغ bin(بنانشانی n);
فراغ spi_tx_rx_شروع(فراغ);
فراغ spi_enable(فراغ);
فراغ spi_rx_enable(فراغ);
فراغ flash_cmd_addr_انکڑے(صحيح command, صحيح addr, صحيح انکڑے_2);
فراغ flash_write(صحيح پتہ, صحيح انکڑے_2);
فراغ flash_erase(صحيح پتہ);
صحيح get_spi(صحيح* addr);
صحيح ثنائی_ہندسہ_Extracted(صحيح نمبر, صحيح k, صحيح p) ;
صحيح concat(صحيح x, صحيح y) ;
صحيح spi_rxne_enable(فراغ);
صحيح spi_notbusy(فراغ);
صحيح flash_write_enable(فراغ);
صحيح flash_clear_sr(فراغ);
صحيح flash_cmd_addr(صحيح command, صحيح addr);
صحيح flash_cmd_منزل_read(صحيح command, صحيح addr);
صحيح flash_read(صحيح پتہ);
صحيح flash_cmd_read(صحيح command);
صحيح flash_حالت_رجسٹر_read(فراغ);
صحيح flash_device_id(فراغ);

#جے_انت
