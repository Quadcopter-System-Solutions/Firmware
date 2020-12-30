#ifndef __ERRORHANDLING_H
#define __ERRORHANDLING_H

#include "FreeRTOS.h"
#include "stm32f4xx_hal.h"
#include "task.h"


uint16_t errorMessage;

void TASK_errorHandler(void);
void TASK_nucleoRED(void);
void TASK_nucleoBLU(void);
void errorInit(void);


#endif
