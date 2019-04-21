/*
 * can_tx.c
 *
 *  Created on: Mar 3, 2019
 *      Author: Vidushi
 */

#include "can.h"
#include "stdio.h"
#include "_can_dbc/generated_can.h"
#include "can_code/can_tx.h"
#include "c_io.h"
#include "compass.h"

can_msg_t msg;

#define CAN_BAUDRATE    100
#define TX_SIZE_DATA    100
#define RX_SIZE_DATA    100

bool can_init(void)
{
    bool val;

    if(CAN_init(can1, CAN_BAUDRATE, RX_SIZE_DATA, TX_SIZE_DATA, NULL, NULL)) {
        CAN_reset_bus(can1);
        val=true;
    }
    else {
        val = false;
    }

    return val;
}

bool transmit_gps_data_on_can(void){
    GPS_LOCATION_t gps_cmd = {0};
    gps_cmd.CURRENT_LAT_deg = 37.3686485291;
    gps_cmd.CURRENT_LONG_deg = -121.915328979;

    can_msg_t can_msg = { 0 };

    // Encode the CAN message's data bytes, get its header and set the CAN message's DLC and length
    dbc_msg_hdr_t msg_hdr = dbc_encode_GPS_LOCATION(can_msg.data.bytes, &gps_cmd);
    can_msg.msg_id = msg_hdr.mid;
    can_msg.frame_fields.data_len = msg_hdr.dlc;

    for (int i = 0; i < can_msg.frame_fields.data_len; i++) {
                    printf("%#2X, ", can_msg.data.bytes[i]);
    }

    // Queue the CAN message to be sent out
    return (CAN_tx(can1, &can_msg, 0));
}

bool transmit_compass_data_on_can(void)
{
    COMPASS_t compass_msg = {0};
    can_msg_t can_msg = { 0 };

    float compass_Bearing_value = Compass_Get_Bearing_Angle();
//    printf("Compass heading = %f\n", compass_heading_value);
    compass_msg.CMP_BEARING_deg = compass_Bearing_value;

    dbc_msg_hdr_t msg_hdr = dbc_encode_COMPASS(can_msg.data.bytes, &compass_msg);
    can_msg.msg_id = msg_hdr.mid;
    can_msg.frame_fields.data_len = msg_hdr.dlc;

    // Queue the CAN message to be sent out
    return (CAN_tx(can1, &can_msg, 0));
}

bool transmit_heartbeat_on_can(void)
{
    GPS_HEARTBEAT_t heartbeat_msg = {0};
    can_msg_t can_msg = { 0 };

    heartbeat_msg.GPS_hbt = GPS_HEART_BEAT;

    dbc_msg_hdr_t msg_hdr = dbc_encode_GPS_HEARTBEAT(can_msg.data.bytes, &heartbeat_msg);
    can_msg.msg_id = msg_hdr.mid;
    can_msg.frame_fields.data_len = msg_hdr.dlc;

    setLED(4,1);
    // Queue the CAN message to be sent out
    return (CAN_tx(can1, &can_msg, 0));
}


void check_bus_off(void){
    if(CAN_is_bus_off(can1)){
        CAN_reset_bus(can1);
        CAN_bypass_filter_accept_all_msgs();
    }
}
