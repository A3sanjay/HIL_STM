################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/crc15.c \
../Core/Src/freertos.c \
../Core/Src/i2c_slave.c \
../Core/Src/i2c_spi_periphs_control.c \
../Core/Src/ltc6811.c \
../Core/Src/main.c \
../Core/Src/max17261.c \
../Core/Src/mcp2515.c \
../Core/Src/mcp4811.c \
../Core/Src/pca9555.c \
../Core/Src/proto_handling.c \
../Core/Src/proto_handling_task.c \
../Core/Src/proto_processing.c \
../Core/Src/spi_master.c \
../Core/Src/spi_slave.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_hal_timebase_tim.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/uart.c \
../Core/Src/uart_control.c 

OBJS += \
./Core/Src/crc15.o \
./Core/Src/freertos.o \
./Core/Src/i2c_slave.o \
./Core/Src/i2c_spi_periphs_control.o \
./Core/Src/ltc6811.o \
./Core/Src/main.o \
./Core/Src/max17261.o \
./Core/Src/mcp2515.o \
./Core/Src/mcp4811.o \
./Core/Src/pca9555.o \
./Core/Src/proto_handling.o \
./Core/Src/proto_handling_task.o \
./Core/Src/proto_processing.o \
./Core/Src/spi_master.o \
./Core/Src/spi_slave.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_hal_timebase_tim.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/uart.o \
./Core/Src/uart_control.o 

C_DEPS += \
./Core/Src/crc15.d \
./Core/Src/freertos.d \
./Core/Src/i2c_slave.d \
./Core/Src/i2c_spi_periphs_control.d \
./Core/Src/ltc6811.d \
./Core/Src/main.d \
./Core/Src/max17261.d \
./Core/Src/mcp2515.d \
./Core/Src/mcp4811.d \
./Core/Src/pca9555.d \
./Core/Src/proto_handling.d \
./Core/Src/proto_handling_task.d \
./Core/Src/proto_processing.d \
./Core/Src/spi_master.d \
./Core/Src/spi_slave.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_hal_timebase_tim.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/uart.d \
./Core/Src/uart_control.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/arvin/STM32CubeIDE/workspace_1.12.1/HIL_STM/nanopb" -I"C:/Users/arvin/STM32CubeIDE/workspace_1.12.1/HIL_STM/proto" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/crc15.cyclo ./Core/Src/crc15.d ./Core/Src/crc15.o ./Core/Src/crc15.su ./Core/Src/freertos.cyclo ./Core/Src/freertos.d ./Core/Src/freertos.o ./Core/Src/freertos.su ./Core/Src/i2c_slave.cyclo ./Core/Src/i2c_slave.d ./Core/Src/i2c_slave.o ./Core/Src/i2c_slave.su ./Core/Src/i2c_spi_periphs_control.cyclo ./Core/Src/i2c_spi_periphs_control.d ./Core/Src/i2c_spi_periphs_control.o ./Core/Src/i2c_spi_periphs_control.su ./Core/Src/ltc6811.cyclo ./Core/Src/ltc6811.d ./Core/Src/ltc6811.o ./Core/Src/ltc6811.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/max17261.cyclo ./Core/Src/max17261.d ./Core/Src/max17261.o ./Core/Src/max17261.su ./Core/Src/mcp2515.cyclo ./Core/Src/mcp2515.d ./Core/Src/mcp2515.o ./Core/Src/mcp2515.su ./Core/Src/mcp4811.cyclo ./Core/Src/mcp4811.d ./Core/Src/mcp4811.o ./Core/Src/mcp4811.su ./Core/Src/pca9555.cyclo ./Core/Src/pca9555.d ./Core/Src/pca9555.o ./Core/Src/pca9555.su ./Core/Src/proto_handling.cyclo ./Core/Src/proto_handling.d ./Core/Src/proto_handling.o ./Core/Src/proto_handling.su ./Core/Src/proto_handling_task.cyclo ./Core/Src/proto_handling_task.d ./Core/Src/proto_handling_task.o ./Core/Src/proto_handling_task.su ./Core/Src/proto_processing.cyclo ./Core/Src/proto_processing.d ./Core/Src/proto_processing.o ./Core/Src/proto_processing.su ./Core/Src/spi_master.cyclo ./Core/Src/spi_master.d ./Core/Src/spi_master.o ./Core/Src/spi_master.su ./Core/Src/spi_slave.cyclo ./Core/Src/spi_slave.d ./Core/Src/spi_slave.o ./Core/Src/spi_slave.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_hal_timebase_tim.cyclo ./Core/Src/stm32f4xx_hal_timebase_tim.d ./Core/Src/stm32f4xx_hal_timebase_tim.o ./Core/Src/stm32f4xx_hal_timebase_tim.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/uart.cyclo ./Core/Src/uart.d ./Core/Src/uart.o ./Core/Src/uart.su ./Core/Src/uart_control.cyclo ./Core/Src/uart_control.d ./Core/Src/uart_control.o ./Core/Src/uart_control.su

.PHONY: clean-Core-2f-Src

