/*
 * BLE_HC05.c
 *
 *  Created on: Mar 31, 2019
 *      Author: Vidushi
 *      Version: V1.00
 */

#include <Bridge_Module/ble_hc05.h>
#include <stdio.h>
#include <stdlib.h>
#include "c_uart2.h"
#include "c_uart_dev.h"
#include "c_io.h"
#include <can_code/CAN_Communication.h>

ble_msg_t ble_param = {0};

void BLE_init()
{
    //Clear_Display();      /* Clear the display */
    cUart2_init(UART2_BAUD_RATE, UART2_RXQ_SIZE, UART2_TXQ_SIZE);      /* Init baud rate */

    printf("\r\nHC-05 Version:%s\r\n",FIRMWARE_VERSION);
    // Default Values for now
    //ble_param.latitude = "Lat:37.121356 ";
    //ble_param.longitude = "Long:-121.121356 ";
}

void BLE_rx()
{
    while(cgetChar(&ble_param.getdata,0))
     {
        if ('\r' != ble_param.getdata && '\n' != ble_param.getdata) {
            printf("%c",ble_param.getdata);

        }
      }

    if(ble_param.getdata == '1')
    {
          CAN_Transmit(START_CMD);
          //ble_param.getdata = CONTINUE_CMD;
    }
    if(ble_param.getdata == '0')
    {
        CAN_Transmit(STOP_CMD);         //ble_param.getdata = CONTINUE_CMD;
    }
}

void BLE_tx()
{
    Clear_Display();
    cputline(ble_param.latitude,10); //Adjust Delay as per data length
    //printf("%s",ble_param.latitude);
    cputline(ble_param.longitude,10);
    cputline(ble_param.bearing,50);
    //printf("%s",ble_param.longitude);
}

void check_for_data_on_ble()
{
    BLE_rx();
}
