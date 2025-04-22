################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../proto/set_board_response.pb.c \
../proto/update_event_message.pb.c 

OBJS += \
./proto/set_board_response.pb.o \
./proto/update_event_message.pb.o 

C_DEPS += \
./proto/set_board_response.pb.d \
./proto/update_event_message.pb.d 


# Each subdirectory must supply rules for building sources it contributes
proto/%.o proto/%.su proto/%.cyclo: ../proto/%.c proto/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/arvin/STM32CubeIDE/workspace_1.12.1/HIL_STM/nanopb" -I"C:/Users/arvin/STM32CubeIDE/workspace_1.12.1/HIL_STM/proto" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-proto

clean-proto:
	-$(RM) ./proto/set_board_response.pb.cyclo ./proto/set_board_response.pb.d ./proto/set_board_response.pb.o ./proto/set_board_response.pb.su ./proto/update_event_message.pb.cyclo ./proto/update_event_message.pb.d ./proto/update_event_message.pb.o ./proto/update_event_message.pb.su

.PHONY: clean-proto

