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
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ POLL_EG_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ POLL_EG_H

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ

/***************************** Include Files *********************************/


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

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EMAC_DEVICE_ID		XPAR_EMACLITE_0_DEVICE_ID

/***************** Macros (Inline Functions) Definitions *********************/

/**************************** Type Definitions ******************************/

/************************** Function Prototypes *****************************/

/*
 * Utility functions implemented in xemaclite_example_util.c
 */
ਖਾਲੀ EmacLitePhyDelay(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ Seconds);
u32 EmacLitePhyDetect(XEmacLite *InstancePtr);
ਪੂਰਨ Emac_Lite_Enable_Phy_Loop_ਪਿੱਠ(XEmacLite *InstancePtr, u32 Phy_ਪਤਾ);
ਪੂਰਨ Emac_Lite_Disable_Phy_Loop_ਪਿੱਠ(XEmacLite *InstancePtr, u32 Phy_ਪਤਾ);

/************************** Variable Definitions ****************************/
/*
 * Set up valid local MAC addresses. This loop back test uses the LocalAddress
 * both as a source and destination MAC address.
 */

ਬਾਹਰੀ XEmacLite EmacLiteInstance;	/* Instance of the EmacLite */

/*
 * Buffers used for Transmission and Reception of Packets. These are declared
 * as global so that they are not a part of the stack.
 */
ਬਾਹਰੀ u8 Tx_ਚੌਖਟਾ[XEL_MAX_ਚੌਖਟਾ_ਮਾਪ];
ਬਾਹਰੀ u8 Rx_ਚੌਖਟਾ[XEL_MAX_ਚੌਖਟਾ_ਮਾਪ];

ਬਾਹਰੀ ਅਸਥਿਰ u32 Recv_ਚੌਖਟਾ_ਲੰਮਾਈ;	/* Indicates the length of the
					 * Received packet
					 */
ਬਾਹਰੀ ਅਸਥਿਰ ਪੂਰਨ TransmitComplete;	/* Flag to indicate that the
					 * Transmission is complete
					 */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ /* POLL_EG_H */
