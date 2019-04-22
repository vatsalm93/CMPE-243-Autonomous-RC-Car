/*
 * motor_control.h
 *
 *  Created on: Apr 9, 2019
 *      Author: Jay
 */

#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_

#include "motor_can_rx.h"
#include "c_io.h"
#include "c_pwm.h"
#include "speed_calculator.h"
#include "utilities.h"
#include "generated_can.h"

#ifdef __cplusplus
extern "C" {
#endif

//typedef struct{
//    float motor_pwm_value;
//    float servo_pwm_value;
//    bool can_rx_stat;
//}rxstat_val;

void motor_pwm_process(void);


#ifdef __cplusplus
}
#endif

#endif /* MOTOR_CONTROL_H_ */
