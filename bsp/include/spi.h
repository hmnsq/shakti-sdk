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
#अगर_अघोषित SPI_H
#घोषणा SPI_H

#समावेश<stdlib.h>
/*By default SPI0 is enabled at initialization.
  SPI0 is not available externally in TARGET=artix7_35t*/
#घोषणा SPI0_OFFSET 0x00000000
#घोषणा SPI1_OFFSET 0x00000100
#घोषणा SPI2_OFFSET 0x00000200

#घोषणा SPI_CR1	     0x00020000
#घोषणा SPI_CR2	     0x00020004
#घोषणा SPI_SR       0x00020008
#घोषणा SPI_DR1	     0x0002000C
#घोषणा SPI_DR2	     0x00020010
#घोषणा SPI_DR3	     0x00020014
#घोषणा SPI_DR4	     0x00020018
#घोषणा SPI_DR5      0x0002001C
#घोषणा SPI_CRCPR    0x00020020
#घोषणा SPI_RXCRCR   0x00020024
#घोषणा SPI_TXCRCR   0x00020028

// defining SPI_CR1 register
#घोषणा SPI_CPHA	      (1 << 0)
#घोषणा SPI_CPOL	      (1 << 1)
#घोषणा SPI_MSTR	      (1 << 2)
#घोषणा SPI_BR(x)	      (x << 3)
#घोषणा SPI_SPE		      (1 << 6)
#घोषणा SPI_LSBFIRST	      (1 << 7)
#घोषणा SPI_SSI		      (1 << 8)
#घोषणा SPI_SSM		      (1 << 9)
#घोषणा SPI_RXONLY	      (1 << 10)
#घोषणा SPI_CRCL	      (1 << 11)
#घोषणा SPI_CCRCNEXT	      (1 << 12)
#घोषणा SPI_CRCEN	      (1 << 13)
#घोषणा SPI_BIDIOE	      (1 << 14)
#घोषणा SPI_BIDIMODE	      (1 << 15)
#घोषणा SPI_योग_BITS_TX(x)  (x << 16)
#घोषणा SPI_योग_BITS_RX(x)  (x << 24)

// defining SPI_CR2 register
#घोषणा SPI_RX_IMM_START   (1 << 16)
#घोषणा SPI_RX_START	   (1 << 15)
#घोषणा SPI_LDMA_TX	   (1 << 14)
#घोषणा SPI_LDMA_RX	   (1 << 13)
#घोषणा SPI_FRXTH	   (1 << 12)
#घोषणा SPI_DS(x)	   (x << 8)
#घोषणा SPI_TXEIE	   (1 << 7)
#घोषणा SPI_RXNEIE	   (1 << 6)
#घोषणा SPI_ERRIE	   (1 << 5)
#घोषणा SPI_FRF		   (1 << 4)
#घोषणा SPI_NSSP	   (1 << 3)
#घोषणा SPI_SSOE	   (1 << 2)
#घोषणा SPI_TXDMAEN	   (1 << 1)
#घोषणा SPI_RXDMAEN	   (1 << 0)

//defining SR register
#घोषणा SPI_FTLVL(x)	(x << 11)
#घोषणा SPI_FRLVL(x)	(x << 9)
#घोषणा SPI_FRE		(1 << 8)
#घोषणा SPI_OVR		(1 << 6)
#घोषणा SPI_MODF	(1 << 5)
#घोषणा SPI_CRCERR	(1 << 4)
#घोषणा TXE		(1 << 1)
#घोषणा RXNE		(1 << 0)

// function prototype

व्योम configure_spi(पूर्णांक offset);
व्योम spi_init(व्योम);
व्योम set_spi(पूर्णांक* addr, पूर्णांक val);
व्योम bin(अचिन्हित n);
व्योम spi_tx_rx_start(व्योम);
व्योम spi_enable(व्योम);
व्योम spi_rx_enable(व्योम);
व्योम flash_cmd_addr_तथ्य(पूर्णांक command, पूर्णांक addr, पूर्णांक तथ्य_2);
व्योम flash_write(पूर्णांक address, पूर्णांक तथ्य_2);
व्योम flash_erase(पूर्णांक address);
पूर्णांक get_spi(पूर्णांक* addr);
पूर्णांक bitExtracted(पूर्णांक संख्या, पूर्णांक k, पूर्णांक p) ;
पूर्णांक concat(पूर्णांक x, पूर्णांक y) ;
पूर्णांक spi_rxne_enable(व्योम);
पूर्णांक spi_notbusy(व्योम);
पूर्णांक flash_write_enable(व्योम);
पूर्णांक flash_clear_sr(व्योम);
पूर्णांक flash_cmd_addr(पूर्णांक command, पूर्णांक addr);
पूर्णांक flash_cmd_to_read(पूर्णांक command, पूर्णांक addr);
पूर्णांक flash_read(पूर्णांक address);
पूर्णांक flash_cmd_read(पूर्णांक command);
पूर्णांक flash_status_register_read(व्योम);
पूर्णांक flash_device_id(व्योम);

#पूर्ण_अगर
