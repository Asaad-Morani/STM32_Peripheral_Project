#include "main_Inner_System.h"
#include "uart.h"
#include "i2c.h"
#include "spi.h"

/*
 *	transmit and receive
 *	packets using the LWIP. The following code will
 *	program the EVB to be an echo server.
 *
 *	EVB configuration:
 *	IP: 		192.168.7.2
 *	NETMASK: 	255.255.255.0 (or 192.168.7.0/24)
 *	GATEWAY: 	192.168.7.1 (not in use but required by IDE)
 *	Port:		50,007
 */
struct udp_pcb *upcb;
struct Message incoming_message;

uint8_t callback_flag = 0;
ip_addr_t dest_ipaddr = {0};
u16_t dest_port = 0;
u16_t incomming_len = 0;

void rtg_main() {
	printf("Server is listening ... \r\n");
	udpServer_init();					//UDP server initialization
	while (1) {
		ethernetif_input(&gnetif);		//Handles the actual reception of bytes from the network interface
		sys_check_timeouts();			//Handle which checks timeout expiration
		if(callback_flag == 1)
		{
            printf("number is : %d \r\n", incoming_message.number);
			switch (incoming_message.number) {
			    case 1:
			        printf("UART is under test \r\n");
			        uart_test(incoming_message.string);
			        break;
			    case 2:
			    	printf("I2C is under test \r\n");
			    	i2c_test(incoming_message.string);
			        break;
			    case 3:
			    	printf("SPI is under test \r\n");
			    	spi_test(incoming_message.string);
			        break;
			    default:
			    	printf("Error !! \r\n");
			}
			printf("END of test \r\n");
			printf("_____________________________________________\r\n");
			printf("Server is listening to another package... \r\n\n");
			callback_flag = 0;
		}
	}
}
