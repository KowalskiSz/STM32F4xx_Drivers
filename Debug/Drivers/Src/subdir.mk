################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Src/STM32F407_GPIO_Driver.c \
../Drivers/Src/STM32F407_SPI_Driver.c 

OBJS += \
./Drivers/Src/STM32F407_GPIO_Driver.o \
./Drivers/Src/STM32F407_SPI_Driver.o 

C_DEPS += \
./Drivers/Src/STM32F407_GPIO_Driver.d \
./Drivers/Src/STM32F407_SPI_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Src/%.o Drivers/Src/%.su Drivers/Src/%.cyclo: ../Drivers/Src/%.c Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"C:/Embedded-C/MPU1_workspace/STM232f4xx_DRIVERS/STM32F4xx_Drivers/Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Src

clean-Drivers-2f-Src:
	-$(RM) ./Drivers/Src/STM32F407_GPIO_Driver.cyclo ./Drivers/Src/STM32F407_GPIO_Driver.d ./Drivers/Src/STM32F407_GPIO_Driver.o ./Drivers/Src/STM32F407_GPIO_Driver.su ./Drivers/Src/STM32F407_SPI_Driver.cyclo ./Drivers/Src/STM32F407_SPI_Driver.d ./Drivers/Src/STM32F407_SPI_Driver.o ./Drivers/Src/STM32F407_SPI_Driver.su

.PHONY: clean-Drivers-2f-Src

