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
void start_obstacle_avoidance(void);
void master_service_can_msgs(void);

bool master_CAN_turn_on_bus_if_bus_off(void);
void master_send_command_to_motor_module(void);

bool sys_start_stop_cmd(void);
void master_mia_handler(void);

bool hbt_sync_from_all_node(void);

bool transmit_heartbeat_on_can(void);

void master_send_debug_msg(void);



#ifdef __cplusplus
}
#endif

#endif /* MASTER_H_ */
