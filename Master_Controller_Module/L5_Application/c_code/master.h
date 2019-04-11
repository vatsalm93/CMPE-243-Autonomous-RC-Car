/*
 * master.h
 *
 *  Created on: Apr 4, 2019
 *      Author: Aakash
 */

#ifndef MASTER_H_
#define MASTER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdbool.h"

#define BRIDGE_NODE 103
#define SENSOR_NODE 104
#define MOTOR_NODE 105
#define GPS_LOCATION 107
#define COMPASS         108

#define MASTER_CAN_BUS      can1
#define MASTER_BAUD_RATE    100
#define MASTER_RX_Q         8
#define MASTER_TX_Q         8

typedef enum
{
    NACK = 0,
    ACK
} master_ack_e;

void master_controller_init(void);
bool master_avoid_obstacle(void);
void master_service_can_msgs(void);

void service_sensor_msg(void);
void service_gps_msg(void);
void service_bridge_msg(void);
void service_compass_msg(void);

bool master_CAN_turn_on_bus_if_bus_off(void);
void master_send_command_to_motor_module(void);

#ifdef __cplusplus
}
#endif

#endif /* MASTER_H_ */
