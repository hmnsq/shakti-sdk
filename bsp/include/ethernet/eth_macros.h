/************************** Constant Definitions *****************************/
/**
 * Register offsets for the Ethernet MAC.
 */
#تعریف_کرو XEL_TXBUFF_وتھ (0x00000000)			/**< Transmit Buffer */
#تعریف_کرو XEL_MDIOADDR_وتھ (XEL_TXBUFF_وتھ + 0x07E4)/**< MDIO Address offset
رجسٹر*/
#تعریف_کرو XEL_MDIOWR_وتھ  (XEL_TXBUFF_وتھ + 0x07E8)	/**< MDIO write data
							     register offset */
#تعریف_کرو XEL_MDIORD_وتھ (XEL_TXBUFF_وتھ + 0x07EC)	/**< MDIO read data
							     register offset*/
#تعریف_کرو XEL_MDIOCNTR_وتھ (XEL_TXBUFF_وتھ + 0x07F0)/**< MDIO Control
							     Register offset */
#تعریف_کرو XEL_GIER_وتھ   (XEL_TXBUFF_وتھ + 0x07F8)	/**< Offset for the GIE
رجسٹر*/
#تعریف_کرو XEL_TSR_وتھ	  (XEL_TXBUFF_وتھ + 0x07FC)	/**< Tx status */
#تعریف_کرو XEL_TPLR_وتھ   (XEL_TXBUFF_وتھ + 0x07F4)	/**< Tx packet length */

#تعریف_کرو XEL_RXBUFF_وتھ (0x00001000)			/**< Receive Buffer */
#تعریف_کرو XEL_RSR_وتھ	  (XEL_RXBUFF_وتھ + 0x07FC)	/**< Rx status */
#تعریف_کرو XEL_RPLR_وتھ   (XEL_RXBUFF_وتھ + 0x0C)	/**< Rx packet length */

#تعریف_کرو XEL_MAC_HI_وتھ (XEL_TXBUFF_وتھ + 0x14)	/**< MAC address hi
وتھ*/
#تعریف_کرو XEL_MAC_LO_وتھ (XEL_TXBUFF_وتھ)		/**< MAC address lo
وتھ*/

#تعریف_کرو XEL_بفر_وتھ (0x00000800)			/**< Next buffer's
							     offset  same for
							     both TX and RX */
/**
 * MDIO Address/Write Data/Read Data Register Bit Masks
 */
#تعریف_کرو XEL_MDIO_پتہ_نقاب		0x00003E0	/**< PHY Address mask */
#تعریف_کرو XEL_MDIO_پتہ_کھسکاؤ		0x5		/**< PHY Address shift*/
#تعریف_کرو XEL_MDIO_OP_نقاب		0x00000400	/**< PHY read access */

/**
 * MDIO Control Register Bit Masks
 */
#تعریف_کرو XEL_MDIOCNTR_حالت_نقاب	0x00000001	/**< MDIO transfer in
ترقی*/
#تعریف_کرو XEL_MDIOCNTR_ENABLE_نقاب	0x00000008	/**<  MDIO Enable */

/**
 * Global Interrupt Enable Register (GIER) Bit Masks
 */
#تعریف_کرو XEL_GIER_GIE_نقاب		0x80000000	/**< Global Enable */

/**
 * Transmit Status Register (TSR) Bit Masks
 */
#تعریف_کرو XEL_TSR_XMIT_BUSY_نقاب		0x00000001	/**< Xmit complete */
#تعریف_کرو XEL_TSR_پروگرام_نقاب		0x00000002	/**< Program the MAC
پتہ*/
#تعریف_کرو XEL_TSR_XMIT_IE_نقاب		0x00000008	/**< Xmit interrupt
							     enable bit */
#تعریف_کرو XEL_TSR_LOOPBACK_نقاب		0x00000010	/**< Loop back enable
ثنائی_ہندسہ*/
#تعریف_کرو XEL_TSR_XMIT_سرگرم_نقاب	0x80000000	/**< Buffer is active,
							     SW bit only. This
							     is not documented
							     in the HW spec */

/**
 * define for programming the MAC address into the EmacLite
 */
#تعریف_کرو XEL_TSR_PROG_MAC_ADDR   (XEL_TSR_XMIT_BUSY_نقاب | XEL_TSR_پروگرام_نقاب)

/**
 * Receive Status Register (RSR)
 */
#تعریف_کرو XEL_RSR_RECV_پورا_نقاب		0x00000001	/**< Recv complete */
#تعریف_کرو XEL_RSR_RECV_IE_نقاب		0x00000008	/**< Recv interrupt
							     enable bit */

/**
 * Transmit Packet Length Register (TPLR)
 */
#تعریف_کرو XEL_TPLR_لمائی_نقاب_HI		0x0000FF00 /**< Transmit packet length
							  upper byte */
#تعریف_کرو XEL_TPLR_لمائی_نقاب_LO		0x000000FF /**< Transmit packet length
							  lower byte */

/**
 * Receive Packet Length Register (RPLR)
 */
#تعریف_کرو XEL_RPLR_لمائی_نقاب_HI		0x0000FF00 /**< Receive packet length
							  upper byte */
#تعریف_کرو XEL_RPLR_لمائی_نقاب_LO		0x000000FF /**< Receive packet length
							  lower byte */

#تعریف_کرو XEL_سرخی_ناپ			14  /**< Size of header in bytes */
#تعریف_کرو XEL_MTU_ناپ			1500 /**< Max size of data in frame */
#تعریف_کرو XEL_FCS_ناپ			4    /**< Size of CRC */

#تعریف_کرو XEL_سرخی_وتھ		12   /**< Offset to length field */
#تعریف_کرو XEL_سرخی_کھسکاؤ		16   /**< Right shift value to align
لمائی*/


#تعریف_کرو XEL_MAX_چوکھٹا_ناپ (XEL_سرخی_ناپ+XEL_MTU_ناپ+ XEL_FCS_ناپ)	/**< Max
						length of Rx frame  used if
						length/type field
						contains the type (> 1500) */

#تعریف_کرو XEL_MAX_TX_چوکھٹا_ناپ (XEL_سرخی_ناپ + XEL_MTU_ناپ)	/**< Max
						length of Tx frame */


#تعریف_کرو XEL_MAC_ADDR_ناپ		6	/**< length of MAC address */


/*
 * General Ethernet Definitions
 */
#تعریف_کرو XEL_ETHER_PROTO_TYPE_IP		0x0800  /**< IP Protocol */
#تعریف_کرو XEL_ETHER_PROTO_TYPE_ARP	0x0806  /**< ARP Protocol */
#تعریف_کرو XEL_ETHER_PROTO_TYPE_VLAN	0x8100  /**< VLAN Tagged */
#تعریف_کرو XEL_ARP_PACKET_ناپ		28  	/**< Max ARP packet size */
#تعریف_کرو XEL_سرخی_IP_لمائی_وتھ	16  	/**< IP Length Offset */
#تعریف_کرو XEL_VLAN_ٹیگ_ناپ		4  	/**< VLAN Tag Size */

/***************** Macros (Inline Functions) Definitions *********************/

#تعریف_کرو XEmacLite_In32 Xil_In32
#تعریف_کرو XEmacLite_Out32 Xil_Out32

