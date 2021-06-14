#include "stm32f4xx_hal.h"
#include "errorHandling.h"
#include "UART.h"
#include "sensors.h"
#include "bmp280.h"


BMP280_HandleTypedef bmp280;

float pressure, temperature, humidity;

void sensorsInit()
{
	GPIO_InitTypeDef I2C_GPIO;
	I2C_GPIO.Pin = GPIO_PIN_8|GPIO_PIN_9;
	I2C_GPIO.Mode = GPIO_MODE_AF_OD;
	I2C_GPIO.Pull = GPIO_PULLUP;
	I2C_GPIO.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	I2C_GPIO.Alternate = GPIO_AF4_I2C1;
	HAL_GPIO_Init(GPIOB, &I2C_GPIO);

	__HAL_RCC_I2C1_CLK_ENABLE();

	I2C_HandleTypeDef hi2c1;

	hi2c1.Instance = I2C1;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	if (HAL_I2C_Init(&hi2c1) != HAL_OK)
	{
		errorMessage |= 0x00000003; //I2C init error
	}

	HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE);
	HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0);

	bmp280_init_default_params(&bmp280.params);
	bmp280.addr = BMP280_I2C_ADDRESS_0;
	bmp280.i2c = &hi2c1;
}


void TASK_SensorHandler(void)
{
	bmp280_read_float(&bmp280, &temperature, &pressure, &humidity);
}
