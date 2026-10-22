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
#تعریف_کرو ETH_VARI 1

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
متطاير u32 Recv_چوکھٹا_لمائی;
UINTPTR TxBuffPtr;
UINTPTR RxBuffPtr;
متطاير صحيح چوکھٹے_Tx;
متطاير صحيح چوکھٹے_Rx;
متطاير صحيح Tx_گنتی;
متطاير صحيح Rx_گنتی;
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
u8 Tx_چوکھٹا[XEL_MAX_چوکھٹا_ناپ];
u8 Rx_چوکھٹا[XEL_MAX_چوکھٹا_ناپ];

متطاير u32 Recv_چوکھٹا_لمائی;	/* Indicates the length of the Received packet
				 */
متطاير صحيح TransmitComplete;	/* Flag to indicate that the Transmission
				 * is complete
				 */


فراغ StubHandler(فراغ *Call_پٹھ_Ref);


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
	 XPAR_EMACLITE_0_INCLUDE_اندرونی_LOOPBACK
/* Include Internal  loop back support */
	 }
};



/************************** Function Prototypes ******************************/

ساكن u16 XEmac_Lite_Get_Receive_انکڑے_لمائی(UINTPTR ادھار_پتہ);

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
u16 Xil_EndianSwap16(u16 انکڑے)
{
	أرجع (u16) (((انکڑے & 0xFF00U) >> 8U) | ((انکڑے & 0x00FFU) << 8U));
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
u32 Xil_EndianSwap32(u32 انکڑے)
{
	u16 Lo_لفظ;
	u16 Hi_لفظ;

	/* get each of the half words from the 32 bit word */

	Lo_لفظ = (u16) (انکڑے & 0x0000FFFFU);
	Hi_لفظ = (u16) ((انکڑے & 0xFFFF0000U) >> 16U);

	/* byte swap each of the 16 bit half words */

	Lo_لفظ = (((Lo_لفظ & 0xFF00U) >> 8U) | ((Lo_لفظ & 0x00FFU) << 8U));
	Hi_لفظ = (((Hi_لفظ & 0xFF00U) >> 8U) | ((Hi_لفظ & 0x00FFU) << 8U));

	/* swap the half words before returning the value */

	أرجع ((((u32)Lo_لفظ) << (u32)16U) | (u32)Hi_لفظ);
}


/************************** Variable Definitions *****************************/



u16 Xil_Htons(u16 انکڑے)
{
	أرجع (u16) (((انکڑے & 0xFF00U) >> 8U) | ((انکڑے & 0x00FFU) << 8U));
}

u16 Xil_Ntohs(u16 انکڑے)
{
	أرجع (u16) (((انکڑے & 0xFF00U) >> 8U) | ((انکڑے & 0x00FFU) << 8U));
}


#إذا 0
#تعریف_کرو Xil_In16LE	Xil_In16
#تعریف_کرو Xil_In32LE	Xil_In32
#تعریف_کرو Xil_Out16LE	Xil_Out16
#تعریف_کرو Xil_Out32LE	Xil_Out32
#تعریف_کرو Xil_Htons	Xil_EndianSwap16
#تعریف_کرو Xil_Htonl	Xil_EndianSwap32
#تعریف_کرو Xil_Ntohs	Xil_EndianSwap16
#تعریف_کرو Xil_Ntohl	Xil_EndianSwap32
#جے_انت


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
#تعریف_کرو XEmacLite_ReadReg(ادھار_پتہ, Reg_وتھ) \
	XEmacLite_In32((ادھار_پتہ) + (Reg_وتھ))

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
#تعریف_کرو XEmacLite_WriteReg(ادھار_پتہ, Reg_وتھ, رجسٹر_قدر) \
	XEmacLite_Out32((ادھار_پتہ) + (Reg_وتھ), (رجسٹر_قدر))


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
#تعریف_کرو XEmac_Lite_Get_Tx_حالت(ادھار_پتہ)			\
	(XEmacLite_ReadReg((ادھار_پتہ), XEL_TSR_وتھ))


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
#تعریف_کرو XEmac_Lite_سیٹ_Tx_حالت(ادھار_پتہ, انکڑے)			\
	(XEmacLite_WriteReg((ادھار_پتہ), XEL_TSR_وتھ, (انکڑے)))


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
#تعریف_کرو XEmac_Lite_Get_Rx_حالت(ادھار_پتہ)			\
	(XEmacLite_ReadReg((ادھار_پتہ), XEL_RSR_وتھ))


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
#تعریف_کرو XEmac_Lite_سیٹ_Rx_حالت(ادھار_پتہ, انکڑے)			\
	(XEmacLite_WriteReg((ادھار_پتہ), XEL_RSR_وتھ, (انکڑے)))


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
#تعریف_کرو XEmac_Lite_Is_Tx_پورا(ادھار_پتہ)			\
		 ((XEmacLite_ReadReg((ادھار_پتہ), XEL_TSR_وتھ) & 	 \
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
#تعریف_کرو XEmac_Lite_Is_Rx_خالی_تھاواں(ادھار_پتہ) \
		  ((XEmacLite_ReadReg((ادھار_پتہ), XEL_RSR_وتھ) & \
			XEL_RSR_RECV_پورا_نقاب) != XEL_RSR_RECV_پورا_نقاب)

/************************** Function Prototypes ******************************/

فراغ XEmac_Lite_Send_چوکھٹا(UINTPTR ادھار_پتہ, u8 *چوکھٹا_Ptr, بنانشانی Byte_گنتی);
u16 XEmac_Lite_Recv_چوکھٹا(UINTPTR ادھار_پتہ, u8 *چوکھٹا_Ptr);

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
فراغ XEmac_Lite_Send_چوکھٹا(UINTPTR ادھار_پتہ, u8 *چوکھٹا_Ptr, بنانشانی Byte_گنتی)
{
	u32 رجسٹر;

	/*
	 * Write data to the EmacLite
	 */
	XEmacLite_AlignedWrite(چوکھٹا_Ptr, (UINTPTR *) (ادھار_پتہ), Byte_گنتی);

	/*
	 * The frame is in the buffer, now send it
	 */
	XEmacLite_WriteReg(ادھار_پتہ,  XEL_TPLR_وتھ,
				(Byte_گنتی & (XEL_TPLR_لمائی_نقاب_HI |
				XEL_TPLR_لمائی_نقاب_LO)));


	رجسٹر = XEmac_Lite_Get_Tx_حالت(ادھار_پتہ);
	XEmac_Lite_سیٹ_Tx_حالت(ادھار_پتہ, رجسٹر | XEL_TSR_XMIT_BUSY_نقاب);

	/*
	 * Loop on the status waiting for the transmit to be complete.
	 */
	طالما (!XEmac_Lite_Is_Tx_پورا(ادھار_پتہ));

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
u16 XEmac_Lite_Recv_چوکھٹا(UINTPTR ادھار_پتہ, u8 *چوکھٹا_Ptr)
{
	u16 لمائی_Type;
	u16 لمائی;
	u32 رجسٹر;

	/*
	 * Wait for a frame to arrive - this is a blocking call
	 */
	طالما (XEmac_Lite_Is_Rx_خالی_تھاواں(ادھار_پتہ));

	/*
	 * Get the length of the frame that arrived, only 32-bit reads are
	 * allowed LengthType is in the upper half of the 32-bit word.
	 */
	رجسٹر = XEmacLite_ReadReg(ادھار_پتہ, XEL_RPLR_وتھ);
	لمائی_Type = (u16) ((رجسٹر >> 16) &
			    (XEL_RPLR_لمائی_نقاب_HI |
			     XEL_RPLR_لمائی_نقاب_LO));

	/*
	 * Check if length is valid
	 */
	إذا (لمائی_Type > XEL_MAX_چوکھٹا_ناپ) {
		/*
		 * Field contain type, use max frame size and
		 * let user parse it
		 */
		لمائی = XEL_MAX_چوکھٹا_ناپ;
	}
	وإلا {
		/*
		 * Use the length in the frame, plus the header and trailer
		 */
		لمائی = لمائی_Type + XEL_سرخی_ناپ + XEL_FCS_ناپ;
	}

	/*
	 * Read each byte from the EmacLite
	 */
	XEmacLite_AlignedRead((UINTPTR *) (ادھار_پتہ + XEL_RXBUFF_وتھ),
			      چوکھٹا_Ptr, لمائی);

	/*
	 * Acknowledge the frame
	 */
	رجسٹر = XEmac_Lite_Get_Rx_حالت(ادھار_پتہ);
	رجسٹر &= ~XEL_RSR_RECV_پورا_نقاب;
	XEmac_Lite_سیٹ_Rx_حالت(ادھار_پتہ, رجسٹر);

	أرجع لمائی_Type;
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
فراغ XEmacLite_AlignedWrite(فراغ *SrcPtr, UINTPTR *DestPtr, بنانشانی Byte_گنتی)
{
	بنانشانی اشاریہ;
	بنانشانی لمائی = Byte_گنتی;
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
		log_info("length is %x", لمائی);
		log_info("\n Size of To32Ptr: %x", حجم(*To32Ptr));
		log_info("\n Size of From32Ptr: %x", حجم(*From32Ptr));
#جے_انت		
		طالما (لمائی > 3) {
			/*
			 * Output each word destination.
			 */
			*To32Ptr++ = *From32Ptr++;
#إذا 0
			*To32Ptr = *From32Ptr++;
			لکھو("\n Write value @ %x: %x", To32Ptr, *To32Ptr);
			*To32Ptr++;

//#else
			*To32Ptr = *From32Ptr;
			log_info("\n 1:[%x]; 2: [%x]", *To32Ptr, *From32Ptr);
			log_info("\n 1:[%x]; 2: [%x]", To32Ptr, From32Ptr);
			*To32Ptr++;
			*From32Ptr++;
			log_info("\n 1_2:[%x]; 2: [%x]", *To32Ptr, *From32Ptr);
			log_info("\n 1_2:[%x]; 2: [%x]", To32Ptr, From32Ptr);
#جے_انت
			/*
			 * Adjust length accordingly
			 */
			لمائی -= 4;
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

		طالما (لمائی > 3) {
			/*
			 * Copy each byte into the temporary buffer.
			 */
			لكل (اشاریہ = 0; اشاریہ < 4; اشاریہ++) {
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
			لمائی -= 4;
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

		طالما (لمائی > 3) {
			/*
			 * Copy each half word into the temporary buffer.
			 */
			لكل (اشاریہ = 0; اشاریہ < 2; اشاریہ++) {
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
			لمائی -= 4;
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
	لكل (اشاریہ = 0; اشاریہ < لمائی; اشاریہ++) {
		*To8Ptr++ = *From8Ptr++;
	}
	إذا (لمائی) {
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
فراغ XEmacLite_AlignedRead(UINTPTR *SrcPtr, فراغ *DestPtr, بنانشانی Byte_گنتی)
{
	بنانشانی اشاریہ;
	بنانشانی لمائی = Byte_گنتی;
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

		طالما (لمائی > 3) {
			/*
			 * Output each word.
			 */
			*To32Ptr++ = *From32Ptr++;

			/*
			 * Adjust length accordingly.
			 */
			لمائی -= 4;
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

		طالما (لمائی > 3) {
			/*
			 * Copy each word into the temporary buffer.
			 */
			Align_بفر = *From32Ptr++;
			From8Ptr = (u8 *) &Align_بفر;

			/*
			 * Write data to destination.
			 */
			لكل (اشاریہ = 0; اشاریہ < 4; اشاریہ++) {
				*To8Ptr++ = *From8Ptr++;
			}

			/*
			 * Adjust length
			 */
			لمائی -= 4;
		}

	}
	وإلا {
		/*
		 * Half-Word aligned buffer, correct.
		 */
		To16Ptr = (u16 *) DestPtr;

		طالما (لمائی > 3) {
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
			لكل (اشاریہ = 0; اشاریہ < 2; اشاریہ++) {
				*To16Ptr++ = *From16Ptr++;
			}

			/*
			 * Adjust length.
			 */
			لمائی -= 4;
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

	لكل (اشاریہ = 0; اشاریہ < لمائی; اشاریہ++) {
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
	InstancePtr->EmacLiteConfig.ادھار_پتہ = EffectiveAddr;
	InstancePtr->EmacLiteConfig.DeviceId = EmacLiteConfigPtr->DeviceId;
	InstancePtr->EmacLiteConfig.TxPingPong = EmacLiteConfigPtr->TxPingPong;
	InstancePtr->EmacLiteConfig.RxPingPong = EmacLiteConfigPtr->RxPingPong;
	InstancePtr->EmacLiteConfig.MdioInclude = EmacLiteConfigPtr->MdioInclude;
	InstancePtr->EmacLiteConfig.Loopback = EmacLiteConfigPtr->Loopback;

	InstancePtr->اگلا_Tx_بفر_منزل_Use = 0x0;
	InstancePtr->اگلا_Rx_بفر_منزل_Use = 0x0;
	InstancePtr->RecvHandler = (XEmacLite_Handler) StubHandler;
	InstancePtr->SendHandler = (XEmacLite_Handler) StubHandler;
	/*
	 * Clear the TX CSR's in case this is a restart.
	 */
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.ادھار_پتہ,
				XEL_TSR_وتھ, 0);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.ادھار_پتہ,
				XEL_بفر_وتھ + XEL_TSR_وتھ, 0);

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
صحيح XEmacLite_Send(XEmacLite *InstancePtr, u8 *چوکھٹا_Ptr, بنانشانی Byte_گنتی)
{
	u32 رجسٹر;
	UINTPTR ادھار_پتہ;
	UINTPTR Emac_ادھار_پتہ;
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
	ادھار_پتہ = XEmac_Lite_اگلا_Transmit_Addr(InstancePtr);
	Emac_ادھار_پتہ = InstancePtr->EmacLiteConfig.ادھار_پتہ;

	/*
	 * Check the Length if it is too large, truncate it.
	 * The maximum Tx packet size is
	 * Ethernet header (14 Bytes) + Maximum MTU (1500 bytes).
	 */
	إذا (Byte_گنتی > XEL_MAX_TX_چوکھٹا_ناپ) {

		Byte_گنتی = XEL_MAX_TX_چوکھٹا_ناپ;
	}

	/*
	 * Determine if the expected buffer address is empty.
	 */
	رجسٹر = XEmac_Lite_Get_Tx_حالت(ادھار_پتہ);

	/*
	 * If the expected buffer is available, fill it with the provided data
	 * Align if necessary.
	 */
	إذا ((رجسٹر & (XEL_TSR_XMIT_BUSY_نقاب |
			XEL_TSR_XMIT_سرگرم_نقاب)) == 0) {

		/*
		 * Switch to next buffer if configured.
		 */
		إذا (InstancePtr->EmacLiteConfig.TxPingPong != 0) {
			InstancePtr->اگلا_Tx_بفر_منزل_Use ^= XEL_بفر_وتھ;
		}

		/*
		 * Write the frame to the buffer.
		 */
		XEmacLite_AlignedWrite(چوکھٹا_Ptr, (UINTPTR *) ادھار_پتہ,
				       Byte_گنتی);


		/*
		 * The frame is in the buffer, now send it.
		 */
		XEmacLite_WriteReg(ادھار_پتہ, XEL_TPLR_وتھ,
					(Byte_گنتی & (XEL_TPLR_لمائی_نقاب_HI |
					XEL_TPLR_لمائی_نقاب_LO)));

		/*
		 * Update the Tx Status Register to indicate that there is a
		 * frame to send.
		 * If the interrupt enable bit of Ping buffer(since this
		 * controls both the buffers) is enabled then set the
		 * XEL_TSR_XMIT_ACTIVE_MASK flag which is used by the interrupt
		 * handler to call the callback function provided by the user
		 * to indicate that the frame has been transmitted.
		 */
		رجسٹر = XEmac_Lite_Get_Tx_حالت(ادھار_پتہ);
		رجسٹر |= XEL_TSR_XMIT_BUSY_نقاب;
		Intr_Enable_حالت = XEmac_Lite_Get_Tx_حالت(Emac_ادھار_پتہ);
		إذا ((Intr_Enable_حالت & XEL_TSR_XMIT_IE_نقاب) != 0) {
			رجسٹر |= XEL_TSR_XMIT_سرگرم_نقاب;
		}
		XEmac_Lite_سیٹ_Tx_حالت(ادھار_پتہ, رجسٹر);

		أرجع SUCCESS;
	}

	/*
	 * If the expected buffer was full, try the other buffer if configured.
	 */
	إذا (InstancePtr->EmacLiteConfig.TxPingPong != 0) {

		ادھار_پتہ ^= XEL_بفر_وتھ;

		/*
		 * Determine if the expected buffer address is empty.
		 */
		رجسٹر = XEmac_Lite_Get_Tx_حالت(ادھار_پتہ);

		/*
		 * If the next buffer is available, fill it with the provided
		 * data.
		 */
		إذا ((رجسٹر & (XEL_TSR_XMIT_BUSY_نقاب |
				XEL_TSR_XMIT_سرگرم_نقاب)) == 0) {

			/*
			 * Write the frame to the buffer.
			 */
			XEmacLite_AlignedWrite(چوکھٹا_Ptr, (UINTPTR *) ادھار_پتہ,
					       Byte_گنتی);

			/*
			 * The frame is in the buffer, now send it.
			 */
			XEmacLite_WriteReg(ادھار_پتہ, XEL_TPLR_وتھ,
					(Byte_گنتی & (XEL_TPLR_لمائی_نقاب_HI |
					   XEL_TPLR_لمائی_نقاب_LO)));

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
			رجسٹر = XEmac_Lite_Get_Tx_حالت(ادھار_پتہ);
			رجسٹر |= XEL_TSR_XMIT_BUSY_نقاب;
			Intr_Enable_حالت =
					XEmac_Lite_Get_Tx_حالت(Emac_ادھار_پتہ);
			إذا ((Intr_Enable_حالت & XEL_TSR_XMIT_IE_نقاب) != 0) {
				رجسٹر |= XEL_TSR_XMIT_سرگرم_نقاب;
			}
			XEmac_Lite_سیٹ_Tx_حالت(ادھار_پتہ, رجسٹر);

			/*
			 * Do not switch to next buffer, there is a sync problem
			 * and the expected buffer should not change.
			 */
			أرجع SUCCESS;
		}
	}

	لکھو("\n Error in sending the packet");
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
u16 XEmacLite_Recv(XEmacLite *InstancePtr, u8 *چوکھٹا_Ptr)
{
	u16 لمائی_Type;
	u16 لمائی;
	u32 رجسٹر;
	UINTPTR ادھار_پتہ;

	/*
	 * Verify that each of the inputs are valid.
	 */

	إذا (InstancePtr == عدم) {
		أرجع -1;
	}

	/*
	 * Determine the expected buffer address.
	 */
	ادھار_پتہ = XEmac_Lite_اگلا_Receive_Addr(InstancePtr);

	/*
	 * Verify which buffer has valid data.
	 */
	رجسٹر = XEmac_Lite_Get_Rx_حالت(ادھار_پتہ);

	إذا ((رجسٹر & XEL_RSR_RECV_پورا_نقاب) == XEL_RSR_RECV_پورا_نقاب) {

		/*
		 * The driver is in sync, update the next expected buffer if
		 * configured.
		 */

		إذا (InstancePtr->EmacLiteConfig.RxPingPong != 0) {
			InstancePtr->اگلا_Rx_بفر_منزل_Use ^= XEL_بفر_وتھ;
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
			ادھار_پتہ ^= XEL_بفر_وتھ;
		}
		وإلا {
			أرجع 0;	/* No data was available */
		}

		/*
		 * Verify that buffer has valid data.
		 */
		رجسٹر = XEmac_Lite_Get_Rx_حالت(ادھار_پتہ);
		إذا ((رجسٹر & XEL_RSR_RECV_پورا_نقاب) !=
				XEL_RSR_RECV_پورا_نقاب) {
			أرجع 0;	/* No data was available */
		}
	}

	/*
	 * Get the length of the frame that arrived.
	 */
	لمائی_Type = XEmac_Lite_Get_Receive_انکڑے_لمائی(ادھار_پتہ);

	/*
	 * Check if length is valid.
	 */
	إذا (لمائی_Type > XEL_MAX_چوکھٹا_ناپ) {


		إذا (لمائی_Type == XEL_ETHER_PROTO_TYPE_IP) {

			/*
			 * The packet is a an IP Packet.
			 */
#جے_تعریف_شدہ __LITTLE_ENDIAN__
			لمائی = (XEmacLite_ReadReg((ادھار_پتہ),
					XEL_سرخی_IP_لمائی_وتھ +
					XEL_RXBUFF_وتھ) &
					(XEL_RPLR_لمائی_نقاب_HI |
					XEL_RPLR_لمائی_نقاب_LO));
			لمائی = (u16) (((لمائی & 0xFF00) >> 8) | ((لمائی & 0x00FF) << 8));
#وإلا
			لمائی = ((XEmacLite_ReadReg((ادھار_پتہ),
					XEL_سرخی_IP_لمائی_وتھ +
					XEL_RXBUFF_وتھ) >>
					XEL_سرخی_کھسکاؤ) &
					(XEL_RPLR_لمائی_نقاب_HI |
					XEL_RPLR_لمائی_نقاب_LO));
#جے_انت

//			Length += XEL_HEADER_SIZE + XEL_FCS_SIZE;
			لمائی += XEL_سرخی_ناپ;
//			printf("\n Length1 is %x", Length);

		} وإلا إذا (لمائی_Type == XEL_ETHER_PROTO_TYPE_ARP) {

			/*
			 * The packet is an ARP Packet.
			 */
			لمائی = XEL_ARP_PACKET_ناپ + XEL_سرخی_ناپ +
					XEL_FCS_ناپ;

		} وإلا {
			/*
			 * Field contains type other than IP or ARP, use max
			 * frame size and let user parse it.
			 */
			لمائی = XEL_MAX_چوکھٹا_ناپ;

		}
	} وإلا {

		/*
		 * Use the length in the frame, plus the header and trailer.
		 */
		لمائی = لمائی_Type + XEL_سرخی_ناپ + XEL_FCS_ناپ;
	}

	/*
	 * Read from the EmacLite.
	 */
	XEmacLite_AlignedRead(((UINTPTR *) (ادھار_پتہ + XEL_RXBUFF_وتھ)),
			      چوکھٹا_Ptr, لمائی);

	/*
	 * Acknowledge the frame.
	 */
	رجسٹر = XEmac_Lite_Get_Rx_حالت(ادھار_پتہ);
	رجسٹر &= ~XEL_RSR_RECV_پورا_نقاب;
	XEmac_Lite_سیٹ_Rx_حالت(ادھار_پتہ, رجسٹر);

	أرجع لمائی;
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
فراغ XEmac_Lite_سیٹ_Mac_پتہ(XEmacLite *InstancePtr, u8 *پتہ_Ptr)
{
	UINTPTR ادھار_پتہ;

	/*
	 * Verify that each of the inputs are valid.
	 */
	إذا (InstancePtr == عدم) {
		أرجع -1;
	}

	/*
	 * Determine the expected TX buffer address.
	 */
	ادھار_پتہ = XEmac_Lite_اگلا_Transmit_Addr(InstancePtr);

	/*
	 * Copy the MAC address to the Transmit buffer.
	 */
	XEmacLite_AlignedWrite(پتہ_Ptr,
				(UINTPTR *) ادھار_پتہ,
				XEL_MAC_ADDR_ناپ);

	/*
	 * Set the length.
	 */
	XEmacLite_WriteReg(ادھار_پتہ,
				XEL_TPLR_وتھ,
				XEL_MAC_ADDR_ناپ);

	/*
	 * Update the MAC address in the EmacLite.
	 */
	XEmac_Lite_سیٹ_Tx_حالت(ادھار_پتہ, XEL_TSR_PROG_MAC_ADDR);


	/*
	 * Wait for EmacLite to finish with the MAC address update.
	 */
	طالما ((XEmac_Lite_Get_Tx_حالت(ادھار_پتہ) &
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
فراغ StubHandler(فراغ *Call_پٹھ_Ref)
{
	(فراغ)(Call_پٹھ_Ref);
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
صحيح XEmac_Lite_Tx_بفر_دستیاب(XEmacLite *InstancePtr)
{

	u32 رجسٹر;
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
	رجسٹر = XEmac_Lite_Get_Tx_حالت(InstancePtr->EmacLiteConfig.
						ادھار_پتہ);

	TxPingBusy = (رجسٹر & (XEL_TSR_XMIT_BUSY_نقاب |
				 XEL_TSR_XMIT_سرگرم_نقاب));


	/*
	 * Read the Tx Status of the second buffer register and determine if the
	 * buffer is available.
	 */
	إذا (InstancePtr->EmacLiteConfig.TxPingPong != 0) {
		رجسٹر = XEmac_Lite_Get_Tx_حالت(InstancePtr->EmacLiteConfig.
						ادھار_پتہ +
						XEL_بفر_وتھ);

		TxPongBusy = (رجسٹر & (XEL_TSR_XMIT_BUSY_نقاب |
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

	u32 رجسٹر;

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
	رجسٹر = XEmac_Lite_Get_Rx_حالت(InstancePtr->EmacLiteConfig.
						ادھار_پتہ);

	/*
	 * Preserve the IE bit.
	 */
	رجسٹر &= XEL_RSR_RECV_IE_نقاب;

	/*
	 * Write out the value to flush the RX buffer.
	 */
	XEmac_Lite_سیٹ_Rx_حالت(InstancePtr->EmacLiteConfig.ادھار_پتہ,
				رجسٹر);

	/*
	 * If the pong buffer is available, flush it also.
	 */
	إذا (InstancePtr->EmacLiteConfig.RxPingPong != 0) {
		/*
		 * Read the current buffer register and determine if the buffer
		 * is available.
		 */
		رجسٹر = XEmac_Lite_Get_Rx_حالت(InstancePtr->EmacLiteConfig.
							ادھار_پتہ +
							XEL_بفر_وتھ);

		/*
		 * Preserve the IE bit.
		 */
		رجسٹر &= XEL_RSR_RECV_IE_نقاب;

		/*
		 * Write out the value to flush the RX buffer.
		 */
		XEmac_Lite_سیٹ_Rx_حالت(InstancePtr->EmacLiteConfig.ادھار_پتہ +
					XEL_بفر_وتھ, رجسٹر);

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
صحيح XEmacLite_PhyRead(XEmacLite *InstancePtr, u32 Phy_پتہ, u32 Reg_عدد,
			u16 *Phy_انکڑے_Ptr)
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
		إذا (Phy_پتہ <= 31) {
			أرجع -1;
		}
		إذا (Reg_عدد <= 31) {
			أرجع -1;
		}

	إذا (Phy_انکڑے_Ptr == عدم) {
		أرجع -1;
	}

	/*
	 * Verify MDIO master status.
	 */
	إذا (XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.ادھار_پتہ,
				XEL_MDIOCNTR_وتھ) &
				XEL_MDIOCNTR_حالت_نقاب) {
		أرجع DEVICE_BUSY;
	}

	PhyAddrReg = ((((Phy_پتہ << XEL_MDIO_پتہ_کھسکاؤ) &
			XEL_MDIO_پتہ_نقاب) | Reg_عدد) | XEL_MDIO_OP_نقاب);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.ادھار_پتہ,
				 XEL_MDIOADDR_وتھ, PhyAddrReg);

	/*
	 * Enable MDIO and start the transfer.
	 */
	MdioCtrlReg =
		XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.ادھار_پتہ,
					XEL_MDIOCNTR_وتھ);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.ادھار_پتہ,
				XEL_MDIOCNTR_وتھ,
				MdioCtrlReg |
				XEL_MDIOCNTR_حالت_نقاب |
				XEL_MDIOCNTR_ENABLE_نقاب);

	/*
	 * Wait till the completion of transfer.
	 */
	طالما ((XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.ادھار_پتہ,
				XEL_MDIOCNTR_وتھ) &
				XEL_MDIOCNTR_حالت_نقاب));

	/*
	 * Read data from MDIO read data register.
	 */
	*Phy_انکڑے_Ptr = (u16)XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.ادھار_پتہ,
					XEL_MDIORD_وتھ);

	/*
	 * Disable the MDIO.
	 */
	MdioCtrlReg =
		XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.ادھار_پتہ,
					XEL_MDIOCNTR_وتھ);

	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.ادھار_پتہ,
				XEL_MDIOCNTR_وتھ,
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
صحيح XEmacLite_PhyWrite(XEmacLite *InstancePtr, u32 Phy_پتہ, u32 Reg_عدد,
			u16 Phy_انکڑے)
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
	إذا (Phy_پتہ <= 31) {
		أرجع -1;
	}
	إذا (Reg_عدد <= 31) {
		أرجع -1;
	}

	/*
	 * Verify MDIO master status.
	 */
	إذا (XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.ادھار_پتہ,
				XEL_MDIOCNTR_وتھ) &
				XEL_MDIOCNTR_حالت_نقاب) {
		أرجع DEVICE_BUSY;
	}



	PhyAddrReg = ((((Phy_پتہ << XEL_MDIO_پتہ_کھسکاؤ) &
			XEL_MDIO_پتہ_نقاب) | Reg_عدد) & ~XEL_MDIO_OP_نقاب);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.ادھار_پتہ,
				XEL_MDIOADDR_وتھ, PhyAddrReg);

	/*
	 * Write data to MDIO write data register.
	 */
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.ادھار_پتہ,
				XEL_MDIOWR_وتھ, (u32)Phy_انکڑے);

	/*
	 * Enable MDIO and start the transfer.
	 */
	MdioCtrlReg =
		XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.ادھار_پتہ,
					XEL_MDIOCNTR_وتھ);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.ادھار_پتہ,
				XEL_MDIOCNTR_وتھ,
				MdioCtrlReg | XEL_MDIOCNTR_حالت_نقاب |
				XEL_MDIOCNTR_ENABLE_نقاب);

	/*
	 * Wait till the completion of transfer.
	 */
	طالما ((XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.ادھار_پتہ,
				XEL_MDIOCNTR_وتھ) & XEL_MDIOCNTR_حالت_نقاب));


	/*
	 * Disable the MDIO.
	 */
	MdioCtrlReg =
		XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.ادھار_پتہ,
					XEL_MDIOCNTR_وتھ);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.ادھار_پتہ,
				XEL_MDIOCNTR_وتھ,
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
فراغ XEmac_Lite_Enable_Loop_پٹھ(XEmacLite *InstancePtr)
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

	TsrReg = XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.ادھار_پتہ,
					XEL_TSR_وتھ);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.ادھار_پتہ,
			XEL_TSR_وتھ,	TsrReg | XEL_TSR_LOOPBACK_نقاب);
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
فراغ XEmac_Lite_Disable_Loop_پٹھ(XEmacLite *InstancePtr)
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

	TsrReg = XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.ادھار_پتہ,
					XEL_TSR_وتھ);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.ادھار_پتہ,
			XEL_TSR_وتھ,	TsrReg & (~XEL_TSR_LOOPBACK_نقاب));
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
ساكن u16 XEmac_Lite_Get_Receive_انکڑے_لمائی(UINTPTR ادھار_پتہ)
{
	u16 لمائی;

#جے_تعریف_شدہ __LITTLE_ENDIAN__
	لمائی = (XEmacLite_ReadReg((ادھار_پتہ),
			XEL_سرخی_وتھ + XEL_RXBUFF_وتھ) &
			(XEL_RPLR_لمائی_نقاب_HI | XEL_RPLR_لمائی_نقاب_LO));
	لمائی = (u16) (((لمائی & 0xFF00) >> 8) | ((لمائی & 0x00FF) << 8));
#وإلا
	لمائی = ((XEmacLite_ReadReg((ادھار_پتہ),
			XEL_سرخی_وتھ + XEL_RXBUFF_وتھ) >>
			XEL_سرخی_کھسکاؤ) &
			(XEL_RPLR_لمائی_نقاب_HI | XEL_RPLR_لمائی_نقاب_LO));
#جے_انت

	أرجع لمائی;
}

صحيح XEmacLite_EnableInterrupts(XEmacLite *InstancePtr)
{
	u32 رجسٹر;
	UINTPTR ادھار_پتہ;

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
	رجسٹر = XEmac_Lite_Get_Tx_حالت(ادھار_پتہ);
	رجسٹر |= XEL_TSR_XMIT_IE_نقاب;
	XEmac_Lite_سیٹ_Tx_حالت(ادھار_پتہ, رجسٹر);

	/*
	 * Enable the RX interrupts for both the buffers, the Interrupt Enable
	 * is common for the both the buffers and is defined in the
	 * Ping buffer.
	 */
	رجسٹر = XEmac_Lite_Get_Rx_حالت(ادھار_پتہ);
	رجسٹر |= XEL_RSR_RECV_IE_نقاب;
	XEmac_Lite_سیٹ_Rx_حالت(ادھار_پتہ, رجسٹر);

	/*
	 * Enable the global interrupt output.
	 */
	XEmacLite_WriteReg(ادھار_پتہ, XEL_GIER_وتھ, XEL_GIER_GIE_نقاب);

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
	u32 رجسٹر;
	UINTPTR ادھار_پتہ;

	/*
	 * Verify that each of the inputs are valid.
	 */
		إذا(عدم == InstancePtr)
			أرجع -1;
		إذا(InstancePtr->IsReady != XIL_COMPONENT_IS_READY)
			أرجع -1;


	ادھار_پتہ = InstancePtr->EmacLiteConfig.ادھار_پتہ;

	/*
	 * Disable the global interrupt output.
	 */
	XEmacLite_WriteReg(ادھار_پتہ, XEL_GIER_وتھ, 0);

	/*
	 * Disable the TX interrupts for both the buffers, the Interrupt Enable
	 * is common for the both the buffers and is defined in the
	 * Ping buffer.
	 */
	رجسٹر = XEmac_Lite_Get_Tx_حالت(ادھار_پتہ);
	رجسٹر &= ~XEL_TSR_XMIT_IE_نقاب;
	XEmac_Lite_سیٹ_Tx_حالت(ادھار_پتہ, رجسٹر);

	/*
	 * Disable the RX interrupts for both the buffers, the Interrupt Enable
	 * is common for the both the buffers and is defined in the
	 * Ping buffer.
	 */
	رجسٹر = XEmac_Lite_Get_Rx_حالت(ادھار_پتہ);
	رجسٹر &= ~XEL_RSR_RECV_IE_نقاب;
	XEmac_Lite_سیٹ_Rx_حالت(ادھار_پتہ, رجسٹر);

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
فراغ XEmac_Lite_رکاوٹ_Handler(فراغ *InstancePtr)
{

	XEmacLite *EmacLitePtr;
	صحيح TxCompleteIntr = FALSE;
	UINTPTR ادھار_پتہ;
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
	ادھار_پتہ = EmacLitePtr->EmacLiteConfig.ادھار_پتہ;

	إذا ((XEmac_Lite_Is_Rx_خالی_تھاواں(ادھار_پتہ) != TRUE) ||
		(XEmac_Lite_Is_Rx_خالی_تھاواں(ادھار_پتہ +
			XEL_بفر_وتھ) != TRUE)) {
		/*
		 * Call the RX callback.
		 */
		EmacLitePtr->RecvHandler(EmacLitePtr->RecvRef);

	}

	Tx_حالت = XEmac_Lite_Get_Tx_حالت(ادھار_پتہ);
	إذا (((Tx_حالت & XEL_TSR_XMIT_BUSY_نقاب) == 0) &&
		(Tx_حالت & XEL_TSR_XMIT_سرگرم_نقاب) != 0) {

		/*
		 * Clear the Tx Active bit in the Tx Status Register.
		 */
		Tx_حالت &= ~XEL_TSR_XMIT_سرگرم_نقاب;
		XEmac_Lite_سیٹ_Tx_حالت(ادھار_پتہ, Tx_حالت);

		/*
		 * Update the flag indicating that there was a Tx Interrupt.
		 */
		TxCompleteIntr = TRUE;

	}

	Tx_حالت = XEmac_Lite_Get_Tx_حالت(ادھار_پتہ + XEL_بفر_وتھ);
	إذا (((Tx_حالت & XEL_TSR_XMIT_BUSY_نقاب) == 0) &&
		(Tx_حالت & XEL_TSR_XMIT_سرگرم_نقاب) != 0) {

		/*
		 * Clear the Tx Active bit in the Tx Status Register.
		 */
		Tx_حالت &= ~XEL_TSR_XMIT_سرگرم_نقاب;
		XEmac_Lite_سیٹ_Tx_حالت(ادھار_پتہ + XEL_بفر_وتھ,
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
فراغ XEmac_Lite_سیٹ_Recv_Handler(XEmacLite *InstancePtr, فراغ *Call_پٹھ_Ref,
			      XEmacLite_Handler FuncPtr)
{
	إذا(عدم == InstancePtr)
		أرجع -1;
	إذا(عدم == FuncPtr)
		أرجع -1;
	إذا(InstancePtr->IsReady != XIL_COMPONENT_IS_READY)
		أرجع -1;

	InstancePtr->RecvHandler = FuncPtr;
	InstancePtr->RecvRef = Call_پٹھ_Ref;
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
فراغ XEmac_Lite_سیٹ_Send_Handler(XEmacLite *InstancePtr, فراغ *Call_پٹھ_Ref,
			      XEmacLite_Handler FuncPtr)
{
	إذا(عدم == InstancePtr)
		أرجع -1;
	إذا(عدم == FuncPtr)
		أرجع -1;
	إذا(InstancePtr->IsReady != XIL_COMPONENT_IS_READY)
		أرجع -1;

	InstancePtr->SendHandler = FuncPtr;
	InstancePtr->SendRef = Call_پٹھ_Ref;
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
	u16 Phy_انکڑے;
	صحيح PhyAddr;

	/*
	 * Verify all 32 MDIO ports.
	 */
	لكل (PhyAddr = 31; PhyAddr >= 0; PhyAddr--) {
		XEmacLite_PhyRead(InstancePtr, PhyAddr, PHY_REG1_وتھ,
				 &Phy_انکڑے);

		إذا (Phy_انکڑے != 0xFFFF) {
			إذا ((Phy_انکڑے & PHY_REG1_DETECT_نقاب) ==
			PHY_REG1_DETECT_نقاب) {
				أرجع PhyAddr;	/* Found a valid PHY device */
			}
		}
	}
	لکھو("\n Could not detect phy device");
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
صحيح Emac_Lite_Enable_Phy_Loop_پٹھ(XEmacLite *InstancePtr, u32 Phy_پتہ)
{
	صحيح حالت;
	u16 Phy_انکڑے = 0;

	/*
	 * Set the speed and put the PHY in reset.
	 */
	Phy_انکڑے |= PHY_REG0_SPD_100_نقاب;
	حالت = XEmacLite_PhyWrite(InstancePtr, Phy_پتہ, PHY_REG0_وتھ,
			Phy_انکڑے | PHY_REG0_RESET_نقاب);
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
	XEmacLite_PhyWrite(InstancePtr, Phy_پتہ, PHY_REG0_وتھ,
			Phy_انکڑے | PHY_REG0_LOOPBACK_نقاب);
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
صحيح Emac_Lite_Disable_Phy_Loop_پٹھ(XEmacLite *InstancePtr, u32 Phy_پتہ)
{
	صحيح حالت;
	u16 Phy_انکڑے;

	/*
	 * Disable loop back through PHY register using MDIO support.
	 */
	حالت = XEmacLite_PhyRead(InstancePtr, Phy_پتہ, PHY_REG0_وتھ,
					&Phy_انکڑے);
	إذا (حالت != XST_SUCCESS) {
		أرجع XST_FAILURE;
	}

	حالت = XEmacLite_PhyWrite(InstancePtr,Phy_پتہ, PHY_REG0_وتھ,
					Phy_انکڑے & ~(PHY_REG0_LOOPBACK_نقاب));
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
فراغ EmacLitePhyDelay(بنانشانی صحيح Seconds)
{
#جے_تعریف_شدہ __MICROBLAZE__
	ساكن صحيح WarningFlag = 0;

	/* If MB caches are disabled or do not exist, this delay loop could
	 * take minutes instead of seconds (e.g., 30x longer).  Print a warning
	 * message for the user (once).  If only MB had a built-in timer!
	 */
	إذا (((mfmsr() & 0x20) == 0) && (!WarningFlag)) {
#جے_تعریف_شدہ STDOUT_BASEADDRESS
		xil_printf("Warning: This example will take ");
		xil_printf("minutes to complete without I-cache enabled \r\n");
#جے_انت
		WarningFlag = 1;
	}

#تعریف_کرو ITERS_فی_SEC   (XPAR_CPU_CORE_CLOCK_FREQ_HZ / 6)
    asm متطاير ("\n"
                  "1:               \n\t"
                  "addik r7, r0, %0 \n\t"
                  "2:               \n\t"
                  "addik r7, r7, -1 \n\t"
                  "bneid  r7, 2b    \n\t"
                  "or  r0, r0, r0   \n\t"
                  "bneid %1, 1b     \n\t"
                  "addik %1, %1, -1 \n\t"
                  :: "i"(ITERS_فی_SEC), "d" (Seconds));

#وإلا

//	usleep(Seconds * 1000000);
//	waitfor(Seconds * 1000);
#جے_انت
}


