/*
 * Sensor_CAN_Interfacing.cpp
 *
 *  Created on: Apr 14, 2019
 *      Author: halak
 */

#include <stdint.h>
#include <stdbool.h>
#include "Sensor_CAN_Interfacing.h"
#include "can.h"
#include "RPLidar.h"
//#include "LidarTask.h"
#include "_can_dbc/generated_can.h"
#include "L5_Application/ultrasonic_sensor.h"
#include "printf_lib.h"

#define SENSOR_CAN_BUS      can1
#define SENSOR_BAUD_RATE    100
#define SENSOR_RX_Q         8
#define SENSOR_TX_Q         8

extern sensor_lv_max_sonar_t send_sensor_data;
static store_SECTION_value *send_lidar_data;

bool sensor_can_init()
{
    bool status = false;
       do {
           status = CAN_init(SENSOR_CAN_BUS, SENSOR_BAUD_RATE, SENSOR_RX_Q, SENSOR_TX_Q, 0, 0);
       } while (status == false);
       return status;
}

void sensor_send_data()
{
    SENSOR_NODE_t sensor_cmd;
    //u0_dbg_printf("%d\n",sensor_cmd.SENSOR_FRONT_OBSTACLE_TYPE);

   sensor_cmd.SENSOR_FRONT_cm = send_sensor_data.distance;
   sensor_cmd.LIDAR_SECTION0 = send_lidar_data->section0;
   sensor_cmd.LIDAR_SECTION1 = send_lidar_data->section1;
   sensor_cmd.LIDAR_SECTION2 = send_lidar_data->section2;
   sensor_cmd.LIDAR_SECTION3 = send_lidar_data->section3;
   sensor_cmd.LIDAR_SECTION4 = send_lidar_data->section4;
   sensor_cmd.LIDAR_SECTION5 = send_lidar_data->section5;
   sensor_cmd.LIDAR_SECTION6 = send_lidar_data->section6;
   sensor_cmd.LIDAR_SECTION7 = send_lidar_data->section7;
   sensor_cmd.LIDAR_SECTION8 = send_lidar_data->section8;
   sensor_cmd.LIDAR_SECTION9 = send_lidar_data->section9;
   sensor_cmd.LIDAR_SECTION10 = send_lidar_data->section10;
   sensor_cmd.LIDAR_SECTION11 = send_lidar_data->section11;

   u0_dbg_printf("section 0 : %d\n",send_lidar_data->section0);
//   u0_dbg_printf("section 1 : %d\n",send_lidar_data->section1);
//   u0_dbg_printf("section 2 : %d\n",send_lidar_data->section2);
//   u0_dbg_printf("section 3 : %d\n",send_lidar_data->section3);
//   u0_dbg_printf("section 4 : %d\n",sensor_cmd.LIDAR_SECTION4);
//   u0_dbg_printf("section 5 : %d\n",sensor_cmd.LIDAR_SECTION5);
//   u0_dbg_printf("section 6 : %d\n",sensor_cmd.LIDAR_SECTION6);
//   u0_dbg_printf("section 7 : %d\n",sensor_cmd.LIDAR_SECTION7);
//   u0_dbg_printf("section 8 : %d\n",sensor_cmd.LIDAR_SECTION8);
//   u0_dbg_printf("section 9 : %d\n",sensor_cmd.LIDAR_SECTION9);
//   u0_dbg_printf("section 10 : %d\n",sensor_cmd.LIDAR_SECTION10);
//   u0_dbg_printf("section 11 : %d\n",sensor_cmd.LIDAR_SECTION11);

   can_msg_t can_msg = {0};
    dbc_msg_hdr_t can_msg_hdr = dbc_encode_SENSOR_NODE(can_msg.data.bytes, &sensor_cmd);
    can_msg.msg_id = can_msg_hdr.mid;
    can_msg.frame_fields.data_len = can_msg_hdr.dlc;

    if(CAN_tx(SENSOR_CAN_BUS, &can_msg, 0) == 1) {
        //puts("OK");
    } else {
        //puts("Not OK");
    }
}

bool sensor_CAN_turn_on_bus_if_bus_off()
{
    if (CAN_is_bus_off(SENSOR_CAN_BUS))
    {
        CAN_bypass_filter_accept_all_msgs();
        CAN_reset_bus(SENSOR_CAN_BUS);
        return true;
    }
    return false;
}
