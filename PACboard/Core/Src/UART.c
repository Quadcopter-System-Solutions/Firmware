#include "errorHandling.h"
#include "stm32f4xx_hal.h"
#include "UART.h"

UART_HandleTypeDef uart6;
DMA_HandleTypeDef dma_tx, dma_rx;

uint8_t txBuffer[TXBUFFERSIZE];
uint8_t rxBuffer[RXBUFFERSIZE];

void UART_Init(void)
{
//CLOCK
__HAL_RCC_GPIOC_CLK_ENABLE();
__HAL_RCC_USART6_CLK_ENABLE();
__DMA2_CLK_ENABLE();

//GPIO
GPIO_InitTypeDef UART_GPIO;

UART_GPIO.Pin = GPIO_PIN_6|GPIO_PIN_7;
UART_GPIO.Mode = GPIO_MODE_AF_PP;
UART_GPIO.Pull = GPIO_PULLUP;
UART_GPIO.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
UART_GPIO.Alternate = GPIO_AF8_USART6;
HAL_GPIO_Init(GPIOC, &UART_GPIO);

//DMA
dma_tx.Instance                 = DMA2_Stream7;
dma_tx.Init.Channel             = DMA_CHANNEL_5;
dma_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
dma_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
dma_tx.Init.MemInc              = DMA_MINC_ENABLE;
dma_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
dma_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
dma_tx.Init.Mode                = DMA_NORMAL;
dma_tx.Init.Priority            = DMA_PRIORITY_LOW;
dma_tx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
dma_tx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
dma_tx.Init.MemBurst            = DMA_MBURST_INC4;
dma_tx.Init.PeriphBurst         = DMA_PBURST_INC4;

HAL_DMA_Init(&dma_tx);


dma_rx.Instance                 = DMA2_Stream1;
dma_rx.Init.Channel             = DMA_CHANNEL_5;
dma_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
dma_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
dma_rx.Init.MemInc              = DMA_MINC_DISABLE;
dma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
dma_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
dma_rx.Init.Mode                = DMA_NORMAL;
dma_rx.Init.Priority            = DMA_PRIORITY_HIGH;
dma_rx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
dma_rx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
dma_rx.Init.MemBurst            = DMA_MBURST_INC4;
dma_rx.Init.PeriphBurst         = DMA_PBURST_INC4;

HAL_DMA_Init(&dma_rx);



//UART
uart6.Instance        = USART6;

uart6.Init.BaudRate   = 115200;
uart6.Init.WordLength = UART_WORDLENGTH_8B;
uart6.Init.StopBits   = UART_STOPBITS_1;
uart6.Init.Parity     = UART_PARITY_NONE;
uart6.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
uart6.Init.Mode       = UART_MODE_TX_RX;
if(HAL_UART_Init(&uart6) != HAL_OK)
{
  errorMessage = 0x0002; //UART failure
}


//Link DMA -> UART
__HAL_LINKDMA(&uart6, hdmatx, dma_tx);
__HAL_LINKDMA(&uart6, hdmarx, dma_rx);


HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 0, 1);
HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);

/* NVIC configuration for DMA transfer complete interrupt (USART6_RX) */
HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 0, 0);
HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);

/* NVIC for USART, to catch the TX complete */
HAL_NVIC_SetPriority(USART6_IRQn, 0, 1);
HAL_NVIC_EnableIRQ(USART6_IRQn);
}


void TASK_UARTHandler(void)
{
	HAL_UART_Receive_DMA(&uart6, rxBuffer, RXBUFFERSIZE);

	for(int i = 0; i < RXBUFFERSIZE; i++)
	{
		txBuffer[i]=rxBuffer[i];
	}

	if(HAL_UART_Transmit_DMA(&uart6, (uint8_t*)txBuffer, TXBUFFERSIZE) != HAL_OK)
	{
		errorMessage = 0x0003; //uart failure
	}
}



//Interrupt Handling
void DMA2_Stream1_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&dma_rx);
}
void DMA2_Stream7_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&dma_tx);
}
void USART6_IRQHandler(void)
{
  HAL_UART_IRQHandler(&uart6);
}
