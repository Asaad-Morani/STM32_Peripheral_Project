# STM32_Peripheral_Project
STM32F756ZG is a server that receives a struct from the client PC using an ethernet cable that transfers data between server and client (LWIP protocol).
The struct contains a test-ID integer the number of peripherals to test, and a string that send to the server. it's like an echo server that checks data transmission validation between UARTs, I2C, and SPI, using DMA.