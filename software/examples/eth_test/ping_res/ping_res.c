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
#تعریف_کن EMAC_DEVICE_ID			240
#تعریف_کن ETH_پایه_REG 0x44000
متطاير بیعلامت صحيح* eth_پایه_reg = ETH_پایه_REG;
/*
 * Instance of the driver
 */
ساكن XEmacLite EmacLite;



/*
 * Change this parameter to limit the number of ping replies sent by this
 * program.
 */
#تعریف_کن MAX_PING_REPLIES	10000	/* Maximum number of ping replies */

#تعریف_کن پخش_PACKET	1	/* Broadcast packet */
#تعریف_کن MAC_MATCHED_PACKET	2 	/* Dest MAC matched with local MAC */
#تعریف_کن IP_ADDR_اندازه		4	/* IP Address size in Bytes */
#تعریف_کن ARP_REQUEST 		0x0001	/* ARP Request bits in Rx packet */
#تعریف_کن ARP_پاسخ 		0x0002 	/* ARP status bits indicating reply */
#تعریف_کن ARP_PACKET_اندازه 	0x3C    /* ARP packet len 60 Bytes */
#تعریف_کن ICMP_PACKET_اندازه 	98 //0x4A    /* ICMP packet length 74 Bytes
					 /* including Src and Dest MAC Address */
#تعریف_کن پخش_ADDR 		0xFFFF  /* Broadcast Address */
#تعریف_کن CORRECT_CKSUM_مقدار	0xFFFF  /* Correct checksum value */
#تعریف_کن IDENT_فیلد_مقدار	0x9263	/* Identification field (random num) */

/*
 * Definitions for the locations and length of some of the fields in a
 * IP packet. The lengths are defined in Half-Words (2 bytes).
 */
#تعریف_کن ETHER_PROTO_TYPE_LEN	1  /* Ethernet protocol Type length  */
#تعریف_کن SRC_MAC_ADDR_LOC	3  /* Source MAC address location */
#تعریف_کن MAC_ADDR_LEN 		3  /* MAC address length */
#تعریف_کن ETHER_PROTO_TYPE_LOC	6  /* Ethernet Proto type location */

#تعریف_کن ARP_HW_TYPE_LEN 	1  /* Hardware Type length  */
#تعریف_کن ARP_PROTO_TYPE_LEN	1  /* Protocol Type length  */
#تعریف_کن ARP_HW_جمع_کن_LEN		1  /* Hardware address length */
#تعریف_کن ARP_PROTO_جمع_کن_LEN	1  /* Protocol address length */
#تعریف_کن ARP_ZEROS_LEN		9  /* Length to be filled with zeros */
#تعریف_کن ARP_REQ_وضعیت_LOC 	10 /* ARP request location */
#تعریف_کن ARP_REQ_SRC_IP_LOC 	14 /* Src IP address location of ARP request */
#تعریف_کن ARP_REQ_DEST_IP_LOC_1 	19 /* Destination IP's 1st half word location */
#تعریف_کن ARP_REQ_DEST_IP_LOC_2 	20 /* Destination IP's 2nd half word location */

#تعریف_کن IP_نسخه_LEN 		1  /* IP Version length  */
#تعریف_کن IP_PACKET_LEN 		1  /* IP Packet length field  */
#تعریف_کن IP_FRAG_فیلد_LEN	1  /* Fragment field len in ICMP packet */
#تعریف_کن IP_TTL_ICM_LEN 		1  /* Time to live and ICM fields length */
#تعریف_کن IP_ADDR_LEN 		2  /* Size of IP address in half-words */
#تعریف_کن IP_CSUM_LOC_پشت	5  /* IP checksum location from end of frame */
#تعریف_کن IP_HDR_شروع_LOC 	7  /* IP header start location */
#تعریف_کن IP_HDR_LEN 		10 /* IP Header length */
#تعریف_کن IP_FRAG_فیلد_LOC 	10 /* Fragment field location */

#تعریف_کن ICMP_TYPE_LEN 		1  /* ICMP Type length */
#تعریف_کن ICMP_ECHO_فیلد_LEN 	2  /* Echo field length in half-words */
#تعریف_کن ICMP_REQ_SRC_IP_LOC 	13 /* Src IP address location of ICMP request */
#تعریف_کن ICMP_ECHO_فیلد_LOC 	17 /* Echo field location */
#تعریف_کن ICMP_داده_شروع_LOC 	17 /* Data field start location */
#تعریف_کن ICMP_داده_LEN 		30  //18  /* ICMP data length */
#تعریف_کن ICMP_داده_LOC 		19 /* ICMP data location including
				      identifier number and sequence number */
#تعریف_کن ICMP_داده_CSUM_LOC_پشت 31 //19 
/* Data checksum location from end of
قاب*/
#تعریف_کن ICMP_داده_فیلد_LEN 	32 //20 /* Data field length */

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

ساكن صحيح Emac_Lite_Ping_پاسخ_Example(u16 DeviceId);

ساكن فراغ Process_Recv_قاب(XEmacLite *InstancePtr);

ساكن u16 Check_جمع_Calculation(u16 *Rx_قاب_Ptr, صحيح شروع_Loc, صحيح درازی);

/************************** Variable Definitions *****************************/

/*
 * Set up a local MAC address.
 */
ساكن u8 LocalMacAddr[XEL_MAC_ADDR_اندازه] =
{
	0x00, 0x00, 0x5E, 0x00, 0xFA, 0xCE
};

/*
 * The IP address was set to 172.16.63.121. User need to set a free IP address
 * based on the network on which this example is to be run.
 */
ساكن u8 LocalIpAddr[IP_ADDR_اندازه] =
{
	192, 168, 1, 25
};

ساكن XEmacLite EmacLiteInstance;	/* Instance of the EmacLite driver */

/*
 * Buffers used for Transmission and Reception of Packets. These are declared as
 * global so that they are not a part of the stack.
 */
ساكن u8 Rx_قاب[XEL_MAX_قاب_اندازه];
ساكن u8 Tx_قاب[XEL_MAX_قاب_اندازه];

/*
 * Variable used to indicate the length of the received frame.
 */
خارجي متطاير u32 Recv_قاب_درازی = 0;

/*
 * Variable used to indicate the number of Ping replies sent.
 */
u32 رقم_از_Ping_Replies;
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
صحيح اصلی()
{
	صحيح وضعیت;
	arpcount = 0;
	/*
	 * Run the EmacLite Ping reply example.
	 */
	وضعیت = Emac_Lite_Ping_پاسخ_Example(EMAC_DEVICE_ID);
	إذا (وضعیت != XST_SUCCESS) {
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
صحيح Emac_Lite_Ping_پاسخ_Example(u16 DeviceId)
{
	صحيح وضعیت, شمار = 0;
	XEmacLite *EmacLiteInstPtr = &EmacLiteInstance;
	XEmacLite_Config *ConfigPtr;
	رقم_از_Ping_Replies = 0;

	/*
	 * Initialize the EmacLite device.
	 */
	ConfigPtr = &XEmac_Lite_Config_جدول;
	إذا (ConfigPtr == عدم) {
		أرجع -1;
	}
	چاپ_کن("\n ");

	ConfigPtr->پایه_آدرس = (UINTPTR *) 0X44000;
	ConfigPtr->RxPingPong = XPAR_EMACLITE_0_RX_PING_PONG;
	ConfigPtr->MdioInclude = XPAR_EMACLITE_0_INCLUDE_MDIO;
	ConfigPtr->TxPingPong = XPAR_EMACLITE_0_TX_PING_PONG;
	وضعیت = XEmacLite_CfgInitialize(EmacLiteInstPtr,
					ConfigPtr,
					ConfigPtr->پایه_آدرس);
	إذا (وضعیت != 0) {
		أرجع -1;
	}
	
	/*
	 * Set the MAC address.
	 */
	XEmac_Lite_مجموعه_Mac_آدرس(EmacLiteInstPtr, LocalMacAddr);
	/*
	 * Empty any existing receive frames.
	 */
	XEmacLite_FlushReceive(EmacLiteInstPtr);

	طالما (1) {

		/*
		 * Wait for a Receive packet.
		 */
		طالما (Recv_قاب_درازی == 0) {
			Recv_قاب_درازی = XEmacLite_Recv(EmacLiteInstPtr,
								(u8 *)Rx_قاب);
		}
#إذا 1
		چاپ_کن("\n Rcv. Frame %x: %x\n", رقم_از_Ping_Replies, Recv_قاب_درازی);
		لكل(صحيح i = 0; i < Recv_قاب_درازی; i++)
			چاپ_کن("%x ", Rx_قاب[i]);
		چاپ_کن("\n");
#پایان_اگر			
		/*
		 * Empty any existing receive frames.
		 */
		XEmacLite_FlushReceive(EmacLiteInstPtr);

		/*
		 * Process the Receive frame.
		 */
		Process_Recv_قاب(EmacLiteInstPtr);
		Recv_قاب_درازی = 0;

		/*
		 * If the number of ping replies sent is equal to that
		 * specified by the user then exit out of this loop.
		 */
		إذا (رقم_از_Ping_Replies == MAX_PING_REPLIES) {

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
ساكن فراغ Process_Recv_قاب(XEmacLite *InstancePtr)
{
	u16 *Rx_قاب_Ptr;
	u16 *Tx_قاب_Ptr;
	u16 *موقت_Ptr;
	u16 Check_جمع;
	u32 بعدی_Tx_Buff_پایه_Addr;
	صحيح شاخص;
	صحيح PacketType = 0;

	Tx_قاب_Ptr = (u16 *)Tx_قاب;
	Rx_قاب_Ptr = (u16 *)Rx_قاب;

	/*
	 * Determine the next expected Tx buffer address.
	 */
	بعدی_Tx_Buff_پایه_Addr = XEmac_Lite_بعدی_Transmit_Addr(InstancePtr);

	/*
	 * Check the packet type.
	 */
	شاخص = MAC_ADDR_LEN;
	موقت_Ptr = (u16 *)LocalMacAddr;
	طالما (شاخص--) {
		إذا (Xil_Ntohs((*(Rx_قاب_Ptr + شاخص)) == پخش_ADDR) &&
					(PacketType != MAC_MATCHED_PACKET)) {
			PacketType = پخش_PACKET;
		} وإلا إذا (Xil_Ntohs((*(Rx_قاب_Ptr + شاخص)) == *(موقت_Ptr + شاخص)) &&
					(PacketType != پخش_PACKET)) {
			PacketType = MAC_MATCHED_PACKET;
		} وإلا {
			PacketType = 0;
			اكسر;
		}
	}
#إذا 0
	چاپ_کن("\n Packet type is %x", PacketType);
#پایان_اگر
	/*
	 * Process broadcast packet.
	 */
	إذا (PacketType == پخش_PACKET) {

		/*
		 * Check for an ARP Packet if so generate a reply.
		 */
		إذا (Xil_Ntohs(*(Rx_قاب_Ptr + ETHER_PROTO_TYPE_LOC)) ==
				XEL_ETHER_PROTO_TYPE_ARP) {

			/*
			 * IP address of the local machine.
			 */
			موقت_Ptr = (u16 *)LocalIpAddr;

			/*
			 * Check destination IP address of the packet with
			 * local IP address.
			 */
			إذا (
			((*(Rx_قاب_Ptr + ARP_REQ_DEST_IP_LOC_1)) == *موقت_Ptr++) &&
			((*(Rx_قاب_Ptr + ARP_REQ_DEST_IP_LOC_2)) == *موقت_Ptr++)) {

				/*
				 * Check ARP packet type(request/reply).
				 */
				إذا (Xil_Ntohs(*(Rx_قاب_Ptr + ARP_REQ_وضعیت_LOC)) ==
								ARP_REQUEST) {

					/*
					 * Add destination MAC address
					 * to the reply packet (i.e) source
					 * address of the received packet.
					 */
					شاخص = SRC_MAC_ADDR_LOC;
					طالما (شاخص < (SRC_MAC_ADDR_LOC +
							MAC_ADDR_LEN)) {
						*Tx_قاب_Ptr++ =
							*(Rx_قاب_Ptr + شاخص);
						شاخص++;
					}

					/*
					 * Add source (local) MAC address
					 * to the reply packet.
					 */
					شاخص = 0;
					موقت_Ptr = (u16 *)LocalMacAddr;
					طالما (شاخص < MAC_ADDR_LEN) {
						*Tx_قاب_Ptr++ = *موقت_Ptr++;
						شاخص++;
					}

					/*
					 * Add Ethernet proto type H/W
					 * type(10/3MBps),H/W address length and
					 * protocol address len (i.e)same as in
					 * the received packet
					 */
					شاخص = ETHER_PROTO_TYPE_LOC;
					طالما (شاخص < (ETHER_PROTO_TYPE_LOC +
							ETHER_PROTO_TYPE_LEN +
							ARP_HW_TYPE_LEN +
							ARP_HW_جمع_کن_LEN
							+ ARP_PROTO_جمع_کن_LEN)) {
						*Tx_قاب_Ptr++ =
							*(Rx_قاب_Ptr + شاخص);
						شاخص++;
					}

					/*
					 * Add ARP reply status to the reply
					 * packet.
					 */
					*Tx_قاب_Ptr++ = Xil_Htons(ARP_پاسخ);

					/*
					 * Add local MAC Address
					 * to the reply packet.
					 */
					موقت_Ptr = (u16 *)LocalMacAddr;
					شاخص = 0;
					طالما (شاخص < MAC_ADDR_LEN) {
						*Tx_قاب_Ptr++ = *موقت_Ptr++;
						شاخص++;
					}

					/*
					 * Add local IP Address
					 * to the reply packet.
					 */
					موقت_Ptr = (u16 *)LocalIpAddr;
					شاخص = 0;
					طالما (شاخص < IP_ADDR_LEN) {
						*Tx_قاب_Ptr++ = *موقت_Ptr++ ;
						شاخص++;
					}

					/*
					 * Add Destination MAC Address
					 * to the reply packet from the received
					 * packet.
					 */
					شاخص = SRC_MAC_ADDR_LOC;
					طالما (شاخص < (SRC_MAC_ADDR_LOC +
							MAC_ADDR_LEN)) {
						*Tx_قاب_Ptr++ =
							*(Rx_قاب_Ptr + شاخص);
						شاخص++;
					}

					/*
					 * Add Destination IP Address
					 * to the reply packet.
					 */
					شاخص = ARP_REQ_SRC_IP_LOC;
					طالما (شاخص < (ARP_REQ_SRC_IP_LOC +
							IP_ADDR_LEN)) {
						*Tx_قاب_Ptr++ =
								*(Rx_قاب_Ptr + شاخص);
						شاخص++;
					}

					/*
					 * Fill zeros as per protocol.
					 */
					شاخص = 0;
					طالما (شاخص < ARP_ZEROS_LEN) {
						*Tx_قاب_Ptr++ = 0x0000;
						شاخص++;
					}

					/*
					 * Transmit the Reply Packet.
					 */
					XEmacLite_Send(InstancePtr,
							(u8 *)&Tx_قاب,
							ARP_PACKET_اندازه);
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
		إذا (Xil_Ntohs(*(Rx_قاب_Ptr + ETHER_PROTO_TYPE_LOC)) ==
						XEL_ETHER_PROTO_TYPE_IP) {
//			printf("\n calculate ip header checksum");
			/*
			 * Check the IP header checksum.
			 */
			Check_جمع = Check_جمع_Calculation(Rx_قاب_Ptr,
						IP_HDR_شروع_LOC,
						IP_HDR_LEN);

			/*
			 * Check the Data field checksum.
			 */
//			printf("\n ip checksum:%x", CheckSum);
			إذا (Check_جمع == CORRECT_CKSUM_مقدار) {
				Check_جمع = Check_جمع_Calculation(Rx_قاب_Ptr,
						ICMP_داده_شروع_LOC,
						ICMP_داده_فیلد_LEN);
#إذا 0
			چاپ_کن("\nICMP Rcv Packet: \n");
			لكل(صحيح i = ICMP_داده_شروع_LOC; i <= ICMP_داده_فیلد_LEN; i++)
			   چاپ_کن("%x ", Rx_قاب_Ptr[i]);
			چاپ_کن("\n End of ICMP Rcv Packet");
				
				چاپ_کن("\n data checksum:%x", Check_جمع);
#پایان_اگر
				إذا (Check_جمع == CORRECT_CKSUM_مقدار) {

					/*
					 * Add destination address
					 * to the reply packet (i.e)source
					 * address of the received packet.
					 */
					شاخص = SRC_MAC_ADDR_LOC;
					طالما (شاخص < (SRC_MAC_ADDR_LOC +
							MAC_ADDR_LEN)) {
						*Tx_قاب_Ptr++ =
							*(Rx_قاب_Ptr + شاخص);
						شاخص++;
					}

					/*
					 * Add local MAC address
					 * to the reply packet.
					 */
					شاخص = 0;
					موقت_Ptr = (u16 *)LocalMacAddr;
					طالما (شاخص < MAC_ADDR_LEN) {
						*Tx_قاب_Ptr++ = *موقت_Ptr++;
						شاخص++;
					}

					/*
					 * Add protocol type
					 * header length and, packet
					 * length(60 Bytes) to the reply packet.
					 */
					شاخص = ETHER_PROTO_TYPE_LOC;
					طالما (شاخص < (ETHER_PROTO_TYPE_LOC +
							ETHER_PROTO_TYPE_LEN +
							IP_نسخه_LEN +
							IP_PACKET_LEN)) {
						*Tx_قاب_Ptr++ =
							*(Rx_قاب_Ptr + شاخص);
						شاخص++;
					}

					/*
					 * Identification field a random number
					 * which is set to IDENT_FIELD_VALUE.
					 */
					*Tx_قاب_Ptr++ = IDENT_فیلد_مقدار;

					/*
					 * Add fragment type, time to live and
					 * ICM field. It is same as in the
					 * received packet.
					 */
					شاخص = IP_FRAG_فیلد_LOC;
					طالما (شاخص < (IP_FRAG_فیلد_LOC +
							IP_TTL_ICM_LEN +
							IP_FRAG_فیلد_LEN)) {
						*Tx_قاب_Ptr++ =
							*(Rx_قاب_Ptr + شاخص);
						شاخص++;
					}

					/*
					 * Checksum first set to 0 and
					 * added in this field later.
					 */
					*Tx_قاب_Ptr++ = 0x0000;

					/*
					 * Add Source IP address
					 */
					شاخص = 0;
					موقت_Ptr = (u16 *)LocalIpAddr;
					طالما (شاخص < IP_ADDR_LEN) {
						*Tx_قاب_Ptr++ = *موقت_Ptr++;
						شاخص++;
					}

					/*
					 * Add Destination IP address.
					 */
					شاخص = ICMP_REQ_SRC_IP_LOC;
					طالما (شاخص < (ICMP_REQ_SRC_IP_LOC +
							IP_ADDR_LEN)) {
						*Tx_قاب_Ptr++ =
							*(Rx_قاب_Ptr + شاخص);
						شاخص++;
					}

					/*
					 * Calculate checksum, and
					 * add it in the appropriate field.
					 */
					Check_جمع = Check_جمع_Calculation(
							(u16 *)Tx_قاب,
							IP_HDR_شروع_LOC,
							IP_HDR_LEN);
					Check_جمع = ~Check_جمع;
					*(Tx_قاب_Ptr - IP_CSUM_LOC_پشت) =
								Xil_Htons(Check_جمع);

					/*
					 * Echo reply status & checksum.
					 */
					شاخص = ICMP_ECHO_فیلد_LOC;
					طالما (شاخص < (ICMP_ECHO_فیلد_LOC +
							ICMP_ECHO_فیلد_LEN)) {
						*Tx_قاب_Ptr++ = 0x0000;
						شاخص++;
					}

					/*
					 * Add data to buffer which was
					 * received from the packet.
					 */
					شاخص = ICMP_داده_LOC;
					طالما (شاخص < (ICMP_داده_LOC +
							ICMP_داده_LEN)) {
						*Tx_قاب_Ptr++ =
								(*(Rx_قاب_Ptr + شاخص));
						شاخص++;
					}

					/*
					 * Generate checksum for the data and
					 * add it in the appropriate field.
					 */
					Check_جمع = Check_جمع_Calculation(
							(u16 *)Tx_قاب,
							ICMP_داده_شروع_LOC,
							ICMP_داده_فیلد_LEN);
					Check_جمع = ~Check_جمع;
					*(Tx_قاب_Ptr - ICMP_داده_CSUM_LOC_پشت)
								= Xil_Htons(Check_جمع);

					/*
					 * Transmit the frame.
					 */
#إذا 1
					 چاپ_کن("\n%x. ICMP Tx Packet \n", رقم_از_Ping_Replies);
					 لكل(صحيح i = 0; i < ICMP_PACKET_اندازه; i++)
					 	چاپ_کن("%x ", Tx_قاب[i]);
					 چاپ_کن("\n End of ICMP Tx Packet");
#پایان_اگر					 
					XEmacLite_Send(InstancePtr,
							(u8 *)&Tx_قاب,
							ICMP_PACKET_اندازه);

					/*
					 * Increment the number of
					 * Ping replies sent.
					 */
					رقم_از_Ping_Replies++;
//					printf("NumOfPingReplies: %x", NumOfPingReplies);

				}
				وإلا
					چاپ_کن("\n Data check sum error");
			}
			وإلا
				چاپ_کن("\n IP Check sum error");
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
ساكن u16 Check_جمع_Calculation(u16 *Rx_قاب_Ptr, صحيح شروع_Loc, صحيح درازی)
{
	u32 جمع = 0;
	u16 Check_جمع = 0;
	صحيح شاخص;

	/*
	 * Add all the 16 bit data.
	 */
	شاخص = شروع_Loc;
	طالما (شاخص < (شروع_Loc + درازی)) {
		جمع = جمع + Xil_Ntohs(*(Rx_قاب_Ptr + شاخص));
		شاخص++;
	}

	/*
	 * Add upper 16 bits to lower 16 bits.
	 */
	Check_جمع = جمع;
	جمع = جمع >> 16;
	Check_جمع = جمع + Check_جمع;
	أرجع Check_جمع;
}
