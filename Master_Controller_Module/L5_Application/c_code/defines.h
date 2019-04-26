/*
 * defines.h
 *
 *  Created on: Apr 17, 2019
 *      Author: Aakash
 */

#ifndef DEFINES_H_
#define DEFINES_H_

#ifdef __cplusplus
extern "C" {
#endif

#define BRIDGE_MID                  103
#define SENSOR_MID                  105
#define CAR_CONTROL_MID             104
#define MOTOR_MID                   106
#define BRIDGE_CHECKPOINTS_MID      107
#define GPS_LOCATION_MID            108
#define COMPASS_MID                 109
#define MASTER_HEARTBEAT_MID        110
#define SENSOR_HEARTBEAT_MID        111
#define MOTOR_HEARTBEAT_MID         112
#define GPS_HEARTBEAT_MID           113
#define BRIDGE_HEARTBEAT_MID        114

#define CAN_BUS                     can1
#define CAN_BAUD_RATE               100

#define HEART_BEAT_cmd              1

#define ZONE_NEAR                   50
#define ZONE_MID                    150
#define ZONE_FAR                    250

#define LIDAR_PLACEMENT_OFFSET      28
#define LIDAR_ZONE_1                LIDAR_PLACEMENT_OFFSET + ZONE_NEAR
#define LIDAR_ZONE_2                LIDAR_PLACEMENT_OFFSET + ZONE_MID
#define LIDAR_ZONE_3                LIDAR_PLACEMENT_OFFSET + ZONE_FAR

#define OBSTACLE_TRACK_THRESHOLD    4
#define CLEARANCE_TRACK_THRESHOLD   OBSTACLE_TRACK_THRESHOLD - 1

#define MOTOR_SLOW_KPH              3.00
#define MOTOR_MED_KPH               5.00
#define MOTOR_FAST_KPH              7.00
#define MOTOR_STOP_KPH              0.00

#ifdef __cplusplus
}
#endif

#endif /* DEFINES_H_ */
