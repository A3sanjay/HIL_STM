################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../nanopb/spm-test/objc/c-header.c 

OBJS += \
./nanopb/spm-test/objc/c-header.o 

C_DEPS += \
./nanopb/spm-test/objc/c-header.d 


# Each subdirectory must supply rules for building sources it contributes
nanopb/spm-test/objc/%.o nanopb/spm-test/objc/%.su nanopb/spm-test/objc/%.cyclo: ../nanopb/spm-test/objc/%.c nanopb/spm-test/objc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/arvin/STM32CubeIDE/workspace_1.12.1/HIL_STM/nanopb" -I"C:/Users/arvin/STM32CubeIDE/workspace_1.12.1/HIL_STM/proto" -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-nanopb-2f-spm-2d-test-2f-objc

clean-nanopb-2f-spm-2d-test-2f-objc:
	-$(RM) ./nanopb/spm-test/objc/c-header.cyclo ./nanopb/spm-test/objc/c-header.d ./nanopb/spm-test/objc/c-header.o ./nanopb/spm-test/objc/c-header.su

.PHONY: clean-nanopb-2f-spm-2d-test-2f-objc

