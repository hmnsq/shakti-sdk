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
#تعریف_کرو EMAC_DEVICE_ID			240
#تعریف_کرو ETH_ادھار_REG 0x44000
متطاير بنانشانی صحيح* eth_ادھار_reg = ETH_ادھار_REG;

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
#تعریف_کرو عدد_دا_PING_REQ_PKTS	100	/* Number of ping req it generates */

#تعریف_کرو ECHO_جواب		0x00	/* Echo reply */
#تعریف_کرو HW_TYPE			0x01	/* Hardware type (10/100 Mbps) */
#تعریف_کرو ARP_REQUEST 		0x01	/* ARP Request bits in Rx packet */
#تعریف_کرو ARP_جواب 		0x02 	/* ARP status bits indicating reply */
#تعریف_کرو IDEN_عدد		0x02	/* ICMP identifier number */
#تعریف_کرو IP_نسخہ		0x0604	/* IP version ipv4/ipv6 */
#تعریف_کرو نشر_ADDR 		0xFFFF 	/* Broadcast Address */
#تعریف_کرو CORRECT_CHECKSUM_قدر	0xFFFF	/* Correct checksum value */
#تعریف_کرو ARP_REQ_PKT_ناپ	0x2A	/* ARP request packet size */
#تعریف_کرو ICMP_PKT_ناپ 		0x4A	/* ICMP packet length 74 Bytes
					including Src and dest MAC Add */
#تعریف_کرو IP_ADDR_ناپ		4	/* IP Address size in Bytes */
#تعریف_کرو عدد_RX_PACK_CHECK_REQ	10	/* Max num of Rx pack to be checked
					before sending another request */
#تعریف_کرو عدد_PACK_CHECK_RX_PACK	100	/* Max number of pack to be checked
					before to identify a Rx packet */
#تعریف_کرو DELAY			5000000 /* Used to introduce delay */

/*
 * Definitions for the locations and length of some of the fields in a
 * IP packet. The lengths are defined in Half-Words (2 bytes).
 */

#تعریف_کرو SRC_MAC_ADDR_LOC	3	/* Src MAC address location */
#تعریف_کرو MAC_ADDR_LEN 		3	/* MAC address length */
#تعریف_کرو ETHER_PROTO_TYPE_LOC	6	/* Ethernet Proto type loc */

#تعریف_کرو IP_ADDR_LEN 		2	/* Size of IP address */
#تعریف_کرو IP_شروع_LOC 		7	/* IP header start location */
#تعریف_کرو IP_سرخی_INFO_LEN	7	/* IP header information length */
#تعریف_کرو IP_سرخی_LEN 		10 	/* IP header length */
#تعریف_کرو IP_CHECKSUM_LOC		12	/* IP header checksum location */
#تعریف_کرو IP_REQ_SRC_IP_LOC 	13	/* Src IP add loc of ICMP req */
#تعریف_کرو IP_REQ_DEST_IP_LOC	15	/* Dest IP add loc of ICMP req */

#تعریف_کرو ICMP_معلوم_انکڑے_LEN	64	/* ICMP known data length */
#تعریف_کرو ICMP_ECHO_میدان_LOC 	17	/* Echo field loc */
#تعریف_کرو ICMP_انکڑے_شروع_LOC 	17	/* Data field start location */
#تعریف_کرو ICMP_انکڑے_LEN 		18	/* ICMP data length */
#تعریف_کرو ICMP_انکڑے_CHECKSUM_LOC	18	/* ICMP data checksum location */
#تعریف_کرو ICMP_IDEN_میدان_LOC	19	/* Identifier field loc */
#تعریف_کرو ICMP_انکڑے_LOC 		19	/* ICMP data loc including
					identifier number and sequence number */
#تعریف_کرو ICMP_SEQ_NO_LOC		20	/* sequence number location */
#تعریف_کرو ICMP_انکڑے_میدان_LEN 	20 	/* Data field length */
#تعریف_کرو ICMP_معلوم_انکڑے_LOC	21	/* ICMP known data start loc */

#تعریف_کرو ARP_REQ_حالت_LOC 	10	/* ARP request loc */
#تعریف_کرو ARP_REQ_SRC_IP_LOC 	14	/* Src IP add loc of ARP req Packet */

/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/

ساكن صحيح EmacLitePingReqExample(u16 DeviceId);

ساكن فراغ Send_Arp_Req_چوکھٹا(XEmacLite *InstancePtr);

ساكن فراغ Send_Echo_Req_چوکھٹا(XEmacLite *InstancePtr);

ساكن صحيح Process_Recv_چوکھٹا(XEmacLite *InstancePtr);

ساكن u16 Check_جوڑ_Calculation(u16 *Rx_چوکھٹا_Ptr16, صحيح شروع_Loc, صحيح لمائی);

ساكن صحيح Compare_انکڑے(u16 *LhsPtr, u16 *RhsPtr, صحيح LhsLoc, صحيح RhsLoc,
			صحيح گنتی_2);

/************************** Variable Definitions *****************************/

/*
 * Set up a local MAC address.
 */
ساكن u8 LocalMacAddr[XEL_MAC_ADDR_ناپ] =
{
	0x00, 0x0A, 0x35, 0x03, 0x02, 0x01
};

/*
 * The IP address was set to 172.16.63.121. User need to set a free IP address
 * based on the network on which this example is to be run.
 */
ساكن u8 Local_Ip_پتہ[IP_ADDR_ناپ] =
{
	192, 168, 1, 26
};

/*
 * Set up a Destination IP address. Currently it is set to 172.16.63.61.
 */
/* ifconfig enp1s0 172.16.63.61 netmask 255.255.255.0 up */
ساكن u8 Dest_Ip_پتہ[IP_ADDR_ناپ] =
{
	192, 168, 1, 25
};

ساكن u16 DestMacAddr[MAC_ADDR_LEN]; 	/* Destination MAC Address */
ساكن XEmacLite EmacLiteInstance;	/* Instance of the EmacLite driver */

/*
 * Known data transmitted in Echo request.
 */
u16 Icmp_انکڑے[ICMP_معلوم_انکڑے_LEN] =
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
u16 Ip_سرخی_Info[IP_سرخی_INFO_LEN] =
{
	0x0800,	0x4500, 0x003C,	0x5566,	0x0000,	0x8001, 0x0000
};

/*
 * Buffers used for Transmission and Reception of Packets. These are declared as
 * global so that they are not a part of the stack.
 */
ساكن u8 Rx_چوکھٹا[XEL_MAX_چوکھٹا_ناپ];
ساكن u8 Tx_چوکھٹا[XEL_MAX_چوکھٹا_ناپ];

/*
 * Variable used to indicate the length of the received frame.
 */
خارجي متطاير u32 Recv_چوکھٹا_لمائی;

/*
 * Variable used to indicate the sequence number of the ICMP(echo) packet.
 */
صحيح Seq_عدد;

/*
 * Variable used to indicate the number of ping request packets to be send.
 */
صحيح عدد_دا_Ping_Req_Pkts;

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
صحيح مکھ()
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
	صحيح اشاریہ;
	صحيح گنتی_2;
	صحيح Echo_جواب_حالت;
	XEmacLite_Config *ConfigPtr;
	XEmacLite *EmacLiteInstPtr = &EmacLiteInstance;
	Seq_عدد = 0;
	Recv_چوکھٹا_لمائی = 0;
	Echo_جواب_حالت = XST_FAILURE;
	عدد_دا_Ping_Req_Pkts = عدد_دا_PING_REQ_PKTS;

	/*
	 * Initialize the EmacLite device.
	 */
	ConfigPtr = &XEmac_Lite_Config_جدول;
	إذا (ConfigPtr == عدم) {
		أرجع -1;
	}
	ConfigPtr->ادھار_پتہ = (UINTPTR *) 0X44000;
	ConfigPtr->RxPingPong = XPAR_EMACLITE_0_RX_PING_PONG;
	ConfigPtr->MdioInclude = XPAR_EMACLITE_0_INCLUDE_MDIO;
	ConfigPtr->TxPingPong = XPAR_EMACLITE_0_TX_PING_PONG;
#إذا 0
	log_debug("\n ConfigPtr: BaseAddress: %x", ConfigPtr->ادھار_پتہ);
	log_debug("\n ConfigPtr: DeviceId: %x", ConfigPtr->DeviceId);
	log_debug("\n ConfigPtr: TxPingPong: %x", ConfigPtr->TxPingPong);
	log_debug("\n ConfigPtr: RxPingPong: %x", ConfigPtr->RxPingPong);
	log_debug("\n ConfigPtr: MdioInclude: %x", ConfigPtr->MdioInclude);
	log_debug("\n ConfigPtr: Loopback: %x", ConfigPtr->Loopback);
#جے_انت	
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
	طالما (عدد_دا_Ping_Req_Pkts--) {

		/*
		 * Introduce delay.
		 */
		گنتی_2 = DELAY;
		طالما (گنتی_2--) {
		}

		/*
		 * Send an ARP or an ICMP packet based on receive packet.
		 */
		إذا (Seq_عدد == 0) {
			Send_Arp_Req_چوکھٹا(EmacLiteInstPtr);
		} وإلا {
			Send_Echo_Req_چوکھٹا(EmacLiteInstPtr);
		}

		/*
		 * Check next 10 packets for the correct reply.
		 */
		اشاریہ = عدد_RX_PACK_CHECK_REQ;
		طالما (اشاریہ--) {

			/*
			 * Wait for a Receive packet.
			 */
			گنتی_2 = عدد_PACK_CHECK_RX_PACK;
			طالما (Recv_چوکھٹا_لمائی == 0) {
				Recv_چوکھٹا_لمائی = XEmacLite_Recv(
							EmacLiteInstPtr,
							(u8 *)Rx_چوکھٹا);

				/*
				 * To avoid infinite loop when no packet is
				 * received.
				 */
				إذا (گنتی_2-- == 0) {
					اكسر;
				}
			}

			/*
			 * Process the Receive frame.
			 */
			إذا (Recv_چوکھٹا_لمائی != 0) {
				Echo_جواب_حالت = Process_Recv_چوکھٹا(
							EmacLiteInstPtr);
			}
			Recv_چوکھٹا_لمائی = 0;

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
				عدد_دا_PING_REQ_PKTS - عدد_دا_Ping_Req_Pkts);
			xil_printf(" Seq NO %d Request timed out\r\n",
							Seq_عدد);
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
ساكن فراغ Send_Arp_Req_چوکھٹا(XEmacLite *InstancePtr)
{
	u16 *عارضی_Ptr;
	u16 *Tx_چوکھٹا_Ptr;
	u32 اگلا_Tx_Buff_ادھار_Addr;
	صحيح اشاریہ;

	Tx_چوکھٹا_Ptr = (u16 *)Tx_چوکھٹا;

	/*
	 * Determine the next expected transmit buffer base address.
	 */
	اگلا_Tx_Buff_ادھار_Addr = XEmac_Lite_اگلا_Transmit_Addr(InstancePtr);

	/*
	 * Add broadcast address.
	 */
	اشاریہ = MAC_ADDR_LEN;
	طالما (اشاریہ--) {
		*Tx_چوکھٹا_Ptr++ = نشر_ADDR;
	}

	/*
	 * Add local MAC address.
	 */
	اشاریہ = 0;
	عارضی_Ptr = (u16 *)LocalMacAddr;
	طالما (اشاریہ < MAC_ADDR_LEN) {
		*Tx_چوکھٹا_Ptr++ = *(عارضی_Ptr + اشاریہ);
		اشاریہ++;
	}

	/*
	 * Add
	 * 	- Ethernet proto type.
	 *	- Hardware Type
	 *	- Protocol IP Type
	 *	- IP version (IPv6/IPv4)
	 *	- ARP Request
	 */
	*Tx_چوکھٹا_Ptr++ = Xil_Htons(XEL_ETHER_PROTO_TYPE_ARP);
	*Tx_چوکھٹا_Ptr++ = Xil_Htons(HW_TYPE);
	*Tx_چوکھٹا_Ptr++ = Xil_Htons(XEL_ETHER_PROTO_TYPE_IP);
	*Tx_چوکھٹا_Ptr++ = Xil_Htons(IP_نسخہ);
	*Tx_چوکھٹا_Ptr++ = Xil_Htons(ARP_REQUEST);

	/*
	 * Add local MAC address.
	 */
	اشاریہ = 0;
	عارضی_Ptr = (u16 *)LocalMacAddr;
	طالما (اشاریہ < MAC_ADDR_LEN) {
		*Tx_چوکھٹا_Ptr++ = *(عارضی_Ptr + اشاریہ);
		اشاریہ++;
	}

	/*
	 * Add local IP address.
	 */
	اشاریہ = 0;
	عارضی_Ptr = (u16 *)Local_Ip_پتہ;
	طالما (اشاریہ < IP_ADDR_LEN) {
		*Tx_چوکھٹا_Ptr++ = *(عارضی_Ptr + اشاریہ);
		اشاریہ++;
	}

	/*
	 * Fills 6 bytes of information with zeros as per protocol.
	 */
	اشاریہ = 0;
	طالما (اشاریہ < 3) {
		*Tx_چوکھٹا_Ptr++ = 0x0000;
		اشاریہ++;
	}

	/*
	 * Add Destination IP address.
	 */
	اشاریہ = 0;
	عارضی_Ptr = (u16 *)Dest_Ip_پتہ;
	طالما (اشاریہ < IP_ADDR_LEN) {
		*Tx_چوکھٹا_Ptr++ = *(عارضی_Ptr + اشاریہ);
		اشاریہ++;
	}

	/*
	 * Transmit the Frame.
	 */
	XEmacLite_Send(InstancePtr, (u8 *)&Tx_چوکھٹا, ARP_REQ_PKT_ناپ);
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
ساكن فراغ Send_Echo_Req_چوکھٹا(XEmacLite *InstancePtr)
{
	u16 *عارضی_Ptr;
	u16 *Tx_چوکھٹا_Ptr;
	u16 *Rx_چوکھٹا_Ptr;
	u16 Check_جوڑ;
	u32 اگلا_Tx_Buff_ادھار_Addr;
	صحيح اشاریہ;

	Tx_چوکھٹا_Ptr = (u16 *)Tx_چوکھٹا;
	Rx_چوکھٹا_Ptr = (u16 *)Rx_چوکھٹا;

	/*
	 * Determine the next expected transmit buffer base address.
	 */
	اگلا_Tx_Buff_ادھار_Addr = XEmac_Lite_اگلا_Transmit_Addr(InstancePtr);

	/*
	 * Add Destination MAC Address.
	 */
	اشاریہ = MAC_ADDR_LEN;
	طالما (اشاریہ--) {
		*(Tx_چوکھٹا_Ptr + اشاریہ) = *(DestMacAddr + اشاریہ);
	}

	/*
	 * Add Source MAC Address.
	 */
	اشاریہ = MAC_ADDR_LEN;
	عارضی_Ptr = (u16 *)LocalMacAddr;
	طالما (اشاریہ--) {
		*(Tx_چوکھٹا_Ptr + (اشاریہ + SRC_MAC_ADDR_LOC )) =
							*(عارضی_Ptr + اشاریہ);
	}

	/*
	 * Add IP header information.
	 */
	اشاریہ = IP_شروع_LOC;
	طالما (اشاریہ--) {
		*(Tx_چوکھٹا_Ptr + (اشاریہ + ETHER_PROTO_TYPE_LOC )) =
				Xil_Htons(*(Ip_سرخی_Info + اشاریہ));
	}

	/*
	 * Add Source IP address.
	 */
	اشاریہ = IP_ADDR_LEN;
	عارضی_Ptr = (u16 *)Local_Ip_پتہ;
	طالما (اشاریہ--) {
		*(Tx_چوکھٹا_Ptr + (اشاریہ + IP_REQ_SRC_IP_LOC )) =
						*(عارضی_Ptr + اشاریہ);
	}

	/*
	 * Add Destination IP address.
	 */
	اشاریہ = IP_ADDR_LEN;
	عارضی_Ptr = (u16 *)Dest_Ip_پتہ;
	طالما (اشاریہ--) {
		*(Tx_چوکھٹا_Ptr + (اشاریہ + IP_REQ_DEST_IP_LOC )) =
						*(عارضی_Ptr + اشاریہ);
	}

	/*
	 * Checksum is calculated for IP field and added in the frame.
	 */
	Check_جوڑ = Check_جوڑ_Calculation((u16 *)Tx_چوکھٹا, IP_شروع_LOC,
							IP_سرخی_LEN);
	Check_جوڑ = ~Check_جوڑ;
	*(Tx_چوکھٹا_Ptr + IP_CHECKSUM_LOC) = Xil_Htons(Check_جوڑ);

	/*
	 * Add echo field information.
	 */
	*(Tx_چوکھٹا_Ptr + ICMP_ECHO_میدان_LOC) = Xil_Htons(XEL_ETHER_PROTO_TYPE_IP);

	/*
	 * Checksum value is initialized to zeros.
	 */
	*(Tx_چوکھٹا_Ptr + ICMP_انکڑے_LEN) = 0x0000;

	/*
	 * Add identifier and sequence number to the frame.
	 */
	*(Tx_چوکھٹا_Ptr + ICMP_IDEN_میدان_LOC) = (IDEN_عدد);
	*(Tx_چوکھٹا_Ptr + (ICMP_IDEN_میدان_LOC + 1)) = Xil_Htons((u16)(++Seq_عدد));

	/*
	 * Add known data to the frame.
	 */
	اشاریہ = ICMP_معلوم_انکڑے_LEN;
	طالما (اشاریہ--) {
		*(Tx_چوکھٹا_Ptr + (اشاریہ + ICMP_معلوم_انکڑے_LOC)) =
				Xil_Htons(*(Icmp_انکڑے + اشاریہ));
	}

	/*
	 * Checksum is calculated for Data Field and added in the frame.
	 */
	Check_جوڑ = Check_جوڑ_Calculation((u16 *)Tx_چوکھٹا, ICMP_انکڑے_شروع_LOC,
						ICMP_انکڑے_میدان_LEN );
	Check_جوڑ = ~Check_جوڑ;
	*(Tx_چوکھٹا_Ptr + ICMP_انکڑے_CHECKSUM_LOC) = Xil_Htons(Check_جوڑ);

	/*
	 * Transmit the Frame.
	 */
	XEmacLite_Send(InstancePtr, (u8 *)&Tx_چوکھٹا, ICMP_PKT_ناپ);
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
ساكن صحيح Process_Recv_چوکھٹا(XEmacLite *InstancePtr)
{
	u16 *Rx_چوکھٹا_Ptr;
	u16 *عارضی_Ptr;
	u16 Check_جوڑ;
	صحيح اشاریہ;
	صحيح میل = 0;
	صحيح انکڑے_Wrong = 0;

	Rx_چوکھٹا_Ptr = (u16 *)Rx_چوکھٹا;
	عارضی_Ptr = (u16 *)LocalMacAddr;

	/*
	 * Check Dest Mac address of the packet with the LocalMac address.
	 */
	میل = Compare_انکڑے(Rx_چوکھٹا_Ptr, عارضی_Ptr, 0, 0, MAC_ADDR_LEN);
	إذا (میل == XST_SUCCESS) {

		/*
		 * Check ARP type.
		 */
		إذا (Xil_Ntohs(*(Rx_چوکھٹا_Ptr + ETHER_PROTO_TYPE_LOC)) ==
				XEL_ETHER_PROTO_TYPE_ARP ) {

			/*
			 * Check ARP status.
			 */
			إذا (Xil_Ntohs(*(Rx_چوکھٹا_Ptr + ARP_REQ_حالت_LOC)) == ARP_جواب) {

				/*
				 * Check destination IP address with
				 * packet's source IP address.
				 */
				عارضی_Ptr = (u16 *)Dest_Ip_پتہ;
				میل = Compare_انکڑے(Rx_چوکھٹا_Ptr,
						عارضی_Ptr, ARP_REQ_SRC_IP_LOC,
						0, IP_ADDR_LEN);
				إذا (میل == XST_SUCCESS) {

					/*
					 * Copy src Mac address of the received
					 * packet.
					 */
					اشاریہ = MAC_ADDR_LEN;
					عارضی_Ptr = (u16 *)DestMacAddr;
					طالما (اشاریہ--) {
						*(عارضی_Ptr + اشاریہ) =
							*(Rx_چوکھٹا_Ptr +
							(SRC_MAC_ADDR_LOC +
								اشاریہ));
					}

					/*
					 * Send Echo request packet.
					 */
					Send_Echo_Req_چوکھٹا(InstancePtr);
				}
			}
		}

		/*
		 * Check for IP type.
		 */
		وإلا إذا (Xil_Ntohs(*(Rx_چوکھٹا_Ptr + ETHER_PROTO_TYPE_LOC)) ==
						XEL_ETHER_PROTO_TYPE_IP) {

			/*
			 * Calculate checksum.
			 */
			Check_جوڑ = Check_جوڑ_Calculation(Rx_چوکھٹا_Ptr,
							ICMP_انکڑے_شروع_LOC,
							ICMP_انکڑے_میدان_LEN);

			/*
			 * Verify checksum, echo reply, identifier number and
			 * sequence number of the received packet.
			 */
			إذا ((Check_جوڑ == CORRECT_CHECKSUM_قدر) &&
			(Xil_Ntohs(*(Rx_چوکھٹا_Ptr + ICMP_ECHO_میدان_LOC)) == ECHO_جواب) &&
			(Xil_Ntohs(*(Rx_چوکھٹا_Ptr + ICMP_IDEN_میدان_LOC)) == IDEN_عدد) &&
			(Xil_Ntohs(*(Rx_چوکھٹا_Ptr + (ICMP_SEQ_NO_LOC))) == Seq_عدد)) {

				/*
				 * Verify data in the received packet with known
				 * data.
				 */
				عارضی_Ptr = Icmp_انکڑے;
				میل = Compare_انکڑے(Rx_چوکھٹا_Ptr,
						عارضی_Ptr, ICMP_معلوم_انکڑے_LOC,
							0, ICMP_معلوم_انکڑے_LEN);
				إذا (میل == XST_FAILURE) {
					انکڑے_Wrong = 1;
				}
			}
			إذا (انکڑے_Wrong != 1) {
				xil_printf("Packet No: %d ",
				عدد_دا_PING_REQ_PKTS - عدد_دا_Ping_Req_Pkts);
				xil_printf("Seq NO %d Echo Packet received\r\n",
								Seq_عدد);
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
		جوڑ = جوڑ + Xil_Htons(*(Rx_چوکھٹا_Ptr + اشاریہ));
		اشاریہ++;
	}

	/*
	 * Add upper 16 bits to lower 16 bits.
	 */
	Check_جوڑ = جوڑ;
	جوڑ = جوڑ>>16;
	Check_جوڑ = جوڑ + Check_جوڑ;
	أرجع Check_جوڑ;
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
ساكن صحيح Compare_انکڑے(u16 *LhsPtr, u16 *RhsPtr, صحيح LhsLoc, صحيح RhsLoc,
								صحيح گنتی_2)
{
	صحيح نتیجہ;
	طالما (گنتی_2--) {
		إذا (*(LhsPtr + LhsLoc + گنتی_2) == *(RhsPtr + RhsLoc + گنتی_2)) {
			نتیجہ = XST_SUCCESS;
		} وإلا {
			نتیجہ = XST_FAILURE;
			اكسر;
		}
	}
	أرجع نتیجہ;
}
