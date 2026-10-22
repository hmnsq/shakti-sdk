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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ IO_ACCESS_H           /* prevent circular inclusions */
#ವ್ಯಾಖ್ಯಾನಿಸು IO_ACCESS_H           /* by using protection macros */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ

/***************************** Include Files *********************************/

#ಅನ್ತರ್ಭಾವ "xil_types.h"
#ಅನ್ತರ್ಭಾವ "log_debug.h"
#ಅನ್ತರ್ಭಾವ "xstatus.h"

#ಆದರೆ defined (__MICROBLAZE__)
#ಅನ್ತರ್ಭಾವ "mb_interface.h"
#ಇಲ್ಲದಿದ್ದರೆ
#ಅನ್ತರ್ಭಾವ "xpseudo_asm.h"
#ಆದರೆ_ಅಂತ್ಯ

/************************** Function Prototypes ******************************/
u16 Xil_EndianSwap16(u16 ದತ್ತಾಂಶ);
u32 Xil_EndianSwap32(u32 ದತ್ತಾಂಶ);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ ENABLE_SAFETY
ಬಾಹ್ಯ u32 XStl_RegUpdate(u32 RegAddr, u32 RegVal);
#ಆದರೆ_ಅಂತ್ಯ

/***************** Macros (Inline Functions) Definitions *********************/
#ಆದರೆ defined __GNUC__
#ಆದರೆ defined (__MICROBLAZE__)
#  define INST_SYNC		mbar(0)
#  define ದತ್ತಾಂಶ_SYNC		mbar(1)
# ಇಲ್ಲದಿದ್ದರೆ
#  define SYNCHRONIZE_IO	dmb()
#  define INST_SYNC		isb()
#  define ದತ್ತಾಂಶ_SYNC		dsb()
# endif
#ಇಲ್ಲದಿದ್ದರೆ
# define SYNCHRONIZE_IO
# define INST_SYNC
# define ದತ್ತಾಂಶ_SYNC
# define INST_SYNC
# define ದತ್ತಾಂಶ_SYNC
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ defined (__GNUC__) || defined (__ICCARM__) || defined (__MICROBLAZE__)
#ವ್ಯಾಖ್ಯಾನಿಸು INLINE ಸಾಲೊಳಗೆ
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು INLINE __inline
#ಆದರೆ_ಅಂತ್ಯ

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
ಸ್ಥಿರ INLINE uint8_t get_io8(UINTPTR Addr)
{
	ಹಿಂತಿರುಗಿ *(ಅಸ್ಥಿರ uint8_t *) Addr;
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
ಸ್ಥಿರ INLINE uin16_t get_io16(UINTPTR Addr)
{
	ಹಿಂತಿರುಗಿ *(ಅಸ್ಥಿರ uin16_t *) Addr;
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
ಸ್ಥಿರ INLINE uint32_t get_io32(UINTPTR Addr)
{
	ಹಿಂತಿರುಗಿ *(ಅಸ್ಥಿರ uint32_t *) Addr;
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
ಸ್ಥಿರ INLINE uint64_t get_io64(UINTPTR Addr)
{
	ಹಿಂತಿರುಗಿ *(ಅಸ್ಥಿರ uint64_t *) Addr;
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
ಸ್ಥಿರ INLINE ಶೂನ್ಯ ಗಣ_io8(UINTPTR Addr, uint8_t ಮೌಲ್ಯ_2)
{
	ಅಸ್ಥಿರ uint8_t *LocalAddr = (ಅಸ್ಥಿರ uint8_t *)Addr;
	*LocalAddr = ಮೌಲ್ಯ_2;
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
ಸ್ಥಿರ INLINE ಶೂನ್ಯ ಗಣ_io16(UINTPTR Addr, uint16_t ಮೌಲ್ಯ_2)
{
	ಅಸ್ಥಿರ uint16_t *LocalAddr = (ಅಸ್ಥಿರ uint16_t *)Addr;
	*LocalAddr = ಮೌಲ್ಯ_2;
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
ಸ್ಥಿರ INLINE ಶೂನ್ಯ ಗಣ_io32(UINTPTR Addr, uint32_t ಮೌಲ್ಯ_2)
{
	ಅಸ್ಥಿರ uint32_t *LocalAddr = (ಅಸ್ಥಿರ uint32_t *)Addr;
	*LocalAddr = ಮೌಲ್ಯ_2;
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
ಸ್ಥಿರ INLINE ಶೂನ್ಯ ಗಣ_io64(UINTPTR Addr, uint64_t ಮೌಲ್ಯ_2)
{
	ಅಸ್ಥಿರ uint64_t *LocalAddr = (ಅಸ್ಥಿರ uint64_t *)Addr;
	*LocalAddr = ಮೌಲ್ಯ_2;
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
ಸ್ಥಿರ INLINE u32 Xil_SecureOut32(UINTPTR Addr, u32 ಮೌಲ್ಯ_2)
{
	u32 ReadReg;
	u32 Read_Reg_ತಾತ್ಕಾಲಿಕ;
	u32 ಸ್ಥಿತಿ_2 = (u32)FAILURE;

	Xil_Out32(Addr, ಮೌಲ್ಯ_2);

	ReadReg = Xil_In32(Addr);
	Read_Reg_ತಾತ್ಕಾಲಿಕ = Xil_In32(Addr);

	ಆದರೆ( (ReadReg == ಮೌಲ್ಯ_2) && (Read_Reg_ತಾತ್ಕಾಲಿಕ == ಮೌಲ್ಯ_2) ) {
		ಸ್ಥಿತಿ_2 = (u32)SUCCESS;
	}

	ಹಿಂತಿರುಗಿ ಸ್ಥಿತಿ_2;
}

#ಆದರೆ defined (__MICROBLAZE__)
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __LITTLE_ENDIAN__
# define Xil_In16LE	get_io16
# define Xil_In32LE	get_io32
# define Xil_Out16LE	ಗಣ_io16
# define Xil_Out32LE	ಗಣ_io32
# define Xil_Htons	Xil_EndianSwap16
# define Xil_Htonl	Xil_EndianSwap32
# define Xil_Ntohs	Xil_EndianSwap16
# define Xil_Ntohl	Xil_EndianSwap32
# ಇಲ್ಲದಿದ್ದರೆ
# define Xil_In16BE	get_io16
# define Xil_In32BE	get_io32
# define Xil_Out16BE	ಗಣ_io16
# define Xil_Out32BE	ಗಣ_io32
# define Xil_Htons(ದತ್ತಾಂಶ) (ದತ್ತಾಂಶ)
# define Xil_Htonl(ದತ್ತಾಂಶ) (ದತ್ತಾಂಶ)
# define Xil_Ntohs(ದತ್ತಾಂಶ) (ದತ್ತಾಂಶ)
# define Xil_Ntohl(ದತ್ತಾಂಶ) (ದತ್ತಾಂಶ)
#ಆದರೆ_ಅಂತ್ಯ
#ಇಲ್ಲದಿದ್ದರೆ
# define Xil_In16LE	get_io16
# define Xil_In32LE	get_io32
# define Xil_Out16LE	ಗಣ_io16
# define Xil_Out32LE	ಗಣ_io32
# define Xil_Htons	Xil_EndianSwap16
# define Xil_Htonl	Xil_EndianSwap32
# define Xil_Ntohs	Xil_EndianSwap16
# define Xil_Ntohl	Xil_EndianSwap32
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ defined (__MICROBLAZE__)
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __LITTLE_ENDIAN__
ಸ್ಥಿರ INLINE u16 Xil_In16BE(UINTPTR Addr)
#ಇಲ್ಲದಿದ್ದರೆ
ಸ್ಥಿರ INLINE u16 Xil_In16LE(UINTPTR Addr)
#ಆದರೆ_ಅಂತ್ಯ
#ಇಲ್ಲದಿದ್ದರೆ
ಸ್ಥಿರ INLINE u16 Xil_In16BE(UINTPTR Addr)
#ಆದರೆ_ಅಂತ್ಯ
{
	u16 ಮೌಲ್ಯ = Xil_In16(Addr);
	ಹಿಂತಿರುಗಿ Xil_EndianSwap16(ಮೌಲ್ಯ);
}

#ಆದರೆ defined (__MICROBLAZE__)
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __LITTLE_ENDIAN__
ಸ್ಥಿರ INLINE u32 Xil_In32BE(UINTPTR Addr)
#ಇಲ್ಲದಿದ್ದರೆ
ಸ್ಥಿರ INLINE u32 Xil_In32LE(UINTPTR Addr)
#ಆದರೆ_ಅಂತ್ಯ
#ಇಲ್ಲದಿದ್ದರೆ
ಸ್ಥಿರ INLINE u32 Xil_In32BE(UINTPTR Addr)
#ಆದರೆ_ಅಂತ್ಯ
{
	u32 ಮೌಲ್ಯ = Xil_In32(Addr);
	ಹಿಂತಿರುಗಿ Xil_EndianSwap32(ಮೌಲ್ಯ);
}

#ಆದರೆ defined (__MICROBLAZE__)
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __LITTLE_ENDIAN__
ಸ್ಥಿರ INLINE ಶೂನ್ಯ Xil_Out16BE(UINTPTR Addr, u16 ಮೌಲ್ಯ_2)
#ಇಲ್ಲದಿದ್ದರೆ
ಸ್ಥಿರ INLINE ಶೂನ್ಯ Xil_Out16LE(UINTPTR Addr, u16 ಮೌಲ್ಯ_2)
#ಆದರೆ_ಅಂತ್ಯ
#ಇಲ್ಲದಿದ್ದರೆ
ಸ್ಥಿರ INLINE ಶೂನ್ಯ Xil_Out16BE(UINTPTR Addr, u16 ಮೌಲ್ಯ_2)
#ಆದರೆ_ಅಂತ್ಯ
{
	ಮೌಲ್ಯ_2 = Xil_EndianSwap16(ಮೌಲ್ಯ_2);
	Xil_Out16(Addr, ಮೌಲ್ಯ_2);
}

#ಆದರೆ defined (__MICROBLAZE__)
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __LITTLE_ENDIAN__
ಸ್ಥಿರ INLINE ಶೂನ್ಯ Xil_Out32BE(UINTPTR Addr, u32 ಮೌಲ್ಯ_2)
#ಇಲ್ಲದಿದ್ದರೆ
ಸ್ಥಿರ INLINE ಶೂನ್ಯ Xil_Out32LE(UINTPTR Addr, u32 ಮೌಲ್ಯ_2)
#ಆದರೆ_ಅಂತ್ಯ
#ಇಲ್ಲದಿದ್ದರೆ
ಸ್ಥಿರ INLINE ಶೂನ್ಯ Xil_Out32BE(UINTPTR Addr, u32 ಮೌಲ್ಯ_2)
#ಆದರೆ_ಅಂತ್ಯ
{
	ಮೌಲ್ಯ_2 = Xil_EndianSwap32(ಮೌಲ್ಯ_2);
	Xil_Out32(Addr, ಮೌಲ್ಯ_2);
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ /* end of protection macro */
/**
* @} End of "addtogroup common_io_interfacing_apis".
*/

