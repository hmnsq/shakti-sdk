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
#تعریف_کرو EMAC_DEVICE_ID			240
#تعریف_کرو ETH_ادھار_REG 0x44000
متطاير بنانشانی صحيح* eth_ادھار_reg = ETH_ادھار_REG;
/*
 * Instance of the driver
 */
ساكن XEmacLite EmacLite;



/*
 * Change this parameter to limit the number of ping replies sent by this
 * program.
 */
#تعریف_کرو MAX_PING_REPLIES	10000	/* Maximum number of ping replies */

#تعریف_کرو نشر_PACKET	1	/* Broadcast packet */
#تعریف_کرو MAC_MATCHED_PACKET	2 	/* Dest MAC matched with local MAC */
#تعریف_کرو IP_ADDR_ناپ		4	/* IP Address size in Bytes */
#تعریف_کرو ARP_REQUEST 		0x0001	/* ARP Request bits in Rx packet */
#تعریف_کرو ARP_جواب 		0x0002 	/* ARP status bits indicating reply */
#تعریف_کرو ARP_PACKET_ناپ 	0x3C    /* ARP packet len 60 Bytes */
#تعریف_کرو ICMP_PACKET_ناپ 	98 //0x4A    /* ICMP packet length 74 Bytes
					 /* including Src and Dest MAC Address */
#تعریف_کرو نشر_ADDR 		0xFFFF  /* Broadcast Address */
#تعریف_کرو CORRECT_CKSUM_قدر	0xFFFF  /* Correct checksum value */
#تعریف_کرو IDENT_میدان_قدر	0x9263	/* Identification field (random num) */

/*
 * Definitions for the locations and length of some of the fields in a
 * IP packet. The lengths are defined in Half-Words (2 bytes).
 */
#تعریف_کرو ETHER_PROTO_TYPE_LEN	1  /* Ethernet protocol Type length  */
#تعریف_کرو SRC_MAC_ADDR_LOC	3  /* Source MAC address location */
#تعریف_کرو MAC_ADDR_LEN 		3  /* MAC address length */
#تعریف_کرو ETHER_PROTO_TYPE_LOC	6  /* Ethernet Proto type location */

#تعریف_کرو ARP_HW_TYPE_LEN 	1  /* Hardware Type length  */
#تعریف_کرو ARP_PROTO_TYPE_LEN	1  /* Protocol Type length  */
#تعریف_کرو ARP_HW_جوڑو_LEN		1  /* Hardware address length */
#تعریف_کرو ARP_PROTO_جوڑو_LEN	1  /* Protocol address length */
#تعریف_کرو ARP_ZEROS_LEN		9  /* Length to be filled with zeros */
#تعریف_کرو ARP_REQ_حالت_LOC 	10 /* ARP request location */
#تعریف_کرو ARP_REQ_SRC_IP_LOC 	14 /* Src IP address location of ARP request */
#تعریف_کرو ARP_REQ_DEST_IP_LOC_1 	19 /* Destination IP's 1st half word location */
#تعریف_کرو ARP_REQ_DEST_IP_LOC_2 	20 /* Destination IP's 2nd half word location */

#تعریف_کرو IP_نسخہ_LEN 		1  /* IP Version length  */
#تعریف_کرو IP_PACKET_LEN 		1  /* IP Packet length field  */
#تعریف_کرو IP_FRAG_میدان_LEN	1  /* Fragment field len in ICMP packet */
#تعریف_کرو IP_TTL_ICM_LEN 		1  /* Time to live and ICM fields length */
#تعریف_کرو IP_ADDR_LEN 		2  /* Size of IP address in half-words */
#تعریف_کرو IP_CSUM_LOC_پٹھ	5  /* IP checksum location from end of frame */
#تعریف_کرو IP_HDR_شروع_LOC 	7  /* IP header start location */
#تعریف_کرو IP_HDR_LEN 		10 /* IP Header length */
#تعریف_کرو IP_FRAG_میدان_LOC 	10 /* Fragment field location */

#تعریف_کرو ICMP_TYPE_LEN 		1  /* ICMP Type length */
#تعریف_کرو ICMP_ECHO_میدان_LEN 	2  /* Echo field length in half-words */
#تعریف_کرو ICMP_REQ_SRC_IP_LOC 	13 /* Src IP address location of ICMP request */
#تعریف_کرو ICMP_ECHO_میدان_LOC 	17 /* Echo field location */
#تعریف_کرو ICMP_انکڑے_شروع_LOC 	17 /* Data field start location */
#تعریف_کرو ICMP_انکڑے_LEN 		30  //18  /* ICMP data length */
#تعریف_کرو ICMP_انکڑے_LOC 		19 /* ICMP data location including
				      identifier number and sequence number */
#تعریف_کرو ICMP_انکڑے_CSUM_LOC_پٹھ 31 //19 
/* Data checksum location from end of
چوکھٹا*/
#تعریف_کرو ICMP_انکڑے_میدان_LEN 	32 //20 /* Data field length */

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

ساكن صحيح Emac_Lite_Ping_جواب_Example(u16 DeviceId);

ساكن فراغ Process_Recv_چوکھٹا(XEmacLite *InstancePtr);

ساكن u16 Check_جوڑ_Calculation(u16 *Rx_چوکھٹا_Ptr, صحيح شروع_Loc, صحيح لمائی);

/************************** Variable Definitions *****************************/

/*
 * Set up a local MAC address.
 */
ساكن u8 LocalMacAddr[XEL_MAC_ADDR_ناپ] =
{
	0x00, 0x00, 0x5E, 0x00, 0xFA, 0xCE
};

/*
 * The IP address was set to 172.16.63.121. User need to set a free IP address
 * based on the network on which this example is to be run.
 */
ساكن u8 LocalIpAddr[IP_ADDR_ناپ] =
{
	192, 168, 1, 25
};

ساكن XEmacLite EmacLiteInstance;	/* Instance of the EmacLite driver */

/*
 * Buffers used for Transmission and Reception of Packets. These are declared as
 * global so that they are not a part of the stack.
 */
ساكن u8 Rx_چوکھٹا[XEL_MAX_چوکھٹا_ناپ];
ساكن u8 Tx_چوکھٹا[XEL_MAX_چوکھٹا_ناپ];

/*
 * Variable used to indicate the length of the received frame.
 */
خارجي متطاير u32 Recv_چوکھٹا_لمائی = 0;

/*
 * Variable used to indicate the number of Ping replies sent.
 */
u32 عدد_دا_Ping_Replies;
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
صحيح مکھ()
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
	صحيح حالت, گنتی = 0;
	XEmacLite *EmacLiteInstPtr = &EmacLiteInstance;
	XEmacLite_Config *ConfigPtr;
	عدد_دا_Ping_Replies = 0;

	/*
	 * Initialize the EmacLite device.
	 */
	ConfigPtr = &XEmac_Lite_Config_جدول;
	إذا (ConfigPtr == عدم) {
		أرجع -1;
	}
	لکھو("\n ");

	ConfigPtr->ادھار_پتہ = (UINTPTR *) 0X44000;
	ConfigPtr->RxPingPong = XPAR_EMACLITE_0_RX_PING_PONG;
	ConfigPtr->MdioInclude = XPAR_EMACLITE_0_INCLUDE_MDIO;
	ConfigPtr->TxPingPong = XPAR_EMACLITE_0_TX_PING_PONG;
	حالت = XEmacLite_CfgInitialize(EmacLiteInstPtr,
					ConfigPtr,
					ConfigPtr->ادھار_پتہ);
	إذا (حالت != 0) {
		أرجع -1;
	}
	
	/*
	 * Set the MAC address.
	 */
	XEmac_Lite_سیٹ_Mac_پتہ(EmacLiteInstPtr, LocalMacAddr);
	/*
	 * Empty any existing receive frames.
	 */
	XEmacLite_FlushReceive(EmacLiteInstPtr);

	طالما (1) {

		/*
		 * Wait for a Receive packet.
		 */
		طالما (Recv_چوکھٹا_لمائی == 0) {
			Recv_چوکھٹا_لمائی = XEmacLite_Recv(EmacLiteInstPtr,
								(u8 *)Rx_چوکھٹا);
		}
#إذا 1
		لکھو("\n Rcv. Frame %x: %x\n", عدد_دا_Ping_Replies, Recv_چوکھٹا_لمائی);
		لكل(صحيح i = 0; i < Recv_چوکھٹا_لمائی; i++)
			لکھو("%x ", Rx_چوکھٹا[i]);
		لکھو("\n");
#جے_انت			
		/*
		 * Empty any existing receive frames.
		 */
		XEmacLite_FlushReceive(EmacLiteInstPtr);

		/*
		 * Process the Receive frame.
		 */
		Process_Recv_چوکھٹا(EmacLiteInstPtr);
		Recv_چوکھٹا_لمائی = 0;

		/*
		 * If the number of ping replies sent is equal to that
		 * specified by the user then exit out of this loop.
		 */
		إذا (عدد_دا_Ping_Replies == MAX_PING_REPLIES) {

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
ساكن فراغ Process_Recv_چوکھٹا(XEmacLite *InstancePtr)
{
	u16 *Rx_چوکھٹا_Ptr;
	u16 *Tx_چوکھٹا_Ptr;
	u16 *عارضی_Ptr;
	u16 Check_جوڑ;
	u32 اگلا_Tx_Buff_ادھار_Addr;
	صحيح اشاریہ;
	صحيح PacketType = 0;

	Tx_چوکھٹا_Ptr = (u16 *)Tx_چوکھٹا;
	Rx_چوکھٹا_Ptr = (u16 *)Rx_چوکھٹا;

	/*
	 * Determine the next expected Tx buffer address.
	 */
	اگلا_Tx_Buff_ادھار_Addr = XEmac_Lite_اگلا_Transmit_Addr(InstancePtr);

	/*
	 * Check the packet type.
	 */
	اشاریہ = MAC_ADDR_LEN;
	عارضی_Ptr = (u16 *)LocalMacAddr;
	طالما (اشاریہ--) {
		إذا (Xil_Ntohs((*(Rx_چوکھٹا_Ptr + اشاریہ)) == نشر_ADDR) &&
					(PacketType != MAC_MATCHED_PACKET)) {
			PacketType = نشر_PACKET;
		} وإلا إذا (Xil_Ntohs((*(Rx_چوکھٹا_Ptr + اشاریہ)) == *(عارضی_Ptr + اشاریہ)) &&
					(PacketType != نشر_PACKET)) {
			PacketType = MAC_MATCHED_PACKET;
		} وإلا {
			PacketType = 0;
			اكسر;
		}
	}
#إذا 0
	لکھو("\n Packet type is %x", PacketType);
#جے_انت
	/*
	 * Process broadcast packet.
	 */
	إذا (PacketType == نشر_PACKET) {

		/*
		 * Check for an ARP Packet if so generate a reply.
		 */
		إذا (Xil_Ntohs(*(Rx_چوکھٹا_Ptr + ETHER_PROTO_TYPE_LOC)) ==
				XEL_ETHER_PROTO_TYPE_ARP) {

			/*
			 * IP address of the local machine.
			 */
			عارضی_Ptr = (u16 *)LocalIpAddr;

			/*
			 * Check destination IP address of the packet with
			 * local IP address.
			 */
			إذا (
			((*(Rx_چوکھٹا_Ptr + ARP_REQ_DEST_IP_LOC_1)) == *عارضی_Ptr++) &&
			((*(Rx_چوکھٹا_Ptr + ARP_REQ_DEST_IP_LOC_2)) == *عارضی_Ptr++)) {

				/*
				 * Check ARP packet type(request/reply).
				 */
				إذا (Xil_Ntohs(*(Rx_چوکھٹا_Ptr + ARP_REQ_حالت_LOC)) ==
								ARP_REQUEST) {

					/*
					 * Add destination MAC address
					 * to the reply packet (i.e) source
					 * address of the received packet.
					 */
					اشاریہ = SRC_MAC_ADDR_LOC;
					طالما (اشاریہ < (SRC_MAC_ADDR_LOC +
							MAC_ADDR_LEN)) {
						*Tx_چوکھٹا_Ptr++ =
							*(Rx_چوکھٹا_Ptr + اشاریہ);
						اشاریہ++;
					}

					/*
					 * Add source (local) MAC address
					 * to the reply packet.
					 */
					اشاریہ = 0;
					عارضی_Ptr = (u16 *)LocalMacAddr;
					طالما (اشاریہ < MAC_ADDR_LEN) {
						*Tx_چوکھٹا_Ptr++ = *عارضی_Ptr++;
						اشاریہ++;
					}

					/*
					 * Add Ethernet proto type H/W
					 * type(10/3MBps),H/W address length and
					 * protocol address len (i.e)same as in
					 * the received packet
					 */
					اشاریہ = ETHER_PROTO_TYPE_LOC;
					طالما (اشاریہ < (ETHER_PROTO_TYPE_LOC +
							ETHER_PROTO_TYPE_LEN +
							ARP_HW_TYPE_LEN +
							ARP_HW_جوڑو_LEN
							+ ARP_PROTO_جوڑو_LEN)) {
						*Tx_چوکھٹا_Ptr++ =
							*(Rx_چوکھٹا_Ptr + اشاریہ);
						اشاریہ++;
					}

					/*
					 * Add ARP reply status to the reply
					 * packet.
					 */
					*Tx_چوکھٹا_Ptr++ = Xil_Htons(ARP_جواب);

					/*
					 * Add local MAC Address
					 * to the reply packet.
					 */
					عارضی_Ptr = (u16 *)LocalMacAddr;
					اشاریہ = 0;
					طالما (اشاریہ < MAC_ADDR_LEN) {
						*Tx_چوکھٹا_Ptr++ = *عارضی_Ptr++;
						اشاریہ++;
					}

					/*
					 * Add local IP Address
					 * to the reply packet.
					 */
					عارضی_Ptr = (u16 *)LocalIpAddr;
					اشاریہ = 0;
					طالما (اشاریہ < IP_ADDR_LEN) {
						*Tx_چوکھٹا_Ptr++ = *عارضی_Ptr++ ;
						اشاریہ++;
					}

					/*
					 * Add Destination MAC Address
					 * to the reply packet from the received
					 * packet.
					 */
					اشاریہ = SRC_MAC_ADDR_LOC;
					طالما (اشاریہ < (SRC_MAC_ADDR_LOC +
							MAC_ADDR_LEN)) {
						*Tx_چوکھٹا_Ptr++ =
							*(Rx_چوکھٹا_Ptr + اشاریہ);
						اشاریہ++;
					}

					/*
					 * Add Destination IP Address
					 * to the reply packet.
					 */
					اشاریہ = ARP_REQ_SRC_IP_LOC;
					طالما (اشاریہ < (ARP_REQ_SRC_IP_LOC +
							IP_ADDR_LEN)) {
						*Tx_چوکھٹا_Ptr++ =
								*(Rx_چوکھٹا_Ptr + اشاریہ);
						اشاریہ++;
					}

					/*
					 * Fill zeros as per protocol.
					 */
					اشاریہ = 0;
					طالما (اشاریہ < ARP_ZEROS_LEN) {
						*Tx_چوکھٹا_Ptr++ = 0x0000;
						اشاریہ++;
					}

					/*
					 * Transmit the Reply Packet.
					 */
					XEmacLite_Send(InstancePtr,
							(u8 *)&Tx_چوکھٹا,
							ARP_PACKET_ناپ);
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
		إذا (Xil_Ntohs(*(Rx_چوکھٹا_Ptr + ETHER_PROTO_TYPE_LOC)) ==
						XEL_ETHER_PROTO_TYPE_IP) {
//			printf("\n calculate ip header checksum");
			/*
			 * Check the IP header checksum.
			 */
			Check_جوڑ = Check_جوڑ_Calculation(Rx_چوکھٹا_Ptr,
						IP_HDR_شروع_LOC,
						IP_HDR_LEN);

			/*
			 * Check the Data field checksum.
			 */
//			printf("\n ip checksum:%x", CheckSum);
			إذا (Check_جوڑ == CORRECT_CKSUM_قدر) {
				Check_جوڑ = Check_جوڑ_Calculation(Rx_چوکھٹا_Ptr,
						ICMP_انکڑے_شروع_LOC,
						ICMP_انکڑے_میدان_LEN);
#إذا 0
			لکھو("\nICMP Rcv Packet: \n");
			لكل(صحيح i = ICMP_انکڑے_شروع_LOC; i <= ICMP_انکڑے_میدان_LEN; i++)
			   لکھو("%x ", Rx_چوکھٹا_Ptr[i]);
			لکھو("\n End of ICMP Rcv Packet");
				
				لکھو("\n data checksum:%x", Check_جوڑ);
#جے_انت
				إذا (Check_جوڑ == CORRECT_CKSUM_قدر) {

					/*
					 * Add destination address
					 * to the reply packet (i.e)source
					 * address of the received packet.
					 */
					اشاریہ = SRC_MAC_ADDR_LOC;
					طالما (اشاریہ < (SRC_MAC_ADDR_LOC +
							MAC_ADDR_LEN)) {
						*Tx_چوکھٹا_Ptr++ =
							*(Rx_چوکھٹا_Ptr + اشاریہ);
						اشاریہ++;
					}

					/*
					 * Add local MAC address
					 * to the reply packet.
					 */
					اشاریہ = 0;
					عارضی_Ptr = (u16 *)LocalMacAddr;
					طالما (اشاریہ < MAC_ADDR_LEN) {
						*Tx_چوکھٹا_Ptr++ = *عارضی_Ptr++;
						اشاریہ++;
					}

					/*
					 * Add protocol type
					 * header length and, packet
					 * length(60 Bytes) to the reply packet.
					 */
					اشاریہ = ETHER_PROTO_TYPE_LOC;
					طالما (اشاریہ < (ETHER_PROTO_TYPE_LOC +
							ETHER_PROTO_TYPE_LEN +
							IP_نسخہ_LEN +
							IP_PACKET_LEN)) {
						*Tx_چوکھٹا_Ptr++ =
							*(Rx_چوکھٹا_Ptr + اشاریہ);
						اشاریہ++;
					}

					/*
					 * Identification field a random number
					 * which is set to IDENT_FIELD_VALUE.
					 */
					*Tx_چوکھٹا_Ptr++ = IDENT_میدان_قدر;

					/*
					 * Add fragment type, time to live and
					 * ICM field. It is same as in the
					 * received packet.
					 */
					اشاریہ = IP_FRAG_میدان_LOC;
					طالما (اشاریہ < (IP_FRAG_میدان_LOC +
							IP_TTL_ICM_LEN +
							IP_FRAG_میدان_LEN)) {
						*Tx_چوکھٹا_Ptr++ =
							*(Rx_چوکھٹا_Ptr + اشاریہ);
						اشاریہ++;
					}

					/*
					 * Checksum first set to 0 and
					 * added in this field later.
					 */
					*Tx_چوکھٹا_Ptr++ = 0x0000;

					/*
					 * Add Source IP address
					 */
					اشاریہ = 0;
					عارضی_Ptr = (u16 *)LocalIpAddr;
					طالما (اشاریہ < IP_ADDR_LEN) {
						*Tx_چوکھٹا_Ptr++ = *عارضی_Ptr++;
						اشاریہ++;
					}

					/*
					 * Add Destination IP address.
					 */
					اشاریہ = ICMP_REQ_SRC_IP_LOC;
					طالما (اشاریہ < (ICMP_REQ_SRC_IP_LOC +
							IP_ADDR_LEN)) {
						*Tx_چوکھٹا_Ptr++ =
							*(Rx_چوکھٹا_Ptr + اشاریہ);
						اشاریہ++;
					}

					/*
					 * Calculate checksum, and
					 * add it in the appropriate field.
					 */
					Check_جوڑ = Check_جوڑ_Calculation(
							(u16 *)Tx_چوکھٹا,
							IP_HDR_شروع_LOC,
							IP_HDR_LEN);
					Check_جوڑ = ~Check_جوڑ;
					*(Tx_چوکھٹا_Ptr - IP_CSUM_LOC_پٹھ) =
								Xil_Htons(Check_جوڑ);

					/*
					 * Echo reply status & checksum.
					 */
					اشاریہ = ICMP_ECHO_میدان_LOC;
					طالما (اشاریہ < (ICMP_ECHO_میدان_LOC +
							ICMP_ECHO_میدان_LEN)) {
						*Tx_چوکھٹا_Ptr++ = 0x0000;
						اشاریہ++;
					}

					/*
					 * Add data to buffer which was
					 * received from the packet.
					 */
					اشاریہ = ICMP_انکڑے_LOC;
					طالما (اشاریہ < (ICMP_انکڑے_LOC +
							ICMP_انکڑے_LEN)) {
						*Tx_چوکھٹا_Ptr++ =
								(*(Rx_چوکھٹا_Ptr + اشاریہ));
						اشاریہ++;
					}

					/*
					 * Generate checksum for the data and
					 * add it in the appropriate field.
					 */
					Check_جوڑ = Check_جوڑ_Calculation(
							(u16 *)Tx_چوکھٹا,
							ICMP_انکڑے_شروع_LOC,
							ICMP_انکڑے_میدان_LEN);
					Check_جوڑ = ~Check_جوڑ;
					*(Tx_چوکھٹا_Ptr - ICMP_انکڑے_CSUM_LOC_پٹھ)
								= Xil_Htons(Check_جوڑ);

					/*
					 * Transmit the frame.
					 */
#إذا 1
					 لکھو("\n%x. ICMP Tx Packet \n", عدد_دا_Ping_Replies);
					 لكل(صحيح i = 0; i < ICMP_PACKET_ناپ; i++)
					 	لکھو("%x ", Tx_چوکھٹا[i]);
					 لکھو("\n End of ICMP Tx Packet");
#جے_انت					 
					XEmacLite_Send(InstancePtr,
							(u8 *)&Tx_چوکھٹا,
							ICMP_PACKET_ناپ);

					/*
					 * Increment the number of
					 * Ping replies sent.
					 */
					عدد_دا_Ping_Replies++;
//					printf("NumOfPingReplies: %x", NumOfPingReplies);

				}
				وإلا
					لکھو("\n Data check sum error");
			}
			وإلا
				لکھو("\n IP Check sum error");
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
ساكن u16 Check_جوڑ_Calculation(u16 *Rx_چوکھٹا_Ptr, صحيح شروع_Loc, صحيح لمائی)
{
	u32 جوڑ = 0;
	u16 Check_جوڑ = 0;
	صحيح اشاریہ;

	/*
	 * Add all the 16 bit data.
	 */
	اشاریہ = شروع_Loc;
	طالما (اشاریہ < (شروع_Loc + لمائی)) {
		جوڑ = جوڑ + Xil_Ntohs(*(Rx_چوکھٹا_Ptr + اشاریہ));
		اشاریہ++;
	}

	/*
	 * Add upper 16 bits to lower 16 bits.
	 */
	Check_جوڑ = جوڑ;
	جوڑ = جوڑ >> 16;
	Check_جوڑ = جوڑ + Check_جوڑ;
	أرجع Check_جوڑ;
}
