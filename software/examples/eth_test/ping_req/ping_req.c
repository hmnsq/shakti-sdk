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

#ضمن "gpio.h"
#ضمن "uart.h"
#ضمن "traps.h"
#ضمن "platform.h"
#ضمن "eth_driver.h"
#ضمن "log.h"




/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#define EMAC_DEVICE_ID			240
#define ETH_BASE_REG 0x44000
متطاير unsigned صحيح* eth_base_reg = ETH_BASE_REG;

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

خارجي XEmacLite_Config XEmacLite_ConfigTable;

/************************** Variable Definitions *****************************/

/*
 * Instance of the driver
 */
ساكن XEmacLite EmacLite;


/*
 * Change this parameter to limit the number of ping requests sent by this
 * program.
 */
#define رقم_OF_PING_REQ_PKTS	100	/* Number of ping req it generates */

#define ECHO_REPLY		0x00	/* Echo reply */
#define HW_TYPE			0x01	/* Hardware type (10/100 Mbps) */
#define ARP_REQUEST 		0x01	/* ARP Request bits in Rx packet */
#define ARP_REPLY 		0x02 	/* ARP status bits indicating reply */
#define IDEN_رقم		0x02	/* ICMP identifier number */
#define IP_VERSION		0x0604	/* IP version ipv4/ipv6 */
#define BROADCAST_ADDR 		0xFFFF 	/* Broadcast Address */
#define CORRECT_CHECKSUM_قيمة	0xFFFF	/* Correct checksum value */
#define ARP_REQ_PKT_SIZE	0x2A	/* ARP request packet size */
#define ICMP_PKT_SIZE 		0x4A	/* ICMP packet length 74 Bytes
					including Src and dest MAC Add */
#define IP_ADDR_SIZE		4	/* IP Address size in Bytes */
#define رقم_RX_PACK_CHECK_REQ	10	/* Max num of Rx pack to be checked
					before sending another request */
#define رقم_PACK_CHECK_RX_PACK	100	/* Max number of pack to be checked
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

ساكن صحيح EmacLitePingReqExample(u16 DeviceId);

ساكن فراغ SendArpReqFrame(XEmacLite *InstancePtr);

ساكن فراغ SendEchoReqFrame(XEmacLite *InstancePtr);

ساكن صحيح ProcessRecvFrame(XEmacLite *InstancePtr);

ساكن u16 CheckSumCalculation(u16 *RxFramePtr16, صحيح StartLoc, صحيح Length);

ساكن صحيح CompareData(u16 *LhsPtr, u16 *RhsPtr, صحيح LhsLoc, صحيح RhsLoc,
			صحيح عدد_2);

/************************** Variable Definitions *****************************/

/*
 * Set up a local MAC address.
 */
ساكن u8 LocalMacAddr[XEL_MAC_ADDR_SIZE] =
{
	0x00, 0x0A, 0x35, 0x03, 0x02, 0x01
};

/*
 * The IP address was set to 172.16.63.121. User need to set a free IP address
 * based on the network on which this example is to be run.
 */
ساكن u8 LocalIpAddress[IP_ADDR_SIZE] =
{
	192, 168, 1, 26
};

/*
 * Set up a Destination IP address. Currently it is set to 172.16.63.61.
 */
/* ifconfig enp1s0 172.16.63.61 netmask 255.255.255.0 up */
ساكن u8 DestIpAddress[IP_ADDR_SIZE] =
{
	192, 168, 1, 25
};

ساكن u16 DestMacAddr[MAC_ADDR_LEN]; 	/* Destination MAC Address */
ساكن XEmacLite EmacLiteInstance;	/* Instance of the EmacLite driver */

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
ساكن u8 RxFrame[XEL_MAX_FRAME_SIZE];
ساكن u8 TxFrame[XEL_MAX_FRAME_SIZE];

/*
 * Variable used to indicate the length of the received frame.
 */
خارجي متطاير u32 RecvFrameLength;

/*
 * Variable used to indicate the sequence number of the ICMP(echo) packet.
 */
صحيح Seq_رقم;

/*
 * Variable used to indicate the number of ping request packets to be send.
 */
صحيح رقم_Of_Ping_Req_Pkts;

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
صحيح main()
{
	صحيح Status;

	/*
	 * Run the EmacLite Ping request example.
	 */
	Status = EmacLitePingReqExample(EMAC_DEVICE_ID);
	إذا (Status != XST_SUCCESS) {
		xil_printf("Emaclite ping request Example Failed\r\n");
		أرجع XST_FAILURE;
	}

	xil_printf("Successfully ran Emaclite ping request Example\r\n");
	أرجع XST_SUCCESS;
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
ساكن صحيح EmacLitePingReqExample(u16 DeviceId)
{
	صحيح Status;
	صحيح Index;
	صحيح عدد_2;
	صحيح EchoReplyStatus;
	XEmacLite_Config *ConfigPtr;
	XEmacLite *EmacLiteInstPtr = &EmacLiteInstance;
	Seq_رقم = 0;
	RecvFrameLength = 0;
	EchoReplyStatus = XST_FAILURE;
	رقم_Of_Ping_Req_Pkts = رقم_OF_PING_REQ_PKTS;

	/*
	 * Initialize the EmacLite device.
	 */
	ConfigPtr = &XEmacLite_ConfigTable;
	إذا (ConfigPtr == عدم) {
		أرجع -1;
	}
	ConfigPtr->BaseAddress = (UINTPTR *) 0X44000;
	ConfigPtr->RxPingPong = XPAR_EMACLITE_0_RX_PING_PONG;
	ConfigPtr->MdioInclude = XPAR_EMACLITE_0_INCLUDE_MDIO;
	ConfigPtr->TxPingPong = XPAR_EMACLITE_0_TX_PING_PONG;
#إذا 0
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
	إذا (Status != 0) {
		أرجع -1;
	}
	

	/*
	 * Set the MAC address.
	 */
	XEmacLite_SetMacAddress(EmacLiteInstPtr, LocalMacAddr);

	/*
	 * Empty any existing receive frames.
	 */
	XEmacLite_FlushReceive(EmacLiteInstPtr);
	طالما (رقم_Of_Ping_Req_Pkts--) {

		/*
		 * Introduce delay.
		 */
		عدد_2 = DELAY;
		طالما (عدد_2--) {
		}

		/*
		 * Send an ARP or an ICMP packet based on receive packet.
		 */
		إذا (Seq_رقم == 0) {
			SendArpReqFrame(EmacLiteInstPtr);
		} وإلا {
			SendEchoReqFrame(EmacLiteInstPtr);
		}

		/*
		 * Check next 10 packets for the correct reply.
		 */
		Index = رقم_RX_PACK_CHECK_REQ;
		طالما (Index--) {

			/*
			 * Wait for a Receive packet.
			 */
			عدد_2 = رقم_PACK_CHECK_RX_PACK;
			طالما (RecvFrameLength == 0) {
				RecvFrameLength = XEmacLite_Recv(
							EmacLiteInstPtr,
							(u8 *)RxFrame);

				/*
				 * To avoid infinite loop when no packet is
				 * received.
				 */
				إذا (عدد_2-- == 0) {
					اكسر;
				}
			}

			/*
			 * Process the Receive frame.
			 */
			إذا (RecvFrameLength != 0) {
				EchoReplyStatus = ProcessRecvFrame(
							EmacLiteInstPtr);
			}
			RecvFrameLength = 0;

			/*
			 * Comes out of loop when an echo reply packet is
			 * received.
			 */
			إذا (EchoReplyStatus == XST_SUCCESS) {
				اكسر;
			}
		}

		/*
		 * If no echo reply packet is received, it reports
		 * request timed out.
		 */
		إذا (EchoReplyStatus == XST_FAILURE) {
			xil_printf("Packet No: %d",
				رقم_OF_PING_REQ_PKTS - رقم_Of_Ping_Req_Pkts);
			xil_printf(" Seq NO %d Request timed out\r\n",
							Seq_رقم);
		}
	}
	أرجع XST_SUCCESS;
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
ساكن فراغ SendArpReqFrame(XEmacLite *InstancePtr)
{
	u16 *TempPtr;
	u16 *TxFramePtr;
	u32 NextTxBuffBaseAddr;
	صحيح Index;

	TxFramePtr = (u16 *)TxFrame;

	/*
	 * Determine the next expected transmit buffer base address.
	 */
	NextTxBuffBaseAddr = XEmacLite_NextTransmitAddr(InstancePtr);

	/*
	 * Add broadcast address.
	 */
	Index = MAC_ADDR_LEN;
	طالما (Index--) {
		*TxFramePtr++ = BROADCAST_ADDR;
	}

	/*
	 * Add local MAC address.
	 */
	Index = 0;
	TempPtr = (u16 *)LocalMacAddr;
	طالما (Index < MAC_ADDR_LEN) {
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
	طالما (Index < MAC_ADDR_LEN) {
		*TxFramePtr++ = *(TempPtr + Index);
		Index++;
	}

	/*
	 * Add local IP address.
	 */
	Index = 0;
	TempPtr = (u16 *)LocalIpAddress;
	طالما (Index < IP_ADDR_LEN) {
		*TxFramePtr++ = *(TempPtr + Index);
		Index++;
	}

	/*
	 * Fills 6 bytes of information with zeros as per protocol.
	 */
	Index = 0;
	طالما (Index < 3) {
		*TxFramePtr++ = 0x0000;
		Index++;
	}

	/*
	 * Add Destination IP address.
	 */
	Index = 0;
	TempPtr = (u16 *)DestIpAddress;
	طالما (Index < IP_ADDR_LEN) {
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
ساكن فراغ SendEchoReqFrame(XEmacLite *InstancePtr)
{
	u16 *TempPtr;
	u16 *TxFramePtr;
	u16 *RxFramePtr;
	u16 CheckSum;
	u32 NextTxBuffBaseAddr;
	صحيح Index;

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
	طالما (Index--) {
		*(TxFramePtr + Index) = *(DestMacAddr + Index);
	}

	/*
	 * Add Source MAC Address.
	 */
	Index = MAC_ADDR_LEN;
	TempPtr = (u16 *)LocalMacAddr;
	طالما (Index--) {
		*(TxFramePtr + (Index + SRC_MAC_ADDR_LOC )) =
							*(TempPtr + Index);
	}

	/*
	 * Add IP header information.
	 */
	Index = IP_START_LOC;
	طالما (Index--) {
		*(TxFramePtr + (Index + ETHER_PROTO_TYPE_LOC )) =
				Xil_Htons(*(IpHeaderInfo + Index));
	}

	/*
	 * Add Source IP address.
	 */
	Index = IP_ADDR_LEN;
	TempPtr = (u16 *)LocalIpAddress;
	طالما (Index--) {
		*(TxFramePtr + (Index + IP_REQ_SRC_IP_LOC )) =
						*(TempPtr + Index);
	}

	/*
	 * Add Destination IP address.
	 */
	Index = IP_ADDR_LEN;
	TempPtr = (u16 *)DestIpAddress;
	طالما (Index--) {
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
	*(TxFramePtr + ICMP_IDEN_FIELD_LOC) = (IDEN_رقم);
	*(TxFramePtr + (ICMP_IDEN_FIELD_LOC + 1)) = Xil_Htons((u16)(++Seq_رقم));

	/*
	 * Add known data to the frame.
	 */
	Index = ICMP_KNOWN_DATA_LEN;
	طالما (Index--) {
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
ساكن صحيح ProcessRecvFrame(XEmacLite *InstancePtr)
{
	u16 *RxFramePtr;
	u16 *TempPtr;
	u16 CheckSum;
	صحيح Index;
	صحيح Match = 0;
	صحيح DataWrong = 0;

	RxFramePtr = (u16 *)RxFrame;
	TempPtr = (u16 *)LocalMacAddr;

	/*
	 * Check Dest Mac address of the packet with the LocalMac address.
	 */
	Match = CompareData(RxFramePtr, TempPtr, 0, 0, MAC_ADDR_LEN);
	إذا (Match == XST_SUCCESS) {

		/*
		 * Check ARP type.
		 */
		إذا (Xil_Ntohs(*(RxFramePtr + ETHER_PROTO_TYPE_LOC)) ==
				XEL_ETHER_PROTO_TYPE_ARP ) {

			/*
			 * Check ARP status.
			 */
			إذا (Xil_Ntohs(*(RxFramePtr + ARP_REQ_STATUS_LOC)) == ARP_REPLY) {

				/*
				 * Check destination IP address with
				 * packet's source IP address.
				 */
				TempPtr = (u16 *)DestIpAddress;
				Match = CompareData(RxFramePtr,
						TempPtr, ARP_REQ_SRC_IP_LOC,
						0, IP_ADDR_LEN);
				إذا (Match == XST_SUCCESS) {

					/*
					 * Copy src Mac address of the received
					 * packet.
					 */
					Index = MAC_ADDR_LEN;
					TempPtr = (u16 *)DestMacAddr;
					طالما (Index--) {
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
		وإلا إذا (Xil_Ntohs(*(RxFramePtr + ETHER_PROTO_TYPE_LOC)) ==
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
			إذا ((CheckSum == CORRECT_CHECKSUM_قيمة) &&
			(Xil_Ntohs(*(RxFramePtr + ICMP_ECHO_FIELD_LOC)) == ECHO_REPLY) &&
			(Xil_Ntohs(*(RxFramePtr + ICMP_IDEN_FIELD_LOC)) == IDEN_رقم) &&
			(Xil_Ntohs(*(RxFramePtr + (ICMP_SEQ_NO_LOC))) == Seq_رقم)) {

				/*
				 * Verify data in the received packet with known
				 * data.
				 */
				TempPtr = IcmpData;
				Match = CompareData(RxFramePtr,
						TempPtr, ICMP_KNOWN_DATA_LOC,
							0, ICMP_KNOWN_DATA_LEN);
				إذا (Match == XST_FAILURE) {
					DataWrong = 1;
				}
			}
			إذا (DataWrong != 1) {
				xil_printf("Packet No: %d ",
				رقم_OF_PING_REQ_PKTS - رقم_Of_Ping_Req_Pkts);
				xil_printf("Seq NO %d Echo Packet received\r\n",
								Seq_رقم);
				أرجع XST_SUCCESS;
			}
		}
	}
	أرجع XST_FAILURE;
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
ساكن u16 CheckSumCalculation(u16 *RxFramePtr, صحيح StartLoc, صحيح Length)
{
	u32 Sum = 0;
	u16 CheckSum = 0;
	صحيح Index;

	/*
	 * Add all the 16 bit data.
	 */
	Index = StartLoc;
	طالما (Index < (StartLoc + Length)) {
		Sum = Sum + Xil_Htons(*(RxFramePtr + Index));
		Index++;
	}

	/*
	 * Add upper 16 bits to lower 16 bits.
	 */
	CheckSum = Sum;
	Sum = Sum>>16;
	CheckSum = Sum + CheckSum;
	أرجع CheckSum;
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
ساكن صحيح CompareData(u16 *LhsPtr, u16 *RhsPtr, صحيح LhsLoc, صحيح RhsLoc,
								صحيح عدد_2)
{
	صحيح Result;
	طالما (عدد_2--) {
		إذا (*(LhsPtr + LhsLoc + عدد_2) == *(RhsPtr + RhsLoc + عدد_2)) {
			Result = XST_SUCCESS;
		} وإلا {
			Result = XST_FAILURE;
			اكسر;
		}
	}
	أرجع Result;
}
