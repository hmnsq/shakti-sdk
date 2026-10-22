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

#ಅನ್ತರ್ಭಾವ "gpio.h"
#ಅನ್ತರ್ಭಾವ "uart.h"
#ಅನ್ತರ್ಭಾವ "traps.h"
#ಅನ್ತರ್ಭಾವ "platform.h"
#ಅನ್ತರ್ಭಾವ "eth_driver.h"
#ಅನ್ತರ್ಭಾವ "log.h"




/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು EMAC_DEVICE_ID			240
#ವ್ಯಾಖ್ಯಾನಿಸು ETH_ತಳ_REG 0x44000
ಅಸ್ಥಿರ ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ* eth_ತಳ_reg = ETH_ತಳ_REG;
/*
 * Instance of the driver
 */
ಸ್ಥಿರ XEmacLite EmacLite;



/*
 * Change this parameter to limit the number of ping replies sent by this
 * program.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು MAX_PING_REPLIES	10000	/* Maximum number of ping replies */

#ವ್ಯಾಖ್ಯಾನಿಸು ಪ್ರಸಾರ_PACKET	1	/* Broadcast packet */
#ವ್ಯಾಖ್ಯಾನಿಸು MAC_MATCHED_PACKET	2 	/* Dest MAC matched with local MAC */
#ವ್ಯಾಖ್ಯಾನಿಸು IP_ADDR_ಗಾತ್ರ		4	/* IP Address size in Bytes */
#ವ್ಯಾಖ್ಯಾನಿಸು ARP_REQUEST 		0x0001	/* ARP Request bits in Rx packet */
#ವ್ಯಾಖ್ಯಾನಿಸು ARP_ಉತ್ತರ 		0x0002 	/* ARP status bits indicating reply */
#ವ್ಯಾಖ್ಯಾನಿಸು ARP_PACKET_ಗಾತ್ರ 	0x3C    /* ARP packet len 60 Bytes */
#ವ್ಯಾಖ್ಯಾನಿಸು ICMP_PACKET_ಗಾತ್ರ 	98 //0x4A    /* ICMP packet length 74 Bytes
					 /* including Src and Dest MAC Address */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪ್ರಸಾರ_ADDR 		0xFFFF  /* Broadcast Address */
#ವ್ಯಾಖ್ಯಾನಿಸು CORRECT_CKSUM_ಮೌಲ್ಯ	0xFFFF  /* Correct checksum value */
#ವ್ಯಾಖ್ಯಾನಿಸು IDENT_ಕ್ಷೇತ್ರ_ಮೌಲ್ಯ	0x9263	/* Identification field (random num) */

/*
 * Definitions for the locations and length of some of the fields in a
 * IP packet. The lengths are defined in Half-Words (2 bytes).
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ETHER_PROTO_TYPE_LEN	1  /* Ethernet protocol Type length  */
#ವ್ಯಾಖ್ಯಾನಿಸು SRC_MAC_ADDR_LOC	3  /* Source MAC address location */
#ವ್ಯಾಖ್ಯಾನಿಸು MAC_ADDR_LEN 		3  /* MAC address length */
#ವ್ಯಾಖ್ಯಾನಿಸು ETHER_PROTO_TYPE_LOC	6  /* Ethernet Proto type location */

#ವ್ಯಾಖ್ಯಾನಿಸು ARP_HW_TYPE_LEN 	1  /* Hardware Type length  */
#ವ್ಯಾಖ್ಯಾನಿಸು ARP_PROTO_TYPE_LEN	1  /* Protocol Type length  */
#ವ್ಯಾಖ್ಯಾನಿಸು ARP_HW_ಕೂಡಿಸು_LEN		1  /* Hardware address length */
#ವ್ಯಾಖ್ಯಾನಿಸು ARP_PROTO_ಕೂಡಿಸು_LEN	1  /* Protocol address length */
#ವ್ಯಾಖ್ಯಾನಿಸು ARP_ZEROS_LEN		9  /* Length to be filled with zeros */
#ವ್ಯಾಖ್ಯಾನಿಸು ARP_REQ_ಸ್ಥಿತಿ_LOC 	10 /* ARP request location */
#ವ್ಯಾಖ್ಯಾನಿಸು ARP_REQ_SRC_IP_LOC 	14 /* Src IP address location of ARP request */
#ವ್ಯಾಖ್ಯಾನಿಸು ARP_REQ_DEST_IP_LOC_1 	19 /* Destination IP's 1st half word location */
#ವ್ಯಾಖ್ಯಾನಿಸು ARP_REQ_DEST_IP_LOC_2 	20 /* Destination IP's 2nd half word location */

#ವ್ಯಾಖ್ಯಾನಿಸು IP_ಆವೃತ್ತಿ_LEN 		1  /* IP Version length  */
#ವ್ಯಾಖ್ಯಾನಿಸು IP_PACKET_LEN 		1  /* IP Packet length field  */
#ವ್ಯಾಖ್ಯಾನಿಸು IP_FRAG_ಕ್ಷೇತ್ರ_LEN	1  /* Fragment field len in ICMP packet */
#ವ್ಯಾಖ್ಯಾನಿಸು IP_TTL_ICM_LEN 		1  /* Time to live and ICM fields length */
#ವ್ಯಾಖ್ಯಾನಿಸು IP_ADDR_LEN 		2  /* Size of IP address in half-words */
#ವ್ಯಾಖ್ಯಾನಿಸು IP_CSUM_LOC_ಹಿಂಭಾಗ	5  /* IP checksum location from end of frame */
#ವ್ಯಾಖ್ಯಾನಿಸು IP_HDR_ಆರಂಭ_LOC 	7  /* IP header start location */
#ವ್ಯಾಖ್ಯಾನಿಸು IP_HDR_LEN 		10 /* IP Header length */
#ವ್ಯಾಖ್ಯಾನಿಸು IP_FRAG_ಕ್ಷೇತ್ರ_LOC 	10 /* Fragment field location */

#ವ್ಯಾಖ್ಯಾನಿಸು ICMP_TYPE_LEN 		1  /* ICMP Type length */
#ವ್ಯಾಖ್ಯಾನಿಸು ICMP_ECHO_ಕ್ಷೇತ್ರ_LEN 	2  /* Echo field length in half-words */
#ವ್ಯಾಖ್ಯಾನಿಸು ICMP_REQ_SRC_IP_LOC 	13 /* Src IP address location of ICMP request */
#ವ್ಯಾಖ್ಯಾನಿಸು ICMP_ECHO_ಕ್ಷೇತ್ರ_LOC 	17 /* Echo field location */
#ವ್ಯಾಖ್ಯಾನಿಸು ICMP_ದತ್ತಾಂಶ_ಆರಂಭ_LOC 	17 /* Data field start location */
#ವ್ಯಾಖ್ಯಾನಿಸು ICMP_ದತ್ತಾಂಶ_LEN 		30  //18  /* ICMP data length */
#ವ್ಯಾಖ್ಯಾನಿಸು ICMP_ದತ್ತಾಂಶ_LOC 		19 /* ICMP data location including
				      identifier number and sequence number */
#ವ್ಯಾಖ್ಯಾನಿಸು ICMP_ದತ್ತಾಂಶ_CSUM_LOC_ಹಿಂಭಾಗ 31 //19 
/* Data checksum location from end of
ಚೌಕಟ್ಟು*/
#ವ್ಯಾಖ್ಯಾನಿಸು ICMP_ದತ್ತಾಂಶ_ಕ್ಷೇತ್ರ_LEN 	32 //20 /* Data field length */

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ Emac_Lite_Ping_ಉತ್ತರ_Example(u16 DeviceId);

ಸ್ಥಿರ ಶೂನ್ಯ Process_Recv_ಚೌಕಟ್ಟು(XEmacLite *InstancePtr);

ಸ್ಥಿರ u16 Check_ಮೊತ್ತ_Calculation(u16 *Rx_ಚೌಕಟ್ಟು_Ptr, ಪೂರ್ಣಾಂಕ ಆರಂಭ_Loc, ಪೂರ್ಣಾಂಕ ಉದ್ದಳತೆ);

/************************** Variable Definitions *****************************/

/*
 * Set up a local MAC address.
 */
ಸ್ಥಿರ u8 LocalMacAddr[XEL_MAC_ADDR_ಗಾತ್ರ] =
{
	0x00, 0x00, 0x5E, 0x00, 0xFA, 0xCE
};

/*
 * The IP address was set to 172.16.63.121. User need to set a free IP address
 * based on the network on which this example is to be run.
 */
ಸ್ಥಿರ u8 LocalIpAddr[IP_ADDR_ಗಾತ್ರ] =
{
	192, 168, 1, 25
};

ಸ್ಥಿರ XEmacLite EmacLiteInstance;	/* Instance of the EmacLite driver */

/*
 * Buffers used for Transmission and Reception of Packets. These are declared as
 * global so that they are not a part of the stack.
 */
ಸ್ಥಿರ u8 Rx_ಚೌಕಟ್ಟು[XEL_MAX_ಚೌಕಟ್ಟು_ಗಾತ್ರ];
ಸ್ಥಿರ u8 Tx_ಚೌಕಟ್ಟು[XEL_MAX_ಚೌಕಟ್ಟು_ಗಾತ್ರ];

/*
 * Variable used to indicate the length of the received frame.
 */
ಬಾಹ್ಯ ಅಸ್ಥಿರ u32 Recv_ಚೌಕಟ್ಟು_ಉದ್ದಳತೆ = 0;

/*
 * Variable used to indicate the number of Ping replies sent.
 */
u32 ಅಂಕೆ_ದ_Ping_Replies;
u32 arpcount = 0;

/****************************************************************************/
/**
*
* This function is the main function of the Ping reply example in
* polled mode.
*
* @param	None.
*
* @return	XST_FAILURE to indicate failure, otherwise XST_SUCCESS
*		is returned.
*
* @note		None.
*
*****************************************************************************/
ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ()
{
	ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_2;
	arpcount = 0;
	/*
	 * Run the EmacLite Ping reply example.
	 */
	ಸ್ಥಿತಿ_2 = Emac_Lite_Ping_ಉತ್ತರ_Example(EMAC_DEVICE_ID);
	ಆದರೆ (ಸ್ಥಿತಿ_2 != XST_SUCCESS) {
		xil_printf("Emaclite ping reply Example Failed\r\n");
		ಹಿಂತಿರುಗಿ XST_FAILURE;
	}

	xil_printf("Successfully ran Emaclite ping reply Example\r\n");
	ಹಿಂತಿರುಗಿ XST_SUCCESS;
}

/*****************************************************************************/
/**
*
* The entry point for the EmacLite Ping reply example in polled mode.
*
* @param	DeviceId is device ID of the XEmacLite Device.
*
* @return	XST_FAILURE to indicate failure, otherwise XST_SUCCESS is
*		returned.
*
* @note		This is in a continuous loop generating a specified number of
*		ping replies as defined by MAX_PING_REPLIES.
*
******************************************************************************/
ಪೂರ್ಣಾಂಕ Emac_Lite_Ping_ಉತ್ತರ_Example(u16 DeviceId)
{
	ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_2, ಎಣಿಕೆ_2 = 0;
	XEmacLite *EmacLiteInstPtr = &EmacLiteInstance;
	XEmacLite_Config *ConfigPtr;
	ಅಂಕೆ_ದ_Ping_Replies = 0;

	/*
	 * Initialize the EmacLite device.
	 */
	ConfigPtr = &XEmac_Lite_Config_ಕೋಷ್ಟಕ;
	ಆದರೆ (ConfigPtr == ಖಾಲಿ) {
		ಹಿಂತಿರುಗಿ -1;
	}
	ಬರೆ("\n ");

	ConfigPtr->ತಳ_ವಿಳಾಸ = (UINTPTR *) 0X44000;
	ConfigPtr->RxPingPong = XPAR_EMACLITE_0_RX_PING_PONG;
	ConfigPtr->MdioInclude = XPAR_EMACLITE_0_INCLUDE_MDIO;
	ConfigPtr->TxPingPong = XPAR_EMACLITE_0_TX_PING_PONG;
	ಸ್ಥಿತಿ_2 = XEmacLite_CfgInitialize(EmacLiteInstPtr,
					ConfigPtr,
					ConfigPtr->ತಳ_ವಿಳಾಸ);
	ಆದರೆ (ಸ್ಥಿತಿ_2 != 0) {
		ಹಿಂತಿರುಗಿ -1;
	}
	
	/*
	 * Set the MAC address.
	 */
	XEmac_Lite_ಗಣ_Mac_ವಿಳಾಸ(EmacLiteInstPtr, LocalMacAddr);
	/*
	 * Empty any existing receive frames.
	 */
	XEmacLite_FlushReceive(EmacLiteInstPtr);

	ಆಗ (1) {

		/*
		 * Wait for a Receive packet.
		 */
		ಆಗ (Recv_ಚೌಕಟ್ಟು_ಉದ್ದಳತೆ == 0) {
			Recv_ಚೌಕಟ್ಟು_ಉದ್ದಳತೆ = XEmacLite_Recv(EmacLiteInstPtr,
								(u8 *)Rx_ಚೌಕಟ್ಟು);
		}
#ಆದರೆ 1
		ಬರೆ("\n Rcv. Frame %x: %x\n", ಅಂಕೆ_ದ_Ping_Replies, Recv_ಚೌಕಟ್ಟು_ಉದ್ದಳತೆ);
		ಗಾಗಿ(ಪೂರ್ಣಾಂಕ i = 0; i < Recv_ಚೌಕಟ್ಟು_ಉದ್ದಳತೆ; i++)
			ಬರೆ("%x ", Rx_ಚೌಕಟ್ಟು[i]);
		ಬರೆ("\n");
#ಆದರೆ_ಅಂತ್ಯ			
		/*
		 * Empty any existing receive frames.
		 */
		XEmacLite_FlushReceive(EmacLiteInstPtr);

		/*
		 * Process the Receive frame.
		 */
		Process_Recv_ಚೌಕಟ್ಟು(EmacLiteInstPtr);
		Recv_ಚೌಕಟ್ಟು_ಉದ್ದಳತೆ = 0;

		/*
		 * If the number of ping replies sent is equal to that
		 * specified by the user then exit out of this loop.
		 */
		ಆದರೆ (ಅಂಕೆ_ದ_Ping_Replies == MAX_PING_REPLIES) {

			ಹಿಂತಿರುಗಿ XST_SUCCESS;
		}

	}
}

/******************************************************************************/
/**
*
* This function processes the received packet and generates the corresponding
* reply packets.
*
* @param	InstancePtr is a pointer to the instance of the EmacLite.
*
* @return	None.
*
* @note		This function assumes MAC does not strip padding or CRC.
*
******************************************************************************/
ಸ್ಥಿರ ಶೂನ್ಯ Process_Recv_ಚೌಕಟ್ಟು(XEmacLite *InstancePtr)
{
	u16 *Rx_ಚೌಕಟ್ಟು_Ptr;
	u16 *Tx_ಚೌಕಟ್ಟು_Ptr;
	u16 *ತಾತ್ಕಾಲಿಕ_Ptr;
	u16 Check_ಮೊತ್ತ;
	u32 ಮುಂದಿನ_Tx_Buff_ತಳ_Addr;
	ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ;
	ಪೂರ್ಣಾಂಕ PacketType = 0;

	Tx_ಚೌಕಟ್ಟು_Ptr = (u16 *)Tx_ಚೌಕಟ್ಟು;
	Rx_ಚೌಕಟ್ಟು_Ptr = (u16 *)Rx_ಚೌಕಟ್ಟು;

	/*
	 * Determine the next expected Tx buffer address.
	 */
	ಮುಂದಿನ_Tx_Buff_ತಳ_Addr = XEmac_Lite_ಮುಂದಿನ_Transmit_Addr(InstancePtr);

	/*
	 * Check the packet type.
	 */
	ಸೂಚ್ಯಂಕ = MAC_ADDR_LEN;
	ತಾತ್ಕಾಲಿಕ_Ptr = (u16 *)LocalMacAddr;
	ಆಗ (ಸೂಚ್ಯಂಕ--) {
		ಆದರೆ (Xil_Ntohs((*(Rx_ಚೌಕಟ್ಟು_Ptr + ಸೂಚ್ಯಂಕ)) == ಪ್ರಸಾರ_ADDR) &&
					(PacketType != MAC_MATCHED_PACKET)) {
			PacketType = ಪ್ರಸಾರ_PACKET;
		} ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (Xil_Ntohs((*(Rx_ಚೌಕಟ್ಟು_Ptr + ಸೂಚ್ಯಂಕ)) == *(ತಾತ್ಕಾಲಿಕ_Ptr + ಸೂಚ್ಯಂಕ)) &&
					(PacketType != ಪ್ರಸಾರ_PACKET)) {
			PacketType = MAC_MATCHED_PACKET;
		} ಇಲ್ಲದಿದ್ದರೆ {
			PacketType = 0;
			ನಿಲ್ಲಿಸು;
		}
	}
#ಆದರೆ 0
	ಬರೆ("\n Packet type is %x", PacketType);
#ಆದರೆ_ಅಂತ್ಯ
	/*
	 * Process broadcast packet.
	 */
	ಆದರೆ (PacketType == ಪ್ರಸಾರ_PACKET) {

		/*
		 * Check for an ARP Packet if so generate a reply.
		 */
		ಆದರೆ (Xil_Ntohs(*(Rx_ಚೌಕಟ್ಟು_Ptr + ETHER_PROTO_TYPE_LOC)) ==
				XEL_ETHER_PROTO_TYPE_ARP) {

			/*
			 * IP address of the local machine.
			 */
			ತಾತ್ಕಾಲಿಕ_Ptr = (u16 *)LocalIpAddr;

			/*
			 * Check destination IP address of the packet with
			 * local IP address.
			 */
			ಆದರೆ (
			((*(Rx_ಚೌಕಟ್ಟು_Ptr + ARP_REQ_DEST_IP_LOC_1)) == *ತಾತ್ಕಾಲಿಕ_Ptr++) &&
			((*(Rx_ಚೌಕಟ್ಟು_Ptr + ARP_REQ_DEST_IP_LOC_2)) == *ತಾತ್ಕಾಲಿಕ_Ptr++)) {

				/*
				 * Check ARP packet type(request/reply).
				 */
				ಆದರೆ (Xil_Ntohs(*(Rx_ಚೌಕಟ್ಟು_Ptr + ARP_REQ_ಸ್ಥಿತಿ_LOC)) ==
								ARP_REQUEST) {

					/*
					 * Add destination MAC address
					 * to the reply packet (i.e) source
					 * address of the received packet.
					 */
					ಸೂಚ್ಯಂಕ = SRC_MAC_ADDR_LOC;
					ಆಗ (ಸೂಚ್ಯಂಕ < (SRC_MAC_ADDR_LOC +
							MAC_ADDR_LEN)) {
						*Tx_ಚೌಕಟ್ಟು_Ptr++ =
							*(Rx_ಚೌಕಟ್ಟು_Ptr + ಸೂಚ್ಯಂಕ);
						ಸೂಚ್ಯಂಕ++;
					}

					/*
					 * Add source (local) MAC address
					 * to the reply packet.
					 */
					ಸೂಚ್ಯಂಕ = 0;
					ತಾತ್ಕಾಲಿಕ_Ptr = (u16 *)LocalMacAddr;
					ಆಗ (ಸೂಚ್ಯಂಕ < MAC_ADDR_LEN) {
						*Tx_ಚೌಕಟ್ಟು_Ptr++ = *ತಾತ್ಕಾಲಿಕ_Ptr++;
						ಸೂಚ್ಯಂಕ++;
					}

					/*
					 * Add Ethernet proto type H/W
					 * type(10/3MBps),H/W address length and
					 * protocol address len (i.e)same as in
					 * the received packet
					 */
					ಸೂಚ್ಯಂಕ = ETHER_PROTO_TYPE_LOC;
					ಆಗ (ಸೂಚ್ಯಂಕ < (ETHER_PROTO_TYPE_LOC +
							ETHER_PROTO_TYPE_LEN +
							ARP_HW_TYPE_LEN +
							ARP_HW_ಕೂಡಿಸು_LEN
							+ ARP_PROTO_ಕೂಡಿಸು_LEN)) {
						*Tx_ಚೌಕಟ್ಟು_Ptr++ =
							*(Rx_ಚೌಕಟ್ಟು_Ptr + ಸೂಚ್ಯಂಕ);
						ಸೂಚ್ಯಂಕ++;
					}

					/*
					 * Add ARP reply status to the reply
					 * packet.
					 */
					*Tx_ಚೌಕಟ್ಟು_Ptr++ = Xil_Htons(ARP_ಉತ್ತರ);

					/*
					 * Add local MAC Address
					 * to the reply packet.
					 */
					ತಾತ್ಕಾಲಿಕ_Ptr = (u16 *)LocalMacAddr;
					ಸೂಚ್ಯಂಕ = 0;
					ಆಗ (ಸೂಚ್ಯಂಕ < MAC_ADDR_LEN) {
						*Tx_ಚೌಕಟ್ಟು_Ptr++ = *ತಾತ್ಕಾಲಿಕ_Ptr++;
						ಸೂಚ್ಯಂಕ++;
					}

					/*
					 * Add local IP Address
					 * to the reply packet.
					 */
					ತಾತ್ಕಾಲಿಕ_Ptr = (u16 *)LocalIpAddr;
					ಸೂಚ್ಯಂಕ = 0;
					ಆಗ (ಸೂಚ್ಯಂಕ < IP_ADDR_LEN) {
						*Tx_ಚೌಕಟ್ಟು_Ptr++ = *ತಾತ್ಕಾಲಿಕ_Ptr++ ;
						ಸೂಚ್ಯಂಕ++;
					}

					/*
					 * Add Destination MAC Address
					 * to the reply packet from the received
					 * packet.
					 */
					ಸೂಚ್ಯಂಕ = SRC_MAC_ADDR_LOC;
					ಆಗ (ಸೂಚ್ಯಂಕ < (SRC_MAC_ADDR_LOC +
							MAC_ADDR_LEN)) {
						*Tx_ಚೌಕಟ್ಟು_Ptr++ =
							*(Rx_ಚೌಕಟ್ಟು_Ptr + ಸೂಚ್ಯಂಕ);
						ಸೂಚ್ಯಂಕ++;
					}

					/*
					 * Add Destination IP Address
					 * to the reply packet.
					 */
					ಸೂಚ್ಯಂಕ = ARP_REQ_SRC_IP_LOC;
					ಆಗ (ಸೂಚ್ಯಂಕ < (ARP_REQ_SRC_IP_LOC +
							IP_ADDR_LEN)) {
						*Tx_ಚೌಕಟ್ಟು_Ptr++ =
								*(Rx_ಚೌಕಟ್ಟು_Ptr + ಸೂಚ್ಯಂಕ);
						ಸೂಚ್ಯಂಕ++;
					}

					/*
					 * Fill zeros as per protocol.
					 */
					ಸೂಚ್ಯಂಕ = 0;
					ಆಗ (ಸೂಚ್ಯಂಕ < ARP_ZEROS_LEN) {
						*Tx_ಚೌಕಟ್ಟು_Ptr++ = 0x0000;
						ಸೂಚ್ಯಂಕ++;
					}

					/*
					 * Transmit the Reply Packet.
					 */
					XEmacLite_Send(InstancePtr,
							(u8 *)&Tx_ಚೌಕಟ್ಟು,
							ARP_PACKET_ಗಾತ್ರ);
				}
			}
		}
	}

	/*
	 * Process packets whose MAC address is matched.
	 */
	ಆದರೆ (PacketType == MAC_MATCHED_PACKET) {
//		printf("\n MAC matched packet");
		/*
		 * Check ICMP packet.
		 */
		ಆದರೆ (Xil_Ntohs(*(Rx_ಚೌಕಟ್ಟು_Ptr + ETHER_PROTO_TYPE_LOC)) ==
						XEL_ETHER_PROTO_TYPE_IP) {
//			printf("\n calculate ip header checksum");
			/*
			 * Check the IP header checksum.
			 */
			Check_ಮೊತ್ತ = Check_ಮೊತ್ತ_Calculation(Rx_ಚೌಕಟ್ಟು_Ptr,
						IP_HDR_ಆರಂಭ_LOC,
						IP_HDR_LEN);

			/*
			 * Check the Data field checksum.
			 */
//			printf("\n ip checksum:%x", CheckSum);
			ಆದರೆ (Check_ಮೊತ್ತ == CORRECT_CKSUM_ಮೌಲ್ಯ) {
				Check_ಮೊತ್ತ = Check_ಮೊತ್ತ_Calculation(Rx_ಚೌಕಟ್ಟು_Ptr,
						ICMP_ದತ್ತಾಂಶ_ಆರಂಭ_LOC,
						ICMP_ದತ್ತಾಂಶ_ಕ್ಷೇತ್ರ_LEN);
#ಆದರೆ 0
			ಬರೆ("\nICMP Rcv Packet: \n");
			ಗಾಗಿ(ಪೂರ್ಣಾಂಕ i = ICMP_ದತ್ತಾಂಶ_ಆರಂಭ_LOC; i <= ICMP_ದತ್ತಾಂಶ_ಕ್ಷೇತ್ರ_LEN; i++)
			   ಬರೆ("%x ", Rx_ಚೌಕಟ್ಟು_Ptr[i]);
			ಬರೆ("\n End of ICMP Rcv Packet");
				
				ಬರೆ("\n data checksum:%x", Check_ಮೊತ್ತ);
#ಆದರೆ_ಅಂತ್ಯ
				ಆದರೆ (Check_ಮೊತ್ತ == CORRECT_CKSUM_ಮೌಲ್ಯ) {

					/*
					 * Add destination address
					 * to the reply packet (i.e)source
					 * address of the received packet.
					 */
					ಸೂಚ್ಯಂಕ = SRC_MAC_ADDR_LOC;
					ಆಗ (ಸೂಚ್ಯಂಕ < (SRC_MAC_ADDR_LOC +
							MAC_ADDR_LEN)) {
						*Tx_ಚೌಕಟ್ಟು_Ptr++ =
							*(Rx_ಚೌಕಟ್ಟು_Ptr + ಸೂಚ್ಯಂಕ);
						ಸೂಚ್ಯಂಕ++;
					}

					/*
					 * Add local MAC address
					 * to the reply packet.
					 */
					ಸೂಚ್ಯಂಕ = 0;
					ತಾತ್ಕಾಲಿಕ_Ptr = (u16 *)LocalMacAddr;
					ಆಗ (ಸೂಚ್ಯಂಕ < MAC_ADDR_LEN) {
						*Tx_ಚೌಕಟ್ಟು_Ptr++ = *ತಾತ್ಕಾಲಿಕ_Ptr++;
						ಸೂಚ್ಯಂಕ++;
					}

					/*
					 * Add protocol type
					 * header length and, packet
					 * length(60 Bytes) to the reply packet.
					 */
					ಸೂಚ್ಯಂಕ = ETHER_PROTO_TYPE_LOC;
					ಆಗ (ಸೂಚ್ಯಂಕ < (ETHER_PROTO_TYPE_LOC +
							ETHER_PROTO_TYPE_LEN +
							IP_ಆವೃತ್ತಿ_LEN +
							IP_PACKET_LEN)) {
						*Tx_ಚೌಕಟ್ಟು_Ptr++ =
							*(Rx_ಚೌಕಟ್ಟು_Ptr + ಸೂಚ್ಯಂಕ);
						ಸೂಚ್ಯಂಕ++;
					}

					/*
					 * Identification field a random number
					 * which is set to IDENT_FIELD_VALUE.
					 */
					*Tx_ಚೌಕಟ್ಟು_Ptr++ = IDENT_ಕ್ಷೇತ್ರ_ಮೌಲ್ಯ;

					/*
					 * Add fragment type, time to live and
					 * ICM field. It is same as in the
					 * received packet.
					 */
					ಸೂಚ್ಯಂಕ = IP_FRAG_ಕ್ಷೇತ್ರ_LOC;
					ಆಗ (ಸೂಚ್ಯಂಕ < (IP_FRAG_ಕ್ಷೇತ್ರ_LOC +
							IP_TTL_ICM_LEN +
							IP_FRAG_ಕ್ಷೇತ್ರ_LEN)) {
						*Tx_ಚೌಕಟ್ಟು_Ptr++ =
							*(Rx_ಚೌಕಟ್ಟು_Ptr + ಸೂಚ್ಯಂಕ);
						ಸೂಚ್ಯಂಕ++;
					}

					/*
					 * Checksum first set to 0 and
					 * added in this field later.
					 */
					*Tx_ಚೌಕಟ್ಟು_Ptr++ = 0x0000;

					/*
					 * Add Source IP address
					 */
					ಸೂಚ್ಯಂಕ = 0;
					ತಾತ್ಕಾಲಿಕ_Ptr = (u16 *)LocalIpAddr;
					ಆಗ (ಸೂಚ್ಯಂಕ < IP_ADDR_LEN) {
						*Tx_ಚೌಕಟ್ಟು_Ptr++ = *ತಾತ್ಕಾಲಿಕ_Ptr++;
						ಸೂಚ್ಯಂಕ++;
					}

					/*
					 * Add Destination IP address.
					 */
					ಸೂಚ್ಯಂಕ = ICMP_REQ_SRC_IP_LOC;
					ಆಗ (ಸೂಚ್ಯಂಕ < (ICMP_REQ_SRC_IP_LOC +
							IP_ADDR_LEN)) {
						*Tx_ಚೌಕಟ್ಟು_Ptr++ =
							*(Rx_ಚೌಕಟ್ಟು_Ptr + ಸೂಚ್ಯಂಕ);
						ಸೂಚ್ಯಂಕ++;
					}

					/*
					 * Calculate checksum, and
					 * add it in the appropriate field.
					 */
					Check_ಮೊತ್ತ = Check_ಮೊತ್ತ_Calculation(
							(u16 *)Tx_ಚೌಕಟ್ಟು,
							IP_HDR_ಆರಂಭ_LOC,
							IP_HDR_LEN);
					Check_ಮೊತ್ತ = ~Check_ಮೊತ್ತ;
					*(Tx_ಚೌಕಟ್ಟು_Ptr - IP_CSUM_LOC_ಹಿಂಭಾಗ) =
								Xil_Htons(Check_ಮೊತ್ತ);

					/*
					 * Echo reply status & checksum.
					 */
					ಸೂಚ್ಯಂಕ = ICMP_ECHO_ಕ್ಷೇತ್ರ_LOC;
					ಆಗ (ಸೂಚ್ಯಂಕ < (ICMP_ECHO_ಕ್ಷೇತ್ರ_LOC +
							ICMP_ECHO_ಕ್ಷೇತ್ರ_LEN)) {
						*Tx_ಚೌಕಟ್ಟು_Ptr++ = 0x0000;
						ಸೂಚ್ಯಂಕ++;
					}

					/*
					 * Add data to buffer which was
					 * received from the packet.
					 */
					ಸೂಚ್ಯಂಕ = ICMP_ದತ್ತಾಂಶ_LOC;
					ಆಗ (ಸೂಚ್ಯಂಕ < (ICMP_ದತ್ತಾಂಶ_LOC +
							ICMP_ದತ್ತಾಂಶ_LEN)) {
						*Tx_ಚೌಕಟ್ಟು_Ptr++ =
								(*(Rx_ಚೌಕಟ್ಟು_Ptr + ಸೂಚ್ಯಂಕ));
						ಸೂಚ್ಯಂಕ++;
					}

					/*
					 * Generate checksum for the data and
					 * add it in the appropriate field.
					 */
					Check_ಮೊತ್ತ = Check_ಮೊತ್ತ_Calculation(
							(u16 *)Tx_ಚೌಕಟ್ಟು,
							ICMP_ದತ್ತಾಂಶ_ಆರಂಭ_LOC,
							ICMP_ದತ್ತಾಂಶ_ಕ್ಷೇತ್ರ_LEN);
					Check_ಮೊತ್ತ = ~Check_ಮೊತ್ತ;
					*(Tx_ಚೌಕಟ್ಟು_Ptr - ICMP_ದತ್ತಾಂಶ_CSUM_LOC_ಹಿಂಭಾಗ)
								= Xil_Htons(Check_ಮೊತ್ತ);

					/*
					 * Transmit the frame.
					 */
#ಆದರೆ 1
					 ಬರೆ("\n%x. ICMP Tx Packet \n", ಅಂಕೆ_ದ_Ping_Replies);
					 ಗಾಗಿ(ಪೂರ್ಣಾಂಕ i = 0; i < ICMP_PACKET_ಗಾತ್ರ; i++)
					 	ಬರೆ("%x ", Tx_ಚೌಕಟ್ಟು[i]);
					 ಬರೆ("\n End of ICMP Tx Packet");
#ಆದರೆ_ಅಂತ್ಯ					 
					XEmacLite_Send(InstancePtr,
							(u8 *)&Tx_ಚೌಕಟ್ಟು,
							ICMP_PACKET_ಗಾತ್ರ);

					/*
					 * Increment the number of
					 * Ping replies sent.
					 */
					ಅಂಕೆ_ದ_Ping_Replies++;
//					printf("NumOfPingReplies: %x", NumOfPingReplies);

				}
				ಇಲ್ಲದಿದ್ದರೆ
					ಬರೆ("\n Data check sum error");
			}
			ಇಲ್ಲದಿದ್ದರೆ
				ಬರೆ("\n IP Check sum error");
		}
	}
}

/*****************************************************************************/
/**
*
* This function calculates the checksum and returns a 16 bit result.
*
* @param 	RxFramePtr is a 16 bit pointer for the data to which checksum
* 		is to be calculated.
* @param	StartLoc is the starting location of the data from which the
*		checksum has to be calculated.
* @param	Length is the number of halfwords(16 bits) to which checksum is
* 		to be calculated.
*
* @return	It returns a 16 bit checksum value.
*
* @note		This can also be used for calculating checksum. The ones
* 		complement of this return value will give the final checksum.
*
******************************************************************************/
ಸ್ಥಿರ u16 Check_ಮೊತ್ತ_Calculation(u16 *Rx_ಚೌಕಟ್ಟು_Ptr, ಪೂರ್ಣಾಂಕ ಆರಂಭ_Loc, ಪೂರ್ಣಾಂಕ ಉದ್ದಳತೆ)
{
	u32 ಮೊತ್ತ = 0;
	u16 Check_ಮೊತ್ತ = 0;
	ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ;

	/*
	 * Add all the 16 bit data.
	 */
	ಸೂಚ್ಯಂಕ = ಆರಂಭ_Loc;
	ಆಗ (ಸೂಚ್ಯಂಕ < (ಆರಂಭ_Loc + ಉದ್ದಳತೆ)) {
		ಮೊತ್ತ = ಮೊತ್ತ + Xil_Ntohs(*(Rx_ಚೌಕಟ್ಟು_Ptr + ಸೂಚ್ಯಂಕ));
		ಸೂಚ್ಯಂಕ++;
	}

	/*
	 * Add upper 16 bits to lower 16 bits.
	 */
	Check_ಮೊತ್ತ = ಮೊತ್ತ;
	ಮೊತ್ತ = ಮೊತ್ತ >> 16;
	Check_ಮೊತ್ತ = ಮೊತ್ತ + Check_ಮೊತ್ತ;
	ಹಿಂತಿರುಗಿ Check_ಮೊತ್ತ;
}
