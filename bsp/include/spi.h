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
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SPI_H
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_H

#ಅನ್ತರ್ಭಾವ<stdlib.h>
/*By default SPI0 is enabled at initialization.
  SPI0 is not available externally in TARGET=artix7_35t*/
#ವ್ಯಾಖ್ಯಾನಿಸು SPI0_ಸ್ಥಾನಾಂತರ 0x00000000
#ವ್ಯಾಖ್ಯಾನಿಸು SPI1_ಸ್ಥಾನಾಂತರ 0x00000100
#ವ್ಯಾಖ್ಯಾನಿಸು SPI2_ಸ್ಥಾನಾಂತರ 0x00000200

#ವ್ಯಾಖ್ಯಾನಿಸು SPI_CR1	     0x00020000
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_CR2	     0x00020004
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_SR       0x00020008
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_DR1	     0x0002000C
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_DR2	     0x00020010
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_DR3	     0x00020014
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_DR4	     0x00020018
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_DR5      0x0002001C
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_CRCPR    0x00020020
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_RXCRCR   0x00020024
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_TXCRCR   0x00020028

// defining SPI_CR1 register
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_CPHA	      (1 << 0)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_CPOL	      (1 << 1)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_MSTR	      (1 << 2)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_BR(x)	      (x << 3)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_SPE		      (1 << 6)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_LSBFIRST	      (1 << 7)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_SSI		      (1 << 8)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_SSM		      (1 << 9)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_RXONLY	      (1 << 10)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_CRCL	      (1 << 11)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_CCRCNEXT	      (1 << 12)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_CRCEN	      (1 << 13)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_BIDIOE	      (1 << 14)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_BIDIMODE	      (1 << 15)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_ಒಟ್ಟು_ಬಿಟ್ಟುಗಳು_TX(x)  (x << 16)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_ಒಟ್ಟು_ಬಿಟ್ಟುಗಳು_RX(x)  (x << 24)

// defining SPI_CR2 register
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_RX_IMM_ಆರಂಭ   (1 << 16)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_RX_ಆರಂಭ	   (1 << 15)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_LDMA_TX	   (1 << 14)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_LDMA_RX	   (1 << 13)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_FRXTH	   (1 << 12)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_DS(x)	   (x << 8)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_TXEIE	   (1 << 7)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_RXNEIE	   (1 << 6)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_ERRIE	   (1 << 5)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_FRF		   (1 << 4)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_NSSP	   (1 << 3)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_SSOE	   (1 << 2)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_TXDMAEN	   (1 << 1)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_RXDMAEN	   (1 << 0)

//defining SR register
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_FTLVL(x)	(x << 11)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_FRLVL(x)	(x << 9)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_FRE		(1 << 8)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_OVR		(1 << 6)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_MODF	(1 << 5)
#ವ್ಯಾಖ್ಯಾನಿಸು SPI_CRCERR	(1 << 4)
#ವ್ಯಾಖ್ಯಾನಿಸು TXE		(1 << 1)
#ವ್ಯಾಖ್ಯಾನಿಸು RXNE		(1 << 0)

// function prototype

ಶೂನ್ಯ configure_spi(ಪೂರ್ಣಾಂಕ ಸ್ಥಾನಾಂತರ);
ಶೂನ್ಯ spi_init(ಶೂನ್ಯ);
ಶೂನ್ಯ ಗಣ_spi(ಪೂರ್ಣಾಂಕ* addr, ಪೂರ್ಣಾಂಕ val);
ಶೂನ್ಯ bin(ಚಿಹ್ನೆರಹಿತ n);
ಶೂನ್ಯ spi_tx_rx_ಆರಂಭ(ಶೂನ್ಯ);
ಶೂನ್ಯ spi_enable(ಶೂನ್ಯ);
ಶೂನ್ಯ spi_rx_enable(ಶೂನ್ಯ);
ಶೂನ್ಯ flash_cmd_addr_ದತ್ತಾಂಶ(ಪೂರ್ಣಾಂಕ command, ಪೂರ್ಣಾಂಕ addr, ಪೂರ್ಣಾಂಕ ದತ್ತಾಂಶ_2);
ಶೂನ್ಯ flash_write(ಪೂರ್ಣಾಂಕ ವಿಳಾಸ, ಪೂರ್ಣಾಂಕ ದತ್ತಾಂಶ_2);
ಶೂನ್ಯ flash_erase(ಪೂರ್ಣಾಂಕ ವಿಳಾಸ);
ಪೂರ್ಣಾಂಕ get_spi(ಪೂರ್ಣಾಂಕ* addr);
ಪೂರ್ಣಾಂಕ ಬಿಟ್_Extracted(ಪೂರ್ಣಾಂಕ ಸಂಖ್ಯೆ, ಪೂರ್ಣಾಂಕ k, ಪೂರ್ಣಾಂಕ p) ;
ಪೂರ್ಣಾಂಕ concat(ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y) ;
ಪೂರ್ಣಾಂಕ spi_rxne_enable(ಶೂನ್ಯ);
ಪೂರ್ಣಾಂಕ spi_notbusy(ಶೂನ್ಯ);
ಪೂರ್ಣಾಂಕ flash_write_enable(ಶೂನ್ಯ);
ಪೂರ್ಣಾಂಕ flash_clear_sr(ಶೂನ್ಯ);
ಪೂರ್ಣಾಂಕ flash_cmd_addr(ಪೂರ್ಣಾಂಕ command, ಪೂರ್ಣಾಂಕ addr);
ಪೂರ್ಣಾಂಕ flash_cmd_ಗಮ್ಯ_read(ಪೂರ್ಣಾಂಕ command, ಪೂರ್ಣಾಂಕ addr);
ಪೂರ್ಣಾಂಕ flash_read(ಪೂರ್ಣಾಂಕ ವಿಳಾಸ);
ಪೂರ್ಣಾಂಕ flash_cmd_read(ಪೂರ್ಣಾಂಕ command);
ಪೂರ್ಣಾಂಕ flash_ಸ್ಥಿತಿ_ರಿಜಿಸ್ಟರ್_read(ಶೂನ್ಯ);
ಪೂರ್ಣಾಂಕ flash_device_id(ಶೂನ್ಯ);

#ಆದರೆ_ಅಂತ್ಯ
