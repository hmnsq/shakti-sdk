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
#تعریف_کن ETH_VARI 1

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
متطاير u32 Recv_قاب_درازی;
UINTPTR TxBuffPtr;
UINTPTR RxBuffPtr;
متطاير صحيح قابها_Tx;
متطاير صحيح قابها_Rx;
متطاير صحيح Tx_شمار;
متطاير صحيح Rx_شمار;
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
u8 Tx_قاب[XEL_MAX_قاب_اندازه];
u8 Rx_قاب[XEL_MAX_قاب_اندازه];

متطاير u32 Recv_قاب_درازی;	/* Indicates the length of the Received packet
				 */
متطاير صحيح TransmitComplete;	/* Flag to indicate that the Transmission
				 * is complete
				 */


فراغ StubHandler(فراغ *Call_پشت_Ref);


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
	 XPAR_EMACLITE_0_INCLUDE_داخلی_LOOPBACK
/* Include Internal  loop back support */
	 }
};



/************************** Function Prototypes ******************************/

ساكن u16 XEmac_Lite_Get_Receive_داده_درازی(UINTPTR پایه_آدرس);

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
ساكن INLINE فراغ Xil_Out8(UINTPTR Addr, u8 مقدار_2)
{
	متطاير u8 *LocalAddr = (متطاير u8 *)Addr;
	*LocalAddr = مقدار_2;
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
ساكن INLINE فراغ Xil_Out16(UINTPTR Addr, u16 مقدار_2)
{
	متطاير u16 *LocalAddr = (متطاير u16 *)Addr;
	*LocalAddr = مقدار_2;
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
ساكن INLINE فراغ Xil_Out32(UINTPTR Addr, u32 مقدار_2)
{
	متطاير u32 *LocalAddr = (متطاير u32 *)Addr;
	*LocalAddr = مقدار_2;
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
ساكن INLINE فراغ Xil_Out64(UINTPTR Addr, u64 مقدار_2)
{
	متطاير u64 *LocalAddr = (متطاير u64 *)Addr;
	*LocalAddr = مقدار_2;
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
u16 Xil_EndianSwap16(u16 داده)
{
	أرجع (u16) (((داده & 0xFF00U) >> 8U) | ((داده & 0x00FFU) << 8U));
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
u32 Xil_EndianSwap32(u32 داده)
{
	u16 Lo_کلمه;
	u16 Hi_کلمه;

	/* get each of the half words from the 32 bit word */

	Lo_کلمه = (u16) (داده & 0x0000FFFFU);
	Hi_کلمه = (u16) ((داده & 0xFFFF0000U) >> 16U);

	/* byte swap each of the 16 bit half words */

	Lo_کلمه = (((Lo_کلمه & 0xFF00U) >> 8U) | ((Lo_کلمه & 0x00FFU) << 8U));
	Hi_کلمه = (((Hi_کلمه & 0xFF00U) >> 8U) | ((Hi_کلمه & 0x00FFU) << 8U));

	/* swap the half words before returning the value */

	أرجع ((((u32)Lo_کلمه) << (u32)16U) | (u32)Hi_کلمه);
}


/************************** Variable Definitions *****************************/



u16 Xil_Htons(u16 داده)
{
	أرجع (u16) (((داده & 0xFF00U) >> 8U) | ((داده & 0x00FFU) << 8U));
}

u16 Xil_Ntohs(u16 داده)
{
	أرجع (u16) (((داده & 0xFF00U) >> 8U) | ((داده & 0x00FFU) << 8U));
}


#إذا 0
#تعریف_کن Xil_In16LE	Xil_In16
#تعریف_کن Xil_In32LE	Xil_In32
#تعریف_کن Xil_Out16LE	Xil_Out16
#تعریف_کن Xil_Out32LE	Xil_Out32
#تعریف_کن Xil_Htons	Xil_EndianSwap16
#تعریف_کن Xil_Htonl	Xil_EndianSwap32
#تعریف_کن Xil_Ntohs	Xil_EndianSwap16
#تعریف_کن Xil_Ntohl	Xil_EndianSwap32
#پایان_اگر


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
#تعریف_کن XEmacLite_ReadReg(پایه_آدرس, Reg_جابه_جایی) \
	XEmacLite_In32((پایه_آدرس) + (Reg_جابه_جایی))

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
#تعریف_کن XEmacLite_WriteReg(پایه_آدرس, Reg_جابه_جایی, ثبات_مقدار) \
	XEmacLite_Out32((پایه_آدرس) + (Reg_جابه_جایی), (ثبات_مقدار))


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
#تعریف_کن XEmac_Lite_Get_Tx_وضعیت(پایه_آدرس)			\
	(XEmacLite_ReadReg((پایه_آدرس), XEL_TSR_جابه_جایی))


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
#تعریف_کن XEmac_Lite_مجموعه_Tx_وضعیت(پایه_آدرس, داده)			\
	(XEmacLite_WriteReg((پایه_آدرس), XEL_TSR_جابه_جایی, (داده)))


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
#تعریف_کن XEmac_Lite_Get_Rx_وضعیت(پایه_آدرس)			\
	(XEmacLite_ReadReg((پایه_آدرس), XEL_RSR_جابه_جایی))


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
#تعریف_کن XEmac_Lite_مجموعه_Rx_وضعیت(پایه_آدرس, داده)			\
	(XEmacLite_WriteReg((پایه_آدرس), XEL_RSR_جابه_جایی, (داده)))


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
#تعریف_کن XEmac_Lite_Is_Tx_انجامشده(پایه_آدرس)			\
		 ((XEmacLite_ReadReg((پایه_آدرس), XEL_TSR_جابه_جایی) & 	 \
			 XEL_TSR_XMIT_BUSY_ماسک) != XEL_TSR_XMIT_BUSY_ماسک)


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
#تعریف_کن XEmac_Lite_Is_Rx_خالی(پایه_آدرس) \
		  ((XEmacLite_ReadReg((پایه_آدرس), XEL_RSR_جابه_جایی) & \
			XEL_RSR_RECV_انجامشده_ماسک) != XEL_RSR_RECV_انجامشده_ماسک)

/************************** Function Prototypes ******************************/

فراغ XEmac_Lite_Send_قاب(UINTPTR پایه_آدرس, u8 *قاب_Ptr, بیعلامت Byte_شمار);
u16 XEmac_Lite_Recv_قاب(UINTPTR پایه_آدرس, u8 *قاب_Ptr);

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
فراغ XEmac_Lite_Send_قاب(UINTPTR پایه_آدرس, u8 *قاب_Ptr, بیعلامت Byte_شمار)
{
	u32 ثبات;

	/*
	 * Write data to the EmacLite
	 */
	XEmacLite_AlignedWrite(قاب_Ptr, (UINTPTR *) (پایه_آدرس), Byte_شمار);

	/*
	 * The frame is in the buffer, now send it
	 */
	XEmacLite_WriteReg(پایه_آدرس,  XEL_TPLR_جابه_جایی,
				(Byte_شمار & (XEL_TPLR_درازی_ماسک_HI |
				XEL_TPLR_درازی_ماسک_LO)));


	ثبات = XEmac_Lite_Get_Tx_وضعیت(پایه_آدرس);
	XEmac_Lite_مجموعه_Tx_وضعیت(پایه_آدرس, ثبات | XEL_TSR_XMIT_BUSY_ماسک);

	/*
	 * Loop on the status waiting for the transmit to be complete.
	 */
	طالما (!XEmac_Lite_Is_Tx_انجامشده(پایه_آدرس));

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
u16 XEmac_Lite_Recv_قاب(UINTPTR پایه_آدرس, u8 *قاب_Ptr)
{
	u16 درازی_Type;
	u16 درازی;
	u32 ثبات;

	/*
	 * Wait for a frame to arrive - this is a blocking call
	 */
	طالما (XEmac_Lite_Is_Rx_خالی(پایه_آدرس));

	/*
	 * Get the length of the frame that arrived, only 32-bit reads are
	 * allowed LengthType is in the upper half of the 32-bit word.
	 */
	ثبات = XEmacLite_ReadReg(پایه_آدرس, XEL_RPLR_جابه_جایی);
	درازی_Type = (u16) ((ثبات >> 16) &
			    (XEL_RPLR_درازی_ماسک_HI |
			     XEL_RPLR_درازی_ماسک_LO));

	/*
	 * Check if length is valid
	 */
	إذا (درازی_Type > XEL_MAX_قاب_اندازه) {
		/*
		 * Field contain type, use max frame size and
		 * let user parse it
		 */
		درازی = XEL_MAX_قاب_اندازه;
	}
	وإلا {
		/*
		 * Use the length in the frame, plus the header and trailer
		 */
		درازی = درازی_Type + XEL_سرآیند_اندازه + XEL_FCS_اندازه;
	}

	/*
	 * Read each byte from the EmacLite
	 */
	XEmacLite_AlignedRead((UINTPTR *) (پایه_آدرس + XEL_RXBUFF_جابه_جایی),
			      قاب_Ptr, درازی);

	/*
	 * Acknowledge the frame
	 */
	ثبات = XEmac_Lite_Get_Rx_وضعیت(پایه_آدرس);
	ثبات &= ~XEL_RSR_RECV_انجامشده_ماسک;
	XEmac_Lite_مجموعه_Rx_وضعیت(پایه_آدرس, ثبات);

	أرجع درازی_Type;
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
فراغ XEmacLite_AlignedWrite(فراغ *SrcPtr, UINTPTR *DestPtr, بیعلامت Byte_شمار)
{
	بیعلامت شاخص;
	بیعلامت درازی = Byte_شمار;
	متطاير u32 Align_میانگیر;
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
		log_info("length is %x", درازی);
		log_info("\n Size of To32Ptr: %x", حجم(*To32Ptr));
		log_info("\n Size of From32Ptr: %x", حجم(*From32Ptr));
#پایان_اگر		
		طالما (درازی > 3) {
			/*
			 * Output each word destination.
			 */
			*To32Ptr++ = *From32Ptr++;
#إذا 0
			*To32Ptr = *From32Ptr++;
			چاپ_کن("\n Write value @ %x: %x", To32Ptr, *To32Ptr);
			*To32Ptr++;

//#else
			*To32Ptr = *From32Ptr;
			log_info("\n 1:[%x]; 2: [%x]", *To32Ptr, *From32Ptr);
			log_info("\n 1:[%x]; 2: [%x]", To32Ptr, From32Ptr);
			*To32Ptr++;
			*From32Ptr++;
			log_info("\n 1_2:[%x]; 2: [%x]", *To32Ptr, *From32Ptr);
			log_info("\n 1_2:[%x]; 2: [%x]", To32Ptr, From32Ptr);
#پایان_اگر
			/*
			 * Adjust length accordingly
			 */
			درازی -= 4;
		}

		/*
		 * Set up to output the remaining data, zero the temp buffer
		 first.
		 */
		Align_میانگیر = 0;
		To8Ptr = (u8 *) &Align_میانگیر;
		From8Ptr = (u8 *) From32Ptr;

	}
	وإلا إذا ((((u32) SrcPtr) & 0x00000001) != 0) {
		/*
		 * Byte aligned buffer, correct.
		 */
		Align_میانگیر = 0;
		To8Ptr = (u8 *) &Align_میانگیر;
		From8Ptr = (u8 *) SrcPtr;

		طالما (درازی > 3) {
			/*
			 * Copy each byte into the temporary buffer.
			 */
			لكل (شاخص = 0; شاخص < 4; شاخص++) {
				*To8Ptr++ = *From8Ptr++;
			}

			/*
			 * Output the buffer
			 */
			*To32Ptr++ = Align_میانگیر;

			/*.
			 * Reset the temporary buffer pointer and adjust length.
			 */
			To8Ptr = (u8 *) &Align_میانگیر;
			درازی -= 4;
		}

		/*
		 * Set up to output the remaining data, zero the temp buffer
		 * first.
		 */
		Align_میانگیر = 0;
		To8Ptr = (u8 *) &Align_میانگیر;

	}
	وإلا {
		/*
		 * Half-Word aligned buffer, correct.
		 */
		Align_میانگیر = 0;

		/*
		 * This is a funny looking cast. The new gcc, version 3.3.x has
		 * a strict cast check for 16 bit pointers, aka short pointers.
		 * The following warning is issued if the initial 'void *' cast
		 * is  not used:
		 * 'dereferencing type-punned pointer will break strict-aliasing
		 * rules'
		 */

		To16Ptr = (u16 *) ((فراغ *) &Align_میانگیر);
		From16Ptr = (u16 *) SrcPtr;

		طالما (درازی > 3) {
			/*
			 * Copy each half word into the temporary buffer.
			 */
			لكل (شاخص = 0; شاخص < 2; شاخص++) {
				*To16Ptr++ = *From16Ptr++;
			}

			/*
			 * Output the buffer.
			 */
			*To32Ptr++ = Align_میانگیر;

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
			To16Ptr = (u16 *) ((فراغ *) &Align_میانگیر);
			درازی -= 4;
		}

		/*
		 * Set up to output the remaining data, zero the temp buffer
		 * first.
		 */
		Align_میانگیر = 0;
		To8Ptr = (u8 *) &Align_میانگیر;
		From8Ptr = (u8 *) From16Ptr;
	}

	/*
	 * Output the remaining data, zero the temp buffer first.
	 */
	لكل (شاخص = 0; شاخص < درازی; شاخص++) {
		*To8Ptr++ = *From8Ptr++;
	}
	إذا (درازی) {
		*To32Ptr++ = Align_میانگیر;
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
فراغ XEmacLite_AlignedRead(UINTPTR *SrcPtr, فراغ *DestPtr, بیعلامت Byte_شمار)
{
	بیعلامت شاخص;
	بیعلامت درازی = Byte_شمار;
	متطاير u32 Align_میانگیر;
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

		طالما (درازی > 3) {
			/*
			 * Output each word.
			 */
			*To32Ptr++ = *From32Ptr++;

			/*
			 * Adjust length accordingly.
			 */
			درازی -= 4;
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

		طالما (درازی > 3) {
			/*
			 * Copy each word into the temporary buffer.
			 */
			Align_میانگیر = *From32Ptr++;
			From8Ptr = (u8 *) &Align_میانگیر;

			/*
			 * Write data to destination.
			 */
			لكل (شاخص = 0; شاخص < 4; شاخص++) {
				*To8Ptr++ = *From8Ptr++;
			}

			/*
			 * Adjust length
			 */
			درازی -= 4;
		}

	}
	وإلا {
		/*
		 * Half-Word aligned buffer, correct.
		 */
		To16Ptr = (u16 *) DestPtr;

		طالما (درازی > 3) {
			/*
			 * Copy each word into the temporary buffer.
			 */
			Align_میانگیر = *From32Ptr++;

			/*
			 * This is a funny looking cast. The new gcc, version
			 * 3.3.x has a strict cast check for 16 bit pointers,
			 * aka short pointers. The following warning is issued
			 * if the initial 'void *' cast is not used:
			 * 'dereferencing type-punned pointer will break
			 *  strict-aliasing rules'
			 */
			From16Ptr = (u16 *) ((فراغ *) &Align_میانگیر);

			/*
			 * Write data to destination.
			 */
			لكل (شاخص = 0; شاخص < 2; شاخص++) {
				*To16Ptr++ = *From16Ptr++;
			}

			/*
			 * Adjust length.
			 */
			درازی -= 4;
		}

		/*
		 * Set up to read the remaining data.
		 */
		To8Ptr = (u8 *) To16Ptr;
	}

	/*
	 * Read the remaining data.
	 */
	Align_میانگیر = *From32Ptr++;
	From8Ptr = (u8 *) &Align_میانگیر;

	لكل (شاخص = 0; شاخص < درازی; شاخص++) {
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
	InstancePtr->EmacLiteConfig.پایه_آدرس = EffectiveAddr;
	InstancePtr->EmacLiteConfig.DeviceId = EmacLiteConfigPtr->DeviceId;
	InstancePtr->EmacLiteConfig.TxPingPong = EmacLiteConfigPtr->TxPingPong;
	InstancePtr->EmacLiteConfig.RxPingPong = EmacLiteConfigPtr->RxPingPong;
	InstancePtr->EmacLiteConfig.MdioInclude = EmacLiteConfigPtr->MdioInclude;
	InstancePtr->EmacLiteConfig.Loopback = EmacLiteConfigPtr->Loopback;

	InstancePtr->بعدی_Tx_میانگیر_مقصد_Use = 0x0;
	InstancePtr->بعدی_Rx_میانگیر_مقصد_Use = 0x0;
	InstancePtr->RecvHandler = (XEmacLite_Handler) StubHandler;
	InstancePtr->SendHandler = (XEmacLite_Handler) StubHandler;
	/*
	 * Clear the TX CSR's in case this is a restart.
	 */
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.پایه_آدرس,
				XEL_TSR_جابه_جایی, 0);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.پایه_آدرس,
				XEL_میانگیر_جابه_جایی + XEL_TSR_جابه_جایی, 0);

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
صحيح XEmacLite_Send(XEmacLite *InstancePtr, u8 *قاب_Ptr, بیعلامت Byte_شمار)
{
	u32 ثبات;
	UINTPTR پایه_آدرس;
	UINTPTR Emac_پایه_آدرس;
	u32 Intr_Enable_وضعیت;

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
	پایه_آدرس = XEmac_Lite_بعدی_Transmit_Addr(InstancePtr);
	Emac_پایه_آدرس = InstancePtr->EmacLiteConfig.پایه_آدرس;

	/*
	 * Check the Length if it is too large, truncate it.
	 * The maximum Tx packet size is
	 * Ethernet header (14 Bytes) + Maximum MTU (1500 bytes).
	 */
	إذا (Byte_شمار > XEL_MAX_TX_قاب_اندازه) {

		Byte_شمار = XEL_MAX_TX_قاب_اندازه;
	}

	/*
	 * Determine if the expected buffer address is empty.
	 */
	ثبات = XEmac_Lite_Get_Tx_وضعیت(پایه_آدرس);

	/*
	 * If the expected buffer is available, fill it with the provided data
	 * Align if necessary.
	 */
	إذا ((ثبات & (XEL_TSR_XMIT_BUSY_ماسک |
			XEL_TSR_XMIT_فعال_ماسک)) == 0) {

		/*
		 * Switch to next buffer if configured.
		 */
		إذا (InstancePtr->EmacLiteConfig.TxPingPong != 0) {
			InstancePtr->بعدی_Tx_میانگیر_مقصد_Use ^= XEL_میانگیر_جابه_جایی;
		}

		/*
		 * Write the frame to the buffer.
		 */
		XEmacLite_AlignedWrite(قاب_Ptr, (UINTPTR *) پایه_آدرس,
				       Byte_شمار);


		/*
		 * The frame is in the buffer, now send it.
		 */
		XEmacLite_WriteReg(پایه_آدرس, XEL_TPLR_جابه_جایی,
					(Byte_شمار & (XEL_TPLR_درازی_ماسک_HI |
					XEL_TPLR_درازی_ماسک_LO)));

		/*
		 * Update the Tx Status Register to indicate that there is a
		 * frame to send.
		 * If the interrupt enable bit of Ping buffer(since this
		 * controls both the buffers) is enabled then set the
		 * XEL_TSR_XMIT_ACTIVE_MASK flag which is used by the interrupt
		 * handler to call the callback function provided by the user
		 * to indicate that the frame has been transmitted.
		 */
		ثبات = XEmac_Lite_Get_Tx_وضعیت(پایه_آدرس);
		ثبات |= XEL_TSR_XMIT_BUSY_ماسک;
		Intr_Enable_وضعیت = XEmac_Lite_Get_Tx_وضعیت(Emac_پایه_آدرس);
		إذا ((Intr_Enable_وضعیت & XEL_TSR_XMIT_IE_ماسک) != 0) {
			ثبات |= XEL_TSR_XMIT_فعال_ماسک;
		}
		XEmac_Lite_مجموعه_Tx_وضعیت(پایه_آدرس, ثبات);

		أرجع SUCCESS;
	}

	/*
	 * If the expected buffer was full, try the other buffer if configured.
	 */
	إذا (InstancePtr->EmacLiteConfig.TxPingPong != 0) {

		پایه_آدرس ^= XEL_میانگیر_جابه_جایی;

		/*
		 * Determine if the expected buffer address is empty.
		 */
		ثبات = XEmac_Lite_Get_Tx_وضعیت(پایه_آدرس);

		/*
		 * If the next buffer is available, fill it with the provided
		 * data.
		 */
		إذا ((ثبات & (XEL_TSR_XMIT_BUSY_ماسک |
				XEL_TSR_XMIT_فعال_ماسک)) == 0) {

			/*
			 * Write the frame to the buffer.
			 */
			XEmacLite_AlignedWrite(قاب_Ptr, (UINTPTR *) پایه_آدرس,
					       Byte_شمار);

			/*
			 * The frame is in the buffer, now send it.
			 */
			XEmacLite_WriteReg(پایه_آدرس, XEL_TPLR_جابه_جایی,
					(Byte_شمار & (XEL_TPLR_درازی_ماسک_HI |
					   XEL_TPLR_درازی_ماسک_LO)));

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
			ثبات = XEmac_Lite_Get_Tx_وضعیت(پایه_آدرس);
			ثبات |= XEL_TSR_XMIT_BUSY_ماسک;
			Intr_Enable_وضعیت =
					XEmac_Lite_Get_Tx_وضعیت(Emac_پایه_آدرس);
			إذا ((Intr_Enable_وضعیت & XEL_TSR_XMIT_IE_ماسک) != 0) {
				ثبات |= XEL_TSR_XMIT_فعال_ماسک;
			}
			XEmac_Lite_مجموعه_Tx_وضعیت(پایه_آدرس, ثبات);

			/*
			 * Do not switch to next buffer, there is a sync problem
			 * and the expected buffer should not change.
			 */
			أرجع SUCCESS;
		}
	}

	چاپ_کن("\n Error in sending the packet");
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
u16 XEmacLite_Recv(XEmacLite *InstancePtr, u8 *قاب_Ptr)
{
	u16 درازی_Type;
	u16 درازی;
	u32 ثبات;
	UINTPTR پایه_آدرس;

	/*
	 * Verify that each of the inputs are valid.
	 */

	إذا (InstancePtr == عدم) {
		أرجع -1;
	}

	/*
	 * Determine the expected buffer address.
	 */
	پایه_آدرس = XEmac_Lite_بعدی_Receive_Addr(InstancePtr);

	/*
	 * Verify which buffer has valid data.
	 */
	ثبات = XEmac_Lite_Get_Rx_وضعیت(پایه_آدرس);

	إذا ((ثبات & XEL_RSR_RECV_انجامشده_ماسک) == XEL_RSR_RECV_انجامشده_ماسک) {

		/*
		 * The driver is in sync, update the next expected buffer if
		 * configured.
		 */

		إذا (InstancePtr->EmacLiteConfig.RxPingPong != 0) {
			InstancePtr->بعدی_Rx_میانگیر_مقصد_Use ^= XEL_میانگیر_جابه_جایی;
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
			پایه_آدرس ^= XEL_میانگیر_جابه_جایی;
		}
		وإلا {
			أرجع 0;	/* No data was available */
		}

		/*
		 * Verify that buffer has valid data.
		 */
		ثبات = XEmac_Lite_Get_Rx_وضعیت(پایه_آدرس);
		إذا ((ثبات & XEL_RSR_RECV_انجامشده_ماسک) !=
				XEL_RSR_RECV_انجامشده_ماسک) {
			أرجع 0;	/* No data was available */
		}
	}

	/*
	 * Get the length of the frame that arrived.
	 */
	درازی_Type = XEmac_Lite_Get_Receive_داده_درازی(پایه_آدرس);

	/*
	 * Check if length is valid.
	 */
	إذا (درازی_Type > XEL_MAX_قاب_اندازه) {


		إذا (درازی_Type == XEL_ETHER_PROTO_TYPE_IP) {

			/*
			 * The packet is a an IP Packet.
			 */
#اگر_تعریف_شده __LITTLE_ENDIAN__
			درازی = (XEmacLite_ReadReg((پایه_آدرس),
					XEL_سرآیند_IP_درازی_جابه_جایی +
					XEL_RXBUFF_جابه_جایی) &
					(XEL_RPLR_درازی_ماسک_HI |
					XEL_RPLR_درازی_ماسک_LO));
			درازی = (u16) (((درازی & 0xFF00) >> 8) | ((درازی & 0x00FF) << 8));
#وإلا
			درازی = ((XEmacLite_ReadReg((پایه_آدرس),
					XEL_سرآیند_IP_درازی_جابه_جایی +
					XEL_RXBUFF_جابه_جایی) >>
					XEL_سرآیند_لغزش) &
					(XEL_RPLR_درازی_ماسک_HI |
					XEL_RPLR_درازی_ماسک_LO));
#پایان_اگر

//			Length += XEL_HEADER_SIZE + XEL_FCS_SIZE;
			درازی += XEL_سرآیند_اندازه;
//			printf("\n Length1 is %x", Length);

		} وإلا إذا (درازی_Type == XEL_ETHER_PROTO_TYPE_ARP) {

			/*
			 * The packet is an ARP Packet.
			 */
			درازی = XEL_ARP_PACKET_اندازه + XEL_سرآیند_اندازه +
					XEL_FCS_اندازه;

		} وإلا {
			/*
			 * Field contains type other than IP or ARP, use max
			 * frame size and let user parse it.
			 */
			درازی = XEL_MAX_قاب_اندازه;

		}
	} وإلا {

		/*
		 * Use the length in the frame, plus the header and trailer.
		 */
		درازی = درازی_Type + XEL_سرآیند_اندازه + XEL_FCS_اندازه;
	}

	/*
	 * Read from the EmacLite.
	 */
	XEmacLite_AlignedRead(((UINTPTR *) (پایه_آدرس + XEL_RXBUFF_جابه_جایی)),
			      قاب_Ptr, درازی);

	/*
	 * Acknowledge the frame.
	 */
	ثبات = XEmac_Lite_Get_Rx_وضعیت(پایه_آدرس);
	ثبات &= ~XEL_RSR_RECV_انجامشده_ماسک;
	XEmac_Lite_مجموعه_Rx_وضعیت(پایه_آدرس, ثبات);

	أرجع درازی;
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
فراغ XEmac_Lite_مجموعه_Mac_آدرس(XEmacLite *InstancePtr, u8 *آدرس_Ptr)
{
	UINTPTR پایه_آدرس;

	/*
	 * Verify that each of the inputs are valid.
	 */
	إذا (InstancePtr == عدم) {
		أرجع -1;
	}

	/*
	 * Determine the expected TX buffer address.
	 */
	پایه_آدرس = XEmac_Lite_بعدی_Transmit_Addr(InstancePtr);

	/*
	 * Copy the MAC address to the Transmit buffer.
	 */
	XEmacLite_AlignedWrite(آدرس_Ptr,
				(UINTPTR *) پایه_آدرس,
				XEL_MAC_ADDR_اندازه);

	/*
	 * Set the length.
	 */
	XEmacLite_WriteReg(پایه_آدرس,
				XEL_TPLR_جابه_جایی,
				XEL_MAC_ADDR_اندازه);

	/*
	 * Update the MAC address in the EmacLite.
	 */
	XEmac_Lite_مجموعه_Tx_وضعیت(پایه_آدرس, XEL_TSR_PROG_MAC_ADDR);


	/*
	 * Wait for EmacLite to finish with the MAC address update.
	 */
	طالما ((XEmac_Lite_Get_Tx_وضعیت(پایه_آدرس) &
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
فراغ StubHandler(فراغ *Call_پشت_Ref)
{
	(فراغ)(Call_پشت_Ref);
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
صحيح XEmac_Lite_Tx_میانگیر_موجود(XEmacLite *InstancePtr)
{

	u32 ثبات;
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
	ثبات = XEmac_Lite_Get_Tx_وضعیت(InstancePtr->EmacLiteConfig.
						پایه_آدرس);

	TxPingBusy = (ثبات & (XEL_TSR_XMIT_BUSY_ماسک |
				 XEL_TSR_XMIT_فعال_ماسک));


	/*
	 * Read the Tx Status of the second buffer register and determine if the
	 * buffer is available.
	 */
	إذا (InstancePtr->EmacLiteConfig.TxPingPong != 0) {
		ثبات = XEmac_Lite_Get_Tx_وضعیت(InstancePtr->EmacLiteConfig.
						پایه_آدرس +
						XEL_میانگیر_جابه_جایی);

		TxPongBusy = (ثبات & (XEL_TSR_XMIT_BUSY_ماسک |
					XEL_TSR_XMIT_فعال_ماسک));

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

	u32 ثبات;

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
	ثبات = XEmac_Lite_Get_Rx_وضعیت(InstancePtr->EmacLiteConfig.
						پایه_آدرس);

	/*
	 * Preserve the IE bit.
	 */
	ثبات &= XEL_RSR_RECV_IE_ماسک;

	/*
	 * Write out the value to flush the RX buffer.
	 */
	XEmac_Lite_مجموعه_Rx_وضعیت(InstancePtr->EmacLiteConfig.پایه_آدرس,
				ثبات);

	/*
	 * If the pong buffer is available, flush it also.
	 */
	إذا (InstancePtr->EmacLiteConfig.RxPingPong != 0) {
		/*
		 * Read the current buffer register and determine if the buffer
		 * is available.
		 */
		ثبات = XEmac_Lite_Get_Rx_وضعیت(InstancePtr->EmacLiteConfig.
							پایه_آدرس +
							XEL_میانگیر_جابه_جایی);

		/*
		 * Preserve the IE bit.
		 */
		ثبات &= XEL_RSR_RECV_IE_ماسک;

		/*
		 * Write out the value to flush the RX buffer.
		 */
		XEmac_Lite_مجموعه_Rx_وضعیت(InstancePtr->EmacLiteConfig.پایه_آدرس +
					XEL_میانگیر_جابه_جایی, ثبات);

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
صحيح XEmacLite_PhyRead(XEmacLite *InstancePtr, u32 Phy_آدرس, u32 Reg_رقم,
			u16 *Phy_داده_Ptr)
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
		إذا (Phy_آدرس <= 31) {
			أرجع -1;
		}
		إذا (Reg_رقم <= 31) {
			أرجع -1;
		}

	إذا (Phy_داده_Ptr == عدم) {
		أرجع -1;
	}

	/*
	 * Verify MDIO master status.
	 */
	إذا (XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.پایه_آدرس,
				XEL_MDIOCNTR_جابه_جایی) &
				XEL_MDIOCNTR_وضعیت_ماسک) {
		أرجع DEVICE_BUSY;
	}

	PhyAddrReg = ((((Phy_آدرس << XEL_MDIO_آدرس_لغزش) &
			XEL_MDIO_آدرس_ماسک) | Reg_رقم) | XEL_MDIO_OP_ماسک);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.پایه_آدرس,
				 XEL_MDIOADDR_جابه_جایی, PhyAddrReg);

	/*
	 * Enable MDIO and start the transfer.
	 */
	MdioCtrlReg =
		XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.پایه_آدرس,
					XEL_MDIOCNTR_جابه_جایی);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.پایه_آدرس,
				XEL_MDIOCNTR_جابه_جایی,
				MdioCtrlReg |
				XEL_MDIOCNTR_وضعیت_ماسک |
				XEL_MDIOCNTR_ENABLE_ماسک);

	/*
	 * Wait till the completion of transfer.
	 */
	طالما ((XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.پایه_آدرس,
				XEL_MDIOCNTR_جابه_جایی) &
				XEL_MDIOCNTR_وضعیت_ماسک));

	/*
	 * Read data from MDIO read data register.
	 */
	*Phy_داده_Ptr = (u16)XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.پایه_آدرس,
					XEL_MDIORD_جابه_جایی);

	/*
	 * Disable the MDIO.
	 */
	MdioCtrlReg =
		XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.پایه_آدرس,
					XEL_MDIOCNTR_جابه_جایی);

	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.پایه_آدرس,
				XEL_MDIOCNTR_جابه_جایی,
				MdioCtrlReg & ~XEL_MDIOCNTR_ENABLE_ماسک);


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
صحيح XEmacLite_PhyWrite(XEmacLite *InstancePtr, u32 Phy_آدرس, u32 Reg_رقم,
			u16 Phy_داده)
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
	إذا (Phy_آدرس <= 31) {
		أرجع -1;
	}
	إذا (Reg_رقم <= 31) {
		أرجع -1;
	}

	/*
	 * Verify MDIO master status.
	 */
	إذا (XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.پایه_آدرس,
				XEL_MDIOCNTR_جابه_جایی) &
				XEL_MDIOCNTR_وضعیت_ماسک) {
		أرجع DEVICE_BUSY;
	}



	PhyAddrReg = ((((Phy_آدرس << XEL_MDIO_آدرس_لغزش) &
			XEL_MDIO_آدرس_ماسک) | Reg_رقم) & ~XEL_MDIO_OP_ماسک);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.پایه_آدرس,
				XEL_MDIOADDR_جابه_جایی, PhyAddrReg);

	/*
	 * Write data to MDIO write data register.
	 */
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.پایه_آدرس,
				XEL_MDIOWR_جابه_جایی, (u32)Phy_داده);

	/*
	 * Enable MDIO and start the transfer.
	 */
	MdioCtrlReg =
		XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.پایه_آدرس,
					XEL_MDIOCNTR_جابه_جایی);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.پایه_آدرس,
				XEL_MDIOCNTR_جابه_جایی,
				MdioCtrlReg | XEL_MDIOCNTR_وضعیت_ماسک |
				XEL_MDIOCNTR_ENABLE_ماسک);

	/*
	 * Wait till the completion of transfer.
	 */
	طالما ((XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.پایه_آدرس,
				XEL_MDIOCNTR_جابه_جایی) & XEL_MDIOCNTR_وضعیت_ماسک));


	/*
	 * Disable the MDIO.
	 */
	MdioCtrlReg =
		XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.پایه_آدرس,
					XEL_MDIOCNTR_جابه_جایی);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.پایه_آدرس,
				XEL_MDIOCNTR_جابه_جایی,
				MdioCtrlReg & ~XEL_MDIOCNTR_ENABLE_ماسک);



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
فراغ XEmac_Lite_Enable_Loop_پشت(XEmacLite *InstancePtr)
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

	TsrReg = XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.پایه_آدرس,
					XEL_TSR_جابه_جایی);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.پایه_آدرس,
			XEL_TSR_جابه_جایی,	TsrReg | XEL_TSR_LOOPBACK_ماسک);
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
فراغ XEmac_Lite_Disable_Loop_پشت(XEmacLite *InstancePtr)
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

	TsrReg = XEmacLite_ReadReg(InstancePtr->EmacLiteConfig.پایه_آدرس,
					XEL_TSR_جابه_جایی);
	XEmacLite_WriteReg(InstancePtr->EmacLiteConfig.پایه_آدرس,
			XEL_TSR_جابه_جایی,	TsrReg & (~XEL_TSR_LOOPBACK_ماسک));
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
ساكن u16 XEmac_Lite_Get_Receive_داده_درازی(UINTPTR پایه_آدرس)
{
	u16 درازی;

#اگر_تعریف_شده __LITTLE_ENDIAN__
	درازی = (XEmacLite_ReadReg((پایه_آدرس),
			XEL_سرآیند_جابه_جایی + XEL_RXBUFF_جابه_جایی) &
			(XEL_RPLR_درازی_ماسک_HI | XEL_RPLR_درازی_ماسک_LO));
	درازی = (u16) (((درازی & 0xFF00) >> 8) | ((درازی & 0x00FF) << 8));
#وإلا
	درازی = ((XEmacLite_ReadReg((پایه_آدرس),
			XEL_سرآیند_جابه_جایی + XEL_RXBUFF_جابه_جایی) >>
			XEL_سرآیند_لغزش) &
			(XEL_RPLR_درازی_ماسک_HI | XEL_RPLR_درازی_ماسک_LO));
#پایان_اگر

	أرجع درازی;
}

صحيح XEmacLite_EnableInterrupts(XEmacLite *InstancePtr)
{
	u32 ثبات;
	UINTPTR پایه_آدرس;

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
	ثبات = XEmac_Lite_Get_Tx_وضعیت(پایه_آدرس);
	ثبات |= XEL_TSR_XMIT_IE_ماسک;
	XEmac_Lite_مجموعه_Tx_وضعیت(پایه_آدرس, ثبات);

	/*
	 * Enable the RX interrupts for both the buffers, the Interrupt Enable
	 * is common for the both the buffers and is defined in the
	 * Ping buffer.
	 */
	ثبات = XEmac_Lite_Get_Rx_وضعیت(پایه_آدرس);
	ثبات |= XEL_RSR_RECV_IE_ماسک;
	XEmac_Lite_مجموعه_Rx_وضعیت(پایه_آدرس, ثبات);

	/*
	 * Enable the global interrupt output.
	 */
	XEmacLite_WriteReg(پایه_آدرس, XEL_GIER_جابه_جایی, XEL_GIER_GIE_ماسک);

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
	u32 ثبات;
	UINTPTR پایه_آدرس;

	/*
	 * Verify that each of the inputs are valid.
	 */
		إذا(عدم == InstancePtr)
			أرجع -1;
		إذا(InstancePtr->IsReady != XIL_COMPONENT_IS_READY)
			أرجع -1;


	پایه_آدرس = InstancePtr->EmacLiteConfig.پایه_آدرس;

	/*
	 * Disable the global interrupt output.
	 */
	XEmacLite_WriteReg(پایه_آدرس, XEL_GIER_جابه_جایی, 0);

	/*
	 * Disable the TX interrupts for both the buffers, the Interrupt Enable
	 * is common for the both the buffers and is defined in the
	 * Ping buffer.
	 */
	ثبات = XEmac_Lite_Get_Tx_وضعیت(پایه_آدرس);
	ثبات &= ~XEL_TSR_XMIT_IE_ماسک;
	XEmac_Lite_مجموعه_Tx_وضعیت(پایه_آدرس, ثبات);

	/*
	 * Disable the RX interrupts for both the buffers, the Interrupt Enable
	 * is common for the both the buffers and is defined in the
	 * Ping buffer.
	 */
	ثبات = XEmac_Lite_Get_Rx_وضعیت(پایه_آدرس);
	ثبات &= ~XEL_RSR_RECV_IE_ماسک;
	XEmac_Lite_مجموعه_Rx_وضعیت(پایه_آدرس, ثبات);

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
فراغ XEmac_Lite_وقفه_Handler(فراغ *InstancePtr)
{

	XEmacLite *EmacLitePtr;
	صحيح TxCompleteIntr = FALSE;
	UINTPTR پایه_آدرس;
	u32 Tx_وضعیت;

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
	پایه_آدرس = EmacLitePtr->EmacLiteConfig.پایه_آدرس;

	إذا ((XEmac_Lite_Is_Rx_خالی(پایه_آدرس) != TRUE) ||
		(XEmac_Lite_Is_Rx_خالی(پایه_آدرس +
			XEL_میانگیر_جابه_جایی) != TRUE)) {
		/*
		 * Call the RX callback.
		 */
		EmacLitePtr->RecvHandler(EmacLitePtr->RecvRef);

	}

	Tx_وضعیت = XEmac_Lite_Get_Tx_وضعیت(پایه_آدرس);
	إذا (((Tx_وضعیت & XEL_TSR_XMIT_BUSY_ماسک) == 0) &&
		(Tx_وضعیت & XEL_TSR_XMIT_فعال_ماسک) != 0) {

		/*
		 * Clear the Tx Active bit in the Tx Status Register.
		 */
		Tx_وضعیت &= ~XEL_TSR_XMIT_فعال_ماسک;
		XEmac_Lite_مجموعه_Tx_وضعیت(پایه_آدرس, Tx_وضعیت);

		/*
		 * Update the flag indicating that there was a Tx Interrupt.
		 */
		TxCompleteIntr = TRUE;

	}

	Tx_وضعیت = XEmac_Lite_Get_Tx_وضعیت(پایه_آدرس + XEL_میانگیر_جابه_جایی);
	إذا (((Tx_وضعیت & XEL_TSR_XMIT_BUSY_ماسک) == 0) &&
		(Tx_وضعیت & XEL_TSR_XMIT_فعال_ماسک) != 0) {

		/*
		 * Clear the Tx Active bit in the Tx Status Register.
		 */
		Tx_وضعیت &= ~XEL_TSR_XMIT_فعال_ماسک;
		XEmac_Lite_مجموعه_Tx_وضعیت(پایه_آدرس + XEL_میانگیر_جابه_جایی,
					Tx_وضعیت);
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
فراغ XEmac_Lite_مجموعه_Recv_Handler(XEmacLite *InstancePtr, فراغ *Call_پشت_Ref,
			      XEmacLite_Handler FuncPtr)
{
	إذا(عدم == InstancePtr)
		أرجع -1;
	إذا(عدم == FuncPtr)
		أرجع -1;
	إذا(InstancePtr->IsReady != XIL_COMPONENT_IS_READY)
		أرجع -1;

	InstancePtr->RecvHandler = FuncPtr;
	InstancePtr->RecvRef = Call_پشت_Ref;
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
فراغ XEmac_Lite_مجموعه_Send_Handler(XEmacLite *InstancePtr, فراغ *Call_پشت_Ref,
			      XEmacLite_Handler FuncPtr)
{
	إذا(عدم == InstancePtr)
		أرجع -1;
	إذا(عدم == FuncPtr)
		أرجع -1;
	إذا(InstancePtr->IsReady != XIL_COMPONENT_IS_READY)
		أرجع -1;

	InstancePtr->SendHandler = FuncPtr;
	InstancePtr->SendRef = Call_پشت_Ref;
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
	u16 Phy_داده;
	صحيح PhyAddr;

	/*
	 * Verify all 32 MDIO ports.
	 */
	لكل (PhyAddr = 31; PhyAddr >= 0; PhyAddr--) {
		XEmacLite_PhyRead(InstancePtr, PhyAddr, PHY_REG1_جابه_جایی,
				 &Phy_داده);

		إذا (Phy_داده != 0xFFFF) {
			إذا ((Phy_داده & PHY_REG1_DETECT_ماسک) ==
			PHY_REG1_DETECT_ماسک) {
				أرجع PhyAddr;	/* Found a valid PHY device */
			}
		}
	}
	چاپ_کن("\n Could not detect phy device");
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
صحيح Emac_Lite_Enable_Phy_Loop_پشت(XEmacLite *InstancePtr, u32 Phy_آدرس)
{
	صحيح وضعیت;
	u16 Phy_داده = 0;

	/*
	 * Set the speed and put the PHY in reset.
	 */
	Phy_داده |= PHY_REG0_SPD_100_ماسک;
	وضعیت = XEmacLite_PhyWrite(InstancePtr, Phy_آدرس, PHY_REG0_جابه_جایی,
			Phy_داده | PHY_REG0_RESET_ماسک);
	إذا (وضعیت != XST_SUCCESS) {
		أرجع XST_FAILURE;
	}

	/*
	 * Give sufficient delay for Phy Reset.
	 */
	EmacLitePhyDelay(EMACLITE_PHY_DELAY_SEC);

	/*
	 * Set the PHY in loop back.
	 */
	XEmacLite_PhyWrite(InstancePtr, Phy_آدرس, PHY_REG0_جابه_جایی,
			Phy_داده | PHY_REG0_LOOPBACK_ماسک);
	إذا (وضعیت != XST_SUCCESS) {
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
صحيح Emac_Lite_Disable_Phy_Loop_پشت(XEmacLite *InstancePtr, u32 Phy_آدرس)
{
	صحيح وضعیت;
	u16 Phy_داده;

	/*
	 * Disable loop back through PHY register using MDIO support.
	 */
	وضعیت = XEmacLite_PhyRead(InstancePtr, Phy_آدرس, PHY_REG0_جابه_جایی,
					&Phy_داده);
	إذا (وضعیت != XST_SUCCESS) {
		أرجع XST_FAILURE;
	}

	وضعیت = XEmacLite_PhyWrite(InstancePtr,Phy_آدرس, PHY_REG0_جابه_جایی,
					Phy_داده & ~(PHY_REG0_LOOPBACK_ماسک));
	إذا (وضعیت != XST_SUCCESS) {
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
فراغ EmacLitePhyDelay(بیعلامت صحيح Seconds)
{
#اگر_تعریف_شده __MICROBLAZE__
	ساكن صحيح WarningFlag = 0;

	/* If MB caches are disabled or do not exist, this delay loop could
	 * take minutes instead of seconds (e.g., 30x longer).  Print a warning
	 * message for the user (once).  If only MB had a built-in timer!
	 */
	إذا (((mfmsr() & 0x20) == 0) && (!WarningFlag)) {
#اگر_تعریف_شده STDOUT_BASEADDRESS
		xil_printf("Warning: This example will take ");
		xil_printf("minutes to complete without I-cache enabled \r\n");
#پایان_اگر
		WarningFlag = 1;
	}

#تعریف_کن ITERS_در_هر_SEC   (XPAR_CPU_CORE_CLOCK_FREQ_HZ / 6)
    asm متطاير ("\n"
                  "1:               \n\t"
                  "addik r7, r0, %0 \n\t"
                  "2:               \n\t"
                  "addik r7, r7, -1 \n\t"
                  "bneid  r7, 2b    \n\t"
                  "or  r0, r0, r0   \n\t"
                  "bneid %1, 1b     \n\t"
                  "addik %1, %1, -1 \n\t"
                  :: "i"(ITERS_در_هر_SEC), "d" (Seconds));

#وإلا

//	usleep(Seconds * 1000000);
//	waitfor(Seconds * 1000);
#پایان_اگر
}


