/*
 * gps.c
 *
 *  Created on: Apr 17, 2019
 *      Author: Aakash
 */
#include "includes.h"

void service_gps_msg(void)
{
    dbc_decode_GPS_LOCATION(&gps_data, can_msg.data.bytes, &can_msg_hdr);
    setLED(3, false);
}

void service_gps_hbt_msg(void)
{
    dbc_decode_GPS_HEARTBEAT(&gps_hbt, can_msg.data.bytes, &can_msg_hdr);
    gps_hbt_sync = gps_hbt.GPS_hbt;
}
