/*
 * master.cpp
 *
 *  Created on: Apr 4, 2019
 *      Author: Aakash
 */
#include "can.h"
#include "../../_can_dbc/generated_can.h"
#include "c_code/defines.h"
#include "c_code/bridge.h"
#include "c_code/sensor.h"
#include "c_code/gps.h"
#include "c_code/master.h"
#include "c_code/structures.h"
#include "c_code/compass.h"
#include "c_code/motor.h"
#include "c_code/c_io.h"
#include <stdio.h>

BRIDGE_NODE_t bridge_data = {0, {0}};
SENSOR_NODE_t sensor_data = {0};
GPS_LOCATION_t gps_data = {0, 0, {0}};
COMPASS_t compass_data = {0};
CAR_CONTROL_t car_control = { 0 };
SENSOR_HEARTBEAT_t sensor_hbt = {0};
MOTOR_HEARTBEAT_t motor_hbt = {0};
GPS_HEARTBEAT_t gps_hbt = {0};
BRIDGE_HEARTBEAT_t bridge_hbt = {0};

can_msg_t can_msg;
dbc_msg_hdr_t can_msg_hdr;

const uint32_t                             BRIDGE_NODE__MIA_MS = 3000;
const BRIDGE_NODE_t                        BRIDGE_NODE__MIA_MSG = { 0, {0} };
const uint32_t                             SENSOR_NODE__MIA_MS = 3000;
const SENSOR_NODE_t                        SENSOR_NODE__MIA_MSG = { 0 };
const uint32_t                             GPS_LOCATION__MIA_MS = 3000;
const GPS_LOCATION_t                       GPS_LOCATION__MIA_MSG = { 37.3686485, -121.9153289, {0} };
const uint32_t                             COMPASS__MIA_MS = 3000;
const COMPASS_t                            COMPASS__MIA_MSG = { 37.3686485, -121.9153289, {0} };
const uint32_t                             SENSOR_HEARTBEAT__MIA_MS = 5000;
const SENSOR_HEARTBEAT_t                   SENSOR_HEARTBEAT__MIA_MSG = {0, {0}};
const uint32_t                             MOTOR_HEARTBEAT__MIA_MS = 5000;
const MOTOR_HEARTBEAT_t                    MOTOR_HEARTBEAT__MIA_MSG = {0, {0}};
const uint32_t                             GPS_HEARTBEAT__MIA_MS = 5000;
const GPS_HEARTBEAT_t                      GPS_HEARTBEAT__MIA_MSG = {0, {0}};
const uint32_t                             BRIDGE_HEARTBEAT__MIA_MS = 5000;
const BRIDGE_HEARTBEAT_t                   BRIDGE_HEARTBEAT__MIA_MSG = {0, {0}};

bool start_cmd = false;
bool sensor_hbt_sync = false;
bool motor_hbt_sync = false;
bool gps_hbt_sync = false;
bool bridge_hbt_sync = false;

bool can_init_flag = false;
bool bus_off_flag = false;

bool start_free_run_flag = false;
bool free_run_motor_flag = false;
bool free_steer_flag = false;
bool check_rear_obstacle = false;

void master_controller_init(void)
{
    do {
        can_init_flag = CAN_init(CAN_BUS, CAN_BAUD_RATE, CAN_RX_QUEUE_SIZE, CAN_TX_QUEUE_SIZE, 0, 0);
    } while(false == can_init_flag);

    CAN_bypass_filter_accept_all_msgs();
    CAN_reset_bus(CAN_BUS);
}

void start_obstacle_avoidance()
{
    uint16_t front_sensor = sensor_data.SENSOR_FRONT_cm;
//    uint8_t obs_front = sensor_data.LIDAR_Obstacle_FRONT;
    uint8_t obs_left = sensor_data.LIDAR_Obstacle_LEFT;
    uint8_t obs_right = sensor_data.LIDAR_Obstacle_RIGHT;
    uint8_t obs_back = sensor_data.LIDAR_Obstacle_BACK;

    // no obstacle
    if ((obs_left >= OBSTACLE_TRACK_THRESHOLD) && (obs_right >= OBSTACLE_TRACK_THRESHOLD)
            && (front_sensor >= ULTRASONIC_THRESHOLD))
    {
        drive_motor_fwd_med();
        master_dont_steer();
        check_rear_obstacle = false;
    }
    // only front obstacle
    else if ((obs_left >= OBSTACLE_TRACK_THRESHOLD) && (obs_right >= OBSTACLE_TRACK_THRESHOLD)
            && (front_sensor < ULTRASONIC_THRESHOLD))
    {
        drive_motor_fwd_slow();
        if ((obs_left < obs_right))
        {
            master_steer_full_right();
        }
        else if ((obs_left > obs_right))
        {
            master_steer_full_left();
        }
        else
        {
            master_steer_full_left();
        }
        check_rear_obstacle = false;
    }
    // only left obstacle
    else if ((obs_left < OBSTACLE_TRACK_THRESHOLD) && (obs_right >= OBSTACLE_TRACK_THRESHOLD)
            && (front_sensor >= ULTRASONIC_THRESHOLD))
    {
        drive_motor_fwd_slow();
        master_steer_slight_right();
        check_rear_obstacle = false;
    }
    // only right obstacle
    else if ((obs_left >= OBSTACLE_TRACK_THRESHOLD) && (obs_right < OBSTACLE_TRACK_THRESHOLD)
            && (front_sensor >= ULTRASONIC_THRESHOLD))
    {
        drive_motor_fwd_slow();
        master_steer_slight_left();
        check_rear_obstacle = false;
    }
    // front and left obstacle
    else if ((obs_left < OBSTACLE_TRACK_THRESHOLD) && (obs_right >= OBSTACLE_TRACK_THRESHOLD)
            && (front_sensor < ULTRASONIC_THRESHOLD))
    {
        drive_motor_fwd_slow();
        master_steer_full_right();
        check_rear_obstacle = false;
    }
    // front and right obstacle
    else if ((obs_left >= OBSTACLE_TRACK_THRESHOLD) && (obs_right < OBSTACLE_TRACK_THRESHOLD)
            && (front_sensor < ULTRASONIC_THRESHOLD))
    {
        drive_motor_fwd_slow();
        master_steer_full_left();
        check_rear_obstacle = false;
    }
    // left and right obstacle
    else if ((obs_left < OBSTACLE_TRACK_THRESHOLD) && (obs_right < OBSTACLE_TRACK_THRESHOLD)
            && (front_sensor >= ULTRASONIC_THRESHOLD))
    {
        if ((obs_left < obs_right))
        {
            drive_motor_fwd_slow();
            master_steer_slight_right();
        }
        else if ((obs_left > obs_right))
        {
            drive_motor_fwd_slow();
            master_steer_slight_left();
        }
        else
        {
            drive_motor_fwd_slow();
            master_dont_steer();
        }
        check_rear_obstacle = false;
    }
    // left, right and front obstacle
    else if ((obs_left < OBSTACLE_TRACK_THRESHOLD) && (obs_right < OBSTACLE_TRACK_THRESHOLD)
            && (front_sensor < ULTRASONIC_THRESHOLD) && (!check_rear_obstacle))
    {
        drive_motor_stop();
        master_dont_steer();
        check_rear_obstacle = true;
    }
    // If left, front and right have obstacle;
    // check for rear obstacle
    else if (check_rear_obstacle)
    {
        if (obs_back < OBSTACLE_TRACK_THRESHOLD - 1)
        {
            drive_motor_stop();
            master_dont_steer();
        }
        else
        {
            drive_motor_rev_slow();
            master_dont_steer();
        }
    }
}

void master_service_can_msgs(void)
{
    while(CAN_rx(CAN_BUS, &can_msg, 0))
    {
        // Form the message header from the metadata of the arriving message
        can_msg_hdr.dlc = can_msg.frame_fields.data_len;
        can_msg_hdr.mid = can_msg.msg_id;
        switch(can_msg_hdr.mid){
            case BRIDGE_MID:
                service_bridge_msg();
                break;
            case SENSOR_MID:
                service_sensor_msg();
                break;
            case GPS_LOCATION_MID:
                service_gps_msg();
                break;
            case COMPASS_MID:
                service_compass_msg();
                break;
            case SENSOR_HEARTBEAT_MID:
                service_sensor_hbt_msg();
                break;
            case MOTOR_HEARTBEAT_MID:
                service_motor_hbt_msg();
                break;
            case GPS_HEARTBEAT_MID:
                service_gps_hbt_msg();
                break;
            case BRIDGE_HEARTBEAT_MID:
                service_bridge_hbt_msg();
                break;
            default: break;
        }
    }
    master_mia_handler();
}

void master_mia_handler(void)
{
    if (dbc_handle_mia_BRIDGE_NODE(&bridge_data, 100))
    {
        setLED(1, true);
    }
    if (dbc_handle_mia_SENSOR_NODE(&sensor_data, 100))
    {
        setLED(2, true);
    }
    if (dbc_handle_mia_GPS_LOCATION(&gps_data, 100))
    {
        setLED(3, true);
    }
    if (dbc_handle_mia_COMPASS(&compass_data, 100))
    {
        setLED(4, true);
    }
    if (dbc_handle_mia_SENSOR_HEARTBEAT(&sensor_hbt, 50))
    {
        sensor_hbt_sync = false;
    }
    if (dbc_handle_mia_MOTOR_HEARTBEAT(&motor_hbt, 50))
    {
        motor_hbt_sync = false;
    }
    if (dbc_handle_mia_GPS_HEARTBEAT(&gps_hbt, 50))
    {
        gps_hbt_sync = false;
    }
    if (dbc_handle_mia_BRIDGE_HEARTBEAT(&bridge_hbt, 50))
    {
        bridge_hbt_sync = false;
    }
}

bool hbt_sync_from_all_node(void)
{
    return (sensor_hbt_sync & motor_hbt_sync & gps_hbt_sync & bridge_hbt_sync);
}

void master_send_command_to_motor_module(void)
{
    dbc_msg_hdr_t msg_hdr_tx = {0};
    msg_hdr_tx = dbc_encode_CAR_CONTROL(can_msg.data.bytes,&car_control);
    can_msg.msg_id = msg_hdr_tx.mid;
    can_msg.frame_fields.data_len = msg_hdr_tx.dlc;
    CAN_tx(CAN_BUS, &can_msg, 0);
}

bool master_CAN_turn_on_bus_if_bus_off(void)
{
    if (CAN_is_bus_off(CAN_BUS))
    {
        bus_off_flag = true;
        CAN_bypass_filter_accept_all_msgs();
        CAN_reset_bus(CAN_BUS);
        return true;
    }
    bus_off_flag = false;
    return false;
}

bool sys_start_stop_cmd()
{
    return start_cmd;
}

bool transmit_heartbeat_on_can(void)
{
    MASTER_HEARTBEAT_t heartbeat_msg = { 0 };
    heartbeat_msg.MASTER_hbt = HEART_BEAT_cmd;
    dbc_msg_hdr_t msg_hdr = dbc_encode_MASTER_HEARTBEAT(can_msg.data.bytes, &heartbeat_msg);
    can_msg.msg_id = msg_hdr.mid;
    can_msg.frame_fields.data_len = msg_hdr.dlc;
    // Queue the CAN message to be sent out
    return (CAN_tx(CAN_BUS, &can_msg, 0));
}

void master_send_debug_msg(void)
{
    MASTER_DEBUG_t master_dbg_msg = {0};
    master_dbg_msg.IO_DEBUG_CAN_init = can_init_flag;
    master_dbg_msg.IO_DEBUG_HBT_FROM_ALL_CONTR = hbt_sync_from_all_node();
    master_dbg_msg.IO_DEBUG_drive_mode = start_free_run_flag;
    master_dbg_msg.IO_DEBUG_bus_off = bus_off_flag;

    dbc_msg_hdr_t msg_hdr = dbc_encode_MASTER_DEBUG(can_msg.data.bytes, &master_dbg_msg);
    can_msg.msg_id = msg_hdr.mid;
    can_msg.frame_fields.data_len = msg_hdr.dlc;
    // Queue the CAN message to be sent out
    CAN_tx(CAN_BUS, &can_msg, 0);
}
