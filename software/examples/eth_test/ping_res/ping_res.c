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
#وصف_ڪريو EMAC_DEVICE_ID			240
#وصف_ڪريو ETH_بنياد_REG 0x44000
متطاير بنانشان صحيح* eth_بنياد_reg = ETH_بنياد_REG;
/*
 * Instance of the driver
 */
ساكن XEmacLite EmacLite;



/*
 * Change this parameter to limit the number of ping replies sent by this
 * program.
 */
#وصف_ڪريو MAX_PING_REPLIES	10000	/* Maximum number of ping replies */

#وصف_ڪريو نشر_PACKET	1	/* Broadcast packet */
#وصف_ڪريو MAC_MATCHED_PACKET	2 	/* Dest MAC matched with local MAC */
#وصف_ڪريو IP_ADDR_سائيز		4	/* IP Address size in Bytes */
#وصف_ڪريو ARP_REQUEST 		0x0001	/* ARP Request bits in Rx packet */
#وصف_ڪريو ARP_جواب 		0x0002 	/* ARP status bits indicating reply */
#وصف_ڪريو ARP_PACKET_سائيز 	0x3C    /* ARP packet len 60 Bytes */
#وصف_ڪريو ICMP_PACKET_سائيز 	98 //0x4A    /* ICMP packet length 74 Bytes
					 /* including Src and Dest MAC Address */
#وصف_ڪريو نشر_ADDR 		0xFFFF  /* Broadcast Address */
#وصف_ڪريو CORRECT_CKSUM_قدر	0xFFFF  /* Correct checksum value */
#وصف_ڪريو IDENT_ميدان_قدر	0x9263	/* Identification field (random num) */

/*
 * Definitions for the locations and length of some of the fields in a
 * IP packet. The lengths are defined in Half-Words (2 bytes).
 */
#وصف_ڪريو ETHER_PROTO_TYPE_LEN	1  /* Ethernet protocol Type length  */
#وصف_ڪريو SRC_MAC_ADDR_LOC	3  /* Source MAC address location */
#وصف_ڪريو MAC_ADDR_LEN 		3  /* MAC address length */
#وصف_ڪريو ETHER_PROTO_TYPE_LOC	6  /* Ethernet Proto type location */

#وصف_ڪريو ARP_HW_TYPE_LEN 	1  /* Hardware Type length  */
#وصف_ڪريو ARP_PROTO_TYPE_LEN	1  /* Protocol Type length  */
#وصف_ڪريو ARP_HW_جوڙيو_LEN		1  /* Hardware address length */
#وصف_ڪريو ARP_PROTO_جوڙيو_LEN	1  /* Protocol address length */
#وصف_ڪريو ARP_ZEROS_LEN		9  /* Length to be filled with zeros */
#وصف_ڪريو ARP_REQ_حالت_LOC 	10 /* ARP request location */
#وصف_ڪريو ARP_REQ_SRC_IP_LOC 	14 /* Src IP address location of ARP request */
#وصف_ڪريو ARP_REQ_DEST_IP_LOC_1 	19 /* Destination IP's 1st half word location */
#وصف_ڪريو ARP_REQ_DEST_IP_LOC_2 	20 /* Destination IP's 2nd half word location */

#وصف_ڪريو IP_نسخو_LEN 		1  /* IP Version length  */
#وصف_ڪريو IP_PACKET_LEN 		1  /* IP Packet length field  */
#وصف_ڪريو IP_FRAG_ميدان_LEN	1  /* Fragment field len in ICMP packet */
#وصف_ڪريو IP_TTL_ICM_LEN 		1  /* Time to live and ICM fields length */
#وصف_ڪريو IP_ADDR_LEN 		2  /* Size of IP address in half-words */
#وصف_ڪريو IP_CSUM_LOC_پٺ	5  /* IP checksum location from end of frame */
#وصف_ڪريو IP_HDR_شروعات_LOC 	7  /* IP header start location */
#وصف_ڪريو IP_HDR_LEN 		10 /* IP Header length */
#وصف_ڪريو IP_FRAG_ميدان_LOC 	10 /* Fragment field location */

#وصف_ڪريو ICMP_TYPE_LEN 		1  /* ICMP Type length */
#وصف_ڪريو ICMP_ECHO_ميدان_LEN 	2  /* Echo field length in half-words */
#وصف_ڪريو ICMP_REQ_SRC_IP_LOC 	13 /* Src IP address location of ICMP request */
#وصف_ڪريو ICMP_ECHO_ميدان_LOC 	17 /* Echo field location */
#وصف_ڪريو ICMP_معلومات_شروعات_LOC 	17 /* Data field start location */
#وصف_ڪريو ICMP_معلومات_LEN 		30  //18  /* ICMP data length */
#وصف_ڪريو ICMP_معلومات_LOC 		19 /* ICMP data location including
				      identifier number and sequence number */
#وصف_ڪريو ICMP_معلومات_CSUM_LOC_پٺ 31 //19 
/* Data checksum location from end of
چوکٺو*/
#وصف_ڪريو ICMP_معلومات_ميدان_LEN 	32 //20 /* Data field length */

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

ساكن صحيح Emac_Lite_Ping_جواب_Example(u16 DeviceId);

ساكن فراغ Process_Recv_چوکٺو(XEmacLite *InstancePtr);

ساكن u16 Check_جوڙ_Calculation(u16 *Rx_چوکٺو_Ptr, صحيح شروعات_Loc, صحيح ڊيگهائي);

/************************** Variable Definitions *****************************/

/*
 * Set up a local MAC address.
 */
ساكن u8 LocalMacAddr[XEL_MAC_ADDR_سائيز] =
{
	0x00, 0x00, 0x5E, 0x00, 0xFA, 0xCE
};

/*
 * The IP address was set to 172.16.63.121. User need to set a free IP address
 * based on the network on which this example is to be run.
 */
ساكن u8 LocalIpAddr[IP_ADDR_سائيز] =
{
	192, 168, 1, 25
};

ساكن XEmacLite EmacLiteInstance;	/* Instance of the EmacLite driver */

/*
 * Buffers used for Transmission and Reception of Packets. These are declared as
 * global so that they are not a part of the stack.
 */
ساكن u8 Rx_چوکٺو[XEL_MAX_چوکٺو_سائيز];
ساكن u8 Tx_چوکٺو[XEL_MAX_چوکٺو_سائيز];

/*
 * Variable used to indicate the length of the received frame.
 */
خارجي متطاير u32 Recv_چوکٺو_ڊيگهائي = 0;

/*
 * Variable used to indicate the number of Ping replies sent.
 */
u32 انگ_جو_Ping_Replies;
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
صحيح مکيه()
{
	صحيح حالت;
	arpcount = 0;
	/*
	 * Run the EmacLite Ping reply example.
	 */
	حالت = Emac_Lite_Ping_جواب_Example(EMAC_DEVICE_ID);
	إذا (حالت != XST_SUCCESS) {
		xil_printf("Emaclite ping reply Example Failed\r\n");
		أرجع XST_FAILURE;
	}

	xil_printf("Successfully ran Emaclite ping reply Example\r\n");
	أرجع XST_SUCCESS;
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
صحيح Emac_Lite_Ping_جواب_Example(u16 DeviceId)
{
	صحيح حالت, ڳڻپ = 0;
	XEmacLite *EmacLiteInstPtr = &EmacLiteInstance;
	XEmacLite_Config *ConfigPtr;
	انگ_جو_Ping_Replies = 0;

	/*
	 * Initialize the EmacLite device.
	 */
	ConfigPtr = &XEmac_Lite_Config_جدول;
	إذا (ConfigPtr == عدم) {
		أرجع -1;
	}
	لکو("\n ");

	ConfigPtr->بنياد_پتو = (UINTPTR *) 0X44000;
	ConfigPtr->RxPingPong = XPAR_EMACLITE_0_RX_PING_PONG;
	ConfigPtr->MdioInclude = XPAR_EMACLITE_0_INCLUDE_MDIO;
	ConfigPtr->TxPingPong = XPAR_EMACLITE_0_TX_PING_PONG;
	حالت = XEmacLite_CfgInitialize(EmacLiteInstPtr,
					ConfigPtr,
					ConfigPtr->بنياد_پتو);
	إذا (حالت != 0) {
		أرجع -1;
	}
	
	/*
	 * Set the MAC address.
	 */
	XEmac_Lite_سيٽ_Mac_پتو(EmacLiteInstPtr, LocalMacAddr);
	/*
	 * Empty any existing receive frames.
	 */
	XEmacLite_FlushReceive(EmacLiteInstPtr);

	طالما (1) {

		/*
		 * Wait for a Receive packet.
		 */
		طالما (Recv_چوکٺو_ڊيگهائي == 0) {
			Recv_چوکٺو_ڊيگهائي = XEmacLite_Recv(EmacLiteInstPtr,
								(u8 *)Rx_چوکٺو);
		}
#إذا 1
		لکو("\n Rcv. Frame %x: %x\n", انگ_جو_Ping_Replies, Recv_چوکٺو_ڊيگهائي);
		لكل(صحيح i = 0; i < Recv_چوکٺو_ڊيگهائي; i++)
			لکو("%x ", Rx_چوکٺو[i]);
		لکو("\n");
#جيڪڏهن_پورو			
		/*
		 * Empty any existing receive frames.
		 */
		XEmacLite_FlushReceive(EmacLiteInstPtr);

		/*
		 * Process the Receive frame.
		 */
		Process_Recv_چوکٺو(EmacLiteInstPtr);
		Recv_چوکٺو_ڊيگهائي = 0;

		/*
		 * If the number of ping replies sent is equal to that
		 * specified by the user then exit out of this loop.
		 */
		إذا (انگ_جو_Ping_Replies == MAX_PING_REPLIES) {

			أرجع XST_SUCCESS;
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
ساكن فراغ Process_Recv_چوکٺو(XEmacLite *InstancePtr)
{
	u16 *Rx_چوکٺو_Ptr;
	u16 *Tx_چوکٺو_Ptr;
	u16 *عارضي_Ptr;
	u16 Check_جوڙ;
	u32 ايندڙ_Tx_Buff_بنياد_Addr;
	صحيح اشاريو;
	صحيح PacketType = 0;

	Tx_چوکٺو_Ptr = (u16 *)Tx_چوکٺو;
	Rx_چوکٺو_Ptr = (u16 *)Rx_چوکٺو;

	/*
	 * Determine the next expected Tx buffer address.
	 */
	ايندڙ_Tx_Buff_بنياد_Addr = XEmac_Lite_ايندڙ_Transmit_Addr(InstancePtr);

	/*
	 * Check the packet type.
	 */
	اشاريو = MAC_ADDR_LEN;
	عارضي_Ptr = (u16 *)LocalMacAddr;
	طالما (اشاريو--) {
		إذا (Xil_Ntohs((*(Rx_چوکٺو_Ptr + اشاريو)) == نشر_ADDR) &&
					(PacketType != MAC_MATCHED_PACKET)) {
			PacketType = نشر_PACKET;
		} وإلا إذا (Xil_Ntohs((*(Rx_چوکٺو_Ptr + اشاريو)) == *(عارضي_Ptr + اشاريو)) &&
					(PacketType != نشر_PACKET)) {
			PacketType = MAC_MATCHED_PACKET;
		} وإلا {
			PacketType = 0;
			اكسر;
		}
	}
#إذا 0
	لکو("\n Packet type is %x", PacketType);
#جيڪڏهن_پورو
	/*
	 * Process broadcast packet.
	 */
	إذا (PacketType == نشر_PACKET) {

		/*
		 * Check for an ARP Packet if so generate a reply.
		 */
		إذا (Xil_Ntohs(*(Rx_چوکٺو_Ptr + ETHER_PROTO_TYPE_LOC)) ==
				XEL_ETHER_PROTO_TYPE_ARP) {

			/*
			 * IP address of the local machine.
			 */
			عارضي_Ptr = (u16 *)LocalIpAddr;

			/*
			 * Check destination IP address of the packet with
			 * local IP address.
			 */
			إذا (
			((*(Rx_چوکٺو_Ptr + ARP_REQ_DEST_IP_LOC_1)) == *عارضي_Ptr++) &&
			((*(Rx_چوکٺو_Ptr + ARP_REQ_DEST_IP_LOC_2)) == *عارضي_Ptr++)) {

				/*
				 * Check ARP packet type(request/reply).
				 */
				إذا (Xil_Ntohs(*(Rx_چوکٺو_Ptr + ARP_REQ_حالت_LOC)) ==
								ARP_REQUEST) {

					/*
					 * Add destination MAC address
					 * to the reply packet (i.e) source
					 * address of the received packet.
					 */
					اشاريو = SRC_MAC_ADDR_LOC;
					طالما (اشاريو < (SRC_MAC_ADDR_LOC +
							MAC_ADDR_LEN)) {
						*Tx_چوکٺو_Ptr++ =
							*(Rx_چوکٺو_Ptr + اشاريو);
						اشاريو++;
					}

					/*
					 * Add source (local) MAC address
					 * to the reply packet.
					 */
					اشاريو = 0;
					عارضي_Ptr = (u16 *)LocalMacAddr;
					طالما (اشاريو < MAC_ADDR_LEN) {
						*Tx_چوکٺو_Ptr++ = *عارضي_Ptr++;
						اشاريو++;
					}

					/*
					 * Add Ethernet proto type H/W
					 * type(10/3MBps),H/W address length and
					 * protocol address len (i.e)same as in
					 * the received packet
					 */
					اشاريو = ETHER_PROTO_TYPE_LOC;
					طالما (اشاريو < (ETHER_PROTO_TYPE_LOC +
							ETHER_PROTO_TYPE_LEN +
							ARP_HW_TYPE_LEN +
							ARP_HW_جوڙيو_LEN
							+ ARP_PROTO_جوڙيو_LEN)) {
						*Tx_چوکٺو_Ptr++ =
							*(Rx_چوکٺو_Ptr + اشاريو);
						اشاريو++;
					}

					/*
					 * Add ARP reply status to the reply
					 * packet.
					 */
					*Tx_چوکٺو_Ptr++ = Xil_Htons(ARP_جواب);

					/*
					 * Add local MAC Address
					 * to the reply packet.
					 */
					عارضي_Ptr = (u16 *)LocalMacAddr;
					اشاريو = 0;
					طالما (اشاريو < MAC_ADDR_LEN) {
						*Tx_چوکٺو_Ptr++ = *عارضي_Ptr++;
						اشاريو++;
					}

					/*
					 * Add local IP Address
					 * to the reply packet.
					 */
					عارضي_Ptr = (u16 *)LocalIpAddr;
					اشاريو = 0;
					طالما (اشاريو < IP_ADDR_LEN) {
						*Tx_چوکٺو_Ptr++ = *عارضي_Ptr++ ;
						اشاريو++;
					}

					/*
					 * Add Destination MAC Address
					 * to the reply packet from the received
					 * packet.
					 */
					اشاريو = SRC_MAC_ADDR_LOC;
					طالما (اشاريو < (SRC_MAC_ADDR_LOC +
							MAC_ADDR_LEN)) {
						*Tx_چوکٺو_Ptr++ =
							*(Rx_چوکٺو_Ptr + اشاريو);
						اشاريو++;
					}

					/*
					 * Add Destination IP Address
					 * to the reply packet.
					 */
					اشاريو = ARP_REQ_SRC_IP_LOC;
					طالما (اشاريو < (ARP_REQ_SRC_IP_LOC +
							IP_ADDR_LEN)) {
						*Tx_چوکٺو_Ptr++ =
								*(Rx_چوکٺو_Ptr + اشاريو);
						اشاريو++;
					}

					/*
					 * Fill zeros as per protocol.
					 */
					اشاريو = 0;
					طالما (اشاريو < ARP_ZEROS_LEN) {
						*Tx_چوکٺو_Ptr++ = 0x0000;
						اشاريو++;
					}

					/*
					 * Transmit the Reply Packet.
					 */
					XEmacLite_Send(InstancePtr,
							(u8 *)&Tx_چوکٺو,
							ARP_PACKET_سائيز);
				}
			}
		}
	}

	/*
	 * Process packets whose MAC address is matched.
	 */
	إذا (PacketType == MAC_MATCHED_PACKET) {
//		printf("\n MAC matched packet");
		/*
		 * Check ICMP packet.
		 */
		إذا (Xil_Ntohs(*(Rx_چوکٺو_Ptr + ETHER_PROTO_TYPE_LOC)) ==
						XEL_ETHER_PROTO_TYPE_IP) {
//			printf("\n calculate ip header checksum");
			/*
			 * Check the IP header checksum.
			 */
			Check_جوڙ = Check_جوڙ_Calculation(Rx_چوکٺو_Ptr,
						IP_HDR_شروعات_LOC,
						IP_HDR_LEN);

			/*
			 * Check the Data field checksum.
			 */
//			printf("\n ip checksum:%x", CheckSum);
			إذا (Check_جوڙ == CORRECT_CKSUM_قدر) {
				Check_جوڙ = Check_جوڙ_Calculation(Rx_چوکٺو_Ptr,
						ICMP_معلومات_شروعات_LOC,
						ICMP_معلومات_ميدان_LEN);
#إذا 0
			لکو("\nICMP Rcv Packet: \n");
			لكل(صحيح i = ICMP_معلومات_شروعات_LOC; i <= ICMP_معلومات_ميدان_LEN; i++)
			   لکو("%x ", Rx_چوکٺو_Ptr[i]);
			لکو("\n End of ICMP Rcv Packet");
				
				لکو("\n data checksum:%x", Check_جوڙ);
#جيڪڏهن_پورو
				إذا (Check_جوڙ == CORRECT_CKSUM_قدر) {

					/*
					 * Add destination address
					 * to the reply packet (i.e)source
					 * address of the received packet.
					 */
					اشاريو = SRC_MAC_ADDR_LOC;
					طالما (اشاريو < (SRC_MAC_ADDR_LOC +
							MAC_ADDR_LEN)) {
						*Tx_چوکٺو_Ptr++ =
							*(Rx_چوکٺو_Ptr + اشاريو);
						اشاريو++;
					}

					/*
					 * Add local MAC address
					 * to the reply packet.
					 */
					اشاريو = 0;
					عارضي_Ptr = (u16 *)LocalMacAddr;
					طالما (اشاريو < MAC_ADDR_LEN) {
						*Tx_چوکٺو_Ptr++ = *عارضي_Ptr++;
						اشاريو++;
					}

					/*
					 * Add protocol type
					 * header length and, packet
					 * length(60 Bytes) to the reply packet.
					 */
					اشاريو = ETHER_PROTO_TYPE_LOC;
					طالما (اشاريو < (ETHER_PROTO_TYPE_LOC +
							ETHER_PROTO_TYPE_LEN +
							IP_نسخو_LEN +
							IP_PACKET_LEN)) {
						*Tx_چوکٺو_Ptr++ =
							*(Rx_چوکٺو_Ptr + اشاريو);
						اشاريو++;
					}

					/*
					 * Identification field a random number
					 * which is set to IDENT_FIELD_VALUE.
					 */
					*Tx_چوکٺو_Ptr++ = IDENT_ميدان_قدر;

					/*
					 * Add fragment type, time to live and
					 * ICM field. It is same as in the
					 * received packet.
					 */
					اشاريو = IP_FRAG_ميدان_LOC;
					طالما (اشاريو < (IP_FRAG_ميدان_LOC +
							IP_TTL_ICM_LEN +
							IP_FRAG_ميدان_LEN)) {
						*Tx_چوکٺو_Ptr++ =
							*(Rx_چوکٺو_Ptr + اشاريو);
						اشاريو++;
					}

					/*
					 * Checksum first set to 0 and
					 * added in this field later.
					 */
					*Tx_چوکٺو_Ptr++ = 0x0000;

					/*
					 * Add Source IP address
					 */
					اشاريو = 0;
					عارضي_Ptr = (u16 *)LocalIpAddr;
					طالما (اشاريو < IP_ADDR_LEN) {
						*Tx_چوکٺو_Ptr++ = *عارضي_Ptr++;
						اشاريو++;
					}

					/*
					 * Add Destination IP address.
					 */
					اشاريو = ICMP_REQ_SRC_IP_LOC;
					طالما (اشاريو < (ICMP_REQ_SRC_IP_LOC +
							IP_ADDR_LEN)) {
						*Tx_چوکٺو_Ptr++ =
							*(Rx_چوکٺو_Ptr + اشاريو);
						اشاريو++;
					}

					/*
					 * Calculate checksum, and
					 * add it in the appropriate field.
					 */
					Check_جوڙ = Check_جوڙ_Calculation(
							(u16 *)Tx_چوکٺو,
							IP_HDR_شروعات_LOC,
							IP_HDR_LEN);
					Check_جوڙ = ~Check_جوڙ;
					*(Tx_چوکٺو_Ptr - IP_CSUM_LOC_پٺ) =
								Xil_Htons(Check_جوڙ);

					/*
					 * Echo reply status & checksum.
					 */
					اشاريو = ICMP_ECHO_ميدان_LOC;
					طالما (اشاريو < (ICMP_ECHO_ميدان_LOC +
							ICMP_ECHO_ميدان_LEN)) {
						*Tx_چوکٺو_Ptr++ = 0x0000;
						اشاريو++;
					}

					/*
					 * Add data to buffer which was
					 * received from the packet.
					 */
					اشاريو = ICMP_معلومات_LOC;
					طالما (اشاريو < (ICMP_معلومات_LOC +
							ICMP_معلومات_LEN)) {
						*Tx_چوکٺو_Ptr++ =
								(*(Rx_چوکٺو_Ptr + اشاريو));
						اشاريو++;
					}

					/*
					 * Generate checksum for the data and
					 * add it in the appropriate field.
					 */
					Check_جوڙ = Check_جوڙ_Calculation(
							(u16 *)Tx_چوکٺو,
							ICMP_معلومات_شروعات_LOC,
							ICMP_معلومات_ميدان_LEN);
					Check_جوڙ = ~Check_جوڙ;
					*(Tx_چوکٺو_Ptr - ICMP_معلومات_CSUM_LOC_پٺ)
								= Xil_Htons(Check_جوڙ);

					/*
					 * Transmit the frame.
					 */
#إذا 1
					 لکو("\n%x. ICMP Tx Packet \n", انگ_جو_Ping_Replies);
					 لكل(صحيح i = 0; i < ICMP_PACKET_سائيز; i++)
					 	لکو("%x ", Tx_چوکٺو[i]);
					 لکو("\n End of ICMP Tx Packet");
#جيڪڏهن_پورو					 
					XEmacLite_Send(InstancePtr,
							(u8 *)&Tx_چوکٺو,
							ICMP_PACKET_سائيز);

					/*
					 * Increment the number of
					 * Ping replies sent.
					 */
					انگ_جو_Ping_Replies++;
//					printf("NumOfPingReplies: %x", NumOfPingReplies);

				}
				وإلا
					لکو("\n Data check sum error");
			}
			وإلا
				لکو("\n IP Check sum error");
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
ساكن u16 Check_جوڙ_Calculation(u16 *Rx_چوکٺو_Ptr, صحيح شروعات_Loc, صحيح ڊيگهائي)
{
	u32 جوڙ = 0;
	u16 Check_جوڙ = 0;
	صحيح اشاريو;

	/*
	 * Add all the 16 bit data.
	 */
	اشاريو = شروعات_Loc;
	طالما (اشاريو < (شروعات_Loc + ڊيگهائي)) {
		جوڙ = جوڙ + Xil_Ntohs(*(Rx_چوکٺو_Ptr + اشاريو));
		اشاريو++;
	}

	/*
	 * Add upper 16 bits to lower 16 bits.
	 */
	Check_جوڙ = جوڙ;
	جوڙ = جوڙ >> 16;
	Check_جوڙ = جوڙ + Check_جوڙ;
	أرجع Check_جوڙ;
}
