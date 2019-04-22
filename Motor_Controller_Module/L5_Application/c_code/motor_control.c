/*
 * motor_control.c
 *
 *  Created on: Apr 9, 2019
 *      Author: Jay
 */
#include "motor_control.h"
#include "printf_lib.h"

#define FAST_SPEED 16.80
#define MEDIUM_SPEED 16.20
#define SLOW_SPEED 15.92
#define STOP 15.00

#define NO_STEER 15.00
#define SLIGHT_RIGHT 16.00
#define SLIGHT_LEFT 14.00
#define HARD_RIGHT 19.50
#define HARD_LEFT 10.50

const uint32_t CAR_CONTROL__MIA_MS = 3000;
const CAR_CONTROL_t CAR_CONTROL__MIA_MSG = {MOTOR_STOP, MOTOR_DONT_STEER, 0, {0}};


void motor_pwm_process(void)
{
    static CAR_CONTROL_t drive = {2, 2};
    static uint32_t count = 0;
    static bool flag = false;
    setLED(2, 0);
    setLED(3, 0);
    setLED(4, 0);

    motor_can_rx(&drive);
    // static pwm_val_motor = 15;
    switch (drive.MOTOR_DRIVE_cmd) {
        case MOTOR_STOP:
            /*
              if(pwm_val_motor < 15.8){
                  pwm_val_motor = 15.8;
              }
              else if(pwm_val_motor > 16){
                  pwm_val_motor = 16.00;
              }
              if(get_speed < drive.mph){
                  set_PWM(motor_1, pwm_val_motor + 0.005);
              }
              if(get_speed > drive.mph){
                  set_PWM(motor_1, pwm_val_motor - 0.005);
              }
             */
            flag = false;
            set_pwm_value(motor_1, STOP);
            setLED(4, 1);
            break;
//        case MOTOR_FWD_SLOW:
//            flag = false;
//            set_pwm_value(motor_1, SLOW_SPEED);
//            setLED(2, 1);
//            break;
//        case MOTOR_FWD_MED:
//            flag = false;
//            set_pwm_value(motor_1, MEDIUM_SPEED);
//            break;
        case MOTOR_REV:
            if (flag == false) {
                u0_dbg_printf("in flag_false_rev\n");
                if (6 == count) {
                    flag = true;
                    count = 0;
                }
                if (count % 3 == 0) {
                    set_pwm_value(motor_1, 15.00);
                }
                else if(count % 3 == 1){
                    set_pwm_value(motor_1, 15.00);
                }
                else if (count % 3 == 2) {
                    set_pwm_value(motor_1, 14.2);
                }
                ++count;
            }
            else{
                set_pwm_value(motor_1, 14.2);
                count = 0;
            }
            setLED(3, 1);
            break;
//        case MOTOR_FWD_FAST:
//            flag = false;
//            set_pwm_value(motor_1, FAST_SPEED);
//            break;
        default:
            set_pwm_value(motor_1, STOP);
    }

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
}

void forward_speed_control(CAR_CONTROL_t *drive)
{
    static uint8_t pwm_val_motor = 15;
    if (pwm_val_motor < 15.8) {
        pwm_val_motor = 15.8;
    }
    else if (pwm_val_motor > 16) {
        pwm_val_motor = 16.00;
    }
    if (get_speed() < drive->MOTOR_kph) {
        set_pwm_value(motor_1, pwm_val_motor + 0.005);
    }
    if (get_speed() > drive->MOTOR_kph) {
        set_pwm_value(motor_1, pwm_val_motor - 0.005);
    }
}
