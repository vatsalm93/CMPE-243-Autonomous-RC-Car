/*
 * c_gpio.h
 *
 *  Created on: Apr 9, 2019
 *      Author: halak
 */

#ifndef C_GPIO_H_
#define C_GPIO_H_

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void setPin(void);
void setInput(void);
void setOutput(void);
void SET(bool check);
bool read_pin(void);

#ifdef __cplusplus
}
#endif

#endif /* C_GPIO_H_ */
