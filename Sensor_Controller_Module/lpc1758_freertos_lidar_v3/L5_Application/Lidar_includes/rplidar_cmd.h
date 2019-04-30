
#pragma once

#include "rplidar_protocol.h"

// Commands
//-----------------------------------------

//DIVIDE INTO ANGLES
#if 0
#define Obstacle_FRONT0_start_range 340
#define Obstacle_FRONT0_end_range 359
#define Obstacle_FRONT1_start_range 0
#define Obstacle_FRONT1_end_range 15
#define Obstacle_RIGHT_start_range 15
#define Obstacle_RIGHT_end_range 60
#define Obstacle_LEFT_start_range 285
#define Obstacle_LEFT_end_range 340
#define Obstacle_BACK_start_range 165
#define Obstacle_BACK_end_range 195


#define Obstacle_FRONT0_start_range 0
#define Obstacle_FRONT0_end_range 5
#define Obstacle_FRONT1_start_range 335
#define Obstacle_FRONT1_end_range 359
#define Obstacle_RIGHT_start_range 5
#define Obstacle_RIGHT_end_range 50
#define Obstacle_LEFT_start_range 270
#define Obstacle_LEFT_end_range 335
#define Obstacle_BACK_start_range 140
#define Obstacle_BACK_end_range 200
#endif


#define DEGREES10  (10.0)
#define DEGREES20  (20.0)
#define DEGREES45  (45.0)
#define DEGREES90     (90.0)
#define DEGREES120  (120.0)
#define DEGREES150  (150.0)
#define DEGREES180  (180.0)
#define DEGREES210  (210.0)
#define DEGREES240  (240.0)
#define DEGREES270  (270.0)
#define DEGREES315     (290.0)
#define DEGREES335  (335.0)
#define DEGREES345 (345.0)
#define DEGREES355 (355.0)

// Commands without payload and response
#define RPLIDAR_CMD_STOP               0x25
#define RPLIDAR_CMD_SCAN               0x20
#define RPLIDAR_CMD_FORCE_SCAN         0x21
#define RPLIDAR_CMD_RESET              0x40

// Commands without payload but have response
#define RPLIDAR_CMD_GET_DEVICE_INFO      0x50
#define RPLIDAR_CMD_GET_DEVICE_HEALTH    0x52

#if defined(_WIN32)
#pragma pack(1)
#endif


// Response
// ------------------------------------------
#define RPLIDAR_ANS_TYPE_MEASUREMENT      0x81

#define RPLIDAR_ANS_TYPE_DEVINFO          0x4
#define RPLIDAR_ANS_TYPE_DEVHEALTH        0x6


#define RPLIDAR_STATUS_OK                 0x0
#define RPLIDAR_STATUS_WARNING            0x1
#define RPLIDAR_STATUS_ERROR              0x2

#define RPLIDAR_RESP_MEASUREMENT_SYNCBIT        (0x1<<0)
#define RPLIDAR_RESP_MEASUREMENT_QUALITY_SHIFT  2
#define RPLIDAR_RESP_MEASUREMENT_CHECKBIT       (0x1<<0)
#define RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT    1

// RP-Lidar Input Packets
#define RPLIDAR_CMD_SYNC_BYTE        0xA5
#define RPLIDAR_CMDFLAG_HAS_PAYLOAD  0x80
#define RPLIDAR_ANS_SYNC_BYTE1       0xA5
#define RPLIDAR_ANS_SYNC_BYTE2       0x5A
#define RPLIDAR_ANS_PKTFLAG_LOOP     0x1

//Results types
#define RESULT_OK              0
#define RESULT_FAIL_BIT        0x80000000
#define RESULT_ALREADY_DONE    0x20
#define RESULT_INVALID_DATA    (0x8000 | RESULT_FAIL_BIT)
#define RESULT_OPERATION_FAIL  (0x8001 | RESULT_FAIL_BIT)
#define RESULT_OPERATION_TIMEOUT  (0x8002 | RESULT_FAIL_BIT)
#define RESULT_OPERATION_STOP    (0x8003 | RESULT_FAIL_BIT)
#define RESULT_OPERATION_NOT_SUPPORT    (0x8004 | RESULT_FAIL_BIT)
#define RESULT_FORMAT_NOT_SUPPORT    (0x8005 | RESULT_FAIL_BIT)
#define RESULT_INSUFFICIENT_MEMORY   (0x8006 | RESULT_FAIL_BIT)
#define IS_OK(x)    ( ((x) & RESULT_FAIL_BIT) == 0 )
#define IS_FAIL(x)  ( ((x) & RESULT_FAIL_BIT) )

typedef struct _rplidar_response_measurement_node_t {
    uint8_t    sync_quality;      // syncbit:1;syncbit_inverse:1;quality:6;
    uint16_t   angle_q6_checkbit; // check_bit:1;angle_q6:15;
    uint16_t   distance_q2;
} __attribute__((packed)) rplidar_response_measurement_node_t;

typedef struct _rplidar_response_device_info_t {
    uint8_t   model;
    uint16_t  firmware_version;
    uint8_t   hardware_version;
    uint8_t   serialnum[16];
} __attribute__((packed)) rplidar_response_device_info_t;

typedef struct _rplidar_response_device_health_t {
    uint8_t   status;
    uint16_t  error_code;
} __attribute__((packed)) rplidar_response_device_health_t;


#if defined(_WIN32)
#pragma pack()
#endif
