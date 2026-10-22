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
/*
 * Instance of the driver
 */
ਸਥਿਰ XEmacLite EmacLite;



/*
 * Change this parameter to limit the number of ping replies sent by this
 * program.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_PING_REPLIES	10000	/* Maximum number of ping replies */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪ੍ਰਸਾਰਣ_PACKET	1	/* Broadcast packet */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAC_MATCHED_PACKET	2 	/* Dest MAC matched with local MAC */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IP_ADDR_ਮਾਪ		4	/* IP Address size in Bytes */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ARP_REQUEST 		0x0001	/* ARP Request bits in Rx packet */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ARP_ਜਵਾਬ 		0x0002 	/* ARP status bits indicating reply */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ARP_PACKET_ਮਾਪ 	0x3C    /* ARP packet len 60 Bytes */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ICMP_PACKET_ਮਾਪ 	98 //0x4A    /* ICMP packet length 74 Bytes
					 /* including Src and Dest MAC Address */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪ੍ਰਸਾਰਣ_ADDR 		0xFFFF  /* Broadcast Address */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CORRECT_CKSUM_ਮੁੱਲ	0xFFFF  /* Correct checksum value */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IDENT_ਖੇਤਰ_ਮੁੱਲ	0x9263	/* Identification field (random num) */

/*
 * Definitions for the locations and length of some of the fields in a
 * IP packet. The lengths are defined in Half-Words (2 bytes).
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ETHER_PROTO_TYPE_LEN	1  /* Ethernet protocol Type length  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRC_MAC_ADDR_LOC	3  /* Source MAC address location */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAC_ADDR_LEN 		3  /* MAC address length */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ETHER_PROTO_TYPE_LOC	6  /* Ethernet Proto type location */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ARP_HW_TYPE_LEN 	1  /* Hardware Type length  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ARP_PROTO_TYPE_LEN	1  /* Protocol Type length  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ARP_HW_ਜੋੜੋ_LEN		1  /* Hardware address length */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ARP_PROTO_ਜੋੜੋ_LEN	1  /* Protocol address length */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ARP_ZEROS_LEN		9  /* Length to be filled with zeros */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ARP_REQ_ਸਥਿਤੀ_LOC 	10 /* ARP request location */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ARP_REQ_SRC_IP_LOC 	14 /* Src IP address location of ARP request */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ARP_REQ_DEST_IP_LOC_1 	19 /* Destination IP's 1st half word location */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ARP_REQ_DEST_IP_LOC_2 	20 /* Destination IP's 2nd half word location */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IP_ਸੰਸਕਰਣ_LEN 		1  /* IP Version length  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IP_PACKET_LEN 		1  /* IP Packet length field  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IP_FRAG_ਖੇਤਰ_LEN	1  /* Fragment field len in ICMP packet */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IP_TTL_ICM_LEN 		1  /* Time to live and ICM fields length */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IP_ADDR_LEN 		2  /* Size of IP address in half-words */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IP_CSUM_LOC_ਪਿੱਠ	5  /* IP checksum location from end of frame */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IP_HDR_ਸ਼ੁਰੂ_LOC 	7  /* IP header start location */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IP_HDR_LEN 		10 /* IP Header length */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IP_FRAG_ਖੇਤਰ_LOC 	10 /* Fragment field location */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ICMP_TYPE_LEN 		1  /* ICMP Type length */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ICMP_ECHO_ਖੇਤਰ_LEN 	2  /* Echo field length in half-words */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ICMP_REQ_SRC_IP_LOC 	13 /* Src IP address location of ICMP request */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ICMP_ECHO_ਖੇਤਰ_LOC 	17 /* Echo field location */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ICMP_ਅੰਕੜੇ_ਸ਼ੁਰੂ_LOC 	17 /* Data field start location */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ICMP_ਅੰਕੜੇ_LEN 		30  //18  /* ICMP data length */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ICMP_ਅੰਕੜੇ_LOC 		19 /* ICMP data location including
				      identifier number and sequence number */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ICMP_ਅੰਕੜੇ_CSUM_LOC_ਪਿੱਠ 31 //19 
/* Data checksum location from end of
ਚੌਖਟਾ*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ICMP_ਅੰਕੜੇ_ਖੇਤਰ_LEN 	32 //20 /* Data field length */

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

ਸਥਿਰ ਪੂਰਨ Emac_Lite_Ping_ਜਵਾਬ_Example(u16 DeviceId);

ਸਥਿਰ ਖਾਲੀ Process_Recv_ਚੌਖਟਾ(XEmacLite *InstancePtr);

ਸਥਿਰ u16 Check_ਜੋੜ_Calculation(u16 *Rx_ਚੌਖਟਾ_Ptr, ਪੂਰਨ ਸ਼ੁਰੂ_Loc, ਪੂਰਨ ਲੰਮਾਈ);

/************************** Variable Definitions *****************************/

/*
 * Set up a local MAC address.
 */
ਸਥਿਰ u8 LocalMacAddr[XEL_MAC_ADDR_ਮਾਪ] =
{
	0x00, 0x00, 0x5E, 0x00, 0xFA, 0xCE
};

/*
 * The IP address was set to 172.16.63.121. User need to set a free IP address
 * based on the network on which this example is to be run.
 */
ਸਥਿਰ u8 LocalIpAddr[IP_ADDR_ਮਾਪ] =
{
	192, 168, 1, 25
};

ਸਥਿਰ XEmacLite EmacLiteInstance;	/* Instance of the EmacLite driver */

/*
 * Buffers used for Transmission and Reception of Packets. These are declared as
 * global so that they are not a part of the stack.
 */
ਸਥਿਰ u8 Rx_ਚੌਖਟਾ[XEL_MAX_ਚੌਖਟਾ_ਮਾਪ];
ਸਥਿਰ u8 Tx_ਚੌਖਟਾ[XEL_MAX_ਚੌਖਟਾ_ਮਾਪ];

/*
 * Variable used to indicate the length of the received frame.
 */
ਬਾਹਰੀ ਅਸਥਿਰ u32 Recv_ਚੌਖਟਾ_ਲੰਮਾਈ = 0;

/*
 * Variable used to indicate the number of Ping replies sent.
 */
u32 ਅੰਕ_ਦਾ_Ping_Replies;
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
ਪੂਰਨ ਮੁੱਖ()
{
	ਪੂਰਨ ਸਥਿਤੀ;
	arpcount = 0;
	/*
	 * Run the EmacLite Ping reply example.
	 */
	ਸਥਿਤੀ = Emac_Lite_Ping_ਜਵਾਬ_Example(EMAC_DEVICE_ID);
	ਜੇ (ਸਥਿਤੀ != XST_SUCCESS) {
		xil_printf("Emaclite ping reply Example Failed\r\n");
		ਵਾਪਸ XST_FAILURE;
	}

	xil_printf("Successfully ran Emaclite ping reply Example\r\n");
	ਵਾਪਸ XST_SUCCESS;
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
ਪੂਰਨ Emac_Lite_Ping_ਜਵਾਬ_Example(u16 DeviceId)
{
	ਪੂਰਨ ਸਥਿਤੀ, ਗਿਣਤੀ_2 = 0;
	XEmacLite *EmacLiteInstPtr = &EmacLiteInstance;
	XEmacLite_Config *ConfigPtr;
	ਅੰਕ_ਦਾ_Ping_Replies = 0;

	/*
	 * Initialize the EmacLite device.
	 */
	ConfigPtr = &XEmac_Lite_Config_ਸਾਰਣੀ;
	ਜੇ (ConfigPtr == ਨਿਰਾ) {
		ਵਾਪਸ -1;
	}
	ਲਿਖੋ("\n ");

	ConfigPtr->ਅਧਾਰ_ਪਤਾ = (UINTPTR *) 0X44000;
	ConfigPtr->RxPingPong = XPAR_EMACLITE_0_RX_PING_PONG;
	ConfigPtr->MdioInclude = XPAR_EMACLITE_0_INCLUDE_MDIO;
	ConfigPtr->TxPingPong = XPAR_EMACLITE_0_TX_PING_PONG;
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

	ਜਦੋਂ (1) {

		/*
		 * Wait for a Receive packet.
		 */
		ਜਦੋਂ (Recv_ਚੌਖਟਾ_ਲੰਮਾਈ == 0) {
			Recv_ਚੌਖਟਾ_ਲੰਮਾਈ = XEmacLite_Recv(EmacLiteInstPtr,
								(u8 *)Rx_ਚੌਖਟਾ);
		}
#ਜੇ 1
		ਲਿਖੋ("\n Rcv. Frame %x: %x\n", ਅੰਕ_ਦਾ_Ping_Replies, Recv_ਚੌਖਟਾ_ਲੰਮਾਈ);
		ਲਈ(ਪੂਰਨ i = 0; i < Recv_ਚੌਖਟਾ_ਲੰਮਾਈ; i++)
			ਲਿਖੋ("%x ", Rx_ਚੌਖਟਾ[i]);
		ਲਿਖੋ("\n");
#ਜੇ_ਅੰਤ			
		/*
		 * Empty any existing receive frames.
		 */
		XEmacLite_FlushReceive(EmacLiteInstPtr);

		/*
		 * Process the Receive frame.
		 */
		Process_Recv_ਚੌਖਟਾ(EmacLiteInstPtr);
		Recv_ਚੌਖਟਾ_ਲੰਮਾਈ = 0;

		/*
		 * If the number of ping replies sent is equal to that
		 * specified by the user then exit out of this loop.
		 */
		ਜੇ (ਅੰਕ_ਦਾ_Ping_Replies == MAX_PING_REPLIES) {

			ਵਾਪਸ XST_SUCCESS;
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
ਸਥਿਰ ਖਾਲੀ Process_Recv_ਚੌਖਟਾ(XEmacLite *InstancePtr)
{
	u16 *Rx_ਚੌਖਟਾ_Ptr;
	u16 *Tx_ਚੌਖਟਾ_Ptr;
	u16 *ਆਰਜ਼ੀ_Ptr;
	u16 Check_ਜੋੜ;
	u32 ਅਗਲਾ_Tx_Buff_ਅਧਾਰ_Addr;
	ਪੂਰਨ ਸੂਚਕਾਂਕ;
	ਪੂਰਨ PacketType = 0;

	Tx_ਚੌਖਟਾ_Ptr = (u16 *)Tx_ਚੌਖਟਾ;
	Rx_ਚੌਖਟਾ_Ptr = (u16 *)Rx_ਚੌਖਟਾ;

	/*
	 * Determine the next expected Tx buffer address.
	 */
	ਅਗਲਾ_Tx_Buff_ਅਧਾਰ_Addr = XEmac_Lite_ਅਗਲਾ_Transmit_Addr(InstancePtr);

	/*
	 * Check the packet type.
	 */
	ਸੂਚਕਾਂਕ = MAC_ADDR_LEN;
	ਆਰਜ਼ੀ_Ptr = (u16 *)LocalMacAddr;
	ਜਦੋਂ (ਸੂਚਕਾਂਕ--) {
		ਜੇ (Xil_Ntohs((*(Rx_ਚੌਖਟਾ_Ptr + ਸੂਚਕਾਂਕ)) == ਪ੍ਰਸਾਰਣ_ADDR) &&
					(PacketType != MAC_MATCHED_PACKET)) {
			PacketType = ਪ੍ਰਸਾਰਣ_PACKET;
		} ਨਹੀਂਤਾਂ ਜੇ (Xil_Ntohs((*(Rx_ਚੌਖਟਾ_Ptr + ਸੂਚਕਾਂਕ)) == *(ਆਰਜ਼ੀ_Ptr + ਸੂਚਕਾਂਕ)) &&
					(PacketType != ਪ੍ਰਸਾਰਣ_PACKET)) {
			PacketType = MAC_MATCHED_PACKET;
		} ਨਹੀਂਤਾਂ {
			PacketType = 0;
			ਰੋਕੋ;
		}
	}
#ਜੇ 0
	ਲਿਖੋ("\n Packet type is %x", PacketType);
#ਜੇ_ਅੰਤ
	/*
	 * Process broadcast packet.
	 */
	ਜੇ (PacketType == ਪ੍ਰਸਾਰਣ_PACKET) {

		/*
		 * Check for an ARP Packet if so generate a reply.
		 */
		ਜੇ (Xil_Ntohs(*(Rx_ਚੌਖਟਾ_Ptr + ETHER_PROTO_TYPE_LOC)) ==
				XEL_ETHER_PROTO_TYPE_ARP) {

			/*
			 * IP address of the local machine.
			 */
			ਆਰਜ਼ੀ_Ptr = (u16 *)LocalIpAddr;

			/*
			 * Check destination IP address of the packet with
			 * local IP address.
			 */
			ਜੇ (
			((*(Rx_ਚੌਖਟਾ_Ptr + ARP_REQ_DEST_IP_LOC_1)) == *ਆਰਜ਼ੀ_Ptr++) &&
			((*(Rx_ਚੌਖਟਾ_Ptr + ARP_REQ_DEST_IP_LOC_2)) == *ਆਰਜ਼ੀ_Ptr++)) {

				/*
				 * Check ARP packet type(request/reply).
				 */
				ਜੇ (Xil_Ntohs(*(Rx_ਚੌਖਟਾ_Ptr + ARP_REQ_ਸਥਿਤੀ_LOC)) ==
								ARP_REQUEST) {

					/*
					 * Add destination MAC address
					 * to the reply packet (i.e) source
					 * address of the received packet.
					 */
					ਸੂਚਕਾਂਕ = SRC_MAC_ADDR_LOC;
					ਜਦੋਂ (ਸੂਚਕਾਂਕ < (SRC_MAC_ADDR_LOC +
							MAC_ADDR_LEN)) {
						*Tx_ਚੌਖਟਾ_Ptr++ =
							*(Rx_ਚੌਖਟਾ_Ptr + ਸੂਚਕਾਂਕ);
						ਸੂਚਕਾਂਕ++;
					}

					/*
					 * Add source (local) MAC address
					 * to the reply packet.
					 */
					ਸੂਚਕਾਂਕ = 0;
					ਆਰਜ਼ੀ_Ptr = (u16 *)LocalMacAddr;
					ਜਦੋਂ (ਸੂਚਕਾਂਕ < MAC_ADDR_LEN) {
						*Tx_ਚੌਖਟਾ_Ptr++ = *ਆਰਜ਼ੀ_Ptr++;
						ਸੂਚਕਾਂਕ++;
					}

					/*
					 * Add Ethernet proto type H/W
					 * type(10/3MBps),H/W address length and
					 * protocol address len (i.e)same as in
					 * the received packet
					 */
					ਸੂਚਕਾਂਕ = ETHER_PROTO_TYPE_LOC;
					ਜਦੋਂ (ਸੂਚਕਾਂਕ < (ETHER_PROTO_TYPE_LOC +
							ETHER_PROTO_TYPE_LEN +
							ARP_HW_TYPE_LEN +
							ARP_HW_ਜੋੜੋ_LEN
							+ ARP_PROTO_ਜੋੜੋ_LEN)) {
						*Tx_ਚੌਖਟਾ_Ptr++ =
							*(Rx_ਚੌਖਟਾ_Ptr + ਸੂਚਕਾਂਕ);
						ਸੂਚਕਾਂਕ++;
					}

					/*
					 * Add ARP reply status to the reply
					 * packet.
					 */
					*Tx_ਚੌਖਟਾ_Ptr++ = Xil_Htons(ARP_ਜਵਾਬ);

					/*
					 * Add local MAC Address
					 * to the reply packet.
					 */
					ਆਰਜ਼ੀ_Ptr = (u16 *)LocalMacAddr;
					ਸੂਚਕਾਂਕ = 0;
					ਜਦੋਂ (ਸੂਚਕਾਂਕ < MAC_ADDR_LEN) {
						*Tx_ਚੌਖਟਾ_Ptr++ = *ਆਰਜ਼ੀ_Ptr++;
						ਸੂਚਕਾਂਕ++;
					}

					/*
					 * Add local IP Address
					 * to the reply packet.
					 */
					ਆਰਜ਼ੀ_Ptr = (u16 *)LocalIpAddr;
					ਸੂਚਕਾਂਕ = 0;
					ਜਦੋਂ (ਸੂਚਕਾਂਕ < IP_ADDR_LEN) {
						*Tx_ਚੌਖਟਾ_Ptr++ = *ਆਰਜ਼ੀ_Ptr++ ;
						ਸੂਚਕਾਂਕ++;
					}

					/*
					 * Add Destination MAC Address
					 * to the reply packet from the received
					 * packet.
					 */
					ਸੂਚਕਾਂਕ = SRC_MAC_ADDR_LOC;
					ਜਦੋਂ (ਸੂਚਕਾਂਕ < (SRC_MAC_ADDR_LOC +
							MAC_ADDR_LEN)) {
						*Tx_ਚੌਖਟਾ_Ptr++ =
							*(Rx_ਚੌਖਟਾ_Ptr + ਸੂਚਕਾਂਕ);
						ਸੂਚਕਾਂਕ++;
					}

					/*
					 * Add Destination IP Address
					 * to the reply packet.
					 */
					ਸੂਚਕਾਂਕ = ARP_REQ_SRC_IP_LOC;
					ਜਦੋਂ (ਸੂਚਕਾਂਕ < (ARP_REQ_SRC_IP_LOC +
							IP_ADDR_LEN)) {
						*Tx_ਚੌਖਟਾ_Ptr++ =
								*(Rx_ਚੌਖਟਾ_Ptr + ਸੂਚਕਾਂਕ);
						ਸੂਚਕਾਂਕ++;
					}

					/*
					 * Fill zeros as per protocol.
					 */
					ਸੂਚਕਾਂਕ = 0;
					ਜਦੋਂ (ਸੂਚਕਾਂਕ < ARP_ZEROS_LEN) {
						*Tx_ਚੌਖਟਾ_Ptr++ = 0x0000;
						ਸੂਚਕਾਂਕ++;
					}

					/*
					 * Transmit the Reply Packet.
					 */
					XEmacLite_Send(InstancePtr,
							(u8 *)&Tx_ਚੌਖਟਾ,
							ARP_PACKET_ਮਾਪ);
				}
			}
		}
	}

	/*
	 * Process packets whose MAC address is matched.
	 */
	ਜੇ (PacketType == MAC_MATCHED_PACKET) {
//		printf("\n MAC matched packet");
		/*
		 * Check ICMP packet.
		 */
		ਜੇ (Xil_Ntohs(*(Rx_ਚੌਖਟਾ_Ptr + ETHER_PROTO_TYPE_LOC)) ==
						XEL_ETHER_PROTO_TYPE_IP) {
//			printf("\n calculate ip header checksum");
			/*
			 * Check the IP header checksum.
			 */
			Check_ਜੋੜ = Check_ਜੋੜ_Calculation(Rx_ਚੌਖਟਾ_Ptr,
						IP_HDR_ਸ਼ੁਰੂ_LOC,
						IP_HDR_LEN);

			/*
			 * Check the Data field checksum.
			 */
//			printf("\n ip checksum:%x", CheckSum);
			ਜੇ (Check_ਜੋੜ == CORRECT_CKSUM_ਮੁੱਲ) {
				Check_ਜੋੜ = Check_ਜੋੜ_Calculation(Rx_ਚੌਖਟਾ_Ptr,
						ICMP_ਅੰਕੜੇ_ਸ਼ੁਰੂ_LOC,
						ICMP_ਅੰਕੜੇ_ਖੇਤਰ_LEN);
#ਜੇ 0
			ਲਿਖੋ("\nICMP Rcv Packet: \n");
			ਲਈ(ਪੂਰਨ i = ICMP_ਅੰਕੜੇ_ਸ਼ੁਰੂ_LOC; i <= ICMP_ਅੰਕੜੇ_ਖੇਤਰ_LEN; i++)
			   ਲਿਖੋ("%x ", Rx_ਚੌਖਟਾ_Ptr[i]);
			ਲਿਖੋ("\n End of ICMP Rcv Packet");
				
				ਲਿਖੋ("\n data checksum:%x", Check_ਜੋੜ);
#ਜੇ_ਅੰਤ
				ਜੇ (Check_ਜੋੜ == CORRECT_CKSUM_ਮੁੱਲ) {

					/*
					 * Add destination address
					 * to the reply packet (i.e)source
					 * address of the received packet.
					 */
					ਸੂਚਕਾਂਕ = SRC_MAC_ADDR_LOC;
					ਜਦੋਂ (ਸੂਚਕਾਂਕ < (SRC_MAC_ADDR_LOC +
							MAC_ADDR_LEN)) {
						*Tx_ਚੌਖਟਾ_Ptr++ =
							*(Rx_ਚੌਖਟਾ_Ptr + ਸੂਚਕਾਂਕ);
						ਸੂਚਕਾਂਕ++;
					}

					/*
					 * Add local MAC address
					 * to the reply packet.
					 */
					ਸੂਚਕਾਂਕ = 0;
					ਆਰਜ਼ੀ_Ptr = (u16 *)LocalMacAddr;
					ਜਦੋਂ (ਸੂਚਕਾਂਕ < MAC_ADDR_LEN) {
						*Tx_ਚੌਖਟਾ_Ptr++ = *ਆਰਜ਼ੀ_Ptr++;
						ਸੂਚਕਾਂਕ++;
					}

					/*
					 * Add protocol type
					 * header length and, packet
					 * length(60 Bytes) to the reply packet.
					 */
					ਸੂਚਕਾਂਕ = ETHER_PROTO_TYPE_LOC;
					ਜਦੋਂ (ਸੂਚਕਾਂਕ < (ETHER_PROTO_TYPE_LOC +
							ETHER_PROTO_TYPE_LEN +
							IP_ਸੰਸਕਰਣ_LEN +
							IP_PACKET_LEN)) {
						*Tx_ਚੌਖਟਾ_Ptr++ =
							*(Rx_ਚੌਖਟਾ_Ptr + ਸੂਚਕਾਂਕ);
						ਸੂਚਕਾਂਕ++;
					}

					/*
					 * Identification field a random number
					 * which is set to IDENT_FIELD_VALUE.
					 */
					*Tx_ਚੌਖਟਾ_Ptr++ = IDENT_ਖੇਤਰ_ਮੁੱਲ;

					/*
					 * Add fragment type, time to live and
					 * ICM field. It is same as in the
					 * received packet.
					 */
					ਸੂਚਕਾਂਕ = IP_FRAG_ਖੇਤਰ_LOC;
					ਜਦੋਂ (ਸੂਚਕਾਂਕ < (IP_FRAG_ਖੇਤਰ_LOC +
							IP_TTL_ICM_LEN +
							IP_FRAG_ਖੇਤਰ_LEN)) {
						*Tx_ਚੌਖਟਾ_Ptr++ =
							*(Rx_ਚੌਖਟਾ_Ptr + ਸੂਚਕਾਂਕ);
						ਸੂਚਕਾਂਕ++;
					}

					/*
					 * Checksum first set to 0 and
					 * added in this field later.
					 */
					*Tx_ਚੌਖਟਾ_Ptr++ = 0x0000;

					/*
					 * Add Source IP address
					 */
					ਸੂਚਕਾਂਕ = 0;
					ਆਰਜ਼ੀ_Ptr = (u16 *)LocalIpAddr;
					ਜਦੋਂ (ਸੂਚਕਾਂਕ < IP_ADDR_LEN) {
						*Tx_ਚੌਖਟਾ_Ptr++ = *ਆਰਜ਼ੀ_Ptr++;
						ਸੂਚਕਾਂਕ++;
					}

					/*
					 * Add Destination IP address.
					 */
					ਸੂਚਕਾਂਕ = ICMP_REQ_SRC_IP_LOC;
					ਜਦੋਂ (ਸੂਚਕਾਂਕ < (ICMP_REQ_SRC_IP_LOC +
							IP_ADDR_LEN)) {
						*Tx_ਚੌਖਟਾ_Ptr++ =
							*(Rx_ਚੌਖਟਾ_Ptr + ਸੂਚਕਾਂਕ);
						ਸੂਚਕਾਂਕ++;
					}

					/*
					 * Calculate checksum, and
					 * add it in the appropriate field.
					 */
					Check_ਜੋੜ = Check_ਜੋੜ_Calculation(
							(u16 *)Tx_ਚੌਖਟਾ,
							IP_HDR_ਸ਼ੁਰੂ_LOC,
							IP_HDR_LEN);
					Check_ਜੋੜ = ~Check_ਜੋੜ;
					*(Tx_ਚੌਖਟਾ_Ptr - IP_CSUM_LOC_ਪਿੱਠ) =
								Xil_Htons(Check_ਜੋੜ);

					/*
					 * Echo reply status & checksum.
					 */
					ਸੂਚਕਾਂਕ = ICMP_ECHO_ਖੇਤਰ_LOC;
					ਜਦੋਂ (ਸੂਚਕਾਂਕ < (ICMP_ECHO_ਖੇਤਰ_LOC +
							ICMP_ECHO_ਖੇਤਰ_LEN)) {
						*Tx_ਚੌਖਟਾ_Ptr++ = 0x0000;
						ਸੂਚਕਾਂਕ++;
					}

					/*
					 * Add data to buffer which was
					 * received from the packet.
					 */
					ਸੂਚਕਾਂਕ = ICMP_ਅੰਕੜੇ_LOC;
					ਜਦੋਂ (ਸੂਚਕਾਂਕ < (ICMP_ਅੰਕੜੇ_LOC +
							ICMP_ਅੰਕੜੇ_LEN)) {
						*Tx_ਚੌਖਟਾ_Ptr++ =
								(*(Rx_ਚੌਖਟਾ_Ptr + ਸੂਚਕਾਂਕ));
						ਸੂਚਕਾਂਕ++;
					}

					/*
					 * Generate checksum for the data and
					 * add it in the appropriate field.
					 */
					Check_ਜੋੜ = Check_ਜੋੜ_Calculation(
							(u16 *)Tx_ਚੌਖਟਾ,
							ICMP_ਅੰਕੜੇ_ਸ਼ੁਰੂ_LOC,
							ICMP_ਅੰਕੜੇ_ਖੇਤਰ_LEN);
					Check_ਜੋੜ = ~Check_ਜੋੜ;
					*(Tx_ਚੌਖਟਾ_Ptr - ICMP_ਅੰਕੜੇ_CSUM_LOC_ਪਿੱਠ)
								= Xil_Htons(Check_ਜੋੜ);

					/*
					 * Transmit the frame.
					 */
#ਜੇ 1
					 ਲਿਖੋ("\n%x. ICMP Tx Packet \n", ਅੰਕ_ਦਾ_Ping_Replies);
					 ਲਈ(ਪੂਰਨ i = 0; i < ICMP_PACKET_ਮਾਪ; i++)
					 	ਲਿਖੋ("%x ", Tx_ਚੌਖਟਾ[i]);
					 ਲਿਖੋ("\n End of ICMP Tx Packet");
#ਜੇ_ਅੰਤ					 
					XEmacLite_Send(InstancePtr,
							(u8 *)&Tx_ਚੌਖਟਾ,
							ICMP_PACKET_ਮਾਪ);

					/*
					 * Increment the number of
					 * Ping replies sent.
					 */
					ਅੰਕ_ਦਾ_Ping_Replies++;
//					printf("NumOfPingReplies: %x", NumOfPingReplies);

				}
				ਨਹੀਂਤਾਂ
					ਲਿਖੋ("\n Data check sum error");
			}
			ਨਹੀਂਤਾਂ
				ਲਿਖੋ("\n IP Check sum error");
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
		ਜੋੜ = ਜੋੜ + Xil_Ntohs(*(Rx_ਚੌਖਟਾ_Ptr + ਸੂਚਕਾਂਕ));
		ਸੂਚਕਾਂਕ++;
	}

	/*
	 * Add upper 16 bits to lower 16 bits.
	 */
	Check_ਜੋੜ = ਜੋੜ;
	ਜੋੜ = ਜੋੜ >> 16;
	Check_ਜੋੜ = ਜੋੜ + Check_ਜੋੜ;
	ਵਾਪਸ Check_ਜੋੜ;
}
