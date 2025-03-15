################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../nanopb/tests/fuzztest/flakystream.c \
../nanopb/tests/fuzztest/fuzztest.c \
../nanopb/tests/fuzztest/generate_message.c \
../nanopb/tests/fuzztest/random_data.c \
../nanopb/tests/fuzztest/validation.c 

OBJS += \
./nanopb/tests/fuzztest/flakystream.o \
./nanopb/tests/fuzztest/fuzztest.o \
./nanopb/tests/fuzztest/generate_message.o \
./nanopb/tests/fuzztest/random_data.o \
./nanopb/tests/fuzztest/validation.o 

C_DEPS += \
./nanopb/tests/fuzztest/flakystream.d \
./nanopb/tests/fuzztest/fuzztest.d \
./nanopb/tests/fuzztest/generate_message.d \
./nanopb/tests/fuzztest/random_data.d \
./nanopb/tests/fuzztest/validation.d 


# Each subdirectory must supply rules for building sources it contributes
nanopb/tests/fuzztest/%.o nanopb/tests/fuzztest/%.su nanopb/tests/fuzztest/%.cyclo: ../nanopb/tests/fuzztest/%.c nanopb/tests/fuzztest/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/arvin/STM32CubeIDE/workspace_1.12.1/HIL_STM/nanopb" -I"C:/Users/arvin/STM32CubeIDE/workspace_1.12.1/HIL_STM/proto" -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-nanopb-2f-tests-2f-fuzztest

clean-nanopb-2f-tests-2f-fuzztest:
	-$(RM) ./nanopb/tests/fuzztest/flakystream.cyclo ./nanopb/tests/fuzztest/flakystream.d ./nanopb/tests/fuzztest/flakystream.o ./nanopb/tests/fuzztest/flakystream.su ./nanopb/tests/fuzztest/fuzztest.cyclo ./nanopb/tests/fuzztest/fuzztest.d ./nanopb/tests/fuzztest/fuzztest.o ./nanopb/tests/fuzztest/fuzztest.su ./nanopb/tests/fuzztest/generate_message.cyclo ./nanopb/tests/fuzztest/generate_message.d ./nanopb/tests/fuzztest/generate_message.o ./nanopb/tests/fuzztest/generate_message.su ./nanopb/tests/fuzztest/random_data.cyclo ./nanopb/tests/fuzztest/random_data.d ./nanopb/tests/fuzztest/random_data.o ./nanopb/tests/fuzztest/random_data.su ./nanopb/tests/fuzztest/validation.cyclo ./nanopb/tests/fuzztest/validation.d ./nanopb/tests/fuzztest/validation.o ./nanopb/tests/fuzztest/validation.su

.PHONY: clean-nanopb-2f-tests-2f-fuzztest

