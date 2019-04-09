/*
 * BLE_HC05.c
 *
 *  Created on: Mar 31, 2019
 *      Author: Vidushi
 *      Version: V1.00
 */

#include <Bridge_Module/ble_hc05.h>
#include <stdio.h>
#include "c_uart2.h"
#include "c_io.h"
#include "c_uart_dev.h"

ble_msg_t ble_param = {0};

void BLE_init()
{
    Clear_Display();      /* Clear the display */
    cUart2_init(UART2_BAUD_RATE, UART2_RXQ_SIZE, UART2_TXQ_SIZE);      /* Init baud rate */

    printf("\r\nHC-05 Version:%s\r\n",FIRMWARE_VERSION);
    // Default Values for now
    ble_param.latitude = "37.121356,";
    ble_param.longitude = "-121.121356";
}

void BLE_rx()
{
    while(cgetChar(&ble_param.getdata,0))
     {
        setLED(2,1);
        setLCD_Display(ble_param.getdata);
        if ('\r' != ble_param.getdata && '\n' != ble_param.getdata) {
            printf("%c",ble_param.getdata);
        }
      }
}

void BLE_tx()
{
    Clear_Display();
    cputline(ble_param.latitude,10); //Adjust Delay as per data length
    printf("%s",ble_param.latitude);
    cputline(ble_param.longitude,10);
    printf("%s",ble_param.longitude);
}

void check_for_data_on_ble()
{
    if(switch_detect() > 0)
    {
        BLE_tx();
    }

    BLE_rx();
}
