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

#अन्तर्भाव "gpio.h"
#अन्तर्भाव "uart.h"
#अन्तर्भाव "traps.h"
#अन्तर्भाव "platform.h"
#अन्तर्भाव "eth_driver.h"
#अन्तर्भाव "log.h"




/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#define EMAC_DEVICE_ID			240
#define ETH_BASE_REG 0x44000
चञ्चल अचिन्हित पूर्णाङ्क* eth_base_reg = ETH_BASE_REG;

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

बाह्य XEmacLite_Config XEmacLite_ConfigTable;

/************************** Variable Definitions *****************************/

/*
 * Instance of the driver
 */
स्थिर XEmacLite EmacLite;


/*
 * Change this parameter to limit the number of ping requests sent by this
 * program.
 */
#define अङ्क_OF_PING_REQ_PKTS	100	/* Number of ping req it generates */

#define ECHO_REPLY		0x00	/* Echo reply */
#define HW_TYPE			0x01	/* Hardware type (10/100 Mbps) */
#define ARP_REQUEST 		0x01	/* ARP Request bits in Rx packet */
#define ARP_REPLY 		0x02 	/* ARP status bits indicating reply */
#define IDEN_अङ्क		0x02	/* ICMP identifier number */
#define IP_VERSION		0x0604	/* IP version ipv4/ipv6 */
#define BROADCAST_ADDR 		0xFFFF 	/* Broadcast Address */
#define CORRECT_CHECKSUM_मान	0xFFFF	/* Correct checksum value */
#define ARP_REQ_PKT_SIZE	0x2A	/* ARP request packet size */
#define ICMP_PKT_SIZE 		0x4A	/* ICMP packet length 74 Bytes
					including Src and dest MAC Add */
#define IP_ADDR_SIZE		4	/* IP Address size in Bytes */
#define अङ्क_RX_PACK_CHECK_REQ	10	/* Max num of Rx pack to be checked
					before sending another request */
#define अङ्क_PACK_CHECK_RX_PACK	100	/* Max number of pack to be checked
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

स्थिर पूर्णाङ्क EmacLitePingReqExample(u16 DeviceId);

स्थिर शून्य SendArpReqFrame(XEmacLite *InstancePtr);

स्थिर शून्य SendEchoReqFrame(XEmacLite *InstancePtr);

स्थिर पूर्णाङ्क ProcessRecvFrame(XEmacLite *InstancePtr);

स्थिर u16 CheckSumCalculation(u16 *RxFramePtr16, पूर्णाङ्क StartLoc, पूर्णाङ्क Length);

स्थिर पूर्णाङ्क CompareData(u16 *LhsPtr, u16 *RhsPtr, पूर्णाङ्क LhsLoc, पूर्णाङ्क RhsLoc,
			पूर्णाङ्क गन्ती_2);

/************************** Variable Definitions *****************************/

/*
 * Set up a local MAC address.
 */
स्थिर u8 LocalMacAddr[XEL_MAC_ADDR_SIZE] =
{
	0x00, 0x0A, 0x35, 0x03, 0x02, 0x01
};

/*
 * The IP address was set to 172.16.63.121. User need to set a free IP address
 * based on the network on which this example is to be run.
 */
स्थिर u8 LocalIpAddress[IP_ADDR_SIZE] =
{
	192, 168, 1, 26
};

/*
 * Set up a Destination IP address. Currently it is set to 172.16.63.61.
 */
/* ifconfig enp1s0 172.16.63.61 netmask 255.255.255.0 up */
स्थिर u8 DestIpAddress[IP_ADDR_SIZE] =
{
	192, 168, 1, 25
};

स्थिर u16 DestMacAddr[MAC_ADDR_LEN]; 	/* Destination MAC Address */
स्थिर XEmacLite EmacLiteInstance;	/* Instance of the EmacLite driver */

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
स्थिर u8 RxFrame[XEL_MAX_FRAME_SIZE];
स्थिर u8 TxFrame[XEL_MAX_FRAME_SIZE];

/*
 * Variable used to indicate the length of the received frame.
 */
बाह्य चञ्चल u32 RecvFrameLength;

/*
 * Variable used to indicate the sequence number of the ICMP(echo) packet.
 */
पूर्णाङ्क Seq_अङ्क;

/*
 * Variable used to indicate the number of ping request packets to be send.
 */
पूर्णाङ्क अङ्क_Of_Ping_Req_Pkts;

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
पूर्णाङ्क main()
{
	पूर्णाङ्क Status;

	/*
	 * Run the EmacLite Ping request example.
	 */
	Status = EmacLitePingReqExample(EMAC_DEVICE_ID);
	यदि (Status != XST_SUCCESS) {
		xil_printf("Emaclite ping request Example Failed\r\n");
		फर्काऊ XST_FAILURE;
	}

	xil_printf("Successfully ran Emaclite ping request Example\r\n");
	फर्काऊ XST_SUCCESS;
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
स्थिर पूर्णाङ्क EmacLitePingReqExample(u16 DeviceId)
{
	पूर्णाङ्क Status;
	पूर्णाङ्क Index;
	पूर्णाङ्क गन्ती_2;
	पूर्णाङ्क EchoReplyStatus;
	XEmacLite_Config *ConfigPtr;
	XEmacLite *EmacLiteInstPtr = &EmacLiteInstance;
	Seq_अङ्क = 0;
	RecvFrameLength = 0;
	EchoReplyStatus = XST_FAILURE;
	अङ्क_Of_Ping_Req_Pkts = अङ्क_OF_PING_REQ_PKTS;

	/*
	 * Initialize the EmacLite device.
	 */
	ConfigPtr = &XEmacLite_ConfigTable;
	यदि (ConfigPtr == रिक्त) {
		फर्काऊ -1;
	}
	ConfigPtr->BaseAddress = (UINTPTR *) 0X44000;
	ConfigPtr->RxPingPong = XPAR_EMACLITE_0_RX_PING_PONG;
	ConfigPtr->MdioInclude = XPAR_EMACLITE_0_INCLUDE_MDIO;
	ConfigPtr->TxPingPong = XPAR_EMACLITE_0_TX_PING_PONG;
#यदि 0
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
	यदि (Status != 0) {
		फर्काऊ -1;
	}
	

	/*
	 * Set the MAC address.
	 */
	XEmacLite_SetMacAddress(EmacLiteInstPtr, LocalMacAddr);

	/*
	 * Empty any existing receive frames.
	 */
	XEmacLite_FlushReceive(EmacLiteInstPtr);
	जबसम्म (अङ्क_Of_Ping_Req_Pkts--) {

		/*
		 * Introduce delay.
		 */
		गन्ती_2 = DELAY;
		जबसम्म (गन्ती_2--) {
		}

		/*
		 * Send an ARP or an ICMP packet based on receive packet.
		 */
		यदि (Seq_अङ्क == 0) {
			SendArpReqFrame(EmacLiteInstPtr);
		} अन्यथा {
			SendEchoReqFrame(EmacLiteInstPtr);
		}

		/*
		 * Check next 10 packets for the correct reply.
		 */
		Index = अङ्क_RX_PACK_CHECK_REQ;
		जबसम्म (Index--) {

			/*
			 * Wait for a Receive packet.
			 */
			गन्ती_2 = अङ्क_PACK_CHECK_RX_PACK;
			जबसम्म (RecvFrameLength == 0) {
				RecvFrameLength = XEmacLite_Recv(
							EmacLiteInstPtr,
							(u8 *)RxFrame);

				/*
				 * To avoid infinite loop when no packet is
				 * received.
				 */
				यदि (गन्ती_2-- == 0) {
					रोक;
				}
			}

			/*
			 * Process the Receive frame.
			 */
			यदि (RecvFrameLength != 0) {
				EchoReplyStatus = ProcessRecvFrame(
							EmacLiteInstPtr);
			}
			RecvFrameLength = 0;

			/*
			 * Comes out of loop when an echo reply packet is
			 * received.
			 */
			यदि (EchoReplyStatus == XST_SUCCESS) {
				रोक;
			}
		}

		/*
		 * If no echo reply packet is received, it reports
		 * request timed out.
		 */
		यदि (EchoReplyStatus == XST_FAILURE) {
			xil_printf("Packet No: %d",
				अङ्क_OF_PING_REQ_PKTS - अङ्क_Of_Ping_Req_Pkts);
			xil_printf(" Seq NO %d Request timed out\r\n",
							Seq_अङ्क);
		}
	}
	फर्काऊ XST_SUCCESS;
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
स्थिर शून्य SendArpReqFrame(XEmacLite *InstancePtr)
{
	u16 *TempPtr;
	u16 *TxFramePtr;
	u32 NextTxBuffBaseAddr;
	पूर्णाङ्क Index;

	TxFramePtr = (u16 *)TxFrame;

	/*
	 * Determine the next expected transmit buffer base address.
	 */
	NextTxBuffBaseAddr = XEmacLite_NextTransmitAddr(InstancePtr);

	/*
	 * Add broadcast address.
	 */
	Index = MAC_ADDR_LEN;
	जबसम्म (Index--) {
		*TxFramePtr++ = BROADCAST_ADDR;
	}

	/*
	 * Add local MAC address.
	 */
	Index = 0;
	TempPtr = (u16 *)LocalMacAddr;
	जबसम्म (Index < MAC_ADDR_LEN) {
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
	जबसम्म (Index < MAC_ADDR_LEN) {
		*TxFramePtr++ = *(TempPtr + Index);
		Index++;
	}

	/*
	 * Add local IP address.
	 */
	Index = 0;
	TempPtr = (u16 *)LocalIpAddress;
	जबसम्म (Index < IP_ADDR_LEN) {
		*TxFramePtr++ = *(TempPtr + Index);
		Index++;
	}

	/*
	 * Fills 6 bytes of information with zeros as per protocol.
	 */
	Index = 0;
	जबसम्म (Index < 3) {
		*TxFramePtr++ = 0x0000;
		Index++;
	}

	/*
	 * Add Destination IP address.
	 */
	Index = 0;
	TempPtr = (u16 *)DestIpAddress;
	जबसम्म (Index < IP_ADDR_LEN) {
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
स्थिर शून्य SendEchoReqFrame(XEmacLite *InstancePtr)
{
	u16 *TempPtr;
	u16 *TxFramePtr;
	u16 *RxFramePtr;
	u16 CheckSum;
	u32 NextTxBuffBaseAddr;
	पूर्णाङ्क Index;

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
	जबसम्म (Index--) {
		*(TxFramePtr + Index) = *(DestMacAddr + Index);
	}

	/*
	 * Add Source MAC Address.
	 */
	Index = MAC_ADDR_LEN;
	TempPtr = (u16 *)LocalMacAddr;
	जबसम्म (Index--) {
		*(TxFramePtr + (Index + SRC_MAC_ADDR_LOC )) =
							*(TempPtr + Index);
	}

	/*
	 * Add IP header information.
	 */
	Index = IP_START_LOC;
	जबसम्म (Index--) {
		*(TxFramePtr + (Index + ETHER_PROTO_TYPE_LOC )) =
				Xil_Htons(*(IpHeaderInfo + Index));
	}

	/*
	 * Add Source IP address.
	 */
	Index = IP_ADDR_LEN;
	TempPtr = (u16 *)LocalIpAddress;
	जबसम्म (Index--) {
		*(TxFramePtr + (Index + IP_REQ_SRC_IP_LOC )) =
						*(TempPtr + Index);
	}

	/*
	 * Add Destination IP address.
	 */
	Index = IP_ADDR_LEN;
	TempPtr = (u16 *)DestIpAddress;
	जबसम्म (Index--) {
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
	*(TxFramePtr + ICMP_IDEN_FIELD_LOC) = (IDEN_अङ्क);
	*(TxFramePtr + (ICMP_IDEN_FIELD_LOC + 1)) = Xil_Htons((u16)(++Seq_अङ्क));

	/*
	 * Add known data to the frame.
	 */
	Index = ICMP_KNOWN_DATA_LEN;
	जबसम्म (Index--) {
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
स्थिर पूर्णाङ्क ProcessRecvFrame(XEmacLite *InstancePtr)
{
	u16 *RxFramePtr;
	u16 *TempPtr;
	u16 CheckSum;
	पूर्णाङ्क Index;
	पूर्णाङ्क Match = 0;
	पूर्णाङ्क DataWrong = 0;

	RxFramePtr = (u16 *)RxFrame;
	TempPtr = (u16 *)LocalMacAddr;

	/*
	 * Check Dest Mac address of the packet with the LocalMac address.
	 */
	Match = CompareData(RxFramePtr, TempPtr, 0, 0, MAC_ADDR_LEN);
	यदि (Match == XST_SUCCESS) {

		/*
		 * Check ARP type.
		 */
		यदि (Xil_Ntohs(*(RxFramePtr + ETHER_PROTO_TYPE_LOC)) ==
				XEL_ETHER_PROTO_TYPE_ARP ) {

			/*
			 * Check ARP status.
			 */
			यदि (Xil_Ntohs(*(RxFramePtr + ARP_REQ_STATUS_LOC)) == ARP_REPLY) {

				/*
				 * Check destination IP address with
				 * packet's source IP address.
				 */
				TempPtr = (u16 *)DestIpAddress;
				Match = CompareData(RxFramePtr,
						TempPtr, ARP_REQ_SRC_IP_LOC,
						0, IP_ADDR_LEN);
				यदि (Match == XST_SUCCESS) {

					/*
					 * Copy src Mac address of the received
					 * packet.
					 */
					Index = MAC_ADDR_LEN;
					TempPtr = (u16 *)DestMacAddr;
					जबसम्म (Index--) {
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
		अन्यथा यदि (Xil_Ntohs(*(RxFramePtr + ETHER_PROTO_TYPE_LOC)) ==
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
			यदि ((CheckSum == CORRECT_CHECKSUM_मान) &&
			(Xil_Ntohs(*(RxFramePtr + ICMP_ECHO_FIELD_LOC)) == ECHO_REPLY) &&
			(Xil_Ntohs(*(RxFramePtr + ICMP_IDEN_FIELD_LOC)) == IDEN_अङ्क) &&
			(Xil_Ntohs(*(RxFramePtr + (ICMP_SEQ_NO_LOC))) == Seq_अङ्क)) {

				/*
				 * Verify data in the received packet with known
				 * data.
				 */
				TempPtr = IcmpData;
				Match = CompareData(RxFramePtr,
						TempPtr, ICMP_KNOWN_DATA_LOC,
							0, ICMP_KNOWN_DATA_LEN);
				यदि (Match == XST_FAILURE) {
					DataWrong = 1;
				}
			}
			यदि (DataWrong != 1) {
				xil_printf("Packet No: %d ",
				अङ्क_OF_PING_REQ_PKTS - अङ्क_Of_Ping_Req_Pkts);
				xil_printf("Seq NO %d Echo Packet received\r\n",
								Seq_अङ्क);
				फर्काऊ XST_SUCCESS;
			}
		}
	}
	फर्काऊ XST_FAILURE;
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
स्थिर u16 CheckSumCalculation(u16 *RxFramePtr, पूर्णाङ्क StartLoc, पूर्णाङ्क Length)
{
	u32 Sum = 0;
	u16 CheckSum = 0;
	पूर्णाङ्क Index;

	/*
	 * Add all the 16 bit data.
	 */
	Index = StartLoc;
	जबसम्म (Index < (StartLoc + Length)) {
		Sum = Sum + Xil_Htons(*(RxFramePtr + Index));
		Index++;
	}

	/*
	 * Add upper 16 bits to lower 16 bits.
	 */
	CheckSum = Sum;
	Sum = Sum>>16;
	CheckSum = Sum + CheckSum;
	फर्काऊ CheckSum;
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
स्थिर पूर्णाङ्क CompareData(u16 *LhsPtr, u16 *RhsPtr, पूर्णाङ्क LhsLoc, पूर्णाङ्क RhsLoc,
								पूर्णाङ्क गन्ती_2)
{
	पूर्णाङ्क Result;
	जबसम्म (गन्ती_2--) {
		यदि (*(LhsPtr + LhsLoc + गन्ती_2) == *(RhsPtr + RhsLoc + गन्ती_2)) {
			Result = XST_SUCCESS;
		} अन्यथा {
			Result = XST_FAILURE;
			रोक;
		}
	}
	फर्काऊ Result;
}
