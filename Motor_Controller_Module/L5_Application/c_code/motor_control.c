/*
 * motor_control.c
 *
 *  Created on: Apr 9, 2019
 *      Author: Jay
 */

#include "motor_control.h"
#include "printf_lib.h"
#include "rpm/c_pid.h"
#include "servo_degree.h"

#define STEP_UPHILL 0.002
#define STEP_DOWNHILL 0.0004
#define SPEED_LIMIT 16.05
#define STOP 15.00
#define REVERSE 14.2
#define FORWARD_START 15.7

#define NO_STEER 0
#define SLIGHT_RIGHT 17.00
#define SLIGHT_LEFT 13.00
#define HARD_RIGHT 19.00
#define HARD_LEFT 11.00

CAR_CONTROL_t drive = {MOTOR_STOP, NO_STEER, 0.00, {0}};
extern s_pid_t dc;
float fw_pwm_val_motor = 15.00;
//static bool fw_flag = false;

static uint32_t reverse_count = 0;
static bool reverse_flag = false;

void command_motor(CAR_CONTROL_t *drive_motor) {
    setLED(2, 0);
    setLED(3, 0);
    setLED(4, 0);

    switch (drive_motor->MOTOR_DRIVE_cmd) {

        case MOTOR_FORWARD:
            reverse_flag = false;
            setLED(2, 1);
            forward_speed_control(drive_motor);
            break;

        case MOTOR_STOP:
            reverse_flag = false;
            set_pwm_value(motor_1, STOP);
            setLED(4, 1);
            break;

        case MOTOR_REV:
            command_motor_reverse();
            break;

        default:
            reverse_flag = false;
            set_pwm_value(motor_1, STOP);
    }
}

void command_servo(CAR_CONTROL_t *drive_servo){
    drive.MOTOR_STEER_cmd = 180;
    float percent = get_servo_angle(drive_servo);
    set_pwm_value(servo_2, percent);
//    switch (drive_servo->MOTOR_STEER_cmd) {
//        case MOTOR_DONT_STEER:
//            set_pwm_value(servo_2, NO_STEER);
//            break;
//        case MOTOR_STEER_FULL_LEFT:
//            set_pwm_value(servo_2, HARD_LEFT);
//            break;
//        case MOTOR_STEER_SLIGHT_LEFT:
//            set_pwm_value(servo_2, SLIGHT_LEFT);
//            break;
//        case MOTOR_STEER_SLIGHT_RIGHT:
//            set_pwm_value(servo_2, SLIGHT_RIGHT);
//            break;
//        case MOTOR_STEER_FULL_RIGHT:
//            set_pwm_value(servo_2, HARD_RIGHT);
//            break;
//    }
}

void forward_speed_control(CAR_CONTROL_t *drive_forward) {
//    float speed = get_speed();
//    float _error = speed - drive_forward->MOTOR_kph;
//
//    if(_error > 0)
//        fw_pwm_val_motor -= _error/150;
//    else if(_error < 0)
//        fw_pwm_val_motor -= _error/220;
//    else{}
//
//    if(fw_pwm_val_motor < 15.00)
//        fw_pwm_val_motor = 15.00;
//    else if(fw_pwm_val_motor > 16.3)
//        fw_pwm_val_motor = 16.3;
////    if(_error > 2)
////        fw_pwm_val_motor = 15.00;
//
//    set_pwm_value(motor_1, fw_pwm_val_motor);

    float speed = get_speed();
    float _error = calculate(drive_forward->MOTOR_kph, speed, &dc);
    fw_pwm_val_motor += _error;
    if(fw_pwm_val_motor < 15.00)
        fw_pwm_val_motor = 15.00;
    else if(fw_pwm_val_motor > 16.3)
        fw_pwm_val_motor = 16.3;
    set_pwm_value(motor_1, fw_pwm_val_motor);
    u0_dbg_printf("PWM: %f\n", fw_pwm_val_motor);
}

void command_motor_reverse(void)
{
    if (false == reverse_flag) {
        if (6 == reverse_count) {
            reverse_flag = true;
            reverse_count = 0;
        }
        if (0 == reverse_count % 3) {
            set_pwm_value(motor_1, STOP);
        }
        else if (1 == reverse_count % 3) {
            set_pwm_value(motor_1, STOP);
        }
        else if (2 == reverse_count % 3) {
            set_pwm_value(motor_1, REVERSE);
        }
        ++reverse_count;
    }
    else {
        set_pwm_value(motor_1, REVERSE);
        reverse_count = 0;
    }
}
