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




/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#परिभाषय EMAC_DEVICE_ID			240
#परिभाषय ETH_आधारः_REG 0x44000
चञ्चल अचिह्नित पूर्णाङ्क* eth_आधारः_reg = ETH_आधारः_REG;
/*
 * Instance of the driver
 */
स्थिर XEmacLite EmacLite;



/*
 * Change this parameter to limit the number of ping replies sent by this
 * program.
 */
#परिभाषय MAX_PING_REPLIES	10000	/* Maximum number of ping replies */

#परिभाषय प्रसारणम्_PACKET	1	/* Broadcast packet */
#परिभाषय MAC_MATCHED_PACKET	2 	/* Dest MAC matched with local MAC */
#परिभाषय IP_ADDR_आकार		4	/* IP Address size in Bytes */
#परिभाषय ARP_REQUEST 		0x0001	/* ARP Request bits in Rx packet */
#परिभाषय ARP_प्रत्युत्तरम् 		0x0002 	/* ARP status bits indicating reply */
#परिभाषय ARP_PACKET_आकार 	0x3C    /* ARP packet len 60 Bytes */
#परिभाषय ICMP_PACKET_आकार 	98 //0x4A    /* ICMP packet length 74 Bytes
					 /* including Src and Dest MAC Address */
#परिभाषय प्रसारणम्_ADDR 		0xFFFF  /* Broadcast Address */
#परिभाषय CORRECT_CKSUM_मानम्	0xFFFF  /* Correct checksum value */
#परिभाषय IDENT_क्षेत्रम्_मानम्	0x9263	/* Identification field (random num) */

/*
 * Definitions for the locations and length of some of the fields in a
 * IP packet. The lengths are defined in Half-Words (2 bytes).
 */
#परिभाषय ETHER_PROTO_TYPE_LEN	1  /* Ethernet protocol Type length  */
#परिभाषय SRC_MAC_ADDR_LOC	3  /* Source MAC address location */
#परिभाषय MAC_ADDR_LEN 		3  /* MAC address length */
#परिभाषय ETHER_PROTO_TYPE_LOC	6  /* Ethernet Proto type location */

#परिभाषय ARP_HW_TYPE_LEN 	1  /* Hardware Type length  */
#परिभाषय ARP_PROTO_TYPE_LEN	1  /* Protocol Type length  */
#परिभाषय ARP_HW_सङ्कलय_LEN		1  /* Hardware address length */
#परिभाषय ARP_PROTO_सङ्कलय_LEN	1  /* Protocol address length */
#परिभाषय ARP_ZEROS_LEN		9  /* Length to be filled with zeros */
#परिभाषय ARP_REQ_स्थितिः_LOC 	10 /* ARP request location */
#परिभाषय ARP_REQ_SRC_IP_LOC 	14 /* Src IP address location of ARP request */
#परिभाषय ARP_REQ_DEST_IP_LOC_1 	19 /* Destination IP's 1st half word location */
#परिभाषय ARP_REQ_DEST_IP_LOC_2 	20 /* Destination IP's 2nd half word location */

#परिभाषय IP_संस्करणम्_LEN 		1  /* IP Version length  */
#परिभाषय IP_PACKET_LEN 		1  /* IP Packet length field  */
#परिभाषय IP_FRAG_क्षेत्रम्_LEN	1  /* Fragment field len in ICMP packet */
#परिभाषय IP_TTL_ICM_LEN 		1  /* Time to live and ICM fields length */
#परिभाषय IP_ADDR_LEN 		2  /* Size of IP address in half-words */
#परिभाषय IP_CSUM_LOC_पृष्ठभागः	5  /* IP checksum location from end of frame */
#परिभाषय IP_HDR_START_LOC 	7  /* IP header start location */
#परिभाषय IP_HDR_LEN 		10 /* IP Header length */
#परिभाषय IP_FRAG_क्षेत्रम्_LOC 	10 /* Fragment field location */

#परिभाषय ICMP_TYPE_LEN 		1  /* ICMP Type length */
#परिभाषय ICMP_ECHO_क्षेत्रम्_LEN 	2  /* Echo field length in half-words */
#परिभाषय ICMP_REQ_SRC_IP_LOC 	13 /* Src IP address location of ICMP request */
#परिभाषय ICMP_ECHO_क्षेत्रम्_LOC 	17 /* Echo field location */
#परिभाषय ICMP_दत्त_START_LOC 	17 /* Data field start location */
#परिभाषय ICMP_दत्त_LEN 		30  //18  /* ICMP data length */
#परिभाषय ICMP_दत्त_LOC 		19 /* ICMP data location including
				      identifier number and sequence number */
#परिभाषय ICMP_दत्त_CSUM_LOC_पृष्ठभागः 31 //19 
/* Data checksum location from end of
					frame */
#परिभाषय ICMP_दत्त_क्षेत्रम्_LEN 	32 //20 /* Data field length */

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

स्थिर पूर्णाङ्क Emac_Lite_Ping_प्रत्युत्तरम्_Example(u16 DeviceId);

स्थिर शून्य ProcessRecvFrame(XEmacLite *InstancePtr);

स्थिर u16 Check_योग_Calculation(u16 *RxFramePtr, पूर्णाङ्क StartLoc, पूर्णाङ्क दीर्घता);

/************************** Variable Definitions *****************************/

/*
 * Set up a local MAC address.
 */
स्थिर u8 LocalMacAddr[XEL_MAC_ADDR_आकार] =
{
	0x00, 0x00, 0x5E, 0x00, 0xFA, 0xCE
};

/*
 * The IP address was set to 172.16.63.121. User need to set a free IP address
 * based on the network on which this example is to be run.
 */
स्थिर u8 LocalIpAddr[IP_ADDR_आकार] =
{
	192, 168, 1, 25
};

स्थिर XEmacLite EmacLiteInstance;	/* Instance of the EmacLite driver */

/*
 * Buffers used for Transmission and Reception of Packets. These are declared as
 * global so that they are not a part of the stack.
 */
स्थिर u8 RxFrame[XEL_MAX_FRAME_आकार];
स्थिर u8 TxFrame[XEL_MAX_FRAME_आकार];

/*
 * Variable used to indicate the length of the received frame.
 */
बाह्य चञ्चल u32 Recv_Frame_दीर्घता = 0;

/*
 * Variable used to indicate the number of Ping replies sent.
 */
u32 अङ्कः_सम्बन्धि_Ping_Replies;
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
पूर्णाङ्क मुख्यम्()
{
	पूर्णाङ्क स्थितिः;
	arpcount = 0;
	/*
	 * Run the EmacLite Ping reply example.
	 */
	स्थितिः = Emac_Lite_Ping_प्रत्युत्तरम्_Example(EMAC_DEVICE_ID);
	यदि (स्थितिः != XST_SUCCESS) {
		xil_printf("Emaclite ping reply Example Failed\r\n");
		प्रत्यागम XST_FAILURE;
	}

	xil_printf("Successfully ran Emaclite ping reply Example\r\n");
	प्रत्यागम XST_SUCCESS;
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
पूर्णाङ्क Emac_Lite_Ping_प्रत्युत्तरम्_Example(u16 DeviceId)
{
	पूर्णाङ्क स्थितिः, गणनम् = 0;
	XEmacLite *EmacLiteInstPtr = &EmacLiteInstance;
	XEmacLite_Config *ConfigPtr;
	अङ्कः_सम्बन्धि_Ping_Replies = 0;

	/*
	 * Initialize the EmacLite device.
	 */
	ConfigPtr = &XEmac_Lite_Config_सारणी;
	यदि (ConfigPtr == रिक्त) {
		प्रत्यागम -1;
	}
	प्रारूप_लिख("\n ");

	ConfigPtr->आधारः_स्थानाङ्कः = (UINTPTR *) 0X44000;
	ConfigPtr->RxPingPong = XPAR_EMACLITE_0_RX_PING_PONG;
	ConfigPtr->MdioInclude = XPAR_EMACLITE_0_INCLUDE_MDIO;
	ConfigPtr->TxPingPong = XPAR_EMACLITE_0_TX_PING_PONG;
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

	यावत् (1) {

		/*
		 * Wait for a Receive packet.
		 */
		यावत् (Recv_Frame_दीर्घता == 0) {
			Recv_Frame_दीर्घता = XEmacLite_Recv(EmacLiteInstPtr,
								(u8 *)RxFrame);
		}
#यदि 1
		प्रारूप_लिख("\n Rcv. Frame %x: %x\n", अङ्कः_सम्बन्धि_Ping_Replies, Recv_Frame_दीर्घता);
		प्रति(पूर्णाङ्क i = 0; i < Recv_Frame_दीर्घता; i++)
			प्रारूप_लिख("%x ", RxFrame[i]);
		प्रारूप_लिख("\n");
#यदि_अन्तः			
		/*
		 * Empty any existing receive frames.
		 */
		XEmacLite_FlushReceive(EmacLiteInstPtr);

		/*
		 * Process the Receive frame.
		 */
		ProcessRecvFrame(EmacLiteInstPtr);
		Recv_Frame_दीर्घता = 0;

		/*
		 * If the number of ping replies sent is equal to that
		 * specified by the user then exit out of this loop.
		 */
		यदि (अङ्कः_सम्बन्धि_Ping_Replies == MAX_PING_REPLIES) {

			प्रत्यागम XST_SUCCESS;
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
स्थिर शून्य ProcessRecvFrame(XEmacLite *InstancePtr)
{
	u16 *RxFramePtr;
	u16 *TxFramePtr;
	u16 *अस्थायी_Ptr;
	u16 Check_योग;
	u32 अग्र_Tx_Buff_आधारः_Addr;
	पूर्णाङ्क सूचकांक;
	पूर्णाङ्क PacketType = 0;

	TxFramePtr = (u16 *)TxFrame;
	RxFramePtr = (u16 *)RxFrame;

	/*
	 * Determine the next expected Tx buffer address.
	 */
	अग्र_Tx_Buff_आधारः_Addr = XEmac_Lite_अग्र_Transmit_Addr(InstancePtr);

	/*
	 * Check the packet type.
	 */
	सूचकांक = MAC_ADDR_LEN;
	अस्थायी_Ptr = (u16 *)LocalMacAddr;
	यावत् (सूचकांक--) {
		यदि (Xil_Ntohs((*(RxFramePtr + सूचकांक)) == प्रसारणम्_ADDR) &&
					(PacketType != MAC_MATCHED_PACKET)) {
			PacketType = प्रसारणम्_PACKET;
		} अन्यथा यदि (Xil_Ntohs((*(RxFramePtr + सूचकांक)) == *(अस्थायी_Ptr + सूचकांक)) &&
					(PacketType != प्रसारणम्_PACKET)) {
			PacketType = MAC_MATCHED_PACKET;
		} अन्यथा {
			PacketType = 0;
			भङ्ग;
		}
	}
#यदि 0
	प्रारूप_लिख("\n Packet type is %x", PacketType);
#यदि_अन्तः
	/*
	 * Process broadcast packet.
	 */
	यदि (PacketType == प्रसारणम्_PACKET) {

		/*
		 * Check for an ARP Packet if so generate a reply.
		 */
		यदि (Xil_Ntohs(*(RxFramePtr + ETHER_PROTO_TYPE_LOC)) ==
				XEL_ETHER_PROTO_TYPE_ARP) {

			/*
			 * IP address of the local machine.
			 */
			अस्थायी_Ptr = (u16 *)LocalIpAddr;

			/*
			 * Check destination IP address of the packet with
			 * local IP address.
			 */
			यदि (
			((*(RxFramePtr + ARP_REQ_DEST_IP_LOC_1)) == *अस्थायी_Ptr++) &&
			((*(RxFramePtr + ARP_REQ_DEST_IP_LOC_2)) == *अस्थायी_Ptr++)) {

				/*
				 * Check ARP packet type(request/reply).
				 */
				यदि (Xil_Ntohs(*(RxFramePtr + ARP_REQ_स्थितिः_LOC)) ==
								ARP_REQUEST) {

					/*
					 * Add destination MAC address
					 * to the reply packet (i.e) source
					 * address of the received packet.
					 */
					सूचकांक = SRC_MAC_ADDR_LOC;
					यावत् (सूचकांक < (SRC_MAC_ADDR_LOC +
							MAC_ADDR_LEN)) {
						*TxFramePtr++ =
							*(RxFramePtr + सूचकांक);
						सूचकांक++;
					}

					/*
					 * Add source (local) MAC address
					 * to the reply packet.
					 */
					सूचकांक = 0;
					अस्थायी_Ptr = (u16 *)LocalMacAddr;
					यावत् (सूचकांक < MAC_ADDR_LEN) {
						*TxFramePtr++ = *अस्थायी_Ptr++;
						सूचकांक++;
					}

					/*
					 * Add Ethernet proto type H/W
					 * type(10/3MBps),H/W address length and
					 * protocol address len (i.e)same as in
					 * the received packet
					 */
					सूचकांक = ETHER_PROTO_TYPE_LOC;
					यावत् (सूचकांक < (ETHER_PROTO_TYPE_LOC +
							ETHER_PROTO_TYPE_LEN +
							ARP_HW_TYPE_LEN +
							ARP_HW_सङ्कलय_LEN
							+ ARP_PROTO_सङ्कलय_LEN)) {
						*TxFramePtr++ =
							*(RxFramePtr + सूचकांक);
						सूचकांक++;
					}

					/*
					 * Add ARP reply status to the reply
					 * packet.
					 */
					*TxFramePtr++ = Xil_Htons(ARP_प्रत्युत्तरम्);

					/*
					 * Add local MAC Address
					 * to the reply packet.
					 */
					अस्थायी_Ptr = (u16 *)LocalMacAddr;
					सूचकांक = 0;
					यावत् (सूचकांक < MAC_ADDR_LEN) {
						*TxFramePtr++ = *अस्थायी_Ptr++;
						सूचकांक++;
					}

					/*
					 * Add local IP Address
					 * to the reply packet.
					 */
					अस्थायी_Ptr = (u16 *)LocalIpAddr;
					सूचकांक = 0;
					यावत् (सूचकांक < IP_ADDR_LEN) {
						*TxFramePtr++ = *अस्थायी_Ptr++ ;
						सूचकांक++;
					}

					/*
					 * Add Destination MAC Address
					 * to the reply packet from the received
					 * packet.
					 */
					सूचकांक = SRC_MAC_ADDR_LOC;
					यावत् (सूचकांक < (SRC_MAC_ADDR_LOC +
							MAC_ADDR_LEN)) {
						*TxFramePtr++ =
							*(RxFramePtr + सूचकांक);
						सूचकांक++;
					}

					/*
					 * Add Destination IP Address
					 * to the reply packet.
					 */
					सूचकांक = ARP_REQ_SRC_IP_LOC;
					यावत् (सूचकांक < (ARP_REQ_SRC_IP_LOC +
							IP_ADDR_LEN)) {
						*TxFramePtr++ =
								*(RxFramePtr + सूचकांक);
						सूचकांक++;
					}

					/*
					 * Fill zeros as per protocol.
					 */
					सूचकांक = 0;
					यावत् (सूचकांक < ARP_ZEROS_LEN) {
						*TxFramePtr++ = 0x0000;
						सूचकांक++;
					}

					/*
					 * Transmit the Reply Packet.
					 */
					XEmacLite_Send(InstancePtr,
							(u8 *)&TxFrame,
							ARP_PACKET_आकार);
				}
			}
		}
	}

	/*
	 * Process packets whose MAC address is matched.
	 */
	यदि (PacketType == MAC_MATCHED_PACKET) {
//		printf("\n MAC matched packet");
		/*
		 * Check ICMP packet.
		 */
		यदि (Xil_Ntohs(*(RxFramePtr + ETHER_PROTO_TYPE_LOC)) ==
						XEL_ETHER_PROTO_TYPE_IP) {
//			printf("\n calculate ip header checksum");
			/*
			 * Check the IP header checksum.
			 */
			Check_योग = Check_योग_Calculation(RxFramePtr,
						IP_HDR_START_LOC,
						IP_HDR_LEN);

			/*
			 * Check the Data field checksum.
			 */
//			printf("\n ip checksum:%x", CheckSum);
			यदि (Check_योग == CORRECT_CKSUM_मानम्) {
				Check_योग = Check_योग_Calculation(RxFramePtr,
						ICMP_दत्त_START_LOC,
						ICMP_दत्त_क्षेत्रम्_LEN);
#यदि 0
			प्रारूप_लिख("\nICMP Rcv Packet: \n");
			प्रति(पूर्णाङ्क i = ICMP_दत्त_START_LOC; i <= ICMP_दत्त_क्षेत्रम्_LEN; i++)
			   प्रारूप_लिख("%x ", RxFramePtr[i]);
			प्रारूप_लिख("\n End of ICMP Rcv Packet");
				
				प्रारूप_लिख("\n data checksum:%x", Check_योग);
#यदि_अन्तः
				यदि (Check_योग == CORRECT_CKSUM_मानम्) {

					/*
					 * Add destination address
					 * to the reply packet (i.e)source
					 * address of the received packet.
					 */
					सूचकांक = SRC_MAC_ADDR_LOC;
					यावत् (सूचकांक < (SRC_MAC_ADDR_LOC +
							MAC_ADDR_LEN)) {
						*TxFramePtr++ =
							*(RxFramePtr + सूचकांक);
						सूचकांक++;
					}

					/*
					 * Add local MAC address
					 * to the reply packet.
					 */
					सूचकांक = 0;
					अस्थायी_Ptr = (u16 *)LocalMacAddr;
					यावत् (सूचकांक < MAC_ADDR_LEN) {
						*TxFramePtr++ = *अस्थायी_Ptr++;
						सूचकांक++;
					}

					/*
					 * Add protocol type
					 * header length and, packet
					 * length(60 Bytes) to the reply packet.
					 */
					सूचकांक = ETHER_PROTO_TYPE_LOC;
					यावत् (सूचकांक < (ETHER_PROTO_TYPE_LOC +
							ETHER_PROTO_TYPE_LEN +
							IP_संस्करणम्_LEN +
							IP_PACKET_LEN)) {
						*TxFramePtr++ =
							*(RxFramePtr + सूचकांक);
						सूचकांक++;
					}

					/*
					 * Identification field a random number
					 * which is set to IDENT_FIELD_VALUE.
					 */
					*TxFramePtr++ = IDENT_क्षेत्रम्_मानम्;

					/*
					 * Add fragment type, time to live and
					 * ICM field. It is same as in the
					 * received packet.
					 */
					सूचकांक = IP_FRAG_क्षेत्रम्_LOC;
					यावत् (सूचकांक < (IP_FRAG_क्षेत्रम्_LOC +
							IP_TTL_ICM_LEN +
							IP_FRAG_क्षेत्रम्_LEN)) {
						*TxFramePtr++ =
							*(RxFramePtr + सूचकांक);
						सूचकांक++;
					}

					/*
					 * Checksum first set to 0 and
					 * added in this field later.
					 */
					*TxFramePtr++ = 0x0000;

					/*
					 * Add Source IP address
					 */
					सूचकांक = 0;
					अस्थायी_Ptr = (u16 *)LocalIpAddr;
					यावत् (सूचकांक < IP_ADDR_LEN) {
						*TxFramePtr++ = *अस्थायी_Ptr++;
						सूचकांक++;
					}

					/*
					 * Add Destination IP address.
					 */
					सूचकांक = ICMP_REQ_SRC_IP_LOC;
					यावत् (सूचकांक < (ICMP_REQ_SRC_IP_LOC +
							IP_ADDR_LEN)) {
						*TxFramePtr++ =
							*(RxFramePtr + सूचकांक);
						सूचकांक++;
					}

					/*
					 * Calculate checksum, and
					 * add it in the appropriate field.
					 */
					Check_योग = Check_योग_Calculation(
							(u16 *)TxFrame,
							IP_HDR_START_LOC,
							IP_HDR_LEN);
					Check_योग = ~Check_योग;
					*(TxFramePtr - IP_CSUM_LOC_पृष्ठभागः) =
								Xil_Htons(Check_योग);

					/*
					 * Echo reply status & checksum.
					 */
					सूचकांक = ICMP_ECHO_क्षेत्रम्_LOC;
					यावत् (सूचकांक < (ICMP_ECHO_क्षेत्रम्_LOC +
							ICMP_ECHO_क्षेत्रम्_LEN)) {
						*TxFramePtr++ = 0x0000;
						सूचकांक++;
					}

					/*
					 * Add data to buffer which was
					 * received from the packet.
					 */
					सूचकांक = ICMP_दत्त_LOC;
					यावत् (सूचकांक < (ICMP_दत्त_LOC +
							ICMP_दत्त_LEN)) {
						*TxFramePtr++ =
								(*(RxFramePtr + सूचकांक));
						सूचकांक++;
					}

					/*
					 * Generate checksum for the data and
					 * add it in the appropriate field.
					 */
					Check_योग = Check_योग_Calculation(
							(u16 *)TxFrame,
							ICMP_दत्त_START_LOC,
							ICMP_दत्त_क्षेत्रम्_LEN);
					Check_योग = ~Check_योग;
					*(TxFramePtr - ICMP_दत्त_CSUM_LOC_पृष्ठभागः)
								= Xil_Htons(Check_योग);

					/*
					 * Transmit the frame.
					 */
#यदि 1
					 प्रारूप_लिख("\n%x. ICMP Tx Packet \n", अङ्कः_सम्बन्धि_Ping_Replies);
					 प्रति(पूर्णाङ्क i = 0; i < ICMP_PACKET_आकार; i++)
					 	प्रारूप_लिख("%x ", TxFrame[i]);
					 प्रारूप_लिख("\n End of ICMP Tx Packet");
#यदि_अन्तः					 
					XEmacLite_Send(InstancePtr,
							(u8 *)&TxFrame,
							ICMP_PACKET_आकार);

					/*
					 * Increment the number of
					 * Ping replies sent.
					 */
					अङ्कः_सम्बन्धि_Ping_Replies++;
//					printf("NumOfPingReplies: %x", NumOfPingReplies);

				}
				अन्यथा
					प्रारूप_लिख("\n Data check sum error");
			}
			अन्यथा
				प्रारूप_लिख("\n IP Check sum error");
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
		योग = योग + Xil_Ntohs(*(RxFramePtr + सूचकांक));
		सूचकांक++;
	}

	/*
	 * Add upper 16 bits to lower 16 bits.
	 */
	Check_योग = योग;
	योग = योग >> 16;
	Check_योग = योग + Check_योग;
	प्रत्यागम Check_योग;
}
