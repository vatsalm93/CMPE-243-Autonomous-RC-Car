/*
 * RoboPeak RPLIDAR Driver for Arduino
 * RoboPeak.com
 *
 * Copyright (c) 2014, RoboPeak
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <stddef.h>
#include "lpc_sys.h"
#include "utilities.h"
#include "Lidar_includes/RPLidar.h"
#include "printf_lib.h"
#include "_can_dbc/generated_can.h"
#include <string.h>

#define distance_range 250.0
SENSOR_NODE_t sensor_cmd;
static int previous_track[4] = {13};

// ask the RPLIDAR for its health info
uint32_t RPLidar::getHealth(rplidar_response_device_health_t & healthinfo, uint32_t timeout)
{
    uint32_t currentTs = sys_get_uptime_ms();
    uint32_t remainingtime;
    uint8_t *infobuf = (uint8_t *)&healthinfo;
    uint8_t recvPos = 0;

    rplidar_ans_header_t response_header;
    u_result  ans;
    if (IS_FAIL(ans = _sendCommand(RPLIDAR_CMD_GET_DEVICE_HEALTH, NULL, 0))) {
        return ans;
    }

    if (IS_FAIL(ans = _waitResponseHeader(&response_header, timeout))) {
        return ans;
    }

    // verify whether we got a correct header
    if (response_header.type != RPLIDAR_ANS_TYPE_DEVHEALTH) {
        return RESULT_INVALID_DATA;
    }

    if ((response_header.size) < sizeof(rplidar_response_device_health_t)) {
        return RESULT_INVALID_DATA;
    }

    while ((remainingtime=sys_get_uptime_ms() - currentTs) <= timeout) {
        char received_data;
        uart2.getChar(&received_data,portMAX_DELAY);
        int currentbyte = received_data;
        if (currentbyte < 0) continue;
        infobuf[recvPos++] = currentbyte;

        if (recvPos == sizeof(rplidar_response_device_health_t)) {
            return RESULT_OK;
        }
    }
    return RESULT_OPERATION_TIMEOUT;
}

// ask the RPLIDAR for its device info like the serial number
uint32_t RPLidar::getDeviceInfo(rplidar_response_device_info_t & info, uint32_t timeout )
{
    uint8_t  recvPos = 0;
    uint32_t currentTs = sys_get_uptime_ms();
    uint32_t remainingtime;
    uint8_t *infobuf = (uint8_t*)&info;
    rplidar_ans_header_t response_header;
    u_result  ans;

    {
        if (IS_FAIL(ans = _sendCommand(RPLIDAR_CMD_GET_DEVICE_INFO,NULL,0))) {
            return ans;
        }

        if (IS_FAIL(ans = _waitResponseHeader(&response_header, timeout))) {
            return ans;
        }

        // verify whether we got a correct header
        if (response_header.type != RPLIDAR_ANS_TYPE_DEVINFO) {
            return RESULT_INVALID_DATA;
        }

        if (response_header.size < sizeof(rplidar_response_device_info_t)) {
            return RESULT_INVALID_DATA;
        }

        while ((remainingtime=sys_get_uptime_ms() - currentTs) <= timeout) {

            char received_data;
            uart2.getChar(&received_data,portMAX_DELAY);
            int currentbyte = received_data;
            if (currentbyte<0) continue;
            infobuf[recvPos++] = currentbyte;

            if (recvPos == sizeof(rplidar_response_device_info_t)) {
                return RESULT_OK;
            }
        }
    }

    return RESULT_OPERATION_TIMEOUT;
}

// stop the measurement operation
uint32_t RPLidar::stop()
{
    uint32_t ans = _sendCommand(RPLIDAR_CMD_STOP,NULL,0);
    return ans;
}

uint32_t RPLidar::reset()
{
    uint32_t ans = _sendCommand(RPLIDAR_CMD_RESET,NULL,0);
    return ans;
}


// start the measurement operation
uint32_t RPLidar::startScan(bool force, uint32_t timeout)
{
    uint32_t ans;

    stop(); //force the previous operation to stop
    u0_dbg_printf("step1\n");
    ans = _sendCommand(force?RPLIDAR_CMD_FORCE_SCAN:RPLIDAR_CMD_SCAN, NULL, 0);
    if (IS_FAIL(ans)) return ans;
    u0_dbg_printf("step2\n");

    // waiting for confirmation
    rplidar_ans_header_t response_header;
    if (IS_FAIL(ans = _waitResponseHeader(&response_header, timeout))) {
        u0_dbg_printf("ans is %x\n",ans);
        u0_dbg_printf("step3\n");
        return ans;
    }

    // verify whether we got a correct header
    if (response_header.type != RPLIDAR_ANS_TYPE_MEASUREMENT) {
        u0_dbg_printf("step4\n");
        return RESULT_INVALID_DATA;
    }

    if (response_header.size < sizeof(rplidar_response_measurement_node_t)) {
        u0_dbg_printf("step5\n");
        return RESULT_INVALID_DATA;
    }
    u0_dbg_printf("step6\n");
    return RESULT_OK;
}



uint32_t RPLidar::_sendCommand(uint8_t cmd, const void * payload, size_t payloadsize)
{
    rplidar_cmd_packet_t pkt_header;
    rplidar_cmd_packet_t * header = &pkt_header;

    if (payloadsize && payload) {
        cmd |= RPLIDAR_CMDFLAG_HAS_PAYLOAD;
    }

    header->syncByte = RPLIDAR_CMD_SYNC_BYTE;
    header->cmd_flag = cmd;
    uart2.putChar(header->syncByte, portMAX_DELAY);
    uart2.putChar(header->cmd_flag, portMAX_DELAY);
    return RESULT_OK;
}

uint32_t RPLidar::_waitResponseHeader(rplidar_ans_header_t * header, uint32_t timeout)
{
    uint8_t  recvPos = 0;
    uint32_t currentTs = sys_get_uptime_ms();
    uint32_t remainingtime;
    uint8_t *headerbuf = (uint8_t*)header;
    while ((remainingtime=sys_get_uptime_ms() - currentTs) <= timeout) {

        char received_data;
        uart2.getChar(&received_data,portMAX_DELAY);
        int currentbyte = received_data;

        if (currentbyte<0) continue;

        switch (recvPos) {
            case 0:
                if (currentbyte != RPLIDAR_ANS_SYNC_BYTE1) {
                    continue;
                }
                break;
            case 1:
                if (currentbyte != RPLIDAR_ANS_SYNC_BYTE2) {
                    recvPos = 0;
                    continue;
                }
                break;
        }
        headerbuf[recvPos++] = currentbyte;
        if (recvPos == sizeof(rplidar_ans_header_t)) {
            return RESULT_OK;
        }


    }

    return RESULT_OPERATION_TIMEOUT;
}

uint32_t RPLidar::waitPoint(rplidar_response_measurement_node_t *node, uint32_t timeout, RPLidarMeasurement *measurement)
{
    uint32_t currentTs = sys_get_uptime_ms();
    uint32_t remainingtime;
    uint8_t *nodebuf = (uint8_t*)node;
    uint8_t recvPos = 0;
    while ((remainingtime=sys_get_uptime_ms() - currentTs) <= timeout) {
        char recieved_char;
        int currentbyte = 0;
        if(uart2.getChar(&recieved_char,portMAX_DELAY)){
            currentbyte = recieved_char;
        }
        if (currentbyte<0) continue;

        switch (recvPos) {
            case 0: // expect the sync bit and its reverse in this byte          {
            {
                uint8_t tmp = (currentbyte>>1);
                if ( (tmp ^ currentbyte) & 0x1 ) {
                    // pass
                } else {
                    continue;
                }

            }
            break;
            case 1: // expect the highest bit to be 1
            {
                if (currentbyte & RPLIDAR_RESP_MEASUREMENT_CHECKBIT) {
                    // pass
                } else {
                    recvPos = 0;
                    continue;
                }
            }
            break;
        }
        nodebuf[recvPos++] = currentbyte;

        if (recvPos == sizeof(rplidar_response_measurement_node_t)) {
            measurement->distance = node->distance_q2/(float)4.0;
            measurement->angle = (node->angle_q6_checkbit >> RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT)/(float)64.0;
            measurement->quality = (node->sync_quality>>RPLIDAR_RESP_MEASUREMENT_QUALITY_SHIFT);
            measurement->startBit = (node->sync_quality & RPLIDAR_RESP_MEASUREMENT_SYNCBIT);
            return RESULT_OK;
        }
    }
    return RESULT_OPERATION_TIMEOUT;
}

int RPLidar::divideDistance(float distance)
{
    int track;
    if ((distance > 0) && (distance <= distance_range)) {
        track = 1;
    }
    else if ((distance > distance_range) && (distance <= distance_range * 2)) {
        track = 2;
    }
    else if ((distance > distance_range * 2) && (distance <= distance_range * 3)) {
        track = 3;
    }
    else if ((distance > distance_range * 3) && (distance <= distance_range * 4)) {
        track = 4;
    }
    else if ((distance > distance_range * 4) && (distance <= distance_range * 5)) {
        track = 5;
    }
    else if ((distance > distance_range * 5) && (distance <= distance_range * 6)) {
        track = 6;
    }
    else if ((distance > distance_range * 6) && (distance <= distance_range * 7)) {
        track = 7;
    }
    else if ((distance > distance_range * 7) && (distance <= distance_range * 8)) {
        track = 8;
    }
    else if ((distance > distance_range * 8) && (distance <= distance_range * 9)) {
        track = 9;
    }
    else if ((distance > distance_range * 9) && (distance <= distance_range * 10)) {
        track = 10;
    }
    else if ((distance > distance_range * 10) && (distance <= distance_range * 11)) {
        track = 11;
    }
    else if ((distance > distance_range * 11) && (distance <= distance_range * 12)) {
        track = 12;
    }
    else {
        track = 13;
    }
    return track;
}

void RPLidar::divideAngle(RPLidarMeasurement *angle_value, int length, RPLidarRotation *rot)
{
    int store_angle = 0;
    float store_distance = 0.0;
    memset(previous_track, 13, sizeof(previous_track));
    for (int i = 0; i < length; i++) {
        int track = 13;
        if (angle_value->quality != 0)
        {
            store_angle = angle_value[i].angle;
            store_distance = angle_value[i].distance;
            if (((store_angle > Obstacle_FRONT0_start_range) && (store_angle <= Obstacle_FRONT0_end_range))
                    || ((store_angle >= Obstacle_FRONT1_start_range) && (store_angle <= Obstacle_FRONT1_end_range)))
            {
                track = divideDistance(store_distance);
                rot->sector_front = previous_track[0];
                if (track < previous_track[0])
                    rot->sector_front = track;
                previous_track[0] = track;
                sensor_cmd.LIDAR_Obstacle_FRONT = rot->sector_front;
            }
            else if ((store_angle > Obstacle_RIGHT_start_range) && (store_angle <= Obstacle_RIGHT_end_range))
            {
                track = divideDistance(store_distance);
                rot->sector_front_right = previous_track[1];
                if (track < previous_track[1])
                    rot->sector_front_right = track;
                previous_track[1] = track;
                sensor_cmd.LIDAR_Obstacle_RIGHT = rot->sector_front_right;
            }
            else if ((store_angle > Obstacle_LEFT_start_range) && (store_angle <= Obstacle_LEFT_end_range))
            {
                track = divideDistance(store_distance);
                rot->sector_front_left = previous_track[2];
                if (track < previous_track[2])
                    rot->sector_front_left = track;
                previous_track[2] = track;
                sensor_cmd.LIDAR_Obstacle_LEFT = rot->sector_front_left;
            }
            else if ((store_angle > Obstacle_BACK_start_range) && (store_angle <= Obstacle_BACK_end_range))
            {
                track = divideDistance(store_distance);
                rot->sector_rear = previous_track[3];
                if (track < previous_track[3])
                    rot->sector_rear = track;
                previous_track[3] = track;
                sensor_cmd.LIDAR_Obstacle_BACK = rot->sector_rear;
            }
            else
            {
                ;
            }
        }
    }
}