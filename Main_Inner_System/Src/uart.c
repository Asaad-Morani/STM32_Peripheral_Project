/**
 * @file uart.c
 * @brief This is a brief description of the UART file.
 *  receives a buffer input data from the user client.
 *	The microcontroller transmit this data from UART7 to UART5,
 *	then from UART5 to UART7, and finally back to the user via server.
 */

#include "main_Inner_System.h"
#include "main.h"
#include "uart.h"
#include <string.h>

volatile uint8_t flag_uart_7=0;
volatile uint8_t flag_uart_5=0;

/**
 * @brief Test UART communication with buffer handling.
 *
 * This function demonstrates UART communication between UART 7 and UART 5.
 * It receives data from UART 5 into a middle buffer, transmits data from
 * a first buffer to UART 7, and then transfers data from the middle buffer
 * to a last buffer. Finally, it sends the modified data back to a client.
 *
 * @param buffer The input data buffer.
 */
void uart_test(const char* buffer)
{
	char buff_first[MAX_BUF_LEN] = {0};
	char buff_middle[MAX_BUF_LEN] = {0};
	char buff_last[MAX_BUF_LEN] = {0};
	HAL_StatusTypeDef status = 0;

	strncpy(buff_first, buffer, MAX_BUF_LEN - 1); /**< Copy buffer to buff_first. */

	/**
	 * UART 7 -> UART 5
	 * Sending from first buffer to the middle buffer
	 */
	status = HAL_UART_Receive_DMA(UART_5, buff_middle, MAX_BUF_LEN);
	if(status != HAL_OK)
	{
		printf("We got the following error: %d\r\n", status);
		exit(1);
	}
	status = HAL_UART_Transmit(UART_7, buff_first, MAX_BUF_LEN, SHORT_TIMEOUT);
	if(status != HAL_OK)
	{
		printf("We got the following error: %d\r\n", status);
		exit(1);
	}

	while(1)
	{
		if(flag_uart_5)
		{
			/** Sending from middle buffer to the last buffer */
			status = HAL_UART_Receive_DMA(UART_7, buff_last, MAX_BUF_LEN);
			if(status != HAL_OK)
			{
				printf("We got the following error 3 : %d\r\n", status);
				exit(1);
			}
			status = HAL_UART_Transmit(UART_5, buff_middle, MAX_BUF_LEN, SHORT_TIMEOUT);
			if(status != HAL_OK)
			{
				printf("We got the following error: %d\r\n", status);
				exit(1);
			}

			flag_uart_5 = 0;
			strcat(buff_last, " - (UART Message Receive)");
			printf("buff_last result is : %s \r\n", buff_last);
			// Send back the packet to the client
			send_packet(upcb, buff_last, sizeof(buff_last), &dest_ipaddr, dest_port);
			// Clear the buffers
			memset(buff_first, 0, sizeof(buff_first));
			memset(buff_middle, 0, sizeof(buff_middle));
			memset(buff_last, 0, sizeof(buff_last));
			break;
		}
	}
}

/**
 * @brief UART receive complete callback.
 *
 * This function is a callback that gets triggered when a UART receive operation
 * is completed. It checks if the completed UART handle is for UART 5 and sets
 * the flag_uart_5 variable to indicate that data has been received.
 *
 * @param huart Pointer to the UART handle that triggered the callback.
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == UART_5)
	{
		flag_uart_5 = 1;
	}
}














