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
/*
 * Instance of the driver
 */
अटल XEmacLite EmacLite;



/*
 * Change this parameter to limit the number of ping replies sent by this
 * program.
 */
#घोषणा MAX_PING_REPLIES	10000	/* Maximum number of ping replies */

#घोषणा BROADCAST_PACKET	1	/* Broadcast packet */
#घोषणा MAC_MATCHED_PACKET	2 	/* Dest MAC matched with local MAC */
#घोषणा IP_ADDR_आकार		4	/* IP Address size in Bytes */
#घोषणा ARP_REQUEST 		0x0001	/* ARP Request bits in Rx packet */
#घोषणा ARP_REPLY 		0x0002 	/* ARP status bits indicating reply */
#घोषणा ARP_PACKET_आकार 	0x3C    /* ARP packet len 60 Bytes */
#घोषणा ICMP_PACKET_आकार 	98 //0x4A    /* ICMP packet length 74 Bytes
					 /* including Src and Dest MAC Address */
#घोषणा BROADCAST_ADDR 		0xFFFF  /* Broadcast Address */
#घोषणा CORRECT_CKSUM_मूल्य	0xFFFF  /* Correct checksum value */
#घोषणा IDENT_FIELD_मूल्य	0x9263	/* Identification field (random num) */

/*
 * Definitions for the locations and length of some of the fields in a
 * IP packet. The lengths are defined in Half-Words (2 bytes).
 */
#घोषणा ETHER_PROTO_TYPE_LEN	1  /* Ethernet protocol Type length  */
#घोषणा SRC_MAC_ADDR_LOC	3  /* Source MAC address location */
#घोषणा MAC_ADDR_LEN 		3  /* MAC address length */
#घोषणा ETHER_PROTO_TYPE_LOC	6  /* Ethernet Proto type location */

#घोषणा ARP_HW_TYPE_LEN 	1  /* Hardware Type length  */
#घोषणा ARP_PROTO_TYPE_LEN	1  /* Protocol Type length  */
#घोषणा ARP_HW_ADD_LEN		1  /* Hardware address length */
#घोषणा ARP_PROTO_ADD_LEN	1  /* Protocol address length */
#घोषणा ARP_ZEROS_LEN		9  /* Length to be filled with zeros */
#घोषणा ARP_REQ_STATUS_LOC 	10 /* ARP request location */
#घोषणा ARP_REQ_SRC_IP_LOC 	14 /* Src IP address location of ARP request */
#घोषणा ARP_REQ_DEST_IP_LOC_1 	19 /* Destination IP's 1st half word location */
#घोषणा ARP_REQ_DEST_IP_LOC_2 	20 /* Destination IP's 2nd half word location */

#घोषणा IP_VERSION_LEN 		1  /* IP Version length  */
#घोषणा IP_PACKET_LEN 		1  /* IP Packet length field  */
#घोषणा IP_FRAG_FIELD_LEN	1  /* Fragment field len in ICMP packet */
#घोषणा IP_TTL_ICM_LEN 		1  /* Time to live and ICM fields length */
#घोषणा IP_ADDR_LEN 		2  /* Size of IP address in half-words */
#घोषणा IP_CSUM_LOC_BACK	5  /* IP checksum location from end of frame */
#घोषणा IP_HDR_START_LOC 	7  /* IP header start location */
#घोषणा IP_HDR_LEN 		10 /* IP Header length */
#घोषणा IP_FRAG_FIELD_LOC 	10 /* Fragment field location */

#घोषणा ICMP_TYPE_LEN 		1  /* ICMP Type length */
#घोषणा ICMP_ECHO_FIELD_LEN 	2  /* Echo field length in half-words */
#घोषणा ICMP_REQ_SRC_IP_LOC 	13 /* Src IP address location of ICMP request */
#घोषणा ICMP_ECHO_FIELD_LOC 	17 /* Echo field location */
#घोषणा ICMP_तथ्य_START_LOC 	17 /* Data field start location */
#घोषणा ICMP_तथ्य_LEN 		30  //18  /* ICMP data length */
#घोषणा ICMP_तथ्य_LOC 		19 /* ICMP data location including
				      identifier number and sequence number */
#घोषणा ICMP_तथ्य_CSUM_LOC_BACK 31 //19 
/* Data checksum location from end of
					frame */
#घोषणा ICMP_तथ्य_FIELD_LEN 	32 //20 /* Data field length */

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

अटल पूर्णांक EmacLitePingReplyExample(u16 DeviceId);

अटल व्योम ProcessRecvFrame(XEmacLite *InstancePtr);

अटल u16 Check_योग_Calculation(u16 *RxFramePtr, पूर्णांक StartLoc, पूर्णांक लंबाई);

/************************** Variable Definitions *****************************/

/*
 * Set up a local MAC address.
 */
अटल u8 LocalMacAddr[XEL_MAC_ADDR_आकार] =
{
	0x00, 0x00, 0x5E, 0x00, 0xFA, 0xCE
};

/*
 * The IP address was set to 172.16.63.121. User need to set a free IP address
 * based on the network on which this example is to be run.
 */
अटल u8 LocalIpAddr[IP_ADDR_आकार] =
{
	192, 168, 1, 25
};

अटल XEmacLite EmacLiteInstance;	/* Instance of the EmacLite driver */

/*
 * Buffers used for Transmission and Reception of Packets. These are declared as
 * global so that they are not a part of the stack.
 */
अटल u8 RxFrame[XEL_MAX_FRAME_आकार];
अटल u8 TxFrame[XEL_MAX_FRAME_आकार];

/*
 * Variable used to indicate the length of the received frame.
 */
बाह्य अस्थिर u32 Recv_Frame_लंबाई = 0;

/*
 * Variable used to indicate the number of Ping replies sent.
 */
u32 अंक_Of_Ping_Replies;
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
पूर्णांक मुख्य()
{
	पूर्णांक Status;
	arpcount = 0;
	/*
	 * Run the EmacLite Ping reply example.
	 */
	Status = EmacLitePingReplyExample(EMAC_DEVICE_ID);
	अगर (Status != XST_SUCCESS) {
		xil_printf("Emaclite ping reply Example Failed\r\n");
		वापस XST_FAILURE;
	}

	xil_printf("Successfully ran Emaclite ping reply Example\r\n");
	वापस XST_SUCCESS;
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
पूर्णांक EmacLitePingReplyExample(u16 DeviceId)
{
	पूर्णांक Status, गिनती = 0;
	XEmacLite *EmacLiteInstPtr = &EmacLiteInstance;
	XEmacLite_Config *ConfigPtr;
	अंक_Of_Ping_Replies = 0;

	/*
	 * Initialize the EmacLite device.
	 */
	ConfigPtr = &XEmacLite_ConfigTable;
	अगर (ConfigPtr == शून्य) {
		वापस -1;
	}
	म_लिखो("\n ");

	ConfigPtr->BaseAddress = (UINTPTR *) 0X44000;
	ConfigPtr->RxPingPong = XPAR_EMACLITE_0_RX_PING_PONG;
	ConfigPtr->MdioInclude = XPAR_EMACLITE_0_INCLUDE_MDIO;
	ConfigPtr->TxPingPong = XPAR_EMACLITE_0_TX_PING_PONG;
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

	जबतक (1) {

		/*
		 * Wait for a Receive packet.
		 */
		जबतक (Recv_Frame_लंबाई == 0) {
			Recv_Frame_लंबाई = XEmacLite_Recv(EmacLiteInstPtr,
								(u8 *)RxFrame);
		}
#अगर 1
		म_लिखो("\n Rcv. Frame %x: %x\n", अंक_Of_Ping_Replies, Recv_Frame_लंबाई);
		क्रम(पूर्णांक i = 0; i < Recv_Frame_लंबाई; i++)
			म_लिखो("%x ", RxFrame[i]);
		म_लिखो("\n");
#पूर्ण_अगर			
		/*
		 * Empty any existing receive frames.
		 */
		XEmacLite_FlushReceive(EmacLiteInstPtr);

		/*
		 * Process the Receive frame.
		 */
		ProcessRecvFrame(EmacLiteInstPtr);
		Recv_Frame_लंबाई = 0;

		/*
		 * If the number of ping replies sent is equal to that
		 * specified by the user then exit out of this loop.
		 */
		अगर (अंक_Of_Ping_Replies == MAX_PING_REPLIES) {

			वापस XST_SUCCESS;
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
अटल व्योम ProcessRecvFrame(XEmacLite *InstancePtr)
{
	u16 *RxFramePtr;
	u16 *TxFramePtr;
	u16 *अस्थायी_Ptr;
	u16 Check_योग;
	u32 अग्र_Tx_Buff_Base_Addr;
	पूर्णांक सूचकांक;
	पूर्णांक PacketType = 0;

	TxFramePtr = (u16 *)TxFrame;
	RxFramePtr = (u16 *)RxFrame;

	/*
	 * Determine the next expected Tx buffer address.
	 */
	अग्र_Tx_Buff_Base_Addr = XEmac_Lite_अग्र_Transmit_Addr(InstancePtr);

	/*
	 * Check the packet type.
	 */
	सूचकांक = MAC_ADDR_LEN;
	अस्थायी_Ptr = (u16 *)LocalMacAddr;
	जबतक (सूचकांक--) {
		अगर (Xil_Ntohs((*(RxFramePtr + सूचकांक)) == BROADCAST_ADDR) &&
					(PacketType != MAC_MATCHED_PACKET)) {
			PacketType = BROADCAST_PACKET;
		} अन्यथा अगर (Xil_Ntohs((*(RxFramePtr + सूचकांक)) == *(अस्थायी_Ptr + सूचकांक)) &&
					(PacketType != BROADCAST_PACKET)) {
			PacketType = MAC_MATCHED_PACKET;
		} अन्यथा {
			PacketType = 0;
			अवरोध;
		}
	}
#अगर 0
	म_लिखो("\n Packet type is %x", PacketType);
#पूर्ण_अगर
	/*
	 * Process broadcast packet.
	 */
	अगर (PacketType == BROADCAST_PACKET) {

		/*
		 * Check for an ARP Packet if so generate a reply.
		 */
		अगर (Xil_Ntohs(*(RxFramePtr + ETHER_PROTO_TYPE_LOC)) ==
				XEL_ETHER_PROTO_TYPE_ARP) {

			/*
			 * IP address of the local machine.
			 */
			अस्थायी_Ptr = (u16 *)LocalIpAddr;

			/*
			 * Check destination IP address of the packet with
			 * local IP address.
			 */
			अगर (
			((*(RxFramePtr + ARP_REQ_DEST_IP_LOC_1)) == *अस्थायी_Ptr++) &&
			((*(RxFramePtr + ARP_REQ_DEST_IP_LOC_2)) == *अस्थायी_Ptr++)) {

				/*
				 * Check ARP packet type(request/reply).
				 */
				अगर (Xil_Ntohs(*(RxFramePtr + ARP_REQ_STATUS_LOC)) ==
								ARP_REQUEST) {

					/*
					 * Add destination MAC address
					 * to the reply packet (i.e) source
					 * address of the received packet.
					 */
					सूचकांक = SRC_MAC_ADDR_LOC;
					जबतक (सूचकांक < (SRC_MAC_ADDR_LOC +
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
					जबतक (सूचकांक < MAC_ADDR_LEN) {
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
					जबतक (सूचकांक < (ETHER_PROTO_TYPE_LOC +
							ETHER_PROTO_TYPE_LEN +
							ARP_HW_TYPE_LEN +
							ARP_HW_ADD_LEN
							+ ARP_PROTO_ADD_LEN)) {
						*TxFramePtr++ =
							*(RxFramePtr + सूचकांक);
						सूचकांक++;
					}

					/*
					 * Add ARP reply status to the reply
					 * packet.
					 */
					*TxFramePtr++ = Xil_Htons(ARP_REPLY);

					/*
					 * Add local MAC Address
					 * to the reply packet.
					 */
					अस्थायी_Ptr = (u16 *)LocalMacAddr;
					सूचकांक = 0;
					जबतक (सूचकांक < MAC_ADDR_LEN) {
						*TxFramePtr++ = *अस्थायी_Ptr++;
						सूचकांक++;
					}

					/*
					 * Add local IP Address
					 * to the reply packet.
					 */
					अस्थायी_Ptr = (u16 *)LocalIpAddr;
					सूचकांक = 0;
					जबतक (सूचकांक < IP_ADDR_LEN) {
						*TxFramePtr++ = *अस्थायी_Ptr++ ;
						सूचकांक++;
					}

					/*
					 * Add Destination MAC Address
					 * to the reply packet from the received
					 * packet.
					 */
					सूचकांक = SRC_MAC_ADDR_LOC;
					जबतक (सूचकांक < (SRC_MAC_ADDR_LOC +
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
					जबतक (सूचकांक < (ARP_REQ_SRC_IP_LOC +
							IP_ADDR_LEN)) {
						*TxFramePtr++ =
								*(RxFramePtr + सूचकांक);
						सूचकांक++;
					}

					/*
					 * Fill zeros as per protocol.
					 */
					सूचकांक = 0;
					जबतक (सूचकांक < ARP_ZEROS_LEN) {
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
	अगर (PacketType == MAC_MATCHED_PACKET) {
//		printf("\n MAC matched packet");
		/*
		 * Check ICMP packet.
		 */
		अगर (Xil_Ntohs(*(RxFramePtr + ETHER_PROTO_TYPE_LOC)) ==
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
			अगर (Check_योग == CORRECT_CKSUM_मूल्य) {
				Check_योग = Check_योग_Calculation(RxFramePtr,
						ICMP_तथ्य_START_LOC,
						ICMP_तथ्य_FIELD_LEN);
#अगर 0
			म_लिखो("\nICMP Rcv Packet: \n");
			क्रम(पूर्णांक i = ICMP_तथ्य_START_LOC; i <= ICMP_तथ्य_FIELD_LEN; i++)
			   म_लिखो("%x ", RxFramePtr[i]);
			म_लिखो("\n End of ICMP Rcv Packet");
				
				म_लिखो("\n data checksum:%x", Check_योग);
#पूर्ण_अगर
				अगर (Check_योग == CORRECT_CKSUM_मूल्य) {

					/*
					 * Add destination address
					 * to the reply packet (i.e)source
					 * address of the received packet.
					 */
					सूचकांक = SRC_MAC_ADDR_LOC;
					जबतक (सूचकांक < (SRC_MAC_ADDR_LOC +
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
					जबतक (सूचकांक < MAC_ADDR_LEN) {
						*TxFramePtr++ = *अस्थायी_Ptr++;
						सूचकांक++;
					}

					/*
					 * Add protocol type
					 * header length and, packet
					 * length(60 Bytes) to the reply packet.
					 */
					सूचकांक = ETHER_PROTO_TYPE_LOC;
					जबतक (सूचकांक < (ETHER_PROTO_TYPE_LOC +
							ETHER_PROTO_TYPE_LEN +
							IP_VERSION_LEN +
							IP_PACKET_LEN)) {
						*TxFramePtr++ =
							*(RxFramePtr + सूचकांक);
						सूचकांक++;
					}

					/*
					 * Identification field a random number
					 * which is set to IDENT_FIELD_VALUE.
					 */
					*TxFramePtr++ = IDENT_FIELD_मूल्य;

					/*
					 * Add fragment type, time to live and
					 * ICM field. It is same as in the
					 * received packet.
					 */
					सूचकांक = IP_FRAG_FIELD_LOC;
					जबतक (सूचकांक < (IP_FRAG_FIELD_LOC +
							IP_TTL_ICM_LEN +
							IP_FRAG_FIELD_LEN)) {
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
					जबतक (सूचकांक < IP_ADDR_LEN) {
						*TxFramePtr++ = *अस्थायी_Ptr++;
						सूचकांक++;
					}

					/*
					 * Add Destination IP address.
					 */
					सूचकांक = ICMP_REQ_SRC_IP_LOC;
					जबतक (सूचकांक < (ICMP_REQ_SRC_IP_LOC +
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
					*(TxFramePtr - IP_CSUM_LOC_BACK) =
								Xil_Htons(Check_योग);

					/*
					 * Echo reply status & checksum.
					 */
					सूचकांक = ICMP_ECHO_FIELD_LOC;
					जबतक (सूचकांक < (ICMP_ECHO_FIELD_LOC +
							ICMP_ECHO_FIELD_LEN)) {
						*TxFramePtr++ = 0x0000;
						सूचकांक++;
					}

					/*
					 * Add data to buffer which was
					 * received from the packet.
					 */
					सूचकांक = ICMP_तथ्य_LOC;
					जबतक (सूचकांक < (ICMP_तथ्य_LOC +
							ICMP_तथ्य_LEN)) {
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
							ICMP_तथ्य_START_LOC,
							ICMP_तथ्य_FIELD_LEN);
					Check_योग = ~Check_योग;
					*(TxFramePtr - ICMP_तथ्य_CSUM_LOC_BACK)
								= Xil_Htons(Check_योग);

					/*
					 * Transmit the frame.
					 */
#अगर 1
					 म_लिखो("\n%x. ICMP Tx Packet \n", अंक_Of_Ping_Replies);
					 क्रम(पूर्णांक i = 0; i < ICMP_PACKET_आकार; i++)
					 	म_लिखो("%x ", TxFrame[i]);
					 म_लिखो("\n End of ICMP Tx Packet");
#पूर्ण_अगर					 
					XEmacLite_Send(InstancePtr,
							(u8 *)&TxFrame,
							ICMP_PACKET_आकार);

					/*
					 * Increment the number of
					 * Ping replies sent.
					 */
					अंक_Of_Ping_Replies++;
//					printf("NumOfPingReplies: %x", NumOfPingReplies);

				}
				अन्यथा
					म_लिखो("\n Data check sum error");
			}
			अन्यथा
				म_लिखो("\n IP Check sum error");
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
		योग = योग + Xil_Ntohs(*(RxFramePtr + सूचकांक));
		सूचकांक++;
	}

	/*
	 * Add upper 16 bits to lower 16 bits.
	 */
	Check_योग = योग;
	योग = योग >> 16;
	Check_योग = योग + Check_योग;
	वापस Check_योग;
}
