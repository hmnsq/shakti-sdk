/************************** Constant Definitions *****************************/
/**
 * Register offsets for the Ethernet MAC.
 */
#घोषणा XEL_TXBUFF_OFFSET (0x00000000)			/**< Transmit Buffer */
#घोषणा XEL_MDIOADDR_OFFSET (XEL_TXBUFF_OFFSET + 0x07E4)/**< MDIO Address offset
							     register */
#घोषणा XEL_MDIOWR_OFFSET  (XEL_TXBUFF_OFFSET + 0x07E8)	/**< MDIO write data
							     register offset */
#घोषणा XEL_MDIORD_OFFSET (XEL_TXBUFF_OFFSET + 0x07EC)	/**< MDIO read data
							     register offset*/
#घोषणा XEL_MDIOCNTR_OFFSET (XEL_TXBUFF_OFFSET + 0x07F0)/**< MDIO Control
							     Register offset */
#घोषणा XEL_GIER_OFFSET   (XEL_TXBUFF_OFFSET + 0x07F8)	/**< Offset for the GIE
							     Register */
#घोषणा XEL_TSR_OFFSET	  (XEL_TXBUFF_OFFSET + 0x07FC)	/**< Tx status */
#घोषणा XEL_TPLR_OFFSET   (XEL_TXBUFF_OFFSET + 0x07F4)	/**< Tx packet length */

#घोषणा XEL_RXBUFF_OFFSET (0x00001000)			/**< Receive Buffer */
#घोषणा XEL_RSR_OFFSET	  (XEL_RXBUFF_OFFSET + 0x07FC)	/**< Rx status */
#घोषणा XEL_RPLR_OFFSET   (XEL_RXBUFF_OFFSET + 0x0C)	/**< Rx packet length */

#घोषणा XEL_MAC_HI_OFFSET (XEL_TXBUFF_OFFSET + 0x14)	/**< MAC address hi
							     offset */
#घोषणा XEL_MAC_LO_OFFSET (XEL_TXBUFF_OFFSET)		/**< MAC address lo
							     offset */

#घोषणा XEL_बफर_OFFSET (0x00000800)			/**< Next buffer's
							     offset  same for
							     both TX and RX */
/**
 * MDIO Address/Write Data/Read Data Register Bit Masks
 */
#घोषणा XEL_MDIO_ADDRESS_MASK		0x00003E0	/**< PHY Address mask */
#घोषणा XEL_MDIO_ADDRESS_SHIFT		0x5		/**< PHY Address shift*/
#घोषणा XEL_MDIO_OP_MASK		0x00000400	/**< PHY read access */

/**
 * MDIO Control Register Bit Masks
 */
#घोषणा XEL_MDIOCNTR_STATUS_MASK	0x00000001	/**< MDIO transfer in
							     Progress */
#घोषणा XEL_MDIOCNTR_ENABLE_MASK	0x00000008	/**<  MDIO Enable */

/**
 * Global Interrupt Enable Register (GIER) Bit Masks
 */
#घोषणा XEL_GIER_GIE_MASK		0x80000000	/**< Global Enable */

/**
 * Transmit Status Register (TSR) Bit Masks
 */
#घोषणा XEL_TSR_XMIT_BUSY_MASK		0x00000001	/**< Xmit complete */
#घोषणा XEL_TSR_PROGRAM_MASK		0x00000002	/**< Program the MAC
							     address */
#घोषणा XEL_TSR_XMIT_IE_MASK		0x00000008	/**< Xmit interrupt
							     enable bit */
#घोषणा XEL_TSR_LOOPBACK_MASK		0x00000010	/**< Loop back enable
							     bit */
#घोषणा XEL_TSR_XMIT_ACTIVE_MASK	0x80000000	/**< Buffer is active,
							     SW bit only. This
							     is not documented
							     in the HW spec */

/**
 * define for programming the MAC address into the EmacLite
 */
#घोषणा XEL_TSR_PROG_MAC_ADDR   (XEL_TSR_XMIT_BUSY_MASK | XEL_TSR_PROGRAM_MASK)

/**
 * Receive Status Register (RSR)
 */
#घोषणा XEL_RSR_RECV_DONE_MASK		0x00000001	/**< Recv complete */
#घोषणा XEL_RSR_RECV_IE_MASK		0x00000008	/**< Recv interrupt
							     enable bit */

/**
 * Transmit Packet Length Register (TPLR)
 */
#घोषणा XEL_TPLR_लंबाई_MASK_HI		0x0000FF00 /**< Transmit packet length
							  upper byte */
#घोषणा XEL_TPLR_लंबाई_MASK_LO		0x000000FF /**< Transmit packet length
							  lower byte */

/**
 * Receive Packet Length Register (RPLR)
 */
#घोषणा XEL_RPLR_लंबाई_MASK_HI		0x0000FF00 /**< Receive packet length
							  upper byte */
#घोषणा XEL_RPLR_लंबाई_MASK_LO		0x000000FF /**< Receive packet length
							  lower byte */

#घोषणा XEL_HEADER_आकार			14  /**< Size of header in bytes */
#घोषणा XEL_MTU_आकार			1500 /**< Max size of data in frame */
#घोषणा XEL_FCS_आकार			4    /**< Size of CRC */

#घोषणा XEL_HEADER_OFFSET		12   /**< Offset to length field */
#घोषणा XEL_HEADER_SHIFT		16   /**< Right shift value to align
लंबाई*/


#घोषणा XEL_MAX_FRAME_आकार (XEL_HEADER_आकार+XEL_MTU_आकार+ XEL_FCS_आकार)	/**< Max
						length of Rx frame  used if
						length/type field
						contains the type (> 1500) */

#घोषणा XEL_MAX_TX_FRAME_आकार (XEL_HEADER_आकार + XEL_MTU_आकार)	/**< Max
						length of Tx frame */


#घोषणा XEL_MAC_ADDR_आकार		6	/**< length of MAC address */


/*
 * General Ethernet Definitions
 */
#घोषणा XEL_ETHER_PROTO_TYPE_IP		0x0800  /**< IP Protocol */
#घोषणा XEL_ETHER_PROTO_TYPE_ARP	0x0806  /**< ARP Protocol */
#घोषणा XEL_ETHER_PROTO_TYPE_VLAN	0x8100  /**< VLAN Tagged */
#घोषणा XEL_ARP_PACKET_आकार		28  	/**< Max ARP packet size */
#घोषणा XEL_HEADER_IP_लंबाई_OFFSET	16  	/**< IP Length Offset */
#घोषणा XEL_VLAN_TAG_आकार		4  	/**< VLAN Tag Size */

/***************** Macros (Inline Functions) Definitions *********************/

#घोषणा XEmacLite_In32 Xil_In32
#घोषणा XEmacLite_Out32 Xil_Out32

