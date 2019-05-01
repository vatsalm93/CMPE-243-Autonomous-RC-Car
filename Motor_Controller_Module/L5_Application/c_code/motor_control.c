/*
 * motor_control.c
 *
 *  Created on: Apr 9, 2019
 *      Author: Jay
 */

#include "motor_control.h"
#include "printf_lib.h"

#define STEP_UPHILL 0.0002
#define STEP_DOWNHILL 0.0004
#define SPEED_LIMIT 16.10
#define STOP 15.00
#define REVERSE 14.2
#define FORWARD_START 15.7

#define NO_STEER 15.00
#define SLIGHT_RIGHT 17.00
#define SLIGHT_LEFT 13.00
#define HARD_RIGHT 19.00
#define HARD_LEFT 11.00

CAR_CONTROL_t drive = {2, 2, 0.00, {0}};

static float fw_pwm_val_motor = 15.7;
static bool fw_flag = false;

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
    switch (drive_servo->MOTOR_STEER_cmd) {
        case MOTOR_DONT_STEER:
            set_pwm_value(servo_2, NO_STEER);
            break;
        case MOTOR_STEER_FULL_LEFT:
            set_pwm_value(servo_2, HARD_LEFT);
            setLED(2,1);
            break;
        case MOTOR_STEER_SLIGHT_LEFT:
            set_pwm_value(servo_2, SLIGHT_LEFT);
            break;
        case MOTOR_STEER_SLIGHT_RIGHT:
            set_pwm_value(servo_2, SLIGHT_RIGHT);
            setLED(3,1);
            break;
        case MOTOR_STEER_FULL_RIGHT:
            set_pwm_value(servo_2, HARD_RIGHT);
            break;
    }
}

void forward_speed_control(CAR_CONTROL_t *drive_forward)
{
    float speed = get_speed();
    if (speed >= (drive_forward->MOTOR_kph + 1)) {
        setLED(3, 1);
        fw_flag = true;
        set_pwm_value(motor_1, STOP);
        fw_pwm_val_motor = STOP;
    }

    else {
        if (fw_pwm_val_motor > SPEED_LIMIT)
            fw_pwm_val_motor = SPEED_LIMIT;

        if (speed < (drive_forward->MOTOR_kph) && fw_pwm_val_motor < SPEED_LIMIT) {
            if (fw_flag == true) {
                fw_pwm_val_motor = FORWARD_START;
                fw_flag = false;
            }
            fw_pwm_val_motor += STEP_UPHILL;
        }
        if((int)speed == 0) {
            fw_pwm_val_motor += STEP_UPHILL + STEP_UPHILL;
        }
        set_pwm_value(motor_1, fw_pwm_val_motor);
    }
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
