################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/Inc/CAN_Bus.c 

OBJS += \
./Application/Inc/CAN_Bus.o 

C_DEPS += \
./Application/Inc/CAN_Bus.d 


# Each subdirectory must supply rules for building sources it contributes
Application/Inc/%.o Application/Inc/%.su Application/Inc/%.cyclo: ../Application/Inc/%.c Application/Inc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -DDEBUG '-DREVISION=$(or $(SAMPLE),$(SAMPLE),255)' -c -I../Application/Inc -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-Inc

clean-Application-2f-Inc:
	-$(RM) ./Application/Inc/CAN_Bus.cyclo ./Application/Inc/CAN_Bus.d ./Application/Inc/CAN_Bus.o ./Application/Inc/CAN_Bus.su

.PHONY: clean-Application-2f-Inc

