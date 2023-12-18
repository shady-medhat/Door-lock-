################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Buzzer.c \
../Control_APP.c \
../DC.c \
../PWM.c \
../Timer1.c \
../UART.c \
../external_eeprom.c \
../gpio.c \
../twi.c 

OBJS += \
./Buzzer.o \
./Control_APP.o \
./DC.o \
./PWM.o \
./Timer1.o \
./UART.o \
./external_eeprom.o \
./gpio.o \
./twi.o 

C_DEPS += \
./Buzzer.d \
./Control_APP.d \
./DC.d \
./PWM.d \
./Timer1.d \
./UART.d \
./external_eeprom.d \
./gpio.d \
./twi.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


