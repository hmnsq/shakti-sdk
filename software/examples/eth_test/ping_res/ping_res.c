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
/*
 * Instance of the driver
 */
স্থির XEmacLite EmacLite;



/*
 * Change this parameter to limit the number of ping replies sent by this
 * program.
 */
#define MAX_PING_REPLIES	10000	/* Maximum number of ping replies */

#define BROADCAST_PACKET	1	/* Broadcast packet */
#define MAC_MATCHED_PACKET	2 	/* Dest MAC matched with local MAC */
#define IP_ADDR_আকার		4	/* IP Address size in Bytes */
#define ARP_REQUEST 		0x0001	/* ARP Request bits in Rx packet */
#define ARP_REPLY 		0x0002 	/* ARP status bits indicating reply */
#define ARP_PACKET_আকার 	0x3C    /* ARP packet len 60 Bytes */
#define ICMP_PACKET_আকার 	98 //0x4A    /* ICMP packet length 74 Bytes
					 /* including Src and Dest MAC Address */
#define BROADCAST_ADDR 		0xFFFF  /* Broadcast Address */
#define CORRECT_CKSUM_মান	0xFFFF  /* Correct checksum value */
#define IDENT_FIELD_মান	0x9263	/* Identification field (random num) */

/*
 * Definitions for the locations and length of some of the fields in a
 * IP packet. The lengths are defined in Half-Words (2 bytes).
 */
#define ETHER_PROTO_TYPE_LEN	1  /* Ethernet protocol Type length  */
#define SRC_MAC_ADDR_LOC	3  /* Source MAC address location */
#define MAC_ADDR_LEN 		3  /* MAC address length */
#define ETHER_PROTO_TYPE_LOC	6  /* Ethernet Proto type location */

#define ARP_HW_TYPE_LEN 	1  /* Hardware Type length  */
#define ARP_PROTO_TYPE_LEN	1  /* Protocol Type length  */
#define ARP_HW_ADD_LEN		1  /* Hardware address length */
#define ARP_PROTO_ADD_LEN	1  /* Protocol address length */
#define ARP_ZEROS_LEN		9  /* Length to be filled with zeros */
#define ARP_REQ_STATUS_LOC 	10 /* ARP request location */
#define ARP_REQ_SRC_IP_LOC 	14 /* Src IP address location of ARP request */
#define ARP_REQ_DEST_IP_LOC_1 	19 /* Destination IP's 1st half word location */
#define ARP_REQ_DEST_IP_LOC_2 	20 /* Destination IP's 2nd half word location */

#define IP_VERSION_LEN 		1  /* IP Version length  */
#define IP_PACKET_LEN 		1  /* IP Packet length field  */
#define IP_FRAG_FIELD_LEN	1  /* Fragment field len in ICMP packet */
#define IP_TTL_ICM_LEN 		1  /* Time to live and ICM fields length */
#define IP_ADDR_LEN 		2  /* Size of IP address in half-words */
#define IP_CSUM_LOC_BACK	5  /* IP checksum location from end of frame */
#define IP_HDR_START_LOC 	7  /* IP header start location */
#define IP_HDR_LEN 		10 /* IP Header length */
#define IP_FRAG_FIELD_LOC 	10 /* Fragment field location */

#define ICMP_TYPE_LEN 		1  /* ICMP Type length */
#define ICMP_ECHO_FIELD_LEN 	2  /* Echo field length in half-words */
#define ICMP_REQ_SRC_IP_LOC 	13 /* Src IP address location of ICMP request */
#define ICMP_ECHO_FIELD_LOC 	17 /* Echo field location */
#define ICMP_তথ্য_START_LOC 	17 /* Data field start location */
#define ICMP_তথ্য_LEN 		30  //18  /* ICMP data length */
#define ICMP_তথ্য_LOC 		19 /* ICMP data location including
				      identifier number and sequence number */
#define ICMP_তথ্য_CSUM_LOC_BACK 31 //19 
/* Data checksum location from end of
					frame */
#define ICMP_তথ্য_FIELD_LEN 	32 //20 /* Data field length */

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

স্থির পূর্ণসংখ্যা EmacLitePingReplyExample(u16 DeviceId);

স্থির শূন্য ProcessRecvFrame(XEmacLite *InstancePtr);

স্থির u16 Check_যোগ_Calculation(u16 *RxFramePtr, পূর্ণসংখ্যা StartLoc, পূর্ণসংখ্যা দৈর্ঘ্য);

/************************** Variable Definitions *****************************/

/*
 * Set up a local MAC address.
 */
স্থির u8 LocalMacAddr[XEL_MAC_ADDR_আকার] =
{
	0x00, 0x00, 0x5E, 0x00, 0xFA, 0xCE
};

/*
 * The IP address was set to 172.16.63.121. User need to set a free IP address
 * based on the network on which this example is to be run.
 */
স্থির u8 LocalIpAddr[IP_ADDR_আকার] =
{
	192, 168, 1, 25
};

স্থির XEmacLite EmacLiteInstance;	/* Instance of the EmacLite driver */

/*
 * Buffers used for Transmission and Reception of Packets. These are declared as
 * global so that they are not a part of the stack.
 */
স্থির u8 RxFrame[XEL_MAX_FRAME_আকার];
স্থির u8 TxFrame[XEL_MAX_FRAME_আকার];

/*
 * Variable used to indicate the length of the received frame.
 */
বাহ্যিক অস্থির u32 Recv_Frame_দৈর্ঘ্য = 0;

/*
 * Variable used to indicate the number of Ping replies sent.
 */
u32 অঙ্ক_Of_Ping_Replies;
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
পূর্ণসংখ্যা প্রধান()
{
	পূর্ণসংখ্যা Status;
	arpcount = 0;
	/*
	 * Run the EmacLite Ping reply example.
	 */
	Status = EmacLitePingReplyExample(EMAC_DEVICE_ID);
	যদি (Status != XST_SUCCESS) {
		xil_printf("Emaclite ping reply Example Failed\r\n");
		ফেরত XST_FAILURE;
	}

	xil_printf("Successfully ran Emaclite ping reply Example\r\n");
	ফেরত XST_SUCCESS;
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
পূর্ণসংখ্যা EmacLitePingReplyExample(u16 DeviceId)
{
	পূর্ণসংখ্যা Status, গুনতি = 0;
	XEmacLite *EmacLiteInstPtr = &EmacLiteInstance;
	XEmacLite_Config *ConfigPtr;
	অঙ্ক_Of_Ping_Replies = 0;

	/*
	 * Initialize the EmacLite device.
	 */
	ConfigPtr = &XEmacLite_ConfigTable;
	যদি (ConfigPtr == ফাঁকা) {
		ফেরত -1;
	}
	printf("\n ");

	ConfigPtr->BaseAddress = (UINTPTR *) 0X44000;
	ConfigPtr->RxPingPong = XPAR_EMACLITE_0_RX_PING_PONG;
	ConfigPtr->MdioInclude = XPAR_EMACLITE_0_INCLUDE_MDIO;
	ConfigPtr->TxPingPong = XPAR_EMACLITE_0_TX_PING_PONG;
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

	যখন (1) {

		/*
		 * Wait for a Receive packet.
		 */
		যখন (Recv_Frame_দৈর্ঘ্য == 0) {
			Recv_Frame_দৈর্ঘ্য = XEmacLite_Recv(EmacLiteInstPtr,
								(u8 *)RxFrame);
		}
#যদি 1
		printf("\n Rcv. Frame %x: %x\n", অঙ্ক_Of_Ping_Replies, Recv_Frame_দৈর্ঘ্য);
		জন্য(পূর্ণসংখ্যা i = 0; i < Recv_Frame_দৈর্ঘ্য; i++)
			printf("%x ", RxFrame[i]);
		printf("\n");
#endif			
		/*
		 * Empty any existing receive frames.
		 */
		XEmacLite_FlushReceive(EmacLiteInstPtr);

		/*
		 * Process the Receive frame.
		 */
		ProcessRecvFrame(EmacLiteInstPtr);
		Recv_Frame_দৈর্ঘ্য = 0;

		/*
		 * If the number of ping replies sent is equal to that
		 * specified by the user then exit out of this loop.
		 */
		যদি (অঙ্ক_Of_Ping_Replies == MAX_PING_REPLIES) {

			ফেরত XST_SUCCESS;
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
স্থির শূন্য ProcessRecvFrame(XEmacLite *InstancePtr)
{
	u16 *RxFramePtr;
	u16 *TxFramePtr;
	u16 *অস্থায়ী_Ptr;
	u16 Check_যোগ;
	u32 পরবর্তী_Tx_Buff_Base_Addr;
	পূর্ণসংখ্যা সূচক;
	পূর্ণসংখ্যা PacketType = 0;

	TxFramePtr = (u16 *)TxFrame;
	RxFramePtr = (u16 *)RxFrame;

	/*
	 * Determine the next expected Tx buffer address.
	 */
	পরবর্তী_Tx_Buff_Base_Addr = XEmac_Lite_পরবর্তী_Transmit_Addr(InstancePtr);

	/*
	 * Check the packet type.
	 */
	সূচক = MAC_ADDR_LEN;
	অস্থায়ী_Ptr = (u16 *)LocalMacAddr;
	যখন (সূচক--) {
		যদি (Xil_Ntohs((*(RxFramePtr + সূচক)) == BROADCAST_ADDR) &&
					(PacketType != MAC_MATCHED_PACKET)) {
			PacketType = BROADCAST_PACKET;
		} অন্যথা যদি (Xil_Ntohs((*(RxFramePtr + সূচক)) == *(অস্থায়ী_Ptr + সূচক)) &&
					(PacketType != BROADCAST_PACKET)) {
			PacketType = MAC_MATCHED_PACKET;
		} অন্যথা {
			PacketType = 0;
			বিরতি;
		}
	}
#যদি 0
	printf("\n Packet type is %x", PacketType);
#endif
	/*
	 * Process broadcast packet.
	 */
	যদি (PacketType == BROADCAST_PACKET) {

		/*
		 * Check for an ARP Packet if so generate a reply.
		 */
		যদি (Xil_Ntohs(*(RxFramePtr + ETHER_PROTO_TYPE_LOC)) ==
				XEL_ETHER_PROTO_TYPE_ARP) {

			/*
			 * IP address of the local machine.
			 */
			অস্থায়ী_Ptr = (u16 *)LocalIpAddr;

			/*
			 * Check destination IP address of the packet with
			 * local IP address.
			 */
			যদি (
			((*(RxFramePtr + ARP_REQ_DEST_IP_LOC_1)) == *অস্থায়ী_Ptr++) &&
			((*(RxFramePtr + ARP_REQ_DEST_IP_LOC_2)) == *অস্থায়ী_Ptr++)) {

				/*
				 * Check ARP packet type(request/reply).
				 */
				যদি (Xil_Ntohs(*(RxFramePtr + ARP_REQ_STATUS_LOC)) ==
								ARP_REQUEST) {

					/*
					 * Add destination MAC address
					 * to the reply packet (i.e) source
					 * address of the received packet.
					 */
					সূচক = SRC_MAC_ADDR_LOC;
					যখন (সূচক < (SRC_MAC_ADDR_LOC +
							MAC_ADDR_LEN)) {
						*TxFramePtr++ =
							*(RxFramePtr + সূচক);
						সূচক++;
					}

					/*
					 * Add source (local) MAC address
					 * to the reply packet.
					 */
					সূচক = 0;
					অস্থায়ী_Ptr = (u16 *)LocalMacAddr;
					যখন (সূচক < MAC_ADDR_LEN) {
						*TxFramePtr++ = *অস্থায়ী_Ptr++;
						সূচক++;
					}

					/*
					 * Add Ethernet proto type H/W
					 * type(10/3MBps),H/W address length and
					 * protocol address len (i.e)same as in
					 * the received packet
					 */
					সূচক = ETHER_PROTO_TYPE_LOC;
					যখন (সূচক < (ETHER_PROTO_TYPE_LOC +
							ETHER_PROTO_TYPE_LEN +
							ARP_HW_TYPE_LEN +
							ARP_HW_ADD_LEN
							+ ARP_PROTO_ADD_LEN)) {
						*TxFramePtr++ =
							*(RxFramePtr + সূচক);
						সূচক++;
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
					অস্থায়ী_Ptr = (u16 *)LocalMacAddr;
					সূচক = 0;
					যখন (সূচক < MAC_ADDR_LEN) {
						*TxFramePtr++ = *অস্থায়ী_Ptr++;
						সূচক++;
					}

					/*
					 * Add local IP Address
					 * to the reply packet.
					 */
					অস্থায়ী_Ptr = (u16 *)LocalIpAddr;
					সূচক = 0;
					যখন (সূচক < IP_ADDR_LEN) {
						*TxFramePtr++ = *অস্থায়ী_Ptr++ ;
						সূচক++;
					}

					/*
					 * Add Destination MAC Address
					 * to the reply packet from the received
					 * packet.
					 */
					সূচক = SRC_MAC_ADDR_LOC;
					যখন (সূচক < (SRC_MAC_ADDR_LOC +
							MAC_ADDR_LEN)) {
						*TxFramePtr++ =
							*(RxFramePtr + সূচক);
						সূচক++;
					}

					/*
					 * Add Destination IP Address
					 * to the reply packet.
					 */
					সূচক = ARP_REQ_SRC_IP_LOC;
					যখন (সূচক < (ARP_REQ_SRC_IP_LOC +
							IP_ADDR_LEN)) {
						*TxFramePtr++ =
								*(RxFramePtr + সূচক);
						সূচক++;
					}

					/*
					 * Fill zeros as per protocol.
					 */
					সূচক = 0;
					যখন (সূচক < ARP_ZEROS_LEN) {
						*TxFramePtr++ = 0x0000;
						সূচক++;
					}

					/*
					 * Transmit the Reply Packet.
					 */
					XEmacLite_Send(InstancePtr,
							(u8 *)&TxFrame,
							ARP_PACKET_আকার);
				}
			}
		}
	}

	/*
	 * Process packets whose MAC address is matched.
	 */
	যদি (PacketType == MAC_MATCHED_PACKET) {
//		printf("\n MAC matched packet");
		/*
		 * Check ICMP packet.
		 */
		যদি (Xil_Ntohs(*(RxFramePtr + ETHER_PROTO_TYPE_LOC)) ==
						XEL_ETHER_PROTO_TYPE_IP) {
//			printf("\n calculate ip header checksum");
			/*
			 * Check the IP header checksum.
			 */
			Check_যোগ = Check_যোগ_Calculation(RxFramePtr,
						IP_HDR_START_LOC,
						IP_HDR_LEN);

			/*
			 * Check the Data field checksum.
			 */
//			printf("\n ip checksum:%x", CheckSum);
			যদি (Check_যোগ == CORRECT_CKSUM_মান) {
				Check_যোগ = Check_যোগ_Calculation(RxFramePtr,
						ICMP_তথ্য_START_LOC,
						ICMP_তথ্য_FIELD_LEN);
#যদি 0
			printf("\nICMP Rcv Packet: \n");
			জন্য(পূর্ণসংখ্যা i = ICMP_তথ্য_START_LOC; i <= ICMP_তথ্য_FIELD_LEN; i++)
			   printf("%x ", RxFramePtr[i]);
			printf("\n End of ICMP Rcv Packet");
				
				printf("\n data checksum:%x", Check_যোগ);
#endif
				যদি (Check_যোগ == CORRECT_CKSUM_মান) {

					/*
					 * Add destination address
					 * to the reply packet (i.e)source
					 * address of the received packet.
					 */
					সূচক = SRC_MAC_ADDR_LOC;
					যখন (সূচক < (SRC_MAC_ADDR_LOC +
							MAC_ADDR_LEN)) {
						*TxFramePtr++ =
							*(RxFramePtr + সূচক);
						সূচক++;
					}

					/*
					 * Add local MAC address
					 * to the reply packet.
					 */
					সূচক = 0;
					অস্থায়ী_Ptr = (u16 *)LocalMacAddr;
					যখন (সূচক < MAC_ADDR_LEN) {
						*TxFramePtr++ = *অস্থায়ী_Ptr++;
						সূচক++;
					}

					/*
					 * Add protocol type
					 * header length and, packet
					 * length(60 Bytes) to the reply packet.
					 */
					সূচক = ETHER_PROTO_TYPE_LOC;
					যখন (সূচক < (ETHER_PROTO_TYPE_LOC +
							ETHER_PROTO_TYPE_LEN +
							IP_VERSION_LEN +
							IP_PACKET_LEN)) {
						*TxFramePtr++ =
							*(RxFramePtr + সূচক);
						সূচক++;
					}

					/*
					 * Identification field a random number
					 * which is set to IDENT_FIELD_VALUE.
					 */
					*TxFramePtr++ = IDENT_FIELD_মান;

					/*
					 * Add fragment type, time to live and
					 * ICM field. It is same as in the
					 * received packet.
					 */
					সূচক = IP_FRAG_FIELD_LOC;
					যখন (সূচক < (IP_FRAG_FIELD_LOC +
							IP_TTL_ICM_LEN +
							IP_FRAG_FIELD_LEN)) {
						*TxFramePtr++ =
							*(RxFramePtr + সূচক);
						সূচক++;
					}

					/*
					 * Checksum first set to 0 and
					 * added in this field later.
					 */
					*TxFramePtr++ = 0x0000;

					/*
					 * Add Source IP address
					 */
					সূচক = 0;
					অস্থায়ী_Ptr = (u16 *)LocalIpAddr;
					যখন (সূচক < IP_ADDR_LEN) {
						*TxFramePtr++ = *অস্থায়ী_Ptr++;
						সূচক++;
					}

					/*
					 * Add Destination IP address.
					 */
					সূচক = ICMP_REQ_SRC_IP_LOC;
					যখন (সূচক < (ICMP_REQ_SRC_IP_LOC +
							IP_ADDR_LEN)) {
						*TxFramePtr++ =
							*(RxFramePtr + সূচক);
						সূচক++;
					}

					/*
					 * Calculate checksum, and
					 * add it in the appropriate field.
					 */
					Check_যোগ = Check_যোগ_Calculation(
							(u16 *)TxFrame,
							IP_HDR_START_LOC,
							IP_HDR_LEN);
					Check_যোগ = ~Check_যোগ;
					*(TxFramePtr - IP_CSUM_LOC_BACK) =
								Xil_Htons(Check_যোগ);

					/*
					 * Echo reply status & checksum.
					 */
					সূচক = ICMP_ECHO_FIELD_LOC;
					যখন (সূচক < (ICMP_ECHO_FIELD_LOC +
							ICMP_ECHO_FIELD_LEN)) {
						*TxFramePtr++ = 0x0000;
						সূচক++;
					}

					/*
					 * Add data to buffer which was
					 * received from the packet.
					 */
					সূচক = ICMP_তথ্য_LOC;
					যখন (সূচক < (ICMP_তথ্য_LOC +
							ICMP_তথ্য_LEN)) {
						*TxFramePtr++ =
								(*(RxFramePtr + সূচক));
						সূচক++;
					}

					/*
					 * Generate checksum for the data and
					 * add it in the appropriate field.
					 */
					Check_যোগ = Check_যোগ_Calculation(
							(u16 *)TxFrame,
							ICMP_তথ্য_START_LOC,
							ICMP_তথ্য_FIELD_LEN);
					Check_যোগ = ~Check_যোগ;
					*(TxFramePtr - ICMP_তথ্য_CSUM_LOC_BACK)
								= Xil_Htons(Check_যোগ);

					/*
					 * Transmit the frame.
					 */
#যদি 1
					 printf("\n%x. ICMP Tx Packet \n", অঙ্ক_Of_Ping_Replies);
					 জন্য(পূর্ণসংখ্যা i = 0; i < ICMP_PACKET_আকার; i++)
					 	printf("%x ", TxFrame[i]);
					 printf("\n End of ICMP Tx Packet");
#endif					 
					XEmacLite_Send(InstancePtr,
							(u8 *)&TxFrame,
							ICMP_PACKET_আকার);

					/*
					 * Increment the number of
					 * Ping replies sent.
					 */
					অঙ্ক_Of_Ping_Replies++;
//					printf("NumOfPingReplies: %x", NumOfPingReplies);

				}
				অন্যথা
					printf("\n Data check sum error");
			}
			অন্যথা
				printf("\n IP Check sum error");
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
		যোগ = যোগ + Xil_Ntohs(*(RxFramePtr + সূচক));
		সূচক++;
	}

	/*
	 * Add upper 16 bits to lower 16 bits.
	 */
	Check_যোগ = যোগ;
	যোগ = যোগ >> 16;
	Check_যোগ = যোগ + Check_যোগ;
	ফেরত Check_যোগ;
}
