################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../nanopb/tests/site_scons/platforms/avr/avr_io.c \
../nanopb/tests/site_scons/platforms/avr/run_test.c 

OBJS += \
./nanopb/tests/site_scons/platforms/avr/avr_io.o \
./nanopb/tests/site_scons/platforms/avr/run_test.o 

C_DEPS += \
./nanopb/tests/site_scons/platforms/avr/avr_io.d \
./nanopb/tests/site_scons/platforms/avr/run_test.d 


# Each subdirectory must supply rules for building sources it contributes
nanopb/tests/site_scons/platforms/avr/%.o nanopb/tests/site_scons/platforms/avr/%.su nanopb/tests/site_scons/platforms/avr/%.cyclo: ../nanopb/tests/site_scons/platforms/avr/%.c nanopb/tests/site_scons/platforms/avr/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/arvin/STM32CubeIDE/workspace_1.12.1/HIL_STM/nanopb" -I"C:/Users/arvin/STM32CubeIDE/workspace_1.12.1/HIL_STM/proto" -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-nanopb-2f-tests-2f-site_scons-2f-platforms-2f-avr

clean-nanopb-2f-tests-2f-site_scons-2f-platforms-2f-avr:
	-$(RM) ./nanopb/tests/site_scons/platforms/avr/avr_io.cyclo ./nanopb/tests/site_scons/platforms/avr/avr_io.d ./nanopb/tests/site_scons/platforms/avr/avr_io.o ./nanopb/tests/site_scons/platforms/avr/avr_io.su ./nanopb/tests/site_scons/platforms/avr/run_test.cyclo ./nanopb/tests/site_scons/platforms/avr/run_test.d ./nanopb/tests/site_scons/platforms/avr/run_test.o ./nanopb/tests/site_scons/platforms/avr/run_test.su

.PHONY: clean-nanopb-2f-tests-2f-site_scons-2f-platforms-2f-avr

