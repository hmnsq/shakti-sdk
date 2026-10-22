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
#परिभाषय EMAC_DEVICE_ID			240
#परिभाषय ETH_आधारः_REG 0x44000
चञ्चल अचिह्नित पूर्णाङ्क* eth_आधारः_reg = ETH_आधारः_REG;

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

बाह्य XEmacLite_Config XEmac_Lite_Config_सारणी;

/************************** Variable Definitions *****************************/

/*
 * Instance of the driver
 */
स्थिर XEmacLite EmacLite;


/*
 * Change this parameter to limit the number of ping requests sent by this
 * program.
 */
#परिभाषय अङ्कः_सम्बन्धि_PING_REQ_PKTS	100	/* Number of ping req it generates */

#परिभाषय ECHO_प्रत्युत्तरम्		0x00	/* Echo reply */
#परिभाषय HW_TYPE			0x01	/* Hardware type (10/100 Mbps) */
#परिभाषय ARP_REQUEST 		0x01	/* ARP Request bits in Rx packet */
#परिभाषय ARP_प्रत्युत्तरम् 		0x02 	/* ARP status bits indicating reply */
#परिभाषय IDEN_अङ्कः		0x02	/* ICMP identifier number */
#परिभाषय IP_संस्करणम्		0x0604	/* IP version ipv4/ipv6 */
#परिभाषय प्रसारणम्_ADDR 		0xFFFF 	/* Broadcast Address */
#परिभाषय CORRECT_CHECKSUM_मानम्	0xFFFF	/* Correct checksum value */
#परिभाषय ARP_REQ_PKT_आकार	0x2A	/* ARP request packet size */
#परिभाषय ICMP_PKT_आकार 		0x4A	/* ICMP packet length 74 Bytes
					including Src and dest MAC Add */
#परिभाषय IP_ADDR_आकार		4	/* IP Address size in Bytes */
#परिभाषय अङ्कः_RX_PACK_CHECK_REQ	10	/* Max num of Rx pack to be checked
					before sending another request */
#परिभाषय अङ्कः_PACK_CHECK_RX_PACK	100	/* Max number of pack to be checked
					before to identify a Rx packet */
#परिभाषय DELAY			5000000 /* Used to introduce delay */

/*
 * Definitions for the locations and length of some of the fields in a
 * IP packet. The lengths are defined in Half-Words (2 bytes).
 */

#परिभाषय SRC_MAC_ADDR_LOC	3	/* Src MAC address location */
#परिभाषय MAC_ADDR_LEN 		3	/* MAC address length */
#परिभाषय ETHER_PROTO_TYPE_LOC	6	/* Ethernet Proto type loc */

#परिभाषय IP_ADDR_LEN 		2	/* Size of IP address */
#परिभाषय IP_START_LOC 		7	/* IP header start location */
#परिभाषय IP_शीर्षकम्_INFO_LEN	7	/* IP header information length */
#परिभाषय IP_शीर्षकम्_LEN 		10 	/* IP header length */
#परिभाषय IP_CHECKSUM_LOC		12	/* IP header checksum location */
#परिभाषय IP_REQ_SRC_IP_LOC 	13	/* Src IP add loc of ICMP req */
#परिभाषय IP_REQ_DEST_IP_LOC	15	/* Dest IP add loc of ICMP req */

#परिभाषय ICMP_ज्ञातम्_दत्त_LEN	64	/* ICMP known data length */
#परिभाषय ICMP_ECHO_क्षेत्रम्_LOC 	17	/* Echo field loc */
#परिभाषय ICMP_दत्त_START_LOC 	17	/* Data field start location */
#परिभाषय ICMP_दत्त_LEN 		18	/* ICMP data length */
#परिभाषय ICMP_दत्त_CHECKSUM_LOC	18	/* ICMP data checksum location */
#परिभाषय ICMP_IDEN_क्षेत्रम्_LOC	19	/* Identifier field loc */
#परिभाषय ICMP_दत्त_LOC 		19	/* ICMP data loc including
					identifier number and sequence number */
#परिभाषय ICMP_SEQ_NO_LOC		20	/* sequence number location */
#परिभाषय ICMP_दत्त_क्षेत्रम्_LEN 	20 	/* Data field length */
#परिभाषय ICMP_ज्ञातम्_दत्त_LOC	21	/* ICMP known data start loc */

#परिभाषय ARP_REQ_स्थितिः_LOC 	10	/* ARP request loc */
#परिभाषय ARP_REQ_SRC_IP_LOC 	14	/* Src IP add loc of ARP req Packet */

/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/

स्थिर पूर्णाङ्क EmacLitePingReqExample(u16 DeviceId);

स्थिर शून्य SendArpReqFrame(XEmacLite *InstancePtr);

स्थिर शून्य SendEchoReqFrame(XEmacLite *InstancePtr);

स्थिर पूर्णाङ्क ProcessRecvFrame(XEmacLite *InstancePtr);

स्थिर u16 Check_योग_Calculation(u16 *RxFramePtr16, पूर्णाङ्क StartLoc, पूर्णाङ्क दीर्घता);

स्थिर पूर्णाङ्क Compare_दत्त(u16 *LhsPtr, u16 *RhsPtr, पूर्णाङ्क LhsLoc, पूर्णाङ्क RhsLoc,
			पूर्णाङ्क गणनम्_2);

/************************** Variable Definitions *****************************/

/*
 * Set up a local MAC address.
 */
स्थिर u8 LocalMacAddr[XEL_MAC_ADDR_आकार] =
{
	0x00, 0x0A, 0x35, 0x03, 0x02, 0x01
};

/*
 * The IP address was set to 172.16.63.121. User need to set a free IP address
 * based on the network on which this example is to be run.
 */
स्थिर u8 Local_Ip_स्थानाङ्कः[IP_ADDR_आकार] =
{
	192, 168, 1, 26
};

/*
 * Set up a Destination IP address. Currently it is set to 172.16.63.61.
 */
/* ifconfig enp1s0 172.16.63.61 netmask 255.255.255.0 up */
स्थिर u8 Dest_Ip_स्थानाङ्कः[IP_ADDR_आकार] =
{
	192, 168, 1, 25
};

स्थिर u16 DestMacAddr[MAC_ADDR_LEN]; 	/* Destination MAC Address */
स्थिर XEmacLite EmacLiteInstance;	/* Instance of the EmacLite driver */

/*
 * Known data transmitted in Echo request.
 */
u16 Icmp_दत्त[ICMP_ज्ञातम्_दत्त_LEN] =
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
u16 Ip_शीर्षकम्_Info[IP_शीर्षकम्_INFO_LEN] =
{
	0x0800,	0x4500, 0x003C,	0x5566,	0x0000,	0x8001, 0x0000
};

/*
 * Buffers used for Transmission and Reception of Packets. These are declared as
 * global so that they are not a part of the stack.
 */
स्थिर u8 RxFrame[XEL_MAX_FRAME_आकार];
स्थिर u8 TxFrame[XEL_MAX_FRAME_आकार];

/*
 * Variable used to indicate the length of the received frame.
 */
बाह्य चञ्चल u32 Recv_Frame_दीर्घता;

/*
 * Variable used to indicate the sequence number of the ICMP(echo) packet.
 */
पूर्णाङ्क Seq_अङ्कः;

/*
 * Variable used to indicate the number of ping request packets to be send.
 */
पूर्णाङ्क अङ्कः_सम्बन्धि_Ping_Req_Pkts;

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
पूर्णाङ्क मुख्यम्()
{
	पूर्णाङ्क स्थितिः;

	/*
	 * Run the EmacLite Ping request example.
	 */
	स्थितिः = EmacLitePingReqExample(EMAC_DEVICE_ID);
	यदि (स्थितिः != XST_SUCCESS) {
		xil_printf("Emaclite ping request Example Failed\r\n");
		प्रत्यागम XST_FAILURE;
	}

	xil_printf("Successfully ran Emaclite ping request Example\r\n");
	प्रत्यागम XST_SUCCESS;
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
	पूर्णाङ्क स्थितिः;
	पूर्णाङ्क सूचकांक;
	पूर्णाङ्क गणनम्_2;
	पूर्णाङ्क Echo_प्रत्युत्तरम्_स्थितिः;
	XEmacLite_Config *ConfigPtr;
	XEmacLite *EmacLiteInstPtr = &EmacLiteInstance;
	Seq_अङ्कः = 0;
	Recv_Frame_दीर्घता = 0;
	Echo_प्रत्युत्तरम्_स्थितिः = XST_FAILURE;
	अङ्कः_सम्बन्धि_Ping_Req_Pkts = अङ्कः_सम्बन्धि_PING_REQ_PKTS;

	/*
	 * Initialize the EmacLite device.
	 */
	ConfigPtr = &XEmac_Lite_Config_सारणी;
	यदि (ConfigPtr == रिक्त) {
		प्रत्यागम -1;
	}
	ConfigPtr->आधारः_स्थानाङ्कः = (UINTPTR *) 0X44000;
	ConfigPtr->RxPingPong = XPAR_EMACLITE_0_RX_PING_PONG;
	ConfigPtr->MdioInclude = XPAR_EMACLITE_0_INCLUDE_MDIO;
	ConfigPtr->TxPingPong = XPAR_EMACLITE_0_TX_PING_PONG;
#यदि 0
	log_debug("\n ConfigPtr: BaseAddress: %x", ConfigPtr->आधारः_स्थानाङ्कः);
	log_debug("\n ConfigPtr: DeviceId: %x", ConfigPtr->DeviceId);
	log_debug("\n ConfigPtr: TxPingPong: %x", ConfigPtr->TxPingPong);
	log_debug("\n ConfigPtr: RxPingPong: %x", ConfigPtr->RxPingPong);
	log_debug("\n ConfigPtr: MdioInclude: %x", ConfigPtr->MdioInclude);
	log_debug("\n ConfigPtr: Loopback: %x", ConfigPtr->Loopback);
#यदि_अन्तः	
	स्थितिः = XEmacLite_CfgInitialize(EmacLiteInstPtr,
					ConfigPtr,
					ConfigPtr->आधारः_स्थानाङ्कः);
	यदि (स्थितिः != 0) {
		प्रत्यागम -1;
	}
	

	/*
	 * Set the MAC address.
	 */
	XEmac_Lite_समुच्चयः_Mac_स्थानाङ्कः(EmacLiteInstPtr, LocalMacAddr);

	/*
	 * Empty any existing receive frames.
	 */
	XEmacLite_FlushReceive(EmacLiteInstPtr);
	यावत् (अङ्कः_सम्बन्धि_Ping_Req_Pkts--) {

		/*
		 * Introduce delay.
		 */
		गणनम्_2 = DELAY;
		यावत् (गणनम्_2--) {
		}

		/*
		 * Send an ARP or an ICMP packet based on receive packet.
		 */
		यदि (Seq_अङ्कः == 0) {
			SendArpReqFrame(EmacLiteInstPtr);
		} अन्यथा {
			SendEchoReqFrame(EmacLiteInstPtr);
		}

		/*
		 * Check next 10 packets for the correct reply.
		 */
		सूचकांक = अङ्कः_RX_PACK_CHECK_REQ;
		यावत् (सूचकांक--) {

			/*
			 * Wait for a Receive packet.
			 */
			गणनम्_2 = अङ्कः_PACK_CHECK_RX_PACK;
			यावत् (Recv_Frame_दीर्घता == 0) {
				Recv_Frame_दीर्घता = XEmacLite_Recv(
							EmacLiteInstPtr,
							(u8 *)RxFrame);

				/*
				 * To avoid infinite loop when no packet is
				 * received.
				 */
				यदि (गणनम्_2-- == 0) {
					भङ्ग;
				}
			}

			/*
			 * Process the Receive frame.
			 */
			यदि (Recv_Frame_दीर्घता != 0) {
				Echo_प्रत्युत्तरम्_स्थितिः = ProcessRecvFrame(
							EmacLiteInstPtr);
			}
			Recv_Frame_दीर्घता = 0;

			/*
			 * Comes out of loop when an echo reply packet is
			 * received.
			 */
			यदि (Echo_प्रत्युत्तरम्_स्थितिः == XST_SUCCESS) {
				भङ्ग;
			}
		}

		/*
		 * If no echo reply packet is received, it reports
		 * request timed out.
		 */
		यदि (Echo_प्रत्युत्तरम्_स्थितिः == XST_FAILURE) {
			xil_printf("Packet No: %d",
				अङ्कः_सम्बन्धि_PING_REQ_PKTS - अङ्कः_सम्बन्धि_Ping_Req_Pkts);
			xil_printf(" Seq NO %d Request timed out\r\n",
							Seq_अङ्कः);
		}
	}
	प्रत्यागम XST_SUCCESS;
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
	u16 *अस्थायी_Ptr;
	u16 *TxFramePtr;
	u32 अग्र_Tx_Buff_आधारः_Addr;
	पूर्णाङ्क सूचकांक;

	TxFramePtr = (u16 *)TxFrame;

	/*
	 * Determine the next expected transmit buffer base address.
	 */
	अग्र_Tx_Buff_आधारः_Addr = XEmac_Lite_अग्र_Transmit_Addr(InstancePtr);

	/*
	 * Add broadcast address.
	 */
	सूचकांक = MAC_ADDR_LEN;
	यावत् (सूचकांक--) {
		*TxFramePtr++ = प्रसारणम्_ADDR;
	}

	/*
	 * Add local MAC address.
	 */
	सूचकांक = 0;
	अस्थायी_Ptr = (u16 *)LocalMacAddr;
	यावत् (सूचकांक < MAC_ADDR_LEN) {
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
	*TxFramePtr++ = Xil_Htons(IP_संस्करणम्);
	*TxFramePtr++ = Xil_Htons(ARP_REQUEST);

	/*
	 * Add local MAC address.
	 */
	सूचकांक = 0;
	अस्थायी_Ptr = (u16 *)LocalMacAddr;
	यावत् (सूचकांक < MAC_ADDR_LEN) {
		*TxFramePtr++ = *(अस्थायी_Ptr + सूचकांक);
		सूचकांक++;
	}

	/*
	 * Add local IP address.
	 */
	सूचकांक = 0;
	अस्थायी_Ptr = (u16 *)Local_Ip_स्थानाङ्कः;
	यावत् (सूचकांक < IP_ADDR_LEN) {
		*TxFramePtr++ = *(अस्थायी_Ptr + सूचकांक);
		सूचकांक++;
	}

	/*
	 * Fills 6 bytes of information with zeros as per protocol.
	 */
	सूचकांक = 0;
	यावत् (सूचकांक < 3) {
		*TxFramePtr++ = 0x0000;
		सूचकांक++;
	}

	/*
	 * Add Destination IP address.
	 */
	सूचकांक = 0;
	अस्थायी_Ptr = (u16 *)Dest_Ip_स्थानाङ्कः;
	यावत् (सूचकांक < IP_ADDR_LEN) {
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
स्थिर शून्य SendEchoReqFrame(XEmacLite *InstancePtr)
{
	u16 *अस्थायी_Ptr;
	u16 *TxFramePtr;
	u16 *RxFramePtr;
	u16 Check_योग;
	u32 अग्र_Tx_Buff_आधारः_Addr;
	पूर्णाङ्क सूचकांक;

	TxFramePtr = (u16 *)TxFrame;
	RxFramePtr = (u16 *)RxFrame;

	/*
	 * Determine the next expected transmit buffer base address.
	 */
	अग्र_Tx_Buff_आधारः_Addr = XEmac_Lite_अग्र_Transmit_Addr(InstancePtr);

	/*
	 * Add Destination MAC Address.
	 */
	सूचकांक = MAC_ADDR_LEN;
	यावत् (सूचकांक--) {
		*(TxFramePtr + सूचकांक) = *(DestMacAddr + सूचकांक);
	}

	/*
	 * Add Source MAC Address.
	 */
	सूचकांक = MAC_ADDR_LEN;
	अस्थायी_Ptr = (u16 *)LocalMacAddr;
	यावत् (सूचकांक--) {
		*(TxFramePtr + (सूचकांक + SRC_MAC_ADDR_LOC )) =
							*(अस्थायी_Ptr + सूचकांक);
	}

	/*
	 * Add IP header information.
	 */
	सूचकांक = IP_START_LOC;
	यावत् (सूचकांक--) {
		*(TxFramePtr + (सूचकांक + ETHER_PROTO_TYPE_LOC )) =
				Xil_Htons(*(Ip_शीर्षकम्_Info + सूचकांक));
	}

	/*
	 * Add Source IP address.
	 */
	सूचकांक = IP_ADDR_LEN;
	अस्थायी_Ptr = (u16 *)Local_Ip_स्थानाङ्कः;
	यावत् (सूचकांक--) {
		*(TxFramePtr + (सूचकांक + IP_REQ_SRC_IP_LOC )) =
						*(अस्थायी_Ptr + सूचकांक);
	}

	/*
	 * Add Destination IP address.
	 */
	सूचकांक = IP_ADDR_LEN;
	अस्थायी_Ptr = (u16 *)Dest_Ip_स्थानाङ्कः;
	यावत् (सूचकांक--) {
		*(TxFramePtr + (सूचकांक + IP_REQ_DEST_IP_LOC )) =
						*(अस्थायी_Ptr + सूचकांक);
	}

	/*
	 * Checksum is calculated for IP field and added in the frame.
	 */
	Check_योग = Check_योग_Calculation((u16 *)TxFrame, IP_START_LOC,
							IP_शीर्षकम्_LEN);
	Check_योग = ~Check_योग;
	*(TxFramePtr + IP_CHECKSUM_LOC) = Xil_Htons(Check_योग);

	/*
	 * Add echo field information.
	 */
	*(TxFramePtr + ICMP_ECHO_क्षेत्रम्_LOC) = Xil_Htons(XEL_ETHER_PROTO_TYPE_IP);

	/*
	 * Checksum value is initialized to zeros.
	 */
	*(TxFramePtr + ICMP_दत्त_LEN) = 0x0000;

	/*
	 * Add identifier and sequence number to the frame.
	 */
	*(TxFramePtr + ICMP_IDEN_क्षेत्रम्_LOC) = (IDEN_अङ्कः);
	*(TxFramePtr + (ICMP_IDEN_क्षेत्रम्_LOC + 1)) = Xil_Htons((u16)(++Seq_अङ्कः));

	/*
	 * Add known data to the frame.
	 */
	सूचकांक = ICMP_ज्ञातम्_दत्त_LEN;
	यावत् (सूचकांक--) {
		*(TxFramePtr + (सूचकांक + ICMP_ज्ञातम्_दत्त_LOC)) =
				Xil_Htons(*(Icmp_दत्त + सूचकांक));
	}

	/*
	 * Checksum is calculated for Data Field and added in the frame.
	 */
	Check_योग = Check_योग_Calculation((u16 *)TxFrame, ICMP_दत्त_START_LOC,
						ICMP_दत्त_क्षेत्रम्_LEN );
	Check_योग = ~Check_योग;
	*(TxFramePtr + ICMP_दत्त_CHECKSUM_LOC) = Xil_Htons(Check_योग);

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
स्थिर पूर्णाङ्क ProcessRecvFrame(XEmacLite *InstancePtr)
{
	u16 *RxFramePtr;
	u16 *अस्थायी_Ptr;
	u16 Check_योग;
	पूर्णाङ्क सूचकांक;
	पूर्णाङ्क मेलनम् = 0;
	पूर्णाङ्क दत्त_Wrong = 0;

	RxFramePtr = (u16 *)RxFrame;
	अस्थायी_Ptr = (u16 *)LocalMacAddr;

	/*
	 * Check Dest Mac address of the packet with the LocalMac address.
	 */
	मेलनम् = Compare_दत्त(RxFramePtr, अस्थायी_Ptr, 0, 0, MAC_ADDR_LEN);
	यदि (मेलनम् == XST_SUCCESS) {

		/*
		 * Check ARP type.
		 */
		यदि (Xil_Ntohs(*(RxFramePtr + ETHER_PROTO_TYPE_LOC)) ==
				XEL_ETHER_PROTO_TYPE_ARP ) {

			/*
			 * Check ARP status.
			 */
			यदि (Xil_Ntohs(*(RxFramePtr + ARP_REQ_स्थितिः_LOC)) == ARP_प्रत्युत्तरम्) {

				/*
				 * Check destination IP address with
				 * packet's source IP address.
				 */
				अस्थायी_Ptr = (u16 *)Dest_Ip_स्थानाङ्कः;
				मेलनम् = Compare_दत्त(RxFramePtr,
						अस्थायी_Ptr, ARP_REQ_SRC_IP_LOC,
						0, IP_ADDR_LEN);
				यदि (मेलनम् == XST_SUCCESS) {

					/*
					 * Copy src Mac address of the received
					 * packet.
					 */
					सूचकांक = MAC_ADDR_LEN;
					अस्थायी_Ptr = (u16 *)DestMacAddr;
					यावत् (सूचकांक--) {
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
		अन्यथा यदि (Xil_Ntohs(*(RxFramePtr + ETHER_PROTO_TYPE_LOC)) ==
						XEL_ETHER_PROTO_TYPE_IP) {

			/*
			 * Calculate checksum.
			 */
			Check_योग = Check_योग_Calculation(RxFramePtr,
							ICMP_दत्त_START_LOC,
							ICMP_दत्त_क्षेत्रम्_LEN);

			/*
			 * Verify checksum, echo reply, identifier number and
			 * sequence number of the received packet.
			 */
			यदि ((Check_योग == CORRECT_CHECKSUM_मानम्) &&
			(Xil_Ntohs(*(RxFramePtr + ICMP_ECHO_क्षेत्रम्_LOC)) == ECHO_प्रत्युत्तरम्) &&
			(Xil_Ntohs(*(RxFramePtr + ICMP_IDEN_क्षेत्रम्_LOC)) == IDEN_अङ्कः) &&
			(Xil_Ntohs(*(RxFramePtr + (ICMP_SEQ_NO_LOC))) == Seq_अङ्कः)) {

				/*
				 * Verify data in the received packet with known
				 * data.
				 */
				अस्थायी_Ptr = Icmp_दत्त;
				मेलनम् = Compare_दत्त(RxFramePtr,
						अस्थायी_Ptr, ICMP_ज्ञातम्_दत्त_LOC,
							0, ICMP_ज्ञातम्_दत्त_LEN);
				यदि (मेलनम् == XST_FAILURE) {
					दत्त_Wrong = 1;
				}
			}
			यदि (दत्त_Wrong != 1) {
				xil_printf("Packet No: %d ",
				अङ्कः_सम्बन्धि_PING_REQ_PKTS - अङ्कः_सम्बन्धि_Ping_Req_Pkts);
				xil_printf("Seq NO %d Echo Packet received\r\n",
								Seq_अङ्कः);
				प्रत्यागम XST_SUCCESS;
			}
		}
	}
	प्रत्यागम XST_FAILURE;
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
स्थिर u16 Check_योग_Calculation(u16 *RxFramePtr, पूर्णाङ्क StartLoc, पूर्णाङ्क दीर्घता)
{
	u32 योग = 0;
	u16 Check_योग = 0;
	पूर्णाङ्क सूचकांक;

	/*
	 * Add all the 16 bit data.
	 */
	सूचकांक = StartLoc;
	यावत् (सूचकांक < (StartLoc + दीर्घता)) {
		योग = योग + Xil_Htons(*(RxFramePtr + सूचकांक));
		सूचकांक++;
	}

	/*
	 * Add upper 16 bits to lower 16 bits.
	 */
	Check_योग = योग;
	योग = योग>>16;
	Check_योग = योग + Check_योग;
	प्रत्यागम Check_योग;
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
स्थिर पूर्णाङ्क Compare_दत्त(u16 *LhsPtr, u16 *RhsPtr, पूर्णाङ्क LhsLoc, पूर्णाङ्क RhsLoc,
								पूर्णाङ्क गणनम्_2)
{
	पूर्णाङ्क परिणाम;
	यावत् (गणनम्_2--) {
		यदि (*(LhsPtr + LhsLoc + गणनम्_2) == *(RhsPtr + RhsLoc + गणनम्_2)) {
			परिणाम = XST_SUCCESS;
		} अन्यथा {
			परिणाम = XST_FAILURE;
			भङ्ग;
		}
	}
	प्रत्यागम परिणाम;
}
