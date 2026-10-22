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
#यदि_अपरिभाषितम् POLL_EG_H
#परिभाषय POLL_EG_H

#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः

/***************************** Include Files *********************************/


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

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#परिभाषय EMAC_DEVICE_ID		XPAR_EMACLITE_0_DEVICE_ID

/***************** Macros (Inline Functions) Definitions *********************/

/**************************** Type Definitions ******************************/

/************************** Function Prototypes *****************************/

/*
 * Utility functions implemented in xemaclite_example_util.c
 */
शून्य EmacLitePhyDelay(अचिह्नित पूर्णाङ्क Seconds);
u32 EmacLitePhyDetect(XEmacLite *InstancePtr);
पूर्णाङ्क Emac_Lite_Enable_Phy_Loop_पृष्ठभागः(XEmacLite *InstancePtr, u32 Phy_स्थानाङ्कः);
पूर्णाङ्क Emac_Lite_Disable_Phy_Loop_पृष्ठभागः(XEmacLite *InstancePtr, u32 Phy_स्थानाङ्कः);

/************************** Variable Definitions ****************************/
/*
 * Set up valid local MAC addresses. This loop back test uses the LocalAddress
 * both as a source and destination MAC address.
 */

बाह्य XEmacLite EmacLiteInstance;	/* Instance of the EmacLite */

/*
 * Buffers used for Transmission and Reception of Packets. These are declared
 * as global so that they are not a part of the stack.
 */
बाह्य u8 TxFrame[XEL_MAX_FRAME_आकार];
बाह्य u8 RxFrame[XEL_MAX_FRAME_आकार];

बाह्य चञ्चल u32 Recv_Frame_दीर्घता;	/* Indicates the length of the
					 * Received packet
					 */
बाह्य चञ्चल पूर्णाङ्क TransmitComplete;	/* Flag to indicate that the
					 * Transmission is complete
					 */
#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः /* POLL_EG_H */
