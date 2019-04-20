/*
 * c_gpio.cpp
 *
 *  Created on: Apr 9, 2019
 *      Author: halak
 */

#include "c_gpio.h"
#include "gpio.hpp"

GPIO *gpio;

void setPin(void)
{
     gpio = new GPIO(P2_6);
}

void setInput()
{
    gpio->setAsInput();
}

void setOutput()
{
    gpio->setAsOutput();
}

void SET(bool check)
{
    gpio->set(check);
}

bool read_pin(void){
    return gpio->read();
}
