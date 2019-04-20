/*
 * motor_control.c
 *
 *  Created on: Apr 9, 2019
 *      Author: Jay
 */
#include "motor_control.h"
#include "printf_lib.h"
#include "c_io.h"

const uint32_t CAR_CONTROL__MIA_MS = 3000;
const CAR_CONTROL_t CAR_CONTROL__MIA_MSG = {MOTOR_STOP, MOTOR_DONT_STEER, {0}};


void motor_pwm_process(void)
{
//    rxstat_val motor_pwm = {0};
    static CAR_CONTROL_t drive = {2, 2};
    static uint32_t count = 0;
    static bool flag = false;
    setLED(2, 0);
    setLED(3, 0);
    setLED(4, 0);
//    motor_pwm.can_rx_stat =
    motor_can_rx(&drive);

    switch (drive.MOTOR_DRIVE_cmd) {
        case MOTOR_STOP:
            flag = false;
            u0_dbg_printf("stop\n",count);
            set_pwm_value(motor_1, 15.00);
            setLED(4, 1);
            break;
        case MOTOR_FWD_SLOW:
            flag = false;
            u0_dbg_printf("fwd slow\n",count);
            set_pwm_value(motor_1, 15.8);
            setLED(2, 1);
            break;
        case MOTOR_FWD_MED:
            flag = false;
            u0_dbg_printf("fwd med\n",count);
            set_pwm_value(motor_1, 16.5);
            break;
        case MOTOR_REV:
//            set_pwm_value(motor_1, 14.2);
//            delay_ms(30);
//            set_pwm_value(motor_1, 15);
//            delay_ms(30);
//            set_pwm_value(motor_1, 14.2);
            if (flag == false) {
                u0_dbg_printf("in flag_false_rev\n");
                if (6 == count) {
                    flag = true;
                    u0_dbg_printf("count 4\n");
                    count = 0;
                }
                if (count % 3 == 0) {
                    u0_dbg_printf("%d\n",count);
                    set_pwm_value(motor_1, 15.00);
                }
                else if(count % 3 == 1){
                    u0_dbg_printf("%d\n",count);
                    set_pwm_value(motor_1, 15.00);
                }
                else if (count % 3 == 2) {
                    u0_dbg_printf("%d\n",count);
                    set_pwm_value(motor_1, 14.2);
                }
                ++count;
            }
            else{
                u0_dbg_printf("else\n");
                set_pwm_value(motor_1, 14.2);
                count = 0;
            }
            setLED(3, 1);
            break;
        case MOTOR_FWD_FAST:
            flag = false;
            u0_dbg_printf("fwd fast\n",count);
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
            break;

    }
//    return motor_pwm;
}

