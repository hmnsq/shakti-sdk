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

#यदि_अपरिभाषितम् IO_ACCESS_H           /* prevent circular inclusions */
#परिभाषय IO_ACCESS_H           /* by using protection macros */

#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः

/***************************** Include Files *********************************/

#अन्तर्भाव "xil_types.h"
#अन्तर्भाव "log_debug.h"
#अन्तर्भाव "xstatus.h"

#यदि defined (__MICROBLAZE__)
#अन्तर्भाव "mb_interface.h"
#अन्यथा
#अन्तर्भाव "xpseudo_asm.h"
#यदि_अन्तः

/************************** Function Prototypes ******************************/
u16 Xil_EndianSwap16(u16 दत्त);
u32 Xil_EndianSwap32(u32 दत्त);
#यदि_परिभाषितम् ENABLE_SAFETY
बाह्य u32 XStl_RegUpdate(u32 RegAddr, u32 RegVal);
#यदि_अन्तः

/***************** Macros (Inline Functions) Definitions *********************/
#यदि defined __GNUC__
#यदि defined (__MICROBLAZE__)
#  define INST_SYNC		mbar(0)
#  define दत्त_SYNC		mbar(1)
# अन्यथा
#  define SYNCHRONIZE_IO	dmb()
#  define INST_SYNC		isb()
#  define दत्त_SYNC		dsb()
# endif
#अन्यथा
# define SYNCHRONIZE_IO
# define INST_SYNC
# define दत्त_SYNC
# define INST_SYNC
# define दत्त_SYNC
#यदि_अन्तः

#यदि defined (__GNUC__) || defined (__ICCARM__) || defined (__MICROBLAZE__)
#परिभाषय INLINE अन्तःस्थ
#अन्यथा
#परिभाषय INLINE __inline
#यदि_अन्तः

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
स्थिर INLINE uint8_t get_io8(UINTPTR Addr)
{
	प्रत्यागम *(चञ्चल uint8_t *) Addr;
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
स्थिर INLINE uin16_t get_io16(UINTPTR Addr)
{
	प्रत्यागम *(चञ्चल uin16_t *) Addr;
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
स्थिर INLINE uint32_t get_io32(UINTPTR Addr)
{
	प्रत्यागम *(चञ्चल uint32_t *) Addr;
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
स्थिर INLINE uint64_t get_io64(UINTPTR Addr)
{
	प्रत्यागम *(चञ्चल uint64_t *) Addr;
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
स्थिर INLINE शून्य समुच्चयः_io8(UINTPTR Addr, uint8_t मानम्_2)
{
	चञ्चल uint8_t *LocalAddr = (चञ्चल uint8_t *)Addr;
	*LocalAddr = मानम्_2;
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
स्थिर INLINE शून्य समुच्चयः_io16(UINTPTR Addr, uint16_t मानम्_2)
{
	चञ्चल uint16_t *LocalAddr = (चञ्चल uint16_t *)Addr;
	*LocalAddr = मानम्_2;
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
स्थिर INLINE शून्य समुच्चयः_io32(UINTPTR Addr, uint32_t मानम्_2)
{
	चञ्चल uint32_t *LocalAddr = (चञ्चल uint32_t *)Addr;
	*LocalAddr = मानम्_2;
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
स्थिर INLINE शून्य समुच्चयः_io64(UINTPTR Addr, uint64_t मानम्_2)
{
	चञ्चल uint64_t *LocalAddr = (चञ्चल uint64_t *)Addr;
	*LocalAddr = मानम्_2;
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
स्थिर INLINE u32 Xil_SecureOut32(UINTPTR Addr, u32 मानम्_2)
{
	u32 ReadReg;
	u32 Read_Reg_अस्थायी;
	u32 स्थितिः = (u32)FAILURE;

	Xil_Out32(Addr, मानम्_2);

	ReadReg = Xil_In32(Addr);
	Read_Reg_अस्थायी = Xil_In32(Addr);

	यदि( (ReadReg == मानम्_2) && (Read_Reg_अस्थायी == मानम्_2) ) {
		स्थितिः = (u32)SUCCESS;
	}

	प्रत्यागम स्थितिः;
}

#यदि defined (__MICROBLAZE__)
#यदि_परिभाषितम् __LITTLE_ENDIAN__
# define Xil_In16LE	get_io16
# define Xil_In32LE	get_io32
# define Xil_Out16LE	समुच्चयः_io16
# define Xil_Out32LE	समुच्चयः_io32
# define Xil_Htons	Xil_EndianSwap16
# define Xil_Htonl	Xil_EndianSwap32
# define Xil_Ntohs	Xil_EndianSwap16
# define Xil_Ntohl	Xil_EndianSwap32
# अन्यथा
# define Xil_In16BE	get_io16
# define Xil_In32BE	get_io32
# define Xil_Out16BE	समुच्चयः_io16
# define Xil_Out32BE	समुच्चयः_io32
# define Xil_Htons(दत्त) (दत्त)
# define Xil_Htonl(दत्त) (दत्त)
# define Xil_Ntohs(दत्त) (दत्त)
# define Xil_Ntohl(दत्त) (दत्त)
#यदि_अन्तः
#अन्यथा
# define Xil_In16LE	get_io16
# define Xil_In32LE	get_io32
# define Xil_Out16LE	समुच्चयः_io16
# define Xil_Out32LE	समुच्चयः_io32
# define Xil_Htons	Xil_EndianSwap16
# define Xil_Htonl	Xil_EndianSwap32
# define Xil_Ntohs	Xil_EndianSwap16
# define Xil_Ntohl	Xil_EndianSwap32
#यदि_अन्तः

#यदि defined (__MICROBLAZE__)
#यदि_परिभाषितम् __LITTLE_ENDIAN__
स्थिर INLINE u16 Xil_In16BE(UINTPTR Addr)
#अन्यथा
स्थिर INLINE u16 Xil_In16LE(UINTPTR Addr)
#यदि_अन्तः
#अन्यथा
स्थिर INLINE u16 Xil_In16BE(UINTPTR Addr)
#यदि_अन्तः
{
	u16 मानम् = Xil_In16(Addr);
	प्रत्यागम Xil_EndianSwap16(मानम्);
}

#यदि defined (__MICROBLAZE__)
#यदि_परिभाषितम् __LITTLE_ENDIAN__
स्थिर INLINE u32 Xil_In32BE(UINTPTR Addr)
#अन्यथा
स्थिर INLINE u32 Xil_In32LE(UINTPTR Addr)
#यदि_अन्तः
#अन्यथा
स्थिर INLINE u32 Xil_In32BE(UINTPTR Addr)
#यदि_अन्तः
{
	u32 मानम् = Xil_In32(Addr);
	प्रत्यागम Xil_EndianSwap32(मानम्);
}

#यदि defined (__MICROBLAZE__)
#यदि_परिभाषितम् __LITTLE_ENDIAN__
स्थिर INLINE शून्य Xil_Out16BE(UINTPTR Addr, u16 मानम्_2)
#अन्यथा
स्थिर INLINE शून्य Xil_Out16LE(UINTPTR Addr, u16 मानम्_2)
#यदि_अन्तः
#अन्यथा
स्थिर INLINE शून्य Xil_Out16BE(UINTPTR Addr, u16 मानम्_2)
#यदि_अन्तः
{
	मानम्_2 = Xil_EndianSwap16(मानम्_2);
	Xil_Out16(Addr, मानम्_2);
}

#यदि defined (__MICROBLAZE__)
#यदि_परिभाषितम् __LITTLE_ENDIAN__
स्थिर INLINE शून्य Xil_Out32BE(UINTPTR Addr, u32 मानम्_2)
#अन्यथा
स्थिर INLINE शून्य Xil_Out32LE(UINTPTR Addr, u32 मानम्_2)
#यदि_अन्तः
#अन्यथा
स्थिर INLINE शून्य Xil_Out32BE(UINTPTR Addr, u32 मानम्_2)
#यदि_अन्तः
{
	मानम्_2 = Xil_EndianSwap32(मानम्_2);
	Xil_Out32(Addr, मानम्_2);
}

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः /* end of protection macro */
/**
* @} End of "addtogroup common_io_interfacing_apis".
*/

