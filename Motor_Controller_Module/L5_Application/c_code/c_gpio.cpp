/*
 * c_gpio.cpp
 *
 *  Created on: Apr 9, 2019
 *      Author: Jay
 */

#include "c_gpio.h"
#include "gpio.hpp"

GPIO *gpio;

void GPIO_interrupt(void) {
     gpio = new GPIO(P2_6);
     gpio->setAsInput();
}
