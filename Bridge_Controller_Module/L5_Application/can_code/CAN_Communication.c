#include <stdint.h>
#include "can.h"
#include <stdio.h>
#include "CAN_Communication.h"
#include <Bridge_Module/ble_hc05.h>


COMPASS_t compass_data ={0};
BRIDGE_DEBUG_t debug = {0};
const uint32_t GPS_LOCATION__MIA_MS = 3000;
const GPS_LOCATION_t GPS_LOCATION__MIA_MSG = { 0 };
const uint32_t COMPASS__MIA_MS=3000;
const COMPASS_t COMPASS__MIA_MSG={0};
BRIDGE_NODE_t start_cmd = {0};
GPS_LOCATION_t RX_data ={0};
ble_msg_t ble_param;

void CAN_Init_w(void)
{
    if(CAN_init(can1, 100, 100, 100, NULL, NULL))
    {
        CAN_bypass_filter_accept_all_msgs();
        CAN_reset_bus(can1);
        Clear_Display();
        start_cmd.BRIDGE_START_cmd = 0x0;
        debug.IO_DEBUG_CAN_init =0x00;
    }
    else
        debug.IO_DEBUG_CAN_init =0x01;

}

void CANresetAfterBusOff(void)
{
    if(CAN_is_bus_off(can1))
    {
        debug.IO_DEBUG_bus_off = 0x01;
        printf("can bus off\n");
        //CAN_bypass_filter_accept_all_msgs();
        CAN_reset_bus(can1);

    }
    else
        debug.IO_DEBUG_bus_off = 0x00;
}

void CAN_Recieve(void)
{
    can_msg_t can_msg;
    while(CAN_rx(can1, &can_msg, 0))
    {
        dbc_msg_hdr_t can_msg_hdr;
        can_msg_hdr.dlc = can_msg.frame_fields.data_len;
        can_msg_hdr.mid = can_msg.msg_id;
        if(can_msg_hdr.mid == 108)
        {
            setLED(1,1);
            dbc_decode_GPS_LOCATION(&RX_data, can_msg.data.bytes, &can_msg_hdr);
            //printf("Latitude : %f\n",RX_data.CURRENT_LAT_deg);
            //printf("Longitude : %f\n",RX_data.CURRENT_LONG_deg);
            //gcvt(RX_data.CURRENT_LAT_deg, 11, ble_param.latitude);
            snprintf(ble_param.latitude,25, "Lat:%f", RX_data.CURRENT_LAT_deg);
            snprintf(ble_param.longitude,25, "Long:%f", RX_data.CURRENT_LONG_deg);
            debug.IO_DEBUG_Bridge_rx = 0x00;
        }
        if(can_msg_hdr.mid == 109)
        {
            setLED(2,1);
            dbc_decode_COMPASS(&compass_data, can_msg.data.bytes, &can_msg_hdr);
            snprintf(ble_param.bearing,25, "Bearing:%f", compass_data.CMP_BEARING_deg);
            printf("Bearing %s\n",ble_param.bearing);
            debug.IO_DEBUG_Bridge_rx = 0x00;
           //printf("Heading : %f\n",compass_data.CMP_HEADING_deg);
        }
    }

  if(dbc_handle_mia_GPS_LOCATION(&RX_data, 100))
  {
      setLED(1,0);
      printf("Mia Occured:GPS");
      debug.IO_DEBUG_Bridge_rx = 0x01;
  }

  if(dbc_handle_mia_COMPASS(&compass_data,100))
  {
      setLED(2,0);
      printf("Mia Occured:Compass");
      debug.IO_DEBUG_Bridge_rx = 0x01;
  }
}


void CAN_Transmit(uint8_t data)
{
   bool success;
    start_cmd.BRIDGE_START_cmd = data;
   can_msg_t can_msg = { 0 };

   // Encode the CAN message's data bytes, get its header and set the CAN message's DLC and length
   dbc_msg_hdr_t msg_hdr = dbc_encode_BRIDGE_NODE(can_msg.data.bytes, &start_cmd);
   can_msg.msg_id = msg_hdr.mid;
   can_msg.frame_fields.data_len = msg_hdr.dlc;
   // Queue the CAN message to be sent out
   data?setLCD_Right('1'):setLCD_Right('0');
   success = CAN_tx(can1, &can_msg, 0);
   printf("Transmit : %d\n",success);
}

bool transmit_heartbeat_on_can(void)
{
   BRIDGE_HEARTBEAT_t heartbeat_msg = {0};
   can_msg_t can_msg = { 0 };

   heartbeat_msg.BRIDGE_hbt = 1;

   dbc_msg_hdr_t msg_hdr = dbc_encode_BRIDGE_HEARTBEAT(can_msg.data.bytes, &heartbeat_msg);
   can_msg.msg_id = msg_hdr.mid;
   can_msg.frame_fields.data_len = msg_hdr.dlc;

   setLED(4,1);
   // Queue the CAN message to be sent out
   if(CAN_tx(can1, &can_msg, 0))
   {
      debug.IO_DEBUG_HBT_Transmit = 0x00;
      return true;
   }
   else
   {
       debug.IO_DEBUG_HBT_Transmit = 0x01;
       return false;
   }

}

bool transmit_debug_on_can(void)
{
    can_msg_t can_msg = { 0 };
    dbc_msg_hdr_t msg_hdr = dbc_encode_BRIDGE_DEBUG(can_msg.data.bytes, &debug);
    can_msg.msg_id = msg_hdr.mid;
    can_msg.frame_fields.data_len = msg_hdr.dlc;
    return(CAN_tx(can1, &can_msg, 0));
}


