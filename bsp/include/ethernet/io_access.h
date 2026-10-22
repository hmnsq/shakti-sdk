/**************************************************************************
 * Project           	         : shakti devt board
 * Name of the file	         : io_access.h
 * Brief Description of file     : header file for accessing io addresses.
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
 * @file io_access.h
 * @brief  Header file for accessing io lines
 * @detail this is the header file for accessing all io lines mapped to shakti core.
 */

#నిర్వచితం_కాకపోతే IO_ACCESS_H           /* prevent circular inclusions */
#నిర్వచించు IO_ACCESS_H           /* by using protection macros */

#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు

/***************************** Include Files *********************************/

#అన్తర్భావ "xil_types.h"
#అన్తర్భావ "log_debug.h"
#అన్తర్భావ "xstatus.h"

#ఒకవేళ defined (__MICROBLAZE__)
#అన్తర్భావ "mb_interface.h"
#లేకపోతే
#అన్తర్భావ "xpseudo_asm.h"
#అయితే_ముగింపు

/************************** Function Prototypes ******************************/
u16 Xil_EndianSwap16(u16 దత్తాంశం);
u32 Xil_EndianSwap32(u32 దత్తాంశం);
#నిర్వచితమైతే ENABLE_SAFETY
బాహ్య u32 XStl_RegUpdate(u32 RegAddr, u32 RegVal);
#అయితే_ముగింపు

/***************** Macros (Inline Functions) Definitions *********************/
#ఒకవేళ defined __GNUC__
#ఒకవేళ defined (__MICROBLAZE__)
#  define INST_SYNC		mbar(0)
#  define దత్తాంశం_SYNC		mbar(1)
# లేకపోతే
#  define SYNCHRONIZE_IO	dmb()
#  define INST_SYNC		isb()
#  define దత్తాంశం_SYNC		dsb()
# endif
#లేకపోతే
# define SYNCHRONIZE_IO
# define INST_SYNC
# define దత్తాంశం_SYNC
# define INST_SYNC
# define దత్తాంశం_SYNC
#అయితే_ముగింపు

#ఒకవేళ defined (__GNUC__) || defined (__ICCARM__) || defined (__MICROBLAZE__)
#నిర్వచించు INLINE అంతఃవరుస
#లేకపోతే
#నిర్వచించు INLINE __inline
#అయితే_ముగింపు

/*****************************************************************************/
/**
*
* @brief    Performs an input operation for a memory location by reading
*           from the specified address and returning the 8 bit Value read from
*            that address.
*
* @param	Addr: contains the address to perform the input operation
*
* @return	The 8 bit Value read from the specified input address.

*
******************************************************************************/
స్థిర INLINE uint8_t get_io8(UINTPTR Addr)
{
	తిరిగి *(అస్థిర uint8_t *) Addr;
}

/*****************************************************************************/
/**
*
* @brief    Performs an input operation for a memory location by reading from
*           the specified address and returning the 16 bit Value read from that
*           address.
*
* @param	Addr: contains the address to perform the input operation
*
* @return	The 16 bit Value read from the specified input address.
*
******************************************************************************/
స్థిర INLINE uin16_t get_io16(UINTPTR Addr)
{
	తిరిగి *(అస్థిర uin16_t *) Addr;
}

/*****************************************************************************/
/**
*
* @brief    Performs an input operation for a memory location by
*           reading from the specified address and returning the 32 bit Value
*           read  from that address.
*
* @param	Addr: contains the address to perform the input operation
*
* @return	The 32 bit Value read from the specified input address.
*
******************************************************************************/
స్థిర INLINE uint32_t get_io32(UINTPTR Addr)
{
	తిరిగి *(అస్థిర uint32_t *) Addr;
}

/*****************************************************************************/
/**
*
* @brief     Performs an input operation for a memory location by reading the
*            64 bit Value read  from that address.
*
*
* @param	Addr: contains the address to perform the input operation
*
* @return	The 64 bit Value read from the specified input address.
*
******************************************************************************/
స్థిర INLINE uint64_t get_io64(UINTPTR Addr)
{
	తిరిగి *(అస్థిర uint64_t *) Addr;
}

/*****************************************************************************/
/**
*
* @brief    Performs an output operation for an memory location by
*           writing the 8 bit Value to the the specified address.
*
* @param	Addr: contains the address to perform the output operation
* @param	Value: contains the 8 bit Value to be written at the specified
*           address.
*
* @return	None.
*
******************************************************************************/
స్థిర INLINE శూన్య సమితి_io8(UINTPTR Addr, uint8_t విలువ_2)
{
	అస్థిర uint8_t *LocalAddr = (అస్థిర uint8_t *)Addr;
	*LocalAddr = విలువ_2;
}

/*****************************************************************************/
/**
*
* @brief    Performs an output operation for a memory location by writing the
*            16 bit Value to the the specified address.
*
* @param	Addr contains the address to perform the output operation
* @param	Value contains the Value to be written at the specified address.
*
* @return	None.
*
******************************************************************************/
స్థిర INLINE శూన్య సమితి_io16(UINTPTR Addr, uint16_t విలువ_2)
{
	అస్థిర uint16_t *LocalAddr = (అస్థిర uint16_t *)Addr;
	*LocalAddr = విలువ_2;
}

/*****************************************************************************/
/**
*
* @brief    Performs an output operation for a memory location by writing the
*           32 bit Value to the the specified address.
*
* @param	Addr contains the address to perform the output operation
* @param	Value contains the 32 bit Value to be written at the specified
*           address.
*
* @return	None.
*
******************************************************************************/
స్థిర INLINE శూన్య సమితి_io32(UINTPTR Addr, uint32_t విలువ_2)
{
	అస్థిర uint32_t *LocalAddr = (అస్థిర uint32_t *)Addr;
	*LocalAddr = విలువ_2;
}

/*****************************************************************************/
/**
*
* @brief    Performs an output operation for a memory location by writing the
*           64 bit Value to the the specified address.
*
* @param	Addr contains the address to perform the output operation
* @param	Value contains 64 bit Value to be written at the specified address.
*
* @return	None.
*
******************************************************************************/
స్థిర INLINE శూన్య సమితి_io64(UINTPTR Addr, uint64_t విలువ_2)
{
	అస్థిర uint64_t *LocalAddr = (అస్థిర uint64_t *)Addr;
	*LocalAddr = విలువ_2;
}

/*****************************************************************************/
/**
 *
 * @brief	Performs an output operation for a memory location by writing the
 *       	32 bit Value to the the specified address and then reading it
 *       	back to verify the value written in the register.
 *
 * @param	Addr contains the address to perform the output operation
 * @param	Value contains 32 bit Value to be written at the specified address
 *
 * @return	Returns Status
 *        	- SUCCESS on success
 *        	- FAILURE on failure
 *
 *****************************************************************************/
స్థిర INLINE u32 Xil_SecureOut32(UINTPTR Addr, u32 విలువ_2)
{
	u32 ReadReg;
	u32 Read_Reg_తాత్కాలిక;
	u32 స్థితి_2 = (u32)FAILURE;

	Xil_Out32(Addr, విలువ_2);

	ReadReg = Xil_In32(Addr);
	Read_Reg_తాత్కాలిక = Xil_In32(Addr);

	ఒకవేళ( (ReadReg == విలువ_2) && (Read_Reg_తాత్కాలిక == విలువ_2) ) {
		స్థితి_2 = (u32)SUCCESS;
	}

	తిరిగి స్థితి_2;
}

#ఒకవేళ defined (__MICROBLAZE__)
#నిర్వచితమైతే __LITTLE_ENDIAN__
# define Xil_In16LE	get_io16
# define Xil_In32LE	get_io32
# define Xil_Out16LE	సమితి_io16
# define Xil_Out32LE	సమితి_io32
# define Xil_Htons	Xil_EndianSwap16
# define Xil_Htonl	Xil_EndianSwap32
# define Xil_Ntohs	Xil_EndianSwap16
# define Xil_Ntohl	Xil_EndianSwap32
# లేకపోతే
# define Xil_In16BE	get_io16
# define Xil_In32BE	get_io32
# define Xil_Out16BE	సమితి_io16
# define Xil_Out32BE	సమితి_io32
# define Xil_Htons(దత్తాంశం) (దత్తాంశం)
# define Xil_Htonl(దత్తాంశం) (దత్తాంశం)
# define Xil_Ntohs(దత్తాంశం) (దత్తాంశం)
# define Xil_Ntohl(దత్తాంశం) (దత్తాంశం)
#అయితే_ముగింపు
#లేకపోతే
# define Xil_In16LE	get_io16
# define Xil_In32LE	get_io32
# define Xil_Out16LE	సమితి_io16
# define Xil_Out32LE	సమితి_io32
# define Xil_Htons	Xil_EndianSwap16
# define Xil_Htonl	Xil_EndianSwap32
# define Xil_Ntohs	Xil_EndianSwap16
# define Xil_Ntohl	Xil_EndianSwap32
#అయితే_ముగింపు

#ఒకవేళ defined (__MICROBLAZE__)
#నిర్వచితమైతే __LITTLE_ENDIAN__
స్థిర INLINE u16 Xil_In16BE(UINTPTR Addr)
#లేకపోతే
స్థిర INLINE u16 Xil_In16LE(UINTPTR Addr)
#అయితే_ముగింపు
#లేకపోతే
స్థిర INLINE u16 Xil_In16BE(UINTPTR Addr)
#అయితే_ముగింపు
{
	u16 విలువ = Xil_In16(Addr);
	తిరిగి Xil_EndianSwap16(విలువ);
}

#ఒకవేళ defined (__MICROBLAZE__)
#నిర్వచితమైతే __LITTLE_ENDIAN__
స్థిర INLINE u32 Xil_In32BE(UINTPTR Addr)
#లేకపోతే
స్థిర INLINE u32 Xil_In32LE(UINTPTR Addr)
#అయితే_ముగింపు
#లేకపోతే
స్థిర INLINE u32 Xil_In32BE(UINTPTR Addr)
#అయితే_ముగింపు
{
	u32 విలువ = Xil_In32(Addr);
	తిరిగి Xil_EndianSwap32(విలువ);
}

#ఒకవేళ defined (__MICROBLAZE__)
#నిర్వచితమైతే __LITTLE_ENDIAN__
స్థిర INLINE శూన్య Xil_Out16BE(UINTPTR Addr, u16 విలువ_2)
#లేకపోతే
స్థిర INLINE శూన్య Xil_Out16LE(UINTPTR Addr, u16 విలువ_2)
#అయితే_ముగింపు
#లేకపోతే
స్థిర INLINE శూన్య Xil_Out16BE(UINTPTR Addr, u16 విలువ_2)
#అయితే_ముగింపు
{
	విలువ_2 = Xil_EndianSwap16(విలువ_2);
	Xil_Out16(Addr, విలువ_2);
}

#ఒకవేళ defined (__MICROBLAZE__)
#నిర్వచితమైతే __LITTLE_ENDIAN__
స్థిర INLINE శూన్య Xil_Out32BE(UINTPTR Addr, u32 విలువ_2)
#లేకపోతే
స్థిర INLINE శూన్య Xil_Out32LE(UINTPTR Addr, u32 విలువ_2)
#అయితే_ముగింపు
#లేకపోతే
స్థిర INLINE శూన్య Xil_Out32BE(UINTPTR Addr, u32 విలువ_2)
#అయితే_ముగింపు
{
	విలువ_2 = Xil_EndianSwap32(విలువ_2);
	Xil_Out32(Addr, విలువ_2);
}

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు /* end of protection macro */
/**
* @} End of "addtogroup common_io_interfacing_apis".
*/

