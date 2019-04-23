#ifndef CAN_COMMUNICATION_H__
#define CAN_COMMUNICATION_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "c_io.h"
#include <stdint.h>
#include "../../_can_dbc/generated_can.h"


void CANresetAfterBusOff(void);
void canBus_callback(uint32_t data);
void CanOverrun_callback(uint32_t data);
void CAN_Init_w(void);
void CAN_Recieve(void);
void CAN_Transmit(uint8_t data);
bool transmit_heartbeat_on_can(void);
bool transmit_debug_on_can(void);


#ifdef __cplusplus
}
#endif
#endif
