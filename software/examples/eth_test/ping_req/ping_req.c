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

#ਅਨ੍ਤਰ੍ਭਾਵ "gpio.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "uart.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "traps.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "platform.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "eth_driver.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"




/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EMAC_DEVICE_ID			240
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ETH_ਅਧਾਰ_REG 0x44000
ਅਸਥਿਰ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ* eth_ਅਧਾਰ_reg = ETH_ਅਧਾਰ_REG;

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

ਬਾਹਰੀ XEmacLite_Config XEmac_Lite_Config_ਸਾਰਣੀ;

/************************** Variable Definitions *****************************/

/*
 * Instance of the driver
 */
ਸਥਿਰ XEmacLite EmacLite;


/*
 * Change this parameter to limit the number of ping requests sent by this
 * program.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਅੰਕ_ਦਾ_PING_REQ_PKTS	100	/* Number of ping req it generates */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ECHO_ਜਵਾਬ		0x00	/* Echo reply */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HW_TYPE			0x01	/* Hardware type (10/100 Mbps) */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ARP_REQUEST 		0x01	/* ARP Request bits in Rx packet */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ARP_ਜਵਾਬ 		0x02 	/* ARP status bits indicating reply */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IDEN_ਅੰਕ		0x02	/* ICMP identifier number */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IP_ਸੰਸਕਰਣ		0x0604	/* IP version ipv4/ipv6 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪ੍ਰਸਾਰਣ_ADDR 		0xFFFF 	/* Broadcast Address */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CORRECT_CHECKSUM_ਮੁੱਲ	0xFFFF	/* Correct checksum value */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ARP_REQ_PKT_ਮਾਪ	0x2A	/* ARP request packet size */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ICMP_PKT_ਮਾਪ 		0x4A	/* ICMP packet length 74 Bytes
					including Src and dest MAC Add */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IP_ADDR_ਮਾਪ		4	/* IP Address size in Bytes */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਅੰਕ_RX_PACK_CHECK_REQ	10	/* Max num of Rx pack to be checked
					before sending another request */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਅੰਕ_PACK_CHECK_RX_PACK	100	/* Max number of pack to be checked
					before to identify a Rx packet */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DELAY			5000000 /* Used to introduce delay */

/*
 * Definitions for the locations and length of some of the fields in a
 * IP packet. The lengths are defined in Half-Words (2 bytes).
 */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRC_MAC_ADDR_LOC	3	/* Src MAC address location */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAC_ADDR_LEN 		3	/* MAC address length */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ETHER_PROTO_TYPE_LOC	6	/* Ethernet Proto type loc */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IP_ADDR_LEN 		2	/* Size of IP address */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IP_ਸ਼ੁਰੂ_LOC 		7	/* IP header start location */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IP_ਸਿਰਲੇਖ_INFO_LEN	7	/* IP header information length */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IP_ਸਿਰਲੇਖ_LEN 		10 	/* IP header length */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IP_CHECKSUM_LOC		12	/* IP header checksum location */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IP_REQ_SRC_IP_LOC 	13	/* Src IP add loc of ICMP req */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IP_REQ_DEST_IP_LOC	15	/* Dest IP add loc of ICMP req */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ICMP_ਗਿਆਤ_ਅੰਕੜੇ_LEN	64	/* ICMP known data length */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ICMP_ECHO_ਖੇਤਰ_LOC 	17	/* Echo field loc */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ICMP_ਅੰਕੜੇ_ਸ਼ੁਰੂ_LOC 	17	/* Data field start location */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ICMP_ਅੰਕੜੇ_LEN 		18	/* ICMP data length */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ICMP_ਅੰਕੜੇ_CHECKSUM_LOC	18	/* ICMP data checksum location */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ICMP_IDEN_ਖੇਤਰ_LOC	19	/* Identifier field loc */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ICMP_ਅੰਕੜੇ_LOC 		19	/* ICMP data loc including
					identifier number and sequence number */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ICMP_SEQ_NO_LOC		20	/* sequence number location */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ICMP_ਅੰਕੜੇ_ਖੇਤਰ_LEN 	20 	/* Data field length */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ICMP_ਗਿਆਤ_ਅੰਕੜੇ_LOC	21	/* ICMP known data start loc */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ARP_REQ_ਸਥਿਤੀ_LOC 	10	/* ARP request loc */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ARP_REQ_SRC_IP_LOC 	14	/* Src IP add loc of ARP req Packet */

/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/

ਸਥਿਰ ਪੂਰਨ EmacLitePingReqExample(u16 DeviceId);

ਸਥਿਰ ਖਾਲੀ Send_Arp_Req_ਚੌਖਟਾ(XEmacLite *InstancePtr);

ਸਥਿਰ ਖਾਲੀ Send_Echo_Req_ਚੌਖਟਾ(XEmacLite *InstancePtr);

ਸਥਿਰ ਪੂਰਨ Process_Recv_ਚੌਖਟਾ(XEmacLite *InstancePtr);

ਸਥਿਰ u16 Check_ਜੋੜ_Calculation(u16 *Rx_ਚੌਖਟਾ_Ptr16, ਪੂਰਨ ਸ਼ੁਰੂ_Loc, ਪੂਰਨ ਲੰਮਾਈ);

ਸਥਿਰ ਪੂਰਨ Compare_ਅੰਕੜੇ(u16 *LhsPtr, u16 *RhsPtr, ਪੂਰਨ LhsLoc, ਪੂਰਨ RhsLoc,
			ਪੂਰਨ ਗਿਣਤੀ_3);

/************************** Variable Definitions *****************************/

/*
 * Set up a local MAC address.
 */
ਸਥਿਰ u8 LocalMacAddr[XEL_MAC_ADDR_ਮਾਪ] =
{
	0x00, 0x0A, 0x35, 0x03, 0x02, 0x01
};

/*
 * The IP address was set to 172.16.63.121. User need to set a free IP address
 * based on the network on which this example is to be run.
 */
ਸਥਿਰ u8 Local_Ip_ਪਤਾ[IP_ADDR_ਮਾਪ] =
{
	192, 168, 1, 26
};

/*
 * Set up a Destination IP address. Currently it is set to 172.16.63.61.
 */
/* ifconfig enp1s0 172.16.63.61 netmask 255.255.255.0 up */
ਸਥਿਰ u8 Dest_Ip_ਪਤਾ[IP_ADDR_ਮਾਪ] =
{
	192, 168, 1, 25
};

ਸਥਿਰ u16 DestMacAddr[MAC_ADDR_LEN]; 	/* Destination MAC Address */
ਸਥਿਰ XEmacLite EmacLiteInstance;	/* Instance of the EmacLite driver */

/*
 * Known data transmitted in Echo request.
 */
u16 Icmp_ਅੰਕੜੇ[ICMP_ਗਿਆਤ_ਅੰਕੜੇ_LEN] =
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
u16 Ip_ਸਿਰਲੇਖ_Info[IP_ਸਿਰਲੇਖ_INFO_LEN] =
{
	0x0800,	0x4500, 0x003C,	0x5566,	0x0000,	0x8001, 0x0000
};

/*
 * Buffers used for Transmission and Reception of Packets. These are declared as
 * global so that they are not a part of the stack.
 */
ਸਥਿਰ u8 Rx_ਚੌਖਟਾ[XEL_MAX_ਚੌਖਟਾ_ਮਾਪ];
ਸਥਿਰ u8 Tx_ਚੌਖਟਾ[XEL_MAX_ਚੌਖਟਾ_ਮਾਪ];

/*
 * Variable used to indicate the length of the received frame.
 */
ਬਾਹਰੀ ਅਸਥਿਰ u32 Recv_ਚੌਖਟਾ_ਲੰਮਾਈ;

/*
 * Variable used to indicate the sequence number of the ICMP(echo) packet.
 */
ਪੂਰਨ Seq_ਅੰਕ;

/*
 * Variable used to indicate the number of ping request packets to be send.
 */
ਪੂਰਨ ਅੰਕ_ਦਾ_Ping_Req_Pkts;

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
ਪੂਰਨ ਮੁੱਖ()
{
	ਪੂਰਨ ਸਥਿਤੀ;

	/*
	 * Run the EmacLite Ping request example.
	 */
	ਸਥਿਤੀ = EmacLitePingReqExample(EMAC_DEVICE_ID);
	ਜੇ (ਸਥਿਤੀ != XST_SUCCESS) {
		xil_printf("Emaclite ping request Example Failed\r\n");
		ਵਾਪਸ XST_FAILURE;
	}

	xil_printf("Successfully ran Emaclite ping request Example\r\n");
	ਵਾਪਸ XST_SUCCESS;
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
ਸਥਿਰ ਪੂਰਨ EmacLitePingReqExample(u16 DeviceId)
{
	ਪੂਰਨ ਸਥਿਤੀ;
	ਪੂਰਨ ਸੂਚਕਾਂਕ;
	ਪੂਰਨ ਗਿਣਤੀ_3;
	ਪੂਰਨ Echo_ਜਵਾਬ_ਸਥਿਤੀ;
	XEmacLite_Config *ConfigPtr;
	XEmacLite *EmacLiteInstPtr = &EmacLiteInstance;
	Seq_ਅੰਕ = 0;
	Recv_ਚੌਖਟਾ_ਲੰਮਾਈ = 0;
	Echo_ਜਵਾਬ_ਸਥਿਤੀ = XST_FAILURE;
	ਅੰਕ_ਦਾ_Ping_Req_Pkts = ਅੰਕ_ਦਾ_PING_REQ_PKTS;

	/*
	 * Initialize the EmacLite device.
	 */
	ConfigPtr = &XEmac_Lite_Config_ਸਾਰਣੀ;
	ਜੇ (ConfigPtr == ਨਿਰਾ) {
		ਵਾਪਸ -1;
	}
	ConfigPtr->ਅਧਾਰ_ਪਤਾ = (UINTPTR *) 0X44000;
	ConfigPtr->RxPingPong = XPAR_EMACLITE_0_RX_PING_PONG;
	ConfigPtr->MdioInclude = XPAR_EMACLITE_0_INCLUDE_MDIO;
	ConfigPtr->TxPingPong = XPAR_EMACLITE_0_TX_PING_PONG;
#ਜੇ 0
	log_debug("\n ConfigPtr: BaseAddress: %x", ConfigPtr->ਅਧਾਰ_ਪਤਾ);
	log_debug("\n ConfigPtr: DeviceId: %x", ConfigPtr->DeviceId);
	log_debug("\n ConfigPtr: TxPingPong: %x", ConfigPtr->TxPingPong);
	log_debug("\n ConfigPtr: RxPingPong: %x", ConfigPtr->RxPingPong);
	log_debug("\n ConfigPtr: MdioInclude: %x", ConfigPtr->MdioInclude);
	log_debug("\n ConfigPtr: Loopback: %x", ConfigPtr->Loopback);
#ਜੇ_ਅੰਤ	
	ਸਥਿਤੀ = XEmacLite_CfgInitialize(EmacLiteInstPtr,
					ConfigPtr,
					ConfigPtr->ਅਧਾਰ_ਪਤਾ);
	ਜੇ (ਸਥਿਤੀ != 0) {
		ਵਾਪਸ -1;
	}
	

	/*
	 * Set the MAC address.
	 */
	XEmac_Lite_ਸੈੱਟ_Mac_ਪਤਾ(EmacLiteInstPtr, LocalMacAddr);

	/*
	 * Empty any existing receive frames.
	 */
	XEmacLite_FlushReceive(EmacLiteInstPtr);
	ਜਦੋਂ (ਅੰਕ_ਦਾ_Ping_Req_Pkts--) {

		/*
		 * Introduce delay.
		 */
		ਗਿਣਤੀ_3 = DELAY;
		ਜਦੋਂ (ਗਿਣਤੀ_3--) {
		}

		/*
		 * Send an ARP or an ICMP packet based on receive packet.
		 */
		ਜੇ (Seq_ਅੰਕ == 0) {
			Send_Arp_Req_ਚੌਖਟਾ(EmacLiteInstPtr);
		} ਨਹੀਂਤਾਂ {
			Send_Echo_Req_ਚੌਖਟਾ(EmacLiteInstPtr);
		}

		/*
		 * Check next 10 packets for the correct reply.
		 */
		ਸੂਚਕਾਂਕ = ਅੰਕ_RX_PACK_CHECK_REQ;
		ਜਦੋਂ (ਸੂਚਕਾਂਕ--) {

			/*
			 * Wait for a Receive packet.
			 */
			ਗਿਣਤੀ_3 = ਅੰਕ_PACK_CHECK_RX_PACK;
			ਜਦੋਂ (Recv_ਚੌਖਟਾ_ਲੰਮਾਈ == 0) {
				Recv_ਚੌਖਟਾ_ਲੰਮਾਈ = XEmacLite_Recv(
							EmacLiteInstPtr,
							(u8 *)Rx_ਚੌਖਟਾ);

				/*
				 * To avoid infinite loop when no packet is
				 * received.
				 */
				ਜੇ (ਗਿਣਤੀ_3-- == 0) {
					ਰੋਕੋ;
				}
			}

			/*
			 * Process the Receive frame.
			 */
			ਜੇ (Recv_ਚੌਖਟਾ_ਲੰਮਾਈ != 0) {
				Echo_ਜਵਾਬ_ਸਥਿਤੀ = Process_Recv_ਚੌਖਟਾ(
							EmacLiteInstPtr);
			}
			Recv_ਚੌਖਟਾ_ਲੰਮਾਈ = 0;

			/*
			 * Comes out of loop when an echo reply packet is
			 * received.
			 */
			ਜੇ (Echo_ਜਵਾਬ_ਸਥਿਤੀ == XST_SUCCESS) {
				ਰੋਕੋ;
			}
		}

		/*
		 * If no echo reply packet is received, it reports
		 * request timed out.
		 */
		ਜੇ (Echo_ਜਵਾਬ_ਸਥਿਤੀ == XST_FAILURE) {
			xil_printf("Packet No: %d",
				ਅੰਕ_ਦਾ_PING_REQ_PKTS - ਅੰਕ_ਦਾ_Ping_Req_Pkts);
			xil_printf(" Seq NO %d Request timed out\r\n",
							Seq_ਅੰਕ);
		}
	}
	ਵਾਪਸ XST_SUCCESS;
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
ਸਥਿਰ ਖਾਲੀ Send_Arp_Req_ਚੌਖਟਾ(XEmacLite *InstancePtr)
{
	u16 *ਆਰਜ਼ੀ_Ptr;
	u16 *Tx_ਚੌਖਟਾ_Ptr;
	u32 ਅਗਲਾ_Tx_Buff_ਅਧਾਰ_Addr;
	ਪੂਰਨ ਸੂਚਕਾਂਕ;

	Tx_ਚੌਖਟਾ_Ptr = (u16 *)Tx_ਚੌਖਟਾ;

	/*
	 * Determine the next expected transmit buffer base address.
	 */
	ਅਗਲਾ_Tx_Buff_ਅਧਾਰ_Addr = XEmac_Lite_ਅਗਲਾ_Transmit_Addr(InstancePtr);

	/*
	 * Add broadcast address.
	 */
	ਸੂਚਕਾਂਕ = MAC_ADDR_LEN;
	ਜਦੋਂ (ਸੂਚਕਾਂਕ--) {
		*Tx_ਚੌਖਟਾ_Ptr++ = ਪ੍ਰਸਾਰਣ_ADDR;
	}

	/*
	 * Add local MAC address.
	 */
	ਸੂਚਕਾਂਕ = 0;
	ਆਰਜ਼ੀ_Ptr = (u16 *)LocalMacAddr;
	ਜਦੋਂ (ਸੂਚਕਾਂਕ < MAC_ADDR_LEN) {
		*Tx_ਚੌਖਟਾ_Ptr++ = *(ਆਰਜ਼ੀ_Ptr + ਸੂਚਕਾਂਕ);
		ਸੂਚਕਾਂਕ++;
	}

	/*
	 * Add
	 * 	- Ethernet proto type.
	 *	- Hardware Type
	 *	- Protocol IP Type
	 *	- IP version (IPv6/IPv4)
	 *	- ARP Request
	 */
	*Tx_ਚੌਖਟਾ_Ptr++ = Xil_Htons(XEL_ETHER_PROTO_TYPE_ARP);
	*Tx_ਚੌਖਟਾ_Ptr++ = Xil_Htons(HW_TYPE);
	*Tx_ਚੌਖਟਾ_Ptr++ = Xil_Htons(XEL_ETHER_PROTO_TYPE_IP);
	*Tx_ਚੌਖਟਾ_Ptr++ = Xil_Htons(IP_ਸੰਸਕਰਣ);
	*Tx_ਚੌਖਟਾ_Ptr++ = Xil_Htons(ARP_REQUEST);

	/*
	 * Add local MAC address.
	 */
	ਸੂਚਕਾਂਕ = 0;
	ਆਰਜ਼ੀ_Ptr = (u16 *)LocalMacAddr;
	ਜਦੋਂ (ਸੂਚਕਾਂਕ < MAC_ADDR_LEN) {
		*Tx_ਚੌਖਟਾ_Ptr++ = *(ਆਰਜ਼ੀ_Ptr + ਸੂਚਕਾਂਕ);
		ਸੂਚਕਾਂਕ++;
	}

	/*
	 * Add local IP address.
	 */
	ਸੂਚਕਾਂਕ = 0;
	ਆਰਜ਼ੀ_Ptr = (u16 *)Local_Ip_ਪਤਾ;
	ਜਦੋਂ (ਸੂਚਕਾਂਕ < IP_ADDR_LEN) {
		*Tx_ਚੌਖਟਾ_Ptr++ = *(ਆਰਜ਼ੀ_Ptr + ਸੂਚਕਾਂਕ);
		ਸੂਚਕਾਂਕ++;
	}

	/*
	 * Fills 6 bytes of information with zeros as per protocol.
	 */
	ਸੂਚਕਾਂਕ = 0;
	ਜਦੋਂ (ਸੂਚਕਾਂਕ < 3) {
		*Tx_ਚੌਖਟਾ_Ptr++ = 0x0000;
		ਸੂਚਕਾਂਕ++;
	}

	/*
	 * Add Destination IP address.
	 */
	ਸੂਚਕਾਂਕ = 0;
	ਆਰਜ਼ੀ_Ptr = (u16 *)Dest_Ip_ਪਤਾ;
	ਜਦੋਂ (ਸੂਚਕਾਂਕ < IP_ADDR_LEN) {
		*Tx_ਚੌਖਟਾ_Ptr++ = *(ਆਰਜ਼ੀ_Ptr + ਸੂਚਕਾਂਕ);
		ਸੂਚਕਾਂਕ++;
	}

	/*
	 * Transmit the Frame.
	 */
	XEmacLite_Send(InstancePtr, (u8 *)&Tx_ਚੌਖਟਾ, ARP_REQ_PKT_ਮਾਪ);
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
ਸਥਿਰ ਖਾਲੀ Send_Echo_Req_ਚੌਖਟਾ(XEmacLite *InstancePtr)
{
	u16 *ਆਰਜ਼ੀ_Ptr;
	u16 *Tx_ਚੌਖਟਾ_Ptr;
	u16 *Rx_ਚੌਖਟਾ_Ptr;
	u16 Check_ਜੋੜ;
	u32 ਅਗਲਾ_Tx_Buff_ਅਧਾਰ_Addr;
	ਪੂਰਨ ਸੂਚਕਾਂਕ;

	Tx_ਚੌਖਟਾ_Ptr = (u16 *)Tx_ਚੌਖਟਾ;
	Rx_ਚੌਖਟਾ_Ptr = (u16 *)Rx_ਚੌਖਟਾ;

	/*
	 * Determine the next expected transmit buffer base address.
	 */
	ਅਗਲਾ_Tx_Buff_ਅਧਾਰ_Addr = XEmac_Lite_ਅਗਲਾ_Transmit_Addr(InstancePtr);

	/*
	 * Add Destination MAC Address.
	 */
	ਸੂਚਕਾਂਕ = MAC_ADDR_LEN;
	ਜਦੋਂ (ਸੂਚਕਾਂਕ--) {
		*(Tx_ਚੌਖਟਾ_Ptr + ਸੂਚਕਾਂਕ) = *(DestMacAddr + ਸੂਚਕਾਂਕ);
	}

	/*
	 * Add Source MAC Address.
	 */
	ਸੂਚਕਾਂਕ = MAC_ADDR_LEN;
	ਆਰਜ਼ੀ_Ptr = (u16 *)LocalMacAddr;
	ਜਦੋਂ (ਸੂਚਕਾਂਕ--) {
		*(Tx_ਚੌਖਟਾ_Ptr + (ਸੂਚਕਾਂਕ + SRC_MAC_ADDR_LOC )) =
							*(ਆਰਜ਼ੀ_Ptr + ਸੂਚਕਾਂਕ);
	}

	/*
	 * Add IP header information.
	 */
	ਸੂਚਕਾਂਕ = IP_ਸ਼ੁਰੂ_LOC;
	ਜਦੋਂ (ਸੂਚਕਾਂਕ--) {
		*(Tx_ਚੌਖਟਾ_Ptr + (ਸੂਚਕਾਂਕ + ETHER_PROTO_TYPE_LOC )) =
				Xil_Htons(*(Ip_ਸਿਰਲੇਖ_Info + ਸੂਚਕਾਂਕ));
	}

	/*
	 * Add Source IP address.
	 */
	ਸੂਚਕਾਂਕ = IP_ADDR_LEN;
	ਆਰਜ਼ੀ_Ptr = (u16 *)Local_Ip_ਪਤਾ;
	ਜਦੋਂ (ਸੂਚਕਾਂਕ--) {
		*(Tx_ਚੌਖਟਾ_Ptr + (ਸੂਚਕਾਂਕ + IP_REQ_SRC_IP_LOC )) =
						*(ਆਰਜ਼ੀ_Ptr + ਸੂਚਕਾਂਕ);
	}

	/*
	 * Add Destination IP address.
	 */
	ਸੂਚਕਾਂਕ = IP_ADDR_LEN;
	ਆਰਜ਼ੀ_Ptr = (u16 *)Dest_Ip_ਪਤਾ;
	ਜਦੋਂ (ਸੂਚਕਾਂਕ--) {
		*(Tx_ਚੌਖਟਾ_Ptr + (ਸੂਚਕਾਂਕ + IP_REQ_DEST_IP_LOC )) =
						*(ਆਰਜ਼ੀ_Ptr + ਸੂਚਕਾਂਕ);
	}

	/*
	 * Checksum is calculated for IP field and added in the frame.
	 */
	Check_ਜੋੜ = Check_ਜੋੜ_Calculation((u16 *)Tx_ਚੌਖਟਾ, IP_ਸ਼ੁਰੂ_LOC,
							IP_ਸਿਰਲੇਖ_LEN);
	Check_ਜੋੜ = ~Check_ਜੋੜ;
	*(Tx_ਚੌਖਟਾ_Ptr + IP_CHECKSUM_LOC) = Xil_Htons(Check_ਜੋੜ);

	/*
	 * Add echo field information.
	 */
	*(Tx_ਚੌਖਟਾ_Ptr + ICMP_ECHO_ਖੇਤਰ_LOC) = Xil_Htons(XEL_ETHER_PROTO_TYPE_IP);

	/*
	 * Checksum value is initialized to zeros.
	 */
	*(Tx_ਚੌਖਟਾ_Ptr + ICMP_ਅੰਕੜੇ_LEN) = 0x0000;

	/*
	 * Add identifier and sequence number to the frame.
	 */
	*(Tx_ਚੌਖਟਾ_Ptr + ICMP_IDEN_ਖੇਤਰ_LOC) = (IDEN_ਅੰਕ);
	*(Tx_ਚੌਖਟਾ_Ptr + (ICMP_IDEN_ਖੇਤਰ_LOC + 1)) = Xil_Htons((u16)(++Seq_ਅੰਕ));

	/*
	 * Add known data to the frame.
	 */
	ਸੂਚਕਾਂਕ = ICMP_ਗਿਆਤ_ਅੰਕੜੇ_LEN;
	ਜਦੋਂ (ਸੂਚਕਾਂਕ--) {
		*(Tx_ਚੌਖਟਾ_Ptr + (ਸੂਚਕਾਂਕ + ICMP_ਗਿਆਤ_ਅੰਕੜੇ_LOC)) =
				Xil_Htons(*(Icmp_ਅੰਕੜੇ + ਸੂਚਕਾਂਕ));
	}

	/*
	 * Checksum is calculated for Data Field and added in the frame.
	 */
	Check_ਜੋੜ = Check_ਜੋੜ_Calculation((u16 *)Tx_ਚੌਖਟਾ, ICMP_ਅੰਕੜੇ_ਸ਼ੁਰੂ_LOC,
						ICMP_ਅੰਕੜੇ_ਖੇਤਰ_LEN );
	Check_ਜੋੜ = ~Check_ਜੋੜ;
	*(Tx_ਚੌਖਟਾ_Ptr + ICMP_ਅੰਕੜੇ_CHECKSUM_LOC) = Xil_Htons(Check_ਜੋੜ);

	/*
	 * Transmit the Frame.
	 */
	XEmacLite_Send(InstancePtr, (u8 *)&Tx_ਚੌਖਟਾ, ICMP_PKT_ਮਾਪ);
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
ਸਥਿਰ ਪੂਰਨ Process_Recv_ਚੌਖਟਾ(XEmacLite *InstancePtr)
{
	u16 *Rx_ਚੌਖਟਾ_Ptr;
	u16 *ਆਰਜ਼ੀ_Ptr;
	u16 Check_ਜੋੜ;
	ਪੂਰਨ ਸੂਚਕਾਂਕ;
	ਪੂਰਨ ਮੇਲ = 0;
	ਪੂਰਨ ਅੰਕੜੇ_Wrong = 0;

	Rx_ਚੌਖਟਾ_Ptr = (u16 *)Rx_ਚੌਖਟਾ;
	ਆਰਜ਼ੀ_Ptr = (u16 *)LocalMacAddr;

	/*
	 * Check Dest Mac address of the packet with the LocalMac address.
	 */
	ਮੇਲ = Compare_ਅੰਕੜੇ(Rx_ਚੌਖਟਾ_Ptr, ਆਰਜ਼ੀ_Ptr, 0, 0, MAC_ADDR_LEN);
	ਜੇ (ਮੇਲ == XST_SUCCESS) {

		/*
		 * Check ARP type.
		 */
		ਜੇ (Xil_Ntohs(*(Rx_ਚੌਖਟਾ_Ptr + ETHER_PROTO_TYPE_LOC)) ==
				XEL_ETHER_PROTO_TYPE_ARP ) {

			/*
			 * Check ARP status.
			 */
			ਜੇ (Xil_Ntohs(*(Rx_ਚੌਖਟਾ_Ptr + ARP_REQ_ਸਥਿਤੀ_LOC)) == ARP_ਜਵਾਬ) {

				/*
				 * Check destination IP address with
				 * packet's source IP address.
				 */
				ਆਰਜ਼ੀ_Ptr = (u16 *)Dest_Ip_ਪਤਾ;
				ਮੇਲ = Compare_ਅੰਕੜੇ(Rx_ਚੌਖਟਾ_Ptr,
						ਆਰਜ਼ੀ_Ptr, ARP_REQ_SRC_IP_LOC,
						0, IP_ADDR_LEN);
				ਜੇ (ਮੇਲ == XST_SUCCESS) {

					/*
					 * Copy src Mac address of the received
					 * packet.
					 */
					ਸੂਚਕਾਂਕ = MAC_ADDR_LEN;
					ਆਰਜ਼ੀ_Ptr = (u16 *)DestMacAddr;
					ਜਦੋਂ (ਸੂਚਕਾਂਕ--) {
						*(ਆਰਜ਼ੀ_Ptr + ਸੂਚਕਾਂਕ) =
							*(Rx_ਚੌਖਟਾ_Ptr +
							(SRC_MAC_ADDR_LOC +
								ਸੂਚਕਾਂਕ));
					}

					/*
					 * Send Echo request packet.
					 */
					Send_Echo_Req_ਚੌਖਟਾ(InstancePtr);
				}
			}
		}

		/*
		 * Check for IP type.
		 */
		ਨਹੀਂਤਾਂ ਜੇ (Xil_Ntohs(*(Rx_ਚੌਖਟਾ_Ptr + ETHER_PROTO_TYPE_LOC)) ==
						XEL_ETHER_PROTO_TYPE_IP) {

			/*
			 * Calculate checksum.
			 */
			Check_ਜੋੜ = Check_ਜੋੜ_Calculation(Rx_ਚੌਖਟਾ_Ptr,
							ICMP_ਅੰਕੜੇ_ਸ਼ੁਰੂ_LOC,
							ICMP_ਅੰਕੜੇ_ਖੇਤਰ_LEN);

			/*
			 * Verify checksum, echo reply, identifier number and
			 * sequence number of the received packet.
			 */
			ਜੇ ((Check_ਜੋੜ == CORRECT_CHECKSUM_ਮੁੱਲ) &&
			(Xil_Ntohs(*(Rx_ਚੌਖਟਾ_Ptr + ICMP_ECHO_ਖੇਤਰ_LOC)) == ECHO_ਜਵਾਬ) &&
			(Xil_Ntohs(*(Rx_ਚੌਖਟਾ_Ptr + ICMP_IDEN_ਖੇਤਰ_LOC)) == IDEN_ਅੰਕ) &&
			(Xil_Ntohs(*(Rx_ਚੌਖਟਾ_Ptr + (ICMP_SEQ_NO_LOC))) == Seq_ਅੰਕ)) {

				/*
				 * Verify data in the received packet with known
				 * data.
				 */
				ਆਰਜ਼ੀ_Ptr = Icmp_ਅੰਕੜੇ;
				ਮੇਲ = Compare_ਅੰਕੜੇ(Rx_ਚੌਖਟਾ_Ptr,
						ਆਰਜ਼ੀ_Ptr, ICMP_ਗਿਆਤ_ਅੰਕੜੇ_LOC,
							0, ICMP_ਗਿਆਤ_ਅੰਕੜੇ_LEN);
				ਜੇ (ਮੇਲ == XST_FAILURE) {
					ਅੰਕੜੇ_Wrong = 1;
				}
			}
			ਜੇ (ਅੰਕੜੇ_Wrong != 1) {
				xil_printf("Packet No: %d ",
				ਅੰਕ_ਦਾ_PING_REQ_PKTS - ਅੰਕ_ਦਾ_Ping_Req_Pkts);
				xil_printf("Seq NO %d Echo Packet received\r\n",
								Seq_ਅੰਕ);
				ਵਾਪਸ XST_SUCCESS;
			}
		}
	}
	ਵਾਪਸ XST_FAILURE;
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
ਸਥਿਰ u16 Check_ਜੋੜ_Calculation(u16 *Rx_ਚੌਖਟਾ_Ptr, ਪੂਰਨ ਸ਼ੁਰੂ_Loc, ਪੂਰਨ ਲੰਮਾਈ)
{
	u32 ਜੋੜ = 0;
	u16 Check_ਜੋੜ = 0;
	ਪੂਰਨ ਸੂਚਕਾਂਕ;

	/*
	 * Add all the 16 bit data.
	 */
	ਸੂਚਕਾਂਕ = ਸ਼ੁਰੂ_Loc;
	ਜਦੋਂ (ਸੂਚਕਾਂਕ < (ਸ਼ੁਰੂ_Loc + ਲੰਮਾਈ)) {
		ਜੋੜ = ਜੋੜ + Xil_Htons(*(Rx_ਚੌਖਟਾ_Ptr + ਸੂਚਕਾਂਕ));
		ਸੂਚਕਾਂਕ++;
	}

	/*
	 * Add upper 16 bits to lower 16 bits.
	 */
	Check_ਜੋੜ = ਜੋੜ;
	ਜੋੜ = ਜੋੜ>>16;
	Check_ਜੋੜ = ਜੋੜ + Check_ਜੋੜ;
	ਵਾਪਸ Check_ਜੋੜ;
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
ਸਥਿਰ ਪੂਰਨ Compare_ਅੰਕੜੇ(u16 *LhsPtr, u16 *RhsPtr, ਪੂਰਨ LhsLoc, ਪੂਰਨ RhsLoc,
								ਪੂਰਨ ਗਿਣਤੀ_3)
{
	ਪੂਰਨ ਨਤੀਜਾ;
	ਜਦੋਂ (ਗਿਣਤੀ_3--) {
		ਜੇ (*(LhsPtr + LhsLoc + ਗਿਣਤੀ_3) == *(RhsPtr + RhsLoc + ਗਿਣਤੀ_3)) {
			ਨਤੀਜਾ = XST_SUCCESS;
		} ਨਹੀਂਤਾਂ {
			ਨਤੀਜਾ = XST_FAILURE;
			ਰੋਕੋ;
		}
	}
	ਵਾਪਸ ਨਤੀਜਾ;
}
