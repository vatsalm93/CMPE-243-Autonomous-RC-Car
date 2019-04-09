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

bool can_init(void);
bool transmit_dbc_data_on_can(void);
void check_bus_off(void);


#endif /* CAN_TX_H_ */
