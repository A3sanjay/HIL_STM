################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../nanopb/tests/typename_mangling/test_flatten.c \
../nanopb/tests/typename_mangling/test_package_initials.c \
../nanopb/tests/typename_mangling/test_replace_package.c \
../nanopb/tests/typename_mangling/test_strip_package.c \
../nanopb/tests/typename_mangling/test_strip_package_dependencies.c 

OBJS += \
./nanopb/tests/typename_mangling/test_flatten.o \
./nanopb/tests/typename_mangling/test_package_initials.o \
./nanopb/tests/typename_mangling/test_replace_package.o \
./nanopb/tests/typename_mangling/test_strip_package.o \
./nanopb/tests/typename_mangling/test_strip_package_dependencies.o 

C_DEPS += \
./nanopb/tests/typename_mangling/test_flatten.d \
./nanopb/tests/typename_mangling/test_package_initials.d \
./nanopb/tests/typename_mangling/test_replace_package.d \
./nanopb/tests/typename_mangling/test_strip_package.d \
./nanopb/tests/typename_mangling/test_strip_package_dependencies.d 


# Each subdirectory must supply rules for building sources it contributes
nanopb/tests/typename_mangling/%.o nanopb/tests/typename_mangling/%.su nanopb/tests/typename_mangling/%.cyclo: ../nanopb/tests/typename_mangling/%.c nanopb/tests/typename_mangling/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/arvin/STM32CubeIDE/workspace_1.12.1/HIL_STM/nanopb" -I"C:/Users/arvin/STM32CubeIDE/workspace_1.12.1/HIL_STM/proto" -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-nanopb-2f-tests-2f-typename_mangling

clean-nanopb-2f-tests-2f-typename_mangling:
	-$(RM) ./nanopb/tests/typename_mangling/test_flatten.cyclo ./nanopb/tests/typename_mangling/test_flatten.d ./nanopb/tests/typename_mangling/test_flatten.o ./nanopb/tests/typename_mangling/test_flatten.su ./nanopb/tests/typename_mangling/test_package_initials.cyclo ./nanopb/tests/typename_mangling/test_package_initials.d ./nanopb/tests/typename_mangling/test_package_initials.o ./nanopb/tests/typename_mangling/test_package_initials.su ./nanopb/tests/typename_mangling/test_replace_package.cyclo ./nanopb/tests/typename_mangling/test_replace_package.d ./nanopb/tests/typename_mangling/test_replace_package.o ./nanopb/tests/typename_mangling/test_replace_package.su ./nanopb/tests/typename_mangling/test_strip_package.cyclo ./nanopb/tests/typename_mangling/test_strip_package.d ./nanopb/tests/typename_mangling/test_strip_package.o ./nanopb/tests/typename_mangling/test_strip_package.su ./nanopb/tests/typename_mangling/test_strip_package_dependencies.cyclo ./nanopb/tests/typename_mangling/test_strip_package_dependencies.d ./nanopb/tests/typename_mangling/test_strip_package_dependencies.o ./nanopb/tests/typename_mangling/test_strip_package_dependencies.su

.PHONY: clean-nanopb-2f-tests-2f-typename_mangling

