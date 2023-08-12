/**
 * @file i2c.h
 * @brief Header file containing declarations for I2C functionality.
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#include "main.h"
#include "stm32f7xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief External UART handle for debugging.
 */
extern UART_HandleTypeDef huart3;

/**
 * @brief External I2C handles for communication.
 */
extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;

/**
 * @brief Define for UART debugging interface.
 */
#define UART_DEBUG &huart3

/**
 * @brief Define for I2C master and slave interfaces.
 */
#define I2C_1 &hi2c1
#define I2C_2 &hi2c2

/**
 * @brief Address of the I2C master.
 */
#define I2C_Master 0

/**
 * @brief Address of the I2C slave.
 */
#define I2C_Slave 2

/**
 * @brief Test function for I2C communication.
 *
 * This function is used to perform I2C communication tests using the provided buffer.
 *
 * @param buffer The input data buffer.
 */
void i2c_test(const char* buffer);


#endif /* INC_I2C_H_ */
