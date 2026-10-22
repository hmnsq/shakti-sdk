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
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ POLL_EG_H
#ವ್ಯಾಖ್ಯಾನಿಸು POLL_EG_H

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ

/***************************** Include Files *********************************/


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

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು EMAC_DEVICE_ID		XPAR_EMACLITE_0_DEVICE_ID

/***************** Macros (Inline Functions) Definitions *********************/

/**************************** Type Definitions ******************************/

/************************** Function Prototypes *****************************/

/*
 * Utility functions implemented in xemaclite_example_util.c
 */
ಶೂನ್ಯ EmacLitePhyDelay(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ Seconds);
u32 EmacLitePhyDetect(XEmacLite *InstancePtr);
ಪೂರ್ಣಾಂಕ Emac_Lite_Enable_Phy_Loop_ಹಿಂಭಾಗ(XEmacLite *InstancePtr, u32 Phy_ವಿಳಾಸ);
ಪೂರ್ಣಾಂಕ Emac_Lite_Disable_Phy_Loop_ಹಿಂಭಾಗ(XEmacLite *InstancePtr, u32 Phy_ವಿಳಾಸ);

/************************** Variable Definitions ****************************/
/*
 * Set up valid local MAC addresses. This loop back test uses the LocalAddress
 * both as a source and destination MAC address.
 */

ಬಾಹ್ಯ XEmacLite EmacLiteInstance;	/* Instance of the EmacLite */

/*
 * Buffers used for Transmission and Reception of Packets. These are declared
 * as global so that they are not a part of the stack.
 */
ಬಾಹ್ಯ u8 Tx_ಚೌಕಟ್ಟು[XEL_MAX_ಚೌಕಟ್ಟು_ಗಾತ್ರ];
ಬಾಹ್ಯ u8 Rx_ಚೌಕಟ್ಟು[XEL_MAX_ಚೌಕಟ್ಟು_ಗಾತ್ರ];

ಬಾಹ್ಯ ಅಸ್ಥಿರ u32 Recv_ಚೌಕಟ್ಟು_ಉದ್ದಳತೆ;	/* Indicates the length of the
					 * Received packet
					 */
ಬಾಹ್ಯ ಅಸ್ಥಿರ ಪೂರ್ಣಾಂಕ TransmitComplete;	/* Flag to indicate that the
					 * Transmission is complete
					 */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ /* POLL_EG_H */
