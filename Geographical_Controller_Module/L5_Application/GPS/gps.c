/*
 * GPS.c
 *
 *  Created on: Mar 31, 2019
 *      Author: Vidushi
 *      Version: V1.00
 */

#include <gps.h>
#include <stdio.h>
#include <stdbool.h>
#include "c_uart2.h"
#include "c_io.h"
#include "c_uart_dev.h"
#include "utilities.h"
#include <stdlib.h>
#include <string.h>

void create_gps_config(void)
{
    cputline(PMTK_SET_NMEA_OUTPUT_RMCONLY, 10);
    cputline(PMTK_SET_NMEA_UPDATE_10HZ, 10);
    cputline(PMTK_API_SET_FIX_CTL_5HZ, 10);
}

//UART INIT
void init_gps(void)
{
    Clear_Display();      /* Clear the display */
    cUart2_init(UART2_BAUD_RATE, UART_RECEIVE_BUFFER_SIZE, UART_TRANSMIT_BUFFER_SIZE);      /* Init baud rate */
    create_gps_config();
}

void gps_rx(void)
{
    if(cgets(gps_line, 80, 80))
    {
        setLED(3,1);
    }
    else
    {
        setLED(3,0);
    }
}

bool gps_parse_data(void)
{
    if(!memcmp(gps_line, "$GPRMC", 6) && gps_line[18]=='A' && gps_line[30]=='N' && gps_line[43]=='W')
    {
        setLCD_LEFT('0');
        setLCD_Right('F');

        char lat[10] = "";
        char lon[11] = "";

        memcpy(lat, (gps_line+20), 9);
        memcpy(lon, (gps_line+32), 10);

        float tempLat = (float)(atof(lat));        // Change float values to 6 digits
        latitude = (tempLat - 100*(int)(tempLat/100))/60.0;
        latitude += (int)(tempLat/100);
      //  printf("%f,",latitude);

        float tempLon = (float)atof(lon);
        longitude = (tempLon - 100*(int)(tempLon/100))/60.0;
        longitude += (int)(tempLon/100);
        longitude = -longitude;
      //  printf("%f,",longitude);
        setLED(2,1);
        return true;
    }
    else
    {
        latitude = 0.0;
        longitude = 0.0;
        setLED(2,0);
    }

    return false;
}

void check_for_data_on_gps(void)
{
    gps_rx();
    delay_ms(1);
    gps_parse_data();
}
