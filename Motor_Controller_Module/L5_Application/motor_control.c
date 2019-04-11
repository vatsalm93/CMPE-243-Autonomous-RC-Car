/*
 * motor_control.c
 *
 *  Created on: Apr 9, 2019
 *      Author: Jay
 */
#include "motor_control.h"

rxstat_val motor_pwm_process(void){

    rxstat_val motor_pwm = {0};
    CAR_CONTROL_t drive = {0};

    motor_pwm.can_rx_stat = motor_can_rx(&drive);

    switch(drive.MOTOR_DRIVE_cmd){
        case MOTOR_STOP:
            motor_pwm.motor_pwm_value = 15.00;
            break;
        case MOTOR_FWD_SLOW:
            motor_pwm.motor_pwm_value = 15.8;
            break;
        case MOTOR_FWD_MED:
            break;
        case MOTOR_REV:
            break;
        case MOTOR_FWD_FAST:
            break;
    }
    switch(drive.MOTOR_STEER_cmd){
        case MOTOR_DONT_STEER:
            motor_pwm.servo_pwm_value = 15.00;
            break;
        case MOTOR_STEER_FULL_LEFT:
            motor_pwm.servo_pwm_value = 11.5;
            break;
        case MOTOR_STEER_SLIGHT_LEFT:
            motor_pwm.servo_pwm_value = 14.00;
            break;
        case MOTOR_STEER_SLIGHT_RIGHT:
            motor_pwm.servo_pwm_value = 16.00;
            break;
        case MOTOR_STEER_FULL_RIGHT:
            motor_pwm.servo_pwm_value = 18.5;
            break;

    }
    return motor_pwm;
}

