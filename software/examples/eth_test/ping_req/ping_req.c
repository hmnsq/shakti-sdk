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

#অন্তর্ভাব "gpio.h"
#অন্তর্ভাব "uart.h"
#অন্তর্ভাব "traps.h"
#অন্তর্ভাব "platform.h"
#অন্তর্ভাব "eth_driver.h"
#অন্তর্ভাব "log.h"




/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#define EMAC_DEVICE_ID			240
#define ETH_BASE_REG 0x44000
অস্থির unsigned পূর্ণসংখ্যা* eth_base_reg = ETH_BASE_REG;

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

বাহ্যিক XEmacLite_Config XEmacLite_ConfigTable;

/************************** Variable Definitions *****************************/

/*
 * Instance of the driver
 */
স্থির XEmacLite EmacLite;


/*
 * Change this parameter to limit the number of ping requests sent by this
 * program.
 */
#define অঙ্ক_OF_PING_REQ_PKTS	100	/* Number of ping req it generates */

#define ECHO_REPLY		0x00	/* Echo reply */
#define HW_TYPE			0x01	/* Hardware type (10/100 Mbps) */
#define ARP_REQUEST 		0x01	/* ARP Request bits in Rx packet */
#define ARP_REPLY 		0x02 	/* ARP status bits indicating reply */
#define IDEN_অঙ্ক		0x02	/* ICMP identifier number */
#define IP_VERSION		0x0604	/* IP version ipv4/ipv6 */
#define BROADCAST_ADDR 		0xFFFF 	/* Broadcast Address */
#define CORRECT_CHECKSUM_মান	0xFFFF	/* Correct checksum value */
#define ARP_REQ_PKT_আকার	0x2A	/* ARP request packet size */
#define ICMP_PKT_আকার 		0x4A	/* ICMP packet length 74 Bytes
					including Src and dest MAC Add */
#define IP_ADDR_আকার		4	/* IP Address size in Bytes */
#define অঙ্ক_RX_PACK_CHECK_REQ	10	/* Max num of Rx pack to be checked
					before sending another request */
#define অঙ্ক_PACK_CHECK_RX_PACK	100	/* Max number of pack to be checked
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

#define ICMP_KNOWN_তথ্য_LEN	64	/* ICMP known data length */
#define ICMP_ECHO_FIELD_LOC 	17	/* Echo field loc */
#define ICMP_তথ্য_START_LOC 	17	/* Data field start location */
#define ICMP_তথ্য_LEN 		18	/* ICMP data length */
#define ICMP_তথ্য_CHECKSUM_LOC	18	/* ICMP data checksum location */
#define ICMP_IDEN_FIELD_LOC	19	/* Identifier field loc */
#define ICMP_তথ্য_LOC 		19	/* ICMP data loc including
					identifier number and sequence number */
#define ICMP_SEQ_NO_LOC		20	/* sequence number location */
#define ICMP_তথ্য_FIELD_LEN 	20 	/* Data field length */
#define ICMP_KNOWN_তথ্য_LOC	21	/* ICMP known data start loc */

#define ARP_REQ_STATUS_LOC 	10	/* ARP request loc */
#define ARP_REQ_SRC_IP_LOC 	14	/* Src IP add loc of ARP req Packet */

/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/

স্থির পূর্ণসংখ্যা EmacLitePingReqExample(u16 DeviceId);

স্থির শূন্য SendArpReqFrame(XEmacLite *InstancePtr);

স্থির শূন্য SendEchoReqFrame(XEmacLite *InstancePtr);

স্থির পূর্ণসংখ্যা ProcessRecvFrame(XEmacLite *InstancePtr);

স্থির u16 Check_যোগ_Calculation(u16 *RxFramePtr16, পূর্ণসংখ্যা StartLoc, পূর্ণসংখ্যা দৈর্ঘ্য);

স্থির পূর্ণসংখ্যা Compare_তথ্য(u16 *LhsPtr, u16 *RhsPtr, পূর্ণসংখ্যা LhsLoc, পূর্ণসংখ্যা RhsLoc,
			পূর্ণসংখ্যা গুনতি_2);

/************************** Variable Definitions *****************************/

/*
 * Set up a local MAC address.
 */
স্থির u8 LocalMacAddr[XEL_MAC_ADDR_আকার] =
{
	0x00, 0x0A, 0x35, 0x03, 0x02, 0x01
};

/*
 * The IP address was set to 172.16.63.121. User need to set a free IP address
 * based on the network on which this example is to be run.
 */
স্থির u8 LocalIpAddress[IP_ADDR_আকার] =
{
	192, 168, 1, 26
};

/*
 * Set up a Destination IP address. Currently it is set to 172.16.63.61.
 */
/* ifconfig enp1s0 172.16.63.61 netmask 255.255.255.0 up */
স্থির u8 DestIpAddress[IP_ADDR_আকার] =
{
	192, 168, 1, 25
};

স্থির u16 DestMacAddr[MAC_ADDR_LEN]; 	/* Destination MAC Address */
স্থির XEmacLite EmacLiteInstance;	/* Instance of the EmacLite driver */

/*
 * Known data transmitted in Echo request.
 */
u16 Icmp_তথ্য[ICMP_KNOWN_তথ্য_LEN] =
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
স্থির u8 RxFrame[XEL_MAX_FRAME_আকার];
স্থির u8 TxFrame[XEL_MAX_FRAME_আকার];

/*
 * Variable used to indicate the length of the received frame.
 */
বাহ্যিক অস্থির u32 Recv_Frame_দৈর্ঘ্য;

/*
 * Variable used to indicate the sequence number of the ICMP(echo) packet.
 */
পূর্ণসংখ্যা Seq_অঙ্ক;

/*
 * Variable used to indicate the number of ping request packets to be send.
 */
পূর্ণসংখ্যা অঙ্ক_Of_Ping_Req_Pkts;

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
পূর্ণসংখ্যা প্রধান()
{
	পূর্ণসংখ্যা Status;

	/*
	 * Run the EmacLite Ping request example.
	 */
	Status = EmacLitePingReqExample(EMAC_DEVICE_ID);
	যদি (Status != XST_SUCCESS) {
		xil_printf("Emaclite ping request Example Failed\r\n");
		ফেরত XST_FAILURE;
	}

	xil_printf("Successfully ran Emaclite ping request Example\r\n");
	ফেরত XST_SUCCESS;
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
স্থির পূর্ণসংখ্যা EmacLitePingReqExample(u16 DeviceId)
{
	পূর্ণসংখ্যা Status;
	পূর্ণসংখ্যা সূচক;
	পূর্ণসংখ্যা গুনতি_2;
	পূর্ণসংখ্যা EchoReplyStatus;
	XEmacLite_Config *ConfigPtr;
	XEmacLite *EmacLiteInstPtr = &EmacLiteInstance;
	Seq_অঙ্ক = 0;
	Recv_Frame_দৈর্ঘ্য = 0;
	EchoReplyStatus = XST_FAILURE;
	অঙ্ক_Of_Ping_Req_Pkts = অঙ্ক_OF_PING_REQ_PKTS;

	/*
	 * Initialize the EmacLite device.
	 */
	ConfigPtr = &XEmacLite_ConfigTable;
	যদি (ConfigPtr == ফাঁকা) {
		ফেরত -1;
	}
	ConfigPtr->BaseAddress = (UINTPTR *) 0X44000;
	ConfigPtr->RxPingPong = XPAR_EMACLITE_0_RX_PING_PONG;
	ConfigPtr->MdioInclude = XPAR_EMACLITE_0_INCLUDE_MDIO;
	ConfigPtr->TxPingPong = XPAR_EMACLITE_0_TX_PING_PONG;
#যদি 0
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
	যদি (Status != 0) {
		ফেরত -1;
	}
	

	/*
	 * Set the MAC address.
	 */
	XEmacLite_SetMacAddress(EmacLiteInstPtr, LocalMacAddr);

	/*
	 * Empty any existing receive frames.
	 */
	XEmacLite_FlushReceive(EmacLiteInstPtr);
	যখন (অঙ্ক_Of_Ping_Req_Pkts--) {

		/*
		 * Introduce delay.
		 */
		গুনতি_2 = DELAY;
		যখন (গুনতি_2--) {
		}

		/*
		 * Send an ARP or an ICMP packet based on receive packet.
		 */
		যদি (Seq_অঙ্ক == 0) {
			SendArpReqFrame(EmacLiteInstPtr);
		} অন্যথা {
			SendEchoReqFrame(EmacLiteInstPtr);
		}

		/*
		 * Check next 10 packets for the correct reply.
		 */
		সূচক = অঙ্ক_RX_PACK_CHECK_REQ;
		যখন (সূচক--) {

			/*
			 * Wait for a Receive packet.
			 */
			গুনতি_2 = অঙ্ক_PACK_CHECK_RX_PACK;
			যখন (Recv_Frame_দৈর্ঘ্য == 0) {
				Recv_Frame_দৈর্ঘ্য = XEmacLite_Recv(
							EmacLiteInstPtr,
							(u8 *)RxFrame);

				/*
				 * To avoid infinite loop when no packet is
				 * received.
				 */
				যদি (গুনতি_2-- == 0) {
					বিরতি;
				}
			}

			/*
			 * Process the Receive frame.
			 */
			যদি (Recv_Frame_দৈর্ঘ্য != 0) {
				EchoReplyStatus = ProcessRecvFrame(
							EmacLiteInstPtr);
			}
			Recv_Frame_দৈর্ঘ্য = 0;

			/*
			 * Comes out of loop when an echo reply packet is
			 * received.
			 */
			যদি (EchoReplyStatus == XST_SUCCESS) {
				বিরতি;
			}
		}

		/*
		 * If no echo reply packet is received, it reports
		 * request timed out.
		 */
		যদি (EchoReplyStatus == XST_FAILURE) {
			xil_printf("Packet No: %d",
				অঙ্ক_OF_PING_REQ_PKTS - অঙ্ক_Of_Ping_Req_Pkts);
			xil_printf(" Seq NO %d Request timed out\r\n",
							Seq_অঙ্ক);
		}
	}
	ফেরত XST_SUCCESS;
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
স্থির শূন্য SendArpReqFrame(XEmacLite *InstancePtr)
{
	u16 *অস্থায়ী_Ptr;
	u16 *TxFramePtr;
	u32 পরবর্তী_Tx_Buff_Base_Addr;
	পূর্ণসংখ্যা সূচক;

	TxFramePtr = (u16 *)TxFrame;

	/*
	 * Determine the next expected transmit buffer base address.
	 */
	পরবর্তী_Tx_Buff_Base_Addr = XEmac_Lite_পরবর্তী_Transmit_Addr(InstancePtr);

	/*
	 * Add broadcast address.
	 */
	সূচক = MAC_ADDR_LEN;
	যখন (সূচক--) {
		*TxFramePtr++ = BROADCAST_ADDR;
	}

	/*
	 * Add local MAC address.
	 */
	সূচক = 0;
	অস্থায়ী_Ptr = (u16 *)LocalMacAddr;
	যখন (সূচক < MAC_ADDR_LEN) {
		*TxFramePtr++ = *(অস্থায়ী_Ptr + সূচক);
		সূচক++;
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
	সূচক = 0;
	অস্থায়ী_Ptr = (u16 *)LocalMacAddr;
	যখন (সূচক < MAC_ADDR_LEN) {
		*TxFramePtr++ = *(অস্থায়ী_Ptr + সূচক);
		সূচক++;
	}

	/*
	 * Add local IP address.
	 */
	সূচক = 0;
	অস্থায়ী_Ptr = (u16 *)LocalIpAddress;
	যখন (সূচক < IP_ADDR_LEN) {
		*TxFramePtr++ = *(অস্থায়ী_Ptr + সূচক);
		সূচক++;
	}

	/*
	 * Fills 6 bytes of information with zeros as per protocol.
	 */
	সূচক = 0;
	যখন (সূচক < 3) {
		*TxFramePtr++ = 0x0000;
		সূচক++;
	}

	/*
	 * Add Destination IP address.
	 */
	সূচক = 0;
	অস্থায়ী_Ptr = (u16 *)DestIpAddress;
	যখন (সূচক < IP_ADDR_LEN) {
		*TxFramePtr++ = *(অস্থায়ী_Ptr + সূচক);
		সূচক++;
	}

	/*
	 * Transmit the Frame.
	 */
	XEmacLite_Send(InstancePtr, (u8 *)&TxFrame, ARP_REQ_PKT_আকার);
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
স্থির শূন্য SendEchoReqFrame(XEmacLite *InstancePtr)
{
	u16 *অস্থায়ী_Ptr;
	u16 *TxFramePtr;
	u16 *RxFramePtr;
	u16 Check_যোগ;
	u32 পরবর্তী_Tx_Buff_Base_Addr;
	পূর্ণসংখ্যা সূচক;

	TxFramePtr = (u16 *)TxFrame;
	RxFramePtr = (u16 *)RxFrame;

	/*
	 * Determine the next expected transmit buffer base address.
	 */
	পরবর্তী_Tx_Buff_Base_Addr = XEmac_Lite_পরবর্তী_Transmit_Addr(InstancePtr);

	/*
	 * Add Destination MAC Address.
	 */
	সূচক = MAC_ADDR_LEN;
	যখন (সূচক--) {
		*(TxFramePtr + সূচক) = *(DestMacAddr + সূচক);
	}

	/*
	 * Add Source MAC Address.
	 */
	সূচক = MAC_ADDR_LEN;
	অস্থায়ী_Ptr = (u16 *)LocalMacAddr;
	যখন (সূচক--) {
		*(TxFramePtr + (সূচক + SRC_MAC_ADDR_LOC )) =
							*(অস্থায়ী_Ptr + সূচক);
	}

	/*
	 * Add IP header information.
	 */
	সূচক = IP_START_LOC;
	যখন (সূচক--) {
		*(TxFramePtr + (সূচক + ETHER_PROTO_TYPE_LOC )) =
				Xil_Htons(*(IpHeaderInfo + সূচক));
	}

	/*
	 * Add Source IP address.
	 */
	সূচক = IP_ADDR_LEN;
	অস্থায়ী_Ptr = (u16 *)LocalIpAddress;
	যখন (সূচক--) {
		*(TxFramePtr + (সূচক + IP_REQ_SRC_IP_LOC )) =
						*(অস্থায়ী_Ptr + সূচক);
	}

	/*
	 * Add Destination IP address.
	 */
	সূচক = IP_ADDR_LEN;
	অস্থায়ী_Ptr = (u16 *)DestIpAddress;
	যখন (সূচক--) {
		*(TxFramePtr + (সূচক + IP_REQ_DEST_IP_LOC )) =
						*(অস্থায়ী_Ptr + সূচক);
	}

	/*
	 * Checksum is calculated for IP field and added in the frame.
	 */
	Check_যোগ = Check_যোগ_Calculation((u16 *)TxFrame, IP_START_LOC,
							IP_HEADER_LEN);
	Check_যোগ = ~Check_যোগ;
	*(TxFramePtr + IP_CHECKSUM_LOC) = Xil_Htons(Check_যোগ);

	/*
	 * Add echo field information.
	 */
	*(TxFramePtr + ICMP_ECHO_FIELD_LOC) = Xil_Htons(XEL_ETHER_PROTO_TYPE_IP);

	/*
	 * Checksum value is initialized to zeros.
	 */
	*(TxFramePtr + ICMP_তথ্য_LEN) = 0x0000;

	/*
	 * Add identifier and sequence number to the frame.
	 */
	*(TxFramePtr + ICMP_IDEN_FIELD_LOC) = (IDEN_অঙ্ক);
	*(TxFramePtr + (ICMP_IDEN_FIELD_LOC + 1)) = Xil_Htons((u16)(++Seq_অঙ্ক));

	/*
	 * Add known data to the frame.
	 */
	সূচক = ICMP_KNOWN_তথ্য_LEN;
	যখন (সূচক--) {
		*(TxFramePtr + (সূচক + ICMP_KNOWN_তথ্য_LOC)) =
				Xil_Htons(*(Icmp_তথ্য + সূচক));
	}

	/*
	 * Checksum is calculated for Data Field and added in the frame.
	 */
	Check_যোগ = Check_যোগ_Calculation((u16 *)TxFrame, ICMP_তথ্য_START_LOC,
						ICMP_তথ্য_FIELD_LEN );
	Check_যোগ = ~Check_যোগ;
	*(TxFramePtr + ICMP_তথ্য_CHECKSUM_LOC) = Xil_Htons(Check_যোগ);

	/*
	 * Transmit the Frame.
	 */
	XEmacLite_Send(InstancePtr, (u8 *)&TxFrame, ICMP_PKT_আকার);
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
স্থির পূর্ণসংখ্যা ProcessRecvFrame(XEmacLite *InstancePtr)
{
	u16 *RxFramePtr;
	u16 *অস্থায়ী_Ptr;
	u16 Check_যোগ;
	পূর্ণসংখ্যা সূচক;
	পূর্ণসংখ্যা Match = 0;
	পূর্ণসংখ্যা তথ্য_Wrong = 0;

	RxFramePtr = (u16 *)RxFrame;
	অস্থায়ী_Ptr = (u16 *)LocalMacAddr;

	/*
	 * Check Dest Mac address of the packet with the LocalMac address.
	 */
	Match = Compare_তথ্য(RxFramePtr, অস্থায়ী_Ptr, 0, 0, MAC_ADDR_LEN);
	যদি (Match == XST_SUCCESS) {

		/*
		 * Check ARP type.
		 */
		যদি (Xil_Ntohs(*(RxFramePtr + ETHER_PROTO_TYPE_LOC)) ==
				XEL_ETHER_PROTO_TYPE_ARP ) {

			/*
			 * Check ARP status.
			 */
			যদি (Xil_Ntohs(*(RxFramePtr + ARP_REQ_STATUS_LOC)) == ARP_REPLY) {

				/*
				 * Check destination IP address with
				 * packet's source IP address.
				 */
				অস্থায়ী_Ptr = (u16 *)DestIpAddress;
				Match = Compare_তথ্য(RxFramePtr,
						অস্থায়ী_Ptr, ARP_REQ_SRC_IP_LOC,
						0, IP_ADDR_LEN);
				যদি (Match == XST_SUCCESS) {

					/*
					 * Copy src Mac address of the received
					 * packet.
					 */
					সূচক = MAC_ADDR_LEN;
					অস্থায়ী_Ptr = (u16 *)DestMacAddr;
					যখন (সূচক--) {
						*(অস্থায়ী_Ptr + সূচক) =
							*(RxFramePtr +
							(SRC_MAC_ADDR_LOC +
								সূচক));
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
		অন্যথা যদি (Xil_Ntohs(*(RxFramePtr + ETHER_PROTO_TYPE_LOC)) ==
						XEL_ETHER_PROTO_TYPE_IP) {

			/*
			 * Calculate checksum.
			 */
			Check_যোগ = Check_যোগ_Calculation(RxFramePtr,
							ICMP_তথ্য_START_LOC,
							ICMP_তথ্য_FIELD_LEN);

			/*
			 * Verify checksum, echo reply, identifier number and
			 * sequence number of the received packet.
			 */
			যদি ((Check_যোগ == CORRECT_CHECKSUM_মান) &&
			(Xil_Ntohs(*(RxFramePtr + ICMP_ECHO_FIELD_LOC)) == ECHO_REPLY) &&
			(Xil_Ntohs(*(RxFramePtr + ICMP_IDEN_FIELD_LOC)) == IDEN_অঙ্ক) &&
			(Xil_Ntohs(*(RxFramePtr + (ICMP_SEQ_NO_LOC))) == Seq_অঙ্ক)) {

				/*
				 * Verify data in the received packet with known
				 * data.
				 */
				অস্থায়ী_Ptr = Icmp_তথ্য;
				Match = Compare_তথ্য(RxFramePtr,
						অস্থায়ী_Ptr, ICMP_KNOWN_তথ্য_LOC,
							0, ICMP_KNOWN_তথ্য_LEN);
				যদি (Match == XST_FAILURE) {
					তথ্য_Wrong = 1;
				}
			}
			যদি (তথ্য_Wrong != 1) {
				xil_printf("Packet No: %d ",
				অঙ্ক_OF_PING_REQ_PKTS - অঙ্ক_Of_Ping_Req_Pkts);
				xil_printf("Seq NO %d Echo Packet received\r\n",
								Seq_অঙ্ক);
				ফেরত XST_SUCCESS;
			}
		}
	}
	ফেরত XST_FAILURE;
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
স্থির u16 Check_যোগ_Calculation(u16 *RxFramePtr, পূর্ণসংখ্যা StartLoc, পূর্ণসংখ্যা দৈর্ঘ্য)
{
	u32 যোগ = 0;
	u16 Check_যোগ = 0;
	পূর্ণসংখ্যা সূচক;

	/*
	 * Add all the 16 bit data.
	 */
	সূচক = StartLoc;
	যখন (সূচক < (StartLoc + দৈর্ঘ্য)) {
		যোগ = যোগ + Xil_Htons(*(RxFramePtr + সূচক));
		সূচক++;
	}

	/*
	 * Add upper 16 bits to lower 16 bits.
	 */
	Check_যোগ = যোগ;
	যোগ = যোগ>>16;
	Check_যোগ = যোগ + Check_যোগ;
	ফেরত Check_যোগ;
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
স্থির পূর্ণসংখ্যা Compare_তথ্য(u16 *LhsPtr, u16 *RhsPtr, পূর্ণসংখ্যা LhsLoc, পূর্ণসংখ্যা RhsLoc,
								পূর্ণসংখ্যা গুনতি_2)
{
	পূর্ণসংখ্যা ফলাফল;
	যখন (গুনতি_2--) {
		যদি (*(LhsPtr + LhsLoc + গুনতি_2) == *(RhsPtr + RhsLoc + গুনতি_2)) {
			ফলাফল = XST_SUCCESS;
		} অন্যথা {
			ফলাফল = XST_FAILURE;
			বিরতি;
		}
	}
	ফেরত ফলাফল;
}
