#include "errorHandling.h"



void TASK_errorHandler(void)
{
	for(;;)
	{

	}
}

void TASK_nucleoRED(void)
{

	GPIO_InitTypeDef  RED_LED = {GPIO_PIN_14,
			 	 	 	 	 	GPIO_MODE_OUTPUT_PP,
								GPIO_PULLUP,
								GPIO_SPEED_FREQ_VERY_HIGH,
								0};

	HAL_GPIO_Init(GPIOB, &RED_LED);

	for(;;)
	{
		HAL_GPIO_TogglePin(GPIOB, U14);
}




void TASK_nucleoBLU(void)
{


	GPIO_InitTypeDef  BLU_LED = {GPIO_PIN_7,
			 	 	 	 	 	GPIO_MODE_OUTPUT_PP,
								GPIO_PULLUP,
								GPIO_SPEED_FREQ_VERY_HIGH,
								0};

	HAL_GPIO_Init(GPIOB, &BLU_LED);

	for(;;)
	{
		HAL_GPIO_WritePin((GPIO_TypeDef*) GPIOB, (uint16_t) 7, (GPIO_PinState) GPIO_PIN_SET);
		vTaskDelay(250);
		HAL_GPIO_WritePin((GPIO_TypeDef*) GPIOB, (uint16_t) 7, (GPIO_PinState) GPIO_PIN_RESET);
		vTaskDelay(250);
	}
}


