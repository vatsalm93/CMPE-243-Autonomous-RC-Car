/*
 * Sensor_CAN_Interfacing.cpp
 *
 *  Created on: Apr 14, 2019
 *      Author: halak
 */

#include <stdint.h>
#include <stdbool.h>
#include "Lidar_includes/Sensor_CAN_Interfacing.h"
#include "can.h"
#include "Lidar_includes/RPLidar.h"
#include "_can_dbc/generated_can.h"
#include "Lidar_includes/ultrasonic_sensor.h"
#include "printf_lib.h"
#include "c_code/c_io.h"

#define SENSOR_CAN_BUS      can1
#define SENSOR_BAUD_RATE    100
#define SENSOR_RX_Q         10
#define SENSOR_TX_Q         10

extern SENSOR_NODE_t sensor_cmd;
extern sensor_lv_max_sonar_t send_ultrasonic_data;
static SENSOR_DEBUG_t debug_msg;

bool sensor_can_init()
{
    bool status = false;
    do {
        status = CAN_init(SENSOR_CAN_BUS, SENSOR_BAUD_RATE, SENSOR_RX_Q, SENSOR_TX_Q, 0, 0);
    } while (status == false);

    CAN_reset_bus(SENSOR_CAN_BUS);

    debug_msg.IO_DEBUG_CAN_init = status;
    return status;
}

bool sensor_send_data(RPLidarRotation *singleRotation)
{
    sensor_cmd.SENSOR_FRONT_cm = send_ultrasonic_data.distance;

    can_msg_t can_msg = {0};
    dbc_msg_hdr_t can_msg_hdr = dbc_encode_SENSOR_NODE(can_msg.data.bytes, &sensor_cmd);
    can_msg.msg_id = can_msg_hdr.mid;
    can_msg.frame_fields.data_len = can_msg_hdr.dlc;
    bool flag = CAN_tx(SENSOR_CAN_BUS, &can_msg, 0);
    debug_msg.IO_DEBUG_CAN_TX = flag;
    return flag;
}

bool transmit_heartbeat_on_can(void)
{
    SENSOR_HEARTBEAT_t heartbeat_msg = {0};
    can_msg_t can_msg = { 0 };

    heartbeat_msg.SENSOR_hbt = 1;

    dbc_msg_hdr_t msg_hdr = dbc_encode_SENSOR_HEARTBEAT(can_msg.data.bytes, &heartbeat_msg);
    can_msg.msg_id = msg_hdr.mid;
    can_msg.frame_fields.data_len = msg_hdr.dlc;

    setLED(4,1);
    // Queue the CAN message to be sent out
    return (CAN_tx(can1, &can_msg, 0));
}

bool sensor_CAN_turn_on_bus_if_bus_off()
{
    bool flag = CAN_is_bus_off(SENSOR_CAN_BUS);
    debug_msg.IO_DEBUG_bus_off = flag;
    if (flag)
    {
        CAN_bypass_filter_accept_all_msgs();
        CAN_reset_bus(SENSOR_CAN_BUS);
        return true;
    }
    return false;
}

bool send_sensor_debug_msg()
{
    can_msg_t can_msg = { 0 };
    dbc_msg_hdr_t msg_hdr = dbc_encode_SENSOR_DEBUG(can_msg.data.bytes, &debug_msg);
    can_msg.msg_id = msg_hdr.mid;
    can_msg.frame_fields.data_len = msg_hdr.dlc;

        // Queue the CAN message to be sent out
   return (CAN_tx(can1, &can_msg, 0));
}
