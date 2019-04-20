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
#include "speed_calculator.h"
#include "eint.h"
#include "c_io.h"
#include "c_gpio.h"

//void_func_t *ptr = eint3_handler;

bool C_period_init(void) {

    setLED(1, 0);
    eint3_enable_port2(6, eint_falling_edge, eint3_handler);
    motor_can_init();
    init_pwm(100);
    set_pwm_value(motor_1, 15);
    set_pwm_value(servo_2, 15);
    setPin();
    setInput();

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
    motor_pwm_process();
    (void) count;
}

void C_period_100Hz(uint32_t count) {
    (void) count;
 //   if(!read_pin())
 //   u0_dbg_printf("Value: %d\n", read_pin());
    C_period_10Hz(count);
}

void C_period_1000Hz(uint32_t count) {
    (void) count;
    motor_can_reset_busoff();
}

