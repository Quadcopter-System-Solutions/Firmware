#ifndef __UART_H
 #define __UART_H

#define RXBUFFERSIZE 10
#define TXBUFFERSIZE 10

extern uint8_t txBuffer[TXBUFFERSIZE];
extern uint8_t rxBuffer[RXBUFFERSIZE];

void UART_Init(void);
void TASK_UARTHandler(void);

extern uint16_t errorMessage;

#endif
