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

#ਅਨ੍ਤਰ੍ਭਾਵ "gpio.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "uart.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "traps.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "platform.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "eth_driver.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "poll_eg.h"



/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EMAC_DEVICE_ID			240
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ETH_ਅਧਾਰ_REG 0x44000
ਅਸਥਿਰ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ* eth_ਅਧਾਰ_reg = ETH_ਅਧਾਰ_REG;
/*
 * The Size of the Test Frame.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EMACLITE_TEST_ਚੌਖਟਾ_ਮਾਪ	1000

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

ਪੂਰਨ EmacLitePolledExample(u16 DeviceId);

ਸਥਿਰ ਪੂਰਨ Emac_Lite_Send_ਚੌਖਟਾ(XEmacLite *InstancePtr, u32 Payload_ਮਾਪ);

ਸਥਿਰ ਪੂਰਨ Emac_Lite_Recv_ਚੌਖਟਾ(u32 Payload_ਮਾਪ);

ਬਾਹਰੀ u16 Xil_EndianSwap16(u16 ਅੰਕੜੇ);

/************************** Variable Definitions *****************************/

/*
 * Set up valid local and remote MAC addresses. This loop back test uses the
 * LocalAddress both as a source and destination MAC address.
 */
ਸਥਿਰ u8 Local_ਪਤਾ[XEL_MAC_ADDR_ਮਾਪ] =
{
	0x00, 0x0A, 0x35, 0x01, 0x02, 0x03
};
ਸਥਿਰ u8 Remote_ਪਤਾ[XEL_MAC_ADDR_ਮਾਪ] =
{
	0x00, 0x10, 0xa4, 0xb6, 0xfd, 0x09
};

ਬਾਹਰੀ XEmacLite_Config XEmac_Lite_Config_ਸਾਰਣੀ;

/************************** Variable Definitions *****************************/

/*
 * Instance of the driver
 */
ਸਥਿਰ XEmacLite EmacLite;

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
ਪੂਰਨ ਮੁੱਖ()
{
	ਪੂਰਨ ਸਥਿਤੀ;

	/*
	 * Run the EmacLite Polled example, specify the Device ID that is
	 * generated in xparameters.h.
	 */
	ਸਥਿਤੀ = EmacLitePolledExample(EMAC_DEVICE_ID);
	ਜੇ (ਸਥਿਤੀ != SUCCESS) {
		log_debug("Emaclite polled Example Failed\r\n");
		ਵਾਪਸ FAILURE;
	}

	log_debug("Successfully ran Emaclite polled Example\r\n");
	ਵਾਪਸ SUCCESS;
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
ਪੂਰਨ EmacLitePolledExample(u16 DeviceId)
{
	ਪੂਰਨ ਸਥਿਤੀ;
	XEmacLite *EmacLiteInstPtr = &EmacLiteInstance;
	u32 Phy_ਪਤਾ = 0;
	Recv_ਚੌਖਟਾ_ਲੰਮਾਈ = 0;
	XEmacLite_Config *ConfigPtr;

	ConfigPtr = &XEmac_Lite_Config_ਸਾਰਣੀ;
	ਜੇ (ConfigPtr == ਨਿਰਾ) {
		ਵਾਪਸ -1;
	}
	ConfigPtr->ਅਧਾਰ_ਪਤਾ = (UINTPTR *) 0X44000;
	ConfigPtr->RxPingPong = XPAR_EMACLITE_0_RX_PING_PONG;
	ConfigPtr->MdioInclude = XPAR_EMACLITE_0_INCLUDE_MDIO;
	ConfigPtr->TxPingPong = XPAR_EMACLITE_0_TX_PING_PONG;
	log_debug("\n ConfigPtr: BaseAddress: %x", ConfigPtr->ਅਧਾਰ_ਪਤਾ);
	log_debug("\n ConfigPtr: DeviceId: %x", ConfigPtr->DeviceId);
	log_debug("\n ConfigPtr: TxPingPong: %x", ConfigPtr->TxPingPong);
	log_debug("\n ConfigPtr: RxPingPong: %x", ConfigPtr->RxPingPong);
	log_debug("\n ConfigPtr: MdioInclude: %x", ConfigPtr->MdioInclude);
	log_debug("\n ConfigPtr: Loopback: %x", ConfigPtr->Loopback);
	ਸਥਿਤੀ = XEmacLite_CfgInitialize(EmacLiteInstPtr,
					ConfigPtr,
					ConfigPtr->ਅਧਾਰ_ਪਤਾ);
	ਜੇ (ਸਥਿਤੀ != 0) {
		ਵਾਪਸ -1;
	}

	/*
	 * Set the MAC address.
	 */
	XEmac_Lite_ਸੈੱਟ_Mac_ਪਤਾ(EmacLiteInstPtr, Local_ਪਤਾ);

	/*
	 * Check if there is a TX buffer available, if there isn't it is an
	 * error.
	 */
	ਜੇ (XEmac_Lite_Tx_ਬਫਰ_ਉਪਲਬਧ(EmacLiteInstPtr) != TRUE) {
		ਵਾਪਸ FAILURE;
	}

	/*
	 * If the MDIO is configured in the device.
	 */
	ਜੇ (XEmacLite_IsMdioConfigured(EmacLiteInstPtr)) {
		/*
		 * Detect the PHY device and enable the MAC Loop back
		 * in the PHY.
		 */
		Phy_ਪਤਾ = EmacLitePhyDetect(EmacLiteInstPtr);
		ਸਥਿਤੀ = Emac_Lite_Enable_Phy_Loop_ਪਿੱਠ(EmacLiteInstPtr,
							 Phy_ਪਤਾ);
		ਜੇ (ਸਥਿਤੀ != SUCCESS) {
			ਵਾਪਸ FAILURE;
		}
	}

	/*
	 * Empty any existing receive frames.
	 */
	XEmacLite_FlushReceive(EmacLiteInstPtr);

	/*
	 * Reset the receive frame length to zero.
	 */
	Recv_ਚੌਖਟਾ_ਲੰਮਾਈ = 0;
	ਸਥਿਤੀ = Emac_Lite_Send_ਚੌਖਟਾ(EmacLiteInstPtr, EMACLITE_TEST_ਚੌਖਟਾ_ਮਾਪ);
	ਜੇ (ਸਥਿਤੀ != SUCCESS) {
		ਜੇ (XEmacLite_IsMdioConfigured(EmacLiteInstPtr)) {
			/*
			 * Disable the MAC Loop back in the PHY.
			 */
			Emac_Lite_Disable_Phy_Loop_ਪਿੱਠ(EmacLiteInstPtr,
							 Phy_ਪਤਾ);
			ਵਾਪਸ FAILURE;
		}
	}

	/*
	 * If the MDIO is not configured in the core then return SUCCESS
	 * as the frame has been transmitted.
	 */
	ਜੇ (!XEmacLite_IsMdioConfigured(EmacLiteInstPtr)) {
		ਵਾਪਸ SUCCESS;
	}


	/*
	 * Poll for receive packet.
	 */
	ਜਦੋਂ ((ਅਸਥਿਰ u32)Recv_ਚੌਖਟਾ_ਲੰਮਾਈ == 0)  {
		Recv_ਚੌਖਟਾ_ਲੰਮਾਈ = XEmacLite_Recv(EmacLiteInstPtr,
						(u8 *)Rx_ਚੌਖਟਾ);
	}

	/*
	 * Check the received frame.
	 */
	ਸਥਿਤੀ = Emac_Lite_Recv_ਚੌਖਟਾ(EMACLITE_TEST_ਚੌਖਟਾ_ਮਾਪ);
	ਜੇ ((ਸਥਿਤੀ != SUCCESS) && (ਸਥਿਤੀ != NO_ਅੰਕੜੇ)) {
		/*
		 * Disable the MAC Loop back in the PHY.
		 */
		Emac_Lite_Disable_Phy_Loop_ਪਿੱਠ(EmacLiteInstPtr, Phy_ਪਤਾ);
		ਵਾਪਸ FAILURE;
	}


	/*
	 * Disable the MAC Loop back in the PHY.
	 */
	Emac_Lite_Disable_Phy_Loop_ਪਿੱਠ(EmacLiteInstPtr, Phy_ਪਤਾ);

	ਵਾਪਸ SUCCESS;
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
ਸਥਿਰ ਪੂਰਨ Emac_Lite_Send_ਚੌਖਟਾ(XEmacLite *InstancePtr, u32 Payload_ਮਾਪ)
{
	u8 *ਚੌਖਟਾ_Ptr;
	ਪੂਰਨ ਸੂਚਕਾਂਕ;
	ਚੌਖਟਾ_Ptr = (u8 *)Tx_ਚੌਖਟਾ;

	/*
	 * Set up the destination address as the local address for
	 * Phy Loopback.
	 */
	ਜੇ (XEmacLite_IsMdioConfigured(InstancePtr)) {

		*ਚੌਖਟਾ_Ptr++ = Local_ਪਤਾ[0];
		*ਚੌਖਟਾ_Ptr++ = Local_ਪਤਾ[1];
		*ਚੌਖਟਾ_Ptr++ = Local_ਪਤਾ[2];
		*ਚੌਖਟਾ_Ptr++ = Local_ਪਤਾ[3];
		*ਚੌਖਟਾ_Ptr++ = Local_ਪਤਾ[4];
		*ਚੌਖਟਾ_Ptr++ = Local_ਪਤਾ[5];
	} ਨਹੀਂਤਾਂ {
		/*
		 * Fill in the valid Destination MAC address if
		 * the Loopback is not enabled.
		 */
		*ਚੌਖਟਾ_Ptr++ = Remote_ਪਤਾ[0];
		*ਚੌਖਟਾ_Ptr++ = Remote_ਪਤਾ[1];
		*ਚੌਖਟਾ_Ptr++ = Remote_ਪਤਾ[2];
		*ਚੌਖਟਾ_Ptr++ = Remote_ਪਤਾ[3];
		*ਚੌਖਟਾ_Ptr++ = Remote_ਪਤਾ[4];
		*ਚੌਖਟਾ_Ptr++ = Remote_ਪਤਾ[5];
	}

	/*
	 * Fill in the source MAC address.
	 */
	*ਚੌਖਟਾ_Ptr++ = Local_ਪਤਾ[0];
	*ਚੌਖਟਾ_Ptr++ = Local_ਪਤਾ[1];
	*ਚੌਖਟਾ_Ptr++ = Local_ਪਤਾ[2];
	*ਚੌਖਟਾ_Ptr++ = Local_ਪਤਾ[3];
	*ਚੌਖਟਾ_Ptr++ = Local_ਪਤਾ[4];
	*ਚੌਖਟਾ_Ptr++ = Local_ਪਤਾ[5];

	/*
	 * Set up the type/length field - be sure its in network order.
	 */
    *((u16 *)ਚੌਖਟਾ_Ptr) = Xil_EndianSwap16(Payload_ਮਾਪ);
	ਚੌਖਟਾ_Ptr++;
	ਚੌਖਟਾ_Ptr++;

	/*
	 * Now fill in the data field with known values so we can verify them
	 * on receive.
	 */
	ਲਈ (ਸੂਚਕਾਂਕ = 0; ਸੂਚਕਾਂਕ < Payload_ਮਾਪ; ਸੂਚਕਾਂਕ++) {
		*ਚੌਖਟਾ_Ptr++ = (u8)ਸੂਚਕਾਂਕ;
	}

	/*
	 * Now send the frame.
	 */
	ਵਾਪਸ XEmacLite_Send(InstancePtr, (u8 *)Tx_ਚੌਖਟਾ,
				Payload_ਮਾਪ + XEL_ਸਿਰਲੇਖ_ਮਾਪ);

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
ਸਥਿਰ ਪੂਰਨ Emac_Lite_Recv_ਚੌਖਟਾ(u32 Payload_ਮਾਪ)
{
	u8 *ਚੌਖਟਾ_Ptr;

	/*
	 * This assumes MAC does not strip padding or CRC.
	 */
	ਜੇ (Recv_ਚੌਖਟਾ_ਲੰਮਾਈ != 0) {
		ਪੂਰਨ ਸੂਚਕਾਂਕ;

		/*
		 * Verify length, which should be the payload size.
		 */
		ਜੇ ((Recv_ਚੌਖਟਾ_ਲੰਮਾਈ- (XEL_ਸਿਰਲੇਖ_ਮਾਪ + XEL_FCS_ਮਾਪ)) !=
				Payload_ਮਾਪ) {
			ਵਾਪਸ XST_LOOPBACK_ERROR;
		}

		/*
		 * Verify the contents of the Received Frame.
		 */
		ਚੌਖਟਾ_Ptr = (u8 *)Rx_ਚੌਖਟਾ;
		ਚੌਖਟਾ_Ptr += XEL_ਸਿਰਲੇਖ_ਮਾਪ;	/* Get past the header */

		ਲਈ (ਸੂਚਕਾਂਕ = 0; ਸੂਚਕਾਂਕ < Payload_ਮਾਪ; ਸੂਚਕਾਂਕ++) {
			ਜੇ (*ਚੌਖਟਾ_Ptr++ != (u8)ਸੂਚਕਾਂਕ) {
				ਵਾਪਸ XST_LOOPBACK_ERROR;
			}
		}
	}

	ਵਾਪਸ SUCCESS;
}
