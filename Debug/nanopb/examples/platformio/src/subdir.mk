################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../nanopb/examples/platformio/src/pio_esp32_idf.c \
../nanopb/examples/platformio/src/pio_with_options.c \
../nanopb/examples/platformio/src/pio_without_options.c 

OBJS += \
./nanopb/examples/platformio/src/pio_esp32_idf.o \
./nanopb/examples/platformio/src/pio_with_options.o \
./nanopb/examples/platformio/src/pio_without_options.o 

C_DEPS += \
./nanopb/examples/platformio/src/pio_esp32_idf.d \
./nanopb/examples/platformio/src/pio_with_options.d \
./nanopb/examples/platformio/src/pio_without_options.d 


# Each subdirectory must supply rules for building sources it contributes
nanopb/examples/platformio/src/%.o nanopb/examples/platformio/src/%.su nanopb/examples/platformio/src/%.cyclo: ../nanopb/examples/platformio/src/%.c nanopb/examples/platformio/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/arvin/STM32CubeIDE/workspace_1.12.1/HIL_STM/nanopb" -I"C:/Users/arvin/STM32CubeIDE/workspace_1.12.1/HIL_STM/proto" -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-nanopb-2f-examples-2f-platformio-2f-src

clean-nanopb-2f-examples-2f-platformio-2f-src:
	-$(RM) ./nanopb/examples/platformio/src/pio_esp32_idf.cyclo ./nanopb/examples/platformio/src/pio_esp32_idf.d ./nanopb/examples/platformio/src/pio_esp32_idf.o ./nanopb/examples/platformio/src/pio_esp32_idf.su ./nanopb/examples/platformio/src/pio_with_options.cyclo ./nanopb/examples/platformio/src/pio_with_options.d ./nanopb/examples/platformio/src/pio_with_options.o ./nanopb/examples/platformio/src/pio_with_options.su ./nanopb/examples/platformio/src/pio_without_options.cyclo ./nanopb/examples/platformio/src/pio_without_options.d ./nanopb/examples/platformio/src/pio_without_options.o ./nanopb/examples/platformio/src/pio_without_options.su

.PHONY: clean-nanopb-2f-examples-2f-platformio-2f-src

