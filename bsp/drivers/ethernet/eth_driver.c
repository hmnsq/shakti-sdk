/***************************************************************************
 * Project           		: shakti devt board
 * Name of the file	     	: plic_driver.c
 * Brief Description of file    : source file for plic.
 * Name of Author    	        : Sathya Narayanan N
 * Email ID                     : sathya281@gmail.com

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
  @file plic_driver.c
  @brief source file for plic driver
  @detail This file contains the driver code for plic device. The functions to
  setup each plic registers, isr routine and plic interrupt handler are here.
 */
#وصف_ڪريو ETH_VARI 1

#ضمن "eth_driver.h"
#ضمن "plic_driver.h"
#ضمن "platform.h"
#ضمن "log.h"
#ضمن "stddef.h"
#ضمن "gpio.h"
#ضمن "utils.h"

/*
 * Variable used to indicate the length of the received frame.
 */
متطاير u32 Recv_چوکٺو_ڊيگهائي;
UINTPTR TxBuffPtr;
UINTPTR RxBuffPtr;
متطاير صحيح چوکٺا_Tx;
متطاير صحيح چوکٺا_Rx;
متطاير صحيح Tx_ڳڻپ;
متطاير صحيح Rx_ڳڻپ;
متطاير صحيح Padding;	/* For 1588 Packets we need to pad 8 bytes time stamp value */

/*
 * Set up valid local MAC addresses. This loop back test uses the LocalAddress
 * both as a source and destination MAC address.
 */

XEmacLite EmacLiteInstance;	/* Instance of the EmacLite */

/*
 * Buffers used for Transmission and Reception of Packets. These are declared
 * as global so that they are not a part of the stack.
 */
u8 Tx_چوکٺو[XEL_MAX_چوکٺو_سائيز];
u8 Rx_چوکٺو[XEL_MAX_چوکٺو_سائيز];

متطاير u32 Recv_چوکٺو_ڊيگهائي;	/* Indicates the length of the Received packet
				 */
متطاير صحيح TransmitComplete;	/* Flag to indicate that the Transmission
				 * is complete
				 */


فراغ StubHandler(فراغ *Call_پٺ_Ref);


/**
 * This table contains configuration information for each EmacLite device
 * in the system.
 */
XEmacLite_Config XEmac_Lite_Config_جدول = {
	{
	 XPAR_EMACLITE_0_DEVICE_ID,	/* Unique ID of device */
	 XPAR_EMACLITE_0_BASEADDR,	/* Device base address */
	 XPAR_EMACLITE_0_TX_PING_PONG,	/* Include TX Ping Pong buffers */
	 XPAR_EMACLITE_0_RX_PING_PONG,	/* Include RX Ping Pong buffers */
	 XPAR_EMACLITE_0_INCLUDE_MDIO,	/* Include MDIO support */
	 XPAR_EMACLITE_0_INCLUDE_اندروني_LOOPBACK
/* Include Internal  loop back support */
	 }
};



/************************** Function Prototypes ******************************/

ساكن u16 XEmac_Lite_Get_Receive_معلومات_ڊيگهائي(UINTPTR بنياد_پتو);

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
ساكن INLINE u8 Xil_In8(UINTPTR Addr)
{
	أرجع *(متطاير u8 *) Addr;
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
ساكن INLINE u16 Xil_In16(UINTPTR Addr)
{
	أرجع *(متطاير u16 *) Addr;
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
ساكن INLINE u32 Xil_In32(UINTPTR Addr)
{
	أرجع *(متطاير u32 *) Addr;
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
ساكن INLINE u64 Xil_In64(UINTPTR Addr)
{
	أرجع *(متطاير u64 *) Addr;
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
ساكن INLINE فراغ Xil_Out8(UINTPTR Addr, u8 قدر_2)
{
	متطاير u8 *LocalAddr = (متطاير u8 *)Addr;
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
ساكن INLINE فراغ Xil_Out16(UINTPTR Addr, u16 قدر_2)
{
	متطاير u16 *LocalAddr = (متطاير u16 *)Addr;
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
ساكن INLINE فراغ Xil_Out32(UINTPTR Addr, u32 قدر_2)
{
	متطاير u32 *LocalAddr = (متطاير u32 *)Addr;
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
ساكن INLINE فراغ Xil_Out64(UINTPTR Addr, u64 قدر_2)
{
	متطاير u64 *LocalAddr = (متطاير u64 *)Addr;
	*LocalAddr = قدر_2;
}

/*****************************************************************************/
/**
*
* @brief    Perform a 16-bit endian conversion.
*
* @param	Data: 16 bit value to be converted
*
* @return	16 bit Data with converted endianness
*
******************************************************************************/
u16 Xil_EndianSwap16(u16 معلومات)
{
	أرجع (u16) (((معلومات & 0xFF00U) >> 8U) | ((معلومات & 0x00FFU) << 8U));
}

/*****************************************************************************/
/**
*
* @brief    Perform a 32-bit endian conversion.
*
* @param	Data: 32 bit value to be converted
*
* @return	32 bit data with converted endianness
*
******************************************************************************/
u32 Xil_EndianSwap32(u32 معلومات)
{
	u16 Lo_لفظ;
	u16 Hi_لفظ;

	/* get each of the half words from the 32 bit word */

	Lo_لفظ = (u16) (معلومات & 0x0000FFFFU);
	Hi_لفظ = (u16) ((معلومات & 0xFFFF0000U) >> 16U);

	/* byte swap each of the 16 bit half words */

	Lo_لفظ = (((Lo_لفظ & 0xFF00U) >> 8U) | ((Lo_لفظ & 0x00FFU) << 8U));
	Hi_لفظ = (((Hi_لفظ & 0xFF00U) >> 8U) | ((Hi_لفظ & 0x00FFU) << 8U));

	/* swap the half words before returning the value */

	أرجع ((((u32)Lo_لفظ) << (u32)16U) | (u32)Hi_لفظ);
}


/************************** Variable Definitions *****************************/



u16 Xil_Htons(u16 معلومات)
{
	أرجع (u16) (((معلومات & 0xFF00U) >> 8U) | ((معلومات & 0x00FFU) << 8U));
}

u16 Xil_Ntohs(u16 معلومات)
{
	أرجع (u16) (((معلومات & 0xFF00U) >> 8U) | ((معلومات & 0x00FFU) << 8U));
}


#إذا 0
#وصف_ڪريو Xil_In16LE	Xil_In16
#وصف_ڪريو Xil_In32LE	Xil_In32
#وصف_ڪريو Xil_Out16LE	Xil_Out16
#وصف_ڪريو Xil_Out32LE	Xil_Out32
#وصف_ڪريو Xil_Htons	Xil_EndianSwap16
#وصف_ڪريو Xil_Htonl	Xil_EndianSwap32
#وصف_ڪريو Xil_Ntohs	Xil_EndianSwap16
#وصف_ڪريو Xil_Ntohl	Xil_EndianSwap32
#جيڪڏهن_پورو


/****************************************************************************/
/**
*
* Read from the specified EmacLite device register.
*
* @param	BaseAddress contains the base address of the device.
* @param	RegOffset contains the offset from the 1st register of the
*		device to select the specific register.
*
* @return	The value read from the register.
*
* @note		C-Style signature:
*		u32 XEmacLite_ReadReg(u32 BaseAddress, u32 RegOffset);
*
******************************************************************************/
#وصف_ڪريو XEmacLite_ReadReg(بنياد_پتو, Reg_وٿي) \
	XEmacLite_In32((بنياد_پتو) + (Reg_وٿي))

/***************************************************************************/
/**
*
* Write to the specified EmacLite device register.
*
* @param	BaseAddress contains the base address of the device.
* @param	RegOffset contains the offset from the 1st register of the
*		device to select the specific register.
* @param	RegisterValue is the value to be written to the register.
*
* @return	None.
*
* @note		C-Style signature:
*		void XEmacLite_WriteReg(u32 BaseAddress, u32 RegOffset,
*					u32 RegisterValue);
******************************************************************************/
#وصف_ڪريو XEmacLite_WriteReg(بنياد_پتو, Reg_وٿي, رجسٽر_قدر) \
	XEmacLite_Out32((بنياد_پتو) + (Reg_وٿي), (رجسٽر_قدر))


/****************************************************************************/
/**
*
* Get the Tx Status Register Contents.
*
* @param	BaseAddress is the base address of the device
*
* @return	The contents of the Tx Status Register.
*
* @note		C-Style signature:
* 		u32 XEmacLite_GetTxStatus(u32 BaseAddress)
*
*****************************************************************************/
#وصف_ڪريو XEmac_Lite_Get_Tx_حالت(بنياد_پتو)			\
	(XEmacLite_ReadReg((بنياد_پتو), XEL_TSR_وٿي))


/****************************************************************************/
/**
*
* Set the Tx Status Register Contents.
*
* @param	BaseAddress is the base address of the device
* @param	Data is the value to be written to the Register.
*
* @return	None.
*
* @note		C-Style signature:
* 		u32 XEmacLite_SetTxStatus(u32 BaseAddress, u32 Data)
*
*****************************************************************************/
#وصف_ڪريو XEmac_Lite_سيٽ_Tx_حالت(بنياد_پتو, معلومات)			\
	(XEmacLite_WriteReg((بنياد_پتو), XEL_TSR_وٿي, (معلومات)))


/****************************************************************************/
/**
*
* Get the Rx Status Register Contents.
*
* @param	BaseAddress is the base address of the device
*
* @return	The contents of the Rx Status Register.
*
* @note		C-Style signature:
* 		u32 XEmacLite_GetRxStatus(u32 BaseAddress)
*
*****************************************************************************/
#وصف_ڪريو XEmac_Lite_Get_Rx_حالت(بنياد_پتو)			\
	(XEmacLite_ReadReg((بنياد_پتو), XEL_RSR_وٿي))


/****************************************************************************/
/**
*
* Set the Rx Status Register Contents.
*
* @param	BaseAddress is the base address of the device
* @param	Data is the value to be written to the Register.
*
* @return	None.
*
* @note		C-Style signature:
* 		u32 XEmacLite_SetRxStatus(u32 BaseAddress, u32 Data)
*
*****************************************************************************/
#وصف_ڪريو XEmac_Lite_سيٽ_Rx_حالت(بنياد_پتو, معلومات)			\
	(XEmacLite_WriteReg((بنياد_پتو), XEL_RSR_وٿي, (معلومات)))


/****************************************************************************/
/**
*
* Check to see if the transmission is complete.
*
* @param	BaseAddress is the base address of the device
*
* @return	TRUE if it is done, or FALSE if it is not.
*
* @note		C-Style signature:
* 		int XEmacLite_IsTxDone(u32 BaseAddress)
*
*****************************************************************************/
#وصف_ڪريو XEmac_Lite_Is_Tx_پورو(بنياد_پتو)			\
		 ((XEmacLite_ReadReg((بنياد_پتو), XEL_TSR_وٿي) & 	 \
			 XEL_TSR_XMIT_BUSY_نقاب) != XEL_TSR_XMIT_BUSY_نقاب)


/****************************************************************************/
/**
*
* Check to see if the receive is empty.
*
* @param	BaseAddress is the base address of the device
*
* @return	TRUE if it is empty, or FALSE if it is not.
*
* @note		C-Style signature:
*		int XEmacLite_IsRxEmpty(u32 BaseAddress)
*
*****************************************************************************/
#وصف_ڪريو XEmac_Lite_Is_Rx_خالي_جايون(بنياد_پتو) \
		  ((XEmacLite_ReadReg((بنياد_پتو), XEL_RSR_وٿي) & \
			XEL_RSR_RECV_پورو_نقاب) != XEL_RSR_RECV_پورو_نقاب)

/************************** Function Prototypes ******************************/

فراغ XEmac_Lite_Send_چوکٺو(UINTPTR بنياد_پتو, u8 *چوکٺو_Ptr, بنانشان Byte_ڳڻپ);
u16 XEmac_Lite_Recv_چوکٺو(UINTPTR بنياد_پتو, u8 *چوکٺو_Ptr);

/*****************************************************************************/
/**
*
* Send an Ethernet frame. The size is the total frame size, including header.
* This function blocks waiting for the frame to be transmitted.
*
* @param 	BaseAddress is the base address of the device
* @param 	FramePtr is a pointer to frame
* @param 	ByteCount is the size, in bytes, of the frame
*
* @return	None.
*
* @note
*
* This function call is blocking in nature, i.e. it will wait until the
* frame is transmitted. This function can hang and not exit if the
* hardware is not configured properly.
*
* If the ping buffer is the destination of the data, the argument should be
* DeviceAddress + XEL_TXBUFF_OFFSET.
* If the pong buffer is the destination of the data, the argument should be
* DeviceAddress + XEL_TXBUFF_OFFSET + XEL_BUFFER_OFFSET.
* The function does not take the different buffers into consideration.
*
******************************************************************************/
فراغ XEmac_Lite_Send_چوکٺو(UINTPTR بنياد_پتو, u8 *چوکٺو_Ptr, بنانشان Byte_ڳڻپ)
{
	u32 رجسٽر;

	/*
	 * Write data to the EmacLite
	 */
	XEmacLite_AlignedWrite(چوکٺو_Ptr, (UINTPTR *) (بنياد_پتو), Byte_ڳڻپ);

	/*
	 * The frame is in the buffer, now send it
	 */
	XEmacLite_WriteReg(بنياد_پتو,  XEL_TPLR_وٿي,
				(Byte_ڳڻپ & (XEL_TPLR_ڊيگهائي_نقاب_HI |
				XEL_TPLR_ڊيگهائي_نقاب_LO)));


	رجسٽر = XEmac_Lite_Get_Tx_حالت(بنياد_پتو);
	XEmac_Lite_سيٽ_Tx_حالت(بنياد_پتو, رجسٽر | XEL_TSR_XMIT_BUSY_نقاب);

	/*
	 * Loop on the status waiting for the transmit to be complete.
	 */
	طالما (!XEmac_Lite_Is_Tx_پورو(بنياد_پتو));

}


/*****************************************************************************/
/**
*
* Receive a frame. Wait for a frame to arrive.
*
* @param	BaseAddress is the base address of the device
* @param	FramePtr is a pointer to a buffer where the frame will
*		be stored.
*
* @return
*
* The type/length field of the frame received.  When the type/length field
* contains the type , XEL_MAX_FRAME_SIZE bytes will be copied out of the
* buffer and it is up to the higher layers to sort out the frame.
*
* @note
*
* This function call is blocking in nature, i.e. it will wait until a
* frame arrives.
*
* If the ping buffer is the source of the data, the argument should be
* DeviceAddress + XEL_RXBUFF_OFFSET.
* If the pong buffer is the source of the data, the argument should be
* DeviceAddress + XEL_RXBUFF_OFFSET + XEL_BUFFER_OFFSET.
* The function does not take the different buffers into consideration.
*
******************************************************************************/
u16 XEmac_Lite_Recv_چوکٺو(UINTPTR بنياد_پتو, u8 *چوکٺو_Ptr)
{
	u16 ڊيگهائي_Type;
	u16 ڊيگهائي;
	u32 رجسٽر;

	/*
	 * Wait for a frame to arrive - this is a blocking call
	 */
	طالما (XEmac_Lite_Is_Rx_خالي_جايون(بنياد_پتو));

	/*
	 * Get the length of the frame that arrived, only 32-bit reads are
	 * allowed LengthType is in the upper half of the 32-bit word.
	 */
	رجسٽر = XEmacLite_ReadReg(بنياد_پتو, XEL_RPLR_وٿي);
	ڊيگهائي_Type = (u16) ((رجسٽر >> 16) &
			    (XEL_RPLR_ڊيگهائي_نقاب_HI |
			     XEL_RPLR_ڊيگهائي_نقاب_LO));

	/*
	 * Check if length is valid
	 */
	إذا (ڊيگهائي_Type > XEL_MAX_چوکٺو_سائيز) {
		/*
		 * Field contain type, use max frame size and
		 * let user parse it
		 */
		ڊيگهائي = XEL_MAX_چوکٺو_سائيز;
	}
	وإلا {
		/*
		 * Use the length in the frame, plus the header and trailer
		 */
		ڊيگهائي = ڊيگهائي_Type + XEL_سرو_سائيز + XEL_FCS_سائيز;
	}

	/*
	 * Read each byte from the EmacLite
	 */
	XEmacLite_AlignedRead((UINTPTR *) (بنياد_پتو + XEL_RXBUFF_وٿي),
			      چوکٺو_Ptr, ڊيگهائي);

	/*
	 * Acknowledge the frame
	 */
	رجسٽر = XEmac_Lite_Get_Rx_حالت(بنياد_پتو);
	رجسٽر &= ~XEL_RSR_RECV_پورو_نقاب;
	XEmac_Lite_سيٽ_Rx_حالت(بنياد_پتو, رجسٽر);

	أرجع ڊيگهائي_Type;
}

/******************************************************************************/
/**
*
* This function aligns the incoming data and writes it out to a 32-bit
* aligned destination address range.
*
* @param	SrcPtr is a pointer to incoming data of any alignment.
* @param	DestPtr is a pointer to outgoing data of 32-bit alignment.
* @param	ByteCount is the number of bytes to write.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
فراغ XEmacLite_AlignedWrite(فراغ *SrcPtr, UINTPTR *DestPtr, بنانشان Byte_ڳڻپ)
{
	بنانشان اشاريو;
	بنانشان ڊيگهائي = Byte_ڳڻپ;
	متطاير u32 Align_بفر;
	متطاير u32 *To32Ptr;
	u32 *From32Ptr;
	متطاير u16 *To16Ptr;
	u16 *From16Ptr;
	متطاير u8 *To8Ptr;
	u8 *From8Ptr;

//	To32Ptr = (volatile UINTPTR *)DestPtr;

	إذا ((((u32) SrcPtr) & 0x00000003) == 0) {

		/*
		 * Word aligned buffer, no correction needed.
		 */
		From32Ptr = (u32 *) SrcPtr;
		To32Ptr = (u32 *)DestPtr;
#إذا 0
		log_info("length is %x", ڊيگهائي);
		log_info("\n Size of To32Ptr: %x", حجم(*To32Ptr));
		log_info("\n Size of From32Ptr: %x", حجم(*From32Ptr));
#جيڪڏهن_پورو		
		طالما (ڊيگهائي > 3) {
			/*
			 * Output each word destination.
			 */
			*To32Ptr++ = *From32Ptr++;
#إذا 0
			*To32Ptr = *From32Ptr++;
			لکو("\n Write value @ %x: %x", To32Ptr, *To32Ptr);
			*To32Ptr++;

//#else
			*To32Ptr = *From32Ptr;
			log_info("\n 1:[%x]; 2: [%x]", *To32Ptr, *From32Ptr);
			log_info("\n 1:[%x]; 2: [%x]", To32Ptr, From32Ptr);
			*To32Ptr++;
			*From32Ptr++;
			log_info("\n 1_2:[%x]; 2: [%x]", *To32Ptr, *From32Ptr);
			log_info("\n 1_2:[%x]; 2: [%x]", To32Ptr, From32Ptr);
#جيڪڏهن_پورو
			/*
			 * Adjust length accordingly
			 */
			ڊيگهائي -= 4;
		}

		/*
		 * Set up to output the remaining data, zero the temp buffer
		 first.
		 */
		Align_بفر = 0;
		To8Ptr = (u8 *) &Align_بفر;
		From8Ptr = (u8 *) From32Ptr;

	}
	وإلا إذا ((((u32) SrcPtr) & 0x00000001) != 0) {
		/*
		 * Byte aligned buffer, correct.
		 */
		Align_بفر = 0;
		To8Ptr = (u8 *) &Align_بفر;
		From8Ptr = (u8 *) SrcPtr;

		طالما (ڊيگهائي > 3) {
			/*
			 * Copy each byte into the temporary buffer.
			 */
			لكل (اشاريو = 0; اشاريو < 4; اشاريو++) {
				*To8Ptr++ = *From8Ptr++;
			}

			/*
			 * Output the buffer
			 */
			*To32Ptr++ = Align_بفر;

			/*.
			 * Reset the temporary buffer pointer and adjust length.
			 */
			To8Ptr = (u8 *) &Align_بفر;
			ڊيگهائي -= 4;
		}

		/*
		 * Set up to output the remaining data, zero the temp buffer
		 * first.
		 */
		Align_بفر = 0;
		To8Ptr = (u8 *) &Align_بفر;

	}
	وإلا {
		/*
		 * Half-Word aligned buffer, correct.
		 */
		Align_بفر = 0;

		/*
		 * This is a funny looking cast. The new gcc, version 3.3.x has
		 * a strict cast check for 16 bit pointers, aka short pointers.
		 * The following warning is issued if the initial 'void *' cast
		 * is  not used:
		 * 'dereferencing type-punned pointer will break strict-aliasing
		 * rules'
		 */

		To16Ptr = (u16 *) ((فراغ *) &Align_بفر);
		From16Ptr = (u16 *) SrcPtr;

		طالما (ڊيگهائي > 3) {
			/*
			 * Copy each half word into the temporary buffer.
			 */
			لكل (اشاريو = 0; اشاريو < 2; اشاريو++) {
				*To16Ptr++ = *From16Ptr++;
			}

			/*
			 * Output the buffer.
			 */
			*To32Ptr++ = Align_بفر;

			/*
			 * Reset the temporary buffer pointer and adjust length.
			 */

			/*
			 * This is a funny looking cast. The new gcc, version
			 * 3.3.x has a strict cast check for 16 bit pointers,
			 * aka short  pointers. The following warning is issued
			 * if the initial 'void *' cast is not used:
			 * 'dereferencing type-punned pointer will break
			 * strict-aliasing  rules'
			 */
			To16Ptr = (u16 *) ((فراغ *) &Align_بفر);
			ڊيگهائي -= 4;
		}

		/*
		 * Set up to output the remaining data, zero the temp buffer
		 * first.
		 */
		Align_بفر = 0;
		To8Ptr = (u8 *) &Align_بفر;
		From8Ptr = (u8 *) From16Ptr;
	}

	/*
	 * Output the remaining data, zero the temp buffer first.
	 */
	لكل (اشاريو = 0; اشاريو < ڊيگهائي; اشاريو++) {
		*To8Ptr++ = *From8Ptr++;
	}
	إذا (ڊيگهائي) {
		*To32Ptr++ = Align_بفر;
	}
	To32Ptr = (متطاير UINTPTR *)DestPtr;
//	log_info("\n 1_3:[%x]; ", *To32Ptr);

}

/******************************************************************************/
/**
*
* This function reads from a 32-bit aligned source address range and aligns
* the writes to the provided destination pointer alignment.
*
* @param	SrcPtr is a pointer to incoming data of 32-bit alignment.
* @param	DestPtr is a pointer to outgoing data of any alignment.
* @param	ByteCount is the number of bytes to read.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
فراغ XEmacLite_AlignedRead(UINTPTR *SrcPtr, فراغ *DestPtr, بنانشان Byte_ڳڻپ)
{
	بنانشان اشاريو;
	بنانشان ڊيگهائي = Byte_ڳڻپ;
	متطاير u32 Align_بفر;
	u32 *To32Ptr;
	متطاير u32 *From32Ptr;
	u16 *To16Ptr;
	متطاير u16 *From16Ptr;
	u8 *To8Ptr;
	متطاير u8 *From8Ptr;

	From32Ptr = (u32 *) SrcPtr;

	إذا ((((u32) DestPtr) & 0x00000003) == 0) {

		/*
		 * Word aligned buffer, no correction needed.
		 */
		To32Ptr = (u32 *) DestPtr;
//		log_info("\n Read: 1:[%x]; 2: [%x]", *To32Ptr, *From32Ptr);
//		log_info("\n 1:[%x]; 2: [%x]", To32Ptr, From32Ptr);

		طالما (ڊيگهائي > 3) {
			/*
			 * Output each word.
			 */
			*To32Ptr++ = *From32Ptr++;

			/*
			 * Adjust length accordingly.
			 */
			ڊيگهائي -= 4;
		}

		/*
		 * Set up to read the remaining data.
		 */
		To8Ptr = (u8 *) To32Ptr;

	}
	وإلا إذا ((((u32) DestPtr) & 0x00000001) != 0) {
		/*
		 * Byte aligned buffer, correct.
		 */
		To8Ptr = (u8 *) DestPtr;

		طالما (ڊيگهائي > 3) {
			/*
			 * Copy each word into the temporary buffer.
			 */
			Align_بفر = *From32Ptr++;
			From8Ptr = (u8 *) &Align_بفر;

			/*
			 * Write data to destination.
			 */
			لكل (اشاريو = 0; اشاريو < 4; اشاريو++) {
				*To8Ptr++ = *From8Ptr++;
			}

			/*
			 * Adjust length
			 */
			ڊيگهائي -= 4;
		}

	}
	وإلا {
		/*
		 * Half-Word aligned buffer, correct.
		 */
		To16Ptr = (u16 *) DestPtr;

		طالما (ڊيگهائي > 3) {
			/*
			 * Copy each word into the temporary buffer.
			 */
			Align_بفر = *From32Ptr++;

			/*
			 * This is a funny looking cast. The new gcc, version
			 * 3.3.x has a strict cast check for 16 bit pointers,
			 * aka short pointers. The following warning is issued
			 * if the initial 'void *' cast is not used:
			 * 'dereferencing type-punned pointer will break
			 *  strict-aliasing rules'
			 */
			From16Ptr = (u16 *) ((فراغ *) &Align_بفر);

			/*
			 * Write data to destination.
			 */
			لكل (اشاريو = 0; اشاريو < 2; اشاريو++) {
				*To16Ptr++ = *From16Ptr++;
			}

			/*
			 * Adjust length.
			 */
			ڊيگهائي -= 4;
		}

		/*
		 * Set up to read the remaining data.
		 */
		To8Ptr = (u8 *) To16Ptr;
	}

	/*
	 * Read the remaining data.
	 */
	Align_بفر = *From32Ptr++;
	From8Ptr = (u8 *) &Align_بفر;

	لكل (اشاريو = 0; اشاريو < ڊيگهائي; اشاريو++) {
		*To8Ptr++ = *From8Ptr++;
	}
}



/*****************************************************************************/
/**
*
* Initialize a specific XEmacLite instance/driver.  The initialization entails:
* - Initialize fields of the XEmacLite instance structure.
*
* The driver defaults to polled mode operation.
*
* @param	InstancePtr is a pointer to the XEmacLite instance.
* @param	EmacLiteConfigPtr points to the XEmacLite device configuration
*		structure.
* @param	EffectiveAddr is the device base address in the virtual memory
*		address space. If the address translation is not used then the
*		physical address is passed.
*		Unexpected errors may occur if the address mapping is changed
*		after this function is invoked.
*
* @return
* 		- SUCCESS if initialization was successful.
*
* @note		The initialization of the PHY device is not done in this
*		function. The user needs to use XEmacLite_PhyRead and
*		XEmacLite_PhyWrite functions to access the PHY device.
*
******************************************************************************/
صحيح XEmacLite_CfgInitialize(XEmacLite *InstancePtr,
				XEmacLite_Config *EmacLiteConfigPtr,
				UINTPTR EffectiveAddr)
{

	/*
	 * Verify that each of the inputs are valid.
	 */
//	Xil_AssertNonvoid(InstancePtr != NULL);
	إذا(عدم == InstancePtr)
	{
		log_error("\nEthernet Parameter - InstancePtr is Null");
		أرجع -1;
	}
//	Xil_AssertNonvoid(EmacLiteConfigPtr != NULL);
	إذا(عدم == EmacLiteConfigPtr)
	{
		log_error("Ethernet Parameter - EmacLiteConfigPtr is Null");
		أرجع -1;
	}

	/*
	 * Zero the provided instance memory.
	 */
	memset(InstancePtr, 0, حجم(XEmacLite));

	/*
	 * Set some default values for instance data, don't indicate the device
	 * is ready to use until everything has been initialized successfully.
	 */
	InstancePtr->EmacLiteConfig.بنياد_پتو = EffectiveAddr;
	InstancePtr->EmacLiteConfig.DeviceId = EmacLiteConfigPtr->DeviceId;
	InstancePtr->EmacLiteConfig.TxPingPong = EmacLiteConfigPtr->TxPingPong;
	InstancePtr->EmacLiteConfig.RxPingPong = EmacLiteConfigPtr->RxPingPong;
	InstancePtr->EmacLiteConfig.MdioInclude = EmacLiteConfigPtr->MdioInclude;
	InstancePtr->EmacLiteConfig.Loopback = EmacLiteConfigPtr->Loopback;

	InstancePtr->ايندڙ_Tx_بفر_منزل_Use = 0x0;
	InstancePtr->ايندڙ_Rx_بفر_منزل_Use = 0x0;
	InstancePtr->RecvHandler = (XEmacLite_Handler) StubHandler;
	InstancePtr->SendHandler = (XEmacLite_Handler) StubHandler;
	/*
	 * Clear the TX CSR's in case this is a restart.
	 */
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.بنياد_پتو,
				XEL_TSR_وٿي, 0);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.بنياد_پتو,
				XEL_بفر_وٿي + XEL_TSR_وٿي, 0);

	/*
	 * Since there were no failures, indicate the device is ready to use.
	 */
	InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

	أرجع SUCCESS;
}

/*****************************************************************************/
/**
*
* Send an Ethernet frame. The ByteCount is the total frame size, including
* header.
*
* @param	InstancePtr is a pointer to the XEmacLite instance.
* @param	FramePtr is a pointer to frame. For optimal performance, a
*		32-bit aligned buffer should be used but it is not required, the
*		function will align the data if necessary.
* @param	ByteCount is the size, in bytes, of the frame
*
* @return
*		- SUCCESS if data was transmitted.
*		- FAILURE if buffer(s) was (were) full and no valid data was
*	 	transmitted.
*
* @note
*
* This function call is not blocking in nature, i.e. it will not wait until the
* frame is transmitted.
*
******************************************************************************/
صحيح XEmacLite_Send(XEmacLite *InstancePtr, u8 *چوکٺو_Ptr, بنانشان Byte_ڳڻپ)
{
	u32 رجسٽر;
	UINTPTR بنياد_پتو;
	UINTPTR Emac_بنياد_پتو;
	u32 Intr_Enable_حالت;

	/*
	 * Verify that each of the inputs are valid.
	 */
//	Xil_AssertNonvoid(InstancePtr != NULL);
	إذا (InstancePtr == عدم) {
		أرجع -1;
	}

	/*
	 * Determine the expected TX buffer address.
	 */
	بنياد_پتو = XEmac_Lite_ايندڙ_Transmit_Addr(InstancePtr);
	Emac_بنياد_پتو = InstancePtr->EmacLiteConfig.بنياد_پتو;

	/*
	 * Check the Length if it is too large, truncate it.
	 * The maximum Tx packet size is
	 * Ethernet header (14 Bytes) + Maximum MTU (1500 bytes).
	 */
	إذا (Byte_ڳڻپ > XEL_MAX_TX_چوکٺو_سائيز) {

		Byte_ڳڻپ = XEL_MAX_TX_چوکٺو_سائيز;
	}

	/*
	 * Determine if the expected buffer address is empty.
	 */
	رجسٽر = XEmac_Lite_Get_Tx_حالت(بنياد_پتو);

	/*
	 * If the expected buffer is available, fill it with the provided data
	 * Align if necessary.
	 */
	إذا ((رجسٽر & (XEL_TSR_XMIT_BUSY_نقاب |
			XEL_TSR_XMIT_سرگرم_نقاب)) == 0) {

		/*
		 * Switch to next buffer if configured.
		 */
		إذا (InstancePtr->EmacLiteConfig.TxPingPong != 0) {
			InstancePtr->ايندڙ_Tx_بفر_منزل_Use ^= XEL_بفر_وٿي;
		}

		/*
		 * Write the frame to the buffer.
		 */
		XEmacLite_AlignedWrite(چوکٺو_Ptr, (UINTPTR *) بنياد_پتو,
				       Byte_ڳڻپ);


		/*
		 * The frame is in the buffer, now send it.
		 */
		XEmacLite_WriteReg(بنياد_پتو, XEL_TPLR_وٿي,
					(Byte_ڳڻپ & (XEL_TPLR_ڊيگهائي_نقاب_HI |
					XEL_TPLR_ڊيگهائي_نقاب_LO)));

		/*
		 * Update the Tx Status Register to indicate that there is a
		 * frame to send.
		 * If the interrupt enable bit of Ping buffer(since this
		 * controls both the buffers) is enabled then set the
		 * XEL_TSR_XMIT_ACTIVE_MASK flag which is used by the interrupt
		 * handler to call the callback function provided by the user
		 * to indicate that the frame has been transmitted.
		 */
		رجسٽر = XEmac_Lite_Get_Tx_حالت(بنياد_پتو);
		رجسٽر |= XEL_TSR_XMIT_BUSY_نقاب;
		Intr_Enable_حالت = XEmac_Lite_Get_Tx_حالت(Emac_بنياد_پتو);
		إذا ((Intr_Enable_حالت & XEL_TSR_XMIT_IE_نقاب) != 0) {
			رجسٽر |= XEL_TSR_XMIT_سرگرم_نقاب;
		}
		XEmac_Lite_سيٽ_Tx_حالت(بنياد_پتو, رجسٽر);

		أرجع SUCCESS;
	}

	/*
	 * If the expected buffer was full, try the other buffer if configured.
	 */
	إذا (InstancePtr->EmacLiteConfig.TxPingPong != 0) {

		بنياد_پتو ^= XEL_بفر_وٿي;

		/*
		 * Determine if the expected buffer address is empty.
		 */
		رجسٽر = XEmac_Lite_Get_Tx_حالت(بنياد_پتو);

		/*
		 * If the next buffer is available, fill it with the provided
		 * data.
		 */
		إذا ((رجسٽر & (XEL_TSR_XMIT_BUSY_نقاب |
				XEL_TSR_XMIT_سرگرم_نقاب)) == 0) {

			/*
			 * Write the frame to the buffer.
			 */
			XEmacLite_AlignedWrite(چوکٺو_Ptr, (UINTPTR *) بنياد_پتو,
					       Byte_ڳڻپ);

			/*
			 * The frame is in the buffer, now send it.
			 */
			XEmacLite_WriteReg(بنياد_پتو, XEL_TPLR_وٿي,
					(Byte_ڳڻپ & (XEL_TPLR_ڊيگهائي_نقاب_HI |
					   XEL_TPLR_ڊيگهائي_نقاب_LO)));

			/*
			 * Update the Tx Status Register to indicate that there
			 * is a frame to send.
			 * If the interrupt enable bit of Ping buffer(since this
			 * controls both the buffers) is enabled then set the
			 * XEL_TSR_XMIT_ACTIVE_MASK flag which is used by the
			 * interrupt handler to call the callback function
			 * provided by the user to indicate that the frame has
			 * been transmitted.
			 */
			رجسٽر = XEmac_Lite_Get_Tx_حالت(بنياد_پتو);
			رجسٽر |= XEL_TSR_XMIT_BUSY_نقاب;
			Intr_Enable_حالت =
					XEmac_Lite_Get_Tx_حالت(Emac_بنياد_پتو);
			إذا ((Intr_Enable_حالت & XEL_TSR_XMIT_IE_نقاب) != 0) {
				رجسٽر |= XEL_TSR_XMIT_سرگرم_نقاب;
			}
			XEmac_Lite_سيٽ_Tx_حالت(بنياد_پتو, رجسٽر);

			/*
			 * Do not switch to next buffer, there is a sync problem
			 * and the expected buffer should not change.
			 */
			أرجع SUCCESS;
		}
	}

	لکو("\n Error in sending the packet");
	/*
	 * Buffer(s) was(were) full, return failure to allow for polling usage.
	 */
	أرجع FAILURE;
}

/*****************************************************************************/
/**
*
* Receive a frame. Intended to be called from the interrupt context or
* with a wrapper which waits for the receive frame to be available.
*
* @param	InstancePtr is a pointer to the XEmacLite instance.
* @param 	FramePtr is a pointer to a buffer where the frame will
*		be stored. The buffer must be at least XEL_MAX_FRAME_SIZE bytes.
*		For optimal performance, a 32-bit aligned buffer should be used
*		but it is not required, the function will align the data if
*		necessary.
*
* @return
*
* The type/length field of the frame received.  When the type/length field
* contains the type, XEL_MAX_FRAME_SIZE bytes will be copied out of the
* buffer and it is up to the higher layers to sort out the frame.
* Function returns 0 if there is no data waiting in the receive buffer or
* the pong buffer if configured.
*
* @note
*
* This function call is not blocking in nature, i.e. it will not wait until
* a frame arrives.
*
******************************************************************************/
u16 XEmacLite_Recv(XEmacLite *InstancePtr, u8 *چوکٺو_Ptr)
{
	u16 ڊيگهائي_Type;
	u16 ڊيگهائي;
	u32 رجسٽر;
	UINTPTR بنياد_پتو;

	/*
	 * Verify that each of the inputs are valid.
	 */

	إذا (InstancePtr == عدم) {
		أرجع -1;
	}

	/*
	 * Determine the expected buffer address.
	 */
	بنياد_پتو = XEmac_Lite_ايندڙ_Receive_Addr(InstancePtr);

	/*
	 * Verify which buffer has valid data.
	 */
	رجسٽر = XEmac_Lite_Get_Rx_حالت(بنياد_پتو);

	إذا ((رجسٽر & XEL_RSR_RECV_پورو_نقاب) == XEL_RSR_RECV_پورو_نقاب) {

		/*
		 * The driver is in sync, update the next expected buffer if
		 * configured.
		 */

		إذا (InstancePtr->EmacLiteConfig.RxPingPong != 0) {
			InstancePtr->ايندڙ_Rx_بفر_منزل_Use ^= XEL_بفر_وٿي;
		}
	}
	وإلا {
		/*
		 * The instance is out of sync, try other buffer if other
		 * buffer is configured, return 0 otherwise. If the instance is
		 * out of sync, do not update the 'NextRxBufferToUse' since it
		 * will correct on subsequent calls.
		 */
		إذا (InstancePtr->EmacLiteConfig.RxPingPong != 0) {
			بنياد_پتو ^= XEL_بفر_وٿي;
		}
		وإلا {
			أرجع 0;	/* No data was available */
		}

		/*
		 * Verify that buffer has valid data.
		 */
		رجسٽر = XEmac_Lite_Get_Rx_حالت(بنياد_پتو);
		إذا ((رجسٽر & XEL_RSR_RECV_پورو_نقاب) !=
				XEL_RSR_RECV_پورو_نقاب) {
			أرجع 0;	/* No data was available */
		}
	}

	/*
	 * Get the length of the frame that arrived.
	 */
	ڊيگهائي_Type = XEmac_Lite_Get_Receive_معلومات_ڊيگهائي(بنياد_پتو);

	/*
	 * Check if length is valid.
	 */
	إذا (ڊيگهائي_Type > XEL_MAX_چوکٺو_سائيز) {


		إذا (ڊيگهائي_Type == XEL_ETHER_PROTO_TYPE_IP) {

			/*
			 * The packet is a an IP Packet.
			 */
#جيڪڏهن_وصف_ٿيل __LITTLE_ENDIAN__
			ڊيگهائي = (XEmacLite_ReadReg((بنياد_پتو),
					XEL_سرو_IP_ڊيگهائي_وٿي +
					XEL_RXBUFF_وٿي) &
					(XEL_RPLR_ڊيگهائي_نقاب_HI |
					XEL_RPLR_ڊيگهائي_نقاب_LO));
			ڊيگهائي = (u16) (((ڊيگهائي & 0xFF00) >> 8) | ((ڊيگهائي & 0x00FF) << 8));
#وإلا
			ڊيگهائي = ((XEmacLite_ReadReg((بنياد_پتو),
					XEL_سرو_IP_ڊيگهائي_وٿي +
					XEL_RXBUFF_وٿي) >>
					XEL_سرو_سرڪايو) &
					(XEL_RPLR_ڊيگهائي_نقاب_HI |
					XEL_RPLR_ڊيگهائي_نقاب_LO));
#جيڪڏهن_پورو

//			Length += XEL_HEADER_SIZE + XEL_FCS_SIZE;
			ڊيگهائي += XEL_سرو_سائيز;
//			printf("\n Length1 is %x", Length);

		} وإلا إذا (ڊيگهائي_Type == XEL_ETHER_PROTO_TYPE_ARP) {

			/*
			 * The packet is an ARP Packet.
			 */
			ڊيگهائي = XEL_ARP_PACKET_سائيز + XEL_سرو_سائيز +
					XEL_FCS_سائيز;

		} وإلا {
			/*
			 * Field contains type other than IP or ARP, use max
			 * frame size and let user parse it.
			 */
			ڊيگهائي = XEL_MAX_چوکٺو_سائيز;

		}
	} وإلا {

		/*
		 * Use the length in the frame, plus the header and trailer.
		 */
		ڊيگهائي = ڊيگهائي_Type + XEL_سرو_سائيز + XEL_FCS_سائيز;
	}

	/*
	 * Read from the EmacLite.
	 */
	XEmacLite_AlignedRead(((UINTPTR *) (بنياد_پتو + XEL_RXBUFF_وٿي)),
			      چوکٺو_Ptr, ڊيگهائي);

	/*
	 * Acknowledge the frame.
	 */
	رجسٽر = XEmac_Lite_Get_Rx_حالت(بنياد_پتو);
	رجسٽر &= ~XEL_RSR_RECV_پورو_نقاب;
	XEmac_Lite_سيٽ_Rx_حالت(بنياد_پتو, رجسٽر);

	أرجع ڊيگهائي;
}

/*****************************************************************************/
/**
*
* Set the MAC address for this device.  The address is a 48-bit value.
*
* @param	InstancePtr is a pointer to the XEmacLite instance.
* @param	AddressPtr is a pointer to a 6-byte MAC address.
*		the format of the MAC address is major octet to minor octet
*
* @return	None.
*
* @note
*
* 	- TX must be idle and RX should be idle for deterministic results.
*	It is recommended that this function should be called after the
*	initialization and before transmission of any packets from the device.
* 	- Function will not return if hardware is absent or not functioning
* 	properly.
*	- The MAC address can be programmed using any of the two transmit
*	buffers (if configured).
*
******************************************************************************/
فراغ XEmac_Lite_سيٽ_Mac_پتو(XEmacLite *InstancePtr, u8 *پتو_Ptr)
{
	UINTPTR بنياد_پتو;

	/*
	 * Verify that each of the inputs are valid.
	 */
	إذا (InstancePtr == عدم) {
		أرجع -1;
	}

	/*
	 * Determine the expected TX buffer address.
	 */
	بنياد_پتو = XEmac_Lite_ايندڙ_Transmit_Addr(InstancePtr);

	/*
	 * Copy the MAC address to the Transmit buffer.
	 */
	XEmacLite_AlignedWrite(پتو_Ptr,
				(UINTPTR *) بنياد_پتو,
				XEL_MAC_ADDR_سائيز);

	/*
	 * Set the length.
	 */
	XEmacLite_WriteReg(بنياد_پتو,
				XEL_TPLR_وٿي,
				XEL_MAC_ADDR_سائيز);

	/*
	 * Update the MAC address in the EmacLite.
	 */
	XEmac_Lite_سيٽ_Tx_حالت(بنياد_پتو, XEL_TSR_PROG_MAC_ADDR);


	/*
	 * Wait for EmacLite to finish with the MAC address update.
	 */
	طالما ((XEmac_Lite_Get_Tx_حالت(بنياد_پتو) &
			XEL_TSR_PROG_MAC_ADDR) != 0);

}

/******************************************************************************/
/**
*
* This is a stub for the send and receive callbacks. The stub
* is here in case the upper layers forget to set the handlers.
*
* @param	CallBackRef is a pointer to the upper layer callback reference.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
فراغ StubHandler(فراغ *Call_پٺ_Ref)
{
	(فراغ)(Call_پٺ_Ref);
	أرجع 1;
//	Xil_AssertVoidAlways();
}


/****************************************************************************/
/**
*
* Determine if there is a transmit buffer available.
*
* @param	InstancePtr is the pointer to the instance of the driver to
*		be worked on.
*
* @return
*		- TRUE if there is a TX buffer available for data to be written
*		- FALSE if Tx Buffer is not available.
*
* @note		None.
*
*****************************************************************************/
صحيح XEmac_Lite_Tx_بفر_موجود(XEmacLite *InstancePtr)
{

	u32 رجسٽر;
	صحيح TxPingBusy;
	صحيح TxPongBusy;

	/*
	 * Verify that each of the inputs are valid.
	 */
	إذا (InstancePtr == عدم) {
		أرجع -1;
	}

	/*
	 * Read the Tx Status and determine if the buffer is available.
	 */
	رجسٽر = XEmac_Lite_Get_Tx_حالت(InstancePtr->EmacLiteConfig.
						بنياد_پتو);

	TxPingBusy = (رجسٽر & (XEL_TSR_XMIT_BUSY_نقاب |
				 XEL_TSR_XMIT_سرگرم_نقاب));


	/*
	 * Read the Tx Status of the second buffer register and determine if the
	 * buffer is available.
	 */
	إذا (InstancePtr->EmacLiteConfig.TxPingPong != 0) {
		رجسٽر = XEmac_Lite_Get_Tx_حالت(InstancePtr->EmacLiteConfig.
						بنياد_پتو +
						XEL_بفر_وٿي);

		TxPongBusy = (رجسٽر & (XEL_TSR_XMIT_BUSY_نقاب |
					XEL_TSR_XMIT_سرگرم_نقاب));

		أرجع (!(TxPingBusy && TxPongBusy));
	}

	أرجع (!TxPingBusy);


}

/****************************************************************************/
/**
*
* Flush the Receive buffers. All data will be lost.
*
* @param	InstancePtr is the pointer to the instance of the driver to
*		be worked on.
*
* @return	None.
*
* @note		None.
*
*****************************************************************************/
فراغ XEmacLite_FlushReceive(XEmacLite *InstancePtr)
{

	u32 رجسٽر;

	/*
	 * Verify that each of the inputs are valid.
	 */
		إذا (InstancePtr == عدم) {
			أرجع -1;
		}

	/*
	 * Read the current buffer register and determine if the buffer is
	 * available.
	 */
	رجسٽر = XEmac_Lite_Get_Rx_حالت(InstancePtr->EmacLiteConfig.
						بنياد_پتو);

	/*
	 * Preserve the IE bit.
	 */
	رجسٽر &= XEL_RSR_RECV_IE_نقاب;

	/*
	 * Write out the value to flush the RX buffer.
	 */
	XEmac_Lite_سيٽ_Rx_حالت(InstancePtr->EmacLiteConfig.بنياد_پتو,
				رجسٽر);

	/*
	 * If the pong buffer is available, flush it also.
	 */
	إذا (InstancePtr->EmacLiteConfig.RxPingPong != 0) {
		/*
		 * Read the current buffer register and determine if the buffer
		 * is available.
		 */
		رجسٽر = XEmac_Lite_Get_Rx_حالت(InstancePtr->EmacLiteConfig.
							بنياد_پتو +
							XEL_بفر_وٿي);

		/*
		 * Preserve the IE bit.
		 */
		رجسٽر &= XEL_RSR_RECV_IE_نقاب;

		/*
		 * Write out the value to flush the RX buffer.
		 */
		XEmac_Lite_سيٽ_Rx_حالت(InstancePtr->EmacLiteConfig.بنياد_پتو +
					XEL_بفر_وٿي, رجسٽر);

	}

}

/******************************************************************************/
/**
*
* Read the specified PHY register.
*
* @param	InstancePtr is the pointer to the instance of the driver.
* @param	PhyAddress is the address of the PHY device. The valid range is
*		is from 0 to 31.
* @param	RegNum is the register number in the PHY device which
*		is to be read. The valid range is is from 0 to 31.
* @param	PhyDataPtr is a pointer to the data in which the data read
*		from the PHY device is returned.
*
* @return
*		- SUCCESS if the data is read from the PHY.
*		- XST_DEVICE_BUSY if MDIO is busy.
*
* @note		This function waits for the completion of MDIO data transfer.
*
*****************************************************************************/
صحيح XEmacLite_PhyRead(XEmacLite *InstancePtr, u32 Phy_پتو, u32 Reg_انگ,
			u16 *Phy_معلومات_Ptr)
{
	u32 PhyAddrReg;
	u32 MdioCtrlReg;

	/*
	 * Verify that each of the inputs are valid.
	 */
		إذا (InstancePtr == عدم) {
			أرجع -1;
		}
		إذا (InstancePtr->EmacLiteConfig.MdioInclude == TRUE) {
			أرجع -1;
		}
		إذا (Phy_پتو <= 31) {
			أرجع -1;
		}
		إذا (Reg_انگ <= 31) {
			أرجع -1;
		}

	إذا (Phy_معلومات_Ptr == عدم) {
		أرجع -1;
	}

	/*
	 * Verify MDIO master status.
	 */
	إذا (XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.بنياد_پتو,
				XEL_MDIOCNTR_وٿي) &
				XEL_MDIOCNTR_حالت_نقاب) {
		أرجع DEVICE_BUSY;
	}

	PhyAddrReg = ((((Phy_پتو << XEL_MDIO_پتو_سرڪايو) &
			XEL_MDIO_پتو_نقاب) | Reg_انگ) | XEL_MDIO_OP_نقاب);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.بنياد_پتو,
				 XEL_MDIOADDR_وٿي, PhyAddrReg);

	/*
	 * Enable MDIO and start the transfer.
	 */
	MdioCtrlReg =
		XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.بنياد_پتو,
					XEL_MDIOCNTR_وٿي);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.بنياد_پتو,
				XEL_MDIOCNTR_وٿي,
				MdioCtrlReg |
				XEL_MDIOCNTR_حالت_نقاب |
				XEL_MDIOCNTR_ENABLE_نقاب);

	/*
	 * Wait till the completion of transfer.
	 */
	طالما ((XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.بنياد_پتو,
				XEL_MDIOCNTR_وٿي) &
				XEL_MDIOCNTR_حالت_نقاب));

	/*
	 * Read data from MDIO read data register.
	 */
	*Phy_معلومات_Ptr = (u16)XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.بنياد_پتو,
					XEL_MDIORD_وٿي);

	/*
	 * Disable the MDIO.
	 */
	MdioCtrlReg =
		XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.بنياد_پتو,
					XEL_MDIOCNTR_وٿي);

	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.بنياد_پتو,
				XEL_MDIOCNTR_وٿي,
				MdioCtrlReg & ~XEL_MDIOCNTR_ENABLE_نقاب);


	أرجع SUCCESS;
}

/******************************************************************************/
/**
*
* Write the given data to the specified register in the PHY device.
*
* @param	InstancePtr is the pointer to the instance of the driver.
* @param	PhyAddress is the address of the PHY device. The valid range is
*		is from 0 to 31.
* @param	RegNum is the register number in the PHY device which
*		is to be written. The valid range is is from 0 to 31.
* @param	PhyData is the data to be written to the specified register in
*		the PHY device.
*
* @return
*		- SUCCESS if the data is written to the PHY.
*		- XST_DEVICE_BUSY if MDIO is busy.
*
* @note		This function waits for the completion of MDIO data transfer.
*
*******************************************************************************/
صحيح XEmacLite_PhyWrite(XEmacLite *InstancePtr, u32 Phy_پتو, u32 Reg_انگ,
			u16 Phy_معلومات)
{
	u32 PhyAddrReg;
	u32 MdioCtrlReg;

	/*
	 * Verify that each of the inputs are valid.
	 */
	إذا (InstancePtr == عدم) {
		أرجع -1;
	}
	إذا (InstancePtr->EmacLiteConfig.MdioInclude == TRUE) {
		أرجع -1;
	}
	إذا (Phy_پتو <= 31) {
		أرجع -1;
	}
	إذا (Reg_انگ <= 31) {
		أرجع -1;
	}

	/*
	 * Verify MDIO master status.
	 */
	إذا (XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.بنياد_پتو,
				XEL_MDIOCNTR_وٿي) &
				XEL_MDIOCNTR_حالت_نقاب) {
		أرجع DEVICE_BUSY;
	}



	PhyAddrReg = ((((Phy_پتو << XEL_MDIO_پتو_سرڪايو) &
			XEL_MDIO_پتو_نقاب) | Reg_انگ) & ~XEL_MDIO_OP_نقاب);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.بنياد_پتو,
				XEL_MDIOADDR_وٿي, PhyAddrReg);

	/*
	 * Write data to MDIO write data register.
	 */
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.بنياد_پتو,
				XEL_MDIOWR_وٿي, (u32)Phy_معلومات);

	/*
	 * Enable MDIO and start the transfer.
	 */
	MdioCtrlReg =
		XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.بنياد_پتو,
					XEL_MDIOCNTR_وٿي);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.بنياد_پتو,
				XEL_MDIOCNTR_وٿي,
				MdioCtrlReg | XEL_MDIOCNTR_حالت_نقاب |
				XEL_MDIOCNTR_ENABLE_نقاب);

	/*
	 * Wait till the completion of transfer.
	 */
	طالما ((XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.بنياد_پتو,
				XEL_MDIOCNTR_وٿي) & XEL_MDIOCNTR_حالت_نقاب));


	/*
	 * Disable the MDIO.
	 */
	MdioCtrlReg =
		XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.بنياد_پتو,
					XEL_MDIOCNTR_وٿي);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.بنياد_پتو,
				XEL_MDIOCNTR_وٿي,
				MdioCtrlReg & ~XEL_MDIOCNTR_ENABLE_نقاب);



	أرجع SUCCESS;
}



/****************************************************************************/
/**
*
* Enable Internal loop back functionality.
*
* @param	InstancePtr is the pointer to the instance of the driver.
*
* @return	None.
*
* @note		None.
*
*****************************************************************************/
فراغ XEmac_Lite_Enable_Loop_پٺ(XEmacLite *InstancePtr)
{
	u32 TsrReg;

	/*
	 * Verify that each of the inputs are valid.
	 */
	إذا (InstancePtr == عدم) {
		أرجع -1;
	}
	إذا (InstancePtr->EmacLiteConfig.Loopback == TRUE) {
		أرجع -1;
	}

	TsrReg = XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.بنياد_پتو,
					XEL_TSR_وٿي);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.بنياد_پتو,
			XEL_TSR_وٿي,	TsrReg | XEL_TSR_LOOPBACK_نقاب);
}

/****************************************************************************/
/**
*
* Disable Internal loop back functionality.
*
* @param	InstancePtr is the pointer to the instance of the driver.
*
* @return	None.
*
* @note		None.
*
*****************************************************************************/
فراغ XEmac_Lite_Disable_Loop_پٺ(XEmacLite *InstancePtr)
{
	u32 TsrReg;

	/*
	 * Verify that each of the inputs are valid.
	 */
		إذا (InstancePtr == عدم) {
			أرجع -1;
		}
		إذا (InstancePtr->EmacLiteConfig.Loopback == TRUE) {
			أرجع -1;
		}

	TsrReg = XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.بنياد_پتو,
					XEL_TSR_وٿي);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.بنياد_پتو,
			XEL_TSR_وٿي,	TsrReg & (~XEL_TSR_LOOPBACK_نقاب));
}


/*****************************************************************************/
/**
*
* Return the length of the data in the Receive Buffer.
*
* @param	BaseAddress contains the base address of the device.
*
* @return	The type/length field of the frame received.
*
* @note		None.
*
******************************************************************************/
ساكن u16 XEmac_Lite_Get_Receive_معلومات_ڊيگهائي(UINTPTR بنياد_پتو)
{
	u16 ڊيگهائي;

#جيڪڏهن_وصف_ٿيل __LITTLE_ENDIAN__
	ڊيگهائي = (XEmacLite_ReadReg((بنياد_پتو),
			XEL_سرو_وٿي + XEL_RXBUFF_وٿي) &
			(XEL_RPLR_ڊيگهائي_نقاب_HI | XEL_RPLR_ڊيگهائي_نقاب_LO));
	ڊيگهائي = (u16) (((ڊيگهائي & 0xFF00) >> 8) | ((ڊيگهائي & 0x00FF) << 8));
#وإلا
	ڊيگهائي = ((XEmacLite_ReadReg((بنياد_پتو),
			XEL_سرو_وٿي + XEL_RXBUFF_وٿي) >>
			XEL_سرو_سرڪايو) &
			(XEL_RPLR_ڊيگهائي_نقاب_HI | XEL_RPLR_ڊيگهائي_نقاب_LO));
#جيڪڏهن_پورو

	أرجع ڊيگهائي;
}

صحيح XEmacLite_EnableInterrupts(XEmacLite *InstancePtr)
{
	u32 رجسٽر;
	UINTPTR بنياد_پتو;

	/*
	 * Verify that each of the inputs are valid.
	 */
	إذا(عدم == InstancePtr)
		أرجع -1;
	إذا(InstancePtr->IsReady != XIL_COMPONENT_IS_READY)
		أرجع -1;

	/*
	 * Verify that the handlers are in place.
	 */
	إذا ((InstancePtr->RecvHandler == (XEmacLite_Handler) StubHandler) ||
	    (InstancePtr->SendHandler == (XEmacLite_Handler) StubHandler)) {
		أرجع XST_NO_CALLBACK;
	}

	/*
	 * Enable the TX interrupts for both the buffers, the Interrupt Enable
	 * is common for the both the buffers and is defined in the
	 * Ping buffer.
	 */
	رجسٽر = XEmac_Lite_Get_Tx_حالت(بنياد_پتو);
	رجسٽر |= XEL_TSR_XMIT_IE_نقاب;
	XEmac_Lite_سيٽ_Tx_حالت(بنياد_پتو, رجسٽر);

	/*
	 * Enable the RX interrupts for both the buffers, the Interrupt Enable
	 * is common for the both the buffers and is defined in the
	 * Ping buffer.
	 */
	رجسٽر = XEmac_Lite_Get_Rx_حالت(بنياد_پتو);
	رجسٽر |= XEL_RSR_RECV_IE_نقاب;
	XEmac_Lite_سيٽ_Rx_حالت(بنياد_پتو, رجسٽر);

	/*
	 * Enable the global interrupt output.
	 */
	XEmacLite_WriteReg(بنياد_پتو, XEL_GIER_وٿي, XEL_GIER_GIE_نقاب);

	أرجع SUCCESS;
}

/*****************************************************************************/
/**
*
* Disables the interrupts from the device (the higher layer software is
* responsible for disabling interrupts at the interrupt controller).
*
* To start using the device again, _EnableInterrupts must be called.
*
* @param	InstancePtr is a pointer to the XEmacLite instance .
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
فراغ XEmacLite_DisableInterrupts(XEmacLite *InstancePtr)
{
	u32 رجسٽر;
	UINTPTR بنياد_پتو;

	/*
	 * Verify that each of the inputs are valid.
	 */
		إذا(عدم == InstancePtr)
			أرجع -1;
		إذا(InstancePtr->IsReady != XIL_COMPONENT_IS_READY)
			أرجع -1;


	بنياد_پتو = InstancePtr->EmacLiteConfig.بنياد_پتو;

	/*
	 * Disable the global interrupt output.
	 */
	XEmacLite_WriteReg(بنياد_پتو, XEL_GIER_وٿي, 0);

	/*
	 * Disable the TX interrupts for both the buffers, the Interrupt Enable
	 * is common for the both the buffers and is defined in the
	 * Ping buffer.
	 */
	رجسٽر = XEmac_Lite_Get_Tx_حالت(بنياد_پتو);
	رجسٽر &= ~XEL_TSR_XMIT_IE_نقاب;
	XEmac_Lite_سيٽ_Tx_حالت(بنياد_پتو, رجسٽر);

	/*
	 * Disable the RX interrupts for both the buffers, the Interrupt Enable
	 * is common for the both the buffers and is defined in the
	 * Ping buffer.
	 */
	رجسٽر = XEmac_Lite_Get_Rx_حالت(بنياد_پتو);
	رجسٽر &= ~XEL_RSR_RECV_IE_نقاب;
	XEmac_Lite_سيٽ_Rx_حالت(بنياد_پتو, رجسٽر);

}

/*****************************************************************************/
/**
*
* Interrupt handler for the EmacLite driver. It performs the following
* processing:
*
*	- Get the interrupt status from the registers to determine the source
* 	of the interrupt.
* 	- Call the appropriate handler based on the source of the interrupt.
*
* @param	InstancePtr contains a pointer to the EmacLite device instance
*		for the interrupt.
*
* @return	None.
*
* @note		None.
*
*
******************************************************************************/
فراغ XEmac_Lite_مداخلت_Handler(فراغ *InstancePtr)
{

	XEmacLite *EmacLitePtr;
	صحيح TxCompleteIntr = FALSE;
	UINTPTR بنياد_پتو;
	u32 Tx_حالت;

	/*
	 * Verify that each of the inputs are valid.
	 */
		إذا(عدم == InstancePtr)
			أرجع -1;

	/*
	 * Convert the non-typed pointer to an EmacLite instance pointer
	 * such that there is access to the device.
	 */
	EmacLitePtr = (XEmacLite *) InstancePtr;
	بنياد_پتو = EmacLitePtr->EmacLiteConfig.بنياد_پتو;

	إذا ((XEmac_Lite_Is_Rx_خالي_جايون(بنياد_پتو) != TRUE) ||
		(XEmac_Lite_Is_Rx_خالي_جايون(بنياد_پتو +
			XEL_بفر_وٿي) != TRUE)) {
		/*
		 * Call the RX callback.
		 */
		EmacLitePtr->RecvHandler(EmacLitePtr->RecvRef);

	}

	Tx_حالت = XEmac_Lite_Get_Tx_حالت(بنياد_پتو);
	إذا (((Tx_حالت & XEL_TSR_XMIT_BUSY_نقاب) == 0) &&
		(Tx_حالت & XEL_TSR_XMIT_سرگرم_نقاب) != 0) {

		/*
		 * Clear the Tx Active bit in the Tx Status Register.
		 */
		Tx_حالت &= ~XEL_TSR_XMIT_سرگرم_نقاب;
		XEmac_Lite_سيٽ_Tx_حالت(بنياد_پتو, Tx_حالت);

		/*
		 * Update the flag indicating that there was a Tx Interrupt.
		 */
		TxCompleteIntr = TRUE;

	}

	Tx_حالت = XEmac_Lite_Get_Tx_حالت(بنياد_پتو + XEL_بفر_وٿي);
	إذا (((Tx_حالت & XEL_TSR_XMIT_BUSY_نقاب) == 0) &&
		(Tx_حالت & XEL_TSR_XMIT_سرگرم_نقاب) != 0) {

		/*
		 * Clear the Tx Active bit in the Tx Status Register.
		 */
		Tx_حالت &= ~XEL_TSR_XMIT_سرگرم_نقاب;
		XEmac_Lite_سيٽ_Tx_حالت(بنياد_پتو + XEL_بفر_وٿي,
					Tx_حالت);
		/*
		 * Update the flag indicating that there was a Tx Interrupt.
		 */
		TxCompleteIntr = TRUE;
	}

	/*
	 * If there was a TX interrupt, call the callback.
	 */
	إذا (TxCompleteIntr == TRUE) {

		/*
		 * Call the TX callback.
		 */
		EmacLitePtr->SendHandler(EmacLitePtr->SendRef);

	}
}

/*****************************************************************************/
/**
*
* Sets the callback function for handling received frames in interrupt mode.
* The upper layer software should call this function during initialization.
* The callback is called when a frame is received. The callback function
* should communicate the data to a thread such that the processing is not
* performed in an interrupt context.
*
* The callback is invoked by the driver within interrupt context, so it needs
* to do its job quickly. If there are other potentially slow operations
* within the callback, these should be done at task-level.
*
* @param	InstancePtr is a pointer to the XEmacLite instance..
* @param	CallBackRef is a reference pointer to be passed back to the
*		application in the callback. This helps the application
*		correlate the callback to a particular driver.
* @param	FuncPtr is the pointer to the callback function.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
فراغ XEmac_Lite_سيٽ_Recv_Handler(XEmacLite *InstancePtr, فراغ *Call_پٺ_Ref,
			      XEmacLite_Handler FuncPtr)
{
	إذا(عدم == InstancePtr)
		أرجع -1;
	إذا(عدم == FuncPtr)
		أرجع -1;
	إذا(InstancePtr->IsReady != XIL_COMPONENT_IS_READY)
		أرجع -1;

	InstancePtr->RecvHandler = FuncPtr;
	InstancePtr->RecvRef = Call_پٺ_Ref;
}


/*****************************************************************************/
/**
*
* Sets the callback function for handling transmitted frames in interrupt mode.
* The upper layer software should call this function during initialization.
* The callback is called when a frame is transmitted. The callback function
* should communicate the data to a thread such that the processing is not
* performed in an interrupt context.
*
* The callback is invoked by the driver within interrupt context, so it needs
* to do its job quickly. If there are other potentially slow operations
* within the callback, these should be done at task-level.
*
* @param	InstancePtr is a pointer to the XEmacLite instance.
* @param	CallBackRef is a reference pointer to be passed back to the
*		application in the callback. This helps the application
*		correlate the callback to a particular driver.
* @param	FuncPtr is the pointer to the callback function.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
فراغ XEmac_Lite_سيٽ_Send_Handler(XEmacLite *InstancePtr, فراغ *Call_پٺ_Ref,
			      XEmacLite_Handler FuncPtr)
{
	إذا(عدم == InstancePtr)
		أرجع -1;
	إذا(عدم == FuncPtr)
		أرجع -1;
	إذا(InstancePtr->IsReady != XIL_COMPONENT_IS_READY)
		أرجع -1;

	InstancePtr->SendHandler = FuncPtr;
	InstancePtr->SendRef = Call_پٺ_Ref;
}


/******************************************************************************/
/**
*
* This function detects the PHY address by looking for successful MII status
* register contents (PHY register 1). It looks for a PHY that supports
* auto-negotiation and 10Mbps full-duplex and half-duplex. So, this code
* won't work for PHYs that don't support those features, but it's a bit more
* general purpose than matching a specific PHY manufacturer ID.
*
* Note also that on some (older) Xilinx ML4xx boards, PHY address 0 does not
* properly respond to this query. But, since the default is 0 and assuming
* no other address responds, then it seems to work OK.
*
* @param	InstancePtr is the pointer to the instance of EmacLite driver.
*
* @return	The address of the PHY device detected (returns 0 if not
*		detected).
*
* @note
*		The bit mask (0x1808) of the MII status register
*		(PHY Register 1) used in this function are:
* 		0x1000: 10Mbps full duplex support.
* 		0x0800: 10Mbps half duplex support.
*  		0x0008: Auto-negotiation support.
*
******************************************************************************/
u32 EmacLitePhyDetect(XEmacLite *InstancePtr)
{
	u16 Phy_معلومات;
	صحيح PhyAddr;

	/*
	 * Verify all 32 MDIO ports.
	 */
	لكل (PhyAddr = 31; PhyAddr >= 0; PhyAddr--) {
		XEmacLite_PhyRead(InstancePtr, PhyAddr, PHY_REG1_وٿي,
				 &Phy_معلومات);

		إذا (Phy_معلومات != 0xFFFF) {
			إذا ((Phy_معلومات & PHY_REG1_DETECT_نقاب) ==
			PHY_REG1_DETECT_نقاب) {
				أرجع PhyAddr;	/* Found a valid PHY device */
			}
		}
	}
	لکو("\n Could not detect phy device");
	/*
	 * Unable to detect PHY device returning the default address of 0.
	 */
	أرجع 0;
}

/******************************************************************************/
/**
*
* This function enables the MAC loopback on the PHY.
*
* @param	InstancePtr is the pointer to the instance of EmacLite driver.
* @param	PhyAddress is the address of the Phy device.
*
* @return
*		- XST_SUCCESS if the loop back is enabled.
*		- XST_FAILURE if the loop back was not enabled.
*
* @note		None.
*
******************************************************************************/
صحيح Emac_Lite_Enable_Phy_Loop_پٺ(XEmacLite *InstancePtr, u32 Phy_پتو)
{
	صحيح حالت;
	u16 Phy_معلومات = 0;

	/*
	 * Set the speed and put the PHY in reset.
	 */
	Phy_معلومات |= PHY_REG0_SPD_100_نقاب;
	حالت = XEmacLite_PhyWrite(InstancePtr, Phy_پتو, PHY_REG0_وٿي,
			Phy_معلومات | PHY_REG0_RESET_نقاب);
	إذا (حالت != XST_SUCCESS) {
		أرجع XST_FAILURE;
	}

	/*
	 * Give sufficient delay for Phy Reset.
	 */
	EmacLitePhyDelay(EMACLITE_PHY_DELAY_SEC);

	/*
	 * Set the PHY in loop back.
	 */
	XEmacLite_PhyWrite(InstancePtr, Phy_پتو, PHY_REG0_وٿي,
			Phy_معلومات | PHY_REG0_LOOPBACK_نقاب);
	إذا (حالت != XST_SUCCESS) {
		أرجع XST_FAILURE;
	}

	/*
	 * Give sufficient delay for Phy Loopback Enable.
	 */
	EmacLitePhyDelay(1);

	أرجع XST_SUCCESS;
}

/******************************************************************************/
/**
*
* This function disables the MAC loopback on the PHY.
*
* @param	InstancePtr is the pointer to the instance of EmacLite driver.
* @param	PhyAddress is the address of the Phy device.
*
* @return
*		- XST_SUCCESS if the loop back was disabled.
*		- XST_FAILURE if the loop back was not disabled.
*
* @note		None.
*
******************************************************************************/
صحيح Emac_Lite_Disable_Phy_Loop_پٺ(XEmacLite *InstancePtr, u32 Phy_پتو)
{
	صحيح حالت;
	u16 Phy_معلومات;

	/*
	 * Disable loop back through PHY register using MDIO support.
	 */
	حالت = XEmacLite_PhyRead(InstancePtr, Phy_پتو, PHY_REG0_وٿي,
					&Phy_معلومات);
	إذا (حالت != XST_SUCCESS) {
		أرجع XST_FAILURE;
	}

	حالت = XEmacLite_PhyWrite(InstancePtr,Phy_پتو, PHY_REG0_وٿي,
					Phy_معلومات & ~(PHY_REG0_LOOPBACK_نقاب));
	إذا (حالت != XST_SUCCESS) {
		أرجع XST_FAILURE;
	}

	أرجع XST_SUCCESS;

}

/******************************************************************************/
/**
*
* For PPC we use a usleep call, for Microblaze we use an assembly loop that
* is roughly the same regardless of optimization level, although caches and
* memory access time can make the delay vary.  Just keep in mind that after
* resetting or updating the PHY modes, the PHY typically needs time to recover.
*
* @return   None
*
* @note     None
*
******************************************************************************/
فراغ EmacLitePhyDelay(بنانشان صحيح Seconds)
{
#جيڪڏهن_وصف_ٿيل __MICROBLAZE__
	ساكن صحيح WarningFlag = 0;

	/* If MB caches are disabled or do not exist, this delay loop could
	 * take minutes instead of seconds (e.g., 30x longer).  Print a warning
	 * message for the user (once).  If only MB had a built-in timer!
	 */
	إذا (((mfmsr() & 0x20) == 0) && (!WarningFlag)) {
#جيڪڏهن_وصف_ٿيل STDOUT_BASEADDRESS
		xil_printf("Warning: This example will take ");
		xil_printf("minutes to complete without I-cache enabled \r\n");
#جيڪڏهن_پورو
		WarningFlag = 1;
	}

#وصف_ڪريو ITERS_في_SEC   (XPAR_CPU_CORE_CLOCK_FREQ_HZ / 6)
    asm متطاير ("\n"
                  "1:               \n\t"
                  "addik r7, r0, %0 \n\t"
                  "2:               \n\t"
                  "addik r7, r7, -1 \n\t"
                  "bneid  r7, 2b    \n\t"
                  "or  r0, r0, r0   \n\t"
                  "bneid %1, 1b     \n\t"
                  "addik %1, %1, -1 \n\t"
                  :: "i"(ITERS_في_SEC), "d" (Seconds));

#وإلا

//	usleep(Seconds * 1000000);
//	waitfor(Seconds * 1000);
#جيڪڏهن_پورو
}


