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

#define NO_STEER 15.00
#define SLIGHT_RIGHT 17.00
#define SLIGHT_LEFT 13.00
#define HARD_RIGHT 19.00
#define HARD_LEFT 11.00

const uint32_t CAR_CONTROL__MIA_MS = 3000;
const CAR_CONTROL_t CAR_CONTROL__MIA_MSG = { MOTOR_STOP, MOTOR_DONT_STEER, 0, { 0 } };
CAR_CONTROL_t drive = {2, 2};

void motor_pwm_process(void)
{
//    static CAR_CONTROL_t drive = { 2, 2 };
    static uint32_t count = 0;
    static bool flag = false;
    setLED(2, 0);
    setLED(3, 0);
    setLED(4, 0);

//    motor_can_rx(&drive);

    switch (drive.MOTOR_STEER_cmd) {
        case MOTOR_DONT_STEER:
            set_pwm_value(servo_2, NO_STEER);
            break;
        case MOTOR_STEER_FULL_LEFT:
            set_pwm_value(servo_2, HARD_LEFT);
            break;
        case MOTOR_STEER_SLIGHT_LEFT:
            set_pwm_value(servo_2, SLIGHT_LEFT);
            break;
        case MOTOR_STEER_SLIGHT_RIGHT:
            set_pwm_value(servo_2, SLIGHT_RIGHT);
            break;
        case MOTOR_STEER_FULL_RIGHT:
            set_pwm_value(servo_2, HARD_RIGHT);
            break;
    }

    switch (drive.MOTOR_DRIVE_cmd) {
        case MOTOR_FORWARD:
            flag = false;
            setLED(2, 1);
            forward_speed_control(&drive);
            break;
        case MOTOR_STOP:
            flag = false;
            set_pwm_value(motor_1, STOP);
            setLED(4, 1);
            break;
        case MOTOR_REV:
            if (flag == false) {
                if (6 == count) {
                    flag = true;
                    count = 0;
                }
                if (count % 3 == 0) {
                    set_pwm_value(motor_1, 15.00);
                }
                else if (count % 3 == 1) {
                    set_pwm_value(motor_1, 15.00);
                }
                else if (count % 3 == 2) {
                    set_pwm_value(motor_1, 14.2);
                }
                ++count;
            }
            else {
                set_pwm_value(motor_1, 14.2);
                count = 0;
            }
            break;
        default:
            set_pwm_value(motor_1, STOP);
    }
}

void forward_speed_control(CAR_CONTROL_t *drive_forward)
{
    static float pwm_val_motor = 15.7;
    static bool flag = false;
    float speed = get_speed();

    if (speed > (drive_forward->MOTOR_kph + 0.6)) {
        setLED(3, 1);
        flag = ramp_stop_car();
        pwm_val_motor = STOP;
    }

    else {
        if (pwm_val_motor < STOP) pwm_val_motor = STOP;
        else if (pwm_val_motor > SPEED_LIMIT) pwm_val_motor = SPEED_LIMIT;

        if (speed < (drive_forward->MOTOR_kph) && pwm_val_motor < SPEED_LIMIT) {
            if (flag == true) {
                pwm_val_motor = 15.7;
                flag = false;
            }
            pwm_val_motor += STEP_UPHILL;
            set_pwm_value(motor_1, pwm_val_motor);
        }
        else
            set_pwm_value(motor_1, pwm_val_motor);
    }
}

bool ramp_stop_car(void)
{
    static uint32_t count1 = 0;
    static bool flag1 = false;
    if (flag1 == false) {
        if (6 == count1) {
            flag1 = true;
            count1 = 0;
        }
        if (count1 % 3 == 0) {
            set_pwm_value(motor_1, 15.00);
        }
        else if (count1 % 3 == 1) {
            set_pwm_value(motor_1, 15.00);
        }
        else if (count1 % 3 == 2) {
            set_pwm_value(motor_1, 14.7);
        }
        ++count1;
    }
    else {
        set_pwm_value(motor_1, 14.7);
        count1 = 0;
    }
    return true;
}
