
#include "FreeRTOS.h"
#include "rtos.h"
#include "task.h"
#include "errorHandling.h"
#include "stm32f4xx_hal.h"


static void PRIVATE_errorHandler(void);
static void PRIVATE_nucleoRED(void);
static void PRIVATE_nucleoBLU(void);

void PRIVATE_errorHandler()
{
	TASK_errorHandler();
}

void PRIVATE_nucleoRED()
{
	TASK_nucleoRED();
}

void PRIVATE_nucleoBLU()
{
	TASK_nucleoBLU();
}

void RTOS_init()
{

	BaseType_t ret;


	TaskHandle_t errorHandler_th;

	ret = xTaskCreate((TaskFunction_t)PRIVATE_errorHandler,
				(const char * const)"errorHandler",
				configMINIMAL_STACK_SIZE,
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
				configMINIMAL_STACK_SIZE,
				NULL,
				tskIDLE_PRIORITY + 1U,
				&nucleoRED_th);

		if(ret != pdPASS)
		{
			errorMessage |= 0x0001; //RTOS init error
		}



	TaskHandle_t nucleoBLUE_th;

	xTaskCreate((TaskFunction_t)PRIVATE_nucleoBLU,
				(const char * const)"nucleoBLUE",
				configMINIMAL_STACK_SIZE,
				NULL,
				tskIDLE_PRIORITY + 1U,
				&nucleoBLUE_th);

		if(ret != pdPASS)
		{
			errorMessage |= 0x00000001; //RTOS init error
		}


	vTaskStartScheduler();

}
