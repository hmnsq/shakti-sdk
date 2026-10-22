/***************************************************************************
* Project           	     : shakti devt board
* Name of the file	     : ETH_driver.h
* Brief Description of file  : Header file for ETH driver.
* Name of Author    	     : 
* Email ID                   : sathya281@gmail.com

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
 * @file plic_driver.h
 * @brief  Header file for plic driver.c
 * @detail This file contains the definitions for plic driver. The memory map
 * for the plic module is also defined here.
 */

#अगर_अघोषित ETH_DRIVER_H
#घोषणा ETH_DRIVER_H
#समावेश "platform.h"
#समावेश "traps.h"
#समावेश "eth_driver.h"
#समावेश "eth_macros.h"

#घोषणा INLINE अंतरभूत
#घोषणा __LITTLE_ENDIAN__ 1


/*
 * guarded against xbasic_types.h.
 */
प्रकार uint8_t u8;
प्रकार uint16_t u16;
प्रकार uint32_t u32;
/** @}*/
#घोषणा __XUINT64__
प्रकार काष्ठा
{
	u32 Upper;
	u32 Lower;
} Xuint64;

प्रकार अक्षर char8;
प्रकार int8_t s8;
प्रकार int16_t s16;
प्रकार int32_t s32;
प्रकार int64_t s64;
प्रकार uint64_t u64;
प्रकार पूर्णांक sint32;

प्रकार intptr_t INTPTR;
प्रकार uintptr_t UINTPTR;
//typedef ptrdiff_t PTRDIFF;

/*****************************************************************************
 *
 * EmacLite defines .
 * DeviceID starts at 240
 */
#घोषणा XPAR_XEMACLITE_अंक_INSTANCES    1
#घोषणा XPAR_EMACLITE_0_DEVICE_ID       240
/* EK Change */
#घोषणा XPAR_EMACLITE_0_BASEADDR      0x00044000 //0
#घोषणा XPAR_EMACLITE_0_TX_PING_PONG    1
#घोषणा XPAR_EMACLITE_0_RX_PING_PONG    1
#घोषणा XPAR_EMACLITE_0_INCLUDE_MDIO 1
#घोषणा XPAR_EMACLITE_0_INCLUDE_INTERNAL_LOOPBACK 1


#घोषणा TRUE		1U
#घोषणा FALSE		0U

#घोषणा शून्य		0U
#घोषणा SUCCESS 0
#घोषणा FAILURE -1
#घोषणा DEVICE_BUSY                 21L	/*!< Device is busy */
#घोषणा NO_CALLBACK 18L	/*!< A callback has not yet been
						   registered */
#घोषणा NO_तथ्य                     13L	/*!< There was no data available */
#घोषणा XST_LOOPBACK_ERROR              17L	/*!< A loopback test failed */
#घोषणा XST_NO_CALLBACK                 18L	/*!< A callback has not yet been
						   registered */
#घोषणा XST_NO_FEATURE                  19L	/*!< Device is not configured with
						   the requested feature */
#घोषणा XST_NOT_INTERRUPT               20L	/*!< Device is not configured for
						   interrupt mode operation */

#घोषणा XIL_COMPONENT_IS_READY     0x11111111U  /**< In device drivers, This macro will be
                                                 assigend to "IsReady" member of driver
												 instance to indicate that driver
												 instance is initialized and ready to use. */
#घोषणा XIL_COMPONENT_IS_STARTED   0x22222222U  /**< In device drivers, This macro will be assigend to
                                                 "IsStarted" member of driver instance
												 to indicate that driver instance is
												 started and it can be enabled. */
#घोषणा XST_SUCCESS SUCCESS
#घोषणा XST_FAILURE FAILURE
#घोषणा xil_printf log_debug

/************************** Constant Definitions ****************************/

#घोषणा PHY_REG0_OFFSET		0 /* Register 0 of PHY device */
#घोषणा PHY_REG1_OFFSET 	1 /* Register 1 of PHY device */

#घोषणा PHY_REG0_RESET_MASK	0x8000  /* Reset Phy device */
#घोषणा PHY_REG0_LOOPBACK_MASK	0x4000  /* Loopback Enable in Phy */
#घोषणा PHY_REG0_SPD_100_MASK	0x2000  /* Speed of 100Mbps for Phy */

#घोषणा PHY_REG1_DETECT_MASK	0x1808	/* Mask to detect PHY device */

#घोषणा EMACLITE_PHY_DELAY_SEC	4	/* Amount of time to delay waiting on
					 * PHY to reset.
					 */


/**
 * This typedef contains configuration information for a device.
 */
प्रकार काष्ठा {
	u16 DeviceId;	 /**< Unique ID  of device */
	UINTPTR BaseAddress; /**< Device base address */
	u8 TxPingPong;	 /**< 1 if TX Pong buffer configured, 0 otherwise */
	u8 RxPingPong;	 /**< 1 if RX Pong buffer configured, 0 otherwise */
	u8 MdioInclude;  /**< 1 if MDIO is enabled, 0 otherwise */
	u8 Loopback;     /**< 1 if internal loopback is enabled, 0 otherwise */
} XEmacLite_Config;

/*
 * Callback when data is sent or received .
 * @param 	CallBackRef is a callback reference passed in by the upper layer
 *		when setting the callback functions, and passed back to the
 *		upper layer when the callback is invoked.
 */
प्रकार व्योम (*XEmacLite_Handler) (व्योम *CallBackRef);

/**
 * The XEmacLite driver instance data. The user is required to allocate a
 * variable of this type for every EmacLite device in the system. A pointer
 * to a variable of this type is then passed to the driver API functions.
 */
प्रकार काष्ठा {
	XEmacLite_Config EmacLiteConfig; /* Device configuration */
	u32 IsReady;			 /* Device is initialized and ready */

	u32 अग्र_Tx_बफर_To_Use;		 /* Next TX buffer to write to */
	u32 अग्र_Rx_बफर_To_Use;		 /* Next RX buffer to read from */

	/*
	 * Callbacks
	 */
	XEmacLite_Handler RecvHandler;
	व्योम *RecvRef;
	XEmacLite_Handler SendHandler;
	व्योम *SendRef;

} XEmacLite;

#अगर_अघोषित ETH_VARI
बाह्य अस्थिर u32 Recv_Frame_लंबाई;
बाह्य UINTPTR TxBuffPtr;
बाह्य UINTPTR RxBuffPtr;
बाह्य अस्थिर पूर्णांक FramesTx;
बाह्य अस्थिर पूर्णांक FramesRx;
बाह्य अस्थिर पूर्णांक Tx_गिनती;
बाह्य अस्थिर पूर्णांक Rx_गिनती;
बाह्य अस्थिर पूर्णांक Padding;	/* For 1588 Packets we need to pad 8 bytes time stamp value */
#पूर्ण_अगर



/****************************************************************************/
/**
*
* Return the next expected Transmit Buffer's address.
*
* @param	InstancePtr is the pointer to the instance of the driver to
*		be worked on
*
* @note		C-Style signature:
*		u32 XEmacLite_NextTransmitAddr(XEmacLite *InstancePtr);
*
* This macro returns the address of the next transmit buffer to put data into.
* This is used to determine the destination of the next transmit data frame.
*
*****************************************************************************/
#घोषणा XEmac_Lite_अग्र_Transmit_Addr(InstancePtr) 			\
	((InstancePtr)->EmacLiteConfig.BaseAddress + 			\
		(InstancePtr)->अग्र_Tx_बफर_To_Use) + XEL_TXBUFF_OFFSET

/****************************************************************************/
/**
*
* Return the next expected Receive Buffer's address.
*
* @param	InstancePtr is the pointer to the instance of the driver to
*		be worked on
*
* @note		C-Style signature:
*		u32 XEmacLite_NextReceiveAddr(XEmacLite *InstancePtr);
*
* This macro returns the address of the next receive buffer to read data from.
* This is the expected receive buffer address if the driver is in sync.
*
*****************************************************************************/
#घोषणा XEmac_Lite_अग्र_Receive_Addr(InstancePtr)				\
	((InstancePtr)->EmacLiteConfig.BaseAddress + 			\
	(InstancePtr)->अग्र_Rx_बफर_To_Use)

/*****************************************************************************/
/**
*
* This macro determines if the device is currently configured for MDIO.
*
* @param	InstancePtr is the pointer to the instance of the
*		EmacLite driver.
*
* @return
* 		- TRUE if the device is configured for MDIO.
*		- FALSE if the device is NOT configured for MDIO.
*
* @note		C-Style signature:
*		int XEmacLite_IsMdioConfigured(XEmacLite *InstancePtr)
*
******************************************************************************/
#घोषणा XEmacLite_IsMdioConfigured(InstancePtr) 			\
	((InstancePtr)->EmacLiteConfig.MdioInclude == 1)

/*****************************************************************************/
/**
*
* This macro determines if the device is currently configured for internal
* loopback.
*
* @param	InstancePtr is the pointer to the instance of the
*		EmacLite driver.
*
* @return
* 		- TRUE if the device is configured for internal loopback.
*		- FALSE if the device is NOT configured for internal loopback.
*
* @note		C-Style signature:
*		int XEmacLite_IsLoopbackConfigured(XEmacLite *InstancePtr)
*
******************************************************************************/
#घोषणा XEmacLite_IsLoopbackConfigured(InstancePtr) 			\
            ((InstancePtr)->EmacLiteConfig.Loopback == 1)

/************************** Variable Definitions *****************************/


व्योम XEmacLite_AlignedWrite(व्योम *SrcPtr, UINTPTR *DestPtr, अचिन्हित Byte_गिनती);
व्योम XEmacLite_AlignedRead(UINTPTR *SrcPtr, व्योम *DestPtr, अचिन्हित Byte_गिनती);

बाह्य XEmacLite_Config XEmacLite_ConfigTable;
बाह्य पूर्णांक XEmacLite_CfgInitialize(XEmacLite *InstancePtr,
				XEmacLite_Config *EmacLiteConfigPtr,
				UINTPTR EffectiveAddr);


#पूर्ण_अगर
