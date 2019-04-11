/*
 * master.cpp
 *
 *  Created on: Apr 4, 2019
 *      Author: Aakash
 */
#include "master.h"
#include "can.h"
#include "_can_dbc/generated_can.h"
#include "c_io.h"

static BRIDGE_NODE_t bridge_data = {0, {0}};
static SENSOR_NODE_t sensor_data = {OBSTACLE_NEAR, 0, 0, {0}};
static GPS_LOCATION_t gps_data = {0, 0, {0}};
static COMPASS_t compass_data = {0};

const uint32_t                             BRIDGE_NODE__MIA_MS = 3000;
const BRIDGE_NODE_t                        BRIDGE_NODE__MIA_MSG = { 1, {0} };
const uint32_t                             SENSOR_NODE__MIA_MS = 3000;
const SENSOR_NODE_t                        SENSOR_NODE__MIA_MSG = { OBSTACLE_NEAR,0,0,{0} };
const uint32_t                             GPS_LOCATION__MIA_MS = 3000;
const GPS_LOCATION_t                       GPS_LOCATION__MIA_MSG = { 37.3686485, -121.9153289, {0} };
const uint32_t                             COMPASS__MIA_MS = 3000;
const COMPASS_t                            COMPASS__MIA_MSG = { 37.3686485, -121.9153289, {0} };

static can_msg_t can_msg;
static dbc_msg_hdr_t can_msg_hdr;

void master_controller_init(void)
{
    bool status = false;
    do {
        status = CAN_init(MASTER_CAN_BUS, MASTER_BAUD_RATE, MASTER_RX_Q, MASTER_TX_Q, 0, 0);
    } while(false == status);


    CAN_bypass_filter_accept_all_msgs();
    CAN_reset_bus(MASTER_CAN_BUS);
}

bool power_up_and_sync(void)
{
    return true;
}

bool master_avoid_obstacle(void)
{
    return true;
}

void master_service_can_msgs(void)
{
    while(CAN_rx(MASTER_CAN_BUS, &can_msg, 0))
    {
        // Form the message header from the metadata of the arriving message
        can_msg_hdr.dlc = can_msg.frame_fields.data_len;
        can_msg_hdr.mid = can_msg.msg_id;
        switch(can_msg_hdr.mid){
            case BRIDGE_NODE:
                service_bridge_msg();
                break;
            case SENSOR_NODE:
                service_sensor_msg();
                break;
            case GPS_LOCATION:
                service_gps_msg();
                break;
            case COMPASS:
                service_compass_msg();
                break;
            default: break;
        }
    }

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
}

void service_bridge_msg(void)
{
    dbc_decode_BRIDGE_NODE(&bridge_data, can_msg.data.bytes, &can_msg_hdr);
    setLED(1,false);
}

void service_sensor_msg(void)
{
    dbc_decode_SENSOR_NODE(&sensor_data, can_msg.data.bytes, &can_msg_hdr);
    setLED(2,false);
}

void service_gps_msg(void)
{
    dbc_decode_GPS_LOCATION(&gps_data, can_msg.data.bytes, &can_msg_hdr);
    setLED(3, false);
}

void service_compass_msg(void)
{
    dbc_decode_COMPASS(&compass_data, can_msg.data.bytes, &can_msg_hdr);
    setLED(4, false);
}

void master_send_command_to_motor_module(void)
{
    MOTOR_NODE_t motor_data;
    dbc_msg_hdr_t msg_hdr_tx = {0};
    if (sensor_data.SENSOR_FRONT_OBSTACLE_TYPE == NO_OBSTACLE)
    {
        motor_data.MOTOR_DRIVE_CMD = MOTOR_FWD_FAST;
        motor_data.MOTOR_STEER_CMD = MOTOR_DONT_STEER;
    }
    else if (sensor_data.SENSOR_FRONT_OBSTACLE_TYPE == OBSTACLE_NEAR)
    {
        motor_data.MOTOR_DRIVE_CMD = MOTOR_FWD_SLOW;
        motor_data.MOTOR_STEER_CMD = MOTOR_STEER_FULL_LEFT;
    }
    else if (sensor_data.SENSOR_FRONT_OBSTACLE_TYPE == OBSTACLE_FAR)
    {
        motor_data.MOTOR_DRIVE_CMD = MOTOR_FWD_MED;
        motor_data.MOTOR_STEER_CMD = MOTOR_STEER_SLIGHT_RIGHT;
    }
    else
    {
        motor_data.MOTOR_DRIVE_CMD = MOTOR_STOP;
        motor_data.MOTOR_STEER_CMD = MOTOR_DONT_STEER;
    }

    msg_hdr_tx = dbc_encode_MOTOR_NODE(can_msg.data.bytes,&motor_data);
    can_msg.msg_id = msg_hdr_tx.mid;
    can_msg.frame_fields.data_len = msg_hdr_tx.dlc;
    CAN_tx(MASTER_CAN_BUS, &can_msg, 0);
}

bool master_CAN_turn_on_bus_if_bus_off(void)
{
    if (CAN_is_bus_off(MASTER_CAN_BUS))
    {
        CAN_bypass_filter_accept_all_msgs();
        CAN_reset_bus(MASTER_CAN_BUS);
        return true;
    }
    return false;
}
