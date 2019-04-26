/*
 * test_can_tx.c
 *
 *  Created on: Mar 12, 2019
 *      Author: vidushi
 */


#include "unity.h"
#include "can_tx.h"
#include <stdbool.h>
#include <stdio.h>
#include "Mockcan.h"


void setUp(void) {

}
void tearDown(void) {
}

void test_can_init(void)
{
   CAN_init_ExpectAndReturn(0, 100, 100, 100, NULL, NULL,true);
   CAN_reset_bus_Expect(0);
   TEST_ASSERT_TRUE(can_init());
   CAN_init_ExpectAnyArgsAndReturn(false);
   TEST_ASSERT_FALSE(can_init());
}

void test_transmit_dbc_data_on_can(void)
{
    CAN_tx_ExpectAnyArgsAndReturn(true);
    TEST_ASSERT_TRUE(transmit_dbc_data_on_can());
}

void test_check_bus_off(void)
{
    CAN_is_bus_off_ExpectAndReturn(0,true);
    CAN_reset_bus_Expect(0);
    CAN_bypass_filter_accept_all_msgs_Expect();
    check_bus_off();
}
