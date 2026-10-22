/************************** Constant Definitions *****************************/
/**
 * Register offsets for the Ethernet MAC.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_TXBUFF_ಸ್ಥಾನಾಂತರ (0x00000000)			/**< Transmit Buffer */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_MDIOADDR_ಸ್ಥಾನಾಂತರ (XEL_TXBUFF_ಸ್ಥಾನಾಂತರ + 0x07E4)/**< MDIO Address offset
ರಿಜಿಸ್ಟರ್*/
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_MDIOWR_ಸ್ಥಾನಾಂತರ  (XEL_TXBUFF_ಸ್ಥಾನಾಂತರ + 0x07E8)	/**< MDIO write data
							     register offset */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_MDIORD_ಸ್ಥಾನಾಂತರ (XEL_TXBUFF_ಸ್ಥಾನಾಂತರ + 0x07EC)	/**< MDIO read data
							     register offset*/
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_MDIOCNTR_ಸ್ಥಾನಾಂತರ (XEL_TXBUFF_ಸ್ಥಾನಾಂತರ + 0x07F0)/**< MDIO Control
							     Register offset */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_GIER_ಸ್ಥಾನಾಂತರ   (XEL_TXBUFF_ಸ್ಥಾನಾಂತರ + 0x07F8)	/**< Offset for the GIE
ರಿಜಿಸ್ಟರ್*/
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_TSR_ಸ್ಥಾನಾಂತರ	  (XEL_TXBUFF_ಸ್ಥಾನಾಂತರ + 0x07FC)	/**< Tx status */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_TPLR_ಸ್ಥಾನಾಂತರ   (XEL_TXBUFF_ಸ್ಥಾನಾಂತರ + 0x07F4)	/**< Tx packet length */

#ವ್ಯಾಖ್ಯಾನಿಸು XEL_RXBUFF_ಸ್ಥಾನಾಂತರ (0x00001000)			/**< Receive Buffer */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_RSR_ಸ್ಥಾನಾಂತರ	  (XEL_RXBUFF_ಸ್ಥಾನಾಂತರ + 0x07FC)	/**< Rx status */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_RPLR_ಸ್ಥಾನಾಂತರ   (XEL_RXBUFF_ಸ್ಥಾನಾಂತರ + 0x0C)	/**< Rx packet length */

#ವ್ಯಾಖ್ಯಾನಿಸು XEL_MAC_HI_ಸ್ಥಾನಾಂತರ (XEL_TXBUFF_ಸ್ಥಾನಾಂತರ + 0x14)	/**< MAC address hi
ಸ್ಥಾನಾಂತರ*/
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_MAC_LO_ಸ್ಥಾನಾಂತರ (XEL_TXBUFF_ಸ್ಥಾನಾಂತರ)		/**< MAC address lo
ಸ್ಥಾನಾಂತರ*/

#ವ್ಯಾಖ್ಯಾನಿಸು XEL_ಬಫರ್_ಸ್ಥಾನಾಂತರ (0x00000800)			/**< Next buffer's
							     offset  same for
							     both TX and RX */
/**
 * MDIO Address/Write Data/Read Data Register Bit Masks
 */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_MDIO_ವಿಳಾಸ_ಮುಖವಾಡ		0x00003E0	/**< PHY Address mask */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_MDIO_ವಿಳಾಸ_ಸರಿಸು		0x5		/**< PHY Address shift*/
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_MDIO_OP_ಮುಖವಾಡ		0x00000400	/**< PHY read access */

/**
 * MDIO Control Register Bit Masks
 */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_MDIOCNTR_ಸ್ಥಿತಿ_ಮುಖವಾಡ	0x00000001	/**< MDIO transfer in
ಪ್ರಗತಿ*/
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_MDIOCNTR_ENABLE_ಮುಖವಾಡ	0x00000008	/**<  MDIO Enable */

/**
 * Global Interrupt Enable Register (GIER) Bit Masks
 */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_GIER_GIE_ಮುಖವಾಡ		0x80000000	/**< Global Enable */

/**
 * Transmit Status Register (TSR) Bit Masks
 */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_TSR_XMIT_BUSY_ಮುಖವಾಡ		0x00000001	/**< Xmit complete */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_TSR_ಕಾರ್ಯಕ್ರಮ_ಮುಖವಾಡ		0x00000002	/**< Program the MAC
ವಿಳಾಸ*/
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_TSR_XMIT_IE_ಮುಖವಾಡ		0x00000008	/**< Xmit interrupt
							     enable bit */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_TSR_LOOPBACK_ಮುಖವಾಡ		0x00000010	/**< Loop back enable
ಬಿಟ್*/
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_TSR_XMIT_ಸಕ್ರಿಯ_ಮುಖವಾಡ	0x80000000	/**< Buffer is active,
							     SW bit only. This
							     is not documented
							     in the HW spec */

/**
 * define for programming the MAC address into the EmacLite
 */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_TSR_PROG_MAC_ADDR   (XEL_TSR_XMIT_BUSY_ಮುಖವಾಡ | XEL_TSR_ಕಾರ್ಯಕ್ರಮ_ಮುಖವಾಡ)

/**
 * Receive Status Register (RSR)
 */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_RSR_RECV_ಮುಗಿದ_ಮುಖವಾಡ		0x00000001	/**< Recv complete */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_RSR_RECV_IE_ಮುಖವಾಡ		0x00000008	/**< Recv interrupt
							     enable bit */

/**
 * Transmit Packet Length Register (TPLR)
 */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_TPLR_ಉದ್ದಳತೆ_ಮುಖವಾಡ_HI		0x0000FF00 /**< Transmit packet length
							  upper byte */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_TPLR_ಉದ್ದಳತೆ_ಮುಖವಾಡ_LO		0x000000FF /**< Transmit packet length
							  lower byte */

/**
 * Receive Packet Length Register (RPLR)
 */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_RPLR_ಉದ್ದಳತೆ_ಮುಖವಾಡ_HI		0x0000FF00 /**< Receive packet length
							  upper byte */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_RPLR_ಉದ್ದಳತೆ_ಮುಖವಾಡ_LO		0x000000FF /**< Receive packet length
							  lower byte */

#ವ್ಯಾಖ್ಯಾನಿಸು XEL_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ			14  /**< Size of header in bytes */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_MTU_ಗಾತ್ರ			1500 /**< Max size of data in frame */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_FCS_ಗಾತ್ರ			4    /**< Size of CRC */

#ವ್ಯಾಖ್ಯಾನಿಸು XEL_ಶೀರ್ಷಿಕೆ_ಸ್ಥಾನಾಂತರ		12   /**< Offset to length field */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_ಶೀರ್ಷಿಕೆ_ಸರಿಸು		16   /**< Right shift value to align
ಉದ್ದಳತೆ*/


#ವ್ಯಾಖ್ಯಾನಿಸು XEL_MAX_ಚೌಕಟ್ಟು_ಗಾತ್ರ (XEL_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ+XEL_MTU_ಗಾತ್ರ+ XEL_FCS_ಗಾತ್ರ)	/**< Max
						length of Rx frame  used if
						length/type field
						contains the type (> 1500) */

#ವ್ಯಾಖ್ಯಾನಿಸು XEL_MAX_TX_ಚೌಕಟ್ಟು_ಗಾತ್ರ (XEL_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ + XEL_MTU_ಗಾತ್ರ)	/**< Max
						length of Tx frame */


#ವ್ಯಾಖ್ಯಾನಿಸು XEL_MAC_ADDR_ಗಾತ್ರ		6	/**< length of MAC address */


/*
 * General Ethernet Definitions
 */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_ETHER_PROTO_TYPE_IP		0x0800  /**< IP Protocol */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_ETHER_PROTO_TYPE_ARP	0x0806  /**< ARP Protocol */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_ETHER_PROTO_TYPE_VLAN	0x8100  /**< VLAN Tagged */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_ARP_PACKET_ಗಾತ್ರ		28  	/**< Max ARP packet size */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_ಶೀರ್ಷಿಕೆ_IP_ಉದ್ದಳತೆ_ಸ್ಥಾನಾಂತರ	16  	/**< IP Length Offset */
#ವ್ಯಾಖ್ಯಾನಿಸು XEL_VLAN_ಟ್ಯಾಗ್_ಗಾತ್ರ		4  	/**< VLAN Tag Size */

/***************** Macros (Inline Functions) Definitions *********************/

#ವ್ಯಾಖ್ಯಾನಿಸು XEmacLite_In32 Xil_In32
#ವ್ಯಾಖ್ಯಾನಿಸು XEmacLite_Out32 Xil_Out32

