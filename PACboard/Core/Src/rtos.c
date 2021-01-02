
#include "FreeRTOS.h"
#include "rtos.h"
#include "UART.h"
#include "task.h"
#include "errorHandling.h"
#include "stm32f4xx_hal.h"


static void PRIVATE_errorHandler(void);
static void PRIVATE_nucleoRED(void);
static void PRIVATE_nucleoBLU(void);
static void PRIVATE_UARTHandler(void);

static void PRIVATE_errorHandler()
{
	while(1)
	{
		TASK_errorHandler();
		vTaskDelay(500);
	}
}

static void PRIVATE_nucleoRED()
{
	while(1)
	{
		TASK_nucleoRED();
		vTaskDelay(500);
	}
}

static void PRIVATE_nucleoBLU()
{
	while(1)
	{
		TASK_nucleoBLU();
		vTaskDelay(250);
	}
}

static void PRIVATE_UARTHandler()
{
	while(1)
	{
		TASK_UARTHandler();
		vTaskDelay(1000);
	}
}




void RTOS_init()
{

	BaseType_t ret;


	TaskHandle_t errorHandler_th;

	ret = xTaskCreate((TaskFunction_t)PRIVATE_errorHandler,
				(const char * const)"errorHandler",
				configMINIMAL_STACK_SIZE*2,
				NULL,
				tskIDLE_PRIORITY + 1U,
				&errorHandler_th);

		if(ret != pdPASS)
		{
			errorMessage |= 0x0001; //RTOS init error
		}



	TaskHandle_t nucleoRED_th;

	ret = xTaskCreate((TaskFunction_t)PRIVATE_nucleoRED,
				(const char * const)"nucleoRED",
				configMINIMAL_STACK_SIZE*2,
				NULL,
				tskIDLE_PRIORITY + 3U,
				&nucleoRED_th);

		if(ret != pdPASS)
		{
			errorMessage |= 0x0001; //RTOS init error
		}



	TaskHandle_t nucleoBLUE_th;

	xTaskCreate((TaskFunction_t)PRIVATE_nucleoBLU,
				(const char * const)"nucleoBLUE",
				configMINIMAL_STACK_SIZE*2,
				NULL,
				tskIDLE_PRIORITY + 3U,
				&nucleoBLUE_th);

		if(ret != pdPASS)
		{
			errorMessage |= 0x00000001; //RTOS init error
		}



	TaskHandle_t UARTHandler_th;

	ret = xTaskCreate((TaskFunction_t)PRIVATE_UARTHandler,
				(const char * const)"UARTHandler",
				configMINIMAL_STACK_SIZE*2,
				NULL,
				tskIDLE_PRIORITY + 5U,
				&UARTHandler_th);

		if(ret != pdPASS)
		{
			errorMessage |= 0x0001; //RTOS init error
		}

	vTaskStartScheduler();

	for(;;);

}
