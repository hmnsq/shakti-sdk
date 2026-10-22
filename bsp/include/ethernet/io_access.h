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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ IO_ACCESS_H           /* prevent circular inclusions */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IO_ACCESS_H           /* by using protection macros */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ

/***************************** Include Files *********************************/

#ਅਨ੍ਤਰ੍ਭਾਵ "xil_types.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log_debug.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "xstatus.h"

#ਜੇ defined (__MICROBLAZE__)
#ਅਨ੍ਤਰ੍ਭਾਵ "mb_interface.h"
#ਨਹੀਂਤਾਂ
#ਅਨ੍ਤਰ੍ਭਾਵ "xpseudo_asm.h"
#ਜੇ_ਅੰਤ

/************************** Function Prototypes ******************************/
u16 Xil_EndianSwap16(u16 ਅੰਕੜੇ);
u32 Xil_EndianSwap32(u32 ਅੰਕੜੇ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ ENABLE_SAFETY
ਬਾਹਰੀ u32 XStl_RegUpdate(u32 RegAddr, u32 RegVal);
#ਜੇ_ਅੰਤ

/***************** Macros (Inline Functions) Definitions *********************/
#ਜੇ defined __GNUC__
#ਜੇ defined (__MICROBLAZE__)
#  define INST_SYNC		mbar(0)
#  define ਅੰਕੜੇ_SYNC		mbar(1)
# ਨਹੀਂਤਾਂ
#  define SYNCHRONIZE_IO	dmb()
#  define INST_SYNC		isb()
#  define ਅੰਕੜੇ_SYNC		dsb()
# endif
#ਨਹੀਂਤਾਂ
# define SYNCHRONIZE_IO
# define INST_SYNC
# define ਅੰਕੜੇ_SYNC
# define INST_SYNC
# define ਅੰਕੜੇ_SYNC
#ਜੇ_ਅੰਤ

#ਜੇ defined (__GNUC__) || defined (__ICCARM__) || defined (__MICROBLAZE__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INLINE ਸਤਰਅੰਦਰ
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INLINE __inline
#ਜੇ_ਅੰਤ

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
ਸਥਿਰ INLINE uint8_t get_io8(UINTPTR Addr)
{
	ਵਾਪਸ *(ਅਸਥਿਰ uint8_t *) Addr;
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
ਸਥਿਰ INLINE uin16_t get_io16(UINTPTR Addr)
{
	ਵਾਪਸ *(ਅਸਥਿਰ uin16_t *) Addr;
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
ਸਥਿਰ INLINE uint32_t get_io32(UINTPTR Addr)
{
	ਵਾਪਸ *(ਅਸਥਿਰ uint32_t *) Addr;
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
ਸਥਿਰ INLINE uint64_t get_io64(UINTPTR Addr)
{
	ਵਾਪਸ *(ਅਸਥਿਰ uint64_t *) Addr;
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
ਸਥਿਰ INLINE ਖਾਲੀ ਸੈੱਟ_io8(UINTPTR Addr, uint8_t ਮੁੱਲ_2)
{
	ਅਸਥਿਰ uint8_t *LocalAddr = (ਅਸਥਿਰ uint8_t *)Addr;
	*LocalAddr = ਮੁੱਲ_2;
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
ਸਥਿਰ INLINE ਖਾਲੀ ਸੈੱਟ_io16(UINTPTR Addr, uint16_t ਮੁੱਲ_2)
{
	ਅਸਥਿਰ uint16_t *LocalAddr = (ਅਸਥਿਰ uint16_t *)Addr;
	*LocalAddr = ਮੁੱਲ_2;
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
ਸਥਿਰ INLINE ਖਾਲੀ ਸੈੱਟ_io32(UINTPTR Addr, uint32_t ਮੁੱਲ_2)
{
	ਅਸਥਿਰ uint32_t *LocalAddr = (ਅਸਥਿਰ uint32_t *)Addr;
	*LocalAddr = ਮੁੱਲ_2;
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
ਸਥਿਰ INLINE ਖਾਲੀ ਸੈੱਟ_io64(UINTPTR Addr, uint64_t ਮੁੱਲ_2)
{
	ਅਸਥਿਰ uint64_t *LocalAddr = (ਅਸਥਿਰ uint64_t *)Addr;
	*LocalAddr = ਮੁੱਲ_2;
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
ਸਥਿਰ INLINE u32 Xil_SecureOut32(UINTPTR Addr, u32 ਮੁੱਲ_2)
{
	u32 ReadReg;
	u32 Read_Reg_ਆਰਜ਼ੀ;
	u32 ਸਥਿਤੀ = (u32)FAILURE;

	Xil_Out32(Addr, ਮੁੱਲ_2);

	ReadReg = Xil_In32(Addr);
	Read_Reg_ਆਰਜ਼ੀ = Xil_In32(Addr);

	ਜੇ( (ReadReg == ਮੁੱਲ_2) && (Read_Reg_ਆਰਜ਼ੀ == ਮੁੱਲ_2) ) {
		ਸਥਿਤੀ = (u32)SUCCESS;
	}

	ਵਾਪਸ ਸਥਿਤੀ;
}

#ਜੇ defined (__MICROBLAZE__)
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __LITTLE_ENDIAN__
# define Xil_In16LE	get_io16
# define Xil_In32LE	get_io32
# define Xil_Out16LE	ਸੈੱਟ_io16
# define Xil_Out32LE	ਸੈੱਟ_io32
# define Xil_Htons	Xil_EndianSwap16
# define Xil_Htonl	Xil_EndianSwap32
# define Xil_Ntohs	Xil_EndianSwap16
# define Xil_Ntohl	Xil_EndianSwap32
# ਨਹੀਂਤਾਂ
# define Xil_In16BE	get_io16
# define Xil_In32BE	get_io32
# define Xil_Out16BE	ਸੈੱਟ_io16
# define Xil_Out32BE	ਸੈੱਟ_io32
# define Xil_Htons(ਅੰਕੜੇ) (ਅੰਕੜੇ)
# define Xil_Htonl(ਅੰਕੜੇ) (ਅੰਕੜੇ)
# define Xil_Ntohs(ਅੰਕੜੇ) (ਅੰਕੜੇ)
# define Xil_Ntohl(ਅੰਕੜੇ) (ਅੰਕੜੇ)
#ਜੇ_ਅੰਤ
#ਨਹੀਂਤਾਂ
# define Xil_In16LE	get_io16
# define Xil_In32LE	get_io32
# define Xil_Out16LE	ਸੈੱਟ_io16
# define Xil_Out32LE	ਸੈੱਟ_io32
# define Xil_Htons	Xil_EndianSwap16
# define Xil_Htonl	Xil_EndianSwap32
# define Xil_Ntohs	Xil_EndianSwap16
# define Xil_Ntohl	Xil_EndianSwap32
#ਜੇ_ਅੰਤ

#ਜੇ defined (__MICROBLAZE__)
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __LITTLE_ENDIAN__
ਸਥਿਰ INLINE u16 Xil_In16BE(UINTPTR Addr)
#ਨਹੀਂਤਾਂ
ਸਥਿਰ INLINE u16 Xil_In16LE(UINTPTR Addr)
#ਜੇ_ਅੰਤ
#ਨਹੀਂਤਾਂ
ਸਥਿਰ INLINE u16 Xil_In16BE(UINTPTR Addr)
#ਜੇ_ਅੰਤ
{
	u16 ਮੁੱਲ = Xil_In16(Addr);
	ਵਾਪਸ Xil_EndianSwap16(ਮੁੱਲ);
}

#ਜੇ defined (__MICROBLAZE__)
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __LITTLE_ENDIAN__
ਸਥਿਰ INLINE u32 Xil_In32BE(UINTPTR Addr)
#ਨਹੀਂਤਾਂ
ਸਥਿਰ INLINE u32 Xil_In32LE(UINTPTR Addr)
#ਜੇ_ਅੰਤ
#ਨਹੀਂਤਾਂ
ਸਥਿਰ INLINE u32 Xil_In32BE(UINTPTR Addr)
#ਜੇ_ਅੰਤ
{
	u32 ਮੁੱਲ = Xil_In32(Addr);
	ਵਾਪਸ Xil_EndianSwap32(ਮੁੱਲ);
}

#ਜੇ defined (__MICROBLAZE__)
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __LITTLE_ENDIAN__
ਸਥਿਰ INLINE ਖਾਲੀ Xil_Out16BE(UINTPTR Addr, u16 ਮੁੱਲ_2)
#ਨਹੀਂਤਾਂ
ਸਥਿਰ INLINE ਖਾਲੀ Xil_Out16LE(UINTPTR Addr, u16 ਮੁੱਲ_2)
#ਜੇ_ਅੰਤ
#ਨਹੀਂਤਾਂ
ਸਥਿਰ INLINE ਖਾਲੀ Xil_Out16BE(UINTPTR Addr, u16 ਮੁੱਲ_2)
#ਜੇ_ਅੰਤ
{
	ਮੁੱਲ_2 = Xil_EndianSwap16(ਮੁੱਲ_2);
	Xil_Out16(Addr, ਮੁੱਲ_2);
}

#ਜੇ defined (__MICROBLAZE__)
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __LITTLE_ENDIAN__
ਸਥਿਰ INLINE ਖਾਲੀ Xil_Out32BE(UINTPTR Addr, u32 ਮੁੱਲ_2)
#ਨਹੀਂਤਾਂ
ਸਥਿਰ INLINE ਖਾਲੀ Xil_Out32LE(UINTPTR Addr, u32 ਮੁੱਲ_2)
#ਜੇ_ਅੰਤ
#ਨਹੀਂਤਾਂ
ਸਥਿਰ INLINE ਖਾਲੀ Xil_Out32BE(UINTPTR Addr, u32 ਮੁੱਲ_2)
#ਜੇ_ਅੰਤ
{
	ਮੁੱਲ_2 = Xil_EndianSwap32(ਮੁੱਲ_2);
	Xil_Out32(Addr, ਮੁੱਲ_2);
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ /* end of protection macro */
/**
* @} End of "addtogroup common_io_interfacing_apis".
*/

