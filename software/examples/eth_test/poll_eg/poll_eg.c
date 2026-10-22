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

#अन्तर्भाव "gpio.h"
#अन्तर्भाव "uart.h"
#अन्तर्भाव "traps.h"
#अन्तर्भाव "platform.h"
#अन्तर्भाव "eth_driver.h"
#अन्तर्भाव "log.h"
#अन्तर्भाव "poll_eg.h"



/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#परिभाषय EMAC_DEVICE_ID			240
#परिभाषय ETH_आधारः_REG 0x44000
चञ्चल अचिह्नित पूर्णाङ्क* eth_आधारः_reg = ETH_आधारः_REG;
/*
 * The Size of the Test Frame.
 */
#परिभाषय EMACLITE_TEST_FRAME_आकार	1000

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

पूर्णाङ्क EmacLitePolledExample(u16 DeviceId);

स्थिर पूर्णाङ्क EmacLiteSendFrame(XEmacLite *InstancePtr, u32 Payload_आकार);

स्थिर पूर्णाङ्क EmacLiteRecvFrame(u32 Payload_आकार);

बाह्य u16 Xil_EndianSwap16(u16 दत्त);

/************************** Variable Definitions *****************************/

/*
 * Set up valid local and remote MAC addresses. This loop back test uses the
 * LocalAddress both as a source and destination MAC address.
 */
स्थिर u8 Local_स्थानाङ्कः[XEL_MAC_ADDR_आकार] =
{
	0x00, 0x0A, 0x35, 0x01, 0x02, 0x03
};
स्थिर u8 Remote_स्थानाङ्कः[XEL_MAC_ADDR_आकार] =
{
	0x00, 0x10, 0xa4, 0xb6, 0xfd, 0x09
};

बाह्य XEmacLite_Config XEmac_Lite_Config_सारणी;

/************************** Variable Definitions *****************************/

/*
 * Instance of the driver
 */
स्थिर XEmacLite EmacLite;

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
पूर्णाङ्क मुख्यम्()
{
	पूर्णाङ्क स्थितिः;

	/*
	 * Run the EmacLite Polled example, specify the Device ID that is
	 * generated in xparameters.h.
	 */
	स्थितिः = EmacLitePolledExample(EMAC_DEVICE_ID);
	यदि (स्थितिः != SUCCESS) {
		log_debug("Emaclite polled Example Failed\r\n");
		प्रत्यागम FAILURE;
	}

	log_debug("Successfully ran Emaclite polled Example\r\n");
	प्रत्यागम SUCCESS;
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
पूर्णाङ्क EmacLitePolledExample(u16 DeviceId)
{
	पूर्णाङ्क स्थितिः;
	XEmacLite *EmacLiteInstPtr = &EmacLiteInstance;
	u32 Phy_स्थानाङ्कः = 0;
	Recv_Frame_दीर्घता = 0;
	XEmacLite_Config *ConfigPtr;

	ConfigPtr = &XEmac_Lite_Config_सारणी;
	यदि (ConfigPtr == रिक्त) {
		प्रत्यागम -1;
	}
	ConfigPtr->आधारः_स्थानाङ्कः = (UINTPTR *) 0X44000;
	ConfigPtr->RxPingPong = XPAR_EMACLITE_0_RX_PING_PONG;
	ConfigPtr->MdioInclude = XPAR_EMACLITE_0_INCLUDE_MDIO;
	ConfigPtr->TxPingPong = XPAR_EMACLITE_0_TX_PING_PONG;
	log_debug("\n ConfigPtr: BaseAddress: %x", ConfigPtr->आधारः_स्थानाङ्कः);
	log_debug("\n ConfigPtr: DeviceId: %x", ConfigPtr->DeviceId);
	log_debug("\n ConfigPtr: TxPingPong: %x", ConfigPtr->TxPingPong);
	log_debug("\n ConfigPtr: RxPingPong: %x", ConfigPtr->RxPingPong);
	log_debug("\n ConfigPtr: MdioInclude: %x", ConfigPtr->MdioInclude);
	log_debug("\n ConfigPtr: Loopback: %x", ConfigPtr->Loopback);
	स्थितिः = XEmacLite_CfgInitialize(EmacLiteInstPtr,
					ConfigPtr,
					ConfigPtr->आधारः_स्थानाङ्कः);
	यदि (स्थितिः != 0) {
		प्रत्यागम -1;
	}

	/*
	 * Set the MAC address.
	 */
	XEmac_Lite_समुच्चयः_Mac_स्थानाङ्कः(EmacLiteInstPtr, Local_स्थानाङ्कः);

	/*
	 * Check if there is a TX buffer available, if there isn't it is an
	 * error.
	 */
	यदि (XEmac_Lite_Tx_बफर_उपलब्धम्(EmacLiteInstPtr) != TRUE) {
		प्रत्यागम FAILURE;
	}

	/*
	 * If the MDIO is configured in the device.
	 */
	यदि (XEmacLite_IsMdioConfigured(EmacLiteInstPtr)) {
		/*
		 * Detect the PHY device and enable the MAC Loop back
		 * in the PHY.
		 */
		Phy_स्थानाङ्कः = EmacLitePhyDetect(EmacLiteInstPtr);
		स्थितिः = Emac_Lite_Enable_Phy_Loop_पृष्ठभागः(EmacLiteInstPtr,
							 Phy_स्थानाङ्कः);
		यदि (स्थितिः != SUCCESS) {
			प्रत्यागम FAILURE;
		}
	}

	/*
	 * Empty any existing receive frames.
	 */
	XEmacLite_FlushReceive(EmacLiteInstPtr);

	/*
	 * Reset the receive frame length to zero.
	 */
	Recv_Frame_दीर्घता = 0;
	स्थितिः = EmacLiteSendFrame(EmacLiteInstPtr, EMACLITE_TEST_FRAME_आकार);
	यदि (स्थितिः != SUCCESS) {
		यदि (XEmacLite_IsMdioConfigured(EmacLiteInstPtr)) {
			/*
			 * Disable the MAC Loop back in the PHY.
			 */
			Emac_Lite_Disable_Phy_Loop_पृष्ठभागः(EmacLiteInstPtr,
							 Phy_स्थानाङ्कः);
			प्रत्यागम FAILURE;
		}
	}

	/*
	 * If the MDIO is not configured in the core then return SUCCESS
	 * as the frame has been transmitted.
	 */
	यदि (!XEmacLite_IsMdioConfigured(EmacLiteInstPtr)) {
		प्रत्यागम SUCCESS;
	}


	/*
	 * Poll for receive packet.
	 */
	यावत् ((चञ्चल u32)Recv_Frame_दीर्घता == 0)  {
		Recv_Frame_दीर्घता = XEmacLite_Recv(EmacLiteInstPtr,
						(u8 *)RxFrame);
	}

	/*
	 * Check the received frame.
	 */
	स्थितिः = EmacLiteRecvFrame(EMACLITE_TEST_FRAME_आकार);
	यदि ((स्थितिः != SUCCESS) && (स्थितिः != NO_दत्त)) {
		/*
		 * Disable the MAC Loop back in the PHY.
		 */
		Emac_Lite_Disable_Phy_Loop_पृष्ठभागः(EmacLiteInstPtr, Phy_स्थानाङ्कः);
		प्रत्यागम FAILURE;
	}


	/*
	 * Disable the MAC Loop back in the PHY.
	 */
	Emac_Lite_Disable_Phy_Loop_पृष्ठभागः(EmacLiteInstPtr, Phy_स्थानाङ्कः);

	प्रत्यागम SUCCESS;
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
स्थिर पूर्णाङ्क EmacLiteSendFrame(XEmacLite *InstancePtr, u32 Payload_आकार)
{
	u8 *FramePtr;
	पूर्णाङ्क सूचकांक;
	FramePtr = (u8 *)TxFrame;

	/*
	 * Set up the destination address as the local address for
	 * Phy Loopback.
	 */
	यदि (XEmacLite_IsMdioConfigured(InstancePtr)) {

		*FramePtr++ = Local_स्थानाङ्कः[0];
		*FramePtr++ = Local_स्थानाङ्कः[1];
		*FramePtr++ = Local_स्थानाङ्कः[2];
		*FramePtr++ = Local_स्थानाङ्कः[3];
		*FramePtr++ = Local_स्थानाङ्कः[4];
		*FramePtr++ = Local_स्थानाङ्कः[5];
	} अन्यथा {
		/*
		 * Fill in the valid Destination MAC address if
		 * the Loopback is not enabled.
		 */
		*FramePtr++ = Remote_स्थानाङ्कः[0];
		*FramePtr++ = Remote_स्थानाङ्कः[1];
		*FramePtr++ = Remote_स्थानाङ्कः[2];
		*FramePtr++ = Remote_स्थानाङ्कः[3];
		*FramePtr++ = Remote_स्थानाङ्कः[4];
		*FramePtr++ = Remote_स्थानाङ्कः[5];
	}

	/*
	 * Fill in the source MAC address.
	 */
	*FramePtr++ = Local_स्थानाङ्कः[0];
	*FramePtr++ = Local_स्थानाङ्कः[1];
	*FramePtr++ = Local_स्थानाङ्कः[2];
	*FramePtr++ = Local_स्थानाङ्कः[3];
	*FramePtr++ = Local_स्थानाङ्कः[4];
	*FramePtr++ = Local_स्थानाङ्कः[5];

	/*
	 * Set up the type/length field - be sure its in network order.
	 */
    *((u16 *)FramePtr) = Xil_EndianSwap16(Payload_आकार);
	FramePtr++;
	FramePtr++;

	/*
	 * Now fill in the data field with known values so we can verify them
	 * on receive.
	 */
	प्रति (सूचकांक = 0; सूचकांक < Payload_आकार; सूचकांक++) {
		*FramePtr++ = (u8)सूचकांक;
	}

	/*
	 * Now send the frame.
	 */
	प्रत्यागम XEmacLite_Send(InstancePtr, (u8 *)TxFrame,
				Payload_आकार + XEL_शीर्षकम्_आकार);

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
स्थिर पूर्णाङ्क EmacLiteRecvFrame(u32 Payload_आकार)
{
	u8 *FramePtr;

	/*
	 * This assumes MAC does not strip padding or CRC.
	 */
	यदि (Recv_Frame_दीर्घता != 0) {
		पूर्णाङ्क सूचकांक;

		/*
		 * Verify length, which should be the payload size.
		 */
		यदि ((Recv_Frame_दीर्घता- (XEL_शीर्षकम्_आकार + XEL_FCS_आकार)) !=
				Payload_आकार) {
			प्रत्यागम XST_LOOPBACK_ERROR;
		}

		/*
		 * Verify the contents of the Received Frame.
		 */
		FramePtr = (u8 *)RxFrame;
		FramePtr += XEL_शीर्षकम्_आकार;	/* Get past the header */

		प्रति (सूचकांक = 0; सूचकांक < Payload_आकार; सूचकांक++) {
			यदि (*FramePtr++ != (u8)सूचकांक) {
				प्रत्यागम XST_LOOPBACK_ERROR;
			}
		}
	}

	प्रत्यागम SUCCESS;
}
