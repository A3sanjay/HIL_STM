################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../nanopb/pb_common.c \
../nanopb/pb_decode.c \
../nanopb/pb_encode.c 

OBJS += \
./nanopb/pb_common.o \
./nanopb/pb_decode.o \
./nanopb/pb_encode.o 

C_DEPS += \
./nanopb/pb_common.d \
./nanopb/pb_decode.d \
./nanopb/pb_encode.d 


# Each subdirectory must supply rules for building sources it contributes
nanopb/%.o nanopb/%.su nanopb/%.cyclo: ../nanopb/%.c nanopb/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/arvin/STM32CubeIDE/workspace_1.12.1/HIL_STM/nanopb" -I"C:/Users/arvin/STM32CubeIDE/workspace_1.12.1/HIL_STM/proto" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-nanopb

clean-nanopb:
	-$(RM) ./nanopb/pb_common.cyclo ./nanopb/pb_common.d ./nanopb/pb_common.o ./nanopb/pb_common.su ./nanopb/pb_decode.cyclo ./nanopb/pb_decode.d ./nanopb/pb_decode.o ./nanopb/pb_decode.su ./nanopb/pb_encode.cyclo ./nanopb/pb_encode.d ./nanopb/pb_encode.o ./nanopb/pb_encode.su

.PHONY: clean-nanopb

