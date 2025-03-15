################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../nanopb/build-tests/legacy_cmake_simple/simple.c 

OBJS += \
./nanopb/build-tests/legacy_cmake_simple/simple.o 

C_DEPS += \
./nanopb/build-tests/legacy_cmake_simple/simple.d 


# Each subdirectory must supply rules for building sources it contributes
nanopb/build-tests/legacy_cmake_simple/%.o nanopb/build-tests/legacy_cmake_simple/%.su nanopb/build-tests/legacy_cmake_simple/%.cyclo: ../nanopb/build-tests/legacy_cmake_simple/%.c nanopb/build-tests/legacy_cmake_simple/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/arvin/STM32CubeIDE/workspace_1.12.1/HIL_STM/nanopb" -I"C:/Users/arvin/STM32CubeIDE/workspace_1.12.1/HIL_STM/proto" -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-nanopb-2f-build-2d-tests-2f-legacy_cmake_simple

clean-nanopb-2f-build-2d-tests-2f-legacy_cmake_simple:
	-$(RM) ./nanopb/build-tests/legacy_cmake_simple/simple.cyclo ./nanopb/build-tests/legacy_cmake_simple/simple.d ./nanopb/build-tests/legacy_cmake_simple/simple.o ./nanopb/build-tests/legacy_cmake_simple/simple.su

.PHONY: clean-nanopb-2f-build-2d-tests-2f-legacy_cmake_simple

