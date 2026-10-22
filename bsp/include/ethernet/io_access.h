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

#اگر_تعریف_نشده IO_ACCESS_H           /* prevent circular inclusions */
#تعریف_کن IO_ACCESS_H           /* by using protection macros */

#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر

/***************************** Include Files *********************************/

#ضمن "xil_types.h"
#ضمن "log_debug.h"
#ضمن "xstatus.h"

#إذا defined (__MICROBLAZE__)
#ضمن "mb_interface.h"
#وإلا
#ضمن "xpseudo_asm.h"
#پایان_اگر

/************************** Function Prototypes ******************************/
u16 Xil_EndianSwap16(u16 داده);
u32 Xil_EndianSwap32(u32 داده);
#اگر_تعریف_شده ENABLE_SAFETY
خارجي u32 XStl_RegUpdate(u32 RegAddr, u32 RegVal);
#پایان_اگر

/***************** Macros (Inline Functions) Definitions *********************/
#إذا defined __GNUC__
#إذا defined (__MICROBLAZE__)
#  define INST_SYNC		mbar(0)
#  define داده_SYNC		mbar(1)
# وإلا
#  define SYNCHRONIZE_IO	dmb()
#  define INST_SYNC		isb()
#  define داده_SYNC		dsb()
# endif
#وإلا
# define SYNCHRONIZE_IO
# define INST_SYNC
# define داده_SYNC
# define INST_SYNC
# define داده_SYNC
#پایان_اگر

#إذا defined (__GNUC__) || defined (__ICCARM__) || defined (__MICROBLAZE__)
#تعریف_کن INLINE مضمن
#وإلا
#تعریف_کن INLINE __inline
#پایان_اگر

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
ساكن INLINE فراغ مجموعه_io8(UINTPTR Addr, uint8_t مقدار_2)
{
	متطاير uint8_t *LocalAddr = (متطاير uint8_t *)Addr;
	*LocalAddr = مقدار_2;
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
ساكن INLINE فراغ مجموعه_io16(UINTPTR Addr, uint16_t مقدار_2)
{
	متطاير uint16_t *LocalAddr = (متطاير uint16_t *)Addr;
	*LocalAddr = مقدار_2;
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
ساكن INLINE فراغ مجموعه_io32(UINTPTR Addr, uint32_t مقدار_2)
{
	متطاير uint32_t *LocalAddr = (متطاير uint32_t *)Addr;
	*LocalAddr = مقدار_2;
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
ساكن INLINE فراغ مجموعه_io64(UINTPTR Addr, uint64_t مقدار_2)
{
	متطاير uint64_t *LocalAddr = (متطاير uint64_t *)Addr;
	*LocalAddr = مقدار_2;
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
ساكن INLINE u32 Xil_SecureOut32(UINTPTR Addr, u32 مقدار_2)
{
	u32 ReadReg;
	u32 Read_Reg_موقت;
	u32 وضعیت = (u32)FAILURE;

	Xil_Out32(Addr, مقدار_2);

	ReadReg = Xil_In32(Addr);
	Read_Reg_موقت = Xil_In32(Addr);

	إذا( (ReadReg == مقدار_2) && (Read_Reg_موقت == مقدار_2) ) {
		وضعیت = (u32)SUCCESS;
	}

	أرجع وضعیت;
}

#إذا defined (__MICROBLAZE__)
#اگر_تعریف_شده __LITTLE_ENDIAN__
# define Xil_In16LE	get_io16
# define Xil_In32LE	get_io32
# define Xil_Out16LE	مجموعه_io16
# define Xil_Out32LE	مجموعه_io32
# define Xil_Htons	Xil_EndianSwap16
# define Xil_Htonl	Xil_EndianSwap32
# define Xil_Ntohs	Xil_EndianSwap16
# define Xil_Ntohl	Xil_EndianSwap32
# وإلا
# define Xil_In16BE	get_io16
# define Xil_In32BE	get_io32
# define Xil_Out16BE	مجموعه_io16
# define Xil_Out32BE	مجموعه_io32
# define Xil_Htons(داده) (داده)
# define Xil_Htonl(داده) (داده)
# define Xil_Ntohs(داده) (داده)
# define Xil_Ntohl(داده) (داده)
#پایان_اگر
#وإلا
# define Xil_In16LE	get_io16
# define Xil_In32LE	get_io32
# define Xil_Out16LE	مجموعه_io16
# define Xil_Out32LE	مجموعه_io32
# define Xil_Htons	Xil_EndianSwap16
# define Xil_Htonl	Xil_EndianSwap32
# define Xil_Ntohs	Xil_EndianSwap16
# define Xil_Ntohl	Xil_EndianSwap32
#پایان_اگر

#إذا defined (__MICROBLAZE__)
#اگر_تعریف_شده __LITTLE_ENDIAN__
ساكن INLINE u16 Xil_In16BE(UINTPTR Addr)
#وإلا
ساكن INLINE u16 Xil_In16LE(UINTPTR Addr)
#پایان_اگر
#وإلا
ساكن INLINE u16 Xil_In16BE(UINTPTR Addr)
#پایان_اگر
{
	u16 مقدار = Xil_In16(Addr);
	أرجع Xil_EndianSwap16(مقدار);
}

#إذا defined (__MICROBLAZE__)
#اگر_تعریف_شده __LITTLE_ENDIAN__
ساكن INLINE u32 Xil_In32BE(UINTPTR Addr)
#وإلا
ساكن INLINE u32 Xil_In32LE(UINTPTR Addr)
#پایان_اگر
#وإلا
ساكن INLINE u32 Xil_In32BE(UINTPTR Addr)
#پایان_اگر
{
	u32 مقدار = Xil_In32(Addr);
	أرجع Xil_EndianSwap32(مقدار);
}

#إذا defined (__MICROBLAZE__)
#اگر_تعریف_شده __LITTLE_ENDIAN__
ساكن INLINE فراغ Xil_Out16BE(UINTPTR Addr, u16 مقدار_2)
#وإلا
ساكن INLINE فراغ Xil_Out16LE(UINTPTR Addr, u16 مقدار_2)
#پایان_اگر
#وإلا
ساكن INLINE فراغ Xil_Out16BE(UINTPTR Addr, u16 مقدار_2)
#پایان_اگر
{
	مقدار_2 = Xil_EndianSwap16(مقدار_2);
	Xil_Out16(Addr, مقدار_2);
}

#إذا defined (__MICROBLAZE__)
#اگر_تعریف_شده __LITTLE_ENDIAN__
ساكن INLINE فراغ Xil_Out32BE(UINTPTR Addr, u32 مقدار_2)
#وإلا
ساكن INLINE فراغ Xil_Out32LE(UINTPTR Addr, u32 مقدار_2)
#پایان_اگر
#وإلا
ساكن INLINE فراغ Xil_Out32BE(UINTPTR Addr, u32 مقدار_2)
#پایان_اگر
{
	مقدار_2 = Xil_EndianSwap32(مقدار_2);
	Xil_Out32(Addr, مقدار_2);
}

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر /* end of protection macro */
/**
* @} End of "addtogroup common_io_interfacing_apis".
*/

