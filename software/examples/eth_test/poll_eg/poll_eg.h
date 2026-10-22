/******************************************************************************
* Copyright (C) 2009 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xemaclite_example.h
*
* Defines common data types, prototypes, and includes the proper headers
* for use with the EmacLite example code residing in this directory.
*
* This file along with xemaclite_example_util.c are utilized with the specific
* example code in the other source code files provided.
*
* These examples are designed to be compiled and utilized within the EDK
* standalone BSP development environment. The readme file contains more
* information on build requirements needed by these examples.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 2.00a ktn  04/13/09 First release
* 3.03a bss  09/01/12 Moved the declarations of RecvFrameLength
*		      TransmitComplete, EmacLiteInstance,
*		      TxFrame[XEL_MAX_FRAME_SIZE], RxFrame[XEL_MAX_FRAME_SIZE];
* 		      to xemaclite_example_util.c for fixing C++ compilation
*		      errors
* </pre>
*
******************************************************************************/
#جے_بنا_تعریف POLL_EG_H
#تعریف_کرو POLL_EG_H

#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت

/***************************** Include Files *********************************/


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

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#تعریف_کرو EMAC_DEVICE_ID		XPAR_EMACLITE_0_DEVICE_ID

/***************** Macros (Inline Functions) Definitions *********************/

/**************************** Type Definitions ******************************/

/************************** Function Prototypes *****************************/

/*
 * Utility functions implemented in xemaclite_example_util.c
 */
فراغ EmacLitePhyDelay(بنانشانی صحيح Seconds);
u32 EmacLitePhyDetect(XEmacLite *InstancePtr);
صحيح Emac_Lite_Enable_Phy_Loop_پٹھ(XEmacLite *InstancePtr, u32 Phy_پتہ);
صحيح Emac_Lite_Disable_Phy_Loop_پٹھ(XEmacLite *InstancePtr, u32 Phy_پتہ);

/************************** Variable Definitions ****************************/
/*
 * Set up valid local MAC addresses. This loop back test uses the LocalAddress
 * both as a source and destination MAC address.
 */

خارجي XEmacLite EmacLiteInstance;	/* Instance of the EmacLite */

/*
 * Buffers used for Transmission and Reception of Packets. These are declared
 * as global so that they are not a part of the stack.
 */
خارجي u8 Tx_چوکھٹا[XEL_MAX_چوکھٹا_ناپ];
خارجي u8 Rx_چوکھٹا[XEL_MAX_چوکھٹا_ناپ];

خارجي متطاير u32 Recv_چوکھٹا_لمائی;	/* Indicates the length of the
					 * Received packet
					 */
خارجي متطاير صحيح TransmitComplete;	/* Flag to indicate that the
					 * Transmission is complete
					 */
#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت /* POLL_EG_H */
