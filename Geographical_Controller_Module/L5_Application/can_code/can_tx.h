/*
 * can_tx.h
 *
 *  Created on: Mar 10, 2019
 *      Author: Vidushi
 */

#ifndef CAN_TX_H_
#define CAN_TX_H_

#include <stdint.h>
#include <stdbool.h>

#define GPS_HEART_BEAT 1

bool can_init(void);
bool transmit_dbc_data_on_can(void);
void check_bus_off(void);
bool transmit_compass_data_on_can(void);
bool transmit_gps_data_on_can(void);
bool transmit_heartbeat_on_can(void);
bool transmit_debug_data_on_can(void);
void can_receive(void);

#endif /* CAN_TX_H_ */
