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

#اگر_غیر_تعریف_شدہ IO_ACCESS_H           /* prevent circular inclusions */
#تعریف_کرو IO_ACCESS_H           /* by using protection macros */

#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم

/***************************** Include Files *********************************/

#شامل "xil_types.h"
#شامل "log_debug.h"
#شامل "xstatus.h"

#اگر defined (__MICROBLAZE__)
#شامل "mb_interface.h"
#ورنہ
#شامل "xpseudo_asm.h"
#اگر_ختم

/************************** Function Prototypes ******************************/
u16 Xil_EndianSwap16(u16 ڈیٹا);
u32 Xil_EndianSwap32(u32 ڈیٹا);
#اگر_تعریف_شدہ ENABLE_SAFETY
خارجی u32 XStl_RegUpdate(u32 RegAddr, u32 RegVal);
#اگر_ختم

/***************** Macros (Inline Functions) Definitions *********************/
#اگر defined __GNUC__
#اگر defined (__MICROBLAZE__)
#  define INST_SYNC		mbar(0)
#  define ڈیٹا_SYNC		mbar(1)
# ورنہ
#  define SYNCHRONIZE_IO	dmb()
#  define INST_SYNC		isb()
#  define ڈیٹا_SYNC		dsb()
# endif
#ورنہ
# define SYNCHRONIZE_IO
# define INST_SYNC
# define ڈیٹا_SYNC
# define INST_SYNC
# define ڈیٹا_SYNC
#اگر_ختم

#اگر defined (__GNUC__) || defined (__ICCARM__) || defined (__MICROBLAZE__)
#تعریف_کرو INLINE اندرونی
#ورنہ
#تعریف_کرو INLINE __inline
#اگر_ختم

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
ساکن INLINE uint8_t get_io8(UINTPTR Addr)
{
	واپس *(متلون uint8_t *) Addr;
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
ساکن INLINE uin16_t get_io16(UINTPTR Addr)
{
	واپس *(متلون uin16_t *) Addr;
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
ساکن INLINE uint32_t get_io32(UINTPTR Addr)
{
	واپس *(متلون uint32_t *) Addr;
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
ساکن INLINE uint64_t get_io64(UINTPTR Addr)
{
	واپس *(متلون uint64_t *) Addr;
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
ساکن INLINE خالی سیٹ_io8(UINTPTR Addr, uint8_t قدر_2)
{
	متلون uint8_t *LocalAddr = (متلون uint8_t *)Addr;
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
ساکن INLINE خالی سیٹ_io16(UINTPTR Addr, uint16_t قدر_2)
{
	متلون uint16_t *LocalAddr = (متلون uint16_t *)Addr;
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
ساکن INLINE خالی سیٹ_io32(UINTPTR Addr, uint32_t قدر_2)
{
	متلون uint32_t *LocalAddr = (متلون uint32_t *)Addr;
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
ساکن INLINE خالی سیٹ_io64(UINTPTR Addr, uint64_t قدر_2)
{
	متلون uint64_t *LocalAddr = (متلون uint64_t *)Addr;
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
ساکن INLINE u32 Xil_SecureOut32(UINTPTR Addr, u32 قدر_2)
{
	u32 ReadReg;
	u32 Read_Reg_عارضی;
	u32 حالت_2 = (u32)FAILURE;

	Xil_Out32(Addr, قدر_2);

	ReadReg = Xil_In32(Addr);
	Read_Reg_عارضی = Xil_In32(Addr);

	اگر( (ReadReg == قدر_2) && (Read_Reg_عارضی == قدر_2) ) {
		حالت_2 = (u32)SUCCESS;
	}

	واپس حالت_2;
}

#اگر defined (__MICROBLAZE__)
#اگر_تعریف_شدہ __LITTLE_ENDIAN__
# define Xil_In16LE	get_io16
# define Xil_In32LE	get_io32
# define Xil_Out16LE	سیٹ_io16
# define Xil_Out32LE	سیٹ_io32
# define Xil_Htons	Xil_EndianSwap16
# define Xil_Htonl	Xil_EndianSwap32
# define Xil_Ntohs	Xil_EndianSwap16
# define Xil_Ntohl	Xil_EndianSwap32
# ورنہ
# define Xil_In16BE	get_io16
# define Xil_In32BE	get_io32
# define Xil_Out16BE	سیٹ_io16
# define Xil_Out32BE	سیٹ_io32
# define Xil_Htons(ڈیٹا) (ڈیٹا)
# define Xil_Htonl(ڈیٹا) (ڈیٹا)
# define Xil_Ntohs(ڈیٹا) (ڈیٹا)
# define Xil_Ntohl(ڈیٹا) (ڈیٹا)
#اگر_ختم
#ورنہ
# define Xil_In16LE	get_io16
# define Xil_In32LE	get_io32
# define Xil_Out16LE	سیٹ_io16
# define Xil_Out32LE	سیٹ_io32
# define Xil_Htons	Xil_EndianSwap16
# define Xil_Htonl	Xil_EndianSwap32
# define Xil_Ntohs	Xil_EndianSwap16
# define Xil_Ntohl	Xil_EndianSwap32
#اگر_ختم

#اگر defined (__MICROBLAZE__)
#اگر_تعریف_شدہ __LITTLE_ENDIAN__
ساکن INLINE u16 Xil_In16BE(UINTPTR Addr)
#ورنہ
ساکن INLINE u16 Xil_In16LE(UINTPTR Addr)
#اگر_ختم
#ورنہ
ساکن INLINE u16 Xil_In16BE(UINTPTR Addr)
#اگر_ختم
{
	u16 قدر = Xil_In16(Addr);
	واپس Xil_EndianSwap16(قدر);
}

#اگر defined (__MICROBLAZE__)
#اگر_تعریف_شدہ __LITTLE_ENDIAN__
ساکن INLINE u32 Xil_In32BE(UINTPTR Addr)
#ورنہ
ساکن INLINE u32 Xil_In32LE(UINTPTR Addr)
#اگر_ختم
#ورنہ
ساکن INLINE u32 Xil_In32BE(UINTPTR Addr)
#اگر_ختم
{
	u32 قدر = Xil_In32(Addr);
	واپس Xil_EndianSwap32(قدر);
}

#اگر defined (__MICROBLAZE__)
#اگر_تعریف_شدہ __LITTLE_ENDIAN__
ساکن INLINE خالی Xil_Out16BE(UINTPTR Addr, u16 قدر_2)
#ورنہ
ساکن INLINE خالی Xil_Out16LE(UINTPTR Addr, u16 قدر_2)
#اگر_ختم
#ورنہ
ساکن INLINE خالی Xil_Out16BE(UINTPTR Addr, u16 قدر_2)
#اگر_ختم
{
	قدر_2 = Xil_EndianSwap16(قدر_2);
	Xil_Out16(Addr, قدر_2);
}

#اگر defined (__MICROBLAZE__)
#اگر_تعریف_شدہ __LITTLE_ENDIAN__
ساکن INLINE خالی Xil_Out32BE(UINTPTR Addr, u32 قدر_2)
#ورنہ
ساکن INLINE خالی Xil_Out32LE(UINTPTR Addr, u32 قدر_2)
#اگر_ختم
#ورنہ
ساکن INLINE خالی Xil_Out32BE(UINTPTR Addr, u32 قدر_2)
#اگر_ختم
{
	قدر_2 = Xil_EndianSwap32(قدر_2);
	Xil_Out32(Addr, قدر_2);
}

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم /* end of protection macro */
/**
* @} End of "addtogroup common_io_interfacing_apis".
*/

