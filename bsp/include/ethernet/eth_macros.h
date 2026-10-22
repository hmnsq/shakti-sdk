/************************** Constant Definitions *****************************/
/**
 * Register offsets for the Ethernet MAC.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_TXBUFF_ਵਿੱਥ (0x00000000)			/**< Transmit Buffer */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_MDIOADDR_ਵਿੱਥ (XEL_TXBUFF_ਵਿੱਥ + 0x07E4)/**< MDIO Address offset
ਰਜਿਸਟਰ*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_MDIOWR_ਵਿੱਥ  (XEL_TXBUFF_ਵਿੱਥ + 0x07E8)	/**< MDIO write data
							     register offset */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_MDIORD_ਵਿੱਥ (XEL_TXBUFF_ਵਿੱਥ + 0x07EC)	/**< MDIO read data
							     register offset*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_MDIOCNTR_ਵਿੱਥ (XEL_TXBUFF_ਵਿੱਥ + 0x07F0)/**< MDIO Control
							     Register offset */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_GIER_ਵਿੱਥ   (XEL_TXBUFF_ਵਿੱਥ + 0x07F8)	/**< Offset for the GIE
ਰਜਿਸਟਰ*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_TSR_ਵਿੱਥ	  (XEL_TXBUFF_ਵਿੱਥ + 0x07FC)	/**< Tx status */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_TPLR_ਵਿੱਥ   (XEL_TXBUFF_ਵਿੱਥ + 0x07F4)	/**< Tx packet length */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_RXBUFF_ਵਿੱਥ (0x00001000)			/**< Receive Buffer */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_RSR_ਵਿੱਥ	  (XEL_RXBUFF_ਵਿੱਥ + 0x07FC)	/**< Rx status */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_RPLR_ਵਿੱਥ   (XEL_RXBUFF_ਵਿੱਥ + 0x0C)	/**< Rx packet length */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_MAC_HI_ਵਿੱਥ (XEL_TXBUFF_ਵਿੱਥ + 0x14)	/**< MAC address hi
ਵਿੱਥ*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_MAC_LO_ਵਿੱਥ (XEL_TXBUFF_ਵਿੱਥ)		/**< MAC address lo
ਵਿੱਥ*/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_ਬਫਰ_ਵਿੱਥ (0x00000800)			/**< Next buffer's
							     offset  same for
							     both TX and RX */
/**
 * MDIO Address/Write Data/Read Data Register Bit Masks
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_MDIO_ਪਤਾ_ਨਕਾਬ		0x00003E0	/**< PHY Address mask */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_MDIO_ਪਤਾ_ਖਿਸਕਾਓ		0x5		/**< PHY Address shift*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_MDIO_OP_ਨਕਾਬ		0x00000400	/**< PHY read access */

/**
 * MDIO Control Register Bit Masks
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_MDIOCNTR_ਸਥਿਤੀ_ਨਕਾਬ	0x00000001	/**< MDIO transfer in
ਤਰੱਕੀ*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_MDIOCNTR_ENABLE_ਨਕਾਬ	0x00000008	/**<  MDIO Enable */

/**
 * Global Interrupt Enable Register (GIER) Bit Masks
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_GIER_GIE_ਨਕਾਬ		0x80000000	/**< Global Enable */

/**
 * Transmit Status Register (TSR) Bit Masks
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_TSR_XMIT_BUSY_ਨਕਾਬ		0x00000001	/**< Xmit complete */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_TSR_ਪ੍ਰੋਗਰਾਮ_ਨਕਾਬ		0x00000002	/**< Program the MAC
ਪਤਾ*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_TSR_XMIT_IE_ਨਕਾਬ		0x00000008	/**< Xmit interrupt
							     enable bit */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_TSR_LOOPBACK_ਨਕਾਬ		0x00000010	/**< Loop back enable
ਦੋਆਧਾਰੀ_ਅੰਕ*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_TSR_XMIT_ਸਰਗਰਮ_ਨਕਾਬ	0x80000000	/**< Buffer is active,
							     SW bit only. This
							     is not documented
							     in the HW spec */

/**
 * define for programming the MAC address into the EmacLite
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_TSR_PROG_MAC_ADDR   (XEL_TSR_XMIT_BUSY_ਨਕਾਬ | XEL_TSR_ਪ੍ਰੋਗਰਾਮ_ਨਕਾਬ)

/**
 * Receive Status Register (RSR)
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_RSR_RECV_ਪੂਰਾ_ਨਕਾਬ		0x00000001	/**< Recv complete */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_RSR_RECV_IE_ਨਕਾਬ		0x00000008	/**< Recv interrupt
							     enable bit */

/**
 * Transmit Packet Length Register (TPLR)
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_TPLR_ਲੰਮਾਈ_ਨਕਾਬ_HI		0x0000FF00 /**< Transmit packet length
							  upper byte */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_TPLR_ਲੰਮਾਈ_ਨਕਾਬ_LO		0x000000FF /**< Transmit packet length
							  lower byte */

/**
 * Receive Packet Length Register (RPLR)
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_RPLR_ਲੰਮਾਈ_ਨਕਾਬ_HI		0x0000FF00 /**< Receive packet length
							  upper byte */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_RPLR_ਲੰਮਾਈ_ਨਕਾਬ_LO		0x000000FF /**< Receive packet length
							  lower byte */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_ਸਿਰਲੇਖ_ਮਾਪ			14  /**< Size of header in bytes */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_MTU_ਮਾਪ			1500 /**< Max size of data in frame */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_FCS_ਮਾਪ			4    /**< Size of CRC */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_ਸਿਰਲੇਖ_ਵਿੱਥ		12   /**< Offset to length field */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_ਸਿਰਲੇਖ_ਖਿਸਕਾਓ		16   /**< Right shift value to align
ਲੰਮਾਈ*/


#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_MAX_ਚੌਖਟਾ_ਮਾਪ (XEL_ਸਿਰਲੇਖ_ਮਾਪ+XEL_MTU_ਮਾਪ+ XEL_FCS_ਮਾਪ)	/**< Max
						length of Rx frame  used if
						length/type field
						contains the type (> 1500) */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_MAX_TX_ਚੌਖਟਾ_ਮਾਪ (XEL_ਸਿਰਲੇਖ_ਮਾਪ + XEL_MTU_ਮਾਪ)	/**< Max
						length of Tx frame */


#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_MAC_ADDR_ਮਾਪ		6	/**< length of MAC address */


/*
 * General Ethernet Definitions
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_ETHER_PROTO_TYPE_IP		0x0800  /**< IP Protocol */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_ETHER_PROTO_TYPE_ARP	0x0806  /**< ARP Protocol */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_ETHER_PROTO_TYPE_VLAN	0x8100  /**< VLAN Tagged */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_ARP_PACKET_ਮਾਪ		28  	/**< Max ARP packet size */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_ਸਿਰਲੇਖ_IP_ਲੰਮਾਈ_ਵਿੱਥ	16  	/**< IP Length Offset */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEL_VLAN_ਟੈਗ_ਮਾਪ		4  	/**< VLAN Tag Size */

/***************** Macros (Inline Functions) Definitions *********************/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEmacLite_In32 Xil_In32
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XEmacLite_Out32 Xil_Out32

