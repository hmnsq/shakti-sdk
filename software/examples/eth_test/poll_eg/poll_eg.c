/***************************************************************************
 * Project           			:  shakti devt board
 * Name of the file	     		:  btnled.c
 * Brief Description of file    :  Controls the led operation with help of button,gpio based.
 * Name of Author    	        :  Sathya Narayanan N & Abhinav Ramnath
 * Email ID                     :  sathya281@gmail.com  & abhinavramnath13@gmail.com 

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
@file pwminterrupt
@brief A application to demonstrate working of pwm interrupts
@detail This file contains an application to demonstrate the working of pwm
 interrupts. The interrupts are enabled for a pwm module. The pwm module is
 confiured for interrupt mode and pwm registers are setup appropriately.
 Once the pwm timer overflows, an interrupt is generated and it is handled
 by the isr.
*/

#అన్తర్భావ "gpio.h"
#అన్తర్భావ "uart.h"
#అన్తర్భావ "traps.h"
#అన్తర్భావ "platform.h"
#అన్తర్భావ "eth_driver.h"
#అన్తర్భావ "log.h"
#అన్తర్భావ "poll_eg.h"



/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#నిర్వచించు EMAC_DEVICE_ID			240
#నిర్వచించు ETH_పునాది_REG 0x44000
అస్థిర గుర్తులేని పూర్ణాంకం* eth_పునాది_reg = ETH_పునాది_REG;
/*
 * The Size of the Test Frame.
 */
#నిర్వచించు EMACLITE_TEST_చట్రం_కొలత	1000

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

పూర్ణాంకం EmacLitePolledExample(u16 DeviceId);

స్థిర పూర్ణాంకం Emac_Lite_Send_చట్రం(XEmacLite *InstancePtr, u32 Payload_కొలత);

స్థిర పూర్ణాంకం Emac_Lite_Recv_చట్రం(u32 Payload_కొలత);

బాహ్య u16 Xil_EndianSwap16(u16 దత్తాంశం);

/************************** Variable Definitions *****************************/

/*
 * Set up valid local and remote MAC addresses. This loop back test uses the
 * LocalAddress both as a source and destination MAC address.
 */
స్థిర u8 Local_చిరునామా[XEL_MAC_ADDR_కొలత] =
{
	0x00, 0x0A, 0x35, 0x01, 0x02, 0x03
};
స్థిర u8 Remote_చిరునామా[XEL_MAC_ADDR_కొలత] =
{
	0x00, 0x10, 0xa4, 0xb6, 0xfd, 0x09
};

బాహ్య XEmacLite_Config XEmac_Lite_Config_పట్టిక;

/************************** Variable Definitions *****************************/

/*
 * Instance of the driver
 */
స్థిర XEmacLite EmacLite;

/****************************************************************************/
/**
*
* This function is the main function of the EmacLite polled example.
*
* @param	None.
*
* @return	SUCCESS to indicate success, otherwise FAILURE .
*
* @note		None.
*
*****************************************************************************/
పూర్ణాంకం ప్రధాన()
{
	పూర్ణాంకం స్థితి_2;

	/*
	 * Run the EmacLite Polled example, specify the Device ID that is
	 * generated in xparameters.h.
	 */
	స్థితి_2 = EmacLitePolledExample(EMAC_DEVICE_ID);
	ఒకవేళ (స్థితి_2 != SUCCESS) {
		log_debug("Emaclite polled Example Failed\r\n");
		తిరిగి FAILURE;
	}

	log_debug("Successfully ran Emaclite polled Example\r\n");
	తిరిగి SUCCESS;
}


/*****************************************************************************/
/**
*
* The main entry point for the EmacLite driver example in polled mode.
*
* This function will transmit/receive the Ethernet frames and verify the
* data in the received frame (if the MDIO interface is configured in the
* EmacLite core).
* This function simply transmits a frame if the MDIO interface is not
* configured in the EmacLite core.
*
* @param	DeviceId is device ID of the XEmacLite Device , typically
*		XPAR_<EMAC_instance>_DEVICE_ID value from xparameters.h.
*
* @return	SUCCESS to indicate success, FAILURE otherwise.
*
* @note		None.
*
******************************************************************************/
పూర్ణాంకం EmacLitePolledExample(u16 DeviceId)
{
	పూర్ణాంకం స్థితి_2;
	XEmacLite *EmacLiteInstPtr = &EmacLiteInstance;
	u32 Phy_చిరునామా = 0;
	Recv_చట్రం_నిడివి = 0;
	XEmacLite_Config *ConfigPtr;

	ConfigPtr = &XEmac_Lite_Config_పట్టిక;
	ఒకవేళ (ConfigPtr == ఖాళీ) {
		తిరిగి -1;
	}
	ConfigPtr->పునాది_చిరునామా = (UINTPTR *) 0X44000;
	ConfigPtr->RxPingPong = XPAR_EMACLITE_0_RX_PING_PONG;
	ConfigPtr->MdioInclude = XPAR_EMACLITE_0_INCLUDE_MDIO;
	ConfigPtr->TxPingPong = XPAR_EMACLITE_0_TX_PING_PONG;
	log_debug("\n ConfigPtr: BaseAddress: %x", ConfigPtr->పునాది_చిరునామా);
	log_debug("\n ConfigPtr: DeviceId: %x", ConfigPtr->DeviceId);
	log_debug("\n ConfigPtr: TxPingPong: %x", ConfigPtr->TxPingPong);
	log_debug("\n ConfigPtr: RxPingPong: %x", ConfigPtr->RxPingPong);
	log_debug("\n ConfigPtr: MdioInclude: %x", ConfigPtr->MdioInclude);
	log_debug("\n ConfigPtr: Loopback: %x", ConfigPtr->Loopback);
	స్థితి_2 = XEmacLite_CfgInitialize(EmacLiteInstPtr,
					ConfigPtr,
					ConfigPtr->పునాది_చిరునామా);
	ఒకవేళ (స్థితి_2 != 0) {
		తిరిగి -1;
	}

	/*
	 * Set the MAC address.
	 */
	XEmac_Lite_సమితి_Mac_చిరునామా(EmacLiteInstPtr, Local_చిరునామా);

	/*
	 * Check if there is a TX buffer available, if there isn't it is an
	 * error.
	 */
	ఒకవేళ (XEmac_Lite_Tx_బఫరు_అందుబాటు(EmacLiteInstPtr) != TRUE) {
		తిరిగి FAILURE;
	}

	/*
	 * If the MDIO is configured in the device.
	 */
	ఒకవేళ (XEmacLite_IsMdioConfigured(EmacLiteInstPtr)) {
		/*
		 * Detect the PHY device and enable the MAC Loop back
		 * in the PHY.
		 */
		Phy_చిరునామా = EmacLitePhyDetect(EmacLiteInstPtr);
		స్థితి_2 = Emac_Lite_Enable_Phy_Loop_వెనుక(EmacLiteInstPtr,
							 Phy_చిరునామా);
		ఒకవేళ (స్థితి_2 != SUCCESS) {
			తిరిగి FAILURE;
		}
	}

	/*
	 * Empty any existing receive frames.
	 */
	XEmacLite_FlushReceive(EmacLiteInstPtr);

	/*
	 * Reset the receive frame length to zero.
	 */
	Recv_చట్రం_నిడివి = 0;
	స్థితి_2 = Emac_Lite_Send_చట్రం(EmacLiteInstPtr, EMACLITE_TEST_చట్రం_కొలత);
	ఒకవేళ (స్థితి_2 != SUCCESS) {
		ఒకవేళ (XEmacLite_IsMdioConfigured(EmacLiteInstPtr)) {
			/*
			 * Disable the MAC Loop back in the PHY.
			 */
			Emac_Lite_Disable_Phy_Loop_వెనుక(EmacLiteInstPtr,
							 Phy_చిరునామా);
			తిరిగి FAILURE;
		}
	}

	/*
	 * If the MDIO is not configured in the core then return SUCCESS
	 * as the frame has been transmitted.
	 */
	ఒకవేళ (!XEmacLite_IsMdioConfigured(EmacLiteInstPtr)) {
		తిరిగి SUCCESS;
	}


	/*
	 * Poll for receive packet.
	 */
	అయితే ((అస్థిర u32)Recv_చట్రం_నిడివి == 0)  {
		Recv_చట్రం_నిడివి = XEmacLite_Recv(EmacLiteInstPtr,
						(u8 *)Rx_చట్రం);
	}

	/*
	 * Check the received frame.
	 */
	స్థితి_2 = Emac_Lite_Recv_చట్రం(EMACLITE_TEST_చట్రం_కొలత);
	ఒకవేళ ((స్థితి_2 != SUCCESS) && (స్థితి_2 != NO_దత్తాంశం)) {
		/*
		 * Disable the MAC Loop back in the PHY.
		 */
		Emac_Lite_Disable_Phy_Loop_వెనుక(EmacLiteInstPtr, Phy_చిరునామా);
		తిరిగి FAILURE;
	}


	/*
	 * Disable the MAC Loop back in the PHY.
	 */
	Emac_Lite_Disable_Phy_Loop_వెనుక(EmacLiteInstPtr, Phy_చిరునామా);

	తిరిగి SUCCESS;
}

/******************************************************************************/
/**
*
* This function sends a frame of given size.
*
* @param	XEmacInstancePtr is a pointer to the XEmacLite instance.
* @param	PayloadSize is the size of the frame to create. The size only
*		reflects the payload size, it does not include the Ethernet
*		header size (14 bytes) nor the Ethernet CRC size (4 bytes).
*
* @return	SUCCESS if successful, else a driver-specific return code.
*
* @note		None.
*
******************************************************************************/
స్థిర పూర్ణాంకం Emac_Lite_Send_చట్రం(XEmacLite *InstancePtr, u32 Payload_కొలత)
{
	u8 *చట్రం_Ptr;
	పూర్ణాంకం సూచీ;
	చట్రం_Ptr = (u8 *)Tx_చట్రం;

	/*
	 * Set up the destination address as the local address for
	 * Phy Loopback.
	 */
	ఒకవేళ (XEmacLite_IsMdioConfigured(InstancePtr)) {

		*చట్రం_Ptr++ = Local_చిరునామా[0];
		*చట్రం_Ptr++ = Local_చిరునామా[1];
		*చట్రం_Ptr++ = Local_చిరునామా[2];
		*చట్రం_Ptr++ = Local_చిరునామా[3];
		*చట్రం_Ptr++ = Local_చిరునామా[4];
		*చట్రం_Ptr++ = Local_చిరునామా[5];
	} లేకపోతే {
		/*
		 * Fill in the valid Destination MAC address if
		 * the Loopback is not enabled.
		 */
		*చట్రం_Ptr++ = Remote_చిరునామా[0];
		*చట్రం_Ptr++ = Remote_చిరునామా[1];
		*చట్రం_Ptr++ = Remote_చిరునామా[2];
		*చట్రం_Ptr++ = Remote_చిరునామా[3];
		*చట్రం_Ptr++ = Remote_చిరునామా[4];
		*చట్రం_Ptr++ = Remote_చిరునామా[5];
	}

	/*
	 * Fill in the source MAC address.
	 */
	*చట్రం_Ptr++ = Local_చిరునామా[0];
	*చట్రం_Ptr++ = Local_చిరునామా[1];
	*చట్రం_Ptr++ = Local_చిరునామా[2];
	*చట్రం_Ptr++ = Local_చిరునామా[3];
	*చట్రం_Ptr++ = Local_చిరునామా[4];
	*చట్రం_Ptr++ = Local_చిరునామా[5];

	/*
	 * Set up the type/length field - be sure its in network order.
	 */
    *((u16 *)చట్రం_Ptr) = Xil_EndianSwap16(Payload_కొలత);
	చట్రం_Ptr++;
	చట్రం_Ptr++;

	/*
	 * Now fill in the data field with known values so we can verify them
	 * on receive.
	 */
	కొరకు (సూచీ = 0; సూచీ < Payload_కొలత; సూచీ++) {
		*చట్రం_Ptr++ = (u8)సూచీ;
	}

	/*
	 * Now send the frame.
	 */
	తిరిగి XEmacLite_Send(InstancePtr, (u8 *)Tx_చట్రం,
				Payload_కొలత + XEL_శీర్షిక_కొలత);

}

/******************************************************************************/
/**
*
* This function receives a frame of given size. This function assumes interrupt
* mode, receives the frame and verifies its contents.
*
* @param	PayloadSize is the size of the frame to receive.
*		The size only reflects the payload size, it does not include the
*		Ethernet header size (14 bytes) nor the Ethernet CRC size (4
*		bytes).
*
* @return	SUCCESS if successful, a driver-specific return code if not.
*
* @note		None.
*
******************************************************************************/
స్థిర పూర్ణాంకం Emac_Lite_Recv_చట్రం(u32 Payload_కొలత)
{
	u8 *చట్రం_Ptr;

	/*
	 * This assumes MAC does not strip padding or CRC.
	 */
	ఒకవేళ (Recv_చట్రం_నిడివి != 0) {
		పూర్ణాంకం సూచీ;

		/*
		 * Verify length, which should be the payload size.
		 */
		ఒకవేళ ((Recv_చట్రం_నిడివి- (XEL_శీర్షిక_కొలత + XEL_FCS_కొలత)) !=
				Payload_కొలత) {
			తిరిగి XST_LOOPBACK_ERROR;
		}

		/*
		 * Verify the contents of the Received Frame.
		 */
		చట్రం_Ptr = (u8 *)Rx_చట్రం;
		చట్రం_Ptr += XEL_శీర్షిక_కొలత;	/* Get past the header */

		కొరకు (సూచీ = 0; సూచీ < Payload_కొలత; సూచీ++) {
			ఒకవేళ (*చట్రం_Ptr++ != (u8)సూచీ) {
				తిరిగి XST_LOOPBACK_ERROR;
			}
		}
	}

	తిరిగి SUCCESS;
}
