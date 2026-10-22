/***********************************************************************
* Project           		:  shakti devt board
* Name of the file	     	:  defines.h
* Brief Description of file     :  Header file for handling traps
* Name of Author    	        :  Sathya Narayanan N
* Email ID                      :  sathya281@gmail.com

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
**************************************************************************/
/**
 * @file defines.h
 * @brief Header file for handling traps
 * @detail This is the header file to hold some risc-v system definitions.
 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ਨਿਰਧਾਰਤ_ਕਰਦਾ_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਨਿਰਧਾਰਤ_ਕਰਦਾ_H

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ REGSIZE __riscv_xlen/8

#ਜੇ __riscv_xlen == 64
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LREG ld
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SREG sd
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LREG lw
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SREG sw
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MSTATUS_MPP         0x00001800
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MSTATUS_FS          0x00006000

#ਜੇ_ਅੰਤ

