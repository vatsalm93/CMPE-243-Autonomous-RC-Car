/*
 * can_lcd.c
 *
 *  Created on: Apr 23, 2019
 *      Author: Jay
 */
#include "can_receive.h"
#include "printf_lib.h"

#define TIMEOUT_MS 0

uint8_t master_status, sensor_status, gps_status, bridge_status;

const uint32_t                             BRIDGE_NODE__MIA_MS = 3000;
const BRIDGE_NODE_t                        BRIDGE_NODE__MIA_MSG = { 0 };
const uint32_t                             SENSOR_NODE__MIA_MS = 3000;
const SENSOR_NODE_t                        SENSOR_NODE__MIA_MSG = {0};
const uint32_t                             GPS_LOCATION__MIA_MS = 3000;
const GPS_LOCATION_t                       GPS_LOCATION__MIA_MSG = {0};
const uint32_t                             COMPASS__MIA_MS = 3000;
const COMPASS_t                            COMPASS__MIA_MSG = {0};
const uint32_t                             MASTER_HEARTBEAT__MIA_MS = 3000;
const MASTER_HEARTBEAT_t                   MASTER_HEARTBEAT__MIA_MSG = {0};
const uint32_t                             CAR_CONTROL__MIA_MS = 3000;
const CAR_CONTROL_t                        CAR_CONTROL__MIA_MSG = { MOTOR_STOP, 30, 0, { 0 } };

bool receive_can_msg(void){
    can_msg_t can_motor_msg;
    dbc_msg_hdr_t can_msg_hdr;
    BRIDGE_NODE_t bridge_msg = {0};
    SENSOR_NODE_t sensor_msg = {0};
    GPS_LOCATION_t gps_msg = {0};
    COMPASS_t compass_msg = {0};
    bool motor_rx_flag = false;
    while (CAN_rx(can1, &can_motor_msg, TIMEOUT_MS))
    {
        can_msg_hdr.dlc = can_motor_msg.frame_fields.data_len;
        can_msg_hdr.mid = can_motor_msg.msg_id;
        uint32_t mid = can_motor_msg.msg_id;

        switch (mid)
        {
            case 103: // Bridge
                dbc_decode_BRIDGE_NODE(&bridge_msg, can_motor_msg.data.bytes, &can_msg_hdr);
                bridge_status = 1;
                break;
            case 104: //Master Node
                dbc_decode_CAR_CONTROL(&drive, can_motor_msg.data.bytes, &can_msg_hdr);
                setLED(1, 0);
                break;
            case 105: // Sensor Node
                dbc_decode_SENSOR_NODE(&sensor_msg, can_motor_msg.data.bytes, &can_msg_hdr);
                led_digit_front_obs =  sensor_msg.LIDAR_Obstacle_FRONT;
                led_digit_left_obs =  sensor_msg.LIDAR_Obstacle_LEFT;
                led_digit_back_obs =  sensor_msg.LIDAR_Obstacle_BACK;
                led_digit_right_obs =  sensor_msg.LIDAR_Obstacle_RIGHT;
                sensor_status = 1;
                break;
            case 108: // GPS
                dbc_decode_GPS_LOCATION(&gps_msg, can_motor_msg.data.bytes, &can_msg_hdr);
                gps_latitude = gps_msg.CURRENT_LAT_deg;
                gps_longitude = gps_msg.CURRENT_LONG_deg;
                gps_status = 1;
                break;
            case 109: // Compass
                dbc_decode_COMPASS(&compass_msg, can_motor_msg.data.bytes, &can_msg_hdr);
                gps_bearing = compass_msg.CMP_BEARING_deg;
                break;
        }
    }

    if(dbc_handle_mia_SENSOR_NODE(&sensor_msg, 100))
        sensor_status = 0;
    if (dbc_handle_mia_CAR_CONTROL(&drive, 100)) {
        drive.MOTOR_DRIVE_cmd = 2;
        drive.MOTOR_STEER_cmd = 2;
        setLED(1, 1);
    }
    if(dbc_handle_mia_GPS_LOCATION(&gps_msg, 100))
        gps_status = 0;
    if(dbc_handle_mia_BRIDGE_NODE(&bridge_msg, 100))
        bridge_status = 0;
    return motor_rx_flag;
}

