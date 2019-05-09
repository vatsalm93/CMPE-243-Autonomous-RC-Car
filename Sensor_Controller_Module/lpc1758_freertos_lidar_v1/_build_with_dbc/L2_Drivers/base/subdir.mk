################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../L2_Drivers/base/char_dev.cpp \
../L2_Drivers/base/i2c_base.cpp \
../L2_Drivers/base/uart_dev.cpp 

OBJS += \
./L2_Drivers/base/char_dev.o \
./L2_Drivers/base/i2c_base.o \
./L2_Drivers/base/uart_dev.o 

CPP_DEPS += \
./L2_Drivers/base/char_dev.d \
./L2_Drivers/base/i2c_base.d \
./L2_Drivers/base/uart_dev.d 


# Each subdirectory must supply rules for building sources it contributes
L2_Drivers/base/%.o: ../L2_Drivers/base/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -ffunction-sections -fdata-sections -Wall -Wshadow -Wlogical-op -Wfloat-equal -DBUILD_CFG_MPU=0 -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\newlib" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L0_LowLevel" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L1_FreeRTOS" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L1_FreeRTOS\include" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L1_FreeRTOS\portable" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L1_FreeRTOS\portable\no_mpu" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L2_Drivers" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L2_Drivers\base" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L3_Utils" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L3_Utils\tlm" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L4_IO" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L4_IO\fat" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L4_IO\wireless" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L5_Application" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L5_Application\c_code" -std=gnu++11 -fabi-version=0 -fno-exceptions -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


