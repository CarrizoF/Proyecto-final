################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main_BTH.c \
../src/syscalls.c \
../src/system_stm32f4xx.c 

OBJS += \
./src/main_BTH.o \
./src/syscalls.o \
./src/system_stm32f4xx.o 

C_DEPS += \
./src/main_BTH.d \
./src/syscalls.d \
./src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F429ZITx -DNUCLEO_F429ZI -DSTM32F429_439xx -DUSE_STDPERIPH_DRIVER -I"C:/Users/carri/workspace/BTH-test/StdPeriph_Driver/inc" -I"C:/Users/carri/workspace/BTH-test/inc" -I"C:/Users/carri/workspace/BTH-test/CMSIS/device" -I"C:/Users/carri/workspace/BTH-test/CMSIS/core" -O3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


