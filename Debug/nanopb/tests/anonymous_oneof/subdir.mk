################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../nanopb/tests/anonymous_oneof/decode_oneof.c 

OBJS += \
./nanopb/tests/anonymous_oneof/decode_oneof.o 

C_DEPS += \
./nanopb/tests/anonymous_oneof/decode_oneof.d 


# Each subdirectory must supply rules for building sources it contributes
nanopb/tests/anonymous_oneof/%.o nanopb/tests/anonymous_oneof/%.su nanopb/tests/anonymous_oneof/%.cyclo: ../nanopb/tests/anonymous_oneof/%.c nanopb/tests/anonymous_oneof/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/arvin/STM32CubeIDE/workspace_1.12.1/HIL_STM/nanopb" -I"C:/Users/arvin/STM32CubeIDE/workspace_1.12.1/HIL_STM/proto" -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-nanopb-2f-tests-2f-anonymous_oneof

clean-nanopb-2f-tests-2f-anonymous_oneof:
	-$(RM) ./nanopb/tests/anonymous_oneof/decode_oneof.cyclo ./nanopb/tests/anonymous_oneof/decode_oneof.d ./nanopb/tests/anonymous_oneof/decode_oneof.o ./nanopb/tests/anonymous_oneof/decode_oneof.su

.PHONY: clean-nanopb-2f-tests-2f-anonymous_oneof

