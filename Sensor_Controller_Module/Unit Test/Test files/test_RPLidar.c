
#include <stdio.h>
#include <stdint.h>
#include "unity.h"
#include "RPLidar.h"
#include "Mockgenerated_can.h"
#include "Mockc_uart2.h"


void test_uart_init_for_sensor(void)
{
	uart2_instance_ExpectAnyArgs();
	uart2_init_Expect(115200, 50, 50);
	Uart_init_for_sensor();
}

void test__sendCommand(void)
{
	uart2_put_char_ExpectAndReturn(0xA5, 0, 1);
    uart2_put_char_ExpectAndReturn(123, 0, 1);
	TEST_ASSERT_FALSE(_sendCommand(123,0,0));
}
	
void test__waitResponseHeader(void)
{
	uart2_put_char_ExpectAndReturn(123, 0, 1);
	TEST_ASSERT_FALSE(_waitResponseHeader(0,0));
	
	uart2_put_char_ExpectAndReturn(0xA5, 0, 1);
	TEST_ASSERT_EQUAL(0x80020000,_waitResponseHeader(0,0));
	
	uart2_put_char_ExpectAndReturn(0x5A, 0, 1);
	TEST_ASSERT_EQUAL(0x80020000,_waitResponseHeader(0,0));
}