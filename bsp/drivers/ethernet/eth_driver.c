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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ETH_VARI 1

#ਅਨ੍ਤਰ੍ਭਾਵ "eth_driver.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "plic_driver.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "platform.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "stddef.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gpio.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "utils.h"

/*
 * Variable used to indicate the length of the received frame.
 */
ਅਸਥਿਰ u32 Recv_ਚੌਖਟਾ_ਲੰਮਾਈ;
UINTPTR TxBuffPtr;
UINTPTR RxBuffPtr;
ਅਸਥਿਰ ਪੂਰਨ ਚੌਖਟੇ_Tx;
ਅਸਥਿਰ ਪੂਰਨ ਚੌਖਟੇ_Rx;
ਅਸਥਿਰ ਪੂਰਨ Tx_ਗਿਣਤੀ;
ਅਸਥਿਰ ਪੂਰਨ Rx_ਗਿਣਤੀ;
ਅਸਥਿਰ ਪੂਰਨ Padding;	/* For 1588 Packets we need to pad 8 bytes time stamp value */

/*
 * Set up valid local MAC addresses. This loop back test uses the LocalAddress
 * both as a source and destination MAC address.
 */

XEmacLite EmacLiteInstance;	/* Instance of the EmacLite */

/*
 * Buffers used for Transmission and Reception of Packets. These are declared
 * as global so that they are not a part of the stack.
 */
u8 Tx_ਚੌਖਟਾ[XEL_MAX_ਚੌਖਟਾ_ਮਾਪ];
u8 Rx_ਚੌਖਟਾ[XEL_MAX_ਚੌਖਟਾ_ਮਾਪ];

ਅਸਥਿਰ u32 Recv_ਚੌਖਟਾ_ਲੰਮਾਈ;	/* Indicates the length of the Received packet
				 */
ਅਸਥਿਰ ਪੂਰਨ TransmitComplete;	/* Flag to indicate that the Transmission
				 * is complete
				 */


ਖਾਲੀ StubHandler(ਖਾਲੀ *Call_ਪਿੱਠ_Ref);


/**
 * This table contains configuration information for each EmacLite device
 * in the system.
 */
XEmacLite_Config XEmac_Lite_Config_ਸਾਰਣੀ = {
	{
	 XPAR_EMACLITE_0_DEVICE_ID,	/* Unique ID of device */
	 XPAR_EMACLITE_0_BASEADDR,	/* Device base address */
	 XPAR_EMACLITE_0_TX_PING_PONG,	/* Include TX Ping Pong buffers */
	 XPAR_EMACLITE_0_RX_PING_PONG,	/* Include RX Ping Pong buffers */
	 XPAR_EMACLITE_0_INCLUDE_MDIO,	/* Include MDIO support */
	 XPAR_EMACLITE_0_INCLUDE_ਅੰਦਰੂਨੀ_LOOPBACK
/* Include Internal  loop back support */
	 }
};



/************************** Function Prototypes ******************************/

ਸਥਿਰ u16 XEmac_Lite_Get_Receive_ਅੰਕੜੇ_ਲੰਮਾਈ(UINTPTR ਅਧਾਰ_ਪਤਾ);

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
ਸਥਿਰ INLINE u8 Xil_In8(UINTPTR Addr)
{
	ਵਾਪਸ *(ਅਸਥਿਰ u8 *) Addr;
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
ਸਥਿਰ INLINE u16 Xil_In16(UINTPTR Addr)
{
	ਵਾਪਸ *(ਅਸਥਿਰ u16 *) Addr;
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
ਸਥਿਰ INLINE u32 Xil_In32(UINTPTR Addr)
{
	ਵਾਪਸ *(ਅਸਥਿਰ u32 *) Addr;
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
ਸਥਿਰ INLINE u64 Xil_In64(UINTPTR Addr)
{
	ਵਾਪਸ *(ਅਸਥਿਰ u64 *) Addr;
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
ਸਥਿਰ INLINE ਖਾਲੀ Xil_Out8(UINTPTR Addr, u8 ਮੁੱਲ_2)
{
	ਅਸਥਿਰ u8 *LocalAddr = (ਅਸਥਿਰ u8 *)Addr;
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
ਸਥਿਰ INLINE ਖਾਲੀ Xil_Out16(UINTPTR Addr, u16 ਮੁੱਲ_2)
{
	ਅਸਥਿਰ u16 *LocalAddr = (ਅਸਥਿਰ u16 *)Addr;
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
ਸਥਿਰ INLINE ਖਾਲੀ Xil_Out32(UINTPTR Addr, u32 ਮੁੱਲ_2)
{
	ਅਸਥਿਰ u32 *LocalAddr = (ਅਸਥਿਰ u32 *)Addr;
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
ਸਥਿਰ INLINE ਖਾਲੀ Xil_Out64(UINTPTR Addr, u64 ਮੁੱਲ_2)
{
	ਅਸਥਿਰ u64 *LocalAddr = (ਅਸਥਿਰ u64 *)Addr;
	*LocalAddr = ਮੁੱਲ_2;
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
u16 Xil_EndianSwap16(u16 ਅੰਕੜੇ)
{
	ਵਾਪਸ (u16) (((ਅੰਕੜੇ & 0xFF00U) >> 8U) | ((ਅੰਕੜੇ & 0x00FFU) << 8U));
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
u32 Xil_EndianSwap32(u32 ਅੰਕੜੇ)
{
	u16 Lo_ਸ਼ਬਦ;
	u16 Hi_ਸ਼ਬਦ;

	/* get each of the half words from the 32 bit word */

	Lo_ਸ਼ਬਦ = (u16) (ਅੰਕੜੇ & 0x0000FFFFU);
	Hi_ਸ਼ਬਦ = (u16) ((ਅੰਕੜੇ & 0xFFFF0000U) >> 16U);

	/* byte swap each of the 16 bit half words */

	Lo_ਸ਼ਬਦ = (((Lo_ਸ਼ਬਦ & 0xFF00U) >> 8U) | ((Lo_ਸ਼ਬਦ & 0x00FFU) << 8U));
	Hi_ਸ਼ਬਦ = (((Hi_ਸ਼ਬਦ & 0xFF00U) >> 8U) | ((Hi_ਸ਼ਬਦ & 0x00FFU) << 8U));

	/* swap the half words before returning the value */

	ਵਾਪਸ ((((u32)Lo_ਸ਼ਬਦ) << (u32)16U) | (u32)Hi_ਸ਼ਬਦ);
}


/************************** Variable Definitions *****************************/



u16 Xil_Htons(u16 ਅੰਕੜੇ)
{
	ਵਾਪਸ (u16) (((ਅੰਕੜੇ & 0xFF00U) >> 8U) | ((ਅੰਕੜੇ & 0x00FFU) << 8U));
}

u16 Xil_Ntohs(u16 ਅੰਕੜੇ)
{
	ਵਾਪਸ (u16) (((ਅੰਕੜੇ & 0xFF00U) >> 8U) | ((ਅੰਕੜੇ & 0x00FFU) << 8U));
}


#ਜੇ 0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Xil_In16LE	Xil_In16
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Xil_In32LE	Xil_In32
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Xil_Out16LE	Xil_Out16
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Xil_Out32LE	Xil_Out32
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Xil_Htons	Xil_EndianSwap16
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Xil_Htonl	Xil_EndianSwap32
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Xil_Ntohs	Xil_EndianSwap16
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Xil_Ntohl	Xil_EndianSwap32
#ਜੇ_ਅੰਤ


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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEmacLite_ReadReg(ਅਧਾਰ_ਪਤਾ, Reg_ਵਿੱਥ) \
	XEmacLite_In32((ਅਧਾਰ_ਪਤਾ) + (Reg_ਵਿੱਥ))

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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEmacLite_WriteReg(ਅਧਾਰ_ਪਤਾ, Reg_ਵਿੱਥ, ਰਜਿਸਟਰ_ਮੁੱਲ) \
	XEmacLite_Out32((ਅਧਾਰ_ਪਤਾ) + (Reg_ਵਿੱਥ), (ਰਜਿਸਟਰ_ਮੁੱਲ))


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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEmac_Lite_Get_Tx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ)			\
	(XEmacLite_ReadReg((ਅਧਾਰ_ਪਤਾ), XEL_TSR_ਵਿੱਥ))


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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEmac_Lite_ਸੈੱਟ_Tx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ, ਅੰਕੜੇ)			\
	(XEmacLite_WriteReg((ਅਧਾਰ_ਪਤਾ), XEL_TSR_ਵਿੱਥ, (ਅੰਕੜੇ)))


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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEmac_Lite_Get_Rx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ)			\
	(XEmacLite_ReadReg((ਅਧਾਰ_ਪਤਾ), XEL_RSR_ਵਿੱਥ))


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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEmac_Lite_ਸੈੱਟ_Rx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ, ਅੰਕੜੇ)			\
	(XEmacLite_WriteReg((ਅਧਾਰ_ਪਤਾ), XEL_RSR_ਵਿੱਥ, (ਅੰਕੜੇ)))


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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEmac_Lite_Is_Tx_ਪੂਰਾ(ਅਧਾਰ_ਪਤਾ)			\
		 ((XEmacLite_ReadReg((ਅਧਾਰ_ਪਤਾ), XEL_TSR_ਵਿੱਥ) & 	 \
			 XEL_TSR_XMIT_BUSY_ਨਕਾਬ) != XEL_TSR_XMIT_BUSY_ਨਕਾਬ)


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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEmac_Lite_Is_Rx_ਖਾਲੀ_ਥਾਵਾਂ(ਅਧਾਰ_ਪਤਾ) \
		  ((XEmacLite_ReadReg((ਅਧਾਰ_ਪਤਾ), XEL_RSR_ਵਿੱਥ) & \
			XEL_RSR_RECV_ਪੂਰਾ_ਨਕਾਬ) != XEL_RSR_RECV_ਪੂਰਾ_ਨਕਾਬ)

/************************** Function Prototypes ******************************/

ਖਾਲੀ XEmac_Lite_Send_ਚੌਖਟਾ(UINTPTR ਅਧਾਰ_ਪਤਾ, u8 *ਚੌਖਟਾ_Ptr, ਬਿਨਾਨਿਸ਼ਾਨੀ Byte_ਗਿਣਤੀ);
u16 XEmac_Lite_Recv_ਚੌਖਟਾ(UINTPTR ਅਧਾਰ_ਪਤਾ, u8 *ਚੌਖਟਾ_Ptr);

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
ਖਾਲੀ XEmac_Lite_Send_ਚੌਖਟਾ(UINTPTR ਅਧਾਰ_ਪਤਾ, u8 *ਚੌਖਟਾ_Ptr, ਬਿਨਾਨਿਸ਼ਾਨੀ Byte_ਗਿਣਤੀ)
{
	u32 ਰਜਿਸਟਰ_2;

	/*
	 * Write data to the EmacLite
	 */
	XEmacLite_AlignedWrite(ਚੌਖਟਾ_Ptr, (UINTPTR *) (ਅਧਾਰ_ਪਤਾ), Byte_ਗਿਣਤੀ);

	/*
	 * The frame is in the buffer, now send it
	 */
	XEmacLite_WriteReg(ਅਧਾਰ_ਪਤਾ,  XEL_TPLR_ਵਿੱਥ,
				(Byte_ਗਿਣਤੀ & (XEL_TPLR_ਲੰਮਾਈ_ਨਕਾਬ_HI |
				XEL_TPLR_ਲੰਮਾਈ_ਨਕਾਬ_LO)));


	ਰਜਿਸਟਰ_2 = XEmac_Lite_Get_Tx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ);
	XEmac_Lite_ਸੈੱਟ_Tx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ, ਰਜਿਸਟਰ_2 | XEL_TSR_XMIT_BUSY_ਨਕਾਬ);

	/*
	 * Loop on the status waiting for the transmit to be complete.
	 */
	ਜਦੋਂ (!XEmac_Lite_Is_Tx_ਪੂਰਾ(ਅਧਾਰ_ਪਤਾ));

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
u16 XEmac_Lite_Recv_ਚੌਖਟਾ(UINTPTR ਅਧਾਰ_ਪਤਾ, u8 *ਚੌਖਟਾ_Ptr)
{
	u16 ਲੰਮਾਈ_Type;
	u16 ਲੰਮਾਈ;
	u32 ਰਜਿਸਟਰ_2;

	/*
	 * Wait for a frame to arrive - this is a blocking call
	 */
	ਜਦੋਂ (XEmac_Lite_Is_Rx_ਖਾਲੀ_ਥਾਵਾਂ(ਅਧਾਰ_ਪਤਾ));

	/*
	 * Get the length of the frame that arrived, only 32-bit reads are
	 * allowed LengthType is in the upper half of the 32-bit word.
	 */
	ਰਜਿਸਟਰ_2 = XEmacLite_ReadReg(ਅਧਾਰ_ਪਤਾ, XEL_RPLR_ਵਿੱਥ);
	ਲੰਮਾਈ_Type = (u16) ((ਰਜਿਸਟਰ_2 >> 16) &
			    (XEL_RPLR_ਲੰਮਾਈ_ਨਕਾਬ_HI |
			     XEL_RPLR_ਲੰਮਾਈ_ਨਕਾਬ_LO));

	/*
	 * Check if length is valid
	 */
	ਜੇ (ਲੰਮਾਈ_Type > XEL_MAX_ਚੌਖਟਾ_ਮਾਪ) {
		/*
		 * Field contain type, use max frame size and
		 * let user parse it
		 */
		ਲੰਮਾਈ = XEL_MAX_ਚੌਖਟਾ_ਮਾਪ;
	}
	ਨਹੀਂਤਾਂ {
		/*
		 * Use the length in the frame, plus the header and trailer
		 */
		ਲੰਮਾਈ = ਲੰਮਾਈ_Type + XEL_ਸਿਰਲੇਖ_ਮਾਪ + XEL_FCS_ਮਾਪ;
	}

	/*
	 * Read each byte from the EmacLite
	 */
	XEmacLite_AlignedRead((UINTPTR *) (ਅਧਾਰ_ਪਤਾ + XEL_RXBUFF_ਵਿੱਥ),
			      ਚੌਖਟਾ_Ptr, ਲੰਮਾਈ);

	/*
	 * Acknowledge the frame
	 */
	ਰਜਿਸਟਰ_2 = XEmac_Lite_Get_Rx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ);
	ਰਜਿਸਟਰ_2 &= ~XEL_RSR_RECV_ਪੂਰਾ_ਨਕਾਬ;
	XEmac_Lite_ਸੈੱਟ_Rx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ, ਰਜਿਸਟਰ_2);

	ਵਾਪਸ ਲੰਮਾਈ_Type;
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
ਖਾਲੀ XEmacLite_AlignedWrite(ਖਾਲੀ *SrcPtr, UINTPTR *DestPtr, ਬਿਨਾਨਿਸ਼ਾਨੀ Byte_ਗਿਣਤੀ)
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਸੂਚਕਾਂਕ;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾਈ = Byte_ਗਿਣਤੀ;
	ਅਸਥਿਰ u32 Align_ਬਫਰ;
	ਅਸਥਿਰ u32 *To32Ptr;
	u32 *From32Ptr;
	ਅਸਥਿਰ u16 *To16Ptr;
	u16 *From16Ptr;
	ਅਸਥਿਰ u8 *To8Ptr;
	u8 *From8Ptr;

//	To32Ptr = (volatile UINTPTR *)DestPtr;

	ਜੇ ((((u32) SrcPtr) & 0x00000003) == 0) {

		/*
		 * Word aligned buffer, no correction needed.
		 */
		From32Ptr = (u32 *) SrcPtr;
		To32Ptr = (u32 *)DestPtr;
#ਜੇ 0
		log_info("length is %x", ਲੰਮਾਈ);
		log_info("\n Size of To32Ptr: %x", ਆਕਾਰ(*To32Ptr));
		log_info("\n Size of From32Ptr: %x", ਆਕਾਰ(*From32Ptr));
#ਜੇ_ਅੰਤ		
		ਜਦੋਂ (ਲੰਮਾਈ > 3) {
			/*
			 * Output each word destination.
			 */
			*To32Ptr++ = *From32Ptr++;
#ਜੇ 0
			*To32Ptr = *From32Ptr++;
			ਲਿਖੋ("\n Write value @ %x: %x", To32Ptr, *To32Ptr);
			*To32Ptr++;

//#else
			*To32Ptr = *From32Ptr;
			log_info("\n 1:[%x]; 2: [%x]", *To32Ptr, *From32Ptr);
			log_info("\n 1:[%x]; 2: [%x]", To32Ptr, From32Ptr);
			*To32Ptr++;
			*From32Ptr++;
			log_info("\n 1_2:[%x]; 2: [%x]", *To32Ptr, *From32Ptr);
			log_info("\n 1_2:[%x]; 2: [%x]", To32Ptr, From32Ptr);
#ਜੇ_ਅੰਤ
			/*
			 * Adjust length accordingly
			 */
			ਲੰਮਾਈ -= 4;
		}

		/*
		 * Set up to output the remaining data, zero the temp buffer
		 first.
		 */
		Align_ਬਫਰ = 0;
		To8Ptr = (u8 *) &Align_ਬਫਰ;
		From8Ptr = (u8 *) From32Ptr;

	}
	ਨਹੀਂਤਾਂ ਜੇ ((((u32) SrcPtr) & 0x00000001) != 0) {
		/*
		 * Byte aligned buffer, correct.
		 */
		Align_ਬਫਰ = 0;
		To8Ptr = (u8 *) &Align_ਬਫਰ;
		From8Ptr = (u8 *) SrcPtr;

		ਜਦੋਂ (ਲੰਮਾਈ > 3) {
			/*
			 * Copy each byte into the temporary buffer.
			 */
			ਲਈ (ਸੂਚਕਾਂਕ = 0; ਸੂਚਕਾਂਕ < 4; ਸੂਚਕਾਂਕ++) {
				*To8Ptr++ = *From8Ptr++;
			}

			/*
			 * Output the buffer
			 */
			*To32Ptr++ = Align_ਬਫਰ;

			/*.
			 * Reset the temporary buffer pointer and adjust length.
			 */
			To8Ptr = (u8 *) &Align_ਬਫਰ;
			ਲੰਮਾਈ -= 4;
		}

		/*
		 * Set up to output the remaining data, zero the temp buffer
		 * first.
		 */
		Align_ਬਫਰ = 0;
		To8Ptr = (u8 *) &Align_ਬਫਰ;

	}
	ਨਹੀਂਤਾਂ {
		/*
		 * Half-Word aligned buffer, correct.
		 */
		Align_ਬਫਰ = 0;

		/*
		 * This is a funny looking cast. The new gcc, version 3.3.x has
		 * a strict cast check for 16 bit pointers, aka short pointers.
		 * The following warning is issued if the initial 'void *' cast
		 * is  not used:
		 * 'dereferencing type-punned pointer will break strict-aliasing
		 * rules'
		 */

		To16Ptr = (u16 *) ((ਖਾਲੀ *) &Align_ਬਫਰ);
		From16Ptr = (u16 *) SrcPtr;

		ਜਦੋਂ (ਲੰਮਾਈ > 3) {
			/*
			 * Copy each half word into the temporary buffer.
			 */
			ਲਈ (ਸੂਚਕਾਂਕ = 0; ਸੂਚਕਾਂਕ < 2; ਸੂਚਕਾਂਕ++) {
				*To16Ptr++ = *From16Ptr++;
			}

			/*
			 * Output the buffer.
			 */
			*To32Ptr++ = Align_ਬਫਰ;

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
			To16Ptr = (u16 *) ((ਖਾਲੀ *) &Align_ਬਫਰ);
			ਲੰਮਾਈ -= 4;
		}

		/*
		 * Set up to output the remaining data, zero the temp buffer
		 * first.
		 */
		Align_ਬਫਰ = 0;
		To8Ptr = (u8 *) &Align_ਬਫਰ;
		From8Ptr = (u8 *) From16Ptr;
	}

	/*
	 * Output the remaining data, zero the temp buffer first.
	 */
	ਲਈ (ਸੂਚਕਾਂਕ = 0; ਸੂਚਕਾਂਕ < ਲੰਮਾਈ; ਸੂਚਕਾਂਕ++) {
		*To8Ptr++ = *From8Ptr++;
	}
	ਜੇ (ਲੰਮਾਈ) {
		*To32Ptr++ = Align_ਬਫਰ;
	}
	To32Ptr = (ਅਸਥਿਰ UINTPTR *)DestPtr;
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
ਖਾਲੀ XEmacLite_AlignedRead(UINTPTR *SrcPtr, ਖਾਲੀ *DestPtr, ਬਿਨਾਨਿਸ਼ਾਨੀ Byte_ਗਿਣਤੀ)
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਸੂਚਕਾਂਕ;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾਈ = Byte_ਗਿਣਤੀ;
	ਅਸਥਿਰ u32 Align_ਬਫਰ;
	u32 *To32Ptr;
	ਅਸਥਿਰ u32 *From32Ptr;
	u16 *To16Ptr;
	ਅਸਥਿਰ u16 *From16Ptr;
	u8 *To8Ptr;
	ਅਸਥਿਰ u8 *From8Ptr;

	From32Ptr = (u32 *) SrcPtr;

	ਜੇ ((((u32) DestPtr) & 0x00000003) == 0) {

		/*
		 * Word aligned buffer, no correction needed.
		 */
		To32Ptr = (u32 *) DestPtr;
//		log_info("\n Read: 1:[%x]; 2: [%x]", *To32Ptr, *From32Ptr);
//		log_info("\n 1:[%x]; 2: [%x]", To32Ptr, From32Ptr);

		ਜਦੋਂ (ਲੰਮਾਈ > 3) {
			/*
			 * Output each word.
			 */
			*To32Ptr++ = *From32Ptr++;

			/*
			 * Adjust length accordingly.
			 */
			ਲੰਮਾਈ -= 4;
		}

		/*
		 * Set up to read the remaining data.
		 */
		To8Ptr = (u8 *) To32Ptr;

	}
	ਨਹੀਂਤਾਂ ਜੇ ((((u32) DestPtr) & 0x00000001) != 0) {
		/*
		 * Byte aligned buffer, correct.
		 */
		To8Ptr = (u8 *) DestPtr;

		ਜਦੋਂ (ਲੰਮਾਈ > 3) {
			/*
			 * Copy each word into the temporary buffer.
			 */
			Align_ਬਫਰ = *From32Ptr++;
			From8Ptr = (u8 *) &Align_ਬਫਰ;

			/*
			 * Write data to destination.
			 */
			ਲਈ (ਸੂਚਕਾਂਕ = 0; ਸੂਚਕਾਂਕ < 4; ਸੂਚਕਾਂਕ++) {
				*To8Ptr++ = *From8Ptr++;
			}

			/*
			 * Adjust length
			 */
			ਲੰਮਾਈ -= 4;
		}

	}
	ਨਹੀਂਤਾਂ {
		/*
		 * Half-Word aligned buffer, correct.
		 */
		To16Ptr = (u16 *) DestPtr;

		ਜਦੋਂ (ਲੰਮਾਈ > 3) {
			/*
			 * Copy each word into the temporary buffer.
			 */
			Align_ਬਫਰ = *From32Ptr++;

			/*
			 * This is a funny looking cast. The new gcc, version
			 * 3.3.x has a strict cast check for 16 bit pointers,
			 * aka short pointers. The following warning is issued
			 * if the initial 'void *' cast is not used:
			 * 'dereferencing type-punned pointer will break
			 *  strict-aliasing rules'
			 */
			From16Ptr = (u16 *) ((ਖਾਲੀ *) &Align_ਬਫਰ);

			/*
			 * Write data to destination.
			 */
			ਲਈ (ਸੂਚਕਾਂਕ = 0; ਸੂਚਕਾਂਕ < 2; ਸੂਚਕਾਂਕ++) {
				*To16Ptr++ = *From16Ptr++;
			}

			/*
			 * Adjust length.
			 */
			ਲੰਮਾਈ -= 4;
		}

		/*
		 * Set up to read the remaining data.
		 */
		To8Ptr = (u8 *) To16Ptr;
	}

	/*
	 * Read the remaining data.
	 */
	Align_ਬਫਰ = *From32Ptr++;
	From8Ptr = (u8 *) &Align_ਬਫਰ;

	ਲਈ (ਸੂਚਕਾਂਕ = 0; ਸੂਚਕਾਂਕ < ਲੰਮਾਈ; ਸੂਚਕਾਂਕ++) {
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
ਪੂਰਨ XEmacLite_CfgInitialize(XEmacLite *InstancePtr,
				XEmacLite_Config *EmacLiteConfigPtr,
				UINTPTR EffectiveAddr)
{

	/*
	 * Verify that each of the inputs are valid.
	 */
//	Xil_AssertNonvoid(InstancePtr != NULL);
	ਜੇ(ਨਿਰਾ == InstancePtr)
	{
		log_error("\nEthernet Parameter - InstancePtr is Null");
		ਵਾਪਸ -1;
	}
//	Xil_AssertNonvoid(EmacLiteConfigPtr != NULL);
	ਜੇ(ਨਿਰਾ == EmacLiteConfigPtr)
	{
		log_error("Ethernet Parameter - EmacLiteConfigPtr is Null");
		ਵਾਪਸ -1;
	}

	/*
	 * Zero the provided instance memory.
	 */
	memset(InstancePtr, 0, ਆਕਾਰ(XEmacLite));

	/*
	 * Set some default values for instance data, don't indicate the device
	 * is ready to use until everything has been initialized successfully.
	 */
	InstancePtr->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ = EffectiveAddr;
	InstancePtr->EmacLiteConfig.DeviceId = EmacLiteConfigPtr->DeviceId;
	InstancePtr->EmacLiteConfig.TxPingPong = EmacLiteConfigPtr->TxPingPong;
	InstancePtr->EmacLiteConfig.RxPingPong = EmacLiteConfigPtr->RxPingPong;
	InstancePtr->EmacLiteConfig.MdioInclude = EmacLiteConfigPtr->MdioInclude;
	InstancePtr->EmacLiteConfig.Loopback = EmacLiteConfigPtr->Loopback;

	InstancePtr->ਅਗਲਾ_Tx_ਬਫਰ_ਮੰਜ਼ਿਲ_Use = 0x0;
	InstancePtr->ਅਗਲਾ_Rx_ਬਫਰ_ਮੰਜ਼ਿਲ_Use = 0x0;
	InstancePtr->RecvHandler = (XEmacLite_Handler) StubHandler;
	InstancePtr->SendHandler = (XEmacLite_Handler) StubHandler;
	/*
	 * Clear the TX CSR's in case this is a restart.
	 */
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ,
				XEL_TSR_ਵਿੱਥ, 0);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ,
				XEL_ਬਫਰ_ਵਿੱਥ + XEL_TSR_ਵਿੱਥ, 0);

	/*
	 * Since there were no failures, indicate the device is ready to use.
	 */
	InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

	ਵਾਪਸ SUCCESS;
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
ਪੂਰਨ XEmacLite_Send(XEmacLite *InstancePtr, u8 *ਚੌਖਟਾ_Ptr, ਬਿਨਾਨਿਸ਼ਾਨੀ Byte_ਗਿਣਤੀ)
{
	u32 ਰਜਿਸਟਰ_2;
	UINTPTR ਅਧਾਰ_ਪਤਾ;
	UINTPTR Emac_ਅਧਾਰ_ਪਤਾ;
	u32 Intr_Enable_ਸਥਿਤੀ;

	/*
	 * Verify that each of the inputs are valid.
	 */
//	Xil_AssertNonvoid(InstancePtr != NULL);
	ਜੇ (InstancePtr == ਨਿਰਾ) {
		ਵਾਪਸ -1;
	}

	/*
	 * Determine the expected TX buffer address.
	 */
	ਅਧਾਰ_ਪਤਾ = XEmac_Lite_ਅਗਲਾ_Transmit_Addr(InstancePtr);
	Emac_ਅਧਾਰ_ਪਤਾ = InstancePtr->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ;

	/*
	 * Check the Length if it is too large, truncate it.
	 * The maximum Tx packet size is
	 * Ethernet header (14 Bytes) + Maximum MTU (1500 bytes).
	 */
	ਜੇ (Byte_ਗਿਣਤੀ > XEL_MAX_TX_ਚੌਖਟਾ_ਮਾਪ) {

		Byte_ਗਿਣਤੀ = XEL_MAX_TX_ਚੌਖਟਾ_ਮਾਪ;
	}

	/*
	 * Determine if the expected buffer address is empty.
	 */
	ਰਜਿਸਟਰ_2 = XEmac_Lite_Get_Tx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ);

	/*
	 * If the expected buffer is available, fill it with the provided data
	 * Align if necessary.
	 */
	ਜੇ ((ਰਜਿਸਟਰ_2 & (XEL_TSR_XMIT_BUSY_ਨਕਾਬ |
			XEL_TSR_XMIT_ਸਰਗਰਮ_ਨਕਾਬ)) == 0) {

		/*
		 * Switch to next buffer if configured.
		 */
		ਜੇ (InstancePtr->EmacLiteConfig.TxPingPong != 0) {
			InstancePtr->ਅਗਲਾ_Tx_ਬਫਰ_ਮੰਜ਼ਿਲ_Use ^= XEL_ਬਫਰ_ਵਿੱਥ;
		}

		/*
		 * Write the frame to the buffer.
		 */
		XEmacLite_AlignedWrite(ਚੌਖਟਾ_Ptr, (UINTPTR *) ਅਧਾਰ_ਪਤਾ,
				       Byte_ਗਿਣਤੀ);


		/*
		 * The frame is in the buffer, now send it.
		 */
		XEmacLite_WriteReg(ਅਧਾਰ_ਪਤਾ, XEL_TPLR_ਵਿੱਥ,
					(Byte_ਗਿਣਤੀ & (XEL_TPLR_ਲੰਮਾਈ_ਨਕਾਬ_HI |
					XEL_TPLR_ਲੰਮਾਈ_ਨਕਾਬ_LO)));

		/*
		 * Update the Tx Status Register to indicate that there is a
		 * frame to send.
		 * If the interrupt enable bit of Ping buffer(since this
		 * controls both the buffers) is enabled then set the
		 * XEL_TSR_XMIT_ACTIVE_MASK flag which is used by the interrupt
		 * handler to call the callback function provided by the user
		 * to indicate that the frame has been transmitted.
		 */
		ਰਜਿਸਟਰ_2 = XEmac_Lite_Get_Tx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ);
		ਰਜਿਸਟਰ_2 |= XEL_TSR_XMIT_BUSY_ਨਕਾਬ;
		Intr_Enable_ਸਥਿਤੀ = XEmac_Lite_Get_Tx_ਸਥਿਤੀ(Emac_ਅਧਾਰ_ਪਤਾ);
		ਜੇ ((Intr_Enable_ਸਥਿਤੀ & XEL_TSR_XMIT_IE_ਨਕਾਬ) != 0) {
			ਰਜਿਸਟਰ_2 |= XEL_TSR_XMIT_ਸਰਗਰਮ_ਨਕਾਬ;
		}
		XEmac_Lite_ਸੈੱਟ_Tx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ, ਰਜਿਸਟਰ_2);

		ਵਾਪਸ SUCCESS;
	}

	/*
	 * If the expected buffer was full, try the other buffer if configured.
	 */
	ਜੇ (InstancePtr->EmacLiteConfig.TxPingPong != 0) {

		ਅਧਾਰ_ਪਤਾ ^= XEL_ਬਫਰ_ਵਿੱਥ;

		/*
		 * Determine if the expected buffer address is empty.
		 */
		ਰਜਿਸਟਰ_2 = XEmac_Lite_Get_Tx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ);

		/*
		 * If the next buffer is available, fill it with the provided
		 * data.
		 */
		ਜੇ ((ਰਜਿਸਟਰ_2 & (XEL_TSR_XMIT_BUSY_ਨਕਾਬ |
				XEL_TSR_XMIT_ਸਰਗਰਮ_ਨਕਾਬ)) == 0) {

			/*
			 * Write the frame to the buffer.
			 */
			XEmacLite_AlignedWrite(ਚੌਖਟਾ_Ptr, (UINTPTR *) ਅਧਾਰ_ਪਤਾ,
					       Byte_ਗਿਣਤੀ);

			/*
			 * The frame is in the buffer, now send it.
			 */
			XEmacLite_WriteReg(ਅਧਾਰ_ਪਤਾ, XEL_TPLR_ਵਿੱਥ,
					(Byte_ਗਿਣਤੀ & (XEL_TPLR_ਲੰਮਾਈ_ਨਕਾਬ_HI |
					   XEL_TPLR_ਲੰਮਾਈ_ਨਕਾਬ_LO)));

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
			ਰਜਿਸਟਰ_2 = XEmac_Lite_Get_Tx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ);
			ਰਜਿਸਟਰ_2 |= XEL_TSR_XMIT_BUSY_ਨਕਾਬ;
			Intr_Enable_ਸਥਿਤੀ =
					XEmac_Lite_Get_Tx_ਸਥਿਤੀ(Emac_ਅਧਾਰ_ਪਤਾ);
			ਜੇ ((Intr_Enable_ਸਥਿਤੀ & XEL_TSR_XMIT_IE_ਨਕਾਬ) != 0) {
				ਰਜਿਸਟਰ_2 |= XEL_TSR_XMIT_ਸਰਗਰਮ_ਨਕਾਬ;
			}
			XEmac_Lite_ਸੈੱਟ_Tx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ, ਰਜਿਸਟਰ_2);

			/*
			 * Do not switch to next buffer, there is a sync problem
			 * and the expected buffer should not change.
			 */
			ਵਾਪਸ SUCCESS;
		}
	}

	ਲਿਖੋ("\n Error in sending the packet");
	/*
	 * Buffer(s) was(were) full, return failure to allow for polling usage.
	 */
	ਵਾਪਸ FAILURE;
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
u16 XEmacLite_Recv(XEmacLite *InstancePtr, u8 *ਚੌਖਟਾ_Ptr)
{
	u16 ਲੰਮਾਈ_Type;
	u16 ਲੰਮਾਈ;
	u32 ਰਜਿਸਟਰ_2;
	UINTPTR ਅਧਾਰ_ਪਤਾ;

	/*
	 * Verify that each of the inputs are valid.
	 */

	ਜੇ (InstancePtr == ਨਿਰਾ) {
		ਵਾਪਸ -1;
	}

	/*
	 * Determine the expected buffer address.
	 */
	ਅਧਾਰ_ਪਤਾ = XEmac_Lite_ਅਗਲਾ_Receive_Addr(InstancePtr);

	/*
	 * Verify which buffer has valid data.
	 */
	ਰਜਿਸਟਰ_2 = XEmac_Lite_Get_Rx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ);

	ਜੇ ((ਰਜਿਸਟਰ_2 & XEL_RSR_RECV_ਪੂਰਾ_ਨਕਾਬ) == XEL_RSR_RECV_ਪੂਰਾ_ਨਕਾਬ) {

		/*
		 * The driver is in sync, update the next expected buffer if
		 * configured.
		 */

		ਜੇ (InstancePtr->EmacLiteConfig.RxPingPong != 0) {
			InstancePtr->ਅਗਲਾ_Rx_ਬਫਰ_ਮੰਜ਼ਿਲ_Use ^= XEL_ਬਫਰ_ਵਿੱਥ;
		}
	}
	ਨਹੀਂਤਾਂ {
		/*
		 * The instance is out of sync, try other buffer if other
		 * buffer is configured, return 0 otherwise. If the instance is
		 * out of sync, do not update the 'NextRxBufferToUse' since it
		 * will correct on subsequent calls.
		 */
		ਜੇ (InstancePtr->EmacLiteConfig.RxPingPong != 0) {
			ਅਧਾਰ_ਪਤਾ ^= XEL_ਬਫਰ_ਵਿੱਥ;
		}
		ਨਹੀਂਤਾਂ {
			ਵਾਪਸ 0;	/* No data was available */
		}

		/*
		 * Verify that buffer has valid data.
		 */
		ਰਜਿਸਟਰ_2 = XEmac_Lite_Get_Rx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ);
		ਜੇ ((ਰਜਿਸਟਰ_2 & XEL_RSR_RECV_ਪੂਰਾ_ਨਕਾਬ) !=
				XEL_RSR_RECV_ਪੂਰਾ_ਨਕਾਬ) {
			ਵਾਪਸ 0;	/* No data was available */
		}
	}

	/*
	 * Get the length of the frame that arrived.
	 */
	ਲੰਮਾਈ_Type = XEmac_Lite_Get_Receive_ਅੰਕੜੇ_ਲੰਮਾਈ(ਅਧਾਰ_ਪਤਾ);

	/*
	 * Check if length is valid.
	 */
	ਜੇ (ਲੰਮਾਈ_Type > XEL_MAX_ਚੌਖਟਾ_ਮਾਪ) {


		ਜੇ (ਲੰਮਾਈ_Type == XEL_ETHER_PROTO_TYPE_IP) {

			/*
			 * The packet is a an IP Packet.
			 */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __LITTLE_ENDIAN__
			ਲੰਮਾਈ = (XEmacLite_ReadReg((ਅਧਾਰ_ਪਤਾ),
					XEL_ਸਿਰਲੇਖ_IP_ਲੰਮਾਈ_ਵਿੱਥ +
					XEL_RXBUFF_ਵਿੱਥ) &
					(XEL_RPLR_ਲੰਮਾਈ_ਨਕਾਬ_HI |
					XEL_RPLR_ਲੰਮਾਈ_ਨਕਾਬ_LO));
			ਲੰਮਾਈ = (u16) (((ਲੰਮਾਈ & 0xFF00) >> 8) | ((ਲੰਮਾਈ & 0x00FF) << 8));
#ਨਹੀਂਤਾਂ
			ਲੰਮਾਈ = ((XEmacLite_ReadReg((ਅਧਾਰ_ਪਤਾ),
					XEL_ਸਿਰਲੇਖ_IP_ਲੰਮਾਈ_ਵਿੱਥ +
					XEL_RXBUFF_ਵਿੱਥ) >>
					XEL_ਸਿਰਲੇਖ_ਖਿਸਕਾਓ) &
					(XEL_RPLR_ਲੰਮਾਈ_ਨਕਾਬ_HI |
					XEL_RPLR_ਲੰਮਾਈ_ਨਕਾਬ_LO));
#ਜੇ_ਅੰਤ

//			Length += XEL_HEADER_SIZE + XEL_FCS_SIZE;
			ਲੰਮਾਈ += XEL_ਸਿਰਲੇਖ_ਮਾਪ;
//			printf("\n Length1 is %x", Length);

		} ਨਹੀਂਤਾਂ ਜੇ (ਲੰਮਾਈ_Type == XEL_ETHER_PROTO_TYPE_ARP) {

			/*
			 * The packet is an ARP Packet.
			 */
			ਲੰਮਾਈ = XEL_ARP_PACKET_ਮਾਪ + XEL_ਸਿਰਲੇਖ_ਮਾਪ +
					XEL_FCS_ਮਾਪ;

		} ਨਹੀਂਤਾਂ {
			/*
			 * Field contains type other than IP or ARP, use max
			 * frame size and let user parse it.
			 */
			ਲੰਮਾਈ = XEL_MAX_ਚੌਖਟਾ_ਮਾਪ;

		}
	} ਨਹੀਂਤਾਂ {

		/*
		 * Use the length in the frame, plus the header and trailer.
		 */
		ਲੰਮਾਈ = ਲੰਮਾਈ_Type + XEL_ਸਿਰਲੇਖ_ਮਾਪ + XEL_FCS_ਮਾਪ;
	}

	/*
	 * Read from the EmacLite.
	 */
	XEmacLite_AlignedRead(((UINTPTR *) (ਅਧਾਰ_ਪਤਾ + XEL_RXBUFF_ਵਿੱਥ)),
			      ਚੌਖਟਾ_Ptr, ਲੰਮਾਈ);

	/*
	 * Acknowledge the frame.
	 */
	ਰਜਿਸਟਰ_2 = XEmac_Lite_Get_Rx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ);
	ਰਜਿਸਟਰ_2 &= ~XEL_RSR_RECV_ਪੂਰਾ_ਨਕਾਬ;
	XEmac_Lite_ਸੈੱਟ_Rx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ, ਰਜਿਸਟਰ_2);

	ਵਾਪਸ ਲੰਮਾਈ;
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
ਖਾਲੀ XEmac_Lite_ਸੈੱਟ_Mac_ਪਤਾ(XEmacLite *InstancePtr, u8 *ਪਤਾ_Ptr)
{
	UINTPTR ਅਧਾਰ_ਪਤਾ;

	/*
	 * Verify that each of the inputs are valid.
	 */
	ਜੇ (InstancePtr == ਨਿਰਾ) {
		ਵਾਪਸ -1;
	}

	/*
	 * Determine the expected TX buffer address.
	 */
	ਅਧਾਰ_ਪਤਾ = XEmac_Lite_ਅਗਲਾ_Transmit_Addr(InstancePtr);

	/*
	 * Copy the MAC address to the Transmit buffer.
	 */
	XEmacLite_AlignedWrite(ਪਤਾ_Ptr,
				(UINTPTR *) ਅਧਾਰ_ਪਤਾ,
				XEL_MAC_ADDR_ਮਾਪ);

	/*
	 * Set the length.
	 */
	XEmacLite_WriteReg(ਅਧਾਰ_ਪਤਾ,
				XEL_TPLR_ਵਿੱਥ,
				XEL_MAC_ADDR_ਮਾਪ);

	/*
	 * Update the MAC address in the EmacLite.
	 */
	XEmac_Lite_ਸੈੱਟ_Tx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ, XEL_TSR_PROG_MAC_ADDR);


	/*
	 * Wait for EmacLite to finish with the MAC address update.
	 */
	ਜਦੋਂ ((XEmac_Lite_Get_Tx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ) &
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
ਖਾਲੀ StubHandler(ਖਾਲੀ *Call_ਪਿੱਠ_Ref)
{
	(ਖਾਲੀ)(Call_ਪਿੱਠ_Ref);
	ਵਾਪਸ 1;
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
ਪੂਰਨ XEmac_Lite_Tx_ਬਫਰ_ਉਪਲਬਧ(XEmacLite *InstancePtr)
{

	u32 ਰਜਿਸਟਰ_2;
	ਪੂਰਨ TxPingBusy;
	ਪੂਰਨ TxPongBusy;

	/*
	 * Verify that each of the inputs are valid.
	 */
	ਜੇ (InstancePtr == ਨਿਰਾ) {
		ਵਾਪਸ -1;
	}

	/*
	 * Read the Tx Status and determine if the buffer is available.
	 */
	ਰਜਿਸਟਰ_2 = XEmac_Lite_Get_Tx_ਸਥਿਤੀ(InstancePtr->EmacLiteConfig.
						ਅਧਾਰ_ਪਤਾ);

	TxPingBusy = (ਰਜਿਸਟਰ_2 & (XEL_TSR_XMIT_BUSY_ਨਕਾਬ |
				 XEL_TSR_XMIT_ਸਰਗਰਮ_ਨਕਾਬ));


	/*
	 * Read the Tx Status of the second buffer register and determine if the
	 * buffer is available.
	 */
	ਜੇ (InstancePtr->EmacLiteConfig.TxPingPong != 0) {
		ਰਜਿਸਟਰ_2 = XEmac_Lite_Get_Tx_ਸਥਿਤੀ(InstancePtr->EmacLiteConfig.
						ਅਧਾਰ_ਪਤਾ +
						XEL_ਬਫਰ_ਵਿੱਥ);

		TxPongBusy = (ਰਜਿਸਟਰ_2 & (XEL_TSR_XMIT_BUSY_ਨਕਾਬ |
					XEL_TSR_XMIT_ਸਰਗਰਮ_ਨਕਾਬ));

		ਵਾਪਸ (!(TxPingBusy && TxPongBusy));
	}

	ਵਾਪਸ (!TxPingBusy);


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
ਖਾਲੀ XEmacLite_FlushReceive(XEmacLite *InstancePtr)
{

	u32 ਰਜਿਸਟਰ_2;

	/*
	 * Verify that each of the inputs are valid.
	 */
		ਜੇ (InstancePtr == ਨਿਰਾ) {
			ਵਾਪਸ -1;
		}

	/*
	 * Read the current buffer register and determine if the buffer is
	 * available.
	 */
	ਰਜਿਸਟਰ_2 = XEmac_Lite_Get_Rx_ਸਥਿਤੀ(InstancePtr->EmacLiteConfig.
						ਅਧਾਰ_ਪਤਾ);

	/*
	 * Preserve the IE bit.
	 */
	ਰਜਿਸਟਰ_2 &= XEL_RSR_RECV_IE_ਨਕਾਬ;

	/*
	 * Write out the value to flush the RX buffer.
	 */
	XEmac_Lite_ਸੈੱਟ_Rx_ਸਥਿਤੀ(InstancePtr->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ,
				ਰਜਿਸਟਰ_2);

	/*
	 * If the pong buffer is available, flush it also.
	 */
	ਜੇ (InstancePtr->EmacLiteConfig.RxPingPong != 0) {
		/*
		 * Read the current buffer register and determine if the buffer
		 * is available.
		 */
		ਰਜਿਸਟਰ_2 = XEmac_Lite_Get_Rx_ਸਥਿਤੀ(InstancePtr->EmacLiteConfig.
							ਅਧਾਰ_ਪਤਾ +
							XEL_ਬਫਰ_ਵਿੱਥ);

		/*
		 * Preserve the IE bit.
		 */
		ਰਜਿਸਟਰ_2 &= XEL_RSR_RECV_IE_ਨਕਾਬ;

		/*
		 * Write out the value to flush the RX buffer.
		 */
		XEmac_Lite_ਸੈੱਟ_Rx_ਸਥਿਤੀ(InstancePtr->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ +
					XEL_ਬਫਰ_ਵਿੱਥ, ਰਜਿਸਟਰ_2);

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
ਪੂਰਨ XEmacLite_PhyRead(XEmacLite *InstancePtr, u32 Phy_ਪਤਾ, u32 Reg_ਅੰਕ,
			u16 *Phy_ਅੰਕੜੇ_Ptr)
{
	u32 PhyAddrReg;
	u32 MdioCtrlReg;

	/*
	 * Verify that each of the inputs are valid.
	 */
		ਜੇ (InstancePtr == ਨਿਰਾ) {
			ਵਾਪਸ -1;
		}
		ਜੇ (InstancePtr->EmacLiteConfig.MdioInclude == TRUE) {
			ਵਾਪਸ -1;
		}
		ਜੇ (Phy_ਪਤਾ <= 31) {
			ਵਾਪਸ -1;
		}
		ਜੇ (Reg_ਅੰਕ <= 31) {
			ਵਾਪਸ -1;
		}

	ਜੇ (Phy_ਅੰਕੜੇ_Ptr == ਨਿਰਾ) {
		ਵਾਪਸ -1;
	}

	/*
	 * Verify MDIO master status.
	 */
	ਜੇ (XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ,
				XEL_MDIOCNTR_ਵਿੱਥ) &
				XEL_MDIOCNTR_ਸਥਿਤੀ_ਨਕਾਬ) {
		ਵਾਪਸ DEVICE_BUSY;
	}

	PhyAddrReg = ((((Phy_ਪਤਾ << XEL_MDIO_ਪਤਾ_ਖਿਸਕਾਓ) &
			XEL_MDIO_ਪਤਾ_ਨਕਾਬ) | Reg_ਅੰਕ) | XEL_MDIO_OP_ਨਕਾਬ);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ,
				 XEL_MDIOADDR_ਵਿੱਥ, PhyAddrReg);

	/*
	 * Enable MDIO and start the transfer.
	 */
	MdioCtrlReg =
		XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ,
					XEL_MDIOCNTR_ਵਿੱਥ);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ,
				XEL_MDIOCNTR_ਵਿੱਥ,
				MdioCtrlReg |
				XEL_MDIOCNTR_ਸਥਿਤੀ_ਨਕਾਬ |
				XEL_MDIOCNTR_ENABLE_ਨਕਾਬ);

	/*
	 * Wait till the completion of transfer.
	 */
	ਜਦੋਂ ((XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ,
				XEL_MDIOCNTR_ਵਿੱਥ) &
				XEL_MDIOCNTR_ਸਥਿਤੀ_ਨਕਾਬ));

	/*
	 * Read data from MDIO read data register.
	 */
	*Phy_ਅੰਕੜੇ_Ptr = (u16)XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ,
					XEL_MDIORD_ਵਿੱਥ);

	/*
	 * Disable the MDIO.
	 */
	MdioCtrlReg =
		XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ,
					XEL_MDIOCNTR_ਵਿੱਥ);

	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ,
				XEL_MDIOCNTR_ਵਿੱਥ,
				MdioCtrlReg & ~XEL_MDIOCNTR_ENABLE_ਨਕਾਬ);


	ਵਾਪਸ SUCCESS;
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
ਪੂਰਨ XEmacLite_PhyWrite(XEmacLite *InstancePtr, u32 Phy_ਪਤਾ, u32 Reg_ਅੰਕ,
			u16 Phy_ਅੰਕੜੇ)
{
	u32 PhyAddrReg;
	u32 MdioCtrlReg;

	/*
	 * Verify that each of the inputs are valid.
	 */
	ਜੇ (InstancePtr == ਨਿਰਾ) {
		ਵਾਪਸ -1;
	}
	ਜੇ (InstancePtr->EmacLiteConfig.MdioInclude == TRUE) {
		ਵਾਪਸ -1;
	}
	ਜੇ (Phy_ਪਤਾ <= 31) {
		ਵਾਪਸ -1;
	}
	ਜੇ (Reg_ਅੰਕ <= 31) {
		ਵਾਪਸ -1;
	}

	/*
	 * Verify MDIO master status.
	 */
	ਜੇ (XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ,
				XEL_MDIOCNTR_ਵਿੱਥ) &
				XEL_MDIOCNTR_ਸਥਿਤੀ_ਨਕਾਬ) {
		ਵਾਪਸ DEVICE_BUSY;
	}



	PhyAddrReg = ((((Phy_ਪਤਾ << XEL_MDIO_ਪਤਾ_ਖਿਸਕਾਓ) &
			XEL_MDIO_ਪਤਾ_ਨਕਾਬ) | Reg_ਅੰਕ) & ~XEL_MDIO_OP_ਨਕਾਬ);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ,
				XEL_MDIOADDR_ਵਿੱਥ, PhyAddrReg);

	/*
	 * Write data to MDIO write data register.
	 */
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ,
				XEL_MDIOWR_ਵਿੱਥ, (u32)Phy_ਅੰਕੜੇ);

	/*
	 * Enable MDIO and start the transfer.
	 */
	MdioCtrlReg =
		XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ,
					XEL_MDIOCNTR_ਵਿੱਥ);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ,
				XEL_MDIOCNTR_ਵਿੱਥ,
				MdioCtrlReg | XEL_MDIOCNTR_ਸਥਿਤੀ_ਨਕਾਬ |
				XEL_MDIOCNTR_ENABLE_ਨਕਾਬ);

	/*
	 * Wait till the completion of transfer.
	 */
	ਜਦੋਂ ((XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ,
				XEL_MDIOCNTR_ਵਿੱਥ) & XEL_MDIOCNTR_ਸਥਿਤੀ_ਨਕਾਬ));


	/*
	 * Disable the MDIO.
	 */
	MdioCtrlReg =
		XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ,
					XEL_MDIOCNTR_ਵਿੱਥ);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ,
				XEL_MDIOCNTR_ਵਿੱਥ,
				MdioCtrlReg & ~XEL_MDIOCNTR_ENABLE_ਨਕਾਬ);



	ਵਾਪਸ SUCCESS;
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
ਖਾਲੀ XEmac_Lite_Enable_Loop_ਪਿੱਠ(XEmacLite *InstancePtr)
{
	u32 TsrReg;

	/*
	 * Verify that each of the inputs are valid.
	 */
	ਜੇ (InstancePtr == ਨਿਰਾ) {
		ਵਾਪਸ -1;
	}
	ਜੇ (InstancePtr->EmacLiteConfig.Loopback == TRUE) {
		ਵਾਪਸ -1;
	}

	TsrReg = XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ,
					XEL_TSR_ਵਿੱਥ);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ,
			XEL_TSR_ਵਿੱਥ,	TsrReg | XEL_TSR_LOOPBACK_ਨਕਾਬ);
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
ਖਾਲੀ XEmac_Lite_Disable_Loop_ਪਿੱਠ(XEmacLite *InstancePtr)
{
	u32 TsrReg;

	/*
	 * Verify that each of the inputs are valid.
	 */
		ਜੇ (InstancePtr == ਨਿਰਾ) {
			ਵਾਪਸ -1;
		}
		ਜੇ (InstancePtr->EmacLiteConfig.Loopback == TRUE) {
			ਵਾਪਸ -1;
		}

	TsrReg = XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ,
					XEL_TSR_ਵਿੱਥ);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ,
			XEL_TSR_ਵਿੱਥ,	TsrReg & (~XEL_TSR_LOOPBACK_ਨਕਾਬ));
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
ਸਥਿਰ u16 XEmac_Lite_Get_Receive_ਅੰਕੜੇ_ਲੰਮਾਈ(UINTPTR ਅਧਾਰ_ਪਤਾ)
{
	u16 ਲੰਮਾਈ;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __LITTLE_ENDIAN__
	ਲੰਮਾਈ = (XEmacLite_ReadReg((ਅਧਾਰ_ਪਤਾ),
			XEL_ਸਿਰਲੇਖ_ਵਿੱਥ + XEL_RXBUFF_ਵਿੱਥ) &
			(XEL_RPLR_ਲੰਮਾਈ_ਨਕਾਬ_HI | XEL_RPLR_ਲੰਮਾਈ_ਨਕਾਬ_LO));
	ਲੰਮਾਈ = (u16) (((ਲੰਮਾਈ & 0xFF00) >> 8) | ((ਲੰਮਾਈ & 0x00FF) << 8));
#ਨਹੀਂਤਾਂ
	ਲੰਮਾਈ = ((XEmacLite_ReadReg((ਅਧਾਰ_ਪਤਾ),
			XEL_ਸਿਰਲੇਖ_ਵਿੱਥ + XEL_RXBUFF_ਵਿੱਥ) >>
			XEL_ਸਿਰਲੇਖ_ਖਿਸਕਾਓ) &
			(XEL_RPLR_ਲੰਮਾਈ_ਨਕਾਬ_HI | XEL_RPLR_ਲੰਮਾਈ_ਨਕਾਬ_LO));
#ਜੇ_ਅੰਤ

	ਵਾਪਸ ਲੰਮਾਈ;
}

ਪੂਰਨ XEmacLite_EnableInterrupts(XEmacLite *InstancePtr)
{
	u32 ਰਜਿਸਟਰ_2;
	UINTPTR ਅਧਾਰ_ਪਤਾ;

	/*
	 * Verify that each of the inputs are valid.
	 */
	ਜੇ(ਨਿਰਾ == InstancePtr)
		ਵਾਪਸ -1;
	ਜੇ(InstancePtr->IsReady != XIL_COMPONENT_IS_READY)
		ਵਾਪਸ -1;

	/*
	 * Verify that the handlers are in place.
	 */
	ਜੇ ((InstancePtr->RecvHandler == (XEmacLite_Handler) StubHandler) ||
	    (InstancePtr->SendHandler == (XEmacLite_Handler) StubHandler)) {
		ਵਾਪਸ XST_NO_CALLBACK;
	}

	/*
	 * Enable the TX interrupts for both the buffers, the Interrupt Enable
	 * is common for the both the buffers and is defined in the
	 * Ping buffer.
	 */
	ਰਜਿਸਟਰ_2 = XEmac_Lite_Get_Tx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ);
	ਰਜਿਸਟਰ_2 |= XEL_TSR_XMIT_IE_ਨਕਾਬ;
	XEmac_Lite_ਸੈੱਟ_Tx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ, ਰਜਿਸਟਰ_2);

	/*
	 * Enable the RX interrupts for both the buffers, the Interrupt Enable
	 * is common for the both the buffers and is defined in the
	 * Ping buffer.
	 */
	ਰਜਿਸਟਰ_2 = XEmac_Lite_Get_Rx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ);
	ਰਜਿਸਟਰ_2 |= XEL_RSR_RECV_IE_ਨਕਾਬ;
	XEmac_Lite_ਸੈੱਟ_Rx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ, ਰਜਿਸਟਰ_2);

	/*
	 * Enable the global interrupt output.
	 */
	XEmacLite_WriteReg(ਅਧਾਰ_ਪਤਾ, XEL_GIER_ਵਿੱਥ, XEL_GIER_GIE_ਨਕਾਬ);

	ਵਾਪਸ SUCCESS;
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
ਖਾਲੀ XEmacLite_DisableInterrupts(XEmacLite *InstancePtr)
{
	u32 ਰਜਿਸਟਰ_2;
	UINTPTR ਅਧਾਰ_ਪਤਾ;

	/*
	 * Verify that each of the inputs are valid.
	 */
		ਜੇ(ਨਿਰਾ == InstancePtr)
			ਵਾਪਸ -1;
		ਜੇ(InstancePtr->IsReady != XIL_COMPONENT_IS_READY)
			ਵਾਪਸ -1;


	ਅਧਾਰ_ਪਤਾ = InstancePtr->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ;

	/*
	 * Disable the global interrupt output.
	 */
	XEmacLite_WriteReg(ਅਧਾਰ_ਪਤਾ, XEL_GIER_ਵਿੱਥ, 0);

	/*
	 * Disable the TX interrupts for both the buffers, the Interrupt Enable
	 * is common for the both the buffers and is defined in the
	 * Ping buffer.
	 */
	ਰਜਿਸਟਰ_2 = XEmac_Lite_Get_Tx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ);
	ਰਜਿਸਟਰ_2 &= ~XEL_TSR_XMIT_IE_ਨਕਾਬ;
	XEmac_Lite_ਸੈੱਟ_Tx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ, ਰਜਿਸਟਰ_2);

	/*
	 * Disable the RX interrupts for both the buffers, the Interrupt Enable
	 * is common for the both the buffers and is defined in the
	 * Ping buffer.
	 */
	ਰਜਿਸਟਰ_2 = XEmac_Lite_Get_Rx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ);
	ਰਜਿਸਟਰ_2 &= ~XEL_RSR_RECV_IE_ਨਕਾਬ;
	XEmac_Lite_ਸੈੱਟ_Rx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ, ਰਜਿਸਟਰ_2);

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
ਖਾਲੀ XEmac_Lite_ਰੁਕਾਵਟ_Handler(ਖਾਲੀ *InstancePtr)
{

	XEmacLite *EmacLitePtr;
	ਪੂਰਨ TxCompleteIntr = FALSE;
	UINTPTR ਅਧਾਰ_ਪਤਾ;
	u32 Tx_ਸਥਿਤੀ;

	/*
	 * Verify that each of the inputs are valid.
	 */
		ਜੇ(ਨਿਰਾ == InstancePtr)
			ਵਾਪਸ -1;

	/*
	 * Convert the non-typed pointer to an EmacLite instance pointer
	 * such that there is access to the device.
	 */
	EmacLitePtr = (XEmacLite *) InstancePtr;
	ਅਧਾਰ_ਪਤਾ = EmacLitePtr->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ;

	ਜੇ ((XEmac_Lite_Is_Rx_ਖਾਲੀ_ਥਾਵਾਂ(ਅਧਾਰ_ਪਤਾ) != TRUE) ||
		(XEmac_Lite_Is_Rx_ਖਾਲੀ_ਥਾਵਾਂ(ਅਧਾਰ_ਪਤਾ +
			XEL_ਬਫਰ_ਵਿੱਥ) != TRUE)) {
		/*
		 * Call the RX callback.
		 */
		EmacLitePtr->RecvHandler(EmacLitePtr->RecvRef);

	}

	Tx_ਸਥਿਤੀ = XEmac_Lite_Get_Tx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ);
	ਜੇ (((Tx_ਸਥਿਤੀ & XEL_TSR_XMIT_BUSY_ਨਕਾਬ) == 0) &&
		(Tx_ਸਥਿਤੀ & XEL_TSR_XMIT_ਸਰਗਰਮ_ਨਕਾਬ) != 0) {

		/*
		 * Clear the Tx Active bit in the Tx Status Register.
		 */
		Tx_ਸਥਿਤੀ &= ~XEL_TSR_XMIT_ਸਰਗਰਮ_ਨਕਾਬ;
		XEmac_Lite_ਸੈੱਟ_Tx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ, Tx_ਸਥਿਤੀ);

		/*
		 * Update the flag indicating that there was a Tx Interrupt.
		 */
		TxCompleteIntr = TRUE;

	}

	Tx_ਸਥਿਤੀ = XEmac_Lite_Get_Tx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ + XEL_ਬਫਰ_ਵਿੱਥ);
	ਜੇ (((Tx_ਸਥਿਤੀ & XEL_TSR_XMIT_BUSY_ਨਕਾਬ) == 0) &&
		(Tx_ਸਥਿਤੀ & XEL_TSR_XMIT_ਸਰਗਰਮ_ਨਕਾਬ) != 0) {

		/*
		 * Clear the Tx Active bit in the Tx Status Register.
		 */
		Tx_ਸਥਿਤੀ &= ~XEL_TSR_XMIT_ਸਰਗਰਮ_ਨਕਾਬ;
		XEmac_Lite_ਸੈੱਟ_Tx_ਸਥਿਤੀ(ਅਧਾਰ_ਪਤਾ + XEL_ਬਫਰ_ਵਿੱਥ,
					Tx_ਸਥਿਤੀ);
		/*
		 * Update the flag indicating that there was a Tx Interrupt.
		 */
		TxCompleteIntr = TRUE;
	}

	/*
	 * If there was a TX interrupt, call the callback.
	 */
	ਜੇ (TxCompleteIntr == TRUE) {

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
ਖਾਲੀ XEmac_Lite_ਸੈੱਟ_Recv_Handler(XEmacLite *InstancePtr, ਖਾਲੀ *Call_ਪਿੱਠ_Ref,
			      XEmacLite_Handler FuncPtr)
{
	ਜੇ(ਨਿਰਾ == InstancePtr)
		ਵਾਪਸ -1;
	ਜੇ(ਨਿਰਾ == FuncPtr)
		ਵਾਪਸ -1;
	ਜੇ(InstancePtr->IsReady != XIL_COMPONENT_IS_READY)
		ਵਾਪਸ -1;

	InstancePtr->RecvHandler = FuncPtr;
	InstancePtr->RecvRef = Call_ਪਿੱਠ_Ref;
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
ਖਾਲੀ XEmac_Lite_ਸੈੱਟ_Send_Handler(XEmacLite *InstancePtr, ਖਾਲੀ *Call_ਪਿੱਠ_Ref,
			      XEmacLite_Handler FuncPtr)
{
	ਜੇ(ਨਿਰਾ == InstancePtr)
		ਵਾਪਸ -1;
	ਜੇ(ਨਿਰਾ == FuncPtr)
		ਵਾਪਸ -1;
	ਜੇ(InstancePtr->IsReady != XIL_COMPONENT_IS_READY)
		ਵਾਪਸ -1;

	InstancePtr->SendHandler = FuncPtr;
	InstancePtr->SendRef = Call_ਪਿੱਠ_Ref;
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
	u16 Phy_ਅੰਕੜੇ;
	ਪੂਰਨ PhyAddr;

	/*
	 * Verify all 32 MDIO ports.
	 */
	ਲਈ (PhyAddr = 31; PhyAddr >= 0; PhyAddr--) {
		XEmacLite_PhyRead(InstancePtr, PhyAddr, PHY_REG1_ਵਿੱਥ,
				 &Phy_ਅੰਕੜੇ);

		ਜੇ (Phy_ਅੰਕੜੇ != 0xFFFF) {
			ਜੇ ((Phy_ਅੰਕੜੇ & PHY_REG1_DETECT_ਨਕਾਬ) ==
			PHY_REG1_DETECT_ਨਕਾਬ) {
				ਵਾਪਸ PhyAddr;	/* Found a valid PHY device */
			}
		}
	}
	ਲਿਖੋ("\n Could not detect phy device");
	/*
	 * Unable to detect PHY device returning the default address of 0.
	 */
	ਵਾਪਸ 0;
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
ਪੂਰਨ Emac_Lite_Enable_Phy_Loop_ਪਿੱਠ(XEmacLite *InstancePtr, u32 Phy_ਪਤਾ)
{
	ਪੂਰਨ ਸਥਿਤੀ;
	u16 Phy_ਅੰਕੜੇ = 0;

	/*
	 * Set the speed and put the PHY in reset.
	 */
	Phy_ਅੰਕੜੇ |= PHY_REG0_SPD_100_ਨਕਾਬ;
	ਸਥਿਤੀ = XEmacLite_PhyWrite(InstancePtr, Phy_ਪਤਾ, PHY_REG0_ਵਿੱਥ,
			Phy_ਅੰਕੜੇ | PHY_REG0_RESET_ਨਕਾਬ);
	ਜੇ (ਸਥਿਤੀ != XST_SUCCESS) {
		ਵਾਪਸ XST_FAILURE;
	}

	/*
	 * Give sufficient delay for Phy Reset.
	 */
	EmacLitePhyDelay(EMACLITE_PHY_DELAY_SEC);

	/*
	 * Set the PHY in loop back.
	 */
	XEmacLite_PhyWrite(InstancePtr, Phy_ਪਤਾ, PHY_REG0_ਵਿੱਥ,
			Phy_ਅੰਕੜੇ | PHY_REG0_LOOPBACK_ਨਕਾਬ);
	ਜੇ (ਸਥਿਤੀ != XST_SUCCESS) {
		ਵਾਪਸ XST_FAILURE;
	}

	/*
	 * Give sufficient delay for Phy Loopback Enable.
	 */
	EmacLitePhyDelay(1);

	ਵਾਪਸ XST_SUCCESS;
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
ਪੂਰਨ Emac_Lite_Disable_Phy_Loop_ਪਿੱਠ(XEmacLite *InstancePtr, u32 Phy_ਪਤਾ)
{
	ਪੂਰਨ ਸਥਿਤੀ;
	u16 Phy_ਅੰਕੜੇ;

	/*
	 * Disable loop back through PHY register using MDIO support.
	 */
	ਸਥਿਤੀ = XEmacLite_PhyRead(InstancePtr, Phy_ਪਤਾ, PHY_REG0_ਵਿੱਥ,
					&Phy_ਅੰਕੜੇ);
	ਜੇ (ਸਥਿਤੀ != XST_SUCCESS) {
		ਵਾਪਸ XST_FAILURE;
	}

	ਸਥਿਤੀ = XEmacLite_PhyWrite(InstancePtr,Phy_ਪਤਾ, PHY_REG0_ਵਿੱਥ,
					Phy_ਅੰਕੜੇ & ~(PHY_REG0_LOOPBACK_ਨਕਾਬ));
	ਜੇ (ਸਥਿਤੀ != XST_SUCCESS) {
		ਵਾਪਸ XST_FAILURE;
	}

	ਵਾਪਸ XST_SUCCESS;

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
ਖਾਲੀ EmacLitePhyDelay(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ Seconds)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __MICROBLAZE__
	ਸਥਿਰ ਪੂਰਨ WarningFlag = 0;

	/* If MB caches are disabled or do not exist, this delay loop could
	 * take minutes instead of seconds (e.g., 30x longer).  Print a warning
	 * message for the user (once).  If only MB had a built-in timer!
	 */
	ਜੇ (((mfmsr() & 0x20) == 0) && (!WarningFlag)) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ STDOUT_BASEADDRESS
		xil_printf("Warning: This example will take ");
		xil_printf("minutes to complete without I-cache enabled \r\n");
#ਜੇ_ਅੰਤ
		WarningFlag = 1;
	}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ITERS_ਪ੍ਰਤੀ_SEC   (XPAR_CPU_CORE_CLOCK_FREQ_HZ / 6)
    asm ਅਸਥਿਰ ("\n"
                  "1:               \n\t"
                  "addik r7, r0, %0 \n\t"
                  "2:               \n\t"
                  "addik r7, r7, -1 \n\t"
                  "bneid  r7, 2b    \n\t"
                  "or  r0, r0, r0   \n\t"
                  "bneid %1, 1b     \n\t"
                  "addik %1, %1, -1 \n\t"
                  :: "i"(ITERS_ਪ੍ਰਤੀ_SEC), "d" (Seconds));

#ਨਹੀਂਤਾਂ

//	usleep(Seconds * 1000000);
//	waitfor(Seconds * 1000);
#ਜੇ_ਅੰਤ
}


