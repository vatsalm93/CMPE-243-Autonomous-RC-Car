################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../L4_IO/wireless/src/mesh.c \
../L4_IO/wireless/src/nrf24L01Plus.c \
../L4_IO/wireless/src/wireless.c 

OBJS += \
./L4_IO/wireless/src/mesh.o \
./L4_IO/wireless/src/nrf24L01Plus.o \
./L4_IO/wireless/src/wireless.o 

C_DEPS += \
./L4_IO/wireless/src/mesh.d \
./L4_IO/wireless/src/nrf24L01Plus.d \
./L4_IO/wireless/src/wireless.d 


# Each subdirectory must supply rules for building sources it contributes
L4_IO/wireless/src/%.o: ../L4_IO/wireless/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -ffunction-sections -fdata-sections -Wall -Wshadow -Wlogical-op -Wfloat-equal -DBUILD_CFG_MPU=0 -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\newlib" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L0_LowLevel" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L1_FreeRTOS" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L1_FreeRTOS\include" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L1_FreeRTOS\portable\no_mpu" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L2_Drivers" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L2_Drivers\base" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L3_Utils" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L3_Utils\tlm" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L4_IO" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L4_IO\fat" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L4_IO\wireless" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L5_Application" -I"E:\My_Project\CMPE-243\cmpe243_techsavy_rc_car\Sensor_Controller_Module\lpc1758_freertos_lidar_v1\L5_Application\c_code" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


