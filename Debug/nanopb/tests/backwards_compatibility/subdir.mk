################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../nanopb/tests/backwards_compatibility/alltypes_legacy.c \
../nanopb/tests/backwards_compatibility/decode_legacy.c \
../nanopb/tests/backwards_compatibility/encode_legacy.c 

OBJS += \
./nanopb/tests/backwards_compatibility/alltypes_legacy.o \
./nanopb/tests/backwards_compatibility/decode_legacy.o \
./nanopb/tests/backwards_compatibility/encode_legacy.o 

C_DEPS += \
./nanopb/tests/backwards_compatibility/alltypes_legacy.d \
./nanopb/tests/backwards_compatibility/decode_legacy.d \
./nanopb/tests/backwards_compatibility/encode_legacy.d 


# Each subdirectory must supply rules for building sources it contributes
nanopb/tests/backwards_compatibility/%.o nanopb/tests/backwards_compatibility/%.su nanopb/tests/backwards_compatibility/%.cyclo: ../nanopb/tests/backwards_compatibility/%.c nanopb/tests/backwards_compatibility/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/arvin/STM32CubeIDE/workspace_1.12.1/HIL_STM/nanopb" -I"C:/Users/arvin/STM32CubeIDE/workspace_1.12.1/HIL_STM/proto" -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-nanopb-2f-tests-2f-backwards_compatibility

clean-nanopb-2f-tests-2f-backwards_compatibility:
	-$(RM) ./nanopb/tests/backwards_compatibility/alltypes_legacy.cyclo ./nanopb/tests/backwards_compatibility/alltypes_legacy.d ./nanopb/tests/backwards_compatibility/alltypes_legacy.o ./nanopb/tests/backwards_compatibility/alltypes_legacy.su ./nanopb/tests/backwards_compatibility/decode_legacy.cyclo ./nanopb/tests/backwards_compatibility/decode_legacy.d ./nanopb/tests/backwards_compatibility/decode_legacy.o ./nanopb/tests/backwards_compatibility/decode_legacy.su ./nanopb/tests/backwards_compatibility/encode_legacy.cyclo ./nanopb/tests/backwards_compatibility/encode_legacy.d ./nanopb/tests/backwards_compatibility/encode_legacy.o ./nanopb/tests/backwards_compatibility/encode_legacy.su

.PHONY: clean-nanopb-2f-tests-2f-backwards_compatibility

