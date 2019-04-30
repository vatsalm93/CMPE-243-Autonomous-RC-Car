/*
 * BLE_HC05.h
 *
 *  Created on: Mar 31, 2019
 *      Author: Vidushi
 */

#ifndef BLE_HC05_H_
#define BLE_HC05_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

#define UART2_BAUD_RATE  38400  ///< Baud rate you wish to use (it will auto-detect and change to this)
#define UART2_RXQ_SIZE   512     ///< Size of UART's RXQ
#define UART2_TXQ_SIZE   10     ///< Size of UART's TXQ
#define FIRMWARE_VERSION    "1.00"


void BLE_init(void);
void check_for_data_on_ble(void);
void BLE_tx(void);

enum dataFromApp {
    STOP_CMD = 0,
    START_CMD = 1,
    CONTINUE_CMD = 2
};

/**
 *
 */
typedef struct {
    char getdata;
    char latitude[15];
    char longitude[15];
    char bearing[20];
} __attribute__((__packed__)) ble_msg_t;


#ifdef __cplusplus
}
#endif
#endif /* BLE_HC05_H_ */
