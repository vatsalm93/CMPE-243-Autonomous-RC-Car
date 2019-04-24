/*
 * can_lcd.h
 *
 *  Created on: Apr 23, 2019
 *      Author: Jay
 */

#ifndef CAN_LCD_H_
#define CAN_LCD_H_

#include "can.h"
#include "c_io.h"
#include "speed_calculator.h"
#include "generated_can.h"


#ifdef __cplusplus
extern "C" {
#endif

char led_digit_front_obs;
char led_digit_left_obs;
char led_digit_right_obs;
char led_digit_back_obs;

float gps_latitude;
float gps_longitude;
float gps_bearing;
float gps_distance;

uint8_t master_status, sensor_status, gps_status, bridge_status;

const uint32_t                             BRIDGE_NODE__MIA_MS;
const BRIDGE_NODE_t                        BRIDGE_NODE__MIA_MSG;
const uint32_t                             SENSOR_NODE__MIA_MS;
const SENSOR_NODE_t                        SENSOR_NODE__MIA_MSG;
const uint32_t                             GPS_LOCATION__MIA_MS;
const GPS_LOCATION_t                       GPS_LOCATION__MIA_MSG;
const uint32_t                             COMPASS__MIA_MS;
const COMPASS_t                            COMPASS__MIA_MSG;
const uint32_t                             MASTER_HEARTBEAT__MIA_MS;
const MASTER_HEARTBEAT_t                   MASTER_HEARTBEAT__MIA_MSG;

bool receive_can_msg(void);

#ifdef __cplusplus
}
#endif

#endif /* CAN_LCD_H_ */
