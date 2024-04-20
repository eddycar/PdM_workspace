################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Utilities/Src/config.c \
../Drivers/Utilities/Src/error_handler.c \
../Drivers/Utilities/Src/typedefs.c 

OBJS += \
./Drivers/Utilities/Src/config.o \
./Drivers/Utilities/Src/error_handler.o \
./Drivers/Utilities/Src/typedefs.o 

C_DEPS += \
./Drivers/Utilities/Src/config.d \
./Drivers/Utilities/Src/error_handler.d \
./Drivers/Utilities/Src/typedefs.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Utilities/Src/%.o Drivers/Utilities/Src/%.su Drivers/Utilities/Src/%.cyclo: ../Drivers/Utilities/Src/%.c Drivers/Utilities/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F439xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/ASUS/Desktop/PdM_workspace/Proyectos/Trabajo_Practico_Final/DAQ_Temp/Drivers/API" -I"C:/Users/ASUS/Desktop/PdM_workspace/Proyectos/Trabajo_Practico_Final/DAQ_Temp/Drivers/API/Inc" -I"C:/Users/ASUS/Desktop/PdM_workspace/Proyectos/Trabajo_Practico_Final/DAQ_Temp/Drivers/STM32F4xx_HAL_Driver" -I"C:/Users/ASUS/Desktop/PdM_workspace/Proyectos/Trabajo_Practico_Final/DAQ_Temp/Drivers/STM32F4xx_HAL_Driver/Src" -I"C:/Users/ASUS/Desktop/PdM_workspace/Proyectos/Trabajo_Practico_Final/DAQ_Temp/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/ASUS/Desktop/PdM_workspace/Proyectos/Trabajo_Practico_Final/DAQ_Temp/Drivers/Utilities" -I"C:/Users/ASUS/Desktop/PdM_workspace/Proyectos/Trabajo_Practico_Final/DAQ_Temp/Drivers/Utilities/Src" -I"C:/Users/ASUS/Desktop/PdM_workspace/Proyectos/Trabajo_Practico_Final/DAQ_Temp/Drivers/Utilities/Inc" -O0 -ffunction-sections -fdata-sections -Wall -u _printf_float -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Utilities-2f-Src

clean-Drivers-2f-Utilities-2f-Src:
	-$(RM) ./Drivers/Utilities/Src/config.cyclo ./Drivers/Utilities/Src/config.d ./Drivers/Utilities/Src/config.o ./Drivers/Utilities/Src/config.su ./Drivers/Utilities/Src/error_handler.cyclo ./Drivers/Utilities/Src/error_handler.d ./Drivers/Utilities/Src/error_handler.o ./Drivers/Utilities/Src/error_handler.su ./Drivers/Utilities/Src/typedefs.cyclo ./Drivers/Utilities/Src/typedefs.d ./Drivers/Utilities/Src/typedefs.o ./Drivers/Utilities/Src/typedefs.su

.PHONY: clean-Drivers-2f-Utilities-2f-Src

