/**
 * @file i2c.c
 * @brief This file contains implementations for I2C testing functions.
 */

#include "main_Inner_System.h"
#include "i2c.h"

uint8_t flag_slave=0;

/**
 * @brief Perform I2C communication test.
 *
 * This function demonstrates I2C communication between a master and a slave.
 * It sends data from a first buffer to a middle buffer using DMA for reception
 * on the slave side. Then, it transmits data from the master to the slave.
 * Finally, it receives data from the slave to the master and transmits data
 * from the middle buffer to a last buffer on the slave side. The processed
 * data is sent back to a client.
 *
 * @param buffer The input data buffer.
 */
void i2c_test(const char* buffer)
{
	char buff_first[MAX_BUF_LEN] = {0};
	char buff_middle[MAX_BUF_LEN] = {0};
	char buff_last[MAX_BUF_LEN] = {0};
	HAL_StatusTypeDef status = 0;

	strncpy(buff_first, buffer, MAX_BUF_LEN - 1);  /** Copy buffer to str */

	/** Master to Salve - send data from first buffer to middle buffer */
	status = HAL_I2C_Slave_Receive_DMA(I2C_2, buff_middle, MAX_BUF_LEN);
	if(status != HAL_OK)
	{
		printf("We got the following error: %d\r\n", status);
		exit(1);
	}

	status = HAL_I2C_Master_Transmit(I2C_1, I2C_Slave, buff_first, MAX_BUF_LEN, SHORT_TIMEOUT);
	if(status != HAL_OK)
	{
		printf("We got the following error: %d\r\n", status);
		exit(1);
	}

	while(1)
	{
		if(flag_slave)
		{
			/** Slave to Master - send data from middle buffer to last buffer */
			status = HAL_I2C_Master_Receive_DMA(I2C_1, I2C_Slave, buff_last, MAX_BUF_LEN);
			if(status != HAL_OK)
			{
				printf("We got the following error: %d\r\n", status);
				exit(1);
			}

			status = HAL_I2C_Slave_Transmit(I2C_2, buff_middle, MAX_BUF_LEN, SHORT_TIMEOUT);
			if(status != HAL_OK)
			{
				printf("We got the following error: %d\r\n", status);
				exit(1);
			}

			flag_slave = 0;
			strcat(buff_last, " - (I2C Message Receive)");
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
 * @brief I2C Slave receive complete callback.
 *
 * This function is a callback that gets triggered when an I2C slave receive operation
 * is completed. It checks if the completed I2C handle is for the slave and sets
 * the @c flag_slave variable to indicate that data has been received.
 *
 * @param hi2c Pointer to the I2C handle that triggered the callback.
 */
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if(hi2c == I2C_2)
	{
		flag_slave = 1;
	}
}

