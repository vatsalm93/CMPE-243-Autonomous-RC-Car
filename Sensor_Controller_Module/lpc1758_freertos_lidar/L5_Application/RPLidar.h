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

#pragma once

#include "rptypes.h"
#include "rplidar_cmd.h"
#include "uart2.hpp"

struct RPLidarMeasurement
{
    float distance;
    float angle;
    uint8_t quality;
    bool  startBit;
};

typedef struct store_SECTION_VALUE
{
    int section0;
    int section1;
    int section2;
    int section3;
    int section4;
    int section5;
    int section6;
    int section7;
    int section8;
    int section9;
    int section10;
    int section11;
}store_SECTION_value;

class RPLidar
{
    public:
        enum{
            RPLIDAR_SERIAL_BAUDRATE = 115200,
            RPLIDAR_DEFAULT_TIMEOUT = 500,
        };

    Uart2 &uart2 = Uart2::getInstance();
   // bool uart2_init(unsigned int baudRate, int rxQSize=32, int txQSize=64);
    // ask the RPLIDAR for its health info
    uint32_t getHealth(rplidar_response_device_health_t & healthinfo, uint32_t timeout = RPLIDAR_DEFAULT_TIMEOUT);

    // ask the RPLIDAR for its device info like the serial number
    uint32_t getDeviceInfo(rplidar_response_device_info_t & info, uint32_t timeout = RPLIDAR_DEFAULT_TIMEOUT);

    // stop the measurement operation
    u_result stop();

    uint32_t reset();
    // start the measurement operation
    uint32_t startScan(bool force = false, uint32_t timeout = RPLIDAR_DEFAULT_TIMEOUT*2);

    // wait for one sample point to arrive
    uint32_t waitPoint(rplidar_response_measurement_node_t *node, uint32_t timeout, RPLidarMeasurement *measurement);

    // retrieve currently received sample point

    const RPLidarMeasurement & getCurrentPoint()
    {
        return _currentMeasurement;
    }

    uint32_t divideAngle(RPLidarMeasurement *angle_value,int length, store_SECTION_value *identify_section);
    int divideDistance(float distance);

protected:
    uint32_t _sendCommand(uint8_t cmd, const void * payload, size_t payloadsize);
    uint32_t _waitResponseHeader(rplidar_ans_header_t * header, uint32_t timeout);

protected:
    RPLidarMeasurement _currentMeasurement;
};
