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

#अगर_अघोषित IO_ACCESS_H           /* prevent circular inclusions */
#घोषणा IO_ACCESS_H           /* by using protection macros */

#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर

/***************************** Include Files *********************************/

#समावेश "xil_types.h"
#समावेश "log_debug.h"
#समावेश "xstatus.h"

#अगर defined (__MICROBLAZE__)
#समावेश "mb_interface.h"
#अन्यथा
#समावेश "xpseudo_asm.h"
#पूर्ण_अगर

/************************** Function Prototypes ******************************/
u16 Xil_EndianSwap16(u16 तथ्य);
u32 Xil_EndianSwap32(u32 तथ्य);
#अगर_घोषित ENABLE_SAFETY
बाह्य u32 XStl_RegUpdate(u32 RegAddr, u32 RegVal);
#पूर्ण_अगर

/***************** Macros (Inline Functions) Definitions *********************/
#अगर defined __GNUC__
#अगर defined (__MICROBLAZE__)
#  define INST_SYNC		mbar(0)
#  define तथ्य_SYNC		mbar(1)
# अन्यथा
#  define SYNCHRONIZE_IO	dmb()
#  define INST_SYNC		isb()
#  define तथ्य_SYNC		dsb()
# endif
#अन्यथा
# define SYNCHRONIZE_IO
# define INST_SYNC
# define तथ्य_SYNC
# define INST_SYNC
# define तथ्य_SYNC
#पूर्ण_अगर

#अगर defined (__GNUC__) || defined (__ICCARM__) || defined (__MICROBLAZE__)
#घोषणा INLINE अंतरभूत
#अन्यथा
#घोषणा INLINE __inline
#पूर्ण_अगर

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
अटल INLINE uint8_t get_io8(UINTPTR Addr)
{
	वापस *(अस्थिर uint8_t *) Addr;
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
अटल INLINE uin16_t get_io16(UINTPTR Addr)
{
	वापस *(अस्थिर uin16_t *) Addr;
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
अटल INLINE uint32_t get_io32(UINTPTR Addr)
{
	वापस *(अस्थिर uint32_t *) Addr;
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
अटल INLINE uint64_t get_io64(UINTPTR Addr)
{
	वापस *(अस्थिर uint64_t *) Addr;
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
अटल INLINE व्योम set_io8(UINTPTR Addr, uint8_t मूल्य_2)
{
	अस्थिर uint8_t *LocalAddr = (अस्थिर uint8_t *)Addr;
	*LocalAddr = मूल्य_2;
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
अटल INLINE व्योम set_io16(UINTPTR Addr, uint16_t मूल्य_2)
{
	अस्थिर uint16_t *LocalAddr = (अस्थिर uint16_t *)Addr;
	*LocalAddr = मूल्य_2;
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
अटल INLINE व्योम set_io32(UINTPTR Addr, uint32_t मूल्य_2)
{
	अस्थिर uint32_t *LocalAddr = (अस्थिर uint32_t *)Addr;
	*LocalAddr = मूल्य_2;
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
अटल INLINE व्योम set_io64(UINTPTR Addr, uint64_t मूल्य_2)
{
	अस्थिर uint64_t *LocalAddr = (अस्थिर uint64_t *)Addr;
	*LocalAddr = मूल्य_2;
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
अटल INLINE u32 Xil_SecureOut32(UINTPTR Addr, u32 मूल्य_2)
{
	u32 ReadReg;
	u32 Read_Reg_अस्थायी;
	u32 Status = (u32)FAILURE;

	Xil_Out32(Addr, मूल्य_2);

	ReadReg = Xil_In32(Addr);
	Read_Reg_अस्थायी = Xil_In32(Addr);

	अगर( (ReadReg == मूल्य_2) && (Read_Reg_अस्थायी == मूल्य_2) ) {
		Status = (u32)SUCCESS;
	}

	वापस Status;
}

#अगर defined (__MICROBLAZE__)
#अगर_घोषित __LITTLE_ENDIAN__
# define Xil_In16LE	get_io16
# define Xil_In32LE	get_io32
# define Xil_Out16LE	set_io16
# define Xil_Out32LE	set_io32
# define Xil_Htons	Xil_EndianSwap16
# define Xil_Htonl	Xil_EndianSwap32
# define Xil_Ntohs	Xil_EndianSwap16
# define Xil_Ntohl	Xil_EndianSwap32
# अन्यथा
# define Xil_In16BE	get_io16
# define Xil_In32BE	get_io32
# define Xil_Out16BE	set_io16
# define Xil_Out32BE	set_io32
# define Xil_Htons(तथ्य) (तथ्य)
# define Xil_Htonl(तथ्य) (तथ्य)
# define Xil_Ntohs(तथ्य) (तथ्य)
# define Xil_Ntohl(तथ्य) (तथ्य)
#पूर्ण_अगर
#अन्यथा
# define Xil_In16LE	get_io16
# define Xil_In32LE	get_io32
# define Xil_Out16LE	set_io16
# define Xil_Out32LE	set_io32
# define Xil_Htons	Xil_EndianSwap16
# define Xil_Htonl	Xil_EndianSwap32
# define Xil_Ntohs	Xil_EndianSwap16
# define Xil_Ntohl	Xil_EndianSwap32
#पूर्ण_अगर

#अगर defined (__MICROBLAZE__)
#अगर_घोषित __LITTLE_ENDIAN__
अटल INLINE u16 Xil_In16BE(UINTPTR Addr)
#अन्यथा
अटल INLINE u16 Xil_In16LE(UINTPTR Addr)
#पूर्ण_अगर
#अन्यथा
अटल INLINE u16 Xil_In16BE(UINTPTR Addr)
#पूर्ण_अगर
{
	u16 मूल्य = Xil_In16(Addr);
	वापस Xil_EndianSwap16(मूल्य);
}

#अगर defined (__MICROBLAZE__)
#अगर_घोषित __LITTLE_ENDIAN__
अटल INLINE u32 Xil_In32BE(UINTPTR Addr)
#अन्यथा
अटल INLINE u32 Xil_In32LE(UINTPTR Addr)
#पूर्ण_अगर
#अन्यथा
अटल INLINE u32 Xil_In32BE(UINTPTR Addr)
#पूर्ण_अगर
{
	u32 मूल्य = Xil_In32(Addr);
	वापस Xil_EndianSwap32(मूल्य);
}

#अगर defined (__MICROBLAZE__)
#अगर_घोषित __LITTLE_ENDIAN__
अटल INLINE व्योम Xil_Out16BE(UINTPTR Addr, u16 मूल्य_2)
#अन्यथा
अटल INLINE व्योम Xil_Out16LE(UINTPTR Addr, u16 मूल्य_2)
#पूर्ण_अगर
#अन्यथा
अटल INLINE व्योम Xil_Out16BE(UINTPTR Addr, u16 मूल्य_2)
#पूर्ण_अगर
{
	मूल्य_2 = Xil_EndianSwap16(मूल्य_2);
	Xil_Out16(Addr, मूल्य_2);
}

#अगर defined (__MICROBLAZE__)
#अगर_घोषित __LITTLE_ENDIAN__
अटल INLINE व्योम Xil_Out32BE(UINTPTR Addr, u32 मूल्य_2)
#अन्यथा
अटल INLINE व्योम Xil_Out32LE(UINTPTR Addr, u32 मूल्य_2)
#पूर्ण_अगर
#अन्यथा
अटल INLINE व्योम Xil_Out32BE(UINTPTR Addr, u32 मूल्य_2)
#पूर्ण_अगर
{
	मूल्य_2 = Xil_EndianSwap32(मूल्य_2);
	Xil_Out32(Addr, मूल्य_2);
}

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर /* end of protection macro */
/**
* @} End of "addtogroup common_io_interfacing_apis".
*/

