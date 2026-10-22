/************************** Constant Definitions *****************************/
/**
 * Register offsets for the Ethernet MAC.
 */
#నిర్వచించు XEL_TXBUFF_స్థానభ్రంశం (0x00000000)			/**< Transmit Buffer */
#నిర్వచించు XEL_MDIOADDR_స్థానభ్రంశం (XEL_TXBUFF_స్థానభ్రంశం + 0x07E4)/**< MDIO Address offset
రిజిస్టరు*/
#నిర్వచించు XEL_MDIOWR_స్థానభ్రంశం  (XEL_TXBUFF_స్థానభ్రంశం + 0x07E8)	/**< MDIO write data
							     register offset */
#నిర్వచించు XEL_MDIORD_స్థానభ్రంశం (XEL_TXBUFF_స్థానభ్రంశం + 0x07EC)	/**< MDIO read data
							     register offset*/
#నిర్వచించు XEL_MDIOCNTR_స్థానభ్రంశం (XEL_TXBUFF_స్థానభ్రంశం + 0x07F0)/**< MDIO Control
							     Register offset */
#నిర్వచించు XEL_GIER_స్థానభ్రంశం   (XEL_TXBUFF_స్థానభ్రంశం + 0x07F8)	/**< Offset for the GIE
రిజిస్టరు*/
#నిర్వచించు XEL_TSR_స్థానభ్రంశం	  (XEL_TXBUFF_స్థానభ్రంశం + 0x07FC)	/**< Tx status */
#నిర్వచించు XEL_TPLR_స్థానభ్రంశం   (XEL_TXBUFF_స్థానభ్రంశం + 0x07F4)	/**< Tx packet length */

#నిర్వచించు XEL_RXBUFF_స్థానభ్రంశం (0x00001000)			/**< Receive Buffer */
#నిర్వచించు XEL_RSR_స్థానభ్రంశం	  (XEL_RXBUFF_స్థానభ్రంశం + 0x07FC)	/**< Rx status */
#నిర్వచించు XEL_RPLR_స్థానభ్రంశం   (XEL_RXBUFF_స్థానభ్రంశం + 0x0C)	/**< Rx packet length */

#నిర్వచించు XEL_MAC_HI_స్థానభ్రంశం (XEL_TXBUFF_స్థానభ్రంశం + 0x14)	/**< MAC address hi
స్థానభ్రంశం*/
#నిర్వచించు XEL_MAC_LO_స్థానభ్రంశం (XEL_TXBUFF_స్థానభ్రంశం)		/**< MAC address lo
స్థానభ్రంశం*/

#నిర్వచించు XEL_బఫరు_స్థానభ్రంశం (0x00000800)			/**< Next buffer's
							     offset  same for
							     both TX and RX */
/**
 * MDIO Address/Write Data/Read Data Register Bit Masks
 */
#నిర్వచించు XEL_MDIO_చిరునామా_ముసుగు		0x00003E0	/**< PHY Address mask */
#నిర్వచించు XEL_MDIO_చిరునామా_జరుపు		0x5		/**< PHY Address shift*/
#నిర్వచించు XEL_MDIO_OP_ముసుగు		0x00000400	/**< PHY read access */

/**
 * MDIO Control Register Bit Masks
 */
#నిర్వచించు XEL_MDIOCNTR_స్థితి_ముసుగు	0x00000001	/**< MDIO transfer in
పురోగతి*/
#నిర్వచించు XEL_MDIOCNTR_ENABLE_ముసుగు	0x00000008	/**<  MDIO Enable */

/**
 * Global Interrupt Enable Register (GIER) Bit Masks
 */
#నిర్వచించు XEL_GIER_GIE_ముసుగు		0x80000000	/**< Global Enable */

/**
 * Transmit Status Register (TSR) Bit Masks
 */
#నిర్వచించు XEL_TSR_XMIT_BUSY_ముసుగు		0x00000001	/**< Xmit complete */
#నిర్వచించు XEL_TSR_కార్యక్రమం_ముసుగు		0x00000002	/**< Program the MAC
చిరునామా*/
#నిర్వచించు XEL_TSR_XMIT_IE_ముసుగు		0x00000008	/**< Xmit interrupt
							     enable bit */
#నిర్వచించు XEL_TSR_LOOPBACK_ముసుగు		0x00000010	/**< Loop back enable
బిట్టు*/
#నిర్వచించు XEL_TSR_XMIT_చురుకైన_ముసుగు	0x80000000	/**< Buffer is active,
							     SW bit only. This
							     is not documented
							     in the HW spec */

/**
 * define for programming the MAC address into the EmacLite
 */
#నిర్వచించు XEL_TSR_PROG_MAC_ADDR   (XEL_TSR_XMIT_BUSY_ముసుగు | XEL_TSR_కార్యక్రమం_ముసుగు)

/**
 * Receive Status Register (RSR)
 */
#నిర్వచించు XEL_RSR_RECV_పూర్తి_ముసుగు		0x00000001	/**< Recv complete */
#నిర్వచించు XEL_RSR_RECV_IE_ముసుగు		0x00000008	/**< Recv interrupt
							     enable bit */

/**
 * Transmit Packet Length Register (TPLR)
 */
#నిర్వచించు XEL_TPLR_నిడివి_ముసుగు_HI		0x0000FF00 /**< Transmit packet length
							  upper byte */
#నిర్వచించు XEL_TPLR_నిడివి_ముసుగు_LO		0x000000FF /**< Transmit packet length
							  lower byte */

/**
 * Receive Packet Length Register (RPLR)
 */
#నిర్వచించు XEL_RPLR_నిడివి_ముసుగు_HI		0x0000FF00 /**< Receive packet length
							  upper byte */
#నిర్వచించు XEL_RPLR_నిడివి_ముసుగు_LO		0x000000FF /**< Receive packet length
							  lower byte */

#నిర్వచించు XEL_శీర్షిక_కొలత			14  /**< Size of header in bytes */
#నిర్వచించు XEL_MTU_కొలత			1500 /**< Max size of data in frame */
#నిర్వచించు XEL_FCS_కొలత			4    /**< Size of CRC */

#నిర్వచించు XEL_శీర్షిక_స్థానభ్రంశం		12   /**< Offset to length field */
#నిర్వచించు XEL_శీర్షిక_జరుపు		16   /**< Right shift value to align
నిడివి*/


#నిర్వచించు XEL_MAX_చట్రం_కొలత (XEL_శీర్షిక_కొలత+XEL_MTU_కొలత+ XEL_FCS_కొలత)	/**< Max
						length of Rx frame  used if
						length/type field
						contains the type (> 1500) */

#నిర్వచించు XEL_MAX_TX_చట్రం_కొలత (XEL_శీర్షిక_కొలత + XEL_MTU_కొలత)	/**< Max
						length of Tx frame */


#నిర్వచించు XEL_MAC_ADDR_కొలత		6	/**< length of MAC address */


/*
 * General Ethernet Definitions
 */
#నిర్వచించు XEL_ETHER_PROTO_TYPE_IP		0x0800  /**< IP Protocol */
#నిర్వచించు XEL_ETHER_PROTO_TYPE_ARP	0x0806  /**< ARP Protocol */
#నిర్వచించు XEL_ETHER_PROTO_TYPE_VLAN	0x8100  /**< VLAN Tagged */
#నిర్వచించు XEL_ARP_PACKET_కొలత		28  	/**< Max ARP packet size */
#నిర్వచించు XEL_శీర్షిక_IP_నిడివి_స్థానభ్రంశం	16  	/**< IP Length Offset */
#నిర్వచించు XEL_VLAN_ట్యాగ్_కొలత		4  	/**< VLAN Tag Size */

/***************** Macros (Inline Functions) Definitions *********************/

#నిర్వచించు XEmacLite_In32 Xil_In32
#నిర్వచించు XEmacLite_Out32 Xil_Out32

