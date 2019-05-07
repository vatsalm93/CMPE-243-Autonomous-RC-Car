/*
 * servo_degree.c
 *
 *  Created on: May 4, 2019
 *      Author: Jay
 */

#include "servo_degree.h"
#include "printf_lib.h"

float get_servo_angle(CAR_CONTROL_t * servo) {
    float  on_time = 0;
    if((servo->MOTOR_STEER_cmd + 90) > 180 && servo->MOTOR_STEER_cmd <= 270)
        on_time = 20;
    else if((servo->MOTOR_STEER_cmd + 90) > 270 && servo->MOTOR_STEER_cmd <= 359.99)
        on_time = 10;
    else
        on_time = 10 + ((servo->MOTOR_STEER_cmd + 90) * (0.05555));

    u0_dbg_printf("percent: %f\n", on_time);
    return on_time;
}
