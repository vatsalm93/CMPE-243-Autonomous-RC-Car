/*
 * motor_control.c
 *
 *  Created on: Apr 9, 2019
 *      Author: Jay
 */
#include "motor_control.h"

void motor_pwm_process(void)
{
//    rxstat_val motor_pwm = {0};
    CAR_CONTROL_t drive = { 0 };

//    motor_pwm.can_rx_stat =
    motor_can_rx(&drive);

    switch (drive.MOTOR_DRIVE_cmd) {
        case MOTOR_STOP:
            set_pwm_value(motor_1, 15.00);
            break;
        case MOTOR_FWD_SLOW:
            set_pwm_value(motor_1, 15.8);
            break;
        case MOTOR_FWD_MED:
            set_pwm_value(motor_1, 16.5);
            break;
        case MOTOR_REV:
            set_pwm_value(motor_1, 14.2);
//            delay_ms(30);
//            set_pwm_value(motor_1, 15);
//            delay_ms(30);
//            set_pwm_value(motor_1, 14.2);
            break;
        case MOTOR_FWD_FAST:
            set_pwm_value(motor_1, 18);
            break;
        default:
            set_pwm_value(motor_1, 15);
    }

    switch (drive.MOTOR_STEER_cmd) {
        case MOTOR_DONT_STEER:
            set_pwm_value(servo_2, 15.00);
            break;
        case MOTOR_STEER_FULL_LEFT:
            set_pwm_value(servo_2, 11.50);
            break;
        case MOTOR_STEER_SLIGHT_LEFT:
            set_pwm_value(servo_2, 14.00);
            break;
        case MOTOR_STEER_SLIGHT_RIGHT:
            set_pwm_value(servo_2, 16.00);
            ;
            break;
        case MOTOR_STEER_FULL_RIGHT:
            set_pwm_value(servo_2, 18.50);
            ;
            break;

    }
//    return motor_pwm;
}

