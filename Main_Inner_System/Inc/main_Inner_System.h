/**
 * @file main_inner_system.h
 * @brief Header file containing declarations for the main Inner System functionality.
 */

#ifndef INC_RTG_H_
#define INC_RTG_H_

#include "main.h"
#include "inet.h"
#include "lwip.h"
#include "stm32f7xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** @brief Define the UART debug port */
extern UART_HandleTypeDef huart3;
#define UART_DEBUG &huart3
#define SHORT_TIMEOUT 100 /**< Timeout for 0.1 seconds */

#define END_OF_STRING 0
#define BACKSPACE 8
#define LINE_FEED 10
#define CARRIAGE_RETURN 13

/** @brief Define the port number for the server */
#define SERVER_PORT 50007

/** @brief Define the lwIP network interface
 * 		   Generic data structure used for all lwIP network interfaces.
 */
extern struct netif gnetif;

/** @brief Define the maximum length of the incoming packet buffer */
#define MAX_BUF_LEN 100

#pragma pack(push, 1)
/** @struct Message
 *  @brief Structure representing a message with a number and string data.
 */
struct Message {
    int number; /**< Message number */
    char string[MAX_BUF_LEN]; /**< Message string */
};
#pragma pack(pop)

/** @brief User message */
extern struct Message incoming_message;

/** @brief Define global variables */
extern uint8_t callback_flag;        /** Flag used to signal when a packet has been received */
extern struct udp_pcb* upcb;         /** UDP protocol control block */
extern ip_addr_t dest_ipaddr;        /** Destination IP address */
extern u16_t dest_port;           	 /** Destination port number */
extern u16_t incomming_len;
struct udp_pcb;                      			// Forward declaration of the udp_pcb structure */

/** @brief Define function prototypes */
void main_inner_sys();                  /** Main function for the Inner System program */
void udpServer_init();                  /** Initialize the UDP server */
void udp_disconnect(struct udp_pcb*);   /** Disconnect the UDP server */
err_t udp_send(struct udp_pcb *, struct pbuf *);  // Send a UDP packet */
err_t udp_connect(struct udp_pcb *, const ip_addr_t *, u16_t);  /** Connect to a remote host */
struct udp_pcb *udp_new(void);           /** Allocate a new udp_pcb structure */
err_t udp_bind(struct udp_pcb *, const ip_addr_t *, u16_t);     /** Bind the UDP server to an IP address and port number */
void udp_recv(struct udp_pcb *, void *, void *);                /** Receive a UDP packet */
void udp_remove(struct udp_pcb *);err_t
udp_sendto(struct udp_pcb *, struct pbuf *, const ip_addr_t *, u16_t);  /** Send a UDP packet to a specific IP address and port number */
err_t send_packet(struct udp_pcb*, const void*, u16_t, const ip_addr_t*, u16_t);
void udp_receive_callback(void* arg, struct udp_pcb* upcb, struct pbuf* p, const ip_addr_t* addr, u16_t port);


#endif /* INC_RTG_H_ */
