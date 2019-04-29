/// DBC file: ../_can_dbc/243.dbc    Self node: 'SENSOR'  (ALL = 0)
/// This file can be included by a source file, for example: #include "generated.h"
#ifndef __GENEARTED_DBC_PARSER
#define __GENERATED_DBC_PARSER
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>



/// Extern function needed for dbc_encode_and_send()
extern bool dbc_app_send_can_msg(uint32_t mid, uint8_t dlc, uint8_t bytes[8]);

/// Missing in Action structure
typedef struct {
    uint32_t is_mia : 1;          ///< Missing in action flag
    uint32_t mia_counter_ms : 31; ///< Missing in action counter
} dbc_mia_info_t;

/// CAN message header structure
typedef struct { 
    uint32_t mid; ///< Message ID of the message
    uint8_t  dlc; ///< Data length of the message
} dbc_msg_hdr_t; 

// static const dbc_msg_hdr_t BRIDGE_NODE_HDR =                      {  103, 1 };
static const dbc_msg_hdr_t SENSOR_NODE_HDR =                      {  104, 5 };
// static const dbc_msg_hdr_t CAR_CONTROL_HDR =                      {  105, 1 };
// static const dbc_msg_hdr_t MOTOR_NODE_HDR =                       {  106, 1 };
// static const dbc_msg_hdr_t BRIDGE_CHECKPOINTS_HDR =               {  107, 8 };
// static const dbc_msg_hdr_t GPS_LOCATION_HDR =                     {  108, 8 };
// static const dbc_msg_hdr_t COMPASS_HDR =                          {  109, 8 };
static const dbc_msg_hdr_t MASTER_HEARTBEAT_HDR =                 {  110, 1 };
static const dbc_msg_hdr_t SENSOR_HEARTBEAT_HDR =                 {  111, 1 };
// static const dbc_msg_hdr_t MOTOR_HEARTBEAT_HDR =                  {  112, 1 };
// static const dbc_msg_hdr_t GPS_HEARTBEAT_HDR =                    {  113, 1 };
// static const dbc_msg_hdr_t BRIDGE_HEARTBEAT_HDR =                 {  114, 1 };




/// Message: SENSOR_NODE from 'SENSOR', DLC: 5 byte(s), MID: 104
typedef struct {
    uint16_t SENSOR_FRONT_cm;                 ///< B9:0  Min: 0 Max: 645   Destination: MASTER,MOTOR,BRIDGE
    uint8_t LIDAR_Obstacle_FRONT : 3;         ///< B12:10  Min: 0 Max: 4   Destination: MASTER,MOTOR,BRIDGE
    uint8_t LIDAR_Obstacle_RIGHT : 3;         ///< B15:13  Min: 0 Max: 4   Destination: MASTER,MOTOR,BRIDGE
    uint8_t LIDAR_Obstacle_LEFT : 3;          ///< B18:16  Min: 0 Max: 4   Destination: MASTER,MOTOR,BRIDGE
    uint8_t LIDAR_Obstacle_BACK : 3;          ///< B21:19  Min: 0 Max: 4   Destination: MASTER,MOTOR,BRIDGE

    // No dbc_mia_info_t for a message that we will send
} SENSOR_NODE_t;


/// Message: MASTER_HEARTBEAT from 'MASTER', DLC: 1 byte(s), MID: 110
typedef struct {
    uint8_t MASTER_hbt : 1;                   ///< B0:0  Min: 0 Max: 1   Destination: SENSOR,MOTOR,BRIDGE,GPS

    dbc_mia_info_t mia_info;
} MASTER_HEARTBEAT_t;


/// Message: SENSOR_HEARTBEAT from 'SENSOR', DLC: 1 byte(s), MID: 111
typedef struct {
    uint8_t SENSOR_hbt : 1;                   ///< B0:0  Min: 0 Max: 1   Destination: MASTER

    // No dbc_mia_info_t for a message that we will send
} SENSOR_HEARTBEAT_t;


/// @{ These 'externs' need to be defined in a source file of your project
extern const uint32_t                             MASTER_HEARTBEAT__MIA_MS;
extern const MASTER_HEARTBEAT_t                   MASTER_HEARTBEAT__MIA_MSG;
/// @}


/// Not generating code for dbc_encode_BRIDGE_NODE() since the sender is BRIDGE and we are SENSOR

/// Encode SENSOR's 'SENSOR_NODE' message
/// @returns the message header of this message
static inline dbc_msg_hdr_t dbc_encode_SENSOR_NODE(uint8_t bytes[8], SENSOR_NODE_t *from)
{
    uint32_t raw;
    bytes[0]=bytes[1]=bytes[2]=bytes[3]=bytes[4]=bytes[5]=bytes[6]=bytes[7]=0;

    // Not doing min value check since the signal is unsigned already
    if(from->SENSOR_FRONT_cm > 645) { from->SENSOR_FRONT_cm = 645; } // Max value: 645
    raw = ((uint32_t)(((from->SENSOR_FRONT_cm)))) & 0x3ff;
    bytes[0] |= (((uint8_t)(raw) & 0xff)); ///< 8 bit(s) starting from B0
    bytes[1] |= (((uint8_t)(raw >> 8) & 0x03)); ///< 2 bit(s) starting from B8

    // Not doing min value check since the signal is unsigned already
    if(from->LIDAR_Obstacle_FRONT > 4) { from->LIDAR_Obstacle_FRONT = 4; } // Max value: 4
    raw = ((uint32_t)(((from->LIDAR_Obstacle_FRONT)))) & 0x07;
    bytes[1] |= (((uint8_t)(raw) & 0x07) << 2); ///< 3 bit(s) starting from B10

    // Not doing min value check since the signal is unsigned already
    if(from->LIDAR_Obstacle_RIGHT > 4) { from->LIDAR_Obstacle_RIGHT = 4; } // Max value: 4
    raw = ((uint32_t)(((from->LIDAR_Obstacle_RIGHT)))) & 0x07;
    bytes[1] |= (((uint8_t)(raw) & 0x07) << 5); ///< 3 bit(s) starting from B13

    // Not doing min value check since the signal is unsigned already
    if(from->LIDAR_Obstacle_LEFT > 4) { from->LIDAR_Obstacle_LEFT = 4; } // Max value: 4
    raw = ((uint32_t)(((from->LIDAR_Obstacle_LEFT)))) & 0x07;
    bytes[2] |= (((uint8_t)(raw) & 0x07)); ///< 3 bit(s) starting from B16

    // Not doing min value check since the signal is unsigned already
    if(from->LIDAR_Obstacle_BACK > 4) { from->LIDAR_Obstacle_BACK = 4; } // Max value: 4
    raw = ((uint32_t)(((from->LIDAR_Obstacle_BACK)))) & 0x07;
    bytes[2] |= (((uint8_t)(raw) & 0x07) << 3); ///< 3 bit(s) starting from B19

    return SENSOR_NODE_HDR;
}

/// Encode and send for dbc_encode_SENSOR_NODE() message
static inline bool dbc_encode_and_send_SENSOR_NODE(SENSOR_NODE_t *from)
{
    uint8_t bytes[8];
    const dbc_msg_hdr_t hdr = dbc_encode_SENSOR_NODE(bytes, from);
    return dbc_app_send_can_msg(hdr.mid, hdr.dlc, bytes);
}



/// Not generating code for dbc_encode_CAR_CONTROL() since the sender is MASTER and we are SENSOR

/// Not generating code for dbc_encode_MOTOR_NODE() since the sender is MOTOR and we are SENSOR

/// Not generating code for dbc_encode_BRIDGE_CHECKPOINTS() since the sender is BRIDGE and we are SENSOR

/// Not generating code for dbc_encode_GPS_LOCATION() since the sender is GPS and we are SENSOR

/// Not generating code for dbc_encode_COMPASS() since the sender is GPS and we are SENSOR

/// Not generating code for dbc_encode_MASTER_HEARTBEAT() since the sender is MASTER and we are SENSOR

/// Encode SENSOR's 'SENSOR_HEARTBEAT' message
/// @returns the message header of this message
static inline dbc_msg_hdr_t dbc_encode_SENSOR_HEARTBEAT(uint8_t bytes[8], SENSOR_HEARTBEAT_t *from)
{
    uint32_t raw;
    bytes[0]=bytes[1]=bytes[2]=bytes[3]=bytes[4]=bytes[5]=bytes[6]=bytes[7]=0;

    // Not doing min value check since the signal is unsigned already
    if(from->SENSOR_hbt > 1) { from->SENSOR_hbt = 1; } // Max value: 1
    raw = ((uint32_t)(((from->SENSOR_hbt)))) & 0x01;
    bytes[0] |= (((uint8_t)(raw) & 0x01)); ///< 1 bit(s) starting from B0

    return SENSOR_HEARTBEAT_HDR;
}

/// Encode and send for dbc_encode_SENSOR_HEARTBEAT() message
static inline bool dbc_encode_and_send_SENSOR_HEARTBEAT(SENSOR_HEARTBEAT_t *from)
{
    uint8_t bytes[8];
    const dbc_msg_hdr_t hdr = dbc_encode_SENSOR_HEARTBEAT(bytes, from);
    return dbc_app_send_can_msg(hdr.mid, hdr.dlc, bytes);
}



/// Not generating code for dbc_encode_MOTOR_HEARTBEAT() since the sender is MOTOR and we are SENSOR

/// Not generating code for dbc_encode_GPS_HEARTBEAT() since the sender is GPS and we are SENSOR

/// Not generating code for dbc_encode_BRIDGE_HEARTBEAT() since the sender is BRIDGE and we are SENSOR

/// Not generating code for dbc_decode_BRIDGE_NODE() since 'SENSOR' is not the recipient of any of the signals

/// Not generating code for dbc_decode_SENSOR_NODE() since 'SENSOR' is not the recipient of any of the signals

/// Not generating code for dbc_decode_CAR_CONTROL() since 'SENSOR' is not the recipient of any of the signals

/// Not generating code for dbc_decode_MOTOR_NODE() since 'SENSOR' is not the recipient of any of the signals

/// Not generating code for dbc_decode_BRIDGE_CHECKPOINTS() since 'SENSOR' is not the recipient of any of the signals

/// Not generating code for dbc_decode_GPS_LOCATION() since 'SENSOR' is not the recipient of any of the signals

/// Not generating code for dbc_decode_COMPASS() since 'SENSOR' is not the recipient of any of the signals

/// Decode MASTER's 'MASTER_HEARTBEAT' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_MASTER_HEARTBEAT(MASTER_HEARTBEAT_t *to, const uint8_t bytes[8], const dbc_msg_hdr_t *hdr)
{
    const bool success = true;
    // If msg header is provided, check if the DLC and the MID match
    if (NULL != hdr && (hdr->dlc != MASTER_HEARTBEAT_HDR.dlc || hdr->mid != MASTER_HEARTBEAT_HDR.mid)) {
        return !success;
    }

    uint32_t raw;
    raw  = ((uint32_t)((bytes[0]) & 0x01)); ///< 1 bit(s) from B0
    to->MASTER_hbt = ((raw));

    to->mia_info.mia_counter_ms = 0; ///< Reset the MIA counter

    return success;
}


/// Not generating code for dbc_decode_SENSOR_HEARTBEAT() since 'SENSOR' is not the recipient of any of the signals

/// Not generating code for dbc_decode_MOTOR_HEARTBEAT() since 'SENSOR' is not the recipient of any of the signals

/// Not generating code for dbc_decode_GPS_HEARTBEAT() since 'SENSOR' is not the recipient of any of the signals

/// Not generating code for dbc_decode_BRIDGE_HEARTBEAT() since 'SENSOR' is not the recipient of any of the signals

/// Handle the MIA for MASTER's MASTER_HEARTBEAT message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_MASTER_HEARTBEAT(MASTER_HEARTBEAT_t *msg, uint32_t time_incr_ms)
{
    bool mia_occurred = false;
    const dbc_mia_info_t old_mia = msg->mia_info;
    msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= MASTER_HEARTBEAT__MIA_MS);

    if (!msg->mia_info.is_mia) { // Not MIA yet, so keep incrementing the MIA counter
        msg->mia_info.mia_counter_ms += time_incr_ms;
    }
    else if(!old_mia.is_mia)   { // Previously not MIA, but it is MIA now
        // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
        *msg = MASTER_HEARTBEAT__MIA_MSG;
        msg->mia_info.mia_counter_ms = MASTER_HEARTBEAT__MIA_MS;
        msg->mia_info.is_mia = true;
        mia_occurred = true;
    }

    return mia_occurred;
}

#endif
