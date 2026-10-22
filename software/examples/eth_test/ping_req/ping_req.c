/***************************************************************************
 * Project           			:  shakti devt board
 * Name of the file	     		:  ping_req.c
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

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

ಬಾಹ್ಯ XEmacLite_Config XEmac_Lite_Config_ಕೋಷ್ಟಕ;

/************************** Variable Definitions *****************************/

/*
 * Instance of the driver
 */
ಸ್ಥಿರ XEmacLite EmacLite;


/*
 * Change this parameter to limit the number of ping requests sent by this
 * program.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಅಂಕೆ_ದ_PING_REQ_PKTS	100	/* Number of ping req it generates */

#ವ್ಯಾಖ್ಯಾನಿಸು ECHO_ಉತ್ತರ		0x00	/* Echo reply */
#ವ್ಯಾಖ್ಯಾನಿಸು HW_TYPE			0x01	/* Hardware type (10/100 Mbps) */
#ವ್ಯಾಖ್ಯಾನಿಸು ARP_REQUEST 		0x01	/* ARP Request bits in Rx packet */
#ವ್ಯಾಖ್ಯಾನಿಸು ARP_ಉತ್ತರ 		0x02 	/* ARP status bits indicating reply */
#ವ್ಯಾಖ್ಯಾನಿಸು IDEN_ಅಂಕೆ		0x02	/* ICMP identifier number */
#ವ್ಯಾಖ್ಯಾನಿಸು IP_ಆವೃತ್ತಿ		0x0604	/* IP version ipv4/ipv6 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪ್ರಸಾರ_ADDR 		0xFFFF 	/* Broadcast Address */
#ವ್ಯಾಖ್ಯಾನಿಸು CORRECT_CHECKSUM_ಮೌಲ್ಯ	0xFFFF	/* Correct checksum value */
#ವ್ಯಾಖ್ಯಾನಿಸು ARP_REQ_PKT_ಗಾತ್ರ	0x2A	/* ARP request packet size */
#ವ್ಯಾಖ್ಯಾನಿಸು ICMP_PKT_ಗಾತ್ರ 		0x4A	/* ICMP packet length 74 Bytes
					including Src and dest MAC Add */
#ವ್ಯಾಖ್ಯಾನಿಸು IP_ADDR_ಗಾತ್ರ		4	/* IP Address size in Bytes */
#ವ್ಯಾಖ್ಯಾನಿಸು ಅಂಕೆ_RX_PACK_CHECK_REQ	10	/* Max num of Rx pack to be checked
					before sending another request */
#ವ್ಯಾಖ್ಯಾನಿಸು ಅಂಕೆ_PACK_CHECK_RX_PACK	100	/* Max number of pack to be checked
					before to identify a Rx packet */
#ವ್ಯಾಖ್ಯಾನಿಸು DELAY			5000000 /* Used to introduce delay */

/*
 * Definitions for the locations and length of some of the fields in a
 * IP packet. The lengths are defined in Half-Words (2 bytes).
 */

#ವ್ಯಾಖ್ಯಾನಿಸು SRC_MAC_ADDR_LOC	3	/* Src MAC address location */
#ವ್ಯಾಖ್ಯಾನಿಸು MAC_ADDR_LEN 		3	/* MAC address length */
#ವ್ಯಾಖ್ಯಾನಿಸು ETHER_PROTO_TYPE_LOC	6	/* Ethernet Proto type loc */

#ವ್ಯಾಖ್ಯಾನಿಸು IP_ADDR_LEN 		2	/* Size of IP address */
#ವ್ಯಾಖ್ಯಾನಿಸು IP_ಆರಂಭ_LOC 		7	/* IP header start location */
#ವ್ಯಾಖ್ಯಾನಿಸು IP_ಶೀರ್ಷಿಕೆ_INFO_LEN	7	/* IP header information length */
#ವ್ಯಾಖ್ಯಾನಿಸು IP_ಶೀರ್ಷಿಕೆ_LEN 		10 	/* IP header length */
#ವ್ಯಾಖ್ಯಾನಿಸು IP_CHECKSUM_LOC		12	/* IP header checksum location */
#ವ್ಯಾಖ್ಯಾನಿಸು IP_REQ_SRC_IP_LOC 	13	/* Src IP add loc of ICMP req */
#ವ್ಯಾಖ್ಯಾನಿಸು IP_REQ_DEST_IP_LOC	15	/* Dest IP add loc of ICMP req */

#ವ್ಯಾಖ್ಯಾನಿಸು ICMP_ತಿಳಿದ_ದತ್ತಾಂಶ_LEN	64	/* ICMP known data length */
#ವ್ಯಾಖ್ಯಾನಿಸು ICMP_ECHO_ಕ್ಷೇತ್ರ_LOC 	17	/* Echo field loc */
#ವ್ಯಾಖ್ಯಾನಿಸು ICMP_ದತ್ತಾಂಶ_ಆರಂಭ_LOC 	17	/* Data field start location */
#ವ್ಯಾಖ್ಯಾನಿಸು ICMP_ದತ್ತಾಂಶ_LEN 		18	/* ICMP data length */
#ವ್ಯಾಖ್ಯಾನಿಸು ICMP_ದತ್ತಾಂಶ_CHECKSUM_LOC	18	/* ICMP data checksum location */
#ವ್ಯಾಖ್ಯಾನಿಸು ICMP_IDEN_ಕ್ಷೇತ್ರ_LOC	19	/* Identifier field loc */
#ವ್ಯಾಖ್ಯಾನಿಸು ICMP_ದತ್ತಾಂಶ_LOC 		19	/* ICMP data loc including
					identifier number and sequence number */
#ವ್ಯಾಖ್ಯಾನಿಸು ICMP_SEQ_NO_LOC		20	/* sequence number location */
#ವ್ಯಾಖ್ಯಾನಿಸು ICMP_ದತ್ತಾಂಶ_ಕ್ಷೇತ್ರ_LEN 	20 	/* Data field length */
#ವ್ಯಾಖ್ಯಾನಿಸು ICMP_ತಿಳಿದ_ದತ್ತಾಂಶ_LOC	21	/* ICMP known data start loc */

#ವ್ಯಾಖ್ಯಾನಿಸು ARP_REQ_ಸ್ಥಿತಿ_LOC 	10	/* ARP request loc */
#ವ್ಯಾಖ್ಯಾನಿಸು ARP_REQ_SRC_IP_LOC 	14	/* Src IP add loc of ARP req Packet */

/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ EmacLitePingReqExample(u16 DeviceId);

ಸ್ಥಿರ ಶೂನ್ಯ Send_Arp_Req_ಚೌಕಟ್ಟು(XEmacLite *InstancePtr);

ಸ್ಥಿರ ಶೂನ್ಯ Send_Echo_Req_ಚೌಕಟ್ಟು(XEmacLite *InstancePtr);

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ Process_Recv_ಚೌಕಟ್ಟು(XEmacLite *InstancePtr);

ಸ್ಥಿರ u16 Check_ಮೊತ್ತ_Calculation(u16 *Rx_ಚೌಕಟ್ಟು_Ptr16, ಪೂರ್ಣಾಂಕ ಆರಂಭ_Loc, ಪೂರ್ಣಾಂಕ ಉದ್ದಳತೆ);

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ Compare_ದತ್ತಾಂಶ(u16 *LhsPtr, u16 *RhsPtr, ಪೂರ್ಣಾಂಕ LhsLoc, ಪೂರ್ಣಾಂಕ RhsLoc,
			ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_3);

/************************** Variable Definitions *****************************/

/*
 * Set up a local MAC address.
 */
ಸ್ಥಿರ u8 LocalMacAddr[XEL_MAC_ADDR_ಗಾತ್ರ] =
{
	0x00, 0x0A, 0x35, 0x03, 0x02, 0x01
};

/*
 * The IP address was set to 172.16.63.121. User need to set a free IP address
 * based on the network on which this example is to be run.
 */
ಸ್ಥಿರ u8 Local_Ip_ವಿಳಾಸ[IP_ADDR_ಗಾತ್ರ] =
{
	192, 168, 1, 26
};

/*
 * Set up a Destination IP address. Currently it is set to 172.16.63.61.
 */
/* ifconfig enp1s0 172.16.63.61 netmask 255.255.255.0 up */
ಸ್ಥಿರ u8 Dest_Ip_ವಿಳಾಸ[IP_ADDR_ಗಾತ್ರ] =
{
	192, 168, 1, 25
};

ಸ್ಥಿರ u16 DestMacAddr[MAC_ADDR_LEN]; 	/* Destination MAC Address */
ಸ್ಥಿರ XEmacLite EmacLiteInstance;	/* Instance of the EmacLite driver */

/*
 * Known data transmitted in Echo request.
 */
u16 Icmp_ದತ್ತಾಂಶ[ICMP_ತಿಳಿದ_ದತ್ತಾಂಶ_LEN] =
{
	0x2122, 0x2324, 0x2526, 0x2728, 0x292A, 0x2B2C, 0x2D2E, 0x2F30,
	0x3132, 0x3334, 0x3536, 0x3738, 0x393A, 0x3B3C, 0x3D3E, 0x3F40,
	0x4142, 0x4344, 0x4546, 0x4748, 0x494A, 0x4B4C, 0x4D4E, 0x4F50,
	0x5152, 0x5354, 0x5556, 0x5758, 0x595A, 0x5B5C, 0x5D5E, 0x5F60,
	0x6162, 0x6364, 0x6566, 0x6768, 0x696A, 0x6B6C, 0x6D6E, 0x6F70,
	0x7172, 0x7374, 0x7576, 0x7778, 0x797A, 0x7B7C, 0x7D7E, 0x7F80,
	0x8182, 0x8384, 0x8586, 0x8788, 0x898A, 0x8B8C, 0x8D8E, 0X8F90,
	0x9192, 0x9394, 0x9596, 0x9798, 0x999a,  0x9b9c, 0x9d9e, 0x9fa0
};

/*
 * IP header information -- each field has its own significance.
 * Icmp type, ipv4 typelength, packet length, identification field
 * Fragment type, time to live and ICM, checksum.
 */
u16 Ip_ಶೀರ್ಷಿಕೆ_Info[IP_ಶೀರ್ಷಿಕೆ_INFO_LEN] =
{
	0x0800,	0x4500, 0x003C,	0x5566,	0x0000,	0x8001, 0x0000
};

/*
 * Buffers used for Transmission and Reception of Packets. These are declared as
 * global so that they are not a part of the stack.
 */
ಸ್ಥಿರ u8 Rx_ಚೌಕಟ್ಟು[XEL_MAX_ಚೌಕಟ್ಟು_ಗಾತ್ರ];
ಸ್ಥಿರ u8 Tx_ಚೌಕಟ್ಟು[XEL_MAX_ಚೌಕಟ್ಟು_ಗಾತ್ರ];

/*
 * Variable used to indicate the length of the received frame.
 */
ಬಾಹ್ಯ ಅಸ್ಥಿರ u32 Recv_ಚೌಕಟ್ಟು_ಉದ್ದಳತೆ;

/*
 * Variable used to indicate the sequence number of the ICMP(echo) packet.
 */
ಪೂರ್ಣಾಂಕ Seq_ಅಂಕೆ;

/*
 * Variable used to indicate the number of ping request packets to be send.
 */
ಪೂರ್ಣಾಂಕ ಅಂಕೆ_ದ_Ping_Req_Pkts;

/****************************************************************************/
/**
*
* This function is the main function of the Ping Request example in polled mode.
*
* @param	None.
*
* @return	XST_FAILURE to indicate failure, otherwise it will return
*		XST_SUCCESS after sending specified number of packets as
*		defined in "NUM_OF_PING_REQ_PKTS" .
*
* @note		None.
*
*****************************************************************************/
ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ()
{
	ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_2;

	/*
	 * Run the EmacLite Ping request example.
	 */
	ಸ್ಥಿತಿ_2 = EmacLitePingReqExample(EMAC_DEVICE_ID);
	ಆದರೆ (ಸ್ಥಿತಿ_2 != XST_SUCCESS) {
		xil_printf("Emaclite ping request Example Failed\r\n");
		ಹಿಂತಿರುಗಿ XST_FAILURE;
	}

	xil_printf("Successfully ran Emaclite ping request Example\r\n");
	ಹಿಂತಿರುಗಿ XST_SUCCESS;
}

/*****************************************************************************/
/**
*
* The entry point for the EmacLite driver to ping request example in polled
* mode. This function will generate specified number of request packets as
* defined in "NUM_OF_PING_REQ_PKTS.
*
* @param	DeviceId is device ID of the XEmacLite Device.
*
* @return	XST_FAILURE to indicate failure, otherwise it will return
*		XST_SUCCESS.
*
* @note		None.
*
******************************************************************************/
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ EmacLitePingReqExample(u16 DeviceId)
{
	ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_2;
	ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ;
	ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_3;
	ಪೂರ್ಣಾಂಕ Echo_ಉತ್ತರ_ಸ್ಥಿತಿ;
	XEmacLite_Config *ConfigPtr;
	XEmacLite *EmacLiteInstPtr = &EmacLiteInstance;
	Seq_ಅಂಕೆ = 0;
	Recv_ಚೌಕಟ್ಟು_ಉದ್ದಳತೆ = 0;
	Echo_ಉತ್ತರ_ಸ್ಥಿತಿ = XST_FAILURE;
	ಅಂಕೆ_ದ_Ping_Req_Pkts = ಅಂಕೆ_ದ_PING_REQ_PKTS;

	/*
	 * Initialize the EmacLite device.
	 */
	ConfigPtr = &XEmac_Lite_Config_ಕೋಷ್ಟಕ;
	ಆದರೆ (ConfigPtr == ಖಾಲಿ) {
		ಹಿಂತಿರುಗಿ -1;
	}
	ConfigPtr->ತಳ_ವಿಳಾಸ = (UINTPTR *) 0X44000;
	ConfigPtr->RxPingPong = XPAR_EMACLITE_0_RX_PING_PONG;
	ConfigPtr->MdioInclude = XPAR_EMACLITE_0_INCLUDE_MDIO;
	ConfigPtr->TxPingPong = XPAR_EMACLITE_0_TX_PING_PONG;
#ಆದರೆ 0
	log_debug("\n ConfigPtr: BaseAddress: %x", ConfigPtr->ತಳ_ವಿಳಾಸ);
	log_debug("\n ConfigPtr: DeviceId: %x", ConfigPtr->DeviceId);
	log_debug("\n ConfigPtr: TxPingPong: %x", ConfigPtr->TxPingPong);
	log_debug("\n ConfigPtr: RxPingPong: %x", ConfigPtr->RxPingPong);
	log_debug("\n ConfigPtr: MdioInclude: %x", ConfigPtr->MdioInclude);
	log_debug("\n ConfigPtr: Loopback: %x", ConfigPtr->Loopback);
#ಆದರೆ_ಅಂತ್ಯ	
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
	ಆಗ (ಅಂಕೆ_ದ_Ping_Req_Pkts--) {

		/*
		 * Introduce delay.
		 */
		ಎಣಿಕೆ_3 = DELAY;
		ಆಗ (ಎಣಿಕೆ_3--) {
		}

		/*
		 * Send an ARP or an ICMP packet based on receive packet.
		 */
		ಆದರೆ (Seq_ಅಂಕೆ == 0) {
			Send_Arp_Req_ಚೌಕಟ್ಟು(EmacLiteInstPtr);
		} ಇಲ್ಲದಿದ್ದರೆ {
			Send_Echo_Req_ಚೌಕಟ್ಟು(EmacLiteInstPtr);
		}

		/*
		 * Check next 10 packets for the correct reply.
		 */
		ಸೂಚ್ಯಂಕ = ಅಂಕೆ_RX_PACK_CHECK_REQ;
		ಆಗ (ಸೂಚ್ಯಂಕ--) {

			/*
			 * Wait for a Receive packet.
			 */
			ಎಣಿಕೆ_3 = ಅಂಕೆ_PACK_CHECK_RX_PACK;
			ಆಗ (Recv_ಚೌಕಟ್ಟು_ಉದ್ದಳತೆ == 0) {
				Recv_ಚೌಕಟ್ಟು_ಉದ್ದಳತೆ = XEmacLite_Recv(
							EmacLiteInstPtr,
							(u8 *)Rx_ಚೌಕಟ್ಟು);

				/*
				 * To avoid infinite loop when no packet is
				 * received.
				 */
				ಆದರೆ (ಎಣಿಕೆ_3-- == 0) {
					ನಿಲ್ಲಿಸು;
				}
			}

			/*
			 * Process the Receive frame.
			 */
			ಆದರೆ (Recv_ಚೌಕಟ್ಟು_ಉದ್ದಳತೆ != 0) {
				Echo_ಉತ್ತರ_ಸ್ಥಿತಿ = Process_Recv_ಚೌಕಟ್ಟು(
							EmacLiteInstPtr);
			}
			Recv_ಚೌಕಟ್ಟು_ಉದ್ದಳತೆ = 0;

			/*
			 * Comes out of loop when an echo reply packet is
			 * received.
			 */
			ಆದರೆ (Echo_ಉತ್ತರ_ಸ್ಥಿತಿ == XST_SUCCESS) {
				ನಿಲ್ಲಿಸು;
			}
		}

		/*
		 * If no echo reply packet is received, it reports
		 * request timed out.
		 */
		ಆದರೆ (Echo_ಉತ್ತರ_ಸ್ಥಿತಿ == XST_FAILURE) {
			xil_printf("Packet No: %d",
				ಅಂಕೆ_ದ_PING_REQ_PKTS - ಅಂಕೆ_ದ_Ping_Req_Pkts);
			xil_printf(" Seq NO %d Request timed out\r\n",
							Seq_ಅಂಕೆ);
		}
	}
	ಹಿಂತಿರುಗಿ XST_SUCCESS;
}

/*****************************************************************************/
/**
*
* This function will send a ARP request packet.
*
* @param	InstancePtr is a pointer to the instance of the EmacLite.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
ಸ್ಥಿರ ಶೂನ್ಯ Send_Arp_Req_ಚೌಕಟ್ಟು(XEmacLite *InstancePtr)
{
	u16 *ತಾತ್ಕಾಲಿಕ_Ptr;
	u16 *Tx_ಚೌಕಟ್ಟು_Ptr;
	u32 ಮುಂದಿನ_Tx_Buff_ತಳ_Addr;
	ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ;

	Tx_ಚೌಕಟ್ಟು_Ptr = (u16 *)Tx_ಚೌಕಟ್ಟು;

	/*
	 * Determine the next expected transmit buffer base address.
	 */
	ಮುಂದಿನ_Tx_Buff_ತಳ_Addr = XEmac_Lite_ಮುಂದಿನ_Transmit_Addr(InstancePtr);

	/*
	 * Add broadcast address.
	 */
	ಸೂಚ್ಯಂಕ = MAC_ADDR_LEN;
	ಆಗ (ಸೂಚ್ಯಂಕ--) {
		*Tx_ಚೌಕಟ್ಟು_Ptr++ = ಪ್ರಸಾರ_ADDR;
	}

	/*
	 * Add local MAC address.
	 */
	ಸೂಚ್ಯಂಕ = 0;
	ತಾತ್ಕಾಲಿಕ_Ptr = (u16 *)LocalMacAddr;
	ಆಗ (ಸೂಚ್ಯಂಕ < MAC_ADDR_LEN) {
		*Tx_ಚೌಕಟ್ಟು_Ptr++ = *(ತಾತ್ಕಾಲಿಕ_Ptr + ಸೂಚ್ಯಂಕ);
		ಸೂಚ್ಯಂಕ++;
	}

	/*
	 * Add
	 * 	- Ethernet proto type.
	 *	- Hardware Type
	 *	- Protocol IP Type
	 *	- IP version (IPv6/IPv4)
	 *	- ARP Request
	 */
	*Tx_ಚೌಕಟ್ಟು_Ptr++ = Xil_Htons(XEL_ETHER_PROTO_TYPE_ARP);
	*Tx_ಚೌಕಟ್ಟು_Ptr++ = Xil_Htons(HW_TYPE);
	*Tx_ಚೌಕಟ್ಟು_Ptr++ = Xil_Htons(XEL_ETHER_PROTO_TYPE_IP);
	*Tx_ಚೌಕಟ್ಟು_Ptr++ = Xil_Htons(IP_ಆವೃತ್ತಿ);
	*Tx_ಚೌಕಟ್ಟು_Ptr++ = Xil_Htons(ARP_REQUEST);

	/*
	 * Add local MAC address.
	 */
	ಸೂಚ್ಯಂಕ = 0;
	ತಾತ್ಕಾಲಿಕ_Ptr = (u16 *)LocalMacAddr;
	ಆಗ (ಸೂಚ್ಯಂಕ < MAC_ADDR_LEN) {
		*Tx_ಚೌಕಟ್ಟು_Ptr++ = *(ತಾತ್ಕಾಲಿಕ_Ptr + ಸೂಚ್ಯಂಕ);
		ಸೂಚ್ಯಂಕ++;
	}

	/*
	 * Add local IP address.
	 */
	ಸೂಚ್ಯಂಕ = 0;
	ತಾತ್ಕಾಲಿಕ_Ptr = (u16 *)Local_Ip_ವಿಳಾಸ;
	ಆಗ (ಸೂಚ್ಯಂಕ < IP_ADDR_LEN) {
		*Tx_ಚೌಕಟ್ಟು_Ptr++ = *(ತಾತ್ಕಾಲಿಕ_Ptr + ಸೂಚ್ಯಂಕ);
		ಸೂಚ್ಯಂಕ++;
	}

	/*
	 * Fills 6 bytes of information with zeros as per protocol.
	 */
	ಸೂಚ್ಯಂಕ = 0;
	ಆಗ (ಸೂಚ್ಯಂಕ < 3) {
		*Tx_ಚೌಕಟ್ಟು_Ptr++ = 0x0000;
		ಸೂಚ್ಯಂಕ++;
	}

	/*
	 * Add Destination IP address.
	 */
	ಸೂಚ್ಯಂಕ = 0;
	ತಾತ್ಕಾಲಿಕ_Ptr = (u16 *)Dest_Ip_ವಿಳಾಸ;
	ಆಗ (ಸೂಚ್ಯಂಕ < IP_ADDR_LEN) {
		*Tx_ಚೌಕಟ್ಟು_Ptr++ = *(ತಾತ್ಕಾಲಿಕ_Ptr + ಸೂಚ್ಯಂಕ);
		ಸೂಚ್ಯಂಕ++;
	}

	/*
	 * Transmit the Frame.
	 */
	XEmacLite_Send(InstancePtr, (u8 *)&Tx_ಚೌಕಟ್ಟು, ARP_REQ_PKT_ಗಾತ್ರ);
}

/*****************************************************************************/
/**
*
* This function will send a Echo request packet.
*
* @param	InstancePtr is a pointer to the instance of the EmacLite.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
ಸ್ಥಿರ ಶೂನ್ಯ Send_Echo_Req_ಚೌಕಟ್ಟು(XEmacLite *InstancePtr)
{
	u16 *ತಾತ್ಕಾಲಿಕ_Ptr;
	u16 *Tx_ಚೌಕಟ್ಟು_Ptr;
	u16 *Rx_ಚೌಕಟ್ಟು_Ptr;
	u16 Check_ಮೊತ್ತ;
	u32 ಮುಂದಿನ_Tx_Buff_ತಳ_Addr;
	ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ;

	Tx_ಚೌಕಟ್ಟು_Ptr = (u16 *)Tx_ಚೌಕಟ್ಟು;
	Rx_ಚೌಕಟ್ಟು_Ptr = (u16 *)Rx_ಚೌಕಟ್ಟು;

	/*
	 * Determine the next expected transmit buffer base address.
	 */
	ಮುಂದಿನ_Tx_Buff_ತಳ_Addr = XEmac_Lite_ಮುಂದಿನ_Transmit_Addr(InstancePtr);

	/*
	 * Add Destination MAC Address.
	 */
	ಸೂಚ್ಯಂಕ = MAC_ADDR_LEN;
	ಆಗ (ಸೂಚ್ಯಂಕ--) {
		*(Tx_ಚೌಕಟ್ಟು_Ptr + ಸೂಚ್ಯಂಕ) = *(DestMacAddr + ಸೂಚ್ಯಂಕ);
	}

	/*
	 * Add Source MAC Address.
	 */
	ಸೂಚ್ಯಂಕ = MAC_ADDR_LEN;
	ತಾತ್ಕಾಲಿಕ_Ptr = (u16 *)LocalMacAddr;
	ಆಗ (ಸೂಚ್ಯಂಕ--) {
		*(Tx_ಚೌಕಟ್ಟು_Ptr + (ಸೂಚ್ಯಂಕ + SRC_MAC_ADDR_LOC )) =
							*(ತಾತ್ಕಾಲಿಕ_Ptr + ಸೂಚ್ಯಂಕ);
	}

	/*
	 * Add IP header information.
	 */
	ಸೂಚ್ಯಂಕ = IP_ಆರಂಭ_LOC;
	ಆಗ (ಸೂಚ್ಯಂಕ--) {
		*(Tx_ಚೌಕಟ್ಟು_Ptr + (ಸೂಚ್ಯಂಕ + ETHER_PROTO_TYPE_LOC )) =
				Xil_Htons(*(Ip_ಶೀರ್ಷಿಕೆ_Info + ಸೂಚ್ಯಂಕ));
	}

	/*
	 * Add Source IP address.
	 */
	ಸೂಚ್ಯಂಕ = IP_ADDR_LEN;
	ತಾತ್ಕಾಲಿಕ_Ptr = (u16 *)Local_Ip_ವಿಳಾಸ;
	ಆಗ (ಸೂಚ್ಯಂಕ--) {
		*(Tx_ಚೌಕಟ್ಟು_Ptr + (ಸೂಚ್ಯಂಕ + IP_REQ_SRC_IP_LOC )) =
						*(ತಾತ್ಕಾಲಿಕ_Ptr + ಸೂಚ್ಯಂಕ);
	}

	/*
	 * Add Destination IP address.
	 */
	ಸೂಚ್ಯಂಕ = IP_ADDR_LEN;
	ತಾತ್ಕಾಲಿಕ_Ptr = (u16 *)Dest_Ip_ವಿಳಾಸ;
	ಆಗ (ಸೂಚ್ಯಂಕ--) {
		*(Tx_ಚೌಕಟ್ಟು_Ptr + (ಸೂಚ್ಯಂಕ + IP_REQ_DEST_IP_LOC )) =
						*(ತಾತ್ಕಾಲಿಕ_Ptr + ಸೂಚ್ಯಂಕ);
	}

	/*
	 * Checksum is calculated for IP field and added in the frame.
	 */
	Check_ಮೊತ್ತ = Check_ಮೊತ್ತ_Calculation((u16 *)Tx_ಚೌಕಟ್ಟು, IP_ಆರಂಭ_LOC,
							IP_ಶೀರ್ಷಿಕೆ_LEN);
	Check_ಮೊತ್ತ = ~Check_ಮೊತ್ತ;
	*(Tx_ಚೌಕಟ್ಟು_Ptr + IP_CHECKSUM_LOC) = Xil_Htons(Check_ಮೊತ್ತ);

	/*
	 * Add echo field information.
	 */
	*(Tx_ಚೌಕಟ್ಟು_Ptr + ICMP_ECHO_ಕ್ಷೇತ್ರ_LOC) = Xil_Htons(XEL_ETHER_PROTO_TYPE_IP);

	/*
	 * Checksum value is initialized to zeros.
	 */
	*(Tx_ಚೌಕಟ್ಟು_Ptr + ICMP_ದತ್ತಾಂಶ_LEN) = 0x0000;

	/*
	 * Add identifier and sequence number to the frame.
	 */
	*(Tx_ಚೌಕಟ್ಟು_Ptr + ICMP_IDEN_ಕ್ಷೇತ್ರ_LOC) = (IDEN_ಅಂಕೆ);
	*(Tx_ಚೌಕಟ್ಟು_Ptr + (ICMP_IDEN_ಕ್ಷೇತ್ರ_LOC + 1)) = Xil_Htons((u16)(++Seq_ಅಂಕೆ));

	/*
	 * Add known data to the frame.
	 */
	ಸೂಚ್ಯಂಕ = ICMP_ತಿಳಿದ_ದತ್ತಾಂಶ_LEN;
	ಆಗ (ಸೂಚ್ಯಂಕ--) {
		*(Tx_ಚೌಕಟ್ಟು_Ptr + (ಸೂಚ್ಯಂಕ + ICMP_ತಿಳಿದ_ದತ್ತಾಂಶ_LOC)) =
				Xil_Htons(*(Icmp_ದತ್ತಾಂಶ + ಸೂಚ್ಯಂಕ));
	}

	/*
	 * Checksum is calculated for Data Field and added in the frame.
	 */
	Check_ಮೊತ್ತ = Check_ಮೊತ್ತ_Calculation((u16 *)Tx_ಚೌಕಟ್ಟು, ICMP_ದತ್ತಾಂಶ_ಆರಂಭ_LOC,
						ICMP_ದತ್ತಾಂಶ_ಕ್ಷೇತ್ರ_LEN );
	Check_ಮೊತ್ತ = ~Check_ಮೊತ್ತ;
	*(Tx_ಚೌಕಟ್ಟು_Ptr + ICMP_ದತ್ತಾಂಶ_CHECKSUM_LOC) = Xil_Htons(Check_ಮೊತ್ತ);

	/*
	 * Transmit the Frame.
	 */
	XEmacLite_Send(InstancePtr, (u8 *)&Tx_ಚೌಕಟ್ಟು, ICMP_PKT_ಗಾತ್ರ);
}

/*****************************************************************************/
/**
*
* This function will process the received packet. This function sends
* the echo request packet based on the ARP reply packet.
*
* @param	InstancePtr is a pointer to the instance of the EmacLite.
*
* @return	XST_SUCCESS is returned when an echo reply is received.
*		Otherwise, XST_FAILURE is returned.
*
* @note		This assumes MAC does not strip padding or CRC.
*
******************************************************************************/
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ Process_Recv_ಚೌಕಟ್ಟು(XEmacLite *InstancePtr)
{
	u16 *Rx_ಚೌಕಟ್ಟು_Ptr;
	u16 *ತಾತ್ಕಾಲಿಕ_Ptr;
	u16 Check_ಮೊತ್ತ;
	ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ;
	ಪೂರ್ಣಾಂಕ ಹೊಂದಿಕೆ = 0;
	ಪೂರ್ಣಾಂಕ ದತ್ತಾಂಶ_Wrong = 0;

	Rx_ಚೌಕಟ್ಟು_Ptr = (u16 *)Rx_ಚೌಕಟ್ಟು;
	ತಾತ್ಕಾಲಿಕ_Ptr = (u16 *)LocalMacAddr;

	/*
	 * Check Dest Mac address of the packet with the LocalMac address.
	 */
	ಹೊಂದಿಕೆ = Compare_ದತ್ತಾಂಶ(Rx_ಚೌಕಟ್ಟು_Ptr, ತಾತ್ಕಾಲಿಕ_Ptr, 0, 0, MAC_ADDR_LEN);
	ಆದರೆ (ಹೊಂದಿಕೆ == XST_SUCCESS) {

		/*
		 * Check ARP type.
		 */
		ಆದರೆ (Xil_Ntohs(*(Rx_ಚೌಕಟ್ಟು_Ptr + ETHER_PROTO_TYPE_LOC)) ==
				XEL_ETHER_PROTO_TYPE_ARP ) {

			/*
			 * Check ARP status.
			 */
			ಆದರೆ (Xil_Ntohs(*(Rx_ಚೌಕಟ್ಟು_Ptr + ARP_REQ_ಸ್ಥಿತಿ_LOC)) == ARP_ಉತ್ತರ) {

				/*
				 * Check destination IP address with
				 * packet's source IP address.
				 */
				ತಾತ್ಕಾಲಿಕ_Ptr = (u16 *)Dest_Ip_ವಿಳಾಸ;
				ಹೊಂದಿಕೆ = Compare_ದತ್ತಾಂಶ(Rx_ಚೌಕಟ್ಟು_Ptr,
						ತಾತ್ಕಾಲಿಕ_Ptr, ARP_REQ_SRC_IP_LOC,
						0, IP_ADDR_LEN);
				ಆದರೆ (ಹೊಂದಿಕೆ == XST_SUCCESS) {

					/*
					 * Copy src Mac address of the received
					 * packet.
					 */
					ಸೂಚ್ಯಂಕ = MAC_ADDR_LEN;
					ತಾತ್ಕಾಲಿಕ_Ptr = (u16 *)DestMacAddr;
					ಆಗ (ಸೂಚ್ಯಂಕ--) {
						*(ತಾತ್ಕಾಲಿಕ_Ptr + ಸೂಚ್ಯಂಕ) =
							*(Rx_ಚೌಕಟ್ಟು_Ptr +
							(SRC_MAC_ADDR_LOC +
								ಸೂಚ್ಯಂಕ));
					}

					/*
					 * Send Echo request packet.
					 */
					Send_Echo_Req_ಚೌಕಟ್ಟು(InstancePtr);
				}
			}
		}

		/*
		 * Check for IP type.
		 */
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (Xil_Ntohs(*(Rx_ಚೌಕಟ್ಟು_Ptr + ETHER_PROTO_TYPE_LOC)) ==
						XEL_ETHER_PROTO_TYPE_IP) {

			/*
			 * Calculate checksum.
			 */
			Check_ಮೊತ್ತ = Check_ಮೊತ್ತ_Calculation(Rx_ಚೌಕಟ್ಟು_Ptr,
							ICMP_ದತ್ತಾಂಶ_ಆರಂಭ_LOC,
							ICMP_ದತ್ತಾಂಶ_ಕ್ಷೇತ್ರ_LEN);

			/*
			 * Verify checksum, echo reply, identifier number and
			 * sequence number of the received packet.
			 */
			ಆದರೆ ((Check_ಮೊತ್ತ == CORRECT_CHECKSUM_ಮೌಲ್ಯ) &&
			(Xil_Ntohs(*(Rx_ಚೌಕಟ್ಟು_Ptr + ICMP_ECHO_ಕ್ಷೇತ್ರ_LOC)) == ECHO_ಉತ್ತರ) &&
			(Xil_Ntohs(*(Rx_ಚೌಕಟ್ಟು_Ptr + ICMP_IDEN_ಕ್ಷೇತ್ರ_LOC)) == IDEN_ಅಂಕೆ) &&
			(Xil_Ntohs(*(Rx_ಚೌಕಟ್ಟು_Ptr + (ICMP_SEQ_NO_LOC))) == Seq_ಅಂಕೆ)) {

				/*
				 * Verify data in the received packet with known
				 * data.
				 */
				ತಾತ್ಕಾಲಿಕ_Ptr = Icmp_ದತ್ತಾಂಶ;
				ಹೊಂದಿಕೆ = Compare_ದತ್ತಾಂಶ(Rx_ಚೌಕಟ್ಟು_Ptr,
						ತಾತ್ಕಾಲಿಕ_Ptr, ICMP_ತಿಳಿದ_ದತ್ತಾಂಶ_LOC,
							0, ICMP_ತಿಳಿದ_ದತ್ತಾಂಶ_LEN);
				ಆದರೆ (ಹೊಂದಿಕೆ == XST_FAILURE) {
					ದತ್ತಾಂಶ_Wrong = 1;
				}
			}
			ಆದರೆ (ದತ್ತಾಂಶ_Wrong != 1) {
				xil_printf("Packet No: %d ",
				ಅಂಕೆ_ದ_PING_REQ_PKTS - ಅಂಕೆ_ದ_Ping_Req_Pkts);
				xil_printf("Seq NO %d Echo Packet received\r\n",
								Seq_ಅಂಕೆ);
				ಹಿಂತಿರುಗಿ XST_SUCCESS;
			}
		}
	}
	ಹಿಂತಿರುಗಿ XST_FAILURE;
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
		ಮೊತ್ತ = ಮೊತ್ತ + Xil_Htons(*(Rx_ಚೌಕಟ್ಟು_Ptr + ಸೂಚ್ಯಂಕ));
		ಸೂಚ್ಯಂಕ++;
	}

	/*
	 * Add upper 16 bits to lower 16 bits.
	 */
	Check_ಮೊತ್ತ = ಮೊತ್ತ;
	ಮೊತ್ತ = ಮೊತ್ತ>>16;
	Check_ಮೊತ್ತ = ಮೊತ್ತ + Check_ಮೊತ್ತ;
	ಹಿಂತಿರುಗಿ Check_ಮೊತ್ತ;
}
/*****************************************************************************/
/**
*
* This function checks the match for the specified number of half words.
*
* @param	LhsPtr is a LHS entity pointer.
* @param 	RhsPtr is a RHS entity pointer.
* @param	LhsLoc is a LHS entity location.
* @param 	RhsLoc is a RHS entity location.
* @param 	Count is the number of location which has to compared.
*
* @return	XST_SUCCESS is returned when both the entities are same,
*		otherwise XST_FAILURE is returned.
*
* @note		None.
*
******************************************************************************/
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ Compare_ದತ್ತಾಂಶ(u16 *LhsPtr, u16 *RhsPtr, ಪೂರ್ಣಾಂಕ LhsLoc, ಪೂರ್ಣಾಂಕ RhsLoc,
								ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_3)
{
	ಪೂರ್ಣಾಂಕ ಫಲಿತಾಂಶ;
	ಆಗ (ಎಣಿಕೆ_3--) {
		ಆದರೆ (*(LhsPtr + LhsLoc + ಎಣಿಕೆ_3) == *(RhsPtr + RhsLoc + ಎಣಿಕೆ_3)) {
			ಫಲಿತಾಂಶ = XST_SUCCESS;
		} ಇಲ್ಲದಿದ್ದರೆ {
			ಫಲಿತಾಂಶ = XST_FAILURE;
			ನಿಲ್ಲಿಸು;
		}
	}
	ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}
