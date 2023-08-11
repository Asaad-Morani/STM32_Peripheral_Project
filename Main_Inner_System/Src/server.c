#include "main_Inner_System.h"

void udp_receive_callback(void* arg, struct udp_pcb* upcb, struct pbuf* p, const ip_addr_t* addr, u16_t port)
{
	// Check if we finished with the last packet
	if(callback_flag == 1 || p->len > MAX_BUF_LEN)
	{
		// Drop the packet
		pbuf_free(p);
		return;
	}
	// Store the sender information
	ip_addr_copy(dest_ipaddr, *addr);
	dest_port = port;
	memcpy(&incoming_message, p->payload, p->len);
	incomming_len = p->len;

	callback_flag = 1;
	// free the pbuf
	pbuf_free(p);
}

err_t send_packet(struct udp_pcb* pcb, const void* payload, u16_t payload_len, const ip_addr_t* ipaddr, u16_t port)
{
    err_t err;
    struct pbuf* p;

    // allocate a pbuf for the payload
    p = pbuf_alloc(PBUF_TRANSPORT, payload_len, PBUF_RAM);
    if (!p) {
        // failed to allocate pbuf
        return ERR_MEM;
    }

    // copy the payload into the pbuf
    memcpy(p->payload, payload, payload_len);

    // send the packet
    err = udp_sendto(pcb, p, ipaddr, port);

    // free the pbuf
    pbuf_free(p);

    return err;
}


void udpServer_init(void) {
	// UDP Control Block structure
   upcb = udp_new();
   callback_flag = 0;
   err_t err = udp_bind(upcb, IP_ADDR_ANY, SERVER_PORT);  // 50,007 is the server UDP port

   /* 3. Set a receive callback for the upcb */
   if (err == ERR_OK) {
	   udp_recv(upcb, udp_receive_callback, NULL);
   }
   else {
	   udp_remove(upcb);
   }
}
