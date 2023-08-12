/**
 * @file spi.h
 * @brief Header file containing declarations for SPI functionality.
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

#include "main.h"
#include "stm32f7xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** @brief External SPI handles for master and slave communication. */
extern SPI_HandleTypeDef hspi3;  /**< SPI handle for master communication */
extern SPI_HandleTypeDef hspi4;  /**< SPI handle for slave communication */

/** @brief Define for SPI master and slave interfaces. */
#define SPI_MASTER &hspi3 /**< SPI master interface */
#define SPI_SLAVE &hspi4  /**< SPI slave interface */

/**
 * @brief Perform SPI communication test.
 *
 * This function demonstrates SPI communication between a master and a slave.
 * It sends data from a first buffer to a middle buffer using DMA for reception
 * on the slave side. Then, it transmits data from the master to the slave.
 * Finally, it receives data from the slave to the master and transmits data
 * from the middle buffer to a last buffer on the slave side. The processed
 * data is sent back to a client.
 *
 * @param buffer The input data buffer.
 */
void spi_test(const char* buffer);

#endif /* INC_SPI_H_ */
