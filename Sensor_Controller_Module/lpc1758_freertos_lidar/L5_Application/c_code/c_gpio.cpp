/*
 * c_gpio.cpp
 *
 *  Created on: Apr 9, 2019
 *      Author: halak
 */

#include "c_gpio.h"
#include "gpio.hpp"

GPIO *gpio;

void setPin()
{
     gpio = new GPIO(P2_2);
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
