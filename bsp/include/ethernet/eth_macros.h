/************************** Constant Definitions *****************************/
/**
 * Register offsets for the Ethernet MAC.
 */
#وصف_ڪريو XEL_TXBUFF_وٿي (0x00000000)			/**< Transmit Buffer */
#وصف_ڪريو XEL_MDIOADDR_وٿي (XEL_TXBUFF_وٿي + 0x07E4)/**< MDIO Address offset
رجسٽر*/
#وصف_ڪريو XEL_MDIOWR_وٿي  (XEL_TXBUFF_وٿي + 0x07E8)	/**< MDIO write data
							     register offset */
#وصف_ڪريو XEL_MDIORD_وٿي (XEL_TXBUFF_وٿي + 0x07EC)	/**< MDIO read data
							     register offset*/
#وصف_ڪريو XEL_MDIOCNTR_وٿي (XEL_TXBUFF_وٿي + 0x07F0)/**< MDIO Control
							     Register offset */
#وصف_ڪريو XEL_GIER_وٿي   (XEL_TXBUFF_وٿي + 0x07F8)	/**< Offset for the GIE
رجسٽر*/
#وصف_ڪريو XEL_TSR_وٿي	  (XEL_TXBUFF_وٿي + 0x07FC)	/**< Tx status */
#وصف_ڪريو XEL_TPLR_وٿي   (XEL_TXBUFF_وٿي + 0x07F4)	/**< Tx packet length */

#وصف_ڪريو XEL_RXBUFF_وٿي (0x00001000)			/**< Receive Buffer */
#وصف_ڪريو XEL_RSR_وٿي	  (XEL_RXBUFF_وٿي + 0x07FC)	/**< Rx status */
#وصف_ڪريو XEL_RPLR_وٿي   (XEL_RXBUFF_وٿي + 0x0C)	/**< Rx packet length */

#وصف_ڪريو XEL_MAC_HI_وٿي (XEL_TXBUFF_وٿي + 0x14)	/**< MAC address hi
وٿي*/
#وصف_ڪريو XEL_MAC_LO_وٿي (XEL_TXBUFF_وٿي)		/**< MAC address lo
وٿي*/

#وصف_ڪريو XEL_بفر_وٿي (0x00000800)			/**< Next buffer's
							     offset  same for
							     both TX and RX */
/**
 * MDIO Address/Write Data/Read Data Register Bit Masks
 */
#وصف_ڪريو XEL_MDIO_پتو_نقاب		0x00003E0	/**< PHY Address mask */
#وصف_ڪريو XEL_MDIO_پتو_سرڪايو		0x5		/**< PHY Address shift*/
#وصف_ڪريو XEL_MDIO_OP_نقاب		0x00000400	/**< PHY read access */

/**
 * MDIO Control Register Bit Masks
 */
#وصف_ڪريو XEL_MDIOCNTR_حالت_نقاب	0x00000001	/**< MDIO transfer in
ترقي*/
#وصف_ڪريو XEL_MDIOCNTR_ENABLE_نقاب	0x00000008	/**<  MDIO Enable */

/**
 * Global Interrupt Enable Register (GIER) Bit Masks
 */
#وصف_ڪريو XEL_GIER_GIE_نقاب		0x80000000	/**< Global Enable */

/**
 * Transmit Status Register (TSR) Bit Masks
 */
#وصف_ڪريو XEL_TSR_XMIT_BUSY_نقاب		0x00000001	/**< Xmit complete */
#وصف_ڪريو XEL_TSR_پروگرام_نقاب		0x00000002	/**< Program the MAC
پتو*/
#وصف_ڪريو XEL_TSR_XMIT_IE_نقاب		0x00000008	/**< Xmit interrupt
							     enable bit */
#وصف_ڪريو XEL_TSR_LOOPBACK_نقاب		0x00000010	/**< Loop back enable
ٻٽو_انگ*/
#وصف_ڪريو XEL_TSR_XMIT_سرگرم_نقاب	0x80000000	/**< Buffer is active,
							     SW bit only. This
							     is not documented
							     in the HW spec */

/**
 * define for programming the MAC address into the EmacLite
 */
#وصف_ڪريو XEL_TSR_PROG_MAC_ADDR   (XEL_TSR_XMIT_BUSY_نقاب | XEL_TSR_پروگرام_نقاب)

/**
 * Receive Status Register (RSR)
 */
#وصف_ڪريو XEL_RSR_RECV_پورو_نقاب		0x00000001	/**< Recv complete */
#وصف_ڪريو XEL_RSR_RECV_IE_نقاب		0x00000008	/**< Recv interrupt
							     enable bit */

/**
 * Transmit Packet Length Register (TPLR)
 */
#وصف_ڪريو XEL_TPLR_ڊيگهائي_نقاب_HI		0x0000FF00 /**< Transmit packet length
							  upper byte */
#وصف_ڪريو XEL_TPLR_ڊيگهائي_نقاب_LO		0x000000FF /**< Transmit packet length
							  lower byte */

/**
 * Receive Packet Length Register (RPLR)
 */
#وصف_ڪريو XEL_RPLR_ڊيگهائي_نقاب_HI		0x0000FF00 /**< Receive packet length
							  upper byte */
#وصف_ڪريو XEL_RPLR_ڊيگهائي_نقاب_LO		0x000000FF /**< Receive packet length
							  lower byte */

#وصف_ڪريو XEL_سرو_سائيز			14  /**< Size of header in bytes */
#وصف_ڪريو XEL_MTU_سائيز			1500 /**< Max size of data in frame */
#وصف_ڪريو XEL_FCS_سائيز			4    /**< Size of CRC */

#وصف_ڪريو XEL_سرو_وٿي		12   /**< Offset to length field */
#وصف_ڪريو XEL_سرو_سرڪايو		16   /**< Right shift value to align
ڊيگهائي*/


#وصف_ڪريو XEL_MAX_چوکٺو_سائيز (XEL_سرو_سائيز+XEL_MTU_سائيز+ XEL_FCS_سائيز)	/**< Max
						length of Rx frame  used if
						length/type field
						contains the type (> 1500) */

#وصف_ڪريو XEL_MAX_TX_چوکٺو_سائيز (XEL_سرو_سائيز + XEL_MTU_سائيز)	/**< Max
						length of Tx frame */


#وصف_ڪريو XEL_MAC_ADDR_سائيز		6	/**< length of MAC address */


/*
 * General Ethernet Definitions
 */
#وصف_ڪريو XEL_ETHER_PROTO_TYPE_IP		0x0800  /**< IP Protocol */
#وصف_ڪريو XEL_ETHER_PROTO_TYPE_ARP	0x0806  /**< ARP Protocol */
#وصف_ڪريو XEL_ETHER_PROTO_TYPE_VLAN	0x8100  /**< VLAN Tagged */
#وصف_ڪريو XEL_ARP_PACKET_سائيز		28  	/**< Max ARP packet size */
#وصف_ڪريو XEL_سرو_IP_ڊيگهائي_وٿي	16  	/**< IP Length Offset */
#وصف_ڪريو XEL_VLAN_ٽيگ_سائيز		4  	/**< VLAN Tag Size */

/***************** Macros (Inline Functions) Definitions *********************/

#وصف_ڪريو XEmacLite_In32 Xil_In32
#وصف_ڪريو XEmacLite_Out32 Xil_Out32

