#ifndef __UART_H
 #define __UART_H

#define RXBUFFERSIZE 32
#define TXBUFFERSIZE 32

uint8_t txBuffer[TXBUFFERSIZE];
uint8_t rxBuffer[RXBUFFERSIZE];

void UART_Init(void);
void TASK_UARTHandler(void);

extern uint16_t errorMessage;

#endif
