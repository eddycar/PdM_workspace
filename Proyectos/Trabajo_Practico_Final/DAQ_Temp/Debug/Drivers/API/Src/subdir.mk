################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/API/Src/API_debounce.c \
../Drivers/API/Src/API_delay.c \
../Drivers/API/Src/FINITE_STATE_MACHINE.c \
../Drivers/API/Src/MAX31865_lib.c \
../Drivers/API/Src/SPI.c \
../Drivers/API/Src/UART.c 

OBJS += \
./Drivers/API/Src/API_debounce.o \
./Drivers/API/Src/API_delay.o \
./Drivers/API/Src/FINITE_STATE_MACHINE.o \
./Drivers/API/Src/MAX31865_lib.o \
./Drivers/API/Src/SPI.o \
./Drivers/API/Src/UART.o 

C_DEPS += \
./Drivers/API/Src/API_debounce.d \
./Drivers/API/Src/API_delay.d \
./Drivers/API/Src/FINITE_STATE_MACHINE.d \
./Drivers/API/Src/MAX31865_lib.d \
./Drivers/API/Src/SPI.d \
./Drivers/API/Src/UART.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/API/Src/%.o Drivers/API/Src/%.su Drivers/API/Src/%.cyclo: ../Drivers/API/Src/%.c Drivers/API/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F439xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/ASUS/Desktop/Trabajo_Practico_Final/DAQ_Temp/Drivers/API" -I"C:/Users/ASUS/Desktop/Trabajo_Practico_Final/DAQ_Temp/Drivers/API/Inc" -I"C:/Users/ASUS/Desktop/Trabajo_Practico_Final/DAQ_Temp/Drivers/STM32F4xx_HAL_Driver" -I"C:/Users/ASUS/Desktop/Trabajo_Practico_Final/DAQ_Temp/Drivers/STM32F4xx_HAL_Driver/Src" -I"C:/Users/ASUS/Desktop/Trabajo_Practico_Final/DAQ_Temp/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/ASUS/Desktop/Trabajo_Practico_Final/DAQ_Temp/Drivers/Utilities" -I"C:/Users/ASUS/Desktop/Trabajo_Practico_Final/DAQ_Temp/Drivers/Utilities/Src" -I"C:/Users/ASUS/Desktop/Trabajo_Practico_Final/DAQ_Temp/Drivers/Utilities/Inc" -I"C:/Users/ASUS/Desktop/Trabajo_Practico_Final/DAQ_Temp/Drivers/API/Src" -O0 -ffunction-sections -fdata-sections -Wall -u _printf_float -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-API-2f-Src

clean-Drivers-2f-API-2f-Src:
	-$(RM) ./Drivers/API/Src/API_debounce.cyclo ./Drivers/API/Src/API_debounce.d ./Drivers/API/Src/API_debounce.o ./Drivers/API/Src/API_debounce.su ./Drivers/API/Src/API_delay.cyclo ./Drivers/API/Src/API_delay.d ./Drivers/API/Src/API_delay.o ./Drivers/API/Src/API_delay.su ./Drivers/API/Src/FINITE_STATE_MACHINE.cyclo ./Drivers/API/Src/FINITE_STATE_MACHINE.d ./Drivers/API/Src/FINITE_STATE_MACHINE.o ./Drivers/API/Src/FINITE_STATE_MACHINE.su ./Drivers/API/Src/MAX31865_lib.cyclo ./Drivers/API/Src/MAX31865_lib.d ./Drivers/API/Src/MAX31865_lib.o ./Drivers/API/Src/MAX31865_lib.su ./Drivers/API/Src/SPI.cyclo ./Drivers/API/Src/SPI.d ./Drivers/API/Src/SPI.o ./Drivers/API/Src/SPI.su ./Drivers/API/Src/UART.cyclo ./Drivers/API/Src/UART.d ./Drivers/API/Src/UART.o ./Drivers/API/Src/UART.su

.PHONY: clean-Drivers-2f-API-2f-Src

