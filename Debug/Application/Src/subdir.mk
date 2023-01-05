################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/Src/Bamocar.c \
../Application/Src/BasicUart.c \
../Application/Src/DIS_Comms.c \
../Application/Src/DIS_Draw.c \
../Application/Src/SystemInfo.c \
../Application/Src/adc_inputs.c \
../Application/Src/error.c \
../Application/Src/inputs.c \
../Application/Src/millis.c \
../Application/Src/outputs.c \
../Application/Src/pedale.c 

OBJS += \
./Application/Src/Bamocar.o \
./Application/Src/BasicUart.o \
./Application/Src/DIS_Comms.o \
./Application/Src/DIS_Draw.o \
./Application/Src/SystemInfo.o \
./Application/Src/adc_inputs.o \
./Application/Src/error.o \
./Application/Src/inputs.o \
./Application/Src/millis.o \
./Application/Src/outputs.o \
./Application/Src/pedale.o 

C_DEPS += \
./Application/Src/Bamocar.d \
./Application/Src/BasicUart.d \
./Application/Src/DIS_Comms.d \
./Application/Src/DIS_Draw.d \
./Application/Src/SystemInfo.d \
./Application/Src/adc_inputs.d \
./Application/Src/error.d \
./Application/Src/inputs.d \
./Application/Src/millis.d \
./Application/Src/outputs.d \
./Application/Src/pedale.d 


# Each subdirectory must supply rules for building sources it contributes
Application/Src/%.o Application/Src/%.su: ../Application/Src/%.c Application/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -DDEBUG '-DREVISION=$(or $(SAMPLE),$(SAMPLE),255)' -c -I../Application/Inc -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-Src

clean-Application-2f-Src:
	-$(RM) ./Application/Src/Bamocar.d ./Application/Src/Bamocar.o ./Application/Src/Bamocar.su ./Application/Src/BasicUart.d ./Application/Src/BasicUart.o ./Application/Src/BasicUart.su ./Application/Src/DIS_Comms.d ./Application/Src/DIS_Comms.o ./Application/Src/DIS_Comms.su ./Application/Src/DIS_Draw.d ./Application/Src/DIS_Draw.o ./Application/Src/DIS_Draw.su ./Application/Src/SystemInfo.d ./Application/Src/SystemInfo.o ./Application/Src/SystemInfo.su ./Application/Src/adc_inputs.d ./Application/Src/adc_inputs.o ./Application/Src/adc_inputs.su ./Application/Src/error.d ./Application/Src/error.o ./Application/Src/error.su ./Application/Src/inputs.d ./Application/Src/inputs.o ./Application/Src/inputs.su ./Application/Src/millis.d ./Application/Src/millis.o ./Application/Src/millis.su ./Application/Src/outputs.d ./Application/Src/outputs.o ./Application/Src/outputs.su ./Application/Src/pedale.d ./Application/Src/pedale.o ./Application/Src/pedale.su

.PHONY: clean-Application-2f-Src

