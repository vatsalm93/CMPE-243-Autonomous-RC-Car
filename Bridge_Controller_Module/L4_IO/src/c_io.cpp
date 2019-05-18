/*
 * c_io.cpp
 *
 *  Created on: Mar 4, 2019
 *      Author: vidushi
 */
#include "c_io.h"
#include "io.hpp"

void setLED(uint8_t ledNum, bool on)
{
    LE.set(ledNum, on);
}

void setLCD_Display(char num)
{
    LD.setNumber(num);
}

void setLCD_LEFT(char num)
{
    LD.setLeftDigit(num);
}

void setLCD_Right(char num)
{
    LD.setRightDigit(num);
}

void Clear_Display(void)
{
    LD.clear();
}

uint8_t switch_detect(void)
{
    uint8_t switches = SW.getSwitchValues();
    return switches;
}

bool switch_function(int number)
{
    bool res = SW.getSwitch(number);
    return res;
}

