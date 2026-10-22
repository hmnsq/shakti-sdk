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

#यदि_अपरिभाषितम् ETH_DRIVER_H
#परिभाषय ETH_DRIVER_H
#अन्तर्भाव "platform.h"
#अन्तर्भाव "traps.h"
#अन्तर्भाव "eth_driver.h"
#अन्तर्भाव "eth_macros.h"

#परिभाषय INLINE अन्तःस्थ
#परिभाषय __LITTLE_ENDIAN__ 1


/*
 * guarded against xbasic_types.h.
 */
प्रकारनिर्देश uint8_t u8;
प्रकारनिर्देश uint16_t u16;
प्रकारनिर्देश uint32_t u32;
/** @}*/
#परिभाषय __XUINT64__
प्रकारनिर्देश संरचना
{
	u32 ऊर्ध्वस्थम्;
	u32 अधस्तनम्;
} Xuint64;

प्रकारनिर्देश वर्ण char8;
प्रकारनिर्देश int8_t s8;
प्रकारनिर्देश int16_t s16;
प्रकारनिर्देश int32_t s32;
प्रकारनिर्देश int64_t s64;
प्रकारनिर्देश uint64_t u64;
प्रकारनिर्देश पूर्णाङ्क sint32;

प्रकारनिर्देश intptr_t INTPTR;
प्रकारनिर्देश uintptr_t UINTPTR;
//typedef ptrdiff_t PTRDIFF;

/*****************************************************************************
 *
 * EmacLite defines .
 * DeviceID starts at 240
 */
#परिभाषय XPAR_XEMACLITE_अङ्कः_INSTANCES    1
#परिभाषय XPAR_EMACLITE_0_DEVICE_ID       240
/* EK Change */
#परिभाषय XPAR_EMACLITE_0_BASEADDR      0x00044000 //0
#परिभाषय XPAR_EMACLITE_0_TX_PING_PONG    1
#परिभाषय XPAR_EMACLITE_0_RX_PING_PONG    1
#परिभाषय XPAR_EMACLITE_0_INCLUDE_MDIO 1
#परिभाषय XPAR_EMACLITE_0_INCLUDE_आन्तरिकम्_LOOPBACK 1


#परिभाषय TRUE		1U
#परिभाषय FALSE		0U

#परिभाषय रिक्त		0U
#परिभाषय SUCCESS 0
#परिभाषय FAILURE -1
#परिभाषय DEVICE_BUSY                 21L	/*!< Device is busy */
#परिभाषय NO_CALLBACK 18L	/*!< A callback has not yet been
						   registered */
#परिभाषय NO_दत्त                     13L	/*!< There was no data available */
#परिभाषय XST_LOOPBACK_ERROR              17L	/*!< A loopback test failed */
#परिभाषय XST_NO_CALLBACK                 18L	/*!< A callback has not yet been
						   registered */
#परिभाषय XST_NO_FEATURE                  19L	/*!< Device is not configured with
						   the requested feature */
#परिभाषय XST_NOT_व्यवधानम्               20L	/*!< Device is not configured for
						   interrupt mode operation */

#परिभाषय XIL_COMPONENT_IS_READY     0x11111111U  /**< In device drivers, This macro will be
                                                 assigend to "IsReady" member of driver
												 instance to indicate that driver
												 instance is initialized and ready to use. */
#परिभाषय XIL_COMPONENT_IS_STARTED   0x22222222U  /**< In device drivers, This macro will be assigend to
                                                 "IsStarted" member of driver instance
												 to indicate that driver instance is
												 started and it can be enabled. */
#परिभाषय XST_SUCCESS SUCCESS
#परिभाषय XST_FAILURE FAILURE
#परिभाषय xil_printf log_debug

/************************** Constant Definitions ****************************/

#परिभाषय PHY_REG0_विस्थापनम्		0 /* Register 0 of PHY device */
#परिभाषय PHY_REG1_विस्थापनम् 	1 /* Register 1 of PHY device */

#परिभाषय PHY_REG0_RESET_आवरणम्	0x8000  /* Reset Phy device */
#परिभाषय PHY_REG0_LOOPBACK_आवरणम्	0x4000  /* Loopback Enable in Phy */
#परिभाषय PHY_REG0_SPD_100_आवरणम्	0x2000  /* Speed of 100Mbps for Phy */

#परिभाषय PHY_REG1_DETECT_आवरणम्	0x1808	/* Mask to detect PHY device */

#परिभाषय EMACLITE_PHY_DELAY_SEC	4	/* Amount of time to delay waiting on
					 * PHY to reset.
					 */


/**
 * This typedef contains configuration information for a device.
 */
प्रकारनिर्देश संरचना {
	u16 DeviceId;	 /**< Unique ID  of device */
	UINTPTR आधारः_स्थानाङ्कः; /**< Device base address */
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
प्रकारनिर्देश शून्य (*XEmacLite_Handler) (शून्य *Call_पृष्ठभागः_Ref);

/**
 * The XEmacLite driver instance data. The user is required to allocate a
 * variable of this type for every EmacLite device in the system. A pointer
 * to a variable of this type is then passed to the driver API functions.
 */
प्रकारनिर्देश संरचना {
	XEmacLite_Config EmacLiteConfig; /* Device configuration */
	u32 IsReady;			 /* Device is initialized and ready */

	u32 अग्र_Tx_बफर_गन्तव्यम्_Use;		 /* Next TX buffer to write to */
	u32 अग्र_Rx_बफर_गन्तव्यम्_Use;		 /* Next RX buffer to read from */

	/*
	 * Callbacks
	 */
	XEmacLite_Handler RecvHandler;
	शून्य *RecvRef;
	XEmacLite_Handler SendHandler;
	शून्य *SendRef;

} XEmacLite;

#यदि_अपरिभाषितम् ETH_VARI
बाह्य चञ्चल u32 Recv_Frame_दीर्घता;
बाह्य UINTPTR TxBuffPtr;
बाह्य UINTPTR RxBuffPtr;
बाह्य चञ्चल पूर्णाङ्क चौकटाः_Tx;
बाह्य चञ्चल पूर्णाङ्क चौकटाः_Rx;
बाह्य चञ्चल पूर्णाङ्क Tx_गणनम्;
बाह्य चञ्चल पूर्णाङ्क Rx_गणनम्;
बाह्य चञ्चल पूर्णाङ्क Padding;	/* For 1588 Packets we need to pad 8 bytes time stamp value */
#यदि_अन्तः



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
#परिभाषय XEmac_Lite_अग्र_Transmit_Addr(InstancePtr) 			\
	((InstancePtr)->EmacLiteConfig.आधारः_स्थानाङ्कः + 			\
		(InstancePtr)->अग्र_Tx_बफर_गन्तव्यम्_Use) + XEL_TXBUFF_विस्थापनम्

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
#परिभाषय XEmac_Lite_अग्र_Receive_Addr(InstancePtr)				\
	((InstancePtr)->EmacLiteConfig.आधारः_स्थानाङ्कः + 			\
	(InstancePtr)->अग्र_Rx_बफर_गन्तव्यम्_Use)

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
#परिभाषय XEmacLite_IsMdioConfigured(InstancePtr) 			\
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
#परिभाषय XEmacLite_IsLoopbackConfigured(InstancePtr) 			\
            ((InstancePtr)->EmacLiteConfig.Loopback == 1)

/************************** Variable Definitions *****************************/


शून्य XEmacLite_AlignedWrite(शून्य *SrcPtr, UINTPTR *DestPtr, अचिह्नित Byte_गणनम्);
शून्य XEmacLite_AlignedRead(UINTPTR *SrcPtr, शून्य *DestPtr, अचिह्नित Byte_गणनम्);

बाह्य XEmacLite_Config XEmac_Lite_Config_सारणी;
बाह्य पूर्णाङ्क XEmacLite_CfgInitialize(XEmacLite *InstancePtr,
				XEmacLite_Config *EmacLiteConfigPtr,
				UINTPTR EffectiveAddr);


#यदि_अन्तः
