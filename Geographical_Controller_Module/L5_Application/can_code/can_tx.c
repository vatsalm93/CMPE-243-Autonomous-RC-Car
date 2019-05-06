/*
 * can_tx.c
 *
 *  Created on: Mar 3, 2019
 *      Author: Vidushi
 */

#include "can.h"
#include <stdio.h>
#include <stdbool.h>
#include "generated_can.h"
#include "can_tx.h"
#include "gps.h"
#include "c_io.h"
#include "compass.h"

can_msg_t msg;

#define CAN_BAUDRATE    100
#define TX_SIZE_DATA    100
#define RX_SIZE_DATA    100

GPS_DEBUG_t debug_cmd = {0};
static bool setHeartbeat = false;
static float checkpoint_lat = 0.0;
static float checkpoint_long = 0.0;
BRIDGE_CHECKPOINTS_t startLoc = {0};
MASTER_HEARTBEAT_t heartbeat = {0};

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

    debug_cmd.IO_DEBUG_CAN_init = (char)val;
    return val;
}

bool transmit_gps_data_on_can(void)
{
   // if(setHeartbeat)
    {
        GPS_LOCATION_t gps_cmd = {0};
        gps_cmd.CURRENT_LAT_deg = getLatitude();
        gps_cmd.CURRENT_LONG_deg = getLongitude();

        if(gps_cmd.CURRENT_LAT_deg == 0.0) {
            debug_cmd.IO_DEBUG_GPS_Fix = 1;
            debug_cmd.IO_DEBUG_GPS_rx = 1;
        }
        else {
            debug_cmd.IO_DEBUG_GPS_Fix = 0;
            debug_cmd.IO_DEBUG_GPS_rx = 0;
        }

        can_msg_t can_msg = { 0 };

        // Encode the CAN message's data bytes, get its header and set the CAN message's DLC and length
        dbc_msg_hdr_t msg_hdr = dbc_encode_GPS_LOCATION(can_msg.data.bytes, &gps_cmd);
        can_msg.msg_id = msg_hdr.mid;
        can_msg.frame_fields.data_len = msg_hdr.dlc;

        // Queue the CAN message to be sent out
        return (CAN_tx(can1, &can_msg, 0));
    }
}

bool transmit_compass_data_on_can(void)
{
  // if(setHeartbeat)
    COMPASS_t compass_msg = {0};
    can_msg_t can_msg = { 0 };

    float compass_Bearing_value = Compass_Get_Bearing_Angle();
    float Heading_value = HeadingAngle(checkpoint_lat, checkpoint_long);

    if(compass_Bearing_value == 0.0)
        debug_cmd.IO_DEBUG_Compass_Rx = 1;
    else
        debug_cmd.IO_DEBUG_Compass_Rx = 0;

    compass_msg.CMP_BEARING_deg = compass_Bearing_value;
    compass_msg.CMP_HEADING_deg = Heading_value;

 /*   float deflection_angle = Heading_value - compass_Bearing_value;
    if (deflection_angle > 180)
    {
        deflection_angle -= 360;
    }
    else if (deflection_angle < -180)
    {
        deflection_angle += 360;
    }*/

    float distance = calcDistance(checkpoint_lat, checkpoint_long);
    //    printf("Distance to checkpoint = %f\n", distance_to_checkpoint);
    compass_msg.CMP_DISTANCE_meters = distance;

    dbc_msg_hdr_t msg_hdr = dbc_encode_COMPASS(can_msg.data.bytes, &compass_msg);
    can_msg.msg_id = msg_hdr.mid;
    can_msg.frame_fields.data_len = msg_hdr.dlc;

    // Queue the CAN message to be sent out
    return (CAN_tx(can1, &can_msg, 0));
}

bool transmit_debug_data_on_can(void){
    can_msg_t can_msg = { 0 };

    // Encode the CAN message's data bytes, get its header and set the CAN message's DLC and length
    dbc_msg_hdr_t msg_hdr = dbc_encode_GPS_DEBUG(can_msg.data.bytes, &debug_cmd);
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

   // setLED(4,1);

    debug_cmd.IO_DEBUG_HBT_Transmit = (char)CAN_tx(can1, &can_msg, 0);
    // Queue the CAN message to be sent out
    return ((bool)debug_cmd.IO_DEBUG_HBT_Transmit);
}

void can_receive(void)
{
    can_msg_t can_msg;

    while(CAN_rx(can1, &can_msg, 0))
    {
        dbc_msg_hdr_t msg_hdr_receive;
        msg_hdr_receive.mid = can_msg.msg_id;
        msg_hdr_receive.dlc = can_msg.frame_fields.data_len;

        switch(can_msg.msg_id)
        {
            case 110:
               dbc_decode_MASTER_HEARTBEAT(&heartbeat, can_msg.data.bytes, &msg_hdr_receive);
                   if(heartbeat.MASTER_hbt == 1)
                   {
                       setHeartbeat = true;
                       setLED(4,1);
                   }
                   else if(heartbeat.MASTER_hbt == 1)
                   {
                       setHeartbeat = false;
                       setLED(4,0);
                   }
               break;

            case 107:
                dbc_decode_BRIDGE_CHECKPOINTS(&startLoc, can_msg.data.bytes, &msg_hdr_receive);
                checkpoint_lat = startLoc.CHECKPOINT_LAT_deg;
                checkpoint_long = startLoc.CHECKPOINT_LONG_deg;
                break;
        }
    }
}

void check_bus_off(void){
    if(CAN_is_bus_off(can1)){
        debug_cmd.IO_DEBUG_bus_off = 1;
        CAN_reset_bus(can1);
        CAN_bypass_filter_accept_all_msgs();
    }
    else
        debug_cmd.IO_DEBUG_bus_off = 0;
}
