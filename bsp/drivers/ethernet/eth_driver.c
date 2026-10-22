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
#परिभाषय ETH_VARI 1

#अन्तर्भाव "eth_driver.h"
#अन्तर्भाव "plic_driver.h"
#अन्तर्भाव "platform.h"
#अन्तर्भाव "log.h"
#अन्तर्भाव "stddef.h"
#अन्तर्भाव "gpio.h"
#अन्तर्भाव "utils.h"

/*
 * Variable used to indicate the length of the received frame.
 */
चञ्चल u32 Recv_Frame_दीर्घता;
UINTPTR TxBuffPtr;
UINTPTR RxBuffPtr;
चञ्चल पूर्णाङ्क चौकटाः_Tx;
चञ्चल पूर्णाङ्क चौकटाः_Rx;
चञ्चल पूर्णाङ्क Tx_गणनम्;
चञ्चल पूर्णाङ्क Rx_गणनम्;
चञ्चल पूर्णाङ्क Padding;	/* For 1588 Packets we need to pad 8 bytes time stamp value */

/*
 * Set up valid local MAC addresses. This loop back test uses the LocalAddress
 * both as a source and destination MAC address.
 */

XEmacLite EmacLiteInstance;	/* Instance of the EmacLite */

/*
 * Buffers used for Transmission and Reception of Packets. These are declared
 * as global so that they are not a part of the stack.
 */
u8 TxFrame[XEL_MAX_FRAME_आकार];
u8 RxFrame[XEL_MAX_FRAME_आकार];

चञ्चल u32 Recv_Frame_दीर्घता;	/* Indicates the length of the Received packet
				 */
चञ्चल पूर्णाङ्क TransmitComplete;	/* Flag to indicate that the Transmission
				 * is complete
				 */


शून्य StubHandler(शून्य *Call_पृष्ठभागः_Ref);


/**
 * This table contains configuration information for each EmacLite device
 * in the system.
 */
XEmacLite_Config XEmac_Lite_Config_सारणी = {
	{
	 XPAR_EMACLITE_0_DEVICE_ID,	/* Unique ID of device */
	 XPAR_EMACLITE_0_BASEADDR,	/* Device base address */
	 XPAR_EMACLITE_0_TX_PING_PONG,	/* Include TX Ping Pong buffers */
	 XPAR_EMACLITE_0_RX_PING_PONG,	/* Include RX Ping Pong buffers */
	 XPAR_EMACLITE_0_INCLUDE_MDIO,	/* Include MDIO support */
	 XPAR_EMACLITE_0_INCLUDE_आन्तरिकम्_LOOPBACK
/* Include Internal  loop back support */
	 }
};



/************************** Function Prototypes ******************************/

स्थिर u16 XEmac_Lite_Get_Receive_दत्त_दीर्घता(UINTPTR आधारः_स्थानाङ्कः);

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
स्थिर INLINE u8 Xil_In8(UINTPTR Addr)
{
	प्रत्यागम *(चञ्चल u8 *) Addr;
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
स्थिर INLINE u16 Xil_In16(UINTPTR Addr)
{
	प्रत्यागम *(चञ्चल u16 *) Addr;
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
स्थिर INLINE u32 Xil_In32(UINTPTR Addr)
{
	प्रत्यागम *(चञ्चल u32 *) Addr;
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
स्थिर INLINE u64 Xil_In64(UINTPTR Addr)
{
	प्रत्यागम *(चञ्चल u64 *) Addr;
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
स्थिर INLINE शून्य Xil_Out8(UINTPTR Addr, u8 मानम्_2)
{
	चञ्चल u8 *LocalAddr = (चञ्चल u8 *)Addr;
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
स्थिर INLINE शून्य Xil_Out16(UINTPTR Addr, u16 मानम्_2)
{
	चञ्चल u16 *LocalAddr = (चञ्चल u16 *)Addr;
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
स्थिर INLINE शून्य Xil_Out32(UINTPTR Addr, u32 मानम्_2)
{
	चञ्चल u32 *LocalAddr = (चञ्चल u32 *)Addr;
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
स्थिर INLINE शून्य Xil_Out64(UINTPTR Addr, u64 मानम्_2)
{
	चञ्चल u64 *LocalAddr = (चञ्चल u64 *)Addr;
	*LocalAddr = मानम्_2;
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
u16 Xil_EndianSwap16(u16 दत्त)
{
	प्रत्यागम (u16) (((दत्त & 0xFF00U) >> 8U) | ((दत्त & 0x00FFU) << 8U));
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
u32 Xil_EndianSwap32(u32 दत्त)
{
	u16 LoWord;
	u16 HiWord;

	/* get each of the half words from the 32 bit word */

	LoWord = (u16) (दत्त & 0x0000FFFFU);
	HiWord = (u16) ((दत्त & 0xFFFF0000U) >> 16U);

	/* byte swap each of the 16 bit half words */

	LoWord = (((LoWord & 0xFF00U) >> 8U) | ((LoWord & 0x00FFU) << 8U));
	HiWord = (((HiWord & 0xFF00U) >> 8U) | ((HiWord & 0x00FFU) << 8U));

	/* swap the half words before returning the value */

	प्रत्यागम ((((u32)LoWord) << (u32)16U) | (u32)HiWord);
}


/************************** Variable Definitions *****************************/



u16 Xil_Htons(u16 दत्त)
{
	प्रत्यागम (u16) (((दत्त & 0xFF00U) >> 8U) | ((दत्त & 0x00FFU) << 8U));
}

u16 Xil_Ntohs(u16 दत्त)
{
	प्रत्यागम (u16) (((दत्त & 0xFF00U) >> 8U) | ((दत्त & 0x00FFU) << 8U));
}


#यदि 0
#परिभाषय Xil_In16LE	Xil_In16
#परिभाषय Xil_In32LE	Xil_In32
#परिभाषय Xil_Out16LE	Xil_Out16
#परिभाषय Xil_Out32LE	Xil_Out32
#परिभाषय Xil_Htons	Xil_EndianSwap16
#परिभाषय Xil_Htonl	Xil_EndianSwap32
#परिभाषय Xil_Ntohs	Xil_EndianSwap16
#परिभाषय Xil_Ntohl	Xil_EndianSwap32
#यदि_अन्तः


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
#परिभाषय XEmacLite_ReadReg(आधारः_स्थानाङ्कः, Reg_विस्थापनम्) \
	XEmacLite_In32((आधारः_स्थानाङ्कः) + (Reg_विस्थापनम्))

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
#परिभाषय XEmacLite_WriteReg(आधारः_स्थानाङ्कः, Reg_विस्थापनम्, पञ्जिकाकोशः_मानम्) \
	XEmacLite_Out32((आधारः_स्थानाङ्कः) + (Reg_विस्थापनम्), (पञ्जिकाकोशः_मानम्))


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
#परिभाषय XEmac_Lite_Get_Tx_स्थितिः(आधारः_स्थानाङ्कः)			\
	(XEmacLite_ReadReg((आधारः_स्थानाङ्कः), XEL_TSR_विस्थापनम्))


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
#परिभाषय XEmac_Lite_समुच्चयः_Tx_स्थितिः(आधारः_स्थानाङ्कः, दत्त)			\
	(XEmacLite_WriteReg((आधारः_स्थानाङ्कः), XEL_TSR_विस्थापनम्, (दत्त)))


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
#परिभाषय XEmac_Lite_Get_Rx_स्थितिः(आधारः_स्थानाङ्कः)			\
	(XEmacLite_ReadReg((आधारः_स्थानाङ्कः), XEL_RSR_विस्थापनम्))


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
#परिभाषय XEmac_Lite_समुच्चयः_Rx_स्थितिः(आधारः_स्थानाङ्कः, दत्त)			\
	(XEmacLite_WriteReg((आधारः_स्थानाङ्कः), XEL_RSR_विस्थापनम्, (दत्त)))


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
#परिभाषय XEmac_Lite_Is_Tx_समाप्तम्(आधारः_स्थानाङ्कः)			\
		 ((XEmacLite_ReadReg((आधारः_स्थानाङ्कः), XEL_TSR_विस्थापनम्) & 	 \
			 XEL_TSR_XMIT_BUSY_आवरणम्) != XEL_TSR_XMIT_BUSY_आवरणम्)


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
#परिभाषय XEmac_Lite_Is_Rx_रिक्तानि(आधारः_स्थानाङ्कः) \
		  ((XEmacLite_ReadReg((आधारः_स्थानाङ्कः), XEL_RSR_विस्थापनम्) & \
			XEL_RSR_RECV_समाप्तम्_आवरणम्) != XEL_RSR_RECV_समाप्तम्_आवरणम्)

/************************** Function Prototypes ******************************/

शून्य XEmacLite_SendFrame(UINTPTR आधारः_स्थानाङ्कः, u8 *FramePtr, अचिह्नित Byte_गणनम्);
u16 XEmacLite_RecvFrame(UINTPTR आधारः_स्थानाङ्कः, u8 *FramePtr);

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
शून्य XEmacLite_SendFrame(UINTPTR आधारः_स्थानाङ्कः, u8 *FramePtr, अचिह्नित Byte_गणनम्)
{
	u32 पञ्जिकाकोशः;

	/*
	 * Write data to the EmacLite
	 */
	XEmacLite_AlignedWrite(FramePtr, (UINTPTR *) (आधारः_स्थानाङ्कः), Byte_गणनम्);

	/*
	 * The frame is in the buffer, now send it
	 */
	XEmacLite_WriteReg(आधारः_स्थानाङ्कः,  XEL_TPLR_विस्थापनम्,
				(Byte_गणनम् & (XEL_TPLR_दीर्घता_आवरणम्_HI |
				XEL_TPLR_दीर्घता_आवरणम्_LO)));


	पञ्जिकाकोशः = XEmac_Lite_Get_Tx_स्थितिः(आधारः_स्थानाङ्कः);
	XEmac_Lite_समुच्चयः_Tx_स्थितिः(आधारः_स्थानाङ्कः, पञ्जिकाकोशः | XEL_TSR_XMIT_BUSY_आवरणम्);

	/*
	 * Loop on the status waiting for the transmit to be complete.
	 */
	यावत् (!XEmac_Lite_Is_Tx_समाप्तम्(आधारः_स्थानाङ्कः));

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
u16 XEmacLite_RecvFrame(UINTPTR आधारः_स्थानाङ्कः, u8 *FramePtr)
{
	u16 दीर्घता_Type;
	u16 दीर्घता;
	u32 पञ्जिकाकोशः;

	/*
	 * Wait for a frame to arrive - this is a blocking call
	 */
	यावत् (XEmac_Lite_Is_Rx_रिक्तानि(आधारः_स्थानाङ्कः));

	/*
	 * Get the length of the frame that arrived, only 32-bit reads are
	 * allowed LengthType is in the upper half of the 32-bit word.
	 */
	पञ्जिकाकोशः = XEmacLite_ReadReg(आधारः_स्थानाङ्कः, XEL_RPLR_विस्थापनम्);
	दीर्घता_Type = (u16) ((पञ्जिकाकोशः >> 16) &
			    (XEL_RPLR_दीर्घता_आवरणम्_HI |
			     XEL_RPLR_दीर्घता_आवरणम्_LO));

	/*
	 * Check if length is valid
	 */
	यदि (दीर्घता_Type > XEL_MAX_FRAME_आकार) {
		/*
		 * Field contain type, use max frame size and
		 * let user parse it
		 */
		दीर्घता = XEL_MAX_FRAME_आकार;
	}
	अन्यथा {
		/*
		 * Use the length in the frame, plus the header and trailer
		 */
		दीर्घता = दीर्घता_Type + XEL_शीर्षकम्_आकार + XEL_FCS_आकार;
	}

	/*
	 * Read each byte from the EmacLite
	 */
	XEmacLite_AlignedRead((UINTPTR *) (आधारः_स्थानाङ्कः + XEL_RXBUFF_विस्थापनम्),
			      FramePtr, दीर्घता);

	/*
	 * Acknowledge the frame
	 */
	पञ्जिकाकोशः = XEmac_Lite_Get_Rx_स्थितिः(आधारः_स्थानाङ्कः);
	पञ्जिकाकोशः &= ~XEL_RSR_RECV_समाप्तम्_आवरणम्;
	XEmac_Lite_समुच्चयः_Rx_स्थितिः(आधारः_स्थानाङ्कः, पञ्जिकाकोशः);

	प्रत्यागम दीर्घता_Type;
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
शून्य XEmacLite_AlignedWrite(शून्य *SrcPtr, UINTPTR *DestPtr, अचिह्नित Byte_गणनम्)
{
	अचिह्नित सूचकांक;
	अचिह्नित दीर्घता = Byte_गणनम्;
	चञ्चल u32 Align_बफर;
	चञ्चल u32 *To32Ptr;
	u32 *From32Ptr;
	चञ्चल u16 *To16Ptr;
	u16 *From16Ptr;
	चञ्चल u8 *To8Ptr;
	u8 *From8Ptr;

//	To32Ptr = (volatile UINTPTR *)DestPtr;

	यदि ((((u32) SrcPtr) & 0x00000003) == 0) {

		/*
		 * Word aligned buffer, no correction needed.
		 */
		From32Ptr = (u32 *) SrcPtr;
		To32Ptr = (u32 *)DestPtr;
#यदि 0
		log_info("length is %x", दीर्घता);
		log_info("\n Size of To32Ptr: %x", परिमाण(*To32Ptr));
		log_info("\n Size of From32Ptr: %x", परिमाण(*From32Ptr));
#यदि_अन्तः		
		यावत् (दीर्घता > 3) {
			/*
			 * Output each word destination.
			 */
			*To32Ptr++ = *From32Ptr++;
#यदि 0
			*To32Ptr = *From32Ptr++;
			प्रारूप_लिख("\n Write value @ %x: %x", To32Ptr, *To32Ptr);
			*To32Ptr++;

//#else
			*To32Ptr = *From32Ptr;
			log_info("\n 1:[%x]; 2: [%x]", *To32Ptr, *From32Ptr);
			log_info("\n 1:[%x]; 2: [%x]", To32Ptr, From32Ptr);
			*To32Ptr++;
			*From32Ptr++;
			log_info("\n 1_2:[%x]; 2: [%x]", *To32Ptr, *From32Ptr);
			log_info("\n 1_2:[%x]; 2: [%x]", To32Ptr, From32Ptr);
#यदि_अन्तः
			/*
			 * Adjust length accordingly
			 */
			दीर्घता -= 4;
		}

		/*
		 * Set up to output the remaining data, zero the temp buffer
		 first.
		 */
		Align_बफर = 0;
		To8Ptr = (u8 *) &Align_बफर;
		From8Ptr = (u8 *) From32Ptr;

	}
	अन्यथा यदि ((((u32) SrcPtr) & 0x00000001) != 0) {
		/*
		 * Byte aligned buffer, correct.
		 */
		Align_बफर = 0;
		To8Ptr = (u8 *) &Align_बफर;
		From8Ptr = (u8 *) SrcPtr;

		यावत् (दीर्घता > 3) {
			/*
			 * Copy each byte into the temporary buffer.
			 */
			प्रति (सूचकांक = 0; सूचकांक < 4; सूचकांक++) {
				*To8Ptr++ = *From8Ptr++;
			}

			/*
			 * Output the buffer
			 */
			*To32Ptr++ = Align_बफर;

			/*.
			 * Reset the temporary buffer pointer and adjust length.
			 */
			To8Ptr = (u8 *) &Align_बफर;
			दीर्घता -= 4;
		}

		/*
		 * Set up to output the remaining data, zero the temp buffer
		 * first.
		 */
		Align_बफर = 0;
		To8Ptr = (u8 *) &Align_बफर;

	}
	अन्यथा {
		/*
		 * Half-Word aligned buffer, correct.
		 */
		Align_बफर = 0;

		/*
		 * This is a funny looking cast. The new gcc, version 3.3.x has
		 * a strict cast check for 16 bit pointers, aka short pointers.
		 * The following warning is issued if the initial 'void *' cast
		 * is  not used:
		 * 'dereferencing type-punned pointer will break strict-aliasing
		 * rules'
		 */

		To16Ptr = (u16 *) ((शून्य *) &Align_बफर);
		From16Ptr = (u16 *) SrcPtr;

		यावत् (दीर्घता > 3) {
			/*
			 * Copy each half word into the temporary buffer.
			 */
			प्रति (सूचकांक = 0; सूचकांक < 2; सूचकांक++) {
				*To16Ptr++ = *From16Ptr++;
			}

			/*
			 * Output the buffer.
			 */
			*To32Ptr++ = Align_बफर;

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
			To16Ptr = (u16 *) ((शून्य *) &Align_बफर);
			दीर्घता -= 4;
		}

		/*
		 * Set up to output the remaining data, zero the temp buffer
		 * first.
		 */
		Align_बफर = 0;
		To8Ptr = (u8 *) &Align_बफर;
		From8Ptr = (u8 *) From16Ptr;
	}

	/*
	 * Output the remaining data, zero the temp buffer first.
	 */
	प्रति (सूचकांक = 0; सूचकांक < दीर्घता; सूचकांक++) {
		*To8Ptr++ = *From8Ptr++;
	}
	यदि (दीर्घता) {
		*To32Ptr++ = Align_बफर;
	}
	To32Ptr = (चञ्चल UINTPTR *)DestPtr;
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
शून्य XEmacLite_AlignedRead(UINTPTR *SrcPtr, शून्य *DestPtr, अचिह्नित Byte_गणनम्)
{
	अचिह्नित सूचकांक;
	अचिह्नित दीर्घता = Byte_गणनम्;
	चञ्चल u32 Align_बफर;
	u32 *To32Ptr;
	चञ्चल u32 *From32Ptr;
	u16 *To16Ptr;
	चञ्चल u16 *From16Ptr;
	u8 *To8Ptr;
	चञ्चल u8 *From8Ptr;

	From32Ptr = (u32 *) SrcPtr;

	यदि ((((u32) DestPtr) & 0x00000003) == 0) {

		/*
		 * Word aligned buffer, no correction needed.
		 */
		To32Ptr = (u32 *) DestPtr;
//		log_info("\n Read: 1:[%x]; 2: [%x]", *To32Ptr, *From32Ptr);
//		log_info("\n 1:[%x]; 2: [%x]", To32Ptr, From32Ptr);

		यावत् (दीर्घता > 3) {
			/*
			 * Output each word.
			 */
			*To32Ptr++ = *From32Ptr++;

			/*
			 * Adjust length accordingly.
			 */
			दीर्घता -= 4;
		}

		/*
		 * Set up to read the remaining data.
		 */
		To8Ptr = (u8 *) To32Ptr;

	}
	अन्यथा यदि ((((u32) DestPtr) & 0x00000001) != 0) {
		/*
		 * Byte aligned buffer, correct.
		 */
		To8Ptr = (u8 *) DestPtr;

		यावत् (दीर्घता > 3) {
			/*
			 * Copy each word into the temporary buffer.
			 */
			Align_बफर = *From32Ptr++;
			From8Ptr = (u8 *) &Align_बफर;

			/*
			 * Write data to destination.
			 */
			प्रति (सूचकांक = 0; सूचकांक < 4; सूचकांक++) {
				*To8Ptr++ = *From8Ptr++;
			}

			/*
			 * Adjust length
			 */
			दीर्घता -= 4;
		}

	}
	अन्यथा {
		/*
		 * Half-Word aligned buffer, correct.
		 */
		To16Ptr = (u16 *) DestPtr;

		यावत् (दीर्घता > 3) {
			/*
			 * Copy each word into the temporary buffer.
			 */
			Align_बफर = *From32Ptr++;

			/*
			 * This is a funny looking cast. The new gcc, version
			 * 3.3.x has a strict cast check for 16 bit pointers,
			 * aka short pointers. The following warning is issued
			 * if the initial 'void *' cast is not used:
			 * 'dereferencing type-punned pointer will break
			 *  strict-aliasing rules'
			 */
			From16Ptr = (u16 *) ((शून्य *) &Align_बफर);

			/*
			 * Write data to destination.
			 */
			प्रति (सूचकांक = 0; सूचकांक < 2; सूचकांक++) {
				*To16Ptr++ = *From16Ptr++;
			}

			/*
			 * Adjust length.
			 */
			दीर्घता -= 4;
		}

		/*
		 * Set up to read the remaining data.
		 */
		To8Ptr = (u8 *) To16Ptr;
	}

	/*
	 * Read the remaining data.
	 */
	Align_बफर = *From32Ptr++;
	From8Ptr = (u8 *) &Align_बफर;

	प्रति (सूचकांक = 0; सूचकांक < दीर्घता; सूचकांक++) {
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
पूर्णाङ्क XEmacLite_CfgInitialize(XEmacLite *InstancePtr,
				XEmacLite_Config *EmacLiteConfigPtr,
				UINTPTR EffectiveAddr)
{

	/*
	 * Verify that each of the inputs are valid.
	 */
//	Xil_AssertNonvoid(InstancePtr != NULL);
	यदि(रिक्त == InstancePtr)
	{
		log_error("\nEthernet Parameter - InstancePtr is Null");
		प्रत्यागम -1;
	}
//	Xil_AssertNonvoid(EmacLiteConfigPtr != NULL);
	यदि(रिक्त == EmacLiteConfigPtr)
	{
		log_error("Ethernet Parameter - EmacLiteConfigPtr is Null");
		प्रत्यागम -1;
	}

	/*
	 * Zero the provided instance memory.
	 */
	स्मृतिं_पूरय(InstancePtr, 0, परिमाण(XEmacLite));

	/*
	 * Set some default values for instance data, don't indicate the device
	 * is ready to use until everything has been initialized successfully.
	 */
	InstancePtr->EmacLiteConfig.आधारः_स्थानाङ्कः = EffectiveAddr;
	InstancePtr->EmacLiteConfig.DeviceId = EmacLiteConfigPtr->DeviceId;
	InstancePtr->EmacLiteConfig.TxPingPong = EmacLiteConfigPtr->TxPingPong;
	InstancePtr->EmacLiteConfig.RxPingPong = EmacLiteConfigPtr->RxPingPong;
	InstancePtr->EmacLiteConfig.MdioInclude = EmacLiteConfigPtr->MdioInclude;
	InstancePtr->EmacLiteConfig.Loopback = EmacLiteConfigPtr->Loopback;

	InstancePtr->अग्र_Tx_बफर_गन्तव्यम्_Use = 0x0;
	InstancePtr->अग्र_Rx_बफर_गन्तव्यम्_Use = 0x0;
	InstancePtr->RecvHandler = (XEmacLite_Handler) StubHandler;
	InstancePtr->SendHandler = (XEmacLite_Handler) StubHandler;
	/*
	 * Clear the TX CSR's in case this is a restart.
	 */
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.आधारः_स्थानाङ्कः,
				XEL_TSR_विस्थापनम्, 0);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.आधारः_स्थानाङ्कः,
				XEL_बफर_विस्थापनम् + XEL_TSR_विस्थापनम्, 0);

	/*
	 * Since there were no failures, indicate the device is ready to use.
	 */
	InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

	प्रत्यागम SUCCESS;
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
पूर्णाङ्क XEmacLite_Send(XEmacLite *InstancePtr, u8 *FramePtr, अचिह्नित Byte_गणनम्)
{
	u32 पञ्जिकाकोशः;
	UINTPTR आधारः_स्थानाङ्कः;
	UINTPTR Emac_आधारः_स्थानाङ्कः;
	u32 Intr_Enable_स्थितिः;

	/*
	 * Verify that each of the inputs are valid.
	 */
//	Xil_AssertNonvoid(InstancePtr != NULL);
	यदि (InstancePtr == रिक्त) {
		प्रत्यागम -1;
	}

	/*
	 * Determine the expected TX buffer address.
	 */
	आधारः_स्थानाङ्कः = XEmac_Lite_अग्र_Transmit_Addr(InstancePtr);
	Emac_आधारः_स्थानाङ्कः = InstancePtr->EmacLiteConfig.आधारः_स्थानाङ्कः;

	/*
	 * Check the Length if it is too large, truncate it.
	 * The maximum Tx packet size is
	 * Ethernet header (14 Bytes) + Maximum MTU (1500 bytes).
	 */
	यदि (Byte_गणनम् > XEL_MAX_TX_FRAME_आकार) {

		Byte_गणनम् = XEL_MAX_TX_FRAME_आकार;
	}

	/*
	 * Determine if the expected buffer address is empty.
	 */
	पञ्जिकाकोशः = XEmac_Lite_Get_Tx_स्थितिः(आधारः_स्थानाङ्कः);

	/*
	 * If the expected buffer is available, fill it with the provided data
	 * Align if necessary.
	 */
	यदि ((पञ्जिकाकोशः & (XEL_TSR_XMIT_BUSY_आवरणम् |
			XEL_TSR_XMIT_सक्रिय_आवरणम्)) == 0) {

		/*
		 * Switch to next buffer if configured.
		 */
		यदि (InstancePtr->EmacLiteConfig.TxPingPong != 0) {
			InstancePtr->अग्र_Tx_बफर_गन्तव्यम्_Use ^= XEL_बफर_विस्थापनम्;
		}

		/*
		 * Write the frame to the buffer.
		 */
		XEmacLite_AlignedWrite(FramePtr, (UINTPTR *) आधारः_स्थानाङ्कः,
				       Byte_गणनम्);


		/*
		 * The frame is in the buffer, now send it.
		 */
		XEmacLite_WriteReg(आधारः_स्थानाङ्कः, XEL_TPLR_विस्थापनम्,
					(Byte_गणनम् & (XEL_TPLR_दीर्घता_आवरणम्_HI |
					XEL_TPLR_दीर्घता_आवरणम्_LO)));

		/*
		 * Update the Tx Status Register to indicate that there is a
		 * frame to send.
		 * If the interrupt enable bit of Ping buffer(since this
		 * controls both the buffers) is enabled then set the
		 * XEL_TSR_XMIT_ACTIVE_MASK flag which is used by the interrupt
		 * handler to call the callback function provided by the user
		 * to indicate that the frame has been transmitted.
		 */
		पञ्जिकाकोशः = XEmac_Lite_Get_Tx_स्थितिः(आधारः_स्थानाङ्कः);
		पञ्जिकाकोशः |= XEL_TSR_XMIT_BUSY_आवरणम्;
		Intr_Enable_स्थितिः = XEmac_Lite_Get_Tx_स्थितिः(Emac_आधारः_स्थानाङ्कः);
		यदि ((Intr_Enable_स्थितिः & XEL_TSR_XMIT_IE_आवरणम्) != 0) {
			पञ्जिकाकोशः |= XEL_TSR_XMIT_सक्रिय_आवरणम्;
		}
		XEmac_Lite_समुच्चयः_Tx_स्थितिः(आधारः_स्थानाङ्कः, पञ्जिकाकोशः);

		प्रत्यागम SUCCESS;
	}

	/*
	 * If the expected buffer was full, try the other buffer if configured.
	 */
	यदि (InstancePtr->EmacLiteConfig.TxPingPong != 0) {

		आधारः_स्थानाङ्कः ^= XEL_बफर_विस्थापनम्;

		/*
		 * Determine if the expected buffer address is empty.
		 */
		पञ्जिकाकोशः = XEmac_Lite_Get_Tx_स्थितिः(आधारः_स्थानाङ्कः);

		/*
		 * If the next buffer is available, fill it with the provided
		 * data.
		 */
		यदि ((पञ्जिकाकोशः & (XEL_TSR_XMIT_BUSY_आवरणम् |
				XEL_TSR_XMIT_सक्रिय_आवरणम्)) == 0) {

			/*
			 * Write the frame to the buffer.
			 */
			XEmacLite_AlignedWrite(FramePtr, (UINTPTR *) आधारः_स्थानाङ्कः,
					       Byte_गणनम्);

			/*
			 * The frame is in the buffer, now send it.
			 */
			XEmacLite_WriteReg(आधारः_स्थानाङ्कः, XEL_TPLR_विस्थापनम्,
					(Byte_गणनम् & (XEL_TPLR_दीर्घता_आवरणम्_HI |
					   XEL_TPLR_दीर्घता_आवरणम्_LO)));

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
			पञ्जिकाकोशः = XEmac_Lite_Get_Tx_स्थितिः(आधारः_स्थानाङ्कः);
			पञ्जिकाकोशः |= XEL_TSR_XMIT_BUSY_आवरणम्;
			Intr_Enable_स्थितिः =
					XEmac_Lite_Get_Tx_स्थितिः(Emac_आधारः_स्थानाङ्कः);
			यदि ((Intr_Enable_स्थितिः & XEL_TSR_XMIT_IE_आवरणम्) != 0) {
				पञ्जिकाकोशः |= XEL_TSR_XMIT_सक्रिय_आवरणम्;
			}
			XEmac_Lite_समुच्चयः_Tx_स्थितिः(आधारः_स्थानाङ्कः, पञ्जिकाकोशः);

			/*
			 * Do not switch to next buffer, there is a sync problem
			 * and the expected buffer should not change.
			 */
			प्रत्यागम SUCCESS;
		}
	}

	प्रारूप_लिख("\n Error in sending the packet");
	/*
	 * Buffer(s) was(were) full, return failure to allow for polling usage.
	 */
	प्रत्यागम FAILURE;
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
u16 XEmacLite_Recv(XEmacLite *InstancePtr, u8 *FramePtr)
{
	u16 दीर्घता_Type;
	u16 दीर्घता;
	u32 पञ्जिकाकोशः;
	UINTPTR आधारः_स्थानाङ्कः;

	/*
	 * Verify that each of the inputs are valid.
	 */

	यदि (InstancePtr == रिक्त) {
		प्रत्यागम -1;
	}

	/*
	 * Determine the expected buffer address.
	 */
	आधारः_स्थानाङ्कः = XEmac_Lite_अग्र_Receive_Addr(InstancePtr);

	/*
	 * Verify which buffer has valid data.
	 */
	पञ्जिकाकोशः = XEmac_Lite_Get_Rx_स्थितिः(आधारः_स्थानाङ्कः);

	यदि ((पञ्जिकाकोशः & XEL_RSR_RECV_समाप्तम्_आवरणम्) == XEL_RSR_RECV_समाप्तम्_आवरणम्) {

		/*
		 * The driver is in sync, update the next expected buffer if
		 * configured.
		 */

		यदि (InstancePtr->EmacLiteConfig.RxPingPong != 0) {
			InstancePtr->अग्र_Rx_बफर_गन्तव्यम्_Use ^= XEL_बफर_विस्थापनम्;
		}
	}
	अन्यथा {
		/*
		 * The instance is out of sync, try other buffer if other
		 * buffer is configured, return 0 otherwise. If the instance is
		 * out of sync, do not update the 'NextRxBufferToUse' since it
		 * will correct on subsequent calls.
		 */
		यदि (InstancePtr->EmacLiteConfig.RxPingPong != 0) {
			आधारः_स्थानाङ्कः ^= XEL_बफर_विस्थापनम्;
		}
		अन्यथा {
			प्रत्यागम 0;	/* No data was available */
		}

		/*
		 * Verify that buffer has valid data.
		 */
		पञ्जिकाकोशः = XEmac_Lite_Get_Rx_स्थितिः(आधारः_स्थानाङ्कः);
		यदि ((पञ्जिकाकोशः & XEL_RSR_RECV_समाप्तम्_आवरणम्) !=
				XEL_RSR_RECV_समाप्तम्_आवरणम्) {
			प्रत्यागम 0;	/* No data was available */
		}
	}

	/*
	 * Get the length of the frame that arrived.
	 */
	दीर्घता_Type = XEmac_Lite_Get_Receive_दत्त_दीर्घता(आधारः_स्थानाङ्कः);

	/*
	 * Check if length is valid.
	 */
	यदि (दीर्घता_Type > XEL_MAX_FRAME_आकार) {


		यदि (दीर्घता_Type == XEL_ETHER_PROTO_TYPE_IP) {

			/*
			 * The packet is a an IP Packet.
			 */
#यदि_परिभाषितम् __LITTLE_ENDIAN__
			दीर्घता = (XEmacLite_ReadReg((आधारः_स्थानाङ्कः),
					XEL_शीर्षकम्_IP_दीर्घता_विस्थापनम् +
					XEL_RXBUFF_विस्थापनम्) &
					(XEL_RPLR_दीर्घता_आवरणम्_HI |
					XEL_RPLR_दीर्घता_आवरणम्_LO));
			दीर्घता = (u16) (((दीर्घता & 0xFF00) >> 8) | ((दीर्घता & 0x00FF) << 8));
#अन्यथा
			दीर्घता = ((XEmacLite_ReadReg((आधारः_स्थानाङ्कः),
					XEL_शीर्षकम्_IP_दीर्घता_विस्थापनम् +
					XEL_RXBUFF_विस्थापनम्) >>
					XEL_शीर्षकम्_सरणम्) &
					(XEL_RPLR_दीर्घता_आवरणम्_HI |
					XEL_RPLR_दीर्घता_आवरणम्_LO));
#यदि_अन्तः

//			Length += XEL_HEADER_SIZE + XEL_FCS_SIZE;
			दीर्घता += XEL_शीर्षकम्_आकार;
//			printf("\n Length1 is %x", Length);

		} अन्यथा यदि (दीर्घता_Type == XEL_ETHER_PROTO_TYPE_ARP) {

			/*
			 * The packet is an ARP Packet.
			 */
			दीर्घता = XEL_ARP_PACKET_आकार + XEL_शीर्षकम्_आकार +
					XEL_FCS_आकार;

		} अन्यथा {
			/*
			 * Field contains type other than IP or ARP, use max
			 * frame size and let user parse it.
			 */
			दीर्घता = XEL_MAX_FRAME_आकार;

		}
	} अन्यथा {

		/*
		 * Use the length in the frame, plus the header and trailer.
		 */
		दीर्घता = दीर्घता_Type + XEL_शीर्षकम्_आकार + XEL_FCS_आकार;
	}

	/*
	 * Read from the EmacLite.
	 */
	XEmacLite_AlignedRead(((UINTPTR *) (आधारः_स्थानाङ्कः + XEL_RXBUFF_विस्थापनम्)),
			      FramePtr, दीर्घता);

	/*
	 * Acknowledge the frame.
	 */
	पञ्जिकाकोशः = XEmac_Lite_Get_Rx_स्थितिः(आधारः_स्थानाङ्कः);
	पञ्जिकाकोशः &= ~XEL_RSR_RECV_समाप्तम्_आवरणम्;
	XEmac_Lite_समुच्चयः_Rx_स्थितिः(आधारः_स्थानाङ्कः, पञ्जिकाकोशः);

	प्रत्यागम दीर्घता;
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
शून्य XEmac_Lite_समुच्चयः_Mac_स्थानाङ्कः(XEmacLite *InstancePtr, u8 *स्थानाङ्कः_Ptr)
{
	UINTPTR आधारः_स्थानाङ्कः;

	/*
	 * Verify that each of the inputs are valid.
	 */
	यदि (InstancePtr == रिक्त) {
		प्रत्यागम -1;
	}

	/*
	 * Determine the expected TX buffer address.
	 */
	आधारः_स्थानाङ्कः = XEmac_Lite_अग्र_Transmit_Addr(InstancePtr);

	/*
	 * Copy the MAC address to the Transmit buffer.
	 */
	XEmacLite_AlignedWrite(स्थानाङ्कः_Ptr,
				(UINTPTR *) आधारः_स्थानाङ्कः,
				XEL_MAC_ADDR_आकार);

	/*
	 * Set the length.
	 */
	XEmacLite_WriteReg(आधारः_स्थानाङ्कः,
				XEL_TPLR_विस्थापनम्,
				XEL_MAC_ADDR_आकार);

	/*
	 * Update the MAC address in the EmacLite.
	 */
	XEmac_Lite_समुच्चयः_Tx_स्थितिः(आधारः_स्थानाङ्कः, XEL_TSR_PROG_MAC_ADDR);


	/*
	 * Wait for EmacLite to finish with the MAC address update.
	 */
	यावत् ((XEmac_Lite_Get_Tx_स्थितिः(आधारः_स्थानाङ्कः) &
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
शून्य StubHandler(शून्य *Call_पृष्ठभागः_Ref)
{
	(शून्य)(Call_पृष्ठभागः_Ref);
	प्रत्यागम 1;
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
पूर्णाङ्क XEmac_Lite_Tx_बफर_उपलब्धम्(XEmacLite *InstancePtr)
{

	u32 पञ्जिकाकोशः;
	पूर्णाङ्क TxPingBusy;
	पूर्णाङ्क TxPongBusy;

	/*
	 * Verify that each of the inputs are valid.
	 */
	यदि (InstancePtr == रिक्त) {
		प्रत्यागम -1;
	}

	/*
	 * Read the Tx Status and determine if the buffer is available.
	 */
	पञ्जिकाकोशः = XEmac_Lite_Get_Tx_स्थितिः(InstancePtr->EmacLiteConfig.
						आधारः_स्थानाङ्कः);

	TxPingBusy = (पञ्जिकाकोशः & (XEL_TSR_XMIT_BUSY_आवरणम् |
				 XEL_TSR_XMIT_सक्रिय_आवरणम्));


	/*
	 * Read the Tx Status of the second buffer register and determine if the
	 * buffer is available.
	 */
	यदि (InstancePtr->EmacLiteConfig.TxPingPong != 0) {
		पञ्जिकाकोशः = XEmac_Lite_Get_Tx_स्थितिः(InstancePtr->EmacLiteConfig.
						आधारः_स्थानाङ्कः +
						XEL_बफर_विस्थापनम्);

		TxPongBusy = (पञ्जिकाकोशः & (XEL_TSR_XMIT_BUSY_आवरणम् |
					XEL_TSR_XMIT_सक्रिय_आवरणम्));

		प्रत्यागम (!(TxPingBusy && TxPongBusy));
	}

	प्रत्यागम (!TxPingBusy);


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
शून्य XEmacLite_FlushReceive(XEmacLite *InstancePtr)
{

	u32 पञ्जिकाकोशः;

	/*
	 * Verify that each of the inputs are valid.
	 */
		यदि (InstancePtr == रिक्त) {
			प्रत्यागम -1;
		}

	/*
	 * Read the current buffer register and determine if the buffer is
	 * available.
	 */
	पञ्जिकाकोशः = XEmac_Lite_Get_Rx_स्थितिः(InstancePtr->EmacLiteConfig.
						आधारः_स्थानाङ्कः);

	/*
	 * Preserve the IE bit.
	 */
	पञ्जिकाकोशः &= XEL_RSR_RECV_IE_आवरणम्;

	/*
	 * Write out the value to flush the RX buffer.
	 */
	XEmac_Lite_समुच्चयः_Rx_स्थितिः(InstancePtr->EmacLiteConfig.आधारः_स्थानाङ्कः,
				पञ्जिकाकोशः);

	/*
	 * If the pong buffer is available, flush it also.
	 */
	यदि (InstancePtr->EmacLiteConfig.RxPingPong != 0) {
		/*
		 * Read the current buffer register and determine if the buffer
		 * is available.
		 */
		पञ्जिकाकोशः = XEmac_Lite_Get_Rx_स्थितिः(InstancePtr->EmacLiteConfig.
							आधारः_स्थानाङ्कः +
							XEL_बफर_विस्थापनम्);

		/*
		 * Preserve the IE bit.
		 */
		पञ्जिकाकोशः &= XEL_RSR_RECV_IE_आवरणम्;

		/*
		 * Write out the value to flush the RX buffer.
		 */
		XEmac_Lite_समुच्चयः_Rx_स्थितिः(InstancePtr->EmacLiteConfig.आधारः_स्थानाङ्कः +
					XEL_बफर_विस्थापनम्, पञ्जिकाकोशः);

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
पूर्णाङ्क XEmacLite_PhyRead(XEmacLite *InstancePtr, u32 Phy_स्थानाङ्कः, u32 Reg_अङ्कः,
			u16 *Phy_दत्त_Ptr)
{
	u32 PhyAddrReg;
	u32 MdioCtrlReg;

	/*
	 * Verify that each of the inputs are valid.
	 */
		यदि (InstancePtr == रिक्त) {
			प्रत्यागम -1;
		}
		यदि (InstancePtr->EmacLiteConfig.MdioInclude == TRUE) {
			प्रत्यागम -1;
		}
		यदि (Phy_स्थानाङ्कः <= 31) {
			प्रत्यागम -1;
		}
		यदि (Reg_अङ्कः <= 31) {
			प्रत्यागम -1;
		}

	यदि (Phy_दत्त_Ptr == रिक्त) {
		प्रत्यागम -1;
	}

	/*
	 * Verify MDIO master status.
	 */
	यदि (XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.आधारः_स्थानाङ्कः,
				XEL_MDIOCNTR_विस्थापनम्) &
				XEL_MDIOCNTR_स्थितिः_आवरणम्) {
		प्रत्यागम DEVICE_BUSY;
	}

	PhyAddrReg = ((((Phy_स्थानाङ्कः << XEL_MDIO_स्थानाङ्कः_सरणम्) &
			XEL_MDIO_स्थानाङ्कः_आवरणम्) | Reg_अङ्कः) | XEL_MDIO_OP_आवरणम्);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.आधारः_स्थानाङ्कः,
				 XEL_MDIOADDR_विस्थापनम्, PhyAddrReg);

	/*
	 * Enable MDIO and start the transfer.
	 */
	MdioCtrlReg =
		XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.आधारः_स्थानाङ्कः,
					XEL_MDIOCNTR_विस्थापनम्);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.आधारः_स्थानाङ्कः,
				XEL_MDIOCNTR_विस्थापनम्,
				MdioCtrlReg |
				XEL_MDIOCNTR_स्थितिः_आवरणम् |
				XEL_MDIOCNTR_ENABLE_आवरणम्);

	/*
	 * Wait till the completion of transfer.
	 */
	यावत् ((XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.आधारः_स्थानाङ्कः,
				XEL_MDIOCNTR_विस्थापनम्) &
				XEL_MDIOCNTR_स्थितिः_आवरणम्));

	/*
	 * Read data from MDIO read data register.
	 */
	*Phy_दत्त_Ptr = (u16)XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.आधारः_स्थानाङ्कः,
					XEL_MDIORD_विस्थापनम्);

	/*
	 * Disable the MDIO.
	 */
	MdioCtrlReg =
		XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.आधारः_स्थानाङ्कः,
					XEL_MDIOCNTR_विस्थापनम्);

	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.आधारः_स्थानाङ्कः,
				XEL_MDIOCNTR_विस्थापनम्,
				MdioCtrlReg & ~XEL_MDIOCNTR_ENABLE_आवरणम्);


	प्रत्यागम SUCCESS;
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
पूर्णाङ्क XEmacLite_PhyWrite(XEmacLite *InstancePtr, u32 Phy_स्थानाङ्कः, u32 Reg_अङ्कः,
			u16 Phy_दत्त)
{
	u32 PhyAddrReg;
	u32 MdioCtrlReg;

	/*
	 * Verify that each of the inputs are valid.
	 */
	यदि (InstancePtr == रिक्त) {
		प्रत्यागम -1;
	}
	यदि (InstancePtr->EmacLiteConfig.MdioInclude == TRUE) {
		प्रत्यागम -1;
	}
	यदि (Phy_स्थानाङ्कः <= 31) {
		प्रत्यागम -1;
	}
	यदि (Reg_अङ्कः <= 31) {
		प्रत्यागम -1;
	}

	/*
	 * Verify MDIO master status.
	 */
	यदि (XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.आधारः_स्थानाङ्कः,
				XEL_MDIOCNTR_विस्थापनम्) &
				XEL_MDIOCNTR_स्थितिः_आवरणम्) {
		प्रत्यागम DEVICE_BUSY;
	}



	PhyAddrReg = ((((Phy_स्थानाङ्कः << XEL_MDIO_स्थानाङ्कः_सरणम्) &
			XEL_MDIO_स्थानाङ्कः_आवरणम्) | Reg_अङ्कः) & ~XEL_MDIO_OP_आवरणम्);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.आधारः_स्थानाङ्कः,
				XEL_MDIOADDR_विस्थापनम्, PhyAddrReg);

	/*
	 * Write data to MDIO write data register.
	 */
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.आधारः_स्थानाङ्कः,
				XEL_MDIOWR_विस्थापनम्, (u32)Phy_दत्त);

	/*
	 * Enable MDIO and start the transfer.
	 */
	MdioCtrlReg =
		XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.आधारः_स्थानाङ्कः,
					XEL_MDIOCNTR_विस्थापनम्);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.आधारः_स्थानाङ्कः,
				XEL_MDIOCNTR_विस्थापनम्,
				MdioCtrlReg | XEL_MDIOCNTR_स्थितिः_आवरणम् |
				XEL_MDIOCNTR_ENABLE_आवरणम्);

	/*
	 * Wait till the completion of transfer.
	 */
	यावत् ((XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.आधारः_स्थानाङ्कः,
				XEL_MDIOCNTR_विस्थापनम्) & XEL_MDIOCNTR_स्थितिः_आवरणम्));


	/*
	 * Disable the MDIO.
	 */
	MdioCtrlReg =
		XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.आधारः_स्थानाङ्कः,
					XEL_MDIOCNTR_विस्थापनम्);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.आधारः_स्थानाङ्कः,
				XEL_MDIOCNTR_विस्थापनम्,
				MdioCtrlReg & ~XEL_MDIOCNTR_ENABLE_आवरणम्);



	प्रत्यागम SUCCESS;
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
शून्य XEmac_Lite_Enable_Loop_पृष्ठभागः(XEmacLite *InstancePtr)
{
	u32 TsrReg;

	/*
	 * Verify that each of the inputs are valid.
	 */
	यदि (InstancePtr == रिक्त) {
		प्रत्यागम -1;
	}
	यदि (InstancePtr->EmacLiteConfig.Loopback == TRUE) {
		प्रत्यागम -1;
	}

	TsrReg = XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.आधारः_स्थानाङ्कः,
					XEL_TSR_विस्थापनम्);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.आधारः_स्थानाङ्कः,
			XEL_TSR_विस्थापनम्,	TsrReg | XEL_TSR_LOOPBACK_आवरणम्);
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
शून्य XEmac_Lite_Disable_Loop_पृष्ठभागः(XEmacLite *InstancePtr)
{
	u32 TsrReg;

	/*
	 * Verify that each of the inputs are valid.
	 */
		यदि (InstancePtr == रिक्त) {
			प्रत्यागम -1;
		}
		यदि (InstancePtr->EmacLiteConfig.Loopback == TRUE) {
			प्रत्यागम -1;
		}

	TsrReg = XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.आधारः_स्थानाङ्कः,
					XEL_TSR_विस्थापनम्);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.आधारः_स्थानाङ्कः,
			XEL_TSR_विस्थापनम्,	TsrReg & (~XEL_TSR_LOOPBACK_आवरणम्));
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
स्थिर u16 XEmac_Lite_Get_Receive_दत्त_दीर्घता(UINTPTR आधारः_स्थानाङ्कः)
{
	u16 दीर्घता;

#यदि_परिभाषितम् __LITTLE_ENDIAN__
	दीर्घता = (XEmacLite_ReadReg((आधारः_स्थानाङ्कः),
			XEL_शीर्षकम्_विस्थापनम् + XEL_RXBUFF_विस्थापनम्) &
			(XEL_RPLR_दीर्घता_आवरणम्_HI | XEL_RPLR_दीर्घता_आवरणम्_LO));
	दीर्घता = (u16) (((दीर्घता & 0xFF00) >> 8) | ((दीर्घता & 0x00FF) << 8));
#अन्यथा
	दीर्घता = ((XEmacLite_ReadReg((आधारः_स्थानाङ्कः),
			XEL_शीर्षकम्_विस्थापनम् + XEL_RXBUFF_विस्थापनम्) >>
			XEL_शीर्षकम्_सरणम्) &
			(XEL_RPLR_दीर्घता_आवरणम्_HI | XEL_RPLR_दीर्घता_आवरणम्_LO));
#यदि_अन्तः

	प्रत्यागम दीर्घता;
}

पूर्णाङ्क XEmacLite_EnableInterrupts(XEmacLite *InstancePtr)
{
	u32 पञ्जिकाकोशः;
	UINTPTR आधारः_स्थानाङ्कः;

	/*
	 * Verify that each of the inputs are valid.
	 */
	यदि(रिक्त == InstancePtr)
		प्रत्यागम -1;
	यदि(InstancePtr->IsReady != XIL_COMPONENT_IS_READY)
		प्रत्यागम -1;

	/*
	 * Verify that the handlers are in place.
	 */
	यदि ((InstancePtr->RecvHandler == (XEmacLite_Handler) StubHandler) ||
	    (InstancePtr->SendHandler == (XEmacLite_Handler) StubHandler)) {
		प्रत्यागम XST_NO_CALLBACK;
	}

	/*
	 * Enable the TX interrupts for both the buffers, the Interrupt Enable
	 * is common for the both the buffers and is defined in the
	 * Ping buffer.
	 */
	पञ्जिकाकोशः = XEmac_Lite_Get_Tx_स्थितिः(आधारः_स्थानाङ्कः);
	पञ्जिकाकोशः |= XEL_TSR_XMIT_IE_आवरणम्;
	XEmac_Lite_समुच्चयः_Tx_स्थितिः(आधारः_स्थानाङ्कः, पञ्जिकाकोशः);

	/*
	 * Enable the RX interrupts for both the buffers, the Interrupt Enable
	 * is common for the both the buffers and is defined in the
	 * Ping buffer.
	 */
	पञ्जिकाकोशः = XEmac_Lite_Get_Rx_स्थितिः(आधारः_स्थानाङ्कः);
	पञ्जिकाकोशः |= XEL_RSR_RECV_IE_आवरणम्;
	XEmac_Lite_समुच्चयः_Rx_स्थितिः(आधारः_स्थानाङ्कः, पञ्जिकाकोशः);

	/*
	 * Enable the global interrupt output.
	 */
	XEmacLite_WriteReg(आधारः_स्थानाङ्कः, XEL_GIER_विस्थापनम्, XEL_GIER_GIE_आवरणम्);

	प्रत्यागम SUCCESS;
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
शून्य XEmacLite_DisableInterrupts(XEmacLite *InstancePtr)
{
	u32 पञ्जिकाकोशः;
	UINTPTR आधारः_स्थानाङ्कः;

	/*
	 * Verify that each of the inputs are valid.
	 */
		यदि(रिक्त == InstancePtr)
			प्रत्यागम -1;
		यदि(InstancePtr->IsReady != XIL_COMPONENT_IS_READY)
			प्रत्यागम -1;


	आधारः_स्थानाङ्कः = InstancePtr->EmacLiteConfig.आधारः_स्थानाङ्कः;

	/*
	 * Disable the global interrupt output.
	 */
	XEmacLite_WriteReg(आधारः_स्थानाङ्कः, XEL_GIER_विस्थापनम्, 0);

	/*
	 * Disable the TX interrupts for both the buffers, the Interrupt Enable
	 * is common for the both the buffers and is defined in the
	 * Ping buffer.
	 */
	पञ्जिकाकोशः = XEmac_Lite_Get_Tx_स्थितिः(आधारः_स्थानाङ्कः);
	पञ्जिकाकोशः &= ~XEL_TSR_XMIT_IE_आवरणम्;
	XEmac_Lite_समुच्चयः_Tx_स्थितिः(आधारः_स्थानाङ्कः, पञ्जिकाकोशः);

	/*
	 * Disable the RX interrupts for both the buffers, the Interrupt Enable
	 * is common for the both the buffers and is defined in the
	 * Ping buffer.
	 */
	पञ्जिकाकोशः = XEmac_Lite_Get_Rx_स्थितिः(आधारः_स्थानाङ्कः);
	पञ्जिकाकोशः &= ~XEL_RSR_RECV_IE_आवरणम्;
	XEmac_Lite_समुच्चयः_Rx_स्थितिः(आधारः_स्थानाङ्कः, पञ्जिकाकोशः);

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
शून्य XEmac_Lite_व्यवधानम्_Handler(शून्य *InstancePtr)
{

	XEmacLite *EmacLitePtr;
	पूर्णाङ्क TxCompleteIntr = FALSE;
	UINTPTR आधारः_स्थानाङ्कः;
	u32 Tx_स्थितिः;

	/*
	 * Verify that each of the inputs are valid.
	 */
		यदि(रिक्त == InstancePtr)
			प्रत्यागम -1;

	/*
	 * Convert the non-typed pointer to an EmacLite instance pointer
	 * such that there is access to the device.
	 */
	EmacLitePtr = (XEmacLite *) InstancePtr;
	आधारः_स्थानाङ्कः = EmacLitePtr->EmacLiteConfig.आधारः_स्थानाङ्कः;

	यदि ((XEmac_Lite_Is_Rx_रिक्तानि(आधारः_स्थानाङ्कः) != TRUE) ||
		(XEmac_Lite_Is_Rx_रिक्तानि(आधारः_स्थानाङ्कः +
			XEL_बफर_विस्थापनम्) != TRUE)) {
		/*
		 * Call the RX callback.
		 */
		EmacLitePtr->RecvHandler(EmacLitePtr->RecvRef);

	}

	Tx_स्थितिः = XEmac_Lite_Get_Tx_स्थितिः(आधारः_स्थानाङ्कः);
	यदि (((Tx_स्थितिः & XEL_TSR_XMIT_BUSY_आवरणम्) == 0) &&
		(Tx_स्थितिः & XEL_TSR_XMIT_सक्रिय_आवरणम्) != 0) {

		/*
		 * Clear the Tx Active bit in the Tx Status Register.
		 */
		Tx_स्थितिः &= ~XEL_TSR_XMIT_सक्रिय_आवरणम्;
		XEmac_Lite_समुच्चयः_Tx_स्थितिः(आधारः_स्थानाङ्कः, Tx_स्थितिः);

		/*
		 * Update the flag indicating that there was a Tx Interrupt.
		 */
		TxCompleteIntr = TRUE;

	}

	Tx_स्थितिः = XEmac_Lite_Get_Tx_स्थितिः(आधारः_स्थानाङ्कः + XEL_बफर_विस्थापनम्);
	यदि (((Tx_स्थितिः & XEL_TSR_XMIT_BUSY_आवरणम्) == 0) &&
		(Tx_स्थितिः & XEL_TSR_XMIT_सक्रिय_आवरणम्) != 0) {

		/*
		 * Clear the Tx Active bit in the Tx Status Register.
		 */
		Tx_स्थितिः &= ~XEL_TSR_XMIT_सक्रिय_आवरणम्;
		XEmac_Lite_समुच्चयः_Tx_स्थितिः(आधारः_स्थानाङ्कः + XEL_बफर_विस्थापनम्,
					Tx_स्थितिः);
		/*
		 * Update the flag indicating that there was a Tx Interrupt.
		 */
		TxCompleteIntr = TRUE;
	}

	/*
	 * If there was a TX interrupt, call the callback.
	 */
	यदि (TxCompleteIntr == TRUE) {

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
शून्य XEmac_Lite_समुच्चयः_Recv_Handler(XEmacLite *InstancePtr, शून्य *Call_पृष्ठभागः_Ref,
			      XEmacLite_Handler FuncPtr)
{
	यदि(रिक्त == InstancePtr)
		प्रत्यागम -1;
	यदि(रिक्त == FuncPtr)
		प्रत्यागम -1;
	यदि(InstancePtr->IsReady != XIL_COMPONENT_IS_READY)
		प्रत्यागम -1;

	InstancePtr->RecvHandler = FuncPtr;
	InstancePtr->RecvRef = Call_पृष्ठभागः_Ref;
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
शून्य XEmac_Lite_समुच्चयः_Send_Handler(XEmacLite *InstancePtr, शून्य *Call_पृष्ठभागः_Ref,
			      XEmacLite_Handler FuncPtr)
{
	यदि(रिक्त == InstancePtr)
		प्रत्यागम -1;
	यदि(रिक्त == FuncPtr)
		प्रत्यागम -1;
	यदि(InstancePtr->IsReady != XIL_COMPONENT_IS_READY)
		प्रत्यागम -1;

	InstancePtr->SendHandler = FuncPtr;
	InstancePtr->SendRef = Call_पृष्ठभागः_Ref;
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
	u16 Phy_दत्त;
	पूर्णाङ्क PhyAddr;

	/*
	 * Verify all 32 MDIO ports.
	 */
	प्रति (PhyAddr = 31; PhyAddr >= 0; PhyAddr--) {
		XEmacLite_PhyRead(InstancePtr, PhyAddr, PHY_REG1_विस्थापनम्,
				 &Phy_दत्त);

		यदि (Phy_दत्त != 0xFFFF) {
			यदि ((Phy_दत्त & PHY_REG1_DETECT_आवरणम्) ==
			PHY_REG1_DETECT_आवरणम्) {
				प्रत्यागम PhyAddr;	/* Found a valid PHY device */
			}
		}
	}
	प्रारूप_लिख("\n Could not detect phy device");
	/*
	 * Unable to detect PHY device returning the default address of 0.
	 */
	प्रत्यागम 0;
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
पूर्णाङ्क Emac_Lite_Enable_Phy_Loop_पृष्ठभागः(XEmacLite *InstancePtr, u32 Phy_स्थानाङ्कः)
{
	पूर्णाङ्क स्थितिः;
	u16 Phy_दत्त = 0;

	/*
	 * Set the speed and put the PHY in reset.
	 */
	Phy_दत्त |= PHY_REG0_SPD_100_आवरणम्;
	स्थितिः = XEmacLite_PhyWrite(InstancePtr, Phy_स्थानाङ्कः, PHY_REG0_विस्थापनम्,
			Phy_दत्त | PHY_REG0_RESET_आवरणम्);
	यदि (स्थितिः != XST_SUCCESS) {
		प्रत्यागम XST_FAILURE;
	}

	/*
	 * Give sufficient delay for Phy Reset.
	 */
	EmacLitePhyDelay(EMACLITE_PHY_DELAY_SEC);

	/*
	 * Set the PHY in loop back.
	 */
	XEmacLite_PhyWrite(InstancePtr, Phy_स्थानाङ्कः, PHY_REG0_विस्थापनम्,
			Phy_दत्त | PHY_REG0_LOOPBACK_आवरणम्);
	यदि (स्थितिः != XST_SUCCESS) {
		प्रत्यागम XST_FAILURE;
	}

	/*
	 * Give sufficient delay for Phy Loopback Enable.
	 */
	EmacLitePhyDelay(1);

	प्रत्यागम XST_SUCCESS;
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
पूर्णाङ्क Emac_Lite_Disable_Phy_Loop_पृष्ठभागः(XEmacLite *InstancePtr, u32 Phy_स्थानाङ्कः)
{
	पूर्णाङ्क स्थितिः;
	u16 Phy_दत्त;

	/*
	 * Disable loop back through PHY register using MDIO support.
	 */
	स्थितिः = XEmacLite_PhyRead(InstancePtr, Phy_स्थानाङ्कः, PHY_REG0_विस्थापनम्,
					&Phy_दत्त);
	यदि (स्थितिः != XST_SUCCESS) {
		प्रत्यागम XST_FAILURE;
	}

	स्थितिः = XEmacLite_PhyWrite(InstancePtr,Phy_स्थानाङ्कः, PHY_REG0_विस्थापनम्,
					Phy_दत्त & ~(PHY_REG0_LOOPBACK_आवरणम्));
	यदि (स्थितिः != XST_SUCCESS) {
		प्रत्यागम XST_FAILURE;
	}

	प्रत्यागम XST_SUCCESS;

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
शून्य EmacLitePhyDelay(अचिह्नित पूर्णाङ्क Seconds)
{
#यदि_परिभाषितम् __MICROBLAZE__
	स्थिर पूर्णाङ्क WarningFlag = 0;

	/* If MB caches are disabled or do not exist, this delay loop could
	 * take minutes instead of seconds (e.g., 30x longer).  Print a warning
	 * message for the user (once).  If only MB had a built-in timer!
	 */
	यदि (((mfmsr() & 0x20) == 0) && (!WarningFlag)) {
#यदि_परिभाषितम् STDOUT_BASEADDRESS
		xil_printf("Warning: This example will take ");
		xil_printf("minutes to complete without I-cache enabled \r\n");
#यदि_अन्तः
		WarningFlag = 1;
	}

#परिभाषय ITERS_प्रत्येकम्_SEC   (XPAR_CPU_CORE_CLOCK_FREQ_HZ / 6)
    asm चञ्चल ("\n"
                  "1:               \n\t"
                  "addik r7, r0, %0 \n\t"
                  "2:               \n\t"
                  "addik r7, r7, -1 \n\t"
                  "bneid  r7, 2b    \n\t"
                  "or  r0, r0, r0   \n\t"
                  "bneid %1, 1b     \n\t"
                  "addik %1, %1, -1 \n\t"
                  :: "i"(ITERS_प्रत्येकम्_SEC), "d" (Seconds));

#अन्यथा

//	usleep(Seconds * 1000000);
//	waitfor(Seconds * 1000);
#यदि_अन्तः
}


