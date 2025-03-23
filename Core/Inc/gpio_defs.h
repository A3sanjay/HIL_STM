/*
 * gpio_defs.h
 *
 *  Created on: Mar. 18, 2025
 *      Author: arvin
 */

#ifndef INC_GPIO_DEFS_H_
#define INC_GPIO_DEFS_H_

#include <stdint.h>

#include "main.h"

typedef struct {
    GPIO_TypeDef *gpio_port;
    uint16_t gpio_pin;
} GPIO_Pin;

#endif /* INC_GPIO_DEFS_H_ */
