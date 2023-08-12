/**
 * @file spi.c
 * @brief This file contains implementations for SPI testing functions.
 */

#include "main_Inner_System.h"
#include "spi.h"

uint8_t flag_slave_spi=0;
char buff_first[MAX_BUF_LEN] = {0};
char buff_middle[MAX_BUF_LEN] = {0};
char buff_last[MAX_BUF_LEN] = {0};
HAL_StatusTypeDef status = 0;

/**
 * @brief Test SPI communication with buffer handling.
 *
 * This function demonstrates SPI communication between a master and a slave.
 * It sends data from a first buffer to a middle buffer using DMA for reception
 * on the slave side. Then, it transmits data from the master to the slave.
 * Finally, it transmits data from the middle buffer to a last buffer on the
 * slave side, and receives data from the slave to the master. The processed
 * data is sent back to a client.
 *
 * @param buffer The input data buffer.
 */
void spi_test(const char* buffer) {

	strncpy(buff_first, buffer, MAX_BUF_LEN - 1);  // Copy buffer to str

	/** Master to Salve - send data from first buffer to middle buffer */
	status = HAL_SPI_Receive_DMA(SPI_SLAVE, buff_middle, MAX_BUF_LEN);
	if(status != HAL_OK)
	{
		printf("We got the following error buff_middle SPI_SLAVE : %d\r\n", status);
		exit(1);
	}

	status = HAL_SPI_Transmit(SPI_MASTER, buff_first, MAX_BUF_LEN, SHORT_TIMEOUT);
	if(status != HAL_OK)
	{
		printf("We got the following error HAL_SPI_Transmit SPI_MASTER : %d\r\n", status);
		exit(1);
	}

	while (1)
	{
		if(flag_slave_spi)
		{
			/** Slave to Master - send data from middle buffer to last buffer */
			status = HAL_SPI_Transmit_IT(SPI_SLAVE, buff_middle, MAX_BUF_LEN);
			if(status != HAL_OK)
			{
				printf("middle buff is : %s \r\n", buff_middle);
				printf("We got the following error HAL_SPI_Transmit SPI_SLAVE : %d\r\n", status);
				exit(1);
			}

			status = HAL_SPI_Receive(SPI_MASTER, buff_last, MAX_BUF_LEN, SHORT_TIMEOUT);
			if(status != HAL_OK)
			{
				printf("We got the following error HAL_SPI_Receive_IT SPI_MASTER : %d\r\n", status);
				exit(1);
			}

			flag_slave_spi = 0;
			strcat(buff_last, " - (SPI Message Receive)");
			printf("buff is : %s \r\n", buff_last);
			/** Send back the packet to the client */
			send_packet(upcb, buff_last, sizeof(buff_last), &dest_ipaddr, dest_port);
			/** Clear the buffers */
			memset(buff_first, 0, sizeof(buff_first));
			memset(buff_middle, 0, sizeof(buff_middle));
			memset(buff_last, 0, sizeof(buff_last));
			break;
		}
	}
}

/**
 * @brief SPI receive complete callback.
 *
 * This function is a callback that gets triggered when an SPI receive operation
 * is completed. It checks if the completed SPI handle is for the slave and sets
 * the @c flag_slave_spi variable to indicate that data has been received.
 *
 * @param hspi Pointer to the SPI handle that triggered the callback.
 */
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi) {
	if (hspi == SPI_SLAVE) {
		flag_slave_spi = 1;
	}
}
