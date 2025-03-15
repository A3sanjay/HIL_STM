################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../nanopb/examples/network_server/client.c \
../nanopb/examples/network_server/common.c \
../nanopb/examples/network_server/server.c 

OBJS += \
./nanopb/examples/network_server/client.o \
./nanopb/examples/network_server/common.o \
./nanopb/examples/network_server/server.o 

C_DEPS += \
./nanopb/examples/network_server/client.d \
./nanopb/examples/network_server/common.d \
./nanopb/examples/network_server/server.d 


# Each subdirectory must supply rules for building sources it contributes
nanopb/examples/network_server/%.o nanopb/examples/network_server/%.su nanopb/examples/network_server/%.cyclo: ../nanopb/examples/network_server/%.c nanopb/examples/network_server/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/arvin/STM32CubeIDE/workspace_1.12.1/HIL_STM/nanopb" -I"C:/Users/arvin/STM32CubeIDE/workspace_1.12.1/HIL_STM/proto" -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-nanopb-2f-examples-2f-network_server

clean-nanopb-2f-examples-2f-network_server:
	-$(RM) ./nanopb/examples/network_server/client.cyclo ./nanopb/examples/network_server/client.d ./nanopb/examples/network_server/client.o ./nanopb/examples/network_server/client.su ./nanopb/examples/network_server/common.cyclo ./nanopb/examples/network_server/common.d ./nanopb/examples/network_server/common.o ./nanopb/examples/network_server/common.su ./nanopb/examples/network_server/server.cyclo ./nanopb/examples/network_server/server.d ./nanopb/examples/network_server/server.o ./nanopb/examples/network_server/server.su

.PHONY: clean-nanopb-2f-examples-2f-network_server

