#include "errorHandling.h"

static GPIO_InitTypeDef  GPIO_InitStructRED;
static GPIO_InitTypeDef  GPIO_InitStructBLU;

void TASK_errorHandler(void)
{

}

void TASK_nucleoRED(void)
{
		GPIOB->ODR ^= GPIO_PIN_14;
}




void TASK_nucleoBLU(void)
{
		GPIOB->ODR ^= GPIO_PIN_7;
}


void errorInit(void)
{
	GPIO_InitStructRED.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructRED.Pull  = GPIO_PULLUP;
	GPIO_InitStructRED.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStructRED.Pin = GPIO_PIN_7;

	HAL_GPIO_Init(GPIOB, &GPIO_InitStructRED);

	GPIO_InitStructBLU.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructBLU.Pull  = GPIO_PULLUP;
	GPIO_InitStructBLU.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStructBLU.Pin = GPIO_PIN_14;

	HAL_GPIO_Init(GPIOB, &GPIO_InitStructBLU);
}


