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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ ETH_DRIVER_H
#ವ್ಯಾಖ್ಯಾನಿಸು ETH_DRIVER_H
#ಅನ್ತರ್ಭಾವ "platform.h"
#ಅನ್ತರ್ಭಾವ "traps.h"
#ಅನ್ತರ್ಭಾವ "eth_driver.h"
#ಅನ್ತರ್ಭಾವ "eth_macros.h"

#ವ್ಯಾಖ್ಯಾನಿಸು INLINE ಸಾಲೊಳಗೆ
#ವ್ಯಾಖ್ಯಾನಿಸು __LITTLE_ENDIAN__ 1


/*
 * guarded against xbasic_types.h.
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint8_t u8;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint16_t u16;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t u32;
/** @}*/
#ವ್ಯಾಖ್ಯಾನಿಸು __XUINT64__
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
	u32 ಊರ್ಧ್ವ;
	u32 ಅಧೋ;
} Xuint64;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಅಕ್ಷರ char8;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ int8_t s8;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ int16_t s16;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ int32_t s32;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ int64_t s64;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint64_t u64;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೂರ್ಣಾಂಕ sint32;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ intptr_t INTPTR;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uintptr_t UINTPTR;
//typedef ptrdiff_t PTRDIFF;

/*****************************************************************************
 *
 * EmacLite defines .
 * DeviceID starts at 240
 */
#ವ್ಯಾಖ್ಯಾನಿಸು XPAR_XEMACLITE_ಅಂಕೆ_INSTANCES    1
#ವ್ಯಾಖ್ಯಾನಿಸು XPAR_EMACLITE_0_DEVICE_ID       240
/* EK Change */
#ವ್ಯಾಖ್ಯಾನಿಸು XPAR_EMACLITE_0_BASEADDR      0x00044000 //0
#ವ್ಯಾಖ್ಯಾನಿಸು XPAR_EMACLITE_0_TX_PING_PONG    1
#ವ್ಯಾಖ್ಯಾನಿಸು XPAR_EMACLITE_0_RX_PING_PONG    1
#ವ್ಯಾಖ್ಯಾನಿಸು XPAR_EMACLITE_0_INCLUDE_MDIO 1
#ವ್ಯಾಖ್ಯಾನಿಸು XPAR_EMACLITE_0_INCLUDE_ಆಂತರಿಕ_LOOPBACK 1


#ವ್ಯಾಖ್ಯಾನಿಸು TRUE		1U
#ವ್ಯಾಖ್ಯಾನಿಸು FALSE		0U

#ವ್ಯಾಖ್ಯಾನಿಸು ಖಾಲಿ		0U
#ವ್ಯಾಖ್ಯಾನಿಸು SUCCESS 0
#ವ್ಯಾಖ್ಯಾನಿಸು FAILURE -1
#ವ್ಯಾಖ್ಯಾನಿಸು DEVICE_BUSY                 21L	/*!< Device is busy */
#ವ್ಯಾಖ್ಯಾನಿಸು NO_CALLBACK 18L	/*!< A callback has not yet been
						   registered */
#ವ್ಯಾಖ್ಯಾನಿಸು NO_ದತ್ತಾಂಶ                     13L	/*!< There was no data available */
#ವ್ಯಾಖ್ಯಾನಿಸು XST_LOOPBACK_ERROR              17L	/*!< A loopback test failed */
#ವ್ಯಾಖ್ಯಾನಿಸು XST_NO_CALLBACK                 18L	/*!< A callback has not yet been
						   registered */
#ವ್ಯಾಖ್ಯಾನಿಸು XST_NO_FEATURE                  19L	/*!< Device is not configured with
						   the requested feature */
#ವ್ಯಾಖ್ಯಾನಿಸು XST_NOT_ಅಡಚಣೆ               20L	/*!< Device is not configured for
						   interrupt mode operation */

#ವ್ಯಾಖ್ಯಾನಿಸು XIL_COMPONENT_IS_READY     0x11111111U  /**< In device drivers, This macro will be
                                                 assigend to "IsReady" member of driver
												 instance to indicate that driver
												 instance is initialized and ready to use. */
#ವ್ಯಾಖ್ಯಾನಿಸು XIL_COMPONENT_IS_STARTED   0x22222222U  /**< In device drivers, This macro will be assigend to
                                                 "IsStarted" member of driver instance
												 to indicate that driver instance is
												 started and it can be enabled. */
#ವ್ಯಾಖ್ಯಾನಿಸು XST_SUCCESS SUCCESS
#ವ್ಯಾಖ್ಯಾನಿಸು XST_FAILURE FAILURE
#ವ್ಯಾಖ್ಯಾನಿಸು xil_printf log_debug

/************************** Constant Definitions ****************************/

#ವ್ಯಾಖ್ಯಾನಿಸು PHY_REG0_ಸ್ಥಾನಾಂತರ		0 /* Register 0 of PHY device */
#ವ್ಯಾಖ್ಯಾನಿಸು PHY_REG1_ಸ್ಥಾನಾಂತರ 	1 /* Register 1 of PHY device */

#ವ್ಯಾಖ್ಯಾನಿಸು PHY_REG0_RESET_ಮುಖವಾಡ	0x8000  /* Reset Phy device */
#ವ್ಯಾಖ್ಯಾನಿಸು PHY_REG0_LOOPBACK_ಮುಖವಾಡ	0x4000  /* Loopback Enable in Phy */
#ವ್ಯಾಖ್ಯಾನಿಸು PHY_REG0_SPD_100_ಮುಖವಾಡ	0x2000  /* Speed of 100Mbps for Phy */

#ವ್ಯಾಖ್ಯಾನಿಸು PHY_REG1_DETECT_ಮುಖವಾಡ	0x1808	/* Mask to detect PHY device */

#ವ್ಯಾಖ್ಯಾನಿಸು EMACLITE_PHY_DELAY_SEC	4	/* Amount of time to delay waiting on
					 * PHY to reset.
					 */


/**
 * This typedef contains configuration information for a device.
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ {
	u16 DeviceId;	 /**< Unique ID  of device */
	UINTPTR ತಳ_ವಿಳಾಸ; /**< Device base address */
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
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (*XEmacLite_Handler) (ಶೂನ್ಯ *Call_ಹಿಂಭಾಗ_Ref);

/**
 * The XEmacLite driver instance data. The user is required to allocate a
 * variable of this type for every EmacLite device in the system. A pointer
 * to a variable of this type is then passed to the driver API functions.
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ {
	XEmacLite_Config EmacLiteConfig; /* Device configuration */
	u32 IsReady;			 /* Device is initialized and ready */

	u32 ಮುಂದಿನ_Tx_ಬಫರ್_ಗಮ್ಯ_Use;		 /* Next TX buffer to write to */
	u32 ಮುಂದಿನ_Rx_ಬಫರ್_ಗಮ್ಯ_Use;		 /* Next RX buffer to read from */

	/*
	 * Callbacks
	 */
	XEmacLite_Handler RecvHandler;
	ಶೂನ್ಯ *RecvRef;
	XEmacLite_Handler SendHandler;
	ಶೂನ್ಯ *SendRef;

} XEmacLite;

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ ETH_VARI
ಬಾಹ್ಯ ಅಸ್ಥಿರ u32 Recv_ಚೌಕಟ್ಟು_ಉದ್ದಳತೆ;
ಬಾಹ್ಯ UINTPTR TxBuffPtr;
ಬಾಹ್ಯ UINTPTR RxBuffPtr;
ಬಾಹ್ಯ ಅಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಚೌಕಟ್ಟುಗಳು_Tx;
ಬಾಹ್ಯ ಅಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಚೌಕಟ್ಟುಗಳು_Rx;
ಬಾಹ್ಯ ಅಸ್ಥಿರ ಪೂರ್ಣಾಂಕ Tx_ಎಣಿಕೆ;
ಬಾಹ್ಯ ಅಸ್ಥಿರ ಪೂರ್ಣಾಂಕ Rx_ಎಣಿಕೆ;
ಬಾಹ್ಯ ಅಸ್ಥಿರ ಪೂರ್ಣಾಂಕ Padding;	/* For 1588 Packets we need to pad 8 bytes time stamp value */
#ಆದರೆ_ಅಂತ್ಯ



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
#ವ್ಯಾಖ್ಯಾನಿಸು XEmac_Lite_ಮುಂದಿನ_Transmit_Addr(InstancePtr) 			\
	((InstancePtr)->EmacLiteConfig.ತಳ_ವಿಳಾಸ + 			\
		(InstancePtr)->ಮುಂದಿನ_Tx_ಬಫರ್_ಗಮ್ಯ_Use) + XEL_TXBUFF_ಸ್ಥಾನಾಂತರ

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
#ವ್ಯಾಖ್ಯಾನಿಸು XEmac_Lite_ಮುಂದಿನ_Receive_Addr(InstancePtr)				\
	((InstancePtr)->EmacLiteConfig.ತಳ_ವಿಳಾಸ + 			\
	(InstancePtr)->ಮುಂದಿನ_Rx_ಬಫರ್_ಗಮ್ಯ_Use)

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
#ವ್ಯಾಖ್ಯಾನಿಸು XEmacLite_IsMdioConfigured(InstancePtr) 			\
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
#ವ್ಯಾಖ್ಯಾನಿಸು XEmacLite_IsLoopbackConfigured(InstancePtr) 			\
            ((InstancePtr)->EmacLiteConfig.Loopback == 1)

/************************** Variable Definitions *****************************/


ಶೂನ್ಯ XEmacLite_AlignedWrite(ಶೂನ್ಯ *SrcPtr, UINTPTR *DestPtr, ಚಿಹ್ನೆರಹಿತ Byte_ಎಣಿಕೆ);
ಶೂನ್ಯ XEmacLite_AlignedRead(UINTPTR *SrcPtr, ಶೂನ್ಯ *DestPtr, ಚಿಹ್ನೆರಹಿತ Byte_ಎಣಿಕೆ);

ಬಾಹ್ಯ XEmacLite_Config XEmac_Lite_Config_ಕೋಷ್ಟಕ;
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ XEmacLite_CfgInitialize(XEmacLite *InstancePtr,
				XEmacLite_Config *EmacLiteConfigPtr,
				UINTPTR EffectiveAddr);


#ಆದರೆ_ಅಂತ್ಯ
