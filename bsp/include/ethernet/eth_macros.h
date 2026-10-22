/************************** Constant Definitions *****************************/
/**
 * Register offsets for the Ethernet MAC.
 */
#تعریف_کړه XEL_TXBUFF_دننه_واټن (0x00000000)			/**< Transmit Buffer */
#تعریف_کړه XEL_MDIOADDR_دننه_واټن (XEL_TXBUFF_دننه_واټن + 0x07E4)/**< MDIO Address offset
ثبتوونکی*/
#تعریف_کړه XEL_MDIOWR_دننه_واټن  (XEL_TXBUFF_دننه_واټن + 0x07E8)	/**< MDIO write data
							     register offset */
#تعریف_کړه XEL_MDIORD_دننه_واټن (XEL_TXBUFF_دننه_واټن + 0x07EC)	/**< MDIO read data
							     register offset*/
#تعریف_کړه XEL_MDIOCNTR_دننه_واټن (XEL_TXBUFF_دننه_واټن + 0x07F0)/**< MDIO Control
							     Register offset */
#تعریف_کړه XEL_GIER_دننه_واټن   (XEL_TXBUFF_دننه_واټن + 0x07F8)	/**< Offset for the GIE
ثبتوونکی*/
#تعریف_کړه XEL_TSR_دننه_واټن	  (XEL_TXBUFF_دننه_واټن + 0x07FC)	/**< Tx status */
#تعریف_کړه XEL_TPLR_دننه_واټن   (XEL_TXBUFF_دننه_واټن + 0x07F4)	/**< Tx packet length */

#تعریف_کړه XEL_RXBUFF_دننه_واټن (0x00001000)			/**< Receive Buffer */
#تعریف_کړه XEL_RSR_دننه_واټن	  (XEL_RXBUFF_دننه_واټن + 0x07FC)	/**< Rx status */
#تعریف_کړه XEL_RPLR_دننه_واټن   (XEL_RXBUFF_دننه_واټن + 0x0C)	/**< Rx packet length */

#تعریف_کړه XEL_MAC_HI_دننه_واټن (XEL_TXBUFF_دننه_واټن + 0x14)	/**< MAC address hi
دننه_واټن*/
#تعریف_کړه XEL_MAC_LO_دننه_واټن (XEL_TXBUFF_دننه_واټن)		/**< MAC address lo
دننه_واټن*/

#تعریف_کړه XEL_بفر_دننه_واټن (0x00000800)			/**< Next buffer's
							     offset  same for
							     both TX and RX */
/**
 * MDIO Address/Write Data/Read Data Register Bit Masks
 */
#تعریف_کړه XEL_MDIO_پته_ماسک		0x00003E0	/**< PHY Address mask */
#تعریف_کړه XEL_MDIO_پته_ښويدنه		0x5		/**< PHY Address shift*/
#تعریف_کړه XEL_MDIO_OP_ماسک		0x00000400	/**< PHY read access */

/**
 * MDIO Control Register Bit Masks
 */
#تعریف_کړه XEL_MDIOCNTR_حالت_ماسک	0x00000001	/**< MDIO transfer in
پرمختګ*/
#تعریف_کړه XEL_MDIOCNTR_ENABLE_ماسک	0x00000008	/**<  MDIO Enable */

/**
 * Global Interrupt Enable Register (GIER) Bit Masks
 */
#تعریف_کړه XEL_GIER_GIE_ماسک		0x80000000	/**< Global Enable */

/**
 * Transmit Status Register (TSR) Bit Masks
 */
#تعریف_کړه XEL_TSR_XMIT_BUSY_ماسک		0x00000001	/**< Xmit complete */
#تعریف_کړه XEL_TSR_پروګرام_ماسک		0x00000002	/**< Program the MAC
پته*/
#تعریف_کړه XEL_TSR_XMIT_IE_ماسک		0x00000008	/**< Xmit interrupt
							     enable bit */
#تعریف_کړه XEL_TSR_LOOPBACK_ماسک		0x00000010	/**< Loop back enable
بټ*/
#تعریف_کړه XEL_TSR_XMIT_فعال_ماسک	0x80000000	/**< Buffer is active,
							     SW bit only. This
							     is not documented
							     in the HW spec */

/**
 * define for programming the MAC address into the EmacLite
 */
#تعریف_کړه XEL_TSR_PROG_MAC_ADDR   (XEL_TSR_XMIT_BUSY_ماسک | XEL_TSR_پروګرام_ماسک)

/**
 * Receive Status Register (RSR)
 */
#تعریف_کړه XEL_RSR_RECV_بشپړ_ماسک		0x00000001	/**< Recv complete */
#تعریف_کړه XEL_RSR_RECV_IE_ماسک		0x00000008	/**< Recv interrupt
							     enable bit */

/**
 * Transmit Packet Length Register (TPLR)
 */
#تعریف_کړه XEL_TPLR_اوږدتیا_ماسک_HI		0x0000FF00 /**< Transmit packet length
							  upper byte */
#تعریف_کړه XEL_TPLR_اوږدتیا_ماسک_LO		0x000000FF /**< Transmit packet length
							  lower byte */

/**
 * Receive Packet Length Register (RPLR)
 */
#تعریف_کړه XEL_RPLR_اوږدتیا_ماسک_HI		0x0000FF00 /**< Receive packet length
							  upper byte */
#تعریف_کړه XEL_RPLR_اوږدتیا_ماسک_LO		0x000000FF /**< Receive packet length
							  lower byte */

#تعریف_کړه XEL_سرلیک_اندازه			14  /**< Size of header in bytes */
#تعریف_کړه XEL_MTU_اندازه			1500 /**< Max size of data in frame */
#تعریف_کړه XEL_FCS_اندازه			4    /**< Size of CRC */

#تعریف_کړه XEL_سرلیک_دننه_واټن		12   /**< Offset to length field */
#تعریف_کړه XEL_سرلیک_ښويدنه		16   /**< Right shift value to align
اوږدتیا*/


#تعریف_کړه XEL_MAX_چوکاټ_اندازه (XEL_سرلیک_اندازه+XEL_MTU_اندازه+ XEL_FCS_اندازه)	/**< Max
						length of Rx frame  used if
						length/type field
						contains the type (> 1500) */

#تعریف_کړه XEL_MAX_TX_چوکاټ_اندازه (XEL_سرلیک_اندازه + XEL_MTU_اندازه)	/**< Max
						length of Tx frame */


#تعریف_کړه XEL_MAC_ADDR_اندازه		6	/**< length of MAC address */


/*
 * General Ethernet Definitions
 */
#تعریف_کړه XEL_ETHER_PROTO_TYPE_IP		0x0800  /**< IP Protocol */
#تعریف_کړه XEL_ETHER_PROTO_TYPE_ARP	0x0806  /**< ARP Protocol */
#تعریف_کړه XEL_ETHER_PROTO_TYPE_VLAN	0x8100  /**< VLAN Tagged */
#تعریف_کړه XEL_ARP_PACKET_اندازه		28  	/**< Max ARP packet size */
#تعریف_کړه XEL_سرلیک_IP_اوږدتیا_دننه_واټن	16  	/**< IP Length Offset */
#تعریف_کړه XEL_VLAN_نښان_اندازه		4  	/**< VLAN Tag Size */

/***************** Macros (Inline Functions) Definitions *********************/

#تعریف_کړه XEmacLite_In32 Xil_In32
#تعریف_کړه XEmacLite_Out32 Xil_Out32

