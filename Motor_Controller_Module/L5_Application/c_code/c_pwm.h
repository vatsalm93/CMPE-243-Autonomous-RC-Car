/*
 * c_pwm.h
 *
 *  Created on: Apr 14, 2019
 *      Author: Jay
 */

#ifndef C_PWM_H_
#define C_PWM_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    motor_1 = 1,
    servo_2 = 2,
}pwm_pin_t;

void init_pwm(long unsigned int freq);
bool set_pwm_value(pwm_pin_t pwm_pin, float percent);

#ifdef __cplusplus
}
#endif

#endif /* C_PWM_H_ */
