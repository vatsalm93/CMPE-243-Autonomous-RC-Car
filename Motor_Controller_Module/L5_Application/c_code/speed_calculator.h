/*
 * speed_calculator.h
 *
 *  Created on: Apr 19, 2019
 *      Author: Jay
 */

#ifndef SPEED_CALCULATOR_H_
#define SPEED_CALCULATOR_H_

#include <stdint.h>
#include <stdbool.h>
#include "lpc_timers.h"
#define circumference 0.33

typedef struct{
    uint16_t rpm_pulses_sec;
    uint8_t speed_km_hr;
} rpm_sensor_t;

void eint3_handler(void);
float calculate_speed(void);
float get_speed(void);
#endif /* SPEED_CALCULATOR_H_ */
