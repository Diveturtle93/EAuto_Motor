################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/Src/Bamocar.c \
../Application/Src/BasicUart.c \
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
./Application/Src/SystemInfo.d \
./Application/Src/adc_inputs.d \
./Application/Src/error.d \
./Application/Src/inputs.d \
./Application/Src/millis.d \
./Application/Src/outputs.d \
./Application/Src/pedale.d 


# Each subdirectory must supply rules for building sources it contributes
Application/Src/%.o: ../Application/Src/%.c Application/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F767xx '-DREVISION=$(or $(SAMPLE),$(SAMPLE),255)' -c -I../Application/Inc -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

