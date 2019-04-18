#include <stdint.h>
#include "can.h"
#include <string.h>
#include <stdio.h>
#include "CAN_Communication.h"
#include <Bridge_Module/ble_hc05.h>

BRIDGE_NODE_t start_cmd = {0};
GPS_LOCATION_t RX_data ={0};
const uint32_t GPS_LOCATION__MIA_MS = 3000;
const GPS_LOCATION_t GPS_LOCATION__MIA_MSG = { 0 };

void CAN_Init_w(void)
{
    if(CAN_init(can1, 100, 100, 100, NULL, NULL))
    {
        CAN_bypass_filter_accept_all_msgs();
        CAN_reset_bus(can1);
        Clear_Display();
        start_cmd.BRIDGE_START_cmd = 0x0;
    }
}

void CANresetAfterBusOff(void)
{
    if(CAN_is_bus_off(can1))
    {
        printf("can bus off\n");
        CAN_bypass_filter_accept_all_msgs();
        CAN_reset_bus(can1);
    }
}

void CAN_Recieve(void)
{
    can_msg_t can_msg;
    while(CAN_rx(can1, &can_msg, 0))
    {
        dbc_msg_hdr_t can_msg_hdr;
        can_msg_hdr.dlc = can_msg.frame_fields.data_len;
        can_msg_hdr.mid = can_msg.msg_id;
        if(can_msg_hdr.mid == 107)
        {
         setLED(3,0);
         dbc_decode_GPS_LOCATION(&RX_data, can_msg.data.bytes, &can_msg_hdr);
         printf("Latitude : %f\n",RX_data.CURRENT_LAT_deg);
         printf("Longitude : %f\n",RX_data.CURRENT_LONG_deg);
        }
    }

  if(dbc_handle_mia_GPS_LOCATION(&RX_data, 100))
  {
      setLED(3,1);
      printf("Mia Occured");
  }
  else
      printf(".");
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
   return (CAN_tx(can1, &can_msg, 0));
}
