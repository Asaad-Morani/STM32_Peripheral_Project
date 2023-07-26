#ifndef INC_I2C_H_
#define INC_I2C_H_

#include "main.h"
#include "stm32f7xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern UART_HandleTypeDef huart3;
extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;

// define master and slave
#define UART_DEBUG &huart3
#define I2C_1 &hi2c1
#define I2C_2 &hi2c2

#define I2C_Master 0   // master address
#define I2C_Slave 2	   // slave address

// test function
void i2c_test(const char* buffer);


#endif /* INC_I2C_H_ */
