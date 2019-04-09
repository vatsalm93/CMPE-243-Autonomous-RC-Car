/*
 * compass.c
 *
 *  Created on: Apr 4, 2019
 *      Author: Vidushi
 */

#include "stdio.h"
#include "compass/compass.h"
#include "c_io.h"
#include "utilities.h"
#include "c_i2c_base.h"

#define COMPASS_OFFSET 10;

float Compass_Get_Heading_Angle(void)
{
    int heading_int = 0;
    float heading_float = 0;
    uint8_t buffer[2] = { 0 };

    if (I2C_ReadRegisters(COMPASS_I2C_ADDR, COMPASS_BEARING_16BIT_REG_ADDR, &buffer[0], READ_TWO_REGISTERS))
    {
        heading_int = buffer[0];
        heading_int <<= 8;
        heading_int += buffer[1];
        heading_float = (float)(heading_int/10.00);
       // heading_float = heading_float + COMPASS_OFFSET;
        setLCD_Display(heading_int);
        printf("%f\n", heading_float);
        return heading_float;
    }
    return 0;
}


void Start_Compass_Calibration(void)
{
    uint8_t buffer[1] = { 0 };
    buffer[0] = 0xF0;
    I2C_writeRegisters(COMPASS_I2C_ADDR, COMMAND_REG_ADDR, &buffer[0], READ_ONE_REGISTER);
    delay_ms(30);
    buffer[0] = 0xF5;
    I2C_writeRegisters(COMPASS_I2C_ADDR, COMMAND_REG_ADDR, &buffer[0], READ_ONE_REGISTER);
    delay_ms(30);
    buffer[0] = 0xF6;
    I2C_writeRegisters(COMPASS_I2C_ADDR, COMMAND_REG_ADDR, &buffer[0], READ_ONE_REGISTER);
}


void Stop_Compass_Calibration(void)
{
    uint8_t buffer[1] = { 0 };
    buffer[0] = 0xF8;
    I2C_writeRegisters(COMPASS_I2C_ADDR, COMMAND_REG_ADDR, &buffer[0], READ_ONE_REGISTER);
}

void Set_Default_Calibration(void)
{
    uint8_t buffer[1] = { 0 };
    buffer[0] = 0x20;
    I2C_writeRegisters(COMPASS_I2C_ADDR, COMMAND_REG_ADDR, &buffer[0], READ_ONE_REGISTER);
    delay_ms(30);
    buffer[0] = 0x2A;
    I2C_writeRegisters(COMPASS_I2C_ADDR, COMMAND_REG_ADDR, &buffer[0], READ_ONE_REGISTER);
    delay_ms(30);
    buffer[0] = 0x60;
    I2C_writeRegisters(COMPASS_I2C_ADDR, COMMAND_REG_ADDR, &buffer[0], READ_ONE_REGISTER);
}

void get_compass_data(void)
{
    switch(switch_detect())
    {
        case sw1:
            setLED(1,1);
            Start_Compass_Calibration();
            break;
        case sw2:
            setLED(2,1);
            Stop_Compass_Calibration();
            break;
        case sw3:
            setLED(3,1);
            Set_Default_Calibration();
            break;
        case sw4:
            setLED(4,1);
            Compass_Get_Heading_Angle();
            break;
        default:
        break;
    }
}

