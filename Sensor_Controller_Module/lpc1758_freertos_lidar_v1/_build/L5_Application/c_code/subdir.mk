################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../L5_Application/c_code/c_period_callbacks.c \
../L5_Application/c_code/queue.c 

CPP_SRCS += \
../L5_Application/c_code/c_gpio.cpp \
../L5_Application/c_code/c_io.cpp \
../L5_Application/c_code/c_pwm.cpp \
../L5_Application/c_code/c_switch.cpp \
../L5_Application/c_code/c_uart2.cpp 

OBJS += \
./L5_Application/c_code/c_gpio.o \
./L5_Application/c_code/c_io.o \
./L5_Application/c_code/c_period_callbacks.o \
./L5_Application/c_code/c_pwm.o \
./L5_Application/c_code/c_switch.o \
./L5_Application/c_code/c_uart2.o \
./L5_Application/c_code/queue.o 

C_DEPS += \
./L5_Application/c_code/c_period_callbacks.d \
./L5_Application/c_code/queue.d 

CPP_DEPS += \
./L5_Application/c_code/c_gpio.d \
./L5_Application/c_code/c_io.d \
./L5_Application/c_code/c_pwm.d \
./L5_Application/c_code/c_switch.d \
./L5_Application/c_code/c_uart2.d 


# Each subdirectory must supply rules for building sources it contributes
L5_Application/c_code/%.o: ../L5_Application/c_code/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -ffunction-sections -fdata-sections -Wall -Wshadow -Wlogical-op -Wfloat-equal -DBUILD_CFG_MPU=0 -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\newlib" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L0_LowLevel" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L1_FreeRTOS" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L1_FreeRTOS\include" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L1_FreeRTOS\portable" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L1_FreeRTOS\portable\no_mpu" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L2_Drivers" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L2_Drivers\base" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L3_Utils" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L3_Utils\tlm" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L4_IO" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L4_IO\fat" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L4_IO\wireless" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L5_Application" -std=gnu++11 -fabi-version=0 -fno-exceptions -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

L5_Application/c_code/%.o: ../L5_Application/c_code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -ffunction-sections -fdata-sections -Wall -Wshadow -Wlogical-op -Wfloat-equal -DBUILD_CFG_MPU=0 -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\newlib" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L0_LowLevel" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L1_FreeRTOS" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L1_FreeRTOS\include" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L1_FreeRTOS\portable\no_mpu" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L2_Drivers" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L2_Drivers\base" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L3_Utils" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L3_Utils\tlm" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L4_IO" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L4_IO\fat" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L4_IO\wireless" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L5_Application" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


