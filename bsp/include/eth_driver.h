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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ETH_DRIVER_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ETH_DRIVER_H
#ਅਨ੍ਤਰ੍ਭਾਵ "platform.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "traps.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "eth_driver.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "eth_macros.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INLINE ਸਤਰਅੰਦਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ __LITTLE_ENDIAN__ 1


/*
 * guarded against xbasic_types.h.
 */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint8_t u8;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint16_t u16;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint32_t u32;
/** @}*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ __XUINT64__
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
	u32 ਉੱਤਲਾ;
	u32 ਹੇਠਲਾ;
} Xuint64;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਅੱਖਰ char8;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ int8_t s8;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ int16_t s16;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ int32_t s32;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ int64_t s64;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uint64_t u64;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੂਰਨ sint32;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ intptr_t INTPTR;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ uintptr_t UINTPTR;
//typedef ptrdiff_t PTRDIFF;

/*****************************************************************************
 *
 * EmacLite defines .
 * DeviceID starts at 240
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XPAR_XEMACLITE_ਅੰਕ_INSTANCES    1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XPAR_EMACLITE_0_DEVICE_ID       240
/* EK Change */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XPAR_EMACLITE_0_BASEADDR      0x00044000 //0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XPAR_EMACLITE_0_TX_PING_PONG    1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XPAR_EMACLITE_0_RX_PING_PONG    1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XPAR_EMACLITE_0_INCLUDE_MDIO 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XPAR_EMACLITE_0_INCLUDE_ਅੰਦਰੂਨੀ_LOOPBACK 1


#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TRUE		1U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FALSE		0U

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਨਿਰਾ		0U
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SUCCESS 0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FAILURE -1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEVICE_BUSY                 21L	/*!< Device is busy */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ NO_CALLBACK 18L	/*!< A callback has not yet been
						   registered */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ NO_ਅੰਕੜੇ                     13L	/*!< There was no data available */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XST_LOOPBACK_ERROR              17L	/*!< A loopback test failed */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XST_NO_CALLBACK                 18L	/*!< A callback has not yet been
						   registered */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XST_NO_FEATURE                  19L	/*!< Device is not configured with
						   the requested feature */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XST_NOT_ਰੁਕਾਵਟ               20L	/*!< Device is not configured for
						   interrupt mode operation */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XIL_COMPONENT_IS_READY     0x11111111U  /**< In device drivers, This macro will be
                                                 assigend to "IsReady" member of driver
												 instance to indicate that driver
												 instance is initialized and ready to use. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XIL_COMPONENT_IS_STARTED   0x22222222U  /**< In device drivers, This macro will be assigend to
                                                 "IsStarted" member of driver instance
												 to indicate that driver instance is
												 started and it can be enabled. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XST_SUCCESS SUCCESS
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XST_FAILURE FAILURE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ xil_printf log_debug

/************************** Constant Definitions ****************************/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PHY_REG0_ਵਿੱਥ		0 /* Register 0 of PHY device */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PHY_REG1_ਵਿੱਥ 	1 /* Register 1 of PHY device */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PHY_REG0_RESET_ਨਕਾਬ	0x8000  /* Reset Phy device */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PHY_REG0_LOOPBACK_ਨਕਾਬ	0x4000  /* Loopback Enable in Phy */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PHY_REG0_SPD_100_ਨਕਾਬ	0x2000  /* Speed of 100Mbps for Phy */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PHY_REG1_DETECT_ਨਕਾਬ	0x1808	/* Mask to detect PHY device */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EMACLITE_PHY_DELAY_SEC	4	/* Amount of time to delay waiting on
					 * PHY to reset.
					 */


/**
 * This typedef contains configuration information for a device.
 */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ {
	u16 DeviceId;	 /**< Unique ID  of device */
	UINTPTR ਅਧਾਰ_ਪਤਾ; /**< Device base address */
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
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (*XEmacLite_Handler) (ਖਾਲੀ *Call_ਪਿੱਠ_Ref);

/**
 * The XEmacLite driver instance data. The user is required to allocate a
 * variable of this type for every EmacLite device in the system. A pointer
 * to a variable of this type is then passed to the driver API functions.
 */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ {
	XEmacLite_Config EmacLiteConfig; /* Device configuration */
	u32 IsReady;			 /* Device is initialized and ready */

	u32 ਅਗਲਾ_Tx_ਬਫਰ_ਮੰਜ਼ਿਲ_Use;		 /* Next TX buffer to write to */
	u32 ਅਗਲਾ_Rx_ਬਫਰ_ਮੰਜ਼ਿਲ_Use;		 /* Next RX buffer to read from */

	/*
	 * Callbacks
	 */
	XEmacLite_Handler RecvHandler;
	ਖਾਲੀ *RecvRef;
	XEmacLite_Handler SendHandler;
	ਖਾਲੀ *SendRef;

} XEmacLite;

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ETH_VARI
ਬਾਹਰੀ ਅਸਥਿਰ u32 Recv_ਚੌਖਟਾ_ਲੰਮਾਈ;
ਬਾਹਰੀ UINTPTR TxBuffPtr;
ਬਾਹਰੀ UINTPTR RxBuffPtr;
ਬਾਹਰੀ ਅਸਥਿਰ ਪੂਰਨ ਚੌਖਟੇ_Tx;
ਬਾਹਰੀ ਅਸਥਿਰ ਪੂਰਨ ਚੌਖਟੇ_Rx;
ਬਾਹਰੀ ਅਸਥਿਰ ਪੂਰਨ Tx_ਗਿਣਤੀ;
ਬਾਹਰੀ ਅਸਥਿਰ ਪੂਰਨ Rx_ਗਿਣਤੀ;
ਬਾਹਰੀ ਅਸਥਿਰ ਪੂਰਨ Padding;	/* For 1588 Packets we need to pad 8 bytes time stamp value */
#ਜੇ_ਅੰਤ



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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEmac_Lite_ਅਗਲਾ_Transmit_Addr(InstancePtr) 			\
	((InstancePtr)->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ + 			\
		(InstancePtr)->ਅਗਲਾ_Tx_ਬਫਰ_ਮੰਜ਼ਿਲ_Use) + XEL_TXBUFF_ਵਿੱਥ

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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEmac_Lite_ਅਗਲਾ_Receive_Addr(InstancePtr)				\
	((InstancePtr)->EmacLiteConfig.ਅਧਾਰ_ਪਤਾ + 			\
	(InstancePtr)->ਅਗਲਾ_Rx_ਬਫਰ_ਮੰਜ਼ਿਲ_Use)

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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEmacLite_IsMdioConfigured(InstancePtr) 			\
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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEmacLite_IsLoopbackConfigured(InstancePtr) 			\
            ((InstancePtr)->EmacLiteConfig.Loopback == 1)

/************************** Variable Definitions *****************************/


ਖਾਲੀ XEmacLite_AlignedWrite(ਖਾਲੀ *SrcPtr, UINTPTR *DestPtr, ਬਿਨਾਨਿਸ਼ਾਨੀ Byte_ਗਿਣਤੀ);
ਖਾਲੀ XEmacLite_AlignedRead(UINTPTR *SrcPtr, ਖਾਲੀ *DestPtr, ਬਿਨਾਨਿਸ਼ਾਨੀ Byte_ਗਿਣਤੀ);

ਬਾਹਰੀ XEmacLite_Config XEmac_Lite_Config_ਸਾਰਣੀ;
ਬਾਹਰੀ ਪੂਰਨ XEmacLite_CfgInitialize(XEmacLite *InstancePtr,
				XEmacLite_Config *EmacLiteConfigPtr,
				UINTPTR EffectiveAddr);


#ਜੇ_ਅੰਤ
