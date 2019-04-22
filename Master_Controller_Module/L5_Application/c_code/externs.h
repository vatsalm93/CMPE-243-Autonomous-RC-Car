/*
 * externs.h
 *
 *  Created on: Apr 17, 2019
 *      Author: Aakash
 */

#ifndef EXTERNS_H_
#define EXTERNS_H_
#include "stdbool.h"
#include "../../_can_dbc/generated_can.h"
#include "can.h"
extern bool start_cmd;
extern bool sensor_hbt_sync;
extern bool motor_hbt_sync;
extern bool gps_hbt_sync;
extern bool bridge_hbt_sync;

extern BRIDGE_NODE_t bridge_data;
extern SENSOR_NODE_t sensor_data;
extern GPS_LOCATION_t gps_data;
extern COMPASS_t compass_data;
extern CAR_CONTROL_t car_control;
extern SENSOR_HEARTBEAT_t sensor_hbt;
extern MOTOR_HEARTBEAT_t motor_hbt;
extern GPS_HEARTBEAT_t gps_hbt;
extern BRIDGE_HEARTBEAT_t bridge_hbt;

extern can_msg_t can_msg;
extern dbc_msg_hdr_t can_msg_hdr;

#endif /* EXTERNS_H_ */
