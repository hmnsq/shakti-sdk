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
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SPI_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_H

#ਅਨ੍ਤਰ੍ਭਾਵ<stdlib.h>
/*By default SPI0 is enabled at initialization.
  SPI0 is not available externally in TARGET=artix7_35t*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI0_ਵਿੱਥ 0x00000000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI1_ਵਿੱਥ 0x00000100
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI2_ਵਿੱਥ 0x00000200

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_CR1	     0x00020000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_CR2	     0x00020004
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_SR       0x00020008
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_DR1	     0x0002000C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_DR2	     0x00020010
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_DR3	     0x00020014
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_DR4	     0x00020018
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_DR5      0x0002001C
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_CRCPR    0x00020020
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_RXCRCR   0x00020024
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_TXCRCR   0x00020028

// defining SPI_CR1 register
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_CPHA	      (1 << 0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_CPOL	      (1 << 1)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_MSTR	      (1 << 2)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_BR(x)	      (x << 3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_SPE		      (1 << 6)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_LSBFIRST	      (1 << 7)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_SSI		      (1 << 8)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_SSM		      (1 << 9)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_RXONLY	      (1 << 10)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_CRCL	      (1 << 11)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_CCRCNEXT	      (1 << 12)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_CRCEN	      (1 << 13)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_BIDIOE	      (1 << 14)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_BIDIMODE	      (1 << 15)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_ਕੁੱਲ_ਬਿੱਟ_TX(x)  (x << 16)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_ਕੁੱਲ_ਬਿੱਟ_RX(x)  (x << 24)

// defining SPI_CR2 register
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_RX_IMM_ਸ਼ੁਰੂ   (1 << 16)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_RX_ਸ਼ੁਰੂ	   (1 << 15)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_LDMA_TX	   (1 << 14)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_LDMA_RX	   (1 << 13)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_FRXTH	   (1 << 12)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_DS(x)	   (x << 8)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_TXEIE	   (1 << 7)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_RXNEIE	   (1 << 6)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_ERRIE	   (1 << 5)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_FRF		   (1 << 4)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_NSSP	   (1 << 3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_SSOE	   (1 << 2)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_TXDMAEN	   (1 << 1)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_RXDMAEN	   (1 << 0)

//defining SR register
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_FTLVL(x)	(x << 11)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_FRLVL(x)	(x << 9)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_FRE		(1 << 8)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_OVR		(1 << 6)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_MODF	(1 << 5)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPI_CRCERR	(1 << 4)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TXE		(1 << 1)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RXNE		(1 << 0)

// function prototype

ਖਾਲੀ configure_spi(ਪੂਰਨ ਵਿੱਥ);
ਖਾਲੀ spi_init(ਖਾਲੀ);
ਖਾਲੀ ਸੈੱਟ_spi(ਪੂਰਨ* addr, ਪੂਰਨ val);
ਖਾਲੀ bin(ਬਿਨਾਨਿਸ਼ਾਨੀ n);
ਖਾਲੀ spi_tx_rx_ਸ਼ੁਰੂ(ਖਾਲੀ);
ਖਾਲੀ spi_enable(ਖਾਲੀ);
ਖਾਲੀ spi_rx_enable(ਖਾਲੀ);
ਖਾਲੀ flash_cmd_addr_ਅੰਕੜੇ(ਪੂਰਨ command, ਪੂਰਨ addr, ਪੂਰਨ ਅੰਕੜੇ_2);
ਖਾਲੀ flash_write(ਪੂਰਨ ਪਤਾ, ਪੂਰਨ ਅੰਕੜੇ_2);
ਖਾਲੀ flash_erase(ਪੂਰਨ ਪਤਾ);
ਪੂਰਨ get_spi(ਪੂਰਨ* addr);
ਪੂਰਨ ਦੋਆਧਾਰੀ_ਅੰਕ_Extracted(ਪੂਰਨ ਸੰਖਿਆ, ਪੂਰਨ k, ਪੂਰਨ p) ;
ਪੂਰਨ concat(ਪੂਰਨ x, ਪੂਰਨ y) ;
ਪੂਰਨ spi_rxne_enable(ਖਾਲੀ);
ਪੂਰਨ spi_notbusy(ਖਾਲੀ);
ਪੂਰਨ flash_write_enable(ਖਾਲੀ);
ਪੂਰਨ flash_clear_sr(ਖਾਲੀ);
ਪੂਰਨ flash_cmd_addr(ਪੂਰਨ command, ਪੂਰਨ addr);
ਪੂਰਨ flash_cmd_ਮੰਜ਼ਿਲ_read(ਪੂਰਨ command, ਪੂਰਨ addr);
ਪੂਰਨ flash_read(ਪੂਰਨ ਪਤਾ);
ਪੂਰਨ flash_cmd_read(ਪੂਰਨ command);
ਪੂਰਨ flash_ਸਥਿਤੀ_ਰਜਿਸਟਰ_read(ਖਾਲੀ);
ਪੂਰਨ flash_device_id(ਖਾਲੀ);

#ਜੇ_ਅੰਤ
