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
#నిర్వచించు ETH_VARI 1

#అన్తర్భావ "eth_driver.h"
#అన్తర్భావ "plic_driver.h"
#అన్తర్భావ "platform.h"
#అన్తర్భావ "log.h"
#అన్తర్భావ "stddef.h"
#అన్తర్భావ "gpio.h"
#అన్తర్భావ "utils.h"

/*
 * Variable used to indicate the length of the received frame.
 */
అస్థిర u32 Recv_చట్రం_నిడివి;
UINTPTR TxBuffPtr;
UINTPTR RxBuffPtr;
అస్థిర పూర్ణాంకం చట్రాలు_Tx;
అస్థిర పూర్ణాంకం చట్రాలు_Rx;
అస్థిర పూర్ణాంకం Tx_లెక్క;
అస్థిర పూర్ణాంకం Rx_లెక్క;
అస్థిర పూర్ణాంకం Padding;	/* For 1588 Packets we need to pad 8 bytes time stamp value */

/*
 * Set up valid local MAC addresses. This loop back test uses the LocalAddress
 * both as a source and destination MAC address.
 */

XEmacLite EmacLiteInstance;	/* Instance of the EmacLite */

/*
 * Buffers used for Transmission and Reception of Packets. These are declared
 * as global so that they are not a part of the stack.
 */
u8 Tx_చట్రం[XEL_MAX_చట్రం_కొలత];
u8 Rx_చట్రం[XEL_MAX_చట్రం_కొలత];

అస్థిర u32 Recv_చట్రం_నిడివి;	/* Indicates the length of the Received packet
				 */
అస్థిర పూర్ణాంకం TransmitComplete;	/* Flag to indicate that the Transmission
				 * is complete
				 */


శూన్య StubHandler(శూన్య *Call_వెనుక_Ref);


/**
 * This table contains configuration information for each EmacLite device
 * in the system.
 */
XEmacLite_Config XEmac_Lite_Config_పట్టిక = {
	{
	 XPAR_EMACLITE_0_DEVICE_ID,	/* Unique ID of device */
	 XPAR_EMACLITE_0_BASEADDR,	/* Device base address */
	 XPAR_EMACLITE_0_TX_PING_PONG,	/* Include TX Ping Pong buffers */
	 XPAR_EMACLITE_0_RX_PING_PONG,	/* Include RX Ping Pong buffers */
	 XPAR_EMACLITE_0_INCLUDE_MDIO,	/* Include MDIO support */
	 XPAR_EMACLITE_0_INCLUDE_అంతర్గత_LOOPBACK
/* Include Internal  loop back support */
	 }
};



/************************** Function Prototypes ******************************/

స్థిర u16 XEmac_Lite_Get_Receive_దత్తాంశం_నిడివి(UINTPTR పునాది_చిరునామా);

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
స్థిర INLINE u8 Xil_In8(UINTPTR Addr)
{
	తిరిగి *(అస్థిర u8 *) Addr;
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
స్థిర INLINE u16 Xil_In16(UINTPTR Addr)
{
	తిరిగి *(అస్థిర u16 *) Addr;
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
స్థిర INLINE u32 Xil_In32(UINTPTR Addr)
{
	తిరిగి *(అస్థిర u32 *) Addr;
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
స్థిర INLINE u64 Xil_In64(UINTPTR Addr)
{
	తిరిగి *(అస్థిర u64 *) Addr;
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
స్థిర INLINE శూన్య Xil_Out8(UINTPTR Addr, u8 విలువ_2)
{
	అస్థిర u8 *LocalAddr = (అస్థిర u8 *)Addr;
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
స్థిర INLINE శూన్య Xil_Out16(UINTPTR Addr, u16 విలువ_2)
{
	అస్థిర u16 *LocalAddr = (అస్థిర u16 *)Addr;
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
స్థిర INLINE శూన్య Xil_Out32(UINTPTR Addr, u32 విలువ_2)
{
	అస్థిర u32 *LocalAddr = (అస్థిర u32 *)Addr;
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
స్థిర INLINE శూన్య Xil_Out64(UINTPTR Addr, u64 విలువ_2)
{
	అస్థిర u64 *LocalAddr = (అస్థిర u64 *)Addr;
	*LocalAddr = విలువ_2;
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
u16 Xil_EndianSwap16(u16 దత్తాంశం)
{
	తిరిగి (u16) (((దత్తాంశం & 0xFF00U) >> 8U) | ((దత్తాంశం & 0x00FFU) << 8U));
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
u32 Xil_EndianSwap32(u32 దత్తాంశం)
{
	u16 Lo_మాట;
	u16 Hi_మాట;

	/* get each of the half words from the 32 bit word */

	Lo_మాట = (u16) (దత్తాంశం & 0x0000FFFFU);
	Hi_మాట = (u16) ((దత్తాంశం & 0xFFFF0000U) >> 16U);

	/* byte swap each of the 16 bit half words */

	Lo_మాట = (((Lo_మాట & 0xFF00U) >> 8U) | ((Lo_మాట & 0x00FFU) << 8U));
	Hi_మాట = (((Hi_మాట & 0xFF00U) >> 8U) | ((Hi_మాట & 0x00FFU) << 8U));

	/* swap the half words before returning the value */

	తిరిగి ((((u32)Lo_మాట) << (u32)16U) | (u32)Hi_మాట);
}


/************************** Variable Definitions *****************************/



u16 Xil_Htons(u16 దత్తాంశం)
{
	తిరిగి (u16) (((దత్తాంశం & 0xFF00U) >> 8U) | ((దత్తాంశం & 0x00FFU) << 8U));
}

u16 Xil_Ntohs(u16 దత్తాంశం)
{
	తిరిగి (u16) (((దత్తాంశం & 0xFF00U) >> 8U) | ((దత్తాంశం & 0x00FFU) << 8U));
}


#ఒకవేళ 0
#నిర్వచించు Xil_In16LE	Xil_In16
#నిర్వచించు Xil_In32LE	Xil_In32
#నిర్వచించు Xil_Out16LE	Xil_Out16
#నిర్వచించు Xil_Out32LE	Xil_Out32
#నిర్వచించు Xil_Htons	Xil_EndianSwap16
#నిర్వచించు Xil_Htonl	Xil_EndianSwap32
#నిర్వచించు Xil_Ntohs	Xil_EndianSwap16
#నిర్వచించు Xil_Ntohl	Xil_EndianSwap32
#అయితే_ముగింపు


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
#నిర్వచించు XEmacLite_ReadReg(పునాది_చిరునామా, Reg_స్థానభ్రంశం) \
	XEmacLite_In32((పునాది_చిరునామా) + (Reg_స్థానభ్రంశం))

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
#నిర్వచించు XEmacLite_WriteReg(పునాది_చిరునామా, Reg_స్థానభ్రంశం, రిజిస్టరు_విలువ) \
	XEmacLite_Out32((పునాది_చిరునామా) + (Reg_స్థానభ్రంశం), (రిజిస్టరు_విలువ))


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
#నిర్వచించు XEmac_Lite_Get_Tx_స్థితి(పునాది_చిరునామా)			\
	(XEmacLite_ReadReg((పునాది_చిరునామా), XEL_TSR_స్థానభ్రంశం))


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
#నిర్వచించు XEmac_Lite_సమితి_Tx_స్థితి(పునాది_చిరునామా, దత్తాంశం)			\
	(XEmacLite_WriteReg((పునాది_చిరునామా), XEL_TSR_స్థానభ్రంశం, (దత్తాంశం)))


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
#నిర్వచించు XEmac_Lite_Get_Rx_స్థితి(పునాది_చిరునామా)			\
	(XEmacLite_ReadReg((పునాది_చిరునామా), XEL_RSR_స్థానభ్రంశం))


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
#నిర్వచించు XEmac_Lite_సమితి_Rx_స్థితి(పునాది_చిరునామా, దత్తాంశం)			\
	(XEmacLite_WriteReg((పునాది_చిరునామా), XEL_RSR_స్థానభ్రంశం, (దత్తాంశం)))


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
#నిర్వచించు XEmac_Lite_Is_Tx_పూర్తి(పునాది_చిరునామా)			\
		 ((XEmacLite_ReadReg((పునాది_చిరునామా), XEL_TSR_స్థానభ్రంశం) & 	 \
			 XEL_TSR_XMIT_BUSY_ముసుగు) != XEL_TSR_XMIT_BUSY_ముసుగు)


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
#నిర్వచించు XEmac_Lite_Is_Rx_ఖాళీలు(పునాది_చిరునామా) \
		  ((XEmacLite_ReadReg((పునాది_చిరునామా), XEL_RSR_స్థానభ్రంశం) & \
			XEL_RSR_RECV_పూర్తి_ముసుగు) != XEL_RSR_RECV_పూర్తి_ముసుగు)

/************************** Function Prototypes ******************************/

శూన్య XEmac_Lite_Send_చట్రం(UINTPTR పునాది_చిరునామా, u8 *చట్రం_Ptr, గుర్తులేని Byte_లెక్క);
u16 XEmac_Lite_Recv_చట్రం(UINTPTR పునాది_చిరునామా, u8 *చట్రం_Ptr);

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
శూన్య XEmac_Lite_Send_చట్రం(UINTPTR పునాది_చిరునామా, u8 *చట్రం_Ptr, గుర్తులేని Byte_లెక్క)
{
	u32 రిజిస్టరు;

	/*
	 * Write data to the EmacLite
	 */
	XEmacLite_AlignedWrite(చట్రం_Ptr, (UINTPTR *) (పునాది_చిరునామా), Byte_లెక్క);

	/*
	 * The frame is in the buffer, now send it
	 */
	XEmacLite_WriteReg(పునాది_చిరునామా,  XEL_TPLR_స్థానభ్రంశం,
				(Byte_లెక్క & (XEL_TPLR_నిడివి_ముసుగు_HI |
				XEL_TPLR_నిడివి_ముసుగు_LO)));


	రిజిస్టరు = XEmac_Lite_Get_Tx_స్థితి(పునాది_చిరునామా);
	XEmac_Lite_సమితి_Tx_స్థితి(పునాది_చిరునామా, రిజిస్టరు | XEL_TSR_XMIT_BUSY_ముసుగు);

	/*
	 * Loop on the status waiting for the transmit to be complete.
	 */
	అయితే (!XEmac_Lite_Is_Tx_పూర్తి(పునాది_చిరునామా));

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
u16 XEmac_Lite_Recv_చట్రం(UINTPTR పునాది_చిరునామా, u8 *చట్రం_Ptr)
{
	u16 నిడివి_Type;
	u16 నిడివి;
	u32 రిజిస్టరు;

	/*
	 * Wait for a frame to arrive - this is a blocking call
	 */
	అయితే (XEmac_Lite_Is_Rx_ఖాళీలు(పునాది_చిరునామా));

	/*
	 * Get the length of the frame that arrived, only 32-bit reads are
	 * allowed LengthType is in the upper half of the 32-bit word.
	 */
	రిజిస్టరు = XEmacLite_ReadReg(పునాది_చిరునామా, XEL_RPLR_స్థానభ్రంశం);
	నిడివి_Type = (u16) ((రిజిస్టరు >> 16) &
			    (XEL_RPLR_నిడివి_ముసుగు_HI |
			     XEL_RPLR_నిడివి_ముసుగు_LO));

	/*
	 * Check if length is valid
	 */
	ఒకవేళ (నిడివి_Type > XEL_MAX_చట్రం_కొలత) {
		/*
		 * Field contain type, use max frame size and
		 * let user parse it
		 */
		నిడివి = XEL_MAX_చట్రం_కొలత;
	}
	లేకపోతే {
		/*
		 * Use the length in the frame, plus the header and trailer
		 */
		నిడివి = నిడివి_Type + XEL_శీర్షిక_కొలత + XEL_FCS_కొలత;
	}

	/*
	 * Read each byte from the EmacLite
	 */
	XEmacLite_AlignedRead((UINTPTR *) (పునాది_చిరునామా + XEL_RXBUFF_స్థానభ్రంశం),
			      చట్రం_Ptr, నిడివి);

	/*
	 * Acknowledge the frame
	 */
	రిజిస్టరు = XEmac_Lite_Get_Rx_స్థితి(పునాది_చిరునామా);
	రిజిస్టరు &= ~XEL_RSR_RECV_పూర్తి_ముసుగు;
	XEmac_Lite_సమితి_Rx_స్థితి(పునాది_చిరునామా, రిజిస్టరు);

	తిరిగి నిడివి_Type;
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
శూన్య XEmacLite_AlignedWrite(శూన్య *SrcPtr, UINTPTR *DestPtr, గుర్తులేని Byte_లెక్క)
{
	గుర్తులేని సూచీ;
	గుర్తులేని నిడివి = Byte_లెక్క;
	అస్థిర u32 Align_బఫరు;
	అస్థిర u32 *To32Ptr;
	u32 *From32Ptr;
	అస్థిర u16 *To16Ptr;
	u16 *From16Ptr;
	అస్థిర u8 *To8Ptr;
	u8 *From8Ptr;

//	To32Ptr = (volatile UINTPTR *)DestPtr;

	ఒకవేళ ((((u32) SrcPtr) & 0x00000003) == 0) {

		/*
		 * Word aligned buffer, no correction needed.
		 */
		From32Ptr = (u32 *) SrcPtr;
		To32Ptr = (u32 *)DestPtr;
#ఒకవేళ 0
		log_info("length is %x", నిడివి);
		log_info("\n Size of To32Ptr: %x", పరిమాణం(*To32Ptr));
		log_info("\n Size of From32Ptr: %x", పరిమాణం(*From32Ptr));
#అయితే_ముగింపు		
		అయితే (నిడివి > 3) {
			/*
			 * Output each word destination.
			 */
			*To32Ptr++ = *From32Ptr++;
#ఒకవేళ 0
			*To32Ptr = *From32Ptr++;
			రాయి("\n Write value @ %x: %x", To32Ptr, *To32Ptr);
			*To32Ptr++;

//#else
			*To32Ptr = *From32Ptr;
			log_info("\n 1:[%x]; 2: [%x]", *To32Ptr, *From32Ptr);
			log_info("\n 1:[%x]; 2: [%x]", To32Ptr, From32Ptr);
			*To32Ptr++;
			*From32Ptr++;
			log_info("\n 1_2:[%x]; 2: [%x]", *To32Ptr, *From32Ptr);
			log_info("\n 1_2:[%x]; 2: [%x]", To32Ptr, From32Ptr);
#అయితే_ముగింపు
			/*
			 * Adjust length accordingly
			 */
			నిడివి -= 4;
		}

		/*
		 * Set up to output the remaining data, zero the temp buffer
		 first.
		 */
		Align_బఫరు = 0;
		To8Ptr = (u8 *) &Align_బఫరు;
		From8Ptr = (u8 *) From32Ptr;

	}
	లేకపోతే ఒకవేళ ((((u32) SrcPtr) & 0x00000001) != 0) {
		/*
		 * Byte aligned buffer, correct.
		 */
		Align_బఫరు = 0;
		To8Ptr = (u8 *) &Align_బఫరు;
		From8Ptr = (u8 *) SrcPtr;

		అయితే (నిడివి > 3) {
			/*
			 * Copy each byte into the temporary buffer.
			 */
			కొరకు (సూచీ = 0; సూచీ < 4; సూచీ++) {
				*To8Ptr++ = *From8Ptr++;
			}

			/*
			 * Output the buffer
			 */
			*To32Ptr++ = Align_బఫరు;

			/*.
			 * Reset the temporary buffer pointer and adjust length.
			 */
			To8Ptr = (u8 *) &Align_బఫరు;
			నిడివి -= 4;
		}

		/*
		 * Set up to output the remaining data, zero the temp buffer
		 * first.
		 */
		Align_బఫరు = 0;
		To8Ptr = (u8 *) &Align_బఫరు;

	}
	లేకపోతే {
		/*
		 * Half-Word aligned buffer, correct.
		 */
		Align_బఫరు = 0;

		/*
		 * This is a funny looking cast. The new gcc, version 3.3.x has
		 * a strict cast check for 16 bit pointers, aka short pointers.
		 * The following warning is issued if the initial 'void *' cast
		 * is  not used:
		 * 'dereferencing type-punned pointer will break strict-aliasing
		 * rules'
		 */

		To16Ptr = (u16 *) ((శూన్య *) &Align_బఫరు);
		From16Ptr = (u16 *) SrcPtr;

		అయితే (నిడివి > 3) {
			/*
			 * Copy each half word into the temporary buffer.
			 */
			కొరకు (సూచీ = 0; సూచీ < 2; సూచీ++) {
				*To16Ptr++ = *From16Ptr++;
			}

			/*
			 * Output the buffer.
			 */
			*To32Ptr++ = Align_బఫరు;

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
			To16Ptr = (u16 *) ((శూన్య *) &Align_బఫరు);
			నిడివి -= 4;
		}

		/*
		 * Set up to output the remaining data, zero the temp buffer
		 * first.
		 */
		Align_బఫరు = 0;
		To8Ptr = (u8 *) &Align_బఫరు;
		From8Ptr = (u8 *) From16Ptr;
	}

	/*
	 * Output the remaining data, zero the temp buffer first.
	 */
	కొరకు (సూచీ = 0; సూచీ < నిడివి; సూచీ++) {
		*To8Ptr++ = *From8Ptr++;
	}
	ఒకవేళ (నిడివి) {
		*To32Ptr++ = Align_బఫరు;
	}
	To32Ptr = (అస్థిర UINTPTR *)DestPtr;
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
శూన్య XEmacLite_AlignedRead(UINTPTR *SrcPtr, శూన్య *DestPtr, గుర్తులేని Byte_లెక్క)
{
	గుర్తులేని సూచీ;
	గుర్తులేని నిడివి = Byte_లెక్క;
	అస్థిర u32 Align_బఫరు;
	u32 *To32Ptr;
	అస్థిర u32 *From32Ptr;
	u16 *To16Ptr;
	అస్థిర u16 *From16Ptr;
	u8 *To8Ptr;
	అస్థిర u8 *From8Ptr;

	From32Ptr = (u32 *) SrcPtr;

	ఒకవేళ ((((u32) DestPtr) & 0x00000003) == 0) {

		/*
		 * Word aligned buffer, no correction needed.
		 */
		To32Ptr = (u32 *) DestPtr;
//		log_info("\n Read: 1:[%x]; 2: [%x]", *To32Ptr, *From32Ptr);
//		log_info("\n 1:[%x]; 2: [%x]", To32Ptr, From32Ptr);

		అయితే (నిడివి > 3) {
			/*
			 * Output each word.
			 */
			*To32Ptr++ = *From32Ptr++;

			/*
			 * Adjust length accordingly.
			 */
			నిడివి -= 4;
		}

		/*
		 * Set up to read the remaining data.
		 */
		To8Ptr = (u8 *) To32Ptr;

	}
	లేకపోతే ఒకవేళ ((((u32) DestPtr) & 0x00000001) != 0) {
		/*
		 * Byte aligned buffer, correct.
		 */
		To8Ptr = (u8 *) DestPtr;

		అయితే (నిడివి > 3) {
			/*
			 * Copy each word into the temporary buffer.
			 */
			Align_బఫరు = *From32Ptr++;
			From8Ptr = (u8 *) &Align_బఫరు;

			/*
			 * Write data to destination.
			 */
			కొరకు (సూచీ = 0; సూచీ < 4; సూచీ++) {
				*To8Ptr++ = *From8Ptr++;
			}

			/*
			 * Adjust length
			 */
			నిడివి -= 4;
		}

	}
	లేకపోతే {
		/*
		 * Half-Word aligned buffer, correct.
		 */
		To16Ptr = (u16 *) DestPtr;

		అయితే (నిడివి > 3) {
			/*
			 * Copy each word into the temporary buffer.
			 */
			Align_బఫరు = *From32Ptr++;

			/*
			 * This is a funny looking cast. The new gcc, version
			 * 3.3.x has a strict cast check for 16 bit pointers,
			 * aka short pointers. The following warning is issued
			 * if the initial 'void *' cast is not used:
			 * 'dereferencing type-punned pointer will break
			 *  strict-aliasing rules'
			 */
			From16Ptr = (u16 *) ((శూన్య *) &Align_బఫరు);

			/*
			 * Write data to destination.
			 */
			కొరకు (సూచీ = 0; సూచీ < 2; సూచీ++) {
				*To16Ptr++ = *From16Ptr++;
			}

			/*
			 * Adjust length.
			 */
			నిడివి -= 4;
		}

		/*
		 * Set up to read the remaining data.
		 */
		To8Ptr = (u8 *) To16Ptr;
	}

	/*
	 * Read the remaining data.
	 */
	Align_బఫరు = *From32Ptr++;
	From8Ptr = (u8 *) &Align_బఫరు;

	కొరకు (సూచీ = 0; సూచీ < నిడివి; సూచీ++) {
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
పూర్ణాంకం XEmacLite_CfgInitialize(XEmacLite *InstancePtr,
				XEmacLite_Config *EmacLiteConfigPtr,
				UINTPTR EffectiveAddr)
{

	/*
	 * Verify that each of the inputs are valid.
	 */
//	Xil_AssertNonvoid(InstancePtr != NULL);
	ఒకవేళ(ఖాళీ == InstancePtr)
	{
		log_error("\nEthernet Parameter - InstancePtr is Null");
		తిరిగి -1;
	}
//	Xil_AssertNonvoid(EmacLiteConfigPtr != NULL);
	ఒకవేళ(ఖాళీ == EmacLiteConfigPtr)
	{
		log_error("Ethernet Parameter - EmacLiteConfigPtr is Null");
		తిరిగి -1;
	}

	/*
	 * Zero the provided instance memory.
	 */
	memset(InstancePtr, 0, పరిమాణం(XEmacLite));

	/*
	 * Set some default values for instance data, don't indicate the device
	 * is ready to use until everything has been initialized successfully.
	 */
	InstancePtr->EmacLiteConfig.పునాది_చిరునామా = EffectiveAddr;
	InstancePtr->EmacLiteConfig.DeviceId = EmacLiteConfigPtr->DeviceId;
	InstancePtr->EmacLiteConfig.TxPingPong = EmacLiteConfigPtr->TxPingPong;
	InstancePtr->EmacLiteConfig.RxPingPong = EmacLiteConfigPtr->RxPingPong;
	InstancePtr->EmacLiteConfig.MdioInclude = EmacLiteConfigPtr->MdioInclude;
	InstancePtr->EmacLiteConfig.Loopback = EmacLiteConfigPtr->Loopback;

	InstancePtr->తదుపరి_Tx_బఫరు_గమ్యం_Use = 0x0;
	InstancePtr->తదుపరి_Rx_బఫరు_గమ్యం_Use = 0x0;
	InstancePtr->RecvHandler = (XEmacLite_Handler) StubHandler;
	InstancePtr->SendHandler = (XEmacLite_Handler) StubHandler;
	/*
	 * Clear the TX CSR's in case this is a restart.
	 */
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.పునాది_చిరునామా,
				XEL_TSR_స్థానభ్రంశం, 0);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.పునాది_చిరునామా,
				XEL_బఫరు_స్థానభ్రంశం + XEL_TSR_స్థానభ్రంశం, 0);

	/*
	 * Since there were no failures, indicate the device is ready to use.
	 */
	InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

	తిరిగి SUCCESS;
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
పూర్ణాంకం XEmacLite_Send(XEmacLite *InstancePtr, u8 *చట్రం_Ptr, గుర్తులేని Byte_లెక్క)
{
	u32 రిజిస్టరు;
	UINTPTR పునాది_చిరునామా;
	UINTPTR Emac_పునాది_చిరునామా;
	u32 Intr_Enable_స్థితి;

	/*
	 * Verify that each of the inputs are valid.
	 */
//	Xil_AssertNonvoid(InstancePtr != NULL);
	ఒకవేళ (InstancePtr == ఖాళీ) {
		తిరిగి -1;
	}

	/*
	 * Determine the expected TX buffer address.
	 */
	పునాది_చిరునామా = XEmac_Lite_తదుపరి_Transmit_Addr(InstancePtr);
	Emac_పునాది_చిరునామా = InstancePtr->EmacLiteConfig.పునాది_చిరునామా;

	/*
	 * Check the Length if it is too large, truncate it.
	 * The maximum Tx packet size is
	 * Ethernet header (14 Bytes) + Maximum MTU (1500 bytes).
	 */
	ఒకవేళ (Byte_లెక్క > XEL_MAX_TX_చట్రం_కొలత) {

		Byte_లెక్క = XEL_MAX_TX_చట్రం_కొలత;
	}

	/*
	 * Determine if the expected buffer address is empty.
	 */
	రిజిస్టరు = XEmac_Lite_Get_Tx_స్థితి(పునాది_చిరునామా);

	/*
	 * If the expected buffer is available, fill it with the provided data
	 * Align if necessary.
	 */
	ఒకవేళ ((రిజిస్టరు & (XEL_TSR_XMIT_BUSY_ముసుగు |
			XEL_TSR_XMIT_చురుకైన_ముసుగు)) == 0) {

		/*
		 * Switch to next buffer if configured.
		 */
		ఒకవేళ (InstancePtr->EmacLiteConfig.TxPingPong != 0) {
			InstancePtr->తదుపరి_Tx_బఫరు_గమ్యం_Use ^= XEL_బఫరు_స్థానభ్రంశం;
		}

		/*
		 * Write the frame to the buffer.
		 */
		XEmacLite_AlignedWrite(చట్రం_Ptr, (UINTPTR *) పునాది_చిరునామా,
				       Byte_లెక్క);


		/*
		 * The frame is in the buffer, now send it.
		 */
		XEmacLite_WriteReg(పునాది_చిరునామా, XEL_TPLR_స్థానభ్రంశం,
					(Byte_లెక్క & (XEL_TPLR_నిడివి_ముసుగు_HI |
					XEL_TPLR_నిడివి_ముసుగు_LO)));

		/*
		 * Update the Tx Status Register to indicate that there is a
		 * frame to send.
		 * If the interrupt enable bit of Ping buffer(since this
		 * controls both the buffers) is enabled then set the
		 * XEL_TSR_XMIT_ACTIVE_MASK flag which is used by the interrupt
		 * handler to call the callback function provided by the user
		 * to indicate that the frame has been transmitted.
		 */
		రిజిస్టరు = XEmac_Lite_Get_Tx_స్థితి(పునాది_చిరునామా);
		రిజిస్టరు |= XEL_TSR_XMIT_BUSY_ముసుగు;
		Intr_Enable_స్థితి = XEmac_Lite_Get_Tx_స్థితి(Emac_పునాది_చిరునామా);
		ఒకవేళ ((Intr_Enable_స్థితి & XEL_TSR_XMIT_IE_ముసుగు) != 0) {
			రిజిస్టరు |= XEL_TSR_XMIT_చురుకైన_ముసుగు;
		}
		XEmac_Lite_సమితి_Tx_స్థితి(పునాది_చిరునామా, రిజిస్టరు);

		తిరిగి SUCCESS;
	}

	/*
	 * If the expected buffer was full, try the other buffer if configured.
	 */
	ఒకవేళ (InstancePtr->EmacLiteConfig.TxPingPong != 0) {

		పునాది_చిరునామా ^= XEL_బఫరు_స్థానభ్రంశం;

		/*
		 * Determine if the expected buffer address is empty.
		 */
		రిజిస్టరు = XEmac_Lite_Get_Tx_స్థితి(పునాది_చిరునామా);

		/*
		 * If the next buffer is available, fill it with the provided
		 * data.
		 */
		ఒకవేళ ((రిజిస్టరు & (XEL_TSR_XMIT_BUSY_ముసుగు |
				XEL_TSR_XMIT_చురుకైన_ముసుగు)) == 0) {

			/*
			 * Write the frame to the buffer.
			 */
			XEmacLite_AlignedWrite(చట్రం_Ptr, (UINTPTR *) పునాది_చిరునామా,
					       Byte_లెక్క);

			/*
			 * The frame is in the buffer, now send it.
			 */
			XEmacLite_WriteReg(పునాది_చిరునామా, XEL_TPLR_స్థానభ్రంశం,
					(Byte_లెక్క & (XEL_TPLR_నిడివి_ముసుగు_HI |
					   XEL_TPLR_నిడివి_ముసుగు_LO)));

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
			రిజిస్టరు = XEmac_Lite_Get_Tx_స్థితి(పునాది_చిరునామా);
			రిజిస్టరు |= XEL_TSR_XMIT_BUSY_ముసుగు;
			Intr_Enable_స్థితి =
					XEmac_Lite_Get_Tx_స్థితి(Emac_పునాది_చిరునామా);
			ఒకవేళ ((Intr_Enable_స్థితి & XEL_TSR_XMIT_IE_ముసుగు) != 0) {
				రిజిస్టరు |= XEL_TSR_XMIT_చురుకైన_ముసుగు;
			}
			XEmac_Lite_సమితి_Tx_స్థితి(పునాది_చిరునామా, రిజిస్టరు);

			/*
			 * Do not switch to next buffer, there is a sync problem
			 * and the expected buffer should not change.
			 */
			తిరిగి SUCCESS;
		}
	}

	రాయి("\n Error in sending the packet");
	/*
	 * Buffer(s) was(were) full, return failure to allow for polling usage.
	 */
	తిరిగి FAILURE;
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
u16 XEmacLite_Recv(XEmacLite *InstancePtr, u8 *చట్రం_Ptr)
{
	u16 నిడివి_Type;
	u16 నిడివి;
	u32 రిజిస్టరు;
	UINTPTR పునాది_చిరునామా;

	/*
	 * Verify that each of the inputs are valid.
	 */

	ఒకవేళ (InstancePtr == ఖాళీ) {
		తిరిగి -1;
	}

	/*
	 * Determine the expected buffer address.
	 */
	పునాది_చిరునామా = XEmac_Lite_తదుపరి_Receive_Addr(InstancePtr);

	/*
	 * Verify which buffer has valid data.
	 */
	రిజిస్టరు = XEmac_Lite_Get_Rx_స్థితి(పునాది_చిరునామా);

	ఒకవేళ ((రిజిస్టరు & XEL_RSR_RECV_పూర్తి_ముసుగు) == XEL_RSR_RECV_పూర్తి_ముసుగు) {

		/*
		 * The driver is in sync, update the next expected buffer if
		 * configured.
		 */

		ఒకవేళ (InstancePtr->EmacLiteConfig.RxPingPong != 0) {
			InstancePtr->తదుపరి_Rx_బఫరు_గమ్యం_Use ^= XEL_బఫరు_స్థానభ్రంశం;
		}
	}
	లేకపోతే {
		/*
		 * The instance is out of sync, try other buffer if other
		 * buffer is configured, return 0 otherwise. If the instance is
		 * out of sync, do not update the 'NextRxBufferToUse' since it
		 * will correct on subsequent calls.
		 */
		ఒకవేళ (InstancePtr->EmacLiteConfig.RxPingPong != 0) {
			పునాది_చిరునామా ^= XEL_బఫరు_స్థానభ్రంశం;
		}
		లేకపోతే {
			తిరిగి 0;	/* No data was available */
		}

		/*
		 * Verify that buffer has valid data.
		 */
		రిజిస్టరు = XEmac_Lite_Get_Rx_స్థితి(పునాది_చిరునామా);
		ఒకవేళ ((రిజిస్టరు & XEL_RSR_RECV_పూర్తి_ముసుగు) !=
				XEL_RSR_RECV_పూర్తి_ముసుగు) {
			తిరిగి 0;	/* No data was available */
		}
	}

	/*
	 * Get the length of the frame that arrived.
	 */
	నిడివి_Type = XEmac_Lite_Get_Receive_దత్తాంశం_నిడివి(పునాది_చిరునామా);

	/*
	 * Check if length is valid.
	 */
	ఒకవేళ (నిడివి_Type > XEL_MAX_చట్రం_కొలత) {


		ఒకవేళ (నిడివి_Type == XEL_ETHER_PROTO_TYPE_IP) {

			/*
			 * The packet is a an IP Packet.
			 */
#నిర్వచితమైతే __LITTLE_ENDIAN__
			నిడివి = (XEmacLite_ReadReg((పునాది_చిరునామా),
					XEL_శీర్షిక_IP_నిడివి_స్థానభ్రంశం +
					XEL_RXBUFF_స్థానభ్రంశం) &
					(XEL_RPLR_నిడివి_ముసుగు_HI |
					XEL_RPLR_నిడివి_ముసుగు_LO));
			నిడివి = (u16) (((నిడివి & 0xFF00) >> 8) | ((నిడివి & 0x00FF) << 8));
#లేకపోతే
			నిడివి = ((XEmacLite_ReadReg((పునాది_చిరునామా),
					XEL_శీర్షిక_IP_నిడివి_స్థానభ్రంశం +
					XEL_RXBUFF_స్థానభ్రంశం) >>
					XEL_శీర్షిక_జరుపు) &
					(XEL_RPLR_నిడివి_ముసుగు_HI |
					XEL_RPLR_నిడివి_ముసుగు_LO));
#అయితే_ముగింపు

//			Length += XEL_HEADER_SIZE + XEL_FCS_SIZE;
			నిడివి += XEL_శీర్షిక_కొలత;
//			printf("\n Length1 is %x", Length);

		} లేకపోతే ఒకవేళ (నిడివి_Type == XEL_ETHER_PROTO_TYPE_ARP) {

			/*
			 * The packet is an ARP Packet.
			 */
			నిడివి = XEL_ARP_PACKET_కొలత + XEL_శీర్షిక_కొలత +
					XEL_FCS_కొలత;

		} లేకపోతే {
			/*
			 * Field contains type other than IP or ARP, use max
			 * frame size and let user parse it.
			 */
			నిడివి = XEL_MAX_చట్రం_కొలత;

		}
	} లేకపోతే {

		/*
		 * Use the length in the frame, plus the header and trailer.
		 */
		నిడివి = నిడివి_Type + XEL_శీర్షిక_కొలత + XEL_FCS_కొలత;
	}

	/*
	 * Read from the EmacLite.
	 */
	XEmacLite_AlignedRead(((UINTPTR *) (పునాది_చిరునామా + XEL_RXBUFF_స్థానభ్రంశం)),
			      చట్రం_Ptr, నిడివి);

	/*
	 * Acknowledge the frame.
	 */
	రిజిస్టరు = XEmac_Lite_Get_Rx_స్థితి(పునాది_చిరునామా);
	రిజిస్టరు &= ~XEL_RSR_RECV_పూర్తి_ముసుగు;
	XEmac_Lite_సమితి_Rx_స్థితి(పునాది_చిరునామా, రిజిస్టరు);

	తిరిగి నిడివి;
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
శూన్య XEmac_Lite_సమితి_Mac_చిరునామా(XEmacLite *InstancePtr, u8 *చిరునామా_Ptr)
{
	UINTPTR పునాది_చిరునామా;

	/*
	 * Verify that each of the inputs are valid.
	 */
	ఒకవేళ (InstancePtr == ఖాళీ) {
		తిరిగి -1;
	}

	/*
	 * Determine the expected TX buffer address.
	 */
	పునాది_చిరునామా = XEmac_Lite_తదుపరి_Transmit_Addr(InstancePtr);

	/*
	 * Copy the MAC address to the Transmit buffer.
	 */
	XEmacLite_AlignedWrite(చిరునామా_Ptr,
				(UINTPTR *) పునాది_చిరునామా,
				XEL_MAC_ADDR_కొలత);

	/*
	 * Set the length.
	 */
	XEmacLite_WriteReg(పునాది_చిరునామా,
				XEL_TPLR_స్థానభ్రంశం,
				XEL_MAC_ADDR_కొలత);

	/*
	 * Update the MAC address in the EmacLite.
	 */
	XEmac_Lite_సమితి_Tx_స్థితి(పునాది_చిరునామా, XEL_TSR_PROG_MAC_ADDR);


	/*
	 * Wait for EmacLite to finish with the MAC address update.
	 */
	అయితే ((XEmac_Lite_Get_Tx_స్థితి(పునాది_చిరునామా) &
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
శూన్య StubHandler(శూన్య *Call_వెనుక_Ref)
{
	(శూన్య)(Call_వెనుక_Ref);
	తిరిగి 1;
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
పూర్ణాంకం XEmac_Lite_Tx_బఫరు_అందుబాటు(XEmacLite *InstancePtr)
{

	u32 రిజిస్టరు;
	పూర్ణాంకం TxPingBusy;
	పూర్ణాంకం TxPongBusy;

	/*
	 * Verify that each of the inputs are valid.
	 */
	ఒకవేళ (InstancePtr == ఖాళీ) {
		తిరిగి -1;
	}

	/*
	 * Read the Tx Status and determine if the buffer is available.
	 */
	రిజిస్టరు = XEmac_Lite_Get_Tx_స్థితి(InstancePtr->EmacLiteConfig.
						పునాది_చిరునామా);

	TxPingBusy = (రిజిస్టరు & (XEL_TSR_XMIT_BUSY_ముసుగు |
				 XEL_TSR_XMIT_చురుకైన_ముసుగు));


	/*
	 * Read the Tx Status of the second buffer register and determine if the
	 * buffer is available.
	 */
	ఒకవేళ (InstancePtr->EmacLiteConfig.TxPingPong != 0) {
		రిజిస్టరు = XEmac_Lite_Get_Tx_స్థితి(InstancePtr->EmacLiteConfig.
						పునాది_చిరునామా +
						XEL_బఫరు_స్థానభ్రంశం);

		TxPongBusy = (రిజిస్టరు & (XEL_TSR_XMIT_BUSY_ముసుగు |
					XEL_TSR_XMIT_చురుకైన_ముసుగు));

		తిరిగి (!(TxPingBusy && TxPongBusy));
	}

	తిరిగి (!TxPingBusy);


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
శూన్య XEmacLite_FlushReceive(XEmacLite *InstancePtr)
{

	u32 రిజిస్టరు;

	/*
	 * Verify that each of the inputs are valid.
	 */
		ఒకవేళ (InstancePtr == ఖాళీ) {
			తిరిగి -1;
		}

	/*
	 * Read the current buffer register and determine if the buffer is
	 * available.
	 */
	రిజిస్టరు = XEmac_Lite_Get_Rx_స్థితి(InstancePtr->EmacLiteConfig.
						పునాది_చిరునామా);

	/*
	 * Preserve the IE bit.
	 */
	రిజిస్టరు &= XEL_RSR_RECV_IE_ముసుగు;

	/*
	 * Write out the value to flush the RX buffer.
	 */
	XEmac_Lite_సమితి_Rx_స్థితి(InstancePtr->EmacLiteConfig.పునాది_చిరునామా,
				రిజిస్టరు);

	/*
	 * If the pong buffer is available, flush it also.
	 */
	ఒకవేళ (InstancePtr->EmacLiteConfig.RxPingPong != 0) {
		/*
		 * Read the current buffer register and determine if the buffer
		 * is available.
		 */
		రిజిస్టరు = XEmac_Lite_Get_Rx_స్థితి(InstancePtr->EmacLiteConfig.
							పునాది_చిరునామా +
							XEL_బఫరు_స్థానభ్రంశం);

		/*
		 * Preserve the IE bit.
		 */
		రిజిస్టరు &= XEL_RSR_RECV_IE_ముసుగు;

		/*
		 * Write out the value to flush the RX buffer.
		 */
		XEmac_Lite_సమితి_Rx_స్థితి(InstancePtr->EmacLiteConfig.పునాది_చిరునామా +
					XEL_బఫరు_స్థానభ్రంశం, రిజిస్టరు);

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
పూర్ణాంకం XEmacLite_PhyRead(XEmacLite *InstancePtr, u32 Phy_చిరునామా, u32 Reg_అంకె,
			u16 *Phy_దత్తాంశం_Ptr)
{
	u32 PhyAddrReg;
	u32 MdioCtrlReg;

	/*
	 * Verify that each of the inputs are valid.
	 */
		ఒకవేళ (InstancePtr == ఖాళీ) {
			తిరిగి -1;
		}
		ఒకవేళ (InstancePtr->EmacLiteConfig.MdioInclude == TRUE) {
			తిరిగి -1;
		}
		ఒకవేళ (Phy_చిరునామా <= 31) {
			తిరిగి -1;
		}
		ఒకవేళ (Reg_అంకె <= 31) {
			తిరిగి -1;
		}

	ఒకవేళ (Phy_దత్తాంశం_Ptr == ఖాళీ) {
		తిరిగి -1;
	}

	/*
	 * Verify MDIO master status.
	 */
	ఒకవేళ (XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.పునాది_చిరునామా,
				XEL_MDIOCNTR_స్థానభ్రంశం) &
				XEL_MDIOCNTR_స్థితి_ముసుగు) {
		తిరిగి DEVICE_BUSY;
	}

	PhyAddrReg = ((((Phy_చిరునామా << XEL_MDIO_చిరునామా_జరుపు) &
			XEL_MDIO_చిరునామా_ముసుగు) | Reg_అంకె) | XEL_MDIO_OP_ముసుగు);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.పునాది_చిరునామా,
				 XEL_MDIOADDR_స్థానభ్రంశం, PhyAddrReg);

	/*
	 * Enable MDIO and start the transfer.
	 */
	MdioCtrlReg =
		XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.పునాది_చిరునామా,
					XEL_MDIOCNTR_స్థానభ్రంశం);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.పునాది_చిరునామా,
				XEL_MDIOCNTR_స్థానభ్రంశం,
				MdioCtrlReg |
				XEL_MDIOCNTR_స్థితి_ముసుగు |
				XEL_MDIOCNTR_ENABLE_ముసుగు);

	/*
	 * Wait till the completion of transfer.
	 */
	అయితే ((XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.పునాది_చిరునామా,
				XEL_MDIOCNTR_స్థానభ్రంశం) &
				XEL_MDIOCNTR_స్థితి_ముసుగు));

	/*
	 * Read data from MDIO read data register.
	 */
	*Phy_దత్తాంశం_Ptr = (u16)XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.పునాది_చిరునామా,
					XEL_MDIORD_స్థానభ్రంశం);

	/*
	 * Disable the MDIO.
	 */
	MdioCtrlReg =
		XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.పునాది_చిరునామా,
					XEL_MDIOCNTR_స్థానభ్రంశం);

	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.పునాది_చిరునామా,
				XEL_MDIOCNTR_స్థానభ్రంశం,
				MdioCtrlReg & ~XEL_MDIOCNTR_ENABLE_ముసుగు);


	తిరిగి SUCCESS;
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
పూర్ణాంకం XEmacLite_PhyWrite(XEmacLite *InstancePtr, u32 Phy_చిరునామా, u32 Reg_అంకె,
			u16 Phy_దత్తాంశం)
{
	u32 PhyAddrReg;
	u32 MdioCtrlReg;

	/*
	 * Verify that each of the inputs are valid.
	 */
	ఒకవేళ (InstancePtr == ఖాళీ) {
		తిరిగి -1;
	}
	ఒకవేళ (InstancePtr->EmacLiteConfig.MdioInclude == TRUE) {
		తిరిగి -1;
	}
	ఒకవేళ (Phy_చిరునామా <= 31) {
		తిరిగి -1;
	}
	ఒకవేళ (Reg_అంకె <= 31) {
		తిరిగి -1;
	}

	/*
	 * Verify MDIO master status.
	 */
	ఒకవేళ (XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.పునాది_చిరునామా,
				XEL_MDIOCNTR_స్థానభ్రంశం) &
				XEL_MDIOCNTR_స్థితి_ముసుగు) {
		తిరిగి DEVICE_BUSY;
	}



	PhyAddrReg = ((((Phy_చిరునామా << XEL_MDIO_చిరునామా_జరుపు) &
			XEL_MDIO_చిరునామా_ముసుగు) | Reg_అంకె) & ~XEL_MDIO_OP_ముసుగు);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.పునాది_చిరునామా,
				XEL_MDIOADDR_స్థానభ్రంశం, PhyAddrReg);

	/*
	 * Write data to MDIO write data register.
	 */
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.పునాది_చిరునామా,
				XEL_MDIOWR_స్థానభ్రంశం, (u32)Phy_దత్తాంశం);

	/*
	 * Enable MDIO and start the transfer.
	 */
	MdioCtrlReg =
		XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.పునాది_చిరునామా,
					XEL_MDIOCNTR_స్థానభ్రంశం);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.పునాది_చిరునామా,
				XEL_MDIOCNTR_స్థానభ్రంశం,
				MdioCtrlReg | XEL_MDIOCNTR_స్థితి_ముసుగు |
				XEL_MDIOCNTR_ENABLE_ముసుగు);

	/*
	 * Wait till the completion of transfer.
	 */
	అయితే ((XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.పునాది_చిరునామా,
				XEL_MDIOCNTR_స్థానభ్రంశం) & XEL_MDIOCNTR_స్థితి_ముసుగు));


	/*
	 * Disable the MDIO.
	 */
	MdioCtrlReg =
		XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.పునాది_చిరునామా,
					XEL_MDIOCNTR_స్థానభ్రంశం);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.పునాది_చిరునామా,
				XEL_MDIOCNTR_స్థానభ్రంశం,
				MdioCtrlReg & ~XEL_MDIOCNTR_ENABLE_ముసుగు);



	తిరిగి SUCCESS;
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
శూన్య XEmac_Lite_Enable_Loop_వెనుక(XEmacLite *InstancePtr)
{
	u32 TsrReg;

	/*
	 * Verify that each of the inputs are valid.
	 */
	ఒకవేళ (InstancePtr == ఖాళీ) {
		తిరిగి -1;
	}
	ఒకవేళ (InstancePtr->EmacLiteConfig.Loopback == TRUE) {
		తిరిగి -1;
	}

	TsrReg = XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.పునాది_చిరునామా,
					XEL_TSR_స్థానభ్రంశం);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.పునాది_చిరునామా,
			XEL_TSR_స్థానభ్రంశం,	TsrReg | XEL_TSR_LOOPBACK_ముసుగు);
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
శూన్య XEmac_Lite_Disable_Loop_వెనుక(XEmacLite *InstancePtr)
{
	u32 TsrReg;

	/*
	 * Verify that each of the inputs are valid.
	 */
		ఒకవేళ (InstancePtr == ఖాళీ) {
			తిరిగి -1;
		}
		ఒకవేళ (InstancePtr->EmacLiteConfig.Loopback == TRUE) {
			తిరిగి -1;
		}

	TsrReg = XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.పునాది_చిరునామా,
					XEL_TSR_స్థానభ్రంశం);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.పునాది_చిరునామా,
			XEL_TSR_స్థానభ్రంశం,	TsrReg & (~XEL_TSR_LOOPBACK_ముసుగు));
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
స్థిర u16 XEmac_Lite_Get_Receive_దత్తాంశం_నిడివి(UINTPTR పునాది_చిరునామా)
{
	u16 నిడివి;

#నిర్వచితమైతే __LITTLE_ENDIAN__
	నిడివి = (XEmacLite_ReadReg((పునాది_చిరునామా),
			XEL_శీర్షిక_స్థానభ్రంశం + XEL_RXBUFF_స్థానభ్రంశం) &
			(XEL_RPLR_నిడివి_ముసుగు_HI | XEL_RPLR_నిడివి_ముసుగు_LO));
	నిడివి = (u16) (((నిడివి & 0xFF00) >> 8) | ((నిడివి & 0x00FF) << 8));
#లేకపోతే
	నిడివి = ((XEmacLite_ReadReg((పునాది_చిరునామా),
			XEL_శీర్షిక_స్థానభ్రంశం + XEL_RXBUFF_స్థానభ్రంశం) >>
			XEL_శీర్షిక_జరుపు) &
			(XEL_RPLR_నిడివి_ముసుగు_HI | XEL_RPLR_నిడివి_ముసుగు_LO));
#అయితే_ముగింపు

	తిరిగి నిడివి;
}

పూర్ణాంకం XEmacLite_EnableInterrupts(XEmacLite *InstancePtr)
{
	u32 రిజిస్టరు;
	UINTPTR పునాది_చిరునామా;

	/*
	 * Verify that each of the inputs are valid.
	 */
	ఒకవేళ(ఖాళీ == InstancePtr)
		తిరిగి -1;
	ఒకవేళ(InstancePtr->IsReady != XIL_COMPONENT_IS_READY)
		తిరిగి -1;

	/*
	 * Verify that the handlers are in place.
	 */
	ఒకవేళ ((InstancePtr->RecvHandler == (XEmacLite_Handler) StubHandler) ||
	    (InstancePtr->SendHandler == (XEmacLite_Handler) StubHandler)) {
		తిరిగి XST_NO_CALLBACK;
	}

	/*
	 * Enable the TX interrupts for both the buffers, the Interrupt Enable
	 * is common for the both the buffers and is defined in the
	 * Ping buffer.
	 */
	రిజిస్టరు = XEmac_Lite_Get_Tx_స్థితి(పునాది_చిరునామా);
	రిజిస్టరు |= XEL_TSR_XMIT_IE_ముసుగు;
	XEmac_Lite_సమితి_Tx_స్థితి(పునాది_చిరునామా, రిజిస్టరు);

	/*
	 * Enable the RX interrupts for both the buffers, the Interrupt Enable
	 * is common for the both the buffers and is defined in the
	 * Ping buffer.
	 */
	రిజిస్టరు = XEmac_Lite_Get_Rx_స్థితి(పునాది_చిరునామా);
	రిజిస్టరు |= XEL_RSR_RECV_IE_ముసుగు;
	XEmac_Lite_సమితి_Rx_స్థితి(పునాది_చిరునామా, రిజిస్టరు);

	/*
	 * Enable the global interrupt output.
	 */
	XEmacLite_WriteReg(పునాది_చిరునామా, XEL_GIER_స్థానభ్రంశం, XEL_GIER_GIE_ముసుగు);

	తిరిగి SUCCESS;
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
శూన్య XEmacLite_DisableInterrupts(XEmacLite *InstancePtr)
{
	u32 రిజిస్టరు;
	UINTPTR పునాది_చిరునామా;

	/*
	 * Verify that each of the inputs are valid.
	 */
		ఒకవేళ(ఖాళీ == InstancePtr)
			తిరిగి -1;
		ఒకవేళ(InstancePtr->IsReady != XIL_COMPONENT_IS_READY)
			తిరిగి -1;


	పునాది_చిరునామా = InstancePtr->EmacLiteConfig.పునాది_చిరునామా;

	/*
	 * Disable the global interrupt output.
	 */
	XEmacLite_WriteReg(పునాది_చిరునామా, XEL_GIER_స్థానభ్రంశం, 0);

	/*
	 * Disable the TX interrupts for both the buffers, the Interrupt Enable
	 * is common for the both the buffers and is defined in the
	 * Ping buffer.
	 */
	రిజిస్టరు = XEmac_Lite_Get_Tx_స్థితి(పునాది_చిరునామా);
	రిజిస్టరు &= ~XEL_TSR_XMIT_IE_ముసుగు;
	XEmac_Lite_సమితి_Tx_స్థితి(పునాది_చిరునామా, రిజిస్టరు);

	/*
	 * Disable the RX interrupts for both the buffers, the Interrupt Enable
	 * is common for the both the buffers and is defined in the
	 * Ping buffer.
	 */
	రిజిస్టరు = XEmac_Lite_Get_Rx_స్థితి(పునాది_చిరునామా);
	రిజిస్టరు &= ~XEL_RSR_RECV_IE_ముసుగు;
	XEmac_Lite_సమితి_Rx_స్థితి(పునాది_చిరునామా, రిజిస్టరు);

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
శూన్య XEmac_Lite_అంతరాయం_Handler(శూన్య *InstancePtr)
{

	XEmacLite *EmacLitePtr;
	పూర్ణాంకం TxCompleteIntr = FALSE;
	UINTPTR పునాది_చిరునామా;
	u32 Tx_స్థితి;

	/*
	 * Verify that each of the inputs are valid.
	 */
		ఒకవేళ(ఖాళీ == InstancePtr)
			తిరిగి -1;

	/*
	 * Convert the non-typed pointer to an EmacLite instance pointer
	 * such that there is access to the device.
	 */
	EmacLitePtr = (XEmacLite *) InstancePtr;
	పునాది_చిరునామా = EmacLitePtr->EmacLiteConfig.పునాది_చిరునామా;

	ఒకవేళ ((XEmac_Lite_Is_Rx_ఖాళీలు(పునాది_చిరునామా) != TRUE) ||
		(XEmac_Lite_Is_Rx_ఖాళీలు(పునాది_చిరునామా +
			XEL_బఫరు_స్థానభ్రంశం) != TRUE)) {
		/*
		 * Call the RX callback.
		 */
		EmacLitePtr->RecvHandler(EmacLitePtr->RecvRef);

	}

	Tx_స్థితి = XEmac_Lite_Get_Tx_స్థితి(పునాది_చిరునామా);
	ఒకవేళ (((Tx_స్థితి & XEL_TSR_XMIT_BUSY_ముసుగు) == 0) &&
		(Tx_స్థితి & XEL_TSR_XMIT_చురుకైన_ముసుగు) != 0) {

		/*
		 * Clear the Tx Active bit in the Tx Status Register.
		 */
		Tx_స్థితి &= ~XEL_TSR_XMIT_చురుకైన_ముసుగు;
		XEmac_Lite_సమితి_Tx_స్థితి(పునాది_చిరునామా, Tx_స్థితి);

		/*
		 * Update the flag indicating that there was a Tx Interrupt.
		 */
		TxCompleteIntr = TRUE;

	}

	Tx_స్థితి = XEmac_Lite_Get_Tx_స్థితి(పునాది_చిరునామా + XEL_బఫరు_స్థానభ్రంశం);
	ఒకవేళ (((Tx_స్థితి & XEL_TSR_XMIT_BUSY_ముసుగు) == 0) &&
		(Tx_స్థితి & XEL_TSR_XMIT_చురుకైన_ముసుగు) != 0) {

		/*
		 * Clear the Tx Active bit in the Tx Status Register.
		 */
		Tx_స్థితి &= ~XEL_TSR_XMIT_చురుకైన_ముసుగు;
		XEmac_Lite_సమితి_Tx_స్థితి(పునాది_చిరునామా + XEL_బఫరు_స్థానభ్రంశం,
					Tx_స్థితి);
		/*
		 * Update the flag indicating that there was a Tx Interrupt.
		 */
		TxCompleteIntr = TRUE;
	}

	/*
	 * If there was a TX interrupt, call the callback.
	 */
	ఒకవేళ (TxCompleteIntr == TRUE) {

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
శూన్య XEmac_Lite_సమితి_Recv_Handler(XEmacLite *InstancePtr, శూన్య *Call_వెనుక_Ref,
			      XEmacLite_Handler FuncPtr)
{
	ఒకవేళ(ఖాళీ == InstancePtr)
		తిరిగి -1;
	ఒకవేళ(ఖాళీ == FuncPtr)
		తిరిగి -1;
	ఒకవేళ(InstancePtr->IsReady != XIL_COMPONENT_IS_READY)
		తిరిగి -1;

	InstancePtr->RecvHandler = FuncPtr;
	InstancePtr->RecvRef = Call_వెనుక_Ref;
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
శూన్య XEmac_Lite_సమితి_Send_Handler(XEmacLite *InstancePtr, శూన్య *Call_వెనుక_Ref,
			      XEmacLite_Handler FuncPtr)
{
	ఒకవేళ(ఖాళీ == InstancePtr)
		తిరిగి -1;
	ఒకవేళ(ఖాళీ == FuncPtr)
		తిరిగి -1;
	ఒకవేళ(InstancePtr->IsReady != XIL_COMPONENT_IS_READY)
		తిరిగి -1;

	InstancePtr->SendHandler = FuncPtr;
	InstancePtr->SendRef = Call_వెనుక_Ref;
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
	u16 Phy_దత్తాంశం;
	పూర్ణాంకం PhyAddr;

	/*
	 * Verify all 32 MDIO ports.
	 */
	కొరకు (PhyAddr = 31; PhyAddr >= 0; PhyAddr--) {
		XEmacLite_PhyRead(InstancePtr, PhyAddr, PHY_REG1_స్థానభ్రంశం,
				 &Phy_దత్తాంశం);

		ఒకవేళ (Phy_దత్తాంశం != 0xFFFF) {
			ఒకవేళ ((Phy_దత్తాంశం & PHY_REG1_DETECT_ముసుగు) ==
			PHY_REG1_DETECT_ముసుగు) {
				తిరిగి PhyAddr;	/* Found a valid PHY device */
			}
		}
	}
	రాయి("\n Could not detect phy device");
	/*
	 * Unable to detect PHY device returning the default address of 0.
	 */
	తిరిగి 0;
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
పూర్ణాంకం Emac_Lite_Enable_Phy_Loop_వెనుక(XEmacLite *InstancePtr, u32 Phy_చిరునామా)
{
	పూర్ణాంకం స్థితి_2;
	u16 Phy_దత్తాంశం = 0;

	/*
	 * Set the speed and put the PHY in reset.
	 */
	Phy_దత్తాంశం |= PHY_REG0_SPD_100_ముసుగు;
	స్థితి_2 = XEmacLite_PhyWrite(InstancePtr, Phy_చిరునామా, PHY_REG0_స్థానభ్రంశం,
			Phy_దత్తాంశం | PHY_REG0_RESET_ముసుగు);
	ఒకవేళ (స్థితి_2 != XST_SUCCESS) {
		తిరిగి XST_FAILURE;
	}

	/*
	 * Give sufficient delay for Phy Reset.
	 */
	EmacLitePhyDelay(EMACLITE_PHY_DELAY_SEC);

	/*
	 * Set the PHY in loop back.
	 */
	XEmacLite_PhyWrite(InstancePtr, Phy_చిరునామా, PHY_REG0_స్థానభ్రంశం,
			Phy_దత్తాంశం | PHY_REG0_LOOPBACK_ముసుగు);
	ఒకవేళ (స్థితి_2 != XST_SUCCESS) {
		తిరిగి XST_FAILURE;
	}

	/*
	 * Give sufficient delay for Phy Loopback Enable.
	 */
	EmacLitePhyDelay(1);

	తిరిగి XST_SUCCESS;
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
పూర్ణాంకం Emac_Lite_Disable_Phy_Loop_వెనుక(XEmacLite *InstancePtr, u32 Phy_చిరునామా)
{
	పూర్ణాంకం స్థితి_2;
	u16 Phy_దత్తాంశం;

	/*
	 * Disable loop back through PHY register using MDIO support.
	 */
	స్థితి_2 = XEmacLite_PhyRead(InstancePtr, Phy_చిరునామా, PHY_REG0_స్థానభ్రంశం,
					&Phy_దత్తాంశం);
	ఒకవేళ (స్థితి_2 != XST_SUCCESS) {
		తిరిగి XST_FAILURE;
	}

	స్థితి_2 = XEmacLite_PhyWrite(InstancePtr,Phy_చిరునామా, PHY_REG0_స్థానభ్రంశం,
					Phy_దత్తాంశం & ~(PHY_REG0_LOOPBACK_ముసుగు));
	ఒకవేళ (స్థితి_2 != XST_SUCCESS) {
		తిరిగి XST_FAILURE;
	}

	తిరిగి XST_SUCCESS;

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
శూన్య EmacLitePhyDelay(గుర్తులేని పూర్ణాంకం Seconds)
{
#నిర్వచితమైతే __MICROBLAZE__
	స్థిర పూర్ణాంకం WarningFlag = 0;

	/* If MB caches are disabled or do not exist, this delay loop could
	 * take minutes instead of seconds (e.g., 30x longer).  Print a warning
	 * message for the user (once).  If only MB had a built-in timer!
	 */
	ఒకవేళ (((mfmsr() & 0x20) == 0) && (!WarningFlag)) {
#నిర్వచితమైతే STDOUT_BASEADDRESS
		xil_printf("Warning: This example will take ");
		xil_printf("minutes to complete without I-cache enabled \r\n");
#అయితే_ముగింపు
		WarningFlag = 1;
	}

#నిర్వచించు ITERS_చొప్పున_SEC   (XPAR_CPU_CORE_CLOCK_FREQ_HZ / 6)
    asm అస్థిర ("\n"
                  "1:               \n\t"
                  "addik r7, r0, %0 \n\t"
                  "2:               \n\t"
                  "addik r7, r7, -1 \n\t"
                  "bneid  r7, 2b    \n\t"
                  "or  r0, r0, r0   \n\t"
                  "bneid %1, 1b     \n\t"
                  "addik %1, %1, -1 \n\t"
                  :: "i"(ITERS_చొప్పున_SEC), "d" (Seconds));

#లేకపోతే

//	usleep(Seconds * 1000000);
//	waitfor(Seconds * 1000);
#అయితే_ముగింపు
}


