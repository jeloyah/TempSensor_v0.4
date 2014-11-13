################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Project_Settings/Startup_Code/startup.c 

OBJS += \
./Project_Settings/Startup_Code/startup.o 

C_DEPS += \
./Project_Settings/Startup_Code/startup.d 


# Each subdirectory must supply rules for building sources it contributes
Project_Settings/Startup_Code/%.o: ../Project_Settings/Startup_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/UABC/workspace.kds/Temp_Sensor/TempSensor_v0.4/Static_Code\PDD" -I"C:/Users/UABC/workspace.kds/Temp_Sensor/TempSensor_v0.4/Static_Code\IO_Map" -I"C:/Users/UABC/workspace.kds/Temp_Sensor/TempSensor_v0.4/Sources" -I"C:/Users/UABC/workspace.kds/Temp_Sensor/TempSensor_v0.4/Generated_Code" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


