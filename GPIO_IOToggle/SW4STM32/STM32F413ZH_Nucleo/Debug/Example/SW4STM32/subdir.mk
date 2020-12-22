################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
C:/Users/carte/Documents/GitHub/QSS/Firmware/GPIO_IOToggle/SW4STM32/startup_stm32f413xx.s 

OBJS += \
./Example/SW4STM32/startup_stm32f413xx.o 

S_DEPS += \
./Example/SW4STM32/startup_stm32f413xx.d 


# Each subdirectory must supply rules for building sources it contributes
Example/SW4STM32/startup_stm32f413xx.o: C:/Users/carte/Documents/GitHub/QSS/Firmware/GPIO_IOToggle/SW4STM32/startup_stm32f413xx.s
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -x assembler-with-cpp -MMD -MP -MF"Example/SW4STM32/startup_stm32f413xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

