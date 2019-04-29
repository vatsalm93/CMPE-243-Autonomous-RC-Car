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
	arm-none-eabi-g++ -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -ffunction-sections -fdata-sections -Wall -Wshadow -Wlogical-op -Wfloat-equal -DBUILD_CFG_MPU=0 -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar" -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar\newlib" -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar\L0_LowLevel" -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar\L1_FreeRTOS" -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar\L1_FreeRTOS\include" -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar\L1_FreeRTOS\portable" -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar\L1_FreeRTOS\portable\no_mpu" -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar\L2_Drivers" -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar\L2_Drivers\base" -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar\L3_Utils" -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar\L3_Utils\tlm" -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar\L4_IO" -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar\L4_IO\fat" -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar\L4_IO\wireless" -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar\L5_Application" -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar\L5_Application\c_code" -std=gnu++11 -fabi-version=0 -fno-exceptions -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

L5_Application/c_code/%.o: ../L5_Application/c_code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -ffunction-sections -fdata-sections -Wall -Wshadow -Wlogical-op -Wfloat-equal -DBUILD_CFG_MPU=0 -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar" -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar\newlib" -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar\L0_LowLevel" -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar\L1_FreeRTOS" -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar\L1_FreeRTOS\include" -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar\L1_FreeRTOS\portable\no_mpu" -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar\L2_Drivers" -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar\L2_Drivers\base" -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar\L3_Utils" -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar\L3_Utils\tlm" -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar\L4_IO" -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar\L4_IO\fat" -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar\L4_IO\wireless" -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar\L5_Application" -I"C:\Users\Aakash\Downloads\CMPE243\SJSU_Dev_hyperload2\SJSU_Dev\projects\lpc1758_freertos_lidar\L5_Application\c_code" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


