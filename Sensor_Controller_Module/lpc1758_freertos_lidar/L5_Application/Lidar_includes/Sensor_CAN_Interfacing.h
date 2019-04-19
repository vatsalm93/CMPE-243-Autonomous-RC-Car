/*
 * Sensor_CAN_Interfacing.h
 *
 *  Created on: Apr 13, 2019
 *      Author: halak
 */

#ifndef SENSOR_CAN_INTERFACING_H_
#define SENSOR_CAN_INTERFACING_H_

#include <stdint.h>

bool sensor_can_init();
bool sensor_send_data(void);
bool sensor_CAN_turn_on_bus_if_bus_off();
bool transmit_heartbeat_on_can(void);

#endif /* SENSOR_CAN_INTERFACING_H_ */
