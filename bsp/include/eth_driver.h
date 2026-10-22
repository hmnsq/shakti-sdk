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

#నిర్వచితం_కాకపోతే ETH_DRIVER_H
#నిర్వచించు ETH_DRIVER_H
#అన్తర్భావ "platform.h"
#అన్తర్భావ "traps.h"
#అన్తర్భావ "eth_driver.h"
#అన్తర్భావ "eth_macros.h"

#నిర్వచించు INLINE అంతఃవరుస
#నిర్వచించు __LITTLE_ENDIAN__ 1


/*
 * guarded against xbasic_types.h.
 */
రకనిర్వచనం uint8_t u8;
రకనిర్వచనం uint16_t u16;
రకనిర్వచనం uint32_t u32;
/** @}*/
#నిర్వచించు __XUINT64__
రకనిర్వచనం నిర్మాణం
{
	u32 పై;
	u32 క్రింది;
} Xuint64;

రకనిర్వచనం అక్షరం char8;
రకనిర్వచనం int8_t s8;
రకనిర్వచనం int16_t s16;
రకనిర్వచనం int32_t s32;
రకనిర్వచనం int64_t s64;
రకనిర్వచనం uint64_t u64;
రకనిర్వచనం పూర్ణాంకం sint32;

రకనిర్వచనం intptr_t INTPTR;
రకనిర్వచనం uintptr_t UINTPTR;
//typedef ptrdiff_t PTRDIFF;

/*****************************************************************************
 *
 * EmacLite defines .
 * DeviceID starts at 240
 */
#నిర్వచించు XPAR_XEMACLITE_అంకె_INSTANCES    1
#నిర్వచించు XPAR_EMACLITE_0_DEVICE_ID       240
/* EK Change */
#నిర్వచించు XPAR_EMACLITE_0_BASEADDR      0x00044000 //0
#నిర్వచించు XPAR_EMACLITE_0_TX_PING_PONG    1
#నిర్వచించు XPAR_EMACLITE_0_RX_PING_PONG    1
#నిర్వచించు XPAR_EMACLITE_0_INCLUDE_MDIO 1
#నిర్వచించు XPAR_EMACLITE_0_INCLUDE_అంతర్గత_LOOPBACK 1


#నిర్వచించు TRUE		1U
#నిర్వచించు FALSE		0U

#నిర్వచించు ఖాళీ		0U
#నిర్వచించు SUCCESS 0
#నిర్వచించు FAILURE -1
#నిర్వచించు DEVICE_BUSY                 21L	/*!< Device is busy */
#నిర్వచించు NO_CALLBACK 18L	/*!< A callback has not yet been
						   registered */
#నిర్వచించు NO_దత్తాంశం                     13L	/*!< There was no data available */
#నిర్వచించు XST_LOOPBACK_ERROR              17L	/*!< A loopback test failed */
#నిర్వచించు XST_NO_CALLBACK                 18L	/*!< A callback has not yet been
						   registered */
#నిర్వచించు XST_NO_FEATURE                  19L	/*!< Device is not configured with
						   the requested feature */
#నిర్వచించు XST_NOT_అంతరాయం               20L	/*!< Device is not configured for
						   interrupt mode operation */

#నిర్వచించు XIL_COMPONENT_IS_READY     0x11111111U  /**< In device drivers, This macro will be
                                                 assigend to "IsReady" member of driver
												 instance to indicate that driver
												 instance is initialized and ready to use. */
#నిర్వచించు XIL_COMPONENT_IS_STARTED   0x22222222U  /**< In device drivers, This macro will be assigend to
                                                 "IsStarted" member of driver instance
												 to indicate that driver instance is
												 started and it can be enabled. */
#నిర్వచించు XST_SUCCESS SUCCESS
#నిర్వచించు XST_FAILURE FAILURE
#నిర్వచించు xil_printf log_debug

/************************** Constant Definitions ****************************/

#నిర్వచించు PHY_REG0_స్థానభ్రంశం		0 /* Register 0 of PHY device */
#నిర్వచించు PHY_REG1_స్థానభ్రంశం 	1 /* Register 1 of PHY device */

#నిర్వచించు PHY_REG0_RESET_ముసుగు	0x8000  /* Reset Phy device */
#నిర్వచించు PHY_REG0_LOOPBACK_ముసుగు	0x4000  /* Loopback Enable in Phy */
#నిర్వచించు PHY_REG0_SPD_100_ముసుగు	0x2000  /* Speed of 100Mbps for Phy */

#నిర్వచించు PHY_REG1_DETECT_ముసుగు	0x1808	/* Mask to detect PHY device */

#నిర్వచించు EMACLITE_PHY_DELAY_SEC	4	/* Amount of time to delay waiting on
					 * PHY to reset.
					 */


/**
 * This typedef contains configuration information for a device.
 */
రకనిర్వచనం నిర్మాణం {
	u16 DeviceId;	 /**< Unique ID  of device */
	UINTPTR పునాది_చిరునామా; /**< Device base address */
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
రకనిర్వచనం శూన్య (*XEmacLite_Handler) (శూన్య *Call_వెనుక_Ref);

/**
 * The XEmacLite driver instance data. The user is required to allocate a
 * variable of this type for every EmacLite device in the system. A pointer
 * to a variable of this type is then passed to the driver API functions.
 */
రకనిర్వచనం నిర్మాణం {
	XEmacLite_Config EmacLiteConfig; /* Device configuration */
	u32 IsReady;			 /* Device is initialized and ready */

	u32 తదుపరి_Tx_బఫరు_గమ్యం_Use;		 /* Next TX buffer to write to */
	u32 తదుపరి_Rx_బఫరు_గమ్యం_Use;		 /* Next RX buffer to read from */

	/*
	 * Callbacks
	 */
	XEmacLite_Handler RecvHandler;
	శూన్య *RecvRef;
	XEmacLite_Handler SendHandler;
	శూన్య *SendRef;

} XEmacLite;

#నిర్వచితం_కాకపోతే ETH_VARI
బాహ్య అస్థిర u32 Recv_చట్రం_నిడివి;
బాహ్య UINTPTR TxBuffPtr;
బాహ్య UINTPTR RxBuffPtr;
బాహ్య అస్థిర పూర్ణాంకం చట్రాలు_Tx;
బాహ్య అస్థిర పూర్ణాంకం చట్రాలు_Rx;
బాహ్య అస్థిర పూర్ణాంకం Tx_లెక్క;
బాహ్య అస్థిర పూర్ణాంకం Rx_లెక్క;
బాహ్య అస్థిర పూర్ణాంకం Padding;	/* For 1588 Packets we need to pad 8 bytes time stamp value */
#అయితే_ముగింపు



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
#నిర్వచించు XEmac_Lite_తదుపరి_Transmit_Addr(InstancePtr) 			\
	((InstancePtr)->EmacLiteConfig.పునాది_చిరునామా + 			\
		(InstancePtr)->తదుపరి_Tx_బఫరు_గమ్యం_Use) + XEL_TXBUFF_స్థానభ్రంశం

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
#నిర్వచించు XEmac_Lite_తదుపరి_Receive_Addr(InstancePtr)				\
	((InstancePtr)->EmacLiteConfig.పునాది_చిరునామా + 			\
	(InstancePtr)->తదుపరి_Rx_బఫరు_గమ్యం_Use)

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
#నిర్వచించు XEmacLite_IsMdioConfigured(InstancePtr) 			\
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
#నిర్వచించు XEmacLite_IsLoopbackConfigured(InstancePtr) 			\
            ((InstancePtr)->EmacLiteConfig.Loopback == 1)

/************************** Variable Definitions *****************************/


శూన్య XEmacLite_AlignedWrite(శూన్య *SrcPtr, UINTPTR *DestPtr, గుర్తులేని Byte_లెక్క);
శూన్య XEmacLite_AlignedRead(UINTPTR *SrcPtr, శూన్య *DestPtr, గుర్తులేని Byte_లెక్క);

బాహ్య XEmacLite_Config XEmac_Lite_Config_పట్టిక;
బాహ్య పూర్ణాంకం XEmacLite_CfgInitialize(XEmacLite *InstancePtr,
				XEmacLite_Config *EmacLiteConfigPtr,
				UINTPTR EffectiveAddr);


#అయితే_ముగింపు
