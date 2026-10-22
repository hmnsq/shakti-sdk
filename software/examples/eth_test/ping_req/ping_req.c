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

#समावेश "gpio.h"
#समावेश "uart.h"
#समावेश "traps.h"
#समावेश "platform.h"
#समावेश "eth_driver.h"
#समावेश "log.h"




/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#घोषणा EMAC_DEVICE_ID			240
#घोषणा ETH_BASE_REG 0x44000
अस्थिर अचिन्हित पूर्णांक* eth_base_reg = ETH_BASE_REG;

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

बाह्य XEmacLite_Config XEmacLite_ConfigTable;

/************************** Variable Definitions *****************************/

/*
 * Instance of the driver
 */
अटल XEmacLite EmacLite;


/*
 * Change this parameter to limit the number of ping requests sent by this
 * program.
 */
#घोषणा अंक_OF_PING_REQ_PKTS	100	/* Number of ping req it generates */

#घोषणा ECHO_REPLY		0x00	/* Echo reply */
#घोषणा HW_TYPE			0x01	/* Hardware type (10/100 Mbps) */
#घोषणा ARP_REQUEST 		0x01	/* ARP Request bits in Rx packet */
#घोषणा ARP_REPLY 		0x02 	/* ARP status bits indicating reply */
#घोषणा IDEN_अंक		0x02	/* ICMP identifier number */
#घोषणा IP_VERSION		0x0604	/* IP version ipv4/ipv6 */
#घोषणा BROADCAST_ADDR 		0xFFFF 	/* Broadcast Address */
#घोषणा CORRECT_CHECKSUM_मूल्य	0xFFFF	/* Correct checksum value */
#घोषणा ARP_REQ_PKT_आकार	0x2A	/* ARP request packet size */
#घोषणा ICMP_PKT_आकार 		0x4A	/* ICMP packet length 74 Bytes
					including Src and dest MAC Add */
#घोषणा IP_ADDR_आकार		4	/* IP Address size in Bytes */
#घोषणा अंक_RX_PACK_CHECK_REQ	10	/* Max num of Rx pack to be checked
					before sending another request */
#घोषणा अंक_PACK_CHECK_RX_PACK	100	/* Max number of pack to be checked
					before to identify a Rx packet */
#घोषणा DELAY			5000000 /* Used to introduce delay */

/*
 * Definitions for the locations and length of some of the fields in a
 * IP packet. The lengths are defined in Half-Words (2 bytes).
 */

#घोषणा SRC_MAC_ADDR_LOC	3	/* Src MAC address location */
#घोषणा MAC_ADDR_LEN 		3	/* MAC address length */
#घोषणा ETHER_PROTO_TYPE_LOC	6	/* Ethernet Proto type loc */

#घोषणा IP_ADDR_LEN 		2	/* Size of IP address */
#घोषणा IP_START_LOC 		7	/* IP header start location */
#घोषणा IP_HEADER_INFO_LEN	7	/* IP header information length */
#घोषणा IP_HEADER_LEN 		10 	/* IP header length */
#घोषणा IP_CHECKSUM_LOC		12	/* IP header checksum location */
#घोषणा IP_REQ_SRC_IP_LOC 	13	/* Src IP add loc of ICMP req */
#घोषणा IP_REQ_DEST_IP_LOC	15	/* Dest IP add loc of ICMP req */

#घोषणा ICMP_KNOWN_तथ्य_LEN	64	/* ICMP known data length */
#घोषणा ICMP_ECHO_FIELD_LOC 	17	/* Echo field loc */
#घोषणा ICMP_तथ्य_START_LOC 	17	/* Data field start location */
#घोषणा ICMP_तथ्य_LEN 		18	/* ICMP data length */
#घोषणा ICMP_तथ्य_CHECKSUM_LOC	18	/* ICMP data checksum location */
#घोषणा ICMP_IDEN_FIELD_LOC	19	/* Identifier field loc */
#घोषणा ICMP_तथ्य_LOC 		19	/* ICMP data loc including
					identifier number and sequence number */
#घोषणा ICMP_SEQ_NO_LOC		20	/* sequence number location */
#घोषणा ICMP_तथ्य_FIELD_LEN 	20 	/* Data field length */
#घोषणा ICMP_KNOWN_तथ्य_LOC	21	/* ICMP known data start loc */

#घोषणा ARP_REQ_STATUS_LOC 	10	/* ARP request loc */
#घोषणा ARP_REQ_SRC_IP_LOC 	14	/* Src IP add loc of ARP req Packet */

/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/

अटल पूर्णांक EmacLitePingReqExample(u16 DeviceId);

अटल व्योम SendArpReqFrame(XEmacLite *InstancePtr);

अटल व्योम SendEchoReqFrame(XEmacLite *InstancePtr);

अटल पूर्णांक ProcessRecvFrame(XEmacLite *InstancePtr);

अटल u16 Check_योग_Calculation(u16 *RxFramePtr16, पूर्णांक StartLoc, पूर्णांक लंबाई);

अटल पूर्णांक Compare_तथ्य(u16 *LhsPtr, u16 *RhsPtr, पूर्णांक LhsLoc, पूर्णांक RhsLoc,
			पूर्णांक गिनती_2);

/************************** Variable Definitions *****************************/

/*
 * Set up a local MAC address.
 */
अटल u8 LocalMacAddr[XEL_MAC_ADDR_आकार] =
{
	0x00, 0x0A, 0x35, 0x03, 0x02, 0x01
};

/*
 * The IP address was set to 172.16.63.121. User need to set a free IP address
 * based on the network on which this example is to be run.
 */
अटल u8 LocalIpAddress[IP_ADDR_आकार] =
{
	192, 168, 1, 26
};

/*
 * Set up a Destination IP address. Currently it is set to 172.16.63.61.
 */
/* ifconfig enp1s0 172.16.63.61 netmask 255.255.255.0 up */
अटल u8 DestIpAddress[IP_ADDR_आकार] =
{
	192, 168, 1, 25
};

अटल u16 DestMacAddr[MAC_ADDR_LEN]; 	/* Destination MAC Address */
अटल XEmacLite EmacLiteInstance;	/* Instance of the EmacLite driver */

/*
 * Known data transmitted in Echo request.
 */
u16 Icmp_तथ्य[ICMP_KNOWN_तथ्य_LEN] =
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
अटल u8 RxFrame[XEL_MAX_FRAME_आकार];
अटल u8 TxFrame[XEL_MAX_FRAME_आकार];

/*
 * Variable used to indicate the length of the received frame.
 */
बाह्य अस्थिर u32 Recv_Frame_लंबाई;

/*
 * Variable used to indicate the sequence number of the ICMP(echo) packet.
 */
पूर्णांक Seq_अंक;

/*
 * Variable used to indicate the number of ping request packets to be send.
 */
पूर्णांक अंक_Of_Ping_Req_Pkts;

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
पूर्णांक मुख्य()
{
	पूर्णांक Status;

	/*
	 * Run the EmacLite Ping request example.
	 */
	Status = EmacLitePingReqExample(EMAC_DEVICE_ID);
	अगर (Status != XST_SUCCESS) {
		xil_printf("Emaclite ping request Example Failed\r\n");
		वापस XST_FAILURE;
	}

	xil_printf("Successfully ran Emaclite ping request Example\r\n");
	वापस XST_SUCCESS;
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
अटल पूर्णांक EmacLitePingReqExample(u16 DeviceId)
{
	पूर्णांक Status;
	पूर्णांक सूचकांक;
	पूर्णांक गिनती_2;
	पूर्णांक EchoReplyStatus;
	XEmacLite_Config *ConfigPtr;
	XEmacLite *EmacLiteInstPtr = &EmacLiteInstance;
	Seq_अंक = 0;
	Recv_Frame_लंबाई = 0;
	EchoReplyStatus = XST_FAILURE;
	अंक_Of_Ping_Req_Pkts = अंक_OF_PING_REQ_PKTS;

	/*
	 * Initialize the EmacLite device.
	 */
	ConfigPtr = &XEmacLite_ConfigTable;
	अगर (ConfigPtr == शून्य) {
		वापस -1;
	}
	ConfigPtr->BaseAddress = (UINTPTR *) 0X44000;
	ConfigPtr->RxPingPong = XPAR_EMACLITE_0_RX_PING_PONG;
	ConfigPtr->MdioInclude = XPAR_EMACLITE_0_INCLUDE_MDIO;
	ConfigPtr->TxPingPong = XPAR_EMACLITE_0_TX_PING_PONG;
#अगर 0
	log_debug("\n ConfigPtr: BaseAddress: %x", ConfigPtr->BaseAddress);
	log_debug("\n ConfigPtr: DeviceId: %x", ConfigPtr->DeviceId);
	log_debug("\n ConfigPtr: TxPingPong: %x", ConfigPtr->TxPingPong);
	log_debug("\n ConfigPtr: RxPingPong: %x", ConfigPtr->RxPingPong);
	log_debug("\n ConfigPtr: MdioInclude: %x", ConfigPtr->MdioInclude);
	log_debug("\n ConfigPtr: Loopback: %x", ConfigPtr->Loopback);
#पूर्ण_अगर	
	Status = XEmacLite_CfgInitialize(EmacLiteInstPtr,
					ConfigPtr,
					ConfigPtr->BaseAddress);
	अगर (Status != 0) {
		वापस -1;
	}
	

	/*
	 * Set the MAC address.
	 */
	XEmacLite_SetMacAddress(EmacLiteInstPtr, LocalMacAddr);

	/*
	 * Empty any existing receive frames.
	 */
	XEmacLite_FlushReceive(EmacLiteInstPtr);
	जबतक (अंक_Of_Ping_Req_Pkts--) {

		/*
		 * Introduce delay.
		 */
		गिनती_2 = DELAY;
		जबतक (गिनती_2--) {
		}

		/*
		 * Send an ARP or an ICMP packet based on receive packet.
		 */
		अगर (Seq_अंक == 0) {
			SendArpReqFrame(EmacLiteInstPtr);
		} अन्यथा {
			SendEchoReqFrame(EmacLiteInstPtr);
		}

		/*
		 * Check next 10 packets for the correct reply.
		 */
		सूचकांक = अंक_RX_PACK_CHECK_REQ;
		जबतक (सूचकांक--) {

			/*
			 * Wait for a Receive packet.
			 */
			गिनती_2 = अंक_PACK_CHECK_RX_PACK;
			जबतक (Recv_Frame_लंबाई == 0) {
				Recv_Frame_लंबाई = XEmacLite_Recv(
							EmacLiteInstPtr,
							(u8 *)RxFrame);

				/*
				 * To avoid infinite loop when no packet is
				 * received.
				 */
				अगर (गिनती_2-- == 0) {
					अवरोध;
				}
			}

			/*
			 * Process the Receive frame.
			 */
			अगर (Recv_Frame_लंबाई != 0) {
				EchoReplyStatus = ProcessRecvFrame(
							EmacLiteInstPtr);
			}
			Recv_Frame_लंबाई = 0;

			/*
			 * Comes out of loop when an echo reply packet is
			 * received.
			 */
			अगर (EchoReplyStatus == XST_SUCCESS) {
				अवरोध;
			}
		}

		/*
		 * If no echo reply packet is received, it reports
		 * request timed out.
		 */
		अगर (EchoReplyStatus == XST_FAILURE) {
			xil_printf("Packet No: %d",
				अंक_OF_PING_REQ_PKTS - अंक_Of_Ping_Req_Pkts);
			xil_printf(" Seq NO %d Request timed out\r\n",
							Seq_अंक);
		}
	}
	वापस XST_SUCCESS;
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
अटल व्योम SendArpReqFrame(XEmacLite *InstancePtr)
{
	u16 *अस्थायी_Ptr;
	u16 *TxFramePtr;
	u32 अग्र_Tx_Buff_Base_Addr;
	पूर्णांक सूचकांक;

	TxFramePtr = (u16 *)TxFrame;

	/*
	 * Determine the next expected transmit buffer base address.
	 */
	अग्र_Tx_Buff_Base_Addr = XEmac_Lite_अग्र_Transmit_Addr(InstancePtr);

	/*
	 * Add broadcast address.
	 */
	सूचकांक = MAC_ADDR_LEN;
	जबतक (सूचकांक--) {
		*TxFramePtr++ = BROADCAST_ADDR;
	}

	/*
	 * Add local MAC address.
	 */
	सूचकांक = 0;
	अस्थायी_Ptr = (u16 *)LocalMacAddr;
	जबतक (सूचकांक < MAC_ADDR_LEN) {
		*TxFramePtr++ = *(अस्थायी_Ptr + सूचकांक);
		सूचकांक++;
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
	सूचकांक = 0;
	अस्थायी_Ptr = (u16 *)LocalMacAddr;
	जबतक (सूचकांक < MAC_ADDR_LEN) {
		*TxFramePtr++ = *(अस्थायी_Ptr + सूचकांक);
		सूचकांक++;
	}

	/*
	 * Add local IP address.
	 */
	सूचकांक = 0;
	अस्थायी_Ptr = (u16 *)LocalIpAddress;
	जबतक (सूचकांक < IP_ADDR_LEN) {
		*TxFramePtr++ = *(अस्थायी_Ptr + सूचकांक);
		सूचकांक++;
	}

	/*
	 * Fills 6 bytes of information with zeros as per protocol.
	 */
	सूचकांक = 0;
	जबतक (सूचकांक < 3) {
		*TxFramePtr++ = 0x0000;
		सूचकांक++;
	}

	/*
	 * Add Destination IP address.
	 */
	सूचकांक = 0;
	अस्थायी_Ptr = (u16 *)DestIpAddress;
	जबतक (सूचकांक < IP_ADDR_LEN) {
		*TxFramePtr++ = *(अस्थायी_Ptr + सूचकांक);
		सूचकांक++;
	}

	/*
	 * Transmit the Frame.
	 */
	XEmacLite_Send(InstancePtr, (u8 *)&TxFrame, ARP_REQ_PKT_आकार);
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
अटल व्योम SendEchoReqFrame(XEmacLite *InstancePtr)
{
	u16 *अस्थायी_Ptr;
	u16 *TxFramePtr;
	u16 *RxFramePtr;
	u16 Check_योग;
	u32 अग्र_Tx_Buff_Base_Addr;
	पूर्णांक सूचकांक;

	TxFramePtr = (u16 *)TxFrame;
	RxFramePtr = (u16 *)RxFrame;

	/*
	 * Determine the next expected transmit buffer base address.
	 */
	अग्र_Tx_Buff_Base_Addr = XEmac_Lite_अग्र_Transmit_Addr(InstancePtr);

	/*
	 * Add Destination MAC Address.
	 */
	सूचकांक = MAC_ADDR_LEN;
	जबतक (सूचकांक--) {
		*(TxFramePtr + सूचकांक) = *(DestMacAddr + सूचकांक);
	}

	/*
	 * Add Source MAC Address.
	 */
	सूचकांक = MAC_ADDR_LEN;
	अस्थायी_Ptr = (u16 *)LocalMacAddr;
	जबतक (सूचकांक--) {
		*(TxFramePtr + (सूचकांक + SRC_MAC_ADDR_LOC )) =
							*(अस्थायी_Ptr + सूचकांक);
	}

	/*
	 * Add IP header information.
	 */
	सूचकांक = IP_START_LOC;
	जबतक (सूचकांक--) {
		*(TxFramePtr + (सूचकांक + ETHER_PROTO_TYPE_LOC )) =
				Xil_Htons(*(IpHeaderInfo + सूचकांक));
	}

	/*
	 * Add Source IP address.
	 */
	सूचकांक = IP_ADDR_LEN;
	अस्थायी_Ptr = (u16 *)LocalIpAddress;
	जबतक (सूचकांक--) {
		*(TxFramePtr + (सूचकांक + IP_REQ_SRC_IP_LOC )) =
						*(अस्थायी_Ptr + सूचकांक);
	}

	/*
	 * Add Destination IP address.
	 */
	सूचकांक = IP_ADDR_LEN;
	अस्थायी_Ptr = (u16 *)DestIpAddress;
	जबतक (सूचकांक--) {
		*(TxFramePtr + (सूचकांक + IP_REQ_DEST_IP_LOC )) =
						*(अस्थायी_Ptr + सूचकांक);
	}

	/*
	 * Checksum is calculated for IP field and added in the frame.
	 */
	Check_योग = Check_योग_Calculation((u16 *)TxFrame, IP_START_LOC,
							IP_HEADER_LEN);
	Check_योग = ~Check_योग;
	*(TxFramePtr + IP_CHECKSUM_LOC) = Xil_Htons(Check_योग);

	/*
	 * Add echo field information.
	 */
	*(TxFramePtr + ICMP_ECHO_FIELD_LOC) = Xil_Htons(XEL_ETHER_PROTO_TYPE_IP);

	/*
	 * Checksum value is initialized to zeros.
	 */
	*(TxFramePtr + ICMP_तथ्य_LEN) = 0x0000;

	/*
	 * Add identifier and sequence number to the frame.
	 */
	*(TxFramePtr + ICMP_IDEN_FIELD_LOC) = (IDEN_अंक);
	*(TxFramePtr + (ICMP_IDEN_FIELD_LOC + 1)) = Xil_Htons((u16)(++Seq_अंक));

	/*
	 * Add known data to the frame.
	 */
	सूचकांक = ICMP_KNOWN_तथ्य_LEN;
	जबतक (सूचकांक--) {
		*(TxFramePtr + (सूचकांक + ICMP_KNOWN_तथ्य_LOC)) =
				Xil_Htons(*(Icmp_तथ्य + सूचकांक));
	}

	/*
	 * Checksum is calculated for Data Field and added in the frame.
	 */
	Check_योग = Check_योग_Calculation((u16 *)TxFrame, ICMP_तथ्य_START_LOC,
						ICMP_तथ्य_FIELD_LEN );
	Check_योग = ~Check_योग;
	*(TxFramePtr + ICMP_तथ्य_CHECKSUM_LOC) = Xil_Htons(Check_योग);

	/*
	 * Transmit the Frame.
	 */
	XEmacLite_Send(InstancePtr, (u8 *)&TxFrame, ICMP_PKT_आकार);
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
अटल पूर्णांक ProcessRecvFrame(XEmacLite *InstancePtr)
{
	u16 *RxFramePtr;
	u16 *अस्थायी_Ptr;
	u16 Check_योग;
	पूर्णांक सूचकांक;
	पूर्णांक Match = 0;
	पूर्णांक तथ्य_Wrong = 0;

	RxFramePtr = (u16 *)RxFrame;
	अस्थायी_Ptr = (u16 *)LocalMacAddr;

	/*
	 * Check Dest Mac address of the packet with the LocalMac address.
	 */
	Match = Compare_तथ्य(RxFramePtr, अस्थायी_Ptr, 0, 0, MAC_ADDR_LEN);
	अगर (Match == XST_SUCCESS) {

		/*
		 * Check ARP type.
		 */
		अगर (Xil_Ntohs(*(RxFramePtr + ETHER_PROTO_TYPE_LOC)) ==
				XEL_ETHER_PROTO_TYPE_ARP ) {

			/*
			 * Check ARP status.
			 */
			अगर (Xil_Ntohs(*(RxFramePtr + ARP_REQ_STATUS_LOC)) == ARP_REPLY) {

				/*
				 * Check destination IP address with
				 * packet's source IP address.
				 */
				अस्थायी_Ptr = (u16 *)DestIpAddress;
				Match = Compare_तथ्य(RxFramePtr,
						अस्थायी_Ptr, ARP_REQ_SRC_IP_LOC,
						0, IP_ADDR_LEN);
				अगर (Match == XST_SUCCESS) {

					/*
					 * Copy src Mac address of the received
					 * packet.
					 */
					सूचकांक = MAC_ADDR_LEN;
					अस्थायी_Ptr = (u16 *)DestMacAddr;
					जबतक (सूचकांक--) {
						*(अस्थायी_Ptr + सूचकांक) =
							*(RxFramePtr +
							(SRC_MAC_ADDR_LOC +
								सूचकांक));
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
		अन्यथा अगर (Xil_Ntohs(*(RxFramePtr + ETHER_PROTO_TYPE_LOC)) ==
						XEL_ETHER_PROTO_TYPE_IP) {

			/*
			 * Calculate checksum.
			 */
			Check_योग = Check_योग_Calculation(RxFramePtr,
							ICMP_तथ्य_START_LOC,
							ICMP_तथ्य_FIELD_LEN);

			/*
			 * Verify checksum, echo reply, identifier number and
			 * sequence number of the received packet.
			 */
			अगर ((Check_योग == CORRECT_CHECKSUM_मूल्य) &&
			(Xil_Ntohs(*(RxFramePtr + ICMP_ECHO_FIELD_LOC)) == ECHO_REPLY) &&
			(Xil_Ntohs(*(RxFramePtr + ICMP_IDEN_FIELD_LOC)) == IDEN_अंक) &&
			(Xil_Ntohs(*(RxFramePtr + (ICMP_SEQ_NO_LOC))) == Seq_अंक)) {

				/*
				 * Verify data in the received packet with known
				 * data.
				 */
				अस्थायी_Ptr = Icmp_तथ्य;
				Match = Compare_तथ्य(RxFramePtr,
						अस्थायी_Ptr, ICMP_KNOWN_तथ्य_LOC,
							0, ICMP_KNOWN_तथ्य_LEN);
				अगर (Match == XST_FAILURE) {
					तथ्य_Wrong = 1;
				}
			}
			अगर (तथ्य_Wrong != 1) {
				xil_printf("Packet No: %d ",
				अंक_OF_PING_REQ_PKTS - अंक_Of_Ping_Req_Pkts);
				xil_printf("Seq NO %d Echo Packet received\r\n",
								Seq_अंक);
				वापस XST_SUCCESS;
			}
		}
	}
	वापस XST_FAILURE;
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
अटल u16 Check_योग_Calculation(u16 *RxFramePtr, पूर्णांक StartLoc, पूर्णांक लंबाई)
{
	u32 योग = 0;
	u16 Check_योग = 0;
	पूर्णांक सूचकांक;

	/*
	 * Add all the 16 bit data.
	 */
	सूचकांक = StartLoc;
	जबतक (सूचकांक < (StartLoc + लंबाई)) {
		योग = योग + Xil_Htons(*(RxFramePtr + सूचकांक));
		सूचकांक++;
	}

	/*
	 * Add upper 16 bits to lower 16 bits.
	 */
	Check_योग = योग;
	योग = योग>>16;
	Check_योग = योग + Check_योग;
	वापस Check_योग;
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
अटल पूर्णांक Compare_तथ्य(u16 *LhsPtr, u16 *RhsPtr, पूर्णांक LhsLoc, पूर्णांक RhsLoc,
								पूर्णांक गिनती_2)
{
	पूर्णांक परिणाम;
	जबतक (गिनती_2--) {
		अगर (*(LhsPtr + LhsLoc + गिनती_2) == *(RhsPtr + RhsLoc + गिनती_2)) {
			परिणाम = XST_SUCCESS;
		} अन्यथा {
			परिणाम = XST_FAILURE;
			अवरोध;
		}
	}
	वापस परिणाम;
}
