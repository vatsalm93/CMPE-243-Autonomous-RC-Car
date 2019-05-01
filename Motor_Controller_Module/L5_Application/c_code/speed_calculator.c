/*
 * speed_calculator.c
 *
 *  Created on: Apr 19, 2019
 *      Author: Jay
 */

#include "speed_calculator.h"

uint16_t pulse = 0;
float speed_m_sec = 0;

void eint3_handler(void){
    pulse++;
}

float get_speed(void) {
    return speed_m_sec;
}

float calculate_speed(void) {
    uint16_t rotation_per_sec = pulse;
    pulse = 0;
    speed_m_sec = (circumference * rotation_per_sec) / (2.7);
    return speed_m_sec;
}
