#ifndef INC_UART_H_
#define INC_UART_H_

// for UART using
extern UART_HandleTypeDef huart3;
#define DEBUG_UART &huart3
extern UART_HandleTypeDef huart5;
#define UART_5 &huart5
extern UART_HandleTypeDef huart7;
#define UART_7 &huart7

void uart_test(const char* buffer);


#endif /* INC_UART_H_ */
