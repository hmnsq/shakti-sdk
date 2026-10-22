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

#അന്തര്ഭാവ "gpio.h"
#അന്തര്ഭാവ "uart.h"
#അന്തര്ഭാവ "traps.h"
#അന്തര്ഭാവ "platform.h"
#അന്തര്ഭാവ "eth_driver.h"
#അന്തര്ഭാവ "log.h"




/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#define EMAC_DEVICE_ID			240
#define ETH_BASE_REG 0x44000
അസ്ഥിര unsigned പൂർണ്ണസംഖ്യ* eth_base_reg = ETH_BASE_REG;

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

ബാഹ്യ XEmacLite_Config XEmacLite_ConfigTable;

/************************** Variable Definitions *****************************/

/*
 * Instance of the driver
 */
സ്ഥിതം XEmacLite EmacLite;


/*
 * Change this parameter to limit the number of ping requests sent by this
 * program.
 */
#define അക്കം_OF_PING_REQ_PKTS	100	/* Number of ping req it generates */

#define ECHO_REPLY		0x00	/* Echo reply */
#define HW_TYPE			0x01	/* Hardware type (10/100 Mbps) */
#define ARP_REQUEST 		0x01	/* ARP Request bits in Rx packet */
#define ARP_REPLY 		0x02 	/* ARP status bits indicating reply */
#define IDEN_അക്കം		0x02	/* ICMP identifier number */
#define IP_VERSION		0x0604	/* IP version ipv4/ipv6 */
#define BROADCAST_ADDR 		0xFFFF 	/* Broadcast Address */
#define CORRECT_CHECKSUM_മൂല്യം	0xFFFF	/* Correct checksum value */
#define ARP_REQ_PKT_SIZE	0x2A	/* ARP request packet size */
#define ICMP_PKT_SIZE 		0x4A	/* ICMP packet length 74 Bytes
					including Src and dest MAC Add */
#define IP_ADDR_SIZE		4	/* IP Address size in Bytes */
#define അക്കം_RX_PACK_CHECK_REQ	10	/* Max num of Rx pack to be checked
					before sending another request */
#define അക്കം_PACK_CHECK_RX_PACK	100	/* Max number of pack to be checked
					before to identify a Rx packet */
#define DELAY			5000000 /* Used to introduce delay */

/*
 * Definitions for the locations and length of some of the fields in a
 * IP packet. The lengths are defined in Half-Words (2 bytes).
 */

#define SRC_MAC_ADDR_LOC	3	/* Src MAC address location */
#define MAC_ADDR_LEN 		3	/* MAC address length */
#define ETHER_PROTO_TYPE_LOC	6	/* Ethernet Proto type loc */

#define IP_ADDR_LEN 		2	/* Size of IP address */
#define IP_START_LOC 		7	/* IP header start location */
#define IP_HEADER_INFO_LEN	7	/* IP header information length */
#define IP_HEADER_LEN 		10 	/* IP header length */
#define IP_CHECKSUM_LOC		12	/* IP header checksum location */
#define IP_REQ_SRC_IP_LOC 	13	/* Src IP add loc of ICMP req */
#define IP_REQ_DEST_IP_LOC	15	/* Dest IP add loc of ICMP req */

#define ICMP_KNOWN_DATA_LEN	64	/* ICMP known data length */
#define ICMP_ECHO_FIELD_LOC 	17	/* Echo field loc */
#define ICMP_DATA_START_LOC 	17	/* Data field start location */
#define ICMP_DATA_LEN 		18	/* ICMP data length */
#define ICMP_DATA_CHECKSUM_LOC	18	/* ICMP data checksum location */
#define ICMP_IDEN_FIELD_LOC	19	/* Identifier field loc */
#define ICMP_DATA_LOC 		19	/* ICMP data loc including
					identifier number and sequence number */
#define ICMP_SEQ_NO_LOC		20	/* sequence number location */
#define ICMP_DATA_FIELD_LEN 	20 	/* Data field length */
#define ICMP_KNOWN_DATA_LOC	21	/* ICMP known data start loc */

#define ARP_REQ_STATUS_LOC 	10	/* ARP request loc */
#define ARP_REQ_SRC_IP_LOC 	14	/* Src IP add loc of ARP req Packet */

/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/

സ്ഥിതം പൂർണ്ണസംഖ്യ EmacLitePingReqExample(u16 DeviceId);

സ്ഥിതം ശൂന്യം SendArpReqFrame(XEmacLite *InstancePtr);

സ്ഥിതം ശൂന്യം SendEchoReqFrame(XEmacLite *InstancePtr);

സ്ഥിതം പൂർണ്ണസംഖ്യ ProcessRecvFrame(XEmacLite *InstancePtr);

സ്ഥിതം u16 CheckSumCalculation(u16 *RxFramePtr16, പൂർണ്ണസംഖ്യ StartLoc, പൂർണ്ണസംഖ്യ Length);

സ്ഥിതം പൂർണ്ണസംഖ്യ CompareData(u16 *LhsPtr, u16 *RhsPtr, പൂർണ്ണസംഖ്യ LhsLoc, പൂർണ്ണസംഖ്യ RhsLoc,
			പൂർണ്ണസംഖ്യ എണ്ണം_2);

/************************** Variable Definitions *****************************/

/*
 * Set up a local MAC address.
 */
സ്ഥിതം u8 LocalMacAddr[XEL_MAC_ADDR_SIZE] =
{
	0x00, 0x0A, 0x35, 0x03, 0x02, 0x01
};

/*
 * The IP address was set to 172.16.63.121. User need to set a free IP address
 * based on the network on which this example is to be run.
 */
സ്ഥിതം u8 LocalIpAddress[IP_ADDR_SIZE] =
{
	192, 168, 1, 26
};

/*
 * Set up a Destination IP address. Currently it is set to 172.16.63.61.
 */
/* ifconfig enp1s0 172.16.63.61 netmask 255.255.255.0 up */
സ്ഥിതം u8 DestIpAddress[IP_ADDR_SIZE] =
{
	192, 168, 1, 25
};

സ്ഥിതം u16 DestMacAddr[MAC_ADDR_LEN]; 	/* Destination MAC Address */
സ്ഥിതം XEmacLite EmacLiteInstance;	/* Instance of the EmacLite driver */

/*
 * Known data transmitted in Echo request.
 */
u16 IcmpData[ICMP_KNOWN_DATA_LEN] =
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
u16 IpHeaderInfo[IP_HEADER_INFO_LEN] =
{
	0x0800,	0x4500, 0x003C,	0x5566,	0x0000,	0x8001, 0x0000
};

/*
 * Buffers used for Transmission and Reception of Packets. These are declared as
 * global so that they are not a part of the stack.
 */
സ്ഥിതം u8 RxFrame[XEL_MAX_FRAME_SIZE];
സ്ഥിതം u8 TxFrame[XEL_MAX_FRAME_SIZE];

/*
 * Variable used to indicate the length of the received frame.
 */
ബാഹ്യ അസ്ഥിര u32 RecvFrameLength;

/*
 * Variable used to indicate the sequence number of the ICMP(echo) packet.
 */
പൂർണ്ണസംഖ്യ Seq_അക്കം;

/*
 * Variable used to indicate the number of ping request packets to be send.
 */
പൂർണ്ണസംഖ്യ അക്കം_Of_Ping_Req_Pkts;

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
പൂർണ്ണസംഖ്യ പ്രധാന()
{
	പൂർണ്ണസംഖ്യ Status;

	/*
	 * Run the EmacLite Ping request example.
	 */
	Status = EmacLitePingReqExample(EMAC_DEVICE_ID);
	എങ്കിൽ (Status != XST_SUCCESS) {
		xil_printf("Emaclite ping request Example Failed\r\n");
		തിരികെ XST_FAILURE;
	}

	xil_printf("Successfully ran Emaclite ping request Example\r\n");
	തിരികെ XST_SUCCESS;
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
സ്ഥിതം പൂർണ്ണസംഖ്യ EmacLitePingReqExample(u16 DeviceId)
{
	പൂർണ്ണസംഖ്യ Status;
	പൂർണ്ണസംഖ്യ Index;
	പൂർണ്ണസംഖ്യ എണ്ണം_2;
	പൂർണ്ണസംഖ്യ EchoReplyStatus;
	XEmacLite_Config *ConfigPtr;
	XEmacLite *EmacLiteInstPtr = &EmacLiteInstance;
	Seq_അക്കം = 0;
	RecvFrameLength = 0;
	EchoReplyStatus = XST_FAILURE;
	അക്കം_Of_Ping_Req_Pkts = അക്കം_OF_PING_REQ_PKTS;

	/*
	 * Initialize the EmacLite device.
	 */
	ConfigPtr = &XEmacLite_ConfigTable;
	എങ്കിൽ (ConfigPtr == ശൂന്യ) {
		തിരികെ -1;
	}
	ConfigPtr->BaseAddress = (UINTPTR *) 0X44000;
	ConfigPtr->RxPingPong = XPAR_EMACLITE_0_RX_PING_PONG;
	ConfigPtr->MdioInclude = XPAR_EMACLITE_0_INCLUDE_MDIO;
	ConfigPtr->TxPingPong = XPAR_EMACLITE_0_TX_PING_PONG;
#എങ്കിൽ 0
	log_debug("\n ConfigPtr: BaseAddress: %x", ConfigPtr->BaseAddress);
	log_debug("\n ConfigPtr: DeviceId: %x", ConfigPtr->DeviceId);
	log_debug("\n ConfigPtr: TxPingPong: %x", ConfigPtr->TxPingPong);
	log_debug("\n ConfigPtr: RxPingPong: %x", ConfigPtr->RxPingPong);
	log_debug("\n ConfigPtr: MdioInclude: %x", ConfigPtr->MdioInclude);
	log_debug("\n ConfigPtr: Loopback: %x", ConfigPtr->Loopback);
#endif	
	Status = XEmacLite_CfgInitialize(EmacLiteInstPtr,
					ConfigPtr,
					ConfigPtr->BaseAddress);
	എങ്കിൽ (Status != 0) {
		തിരികെ -1;
	}
	

	/*
	 * Set the MAC address.
	 */
	XEmacLite_SetMacAddress(EmacLiteInstPtr, LocalMacAddr);

	/*
	 * Empty any existing receive frames.
	 */
	XEmacLite_FlushReceive(EmacLiteInstPtr);
	ആകുമ്പോൾ (അക്കം_Of_Ping_Req_Pkts--) {

		/*
		 * Introduce delay.
		 */
		എണ്ണം_2 = DELAY;
		ആകുമ്പോൾ (എണ്ണം_2--) {
		}

		/*
		 * Send an ARP or an ICMP packet based on receive packet.
		 */
		എങ്കിൽ (Seq_അക്കം == 0) {
			SendArpReqFrame(EmacLiteInstPtr);
		} അല്ലെങ്കിൽ {
			SendEchoReqFrame(EmacLiteInstPtr);
		}

		/*
		 * Check next 10 packets for the correct reply.
		 */
		Index = അക്കം_RX_PACK_CHECK_REQ;
		ആകുമ്പോൾ (Index--) {

			/*
			 * Wait for a Receive packet.
			 */
			എണ്ണം_2 = അക്കം_PACK_CHECK_RX_PACK;
			ആകുമ്പോൾ (RecvFrameLength == 0) {
				RecvFrameLength = XEmacLite_Recv(
							EmacLiteInstPtr,
							(u8 *)RxFrame);

				/*
				 * To avoid infinite loop when no packet is
				 * received.
				 */
				എങ്കിൽ (എണ്ണം_2-- == 0) {
					നിർത്തുക;
				}
			}

			/*
			 * Process the Receive frame.
			 */
			എങ്കിൽ (RecvFrameLength != 0) {
				EchoReplyStatus = ProcessRecvFrame(
							EmacLiteInstPtr);
			}
			RecvFrameLength = 0;

			/*
			 * Comes out of loop when an echo reply packet is
			 * received.
			 */
			എങ്കിൽ (EchoReplyStatus == XST_SUCCESS) {
				നിർത്തുക;
			}
		}

		/*
		 * If no echo reply packet is received, it reports
		 * request timed out.
		 */
		എങ്കിൽ (EchoReplyStatus == XST_FAILURE) {
			xil_printf("Packet No: %d",
				അക്കം_OF_PING_REQ_PKTS - അക്കം_Of_Ping_Req_Pkts);
			xil_printf(" Seq NO %d Request timed out\r\n",
							Seq_അക്കം);
		}
	}
	തിരികെ XST_SUCCESS;
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
സ്ഥിതം ശൂന്യം SendArpReqFrame(XEmacLite *InstancePtr)
{
	u16 *TempPtr;
	u16 *TxFramePtr;
	u32 NextTxBuffBaseAddr;
	പൂർണ്ണസംഖ്യ Index;

	TxFramePtr = (u16 *)TxFrame;

	/*
	 * Determine the next expected transmit buffer base address.
	 */
	NextTxBuffBaseAddr = XEmacLite_NextTransmitAddr(InstancePtr);

	/*
	 * Add broadcast address.
	 */
	Index = MAC_ADDR_LEN;
	ആകുമ്പോൾ (Index--) {
		*TxFramePtr++ = BROADCAST_ADDR;
	}

	/*
	 * Add local MAC address.
	 */
	Index = 0;
	TempPtr = (u16 *)LocalMacAddr;
	ആകുമ്പോൾ (Index < MAC_ADDR_LEN) {
		*TxFramePtr++ = *(TempPtr + Index);
		Index++;
	}

	/*
	 * Add
	 * 	- Ethernet proto type.
	 *	- Hardware Type
	 *	- Protocol IP Type
	 *	- IP version (IPv6/IPv4)
	 *	- ARP Request
	 */
	*TxFramePtr++ = Xil_Htons(XEL_ETHER_PROTO_TYPE_ARP);
	*TxFramePtr++ = Xil_Htons(HW_TYPE);
	*TxFramePtr++ = Xil_Htons(XEL_ETHER_PROTO_TYPE_IP);
	*TxFramePtr++ = Xil_Htons(IP_VERSION);
	*TxFramePtr++ = Xil_Htons(ARP_REQUEST);

	/*
	 * Add local MAC address.
	 */
	Index = 0;
	TempPtr = (u16 *)LocalMacAddr;
	ആകുമ്പോൾ (Index < MAC_ADDR_LEN) {
		*TxFramePtr++ = *(TempPtr + Index);
		Index++;
	}

	/*
	 * Add local IP address.
	 */
	Index = 0;
	TempPtr = (u16 *)LocalIpAddress;
	ആകുമ്പോൾ (Index < IP_ADDR_LEN) {
		*TxFramePtr++ = *(TempPtr + Index);
		Index++;
	}

	/*
	 * Fills 6 bytes of information with zeros as per protocol.
	 */
	Index = 0;
	ആകുമ്പോൾ (Index < 3) {
		*TxFramePtr++ = 0x0000;
		Index++;
	}

	/*
	 * Add Destination IP address.
	 */
	Index = 0;
	TempPtr = (u16 *)DestIpAddress;
	ആകുമ്പോൾ (Index < IP_ADDR_LEN) {
		*TxFramePtr++ = *(TempPtr + Index);
		Index++;
	}

	/*
	 * Transmit the Frame.
	 */
	XEmacLite_Send(InstancePtr, (u8 *)&TxFrame, ARP_REQ_PKT_SIZE);
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
സ്ഥിതം ശൂന്യം SendEchoReqFrame(XEmacLite *InstancePtr)
{
	u16 *TempPtr;
	u16 *TxFramePtr;
	u16 *RxFramePtr;
	u16 CheckSum;
	u32 NextTxBuffBaseAddr;
	പൂർണ്ണസംഖ്യ Index;

	TxFramePtr = (u16 *)TxFrame;
	RxFramePtr = (u16 *)RxFrame;

	/*
	 * Determine the next expected transmit buffer base address.
	 */
	NextTxBuffBaseAddr = XEmacLite_NextTransmitAddr(InstancePtr);

	/*
	 * Add Destination MAC Address.
	 */
	Index = MAC_ADDR_LEN;
	ആകുമ്പോൾ (Index--) {
		*(TxFramePtr + Index) = *(DestMacAddr + Index);
	}

	/*
	 * Add Source MAC Address.
	 */
	Index = MAC_ADDR_LEN;
	TempPtr = (u16 *)LocalMacAddr;
	ആകുമ്പോൾ (Index--) {
		*(TxFramePtr + (Index + SRC_MAC_ADDR_LOC )) =
							*(TempPtr + Index);
	}

	/*
	 * Add IP header information.
	 */
	Index = IP_START_LOC;
	ആകുമ്പോൾ (Index--) {
		*(TxFramePtr + (Index + ETHER_PROTO_TYPE_LOC )) =
				Xil_Htons(*(IpHeaderInfo + Index));
	}

	/*
	 * Add Source IP address.
	 */
	Index = IP_ADDR_LEN;
	TempPtr = (u16 *)LocalIpAddress;
	ആകുമ്പോൾ (Index--) {
		*(TxFramePtr + (Index + IP_REQ_SRC_IP_LOC )) =
						*(TempPtr + Index);
	}

	/*
	 * Add Destination IP address.
	 */
	Index = IP_ADDR_LEN;
	TempPtr = (u16 *)DestIpAddress;
	ആകുമ്പോൾ (Index--) {
		*(TxFramePtr + (Index + IP_REQ_DEST_IP_LOC )) =
						*(TempPtr + Index);
	}

	/*
	 * Checksum is calculated for IP field and added in the frame.
	 */
	CheckSum = CheckSumCalculation((u16 *)TxFrame, IP_START_LOC,
							IP_HEADER_LEN);
	CheckSum = ~CheckSum;
	*(TxFramePtr + IP_CHECKSUM_LOC) = Xil_Htons(CheckSum);

	/*
	 * Add echo field information.
	 */
	*(TxFramePtr + ICMP_ECHO_FIELD_LOC) = Xil_Htons(XEL_ETHER_PROTO_TYPE_IP);

	/*
	 * Checksum value is initialized to zeros.
	 */
	*(TxFramePtr + ICMP_DATA_LEN) = 0x0000;

	/*
	 * Add identifier and sequence number to the frame.
	 */
	*(TxFramePtr + ICMP_IDEN_FIELD_LOC) = (IDEN_അക്കം);
	*(TxFramePtr + (ICMP_IDEN_FIELD_LOC + 1)) = Xil_Htons((u16)(++Seq_അക്കം));

	/*
	 * Add known data to the frame.
	 */
	Index = ICMP_KNOWN_DATA_LEN;
	ആകുമ്പോൾ (Index--) {
		*(TxFramePtr + (Index + ICMP_KNOWN_DATA_LOC)) =
				Xil_Htons(*(IcmpData + Index));
	}

	/*
	 * Checksum is calculated for Data Field and added in the frame.
	 */
	CheckSum = CheckSumCalculation((u16 *)TxFrame, ICMP_DATA_START_LOC,
						ICMP_DATA_FIELD_LEN );
	CheckSum = ~CheckSum;
	*(TxFramePtr + ICMP_DATA_CHECKSUM_LOC) = Xil_Htons(CheckSum);

	/*
	 * Transmit the Frame.
	 */
	XEmacLite_Send(InstancePtr, (u8 *)&TxFrame, ICMP_PKT_SIZE);
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
സ്ഥിതം പൂർണ്ണസംഖ്യ ProcessRecvFrame(XEmacLite *InstancePtr)
{
	u16 *RxFramePtr;
	u16 *TempPtr;
	u16 CheckSum;
	പൂർണ്ണസംഖ്യ Index;
	പൂർണ്ണസംഖ്യ Match = 0;
	പൂർണ്ണസംഖ്യ DataWrong = 0;

	RxFramePtr = (u16 *)RxFrame;
	TempPtr = (u16 *)LocalMacAddr;

	/*
	 * Check Dest Mac address of the packet with the LocalMac address.
	 */
	Match = CompareData(RxFramePtr, TempPtr, 0, 0, MAC_ADDR_LEN);
	എങ്കിൽ (Match == XST_SUCCESS) {

		/*
		 * Check ARP type.
		 */
		എങ്കിൽ (Xil_Ntohs(*(RxFramePtr + ETHER_PROTO_TYPE_LOC)) ==
				XEL_ETHER_PROTO_TYPE_ARP ) {

			/*
			 * Check ARP status.
			 */
			എങ്കിൽ (Xil_Ntohs(*(RxFramePtr + ARP_REQ_STATUS_LOC)) == ARP_REPLY) {

				/*
				 * Check destination IP address with
				 * packet's source IP address.
				 */
				TempPtr = (u16 *)DestIpAddress;
				Match = CompareData(RxFramePtr,
						TempPtr, ARP_REQ_SRC_IP_LOC,
						0, IP_ADDR_LEN);
				എങ്കിൽ (Match == XST_SUCCESS) {

					/*
					 * Copy src Mac address of the received
					 * packet.
					 */
					Index = MAC_ADDR_LEN;
					TempPtr = (u16 *)DestMacAddr;
					ആകുമ്പോൾ (Index--) {
						*(TempPtr + Index) =
							*(RxFramePtr +
							(SRC_MAC_ADDR_LOC +
								Index));
					}

					/*
					 * Send Echo request packet.
					 */
					SendEchoReqFrame(InstancePtr);
				}
			}
		}

		/*
		 * Check for IP type.
		 */
		അല്ലെങ്കിൽ എങ്കിൽ (Xil_Ntohs(*(RxFramePtr + ETHER_PROTO_TYPE_LOC)) ==
						XEL_ETHER_PROTO_TYPE_IP) {

			/*
			 * Calculate checksum.
			 */
			CheckSum = CheckSumCalculation(RxFramePtr,
							ICMP_DATA_START_LOC,
							ICMP_DATA_FIELD_LEN);

			/*
			 * Verify checksum, echo reply, identifier number and
			 * sequence number of the received packet.
			 */
			എങ്കിൽ ((CheckSum == CORRECT_CHECKSUM_മൂല്യം) &&
			(Xil_Ntohs(*(RxFramePtr + ICMP_ECHO_FIELD_LOC)) == ECHO_REPLY) &&
			(Xil_Ntohs(*(RxFramePtr + ICMP_IDEN_FIELD_LOC)) == IDEN_അക്കം) &&
			(Xil_Ntohs(*(RxFramePtr + (ICMP_SEQ_NO_LOC))) == Seq_അക്കം)) {

				/*
				 * Verify data in the received packet with known
				 * data.
				 */
				TempPtr = IcmpData;
				Match = CompareData(RxFramePtr,
						TempPtr, ICMP_KNOWN_DATA_LOC,
							0, ICMP_KNOWN_DATA_LEN);
				എങ്കിൽ (Match == XST_FAILURE) {
					DataWrong = 1;
				}
			}
			എങ്കിൽ (DataWrong != 1) {
				xil_printf("Packet No: %d ",
				അക്കം_OF_PING_REQ_PKTS - അക്കം_Of_Ping_Req_Pkts);
				xil_printf("Seq NO %d Echo Packet received\r\n",
								Seq_അക്കം);
				തിരികെ XST_SUCCESS;
			}
		}
	}
	തിരികെ XST_FAILURE;
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
സ്ഥിതം u16 CheckSumCalculation(u16 *RxFramePtr, പൂർണ്ണസംഖ്യ StartLoc, പൂർണ്ണസംഖ്യ Length)
{
	u32 Sum = 0;
	u16 CheckSum = 0;
	പൂർണ്ണസംഖ്യ Index;

	/*
	 * Add all the 16 bit data.
	 */
	Index = StartLoc;
	ആകുമ്പോൾ (Index < (StartLoc + Length)) {
		Sum = Sum + Xil_Htons(*(RxFramePtr + Index));
		Index++;
	}

	/*
	 * Add upper 16 bits to lower 16 bits.
	 */
	CheckSum = Sum;
	Sum = Sum>>16;
	CheckSum = Sum + CheckSum;
	തിരികെ CheckSum;
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
സ്ഥിതം പൂർണ്ണസംഖ്യ CompareData(u16 *LhsPtr, u16 *RhsPtr, പൂർണ്ണസംഖ്യ LhsLoc, പൂർണ്ണസംഖ്യ RhsLoc,
								പൂർണ്ണസംഖ്യ എണ്ണം_2)
{
	പൂർണ്ണസംഖ്യ Result;
	ആകുമ്പോൾ (എണ്ണം_2--) {
		എങ്കിൽ (*(LhsPtr + LhsLoc + എണ്ണം_2) == *(RhsPtr + RhsLoc + എണ്ണം_2)) {
			Result = XST_SUCCESS;
		} അല്ലെങ്കിൽ {
			Result = XST_FAILURE;
			നിർത്തുക;
		}
	}
	തിരികെ Result;
}
