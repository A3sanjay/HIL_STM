################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../nanopb/tests/namingstyle_custom/test_custom_naming_style_c.c \
../nanopb/tests/namingstyle_custom/test_custom_naming_style_importer_c.c \
../nanopb/tests/namingstyle_custom/test_custom_naming_style_mangle_c.c \
../nanopb/tests/namingstyle_custom/test_custom_naming_style_package_c.c 

OBJS += \
./nanopb/tests/namingstyle_custom/test_custom_naming_style_c.o \
./nanopb/tests/namingstyle_custom/test_custom_naming_style_importer_c.o \
./nanopb/tests/namingstyle_custom/test_custom_naming_style_mangle_c.o \
./nanopb/tests/namingstyle_custom/test_custom_naming_style_package_c.o 

C_DEPS += \
./nanopb/tests/namingstyle_custom/test_custom_naming_style_c.d \
./nanopb/tests/namingstyle_custom/test_custom_naming_style_importer_c.d \
./nanopb/tests/namingstyle_custom/test_custom_naming_style_mangle_c.d \
./nanopb/tests/namingstyle_custom/test_custom_naming_style_package_c.d 


# Each subdirectory must supply rules for building sources it contributes
nanopb/tests/namingstyle_custom/%.o nanopb/tests/namingstyle_custom/%.su nanopb/tests/namingstyle_custom/%.cyclo: ../nanopb/tests/namingstyle_custom/%.c nanopb/tests/namingstyle_custom/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/arvin/STM32CubeIDE/workspace_1.12.1/HIL_STM/nanopb" -I"C:/Users/arvin/STM32CubeIDE/workspace_1.12.1/HIL_STM/proto" -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-nanopb-2f-tests-2f-namingstyle_custom

clean-nanopb-2f-tests-2f-namingstyle_custom:
	-$(RM) ./nanopb/tests/namingstyle_custom/test_custom_naming_style_c.cyclo ./nanopb/tests/namingstyle_custom/test_custom_naming_style_c.d ./nanopb/tests/namingstyle_custom/test_custom_naming_style_c.o ./nanopb/tests/namingstyle_custom/test_custom_naming_style_c.su ./nanopb/tests/namingstyle_custom/test_custom_naming_style_importer_c.cyclo ./nanopb/tests/namingstyle_custom/test_custom_naming_style_importer_c.d ./nanopb/tests/namingstyle_custom/test_custom_naming_style_importer_c.o ./nanopb/tests/namingstyle_custom/test_custom_naming_style_importer_c.su ./nanopb/tests/namingstyle_custom/test_custom_naming_style_mangle_c.cyclo ./nanopb/tests/namingstyle_custom/test_custom_naming_style_mangle_c.d ./nanopb/tests/namingstyle_custom/test_custom_naming_style_mangle_c.o ./nanopb/tests/namingstyle_custom/test_custom_naming_style_mangle_c.su ./nanopb/tests/namingstyle_custom/test_custom_naming_style_package_c.cyclo ./nanopb/tests/namingstyle_custom/test_custom_naming_style_package_c.d ./nanopb/tests/namingstyle_custom/test_custom_naming_style_package_c.o ./nanopb/tests/namingstyle_custom/test_custom_naming_style_package_c.su

.PHONY: clean-nanopb-2f-tests-2f-namingstyle_custom

