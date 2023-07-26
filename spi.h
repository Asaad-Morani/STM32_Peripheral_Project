#ifndef INC_SPI_H_
#define INC_SPI_H_

#include "main.h"
#include "stm32f7xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern SPI_HandleTypeDef hspi3;
extern SPI_HandleTypeDef hspi4;

// define master and slave
#define SPI_MASTER &hspi3
#define SPI_SLAVE &hspi4

void spi_test(const char* buffer);

#endif /* INC_SPI_H_ */
