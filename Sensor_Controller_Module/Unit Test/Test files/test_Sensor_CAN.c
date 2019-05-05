#include <stdio.h>
#include <stdint.h>
#include "unity.h"

#include "Sensor_CAN.h"
#include "Mockgenerated_can.h"
#include "Mockultrasonic_sensor.h"
#include "Mockcan.h"
#include "Mockc_io.h"

void setUp(void)
{
   
}
void tearDown(void)
{

}

void test_sensor_can_init(void)
{	
	CAN_init_ExpectAndReturn(can1, 100, 10, 10, 0, 0, 1);
	CAN_reset_bus_Expect(can1);
	TEST_ASSERT_TRUE(sensor_can_init());
	
	//CAN_init_ExpectAndReturn(can1, 100, 10, 10, 0, 0, 0);
	//TEST_ASSERT_FALSE(sensor_can_init());
}

/* void test_sensor_send_data(void)
{
	can_msg_t can_msg = {0};
	dbc_msg_hdr_t can_msg_hdr;
	SENSOR_NODE_t sensor_cmd;
    sensor_lv_max_sonar_t send_ultrasonic_data;
	
	can_msg.dlc = 0x00;
    can_msg.mid = 0x00;
	
} */