/*
 * c_can.c
 *
 *  Created on: Mar 3, 2019
 *      Author: Aakash
 */
#include "motor_can_rx.h"
#include "printf_lib.h"

const can_t can = can1;
const uint32_t baudRate = 100;
const uint16_t rxQueueSize = 100;
const uint16_t txQueueSize = 100;
const uint32_t timeout_ms = 0;

bool motor_can_init(void)
{
    if (CAN_init(can, baudRate, rxQueueSize, txQueueSize, 0, 0))
    {
        u0_dbg_printf("Motor can INIT SUCCESS\n");
        CAN_bypass_filter_accept_all_msgs();
        CAN_reset_bus(can);
        return true;
    }
    else
    {
        return false;
    }
}

bool motor_can_rx(CAR_CONTROL_t *drive)
{
    can_msg_t can_motor_msg;
    dbc_msg_hdr_t can_msg_hdr;
    bool motor_rx_flag = false;
    if (CAN_rx(can, &can_motor_msg, timeout_ms))
    {
        can_msg_hdr.dlc = can_motor_msg.frame_fields.data_len;
        can_msg_hdr.mid = can_motor_msg.msg_id;
        if(105 == can_motor_msg.msg_id){
            dbc_decode_CAR_CONTROL(drive, can_motor_msg.data.bytes, &can_msg_hdr);
//            u0_dbg_printf("motor_encode: %d, motor_decode: %d, servo_decode: %d\n",
//                           can_motor_msg.data.bytes[0], drive->MOTOR_DRIVE_cmd, drive->MOTOR_STEER_cmd);
        }
        motor_rx_flag = true;
    }
        return motor_rx_flag;
}

bool motor_can_reset_busoff(void)
{
    if (CAN_is_bus_off(can))
    {
        CAN_bypass_filter_accept_all_msgs();
        CAN_reset_bus(can);
        return true;
    }
    return false;
}


