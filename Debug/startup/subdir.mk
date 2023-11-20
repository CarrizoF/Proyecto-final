################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32.s 

OBJS += \
./startup/startup_stm32.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
<<<<<<< HEAD
	arm-none-eabi-as -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I"C:/Users/carri/workspace/Final_v1/StdPeriph_Driver/inc" -I"C:/Users/carri/workspace/Final_v1/inc" -I"C:/Users/carri/workspace/Final_v1/CMSIS/device" -I"C:/Users/carri/workspace/Final_v1/CMSIS/core" -g -o "$@" "$<"
=======
	arm-none-eabi-as -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I"C:/Users/carri/workspace/RFID-test/StdPeriph_Driver/inc" -I"C:/Users/carri/workspace/RFID-test/inc" -I"C:/Users/carri/workspace/RFID-test/CMSIS/device" -I"C:/Users/carri/workspace/RFID-test/CMSIS/core" -g -o "$@" "$<"
>>>>>>> e5ce884e878d93d805d1f734fd25e2075f59e355
	@echo 'Finished building: $<'
	@echo ' '


