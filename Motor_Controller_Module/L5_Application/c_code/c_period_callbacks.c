/**
 * @file
 *
 * The purpose of this "C" callbacks is to provide the code to be able
 * to call pure C functions and unit-test it in C test framework
 */
#include <stdint.h>
#include <stdbool.h>
#include "c_pwm.h"
#include <stdint.h>
#include "c_period_callbacks.h"
#include "c_pwm.h"
#include "printf_lib.h"
#include "utilities.h"
#include "c_code/motor_can_rx.h"
#include "c_code/motor_control.h"

bool C_period_init(void) {
    motor_can_init();
    init_pwm(100);
    set_pwm_value(motor_1, 15);
    set_pwm_value(servo_2, 15);
    return true;
}
bool C_period_reg_tlm(void) {
    return true;
}

void C_period_1Hz(uint32_t count) {
    motor_can_tx_heartbeat();
    (void) count;
}

void C_period_10Hz(uint32_t count) {
    (void) count;
}

void C_period_100Hz(uint32_t count) {
    (void) count;
    motor_pwm_process();
//        if(setpwm.can_rx_stat){
//            set_pwm_value(motor_1, setpwm.motor_pwm_value);
//            set_pwm_value(servo_2, setpwm.servo_pwm_value);
//            u0_dbg_printf("motor: %f servo: %f\n", setpwm.motor_pwm_value, setpwm.servo_pwm_value);
//        }
}

void C_period_1000Hz(uint32_t count) {
    (void) count;
    motor_can_reset_busoff();
}
