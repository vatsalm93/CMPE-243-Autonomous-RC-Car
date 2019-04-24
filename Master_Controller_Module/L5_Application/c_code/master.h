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
#include "structures.h"

typedef enum
{
    NACK = 0,
    ACK
} master_ack_e;

void master_controller_init(void);
void start_obstacle_avoidance(obstacle_detection_t obs_detected);
void start_obstacle_detection(obstacle_detection_t *obs_detection);
void master_service_can_msgs(void);

bool master_CAN_turn_on_bus_if_bus_off(void);
void master_send_command_to_motor_module(void);

 void drive_motor_fwd_slow(void);
 void drive_motor_fwd_med(void);
 void drive_motor_fwd_fast(void);
 void drive_motor_rev_slow(void);

 void drive_motor_stop(void);

 void master_steer_full_left(void);
 void master_steer_full_right(void);
 void master_steer_slight_left(void);
 void master_steer_slight_right(void);
 void master_dont_steer(void);

bool sys_start_stop_cmd(void);
void master_mia_handler(void);
void service_sensor_hbt_msg(void);
void service_motor_hbt_msg(void);
void service_gps_hbt_msg(void);
void service_bridge_hbt_msg(void);
bool hbt_sync_from_all_node(void);

bool transmit_heartbeat_on_can(void);

void master_send_debug_msg(void);



#ifdef __cplusplus
}
#endif

#endif /* MASTER_H_ */
