/*
 * test_master.c
 *
 *  Created on: Apr 9, 2019
 *      Author: Aakash
 */
#include "unity.h"
#include "Mockc_io.h"
#include "Mockcan.h"
#include "c_code/externs.h"
#include "c_code/defines.h"
#include "c_code/bridge.h"
#include "c_code/sensor.h"
#include "c_code/gps.h"
#include "c_code/master.h"
#include "c_code/structures.h"
#include "c_code/compass.h"
#include "c_code/c_io.h"

can_t can;
void setUp(void)
{
    can = can1;
}
void tearDown(void)
{

}

void test_master_controller_init(void)
{
    //setup expectation
    CAN_bypass_filter_accept_all_msgs_Expect();
    CAN_reset_bus_Expect(CAN_BUS);

    CAN_init_ExpectAndReturn(can, 100, 10, 10, NULL, NULL, true);
    master_controller_init();
}

void test_master_CAN_turn_on_bus_if_bus_off__return_true(void)
{
    //setup expectation
    CAN_bypass_filter_accept_all_msgs_Expect();
    CAN_reset_bus_Expect(can);
    CAN_is_bus_off_ExpectAndReturn(can, true);
    TEST_ASSERT_TRUE(master_CAN_turn_on_bus_if_bus_off());
}

void test_master_CAN_turn_on_bus_if_bus_off__return_false(void)
{
    //setup expectation
    CAN_is_bus_off_ExpectAndReturn(can, false);
    TEST_ASSERT_FALSE(master_CAN_turn_on_bus_if_bus_off());
}

void test_sys_start_stop_cmd__return_false(void)
{
    start_cmd = false;
    TEST_ASSERT_FALSE(sys_start_stop_cmd());
}

void test_sys_start_stop_cmd__return_true(void)
{
    start_cmd = true;
    TEST_ASSERT_TRUE(sys_start_stop_cmd());
}

void test_transmit_heartbeat_on_can__return_true(void)
{
    MASTER_HEARTBEAT_t heartbeat_msg = { 0 };
    can_msg_t can_msg = {0};
    heartbeat_msg.MASTER_hbt = 1;
    dbc_msg_hdr_t msg_hdr = dbc_encode_MASTER_HEARTBEAT(can_msg.data.bytes, &heartbeat_msg);
    can_msg.msg_id = msg_hdr.mid;
    can_msg.frame_fields.data_len = msg_hdr.dlc;
    CAN_tx_ExpectAndReturn(can, &can_msg, 0, true);
    TEST_ASSERT_TRUE(transmit_heartbeat_on_can());
}

void test_transmit_heartbeat_on_can__return_false(void)
{
    MASTER_HEARTBEAT_t heartbeat_msg = { 0 };
    can_msg_t can_msg = {0};
    heartbeat_msg.MASTER_hbt = 1;
    dbc_msg_hdr_t msg_hdr = dbc_encode_MASTER_HEARTBEAT(can_msg.data.bytes, &heartbeat_msg);
    can_msg.msg_id = msg_hdr.mid;
    can_msg.frame_fields.data_len = msg_hdr.dlc;
    CAN_tx_ExpectAndReturn(can1, &can_msg, 0, false);
    TEST_ASSERT_FALSE(transmit_heartbeat_on_can());
}

void test_hbt_sync_from_all_node__return_true(void)
{
    sensor_hbt_sync = true;
    motor_hbt_sync = true;
    gps_hbt_sync = true;
    bridge_hbt_sync = true;
    TEST_ASSERT_TRUE(hbt_sync_from_all_node());
}
