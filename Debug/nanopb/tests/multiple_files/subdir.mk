################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../nanopb/tests/multiple_files/test_multiple_files.c 

OBJS += \
./nanopb/tests/multiple_files/test_multiple_files.o 

C_DEPS += \
./nanopb/tests/multiple_files/test_multiple_files.d 


# Each subdirectory must supply rules for building sources it contributes
nanopb/tests/multiple_files/%.o nanopb/tests/multiple_files/%.su nanopb/tests/multiple_files/%.cyclo: ../nanopb/tests/multiple_files/%.c nanopb/tests/multiple_files/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/arvin/STM32CubeIDE/workspace_1.12.1/HIL_STM/nanopb" -I"C:/Users/arvin/STM32CubeIDE/workspace_1.12.1/HIL_STM/proto" -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-nanopb-2f-tests-2f-multiple_files

clean-nanopb-2f-tests-2f-multiple_files:
	-$(RM) ./nanopb/tests/multiple_files/test_multiple_files.cyclo ./nanopb/tests/multiple_files/test_multiple_files.d ./nanopb/tests/multiple_files/test_multiple_files.o ./nanopb/tests/multiple_files/test_multiple_files.su

.PHONY: clean-nanopb-2f-tests-2f-multiple_files

