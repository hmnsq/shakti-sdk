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

#جيڪڏهن_وصف_نه_ٿيل IO_ACCESS_H           /* prevent circular inclusions */
#وصف_ڪريو IO_ACCESS_H           /* by using protection macros */

#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو

/***************************** Include Files *********************************/

#ضمن "xil_types.h"
#ضمن "log_debug.h"
#ضمن "xstatus.h"

#إذا defined (__MICROBLAZE__)
#ضمن "mb_interface.h"
#وإلا
#ضمن "xpseudo_asm.h"
#جيڪڏهن_پورو

/************************** Function Prototypes ******************************/
u16 Xil_EndianSwap16(u16 معلومات);
u32 Xil_EndianSwap32(u32 معلومات);
#جيڪڏهن_وصف_ٿيل ENABLE_SAFETY
خارجي u32 XStl_RegUpdate(u32 RegAddr, u32 RegVal);
#جيڪڏهن_پورو

/***************** Macros (Inline Functions) Definitions *********************/
#إذا defined __GNUC__
#إذا defined (__MICROBLAZE__)
#  define INST_SYNC		mbar(0)
#  define معلومات_SYNC		mbar(1)
# وإلا
#  define SYNCHRONIZE_IO	dmb()
#  define INST_SYNC		isb()
#  define معلومات_SYNC		dsb()
# endif
#وإلا
# define SYNCHRONIZE_IO
# define INST_SYNC
# define معلومات_SYNC
# define INST_SYNC
# define معلومات_SYNC
#جيڪڏهن_پورو

#إذا defined (__GNUC__) || defined (__ICCARM__) || defined (__MICROBLAZE__)
#وصف_ڪريو INLINE مضمن
#وإلا
#وصف_ڪريو INLINE __inline
#جيڪڏهن_پورو

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
ساكن INLINE uint8_t get_io8(UINTPTR Addr)
{
	أرجع *(متطاير uint8_t *) Addr;
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
ساكن INLINE uin16_t get_io16(UINTPTR Addr)
{
	أرجع *(متطاير uin16_t *) Addr;
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
ساكن INLINE uint32_t get_io32(UINTPTR Addr)
{
	أرجع *(متطاير uint32_t *) Addr;
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
ساكن INLINE uint64_t get_io64(UINTPTR Addr)
{
	أرجع *(متطاير uint64_t *) Addr;
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
ساكن INLINE فراغ سيٽ_io8(UINTPTR Addr, uint8_t قدر_2)
{
	متطاير uint8_t *LocalAddr = (متطاير uint8_t *)Addr;
	*LocalAddr = قدر_2;
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
ساكن INLINE فراغ سيٽ_io16(UINTPTR Addr, uint16_t قدر_2)
{
	متطاير uint16_t *LocalAddr = (متطاير uint16_t *)Addr;
	*LocalAddr = قدر_2;
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
ساكن INLINE فراغ سيٽ_io32(UINTPTR Addr, uint32_t قدر_2)
{
	متطاير uint32_t *LocalAddr = (متطاير uint32_t *)Addr;
	*LocalAddr = قدر_2;
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
ساكن INLINE فراغ سيٽ_io64(UINTPTR Addr, uint64_t قدر_2)
{
	متطاير uint64_t *LocalAddr = (متطاير uint64_t *)Addr;
	*LocalAddr = قدر_2;
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
ساكن INLINE u32 Xil_SecureOut32(UINTPTR Addr, u32 قدر_2)
{
	u32 ReadReg;
	u32 Read_Reg_عارضي;
	u32 حالت = (u32)FAILURE;

	Xil_Out32(Addr, قدر_2);

	ReadReg = Xil_In32(Addr);
	Read_Reg_عارضي = Xil_In32(Addr);

	إذا( (ReadReg == قدر_2) && (Read_Reg_عارضي == قدر_2) ) {
		حالت = (u32)SUCCESS;
	}

	أرجع حالت;
}

#إذا defined (__MICROBLAZE__)
#جيڪڏهن_وصف_ٿيل __LITTLE_ENDIAN__
# define Xil_In16LE	get_io16
# define Xil_In32LE	get_io32
# define Xil_Out16LE	سيٽ_io16
# define Xil_Out32LE	سيٽ_io32
# define Xil_Htons	Xil_EndianSwap16
# define Xil_Htonl	Xil_EndianSwap32
# define Xil_Ntohs	Xil_EndianSwap16
# define Xil_Ntohl	Xil_EndianSwap32
# وإلا
# define Xil_In16BE	get_io16
# define Xil_In32BE	get_io32
# define Xil_Out16BE	سيٽ_io16
# define Xil_Out32BE	سيٽ_io32
# define Xil_Htons(معلومات) (معلومات)
# define Xil_Htonl(معلومات) (معلومات)
# define Xil_Ntohs(معلومات) (معلومات)
# define Xil_Ntohl(معلومات) (معلومات)
#جيڪڏهن_پورو
#وإلا
# define Xil_In16LE	get_io16
# define Xil_In32LE	get_io32
# define Xil_Out16LE	سيٽ_io16
# define Xil_Out32LE	سيٽ_io32
# define Xil_Htons	Xil_EndianSwap16
# define Xil_Htonl	Xil_EndianSwap32
# define Xil_Ntohs	Xil_EndianSwap16
# define Xil_Ntohl	Xil_EndianSwap32
#جيڪڏهن_پورو

#إذا defined (__MICROBLAZE__)
#جيڪڏهن_وصف_ٿيل __LITTLE_ENDIAN__
ساكن INLINE u16 Xil_In16BE(UINTPTR Addr)
#وإلا
ساكن INLINE u16 Xil_In16LE(UINTPTR Addr)
#جيڪڏهن_پورو
#وإلا
ساكن INLINE u16 Xil_In16BE(UINTPTR Addr)
#جيڪڏهن_پورو
{
	u16 قدر = Xil_In16(Addr);
	أرجع Xil_EndianSwap16(قدر);
}

#إذا defined (__MICROBLAZE__)
#جيڪڏهن_وصف_ٿيل __LITTLE_ENDIAN__
ساكن INLINE u32 Xil_In32BE(UINTPTR Addr)
#وإلا
ساكن INLINE u32 Xil_In32LE(UINTPTR Addr)
#جيڪڏهن_پورو
#وإلا
ساكن INLINE u32 Xil_In32BE(UINTPTR Addr)
#جيڪڏهن_پورو
{
	u32 قدر = Xil_In32(Addr);
	أرجع Xil_EndianSwap32(قدر);
}

#إذا defined (__MICROBLAZE__)
#جيڪڏهن_وصف_ٿيل __LITTLE_ENDIAN__
ساكن INLINE فراغ Xil_Out16BE(UINTPTR Addr, u16 قدر_2)
#وإلا
ساكن INLINE فراغ Xil_Out16LE(UINTPTR Addr, u16 قدر_2)
#جيڪڏهن_پورو
#وإلا
ساكن INLINE فراغ Xil_Out16BE(UINTPTR Addr, u16 قدر_2)
#جيڪڏهن_پورو
{
	قدر_2 = Xil_EndianSwap16(قدر_2);
	Xil_Out16(Addr, قدر_2);
}

#إذا defined (__MICROBLAZE__)
#جيڪڏهن_وصف_ٿيل __LITTLE_ENDIAN__
ساكن INLINE فراغ Xil_Out32BE(UINTPTR Addr, u32 قدر_2)
#وإلا
ساكن INLINE فراغ Xil_Out32LE(UINTPTR Addr, u32 قدر_2)
#جيڪڏهن_پورو
#وإلا
ساكن INLINE فراغ Xil_Out32BE(UINTPTR Addr, u32 قدر_2)
#جيڪڏهن_پورو
{
	قدر_2 = Xil_EndianSwap32(قدر_2);
	Xil_Out32(Addr, قدر_2);
}

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو /* end of protection macro */
/**
* @} End of "addtogroup common_io_interfacing_apis".
*/

