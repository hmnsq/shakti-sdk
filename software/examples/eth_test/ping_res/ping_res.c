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

#అన్తర్భావ "gpio.h"
#అన్తర్భావ "uart.h"
#అన్తర్భావ "traps.h"
#అన్తర్భావ "platform.h"
#అన్తర్భావ "eth_driver.h"
#అన్తర్భావ "log.h"




/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#నిర్వచించు EMAC_DEVICE_ID			240
#నిర్వచించు ETH_పునాది_REG 0x44000
అస్థిర గుర్తులేని పూర్ణాంకం* eth_పునాది_reg = ETH_పునాది_REG;
/*
 * Instance of the driver
 */
స్థిర XEmacLite EmacLite;



/*
 * Change this parameter to limit the number of ping replies sent by this
 * program.
 */
#నిర్వచించు MAX_PING_REPLIES	10000	/* Maximum number of ping replies */

#నిర్వచించు ప్రసారం_PACKET	1	/* Broadcast packet */
#నిర్వచించు MAC_MATCHED_PACKET	2 	/* Dest MAC matched with local MAC */
#నిర్వచించు IP_ADDR_కొలత		4	/* IP Address size in Bytes */
#నిర్వచించు ARP_REQUEST 		0x0001	/* ARP Request bits in Rx packet */
#నిర్వచించు ARP_జవాబు 		0x0002 	/* ARP status bits indicating reply */
#నిర్వచించు ARP_PACKET_కొలత 	0x3C    /* ARP packet len 60 Bytes */
#నిర్వచించు ICMP_PACKET_కొలత 	98 //0x4A    /* ICMP packet length 74 Bytes
					 /* including Src and Dest MAC Address */
#నిర్వచించు ప్రసారం_ADDR 		0xFFFF  /* Broadcast Address */
#నిర్వచించు CORRECT_CKSUM_విలువ	0xFFFF  /* Correct checksum value */
#నిర్వచించు IDENT_క్షేత్రం_విలువ	0x9263	/* Identification field (random num) */

/*
 * Definitions for the locations and length of some of the fields in a
 * IP packet. The lengths are defined in Half-Words (2 bytes).
 */
#నిర్వచించు ETHER_PROTO_TYPE_LEN	1  /* Ethernet protocol Type length  */
#నిర్వచించు SRC_MAC_ADDR_LOC	3  /* Source MAC address location */
#నిర్వచించు MAC_ADDR_LEN 		3  /* MAC address length */
#నిర్వచించు ETHER_PROTO_TYPE_LOC	6  /* Ethernet Proto type location */

#నిర్వచించు ARP_HW_TYPE_LEN 	1  /* Hardware Type length  */
#నిర్వచించు ARP_PROTO_TYPE_LEN	1  /* Protocol Type length  */
#నిర్వచించు ARP_HW_కూడు_LEN		1  /* Hardware address length */
#నిర్వచించు ARP_PROTO_కూడు_LEN	1  /* Protocol address length */
#నిర్వచించు ARP_ZEROS_LEN		9  /* Length to be filled with zeros */
#నిర్వచించు ARP_REQ_స్థితి_LOC 	10 /* ARP request location */
#నిర్వచించు ARP_REQ_SRC_IP_LOC 	14 /* Src IP address location of ARP request */
#నిర్వచించు ARP_REQ_DEST_IP_LOC_1 	19 /* Destination IP's 1st half word location */
#నిర్వచించు ARP_REQ_DEST_IP_LOC_2 	20 /* Destination IP's 2nd half word location */

#నిర్వచించు IP_సంస్కరణ_LEN 		1  /* IP Version length  */
#నిర్వచించు IP_PACKET_LEN 		1  /* IP Packet length field  */
#నిర్వచించు IP_FRAG_క్షేత్రం_LEN	1  /* Fragment field len in ICMP packet */
#నిర్వచించు IP_TTL_ICM_LEN 		1  /* Time to live and ICM fields length */
#నిర్వచించు IP_ADDR_LEN 		2  /* Size of IP address in half-words */
#నిర్వచించు IP_CSUM_LOC_వెనుక	5  /* IP checksum location from end of frame */
#నిర్వచించు IP_HDR_ప్రారంభం_LOC 	7  /* IP header start location */
#నిర్వచించు IP_HDR_LEN 		10 /* IP Header length */
#నిర్వచించు IP_FRAG_క్షేత్రం_LOC 	10 /* Fragment field location */

#నిర్వచించు ICMP_TYPE_LEN 		1  /* ICMP Type length */
#నిర్వచించు ICMP_ECHO_క్షేత్రం_LEN 	2  /* Echo field length in half-words */
#నిర్వచించు ICMP_REQ_SRC_IP_LOC 	13 /* Src IP address location of ICMP request */
#నిర్వచించు ICMP_ECHO_క్షేత్రం_LOC 	17 /* Echo field location */
#నిర్వచించు ICMP_దత్తాంశం_ప్రారంభం_LOC 	17 /* Data field start location */
#నిర్వచించు ICMP_దత్తాంశం_LEN 		30  //18  /* ICMP data length */
#నిర్వచించు ICMP_దత్తాంశం_LOC 		19 /* ICMP data location including
				      identifier number and sequence number */
#నిర్వచించు ICMP_దత్తాంశం_CSUM_LOC_వెనుక 31 //19 
/* Data checksum location from end of
చట్రం*/
#నిర్వచించు ICMP_దత్తాంశం_క్షేత్రం_LEN 	32 //20 /* Data field length */

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

స్థిర పూర్ణాంకం Emac_Lite_Ping_జవాబు_Example(u16 DeviceId);

స్థిర శూన్య Process_Recv_చట్రం(XEmacLite *InstancePtr);

స్థిర u16 Check_కూడిక_Calculation(u16 *Rx_చట్రం_Ptr, పూర్ణాంకం ప్రారంభం_Loc, పూర్ణాంకం నిడివి);

/************************** Variable Definitions *****************************/

/*
 * Set up a local MAC address.
 */
స్థిర u8 LocalMacAddr[XEL_MAC_ADDR_కొలత] =
{
	0x00, 0x00, 0x5E, 0x00, 0xFA, 0xCE
};

/*
 * The IP address was set to 172.16.63.121. User need to set a free IP address
 * based on the network on which this example is to be run.
 */
స్థిర u8 LocalIpAddr[IP_ADDR_కొలత] =
{
	192, 168, 1, 25
};

స్థిర XEmacLite EmacLiteInstance;	/* Instance of the EmacLite driver */

/*
 * Buffers used for Transmission and Reception of Packets. These are declared as
 * global so that they are not a part of the stack.
 */
స్థిర u8 Rx_చట్రం[XEL_MAX_చట్రం_కొలత];
స్థిర u8 Tx_చట్రం[XEL_MAX_చట్రం_కొలత];

/*
 * Variable used to indicate the length of the received frame.
 */
బాహ్య అస్థిర u32 Recv_చట్రం_నిడివి = 0;

/*
 * Variable used to indicate the number of Ping replies sent.
 */
u32 అంకె_యొక్క_Ping_Replies;
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
పూర్ణాంకం ప్రధాన()
{
	పూర్ణాంకం స్థితి_2;
	arpcount = 0;
	/*
	 * Run the EmacLite Ping reply example.
	 */
	స్థితి_2 = Emac_Lite_Ping_జవాబు_Example(EMAC_DEVICE_ID);
	ఒకవేళ (స్థితి_2 != XST_SUCCESS) {
		xil_printf("Emaclite ping reply Example Failed\r\n");
		తిరిగి XST_FAILURE;
	}

	xil_printf("Successfully ran Emaclite ping reply Example\r\n");
	తిరిగి XST_SUCCESS;
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
పూర్ణాంకం Emac_Lite_Ping_జవాబు_Example(u16 DeviceId)
{
	పూర్ణాంకం స్థితి_2, లెక్క = 0;
	XEmacLite *EmacLiteInstPtr = &EmacLiteInstance;
	XEmacLite_Config *ConfigPtr;
	అంకె_యొక్క_Ping_Replies = 0;

	/*
	 * Initialize the EmacLite device.
	 */
	ConfigPtr = &XEmac_Lite_Config_పట్టిక;
	ఒకవేళ (ConfigPtr == ఖాళీ) {
		తిరిగి -1;
	}
	రాయి("\n ");

	ConfigPtr->పునాది_చిరునామా = (UINTPTR *) 0X44000;
	ConfigPtr->RxPingPong = XPAR_EMACLITE_0_RX_PING_PONG;
	ConfigPtr->MdioInclude = XPAR_EMACLITE_0_INCLUDE_MDIO;
	ConfigPtr->TxPingPong = XPAR_EMACLITE_0_TX_PING_PONG;
	స్థితి_2 = XEmacLite_CfgInitialize(EmacLiteInstPtr,
					ConfigPtr,
					ConfigPtr->పునాది_చిరునామా);
	ఒకవేళ (స్థితి_2 != 0) {
		తిరిగి -1;
	}
	
	/*
	 * Set the MAC address.
	 */
	XEmac_Lite_సమితి_Mac_చిరునామా(EmacLiteInstPtr, LocalMacAddr);
	/*
	 * Empty any existing receive frames.
	 */
	XEmacLite_FlushReceive(EmacLiteInstPtr);

	అయితే (1) {

		/*
		 * Wait for a Receive packet.
		 */
		అయితే (Recv_చట్రం_నిడివి == 0) {
			Recv_చట్రం_నిడివి = XEmacLite_Recv(EmacLiteInstPtr,
								(u8 *)Rx_చట్రం);
		}
#ఒకవేళ 1
		రాయి("\n Rcv. Frame %x: %x\n", అంకె_యొక్క_Ping_Replies, Recv_చట్రం_నిడివి);
		కొరకు(పూర్ణాంకం i = 0; i < Recv_చట్రం_నిడివి; i++)
			రాయి("%x ", Rx_చట్రం[i]);
		రాయి("\n");
#అయితే_ముగింపు			
		/*
		 * Empty any existing receive frames.
		 */
		XEmacLite_FlushReceive(EmacLiteInstPtr);

		/*
		 * Process the Receive frame.
		 */
		Process_Recv_చట్రం(EmacLiteInstPtr);
		Recv_చట్రం_నిడివి = 0;

		/*
		 * If the number of ping replies sent is equal to that
		 * specified by the user then exit out of this loop.
		 */
		ఒకవేళ (అంకె_యొక్క_Ping_Replies == MAX_PING_REPLIES) {

			తిరిగి XST_SUCCESS;
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
స్థిర శూన్య Process_Recv_చట్రం(XEmacLite *InstancePtr)
{
	u16 *Rx_చట్రం_Ptr;
	u16 *Tx_చట్రం_Ptr;
	u16 *తాత్కాలిక_Ptr;
	u16 Check_కూడిక;
	u32 తదుపరి_Tx_Buff_పునాది_Addr;
	పూర్ణాంకం సూచీ;
	పూర్ణాంకం PacketType = 0;

	Tx_చట్రం_Ptr = (u16 *)Tx_చట్రం;
	Rx_చట్రం_Ptr = (u16 *)Rx_చట్రం;

	/*
	 * Determine the next expected Tx buffer address.
	 */
	తదుపరి_Tx_Buff_పునాది_Addr = XEmac_Lite_తదుపరి_Transmit_Addr(InstancePtr);

	/*
	 * Check the packet type.
	 */
	సూచీ = MAC_ADDR_LEN;
	తాత్కాలిక_Ptr = (u16 *)LocalMacAddr;
	అయితే (సూచీ--) {
		ఒకవేళ (Xil_Ntohs((*(Rx_చట్రం_Ptr + సూచీ)) == ప్రసారం_ADDR) &&
					(PacketType != MAC_MATCHED_PACKET)) {
			PacketType = ప్రసారం_PACKET;
		} లేకపోతే ఒకవేళ (Xil_Ntohs((*(Rx_చట్రం_Ptr + సూచీ)) == *(తాత్కాలిక_Ptr + సూచీ)) &&
					(PacketType != ప్రసారం_PACKET)) {
			PacketType = MAC_MATCHED_PACKET;
		} లేకపోతే {
			PacketType = 0;
			ఆపు;
		}
	}
#ఒకవేళ 0
	రాయి("\n Packet type is %x", PacketType);
#అయితే_ముగింపు
	/*
	 * Process broadcast packet.
	 */
	ఒకవేళ (PacketType == ప్రసారం_PACKET) {

		/*
		 * Check for an ARP Packet if so generate a reply.
		 */
		ఒకవేళ (Xil_Ntohs(*(Rx_చట్రం_Ptr + ETHER_PROTO_TYPE_LOC)) ==
				XEL_ETHER_PROTO_TYPE_ARP) {

			/*
			 * IP address of the local machine.
			 */
			తాత్కాలిక_Ptr = (u16 *)LocalIpAddr;

			/*
			 * Check destination IP address of the packet with
			 * local IP address.
			 */
			ఒకవేళ (
			((*(Rx_చట్రం_Ptr + ARP_REQ_DEST_IP_LOC_1)) == *తాత్కాలిక_Ptr++) &&
			((*(Rx_చట్రం_Ptr + ARP_REQ_DEST_IP_LOC_2)) == *తాత్కాలిక_Ptr++)) {

				/*
				 * Check ARP packet type(request/reply).
				 */
				ఒకవేళ (Xil_Ntohs(*(Rx_చట్రం_Ptr + ARP_REQ_స్థితి_LOC)) ==
								ARP_REQUEST) {

					/*
					 * Add destination MAC address
					 * to the reply packet (i.e) source
					 * address of the received packet.
					 */
					సూచీ = SRC_MAC_ADDR_LOC;
					అయితే (సూచీ < (SRC_MAC_ADDR_LOC +
							MAC_ADDR_LEN)) {
						*Tx_చట్రం_Ptr++ =
							*(Rx_చట్రం_Ptr + సూచీ);
						సూచీ++;
					}

					/*
					 * Add source (local) MAC address
					 * to the reply packet.
					 */
					సూచీ = 0;
					తాత్కాలిక_Ptr = (u16 *)LocalMacAddr;
					అయితే (సూచీ < MAC_ADDR_LEN) {
						*Tx_చట్రం_Ptr++ = *తాత్కాలిక_Ptr++;
						సూచీ++;
					}

					/*
					 * Add Ethernet proto type H/W
					 * type(10/3MBps),H/W address length and
					 * protocol address len (i.e)same as in
					 * the received packet
					 */
					సూచీ = ETHER_PROTO_TYPE_LOC;
					అయితే (సూచీ < (ETHER_PROTO_TYPE_LOC +
							ETHER_PROTO_TYPE_LEN +
							ARP_HW_TYPE_LEN +
							ARP_HW_కూడు_LEN
							+ ARP_PROTO_కూడు_LEN)) {
						*Tx_చట్రం_Ptr++ =
							*(Rx_చట్రం_Ptr + సూచీ);
						సూచీ++;
					}

					/*
					 * Add ARP reply status to the reply
					 * packet.
					 */
					*Tx_చట్రం_Ptr++ = Xil_Htons(ARP_జవాబు);

					/*
					 * Add local MAC Address
					 * to the reply packet.
					 */
					తాత్కాలిక_Ptr = (u16 *)LocalMacAddr;
					సూచీ = 0;
					అయితే (సూచీ < MAC_ADDR_LEN) {
						*Tx_చట్రం_Ptr++ = *తాత్కాలిక_Ptr++;
						సూచీ++;
					}

					/*
					 * Add local IP Address
					 * to the reply packet.
					 */
					తాత్కాలిక_Ptr = (u16 *)LocalIpAddr;
					సూచీ = 0;
					అయితే (సూచీ < IP_ADDR_LEN) {
						*Tx_చట్రం_Ptr++ = *తాత్కాలిక_Ptr++ ;
						సూచీ++;
					}

					/*
					 * Add Destination MAC Address
					 * to the reply packet from the received
					 * packet.
					 */
					సూచీ = SRC_MAC_ADDR_LOC;
					అయితే (సూచీ < (SRC_MAC_ADDR_LOC +
							MAC_ADDR_LEN)) {
						*Tx_చట్రం_Ptr++ =
							*(Rx_చట్రం_Ptr + సూచీ);
						సూచీ++;
					}

					/*
					 * Add Destination IP Address
					 * to the reply packet.
					 */
					సూచీ = ARP_REQ_SRC_IP_LOC;
					అయితే (సూచీ < (ARP_REQ_SRC_IP_LOC +
							IP_ADDR_LEN)) {
						*Tx_చట్రం_Ptr++ =
								*(Rx_చట్రం_Ptr + సూచీ);
						సూచీ++;
					}

					/*
					 * Fill zeros as per protocol.
					 */
					సూచీ = 0;
					అయితే (సూచీ < ARP_ZEROS_LEN) {
						*Tx_చట్రం_Ptr++ = 0x0000;
						సూచీ++;
					}

					/*
					 * Transmit the Reply Packet.
					 */
					XEmacLite_Send(InstancePtr,
							(u8 *)&Tx_చట్రం,
							ARP_PACKET_కొలత);
				}
			}
		}
	}

	/*
	 * Process packets whose MAC address is matched.
	 */
	ఒకవేళ (PacketType == MAC_MATCHED_PACKET) {
//		printf("\n MAC matched packet");
		/*
		 * Check ICMP packet.
		 */
		ఒకవేళ (Xil_Ntohs(*(Rx_చట్రం_Ptr + ETHER_PROTO_TYPE_LOC)) ==
						XEL_ETHER_PROTO_TYPE_IP) {
//			printf("\n calculate ip header checksum");
			/*
			 * Check the IP header checksum.
			 */
			Check_కూడిక = Check_కూడిక_Calculation(Rx_చట్రం_Ptr,
						IP_HDR_ప్రారంభం_LOC,
						IP_HDR_LEN);

			/*
			 * Check the Data field checksum.
			 */
//			printf("\n ip checksum:%x", CheckSum);
			ఒకవేళ (Check_కూడిక == CORRECT_CKSUM_విలువ) {
				Check_కూడిక = Check_కూడిక_Calculation(Rx_చట్రం_Ptr,
						ICMP_దత్తాంశం_ప్రారంభం_LOC,
						ICMP_దత్తాంశం_క్షేత్రం_LEN);
#ఒకవేళ 0
			రాయి("\nICMP Rcv Packet: \n");
			కొరకు(పూర్ణాంకం i = ICMP_దత్తాంశం_ప్రారంభం_LOC; i <= ICMP_దత్తాంశం_క్షేత్రం_LEN; i++)
			   రాయి("%x ", Rx_చట్రం_Ptr[i]);
			రాయి("\n End of ICMP Rcv Packet");
				
				రాయి("\n data checksum:%x", Check_కూడిక);
#అయితే_ముగింపు
				ఒకవేళ (Check_కూడిక == CORRECT_CKSUM_విలువ) {

					/*
					 * Add destination address
					 * to the reply packet (i.e)source
					 * address of the received packet.
					 */
					సూచీ = SRC_MAC_ADDR_LOC;
					అయితే (సూచీ < (SRC_MAC_ADDR_LOC +
							MAC_ADDR_LEN)) {
						*Tx_చట్రం_Ptr++ =
							*(Rx_చట్రం_Ptr + సూచీ);
						సూచీ++;
					}

					/*
					 * Add local MAC address
					 * to the reply packet.
					 */
					సూచీ = 0;
					తాత్కాలిక_Ptr = (u16 *)LocalMacAddr;
					అయితే (సూచీ < MAC_ADDR_LEN) {
						*Tx_చట్రం_Ptr++ = *తాత్కాలిక_Ptr++;
						సూచీ++;
					}

					/*
					 * Add protocol type
					 * header length and, packet
					 * length(60 Bytes) to the reply packet.
					 */
					సూచీ = ETHER_PROTO_TYPE_LOC;
					అయితే (సూచీ < (ETHER_PROTO_TYPE_LOC +
							ETHER_PROTO_TYPE_LEN +
							IP_సంస్కరణ_LEN +
							IP_PACKET_LEN)) {
						*Tx_చట్రం_Ptr++ =
							*(Rx_చట్రం_Ptr + సూచీ);
						సూచీ++;
					}

					/*
					 * Identification field a random number
					 * which is set to IDENT_FIELD_VALUE.
					 */
					*Tx_చట్రం_Ptr++ = IDENT_క్షేత్రం_విలువ;

					/*
					 * Add fragment type, time to live and
					 * ICM field. It is same as in the
					 * received packet.
					 */
					సూచీ = IP_FRAG_క్షేత్రం_LOC;
					అయితే (సూచీ < (IP_FRAG_క్షేత్రం_LOC +
							IP_TTL_ICM_LEN +
							IP_FRAG_క్షేత్రం_LEN)) {
						*Tx_చట్రం_Ptr++ =
							*(Rx_చట్రం_Ptr + సూచీ);
						సూచీ++;
					}

					/*
					 * Checksum first set to 0 and
					 * added in this field later.
					 */
					*Tx_చట్రం_Ptr++ = 0x0000;

					/*
					 * Add Source IP address
					 */
					సూచీ = 0;
					తాత్కాలిక_Ptr = (u16 *)LocalIpAddr;
					అయితే (సూచీ < IP_ADDR_LEN) {
						*Tx_చట్రం_Ptr++ = *తాత్కాలిక_Ptr++;
						సూచీ++;
					}

					/*
					 * Add Destination IP address.
					 */
					సూచీ = ICMP_REQ_SRC_IP_LOC;
					అయితే (సూచీ < (ICMP_REQ_SRC_IP_LOC +
							IP_ADDR_LEN)) {
						*Tx_చట్రం_Ptr++ =
							*(Rx_చట్రం_Ptr + సూచీ);
						సూచీ++;
					}

					/*
					 * Calculate checksum, and
					 * add it in the appropriate field.
					 */
					Check_కూడిక = Check_కూడిక_Calculation(
							(u16 *)Tx_చట్రం,
							IP_HDR_ప్రారంభం_LOC,
							IP_HDR_LEN);
					Check_కూడిక = ~Check_కూడిక;
					*(Tx_చట్రం_Ptr - IP_CSUM_LOC_వెనుక) =
								Xil_Htons(Check_కూడిక);

					/*
					 * Echo reply status & checksum.
					 */
					సూచీ = ICMP_ECHO_క్షేత్రం_LOC;
					అయితే (సూచీ < (ICMP_ECHO_క్షేత్రం_LOC +
							ICMP_ECHO_క్షేత్రం_LEN)) {
						*Tx_చట్రం_Ptr++ = 0x0000;
						సూచీ++;
					}

					/*
					 * Add data to buffer which was
					 * received from the packet.
					 */
					సూచీ = ICMP_దత్తాంశం_LOC;
					అయితే (సూచీ < (ICMP_దత్తాంశం_LOC +
							ICMP_దత్తాంశం_LEN)) {
						*Tx_చట్రం_Ptr++ =
								(*(Rx_చట్రం_Ptr + సూచీ));
						సూచీ++;
					}

					/*
					 * Generate checksum for the data and
					 * add it in the appropriate field.
					 */
					Check_కూడిక = Check_కూడిక_Calculation(
							(u16 *)Tx_చట్రం,
							ICMP_దత్తాంశం_ప్రారంభం_LOC,
							ICMP_దత్తాంశం_క్షేత్రం_LEN);
					Check_కూడిక = ~Check_కూడిక;
					*(Tx_చట్రం_Ptr - ICMP_దత్తాంశం_CSUM_LOC_వెనుక)
								= Xil_Htons(Check_కూడిక);

					/*
					 * Transmit the frame.
					 */
#ఒకవేళ 1
					 రాయి("\n%x. ICMP Tx Packet \n", అంకె_యొక్క_Ping_Replies);
					 కొరకు(పూర్ణాంకం i = 0; i < ICMP_PACKET_కొలత; i++)
					 	రాయి("%x ", Tx_చట్రం[i]);
					 రాయి("\n End of ICMP Tx Packet");
#అయితే_ముగింపు					 
					XEmacLite_Send(InstancePtr,
							(u8 *)&Tx_చట్రం,
							ICMP_PACKET_కొలత);

					/*
					 * Increment the number of
					 * Ping replies sent.
					 */
					అంకె_యొక్క_Ping_Replies++;
//					printf("NumOfPingReplies: %x", NumOfPingReplies);

				}
				లేకపోతే
					రాయి("\n Data check sum error");
			}
			లేకపోతే
				రాయి("\n IP Check sum error");
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
స్థిర u16 Check_కూడిక_Calculation(u16 *Rx_చట్రం_Ptr, పూర్ణాంకం ప్రారంభం_Loc, పూర్ణాంకం నిడివి)
{
	u32 కూడిక = 0;
	u16 Check_కూడిక = 0;
	పూర్ణాంకం సూచీ;

	/*
	 * Add all the 16 bit data.
	 */
	సూచీ = ప్రారంభం_Loc;
	అయితే (సూచీ < (ప్రారంభం_Loc + నిడివి)) {
		కూడిక = కూడిక + Xil_Ntohs(*(Rx_చట్రం_Ptr + సూచీ));
		సూచీ++;
	}

	/*
	 * Add upper 16 bits to lower 16 bits.
	 */
	Check_కూడిక = కూడిక;
	కూడిక = కూడిక >> 16;
	Check_కూడిక = కూడిక + Check_కూడిక;
	తిరిగి Check_కూడిక;
}
