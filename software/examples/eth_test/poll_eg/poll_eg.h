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
#నిర్వచితం_కాకపోతే POLL_EG_H
#నిర్వచించు POLL_EG_H

#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు

/***************************** Include Files *********************************/


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

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#నిర్వచించు EMAC_DEVICE_ID		XPAR_EMACLITE_0_DEVICE_ID

/***************** Macros (Inline Functions) Definitions *********************/

/**************************** Type Definitions ******************************/

/************************** Function Prototypes *****************************/

/*
 * Utility functions implemented in xemaclite_example_util.c
 */
శూన్య EmacLitePhyDelay(గుర్తులేని పూర్ణాంకం Seconds);
u32 EmacLitePhyDetect(XEmacLite *InstancePtr);
పూర్ణాంకం Emac_Lite_Enable_Phy_Loop_వెనుక(XEmacLite *InstancePtr, u32 Phy_చిరునామా);
పూర్ణాంకం Emac_Lite_Disable_Phy_Loop_వెనుక(XEmacLite *InstancePtr, u32 Phy_చిరునామా);

/************************** Variable Definitions ****************************/
/*
 * Set up valid local MAC addresses. This loop back test uses the LocalAddress
 * both as a source and destination MAC address.
 */

బాహ్య XEmacLite EmacLiteInstance;	/* Instance of the EmacLite */

/*
 * Buffers used for Transmission and Reception of Packets. These are declared
 * as global so that they are not a part of the stack.
 */
బాహ్య u8 Tx_చట్రం[XEL_MAX_చట్రం_కొలత];
బాహ్య u8 Rx_చట్రం[XEL_MAX_చట్రం_కొలత];

బాహ్య అస్థిర u32 Recv_చట్రం_నిడివి;	/* Indicates the length of the
					 * Received packet
					 */
బాహ్య అస్థిర పూర్ణాంకం TransmitComplete;	/* Flag to indicate that the
					 * Transmission is complete
					 */
#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు /* POLL_EG_H */
