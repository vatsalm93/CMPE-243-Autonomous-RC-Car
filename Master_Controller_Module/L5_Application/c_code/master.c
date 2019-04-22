/*
 * master.cpp
 *
 *  Created on: Apr 4, 2019
 *      Author: Aakash
 */
#include "can.h"
#include "c_code/externs.h"
#include "c_code/defines.h"
#include "c_code/bridge.h"
#include "c_code/sensor.h"
#include "c_code/gps.h"
#include "c_code/master.h"
#include "c_code/structures.h"
#include "c_code/compass.h"
#include "c_code/c_io.h"

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
const BRIDGE_NODE_t                        BRIDGE_NODE__MIA_MSG = { 1, {0} };
const uint32_t                             SENSOR_NODE__MIA_MS = 3000;
const SENSOR_NODE_t                        SENSOR_NODE__MIA_MSG = { 0 };
const uint32_t                             GPS_LOCATION__MIA_MS = 3000;
const GPS_LOCATION_t                       GPS_LOCATION__MIA_MSG = { 37.3686485, -121.9153289, {0} };
const uint32_t                             COMPASS__MIA_MS = 3000;
const COMPASS_t                            COMPASS__MIA_MSG = { 37.3686485, -121.9153289, {0} };
const uint32_t                             SENSOR_HEARTBEAT__MIA_MS = 2000;
const SENSOR_HEARTBEAT_t                   SENSOR_HEARTBEAT__MIA_MSG = {0, {0}};
const uint32_t                             MOTOR_HEARTBEAT__MIA_MS = 2000;
const MOTOR_HEARTBEAT_t                    MOTOR_HEARTBEAT__MIA_MSG = {0, {0}};
const uint32_t                             GPS_HEARTBEAT__MIA_MS = 2000;
const GPS_HEARTBEAT_t                      GPS_HEARTBEAT__MIA_MSG = {0, {0}};
const uint32_t                             BRIDGE_HEARTBEAT__MIA_MS = 2000;
const BRIDGE_HEARTBEAT_t                   BRIDGE_HEARTBEAT__MIA_MSG = {0, {0}};

bool start_cmd = false;
bool sensor_hbt_sync = false;
bool motor_hbt_sync = false;
bool gps_hbt_sync = false;
bool bridge_hbt_sync = false;

void master_controller_init(void)
{
    bool status = false;
    do {
        status = CAN_init(CAN_BUS, CAN_BAUD_RATE, 10, 10, 0, 0);
    } while(false == status);

    CAN_bypass_filter_accept_all_msgs();
    CAN_reset_bus(CAN_BUS);
}

void start_obstacle_detection(obstacle_detection_t *obs_detection)
{
    uint16_t front_sensor = sensor_data.SENSOR_FRONT_cm;
//    uint8_t obs_front = sensor_data.LIDAR_Obstacle_FRONT;
    uint8_t obs_left = sensor_data.LIDAR_Obstacle_LEFT;
    uint8_t obs_right = sensor_data.LIDAR_Obstacle_RIGHT;
    uint8_t obs_back = sensor_data.LIDAR_Obstacle_BACK;
    obs_detection->no_obstacle = true;
    obs_detection->front = false;
    obs_detection->frontleft = false;
    obs_detection->frontright = false;
    obs_detection->rear = false;
    obs_detection->rearleft = false;
    obs_detection->rearright = false;

    if ((obs_left < OBSTACLE_TRACK_THRESHOLD) && (obs_right > OBSTACLE_TRACK_THRESHOLD) && (front_sensor > 100))
    {
        drive_motor_fwd_slow();
        master_steer_slight_right();
    }
    else if ((obs_left > OBSTACLE_TRACK_THRESHOLD) && (obs_right < OBSTACLE_TRACK_THRESHOLD) && (front_sensor > 100))
    {
        drive_motor_fwd_slow();
        master_steer_slight_left();
    }
    else if ((obs_left < OBSTACLE_TRACK_THRESHOLD) && (obs_right > OBSTACLE_TRACK_THRESHOLD) && (front_sensor < 100))
    {
        drive_motor_fwd_slow();
        master_steer_full_right();
    }
    else if ((obs_left > OBSTACLE_TRACK_THRESHOLD) && (obs_right < OBSTACLE_TRACK_THRESHOLD) && (front_sensor < 100))
    {
        drive_motor_fwd_slow();
        master_steer_full_left();
    }
    else if ((obs_left < OBSTACLE_TRACK_THRESHOLD) && (obs_right < OBSTACLE_TRACK_THRESHOLD) && (front_sensor > 100))
    {
        drive_motor_fwd_slow();
        master_dont_steer();
    }
    else if ((obs_left < OBSTACLE_TRACK_THRESHOLD) && (obs_right < OBSTACLE_TRACK_THRESHOLD) && (front_sensor < 100))
    {
        if (obs_left < obs_right)
        {
            drive_motor_fwd_slow();
            master_steer_full_right();
        }
        else if (obs_left > obs_right)
        {
            drive_motor_fwd_slow();
            master_steer_full_left();
        }
        else
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
    else
    {
        drive_motor_fwd_med();
        master_dont_steer();
    }
#if 0
    //front obstacle
    if (((obs_front > 0) && (obs_front < OBSTACLE_TRACK_THRESHOLD)) || (front_sensor < 100))
    {
        obs_detection->no_obstacle = false;
        obs_detection->front = true;
    }

    //front-left obstacle
    if ((obs_left > 0) && (obs_left < OBSTACLE_TRACK_THRESHOLD))
    {
        obs_detection->no_obstacle = false;
        obs_detection->frontleft = true;
    }

    //front-right obstacle
    if ((obs_right > 0) && (obs_right < OBSTACLE_TRACK_THRESHOLD))
    {
        obs_detection->no_obstacle = false;
        obs_detection->frontright = true;
    }

    //Rear obstacle
    if ((obs_back > 0) && (obs_back < OBSTACLE_TRACK_THRESHOLD - 1)) // did -1 because lidar is not in center
    {
        obs_detection->no_obstacle = false;
        obs_detection->rear = true;
    }

    //front clearance check
    //for front right
    if((obs_detection->front && obs_front < CLEARANCE_TRACK_THRESHOLD) && !obs_detection->frontright)
    {
        obs_detection->frontright = true;
        obs_detection->no_obstacle = false;
    }

    if((obs_detection->front && obs_front < CLEARANCE_TRACK_THRESHOLD) && !obs_detection->frontleft)
    {
        obs_detection->frontleft = true;
        obs_detection->no_obstacle = false;
    }
#endif
}

void start_obstacle_avoidance(obstacle_detection_t obs_detected)
{
    if (obs_detected.no_obstacle == true)
    {
        car_control.MOTOR_DRIVE_cmd = MOTOR_FWD_MED;
        car_control.MOTOR_STEER_cmd = MOTOR_DONT_STEER;
    }
    else
    {
        if ((obs_detected.front == true) && (obs_detected.frontleft == true) && (obs_detected.frontright == true))
        {
            //check reverse
            if (obs_detected.rear == true)
            {
                car_control.MOTOR_DRIVE_cmd = MOTOR_STOP;
                car_control.MOTOR_STEER_cmd = MOTOR_DONT_STEER;
            }
            else
            {
                car_control.MOTOR_DRIVE_cmd = MOTOR_REV;
                car_control.MOTOR_STEER_cmd = MOTOR_DONT_STEER;
            }
        }
        else if ((obs_detected.front == true) && (obs_detected.frontleft == true))
        {
            car_control.MOTOR_DRIVE_cmd = MOTOR_FWD_SLOW;
            car_control.MOTOR_STEER_cmd = MOTOR_STEER_FULL_RIGHT;
        }
        else if ((obs_detected.front == true) && (obs_detected.frontright == true))
        {
            car_control.MOTOR_DRIVE_cmd = MOTOR_FWD_SLOW;
            car_control.MOTOR_STEER_cmd = MOTOR_STEER_FULL_LEFT;
        }
        else
        {
            if (obs_detected.frontleft == true)
            {
                car_control.MOTOR_DRIVE_cmd = MOTOR_FWD_SLOW;
                car_control.MOTOR_STEER_cmd = MOTOR_STEER_SLIGHT_RIGHT;
            }
            else if (obs_detected.frontright == true)
            {
                car_control.MOTOR_DRIVE_cmd = MOTOR_FWD_SLOW;
                car_control.MOTOR_STEER_cmd = MOTOR_STEER_SLIGHT_LEFT;
            }
            else if (obs_detected.front == true)
            {
                car_control.MOTOR_DRIVE_cmd = MOTOR_FWD_SLOW;
                car_control.MOTOR_STEER_cmd = MOTOR_STEER_FULL_RIGHT;
            }
            else
            {
                car_control.MOTOR_DRIVE_cmd = MOTOR_FWD_SLOW;
                car_control.MOTOR_STEER_cmd = MOTOR_DONT_STEER;
            }
        }
    }
}


void drive_motor_fwd_slow(void)
{
    car_control.MOTOR_DRIVE_cmd = MOTOR_FWD_SLOW;
}

void drive_motor_fwd_med(void)
{
    car_control.MOTOR_DRIVE_cmd = MOTOR_FWD_MED;
}

void drive_motor_fwd_fast(void)
{
    car_control.MOTOR_DRIVE_cmd = MOTOR_FWD_FAST;
}

void drive_motor_rev_slow(void)
{
    car_control.MOTOR_DRIVE_cmd = MOTOR_REV;
}

void drive_motor_stop(void)
{
    car_control.MOTOR_DRIVE_cmd = MOTOR_STOP;
}

void master_steer_full_left(void)
{
    car_control.MOTOR_STEER_cmd = MOTOR_STEER_FULL_LEFT;
}

void master_steer_full_right(void)
{
    car_control.MOTOR_STEER_cmd = MOTOR_STEER_FULL_RIGHT;
}

void master_steer_slight_left(void)
{
    car_control.MOTOR_STEER_cmd = MOTOR_STEER_SLIGHT_LEFT;
}

void master_steer_slight_right(void)
{
    car_control.MOTOR_STEER_cmd = MOTOR_STEER_SLIGHT_RIGHT;
}

void master_dont_steer(void)
{
    car_control.MOTOR_STEER_cmd = MOTOR_DONT_STEER;
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
    if (dbc_handle_mia_SENSOR_HEARTBEAT(&sensor_hbt, 1000))
    {
        sensor_hbt_sync = false;
    }
    if (dbc_handle_mia_MOTOR_HEARTBEAT(&motor_hbt, 1000))
    {
        motor_hbt_sync = false;
    }
    if (dbc_handle_mia_GPS_HEARTBEAT(&gps_hbt, 1000))
    {
        gps_hbt_sync = false;
    }
    if (dbc_handle_mia_BRIDGE_HEARTBEAT(&bridge_hbt, 1000))
    {
        bridge_hbt_sync = false;
    }
}

bool hbt_sync_from_all_node(void)
{
    return (sensor_hbt_sync & motor_hbt_sync & gps_hbt_sync & bridge_hbt_sync);
}

void service_motor_hbt_msg(void)
{
    dbc_decode_MOTOR_HEARTBEAT(&motor_hbt, can_msg.data.bytes, &can_msg_hdr);
    motor_hbt_sync = motor_hbt.MOTOR_hbt;
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
        CAN_bypass_filter_accept_all_msgs();
        CAN_reset_bus(CAN_BUS);
        return true;
    }
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


