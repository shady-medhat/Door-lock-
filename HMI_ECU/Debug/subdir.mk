################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HMI_APP.c \
../Timer1.c \
../UART.c \
../gpio.c \
../keypad.c \
../lcd.c 

OBJS += \
./HMI_APP.o \
./Timer1.o \
./UART.o \
./gpio.o \
./keypad.o \
./lcd.o 

C_DEPS += \
./HMI_APP.d \
./Timer1.d \
./UART.d \
./gpio.d \
./keypad.d \
./lcd.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


