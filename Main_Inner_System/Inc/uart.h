/**
 * @file uart.h
 * @brief Header file containing declarations for UART functionality.
 */

#ifndef INC_UART_H_
#define INC_UART_H_

/** @brief External UART handles for different UART interfaces. */
extern UART_HandleTypeDef huart3; /**< UART handle for debugging */
#define DEBUG_UART &huart3 /**< Debugging UART handle */
extern UART_HandleTypeDef huart5; /**< UART handle for UART 5 interface */
#define UART_5 &huart5 /**< UART 5 handle */
extern UART_HandleTypeDef huart7; /**< UART handle for UART 7 interface */
#define UART_7 &huart7 /**< UART 7 handle */

/**
 * @brief Perform UART communication test.
 *
 * This function performs UART communication test using the provided buffer.
 * It demonstrates sending and receiving data through UART interfaces.
 *
 * @param buffer The input data buffer.
 */
void uart_test(const char* buffer);


#endif /* INC_UART_H_ */
