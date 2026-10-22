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

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

خارجي XEmacLite_Config XEmac_Lite_Config_جدول;

/************************** Variable Definitions *****************************/

/*
 * Instance of the driver
 */
ساكن XEmacLite EmacLite;


/*
 * Change this parameter to limit the number of ping requests sent by this
 * program.
 */
#وصف_ڪريو انگ_جو_PING_REQ_PKTS	100	/* Number of ping req it generates */

#وصف_ڪريو ECHO_جواب		0x00	/* Echo reply */
#وصف_ڪريو HW_TYPE			0x01	/* Hardware type (10/100 Mbps) */
#وصف_ڪريو ARP_REQUEST 		0x01	/* ARP Request bits in Rx packet */
#وصف_ڪريو ARP_جواب 		0x02 	/* ARP status bits indicating reply */
#وصف_ڪريو IDEN_انگ		0x02	/* ICMP identifier number */
#وصف_ڪريو IP_نسخو		0x0604	/* IP version ipv4/ipv6 */
#وصف_ڪريو نشر_ADDR 		0xFFFF 	/* Broadcast Address */
#وصف_ڪريو CORRECT_CHECKSUM_قدر	0xFFFF	/* Correct checksum value */
#وصف_ڪريو ARP_REQ_PKT_سائيز	0x2A	/* ARP request packet size */
#وصف_ڪريو ICMP_PKT_سائيز 		0x4A	/* ICMP packet length 74 Bytes
					including Src and dest MAC Add */
#وصف_ڪريو IP_ADDR_سائيز		4	/* IP Address size in Bytes */
#وصف_ڪريو انگ_RX_PACK_CHECK_REQ	10	/* Max num of Rx pack to be checked
					before sending another request */
#وصف_ڪريو انگ_PACK_CHECK_RX_PACK	100	/* Max number of pack to be checked
					before to identify a Rx packet */
#وصف_ڪريو DELAY			5000000 /* Used to introduce delay */

/*
 * Definitions for the locations and length of some of the fields in a
 * IP packet. The lengths are defined in Half-Words (2 bytes).
 */

#وصف_ڪريو SRC_MAC_ADDR_LOC	3	/* Src MAC address location */
#وصف_ڪريو MAC_ADDR_LEN 		3	/* MAC address length */
#وصف_ڪريو ETHER_PROTO_TYPE_LOC	6	/* Ethernet Proto type loc */

#وصف_ڪريو IP_ADDR_LEN 		2	/* Size of IP address */
#وصف_ڪريو IP_شروعات_LOC 		7	/* IP header start location */
#وصف_ڪريو IP_سرو_INFO_LEN	7	/* IP header information length */
#وصف_ڪريو IP_سرو_LEN 		10 	/* IP header length */
#وصف_ڪريو IP_CHECKSUM_LOC		12	/* IP header checksum location */
#وصف_ڪريو IP_REQ_SRC_IP_LOC 	13	/* Src IP add loc of ICMP req */
#وصف_ڪريو IP_REQ_DEST_IP_LOC	15	/* Dest IP add loc of ICMP req */

#وصف_ڪريو ICMP_معلوم_معلومات_LEN	64	/* ICMP known data length */
#وصف_ڪريو ICMP_ECHO_ميدان_LOC 	17	/* Echo field loc */
#وصف_ڪريو ICMP_معلومات_شروعات_LOC 	17	/* Data field start location */
#وصف_ڪريو ICMP_معلومات_LEN 		18	/* ICMP data length */
#وصف_ڪريو ICMP_معلومات_CHECKSUM_LOC	18	/* ICMP data checksum location */
#وصف_ڪريو ICMP_IDEN_ميدان_LOC	19	/* Identifier field loc */
#وصف_ڪريو ICMP_معلومات_LOC 		19	/* ICMP data loc including
					identifier number and sequence number */
#وصف_ڪريو ICMP_SEQ_NO_LOC		20	/* sequence number location */
#وصف_ڪريو ICMP_معلومات_ميدان_LEN 	20 	/* Data field length */
#وصف_ڪريو ICMP_معلوم_معلومات_LOC	21	/* ICMP known data start loc */

#وصف_ڪريو ARP_REQ_حالت_LOC 	10	/* ARP request loc */
#وصف_ڪريو ARP_REQ_SRC_IP_LOC 	14	/* Src IP add loc of ARP req Packet */

/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/

ساكن صحيح EmacLitePingReqExample(u16 DeviceId);

ساكن فراغ Send_Arp_Req_چوکٺو(XEmacLite *InstancePtr);

ساكن فراغ Send_Echo_Req_چوکٺو(XEmacLite *InstancePtr);

ساكن صحيح Process_Recv_چوکٺو(XEmacLite *InstancePtr);

ساكن u16 Check_جوڙ_Calculation(u16 *Rx_چوکٺو_Ptr16, صحيح شروعات_Loc, صحيح ڊيگهائي);

ساكن صحيح Compare_معلومات(u16 *LhsPtr, u16 *RhsPtr, صحيح LhsLoc, صحيح RhsLoc,
			صحيح ڳڻپ_2);

/************************** Variable Definitions *****************************/

/*
 * Set up a local MAC address.
 */
ساكن u8 LocalMacAddr[XEL_MAC_ADDR_سائيز] =
{
	0x00, 0x0A, 0x35, 0x03, 0x02, 0x01
};

/*
 * The IP address was set to 172.16.63.121. User need to set a free IP address
 * based on the network on which this example is to be run.
 */
ساكن u8 Local_Ip_پتو[IP_ADDR_سائيز] =
{
	192, 168, 1, 26
};

/*
 * Set up a Destination IP address. Currently it is set to 172.16.63.61.
 */
/* ifconfig enp1s0 172.16.63.61 netmask 255.255.255.0 up */
ساكن u8 Dest_Ip_پتو[IP_ADDR_سائيز] =
{
	192, 168, 1, 25
};

ساكن u16 DestMacAddr[MAC_ADDR_LEN]; 	/* Destination MAC Address */
ساكن XEmacLite EmacLiteInstance;	/* Instance of the EmacLite driver */

/*
 * Known data transmitted in Echo request.
 */
u16 Icmp_معلومات[ICMP_معلوم_معلومات_LEN] =
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
u16 Ip_سرو_Info[IP_سرو_INFO_LEN] =
{
	0x0800,	0x4500, 0x003C,	0x5566,	0x0000,	0x8001, 0x0000
};

/*
 * Buffers used for Transmission and Reception of Packets. These are declared as
 * global so that they are not a part of the stack.
 */
ساكن u8 Rx_چوکٺو[XEL_MAX_چوکٺو_سائيز];
ساكن u8 Tx_چوکٺو[XEL_MAX_چوکٺو_سائيز];

/*
 * Variable used to indicate the length of the received frame.
 */
خارجي متطاير u32 Recv_چوکٺو_ڊيگهائي;

/*
 * Variable used to indicate the sequence number of the ICMP(echo) packet.
 */
صحيح Seq_انگ;

/*
 * Variable used to indicate the number of ping request packets to be send.
 */
صحيح انگ_جو_Ping_Req_Pkts;

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
صحيح مکيه()
{
	صحيح حالت;

	/*
	 * Run the EmacLite Ping request example.
	 */
	حالت = EmacLitePingReqExample(EMAC_DEVICE_ID);
	إذا (حالت != XST_SUCCESS) {
		xil_printf("Emaclite ping request Example Failed\r\n");
		أرجع XST_FAILURE;
	}

	xil_printf("Successfully ran Emaclite ping request Example\r\n");
	أرجع XST_SUCCESS;
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
ساكن صحيح EmacLitePingReqExample(u16 DeviceId)
{
	صحيح حالت;
	صحيح اشاريو;
	صحيح ڳڻپ_2;
	صحيح Echo_جواب_حالت;
	XEmacLite_Config *ConfigPtr;
	XEmacLite *EmacLiteInstPtr = &EmacLiteInstance;
	Seq_انگ = 0;
	Recv_چوکٺو_ڊيگهائي = 0;
	Echo_جواب_حالت = XST_FAILURE;
	انگ_جو_Ping_Req_Pkts = انگ_جو_PING_REQ_PKTS;

	/*
	 * Initialize the EmacLite device.
	 */
	ConfigPtr = &XEmac_Lite_Config_جدول;
	إذا (ConfigPtr == عدم) {
		أرجع -1;
	}
	ConfigPtr->بنياد_پتو = (UINTPTR *) 0X44000;
	ConfigPtr->RxPingPong = XPAR_EMACLITE_0_RX_PING_PONG;
	ConfigPtr->MdioInclude = XPAR_EMACLITE_0_INCLUDE_MDIO;
	ConfigPtr->TxPingPong = XPAR_EMACLITE_0_TX_PING_PONG;
#إذا 0
	log_debug("\n ConfigPtr: BaseAddress: %x", ConfigPtr->بنياد_پتو);
	log_debug("\n ConfigPtr: DeviceId: %x", ConfigPtr->DeviceId);
	log_debug("\n ConfigPtr: TxPingPong: %x", ConfigPtr->TxPingPong);
	log_debug("\n ConfigPtr: RxPingPong: %x", ConfigPtr->RxPingPong);
	log_debug("\n ConfigPtr: MdioInclude: %x", ConfigPtr->MdioInclude);
	log_debug("\n ConfigPtr: Loopback: %x", ConfigPtr->Loopback);
#جيڪڏهن_پورو	
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
	طالما (انگ_جو_Ping_Req_Pkts--) {

		/*
		 * Introduce delay.
		 */
		ڳڻپ_2 = DELAY;
		طالما (ڳڻپ_2--) {
		}

		/*
		 * Send an ARP or an ICMP packet based on receive packet.
		 */
		إذا (Seq_انگ == 0) {
			Send_Arp_Req_چوکٺو(EmacLiteInstPtr);
		} وإلا {
			Send_Echo_Req_چوکٺو(EmacLiteInstPtr);
		}

		/*
		 * Check next 10 packets for the correct reply.
		 */
		اشاريو = انگ_RX_PACK_CHECK_REQ;
		طالما (اشاريو--) {

			/*
			 * Wait for a Receive packet.
			 */
			ڳڻپ_2 = انگ_PACK_CHECK_RX_PACK;
			طالما (Recv_چوکٺو_ڊيگهائي == 0) {
				Recv_چوکٺو_ڊيگهائي = XEmacLite_Recv(
							EmacLiteInstPtr,
							(u8 *)Rx_چوکٺو);

				/*
				 * To avoid infinite loop when no packet is
				 * received.
				 */
				إذا (ڳڻپ_2-- == 0) {
					اكسر;
				}
			}

			/*
			 * Process the Receive frame.
			 */
			إذا (Recv_چوکٺو_ڊيگهائي != 0) {
				Echo_جواب_حالت = Process_Recv_چوکٺو(
							EmacLiteInstPtr);
			}
			Recv_چوکٺو_ڊيگهائي = 0;

			/*
			 * Comes out of loop when an echo reply packet is
			 * received.
			 */
			إذا (Echo_جواب_حالت == XST_SUCCESS) {
				اكسر;
			}
		}

		/*
		 * If no echo reply packet is received, it reports
		 * request timed out.
		 */
		إذا (Echo_جواب_حالت == XST_FAILURE) {
			xil_printf("Packet No: %d",
				انگ_جو_PING_REQ_PKTS - انگ_جو_Ping_Req_Pkts);
			xil_printf(" Seq NO %d Request timed out\r\n",
							Seq_انگ);
		}
	}
	أرجع XST_SUCCESS;
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
ساكن فراغ Send_Arp_Req_چوکٺو(XEmacLite *InstancePtr)
{
	u16 *عارضي_Ptr;
	u16 *Tx_چوکٺو_Ptr;
	u32 ايندڙ_Tx_Buff_بنياد_Addr;
	صحيح اشاريو;

	Tx_چوکٺو_Ptr = (u16 *)Tx_چوکٺو;

	/*
	 * Determine the next expected transmit buffer base address.
	 */
	ايندڙ_Tx_Buff_بنياد_Addr = XEmac_Lite_ايندڙ_Transmit_Addr(InstancePtr);

	/*
	 * Add broadcast address.
	 */
	اشاريو = MAC_ADDR_LEN;
	طالما (اشاريو--) {
		*Tx_چوکٺو_Ptr++ = نشر_ADDR;
	}

	/*
	 * Add local MAC address.
	 */
	اشاريو = 0;
	عارضي_Ptr = (u16 *)LocalMacAddr;
	طالما (اشاريو < MAC_ADDR_LEN) {
		*Tx_چوکٺو_Ptr++ = *(عارضي_Ptr + اشاريو);
		اشاريو++;
	}

	/*
	 * Add
	 * 	- Ethernet proto type.
	 *	- Hardware Type
	 *	- Protocol IP Type
	 *	- IP version (IPv6/IPv4)
	 *	- ARP Request
	 */
	*Tx_چوکٺو_Ptr++ = Xil_Htons(XEL_ETHER_PROTO_TYPE_ARP);
	*Tx_چوکٺو_Ptr++ = Xil_Htons(HW_TYPE);
	*Tx_چوکٺو_Ptr++ = Xil_Htons(XEL_ETHER_PROTO_TYPE_IP);
	*Tx_چوکٺو_Ptr++ = Xil_Htons(IP_نسخو);
	*Tx_چوکٺو_Ptr++ = Xil_Htons(ARP_REQUEST);

	/*
	 * Add local MAC address.
	 */
	اشاريو = 0;
	عارضي_Ptr = (u16 *)LocalMacAddr;
	طالما (اشاريو < MAC_ADDR_LEN) {
		*Tx_چوکٺو_Ptr++ = *(عارضي_Ptr + اشاريو);
		اشاريو++;
	}

	/*
	 * Add local IP address.
	 */
	اشاريو = 0;
	عارضي_Ptr = (u16 *)Local_Ip_پتو;
	طالما (اشاريو < IP_ADDR_LEN) {
		*Tx_چوکٺو_Ptr++ = *(عارضي_Ptr + اشاريو);
		اشاريو++;
	}

	/*
	 * Fills 6 bytes of information with zeros as per protocol.
	 */
	اشاريو = 0;
	طالما (اشاريو < 3) {
		*Tx_چوکٺو_Ptr++ = 0x0000;
		اشاريو++;
	}

	/*
	 * Add Destination IP address.
	 */
	اشاريو = 0;
	عارضي_Ptr = (u16 *)Dest_Ip_پتو;
	طالما (اشاريو < IP_ADDR_LEN) {
		*Tx_چوکٺو_Ptr++ = *(عارضي_Ptr + اشاريو);
		اشاريو++;
	}

	/*
	 * Transmit the Frame.
	 */
	XEmacLite_Send(InstancePtr, (u8 *)&Tx_چوکٺو, ARP_REQ_PKT_سائيز);
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
ساكن فراغ Send_Echo_Req_چوکٺو(XEmacLite *InstancePtr)
{
	u16 *عارضي_Ptr;
	u16 *Tx_چوکٺو_Ptr;
	u16 *Rx_چوکٺو_Ptr;
	u16 Check_جوڙ;
	u32 ايندڙ_Tx_Buff_بنياد_Addr;
	صحيح اشاريو;

	Tx_چوکٺو_Ptr = (u16 *)Tx_چوکٺو;
	Rx_چوکٺو_Ptr = (u16 *)Rx_چوکٺو;

	/*
	 * Determine the next expected transmit buffer base address.
	 */
	ايندڙ_Tx_Buff_بنياد_Addr = XEmac_Lite_ايندڙ_Transmit_Addr(InstancePtr);

	/*
	 * Add Destination MAC Address.
	 */
	اشاريو = MAC_ADDR_LEN;
	طالما (اشاريو--) {
		*(Tx_چوکٺو_Ptr + اشاريو) = *(DestMacAddr + اشاريو);
	}

	/*
	 * Add Source MAC Address.
	 */
	اشاريو = MAC_ADDR_LEN;
	عارضي_Ptr = (u16 *)LocalMacAddr;
	طالما (اشاريو--) {
		*(Tx_چوکٺو_Ptr + (اشاريو + SRC_MAC_ADDR_LOC )) =
							*(عارضي_Ptr + اشاريو);
	}

	/*
	 * Add IP header information.
	 */
	اشاريو = IP_شروعات_LOC;
	طالما (اشاريو--) {
		*(Tx_چوکٺو_Ptr + (اشاريو + ETHER_PROTO_TYPE_LOC )) =
				Xil_Htons(*(Ip_سرو_Info + اشاريو));
	}

	/*
	 * Add Source IP address.
	 */
	اشاريو = IP_ADDR_LEN;
	عارضي_Ptr = (u16 *)Local_Ip_پتو;
	طالما (اشاريو--) {
		*(Tx_چوکٺو_Ptr + (اشاريو + IP_REQ_SRC_IP_LOC )) =
						*(عارضي_Ptr + اشاريو);
	}

	/*
	 * Add Destination IP address.
	 */
	اشاريو = IP_ADDR_LEN;
	عارضي_Ptr = (u16 *)Dest_Ip_پتو;
	طالما (اشاريو--) {
		*(Tx_چوکٺو_Ptr + (اشاريو + IP_REQ_DEST_IP_LOC )) =
						*(عارضي_Ptr + اشاريو);
	}

	/*
	 * Checksum is calculated for IP field and added in the frame.
	 */
	Check_جوڙ = Check_جوڙ_Calculation((u16 *)Tx_چوکٺو, IP_شروعات_LOC,
							IP_سرو_LEN);
	Check_جوڙ = ~Check_جوڙ;
	*(Tx_چوکٺو_Ptr + IP_CHECKSUM_LOC) = Xil_Htons(Check_جوڙ);

	/*
	 * Add echo field information.
	 */
	*(Tx_چوکٺو_Ptr + ICMP_ECHO_ميدان_LOC) = Xil_Htons(XEL_ETHER_PROTO_TYPE_IP);

	/*
	 * Checksum value is initialized to zeros.
	 */
	*(Tx_چوکٺو_Ptr + ICMP_معلومات_LEN) = 0x0000;

	/*
	 * Add identifier and sequence number to the frame.
	 */
	*(Tx_چوکٺو_Ptr + ICMP_IDEN_ميدان_LOC) = (IDEN_انگ);
	*(Tx_چوکٺو_Ptr + (ICMP_IDEN_ميدان_LOC + 1)) = Xil_Htons((u16)(++Seq_انگ));

	/*
	 * Add known data to the frame.
	 */
	اشاريو = ICMP_معلوم_معلومات_LEN;
	طالما (اشاريو--) {
		*(Tx_چوکٺو_Ptr + (اشاريو + ICMP_معلوم_معلومات_LOC)) =
				Xil_Htons(*(Icmp_معلومات + اشاريو));
	}

	/*
	 * Checksum is calculated for Data Field and added in the frame.
	 */
	Check_جوڙ = Check_جوڙ_Calculation((u16 *)Tx_چوکٺو, ICMP_معلومات_شروعات_LOC,
						ICMP_معلومات_ميدان_LEN );
	Check_جوڙ = ~Check_جوڙ;
	*(Tx_چوکٺو_Ptr + ICMP_معلومات_CHECKSUM_LOC) = Xil_Htons(Check_جوڙ);

	/*
	 * Transmit the Frame.
	 */
	XEmacLite_Send(InstancePtr, (u8 *)&Tx_چوکٺو, ICMP_PKT_سائيز);
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
ساكن صحيح Process_Recv_چوکٺو(XEmacLite *InstancePtr)
{
	u16 *Rx_چوکٺو_Ptr;
	u16 *عارضي_Ptr;
	u16 Check_جوڙ;
	صحيح اشاريو;
	صحيح ميلاپ = 0;
	صحيح معلومات_Wrong = 0;

	Rx_چوکٺو_Ptr = (u16 *)Rx_چوکٺو;
	عارضي_Ptr = (u16 *)LocalMacAddr;

	/*
	 * Check Dest Mac address of the packet with the LocalMac address.
	 */
	ميلاپ = Compare_معلومات(Rx_چوکٺو_Ptr, عارضي_Ptr, 0, 0, MAC_ADDR_LEN);
	إذا (ميلاپ == XST_SUCCESS) {

		/*
		 * Check ARP type.
		 */
		إذا (Xil_Ntohs(*(Rx_چوکٺو_Ptr + ETHER_PROTO_TYPE_LOC)) ==
				XEL_ETHER_PROTO_TYPE_ARP ) {

			/*
			 * Check ARP status.
			 */
			إذا (Xil_Ntohs(*(Rx_چوکٺو_Ptr + ARP_REQ_حالت_LOC)) == ARP_جواب) {

				/*
				 * Check destination IP address with
				 * packet's source IP address.
				 */
				عارضي_Ptr = (u16 *)Dest_Ip_پتو;
				ميلاپ = Compare_معلومات(Rx_چوکٺو_Ptr,
						عارضي_Ptr, ARP_REQ_SRC_IP_LOC,
						0, IP_ADDR_LEN);
				إذا (ميلاپ == XST_SUCCESS) {

					/*
					 * Copy src Mac address of the received
					 * packet.
					 */
					اشاريو = MAC_ADDR_LEN;
					عارضي_Ptr = (u16 *)DestMacAddr;
					طالما (اشاريو--) {
						*(عارضي_Ptr + اشاريو) =
							*(Rx_چوکٺو_Ptr +
							(SRC_MAC_ADDR_LOC +
								اشاريو));
					}

					/*
					 * Send Echo request packet.
					 */
					Send_Echo_Req_چوکٺو(InstancePtr);
				}
			}
		}

		/*
		 * Check for IP type.
		 */
		وإلا إذا (Xil_Ntohs(*(Rx_چوکٺو_Ptr + ETHER_PROTO_TYPE_LOC)) ==
						XEL_ETHER_PROTO_TYPE_IP) {

			/*
			 * Calculate checksum.
			 */
			Check_جوڙ = Check_جوڙ_Calculation(Rx_چوکٺو_Ptr,
							ICMP_معلومات_شروعات_LOC,
							ICMP_معلومات_ميدان_LEN);

			/*
			 * Verify checksum, echo reply, identifier number and
			 * sequence number of the received packet.
			 */
			إذا ((Check_جوڙ == CORRECT_CHECKSUM_قدر) &&
			(Xil_Ntohs(*(Rx_چوکٺو_Ptr + ICMP_ECHO_ميدان_LOC)) == ECHO_جواب) &&
			(Xil_Ntohs(*(Rx_چوکٺو_Ptr + ICMP_IDEN_ميدان_LOC)) == IDEN_انگ) &&
			(Xil_Ntohs(*(Rx_چوکٺو_Ptr + (ICMP_SEQ_NO_LOC))) == Seq_انگ)) {

				/*
				 * Verify data in the received packet with known
				 * data.
				 */
				عارضي_Ptr = Icmp_معلومات;
				ميلاپ = Compare_معلومات(Rx_چوکٺو_Ptr,
						عارضي_Ptr, ICMP_معلوم_معلومات_LOC,
							0, ICMP_معلوم_معلومات_LEN);
				إذا (ميلاپ == XST_FAILURE) {
					معلومات_Wrong = 1;
				}
			}
			إذا (معلومات_Wrong != 1) {
				xil_printf("Packet No: %d ",
				انگ_جو_PING_REQ_PKTS - انگ_جو_Ping_Req_Pkts);
				xil_printf("Seq NO %d Echo Packet received\r\n",
								Seq_انگ);
				أرجع XST_SUCCESS;
			}
		}
	}
	أرجع XST_FAILURE;
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
		جوڙ = جوڙ + Xil_Htons(*(Rx_چوکٺو_Ptr + اشاريو));
		اشاريو++;
	}

	/*
	 * Add upper 16 bits to lower 16 bits.
	 */
	Check_جوڙ = جوڙ;
	جوڙ = جوڙ>>16;
	Check_جوڙ = جوڙ + Check_جوڙ;
	أرجع Check_جوڙ;
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
ساكن صحيح Compare_معلومات(u16 *LhsPtr, u16 *RhsPtr, صحيح LhsLoc, صحيح RhsLoc,
								صحيح ڳڻپ_2)
{
	صحيح نتيجو;
	طالما (ڳڻپ_2--) {
		إذا (*(LhsPtr + LhsLoc + ڳڻپ_2) == *(RhsPtr + RhsLoc + ڳڻپ_2)) {
			نتيجو = XST_SUCCESS;
		} وإلا {
			نتيجو = XST_FAILURE;
			اكسر;
		}
	}
	أرجع نتيجو;
}
