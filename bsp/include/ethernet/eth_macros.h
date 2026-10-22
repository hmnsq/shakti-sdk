/************************** Constant Definitions *****************************/
/**
 * Register offsets for the Ethernet MAC.
 */
#تعریف_کن XEL_TXBUFF_جابه_جایی (0x00000000)			/**< Transmit Buffer */
#تعریف_کن XEL_MDIOADDR_جابه_جایی (XEL_TXBUFF_جابه_جایی + 0x07E4)/**< MDIO Address offset
ثبات*/
#تعریف_کن XEL_MDIOWR_جابه_جایی  (XEL_TXBUFF_جابه_جایی + 0x07E8)	/**< MDIO write data
							     register offset */
#تعریف_کن XEL_MDIORD_جابه_جایی (XEL_TXBUFF_جابه_جایی + 0x07EC)	/**< MDIO read data
							     register offset*/
#تعریف_کن XEL_MDIOCNTR_جابه_جایی (XEL_TXBUFF_جابه_جایی + 0x07F0)/**< MDIO Control
							     Register offset */
#تعریف_کن XEL_GIER_جابه_جایی   (XEL_TXBUFF_جابه_جایی + 0x07F8)	/**< Offset for the GIE
ثبات*/
#تعریف_کن XEL_TSR_جابه_جایی	  (XEL_TXBUFF_جابه_جایی + 0x07FC)	/**< Tx status */
#تعریف_کن XEL_TPLR_جابه_جایی   (XEL_TXBUFF_جابه_جایی + 0x07F4)	/**< Tx packet length */

#تعریف_کن XEL_RXBUFF_جابه_جایی (0x00001000)			/**< Receive Buffer */
#تعریف_کن XEL_RSR_جابه_جایی	  (XEL_RXBUFF_جابه_جایی + 0x07FC)	/**< Rx status */
#تعریف_کن XEL_RPLR_جابه_جایی   (XEL_RXBUFF_جابه_جایی + 0x0C)	/**< Rx packet length */

#تعریف_کن XEL_MAC_HI_جابه_جایی (XEL_TXBUFF_جابه_جایی + 0x14)	/**< MAC address hi
جابه_جایی*/
#تعریف_کن XEL_MAC_LO_جابه_جایی (XEL_TXBUFF_جابه_جایی)		/**< MAC address lo
جابه_جایی*/

#تعریف_کن XEL_میانگیر_جابه_جایی (0x00000800)			/**< Next buffer's
							     offset  same for
							     both TX and RX */
/**
 * MDIO Address/Write Data/Read Data Register Bit Masks
 */
#تعریف_کن XEL_MDIO_آدرس_ماسک		0x00003E0	/**< PHY Address mask */
#تعریف_کن XEL_MDIO_آدرس_لغزش		0x5		/**< PHY Address shift*/
#تعریف_کن XEL_MDIO_OP_ماسک		0x00000400	/**< PHY read access */

/**
 * MDIO Control Register Bit Masks
 */
#تعریف_کن XEL_MDIOCNTR_وضعیت_ماسک	0x00000001	/**< MDIO transfer in
پیشرفت*/
#تعریف_کن XEL_MDIOCNTR_ENABLE_ماسک	0x00000008	/**<  MDIO Enable */

/**
 * Global Interrupt Enable Register (GIER) Bit Masks
 */
#تعریف_کن XEL_GIER_GIE_ماسک		0x80000000	/**< Global Enable */

/**
 * Transmit Status Register (TSR) Bit Masks
 */
#تعریف_کن XEL_TSR_XMIT_BUSY_ماسک		0x00000001	/**< Xmit complete */
#تعریف_کن XEL_TSR_برنامه_ماسک		0x00000002	/**< Program the MAC
آدرس*/
#تعریف_کن XEL_TSR_XMIT_IE_ماسک		0x00000008	/**< Xmit interrupt
							     enable bit */
#تعریف_کن XEL_TSR_LOOPBACK_ماسک		0x00000010	/**< Loop back enable
بیت*/
#تعریف_کن XEL_TSR_XMIT_فعال_ماسک	0x80000000	/**< Buffer is active,
							     SW bit only. This
							     is not documented
							     in the HW spec */

/**
 * define for programming the MAC address into the EmacLite
 */
#تعریف_کن XEL_TSR_PROG_MAC_ADDR   (XEL_TSR_XMIT_BUSY_ماسک | XEL_TSR_برنامه_ماسک)

/**
 * Receive Status Register (RSR)
 */
#تعریف_کن XEL_RSR_RECV_انجامشده_ماسک		0x00000001	/**< Recv complete */
#تعریف_کن XEL_RSR_RECV_IE_ماسک		0x00000008	/**< Recv interrupt
							     enable bit */

/**
 * Transmit Packet Length Register (TPLR)
 */
#تعریف_کن XEL_TPLR_درازی_ماسک_HI		0x0000FF00 /**< Transmit packet length
							  upper byte */
#تعریف_کن XEL_TPLR_درازی_ماسک_LO		0x000000FF /**< Transmit packet length
							  lower byte */

/**
 * Receive Packet Length Register (RPLR)
 */
#تعریف_کن XEL_RPLR_درازی_ماسک_HI		0x0000FF00 /**< Receive packet length
							  upper byte */
#تعریف_کن XEL_RPLR_درازی_ماسک_LO		0x000000FF /**< Receive packet length
							  lower byte */

#تعریف_کن XEL_سرآیند_اندازه			14  /**< Size of header in bytes */
#تعریف_کن XEL_MTU_اندازه			1500 /**< Max size of data in frame */
#تعریف_کن XEL_FCS_اندازه			4    /**< Size of CRC */

#تعریف_کن XEL_سرآیند_جابه_جایی		12   /**< Offset to length field */
#تعریف_کن XEL_سرآیند_لغزش		16   /**< Right shift value to align
درازی*/


#تعریف_کن XEL_MAX_قاب_اندازه (XEL_سرآیند_اندازه+XEL_MTU_اندازه+ XEL_FCS_اندازه)	/**< Max
						length of Rx frame  used if
						length/type field
						contains the type (> 1500) */

#تعریف_کن XEL_MAX_TX_قاب_اندازه (XEL_سرآیند_اندازه + XEL_MTU_اندازه)	/**< Max
						length of Tx frame */


#تعریف_کن XEL_MAC_ADDR_اندازه		6	/**< length of MAC address */


/*
 * General Ethernet Definitions
 */
#تعریف_کن XEL_ETHER_PROTO_TYPE_IP		0x0800  /**< IP Protocol */
#تعریف_کن XEL_ETHER_PROTO_TYPE_ARP	0x0806  /**< ARP Protocol */
#تعریف_کن XEL_ETHER_PROTO_TYPE_VLAN	0x8100  /**< VLAN Tagged */
#تعریف_کن XEL_ARP_PACKET_اندازه		28  	/**< Max ARP packet size */
#تعریف_کن XEL_سرآیند_IP_درازی_جابه_جایی	16  	/**< IP Length Offset */
#تعریف_کن XEL_VLAN_برچسب_اندازه		4  	/**< VLAN Tag Size */

/***************** Macros (Inline Functions) Definitions *********************/

#تعریف_کن XEmacLite_In32 Xil_In32
#تعریف_کن XEmacLite_Out32 Xil_Out32

