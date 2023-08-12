/**
 * @file server.c
 * @brief This file contains implementations for UDP communication functions.
 */

#include "main_Inner_System.h"

/**
 * @brief Callback function for receiving UDP packets.
 *
 * This function is a callback that gets triggered when a UDP packet is received.
 * It checks if the packet has already been processed or if its length exceeds
 * the maximum buffer length. If conditions are met, the packet is dropped. Otherwise,
 * the sender information is stored, and the packet payload is copied. The callback
 * flag is set, and the pbuf is freed.
 *
 * @param arg Unused argument.
 * @param upcb Pointer to the UDP control block.
 * @param p Pointer to the received pbuf.
 * @param addr Pointer to the source IP address.
 * @param port Source port number.
 */
void udp_receive_callback(void* arg, struct udp_pcb* upcb, struct pbuf* p, const ip_addr_t* addr, u16_t port)
{
	/** Check if we finished with the last packet */
	if(callback_flag == 1 || p->len > MAX_BUF_LEN)
	{
		/** Drop the packet */
		pbuf_free(p);
		return;
	}
	/** Store the sender information */
	ip_addr_copy(dest_ipaddr, *addr);
	dest_port = port;
	memcpy(&incoming_message, p->payload, p->len);
	incomming_len = p->len;

	callback_flag = 1;
	/** free the pbuf */
	pbuf_free(p);
}

/**
 * @brief Send a UDP packet.
 *
 * This function sends a UDP packet using the provided PCB (Protocol Control Block),
 * payload, IP address, and port. It allocates a pbuf, copies the payload, sends
 * the packet, and then frees the pbuf.
 *
 * @param pcb Pointer to the UDP Protocol Control Block.
 * @param payload Pointer to the data to be sent.
 * @param payload_len Length of the data to be sent.
 * @param ipaddr Pointer to the destination IP address.
 * @param port Destination port number.
 * @return Error code indicating the success or failure of the operation.
 */
err_t send_packet(struct udp_pcb* pcb, const void* payload, u16_t payload_len, const ip_addr_t* ipaddr, u16_t port)
{
    err_t err;
    struct pbuf* p;

    /** allocate a pbuf for the payload */
    p = pbuf_alloc(PBUF_TRANSPORT, payload_len, PBUF_RAM);
    if (!p) {
        /** failed to allocate pbuf */
        return ERR_MEM;
    }

    /** copy the payload into the pbuf */
    memcpy(p->payload, payload, payload_len);

    /** send the packet */
    err = udp_sendto(pcb, p, ipaddr, port);

    /** free the pbuf */
    pbuf_free(p);

    return err;
}


/**
 * @brief Initialize the UDP server.
 *
 * This function initializes the UDP server by creating a new UDP control block,
 * binding it to a specific IP address and port, and setting a receive callback.
 */
void udpServer_init(void) {
   /** UDP Control Block structure */
   upcb = udp_new();
   callback_flag = 0;
   err_t err = udp_bind(upcb, IP_ADDR_ANY, SERVER_PORT);  /** 50,007 is the server UDP port */

   /** Set a receive callback for the upcb */
   if (err == ERR_OK) {
	   udp_recv(upcb, udp_receive_callback, NULL);
   }
   else {
	   udp_remove(upcb);
   }
}
