/*
 * servo_degree.c
 *
 *  Created on: May 4, 2019
 *      Author: Jay
 */

#include "servo_degree.h"

extern CAR_CONTROL_t drive;

float get_servo_angle(void) {
    float  on_time = 0;
    if(drive.MOTOR_STEER_cmd > 180 && drive.MOTOR_STEER_cmd <= 270)
        on_time = 20;
    else if(drive.MOTOR_STEER_cmd > 270 && drive.MOTOR_STEER_cmd <= 359.99)
        on_time = 10;
    else
        on_time = 10 + (drive.MOTOR_STEER_cmd * (10 / 180));
    return on_time;
}
