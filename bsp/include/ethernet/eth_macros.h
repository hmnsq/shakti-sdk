/************************** Constant Definitions *****************************/
/**
 * Register offsets for the Ethernet MAC.
 */
#परिभाषय XEL_TXBUFF_विस्थापनम् (0x00000000)			/**< Transmit Buffer */
#परिभाषय XEL_MDIOADDR_विस्थापनम् (XEL_TXBUFF_विस्थापनम् + 0x07E4)/**< MDIO Address offset
पञ्जिकाकोशः*/
#परिभाषय XEL_MDIOWR_विस्थापनम्  (XEL_TXBUFF_विस्थापनम् + 0x07E8)	/**< MDIO write data
							     register offset */
#परिभाषय XEL_MDIORD_विस्थापनम् (XEL_TXBUFF_विस्थापनम् + 0x07EC)	/**< MDIO read data
							     register offset*/
#परिभाषय XEL_MDIOCNTR_विस्थापनम् (XEL_TXBUFF_विस्थापनम् + 0x07F0)/**< MDIO Control
							     Register offset */
#परिभाषय XEL_GIER_विस्थापनम्   (XEL_TXBUFF_विस्थापनम् + 0x07F8)	/**< Offset for the GIE
पञ्जिकाकोशः*/
#परिभाषय XEL_TSR_विस्थापनम्	  (XEL_TXBUFF_विस्थापनम् + 0x07FC)	/**< Tx status */
#परिभाषय XEL_TPLR_विस्थापनम्   (XEL_TXBUFF_विस्थापनम् + 0x07F4)	/**< Tx packet length */

#परिभाषय XEL_RXBUFF_विस्थापनम् (0x00001000)			/**< Receive Buffer */
#परिभाषय XEL_RSR_विस्थापनम्	  (XEL_RXBUFF_विस्थापनम् + 0x07FC)	/**< Rx status */
#परिभाषय XEL_RPLR_विस्थापनम्   (XEL_RXBUFF_विस्थापनम् + 0x0C)	/**< Rx packet length */

#परिभाषय XEL_MAC_HI_विस्थापनम् (XEL_TXBUFF_विस्थापनम् + 0x14)	/**< MAC address hi
विस्थापनम्*/
#परिभाषय XEL_MAC_LO_विस्थापनम् (XEL_TXBUFF_विस्थापनम्)		/**< MAC address lo
विस्थापनम्*/

#परिभाषय XEL_बफर_विस्थापनम् (0x00000800)			/**< Next buffer's
							     offset  same for
							     both TX and RX */
/**
 * MDIO Address/Write Data/Read Data Register Bit Masks
 */
#परिभाषय XEL_MDIO_स्थानाङ्कः_आवरणम्		0x00003E0	/**< PHY Address mask */
#परिभाषय XEL_MDIO_स्थानाङ्कः_सरणम्		0x5		/**< PHY Address shift*/
#परिभाषय XEL_MDIO_OP_आवरणम्		0x00000400	/**< PHY read access */

/**
 * MDIO Control Register Bit Masks
 */
#परिभाषय XEL_MDIOCNTR_स्थितिः_आवरणम्	0x00000001	/**< MDIO transfer in
प्रगतिः*/
#परिभाषय XEL_MDIOCNTR_ENABLE_आवरणम्	0x00000008	/**<  MDIO Enable */

/**
 * Global Interrupt Enable Register (GIER) Bit Masks
 */
#परिभाषय XEL_GIER_GIE_आवरणम्		0x80000000	/**< Global Enable */

/**
 * Transmit Status Register (TSR) Bit Masks
 */
#परिभाषय XEL_TSR_XMIT_BUSY_आवरणम्		0x00000001	/**< Xmit complete */
#परिभाषय XEL_TSR_क्रमादेशः_आवरणम्		0x00000002	/**< Program the MAC
स्थानाङ्कः*/
#परिभाषय XEL_TSR_XMIT_IE_आवरणम्		0x00000008	/**< Xmit interrupt
							     enable bit */
#परिभाषय XEL_TSR_LOOPBACK_आवरणम्		0x00000010	/**< Loop back enable
							     bit */
#परिभाषय XEL_TSR_XMIT_सक्रिय_आवरणम्	0x80000000	/**< Buffer is active,
							     SW bit only. This
							     is not documented
							     in the HW spec */

/**
 * define for programming the MAC address into the EmacLite
 */
#परिभाषय XEL_TSR_PROG_MAC_ADDR   (XEL_TSR_XMIT_BUSY_आवरणम् | XEL_TSR_क्रमादेशः_आवरणम्)

/**
 * Receive Status Register (RSR)
 */
#परिभाषय XEL_RSR_RECV_समाप्तम्_आवरणम्		0x00000001	/**< Recv complete */
#परिभाषय XEL_RSR_RECV_IE_आवरणम्		0x00000008	/**< Recv interrupt
							     enable bit */

/**
 * Transmit Packet Length Register (TPLR)
 */
#परिभाषय XEL_TPLR_दीर्घता_आवरणम्_HI		0x0000FF00 /**< Transmit packet length
							  upper byte */
#परिभाषय XEL_TPLR_दीर्घता_आवरणम्_LO		0x000000FF /**< Transmit packet length
							  lower byte */

/**
 * Receive Packet Length Register (RPLR)
 */
#परिभाषय XEL_RPLR_दीर्घता_आवरणम्_HI		0x0000FF00 /**< Receive packet length
							  upper byte */
#परिभाषय XEL_RPLR_दीर्घता_आवरणम्_LO		0x000000FF /**< Receive packet length
							  lower byte */

#परिभाषय XEL_शीर्षकम्_आकार			14  /**< Size of header in bytes */
#परिभाषय XEL_MTU_आकार			1500 /**< Max size of data in frame */
#परिभाषय XEL_FCS_आकार			4    /**< Size of CRC */

#परिभाषय XEL_शीर्षकम्_विस्थापनम्		12   /**< Offset to length field */
#परिभाषय XEL_शीर्षकम्_सरणम्		16   /**< Right shift value to align
दीर्घता*/


#परिभाषय XEL_MAX_FRAME_आकार (XEL_शीर्षकम्_आकार+XEL_MTU_आकार+ XEL_FCS_आकार)	/**< Max
						length of Rx frame  used if
						length/type field
						contains the type (> 1500) */

#परिभाषय XEL_MAX_TX_FRAME_आकार (XEL_शीर्षकम्_आकार + XEL_MTU_आकार)	/**< Max
						length of Tx frame */


#परिभाषय XEL_MAC_ADDR_आकार		6	/**< length of MAC address */


/*
 * General Ethernet Definitions
 */
#परिभाषय XEL_ETHER_PROTO_TYPE_IP		0x0800  /**< IP Protocol */
#परिभाषय XEL_ETHER_PROTO_TYPE_ARP	0x0806  /**< ARP Protocol */
#परिभाषय XEL_ETHER_PROTO_TYPE_VLAN	0x8100  /**< VLAN Tagged */
#परिभाषय XEL_ARP_PACKET_आकार		28  	/**< Max ARP packet size */
#परिभाषय XEL_शीर्षकम्_IP_दीर्घता_विस्थापनम्	16  	/**< IP Length Offset */
#परिभाषय XEL_VLAN_चिह्नकम्_आकार		4  	/**< VLAN Tag Size */

/***************** Macros (Inline Functions) Definitions *********************/

#परिभाषय XEmacLite_In32 Xil_In32
#परिभाषय XEmacLite_Out32 Xil_Out32

