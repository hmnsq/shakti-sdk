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

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

బాహ్య XEmacLite_Config XEmac_Lite_Config_పట్టిక;

/************************** Variable Definitions *****************************/

/*
 * Instance of the driver
 */
స్థిర XEmacLite EmacLite;


/*
 * Change this parameter to limit the number of ping requests sent by this
 * program.
 */
#నిర్వచించు అంకె_యొక్క_PING_REQ_PKTS	100	/* Number of ping req it generates */

#నిర్వచించు ECHO_జవాబు		0x00	/* Echo reply */
#నిర్వచించు HW_TYPE			0x01	/* Hardware type (10/100 Mbps) */
#నిర్వచించు ARP_REQUEST 		0x01	/* ARP Request bits in Rx packet */
#నిర్వచించు ARP_జవాబు 		0x02 	/* ARP status bits indicating reply */
#నిర్వచించు IDEN_అంకె		0x02	/* ICMP identifier number */
#నిర్వచించు IP_సంస్కరణ		0x0604	/* IP version ipv4/ipv6 */
#నిర్వచించు ప్రసారం_ADDR 		0xFFFF 	/* Broadcast Address */
#నిర్వచించు CORRECT_CHECKSUM_విలువ	0xFFFF	/* Correct checksum value */
#నిర్వచించు ARP_REQ_PKT_కొలత	0x2A	/* ARP request packet size */
#నిర్వచించు ICMP_PKT_కొలత 		0x4A	/* ICMP packet length 74 Bytes
					including Src and dest MAC Add */
#నిర్వచించు IP_ADDR_కొలత		4	/* IP Address size in Bytes */
#నిర్వచించు అంకె_RX_PACK_CHECK_REQ	10	/* Max num of Rx pack to be checked
					before sending another request */
#నిర్వచించు అంకె_PACK_CHECK_RX_PACK	100	/* Max number of pack to be checked
					before to identify a Rx packet */
#నిర్వచించు DELAY			5000000 /* Used to introduce delay */

/*
 * Definitions for the locations and length of some of the fields in a
 * IP packet. The lengths are defined in Half-Words (2 bytes).
 */

#నిర్వచించు SRC_MAC_ADDR_LOC	3	/* Src MAC address location */
#నిర్వచించు MAC_ADDR_LEN 		3	/* MAC address length */
#నిర్వచించు ETHER_PROTO_TYPE_LOC	6	/* Ethernet Proto type loc */

#నిర్వచించు IP_ADDR_LEN 		2	/* Size of IP address */
#నిర్వచించు IP_ప్రారంభం_LOC 		7	/* IP header start location */
#నిర్వచించు IP_శీర్షిక_INFO_LEN	7	/* IP header information length */
#నిర్వచించు IP_శీర్షిక_LEN 		10 	/* IP header length */
#నిర్వచించు IP_CHECKSUM_LOC		12	/* IP header checksum location */
#నిర్వచించు IP_REQ_SRC_IP_LOC 	13	/* Src IP add loc of ICMP req */
#నిర్వచించు IP_REQ_DEST_IP_LOC	15	/* Dest IP add loc of ICMP req */

#నిర్వచించు ICMP_తెలిసిన_దత్తాంశం_LEN	64	/* ICMP known data length */
#నిర్వచించు ICMP_ECHO_క్షేత్రం_LOC 	17	/* Echo field loc */
#నిర్వచించు ICMP_దత్తాంశం_ప్రారంభం_LOC 	17	/* Data field start location */
#నిర్వచించు ICMP_దత్తాంశం_LEN 		18	/* ICMP data length */
#నిర్వచించు ICMP_దత్తాంశం_CHECKSUM_LOC	18	/* ICMP data checksum location */
#నిర్వచించు ICMP_IDEN_క్షేత్రం_LOC	19	/* Identifier field loc */
#నిర్వచించు ICMP_దత్తాంశం_LOC 		19	/* ICMP data loc including
					identifier number and sequence number */
#నిర్వచించు ICMP_SEQ_NO_LOC		20	/* sequence number location */
#నిర్వచించు ICMP_దత్తాంశం_క్షేత్రం_LEN 	20 	/* Data field length */
#నిర్వచించు ICMP_తెలిసిన_దత్తాంశం_LOC	21	/* ICMP known data start loc */

#నిర్వచించు ARP_REQ_స్థితి_LOC 	10	/* ARP request loc */
#నిర్వచించు ARP_REQ_SRC_IP_LOC 	14	/* Src IP add loc of ARP req Packet */

/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/

స్థిర పూర్ణాంకం EmacLitePingReqExample(u16 DeviceId);

స్థిర శూన్య Send_Arp_Req_చట్రం(XEmacLite *InstancePtr);

స్థిర శూన్య Send_Echo_Req_చట్రం(XEmacLite *InstancePtr);

స్థిర పూర్ణాంకం Process_Recv_చట్రం(XEmacLite *InstancePtr);

స్థిర u16 Check_కూడిక_Calculation(u16 *Rx_చట్రం_Ptr16, పూర్ణాంకం ప్రారంభం_Loc, పూర్ణాంకం నిడివి);

స్థిర పూర్ణాంకం Compare_దత్తాంశం(u16 *LhsPtr, u16 *RhsPtr, పూర్ణాంకం LhsLoc, పూర్ణాంకం RhsLoc,
			పూర్ణాంకం లెక్క_2);

/************************** Variable Definitions *****************************/

/*
 * Set up a local MAC address.
 */
స్థిర u8 LocalMacAddr[XEL_MAC_ADDR_కొలత] =
{
	0x00, 0x0A, 0x35, 0x03, 0x02, 0x01
};

/*
 * The IP address was set to 172.16.63.121. User need to set a free IP address
 * based on the network on which this example is to be run.
 */
స్థిర u8 Local_Ip_చిరునామా[IP_ADDR_కొలత] =
{
	192, 168, 1, 26
};

/*
 * Set up a Destination IP address. Currently it is set to 172.16.63.61.
 */
/* ifconfig enp1s0 172.16.63.61 netmask 255.255.255.0 up */
స్థిర u8 Dest_Ip_చిరునామా[IP_ADDR_కొలత] =
{
	192, 168, 1, 25
};

స్థిర u16 DestMacAddr[MAC_ADDR_LEN]; 	/* Destination MAC Address */
స్థిర XEmacLite EmacLiteInstance;	/* Instance of the EmacLite driver */

/*
 * Known data transmitted in Echo request.
 */
u16 Icmp_దత్తాంశం[ICMP_తెలిసిన_దత్తాంశం_LEN] =
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
u16 Ip_శీర్షిక_Info[IP_శీర్షిక_INFO_LEN] =
{
	0x0800,	0x4500, 0x003C,	0x5566,	0x0000,	0x8001, 0x0000
};

/*
 * Buffers used for Transmission and Reception of Packets. These are declared as
 * global so that they are not a part of the stack.
 */
స్థిర u8 Rx_చట్రం[XEL_MAX_చట్రం_కొలత];
స్థిర u8 Tx_చట్రం[XEL_MAX_చట్రం_కొలత];

/*
 * Variable used to indicate the length of the received frame.
 */
బాహ్య అస్థిర u32 Recv_చట్రం_నిడివి;

/*
 * Variable used to indicate the sequence number of the ICMP(echo) packet.
 */
పూర్ణాంకం Seq_అంకె;

/*
 * Variable used to indicate the number of ping request packets to be send.
 */
పూర్ణాంకం అంకె_యొక్క_Ping_Req_Pkts;

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
పూర్ణాంకం ప్రధాన()
{
	పూర్ణాంకం స్థితి_2;

	/*
	 * Run the EmacLite Ping request example.
	 */
	స్థితి_2 = EmacLitePingReqExample(EMAC_DEVICE_ID);
	ఒకవేళ (స్థితి_2 != XST_SUCCESS) {
		xil_printf("Emaclite ping request Example Failed\r\n");
		తిరిగి XST_FAILURE;
	}

	xil_printf("Successfully ran Emaclite ping request Example\r\n");
	తిరిగి XST_SUCCESS;
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
స్థిర పూర్ణాంకం EmacLitePingReqExample(u16 DeviceId)
{
	పూర్ణాంకం స్థితి_2;
	పూర్ణాంకం సూచీ;
	పూర్ణాంకం లెక్క_2;
	పూర్ణాంకం Echo_జవాబు_స్థితి;
	XEmacLite_Config *ConfigPtr;
	XEmacLite *EmacLiteInstPtr = &EmacLiteInstance;
	Seq_అంకె = 0;
	Recv_చట్రం_నిడివి = 0;
	Echo_జవాబు_స్థితి = XST_FAILURE;
	అంకె_యొక్క_Ping_Req_Pkts = అంకె_యొక్క_PING_REQ_PKTS;

	/*
	 * Initialize the EmacLite device.
	 */
	ConfigPtr = &XEmac_Lite_Config_పట్టిక;
	ఒకవేళ (ConfigPtr == ఖాళీ) {
		తిరిగి -1;
	}
	ConfigPtr->పునాది_చిరునామా = (UINTPTR *) 0X44000;
	ConfigPtr->RxPingPong = XPAR_EMACLITE_0_RX_PING_PONG;
	ConfigPtr->MdioInclude = XPAR_EMACLITE_0_INCLUDE_MDIO;
	ConfigPtr->TxPingPong = XPAR_EMACLITE_0_TX_PING_PONG;
#ఒకవేళ 0
	log_debug("\n ConfigPtr: BaseAddress: %x", ConfigPtr->పునాది_చిరునామా);
	log_debug("\n ConfigPtr: DeviceId: %x", ConfigPtr->DeviceId);
	log_debug("\n ConfigPtr: TxPingPong: %x", ConfigPtr->TxPingPong);
	log_debug("\n ConfigPtr: RxPingPong: %x", ConfigPtr->RxPingPong);
	log_debug("\n ConfigPtr: MdioInclude: %x", ConfigPtr->MdioInclude);
	log_debug("\n ConfigPtr: Loopback: %x", ConfigPtr->Loopback);
#అయితే_ముగింపు	
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
	అయితే (అంకె_యొక్క_Ping_Req_Pkts--) {

		/*
		 * Introduce delay.
		 */
		లెక్క_2 = DELAY;
		అయితే (లెక్క_2--) {
		}

		/*
		 * Send an ARP or an ICMP packet based on receive packet.
		 */
		ఒకవేళ (Seq_అంకె == 0) {
			Send_Arp_Req_చట్రం(EmacLiteInstPtr);
		} లేకపోతే {
			Send_Echo_Req_చట్రం(EmacLiteInstPtr);
		}

		/*
		 * Check next 10 packets for the correct reply.
		 */
		సూచీ = అంకె_RX_PACK_CHECK_REQ;
		అయితే (సూచీ--) {

			/*
			 * Wait for a Receive packet.
			 */
			లెక్క_2 = అంకె_PACK_CHECK_RX_PACK;
			అయితే (Recv_చట్రం_నిడివి == 0) {
				Recv_చట్రం_నిడివి = XEmacLite_Recv(
							EmacLiteInstPtr,
							(u8 *)Rx_చట్రం);

				/*
				 * To avoid infinite loop when no packet is
				 * received.
				 */
				ఒకవేళ (లెక్క_2-- == 0) {
					ఆపు;
				}
			}

			/*
			 * Process the Receive frame.
			 */
			ఒకవేళ (Recv_చట్రం_నిడివి != 0) {
				Echo_జవాబు_స్థితి = Process_Recv_చట్రం(
							EmacLiteInstPtr);
			}
			Recv_చట్రం_నిడివి = 0;

			/*
			 * Comes out of loop when an echo reply packet is
			 * received.
			 */
			ఒకవేళ (Echo_జవాబు_స్థితి == XST_SUCCESS) {
				ఆపు;
			}
		}

		/*
		 * If no echo reply packet is received, it reports
		 * request timed out.
		 */
		ఒకవేళ (Echo_జవాబు_స్థితి == XST_FAILURE) {
			xil_printf("Packet No: %d",
				అంకె_యొక్క_PING_REQ_PKTS - అంకె_యొక్క_Ping_Req_Pkts);
			xil_printf(" Seq NO %d Request timed out\r\n",
							Seq_అంకె);
		}
	}
	తిరిగి XST_SUCCESS;
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
స్థిర శూన్య Send_Arp_Req_చట్రం(XEmacLite *InstancePtr)
{
	u16 *తాత్కాలిక_Ptr;
	u16 *Tx_చట్రం_Ptr;
	u32 తదుపరి_Tx_Buff_పునాది_Addr;
	పూర్ణాంకం సూచీ;

	Tx_చట్రం_Ptr = (u16 *)Tx_చట్రం;

	/*
	 * Determine the next expected transmit buffer base address.
	 */
	తదుపరి_Tx_Buff_పునాది_Addr = XEmac_Lite_తదుపరి_Transmit_Addr(InstancePtr);

	/*
	 * Add broadcast address.
	 */
	సూచీ = MAC_ADDR_LEN;
	అయితే (సూచీ--) {
		*Tx_చట్రం_Ptr++ = ప్రసారం_ADDR;
	}

	/*
	 * Add local MAC address.
	 */
	సూచీ = 0;
	తాత్కాలిక_Ptr = (u16 *)LocalMacAddr;
	అయితే (సూచీ < MAC_ADDR_LEN) {
		*Tx_చట్రం_Ptr++ = *(తాత్కాలిక_Ptr + సూచీ);
		సూచీ++;
	}

	/*
	 * Add
	 * 	- Ethernet proto type.
	 *	- Hardware Type
	 *	- Protocol IP Type
	 *	- IP version (IPv6/IPv4)
	 *	- ARP Request
	 */
	*Tx_చట్రం_Ptr++ = Xil_Htons(XEL_ETHER_PROTO_TYPE_ARP);
	*Tx_చట్రం_Ptr++ = Xil_Htons(HW_TYPE);
	*Tx_చట్రం_Ptr++ = Xil_Htons(XEL_ETHER_PROTO_TYPE_IP);
	*Tx_చట్రం_Ptr++ = Xil_Htons(IP_సంస్కరణ);
	*Tx_చట్రం_Ptr++ = Xil_Htons(ARP_REQUEST);

	/*
	 * Add local MAC address.
	 */
	సూచీ = 0;
	తాత్కాలిక_Ptr = (u16 *)LocalMacAddr;
	అయితే (సూచీ < MAC_ADDR_LEN) {
		*Tx_చట్రం_Ptr++ = *(తాత్కాలిక_Ptr + సూచీ);
		సూచీ++;
	}

	/*
	 * Add local IP address.
	 */
	సూచీ = 0;
	తాత్కాలిక_Ptr = (u16 *)Local_Ip_చిరునామా;
	అయితే (సూచీ < IP_ADDR_LEN) {
		*Tx_చట్రం_Ptr++ = *(తాత్కాలిక_Ptr + సూచీ);
		సూచీ++;
	}

	/*
	 * Fills 6 bytes of information with zeros as per protocol.
	 */
	సూచీ = 0;
	అయితే (సూచీ < 3) {
		*Tx_చట్రం_Ptr++ = 0x0000;
		సూచీ++;
	}

	/*
	 * Add Destination IP address.
	 */
	సూచీ = 0;
	తాత్కాలిక_Ptr = (u16 *)Dest_Ip_చిరునామా;
	అయితే (సూచీ < IP_ADDR_LEN) {
		*Tx_చట్రం_Ptr++ = *(తాత్కాలిక_Ptr + సూచీ);
		సూచీ++;
	}

	/*
	 * Transmit the Frame.
	 */
	XEmacLite_Send(InstancePtr, (u8 *)&Tx_చట్రం, ARP_REQ_PKT_కొలత);
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
స్థిర శూన్య Send_Echo_Req_చట్రం(XEmacLite *InstancePtr)
{
	u16 *తాత్కాలిక_Ptr;
	u16 *Tx_చట్రం_Ptr;
	u16 *Rx_చట్రం_Ptr;
	u16 Check_కూడిక;
	u32 తదుపరి_Tx_Buff_పునాది_Addr;
	పూర్ణాంకం సూచీ;

	Tx_చట్రం_Ptr = (u16 *)Tx_చట్రం;
	Rx_చట్రం_Ptr = (u16 *)Rx_చట్రం;

	/*
	 * Determine the next expected transmit buffer base address.
	 */
	తదుపరి_Tx_Buff_పునాది_Addr = XEmac_Lite_తదుపరి_Transmit_Addr(InstancePtr);

	/*
	 * Add Destination MAC Address.
	 */
	సూచీ = MAC_ADDR_LEN;
	అయితే (సూచీ--) {
		*(Tx_చట్రం_Ptr + సూచీ) = *(DestMacAddr + సూచీ);
	}

	/*
	 * Add Source MAC Address.
	 */
	సూచీ = MAC_ADDR_LEN;
	తాత్కాలిక_Ptr = (u16 *)LocalMacAddr;
	అయితే (సూచీ--) {
		*(Tx_చట్రం_Ptr + (సూచీ + SRC_MAC_ADDR_LOC )) =
							*(తాత్కాలిక_Ptr + సూచీ);
	}

	/*
	 * Add IP header information.
	 */
	సూచీ = IP_ప్రారంభం_LOC;
	అయితే (సూచీ--) {
		*(Tx_చట్రం_Ptr + (సూచీ + ETHER_PROTO_TYPE_LOC )) =
				Xil_Htons(*(Ip_శీర్షిక_Info + సూచీ));
	}

	/*
	 * Add Source IP address.
	 */
	సూచీ = IP_ADDR_LEN;
	తాత్కాలిక_Ptr = (u16 *)Local_Ip_చిరునామా;
	అయితే (సూచీ--) {
		*(Tx_చట్రం_Ptr + (సూచీ + IP_REQ_SRC_IP_LOC )) =
						*(తాత్కాలిక_Ptr + సూచీ);
	}

	/*
	 * Add Destination IP address.
	 */
	సూచీ = IP_ADDR_LEN;
	తాత్కాలిక_Ptr = (u16 *)Dest_Ip_చిరునామా;
	అయితే (సూచీ--) {
		*(Tx_చట్రం_Ptr + (సూచీ + IP_REQ_DEST_IP_LOC )) =
						*(తాత్కాలిక_Ptr + సూచీ);
	}

	/*
	 * Checksum is calculated for IP field and added in the frame.
	 */
	Check_కూడిక = Check_కూడిక_Calculation((u16 *)Tx_చట్రం, IP_ప్రారంభం_LOC,
							IP_శీర్షిక_LEN);
	Check_కూడిక = ~Check_కూడిక;
	*(Tx_చట్రం_Ptr + IP_CHECKSUM_LOC) = Xil_Htons(Check_కూడిక);

	/*
	 * Add echo field information.
	 */
	*(Tx_చట్రం_Ptr + ICMP_ECHO_క్షేత్రం_LOC) = Xil_Htons(XEL_ETHER_PROTO_TYPE_IP);

	/*
	 * Checksum value is initialized to zeros.
	 */
	*(Tx_చట్రం_Ptr + ICMP_దత్తాంశం_LEN) = 0x0000;

	/*
	 * Add identifier and sequence number to the frame.
	 */
	*(Tx_చట్రం_Ptr + ICMP_IDEN_క్షేత్రం_LOC) = (IDEN_అంకె);
	*(Tx_చట్రం_Ptr + (ICMP_IDEN_క్షేత్రం_LOC + 1)) = Xil_Htons((u16)(++Seq_అంకె));

	/*
	 * Add known data to the frame.
	 */
	సూచీ = ICMP_తెలిసిన_దత్తాంశం_LEN;
	అయితే (సూచీ--) {
		*(Tx_చట్రం_Ptr + (సూచీ + ICMP_తెలిసిన_దత్తాంశం_LOC)) =
				Xil_Htons(*(Icmp_దత్తాంశం + సూచీ));
	}

	/*
	 * Checksum is calculated for Data Field and added in the frame.
	 */
	Check_కూడిక = Check_కూడిక_Calculation((u16 *)Tx_చట్రం, ICMP_దత్తాంశం_ప్రారంభం_LOC,
						ICMP_దత్తాంశం_క్షేత్రం_LEN );
	Check_కూడిక = ~Check_కూడిక;
	*(Tx_చట్రం_Ptr + ICMP_దత్తాంశం_CHECKSUM_LOC) = Xil_Htons(Check_కూడిక);

	/*
	 * Transmit the Frame.
	 */
	XEmacLite_Send(InstancePtr, (u8 *)&Tx_చట్రం, ICMP_PKT_కొలత);
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
స్థిర పూర్ణాంకం Process_Recv_చట్రం(XEmacLite *InstancePtr)
{
	u16 *Rx_చట్రం_Ptr;
	u16 *తాత్కాలిక_Ptr;
	u16 Check_కూడిక;
	పూర్ణాంకం సూచీ;
	పూర్ణాంకం సరిపోలిక = 0;
	పూర్ణాంకం దత్తాంశం_Wrong = 0;

	Rx_చట్రం_Ptr = (u16 *)Rx_చట్రం;
	తాత్కాలిక_Ptr = (u16 *)LocalMacAddr;

	/*
	 * Check Dest Mac address of the packet with the LocalMac address.
	 */
	సరిపోలిక = Compare_దత్తాంశం(Rx_చట్రం_Ptr, తాత్కాలిక_Ptr, 0, 0, MAC_ADDR_LEN);
	ఒకవేళ (సరిపోలిక == XST_SUCCESS) {

		/*
		 * Check ARP type.
		 */
		ఒకవేళ (Xil_Ntohs(*(Rx_చట్రం_Ptr + ETHER_PROTO_TYPE_LOC)) ==
				XEL_ETHER_PROTO_TYPE_ARP ) {

			/*
			 * Check ARP status.
			 */
			ఒకవేళ (Xil_Ntohs(*(Rx_చట్రం_Ptr + ARP_REQ_స్థితి_LOC)) == ARP_జవాబు) {

				/*
				 * Check destination IP address with
				 * packet's source IP address.
				 */
				తాత్కాలిక_Ptr = (u16 *)Dest_Ip_చిరునామా;
				సరిపోలిక = Compare_దత్తాంశం(Rx_చట్రం_Ptr,
						తాత్కాలిక_Ptr, ARP_REQ_SRC_IP_LOC,
						0, IP_ADDR_LEN);
				ఒకవేళ (సరిపోలిక == XST_SUCCESS) {

					/*
					 * Copy src Mac address of the received
					 * packet.
					 */
					సూచీ = MAC_ADDR_LEN;
					తాత్కాలిక_Ptr = (u16 *)DestMacAddr;
					అయితే (సూచీ--) {
						*(తాత్కాలిక_Ptr + సూచీ) =
							*(Rx_చట్రం_Ptr +
							(SRC_MAC_ADDR_LOC +
								సూచీ));
					}

					/*
					 * Send Echo request packet.
					 */
					Send_Echo_Req_చట్రం(InstancePtr);
				}
			}
		}

		/*
		 * Check for IP type.
		 */
		లేకపోతే ఒకవేళ (Xil_Ntohs(*(Rx_చట్రం_Ptr + ETHER_PROTO_TYPE_LOC)) ==
						XEL_ETHER_PROTO_TYPE_IP) {

			/*
			 * Calculate checksum.
			 */
			Check_కూడిక = Check_కూడిక_Calculation(Rx_చట్రం_Ptr,
							ICMP_దత్తాంశం_ప్రారంభం_LOC,
							ICMP_దత్తాంశం_క్షేత్రం_LEN);

			/*
			 * Verify checksum, echo reply, identifier number and
			 * sequence number of the received packet.
			 */
			ఒకవేళ ((Check_కూడిక == CORRECT_CHECKSUM_విలువ) &&
			(Xil_Ntohs(*(Rx_చట్రం_Ptr + ICMP_ECHO_క్షేత్రం_LOC)) == ECHO_జవాబు) &&
			(Xil_Ntohs(*(Rx_చట్రం_Ptr + ICMP_IDEN_క్షేత్రం_LOC)) == IDEN_అంకె) &&
			(Xil_Ntohs(*(Rx_చట్రం_Ptr + (ICMP_SEQ_NO_LOC))) == Seq_అంకె)) {

				/*
				 * Verify data in the received packet with known
				 * data.
				 */
				తాత్కాలిక_Ptr = Icmp_దత్తాంశం;
				సరిపోలిక = Compare_దత్తాంశం(Rx_చట్రం_Ptr,
						తాత్కాలిక_Ptr, ICMP_తెలిసిన_దత్తాంశం_LOC,
							0, ICMP_తెలిసిన_దత్తాంశం_LEN);
				ఒకవేళ (సరిపోలిక == XST_FAILURE) {
					దత్తాంశం_Wrong = 1;
				}
			}
			ఒకవేళ (దత్తాంశం_Wrong != 1) {
				xil_printf("Packet No: %d ",
				అంకె_యొక్క_PING_REQ_PKTS - అంకె_యొక్క_Ping_Req_Pkts);
				xil_printf("Seq NO %d Echo Packet received\r\n",
								Seq_అంకె);
				తిరిగి XST_SUCCESS;
			}
		}
	}
	తిరిగి XST_FAILURE;
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
		కూడిక = కూడిక + Xil_Htons(*(Rx_చట్రం_Ptr + సూచీ));
		సూచీ++;
	}

	/*
	 * Add upper 16 bits to lower 16 bits.
	 */
	Check_కూడిక = కూడిక;
	కూడిక = కూడిక>>16;
	Check_కూడిక = కూడిక + Check_కూడిక;
	తిరిగి Check_కూడిక;
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
స్థిర పూర్ణాంకం Compare_దత్తాంశం(u16 *LhsPtr, u16 *RhsPtr, పూర్ణాంకం LhsLoc, పూర్ణాంకం RhsLoc,
								పూర్ణాంకం లెక్క_2)
{
	పూర్ణాంకం ఫలితం;
	అయితే (లెక్క_2--) {
		ఒకవేళ (*(LhsPtr + LhsLoc + లెక్క_2) == *(RhsPtr + RhsLoc + లెక్క_2)) {
			ఫలితం = XST_SUCCESS;
		} లేకపోతే {
			ఫలితం = XST_FAILURE;
			ఆపు;
		}
	}
	తిరిగి ఫలితం;
}
