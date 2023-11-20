################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
<<<<<<< HEAD
../src/CE_SD_card_control.c \
../src/GLOBAL.c \
../src/MENU.c \
../src/diskio.c \
../src/fatfs_sd.c \
../src/ff.c \
../src/ffunicode.c \
../src/main_v1.c \
../src/stm32_ub_lcd_2x16.c \
../src/stm32f4xx_it.c \
../src/syscalls.c \
../src/system_stm32f4xx.c \
../src/teclado.c \
../src/tm_stm32f4_delay.c \
../src/tm_stm32f4_fatfs.c \
../src/tm_stm32f4_gpio.c \
../src/tm_stm32f4_mfrc522.c \
../src/tm_stm32f4_spi.c \
../src/tm_stm32f4_timer_properties.c 

OBJS += \
./src/CE_SD_card_control.o \
./src/GLOBAL.o \
./src/MENU.o \
./src/diskio.o \
./src/fatfs_sd.o \
./src/ff.o \
./src/ffunicode.o \
./src/main_v1.o \
./src/stm32_ub_lcd_2x16.o \
./src/stm32f4xx_it.o \
./src/syscalls.o \
./src/system_stm32f4xx.o \
./src/teclado.o \
./src/tm_stm32f4_delay.o \
./src/tm_stm32f4_fatfs.o \
./src/tm_stm32f4_gpio.o \
./src/tm_stm32f4_mfrc522.o \
./src/tm_stm32f4_spi.o \
./src/tm_stm32f4_timer_properties.o 

C_DEPS += \
./src/CE_SD_card_control.d \
./src/GLOBAL.d \
./src/MENU.d \
./src/diskio.d \
./src/fatfs_sd.d \
./src/ff.d \
./src/ffunicode.d \
./src/main_v1.d \
./src/stm32_ub_lcd_2x16.d \
./src/stm32f4xx_it.d \
./src/syscalls.d \
./src/system_stm32f4xx.d \
./src/teclado.d \
./src/tm_stm32f4_delay.d \
./src/tm_stm32f4_fatfs.d \
./src/tm_stm32f4_gpio.d \
./src/tm_stm32f4_mfrc522.d \
./src/tm_stm32f4_spi.d \
./src/tm_stm32f4_timer_properties.d 
=======
../src/main_RFID.c \
../src/syscalls.c \
../src/system_stm32f4xx.c \
../src/tm_stm32f4_gpio.c \
../src/tm_stm32f4_mfrc522.c \
../src/tm_stm32f4_spi.c 

OBJS += \
./src/main_RFID.o \
./src/syscalls.o \
./src/system_stm32f4xx.o \
./src/tm_stm32f4_gpio.o \
./src/tm_stm32f4_mfrc522.o \
./src/tm_stm32f4_spi.o 

C_DEPS += \
./src/main_RFID.d \
./src/syscalls.d \
./src/system_stm32f4xx.d \
./src/tm_stm32f4_gpio.d \
./src/tm_stm32f4_mfrc522.d \
./src/tm_stm32f4_spi.d 
>>>>>>> e5ce884e878d93d805d1f734fd25e2075f59e355


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
<<<<<<< HEAD
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F429ZITx -DNUCLEO_F429ZI -DDEBUG -DSTM32F429_439xx -DUSE_STDPERIPH_DRIVER -I"C:/Users/carri/workspace/Final_v1/StdPeriph_Driver/inc" -I"C:/Users/carri/workspace/Final_v1/inc" -I"C:/Users/carri/workspace/Final_v1/CMSIS/device" -I"C:/Users/carri/workspace/Final_v1/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
=======
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F429ZITx -DNUCLEO_F429ZI -DDEBUG -DSTM32F429_439xx -DUSE_STDPERIPH_DRIVER -I"C:/Users/carri/workspace/RFID-test/StdPeriph_Driver/inc" -I"C:/Users/carri/workspace/RFID-test/inc" -I"C:/Users/carri/workspace/RFID-test/CMSIS/device" -I"C:/Users/carri/workspace/RFID-test/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
>>>>>>> e5ce884e878d93d805d1f734fd25e2075f59e355
	@echo 'Finished building: $<'
	@echo ' '


