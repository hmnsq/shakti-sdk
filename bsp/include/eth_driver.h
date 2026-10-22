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

#جے_بنا_تعریف ETH_DRIVER_H
#تعریف_کرو ETH_DRIVER_H
#ضمن "platform.h"
#ضمن "traps.h"
#ضمن "eth_driver.h"
#ضمن "eth_macros.h"

#تعریف_کرو INLINE مضمن
#تعریف_کرو __LITTLE_ENDIAN__ 1


/*
 * guarded against xbasic_types.h.
 */
تعريفنوع uint8_t u8;
تعريفنوع uint16_t u16;
تعريفنوع uint32_t u32;
/** @}*/
#تعریف_کرو __XUINT64__
تعريفنوع بنية
{
	u32 اتلا;
	u32 ہیٹھلا;
} Xuint64;

تعريفنوع حرف char8;
تعريفنوع int8_t s8;
تعريفنوع int16_t s16;
تعريفنوع int32_t s32;
تعريفنوع int64_t s64;
تعريفنوع uint64_t u64;
تعريفنوع صحيح sint32;

تعريفنوع intptr_t INTPTR;
تعريفنوع uintptr_t UINTPTR;
//typedef ptrdiff_t PTRDIFF;

/*****************************************************************************
 *
 * EmacLite defines .
 * DeviceID starts at 240
 */
#تعریف_کرو XPAR_XEMACLITE_عدد_INSTANCES    1
#تعریف_کرو XPAR_EMACLITE_0_DEVICE_ID       240
/* EK Change */
#تعریف_کرو XPAR_EMACLITE_0_BASEADDR      0x00044000 //0
#تعریف_کرو XPAR_EMACLITE_0_TX_PING_PONG    1
#تعریف_کرو XPAR_EMACLITE_0_RX_PING_PONG    1
#تعریف_کرو XPAR_EMACLITE_0_INCLUDE_MDIO 1
#تعریف_کرو XPAR_EMACLITE_0_INCLUDE_اندرونی_LOOPBACK 1


#تعریف_کرو TRUE		1U
#تعریف_کرو FALSE		0U

#تعریف_کرو عدم		0U
#تعریف_کرو SUCCESS 0
#تعریف_کرو FAILURE -1
#تعریف_کرو DEVICE_BUSY                 21L	/*!< Device is busy */
#تعریف_کرو NO_CALLBACK 18L	/*!< A callback has not yet been
						   registered */
#تعریف_کرو NO_انکڑے                     13L	/*!< There was no data available */
#تعریف_کرو XST_LOOPBACK_ERROR              17L	/*!< A loopback test failed */
#تعریف_کرو XST_NO_CALLBACK                 18L	/*!< A callback has not yet been
						   registered */
#تعریف_کرو XST_NO_FEATURE                  19L	/*!< Device is not configured with
						   the requested feature */
#تعریف_کرو XST_NOT_رکاوٹ               20L	/*!< Device is not configured for
						   interrupt mode operation */

#تعریف_کرو XIL_COMPONENT_IS_READY     0x11111111U  /**< In device drivers, This macro will be
                                                 assigend to "IsReady" member of driver
												 instance to indicate that driver
												 instance is initialized and ready to use. */
#تعریف_کرو XIL_COMPONENT_IS_STARTED   0x22222222U  /**< In device drivers, This macro will be assigend to
                                                 "IsStarted" member of driver instance
												 to indicate that driver instance is
												 started and it can be enabled. */
#تعریف_کرو XST_SUCCESS SUCCESS
#تعریف_کرو XST_FAILURE FAILURE
#تعریف_کرو xil_printf log_debug

/************************** Constant Definitions ****************************/

#تعریف_کرو PHY_REG0_وتھ		0 /* Register 0 of PHY device */
#تعریف_کرو PHY_REG1_وتھ 	1 /* Register 1 of PHY device */

#تعریف_کرو PHY_REG0_RESET_نقاب	0x8000  /* Reset Phy device */
#تعریف_کرو PHY_REG0_LOOPBACK_نقاب	0x4000  /* Loopback Enable in Phy */
#تعریف_کرو PHY_REG0_SPD_100_نقاب	0x2000  /* Speed of 100Mbps for Phy */

#تعریف_کرو PHY_REG1_DETECT_نقاب	0x1808	/* Mask to detect PHY device */

#تعریف_کرو EMACLITE_PHY_DELAY_SEC	4	/* Amount of time to delay waiting on
					 * PHY to reset.
					 */


/**
 * This typedef contains configuration information for a device.
 */
تعريفنوع بنية {
	u16 DeviceId;	 /**< Unique ID  of device */
	UINTPTR ادھار_پتہ; /**< Device base address */
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
تعريفنوع فراغ (*XEmacLite_Handler) (فراغ *Call_پٹھ_Ref);

/**
 * The XEmacLite driver instance data. The user is required to allocate a
 * variable of this type for every EmacLite device in the system. A pointer
 * to a variable of this type is then passed to the driver API functions.
 */
تعريفنوع بنية {
	XEmacLite_Config EmacLiteConfig; /* Device configuration */
	u32 IsReady;			 /* Device is initialized and ready */

	u32 اگلا_Tx_بفر_منزل_Use;		 /* Next TX buffer to write to */
	u32 اگلا_Rx_بفر_منزل_Use;		 /* Next RX buffer to read from */

	/*
	 * Callbacks
	 */
	XEmacLite_Handler RecvHandler;
	فراغ *RecvRef;
	XEmacLite_Handler SendHandler;
	فراغ *SendRef;

} XEmacLite;

#جے_بنا_تعریف ETH_VARI
خارجي متطاير u32 Recv_چوکھٹا_لمائی;
خارجي UINTPTR TxBuffPtr;
خارجي UINTPTR RxBuffPtr;
خارجي متطاير صحيح چوکھٹے_Tx;
خارجي متطاير صحيح چوکھٹے_Rx;
خارجي متطاير صحيح Tx_گنتی;
خارجي متطاير صحيح Rx_گنتی;
خارجي متطاير صحيح Padding;	/* For 1588 Packets we need to pad 8 bytes time stamp value */
#جے_انت



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
#تعریف_کرو XEmac_Lite_اگلا_Transmit_Addr(InstancePtr) 			\
	((InstancePtr)->EmacLiteConfig.ادھار_پتہ + 			\
		(InstancePtr)->اگلا_Tx_بفر_منزل_Use) + XEL_TXBUFF_وتھ

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
#تعریف_کرو XEmac_Lite_اگلا_Receive_Addr(InstancePtr)				\
	((InstancePtr)->EmacLiteConfig.ادھار_پتہ + 			\
	(InstancePtr)->اگلا_Rx_بفر_منزل_Use)

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
#تعریف_کرو XEmacLite_IsMdioConfigured(InstancePtr) 			\
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
#تعریف_کرو XEmacLite_IsLoopbackConfigured(InstancePtr) 			\
            ((InstancePtr)->EmacLiteConfig.Loopback == 1)

/************************** Variable Definitions *****************************/


فراغ XEmacLite_AlignedWrite(فراغ *SrcPtr, UINTPTR *DestPtr, بنانشانی Byte_گنتی);
فراغ XEmacLite_AlignedRead(UINTPTR *SrcPtr, فراغ *DestPtr, بنانشانی Byte_گنتی);

خارجي XEmacLite_Config XEmac_Lite_Config_جدول;
خارجي صحيح XEmacLite_CfgInitialize(XEmacLite *InstancePtr,
				XEmacLite_Config *EmacLiteConfigPtr,
				UINTPTR EffectiveAddr);


#جے_انت
